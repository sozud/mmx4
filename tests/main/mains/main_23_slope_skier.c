#include "test_runtime.h"
#include "main/mains/main_12_hover_sentry.h"
#include "main/mains/main_23_slope_skier.h"
#include "main/55C4.h"
#include "main/object_motion.h"
extern struct Unk_unk68 D_800FCE9C[];
extern struct VisualSpawnOffset D_800FCE90[5];
extern struct Unk_unk68 slope_skier_terrain_box;

static struct SlopeInput {
    u8 ski, attribute, facing, on_screen, flags, timer, full;
};
enum { EMPTY,
    LOW,
    LOW_FACING,
    LOW_STEEP,
    LOW_STEEP_FACING,
    HIGH,
    HIGH_FACING,
    HIGH_STEEP,
    SPIKE_HIDDEN,
    SPIKE_VISIBLE,
    FLAT,
    OTHER,
    SKI_SPAWN,
    SKI_FULL,
    SKI_WALL,
    SKI_DROP };
static const struct SlopeInput inputs[] = {
    { 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0x12, 0, 0, 0, 0, 0 },
    { 0, 0x12, 0x40, 0, 0, 0, 0 },
    { 0, 0x16, 0, 0, 0, 0, 0 },
    { 0, 0x16, 0x40, 0, 0, 0, 0 },
    { 0, 0x1A, 0, 0, 0, 0, 0 },
    { 0, 0x1A, 0x40, 0, 0, 0, 0 },
    { 0, 0x1C, 0, 0, 0, 0, 0 },
    { 0, 0x3E, 0, 0, 0, 0, 0 },
    { 0, 0x3E, 0, 1, 0, 0, 0 },
    { 0, 0x10, 0, 0, 0, 0, 0 },
    { 0, 0x20, 0, 0, 0, 0, 0 },
    { 1, 0x12, 0, 0, 0, 1, 0 },
    { 1, 0x12, 0, 0, 0, 1, 1 },
    { 1, 0x12, 0, 0, 2, 3, 0 },
    { 1, 0, 0, 0, 0, 3, 0 },
};
#define VISUAL_SLOT 9
static u8 tilemap[256];
static u16 tiles[2][16][16];
static u32 attributes[1];
static u32 steps[2];
static u32* table[0x80];
static struct Unk_unk68 box = { 0, 0, 8, 8 };
static struct MainObj skier, expected;
static struct VisualObj want_visuals[0x20];

static void zero(void* target, u32 size)
{
    u32 i;
    for (i = 0; i < size / 4; i++)
        ((u32*)target)[i] = 0;
}

static u8 slope(u8 attribute, u8 facing, u8 previous)
{
    if (attribute == 0)
        return 3;
    if (attribute > 0x10 && attribute <= 0x1E) {
        if (attribute >= 0x19)
            return attribute >= 0x1B ? (facing == 0 ? 0x82 : 2) : (facing != 0 ? 0x82 : 2);
        return attribute >= 0x15 ? (facing == 0 ? 0x81 : 1) : (facing != 0 ? 0x81 : 1);
    }
    if (attribute == 0x3E || attribute == 0x10)
        return previous;
    return 0;
}

