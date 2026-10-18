#include "test_runtime.h"
#include "main/shots/shot_24_train_boss_shot.h"
#include "main/collision_bounds.h"
#include "main/mains/main_45_train_boss.h"
#include "main/sprite_animations.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static s32 sprites[4] = { 8, 12, 0x11223344, 0x55667788 };
static void expected_animation(struct ShotObj* obj, u32 animation, u32 step)
{
    obj->unk17 = animation;
    obj->previous_animation_index = 0xFF;
    ANIMATED_OBJECT(obj)->animation_cursor = (u32*)(train_boss_animations[animation] + step);
    obj->animation_step = train_boss_animations[animation][step];
}
static u32 bullet_case(u32 mode)
{
    struct ShotObj obj, expected;
    struct MainObj owner, owner_expected;
    struct PlayerObj player_expected;
    struct WeaponObj weapons_expected[16];
    struct VisualObj visuals_expected[32];
    struct BackgroundObj backgrounds_before[3];
    struct RideArmorObj armor_before = qux_object;
    u32 i, dying = mode >= 3, free_slots = mode >= 4 ? mode - 3 : 0;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    cur_random = 119;
    TEST_SPRITE_FRAMES = (u8*)sprites;
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = i >= 32 - free_slots ? 0 : 1;
        visual_objects[i].id = 39;
        visual_objects[i].state = 40;
        visual_objects[i].unk2 = 9;
        visual_objects[i].unk5 = 3;
        visual_objects[i].unk6 = 4;
        visual_objects[i].unk15 = 0x20;
        visual_objects[i].unk42 = 0x7777;
        visual_objects[i].bg_offset = 2;
        visual_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        visual_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    owner.active = 0x41;
    owner.id = 45;
    owner.state = 2;
    owner.unk5 = 7;
    owner.ext.main_45.attack_flags = 0;
    owner.ext.main_45.projectile_command = 0x55;
    obj.active = 0x41;
    obj.id = 24;
    obj.state = 1;
    obj.on_screen = 1;
    obj.bg_offset = -1;
    obj.unk6 = mode < 2 ? 0 : 1;
    obj.unk42 = 0x8123;
    obj.unk5C = 1;
    obj.unk84.shot_24.timer = mode < 2 ? 1 : 0;
    obj.unk84.shot_24.owner_state = mode == 0 ? 3 : 2;
    obj.unk84.shot_24.owner_notified = 0;
    obj.unk7C = (struct MainObj*)&owner.ext.main_45;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    obj.x_vel.val = 2 * 65536;
    obj.y_vel.val = 65536;
    obj.animation_table = (u32**)train_boss_animations;
    obj.unk58.collision_data = D_80106070;
    obj.unk50.data = train_boss_bullet_hit_box;
    obj.unk54 = train_boss_bullet_hit_box;
    expected_animation(&obj, 4, 0);
    g_Player.hp = 30;
    g_Player.spike_immune = 1;
    g_Player.unk2 = 1;
    g_Player.boss_flags = 0x40;
    g_Player.x_pos.val = (mode == 0 ? 132 : mode == 2 ? 102
                                                      : 100)
            * 65536
        + 0x1234;
    g_Player.y_pos.val = (mode == 1 ? 132 : mode == 2 ? 99
                                                      : 100)
            * 65536
        + 0x5678;
    g_Player.unk54 = (struct Unk_unk68*)train_boss_bullet_hit_box;
    if (dying) {
        g_Player.x_pos.i.hi = 140;
        weapon_objects[0].active = 1;
        weapon_objects[0].id = 28;
        weapon_objects[0].bg_offset = -1;
        weapon_objects[0].unk50 = (struct Unk_unk68*)train_boss_bullet_hit_box;
        weapon_objects[0].x_pos.val = 102 * 65536 + 0x1234;
        weapon_objects[0].y_pos.val = 99 * 65536 + 0x5678;
    }
    expected = obj;
    owner_expected = owner;
    player_expected = g_Player;
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    memcpy(visuals_expected, visual_objects, sizeof(visuals_expected));
    expected.unk42 &= 0x7FFF;
    expected_animation(&expected, 4, 1);
    if (mode < 2) {
        expected.unk6 = 1;
        expected.unk84.shot_24.timer = mode == 0 ? 0 : 0x27;
        expected.x_vel.val = mode == 0 ? 3 * 65536 : 0;
        expected.y_vel.val = mode == 0 ? 0 : -3 * 65536;
        expected_animation(&expected, 3, 0);
    } else {
        expected.unk84.shot_24.owner_notified = 1;
        owner_expected.ext.main_45.projectile_command = 0xFF;
        expected.x_pos.val += 2 * 65536;
        expected.y_pos.val -= 65536;
        expected.on_screen = 0;
        expected.state = 2;
        if (dying) {
            assert(D_80106070[28] == 0x7F00);
            expected.unk5C = 0;
            expected.unk42 |= 0x8000;
            player_expected.update_delay_request = 1;
            weapons_expected[0].unk80.word = 101 | (98 << 16);
            if (free_slots) {
                struct VisualObj* visual = &visuals_expected[32 - free_slots];
                visual->active = 0x21;
                visual->id = 3;
                visual->unk2 = 7;
                visual->bg_offset = -1;
                visual->animation_table = D_8011BF40;
                visual->unk40 = 0;
                visual->unk42 = 0x7802;
                visual->unk16 = 0;
                visual->unk3C = (u8*)sprites + 12;
                visual->unk15 = 0x40;
                visual->x_pos.i.hi = 101;
                visual->y_pos.i.hi = 98;
            }
            if (free_slots == 2) {
                struct VisualObj* visual = &visuals_expected[31];
                visual->active = 0x21;
                visual->id = 4;
                visual->unk2 = 0;
                visual->state = visual->unk5 = visual->unk6 = 0;
                visual->unk5C.value = 1;
                visual->x_pos.val = 102 * 65536;
                visual->y_pos.val = 99 * 65536;
                visual->unk15 = 0;
                visual->bg_offset = 0;
                visual->unk16 = 1;
            }
        }
    }
    func_8009E188(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    for (i = 0; i < sizeof(weapons_expected) / 4; i++)
        assert(((u32*)weapon_objects)[i] == ((u32*)weapons_expected)[i]);
    for (i = 0; i < sizeof(visuals_expected) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)visuals_expected)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    for (i = 0; i < sizeof(qux_object) / 4; i++)
        assert(((u32*)&qux_object)[i] == ((u32*)&armor_before)[i]);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    assert(cur_random == (dying ? 376 : 119) && SP_SPRITE_FRAMES == sprites);
    assert(sprites[0] == 8 && sprites[1] == 12 && sprites[2] == 0x11223344 && sprites[3] == 0x55667788);
    i = (u8)obj.state | ((u32)(u8)obj.unk6 << 8) | ((u32)(u16)obj.unk84.shot_24.timer << 16);
    return i;
}
#define CASE(m)                                                     \
    static u32 train_boss_bullet_release_hit_pools_bullet_##m(void) \
    {                                                               \
        return bullet_case(m);                                      \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
#define ENTRY(m) train_boss_bullet_release_hit_pools_bullet_##m,
static const CTestCase train_boss_bullet_release_hit_pools_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) };
static const u32 train_boss_bullet_release_hit_pools_cases_expected[] = { 0x101u, 0x270101u, 0x102u, 0x102u, 0x102u, 0x102u };
#undef CASE
#undef ENTRY

