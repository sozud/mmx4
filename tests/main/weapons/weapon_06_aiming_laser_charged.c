#include "test_runtime.h"
#include "main/quads/quad_09_aiming_laser_beam.h"
#include "main/visuals/visual_18_aiming_laser_scope.h"
#include "main/weapons/weapon_01_lightning_web.h"
#include "main/weapons/weapon_02_frost_tower.h"
#include "main/weapons/weapon_06_aiming_laser_charged.h"
#include "main/weapons/weapon_07_double_cyclone.h"
#include "main/player_weapon.h"
#include "main/sprite_animations.h"
void func_800963E8(struct WeaponObj*, struct PlayerObj*);
extern struct Unk_unk68 aiming_laser_charged_box[];
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static u32 lock_case(u32 mode, u32 observation)
{
    struct WeaponObj obj, expected_weapon, before_weapons[16];
    struct PlayerObj player;
    struct MainObj target, before_target, occupied[3];
    struct MainObj* before_slots[3];
    struct Unk_unk68 box = { 0, 0, 4, 4 };
    s32 result;
    u32 i, j;
    memset(&obj, 0, sizeof(obj));
    memset(&player, 0, sizeof(player));
    memset(&target, 0, sizeof(target));
    memset(occupied, 0, sizeof(occupied));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.bg_offset = -1;
    D_8013E198[0] = -1;
    memset(weapon_objects, 0, sizeof(weapon_objects));
    for (i = 0; i < COUNT(weapon_objects); i++)
        weapon_objects[i].active = 1;
    if (mode == 6)
        weapon_objects[5].active = 0;
    memcpy(before_weapons, weapon_objects, sizeof(before_weapons));
    obj.active = 1;
    obj.id = 6;
    obj.bg_offset = -1;
    obj.on_screen = 1;
    obj.x_pos.val = target.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = target.y_pos.val = 100 * 65536 + 0x2468;
    obj.unk50 = &box;
    target.active = 1;
    target.hp = mode == 3 ? 0 : 16;
    target.unk7A = mode == 2;
    target.hurt_box = &box;
    player.special_shot_count = 3;
    if (mode < 2)
        player.weapon_06_slots[mode + 1] = &target;
    if (mode == 4 || mode == 6) {
        player.weapon_06_slots[0] = &occupied[0];
        player.weapon_06_slots[1] = &occupied[1];
        if (mode == 4)
            player.weapon_06_slots[2] = &occupied[2];
    }
    for (i = 0; i < 3; i++)
        before_slots[i] = player.weapon_06_slots[i];
    before_target = target;
    result = aiming_laser_try_lock_on(&obj, &player, &target);
    assert(D_8013E198[0] == -1);

    assert(box.unk0 == 0 && box.unk1 == 0 && box.unk2 == 4 && box.unk3 == 4);
    assert(obj.active == 1 && obj.id == 6 && obj.bg_offset == -1);
    assert(obj.x_pos.val == 100 * 65536 + 0x1234 && obj.y_pos.val == 100 * 65536 + 0x2468);
    assert(obj.unk50 == (mode >= 5 ? NULL : &box));
    for (i = 0; i < sizeof(target); i++)
        assert(((u8*)&target)[i] == ((u8*)&before_target)[i]);
    for (i = 0; i < 3; i++)
        assert(player.weapon_06_slots[i] == (mode == 6 && i == 2 ? &target : before_slots[i]));
    assert(g_Player.bg_offset == -1);
    for (i = 0; i < COUNT(weapon_objects); i++) {
        expected_weapon = before_weapons[i];
        if (mode == 6 && i == 5) {
            expected_weapon.active = 1;
            expected_weapon.id = 6;
            expected_weapon.unk2 = 2;
            expected_weapon.bg_offset = -1;
            expected_weapon.owner = PLAYER_OBJECT(&target);
        }
        for (j = 0; j < sizeof(expected_weapon); j++)
            assert(((u8*)&weapon_objects[i])[j] == ((u8*)&expected_weapon)[j]);
    }
    if (observation == 0)
        return (u32)result;
    if (observation == 1)
        return (u8)player.special_shot_count | ((u32)(u8)obj.on_screen << 8);
    return (u8)weapon_objects[5].active | ((u32)(u8)weapon_objects[5].id << 8) | ((u32)(u8)weapon_objects[5].unk2 << 16) | ((u32)(u8)weapon_objects[5].bg_offset << 24);
}
#define OBSERVE(mode, field)                                 \
    static u32 aiming_lock_slots_lock_##mode##_##field(void) \
    {                                                        \
        return lock_case(mode, field);                       \
    }