static u32 slope_skier_steps_run(u32 mode)
{
    const struct SlopeInput* input = &inputs[mode];
    union AnimationStep value;
    u32 i, difference = 0;
    u8 next;
    memset(tilemap, 1, sizeof(tilemap));
    memset(tiles, 0, sizeof(tiles));
    attributes[0] = input->attribute;
    SP_BG_TILEMAP = tilemap;
    layout_width = 16;
    layout_size = 256;
    TEST_BG_TILE_PIXELS = (u8*)tiles;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    zero(visual_objects, sizeof(visual_objects));
    zero(misc_objects, sizeof(misc_objects));
    for (i = 0; i < 0x20; i++)
        visual_objects[i].active = input->full || !input->ski || i != VISUAL_SLOT;
    for (i = 0; i < 0x40; i++)
        misc_objects[i].active = 1;
    memcpy(want_visuals, visual_objects, sizeof(want_visuals));
    value.fields.duration = 4;
    value.fields.event = 0;
    value.fields.relative_step = 1;
    value.fields.frame_index = 3;
    steps[0] = value.packed;
    value.fields.duration = 8;
    steps[1] = value.packed;
    for (i = 0; i < COUNT(table); i++)
        table[i] = &steps[1];
    memset(&skier, 0, sizeof(skier));
    skier.active = 0x41;
    skier.id = 0x17;
    skier.state = 1;
    skier.unk5 = 2;
    skier.unk6 = 1;
    skier.on_screen = input->on_screen;
    skier.unk15 = input->facing;
    skier.unk16 = 3;
    skier.unk40 = 0x0123;
    skier.unk42 = 0x0456;
    skier.x_pos.val = 0x00801111;
    skier.y_pos.val = 0x00602222;
    skier.x_speed = 0x10000;
    skier.collision_flags = input->flags;
    skier.unk7C = input->timer;
    skier.terrain_box = &box;
    skier.sprite_frames = (const u8*)&steps[0];
    skier.animation_table = table;
    skier.animation_cursor = &steps[0];
    skier.animation_step.packed = steps[0];
    skier.ext.main_23.unk80 = 0x55;
    expected = skier;

    if (!input->ski) {
        slope_skier_read_slope(&skier);
        expected.ext.main_23.unk81 = 0x55;
        expected.ext.main_23.unk80 = slope(input->attribute, input->facing, 0x55);
        if (mode == SPIKE_VISIBLE)
            expected.state = 2;
    } else {
        func_800562AC(&skier);
        expected.x_pos.val += expected.x_speed;
        expected.animation_step.fields.duration--;
        next = slope(input->attribute, input->facing, 0x55);
        expected.ext.main_23.unk81 = 0x55;
        expected.ext.main_23.unk80 = next;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = &steps[1];
        expected.animation_step.packed = steps[1];
        if (next == 3 || (next & 0x80)) {
            expected.unk5 = 4;
            expected.unk6 = 0;
            expected.unk17 = (u8)(0x55 + 0xD);
        } else {
            expected.unk17 = (next & 0x7F) + 4;
        }
        if (input->flags & 2) {
            expected.unk5 = 5;
            expected.unk6 = 0;
            expected.ext.main_23.unk82 |= 1;
        }
        expected.unk7C--;
        if (expected.unk7C == 0 && !input->full) {
            struct VisualObj* visual = &want_visuals[VISUAL_SLOT];
            visual->active = 0x41;
            visual->id = 3;
            visual->unk2 = 5;
            visual->bg_offset = skier.bg_offset;
            visual->unk15 = skier.unk15;
            visual->unk40 = skier.unk40;
            visual->unk3C = (void*)skier.sprite_frames;
            visual->animation_table = (u32**)skier.animation_table;
            visual->unk42 = skier.unk42;
            visual->x_pos.i.hi = skier.x_pos.i.hi + 0x28;
            visual->y_pos.i.hi = (u16)skier.y_pos.i.hi + (s8)((u8*)D_800FCE9C)[next];
            visual->unk16 = skier.unk16;
            expected.unk7C = 5;
        }
    }
    for (i = 0; i < sizeof(skier) / 4; i++)
        difference |= ((u32*)&skier)[i] ^ ((u32*)&expected)[i];
    for (i = 0; i < sizeof(want_visuals) / 4; i++)
        difference |= ((u32*)visual_objects)[i] ^ ((u32*)want_visuals)[i];
    for (i = 0; i < 0x40; i++)
        difference |= misc_objects[i].active ^ 1;
    assert(difference == 0);
    return skier.ext.main_23.unk80 | ((u32)(u8)skier.state << 8) | ((u32)(u8)skier.unk5 << 16) | ((u32)skier.unk17 << 24);
}

#define CASE(name)                                   \
    static u32 slope_skier_steps_##name##_case(void) \
    {                                                \
        return slope_skier_steps_run(name);          \
    }
CASE(EMPTY)
CASE(LOW)
CASE(LOW_FACING)
CASE(LOW_STEEP)
CASE(LOW_STEEP_FACING)
CASE(HIGH)
CASE(HIGH_FACING)
CASE(HIGH_STEEP)
CASE(SPIKE_HIDDEN)
CASE(SPIKE_VISIBLE)
CASE(FLAT)
CASE(OTHER)
CASE(SKI_SPAWN)
CASE(SKI_FULL)
CASE(SKI_WALL)
CASE(SKI_DROP)
#define ENTRY(name) slope_skier_steps_##name##_case,
static const CTestCase slope_skier_steps_cases[]
    = {
          ENTRY(EMPTY) ENTRY(LOW) ENTRY(LOW_FACING) ENTRY(LOW_STEEP) ENTRY(LOW_STEEP_FACING) ENTRY(HIGH) ENTRY(HIGH_FACING) ENTRY(HIGH_STEEP)
              ENTRY(SPIKE_HIDDEN) ENTRY(SPIKE_VISIBLE) ENTRY(FLAT) ENTRY(OTHER) ENTRY(SKI_SPAWN) ENTRY(SKI_FULL) ENTRY(SKI_WALL) ENTRY(SKI_DROP)
      };
static const u32 slope_skier_steps_cases_expected[] = { 0x20103u, 0x20101u, 0x20181u, 0x20181u, 0x20101u, 0x20102u, 0x20182u, 0x20182u, 0x20155u, 0x20255u, 0x20155u, 0x20100u, 0x5020101u, 0x5020101u, 0x5050101u, 0x62040103u };
#undef VISUAL_SLOT
#undef CASE
#undef ENTRY

