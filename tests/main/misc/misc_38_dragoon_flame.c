#include "test_runtime.h"
#ifndef VERSION_DEMO

#include "support/state_cases.h"
#include "main/misc/misc_38_dragoon_flame.h"

static struct MainObj flame_source;
#define fm state_room.misc
#define FLAME(st, kind) (state_reset(0, 0, 0), memset(&flame_source, 0, sizeof(flame_source)), flame_source.animation_table = (void*)state_table, flame_source.unk42 = 0x8123, flame_source.x_pos.i.hi = 0x90, flame_source.y_pos.i.hi = 0x70, flame_source.air_state = 1, fm.active = 1, fm.state = st, fm.unk2 = kind, fm.ext.misc_7.position = &flame_source, fm.x_pos.i.hi = 0x80, fm.y_pos.i.hi = 0x60)
#define FX() (state_extra = fm.unk16 | (u32)fm.on_screen << 8 | (u32)fm.unk17 << 16)
static void flame_init_5(void) { FLAME(0, 5), dragoon_flame_update(&fm), FX(); }
static void flame_init_4(void) { FLAME(0, 4), dragoon_flame_update(&fm), FX(); }
static void flame_init_3(void) { FLAME(0, 3), dragoon_flame_update(&fm), FX(); }
static void flame_init_2(void) { FLAME(0, 2), dragoon_flame_update(&fm), FX(); }
static void flame_init_0(void) { FLAME(0, 0), dragoon_flame_update(&fm), FX(); }
static void flame_init_1(void) { FLAME(0, 1), dragoon_flame_update(&fm), FX(); }
static void flame_init_other(void) { FLAME(0, 6), dragoon_flame_update(&fm), FX(); }
static void flame_burns(void) { FLAME(1, 2), fm.animation_step.fields.relative_step = 1, dragoon_flame_update(&fm), FX(); }
static void flame_burnt_out(void) { FLAME(1, 2), dragoon_flame_update(&fm), FX(); }
static void flame_despawn(void) { FLAME(2, 2), dragoon_flame_update(&fm), FX(); }
static void flame_source_landed(void) { FLAME(3, 1), flame_source.air_state = 0, dragoon_flame_update(&fm), FX(); }
static void flame_trail_ends(void) { FLAME(3, 1), fm.animation_step.fields.relative_step = -1, dragoon_flame_update(&fm), FX(); }
static void flame_trail_kind_0(void) { FLAME(3, 0), fm.animation_step.fields.relative_step = -1, dragoon_flame_update(&fm), FX(); }
static void flame_trail_follows(void) { FLAME(3, 1), fm.animation_step.fields.relative_step = 1, dragoon_flame_update(&fm), FX(); }
static void flame_attached(void) { FLAME(4, 5), fm.ext.pointer.unk50 = (void*)&flame_source, dragoon_flame_update(&fm), FX(); }
static void (*const flame_cases[])(void) = {
    flame_init_5,
    flame_init_4,
    flame_init_3,
    flame_init_2,
    flame_init_0,
    flame_init_1,
    flame_init_other,
    flame_burns,
    flame_burnt_out,
    flame_despawn,
    flame_source_landed,
    flame_trail_ends,
    flame_trail_kind_0,
    flame_trail_follows,
    flame_attached,
};
static const u32 flame_expected[] = {
    0x4u, 0xFF000501u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x50123u, 0x150100u | VISUAL_SATURN_LAYER(4), 0x0u,
    0x4u, 0xFF000401u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x50123u, 0xE0100u | VISUAL_SATURN_LAYER(4), 0x0u,
    0x1u, 0xFF000301u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x50123u, 0x170100u | VISUAL_SATURN_LAYER(4), 0x0u,
    0x1u, 0xFF000201u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x50123u, 0x180100u | VISUAL_SATURN_LAYER(7), 0x0u,
    0x3u, 0xFF000001u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x50123u, 0x190100u | VISUAL_SATURN_LAYER(4), 0x0u,
    0x3u, 0xFF000101u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x50123u, 0x190100u | VISUAL_SATURN_LAYER(4), 0x0u,
    0x3u, 0xFF000601u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x50123u, 0x190100u | VISUAL_SATURN_LAYER(4), 0x0u,
    0x1u, 0x201u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x100u, 0x0u,
    0x2u, 0x201u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x100u, 0x0u,
    0x0u, 0x0u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x1u, 0xFF000101u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x1A0100u, 0x0u,
    0x2u, 0x101u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x100u, 0x0u,
    0x3u, 0x1u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x100u, 0x0u,
    0x3u, 0x101u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x100u, 0x0u,
    0x4u, 0x501u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x100u, 0x0u,
};
static u32 test_flame(u32 row)
{
    return object_run(flame_cases[row], row, &flame_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "dragoon_flame_states", 0, 0, COUNT(flame_cases), test_flame },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(flame_cases);
#else
const struct CTestGroup c_test_groups[] = {};
const u32 c_test_group_count = 0;
const u32 c_test_count = 0;
#endif
