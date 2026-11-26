#include "test_runtime.h"
#include "main/mains/main_63_hatch_turret.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static const u32 func_8007C090_expected[] = { 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_8007C090(u32 row)
{
    u32 observed_values[10];
    struct WeaponObj obj;
    struct WeaponObj before;
    struct ShotObj shots_before[32];
    memset(&obj, 0, sizeof(obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    FILL_ACTIVE(shot_objects, 32, 255 ? 1 : 0);
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

#include "support/state_cases.h"
#define HT(step, setup) (state_reset(step, 0, 0), memset(shot_objects, 0, sizeof(shot_objects)), so.active = 0x41, so.state = 1, so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, setup, func_8007C144(&so), state_extra = (u16)so.unk7C | (u32)shot_objects[0].active << 16)
static void ht_off_screen(void)
{
    HT(0, so.x_pos.i.hi = 0x300);
}
static void ht_closed_wait(void) { HT(0, so.unk7C = 2); }
static void ht_closed_open(void) { HT(0, 0); }
static void ht_opening(void) { HT(1, so.animation_step.fields.relative_step = 1); }
static void ht_opened(void) { HT(1, 0); }
static void ht_raising(void) { HT(2, so.animation_step.fields.relative_step = 1); }
static void ht_raised(void) { HT(2, 0); }
static void ht_blast_out(void) { HT(3, so.unk7 = 1); }
static void ht_blast_gone(void) { HT(3, 0); }
static void ht_closing(void) { HT(4, so.animation_step.fields.relative_step = 1); }
static void ht_closed(void) { HT(4, 0); }
static void (*const hatch_turret_steps_cases[])(void) = {
    ht_off_screen,
    ht_closed_wait,
    ht_closed_open,
    ht_opening,
    ht_opened,
    ht_raising,
    ht_raised,
    ht_blast_out,
    ht_blast_gone,
    ht_closing,
    ht_closed,
};
static const u32 hatch_turret_steps_expected[] = {
    0x0u,
    0x0u,
    0x3000000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x41000000u,
    0x0u,
    0x1u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x41000000u,
    0x1u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x41000000u,
    0x1u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x41000000u,
    0x2u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x0u,
    0x0u,
    0x41000000u,
    0x2u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x41000000u,
    0x10003u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x410000u,
    0x41410000u,
    0x10003u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x41000000u,
    0x4u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x5u,
    0x0u,
    0x0u,
    0x41000000u,
    0x4u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x41000000u,
    0x0u,
    0x80u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x80u,
    0x41000000u,
};
static u32 test_hatch_turret_steps(u32 row)
{
    return state_run(hatch_turret_steps_cases[row], row, &hatch_turret_steps_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "func_8007C090", 0, 0, 1, test_func_8007C090 },
    { "func_8007C144", 0, 0, 1, test_func_8007C144 },
    { "hatch_turret_steps", 0, 0, COUNT(hatch_turret_steps_cases), test_hatch_turret_steps },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 1 + COUNT(hatch_turret_steps_cases);
