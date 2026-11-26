#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/misc/misc_12_stage_icon.h"

static s32 icon_frames[4];
static u32 icon_meta[4];
#define im state_room.misc
#define ICON(st, kind, chosen) (state_reset(0, 0, 0), memset(&engine_obj, 0, sizeof(engine_obj)), TEST_MENU_FRAMES = (u8*)icon_frames, D_801406A8 = icon_meta, engine_obj.unk3 = chosen, im.active = 1, im.state = st, im.unk2 = kind, im.x_pos.i.hi = 0x80, im.y_pos.i.hi = 0x60)
#define IX() (state_extra = (u16)im.unk42 | (u32)im.unk16 << 16 | (u32)im.on_screen << 24 | (u32)im.unk17 << 28)
static void icon_init_stage(void)
{
    ICON(0, 3, 0), stage_icon_update(&im), IX();
}
static void icon_init_center(void) { ICON(0, 8, 0), stage_icon_update(&im), IX(); }
static void icon_init_corner(void) { ICON(0, 9, 0), stage_icon_update(&im), IX(); }
static void icon_init_portrait(void) { ICON(0, 0x83, 0), stage_icon_update(&im), IX(); }
static void icon_highlighted(void) { ICON(1, 3, 3), stage_icon_update(&im), IX(); }
static void icon_dimmed(void) { ICON(1, 3, 2), stage_icon_update(&im), IX(); }
static void icon_portrait_chosen(void) { ICON(2, 0x83, 0x83), stage_icon_update(&im), IX(); }
static void icon_portrait_other(void) { ICON(2, 0x83, 0x82), stage_icon_update(&im), IX(); }
static void icon_selected_shown(void) { ICON(4, 8, 8), stage_icon_update(&im), IX(); }
static void icon_selected_hidden(void) { ICON(4, 8, 3), stage_icon_update(&im), IX(); }
static void (*const icon_cases[])(void) = {
    icon_init_stage,
    icon_init_center,
    icon_init_corner,
    icon_init_portrait,
    icon_highlighted,
    icon_dimmed,
    icon_portrait_chosen,
    icon_portrait_other,
    icon_selected_shown,
    icon_selected_hidden,
};
static const u32 icon_expected[] = {
    0x1u,
    0xFF000301u,
    0xEF0000u,
    0x1200000u,
    0x0u,
    0x0u,
    0x0u,
    0x1E0000u | OBJECT_CLUT(0x780A),
    0x100000u | OBJECT_CLUT(0x780A),
    0x0u,
    0x3u,
    0xFF000801u,
    0x600000u,
    0x1800000u,
    0x0u,
    0x0u,
    0x0u,
    0x1E0000u | OBJECT_CLUT(0x780A),
    0x100000u | OBJECT_CLUT(0x780A),
    0x0u,
    0x4u,
    0xFF000801u,
    0x3C0000u,
    0x1600000u,
    0x0u,
    0x0u,
    0x0u,
    0x1E0000u | OBJECT_CLUT(0x780A),
    0x100000u | OBJECT_CLUT(0x780A),
    0x0u,
    0x2u,
    0xFF008301u,
    0xEF0000u,
    0x1200000u,
    0x0u,
    0x0u,
    0x0u,
    0x1E0000u | OBJECT_CLUT(0x7803),
    0x10120000u | OBJECT_CLUT(0x7803),
    0x0u,
    0x1u,
    0x301u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u | OBJECT_CLUT(0x780A),
    0x1000000u | OBJECT_CLUT(0x780A),
    0x0u,
    0x1u,
    0x301u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u | OBJECT_CLUT(0x7809),
    OBJECT_CLUT(0x7809),
    0x0u,
    0x2u,
    0x8301u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u | OBJECT_CLUT(0x7803),
    0x1000000u | OBJECT_CLUT(0x7803),
    0x0u,
    0x2u,
    0x8301u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u | OBJECT_CLUT(0x7803),
    0x1000000u | OBJECT_CLUT(0x7803),
    0x0u,
    0x4u,
    0x801u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x1000000u,
    0x0u,
    0x4u,
    0x801u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
};
static u32 test_icon(u32 row)
{
    return object_run(icon_cases[row], row, &icon_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "stage_icon_states", 0, 0, COUNT(icon_cases), test_icon },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(icon_cases);
