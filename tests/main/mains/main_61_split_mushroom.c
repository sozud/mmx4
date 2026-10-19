#include "test_runtime.h"
#include "main/mains/main_61_split_mushroom.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
void split_mushroom_combo(struct MainObj* arg0);
void split_mushroom_spore_rain(struct MainObj* arg0);
void split_mushroom_wall_jump(struct MainObj* arg0);
void func_8007877C(struct MainObj*);
void split_mushroom_stun(struct MainObj* arg0);
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
static const u32 mushroom_hop_signed_speed_cases_expected[] = { 0x1471234u, 0xC85678u, 0xE30000u, 0xFFFFC800u, 0x3800u, 0x10101u };

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
static const u32 mushroom_reunion_vertical_cases_expected[] = { 0x641234u, 0xC45678u, 0x0u, 0x40000u, 0x641234u, 0xCC5678u, 0x0u, 0xFFFC0000u };
static u32 mushroom_reunion_vertical_cases_row(u32 row)
{
    return reunion_case(row / 4, row % 4);
}

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
static const u32 split_mushroom_intro_pools_cases_expected[] = { 0x272700u, 0x272700u, 0x270001u, 0x180001u, 0x274001u, 0x184001u };

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
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    obj.x_pos.i.hi = c->obj_x_pos_hi;
    child_0.x_pos.i.hi = c->child_0_x_pos_hi;
    obj.y_pos.i.hi = c->obj_y_pos_hi;
    child_0.y_pos.i.hi = c->child_0_y_pos_hi;
    obj.ext.main_61.partner = &child_0;
    func_80079824(&obj);
    observed_values[0] = (u32)child_0.ext.main_61.split;
    observed_values[1] = (u32)obj.on_screen;
    observed_values[2] = (u32)obj.x_speed;
    observed_values[3] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 4);
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
#include "support/state_cases.h"

