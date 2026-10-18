#include "test_runtime.h"
#include "main/mains/main_61_split_mushroom.h"
#include "main/55C4.h"
extern s16 split_mushroom_hop_speeds[4];
void split_mushroom_face_player(struct AnimatedObj*);

static u32 hop_case(u32 observation)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    s16 speeds_before[4];
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 61;
    obj.state = 1;
    obj.unk6 = 1;
    obj.unk7 = 0x27;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)split_mushroom_animations;
    set_animation(&obj, 0);
    obj.animation_step.fields.duration = 2;
    obj.animation_step.fields.event = 1;
    memcpy(speeds_before, split_mushroom_hop_speeds, sizeof(speeds_before));
    split_mushroom_hop_speeds[0] = -1;
    D_8013E198[2] = -1;
    before = obj;
    player_before = g_Player;
    func_8007A2B4(&obj);
    before.x_pos = obj.x_pos;
    before.y_pos = obj.y_pos;
    before.x_speed = obj.x_speed;
    before.y_speed = obj.y_speed;
    before.gravity = 0x3800;
    before.unk6 = 3;
    before.unk7 = 0;
    before.animation_step.fields.duration = 1;
    for (i = 0; i < sizeof(obj); i++)
        assert(((u8*)&obj)[i] == ((u8*)&before)[i]);
    for (i = 0; i < sizeof(g_Player); i++)
        assert(((u8*)&g_Player)[i] == ((u8*)&player_before)[i]);
    assert(split_mushroom_hop_speeds[0] == -1 && D_8013E198[2] == -1);
    for (i = 1; i < 4; i++)
        assert(split_mushroom_hop_speeds[i] == speeds_before[i]);
    switch (observation) {
    case 0:
        return obj.x_pos.val;
    case 1:
        return obj.y_pos.val;
    case 2:
        return obj.x_speed;
    case 3:
        return obj.y_speed;
    case 4:
        return obj.gravity;
    default:
        return obj.animation_step.packed;
    }
}
#define CASE(n)                                        \
    static u32 mushroom_hop_signed_speed_hop_##n(void) \
    {                                                  \
        return hop_case(n);                            \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
#define ENTRY(n) mushroom_hop_signed_speed_hop_##n,
static const CTestCase mushroom_hop_signed_speed_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) };
static const u32 mushroom_hop_signed_speed_cases_expected[] = { 0x1471234u, 0xC85678u, 0xE30000u, 0xFFFFC800u, 0x3800u, 0x10101u };
#undef CASE
#undef ENTRY

static u32 reunion_case(u32 mode, u32 observation)
{
    struct MainObj obj, partner, before, partner_before;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&partner, 0, sizeof(partner));
    obj.active = 0x41;
    obj.id = 61;
    obj.state = 1;
    obj.on_screen = 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    partner.x_pos = obj.x_pos;
    partner.y_pos.val = (mode ? 204 : 196) * 65536 + 0x5678;
    partner.ext.main_61.split = 0x27;
    obj.ext.main_61.partner = &partner;
    before = obj;
    partner_before = partner;
    func_80079824(&obj);
    before.x_pos = obj.x_pos;
    before.y_pos = obj.y_pos;
    before.x_speed = obj.x_speed;
    before.y_speed = obj.y_speed;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(partner) / 4; i++)
        assert(((u32*)&partner)[i] == ((u32*)&partner_before)[i]);
    if (observation == 0)
        return obj.x_pos.val;
    if (observation == 1)
        return obj.y_pos.val;
    if (observation == 2)
        return obj.x_speed;
    return obj.y_speed;
}
#define CASE(m, n)                                               \
    static u32 mushroom_reunion_vertical_reunion_##m##_##n(void) \
    {                                                            \
        return reunion_case(m, n);                               \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1) CASE(m, 2) CASE(m, 3)
MODE(0)
MODE(1)
#define ENTRY(m, n) mushroom_reunion_vertical_reunion_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1) ENTRY(m, 2) ENTRY(m, 3)
static const CTestCase mushroom_reunion_vertical_cases[]
    = { ENTRIES(0) ENTRIES(1) };
static const u32 mushroom_reunion_vertical_cases_expected[] = { 0x641234u, 0xC45678u, 0x0u, 0x40000u, 0x641234u, 0xCC5678u, 0x0u, 0xFFFC0000u };
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