#define MODE(mode) OBSERVE(mode, 0) OBSERVE(mode, 1) OBSERVE(mode, 2)
MODE(0)
MODE(1)
MODE(2)
MODE(3)
MODE(4)
MODE(5)
MODE(6)
#define ENTRY(mode, field) aiming_lock_slots_lock_##mode##_##field,
#define ENTRIES(mode) ENTRY(mode, 0) ENTRY(mode, 1) ENTRY(mode, 2)
static const CTestCase aiming_lock_slots_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) ENTRIES(3) ENTRIES(4) ENTRIES(5) ENTRIES(6) };
static const u32 aiming_lock_slots_cases_expected[] = { 0x0u, 0x103u, 0x1u, 0x0u, 0x103u, 0x1u, 0x0u, 0x103u, 0x1u, 0x0u, 0x103u, 0x1u, 0x0u, 0x103u, 0x1u, 0x1u, 0x103u, 0x1u, 0x1u, 0x104u, 0xFF020601u };
#undef OBSERVE
#undef MODE
#undef ENTRY
#undef ENTRIES

static u32 aiming_marker_dispatch_keyframe = 0x2A010102u;
static s32 gfx_archive[16], sprite_archive[32];
static struct Unk_unk68 aiming_marker_dispatch_sentinel = { 0, 0, 4, 4 };

