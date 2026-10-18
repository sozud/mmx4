#include "test_runtime.h"
#include "main/mains/main_63_hatch_turret.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static const u32 func_8007C090_expected[] = { 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_8007C090(u32 row)
{
    u32 observed_values[10];
    struct WeaponObj obj;
    u8 pool_0_full;
    struct WeaponObj before;
    struct ShotObj shots_before[32];
    memset(&obj, 0, sizeof(obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_0_full ? 1 : 0;
    }
    before = obj;
    memcpy(shots_before, shot_objects, sizeof(shots_before));
    func_8007C090(&obj);
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(shot_objects, shots_before, sizeof(shot_objects));
    observed_values[0] = (u32)obj.unk7;
    observed_values[1] = (u32)shot_objects[0].active;
    observed_values[2] = (u32)shot_objects[0].id;
    observed_values[3] = (u32)shot_objects[0].unk15;
    observed_values[4] = (u32)shot_objects[0].unk16;
    observed_values[5] = (u32)shot_objects[0].unk2;
    observed_values[6] = (u32)shot_objects[0].unk40;
    observed_values[7] = (u32)shot_objects[0].unk42;
    observed_values[8] = (u32)shot_objects[0].x_pos.val;
    observed_values[9] = (u32)shot_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, func_8007C090_expected, 10);
}

static const u32 func_8007C144_expected[] = { 0u, 0xFFFFFFFFu, 0u };
static u32 test_func_8007C144(u32 row)
{
    u32 observed_values[3];
    struct MainObj obj;
    struct MainObj before;
    memset(&obj, 0, sizeof(obj));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&shot_objects, 0, sizeof(shot_objects));
    obj.unk5 = -1;
    before = obj;
    func_8007C144(&obj);
    before.on_screen = obj.on_screen;
    c_test_same_words(&obj, &before, sizeof(obj));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk7C;
    return c_test_observe(0, row, observed_values, func_8007C144_expected, 3);
}

const struct CTestGroup c_test_groups[] = {
    { "func_8007C090", 0, 0, 1, test_func_8007C090 },
    { "func_8007C144", 0, 0, 1, test_func_8007C144 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 1;
