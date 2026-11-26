#include "test_runtime.h"
#include "main/mains/main_07_ambush_gunner.h"
#include "main/55C4.h"
extern union AnimationStep* ambush_gunner_animations[9];
extern struct Unk_unk68 ambush_gunner_terrain_box;
extern u32* D_80137E08;
extern u8* D_80141EE8[6];
extern union AnimationStep ambush_gunner_anim_2[31];

static const u32 ambush_gunner_aim_wait_0_expected[] = { 0u, 0u, 0u, 0u, 0x3Cu, 0u, 0u };
static u32 test_ambush_gunner_aim_wait_0(u32 row)
{
    u32 observed_values[7];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.unk15 = 255;
    ambush_gunner_aim_wait(&obj);
    observed_values[0] = (u32)obj.ext.main_7.saved_x_velocity;
    observed_values[1] = (u32)obj.ext.main_7.saved_y_velocity;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.unk7C;
    observed_values[5] = (u32)obj.x_speed;
    observed_values[6] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, ambush_gunner_aim_wait_0_expected, 7);
}

struct ambush_gunner_fire_1_case {
    u32 pools_full;
    u32 expected[16];
};
static const struct ambush_gunner_fire_1_case ambush_gunner_fire_1_cases[] = {
    { 1, { 4u, 2u, 0u, 0u, 0x2A010001u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 0, { 4u, 2u, 0u, 0u, 0x2A010001u, 0x41u, 2u, 0x40u, 0xBAu, OBJECT_CLUT(0x798F), 0x640000u, 0x500000u, 0xFFFE0000u, 0x10000u, 0xFFFFFFFFu, 1u } },
};
static u32 test_ambush_gunner_fire_1(u32 row)
{
    const struct ambush_gunner_fire_1_case* c = &ambush_gunner_fire_1_cases[row];
    u32 observed_values[16];
    struct MainObj obj;
    struct PlayerObj player_before;
    struct ShotObj shots_before[32];
    u8 pools_full;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 7;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    obj.unk2 = 1;
    g_Player.bg_offset = -1;
    g_Player.x_pos.val = 0;
    g_Player.y_pos.val = 5242880;
    player_before = g_Player;
    memset(&D_8013E198, -1, sizeof(D_8013E198));
    memset(&shot_objects[31], 0, sizeof(shot_objects[31]));
    pools_full = c->pools_full;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pools_full ? 1 : 0;
    }
    FILL_ACTIVE(shot_objects, 31, 1);
    func_80047404(&obj);
    obj.unk5 = 4;
    obj.unk6 = 2;
    obj.unk40 = 0xBA;
    obj.unk42 = OBJECT_CLUT(0x798F);
    obj.ext.main_7.saved_x_velocity = -131072;
    obj.ext.main_7.saved_y_velocity = 65536;
    set_animation(&obj, 2);
    obj.animation_step = ambush_gunner_anim_2[23];
    obj.animation_cursor = (const u8*)&ambush_gunner_anim_2[24];
    assert(obj.animation_step.fields.event == 2);
    memcpy(shots_before, shot_objects, sizeof(shots_before));
    if (pools_full == 0) {
        shots_before[31].active = 0x41;
    }
    if (pools_full == 0) {
        shots_before[31].id = 2;
    }
    if (pools_full == 0) {
        shots_before[31].unk40 = obj.unk40;
    }
    if (pools_full == 0) {
        shots_before[31].unk42 = obj.unk42;
    }
    if (pools_full == 0) {
        shots_before[31].animation_table = (u32**)obj.animation_table;
    }
    if (pools_full == 0) {
        shots_before[31].unk3C = (void*)obj.sprite_frames;
    }
    if (pools_full == 0) {
        shots_before[31].unk2 = obj.unk2 & 1;
    }
    if (pools_full == 0) {
        shots_before[31].unk15 = obj.unk15;
    }
    if (pools_full == 0) {
        shots_before[31].bg_offset = obj.bg_offset;
    }
    if (pools_full == 0) {
        shots_before[31].x_pos = obj.x_pos;
    }
    if (pools_full == 0) {
        shots_before[31].y_pos = obj.y_pos;
    }
    if (pools_full == 0) {
        shots_before[31].x_vel.val = obj.ext.main_7.saved_x_velocity;
    }
    if (pools_full == 0) {
        shots_before[31].y_vel.val = obj.ext.main_7.saved_y_velocity;
    }
    ambush_gunner_fire(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(shot_objects, shots_before, sizeof(shot_objects));
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.x_speed;
    observed_values[3] = (u32)obj.y_speed;
    observed_values[4] = C_TEST_STEP(obj.animation_step.packed);
    observed_values[5] = (u32)shot_objects[31].active;
    observed_values[6] = (u32)shot_objects[31].id;
    observed_values[7] = C_TEST_PSX_FACING(shot_objects[31].unk15);
    observed_values[8] = (u32)shot_objects[31].unk40;
    observed_values[9] = (u32)shot_objects[31].unk42;
    observed_values[10] = (u32)shot_objects[31].x_pos.val;
    observed_values[11] = (u32)shot_objects[31].y_pos.val;
    observed_values[12] = (u32)shot_objects[31].x_vel.val;
    observed_values[13] = (u32)shot_objects[31].y_vel.val;
    observed_values[14] = (u32)shot_objects[31].bg_offset;
    observed_values[15] = (u32)shot_objects[31].unk2;
    return c_test_observe(0, row, observed_values, c->expected, 16);
}

struct func_80047404_case {
    u32 unk2;
    u32 expected[15];
};
static const struct func_80047404_case func_80047404_cases[] = {
    { 1, { 6u, 3u, 0u, 1u, 3u, 0u, 0x40u, 0u, 0u, 0u, 1u, 0u, 0u, 0x1B000101u, 0xFFFFFFFFu } },
    { 4, { 6u, 3u, 1u, 1u, 2u, 0u, 0u, DEMO_ALT(1u, 0u), 0u, 0x8Cu, 0u, 0u, 0u, 0x10002u, 0xFFFFFFFFu } },
    { 5, { 6u, 3u, 1u, 1u, 2u, 0u, 0x40u, DEMO_ALT(1u, 0u), 0u, 0x8Cu, 0u, 0u, 0u, 0x10002u, 0xFFFFFFFFu } },
    { 6, { 6u, 3u, 1u, 1u, 2u, 0u, 0u, DEMO_ALT(1u, 0u), 1u, 0x28u, 0u, 0u, 0u, 0x10002u, 0xFFFFFFFFu } },
    { 7, { 6u, 3u, 1u, 1u, 2u, 0u, 0x40u, DEMO_ALT(1u, 0u), 1u, 0x28u, 0u, 0u, 0u, 0x10002u, 0xFFFFFFFFu } },
};
static u32 test_func_80047404(u32 row)
{
    const struct func_80047404_case* c = &func_80047404_cases[row];
    u32 observed_values[15];
    struct MainObj obj;
    struct PlayerObj player_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 7;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    obj.unk2 = c->unk2;
    g_Player.bg_offset = -1;
    player_before = g_Player;
    func_80047404(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    assert(obj.animation_table == (const u8* const*)ambush_gunner_animations);
    assert(obj.hurt_box == &ambush_gunner_terrain_box);
    assert(obj.attack_box == &ambush_gunner_terrain_box);
    observed_values[0] = (u32)obj.hp;
    observed_values[1] = (u32)obj.contact_damage;
    observed_values[2] = (u32)obj.invincibility_timer;
    observed_values[3] = (u32)obj.state;
    observed_values[4] = (u32)obj.unk5;
    observed_values[5] = (u32)obj.unk6;
    observed_values[6] = C_TEST_PSX_FACING(obj.unk15);
    observed_values[7] = (u32)obj.unk7A;
    observed_values[8] = (u32)obj.ext.main_7.unk80;
    observed_values[9] = (u32)obj.ext.main_7.unk84;
    observed_values[10] = (u32)obj.ext.main_7.unk90;
    observed_values[11] = (u32)obj.x_speed;
    observed_values[12] = (u32)obj.y_speed;
    observed_values[13] = C_TEST_STEP(obj.animation_step.packed);
    observed_values[14] = (u32)obj.bg_offset;
    return c_test_observe(0, row, observed_values, c->expected, 15);
}

struct func_80047818_0_case {
    u32 g_Player_x_pos, obj_x_pos, obj_x_pos_hi, g_Player_x_pos_hi, unk80, unk84;
    u32 expected[2];
};
static const struct func_80047818_0_case func_80047818_0_cases[] = {
    { -983042, -1048576, -32128, -32698, 1048576, 570, { 0u, 0u } },
    { -983168, -1048575, 0, -16368, 1048576, 16367, { 1u, 0u } },
    { 0, 16842753, -32768, -32768, 65280, 0, { 0u, 0u } },
    { -2, 16842753, 0, -32768, 65280, 32767, { 1u, 0u } },
};
static u32 test_func_80047818_0(u32 row)
{
    const struct func_80047818_0_case* c = &func_80047818_0_cases[row];
    u32 observed_values[2];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.x_pos.val = c->g_Player_x_pos;
    obj.x_pos.val = c->obj_x_pos;
    obj.x_pos.i.hi = c->obj_x_pos_hi;
    g_Player.x_pos.i.hi = c->g_Player_x_pos_hi;
    obj.ext.main_7.unk80 = c->unk80;
    obj.ext.main_7.unk84 = c->unk84;
    func_80047818(&obj);
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.unk7A;
    return c_test_observe(0, row, observed_values, c->expected, 2);
}

static const u32 func_80047818_1_expected[] = { 1u, 0u, 0x640000u, 0x500000u };
static u32 test_func_80047818_1(u32 row)
{
    u32 observed_values[4];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 7;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    obj.unk2 = 5;
    g_Player.bg_offset = -1;
    g_Player.x_pos.val = 13107200;
    player_before = g_Player;
    func_80047404(&obj);
    expected = obj;
    expected.unk6 = 1;
    expected.unk7A = 0;
    func_80047818(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&obj, &expected, sizeof(obj));
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.unk7A;
    observed_values[2] = (u32)obj.x_pos.val;
    observed_values[3] = (u32)obj.y_pos.val;
    return c_test_observe(0, row, observed_values, func_80047818_1_expected, 4);
}

#include "support/state_cases.h"
void ambush_gunner_main(struct MainObj*);
void ambush_gunner_emerge_burst(struct MainObj*);
void ambush_gunner_emerge_finish(struct MainObj*);
void ambush_gunner_aim_wait(struct MainObj*);
void ambush_gunner_fire(struct MainObj*);
#define AG2(step, sub) (state_reset(step, sub, 0), memset(weapon_objects, 0, sizeof(weapon_objects)), so.active = 0x41, so.state = 1, so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, g_Player.x_pos.i.hi = 0x200, g_Player.y_pos.i.hi = 0x60, SPIKE_IMMUNE_SET(g_Player, 1))
#define AG2X() (state_extra = so.state | so.ext.main_7.unk90 << 8 | (u32)(u16)so.ext.main_7.saved_x_velocity << 16)
#define AGINIT(kind) (AG2(0, 0), so.state = 0, so.unk2 = kind, func_80047404(&so), AG2X(), state_extra ^= so.ext.main_7.unk84 << 4 | so.ext.main_7.unk80 << 12)
static void ag2_init_2(void)
{
    AGINIT(2);
}
static void ag2_init_3(void) { AGINIT(3); }
static void ag2_init_default(void) { AGINIT(0); }
#define AGMAIN(step, sub, setup) (AG2(step, sub), so.unk7C = 5, setup, ambush_gunner_main(&so), AG2X())
static void ag2_main_hidden(void)
{
    AGMAIN(2, 0, so.unk15 = PLAYER_FACING_RIGHT);
}
static void ag2_main_defeat_even(void) { AGMAIN(3, 1, (so.ext.main_7.unk90 = 1, so.unk2 = 2, so.hp = 1, state_hit(&so, 0, 0, 1))); }
static void ag2_main_defeat_odd(void) { AGMAIN(3, 1, (so.ext.main_7.unk90 = 1, so.unk2 = 3, so.hp = 1, state_hit(&so, 0, 0, 1))); }
static void ag2_main_away(void) { AGMAIN(3, 1, so.x_pos.i.hi = 0x400); }
static void ag2_main_aiming(void) { AGMAIN(3, 1, so.ext.main_7.unk90 = 1); }
static void ag2_main_bursting(void) { AGMAIN(2, 1, 0); }
#define WAIT(facing, px, near, reach) (AG2(2, 0), so.unk15 = facing, g_Player.x_pos.i.hi = px, so.ext.main_7.unk80 = near, so.ext.main_7.unk84 = reach, func_80047818(&so), AG2X(), state_extra ^= so.unk7A << 4)
static void ag2_wait_left_behind(void)
{
    WAIT(0, 0x90, 0, 0x64);
}
static void ag2_wait_right_behind(void) { WAIT(PLAYER_FACING_RIGHT, 0x70, 0, 0x64); }
static void ag2_wait_left_far(void) { WAIT(0, 0x10, 0, 0x10); }
static void ag2_wait_right_far_reach(void) { WAIT(PLAYER_FACING_RIGHT, 0x100, 1, 0x28); }
static void ag2_burst_right(void) { AG2(2, 1), so.unk15 = PLAYER_FACING_RIGHT, ambush_gunner_emerge_burst(&so), AG2X(); }
static void ag2_finish_sound(void) { AG2(2, 2), so.animation_step.fields.event = 2, ambush_gunner_emerge_finish(&so), AG2X(); }
static void ag2_finish(void) { AG2(2, 2), so.animation_step.fields.event = 1, ambush_gunner_emerge_finish(&so), AG2X(); }
static void ag2_aim_left(void) { AG2(3, 1), g_Player.x_pos.i.hi = 0x20, ambush_gunner_aim_wait(&so), AG2X(); }
static void ag2_aim_left_behind(void) { AG2(3, 1), ambush_gunner_aim_wait(&so), AG2X(); }
static void ag2_aim_right(void) { AG2(3, 1), so.unk15 = PLAYER_FACING_RIGHT, ambush_gunner_aim_wait(&so), AG2X(); }
#define FIRE(facing, px) (AG2(4, 2), so.unk15 = facing, g_Player.x_pos.i.hi = px, so.ext.main_7.saved_x_velocity = 0x1234, so.animation_step.fields.event = 2, ambush_gunner_fire(&so), AG2X(), state_extra ^= (u32)shot_objects[0].x_vel.val << 4)
static void ag2_fire_left(void)
{
    FIRE(0, 0x20);
}
static void ag2_fire_left_behind(void) { FIRE(0, 0x200); }
static void ag2_fire_right(void) { FIRE(PLAYER_FACING_RIGHT, 0x200); }
static void ag2_fire_end(void) { AG2(4, 2), so.animation_step.fields.event = 1, ambush_gunner_fire(&so), AG2X(); }
static void (*const ag2_cases[])(void) = {
    ag2_init_2,
    ag2_init_3,
    ag2_init_default,
    ag2_main_hidden,
    ag2_main_defeat_even,
    ag2_main_defeat_odd,
    ag2_main_away,
    ag2_main_aiming,
    ag2_main_bursting,
    ag2_wait_left_behind,
    ag2_wait_right_behind,
    ag2_wait_left_far,
    ag2_wait_right_far_reach,
    ag2_burst_right,
    ag2_finish_sound,
    ag2_finish,
    ag2_aim_left,
    ag2_aim_left_behind,
    ag2_aim_right,
    ag2_fire_left,
    ag2_fire_left_behind,
    ag2_fire_right,
    ag2_fire_end,
};
static const u32 ag2_expected[] = {
    0x2u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x60103u,
    0x641u,
    0x41000000u,
    0x2u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x4000u,
    0x60103u,
    0x641u,
    0x41000000u,
    0x3u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x60003u,
    0x101u,
    0x41000000u,
    0x2u,
    0x5u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x4000u,
    0x0u,
    0x1u,
    0x41000000u,
    0x103u,
    0x4u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x80000000u,
    0x1u,
    0x102u,
    0x41002100u,
    0x103u,
    0x4u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x80000000u,
    0x1u,
    0x102u,
    0x41002100u,
    0x103u,
    0x4u,
    0x4000000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x2u,
    0x41000000u,
    0x103u,
    0x4u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x101u,
    0x41000000u,
    0x202u,
    0x5u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x101u,
    0x41000000u,
    0x2u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x41000000u,
    0x2u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x4000u,
    0x0u,
    0x1u,
    0x41000000u,
    0x2u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x41000000u,
    0x102u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x4000u,
    0x0u,
    0x1u,
    0x41000000u,
    0x202u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x4000u,
    0x0u,
    0x101u,
    0x41000000u,
    0x202u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x41000000u,
    0x3u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x0u,
    0x1u,
    0x41000000u,
    0x204u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x2u,
    0x0u,
    0x1u,
    0x41000000u,
    0x103u,
    0x3Cu,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x41000000u,
    0x204u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x4002u,
    0x0u,
    0x1u,
    0x41000000u,
    0x204u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0xEDC40001u,
    0x41410000u,
    0x204u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x12352341u,
    0x41410000u,
    0x204u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x4000u,
    0x0u,
    0x12240001u,
    0x41410000u,
    0x3u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x0u,
    0x1u,
    0x41000000u,
};
static u32 ag2_run(u32 row)
{
    return state_run(ag2_cases[row], row, &ag2_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "ambush_gunner_branch_steps", 0, 0, COUNT(ag2_cases), ag2_run },
    { "ambush_gunner_aim_wait_0", 0, 0, 1, test_ambush_gunner_aim_wait_0 },
    { "ambush_gunner_fire_1", 0, 0, 2, test_ambush_gunner_fire_1 },
    { "func_80047404", 0, 0, 5, test_func_80047404 },
    { "func_80047818_0", 0, 0, 4, test_func_80047818_0 },
    { "func_80047818_1", 0, 0, 1, test_func_80047818_1 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(ag2_cases) + 1 + 2 + 5 + 4 + 1;
