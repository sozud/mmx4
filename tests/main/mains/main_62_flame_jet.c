#include "test_runtime.h"
#include "main/mains/main_62_flame_jet.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
extern union AnimationStep* flame_jet_animations[9];

static u32 flame_case(u32 mode)
{
    static const u8 ids[3] = { 2, 11, 33 };
    static const u8 hp[3] = { 96, 92, 92 };
    struct MainObj obj, expected;
    struct WeaponObj weapons_before[16];
    struct VisualObj visuals_before[32];
    struct PlayerObj player_before;
    struct Unk_unk68 box = { -2, -2, 4, 4 };
    u32 i;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 0x27;
    }
    obj.active = 0x41;
    obj.id = 62;
    obj.state = 1;
    obj.unk5 = 1;
    obj.hp = 100;
    obj.unk42 = 0x9234;
    obj.collision_data = (const u16*)D_80105FF0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)flame_jet_animations;
    set_animation(&obj, 2);
    obj.animation_cursor = (const u8*)(flame_jet_animations[2] + 1);
    obj.animation_step = flame_jet_animations[2][1];
    assert(obj.animation_step.packed == 0x03010007);
    weapon_objects[0].active = 1;
    weapon_objects[0].id = ids[mode];
    weapon_objects[0].unk50 = (const u8*)&box;
    weapon_objects[0].x_pos.val = 195 * 65536;
    weapon_objects[0].y_pos.val = 180 * 65536;
    g_Player.spike_immune = 1;
    expected = obj;
    player_before = g_Player;
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    expected.hurt_box = (const u8*)flame_jet_hurt_boxes[0];
    expected.attack_box = (const u8*)flame_jet_attack_boxes[0];
    expected.hp = hp[mode];
    expected.unk5 = 0;
    expected.unk7E = 20;
    expected.state = 2;
    expected.unk42 = 0x1236;
    weapons_before[0].unk80.word = 195 | (180u << 16);
    if (mode == 2)
        player_before.update_delay_request = 1;
    flame_jet_main(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(weapons_before) / 4; i++)
        assert(((u32*)weapon_objects)[i] == ((u32*)weapons_before)[i]);
    for (i = 0; i < sizeof(visuals_before) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)visuals_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    return (u8)obj.hp | ((u32)(u8)obj.state << 8) | ((u32)obj.unk42 << 16);
}
#define CASE(m)                                                \
    static u32 flame_jet_extinguishing_weapons_flame_##m(void) \
    {                                                          \
        return flame_case(m);                                  \
    }
CASE(0)
CASE(1)
CASE(2)
#define ENTRY(m) flame_jet_extinguishing_weapons_flame_##m,
static const CTestCase flame_jet_extinguishing_weapons_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) };
static const u32 flame_jet_extinguishing_weapons_cases_expected[] = { 0x12360260u, 0x1236025Cu, 0x1236025Cu };
#undef CASE
#undef ENTRY

static u32 vent_case(u32 mode)
{
    static const u8 ids[3] = { 2, 11, 33 };
    struct MainObj obj, expected;
    struct VisualObj signal, signal_before;
    struct WeaponObj weapons_before[16];
    struct PlayerObj player_before;
    struct Unk_unk68 box = { -2, -2, 4, 4 };
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&signal, 0, sizeof(signal));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    obj.active = 0x41;
    obj.id = 62;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk2 = mode == 2 ? 4 : 0;
    obj.ext.main_62.unk80 = &signal;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)flame_jet_animations;
    set_animation(&obj, 0);
    signal.animation_table = (const u8* const*)flame_jet_animations;
    set_animation(&signal, 0);
    if (mode != 0 && mode != 2) {
        signal.animation_cursor = (void*)(flame_jet_animations[0] + 1);
        signal.animation_step = flame_jet_animations[0][1];
        assert(signal.animation_step.packed == 0x01010101);
    }
    if (mode >= 3) {
        weapon_objects[0].active = 1;
        weapon_objects[0].id = ids[mode - 3];
        weapon_objects[0].unk50 = (const u8*)&box;
        weapon_objects[0].x_pos.val = 190 * 65536;
        weapon_objects[0].y_pos.val = 180 * 65536;
    }
    expected = obj;
    signal_before = signal;
    player_before = g_Player;
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    expected.hurt_box = (const u8*)&flame_jet_vent_box;
    if (mode >= 3)
        weapons_before[0].unk80.word = 190 | (180u << 16);
    if (mode == 1 || mode == 2) {
        expected.unk5 = 2;
        expected.state = 2;
        expected.unk17 = 2;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (const u8*)flame_jet_animations[2];
        expected.animation_step = *flame_jet_animations[2];
    }
    flame_jet_wait_sync(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(signal) / 4; i++)
        assert(((u32*)&signal)[i] == ((u32*)&signal_before)[i]);
    for (i = 0; i < sizeof(weapons_before) / 4; i++)
        assert(((u32*)weapon_objects)[i] == ((u32*)weapons_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.state | ((u32)(u8)obj.unk5 << 8) | ((u32)obj.unk17 << 16);
}
#define CASE(m)                                          \
    static u32 flame_jet_linked_vent_sync_vent_##m(void) \
    {                                                    \
        return vent_case(m);                             \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
#define ENTRY(m) flame_jet_linked_vent_sync_vent_##m,
static const CTestCase flame_jet_linked_vent_sync_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) };
static const u32 flame_jet_linked_vent_sync_cases_expected[] = { 0x101u, 0x20202u, 0x20202u, 0x101u, 0x101u, 0x101u };
#undef CASE
#undef ENTRY

const struct CTestGroup c_test_groups[] = {
    { "flame_jet_extinguishing_weapons", flame_jet_extinguishing_weapons_cases, flame_jet_extinguishing_weapons_cases_expected, COUNT(flame_jet_extinguishing_weapons_cases), 0 },
    { "flame_jet_linked_vent_sync", flame_jet_linked_vent_sync_cases, flame_jet_linked_vent_sync_cases_expected, COUNT(flame_jet_linked_vent_sync_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(flame_jet_extinguishing_weapons_cases) + COUNT(flame_jet_linked_vent_sync_cases);
