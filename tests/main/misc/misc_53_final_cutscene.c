#include "test_runtime.h"
extern union AnimationStep final_cutscene_anim_0[3];
extern union AnimationStep* final_cutscene_animations[1];
void final_cutscene_finish(struct MiscObj*);

static u32 approach_case(u32 character, u32 observation)
{
    struct MiscObj obj, before;
    struct AbcObj dialogue_before;
    struct BackgroundObj bg_before;
    struct EngineObj engine_before;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&abc_object, 0, sizeof(abc_object));
    memset(background_objects, 0, sizeof(background_objects));
    memset(&engine_obj, 0, sizeof(engine_obj));
    obj.active = 0x41;
    obj.id = 53;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 0x27;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 80 * 65536 + 0x5678;
    obj.x_vel.val = 65536;
    obj.y_vel.val = -32768;
    obj.animation_table = (u32**)final_cutscene_animations;
    obj.animation_cursor = (u8*)&final_cutscene_anim_0[0];
    obj.animation_step = final_cutscene_anim_0[0];
    obj.ext.misc_53.timer = 1;
    obj.ext.misc_53.movement_timer = 0x27;
    obj.ext.misc_53.x_step = -1;
    background_objects[0].x_pos.i.hi = 100;
    background_objects[0].unk26 = 100;
    engine_obj.cur_character = character;
    abc_object.unkC = 0x80;
    abc_object.unkA = 0x27;
    abc_object.unkD = 4;
    abc_object.unk10 = 0x1234;
    before = obj;
    dialogue_before = abc_object;
    bg_before = background_objects[0];
    engine_before = engine_obj;
    final_cutscene_approach(&obj);
    before.unk5 = obj.unk5;
    before.x_pos = obj.x_pos;
    before.y_pos = obj.y_pos;
    before.animation_cursor = obj.animation_cursor;
    before.animation_step = obj.animation_step;
    before.ext.misc_53.timer = obj.ext.misc_53.timer;
    before.ext.misc_53.movement_timer = obj.ext.misc_53.movement_timer;
    before.ext.misc_53.x_step = obj.ext.misc_53.x_step;
    dialogue_before.unk10 = abc_object.unk10;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(abc_object) / 4; i++)
        assert(((u32*)&abc_object)[i] == ((u32*)&dialogue_before)[i]);
    for (i = 0; i < sizeof(bg_before) / 4; i++)
        assert(((u32*)&background_objects[0])[i] == ((u32*)&bg_before)[i]);
    for (i = 0; i < sizeof(engine_before) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    assert(obj.animation_table == (u32**)final_cutscene_animations);
    assert(obj.animation_cursor == (u8*)&final_cutscene_anim_0[1]);
    assert(final_cutscene_animations[0] == final_cutscene_anim_0);
    assert(final_cutscene_anim_0[0].packed == 0x00010001 && final_cutscene_anim_0[1].packed == 0x01010001 && final_cutscene_anim_0[2].packed == 0x02FE0001);
    switch (observation) {
    case 0:
        actual = (u16)obj.ext.misc_53.timer | ((u32)obj.ext.misc_53.movement_timer << 16) | ((u32)(u8)obj.ext.misc_53.x_step << 24);
        break;
    case 1:
        actual = (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)(u16)abc_object.unk10 << 16);
        break;
    case 2:
        actual = obj.x_pos.val;
        break;
    case 3:
        actual = obj.y_pos.val;
        break;
    default:
        actual = obj.animation_step.packed;
        break;
    }
    return actual;
}
#define APPROACH_CASE(m, n)                                    \
    static u32 final_approach_context_approach_##m##_##n(void) \
    {                                                          \
        return approach_case(m, n);                            \
    }
#define APPROACH_MODE(m) APPROACH_CASE(m, 0) APPROACH_CASE(m, 1) APPROACH_CASE(m, 2) APPROACH_CASE(m, 3) APPROACH_CASE(m, 4)
APPROACH_MODE(0)
APPROACH_MODE(1)
#define APPROACH_ENTRY(m, n) final_approach_context_approach_##m##_##n,
#define APPROACH_ENTRIES(m) APPROACH_ENTRY(m, 0) APPROACH_ENTRY(m, 1) APPROACH_ENTRY(m, 2) APPROACH_ENTRY(m, 3) APPROACH_ENTRY(m, 4)
static const CTestCase final_approach_context_cases[]
    = { APPROACH_ENTRIES(0) APPROACH_ENTRIES(1) };
static const u32 final_approach_context_cases_expected[] = { 0x10A0000u, 0x802D2702u, 0x651234u, 0x50D678u, 0x1010001u, 0x10A0000u, 0x80262702u, 0x651234u, 0x50D678u, 0x1010001u };
#undef APPROACH_CASE
#undef APPROACH_MODE
#undef APPROACH_ENTRY
#undef APPROACH_ENTRIES

