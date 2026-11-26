#include "test_runtime.h"
#include "main/quads/quad_13_null.h"
#include "saturn/player_resources.h"

void func_800D1B44(struct MiscObj* self);
void func_8002F87C(struct EngineObj* arg0);

static struct QuadObj quad;
static struct MiscObj actor;
static s32 frame_banks[2] = { 8, 0x40 };
static u16 palette[0x240];
static u32 graphics_offsets[2] = { 0x1234, 0x5678 };

static void reset(void)
{
    memset(&quad, 0, sizeof(quad));
    memset(&actor, 0, sizeof(actor));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    memset(palette, 0x5A, sizeof(palette));
    saturn_stage_frame_banks = frame_banks;
    saturn_player_palette_destination = palette;
    saturn_stage_graphics_offsets_pointer = graphics_offsets;
    need_palette_load = 0;
}

static void quad_first_frame(void)
{
    engine_obj.unk1F = 5;
    quad_null_update(&quad);
}
static void actor_animated(void)
{
    actor.unk2 = 2;
    func_800D1B44(&actor);
}
static void actor_still(void)
{
    func_800D1B44(&actor);
}
static void curtain_wait(void)
{
    engine_obj.unk4 = 3;
    background_objects[1].y_pos.val = 100 << 16;
    func_8002F87C(&engine_obj);
}
static void curtain_opened(void)
{
    background_objects[1].y_pos.val = 2 << 16;
    background_objects[2].y_pos.val = 238 << 16;
    func_8002F87C(&engine_obj);
}

static void (*const scene_cases[])(void) = {
    quad_first_frame,
    actor_animated,
    actor_still,
    curtain_wait,
    curtain_opened,
};

#define WORDS 8
static const u32 scene_expected[][WORDS] = {
#include "game_scene_objects_expected.inc"
};

static u32 scene_run(u32 row)
{
    u32 observed[WORDS];
    reset();
    scene_cases[row]();
    observed[0] = (u8)quad.active | (u32)quad.state << 8 | (u32)quad.on_screen << 16 | (u32)(u8)engine_obj.unk1F << 24;
    observed[1] = (u16)quad.unk34 | (u32)quad.unk36 << 16;
    observed[2] = quad.vertices[2].x.val ^ quad.vertices[2].y.val;
    observed[3] = actor.state | (u32)actor.unk16 << 8 | (u32)actor.animation_step.fields.frame_index << 16
        | (u32)(u8)actor.x_pos.i.hi << 24;
    observed[4] = (u16)actor.unk40 | (u32)actor.unk42 << 16;
    observed[5] = (actor.unk3C ? (u32)((u8*)actor.unk3C - (u8*)frame_banks) : 0) | (u32)need_palette_load << 24;
    observed[6] = palette[0x200] | (u32)palette[0x23F] << 16;
    observed[7] = (u16)background_objects[1].y_pos.i.hi | (u32)(u16)background_objects[2].y_pos.i.hi << 16
        ^ (u32)(u8)engine_obj.unk4 << 8 ^ (u32)(u8)engine_obj.unk2 << 24;
    return c_test_observe(0, row, observed, scene_expected[row], WORDS);
}

const struct CTestGroup c_test_groups[] = {
    { "saturn_scene_objects", 0, 0, COUNT(scene_cases), scene_run },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(scene_cases);
