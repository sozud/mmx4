#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/items/item_20_gravity_switch.h"

void func_800C4D20(struct ItemObj*);
#ifndef VERSION_DEMO
void func_800C5210(struct ItemObj*);
#endif
void gravity_switch_flip_objects(void);
#define gs state_room.item
static u32 gs_archive[16], gs_meta[64];
#define GS(sub)                                                                                                   \
    (state_reset(0, 0, 0), memset(&engine_obj, 0, sizeof(engine_obj)), engine_obj.stage = 6, engine_obj.substage = 1, \
        memset(weapon_objects, 0, sizeof(weapon_objects)), memset(main_objects, 0, sizeof(main_objects)),             \
        g_Player.unk68 = NULL, ((struct MainObj*)&g_Player)->hurt_box = NULL, g_Player.invincibility_timer = 0, TEST_MENU_FRAMES = (u8*)gs_archive, D_801406A8 = gs_meta, \
        gs.active = 0x41, gs.id = 0x14, gs.unk2 = sub, gs.x_pos.i.hi = 0x290, gs.y_pos.i.hi = 0x3A4)
#define GSX() (state_extra = C_TEST_PSX_FACING(gs.unk15) | (u32)(u16)background_objects[0].unk22 << 8 ^ (u32)(u16)background_objects[1].unk42 << 16 ^ (u32)(u16)background_objects[2].unk42, engine_obj.stage = engine_obj.substage = 0)
static void gs_init_right(void) { GS(0x1A), func_800C4D20(&gs), gs.unk42 = 0, gs.sprite_frames = NULL, GSX(); }
static void gs_init_left(void) { GS(DEMO_ALT(0x22, 0x02)), func_800C4D20(&gs), gs.unk42 = 0, gs.sprite_frames = NULL, GSX(); }
static void gs_wait(u8 touch)
{
    GS(0), gs.state = 1, gs.unk50 = (const u8*)&state_hit_box;
    if (touch)
        ((struct MainObj*)&g_Player)->hurt_box = &state_hit_box, g_Player.x_pos = gs.x_pos, g_Player.y_pos = gs.y_pos;
    gravity_switch_update(&gs), GSX();
    ((struct MainObj*)&g_Player)->hurt_box = NULL;
}
static void gs_wait_idle(void) { gs_wait(0); }
static void gs_wait_touched(void) { gs_wait(1); }
static void gs_flip_objects(void)
{
    GS(0);
    main_objects[1].active = misc_objects[1].active = weapon_objects[1].active = shot_objects[1].active = visual_objects[1].active = 1;
    main_objects[1].y_pos.val = misc_objects[1].y_pos.val = weapon_objects[1].y_pos.val = shot_objects[1].y_pos.val = visual_objects[1].y_pos.val = 0x1000000;
    main_objects[1].unk1C.val = misc_objects[1].unk1C.val = weapon_objects[1].unk1C.val = shot_objects[1].unk1C.val = visual_objects[1].unk1C.val = 0x2000000;
    main_objects[0].y_pos.val = misc_objects[0].y_pos.val = 0x3000000;
    gravity_switch_flip_objects();
    assert(main_objects[0].y_pos.val == 0x3000000 && misc_objects[0].y_pos.val == 0x3000000);
    assert(main_objects[1].y_pos.val == 0x7000000 && misc_objects[1].y_pos.val == 0x7000000 && weapon_objects[1].y_pos.val == 0x7000000 && shot_objects[1].y_pos.val == 0x7000000 && visual_objects[1].y_pos.val == 0x7000000);
#define FLIPPED_PREVIOUS DEMO_ALT(0x6000000, 0x2000000)
    assert(main_objects[1].unk1C.val == FLIPPED_PREVIOUS && misc_objects[1].unk1C.val == FLIPPED_PREVIOUS && weapon_objects[1].unk1C.val == FLIPPED_PREVIOUS && shot_objects[1].unk1C.val == FLIPPED_PREVIOUS && visual_objects[1].unk1C.val == FLIPPED_PREVIOUS);
#undef FLIPPED_PREVIOUS
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(main_objects, 0, sizeof(main_objects));
    GSX();
}
#ifndef VERSION_DEMO
static void gs_camera(u8 gravity) { GS(0x30), engine_obj.character_state.bytes[0] = gravity, background_objects[1].unk42 = 0x400, background_objects[2].unk42 = 0x400, func_800C5210(&gs), GSX(); }
static void gs_camera_flipped(void) { gs_camera(1); }
static void gs_camera_normal(void) { gs_camera(0); }
#endif

static void (*const gravity_switch_states_cases[])(void) = {
    gs_init_right,
    gs_init_left,
    gs_wait_idle,
    gs_wait_touched,
    gs_flip_objects,
#ifndef VERSION_DEMO
    gs_camera_flipped,
    gs_camera_normal,
#endif
};
static const u32 gravity_switch_states_expected[] = {
    0x1u, 0x401A41u, 0x2900000u, 0x3A40000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x40u, 0x0u,
    0x1u, DEMO_ALT(0x2241u, 0x0241u), 0x2900000u, 0x3A40000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x1u, 0x41u, 0x2900000u, 0x3A40000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x101u, 0x41u, 0x2900000u, 0x3A40000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x0u, 0x41u, 0x2900000u, 0x3A40000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
#ifndef VERSION_DEMO
    0x0u, 0x3041u, 0x2900000u, 0x3A40000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x48404C0u, 0x0u,
    0x0u, 0x3041u, 0x2900000u, 0x3A40000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x3840340u, 0x0u,
#endif
};

static u32 test_gravity_switch_states(u32 row)
{
    return object_run(gravity_switch_states_cases[row], row, &gravity_switch_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "gravity_switch_states", 0, 0, COUNT(gravity_switch_states_cases), test_gravity_switch_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(gravity_switch_states_cases);
