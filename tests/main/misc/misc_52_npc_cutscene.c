#include "test_runtime.h"
#include "main/misc/misc_52_npc_cutscene.h"
#include "main/55C4.h"
void npc_cutscene_reply(struct MiscObj*);

static u32 line_case(u32 character)
{
    struct MiscObj obj, before;
    struct PlayerObj player_before;
    struct AbcObj dialogue_before;
    struct EngineObj engine_before;
    struct MainBssState clock_before;
    struct BackgroundObj backgrounds_before[3];
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&abc_object, 0, sizeof(abc_object));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 0x41;
    obj.id = 52;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 0x27;
    obj.on_screen = 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 80 * 65536 + 0x5678;
    engine_obj.cur_character = character;
    abc_object.unkC = 0x80;
    abc_object.unkA = 0x27;
    abc_object.unkD = 4;
    abc_object.unk10 = 0x1234;
    main_bss_state.frame_counter = 2;
    before = obj;
    dialogue_before = abc_object;
    engine_before = engine_obj;
    player_before = g_Player;
    clock_before = main_bss_state;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    npc_cutscene_talk_line(&obj);
    actual = (u8)obj.unk5 | ((u32)(u8)obj.on_screen << 8) | ((u32)(u16)abc_object.unk10 << 16);
    before.unk5 = obj.unk5;
    before.on_screen = obj.on_screen;
    dialogue_before.unk10 = abc_object.unk10;
    for (i = 0; i < sizeof(obj); i++)
        assert(((u8*)&obj)[i] == ((u8*)&before)[i]);
    for (i = 0; i < sizeof(abc_object); i++)
        assert(((u8*)&abc_object)[i] == ((u8*)&dialogue_before)[i]);
    for (i = 0; i < sizeof(engine_obj); i++)
        assert(((u8*)&engine_obj)[i] == ((u8*)&engine_before)[i]);
    for (i = 0; i < sizeof(g_Player); i++)
        assert(((u8*)&g_Player)[i] == ((u8*)&player_before)[i]);
    for (i = 0; i < sizeof(main_bss_state); i++)
        assert(((u8*)&main_bss_state)[i] == ((u8*)&clock_before)[i]);
    for (i = 0; i < sizeof(background_objects); i++)
        assert(((u8*)background_objects)[i] == ((u8*)backgrounds_before)[i]);
    return actual;
}
static const u32 npc_line_context_cases_expected[] = { 0x802B0002u, 0x80230002u };

struct npc_cutscene_talk_line_case {
    u32 frame_counter;
    u32 expected[3];
};
static const struct npc_cutscene_talk_line_case npc_cutscene_talk_line_cases[] = {
    { 0, { 0xFEu, 0u, 0u } },
    { 1, { 0xFEu, 1u, 0u } },
};
static u32 test_npc_cutscene_talk_line(u32 row)
{
    const struct npc_cutscene_talk_line_case* c = &npc_cutscene_talk_line_cases[row];
    u32 observed_values[3];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&D_801397BC, 0, sizeof(D_801397BC));
    memset(&D_801397C0, 0, sizeof(D_801397C0));
    memset(&D_801397C4, 0, sizeof(D_801397C4));
    memset(&D_801397C8, 0, sizeof(D_801397C8));
    memset(&D_801397CC, 0, sizeof(D_801397CC));
    memset(&D_801397D0, 0, sizeof(D_801397D0));
    memset(&D_801397D4, 0, sizeof(D_801397D4));
    memset(&D_801397D8, 0, sizeof(D_801397D8));
    memset(&D_801397DC, 0, sizeof(D_801397DC));
    memset(&D_801397E0, 0, sizeof(D_801397E0));
    memset(&D_801397E4, 0, sizeof(D_801397E4));
    memset(&D_80139824, 0, sizeof(D_80139824));
    memset(&D_80139828, 0, sizeof(D_80139828));
    memset(&abc_object, 0, sizeof(abc_object));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&misc_objects, 0, sizeof(misc_objects));
    memset(&need_palette_load, 0, sizeof(need_palette_load));

    obj.ext.misc_52.timer = 255;
    obj.unk5 = 0;
    engine_obj.cur_character = 0;
    main_bss_state.frame_counter = c->frame_counter;
    npc_cutscene_talk_line(&obj);
    observed_values[0] = (u32)obj.ext.misc_52.timer;
    observed_values[1] = (u32)obj.on_screen;
    observed_values[2] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}
#undef main_bss_state

struct npc_cutscene_talk_wait_line_case {
    u32 unkC, cur_character;
    u32 expected[4];
};
static const struct npc_cutscene_talk_wait_line_case npc_cutscene_talk_wait_line_cases[] = {
    { 255, 0, { 0u, 0u, 0u, 0u } },
    { 0, -1, { 0x1Eu, 2u, 1u, 0u } },
    { 0, 0, { 0x1Eu, 2u, 0u, 0u } },
};
static u32 test_npc_cutscene_talk_wait_line(u32 row)
{
    const struct npc_cutscene_talk_wait_line_case* c = &npc_cutscene_talk_wait_line_cases[row];
    u32 observed_values[4];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&abc_object, 0, sizeof(abc_object));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&background_objects, 0, sizeof(background_objects));
    abc_object.unkC = c->unkC;
    engine_obj.cur_character = c->cur_character;
    npc_cutscene_talk_wait_line(&obj);
    observed_values[0] = (u32)obj.ext.misc_52.timer;
    observed_values[1] = (u32)obj.state;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

