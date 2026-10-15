#include "test_runtime.h"

static u32 pulse_case(u32 mode)
{
    struct ShotObj obj, expected;
    struct VisualObj pool_before[32];
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 0x27;
        visual_objects[i].state = 0x28;
    }
    if (mode == 1)
        visual_objects[31].active = 0;
    obj.active = 0x41;
    obj.id = 23;
    obj.state = 1;
    obj.unk2 = 2;
    obj.unk5 = 1;
    obj.unk6 = mode >= 2;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.unk16 = 2;
    obj.unk15 = 0x40;
    obj.unk40 = 0x540;
    obj.unk42 = 0x9234;
    obj.animation_table = (const u8* const*)web_spider_animations;
    set_animation(&obj, 18);
    if (mode == 2) {
        obj.animation_cursor = (void*)(web_spider_animations[18] + 15);
        obj.animation_step = *(union AnimationStep*)obj.animation_cursor;
        assert(obj.animation_step.packed == 0x63000001);
    }
    expected = obj;
    memcpy(pool_before, visual_objects, sizeof(pool_before));
    if (mode < 2) {
        expected.unk6 = 1;
        if (mode == 1) {
            struct VisualObj* v = &pool_before[31];
            v->active = 0x41;
            v->id = 20;
            v->unk2 = 0;
            v->x_pos = obj.x_pos;
            v->y_pos = obj.y_pos;
            v->animation_table = obj.animation_table;
            v->unk40 = obj.unk40;
            v->unk3C = obj.unk3C;
            v->unk42 = 0x1234;
            v->unk16 = 2;
            v->unk15 = 0x40;
            v->unk50 = PLAYER_OBJECT(&obj);
        }
    } else if (mode == 2) {
        expected.unk5 = expected.unk6 = expected.unk2 = 0;
        expected.unk17 = 19;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (void*)(web_spider_animations[19] + 1);
        expected.animation_step = web_spider_animations[19][1];
    } else {
        expected.animation_cursor = (void*)(web_spider_animations[18] + 1);
        expected.animation_step = web_spider_animations[18][1];
    }
    web_thread_pulse(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)obj.unk17 << 16) | ((u32)visual_objects[31].active << 24);
}
#define CASE(m)                                             \
    static u32 web_thread_pulse_visual_pool_pulse_##m(void) \
    {                                                       \
        return pulse_case(m);                               \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
#define ENTRY(m) web_thread_pulse_visual_pool_pulse_##m,
static const CTestCase web_thread_pulse_visual_pool_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) };
static const u32 web_thread_pulse_visual_pool_cases_expected[] = { 0x1120101u, 0x41120101u, 0x1130000u, 0x1120101u };
#undef CASE
#undef ENTRY

static const u32 web_thread_pulse_expected[] = { 0u, 0u, 0xFFFFFFFFu, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_web_thread_pulse(u32 row)
{
    u32 observed_values[12];
    struct ShotObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    obj.unk6 = -1;
    pool_0_full = 0;
    obj.animation_step.fields.relative_step = -1;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_0_full ? 1 : 0;
    }
    web_thread_pulse(&obj);
    observed_values[0] = (u32)obj.unk2;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)visual_objects[0].active;
    observed_values[4] = (u32)visual_objects[0].id;
    observed_values[5] = (u32)visual_objects[0].unk15;
    observed_values[6] = (u32)visual_objects[0].unk16;
    observed_values[7] = (u32)visual_objects[0].unk2;
    observed_values[8] = (u32)visual_objects[0].unk40;
    observed_values[9] = (u32)visual_objects[0].unk42;
    observed_values[10] = (u32)visual_objects[0].x_pos.val;
    observed_values[11] = (u32)visual_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, web_thread_pulse_expected, 12);
}

static const u32 inputs_0[2][2] = {
    { -1, 0 },
    { 0, 255 },
};
struct web_thread_snap_case {
    u32 expected[3];
};
static const struct web_thread_snap_case web_thread_snap_cases[] = {
    { { 0u, 0u, 0u } },
    { { 0u, 2u, 0u } },
};
static u32 test_web_thread_snap(u32 row)
{
    const struct web_thread_snap_case* c = &web_thread_snap_cases[row];
    u32 observed_values[3];
    struct ShotObj obj;
    struct WeaponObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    obj.animation_step.fields.relative_step = inputs_0[row][0];
    child_0_present = inputs_0[row][1];
    obj.unk7C = child_0_present ? &child_0 : NULL;
    web_thread_snap(&obj);
    observed_values[0] = (u32)child_0.unk80.word;
    observed_values[1] = (u32)obj.state;
    observed_values[2] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

const struct CTestGroup c_test_groups[] = {
    { "web_thread_pulse_visual_pool", web_thread_pulse_visual_pool_cases, web_thread_pulse_visual_pool_cases_expected, COUNT(web_thread_pulse_visual_pool_cases), 0 },
    { "web_thread_pulse", 0, 0, 1, test_web_thread_pulse },
    { "web_thread_snap", 0, 0, 2, test_web_thread_snap },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(web_thread_pulse_visual_pool_cases) + 1 + 2;
