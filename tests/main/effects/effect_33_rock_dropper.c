#include "test_runtime.h"

static u32 rock_case(u32 mode)
{
    struct EffectObj obj, expected;
    struct StageObjectRecord record, record_before;
    struct PlayerObj player_before = g_Player;
    u32 i, subtype = mode < 6 ? (mode / 2) * 16 : 48;
    memset(&obj, 0, sizeof(obj));
    memset(&record, 0xEF, sizeof(record));
    obj.active = 0x41;
    obj.id = 33;
    obj.unk2 = subtype | 3;
    obj.state = 2;
    obj.on_screen = 1;
    obj.unk5 = 5;
    obj.unk6 = 6;
    obj.unk7 = 7;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.backref = mode & 1 ? &record : NULL;
    expected = obj;
    record_before = record;
    if (mode < 6) {
        expected.active = expected.id = expected.unk2 = expected.on_screen = 0;
        expected.state = expected.unk5 = expected.unk6 = expected.unk7 = 0;
        if (mode & 1)
            record_before.flags = subtype == 32 ? 0x60 : 0x80;
    }
    rock_dropper_despawn(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(record); i++)
        assert(((u8*)&record)[i] == ((u8*)&record_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.active | ((u32)(u8)obj.unk2 << 8) | ((u32)record.flags << 16);
}
#define CASE(m)                                     \
    static u32 rock_dropper_backrefs_rock_##m(void) \
    {                                               \
        return rock_case(m);                        \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
#define ENTRY(m) rock_dropper_backrefs_rock_##m,
static const CTestCase rock_dropper_backrefs_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) };
static const u32 rock_dropper_backrefs_cases_expected[] = { 0xEF0000u, 0x800000u, 0xEF0000u, 0x800000u, 0xEF0000u, 0x600000u, 0xEF3341u };
#undef CASE
#undef ENTRY

static struct DropperInput {
    s8 subtype, phase;
    u8 variant, timer, burst, cooldown, proximity, full;
    s16 player_delta, bg_delta;
};
static const struct DropperInput inputs[] = {
    { 0, 0, 0, 1, 4, 1, 0, 1, 0, 0 },
    { 0x10, 0, 0, 1, 4, 1, 0, 1, 385, 0 },
    { 0x10, -1, 0, 1, 4, 1, 0, 0, 385, 0 },
    { 0x10, 0, 1, 1, 3, 1, 0, 0, 0, 0 },
    { 0x10, 0, 1, 1, 3, 1, 0, 1, -385, 0 },
    { 0x20, 0, 0, 1, 4, 1, 0, 0, 0, -960 },
    { 0x20, 0, 1, 1, 4, 1, 0, 1, 0, 0 },
    { 0x20, 0, 0, 1, 4, 1, 1, 0, 32, 0 },
    { 0x20, 0, 0, 1, 4, 1, 1, 0, -32, 0 },
    { 0x20, 0, 1, 2, 4, 1, 1, 0, 1, 0 },
    { 0x20, 0, 1, 1, 4, 1, 1, 0, -1, 0 },
    { 0x30, 0, 0, 1, 4, 1, 0, 0, 0, 0 },
    { 0x20, 0, 1, 1, 4, 1, 1, 1, 0, 0 },
    { 0x10, 3, 0, 1, 4, 1, 0, 0, 385, 0 },
};
static u32 dropper_case(u32 mode, u32 observation)
{
    struct EffectObj obj, before;
    struct PlayerObj player_before;
    struct BackgroundObj bg_before[3];
    struct ShotObj pool_before[32];
    const struct DropperInput* input = &inputs[mode];
    u32 i, j, actual, link;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    memset(shot_objects, 0, sizeof(shot_objects));
    obj.active = 1;
    obj.id = 33;
    obj.state = 1;
    obj.unk2 = input->subtype;
    obj.unk5 = input->phase;
    obj.unk6 = 0x27;
    obj.x_pos.val = 1000 * 65536 + 0xABCD;
    obj.y_pos.val = 200 * 65536 + 0x1234;
    obj.ext.effect_33.timer = input->timer;
    obj.ext.effect_33.period = 0x26;
    obj.ext.effect_33.variant = input->variant;
    obj.ext.effect_33.burst = input->burst;
    obj.ext.effect_33.cooldown = input->cooldown;
    obj.ext.effect_33.proximity = input->proximity;
    g_Player.x_pos.i.hi = 1000 + input->player_delta;
    background_objects[0].x_pos.i.hi = 1000 + input->bg_delta;
    for (i = 0; i < COUNT(shot_objects); i++) {
        shot_objects[i].active = 1;
        shot_objects[i].id = 0x17;
    }
    shot_objects[0].active = input->full ? 1 : 0;
    shot_objects[0].unk2 = 0x28;
    shot_objects[0].state = 0x27;
    shot_objects[0].unk15 = 0x40;
    shot_objects[0].unk6 = 0x2F;
    shot_objects[0].x_pos.val = 250 * 65536 + 0x1234;
    shot_objects[0].y_pos.val = 500 * 65536 + 0x5678;
    before = obj;
    player_before = g_Player;
    memcpy(bg_before, background_objects, sizeof(bg_before));
    memcpy(pool_before, shot_objects, sizeof(pool_before));
    func_800BC92C(&obj);
    before.state = obj.state;
    before.unk5 = obj.unk5;
    before.unk6 = obj.unk6;
    before.ext.effect_33.timer = obj.ext.effect_33.timer;
    before.ext.effect_33.burst = obj.ext.effect_33.burst;
    before.ext.effect_33.cooldown = obj.ext.effect_33.cooldown;
    pool_before[0].active = shot_objects[0].active;
    pool_before[0].id = shot_objects[0].id;
    pool_before[0].unk2 = shot_objects[0].unk2;
    pool_before[0].state = shot_objects[0].state;
    pool_before[0].unk15 = shot_objects[0].unk15;
    pool_before[0].unk6 = shot_objects[0].unk6;
    pool_before[0].x_pos = shot_objects[0].x_pos;
    pool_before[0].y_pos = shot_objects[0].y_pos;
    link = shot_objects[0].active == 0x41 && shot_objects[0].state == 6;
    pool_before[0].unk84.effect = link ? &obj : NULL;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(bg_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)bg_before)[i]);
    for (i = 0; i < COUNT(shot_objects); i++)
        for (j = 0; j < sizeof(pool_before[0]) / 4; j++)
            assert(((u32*)&shot_objects[i])[j] == ((u32*)&pool_before[i])[j]);
    switch (observation) {
    case 0:
        actual = (u8)obj.state | ((u32)(u8)obj.unk5 << 8) | ((u32)(u8)obj.unk6 << 16);
        break;
    case 1:
        actual = obj.ext.effect_33.timer | ((u32)obj.ext.effect_33.burst << 8) | ((u32)obj.ext.effect_33.cooldown << 16) | ((u32)obj.ext.effect_33.period << 24);
        break;
    case 2:
        actual = (u8)shot_objects[0].active | ((u32)(u8)shot_objects[0].id << 8) | ((u32)(u8)shot_objects[0].unk2 << 16) | ((u32)(u8)shot_objects[0].state << 24);
        break;
    case 3:
        actual = shot_objects[0].x_pos.val;
        break;
    case 4:
        actual = shot_objects[0].y_pos.val;
        break;
    default:
        actual = shot_objects[0].unk15 | ((u32)(u8)shot_objects[0].unk6 << 8) | (link << 16);
        break;
    }
    return actual;
}
#define DROPPER(m, n)                                       \
    static u32 rock_dropper_context_dropper_##m##_##n(void) \
    {                                                       \
        return dropper_case(m, n);                          \
    }
