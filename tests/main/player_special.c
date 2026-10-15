#include "test_runtime.h"

static u8 tilemap[256];
static u16 pixels[512];
static u32 attributes[1];
static s32 gfx_archive[4] = { 8, 12, 0x11223344, 0x55667788 };
static s32 zero_shippuuga_cancel_context_sprite_archive[12] = { 24, 28, 32, 36, 40, 44, 1, 2, 3, 4, 5, 6 };
static Palette zero_shippuuga_cancel_context_palette_bank[1];
static u16 zero_shippuuga_cancel_context_palette_storage[18];
static u32 cancel_case(u32 mode, u32 observation)
{
    struct PlayerObj* obj = &g_Player;
    struct PlayerObj before;
    struct EngineObj engine_before;
    struct WeaponObj pool_before[16];
    struct BackgroundObj bg_before[3];
    struct Unk_unk68 bounds = { 0, 0, 4, 4 };
    s32 result;
    u32 i, actual;
    memset(obj, 0, sizeof(*obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    for (i = 0; i < COUNT(weapon_objects); i++)
        weapon_objects[i].active = 1;
    obj->active = 0x41;
    obj->unk2 = 1;
    obj->state = 1;
    obj->unk5 = PLAYER_ZERO_SHIPPUUGA;
    obj->unk6 = 1;
    obj->attacking = 1;
    obj->voice_timer = 1;
    obj->unk68 = &bounds;
    obj->x_pos.val = 100 * 65536 + 0x1234;
    obj->y_pos.val = 200 * 65536 + 0x5678;
    obj->animation_table = (u32**)D_8011AFF0;
    set_animation(obj, 0x68);
    obj->animation_step.fields.event = 0x40;
    if (mode == 0)
        obj->input_locked = 1;
    if (mode == 1)
        obj->input.buttons.held = PLAYER_INPUT_UP;
    if (mode == 2) {
        obj->boss_flags = 1;
        obj->pressed_input = PLAYER_INPUT_SPECIAL;
    }
    if (mode == 3)
        obj->pressed_input = PLAYER_INPUT_SHOOT;
    need_palette_load = 0x80;
    for (i = 0; i < 16; i++)
        zero_shippuuga_cancel_context_palette_bank[0][i] = 0x1200 + i;
    for (i = 0; i < 18; i++)
        zero_shippuuga_cancel_context_palette_storage[i] = 0xBEEF;
    for (i = 0; i < 2; i++)
        D_8013E198[i] = -1;
    memset(tilemap, 1, sizeof(tilemap));
    memset(pixels, 0, sizeof(pixels));
    attributes[0] = 0x20;
    SP_BG_TILEMAP = tilemap;
    layout_width = 16;
    layout_size = 256;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    TEST_PLAYER_GFX = (u8*)gfx_archive;
    TEST_SPRITE_FRAMES = (u8*)zero_shippuuga_cancel_context_sprite_archive;
    TEST_PALETTE = (u8*)&zero_shippuuga_cancel_context_palette_storage[1];
    TEST_PALETTE_BANK = (u8*)zero_shippuuga_cancel_context_palette_bank;
    before = *obj;
    engine_before = engine_obj;
    memcpy(pool_before, weapon_objects, sizeof(pool_before));
    memcpy(bg_before, background_objects, sizeof(bg_before));
    result = player_zero_shippuuga_cancel(obj);
    if (mode != 0) {
        before.unk5 = obj->unk5;
        before.unk6 = obj->unk6;
        before.attacking = obj->attacking;
        before.air_state = obj->air_state;
        before.dash_momentum = obj->dash_momentum;
        before.air_action = obj->air_action;
        before.x_pos = obj->x_pos;
        before.y_pos = obj->y_pos;
        before.x_vel = obj->x_vel;
        before.y_vel = obj->y_vel;
        before.unk28 = obj->unk28;
        before.unk2C = obj->unk2C;
        before.unk17 = obj->unk17;
        before.previous_animation_index = 0xFF;
        before.animation_step = obj->animation_step;
        before.animation_cursor = obj->animation_cursor;
        before.unk38 = SP_ARCHIVE_ENTRY(SP_PLAYER_GFX, D_8011AF60[obj->unk17] ? 1 : 0);
        before.unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, D_8011AF60[obj->unk17] ? 5 : 0);
    }
    for (i = 0; i < sizeof(*obj); i++)
        assert(((u8*)obj)[i] == ((u8*)&before)[i]);
    for (i = 0; i < sizeof(engine_obj); i++)
        assert(((u8*)&engine_obj)[i] == ((u8*)&engine_before)[i]);
    for (i = 0; i < sizeof(pool_before); i++)
        assert(((u8*)weapon_objects)[i] == ((u8*)pool_before)[i]);
    for (i = 0; i < sizeof(bg_before); i++)
        assert(((u8*)background_objects)[i] == ((u8*)bg_before)[i]);
    for (i = 0; i < COUNT(tilemap); i++)
        assert(tilemap[i] == 1);
    for (i = 0; i < COUNT(pixels); i++)
        assert(pixels[i] == 0);
    assert(attributes[0] == 0x20 && gfx_archive[0] == 8 && gfx_archive[1] == 12);
    assert(bounds.unk0 == 0 && bounds.unk1 == 0 && bounds.unk2 == 4 && bounds.unk3 == 4);
    for (i = 0; i < 6; i++)
        assert(zero_shippuuga_cancel_context_sprite_archive[i] == 24 + i * 4 && zero_shippuuga_cancel_context_sprite_archive[i + 6] == i + 1);
    assert(zero_shippuuga_cancel_context_palette_storage[0] == 0xBEEF && zero_shippuuga_cancel_context_palette_storage[17] == 0xBEEF);
    for (i = 0; i < 16; i++) {
        assert(zero_shippuuga_cancel_context_palette_bank[0][i] == 0x1200 + i);
        assert(zero_shippuuga_cancel_context_palette_storage[i + 1] == (mode == 1 ? 0x1200 + i : 0xBEEF));
    }
    assert(need_palette_load == (mode == 1 ? 0x81 : 0x80));
    switch (observation) {
    case 0:
        actual = (u8)result | ((u32)(u8)obj->unk5 << 8) | ((u32)(u8)obj->unk6 << 16) | ((u32)(u8)obj->attacking << 24);
        break;
    case 1:
        actual = obj->x_pos.val;
        break;
    case 2:
        actual = obj->y_pos.val;
        break;
    case 3:
        actual = obj->x_vel.val;
        break;
    case 4:
        actual = obj->y_vel.val;
        break;
    case 5:
        actual = (u8)obj->air_state | ((u32)(u8)obj->air_action << 8) | ((u32)(u8)obj->dash_momentum << 16);
        break;
    case 6:
        actual = obj->animation_step.packed;
        break;
    case 7:
        actual = obj->unk28;
        break;
    case 8:
        actual = obj->unk2C;
        break;
    default:
        actual = (u8)obj->unk17 | ((u32)obj->previous_animation_index << 8) | ((u32)(obj->animation_cursor - (u32*)D_8011AFF0[(u8)obj->unk17]) << 16);
        break;
    }
    for (i = 0; i < 2; i++)
        assert(D_8013E198[i] == -1);
    return actual;
}
#define CASE(m, n)                                                  \
    static u32 zero_shippuuga_cancel_context_cancel_##m##_##n(void) \
    {                                                               \
        return cancel_case(m, n);                                   \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1) CASE(m, 2) CASE(m, 3) CASE(m, 4) CASE(m, 5) CASE(m, 6) CASE(m, 7) CASE(m, 8) CASE(m, 9)
MODE(0)
MODE(1)
MODE(2)
MODE(3)
#define ENTRY(m, n) zero_shippuuga_cancel_context_cancel_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1) ENTRY(m, 2) ENTRY(m, 3) ENTRY(m, 4) ENTRY(m, 5) ENTRY(m, 6) ENTRY(m, 7) ENTRY(m, 8) ENTRY(m, 9)
static const CTestCase zero_shippuuga_cancel_context_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) ENTRIES(3) };
static const u32 zero_shippuuga_cancel_context_cases_expected[] = { 0x1013B00u, 0x641234u, 0xC85678u, 0x0u, 0x0u, 0x0u, 0x9B014001u, 0x0u, 0x0u, 0xFF68u, 0xE01u, 0x680000u, 0xC80000u, 0x0u, 0x10000u, 0x1u, 0xC2010003u, 0x0u, 0x0u, 0xFF1Bu, 0x1013501u, 0x641234u, 0xC85678u, 0x0u, 0x0u, 0x0u, 0x56010002u, 0x0u, 0x0u, 0xFF5Fu, 0x1013001u, 0x641234u, 0xC85678u, 0x0u, 0x0u, 0x0u, 0x3D010001u, 0x0u, 0x0u, 0xFF58u };
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

