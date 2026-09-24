#include "common.h"
#include "oracle.h"

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define FIELD_NONE ((size_t)-1)

struct LogTable {
    const char* name;
    const void* data;
    size_t count;
    size_t stride;
    size_t bg_offset;
    size_t x_vel;
    size_t y_vel;
    size_t texture;
    size_t clut;
    size_t animation_step;
    size_t animation_index;
};

static FILE* object_log;
static FILE* frame_log;
static FILE* extension_log;
static FILE* state_log;
extern u32 mmx4_pc_cd_reads;
extern u32 mmx4_pc_cd_read_sample;

extern u32 D_800FA724;
extern u32 D_800FA728;
extern u32 D_800FA72C;
extern u32 D_800FA730;
extern u32 D_800FA734;
extern u32 D_800FA738;
extern u32 D_800FA73C;
extern u32 D_800FA740;
extern u32 D_800FA744;

static void log_open(void)
{
    const char* directory = getenv("MMX4_OBJECT_LOG_DIR");
    char path[4096];

    if (object_log != NULL || directory == NULL || *directory == '\0')
        return;
    if (mkdir(directory, 0777) != 0 && errno != EEXIST) {
        perror(directory);
        exit(EXIT_FAILURE);
    }
    snprintf(path, sizeof(path), "%s/objects.tsv", directory);
    object_log = fopen(path, "w");
    snprintf(path, sizeof(path), "%s/frames.tsv", directory);
    frame_log = fopen(path, "w");
    snprintf(path, sizeof(path), "%s/extensions.tsv", directory);
    extension_log = fopen(path, "w");
    snprintf(path, sizeof(path), "%s/state.tsv", directory);
    state_log = fopen(path, "w");
    if (object_log == NULL || frame_log == NULL || extension_log == NULL || state_log == NULL) {
        perror(directory);
        exit(EXIT_FAILURE);
    }
    fprintf(object_log,
        "frame\tgame\tengine\ttable\tslot\tactive\tid\tsubtype\ton_screen\t"
        "state\tstep\tsubstep\tunk7\tx\ty\txvel\tyvel\tbgoff\tanim\t"
        "animstep\ttex\tclut\tbackref\n");
    fprintf(frame_log,
        "frame\tgame\tengine\tstate\tstage\tsubstage\tcheckpoint\tcharacter\t"
        "rng\tpad\tpad_prev\thealth\tplayer_x\tplayer_y\tbg0_x\tbg0_y\tphase\t"
        "cd_state\tcd_pending\thud\tboss\ttransition\tentity_intro\t"
        "player_health\tcd_reads\tcd_read_sample\n");
    fprintf(extension_log,
        "frame\tgame\tengine\ttable\tslot\tid\text80_value\text84_value\t"
        "ext88\text89\text8a\text8b\text8c\n");
    fprintf(state_log,
        "frame\tgame\tengine\ttable\tslot\tregion_a\tregion_b\tregion_c\n");
}

static const char* main_8_pointer_value(char* buffer, size_t size, const void* pointer)
{
    static const u32* const known[] = {
        &D_800FA724,
        &D_800FA728,
        &D_800FA72C,
        &D_800FA730,
        &D_800FA734,
        &D_800FA738,
        &D_800FA73C,
        &D_800FA740,
        &D_800FA744,
    };
    size_t i;

    if (pointer == NULL) {
        snprintf(buffer, size, "00000000");
        return buffer;
    }
    for (i = 0; i < COUNT(known); i++) {
        if (pointer == known[i]) {
            snprintf(buffer, size, "%08x", *known[i]);
            return buffer;
        }
    }
    snprintf(buffer, size, "!%p", pointer);
    return buffer;
}

static const char* field_u8(char* buffer, size_t size, const void* base,
    size_t offset)
{
    if (offset == FIELD_NONE)
        return "-";
    snprintf(buffer, size, "%d", (int)*(const s8*)((const u8*)base + offset));
    return buffer;
}

static const char* field_u16(char* buffer, size_t size, const void* base,
    size_t offset)
{
    u16 value;

    if (offset == FIELD_NONE)
        return "-";
    memcpy(&value, (const u8*)base + offset, sizeof(value));
    snprintf(buffer, size, "%u", (unsigned)value);
    return buffer;
}

static const char* field_s32(char* buffer, size_t size, const void* base,
    size_t offset)
{
    s32 value;

    if (offset == FIELD_NONE)
        return "-";
    memcpy(&value, (const u8*)base + offset, sizeof(value));
    snprintf(buffer, size, "%d", (int)value);
    return buffer;
}

