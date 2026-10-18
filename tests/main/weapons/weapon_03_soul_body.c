#include "test_runtime.h"
#include "main/weapons/weapon_03_soul_body.h"
#include "main/player_animations.h"
#include "main/player_special.h"
#include "main/player.h"
#include "main/55C4.h"
extern s32 player_gfx_buf_0[1024];

static u32 cancel_case(u32 mode)
{
    struct WeaponObj obj, expected;
    struct PlayerObj player_before;
    u32 i;
    u8 palette_before = need_palette_load;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 3;
    obj.unk2 = 7;
    obj.on_screen = 1;
    obj.state = mode ? 1 : 2;
    obj.unk5 = 2;
    obj.unk6 = 3;
    obj.unk7 = 4;
    obj.unk50 = (const u8*)soul_body_hit_box;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    g_Player.weapon = mode == 3 ? 0 : 3;
    g_Player.hp = mode == 5 ? 0 : 16;
    g_Player.input_locked = mode == 1;
    g_Player.capsule_state = mode == 2;
    g_Player.actions_reset = mode == 4;
    g_Player.shot_count = 3;
    g_Player.special_shot_count = 2;
    expected = obj;
    player_before = g_Player;
    expected.active = expected.id = expected.unk2 = expected.on_screen = 0;
    expected.state = expected.unk5 = expected.unk6 = expected.unk7 = 0;
    expected.unk50 = NULL;
    player_before.shot_count = 2;
    player_before.special_shot_count = 1;
    soul_body_update(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(need_palette_load == palette_before);
    return (u8)obj.state | ((u32)(u8)player_before.shot_count << 8) | ((u32)(u8)player_before.special_shot_count << 16);
}
static const u32 soul_body_cancellation_dispatch_cases_expected[] = { 0x10200u, 0x10200u, 0x10200u, 0x10200u, 0x10200u, 0x10200u };

static u32 clone_case(u32 mode, u32 observation)
{
    struct PlayerObj player_before, entity_before;
    struct EngineObj engine_before;
    struct BackgroundObj bg_before[3];
    u32 i, actual;
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&g_Entity, 0, sizeof(g_Entity));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    g_Player.bg_offset = 0;
    g_Player.weapon = 3;
    g_Player.hp = 20;
    g_Player.controlling_clone = 1;
    g_Player.spike_immune = 1;
    g_Entity.active = 0x41;
    g_Entity.on_screen = 1;
    g_Entity.state = 3;
    g_Entity.unk5 = 0x25;
    g_Entity.clone_timer = 60;
    g_Entity.unk70 = 0x35;
    g_Entity.touching_spikes = 0x27;
    g_Entity.x_pos.val = 5 * 65536 + 0x1357;
    g_Entity.y_pos.val = 10 * 65536 + 0x2468;
    g_Entity.unk18.val = 0x24681357;
    g_Entity.unk1C.val = 0x13572468;
    g_Entity.previous_animation_index = 0x2A;
    g_Entity.animation_step.fields.frame_index = 0x2A;
    background_objects[0].x_pos.i.hi = 10;
    background_objects[0].y_pos.i.hi = 20;
    engine_obj.controlled_player = &g_Player;
    if (mode == 0) {
        g_Player.capsule_state = 1;
        g_Player.weapon = 0;
        g_Player.actions_reset = 1;
        g_Player.hp = 0;
        g_Entity.y_pos.i.hi = 348;
    }
    player_before = g_Player;
    entity_before = g_Entity;
    engine_before = engine_obj;
    memcpy(bg_before, background_objects, sizeof(bg_before));
    soul_body_clone_update();
    player_before.controlling_clone = g_Player.controlling_clone;
    player_before.spike_immune = g_Player.spike_immune;
    entity_before.active = g_Entity.active;
    entity_before.on_screen = g_Entity.on_screen;
    entity_before.x_pos = g_Entity.x_pos;
    entity_before.y_pos = g_Entity.y_pos;
    entity_before.unk18 = g_Entity.unk18;
    entity_before.unk1C = g_Entity.unk1C;
    entity_before.unk70 = g_Entity.unk70;
    entity_before.touching_spikes = g_Entity.touching_spikes;
    engine_before.controlled_player = engine_obj.controlled_player;
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(g_Entity) / 4; i++)
        assert(((u32*)&g_Entity)[i] == ((u32*)&entity_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(bg_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)bg_before)[i]);
    assert(engine_obj.controlled_player == &g_Player || engine_obj.controlled_player == &g_Entity);
    switch (observation) {
    case 0:
        actual = (u8)g_Entity.active | ((u32)g_Entity.on_screen << 8) | ((u32)(u8)g_Player.controlling_clone << 16) | ((u32)(u8)g_Player.spike_immune << 24);
        break;
    case 1:
        actual = g_Entity.x_pos.val;
        break;
    case 2:
        actual = g_Entity.y_pos.val;
        break;
    case 3:
        actual = g_Entity.unk18.val;
        break;
    case 4:
        actual = g_Entity.unk1C.val;
        break;
    default:
        actual = (u8)g_Entity.unk70 | ((u32)(u8)g_Entity.touching_spikes << 8) | ((u32)(engine_obj.controlled_player == &g_Entity) << 16);
        break;
    }
    return actual;
}
static const u32 soul_clone_context_cases_expected[] = { 0x0u, 0x51357u, 0x15C2468u, 0x24681357u, 0x13572468u, 0x2735u, 0x1010141u, 0xA1357u, 0x142468u, 0x51357u, 0xA2468u, 0x10000u };
static u32 soul_clone_context_cases_row(u32 row)
{
    return clone_case(row / 6, row % 6);
}