static const u32 player_hover_steer_expected[] = { 0u, 1u, 0u, 0u };
static u32 test_player_hover_steer(u32 row)
{
    u32 observed_values[4];
    struct PlayerObj obj;
    s32 return_value;
    memset(&obj, 0, sizeof(obj));
    obj.input.buttons.held = 514;
    obj.unk88.bytes.collision_flags = 2;
    return_value = player_hover_steer(&obj);
    observed_values[0] = (u32)return_value;
    observed_values[1] = (u32)obj.hover_bob;
    observed_values[2] = (u32)obj.x_vel.val;
    observed_values[3] = (u32)obj.y_pos.i.hi;
    return c_test_observe(0, row, observed_values, player_hover_steer_expected, 4);
}

struct player_nova_strike_hit_wall_case {
    u32 collision_flags, unk15;
    u32 expected[5];
};
static const struct player_nova_strike_hit_wall_case player_nova_strike_hit_wall_cases[] = {
    { 0, 0, { 0u, 0u, 0u, 0u, 0u } },
    { 5, 255, { 1u, 0u, 0u, 0u, 0u } },
};
static u32 test_player_nova_strike_hit_wall(u32 row)
{
    const struct player_nova_strike_hit_wall_case* c = &player_nova_strike_hit_wall_cases[row];
    u32 observed_values[5];
    struct PlayerObj obj;
    s32 return_value;
    memset(&obj, 0, sizeof(obj));
    obj.unk88.bytes.collision_flags = c->collision_flags;
    obj.unk15 = c->unk15;
    return_value = player_nova_strike_hit_wall(&obj);
    observed_values[0] = (u32)return_value;
    observed_values[1] = (u32)obj.unk28;
    observed_values[2] = (u32)obj.unk2C;
    observed_values[3] = (u32)obj.x_vel.val;
    observed_values[4] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

static const u32 player_rising_fire_charged_start_expected[] = { 0x7Fu, 0xFFFFC000u, 0x4200u, 1u, 0xFFFC0000u, 0x6C000u };
static u32 test_player_rising_fire_charged_start(u32 row)
{
    u32 observed_values[6];
    struct PlayerObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.animation_step.fields.event = -1;
    player_rising_fire_charged_start(&obj);
    observed_values[0] = (u32)obj.animation_step.fields.event;
    observed_values[1] = (u32)obj.unk28;
    observed_values[2] = (u32)obj.unk2C;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.x_vel.val;
    observed_values[5] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, player_rising_fire_charged_start_expected, 6);
}

