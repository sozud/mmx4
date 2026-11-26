#include "test_runtime.h"
#include "support/platform_fixture.h"
#include "main/misc/misc_29_title_logo.h"
#ifdef MMX4_SATURN
#include "saturn/game_low.h"
#endif

static u32 star_case(u32 mode)
{
    struct MiscObj obj, before, pool_before[64];
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(misc_objects, 0, sizeof(misc_objects));
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = 1;
        misc_objects[i].id = 0x27;
        misc_objects[i].state = 0x28;
    }
    if (mode >= 3)
        misc_objects[63].active = 0;
    obj.active = 0x41;
    obj.id = 29;
    obj.state = 2;
    obj.unk16 = VISUAL_SATURN_LAYER(0);
    obj.bg_offset = -1;
    obj.x_pos.val = 116 * 65536 + 0x1234;
    obj.y_pos.val = 72 * 65536;
    obj.x_vel.val = 0x1234;
    obj.y_vel.val = 0x5678;
    obj.ext.title_logo.palette_shift_value = mode == 0 ? 0x10 : 0;
    obj.ext.title_logo.palette_shift_speed = mode == 1 ? 2 : 0;
    obj.ext.title_logo.unk50 = mode == 4 ? &misc_objects[17] : NULL;
    before = obj;
    memcpy(pool_before, misc_objects, sizeof(pool_before));
    title_logo_star_fly(&obj);
    before.on_screen = 1;
    if (mode == 0) {
        before.x_pos.i.hi = 216;
        before.y_pos.i.hi = 72;
        before.unk16 = VISUAL_SATURN_LAYER(2);
        before.state = 3;
    } else {
        before.ext.title_logo.palette_shift_speed = mode == 1 ? 1 : 3;
        before.x_vel.val = 10 * 65536;
        before.y_vel.val = 0;
        before.x_pos.val += 10 * 65536;
        if (mode >= 3) {
            struct MiscObj* trail = &pool_before[63];
            trail->active = 1;
            trail->id = 29;
            trail->unk2 = 0x10;
            trail->x_pos.val = 116 * 65536 + 0x1234;
            trail->y_pos.val = 72 * 65536;
            before.ext.title_logo.unk50 = &misc_objects[63];
        }
    }
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(misc_objects, pool_before, sizeof(pool_before));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    return (u8)obj.state | ((u32)obj.ext.title_logo.palette_shift_speed << 8) | ((u32)(u16)obj.x_pos.i.hi << 16);
}
static const u32 title_logo_star_pool_cases_expected[] = { 0xD80003u, 0x7E0102u, 0x7E0302u, 0x7E0302u, 0x7E0302u };

static u32 hold_case(u32 despawn)
{
    struct MiscObj obj, before;
    struct BackgroundObj background_before[3];
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 0x41;
    obj.id = 29;
    obj.state = 3;
    obj.unk2 = despawn ? 1 : 0;
    obj.unk5 = 0x24;
    obj.unk6 = 0x25;
    obj.unk7 = 0x26;
    obj.bg_offset = 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    obj.on_screen = 7;
    obj.ext.title_logo.palette_shift_value = 0x27;
    before = obj;
    memcpy(background_before, background_objects, sizeof(background_before));
    title_logo_star_hold(&obj);
    if (despawn)
        memset(&before, 0, 8);
    else
        before.on_screen = 1;
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(background_objects, background_before, sizeof(background_before));
    return (u8)obj.active | ((u32)(u8)obj.state << 8) | ((u32)(u8)obj.on_screen << 16);
}
static const u32 title_star_hold_context_cases_expected[] = { 0x10341u, 0x0u };