static u32 intro_case(u32 mode)
{
    struct MainObj obj, before;
    struct EffectObj pool_before[32];
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u32 i, triggered = mode >= 2, free_slot = mode == 3 || mode == 5;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(effect_objects, 0, sizeof(effect_objects));
    for (i = 0; i < 32; i++) {
        effect_objects[i].active = 1;
        effect_objects[i].id = 0x27;
        effect_objects[i].state = 0x28;
    }
    if (free_slot)
        effect_objects[17].active = 0;
    obj.active = 0x41;
    obj.id = 61;
    obj.state = 1;
    obj.unk6 = 0;
    obj.unk7 = 0x25;
    engine_obj.stage = mode < 4 ? 3 : 12;
    engine_obj.cur_character = mode == 1 || mode == 2 ? 1 : 0;
    g_Player.y_pos.i.hi = mode == 0 ? 0x1CC : mode == 1 ? 0x1CB
                                                        : 0x1CA;
    g_Player.script_state = -1;
    g_Player.script_action = 0x26;
    g_Player.script_facing = 0x27;
    before = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(pool_before, effect_objects, sizeof(pool_before));
    split_mushroom_intro_wait_player(&obj);
    if (triggered) {
        before.unk6 = 1;
        player_before.script_state = 1;
        player_before.script_action = 0x14;
        player_before.script_facing = mode < 4 ? 0 : 0x40;
        player_before.spike_immune = 1;
        engine_before.gameplay_locked = 1;
        if (free_slot) {
            before.ext.main_61.data.effect = &effect_objects[17];
            pool_before[17].active = 1;
            pool_before[17].id = 0x18;
        }
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)effect_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    return (u8)obj.unk6 | ((u32)(u8)g_Player.script_facing << 8) | ((u32)effect_objects[17].id << 16);
}
#define CASE(m)                                           \
    static u32 split_mushroom_intro_pools_intro_##m(void) \
    {                                                     \
        return intro_case(m);                             \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
#define ENTRY(m) split_mushroom_intro_pools_intro_##m,
static const CTestCase split_mushroom_intro_pools_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) };
static const u32 split_mushroom_intro_pools_cases_expected[] = { 0x272700u, 0x272700u, 0x270001u, 0x180001u, 0x274001u, 0x184001u };
#undef CASE
#undef ENTRY

struct func_80079824_case {
    u32 obj_x_pos_hi, child_0_x_pos_hi, obj_y_pos_hi, child_0_y_pos_hi;
    u32 expected[4];
};
static const struct func_80079824_case func_80079824_cases[] = {
    { 0, 0, 0, 0, { 0u, 0u, 0u, 0u } },
    { 4350, 4352, 13376, 13378, { 0u, 0u, 0u, 0u } },
    { -8192, 16, 0, 0, { 0u, 0u, 0x40000u, 0u } },
};
static u32 test_func_80079824(u32 row)
{
    const struct func_80079824_case* c = &func_80079824_cases[row];
    u32 observed_values[4];
    struct MainObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    child_0_present = 255;
    obj.x_pos.i.hi = c->obj_x_pos_hi;
    child_0.x_pos.i.hi = c->child_0_x_pos_hi;
    obj.y_pos.i.hi = c->obj_y_pos_hi;
    child_0.y_pos.i.hi = c->child_0_y_pos_hi;
    obj.ext.main_61.partner = child_0_present ? &child_0 : NULL;
    func_80079824(&obj);
    observed_values[0] = (u32)child_0.ext.main_61.split;
    observed_values[1] = (u32)obj.on_screen;
    observed_values[2] = (u32)obj.x_speed;
    observed_values[3] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

static const u32 split_mushroom_death_explode_expected[] = { 1u, 0u, 0u, 0u, 0u, 0x8000u, 2u, 0u, 5u };
static u32 test_split_mushroom_death_explode(u32 row)
{
    u32 observed_values[9];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&effect_objects, 0, sizeof(effect_objects));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk7C = 1;
    pool_0_full = 255;
    obj.invincibility_timer = 31;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            effect_objects[slot].active = pool_0_full ? 1 : 0;
    }
    split_mushroom_death_explode(&obj);
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)effect_objects[0].x_pos.i.hi;
    observed_values[3] = (u32)effect_objects[0].y_pos.i.hi;
    observed_values[4] = (u32)obj.invincibility_timer;
    observed_values[5] = (u32)obj.unk42;
    observed_values[6] = (u32)obj.unk5;
    observed_values[7] = (u32)obj.unk7C;
    observed_values[8] = (u32)obj.unk7E;
    return c_test_observe(0, row, observed_values, split_mushroom_death_explode_expected, 9);
}

