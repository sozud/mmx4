#include "test_runtime.h"
#include "main/misc/misc_57_falling_piece.h"
#include "main/2824.h"
extern u16 menu_button_bits_a[8], menu_button_bits_b[8];

static u32 binding_case(u8 disabled)
{
    struct UnkObj obj;
    u32 actual;

    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    obj.bg_offset = -1;
    obj.x_pos.i.hi = 90;
    obj.y_pos.i.hi = 80;
    obj.unk2 = disabled ? 7 : 0;
    obj.animation_step.fields.frame_index = 0x55;
    engine_obj.cur_character = 1;
    if (disabled)
        menu_button_bits_a[7] = menu_button_bits_a[0];
    D_800EE430[4] = disabled ? menu_button_bits_b[3] : 0xFFFF;
    func_800D3798(&obj);
    assert(obj.unk2 == (disabled ? 7 : 0));
    assert(obj.x_pos.i.hi == 90 && obj.y_pos.i.hi == 80);
    assert(D_800EE430[4] == (disabled ? menu_button_bits_b[3] : 0xFFFF));
    actual = obj.animation_step.fields.frame_index | ((u32)(u16)obj.unk42 << 8) | ((u32)obj.on_screen << 24);
    return actual;
}
static u32 unmatched_button(void)
{
    return binding_case(0);
}
static u32 disabled_label(void)
{
    return binding_case(1);
}
static const CTestCase menu_binding_edges_cases[] = {
    unmatched_button,
    disabled_label,
};
static const u32 menu_binding_edges_cases_expected[] = { 0x1780055u, 0x178006Bu };
#undef main_bss_state

#undef main_bss_state

#undef main_bss_state

const struct CTestGroup c_test_groups[] = {
    { "menu_binding_edges", menu_binding_edges_cases, menu_binding_edges_cases_expected, COUNT(menu_binding_edges_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(menu_binding_edges_cases);
