#include "test_runtime.h"
#include "main/engine.h"
#include "main/1A5BC.h"
extern struct MiscObj* D_801396C0;
extern struct MiscObj* D_801396C4;
s32 func_8001F8FC(struct GameInfo*);

static const u32 func_8001F6E8_expected[] = { 1u, 4u, 1u, 4u, 1u, 0u, 6u };
static u32 test_func_8001F6E8(u32 row)
{
    u32 observed_values[7];
    struct EngineObj obj;
    struct MiscObj child_0;
    struct MiscObj child_1;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&child_1, 0, sizeof(child_1));
    memset(&controller_input, 0, sizeof(controller_input));
    controller_input.pressed = 255;
    D_801396C0 = &child_0;
    D_801396C4 = &child_1;
    func_8001F6E8(&obj);
    observed_values[0] = (u32)child_0.state;
    observed_values[1] = (u32)child_0.unk5;
    observed_values[2] = (u32)child_1.state;
    observed_values[3] = (u32)child_1.unk5;
    observed_values[4] = (u32)obj.unk2;
    observed_values[5] = (u32)obj.unk3;
    observed_values[6] = (u32)obj.unk4;
    return c_test_observe(0, row, observed_values, func_8001F6E8_expected, 7);
}
#undef controller_input

struct func_8001F8FC_case {
    u32 unk6;
    u32 expected[2];
};
static const struct func_8001F8FC_case func_8001F8FC_cases[] = {
    { 0, { 1u, 0xFFFFFFFFu } },
    { 1, { 0u, 0u } },
};
static u32 test_func_8001F8FC(u32 row)
{
    const struct func_8001F8FC_case* c = &func_8001F8FC_cases[row];
    u32 observed_values[2];
    struct GameInfo obj;
    s32 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&D_80139520, 0, sizeof(D_80139520));
    memset(&D_80139524, 0, sizeof(D_80139524));
    memset(&D_80139528, 0, sizeof(D_80139528));
    memset(&D_80139530, 0, sizeof(D_80139530));
    memset(&D_8013955C, 0, sizeof(D_8013955C));
    memset(&D_80139564, 0, sizeof(D_80139564));
    memset(&D_80139568, 0, sizeof(D_80139568));
    memset(&D_80141BD4, 0, sizeof(D_80141BD4));
    memset(&D_80171EA9, 0, sizeof(D_80171EA9));
    memset(&D_80173C84, 0, sizeof(D_80173C84));
    obj.unk6 = c->unk6;
    return_value = func_8001F8FC(&obj);
    observed_values[0] = (u32)return_value;
    observed_values[1] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, c->expected, 2);
}

struct func_8001FA24_case {
    u32 boss_flags;
    u32 expected[22];
};
static const struct func_8001FA24_case func_8001FA24_cases[] = {
    { -1, { 0xFFFFFFFFu, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 0u, 0u } },
    { 0, { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 0u, 0u } },
};
static u32 test_func_8001FA24(u32 row)
{
    const struct func_8001FA24_case* c = &func_8001FA24_cases[row];
    u32 observed_values[22];
    struct EngineObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.character_state.bytes[0] = 17;
    g_Player.boss_flags = c->boss_flags;
    func_8001FA24(&obj);
    observed_values[0] = (u32)g_Player.boss_flags;
    observed_values[1] = (u32)obj.character_state.bytes[0];
    observed_values[2] = (u32)obj.character_state.bytes[10];
    observed_values[3] = (u32)obj.character_state.bytes[11];
    observed_values[4] = (u32)obj.character_state.bytes[12];
    observed_values[5] = (u32)obj.character_state.bytes[13];
    observed_values[6] = (u32)obj.character_state.bytes[14];
    observed_values[7] = (u32)obj.character_state.bytes[15];
    observed_values[8] = (u32)obj.character_state.bytes[1];
    observed_values[9] = (u32)obj.character_state.bytes[2];
    observed_values[10] = (u32)obj.character_state.bytes[3];
    observed_values[11] = (u32)obj.character_state.bytes[4];
    observed_values[12] = (u32)obj.character_state.bytes[5];
    observed_values[13] = (u32)obj.character_state.bytes[6];
    observed_values[14] = (u32)obj.character_state.bytes[7];
    observed_values[15] = (u32)obj.character_state.bytes[8];
    observed_values[16] = (u32)obj.character_state.bytes[9];
    observed_values[17] = (u32)obj.palette_flags;
    observed_values[18] = (u32)obj.state;
    observed_values[19] = (u32)obj.unk1;
    observed_values[20] = (u32)obj.unk2;
    observed_values[21] = (u32)obj.unk5F;
    return c_test_observe(0, row, observed_values, c->expected, 22);
}

