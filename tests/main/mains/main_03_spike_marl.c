#include "test_runtime.h"
#include "main/mains/main_03_spike_marl.h"
#include "main/195B4.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "support/state_cases.h"
void spike_marl_detect_player(struct MainObj* arg0);
void spike_marl_resume_step(struct MainObj* arg0);
extern union AnimationStep* D_800F9E1C[13];
extern struct Unk_unk68 spike_marl_terrain_box;

static struct spike_marl_ahead_collision_PatrolInput {
    s16 timer;
    u8 tile, ahead, facing, collision, turn;
    s16 player_x;
};
static const struct spike_marl_ahead_collision_PatrolInput spike_marl_ahead_collision_inputs[] = {
    { 0, 1, 1, 0, 2, 1, 50 },
    { 0, 1, 1, 0x40, 1, 1, 150 },
};
static u8 spike_marl_ahead_collision_tilemap[256];
static u16 spike_marl_ahead_collision_pixels[512];
static u32 spike_marl_ahead_collision_attributes[1];
static u32 spike_marl_ahead_collision_patrol_case(u32 mode)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    const struct spike_marl_ahead_collision_PatrolInput* input = &spike_marl_ahead_collision_inputs[mode];
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(spike_marl_ahead_collision_tilemap, 1, sizeof(spike_marl_ahead_collision_tilemap));
    memset(spike_marl_ahead_collision_pixels, 0, sizeof(spike_marl_ahead_collision_pixels));
    spike_marl_ahead_collision_attributes[0] = input->tile;
    SP_BG_TILEMAP = spike_marl_ahead_collision_tilemap;
    layout_width = 16;
    layout_size = 256;
    TEST_BG_TILE_PIXELS = (u8*)spike_marl_ahead_collision_pixels;
    TEST_BG_TILE_ATTRS = (u8*)spike_marl_ahead_collision_attributes;
    obj.active = 0x41;
    obj.id = 3;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 0x27;
    obj.bg_offset = 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 80 * 65536 + 0x5678;
    obj.unk7C = input->timer;
    obj.unk15 = input->facing;
    obj.collision_flags = input->collision;
    obj.terrain_box = &spike_marl_terrain_box;
    obj.ext.main_3.player_ahead = input->ahead;
    obj.ext.main_3.turn_timer = 0x25;
    obj.animation_table = (const u8* const*)D_800F9E1C;
    set_animation(&obj, 0);
    g_Player.x_pos.i.hi = input->player_x;
    before = obj;
    player_before = g_Player;
    spike_marl_check_patrol_path(&obj);
    if (input->timer)
        before.unk7C--;
    if (input->turn) {
        before.unk5 = 3;
        before.unk6 = 0;
        before.ext.main_3.turn_timer = input->ahead ? 0x3C : 0x78;
        if (input->ahead)
            before.ext.main_3.player_ahead = 0;
        before.unk17 = 2;
        before.previous_animation_index = 0xFF;
        before.animation_cursor = (const u8*)D_800F9E1C[2];
        before.animation_step = *D_800F9E1C[2];
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(spike_marl_ahead_collision_tilemap); i++)
        assert(spike_marl_ahead_collision_tilemap[i] == 1);
    for (i = 0; i < COUNT(spike_marl_ahead_collision_pixels); i++)
        assert(spike_marl_ahead_collision_pixels[i] == 0);
    assert(spike_marl_ahead_collision_attributes[0] == input->tile && layout_width == 16 && layout_size == 256);
    return (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)obj.ext.main_3.turn_timer << 16);
}
static const u32 spike_marl_ahead_collision_cases_expected[] = { 0x3C0003u, 0x3C0003u };

