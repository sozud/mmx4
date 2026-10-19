#include "test_runtime.h"
#include "main/shots/shot_24_train_boss_shot.h"
#include "main/collision_bounds.h"
#include "main/mains/main_45_train_boss.h"
#include "main/sprite_animations.h"
void train_boss_arm_advance(struct ShotObj* arg0);
void train_boss_arm_hold(struct ShotObj* arg0);
void train_boss_arm_punch(struct ShotObj* arg0);
void train_boss_arm_retract(struct ShotObj* arg0);
void train_boss_arm_return(struct ShotObj* arg0);
void train_boss_arm_wait_signal(struct ShotObj* arg0);
void train_boss_arm_windup(struct ShotObj* arg0);
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
static const u32 train_boss_bullet_release_hit_pools_cases_expected[] = { 0x101u, 0x270101u, 0x102u, 0x102u, 0x102u, 0x102u };

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

#include "support/state_cases.h"

static struct MainObj arm_owner;
#define ss state_room.shot
#define ARM(step) (state_reset(step, 0, 0), memset(&arm_owner, 0, sizeof(arm_owner)), ss.state = 4, ss.unk7C = (struct WeaponObj*)&arm_owner)
#define OWNER() (state_extra = (u8)arm_owner.active | (u8)arm_owner.unk7 << 8 | (u8)arm_owner.x_pos.val << 16 | (u32)(u8)ss.unk84.bytes[0] << 24)
static void tb_bullet_init(void)
{
    ARM(0);
    ss.state = 0;
    arm_owner.unk6 = 3;
    train_boss_shot_update(&ss);
    state_extra = ss.unk84.value;
}
static void tb_arm_init(void)
{
    ARM(0);
    ss.state = 3;
    ss.unk2 = 1;
    train_boss_shot_update(&ss);
}
static void tb_bullet_despawn_notify(void)
{
    ARM(0);
    ss.state = 2;
    ss.active = 1;
    train_boss_shot_update(&ss);
    OWNER();
}
static void tb_bullet_despawn(void)
{
    ARM(0);
    ss.state = 2;
    ss.active = 1;
    ss.unk84.shot_24.owner_notified = 1;
    train_boss_shot_update(&ss);
    OWNER();
}
static void tb_bullet_despawn_wait(void)
{
    ARM(0);
    ss.state = 2;
    ss.unk84.shot_24.timer = 2;
    train_boss_shot_update(&ss);
    state_extra = ss.unk84.value;
}
static void tb_main_extended(void)
{
    ARM(6);
    ss.unk7 = 2;
    ss.unk2 = 1;
    arm_owner.active = 2;
    train_boss_shot_update(&ss);
}
static void tb_main(void)
{
    ARM(6);
    ss.unk7 = 2;
    ss.x_pos.i.hi = 0x80;
    ss.y_pos.i.hi = 0x60;
    train_boss_shot_update(&ss);
}
static void tb_advance_stop(void)
{
    ARM(2);
    ss.x_pos.i.hi = 0x1A40;
    ss.unk28 = 1;
    train_boss_arm_advance(&ss);
}
static void tb_advance(void)
{
    ARM(2);
    ss.x_vel.val = 0x10000;
    train_boss_arm_advance(&ss);
}
static void tb_signal_own(void)
{
    ARM(3);
    ss.unk2 = 2;
    arm_owner.x_pos.val = 2;
    arm_owner.unk6 = 4;
    train_boss_arm_wait_signal(&ss);
    OWNER();
}
static void tb_signal_all(void)
{
    ARM(3);
    arm_owner.x_pos.val = 4;
    train_boss_arm_wait_signal(&ss);
    OWNER();
}
static void tb_signal_other(void)
{
    ARM(3);
    arm_owner.x_pos.val = 1;
    train_boss_arm_wait_signal(&ss);
    OWNER();
}
static void tb_windup_fire(void)
{
    ARM(4);
    ss.unk7 = 1;
    arm_owner.x_pos.val = 4;
    train_boss_arm_windup(&ss);
    OWNER();
}
static void tb_windup(void)
{
    ARM(4);
    ss.unk7 = 2;
    ss.x_vel.val = -0x20000;
    train_boss_arm_windup(&ss);
    OWNER();
}
static void tb_punch_reach(void)
{
    ARM(5);
    ss.unk7 = 1;
    ss.unk2 = 1;
    ss.x_pos.i.hi = 0x40;
    train_boss_arm_punch(&ss);
    OWNER();
}
static void tb_punch(void)
{
    ARM(5);
    ss.unk7 = 2;
    ss.x_pos.i.hi = -0x80;
    train_boss_arm_punch(&ss);
    OWNER();
}
static void tb_hold_done(void)
{
    ARM(6);
    ss.unk7 = 1;
    train_boss_arm_hold(&ss);
}
static void tb_hold(void)
{
    ARM(6);
    ss.unk7 = 2;
    train_boss_arm_hold(&ss);
}
static void tb_retract_done_signal(void)
{
    ARM(7);
    ss.unk7 = 1;
    ss.unk84.bytes[0] = 3;
    ss.x_pos.i.hi = -0x80;
    arm_owner.unk7 = 0xFF;
    train_boss_arm_retract(&ss);
    OWNER();
}
static void tb_retract_done(void)
{
    ARM(7);
    ss.unk7 = 1;
    ss.x_pos.i.hi = 0x40;
    train_boss_arm_retract(&ss);
    OWNER();
}
static void tb_retract_halfway(void)
{
    ARM(7);
    ss.unk7 = 27;
    ss.unk2 = 2;
    train_boss_arm_retract(&ss);
    OWNER();
}
static void tb_retract_halfway_held(void)
{
    ARM(7);
    ss.unk7 = 27;
    ss.unk84.bytes[0] = 4;
    train_boss_arm_retract(&ss);
    OWNER();
}
static void tb_retract(void)
{
    ARM(7);
    ss.unk7 = 3;
    ss.x_vel.val = -0x40000;
    train_boss_arm_retract(&ss);
    OWNER();
}
static void tb_destroyed(void)
{
    ARM(8);
    ss.unk2 = 1;
    ss.unk42 = 0x8000;
    arm_owner.x_pos.i.hi = 0x300;
    func_8009E8E0(&ss);
    OWNER();
}
static void tb_return_sync(void)
{
    ARM(9);
    ss.x_pos.i.hi = 0x10;
    arm_owner.active = 0x1E;
    train_boss_arm_return(&ss);
    OWNER();
}
static void tb_return_wait(void)
{
    ARM(9);
    ss.x_pos.i.hi = 0x10;
    arm_owner.active = 0x10;
    train_boss_arm_return(&ss);
    OWNER();
}
static void tb_return_move(void)
{
    ARM(9);
    ss.x_pos.i.hi = -0x100;
    ss.x_vel.val = 0x10000;
    train_boss_arm_return(&ss);
    OWNER();
}
static void tb_sync_match(void)
{
    ARM(10);
    arm_owner.active = 0x22;
    arm_owner.x_pos.val = 4;
    train_boss_arm_wait_sync(&ss);
}
static void tb_sync_free(void)
{
    ARM(10);
    arm_owner.active = 0x21;
    train_boss_arm_wait_sync(&ss);
}
static void tb_sync_wait(void)
{
    ARM(10);
    arm_owner.active = 0x21;
    arm_owner.x_pos.val = 4;
    train_boss_arm_wait_sync(&ss);
}

