#include "test_runtime.h"
#include "main/weapons/weapon_01_lightning_web.h"
#include "main/weapons/weapon_02_frost_tower.h"
#include "main/weapons/weapon_06_aiming_laser_charged.h"
#include "main/weapons/weapon_07_double_cyclone.h"
void frost_tower_charged_spawn_part(s8);

static u32 shard_case(u32 mode, u32 observation)
{
    struct MiscObj obj;
    u32 actual;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 1;
    obj.id = 0x25;
    obj.on_screen = 1;
    obj.state = 1;
    obj.bg_offset = -1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x2468;
    obj.x_vel.val = 65536;
    obj.y_vel.val = 2 * 65536;
    obj.unk2C = 0x5000;
    g_Player.weapon = mode == 3 ? 0 : 2;
    g_Player.input_locked = mode == 1;
    g_Player.capsule_state = mode == 2;
    g_Player.shot_type = mode == 4 ? 0xB : 0;
    frost_shard_update(&obj);
    assert(g_Player.weapon == (mode == 3 ? 0 : 2));
    assert(g_Player.input_locked == (mode == 1));
    assert(g_Player.capsule_state == (mode == 2));
    assert(g_Player.shot_type == (mode == 4 ? 0xB : 0));
    assert(obj.bg_offset == -1 && obj.x_vel.val == 65536 && obj.unk2C == 0x5000);
    if (observation == 1)
        return (u32)obj.x_pos.val;
    if (observation == 2)
        return (u32)obj.y_pos.val;
    if (observation == 3)
        return (u32)obj.y_vel.val;
    actual = (u8)obj.active | ((u32)(u8)obj.state << 8) | ((u32)(u8)obj.id << 16) | ((u32)(u8)obj.on_screen << 24);
    return actual;
}
static const u32 frost_shard_gates_cases_expected[] = { 0x250101u, 0x651234u, 0xC62468u, 0x1B000u, 0x0u, 0x641234u, 0xC82468u, 0x20000u, 0x0u, 0x641234u, 0xC82468u, 0x20000u, 0x0u, 0x641234u, 0xC82468u, 0x20000u, 0x0u, 0x641234u, 0xC82468u, 0x20000u };
static u32 frost_shard_gates_cases_row(u32 row)
{
    return shard_case(row / 4, row % 4);
}

static u32 cancel_case(u32 mode)
{
    struct WeaponObj obj, expected;
    struct PlayerObj player_before;
    u32 i;
    struct Unk_unk68 box = { -2, -2, 4, 4 };
    u8 palette_before = need_palette_load;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 2;
    obj.unk2 = 7;
    obj.on_screen = 1;
    obj.state = mode ? 1 : 2;
    obj.unk5 = 2;
    obj.unk6 = 3;
    obj.unk7 = 4;
    obj.unk50 = (const u8*)&box;
    obj.unk68 = &box;
    obj.unk70 = 0xA5;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    g_Player.weapon = mode == 3 ? 0 : 2;
    g_Player.hp = 16;
    g_Player.input_locked = mode == 1;
    g_Player.capsule_state = mode == 2;
    g_Player.shot_type = mode == 4 ? 11 : 0;
    g_Player.shot_count = 3;
    g_Player.special_shot_count = 2;
    expected = obj;
    player_before = g_Player;
    expected.active = expected.id = expected.unk2 = expected.on_screen = 0;
    expected.state = expected.unk5 = expected.unk6 = expected.unk7 = 0;
    expected.unk50 = NULL;
    expected.unk68 = NULL;
    expected.unk70 = 0;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    player_before.shot_count = 2;
    player_before.special_shot_count = 1;
    frost_tower_update(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(need_palette_load == palette_before);
    return (u8)obj.state | ((u32)(u8)player_before.shot_count << 8) | ((u32)(u8)player_before.special_shot_count << 16);
}
static const u32 frost_tower_cancellation_dispatch_cases_expected[] = { 0x10200u, 0x10200u, 0x10200u, 0x10200u, 0x10200u };

static const u32 frost_tower_spawn_shard_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u };
static u32 test_frost_tower_spawn_shard(u32 row)
{
    u32 observed_values[6];
    struct WeaponObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&misc_objects, 0, sizeof(misc_objects));
    FILL_ACTIVE(misc_objects, 64, 255 ? 1 : 0);
    frost_tower_spawn_shard(&obj);
    observed_values[0] = (u32)misc_objects[0].active;
    observed_values[1] = (u32)misc_objects[0].bg_offset;
    observed_values[2] = (u32)misc_objects[0].id;
    observed_values[3] = (u32)misc_objects[0].unk2;
    observed_values[4] = (u32)misc_objects[0].x_pos.val;
    observed_values[5] = (u32)misc_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, frost_tower_spawn_shard_expected, 6);
}

#include "support/charged_dispatch.h"
CHARGED_BASIC(1)
CHARGED_CASE(1, 6)
static const CTestCase frost_tower_charged_dispatch_cases[] = { CHARGED_BASIC_ENTRIES(1) CHARGED_ENTRIES(1, 6) };

static const u32 frost_tower_charged_dispatch_cases_expected[] = { 0x1000191u, 0x605u, 0x0u, 0x504u, 0x0u, 0x504u, 0x0u, 0x504u, 0x0u, 0x504u };

static struct WeaponObj charged_expected_pool[16];
static struct BackgroundObj charged_expected_backgrounds[3];