static struct {
    u32 frames[256];
    u16 stream[6];
} clone_graphics;
static s32 clone_sprite_archive[2] = { 4, 0x12345678 };
static struct RectPtrPair clone_rects[4];

struct CloneExpected {
    struct PlayerObj player, entity;
    struct EngineObj engine;
    struct BackgroundObj backgrounds[3];
    struct RectPtrPair rects[4];
    struct RectPtrPair* rect_end;
};

static void clone_reset(u32 background)
{
    static const s16 origins[3][2] = { { -20, 40 }, { 100, 80 }, { -180, -60 } };
    static const u16 stream[6] = { 0xC000, 0, 64, 0, 0, 0 };
    u32 i;
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&g_Entity, 0, sizeof(g_Entity));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    memset(clone_rects, 0x5A, sizeof(clone_rects));
    for (i = 0; i < 3; i++) {
        background_objects[i].x_pos.val = origins[i][0] * 65536 + 0x1357;
        background_objects[i].y_pos.val = origins[i][1] * 65536 + 0x2468;
    }
    for (i = 0; i < COUNT(clone_graphics.frames); i++)
        clone_graphics.frames[i] = 0x100400;
    memcpy(clone_graphics.stream, stream, sizeof(stream));
    for (i = 0; i < 34; i++)
        player_gfx_buf_1[1023 + i] = 0x5A5A5A5A;
    TEST_SPRITE_FRAMES = (u8*)clone_sprite_archive;
    vram_rect_ptr = clone_rects;
    need_palette_load = 0x80;
    g_Player.bg_offset = background;
    g_Player.weapon = 3;
    g_Player.hp = 20;
    g_Player.controlling_clone = 1;
    g_Player.spike_immune = 1;
    g_Player.x_pos.val = 100 * 65536 + 0x1234;
    g_Player.y_pos.val = 120 * 65536 + 0x5678;
    g_Entity.active = 0x41;
    g_Entity.on_screen = 1;
    g_Entity.state = PLAYER_STATE_NORMAL;
    g_Entity.unk5 = PLAYER_SOUL_BODY_CLONE;
    g_Entity.is_clone = 1;
    g_Entity.air_state = 1;
    g_Entity.hp = 20;
    g_Entity.clone_timer = 240;
    g_Entity.unk70 = 0x35;
    g_Entity.unk71 = 2;
    g_Entity.touching_spikes = 0x27;
    g_Entity.shot_fired = 1;
    g_Entity.attack_ended = 1;
    g_Entity.actions_reset = 1;
    g_Entity.x_pos.val = (origins[background][0] + 120) * 65536 + 0x1234;
    g_Entity.y_pos.val = (origins[background][1] + 100) * 65536 + 0x5678;
    g_Entity.unk18.val = 0x13572468;
    g_Entity.unk1C.val = 0x24681357;
    g_Entity.x_vel.val = 0x18000;
    g_Entity.y_vel.val = -0x24000;
    g_Entity.animation_table = (u32**)D_80119DF0;
    set_animation(&g_Entity, 0x61);
    g_Entity.previous_animation_index = 0x60;
    g_Entity.unk38 = (s32*)clone_graphics.frames;
    g_Entity.unk49 = 1;
    engine_obj.controlled_player = &g_Player;
    engine_obj.unk4 = 0x2468;
    engine_obj.unk10 = 1;
}

static void clone_snapshot(struct CloneExpected* expected)
{
    expected->player = g_Player;
    expected->entity = g_Entity;
    expected->engine = engine_obj;
    memcpy(expected->backgrounds, background_objects, sizeof(expected->backgrounds));
    memcpy(expected->rects, clone_rects, sizeof(expected->rects));
    expected->rect_end = clone_rects;
}

