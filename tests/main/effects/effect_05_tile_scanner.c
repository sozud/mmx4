#include "test_runtime.h"
#include "support/platform_fixture.h"
#include "main/effects/effect_05_tile_scanner.h"

static struct ScannerInput {
    u8 phase, subphase, flags, direction, timer, tile;
    s32 velocity, acceleration, previous;
    u8 box;
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
    { 6, 0, 0, 0, 1, 60, 0, 0, 100 * 65536 },
    { 2, 0, 1, 0, 1, 60, 0, 0, 100 * 65536 },
    { 2, 0, 0, 0, 1, 0, 65536, 0, 101 * 65536 },
    { 2, 0, 0, 0, 1, 1, 65536, 0, 101 * 65536 },
    { 2, 0, 0, 0, 1, 60, -65536, 0, 100 * 65536 },
    { 2, 0, 0, 3, 0, 60, 65536, 1, 100 * 65536 },
    { 2, 0, 0, 1, 1, 60, -0x1000, 0, 100 * 65536 + 0x5678 },
    { 2, 0, 0, 2, 1, 60, 65536, 0, 100 * 65536, 1 },
};
static u8 tilemap[256];
static u16 pixels[512];
static u32 attributes[1];
static struct Unk_unk68 scanner_box = { 0, 0, 8, 8 };
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
    g_Player.unk68 = input->box ? &scanner_box : NULL;
    before = obj;
    player_before = g_Player;
    memset(tilemap, 1, sizeof(tilemap));
    memset(pixels, 0, sizeof(pixels));
    attributes[0] = TEST_DISC32(input->tile);
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
    assert(attributes[0] == TEST_DISC32(input->tile) && SP_BG_TILEMAP == tilemap && SP_BG_TILE_PIXELS == pixels && SP_BG_TILE_ATTRS == attributes);
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
static const u32 tile_scanner_context_cases_expected[] = { 0x10001u, 0xC84321u, 0x641234u, 0x0u, 0x0u, 0x10001u, 0x651234u, 0x651234u, 0x10000u, 0x0u, 0x10001u, 0x651234u, 0x651234u, 0x10000u, 0x0u, 0x10101u, 0x651234u, 0x651234u, 0x10000u, 0x0u, 0x10101u, 0x631234u, 0x631234u, 0xFFFF0000u, 0x0u, 0xFF0101u, 0x631234u, 0x631234u, 0xFFFF0600u, 0x600u, 0x201u, 0x651234u, 0x651234u, 0x10000u, 0x0u, 0x201u, 0x651234u, 0x651234u, 0x10000u, 0x0u, 0x202u, 0x631234u, 0x631234u, 0xFFFF0000u, 0x0u, 0x201u, 0x631234u, 0x631234u, 0xFFFF0000u, 0x0u, 0x202u, 0x651234u, 0x651234u, 0x10000u, 0x0u, 0x202u, 0x651234u, 0x651234u, 0x10000u, 0x0u, 0x10001u, 0xC84321u, 0x641234u, 0x0u, 0x0u, 0x10001u, 0xC84321u, 0x641234u, 0x0u, 0x0u, 0x10001u, 0x651234u, 0x651234u, 0x10000u, 0x0u, 0x10001u, 0x651234u, 0x651234u, 0x10000u, 0x0u, 0x10002u, 0x631234u, 0x631234u, 0xFFFF0000u, 0x0u, 0xFF0102u, 0x651234u, 0x651234u, 0xFA00u, 0xFFFFFA00u, 0x10101u, 0x640234u, 0x640234u, 0xFFFFF000u, 0x0u, 0x201u, 0x651234u, 0x651234u, 0x10000u, 0x0u };
static u32 tile_scanner_context_cases_row(u32 row)
{
    return scanner_case(row / 5, row % 5);
}

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