static const u32 final_cutscene_approach_expected[] = { 0u, 0xFFFFFFFFu, 0u, 0u };
static u32 test_final_cutscene_approach(u32 row)
{
    u32 observed_values[4];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&engine_obj, 0, sizeof(engine_obj));
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
    memset(&misc_objects, 0, sizeof(misc_objects));
    memset(&need_palette_load, 0, sizeof(need_palette_load));

    background_objects[0].x_pos.i.hi = 0;
    background_objects[0].unk26 = 0;
    obj.ext.misc_53.timer = 0;
    obj.unk5 = 0;
    engine_obj.cur_character = 0;
    final_cutscene_approach(&obj);
    observed_values[0] = (u32)obj.ext.misc_53.movement_timer;
    observed_values[1] = (u32)obj.ext.misc_53.timer;
    observed_values[2] = (u32)obj.ext.misc_53.x_step;
    observed_values[3] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, final_cutscene_approach_expected, 4);
}

struct final_cutscene_finish_case {
    u32 timer;
    u32 expected[12];
};
static const struct final_cutscene_finish_case final_cutscene_finish_cases[] = {
    { 0, { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0xFFFFFFFFu, 0u } },
    { 1, { 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0x7C00u, 0x3E0u, 0x1Fu, 4u, 2u, 1u, 0u, 2u } },
};
static u32 test_final_cutscene_finish(u32 row)
{
    const struct final_cutscene_finish_case* c = &final_cutscene_finish_cases[row];
    u32 observed_values[12];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_FilterAmountB, 0, sizeof(g_FilterAmountB));
    memset(&g_FilterAmountG, 0, sizeof(g_FilterAmountG));
    memset(&g_FilterAmountR, 0, sizeof(g_FilterAmountR));
    memset(&g_FilterModeB, 0, sizeof(g_FilterModeB));
    memset(&g_FilterModeG, 0, sizeof(g_FilterModeG));
    memset(&g_FilterModeR, 0, sizeof(g_FilterModeR));
    obj.ext.misc_53.timer = c->timer;
    final_cutscene_finish(&obj);
    observed_values[0] = (u32)D_8013E188[0];
    observed_values[1] = (u32)D_8013E188[1];
    observed_values[2] = (u32)D_8013E188[2];
    observed_values[3] = (u32)D_8013E188[3];
    observed_values[4] = (u32)g_FilterAmountB;
    observed_values[5] = (u32)g_FilterAmountG;
    observed_values[6] = (u32)g_FilterAmountR;
    observed_values[7] = (u32)g_FilterModeB;
    observed_values[8] = (u32)g_FilterModeG;
    observed_values[9] = (u32)g_FilterModeR;
    observed_values[10] = (u32)obj.ext.misc_53.timer;
    observed_values[11] = (u32)obj.state;
    return c_test_observe(0, row, observed_values, c->expected, 12);
}

struct final_cutscene_leave_case {
    u32 on_screen;
    u32 expected[1];
};
static const struct final_cutscene_leave_case final_cutscene_leave_cases[] = {
    { -1, { 0u } },
    { 0, { 1u } },
};
static u32 test_final_cutscene_leave(u32 row)
{
    const struct final_cutscene_leave_case* c = &final_cutscene_leave_cases[row];
    u32 observed_values[1];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.on_screen = c->on_screen;
    final_cutscene_leave(&obj);
    observed_values[0] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, c->expected, 1);
}

struct final_cutscene_rise_case {
    u32 y_vel;
    u32 expected[2];
};
static const struct final_cutscene_rise_case final_cutscene_rise_cases[] = {
    { 0, { 0u, 0u } },
    { -1048576, { 1u, 0u } },
};
static u32 test_final_cutscene_rise(u32 row)
{
    const struct final_cutscene_rise_case* c = &final_cutscene_rise_cases[row];
    u32 observed_values[2];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.y_vel.val = c->y_vel;
    final_cutscene_rise(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, c->expected, 2);
}

struct final_cutscene_start_effect_case {
    u32 pool_0_full;
    u32 expected[4];
};
static const struct final_cutscene_start_effect_case final_cutscene_start_effect_cases[] = {
    { 0, { 0x41u, 0x1Cu, 0x12Cu, 1u } },
    { 255, { 1u, 0u, 0x12Cu, 1u } },
};
static u32 test_final_cutscene_start_effect(u32 row)
{
    const struct final_cutscene_start_effect_case* c = &final_cutscene_start_effect_cases[row];
    u32 observed_values[4];
    struct MiscObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&effect_objects, 0, sizeof(effect_objects));
    pool_0_full = c->pool_0_full;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            effect_objects[slot].active = pool_0_full ? 1 : 0;
    }
    final_cutscene_start_effect(&obj);
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)obj.ext.misc_53.timer;
    observed_values[3] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