struct player_zero_hyouretsuzan_start_case {
    u32 input_locked, held, event;
    u32 expected[8];
};
static const struct player_zero_hyouretsuzan_start_case player_zero_hyouretsuzan_start_cases[] = {
    { -1, 0, 0, { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 0, 771, 16, { 0xFFFFFFFFu, 0u, 0x40u, 0u, 0x4200u, 1u, 0u, 0xFFFD0000u } },
};
static u32 test_player_zero_hyouretsuzan_start(u32 row)
{
    const struct player_zero_hyouretsuzan_start_case* c = &player_zero_hyouretsuzan_start_cases[row];
    u32 observed_values[8];
    struct PlayerObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    obj.input_locked = c->input_locked;
    obj.input.buttons.held = c->held;
    obj.animation_step.fields.event = c->event;
    player_zero_hyouretsuzan_start(&obj);
    observed_values[0] = (u32)obj.air_state;
    observed_values[1] = (u32)obj.animation_step.fields.event;
    observed_values[2] = (u32)obj.unk15;
    observed_values[3] = (u32)obj.unk28;
    observed_values[4] = (u32)obj.unk2C;
    observed_values[5] = (u32)obj.unk6;
    observed_values[6] = (u32)obj.x_vel.val;
    observed_values[7] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, c->expected, 8);
}

#include "support/player_archive_context.h"
ARCHIVE_CLONE(0, 0)
ARCHIVE_CLONE(0, 1)
ARCHIVE_CLONE(1, 0)
ARCHIVE_CLONE(1, 1)
ARCHIVE_CLONE(2, 0)
ARCHIVE_CLONE(2, 1)
ARCHIVE_CLONE(3, 0)
ARCHIVE_CLONE(3, 1)
static const CTestCase soul_body_clone_archive_cases[]
    = { ARCHIVE_CLONE_ENTRY(0, 0) ARCHIVE_CLONE_ENTRY(0, 1) ARCHIVE_CLONE_ENTRY(1, 0) ARCHIVE_CLONE_ENTRY(1, 1) ARCHIVE_CLONE_ENTRY(2, 0) ARCHIVE_CLONE_ENTRY(2, 1) ARCHIVE_CLONE_ENTRY(3, 0) ARCHIVE_CLONE_ENTRY(3, 1) };

static const u32 soul_body_clone_archive_cases_expected[] = { 0x6C2468u, 0x100907u, 0x12C2468u, 0x80007u, 0x12C2468u, 0x80002u, 0x242468u, 0x400007u };
const struct CTestGroup c_test_groups[] = {
    { "zero_shippuuga_cancel_context", zero_shippuuga_cancel_context_cases, zero_shippuuga_cancel_context_cases_expected, COUNT(zero_shippuuga_cancel_context_cases), 0 },
    { "player_hover_steer", 0, 0, 1, test_player_hover_steer },
    { "player_nova_strike_hit_wall", 0, 0, 2, test_player_nova_strike_hit_wall },
    { "player_rising_fire_charged_start", 0, 0, 1, test_player_rising_fire_charged_start },
    { "player_zero_hyouretsuzan_start", 0, 0, 2, test_player_zero_hyouretsuzan_start },
    { "soul_body_clone_archive", soul_body_clone_archive_cases, soul_body_clone_archive_cases_expected, COUNT(soul_body_clone_archive_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(zero_shippuuga_cancel_context_cases) + 1 + 2 + 1 + 2 + COUNT(soul_body_clone_archive_cases);
