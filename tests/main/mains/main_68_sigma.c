#include "test_runtime.h"
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
    g_Player.spike_immune = 1;
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
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(weapons_before) / 4; i++)
        assert(((u32*)weapon_objects)[i] == ((u32*)weapons_before)[i]);
    for (i = 0; i < sizeof(visuals_before) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)visuals_before)[i]);
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
        return weapon_objects[0].unk80.word;
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
    obj.unk15 = right ? 0x40 : 0;
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
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)g_QuadObjects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(D_8013E198[2] == -1);
    return (u8)obj.unk6 | ((u32)obj.unk17 << 8) | ((u32)(u8)g_QuadObjects[31].unk2 << 16) | ((u32)obj.animation_step.fields.event << 24);
}
#define CASE(m)                                          \
    static u32 sigma_eye_laser_quad_pool_laser_##m(void) \
    {                                                    \
        return laser_case(m);                            \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
#define ENTRY(m) sigma_eye_laser_quad_pool_laser_##m,
static const CTestCase sigma_eye_laser_quad_pool_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) };
static const u32 sigma_eye_laser_quad_pool_cases_expected[] = { 0x1C02u, 0x1C02u, 0x11C02u, 0x31C02u, 0x21C02u, 0x1D03u };
#undef CASE
#undef ENTRY

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
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(visuals_before) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)visuals_before)[i]);
    return observation == 0 ? (u8)obj.unk7 | ((u32)(u16)obj.unk7C << 16) : obj.animation_step.packed;
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
    g_Player.spike_immune = dying ? 0 : 1;
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
        weapons_expected[0].unk80.word = 100 | (200 << 16);
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
            visual->unk40 = 0;
            visual->unk42 = 0x7802;
            visual->unk16 = 0;
            visual->unk3C = (u8*)sprites + 12;
            visual->x_pos.i.hi = 100;
            visual->y_pos.i.hi = 200;
            visual->unk15 = 0x40;
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
        player_expected.spike_immune = 1;
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
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_expected)[i]);
    for (i = 0; i < sizeof(weapons_expected) / 4; i++)
        assert(((u32*)weapon_objects)[i] == ((u32*)weapons_expected)[i]);
    for (i = 0; i < sizeof(visuals_expected) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)visuals_expected)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    for (i = 0; i < sizeof(quads_before) / 4; i++)
        assert(((u32*)g_QuadObjects)[i] == ((u32*)quads_before)[i]);
    assert(box.unk0 == -2 && box.unk1 == -2 && box.unk2 == 4 && box.unk3 == 4);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    assert(sprites[0] == 8 && sprites[1] == 12 && sprites[2] == 0x11223344 && sprites[3] == 0x55667788);
    i = (u8)obj.hp | ((u32)obj.ext.main_68.flash_timer << 8) | ((u32)(u8)obj.state << 16) | ((u32)(u8)visual_objects[31].id << 24);
    return i;
}
#define CASE(m)                                                   \
    static u32 sigma_revealed_hit_visual_pools_revealed_##m(void) \
    {                                                             \
        return revealed_case(m);                                  \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
CASE(7)
CASE(8)
CASE(9)
CASE(10)
CASE(11)
CASE(12)
CASE(13)
CASE(14)
CASE(15)
CASE(16)
CASE(17)
CASE(18)
CASE(19)
#define ENTRY(m) sigma_revealed_hit_visual_pools_revealed_##m,
static const CTestCase sigma_revealed_hit_visual_pools_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) ENTRY(8) ENTRY(9) ENTRY(10) ENTRY(11) ENTRY(12) ENTRY(13) ENTRY(14) ENTRY(15) ENTRY(16) ENTRY(17) ENTRY(18) ENTRY(19) };
static const u32 sigma_revealed_hit_visual_pools_cases_expected[] = { 0x27014060u, 0x3014060u, 0x20014060u, 0x20014060u, 0x27014060u, 0x3014060u, 0x20014060u, 0x27010163u, 0x27014063u, 0x27010064u, 0x27010064u, 0x27020000u, 0x27020000u, 0x27010164u, 0x27010064u, 0x27014063u, 0x27010164u, 0x27010162u, 0x27014061u, 0x27014061u };
#undef CASE
#undef ENTRY

static const u32 sigma_pose_expected[] = { 0xFFFFFFFFu, 0xFFFFFFFFu, 0u, 0u, 0u };
static u32 test_sigma_pose(u32 row)
{
    u32 observed_values[5];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    obj.unk7 = -1;
    pool_0_full = 0;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_0_full ? 1 : 0;
    }
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
    pf_script(0x14, 0x40);
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
const struct CTestGroup c_test_groups[] = {
    { "sigma_cloak_flash_hits", sigma_cloak_flash_hits_cases, sigma_cloak_flash_hits_cases_expected, COUNT(sigma_cloak_flash_hits_cases), 0 },
    { "sigma_eye_laser_quad_pool", sigma_eye_laser_quad_pool_cases, sigma_eye_laser_quad_pool_cases_expected, COUNT(sigma_eye_laser_quad_pool_cases), 0 },
    { "sigma_pose_visual_pool", sigma_pose_visual_pool_cases, sigma_pose_visual_pool_cases_expected, COUNT(sigma_pose_visual_pool_cases), 0 },
    { "sigma_revealed_hit_visual_pools", sigma_revealed_hit_visual_pools_cases, sigma_revealed_hit_visual_pools_cases_expected, COUNT(sigma_revealed_hit_visual_pools_cases), 0 },
    { "sigma_pose", 0, 0, 1, test_sigma_pose },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(sigma_cloak_flash_hits_cases) + COUNT(sigma_eye_laser_quad_pool_cases) + COUNT(sigma_pose_visual_pool_cases) + COUNT(sigma_revealed_hit_visual_pools_cases) + 1 + COUNT(pool_full_cases);
