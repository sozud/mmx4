#include "test_runtime.h"
#include "support/platform_fixture.h"
#include "main/collision_bounds.h"
#include "main/shots/shot_12_ice_core_shot.h"
#include "main/55C4.h"
void ice_core_shard_hold(struct ShotObj*);
extern union AnimationStep* D_800FC2B4[34];
extern u8 ice_core_shard_hit_box[4], ice_core_shard_terrain_box[4];
static struct Unk_unk68 contact_box = { 0, 0, 8, 8 };
static struct WeaponObj weapons_expected[16];
static struct VisualObj visuals_before[32];
static struct MiscObj misc_before[64];
static u32 shard(u32 row)
{
    struct ShotObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 type = row % 10, mode = row / 10 % 3, layer = row / 30, i;
    u16 flags[2] = { 0x83FF, 0xA5A5 };
    s32 x = 160 - 9, y = 120 - 16;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    {
        u32 v;
        for (v = 0; v < 32; v++)
            visual_objects[v].active = 1;
    }
    c_test_copy_words((u32*)visuals_before, (u32*)visual_objects, sizeof(visuals_before) / 4);
    D_8013E198[1] = -1;
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < 64; i++)
        misc_objects[i].active = 1;
    c_test_copy_words((u32*)misc_before, (u32*)misc_objects, sizeof(misc_before) / 4);
    obj.active = 0x41;
    obj.id = 12;
    obj.unk2 = type;
    obj.state = 4;
    obj.on_screen = 1;
    obj.bg_offset = layer;
    obj.unk15 = 0;
    obj.unk5C = 1;
    obj.unk60 = 3;
    obj.unk50.data = obj.unk54 = ice_core_shard_hit_box;
    obj.unk68 = (struct Unk_unk68*)ice_core_shard_terrain_box;
    obj.unk58.animation_steps = D_80105FF0;
    obj.unk7C = (struct WeaponObj*)&flags[0];
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.animation_table = (u32**)D_800FC2B4;
    set_animation(&obj, 29);
    assert(obj.animation_step.packed == C_TEST_STEP(0x62010001));
    expected = obj;
    expected.animation_cursor++;
    expected.animation_step.packed = C_TEST_STEP(0x63010009);
    g_Player.bg_offset = layer;
    g_Player.active = 0x41;
    g_Player.hp = 30;
    SPIKE_IMMUNE_SET(g_Player, 1);
    g_Player.unk15 = obj.unk15;
    g_Player.unk54 = (const u32*)&contact_box;
    g_Player.x_pos.val = (mode == 2 ? x : x + 100) * 65536;
    g_Player.y_pos.val = y * 65536;
    player_expected = g_Player;
    if (mode == 1) {
        weapon_objects[0].bg_offset = layer;
        weapon_objects[0].active = 1;
        weapon_objects[0].id = 28;
        weapon_objects[0].unk50 = &contact_box;
        weapon_objects[0].x_pos.val = x * 65536;
        weapon_objects[0].y_pos.val = y * 65536;
        player_expected.update_delay_request = 1;
        expected.unk5C = 0;
        expected.unk42 = 0x8000;
    }
    c_test_copy_words((u32*)weapons_expected, (u32*)weapon_objects, sizeof(weapons_expected) / 4);
    if (mode == 1)
        TEST_SET_HALVES(weapons_expected[0].unk80, x + 4, y + 4);
    if (mode)
        expected.state = 6;
    D_8013E198[5] = -1;
    cur_random = 0x1234;
    ice_core_shard_hold(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(flags[0] == (0x83FF ^ (mode ? 1 << type : 0)) && flags[1] == 0xA5A5 && ice_core_shard_data.masks[type] == (1 << type) && cur_random == 0x1234);
    assert(c_test_word_difference((u32*)weapon_objects, (u32*)weapons_expected, sizeof(weapons_expected) / 4) == 0 && c_test_word_difference((u32*)misc_objects, (u32*)misc_before, sizeof(misc_before) / 4) == 0);
    assert(c_test_word_difference((u32*)visual_objects, (u32*)visuals_before, sizeof(visuals_before) / 4) == 0);
    return 1;
}

void ice_core_spray_fly(struct ShotObj*);
extern u8 ice_core_spray_hit_box[4];
static struct Unk_unk68 player_box = { 0, 0, 12, 24 };
static u32 spray(u32 row)
{
    struct ShotObj obj, expected;
    struct MainObj owner, owner_before;
    struct PlayerObj player_expected;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 dying = row % 2, hit = row / 2 % 2, face = row / 4 % 2, layer = row / 8;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    owner.active = 0x41;
    owner.id = 18;
    owner.state = 1;
    if (dying)
        *(s16*)&owner.state = 2;
    owner_before = owner;
    obj.active = 0x41;
    obj.id = 12;
    obj.unk2 = 0;
    obj.state = 1;
    obj.on_screen = 0;
    obj.bg_offset = layer;
    obj.unk15 = face ? PLAYER_FACING_RIGHT : 0;
    obj.unk50.data = obj.unk54 = ice_core_spray_hit_box;
    obj.unk58.animation_steps = D_80105FF0;
    obj.unk5C = 6;
    obj.unk60 = 3;
    obj.unk7C = (struct WeaponObj*)&owner.state;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_vel.val = face ? 0x60000 : -0x60000;
    obj.y_vel.val = 0x18000;
    expected = obj;
    expected.x_pos.val += obj.x_vel.val;
    expected.y_pos.val -= obj.y_vel.val;
    expected.on_screen = 1;
    if (dying || hit)
        expected.state = 2;
    g_Player.active = 0x41;
    g_Player.hp = 30;
    g_Player.unk54 = (const u32*)&player_box;
    g_Player.unk15 = obj.unk15;
    g_Player.x_pos = expected.x_pos;
    g_Player.y_pos = expected.y_pos;
    if (!hit)
        g_Player.x_pos.i.hi += 100;
    player_expected = g_Player;
    if (hit) {
        player_expected.hp = 27 | 0x80;
        player_expected.hurt_type = 1;
    }
    ice_core_spray_fly(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_before, sizeof(owner));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(player_box.unk0 == 0 && player_box.unk1 == 0 && player_box.unk2 == 12 && player_box.unk3 == 24);
    return 1;
}