static struct MainObj mushroom_partner;
static u32 mushroom_pages[3];
static s32 mushroom_frames[8];
static Palette mushroom_bank[60];
static Palette mushroom_palettes[70];
#define SPLIT(a, b) (state_reset(a, b, 0), memset(&mushroom_partner, 0, sizeof(mushroom_partner)), so.ext.main_61.partner = &mushroom_partner)
#define MUSHROOM() (state_extra = so.ext.main_61.split | so.ext.main_61.merge << 8 | so.ext.main_61.blink_timer << 16 | (u32)mushroom_partner.unk5 << 24)
static void sm_init_highway(void)
{
    SPLIT(0, 0);
    D_801406A8 = mushroom_pages;
    TEST_PALETTE_BANK = (u8*)mushroom_bank;
    TEST_PALETTE = (u8*)mushroom_palettes;
    engine_obj.stage = 3;
    func_8007877C(&so);
    MUSHROOM();
}
static void sm_init_rematch(void)
{
    SPLIT(0, 0);
    D_801406A8 = mushroom_pages;
    TEST_MENU_FRAMES = (u8*)mushroom_frames;
    TEST_PALETTE_BANK = (u8*)mushroom_bank;
    TEST_PALETTE = (u8*)mushroom_palettes;
    engine_obj.stage = 0xC;
    func_8007877C(&so);
}
static void sm_stun_start(void)
{
    SPLIT(2, 0);
    so.unk7E = 1;
    so.animation_step.fields.event = 1;
    split_mushroom_stun(&so);
}
static void sm_stun_start_clone(void)
{
    SPLIT(2, 0);
    so.unk2 = 1;
    split_mushroom_stun(&so);
}
static void sm_stun_wait(void)
{
    SPLIT(2, 1);
    so.unk7C = 2;
    split_mushroom_stun(&so);
}
static void sm_stun_wait_whole(void)
{
    SPLIT(2, 1);
    so.unk7C = 1;
    split_mushroom_stun(&so);
}
static void sm_stun_wait_merge(void)
{
    SPLIT(2, 1);
    so.unk7C = 1;
    so.ext.main_61.split = 1;
    so.ext.main_61.merge = 1;
    split_mushroom_stun(&so);
}
static void sm_stun_wait_clone_merge(void)
{
    SPLIT(2, 1);
    so.unk7C = 1;
    so.ext.main_61.split = 1;
    so.unk2 = 1;
    mushroom_partner.ext.main_61.merge = 1;
    mushroom_partner.unk15 = 0x40;
    split_mushroom_stun(&so);
    MUSHROOM();
}
static void sm_stun_wait_split(void)
{
    SPLIT(2, 1);
    so.unk7C = 1;
    so.ext.main_61.split = 1;
    so.unk2 = 1;
    split_mushroom_stun(&so);
}
static void sm_stun_fall(void)
{
    SPLIT(2, 2);
    so.collision_flags = 8;
    split_mushroom_stun(&so);
}
static void sm_stun_falling(void)
{
    SPLIT(2, 2);
    so.y_speed = -0x10000;
    split_mushroom_stun(&so);
}
static void sm_stun_merge(void)
{
    SPLIT(2, 3);
    split_mushroom_stun(&so);
    MUSHROOM();
}
static void sm_stun_merge_wait(void)
{
    SPLIT(2, 3);
    so.ext.main_61.split = 1;
    split_mushroom_stun(&so);
}
static void sm_stun_land(void)
{
    SPLIT(2, 5);
    so.collision_flags = 8;
    split_mushroom_stun(&so);
}
static void sm_stun_land_fall(void)
{
    SPLIT(2, 5);
    so.y_speed = -0x10000;
    split_mushroom_stun(&so);
}
static void sm_split_center(void)
{
    SPLIT(2, 6);
    so.unk7C = 1;
    so.x_pos.i.hi = 0x40;
    split_mushroom_stun(&so);
    MUSHROOM();
}
static void sm_split_edge(void)
{
    SPLIT(2, 6);
    so.unk7C = 1;
    so.x_pos.i.hi = 0x100;
    split_mushroom_stun(&so);
}
static void sm_split_mirror(void)
{
    SPLIT(2, 6);
    so.unk7C = 1;
    mushroom_partner.unk5 = 6;
    mushroom_partner.unk15 = 0x40;
    split_mushroom_stun(&so);
}
static void sm_split_wait(void)
{
    SPLIT(2, 6);
    so.unk7C = 2;
    split_mushroom_stun(&so);
}
static void sm_sync_time(void)
{
    SPLIT(6, 5);
    so.unk7C = 1;
    split_mushroom_combo(&so);
}
static void sm_sync_partner(void)
{
    SPLIT(6, 5);
    so.unk7C = 3;
    so.unk2 = 1;
    mushroom_partner.unk5 = 6;
    mushroom_partner.unk6 = 5;
    split_mushroom_combo(&so);
    MUSHROOM();
}
static void sm_sync_wait(void)
{
    SPLIT(6, 5);
    so.unk7C = 3;
    so.unk2 = 1;
    split_mushroom_combo(&so);
}
static void sm_hop_land(void)
{
    SPLIT(6, 1);
    so.collision_flags = 8;
    split_mushroom_combo(&so);
}
static void sm_hop_land_split(void)
{
    SPLIT(6, 1);
    so.collision_flags = 8;
    so.unk7 = 1;
    so.ext.main_61.split_done = 1;
    split_mushroom_combo(&so);
}
static void sm_hop_rise(void)
{
    SPLIT(6, 1);
    so.y_speed = 0x10000;
    so.ext.main_61.stunned = 1;
    split_mushroom_combo(&so);
}
static void sm_hop_near(void)
{
    SPLIT(6, 1);
    so.ext.main_61.combo_count = 1;
    so.x_pos.i.hi = 0x10;
    split_mushroom_combo(&so);
}
static void sm_hop_wall_left(void)
{
    SPLIT(6, 1);
    so.ext.main_61.combo_count = 1;
    so.unk7E = 1;
    so.collision_flags = 2;
    split_mushroom_combo(&so);
}
static void sm_hop_wall_right(void)
{
    SPLIT(6, 1);
    so.ext.main_61.combo_count = 1;
    so.unk7E = 1;
    so.unk15 = 0x40;
    so.collision_flags = 1;
    split_mushroom_combo(&so);
}
static void sm_spore_split_a(void)
{
    SPLIT(3, 2);
    so.unk7C = 1;
    main_objects[0x2F].active = 0;
    cur_random = 1;
    split_mushroom_spore_rain(&so);
}
static void sm_spore_split_b(void)
{
    SPLIT(3, 2);
    so.unk7C = 1;
    main_objects[0x2F].active = 0;
    cur_random = 2;
    split_mushroom_spore_rain(&so);
}
static void sm_spore_wait(void)
{
    SPLIT(3, 2);
    so.unk7C = 2;
    split_mushroom_spore_rain(&so);
}
static void sm_wall_jump(void)
{
    SPLIT(7, 0);
    so.animation_step.fields.event = 1;
    so.x_pos.i.hi = 0x40;
    split_mushroom_wall_jump(&so);
}
static void sm_wall_jump_far(void)
{
    SPLIT(7, 0);
    so.animation_step.fields.event = 1;
    so.x_pos.i.hi = 0x100;
    split_mushroom_wall_jump(&so);
}
static void sm_wall_air_turn(void)
{
    SPLIT(7, 1);
    so.y_speed = 0x10000;
    so.gravity = 0x20000;
    split_mushroom_wall_jump(&so);
}
static void sm_wall_air_left(void)
{
    SPLIT(7, 1);
    so.unk7 = 1;
    so.collision_flags = 2;
    split_mushroom_wall_jump(&so);
}
static void sm_wall_air_right(void)
{
    SPLIT(7, 1);
    so.unk7 = 1;
    so.unk15 = 0x40;
    so.collision_flags = 1;
    split_mushroom_wall_jump(&so);
}
static void sm_wall_shot(void)
{
    SPLIT(7, 3);
    so.unk7C = 1;
    so.unk7E = 2;
    split_mushroom_wall_jump(&so);
}
static void sm_wall_shot_last(void)
{
    SPLIT(7, 3);
    so.unk7C = 1;
    split_mushroom_wall_jump(&so);
}

