#include "test_runtime.h"
#include "main/bike.h"
#include "main/195B4.h"
void func_8003D01C(struct RideArmorObj*);
extern union AnimationStep* D_800F8FC4[38];
extern u32* D_80137E08;
extern u8* D_80141EE8[6];
void func_8003C9A4(struct RideArmorObj*);
void func_8003D164(struct VisualObj*, s32);
void func_8003D35C(struct MainObj*);
void func_8003D3B4(struct PlayerObj*);

static u32 right_edge(void)
{
    struct RideArmorObj obj;
    struct Unk_unk68 bounds = { 0, 0, 2, 3 };
    u32 actual;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    obj.unk68 = &bounds;
    obj.x_pos.i.hi = 300;
    obj.hp = 17;
    g_Player.hp = 27;
    func_8003D01C(&obj);
    assert(obj.unk68 == &bounds && bounds.unk2 == 2);
    actual = obj.x_pos.u.hi | ((u32)(u8)obj.hp << 16) | ((u32)(u8)g_Player.hp << 24);
    return actual;
}
static const CTestCase chaser_right_edge_cases[] = { right_edge };
static const u32 chaser_right_edge_cases_expected[] = { 0x1B1100FEu };

static u8 frames[32];
static u32 chaser_case(u32 mode)
{
    struct RideArmorObj obj, expected;
    struct WeaponObj expected_weapon[16];
    struct VisualObj expected_visual[32];
    struct EngineObj engine_expected;
    struct PlayerObj player_before = g_Player;
    u32 i, fire = mode >= 3, free_weapon = mode == 4 || mode >= 6;
    u32 free_visual = mode >= 5, kind = mode == 7 ? 255 : mode & 3;
    memset(&obj, 0, sizeof(obj));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 16; i++) {
        weapon_objects[i].active = 1;
        weapon_objects[i].id = 39;
        weapon_objects[i].unk2 = 9;
        weapon_objects[i].state = 40;
        weapon_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        weapon_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 39;
        visual_objects[i].unk2 = 9;
        visual_objects[i].state = 40;
        visual_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        visual_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    if (free_weapon)
        weapon_objects[15].active = 0;
    if (free_visual)
        visual_objects[31].active = 0;
    obj.active = 0x41;
    obj.id = 2;
    obj.state = 1;
    obj.unk8C.value = mode == 0 ? 0 : 0x10;
    ((u8*)&obj.unk7C)[0x89 - 0x7C] = mode == 1 ? 1 : 0;
    ((u8*)&obj.unk7C)[0x98 - 0x7C] = mode == 2 ? 3 : 2;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)D_800F8FC4;
    obj.unk3C = frames;
    obj.unk40 = 123;
    obj.unk16 = 4;
    obj.unk15 = mode & 1 ? 0x40 : 0;
    engine_obj.stage = 5;
    engine_obj.substage = 0;
    D_8013E198[5] = -1;
    expected = obj;
    engine_expected = engine_obj;
    memcpy(expected_weapon, weapon_objects, sizeof(expected_weapon));
    memcpy(expected_visual, visual_objects, sizeof(expected_visual));
    if (fire) {
        ((u8*)&expected.unk7C)[0x89 - 0x7C] = 4;
        ((u8*)&expected.unk7C)[0x98 - 0x7C] = 3;
        if (free_weapon) {
            struct WeaponObj* w = &expected_weapon[15];
            w->active = 0x41;
            w->id = 0x38;
            w->unk2 = kind;
            w->x_pos.i.hi = 100;
            w->y_pos.i.hi = 200;
            w->animation_table = obj.animation_table;
            w->unk40 = 123;
            w->unk3C = frames;
            w->unk42 = 0x7848;
            w->owner = (struct PlayerObj*)&obj;
            w->unk16 = 4;
            w->unk15 = obj.unk15;
        }
        if (free_visual) {
            struct VisualObj* v = &expected_visual[31];
            v->active = 0x41;
            v->id = 12;
            v->unk2 = kind;
            v->x_pos.i.hi = 100;
            v->y_pos.i.hi = 200;
            v->animation_table = obj.animation_table;
            v->unk40 = 123;
            v->unk3C = frames;
            v->unk42 = 0x7848;
            v->unk50 = (struct PlayerObj*)&obj;
            v->unk16 = 4;
            v->unk15 = obj.unk15;
        }
    }
    func_8003C6EC(&obj, kind);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(expected_weapon) / 4; i++)
        assert(((u32*)weapon_objects)[i] == ((u32*)expected_weapon)[i]);
    for (i = 0; i < sizeof(expected_visual) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)expected_visual)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(s_StageMainIds[5][0][0] == 0x82 && D_8013E198[5] == -1);
    i = ((u8*)&obj.unk7C)[0x98 - 0x7C] | ((u32)weapon_objects[15].active << 8) | ((u32)visual_objects[31].active << 16);
    return i;
}
#define CASE(m)                                        \
    static u32 ride_chaser_shot_pools_chaser_##m(void) \
    {                                                  \
        return chaser_case(m);                         \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
CASE(7)
#define ENTRY(m) ride_chaser_shot_pools_chaser_##m,
static const CTestCase ride_chaser_shot_pools_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) };
static const u32 ride_chaser_shot_pools_cases_expected[] = { 0x10102u, 0x10102u, 0x10103u, 0x10103u, 0x14103u, 0x410103u, 0x414103u, 0x414103u };
#undef CASE
#undef ENTRY