#ifdef MMX4_SATURN
#define TEST_TITLE_TEXTURE SATURN_TITLE_TEXTURE
#else
#define TEST_TITLE_TEXTURE 0x600u
#endif
struct title_logo_init_case {
    u32 unk2;
    u32 expected[15];
};
static const struct title_logo_init_case title_logo_init_cases[] = {
    { 16, { 0x1Cu, 0xFFFFFFFFu, 6u, 4u, 0u, 1u, 0x10u, TEST_TITLE_TEXTURE, OBJECT_CLUT(0x7804), 0u, 0u, 0u, 0u, 0u, 0u } },
    { 0, { 0x1Cu, 0xFFFFFFFFu, 0x1Eu, 1u, 0u, 0u, 0u, TEST_TITLE_TEXTURE, OBJECT_CLUT(0x7804), 0u, 0u, 0x80000u, 0xF0u, 0xF00000u, 0x60000u } },
    { 70, { 0x1Cu, 0xFFFFFFFFu, 0u, 3u, 0u, 0u, 0u, TEST_TITLE_TEXTURE, OBJECT_CLUT(0x7804), 0xD8u, 0xD80000u, 0u, 0x48u, 0x480000u, 0u } },
};
static u32 test_title_logo_init(u32 row)
{
    const struct title_logo_init_case* c = &title_logo_init_cases[row];
    u32 observed_values[15];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk2 = c->unk2;
    title_logo_init(&obj);
    observed_values[0] = (u32)obj.animation_step.fields.frame_index;
    observed_values[1] = (u32)obj.bg_offset;
    observed_values[2] = (u32)obj.ext.title_logo.palette_shift_speed;
    observed_values[3] = (u32)obj.state;
    observed_values[4] = C_TEST_PSX_FACING(obj.unk15);
    observed_values[5] = TEST_PSX_LAYER(obj.unk16);
    observed_values[6] = (u32)obj.unk2;
    observed_values[7] = (u32)obj.unk40;
    observed_values[8] = (u32)obj.unk42;
    observed_values[9] = (u32)obj.x_pos.i.hi;
    observed_values[10] = (u32)obj.x_pos.val;
    observed_values[11] = (u32)obj.x_vel.val;
    observed_values[12] = (u32)obj.y_pos.i.hi;
    observed_values[13] = (u32)obj.y_pos.val;
    observed_values[14] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, c->expected, 15);
}