struct split_mushroom_face_player_case {
    u32 x_pos;
    u32 expected[1];
};
static const struct split_mushroom_face_player_case split_mushroom_face_player_cases[] = {
    { 1, { 0u } },
    { 0, { 0x40u } },
};
static u32 test_split_mushroom_face_player(u32 row)
{
    const struct split_mushroom_face_player_case* c = &split_mushroom_face_player_cases[row];
    u32 observed_values[1];
    struct AnimatedObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.x_pos.val = c->x_pos;
    g_Player.x_pos.val = 0;
    split_mushroom_face_player(&obj);
    observed_values[0] = (u32)obj.unk15;
    return c_test_observe(0, row, observed_values, c->expected, 1);
}

static const u32 split_mushroom_stun_wait_expected[] = { 0u, 0x3800u, 0u, 2u, 0u, 0u, 0u, 0u };
static u32 test_split_mushroom_stun_wait(u32 row)
{
    u32 observed_values[8];
    struct MainObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    obj.unk7C = 1;
    child_0_present = 0;
    obj.ext.main_61.partner = child_0_present ? &child_0 : NULL;
    split_mushroom_stun_wait(&obj);
    observed_values[0] = (u32)obj.ext.main_61.blink_timer;
    observed_values[1] = (u32)obj.gravity;
    observed_values[2] = (u32)obj.unk15;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.unk7C;
    observed_values[5] = (u32)obj.x_accel;
    observed_values[6] = (u32)obj.x_speed;
    observed_values[7] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, split_mushroom_stun_wait_expected, 8);
}

#include "support/boss_death_flash.h"
BOSS_DEATH_FLASH_TESTS(split_mushroom_death_flash, split_mushroom_death_explode, 2)

#include "support/pool_full.h"
static u32 pool_full_split_mushroom_spawn_afterimage(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    split_mushroom_spawn_afterimage(&pf_self);
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_split_mushroom_spawn_afterimage,
};

static const u32 split_mushroom_death_flash_cases_expected[] = { 0x10501u, 0x10502u, 0x10502u, 0x50001u, 0xF0F01u, 0x5FB01u, 0x50001u };
static const u32 pool_full_cases_expected[] = { 0x50000u };
const struct CTestGroup c_test_groups[] = {
    { "mushroom_hop_signed_speed", mushroom_hop_signed_speed_cases, mushroom_hop_signed_speed_cases_expected, COUNT(mushroom_hop_signed_speed_cases), 0 },
    { "mushroom_reunion_vertical", mushroom_reunion_vertical_cases, mushroom_reunion_vertical_cases_expected, COUNT(mushroom_reunion_vertical_cases), 0 },
    { "split_mushroom_intro_pools", split_mushroom_intro_pools_cases, split_mushroom_intro_pools_cases_expected, COUNT(split_mushroom_intro_pools_cases), 0 },
    { "func_80079824", 0, 0, 3, test_func_80079824 },
    { "split_mushroom_death_explode", 0, 0, 1, test_split_mushroom_death_explode },
    { "split_mushroom_face_player", 0, 0, 2, test_split_mushroom_face_player },
    { "split_mushroom_stun_wait", 0, 0, 1, test_split_mushroom_stun_wait },
    { "split_mushroom_death_flash", split_mushroom_death_flash_cases, split_mushroom_death_flash_cases_expected, COUNT(split_mushroom_death_flash_cases), 0 },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(mushroom_hop_signed_speed_cases) + COUNT(mushroom_reunion_vertical_cases) + COUNT(split_mushroom_intro_pools_cases) + 3 + 1 + 2 + 1 + COUNT(split_mushroom_death_flash_cases) + COUNT(pool_full_cases);
