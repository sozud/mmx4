#include "test_runtime.h"
#include "main/weapons/weapon_05_ground_hunter.h"
#include "main/sprite_animations.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static u32 cancelled(void)
{
    struct WeaponObj obj, before;
    struct PlayerObj player_before;
    struct Unk_unk68 box = { 1, 2, 3, 4 };
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.input_locked = 0;
    g_Player.capsule_state = -1;
    g_Player.weapon = 0;
    g_Player.shot_count = 3;
    g_Player.special_shot_count = 2;
    obj.active = 0x41;
    obj.id = 5;
    obj.unk2 = 1;
    obj.on_screen = 1;
    obj.unk5 = 5;
    obj.unk6 = 6;
    obj.unk7 = 7;
    obj.unk50 = &box;
    obj.unk68 = &box;
    obj.unk70 = 0x27;
    obj.unk71 = 0x28;
    assert(MMX4_OFFSET_OF(struct PlayerObj, touching_spikes) < sizeof(obj));
    ((u8*)&obj)[MMX4_OFFSET_OF(struct PlayerObj, touching_spikes)] = 0x29;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    before = obj;
    player_before = g_Player;
    ground_hunter_update(&obj);
    before.unk18.val = before.x_pos.val;
    before.unk1C.val = before.y_pos.val;
    before.active = before.id = before.unk2 = before.on_screen = 0;
    before.state = before.unk5 = before.unk6 = before.unk7 = 0;
    before.unk50 = NULL;
    before.unk68 = NULL;
    before.unk70 = 0;
    ((u8*)&before)[MMX4_OFFSET_OF(struct PlayerObj, touching_spikes)] = 0;
    player_before.shot_count--;
    player_before.special_shot_count--;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(box.unk0 == 1 && box.unk1 == 2 && box.unk2 == 3 && box.unk3 == 4);
    actual = (u8)obj.state | ((u32)(u8)g_Player.shot_count << 8) | ((u32)(u8)g_Player.special_shot_count << 16) | ((u32)(u8)obj.active << 24);
    return actual;
}
static const CTestCase ground_hunter_cancel_collision_cases[] = { cancelled };
static const u32 ground_hunter_cancel_collision_cases_expected[] = { 0x10200u };

static u32 spawn_case(u32 mode, u32 observation)
{
    struct WeaponObj obj, before, pool_before[16];
    struct PlayerObj player_before;
    struct Unk_unk68 hit = { 0, 0, 8, 8 }, terrain = { 0, 0, 8, 8 };
    u32 i, j, actual, mask = 0, cursor = ~0u;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(background_objects, 0, sizeof(background_objects));
    for (i = 0; i < COUNT(weapon_objects); i++) {
        weapon_objects[i].active = 1;
        weapon_objects[i].id = 0x35;
        weapon_objects[i].owner = &g_Player;
        weapon_objects[i].x_pos.val = 0x13572468;
        weapon_objects[i].y_pos.val = 0x24681357;
    }
    if (mode == 1) {
        weapon_objects[3].active = 0;
        weapon_objects[5].active = 0;
    }
    obj.active = 0x41;
    obj.id = 14;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 0x27;
    obj.unk7 = 0x35;
    obj.bg_offset = 0;
    obj.x_pos.val = 80 * 65536 + 0x1357;
    obj.y_pos.val = 90 * 65536 + 0x2468;
    obj.x_vel.val = 0x1357;
    obj.y_vel.val = 0x2468;
    obj.unk50 = &hit;
    obj.unk68 = &terrain;
    obj.unk17 = 0;
    obj.previous_animation_index = 0xA5;
    obj.animation_table = D_8011C0C8;
    obj.animation_cursor = D_8011C0C8[3];
    obj.animation_step.packed = *obj.animation_cursor;
    obj.ext.weapon_14.unk8C = mode == 2 ? 1 : 0;
    obj.ext.weapon_14.unk8D = mode == 1 ? 1 : 2;
    g_Player.bg_offset = 2;
    g_Player.shot_count = 0xFD;
    g_Player.special_shot_count = 0xFE;
    before = obj;
    player_before = g_Player;
    memcpy(pool_before, weapon_objects, sizeof(pool_before));
    func_80096060(&obj);
    before.state = obj.state;
    before.unk5 = obj.unk5;
    before.on_screen = obj.on_screen;
    before.x_vel = obj.x_vel;
    before.y_vel = obj.y_vel;
    before.unk50 = obj.unk50;
    before.unk68 = obj.unk68;
    before.ext.weapon_14 = obj.ext.weapon_14;
    before.animation_cursor = obj.animation_cursor;
    before.animation_step = obj.animation_step;
    before.unk17 = obj.unk17;
    before.previous_animation_index = obj.previous_animation_index;
    player_before.shot_count = g_Player.shot_count;
    player_before.special_shot_count = g_Player.special_shot_count;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < COUNT(weapon_objects); i++) {
        if (mode == 1 && (i == 3 || i == 5)) {
            struct WeaponObj expected = pool_before[i];
            expected.active = 1;
            expected.id = 14;
            expected.unk2 = i == 3 ? 1 : 2;
            expected.bg_offset = g_Player.bg_offset;
            expected.x_pos = obj.x_pos;
            expected.y_pos = obj.y_pos;
            mask |= 1u << i;
            for (j = 0; j < sizeof(expected) / 4; j++)
                assert(((u32*)&weapon_objects[i])[j] == ((u32*)&expected)[j]);
        } else
            for (j = 0; j < sizeof(pool_before[i]) / 4; j++)
                assert(((u32*)&weapon_objects[i])[j] == ((u32*)&pool_before[i])[j]);
    }
    assert(obj.animation_table == D_8011C0C8);
    if (obj.animation_cursor == D_8011C0C8[3])
        cursor = 3;
    if (obj.animation_cursor == D_8011C0C8[6])
        cursor = 6;
    assert(cursor != ~0u);
    assert(obj.unk50 == &hit || obj.unk50 == NULL);
    assert(obj.unk68 == &terrain || obj.unk68 == NULL);
    switch (observation) {
    case 0:
        actual = (u8)obj.state | ((u32)(u8)obj.unk5 << 8) | ((u32)obj.ext.weapon_14.unk8C << 16) | ((u32)obj.ext.weapon_14.unk8D << 24);
        break;
    case 1:
        actual = (u8)g_Player.shot_count | ((u32)(u8)g_Player.special_shot_count << 8) | (mask << 16);
        break;
    case 2:
        actual = obj.animation_step.packed;
        break;
    case 3:
        actual = cursor | ((u32)(obj.unk50 != NULL) << 8) | ((u32)(obj.unk68 != NULL) << 16) | ((u32)obj.on_screen << 24);
        break;
    case 4:
        actual = obj.x_vel.val;
        break;
    default:
        actual = obj.y_vel.val;
        break;
    }
    return actual;
}
static const u32 ground_hunter_spawn_context_cases_expected[] = { 0x1040101u, 0xFFu, 0xA010001u, 0x1010103u, 0x1357u, 0x2468u, 0x40002u, 0x2800FFu, 0x13010002u, 0x1000006u, 0x0u, 0x0u, 0x2000101u, 0xFEFDu, 0xA010001u, 0x1010103u, 0x1357u, 0x2468u };
static u32 ground_hunter_spawn_context_cases_row(u32 row)
{
    return spawn_case(row / 6, row % 6);
}

