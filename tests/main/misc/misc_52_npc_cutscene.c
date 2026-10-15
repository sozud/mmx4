#include "test_runtime.h"

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
#define LINE_CASE(m)                           \
    static u32 npc_line_context_line_##m(void) \
    {                                          \
        return line_case(m);                   \
    }
LINE_CASE(0)
LINE_CASE(1)
#define LINE_ENTRY(m) npc_line_context_line_##m,
static const CTestCase npc_line_context_cases[]
    = { LINE_ENTRY(0) LINE_ENTRY(1) };
static const u32 npc_line_context_cases_expected[] = { 0x802B0002u, 0x80230002u };
#undef main_bss_state
#undef LINE_CASE
#undef LINE_ENTRY

struct npc_cutscene_fade_out_case {
    u32 timer;
    u32 expected[3];
};
static const struct npc_cutscene_fade_out_case npc_cutscene_fade_out_cases[] = {
    { 0, { 0u, 0xFFu, 0u } },
    { 1, { 0x40u, 0u, 0u } },
};
static u32 test_npc_cutscene_fade_out(u32 row)
{
    const struct npc_cutscene_fade_out_case* c = &npc_cutscene_fade_out_cases[row];
    u32 observed_values[3];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    obj.ext.misc_52.timer = c->timer;
    npc_cutscene_fade_out(&obj);
    observed_values[0] = (u32)engine_obj.unkF;
    observed_values[1] = (u32)obj.ext.misc_52.timer;
    observed_values[2] = (u32)obj.on_screen;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

struct npc_cutscene_finish_wait_case {
    u32 timer;
    u32 expected[2];
};
static const struct npc_cutscene_finish_wait_case npc_cutscene_finish_wait_cases[] = {
    { 1, { 0x40u, 0u } },
    { 0, { 0u, 0xFFu } },
};
static u32 test_npc_cutscene_finish_wait(u32 row)
{
    const struct npc_cutscene_finish_wait_case* c = &npc_cutscene_finish_wait_cases[row];
    u32 observed_values[2];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.ext.misc_52.timer = c->timer;
    npc_cutscene_finish_wait(&obj);
    observed_values[0] = (u32)engine_obj.unkF;
    observed_values[1] = (u32)obj.ext.misc_52.timer;
    return c_test_observe(0, row, observed_values, c->expected, 2);
}

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

const struct CTestGroup c_test_groups[] = {
    { "npc_line_context", npc_line_context_cases, npc_line_context_cases_expected, COUNT(npc_line_context_cases), 0 },
    { "npc_cutscene_fade_out", 0, 0, 2, test_npc_cutscene_fade_out },
    { "npc_cutscene_finish_wait", 0, 0, 2, test_npc_cutscene_finish_wait },
    { "npc_cutscene_talk_line", 0, 0, 2, test_npc_cutscene_talk_line },
    { "npc_cutscene_talk_wait_line", 0, 0, 3, test_npc_cutscene_talk_wait_line },
    { "npc_cutscene_talk_wait_player", 0, 0, 4, test_npc_cutscene_talk_wait_player },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(npc_line_context_cases) + 2 + 2 + 2 + 3 + 4;
