#include "common.h"

#include <errno.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <zlib.h>

#include <psyz/video.h>

#include "oracle.h"

#define POKE_CROP 128
#define POKE_SETTLE_FRAMES 60
#define POKE_MAX_CAPTURES 64
#define POKE_GRID_COLUMNS 10

struct PokeHold {
    int first;
    int last;
    u16 buttons;
};

struct PokeField {
    const char* name;
    size_t offset;
};

#define POKE_FIELD(field)                         \
    {                                             \
#field, offsetof(struct PlayerObj, field) \
    }

static const struct PokeField poke_fields[] = {
    POKE_FIELD(unk15),
    POKE_FIELD(hp),
    POKE_FIELD(invincibility_timer),
    POKE_FIELD(hurt_type),
    POKE_FIELD(air_state),
    POKE_FIELD(dash_momentum),
    POKE_FIELD(air_action),
    POKE_FIELD(attacking),
    POKE_FIELD(weapon),
    POKE_FIELD(hurt_phase),
    POKE_FIELD(hit_facing),
    POKE_FIELD(stock_charge),
    POKE_FIELD(armor_parts),
    POKE_FIELD(arm_type),
    POKE_FIELD(boss_flags),
    POKE_FIELD(stun_timer),
    POKE_FIELD(script_state),
    POKE_FIELD(script_action),
    POKE_FIELD(script_facing),
    POKE_FIELD(capsule_state),
    POKE_FIELD(ride_state),
    POKE_FIELD(ride_animation),
    POKE_FIELD(item_step),
    POKE_FIELD(unk70),
    POKE_FIELD(unk71),
};

struct PokeSet {
    size_t offset;
    u8 value;
};

struct PokeScenario {
    char name[64];
    int character;
    int set_state;
    int state;
    int unk5;
    int unk6;
    int unk7;
    int dx;
    int dy;
    int start;
    int frames;
    int stride;
    int full;
    int camera;
    int follow;
    int track_entity;
    int hold_count;
    struct PokeHold holds[16];
    int set_count;
    struct PokeSet sets[16];
    int anim;
    int weapon;
    int has_vx;
    int has_vy;
    double vx;
    double vy;
};

int mmx4_pc_hide_background;

static const char* poke_dir;
static int poke_initialized;
static int settle_frames;
static s8 settle_unk5 = -1;
static int in_child;
static struct PokeScenario scenario;
static int child_frame;
static FILE* child_log;
static unsigned char* strip;
static int strip_size;
static int strip_scale;
static int strip_columns;
static int strip_rows;
static int capture_count;
static void png_chunk(FILE* file, const char* type, const unsigned char* data, u32 length)
{
    unsigned char header[8];
    unsigned char trailer[4];
    uLong crc;

    header[0] = length >> 24;
    header[1] = length >> 16;
    header[2] = length >> 8;
    header[3] = length;
    memcpy(header + 4, type, 4);
    fwrite(header, 1, 8, file);
    if (length != 0)
        fwrite(data, 1, length, file);
    crc = crc32(0, (const Bytef*)type, 4);
    if (length != 0)
        crc = crc32(crc, data, length);
    trailer[0] = crc >> 24;
    trailer[1] = crc >> 16;
    trailer[2] = crc >> 8;
    trailer[3] = crc;
    fwrite(trailer, 1, 4, file);
}

