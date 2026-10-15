#include "test_runtime.h"
void colonel_spawn_afterimages(struct MainObj*);
extern void* D_80104770[25];
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static const u8 frames[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
static const u8 slots[3] = { 31, 29, 27 };
static u32 chain_case(u32 mode)
{
    struct MainObj obj, before;
    struct VisualObj expected[32];
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    u32 i, actual;
    memset(visual_objects, 0x5A, sizeof(visual_objects));
    for (i = 0; i < 32; i++)
        visual_objects[i].active = 1;
    for (i = 0; i < mode; i++)
        visual_objects[slots[i]].active = 0;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 69;
    obj.state = 1;
    obj.unk40 = 0x1234;
    obj.unk42 = 0x9234;
    obj.animation_table = (const u8* const*)D_80104770;
    obj.sprite_frames = frames;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    g_Player.bg_offset = 2;
    player_before = g_Player;
    before = obj;
    memcpy(expected, visual_objects, sizeof(expected));
    for (i = 0; i < mode; i++) {
        struct VisualObj* v = &expected[slots[i]];
        v->active = 0x41;
        v->id = 5;
        v->unk2 = i;
        v->bg_offset = 2;
        v->unk40 = obj.unk40;
        v->unk42 = obj.unk42;
        v->unk16 = 6;
        v->unk3C = (void*)frames;
        v->animation_table = (u32**)obj.animation_table;
        v->unk5C.owner = PLAYER_OBJECT(&obj);
        v->unk50 = i == 0 ? PLAYER_OBJECT(&obj) : PLAYER_OBJECT(&visual_objects[slots[i - 1]]);
    }
    colonel_spawn_afterimages(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(expected) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    actual = visual_objects[31].active | ((u32)visual_objects[29].active << 8) | ((u32)visual_objects[27].active << 16);
    return actual;
}
#define CASE(m)                                              \
    static u32 colonel_afterimage_chain_pool_chain_##m(void) \
    {                                                        \
        return chain_case(m);                                \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
#define ENTRY(m) colonel_afterimage_chain_pool_chain_##m,
static const CTestCase colonel_afterimage_chain_pool_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) };
static const u32 colonel_afterimage_chain_pool_cases_expected[] = { 0x10101u, 0x10141u, 0x14141u, 0x414141u };
#undef CASE
#undef ENTRY

static u32 defeat_case(u32 mode)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct EffectObj pool_before[32];
    struct BackgroundObj bg_before[3];
    u32 i, airborne = mode >= 2, player_right = !(mode & 1);
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(effect_objects, 0, sizeof(effect_objects));
    memset(background_objects, 0, sizeof(background_objects));
    for (i = 0; i < 32; i++) {
        effect_objects[i].active = 1;
        effect_objects[i].id = 0x27;
        effect_objects[i].state = 0x28;
    }
    effect_objects[17].id = 0x25;
    effect_objects[17].unk2 = 0x10;
    effect_objects[17].x_pos.val = 0x1234;
    effect_objects[31].id = 0x25;
    effect_objects[31].unk2 = 0x11;
    obj.active = 0x41;
    obj.id = 69;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 2;
    obj.air_state = airborne;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = 65536;
    obj.y_speed = -32768;
    obj.x_accel = 0x2000;
    obj.gravity = 0x1000;
    obj.animation_table = (const u8* const*)D_80104770;
    set_animation(&obj, 0);
    g_Player.x_pos.i.hi = player_right ? 150 : 50;
    g_Player.hp = 0x27;
    engine_obj.stage = 2;
    g_FilterAmountR = 7;
    g_FilterAmountG = 8;
    g_FilterAmountB = 9;
    need_palette_load = 0x80;
    before = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(pool_before, effect_objects, sizeof(pool_before));
    memcpy(bg_before, background_objects, sizeof(bg_before));
    colonel_defeat_start(&obj);
    before.unk15 = player_right ? 0x40 : 0;
    before.on_screen = 1;
    before.unk6 += airborne ? 1 : 3;
    before.unk17 = airborne ? 10 : 24;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = (const u8*)D_80104770[before.unk17];
    before.animation_step = *(union AnimationStep*)before.animation_cursor;
    if (airborne) {
        before.x_speed = player_right ? -3 * 65536 : 3 * 65536;
        before.x_accel = before.y_speed = 0;
        before.gravity = 0x4200;
    }
    player_before.script_state = 1;
    player_before.script_action = 0x14;
    player_before.script_facing = player_right ? 0 : 0x40;
    player_before.spike_immune = 1;
    engine_before.gameplay_locked = 1;
    ((u32*)&pool_before[17])[0] = ((u32*)&pool_before[17])[1] = 0;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)effect_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(bg_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)bg_before)[i]);
    assert(g_FilterAmountR == 0 && g_FilterAmountG == 0 && g_FilterAmountB == 0 && need_palette_load == 0x81);
    return (u8)obj.unk6 | ((u32)obj.unk17 << 8) | ((u32)(u8)g_Player.script_facing << 16) | ((u32)obj.unk15 << 24);
}
#define CASE(m)                                                  \
    static u32 colonel_defeat_animation_context_defeat_##m(void) \
    {                                                            \
        return defeat_case(m);                                   \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
#define ENTRY(m) colonel_defeat_animation_context_defeat_##m,
static const CTestCase colonel_defeat_animation_context_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) };
static const u32 colonel_defeat_animation_context_cases_expected[] = { 0x40001805u, 0x401805u, 0x40000A03u, 0x400A03u };
#undef CASE
#undef ENTRY

