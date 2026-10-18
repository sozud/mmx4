#include "test_runtime.h"
#include "main/mech.h"
#include "main/195B4.h"
#include "main/mech_state_data.h"
extern union AnimationStep* D_800F9428[31];
extern union AnimationStep* D_800F965C[38];
void func_8003D638(struct VisualObj*, u8);
void func_8003DC1C(struct PlayerObj*, s8);
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
#define CASE(m)                                          \
    static u32 ride_armor_init_resources_armor_##m(void) \
    {                                                    \
        return ride_armor_init_resources_armor_case(m);  \
    }
CASE(0)
CASE(1)
static const CTestCase ride_armor_init_resources_cases[] = { ride_armor_init_resources_armor_0, ride_armor_init_resources_armor_1 };
static const u32 ride_armor_init_resources_cases_expected[] = { 0x20784Cu, 0x120784Cu };
#undef CASE

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
#define CASE(m)                                                   \
    static u32 ride_armor_jump_attack_transitions_armor_##m(void) \
    {                                                             \
        return ride_armor_jump_attack_transitions_armor_case(m);  \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
CASE(7)
CASE(8)
CASE(9)
CASE(10)
CASE(11)
CASE(12)
CASE(13)
#define ENTRY(m) ride_armor_jump_attack_transitions_armor_##m,
static const CTestCase ride_armor_jump_attack_transitions_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) ENTRY(8) ENTRY(9) ENTRY(10) ENTRY(11) ENTRY(12) ENTRY(13) };
static const u32 ride_armor_jump_attack_transitions_cases_expected[] = { 0x1010005u, 0x5u, 0x20006u, 0x20006u, 0x3010Du, 0x2010Du, 0x1010005u, 0x5u, 0x1030111u, 0x20111u, 0x30110u, 0x20110u, 0x1030111u, 0x20111u };
#undef CASE
#undef ENTRY

static const u32 func_8003D638_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_8003D638(u32 row)
{
    u32 observed_values[9];
    struct VisualObj obj;
    u8 pool_0_full;
    u8 arg1;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    pool_0_full = 255;
    arg1 = 0;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_0_full ? 1 : 0;
    }
    func_8003D638(&obj, arg1);
    observed_values[0] = (u32)visual_objects[0].active;
    observed_values[1] = (u32)visual_objects[0].id;
    observed_values[2] = (u32)visual_objects[0].unk15;
    observed_values[3] = (u32)visual_objects[0].unk16;
    observed_values[4] = (u32)visual_objects[0].unk2;
    observed_values[5] = (u32)visual_objects[0].unk40;
    observed_values[6] = (u32)visual_objects[0].unk42;
    observed_values[7] = (u32)visual_objects[0].x_pos.val;
    observed_values[8] = (u32)visual_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, func_8003D638_expected, 9);
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
    observed_values[2] = (u32)visual_objects[0].unk15;
    observed_values[3] = (u32)visual_objects[0].unk16;
    observed_values[4] = (u32)visual_objects[0].unk2;
    observed_values[5] = (u32)visual_objects[0].unk40;
    observed_values[6] = (u32)visual_objects[0].unk42;
    observed_values[7] = (u32)visual_objects[0].x_pos.i.hi;
    observed_values[8] = (u32)visual_objects[0].y_pos.i.hi;
    return c_test_observe(0, row, observed_values, func_8003D6EC_expected, 9);
}

