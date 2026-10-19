#include "test_runtime.h"
#include "main/shots/shot_53_sigma_head.h"
#include "main/object_motion.h"
void sigma_head_chomp(struct ShotObj*);
void sigma_head_freeze(struct ShotObj*);
void sigma_head_lightning(struct ShotObj*);
void sigma_head_shift(struct ShotObj*);
extern s16 sigma_head_formation_end[8][3][2];
extern u8 sigma_head_formation_next[8][3];

static u32 head_case(u32 raw, u32 observation)
{
    struct ShotObj obj, before;
    u8 next_before[8][3];
    u32 i, variant = raw ? 0 : 1;
    s16 x = sigma_head_formation_end[5][variant][0], y = sigma_head_formation_end[5][variant][1];
    memset(&obj, 0, sizeof(obj));
    memcpy(next_before, sigma_head_formation_next, sizeof(next_before));
    assert(next_before[5][0] == 1 && next_before[5][1] == 0);
    if (raw)
        sigma_head_formation_next[5][0] = 0;
    obj.active = 0x41;
    obj.id = 53;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.unk15 = 0x27;
    obj.unk8C.bytes[2] = 5;
    obj.unk2 = variant;
    obj.x_pos.val = (x - 50) * 65536 + 0x1234;
    obj.y_pos.val = y * 65536 + 0x5678;
    obj.x_vel.val = 65536;
    before = obj;
    before.x_pos.val += 65536;
    obj.unk8C.bytes[1] = angle_to_point(OBJECT_HEADER(&before), x * 65536, y * 65536) ^ 0x10;
    before.unk8C.bytes[1] = obj.unk8C.bytes[1];
    sigma_head_move(&obj);
    before.x_pos.i.hi = x;
    before.y_pos.i.hi = y;
    before.unk6 = 0;
    before.unk5 = raw ? 3 : 8;
    if (!raw)
        before.unk15 = 0x40;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(next_before); i++)
        assert(((u8*)sigma_head_formation_next)[i] == (raw && i == 15 ? 0 : ((u8*)next_before)[i]));
    return observation == 0 ? (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)(u8)obj.unk15 << 16) : (u16)obj.x_pos.i.hi | ((u32)(u16)obj.y_pos.i.hi << 16);
}
static const u32 sigma_head_formation_context_cases_expected[] = { 0x400008u, 0x2580408u, 0x270003u, 0x2B80578u };
static u32 sigma_head_formation_context_cases_row(u32 row)
{
    return head_case(row / 2, row % 2);
}

