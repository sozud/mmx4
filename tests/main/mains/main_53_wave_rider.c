#include "test_runtime.h"
extern union AnimationStep* wave_rider_animations[27];

static struct WaveInput {
    u8 tile, bob, air;
    s16 timer;
};
static const struct WaveInput inputs[] = {
    { 0, 0, 0, 0 },
    { 1, 0, 0, 0 },
    { 5, 0, 0, 0 },
    { 9, 0, 0, 0 },
    { 0, 1, 1, 0 },
};
static u8 tilemap[256];
static u16 pixels[512];
static u32 attributes[1];
static u32 wave_case(u32 mode, u32 observation)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    struct BackgroundObj bg_before[3];
    struct Unk_unk68 bounds = { 0, 0, 4, 4 };
    const struct WaveInput* input = &inputs[mode];
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 0x41;
    obj.id = 53;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = input->bob;
    obj.air_state = input->air;
    obj.unk7C = input->timer;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 80 * 65536 + 0x5678;
    obj.x_speed = 0x10000;
    obj.y_speed = 0x1000;
    obj.terrain_box = &bounds;
    obj.ext.main_53.unk80 = input->tile;
    obj.ext.main_53.unk84 = 1;
    obj.animation_table = (const u8* const*)wave_rider_animations;
    set_animation(&obj, 0);
    obj.animation_step.fields.duration = 2;
    before = obj;
    player_before = g_Player;
    memcpy(bg_before, background_objects, sizeof(bg_before));
    memset(tilemap, 1, sizeof(tilemap));
    memset(pixels, 0, sizeof(pixels));
    attributes[0] = input->tile;
    SP_BG_TILEMAP = tilemap;
    layout_width = 16;
    layout_size = 256;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    func_8006B6B0(&obj);
    before.unk5 = obj.unk5;
    before.unk6 = obj.unk6;
    before.air_state = obj.air_state;
    before.on_screen = obj.on_screen;
    before.unk7C = obj.unk7C;
    before.ext.main_53.unk80 = obj.ext.main_53.unk80;
    before.ext.main_53.unk81 = obj.ext.main_53.unk81;
    before.ext.main_53.unk84 = 0;
    before.x_pos = obj.x_pos;
    before.y_pos = obj.y_pos;
    before.x_speed = obj.x_speed;
    before.y_speed = obj.y_speed;
    before.x_accel = 0;
    before.gravity = obj.gravity;
    before.animation_step = obj.animation_step;
    if (obj.unk17 != before.unk17) {
        before.unk17 = obj.unk17;
        before.previous_animation_index = 0xFF;
        before.animation_cursor = (const u8*)wave_rider_animations[obj.unk17];
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(bg_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)bg_before)[i]);
    assert(bounds.unk0 == 0 && bounds.unk1 == 0 && bounds.unk2 == 4 && bounds.unk3 == 4);
    for (i = 0; i < COUNT(tilemap); i++)
        assert(tilemap[i] == 1);
    for (i = 0; i < COUNT(pixels); i++)
        assert(pixels[i] == 0);
    assert(attributes[0] == input->tile && SP_BG_TILEMAP == tilemap
        && SP_BG_TILE_PIXELS == pixels && SP_BG_TILE_ATTRS == attributes);
    assert(layout_width == 16 && layout_size == 256);
    switch (observation) {
    case 0:
        actual = (u8)obj.unk5 | ((u32)(u8)obj.air_state << 8)
            | ((u32)(u8)obj.unk6 << 16) | ((u32)obj.ext.main_53.unk81 << 24);
        break;
    case 1:
        actual = (u16)obj.unk7C | ((u32)obj.ext.main_53.unk80 << 16)
            | ((u32)obj.ext.main_53.unk84 << 24);
        break;
    case 2:
        actual = obj.x_pos.val;
        break;
    case 3:
        actual = obj.y_pos.val;
        break;
    case 4:
        actual = obj.x_speed;
        break;
    case 5:
        actual = obj.y_speed;
        break;
    case 6:
        actual = obj.gravity;
        break;
    case 7:
        actual = obj.animation_step.packed;
        break;
    default:
        actual = obj.on_screen | ((u32)obj.unk17 << 8);
        break;
    }
    return actual;
}
#define CASE(m, n)                                             \
    static u32 wave_rider_terrain_context_wave_##m##_##n(void) \
    {                                                          \
        return wave_case(m, n);                                \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1) CASE(m, 2) CASE(m, 3) CASE(m, 4) CASE(m, 5) CASE(m, 6) CASE(m, 7) CASE(m, 8)
MODE(0)
MODE(1)
MODE(2)
MODE(3)
MODE(4)
#define ENTRY(m, n) wave_rider_terrain_context_wave_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1) ENTRY(m, 2) ENTRY(m, 3) ENTRY(m, 4) ENTRY(m, 5) ENTRY(m, 6) ENTRY(m, 7) ENTRY(m, 8)
static const CTestCase wave_rider_terrain_context_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) ENTRIES(3) ENTRIES(4) };
static const u32 wave_rider_terrain_context_cases_expected[] = { 0x104u, 0x0u, 0x651234u, 0x504678u, 0x80000u, 0x1000u, 0x0u, 0x10002u, 0x301u, 0x1000104u, 0x10000u, 0x651234u, 0x504678u, 0x80000u, 0x1000u, 0x0u, 0x2010002u, 0x501u, 0x5000104u, 0x50000u, 0x651234u, 0x504678u, 0x80000u, 0x1000u, 0x0u, 0x1010002u, 0x401u, 0x9000104u, 0x90000u, 0x651234u, 0x504678u, 0x80000u, 0x1000u, 0x0u, 0x10002u, 0x301u, 0x10103u, 0x0u, 0x651234u, 0x504678u, 0x10000u, 0x1000u, 0x0u, 0x10001u, 0x1u };
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

static const u32 wave_rider_wait_offscreen_expected[] = { 1u, 2u };
static u32 test_wave_rider_wait_offscreen(u32 row)
{
    u32 observed_values[2];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.x_pos.val = -1048575;
    background_objects[0].x_pos.val = 2;
    background_objects[1].x_pos.val = 256;
    wave_rider_wait_offscreen(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, wave_rider_wait_offscreen_expected, 2);
}

const struct CTestGroup c_test_groups[] = {
    { "wave_rider_terrain_context", wave_rider_terrain_context_cases, wave_rider_terrain_context_cases_expected, COUNT(wave_rider_terrain_context_cases), 0 },
    { "wave_rider_wait_offscreen", 0, 0, 1, test_wave_rider_wait_offscreen },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(wave_rider_terrain_context_cases) + 1;