static struct MainObj ski, ski_expected;
static struct VisualObj ski_visuals_expected[32];
static struct EngineObj ski_engine_expected;
static struct PlayerObj ski_player_expected;
static u8 ski_tiles[128], ski_tiles_expected[128];
static u16 ski_pixels[512], ski_pixels_expected[512];
static u32 ski_attrs[2], ski_attrs_expected[2];
static u16 ski_random_expected;
#define SKI_WORDS(object) (sizeof(object) / 4)

static void ski_start(void)
{
    u32 i;
    c_test_zero_words((u32*)&engine_obj, SKI_WORDS(engine_obj));
    c_test_zero_words((u32*)&g_Player, SKI_WORDS(g_Player));
    c_test_zero_words((u32*)visual_objects, SKI_WORDS(visual_objects));
    engine_obj.substage = 1;
    ski.active = 0x41;
    ski.id = 23;
    ski.unk2 = 2;
    ski.x_pos.i.hi = 104;
    ski.y_pos.i.hi = 132;
    SP_CUR_MAIN_OBJ = &ski;
    ski_tiles[0] = 1;
    for (i = 256; i < 512; i++)
        ski_pixels[i] = 1;
    SP_BG_TILEMAP = ski_tiles;
    TEST_BG_TILE_PIXELS = (u8*)ski_pixels;
    TEST_BG_TILE_ATTRS = (u8*)ski_attrs;
    layout_size = 128;
    layout_width = 16;
    for (i = 0; i < 32; i++)
        visual_objects[i].active = 0x41;
    func_800564B4(&ski);
    assert(ski.unk15 == 0x40);
    assert(ski.terrain_box != NULL);
    assert(ski.unk5 == 1);
    ski_attrs[1] = 16;
    ski.unk6 = 1;
    ski.x_speed = FIXED(4.5);
    ski.collision_flags = 9;
    func_800562AC(&ski);
    assert(ski.unk5 == 5 && ski.unk6 == 0);
    assert((ski.ext.main_23.unk82 & 1) != 0);
}

static void ski_snapshot(void)
{
    ski_expected = ski;
    c_test_copy_words((u32*)ski_visuals_expected, (const u32*)visual_objects, SKI_WORDS(visual_objects));
    c_test_copy_words((u32*)ski_tiles_expected, (const u32*)ski_tiles, SKI_WORDS(ski_tiles));
    c_test_copy_words((u32*)ski_pixels_expected, (const u32*)ski_pixels, SKI_WORDS(ski_pixels));
    c_test_copy_words(ski_attrs_expected, ski_attrs, SKI_WORDS(ski_attrs));
    ski_engine_expected = engine_obj;
    ski_player_expected = g_Player;
    ski_random_expected = cur_random;
}

static void ski_check(void)
{
    assert(c_test_word_difference((const u32*)&ski, (const u32*)&ski_expected, SKI_WORDS(ski)) == 0);
    assert(c_test_word_difference((const u32*)visual_objects, (const u32*)ski_visuals_expected, SKI_WORDS(visual_objects)) == 0);
    assert(c_test_word_difference((const u32*)ski_tiles, (const u32*)ski_tiles_expected, SKI_WORDS(ski_tiles)) == 0);
    assert(c_test_word_difference((const u32*)ski_pixels, (const u32*)ski_pixels_expected, SKI_WORDS(ski_pixels)) == 0);
    assert(c_test_word_difference(ski_attrs, ski_attrs_expected, SKI_WORDS(ski_attrs)) == 0);
    assert(c_test_word_difference((const u32*)&engine_obj, (const u32*)&ski_engine_expected, SKI_WORDS(engine_obj)) == 0);
    assert(c_test_word_difference((const u32*)&g_Player, (const u32*)&ski_player_expected, SKI_WORDS(g_Player)) == 0);
    assert(SP_CUR_MAIN_OBJ == &ski);
    assert(SP_BG_TILEMAP == ski_tiles);
    assert(TEST_BG_TILE_PIXELS == (u8*)ski_pixels);
    assert(TEST_BG_TILE_ATTRS == (u8*)ski_attrs);
    assert(layout_size == 128 && layout_width == 16);
    assert(cur_random == ski_random_expected);
}
static const u32 func_80056054_1_expected[] = { 0x18010003u };
static u32 test_func_80056054_1(u32 row)
{
    struct VisualObj* trail;
    u32 observed, i;
    ski_start();
    for (i = 0; i < 6; i++)
        func_80056054(&ski);
    for (i = 0; i < 5; i++)
        visual_objects[i].active = 0;
    ski_snapshot();
    animate_object(ANIMATED_OBJECT(&ski_expected));
    move_object(MOVING_OBJECT(&ski_expected));
    assert(ski_expected.animation_step.fields.event == 2);
    ski_expected.animation_step.fields.event = 0;
    for (i = 0; i < 5; i++) {
        trail = &ski_visuals_expected[i];
        trail->active = 0x41;
        trail->id = 3;
        trail->unk2 = 5;
        trail->bg_offset = ski.bg_offset;
        trail->unk15 = ski.unk15 ^ 0x40;
        trail->unk40 = ski.unk40;
        trail->unk3C = (void*)ski.sprite_frames;
        trail->animation_table = (u32**)ski.animation_table;
        trail->unk42 = ski.unk42;
        trail->x_pos.i.hi = ski_expected.x_pos.i.hi - D_800FCE90[i].x;
        trail->y_pos.i.hi = (u16)ski_expected.y_pos.i.hi + D_800FCE90[i].y;
        trail->unk16 = ski.unk16;
    }
    func_80056054(&ski);
    ski_check();
    observed = ski.animation_step.packed;
    return c_test_observe(0, row, &observed, func_80056054_1_expected, 1);
}