static void write_png(const char* path, const unsigned char* pixels, int width,
    int height, int stride_width, int x0, int y0)
{
    static const unsigned char signature[8] = { 0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n' };
    unsigned char ihdr[13];
    size_t row = (size_t)width * 3 + 1;
    size_t raw_size = row * height;
    unsigned char* raw = malloc(raw_size);
    uLongf packed_size = compressBound(raw_size);
    unsigned char* packed = malloc(packed_size);
    FILE* file;
    int y;

    if (raw == NULL || packed == NULL)
        goto done;
    for (y = 0; y < height; y++) {
        raw[row * y] = 0;
        memcpy(raw + row * y + 1,
            pixels + ((size_t)(y0 + y) * stride_width + x0) * 3, (size_t)width * 3);
    }
    if (compress2(packed, &packed_size, raw, raw_size, 6) != Z_OK)
        goto done;
    file = fopen(path, "wb");
    if (file == NULL)
        goto done;
    ihdr[0] = width >> 24;
    ihdr[1] = width >> 16;
    ihdr[2] = width >> 8;
    ihdr[3] = width;
    ihdr[4] = height >> 24;
    ihdr[5] = height >> 16;
    ihdr[6] = height >> 8;
    ihdr[7] = height;
    ihdr[8] = 8;
    ihdr[9] = 2;
    ihdr[10] = 0;
    ihdr[11] = 0;
    ihdr[12] = 0;
    fwrite(signature, 1, 8, file);
    png_chunk(file, "IHDR", ihdr, 13);
    png_chunk(file, "IDAT", packed, (u32)packed_size);
    png_chunk(file, "IEND", NULL, 0);
    fclose(file);
done:
    free(raw);
    free(packed);
}

static struct BackgroundObj* player_camera(void)
{
    return &background_objects[(u8)g_Player.bg_offset < 3 ? (u8)g_Player.bg_offset : 0];
}

static void capture(int slot, int center_x, int center_y)
{
    unsigned char* pixels;
    int width;
    int height;
    int size;
    int x0;
    int y0;
    int y;
    size_t row_bytes;
    unsigned char* dst;

    pixels = Psyz_VideoAllocCapturedFrame(&width, &height);
    if (pixels == NULL || width <= 0 || height <= 0) {
        free(pixels);
        return;
    }
    if (scenario.full) {
        char path[1024];

        snprintf(path, sizeof(path), "%s/%s_c%u_f%02d.png", poke_dir, scenario.name,
            (u8)g_Player.unk2, slot * scenario.stride);
        write_png(path, pixels, width, height, width, 0, 0);
    }
    if (strip == NULL) {
        strip_scale = width / 320 > 0 ? width / 320 : 1;
        strip_size = POKE_CROP * strip_scale;
        if (strip_size > height)
            strip_size = height;
        strip = calloc((size_t)strip_size * strip_size * strip_columns * strip_rows, 3);
    }
    size = strip_size;
    x0 = center_x * strip_scale - size / 2;
    y0 = (center_y - 16) * strip_scale - size / 2;
    if (x0 < 0)
        x0 = 0;
    if (y0 < 0)
        y0 = 0;
    if (x0 + size > width)
        x0 = width - size;
    if (y0 + size > height)
        y0 = height - size;
    row_bytes = (size_t)size * strip_columns * 3;
    if (strip != NULL) {
        dst = strip + (size_t)(slot / strip_columns) * size * row_bytes
            + (size_t)(slot % strip_columns) * size * 3;
        for (y = 0; y < size; y++)
            memcpy(dst + y * row_bytes, pixels + ((size_t)(y0 + y) * width + x0) * 3,
                (size_t)size * 3);
    }
    free(pixels);
}

static void clear_enemies(void)
{
    int i;

    if (getenv("MMX4_PLAYER_POKE_KEEP_OBJECTS") != NULL)
        return;
    for (i = 0; i < (int)COUNT(main_objects); i++)
        main_objects[i].active = 0;
    for (i = 0; i < (int)COUNT(shot_objects); i++)
        shot_objects[i].active = 0;
}

static void follow_player(void)
{
    struct BackgroundObj* camera = player_camera();

    camera->unk1C = 0x7000;
    camera->unk1E = -0x7000;
    camera->unk20 = 0x7000;
    camera->unk22 = -0x7000;
    camera->unk2C = 0x70;
    camera->unk2E = 0x90;
    camera->unk30 = 0xA0;
    camera->unk32 = 0xA0;
}

static void child_frame_end(void)
{
    static int pending_slot = -1;
    static int pending_x;
    static int pending_y;
    char path[1024];
    int offset = child_frame - scenario.start;
    int last = (capture_count - 1) * scenario.stride;
    struct PlayerObj* tracked = scenario.track_entity ? &g_Entity : &g_Player;

    if (pending_slot >= 0) {
        capture(pending_slot, pending_x, pending_y);
        pending_slot = -1;
    }
    fprintf(child_log, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%04x\n", offset,
        (u8)tracked->state, (u8)tracked->unk5, (u8)tracked->unk6,
        (u8)tracked->unk7, (u8)tracked->hurt_type, tracked->previous_animation_index,
        tracked->x_pos.i.hi, tracked->y_pos.i.hi, tracked->x_vel.val,
        tracked->y_vel.val, mmx4_pc_player_poke_input());
    if (offset >= 0 && offset <= last && offset % scenario.stride == 0) {
        pending_slot = offset / scenario.stride;
        pending_x = tracked->x_pos.i.hi - player_camera()->x_pos.i.hi;
        pending_y = tracked->y_pos.i.hi - player_camera()->y_pos.i.hi;
    }
    clear_enemies();
    if (scenario.follow)
        follow_player();
    if (offset > last) {
        if (strip != NULL) {
            snprintf(path, sizeof(path), "%s/%s_c%u.png", poke_dir, scenario.name,
                (u8)g_Player.unk2);
            write_png(path, strip, strip_size * strip_columns, strip_size * strip_rows,
                strip_size * strip_columns, 0, 0);
        }
        fclose(child_log);
        _exit(0);
    }
    child_frame++;
}

u16 mmx4_pc_player_poke_input(void)
{
    u16 buttons = 0;
    int i;

    if (!in_child)
        return 0;
    for (i = 0; i < scenario.hold_count; i++) {
        if (child_frame >= scenario.holds[i].first && child_frame <= scenario.holds[i].last)
            buttons |= scenario.holds[i].buttons;
    }
    return buttons;
}

static u16 parse_buttons(char* text)
{
    static const struct {
        const char* name;
        u16 mask;
    } names[] = {
        { "up", PADLup },
        { "down", PADLdown },
        { "left", PADLleft },
        { "right", PADLright },
        { "cross", PADRdown },
        { "circle", PADRright },
        { "square", PADRleft },
        { "triangle", PADRup },
        { "l1", PADL1 },
        { "r1", PADR1 },
        { "l2", PADL2 },
        { "r2", PADR2 },
        { "start", PADstart },
        { "select", PADselect },
        { "jump", PADRdown },
        { "shoot", PADRleft },
        { "dash", PADRright },
        { "special", PADRup },
    };
    u16 mask = 0;
    char* item;
    size_t i;

    for (item = strtok(text, "+"); item != NULL; item = strtok(NULL, "+")) {
        for (i = 0; i < COUNT(names); i++) {
            if (strcmp(item, names[i].name) == 0)
                mask |= names[i].mask;
        }
    }
    return mask;
}

static void parse_holds(char* text)
{
    char* save;
    char* item;

    for (item = strtok_r(text, ",", &save); item != NULL && scenario.hold_count < (int)COUNT(scenario.holds);
         item = strtok_r(NULL, ",", &save)) {
        struct PokeHold* hold = &scenario.holds[scenario.hold_count];
        char* colon = strchr(item, ':');
        char* dash;

        if (colon == NULL)
            continue;
        *colon = '\0';
        hold->first = atoi(item);
        dash = strchr(item, '-');
        hold->last = dash != NULL ? atoi(dash + 1) : hold->first;
        hold->buttons = parse_buttons(colon + 1);
        scenario.hold_count++;
    }
}

static void parse_sets(char* text)
{
    char* save;
    char* item;
    size_t i;

    for (item = strtok_r(text, ",", &save); item != NULL && scenario.set_count < (int)COUNT(scenario.sets);
         item = strtok_r(NULL, ",", &save)) {
        char* colon = strchr(item, ':');

        if (colon == NULL)
            continue;
        *colon = '\0';
        for (i = 0; i < COUNT(poke_fields); i++) {
            if (strcmp(item, poke_fields[i].name) == 0) {
                scenario.sets[scenario.set_count].offset = poke_fields[i].offset;
                scenario.sets[scenario.set_count].value = (u8)strtol(colon + 1, NULL, 0);
                scenario.set_count++;
                break;
            }
        }
        if (i == COUNT(poke_fields))
            fprintf(stderr, "MMX4 PC: unknown poke field %s\n", item);
    }
}

static int parse_scenario(char* line)
{
    char* save;
    char* item;

    memset(&scenario, 0, sizeof(scenario));
    scenario.character = -1;
    scenario.frames = 60;
    scenario.stride = 4;
    scenario.anim = -1;
    scenario.weapon = -1;
    scenario.follow = 1;
    item = strtok_r(line, " \t\r\n", &save);
    if (item == NULL || item[0] == '#')
        return 0;
    snprintf(scenario.name, sizeof(scenario.name), "%s", item);
    while ((item = strtok_r(NULL, " \t\r\n", &save)) != NULL) {
        char* value = strchr(item, '=');

        if (value == NULL)
            continue;
        *value++ = '\0';
        if (strcmp(item, "char") == 0) {
            scenario.character = atoi(value);
        } else if (strcmp(item, "poke") == 0) {
            scenario.set_state = 1;
            scenario.state = (int)strtol(value, &value, 0);
            scenario.unk5 = *value == ':' ? (int)strtol(value + 1, &value, 0) : 0;
            scenario.unk6 = *value == ':' ? (int)strtol(value + 1, &value, 0) : 0;
            scenario.unk7 = *value == ':' ? (int)strtol(value + 1, &value, 0) : 0;
        } else if (strcmp(item, "set") == 0) {
            parse_sets(value);
        } else if (strcmp(item, "anim") == 0) {
            scenario.anim = (int)strtol(value, NULL, 0);
        } else if (strcmp(item, "weapon") == 0) {
            scenario.weapon = (int)strtol(value, NULL, 0);
        } else if (strcmp(item, "vx") == 0) {
            scenario.has_vx = 1;
            scenario.vx = atof(value);
        } else if (strcmp(item, "vy") == 0) {
            scenario.has_vy = 1;
            scenario.vy = atof(value);
        } else if (strcmp(item, "hold") == 0) {
            parse_holds(value);
        } else if (strcmp(item, "dx") == 0) {
            scenario.dx = atoi(value);
        } else if (strcmp(item, "dy") == 0) {
            scenario.dy = atoi(value);
        } else if (strcmp(item, "start") == 0) {
            scenario.start = atoi(value);
        } else if (strcmp(item, "frames") == 0) {
            scenario.frames = atoi(value);
        } else if (strcmp(item, "track") == 0) {
            scenario.track_entity = strcmp(value, "entity") == 0;
        } else if (strcmp(item, "follow") == 0) {
            scenario.follow = atoi(value);
        } else if (strcmp(item, "camera") == 0) {
            scenario.camera = atoi(value);
        } else if (strcmp(item, "full") == 0) {
            scenario.full = atoi(value);
        } else if (strcmp(item, "stride") == 0) {
            scenario.stride = atoi(value) > 0 ? atoi(value) : 1;
        }
    }
    if (scenario.character >= 0 && scenario.character != (u8)g_Player.unk2)
        return 0;
    return 1;
}

void player_update_shot_types(struct PlayerObj* arg0);
void player_equip_weapon(struct PlayerObj* arg0);
s32 player_set_animation(struct PlayerObj* arg0, s32 arg1);

static void run_scenario(void)
{
    char path[1024];
    pid_t pid;
    int status;
    int i;

    fflush(NULL);
    pid = fork();
    if (pid < 0) {
        perror("MMX4 PC: fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        in_child = 1;
        alarm(120);
        capture_count = (scenario.frames + scenario.stride - 1) / scenario.stride;
        if (capture_count > POKE_MAX_CAPTURES)
            capture_count = POKE_MAX_CAPTURES;
        if (capture_count < 1)
            capture_count = 1;
        strip_columns = capture_count < POKE_GRID_COLUMNS ? capture_count : POKE_GRID_COLUMNS;
        strip_rows = (capture_count + strip_columns - 1) / strip_columns;
        snprintf(path, sizeof(path), "%s/%s_c%u.tsv", poke_dir, scenario.name,
            (u8)g_Player.unk2);
        child_log = fopen(path, "w");
        if (child_log == NULL)
            _exit(1);
        fputs("frame\tstate\tunk5\tunk6\tunk7\thurt_type\tanim\tx\ty\tx_vel\ty_vel\tinput\n", child_log);
        clear_enemies();
        g_Player.x_pos.i.hi += scenario.dx;
        g_Player.y_pos.i.hi += scenario.dy;
        if (scenario.follow)
            follow_player();
        if (scenario.camera) {
            for (i = 0; i < 3; i++) {
                background_objects[i].x_pos.i.hi += scenario.dx;
                background_objects[i].y_pos.i.hi += scenario.dy;
            }
        }
        for (i = 0; i < scenario.set_count; i++)
            ((u8*)&g_Player)[scenario.sets[i].offset] = scenario.sets[i].value;
        if (scenario.weapon >= 0) {
            g_Player.weapon = scenario.weapon;
            player_update_shot_types(&g_Player);
            player_equip_weapon(&g_Player);
        }
        if (scenario.anim >= 0)
            player_set_animation(&g_Player, scenario.anim);
        if (scenario.has_vx)
            g_Player.x_vel.val = (s32)(scenario.vx * 65536.0);
        if (scenario.has_vy)
            g_Player.y_vel.val = (s32)(scenario.vy * 65536.0);
        if (scenario.set_state) {
            g_Player.state = scenario.state;
            g_Player.unk5 = scenario.unk5;
            g_Player.unk6 = scenario.unk6;
            g_Player.unk7 = scenario.unk7;
        }
        return;
    }
    if (waitpid(pid, &status, 0) < 0 || !WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        fprintf(stderr, "MMX4 PC: scenario %s failed (status 0x%x)\n", scenario.name, status);
    }
}

u8 func_8002D724(struct PlayerObj* object, s16 x, s16 y);

static void scan_tiles(void)
{
    char path[1024];
    FILE* file;
    int x;
    int y;

    snprintf(path, sizeof(path), "%s/tiles.tsv", poke_dir);
    file = fopen(path, "w");
    if (file == NULL)
        return;
    for (y = 0; y < 0x2000; y += 16) {
        for (x = 0; x < 0x4000; x += 16) {
            u8 attribute = func_8002D724(&g_Player, x, y);

            if (attribute != 0)
                fprintf(file, "%d\t%d\t%02x\n", x, y, attribute);
        }
    }
    fclose(file);
}

static void run_all_pokes(void)
{
    const char* script = getenv("MMX4_PLAYER_POKE_SCRIPT");
    const char* only = getenv("MMX4_PLAYER_POKE_ONLY");
    char line[1024];
    FILE* file;
    int i;

    fprintf(stderr, "MMX4 PC: player settled at state %u unk5 0x%02x x %d y %d hp %d armor %02x arm %d zero %02x giga %d, poking\n",
        (u8)g_Player.state, (u8)g_Player.unk5, g_Player.x_pos.i.hi, g_Player.y_pos.i.hi,
        g_Player.hp, (u8)g_Player.armor_parts, g_Player.arm_type, (u8)g_Player.boss_flags,
        g_Player.weapon_energy[0]);
    if (getenv("MMX4_PLAYER_POKE_SCAN") != NULL)
        scan_tiles();
    if (script != NULL && *script != '\0') {
        file = fopen(script, "r");
        if (file == NULL) {
            fprintf(stderr, "MMX4 PC: unable to open %s\n", script);
            exit(EXIT_FAILURE);
        }
        while (!in_child && fgets(line, sizeof(line), file) != NULL) {
            if (!parse_scenario(line))
                continue;
            if (only != NULL && *only != '\0' && strcmp(only, scenario.name) != 0)
                continue;
            run_scenario();
        }
        if (!in_child)
            fclose(file);
    } else {
        for (i = 0; i < 64 && !in_child; i++) {
            if (player_normal_state_funcs[i] == player_idle)
                continue;
            snprintf(line, sizeof(line), "poke_1_%02x poke=1:%d", i, i);
            parse_scenario(line);
            run_scenario();
        }
        for (i = 0; i < 4 && !in_child; i++) {
            snprintf(line, sizeof(line), "poke_2_%02x poke=2:%d", i, i);
            parse_scenario(line);
            run_scenario();
        }
    }
    if (in_child)
        return;
    fprintf(stderr, "MMX4 PC: player pokes written to %s\n", poke_dir);
    fflush(NULL);
    _exit(0);
}

void mmx4_pc_player_dump(long frame)
{
    (void)frame;
    if (!poke_initialized) {
        poke_initialized = 1;
        poke_dir = getenv("MMX4_PLAYER_POKE_DIR");
        if (poke_dir != NULL && *poke_dir == '\0')
            poke_dir = NULL;
        if (poke_dir != NULL && mkdir(poke_dir, 0777) != 0 && errno != EEXIST) {
            fprintf(stderr, "MMX4 PC: unable to create %s\n", poke_dir);
            exit(EXIT_FAILURE);
        }
        mmx4_pc_hide_background = poke_dir != NULL && getenv("MMX4_PLAYER_POKE_BACKGROUND") == NULL;
    }
    if (poke_dir == NULL)
        return;
    if (in_child) {
        child_frame_end();
        return;
    }
    if (engine_obj.state != 6 || !g_Player.active || g_Player.state != 1
        || g_Player.unk5 == 0 || g_Player.unk5 != settle_unk5) {
        settle_unk5 = g_Player.unk5;
        settle_frames = 0;
        return;
    }
    if (++settle_frames == POKE_SETTLE_FRAMES)
        run_all_pokes();
}
