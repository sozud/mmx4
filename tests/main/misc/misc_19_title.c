#include "test_runtime.h"
#include "main/misc/misc_19_title.h"
extern struct TitleObjectInit title_object_inits[22];

struct title_draw_case {
    u32 obj_unk2, game_info_unk2;
    u32 expected[4];
};
static const struct title_draw_case title_draw_cases[] = {
    { 6, 0, { 0u, 0u, 0u, 0u } },
    { 15, -128, { 0u, 1u, 2u, 0x60u } },
};
static u32 test_title_draw(u32 row)
{
    const struct title_draw_case* c = &title_draw_cases[row];
    u32 observed_values[4];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&game_info, 0, sizeof(game_info));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk2 = c->obj_unk2;
    game_info.unk2 = c->game_info_unk2;
    title_object_inits[2].sprite = 0;
    title_object_inits[13].sprite = 0;
    title_object_inits[14].sprite = 0;
    title_draw(&obj);
    observed_values[0] = (u32)obj.animation_step.fields.frame_index;
    observed_values[1] = (u32)obj.on_screen;
    observed_values[2] = (u32)obj.unk16;
    observed_values[3] = (u32)obj.y_pos.i.hi;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}
#undef main_bss_state

const struct CTestGroup c_test_groups[] = {
    { "title_draw", 0, 0, 2, test_title_draw },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2;