static const u32 func_8003BE28_expected[] = { 0u, 0u, 4u, 0u, 1u, 1u, 0u, 0u };
static u32 test_func_8003BE28(u32 row)
{
    u32 observed_values[8];
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
    memset(&visual_objects, 0, sizeof(visual_objects));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    obj.unk6 = -1;
    obj.unk70 = 5;
    obj.unk7D = 255;
    func_8003BE28(&obj);
    observed_values[0] = (u32)obj.unk28;
    observed_values[1] = (u32)obj.unk2C;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.unk67;
    observed_values[5] = (u32)obj.unk8E.value;
    observed_values[6] = (u32)obj.x_vel.val;
    observed_values[7] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, func_8003BE28_expected, 8);
}

struct func_8003C584_case {
    u32 unk70;
    u32 expected[5];
};
static const struct func_8003C584_case func_8003C584_cases[] = {
    { 4, { 0u, 3u, 1u, 0u, 0u } },
    { 5, { 0u, 3u, 1u, 0u, 0u } },
};
static u32 test_func_8003C584(u32 row)
{
    const struct func_8003C584_case* c = &func_8003C584_cases[row];
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
    memset(&visual_objects, 0, sizeof(visual_objects));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    obj.unk70 = c->unk70;
    func_8003C584(&obj);
    observed_values[0] = (u32)obj.unk28;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk67;
    observed_values[3] = (u32)obj.x_vel.val;
    observed_values[4] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

struct func_8003C9A4_case {
    u32 unk82, unk80, x_vel;
    u32 expected[4];
};
static const struct func_8003C9A4_case func_8003C9A4_cases[] = {
    { 255, 0, 0, { 0u, 0u, 0u, 0u } },
    { 2, 1, -1, { 0x5000u, 2u, 3u, 0u } },
};
static u32 test_func_8003C9A4(u32 row)
{
    const struct func_8003C9A4_case* c = &func_8003C9A4_cases[row];
    u32 observed_values[4];
    struct RideArmorObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk80.bytes.unk82 = c->unk82;
    obj.unk80.bytes.unk83 = 0;
    obj.unk80.bytes.unk80 = c->unk80;
    obj.x_vel.val = c->x_vel;
    func_8003C9A4(&obj);
    observed_values[0] = (u32)obj.unk2C;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk80.bytes.unk80;
    observed_values[3] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

static const u32 func_8003CB08_expected[] = { 0u, 0u, 0u, 0xFFFDFFFFu };
static u32 test_func_8003CB08(u32 row)
{
    u32 observed_values[4];
    struct RideArmorObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk8A = 514;
    obj.x_vel.val = -131073;
    func_8003CB08(&obj);
    observed_values[0] = (u32)obj.unk28;
    observed_values[1] = (u32)obj.unk7C;
    observed_values[2] = (u32)obj.unk80.bytes.unk80;
    observed_values[3] = (u32)obj.x_vel.val;
    return c_test_observe(0, row, observed_values, func_8003CB08_expected, 4);
}

static const u32 func_8003CBCC_expected[] = { 0u, 0u, 0xFFFE0000u };
static u32 test_func_8003CBCC(u32 row)
{
    u32 observed_values[3];
    struct RideArmorObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk8A = 514;
    obj.x_vel.val = -1048448;
    func_8003CBCC(&obj);
    observed_values[0] = (u32)obj.unk28;
    observed_values[1] = (u32)obj.unk7C;
    observed_values[2] = (u32)obj.x_vel.val;
    return c_test_observe(0, row, observed_values, func_8003CBCC_expected, 3);
}

struct func_8003CCBC_case {
    u32 unk7D, unk7E;
    u32 expected[5];
};
static const struct func_8003CCBC_case func_8003CCBC_cases[] = {
    { 255, 0, { 0u, 0u, 0xFFu, 0u, 0u } },
    { 0, 255, { 5u, 0u, 1u, 3u, 0u } },
};
static u32 test_func_8003CCBC(u32 row)
{
    const struct func_8003CCBC_case* c = &func_8003CCBC_cases[row];
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
    obj.unk7D = c->unk7D;
    obj.unk7E = c->unk7E;
    func_8003CCBC(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk7D;
    observed_values[3] = (u32)obj.unk80.bytes.unk80;
    observed_values[4] = (u32)obj.unk98.bytes.high;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

static const u32 func_8003D01C_expected[] = { 0u, 0u, 0u };
static u32 test_func_8003D01C(u32 row)
{
    u32 observed_values[3];
    struct RideArmorObj obj;
    struct Unk_unk68 child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&g_Player, 0, sizeof(g_Player));
    child_0_present = 255;
    obj.unk68 = child_0_present ? &child_0 : NULL;
    func_8003D01C(&obj);
    observed_values[0] = (u32)g_Player.hp;
    observed_values[1] = (u32)obj.hp;
    observed_values[2] = (u32)obj.x_pos.i.hi;
    return c_test_observe(0, row, observed_values, func_8003D01C_expected, 3);
}

static const u32 func_8003D164_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_8003D164(u32 row)
{
    u32 observed_values[9];
    struct VisualObj obj;
    u8 pool_0_full;
    s32 arg1;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    memset(&engine_obj, 0, sizeof(engine_obj));
    pool_0_full = 255;
    arg1 = 0;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_0_full ? 1 : 0;
    }
    func_8003D164(&obj, arg1);
    observed_values[0] = (u32)visual_objects[0].active;
    observed_values[1] = (u32)visual_objects[0].id;
    observed_values[2] = (u32)visual_objects[0].unk15;
    observed_values[3] = (u32)visual_objects[0].unk16;
    observed_values[4] = (u32)visual_objects[0].unk2;
    observed_values[5] = (u32)visual_objects[0].unk40;
    observed_values[6] = (u32)visual_objects[0].unk42;
    observed_values[7] = (u32)visual_objects[0].x_pos.i.hi;
    observed_values[8] = (u32)visual_objects[0].y_pos.i.hi;
    return c_test_observe(0, row, observed_values, func_8003D164_expected, 9);
}

static const u32 func_8003D254_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_8003D254(u32 row)
{
    u32 observed_values[9];
    struct VisualObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    memset(&engine_obj, 0, sizeof(engine_obj));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_0_full ? 1 : 0;
    }
    func_8003D254(&obj);
    observed_values[0] = (u32)visual_objects[0].active;
    observed_values[1] = (u32)visual_objects[0].id;
    observed_values[2] = (u32)visual_objects[0].unk15;
    observed_values[3] = (u32)visual_objects[0].unk16;
    observed_values[4] = (u32)visual_objects[0].unk2;
    observed_values[5] = (u32)visual_objects[0].unk40;
    observed_values[6] = (u32)visual_objects[0].unk42;
    observed_values[7] = (u32)visual_objects[0].x_pos.i.hi;
    observed_values[8] = (u32)visual_objects[0].y_pos.i.hi;
    return c_test_observe(0, row, observed_values, func_8003D254_expected, 9);
}

struct func_8003D35C_case {
    u32 y_speed, gravity;
    u32 expected[1];
};
static const struct func_8003D35C_case func_8003D35C_cases[] = {
    { 0, 0, { 0u } },
    { -1048560, -622575, { 0xFFF98000u } },
};
static u32 test_func_8003D35C(u32 row)
{
    const struct func_8003D35C_case* c = &func_8003D35C_cases[row];
    u32 observed_values[1];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.y_speed = c->y_speed;
    obj.gravity = c->gravity;
    func_8003D35C(&obj);
    observed_values[0] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 1);
}