static struct spike_marl_patrol_terrain_PatrolInput {
    s16 timer;
    u8 tile, ahead, facing, collision, turn;
    s16 player_x;
};
static const struct spike_marl_patrol_terrain_PatrolInput spike_marl_patrol_terrain_inputs[] = {
    { 1, 1, 0, 0, 0, 0, 100 },
    { -1, 1, 0, 0, 0, 0, 100 },
    { 0, 0, 0, 0, 0, 1, 100 },
    { 0, 1, 0, 0, 0, 0, 100 },
    { 0, 1, 0, 0, 2, 1, 100 },
    { 0, 1, 0, 0x40, 1, 1, 100 },
    { 0, 1, 1, 0, 0, 0, 50 },
    { 0, 1, 1, 0x40, 0, 0, 150 },
    { 0, 1, 1, 0, 0, 1, 150 },
    { 0, 1, 1, 0x40, 0, 1, 50 },
};
static u8 spike_marl_patrol_terrain_tilemap[256];
static u16 spike_marl_patrol_terrain_pixels[512];
static u32 spike_marl_patrol_terrain_attributes[1];
static u32 spike_marl_patrol_terrain_patrol_case(u32 mode)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    const struct spike_marl_patrol_terrain_PatrolInput* input = &spike_marl_patrol_terrain_inputs[mode];
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(spike_marl_patrol_terrain_tilemap, 1, sizeof(spike_marl_patrol_terrain_tilemap));
    memset(spike_marl_patrol_terrain_pixels, 0, sizeof(spike_marl_patrol_terrain_pixels));
    spike_marl_patrol_terrain_attributes[0] = input->tile;
    SP_BG_TILEMAP = spike_marl_patrol_terrain_tilemap;
    layout_width = 16;
    layout_size = 256;
    TEST_BG_TILE_PIXELS = (u8*)spike_marl_patrol_terrain_pixels;
    TEST_BG_TILE_ATTRS = (u8*)spike_marl_patrol_terrain_attributes;
    obj.active = 0x41;
    obj.id = 3;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 0x27;
    obj.bg_offset = 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 80 * 65536 + 0x5678;
    obj.unk7C = input->timer;
    obj.unk15 = input->facing;
    obj.collision_flags = input->collision;
    obj.terrain_box = &spike_marl_terrain_box;
    obj.ext.main_3.player_ahead = input->ahead;
    obj.ext.main_3.turn_timer = 0x25;
    obj.animation_table = (const u8* const*)D_800F9E1C;
    set_animation(&obj, 0);
    g_Player.x_pos.i.hi = input->player_x;
    before = obj;
    player_before = g_Player;
    spike_marl_check_patrol_path(&obj);
    if (input->timer)
        before.unk7C--;
    if (input->turn) {
        before.unk5 = 3;
        before.unk6 = 0;
        before.ext.main_3.turn_timer = input->ahead ? 0x3C : 0x78;
        if (input->ahead)
            before.ext.main_3.player_ahead = 0;
        before.unk17 = 2;
        before.previous_animation_index = 0xFF;
        before.animation_cursor = (const u8*)D_800F9E1C[2];
        before.animation_step = *D_800F9E1C[2];
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(spike_marl_patrol_terrain_tilemap); i++)
        assert(spike_marl_patrol_terrain_tilemap[i] == 1);
    for (i = 0; i < COUNT(spike_marl_patrol_terrain_pixels); i++)
        assert(spike_marl_patrol_terrain_pixels[i] == 0);
    assert(spike_marl_patrol_terrain_attributes[0] == input->tile && layout_width == 16 && layout_size == 256);
    return (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)obj.ext.main_3.turn_timer << 16);
}
static const u32 spike_marl_patrol_terrain_cases_expected[] = { 0x252702u, 0x252702u, 0x780003u, 0x252702u, 0x780003u, 0x780003u, 0x252702u, 0x252702u, 0x3C0003u, 0x3C0003u };