#define MODE(m) DROPPER(m, 0) DROPPER(m, 1) DROPPER(m, 2) DROPPER(m, 3) DROPPER(m, 4) DROPPER(m, 5)
MODE(0)
MODE(1)
MODE(2)
MODE(3)
MODE(4)
MODE(5)
MODE(6)
MODE(7)
MODE(8)
MODE(9)
MODE(10)
MODE(11)
MODE(12)
MODE(13)
#define ENTRY(m, n) rock_dropper_context_dropper_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1) ENTRY(m, 2) ENTRY(m, 3) ENTRY(m, 4) ENTRY(m, 5)
static const CTestCase rock_dropper_context_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) ENTRIES(3) ENTRIES(4) ENTRIES(5) ENTRIES(6) ENTRIES(7) ENTRIES(8) ENTRIES(9) ENTRIES(10) ENTRIES(11) ENTRIES(12) ENTRIES(13) };
static const u32 rock_dropper_context_cases_expected[] = { 0x270001u, 0x26010426u, 0x27281701u, 0xFA1234u, 0x1F45678u, 0x2F40u, 0x270101u, 0x26010401u, 0x27281701u, 0xFA1234u, 0x1F45678u, 0x2F40u, 0x27FF01u, 0x26010401u, 0x27281700u, 0xFA1234u, 0x1F45678u, 0x2F40u, 0x270003u, 0x26010301u, 0x27281700u, 0xFA1234u, 0x1F45678u, 0x2F40u, 0x270101u, 0x26010301u, 0x27281701u, 0xFA1234u, 0x1F45678u, 0x2F40u, 0x270002u, 0x26010401u, 0x27281700u, 0xFA1234u, 0x1F45678u, 0x2F40u, 0x270001u, 0x26010426u, 0x27281701u, 0xFA1234u, 0x1F45678u, 0x2F40u, 0x270001u, 0x26010426u, 0x27281700u, 0xFA1234u, 0x1F45678u, 0x2F40u, 0x270001u, 0x26010426u, 0x27281700u, 0xFA1234u, 0x1F45678u, 0x2F40u, 0x270001u, 0x26010401u, 0x27281700u, 0xFA1234u, 0x1F45678u, 0x2F40u, 0x10001u, 0x26010400u, 0x6012141u, 0x3E81234u, 0x1F45678u, 0x12740u, 0x270001u, 0x26010401u, 0x27281700u, 0xFA1234u, 0x1F45678u, 0x2F40u, 0x270001u, 0x26010400u, 0x27281701u, 0xFA1234u, 0x1F45678u, 0x2F40u, 0x270301u, 0x26010401u, 0x27281700u, 0xFA1234u, 0x1F45678u, 0x2F40u };
#undef DROPPER
#undef MODE
#undef ENTRY
#undef ENTRIES

