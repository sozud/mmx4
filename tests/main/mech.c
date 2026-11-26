#include "test_runtime.h"
#include "support/platform_fixture.h"
#include "main/mech.h"
#include "main/195B4.h"
#include "main/mech_state_data.h"
#include "main/55C4.h"
#include "main/player_common.h"
#include "support/scalar_hash.h"
extern union AnimationStep* D_800F9428[31];
extern union AnimationStep* D_800F965C[38];
void func_8003D638(struct VisualObj*, u8);
void func_8003DC1C(struct PlayerObj*, s8);
void func_8003D9E0(struct RideArmorObj*);
s32 func_8003E0B0(struct PlayerObj*);
extern u32* D_80137E08;
extern u8* D_80141EE8[6];
void func_800402C4(struct PlayerObj*);

static s32 frames[8] = { 16, 20, 24, 28, 1, 2, 3, 4 };
static u32 metadata[4] = { 0x400, 0x480, 0x500, 0x580 };
static u32 ride_armor_init_resources_armor_case(u32 mode)
{
    static const u8 cleared_tail[] = { 0x7D, 0x7E, 0x80, 0x81, 0x82, 0x83, 0x86, 0x87, 0x8C, 0x8D, 0x8E, 0x93, 0x97 };
    struct RideArmorObj obj, expected;
    struct EngineObj engine_expected;
    struct PlayerObj player_before = g_Player;
    struct Unk_unk68 box = { -2, -3, 4, 5 };
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 1;
    obj.id = 1;
    obj.unk2 = mode;
    obj.on_screen = 0;
    obj.state = 3;
    obj.unk5 = 4;
    obj.unk6 = 5;
    obj.unk7 = 6;
    obj.bg_offset = 2;
    obj.unk15 = PLAYER_FACING_RIGHT;
    obj.unk16 = VISUAL_SATURN_LAYER(7);
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = 123;
    obj.y_vel.val = 456;
    obj.unk28 = 789;
    obj.unk2C = 987;
    obj.hp = 10;
    obj.unk60 = 11;
    obj.unk61 = 12;
    obj.unk67 = 13;
    obj.unk50 = &box;
    obj.unk54 = &box;
    obj.unk58 = &box;
    obj.unk68 = &box;
    memset(&obj.unk7C, 7, 0xA9 - 0x7C);
    engine_obj.stage = 11;
    engine_obj.substage = 1;
    test_stage_graphics(metadata);
    TEST_MENU_FRAMES = (u8*)frames;
    engine_expected = engine_obj;
    expected = obj;
    expected.active = 0x41;
    expected.on_screen = 1;
    expected.state = 1;
    expected.unk5 = expected.unk6 = 0;
    expected.bg_offset = 0;
    expected.unk15 = 0;
    expected.unk16 = VISUAL_SATURN_LAYER(3);
    expected.hp = 0x20;
    expected.animation_table = (u32**)(mode ? D_800F965C : D_800F9428);
    expected.unk3C = (u8*)frames + 20;
    expected.unk40 = OBJECT_STAGE_TEXTURE(func_8002938C(0x86));
    expected.unk42 = OBJECT_CLUT(0x784C);
    expected.unk50 = expected.unk54 = expected.unk58 = NULL;
    expected.unk68 = &D_800F9124;
    expected.unk60 = expected.unk61 = expected.unk67 = 0;
    expected.x_vel.val = expected.y_vel.val = expected.unk28 = expected.unk2C = 0;
    expected.unk7C = 1;
    expected.spawned_parts = 0;
    expected.unkA6 = 0;
    for (i = 0; i < COUNT(cleared_tail); i++)
        ((u8*)&expected.unk7C)[cleared_tail[i] - 0x7C] = 0;
    assert(s_StageMainIds[11][1][1] == 0x86 && (u8)func_8002938C(0x86) == 1);
    func_8003D4C8(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    for (i = 0; i < 4; i++) {
        assert(frames[i] == 16 + i * 4 && frames[i + 4] == i + 1);
        assert(metadata[i] == 0x400 + i * 0x80);
    }
    assert(box.unk0 == -2 && box.unk1 == -3 && box.unk2 == 4 && box.unk3 == 5);
    assert(D_800F9124.unk0 == 0 && D_800F9124.unk1 == 22 && D_800F9124.unk2 == 15 && D_800F9124.unk3 == 10);
    assert(D_801406A8 == metadata && SP_MENU_FRAMES == frames);
    return obj.unk42 | ((u32)(u8)obj.hp << 16) | ((u32)(obj.animation_table == (u32**)D_800F965C) << 24);
}
static const u32 ride_armor_init_resources_cases_expected[] = { 0x200000u | OBJECT_CLUT(0x784C), 0x1200000u | OBJECT_CLUT(0x784C) };

static s32 sprites[8] = { 16, 20, 24, 28, 1, 2, 3, 4 };
static void expected_animation(struct RideArmorObj* obj, u32 index, u32 step)
{
    obj->unk17 = index;
    obj->previous_animation_index = 0xFF;
    ANIMATED_OBJECT(obj)->animation_cursor = (u32*)(D_800F9428[index] + step);
    obj->animation_step = D_800F9428[index][step];
}
static u32 ride_armor_jump_attack_transitions_armor_case(u32 mode)
{
    struct RideArmorObj obj, expected;
    struct WeaponObj pool_expected[16];
    struct PlayerObj player_expected;
    struct EngineObj engine_expected;
    struct BackgroundObj backgrounds_before[3];
    u32 i, second = mode >= 6, sub = mode >= 12 ? mode - 10 : mode % 6, start = sub < 2;
    u32 free_slot = sub != 1 && sub != 3;
    u32 allocate = start || second && sub <= 3;
    memset(&obj, 0, sizeof(obj));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    for (i = 0; i < 16; i++) {
        weapon_objects[i].active = i == 15 && free_slot ? 0 : 1;
        weapon_objects[i].id = 39;
        weapon_objects[i].state = 40;
        weapon_objects[i].unk2 = 9;
        weapon_objects[i].unk5 = 3;
        weapon_objects[i].unk6 = 4;
        weapon_objects[i].unk42 = 0x7777;
        weapon_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        weapon_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    engine_obj.stage = 11;
    engine_obj.substage = 1;
    g_Player.hp = 30;
    g_Player.ride_animation = 7;
    g_Player.unk6 = 9;
    obj.active = 0x41;
    obj.id = 1;
    obj.state = 1;
    obj.unk5 = second ? 16 : 13;
    obj.unk6 = start ? 0 : 1;
    obj.collision_flags = mode >= 12 ? 0 : 8;
    obj.input_flags = start ? 8 : 0;
    obj.unk8A = sub == 5 ? 0 : 0x10;
    obj.unk86 = start ? 0 : sub == 4 ? 3
                                     : 2;
    obj.unk7D = 7;
    obj.unk98.packed = 0x234;
    obj.unk87 = 9;
    obj.unk15 = PLAYER_FACING_RIGHT;
    obj.unk16 = VISUAL_SATURN_LAYER(3);
    obj.unk40 = 9;
    obj.unk42 = 0x8123;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = 123;
    obj.y_vel.val = -65536;
    obj.unk28 = 789;
    obj.unk2C = 0x8000;
    obj.animation_table = (u32**)D_800F9428;
    obj.unk3C = (u8*)sprites;
    expected_animation(&obj, second ? 11 : 9, start ? 0 : second ? 6
                                                                 : 2);
    expected = obj;
    player_expected = g_Player;
    engine_expected = engine_obj;
    memcpy(pool_expected, weapon_objects, sizeof(pool_expected));
    assert(s_StageMainIds[11][1][1] == 0x86 && (u8)func_8002938C(0x86) == 1);
    if (start) {
        expected.unk5 = 5;
        expected.unk6 = 0;
        expected_animation(&expected, second ? 11 : 9, 0);
        player_expected.ride_animation = second ? 0x3D : 0x33;
        player_expected.unk6 = 0;
        if (second) {
            expected.unk7D = 1;
            expected.unk98.packed = 0x160;
            expected.unk87 = 0;
        }
    } else if (second && sub <= 3) {
        expected.unk5 = 0x11;
        expected_animation(&expected, obj.collision_flags & 8 ? 11 : 13, 0);
        player_expected.ride_animation = obj.collision_flags & 8 ? 0x3D : 0x3C;
        player_expected.unk6 = 0;
    } else {
        if (!second) {
            expected.x_vel.val = 0;
            expected.unk28 = 0;
            expected.y_pos.val += 65536;
            expected.y_vel.val -= 0x8000;
            if (sub <= 3) {
                expected.unk5 = 6;
                expected.unk6 = 0;
            }
        }
        if (--expected.animation_step.fields.duration == 0) {
            ANIMATED_OBJECT(&expected)->animation_cursor += expected.animation_step.fields.relative_step;
            expected.animation_step.packed = *ANIMATED_OBJECT(&expected)->animation_cursor;
        }
    }
    if (allocate && free_slot) {
        struct WeaponObj* child = &pool_expected[15];
        expected.unk86++;
        child->active = 0x41;
        child->id = 0x3B;
        child->unk2 = (obj.collision_flags & 8) != 0;
        child->x_pos.i.hi = 100;
        child->y_pos.i.hi = 200;
        child->animation_table = obj.animation_table;
        child->unk40 = obj.unk40;
        child->unk3C = obj.unk3C;
        child->unk42 = OBJECT_CLUT(0x784C);
        child->unk16 = obj.unk16;
        child->owner = PLAYER_OBJECT(&obj);
        child->unk15 = obj.unk15;
    }
    if (second)
        func_8003FD08(&obj);
    else
        func_8003F76C(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(weapon_objects, pool_expected, sizeof(pool_expected));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    for (i = 0; i < 4; i++)
        assert(sprites[i] == 16 + i * 4 && sprites[i + 4] == i + 1);
    i = (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)obj.unk86 << 16) | ((u32)(weapon_objects[15].active == 0x41) << 24);
    return i;
}
static const u32 ride_armor_jump_attack_transitions_cases_expected[] = { 0x1010005u, 0x5u, 0x20006u, 0x20006u, 0x3010Du, 0x2010Du, 0x1010005u, 0x5u, 0x1030111u, 0x20111u, 0x30110u, 0x20110u, 0x1030111u, 0x20111u };

u32 func_8003DCD8(struct RideArmorObj* arg0);
static u32 test_func_8003DCD8(u32 row)
{
    struct RideArmorObj armor;
    memset(&armor, 0, sizeof(armor));
    armor.unk8A = 0x20;
    armor.unk2 = 1;
    armor.unk7E = 1;
    assert(func_8003DCD8(&armor) == 0);
    armor.unk7E = 0;
    assert(func_8003DCD8(&armor) == 1);
    return 1;
}

static const u32 func_8003D6EC_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_8003D6EC(u32 row)
{
    u32 observed_values[9];
    struct AnimatedObj obj;
    u8 pool_0_full;
    s32 arg1;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    pool_0_full = 255;
    arg1 = 0;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_0_full ? 1 : 0;
    }
    func_8003D6EC(&obj, arg1);
    observed_values[0] = (u32)visual_objects[0].active;
    observed_values[1] = (u32)visual_objects[0].id;
    observed_values[2] = C_TEST_PSX_FACING(visual_objects[0].unk15);
    observed_values[3] = TEST_PSX_LAYER(visual_objects[0].unk16);
    observed_values[4] = (u32)visual_objects[0].unk2;
    observed_values[5] = (u32)visual_objects[0].unk40;
    observed_values[6] = (u32)visual_objects[0].unk42;
    observed_values[7] = (u32)visual_objects[0].x_pos.i.hi;
    observed_values[8] = (u32)visual_objects[0].y_pos.i.hi;
    return c_test_observe(0, row, observed_values, func_8003D6EC_expected, 9);
}

struct func_8003E0D0_case {
    u32 unkF, unk2, attacking, nova_strike_active, unk97;
    u32 expected[3];
};
static const struct func_8003E0D0_case func_8003E0D0_cases[] = {
    { -1, 0, 0, 0, 0, { 0u, 0xFFFFFFFFu, 0u } },
    { 0, -1, -1, 0, 0, { 0u, 0xFFFFFFFFu, 0u } },
    { 0, 0, 0, -1, 0, { 0u, 0xFFFFFFFFu, 0u } },
    { 0, 0, 0, 0, -126, { 0u, 0xFFFFFFFFu, 0xFFFFFF82u } },
};
static u32 test_func_8003E0D0(u32 row)
{
    const struct func_8003E0D0_case* c = &func_8003E0D0_cases[row];
    u32 observed_values[3];
    struct RideArmorObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_800F9124, 0, sizeof(D_800F9124));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.unk6 = -1;
    obj.input_flags = 8;
    engine_obj.unkF = c->unkF;
    g_Player.unk2 = c->unk2;
    g_Player.attacking = c->attacking;
#ifndef VERSION_DEMO
    g_Player.nova_strike_active = c->nova_strike_active;
#endif
    obj.unk94.bytes.unk97 = c->unk97;
    func_8003E0D0(&obj);
    observed_values[0] = (u32)g_Player.ride_state;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)(s8)obj.unk94.bytes.unk97;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