static u32 hall_case(u32 mode)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 0x41;
    obj.id = 69;
    obj.state = 1;
    obj.unk7 = 2;
    obj.unk7C = 0x27;
    obj.x_pos.i.hi = 1000;
    g_Player.x_pos.i.hi = mode == 0 ? 823 : 1177;
    g_Player.hp = 0x27;
    engine_obj.stage = 3;
    before = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    colonel_intro_hall_wait_player(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    return obj.unk7 | ((u32)(u16)obj.unk7C << 8);
}
#define CASE(m)                                       \
    static u32 colonel_hall_far_player_hall_##m(void) \
    {                                                 \
        return hall_case(m);                          \
    }
CASE(0)
CASE(1)
#define ENTRY(m) colonel_hall_far_player_hall_##m,
static const CTestCase colonel_hall_far_player_cases[]
    = { ENTRY(0) ENTRY(1) };
static const u32 colonel_hall_far_player_cases_expected[] = { 0x2702u, 0x2702u };
#undef CASE
#undef ENTRY

#define INCOMING_CASE(name, enabled, hitbox, facing, shot_x, velocity) \
    static u32 name(void)                                              \
    {                                                                  \
        struct MainObj obj;                                            \
        u8 bounds[4] = { 0, 0, 1, 1 };                                 \
        u32 actual;                                                    \
        memset(&obj, 0, sizeof(obj));                                  \
        memset(weapon_objects, 0, sizeof(weapon_objects));             \
        obj.x_pos.i.hi = 100;                                          \
        obj.unk15 = facing;                                            \
        weapon_objects[0].active = enabled;                            \
        weapon_objects[0].unk50 = hitbox ? bounds : NULL;              \
        weapon_objects[0].x_pos.i.hi = shot_x;                         \
        weapon_objects[0].x_vel.val = velocity;                        \
        actual = colonel_shot_incoming(&obj);                          \
        assert(obj.x_pos.i.hi == 100 && obj.unk15 == facing);          \
        return actual;                                                 \
    }
