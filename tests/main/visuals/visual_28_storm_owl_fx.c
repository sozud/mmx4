#include "test_runtime.h"
#include "main/visuals/visual_28_storm_owl_fx.h"
#include "main/55C4.h"
#include "main/mains/main_60_storm_owl.h"

static u32 storm_owl_fx_raw_modes_start_case(u32 mode)
{
    struct VisualObj obj, before;
    struct MainObj owner, owner_before;
    struct PlayerObj player_before = g_Player;
    u32 i, subtype = mode == 0 ? 4 : 1, animation = subtype == 0 ? 10 : subtype == 1 ? 26
        : subtype == 2                                                               ? 25
                                                                                     : 14;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    obj.active = 0x41;
    obj.id = 28;
    obj.state = 0;
    obj.unk2 = subtype;
    obj.unk42 = 0x8123;
    obj.unk54 = 0x27;
    obj.unk5C.fields.mode = mode == 0 ? 0 : -1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)storm_owl_animations;
    set_animation(&obj, 0);
    owner.active = 0x41;
    owner.id = 60;
    owner.state = 1;
    owner.unk15 = mode & 1 ? 0x40 : 0;
    owner.ext.main_60.storm_active = 0x28;
    obj.unk50 = (struct PlayerObj*)&owner;
    before = obj;
    owner_before = owner;
    storm_owl_fx_init(&obj);
    before.state = 1;
    before.on_screen = 1;
    before.unk15 = owner.unk15;
    before.unk42 = 0x0123;
    before.unk5C.value = 0;
    if (subtype == 0)
        before.unk54 = 9;

    if (subtype == 2)
        owner_before.ext.main_60.storm_active = 2;
    if (subtype == 1) {
        before.unk17 = animation;
        before.previous_animation_index = 0xFF;
        before.animation_cursor = storm_owl_animations[animation];
        before.animation_step = *(union AnimationStep*)storm_owl_animations[animation];
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.state | ((u32)obj.unk17 << 8) | ((u32)(u16)obj.unk54 << 16);
}
#define CASE(m)                                       \
    static u32 storm_owl_fx_raw_modes_start_##m(void) \
    {                                                 \
        return storm_owl_fx_raw_modes_start_case(m);  \
    }
CASE(0)
CASE(1)
#define ENTRY(m) storm_owl_fx_raw_modes_start_##m,
static const CTestCase storm_owl_fx_raw_modes_cases[]
    = { ENTRY(0) ENTRY(1) };
static const u32 storm_owl_fx_raw_modes_cases_expected[] = { 0x270001u, 0x271A01u };
#undef CASE
#undef ENTRY

static u32 storm_owl_fx_start_modes_start_case(u32 mode)
{
    struct VisualObj obj, before;
    struct MainObj owner, owner_before;
    struct PlayerObj player_before = g_Player;
    u32 i, subtype = mode < 4 ? 1 : mode - 4, animation = subtype == 0 ? 10 : subtype == 1 ? 26
        : subtype == 2                                                                     ? 25
                                                                                           : 14;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    obj.active = 0x41;
    obj.id = 28;
    obj.state = 0;
    obj.unk2 = subtype;
    obj.unk42 = 0x8123;
    obj.unk54 = 0x27;
    obj.unk5C.fields.mode = mode < 4 ? mode : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)storm_owl_animations;
    set_animation(&obj, 0);
    owner.active = 0x41;
    owner.id = 60;
    owner.state = 1;
    owner.unk15 = mode & 1 ? 0x40 : 0;
    owner.ext.main_60.storm_active = 0x28;
    obj.unk50 = (struct PlayerObj*)&owner;
    before = obj;
    owner_before = owner;
    storm_owl_fx_init(&obj);
    before.state = 1;
    before.on_screen = 1;
    before.unk15 = owner.unk15;
    before.unk42 = 0x0123;
    before.unk5C.value = 0;
    if (subtype == 0)
        before.unk54 = 9;
    else if (subtype == 1 && mode < 3)
        before.unk54 = 40;
    if (subtype == 2)
        owner_before.ext.main_60.storm_active = 2;
    before.unk17 = animation;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = storm_owl_animations[animation];
    before.animation_step = *(union AnimationStep*)storm_owl_animations[animation];
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.state | ((u32)obj.unk17 << 8) | ((u32)(u16)obj.unk54 << 16);
}
#define CASE(m)                                         \
    static u32 storm_owl_fx_start_modes_start_##m(void) \
    {                                                   \
        return storm_owl_fx_start_modes_start_case(m);  \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(6)
CASE(7)
#define ENTRY(m) storm_owl_fx_start_modes_start_##m,
static const CTestCase storm_owl_fx_start_modes_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(6) ENTRY(7) };
static const u32 storm_owl_fx_start_modes_cases_expected[] = { 0x281A01u, 0x281A01u, 0x281A01u, 0x271A01u, 0x90A01u, 0x271901u, 0x270E01u };
#undef CASE
#undef ENTRY

