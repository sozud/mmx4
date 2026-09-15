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
    if (object_log == NULL || frame_log == NULL) {
        perror(directory);
        exit(EXIT_FAILURE);
    }
    fprintf(object_log,
        "frame\tgame\tengine\ttable\tslot\tactive\tid\tsubtype\ton_screen\t"
        "state\tstep\tsubstep\tunk7\tx\ty\txvel\tyvel\tbgoff\tanim\t"
        "animstep\ttex\tclut\tbackref\n");
    fprintf(frame_log,
        "frame\tgame\tengine\tstate\tstage\tsubstage\tcheckpoint\tcharacter\t"
        "rng\tpad\tpad_prev\thealth\tplayer_x\tplayer_y\tbg0_x\tbg0_y\n");
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

void mmx4_pc_object_log_dump(void)
{
    long frame = mmx4_pc_replay_frame();
    u32 game;
    u32 engine;

    log_open();
    if (object_log == NULL || frame < 0)
        return;
    memcpy(&game, &game_info, sizeof(game));
    memcpy(&engine, &engine_obj, sizeof(engine));
    fprintf(frame_log,
        "%ld\t%08x\t%08x\t%d\t%d\t%d\t%d\t%d\t%u\t%u\t%u\t%d\t%d\t%d\t%d\t%d\n",
        frame, game, engine, engine_obj.state, engine_obj.stage,
        engine_obj.substage, engine_obj.checkpoint, engine_obj.cur_character,
        cur_random, D_80166C08, D_80166C0A, engine_obj.unk46,
        g_Player.x_pos.val, g_Player.y_pos.val,
        background_objects[0].x_pos.val, background_objects[0].y_pos.val);
    log_objects(frame, game, engine);
    fflush(frame_log);
    fflush(object_log);
}

void mmx4_pc_frame_end(void)
{
    mmx4_oracle_capture_object_changes(mmx4_pc_frame_number());
    mmx4_pc_object_log_dump();
    if (mmx4_pc_replay_complete() && mmx4_pc_replay_exit_requested()) {
        if (object_log != NULL) {
            fclose(object_log);
            fclose(frame_log);
            object_log = NULL;
            frame_log = NULL;
        }
        fprintf(stderr, "MMX4 PC: replay complete, exiting\n");
        fflush(NULL);
        exit(EXIT_SUCCESS);
    }
}
