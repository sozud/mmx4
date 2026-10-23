#include "test_runtime.h"
#include "main/mains/main_69_colonel.h"
#include "main/1AC84.h"
#include "main/55C4.h"
#include "main/effects/effect_37_alarm_flash.h"
#include "main/player.h"
#include "main/objects.h"
#include "main/collision_bounds.h"
#include "main/weapons/weapon_06_aiming_laser_charged.h"
void colonel_jump_slam(struct MainObj* arg0);
void colonel_saber_waves(struct MainObj* arg0);
void colonel_spawn(struct MainObj* arg0);
void colonel_flash_strike(struct MainObj* arg0);
void colonel_intro(struct MainObj* arg0);
void colonel_death(struct MainObj* arg0);
void func_800881F8(struct MainObj*);
void func_800883CC(struct MainObj*);
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
static const u32 colonel_afterimage_chain_pool_cases_expected[] = { 0x10101u, 0x10141u, 0x14141u, 0x414141u };

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
static const u32 colonel_defeat_animation_context_cases_expected[] = { 0x40001805u, 0x401805u, 0x40000A03u, 0x400A03u };

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
static const u32 colonel_hall_far_player_cases_expected[] = { 0x2702u, 0x2702u };

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
    memset(&obj, 0, sizeof(obj));
    memset(&effect_objects, 0, sizeof(effect_objects));
    obj.unk7C = c->unk7C;
    FILL_ACTIVE(effect_objects, 32, c->pool_0_full ? 1 : 0);
    colonel_intro_hall_effect(&obj);
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)effect_objects[0].unk2;
    observed_values[3] = (u32)obj.unk7;
    observed_values[4] = (u32)obj.unk7C;
    return c_test_observe(0, row, observed_values, c->expected, 5);
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

#include "support/state_cases.h"

#define DEFEAT(n) state_reset(0, n, 0)
#define RETREAT(n) state_reset(1, n, 0)
#define PORT(n) state_reset(2, 0, n)
#define FLASH(n) state_reset(0, n, 0)
#define SLAM(n) state_reset(0, n, 0)
static void c_defeat_land(void)
{
    DEFEAT(1);
    so.collision_flags = 8;
    colonel_death(&so);
}
static void c_defeat_next(void)
{
    DEFEAT(2);
    colonel_death(&so);
}
static void c_defeat_dialogue_x(void)
{
    DEFEAT(3);
    abc_object.unkC = 0x80;
    engine_obj.cur_character = 0;
    colonel_death(&so);
}
static void c_defeat_dialogue_zero(void)
{
    DEFEAT(3);
    abc_object.unkC = 0x80;
    engine_obj.cur_character = 1;
    colonel_death(&so);
}
static void c_defeat_wait_dialogue(void)
{
    DEFEAT(4);
    abc_object.unkC = 0;
    colonel_death(&so);
}
static void c_defeat_blink_spawn(void)
{
    DEFEAT(5);
    so.unk7C = 1;
    so.invincibility_timer = 30;
    colonel_death(&so);
}
static void c_defeat_explosion_blink(void)
{
    DEFEAT(6);
    so.ext.main_69.effect = &effect_objects[0];
    effect_objects[0].active = 1;
    colonel_death(&so);
}
static void c_defeat_explosion_done(void)
{
    DEFEAT(6);
    so.ext.main_69.effect = &effect_objects[0];
    colonel_death(&so);
}
static void c_retreat_start(void)
{
    RETREAT(0);
    colonel_death(&so);
}
static void c_retreat_vanish_odd(void)
{
    RETREAT(1);
    so.unk7C = 2;
    so.x_accel = 0x10000;
    colonel_death(&so);
}
static void c_retreat_vanish_even(void)
{
    RETREAT(1);
    so.unk7C = 3;
    so.x_accel = 0x10000;
    colonel_death(&so);
}
static void c_retreat_vanish_done(void)
{
    RETREAT(1);
    so.unk7C = 1;
    colonel_death(&so);
}
static void c_retreat_wait_count(void)
{
    RETREAT(2);
    so.unk7C = 1;
    colonel_death(&so);
}
static void c_retreat_wait_return(void)
{
    RETREAT(2);
    g_Player.script_state = -1;
    background_objects[0].unk1E = 0x40;
    colonel_death(&so);
}
static void c_retreat_reappear_odd(void)
{
    RETREAT(3);
    so.unk7C = 2;
    so.x_accel = 0x10000;
    colonel_death(&so);
}
static void c_retreat_reappear_even(void)
{
    RETREAT(3);
    so.unk7C = 3;
    so.x_accel = 0x10000;
    colonel_death(&so);
}
static void c_retreat_reappear_done(void)
{
    RETREAT(3);
    abc_object.unkC = 0x80;
    so.unk7C = 1;
    colonel_death(&so);
}
static void c_retreat_wait_dialogue(void)
{
    RETREAT(4);
    abc_object.unkC = 0;
    colonel_death(&so);
}
static void c_retreat_start_again(void)
{
    RETREAT(5);
    colonel_death(&so);
}
static void c_retreat_vanish_again_odd(void)
{
    RETREAT(6);
    so.unk7C = 2;
    so.x_accel = 0x10000;
    colonel_death(&so);
}
static void c_retreat_vanish_again_even(void)
{
    RETREAT(6);
    so.unk7C = 3;
    so.x_accel = 0x10000;
    colonel_death(&so);
}
static void c_retreat_vanish_again_done(void)
{
    RETREAT(6);
    so.unk7C = 1;
    colonel_death(&so);
}
static void c_retreat_finish(void)
{
    RETREAT(7);
    so.unk7C = 1;
    colonel_death(&so);
}
static void c_port_appear(void)
{
    PORT(0);
    colonel_intro(&so);
}
static void c_port_flash_spawn(void)
{
    PORT(1);
    colonel_intro_port_flash(&state_room.player);
}
static void c_port_flash_wait(void)
{
    PORT(1);
    state_room.player.input.buttons.held = 5;
    colonel_intro_port_flash(&state_room.player);
}
static void c_port_blink_in(void)
{
    PORT(2);
    so.unk7C = 1;
    so.ext.main_69.linked_object = &visual_objects[0];
    colonel_intro(&so);
}
static void c_port_pose_x(void)
{
    PORT(3);
    abc_object.unkC = 0x80;
    so.animation_step.fields.event = 1;
    engine_obj.cur_character = 0;
    colonel_intro(&so);
}
static void c_port_pose_zero(void)
{
    PORT(3);
    abc_object.unkC = 0x80;
    engine_obj.cur_character = 1;
    colonel_intro(&so);
}
static void c_port_voice(void)
{
    PORT(4);
    abc_object.unkC = 0;
    colonel_intro(&so);
}
static void c_port_fill_health(void)
{
    PORT(5);
    so.hp = 0x2F;
    so.unk7E = 1;
    colonel_intro(&so);
}
static void c_flash_vanish(void)
{
    FLASH(0);
    colonel_flash_strike(&so);
}
static void c_flash_shake_odd(void)
{
    FLASH(1);
    so.unk7C = 2;
    so.x_accel = 0x10000;
    colonel_flash_strike(&so);
}
static void c_flash_shake_even(void)
{
    FLASH(1);
    so.unk7C = 3;
    so.x_accel = 0x10000;
    colonel_flash_strike(&so);
}
static void c_flash_shake_done(void)
{
    FLASH(1);
    so.unk7C = 1;
    colonel_flash_strike(&so);
}
static void c_flash_reappear(void)
{
    FLASH(2);
    so.unk7C = 1;
    background_objects[0].unk1E = 0x40;
    colonel_flash_strike(&so);
}
static void c_flash_slide_odd(void)
{
    FLASH(3);
    so.unk7C = 3;
    so.x_accel = 0x10000;
    colonel_flash_strike(&so);
}
static void c_flash_slide_even(void)
{
    FLASH(3);
    so.unk7C = 4;
    so.x_accel = 0x10000;
    colonel_flash_strike(&so);
}
static void c_flash_slide_done(void)
{
    FLASH(3);
    so.unk7C = 1;
    colonel_flash_strike(&so);
}
static void c_flash_strike_wait(void)
{
    FLASH(4);
    colonel_flash_strike(&so);
}
static void c_flash_flash(void)
{
    FLASH(5);
    so.unk7C = 1;
    so.ext.main_69.linked_object = &visual_objects[0];
    colonel_flash_strike(&so);
}
static void c_flash_hold_wait(void)
{
    FLASH(6);
    colonel_flash_strike(&so);
}
static void c_flash_wait(void)
{
    FLASH(7);
    so.unk7C = 1;
    colonel_flash_strike(&so);
}
static void c_flash_recover(void)
{
    FLASH(8);
    so.animation_step.fields.relative_step = 0;
    colonel_flash_strike(&so);
}
static void c_slam_jump(void)
{
    SLAM(0);
    colonel_jump_slam(&so);
}
static void c_slam_rise(void)
{
    SLAM(1);
    so.animation_step.fields.event = 1;
    colonel_jump_slam(&so);
}
static void c_slam_land(void)
{
    SLAM(2);
    so.collision_flags = 8;
    colonel_jump_slam(&so);
}
static void c_slam_drop_wait(void)
{
    SLAM(3);
    so.unk7C = 2;
    so.air_state = 1;
    so.y_speed = -1;
    colonel_jump_slam(&so);
}
static void c_slam_drop_land(void)
{
    SLAM(3);
    so.unk7C = 2;
    so.air_state = -1;
    so.collision_flags = 8;
    colonel_jump_slam(&so);
}
static void c_slam_recover(void)
{
    SLAM(5);
    so.unk7C = 1;
    colonel_jump_slam(&so);
}
static void c_spawn_variant(void)
{
    state_reset(0, 0, 0);
    so.unk2 = 1;
    colonel_spawn(&so);
}