static u32 marker_case(u32 mode, u32 observation)
{
    struct WeaponObj obj;
    struct MainObj owner, before_owner;
    struct PlayerObj expected_player;
    struct QuadObj before_quads[32], expected_quad;
    u32 i, j, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(g_QuadObjects, 0, sizeof(g_QuadObjects));
    for (i = 0; i < COUNT(g_QuadObjects); i++)
        g_QuadObjects[i].active = 1;
    g_QuadObjects[7].active = 0;
    memcpy(before_quads, g_QuadObjects, sizeof(before_quads));
    for (i = 0; i < COUNT(gfx_archive); i++)
        gfx_archive[i] = 0x11223344;
    for (i = 0; i < COUNT(sprite_archive); i++)
        sprite_archive[i] = 0x55667788;
    gfx_archive[7] = 32;
    sprite_archive[15] = 64;
    TEST_PLAYER_GFX = (u8*)gfx_archive;
    TEST_SPRITE_FRAMES = (u8*)sprite_archive;
    owner.active = 1;
    owner.hp = 16;
    owner.x_pos.val = 300 * 65536 + 0x1234;
    owner.y_pos.val = 400 * 65536 + 0x2468;
    before_owner = owner;
    g_Player.weapon = 6;
    g_Player.hp = 16;
    g_Player.bg_offset = -1;
    g_Player.special_shot_count = 6;
    g_Player.weapon_06_slots[1] = &owner;
    g_Player.shot_fired = mode == 1;
    g_Player.shot_type = 6;
    expected_player = g_Player;
    if (mode == 3) {
        expected_player.special_shot_count = 5;
        expected_player.weapon_06_slots[1] = NULL;
    }
    obj.active = 1;
    obj.id = 6;
    obj.state = mode;
    obj.unk2 = 1;
    obj.on_screen = 1;
    obj.bg_offset = -1;
    obj.owner = PLAYER_OBJECT(&owner);
    obj.unk50 = &aiming_marker_dispatch_sentinel;
    obj.unk64 = 9;
    obj.ext.weapon_6.direction = 8;
    obj.ext.weapon_6.lifetime = mode == 2 ? 0 : 7;
    obj.ext.weapon_6.timer = 6;
    obj.animation_cursor = &aiming_marker_dispatch_keyframe;
    obj.animation_step.packed = aiming_marker_dispatch_keyframe;
    func_800961B0(&obj);
    assert(obj.owner == PLAYER_OBJECT(&owner) && obj.bg_offset == -1);
    assert(obj.x_pos.val == owner.x_pos.val && obj.y_pos.val == owner.y_pos.val);
    assert(obj.unk50 == (mode == 0 ? (void*)&aiming_marker_dispatch_sentinel : mode == 1 ? (void*)aiming_laser_marker_box
                                                                                         : NULL));
    if (mode == 0) {
        assert(obj.unk38 == (u8*)&gfx_archive[8] && obj.unk3C == (u8*)&sprite_archive[16]);
        assert(obj.animation_table == D_8011C0E4 && obj.animation_cursor == D_8011C0E4[2]);
        assert(obj.unk17 == 2 && obj.previous_animation_index == 0xFF);
    } else {
        assert(obj.unk38 == NULL && obj.unk3C == NULL && obj.animation_cursor == &aiming_marker_dispatch_keyframe);
    }
    for (i = 0; i < sizeof(owner); i++)
        assert(((u8*)&owner)[i] == ((u8*)&before_owner)[i]);
    for (i = 0; i < sizeof(g_Player); i++)
        assert(((u8*)&g_Player)[i] == ((u8*)&expected_player)[i]);
    for (i = 0; i < COUNT(g_QuadObjects); i++) {
        expected_quad = before_quads[i];
        if (mode == 1 && i == 7) {
            expected_quad.active = 1;
            expected_quad.id = 9;
            expected_quad.unk2 = 1;
            expected_quad.unk5C = PLAYER_OBJECT(&owner);
        }
        for (j = 0; j < sizeof(expected_quad); j++)
            assert(((u8*)&g_QuadObjects[i])[j] == ((u8*)&expected_quad)[j]);
    }
    for (i = 0; i < COUNT(gfx_archive); i++)
        assert(gfx_archive[i] == (i == 7 ? 32 : 0x11223344));
    for (i = 0; i < COUNT(sprite_archive); i++)
        assert(sprite_archive[i] == (i == 15 ? 64 : 0x55667788));
    assert(aiming_marker_dispatch_keyframe == 0x2A010102u && aiming_marker_dispatch_sentinel.unk2 == 4 && aiming_marker_dispatch_sentinel.unk3 == 4);
    if (observation == 0)
        return (u8)obj.active | ((u32)(u8)obj.id << 8) | ((u32)(u8)obj.state << 16) | ((u32)(u8)obj.on_screen << 24);
    if (observation == 1)
        return obj.ext.weapon_6.lifetime | ((u32)obj.ext.weapon_6.timer << 8) | ((u32)(u8)obj.unk64 << 16);
    if (observation == 2)
        return obj.animation_step.packed;
    actual = (u8)g_Player.special_shot_count | ((u32)(u8)g_QuadObjects[7].active << 8) | ((u32)(u8)g_QuadObjects[7].id << 16) | ((u32)(u8)g_QuadObjects[7].unk2 << 24);
    return actual;
}
#define OBSERVE(mode, field)                                        \
    static u32 aiming_marker_dispatch_marker_##mode##_##field(void) \
    {                                                               \
        return marker_case(mode, field);                            \
    }
