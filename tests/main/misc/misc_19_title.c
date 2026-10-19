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

extern struct TitleObjectInit title_object_inits[];
extern u32* title_animations[];
static const u8 frames[] = { 2, 29, 30 };
static u32 menu_frame(u32 row)
{
    struct MiscObj obj, expected;
    struct GameInfo info_before;
    struct MainBssState main_before = main_bss_state;
    struct EngineObj engine_before = engine_obj;
    struct PlayerObj player_before = g_Player;
    u32 selection = row % 3, facing = row / 3;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 19;
    obj.state = 1;
    obj.unk2 = 15;
    obj.bg_offset = -1;
    obj.unk15 = facing ? 0x40 : 0;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 64 * 65536 + 0x5678;
    obj.unk16 = 3;
    obj.animation_table = title_animations;
    obj.animation_step.fields.frame_index = 2;
    game_info.unk2 = selection;
    info_before = game_info;
    expected = obj;
    expected.unk16 = 2;
    expected.on_screen = 1;
    expected.y_pos.i.hi = 128 + 16 * selection;
    expected.animation_step.fields.frame_index = frames[selection];
    assert(title_object_inits[2].sprite == 2 && title_object_inits[13].sprite == 29 && title_object_inits[14].sprite == 30);
    title_draw(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&game_info, &info_before, sizeof(game_info));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_bss_state));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "title_draw", 0, 0, 2, test_title_draw },
    { "all_three_title_menu_choices_use_shipped_frames", NULL, NULL, 6, menu_frame },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2 + 6;
