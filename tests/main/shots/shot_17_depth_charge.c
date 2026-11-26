#include "test_runtime.h"
#include "main/55C4.h"
void depth_charge_fall(struct ShotObj*);
extern union AnimationStep* thorn_trap_animations[21];
extern u8 depth_charge_sink_box[4];
static const s16 positions[5] = { 0x171F, 0x1720, 0x1721, 0x181F, 0x1820 };
static u32 falling(u32 row)
{
    struct ShotObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 pos = row % 5, rising = row / 5 % 2, level = row / 10 % 3, layer = row / 30;
    s32 surface = 200 + 172, y = surface + (s32)level - 1;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    background_objects[layer].y_pos.i.hi = 200;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    SPIKE_IMMUNE_SET(g_Player, 1);
    player_before = g_Player;
    obj.active = 0x41;
    obj.id = 17;
    obj.unk2 = 1;
    obj.state = 1;
    obj.unk5 = 3;
    obj.bg_offset = layer;
    obj.unk60 = 3;
    obj.unk50.data = depth_charge_sink_box;
    obj.x_pos.val = positions[pos] * 65536 + 0x1234;
    obj.x_vel.val = 0;
    obj.y_vel.val = rising ? 65536 : -65536;
    obj.y_pos.val = y * 65536 + 0x5678 + obj.y_vel.val;
    obj.animation_table = (u32**)thorn_trap_animations;
    set_animation(&obj, 5);
    assert(obj.animation_step.packed == C_TEST_STEP(0x14010004));
    expected = obj;
    expected.y_pos.val -= obj.y_vel.val;
    expected.animation_step.fields.duration--;
    if (pos < 2 || pos == 4) {
        expected.x_vel.val = 0;
        expected.y_vel.val = -2 * 65536;
    }
    if (level && (!rising || pos < 2 || pos == 4)) {
        expected.unk17 = 6;
        expected.previous_animation_index = 255;
        expected.animation_cursor = (u32*)thorn_trap_animations[6];
        expected.animation_step.packed = C_TEST_STEP(0x1C010003);
        expected.unk60 = 4;
        expected.unk50.data = depth_charge_sink_box;
        expected.unk5 = 4;
        expected.y_pos.val = surface * 65536;
        expected.y_vel.val = 0x8000;
    }
    depth_charge_fall(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    return 1;
}
static u32 charge_paths(u32 row);
const struct CTestGroup c_test_groups[] = {
    { "shipped_arena_edges_waterline_and_upward_or_downward_motion", NULL, NULL, 90, falling },
    { "charge_paths", 0, 0, 10, charge_paths },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 90 + 10;

#include "support/state_cases.h"
void func_8009C638(struct ShotObj*);
void func_8009C784(struct ShotObj*);
void depth_charge_sink(struct ShotObj*);
void depth_charge_main(struct ShotObj*);
static u32 charge_paths(u32 row)
{
    struct ShotObj obj;
    struct MainObj parent;
    memset(&obj, 0, sizeof(obj));
    memset(&parent, 0, sizeof(parent));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    ANIMATED_OBJECT(&parent)->animation_table = (u32**)thorn_trap_animations;
    obj.active = 0x41;
    obj.id = 17;
    obj.state = 1;
    obj.unk7C = (struct WeaponObj*)&parent;
    obj.x_pos.i.hi = 0x1780;
    obj.y_pos.i.hi = 0x100;
    obj.animation_table = (u32**)thorn_trap_animations;
    set_animation(&obj, 5);
    obj.animation_step.fields.duration = 2;
    obj.animation_step.fields.relative_step = 1;
    background_objects[0].x_pos.i.hi = 0x1700;
    background_objects[0].y_pos.i.hi = 0x80;
    g_Player.x_pos.i.hi = 0x1780;
    g_Player.y_pos.i.hi = 0x40;
    if (row <= 1) {
        obj.state = 0;
        obj.unk2 = row == 0;
        obj.unk6 = 4;
        func_8009C638(&obj);
        assert(obj.state == 1 && obj.unk5 == 2 && obj.unk17 == (row == 0 ? 5 : 8));
        assert(obj.unk16 == (row == 0 ? 0x20 : 0x10) && (obj.unk68 != NULL) == (row == 0));
        assert(row == 0 ? obj.x_vel.val != 0 : obj.x_vel.val == 0 && obj.y_vel.val > 0);
        return 1;
    }
    if (row <= 4) {
        obj.unk2 = row != 4;
        obj.x_pos.i.hi = row == 2 ? 0x1700 : row == 3 ? 0x1780 : 0x1830;
        obj.y_pos.i.hi = row == 2 ? 0x100 : 0x80 + 0xAC;
        obj.x_vel.val = 0x10000;
        obj.y_vel.val = -0x8000;
        func_8009C784(&obj);
        if (row == 2) {
            assert(obj.x_vel.val == 0 && obj.y_vel.val == -0x20000 && obj.unk5 == 0);
        } else if (row == 3) {
            assert(obj.x_vel.val == 0x10000 && obj.y_vel.val == 0x18000 && obj.unk2C == 0x1000 && obj.unk5 == 1);
        } else {
            assert(obj.x_vel.val == 0x10000 && obj.y_vel.val == -0x8000 && obj.unk5 == 0);
        }
        return 1;
    }
    if (row <= 6) {
        obj.unk5 = 4;
        obj.animation_step.fields.relative_step = row == 6;
        depth_charge_sink(&obj);
        assert(obj.state == (row == 5 ? 2 : 1) && visual_objects[0].active == (row == 5 ? 0x21 : 0));
        return 1;
    }
    obj.unk5 = 2;
    obj.unk5C = 1;
    if (row == 7)
        state_hit(MAIN_OBJECT(&obj), 0, 0, 3);
    if (row == 9)
        obj.x_pos.i.hi = 0x400;
    depth_charge_main(&obj);
    assert(obj.active == (row == 9 ? 0 : 0x41) && obj.state == (row == 7 ? 2 : row == 9 ? 0 : 1));
    assert(row != 8 || obj.on_screen == 1);
    return 1;
}