static void (*const split_mushroom_states_cases[])(void) = {
    sm_init_highway,
    sm_init_rematch,
    sm_stun_start,
    sm_stun_start_clone,
    sm_stun_wait,
    sm_stun_wait_whole,
    sm_stun_wait_merge,
    sm_stun_wait_clone_merge,
    sm_stun_wait_split,
    sm_stun_fall,
    sm_stun_falling,
    sm_stun_merge,
    sm_stun_merge_wait,
    sm_stun_land,
    sm_stun_land_fall,
    sm_split_center,
    sm_split_edge,
    sm_split_mirror,
    sm_split_wait,
    sm_sync_time,
    sm_sync_partner,
    sm_sync_wait,
    sm_hop_land,
    sm_hop_land_split,
    sm_hop_rise,
    sm_hop_near,
    sm_hop_wall_left,
    sm_hop_wall_right,
    sm_spore_split_a,
    sm_spore_split_b,
    sm_spore_wait,
    sm_wall_jump,
    sm_wall_jump_far,
    sm_wall_air_turn,
    sm_wall_air_left,
    sm_wall_air_right,
    sm_wall_shot,
    sm_wall_shot_last,
};
static const u32 split_mushroom_states_expected[] = { 0x101u, 0xFF400000u, 0u, 0u, 0u, 0u, 0x380000u, 0x20000u, 0u, 0u, 0x101u, 0xFF000000u, 0u, 0u, 0u, 0u, 0x380000u, 0x27888u, 0u, 0u, 0x10200u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x200u, 0x100u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10200u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x20200u, 0u, 0u, 0u, 0u, 0u, 0x380000u, 0x50000u, 0u, 0u, 0x30200u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x40200u, 0x400100u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0xFF0001u, 0u, 0x50200u, 0x100u, 0u, 0u, 0u, 0u, 0x380000u, 0x50000u, 0u, 0u, 0x700u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x20200u, 0u, 0u, 0x10000u, 0u, 0xFFFF0000u, 0u, 0x50000u, 0u, 0u, 0x20200u, 0u, 0u, 0u, 0u, 0u, 0x380000u, 0x50000u, 0u, 0u, 0x30200u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x60200u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x50200u, 0u, 0u, 0x10000u, 0u, 0xFFFF0000u, 0u, 0x50000u, 0u, 0u, 0x70600u, 0xFF400000u, 0x400000u, 0u, 0u, 0u, 0u, 0x50000u, 1u, 0u, 0x70600u, 0xFF000000u, 0x1000000u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x70600u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x60200u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x40500u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x40500u, 0x100u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x5000000u, 0u, 0x50600u, 0x100u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x1050600u, 0xFF400000u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x1050600u, 0xFF400000u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x1010600u, 0xFF000000u, 0u, 0xFFFF0000u, 0u, 0x10000u, 0u, 0x50000u, 0u, 0u, 0x20600u, 0u, 0x100000u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x600u, 0x400000u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0x41000000u, 0x600u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0x41000000u, 0x30300u, 0xFF400000u, 0u, 0u, 0xFFFD4000u, 0u, 0x380000u, 0x50000u, 0u, 0u, 0x30300u, 0xFF000000u, 0u, 0u, 0x2C000u, 0u, 0x380000u, 0x50000u, 0u, 0u, 0x20300u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10700u, 0x400000u, 0x448000u, 0xFFF8F956u, 0x48000u, 0x6CEAAu, 0x380000u, 0x40000u, 0u, 0u, 0x10700u, 0u, 0xFB9556u, 0xFFF8F956u, 0xFFFB9556u, 0x6CEAAu, 0x380000u, 0x40000u, 0u, 0u, 0x1010700u, 0xFF000000u, 0u, 0xFFFF0000u, 0u, 0xFFFF0000u, 0x2000000u, 0x40000u, 0u, 0u, 0x1020700u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x1020700u, 0xFF400000u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x30700u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0x410000u, 0x40700u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_split_mushroom_states(u32 row)
{
    return object_run(split_mushroom_states_cases[row], row, &split_mushroom_states_expected[row * 10]);
}

#define MAIN(setup)                                                                                                                                       \
    do {                                                                                                                                                  \
        u8 immune = g_Player.spike_immune, delay = g_Player.update_delay_request;                                                                         \
        SPLIT(2, 1);                                                                                                                                      \
        mushroom_partner.animation_table = so.animation_table;                                                                                            \
        so.unk7C = 5;                                                                                                                                     \
        so.hp = 0x30;                                                                                                                                     \
        so.ext.main_61.active = 1;                                                                                                                        \
        so.ext.main_61.split_hits = 1;                                                                                                                    \
        so.x_pos.i.hi = 0x80;                                                                                                                             \
        so.y_pos.i.hi = 0x60;                                                                                                                             \
        cur_random = 0;                                                                                                                                   \
        setup;                                                                                                                                            \
        func_800788E4(&so);                                                                                                                               \
        state_extra = so.ext.main_61.flash_timer | so.ext.main_61.hit_lock << 8 | so.ext.main_61.stunned << 16 | (u32)so.ext.main_61.merge << 24;         \
        state_extra ^= so.ext.main_61.speed_level << 4 | (u32)mushroom_partner.unk5 << 12 | (u32)so.on_screen << 20 | (u32)mushroom_partner.active << 28; \
        g_Player.spike_immune = immune;                                                                                                                   \
        g_Player.update_delay_request = delay;                                                                                                            \
    } while (0)
static void smm_idle(void)
{
    MAIN();
}
static void smm_inactive(void) { MAIN(so.ext.main_61.active = 0); }
static void smm_tired(void) { MAIN(so.hp = 0x18); }
static void smm_paused(void) { MAIN((so.unk5 = 1, so.unk6 = 0)); }
static void smm_killed(void) { MAIN((state_hit(&so, 0, 0, 0x40))); }
static void smm_killed_split(void) { MAIN((state_hit(&so, 0, 0, 0x40), so.ext.main_61.split = 1, mushroom_partner.active = 1)); }
static void smm_hit(void) { MAIN((state_hit(&so, 0, 0, 1))); }
static void smm_hit_spores(void) { MAIN((state_hit(&so, 0, 0, 1), cur_random = 0x1234)); }
static void smm_hit_fast(void) { MAIN((state_hit(&so, 0x18, 0, 1))); }
static void smm_stun(void) { MAIN((state_hit(&so, 1, 0, 1))); }
static void smm_stun_split(void) { MAIN((state_hit(&so, 0xA, 0, 1), so.ext.main_61.split = 1)); }
static void smm_stun_split_again(void) { MAIN((state_hit(&so, 0x20, 0, 1), so.ext.main_61.split = 1, so.ext.main_61.split_hits = 2)); }
static void smm_stunned(void) { MAIN((state_hit(&so, 1, 0, 1), so.ext.main_61.stunned = 1)); }
static void smm_reflect(void) { MAIN((state_hit(&so, 0, 0xFF, 1))); }
static void smm_locked(void) { MAIN((state_hit(&so, 0, 0, 1), so.ext.main_61.hit_lock = 1)); }
static void smm_whole(void) { MAIN((state_hit(&so, 0, 0, 1), so.ext.main_61.split = 0xFF)); }
static void smm_flash_end(void) { MAIN(so.ext.main_61.flash_timer = 1); }
static void smm_flash_odd(void) { MAIN(so.ext.main_61.flash_timer = 4); }
static void smm_flash_even(void) { MAIN(so.ext.main_61.flash_timer = 3); }
static void smm_blink_on(void) { MAIN(so.ext.main_61.blink_timer = 2); }
static void smm_blink_off(void) { MAIN(so.ext.main_61.blink_timer = 3); }
static void smm_clone_hit(void) { MAIN((so.unk2 = 1, state_hit(&so, 0, 0, 1))); }
static void smm_clone_killed(void) { MAIN((so.unk2 = 1, so.ext.main_61.split = 1, mushroom_partner.active = 1, state_hit(&so, 0, 0, 0x40))); }
static void smm_clone_stun(void) { MAIN((so.unk2 = 1, so.ext.main_61.split = 1, state_hit(&so, 1, 0, 1))); }

static void (*const split_mushroom_main_cases[])(void) = {
    smm_idle,
    smm_inactive,
    smm_tired,
    smm_paused,
    smm_killed,
    smm_killed_split,
    smm_hit,
    smm_hit_spores,
    smm_hit_fast,
    smm_stun,
    smm_stun_split,
    smm_stun_split_again,
    smm_stunned,
    smm_reflect,
    smm_locked,
    smm_whole,
    smm_flash_end,
    smm_flash_odd,
    smm_flash_even,
    smm_blink_on,
    smm_blink_off,
    smm_clone_hit,
    smm_clone_killed,
    smm_clone_stun,
};
static const u32 split_mushroom_main_expected[] = { 0x10200u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x100000u, 0u, 0x10200u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x10200u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x100010u, 0u, 0x10100u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x100000u, 1u, 0x10002u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0u, 0x2100u, 0x10002u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0u, 0x2100u, 0x10200u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0x100040u, 0x412100u, 0x10200u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0x100040u, 0x2100u, 0x10200u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0x100106u, 0x412100u, 0x200u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0x110040u, 0x2100u, 0x200u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0x1112040u, 0x2100u, 0x200u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0x112040u, 0x2100u, 0x10200u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0x110040u, 0x2100u, 0x10200u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x100000u, 0x2100u, 0x10200u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x100000u, 0u, 0x10200u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x100000u, 0u, 0x10200u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x100000u, 0u, 0x10200u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0x100003u, 0u, 0x10200u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x100002u, 0u, 0x10200u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x100000u, 0u, 0x10200u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x10200u, 0x100u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x100000u, 0u, 0x10200u, 0x100u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x10100000u, 0u, 0x10200u, 0x100u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x100000u, 0u };

static u32 test_split_mushroom_main(u32 row)
{
    return object_run(split_mushroom_main_cases[row], row, &split_mushroom_main_expected[row * 10]);
}

void func_8007AE2C(struct MainObj*);
void split_mushroom_combo_swing(struct MainObj*);
extern void* split_mushroom_animations[26];
static struct MiscObj misc_expected[64];
static struct ShotObj shots_expected[32];
static u32 attack(u32 row)
{
    struct MainObj obj, expected, partner, partner_before;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj background_expected;
    u32 slam = row % 2, slots = row / 2 % 3, face = row / 6 % 2, layer = row / 12, available = slam && slots == 2 ? 4 : slots, i;
    engine_obj.stage = 3;
    engine_obj.substage = 1;
    engine_before = engine_obj;
    g_Player.bg_offset = layer;
    player_before = g_Player;
    background_objects[0].unk34 = 0;
    background_expected = background_objects[0];
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = !slam && i >= 64 - available ? 0 : 1;
    memcpy(misc_expected, misc_objects, sizeof(misc_expected));
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    for (i = 0; i < COUNT(shot_objects); i++)
        shot_objects[i].active = slam && i >= 32 - available ? 0 : 1;
    memcpy(shots_expected, shot_objects, sizeof(shots_expected));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 61;
    obj.state = 1;
    obj.hp = slam ? 24 : 48;
    obj.ext.main_61.split = 1;
    obj.ext.main_61.active = 1;
    obj.unk15 = face ? 0x40 : 0;
    obj.bg_offset = layer;
    obj.x_pos.i.hi = 5972;
    obj.y_pos.i.hi = 363;
    obj.animation_table = (const u8* const*)split_mushroom_animations;
    memset(&partner, 0, sizeof(partner));
    partner.active = 0x41;
    partner.id = 61;
    partner.unk2 = 1;
    partner.state = 1;
    partner.hp = 48;
    partner.ext.main_61.split = 1;
    partner.animation_table = obj.animation_table;
    partner.ext.main_61.partner = &obj;
    obj.ext.main_61.partner = &partner;
    partner_before = partner;
    D_8013E198[2] = -1;
    func_8007B6BC(ANIMATED_OBJECT(&obj));
    if (!slam) {
        for (i = 0; i < 39; i++)
            func_8007A4EC(&obj);
        assert(obj.unk5 == 5 && obj.unk6 == 0 && obj.unk7C == 1 && obj.unk7E == 3);
    } else {
        obj.unk6 = 2;
        obj.unk7C = 20;
        set_animation(&obj, 7);
        for (i = 0; i < 20; i++)
            split_mushroom_combo_swing(&obj);
        assert(obj.unk5 == 6 && obj.unk6 == 3 && obj.animation_step.packed == 0x23000101 && obj.gravity == 0x3800);
        obj.collision_flags = 8;
    }
    expected = obj;
    expected.unk7C = slam ? 48 : 0;
    expected.unk6 = slam ? 4 : 1;
    expected.animation_cursor = (const u8*)split_mushroom_animations[slam ? 9 : 5] + (slam ? 0 : 16);
    expected.animation_step.packed = slam ? 0x24010002 : 0x1C010002;
    if (slam) {
        expected.unk17 = 9;
        expected.previous_animation_index = 255;
        expected.y_speed = -0x3800;
        background_expected.unk37 = 16;
        background_expected.unk46 = background_expected.unk3E.bytes[1] = 8;
        background_expected.unk3D = background_expected.unk3B = 2;
        background_expected.unk34 |= 1;
    } else {
        expected.x_speed = face ? 0x64E38 : (s32)0xFFF9B1C8;
        expected.y_speed = expected.gravity = 0;
    }
    for (i = 0; i < available; i++) {
        if (slam) {
            struct ShotObj* s = &shots_expected[32 - available + i];
            s->active = 0x41;
            s->id = 39;
            s->unk2 = i;
            s->unk40 = obj.unk40;
            s->unk42 = obj.unk42;
            s->animation_table = (u32**)obj.animation_table;
            s->unk3C = (void*)obj.sprite_frames;
            s->unk15 = obj.unk15;
            s->bg_offset = layer;
            s->x_pos = obj.x_pos;
            s->y_pos = obj.y_pos;
            s->unk7C = WEAPON_OBJECT(&obj);
        } else if (i == 0) {
            struct MiscObj* m = &misc_expected[64 - available];
            m->active = 0x41;
            m->id = 22;
            m->unk2 = 8;
            m->unk15 = obj.unk15;
            m->x_pos.i.hi = obj.x_pos.i.hi;
            m->y_pos.i.hi = obj.y_pos.i.hi;
            m->bg_offset = layer;
            m->animation_table = (u32**)obj.animation_table;
            m->unk40 = obj.unk40;
            m->unk3C = (void*)obj.sprite_frames;
            m->unk16 = 5;
            m->ext.misc_22.owner = &obj;
            m->ext.misc_22.timer = 36;
            m->unk42 = obj.unk42 & 0x7FFF;
            m->unk17 = 24;
            m->previous_animation_index = 255;
            m->animation_cursor = split_mushroom_animations[24];
            m->animation_step.packed = 0x78010001;
            m->unk6 = 1;
        }
    }
    if (slam)
        func_8007AE2C(&obj);
    else
        func_8007A4EC(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&partner, &partner_before, sizeof(partner));
    c_test_same_words(misc_objects, misc_expected, sizeof(misc_expected));
    c_test_same_words(shot_objects, shots_expected, sizeof(shots_expected));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&background_objects[0], &background_expected, sizeof(background_expected));
    assert(D_8013E198[2] == -1);
    return 1;
}

