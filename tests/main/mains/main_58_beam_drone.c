#include "test_runtime.h"
extern struct Unk_unk68 beam_drone_hit_box;
extern struct Unk_unk68 beam_drone_debris;

static const u32 beam_drone_spawn_beam_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_beam_drone_spawn_beam(u32 row)
{
    u32 observed_values[8];
    struct VisualObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_0_full ? 1 : 0;
    }
    beam_drone_spawn_beam(&obj);
    observed_values[0] = (u32)shot_objects[0].active;
    observed_values[1] = (u32)shot_objects[0].bg_offset;
    observed_values[2] = (u32)shot_objects[0].id;
    observed_values[3] = (u32)shot_objects[0].unk15;
    observed_values[4] = (u32)shot_objects[0].unk16;
    observed_values[5] = (u32)shot_objects[0].unk2;
    observed_values[6] = (u32)shot_objects[0].unk40;
    observed_values[7] = (u32)shot_objects[0].unk42;
    return c_test_observe(0, row, observed_values, beam_drone_spawn_beam_expected, 8);
}

static const u32 beam_drone_spawn_charge_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_beam_drone_spawn_charge(u32 row)
{
    u32 observed_values[10];
    struct AnimatedObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_0_full ? 1 : 0;
    }
    beam_drone_spawn_charge(&obj);
    observed_values[0] = (u32)visual_objects[0].active;
    observed_values[1] = (u32)visual_objects[0].bg_offset;
    observed_values[2] = (u32)visual_objects[0].id;
    observed_values[3] = (u32)visual_objects[0].unk15;
    observed_values[4] = (u32)visual_objects[0].unk16;
    observed_values[5] = (u32)visual_objects[0].unk2;
    observed_values[6] = (u32)visual_objects[0].unk40;
    observed_values[7] = (u32)visual_objects[0].unk42;
    observed_values[8] = (u32)visual_objects[0].x_pos.val;
    observed_values[9] = (u32)visual_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, beam_drone_spawn_charge_expected, 10);
}

struct func_80074438_case {
    u32 unk2;
    u32 expected[17];
};
static const struct func_80074438_case func_80074438_cases[] = {
    { -1, { 0x41u, 0u, 0u, 3u, 0u, 5u, 0u, 1u, 0u, 5u, 2u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 3, { 0x41u, 0u, 0u, 3u, 0u, 5u, 0u, 1u, 0u, 5u, 2u, 0u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_func_80074438(u32 row)
{
    const struct func_80074438_case* c = &func_80074438_cases[row];
    u32 observed_values[17];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&beam_drone_hit_box, 0, sizeof(beam_drone_hit_box));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.unk2 = c->unk2;
    func_80074438(&obj);
    observed_values[0] = (u32)obj.active;
    observed_values[1] = (u32)obj.air_state;
    observed_values[2] = (u32)obj.bg_offset;
    observed_values[3] = (u32)obj.contact_damage;
    observed_values[4] = (u32)obj.gravity;
    observed_values[5] = (u32)obj.hp;
    observed_values[6] = (u32)obj.invincibility_timer;
    observed_values[7] = (u32)obj.state;
    observed_values[8] = (u32)obj.unk15;
    observed_values[9] = (u32)obj.unk16;
    observed_values[10] = (u32)obj.unk5;
    observed_values[11] = (u32)obj.unk6;
    observed_values[12] = (u32)obj.unk7C;
    observed_values[13] = (u32)obj.unk7E;
    observed_values[14] = (u32)obj.x_accel;
    observed_values[15] = (u32)obj.x_speed;
    observed_values[16] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 17);
}

struct func_800745E8_case {
    u32 unk2;
    u32 expected[1];
};
static const struct func_800745E8_case func_800745E8_cases[] = {
    { -1, { 0xFF010201u } },
    { 3, { 0x3010201u } },
};
static u32 test_func_800745E8(u32 row)
{
    const struct func_800745E8_case* c = &func_800745E8_cases[row];
    u32 observed_values[1];
    struct MainObj obj, before;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj background_before[3];
    struct WeaponObj weapons_before[16];
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    obj.id = 58;
    obj.unk2 = c->unk2;
    obj.x_pos.val = 6558260;
    obj.y_pos.val = 5251909;
    g_Player.spike_immune = 1;
    func_80074438(&obj);
    obj.unk5 = 1;
    obj.ext.main_58.saved_unk5 = 2;
    before = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(background_before, background_objects, sizeof(background_before));
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    func_800745E8(&obj);
    before.unk5 = 2;
    before.on_screen = 1;
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, background_before, sizeof(background_before));
    c_test_same_words(weapon_objects, weapons_before, sizeof(weapons_before));
    observed_values[0] = (u8)obj.state | ((u32)(u8)obj.unk5 << 8) | ((u32)(u8)obj.on_screen << 16) | ((u32)(u8)obj.unk2 << 24);
    return c_test_observe(0, row, observed_values, c->expected, 1);
}

const struct CTestGroup c_test_groups[] = {
    { "beam_drone_spawn_beam", 0, 0, 1, test_beam_drone_spawn_beam },
    { "beam_drone_spawn_charge", 0, 0, 1, test_beam_drone_spawn_charge },
    { "func_80074438", 0, 0, 2, test_func_80074438 },
    { "func_800745E8", 0, 0, 2, test_func_800745E8 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 1 + 2 + 2;
