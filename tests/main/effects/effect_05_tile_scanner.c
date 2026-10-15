#include "test_runtime.h"

static struct ScannerInput {
    u8 phase, subphase, flags, direction, timer, tile;
    s32 velocity, acceleration, previous;
};
static const struct ScannerInput inputs[] = {
    { 9, 0, 0, 0, 1, 60, 0, 0, 100 * 65536 },
    { 2, 0, 0, 0, 1, 24, 65536, 0, 99 * 65536 },
    { 2, 0, 0, 0, 1, 28, 65536, 0, 102 * 65536 },
    { 2, 0, 0, 1, 1, 20, 65536, 0, 101 * 65536 + 0x5678 },
    { 2, 0, 0, 1, 1, 26, -65536, 0, 101 * 65536 },
    { 2, 0, 0, 3, 0, 60, -65536, -1, 100 * 65536 },
    { 2, 0, 0, 2, 1, 1, 65536, 0, 100 * 65536 },
    { 2, 0, 0, 2, 1, 0, 65536, 0, 101 * 65536 },
    { 2, 0, 0, 2, 1, 24, -65536, 0, 98 * 65536 },
    { 2, 0, 0, 2, 1, 28, -65536, 0, 101 * 65536 },
    { 12, 0, 0, 2, 1, 20, 65536, 0, 100 * 65536 },
    { 2, 2, 0, 2, 1, 26, 65536, 0, 100 * 65536 },
};
static u8 tilemap[256];
static u16 pixels[512];
static u32 attributes[1];
static u32 scanner_case(u32 mode, u32 observation)
{
    struct EffectObj obj, before;
    struct PlayerObj player_before;
    const struct ScannerInput* input = &inputs[mode];
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 1;
    obj.id = 5;
    obj.state = 2;
    obj.x_pos.val = 200 * 65536 + 0x4321;
    obj.ext.effect_5.unk1D = input->direction;
    obj.ext.effect_5.unk1F = input->timer;
    obj.ext.effect_5.unk14 = input->velocity;
    obj.ext.effect_5.unk18 = input->acceleration;
    g_Player.state = 1;
    g_Player.unk5 = input->phase;
    g_Player.unk6 = input->subphase;
    g_Player.unk88.bytes.collision_flags = input->flags;
    g_Player.x_pos.val = 100 * 65536 + 0x1234;
    g_Player.y_pos.val = 80 * 65536;
    g_Player.unk18.val = input->previous;
    before = obj;
    player_before = g_Player;
    memset(tilemap, 1, sizeof(tilemap));
    memset(pixels, 0, sizeof(pixels));
    attributes[0] = input->tile;
    SP_BG_TILEMAP = tilemap;
    layout_width = 16;
    layout_size = 256;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    func_800B6660(&obj);
    before.state = obj.state;
    before.x_pos = obj.x_pos;
    before.ext.effect_5.unk14 = obj.ext.effect_5.unk14;
    before.ext.effect_5.unk18 = obj.ext.effect_5.unk18;
    before.ext.effect_5.unk1D = obj.ext.effect_5.unk1D;
    before.ext.effect_5.unk1F = obj.ext.effect_5.unk1F;
    player_before.x_pos = g_Player.x_pos;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < COUNT(tilemap); i++)
        assert(tilemap[i] == 1);
    for (i = 0; i < COUNT(pixels); i++)
        assert(pixels[i] == 0);
    assert(attributes[0] == input->tile && SP_BG_TILEMAP == tilemap && SP_BG_TILE_PIXELS == pixels && SP_BG_TILE_ATTRS == attributes);
    assert(layout_width == 16 && layout_size == 256);
    switch (observation) {
    case 0:
        actual = (u8)obj.state | ((u32)obj.ext.effect_5.unk1D << 8) | ((u32)obj.ext.effect_5.unk1F << 16);
        break;
    case 1:
        actual = obj.x_pos.val;
        break;
    case 2:
        actual = g_Player.x_pos.val;
        break;
    case 3:
        actual = obj.ext.effect_5.unk14;
        break;
    default:
        actual = obj.ext.effect_5.unk18;
        break;
    }
    return actual;
}
#define SCANNER(m, n)                                       \
    static u32 tile_scanner_context_scanner_##m##_##n(void) \
    {                                                       \
        return scanner_case(m, n);                          \
    }