extern struct Unk_unk68 D_80107BF8[];
static const u8 weapons[] = { 0, 24, 25 };
static struct WeaponObj weapons_expected[16];
static struct VisualObj visuals_before[32];
#define SAME(a, b) assert(c_test_word_difference((const u32*)&(a), (const u32*)&(b), sizeof(a) / 4) == 0)
static u32 hit_visual_exhaustion(u32 row)
{
    struct MainObj obj, expected;
    struct MainObj* current = SP_CUR_MAIN_OBJ;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 weapon = weapons[row % 3], facing = row / 3 % 2, low = row / 6, i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.hp = 24;
    player_before = g_Player;
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 39;
    }
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    obj.active = 0x41;
    obj.id = 61;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.unk7C = 2;
    obj.on_screen = 7;
    obj.unk15 = facing ? 0x40 : 0;
    obj.unk42 = 0x9234;
    obj.hp = low ? 31 : 48;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.hurt_box = &split_mushroom_hurt_box;
    obj.attack_box = &split_mushroom_attack_box;
    obj.collision_data = D_80107BF8;
    obj.ext.main_61.active = 1;
    obj.ext.main_61.stunned = 1;
    obj.animation_table = (const u8* const*)split_mushroom_animations;
    set_animation(&obj, 19);
    weapon_objects[0].active = 0x21;
    weapon_objects[0].id = weapon;
    weapon_objects[0].unk15 = obj.unk15;
    weapon_objects[0].x_pos = obj.x_pos;
    weapon_objects[0].y_pos = obj.y_pos;
    weapon_objects[0].unk50 = (const u8*)&split_mushroom_hurt_box;
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    expected = obj;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.unk7C = 1;
    expected.hp--;
    expected.collision_data = D_801060F0;
    expected.on_screen = 1;
    expected.ext.main_61.speed_level = low;
    expected.ext.main_61.flash_timer = weapon == 0 ? 64 : 6;
    expected.ext.main_61.hit_lock = weapon != 0;
    ((s16*)&weapons_expected[0].unk80)[0] = facing ? 161 : 159;
    ((s16*)&weapons_expected[0].unk80)[1] = 121;
    weapons_expected[0].unk98 = weapon == 0;
    D_8013E198[0] = D_8013E198[1] = D_8013E198[5] = -1;
    cur_random = 0x1234;
    SP_CUR_MAIN_OBJ = &obj;
    func_800788E4(&obj);
    assert(SP_CUR_MAIN_OBJ == &obj);
    SP_CUR_MAIN_OBJ = current;
    SAME(obj, expected);
    SAME(g_Player, player_before);
    SAME(engine_obj, engine_before);
    SAME(background_objects, backgrounds_before);
    SAME(weapon_objects, weapons_expected);
    SAME(visual_objects, visuals_before);
    assert(cur_random == 0x366A);
    return 1;
}