static u32 test_charged_waves(u32 row)
{
    static const s8 parts[4][4] = {
        { 1, 0, 0, 0 },
        { 2, -126, 0, 0 },
        { 1, 3, -125, 0 },
        { 4, -124, 5, -123 },
    };
    static const u8 counts[] = { 1, 2, 3, 4 };
    static const u8 free_slots[] = { 0, 2, 16 };
    struct WeaponObj obj, expected;
    struct PlayerObj expected_player;
    u32 i, phase = row < 12 ? row / 3 : (row - 12) / 2;
    u32 free_count = row < 12 ? free_slots[row % 3] : 16;
    u32 spawned = row < 12 ? (counts[phase] < free_count ? counts[phase] : free_count) : 0;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(background_objects, 0, sizeof(background_objects));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    for (i = 0; i < 16 - free_count; i++) {
        weapon_objects[i].active = 1;
        weapon_objects[i].id = 1;
        weapon_objects[i].x_pos.val = (i + 1) * 65536;
    }
    g_Player.weapon = 2;
    g_Player.bg_offset = row % 3;
    g_Player.shot_count = 2;
    g_Player.special_shot_count = 1;
    obj.active = 1;
    obj.id = 11;
    obj.on_screen = 1;
    obj.state = 1;
    obj.unk50 = &hitbox;
    obj.unk68 = (struct Unk_unk68*)&hitbox;
    obj.ext.raw[3] = phase;
    if (row >= 12)
        obj.ext.raw[2] = row & 1 ? 40 : 1;
    expected = obj;
    expected_player = g_Player;
    memcpy(charged_expected_pool, weapon_objects, sizeof(weapon_objects));
    memcpy(charged_expected_backgrounds, background_objects, sizeof(background_objects));
    if (row >= 12) {
        expected.ext.raw[2]--;
    } else {
        expected.ext.raw[2] = 40;
        expected.ext.raw[3]++;
        if (phase == 3) {
            expected.on_screen = 0;
            expected.state = 3;
            expected.unk50 = NULL;
            expected.unk68 = NULL;
        }
        expected_player.shot_count += spawned;
        expected_player.special_shot_count += spawned;
        for (i = 0; i < spawned; i++) {
            struct WeaponObj* part = &charged_expected_pool[16 - free_count + i];
            part->active = 1;
            part->id = 11;
            part->unk2 = parts[phase][i];
            part->bg_offset = g_Player.bg_offset;
        }
        charged_expected_backgrounds[0].unk34 = 0x10;
        charged_expected_backgrounds[0].unk36 = phase == 3 ? 64 : 32;
        charged_expected_backgrounds[0].unk45 = 8;
        charged_expected_backgrounds[0].unk3E.bytes[0] = 8;
        charged_expected_backgrounds[0].unk3A = 1;
        charged_expected_backgrounds[0].unk3C = 1;
    }
    frost_tower_charged_update(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &expected_player, sizeof(g_Player));
    c_test_same_words(weapon_objects, charged_expected_pool, sizeof(weapon_objects));
    c_test_same_words(background_objects, charged_expected_backgrounds, sizeof(background_objects));
    return 1;
}

static struct {
    u32 root[8];
    u32 bank[16];
    u16 stream[24];
} frost_archive;