#define MODE(m) SCANNER(m, 0) SCANNER(m, 1) SCANNER(m, 2) SCANNER(m, 3) SCANNER(m, 4)
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
#define ENTRY(m, n) tile_scanner_context_scanner_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1) ENTRY(m, 2) ENTRY(m, 3) ENTRY(m, 4)
static const CTestCase tile_scanner_context_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) ENTRIES(3) ENTRIES(4) ENTRIES(5) ENTRIES(6) ENTRIES(7) ENTRIES(8) ENTRIES(9) ENTRIES(10) ENTRIES(11) };
static const u32 tile_scanner_context_cases_expected[] = { 0x10001u, 0xC84321u, 0x641234u, 0x0u, 0x0u, 0x10001u, 0x651234u, 0x651234u, 0x10000u, 0x0u, 0x10001u, 0x651234u, 0x651234u, 0x10000u, 0x0u, 0x10101u, 0x651234u, 0x651234u, 0x10000u, 0x0u, 0x10101u, 0x631234u, 0x631234u, 0xFFFF0000u, 0x0u, 0xFF0101u, 0x631234u, 0x631234u, 0xFFFF0600u, 0x600u, 0x201u, 0x651234u, 0x651234u, 0x10000u, 0x0u, 0x201u, 0x651234u, 0x651234u, 0x10000u, 0x0u, 0x202u, 0x631234u, 0x631234u, 0xFFFF0000u, 0x0u, 0x201u, 0x631234u, 0x631234u, 0xFFFF0000u, 0x0u, 0x202u, 0x651234u, 0x651234u, 0x10000u, 0x0u, 0x202u, 0x651234u, 0x651234u, 0x10000u, 0x0u };
#undef SCANNER
#undef MODE
#undef ENTRY
#undef ENTRIES

struct func_800B64BC_case {
    u32 state, unk5, unk1C, x_vel, unk1E, unk6, unk15;
    u32 expected[6];
};
static const struct func_800B64BC_case func_800B64BC_cases[] = {
    { 0, 0, 0, 0, 0, 0, 0, { 0u, 0u, 0u, 0u, 0u, 0u } },
    { 1, 48, 50, 0, 255, 0, 0, { 0u, 0xFFFFE800u, 1u, 0xFFu, 0u, 1u } },
    { 1, 12, 0, 0, 0, 2, 0, { 0u, 0xFFFFD800u, 2u, 0u, 0u, 1u } },
    { 1, 12, 0, -1, 0, 2, 255, { 0u, 0x2800u, 3u, 0xFFu, 0u, 1u } },
};
static u32 test_func_800B64BC(u32 row)
{
    const struct func_800B64BC_case* c = &func_800B64BC_cases[row];
    u32 observed_values[6];
    struct EffectObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.state = c->state;
    g_Player.unk5 = c->unk5;
    obj.ext.effect_5.unk1C = c->unk1C;
    g_Player.x_vel.val = c->x_vel;
    obj.ext.effect_5.unk1E = c->unk1E;
    g_Player.unk6 = c->unk6;
    g_Player.unk15 = c->unk15;
    func_800B64BC(&obj);
    observed_values[0] = (u32)obj.ext.effect_5.unk14;
    observed_values[1] = (u32)obj.ext.effect_5.unk18;
    observed_values[2] = (u32)obj.ext.effect_5.unk1D;
    observed_values[3] = (u32)obj.ext.effect_5.unk1E;
    observed_values[4] = (u32)obj.ext.effect_5.unk1F;
    observed_values[5] = (u32)obj.state;
    return c_test_observe(0, row, observed_values, c->expected, 6);
}

const struct CTestGroup c_test_groups[] = {
    { "tile_scanner_context", tile_scanner_context_cases, tile_scanner_context_cases_expected, COUNT(tile_scanner_context_cases), 0 },
    { "func_800B64BC", 0, 0, 4, test_func_800B64BC },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(tile_scanner_context_cases) + 4;
