#include "test_runtime.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];
void fortress_cannon_fire_volley(struct MainObj*);
#ifdef MMX4_PC
extern u8 D_80141BE8[1536];
#endif
#ifndef MMX4_PC
extern u8 D_80141BE8[768];
#endif

static const u32 fortress_cannon_fall_expected[] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_fortress_cannon_fall(u32 row)
{
    u32 observed_values[7];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    fortress_cannon_fall(&obj);
    observed_values[0] = (u32)obj.air_state;
    observed_values[1] = (u32)obj.gravity;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.x_accel;
    observed_values[5] = (u32)obj.x_speed;
    observed_values[6] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, fortress_cannon_fall_expected, 7);
}

static const u32 fortress_cannon_fire_double_shot_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_fortress_cannon_fire_double_shot(u32 row)
{
    u32 observed_values[8];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_0_full ? 1 : 0;
    }
    fortress_cannon_fire_double_shot(&obj);
    observed_values[0] = (u32)shot_objects[0].active;
    observed_values[1] = (u32)shot_objects[0].bg_offset;
    observed_values[2] = (u32)shot_objects[0].id;
    observed_values[3] = (u32)shot_objects[0].unk15;
    observed_values[4] = (u32)shot_objects[0].unk16;
    observed_values[5] = (u32)shot_objects[0].unk2;
    observed_values[6] = (u32)shot_objects[0].unk40;
    observed_values[7] = (u32)shot_objects[0].unk42;
    return c_test_observe(0, row, observed_values, fortress_cannon_fire_double_shot_expected, 8);
}

struct fortress_cannon_fire_shot_case {
    u32 pool_0_full, unk84;
    u32 expected[8];
};
static const struct fortress_cannon_fire_shot_case fortress_cannon_fire_shot_cases[] = {
    { 0, 3, { 0x41u, 0u, 0x1Eu, 0u, 4u, 2u, 0u, 0u } },
    { 255, 0, { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_fortress_cannon_fire_shot(u32 row)
{
    const struct fortress_cannon_fire_shot_case* c = &fortress_cannon_fire_shot_cases[row];
    u32 observed_values[8];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    pool_0_full = c->pool_0_full;
    obj.ext.main_51.unk84 = c->unk84;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_0_full ? 1 : 0;
    }
    fortress_cannon_fire_shot(&obj);
    observed_values[0] = (u32)shot_objects[0].active;
    observed_values[1] = (u32)shot_objects[0].bg_offset;
    observed_values[2] = (u32)shot_objects[0].id;
    observed_values[3] = (u32)shot_objects[0].unk15;
    observed_values[4] = (u32)shot_objects[0].unk16;
    observed_values[5] = (u32)shot_objects[0].unk2;
    observed_values[6] = (u32)shot_objects[0].unk40;
    observed_values[7] = (u32)shot_objects[0].unk42;
    return c_test_observe(0, row, observed_values, c->expected, 8);
}

static const u32 fortress_cannon_fire_start_expected[] = { 0x4Bu, 1u, 0xFFu, 0x41u, 0x1Eu, 0u };
static u32 test_fortress_cannon_fire_start(u32 row)
{
    u32 observed_values[6];
    struct MainObj obj;
    u8 pool_full;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&shot_objects, 0, sizeof(shot_objects));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&qux_object, 0, sizeof(qux_object));
    memset(&visual_objects, 0, sizeof(visual_objects));
    memset(&weapon_objects, 0, sizeof(weapon_objects));

    pool_full = 1;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_full ? 1 : 0;
    }
    shot_objects[31].active = 0;
    obj.id = 51;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    func_80069AD0(&obj);
    obj.unk5 = 3;
    obj.unk6 = 0;
    obj.unk2 = 1;
    obj.ext.main_51.unk84 = 2;
    fortress_cannon_fire_start(&obj);
    assert(shot_objects[31].unk7C == (struct WeaponObj*)&obj);
    assert(shot_objects[31].animation_table == (u32**)obj.animation_table);
    assert(shot_objects[0].active == 1);
    observed_values[0] = (u32)obj.unk7C;
    observed_values[1] = (u32)(u8)obj.unk6;
    observed_values[2] = (u32)obj.previous_animation_index;
    observed_values[3] = (u32)(u8)shot_objects[31].active;
    observed_values[4] = (u32)(u8)shot_objects[31].id;
    observed_values[5] = (u32)(u8)shot_objects[31].unk2;
    return c_test_observe(0, row, observed_values, fortress_cannon_fire_start_expected, 6);
}