INCOMING_CASE(inactive, 0, 1, 0, 100, 0)
INCOMING_CASE(no_hitbox, 1, 0, 0, 100, 0)
INCOMING_CASE(left_behind, 1, 1, 0, 116, 0)
INCOMING_CASE(left_toward, 1, 1, 0, 84, 1)
INCOMING_CASE(left_away, 1, 1, 0, 84, -1)
INCOMING_CASE(left_equal, 1, 1, 0, 100, 0)
INCOMING_CASE(right_behind, 1, 1, 0x40, 84, 0)
INCOMING_CASE(right_toward, 1, 1, 0x40, 116, -1)
INCOMING_CASE(right_away, 1, 1, 0x40, 116, 1)
INCOMING_CASE(right_equal, 1, 1, 0x40, 100, 0)

#define ENTRY(name) name,
static const CTestCase colonel_incoming_cases[] = {
    ENTRY(inactive)
        ENTRY(no_hitbox)
            ENTRY(left_behind)
                ENTRY(left_toward)
                    ENTRY(left_away)
                        ENTRY(left_equal)
                            ENTRY(right_behind)
                                ENTRY(right_toward)
                                    ENTRY(right_away)
                                        ENTRY(right_equal)
};
static const u32 colonel_incoming_cases_expected[] = { 0x0u, 0x0u, 0x0u, 0x1u, 0x0u, 0x1u, 0x0u, 0x1u, 0x0u, 0x1u };
#undef INCOMING_CASE
#undef ENTRY

struct colonel_dash_brake_case {
    u32 unk15, x_speed;
    u32 expected[3];
};
static const struct colonel_dash_brake_case colonel_dash_brake_cases[] = {
    { 255, -1, { 3u, 0u, 0u } },
    { 0, 1, { 3u, 0u, 0u } },
};
static u32 test_colonel_dash_brake(u32 row)
{
    const struct colonel_dash_brake_case* c = &colonel_dash_brake_cases[row];
    u32 observed_values[3];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_801044FC, 0, sizeof(D_801044FC));
    memset(&D_80104500, 0, sizeof(D_80104500));
    obj.unk15 = c->unk15;
    obj.x_speed = c->x_speed;
    colonel_dash_brake(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.x_speed;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

struct colonel_defeat_blink_case {
    u32 unk7C, pool_0_full, hi, unk7E, invincibility_timer;
    u32 expected[9];
};
static const struct colonel_defeat_blink_case colonel_defeat_blink_cases[] = {
    { 0, 0, -32768, 0, 33, { 0u, 0u, 0u, 0u, 0u, 0x8000u, 0u, 0xFFFFFFFFu, 5u } },
    { 1, 255, 0, 255, 0, { 1u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0xFEu } },
};
static u32 test_colonel_defeat_blink(u32 row)
{
    const struct colonel_defeat_blink_case* c = &colonel_defeat_blink_cases[row];
    u32 observed_values[9];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&effect_objects, 0, sizeof(effect_objects));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk7C = c->unk7C;
    pool_0_full = c->pool_0_full;
    obj.x_pos.i.hi = c->hi;
    obj.unk7E = c->unk7E;
    obj.invincibility_timer = c->invincibility_timer;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            effect_objects[slot].active = pool_0_full ? 1 : 0;
    }
    colonel_defeat_blink(&obj);
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)effect_objects[0].x_pos.i.hi;
    observed_values[3] = (u32)effect_objects[0].y_pos.i.hi;
    observed_values[4] = (u32)obj.invincibility_timer;
    observed_values[5] = (u32)obj.unk42;
    observed_values[6] = (u32)obj.unk6;
    observed_values[7] = (u32)obj.unk7C;
    observed_values[8] = (u32)obj.unk7E;
    return c_test_observe(0, row, observed_values, c->expected, 9);
}