static void clone_expect_normal(struct CloneExpected* expected)
{
    expected->engine.controlled_player = &g_Entity;
    expected->entity.unk18 = expected->entity.x_pos;
    expected->entity.unk1C = expected->entity.y_pos;
    expected->entity.unk88.bytes.collision_flags = 0x37;
    expected->entity.shot_fired = 0;
    expected->entity.attack_ended = 0;
    expected->entity.actions_reset = 0;
}

static void clone_expect_decode(struct CloneExpected* expected)
{
    expected->entity.previous_animation_index = expected->entity.animation_step.fields.frame_index;
    expected->rects[0].rect.x = 320;
    expected->rects[0].rect.y = 64;
    expected->rects[0].rect.w = 4;
    expected->rects[0].rect.h = 16;
    expected->rects[0].ptr = (u_long*)&player_gfx_buf_1[1024];
    expected->rects[1].ptr = NULL;
    expected->rect_end = &clone_rects[1];
}

static void clone_check(const struct CloneExpected* expected)
{
    static const u16 stream[6] = { 0xC000, 0, 64, 0, 0, 0 };
    u32 i;
    c_test_same_words(&g_Player, &expected->player, sizeof(g_Player));
    c_test_same_words(&g_Entity, &expected->entity, sizeof(g_Entity));
    c_test_same_words(&engine_obj, &expected->engine, sizeof(engine_obj));
    c_test_same_words(background_objects, expected->backgrounds, sizeof(expected->backgrounds));
    c_test_same_words(clone_rects, expected->rects, sizeof(clone_rects));
    assert(vram_rect_ptr == expected->rect_end);
    assert(need_palette_load == 0x80);
    assert(TEST_SPRITE_FRAMES == (u8*)clone_sprite_archive);
    assert(clone_sprite_archive[0] == 4 && clone_sprite_archive[1] == 0x12345678);
    for (i = 0; i < COUNT(clone_graphics.frames); i++)
        assert(clone_graphics.frames[i] == 0x100400);
    c_test_same_words(clone_graphics.stream, stream, sizeof(stream));
    for (i = 0; i < 34; i++) {
        s32 word = expected->rect_end != clone_rects && i > 0 && i < 33 ? 0 : 0x5A5A5A5A;
        assert(player_gfx_buf_1[1023 + i] == word);
    }
}

static u32 test_clone_cancel_guards(u32 row)
{
    struct CloneExpected expected;
    u32 mode = row / 3;
    clone_reset(row % 3);
    switch (mode) {
    case 0:
        g_Entity.active = 0;
        break;
    case 1:
        g_Player.input_locked = 1;
        break;
    case 2:
        g_Player.capsule_state = 1;
        break;
    case 3:
        g_Player.weapon = 0;
        break;
    case 4:
        g_Player.actions_reset = 1;
        break;
    case 5:
        g_Player.hp = 0;
        break;
    case 6:
        g_Entity.y_pos.i.hi = background_objects[row % 3].y_pos.i.hi + 328;
        break;
    }
    clone_snapshot(&expected);
    if (mode != 0) {
        expected.entity.active = 0;
        expected.entity.on_screen = 0;
        expected.player.controlling_clone = 0;
        expected.player.spike_immune = 0;
    }
    soul_body_clone_update();
    clone_check(&expected);
    return 1;
}

static u32 test_clone_screen_bounds(u32 row)
{
    static const s16 x_offsets[6] = { -1, 0, 1, 319, 320, 321 };
    static const s16 x_results[6] = { 0, 0, 1, 319, 320, 320 };
    static const s16 y_offsets[4] = { -1, 0, 1, 327 };
    static const s16 y_results[4] = { 0, 0, 1, 327 };
    struct CloneExpected expected;
    u32 x = row / 8, y = row / 2 % 4, fraction = row % 2;
    s16 left, top;
    clone_reset(row % 3);
    left = background_objects[row % 3].x_pos.i.hi;
    top = background_objects[row % 3].y_pos.i.hi;
    g_Entity.x_pos.val = (left + x_offsets[x]) * 65536 + (fraction ? 0x1357 : 0);
    g_Entity.y_pos.val = (top + y_offsets[y]) * 65536 + (fraction ? 0x2468 : 0);
    clone_snapshot(&expected);
    clone_expect_normal(&expected);
    expected.entity.clone_timer = 239;
    expected.entity.unk70 = 0;
    expected.entity.touching_spikes = 0;
    expected.entity.x_pos.i.hi = left + x_results[x];
    expected.entity.y_pos.i.hi = top + y_results[y];
    soul_body_clone_update();
    clone_check(&expected);
    return 1;
}