static const u32 inputs_0[5][9] = {
    { 255, 0, 7, 0, 0, 0, 0, 0, 0 },
    { 255, 0, 8, 0, 0, 0, 0, 0, 0 },
    { 255, 0, 0, -1, 255, 23093344, 0, 0, 0 },
    { 255, 0, 0, -1, 0, 0, 0, 0, 255 },
    { 255, 0, 0, -1, 0, 0, 0, 0, 0 },
};
struct func_8009E188_case {
    u32 expected[9];
};
static const struct func_8009E188_case func_8009E188_cases[] = {
    { { 0u, 0u, 2u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { { 0u, 0u, 2u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { { 0u, 0u, 2u, 0u, 0xFFFFFFFFu, 0u, 0xFEu, 0x1606060u, 0u } },
    { { 0u, 1u, 0u, 0u, 0xFFFFFFFFu, 0xFFu, 0u, 0u, 0u } },
    { { 0xFFu, 1u, 0u, 0u, 0xFFFFFFFFu, 1u, 0u, 0u, 0u } },
};
static u32 test_func_8009E188(u32 row)
{
    const struct func_8009E188_case* c = &func_8009E188_cases[row];
    u32 observed_values[9];
    struct ShotObj obj;
    struct Main45Ext child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&cur_random, 0, sizeof(cur_random));

    memset(&qux_object, 0, sizeof(qux_object));
    memset(&visual_objects, 0, sizeof(visual_objects));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    child_0_present = inputs_0[row][0];
    obj.unk42 = inputs_0[row][1];
    child_0.attack_flags = inputs_0[row][2];
    obj.unk6 = inputs_0[row][3];
    obj.unk84.shot_24.timer = inputs_0[row][4];
    obj.x_vel.val = inputs_0[row][5];
    obj.y_vel.val = inputs_0[row][6];
    obj.unk84.shot_24.owner_state = inputs_0[row][7];
    obj.unk84.shot_24.owner_notified = inputs_0[row][8];
    obj.unk7C = child_0_present ? &child_0 : NULL;
    func_8009E188(&obj);
    observed_values[0] = (u32)child_0.projectile_command;
    observed_values[1] = (u32)obj.on_screen;
    observed_values[2] = (u32)obj.state;
    observed_values[3] = (u32)obj.unk42;
    observed_values[4] = (u32)obj.unk6;
    observed_values[5] = (u32)obj.unk84.shot_24.owner_notified;
    observed_values[6] = (u32)obj.unk84.shot_24.timer;
    observed_values[7] = (u32)obj.x_vel.val;
    observed_values[8] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, c->expected, 9);
}

static const u32 train_boss_arm_wait_sync_expected[] = { 0u };
static u32 test_train_boss_arm_wait_sync(u32 row)
{
    u32 observed_values[1];
    struct ShotObj obj;
    struct WeaponObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    child_0_present = 255;
    child_0.active = 16;
    child_0.x_pos.val = -1048572;
    obj.unk7C = child_0_present ? &child_0 : NULL;
    train_boss_arm_wait_sync(&obj);
    observed_values[0] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, train_boss_arm_wait_sync_expected, 1);
}

const struct CTestGroup c_test_groups[] = {
    { "train_boss_bullet_release_hit_pools", train_boss_bullet_release_hit_pools_cases, train_boss_bullet_release_hit_pools_cases_expected, COUNT(train_boss_bullet_release_hit_pools_cases), 0 },
    { "func_8009E188", 0, 0, 5, test_func_8009E188 },
    { "train_boss_arm_wait_sync", 0, 0, 1, test_train_boss_arm_wait_sync },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(train_boss_bullet_release_hit_pools_cases) + 5 + 1;