static u32 chaser_position(s8 ride, s8 charge, s32 axis)
{
    struct PlayerObj owner;
    memset(&owner, 0, sizeof(owner));
    memset(&g_Player, 0, sizeof(g_Player));
    owner.charge_state[0] = charge;
    owner.x_pos.val = -0x123456;
    owner.y_pos.val = 0x234567;
    g_Player.ride_state = ride;
    g_Player.x_pos.val = 0x654321;
    g_Player.y_pos.val = -0x456789;
    func_8003D3B4(&owner);
    assert(owner.x_pos.val == -0x123456 && owner.y_pos.val == 0x234567);
    assert(g_Player.ride_state == ride);
    return axis ? g_Player.y_pos.val : g_Player.x_pos.val;
}
#define COPY_CASE(name, ride, charge, axis)         \
    static u32 name(void)                           \
    {                                               \
        return chaser_position(ride, charge, axis); \
    }
COPY_CASE(no_ride_x, 0, 1, 0)
COPY_CASE(no_ride_y, 0, 1, 1)
COPY_CASE(no_charge_x, 1, 0, 0)
COPY_CASE(no_charge_y, 1, 0, 1)
COPY_CASE(copy_x, 1, 1, 0)
COPY_CASE(copy_y, 1, 1, 1)
#undef COPY_CASE
static const CTestCase chaser_position_copy_cases[] = {
    no_ride_x,
    no_ride_y,
    no_charge_x,
    no_charge_y,
    copy_x,
    copy_y,
};