#define MODE(mode) OBSERVE(mode, 0) OBSERVE(mode, 1) OBSERVE(mode, 2) OBSERVE(mode, 3)
MODE(0)
MODE(1)
MODE(2)
MODE(3)
#define ENTRY(mode, field) aiming_marker_dispatch_marker_##mode##_##field,
#define ENTRIES(mode) ENTRY(mode, 0) ENTRY(mode, 1) ENTRY(mode, 2) ENTRY(mode, 3)
static const CTestCase aiming_marker_dispatch_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) ENTRIES(3) };
static const u32 aiming_marker_dispatch_cases_expected[] = { 0x10601u, 0x90607u, 0x8010001u, 0x6u, 0x20601u, 0x1063Cu, 0x2A010101u, 0x1090106u, 0x30601u, 0x90600u, 0x2A010101u, 0x6u, 0x0u, 0x90607u, 0x2A010102u, 0x5u };
#undef OBSERVE
#undef MODE
#undef ENTRY
#undef ENTRIES

static u32 aiming_reticle_hiding_keyframe = 0x2A010102u;
static struct Unk_unk68 box = { -20, -20, 40, 40 };

static u32 reticle_case(u32 mode, u32 observation)
{
    struct WeaponObj obj;
    struct PlayerObj player, before_player;
    u32 i;
    s8 threshold = player_weapon_energy.charge.initial_thresholds[0];
    assert(threshold > 0);
    memset(&obj, 0, sizeof(obj));
    memset(&player, 0, sizeof(player));
    memset(main_objects, 0, sizeof(main_objects));
    obj.active = 1;
    obj.id = 6;
    obj.unk2 = 3;
    obj.state = 1;
    obj.on_screen = 1;
    obj.bg_offset = -1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x2468;
    obj.ext.weapon_6.direction = 8;
    obj.unk50 = &box;
    obj.animation_cursor = &aiming_reticle_hiding_keyframe;
    obj.animation_step.packed = aiming_reticle_hiding_keyframe;
    player.unk15 = 0x40;
    player.x_pos.val = 100 * 65536 + 0x5678;
    player.y_pos.val = 100 * 65536 + 0x6789;
    player.weapon_energy[6] = mode == 0 ? threshold - 1 : threshold;
    player.special_shot_count = mode == 2 ? 3 : 0;
    player.hurt_phase = mode == 3 ? 1 : 0;
    before_player = player;
    func_800963E8(&obj, &player);
    assert(obj.active == 1 && obj.id == 6 && obj.state == 1 && obj.unk2 == 3);
    assert(obj.bg_offset == -1 && obj.animation_cursor == &aiming_reticle_hiding_keyframe);
    assert(obj.unk50 == (mode == 1 ? NULL : &box));
    assert(aiming_reticle_hiding_keyframe == 0x2A010102u);
    assert(box.unk0 == -20 && box.unk1 == -20 && box.unk2 == 40 && box.unk3 == 40);
    for (i = 0; i < sizeof(player); i++)
        assert(((u8*)&player)[i] == ((u8*)&before_player)[i]);
    assert(((unsigned long)main_objects & 3) == 0 && sizeof(main_objects) % 4 == 0);
    for (i = 0; i < sizeof(main_objects) / 4; i++)
        assert(((u32*)main_objects)[i] == 0);
    if (mode != 1) {
        assert(obj.x_pos.val == 100 * 65536 + 0x1234 && obj.y_pos.val == 100 * 65536 + 0x2468);
        assert(obj.on_screen == 0 && obj.animation_step.packed == aiming_reticle_hiding_keyframe);
    }
    if (observation == 0)
        return (u8)obj.on_screen | ((u32)obj.ext.weapon_6.direction << 8) | ((u32)obj.ext.weapon_6.adjusted_direction << 16) | ((u32)(u8)obj.unk15 << 24);
    if (observation == 1)
        return (u32)obj.x_pos.val;
    if (observation == 2)
        return (u32)obj.y_pos.val;
    if (observation == 3)
        return (u32)obj.x_vel.val;
    if (observation == 4)
        return (u32)obj.y_vel.val;
    return obj.animation_step.packed;
}
#define OBSERVE(mode, field)                                        \
    static u32 aiming_reticle_hiding_reticle_##mode##_##field(void) \
    {                                                               \
        return reticle_case(mode, field);                           \
    }