void func_8001F488(struct EngineObj*);
void func_8001F3D4(struct MainObj*);
extern struct MiscObj *D_801396C0, *D_801396C4;
extern s32 D_801396B8;
static const u16 presses[] = { 0, 0x40, 0x800, 0x1000 };
static const s32 edges[] = { -1, 0, 1 };
static u32 scroll_case(u32 row, u32 direct)
{
    struct EngineObj expected;
    struct PlayerObj player_before = g_Player;
    struct MainBssState main_before = main_bss_state;
    struct MiscObj children[2], children_expected[2];
    struct BackgroundObj backgrounds_expected[3];
    struct ControllerInput input_before;
    u32 character = direct ? row : row % 2, edge = direct ? 1 : row / 2 % 3, press = direct ? 0 : row / 6, i;
    s32 velocity = character ? -65536 : 65536, target = character ? 0xFFFFFF : 0x2000000;
    u32 confirmed = (presses[press] & 0x8FF) != 0, finished = direct || confirmed || (character ? edges[edge] <= 0 : edges[edge] > 0);
    memset(&engine_obj, 0, sizeof(engine_obj));
    engine_obj.state = 1;
    engine_obj.unk1 = 3;
    engine_obj.unk2 = 7;
    engine_obj.unk3 = 8;
    engine_obj.unk4 = 9;
    engine_obj.cur_character = character;
    memset(children, 0, sizeof(children));
    children[0].active = 0x41;
    children[0].id = 45;
    children[0].state = 2;
    children[0].unk5 = 1;
    children[1] = children[0];
    children[1].unk2 = 3;
    memcpy(children_expected, children, sizeof(children_expected));
    D_801396C0 = &children[0];
    D_801396C4 = &children[1];
    memset(background_objects, 0, sizeof(background_objects));
    for (i = 0; i < 3; i++) {
        background_objects[i].x_pos.val = (10 + i) * 65536 + 0x1234;
        background_objects[i].y_pos.val = (20 + i) * 65536 + 0x5678;
        background_objects[i].unk4C = 7;
    }
    background_objects[character].x_pos.val = target + edges[edge] - velocity;
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    controller_input.held = 0x1357;
    controller_input.previous = 0x2468;
    controller_input.pressed = presses[press];
    input_before = controller_input;
    D_801396B8 = velocity;
    g_FilterModeR = 1;
    g_FilterModeG = 2;
    g_FilterModeB = 3;
    g_FilterAmountR = 4;
    g_FilterAmountG = 5;
    g_FilterAmountB = 6;
    for (i = 0; i < 4; i++)
        D_8013E188[i] = 10 + i;
    expected = engine_obj;
    if (!direct && !confirmed)
        backgrounds_expected[character].x_pos.val += velocity;
    if (finished) {
        expected.unk4 = 6;
        expected.unk3 = 0;
        expected.unk2 = 8;
        backgrounds_expected[character].x_pos.val = character ? 0x1000000 : 0x2000000;
        if (!direct && confirmed) {
            backgrounds_expected[character].unk4C = 1;
            expected.character_state.bytes[1] = expected.character_state.bytes[2] = 1;
            for (i = 0; i < 2; i++) {
                children_expected[i].state = 1;
                children_expected[i].unk5 = 4;
            }
        }
    }
    if (direct)
        func_8001F3D4((struct MainObj*)&engine_obj);
    else
        func_8001F488(&engine_obj);
    c_test_same_words(&engine_obj, &expected, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    c_test_same_words(children, children_expected, sizeof(children_expected));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_bss_state));
    assert(controller_input.held == input_before.held && controller_input.previous == input_before.previous && controller_input.pressed == input_before.pressed);
    assert(D_801396C0 == &children[0] && D_801396C4 == &children[1] && D_801396B8 == velocity);
    for (i = 0; i < 4; i++)
        assert(D_8013E188[i] == (finished ? -1 : (s32)(10 + i)));
    assert(g_FilterModeR == (finished ? 0 : 1) && g_FilterModeG == (finished ? 0 : 2) && g_FilterModeB == (finished ? 0 : 3));
    assert(g_FilterAmountR == (finished ? 0 : 4) && g_FilterAmountG == (finished ? 0 : 5) && g_FilterAmountB == (finished ? 0 : 6));
    return 1;
}
static u32 scroll(u32 row) { return scroll_case(row, 0); }
static u32 complete(u32 row) { return scroll_case(row, 1); }