extern void* split_mushroom_animations[26];
static struct ShotObj pool_expected[32];
static u32 spores(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before;
    u32 slots = row == 2 ? 5 : row, i;
    engine_obj.stage = 3;
    engine_obj.substage = 1;
    engine_before = engine_obj;
    D_8013E198[2] = -1;
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    for (i = 0; i < COUNT(shot_objects); i++)
        shot_objects[i].active = i >= 32 - slots ? 0 : 1;
    memcpy(pool_expected, shot_objects, sizeof(pool_expected));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 61;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 4;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)split_mushroom_animations;
    set_animation_frame(ANIMATED_OBJECT(&obj), 17, 3);
    assert(obj.animation_step.packed == 0x4D010002);
    obj.animation_step.fields.duration = 1;
    expected = obj;
    expected.animation_cursor += 4;
    expected.animation_step.packed = 0x4F010101;
    for (i = 0; i < slots; i++) {
        struct ShotObj* s = &pool_expected[32 - slots + i];
        s->active = 0x41;
        s->id = 39;
        s->unk2 = i;
        s->animation_table = (u32**)obj.animation_table;
        s->x_pos = obj.x_pos;
        s->y_pos = obj.y_pos;
        s->unk7C = WEAPON_OBJECT(&obj);
        s->state = 7;
    }
    func_800793AC(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(shot_objects, pool_expected, sizeof(pool_expected));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(D_8013E198[2] == -1);
    return 1;
}

