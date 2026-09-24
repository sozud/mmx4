#include "common.h"

#include <SDL3/SDL.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct InputEvent {
    unsigned long frame;
    u16 buttons;
};

static struct InputEvent events[256];
static size_t event_count;
static unsigned long frame_number;
static unsigned long max_frames;
static u32 previous_game_state;
static u32 previous_engine_state;
static unsigned long stable_state_frames;
static unsigned long capture_transition;
static u32 capture_previous_game_state;
static u32 capture_previous_engine_state;
static unsigned long capture_stable_state_frames;
static int have_capture_previous_state;
struct PendingCapture {
    unsigned long transition;
    u32 game_state;
    u32 engine_state;
};
static struct PendingCapture pending_capture;
static int have_pending_capture;
static int initialized;
static FILE* replay_file;
static u8 replay_stage;
static u8 replay_substage;
static unsigned long replay_length;
static unsigned long replay_consumed;
static int replay_started;
static int replay_complete;
static int replay_exit_requested;
static unsigned long replay_load_points[64];
static unsigned char replay_load_input_phase[64];
static unsigned char replay_load_pending[64];
static size_t replay_load_point_count;
static size_t replay_load_point_index;
static unsigned long replay_xa_stop_points[64];
static size_t replay_xa_stop_point_count;
static size_t replay_xa_stop_point_index;

static void replay_fail(const char* reason)
{
    fprintf(stderr, "MMX4 PC: replay %s: %s\n", mmx4_pc_replay_path, reason);
    exit(EXIT_FAILURE);
}

static void open_replay_sync(void)
{
    const char* override = getenv("MMX4_REPLAY_SYNC");
    char* default_path = NULL;
    const char* path = override;
    FILE* file;
    char* document;
    long size;
    char* cursor;

    if (path == NULL || *path == '\0') {
        size_t length = strlen(mmx4_pc_replay_path);
        default_path = malloc(length + sizeof(".sync.json"));
        if (default_path == NULL)
            abort();
        memcpy(default_path, mmx4_pc_replay_path, length);
        memcpy(default_path + length, ".sync.json", sizeof(".sync.json"));
        path = default_path;
    }
    file = fopen(path, "rb");
    free(default_path);
    if (file == NULL)
        return;
    if (fseek(file, 0, SEEK_END) != 0 || (size = ftell(file)) < 0) {
        fclose(file);
        replay_fail("unable to read sync sidecar");
    }
    rewind(file);
    document = malloc((size_t)size + 1);
    if (document == NULL)
        abort();
    if (fread(document, (size_t)size, 1, file) != 1) {
        free(document);
        fclose(file);
        replay_fail("unable to read sync sidecar");
    }
    document[size] = '\0';
    fclose(file);

    cursor = document;
    while ((cursor = strstr(cursor, "\"sample\"")) != NULL) {
        char* object_end = strchr(cursor, '}');
        char* colon = strchr(cursor, ':');
        char* kind;
        char* load_kind;
        char* xa_kind;
        char* pending;
        unsigned long sample;

        if (object_end == NULL || colon == NULL || colon > object_end)
            break;
        sample = strtoul(colon + 1, NULL, 10);
        kind = strstr(colon, "\"kind\"");
        load_kind = kind == NULL ? NULL : strstr(kind, "\"load-complete\"");
        xa_kind = kind == NULL ? NULL : strstr(kind, "\"xa-complete\"");
        if (kind != NULL && kind < object_end && xa_kind != NULL && xa_kind < object_end) {
            if (replay_xa_stop_point_count == COUNT(replay_xa_stop_points)) {
                free(document);
                replay_fail("too many xa-complete sync points");
            }
            replay_xa_stop_points[replay_xa_stop_point_count++] = sample;
        }
        if (kind != NULL && kind < object_end && load_kind != NULL && load_kind < object_end) {
            if (replay_load_point_count == COUNT(replay_load_points)) {
                free(document);
                replay_fail("too many load-complete sync points");
            }
            char* phase = strstr(colon, "\"phase\"");

            replay_load_input_phase[replay_load_point_count] = phase != NULL && phase < object_end && strstr(phase, "\"input\"") != NULL && strstr(phase, "\"input\"") < object_end;
            pending = strstr(colon, "\"pending\"");
            replay_load_pending[replay_load_point_count] = pending != NULL && pending < object_end;
            replay_load_points[replay_load_point_count++] = sample;
        }
        cursor = object_end + 1;
    }
    free(document);
}