void frost_tower_main(struct WeaponObj*);
void frost_tower_charged_update(struct WeaponObj*);
void frost_sparkle_update(struct MiscObj*);
extern s32 player_gfx_buf_0[0x400];
extern u32* D_8011C094[7];
extern u32* D_8011C018[22];
extern u8 frost_sparkle_animations[8];
extern s32 frost_particle_x_vels[8], frost_particle_y_vels[8];
extern struct Unk_unk68 frost_tower_hit_box[], frost_tower_terrain_box[];
#ifdef MMX4_PC
#define GFX_WORDS 0x4000
#else
#define GFX_WORDS 0xC00
#endif
static struct WeaponObj controller, expected_controller;
static struct MiscObj sparkle, expected_sparkle;
static struct PlayerObj player_before;
static struct EngineObj engine_before;
static struct MainBssState main_before;
static struct BackgroundObj backgrounds_before[3];
static struct WeaponObj weapons_before[16];
static struct MiscObj misc_before[64];
static u32 sprites[32], sprites_before[32];
static u16 random_expected;
static struct RectPtrPair uploads_expected[8];
static u32 queue_expected, pixels_expected[GFX_WORDS], pixels0_expected[0x400];
static const s16 cameras[3][2] = { { 0, 0 }, { 1024, 512 }, { -320, -240 } };
static const s32 x_velocities[8] = { -0x30000, -0x20000, 0x18000, 0x28000, -0x38000, -0x28000, 0x20000, 0x30000 };
static const s32 y_velocities[8] = { 0x38000, 0x48000, 0x60000, 0x30000, 0x40000, 0x50000, 0x58000, 0x28000 };
static const u8 sparkle_animations[8] = { 2, 3, 4, 5, 6, 7, 8, 5 };
static const struct {
    u16 random;
    s8 dx, dy;
    u8 facing, vx, vy, animation;
} launches[256] = {
    { 0x0000, 0, 0, 0x40, 0, 0, 0 },
    { 0x0001, 1, 1, 0x00, 1, 1, 1 },
    { 0x0002, -2, -2, 0x40, 2, 2, 2 },
    { 0x0003, 3, 3, 0x00, 3, 3, 3 },
    { 0x0004, -4, -4, 0x40, 4, 4, 4 },
    { 0x0005, 5, 5, 0x00, 5, 5, 5 },
    { 0x0006, -6, -6, 0x40, 6, 6, 6 },
    { 0x0007, 7, 7, 0x00, 7, 7, 7 },
    { 0x0008, -8, 0, 0x40, 0, 0, 0 },
    { 0x0009, 9, 1, 0x00, 1, 1, 1 },
    { 0x000A, -10, -2, 0x40, 2, 2, 2 },
    { 0x000B, 11, 3, 0x00, 3, 3, 3 },
    { 0x000C, -12, -4, 0x40, 4, 4, 4 },
    { 0x000D, 13, 5, 0x00, 5, 5, 5 },
    { 0x000E, -14, -6, 0x40, 6, 6, 6 },
    { 0x000F, 15, 7, 0x00, 7, 7, 7 },
    { 0x0010, 0, -16, 0x40, 0, 0, 0 },
    { 0x0011, 1, 17, 0x00, 1, 1, 1 },
    { 0x0012, -2, -18, 0x40, 2, 2, 2 },
    { 0x0013, 3, 19, 0x00, 3, 3, 3 },
    { 0x0014, -4, -20, 0x40, 4, 4, 4 },
    { 0x0015, 5, 21, 0x00, 5, 5, 5 },
    { 0x0016, -6, -22, 0x40, 6, 6, 6 },
    { 0x0017, 7, 23, 0x00, 7, 7, 7 },
    { 0x0018, -8, -16, 0x40, 0, 0, 0 },
    { 0x0019, 9, 17, 0x00, 1, 1, 1 },
    { 0x001A, -10, -18, 0x40, 2, 2, 2 },
    { 0x001B, 11, 19, 0x00, 3, 3, 3 },
    { 0x001C, -12, -20, 0x40, 4, 4, 4 },
    { 0x001D, 13, 21, 0x00, 5, 5, 5 },
    { 0x001E, -14, -22, 0x40, 6, 6, 6 },
    { 0x001F, 15, 23, 0x00, 7, 7, 7 },
    { 0x0020, 0, 0, 0x40, 0, 0, 0 },
    { 0x0021, 1, 1, 0x00, 1, 1, 1 },
    { 0x0022, -2, -2, 0x40, 2, 2, 2 },
    { 0x0023, 3, 3, 0x00, 3, 3, 3 },
    { 0x0024, -4, -4, 0x40, 4, 4, 4 },
    { 0x0025, 5, 5, 0x00, 5, 5, 5 },
    { 0x0026, -6, -6, 0x40, 6, 6, 6 },
    { 0x0027, 7, 7, 0x00, 7, 7, 7 },
    { 0x0028, -8, 0, 0x40, 0, 0, 0 },
    { 0x0029, 9, 1, 0x00, 1, 1, 1 },
    { 0x002A, -10, -2, 0x40, 2, 2, 2 },
    { 0x002B, 11, 3, 0x00, 3, 3, 3 },
    { 0x002C, -12, -4, 0x40, 4, 4, 4 },
    { 0x002D, 13, 5, 0x00, 5, 5, 5 },
    { 0x002E, -14, -6, 0x40, 6, 6, 6 },
    { 0x002F, 15, 7, 0x00, 7, 7, 7 },
    { 0x0030, 0, -16, 0x40, 0, 0, 0 },
    { 0x0031, 1, 17, 0x00, 1, 1, 1 },
    { 0x0032, -2, -18, 0x40, 2, 2, 2 },
    { 0x0033, 3, 19, 0x00, 3, 3, 3 },
    { 0x0034, -4, -20, 0x40, 4, 4, 4 },
    { 0x0035, 5, 21, 0x00, 5, 5, 5 },
    { 0x0036, -6, -22, 0x40, 6, 6, 6 },
    { 0x0037, 7, 23, 0x00, 7, 7, 7 },
    { 0x0038, -8, -16, 0x40, 0, 0, 0 },
    { 0x0039, 9, 17, 0x00, 1, 1, 1 },
    { 0x003A, -10, -18, 0x40, 2, 2, 2 },
    { 0x003B, 11, 19, 0x00, 3, 3, 3 },
    { 0x003C, -12, -20, 0x40, 4, 4, 4 },
    { 0x003D, 13, 21, 0x00, 5, 5, 5 },
    { 0x003E, -14, -22, 0x40, 6, 6, 6 },
    { 0x003F, 15, 23, 0x00, 7, 7, 7 },
    { 0x0040, 0, 0, 0x40, 0, 0, 0 },
    { 0x0041, 1, 1, 0x00, 1, 1, 1 },
    { 0x0042, -2, -2, 0x40, 2, 2, 2 },
    { 0x0043, 3, 3, 0x00, 3, 3, 3 },
    { 0x0044, -4, -4, 0x40, 4, 4, 4 },
    { 0x0045, 5, 5, 0x00, 5, 5, 5 },
    { 0x0046, -6, -6, 0x40, 6, 6, 6 },
    { 0x0047, 7, 7, 0x00, 7, 7, 7 },
    { 0x0048, -8, 0, 0x40, 0, 0, 0 },
    { 0x0049, 9, 1, 0x00, 1, 1, 1 },
    { 0x004A, -10, -2, 0x40, 2, 2, 2 },
    { 0x004B, 11, 3, 0x00, 3, 3, 3 },
    { 0x004C, -12, -4, 0x40, 4, 4, 4 },
    { 0x004D, 13, 5, 0x00, 5, 5, 5 },
    { 0x004E, -14, -6, 0x40, 6, 6, 6 },
    { 0x004F, 15, 7, 0x00, 7, 7, 7 },
    { 0x0050, 0, -16, 0x40, 0, 0, 0 },
    { 0x0051, 1, 17, 0x00, 1, 1, 1 },
    { 0x0052, -2, -18, 0x40, 2, 2, 2 },
    { 0x0053, 3, 19, 0x00, 3, 3, 3 },
    { 0x0054, -4, -20, 0x40, 4, 4, 4 },
    { 0x0055, 5, 21, 0x00, 5, 5, 5 },
    { 0xC87E, 11, -16, 0x00, 4, 6, 6 },
    { 0xC87F, -12, 17, 0x40, 5, 7, 7 },
    { 0xC880, 13, -18, 0x00, 6, 0, 0 },
    { 0xC881, -14, 19, 0x40, 7, 1, 1 },
    { 0xC882, 15, -20, 0x00, 0, 2, 2 },
    { 0xC883, 0, 21, 0x40, 1, 3, 3 },
    { 0xC884, 1, -22, 0x00, 2, 4, 4 },
    { 0xC885, -2, 23, 0x40, 3, 5, 5 },
    { 0xC886, 3, -16, 0x00, 4, 6, 6 },
    { 0xC887, -4, 17, 0x40, 5, 7, 7 },
    { 0xC888, 5, -18, 0x00, 6, 0, 0 },
    { 0xC889, -6, 19, 0x40, 7, 1, 1 },
    { 0xC88A, 7, -20, 0x00, 0, 2, 2 },
    { 0xC88B, -8, 21, 0x40, 1, 3, 3 },
    { 0xC88C, 9, -22, 0x00, 2, 4, 4 },
    { 0xC88D, -10, 23, 0x40, 3, 5, 5 },
    { 0xC88E, 11, 0, 0x00, 4, 6, 6 },
    { 0xC88F, -12, 1, 0x40, 5, 7, 7 },
    { 0xC890, 13, -2, 0x00, 6, 0, 0 },
    { 0xC891, -14, 3, 0x40, 7, 1, 1 },
    { 0xC892, 15, -4, 0x00, 0, 2, 2 },
    { 0xC893, 0, 5, 0x40, 1, 3, 3 },
    { 0xC894, 1, -6, 0x00, 2, 4, 4 },
    { 0xC895, -2, 7, 0x40, 3, 5, 5 },
    { 0xC896, 3, 0, 0x00, 4, 6, 6 },
    { 0xC897, -4, 1, 0x40, 5, 7, 7 },
    { 0xC898, 5, -2, 0x00, 6, 0, 0 },
    { 0xE3C1, -6, 3, 0x00, 3, 6, 1 },
    { 0xE3C2, 7, -4, 0x40, 4, 7, 2 },
    { 0xE3C3, -8, 5, 0x00, 5, 0, 3 },
    { 0xE3C4, 9, -6, 0x40, 6, 1, 4 },
    { 0xE3C5, -10, 7, 0x00, 7, 2, 5 },
    { 0xE3C6, 11, -16, 0x40, 0, 3, 6 },
    { 0xE3C7, -12, 17, 0x00, 1, 4, 7 },
    { 0xE3C8, 13, -18, 0x40, 2, 5, 0 },
    { 0xE3C9, -14, 19, 0x00, 3, 6, 1 },
    { 0xE3CA, 15, -20, 0x40, 4, 7, 2 },
    { 0xE3CB, 0, 21, 0x00, 5, 0, 3 },
    { 0xE3CC, 1, -22, 0x40, 6, 1, 4 },
    { 0xE3CD, -2, 23, 0x00, 7, 2, 5 },
    { 0xE3CE, 3, -16, 0x40, 0, 3, 6 },
    { 0xE3CF, -4, 17, 0x00, 1, 4, 7 },
    { 0xE3D0, 5, -18, 0x40, 2, 5, 0 },
    { 0xE3D1, -6, 19, 0x00, 3, 6, 1 },
    { 0xE3D2, 7, -20, 0x40, 4, 7, 2 },
    { 0xE3D3, -8, 21, 0x00, 5, 0, 3 },
    { 0xE3D4, 9, -22, 0x40, 6, 1, 4 },
    { 0xE3D5, -10, 23, 0x00, 7, 2, 5 },
    { 0xE3D6, 11, 0, 0x40, 0, 3, 6 },
    { 0xE3D7, -12, 1, 0x00, 1, 4, 7 },
    { 0xE3D8, 13, -2, 0x40, 2, 5, 0 },
    { 0xE6DD, -14, 3, 0x00, 3, 7, 5 },
    { 0xE6DE, 15, -4, 0x40, 4, 0, 6 },
    { 0xE6DF, 0, 5, 0x00, 5, 1, 7 },
    { 0xE6E0, 1, -6, 0x40, 6, 2, 0 },
    { 0xE6E1, -2, 7, 0x00, 7, 3, 1 },
    { 0xE6E2, 3, 0, 0x40, 0, 4, 2 },
    { 0xE6E3, -4, 1, 0x00, 1, 5, 3 },
    { 0xE6E4, 5, -2, 0x40, 2, 6, 4 },
    { 0xE6E5, -6, 3, 0x00, 3, 7, 5 },
    { 0xE4E4, 7, -4, 0x40, 4, 0, 4 },
    { 0xE4E5, -8, 5, 0x00, 5, 1, 5 },
    { 0xE4E6, 9, -6, 0x40, 6, 2, 6 },
    { 0xE4E7, -10, 7, 0x00, 7, 3, 7 },
    { 0xE4E8, 11, -16, 0x40, 0, 4, 0 },
    { 0xE4E9, -12, 17, 0x00, 1, 5, 1 },
    { 0xE4EA, 13, -18, 0x40, 2, 6, 2 },
    { 0x3564, -14, 20, 0x00, 0, 7, 4 },
    { 0x3565, 15, -21, 0x40, 1, 0, 5 },
    { 0x3566, 0, 22, 0x00, 2, 1, 6 },
    { 0x3567, 1, -23, 0x40, 3, 2, 7 },
    { 0x3568, -2, 16, 0x00, 4, 3, 0 },
    { 0x3E76, 3, -17, 0x40, 6, 0, 6 },
    { 0x3E77, -4, 18, 0x00, 7, 1, 7 },
    { 0x3E78, 5, -19, 0x40, 0, 2, 0 },
    { 0x3E79, -6, 20, 0x00, 1, 3, 1 },
    { 0x3E7A, 7, -21, 0x40, 2, 4, 2 },
    { 0x3E7B, -8, 22, 0x00, 3, 5, 3 },
    { 0x3E7C, 9, -23, 0x40, 4, 6, 4 },
    { 0x3E7D, -10, 0, 0x00, 5, 7, 5 },
    { 0x33EC, 11, 5, 0x00, 6, 1, 4 },
    { 0x33ED, -12, -6, 0x40, 7, 2, 5 },
    { 0x2DE6, 13, 7, 0x00, 0, 1, 6 },
    { 0x2DE7, -14, 0, 0x40, 1, 2, 7 },
    { 0x072F, 0, 22, 0x00, 3, 0, 7 },
    { 0x56A7, 5, 23, 0x00, 7, 1, 7 },
    { 0x56A8, -6, 0, 0x40, 0, 2, 0 },
    { 0x56A9, 7, 1, 0x00, 1, 3, 1 },
    { 0x56AA, -8, -2, 0x40, 2, 4, 2 },
    { 0x56AB, 9, 3, 0x00, 3, 5, 3 },
    { 0x57AD, -10, -4, 0x40, 4, 6, 5 },
    { 0x57AE, 11, 5, 0x00, 5, 7, 6 },
    { 0x57AF, -12, -6, 0x40, 6, 0, 7 },
    { 0x57B0, 13, 7, 0x00, 7, 1, 0 },
    { 0x57B1, -14, 0, 0x40, 0, 2, 1 },
    { 0x57B2, 15, 1, 0x00, 1, 3, 2 },
    { 0x57B3, 0, -2, 0x40, 2, 4, 3 },
    { 0x57B4, 1, 3, 0x00, 3, 5, 4 },
    { 0x57B5, -2, -4, 0x40, 4, 6, 5 },
    { 0x57B6, 3, 5, 0x00, 5, 7, 6 },
    { 0x57B7, -4, -6, 0x40, 6, 0, 7 },
    { 0x57B8, 5, 7, 0x00, 7, 1, 0 },
    { 0x57B9, -6, -16, 0x40, 0, 2, 1 },
    { 0x57BA, 7, 17, 0x00, 1, 3, 2 },
    { 0x57BB, -8, -18, 0x40, 2, 4, 3 },
    { 0x57BC, 9, 19, 0x00, 3, 5, 4 },
    { 0x57BD, -10, -20, 0x40, 4, 6, 5 },
    { 0x57BE, 11, 21, 0x00, 5, 7, 6 },
    { 0x57BF, -12, -22, 0x40, 6, 0, 7 },
    { 0x57C0, 13, 23, 0x00, 7, 1, 0 },
    { 0x57C1, -14, -16, 0x40, 0, 2, 1 },
    { 0x57C2, 15, 17, 0x00, 1, 3, 2 },
    { 0x57C3, 0, -18, 0x40, 2, 4, 3 },
    { 0x57C4, 1, 19, 0x00, 3, 5, 4 },
    { 0x57C5, -2, -20, 0x40, 4, 6, 5 },
    { 0x57C6, 3, 21, 0x00, 5, 7, 6 },
    { 0x57C7, -4, -22, 0x40, 6, 0, 7 },
    { 0x57C8, 5, 23, 0x00, 7, 1, 0 },
    { 0x51C1, -6, 0, 0x40, 0, 0, 1 },
    { 0x51C2, 7, 1, 0x00, 1, 1, 2 },
    { 0x51C3, -8, -2, 0x40, 2, 2, 3 },
    { 0x51C4, 9, 3, 0x00, 3, 3, 4 },
    { 0x51C5, -10, -4, 0x40, 4, 4, 5 },
    { 0x51C6, 11, 5, 0x00, 5, 5, 6 },
    { 0x51C7, -12, -6, 0x40, 6, 6, 7 },
    { 0x51C8, 13, 7, 0x00, 7, 7, 0 },
    { 0x51C9, -14, 0, 0x40, 0, 0, 1 },
    { 0x51CA, 15, 1, 0x00, 1, 1, 2 },
    { 0x51CB, 0, -2, 0x40, 2, 2, 3 },
    { 0x51CC, 1, 3, 0x00, 3, 3, 4 },
    { 0x51CD, -2, -4, 0x40, 4, 4, 5 },
    { 0x51CE, 3, 5, 0x00, 5, 5, 6 },
    { 0x51CF, -4, -6, 0x40, 6, 6, 7 },
    { 0x51D0, 5, 7, 0x00, 7, 7, 0 },
    { 0xB4E6, -6, -6, 0x40, 6, 2, 6 },
    { 0xB4E7, 7, 7, 0x00, 7, 3, 7 },
    { 0xB4E8, -8, -16, 0x40, 0, 4, 0 },
    { 0xB4E9, 9, 17, 0x00, 1, 5, 1 },
    { 0xB4EA, -10, -18, 0x40, 2, 6, 2 },
    { 0xB4EB, 11, 19, 0x00, 3, 7, 3 },
    { 0xB4EC, -12, -20, 0x40, 4, 0, 4 },
    { 0xB4ED, 13, 21, 0x00, 5, 1, 5 },
    { 0xC90E, -14, -22, 0x00, 2, 5, 6 },
    { 0xC90F, 15, 23, 0x40, 3, 6, 7 },
    { 0xC910, 0, -16, 0x00, 4, 7, 0 },
    { 0xC911, 1, 17, 0x40, 5, 0, 1 },
    { 0xC912, -2, -18, 0x00, 6, 1, 2 },
    { 0xC913, 3, 19, 0x40, 7, 2, 3 },
    { 0xC914, -4, -20, 0x00, 0, 3, 4 },
    { 0xC915, 5, 21, 0x40, 1, 4, 5 },
    { 0xC916, -6, -22, 0x00, 2, 5, 6 },
    { 0xC917, 7, 23, 0x40, 3, 6, 7 },
    { 0xC918, -8, 0, 0x00, 4, 7, 0 },
    { 0xC919, 9, 1, 0x40, 5, 0, 1 },
    { 0xC91A, -10, -2, 0x00, 6, 1, 2 },
    { 0xC91B, 11, 3, 0x40, 7, 2, 3 },
    { 0xC91C, -12, -4, 0x00, 0, 3, 4 },
    { 0xC91D, 13, 5, 0x40, 1, 4, 5 },
    { 0xC91E, -14, -6, 0x00, 2, 5, 6 },
    { 0xCA20, 15, 7, 0x40, 3, 6, 0 },
    { 0xEA51, 0, 0, 0x00, 4, 7, 1 },
    { 0xEA52, 1, 1, 0x40, 5, 0, 2 },
    { 0xEA53, -2, -2, 0x00, 6, 1, 3 },
    { 0xEA54, 3, 3, 0x40, 7, 2, 4 },
    { 0xEA55, -4, -4, 0x00, 0, 3, 5 },
    { 0xEA56, 5, 5, 0x40, 1, 4, 6 },
    { 0xEA57, -6, -6, 0x00, 2, 5, 7 },
    { 0xEA58, 7, 7, 0x40, 3, 6, 0 },
    { 0x2FC1, -6, -6, 0x40, 0, 2, 1 },
    { 0x2FC2, 7, 7, 0x00, 1, 3, 2 },
};