#define MODE(mode) OBSERVE(mode, 0) OBSERVE(mode, 1) OBSERVE(mode, 2) \
    OBSERVE(mode, 3) OBSERVE(mode, 4) OBSERVE(mode, 5)
MODE(0)
MODE(1)
MODE(2)
MODE(3)
#define ENTRY(mode, field) aiming_reticle_hiding_reticle_##mode##_##field,
#define ENTRIES(mode) ENTRY(mode, 0) ENTRY(mode, 1) ENTRY(mode, 2) \
    ENTRY(mode, 3) ENTRY(mode, 4) ENTRY(mode, 5)
static const CTestCase aiming_reticle_hiding_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) ENTRIES(3) };
static const u32 aiming_reticle_hiding_cases_expected[] = { 0x800u, 0x641234u, 0x642468u, 0x0u, 0x0u, 0x2A010102u, 0x40080801u, 0xC45678u, 0x646789u, 0x10000u, 0x0u, 0x2A010101u, 0x800u, 0x641234u, 0x642468u, 0x0u, 0x0u, 0x2A010102u, 0x800u, 0x641234u, 0x642468u, 0x0u, 0x0u, 0x2A010102u };
#undef OBSERVE
#undef MODE
#undef ENTRY
#undef ENTRIES

static u8 charged_aiming_thresholds_sentinel = 0x5A;

static u32 threshold_case(u32 mode, u32 observation)
{
    struct WeaponObj obj;
    struct PlayerObj before_player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 1;
    obj.id = 0xF;
    obj.state = 1;
    obj.unk5 = mode;
    obj.unk64 = 9;
    obj.unk50 = &charged_aiming_thresholds_sentinel;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x2468;
    obj.ext.weapon_6.direction = 8;
    obj.ext.weapon_6.lifetime = mode == 0 ? 211 : mode == 1 ? 31
                                                            : 60;
    obj.ext.weapon_6.timer = 6;
    g_Player.unk15 = 0x40;
    g_Player.animation_step.fields.frame_index = 4;
    g_Player.x_pos.val = 300 * 65536 + 0x5678;
    g_Player.y_pos.val = 400 * 65536 + 0x6789;
    before_player = g_Player;
    func_80096B54(&obj);
    assert(obj.active == 1 && obj.id == 0xF && obj.state == 1);
    assert(obj.unk50 == (mode == 0 ? (void*)aiming_laser_charged_box : mode == 1 ? NULL
                                                                                 : &charged_aiming_thresholds_sentinel));
    assert(charged_aiming_thresholds_sentinel == 0x5A);
    for (i = 0; i < sizeof(g_Player); i++)
        assert(((u8*)&g_Player)[i] == ((u8*)&before_player)[i]);
    if (observation == 0)
        return (u8)obj.state | ((u32)(u8)obj.unk5 << 8) | ((u32)(u8)obj.unk64 << 16) | ((u32)(u8)obj.unk15 << 24);
    if (observation == 1)
        return obj.ext.weapon_6.direction | ((u32)obj.ext.weapon_6.adjusted_direction << 8) | ((u32)obj.ext.weapon_6.lifetime << 16) | ((u32)obj.ext.weapon_6.timer << 24);
    if (observation == 2)
        return (u32)obj.x_pos.val;
    if (observation == 3)
        return (u32)obj.y_pos.val;
    if (observation == 4)
        return (u32)obj.x_vel.val;
    return (u32)obj.y_vel.val;
}
#define OBSERVE(mode, field)                                              \
    static u32 charged_aiming_thresholds_threshold_##mode##_##field(void) \
    {                                                                     \
        return threshold_case(mode, field);                               \
    }