static u32 volley_case(u32 mode)
{
    struct ShotObj obj, expected, pool_before[32];
    struct MainObj owner, owner_before;
    struct PlayerObj player_before = g_Player;
    struct Unk_unk68 box = { -2, -2, 4, 4 };
    u32 i, free_count = mode == 2 || mode == 4 ? 1 : mode == 3 || mode == 5 ? 4
                                                                            : 0;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(shot_objects, 0, sizeof(shot_objects));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    for (i = 0; i < 32; i++) {
        shot_objects[i].active = i >= 32 - free_count ? 0 : 1;
        shot_objects[i].id = 39;
        shot_objects[i].state = 40;
        shot_objects[i].unk2 = 9;
        shot_objects[i].unk5 = 3;
        shot_objects[i].unk6 = 4;
        shot_objects[i].unk7 = 5;
        shot_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        shot_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
        shot_objects[i].unk50.data = (const u8*)&box;
        shot_objects[i].unk54 = (const u8*)&box;
        shot_objects[i].unk68 = &box;
        shot_objects[i].unk98 = shot_objects[i].unk61 = shot_objects[i].unk64 = shot_objects[i].unk65 = shot_objects[i].unk66 = 7;
        shot_objects[i].unk72 = shot_objects[i].unk73 = shot_objects[i].unk74 = shot_objects[i].unk76 = shot_objects[i].unk77 = shot_objects[i].unk78 = 7;
        shot_objects[i].unk62 = shot_objects[i].unk63 = shot_objects[i].unk7A = shot_objects[i].unk75 = 7;
    }
    owner.active = 0x41;
    owner.id = 74;
    owner.state = 1;
    obj.active = 0x41;
    obj.id = 53;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 4;
    obj.timer = mode ? 1 : 2;
    obj.unk8A = mode >= 4 ? 1 : 2;
    obj.unk7C = WEAPON_OBJECT(&owner);
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    expected = obj;
    owner_before = owner;
    memcpy(pool_before, shot_objects, sizeof(pool_before));
    expected.timer = mode ? 40 : 1;
    if (mode) {
        expected.unk8A--;
        if (mode >= 4) {
            expected.unk5 = 3;
            expected.unk6 = 0;
            owner_before.ext.main_74.unk8E = 1;
        } else
            expected.unk6 = 3;
        for (i = 0; i < free_count; i++) {
            struct ShotObj* child = &pool_before[32 - free_count + i];
            child->active = 0x41;
            child->id = 54;
            child->unk2 = 0;
            child->unk7 = i;
            child->x_pos = obj.x_pos;
            child->y_pos = obj.y_pos;
            child->unk7C = WEAPON_OBJECT(&owner);
            child->unk50.data = NULL;
            child->unk54 = NULL;
            child->unk68 = NULL;
            child->unk98 = child->unk61 = child->unk64 = child->unk65 = child->unk66 = 0;
            child->unk72 = child->unk73 = child->unk74 = child->unk76 = child->unk77 = child->unk78 = 0;
            child->unk62 = child->unk63 = child->unk7A = child->unk75 = 0;
        }
    }
    sigma_head_fire_wall_shoot(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    return (u16)obj.timer | ((u32)(u8)obj.unk6 << 16) | ((u32)owner.ext.main_74.unk8E << 24);
}
static const u32 sigma_head_wall_volley_pools_cases_expected[] = { 0x40001u, 0x30028u, 0x30028u, 0x30028u, 0x1000028u, 0x1000028u };

static const u32 sigma_head_move_expected[] = { 0x40u, 9u, 0u, 0x498u, 0x2A8u };
static u32 test_sigma_head_move(u32 row)
{
    u32 observed_values[5];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk8C.bytes[2] = 4;
    obj.unk2 = 2;
    obj.unk8C.bytes[1] = 0;
    sigma_head_move(&obj);
    observed_values[0] = (u32)obj.unk15;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.x_pos.i.hi;
    observed_values[4] = (u32)obj.y_pos.i.hi;
    return c_test_observe(0, row, observed_values, sigma_head_move_expected, 5);
}

#include "support/state_cases.h"

static struct MainObj head_owner;
#define ss state_room.shot
#define HEAD(phase) (state_reset(3, phase, 0), memset(&head_owner, 0, sizeof(head_owner)), ss.unk7C = (struct WeaponObj*)&head_owner, ss.x_pos.i.hi = 0x500, ss.y_pos.i.hi = 0x280)
#define HEAD_SEEN() (state_extra = (u16)ss.timer | (u32)(u8)ss.unk8A << 16 | (u32)head_owner.ext.main_74.unk8E << 24)
static void sh_shift_start(void)
{
    HEAD(0);
    sigma_head_shift(&ss);
    HEAD_SEEN();
}
static void sh_shift_move(void)
{
    HEAD(1);
    ss.x_vel.val = 0x20000;
    ss.unk28 = 0x6000000;
    sigma_head_shift(&ss);
}
static void sh_shift_arrive(void)
{
    HEAD(1);
    ss.x_vel.val = 0x20000;
    ss.unk28 = 0x5000000;
    sigma_head_shift(&ss);
}
static void sh_bolt_start(void)
{
    HEAD(0);
    sigma_head_lightning(&ss);
    HEAD_SEEN();
}
static void sh_bolt_wait(void)
{
    HEAD(1);
    ss.timer = 2;
    sigma_head_lightning(&ss);
    HEAD_SEEN();
}
static void sh_bolt_fire(void)
{
    HEAD(1);
    ss.timer = 1;
    ss.unk8A = 3;
    sigma_head_lightning(&ss);
    HEAD_SEEN();
}
static void sh_bolt_last(void)
{
    HEAD(1);
    ss.timer = 1;
    ss.unk8A = 1;
    sigma_head_lightning(&ss);
    HEAD_SEEN();
}
static void sh_freeze_start(void)
{
    HEAD(0);
    sigma_head_freeze(&ss);
    HEAD_SEEN();
}
static void sh_freeze_open(void)
{
    HEAD(1);
    sigma_head_freeze(&ss);
}
static void sh_freeze_opening(void)
{
    HEAD(1);
    ss.animation_step.fields.relative_step = 1;
    sigma_head_freeze(&ss);
}
static void sh_freeze_drop(void)
{
    HEAD(2);
    ss.timer = 1;
    ss.x_vel.val = -0x10000;
    sigma_head_freeze(&ss);
    HEAD_SEEN();
}
static void sh_freeze_glide(void)
{
    HEAD(2);
    ss.timer = 3;
    ss.x_vel.val = -0x10000;
    sigma_head_freeze(&ss);
    HEAD_SEEN();
}
static void sh_freeze_edge(void)
{
    HEAD(2);
    ss.timer = 3;
    ss.x_pos.i.hi = 0x4D0;
    sigma_head_freeze(&ss);
    HEAD_SEEN();
}
static void sh_chomp_start(void)
{
    HEAD(0);
    sigma_head_chomp(&ss);
}
static void sh_chomp_bite(void)
{
    HEAD(1);
    ss.animation_step.fields.event = 1;
    ss.animation_step.fields.relative_step = 1;
    sigma_head_chomp(&ss);
}
static void sh_chomp_done(void)
{
    HEAD(1);
    sigma_head_chomp(&ss);
}
static void sh_idle_wait(void)
{
    HEAD(0);
    ss.unk7 = 2;
    func_800AB050(&ss);
}
static void sh_idle_call(void)
{
    HEAD(0);
    head_owner.ext.main_74.unk8C = 1;
    func_800AB050(&ss);
}
static void sh_idle_leave(void)
{
    HEAD(0);
    ss.unk8C.bytes[0] = 1;
    head_owner.ext.main_74.unk8C = 3;
    func_800AB050(&ss);
}
static void sh_idle_bolt(void)
{
    HEAD(0);
    ss.unk8C.bytes[0] = 1;
    head_owner.ext.main_74.unk8C = 2;
    func_800AB050(&ss);
}
static void sh_idle_freeze(void)
{
    HEAD(0);
    ss.unk8C.bytes[0] = 1;
    ss.unk8C.bytes[2] = 1;
    ss.unk2 = 1;
    head_owner.ext.main_74.unk8C = 2;
    func_800AB050(&ss);
}
static void sh_idle_chomp(void)
{
    HEAD(0);
    ss.unk8C.bytes[0] = 1;
    ss.unk8C.bytes[2] = 2;
    ss.unk2 = 2;
    head_owner.ext.main_74.unk8C = 2;
    func_800AB050(&ss);
}

static void (*const sigma_head_states_cases[])(void) = {
    sh_shift_start,
    sh_shift_move,
    sh_shift_arrive,
    sh_bolt_start,
    sh_bolt_wait,
    sh_bolt_fire,
    sh_bolt_last,
    sh_freeze_start,
    sh_freeze_open,
    sh_freeze_opening,
    sh_freeze_drop,
    sh_freeze_glide,
    sh_freeze_edge,
    sh_chomp_start,
    sh_chomp_bite,
    sh_chomp_done,
    sh_idle_wait,
    sh_idle_call,
    sh_idle_leave,
    sh_idle_bolt,
    sh_idle_freeze,
    sh_idle_chomp,
};
static const u32 sigma_head_states_expected[] = { 0x10300u, 0xFF000000u, 0x5000000u, 0x2800000u, 0x20000u, 0u, 0x5700000u, 0x50000u, 0u, 0u, 0x10300u, 0u, 0x5020000u, 0x2800000u, 0x20000u, 0u, 0x6000000u, 0x40000u, 0u, 0u, 0x300u, 0u, 0x5000000u, 0x2800000u, 0x20000u, 0u, 0x5000000u, 0x40000u, 0u, 0u, 0x10300u, 0u, 0x5000000u, 0x2800000u, 0u, 0u, 0u, 0x50000u, 0x60001u, 0u, 0x10300u, 0u, 0x5000000u, 0x2800000u, 0u, 0u, 0u, 0x50000u, 1u, 0u, 0x10300u, 0u, 0x5000000u, 0x2800000u, 0u, 0u, 0u, 0x50000u, 0x2001Eu, 0x41410000u, 0x300u, 0u, 0x5000000u, 0x2800000u, 0u, 0u, 0u, 0x50000u, 0x100001Eu, 0x41410000u, 0x10300u, 0xFF000000u, 0x5000000u, 0x2800000u, 0xFFFF0000u, 0u, 0u, 0x50000u, 1u, 0u, 0x20300u, 0u, 0x5000000u, 0x2800000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10300u, 0u, 0x5000000u, 0x2800000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x20300u, 0u, 0x4FF0000u, 0x2800000u, 0xFFFF0000u, 0u, 0u, 0x50000u, 6u, 0x410000u, 0x20300u, 0u, 0x4FF0000u, 0x2800000u, 0xFFFF0000u, 0u, 0u, 0x50000u, 2u, 0u, 0x300u, 0u, 0x4D00000u, 0x2800000u, 0u, 0u, 0u, 0x50000u, 0x1000002u, 0u, 0x10300u, 0xFF000000u, 0x5000000u, 0x2800000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x10300u, 0u, 0x5000000u, 0x2800000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x300u, 0u, 0x5000000u, 0x2800000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x1000300u, 0u, 0x5000000u, 0x2800000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x200u, 0u, 0x5000000u, 0x2800000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x700u, 0u, 0x5000000u, 0x2800000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x400u, 0u, 0x5000000u, 0x2800000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x500u, 0x100u, 0x5000000u, 0x2800000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x600u, 0x200u, 0x5000000u, 0x2800000u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_sigma_head_states(u32 row)
{
    return object_run(sigma_head_states_cases[row], row, &sigma_head_states_expected[row * 10]);
}

static struct WeaponObj signal_owner;
#define ss state_room.shot
#define SIGNAL_HEAD(signal, st) (state_reset(0, 0, 0), memset(&signal_owner, 0, sizeof(signal_owner)), signal_owner.unk94 = signal, signal_owner.ext.weapon_6.direction = 3, ss.active = 1, ss.state = st, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60, ss.unk7C = &signal_owner, sigma_head_update(&ss), state_extra = ss.unk5C | signal_owner.ext.weapon_6.direction << 8)
static void sh_destroyed(void)
{
    SIGNAL_HEAD(2, 1);
}
static void sh_reform(void) { SIGNAL_HEAD(1, 1); }
static void sh_despawn(void) { SIGNAL_HEAD(0, 2); }

static void (*const sigma_head_signals_cases[])(void) = {
    sh_destroyed,
    sh_reform,
    sh_despawn,
};
static const u32 sigma_head_signals_expected[] = { 0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x300u, 0x2100u, 0x1000301u, 1u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x30u, 0x2100u, 0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x300u, 0u };

static u32 test_sigma_head_signals(u32 row)
{
    return object_run(sigma_head_signals_cases[row], row, &sigma_head_signals_expected[row * 10]);
}

void sigma_head_lightning_shoot(struct ShotObj*);
static struct ShotObj shots_expected[32];
static struct MiscObj misc_expected[64];
static u32 lightning(u32 row)
{
    struct ShotObj obj, expected;
    struct MainObj owner, owner_expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    u32 free_shot = row % 2, free_misc = row / 2 % 2, final = row / 4 % 2, wait = row / 8, i;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < 32; i++) {
        shot_objects[i].active = i == 31 && free_shot ? 0 : 1;
        shot_objects[i].id = 63;
        shot_objects[i].state = 5;
        shot_objects[i].unk2 = 9;
    }
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = i == 63 && free_misc ? 0 : 1;
        misc_objects[i].id = 63;
        misc_objects[i].state = 5;
        misc_objects[i].unk2 = 9;
    }
    c_test_copy_words((u32*)shots_expected, (u32*)shot_objects, sizeof(shots_expected) / 4);
    c_test_copy_words((u32*)misc_expected, (u32*)misc_objects, sizeof(misc_expected) / 4);
    owner.active = 0x41;
    owner.id = 74;
    owner.state = 1;
    owner_expected = owner;
    obj.active = 0x41;
    obj.id = 53;
    obj.unk2 = 1;
    obj.state = 1;
    obj.unk5 = 5;
    obj.unk6 = 1;
    obj.timer = wait ? 2 : 1;
    obj.unk8A = final ? 1 : 6;
    obj.unk7C = (struct WeaponObj*)&owner;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    expected = obj;
    expected.timer--;
    if (!wait) {
        expected.timer = 30;
        expected.unk8A--;
        if (final) {
            expected.unk5 = 3;
            expected.unk6 = 0;
            owner_expected.ext.main_74.unk8E = 1;
        }
        if (free_shot) {
            struct ShotObj* s = &shots_expected[31];
            s->active = 0x41;
            s->id = 54;
            s->unk2 = 1;
            s->x_pos = obj.x_pos;
            s->y_pos.val = obj.y_pos.val - 24 * 65536;
            s->unk7C = (struct WeaponObj*)&owner;
        }
        if (free_misc) {
            struct MiscObj* m = &misc_expected[63];
            m->active = 0x41;
            m->id = 55;
            m->unk2 = 3;
            m->x_pos = obj.x_pos;
            m->y_pos.val = obj.y_pos.val - 24 * 65536;
            m->ext.misc_55.owner = free_shot ? (struct MainObj*)&shot_objects[31] : NULL;
        }
    }
    D_8013E198[2] = -1;
    sigma_head_lightning_shoot(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_expected, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(c_test_word_difference((u32*)shot_objects, (u32*)shots_expected, sizeof(shots_expected) / 4) == 0 && c_test_word_difference((u32*)misc_objects, (u32*)misc_expected, sizeof(misc_expected) / 4) == 0);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "sigma_head_signals", 0, 0, COUNT(sigma_head_signals_cases), test_sigma_head_signals },
    { "sigma_head_states", 0, 0, COUNT(sigma_head_states_cases), test_sigma_head_states },
    { "sigma_head_formation_context", NULL, sigma_head_formation_context_cases_expected, COUNT(sigma_head_formation_context_cases_expected), sigma_head_formation_context_cases_row },
    { "sigma_head_wall_volley_pools", NULL, sigma_head_wall_volley_pools_cases_expected, COUNT(sigma_head_wall_volley_pools_cases_expected), volley_case },
    { "sigma_head_move", 0, 0, 1, test_sigma_head_move },
    { "independent_full_pools_sixth_bolt_and_waiting_tick", NULL, NULL, 16, lightning },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(sigma_head_signals_cases) + COUNT(sigma_head_states_cases) + COUNT(sigma_head_formation_context_cases_expected) + COUNT(sigma_head_wall_volley_pools_cases_expected) + 1 + 16;
