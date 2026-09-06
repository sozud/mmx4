#include "common.h"
#include "oracle.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

struct ObjectStep {
    u8 active;
    u8 id;
    u8 state;
    u8 step;
    u8 substep;
};

struct ObjectChange {
    const char* trigger;
    const char* object;
    size_t slot;
    struct ObjectStep old_value;
    struct ObjectStep new_value;
    u8 old_phase;
    u8 phase;
};

struct ObjectTable {
    const char* name;
    const void* data;
    size_t count;
    size_t stride;
};

static struct ObjectChange pending_changes[387];
static size_t pending_change_count;
static unsigned long pending_change_frame;
static unsigned int event_number;
static int manifest_initialized;

static int scene_enabled(u32 game, u32 engine)
{
    const char* scene = getenv("MMX4_ORACLE_SCENE");

    if (scene == NULL || *scene == '\0')
        return game != 0;
    if (!strcmp(scene, "title"))
        return (game & 0xff) == 1;
    if (!strcmp(scene, "character-select"))
        return (engine & 0xff) == 1;
    if (!strcmp(scene, "mission-briefing"))
        return (engine & 0xff) == 3;
    if (!strcmp(scene, "initial-stage"))
        return (engine & 0xff) == 6 && (u8)engine_obj.stage == 0 &&
               (u8)engine_obj.substage == 0;
    return 0;
}

static void write_frame(const char* directory, const char* filename)
{
    RECT rect = { 0, (s16)((SP_DRAW_BUFFER ^ 1) * 240), 320, 240 };
    u16* vram = malloc(320u * 240u * sizeof(*vram));
    u8* pixels = malloc(320u * 240u * 3u);
    char path[1024];
    FILE* image;
    size_t i;

    if (vram == NULL || pixels == NULL)
        abort();
    DrawSync(0);
    StoreImage(&rect, (u_long*)vram);
    DrawSync(0);
    for (i = 0; i < 320u * 240u; i++) {
        u16 pixel = vram[i];
        pixels[i * 3] = (u8)((pixel & 0x1f) << 3);
        pixels[i * 3 + 1] = (u8)(((pixel >> 5) & 0x1f) << 3);
        pixels[i * 3 + 2] = (u8)(((pixel >> 10) & 0x1f) << 3);
    }
    free(vram);
    snprintf(path, sizeof(path), "%s/%s", directory, filename);
    image = fopen(path, "wb");
    if (image == NULL) {
        perror(path);
        exit(EXIT_FAILURE);
    }
    fprintf(image, "P6\n320 240\n255\n");
    fwrite(pixels, 1, 320u * 240u * 3u, image);
    fclose(image);
    free(pixels);
}

static void write_event(const char* directory, unsigned long frame,
    const struct ObjectChange* changes, size_t change_count)
{
    char filename[64];
    char path[1024];
    FILE* manifest;
    size_t i;

    if (mkdir(directory, 0777) != 0 && errno != EEXIST) {
        perror(directory);
        exit(EXIT_FAILURE);
    }
    snprintf(filename, sizeof(filename), "change_%04u_f%06lu.ppm",
        event_number, frame);
    write_frame(directory, filename);
    snprintf(path, sizeof(path), "%s/manifest.tsv", directory);
    manifest = fopen(path, manifest_initialized ? "a" : "w");
    if (manifest == NULL) {
        perror(path);
        exit(EXIT_FAILURE);
    }
    if (!manifest_initialized) {
        fprintf(manifest,
            "event\tframe\ttrigger\tobject\tslot\told_active\tactive\t"
            "old_id\tid\told_state\told_step\told_substep\tstate\t"
            "step\tsubstep\told_phase\tphase\tfilename\n");
    }
    for (i = 0; i < change_count; i++) {
        const struct ObjectChange* change = &changes[i];
        fprintf(manifest,
            "%u\t%lu\t%s\t%s\t%zu\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t"
            "%u\t%u\t%u\t%u\t%u\t%s\n",
            event_number, frame, change->trigger, change->object,
            change->slot, change->old_value.active,
            change->new_value.active, change->old_value.id,
            change->new_value.id, change->old_value.state,
            change->old_value.step, change->old_value.substep,
            change->new_value.state, change->new_value.step,
            change->new_value.substep, change->old_phase, change->phase,
            filename);
    }
    fclose(manifest);
    manifest_initialized = 1;
    event_number++;
}