static void (*const train_boss_arm_states_cases[])(void) = {
    tb_bullet_init,
    tb_arm_init,
    tb_bullet_despawn_notify,
    tb_bullet_despawn,
    tb_bullet_despawn_wait,
    tb_main_extended,
    tb_main,
    tb_advance_stop,
    tb_advance,
    tb_signal_own,
    tb_signal_all,
    tb_signal_other,
    tb_windup_fire,
    tb_windup,
    tb_punch_reach,
    tb_punch,
    tb_hold_done,
    tb_hold,
    tb_retract_done_signal,
    tb_retract_done,
    tb_retract_halfway,
    tb_retract_halfway_held,
    tb_retract,
    tb_destroyed,
    tb_return_sync,
    tb_return_wait,
    tb_return_move,
    tb_sync_match,
    tb_sync_free,
    tb_sync_wait,
};
static const u32 train_boss_arm_states_expected[] = { 1u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x200003u, 0u, 0x204u, 0xFF000100u, 0xFF920000u, 0xFFE80000u, 0x10000u, 0u, 0u, 0x50000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0xFF0000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 2u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x10000u, 0u, 0x1000605u, 0x100u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x1000604u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x304u, 0u, 0x1A400000u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x204u, 0u, 0x10000u, 0u, 0x10000u, 0u, 0u, 0x50000u, 0u, 0u, 0x10000404u, 0x200u, 0u, 0u, 0xFFFE0000u, 0u, 1u, 0x50000u, 0x4020000u, 0u, 0x10000404u, 0u, 0u, 0u, 0xFFFE0000u, 0u, 1u, 0x50000u, 0x40000u, 0u, 0x304u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x10000u, 0u, 0x2A000504u, 0u, 0u, 0u, 0x60000u, 0u, 0u, 0x50000u, 0x50000u, 0u, 0x1000404u, 0u, 0xFFFE0000u, 0u, 0xFFFE0000u, 0u, 0u, 0x50000u, 0u, 0u, 0x10000604u, 0x100u, 0x400000u, 0u, 0u, 0u, 0u, 0x50000u, 0x200u, 0u, 0x1000504u, 0u, 0xFF800000u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x37000704u, 0u, 0u, 0u, 0xFFFC0000u, 0u, 0u, 0x50000u, 0u, 0u, 0x1000604u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x304u, 0u, 0xFF800000u, 0u, 0u, 0u, 0u, 0x50000u, 0x3FFFE00u, 0u, 0x304u, 0u, 0x400000u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x1A000704u, 0x200u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0xFF0000u, 0u, 0x1A000704u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x4000000u, 0u, 0x2000704u, 0u, 0xFFFC0000u, 0u, 0xFFFC0000u, 0u, 0u, 0x50000u, 0u, 0u, 0x904u, 0x100u, 0x2220000u, 0u, 0x10000u, 0u, 0u, 0x50000u, 0x20u, 0x41002100u, 0x304u, 0u, 0x100000u, 0u, 0u, 0u, 0u, 0x50000u, 0xEu, 0u, 0xA04u, 0u, 0x100000u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x904u, 0u, 0xFF010000u, 0u, 0x10000u, 0u, 0u, 0x50000u, 0u, 0u, 0x304u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x304u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0xA04u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_train_boss_arm_states(u32 row)
{
    return object_run(train_boss_arm_states_cases[row], row, &train_boss_arm_states_expected[row * 10]);
}

extern u8 train_boss_arm_extended_clear_masks[4];
extern s16 train_boss_arm_reach[4];
void train_boss_arm_retract(struct ShotObj* arg0);
static const s16 reach[3] = { -83, -79, -78 };
static const u8 timers[3] = { 1, 27, 28 };
static u32 retract(u32 row)
{
    struct ShotObj obj, expected;
    struct MainObj owner, owner_expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    u32 type = row % 3, timer = row / 3 % 3, mode = row / 9 % 4, side = row / 36;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    owner.active = 0x41;
    owner.id = 45;
    owner.state = 1;
    owner.ext.main_45.attack_flags = 0x77;
    owner.ext.main_45.projectile_command = type;
    owner.ext.main_45.unk87 = 7;
    obj.active = 0x41;
    obj.id = 24;
    obj.unk2 = type;
    obj.state = 4;
    obj.unk5 = 7;
    obj.unk7 = timers[timer];
    obj.unk84.bytes[0] = mode < 2 ? mode * 2 : mode + 1;
    obj.unk7C = (struct WeaponObj*)&owner.ext.main_45;
    obj.x_vel.val = -4 * 65536;
    obj.unk28 = 1;
    obj.x_pos.val = (reach[type] + (s32)side - 1 + 4) * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    expected = obj;
    owner_expected = owner;
    expected.x_pos.val -= 4 * 65536;
    expected.unk7--;
    if (!side)
        owner_expected.ext.main_45.unk87 &= 7 ^ (1 << type);
    if (!timer) {
        expected.unk28 = 0;
        expected.unk5 = 3;
        if (mode >= 2)
            owner_expected.ext.main_45.projectile_command = 255;
    } else if (timer == 1 && mode < 2)
        owner_expected.ext.main_45.projectile_command = 255;
    assert(train_boss_arm_reach[type] == reach[type] && train_boss_arm_extended_clear_masks[type] == (u8) ~(1 << type));
    train_boss_arm_retract(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_expected, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

extern u8 train_boss_arm_attack_box[4];
extern u8 train_boss_arm_hurt_boxes[2][4];
void train_boss_arm_main(struct ShotObj*);
static struct Unk_unk68 saber_box = { 0, 0, 8, 8 };
static struct WeaponObj weapons_expected[16];
static struct VisualObj visuals_before[32];
static const u8 health[3] = { 4, 5, 26 };
static u32 interrupt(u32 row)
{
    struct ShotObj obj, expected;
    struct MainObj owner, owner_expected;
    struct {
        struct Main45LayerSignals value;
        u8 pad[3];
    } signals, signals_expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 type = row % 3, hp = row / 3, x = 160 + 69, y = 120 - 3;
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(&signals, 0, sizeof(signals));
    memset(&g_Player, 0, sizeof(g_Player));
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    {
        u32 v;
        for (v = 0; v < 32; v++)
            visual_objects[v].active = 1;
    }
    c_test_copy_words((u32*)visuals_before, (u32*)visual_objects, sizeof(visuals_before) / 4);
    D_8013E198[1] = -1;
    owner.active = 0x41;
    owner.id = 45;
    owner.state = 1;
    owner.ext.main_45.attack_flags = 0x70;
    owner.ext.main_45.unk87 = 7;
    owner.ext.main_45.layer_signals = &signals.value;
    owner_expected = owner;
    signals_expected = signals;
    signals_expected.value.projectile_state[type] = 2;
    obj.active = 0x41;
    obj.id = 24;
    obj.unk2 = type;
    obj.state = 4;
    obj.unk5 = 6;
    obj.unk7 = 2;
    obj.unk5C = health[hp];
    obj.unk60 = 6;
    obj.unk7C = (struct WeaponObj*)&owner.ext.main_45;
    obj.unk50.data = train_boss_arm_hurt_boxes[0];
    obj.unk54 = train_boss_arm_attack_box;
    obj.unk58.animation_steps = D_80105FF0;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    weapon_objects[0].active = 1;
    weapon_objects[0].id = 28;
    weapon_objects[0].unk50 = &saber_box;
    weapon_objects[0].x_pos.val = x * 65536;
    weapon_objects[0].y_pos.val = y * 65536;
    c_test_copy_words((u32*)weapons_expected, (u32*)weapon_objects, sizeof(weapons_expected) / 4);
    weapons_expected[0].unk80.word = x + 4 | ((y + 4) << 16);
    g_Player.spike_immune = 1;
    player_expected = g_Player;
    player_expected.update_delay_request = 1;
    expected = obj;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.unk7 = 1;
    expected.unk84.bytes[1] = 6;
    expected.unk42 = 0x8000;
    expected.unk5C -= 4;
    if (!hp) {
        expected.unk5 = 8;
        owner_expected.ext.main_45.unk87 &= 7 ^ (1 << type);
    } else
        expected.on_screen = 1;
    assert(((u16*)D_80105FF0)[28] == 0x0400);
    train_boss_arm_main(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_expected, sizeof(owner));
    c_test_same_words(&signals, &signals_expected, sizeof(signals));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(c_test_word_difference((u32*)weapon_objects, (u32*)weapons_expected, sizeof(weapons_expected) / 4) == 0);
    assert(c_test_word_difference((u32*)visual_objects, (u32*)visuals_before, sizeof(visuals_before) / 4) == 0);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "train_boss_arm_states", 0, 0, COUNT(train_boss_arm_states_cases), test_train_boss_arm_states },
    { "train_boss_bullet_release_hit_pools", NULL, train_boss_bullet_release_hit_pools_cases_expected, COUNT(train_boss_bullet_release_hit_pools_cases_expected), bullet_case },
    { "func_8009E188", 0, 0, 5, test_func_8009E188 },
    { "real_owner_modes_completion_and_halfway_signals_all_three_arms", NULL, NULL, 39, retract },
    { "saber_hits_and_lethal_boundary_notify_real_layer_owner_all_three_arms", NULL, NULL, 9, interrupt },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(train_boss_arm_states_cases) + COUNT(train_boss_bullet_release_hit_pools_cases_expected) + 5 + 39 + 9;