#ifdef VERSION_SATURN_PROTO
static const struct {
    u8 tile, state, previous_tile, player_state, action, facing;
    s32 delta;
} conveyor_rows[] = {
    { 5, 2, 0, 0, 7, 0, 0 },
    { 5, 2, 0, 0, 7, 0, 0x10000 },
    { 0, 1, 0, 1, 7, 0, 0 },
    { 0, 2, 0, 1, 7, 0, 0 },
    { 17, 2, 0, 1, 7, 0, 0x10000 },
    { 17, 2, 0x3C, 1, 7, 1, 0x10000 },
    { 17, 2, 0, 1, 7, 0, -0x40000 },
    { 21, 2, 0, 1, 7, 0, 0x10000 },
    { 21, 2, 0x3C, 1, 7, 0, 0x10000 },
    { 21, 2, 0, 1, 7, 0, 0x40000 },
    { 25, 2, 0, 1, 7, 0, 0x10000 },
    { 25, 2, 0x3C, 1, 7, 1, 0x10000 },
    { 27, 2, 0, 1, 7, 0, 0x10000 },
    { 27, 2, 0x3C, 1, 7, 0, 0x10000 },
    { 60, 1, 0, 1, 7, 0, 0 },
    { 5, 2, 0, 1, 7, 0, 0 },
    { 17, 2, 0x3C, 1, 7, 0, 0x10000 },
    { 17, 2, 0x3C, 1, 12, 1, 0x10000 },
    { 21, 2, 0x3C, 1, 7, 1, 0x10000 },
    { 21, 2, 0x3C, 1, 12, 0, 0x10000 },
    { 25, 2, 0x3C, 1, 7, 0, 0x10000 },
    { 25, 2, 0x3C, 1, 12, 1, 0x10000 },
    { 27, 2, 0x3C, 1, 7, 1, 0x10000 },
    { 27, 2, 0x3C, 1, 12, 0, 0x10000 },
    { 25, 2, 0, 1, 7, 0, -0x40000 },
    { 27, 2, 0, 1, 7, 0, 0x40000 },
};
static const u32 conveyor_expected[COUNT(conveyor_rows)][5] = {
#include "effect_05_conveyor_expected.inc"
};
static struct Unk_unk68 conveyor_box = { 0, 0, 8, 8 };
static u32 conveyor(u32 row)
{
    struct EffectObj obj;
    u32 seen[5];
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 1;
    obj.id = 5;
    obj.state = conveyor_rows[row].state;
    obj.ext.effect_5.unk20 = conveyor_rows[row].previous_tile;
    g_Player.state = conveyor_rows[row].player_state;
    g_Player.unk5 = conveyor_rows[row].action;
    g_Player.unk15 = conveyor_rows[row].facing ? PLAYER_FACING_RIGHT : 0;
    g_Player.unk68 = &conveyor_box;
    g_Player.x_pos.val = 100 * 65536;
    g_Player.unk18.val = 100 * 65536 - conveyor_rows[row].delta;
    g_Player.y_pos.val = 80 * 65536;
    memset(tilemap, 1, sizeof(tilemap));
    memset(pixels, 0, sizeof(pixels));
    attributes[0] = C_TEST_PSX_WORD(conveyor_rows[row].tile);
    SP_BG_TILEMAP = tilemap;
    layout_width = 16;
    layout_size = 256;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    func_800B60BC(&obj);
    seen[0] = obj.state;
    seen[1] = obj.ext.effect_5.unk20 | (u32)obj.ext.effect_5.unk21 << 8;
    seen[2] = obj.ext.effect_5.unk1C;
    seen[3] = obj.ext.effect_5.unk1E;
    seen[4] = g_Player.x_pos.val;
    return c_test_observe(0, row, seen, conveyor_expected[row], 5);
}
#define CONVEYOR_CASES COUNT(conveyor_rows)
#else
#define CONVEYOR_CASES 0
#endif

