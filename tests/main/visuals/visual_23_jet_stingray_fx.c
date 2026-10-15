#include "test_runtime.h"

static u32 jet_stingray_fx_animation_start_start_case(u32 mode)
{
    struct VisualObj obj, before;
    struct EngineObj engine_before;
    struct PlayerObj player_before = g_Player;
    u32 i, animation = mode < 2 ? 19 : mode == 2 ? 30
                                                 : 43;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    obj.active = 0x41;
    obj.id = 23;
    obj.state = 0;
    obj.unk2 = mode < 2 ? 0 : mode - 1;
    obj.unk15 = mode == 1 ? 0x40 : 0;
    obj.unk5C.value = 0x27;
    obj.unk42 = 0x8123;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)jet_stingray_animations;
    set_animation(&obj, 0);
    engine_obj.stage = 5;
    engine_obj.substage = 1;
    before = obj;
    engine_before = engine_obj;
    jet_stingray_fx_init(&obj);
    before.state = 1;
    if (mode < 2) {
        before.unk5C.value = 0;
        before.x_pos.i.hi += mode == 1 ? 51 : -51;
        before.y_pos.i.hi -= 4;
    }
    before.unk42 = mode == 3 ? 0x784C : 0x0123;
    before.unk17 = animation;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = jet_stingray_animations[animation];
    before.animation_step = *(union AnimationStep*)jet_stingray_animations[animation];
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.state | ((u32)obj.unk17 << 8) | ((u32)(u16)obj.x_pos.i.hi << 16);
}
#define CASE(m)                                                \
    static u32 jet_stingray_fx_animation_start_start_##m(void) \
    {                                                          \
        return jet_stingray_fx_animation_start_start_case(m);  \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
#define ENTRY(m) jet_stingray_fx_animation_start_start_##m,
static const CTestCase jet_stingray_fx_animation_start_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) };
static const u32 jet_stingray_fx_animation_start_cases_expected[] = { 0x311301u, 0x971301u, 0x641E01u, 0x642B01u };
#undef CASE
#undef ENTRY

static u32 jet_stingray_fx_raw_default_start_case(u32 mode)
{
    struct VisualObj obj, before;
    struct EngineObj engine_before;
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    obj.active = 0x41;
    obj.id = 23;
    obj.state = 0;
    obj.unk2 = 3;
    obj.unk15 = mode == 1 ? 0x40 : 0;
    obj.unk5C.value = 0x27;
    obj.unk42 = 0x8123;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)jet_stingray_animations;
    set_animation(&obj, 0);
    engine_obj.stage = 5;
    engine_obj.substage = 1;
    before = obj;
    engine_before = engine_obj;
    jet_stingray_fx_init(&obj);
    before.state = 1;
    before.unk42 = mode == 3 ? 0x784C : 0x0123;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.state | ((u32)obj.unk17 << 8) | ((u32)(u16)obj.x_pos.i.hi << 16);
}
#define CASE(m)                                            \
    static u32 jet_stingray_fx_raw_default_start_##m(void) \
    {                                                      \
        return jet_stingray_fx_raw_default_start_case(m);  \
    }
CASE(0)
#define ENTRY(m) jet_stingray_fx_raw_default_start_##m,
static const CTestCase jet_stingray_fx_raw_default_cases[] = { ENTRY(0) };
static const u32 jet_stingray_fx_raw_default_cases_expected[] = { 0x640001u };
#undef CASE
#undef ENTRY