static u32 test_clone_timer_boundaries(u32 row)
{
    static const u16 timers[7] = { 1, 2, 59, 60, 61, 240, 0 };
    static const u16 results[7] = { 0, 1, 58, 59, 60, 239, 0 };
    struct CloneExpected expected;
    u32 index = row / 2;
    clone_reset(row % 3);
    g_Entity.on_screen = row % 2;
    g_Entity.clone_timer = timers[index];
    if (index == 6) {
        g_Entity.unk5 = PLAYER_SOUL_BODY_VANISH;
        set_animation(&g_Entity, 0x62);
        g_Entity.previous_animation_index = 0xD0;
    }
    clone_snapshot(&expected);
    clone_expect_normal(&expected);
    expected.entity.clone_timer = results[index];
    expected.entity.unk70 = 0;
    expected.entity.touching_spikes = 0;
    if (index == 0) {
        expected.entity.unk5 = PLAYER_SOUL_BODY_VANISH;
        expected.entity.on_screen = 1;
        expected.entity.unk17 = 0x62;
        expected.entity.unk3C = (u8*)&clone_sprite_archive[1];
        expected.entity.animation_cursor = (u32*)D_80119DF0[0x62];
        expected.entity.animation_step.packed = 0xD0010003;
        clone_expect_decode(&expected);
    } else if (index >= 1 && index <= 3) {
        expected.entity.on_screen ^= 1;
    }
    soul_body_clone_update();
    clone_check(&expected);
    return 1;
}

static u32 test_clone_vanish_transitions(u32 row)
{
    static const u8 starts[8] = { 0, 0, 0, 1, 1, 2, 3, 4 };
    static const u8 durations[8] = { 0, 2, 1, 2, 1, 1, 1, 1 };
    static const u8 ends[8] = { 0, 0, 1, 1, 2, 3, 4, 5 };
    static const u32 frames[8] = {
        0xD0010002,
        0xD0010001,
        0xD1010002,
        0xD1010001,
        0xD2010001,
        0xD3010001,
        0xD4010001,
        0xD4000060,
    };
    struct CloneExpected expected;
    clone_reset(row % 3);
    engine_obj.unk10 = 0;
    g_Entity.clone_timer = row == 0 ? 1 : 0;
    if (row != 0) {
        g_Entity.unk5 = PLAYER_SOUL_BODY_VANISH;
        g_Entity.unk17 = 0x62;
        g_Entity.unk3C = (u8*)&clone_sprite_archive[1];
        g_Entity.animation_cursor = (u32*)&D_80119DF0[0x62][starts[row]];
        g_Entity.animation_step.packed = D_80119DF0[0x62][starts[row]];
        g_Entity.animation_step.fields.duration = durations[row];
        g_Entity.previous_animation_index = g_Entity.animation_step.fields.frame_index;
    }
    clone_snapshot(&expected);
    clone_expect_normal(&expected);
    expected.entity.clone_timer = 0;
    expected.entity.unk5 = PLAYER_SOUL_BODY_VANISH;
    expected.entity.unk17 = 0x62;
    expected.entity.unk3C = (u8*)&clone_sprite_archive[1];
    expected.entity.animation_cursor = (u32*)&D_80119DF0[0x62][ends[row]];
    expected.entity.animation_step.packed = frames[row];
    expected.entity.unk71 = 0;
    if (row == 7) {
        expected.entity.active = 0;
        expected.entity.on_screen = 0;
        expected.player.controlling_clone = 0;
        expected.player.spike_immune = 0;
    } else {
        expected.entity.unk70 = 0;
        expected.entity.touching_spikes = 0;
        if (row != 1 && row != 3)
            clone_expect_decode(&expected);
    }
    soul_body_clone_update();
    clone_check(&expected);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "clone_cancel_guards", 0, 0, 6, test_clone_cancel_guards },
    { "clone_screen_bounds", 0, 0, 34, test_clone_screen_bounds },
    { "clone_timer_boundaries", 0, 0, 4, test_clone_timer_boundaries },
    { "clone_vanish_transitions", 0, 0, 8, test_clone_vanish_transitions },
    { "soul_body_cancellation_dispatch", NULL, soul_body_cancellation_dispatch_cases_expected, COUNT(soul_body_cancellation_dispatch_cases_expected), cancel_case },
    { "soul_clone_context", NULL, soul_clone_context_cases_expected, COUNT(soul_clone_context_cases_expected), soul_clone_context_cases_row },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 6 + 34 + 4 + 8 + COUNT(soul_body_cancellation_dispatch_cases_expected) + COUNT(soul_clone_context_cases_expected);