static void fill_words(u32* target, u32 count, u32 value)
{
    while (count >= 4) {
        target[0] = target[1] = target[2] = target[3] = value;
        target += 4;
        count -= 4;
    }
    while (count--)
        *target++ = value;
}

static void prepare(u32 layer, u32 wrap)
{
    u32 i;
    c_test_zero_words((u32*)&controller, sizeof(controller) / 4);
    c_test_zero_words((u32*)&sparkle, sizeof(sparkle) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)&main_bss_state, sizeof(main_bss_state) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < 3; i++) {
        background_objects[i].x_pos.val = cameras[i][0] * 65536;
        background_objects[i].y_pos.val = cameras[i][1] * 65536;
    }
    if (wrap) {
        background_objects[layer].x_pos.val = 32600 * 65536;
        background_objects[layer].y_pos.val = 32600 * 65536;
    }
    for (i = 0; i < 32; i++)
        sprites[i] = 0x35353535;
    sprites[6] = 0x40;
    sprites[11] = 0x60;
    TEST_SPRITE_FRAMES = (u8*)sprites;
    g_Player.active = 0x41;
    g_Player.hp = 24;
    g_Player.weapon = 2;
    g_Player.bg_offset = layer;
    g_Player.shot_count = 3;
    g_Player.special_shot_count = 2;
    controller.active = 1;
    controller.id = 11;
    controller.bg_offset = layer;
    controller.owner = &g_Player;
    controller.unk50 = frost_tower_hit_box;
    controller.unk68 = frost_tower_terrain_box;
    controller.unk40 = 0x4567;
    controller.unk42 = 0x9234;
    controller.unk3C = (u8*)sprites + 0x60;
    controller.animation_table = D_8011C094;
    controller.animation_cursor = D_8011C094[0];
    controller.animation_step.packed = 0x55010203;
    controller.previous_animation_index = 0x37;
    controller.ext.raw[2] = 0x35;
    controller.ext.raw[3] = 0x45;
    controller.x_pos.val = (cameras[layer][0] + 160) * 65536 + 0x1234;
    controller.y_pos.val = (cameras[layer][1] + 120) * 65536 + 0x5678;
    sparkle.active = 1;
    sparkle.id = 47;
    sparkle.bg_offset = layer;
    sparkle.on_screen = 1;
    sparkle.x_pos.val = (background_objects[layer].x_pos.i.hi + 160) * 65536 + 0x1234;
    sparkle.y_pos.val = (background_objects[layer].y_pos.i.hi + (wrap ? 160 : 120)) * 65536 + 0x5678;
    sparkle.unk38 = (u8*)sprites + 0x20;
    sparkle.unk40 = 0x4567;
    sparkle.unk42 = 0x9234;
    controller_input.held = 0x1234;
    controller_input.previous = 0x5678;
    controller_input.pressed = 0x840;
    need_palette_load = 0x20;
    cur_random = random_expected = 0x1234;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
}