static void log_objects(long frame, u32 game, u32 engine)
{
    static const struct LogTable tables[] = {
        { "player", &g_Player, 1, sizeof(g_Player),
            offsetof(struct PlayerObj, bg_offset),
            offsetof(struct PlayerObj, x_vel), offsetof(struct PlayerObj, y_vel),
            offsetof(struct PlayerObj, unk40), offsetof(struct PlayerObj, unk42),
            offsetof(struct PlayerObj, animation_step),
            offsetof(struct PlayerObj, previous_animation_index) },
        { "entity", &g_Entity, 1, sizeof(g_Entity),
            offsetof(struct PlayerObj, bg_offset),
            offsetof(struct PlayerObj, x_vel), offsetof(struct PlayerObj, y_vel),
            offsetof(struct PlayerObj, unk40), offsetof(struct PlayerObj, unk42),
            offsetof(struct PlayerObj, animation_step),
            offsetof(struct PlayerObj, previous_animation_index) },
        { "main", main_objects, COUNT(main_objects), sizeof(main_objects[0]),
            offsetof(struct MainObj, bg_offset),
            offsetof(struct MainObj, unk20), offsetof(struct MainObj, unk24),
            offsetof(struct MainObj, unk40), offsetof(struct MainObj, unk42),
            offsetof(struct MainObj, animation_step),
            offsetof(struct MainObj, previous_animation_index) },
        { "visual", visual_objects, COUNT(visual_objects), sizeof(visual_objects[0]),
            offsetof(struct VisualObj, bg_offset),
            offsetof(struct VisualObj, x_vel), offsetof(struct VisualObj, y_vel),
            offsetof(struct VisualObj, unk40), offsetof(struct VisualObj, unk42),
            offsetof(struct VisualObj, animation_step),
            offsetof(struct VisualObj, previous_animation_index) },
        { "shot", shot_objects, COUNT(shot_objects), sizeof(shot_objects[0]),
            offsetof(struct ShotObj, bg_offset),
            offsetof(struct ShotObj, x_vel), offsetof(struct ShotObj, y_vel),
            offsetof(struct ShotObj, unk40), offsetof(struct ShotObj, unk42),
            offsetof(struct ShotObj, animation_step),
            offsetof(struct ShotObj, previous_animation_index) },
        { "weapon", weapon_objects, COUNT(weapon_objects), sizeof(weapon_objects[0]),
            offsetof(struct WeaponObj, bg_offset),
            offsetof(struct WeaponObj, x_vel), offsetof(struct WeaponObj, y_vel),
            offsetof(struct WeaponObj, unk40), offsetof(struct WeaponObj, unk42),
            offsetof(struct WeaponObj, animation_step),
            offsetof(struct WeaponObj, previous_animation_index) },
        { "unk", unk_objects, COUNT(unk_objects), sizeof(unk_objects[0]),
            offsetof(struct UnkObj, bg_offset),
            offsetof(struct UnkObj, x_vel), offsetof(struct UnkObj, y_vel),
            offsetof(struct UnkObj, unk40), offsetof(struct UnkObj, unk42),
            offsetof(struct UnkObj, animation_step),
            offsetof(struct UnkObj, previous_animation_index) },
        { "item", item_objects, COUNT(item_objects), sizeof(item_objects[0]),
            offsetof(struct ItemObj, bg_offset),
            offsetof(struct ItemObj, x_vel), offsetof(struct ItemObj, y_vel),
            offsetof(struct ItemObj, unk40), offsetof(struct ItemObj, unk42),
            offsetof(struct ItemObj, animation_step),
            offsetof(struct ItemObj, previous_animation_index) },
        { "misc", misc_objects, COUNT(misc_objects), sizeof(misc_objects[0]),
            offsetof(struct MiscObj, bg_offset),
            offsetof(struct MiscObj, x_vel), offsetof(struct MiscObj, y_vel),
            offsetof(struct MiscObj, unk40), offsetof(struct MiscObj, unk42),
            offsetof(struct MiscObj, animation_step),
            offsetof(struct MiscObj, previous_animation_index) },
        { "quad", g_QuadObjects, COUNT(g_QuadObjects), sizeof(g_QuadObjects[0]),
            offsetof(struct QuadObj, bg_offset),
            FIELD_NONE, FIELD_NONE, FIELD_NONE, FIELD_NONE, FIELD_NONE,
            FIELD_NONE },
        { "layer", layer_objects, COUNT(layer_objects), sizeof(layer_objects[0]),
            offsetof(struct LayerObj, bg_offset),
            FIELD_NONE, FIELD_NONE, FIELD_NONE, FIELD_NONE, FIELD_NONE,
            FIELD_NONE },
        { "effect", effect_objects, COUNT(effect_objects), sizeof(effect_objects[0]),
            FIELD_NONE, FIELD_NONE, FIELD_NONE, FIELD_NONE, FIELD_NONE,
            FIELD_NONE, FIELD_NONE },
    };
    size_t table;
    size_t slot;

    for (table = 0; table < COUNT(tables); table++) {
        for (slot = 0; slot < tables[table].count; slot++) {
            const u8* raw = (const u8*)tables[table].data + slot * tables[table].stride;
            const struct ObjectHeader* object = (const struct ObjectHeader*)raw;
            char bgoff[16], xvel[16], yvel[16], tex[16], clut[16];
            char animstep[16], anim[16];
            int backref = -1;

            if (object->active == 0 && object->on_screen == 0)
                continue;
            if (object->backref != NULL)
                backref = *(const u8*)object->backref;
            fprintf(object_log,
                "%ld\t%08x\t%08x\t%s\t%zu\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
                "%d\t%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\n",
                frame, game, engine, tables[table].name, slot,
                object->active, object->id, object->unk2, object->on_screen,
                object->state, object->unk5, object->unk6, object->unk7,
                object->x_pos.val, object->y_pos.val,
                field_s32(xvel, sizeof(xvel), raw, tables[table].x_vel),
                field_s32(yvel, sizeof(yvel), raw, tables[table].y_vel),
                field_u8(bgoff, sizeof(bgoff), raw, tables[table].bg_offset),
                field_u8(anim, sizeof(anim), raw, tables[table].animation_index),
                field_s32(animstep, sizeof(animstep), raw, tables[table].animation_step),
                field_u16(tex, sizeof(tex), raw, tables[table].texture),
                field_u16(clut, sizeof(clut), raw, tables[table].clut),
                backref);
            if (table == 2 && object->id == 8) {
                const struct MainObj* main = (const struct MainObj*)raw;
                char ext80[32], ext84[32];

                fprintf(extension_log,
                    "%ld\t%08x\t%08x\tmain\t%zu\t%d\t%s\t%s\t%u\t%u\t%u\t%u\t%u\n",
                    frame, game, engine, slot, object->id,
                    main_8_pointer_value(ext80, sizeof(ext80), main->ext.main_8.unk80),
                    main_8_pointer_value(ext84, sizeof(ext84), main->ext.main_8.unk84),
                    main->ext.main_8.unk88, main->ext.main_8.unk89,
                    main->ext.main_8.unk8A, main->ext.main_8.unk8B,
                    main->ext.main_8.unk8C);
            } else if (table == 2 && object->id == 19) {
                const struct MainObj* main = (const struct MainObj*)raw;
                const struct Main19Ext* ext = &main->ext.main_19;
                const u32 ext80 = ext->unk80 | (ext->animation_index << 8) | (ext->unk82 << 16) | (ext->unk83 << 24);
                const u32 ext84 = ext->unk84 | (ext->unk86 << 16);
                fprintf(extension_log,
                    "%ld\t%08x\t%08x\tmain\t%zu\t%d\t%08x\t%08x\t%u\t%u\t%u\t%u\t%u\n",
                    frame, game, engine, slot, object->id, ext80, ext84,
                    ext->unk88 & 0xff, ext->unk88 >> 8,
                    ext->unk8A & 0xff, ext->unk8A >> 8, ext->unk8C);
            }
        }
    }
    for (slot = 0; slot < COUNT(background_objects); slot++) {
        const struct BackgroundObj* object = &background_objects[slot];

        if (object->unk0 == 0 && object->unk3 == 0)
            continue;
        fprintf(object_log,
            "%ld\t%08x\t%08x\tbackground\t%zu\t%d\t%d\t%d\t%d\t%d\t-\t-\t-\t"
            "%d\t%d\t%d\t%d\t-\t-\t-\t-\t-\t-1\n",
            frame, game, engine, slot, object->unk0, object->unk1,
            object->unk2, object->unk3, object->unk4,
            object->x_pos.val, object->y_pos.val,
            object->unk14.val, object->unk18.val);
    }
}

