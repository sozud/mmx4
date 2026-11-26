#include "test_runtime.h"
#include "main/collision_bounds.h"
#include "main/55C4.h"
void trident_shot_flash(struct ShotObj*);
extern union AnimationStep* trident_mech_animations[29];
extern u8 trident_shot_flash_box[4];
static u32 flash(u32 row)
{
    struct ShotObj obj, expected;
    struct MainObj owner, owner_before;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 live = row % 2, expired = row / 2 % 2, outside = row / 4 % 2, face = row / 8, i;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    owner.active = 0x41;
    owner.id = 16;
    owner.state = 1;
    owner.ext.main_16.shot_09_active = live;
    owner_before = owner;
    SPIKE_IMMUNE_SET(g_Player, 1);
    player_before = g_Player;
    obj.active = 0x41;
    obj.id = 9;
    obj.state = 1;
    obj.on_screen = 1;
    obj.unk15 = face ? PLAYER_FACING_RIGHT : 0;
    obj.unk50.data = obj.unk54 = trident_shot_flash_box;
    obj.unk58.data = (const u8*)D_801060F0;
    obj.unk5C = 1;
    obj.unk60 = 3;
    obj.unk7C = (struct WeaponObj*)&owner.ext.main_16.shot_09_active;
    obj.unk84.value = expired ? 1 : 30;
    obj.x_pos.val = (outside ? 400 : 160) * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.animation_table = (u32**)trident_mech_animations;
    set_animation(&obj, 5);
    assert(obj.animation_step.packed == C_TEST_STEP(0x04010001));
    expected = obj;
    expected.animation_cursor++;
    expected.animation_step.packed = C_TEST_STEP(0x08010001);
    expected.unk84.value--;
    if (!live || expired || outside)
        expected.state = 2;
    trident_shot_flash(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_before, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    for (i = 0; i < 16; i++)
        assert(weapon_objects[i].active == 0);
    return 1;
}

#include "main/shots/shot_09_trident_shot.h"
#include "support/state_cases.h"
#define ss state_room.shot
#define TRI(st, setup) (state_reset(0, 0, 0), memset(&g_Player, 0, sizeof(g_Player)), memset(&engine_obj, 0, sizeof(engine_obj)), g_Player.x_pos.i.hi = 0x400, ss.active = 0x41, ss.state = st, ss.unk2 = 1, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60, ss.x_vel.val = 0x10000, setup, trident_shot_update(&ss))
static void tri_start_left(void)
{
    TRI(3, 0);
}
static void tri_start_right(void) { TRI(3, ss.unk15 = PLAYER_FACING_RIGHT); }
static void tri_gone(void) { TRI(4, ss.x_pos.i.hi = 0x1000); }
static void (*const tri_cases[])(void) = {
    tri_start_left,
    tri_start_right,
    tri_gone,
};
static const u32 tri_expected[] = {
    0x4u,
    0xFF000141u,
    0x6C0000u,
    0x740000u,
    0x40000u,
    0u,
    0u,
    0x50000u,
    0u,
    0u,
    0x4u,
    0xFF400141u,
    0x940000u,
    0x740000u,
    0x40000u,
    0u,
    0u,
    0x50000u,
    0u,
    0u,
    0x5u,
    0x141u,
    0x10010000u,
    0x600000u,
    0x10000u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
};
static u32 test_tri(u32 row)
{
    return object_run(tri_cases[row], row, &tri_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "trident_shot_steps", 0, 0, COUNT(tri_cases), test_tri },
    { "real_owner_latch_timer_and_expanded_viewport_cleanup", NULL, NULL, 16, flash },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 16 + COUNT(tri_cases);
