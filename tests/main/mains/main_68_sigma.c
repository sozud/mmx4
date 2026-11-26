#include "test_runtime.h"
#include "support/platform_fixture.h"
#ifndef VERSION_DEMO
#include "main/mains/main_68_sigma.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "main/sprite_animations.h"
#include "main/shots/shot_46_sigma_shot.h"
extern struct Unk_unk68 D_80107F84[32];
extern void* sigma_animations[44];

static u32 flash_case(u32 mode, u32 observation)
{
    struct MainObj obj, before;
    struct WeaponObj weapons_before[16];
    struct VisualObj visuals_before[32];
    struct PlayerObj player_before;
    struct Unk_unk68 box = { -2, -2, 4, 4 };
    u32 i, table_kind;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = 1;
    SPIKE_IMMUNE_SET(g_Player, 1);
    obj.active = 0x41;
    obj.id = 68;
    obj.state = 1;
    obj.unk5 = 4;
    obj.unk6 = 5;
    obj.on_screen = 1;
    obj.hp = 100;
    obj.unk7C = 2;
    obj.unk42 = 0x2718;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.hurt_box = &box;
    obj.attack_box = &box;
    obj.collision_data = D_80107F84;
    obj.ext.main_68.flash_timer = mode ? 1 : 2;
    weapon_objects[0].active = 1;
    weapon_objects[0].id = 35;
    weapon_objects[0].unk50 = &box;
    weapon_objects[0].x_pos = obj.x_pos;
    weapon_objects[0].y_pos = obj.y_pos;
    table_kind = ((u8*)D_80107F84)[70] | ((u32)((u8*)D_80107F84)[71] << 8);
    assert(table_kind == 0x600);
    D_8013E198[1] = -1;
    before = obj;
    player_before = g_Player;
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    func_80084EE4(&obj);
    before.hp = obj.hp;
    before.unk42 = obj.unk42;
    before.ext.main_68.flash_timer = obj.ext.main_68.flash_timer;
    before.collision_data = mode ? D_801060F0 : D_80107F84;
    before.unk18 = obj.x_pos;
    before.unk1C = obj.y_pos;
    before.unk7C = 1;
    before.on_screen = 0;
    before.attack_box = NULL;
    before.hurt_box = NULL;
    weapons_before[0].unk80 = weapon_objects[0].unk80;
    player_before.update_delay_request = 1;
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(weapon_objects, weapons_before, sizeof(weapons_before));
    c_test_same_words(visual_objects, visuals_before, sizeof(visuals_before));
    assert(box.unk0 == -2 && box.unk1 == -2 && box.unk2 == 4 && box.unk3 == 4);
    assert(D_8013E198[1] == -1 && table_kind == (((u8*)D_80107F84)[70] | ((u32)((u8*)D_80107F84)[71] << 8)));
    switch (observation) {
    case 0:
        return (u8)obj.hp | ((u32)obj.ext.main_68.flash_timer << 8) | ((u32)obj.unk42 << 16);
    case 1:
        return (u8)obj.state | ((u32)(u8)obj.unk5 << 8) | ((u32)(u8)obj.unk6 << 16) | ((u32)(u8)obj.on_screen << 24);
    case 2:
        return obj.unk18.val;
    case 3:
        return obj.unk1C.val;
    case 4:
        return (u16)obj.unk7C | ((u32)g_Player.update_delay_request << 16);
    case 5:
        return TEST_LE_HALVES(&weapon_objects[0].unk80);
    default:
        return obj.collision_data == D_801060F0 ? 1 : 0;
    }
}
#define CASE(m, n)                                          \
    static u32 sigma_cloak_flash_hits_flash_##m##_##n(void) \
    {                                                       \
        return flash_case(m, n);                            \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1) CASE(m, 2) CASE(m, 3) CASE(m, 4) CASE(m, 5) CASE(m, 6)
MODE(0)
MODE(1)
#define ENTRY(m, n) sigma_cloak_flash_hits_flash_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1) ENTRY(m, 2) ENTRY(m, 3) ENTRY(m, 4) ENTRY(m, 5) ENTRY(m, 6)
static const CTestCase sigma_cloak_flash_hits_cases[]
    = { ENTRIES(0) ENTRIES(1) };
static const u32 sigma_cloak_flash_hits_cases_expected[] = { 0xA718015Eu, 0x50401u, 0x641234u, 0xC85678u, 0x10001u, 0xC80064u, 0x0u, 0x2718405Eu, 0x50401u, 0x641234u, 0xC85678u, 0x10001u, 0xC80064u, 0x1u };
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

static u32 laser_case(u32 mode)
{
    struct MainObj obj, before;
    struct QuadObj pool_before[32];
    struct PlayerObj player_before = g_Player;
    u32 i, right = mode == 3 || mode == 4, firing = mode >= 1 && mode <= 4;
    memset(&obj, 0, sizeof(obj));
    memset(g_QuadObjects, 0, sizeof(g_QuadObjects));
    for (i = 0; i < 32; i++) {
        g_QuadObjects[i].active = 1;
        g_QuadObjects[i].id = 0x27;
        g_QuadObjects[i].state = 0x28;
    }
    if (mode == 2 || mode == 3)
        g_QuadObjects[17].active = g_QuadObjects[31].active = 0;
    if (mode == 4)
        g_QuadObjects[31].active = 0;
    obj.active = 0x41;
    obj.id = 68;
    obj.state = 1;
    obj.unk5 = 6;
    obj.unk6 = 2;
    obj.unk15 = right ? PLAYER_FACING_RIGHT : 0;
    obj.ext.main_68.effect = (struct EffectObj*)&g_QuadObjects[0];
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)sigma_animations;
    set_animation_frame(&obj, 28, mode == 0 ? 0 : mode == 5 ? 4
                                                            : 3);
    D_8013E198[2] = -1;
    before = obj;
    memcpy(pool_before, g_QuadObjects, sizeof(pool_before));
    sigma_eye_laser_fire(&obj);
    before.animation_step.fields.duration--;
    if (firing)
        before.animation_step.fields.event = 0;
    if (mode == 2 || mode == 3) {
        pool_before[17].active = pool_before[31].active = 1;
        pool_before[17].id = pool_before[31].id = 15;
        pool_before[17].unk2 = right ? 2 : 0;
        pool_before[31].unk2 = right ? 3 : 1;
        pool_before[17].unk5C = pool_before[31].unk5C = PLAYER_OBJECT(&obj);
        before.ext.main_68.effect = (struct EffectObj*)&g_QuadObjects[31];
    }
    if (mode == 4) {
        pool_before[31].active = 1;
        pool_before[31].id = 15;
        pool_before[31].unk2 = 2;
        pool_before[31].unk5C = PLAYER_OBJECT(&obj);
        before.ext.main_68.effect = (struct EffectObj*)&g_QuadObjects[31];
    }
    if (mode == 5) {
        before.unk6++;
        before.unk17 = 29;
        before.previous_animation_index = 0xFF;
        before.animation_cursor = (const u8*)sigma_animations[29];
        before.animation_step = *(union AnimationStep*)sigma_animations[29];
    }
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(g_QuadObjects, pool_before, sizeof(pool_before));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    assert(D_8013E198[2] == -1);
    return (u8)obj.unk6 | ((u32)obj.unk17 << 8) | ((u32)(u8)g_QuadObjects[31].unk2 << 16) | ((u32)obj.animation_step.fields.event << 24);
}
static const u32 sigma_eye_laser_quad_pool_cases_expected[] = { 0x1C02u, 0x1C02u, 0x11C02u, 0x31C02u, 0x21C02u, 0x1D03u };

static u32 pose_case(u32 mode, u32 observation)
{
    struct MainObj obj, before;
    struct VisualObj visuals_before[32];
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 0x27;
        visual_objects[i].state = 0x28;
    }
    if (mode == 0)
        visual_objects[17].active = 0;
    obj.active = 0x41;
    obj.id = 68;
    obj.state = 1;
    obj.unk7C = 0x27;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)sigma_animations;
    set_animation(&obj, 0);
    before = obj;
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    sigma_pose(&obj);
    before.unk7 = 1;
    before.unk7C = 0x78;
    before.unk17 = 0x29;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = (const u8*)sigma_animations[0x29];
    before.animation_step = *(union AnimationStep*)sigma_animations[0x29];
    if (mode == 0) {
        visuals_before[17].active = 0x41;
        visuals_before[17].id = 0x20;
        visuals_before[17].unk2 = 5;
    }
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(visual_objects, visuals_before, sizeof(visuals_before));
    return observation == 0 ? (u8)obj.unk7 | ((u32)(u16)obj.unk7C << 16) : C_TEST_STEP(obj.animation_step.packed);
}
#define CASE(m, n)                                         \
    static u32 sigma_pose_visual_pool_pose_##m##_##n(void) \
    {                                                      \
        return pose_case(m, n);                            \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1)
MODE(0)
MODE(1)
#define ENTRY(m, n) sigma_pose_visual_pool_pose_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1)
static const CTestCase sigma_pose_visual_pool_cases[]
    = { ENTRIES(0) ENTRIES(1) };
static const u32 sigma_pose_visual_pool_cases_expected[] = { 0x780001u, 0x8A000001u, 0x780001u, 0x8A000001u };
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