static void capture(void)
{
    expected_controller = controller;
    expected_sparkle = sparkle;
    player_before = g_Player;
    engine_before = engine_obj;
    main_before = main_bss_state;
    c_test_copy_words((u32*)backgrounds_before, (const u32*)background_objects, sizeof(backgrounds_before) / 4);
    c_test_zero_words((u32*)weapons_before, sizeof(weapons_before) / 4);
    c_test_zero_words((u32*)misc_before, sizeof(misc_before) / 4);
    c_test_copy_words(sprites_before, sprites, COUNT(sprites));
}

static void same_words(const void* actual, const void* wanted, u32 size)
{
    assert(c_test_word_difference(actual, wanted, size / 4) == 0);
}

static void check(void)
{
    u32 i;
    same_words(&controller, &expected_controller, sizeof(controller));
    same_words(&sparkle, &expected_sparkle, sizeof(sparkle));
    same_words(&g_Player, &player_before, sizeof(player_before));
    same_words(&engine_obj, &engine_before, sizeof(engine_before));
    same_words(&main_bss_state, &main_before, sizeof(main_before));
    same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(c_test_word_difference((const u32*)weapon_objects, (const u32*)weapons_before, sizeof(weapons_before) / 4) == 0);
    assert(c_test_word_difference((const u32*)misc_objects, (const u32*)misc_before, sizeof(misc_before) / 4) == 0);
    same_words(sprites, sprites_before, sizeof(sprites));
    assert(TEST_SPRITE_FRAMES == (u8*)sprites);
    assert(cur_random == random_expected && need_palette_load == 0x20);
    assert(controller_input.held == 0x1234 && controller_input.previous == 0x5678 && controller_input.pressed == 0x840);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    for (i = 0; i < 8; i++) {
        assert(frost_particle_x_vels[i] == x_velocities[i]);
        assert(frost_particle_y_vels[i] == y_velocities[i]);
        assert(frost_sparkle_animations[i] == sparkle_animations[i]);
    }
    for (i = 2; i <= 8; i++)
        assert(*D_8011C018[i] == ((i + 4) << 24 | 0x60));
}

