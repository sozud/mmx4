#include "test_runtime.h"
#include "main/mains/main_62_flame_jet.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "support/state_cases.h"
void flame_jet_extinguished_idle(void);
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
static const u32 flame_jet_extinguishing_weapons_cases_expected[] = { 0x12360260u, 0x1236025Cu, 0x1236025Cu };

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
static const u32 flame_jet_linked_vent_sync_cases_expected[] = { 0x101u, 0x20202u, 0x20202u, 0x101u, 0x101u, 0x101u };

#define FJ(step) (state_reset(step, 0, 0), so.state = 2, so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, so.unk42 = 0x10)
#define VENT(id) (FJ(1), state_hit(&so, id, 0, 1), so.unk7E = func_8007BABC(&so))
static void fj_smoke(void)
{
    FJ(0);
    so.unk7E = 2;
    func_8007BE40(&so);
}
static void fj_relight(void)
{
    FJ(0);
    so.unk7E = 1;
    so.animation_step.fields.frame_index = 4;
    func_8007BE40(&so);
}
static void fj_relight_left(void)
{
    FJ(0);
    so.unk7E = 1;
    so.unk15 = 0x40;
    so.animation_step.fields.frame_index = 3;
    func_8007BE40(&so);
}
static void fj_idle(void)
{
    FJ(1);
    flame_jet_extinguished_idle();
}
static void fj_vent_frost(void) { VENT(2); }
static void fj_vent_ice(void) { VENT(0xB); }
static void fj_vent_freeze(void) { VENT(0x21); }
static void fj_vent_other(void) { VENT(1); }
static void fj_vent_miss(void)
{
    VENT(2);
    weapon_objects[0].x_pos.i.hi = 0x400;
    so.unk7E = func_8007BABC(&so);
}

static void (*const flame_jet_states_cases[])(void) = {
    fj_smoke,
    fj_relight,
    fj_relight_left,
    fj_idle,
    fj_vent_frost,
    fj_vent_ice,
    fj_vent_freeze,
    fj_vent_other,
    fj_vent_miss,
};
static const u32 flame_jet_states_expected[] = { 0u, 0x10000u, 0x800000u, 0u, 0u, 0u, 0x100000u, 0u, 0u, 0u, 3u, 0xC80000u, 0x800000u, 0u, 0u, 0u, 0xE0002u, 0x7F0000u, 0u, 0u, 3u, 0xC80000u, 0x800000u, 0u, 0u, 0u, 0xE4002u, 0x7F0000u, 0u, 0u, 1u, 0u, 0x800000u, 0u, 0u, 0u, 0x100000u, 0u, 0u, 0u, 1u, 0u, 0x800000u, 0u, 0u, 0u, 0x100000u, 1u, 0u, 0u, 1u, 0u, 0x800000u, 0u, 0u, 0u, 0x100000u, 1u, 0u, 0u, 1u, 0u, 0x800000u, 0u, 0u, 0u, 0x100000u, 1u, 0u, 0u, 1u, 0u, 0x800000u, 0u, 0u, 0u, 0x100000u, 1u, 0u, 0u, 1u, 0u, 0x800000u, 0u, 0u, 0u, 0x100000u, 1u, 0u, 0u };

static u32 test_flame_jet_states(u32 row)
{
    return state_run(flame_jet_states_cases[row], row, &flame_jet_states_expected[row * 10]);
}

extern union AnimationStep* flame_jet_animations[9];
extern struct Unk_unk68 D_80107C78[];
static const s16 positions[3][2] = { { 3195, 983 }, { 3534, 951 }, { 4716, 935 } };
static struct VisualObj expected_pool[32];
static struct MiscObj misc_before[64];
static u32 jet(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u32 kind = row % 3 + 1, available = row / 3 % 3, layer = row / 9, i;
    engine_obj.stage = 4;
    engine_obj.substage = 0;
    engine_before = engine_obj;
    g_Player.bg_offset = layer;
    player_before = g_Player;
    cur_random = 0x1234;
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = i >= 32 - available ? 0 : 1;
    memcpy(expected_pool, visual_objects, sizeof(expected_pool));
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = 1;
    memcpy(misc_before, misc_objects, sizeof(misc_before));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 62;
    obj.state = 1;
    obj.unk2 = kind;
    obj.x_pos.val = positions[kind - 1][0] * 65536 + 0x1234;
    obj.y_pos.val = positions[kind - 1][1] * 65536 + 0x5678;
    expected = obj;
    expected.active = 0x45;
    expected.unk15 = kind % 2 ? 0x40 : 0;
    expected.unk7C = kind < 2 ? 20 : 40;
    expected.ext.main_62.unk80 = available == 2 ? &visual_objects[31] : NULL;
    expected.animation_table = (const u8* const*)flame_jet_animations;
    expected.unk16 = 2;
    expected.collision_data = D_80107C78;
    expected.hp = 127;
    expected.contact_damage = 4;
    expected.bg_offset = layer;
    expected.unk5 = 1;
    for (i = 0; i < available; i++) {
        struct VisualObj* v = &expected_pool[32 - available + i];
        v->active = 0x41;
        v->id = 25;
        v->unk2 = 1 - i;
        v->x_pos.val = obj.x_pos.val + (kind % 2 ? -0x690000 : 0x690000);
        v->y_pos.val = obj.y_pos.val - 0x80000;
        v->unk50 = PLAYER_OBJECT(&obj);
    }
    func_8007B90C(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(visual_objects, expected_pool, sizeof(expected_pool));
    c_test_same_words(misc_objects, misc_before, sizeof(misc_before));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(cur_random == 0x1234);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "flame_jet_states", 0, 0, COUNT(flame_jet_states_cases), test_flame_jet_states },
    { "flame_jet_extinguishing_weapons", NULL, flame_jet_extinguishing_weapons_cases_expected, COUNT(flame_jet_extinguishing_weapons_cases_expected), flame_case },
    { "flame_jet_linked_vent_sync", NULL, flame_jet_linked_vent_sync_cases_expected, COUNT(flame_jet_linked_vent_sync_cases_expected), vent_case },
    { "flame_jet_actual_variants_zero_one_two_arm_slots", NULL, NULL, 27, jet },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(flame_jet_states_cases) + COUNT(flame_jet_extinguishing_weapons_cases_expected) + COUNT(flame_jet_linked_vent_sync_cases_expected) + 27;