static void open_replay(void)
{
    unsigned char header[16];
    long size;

    if (mmx4_pc_replay_path == NULL || *mmx4_pc_replay_path == '\0')
        return;
    replay_file = fopen(mmx4_pc_replay_path, "rb");
    if (replay_file == NULL)
        replay_fail("unable to open");
    if (fseek(replay_file, 0, SEEK_END) != 0)
        replay_fail("not seekable");
    size = ftell(replay_file);
    if (size < 0)
        replay_fail("unable to measure");
    if (size < 18 || ((size - 16) % 2) != 0)
        replay_fail("empty, odd-length, or truncated input stream");
    rewind(replay_file);
    if (fread(header, sizeof(header), 1, replay_file) != 1)
        replay_fail("unable to read header");
    if (memcmp(header, "MMX4RPL2", 8) != 0) {
        if (memcmp(header, "MMX4RPL1", 8) == 0)
            replay_fail("legacy video-clock replay; normalize it to MMX4RPL2 first");
        replay_fail("invalid magic");
    }
    if (header[12] != 0 || header[13] != 0 || header[14] != 0 || header[15] != 0)
        replay_fail("nonzero reserved header bytes");
    replay_stage = header[8];
    replay_substage = header[9];
    replay_length = (unsigned long)((size - 16) / 2);
    replay_exit_requested = getenv("MMX4_REPLAY_EXIT") != NULL;
    open_replay_sync();
    fprintf(stderr, "MMX4 PC: replay %s: %lu pad-read samples, stage %u-%u\n",
        mmx4_pc_replay_path, replay_length, replay_stage, replay_substage);
}

static u16 replay_input(void)
{
    unsigned char input[2];

    if (replay_file == NULL)
        return 0;
    if (!replay_started) {
        if (engine_obj.state != 6 || (u8)engine_obj.stage != replay_stage || (u8)engine_obj.substage != replay_substage)
            return 0;
        replay_started = 1;
        D_80141BD8.unk0 = 0;
        fprintf(stderr, "MMX4 PC: replay started at stage %u-%u (engine state 6)\n",
            replay_stage, replay_substage);
    }
    if (replay_complete)
        return 0;
    if (fread(input, sizeof(input), 1, replay_file) != 1)
        replay_fail("input stream ended unexpectedly");
    mmx4_pc_complete_scheduled_cd_load(1);
    replay_consumed++;
    if (replay_consumed == replay_length) {
        replay_complete = 1;
        fclose(replay_file);
        replay_file = NULL;
        fprintf(stderr, "MMX4 PC: replay finished after %lu frames\n",
            replay_consumed);
    }
    return (u16)(input[0] | (input[1] << 8));
}

int mmx4_pc_replay_active(void)
{
    return replay_file != NULL || replay_started;
}

long mmx4_pc_replay_frame(void)
{
    if (!replay_started || replay_consumed == 0)
        return -1;
    return (long)(replay_consumed - 1);
}

int mmx4_pc_replay_complete(void)
{
    return replay_complete;
}

int mmx4_pc_replay_exit_requested(void)
{
    return replay_exit_requested;
}

int mmx4_pc_replay_cd_load_due(int input_phase)
{
    unsigned long consumed = replay_consumed + (input_phase ? 1 : 0);

    if (!replay_started)
        return 1;
    if (replay_load_point_index >= replay_load_point_count)
        return 0;
    if (replay_load_input_phase[replay_load_point_index] != input_phase)
        return 0;
    return consumed >= replay_load_points[replay_load_point_index];
}

unsigned long mmx4_pc_replay_consumed(void)
{
    return replay_consumed;
}

int mmx4_pc_replay_cd_load_pending(void)
{
    if (!replay_started || replay_load_point_index >= replay_load_point_count)
        return 0;
    return replay_load_pending[replay_load_point_index];
}

int mmx4_pc_replay_xa_stop_due(void)
{
    if (!replay_started || replay_xa_stop_point_index >= replay_xa_stop_point_count)
        return 0;
    return replay_consumed >= replay_xa_stop_points[replay_xa_stop_point_index];
}

void mmx4_pc_replay_xa_stop_consume(void)
{
    if (replay_xa_stop_point_index < replay_xa_stop_point_count)
        replay_xa_stop_point_index++;
}

void mmx4_pc_replay_cd_load_consume(void)
{
    if (replay_started && replay_load_point_index < replay_load_point_count)
        replay_load_point_index++;
}

static u16 button_mask(const char* name)
{
    if (!strcmp(name, "start"))
        return PADstart;
    if (!strcmp(name, "select"))
        return PADselect;
    if (!strcmp(name, "up"))
        return PADLup;
    if (!strcmp(name, "down"))
        return PADLdown;
    if (!strcmp(name, "left"))
        return PADLleft;
    if (!strcmp(name, "right"))
        return PADLright;
    if (!strcmp(name, "cross"))
        return PADRdown;
    if (!strcmp(name, "circle"))
        return PADRright;
    if (!strcmp(name, "square"))
        return PADRleft;
    if (!strcmp(name, "triangle"))
        return PADRup;
    return 0;
}