static const u32 fortress_cannon_fire_volley_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_fortress_cannon_fire_volley(u32 row)
{
    u32 observed_values[8];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_0_full ? 1 : 0;
    }
    fortress_cannon_fire_volley(&obj);
    observed_values[0] = (u32)shot_objects[0].active;
    observed_values[1] = (u32)shot_objects[0].bg_offset;
    observed_values[2] = (u32)shot_objects[0].id;
    observed_values[3] = (u32)shot_objects[0].unk15;
    observed_values[4] = (u32)shot_objects[0].unk16;
    observed_values[5] = (u32)shot_objects[0].unk2;
    observed_values[6] = (u32)shot_objects[0].unk40;
    observed_values[7] = (u32)shot_objects[0].unk42;
    return c_test_observe(0, row, observed_values, fortress_cannon_fire_volley_expected, 8);
}

static const u32 func_80069BE4_expected[] = { 0u, 0u, 1u, 1u, 1u, 0x640000u, 0x500000u };
static u32 test_func_80069BE4(u32 row)
{
    u32 observed_values[7];
    struct MainObj obj;
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013B7D8, 0, sizeof(D_8013B7D8));
    memset(&D_8013B7DC, 0, sizeof(D_8013B7DC));
    memset(&D_8013B7E0, 0, sizeof(D_8013B7E0));
    memset(&D_8013B7E4, 0, sizeof(D_8013B7E4));
    memset(&D_8013B7E8, 0, sizeof(D_8013B7E8));
    memset(&D_8013B7EC, 0, sizeof(D_8013B7EC));
    memset(&D_8013B7F0, 0, sizeof(D_8013B7F0));
    memset(&D_8013B7F4, 0, sizeof(D_8013B7F4));
    memset(&D_8013B7F8, 0, sizeof(D_8013B7F8));
    memset(&D_8013B7FC, 0, sizeof(D_8013B7FC));
    memset(&D_8013B800, 0, sizeof(D_8013B800));
    memset(&D_8013B804, 0, sizeof(D_8013B804));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141BE8, 0, sizeof(D_80141BE8));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&D_80141F70, 0, sizeof(D_80141F70));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&cur_random, 0, sizeof(cur_random));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_FilterAmountG, 0, sizeof(g_FilterAmountG));
    memset(&layout_size, 0, sizeof(layout_size));
    memset(&layout_width, 0, sizeof(layout_width));
    memset(&misc_objects, 0, sizeof(misc_objects));

    memset(&qux_object, 0, sizeof(qux_object));
    memset(&shot_objects, 0, sizeof(shot_objects));
    memset(&visual_objects, 0, sizeof(visual_objects));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.spike_immune = 1;
    obj.active = 0x41;
    obj.id = 51;
    obj.hp = 30;
    obj.state = 1;
    obj.unk5 = 1;
    obj.air_state = 1;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    func_80069BE4(&obj);
    assert(obj.terrain_box == NULL);
    observed_values[0] = (u32)(u8)obj.unk5;
    observed_values[1] = (u32)obj.ext.main_51.saved_unk5;
    observed_values[2] = (u32)(u8)obj.state;
    observed_values[3] = (u32)obj.on_screen;
    observed_values[4] = (u32)obj.air_state;
    observed_values[5] = (u32)obj.unk18.val;
    observed_values[6] = (u32)obj.unk1C.val;
    return c_test_observe(0, row, observed_values, func_80069BE4_expected, 7);
}

struct func_80069F28_case {
    u32 unk84;
    u32 expected[4];
};
static const struct func_80069F28_case func_80069F28_cases[] = {
    { 0, { 1u, 0u, 0u, 0u } },
    { 3, { 0u, 4u, 0u, 0x14u } },
};
static u32 test_func_80069F28(u32 row)
{
    const struct func_80069F28_case* c = &func_80069F28_cases[row];
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    obj.unk7C = 1;
    obj.ext.main_51.unk84 = c->unk84;
    obj.unk2 = -1;
    func_80069F28(&obj);
    observed_values[0] = (u32)obj.ext.main_51.unk84;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk7C;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

const struct CTestGroup c_test_groups[] = {
    { "fortress_cannon_fall", 0, 0, 1, test_fortress_cannon_fall },
    { "fortress_cannon_fire_double_shot", 0, 0, 1, test_fortress_cannon_fire_double_shot },
    { "fortress_cannon_fire_shot", 0, 0, 2, test_fortress_cannon_fire_shot },
    { "fortress_cannon_fire_start", 0, 0, 1, test_fortress_cannon_fire_start },
    { "fortress_cannon_fire_volley", 0, 0, 1, test_fortress_cannon_fire_volley },
    { "func_80069BE4", 0, 0, 1, test_func_80069BE4 },
    { "func_80069F28", 0, 0, 2, test_func_80069F28 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 1 + 2 + 1 + 1 + 1 + 2;
