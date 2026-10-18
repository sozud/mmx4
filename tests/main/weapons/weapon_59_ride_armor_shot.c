#include "test_runtime.h"
#include "main/weapons/weapon_59_ride_armor_shot.h"

#include "support/pool_full.h"
#include "main/player_animations.h"
#include "main/player_animations_2.h"
#include "main/player.h"
static u32 pool_full_ride_armor_shot_visual(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    func_80098EA8(WEAPON_OBJECT(&pf_self));
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_ride_armor_shot_visual,
};

static const u32 pool_full_cases_expected[] = { 0x50000u };

void ride_armor_shot_update(struct WeaponObj*);
void enemy_ride_armor_shot_update(struct ShotObj*);
void func_80098EA8(struct WeaponObj*);
void func_80098DA0(struct WeaponObj*);
extern union AnimationStep* D_800F965C[38];
extern void* unused_ride_armor_animations[33];
extern u8 ride_armor_shot_hit_box[4];

static struct WeaponObj shot, expected, weapons_before[16];
static struct VisualObj visuals_expected[32];
static struct PlayerObj player_expected;
static struct EngineObj engine_before;
static struct MainBssState main_before;
static struct BackgroundObj backgrounds_before[3];
static struct RideArmorObj ride_before;
static const s16 cameras[3][2] = { { 0, 0 }, { 1024, 512 }, { -320, -240 } };
static const s16 edges[17][2] = {
    { 160, 120 },
    { -32, 120 },
    { -33, 120 },
    { 351, 120 },
    { 352, 120 },
    { -16, 120 },
    { -17, 120 },
    { 335, 120 },
    { 336, 120 },
    { 160, -32 },
    { 160, -33 },
    { 160, 271 },
    { 160, 272 },
    { 160, -16 },
    { 160, -17 },
    { 160, 255 },
    { 160, 256 },
};
static const u32 animation_words[2][2][4] = {
    { { 0x3D010002, 0x3E010002, 0x3F010002, 0x40FD0002 },
        { 0x41010002, 0x42010002, 0x43010002, 0x44FD0002 } },
    { { 0x44010002, 0x46010002, 0x45010002, 0x47FD0002 },
        { 0x48010002, 0x49010002, 0x4A010002, 0x4BFD0002 } },
};

static void prepare(u32 variant)
{
    u32 i, layer = variant / 4, facing = (variant / 2) % 2;
    c_test_zero_words((u32*)&shot, sizeof(shot) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&qux_object, sizeof(qux_object) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)&main_bss_state, sizeof(main_bss_state) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < 3; i++) {
        background_objects[i].x_pos.val = cameras[i][0] * 65536;
        background_objects[i].y_pos.val = cameras[i][1] * 65536;
    }
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 0x27;
        visual_objects[i].unk40 = 0x2345;
        visual_objects[i].unk42 = 0x6789;
    }
    shot.active = 0x41;
    shot.id = 47;
    shot.unk2 = variant % 2;
    shot.bg_offset = layer;
    shot.unk15 = facing ? 0x40 : 0;
    shot.x_pos.val = (cameras[layer][0] + 160) * 65536 + 0x1234;
    shot.y_pos.val = (cameras[layer][1] + 120) * 65536 + 0x5678;
    shot.animation_table = (u32**)unused_ride_armor_animations;
    shot.unk50 = shot.unk54 = ride_armor_shot_hit_box;
    shot.unk68 = (struct Unk_unk68*)ride_armor_shot_hit_box;
    shot.unk65 = 0x37;
    shot.unk40 = 0x1234;
    shot.unk42 = 0x9234;
    shot.unk16 = 5;
    shot.unk3C = D_800F965C;
    shot.owner = &g_Player;
    g_Player.active = 0x41;
    g_Player.state = PLAYER_STATE_NORMAL;
    g_Player.x_pos.val = (cameras[layer][0] + 1000) * 65536;
    g_Player.y_pos.val = (cameras[layer][1] + 120) * 65536;
    g_Player.spike_immune = 1;
    g_Player.hp = 24;
    g_Player.air_action = 3;
    controller_input.held = 0x1234;
    controller_input.previous = 0x5678;
    controller_input.pressed = 0x840;
    need_palette_load = 0x20;
    cur_random = 0x1234;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
}

static void capture(void)
{
    expected = shot;
    player_expected = g_Player;
    engine_before = engine_obj;
    main_before = main_bss_state;
    ride_before = qux_object;
    c_test_copy_words((u32*)backgrounds_before, (const u32*)background_objects, sizeof(backgrounds_before) / 4);
    c_test_copy_words((u32*)weapons_before, (const u32*)weapon_objects, sizeof(weapons_before) / 4);
    c_test_copy_words((u32*)visuals_expected, (const u32*)visual_objects, sizeof(visuals_expected) / 4);
}