static void parse_script(void)
{
    const char* script = getenv("MMX4_INPUT_SCRIPT");
    char* copy;
    char* item;

    if (script == NULL || *script == '\0')
        return;
    copy = strdup(script);
    if (copy == NULL)
        abort();
    for (item = strtok(copy, ","); item != NULL && event_count < COUNT(events);
         item = strtok(NULL, ",")) {
        char* colon = strchr(item, ':');
        char* button;
        u16 buttons = 0;

        if (colon == NULL)
            continue;
        *colon = '\0';
        button = colon + 1;
        while (button != NULL) {
            char* plus = strchr(button, '+');
            char* cursor;

            if (plus != NULL)
                *plus = '\0';
            for (cursor = button; *cursor != '\0'; cursor++)
                *cursor = (char)tolower((unsigned char)*cursor);
            buttons |= button_mask(button);
            button = plus == NULL ? NULL : plus + 1;
        }
        events[event_count].frame = strtoul(item, NULL, 0);
        events[event_count].buttons = buttons;
        event_count++;
    }
    free(copy);
}

static u16 scripted_input(void)
{
    size_t i;
    u16 buttons = 0;

    for (i = 0; i < event_count; i++) {
        if (events[i].frame == frame_number)
            buttons |= events[i].buttons;
    }
    return buttons;
}

static u16 oracle_input(void)
{
    const char* scene = getenv("MMX4_ORACLE_SCENE");
    u32 game_state;
    u32 engine_state;

    if (scene == NULL || strcmp(scene, "mission-briefing") != 0)
        return 0;
    memcpy(&game_state, &game_info, sizeof(game_state));
    memcpy(&engine_state, &engine_obj, sizeof(engine_state));
    if (game_state != previous_game_state || engine_state != previous_engine_state) {
        previous_game_state = game_state;
        previous_engine_state = engine_state;
        stable_state_frames = 0;
    } else {
        stable_state_frames++;
    }
    if (((game_state & 0xffff) == 0x0d01 || (game_state & 0xffff) == 0x0501 || (game_state & 0xffff) == 0x0106) && stable_state_frames % 30 < 2)
        return PADstart | PADRdown;
    if (((engine_state & 0xffff) == 0x0301 || (engine_state & 0xffff) == 0x0903 || (engine_state & 0xffff) == 0x0403) && stable_state_frames % 20 < 2)
        return PADRdown;
    return 0;
}

static u16 keyboard_input(void)
{
    const bool* keys = SDL_GetKeyboardState(NULL);
    u16 buttons = 0;

    if (keys == NULL)
        return 0;
    if (keys[SDL_SCANCODE_RETURN])
        buttons |= PADstart;
    if (keys[SDL_SCANCODE_BACKSPACE])
        buttons |= PADselect;
    if (keys[SDL_SCANCODE_UP])
        buttons |= PADLup;
    if (keys[SDL_SCANCODE_DOWN])
        buttons |= PADLdown;
    if (keys[SDL_SCANCODE_LEFT])
        buttons |= PADLleft;
    if (keys[SDL_SCANCODE_RIGHT])
        buttons |= PADLright;
    if (keys[SDL_SCANCODE_X])
        buttons |= PADRdown;
    if (keys[SDL_SCANCODE_C])
        buttons |= PADRright;
    if (keys[SDL_SCANCODE_Z])
        buttons |= PADRleft;
    if (keys[SDL_SCANCODE_V])
        buttons |= PADRup;
    return buttons;
}

void mmx4_pc_input_update(u8* pad_buffer)
{
    u16 buttons;
    u32 game_state;
    u32 engine_state;

    if (!initialized) {
        const char* value = getenv("MMX4_MAX_FRAMES");
        parse_script();
        open_replay();
        if (value != NULL)
            max_frames = strtoul(value, NULL, 0);
        initialized = 1;
    }
    if (max_frames != 0 && frame_number >= max_frames)
        exit(EXIT_SUCCESS);
    if (mmx4_pc_replay_active())
        buttons = replay_input();
    else
        buttons = scripted_input() | oracle_input() | keyboard_input();
    pad_buffer[0] = 0;
    pad_buffer[1] = 0x41;
    pad_buffer[2] = (u8)(~buttons >> 8);
    pad_buffer[3] = (u8)~buttons;
    frame_number++;
    memcpy(&game_state, &game_info, sizeof(game_state));
    memcpy(&engine_state, &engine_obj, sizeof(engine_state));
    if (!have_capture_previous_state || game_state != capture_previous_game_state || engine_state != capture_previous_engine_state) {
        pending_capture.transition = capture_transition++;
        pending_capture.game_state = game_state;
        pending_capture.engine_state = engine_state;
        have_pending_capture = 1;
        capture_previous_game_state = game_state;
        capture_previous_engine_state = engine_state;
        capture_stable_state_frames = 0;
        have_capture_previous_state = 1;
    } else if (++capture_stable_state_frames == 30 && D_8016DEA4 == 0) {
        mmx4_pc_write_state_screenshot(capture_transition++, frame_number,
            game_state, engine_state);
    }
    if (have_pending_capture && D_8016DEA4 == 0 && mmx4_pc_write_state_screenshot(pending_capture.transition, frame_number, pending_capture.game_state, pending_capture.engine_state)) {
        have_pending_capture = 0;
    }
}

unsigned long mmx4_pc_frame_number(void)
{
    return frame_number;
}
