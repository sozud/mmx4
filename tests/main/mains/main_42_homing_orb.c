#include "test_runtime.h"
#include "main/mains/main_42_homing_orb.h"
#include "main/55C4.h"
#include "support/state_cases.h"
void homing_orb_leave(struct MainObj* arg0);
void homing_orb_start_idle(struct MainObj* arg0);
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
static const u32 homing_orb_lunge_pool_cases_expected[] = { 0x1005903u, 0x100B402u, 0x4100B402u, 0x1000004u, 0x41000004u };

#define HO(step) (state_reset(step, 0, 0), so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60)
static void ho_leave(void)
{
    HO(5);
    so.x_speed = 0x20000;
    homing_orb_leave(&so);
}
static void ho_idle(void)
{
    HO(1);
    homing_orb_start_idle(&so);
}

static void (*const homing_orb_states_cases[])(void) = {
    ho_leave,
    ho_idle,
};
static const u32 homing_orb_states_expected[] = { 5u, 0u, 0x820000u, 0x20000u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_homing_orb_states(u32 row)
{
    return state_run(homing_orb_states_cases[row], row, &homing_orb_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "homing_orb_states", 0, 0, COUNT(homing_orb_states_cases), test_homing_orb_states },
    { "homing_orb_lunge_pool", NULL, homing_orb_lunge_pool_cases_expected, COUNT(homing_orb_lunge_pool_cases_expected), lunge_case },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(homing_orb_states_cases) + COUNT(homing_orb_lunge_pool_cases_expected);