struct func_800BC784_case {
    u32 unk2;
    u32 expected[9];
};
static const struct func_800BC784_case func_800BC784_cases[] = {
    { -16, { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 47, { 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0u } },
};
static u32 test_func_800BC784(u32 row)
{
    const struct func_800BC784_case* c = &func_800BC784_cases[row];
    u32 observed_values[9];
    struct EffectObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.unk2 = c->unk2;
    func_800BC784(&obj);
    observed_values[0] = (u32)obj.ext.effect_33.burst;
    observed_values[1] = (u32)obj.ext.effect_33.cooldown;
    observed_values[2] = (u32)obj.ext.effect_33.period;
    observed_values[3] = (u32)obj.ext.effect_33.proximity;
    observed_values[4] = (u32)obj.ext.effect_33.timer;
    observed_values[5] = (u32)obj.ext.effect_33.variant;
    observed_values[6] = (u32)obj.state;
    observed_values[7] = (u32)obj.unk5;
    observed_values[8] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, c->expected, 9);
}

const struct CTestGroup c_test_groups[] = {
    { "rock_dropper_backrefs", rock_dropper_backrefs_cases, rock_dropper_backrefs_cases_expected, COUNT(rock_dropper_backrefs_cases), 0 },
    { "rock_dropper_context", rock_dropper_context_cases, rock_dropper_context_cases_expected, COUNT(rock_dropper_context_cases), 0 },
    { "func_800BC784", 0, 0, 2, test_func_800BC784 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(rock_dropper_backrefs_cases) + COUNT(rock_dropper_context_cases) + 2;