static void check(void)
{
    u32 i, j;
    c_test_same_words(&shot, &expected, sizeof(expected));
    c_test_same_words(&g_Player, &player_expected, sizeof(player_expected));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_before));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_before));
    c_test_same_words(&qux_object, &ride_before, sizeof(ride_before));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(c_test_word_difference((const u32*)weapon_objects, (const u32*)weapons_before, sizeof(weapons_before) / 4) == 0);
    assert(c_test_word_difference((const u32*)visual_objects, (const u32*)visuals_expected, sizeof(visuals_expected) / 4) == 0);
    assert(cur_random == 0x1234 && need_palette_load == 0x20);
    assert(controller_input.held == 0x1234 && controller_input.previous == 0x5678 && controller_input.pressed == 0x840);
    assert(ride_armor_shot_hit_box[0] == 0xFC && ride_armor_shot_hit_box[1] == 0xFD
        && ride_armor_shot_hit_box[2] == 6 && ride_armor_shot_hit_box[3] == 5);
    for (i = 0; i < 2; i++)
        for (j = 0; j < 4; j++) {
            assert(D_800F965C[31 + i][j].packed == animation_words[1][i][j]);
            assert(((const u32*)unused_ride_armor_animations[31 + i])[j] == animation_words[0][i][j]);
        }
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
}

static void expect_init(void)
{
    s32 subtype = expected.unk2, facing = expected.unk15 != 0;
    expected.state = expected.on_screen = 1;
    expected.unk16 = 3;
    expected.unk68 = NULL;
    expected.unk54 = NULL;
    expected.unk50 = ride_armor_shot_hit_box;
    expected.x_pos.i.hi += (facing ? 1 : -1) * (subtype ? 44 : 43);
    expected.y_pos.i.hi += subtype ? 25 : 0;
    expected.x_vel.val = (facing ? 1 : -1) * (subtype ? 0x5A828 : 0x80000);
    expected.y_vel.val = subtype ? -0x5A828 : 0;
    expected.unk5C = 1;
    expected.unk60 = 3;
    expected.unk17 = 31 + subtype;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = expected.animation_table[31 + subtype];
    expected.animation_step.packed = animation_words[expected.id == 59][subtype][0];
}

static void init_enemy(void)
{
    capture();
    expect_init();
    enemy_ride_armor_shot_update(SHOT_OBJECT(&shot));
}

static void expect_motion(void)
{
    if (--expected.animation_step.fields.duration == 0) {
        expected.animation_cursor++;
        expected.animation_step.packed = animation_words[expected.id == 59][(u8)expected.unk2][1];
    }
    expected.x_pos.val += expected.x_vel.val;
    expected.y_pos.val -= expected.y_vel.val;
    expected.unk65 = 0;
}

static void expect_release(void)
{
    u32 i;
    for (i = 0; i < 8; i++)
        ((u8*)&expected)[i] = 0;
}

static u32 test_init(u32 row)
{
    prepare(row % 12);
    if (row >= 12) {
        shot.id = 59;
        shot.animation_table = (u32**)D_800F965C;
    }
    capture();
    expect_init();
    if (row < 12)
        enemy_ride_armor_shot_update(SHOT_OBJECT(&shot));
    else
        ride_armor_shot_update(&shot);
    check();
    return 1;
}

static u32 test_viewport(u32 row)
{
    u32 variant = row % 12, edge = row, duration = 1;
    s32 x = edges[edge][0], y = edges[edge][1], layer = variant / 4;
    prepare(variant);
    init_enemy();
    shot.x_pos.val = (cameras[layer][0] + x) * 65536 + 0x1234 - expected.x_vel.val;
    shot.y_pos.val = (cameras[layer][1] + y) * 65536 + 0x5678 + expected.y_vel.val;
    shot.animation_step.fields.duration = duration;
    capture();
    expect_motion();
    if (x < -32 || x >= 352 || y < -32 || y >= 272)
        expect_release();
    else
        expected.on_screen = x >= -16 && x < 336 && y >= -16 && y < 256;
    enemy_ride_armor_shot_update(SHOT_OBJECT(&shot));
    check();
    return 1;
}

static u32 test_contact(u32 row)
{
    u32 variant = row % 12, mode = row % 6, character = row / 12;
    prepare(variant);
    init_enemy();
    g_Player.spike_immune = mode == 1;
    g_Player.hp = mode == 2 ? (s8)0x98 : 24;
    g_Player.hurt_phase = mode == 3;
    g_Player.invincibility_timer = mode == 5;
    g_Player.unk2 = character == 2;
    g_Player.armor_parts = character == 1 ? 2 : 0;
    g_Player.unk15 = shot.unk15;
    g_Player.unk54 = mode == 4 ? NULL : character == 2 ? &D_8011A230[1]
                                                       : &D_801194F0[1];
    g_Player.x_pos.val = expected.x_pos.val + expected.x_vel.val;
    g_Player.y_pos.val = expected.y_pos.val - expected.y_vel.val;
    g_Player.hurt_type = 3;
    g_Player.stun_timer = 7;
    g_Player.hit_facing = 0x40;
    g_Player.weapon_energy[0] = 45;
    capture();
    expect_motion();
    if (mode < 4)
        expect_release();
    if (mode == 0) {
        player_expected.hurt_type = character == 1 ? 4 : 1;
        player_expected.stun_timer = 0;
        player_expected.hp = character == 1 ? (s8)0x96 : (s8)0x95;
        player_expected.hit_facing = 0;
        if (character == 1)
            player_expected.weapon_energy[0] = 48;
    }
    enemy_ride_armor_shot_update(SHOT_OBJECT(&shot));
    check();
    return 1;
}

