#include "test_runtime.h"

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
    obj.unk16 = 0;
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
        before.unk16 = 2;
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
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.state | ((u32)obj.ext.title_logo.palette_shift_speed << 8) | ((u32)(u16)obj.x_pos.i.hi << 16);
}
#define CASE(m)                                    \
    static u32 title_logo_star_pool_star_##m(void) \
    {                                              \
        return star_case(m);                       \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
#define ENTRY(m) title_logo_star_pool_star_##m,
static const CTestCase title_logo_star_pool_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) };
static const u32 title_logo_star_pool_cases_expected[] = { 0xD80003u, 0x7E0102u, 0x7E0302u, 0x7E0302u, 0x7E0302u };
#undef CASE
#undef ENTRY

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
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(background_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)background_before)[i]);
    return (u8)obj.active | ((u32)(u8)obj.state << 8) | ((u32)(u8)obj.on_screen << 16);
}
#define CASE(n)                                       \
    static u32 title_star_hold_context_hold_##n(void) \
    {                                                 \
        return hold_case(n);                          \
    }
CASE(0)
CASE(1)
static const CTestCase title_star_hold_context_cases[] = { title_star_hold_context_hold_0, title_star_hold_context_hold_1 };
static const u32 title_star_hold_context_cases_expected[] = { 0x10341u, 0x0u };
#undef CASE

struct title_logo_init_case {
    u32 unk2;
    u32 expected[15];
};
static const struct title_logo_init_case title_logo_init_cases[] = {
    { 16, { 0x1Cu, 0xFFFFFFFFu, 6u, 4u, 0u, 1u, 0x10u, 0x600u, 0x7804u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 0, { 0x1Cu, 0xFFFFFFFFu, 0x1Eu, 1u, 0u, 0u, 0u, 0x600u, 0x7804u, 0u, 0u, 0x80000u, 0xF0u, 0xF00000u, 0x60000u } },
    { 70, { 0x1Cu, 0xFFFFFFFFu, 0u, 3u, 0u, 0u, 0u, 0x600u, 0x7804u, 0xD8u, 0xD80000u, 0u, 0x48u, 0x480000u, 0u } },
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
    observed_values[4] = (u32)obj.unk15;
    observed_values[5] = (u32)obj.unk16;
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

const struct CTestGroup c_test_groups[] = {
    { "title_logo_star_pool", title_logo_star_pool_cases, title_logo_star_pool_cases_expected, COUNT(title_logo_star_pool_cases), 0 },
    { "title_star_hold_context", title_star_hold_context_cases, title_star_hold_context_cases_expected, COUNT(title_star_hold_context_cases), 0 },
    { "title_logo_init", 0, 0, 3, test_title_logo_init },
    { "title_logo_star_delay", 0, 0, 2, test_title_logo_star_delay },
    { "title_logo_trail_fade", 0, 0, 2, test_title_logo_trail_fade },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(title_logo_star_pool_cases) + COUNT(title_star_hold_context_cases) + 3 + 2 + 2;