struct func_80043390_case {
    u32 unk2, x_pos, unk15, unk5;
};
static const struct func_80043390_case func_80043390_cases[] = {
    { 0, 3276800, 0, 2 },
    { 1, 9830400, 64, 5 },
    { 2, 3276800, 0, 8 },
    { -1, 9830400, 64, 8 },
};
static u32 test_func_80043390(u32 row)
{
    const struct func_80043390_case* c = &func_80043390_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    s32 frames[32], frames_before[32];
    u32 metadata[16], metadata_before[16];
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 3;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.animation_table = (const u8* const*)D_800F9E1C;
    obj.hp = 7;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    set_animation(&obj, 4);
    obj.state = 0;
    obj.unk2 = c->unk2;
    obj.invincibility_timer = 3;
    obj.unk7C = 9;
    obj.x_speed = 0x24000;
    obj.y_speed = -0x23000;
    obj.x_accel = 0x1000;
    obj.gravity = 0x2000;
    obj.air_state = 1;
    obj.ext.main_3.alerted = 5;
    obj.ext.main_3.roll_timer = -17;
    obj.ext.main_3.player_ahead = 4;
    obj.ext.main_3.turn_timer = 13;
    obj.ext.main_3.saved_step = 7;
    memset(&frames, 0, sizeof(frames));
    memset(&metadata, 0, sizeof(metadata));
    frames[2] = 64;
    metadata[2] = 0x1680;
    TEST_MENU_FRAMES = (u8*)frames;
    D_801406A8 = metadata;
    engine_obj.stage = 0;
    engine_obj.substage = 0;
    g_Player.bg_offset = 1;
    g_Player.x_pos.val = c->x_pos;
    assert(s_StageMainIds[0][0][2] == 3);
    assert((u8)func_8002938C(3) == 2);
    expected = obj;
    expected.unk7C = 0;
    expected.hp = 6;
    expected.invincibility_timer = 0;
    expected.bg_offset = 1;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.unk15 = c->unk15;
    expected.terrain_box = &spike_marl_terrain_box;
    expected.hurt_box = &spike_marl_walk_hurt_box;
    expected.attack_box = &spike_marl_walk_attack_box;
    expected.unk16 = 4;
    expected.unk40 = 0x2D;
    expected.sprite_frames = (u8*)frames + 64;
    expected.unk42 = 0x7880;
    expected.air_state = 0;
    expected.collision_data = (const u16*)D_801060F0;
    expected.contact_damage = 4;
    expected.ext.main_3.alerted = 1;
    expected.ext.main_3.player_ahead = 0;
    expected.ext.main_3.turn_timer = 0x78;
    expected.unk5 = c->unk5;
    if (obj.unk2 == 0) {
        expected.collision_data = D_80106470;
    }
    if (obj.unk2 == 0) {
        set_animation(&expected, 1);
    }
    if (obj.unk2 == 0) {
        expected.contact_damage = 3;
    }
    if (obj.unk2 == 0) {
        expected.ext.main_3.alerted = 0;
    }
    if (obj.unk2 != 0 && obj.unk2 != 1) {
        set_animation(&expected, 5);
    }
    expected.x_speed = 0;
    expected.y_speed = 0;
    expected.x_accel = 0;
    expected.gravity = 0;
    expected.state = 1;
    expected.unk6 = 0;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(frames_before, frames, sizeof(frames_before));
    memcpy(metadata_before, metadata, sizeof(metadata_before));
    func_80043390(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(frames, frames_before, sizeof(frames));
    c_test_same_words(metadata, metadata_before, sizeof(metadata));
    assert(SP_MENU_FRAMES == frames && D_801406A8 == metadata);
    return 1;
}

struct func_80043C0C_case {
    u32 collision_flags, unk15;
    u32 expected[5];
};
static const struct func_80043C0C_case func_80043C0C_cases[] = {
    { 2, 0, { 3u, 7u, 0u, 0u, 0u } },
    { 1, 0, { 0u, 0u, 0u, 0u, 0x100000u } },
    { 3, 255, { 3u, 7u, 0u, 0u, 0u } },
};
static u32 test_func_80043C0C(u32 row)
{
    const struct func_80043C0C_case* c = &func_80043C0C_cases[row];
    u32 observed_values[5];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.x_speed = 1048576;
    obj.collision_flags = c->collision_flags;
    obj.unk15 = c->unk15;
    func_80043C0C(&obj);
    observed_values[0] = (u32)obj.contact_damage;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.x_accel;
    observed_values[4] = (u32)obj.x_speed;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

struct spike_marl_curl_update_case {
    u32 event;
};
static const struct spike_marl_curl_update_case spike_marl_curl_update_cases[] = {
    { 0 },
    { 5 },
    { 255 },
};
static u32 test_spike_marl_curl_update(u32 row)
{
    const struct spike_marl_curl_update_case* c = &spike_marl_curl_update_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 3;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.animation_table = (const u8* const*)D_800F9E1C;
    obj.hp = 7;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.unk5 = 4;
    set_animation(&obj, 3);
    obj.animation_step.fields.event = c->event;
    obj.contact_damage = 7;
    obj.collision_data = D_80106470;
    expected = obj;
    --expected.animation_step.fields.duration;
    player_before = g_Player;
    engine_before = engine_obj;
    spike_marl_curl_update(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

struct spike_marl_roll_entry_update_case {
    u32 unk15, obj_unk7C, obj_x_speed, expected_unk7C, expected_x_speed, unk5, unk6;
};
static const struct spike_marl_roll_entry_update_case spike_marl_roll_entry_update_cases[] = {
    { 0, 1, -32768, 0, -131072, 5, 0 },
    { 64, 1, 32768, 0, 131072, 5, 0 },
    { 64, 0, 32768, -1, 32768, 8, 1 },
    { 0, 2, -32768, 1, -32768, 8, 1 },
};
static u32 test_spike_marl_roll_entry_update(u32 row)
{
    const struct spike_marl_roll_entry_update_case* c = &spike_marl_roll_entry_update_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 3;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.animation_table = (const u8* const*)D_800F9E1C;
    obj.hp = 7;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    set_animation(&obj, 5);
    obj.unk5 = 8;
    obj.unk6 = 1;
    obj.unk15 = c->unk15;
    obj.unk7C = c->obj_unk7C;
    obj.x_speed = c->obj_x_speed;
    obj.y_speed = -0x10000;
    expected = obj;
    --expected.animation_step.fields.duration;
    expected.x_pos.val = expected.x_pos.val + obj.x_speed;
    expected.y_pos.val = expected.y_pos.val - obj.y_speed;
    expected.unk7C = c->expected_unk7C;
    expected.x_speed = c->expected_x_speed;
    expected.unk5 = c->unk5;
    expected.unk6 = c->unk6;
    player_before = g_Player;
    engine_before = engine_obj;
    spike_marl_roll_entry_update(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

struct spike_marl_roll_update_case {
    u32 unk15, collision_flags;
    u32 expected[6];
};
static const struct spike_marl_roll_update_case spike_marl_roll_update_cases[] = {
    { 0, 2, { 3u, 0xFFF00004u, 7u, 0u, 0u, 0u } },
    { 0, 1, { 0u, 0xFFF00004u, 0u, 2u, 0xFFFFE800u, 0u } },
    { 255, 3, { 3u, 0xFFF00004u, 7u, 0u, 0u, 0u } },
};
static u32 test_spike_marl_roll_update(u32 row)
{
    const struct spike_marl_roll_update_case* c = &spike_marl_roll_update_cases[row];
    u32 observed_values[6];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.ext.main_3.roll_timer = -1048576;
    obj.unk15 = c->unk15;
    obj.collision_flags = c->collision_flags;
    spike_marl_roll_update(&obj);
    observed_values[0] = (u32)obj.contact_damage;
    observed_values[1] = (u32)obj.ext.main_3.roll_timer;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.x_accel;
    observed_values[5] = (u32)obj.x_speed;
    return c_test_observe(0, row, observed_values, c->expected, 6);
}

struct spike_marl_uncurl_update_case {
    u32 event;
};
static const struct spike_marl_uncurl_update_case spike_marl_uncurl_update_cases[] = {
    { 0 },
    { 5 },
    { 255 },
};
static u32 test_spike_marl_uncurl_update(u32 row)
{
    const struct spike_marl_uncurl_update_case* c = &spike_marl_uncurl_update_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 3;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.animation_table = (const u8* const*)D_800F9E1C;
    obj.hp = 7;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.unk5 = 7;
    set_animation(&obj, 4);
    obj.animation_step.fields.event = c->event;
    obj.contact_damage = 7;
    obj.collision_data = D_80106470;
    expected = obj;
    --expected.animation_step.fields.duration;
    player_before = g_Player;
    engine_before = engine_obj;
    spike_marl_uncurl_update(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

static void sm_resume(void)
{
    state_reset(1, 0, 0);
    so.ext.main_3.saved_step = 3;
    spike_marl_resume_step(&so);
}

static void (*const spike_marl_misc_cases[])(void) = {
    sm_resume,
};
static const u32 spike_marl_misc_expected[] = { 3u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_spike_marl_misc(u32 row)
{
    return state_run(spike_marl_misc_cases[row], row, &spike_marl_misc_expected[row * 10]);
}

#define MARL(step, px, py, flags, facing) (state_reset(step, 0, 0), so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, so.collision_flags = flags, so.unk15 = facing, g_Player.x_pos.i.hi = px, g_Player.y_pos.i.hi = py, spike_marl_detect_player(&so), state_extra = so.ext.main_3.alerted)
static void smd_rolling(void)
{
    MARL(5, 0x70, 0x60, 0, 0);
}
static void smd_bouncing(void) { MARL(6, 0x70, 0x60, 0, 0); }
static void smd_left(void) { MARL(2, 0x70, 0x60, 0, 0); }
static void smd_right(void) { MARL(2, 0x90, 0x60, 0, 0x40); }
static void smd_behind(void) { MARL(2, 0x90, 0x60, 0, 0); }
static void smd_behind_right(void) { MARL(2, 0x70, 0x60, 0, 0x40); }
static void smd_walled(void) { MARL(2, 0x70, 0x60, 1, 0); }
static void smd_far(void) { MARL(2, 0x10, 0x60, 0, 0); }
static void smd_above(void) { MARL(2, 0x70, 0x10, 0, 0); }
static void smd_walking(void) { MARL(3, 0x70, 0x60, 0, 0); }

static void (*const spike_marl_detect_cases[])(void) = {
    smd_rolling,
    smd_bouncing,
    smd_left,
    smd_right,
    smd_behind,
    smd_behind_right,
    smd_walled,
    smd_far,
    smd_above,
    smd_walking,
};
static const u32 spike_marl_detect_expected[] = { 5u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 6u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 4u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 4u, 0u, 0x800000u, 0u, 0u, 0u, 0x4000u, 0u, 1u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0x4000u, 0u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 1u, 0u };

static u32 test_spike_marl_detect(u32 row)
{
    return state_run(spike_marl_detect_cases[row], row, &spike_marl_detect_expected[row * 10]);
}

void spike_marl_roll_begin(struct MainObj* arg0);
void spike_marl_roll_entry_begin(struct MainObj*);
void spike_marl_track_player_side(struct MainObj* arg0);
extern union AnimationStep* D_800F9E1C[13];
static const s16 heights[] = { -33, -32, -31, 31, 32, 33 };
static u32 tracking(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    u32 side = row % 3, face = row / 3 % 2, height = row / 6 % 6, ahead = row / 36;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 3;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk15 = face ? 0x40 : 0;
    obj.ext.main_3.player_ahead = ahead;
    obj.ext.main_3.turn_timer = 9;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    g_Player.x_pos.val = obj.x_pos.val + ((s32)side - 1) * 65536;
    g_Player.y_pos.val = obj.y_pos.val + heights[height] * 65536;
    player_before = g_Player;
    expected = obj;
    if (!ahead && (height == 2 || height == 3) && (face ? side == 2 : side == 0))
        expected.ext.main_3.player_ahead = 1;
    if (ahead && (height == 0 || height == 5)) {
        expected.ext.main_3.player_ahead = 0;
        expected.ext.main_3.turn_timer = 120;
    }
    spike_marl_track_player_side(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}
static u32 rolling(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    u32 mode = row % 3, face = row / 3 % 2, side = row / 6 % 3, wait = row / 18;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 3;
    obj.state = 1;
    obj.unk5 = mode == 2 ? 8 : 5;
    obj.unk6 = mode == 1;
    obj.unk15 = face ? 0x40 : 0;
    obj.unk7C = wait;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_speed = face ? 0x40000 : -0x40000;
    obj.ext.main_3.roll_timer = wait * 4;
    obj.animation_table = (const u8* const*)D_800F9E1C;
    set_animation(&obj, mode == 0 ? 3 : mode == 1 ? 5
                                                  : 1);
    assert(obj.animation_step.packed == (mode == 0 ? 0x0F010002 : mode == 1 ? 0x1D010003
                                                                            : 0x01010006));
    g_Player.x_pos.val = obj.x_pos.val + ((s32)side - 1) * 65536;
    player_before = g_Player;
    expected = obj;
    if (mode == 0) {
        if (!wait) {
            expected.unk6 = 1;
            expected.unk17 = 5;
            expected.previous_animation_index = 255;
            expected.animation_cursor = (const u8*)D_800F9E1C[5];
            expected.animation_step.packed = 0x1D010003;
        } else
            expected.unk7C--;
        expected.animation_step.fields.duration--;
    } else if (mode == 1) {
        expected.ext.main_3.roll_timer += 4;
        if (face ? side == 0 : side == 2) {
            expected.x_accel = -0x1800;
            expected.unk6 = 2;
        }
        expected.x_pos.val += obj.x_speed;
        expected.animation_step.fields.duration--;
    } else {
        expected.unk6 = 1;
        expected.x_speed = face ? 0x8000 : -0x8000;
        expected.x_accel = expected.y_speed = expected.gravity = 0;
        expected.unk7C = 48;
    }
    D_8013E198[2] = -1;
    if (mode == 0)
        spike_marl_roll_begin(&obj);
    else if (mode == 1)
        spike_marl_roll_update(&obj);
    else
        spike_marl_roll_entry_begin(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "spike_marl_detect", 0, 0, COUNT(spike_marl_detect_cases), test_spike_marl_detect },
    { "spike_marl_misc", 0, 0, COUNT(spike_marl_misc_cases), test_spike_marl_misc },
    { "spike_marl_ahead_collision", NULL, spike_marl_ahead_collision_cases_expected, COUNT(spike_marl_ahead_collision_cases_expected), spike_marl_ahead_collision_patrol_case },
    { "spike_marl_patrol_terrain", NULL, spike_marl_patrol_terrain_cases_expected, COUNT(spike_marl_patrol_terrain_cases_expected), spike_marl_patrol_terrain_patrol_case },
    { "func_80043390", 0, 0, 4, test_func_80043390 },
    { "func_80043C0C", 0, 0, 3, test_func_80043C0C },
    { "spike_marl_curl_update", 0, 0, 3, test_spike_marl_curl_update },
    { "spike_marl_roll_entry_update", 0, 0, 4, test_spike_marl_roll_entry_update },
    { "spike_marl_roll_update", 0, 0, 3, test_spike_marl_roll_update },
    { "spike_marl_uncurl_update", 0, 0, 3, test_spike_marl_uncurl_update },
    { "signed_height_edges_and_both_facing_tracking_relations", NULL, NULL, 45, tracking },
    { "shipped_roll_entry_start_and_player_crossing", NULL, NULL, 21, rolling },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(spike_marl_detect_cases) + COUNT(spike_marl_misc_cases) + COUNT(spike_marl_ahead_collision_cases_expected) + COUNT(spike_marl_patrol_terrain_cases_expected) + 4 + 3 + 3 + 4 + 3 + 3 + 45 + 21;