static u32 test_smoke(u32 row)
{
    u32 variant = row % 12, plan = row / 12;
    s32 slot = plan == 0 ? 0 : plan == 1 ? 31
                                         : -1;
    struct VisualObj* visual;
    prepare(variant);
    init_enemy();
    if (slot >= 0)
        visual_objects[slot].active = 0;
    capture();
    if (slot >= 0) {
        visual = &visuals_expected[slot];
        visual->active = expected.active;
        visual->id = 0x16;
        visual->unk2 = 0;
        visual->x_pos.u.hi = expected.x_pos.u.hi;
        visual->y_pos.u.hi = expected.y_pos.u.hi;
        visual->animation_table = expected.animation_table;
        visual->unk40 = expected.unk40;
        visual->unk3C = expected.unk3C;
        visual->unk42 = expected.unk42;
        visual->unk16 = expected.unk16;
        visual->unk50 = PLAYER_OBJECT(&shot);
        visual->unk15 = expected.unk15;
    }
    func_80098EA8(&shot);
    check();
    return 1;
}

static u32 test_despawn(u32 row)
{
    static const u8 counts[] = { 0, 1, 3 };
    prepare(row % 12);
    shot.id = 59;
    shot.animation_table = (u32**)D_800F965C;
    capture();
    expect_init();
    ride_armor_shot_update(&shot);
    shot.state = 2;
    g_Player.air_action = counts[row / 12];
    capture();
    expect_release();
    if (player_expected.air_action)
        player_expected.air_action--;
    ride_armor_shot_update(&shot);
    check();
    return 1;
}

static struct MainObj target_pool_before[48];
static u32 test_target_selection(u32 row)
{
    static const s8 targets[12] = { -1, -1, -1, 0, 47, 0, 0, 47, 47, 47, 47, 0 };
    u32 mode = row % 12, i;
    s32 sx = (row / 12) & 1 ? -1 : 1, sy = row / 24 ? -1 : 1;
    prepare(0);
    shot.id = 60;
    shot.state = 1;
    shot.ext.target = mode == 0 || mode == 2 || mode == 7 || mode == 9 ? &main_objects[47] : NULL;
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    for (i = 0; i < 48; i++) {
        main_objects[i].id = 71;
        main_objects[i].x_pos.val = shot.x_pos.val + sx * 100 * 65536;
        main_objects[i].y_pos.val = shot.y_pos.val;
    }
    if (mode != 0) {
        main_objects[0].active = 1;
        main_objects[0].on_screen = mode != 1;
        main_objects[0].unk7A = mode == 2 || mode == 8;
    }
    if (mode >= 4 && mode != 9) {
        main_objects[47].active = main_objects[47].on_screen = 1;
        main_objects[47].x_pos.val = shot.x_pos.val;
        main_objects[47].y_pos.val = shot.y_pos.val + sy * 10 * 65536;
    }
    if (mode == 5) {
        main_objects[0].x_pos.val = shot.x_pos.val + sx * 10 * 65536;
        main_objects[47].y_pos.val = shot.y_pos.val + sy * 100 * 65536;
    }
    if (mode == 6 || mode == 7)
        main_objects[0].x_pos.val = shot.x_pos.val + sx * 10 * 65536;
    if (mode == 9)
        main_objects[47].x_pos.val = shot.x_pos.val + sx * 5 * 65536;
    if (mode >= 10) {
        for (i = 0; i < 48; i++) {
            main_objects[i].active = main_objects[i].on_screen = 1;
            main_objects[i].unk7A = 0;
            main_objects[i].x_pos.val = shot.x_pos.val + sx * (mode == 10 ? 48 - i : 10) * 65536;
            main_objects[i].y_pos.val = shot.y_pos.val;
        }
    }
    capture();
    c_test_copy_words((u32*)target_pool_before, (const u32*)main_objects, sizeof(target_pool_before) / 4);
    expected.ext.target = targets[mode] < 0 ? NULL : &main_objects[(u8)targets[mode]];
    func_80098DA0(&shot);
    check();
    assert(c_test_word_difference((const u32*)main_objects, (const u32*)target_pool_before, sizeof(target_pool_before) / 4) == 0);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "ride_armor_shot_init", 0, 0, 24, test_init },
    { "enemy_shot_viewport", 0, 0, 17, test_viewport },
    { "enemy_shot_contact", 0, 0, 36, test_contact },
    { "ride_armor_shot_smoke", 0, 0, 36, test_smoke },
    { "ride_armor_shot_despawn", 0, 0, 24, test_despawn },
    { "ride_armor_missile_target", 0, 0, 12, test_target_selection },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(pool_full_cases) + 24 + 17 + 36 + 36 + 24 + 12;