static const u32 func_80056054_2_expected[] = { 1u };
static u32 test_func_80056054_2(u32 row)
{
    u32 observed, i;
    ski_start();
    for (i = 0; i < 60; i++)
        func_80056054(&ski);
    ski_snapshot();
    animate_object(ANIMATED_OBJECT(&ski_expected));
    move_object(MOVING_OBJECT(&ski_expected));
    assert(ski_expected.animation_step.fields.event == 1);
    ski_expected.unk5 = 1;
    ski_expected.unk6 = 0;
    ski_expected.ext.main_23.unk82 &= 0xFE;
    ski_expected.unk15 ^= 0x40;
    func_80056054(&ski);
    ski_check();
    observed = ski.unk5;
    return c_test_observe(0, row, &observed, func_80056054_2_expected, 1);
}

static const u32 func_800564B4_expected[] = { 0u, 0u, 1u, 0u, 0u, 0u, 0u, 3u, 1u, 0u, 6u, 0u, 0u, 1u, 0xAu, 0u, 0u, 0u };
static u32 test_func_800564B4(u32 row)
{
    u32 observed_values[18];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&slope_skier_terrain_box, 0, sizeof(slope_skier_terrain_box));
    obj.unk2 = -1;
    func_800564B4(&obj);
    observed_values[0] = (u32)obj.air_state;
    observed_values[1] = (u32)obj.bg_offset;
    observed_values[2] = (u32)obj.contact_damage;
    observed_values[3] = (u32)obj.ext.main_23.unk80;
    observed_values[4] = (u32)obj.ext.main_23.unk81;
    observed_values[5] = (u32)obj.ext.main_23.unk82;
    observed_values[6] = (u32)obj.gravity;
    observed_values[7] = (u32)obj.hp;
    observed_values[8] = (u32)obj.state;
    observed_values[9] = (u32)obj.unk15;
    observed_values[10] = (u32)obj.unk16;
    observed_values[11] = (u32)obj.unk18.val;
    observed_values[12] = (u32)obj.unk1C.val;
    observed_values[13] = (u32)obj.unk5;
    observed_values[14] = (u32)obj.unk7C;
    observed_values[15] = (u32)obj.x_accel;
    observed_values[16] = (u32)obj.x_speed;
    observed_values[17] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, func_800564B4_expected, 18);
}

#include "support/signed_init_defaults.h"
DEFAULTS_CASE(0, 1)
DEFAULTS_CASE(1, 1)
DEFAULTS_CASE(2, 1)
static const CTestCase slope_skier_signed_init_defaults_cases[] = { DEFAULTS_ENTRY(0, 1) DEFAULTS_ENTRY(1, 1) DEFAULTS_ENTRY(2, 1) };

static const u32 slope_skier_signed_init_defaults_cases_expected[] = { 0x3012001u, 0x3012001u, 0x3012001u };
const struct CTestGroup c_test_groups[] = {
    { "slope_skier_steps", slope_skier_steps_cases, slope_skier_steps_cases_expected, COUNT(slope_skier_steps_cases), 0 },
    { "func_80056054_1", 0, 0, 1, test_func_80056054_1 },
    { "func_80056054_2", 0, 0, 1, test_func_80056054_2 },
    { "func_800564B4", 0, 0, 1, test_func_800564B4 },
    { "slope_skier_signed_init_defaults", slope_skier_signed_init_defaults_cases, slope_skier_signed_init_defaults_cases_expected, COUNT(slope_skier_signed_init_defaults_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(slope_skier_steps_cases) + 1 + 1 + 1 + COUNT(slope_skier_signed_init_defaults_cases);
