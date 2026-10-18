#include "test_runtime.h"
#include "main/misc/misc_28_select_a_character.h"

static u32 select_case(u32 mode, u32 observation)
{
    static const u8 subtypes[4] = { 7, 8, 9, 12 };
    struct MiscObj obj, before;
    s32 archive[128];
    u32 resources[3] = { 0x10000, 0x18000, 0x20000 };
    u32 i, subtype = subtypes[mode], animation, resource;
    u32** table;
    memset(&obj, 0, sizeof(obj));
    memset(archive, 0, sizeof(archive));
    archive[0] = 64;
    archive[1] = 128;
    archive[2] = 192;
    TEST_MENU_FRAMES = (u8*)archive;
    D_801406A8 = resources;
    obj.active = 0x41;
    obj.id = 28;
    obj.state = 0;
    obj.unk2 = subtype;
    obj.unk15 = 0x27;
    obj.unk6 = 0x25;
    obj.unk7 = 0x26;
    obj.unk5 = 0x24;
    obj.unk16 = 0x28;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = 65536;
    obj.y_vel.val = -65536;
    obj.ext.title_logo.palette_shift_speed = 7;
    obj.ext.title_logo.unk57 = 8;
    before = obj;
    select_char_init(&obj);
    if (mode == 1) {
        table = select_char_zero_animations;
        resource = 0;
        before.unk42 = 0x7800;
        before.unk15 = 0;
    } else if (mode == 3) {
        table = select_char_menu_animations;
        resource = 1;
        before.unk42 = 0x7808;
    } else {
        table = select_char_x_animations;
        resource = 2;
        before.unk42 = 0x7840;
        before.unk15 = 0x40;
    }
    animation = select_char_initial_animations[subtype];
    before.unk40 = resources[resource] >> 7;
    before.unk3C = (u8*)archive + archive[resource];
    before.animation_table = table;
    before.animation_cursor = table[animation];
    before.animation_step.packed = *table[animation];
    before.unk17 = animation;
    before.previous_animation_index = 0xFF;
    if (mode < 2) {
        before.x_pos.val = select_char_positions[subtype].x * 65536;
        before.y_pos.val = select_char_positions[subtype].y * 65536;
    }
    if (mode == 3) {
        before.x_pos.val = select_char_text_positions[0].x * 65536;
        before.y_pos.val = select_char_text_positions[0].y * 65536;
    }
    before.unk16 = select_char_priorities[subtype];
    before.bg_offset = -1;
    before.x_vel.val = before.y_vel.val = 0;
    before.ext.title_logo.palette_shift_speed = before.ext.title_logo.unk57 = before.unk6 = before.unk7 = 0;
    before.state = 1;
    before.unk5 = subtype;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    assert(resources[0] == 0x10000 && resources[1] == 0x18000 && resources[2] == 0x20000);
    for (i = 0; i < 128; i++)
        assert(archive[i] == (i < 3 ? (s32)(64 + i * 64) : 0));
    return observation == 0 ? (u16)obj.x_pos.i.hi | ((u32)(u16)obj.y_pos.i.hi << 16) : obj.animation_step.packed;
}
#define CASE(m, n)                                                  \
    static u32 select_character_text_context_select_##m##_##n(void) \
    {                                                               \
        return select_case(m, n);                                   \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1)
MODE(0)
MODE(1)
MODE(2)
MODE(3)
#define ENTRY(m, n) select_character_text_context_select_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1)
static const CTestCase select_character_text_context_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) ENTRIES(3) };
static const u32 select_character_text_context_cases_expected[] = { 0xA00020u, 0x8u, 0xA00120u, 0x1u, 0xC80064u, 0xF010103u, 0x38FF40u, 0x5000001u };
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

