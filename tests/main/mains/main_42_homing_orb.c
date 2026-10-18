#include "test_runtime.h"
#include "main/mains/main_42_homing_orb.h"
#include "main/55C4.h"
extern union AnimationStep* homing_orb_animations[7];

static u32 lunge_case(u32 mode)
{
    struct MainObj obj, before;
    struct MiscObj pool_before[64];
    struct PlayerObj player_before = g_Player;
    u32 i, leaving = mode >= 3, free_slot = mode == 2 || mode == 4;
    memset(&obj, 0, sizeof(obj));
    memset(misc_objects, 0, sizeof(misc_objects));
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = 1;
        misc_objects[i].id = 0x27;
        misc_objects[i].state = 0x28;
    }
    if (free_slot)
        misc_objects[63].active = 0;
    obj.active = 0x41;
    obj.id = 42;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 2;
    obj.unk7C = mode == 0 ? 91 : 2;
    obj.ext.main_42.background_relative = leaving ? 5 : 4;
    obj.ext.main_42.unk84 = &misc_objects[17];
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_accel = 65536;
    obj.gravity = 8192;
    obj.animation_table = (const u8* const*)homing_orb_animations;
    set_animation(&obj, 0);
    before = obj;
    memcpy(pool_before, misc_objects, sizeof(pool_before));
    homing_orb_lunge(&obj);
    if (mode == 0) {
        before.unk7C = 89;
        before.x_accel = -65536;
        before.gravity = -8192;
        before.x_speed = 65536;
        before.y_speed = 8192;
        before.animation_step.fields.duration = 2;
    } else {
        before.unk5 = leaving ? 4 : 2;
        before.unk7C = leaving ? 0 : 180;
        before.unk17 = leaving ? 3 : 0;
        before.previous_animation_index = 0xFF;
        before.animation_cursor = (const u8*)homing_orb_animations[before.unk17];
        before.animation_step = *homing_orb_animations[before.unk17];
        before.animation_step.fields.duration--;
        if (leaving) {
            before.ext.main_42.unk84 = NULL;
            before.x_speed = -65536;
            before.y_speed = 2 * 65536 - 8192;
            before.y_pos.val -= 2 * 65536;
        } else
            before.x_accel = before.gravity = before.x_speed = before.y_speed = 0;
        if (free_slot) {
            pool_before[63].active = 0x41;
            pool_before[63].id = 14;
            pool_before[63].ext.pointer.unk50 = &obj;
            pool_before[63].x_pos.val = obj.x_pos.val;
            pool_before[63].y_pos.val = before.y_pos.val + (leaving ? 2 * 65536 : 0);
            pool_before[63].unk2 = 0;
            before.ext.main_42.unk84 = &misc_objects[63];
        }
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.unk5 | ((u32)(u16)obj.unk7C << 8) | ((u32)misc_objects[63].active << 24);
}
#define CASE(m)                \
    static u32 lunge_##m(void) \
    {                          \
        return lunge_case(m);  \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
#define ENTRY(m) lunge_##m,
static const CTestCase homing_orb_lunge_pool_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) };
static const u32 homing_orb_lunge_pool_cases_expected[] = { 0x1005903u, 0x100B402u, 0x4100B402u, 0x1000004u, 0x41000004u };
#undef CASE
#undef ENTRY

const struct CTestGroup c_test_groups[] = {
    { "homing_orb_lunge_pool", homing_orb_lunge_pool_cases, homing_orb_lunge_pool_cases_expected, COUNT(homing_orb_lunge_pool_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(homing_orb_lunge_pool_cases);
