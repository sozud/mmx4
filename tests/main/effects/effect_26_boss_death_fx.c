#include "test_runtime.h"

static u32 death_case(u32 available)
{
    static const u8 variants[] = { 24, 2, 13 };
    struct EffectObj obj, expected;
    struct QuadObj pool[32];
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(g_QuadObjects, 0, sizeof(g_QuadObjects));
    for (i = 0; i < 32; i++) {
        g_QuadObjects[i].active = i >= 32 - available ? 0 : 1;
        g_QuadObjects[i].id = 39;
        g_QuadObjects[i].state = 40;
        g_QuadObjects[i].unk2 = 9;
        g_QuadObjects[i].unk5 = 3;
        g_QuadObjects[i].unk6 = 4;
        g_QuadObjects[i].unk7 = 5;
        g_QuadObjects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        g_QuadObjects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    obj.active = 1;
    obj.id = 26;
    obj.state = 0;
    obj.unk5 = 7;
    obj.unk2 = 9;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    expected = obj;
    memcpy(pool, g_QuadObjects, sizeof(pool));
    cur_random = 119;
    expected.unk2 = 24;
    expected.state = 1;
    expected.ext.effect_26.timer = 8;
    expected.ext.effect_26.quad_timer = 4;
    for (i = 0; i < available; i++) {
        struct QuadObj* child = &pool[32 - available + i];
        child->active = 1;
        child->id = 4;
        child->unk2 = variants[i];
        child->x_pos.u.hi = 100;
        child->y_pos.u.hi = 200;
    }
    boss_death_fx_init(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(pool) / 4; i++)
        assert(((u32*)g_QuadObjects)[i] == ((u32*)pool)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(cur_random == 376);
    return (u8)obj.unk2 | ((u32)(u8)g_QuadObjects[29].unk2 << 8) | ((u32)(u8)g_QuadObjects[30].unk2 << 16) | ((u32)(u8)g_QuadObjects[31].unk2 << 24);
}
#define CASE(m)                \
    static u32 death_##m(void) \
    {                          \
        return death_case(m);  \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
#define ENTRY(m) death_##m,
static const CTestCase boss_death_quad_allocation_steps_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) };
static const u32 boss_death_quad_allocation_steps_cases_expected[] = { 0x9090918u, 0x18090918u, 0x2180918u, 0xD021818u };
#undef CASE
#undef ENTRY

const struct CTestGroup c_test_groups[] = {
    { "boss_death_quad_allocation_steps", boss_death_quad_allocation_steps_cases, boss_death_quad_allocation_steps_cases_expected, COUNT(boss_death_quad_allocation_steps_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(boss_death_quad_allocation_steps_cases);