struct select_char_portrait_bounce_0_case {
    u32 unk7, blast_timer;
    u32 expected[4];
};
static const struct select_char_portrait_bounce_0_case select_char_portrait_bounce_0_cases[] = {
    { -1, 0, { 0u, 0u, 0xFFFFFFFFu, 0u } },
    { 2, 0, { 0xFFu, 0u, 2u, 0u } },
    { 2, 1, { 0u, 0u, 3u, 0xFFF00000u } },
};
static u32 test_select_char_portrait_bounce_0(u32 row)
{
    const struct select_char_portrait_bounce_0_case* c = &select_char_portrait_bounce_0_cases[row];
    u32 observed_values[4];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk7 = c->unk7;
    obj.ext.sel_char.blast_timer = c->blast_timer;
    select_char_portrait_bounce(&obj);
    observed_values[0] = (u32)obj.ext.sel_char.blast_timer;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk7;
    observed_values[3] = (u32)obj.x_vel.val;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

struct select_char_portrait_bounce_1_case {
    u32 unk7, on_screen, blast_timer, hi;
    u32 expected[4];
};
static const struct select_char_portrait_bounce_1_case select_char_portrait_bounce_1_cases[] = {
    { -1, 0, 0, 0, { 0u, 0u, 0xFFFFFFFFu, 0u } },
    { 2, 0, 0, 0, { 0xFFu, 0u, 2u, 0u } },
    { 2, 0, 1, 0, { 0u, 0u, 3u, 0xFFF00000u } },
    { 1, -1, 0, 0, { 0u, 0u, 1u, 0u } },
    { 3, 0, 0, 0, { 0u, 0u, 3u, 0u } },
    { 3, 0, 0, 224, { 0u, 1u, 0u, 0u } },
    { 0, 0, 0, 0, { 0x14u, 0u, 1u, 0x100000u } },
};
static u32 test_select_char_portrait_bounce_1(u32 row)
{
    const struct select_char_portrait_bounce_1_case* c = &select_char_portrait_bounce_1_cases[row];
    u32 observed_values[4];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk7 = c->unk7;
    obj.on_screen = c->on_screen;
    obj.ext.sel_char.blast_timer = c->blast_timer;
    obj.x_pos.i.hi = c->hi;
    select_char_portrait_bounce(&obj);
    observed_values[0] = (u32)obj.ext.sel_char.blast_timer;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk7;
    observed_values[3] = (u32)obj.x_vel.val;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

static const u32 select_char_scroll_text_init_expected[] = { 1u, 0u };
static u32 test_select_char_scroll_text_init(u32 row)
{
    u32 observed_values[2];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    select_char_scroll_text_init(&obj);
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.x_vel.val;
    return c_test_observe(0, row, observed_values, select_char_scroll_text_init_expected, 2);
}

struct select_char_scroll_text_move_case {
    u32 unk2, hi;
    u32 expected[2];
};
static const struct select_char_scroll_text_move_case select_char_scroll_text_move_cases[] = {
    { 12, 0, { 0u, 0u } },
    { 0, 0, { 0u, 0u } },
    { 12, 126, { 0x7Eu, 0u } },
};
static u32 test_select_char_scroll_text_move(u32 row)
{
    const struct select_char_scroll_text_move_case* c = &select_char_scroll_text_move_cases[row];
    u32 observed_values[2];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk2 = c->unk2;
    obj.x_pos.i.hi = c->hi;
    select_char_scroll_text_move(&obj);
    observed_values[0] = (u32)obj.x_pos.i.hi;
    observed_values[1] = (u32)obj.x_vel.val;
    return c_test_observe(0, row, observed_values, c->expected, 2);
}

#include "support/pool_full.h"
static u32 pool_full_select_char_character_shoot(void)
{
    u32 actual;
    pf_prepare();
    pf_misc.animation_step.fields.event = 1;
    pf_snapshot();
    select_char_character_shoot(&pf_misc);
    pf_misc_expected.animation_step.fields.event = 0;
    pf_misc_expected.animation_step.fields.duration--;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_select_char_shot_burst(void)
{
    u32 actual;
    pf_prepare();
    pf_misc.animation_step.fields.event = 1;
    pf_snapshot();
    select_char_shot_burst(&pf_misc);
    pf_misc_expected.animation_step.fields.event = 0;
    pf_misc_expected.animation_step.fields.duration--;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_select_char_character_shoot,
    pool_full_select_char_shot_burst,
};

static const u32 pool_full_cases_expected[] = { 0x50000u, 0x50000u };
const struct CTestGroup c_test_groups[] = {
    { "select_character_text_context", select_character_text_context_cases, select_character_text_context_cases_expected, COUNT(select_character_text_context_cases), 0 },
    { "select_char_portrait_bounce_0", 0, 0, 3, test_select_char_portrait_bounce_0 },
    { "select_char_portrait_bounce_1", 0, 0, 7, test_select_char_portrait_bounce_1 },
    { "select_char_scroll_text_init", 0, 0, 1, test_select_char_scroll_text_init },
    { "select_char_scroll_text_move", 0, 0, 3, test_select_char_scroll_text_move },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(select_character_text_context_cases) + 3 + 7 + 1 + 3 + COUNT(pool_full_cases);
