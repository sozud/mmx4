#include "test_runtime.h"
#include "main/visuals/visual_28_storm_owl_fx.h"
#include "main/55C4.h"
#include "main/mains/main_60_storm_owl.h"
#include "support/state_cases.h"

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
static const u32 storm_owl_fx_raw_modes_cases_expected[] = { 0x270001u, 0x271A01u };

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

static struct MainObj owl_fx_owner;
#define sv state_room.visual
#define OFX(kind, timer, phase, setup) (state_reset(0, 0, 0), memset(&owl_fx_owner, 0, sizeof(owl_fx_owner)), owl_fx_owner.x_pos.i.hi = 0x90, sv.active = 1, sv.state = 1, sv.unk2 = kind, sv.unk54 = timer, sv.unk5C.value = phase, sv.unk50 = (struct PlayerObj*)&owl_fx_owner, sv.x_pos.i.hi = 0x80, sv.y_pos.i.hi = 0x60, setup, storm_owl_fx_main(&sv), state_extra = sv.unk54 | sv.unk5C.value << 8)
static void sox_flash_wait(void)
{
    OFX(0, 2, 0, 0);
}
static void sox_flash_end(void) { OFX(0, 1, 0, 0); }
static void sox_bolt_grow(void) { OFX(1, 1, 0, 0); }
static void sox_bolt_hold(void) { OFX(1, 1, 1, 0); }
static void sox_bolt_fade(void) { OFX(1, 1, 2, 0); }
static void sox_bolt_end(void) { OFX(1, 1, 3, 0); }
static void sox_storm_on(void) { OFX(2, 1, 0, owl_fx_owner.ext.main_60.storm_active = 1); }
static void sox_storm_off(void) { OFX(2, 1, 0, 0); }
static void sox_glow_on(void) { OFX(3, 1, 0, owl_fx_owner.ext.main_60.flash_mode = 1); }
static void sox_glow_off(void) { OFX(3, 1, 0, 0); }

static void (*const storm_owl_fx_main_states_cases[])(void) = {
    sox_flash_wait,
    sox_flash_end,
    sox_bolt_grow,
    sox_bolt_hold,
    sox_bolt_fade,
    sox_bolt_end,
    sox_storm_on,
    sox_storm_off,
    sox_glow_on,
    sox_glow_off,
};
static const u32 storm_owl_fx_main_states_expected[] = { 2u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 1u, 0u, 3u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 2u, 0xFF000101u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x10Cu, 0u, 2u, 0xFF000101u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x23Eu, 0u, 2u, 0xFF000101u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x30Cu, 0u, 3u, 0x101u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x300u, 0u, 2u, 0x201u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 1u, 0u, 2u, 0x201u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 1u, 0u, 2u, 0x301u, 0x900000u, 0u, 0u, 0u, 0u, 0x40000u, 1u, 0u, 2u, 0x301u, 0x900000u, 0u, 0u, 0u, 0u, 0x40000u, 1u, 0u };

static u32 test_storm_owl_fx_main_states(u32 row)
{
    return object_run(storm_owl_fx_main_states_cases[row], row, &storm_owl_fx_main_states_expected[row * 10]);
}

static const u8 animations[] = { 10, 26, 25, 14 };
static const u32 words[] = { 0x62010002, 0xA8010002, 0x45010001, 0x3F010001 };
static const u32 next_words[] = { 0x62010001, 0xA8010001, 0x44010001, 0x40010001 };
static u32 lifetime(u32 row)
{
    struct VisualObj obj, expected;
    struct MainObj owner, owner_before;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 type = row % 4, end = row / 4 % 4, offscreen = row / 16;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 0x41;
    obj.id = 28;
    obj.state = 1;
    obj.unk2 = type;
    obj.unk54 = 5;
    obj.on_screen = 0;
    obj.x_pos.val = (offscreen ? 1000 : 100) * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    owner.active = end == 1 ? 0 : 0x41;
    owner.id = 60;
    owner.state = end == 2 ? 2 : 1;
    owner.unk5 = end == 3 ? 11 : 5;
    owner.x_pos.val = obj.x_pos.val + 7 * 65536;
    owner.y_pos.val = obj.y_pos.val + 8 * 65536;
    owner.ext.main_60.storm_active = 2;
    owner.ext.main_60.flash_mode = 1;
    obj.unk50 = PLAYER_OBJECT(&owner);
    obj.animation_table = (u32**)storm_owl_animations;
    set_animation(&obj, animations[type]);
    assert(obj.animation_step.packed == words[type]);
    expected = obj;
    owner_before = owner;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    expected.animation_step.packed = next_words[type];
    if (type >= 2)
        expected.animation_cursor++;
    if (type < 2)
        expected.unk54--;
    if (type == 3) {
        expected.x_pos.val = owner.x_pos.val;
        expected.y_pos.val = owner.y_pos.val;
    }
    if (end == 1 || end == 2 || (type == 2 && end == 3))
        expected.state = 2;
    else
        expected.on_screen = !offscreen;
    storm_owl_fx_main(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_before, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "storm_owl_fx_main_states", 0, 0, COUNT(storm_owl_fx_main_states_cases), test_storm_owl_fx_main_states },
    { "storm_owl_fx_raw_modes", NULL, storm_owl_fx_raw_modes_cases_expected, COUNT(storm_owl_fx_raw_modes_cases_expected), storm_owl_fx_raw_modes_start_case },
    { "storm_owl_fx_start_modes", storm_owl_fx_start_modes_cases, storm_owl_fx_start_modes_cases_expected, COUNT(storm_owl_fx_start_modes_cases), 0 },
    { "storm_effect_owner_death_and_storm_end", NULL, NULL, 32, lifetime },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(storm_owl_fx_main_states_cases) + COUNT(storm_owl_fx_raw_modes_cases_expected) + COUNT(storm_owl_fx_start_modes_cases) + 32;
