#include "test_runtime.h"
#include "main/mains/main_31_thorn_trap.h"
#include "main/55C4.h"
#include "support/state_cases.h"
void thorn_trap_idle(struct MainObj* arg0);
extern s8 D_800FDC40[8];
extern union AnimationStep* thorn_trap_animations[18];
extern struct StageObjectRecord stage_object_records_3_1[71];

static struct FireInput {
    u8 aimed, variant, event, full, ended;
};
enum { SPREAD_WIDE,
    SPREAD_NARROW,
    SPREAD_FULL,
    SPREAD_IDLE,
    SPREAD_ENDED,
    AIMED,
    AIMED_RIGHT,
    AIMED_FULL,
    AIMED_IDLE };
static const struct FireInput inputs[] = {
    { 0, 0xA, 1, 0, 0 },
    { 0, 1, 1, 0, 0 },
    { 0, 0xA, 1, 1, 0 },
    { 0, 1, 0, 0, 0 },
    { 0, 1, 0, 0, 1 },
    { 1, 0, 2, 0, 0 },
    { 1, 0, 3, 0, 0 },
    { 1, 0, 2, 1, 0 },
    { 1, 0, 0, 0, 1 },
};
#define SHOT_SLOT 7
static u32 steps[2];
static u32* table[4];
static struct MainObj trap, expected;
static struct ShotObj want_shots[0x20];

static void zero(void* target, u32 size)
{
    u32 i;
    for (i = 0; i < size / 4; i++)
        ((u32*)target)[i] = 0;
}

static u32 thorn_trap_fire_run(u32 mode)
{
    const struct FireInput* input = &inputs[mode];
    union AnimationStep value;
    u32 i, difference = 0, actual = 0, spawned;
    cur_random = 0x5A5A;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.x_pos.i.hi = 0x40;
    g_Player.y_pos.i.hi = 0x40;
    zero(shot_objects, sizeof(shot_objects));
    for (i = 0; i < 0x20; i++)
        shot_objects[i].active = input->full || i != SHOT_SLOT;
    memcpy(want_shots, shot_objects, sizeof(want_shots));
    value.fields.duration = 3;
    value.fields.event = input->event;
    value.fields.relative_step = input->ended ? -2 : 1;
    value.fields.frame_index = 5;
    steps[0] = value.packed;
    value.fields.duration = 6;
    value.fields.event = 0;
    value.fields.relative_step = 1;
    steps[1] = value.packed;
    for (i = 0; i < COUNT(table); i++)
        table[i] = &steps[1];
    memset(&trap, 0, sizeof(trap));
    trap.active = 0x41;
    trap.id = 0x1F;
    trap.unk2 = input->variant;
    trap.state = 1;
    trap.unk5 = 2;
    trap.unk15 = mode == AIMED_RIGHT ? PLAYER_FACING_RIGHT : 0;
    trap.x_pos.val = 0x00A01111;
    trap.y_pos.val = 0x00802222;
    trap.animation_table = table;
    trap.animation_cursor = &steps[0];
    trap.animation_step.packed = steps[0];
    expected = trap;
    if (input->aimed)
        func_8005BFC0(&trap);
    else
        func_8005BDE4(&trap);

    spawned = input->event && !input->full;
    if (spawned) {
        struct ShotObj* shot = &want_shots[SHOT_SLOT];
        shot->active = 0x41;
        shot->id = 0x11;
        shot->unk7C = (struct WeaponObj*)&trap;
        shot->state = 0;
        shot->unk2 = input->aimed;
        if (input->aimed) {
            shot->x_pos.val = trap.x_pos.val + (trap.unk15 ? -0x540000 : 0x540000);
            shot->y_pos.val = trap.y_pos.val - 0x20000;
            shot->unk6 = shot_objects[SHOT_SLOT].unk6;
            assert(shot_objects[SHOT_SLOT].unk6 < 0x20);
            actual = shot_objects[SHOT_SLOT].unk6;
        } else {
            u32 choice, found = 0;
            for (choice = 0; choice < (input->variant >= 0xA ? 3u : 2u); choice++) {
                if (shot_objects[SHOT_SLOT].x_pos.val == trap.x_pos.val + D_800FDC40[choice * 2] * 0x10000
                    && shot_objects[SHOT_SLOT].y_pos.val == trap.y_pos.val + D_800FDC40[choice * 2 + 1] * 0x10000) {
                    found = 1;
                    actual = choice;
                    break;
                }
            }
            assert(found);
            shot->unk5 = 0;
            shot->unk6 = 0;
            shot->x_pos = shot_objects[SHOT_SLOT].x_pos;
            shot->y_pos = shot_objects[SHOT_SLOT].y_pos;
        }
        expected.animation_step.fields.event = 0;
    }
    if (input->ended) {
        expected.unk17 = 0;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = &steps[1];
        expected.animation_step.packed = steps[1];
        expected.unk5 = 3;
    } else {
        expected.animation_step.fields.duration--;
    }
    for (i = 0; i < sizeof(trap) / 4; i++)
        difference |= ((u32*)&trap)[i] ^ ((u32*)&expected)[i];
    for (i = 0; i < sizeof(want_shots) / 4; i++)
        difference |= ((u32*)shot_objects)[i] ^ ((u32*)want_shots)[i];
    assert(difference == 0);
    actual |= spawned << 8 | (u32)(u8)trap.unk5 << 16 | (u32)(u8)trap.animation_step.fields.event << 24;
    return actual;
}

