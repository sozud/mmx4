#include "test_runtime.h"
extern union MainPaletteData D_800F1660;

static u32 dialogue_case(u32 mode, u32 observation)
{
    struct MiscObj parts[6], before[6], pool_expected;
    struct MiscObj** slots[] = { &D_801397C0, &D_801397C4, &D_801397CC, &D_801397C8, &D_801397D4, &D_801397D0 };
    struct AbcObj dialogue_before;
    struct EngineObj engine_before;
    struct PlayerObj player_before;
    struct Func80022730Config config = { 1, 2, 3, 4, 5, 6 };
    u16 palette[1024], messages[] = { 2, 0x800 };
    const u16* dialogue_colors = (const u16*)&D_800F1660.raw[0xA0];
    u32 i, j, active_mask = 0, actual;
    memset(parts, 0, sizeof(parts));
    memset(&abc_object, 0, sizeof(abc_object));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(&pool_expected, 0, sizeof(pool_expected));
    pool_expected.active = 1;
    pool_expected.id = 0x17;
    for (i = 0; i < 64; i++)
        misc_objects[i] = pool_expected;
    for (i = 0; i < 1024; i++)
        palette[i] = 0x1400 + i;
    TEST_PALETTE = (u8*)palette;
    TEST_ARC_48 = (u8*)messages;
    engine_obj.stage = 2;
    engine_obj.cur_character = 1;
    engine_obj.enable_boss = 1;
    engine_obj.unk1F = 7;
    abc_object.unk0 = &messages[1];
    abc_object.unk4 = 0x27;
    abc_object.unkA = 0x15;
    abc_object.unkC = mode == 2 ? 0 : 1;
    abc_object.unkD = 2;
    abc_object.unkE = 3;
    abc_object.unkF = 7;
    for (i = 0; i < 6; i++) {
        parts[i].active = 1;
        parts[i].id = mode == 1 && (i == 2 || i == 4) ? 0x16 : 0x17;
        parts[i].on_screen = 1;
        parts[i].state = 3;
        parts[i].unk6 = 0x27 + i;
        *slots[i] = mode == 0 && i == 0 ? NULL : &parts[i];
    }
    D_801397BC = &parts[5];
    D_801397D8 = 0x27;
    D_801397DC = &config;
    D_801397E0 = 0x25;
    D_80139824 = 0x49;
    D_80139828 = 0x42;
    need_palette_load = 0x20;
    for (i = 0; i < 32; i++)
        D_801397E4[i] = 0x4242;
    memcpy(before, parts, sizeof(before));
    dialogue_before = abc_object;
    engine_before = engine_obj;
    player_before = g_Player;
    func_8002217C(mode == 2 ? 0 : 0x1234, 0x80, 0);
    dialogue_before.unkC = 0x80;
    dialogue_before.unkA = 0x27;
    if (mode == 2) {
        dialogue_before.unk0 = &messages[1];
        dialogue_before.unk4 = 0x800;
        dialogue_before.unk6 = -0x78;
        dialogue_before.unk8 = 0x1D;
        dialogue_before.unkD = 0;
        dialogue_before.unkE = 0;
        dialogue_before.unkF = 1;
        dialogue_before.unk10 = 0;
        engine_before.enable_boss = 0;
        engine_before.unk1F = 0;
        assert(D_801397BC == NULL && D_801397D8 == 0x80 && D_801397E0 == 0);
        assert(D_80139824 == 7 && D_80139828 == 1 && need_palette_load == 0x21);
    } else {
        dialogue_before.unkD = 4;
        dialogue_before.unk10 = (s16)0x9234;
        if (mode == 1) {
            before[2].active = before[2].on_screen = 0;
            before[4].active = before[4].on_screen = 0;
        }
        assert(D_801397BC == &parts[5] && D_801397D8 == 0x27 && D_801397E0 == 0x25);
        assert(D_80139824 == 0x49 && D_80139828 == 0x42 && need_palette_load == 0x20);
    }
    assert(D_801397DC == &config && messages[0] == 2 && messages[1] == 0x800);
    for (i = 0; i < 6; i++) {
        assert(*slots[i] == (mode == 2 || (mode == 0 && i == 0) ? NULL : &parts[i]));
        if (parts[i].active)
            active_mask |= 1 << i;
    }
    for (i = 0; i < sizeof(parts) / 4; i++)
        assert(((u32*)parts)[i] == ((u32*)before)[i]);
    for (i = 0; i < sizeof(abc_object) / 4; i++)
        assert(((u32*)&abc_object)[i] == ((u32*)&dialogue_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < 64; i++)
        for (j = 0; j < sizeof(pool_expected) / 4; j++)
            assert(((u32*)&misc_objects[i])[j] == ((u32*)&pool_expected)[j]);
    for (i = 0; i < 1024; i++)
        assert(palette[i] == (mode == 2 && i >= 0x150 && i < 0x170 ? dialogue_colors[i - 0x150] : 0x1400 + i));
    for (i = 0; i < 32; i++)
        assert(D_801397E4[i] == (mode == 2 ? 0x1550 + i : 0x4242));
    actual = observation == 0 ? abc_object.unkC | ((u32)abc_object.unkD << 8) | ((u32)abc_object.unkA << 16) : (u16)abc_object.unk10 | (active_mask << 16);
    return actual;
}
#define CASE(m, n)                      \
    static u32 dialogue_##m##_##n(void) \
    {                                   \
        return dialogue_case(m, n);     \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1)
MODE(0)
MODE(1)
MODE(2)
#define ENTRY(m, n) dialogue_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1)
static const CTestCase dialogue_interrupt_pool_full_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) };
static const u32 dialogue_interrupt_pool_full_cases_expected[] = { 0x270480u, 0x3F9234u, 0x270480u, 0x2B9234u, 0x270080u, 0x3F0000u };
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

const struct CTestGroup c_test_groups[] = {
    { "dialogue_interrupt_pool_full", dialogue_interrupt_pool_full_cases, dialogue_interrupt_pool_full_cases_expected, COUNT(dialogue_interrupt_pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(dialogue_interrupt_pool_full_cases);
