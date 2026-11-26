#include "test_runtime.h"
#include "main/effects/effect_32_proximity_door.h"

static u32 door_case(u32 mode)
{
    struct EffectObj obj, expected;
    struct PlayerObj player_before;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 1;
    obj.id = 32;
    obj.state = 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.ext.effect_32.unk15 = mode == 2 || mode == 4 || mode == 5 ? 1 : -1;
    obj.ext.effect_32.palette_source.bytes = tile_anim_trigger_scripts[1];
    obj.ext.effect_32.palette.fields.timer = 17;
    obj.ext.effect_32.palette.fields.unk1 = 0xA5;
    obj.ext.effect_32.palette.fields.step = mode == 3 || mode == 5 ? 1 : 0;
    obj.ext.effect_32.palette.fields.id = 6;
    g_Player.x_pos.i.hi = mode == 0 ? 53 : mode == 1 ? 147
        : mode == 4 || mode == 5                     ? 148
        : mode == 6                                  ? 52
                                                     : 100;
    expected = obj;
    player_before = g_Player;
    if (mode == 0 || mode == 1 || mode == 4) {
        u32 close = mode == 4;
        expected.ext.effect_32.palette_source.bytes = tile_anim_trigger_scripts[close];
        expected.ext.effect_32.palette.fields.timer = 2;
        expected.ext.effect_32.palette.fields.unk1 = 0;
        expected.ext.effect_32.palette.fields.step = 1;
        expected.ext.effect_32.palette.fields.id = close ? 8 : 0;
        expected.ext.effect_32.unk15 = close ? -1 : 1;
    }
    proximity_door_check_player(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    return (u8)obj.ext.effect_32.unk15 | ((u32)obj.ext.effect_32.palette.fields.id << 8) | ((u32)obj.ext.effect_32.palette.fields.timer << 16);
}
static const u32 proximity_door_real_scripts_cases_expected[] = { 0x20001u, 0x20001u, 0x110601u, 0x1106FFu, 0x208FFu, 0x110601u, 0x1106FFu };


#include "support/state_cases.h"
#include "support/tile_fixture.h"
#define ae state_room.effect
#define AX32 ae.ext.effect_32
#define DOOR(mv, tm, setup) (state_reset(0, 0, 0), tile_fixture_begin(), memset(&g_Player, 0, sizeof(g_Player)), g_Player.x_pos.i.hi = mv ? 0x80 : 0x400, ae.active = 1, ae.state = 1, ae.x_pos.i.hi = 0x80, ae.y_pos.i.hi = 0x60, AX32.unk15 = mv, AX32.palette_source.bytes = tile_anim_trigger_scripts[0], AX32.palette.fields.timer = tm, AX32.palette.fields.step = mv, setup, proximity_door_update(&ae), state_extra = (u8)AX32.palette.fields.timer | (u32)AX32.palette.fields.id << 8 | (u32)(u8)AX32.palette.fields.step << 16 | (u32)(AX32.palette_source.bytes - tile_anim_trigger_scripts[0]) << 24, state_room.shot.x_vel.val = tile_fixture_end())
static void door_idle(void) { DOOR(0, 0, 0); }
static void door_idle_far(void) { DOOR(0, 0, ae.x_pos.i.hi = 0x1000); }
static void door_waiting(void) { DOOR(1, 3, 0); }
static void door_next_frame(void) { DOOR(1, 1, 0); }

static void (*const door_cases[])(void) = {
    door_idle,
    door_idle_far,
    door_waiting,
    door_next_frame,
};
static const u32 door_expected[] = {
    0x1u, 0x1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u,
    0u, 0u, 0x10000000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u,
    0x1u, 0x10001u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x10002u, 0u,
    0x1u, 0x10001u, 0x800000u, 0x600000u, 0x3510000u | TILE_FIXTURE_WRITES(7, 1), 0u, 0u, 0x50000u, 0x4010102u, 0u,
};
static u32 test_door(u32 row)
{
    return object_run(door_cases[row], row, &door_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "proximity_door_steps", 0, 0, COUNT(door_cases), test_door },
    { "proximity_door_real_scripts", NULL, proximity_door_real_scripts_cases_expected, COUNT(proximity_door_real_scripts_cases_expected), door_case },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(proximity_door_real_scripts_cases_expected) + COUNT(door_cases);