static const u32 thorn_trap_fire_cases_expected[] = { 0x20100u, 0x20101u, 0x1020000u, 0x20000u, 0x30000u, 0x2010Du, 0x2010Du, 0x2020000u, 0x30000u };

static u32 open_case(u32 mode)
{
    static const u8 variants[6] = { 6, 6, 12, 12, 5, 0 };
    static const u8 phases[6] = { 6, 7, 8, 9, 4, 3 };
    static const u8 animations[6] = { 3, 7, 3, 4, 2, 1 };
    struct MainObj obj, before;
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 31;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 2;
    obj.unk2 = variants[mode];
    obj.ext.main_0.flags[0] = mode == 1 || mode == 3;
    obj.unk7C = 0x7777;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = 65536;
    obj.y_speed = -32768;
    obj.animation_table = (const u8* const*)thorn_trap_animations;
    set_animation_frame(&obj, 1, mode == 5 ? 0 : 6);
    before = obj;
    thorn_trap_open(&obj);
    before.unk5 = phases[mode];
    if (mode == 5)
        before.animation_step.fields.duration = 3;
    else {
        before.unk17 = animations[mode];
        before.previous_animation_index = 0xFF;
        before.animation_cursor = (const u8*)thorn_trap_animations[animations[mode]];
        before.animation_step = *thorn_trap_animations[animations[mode]];
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.unk5 | ((u32)obj.unk17 << 8) | ((u32)obj.animation_step.fields.duration << 16);
}
static const u32 thorn_trap_open_animation_cases_expected[] = { 0x80306u, 0x50707u, 0x80308u, 0x50409u, 0x40204u, 0x30103u };

#include "support/enemy_world.h"
static const u32 func_8005C474_expected[] = { 0x4398u };
static u32 test_func_8005C474(u32 row)
{
    struct MainObj* obj = world_spawn(31, 3, 1, 9, &stage_object_records_3_1[51]);
    u32 observed;
    main_bss_state.frame_counter = 1;
    g_Player.x_pos.i.hi = 360;
    g_Player.y_pos.i.hi = 100;
    SPIKE_IMMUNE_SET(g_Player, 1);
    cur_random = 200;
    func_8005B8D0(obj);
    assert(obj->state == 1 && obj->unk5 == 2);
    func_8005C0E4(obj);
    assert(obj->state == 2 && obj->unk5 == 0 && obj->active == 0x45);
    background_objects[0].y_pos.i.hi = 100;
    func_8005C474(obj);
    assert(obj->state == 2 && obj->unk5 == 1 && obj->active == 0x45);
    background_objects[0].x_pos.i.hi = 1000;
    world_snapshot();
    c_test_zero_words((u32*)world_expected, 2);
    world_expected->unk65 = 0;
    world_expected->ext.main_31.unk84 = 0;
    func_8005C474(obj);
    world_check();
    observed = cur_random;
    return c_test_observe(0, row, &observed, func_8005C474_expected, 1);
}

static void tt_idle(void)
{
    state_reset(2, 0, 0);
    thorn_trap_idle(&so);
}

void thorn_trap_windup(struct MainObj*);
void thorn_trap_strike(struct MainObj*);
void thorn_trap_extend(struct MainObj*);
void thorn_trap_extend_high(struct MainObj*);
#define TT(step, sub) (state_reset(step, sub, 0), so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, memset(weapon_objects, 0, sizeof(weapon_objects)), SPIKE_IMMUNE_SET(g_Player, 1))
#define TT_DIST() (state_extra = (u16)so.ext.main_31.distance)
#define TT_ANIM(flag) (state_extra = so.animation_step.fields.duration | (u32)(u8)(flag) << 8)
static void tt_init(u8 kind) { TT(0, 0), so.unk2 = kind, func_8005B8D0(&so), state_extra = (u16)so.ext.main_31.distance | (u32)so.state << 16; }
static void tt_init_left_long(void) { tt_init(4); }
static void tt_init_left_short(void) { tt_init(0); }
#define WAIT(kind, count, dist, open, face) (TT(2, 0), so.unk2 = kind, so.unk7C = count, so.ext.main_31.distance = dist, so.ext.main_31.unk82 = open, so.unk15 = face, func_8005BA2C(&so), TT_DIST())
static void tt_wait_open_low(void) { WAIT(0, 0, -1, 0, 0); }
static void tt_wait_open_mid_extended(void) { WAIT(6, 0, -1, 1, 0); }
static void tt_wait_open_mid(void) { WAIT(6, 0, -1, 0, 0); }
static void tt_wait_open_high_extended(void) { WAIT(0xC, 0, -1, 1, 0); }
static void tt_wait_open_high(void) { WAIT(0xC, 0, -1, 0, 0); }
static void tt_wait_slide_right(void) { WAIT(0, 0, 0x20, 0, PLAYER_FACING_RIGHT); }
static void tt_wait_slide_left_last(void) { WAIT(0, 0, 4, 0, 0); }
static void tt_wait_slide_right_last(void) { WAIT(0, 0, 4, 0, PLAYER_FACING_RIGHT); }
static void tt_wait_slide_left(void) { WAIT(0, 0, 0x20, 0, 0); }
static void tt_windup_done(void) { TT(4, 0), so.animation_step.fields.relative_step = -1, thorn_trap_windup(&so), TT_ANIM(so.contact_damage); }
static void tt_windup(void) { TT(4, 0), thorn_trap_windup(&so), TT_ANIM(so.contact_damage); }
static void tt_strike_hit(void) { TT(5, 0), so.contact_damage = 6, so.animation_step.fields.event = 1, thorn_trap_strike(&so), TT_ANIM(so.contact_damage); }
static void tt_strike(void) { TT(5, 0), so.contact_damage = 6, thorn_trap_strike(&so), TT_ANIM(so.contact_damage); }
#define EXTEND(step, ev, rel, run) (TT(step, 0), so.animation_step.fields.event = ev, so.animation_step.fields.relative_step = rel, run(&so), TT_ANIM(so.ext.main_0.flags[0]))
static void tt_extend_open(void) { EXTEND(6, 1, -1, thorn_trap_extend); }
static void tt_extend(void) { EXTEND(6, 0, 0, thorn_trap_extend); }
static void tt_extended_shot_right(void) { TT(7, 0), so.unk15 = PLAYER_FACING_RIGHT, so.animation_step.fields.event = 1, cur_random = 1, func_8005BDE4(&so), TT_ANIM(0); }
static void tt_extend_high_open(void) { EXTEND(8, 1, -1, thorn_trap_extend_high); }
static void tt_extend_high(void) { EXTEND(8, 0, 0, thorn_trap_extend_high); }
static void tt_main_broken(void) { TT(1, 0), so.state = 1, so.hp = 3, state_hit(&so, 0, 0, 1), func_8005C0E4(&so), state_extra = so.state; }
static void tt_main_off_screen(void) { TT(1, 0), so.state = 1, so.active = 0x41, so.x_pos.i.hi = 0x200, func_8005C0E4(&so), state_extra = so.state; }
static void tt_main_sunk(void) { TT(1, 0), so.state = 1, so.y_pos.i.hi = 0xB0, func_8005C0E4(&so), state_extra = so.state; }
static void tt_break_start_left(void) { TT(0, 0), so.state = 2, func_8005C474(&so), state_extra = so.state; }
static void tt_break_sunk_left(void) { TT(1, 0), so.state = 2, so.y_pos.i.hi = 0xB0, func_8005C474(&so), state_extra = so.state; }
static void tt_break_sunk_right(void) { TT(1, 0), so.state = 2, so.unk15 = PLAYER_FACING_RIGHT, so.y_pos.i.hi = 0xB0, func_8005C474(&so), state_extra = so.state; }
static void tt_despawn(void) { TT(1, 0), so.state = 3, so.active = 0x41, thorn_trap_update(&so), state_extra = so.state; }
static void (*const thorn_trap_misc_cases[])(void) = {
    tt_idle,
    tt_init_left_long,
    tt_init_left_short,
    tt_wait_open_low,
    tt_wait_open_mid_extended,
    tt_wait_open_mid,
    tt_wait_open_high_extended,
    tt_wait_open_high,
    tt_wait_slide_right,
    tt_wait_slide_left_last,
    tt_wait_slide_right_last,
    tt_wait_slide_left,
    tt_windup_done,
    tt_windup,
    tt_strike_hit,
    tt_strike,
    tt_extend_open,
    tt_extend,
    tt_extended_shot_right,
    tt_extend_high_open,
    tt_extend_high,
    tt_main_broken,
    tt_main_off_screen,
    tt_main_sunk,
    tt_break_start_left,
    tt_break_sunk_left,
    tt_break_sunk_right,
    tt_despawn,
};
static const u32 thorn_trap_misc_expected[] = { 2u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    2u, 0x96u, 0xFF940000u, 0u, 0u, 0u, 1u, 0x60002u, 0x100B0u, 0x4000000u,
    2u, 0x96u, 0xFF940000u, 0u, 0u, 0u, 1u, 0x60002u, 0x10060u, 0x4000000u,
    4u, 0u, 0x800000u, 0u, 0u, 0u, 2u, 0u, 0xFFFFu, 0u,
    7u, 0u, 0x800000u, 0u, 0u, 0u, 7u, 0u, 0xFFFFu, 0u,
    6u, 0u, 0x800000u, 0u, 0u, 0u, 3u, 0u, 0xFFFFu, 0u,
    9u, 0u, 0x800000u, 0u, 0u, 0u, 4u, 0u, 0xFFFFu, 0u,
    8u, 0u, 0x800000u, 0u, 0u, 0u, 3u, 0u, 0xFFFFu, 0u,
    2u, 0u, 0x780000u, 0u, 0u, 0u, 0x4000u, 0u, 0x18u, 0u,
    2u, 0u, 0x840000u, 0u, 0u, 0u, 0u, 0u, 0xFFFCu, 0u,
    2u, 0u, 0x7C0000u, 0u, 0u, 0u, 0x4000u, 0u, 0xFFFCu, 0u,
    2u, 0u, 0x880000u, 0u, 0u, 0u, 0u, 0u, 0x18u, 0u,
    5u, 0u, 0x800000u, 0u, 0u, 0u, 9u, 0u, 5u, 0u,
    4u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 4u, 0u,
    5u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 2u, 0x605u, 0u,
    5u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0x604u, 0u,
    7u, 0u, 0x800000u, 0u, 0u, 0u, 7u, 1u, 0x105u, 0u,
    6u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 4u, 0u,
    7u, 0u, 0x800000u, 0u, 0u, 0u, 0x4000u, 0u, 4u, 0x410000u,
    9u, 0u, 0x800000u, 0u, 0u, 0u, 4u, 1u, 0x105u, 0u,
    8u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 4u, 0u,
    0u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 1u, 2u, 0x2100u,
    0u, 0u, 0x2000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 2u, 0x2100u,
    1u, 0u, 0x800000u, 0u, 0u, 0u, 0xBu, 0u, 2u, 0x2100u,
    1u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 3u, 0x2100u,
    1u, 0u, 0x800000u, 0u, 0u, 0u, 0x4000u, 0u, 3u, 0x2100u,
    0u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
};

static u32 test_thorn_trap_misc(u32 row)
{
    return state_run(thorn_trap_misc_cases[row], row, &thorn_trap_misc_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "thorn_trap_misc", 0, 0, COUNT(thorn_trap_misc_cases), test_thorn_trap_misc },
    { "thorn_trap_fire", NULL, thorn_trap_fire_cases_expected, COUNT(thorn_trap_fire_cases_expected), thorn_trap_fire_run },
    { "thorn_trap_open_animation", NULL, thorn_trap_open_animation_cases_expected, COUNT(thorn_trap_open_animation_cases_expected), open_case },
    { "func_8005C474", 0, 0, 1, test_func_8005C474 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(thorn_trap_misc_cases) + COUNT(thorn_trap_fire_cases_expected) + COUNT(thorn_trap_open_animation_cases_expected) + 1;
