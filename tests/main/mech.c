#include "test_runtime.h"
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
    obj.unk15 = 0x40;
    obj.unk16 = 7;
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
    D_801406A8 = metadata;
    TEST_MENU_FRAMES = (u8*)frames;
    engine_expected = engine_obj;
    expected = obj;
    expected.active = 0x41;
    expected.on_screen = 1;
    expected.state = 1;
    expected.unk5 = expected.unk6 = 0;
    expected.bg_offset = 0;
    expected.unk15 = 0;
    expected.unk16 = 3;
    expected.hp = 0x20;
    expected.animation_table = (u32**)(mode ? D_800F965C : D_800F9428);
    expected.unk3C = (u8*)frames + 20;
    expected.unk40 = 9;
    expected.unk42 = 0x784C;
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
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < 4; i++) {
        assert(frames[i] == 16 + i * 4 && frames[i + 4] == i + 1);
        assert(metadata[i] == 0x400 + i * 0x80);
    }
    assert(box.unk0 == -2 && box.unk1 == -3 && box.unk2 == 4 && box.unk3 == 5);
    assert(D_800F9124.unk0 == 0 && D_800F9124.unk1 == 22 && D_800F9124.unk2 == 15 && D_800F9124.unk3 == 10);
    assert(D_801406A8 == metadata && SP_MENU_FRAMES == frames);
    return obj.unk42 | ((u32)(u8)obj.hp << 16) | ((u32)(obj.animation_table == (u32**)D_800F965C) << 24);
}
static const u32 ride_armor_init_resources_cases_expected[] = { 0x20784Cu, 0x120784Cu };

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
    obj.unk15 = 0x40;
    obj.unk16 = 3;
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
        child->unk42 = 0x784C;
        child->unk16 = obj.unk16;
        child->owner = PLAYER_OBJECT(&obj);
        child->unk15 = obj.unk15;
    }
    if (second)
        func_8003FD08(&obj);
    else
        func_8003F76C(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(pool_expected) / 4; i++)
        assert(((u32*)weapon_objects)[i] == ((u32*)pool_expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_expected)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    for (i = 0; i < 4; i++)
        assert(sprites[i] == 16 + i * 4 && sprites[i + 4] == i + 1);
    i = (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)obj.unk86 << 16) | ((u32)(weapon_objects[15].active == 0x41) << 24);
    return i;
}
static const u32 ride_armor_jump_attack_transitions_cases_expected[] = { 0x1010005u, 0x5u, 0x20006u, 0x20006u, 0x3010Du, 0x2010Du, 0x1010005u, 0x5u, 0x1030111u, 0x20111u, 0x30110u, 0x20110u, 0x1030111u, 0x20111u };

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
    observed_values[2] = (u32)visual_objects[0].unk15;
    observed_values[3] = (u32)visual_objects[0].unk16;
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
    g_Player.nova_strike_active = c->nova_strike_active;
    obj.unk94.bytes.unk97 = c->unk97;
    func_8003E0D0(&obj);
    observed_values[0] = (u32)g_Player.ride_state;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk94.bytes.unk97;
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
    sr.unk15 = 0x40;
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
    sr.unk15 = 0x40;
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
    sr.unk15 = 0x40;
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
    sr.unk15 = 0x40;
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
    obj.unk15 = row & 1 ? 0x40 : 0;
    obj.unk16 = 3;
    obj.animation_table = (u32**)D_800F965C;
    obj.unk3C = frames;
    obj.unk40 = 0x2468;
    obj.unk42 = 0x1357;
    obj.unk94.value = 0x40000902;
    obj.unkA6 = 0x30;
    obj.unk7E = 0x7B;
    obj.spawned_parts = row < 40 ? row % 8 : 5;
    obj.unk86 = row >= 32 && row < 40 ? 3 : 0;
    expected = obj;
    player_before = g_Player;
    memcpy(armor_release_expected_weapons, weapon_objects, sizeof(weapon_objects));
    expected.unk94.value = 0x40000900;
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
            shot->unk42 = 0x784C;
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
    obj.unk15 = variant ? 0x40 : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = 0x18000;
    obj.y_vel.val = -0x24000;
    obj.animation_table = (u32**)(variant ? D_800F965C : D_800F9428);
    set_animation(&obj, 7);
    assert(obj.animation_step.packed == 0x0D000008u);
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
    obj.unk15 = facing ? 0x40 : 0;
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
    assert(obj.animation_step.packed == 0x0D010004);
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
    obj.unk15 = 0x40;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.unk16 = 3;
    obj.unk40 = 9;
    obj.collision_flags = wall;
    obj.input_flags = mode == 3 ? 0 : 8;
    obj.spawned_parts = mask;
    obj.unk94.bytes.unk97 = mode == 1 ? 2 : mode == 2 ? 0x10
                                                      : 0;
    obj.unk94.bytes.pad94[0] = mode == 4;
    obj.animation_table = (u32**)D_800F965C;
    set_animation(&obj, 14);
    assert(obj.animation_step.packed == 0x25000005);
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
            expected.unk15 = wall == 2 ? 0 : 0x40;
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
                            child->unk42 = 0x784C;
                            child->unk16 = 3;
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
    assert(obj.animation_step.packed == 0x2C000001);
    g_Player.active = 0x41;
    g_Player.state = 1;
    g_Player.unk2 = character;
    g_Player.attacking = attack;
    g_Player.hp = hp == 0 ? 0 : hp == 1 ? 1
                                        : 30;
    g_Player.spike_immune = immune;
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
        expected.animation_step.packed = 0x2A01000A;
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
    obj.unk8C.value = 7;
    obj.unk42 = 0x8123;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_vel.val = 0x12345;
    obj.y_vel.val = 0x34567;
    obj.unk28 = 0x1234;
    obj.unk2C = 0x4000;
    obj.animation_table = (u32**)D_800F965C;
    set_animation(&obj, 19);
    assert(obj.animation_step.packed == 0x27010005);
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
    obj.unk15 = 0x40;
    obj.animation_table = (u32**)D_800F965C;
    set_animation(&obj, 13);
    assert(obj.animation_step.packed == 0x15010101);
    expected = obj;
    if (mode == 1 || mode == 2) {
        expected.unk5 = mode == 1 ? 11 : 5;
        expected.unk6 = 0;
    } else {
        if (mode != 3 && wall) {
            expected.unk15 = wall == 2 ? 0 : 0x40;
            expected.x_vel.val = wall == 2 ? -0x16000 : 0x16000;
            expected.x_pos.val += expected.x_vel.val;
        }
        expected.animation_cursor++;
        expected.animation_step.packed = 0x16010101;
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
    armor.unk15 = 0x40;
    armor.unk16 = 3;
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
    static const u32 expected[COUNT(phases)] = { 3657060973u, 1138829452u, 633997681u, 2410733456u, 422910193u };
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
    obj.unk16 = 3;
    obj.animation_table = (u32**)D_800F965C;
    set_animation(&obj, 0);
    expected = obj;
    expected.unk6 = 1;
    expected.animation_cursor = (u32*)D_800F965C[8];
    expected.animation_step.packed = 0x25010004;
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

const struct CTestGroup c_test_groups[] = {
    { "armor_recovery", 0, 0, COUNT(armor_recovery_cases) * 2, test_armor_recovery },
    { "armor_part_release", 0, 0, 48, test_armor_part_release },
    { "ride_armor_states", 0, 0, COUNT(ride_armor_states_cases), test_ride_armor_states },
    { "ride_armor_init_resources", NULL, ride_armor_init_resources_cases_expected, COUNT(ride_armor_init_resources_cases_expected), ride_armor_init_resources_armor_case },
    { "ride_armor_jump_attack_transitions", NULL, ride_armor_jump_attack_transitions_cases_expected, COUNT(ride_armor_jump_attack_transitions_cases_expected), ride_armor_jump_attack_transitions_armor_case },
    { "func_8003D6EC", 0, 0, 1, test_func_8003D6EC },
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
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(armor_recovery_cases) * 2 + 48 + COUNT(ride_armor_states_cases) + COUNT(ride_armor_init_resources_cases_expected) + COUNT(ride_armor_jump_attack_transitions_cases_expected) + 1 + 4 + 5 + 1 + COUNT(armor_bounds_clamp_cases) + COUNT(dash_scenes) * 4 + 19 + 54 + 22 + 12 + 5 + 32 + 1;