struct colonel_defeat_fall_case {
    u32 collision_flags;
    u32 expected[3];
};
static const struct colonel_defeat_fall_case colonel_defeat_fall_cases[] = {
    { 0, { 0u, 0u, 0u } },
    { 3, { 0u, 0u, 0u } },
};
static u32 test_colonel_defeat_fall(u32 row)
{
    const struct colonel_defeat_fall_case* c = &colonel_defeat_fall_cases[row];
    u32 observed_values[3];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.collision_flags = c->collision_flags;
    colonel_defeat_fall(&obj);
    observed_values[0] = (u32)obj.air_state;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.x_speed;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

struct colonel_intro_hall_effect_case {
    u32 unk7C, pool_0_full;
    u32 expected[5];
};
static const struct colonel_intro_hall_effect_case colonel_intro_hall_effect_cases[] = {
    { 0, 0, { 0u, 0u, 0u, 0u, 0xFFFFFFFFu } },
    { 1, 255, { 1u, 0u, 0u, 1u, 0u } },
};
static u32 test_colonel_intro_hall_effect(u32 row)
{
    const struct colonel_intro_hall_effect_case* c = &colonel_intro_hall_effect_cases[row];
    u32 observed_values[5];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&effect_objects, 0, sizeof(effect_objects));
    obj.unk7C = c->unk7C;
    pool_0_full = c->pool_0_full;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            effect_objects[slot].active = pool_0_full ? 1 : 0;
    }
    colonel_intro_hall_effect(&obj);
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)effect_objects[0].unk2;
    observed_values[3] = (u32)obj.unk7;
    observed_values[4] = (u32)obj.unk7C;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

static const u32 colonel_intro_hall_wait_player_expected[] = { 0x2C0u, 0x2A0u, 1u, 0x78u };
static u32 test_colonel_intro_hall_wait_player(u32 row)
{
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    colonel_intro_hall_wait_player(&obj);
    observed_values[0] = (u32)background_objects[0].unk24;
    observed_values[1] = (u32)background_objects[0].unk26;
    observed_values[2] = (u32)obj.unk7;
    observed_values[3] = (u32)obj.unk7C;
    return c_test_observe(0, row, observed_values, colonel_intro_hall_wait_player_expected, 4);
}

static const u32 colonel_shot_incoming_0_expected[] = { 0u };
static u32 test_colonel_shot_incoming_0(u32 row)
{
    u32 observed_values[1];
    struct MainObj obj;
    ret_u8 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    weapon_objects[0].active = -1;
    return_value = colonel_shot_incoming(&obj);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, colonel_shot_incoming_0_expected, 1);
}

static const u32 colonel_shot_incoming_1_expected[] = { 0u };
static u32 test_colonel_shot_incoming_1(u32 row)
{
    u32 observed_values[1];
    struct MainObj obj;
    ret_u8 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    weapon_objects[0].active = -1;
    weapon_objects[0].x_pos.i.hi = 0;
    weapon_objects[0].x_vel.val = 0;
    return_value = colonel_shot_incoming(&obj);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, colonel_shot_incoming_1_expected, 1);
}