_Static_assert(offsetof(struct EngineObj, unk1F) - offsetof(struct EngineObj, state) == 0x1F, "engine region a");
_Static_assert(offsetof(struct EngineObj, unk37) - offsetof(struct EngineObj, enable_boss) == 0x37 - 0x24, "engine region b");
_Static_assert(offsetof(struct EngineObj, unk60) - offsetof(struct EngineObj, unk40) == 0x60 - 0x40, "engine region c");
_Static_assert(offsetof(struct PlayerObj, unk67) - offsetof(struct PlayerObj, unk5C) == 0x67 - 0x5C, "player region a");
_Static_assert(offsetof(struct PlayerObj, unkC7) - offsetof(struct PlayerObj, unk6C) == 0xC7 - 0x6C, "player region b");
_Static_assert(offsetof(struct PlayerObj, unkE2) - offsetof(struct PlayerObj, unkD4) == 0xE2 - 0xD4, "player region c");

static void write_state_bytes(unsigned offset, const void* address, size_t length)
{
    const u8* bytes = address;
    size_t i;

    fprintf(state_log, "\t%02x:", offset);
    for (i = 0; i < length; i++)
        fprintf(state_log, "%02x", bytes[i]);
}

static void write_player_state(long frame, u32 game, u32 engine,
    const char* table, const struct PlayerObj* player)
{
    fprintf(state_log, "%ld\t%08x\t%08x\t%s\t0", frame, game, engine, table);
    write_state_bytes(0x5C, &player->unk5C, 0x68 - 0x5C);
    write_state_bytes(0x6C, &player->unk6C, 0xC8 - 0x6C);
    write_state_bytes(0xD4, &player->unkD4, 0xE4 - 0xD4);
    fputc('\n', state_log);
}