struct func_8003FD08_case {
    u32 collision_flags, input_flags, unk97, unk8A, event, unk86;
    u32 expected[5];
};
static const struct func_8003FD08_case func_8003FD08_cases[] = {
    { 1028, 0, 0, -32640, 0, 0, { 0u, 0xBu, 0u, 0u, 0u } },
    { 0, 8, 0, 0, 0, 0, { 0u, 5u, 0u, 0u, 0u } },
    { 0, 0, 2, 0, 0, 0, { 0u, 0u, 0xFFFFFFFFu, 0u, 0u } },
    { 1028, 0, 0, 0, 0, 0, { 0u, 0u, 0xFFFFFFFFu, 0u, 0u } },
    { 1542, 0, 0, 12336, -1, 3, { 0u, 0u, 0xFFFFFFFFu, 0u, 0u } },
};
static u32 test_func_8003FD08(u32 row)
{
    const struct func_8003FD08_case* c = &func_8003FD08_cases[row];
    u32 observed_values[5];
    struct RideArmorObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    obj.unk6 = -1;
    obj.collision_flags = c->collision_flags;
    obj.input_flags = c->input_flags;
    obj.unk94.bytes.unk97 = c->unk97;
    obj.unk8A = c->unk8A;
    obj.animation_step.fields.event = c->event;
    obj.unk86 = c->unk86;
    func_8003FD08(&obj);
    observed_values[0] = (u32)obj.unk87;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk7D;
    observed_values[4] = (u32)obj.unk98.packed;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

static const u32 func_800405D4_expected[] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_800405D4(u32 row)
{
    u32 observed_values[7];
    struct RideArmorObj obj;
    memset(&obj, 0, sizeof(obj));
    func_800405D4(&obj);
    observed_values[0] = (u32)obj.active;
    observed_values[1] = (u32)obj.on_screen;
    observed_values[2] = (u32)obj.state;
    observed_values[3] = (u32)obj.unk2;
    observed_values[4] = (u32)obj.unk5;
    observed_values[5] = (u32)obj.unk6;
    observed_values[6] = (u32)obj.unk7;
    return c_test_observe(0, row, observed_values, func_800405D4_expected, 7);
}

static u32 armor_bounds(void)
{
    struct PlayerObj armor;
    u32 actual;
    memset(&armor, 0, sizeof(armor));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    armor.last_shot_type = 0x40;
    armor.x_pos.i.hi = 288;
    armor.x_pos.i.lo = 0x4321;
    armor.y_pos.i.hi = 272;
    background_objects[0].unk1E = 300;
    func_800402C4(&armor);
    assert(armor.x_pos.i.lo == 0x4321);
    actual = (u16)armor.x_pos.i.hi | ((u32)(u8)armor.state << 16) | ((u32)(u8)g_Player.hp << 24);
    return actual;
}
static const CTestCase armor_bounds_clamp_cases[] = {
    armor_bounds,
};

static const u32 armor_bounds_clamp_cases_expected[] = { 0x8002014Cu };
#include "support/state_cases.h"

void func_8003DDA0(struct RideArmorObj*);
s32 func_8003DE08(struct MainObj*);
void func_8003DE84(struct RideArmorObj*);
void func_8003DF9C(struct PlayerObj*);
s32 func_8003E048(struct PlayerObj*);
#define sr state_room.ride
#define RIDE(step, phase) (state_reset(step, phase, 0), memset(weapon_objects, 0, sizeof(weapon_objects)))
#define RIDDEN() (state_extra = (u8)sr.unk90.byte | (u8)sr.unk94.bytes.unk97 << 8 | (u8)g_Player.ride_animation << 16 | (u32)(u8)weapon_objects[0].active << 24)
static void r_dash_start(void)
{
    RIDE(0x10, 0);
    sr.unk15 = PLAYER_FACING_RIGHT;
    func_8003F908(&sr);
    RIDDEN();
}
static void r_dash_fall(void)
{
    RIDE(0x10, 1);
    sr.collision_flags = 4;
    sr.unk8A = 0x80;
    func_8003F908(&sr);
}
static void r_dash_rider_dead(void)
{
    RIDE(0x10, 1);
    g_Player.hp = -0x80;
    func_8003F908(&sr);
}
static void r_dash_slash(void)
{
    RIDE(0x10, 1);
    sr.unk8A = 0x10;
    func_8003F908(&sr);
}
static void r_dash_released(void)
{
    RIDE(0x10, 1);
    sr.input_flags = 1;
    func_8003F908(&sr);
}
static void r_dash_run(void)
{
    RIDE(0x10, 1);
    state_room.player.unk88.value = 2;
    sr.unk90.byte = 5;
    sr.x_vel.val = 0x40000;
    func_8003F908(&sr);
    RIDDEN();
}
static void r_dash_run_out(void)
{
    RIDE(0x10, 1);
    state_room.player.unk88.value = 2;
    sr.unk90.byte = -1;
    func_8003F908(&sr);
}
static void r_dash_locked(void)
{
    RIDE(0x10, 1);
    sr.unk94.bytes.unk97 = 2;
    func_8003F908(&sr);
}
static void r_punch_ground(void)
{
    RIDE(0xF, 0);
    sr.collision_flags = 8;
    func_8003FA58(&sr);
    RIDDEN();
}
static void r_punch_air(void)
{
    RIDE(0xF, 0);
    func_8003FA58(&sr);
    RIDDEN();
}
static void r_punch_released(void)
{
    RIDE(0xF, 1);
    sr.unk90.byte = 5;
    sr.input_flags = 2;
    func_8003FA58(&sr);
}
static void r_punch_timeout(void)
{
    RIDE(0xF, 1);
    func_8003FA58(&sr);
}
static void r_punch_repeat(void)
{
    RIDE(0xF, 1);
    sr.unk90.byte = 5;
    func_8003FA58(&sr);
}
static void r_punch_step(void)
{
    RIDE(0xF, 1);
    sr.unk90.byte = 5;
    sr.animation_step.fields.relative_step = 1;
    state_room.player.unk88.value = 2;
    sr.x_vel.val = 0x10000;
    func_8003FA58(&sr);
}
static void r_punch_combo_ground(void)
{
    RIDE(0xF, 1);
    sr.unk90.byte = 5;
    sr.animation_step.fields.relative_step = 1;
    sr.unk8A = 0x10;
    sr.collision_flags = 8;
    func_8003FA58(&sr);
}
static void r_punch_combo_air(void)
{
    RIDE(0xF, 1);
    sr.unk90.byte = 5;
    sr.animation_step.fields.relative_step = 1;
    sr.unk8A = 0x10;
    func_8003FA58(&sr);
}
static void r_punch_locked(void)
{
    RIDE(0xF, 1);
    sr.unk94.bytes.unk97 = 2;
    func_8003FA58(&sr);
}
static void r_charge_start(void)
{
    RIDE(8, 0);
    sr.input_flags = 8;
    sr.unk90.byte = 5;
    func_8003EDF0(&sr);
    RIDDEN();
}
static void r_charge_released(void)
{
    RIDE(8, 1);
    func_8003EDF0(&sr);
}
static void r_charge_done(void)
{
    RIDE(8, 1);
    sr.input_flags = 9;
    func_8003EDF0(&sr);
}
static void r_charge_hold(void)
{
    RIDE(8, 1);
    sr.input_flags = 9;
    sr.unk90.byte = 5;
    sr.x_vel.val = 0x10000;
    func_8003EDF0(&sr);
}
static void r_charge_forward(void)
{
    RIDE(8, 1);
    sr.input_flags = 8;
    sr.unk90.byte = 5;
    state_room.player.unk88.value = 2;
    sr.x_vel.val = 0x10000;
    func_8003EDF0(&sr);
}
static void r_charge_idle(void)
{
    RIDE(8, 1);
    sr.input_flags = 8;
    sr.unk90.byte = 5;
    func_8003EDF0(&sr);
}
static void r_charge_locked(void)
{
    RIDE(8, 1);
    sr.input_flags = 8;
    sr.unk94.bytes.unk97 = 2;
    func_8003EDF0(&sr);
}
static void r_rush_fall(void)
{
    RIDE(5, 1);
    sr.collision_flags = 4;
    sr.unk8A = 0x80;
    func_8003F31C(&sr);
}
static void r_rush_released(void)
{
    RIDE(5, 1);
    func_8003F31C(&sr);
}
static void r_rush_blocked(void)
{
    RIDE(5, 1);
    sr.input_flags = 8;
    sr.unk94.bytes.unk97 = 0x10;
    func_8003F31C(&sr);
}
static void r_rush_x(void)
{
    RIDE(5, 1);
    sr.input_flags = 8;
    func_8003F31C(&sr);
    RIDDEN();
}
static void r_rush_zero(void)
{
    RIDE(5, 1);
    sr.input_flags = 8;
    sr.unk2 = 1;
    sr.unk15 = PLAYER_FACING_RIGHT;
    func_8003F31C(&sr);
    RIDDEN();
}
static void r_rush_locked(void)
{
    RIDE(5, 1);
    sr.unk94.bytes.unk97 = 2;
    func_8003F31C(&sr);
}
static void r_rush_run_fall(void)
{
    RIDE(5, 2);
    g_Player.hp = -0x80;
    func_8003F244(&sr);
}
static void r_rush_run_released(void)
{
    RIDE(5, 2);
    func_8003F244(&sr);
}
static void r_rush_run_turn(void)
{
    RIDE(5, 2);
    sr.input_flags = 8;
    state_room.player.unk88.value = 1;
    func_8003F244(&sr);
}
static void r_rush_run_end(void)
{
    RIDE(5, 2);
    sr.input_flags = 8;
    sr.unk90.byte = 1;
    func_8003F244(&sr);
}
static void r_rush_run(void)
{
    RIDE(5, 2);
    sr.input_flags = 8;
    sr.unk90.byte = 3;
    sr.x_vel.val = 0x20000;
    func_8003F244(&sr);
    RIDDEN();
}
static void r_land_done(void)
{
    RIDE(9, 0);
    func_8003F204(&sr);
}
static void r_land(void)
{
    RIDE(9, 0);
    sr.animation_step.fields.relative_step = 1;
    func_8003F204(&sr);
}
static void r_attack_x(void)
{
    RIDE(6, 0);
    sr.input_flags = 8;
    func_8003F570(&sr);
}
static void r_attack_zero(void)
{
    RIDE(6, 0);
    sr.unk2 = 1;
    func_8003F570(&sr);
}
static void r_buttons_cooldown(void)
{
    RIDE(1, 0);
    sr.unk8C.bytes.cooldown = 1;
    func_8003DE84(&sr);
}
static void r_buttons_locked(void)
{
    RIDE(1, 0);
    sr.unk94.bytes.unk97 = 2;
    func_8003DE84(&sr);
}
static void r_buttons_press(void)
{
    RIDE(1, 0);
    sr.unk8A = 1;
    func_8003DE84(&sr);
    state_extra = sr.unk8E.bytes.timer | sr.pad9A << 8;
}
static void r_buttons_dash(void)
{
    RIDE(1, 0);
    sr.unk8E.bytes.active = 1;
    sr.unk8E.bytes.timer = 3;
    sr.pad9A = 1;
    sr.unk8A = 1;
    func_8003DE84(&sr);
    RIDDEN();
}
static void r_buttons_hover(void)
{
    RIDE(1, 0);
    sr.unk8E.bytes.active = 1;
    sr.unk8E.bytes.timer = 3;
    sr.pad9A = 1;
    sr.unk8A = 1;
    sr.unk67 = 1;
    func_8003DE84(&sr);
    RIDDEN();
}
static void r_buttons_expire(void)
{
    RIDE(3, 0);
    sr.unk8E.bytes.active = 1;
    sr.unk8E.bytes.timer = 1;
    sr.pad9A = 1;
    sr.unk8A = 1;
    func_8003DE84(&sr);
    state_extra = sr.unk8E.bytes.active;
}
static void r_walk_start(void)
{
    RIDE(1, 0);
    sr.input_flags = 8;
    func_8003E368(&sr);
}
static void r_walk_dismount(void)
{
    RIDE(1, 1);
    sr.unk94.bytes.pad94[0] = 2;
    func_8003E368(&sr);
}
static void r_walk_fall(void)
{
    RIDE(1, 1);
    g_Player.hp = -0x80;
    func_8003E368(&sr);
}
static void r_walk_released(void)
{
    RIDE(1, 1);
    func_8003E368(&sr);
}
static void r_walk_wall(void)
{
    RIDE(1, 1);
    sr.input_flags = 8;
    sr.collision_flags = 2;
    func_8003E368(&sr);
}
static void r_walk_jump(void)
{
    RIDE(1, 1);
    sr.input_flags = 8;
    sr.unk8A = 0x80;
    func_8003E368(&sr);
}
static void r_walk_attack(void)
{
    RIDE(1, 1);
    sr.input_flags = 8;
    sr.unk8A = 0x10;
    func_8003E368(&sr);
}
static void r_walk_locked(void)
{
    RIDE(1, 1);
    sr.input_flags = 8;
    sr.unk94.bytes.unk97 = 2;
    func_8003E368(&sr);
}
static void r_hover_ground(void)
{
    RIDE(0x11, 0);
    sr.collision_flags = 8;
    func_8003FD08(&sr);
    RIDDEN();
}
static void r_hover_air(void)
{
    RIDE(0x11, 0);
    func_8003FD08(&sr);
    RIDDEN();
}
static void r_hover_fall(void)
{
    RIDE(0x11, 1);
    g_Player.hp = -0x80;
    func_8003FD08(&sr);
}
static void r_hover_mount(void)
{
    RIDE(0x11, 1);
    sr.input_flags = 8;
    func_8003FD08(&sr);
}
static void r_hover_jump(void)
{
    RIDE(0x11, 1);
    sr.unk8A = 0x80;
    func_8003FD08(&sr);
}
static void r_hover_end(void)
{
    RIDE(0x11, 1);
    sr.animation_step.fields.relative_step = -1;
    func_8003FD08(&sr);
}
static void r_hover_punch_ground(void)
{
    RIDE(0x11, 1);
    sr.animation_step.fields.event = 1;
    sr.unk8A = 0x10;
    sr.collision_flags = 8;
    func_8003FD08(&sr);
    RIDDEN();
}
static void r_hover_punch_air(void)
{
    RIDE(0x11, 1);
    sr.animation_step.fields.event = 1;
    sr.unk8A = 0x10;
    func_8003FD08(&sr);
    RIDDEN();
}
static void r_hover_wall(void)
{
    RIDE(0x11, 1);
    sr.collision_flags = 1;
    func_8003FD08(&sr);
}
static void r_hover_locked(void)
{
    RIDE(0x11, 1);
    sr.unk94.bytes.unk97 = 2;
    func_8003FD08(&sr);
}
static void r_air_punch_ground(void)
{
    RIDE(6, 0);
    sr.collision_flags = 8;
    func_8003F76C(&sr);
    RIDDEN();
}
static void r_air_punch(void)
{
    RIDE(6, 0);
    func_8003F76C(&sr);
    RIDDEN();
}
static void r_air_punch_mount(void)
{
    RIDE(6, 1);
    sr.input_flags = 8;
    func_8003F76C(&sr);
}
static void r_air_punch_rise(void)
{
    RIDE(6, 1);
    sr.y_vel.val = -1;
    sr.collision_flags = 0x80;
    func_8003F76C(&sr);
}
static void r_air_punch_land(void)
{
    RIDE(6, 1);
    sr.input_flags = 4;
    sr.y_vel.val = 0x10000;
    func_8003F76C(&sr);
}
static void r_air_punch_drop(void)
{
    RIDE(6, 1);
    sr.animation_step.fields.relative_step = 1;
    sr.y_vel.val = -0x70000;
    sr.collision_flags = 0x81;
    sr.unk98.packed = 0x100;
    func_8003F76C(&sr);
}
static void r_air_punch_again(void)
{
    RIDE(6, 1);
    sr.animation_step.fields.relative_step = 1;
    sr.animation_step.fields.event = 1;
    sr.unk8A = 0x10;
    func_8003F76C(&sr);
}
static void r_air_punch_locked(void)
{
    RIDE(6, 1);
    sr.unk94.bytes.unk97 = 2;
    func_8003F76C(&sr);
}
static void r_rider_stomp(void)
{
    RIDE(1, 0);
    sr.unk8A = 0x100;
    func_8003DF9C(PLAYER_OBJECT(&sr));
}
static void r_rider_hover(void)
{
    RIDE(1, 0);
    sr.unk8A = 0x100;
    state_room.player.air_state = 1;
    func_8003DF9C(PLAYER_OBJECT(&sr));
}
static void r_rider_held(void)
{
    RIDE(1, 0);
    sr.unk8A = 0x100;
    state_room.player.air_state = 1;
    state_room.player.input.bytes.held_high = 1;
    func_8003DF9C(PLAYER_OBJECT(&sr));
}
static void r_wall_left(void)
{
    RIDE(1, 0);
    sr.collision_flags = 2;
    sr.unk98.packed = 0x100;
    func_8003DDA0(&sr);
}
static void r_hop_start(void)
{
    RIDE(0xE, 0);
    func_8003EA08(&sr);
    RIDDEN();
}
static void r_hop_mount(void)
{
    RIDE(0xE, 1);
    sr.input_flags = 8;
    func_8003EA08(&sr);
}
static void r_hop_rise(void)
{
    RIDE(0xE, 1);
    sr.y_vel.val = -1;
    sr.collision_flags = 0x80;
    func_8003EA08(&sr);
}
static void r_hop_drop(void)
{
    RIDE(0xE, 1);
    sr.animation_step.fields.relative_step = 1;
    sr.y_vel.val = -0x70000;
    sr.collision_flags = 0x80;
    func_8003EA08(&sr);
}
static void r_kind_zero_start(void)
{
    RIDE(0, 0);
    sr.unk2 = 1;
    state_extra = func_8003DE08(MAIN_OBJECT(&sr));
}
static void r_kind_zero_other(void)
{
    RIDE(3, 0);
    sr.unk2 = 1;
    state_extra = func_8003DE08(MAIN_OBJECT(&sr));
}
static void r_kind_x_other(void)
{
    RIDE(3, 0);
    state_extra = func_8003DE08(MAIN_OBJECT(&sr));
}
static void r_dash_input_forward(void)
{
    RIDE(1, 0);
    state_room.player.last_shot_type = 8;
    state_room.player.unk88.value = 2;
    state_extra = func_8003E048(PLAYER_OBJECT(&sr));
}
static void r_dash_input_stomp(void)
{
    RIDE(1, 0);
    state_room.player.last_shot_type = 8;
    state_room.player.unk88.value = 0x100;
    sr.unk15 = PLAYER_FACING_RIGHT;
    state_extra = func_8003E048(PLAYER_OBJECT(&sr));
}
static void r_mount_start(void)
{
    RIDE(0, 0);
    func_8003E0D0(&sr);
}
static void r_mount_released(void)
{
    RIDE(0, 1);
    func_8003E0D0(&sr);
}
static void r_mount_busy(void)
{
    RIDE(0, 1);
    sr.input_flags = 8;
    g_Player.script_state = 1;
    func_8003E0D0(&sr);
}
static void r_back_input(void)
{
    RIDE(1, 0);
    sr.unk15 = PLAYER_FACING_RIGHT;
    state_room.player.unk88.value = 2;
    state_extra = func_8003E0B0(PLAYER_OBJECT(&sr));
}
static void r_shot_full(void)
{
    RIDE(1, 0);
    sr.unk86 = 3;
    func_8003D8A8(&sr, 0, 0);
    RIDDEN();
}

static void (*const ride_armor_states_cases[])(void) = {
    r_dash_start,
    r_dash_fall,
    r_dash_rider_dead,
    r_dash_slash,
    r_dash_released,
    r_dash_run,
    r_dash_run_out,
    r_dash_locked,
    r_punch_ground,
    r_punch_air,
    r_punch_released,
    r_punch_timeout,
    r_punch_repeat,
    r_punch_step,
    r_punch_combo_ground,
    r_punch_combo_air,
    r_punch_locked,
    r_charge_start,
    r_charge_released,
    r_charge_done,
    r_charge_hold,
    r_charge_forward,
    r_charge_idle,
    r_charge_locked,
    r_rush_fall,
    r_rush_released,
    r_rush_blocked,
    r_rush_x,
    r_rush_zero,
    r_rush_locked,
    r_rush_run_fall,
    r_rush_run_released,
    r_rush_run_turn,
    r_rush_run_end,
    r_rush_run,
    r_land_done,
    r_land,
    r_attack_x,
    r_attack_zero,
    r_buttons_cooldown,
    r_buttons_locked,
    r_buttons_press,
    r_buttons_dash,
    r_buttons_hover,
    r_buttons_expire,
    r_walk_start,
    r_walk_dismount,
    r_walk_fall,
    r_walk_released,
    r_walk_wall,
    r_walk_jump,
    r_walk_attack,
    r_walk_locked,
    r_hover_ground,
    r_hover_air,
    r_hover_fall,
    r_hover_mount,
    r_hover_jump,
    r_hover_end,
    r_hover_punch_ground,
    r_hover_punch_air,
    r_hover_wall,
    r_hover_locked,
    r_air_punch_ground,
    r_air_punch,
    r_air_punch_mount,
    r_air_punch_rise,
    r_air_punch_land,
    r_air_punch_drop,
    r_air_punch_again,
    r_air_punch_locked,
    r_rider_stomp,
    r_rider_hover,
    r_rider_held,
    r_wall_left,
    r_hop_start,
    r_hop_mount,
    r_hop_rise,
    r_hop_drop,
    r_kind_zero_start,
    r_kind_zero_other,
    r_kind_x_other,
    r_dash_input_forward,
    r_dash_input_stomp,
    r_mount_start,
    r_mount_released,
    r_mount_busy,
    r_back_input,
    r_shot_full,
};
static const u32 ride_armor_states_expected[] = { 0xC00u, 0xFF400000u, 0u, 0u, 0x42000u, 0u, 0u, 0x50000u, 0x2F001Eu, 0u, 0xB00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0xB00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x1000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0xC00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x11000u, 0u, 0x40000u, 0u, 0x40000u, 0u, 0u, 0x40000u, 4u, 0u, 0xC00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x11000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0xC00u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0x413700FFu, 0u, 0xC00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0x410000FFu, 0u, 0xC00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0xC00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10F00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10F00u, 0u, 0x10000u, 0u, 0x10000u, 0u, 0u, 0x40000u, 0u, 0u, 0x1000u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x1000u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10F00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10800u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0x41370004u, 0u, 0xC00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x800u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10800u, 0u, 0x10000u, 0u, 0x10000u, 0u, 0u, 0x40000u, 0u, 0u, 0x10800u, 0u, 0x10000u, 0u, 0x10000u, 0u, 0u, 0x40000u, 0u, 0u, 0x10800u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10800u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0xB00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0xC00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10500u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x20500u, 0xFF000000u, 0u, 0u, 0xFFFBE000u, 0u, 0u, 0x40000u, 0x4136001Eu, 0u, 0x20500u, 0xFF400100u, 0u, 0u, 0x42000u, 0u, 0u, 0x40000u, 0x4136001Eu, 0u, 0x10500u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0xB00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0xC00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x30500u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x30500u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x20500u, 0u, 0x20000u, 0u, 0x20000u, 0u, 0u, 0x40000u, 2u, 0u, 0x100u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x900u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x20600u, 0xFF000000u, 0u, 0u, 0xFFFBE000u, 0u, 0u, 0x40000u, 0u, 0u, 0xC00u, 0xFF000100u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0x4100u, 0x100u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x100u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x100u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x10Cu, 0u, 0x700u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x800u, 0u, 0xF00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x800u, 0u, 0x300u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x10100u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0xD00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0xB00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0xC00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x200u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x400u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x300u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10100u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x11100u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0x413D0000u, 0u, 0x11100u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0x41000000u, 0u, 0xB00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x500u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0xC00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0xE00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x11100u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x413D0000u, 0u, 0x11100u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x413C0000u, 0u, 0x11100u, 0x400000u, 0x16000u, 0u, 0x16000u, 0u, 0u, 0x40000u, 0u, 0u, 0x11100u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10400u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0x41330000u, 0u, 0x10400u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0x41000000u, 0u, 0x500u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x10C00u, 0u, 0u, 0u, 0u, 0xFFFFFFFFu, 0u, 0x40000u, 0u, 0u, 0x10400u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10600u, 0u, 0x10000u, 0x5E000u, 0x10000u, 0xFFFA2000u, 0u, 0x40000u, 0u, 0u, 0x600u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10600u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x700u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0xF00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x100u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x100u, 0u, 0u, 0u, 0xFFFF0000u, 0u, 0u, 0x50000u, 0u, 0u, 0x10400u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0x41330000u, 0u, 0x500u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x10C00u, 0u, 0u, 0u, 0u, 0xFFFFFFFFu, 0u, 0x40000u, 0u, 0u, 0x10E00u, 0u, 0u, 0x5E000u, 0u, 0xFFFA2000u, 0u, 0x40000u, 0u, 0u, 0u, 0x100u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 1u, 0u, 0x300u, 0x100u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 1u, 0u, 0x300u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 1u, 0u, 0x100u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 2u, 0u, 0x100u, 0x400000u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x100u, 0u, 0x10000u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0xC00u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x100u, 0x400000u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 2u, 0u, 0x100u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_ride_armor_states(u32 row)
{
    return object_run(ride_armor_states_cases[row], row, &ride_armor_states_expected[row * 10]);
}

static struct WeaponObj armor_release_expected_weapons[16];
static u8 armor_release_sound_commands[9 * 4];

static u32 test_armor_part_release(u32 row)
{
    static const u8 free_counts[] = { 0, 1, 3, 16, 16 };
    static const u8 cancel_states[] = { 3, 6, 9, 10, 11, 13, 16, 17 };
    struct RideArmorObj obj, expected;
    struct PlayerObj player_before;
    u32 i, part, next_slot, free_count = row < 40 ? free_counts[row / 8] : 16;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(armor_release_sound_commands, 0, sizeof(armor_release_sound_commands));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    D_80141F50[5] = armor_release_sound_commands;
    for (i = 0; i < 16 - free_count; i++) {
        weapon_objects[i].active = 1;
        weapon_objects[i].id = 1;
        weapon_objects[i].x_pos.val = i * 65536;
    }
    engine_obj.stage = 11;
    engine_obj.substage = 1;
    obj.active = 0x41;
    obj.id = 1;
    obj.unk2 = 1;
    obj.state = 1;
    obj.unk5 = row < 40 ? 1 : cancel_states[row - 40];
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.unk15 = row & 1 ? PLAYER_FACING_RIGHT : 0;
    obj.unk16 = VISUAL_SATURN_LAYER(3);
    obj.animation_table = (u32**)D_800F965C;
    obj.unk3C = frames;
    obj.unk40 = 0x2468;
    obj.unk42 = 0x1357;
    obj.unk94.value = C_TEST_PSX_WORD(0x40000902);
    obj.unkA6 = 0x30;
    obj.unk7E = 0x7B;
    obj.spawned_parts = row < 40 ? row % 8 : 5;
    obj.unk86 = row >= 32 && row < 40 ? 3 : 0;
    expected = obj;
    player_before = g_Player;
    memcpy(armor_release_expected_weapons, weapon_objects, sizeof(weapon_objects));
    expected.unk94.value = C_TEST_PSX_WORD(0x40000900);
    expected.unkA6 = 0;
    next_slot = 16 - free_count;
    if (row < 40) {
        expected.spawned_parts = 7;
        expected.unk7E = 16;
        for (part = 0; part < 3; part++) {
            struct WeaponObj* shot;
            if ((obj.spawned_parts & (1 << part)) || obj.unk86 == 3 || next_slot == 16)
                continue;
            shot = &armor_release_expected_weapons[next_slot++];
            shot->active = 0x41;
            shot->id = 60;
            shot->unk2 = part;
            shot->x_pos.val = 100 * 65536;
            shot->y_pos.val = 200 * 65536;
            shot->animation_table = obj.animation_table;
            shot->unk3C = obj.unk3C;
            shot->unk40 = obj.unk40;
            shot->unk42 = OBJECT_CLUT(0x784C);
            shot->unk16 = obj.unk16;
            shot->owner = PLAYER_OBJECT(&obj);
            shot->unk15 = obj.unk15;
        }
    }
    assert(s_StageMainIds[11][1][1] == 0x86);
    func_8003D9E0(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(weapon_objects, armor_release_expected_weapons, sizeof(weapon_objects));
    return 1;
}

static const struct {
    u8 phase, blocked, held, pressed, dead, next_step, next_phase, animated;
} armor_recovery_cases[] = {
    { 0, 0, 0, 0, 0, 1, 0, 1 },
    { 0, 1, 0, 0, 0, 8, 1, 1 },
    { 1, 1, 0, 0, 0, 8, 1, 1 },
    { 1, 0, 0, 0, 0, 1, 0, 1 },
    { 0, 0, 0, 0, 1, 11, 0, 0 },
    { 1, 1, 0, 0, 1, 11, 0, 0 },
    { 0, 1, 4, 0x80, 0, 11, 0, 0 },
    { 1, 0, 4, 0x80, 0, 11, 0, 0 },
};

static u32 test_armor_recovery(u32 row)
{
    struct RideArmorObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before = engine_obj;
    u32 index = row / 2, variant = row % 2;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 1;
    obj.unk2 = variant;
    obj.state = 1;
    obj.unk5 = 8;
    obj.unk6 = armor_recovery_cases[index].phase;
    obj.unk94.bytes.unk97 = armor_recovery_cases[index].blocked ? 2 : 0;
    obj.unk98.packed = 0x234;
    obj.collision_flags = armor_recovery_cases[index].held;
    obj.unk8A = armor_recovery_cases[index].pressed;
    obj.unk15 = variant ? PLAYER_FACING_RIGHT : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = 0x18000;
    obj.y_vel.val = -0x24000;
    obj.animation_table = (u32**)(variant ? D_800F965C : D_800F9428);
    set_animation(&obj, 7);
    assert(obj.animation_step.packed == C_TEST_STEP(0x0D000008u));
    if (obj.unk6 != 0)
        obj.animation_step.fields.duration = 7;
    obj.previous_animation_index = 13;
    g_Player.hp = armor_recovery_cases[index].dead ? -0x80 : 20;
    g_Player.ride_animation = 7;
    g_Player.unk6 = 9;
    expected = obj;
    player_expected = g_Player;
    expected.unk5 = armor_recovery_cases[index].next_step;
    expected.unk6 = armor_recovery_cases[index].next_phase;
    if (armor_recovery_cases[index].phase == 0) {
        expected.unk98.packed = 0x160;
        expected.previous_animation_index = 0xFF;
        player_expected.ride_animation = 0x30;
        player_expected.unk6 = 0;
    }
    if (armor_recovery_cases[index].animated)
        expected.animation_step.fields.duration--;
    func_8003ED00(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

extern union AnimationStep* D_800F9428[31];
extern union AnimationStep* D_800F965C[38];
static struct VisualObj visuals_before[32];
static struct BackgroundObj backgrounds_before[3];
static const struct {
    u8 dead, blocked, pressed, held, collision, next;
    s8 timer;
} dash_scenes[] = {
    { 0, 0, 0, 8, 0, 7, 9 },
    { 1, 0, 0, 8, 0, 11, 9 },
    { 0, 2, 0x90, 0, 0, 7, 9 },
    { 0, 0, 0x10, 8, 0, 9, 9 },
    { 0, 0, 0, 0, 0, 12, 9 },
    { 0, 0, 0, 9, 0, 8, 9 },
    { 0, 0, 0, 8, 0x80, 8, 9 },
    { 0, 0, 0, 8, 0, 8, -1 },
    { 0, 0, 0, 8, 0, 7, 1 },
    { 0, 0, 0x80, 8, 0, 4, 9 },
    { 0, 0, 0x80, 8, 4, 11, 9 },
    { 1, 2, 0x10, 0, 0, 11, 9 },
};
static u32 dash_transition(u32 row)
{
    struct RideArmorObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before = engine_obj;
    struct MainBssState main_before;
    u32 scene = row % COUNT(dash_scenes), variant = row / COUNT(dash_scenes) % 2, facing = row / COUNT(dash_scenes) / 2;
    u32 i, next = dash_scenes[scene].next, move = scene == 0 || scene == 7 || scene == 8;
    u32 seed = cur_random;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    for (i = 0; i < 32; i++)
        visual_objects[i].active = 1;
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    main_bss_state.frame_counter = 1;
    main_before = main_bss_state;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.hp = dash_scenes[scene].dead ? -0x80 : 20;
    g_Player.ride_animation = 7;
    g_Player.unk6 = 9;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 1;
    obj.unk2 = variant;
    obj.state = 1;
    obj.unk5 = 7;
    obj.unk6 = scene != 0;
    obj.unk15 = facing ? PLAYER_FACING_RIGHT : 0;
    obj.unk94.bytes.unk97 = dash_scenes[scene].blocked;
    obj.unk8A = dash_scenes[scene].pressed;
    obj.input_flags = dash_scenes[scene].held;
    obj.collision_flags = dash_scenes[scene].collision == 0x80 ? 0 : dash_scenes[scene].collision | (facing ? 1 : 2);
    obj.unk90.byte = dash_scenes[scene].timer;
    obj.unk98.packed = 0x420;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = facing ? 0x42000 : -0x42000;
    obj.y_vel.val = 0x23456;
    obj.animation_table = (u32**)(variant ? D_800F965C : D_800F9428);
    set_animation(&obj, 5);
    assert(obj.animation_step.packed == C_TEST_STEP(0x0D010004));
    obj.previous_animation_index = 0x35;
    expected = obj;
    player_expected = g_Player;
    if (scene == 0) {
        expected.unk6 = 1;
        expected.unk90.byte = 29;
        expected.previous_animation_index = 0xFF;
        player_expected.ride_animation = 0x2F;
        player_expected.unk6 = 0;
    }
    if (next != 7) {
        expected.unk5 = next;
        expected.unk6 = 0;
    }
    if (move) {
        expected.x_pos.val += obj.x_vel.val;
        if (scene != 0)
            expected.unk90.byte--;
    }
    if (next != 11 && next != 8)
        expected.animation_step.fields.duration = 3;
    func_8003EB4C(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_bss_state));
    c_test_same_words(visual_objects, visuals_before, sizeof(visuals_before));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(cur_random == seed);
    return 1;
}

extern union AnimationStep* D_800F965C[];
static u32 release(u32 row)
{
    struct RideArmorObj obj, expected;
    struct WeaponObj weapons_expected[16];
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u32 mask = row == 18, mode = row % 6, wall = row / 6 % 3, free = row == 18, i, slot = 0;
    memset(&obj, 0, sizeof(obj));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    for (i = 0; i < 16; i++) {
        weapon_objects[i].active = free && i < 3 ? 0 : 1;
        weapon_objects[i].id = 39;
        weapon_objects[i].state = 7;
        weapon_objects[i].unk42 = 0x8123;
    }
    engine_obj.stage = 11;
    engine_obj.substage = 1;
    g_Player.hp = mode == 5 ? -128 : 30;
    D_8013E198[5] = -1;
    obj.active = 0x41;
    obj.id = 1;
    obj.unk2 = 1;
    obj.state = 1;
    obj.unk5 = 5;
    obj.unk6 = 4;
    obj.unk15 = PLAYER_FACING_RIGHT;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.unk16 = VISUAL_SATURN_LAYER(3);
    obj.unk40 = 9;
    obj.collision_flags = wall;
    obj.input_flags = mode == 3 ? 0 : 8;
    obj.spawned_parts = mask;
    obj.unk94.bytes.unk97 = mode == 1 ? 2 : mode == 2 ? 0x10
                                                      : 0;
    obj.unk94.bytes.pad94[0] = mode == 4;
    obj.animation_table = (u32**)D_800F965C;
    set_animation(&obj, 14);
    assert(obj.animation_step.packed == C_TEST_STEP(0x25000005));
    expected = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    assert(s_StageMainIds[11][1][1] == 0x86 && (u8)func_8002938C(0x86) == 1);
    if (mode == 5) {
        expected.unk5 = 11;
        expected.unk6 = 0;
    } else {
        expected.animation_step.fields.duration = 4;
        if (mode == 3) {
            expected.unk5 = 12;
            expected.unk6 = 0;
        } else if (mode != 1) {
            expected.unk15 = wall == 2 ? 0 : PLAYER_FACING_RIGHT;
            if (mode == 0) {
                expected.unk6 = 5;
                expected.unk7E = 16;
                expected.spawned_parts = 7;
                if (free)
                    for (i = 0; i < 3; i++)
                        if (!(mask & (1 << i))) {
                            struct WeaponObj* child = &weapons_expected[slot++];
                            child->active = 0x41;
                            child->id = 60;
                            child->unk2 = i;
                            child->x_pos.i.hi = 100;
                            child->y_pos.i.hi = 120;
                            child->animation_table = obj.animation_table;
                            child->unk40 = 9;
                            child->unk3C = obj.unk3C;
                            child->unk42 = OBJECT_CLUT(0x784C);
                            child->unk16 = VISUAL_SATURN_LAYER(3);
                            child->owner = PLAYER_OBJECT(&obj);
                            child->unk15 = expected.unk15;
                        }
            }
        }
    }
    func_8003F44C(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    assert(c_test_word_difference((u32*)weapon_objects, (u32*)weapons_expected, sizeof(weapons_expected) / 4) == 0);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(D_8013E198[5] == -1);
    return 1;
}

extern union AnimationStep* D_800F965C[];
static u32 stop_entries[9];
static u32 mount(u32 row)
{
    struct RideArmorObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before = engine_obj;
    u32 character = row % 2, attack = row / 2 % 2, hp = row / 4 % 3, immune = row / 12 % 2, spikes = row / 24 % 2, hurt = row / 48;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 1;
    obj.unk2 = 1;
    obj.state = 1;
    obj.unk5 = 0;
    obj.unk6 = 1;
    obj.input_flags = 8;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.unk68 = &D_800F9124;
    obj.animation_table = (u32**)D_800F965C;
    set_animation(&obj, 17);
    assert(obj.animation_step.packed == C_TEST_STEP(0x2C000001));
    g_Player.active = 0x41;
    g_Player.state = 1;
    g_Player.unk2 = character;
    g_Player.attacking = attack;
    g_Player.hp = hp == 0 ? 0 : hp == 1 ? 1
                                        : 30;
    SPIKE_IMMUNE_SET(g_Player, immune);
    g_Player.touching_spikes = spikes;
    g_Player.hurt_phase = hurt;
    g_Player.x_pos = obj.x_pos;
    g_Player.y_pos.val = obj.y_pos.val + 20 * 65536;
    g_Player.unk68 = character ? &player_zero_collision_bounds : &player_x_collision_bounds;
    engine_obj.unkF = 0;
    engine_before = engine_obj;
    player_expected = g_Player;
    expected = obj;
    if ((!character || !attack) && hp && !immune && !spikes && !hurt) {
        expected.unk5 = 10;
        expected.unk6 = 0;
        expected.unk94.bytes.unk97 = 0x40;
        player_expected.ride_state = 1;
        expected.unk17 = 18;
        expected.previous_animation_index = 255;
        expected.animation_cursor = (u32*)D_800F965C[18];
        expected.animation_step.packed = C_TEST_STEP(0x2A01000A);
    }
    func_8003E0D0(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}
static u32 dismount(u32 row)
{
    struct RideArmorObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before = engine_obj;
    u32 start = row % 2, blocked = row / 2 % 2, riding = row / 4 % 2, held = row / 8 % 2, character = row / 16, i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(stop_entries, 0, sizeof(stop_entries));
    D_80141F50[5] = (u8*)stop_entries;
    obj.active = 0x41;
    obj.id = 1;
    obj.unk2 = 1;
    obj.state = 1;
    obj.unk5 = 11;
    obj.unk6 = !start;
    obj.input_flags = held ? 8 : 0;
    obj.unk94.bytes.unk97 = (blocked ? 2 : 0) | (riding ? 0x40 : 0);
    obj.unk94.bytes.pad94[0] = 1;
    obj.unkA6 = 9;
    obj.unk8C.value = C_TEST_PSX_WORD(7);
    obj.unk42 = 0x8123;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_vel.val = 0x12345;
    obj.y_vel.val = 0x34567;
    obj.unk28 = 0x1234;
    obj.unk2C = 0x4000;
    obj.animation_table = (u32**)D_800F965C;
    set_animation(&obj, 19);
    assert(obj.animation_step.packed == C_TEST_STEP(0x27010005));
    g_Player.unk2 = character;
    g_Player.ride_state = riding;
    g_Player.hp = 30;
    player_expected = g_Player;
    expected = obj;
    if (start) {
        expected.unk6 = 1;
        expected.unk61 = 1;
        expected.unk68 = &D_800F9124;
        expected.unk8C.value = 0;
        expected.unk94.bytes.pad94[0] = 0;
        expected.unkA6 = 0;
        if (!blocked) {
            expected.x_vel.val = expected.unk28 = 0;
            expected.y_vel.val = 0x20000;
            expected.unk2C = 0x4000;
        }
        if (riding) {
            if (!blocked)
                expected.y_vel.val = expected.unk2C = 0;
            expected.unk94.bytes.unk97 &= ~0x40;
            player_expected.ride_state = 0;
            player_expected.unk68 = character ? &player_zero_collision_bounds : &player_x_collision_bounds;
        }
        if (!held) {
            expected.unk5 = 12;
            expected.unk6 = 0;
        }
        expected.unk42 = 0x0123;
    }
    if (held)
        expected.y_vel.val = 0;
    if (!blocked) {
        expected.x_pos.val += expected.x_vel.val;
        expected.y_pos.val -= expected.y_vel.val;
        expected.x_vel.val -= expected.unk28;
        expected.y_vel.val -= expected.unk2C;
    }
    expected.animation_step.fields.duration = 4;
    func_8003EEF8(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(D_80141F50[5] == (u8*)stop_entries);
    for (i = 0; i < 9; i++)
        assert(stop_entries[i] == 0);
    return 1;
}
static u32 air_interrupt(u32 row)
{
    struct RideArmorObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    u32 mode = row % 4, wall = row / 4;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.hp = mode == 1 ? -128 : 30;
    player_before = g_Player;
    obj.active = 0x41;
    obj.id = 1;
    obj.unk2 = 1;
    obj.state = 1;
    obj.unk5 = 14;
    obj.unk6 = 1;
    obj.collision_flags = wall;
    obj.unk94.bytes.unk97 = mode == 3 ? 2 : 0;
    obj.input_flags = mode == 2 ? 8 : 0;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.unk15 = PLAYER_FACING_RIGHT;
    obj.animation_table = (u32**)D_800F965C;
    set_animation(&obj, 13);
    assert(obj.animation_step.packed == C_TEST_STEP(0x15010101));
    expected = obj;
    if (mode == 1 || mode == 2) {
        expected.unk5 = mode == 1 ? 11 : 5;
        expected.unk6 = 0;
    } else {
        if (mode != 3 && wall) {
            expected.unk15 = wall == 2 ? 0 : PLAYER_FACING_RIGHT;
            expected.x_vel.val = wall == 2 ? -0x16000 : 0x16000;
            expected.x_pos.val += expected.x_vel.val;
        }
        expected.animation_cursor++;
        expected.animation_step.packed = C_TEST_STEP(0x16010101);
    }
    func_8003FBD8(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

extern union AnimationStep* D_800F9428[31];
extern struct Unk_unk68 D_800F9120, D_800F9128;
void func_8003D9E0(struct RideArmorObj*);
void func_8003E274(struct RideArmorObj*);

#define RIDE_BYTE(object, offset) (((u8*)&(object)->unk7C)[(offset)-0x7C])
static struct RideArmorObj armor;

static void prepare(void)
{
    u32 i;
    c_test_zero_words((u32*)&armor, sizeof(armor) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = i < 30;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    g_Player.ride_animation = 0x11;
    g_Player.unk6 = 5;
    armor.active = 0x41;
    armor.id = 1;
    armor.state = 1;
    armor.unk5 = 4;
    armor.unk15 = PLAYER_FACING_RIGHT;
    armor.unk16 = VISUAL_SATURN_LAYER(3);
    armor.x_pos.val = 0x01000000;
    armor.y_pos.val = 0x00800000;
    armor.unk40 = 9;
    armor.unk42 = 0xF84C;
    armor.animation_table = (u32**)D_800F9428;
    armor.collision_flags = 0x30;
    armor.unkA6 = 0x30;
}

static u32 finish(void)
{
    u32 hash = hash_animated(0, (struct AnimatedObj*)&armor);
    hash = HASH_SPAN(hash, &armor, hp, unk67);
    hash = HASH_SPAN(hash, &armor, unk6C, saved_x_vel);
    hash = hash * 31 + armor.launch_speed + (armor.unkA6 << 16);
    hash = hash * 31 + (u8)armor.input_flags;
    hash = hash * 31 + (armor.unk68 == &D_800F9120) + 2 * (armor.unk54 == &D_800F9128);
    hash = hash * 31 + (u8)g_Player.ride_animation + (g_Player.unk6 << 8);
    return hash_visuals(hash, &armor);
}

static u32 idle_phase(u32 row)
{
    static const u8 phases[] = { 3, 4, 0x7F, 0x80, 0xFF };
#ifdef MMX4_SATURN
    static const u32 expected[COUNT(phases)] = { 0x50DFAAFDu, 0xBAC6811Cu, 0x9CAF6201u, 0x06963820u, 0x901A7181u };
#else
    static const u32 expected[COUNT(phases)] = { 3657060973u, 1138829452u, 633997681u, 2410733456u, 422910193u };
#endif
    u32 hash;
    prepare();
    RIDE_BYTE(&armor, 0x94) = phases[row];
    RIDE_BYTE(&armor, 0x95) = 7;
    hash = finish();
    func_8003D9E0(&armor);
    assert(finish() == hash);
    return c_test_observe(0, row, &hash, &expected[row], 1);
}

static u32 recover(u32 row)
{
#ifdef MMX4_SATURN
    static const u32 expected[32] = {
        0xCDD2C987u,
        0xB9D8BFE8u,
        0x5271D6A3u,
        0x3E77CD04u,
        0xB4C19EE4u,
        0xA0C79545u,
        0x3960AC00u,
        0x2566A261u,
        0xCDD2C987u,
        0xB9D8BFE8u,
        0x3B2CC87Au,
        0x2732BEDBu,
        0xB4C19EE4u,
        0xA0C79545u,
        0xABEFC1E0u,
        0x97F5B841u,
        0x9EAB9B60u,
        0x8AB191C1u,
        0xF95F5FFFu,
        0xDCE218A0u,
        0x859A70BDu,
        0x71A0671Eu,
        0x5BEB0E9Cu,
        0x3F6DC73Du,
        0x9EAB9B60u,
        0x8AB191C1u,
        0x118EA17Bu,
        0xFD9497DCu,
        0x859A70BDu,
        0x71A0671Eu,
        0x82519AE1u,
        0x6E579142u,
    };
#else
    static const u32 expected[32] = {
        2581318737u,
        2246165170u,
        4053105748u,
        3717952181u,
        2160763310u,
        1825609743u,
        3632550321u,
        3297396754u,
        2581318737u,
        2246165170u,
        2153115244u,
        1817961677u,
        2160763310u,
        1825609743u,
        4044941266u,
        3709787699u,
        1790221866u,
        1455068299u,
        2165685057u,
        1687712738u,
        1369666439u,
        1034512872u,
        3819006430u,
        3341034111u,
        1790221866u,
        1455068299u,
        515246189u,
        180092622u,
        1369666439u,
        1034512872u,
        2407072211u,
        2071918644u,
    };
#endif
    u32 hash;
    prepare();
    armor.id = row & 1 ? 0 : 1;
    armor.unk6 = row >> 1 & 1;
    RIDE_BYTE(&armor, 0x8C) = row & 4 ? 3 : 0;
    RIDE_BYTE(&armor, 0x8D) = row & 16 ? 1 : 0;
    armor.unk61 = 9;
    armor.animation_step.fields.duration = 2;
    armor.animation_step.fields.relative_step = row & 8 ? 0 : 1;
    armor.animation_step.fields.event = row & 16 ? 1 : 0;
    func_8003E274(&armor);
    hash = finish();
    return c_test_observe(1, row, &hash, &expected[row], 1);
}

extern union AnimationStep* D_800F965C[38];
static struct WeaponObj expected_weapons[16];
static u32 punch(u32 row)
{
    struct RideArmorObj obj, expected;
    struct PlayerObj player;
    struct EngineObj engine;
    struct MainBssState main = main_bss_state;
    s8 bank = D_8013E198[5];
    u16 rng = cur_random;
    u32 i;
    (void)row;
    engine_obj.stage = 11;
    engine_obj.substage = 1;
    engine = engine_obj;
    g_Player.ride_state = 1;
    g_Player.hp = 24;
    player = g_Player;
    player.ride_animation = 0x31;
    player.unk6 = 0;
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    for (i = 0; i < COUNT(weapon_objects); i++)
        weapon_objects[i].active = 1;
    memcpy(expected_weapons, weapon_objects, sizeof(expected_weapons));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 1;
    obj.state = 1;
    obj.unk5 = 3;
    obj.hp = 24;
    obj.on_screen = 1;
    obj.x_pos.i.hi = 100;
    obj.y_pos.i.hi = 120;
    obj.unk16 = VISUAL_SATURN_LAYER(3);
    obj.animation_table = (u32**)D_800F965C;
    set_animation(&obj, 0);
    expected = obj;
    expected.unk6 = 1;
    expected.animation_cursor = (u32*)D_800F965C[8];
    expected.animation_step.packed = C_TEST_STEP(0x25010004);
    expected.unk17 = 8;
    expected.previous_animation_index = 0xFF;
    D_8013E198[5] = -1;
    func_8003E5F8(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    assert(c_test_word_difference((u32*)weapon_objects, (u32*)expected_weapons, sizeof(expected_weapons) / 4) == 0);
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    c_test_same_words(&main_bss_state, &main, sizeof(main));
    assert(cur_random == rng && D_8013E198[5] == -1);
    D_8013E198[5] = bank;
    return 1;
}

void func_8003E488(struct RideArmorObj*);
void func_8003E750(struct RideArmorObj*);
void func_8003E8A0(struct RideArmorObj*);
void func_8003EA08(struct RideArmorObj*);
void func_8003ED00(struct RideArmorObj*);
void func_8003EDF0(struct RideArmorObj*);
void func_8003F068(struct RideArmorObj*);
void func_8003F244(struct RideArmorObj*);
void func_8003F76C(struct RideArmorObj*);
void func_8003F908(struct RideArmorObj*);
void func_8003FA58(struct RideArmorObj*);
void func_8003FBD8(struct RideArmorObj*);
void func_8003EEF8(struct RideArmorObj*);
void func_8003F31C(struct RideArmorObj*);
void func_8003F618(struct RideArmorObj*);
void func_8003F648(struct RideArmorObj*);
void func_8003F698(struct RideArmorObj*);
void func_8003FF9C(struct RideArmorObj*);
void func_800400C8(struct PlayerObj*);
void func_800401F8(struct PlayerObj*);
void func_80040248(struct RideArmorObj*);
#define RIDE_WRECK_BLINKS(r) (((u8*)&(r)->collision_flags)[9])
#define RIDE_WRECK_FRAMES(r) (((u8*)&(r)->collision_flags)[10])
static void (*const ride_handlers[])(struct RideArmorObj*) = {
    func_8003E488,
    func_8003E5F8,
    func_8003E750,
    func_8003E8A0,
    func_8003EA08,
    func_8003ED00,
    func_8003EDF0,
    func_8003F068,
    func_8003F244,
    func_8003F76C,
    func_8003F908,
    func_8003FA58,
    func_8003FBD8,
    func_8003EEF8,
    func_8003F31C,
    func_8003F618,
    func_8003F648,
    func_8003F698,
};
enum { H_WALK,
    H_PUNCH,
    H_JUMP,
    H_LAND,
    H_AIR_PUNCH,
    H_STEP,
    H_SLIDE,
    H_FALL,
    H_RUSH,
    H_AIR_SHOT,
    H_DASH,
    H_SHOT,
    H_HOVER,
    H_EXIT,
    H_SPIN,
    H_RECOVER,
    H_RECOVERY,
    H_ZERO_PUNCH };
#define RIDE_STEP(duration, event, relative) C_TEST_STEP((duration) | (event) << 8 | (relative) << 16)
static const struct {
    u8 fn, phase, unk2, right, pad, flags, input, coll, bits, unk7D, unk7E, unk87, unk81, unk86, dead, tick;
    s8 timer;
    u16 speed;
    u32 step;
    s32 vx, vy, ay;
    u32 e_state, e_x, e_y, e_vx, e_vy, e_anim, e_spawn, e_flags;
    s8 snd;
} ride_handler_rows[] = {
    { .fn = H_WALK, .pad = 2, .e_state = 0x0D, .e_anim = 0x2A000005, .e_flags = 0x01600000, .snd = -1 },
    { .fn = H_WALK, .phase = 1, .dead = 1, .e_state = 0x0B, .e_anim = 5, .snd = -1 },
    { .fn = H_WALK, .phase = 1, .input = 8, .flags = 2, .e_state = 0x0122, .e_anim = 4, .e_flags = 0x200, .snd = -1 },
    { .fn = H_WALK, .phase = 1, .input = 8, .e_state = 0x01, .e_anim = 5, .snd = -1 },
    { .fn = H_WALK, .phase = 1, .input = 8, .coll = 2, .bits = 0x80, .e_state = 0x04, .e_anim = 5, .snd = -1 },
    { .fn = H_WALK, .phase = 1, .input = 8, .coll = 1, .bits = 0x30, .e_state = 0x03, .e_anim = 5, .e_flags = 0x40, .snd = -1 },
    { .fn = H_WALK, .phase = 1, .input = 8, .coll = 1, .step = RIDE_STEP(5, 1, 0), .e_state = 0x0122, .e_x = 0x16000, .e_vx = 0x16000, .e_anim = 4, .e_flags = 0x40, .snd = 1 },
    { .fn = H_PUNCH, .unk87 = 1, .e_state = 0x01, .e_anim = 0x32000005, .e_spawn = 0x3E41, .snd = 5 },
    { .fn = H_PUNCH, .phase = 1, .unk81 = 1, .e_state = 0x01000003, .e_anim = 5, .snd = -1 },
    { .fn = H_PUNCH, .phase = 1, .step = RIDE_STEP(5, 1, 1), .bits = 0x30, .e_state = 0x01010122, .e_anim = 0x104, .snd = -1 },
    { .fn = H_PUNCH, .phase = 1, .step = RIDE_STEP(5, 1, 1), .e_state = 0x0122, .e_anim = 0x104, .snd = -1 },
    { .fn = H_PUNCH, .phase = 1, .step = RIDE_STEP(5, 1, 1), .bits = 0x30, .unk81 = 1, .e_state = 0x01000122, .e_anim = 0x104, .snd = -1 },
    { .fn = H_PUNCH, .phase = 1, .step = RIDE_STEP(5, 1, 1), .bits = 0x30, .unk87 = 2, .e_state = 0x00020122, .e_anim = 0x104, .snd = -1 },
    { .fn = H_JUMP, .e_state = 0x0C, .e_vy = 0x58000, .e_anim = 0x2B000005, .e_spawn = 0x0C410000, .snd = 4 },
    { .fn = H_JUMP, .unk2 = 1, .bits = 0x30, .e_state = 0x06, .e_vy = 0x58000, .e_anim = 0x2B000005, .snd = 3 },
    { .fn = H_JUMP, .phase = 1, .dead = 1, .e_state = 0x0B, .e_anim = 5, .snd = -1 },
    { .fn = H_JUMP, .phase = 1, .flags = 2, .e_state = 0x0122, .e_anim = 5, .e_flags = 0x200, .snd = -1 },
    { .fn = H_JUMP, .phase = 1, .input = 4, .coll = 0x80, .e_state = 0x0C, .e_anim = 5, .snd = -1 },
    { .fn = H_JUMP, .phase = 1, .coll = 0x80, .vy = -1, .e_state = 0x0C, .e_vy = 0xFFFFFFFF, .e_anim = 5, .snd = -1 },
    { .fn = H_LAND, .e_state = 0x01, .e_anim = 0x2D000005, .e_flags = 0x01600000, .snd = 1 },
    { .fn = H_LAND, .unk2 = 1, .e_state = 0x01, .e_anim = 0x2D000005, .e_flags = 0x01600000, .snd = 0 },
    { .fn = H_LAND, .phase = 1, .dead = 1, .e_state = 0x0B, .e_anim = 5, .snd = -1 },
    { .fn = H_LAND, .phase = 1, .step = RIDE_STEP(5, 0, 1), .flags = 2, .e_state = 0x0122, .e_anim = 4, .e_flags = 0x200, .snd = -1 },
    { .fn = H_LAND, .phase = 1, .step = RIDE_STEP(5, 0, 1), .e_state = 0x0C, .e_anim = 4, .snd = -1 },
    { .fn = H_LAND, .phase = 1, .step = RIDE_STEP(5, 0, 1), .input = 8, .bits = 0x30, .e_state = 0x03, .e_anim = 4, .snd = -1 },
    { .fn = H_LAND, .phase = 1, .step = RIDE_STEP(5, 0, 1), .input = 8, .coll = 1, .e_state = 0x0122, .e_x = 0x16000, .e_vx = 0x16000, .e_anim = 4, .e_flags = 0x40, .snd = -1 },
    { .fn = H_LAND, .phase = 1, .step = RIDE_STEP(5, 0, 1), .input = 8, .e_state = 0x0122, .e_anim = 4, .snd = -1 },
    { .fn = H_AIR_PUNCH, .phase = 1, .flags = 2, .e_state = 0x0122, .e_anim = 4, .e_flags = 0x200, .snd = -1 },
    { .fn = H_AIR_PUNCH, .phase = 1, .input = 4, .vy = 0x10000, .e_state = 0x0104, .e_anim = 4, .snd = -1 },
    { .fn = H_AIR_PUNCH, .phase = 1, .coll = 0x80, .vy = 0x10000, .step = RIDE_STEP(5, 0, 1), .e_state = 0x0122, .e_y = 0xFFFF0000, .e_vy = 0x10000, .e_anim = 4, .snd = -1 },
    { .fn = H_STEP, .phase = 1, .step = RIDE_STEP(5, 0, 1), .bits = 0x80, .e_state = 0x04, .e_anim = 4, .snd = -1 },
    { .fn = H_STEP, .phase = 1, .step = RIDE_STEP(5, 0, 1), .bits = 0x30, .e_state = 0x03, .e_anim = 4, .snd = -1 },
    { .fn = H_STEP, .phase = 1, .step = RIDE_STEP(5, 0, 1), .coll = 1, .e_state = 0x03, .e_anim = 4, .snd = -1 },
    { .fn = H_STEP, .phase = 1, .step = RIDE_STEP(5, 0, 1), .e_state = 0x0122, .e_anim = 4, .snd = -1 },
    { .fn = H_SLIDE, .phase = 1, .input = 8, .step = RIDE_STEP(5, 1, 0), .timer = 5, .vx = 0x20000, .tick = 1, .e_state = 0x0122, .e_x = 0x20000, .e_vx = 0x20000, .e_anim = 0x40104, .snd = -1 },
    { .fn = H_FALL, .flags = 0x40, .input = 8, .e_state = 0x05, .e_anim = 0x2C000005, .e_flags = 0x4000, .snd = -1 },
    { .fn = H_FALL, .input = 8, .e_state = 0x0B, .e_anim = 5, .snd = -1 },
    { .fn = H_FALL, .phase = 1, .flags = 0x40, .dead = 1, .e_state = 0x0B, .e_anim = 5, .e_flags = 0x4000, .snd = -1 },
    { .fn = H_FALL, .phase = 1, .flags = 0x42, .e_state = 0x0122, .e_anim = 5, .e_flags = 0x4200, .snd = -1 },
    { .fn = H_FALL, .phase = 1, .flags = 0x40, .bits = 0x30, .e_state = 0x06, .e_anim = 5, .e_flags = 0x4000, .snd = -1 },
    { .fn = H_FALL, .phase = 1, .flags = 0x40, .unk2 = 1, .bits = 0x80, .e_state = 0x0E, .e_anim = 5, .e_flags = 0x4000, .snd = -1 },
    { .fn = H_FALL, .phase = 1, .flags = 0x40, .unk2 = 1, .unk7D = 1, .bits = 0x80, .vx = 0x30000, .ay = 0x1000, .e_state = 0x0122, .e_vy = 0xFFFFF000, .e_anim = 5, .e_flags = 0x4000, .snd = -1 },
    { .fn = H_FALL, .phase = 1, .flags = 0x40, .vy = -0x60000, .e_state = 0x0122, .e_y = 0x5E000, .e_vy = 0xFFFA2000, .e_anim = 5, .e_flags = 0x4000, .snd = -1 },
    { .fn = H_FALL, .phase = 1, .flags = 0x40, .unk2 = 1, .coll = 1, .speed = 0x100, .vx = 0x30000, .e_state = 0x0122, .e_x = 0x10000, .e_vx = 0x10000, .e_anim = 5, .e_flags = 0x01004040, .snd = -1 },
    { .fn = H_FALL, .phase = 1, .vy = 0x10000, .ay = 0x1000, .e_state = 0x0122, .e_y = 0xFFFF0000, .e_vy = 0xF000, .e_anim = 5, .snd = -1 },
    { .fn = H_RUSH, .phase = 1, .flags = 2, .e_state = 0x0122, .e_anim = 4, .e_flags = 0x200, .snd = -1 },
    { .fn = H_AIR_SHOT, .phase = 1, .coll = 0x80, .vy = 0x10000, .step = RIDE_STEP(5, 0, 1), .e_state = 0x0122, .e_y = 0xFFFF0000, .e_vy = 0x10000, .e_anim = 4, .snd = -1 },
    { .fn = H_DASH, .flags = 2, .e_state = 0x0122, .e_vx = 0xFFFBE000, .e_anim = 0x2F1E0004, .e_flags = 0x04200200, .snd = 2 },
    { .fn = H_SHOT, .phase = 1, .timer = 5, .step = RIDE_STEP(5, 0, 1), .bits = 0x30, .unk86 = 3, .e_state = 0x0122, .e_anim = 0x40004, .snd = -1 },
    { .fn = H_HOVER, .e_state = 0x0122, .e_anim = 0x3C000004, .e_flags = 0x01600000, .snd = 5 },
    { .fn = H_HOVER, .phase = 1, .bits = 0x80, .e_state = 0x0C, .e_anim = 5, .snd = -1 },
    { .fn = H_HOVER, .phase = 1, .bits = 0x30, .e_state = 0x11, .e_anim = 5, .snd = -1 },
    { .fn = H_JUMP, .phase = 1, .coll = 0x82, .vy = 0x10000, .speed = 0x100, .e_state = 0x0122, .e_x = 0xFFFF0000, .e_y = 0xFFFF0000, .e_vx = 0xFFFF0000, .e_vy = 0x10000, .e_anim = 5, .e_flags = 0x01000000, .snd = -1 },
    { .fn = H_EXIT, .phase = 1, .pad = 3, .vy = 0x10000, .e_state = 0, .e_y = 0xFFFF0000, .e_vy = 0x10000, .e_anim = 4, .snd = -1 },
    { .fn = H_SPIN, .phase = 1, .input = 8, .pad = 1, .e_state = 0x0122, .e_anim = 4, .snd = -1 },
    { .fn = H_RECOVER, .phase = 1, .e_state = 0x01, .e_anim = 5, .snd = -1 },
    { .fn = H_RECOVER, .phase = 1, .unk7E = 3, .e_state = 0x0122, .e_anim = 5, .snd = -1 },
    { .fn = H_RECOVERY, .phase = 1, .flags = 2, .e_state = 0x0122, .e_anim = 5, .e_flags = 0x200, .snd = -1 },
    { .fn = H_RECOVERY, .phase = 3, .e_state = 0x01, .e_anim = 5, .snd = -1 },
    { .fn = H_ZERO_PUNCH, .e_state = 0x01, .e_anim = 0x3F000005, .e_spawn = 0x3B41, .snd = 7 },
    { .fn = H_ZERO_PUNCH, .phase = 1, .step = RIDE_STEP(5, 1, 1), .bits = 0x30, .e_state = 0x03, .e_anim = 0x104, .snd = -1 },
    { .fn = H_ZERO_PUNCH, .phase = 1, .step = RIDE_STEP(5, 0, 1), .e_state = 0x0122, .e_anim = 4, .snd = -1 },
    { .fn = H_ZERO_PUNCH, .phase = 1, .step = RIDE_STEP(5, 1, 1), .e_state = 0x0122, .e_anim = 0x104, .snd = -1 },
    { .fn = H_ZERO_PUNCH, .phase = 1, .step = RIDE_STEP(5, 1, 1), .bits = 0x30, .unk86 = 3, .e_state = 0x0122, .e_anim = 0x104, .snd = -1 },
};

#ifdef MMX4_SATURN
#define SOUND_CHECK_RIDE(expression) ((void)0)
#else
#define SOUND_CHECK_RIDE(expression) assert(expression)
#endif
static u32 ride_sound_rows[0x100];
static void ride_sound_probe(void)
{
    memset(D_8013E198, -1, sizeof(D_8013E198));
#ifndef MMX4_SATURN
    memset(ride_sound_rows, 0, sizeof(ride_sound_rows));
    D_8013E198[5] = 0;
    D_80141F50[5] = (u8*)ride_sound_rows;
    D_80141EE8[5] = (u8*)&ride_sound_rows[0xFF];
#endif
    D_80137E08 = NULL;
}
static s32 ride_sound_id(void)
{
    return D_80137E08 == NULL ? -1 : (s32)(D_80137E08 - ride_sound_rows);
}

static void ride_room(u8 phase)
{
    RIDE(0x22, phase);
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    g_Player.hp = 16;
    sr.active = 0x41;
    main_bss_state.frame_counter = 1;
    cur_random = 0x100;
    ride_sound_probe();
}

static u32 test_ride_handlers(u32 row)
{
    struct RideArmorObj* r = &sr;
    ride_room(ride_handler_rows[row].phase);
    r->unk2 = ride_handler_rows[row].unk2;
    r->unk15 = ride_handler_rows[row].right ? PLAYER_FACING_RIGHT : 0;
    r->unk94.bytes.pad94[0] = ride_handler_rows[row].pad;
    r->unk94.bytes.unk97 = ride_handler_rows[row].flags;
    r->input_flags = ride_handler_rows[row].input;
    r->collision_flags = ride_handler_rows[row].coll;
    r->unk8A = ride_handler_rows[row].bits;
    r->unk7D = ride_handler_rows[row].unk7D;
    r->unk87 = ride_handler_rows[row].unk87;
    r->unk80.bytes.unk81 = ride_handler_rows[row].unk81;
    r->unk86 = ride_handler_rows[row].unk86;
    r->unk7E = ride_handler_rows[row].unk7E;
    r->unk90.byte = ride_handler_rows[row].timer;
    r->unk98.packed = ride_handler_rows[row].speed;
    if (ride_handler_rows[row].step)
        r->animation_step.packed = ride_handler_rows[row].step;
    r->x_vel.val = ride_handler_rows[row].vx;
    r->y_vel.val = ride_handler_rows[row].vy;
    r->unk2C = ride_handler_rows[row].ay;
    if (ride_handler_rows[row].dead)
        g_Player.hp = -0x80;
    if (ride_handler_rows[row].tick)
        main_bss_state.frame_counter = 0;
    ride_handlers[ride_handler_rows[row].fn](r);
    assert(((u8)r->unk5 | (u8)r->unk6 << 8 | (u8)r->unk87 << 16 | (u32)r->unk80.bytes.unk81 << 24) == ride_handler_rows[row].e_state);
    assert((u32)r->x_pos.val == ride_handler_rows[row].e_x && (u32)r->y_pos.val == ride_handler_rows[row].e_y);
    assert((u32)r->x_vel.val == ride_handler_rows[row].e_vx && (u32)r->y_vel.val == ride_handler_rows[row].e_vy);
    assert(((u8)r->animation_step.fields.duration | (u8)r->animation_step.fields.event << 8 | (u8)r->unk90.byte << 16
               | (u32)(u8)g_Player.ride_animation << 24)
        == ride_handler_rows[row].e_anim);
    assert((weapon_objects[0].active | weapon_objects[0].id << 8 | visual_objects[0].active << 16 | (u32)visual_objects[0].id << 24)
        == ride_handler_rows[row].e_spawn);
    assert((C_TEST_PSX_FACING(r->unk15) | r->unk94.bytes.unk97 << 8 | (u32)(u16)r->unk98.packed << 16) == ride_handler_rows[row].e_flags);
    assert(cur_random == (ride_handler_rows[row].tick ? 0x90C : 0x100));
    SOUND_CHECK_RIDE(ride_sound_id() == ride_handler_rows[row].snd);
    return 1;
}

static const struct {
    u8 pad, count, mode, flags, coll, a6, unk2;
    u32 e_hold, e_visual;
    s8 snd;
} ride_hold_rows[] = {
    { .mode = 0x80, .flags = 0x80, .coll = 0x30, .e_hold = 0, .snd = -1 },
    { .coll = 0x10, .e_hold = 0x103C01, .snd = -1 },
    { .pad = 1, .a6 = 0x10, .e_hold = 0, .snd = -1 },
    { .pad = 1, .a6 = 0x10, .coll = 0x10, .count = 5, .e_hold = 0x100401, .snd = -1 },
    { .pad = 1, .a6 = 0x10, .coll = 0x10, .count = 1, .e_hold = 0x100002, .snd = -1 },
    { .pad = 1, .a6 = 0x10, .coll = 0x10, .count = 1, .unk2 = 1, .flags = 0x40, .e_hold = 0x100002, .e_visual = 0x101641, .snd = 8 },
    { .pad = 1, .a6 = 0x10, .coll = 0x10, .count = 1, .unk2 = 1, .e_hold = 0x100002, .snd = -1 },
    { .pad = 2, .a6 = 0x10, .coll = 0x10, .e_hold = 0x100002, .snd = -1 },
    { .pad = 2, .a6 = 0x10, .e_hold = 0, .snd = -1 },
    { .pad = 2, .a6 = 0x10, .unk2 = 1, .e_hold = 0, .snd = -1 },
};

static u32 test_ride_hold(u32 row)
{
    struct RideArmorObj* r = &sr;
    ride_room(1);
    r->unk94.bytes.pad94[0] = ride_hold_rows[row].pad;
    r->unk94.bytes.pad94[1] = ride_hold_rows[row].count;
    r->unk94.bytes.pad94[2] = ride_hold_rows[row].mode;
    r->unk94.bytes.unk97 = ride_hold_rows[row].flags;
    r->collision_flags = ride_hold_rows[row].coll;
    r->unkA6 = ride_hold_rows[row].a6;
    r->unk2 = ride_hold_rows[row].unk2;
    func_8003D9E0(r);
    assert((r->unk94.bytes.pad94[0] | r->unk94.bytes.pad94[1] << 8 | (u32)(u8)r->unkA6 << 16 | (u32)r->spawned_parts << 24) == ride_hold_rows[row].e_hold);
    assert((visual_objects[0].active | visual_objects[0].id << 8 | (u32)visual_objects[0].unk2 << 16) == ride_hold_rows[row].e_visual);
    assert(r->unk5 == 0x22 && r->unk94.bytes.unk97 == ride_hold_rows[row].flags && weapon_objects[0].active == 0);
    SOUND_CHECK_RIDE(ride_sound_id() == ride_hold_rows[row].snd);
    return 1;
}

static const u8 ride_kind_rows[][2] = { { 0, 2 }, { 0, 5 }, { 1, 1 }, { 1, 2 }, { 1, 5 }, { 1, 4 }, { 1, 0xC } };
static u32 test_ride_kind(u32 row)
{
    ride_room(1);
    sr.unk2 = ride_kind_rows[row][0];
    sr.unk5 = ride_kind_rows[row][1];
    assert(func_8003DE08(MAIN_OBJECT(&sr)) == 0);
    return 1;
}

static const struct {
    u8 stomp, cooldown, flags, active, timer, unk5, unk67, unk7D;
    u16 tap, bits;
    u8 e_active, e_timer;
    u16 e_tap;
} ride_tap_rows[] = {
    { .bits = 3 },
    { .active = 1, .tap = 1, .bits = 2, .timer = 5, .e_active = 1, .e_timer = 4, .e_tap = 1 },
    { .active = 1, .tap = 1, .bits = 1, .timer = 5, .unk5 = 1, .unk67 = 1, .unk7D = 1, .e_active = 1, .e_timer = 4, .e_tap = 1 },
    { .stomp = 1, .flags = 2, .bits = 0x100, .unk5 = 1 },
    { .stomp = 1, .bits = 0x100, .unk5 = 3 },
};

static u32 test_ride_taps(u32 row)
{
    struct RideArmorObj* r = &sr;
    ride_room(1);
    r->unk5 = ride_tap_rows[row].unk5;
    r->unk8C.bytes.cooldown = ride_tap_rows[row].cooldown;
    r->unk94.bytes.unk97 = ride_tap_rows[row].flags;
    r->unk8E.bytes.active = ride_tap_rows[row].active;
    r->unk8E.bytes.timer = ride_tap_rows[row].timer;
    r->pad9A = ride_tap_rows[row].tap;
    r->unk8A = ride_tap_rows[row].bits;
    r->unk67 = ride_tap_rows[row].unk67;
    r->unk7D = ride_tap_rows[row].unk7D;
    if (ride_tap_rows[row].stomp)
        func_8003DF9C(PLAYER_OBJECT(r));
    else
        func_8003DE84(r);
    assert(r->unk5 == ride_tap_rows[row].unk5 && r->unk6 == 1 && r->unk94.bytes.unk97 == ride_tap_rows[row].flags);
    assert(r->unk8E.bytes.active == ride_tap_rows[row].e_active && r->unk8E.bytes.timer == ride_tap_rows[row].e_timer);
    assert((u16)r->pad9A == ride_tap_rows[row].e_tap);
    return 1;
}

static const struct {
    u8 action, right, flags, input;
    s32 vx, vy, ax, ay;
    s16 sx, sy, sax, say;
    u8 e_action, e_flags;
    s32 e_x, e_y, e_vx, e_vy, e_ax, e_ay;
    s16 e_sx, e_sy, e_sax, e_say;
} ride_launch_rows[] = {
    { 1, 0, 0, 0, 0x12300, 0x4500, 0x1200, 0x3400, 0, 0, 0, 0, 2, 0, 0, 0, 0x40000, 0, 0x5800, 0x5800, 0x123, 0x45, 0x12, 0x34 },
    { 1, 1, 0, 0, 0x12300, 0x4500, 0x1200, 0x3400, 0, 0, 0, 0, 2, 0, 0, 0, -0x40000, 0, 0x5800, 0x5800, 0x123, 0x45, 0x12, 0x34 },
    { 2, 0, 0, 0, -0x50000, 0, 0x5800, 0, 0, 0, 0, 0, 2, 0, -0x50000, 0, -0x55800, 0, 0x5800, 0, 0, 0, 0, 0 },
    { 2, 0, 2, 8, 0x4000, 0x1000, 0, 0, 0x12, 0, 3, 4, 0, 0, 0x4000, -0x1000, 0x1200, 0, 0x300, 0x400, 0x12, 0, 3, 4 },
};

static u32 test_ride_launch(u32 row)
{
    struct RideArmorObj* r = &sr;
    ride_room(1);
    r->unk90.bytes.action_state = ride_launch_rows[row].action;
    r->unk15 = ride_launch_rows[row].right ? PLAYER_FACING_RIGHT : 0;
    r->unk94.bytes.unk97 = ride_launch_rows[row].flags;
    r->input_flags = ride_launch_rows[row].input;
    r->x_vel.val = ride_launch_rows[row].vx;
    r->y_vel.val = ride_launch_rows[row].vy;
    r->unk28 = ride_launch_rows[row].ax;
    r->unk2C = ride_launch_rows[row].ay;
    r->saved_x_vel = ride_launch_rows[row].sx;
    r->saved_y_vel = ride_launch_rows[row].sy;
    r->unkA0.saved_accel.x = ride_launch_rows[row].sax;
    r->unkA0.saved_accel.y = ride_launch_rows[row].say;
    r->launch_speed = 0x400;
    func_8003FF9C(r);
    assert(r->unk90.bytes.action_state == ride_launch_rows[row].e_action && r->unk94.bytes.unk97 == ride_launch_rows[row].e_flags);
    assert(r->x_pos.val == ride_launch_rows[row].e_x && r->y_pos.val == ride_launch_rows[row].e_y);
    assert(r->x_vel.val == ride_launch_rows[row].e_vx && r->y_vel.val == ride_launch_rows[row].e_vy);
    assert(r->unk28 == ride_launch_rows[row].e_ax && r->unk2C == ride_launch_rows[row].e_ay);
    assert(r->saved_x_vel == ride_launch_rows[row].e_sx && r->saved_y_vel == ride_launch_rows[row].e_sy);
    assert(r->unkA0.saved_accel.x == ride_launch_rows[row].e_sax && r->unkA0.saved_accel.y == ride_launch_rows[row].e_say);
    return 1;
}

static const struct {
    u8 fn, unk8D, afterimage, flags, ended, timer91, timer92, dash;
    s16 x, y;
    u16 unk42;
    u8 e_unk8D, e_afterimage, e_flags, e_ended, e_state, e_screen, e_dash, e_timer91, e_timer92, e_debris, e_visual, e_ride;
    u16 e_unk42;
    s16 e_x;
} ride_wreck_rows[] = {
    { .fn = 0, .unk8D = 1, .flags = 0x40, .dash = 5, .e_unk8D = 2, .e_afterimage = 0xFF, .e_flags = 4, .e_ended = 0x1E, .e_state = 1, .e_screen = 1, .e_dash = 5, .e_debris = 7, .e_ride = 0 },
    { .fn = 0, .unk8D = 2, .ended = 1, .e_unk8D = 2, .e_state = 2, .e_visual = 4, .e_ride = 1 },
    { .fn = 0, .unk8D = 2, .ended = 5, .e_unk8D = 2, .e_ended = 4, .e_state = 1, .e_screen = 1, .e_visual = 4, .e_ride = 1 },
    { .fn = 0, .flags = 0x80, .dash = 5, .unk42 = 0x8123, .e_flags = 0x80, .e_state = 1, .e_screen = 1, .e_dash = 5, .e_unk42 = 0x8123, .e_ride = 1 },
    { .fn = 1, .flags = 0x40, .afterimage = 4, .unk42 = 0x0123, .e_flags = 0x40, .e_afterimage = 4, .e_state = 1, .e_screen = 1, .e_unk42 = 0x8123, .e_ride = 1 },
    { .fn = 1, .flags = 0x40, .afterimage = 5, .unk42 = 0x8123, .e_flags = 0x40, .e_afterimage = 5, .e_state = 1, .e_screen = 1, .e_unk42 = 0x0123, .e_ride = 1 },
    { .fn = 2, .flags = 0x80, .timer92 = 2, .unk42 = 0x8123, .e_flags = 0x80, .e_state = 1, .e_screen = 1, .e_timer92 = 1, .e_unk42 = 0x0123, .e_ride = 1 },
    { .fn = 2, .flags = 0x80, .timer92 = 1, .timer91 = 3, .unk42 = 0x0123, .e_flags = 0x80, .e_state = 1, .e_screen = 1, .e_timer91 = 2, .e_timer92 = 3, .e_unk42 = 0x8123, .e_ride = 1 },
    { .fn = 2, .flags = 0x80, .timer92 = 1, .timer91 = 1, .unk42 = 0x0123, .e_unk8D = 1, .e_flags = 0x80, .e_state = 1, .e_screen = 1, .e_timer92 = 1, .e_unk42 = 0x0123, .e_ride = 1 },
    { .fn = 3, .x = 100, .y = 300, .e_state = 2, .e_screen = 1, .e_ride = 1, .e_x = 100 },
};

static u32 test_ride_wreck(u32 row)
{
    struct PlayerObj* p = &state_room.player;
    struct RideArmorObj* r = &sr;
    u32 i, debris = 0;
    ride_room(1);
    g_Player.ride_state = 1;
    g_Player.unk68 = &player_x_collision_bounds;
    memset(background_objects, 0, sizeof(background_objects));
    r->state = 1;
    r->on_screen = 1;
    r->x_pos.i.hi = ride_wreck_rows[row].x;
    r->y_pos.i.hi = ride_wreck_rows[row].y;
    r->unk42 = ride_wreck_rows[row].unk42;
    r->unk94.bytes.unk97 = ride_wreck_rows[row].flags;
    RIDE_WRECK_BLINKS(r) = ride_wreck_rows[row].timer91;
    RIDE_WRECK_FRAMES(r) = ride_wreck_rows[row].timer92;
    p->unk8D = ride_wreck_rows[row].unk8D;
    p->afterimage = ride_wreck_rows[row].afterimage;
    p->attack_ended = ride_wreck_rows[row].ended;
    p->dash_timer = ride_wreck_rows[row].dash;
    switch (ride_wreck_rows[row].fn) {
    case 0:
        func_800400C8(p);
        break;
    case 1:
        func_800401F8(p);
        break;
    case 2:
        func_80040248(r);
        break;
    default:
        func_800402C4(p);
        break;
    }
    for (i = 0; i < COUNT(misc_objects); i++)
        debris += misc_objects[i].active == 0x41 && misc_objects[i].id == 3;
    assert(p->unk8D == ride_wreck_rows[row].e_unk8D && (u8)p->afterimage == ride_wreck_rows[row].e_afterimage);
    assert(r->unk94.bytes.unk97 == ride_wreck_rows[row].e_flags && (u8)p->attack_ended == ride_wreck_rows[row].e_ended);
    assert(r->state == ride_wreck_rows[row].e_state && r->on_screen == ride_wreck_rows[row].e_screen);
    assert(p->dash_timer == ride_wreck_rows[row].e_dash && (u16)r->unk42 == ride_wreck_rows[row].e_unk42);
    assert(RIDE_WRECK_BLINKS(r) == ride_wreck_rows[row].e_timer91 && RIDE_WRECK_FRAMES(r) == ride_wreck_rows[row].e_timer92);
    assert(debris == ride_wreck_rows[row].e_debris && visual_objects[0].id == ride_wreck_rows[row].e_visual);
    assert(g_Player.ride_state == ride_wreck_rows[row].e_ride && g_Player.hp == 16);
    assert(r->x_pos.i.hi == ride_wreck_rows[row].e_x);
    return 1;
}

static const struct {
    u8 screen, cooldown, buttons, flags, unkF, unk2, unk5, unk7E;
    s8 hp;
    u8 e_unk5, e_unk6, e_flags, e_buttons, e_timers, e_launch, e_visual, e_rider, e_unk7E;
} ride_update_rows[] = {
    { .screen = 1, .cooldown = 3, .hp = -0x80, .unk5 = 0x22, .e_unk5 = 0x22, .e_unk6 = 1 },
    { .cooldown = 3, .hp = -0x80, .unk5 = 0x22, .e_unk5 = 0x22, .e_unk6 = 1, .e_flags = 0x82, .e_buttons = 0x78, .e_timers = 0x1E, .e_launch = 1, .e_visual = 0xC },
    { .cooldown = 3, .hp = -1, .unk5 = 0x22, .e_unk5 = 0x22, .e_unk6 = 1, .e_flags = 2, .e_buttons = 0x78, .e_launch = 1, .e_visual = 0xC },
    { .cooldown = 3, .buttons = 1, .flags = 1, .unk5 = 0x22, .e_unk5 = 0x22, .e_unk6 = 1, .e_flags = 1, .e_rider = 1 },
    { .cooldown = 3, .buttons = 1, .unk5 = 0x22, .e_unk5 = 0x22, .e_unk6 = 1 },
    { .cooldown = 3, .flags = 0x41, .unk5 = 0x22, .e_unk5 = 0xB, .e_flags = 0x40 },
    { .cooldown = 3, .flags = 0x40, .unkF = 1, .unk5 = 0x22, .e_unk5 = 0xB, .e_flags = 0x41 },
    { .cooldown = 3, .unkF = 1, .unk5 = 0x22, .e_unk5 = 0x22, .e_unk6 = 1 },
    { .unk5 = 16, .e_unk5 = 0xC },
    { .unk2 = 1, .unk5 = 2, .unk7E = 3, .e_unk5 = 0xC, .e_unk7E = 2 },
    { .unk2 = 1, .unk5 = 2, .e_unk5 = 0xC },
    { .unk5 = 2, .flags = 0x40, .e_unk5 = 0xC, .e_flags = 0x40 },
};

static u32 test_ride_update(u32 row)
{
    struct RideArmorObj* r = &sr;
    ride_room(1);
    state_terrain(0);
    r->state = 1;
    r->on_screen = 1;
    r->bg_offset = 0;
    r->x_pos.i.hi = ride_update_rows[row].screen ? 0x300 : 100;
    r->y_pos.i.hi = 100;
    r->hp = ride_update_rows[row].hp;
    r->unk8C.bytes.cooldown = ride_update_rows[row].cooldown;
    r->unk8C.bytes.buttons = ride_update_rows[row].buttons;
    r->unk94.bytes.unk97 = ride_update_rows[row].flags;
    r->unk2 = ride_update_rows[row].unk2;
    r->unk5 = ride_update_rows[row].unk5;
    r->unk7E = ride_update_rows[row].unk7E;
    r->unk68 = &D_800F9124;
    engine_obj.unkF = ride_update_rows[row].unkF;
    g_Player.x_pos.i.hi = 7;
    func_800403DC(r);
    assert(r->unk5 == ride_update_rows[row].e_unk5 && r->unk6 == ride_update_rows[row].e_unk6);
    assert(r->unk94.bytes.unk97 == ride_update_rows[row].e_flags && r->unk8C.bytes.buttons == ride_update_rows[row].e_buttons);
    assert(RIDE_WRECK_BLINKS(r) == ride_update_rows[row].e_timers && RIDE_WRECK_FRAMES(r) == ride_update_rows[row].e_timers);
    assert(r->launch_speed == (ride_update_rows[row].e_launch ? 0x400 : 0));
    assert(r->unk90.bytes.action_state == ride_update_rows[row].e_launch && r->unk85 == ride_update_rows[row].e_launch);
    assert(visual_objects[0].id == ride_update_rows[row].e_visual && g_Player.on_screen == ride_update_rows[row].e_rider);
    assert(r->unk7E == ride_update_rows[row].e_unk7E);
    assert(g_Player.x_pos.i.hi == (ride_update_rows[row].e_flags & 0x40 && ride_update_rows[row].cooldown == 0 ? 100 : 7));
    if (ride_update_rows[row].screen)
        assert(r->on_screen == 0);
    return 1;
}

static u32 test_ride_mount_out_of_reach(u32 row)
{
    struct RideArmorObj* r = &sr;
    (void)row;
    ride_room(1);
    r->unk5 = 0;
    r->input_flags = 8;
    r->x_pos.val = 160 * 65536;
    r->y_pos.val = 120 * 65536;
    r->unk68 = &D_800F9124;
    g_Player.active = 0x41;
    g_Player.state = 1;
    g_Player.hp = 30;
    g_Player.x_pos = r->x_pos;
    g_Player.y_pos.val = r->y_pos.val + 120 * 65536;
    g_Player.unk68 = &player_x_collision_bounds;
    func_8003E0D0(r);
    assert(r->unk5 == 0 && r->unk6 == 1 && r->unk94.bytes.unk97 == 0 && g_Player.ride_state == 0);
    assert(r->animation_step.packed == C_TEST_STEP(5));
    return 1;
}

static u32 test_ride_release_backref(u32 row)
{
    u8 record = 1;
    (void)row;
    ride_room(1);
    sr.active = 1;
    sr.backref = &record;
    func_800405D4(&sr);
    assert(record == 0x80 && sr.active == 0);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "armor_recovery", 0, 0, COUNT(armor_recovery_cases) * 2, test_armor_recovery },
    { "armor_part_release", 0, 0, 48, test_armor_part_release },
    { "ride_armor_states", 0, 0, COUNT(ride_armor_states_cases), test_ride_armor_states },
    { "ride_armor_init_resources", NULL, ride_armor_init_resources_cases_expected, COUNT(ride_armor_init_resources_cases_expected), ride_armor_init_resources_armor_case },
    { "ride_armor_jump_attack_transitions", NULL, ride_armor_jump_attack_transitions_cases_expected, COUNT(ride_armor_jump_attack_transitions_cases_expected), ride_armor_jump_attack_transitions_armor_case },
    { "func_8003D6EC", 0, 0, 1, test_func_8003D6EC },
    { "func_8003DCD8", 0, 0, 1, test_func_8003DCD8 },
    { "func_8003E0D0", 0, 0, 4, test_func_8003E0D0 },
    { "func_8003FD08", 0, 0, 5, test_func_8003FD08 },
    { "func_800405D4", 0, 0, 1, test_func_800405D4 },
    { "armor_bounds_clamp", armor_bounds_clamp_cases, armor_bounds_clamp_cases_expected, COUNT(armor_bounds_clamp_cases), 0 },
    { "dash_transition_priority", NULL, NULL, COUNT(dash_scenes) * 4, dash_transition },
    { "missile_release_existing_parts_pool_capacity_and_interrupts", NULL, NULL, 19, release },
    { "mount_character_attack_health_and_spike_guards", NULL, NULL, 54, mount },
    { "dismount_initialization_blocked_motion_and_player_bounds", NULL, NULL, 22, dismount },
    { "air_recovery_death_mount_block_and_wall", NULL, NULL, 12, air_interrupt },
    { "unknown_contact_phase_is_inert", NULL, NULL, 5, idle_phase },
    { "recovery_entry_and_exit", NULL, NULL, 32, recover },
    { "actual_Ride_Armor_ground_punch_full_weapon_pool", NULL, NULL, 1, punch },
    { "ride_handlers", 0, 0, COUNT(ride_handler_rows), test_ride_handlers },
    { "ride_hold", 0, 0, COUNT(ride_hold_rows), test_ride_hold },
    { "ride_kind", 0, 0, COUNT(ride_kind_rows), test_ride_kind },
    { "ride_taps", 0, 0, COUNT(ride_tap_rows), test_ride_taps },
    { "ride_launch", 0, 0, COUNT(ride_launch_rows), test_ride_launch },
    { "ride_wreck", 0, 0, COUNT(ride_wreck_rows), test_ride_wreck },
    { "ride_update", 0, 0, COUNT(ride_update_rows), test_ride_update },
    { "ride_release_backref", 0, 0, 1, test_ride_release_backref },
    { "ride_mount_out_of_reach", 0, 0, 1, test_ride_mount_out_of_reach },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(armor_recovery_cases) * 2 + 48 + COUNT(ride_armor_states_cases) + COUNT(ride_armor_init_resources_cases_expected) + COUNT(ride_armor_jump_attack_transitions_cases_expected) + 1 + 4 + 5 + 1 + COUNT(armor_bounds_clamp_cases) + COUNT(dash_scenes) * 4 + 19 + 54 + 22 + 12 + 5 + 32 + 1 + COUNT(ride_handler_rows) + COUNT(ride_hold_rows) + COUNT(ride_kind_rows) + COUNT(ride_tap_rows) + COUNT(ride_launch_rows) + COUNT(ride_wreck_rows) + COUNT(ride_update_rows) + 1 + 1 + 1;