static u32 visible(s16 x_hi, s16 y_hi, u32 layer)
{
    s32 x = x_hi - backgrounds_before[layer].x_pos.i.hi;
    s32 y = y_hi - backgrounds_before[layer].y_pos.i.hi;
    if (x > 32767)
        x -= 65536;
    if (x < -32768)
        x += 65536;
    if (y > 32767)
        y -= 65536;
    if (y < -32768)
        y += 65536;
    return x >= -20 && x < 340 && y >= -24 && y < 264;
}

static void expect_birth(u32 seed)
{
    u32 animation = sparkle_animations[launches[seed].animation];
    expected_sparkle.x_pos.u.hi += launches[seed].dx;
    expected_sparkle.y_pos.u.hi += launches[seed].dy;
    expected_sparkle.unk15 = launches[seed].facing;
    expected_sparkle.x_vel.val = x_velocities[launches[seed].vx];
    expected_sparkle.y_vel.val = y_velocities[launches[seed].vy];
    expected_sparkle.unk28 = 0;
    expected_sparkle.unk2C = 0x5000;
    expected_sparkle.state = 1;
    expected_sparkle.unk5 = 0;
    expected_sparkle.on_screen = visible(expected_sparkle.x_pos.i.hi, expected_sparkle.y_pos.i.hi, expected_sparkle.bg_offset);
    expected_sparkle.unk3C = (u8*)sprites + 0x40;
    expected_sparkle.animation_table = D_8011C018;
    expected_sparkle.unk40 = 0;
    expected_sparkle.unk42 = 0x7802;
    expected_sparkle.unk16 = 0;
    expected_sparkle.unk17 = animation;
    expected_sparkle.previous_animation_index = 0xFF;
    expected_sparkle.animation_cursor = D_8011C018[animation];
    expected_sparkle.animation_step.packed = ((animation + 4) << 24) | 0x60;
    random_expected = launches[seed].random;
}