struct npc_cutscene_talk_wait_player_case {
    u32 unk6, g_Player_x_pos_hi, v_0_x_pos_hi, unk26;
    u32 expected[4];
};
static const struct npc_cutscene_talk_wait_player_case npc_cutscene_talk_wait_player_cases[] = {
    { 0, 0, 0, 0, { 0u, 0u, 0u, 0u } },
    { -1, 0, -16640, 16384, { 0x4000u, 0u, 0u, 0xFFFFFFFFu } },
    { 0, 2328, 0, 0, { 0x8C0u, 0u, 0u, 1u } },
    { -1, 0, 0, 0, { 0u, 0x1Eu, 1u, 0u } },
};
static u32 test_npc_cutscene_talk_wait_player(u32 row)
{
    const struct npc_cutscene_talk_wait_player_case* c = &npc_cutscene_talk_wait_player_cases[row];
    u32 observed_values[4];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    obj.unk6 = c->unk6;
    g_Player.x_pos.i.hi = c->g_Player_x_pos_hi;
    background_objects[0].x_pos.i.hi = c->v_0_x_pos_hi;
    background_objects[0].unk26 = c->unk26;
    npc_cutscene_talk_wait_player(&obj);
    observed_values[0] = (u32)background_objects[0].unk26;
    observed_values[1] = (u32)obj.ext.misc_52.timer;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

static const struct {
    u8 phase, timer, dialogue, next_phase, next_timer, next_state;
    s8 fade;
    s16 x;
} reply_cases[] = {
    { 0, 2, 0x80, 0, 1, 1, 0, 100 },
    { 0, 1, 0x80, 1, 0, 1, 0, 100 },
    { 0, 0, 0x80, 0, 255, 1, 0, 100 },
    { 1, 0, 0x80, 2, 0, 1, 0, 100 },
    { 2, 3, 0x80, 2, 3, 1, 0, 100 },
    { 2, 3, 0, 2, 30, 2, 0, 100 },
    { 0, 1, 0x80, 0, 1, 1, 1, 100 },
    { 1, 0, 0x80, 1, 0, 1, -1, 1000 },
    { 2, 3, 0, 2, 3, 1, 1, 100 },
};
static u32 reply_frame = 5;
static u32* reply_animations[] = { &reply_frame };

static u32 test_npc_reply(u32 row)
{
    struct MiscObj obj, expected;
    memset(&obj, 0, sizeof(obj));
    memset(&abc_object, 0, sizeof(abc_object));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    obj.active = 0x41;
    obj.id = 52;
    obj.state = 1;
    obj.unk5 = reply_cases[row].phase;
    obj.unk6 = 7;
    obj.bg_offset = -1;
    obj.x_pos.val = FIXED(reply_cases[row].x);
    obj.y_pos.val = FIXED(80);
    obj.ext.misc_52.timer = reply_cases[row].timer;
    obj.animation_table = (const u8* const*)reply_animations;
    set_animation(&obj, 0);
    abc_object.unkC = reply_cases[row].dialogue;
    abc_object.unk10 = 0x1234;
    main_bss_state.transition.active = reply_cases[row].fade;
    expected = obj;
    expected.state = reply_cases[row].next_state;
    expected.unk5 = reply_cases[row].next_phase;
    expected.ext.misc_52.timer = reply_cases[row].next_timer;
    expected.on_screen = reply_cases[row].x == 100;
    if (reply_cases[row].next_state == 2)
        expected.unk6 = 0;
    if (!reply_cases[row].fade)
        expected.animation_step.fields.duration = 4;
    npc_cutscene_reply(&obj);
    c_test_same_words(&obj, &expected, sizeof(expected));
    assert(abc_object.unkC == reply_cases[row].dialogue);
    assert((u16)abc_object.unk10 == (reply_cases[row].phase == 1 && !reply_cases[row].fade ? 0x8024 : 0x1234));
    assert(main_bss_state.transition.active == reply_cases[row].fade);
    assert(reply_frame == 5);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "npc_reply", 0, 0, COUNT(reply_cases), test_npc_reply },
    { "npc_line_context", NULL, npc_line_context_cases_expected, COUNT(npc_line_context_cases_expected), line_case },
    { "npc_cutscene_talk_line", 0, 0, 2, test_npc_cutscene_talk_line },
    { "npc_cutscene_talk_wait_line", 0, 0, 3, test_npc_cutscene_talk_wait_line },
    { "npc_cutscene_talk_wait_player", 0, 0, 4, test_npc_cutscene_talk_wait_player },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(reply_cases) + COUNT(npc_line_context_cases_expected) + 2 + 3 + 4;