static const u32 jet_stingray_fx_init_expected[] = { 1u, 0u, 0u, 0u, 0u };
static u32 test_jet_stingray_fx_init(u32 row)
{
    u32 observed_values[5];
    struct VisualObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    obj.unk2 = -1;
    jet_stingray_fx_init(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk42;
    observed_values[2] = (u32)obj.unk5C.value;
    observed_values[3] = (u32)obj.x_pos.i.hi;
    observed_values[4] = (u32)obj.y_pos.i.hi;
    return c_test_observe(0, row, observed_values, jet_stingray_fx_init_expected, 5);
}

static const u32 jet_stingray_fx_splash_expected[] = { 2u, 0xFFFFFFFFu };
static u32 test_jet_stingray_fx_splash(u32 row)
{
    u32 observed_values[2];
    struct VisualObj obj;
    struct PlayerObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    child_0_present = 255;
    obj.unk5 = -1;
    child_0.state = 2;
    obj.unk50 = child_0_present ? &child_0 : NULL;
    jet_stingray_fx_splash(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, jet_stingray_fx_splash_expected, 2);
}

static const u32 jet_stingray_fx_vortex_expected[] = { 2u, 0xFFFFFFFFu };
static u32 test_jet_stingray_fx_vortex(u32 row)
{
    u32 observed_values[2];
    struct VisualObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    child_0_present = 255;
    obj.unk5 = -1;
    child_0.state = 2;
    obj.unk50 = child_0_present ? &child_0 : NULL;
    jet_stingray_fx_vortex(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, jet_stingray_fx_vortex_expected, 2);
}

static u32 jet_stingray_fx_splash_case(u32 mode)
{
    struct MainObj owner, owner_before;
    struct VisualObj visual, visual_before;
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&owner, 0, sizeof(owner));
    memset(&visual, 0, sizeof(visual));
    owner.state = mode == 7 ? 2 : 1;
    owner_before = owner;
    visual.active = 0x41;
    visual.id = 23;
    visual.state = 1;
    visual.unk5 = 2;
    visual.x_pos.val = 100 * 65536 + 0x1234;
    visual.y_pos.val = 200 * 65536 + 0x5678;
    visual.x_vel.val = 65536;
    visual.y_vel.val = 2 * 65536;
    visual.unk50 = PLAYER_OBJECT(&owner);
    visual.animation_table = (const u8* const*)jet_stingray_animations;
    set_animation(&visual, 0);
    visual_before = visual;
    visual_before.x_pos.val += 65536;
    visual_before.y_pos.val -= 2 * 65536;
    if (mode == 7)
        visual_before.state = 2;
    jet_stingray_fx_splash(&visual);
    for (i = 0; i < sizeof(visual) / 4; i++)
        assert(((u32*)&visual)[i] == ((u32*)&visual_before)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)visual.state | ((u32)(u16)visual.x_pos.i.hi << 8);
}
#define CASE(m)                                 \
    static u32 jet_stingray_fx_splash_##m(void) \
    {                                           \
        return jet_stingray_fx_splash_case(m);  \
    }
CASE(6)
CASE(7)
#undef CASE
static const CTestCase jet_stingray_fx_splash_owner_cases[]
    = {
          jet_stingray_fx_splash_6,
          jet_stingray_fx_splash_7,
      };
static const u32 jet_stingray_fx_splash_owner_cases_expected[] = { 0x6501u, 0x6502u };

#include "support/jet_stingray_animation_wait.h"
JET_WAIT_CASE(1, 0)
JET_WAIT_CASE(1, 1)
JET_WAIT_CASE(3, 0)
JET_WAIT_CASE(3, 1)
static const CTestCase jet_stingray_fx_vortex_wait_cases[] = { JET_WAIT_ENTRY(1, 0) JET_WAIT_ENTRY(1, 1) JET_WAIT_ENTRY(3, 0) JET_WAIT_ENTRY(3, 1) };

static const u32 jet_stingray_fx_vortex_wait_cases_expected[] = { 0x4D010003u, 0x102u, 0x10009u, 0x103u };
const struct CTestGroup c_test_groups[] = {
    { "jet_stingray_fx_animation_start", jet_stingray_fx_animation_start_cases, jet_stingray_fx_animation_start_cases_expected, COUNT(jet_stingray_fx_animation_start_cases), 0 },
    { "jet_stingray_fx_raw_default", jet_stingray_fx_raw_default_cases, jet_stingray_fx_raw_default_cases_expected, COUNT(jet_stingray_fx_raw_default_cases), 0 },
    { "jet_stingray_fx_init", 0, 0, 1, test_jet_stingray_fx_init },
    { "jet_stingray_fx_splash", 0, 0, 1, test_jet_stingray_fx_splash },
    { "jet_stingray_fx_vortex", 0, 0, 1, test_jet_stingray_fx_vortex },
    { "jet_stingray_fx_splash_owner", jet_stingray_fx_splash_owner_cases, jet_stingray_fx_splash_owner_cases_expected, COUNT(jet_stingray_fx_splash_owner_cases), 0 },
    { "jet_stingray_fx_vortex_wait", jet_stingray_fx_vortex_wait_cases, jet_stingray_fx_vortex_wait_cases_expected, COUNT(jet_stingray_fx_vortex_wait_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(jet_stingray_fx_animation_start_cases) + COUNT(jet_stingray_fx_raw_default_cases) + 1 + 1 + 1 + COUNT(jet_stingray_fx_splash_owner_cases) + COUNT(jet_stingray_fx_vortex_wait_cases);
