#include "test_runtime.h"
#include "main/mains/main_56_jet_stingray.h"
#include "main/visuals/visual_23_jet_stingray_fx.h"
#include "main/55C4.h"

#ifndef VERSION_DEMO
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
    obj.unk15 = mode == 1 ? PLAYER_FACING_RIGHT : 0;
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
    before.unk42 = mode == 3 ? VISUAL_STAGE_PALETTE(1) : 0x0123;
    before.unk17 = animation;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = jet_stingray_animations[animation];
    memcpy(&before.animation_step, jet_stingray_animations[animation], sizeof(before.animation_step));
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.state | ((u32)obj.unk17 << 8) | ((u32)(u16)obj.x_pos.i.hi << 16);
}
static const u32 jet_stingray_fx_animation_start_cases_expected[] = { 0x311301u, 0x971301u, 0x641E01u, 0x642B01u };

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
    obj.unk15 = mode == 1 ? PLAYER_FACING_RIGHT : 0;
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
static const u32 jet_stingray_fx_raw_default_cases_expected[] = { 0x640001u };
#endif

static const u32 jet_stingray_fx_vortex_expected[] = { DEMO_ALT(2u, 0u), 0xFFFFFFFFu };
static u32 test_jet_stingray_fx_vortex(u32 row)
{
    u32 observed_values[2];
    struct VisualObj obj;
    struct MainObj child_0;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    obj.unk5 = -1;
    child_0.state = 2;
    obj.unk50 = &child_0;
    jet_stingray_fx_vortex(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, jet_stingray_fx_vortex_expected, 2);
}

#ifndef VERSION_DEMO
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

          jet_stingray_fx_splash_7,
      };
static const u32 jet_stingray_fx_splash_owner_cases_expected[] = { 0x6502u };
#define INIT_SPLASH_CASES (COUNT(jet_stingray_fx_animation_start_cases_expected) + COUNT(jet_stingray_fx_raw_default_cases_expected) + COUNT(jet_stingray_fx_splash_owner_cases))
#else
#define INIT_SPLASH_CASES 0
#endif


#include "support/state_cases.h"
static struct MainObj jfx_owner;
#define jv state_room.visual
#define JFX(kind, step, ended, setup) (state_reset(step, 0, 0), memset(&jfx_owner, 0, sizeof(jfx_owner)), jfx_owner.state = 1, jv.active = 1, jv.state = 1, jv.unk2 = kind, jv.unk50 = (struct PlayerObj*)&jfx_owner, jv.animation_step.fields.relative_step = (ended) ? 0 : 1, setup, jet_stingray_fx_update(&jv), state_extra = jv.unk17, jv.unk50 = NULL)
static void jfx_vortex_forms(void) { JFX(0, 0, 1, 0); }
static void jfx_vortex_forming(void) { JFX(0, 0, 0, 0); }
static void jfx_vortex_fades(void) { JFX(0, 2, 1, 0); }
static void jfx_vortex_fading(void) { JFX(0, 2, 0, 0); }
static void jfx_vortex_waits(void) { JFX(0, 1, 0, 0); }
static void jfx_vortex_turns(void) { JFX(0, 1, 0, jfx_owner.ext.main_56.vortex_result = 1); }
#ifndef VERSION_DEMO
static void jfx_splash_rises(void) { JFX(1, 0, 1, 0); }
static void jfx_splash_rising(void) { JFX(1, 0, 0, 0); }
static void jfx_splash_ends(void) { JFX(1, 1, 1, 0); }
static void jfx_splash_falling(void) { JFX(1, 1, 0, 0); }
static void jfx_oneshot_ends(void) { JFX(2, 0, 1, 0); }
static void jfx_oneshot_plays(void) { JFX(2, 0, 0, 0); }
#endif
static void (*const jfx_cases[])(void) = {
    jfx_vortex_forms,
    jfx_vortex_forming,
    jfx_vortex_fades,
    jfx_vortex_fading,
    jfx_vortex_waits,
    jfx_vortex_turns,
#ifndef VERSION_DEMO
    jfx_splash_rises,
    jfx_splash_rising,
    jfx_splash_ends,
    jfx_splash_falling,
    jfx_oneshot_ends,
    jfx_oneshot_plays,
#endif
};
#define JFX_STEP DEMO_ALT(0x50000u, 0x40000u)
static const u32 jfx_expected[] = {
    0x101u, 0xFF000001u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, JFX_STEP, 0x14u, 0x0u,
    0x1u, 0x1u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x202u, 0x1u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x201u, 0x1u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x101u, 0x1u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x201u, 0xFF000001u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, JFX_STEP, 0x15u, 0x0u,
#ifndef VERSION_DEMO
    0x101u, 0xFF000101u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x20u, 0x0u,
    0x1u, 0x101u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x102u, 0x101u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x101u, 0x101u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x2u, 0x201u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x1u, 0x201u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
#endif
};
static u32 test_jfx(u32 row)
{
    return object_run(jfx_cases[row], row, &jfx_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
#ifndef VERSION_DEMO
    { "jet_stingray_fx_animation_start", NULL, jet_stingray_fx_animation_start_cases_expected, COUNT(jet_stingray_fx_animation_start_cases_expected), jet_stingray_fx_animation_start_start_case },
    { "jet_stingray_fx_raw_default", NULL, jet_stingray_fx_raw_default_cases_expected, COUNT(jet_stingray_fx_raw_default_cases_expected), jet_stingray_fx_raw_default_start_case },
#endif
    { "jet_stingray_fx_vortex", 0, 0, 1, test_jet_stingray_fx_vortex },
#ifndef VERSION_DEMO
    { "jet_stingray_fx_splash_owner", jet_stingray_fx_splash_owner_cases, jet_stingray_fx_splash_owner_cases_expected, COUNT(jet_stingray_fx_splash_owner_cases), 0 },
#endif

    { "jet_stingray_fx_steps", 0, 0, COUNT(jfx_cases), test_jfx },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = INIT_SPLASH_CASES + 1 + COUNT(jfx_cases);