struct final_cutscene_wait_effect_case {
    u32 timer, pool_0_full;
    u32 expected[5];
};
static const struct final_cutscene_wait_effect_case final_cutscene_wait_effect_cases[] = {
    { 0, 0, { 0u, 0u, 0u, 0xFFFFFFFFu, 0u } },
    { 1, 0, { 1u, 2u, 0xCu, 0u, 1u } },
    { 1, 255, { 1u, 0u, 0u, 0u, 1u } },
};
static u32 test_final_cutscene_wait_effect(u32 row)
{
    const struct final_cutscene_wait_effect_case* c = &final_cutscene_wait_effect_cases[row];
    u32 observed_values[5];
    struct MiscObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&effect_objects, 0, sizeof(effect_objects));
    obj.ext.misc_53.timer = c->timer;
    pool_0_full = c->pool_0_full;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            effect_objects[slot].active = pool_0_full ? 1 : 0;
    }
    final_cutscene_wait_effect(&obj);
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)effect_objects[0].unk2;
    observed_values[3] = (u32)obj.ext.misc_53.timer;
    observed_values[4] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

struct final_cutscene_wait_fade_case {
    u32 active;
    u32 expected[2];
};
static const struct final_cutscene_wait_fade_case final_cutscene_wait_fade_cases[] = {
    { 1, { 0u, 0u } },
    { 0, { 0x1Eu, 1u } },
};
static u32 test_final_cutscene_wait_fade(u32 row)
{
    const struct final_cutscene_wait_fade_case* c = &final_cutscene_wait_fade_cases[row];
    u32 observed_values[2];
    struct MiscObj obj;
    struct EffectObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&effect_objects, 0, sizeof(effect_objects));
    child_0_present = 255;
    child_0.active = c->active;
    obj.ext.misc_53.effect = child_0_present ? &child_0 : NULL;
    final_cutscene_wait_fade(&obj);
    observed_values[0] = (u32)obj.ext.misc_53.timer;
    observed_values[1] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, c->expected, 2);
}

struct func_800D2CA4_case {
    u32 unkC, frame_counter, movement_timer;
    u32 expected[8];
};
static const struct func_800D2CA4_case func_800D2CA4_cases[] = {
    { 255, -524288, 0, { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 255, 0, 0, { 0xFFu, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 0, 0, 1, { 0xAu, 0u, 0u, 0x4200u, 1u, 0u, 0u, 0x50000u } },
};
static u32 test_func_800D2CA4(u32 row)
{
    const struct func_800D2CA4_case* c = &func_800D2CA4_cases[row];
    u32 observed_values[8];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&abc_object, 0, sizeof(abc_object));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    abc_object.unkC = c->unkC;
    main_bss_state.frame_counter = c->frame_counter;
    obj.ext.misc_53.movement_timer = c->movement_timer;
    func_800D2CA4(&obj);
    observed_values[0] = (u32)obj.ext.misc_53.movement_timer;
    observed_values[1] = (u32)obj.ext.misc_53.x_step;
    observed_values[2] = (u32)obj.unk28;
    observed_values[3] = (u32)obj.unk2C;
    observed_values[4] = (u32)obj.unk5;
    observed_values[5] = (u32)obj.x_vel.val;
    observed_values[6] = (u32)obj.y_pos.i.hi;
    observed_values[7] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, c->expected, 8);
}
#undef main_bss_state

const struct CTestGroup c_test_groups[] = {
    { "final_approach_context", final_approach_context_cases, final_approach_context_cases_expected, COUNT(final_approach_context_cases), 0 },
    { "final_cutscene_approach", 0, 0, 1, test_final_cutscene_approach },
    { "final_cutscene_finish", 0, 0, 2, test_final_cutscene_finish },
    { "final_cutscene_leave", 0, 0, 2, test_final_cutscene_leave },
    { "final_cutscene_rise", 0, 0, 2, test_final_cutscene_rise },
    { "final_cutscene_start_effect", 0, 0, 2, test_final_cutscene_start_effect },
    { "final_cutscene_wait_effect", 0, 0, 3, test_final_cutscene_wait_effect },
    { "final_cutscene_wait_fade", 0, 0, 2, test_final_cutscene_wait_fade },
    { "func_800D2CA4", 0, 0, 3, test_func_800D2CA4 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(final_approach_context_cases) + 1 + 2 + 2 + 2 + 2 + 3 + 2 + 3;
