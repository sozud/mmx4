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
    g_Player.spike_immune = 1;
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
    assert(obj.animation_step.packed == 0x14010004);
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
        expected.animation_step.packed = 0x1C010003;
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
const struct CTestGroup c_test_groups[] = { { "shipped_arena_edges_waterline_and_upward_or_downward_motion", NULL, NULL, 90, falling } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 90;