static s32 sprites[4] = { 8, 12, 0x11223344, 0x55667788 };
static u32 revealed_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_expected;
    struct WeaponObj weapons_expected[16];
    struct VisualObj visuals_expected[32];
    struct BackgroundObj backgrounds_before[3];
    struct QuadObj quads_before[32];
    struct Unk_unk68 box = { -2, -2, 4, 4 };
    u32 i, free_slots = mode <= 2 ? mode : mode == 3 ? 2
        : mode <= 6                                  ? mode - 4
                                                     : 0;
    u32 weapon_id = mode == 16 ? 23 : mode == 17 ? 24
        : mode == 18                             ? 26
        : mode == 19                             ? 18
        : mode <= 2 || mode == 11                ? 1
        : mode == 3                              ? 10
        : mode >= 4 && mode <= 6 || mode == 12   ? 36
        : mode == 9 || mode == 10                ? 2
                                                 : 0;
    u32 immune = mode == 9 || mode == 10, dying = mode == 11 || mode == 12, hit = mode < 13 || mode >= 15;
    u32 character = mode >= 16 && mode <= 18 || mode >= 4 && mode <= 6 || mode == 10 || mode == 12 || mode == 15 ? CHARACTER_ZERO : CHARACTER_X;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memcpy(quads_before, g_QuadObjects, sizeof(quads_before));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    TEST_SPRITE_FRAMES = (u8*)sprites;
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = i >= 32 - free_slots ? 0 : 1;
        visual_objects[i].id = 39;
        visual_objects[i].state = 40;
        visual_objects[i].unk2 = 9;
        visual_objects[i].unk5 = 3;
        visual_objects[i].unk6 = 4;
        visual_objects[i].unk15 = 0x20;
        visual_objects[i].unk42 = 0x7777;
        visual_objects[i].bg_offset = 2;
        visual_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        visual_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    obj.active = 0x41;
    obj.id = 68;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 5;
    obj.on_screen = 1;
    obj.hp = dying ? 1 : 100;
    obj.unk7C = 9;
    obj.unk42 = 0xA718;
    obj.bg_offset = -1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.hurt_box = &box;
    obj.attack_box = NULL;
    obj.collision_data = D_80108004;
    if (mode == 16 || mode == 17)
        obj.collision_data = D_80108104;
    obj.ext.main_68.flash_timer = mode == 16 || mode == 17 || mode == 7 || mode == 13 ? 2 : mode == 8 || mode == 14 ? 1
                                                                                                                    : 0;
    SPIKE_IMMUNE_SET(g_Player, dying ? 0 : 1);
    engine_obj.cur_character = character;
    if (hit) {
        weapon_objects[0].active = 1;
        weapon_objects[0].id = weapon_id;
        weapon_objects[0].unk50 = &box;
        weapon_objects[0].bg_offset = -1;
        weapon_objects[0].x_pos = obj.x_pos;
        weapon_objects[0].y_pos = obj.y_pos;
    }
    expected = obj;
    player_expected = g_Player;
    engine_expected = engine_obj;
    if (mode == 18)
        player_expected.update_delay_request = 1;
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    memcpy(visuals_expected, visual_objects, sizeof(visuals_expected));
    expected.unk42 &= 0x7FFF;
    if (hit) {
        TEST_SET_HALVES(weapons_expected[0].unk80, 100, 200);
        if (immune)
            expected.unk63 = -1;
        else {
            u32 damage = mode == 16 ? 0 : mode == 17 ? 2
                : mode >= 18                         ? 3
                : weapon_id == 0                     ? 1
                                                     : 4;
            assert(((u8*)obj.collision_data)[weapon_id * 2] == 0 && ((u8*)obj.collision_data)[weapon_id * 2 + 1] == damage);
            expected.hp = dying ? 0 : 100 - damage;
            expected.unk42 |= 0x8000;
            if (weapon_id == 0 || weapon_id == 36 || weapon_id == 18)
                weapons_expected[0].unk98 = 1;
        }
        if (free_slots) {
            struct VisualObj* visual = &visuals_expected[32 - free_slots];
            visual->active = 0x21;
            visual->id = 3;
            visual->unk2 = weapon_id == 36 ? 7 : 3;
            visual->bg_offset = -1;
            visual->animation_table = D_8011BF40;
            visual->unk40 = WEAPON_TEXTURE_BASE;
            visual->unk42 = WEAPON_PALETTE_2;
            visual->unk16 = VISUAL_SATURN_LAYER(0);
            visual->unk3C = (u8*)sprites + 12;
            visual->x_pos.i.hi = 100;
            visual->y_pos.i.hi = 200;
            visual->unk15 = PLAYER_FACING_RIGHT;
        }
    }
    if (expected.ext.main_68.flash_timer) {
        expected.ext.main_68.flash_timer--;
        if (expected.ext.main_68.flash_timer & 1)
            expected.unk42 |= 0x8000;
        else
            expected.unk42 &= 0x7FFF;
    }
    if (dying) {
        expected.state = 2;
        expected.unk5 = 0;
        expected.unk42 &= 0x7FFF;
        SPIKE_IMMUNE_SET(player_expected, 1);
    } else {
        if (hit && !immune) {
            if (mode <= 6 && free_slots == 2) {
                visuals_expected[31].active = 0x41;
                visuals_expected[31].id = 0x20;
                visuals_expected[31].unk2 = 6;
                visuals_expected[31].unk50 = PLAYER_OBJECT(&obj);
            }
            if (mode != 16 && mode != 17 && !expected.ext.main_68.flash_timer) {
                expected.collision_data = D_801060F0;
                expected.ext.main_68.flash_timer = 64;
            }
        }
        expected.unk18 = obj.x_pos;
        expected.unk1C = obj.y_pos;
    }
    func_8008502C(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    c_test_same_words(weapon_objects, weapons_expected, sizeof(weapons_expected));
    c_test_same_words(visual_objects, visuals_expected, sizeof(visuals_expected));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    c_test_same_words(g_QuadObjects, quads_before, sizeof(quads_before));
    assert(box.unk0 == -2 && box.unk1 == -2 && box.unk2 == 4 && box.unk3 == 4);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    assert(sprites[0] == 8 && sprites[1] == 12 && sprites[2] == 0x11223344 && sprites[3] == 0x55667788);
    i = (u8)obj.hp | ((u32)obj.ext.main_68.flash_timer << 8) | ((u32)(u8)obj.state << 16) | ((u32)(u8)visual_objects[31].id << 24);
    return i;
}
static const u32 sigma_revealed_hit_visual_pools_cases_expected[] = { 0x27014060u, 0x3014060u, 0x20014060u, 0x20014060u, 0x27014060u, 0x3014060u, 0x20014060u, 0x27010163u, 0x27014063u, 0x27010064u, 0x27010064u, 0x27020000u, 0x27020000u, 0x27010164u, 0x27010064u, 0x27014063u, 0x27010164u, 0x27010162u, 0x27014061u, 0x27014061u };

static const u32 sigma_pose_expected[] = { 0xFFFFFFFFu, 0xFFFFFFFFu, 0u, 0u, 0u };
static u32 test_sigma_pose(u32 row)
{
    u32 observed_values[5];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    obj.unk7 = -1;
    FILL_ACTIVE(visual_objects, 32, 0);
    sigma_pose(&obj);
    observed_values[0] = (u32)obj.unk7;
    observed_values[1] = (u32)obj.unk7C;
    observed_values[2] = (u32)visual_objects[0].active;
    observed_values[3] = (u32)visual_objects[0].id;
    observed_values[4] = (u32)visual_objects[0].unk2;
    return c_test_observe(0, row, observed_values, sigma_pose_expected, 5);
}