#include "support/state_cases.h"
static u16 icf;
#define ss state_room.shot
#define ICE(st, flags, setup) (state_reset(0, 0, 0), icf = flags, D_8013E198[5] = -1, memset(&g_Player, 0, sizeof(g_Player)), g_Player.x_pos.i.hi = 0x400, g_Player.y_pos.i.hi = 0x80, ss.active = 0x41, ss.state = st, ss.unk2 = 1, ss.unk7C = (struct WeaponObj*)&icf, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60, ss.y_vel.val = 0x10000, ss.unk2C = 0x2800, ss.unk50.data = ice_core_shard_hit_box, ss.unk70 = 0xA0, setup, ice_core_shot_update(&ss), state_extra = ss.unk17 | (u32)ss.unk70 << 8 | (u32)icf << 16)
static void ic_core_gone(void)
{
    ICE(4, 0, 0);
}
static void ic_released(void) { ICE(4, 0x8000, 0); }
static void ic_falling(void) { ICE(5, 0x8000, 0); }
static void ic_landed(void) { ICE(5, 0x8000, ss.unk70 = 8); }
static void ic_shot(void) { ICE(5, 0x8000, (so.hp = 1, state_hit(&so, 0, 0, 1))); }
static struct Unk_unk68 ice_player_box = { 0, 0, 12, 24 };
static void ic_touch(void) { ICE(5, 0x8000, (g_Player.x_pos.i.hi = 0x80, g_Player.y_pos.i.hi = 0x60, g_Player.unk54 = (const u32*)&ice_player_box)); }
static void ic_spray_gone(void) { ICE(1, 1, ss.x_pos.i.hi = 0x1000); }

static void (*const ic_cases[])(void) = {
    ic_core_gone,
    ic_released,
    ic_falling,
    ic_landed,
    ic_shot,
    ic_touch,
    ic_spray_gone,
};
static const u32 ic_expected[] = {
    0x6u,
    0x141u,
    0x800000u,
    0x600000u,
    0u,
    0x10000u,
    0x280000u,
    0x40000u,
    0u,
    0x41000000u,
    0x5u,
    0xFF000141u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0x280000u,
    0x50000u,
    0x8000001Eu,
    0u,
    0x5u,
    0x141u,
    0x800000u,
    0x5F0000u,
    0u,
    0xD800u,
    0x280000u,
    0x50000u,
    0x80000000u,
    0u,
    0x6u,
    0x141u,
    0x800000u,
    0x5F0000u,
    0u,
    0xD800u,
    0x280000u,
    0x50000u,
    0x80000000u,
    0x41000000u,
    0x6u,
    0x141u,
    0x800000u,
    0x5F0000u,
    0u,
    0xD800u,
    0x280000u,
    0x58000u,
    0x80000000u,
    0x41002100u,
    0x6u,
    0x141u,
    0x800000u,
    0x5F0000u,
    0u,
    0xD800u,
    0x280000u,
    0x50000u,
    0x80000000u,
    0x41000000u,
    0x2u,
    0x141u,
    0x10000000u,
    0x5F0000u,
    0u,
    0x10000u,
    0x280000u,
    0x50000u,
    0x1A000u,
    0u,
};
static u32 test_ic(u32 row)
{
    return object_run(ic_cases[row], row, &ic_expected[row * 10]);
}

void func_8009B85C(struct ShotObj* arg0);
static u32 spray_init(u32 row)
{
    struct ShotObj obj;
    s32 dx = (s8)ice_core_shard_offsets[2], dy = (s8)ice_core_shard_offsets[3];
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 12;
    obj.unk2 = 1;
    obj.unk15 = row ? PLAYER_FACING_RIGHT : 0;
    obj.animation_table = (u32**)D_800FC2B4;
    obj.x_pos.i.hi = 160;
    obj.y_pos.i.hi = 120;
    func_8009B85C(&obj);
    assert(obj.state == 1 && obj.on_screen == 1 && obj.unk5C == 6 && obj.unk60 == 3);
    assert(obj.y_pos.i.hi == 120 + dy && obj.x_pos.i.hi == (row ? 160 - dx : 160 + dx));
    assert(row ? obj.x_vel.val < 0 : obj.x_vel.val > 0);
    assert(obj.x_vel.val % 6 == 0 && obj.y_vel.val % 6 == 0 && obj.y_vel.val != 0);
    return obj.x_vel.val > 0;
}

const struct CTestGroup c_test_groups[] = {
    { "ice_core_shot_steps", 0, 0, COUNT(ic_cases), test_ic },
    { "all_ten_shipped_shards_real_facing_and_layers_saber_or_immune_contact", NULL, NULL, 60, shard },
    { "real_spray_parent_state_pointer_contact_facing_and_backgrounds", NULL, NULL, 24, spray },
    { "spray_init", 0, 0, 2, spray_init },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 60 + 24 + 2 + COUNT(ic_cases);