#define MODE(mode) OBSERVE(mode, 0) OBSERVE(mode, 1) OBSERVE(mode, 2) \
    OBSERVE(mode, 3) OBSERVE(mode, 4) OBSERVE(mode, 5)
MODE(0)
MODE(1)
MODE(2)
#define ENTRY(mode, field) charged_aiming_thresholds_threshold_##mode##_##field,
#define ENTRIES(mode) ENTRY(mode, 0) ENTRY(mode, 1) ENTRY(mode, 2) \
    ENTRY(mode, 3) ENTRY(mode, 4) ENTRY(mode, 5)
static const CTestCase charged_aiming_thresholds_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) };
static const u32 charged_aiming_thresholds_cases_expected[] = { 0x40010101u, 0x6D20808u, 0x1B01234u, 0x1862468u, 0x10000u, 0x0u, 0x40090201u, 0x61E0808u, 0x1B01234u, 0x1862468u, 0x10000u, 0x0u, 0x40090201u, 0x63B0808u, 0x1B01234u, 0x1862468u, 0x10000u, 0x0u };
#undef OBSERVE
#undef MODE
#undef ENTRY
#undef ENTRIES

static const u32 aiming_laser_charged_aim_expected[] = { 8u, 0u, 0x68u, 0x680000u, 0u, 0u };
static u32 test_aiming_laser_charged_aim(u32 row)
{
    u32 observed_values[6];
    struct WeaponObj obj;
    struct PlayerObj argument_obj_1;
    memset(&obj, 0, sizeof(obj));
    memset(&argument_obj_1, 0, sizeof(argument_obj_1));
    obj.ext.weapon_6.direction = 24;
    obj.ext.weapon_6.adjusted_direction = 0;
    aiming_laser_charged_aim(&obj, &argument_obj_1);
    observed_values[0] = (u32)obj.ext.weapon_6.adjusted_direction;
    observed_values[1] = (u32)obj.unk15;
    observed_values[2] = (u32)obj.x_pos.i.hi;
    observed_values[3] = (u32)obj.x_pos.val;
    observed_values[4] = (u32)obj.y_pos.i.hi;
    observed_values[5] = (u32)obj.y_pos.val;
    return c_test_observe(0, row, observed_values, aiming_laser_charged_aim_expected, 6);
}

static const u32 aiming_laser_charged_init_expected[] = { 1u, 0u, 0u, 0x18u, 8u, 0xF0u, 6u, 1u, 0u };
static u32 test_aiming_laser_charged_init(u32 row)
{
    u32 observed_values[9];
    struct WeaponObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&g_QuadObjects, 0, sizeof(g_QuadObjects));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            g_QuadObjects[slot].active = pool_0_full ? 1 : 0;
    }
    aiming_laser_charged_init(&obj);
    observed_values[0] = (u32)g_QuadObjects[0].active;
    observed_values[1] = (u32)g_QuadObjects[0].id;
    observed_values[2] = (u32)g_QuadObjects[0].unk2;
    observed_values[3] = (u32)obj.ext.weapon_6.adjusted_direction;
    observed_values[4] = (u32)obj.ext.weapon_6.direction;
    observed_values[5] = (u32)obj.ext.weapon_6.lifetime;
    observed_values[6] = (u32)obj.ext.weapon_6.timer;
    observed_values[7] = (u32)obj.state;
    observed_values[8] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, aiming_laser_charged_init_expected, 9);
}