_Static_assert(sizeof(struct BackgroundObj) == 0x54, "background layout");

static void write_background_state(long frame, u32 game, u32 engine, int slot)
{
    fprintf(state_log, "%ld\t%08x\t%08x\tbackground\t%d", frame, game, engine, slot);
    write_state_bytes(0x00, &background_objects[slot], 0x54);
    write_state_bytes(0x54, NULL, 0);
    write_state_bytes(0x54, NULL, 0);
    fputc('\n', state_log);
}

static void write_engine_state(long frame, u32 game, u32 engine)
{
    fprintf(state_log, "%ld\t%08x\t%08x\tengine\t0", frame, game, engine);
    write_state_bytes(0x00, &engine_obj.state, 0x20);
    write_state_bytes(0x24, &engine_obj.enable_boss, 0x38 - 0x24);
    write_state_bytes(0x40, &engine_obj.unk40, 0x61 - 0x40);
    fputc('\n', state_log);
}

void mmx4_pc_object_log_dump(void)
{
    long frame = mmx4_pc_replay_frame();
    u32 game;
    u32 engine;
    int i;

    log_open();
    if (object_log == NULL || frame < 0)
        return;
    memcpy(&game, &game_info, sizeof(game));
    memcpy(&engine, &engine_obj, sizeof(engine));
    fprintf(frame_log,
        "%ld\t%08x\t%08x\t%d\t%d\t%d\t%d\t%d\t%u\t%u\t%u\t%d\t%d\t%d\t%d\t%d\t%d\t%u\t%u\t%d\t%d\t%d\t%d\t%u\t%u\t%u\n",
        frame, game, engine, engine_obj.state, engine_obj.stage,
        engine_obj.substage, engine_obj.checkpoint, engine_obj.cur_character,
        cur_random, D_80166C08, D_80166C0A, engine_obj.unk46,
        g_Player.x_pos.val, g_Player.y_pos.val,
        background_objects[0].x_pos.val, background_objects[0].y_pos.val,
        D_80141BD8.unk0, D_801406AC, D_8013BD40,
        engine_obj.unk1F, engine_obj.enable_boss, engine_obj.unk1E,
        g_Entity.unkD9, (u8)g_Player.unk5C, mmx4_pc_cd_reads,
        mmx4_pc_cd_read_sample);
    log_objects(frame, game, engine);
    write_engine_state(frame, game, engine);
    write_player_state(frame, game, engine, "player", &g_Player);
    write_player_state(frame, game, engine, "entity", &g_Entity);
    for (i = 0; i < 3; i++)
        write_background_state(frame, game, engine, i);
    fflush(frame_log);
    fflush(state_log);
    fflush(object_log);
    fflush(extension_log);
}

void mmx4_pc_frame_end(void)
{
    const char* stop_after = getenv("MMX4_ORACLE_FRAME_STOP_AFTER");
    long replay_frame = mmx4_pc_replay_frame();
    long capture_frame = replay_frame - 1;

    mmx4_pc_write_replay_frame(capture_frame);
    mmx4_oracle_capture_object_changes(mmx4_pc_frame_number());
    mmx4_pc_object_log_dump();
    if (stop_after != NULL && capture_frame >= strtol(stop_after, NULL, 0)) {
        fprintf(stderr, "MMX4 PC: frame capture stopped after replay frame %ld\n",
            capture_frame);
        fflush(NULL);
        exit(EXIT_SUCCESS);
    }
    if (mmx4_pc_replay_complete() && mmx4_pc_replay_exit_requested()) {
        if (object_log != NULL) {
            fclose(object_log);
            fclose(frame_log);
            fclose(extension_log);
            fclose(state_log);
            object_log = NULL;
            frame_log = NULL;
            extension_log = NULL;
            state_log = NULL;
        }
        fprintf(stderr, "MMX4 PC: replay complete, exiting\n");
        fflush(NULL);
        exit(EXIT_SUCCESS);
    }
}