static u32 ground_hunter_charged_fly_case(u32 mode)
{
    struct WeaponObj weapon, weapon_before;
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&weapon, 0, sizeof(weapon));
    weapon.active = 0x41;
    weapon.id = 5;
    weapon.state = 1;
    weapon.on_screen = 1;
    weapon.bg_offset = -1;
    weapon.x_pos.val = (mode == 2 ? 1000 : 100) * 65536 + 0x1234;
    weapon.y_pos.val = 200 * 65536 + 0x5678;
    weapon.unk98 = mode == 1;
    weapon_before = weapon;
    weapon_before.on_screen = mode == 0;
    if (mode == 1)
        weapon_before.state = 3;
    ground_hunter_charged_shot_fly(&weapon);
    for (i = 0; i < sizeof(weapon) / 4; i++)
        assert(((u32*)&weapon)[i] == ((u32*)&weapon_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)weapon.state | ((u32)(u8)weapon.on_screen << 8);
}
#define CASE(m)                                    \
    static u32 ground_hunter_charged_fly_##m(void) \
    {                                              \
        return ground_hunter_charged_fly_case(m);  \
    }
CASE(0)
CASE(1)
CASE(2)
#undef CASE
static const CTestCase ground_hunter_charged_fly_cases[]
    = {
          ground_hunter_charged_fly_0,
          ground_hunter_charged_fly_1,
          ground_hunter_charged_fly_2,
      };

static const u32 ground_hunter_charged_fly_cases_expected[] = { 0x101u, 0x3u, 0x1u };
const struct CTestGroup c_test_groups[] = {
    { "ground_hunter_cancel_collision", ground_hunter_cancel_collision_cases, ground_hunter_cancel_collision_cases_expected, COUNT(ground_hunter_cancel_collision_cases), 0 },
    { "ground_hunter_spawn_context", NULL, ground_hunter_spawn_context_cases_expected, COUNT(ground_hunter_spawn_context_cases_expected), ground_hunter_spawn_context_cases_row },
    { "ground_hunter_charged_fly", ground_hunter_charged_fly_cases, ground_hunter_charged_fly_cases_expected, COUNT(ground_hunter_charged_fly_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(ground_hunter_cancel_collision_cases) + COUNT(ground_hunter_spawn_context_cases_expected) + COUNT(ground_hunter_charged_fly_cases);