#if defined(MMX4_PC) || (defined(MMX4_SATURN) && !defined(VERSION_SATURN_PROTO))
static const struct {
    u8 tile, above, side, state, previous_tile, player_state, action, facing;
    s16 x;
    s32 delta;
} belt_rows[] = {
    { 0, 0, 0, 2, 0, 1, 7, 0, 100, 0 },
    { 17, 0, 0, 2, 0, 1, 7, 0, 100, -0x40000 },
    { 17, 0, 0, 2, 0x3C, 1, 7, 1, 100, 0x10000 },
    { 17, 0, 0, 2, 0x3C, 1, 12, 1, 100, 0x10000 },
    { 21, 0, 0, 2, 0, 1, 7, 0, 100, 0x40000 },
    { 21, 0, 0, 2, 0x3C, 1, 7, 0, 100, 0x10000 },
    { 21, 0, 0, 2, 0x3C, 1, 12, 0, 100, 0x10000 },
    { 60, 0, 0, 1, 0, 1, 7, 0, 100, 0 },
    { 17, 0, 0, 2, 0, 1, 7, 0, 96, 0x10000 },
    { 16, 17, 0, 2, 0, 1, 7, 0, 100, 0x10000 },
    { 18, 0, 0, 2, 0, 1, 7, 0, 100, 0x10000 },
    { 19, 0, 0, 2, 0, 1, 7, 0, 100, 0x10000 },
    { 20, 0, 0, 2, 0, 1, 7, 0, 100, 0x10000 },
    { 25, 0, 0, 2, 0, 1, 7, 0, 100, 0x10000 },
    { 26, 0, 0, 2, 0, 1, 7, 0, 100, 0x10000 },
    { 22, 0, 0, 2, 0, 1, 7, 0, 100, 0x10000 },
    { 23, 0, 0, 2, 0, 1, 7, 0, 100, 0x10000 },
    { 24, 0, 0, 2, 0, 1, 7, 0, 100, 0x10000 },
    { 27, 0, 0, 2, 0, 1, 7, 0, 100, 0x10000 },
    { 28, 0, 0, 2, 0, 1, 7, 0, 100, 0x10000 },
    { 17, 0, 0, 2, 0x3C, 1, 7, 0, 100, 0x10000 },
    { 21, 0, 0, 2, 0x3C, 1, 7, 1, 100, 0x10000 },
    { 5, 0, 0, 2, 0, 1, 7, 0, 100, 0x10000 },
    { 17, 0, 0x30, 2, 0, 1, 7, 0, 96, 0x10000 },
    { 17, 0, 5, 2, 0, 1, 7, 0, 96, 0x10000 },
    { 17, 0, 17, 2, 0, 1, 7, 0, 96, 0x10000 },
    { 5, 0, 0, 2, 0, 0, 7, 0, 100, -0x10000 },
    { 5, 0, 0, 2, 0, 0, 7, 0, 100, 0x10000 },
};
static const u32 belt_expected[COUNT(belt_rows)][5] = {
#include "effect_05_belt_expected.inc"
};
static struct Unk_unk68 belt_box = { 0, 0, 8, 8 };
static u32 belt_attributes[4];
static u32 belt_push(u32 row)
{
    struct EffectObj obj;
    u32 seen[5], column = (u16)belt_rows[row].x >> 4 & 15;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 1;
    obj.id = 5;
    obj.state = belt_rows[row].state;
    obj.ext.effect_5.unk20 = belt_rows[row].previous_tile;
    g_Player.state = belt_rows[row].player_state;
    g_Player.unk5 = belt_rows[row].action;
    g_Player.unk15 = belt_rows[row].facing ? PLAYER_FACING_RIGHT : 0;
    g_Player.unk68 = &belt_box;
    g_Player.x_pos.val = belt_rows[row].x * 65536;
    g_Player.unk18.val = belt_rows[row].x * 65536 - belt_rows[row].delta;
    g_Player.y_pos.val = 80 * 65536;
    memset(tilemap, 1, sizeof(tilemap));
    memset(pixels, 0, sizeof(pixels));
    pixels[256 + 5 * 16 + column] = 1;
    pixels[256 + 4 * 16 + column] = 2;
    pixels[256 + 5 * 16 + column - 1] = pixels[256 + 5 * 16 + column + 1] = 3;
    belt_attributes[0] = 0;
    belt_attributes[1] = TEST_DISC32(belt_rows[row].tile);
    belt_attributes[2] = TEST_DISC32(belt_rows[row].above);
    belt_attributes[3] = TEST_DISC32(belt_rows[row].side);
    layout_width = 16;
    layout_size = 256;
    test_stage_screen(tilemap, pixels, belt_attributes);
    func_800B60BC(&obj);
    seen[0] = obj.state;
    seen[1] = obj.ext.effect_5.unk20 | (u32)obj.ext.effect_5.unk21 << 8;
    seen[2] = obj.ext.effect_5.unk1C;
    seen[3] = C_TEST_PSX_FACING(obj.ext.effect_5.unk1E);
    seen[4] = g_Player.x_pos.val;
    return c_test_observe(5, row, seen, belt_expected[row], 5);
}
#define BELT_CASES COUNT(belt_rows)
#else
#define BELT_CASES 0
#endif

static u32 scan_paths(u32 row);
const struct CTestGroup c_test_groups[] = {
    { "scan_paths", 0, 0, 10, scan_paths },
    { "tile_scanner_context", NULL, tile_scanner_context_cases_expected, COUNT(tile_scanner_context_cases_expected), tile_scanner_context_cases_row },
    { "func_800B64BC", 0, 0, 4, test_func_800B64BC },
#ifdef VERSION_SATURN_PROTO
    { "proto_conveyor_push", 0, 0, CONVEYOR_CASES, conveyor },
#endif
#if defined(MMX4_PC) || (defined(MMX4_SATURN) && !defined(VERSION_SATURN_PROTO))
    { "belt_push", 0, 0, BELT_CASES, belt_push },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(tile_scanner_context_cases_expected) + 4 + 10 + CONVEYOR_CASES + BELT_CASES;

void func_800B64BC(struct EffectObj*);
static u32 scan_paths(u32 row)
{
    static const u8 actions[] = { 48, 2, 2, 2, 2, 5, 8, 12, 0, 7 }, previous[] = { 0, 3, 3, 4, 4, 0, 0, 0, 0, 0 };
    static const s32 speeds[] = { 0, 0x8000, -0x8000, 0x20000, -0x20000, 0x12345, 0x12345, 0, 0, 0 };
    struct EffectObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 1;
    obj.id = 5;
    obj.state = 1;
    g_Player.state = 1;
    g_Player.unk5 = actions[row];
    g_Player.unk6 = 1;
    g_Player.x_vel.val = 0x12345;
    obj.ext.effect_5.unk1C = previous[row];
    obj.ext.effect_5.unk1E = row == 1 || row == 3 || row == 5 ? 0x40 : 0;
    obj.ext.effect_5.unk1F = 9;
    func_800B64BC(&obj);
    assert(obj.ext.effect_5.unk1F == 0);
    if (row == 0 || row >= 7) {
        assert(obj.state == 1 && obj.ext.effect_5.unk14 == 0 && obj.ext.effect_5.unk18 == 0);
        return 1;
    }
    assert(obj.state == 2 && obj.ext.effect_5.unk14 == speeds[row]);
    assert(obj.ext.effect_5.unk18 == (obj.ext.effect_5.unk1E ? -0x1800 : 0x1800));
    assert(obj.ext.effect_5.unk1D == (obj.ext.effect_5.unk1E != 0));
    return 1;
}