struct aiming_laser_marker_wait_fire_case {
    u32 shot_type, pool_0_full;
    u32 expected[7];
};
static const struct aiming_laser_marker_wait_fire_case aiming_laser_marker_wait_fire_cases[] = {
    { 0, 0, { 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 6, 255, { 1u, 0u, 0u, 0x3Cu, 6u, 1u, 1u } },
};
static u32 test_aiming_laser_marker_wait_fire(u32 row)
{
    const struct aiming_laser_marker_wait_fire_case* c = &aiming_laser_marker_wait_fire_cases[row];
    u32 observed_values[7];
    struct WeaponObj obj;
    struct PlayerObj argument_obj_1;
    struct PlayerObj argument_obj_2;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&argument_obj_1, 0, sizeof(argument_obj_1));
    memset(&argument_obj_2, 0, sizeof(argument_obj_2));
    memset(&g_QuadObjects, 0, sizeof(g_QuadObjects));
    memset(&background_objects, 0, sizeof(background_objects));
    argument_obj_1.shot_fired = -1;
    argument_obj_1.shot_type = c->shot_type;
    pool_0_full = c->pool_0_full;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            g_QuadObjects[slot].active = pool_0_full ? 1 : 0;
    }
    aiming_laser_marker_wait_fire(&obj, &argument_obj_1, &argument_obj_2);
    observed_values[0] = (u32)g_QuadObjects[0].active;
    observed_values[1] = (u32)g_QuadObjects[0].id;
    observed_values[2] = (u32)g_QuadObjects[0].unk2;
    observed_values[3] = (u32)obj.ext.weapon_6.lifetime;
    observed_values[4] = (u32)obj.ext.weapon_6.timer;
    observed_values[5] = (u32)obj.state;
    observed_values[6] = (u32)obj.unk64;
    return c_test_observe(0, row, observed_values, c->expected, 7);
}

static const u32 aiming_laser_try_lock_on_expected[] = { 0u, 0u };
static u32 test_aiming_laser_try_lock_on(u32 row)
{
    u32 observed_values[2];
    struct WeaponObj obj;
    struct PlayerObj argument_obj_1;
    struct MainObj argument_obj_2;
    s32 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&argument_obj_1, 0, sizeof(argument_obj_1));
    memset(&argument_obj_2, 0, sizeof(argument_obj_2));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    argument_obj_2.active = -5;
    argument_obj_2.unk7A = -1;
    return_value = aiming_laser_try_lock_on(&obj, &argument_obj_1, &argument_obj_2);
    observed_values[0] = (u32)return_value;
    observed_values[1] = (u32)argument_obj_1.special_shot_count;
    return c_test_observe(0, row, observed_values, aiming_laser_try_lock_on_expected, 2);
}

struct func_80096B54_case {
    u32 lifetime, unk5, direction, held, timer;
    u32 expected[6];
};
static const struct func_80096B54_case func_80096B54_cases[] = {
    { 0, 0, 0, 0, 0, { 0u, 0u, 0u, 3u, 0u, 0u } },
    { 255, -1, 24, 0, 0, { 0x18u, 0xFEu, 0u, 0u, 0xFFFFFFFFu, 0u } },
    { 31, 1, 24, 0, 0, { 0x18u, 0x1Eu, 0u, 0u, 2u, 0u } },
    { 255, 1, 0, 2056, 0, { 1u, 0xFEu, 6u, 0u, 1u, 1u } },
    { 255, 1, 16, 0, 255, { 0x10u, 0xFEu, 0xFEu, 0u, 1u, 0u } },
    { 255, 1, 24, 3084, 0, { 0x18u, 0xFEu, 6u, 0u, 1u, 1u } },
};
static u32 test_func_80096B54(u32 row)
{
    const struct func_80096B54_case* c = &func_80096B54_cases[row];
    u32 observed_values[6];
    struct WeaponObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.ext.weapon_6.lifetime = c->lifetime;
    obj.unk5 = c->unk5;
    obj.ext.weapon_6.direction = c->direction;
    g_Player.input.buttons.held = c->held;
    obj.ext.weapon_6.timer = c->timer;
    func_80096B54(&obj);
    observed_values[0] = (u32)obj.ext.weapon_6.direction;
    observed_values[1] = (u32)obj.ext.weapon_6.lifetime;
    observed_values[2] = (u32)obj.ext.weapon_6.timer;
    observed_values[3] = (u32)obj.state;
    observed_values[4] = (u32)obj.unk5;
    observed_values[5] = (u32)obj.unk64;
    return c_test_observe(0, row, observed_values, c->expected, 6);
}