#include "support/pool_full.h"
static u32 pool_full_sigma_scythe_plant_throw(void)
{
    u32 actual;
    pf_prepare();
    pf_event(1, 1);
    pf_snapshot();
    sigma_scythe_plant_throw(&pf_self);
    pf_expected.animation_step.fields.event = 0;
    pf_animated();
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_sigma_intro_wait_player(void)
{
    u32 actual;
    pf_prepare();
    g_Player.capsule_state = 0;
    pf_snapshot();
    sigma_intro_wait_player(&pf_self);
    pf_backgrounds_expected[0].unk24 -= 0x10;
    pf_script(0x14, PLAYER_FACING_RIGHT);
    pf_expected.unk5++;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_sigma_death_blink(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 1;
    pf_self.unk7E = 1;
    pf_snapshot();
    pf_expected.unk7C = 0;
    pf_expected.unk7E = 0;
    pf_expected.on_screen = 1;
    sigma_death_blink(&pf_self);
    pf_expected.unk5++;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_sigma_darts_spawn(void)
{
    u32 actual;
    pf_prepare();
    pf_event(1, 1);
    pf_snapshot();
    sigma_darts_spawn(&pf_self);
    pf_expected.animation_step.fields.event = 0;
    pf_animated();
    pf_expected.unk6++;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_sigma_cloak_stagger_trail(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 2;
    pf_snapshot();
    sigma_cloak_stagger_trail(&pf_self);
    pf_expected.unk7C = 1;
    pf_expected.on_screen = 1;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_sigma_reveal_fall(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    sigma_reveal_fall(&pf_self);
    pf_animated();
    pf_expected.on_screen = 1;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_sigma_scythe_plant_throw,
    pool_full_sigma_intro_wait_player,
    pool_full_sigma_death_blink,
    pool_full_sigma_darts_spawn,
    pool_full_sigma_cloak_stagger_trail,
    pool_full_sigma_reveal_fall,
};

static const u32 pool_full_cases_expected[] = { 0x50000u, 0x50001u, 0x1u, 0x50100u, 0x10000u, 0x50000u };

void general_intro_dialogue(struct MainObj*);
void sigma_reveal_dialogue(struct MainObj*);
void sigma_reveal_start(struct MainObj*);
extern void* sigma_animations[44];
extern struct Unk_unk68 D_80103EF0;
static u32 dialogue(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_expected;
    struct AbcObj window_expected;
    struct BackgroundObj backgrounds_before[3];
    u32 sigma = row % 2, character = row / 2 % 2, side = row / 4 % 3, wait = row / 12 % 2, played = row / 24;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&abc_object, 0, sizeof(abc_object));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 0x41;
    obj.id = sigma ? 68 : 75;
    obj.state = sigma ? 4 : 0;
    obj.unk5 = sigma ? 4 : 5;
    obj.unk7C = 1 + wait;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    if (sigma) {
        obj.animation_table = (const u8* const*)sigma_animations;
        set_animation(&obj, 15);
        obj.animation_cursor = (const u8*)sigma_animations[15] + 24;
        obj.animation_step.packed = C_TEST_STEP(0x3C000021);
        assert(*(const u32*)obj.animation_cursor == C_TEST_STEP(0x3C000021));
    }
    g_Player.x_pos.val = obj.x_pos.val + ((s32)side - 1) * 65536;
    g_Player.stun_timer = 3;
    engine_obj.cur_character = character;
    engine_obj.stage = sigma ? 9 : 11;
    engine_obj.character_state.bytes[sigma ? 9 : 8] = played;
    abc_object.unkC = 0x80;
    abc_object.unk10 = 0x1234;
    abc_object.unkA = 9;
    abc_object.unkD = 7;
    expected = obj;
    player_expected = g_Player;
    engine_expected = engine_obj;
    window_expected = abc_object;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    if (sigma) {
        expected.animation_step.fields.duration = 32;
        expected.unk6 = 1;
        expected.unk15 = side ? PLAYER_FACING_RIGHT : 0;
        expected.on_screen = 1;
        player_expected.script_state = 1;
        player_expected.script_action = 20;
        player_expected.script_facing = side < 2 ? PLAYER_FACING_RIGHT : 0;
        SPIKE_IMMUNE_SET(player_expected, 1);
        engine_expected.gameplay_locked = 1;
        engine_expected.character_state.bytes[9] = 1;
        window_expected.unk10 = 0x8000 | (character ? 0x2C : 0x31);
    } else {
        expected.unk7C--;
        if (!wait) {
            expected.unk6 = 1;
            engine_expected.character_state.bytes[8] = 1;
            window_expected.unk10 = 0x8000 | (character ? 0x21 : 0x29);
        }
    }
    if (sigma)
        sigma_reveal_dialogue(&obj);
    else
        general_intro_dialogue(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    c_test_same_words(&abc_object, &window_expected, sizeof(abc_object));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    return 1;
}
static u32 reveal(u32 row)
{
    struct MainObj obj, expected;
    struct ShotObj scythe, scythe_expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 side = row % 3, face = row / 3;
    memset(&obj, 0, sizeof(obj));
    memset(&scythe, 0, sizeof(scythe));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    obj.active = 0x41;
    obj.id = 68;
    obj.state = 4;
    obj.unk15 = face ? PLAYER_FACING_RIGHT : 0;
    obj.unk42 = 0x9234;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)sigma_animations;
    obj.ext.main_68.scythe = MAIN_OBJECT(&scythe);
    scythe.active = 0x41;
    scythe.id = 46;
    scythe.unk2 = 7;
    scythe.animation_table = (u32**)sigma_animations;
    g_Player.x_pos.val = obj.x_pos.val + ((s32)side - 1) * 65536;
    player_before = g_Player;
    expected = obj;
    scythe_expected = scythe;
    expected.unk4B = -1;
    expected.terrain_box = &D_80103EF0;
    expected.y_speed = -65536;
    expected.x_speed = 0;
    expected.unk42 = 0x1234;
    expected.unk5 = 1;
    expected.unk15 = side ? PLAYER_FACING_RIGHT : 0;
    expected.on_screen = 1;
    expected.unk17 = 8;
    expected.previous_animation_index = 255;
    expected.animation_cursor = sigma_animations[8];
    expected.animation_step.packed = C_TEST_STEP(0x00010001);
    scythe_expected.unk17 = 9;
    scythe_expected.previous_animation_index = 255;
    scythe_expected.animation_cursor = sigma_animations[9];
    scythe_expected.animation_step.packed = C_TEST_STEP(0x01010001);
    D_8013E198[2] = -1;
    sigma_reveal_start(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&scythe, &scythe_expected, sizeof(scythe));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    return 1;
}

void sigma_cloak_teleport_appear(struct MainObj*);
void sigma_cloak_teleport_fade_in(struct MainObj*);
extern void* sigma_animations[44];
static struct ShotObj expected_shots[32];
static struct VisualObj expected_visuals[32];
static u32 attack(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player;
    struct EngineObj engine;
    struct ShotObj* scythe = &shot_objects[0];
    u32 fire = row % 2, far = row / 2, i;
    engine_obj.stage = 12;
    engine_obj.substage = 1;
    engine = engine_obj;
    background_objects[0].x_pos.i.hi = 1088;
    background_objects[0].y_pos.i.hi = 256;
    g_Player.x_pos.val = (far ? 1392 : 1232) * 65536;
    player = g_Player;
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    for (i = 0; i < COUNT(shot_objects); i++)
        shot_objects[i].active = 1;
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = i == 31 && fire ? 0 : 1;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 68;
    obj.state = 1;
    obj.unk5 = 3;
    obj.hp = 48;
    obj.animation_table = (const u8* const*)sigma_animations;
    obj.ext.main_68.scythe = (struct MainObj*)scythe;
    scythe->active = 0x41;
    scythe->id = 46;
    scythe->unk7C = WEAPON_OBJECT(&obj);
    func_800A8628(scythe);
    D_8013E198[2] = -1;
    sigma_cloak_teleport_appear(&obj);
    for (i = 0; i < 6; i++)
        test_next_frame(), sigma_cloak_teleport_fade_in(&obj);
    assert(obj.unk6 == 2 && obj.unk7C == 40);
    for (i = 0; i < 39; i++)
        test_next_frame(), func_80083710(&obj);
    assert(obj.unk7C == 1);
    memcpy(expected_shots, shot_objects, sizeof(expected_shots));
    memcpy(expected_visuals, visual_objects, sizeof(expected_visuals));
    expected = obj;
    expected.unk7C = 10;
    expected.unk6 = 3;
    expected.on_screen = 1;
    expected.unk17 = 4;
    expected.previous_animation_index = 255;
    expected.animation_cursor = sigma_animations[4];
    expected.animation_step.packed = C_TEST_STEP(0x17000021);
    expected.ext.main_68.count = 0;
    expected.ext.main_68.shot_type = far ? 1 : 2;
    expected_shots[0].unk17 = 7;
    expected_shots[0].previous_animation_index = 255;
    expected_shots[0].animation_cursor = sigma_animations[7];
    expected_shots[0].animation_step.packed = *(u32*)sigma_animations[7];
    if (fire) {
        func_80083710(&obj);
        assert(obj.ext.main_68.visual == &visual_objects[31] && obj.unk6 == 3 && obj.unk7C == 10);
        for (i = 0; i < 9; i++)
            test_next_frame(), func_800837FC(&obj);
        expected = obj;
        expected.unk7C = 0;
        expected.ext.main_68.count = 1;
        memcpy(expected_shots, shot_objects, sizeof(expected_shots));
        memcpy(expected_visuals, visual_objects, sizeof(expected_visuals));
    }
    cur_random = 0x1234;
    if (fire)
        func_800837FC(&obj);
    else
        func_80083710(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(shot_objects, expected_shots, sizeof(expected_shots));
    c_test_same_words(visual_objects, expected_visuals, sizeof(expected_visuals));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    assert(cur_random == 0x1234 && D_8013E198[2] == -1);
    return 1;
}

extern void* sigma_animations[44];
static struct VisualObj visuals_expected[32];
static struct ShotObj shots_expected[32];
static u32 reveal_sigma_reveal_pool_capacity(u32 row)
{
    struct MainObj obj, expected;
    struct ShotObj scythe, scythe_expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct MainBssState main_before;
    u32 slots = row % 3, shot_free = row / 3 % 2, periodic = row / 6 % 2, face = row / 12, available = slots == 2 ? 21 : slots, first = available && periodic, count = available - first > 20 ? 20 : available - first, i, high;
    u16 rng = 0x1234;
    engine_obj.stage = 12;
    engine_obj.substage = 1;
    engine_before = engine_obj;
    main_bss_state.frame_counter = periodic ? 0 : 1;
    main_before = main_bss_state;
    g_Player.x_pos.i.hi = face ? 180 : 140;
    player_before = g_Player;
    cur_random = rng;
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = i >= 32 - available ? 0 : 1;
    memcpy(visuals_expected, visual_objects, sizeof(visuals_expected));
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    for (i = 0; i < COUNT(shot_objects); i++)
        shot_objects[i].active = i == 31 && shot_free ? 0 : 1;
    memcpy(shots_expected, shot_objects, sizeof(shots_expected));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 68;
    obj.state = 4;
    obj.unk5 = 2;
    obj.hp = 48;
    obj.x_pos.i.hi = 160;
    obj.y_pos.i.hi = 120;
    obj.animation_table = (const u8* const*)sigma_animations;
    obj.unk7C = 1;
    memset(&scythe, 0, sizeof(scythe));
    scythe.active = 0x41;
    scythe.id = 46;
    scythe.state = 1;
    scythe.unk7C = WEAPON_OBJECT(&obj);
    scythe.animation_table = (u32**)sigma_animations;
    obj.ext.main_68.scythe = MAIN_OBJECT(&scythe);
    expected = obj;
    scythe_expected = scythe;
    scythe_expected.state = 2;
    expected.unk7C = 0;
    expected.unk5 = 3;
    expected.ext.main_68.count = count;
    expected.unk17 = 14;
    expected.previous_animation_index = 255;
    expected.animation_cursor = sigma_animations[14];
    expected.animation_step.packed = C_TEST_STEP(0x39010003);
    expected.unk15 = face ? PLAYER_FACING_RIGHT : 0;
    if (first) {
        struct VisualObj* v = &visuals_expected[32 - available];
        v->active = 0x41;
        v->id = 32;
        v->unk2 = 5;
        v->unk50 = PLAYER_OBJECT(&obj);
    }
    for (i = 0; i < count; i++) {
        struct VisualObj* v = &visuals_expected[32 - available + first + i];
        high = (u16)(rng * 3) >> 8;
        rng = ((rng + high) & 255) | high << 8;
        v->active = 0x41;
        v->id = 32;
        v->unk2 = 1;
        v->unk54 = rng & 3;
        v->unk50 = PLAYER_OBJECT(&obj);
    }
    if (shot_free) {
        struct ShotObj* s = &shots_expected[31];
        s->active = 0x41;
        s->id = 46;
        s->unk2 = 9;
        s->unk7C = WEAPON_OBJECT(&obj);
        expected.ext.main_68.scythe = MAIN_OBJECT(&shot_objects[31]);
    }
    func_80085A44(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&scythe, &scythe_expected, sizeof(scythe));
    c_test_same_words(visual_objects, visuals_expected, sizeof(visuals_expected));
    c_test_same_words(shot_objects, shots_expected, sizeof(shots_expected));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_bss_state));
    assert(cur_random == rng);
    return 1;
}

void sigma_scythe_spin_rise(struct MainObj*);
void sigma_scythe_spin_throw(struct MainObj*);
extern void* sigma_animations[44];
static struct ShotObj expected_shots_sigma_spin_throw_capacity[32];
static u32 full(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player = g_Player;
    struct EngineObj engine;
    u32 i;
    (void)row;
    engine_obj.stage = 12;
    engine_obj.substage = 1;
    engine = engine_obj;
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    for (i = 0; i < COUNT(shot_objects); i++)
        shot_objects[i].active = 1;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 68;
    obj.unk2 = 1;
    obj.state = 1;
    obj.hp = 48;
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.x_pos.i.hi = 1232;
    obj.y_pos.i.hi = 336;
    obj.animation_table = (const u8* const*)sigma_animations;
    obj.ext.main_68.scythe = (struct MainObj*)&shot_objects[0];
    shot_objects[0].active = 0x41;
    shot_objects[0].id = 46;
    shot_objects[0].unk7C = WEAPON_OBJECT(&obj);
    func_800A8628(&shot_objects[0]);
    set_animation(&obj, 23);
    sigma_scythe_spin_rise(&obj);
    assert(obj.unk6 == 2 && obj.unk7C == 40);
    for (i = 0; i < 64; i++)
        sigma_scythe_spin_throw(&obj);
    assert(obj.unk7 == 1 && obj.unk17 == 26 && obj.animation_cursor == (const u8*)sigma_animations[26] + 12 && obj.animation_step.fields.duration == 1);
    expected = obj;
    expected.animation_cursor = (const u8*)sigma_animations[26] + 16;
    expected.animation_step.packed = C_TEST_STEP(0x5301000C);
    memcpy(expected_shots_sigma_spin_throw_capacity, shot_objects, sizeof(expected_shots_sigma_spin_throw_capacity));
    cur_random = 0x1234;
    sigma_scythe_spin_throw(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(shot_objects, expected_shots_sigma_spin_throw_capacity, sizeof(expected_shots_sigma_spin_throw_capacity));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    assert(cur_random == 0x1234);
    return 1;
}

void sigma_intro_fill_health(struct MainObj*);
void sigma_intro_wait(struct MainObj*);
void sigma_intro_finish(struct MainObj*);
void sigma_cloak_teleport_appear(struct MainObj*);
void sigma_cloak_teleport(struct MainObj*);
void sigma_cloak_teleport_fade_out(struct MainObj*);
void sigma_cloak_teleport_finish(struct MainObj*);
void sigma_cloak_dash_appear(struct MainObj*);
void sigma_cloak_dash_fade_in(struct MainObj*);
void sigma_cloak_dash_run(struct MainObj*);
void sigma_cloak_dash_fade_out(struct MainObj*);
void sigma_cloak_dash_finish(struct MainObj*);
void sigma_scythe_spin_jump(struct MainObj*);
void sigma_scythe_spin(struct MainObj*);
void sigma_scythe_plant_jump(struct MainObj*);
void sigma_scythe_plant(struct MainObj*);
void sigma_cloak_pick_attack(struct MainObj*);
void sigma_darts(struct MainObj*);
void sigma_scythe_retrieve_jump(struct MainObj*);
void sigma_scythe_retrieve(struct MainObj*);
void sigma_land_pause(struct MainObj*);
void sigma_eye_laser(struct MainObj*);
void sigma_death(struct MainObj*);
void sigma_death_finish(struct MainObj*);
void sigma_cloak_stagger(struct MainObj*);
void sigma_reveal(struct MainObj*);
extern struct Unk_unk68 D_80103EEC;
extern struct Unk_unk68 D_80103EF4;
extern struct Unk_unk68 D_80103EF8;

static struct MainObj sg;
static struct Unk_unk68 sg_box = { -2, -2, 4, 4 };
static u8 sg_damage[0x80];
static u8 sg_sound_rows[0x400];
static void sg_reset(u8 state, u8 unk5, u8 unk6, u8 unk7)
{
#ifndef MMX4_SATURN
    D_80141F50[2] = sg_sound_rows;
#endif
    TEST_SPRITE_FRAMES = (u8*)sprites;
    memset(&sg, 0, sizeof(sg));
    memset(shot_objects, 0, sizeof(shot_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(effect_objects, 0, sizeof(effect_objects));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(background_objects, 0, sizeof(background_objects));
    memset(&g_Player, 0, sizeof(g_Player));
    main_bss_state.frame_counter = 1;
    engine_obj.unk36.timer = 0;
    engine_obj.gameplay_locked = 0;
    sg.active = 0x41;
    sg.id = 68;
    sg.state = state;
    sg.unk5 = unk5;
    sg.unk6 = unk6;
    sg.unk7 = unk7;
    sg.x_pos.i.hi = 160;
    sg.y_pos.i.hi = 120;
    sg.bg_offset = -1;
    sg.animation_table = (const u8* const*)sigma_animations;
    set_animation(&sg, 0);
    shot_objects[0].active = 0x41;
    shot_objects[0].id = 0x2E;
    shot_objects[0].animation_table = (u32**)sigma_animations;
    shot_objects[0].unk7C = WEAPON_OBJECT(&sg);
    sg.ext.main_68.scythe = MAIN_OBJECT(&shot_objects[0]);
}
static void sg_step(s8 duration, s8 event, s8 relative_step)
{
    sg.animation_step.fields.duration = duration;
    sg.animation_step.fields.event = event;
    sg.animation_step.fields.relative_step = relative_step;
}
static void sg_hit(u8 weapon, u8 kind, u8 damage)
{
    memset(sg_damage, 0, sizeof(sg_damage));
    sg_damage[weapon * 2] = kind;
    sg_damage[weapon * 2 + 1] = damage;
    sg.collision_data = sg_damage;
    sg.hurt_box = &sg_box;
    sg.bg_offset = -1;
    weapon_objects[0].active = 1;
    weapon_objects[0].id = weapon;
    weapon_objects[0].unk50 = &sg_box;
    weapon_objects[0].bg_offset = -1;
    weapon_objects[0].x_pos = sg.x_pos;
    weapon_objects[0].y_pos = sg.y_pos;
}

static void sg_intro_wait_player(void)
{
    sg_reset(0, 0, 0, 0);
    g_Player.capsule_state = 1;
    sigma_intro_wait_player(&sg);
    assert(sg.unk5 == 0 && effect_objects[0].active == 0 && g_Player.script_state == 0);
    g_Player.capsule_state = 0;
    sg.on_screen = 1;
    sigma_intro_wait_player(&sg);
    assert(sg.unk5 == 1 && sg.on_screen == 0 && background_objects[0].unk24 == -0x10);
    assert(effect_objects[0].active == 1 && effect_objects[0].id == 0x18 && sg.ext.main_68.effect == &effect_objects[0]);
    assert(g_Player.script_state == 1 && g_Player.script_action == 0x14 && g_Player.script_facing == PLAYER_FACING_RIGHT);
}
static void sg_intro_init(void)
{
    sg_reset(0, 1, 0, 0);
    effect_objects[0].active = 1;
    sg.ext.main_68.effect = &effect_objects[0];
    sg.on_screen = 1;
    func_8008329C(&sg);
    assert(sg.unk5 == 1 && sg.on_screen == 0 && sg.contact_damage == 0);
    effect_objects[0].active = 0;
    FILL_ACTIVE(shot_objects, 32, 1);
    sg.ext.main_68.scythe = NULL;
    sg.ext.main_68.next_attack = 3;
    sg.hp = 9;
    func_8008329C(&sg);
    assert(sg.unk5 == 2 && sg.ext.main_68.scythe == NULL && sg.hp == 0 && sg.contact_damage == 4);
    assert(sg.x_pos.val == 0x5200000 && sg.y_pos.val == 0x16B0000 && sg.unk7C == 1 && sg.unk7E == 0x3C);
    assert(sg.ext.main_68.next_attack == 0 && sg.collision_data == D_80107F84 && sg.unk17 == 0);
    assert(engine_obj.enable_boss == 1 && engine_obj.boss_ptr == &sg);
    shot_objects[5].active = 0;
    sg.unk5 = 1;
    func_8008329C(&sg);
    assert(sg.unk5 == 2 && sg.ext.main_68.scythe == MAIN_OBJECT(&shot_objects[5]));
    assert(shot_objects[5].active == 0x41 && shot_objects[5].id == 0x2E && shot_objects[5].unk2 == 0 && shot_objects[5].unk7C == WEAPON_OBJECT(&sg));
}
static void sg_intro_fill_health(void)
{
    sg_reset(0, 2, 0, 0);
    D_80173C84 = 0;
    sg.unk7E = 1;
    sg.unk7C = 2;
    main_bss_state.frame_counter = 2;
    sg.on_screen = 1;
    sigma_intro_fill_health(&sg);
    assert(sg.unk7E == 0 && sg.hp == 0 && sg.unk7C == 2 && sg.on_screen == 0);
    sigma_intro_fill_health(&sg);
    assert(sg.hp == 1 && sg.unk7C == 1);
    sigma_intro_fill_health(&sg);
    assert(sg.hp == 2 && sg.unk7C == 2);
    engine_obj.unk36.timer = 5;
    D_80173C84 = 1;
    sigma_intro_fill_health(&sg);
    assert(sg.hp == 2 && sg.unk7C == 2 && engine_obj.unk36.timer == 5);
    engine_obj.unk36.timer = 0;
    sg.hp = 0x30;
    main_bss_state.frame_counter = 1;
    sigma_intro_fill_health(&sg);
    assert(sg.unk5 == 3 && sg.unk7C == 0x1E && sg.hp == 0x30 && sg.on_screen == C_TEST_VISIBLE(sg.unk16));
}
static void sg_intro_wait(void)
{
    sg_reset(0, 3, 0, 0);
    sg.unk7C = 3;
    main_bss_state.frame_counter = 2;
    g_Player.script_state = 1;
    engine_obj.gameplay_locked = 1;
    sigma_intro_wait(&sg);
    assert(sg.unk7C == 2 && sg.unk5 == 3 && sg.on_screen == 0);
    main_bss_state.frame_counter = 1;
    sigma_intro_wait(&sg);
    assert(sg.unk7C == 1 && sg.on_screen == C_TEST_VISIBLE(sg.unk16));
    sigma_intro_wait(&sg);
    assert(sg.unk5 == 4 && sg.unk7C == 0x3C && sg.on_screen == 0);
    assert(g_Player.script_state == 0 && engine_obj.gameplay_locked == 0);
}
static void sg_intro_finish(void)
{
    sg_reset(0, 4, 0, 0);
    sg.unk7C = 2;
    sigma_update(&sg);
    assert(sg.unk7C == 1 && sg.state == 0 && sg.unk5 == 4);
    sigma_update(&sg);
    assert(sg.state == 1 && sg.unk5 == 2);
}
static void sg_teleport_appear_left(void)
{
    sg_reset(1, 3, 0, 0);
    g_Player.x_pos.i.hi = 0x400;
    sigma_cloak_teleport_appear(&sg);
    assert(sg.x_pos.i.hi == 0x470 && sg.y_pos.val == FIXED(0x150) && sg.unk15 == PLAYER_FACING_RIGHT);
    assert(sg.unk6 == 1 && sg.unk7C == 5 && sg.unk7E == 4 && sg.ext.main_68.bob_step == 2 && shot_objects[0].unk17 == 5);
}
static void sg_teleport_fire(void)
{
    sg_reset(1, 3, 3, 0);
    sg.unk7C = 1;
    sg.ext.main_68.count = 2;
    sg.ext.main_68.shot_type = 1;
    sg.ext.main_68.visual = &visual_objects[3];
    func_800837FC(&sg);
    assert(shot_objects[1].active == 0x41 && shot_objects[1].id == 0x2E && shot_objects[1].unk2 == 1);
    assert(shot_objects[1].unk99 == 0 && shot_objects[2].unk99 == 1 && shot_objects[1].unk9A == 2 && shot_objects[2].unk9A == 2);
    assert(shot_objects[2].unk7C == WEAPON_OBJECT(&sg) && sg.ext.main_68.active_shots == 2 && sg.ext.main_68.count == 3);
    assert(sg.unk7 == 1 && sg.unk7C == 0x14 && sg.unk6 == 3);
    sg.unk7C = 2;
    func_800837FC(&sg);
    assert(sg.unk7C == 1 && sg.unk6 == 3 && visual_objects[3].state == 0);
    func_800837FC(&sg);
    assert(sg.unk6 == 4 && sg.unk7 == 0 && visual_objects[3].state == 1);
}
static void sg_teleport_wait_shots(void)
{
    sg_reset(1, 3, 4, 0);
    main_bss_state.frame_counter = 10;
    sg.unk7E = 1;
    sg.ext.main_68.bob_step = 2;
    sg.ext.main_68.active_shots = 1;
    sigma_cloak_teleport(&sg);
    assert(sg.unk6 == 4 && sg.y_pos.i.hi == 122 && sg.unk7E == 4 && sg.ext.main_68.bob_step == -2);
    main_bss_state.frame_counter = 11;
    sigma_cloak_teleport(&sg);
    assert(sg.unk6 == 4 && sg.y_pos.i.hi == 122 && sg.unk7E == 4);
    main_bss_state.frame_counter = 10;
    sg.ext.main_68.active_shots = 0;
    sigma_cloak_teleport(&sg);
    assert(sg.unk6 == 5 && sg.unk7C == 0xA && sg.y_pos.i.hi == 120 && sg.unk7E == 3 && sg.ext.main_68.bob_step == -2);
}
static void sg_teleport_fade_out(void)
{
    sg_reset(1, 3, 5, 0);
    sg.unk7C = 2;
    sg.hurt_box = &sg_box;
    sg.attack_box = &sg_box;
    sigma_cloak_teleport_fade_out(&sg);
    assert(sg.unk7C == 1 && sg.unk6 == 5 && sg.on_screen == C_TEST_VISIBLE(sg.unk16) && sg.hurt_box != NULL);
    sigma_cloak_teleport_fade_out(&sg);
    assert(sg.unk6 == 6 && sg.unk7C == 0x78 && sg.on_screen == 0 && sg.hurt_box == NULL && sg.attack_box == NULL);
}
static void sg_teleport_finish(void)
{
    sg_reset(1, 3, 6, 0);
    sg.unk7C = 2;
    background_objects[0].x_pos.i.hi = 0x500;
    sigma_cloak_teleport_finish(&sg);
    assert(sg.unk7C == 1 && sg.unk5 == 3 && sg.x_pos.i.hi == 160);
    sigma_cloak_teleport_finish(&sg);
    assert(sg.unk5 == 2 && sg.unk6 == 0 && sg.x_pos.i.hi == 0x400);
}
static void sg_dash_appear(void)
{
    sg_reset(1, 4, 0, 0);
    g_Player.x_pos.i.hi = 0x4D1;
    sigma_cloak_dash_appear(&sg);
    assert(sg.x_pos.i.hi == 0x460 && sg.unk15 == PLAYER_FACING_RIGHT && sg.y_pos.i.hi == 0x150);
    assert(sg.unk7C == 0xA && sg.unk6 == 1 && sg.unk17 == 0 && shot_objects[0].unk17 == 5);
    g_Player.x_pos.i.hi = 0x4D0;
    sigma_cloak_dash_appear(&sg);
    assert(sg.x_pos.i.hi == 0x540 && sg.unk15 == 0 && sg.unk6 == 2);
}
static void sg_dash_fade_in(void)
{
    sg_reset(1, 4, 1, 0);
    sg.unk7C = 2;
    sigma_cloak_dash_fade_in(&sg);
    assert(sg.unk7C == 1 && sg.unk6 == 1 && sg.on_screen == C_TEST_VISIBLE(sg.unk16));
    sigma_cloak_dash_fade_in(&sg);
    assert(sg.unk6 == 2 && sg.unk7C == 0x28 && sg.on_screen == 0);
}
static void sg_dash_start(void)
{
    sg_reset(1, 4, 2, 0);
    sg.unk7C = 2;
    func_80083C2C(&sg);
    assert(sg.unk7C == 1 && sg.unk7 == 0 && sg.attack_box == &D_80103EE4 && sg.hurt_box == &D_80103EE8);
    func_80083C2C(&sg);
    assert(sg.unk7 == 1 && sg.unk15 == PLAYER_FACING_RIGHT && sg.hurt_box == &D_80103EF8 && sg.unk17 == 1 && shot_objects[0].unk17 == 6);
    sg_step(5, 0, 1);
    func_80083C2C(&sg);
    assert(sg.unk6 == 2 && sg.unk7 == 1);
    sg_step(5, 1, 1);
    func_80083C2C(&sg);
    assert(sg.unk6 == 3 && sg.unk7 == 0 && sg.x_speed == -0x60000 && sg.terrain_box == &D_80103EEC && sg.unk4B == 1);
    sg.unk6 = 2;
    sg.unk7 = 1;
    sg.unk15 = 0;
    sg_step(5, 1, 1);
    func_80083C2C(&sg);
    assert(sg.unk6 == 3 && sg.x_speed == 0x60000);
}
static void sg_dash_run(void)
{
    sg_reset(1, 4, 3, 0);
    sg.x_speed = 0x60000;
    sg.ext.main_68.scythe->attack_box = &sg_box;
    sigma_cloak_dash_run(&sg);
    assert(sg.unk6 == 3 && sg.x_pos.i.hi == 166 && sg.unk18.i.hi == 160 && sg.ext.main_68.scythe->attack_box != NULL);
    sg.collision_flags = 1;
    sg.terrain_box = &D_80103EEC;
    sigma_cloak_dash_run(&sg);
    assert(sg.unk6 == 4 && sg.unk7C == 0xA && sg.terrain_box == NULL && sg.unk4B == -1 && sg.ext.main_68.scythe->attack_box == NULL);
}
static void sg_dash_fade_out(void)
{
    sg_reset(1, 4, 4, 0);
    sg.unk7C = 2;
    sg.hurt_box = &sg_box;
    background_objects[0].x_pos.i.hi = 0x500;
    sigma_cloak_dash_fade_out(&sg);
    assert(sg.unk7C == 1 && sg.unk6 == 4 && sg.on_screen == C_TEST_VISIBLE(sg.unk16) && sg.x_pos.i.hi == 160);
    sigma_cloak_dash_fade_out(&sg);
    assert(sg.unk6 == 5 && sg.unk7C == 0x78 && sg.on_screen == 0 && sg.hurt_box == NULL && sg.x_pos.i.hi == 0x400);
    sg.unk7C = 2;
    sg.on_screen = 1;
    sigma_cloak_dash_finish(&sg);
    assert(sg.unk7C == 1 && sg.unk6 == 5 && sg.on_screen == 0);
    sigma_cloak_dash_finish(&sg);
    assert(sg.unk5 == 2 && sg.unk6 == 0);
}
static void sg_spin_jump(void)
{
    sg_reset(1, 2, 0, 0);
    g_Player.x_pos.i.hi = 159;
    sigma_scythe_spin_jump(&sg);
    assert(sg.unk7 == 1 && sg.unk15 == 0 && sg.unk17 == 0x16);
    sg.unk7 = 0;
    g_Player.x_pos.i.hi = 160;
    sigma_scythe_spin_jump(&sg);
    assert(sg.unk7 == 1 && sg.unk15 == PLAYER_FACING_RIGHT);
    sg_step(5, 0, 1);
    sigma_scythe_spin_jump(&sg);
    assert(sg.unk6 == 0 && sg.unk7 == 1);
    sg_step(5, 0, 0);
    sigma_scythe_spin_jump(&sg);
    assert(sg.unk6 == 1 && sg.unk7 == 0 && sg.attack_box == &D_80103F08 && sg.hurt_box == &D_80103F0C && sg.unk17 == 0x17);
}
static void sg_spin_rise_far(void)
{
    sg_reset(1, 2, 1, 0);
    sg.x_pos.i.hi = 1000;
    sg.y_pos.i.hi = 336;
    sigma_scythe_spin_rise(&sg);
    assert(sg.unk6 == 1 && sg.x_speed == 0x40000 && sg.y_speed == 0 && sg.x_pos.i.hi == 1004 && sg.y_pos.i.hi == 336);
}
static void sg_spin_throw(void)
{
    sg_reset(1, 2, 2, 1);
    sg_step(5, 1, 0);
    sigma_scythe_spin_throw(&sg);
    assert(shot_objects[1].active == 0x41 && shot_objects[1].id == 0x2E && shot_objects[1].unk2 == 7 && shot_objects[1].unk7C == WEAPON_OBJECT(&sg));
    assert(sg.ext.main_68.scythe == MAIN_OBJECT(&shot_objects[1]) && sg.animation_step.fields.event == 0 && sg.unk6 == 3 && sg.unk7 == 0);
}
static void sg_spin_wait_land_recover(void)
{
    sg_reset(1, 2, 3, 0);
    sg.x_speed = 0x10000;
    sigma_scythe_spin(&sg);
    assert(sg.unk6 == 3 && sg.x_speed == 0x10000);
    shot_objects[0].active = 0;
    sigma_scythe_spin(&sg);
    assert(sg.unk6 == 4 && sg.x_speed == 0 && sg.y_speed == 0 && sg.gravity == 0x4200 && sg.unk17 == 0x18);
    sigma_scythe_spin(&sg);
    assert(sg.unk6 == 4 && sg.y_speed == -0x4200);
    sg.collision_flags = 8;
    sigma_scythe_spin(&sg);
    assert(sg.unk6 == 5 && sg.attack_box == &D_80103F00 && sg.hurt_box == &D_80103F04 && sg.unk17 == 0x19);
    sg_step(5, 0, 1);
    sigma_scythe_spin(&sg);
    assert(sg.unk5 == 2 && sg.unk6 == 5);
    sg_step(5, 0, 0);
    sg.unk7 = 1;
    sigma_scythe_spin(&sg);
    assert(sg.unk5 == 3 && sg.unk6 == 0 && sg.unk7 == 0);
}
static void sg_plant_jump(void)
{
    sg_reset(1, 3, 0, 0);
    sg.ext.main_68.next_attack = 2;
    g_Player.x_pos.i.hi = 160;
    sigma_scythe_plant_jump(&sg);
    assert(sg.unk7 == 1 && sg.unk15 == PLAYER_FACING_RIGHT && sg.ext.main_68.next_attack == 0 && sg.unk17 == 0x16);
    sg.unk7 = 0;
    g_Player.x_pos.i.hi = 159;
    sigma_scythe_plant_jump(&sg);
    assert(sg.unk7 == 1 && sg.unk15 == 0);
    sg_step(5, 0, 1);
    sigma_scythe_plant_jump(&sg);
    assert(sg.unk6 == 0 && sg.unk7 == 1);
    sg_step(5, 0, 0);
    sg.x_speed = 0x10000;
    sigma_scythe_plant_jump(&sg);
    assert(sg.unk6 == 1 && sg.unk7 == 0 && sg.x_speed == 0 && sg.y_speed == FIXED(6.5) && sg.gravity == 0x4200);
    assert(sg.attack_box == &D_80103F08 && sg.hurt_box == &D_80103F0C && sg.unk17 == 0x17);
}
static void sg_plant_apex_to_next(void)
{
    sg_reset(1, 3, 1, 0);
    sg.y_speed = 0x10000;
    sg.gravity = 0x4200;
    sigma_scythe_plant(&sg);
    assert(sg.unk6 == 1 && sg.y_speed == 0xBE00 && sg.y_pos.i.hi == 119);
    sg.y_speed = 0x1000;
    sigma_scythe_plant(&sg);
    assert(sg.unk6 == 2 && sg.y_speed == 0 && sg.gravity == 0 && sg.unk17 == 0x1A);
    sg_step(5, 0, 1);
    sigma_scythe_plant(&sg);
    assert(sg.unk6 == 2 && shot_objects[1].active == 0);
    sg_step(5, 1, 0);
    sigma_scythe_plant(&sg);
    assert(shot_objects[1].active == 0x41 && shot_objects[1].unk2 == 3 && shot_objects[1].unk7C == WEAPON_OBJECT(&sg));
    assert(sg.ext.main_68.scythe == MAIN_OBJECT(&shot_objects[1]) && sg.unk6 == 3 && sg.gravity == 0x4200 && sg.unk17 == 0x13);
    sigma_scythe_plant(&sg);
    assert(sg.unk6 == 3);
    sg.collision_flags = 8;
    sigma_scythe_plant(&sg);
    assert(sg.unk6 == 4 && sg.attack_box == &D_80103F00 && sg.hurt_box == &D_80103F04 && sg.unk17 == 0x14);
    sg_step(5, 0, 1);
    sigma_scythe_plant(&sg);
    assert(sg.unk7 == 0 && sg.unk17 == 0x14);
    sg_step(5, 0, 0);
    sigma_scythe_plant(&sg);
    assert(sg.unk7 == 1 && sg.unk17 == 0x10);
    sigma_scythe_plant(&sg);
    assert(sg.unk5 == 3 && sg.unk7 == 1);
    sg.ext.main_68.next_attack = 2;
    sigma_scythe_plant(&sg);
    assert(sg.unk5 == 4 && sg.unk6 == 0 && sg.unk7 == 0);
}
static void sg_cloak_pick_attack(void)
{
    sg_reset(1, 2, 5, 5);
    sg.ext.main_68.next_attack = 2;
    sigma_cloak_pick_attack(&sg);
    assert(sg.unk5 == 4 && sg.unk6 == 0 && sg.unk7 == 0 && sg.hurt_box == &D_80103EF4 && sg.ext.main_68.next_attack == 0);
    sigma_cloak_pick_attack(&sg);
    assert(sg.unk5 == 3 && sg.ext.main_68.next_attack == 1);
}
static void sg_darts(void)
{
    sg_reset(1, 4, 0, 0);
    sg.ext.main_68.count = 3;
    g_Player.x_pos.i.hi = 159;
    sigma_darts(&sg);
    assert(sg.unk6 == 1 && sg.unk15 == 0 && sg.ext.main_68.count == 0 && sg.unk17 == 0x1B);
    sg.unk6 = 0;
    g_Player.x_pos.i.hi = 160;
    sigma_darts(&sg);
    assert(sg.unk15 == PLAYER_FACING_RIGHT && sg.unk6 == 1);
    sg_step(5, 0, 1);
    sigma_darts(&sg);
    assert(sg.unk6 == 1 && shot_objects[1].active == 0);
    sg_step(5, 1, 1);
    sigma_darts(&sg);
    assert(sg.unk6 == 2 && sg.animation_step.fields.event == 0 && sg.ext.main_68.count == 4 && shot_objects[5].active == 0);
    assert(shot_objects[1].active == 0x41 && shot_objects[1].id == 0x2E && shot_objects[1].unk2 == 6 && shot_objects[1].timer == 0);
    assert(shot_objects[4].unk2 == 6 && shot_objects[4].timer == 3 && shot_objects[4].unk7C == WEAPON_OBJECT(&sg));
    sg_step(5, 0, 1);
    sigma_darts(&sg);
    assert(sg.unk6 == 2);
    sg_step(5, 0, 0);
    sigma_darts(&sg);
    assert(sg.unk6 == 3 && sg.unk7C == 0x5A && sg.unk17 == 0x2B);
    sg.unk7C = 2;
    sigma_darts(&sg);
    assert(sg.unk7C == 1 && sg.unk5 == 4);
    sg.unk7 = 1;
    sigma_darts(&sg);
    assert(sg.unk5 == 5 && sg.unk6 == 0 && sg.unk7 == 0);
}
static void sg_retrieve_jump(void)
{
    sg_reset(1, 5, 0, 0);
    shot_objects[0].x_pos.i.hi = 161;
    sigma_scythe_retrieve_jump(&sg);
    assert(sg.unk7 == 1 && sg.unk15 == PLAYER_FACING_RIGHT && sg.unk17 == 0x11);
    sg.unk7 = 0;
    shot_objects[0].x_pos.i.hi = 160;
    sigma_scythe_retrieve_jump(&sg);
    assert(sg.unk7 == 1 && sg.unk15 == 0);
    sg_step(5, 0, 1);
    sigma_scythe_retrieve_jump(&sg);
    assert(sg.unk6 == 0);
    sg_step(5, 0, 0);
    sigma_scythe_retrieve_jump(&sg);
    assert(sg.unk6 == 1 && sg.unk7 == 0 && sg.attack_box == &D_80103F08 && sg.hurt_box == &D_80103F0C && sg.unk17 == 0x12);
}
static void sg_retrieve_rise_to_recover(void)
{
    sg_reset(1, 5, 1, 0);
    sg.x_pos.i.hi = 1000;
    sg.y_pos.i.hi = 336;
    sigma_scythe_retrieve(&sg);
    assert(sg.unk6 == 1 && sg.x_pos.i.hi == 1004 && shot_objects[0].unk5 == 0);
    sg.x_pos.i.hi = 1228;
    sigma_scythe_retrieve(&sg);
    assert(sg.unk6 == 2 && sg.x_pos.i.hi == 1232 && shot_objects[0].unk5 == 1);
    sigma_scythe_retrieve(&sg);
    assert(sg.unk6 == 2);
    sg.ext.main_68.scythe = NULL;
    sigma_scythe_retrieve(&sg);
    assert(sg.unk6 == 3 && sg.x_speed == 0 && sg.y_speed == 0 && sg.gravity == 0x4200 && sg.unk17 == 0x18);
    sigma_scythe_retrieve(&sg);
    assert(sg.unk6 == 3);
    sg.collision_flags = 8;
    sigma_scythe_retrieve(&sg);
    assert(sg.unk6 == 4 && sg.attack_box == &D_80103F00 && sg.hurt_box == &D_80103F04 && sg.unk17 == 0x19);
    sg_step(5, 0, 1);
    sigma_scythe_retrieve(&sg);
    assert(sg.unk5 == 5);
    sg_step(5, 0, 0);
    sigma_scythe_retrieve(&sg);
    assert(sg.unk5 == 6 && sg.unk6 == 0 && sg.unk7 == 0);
}
static void sg_land_pause(void)
{
    sg_reset(1, 6, 0, 0);
    sigma_land_pause(&sg);
    assert(sg.unk6 == 1 && sg.unk7C == 0x28 && sg.unk17 == 0x15 && sg.attack_box == &D_80103F00 && sg.hurt_box == &D_80103F04);
    sg.unk7C = 2;
    sigma_land_pause(&sg);
    assert(sg.unk7C == 1 && sg.unk5 == 6);
    sigma_land_pause(&sg);
    assert(sg.unk5 == 2 && sg.unk6 == 0 && sg.unk7 == 0);
}
static void sg_laser_jump(void)
{
    sg_reset(1, 7, 0, 0);
    sigma_eye_laser(&sg);
    assert(sg.unk7 == 1 && sg.unk17 == 0x11);
    sg_step(5, 0, 0);
    sigma_eye_laser(&sg);
    assert(sg.unk7 == 2 && sg.x_speed == FIXED(2.5) && sg.y_speed == 0x60000 && sg.gravity == 0x4200);
    assert(sg.attack_box == &D_80103F08 && sg.hurt_box == &D_80103F0C && sg.unk17 == 0x12);
    sg.unk7 = 1;
    sg.unk15 = PLAYER_FACING_RIGHT;
    sg_step(5, 0, 0);
    sigma_eye_laser(&sg);
    assert(sg.unk7 == 2 && sg.x_speed == FIXED(-2.5));
    sg.y_speed = 0x4200;
    sigma_eye_laser(&sg);
    assert(sg.unk7 == 2 && sg.y_speed == 0);
    sigma_eye_laser(&sg);
    assert(sg.unk7 == 3 && sg.y_speed == 0 && sg.unk17 == 0x13);
    sigma_eye_laser(&sg);
    assert(sg.unk7 == 3);
    sg.collision_flags = 8;
    sigma_eye_laser(&sg);
    assert(sg.unk7 == 4 && sg.attack_box == &D_80103F00 && sg.hurt_box == &D_80103F04 && sg.unk17 == 0x14);
    sg_step(5, 0, 1);
    sigma_eye_laser(&sg);
    assert(sg.unk7 == 4 && sg.unk6 == 0);
    sg_step(5, 0, 0);
    sigma_eye_laser(&sg);
    assert(sg.unk6 == 1 && sg.unk7 == 0 && sg.unk17 == 0x1C);
}
static void sg_laser_wait(void)
{
    sg_reset(1, 7, 2, 0);
    g_QuadObjects[0].active = 1;
    sg.ext.main_68.effect = (struct EffectObj*)&g_QuadObjects[0];
    sigma_eye_laser(&sg);
    assert(sg.unk5 == 7 && sg.unk6 == 2);
    g_QuadObjects[0].active = 0;
    sigma_eye_laser(&sg);
    assert(sg.unk5 == 5 && sg.unk6 == 0 && sg.unk7 == 0);
}
static void sg_cloak_fight_unhit(void)
{
    sg_reset(1, 1, 0, 0);
    sg.collision_data = D_801060F0;
    sg.on_screen = 1;
    sg.hurt_box = &sg_box;
    sg.attack_box = &sg_box;
    sigma_update(&sg);
    assert(sg.state == 1 && sg.collision_data == D_80107F84 && sg.hurt_box == &sg_box && sg.attack_box == &sg_box);
}
static void sg_cloak_fight_hit(u8 weapon, u8 unk5, u8 hp)
{
    sg_reset(1, unk5, 0, 0);
    sg.hp = hp;
    sg.ext.main_68.flash_timer = 3;
    sg_hit(weapon, 0, 2);
    sigma_update(&sg);
}
static void sg_cloak_fight_stagger(void)
{
    sg_cloak_fight_hit(4, 3, 10);
    assert(sg.state == 3 && sg.unk5 == 0 && sg.hp == 8 && sg.ext.main_68.flash_timer == 2);
}
static void sg_cloak_fight_other_weapon(void)
{
    sg_cloak_fight_hit(0, 1, 10);
    assert(sg.state == 1 && sg.unk5 == 1 && sg.hp == 8 && sg.collision_data == sg_damage);
}
static void sg_cloak_fight_reveal(void)
{
    sg_cloak_fight_hit(0, 1, 2);
    assert(sg.state == 4 && sg.unk5 == 0 && sg.unk6 == 0 && sg.hp == 0);
}
static void sg_death_start_blink(void)
{
    sg_reset(2, 0, 0, 0);
    sigma_death(&sg);
    assert(sg.unk5 == 1 && sg.unk7C == 0x7F && sg.unk7E == 0x19 && sg.ext.main_68.blink_delay == 0x19 && sg.unk17 == 0x29);
    assert(g_Player.script_action == 0x15 && g_Player.script_facing == 0 && engine_obj.gameplay_locked == 1);
    sg.unk7C = 2;
    sg.unk7E = 1;
    sigma_death(&sg);
    assert(sg.unk5 == 1 && sg.unk7C == 1 && sg.unk7E == 0 && sg.unk42 == 0);
    sigma_death(&sg);
    assert(sg.unk5 == 2 && effect_objects[0].active == 1 && effect_objects[0].id == 0x1A && sg.ext.main_68.effect == &effect_objects[0]);
    assert(effect_objects[0].x_pos.i.hi == 160 && effect_objects[0].y_pos.i.hi == 120);
    assert(sg.unk42 == 0x8000 && sg.ext.main_68.blink_delay == 0x14 && sg.unk7E == 0x14);
    sg.unk5 = 1;
    sg.unk7C = 5;
    sg.unk7E = 0;
    sg.ext.main_68.blink_delay = 8;
    sigma_death(&sg);
    assert(sg.unk5 == 1 && sg.unk42 == 0 && sg.ext.main_68.blink_delay == 3 && sg.unk7E == 5);
}
static void sg_death_wait_explosion(void)
{
    sg_reset(2, 2, 0, 0);
    effect_objects[0].active = 1;
    effect_objects[0].unk7 = 1;
    sg.ext.main_68.effect = &effect_objects[0];
    sg.on_screen = 1;
    sigma_death(&sg);
    assert(sg.unk5 == 2 && sg.on_screen == 0 && sg.unk42 == 0);
    effect_objects[0].unk7 = 0;
    sigma_death(&sg);
    assert(sg.unk42 == 0x8000 && sg.unk7E == 5 && sg.on_screen == C_TEST_VISIBLE(sg.unk16));
    sg.unk7E = 2;
    sigma_death(&sg);
    assert(sg.unk42 == 0x8000 && sg.unk7E == 1);
    effect_objects[0].active = 0;
    sigma_death(&sg);
    assert(sg.unk5 == 3 && sg.unk7C == 0x78 && background_objects[0].unk28 == 0x100);
    assert(g_Player.script_action == 0x14 && g_Player.script_facing == PLAYER_FACING_RIGHT);
}
static void sg_death_explode(void)
{
    sg_reset(2, 3, 0, 0);
    sg.unk7C = 2;
    engine_obj.gameplay_locked = 1;
    cur_random = 0;
    sigma_death(&sg);
    assert(sg.unk7C == 1 && engine_obj.gameplay_locked == 0 && visual_objects[0].active == 0x21 && visual_objects[0].id == 4);
    assert(visual_objects[0].x_pos.i.hi == 0x47F && visual_objects[0].y_pos.i.hi == 0x1D2 && visual_objects[0].unk5C.value == 0);
    cur_random = 1;
    sigma_death(&sg);
    assert(sg.unk7C == 0 && sg.unk5 == 3 && visual_objects[1].active == 0);
}
static void sg_death_finish_waits(void)
{
    sg_reset(2, 4, 0, 0);
    background_objects[0].y_pos.i.hi = 1;
    sigma_death_finish(&sg);
    assert(sg.active == 0x41 && sg.unk5 == 4);
}
#include "support/tile_writes.h"
static const u8 sg_hit_table[2] = { 0, 1 };
static void sg_revealed_hit_flashing(void)
{
    sg_reset(1, 2, 0, 0);
    sg.hp = 0x20, sg.hurt_box = &sg_box, sg.collision_data = (const u16*)sg_hit_table, sg.ext.main_68.flash_timer = 3;
    weapon_objects[0].active = 1, weapon_objects[0].x_pos = sg.x_pos, weapon_objects[0].y_pos = sg.y_pos, ((struct MainObj*)&weapon_objects[0])->attack_box = &sg_box;
    engine_obj.cur_character = CHARACTER_ZERO;
    func_8008502C(&sg);
    assert(sg.hp == 0x1F && sg.ext.main_68.flash_timer == 2 && sg.collision_data == (const u16*)sg_hit_table);
    engine_obj.cur_character = CHARACTER_X;
}
static void sg_death_floor(void)
{
    sg_reset(2, 3, 0, 0);
    engine_obj.stage = 12, engine_obj.substage = 1, tile_writes_begin(), tile_writes_expect(6, 0x430, 0x1C0, 1);
    sigma_death(&sg);
    tile_writes_end();
    assert(sg.unk5 == 4);
    engine_obj.stage = engine_obj.substage = 0;
}
static void sg_death_finish_open(void)
{
    sg_reset(2, 4, 0, 0);
    background_objects[0].y_pos.i.hi = background_objects[0].unk20 = 0x100;
    background_objects[0].unk28 = 0x40, background_objects[0].unk24 = 0x10;
    g_Player.script_state = 1, SPIKE_IMMUNE_SET(g_Player, 1);
    engine_obj.stage = 12, engine_obj.substage = 1, tile_writes_begin(), tile_writes_expect(7, 0, 0, 1);
    sigma_death_finish(&sg);
    tile_writes_end();
    assert(sg.active == 0 && background_objects[0].unk2A == 0x40 && background_objects[0].unk24 == 0x290 && SPIKE_IMMUNE(g_Player) == 0 && g_Player.script_state == 0);
    engine_obj.stage = engine_obj.substage = 0;
}
static void sg_stagger_start_trail(void)
{
    sg_reset(3, 0, 0, 0);
    sg.unk42 = 0x8123;
    sg.hurt_box = &sg_box;
    sigma_cloak_stagger(&sg);
    assert(sg.unk4B == -1 && sg.unk42 == 0x123 && sg.unk5 == 1 && sg.unk7C == 0x40 && sg.unk7E == 4);
    assert(sg.hurt_box == NULL && sg.unk17 == 8 && shot_objects[0].unk17 == 9);
    sg.unk7C = 2;
    main_bss_state.frame_counter = 8;
    sigma_cloak_stagger(&sg);
    assert(sg.unk7C == 1 && sg.unk5 == 1 && visual_objects[0].active == 0x41 && visual_objects[0].id == 0x20);
    assert(visual_objects[0].unk2 == 2 && visual_objects[0].unk50 == PLAYER_OBJECT(&sg));
    main_bss_state.frame_counter = 10;
    sg.unk7E = 1;
    sg.ext.main_68.bob_step = 2;
    sigma_cloak_stagger(&sg);
    assert(sg.unk5 == 2 && sg.unk7C == 10 && visual_objects[1].active == 0);
    assert(sg.y_pos.i.hi == 122 && sg.unk7E == 4 && sg.ext.main_68.bob_step == -2);
    main_bss_state.frame_counter = 20;
    sigma_cloak_stagger(&sg);
    assert(sg.y_pos.i.hi == 120 && sg.unk7E == 3 && sg.ext.main_68.bob_step == -2 && sg.unk7C == 9);
}
static void sg_stagger_fade_finish(void)
{
    sg_reset(3, 2, 0, 0);
    sg.unk7C = 2;
    background_objects[0].x_pos.i.hi = 0x500;
    sigma_cloak_stagger(&sg);
    assert(sg.unk7C == 1 && sg.unk5 == 2 && sg.on_screen == C_TEST_VISIBLE(sg.unk16));
    sigma_cloak_stagger(&sg);
    assert(sg.unk5 == 3 && sg.unk7C == 0x78 && sg.on_screen == 0);
    sg.unk7C = 2;
    sg.unk6 = 4;
    sg.unk7 = 5;
    sigma_cloak_stagger(&sg);
    assert(sg.unk7C == 1 && sg.state == 3);
    sigma_cloak_stagger(&sg);
    assert(sg.state == 1 && sg.unk5 == 2 && sg.unk6 == 0 && sg.unk7 == 0 && sg.x_pos.i.hi == 0x490);
}
static void sg_reveal_fall(void)
{
    sg_reset(4, 1, 0, 0);
    main_bss_state.frame_counter = 5;
    sigma_reveal(&sg);
    assert(sg.unk5 == 1 && visual_objects[0].active == 0x41 && visual_objects[0].id == 0x20 && visual_objects[0].unk2 == 2);
    main_bss_state.frame_counter = 1;
    sg.collision_flags = 8;
    sigma_reveal(&sg);
    assert(sg.unk5 == 2 && sg.unk7C == 0x78 && visual_objects[1].active == 0);
}
static void sg_reveal_burn_wait(void)
{
    sg_reset(4, 2, 0, 0);
    sg.unk7C = 2;
    func_80085A44(&sg);
    assert(sg.unk7C == 1 && sg.unk5 == 2 && sg.on_screen == C_TEST_VISIBLE(sg.unk16));
}
static void sg_reveal_wait_dialogue(void)
{
    sg_reset(4, 3, 0, 0);
    sg.ext.main_68.count = 1;
    sigma_reveal(&sg);
    assert(sg.unk5 == 3);
    sg.ext.main_68.count = 0;
    sigma_reveal(&sg);
    assert(sg.unk5 == 4 && sg.unk17 == 0xF);
    sg_step(5, 0, 1);
    sigma_reveal(&sg);
    assert(sg.unk5 == 4 && sg.unk6 == 0);
    sg.unk6 = 1;
    abc_object.unkC = 1;
    sigma_reveal(&sg);
    assert(sg.unk5 == 4 && sg.unk6 == 1);
    abc_object.unkC = 0;
    sigma_reveal(&sg);
    assert(sg.unk5 == 5 && sg.unk6 == 0 && sg.unk7C == 1);
}
static void sg_reveal_fill_finish(void)
{
    sg_reset(4, 5, 0, 0);
    sg.hp = 0x2E;
    sg.unk7C = 1;
    sigma_reveal(&sg);
    assert(sg.hp == 0x2F && sg.unk7C == 2);
    sigma_reveal(&sg);
    assert(sg.hp == 0x30 && sg.unk7C == 1 && sg.unk5 == 5);
    sigma_reveal(&sg);
    assert(sg.unk5 == 6 && sg.unk7C == 0x5A && sg.hp == 0x30);
    sg.unk7C = 2;
    sg.unk6 = 3;
    sg.ext.main_68.flash_timer = 9;
    g_Player.script_state = 1;
    sigma_reveal(&sg);
    assert(sg.unk7C == 1 && sg.state == 4 && shot_objects[0].state == 0);
    sigma_reveal(&sg);
    assert(sg.state == 1 && sg.unk2 == 1 && sg.unk5 == 2 && sg.unk6 == 0 && sg.unk7 == 0 && sg.ext.main_68.flash_timer == 0);
    assert(sg.collision_data == D_80108004 && sg.attack_box == &D_80103F00 && sg.hurt_box == &D_80103F04);
    assert(shot_objects[0].state == 1 && g_Player.script_state == 0);
}
static void (*const sg_cases[])(void) = {
    sg_intro_wait_player,
    sg_intro_init,
    sg_intro_fill_health,
    sg_intro_wait,
    sg_intro_finish,
    sg_teleport_appear_left,
    sg_teleport_fire,
    sg_teleport_wait_shots,
    sg_teleport_fade_out,
    sg_teleport_finish,
    sg_dash_appear,
    sg_dash_fade_in,
    sg_dash_start,
    sg_dash_run,
    sg_dash_fade_out,
    sg_spin_jump,
    sg_spin_rise_far,
    sg_spin_throw,
    sg_spin_wait_land_recover,
    sg_plant_jump,
    sg_plant_apex_to_next,
    sg_cloak_pick_attack,
    sg_darts,
    sg_retrieve_jump,
    sg_retrieve_rise_to_recover,
    sg_land_pause,
    sg_laser_jump,
    sg_laser_wait,
    sg_cloak_fight_unhit,
    sg_cloak_fight_stagger,
    sg_cloak_fight_other_weapon,
    sg_cloak_fight_reveal,
    sg_death_start_blink,
    sg_death_wait_explosion,
    sg_death_explode,
    sg_death_finish_waits,
    sg_revealed_hit_flashing,
    sg_death_floor,
    sg_death_finish_open,
    sg_stagger_start_trail,
    sg_stagger_fade_finish,
    sg_reveal_fall,
    sg_reveal_burn_wait,
    sg_reveal_wait_dialogue,
    sg_reveal_fill_finish,
};
static u32 sg_run(u32 row)
{
    sg_cases[row]();
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "sigma_cloak_flash_hits", sigma_cloak_flash_hits_cases, sigma_cloak_flash_hits_cases_expected, COUNT(sigma_cloak_flash_hits_cases), 0 },
    { "sigma_eye_laser_quad_pool", NULL, sigma_eye_laser_quad_pool_cases_expected, COUNT(sigma_eye_laser_quad_pool_cases_expected), laser_case },
    { "sigma_pose_visual_pool", sigma_pose_visual_pool_cases, sigma_pose_visual_pool_cases_expected, COUNT(sigma_pose_visual_pool_cases), 0 },
    { "sigma_revealed_hit_visual_pools", NULL, sigma_revealed_hit_visual_pools_cases_expected, COUNT(sigma_revealed_hit_visual_pools_cases_expected), revealed_case },
    { "sigma_pose", 0, 0, 1, test_sigma_pose },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "shipped_boss_dialogue_characters_and_player_side", NULL, NULL, 48, dialogue },
    { "sigma_reveal_faces_player_and_preserves_scythe_owner", NULL, NULL, 6, reveal },
    { "cloaked_Sigma_own_appear_fade_windup_near_far_full_visual_or_shot_pool", NULL, NULL, 4, attack },
    { "own_Sigma_reveal_cloak_and_scythe_full_partial_pools_exact_RNG", NULL, NULL, 24, reveal_sigma_reveal_pool_capacity },
    { "uncloaked_Sigma_real_rise_40_wait_25_throw_animation_ticks_full_shots", NULL, NULL, 1, full },
    { "sigma_state_steps", NULL, NULL, COUNT(sg_cases), sg_run },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(sigma_cloak_flash_hits_cases) + COUNT(sigma_eye_laser_quad_pool_cases_expected) + COUNT(sigma_pose_visual_pool_cases) + COUNT(sigma_revealed_hit_visual_pools_cases_expected) + 1 + COUNT(pool_full_cases) + 48 + 6 + 4 + 24 + 1 + COUNT(sg_cases);
#else
const struct CTestGroup c_test_groups[] = {};
const u32 c_test_group_count = 0;
const u32 c_test_count = 0;
#endif