static const u32 chaser_position_copy_cases_expected[] = { 0x654321u, 0xFFBA9877u, 0x654321u, 0xFFBA9877u, 0xFFEDCBAAu, 0x234567u };
const struct CTestGroup c_test_groups[] = {
    { "chaser_right_edge", chaser_right_edge_cases, chaser_right_edge_cases_expected, COUNT(chaser_right_edge_cases), 0 },
    { "ride_chaser_shot_pools", ride_chaser_shot_pools_cases, ride_chaser_shot_pools_cases_expected, COUNT(ride_chaser_shot_pools_cases), 0 },
    { "func_8003BE28", 0, 0, 1, test_func_8003BE28 },
    { "func_8003C584", 0, 0, 2, test_func_8003C584 },
    { "func_8003C9A4", 0, 0, 2, test_func_8003C9A4 },
    { "func_8003CB08", 0, 0, 1, test_func_8003CB08 },
    { "func_8003CBCC", 0, 0, 1, test_func_8003CBCC },
    { "func_8003CCBC", 0, 0, 2, test_func_8003CCBC },
    { "func_8003D01C", 0, 0, 1, test_func_8003D01C },
    { "func_8003D164", 0, 0, 1, test_func_8003D164 },
    { "func_8003D254", 0, 0, 1, test_func_8003D254 },
    { "func_8003D35C", 0, 0, 2, test_func_8003D35C },
    { "chaser_position_copy", chaser_position_copy_cases, chaser_position_copy_cases_expected, COUNT(chaser_position_copy_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(chaser_right_edge_cases) + COUNT(ride_chaser_shot_pools_cases) + 1 + 2 + 2 + 1 + 1 + 2 + 1 + 1 + 1 + 2 + COUNT(chaser_position_copy_cases);