static void (*const col_cases[])(void) = {
    c_defeat_land,
    c_defeat_next,
    c_defeat_dialogue_x,
    c_defeat_dialogue_zero,
    c_defeat_wait_dialogue,
    c_defeat_blink_spawn,
    c_defeat_explosion_blink,
    c_defeat_explosion_done,
    c_retreat_start,
    c_retreat_vanish_odd,
    c_retreat_vanish_even,
    c_retreat_vanish_done,
    c_retreat_wait_count,
    c_retreat_wait_return,
    c_retreat_reappear_odd,
    c_retreat_reappear_even,
    c_retreat_reappear_done,
    c_retreat_wait_dialogue,
    c_retreat_start_again,
    c_retreat_vanish_again_odd,
    c_retreat_vanish_again_even,
    c_retreat_vanish_again_done,
    c_retreat_finish,
    c_port_appear,
    c_port_flash_spawn,
    c_port_flash_wait,
    c_port_blink_in,
    c_port_pose_x,
    c_port_pose_zero,
    c_port_voice,
    c_port_fill_health,
    c_flash_vanish,
    c_flash_shake_odd,
    c_flash_shake_even,
    c_flash_shake_done,
    c_flash_reappear,
    c_flash_slide_odd,
    c_flash_slide_even,
    c_flash_slide_done,
    c_flash_strike_wait,
    c_flash_flash,
    c_flash_hold_wait,
    c_flash_wait,
    c_flash_recover,
    c_slam_jump,
    c_slam_rise,
    c_slam_land,
    c_slam_drop_wait,
    c_slam_drop_land,
    c_slam_recover,
    c_spawn_variant,
};
static const u32 col_expected[] = { 0x200u, 0u, 0u, 0u, 0u, 0u, 0x18u, 0u, 0u, 0u, 0x300u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x400u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x400u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x500u, 0x19007Fu, 0u, 0u, 0u, 0u, 0u, 0x1900u, 0u, 0u, 0x600u, 0x190000u, 0u, 0u, 0u, 0u, 0x80000000u, 0x1900u, 0u, 1u, 0x600u, 0x50000u, 0u, 0u, 0u, 0u, 0x80000000u, 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x1000000u, 0u, 0x101u, 0x20u, 0u, 0u, 0u, 0x10000u, 6u, 0u, 0x1501u, 0u, 0x101u, 1u, 0x10000u, 0x10000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0x101u, 2u, 0xFFFF0000u, 0x10000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0x201u, 0x20u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x201u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x301u, 0x20u, 0x1400000u, 0x200000u, 0u, 0xFFFF0000u, 0u, 0u, 0xFFu, 0u, 0x301u, 1u, 0x10000u, 0x10000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0x301u, 2u, 0xFFFF0000u, 0x10000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0x401u, 0u, 0u, 0u, 0u, 0u, 0x4018u, 0u, 0u, 0u, 0x501u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x601u, 0x20u, 0u, 0u, 0u, 0x10000u, 6u, 0u, 0u, 0u, 0x601u, 1u, 0x10000u, 0x10000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0x601u, 2u, 0xFFFF0000u, 0x10000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0x701u, 0x20u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x701u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x1000000u, 0u, 0x10002u, 0x10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x4100u, 0x20002u, 0x20u, 0u, 0u, 0u, 0u, 0x16u, 0u, 0u, 0x4100u, 0x10002u, 4u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x30002u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x10000u, 0u, 0x40002u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40002u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50002u, 0x30000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0u, 0u, 0u, 0u, 0u, 0u, 0x300000u, 0u, 0u, 0x100u, 0x20u, 0u, 0u, 0u, 0x10000u, 6u, 0u, 0u, 0u, 0x100u, 1u, 0x10000u, 0x10000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0x100u, 2u, 0xFFFF0000u, 0x10000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0x200u, 0x28u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x300u, 0x14u, 0xE00000u, 0x200000u, 0u, 0xFFFF0000u, 0u, 0u, 0u, 0u, 0x300u, 2u, 0xFFFF0000u, 0x10000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0x300u, 3u, 0x10000u, 0x10000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0x400u, 0u, 0u, 0u, 0u, 0u, 7u, 3u, 0u, 0u, 0x400u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x600u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x700u, 0x50u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x414100u, 0x800u, 0u, 0u, 0u, 0u, 0u, 8u, 0u, 0u, 0u, 3u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0u, 0u, 0x100u, 0u, 0u, 0u, 0x68000u, 0x420000u, 3u, 3u, 0u, 0u, 0x200u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x1000300u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0xFF000300u, 0x10u, 0u, 0u, 0xFFFFFFFFu, 0u, 0u, 0u, 0u, 0u, 0x400u, 1u, 0u, 0u, 0u, 0u, 4u, 0u, 0u, 0u, 3u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_colonel_states(u32 row)
{
    return state_run(col_cases[row], row, &col_expected[row * 10]);
}

static void s_spawn_warning(void)
{
    state_reset(0, 0, 0);
    colonel_spawn(&so);
}
static void s_defeat_wait_dialogue(void)
{
    DEFEAT(4);
    abc_object.unkC = 0x80;
    colonel_death(&so);
}
static void s_defeat_explosion_still(void)
{
    DEFEAT(6);
    so.unk7E = 2;
    so.ext.main_69.effect = &effect_objects[0];
    effect_objects[0].active = 1;
    colonel_death(&so);
}
static void s_defeat_explosion_exploding(void)
{
    DEFEAT(6);
    so.ext.main_69.effect = &effect_objects[0];
    effect_objects[0].active = 1;
    effect_objects[0].unk7 = 1;
    colonel_death(&so);
}
static void s_retreat_wait_dialogue(void)
{
    RETREAT(4);
    abc_object.unkC = 0x80;
    colonel_death(&so);
}
static void s_retreat_finish_wait(void)
{
    RETREAT(7);
    so.unk7C = 2;
    colonel_death(&so);
}
static void s_port_blink_wait(void)
{
    PORT(2);
    so.unk7C = 2;
    so.on_screen = 1;
    colonel_intro(&so);
}
static void s_port_pose_wait(void)
{
    PORT(3);
    so.animation_step.fields.relative_step = 1;
    colonel_intro(&so);
}
static void s_port_voice_wait(void)
{
    PORT(4);
    abc_object.unkC = 0x80;
    colonel_intro(&so);
}
static void s_port_fill_music(void)
{
    PORT(5);
    engine_obj.unk36.timer = 2;
    D_80173C84 = 1;
    colonel_intro(&so);
}
static void s_port_fill_step(void)
{
    PORT(5);
    so.unk7E = 2;
    colonel_intro(&so);
}
static void s_flash_reappear_wait(void)
{
    FLASH(2);
    so.unk7C = 2;
    colonel_flash_strike(&so);
}
static void s_flash_flash_wait(void)
{
    FLASH(5);
    so.unk7C = 2;
    colonel_flash_strike(&so);
}
static void s_flash_hold_animate(void)
{
    FLASH(6);
    so.animation_step.fields.relative_step = 1;
    colonel_flash_strike(&so);
}
static void s_flash_wait_count(void)
{
    FLASH(7);
    so.unk7C = 2;
    colonel_flash_strike(&so);
}
static void s_flash_recover_animate(void)
{
    FLASH(8);
    so.animation_step.fields.relative_step = 1;
    colonel_flash_strike(&so);
}
static void s_saber_start_high(void)
{
    state_reset(0, 0, 0);
    so.ext.main_69.state.bytes.variant = 1;
    colonel_saber_waves(&so);
}
static void s_slam_rise_wait(void)
{
    SLAM(1);
    colonel_jump_slam(&so);
}
static void s_slam_drop_rising(void)
{
    SLAM(3);
    so.unk7C = 2;
    so.air_state = 1;
    colonel_jump_slam(&so);
}
static void s_slam_drop_falling(void)
{
    SLAM(3);
    so.unk7C = 2;
    so.air_state = -1;
    colonel_jump_slam(&so);
}
static void s_slam_shockwave(void)
{
    SLAM(4);
    so.animation_step.fields.event = 1;
    colonel_jump_slam(&so);
}
static void s_slam_shockwave_animate(void)
{
    SLAM(4);
    so.animation_step.fields.relative_step = 1;
    colonel_jump_slam(&so);
}
static void s_slam_recover_wait(void)
{
    SLAM(5);
    so.unk7C = 2;
    colonel_jump_slam(&so);
}

static void (*const col_sides[])(void) = {
    s_spawn_warning,
    s_defeat_wait_dialogue,
    s_defeat_explosion_still,
    s_defeat_explosion_exploding,
    s_retreat_wait_dialogue,
    s_retreat_finish_wait,
    s_port_blink_wait,
    s_port_pose_wait,
    s_port_voice_wait,
    s_port_fill_music,
    s_port_fill_step,
    s_flash_reappear_wait,
    s_flash_flash_wait,
    s_flash_hold_animate,
    s_flash_wait_count,
    s_flash_recover_animate,
    s_saber_start_high,
    s_slam_rise_wait,
    s_slam_drop_rising,
    s_slam_drop_falling,
    s_slam_shockwave,
    s_slam_shockwave_animate,
    s_slam_recover_wait,
};
static const u32 col_sides_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x1501u, 1u, 0x400u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x600u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0x600u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0x401u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x701u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x20002u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x30002u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40002u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50002u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50002u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0x10000u, 0u, 0u, 0x200u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x500u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x600u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x700u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x800u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x100u, 0x28u, 0u, 0u, 0u, 0u, 4u, 3u, 0u, 0u, 0x100u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x1000300u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0xFF000300u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x500u, 0x50u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x410000u, 0x400u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x500u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_colonel_sides(u32 row)
{
    return state_run(col_sides[row], row, &col_sides_expected[row * 10]);
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
static u32 colonel_pages[8];
#define COLONEL(kind, busy)                                                 \
    do {                                                                    \
        u32* pages = D_801406A8;                                            \
        u8 flag = engine_obj.unk25;                                         \
        struct MainObj* boss = engine_obj.boss_ptr;                         \
        state_reset(0, 0, 0);                                               \
        D_801406A8 = colonel_pages;                                         \
        so.ext.main_69.effect = &effect_objects[0];                         \
        effect_objects[0].active = busy;                                    \
        so.ext.main_69.state.bytes.variant = kind;                          \
        func_80086008(&so);                                                 \
        state_extra = engine_obj.unk25 | (engine_obj.boss_ptr == &so) << 8; \
        D_801406A8 = pages;                                                 \
        engine_obj.unk25 = flag;                                            \
        engine_obj.boss_ptr = boss;                                         \
    } while (0)
static void cn_init_wait(void)
{
    COLONEL(0, 1);
}
static void cn_init(void) { COLONEL(0, 0); }
static void cn_init_rematch(void) { COLONEL(1, 1); }

static void (*const colonel_init_cases[])(void) = {
    cn_init_wait,
    cn_init,
    cn_init_rematch,
};
static const u32 colonel_init_expected[] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 2u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x101u, 0u, 0x102u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x101u, 1u };

static u32 test_colonel_init(u32 row)
{
    return state_run(colonel_init_cases[row], row, &colonel_init_expected[row * 10]);
}

void colonel_flash_strike_slide(struct MainObj*);
void func_800881F8(struct MainObj*);
extern void* D_80104770[25];
static struct VisualObj expected_visuals[32];
static struct EffectObj expected_effects[32];
static u32 white(u32 row)
{
    struct MainObj colonel, expected_colonel;
    struct EffectObj* alarm = &effect_objects[0];
    struct PlayerObj player;
    struct EngineObj engine;
    u32 i;
    (void)row;
    engine_obj.stage = 10;
    engine_obj.substage = 0;
    engine = engine_obj;
    player = g_Player;
    background_objects[0].x_pos.i.hi = 4528;
    background_objects[0].y_pos.i.hi = 808;
    c_test_zero_words((u32*)effect_objects, sizeof(effect_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    memset(&colonel, 0, sizeof(colonel));
    colonel.active = 0x41;
    colonel.id = 69;
    colonel.state = 1;
    colonel.unk5 = 7;
    colonel.unk6 = 3;
    colonel.hp = 48;
    colonel.x_pos.i.hi = 4688;
    colonel.y_pos.i.hi = 928;
    colonel.animation_table = (const u8* const*)D_80104770;
    colonel.unk7C = 20;
    set_animation(&colonel, 6);
    D_8013E198[2] = -1;
    for (i = 0; i < 20; i++)
        colonel_flash_strike_slide(&colonel);
    assert(colonel.unk6 == 4 && colonel.unk17 == 7);
    for (i = 0; i < 19; i++)
        func_800881F8(&colonel);
    assert(colonel.animation_step.fields.event == 1 && colonel.unk6 == 4);
    func_800881F8(&colonel);
    assert(colonel.unk6 == 5 && alarm->active == 0x41 && alarm->id == 37 && alarm->unk2 == 16);
    expected_colonel = colonel;
    memcpy(expected_visuals, visual_objects, sizeof(expected_visuals));
    alarm_flash_update(alarm);
    for (i = 0; i < 9; i++)
        alarm_flash_update(alarm);
    assert(alarm->ext.effect_37.action == 1 && alarm->ext.effect_37.unk22 == 1 && alarm->ext.effect_37.finished == 1 && alarm->ext.effect_37.unk19 == 1);
    memcpy(expected_effects, effect_objects, sizeof(expected_effects));
    expected_effects[0].ext.effect_37.timer = 6;
    expected_effects[0].ext.effect_37.unk19 = 2;
    expected_effects[0].ext.effect_37.finished = 0;
    need_palette_load = 32;
    cur_random = 0x1234;
    alarm_flash_update(alarm);
    c_test_same_words(effect_objects, expected_effects, sizeof(expected_effects));
    c_test_same_words(visual_objects, expected_visuals, sizeof(expected_visuals));
    c_test_same_words(&colonel, &expected_colonel, sizeof(colonel));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    assert(cur_random == 0x1234 && need_palette_load == 37 && g_FilterAmountR == 0 && g_FilterAmountG == 0 && g_FilterAmountB == 0 && D_8013E198[2] == -1);
    return 1;
}

void func_800883CC(struct MainObj*);
extern void* D_80104770[25];
static struct ShotObj shots_expected[32];
static struct VisualObj visuals_expected[32];
static u32 strike(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before;
    struct BackgroundObj background_expected, layer_before;
    u32 available = row % 3, visual_free = row / 3 % 2, face = row / 6 % 2, layer = row / 12, i;
    engine_obj.stage = 10;
    engine_obj.substage = 0;
    engine_before = engine_obj;
    background_objects[layer].x_pos.val = 4528 << 16;
    background_objects[layer].y_pos.val = 808 << 16;
    layer_before = background_objects[layer];
    background_expected = background_objects[0];
    background_expected.unk37 = 16;
    background_expected.unk46 = background_expected.unk3E.bytes[1] = 2;
    background_expected.unk3D = background_expected.unk3B = 1;
    background_expected.unk34 |= 1;
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    for (i = 0; i < COUNT(shot_objects); i++)
        shot_objects[i].active = i >= 32 - available ? 0 : 1;
    memcpy(shots_expected, shot_objects, sizeof(shots_expected));
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = i == 31 && visual_free ? 0 : 1;
    memcpy(visuals_expected, visual_objects, sizeof(visuals_expected));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 69;
    obj.state = 1;
    obj.hp = 48;
    obj.unk5 = 7;
    obj.unk6 = 6;
    obj.unk15 = face ? 0x40 : 0;
    obj.bg_offset = layer;
    obj.x_pos.i.hi = 4688;
    obj.y_pos.i.hi = 928;
    obj.animation_table = (const u8* const*)D_80104770;
    obj.ext.main_69.linked_object = &visual_objects[0];
    visual_objects[0].active = 0x41;
    visual_objects[0].id = 30;
    visual_objects[0].unk50 = PLAYER_OBJECT(&obj);
    visual_objects[0].unk5C.value = 1;
    visuals_expected[0] = visual_objects[0];
    set_animation_frame(ANIMATED_OBJECT(&obj), 7, 16);
    assert(obj.animation_step.packed == 0x33000008);
    expected = obj;
    expected.unk7C = 80;
    expected.unk6++;
    expected.on_screen = 1;
    for (i = 0; i < available; i++) {
        struct ShotObj* s = &shots_expected[32 - available + i];
        s->active = 0x41;
        s->id = 45;
        s->unk2 = i + 16;
        s->unk7C = WEAPON_OBJECT(&obj);
        s->unk8C.object = OBJECT_HEADER(&obj);
    }
    if (visual_free) {
        struct VisualObj* v = &visuals_expected[31];
        v->active = 0x41;
        v->id = 30;
        v->unk2 = 48;
        v->unk50 = PLAYER_OBJECT(&obj);
    }
    D_8013E198[2] = -1;
    func_800883CC(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(shot_objects, shots_expected, sizeof(shots_expected));
    c_test_same_words(visual_objects, visuals_expected, sizeof(visuals_expected));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&background_objects[0], &background_expected, sizeof(background_expected));
    if (layer != 0)
        c_test_same_words(&background_objects[layer], &layer_before, sizeof(layer_before));
    assert(D_8013E198[2] == -1);
    return 1;
}

void func_800881F8(struct MainObj*);
extern void* D_80104770[25];
static struct VisualObj visuals_expected_colonel_flash_strike_pools[32];
static struct EffectObj effects_expected[32];
#define SAME(a, b) assert(c_test_word_difference((const u32*)&(a), (const u32*)&(b), sizeof(a) / 4) == 0)
static u32 strike_pools(u32 row)
{
    struct MainObj obj, expected;
    struct MainObj* current = SP_CUR_MAIN_OBJ;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 free = row % 4, effect_free = row / 4 % 2, event = row / 8 % 2, facing = row / 16 % 2, far = row / 32, i;
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(visual_objects, 0x5A, sizeof(visual_objects));
    memset(effect_objects, 0x5A, sizeof(effect_objects));
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = i < 32 - free;
        effect_objects[i].active = i < 32 - effect_free;
    }
    memcpy(visuals_expected_colonel_flash_strike_pools, visual_objects, sizeof(visuals_expected_colonel_flash_strike_pools));
    memcpy(effects_expected, effect_objects, sizeof(effects_expected));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 69;
    obj.state = 1;
    obj.unk5 = 7;
    obj.unk6 = 4;
    obj.unk7C = 7;
    obj.unk15 = facing ? 0x40 : 0;
    obj.on_screen = 7;
    obj.ext.main_69.linked_object = &visual_objects[0];
    obj.x_pos.val = (far ? 384 : 160) * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)D_80104770;
    set_animation_frame(ANIMATED_OBJECT(&obj), 7, event ? 5 : 0);
    assert(obj.animation_step.packed == (event ? 0x28010101 : 0x24010002));
    expected = obj;
    expected.on_screen = !far;
    if (event) {
        expected.unk6 = 5;
        for (i = 0; i < free; i++) {
            struct VisualObj* v = &visuals_expected_colonel_flash_strike_pools[32 - free + i];
            v->active = 0x41;
            v->id = 30;
            v->unk2 = i == 0 ? 0 : i == 1 ? 32
                                          : 16;
            v->unk50 = PLAYER_OBJECT(&obj);
            if (i == 0) {
                expected.unk7C = 48;
                expected.ext.main_69.linked_object = &visual_objects[32 - free];
            }
            if (i == 2)
                v->unk54 = 80;
        }
        if (effect_free) {
            struct EffectObj* e = &effects_expected[31];
            e->active = 0x41;
            e->id = 37;
            e->unk2 = 16;
            e->ext.effect_37.unk1E = 8;
            e->ext.effect_37.unk1F = 2;
            e->ext.effect_37.unk20 = 3;
            e->ext.effect_37.unk21 = 6;
        }
    } else
        expected.animation_step.fields.duration = 1;
    D_8013E198[2] = -1;
    cur_random = 0x1234;
    SP_CUR_MAIN_OBJ = &obj;
    func_800881F8(&obj);
    assert(SP_CUR_MAIN_OBJ == &obj);
    SP_CUR_MAIN_OBJ = current;
    SAME(obj, expected);
    SAME(g_Player, player_before);
    SAME(engine_obj, engine_before);
    SAME(background_objects, backgrounds_before);
    SAME(visual_objects, visuals_expected_colonel_flash_strike_pools);
    SAME(effect_objects, effects_expected);
    assert(cur_random == 0x1234);
    return 1;
}

void colonel_intro_hall_flash(struct MainObj*);
extern void* D_80104770[25];
static struct EffectObj expected_effects_colonel_hall_flash_effect_capacity[32];
static u32 flash(u32 row)
{
    struct MainObj obj, expected;
    struct EngineObj engine;
    struct PlayerObj player;
    struct BackgroundObj backgrounds[3];
    struct MainBssState main = main_bss_state;
    u32 i;
    u16 rng = cur_random;
    (void)row;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 69;
    obj.unk2 = 1;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.unk7 = 6;
    obj.ext.main_69.state.bytes.variant = 1;
    obj.x_pos.i.hi = 928;
    obj.y_pos.i.hi = 176;
    obj.on_screen = 1;
    obj.animation_table = (const u8* const*)D_80104770;
    set_animation(&obj, 1);
    for (i = 0; i < 40; i++)
        animate_object(ANIMATED_OBJECT(&obj));
    assert(obj.animation_step.packed == 0x0A010001 && obj.animation_cursor == (const u8*)D_80104770[1] + 36);
    c_test_zero_words((u32*)effect_objects, sizeof(effect_objects) / 4);
    for (i = 0; i < COUNT(effect_objects); i++)
        effect_objects[i].active = 1;
    memcpy(expected_effects_colonel_hall_flash_effect_capacity, effect_objects, sizeof(expected_effects_colonel_hall_flash_effect_capacity));
    engine_obj.stage = 9;
    engine_obj.substage = 0;
    engine_obj.enable_boss = 1;
    engine_obj.boss_ptr = &obj;
    engine = engine_obj;
    g_Player.x_pos = obj.x_pos;
    player = g_Player;
    background_objects[0].x_pos.i.hi = 768;
    background_objects[0].y_pos.i.hi = 0;
    memcpy(backgrounds, background_objects, sizeof(backgrounds));
    expected = obj;
    expected.unk7E = 3;
    expected.unk7 = 7;
    expected.unk17 = 2;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = D_80104770[2];
    expected.animation_step.packed = 0x0C010001;
    colonel_intro_hall_flash(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    assert(c_test_word_difference((u32*)effect_objects, (u32*)expected_effects_colonel_hall_flash_effect_capacity, sizeof(expected_effects_colonel_hall_flash_effect_capacity) / 4) == 0);
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(background_objects, backgrounds, sizeof(backgrounds));
    c_test_same_words(&main_bss_state, &main, sizeof(main));
    assert(cur_random == rng);
    return 1;
}

void colonel_intro_hall_portrait_colonel(struct MainObj*);
void colonel_intro_hall_portrait_player(struct MainObj*);
extern void* D_80104770[25];
static struct QuadObj expected_quads[32];
static u32 full(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player;
    struct EngineObj engine;
    u32 i;
    engine_obj.stage = 9;
    engine_obj.substage = 0;
    c_test_zero_words((u32*)g_QuadObjects, sizeof(g_QuadObjects) / 4);
    for (i = 0; i < COUNT(g_QuadObjects); i++)
        g_QuadObjects[i].active = 1;
    memcpy(expected_quads, g_QuadObjects, sizeof(expected_quads));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 69;
    obj.unk2 = 1;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.ext.main_69.state.bytes.variant = 1;
    obj.x_pos.i.hi = 928;
    obj.y_pos.i.hi = 176;
    obj.animation_table = (const u8* const*)D_80104770;
    set_animation(&obj, 0);
    g_Player.x_pos = obj.x_pos;
    colonel_intro_hall_wait_player(&obj);
    assert(obj.unk7 == 1 && obj.unk7C == 120);
    if (row) {
        obj.unk7 = 3;
        obj.unk7C = 0;
        abc_object.unkC = 0;
    } else
        for (i = 0; i < 119; i++)
            colonel_intro_hall_portrait_player(&obj);
    expected = obj;
    if (!row)
        expected.unk7C = 0;
    player = g_Player;
    engine = engine_obj;
    cur_random = 0x1234;
    if (row)
        colonel_intro_hall_portrait_colonel(&obj);
    else
        colonel_intro_hall_portrait_player(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(g_QuadObjects, expected_quads, sizeof(expected_quads));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    assert(cur_random == 0x1234 && abc_object.unkC == 0);
    return 1;
}

void colonel_spawn_afterimages(struct MainObj*);
void colonel_guard(struct MainObj*);
void colonel_saber_waves_start(struct MainObj*);
extern void* D_80104770[25];
extern u8 D_801044B8[8];
extern struct StageObjectRecord stage_object_records_10_0[62];
extern struct Unk_unk68 D_801044F8, D_80104504, D_80104508;
static struct MainObj expected[48];
static struct VisualObj visuals[32];
static u32 frames_colonel_port_script_saber_waves[64];
static u32 zero_difference(const u32* p, u32 count)
{
    u32 different = 0;
    while (count >= 8) {
        different |= p[0] | p[1] | p[2] | p[3] | p[4] | p[5] | p[6] | p[7];
        p += 8;
        count -= 8;
    }
    while (count--)
        different |= *p++;
    return different;
}
static u32 port_script_wave(u32 row)
{
    struct PlayerObj player, entity;
    struct EngineObj engine;
    struct MainBssState main_before;
    struct BackgroundObj cameras[3];
    struct ControllerInput input;
    struct MainObj* current = SP_CUR_MAIN_OBJ;
    struct MainObj* colonel;
    u32 i, record_before[2];
    u16 rng;
    u8 dirty;
    (void)row;
    c_test_copy_words(record_before, (u32*)&stage_object_records_10_0[2], 2);
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    c_test_zero_words((u32*)effect_objects, sizeof(effect_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    for (i = 0; i < 8; i++)
        frames_colonel_port_script_saber_waves[i] = 64;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    engine_obj.stage = 10;
    engine_obj.substage = 0;
    engine_obj.enable_boss = 1;
    engine_obj.unk25 = 1;
    background_objects[0].x_pos.i.hi = 4480;
    background_objects[0].y_pos.i.hi = 752;
    g_Player.active = 0x41;
    g_Player.state = PLAYER_STATE_NORMAL;
    g_Player.hp = 24;
    g_Player.x_pos.i.hi = 4560;
    g_Player.y_pos.i.hi = 928;
    colonel = find_free_main_obj();
    assert(colonel == &main_objects[0]);
    colonel->active = 1;
    colonel->id = 69;
    colonel->backref = &stage_object_records_10_0[2];
    colonel->state = 1;
    colonel->unk5 = 3;
    colonel->hp = 48;
    colonel->contact_damage = 6;
    colonel->x_pos.i.hi = 4688;
    colonel->y_pos.i.hi = 928;
    colonel->unk18 = colonel->x_pos;
    colonel->unk1C = colonel->y_pos;
    colonel->unk16 = 5;
    colonel->unk40 = 0xB0;
    colonel->unk42 = 0x7804;
    colonel->sprite_frames = (u8*)frames_colonel_port_script_saber_waves;
    colonel->animation_table = (const u8* const*)D_80104770;
    colonel->terrain_box = &D_801044F8;
    colonel->ext.main_69.effect = &effect_objects[0];
    engine_obj.boss_ptr = colonel;
    SP_CUR_MAIN_OBJ = colonel;
    set_animation(colonel, 0);
    colonel_spawn_afterimages(colonel);
    assert(visual_objects[31].active == 0x41 && visual_objects[31].id == 5 && visual_objects[30].unk50 == PLAYER_OBJECT(&visual_objects[31]) && visual_objects[29].unk50 == PLAYER_OBJECT(&visual_objects[30]));
    cur_random = 0x1234;
    func_800889DC(colonel);
    assert(cur_random == 0x366A && colonel->ext.main_69.script == D_801044B8);
    colonel_guard(colonel);
    assert(colonel->unk5 == 3 && colonel->unk6 == 1 && colonel->unk7C == 60 && colonel->ext.main_69.script == D_801044B8 + 1);
    for (i = 0; i < 60; i++)
        colonel_guard(colonel);
    assert(colonel->unk6 == 0 && colonel->unk7C == 0);
    colonel_guard(colonel);
    assert(colonel->unk5 == 6 && colonel->unk6 == 0 && colonel->ext.main_69.script == D_801044B8 + 2 && colonel->ext.main_69.state.bytes.variant == 0 && colonel->hp == 48);
    c_test_copy_words((u32*)expected, (u32*)main_objects, sizeof(expected) / 4);
    c_test_copy_words((u32*)visuals, (u32*)visual_objects, sizeof(visuals) / 4);
    player = g_Player;
    entity = g_Entity;
    engine = engine_obj;
    main_before = main_bss_state;
    input = controller_input;
    c_test_copy_words((u32*)cameras, (u32*)background_objects, sizeof(cameras) / 4);
    rng = cur_random;
    dirty = need_palette_load;
    expected[0].unk17 = 4;
    expected[0].previous_animation_index = 255;
    expected[0].animation_cursor = D_80104770[4];
    expected[0].animation_step.packed = 0x14010006;
    expected[0].hurt_box = &D_80104508;
    expected[0].attack_box = &D_80104504;
    expected[0].ext.main_69.state.bytes.wave_delay = 20;
    expected[0].unk7C = 20;
    expected[0].unk6 = 1;
    colonel_saber_waves_start(colonel);
    assert(c_test_word_difference((u32*)main_objects, (u32*)expected, sizeof(expected) / 4) == 0 && c_test_word_difference((u32*)visual_objects, (u32*)visuals, sizeof(visuals) / 4) == 0);
    assert(zero_difference((u32*)shot_objects, sizeof(shot_objects) / 4) == 0 && zero_difference((u32*)weapon_objects, sizeof(weapon_objects) / 4) == 0 && zero_difference((u32*)effect_objects, sizeof(effect_objects) / 4) == 0 && zero_difference((u32*)misc_objects, sizeof(misc_objects) / 4) == 0);
    assert(c_test_word_difference((u32*)&g_Player, (u32*)&player, sizeof(player) / 4) == 0 && c_test_word_difference((u32*)&g_Entity, (u32*)&entity, sizeof(entity) / 4) == 0 && c_test_word_difference((u32*)&engine_obj, (u32*)&engine, sizeof(engine) / 4) == 0 && c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0 && c_test_word_difference((u32*)background_objects, (u32*)cameras, sizeof(cameras) / 4) == 0);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed && cur_random == rng && need_palette_load == dirty && SP_CUR_MAIN_OBJ == colonel && c_test_word_difference((u32*)&stage_object_records_10_0[2], record_before, 2) == 0);
    for (i = 0; i < COUNT(frames_colonel_port_script_saber_waves); i++)
        assert(frames_colonel_port_script_saber_waves[i] == (i < 8 ? 64u : 0));
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    SP_CUR_MAIN_OBJ = current;
    return 1;
}

extern void* D_80104770[25];
extern struct Unk_unk68 D_801044FC, D_80104500, D_80108084[];
static const struct {
    u8 weapon, damage, lethal, flag;
} hits[] = {
    { 255, 0, 0, 0 },
    { 0, 1, 0, 1 },
    { 2, 3, 0, 0 },
    { 4, 0, 0, 0 },
    { 35, 2, 0, 0 },
    { 0, 1, 1, 1 },
};
static const u8 flashes[] = { 0, 1, 2, 64 };
static struct WeaponObj weapons_expected[16];
static struct VisualObj visuals_before[32];
#define SAME_colonel_weapon_defeat(a, b) assert(c_test_word_difference((const u32*)&(a), (const u32*)&(b), sizeof(a) / 4) == 0)
static u32 defeat(u32 row)
{
    struct MainObj obj, expected;
    struct MainObj* current = SP_CUR_MAIN_OBJ;
    struct PlayerObj player_expected;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 hit = row % COUNT(hits), flash = flashes[row / COUNT(hits) % 4], variant = row / COUNT(hits) / 4 % 2, facing = row / COUNT(hits) / 8, i;
    s32 kind = flash || hits[hit].weapon == 4 ? -1 : 0;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.hp = 24;
    player_expected = g_Player;
    if (hits[hit].weapon == 35)
        player_expected.update_delay_request = 1;
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
    obj.id = 69;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 8;
    obj.unk7 = 9;
    obj.on_screen = 7;
    obj.unk15 = facing ? 0x40 : 0;
    obj.unk42 = 0x9234;
    obj.hp = hits[hit].lethal ? 1 : 48;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.hurt_box = &D_801044FC;
    obj.attack_box = &D_80104500;
    obj.collision_data = flash ? D_801060F0 : D_80108084;
    obj.ext.main_69.state.bytes.variant = variant;
    obj.ext.main_69.state.bytes.unk8D = flash;
    obj.ext.main_69.state.bytes.unk8E = flash != 0;
    obj.animation_table = (const u8* const*)D_80104770;
    set_animation(&obj, 0);
    if (hits[hit].weapon != 255) {
        weapon_objects[0].active = 0x21;
        weapon_objects[0].id = hits[hit].weapon;
        weapon_objects[0].unk15 = obj.unk15;
        weapon_objects[0].x_pos = obj.x_pos;
        weapon_objects[0].y_pos = obj.y_pos;
        weapon_objects[0].unk50 = (const u8*)&D_801044FC;
    }
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    expected = obj;
    expected.unk5 = 3;
    expected.unk6 = expected.unk7 = 0;
    expected.unk42 = 0x1234;
    if (hits[hit].weapon != 255) {
        ((s16*)&weapons_expected[0].unk80)[0] = facing ? 158 : 162;
        ((s16*)&weapons_expected[0].unk80)[1] = 115;
        weapons_expected[0].unk98 = flash && hits[hit].weapon == 0 ? -1 : flash ? 0
                                                                                : hits[hit].flag;
        expected.unk63 = kind;
        if (!kind) {
            expected.hp = hits[hit].lethal ? 0 : 48 - hits[hit].damage;
            expected.unk42 |= 0x8000;
        }
    }
    if (flash) {
        expected.ext.main_69.state.bytes.unk8D--;
        if (!(flash & 1))
            expected.unk42 |= 0x8000;
        if (flash == 1) {
            expected.collision_data = D_80108084;
            expected.ext.main_69.state.bytes.unk8E = 0;
        }
    } else if (hits[hit].lethal) {
        expected.state = 2;
        expected.unk5 = variant;
        expected.unk42 &= 0x7FFF;
        expected.on_screen = 1;
        player_expected.spike_immune = 1;
    } else if (!kind && hits[hit].weapon != 255) {
        expected.collision_data = D_801060F0;
        expected.ext.main_69.state.bytes.unk8D = 64;
        expected.ext.main_69.state.bytes.unk8E = 1;
    }
    D_8013E198[0] = D_8013E198[1] = D_8013E198[5] = -1;
    cur_random = 0x1234;
    SP_CUR_MAIN_OBJ = &obj;
    func_80086124(&obj);
    assert(SP_CUR_MAIN_OBJ == &obj);
    SP_CUR_MAIN_OBJ = current;
    SAME_colonel_weapon_defeat(obj, expected);
    SAME_colonel_weapon_defeat(g_Player, player_expected);
    SAME_colonel_weapon_defeat(engine_obj, engine_before);
    SAME_colonel_weapon_defeat(background_objects, backgrounds_before);
    SAME_colonel_weapon_defeat(weapon_objects, weapons_expected);
    SAME_colonel_weapon_defeat(visual_objects, visuals_before);
    assert(cur_random == 0x1234);
    return 1;
}

void colonel_flash_strike_vanish(struct MainObj*);
void colonel_teleport_slash_vanish(struct MainObj*);
extern void* D_80104770[25];
extern struct Unk_unk68 D_801044FC, D_80104500;
static u32 gfx[48], frames_aiming_laser_vanishing_boss[48];
static u32 vanish(u32 row)
{
    struct MainObj target, target_before;
    struct WeaponObj reticle, reticle_before;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj background_before;
    u32 flash = row % 2, face = row / 2, i;
    engine_obj.stage = 10;
    engine_obj.substage = 0;
    engine_obj.cur_character = 0;
    engine_before = engine_obj;
    background_objects[0].x_pos.val = 4528 << 16;
    background_objects[0].y_pos.val = 808 << 16;
    background_before = background_objects[0];
    for (i = 0; i < COUNT(gfx); i++)
        gfx[i] = frames_aiming_laser_vanishing_boss[i] = i < 16 ? 128 + i * 4 : 0x13570000 + i;
    TEST_PLAYER_GFX = (u8*)gfx;
    TEST_SPRITE_FRAMES = (u8*)frames_aiming_laser_vanishing_boss;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.active = 0x41;
    g_Player.state = 1;
    g_Player.hp = 24;
    g_Player.weapon = 6;
    g_Player.weapon_energy[6] = 48;
    g_Player.unk15 = face ? 0x40 : 0;
    g_Player.x_pos.i.hi = 4620;
    g_Player.y_pos.i.hi = 928;
    player_before = g_Player;
    memset(&reticle, 0, sizeof(reticle));
    reticle.active = 0x41;
    reticle.id = 6;
    reticle.unk2 = 3;
    reticle.owner = &g_Player;
    aiming_laser_reticle_init(&reticle, &g_Player);
    assert(reticle.state == 1 && reticle.unk17 == 1 && reticle.animation_step.packed == 0x00010001 && reticle.on_screen == 1);
    reticle_before = reticle;
    memset(&target, 0, sizeof(target));
    target.active = 0x41;
    target.id = 69;
    target.state = 1;
    target.hp = 48;
    target.hurt_box = &D_801044FC;
    target.attack_box = &D_80104500;
    target.unk5 = flash ? 7 : 4;
    target.unk15 = face ? 0x40 : 0;
    target.x_pos.i.hi = 4688;
    target.y_pos.i.hi = 928;
    target.animation_table = (const u8* const*)D_80104770;
    D_8013E198[2] = -1;
    if (flash)
        colonel_flash_strike_vanish(&target);
    else
        colonel_teleport_slash_vanish(&target);
    assert(target.active == 0x41 && target.hp == 48 && target.hurt_box == NULL && target.unk6 == 1);
    target_before = target;
    assert(aiming_laser_try_lock_on(&reticle, &g_Player, &target) == 0);
    c_test_same_words(&reticle, &reticle_before, sizeof(reticle));
    c_test_same_words(&target, &target_before, sizeof(target));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&background_objects[0], &background_before, sizeof(background_before));
    for (i = 0; i < COUNT(gfx); i++)
        assert(gfx[i] == (i < 16 ? 128 + i * 4 : 0x13570000 + i) && frames_aiming_laser_vanishing_boss[i] == gfx[i]);
    assert(TEST_PLAYER_GFX == (u8*)gfx && TEST_SPRITE_FRAMES == (u8*)frames_aiming_laser_vanishing_boss && D_8013E198[2] == -1);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "colonel_init", 0, 0, COUNT(colonel_init_cases), test_colonel_init },
    { "colonel_afterimage_chain_pool", NULL, colonel_afterimage_chain_pool_cases_expected, COUNT(colonel_afterimage_chain_pool_cases_expected), chain_case },
    { "colonel_defeat_animation_context", NULL, colonel_defeat_animation_context_cases_expected, COUNT(colonel_defeat_animation_context_cases_expected), defeat_case },
    { "colonel_hall_far_player", NULL, colonel_hall_far_player_cases_expected, COUNT(colonel_hall_far_player_cases_expected), hall_case },
    { "colonel_incoming", colonel_incoming_cases, colonel_incoming_cases_expected, COUNT(colonel_incoming_cases), 0 },
    { "colonel_dash_brake", 0, 0, 2, test_colonel_dash_brake },
    { "colonel_defeat_blink", 0, 0, 2, test_colonel_defeat_blink },
    { "colonel_defeat_fall", 0, 0, 2, test_colonel_defeat_fall },
    { "colonel_intro_hall_effect", 0, 0, 2, test_colonel_intro_hall_effect },
    { "func_80087A00", 0, 0, 2, test_func_80087A00 },
    { "colonel_states", 0, 0, COUNT(col_cases), test_colonel_states },
    { "colonel_sides", 0, 0, COUNT(col_sides), test_colonel_sides },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "Colonel_actual_flash_factory_white_only_alarm_complete_first_flash", NULL, NULL, 1, white },
    { "own_Colonel_flash_strike_terminal_full_partial_shots_and_visuals", NULL, NULL, 36, strike },
    { "strike_event_partial_full_pools_and_viewport", NULL, NULL, 64, strike_pools },
    { "actual_hall_Colonel_terminal_flash_full_effect_pool_after_filter_expiry", NULL, NULL, 1, flash },
    { "actual_hall_Colonel_variant_both_intro_portraits_full_quad_pool", NULL, NULL, 2, full },
    { "original_port_fullHP_script_guard60_opcode6_wave_delay20", NULL, NULL, 1, port_script_wave },
    { "both_defeat_routes_weapon_damage_and_blink", NULL, NULL, COUNT(hits) * 16, defeat },
    { "own_Aiming_Laser_reticle_rejects_live_Colonel_during_both_real_vanish_transitions", NULL, NULL, 4, vanish },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(colonel_init_cases) + COUNT(colonel_afterimage_chain_pool_cases_expected) + COUNT(colonel_defeat_animation_context_cases_expected) + COUNT(colonel_hall_far_player_cases_expected) + COUNT(colonel_incoming_cases) + 2 + 2 + 2 + 2 + 2 + COUNT(col_cases) + COUNT(col_sides) + COUNT(pool_full_cases) + 1 + 36 + 64 + 1 + 2 + 1 + COUNT(hits) * 16 + 4;