extern void func_8001F2BC(struct EngineObj*);
extern struct MiscObj* func_8001F150(struct EngineObj*, u8);
extern struct MiscObj *D_801396C0, *D_801396C4;
extern s32 D_801396B8, D_80139530, D_80141BD4;
extern u8 D_80139524, D_80139528;
static struct MiscObj expected_pool[64];
static u32 enter(u32 row)
{
    struct EngineObj expected;
    struct PlayerObj player_before = g_Player;
    struct MainBssState main_expected;
    struct BackgroundObj backgrounds_expected[3];
    u32 character = row % 2, boss = row / 2 % 8 + 1, available = 2, i;
    memset(&engine_obj, 0, sizeof(engine_obj));
    engine_obj.state = 1;
    engine_obj.unk1 = 2;
    engine_obj.unk2 = 1;
    engine_obj.stage = 15;
    engine_obj.cur_character = character;
    engine_obj.character_state.bytes[0] = boss;
    expected = engine_obj;
    expected.unk1 = 3;
    expected.unk2 = 0;
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    main_expected = main_bss_state;
    main_expected.transition.active = 1;
    main_expected.transition.fade_amount = 8;
    memset(background_objects, 0, sizeof(background_objects));
    for (i = 0; i < 3; i++)
        background_objects[i].x_pos.val = (10 + i) * 65536 + 0x1234;
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    backgrounds_expected[character].x_pos.val = character ? 0x3000000 : 0;
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = 0;
    memcpy(expected_pool, misc_objects, sizeof(expected_pool));
    for (i = 0; i < available; i++) {
        struct MiscObj* m = &expected_pool[i];
        m->active = 0x41;
        m->id = 45;
        m->unk2 = i == 0 ? (character ? 9 : 0) : boss + (character ? 9 : 0);
    }
    func_8001F2BC(&engine_obj);
    c_test_same_words(&engine_obj, &expected, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&main_bss_state, &main_expected, sizeof(main_bss_state));
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    c_test_same_words(misc_objects, expected_pool, sizeof(expected_pool));
    assert(D_801396B8 == (character ? -0x100000 : 0x100000));
    assert(D_801396C0 == (available ? &misc_objects[0] : NULL));
    assert(D_801396C4 == (available == 2 ? &misc_objects[1] : NULL));
    assert(D_80139524 == 0x70 && D_80139528 == 0x70 && D_80141BD4 == 2 && D_80173C84 == 1 && D_80139530 == 7);
    return 1;
}
static u32 label_capacity(u32 row)
{
    struct EngineObj engine_before = engine_obj;
    struct PlayerObj player_before = g_Player;
    struct MiscObj* result;
    u32 full = row % 2, variant = row / 2 ? 9 : 0, i;
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = i == 63 && !full ? 0 : 1;
    memcpy(expected_pool, misc_objects, sizeof(expected_pool));
    if (!full) {
        expected_pool[63].active = 0x41;
        expected_pool[63].id = 45;
        expected_pool[63].unk2 = variant;
    }
    result = func_8001F150(&engine_obj, variant);
    assert(result == (full ? NULL : &misc_objects[63]));
    c_test_same_words(misc_objects, expected_pool, sizeof(expected_pool));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "func_8001F6E8", 0, 0, 1, test_func_8001F6E8 },
    { "func_8001F8FC", 0, 0, 2, test_func_8001F8FC },
    { "func_8001FA24", 0, 0, 2, test_func_8001FA24 },
    { "scroll_confirmation_and_exact_fixed_point_thresholds", NULL, NULL, 24, scroll },
    { "completion_uses_selected_character_background", NULL, NULL, 2, complete },
    { "both_characters_eight_boss_rewards_normal_screen_setup", NULL, NULL, 16, enter },
    { "public_label_allocation_API_full_and_last_slot_X_Zero_headers", NULL, NULL, 4, label_capacity },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 2 + 2 + 24 + 2 + 16 + 4;