void mmx4_oracle_capture_object_changes(unsigned long frame)
{
    static const struct ObjectTable tables[] = {
        { "player", &g_Player, 1, sizeof(g_Player) },
        { "entity", &g_Entity, 1, sizeof(g_Entity) },
        { "main", main_objects, COUNT(main_objects), sizeof(main_objects[0]) },
        { "visual", visual_objects, COUNT(visual_objects), sizeof(visual_objects[0]) },
        { "shot", shot_objects, COUNT(shot_objects), sizeof(shot_objects[0]) },
        { "weapon", weapon_objects, COUNT(weapon_objects), sizeof(weapon_objects[0]) },
        { "unk", unk_objects, COUNT(unk_objects), sizeof(unk_objects[0]) },
        { "item", item_objects, COUNT(item_objects), sizeof(item_objects[0]) },
        { "misc", misc_objects, COUNT(misc_objects), sizeof(misc_objects[0]) },
        { "quad", g_QuadObjects, COUNT(g_QuadObjects), sizeof(g_QuadObjects[0]) },
        { "effect", effect_objects, COUNT(effect_objects), sizeof(effect_objects[0]) },
        { "background", background_objects, COUNT(background_objects), sizeof(background_objects[0]) },
    };
    static struct ObjectStep previous[384];
    static u32 previous_game;
    static u32 previous_engine;
    static u16 previous_scene;
    static int have_previous;
    struct ObjectStep current[COUNT(previous)];
    struct ObjectChange changes[COUNT(previous) + 3];
    size_t table;
    size_t slot;
    size_t index = 0;
    size_t change_count = 0;
    u32 game;
    u32 engine;
    u16 scene;
    const char* directory = getenv("MMX4_ORACLE_OBJECT_CHANGE_DIR");

    if (directory == NULL || *directory == '\0')
        return;
    for (table = 0; table < COUNT(tables); table++) {
        for (slot = 0; slot < tables[table].count; slot++, index++) {
            const struct BaseObj* object = (const struct BaseObj*)(
                (const u8*)tables[table].data + slot * tables[table].stride);
            struct ObjectStep value = {
                (u8)object->active, (u8)object->id, (u8)object->state,
                (u8)object->unk5, (u8)object->unk6,
            };
            struct ObjectStep old = previous[index];

            if (index >= COUNT(current))
                abort();
            current[index] = value;
            if (!have_previous)
                continue;
            if (!old.active && value.active) {
                changes[change_count++] = (struct ObjectChange){
                    "created", tables[table].name, slot, old, value, 0, 0 };
            } else if (old.active && !value.active) {
                changes[change_count++] = (struct ObjectChange){
                    "destroyed", tables[table].name, slot, old, value, 0, 0 };
            } else if (old.active && value.active && old.id != value.id) {
                changes[change_count++] = (struct ObjectChange){
                    "replaced", tables[table].name, slot, old, value, 0, 0 };
            } else if (value.active &&
                (old.state != value.state || old.step != value.step ||
                 old.substep != value.substep)) {
                changes[change_count++] = (struct ObjectChange){
                    "control", tables[table].name, slot, old, value, 0, 0 };
            }
        }
    }
    memcpy(&game, &game_info, sizeof(game));
    memcpy(&engine, &engine_obj, sizeof(engine));
    scene = (u8)engine_obj.stage | ((u16)(u8)engine_obj.substage << 8);
    if (have_previous && game != previous_game) {
        struct ObjectStep old = { 1, 0, (u8)previous_game,
            (u8)(previous_game >> 8), (u8)(previous_game >> 16) };
        struct ObjectStep value = { 1, 0, (u8)game,
            (u8)(game >> 8), (u8)(game >> 16) };
        changes[change_count++] = (struct ObjectChange){
            "game_info", "game_info", 0, old, value,
            (u8)(previous_game >> 24), (u8)(game >> 24) };
    }
    if (have_previous && engine != previous_engine) {
        struct ObjectStep old = { 1, 0, (u8)previous_engine,
            (u8)(previous_engine >> 8), (u8)(previous_engine >> 16) };
        struct ObjectStep value = { 1, 0, (u8)engine,
            (u8)(engine >> 8), (u8)(engine >> 16) };
        changes[change_count++] = (struct ObjectChange){
            "engine_info", "engine_info", 0, old, value,
            (u8)(previous_engine >> 24), (u8)(engine >> 24) };
    }
    if (have_previous && scene != previous_scene) {
        struct ObjectStep old = { 1, 0, (u8)previous_scene,
            (u8)(previous_scene >> 8), 0 };
        struct ObjectStep value = { 1, 0, (u8)scene,
            (u8)(scene >> 8), 0 };
        changes[change_count++] = (struct ObjectChange){
            "engine_scene", "engine_scene", 0, old, value, 0, 0 };
    }
    memcpy(previous, current, index * sizeof(current[0]));
    previous_game = game;
    previous_engine = engine;
    previous_scene = scene;
    if (!have_previous) {
        have_previous = 1;
        return;
    }
    if (!scene_enabled(game, engine))
        change_count = 0;
    if (pending_change_count != 0)
        write_event(directory, pending_change_frame, pending_changes,
            pending_change_count);
    pending_change_count = change_count;
    pending_change_frame = frame;
    if (change_count != 0)
        memcpy(pending_changes, changes, change_count * sizeof(changes[0]));
}