static u32 test_sparkle_birth(u32 row)
{
    u32 layer = row / 256, seed = row % 256;
    prepare(layer, layer == 2);
    cur_random = seed;
    capture();
    expect_birth(seed);
    frost_sparkle_update(&sparkle);
    check();
    return 1;
}

static void expect_fall(void)
{
    u32 i;
    if (!visible(expected_sparkle.x_pos.i.hi, expected_sparkle.y_pos.i.hi, expected_sparkle.bg_offset)) {
        for (i = 0; i < 8; i++)
            ((u8*)&expected_sparkle)[i] = 0;
        return;
    }
    expected_sparkle.x_pos.val += expected_sparkle.x_vel.val;
    expected_sparkle.y_pos.val -= expected_sparkle.y_vel.val;
    expected_sparkle.y_vel.val -= 0x5000;
    if (expected_sparkle.y_vel.val < -0x68000)
        expected_sparkle.y_vel.val = -0x68000;
    expected_sparkle.on_screen ^= 1;
    if (expected_sparkle.on_screen)
        expected_sparkle.on_screen = visible(expected_sparkle.x_pos.i.hi, expected_sparkle.y_pos.i.hi, expected_sparkle.bg_offset);
}

static const u8 trajectory_seeds[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 16, 31, 63, 95, 127, 159, 191, 255 };
static const u8 prefixes[7] = { 1, 2, 8, 16, 32, 64, 96 };
static u32 test_sparkle_flight(u32 row)
{
    u32 seed = trajectory_seeds[row], layer = row % 2;
    u32 limit = prefixes[(row + 1) % COUNT(prefixes)], i;
    prepare(layer, 0);
    cur_random = seed;
    capture();
    expect_birth(seed);
    frost_sparkle_update(&sparkle);
    same_words(&sparkle, &expected_sparkle, sizeof(sparkle));
    for (i = 0; i < limit && expected_sparkle.active; i++) {
        expect_fall();
        frost_sparkle_update(&sparkle);
        same_words(&sparkle, &expected_sparkle, sizeof(sparkle));
        assert(cur_random == random_expected);
    }
    if (limit == 96)
        assert(expected_sparkle.active == 0);
    check();
    return 1;
}

static const s16 sparkle_edges[9][2] = {
    { 160, 120 },
    { -20, 120 },
    { -21, 120 },
    { 339, 120 },
    { 340, 120 },
    { 160, -24 },
    { 160, -25 },
    { 160, 263 },
    { 160, 264 },
};
static u32 test_sparkle_edges(u32 row)
{
    u32 seed = row % 8, edge = (row / 8) % 9, layer = (row / 72) % 3;
    u32 on_screen = row / 216;
    prepare(layer, 0);
    cur_random = seed;
    capture();
    expect_birth(seed);
    frost_sparkle_update(&sparkle);
    same_words(&sparkle, &expected_sparkle, sizeof(sparkle));
    sparkle.x_pos.val = (cameras[layer][0] + sparkle_edges[edge][0]) * 65536 + 0x1234;
    sparkle.y_pos.val = (cameras[layer][1] + sparkle_edges[edge][1]) * 65536 + 0x5678;
    sparkle.on_screen = on_screen;
    expected_sparkle.x_pos = sparkle.x_pos;
    expected_sparkle.y_pos = sparkle.y_pos;
    expected_sparkle.on_screen = on_screen;
    expect_fall();
    frost_sparkle_update(&sparkle);
    check();
    return 1;
}

static void prepare_graphics(u32 queue)
{
    u32 i;
    fill_words((u32*)player_gfx_buf_1, GFX_WORDS, 0x5A5AA5A5);
    fill_words((u32*)player_gfx_buf_0, 0x400, 0xA5A55A5A);
    for (i = 0; i < 8; i++) {
        vram_rect_ptrs[i].rect.x = 100 + i;
        vram_rect_ptrs[i].rect.y = 200 + i;
        vram_rect_ptrs[i].rect.w = 300 + i;
        vram_rect_ptrs[i].rect.h = 400 + i;
        vram_rect_ptrs[i].ptr = (u_long*)player_gfx_buf_0;
    }
    vram_rect_ptr = &vram_rect_ptrs[queue];
    queue_expected = queue;
    c_test_zero_words((u32*)&frost_archive, sizeof(frost_archive) / 4);
    frost_archive.root[3] = 0x20;
    for (i = 0; i < 16; i++)
        frost_archive.bank[i] = 32 << 20 | ((u8*)frost_archive.stream - (u8*)frost_archive.bank);
    for (i = 1; i <= 16; i++)
        frost_archive.stream[i] = 0x2200;
    frost_archive.stream[17] = 0x7000;
    frost_archive.stream[18] = 0x2200;
    frost_archive.stream[19] = 0x1001;
    frost_archive.stream[21] = 2;
    TEST_PLAYER_GFX = (u8*)&frost_archive;
    c_test_copy_words((u32*)uploads_expected, (const u32*)vram_rect_ptrs, sizeof(uploads_expected) / 4);
    fill_words(pixels_expected, GFX_WORDS, 0x5A5AA5A5);
    fill_words(pixels0_expected, 0x400, 0xA5A55A5A);
}