#include "support/charged_dispatch.h"
CHARGED_BASIC(2)
CHARGED_CASE(2, 4)
CHARGED_CASE(2, 5)
static const CTestCase aiming_laser_charged_dispatch_cases[] = { CHARGED_BASIC_ENTRIES(2) CHARGED_ENTRIES(2, 4) CHARGED_ENTRIES(2, 5) };
static const u32 aiming_laser_charged_dispatch_cases_expected[] = { 0x1000391u, 0x605u, 0x0u, 0x505u, 0x0u, 0x505u, 0x0u, 0x505u, 0x0u, 0x505u, 0x0u, 0x505u };

#include "support/aiming_cancellation.h"
AIMING_CANCEL_MODE(0, 0)
AIMING_CANCEL_SIX(1)
static const CTestCase aiming_laser_cancellation_cases[] = { AIMING_CANCEL_ENTRIES(0, 0) AIMING_CANCEL_SIX_ENTRIES(1) };

static const u32 aiming_laser_cancellation_cases_expected[] = { 0x0u, 0x641234u, 0xC82468u, 0x6u, 0x0u, 0x12C3456u, 0x1904567u, 0x5u, 0x0u, 0x12C3456u, 0x1904567u, 0x5u, 0x0u, 0x12C3456u, 0x1904567u, 0x5u, 0x0u, 0x12C3456u, 0x1904567u, 0x5u, 0x0u, 0x12C3456u, 0x1904567u, 0x5u, 0x0u, 0x12C3456u, 0x1904567u, 0x5u };
const struct CTestGroup c_test_groups[] = {
    { "aiming_lock_slots", aiming_lock_slots_cases, aiming_lock_slots_cases_expected, COUNT(aiming_lock_slots_cases), 0 },
    { "aiming_marker_dispatch", aiming_marker_dispatch_cases, aiming_marker_dispatch_cases_expected, COUNT(aiming_marker_dispatch_cases), 0 },
    { "aiming_reticle_hiding", aiming_reticle_hiding_cases, aiming_reticle_hiding_cases_expected, COUNT(aiming_reticle_hiding_cases), 0 },
    { "charged_aiming_thresholds", charged_aiming_thresholds_cases, charged_aiming_thresholds_cases_expected, COUNT(charged_aiming_thresholds_cases), 0 },
    { "aiming_laser_charged_aim", 0, 0, 1, test_aiming_laser_charged_aim },
    { "aiming_laser_charged_init", 0, 0, 1, test_aiming_laser_charged_init },
    { "aiming_laser_marker_wait_fire", 0, 0, 2, test_aiming_laser_marker_wait_fire },
    { "aiming_laser_try_lock_on", 0, 0, 1, test_aiming_laser_try_lock_on },
    { "func_80096B54", 0, 0, 6, test_func_80096B54 },
    { "aiming_laser_charged_dispatch", aiming_laser_charged_dispatch_cases, aiming_laser_charged_dispatch_cases_expected, COUNT(aiming_laser_charged_dispatch_cases), 0 },
    { "aiming_laser_cancellation", aiming_laser_cancellation_cases, aiming_laser_cancellation_cases_expected, COUNT(aiming_laser_cancellation_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(aiming_lock_slots_cases) + COUNT(aiming_marker_dispatch_cases) + COUNT(aiming_reticle_hiding_cases) + COUNT(charged_aiming_thresholds_cases) + 1 + 1 + 2 + 1 + 6 + COUNT(aiming_laser_charged_dispatch_cases) + COUNT(aiming_laser_cancellation_cases);