struct func_80087A00_case {
    u32 unk15, x_speed, hi;
    u32 expected[4];
};
static const struct func_80087A00_case func_80087A00_cases[] = {
    { 255, 393216, 0, { 0u, 0u, 0u, 0x60000u } },
    { 0, -327680, 32767, { 0u, 0u, 0u, 0xFFFB0000u } },
};
static u32 test_func_80087A00(u32 row)
{
    const struct func_80087A00_case* c = &func_80087A00_cases[row];
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk15 = c->unk15;
    obj.x_speed = c->x_speed;
    obj.x_pos.i.hi = c->hi;
    func_80087A00(&obj);
    observed_values[0] = (u32)obj.unk4B;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.x_accel;
    observed_values[3] = (u32)obj.x_speed;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

#include "support/pool_full.h"
static u32 pool_full_colonel_link_visual(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    func_80086C00(&pf_self);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_colonel_spawn_warning(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    colonel_spawn_warning(&pf_self);
    pf_expected.ext.main_69.state.bytes.variant = 9;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_colonel_intro_port_flash(void)
{
    u32 actual;
    pf_prepare();
    g_Player.input.buttons.held = 0;
    pf_snapshot();
    colonel_intro_port_flash(&g_Player);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_colonel_teleport_slash_swing(void)
{
    u32 actual;
    pf_prepare();
    pf_event(1, 1);
    pf_snapshot();
    pf_animated();
    colonel_teleport_slash_swing(&pf_self);
    pf_expected.on_screen = 1;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_colonel_saber_waves_fire(void)
{
    u32 actual;
    pf_prepare();
    pf_event(1, 1);
    pf_snapshot();
    pf_animated();
    colonel_saber_waves_fire(&pf_self);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_colonel_saber_waves_fire_high(void)
{
    u32 actual;
    pf_prepare();
    pf_event(1, 1);
    pf_snapshot();
    pf_animated();
    colonel_saber_waves_fire_high(&pf_self);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_colonel_saber_waves_fire_last(void)
{
    u32 actual;
    pf_prepare();
    pf_event(1, 1);
    pf_snapshot();
    pf_animated();
    colonel_saber_waves_fire_last(&pf_self);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_colonel_jump_slam_shockwave(void)
{
    u32 actual;
    pf_prepare();
    pf_event(0, 0);
    pf_snapshot();
    colonel_jump_slam_shockwave(&pf_self);
    pf_animated();
    pf_expected.unk7C = 0x50;
    pf_expected.unk6++;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_colonel_link_visual,
    pool_full_colonel_spawn_warning,
    pool_full_colonel_intro_port_flash,
    pool_full_colonel_teleport_slash_swing,
    pool_full_colonel_saber_waves_fire,
    pool_full_colonel_saber_waves_fire_high,
    pool_full_colonel_saber_waves_fire_last,
    pool_full_colonel_jump_slam_shockwave,
};

static const u32 pool_full_cases_expected[] = { 0x50000u, 0x50000u, 0x50000u, 0x50000u, 0x50000u, 0x50000u, 0x50000u, 0x500100u };
const struct CTestGroup c_test_groups[] = {
    { "colonel_afterimage_chain_pool", colonel_afterimage_chain_pool_cases, colonel_afterimage_chain_pool_cases_expected, COUNT(colonel_afterimage_chain_pool_cases), 0 },
    { "colonel_defeat_animation_context", colonel_defeat_animation_context_cases, colonel_defeat_animation_context_cases_expected, COUNT(colonel_defeat_animation_context_cases), 0 },
    { "colonel_hall_far_player", colonel_hall_far_player_cases, colonel_hall_far_player_cases_expected, COUNT(colonel_hall_far_player_cases), 0 },
    { "colonel_incoming", colonel_incoming_cases, colonel_incoming_cases_expected, COUNT(colonel_incoming_cases), 0 },
    { "colonel_dash_brake", 0, 0, 2, test_colonel_dash_brake },
    { "colonel_defeat_blink", 0, 0, 2, test_colonel_defeat_blink },
    { "colonel_defeat_fall", 0, 0, 2, test_colonel_defeat_fall },
    { "colonel_intro_hall_effect", 0, 0, 2, test_colonel_intro_hall_effect },
    { "colonel_intro_hall_wait_player", 0, 0, 1, test_colonel_intro_hall_wait_player },
    { "colonel_shot_incoming_0", 0, 0, 1, test_colonel_shot_incoming_0 },
    { "colonel_shot_incoming_1", 0, 0, 1, test_colonel_shot_incoming_1 },
    { "func_80087A00", 0, 0, 2, test_func_80087A00 },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(colonel_afterimage_chain_pool_cases) + COUNT(colonel_defeat_animation_context_cases) + COUNT(colonel_hall_far_player_cases) + COUNT(colonel_incoming_cases) + 2 + 2 + 2 + 2 + 1 + 1 + 1 + 2 + COUNT(pool_full_cases);