static u32 test_parent_init(u32 row)
{
    u32 layer = row % 3, fraction = (row / 3) % 2, facing = (row / 6) % 2;
    u32 bank = (row / 12) % 4, queue = row / 48 * 3, i;
    u32* destination;
    prepare(layer, 0);
    prepare_graphics(queue);
    controller.unk49 = bank;
    g_Player.unk15 = facing ? 0x40 : 0;
    if (!fraction)
        controller.x_pos.u.lo = controller.y_pos.u.lo = 0;
    capture();
    expected_controller.unk40 = 0x520;
    expected_controller.previous_animation_index = 9;
    expected_controller.animation_step.fields.frame_index = 9;
    expected_controller.state = 1;
    expected_controller.ext.raw[2] = expected_controller.ext.raw[3] = 0;
    expected_controller.unk5 = 0;
    expected_controller.unk38 = (void*)frost_archive.bank;
    destination = bank == 3 ? pixels0_expected : pixels_expected + bank * 1024;
    for (i = 0; i < 21; i++)
        ((u16*)destination)[i] = i < 19 ? 0x2200 : 0;
    uploads_expected[queue].rect.x = 320;
    uploads_expected[queue].rect.y = 32;
    uploads_expected[queue].rect.w = 64;
    uploads_expected[queue].rect.h = 32;
    uploads_expected[queue].ptr = (u_long*)(bank == 3 ? player_gfx_buf_0 : player_gfx_buf_1 + bank * 1024);
    uploads_expected[++queue_expected].ptr = NULL;
    frost_tower_charged_update(&controller);
    check();
    assert(TEST_PLAYER_GFX == (u8*)&frost_archive);
    same_words(vram_rect_ptrs, uploads_expected, sizeof(uploads_expected));
    assert(vram_rect_ptr == &vram_rect_ptrs[queue_expected]);
    assert(c_test_word_difference((const u32*)player_gfx_buf_1, pixels_expected, GFX_WORDS) == 0);
    assert(c_test_word_difference((const u32*)player_gfx_buf_0, pixels0_expected, 0x400) == 0);
    return 1;
}

static const s16 tower_edges[4][2] = { { -41, 120 }, { 360, 120 }, { 160, -57 }, { 160, 296 } };
static u32 test_tower_outside(u32 row)
{
    u32 edge = row % 4, layer = (row / 4) % 3, lifetime = (row / 12) % 2;
    prepare(layer, 0);
    controller.id = 2;
    controller.state = 1;
    controller.on_screen = row / 24;
    controller.animation_step.packed = *D_8011C094[0];
    controller.x_pos.val = (cameras[layer][0] + tower_edges[edge][0]) * 65536 + 0x1234;
    controller.y_pos.val = (cameras[layer][1] + tower_edges[edge][1]) * 65536 + 0x5678;
    controller.ext.weapon_2.lifetime = lifetime;
    capture();
    expected_controller.on_screen = 0;
    expected_controller.state = 3;
    expected_controller.unk50 = expected_controller.unk68 = NULL;
    frost_tower_main(&controller);
    check();
    return 1;
}

static u32 test_tower_damage_timer(u32 row)
{
    static const u8 timers[] = { 0, 1, 8 };
    u32 has_box = row % 2, timer = (row / 2) % 3;
    u32 layer = (row / 6) % 3, on_screen = row / 18;
    prepare(layer, 0);
    controller.id = 2;
    controller.state = 1;
    controller.on_screen = on_screen;
    controller.animation_cursor = D_8011C094[0];
    controller.animation_step.packed = 0x00010002;
    controller.animation_step.fields.duration = 1;
    controller.unk50 = has_box ? frost_tower_hit_box : NULL;
    controller.unk64 = 5;
    controller.ext.weapon_2.lifetime = 149;
    controller.ext.weapon_2.timer = timers[timer];
    capture();
    expected_controller.ext.weapon_2.lifetime = 148;
    expected_controller.animation_cursor = D_8011C094[0] + 1;
    expected_controller.animation_step.packed = 0x01010002;
    expected_controller.on_screen = 1;
    if (has_box) {
        expected_controller.ext.weapon_2.timer = timers[timer] ? timers[timer] - 1 : 8;
        if (!timers[timer])
            expected_controller.unk64 = 6;
    }
    frost_tower_main(&controller);
    check();
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "charged_waves", 0, 0, 20, test_charged_waves },
    { "frost_shard_gates", NULL, frost_shard_gates_cases_expected, COUNT(frost_shard_gates_cases_expected), frost_shard_gates_cases_row },
    { "frost_tower_cancellation_dispatch", NULL, frost_tower_cancellation_dispatch_cases_expected, COUNT(frost_tower_cancellation_dispatch_cases_expected), cancel_case },
    { "frost_tower_spawn_shard", 0, 0, 1, test_frost_tower_spawn_shard },
    { "frost_tower_charged_dispatch", frost_tower_charged_dispatch_cases, frost_tower_charged_dispatch_cases_expected, COUNT(frost_tower_charged_dispatch_cases), 0 },
    { "frost_charged_parent_init", 0, 0, 39, test_parent_init },
    { "frost_sparkle_birth", 0, 0, 2, test_sparkle_birth },
    { "frost_sparkle_flight", 0, 0, 16, test_sparkle_flight },
    { "frost_sparkle_screen_edges", 0, 0, 48, test_sparkle_edges },
    { "frost_tower_outside", 0, 0, 4, test_tower_outside },
    { "frost_tower_damage_timer", 0, 0, 6, test_tower_damage_timer },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 20 + COUNT(frost_shard_gates_cases_expected) + COUNT(frost_tower_cancellation_dispatch_cases_expected) + 1 + COUNT(frost_tower_charged_dispatch_cases) + 39 + 2 + 16 + 48 + 4 + 6;