struct title_logo_star_delay_case {
    u32 palette_shift_speed;
    u32 expected[3];
};
static const struct title_logo_star_delay_case title_logo_star_delay_cases[] = {
    { 255, { 0xFEu, 0u, 0u } },
    { 0, { 3u, 0x1Eu, 1u } },
};
static u32 test_title_logo_star_delay(u32 row)
{
    const struct title_logo_star_delay_case* c = &title_logo_star_delay_cases[row];
    u32 observed_values[3];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.ext.title_logo.palette_shift_speed = c->palette_shift_speed;
    title_logo_star_delay(&obj);
    observed_values[0] = (u32)obj.ext.title_logo.palette_shift_speed;
    observed_values[1] = (u32)obj.ext.title_logo.palette_shift_value;
    observed_values[2] = (u32)obj.state;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

struct title_logo_trail_fade_case {
    u32 palette_shift_speed;
    u32 expected[1];
};
static const struct title_logo_trail_fade_case title_logo_trail_fade_cases[] = {
    { 0, { 0u } },
    { 255, { 0xFEu } },
};
static u32 test_title_logo_trail_fade(u32 row)
{
    const struct title_logo_trail_fade_case* c = &title_logo_trail_fade_cases[row];
    u32 observed_values[1];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.ext.title_logo.palette_shift_speed = c->palette_shift_speed;
    title_logo_trail_fade(&obj);
    observed_values[0] = (u32)obj.ext.title_logo.palette_shift_speed;
    return c_test_observe(0, row, observed_values, c->expected, 1);
}


#include "support/state_cases.h"
#define sm state_room.misc
#ifdef MMX4_SATURN
#define TITLE_PALETTE 0x10
#else
#define TITLE_PALETTE 0x7840
#endif
#if defined(VERSION_JP) || defined(VERSION_SATURN_PROTO)
#define TITLE_FADE_X 120u
#define TITLE_SPARKLE_X 216u
#define TITLE_PALETTE_WORDS 24u
#else
#define TITLE_FADE_X 144u
#define TITLE_SPARKLE_X 208u
#define TITLE_PALETTE_WORDS 16u
#endif
static u16 title_palette[0x200];
static s32 title_source[48], title_target[48];
#define TITLE(st, kind, setup) (state_reset(0, 0, 0), memset(title_palette, 0, sizeof(title_palette)), TEST_PALETTE = (u8*)title_palette, TEST_ARC_30 = (u8*)title_source, need_palette_load = 0, sm.active = 1, sm.state = st, sm.unk2 = kind, sm.x_pos.i.hi = 0x80, sm.y_pos.i.hi = 0x48, setup, TitleLogoUpdate(&sm), state_extra = sm.ext.title_logo.palette_shift_speed | (u32)sm.ext.title_logo.palette_shift_value << 8 | (sm.ext.title_logo.palette1 == NULL ? 0xFFu : (u32)(u8)(sm.ext.title_logo.palette1 - title_source)) << 16 | (u32)need_palette_load << 24)
static void tl_init_fade(void) { TITLE(0, 0x20, 0); }
static void tl_init_sparkle(void) { TITLE(0, 0x21, 0); }
static void tl_fade_ready(void)
{
    TITLE(5, 0, 0);
    assert(sm.ext.title_logo.palette2 == (s32*)(title_palette + 0x100));
#ifdef MMX4_SATURN
    assert(sm.ext.title_logo.palette1 == SATURN_TITLE_PALETTE);
#else
    assert(sm.ext.title_logo.palette1 == title_source);
#endif
    state_extra &= 0xFF00FFFF;
}
static void tl_fade_wait(void) { TITLE(5, 0, sm.animation_step.fields.relative_step = 1); }
#define FADE_STEP(speed, value) (sm.ext.title_logo.palette_shift_speed = speed, sm.ext.title_logo.palette_shift_value = value, sm.ext.title_logo.palette1 = title_source, sm.ext.title_logo.palette2 = title_target)
static void tl_fade_hold(void) { TITLE(6, 0, FADE_STEP(3, 5)); }
static void tl_fade_copy(void)
{
    u32 i;
    for (i = 0; i < COUNT(title_source); i++) {
        title_source[i] = 0x11110000 + i;
        title_target[i] = 0;
    }
    TITLE(6, 0, FADE_STEP(1, 5));
    for (i = 0; i < COUNT(title_target); i++)
        assert(title_target[i] == (i < (u32)(sm.ext.title_logo.palette1 - title_source) ? 0x11110000 + i : 0));
}
static void tl_fade_done(void) { TITLE(6, 0, FADE_STEP(1, 1)); state_extra ^= (u32)sm.id << 24; }
static void tl_sparkle(void) { TITLE(7, 0, sm.animation_step.fields.relative_step = 1); }
static void tl_sparkle_end(void) { TITLE(7, 0, 0); }
static void (*const tl_cases[])(void) = {
    tl_init_fade,
    tl_init_sparkle,
    tl_fade_ready,
    tl_fade_wait,
    tl_fade_hold,
    tl_fade_copy,
    tl_fade_done,
    tl_sparkle,
    tl_sparkle_end,
};
static const u32 tl_expected[] = {
    0x5u, 0xFF002001u, TITLE_FADE_X << 16, 0x480000u, 0u, 0u, 0u, 0x20000u | TITLE_PALETTE, 0xFF0000u, 0u,
    0x7u, 0xFF002101u, TITLE_SPARKLE_X << 16, 0x480000u, 0u, 0u, 0u, 0x10000u | TITLE_PALETTE, 0xFF0000u, 0u,
    0x6u, 0x1u, 0x800000u, 0x480000u, 0u, 0u, 0u, 0x40000u, 0xF02u, 0u,
    0x5u, 0x1u, 0x800000u, 0x480000u, 0u, 0u, 0u, 0x40000u, 0xFF0000u, 0u,
    0x6u, 0x1u, 0x800000u, 0x480000u, 0u, 0u, 0u, 0x50000u, 0x502u, 0u,
    0x6u, 0x1u, 0x800000u, 0x480000u, 0u, 0u, 0u, 0x50000u, 0x1000402u | TITLE_PALETTE_WORDS << 16, 0u,
    0u, 0x1u, 0x800000u, 0x480000u, 0u, 0u, 0u, 0x50000u, 0x13000002u, 0u,
    0x7u, 0x1u, 0x800000u, 0x480000u, 0u, 0u, 0u, 0x40000u, 0xFF0000u, 0u,
    0u, 0u, 0x800000u, 0x480000u, 0u, 0u, 0u, 0x40000u, 0xFF0000u, 0u,
};
static u32 test_tl(u32 row)
{
    return object_run(tl_cases[row], row, &tl_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "title_logo_parts", 0, 0, COUNT(tl_cases), test_tl },
    { "title_logo_star_pool", NULL, title_logo_star_pool_cases_expected, COUNT(title_logo_star_pool_cases_expected), star_case },
    { "title_star_hold_context", NULL, title_star_hold_context_cases_expected, COUNT(title_star_hold_context_cases_expected), hold_case },
    { "title_logo_init", 0, 0, 3, test_title_logo_init },
    { "title_logo_star_delay", 0, 0, 2, test_title_logo_star_delay },
    { "title_logo_trail_fade", 0, 0, 2, test_title_logo_trail_fade },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(title_logo_star_pool_cases_expected) + COUNT(title_star_hold_context_cases_expected) + 3 + 2 + 2 + COUNT(tl_cases);