void split_mushroom_spore_rain_split(struct MainObj*);
void split_mushroom_wall_jump_cling(struct MainObj*);
extern void* split_mushroom_animations[26];
static struct MainObj expected_mains[48];
static struct ShotObj expected_shots[32];
static struct VisualObj expected_visuals[32];
static struct MiscObj expected_misc[64];
static u32 full(u32 row)
{
    struct MainObj* obj = &main_objects[0];
    struct PlayerObj player = g_Player;
    struct EngineObj engine;
    u32 i;
    engine_obj.stage = 3;
    engine_obj.substage = 1;
    engine = engine_obj;
    background_objects[0].x_pos.val = 5812 * 65536;
    background_objects[0].y_pos.val = 243 * 65536;
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    for (i = 0; i < COUNT(main_objects); i++)
        main_objects[i].active = 1;
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    for (i = 0; i < COUNT(shot_objects); i++)
        shot_objects[i].active = 1;
    memcpy(expected_shots, shot_objects, sizeof(expected_shots));
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = 1;
    memcpy(expected_visuals, visual_objects, sizeof(expected_visuals));
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = 1;
    memcpy(expected_misc, misc_objects, sizeof(expected_misc));
    obj->active = 0x41;
    obj->id = 61;
    obj->state = 1;
    obj->hp = 48;
    obj->x_pos.i.hi = 5972;
    obj->y_pos.i.hi = 363;
    obj->animation_table = (const u8* const*)split_mushroom_animations;
    D_8013E198[2] = -1;
    if (row) {
        obj->unk5 = 3;
        set_animation(obj, 2);
        for (i = 0; i < 7; i++)
            func_80079A8C(obj);
        assert(obj->unk6 == 1 && obj->unk7C == 48);
        for (i = 0; i < 48; i++)
            func_80079B50(obj);
        assert(obj->unk6 == 2 && obj->unk7C == 240 && obj->unk17 == 4);
        for (i = 0; i < 239; i++)
            split_mushroom_spore_rain_split(obj);
        assert(obj->unk7C == 1);
    } else {
        obj->unk5 = 7;
        obj->unk6 = 2;
        obj->unk7C = 40;
        set_animation(obj, 6);
        for (i = 0; i < 40; i++)
            split_mushroom_wall_jump_cling(obj);
        assert(obj->unk6 == 3 && obj->unk7C == 40 && obj->unk7E == 6);
        for (i = 0; i < 39; i++)
            func_8007B418(obj);
        assert(obj->unk7C == 1 && obj->animation_step.packed == 0x76010016);
    }
    memcpy(expected_mains, main_objects, sizeof(expected_mains));
    cur_random = 0x1234;
    if (row) {
        struct MainObj* e = &expected_mains[0];
        e->unk7C = 0;
        e->ext.main_61.split = 1;
        e->ext.main_61.stunned = 0;
        e->unk6 = 3;
        e->unk17 = 3;
        e->previous_animation_index = 255;
        e->animation_cursor = split_mushroom_animations[3];
        e->animation_step.packed = *(u32*)split_mushroom_animations[3];
        e->unk15 = 0;
        e->x_speed = 0x2C000;
        e->gravity = 0x3800;
        e->x_accel = e->y_speed = 0;
        split_mushroom_spore_rain_split(obj);
    } else {
        expected_mains[0].unk7C = 40;
        expected_mains[0].unk7E = 5;
        expected_mains[0].animation_step.packed = 0x76010015;
        func_8007B418(obj);
    }
    assert(c_test_word_difference((u32*)main_objects, (u32*)expected_mains, sizeof(expected_mains) / 4) == 0);
    assert(c_test_word_difference((u32*)shot_objects, (u32*)expected_shots, sizeof(expected_shots) / 4) == 0);
    assert(c_test_word_difference((u32*)visual_objects, (u32*)expected_visuals, sizeof(expected_visuals) / 4) == 0);
    assert(c_test_word_difference((u32*)misc_objects, (u32*)expected_misc, sizeof(expected_misc) / 4) == 0);
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    assert(cur_random == (row ? 0x366A : 0x1234) && D_8013E198[2] == -1);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "split_mushroom_main", 0, 0, COUNT(split_mushroom_main_cases), test_split_mushroom_main },
    { "split_mushroom_states", 0, 0, COUNT(split_mushroom_states_cases), test_split_mushroom_states },
    { "mushroom_hop_signed_speed", NULL, mushroom_hop_signed_speed_cases_expected, COUNT(mushroom_hop_signed_speed_cases_expected), hop_case },
    { "mushroom_reunion_vertical", NULL, mushroom_reunion_vertical_cases_expected, COUNT(mushroom_reunion_vertical_cases_expected), mushroom_reunion_vertical_cases_row },
    { "split_mushroom_intro_pools", NULL, split_mushroom_intro_pools_cases_expected, COUNT(split_mushroom_intro_pools_cases_expected), intro_case },
    { "func_80079824", 0, 0, 3, test_func_80079824 },
    { "split_mushroom_face_player", 0, 0, 2, test_split_mushroom_face_player },
    { "split_mushroom_death_flash", split_mushroom_death_flash_cases, split_mushroom_death_flash_cases_expected, COUNT(split_mushroom_death_flash_cases), 0 },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "own_Mushroom_dash_first_smoke_and_grounded_combo_slam_full_partial_pools", NULL, NULL, 36, attack },
    { "full_visual_pool_with_normal_and_short_hit_flashes", NULL, NULL, 12, hit_visual_exhaustion },
    { "actual_intro_talk_animation_event_zero_one_five_spore_slots", NULL, NULL, 3, spores },
    { "own_Mushroom_wall_first_shot_or_spore_split_clock_full_32_shot_or_48_main_slots", NULL, NULL, 2, full },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(split_mushroom_main_cases) + COUNT(split_mushroom_states_cases) + COUNT(mushroom_hop_signed_speed_cases_expected) + COUNT(mushroom_reunion_vertical_cases_expected) + COUNT(split_mushroom_intro_pools_cases_expected) + 3 + 2 + COUNT(split_mushroom_death_flash_cases) + COUNT(pool_full_cases) + 36 + 12 + 3 + 2;