static const u32 storm_owl_fx_init_expected[] = { 0u, 1u, 1u, 0u, 0u, 0u, 0u };
static u32 test_storm_owl_fx_init(u32 row)
{
    u32 observed_values[7];
    struct VisualObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    child_0_present = 255;
    obj.unk2 = -1;
    obj.unk50 = child_0_present ? &child_0 : NULL;
    storm_owl_fx_init(&obj);
    observed_values[0] = (u32)child_0.ext.main_60.storm_active;
    observed_values[1] = (u32)obj.on_screen;
    observed_values[2] = (u32)obj.state;
    observed_values[3] = (u32)obj.unk15;
    observed_values[4] = (u32)obj.unk42;
    observed_values[5] = (u32)obj.unk54;
    observed_values[6] = (u32)obj.unk5C.value;
    return c_test_observe(0, row, observed_values, storm_owl_fx_init_expected, 7);
}

static const u32 inputs_0[2][12] = {
    { 255, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0 },
    { 255, 1, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0 },
};
struct storm_owl_fx_main_case {
    u32 expected[5];
};
static const struct storm_owl_fx_main_case storm_owl_fx_main_cases[] = {
    { { 1u, 0xFFFFFFFFu, 0u, 0u, 0u } },
    { { 2u, 0u, 0xFFFFFFFFu, 0u, 0u } },
};
static u32 test_storm_owl_fx_main(u32 row)
{
    const struct storm_owl_fx_main_case* c = &storm_owl_fx_main_cases[row];
    u32 observed_values[5];
    struct VisualObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&background_objects, 0, sizeof(background_objects));
    child_0_present = inputs_0[row][0];
    obj.unk2 = inputs_0[row][1];
    child_0.ext.main_60.storm_active = inputs_0[row][2];
    obj.state = inputs_0[row][3];
    child_0.x_pos.val = inputs_0[row][4];
    child_0.y_pos.val = inputs_0[row][5];
    child_0.ext.main_60.flash_mode = inputs_0[row][6];
    obj.unk54 = inputs_0[row][7];
    obj.unk5C.value = inputs_0[row][8];
    child_0.active = inputs_0[row][9];
    child_0.state = inputs_0[row][10];
    child_0.unk5 = inputs_0[row][11];
    obj.unk50 = child_0_present ? &child_0 : NULL;
    storm_owl_fx_main(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk54;
    observed_values[2] = (u32)obj.unk5C.value;
    observed_values[3] = (u32)obj.x_pos.val;
    observed_values[4] = (u32)obj.y_pos.val;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

const struct CTestGroup c_test_groups[] = {
    { "storm_owl_fx_raw_modes", storm_owl_fx_raw_modes_cases, storm_owl_fx_raw_modes_cases_expected, COUNT(storm_owl_fx_raw_modes_cases), 0 },
    { "storm_owl_fx_start_modes", storm_owl_fx_start_modes_cases, storm_owl_fx_start_modes_cases_expected, COUNT(storm_owl_fx_start_modes_cases), 0 },
    { "storm_owl_fx_init", 0, 0, 1, test_storm_owl_fx_init },
    { "storm_owl_fx_main", 0, 0, 2, test_storm_owl_fx_main },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(storm_owl_fx_raw_modes_cases) + COUNT(storm_owl_fx_start_modes_cases) + 1 + 2;