static const u32 func_8003D8A8_expected[] = { 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_8003D8A8(u32 row)
{
    u32 observed_values[10];
    struct RideArmorObj obj;
    u8 pool_0_full;
    s32 shot_kind;
    s32 shot_variant;
    memset(&obj, 0, sizeof(obj));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    memset(&engine_obj, 0, sizeof(engine_obj));
    pool_0_full = 255;
    shot_kind = 0;
    shot_variant = 0;
    {
        u32 slot;
        for (slot = 0; slot < 16; ++slot)
            weapon_objects[slot].active = pool_0_full ? 1 : 0;
    }
    func_8003D8A8(&obj, shot_kind, shot_variant);
    observed_values[0] = (u32)obj.unk86;
    observed_values[1] = (u32)weapon_objects[0].active;
    observed_values[2] = (u32)weapon_objects[0].id;
    observed_values[3] = (u32)weapon_objects[0].unk15;
    observed_values[4] = (u32)weapon_objects[0].unk16;
    observed_values[5] = (u32)weapon_objects[0].unk2;
    observed_values[6] = (u32)weapon_objects[0].unk40;
    observed_values[7] = (u32)weapon_objects[0].unk42;
    observed_values[8] = (u32)weapon_objects[0].x_pos.i.hi;
    observed_values[9] = (u32)weapon_objects[0].y_pos.i.hi;
    return c_test_observe(0, row, observed_values, func_8003D8A8_expected, 10);
}

static const u32 func_8003DC1C_expected[] = { 0u, 0u };
static u32 test_func_8003DC1C(u32 row)
{
    u32 observed_values[2];
    struct PlayerObj obj;
    s8 arg1;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.unk8D = 255;
    arg1 = 0;
    func_8003DC1C(&obj, arg1);
    observed_values[0] = (u32)g_Player.ride_animation;
    observed_values[1] = (u32)g_Player.unk6;
    return c_test_observe(0, row, observed_values, func_8003DC1C_expected, 2);
}

static const u32 func_8003E0B0_expected[] = { 0u };
static u32 test_func_8003E0B0(u32 row)
{
    u32 observed_values[1];
    struct PlayerObj obj;
    s32 return_value;
    memset(&obj, 0, sizeof(obj));
    obj.unk15 = 255;
    return_value = func_8003E0B0(&obj);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, func_8003E0B0_expected, 1);
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

struct func_8003F76C_case {
    u32 input_flags, unk97, y_vel, relative_step, event;
    u32 expected[5];
};
static const struct func_8003F76C_case func_8003F76C_cases[] = {
    { 8, 0, 0, 0, 0, { 0u, 5u, 0u, 0u, 0u } },
    { 0, 2, 0, 0, 0, { 0u, 0u, 0xFFFFFFFFu, 0u, 0u } },
    { 4, 0, 0, 0, 0, { 0u, 4u, 0xFFFFFFFFu, 0u, 0u } },
    { 0, 0, -1, -1, 0, { 0u, 0u, 0xFFFFFFFFu, 0u, 0xFFFFFFFFu } },
    { 0, 0, -1048576, -1, -1, { 0u, 0u, 0xFFFFFFFFu, 0u, 0xFFFA2000u } },
};
static u32 test_func_8003F76C(u32 row)
{
    const struct func_8003F76C_case* c = &func_8003F76C_cases[row];
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
    obj.input_flags = c->input_flags;
    obj.unk94.bytes.unk97 = c->unk97;
    obj.y_vel.val = c->y_vel;
    obj.animation_step.fields.relative_step = c->relative_step;
    obj.animation_step.fields.event = c->event;
    func_8003F76C(&obj);
    observed_values[0] = (u32)obj.unk28;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.x_vel.val;
    observed_values[4] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, c->expected, 5);
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
const struct CTestGroup c_test_groups[] = {
    { "ride_armor_init_resources", ride_armor_init_resources_cases, ride_armor_init_resources_cases_expected, COUNT(ride_armor_init_resources_cases), 0 },
    { "ride_armor_jump_attack_transitions", ride_armor_jump_attack_transitions_cases, ride_armor_jump_attack_transitions_cases_expected, COUNT(ride_armor_jump_attack_transitions_cases), 0 },
    { "func_8003D638", 0, 0, 1, test_func_8003D638 },
    { "func_8003D6EC", 0, 0, 1, test_func_8003D6EC },
    { "func_8003D8A8", 0, 0, 1, test_func_8003D8A8 },
    { "func_8003DC1C", 0, 0, 1, test_func_8003DC1C },
    { "func_8003E0B0", 0, 0, 1, test_func_8003E0B0 },
    { "func_8003E0D0", 0, 0, 4, test_func_8003E0D0 },
    { "func_8003F76C", 0, 0, 5, test_func_8003F76C },
    { "func_8003FD08", 0, 0, 5, test_func_8003FD08 },
    { "func_800405D4", 0, 0, 1, test_func_800405D4 },
    { "armor_bounds_clamp", armor_bounds_clamp_cases, armor_bounds_clamp_cases_expected, COUNT(armor_bounds_clamp_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(ride_armor_init_resources_cases) + COUNT(ride_armor_jump_attack_transitions_cases) + 1 + 1 + 1 + 1 + 1 + 4 + 5 + 5 + 1 + COUNT(armor_bounds_clamp_cases);
