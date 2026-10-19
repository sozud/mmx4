#include "test_runtime.h"
#include "main/mains/main_66_iris.h"
#include "support/state_cases.h"

#include "support/pool_full.h"
#include "main/55C4.h"
#include "main/player_animations_2.h"
#include "main/player_check.h"
#include "main/player_common.h"
void iris_death_wait_explosion(struct MainObj*);
void iris_robot_release_crystal_wait(struct MainObj*);
static u32 pool_full_iris_death_explode(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 1;
    pf_self.unk7E = 1;
    pf_snapshot();
    pf_expected.unk7C = 0;
    pf_expected.unk7E = 0;
    pf_expected.on_screen = 1;
    func_80080DF4(&pf_self);
    pf_expected.unk5 = 2;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_iris_crystal_drop_fire(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 1;
    pf_snapshot();
    iris_crystal_drop_fire(&pf_self);
    pf_animated();
    pf_expected.unk7C = 0x86;
    pf_expected.unk6 = 4;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_iris_intro_toss_crystal(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 1;
    pf_snapshot();
    iris_intro_toss_crystal(&pf_self);
    pf_animation(0xA);
    pf_expected.unk7C = 0x3E;
    pf_expected.unk6 = 7;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_iris_robot_dash_laser(void)
{
    u32 actual;
    pf_prepare();
    pf_event(1, 1);
    pf_self.x_speed = 0x10000;
    pf_snapshot();
    iris_robot_dash_laser(&pf_self);
    pf_animation(6);
    pf_expected.x_speed = 0;
    pf_expected.unk7C = 0xB4;
    pf_expected.unk6 = 4;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_iris_death_explode,
    pool_full_iris_crystal_drop_fire,
    pool_full_iris_intro_toss_crystal,
    pool_full_iris_robot_dash_laser,
};

static const u32 pool_full_cases_expected[] = { 0x2u, 0x860400u, 0x3E0700u, 0xB40400u };
static struct MainObj iris_partner;
#define IRIS(timer, flash, inv) (state_reset(0xD, 1, 0), memset(&iris_partner, 0, sizeof(iris_partner)), so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, so.ext.main_66.partner = &iris_partner, so.unk7C = timer, so.unk7E = flash, so.invincibility_timer = inv, func_80080DF4(&so), state_extra = iris_partner.unk42 | (so.ext.main_66.effect == (void*)&effect_objects[0]) << 16)
static void ir_death_wait(void)
{
    IRIS(3, 3, 0);
}
static void ir_death_burst(void) { IRIS(1, 3, 0); }
static void ir_death_flash(void) { IRIS(3, 0, 0x20); }
static void ir_death_flash_slow(void) { IRIS(3, 0, 0x10); }
static void ir_death_flash_fast(void) { IRIS(3, 0, 8); }
static void ir_crystal_wait(void)
{
    state_reset(5, 2, 0);
    so.hp = 0x20;
    iris_robot_release_crystal_wait(&so);
    state_extra = so.ext.main_66.hover_timer;
}
static void ir_crystal_wait_hurt(void)
{
    state_reset(5, 2, 0);
    so.hp = 0x10;
    iris_robot_release_crystal_wait(&so);
    state_extra = so.ext.main_66.hover_timer;
}

static void (*const iris_death_states_cases[])(void) = {
    ir_death_wait,
    ir_death_burst,
    ir_death_flash,
    ir_death_flash_slow,
    ir_death_flash_fast,
    ir_crystal_wait,
    ir_crystal_wait_hurt,
};
static const u32 iris_death_states_expected[] = { 0x10Du, 0x20002u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x102u, 0x20000u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0x10000u, 1u, 0x10Du, 0x50002u, 0x800000u, 0u, 0u, 0u, 0x80000000u, 0u, 0x8000u, 0u, 0x10Du, 0xB0002u, 0x800000u, 0u, 0u, 0u, 0x80000000u, 0xB00u, 0x8000u, 0u, 0x10Du, 0x50002u, 0x800000u, 0u, 0u, 0u, 0x80000000u, 0x300u, 0x8000u, 0u, 0x205u, 0u, 0u, 0u, 0u, 0u, 0u, 0x200000u, 0xF0u, 0u, 0x205u, 0u, 0u, 0u, 0u, 0u, 0u, 0x100000u, 0xB4u, 0u };

static u32 test_iris_death_states(u32 row)
{
    return state_run(iris_death_states_cases[row], row, &iris_death_states_expected[row * 10]);
}

static struct PlayerObj iris_player;
#define BOOM(setup)                                                                                   \
    do {                                                                                              \
        u8 boss = engine_obj.enable_boss;                                                             \
        struct MainObj* ptr = engine_obj.boss_ptr;                                                    \
        iris_player = g_Player;                                                                       \
        state_reset(0xD, 2, 0);                                                                       \
        memset(&iris_partner, 0, sizeof(iris_partner));                                               \
        iris_partner.active = 1;                                                                      \
        iris_partner.x_pos.i.hi = 0x90;                                                               \
        so.x_pos.i.hi = 0x80;                                                                         \
        so.y_pos.i.hi = 0x60;                                                                         \
        so.ext.main_66.partner = &iris_partner;                                                       \
        so.ext.main_66.effect = &effect_objects[0];                                                   \
        setup;                                                                                        \
        iris_death_wait_explosion(&so);                                                               \
        state_extra = iris_partner.unk42 | iris_partner.unk5 << 16 | (u8)g_Player.script_state << 24; \
        g_Player = iris_player;                                                                       \
        engine_obj.enable_boss = boss;                                                                \
        engine_obj.boss_ptr = ptr;                                                                    \
    } while (0)
static void irb_flash(void)
{
    BOOM((effect_objects[0].active = 1, so.unk7E = 0));
}
static void irb_flash_wait(void) { BOOM((effect_objects[0].active = 1, so.unk7E = 3)); }
static void irb_fall(void) { BOOM((effect_objects[0].active = 1, effect_objects[0].unk7 = 1)); }
static void irb_fall_gone(void) { BOOM((effect_objects[0].active = 1, effect_objects[0].unk7 = 1, iris_partner.active = 0)); }
static void irb_done_left(void) { BOOM(g_Player.x_pos.i.hi = 0x100); }
static void irb_done_right(void) { BOOM(g_Player.x_pos.i.hi = 0x10); }

static void (*const iris_death_explosion_cases[])(void) = {
    irb_flash,
    irb_flash_wait,
    irb_fall,
    irb_fall_gone,
    irb_done_left,
    irb_done_right,
};
static const u32 iris_death_explosion_expected[] = { 0x20Du, 0x50000u, 0x800000u, 0u, 0u, 0u, 0x80000000u, 0u, 0x8000u, 1u, 0x20Du, 0x20000u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0x20Du, 0u, 0x900000u, 0u, 0u, 0u, 0x4023u, 0u, 0x10000u, 1u, 0x20Du, 0u, 0x900000u, 0u, 0u, 0u, 0x4023u, 0u, 0u, 1u, 0x203u, 0x3Cu, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0x1000000u, 0u, 0x203u, 0x3Cu, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0x1000000u, 0u };

static u32 test_iris_death_explosion(u32 row)
{
    return state_run(iris_death_explosion_cases[row], row, &iris_death_explosion_expected[row * 10]);
}

extern void* iris_animations[37];
extern struct Unk_unk68 D_80107DFC[], D_80107E84[], D_801060F0[];
extern struct Unk_unk68 D_801035C0, D_801035C8;

static void iris_damage_reset(u8 crystal)
{
    memset(&state_room, 0, sizeof(state_room));
    memset(&iris_partner, 0, sizeof(iris_partner));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(shot_objects, 0, sizeof(shot_objects));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(state_sound_rows, 0, sizeof(state_sound_rows));
    D_80141F50[2] = state_sound_rows;
    D_8013E198[0] = D_8013E198[1] = -1;
    engine_obj.cur_character = CHARACTER_ZERO;
    g_Player.hp = 32;
    g_Player.spike_immune = 1;
    so.active = 0x41;
    so.state = 1;
    so.id = 66;
    so.unk2 = crystal;
    so.unk5 = crystal ? 7 : 5;
    so.unk6 = crystal ? 0 : 1;
    so.hp = 48;
    so.bg_offset = -1;
    so.x_pos.val = FIXED(100);
    so.y_pos.val = FIXED(100);
    so.animation_table = (const u8* const*)iris_animations;
    set_animation(&so, 0);
    so.unk42 = 0x1234;
    so.hurt_box = crystal ? &D_801035C8 : &D_801035C0;
    so.collision_data = crystal ? D_80107E84 : D_80107DFC;
    so.ext.main_66.active = 1;
    so.ext.main_66.partner = &iris_partner;
    iris_partner.state = 1;
    iris_partner.unk5 = 3;
    iris_partner.unk42 = 0x4321;
    iris_partner.animation_table = (const u8* const*)iris_animations;
    set_animation(&iris_partner, 0);
}

static const struct {
    u8 crystal, flash, blink, released, next_flash, next_blink, self_bit, partner_bit;
} iris_flash_cases[] = {
    { 1, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 2, 2, 0, 1, 1, 1, 1 },
    { 1, 2, 1, 0, 1, 0, 0, 0 },
    { 1, 1, 2, 1, 0, 1, 0, 0 },
    { 0, 2, 2, 0, 1, 1, 0, 1 },
    { 0, 1, 2, 1, 0, 1, 0, 0 },
    { 1, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 2, 0, 0, 1, 0, 0, 0 },
};

static u32 test_iris_flash(u32 row)
{
    iris_damage_reset(iris_flash_cases[row].crystal);
    so.ext.main_66.flash_timer = iris_flash_cases[row].flash;
    so.ext.main_66.blink_timer = iris_flash_cases[row].blink;
    so.ext.main_66.crystal_released = iris_flash_cases[row].released;
    so.invincibility_timer = 5;
    if (iris_flash_cases[row].flash)
        so.collision_data = D_801060F0;
    func_80080834(&so);
    assert(so.ext.main_66.flash_timer == iris_flash_cases[row].next_flash);
    assert(so.ext.main_66.blink_timer == iris_flash_cases[row].next_blink);
    assert(!!(so.unk42 & 0x8000) == iris_flash_cases[row].self_bit);
    assert(!!(iris_partner.unk42 & 0x8000) == iris_flash_cases[row].partner_bit);
    assert((so.unk42 & 0x7FFF) == 0x1234);
    assert(so.invincibility_timer == (iris_flash_cases[row].flash == 1 ? 0 : 5));
    if (iris_flash_cases[row].crystal)
        assert(so.collision_data == (iris_flash_cases[row].next_flash ? D_801060F0 : D_80107E84));
    assert(so.hp == 48 && so.state == 1);
    return 1;
}

static const struct {
    u8 crystal, weapon, hp, drones, full_misc, full_shots, facing;
    u16 seed;
    u8 next_hp, next_drones, misc, shots, dead;
} iris_damage_cases[] = {
    { 0, 24, 48, 0, 0, 0, 0, 0xD37, 48, 2, 1, 2, 0 },
    { 0, 24, 48, 16, 0, 0, 0, 0xD37, 48, 16, 1, 0, 0 },
    { 0, 24, 48, 15, 0, 0, 0, 0xD37, 48, 16, 1, 1, 0 },
    { 0, 24, 48, 0, 0, 1, 0, 0xD37, 48, 2, 1, 0, 0 },
    { 0, 24, 48, 0, 1, 0, 0, 0xD37, 48, 2, 0, 2, 0 },
    { 0, 24, 48, 0, 0, 0, 1, 0xD37, 48, 2, 1, 2, 0 },
    { 0, 24, 48, 0, 0, 0, 0, 0x14A, 48, 2, 1, 2, 0 },
    { 1, 24, 48, 0, 0, 0, 0, 0xD37, 46, 0, 0, 0, 0 },
    { 1, 0, 48, 0, 0, 0, 0, 0xD37, 48, 0, 0, 0, 0 },
    { 1, 24, 2, 0, 0, 0, 0, 0xD37, 0, 0, 0, 0, 1 },
    { 0, 0, 48, 0, 0, 0, 0, 0xD37, 48, 0, 0, 0, 0 },
    { 0, 24, 1, 0, 0, 0, 0, 0xD37, 48, 2, 1, 2, 0 },
};

static u32 test_iris_damage(u32 row)
{
    u32 i, misc = 0, shots = 0, first = 0;
    iris_damage_reset(iris_damage_cases[row].crystal);
    so.hp = iris_damage_cases[row].hp;
    if (iris_damage_cases[row].dead)
        g_Player.spike_immune = 0;
    so.unk15 = iris_damage_cases[row].facing ? 0x40 : 0;
    so.ext.main_66.drone_count = iris_damage_cases[row].drones;
    cur_random = iris_damage_cases[row].seed;
    state_hit(&so, iris_damage_cases[row].weapon, 0, 0);
    so.hurt_box = iris_damage_cases[row].crystal ? &D_801035C8 : &D_801035C0;
    so.collision_data = iris_damage_cases[row].crystal ? D_80107E84 : D_80107DFC;
    if (iris_damage_cases[row].full_misc)
        for (i = 0; i < COUNT(misc_objects); i++)
            misc_objects[i].active = 1;
    if (iris_damage_cases[row].full_shots)
        for (i = 0; i < COUNT(shot_objects); i++)
            shot_objects[i].active = 1;
    func_80080834(&so);
    assert(so.hp == iris_damage_cases[row].next_hp);
    assert(so.ext.main_66.drone_count == iris_damage_cases[row].next_drones);
    assert(so.state == (iris_damage_cases[row].dead ? 2 : 1));
    if (iris_damage_cases[row].dead) {
        assert(so.unk5 == 0 && iris_partner.state == 3 && iris_partner.unk5 == 0);
        assert(g_Player.spike_immune == 1);
    } else {
        assert(iris_partner.state == 1 && iris_partner.unk5 == 3);
        assert(so.ext.main_66.flash_timer == (iris_damage_cases[row].weapon == 24 ? 24 : 0));
        assert(so.invincibility_timer == (iris_damage_cases[row].weapon == 24 && !iris_damage_cases[row].crystal ? 1 : 0));
        assert(so.ext.main_66.blink_timer == (iris_damage_cases[row].weapon == 24 && iris_damage_cases[row].crystal ? 24 : 0));
    }
    for (i = 0; i < COUNT(misc_objects); i++)
        if (misc_objects[i].active && misc_objects[i].id == 0x16 && misc_objects[i].ext.unk.unk50 == (void*)&so) {
            assert(misc_objects[i].unk2 == 8 && misc_objects[i].unk6 == 1);
            misc++;
        }
    for (i = 0; i < COUNT(shot_objects); i++)
        if (shot_objects[i].active && shot_objects[i].id == 0x2C && shot_objects[i].unk7C == (void*)&so) {
            assert(shot_objects[i].active == 0x41 && shot_objects[i].unk2 == shots);
            assert(shot_objects[i].x_pos.val == so.x_pos.val && shot_objects[i].y_pos.val == so.y_pos.val);
            assert(shot_objects[i].unk84.value <= (iris_damage_cases[row].facing ? 16 : 8));
            if (shots == 0) {
                first = shot_objects[i].unk84.value;
                assert(first == (iris_damage_cases[row].seed == 0x14A ? 5 : 4) + (iris_damage_cases[row].facing ? 8 : 0));
            } else {
                assert(first != shot_objects[i].unk84.value);
                assert(shot_objects[i].unk84.value == (iris_damage_cases[row].seed == 0x14A ? 6 : 5) + (iris_damage_cases[row].facing ? 8 : 0));
            }
            shots++;
        }
    assert(misc == iris_damage_cases[row].misc && shots == iris_damage_cases[row].shots);
    if (shots == 2)
        assert(cur_random == (iris_damage_cases[row].seed == 0x14A ? 0x1C72 : 0x76D4));
    return 1;
}

static u32 test_iris_low_health_release(u32 row)
{
    iris_damage_reset(0);
    so.unk5 = 3;
    so.unk6 = 0;
    so.ext.main_66.hover_timer = 2;
    so.ext.main_66.crystal_released = row;
    g_Player.hp = 7;
    func_80080834(&so);
    assert(so.unk5 == (row ? 3 : 5));
    assert(so.ext.main_66.hover_timer == 1);
    assert(so.hp == 48);
    return 1;
}

void func_80081AD0(struct MainObj*);
extern void* iris_animations[37];
extern struct Unk_unk68 D_80107DFC[];
static const u8 health[3] = { 23, 24, 48 };
static u32 recover(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before;
    u32 hp = health[row % 3], wait = row / 3 % 2, face = row / 6;
    engine_obj.stage = 11;
    engine_obj.substage = 0;
    engine_obj.cur_character = 1;
    engine_before = engine_obj;
    D_8013E198[2] = -1;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 66;
    obj.state = 1;
    obj.unk5 = 4;
    obj.unk6 = 4;
    obj.hp = hp;
    obj.unk15 = face ? 0x40 : 0;
    obj.unk7C = wait ? 2 : 1;
    obj.ext.main_66.hover_timer = 17;
    obj.animation_table = (const u8* const*)iris_animations;
    set_animation(&obj, 6);
    assert(obj.animation_step.packed == 0x18010001);
    expected = obj;
    expected.unk7C--;
    expected.animation_cursor += 4;
    expected.animation_step.packed = 0x19010001;
    if (!wait) {
        expected.ext.main_66.hover_timer = hp >= 24 ? 240 : 180;
        expected.unk17 = 1;
        expected.animation_cursor = iris_animations[1];
        expected.animation_step.packed = 0x08010001;
        expected.collision_data = D_80107DFC;
        expected.unk5 = 3;
        expected.unk6 = 0;
    }
    func_80081AD0(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(D_8013E198[2] == -1);
    return 1;
}

void iris_intro_wait_camera(struct MainObj*);
void iris_intro_warning(struct MainObj*);
void iris_robot_decide(struct MainObj* arg0);
extern void* iris_animations[37];
static u32 zero_gfx[32], zero_frames[32];
static struct MainObj expected_mains[48];
static struct EffectObj expected_effects[32];
static u32 full(u32 row)
{
    struct MainObj* iris = &main_objects[0];
    struct PlayerObj player;
    struct EngineObj engine;
    u32 i;
    engine_obj.stage = 11;
    engine_obj.substage = 0;
    engine_obj.cur_character = CHARACTER_ZERO;
    engine_obj.max_hp = 32;
    g_Player.active = 0x41;
    g_Player.unk2 = CHARACTER_ZERO;
    g_Player.state = 1;
    g_Player.hp = 24;
    g_Player.animation_table = (u32**)D_8011AFF0;
    memset(zero_gfx, 0, sizeof(zero_gfx));
    memset(zero_frames, 0, sizeof(zero_frames));
    zero_gfx[0] = zero_frames[0] = 64;
    TEST_PLAYER_GFX = (u8*)zero_gfx;
    TEST_SPRITE_FRAMES = (u8*)zero_frames;
    g_Player.x_pos.val = 2096 * 65536;
    g_Player.y_pos.val = 446 * 65536;
    player_set_animation(&g_Player, 5);
    player_set_collision_bounds(&g_Player);
    player_update_frame_hitbox(&g_Player);
    background_objects[0].x_pos.val = 2032 * 65536;
    background_objects[0].y_pos.val = 266 * 65536;
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    for (i = 1; i < COUNT(main_objects); i++)
        main_objects[i].active = row ? 1 : 0;
    c_test_zero_words((u32*)effect_objects, sizeof(effect_objects) / 4);
    for (i = 0; i < COUNT(effect_objects); i++)
        effect_objects[i].active = row ? 0 : 1;
    iris->active = 0x41;
    iris->id = 66;
    iris->state = 1;
    iris->x_pos.i.hi = 2304;
    iris->y_pos.i.hi = 446;
    iris->animation_table = (const u8* const*)iris_animations;
    if (row) {
        iris->hp = 48;
        iris->unk5 = 1;
        iris->ext.main_66.active = 1;
        iris->ext.main_66.release_countdown = 1;
        engine_obj.boss_ptr = iris;
        set_animation(iris, 0);
        iris_robot_decide(iris);
        for (i = 0; i < 6; i++)
            func_80081BA0(iris);
        assert(iris->unk5 == 5 && iris->unk6 == 0 && iris->animation_step.packed == 0xEC010001);
    } else {
        iris->unk5 = 2;
        iris->unk6 = 1;
        set_animation(iris, 9);
        iris_intro_wait_camera(iris);
        assert(iris->unk6 == 2 && g_Player.script_state == 1 && g_Player.script_action == 0x15);
        g_Player.unk5 = g_Player.script_action;
        player_script_walk_to_mark(&g_Player);
        assert(g_Player.script_state == -1);
    }
    memcpy(expected_mains, main_objects, sizeof(expected_mains));
    memcpy(expected_effects, effect_objects, sizeof(expected_effects));
    if (row) {
        expected_mains[0].unk6 = 1;
        expected_mains[0].animation_cursor = (const u8*)iris_animations[32] + 4;
        expected_mains[0].animation_step.packed = 0xEC000101;
    } else {
        expected_mains[0].unk6 = 3;
        expected_mains[0].animation_step.packed = 0x28010003;
    }
    player = g_Player;
    engine = engine_obj;
    cur_random = 0x1234;
    if (row)
        func_80081BA0(iris);
    else
        iris_intro_warning(iris);
    assert(c_test_word_difference((u32*)main_objects, (u32*)expected_mains, sizeof(expected_mains) / 4) == 0);
    c_test_same_words(effect_objects, expected_effects, sizeof(expected_effects));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    assert(cur_random == 0x1234 && engine_obj.cur_character == CHARACTER_ZERO && g_Player.unk2 == CHARACTER_ZERO && TEST_PLAYER_GFX == (u8*)zero_gfx && TEST_SPRITE_FRAMES == (u8*)zero_frames && zero_gfx[0] == 64 && zero_frames[0] == 64);
    for (i = 1; i < 32; i++)
        assert(zero_gfx[i] == 0 && zero_frames[i] == 0);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "iris_flash", 0, 0, COUNT(iris_flash_cases), test_iris_flash },
    { "iris_damage", 0, 0, COUNT(iris_damage_cases), test_iris_damage },
    { "iris_low_health_release", 0, 0, 2, test_iris_low_health_release },
    { "iris_death_explosion", 0, 0, COUNT(iris_death_explosion_cases), test_iris_death_explosion },
    { "iris_death_states", 0, 0, COUNT(iris_death_states_cases), test_iris_death_states },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "actual_laser_recovery_animation_and_hover_health_boundary", NULL, NULL, 12, recover },
    { "Zero_only_Iris_real_script_arrival_warning_or_own_release_event_full_pools", NULL, NULL, 2, full },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(iris_flash_cases) + COUNT(iris_damage_cases) + 2 + COUNT(iris_death_explosion_cases) + COUNT(iris_death_states_cases) + COUNT(pool_full_cases) + 12 + 2;
