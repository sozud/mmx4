#include "test_runtime.h"
#include "main/effects/effect_34_rock_drop_sequence.h"

static u32 rock_case(u32 mode)
{
    struct EffectObj obj, expected, pool_before[32];
    struct BackgroundObj bg_before[3];
    struct PlayerObj player_before;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(effect_objects, 0, sizeof(effect_objects));
    for (i = 0; i < 32; i++) {
        effect_objects[i].active = 1;
        effect_objects[i].id = 0x27;
        effect_objects[i].state = 0x28;
        effect_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        effect_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
        effect_objects[i].backref = &obj;
    }
    if (mode >= 4)
        effect_objects[31].active = 0;
    background_objects[0].unk34 = mode == 1 ? 0x10 : 0;
    obj.active = 0x41;
    obj.id = 34;
    obj.state = 1;
    obj.ext.effect_34.unk14 = mode == 2 ? 2 : mode == 5 ? 8
        : mode < 3                                      ? 1
                                                        : 0;
    obj.ext.effect_34.timer = mode < 3 ? 2 : 1;
    expected = obj;
    player_before = g_Player;
    memcpy(pool_before, effect_objects, sizeof(pool_before));
    memcpy(bg_before, background_objects, sizeof(bg_before));
    expected.ext.effect_34.timer = mode < 3 ? 1 : mode == 5 ? 0
                                                            : 2;
    if (mode >= 3) {
        expected.ext.effect_34.unk14 = mode == 5 ? 9 : 1;
        assert(rock_drop_sequence_delays[mode == 5 ? 9 : 1] == (mode == 5 ? 0 : 2));
        if (mode == 5)
            expected.state = 2;
        if (mode >= 4) {
            assert(rock_drop_sequence_subtypes[mode == 5 ? 8 : 0] == 0x24);
            assert(rock_drop_sequence_x_positions[mode == 5 ? 8 : 0] == (mode == 5 ? 0x4C0 : 0xC0));
            pool_before[31].active = 1;
            pool_before[31].id = 33;
            pool_before[31].unk2 = 0x24;
            pool_before[31].x_pos.u.hi = mode == 5 ? 0x4C0 : 0xC0;
            pool_before[31].y_pos.u.hi = 0x270;
            pool_before[31].backref = NULL;
            pool_before[31].state = 0;
        }
    } else if (mode == 0) {
        bg_before[0].unk36 = 8;
        bg_before[0].unk45 = 4;
        bg_before[0].unk3E.bytes[0] = 4;
        bg_before[0].unk3C = 2;
        bg_before[0].unk3A = 2;
        bg_before[0].unk34 |= 0x10;
    }
    rock_drop_sequence_spawn(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)effect_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(bg_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)bg_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u16)obj.ext.effect_34.timer | ((u32)(u8)obj.ext.effect_34.unk14 << 16) | ((u32)(u8)obj.state << 24);
}
#define CASE(m)                                       \
    static u32 rock_sequence_real_pool_rock_##m(void) \
    {                                                 \
        return rock_case(m);                          \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
#define ENTRY(m) rock_sequence_real_pool_rock_##m,
static const CTestCase rock_sequence_real_pool_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) };
static const u32 rock_sequence_real_pool_cases_expected[] = { 0x1010001u, 0x1010001u, 0x1020001u, 0x1010002u, 0x1010002u, 0x2090000u };
#undef CASE
#undef ENTRY

struct rock_drop_sequence_spawn_case {
    u32 timer, pool_0_full, unk14, unk34;
    u32 expected[9];
};
static const struct rock_drop_sequence_spawn_case rock_drop_sequence_spawn_cases[] = {
    { 0, 0, 1, 16, { 0u, 0u, 0u, 0u, 0u, 0u, 0xFFFFu, 1u, 0u } },
    { 1, 255, 8, 0, { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 2u } },
};
static u32 test_rock_drop_sequence_spawn(u32 row)
{
    const struct rock_drop_sequence_spawn_case* c = &rock_drop_sequence_spawn_cases[row];
    u32 observed_values[9];
    struct EffectObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&effect_objects, 0, sizeof(effect_objects));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.ext.effect_34.timer = c->timer;
    pool_0_full = c->pool_0_full;
    obj.ext.effect_34.unk14 = c->unk14;
    background_objects[0].unk34 = c->unk34;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            effect_objects[slot].active = pool_0_full ? 1 : 0;
    }
    rock_drop_sequence_spawn(&obj);
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)effect_objects[0].state;
    observed_values[3] = (u32)effect_objects[0].unk2;
    observed_values[4] = (u32)effect_objects[0].x_pos.u.hi;
    observed_values[5] = (u32)effect_objects[0].y_pos.u.hi;
    observed_values[6] = (u32)obj.ext.effect_34.timer;
    observed_values[7] = (u32)obj.ext.effect_34.unk14;
    observed_values[8] = (u32)obj.state;
    return c_test_observe(0, row, observed_values, c->expected, 9);
}

const struct CTestGroup c_test_groups[] = {
    { "rock_sequence_real_pool", rock_sequence_real_pool_cases, rock_sequence_real_pool_cases_expected, COUNT(rock_sequence_real_pool_cases), 0 },
    { "rock_drop_sequence_spawn", 0, 0, 2, test_rock_drop_sequence_spawn },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(rock_sequence_real_pool_cases) + 2;
