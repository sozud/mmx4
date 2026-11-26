#include "test_runtime.h"
#include "support/platform_fixture.h"
#include "main/mains/main_18_ice_core.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "main/weapons/weapon_00_lemon.h"
#include "main/weapons/weapon_01_lightning_web.h"
extern union AnimationStep* D_800FC2B4[34];
void ice_core_check_rebuild(struct MainObj*);
void ice_core_pick_attack(struct MainObj*);
void ice_core_shed_ice(struct MainObj*);

static struct HitInput {
    s8 weapon_id;
    u8 character, invincible, state, start_flags;
};
enum { HIT_BONUS_2,
    HIT_BONUS_5,
    HIT_BONUS_10,
    HIT_NO_BONUS,
    INVINCIBLE_TICK,
    INVINCIBLE_END,
    NO_HIT,
    DEFEATED };
static const struct HitInput inputs[] = {
    { 0, 0, 0, 1, 0 },
    { 9, 1, 0, 1, 0x80 },
    { 18, 0, 0, 1, 0x80 },
    { 27, 1, 0, 1, 0x80 },
    { -1, 0, 2, 1, 0x80 },
    { -1, 0, 1, 1, 0x80 },
    { -1, 0, 0, 1, 0x80 },
    { -1, 0, 0, 2, 0x80 },
};
static u8 damage[0x100];
static struct Unk_unk68 weapon_box = { -60, -60, 0x7F, 0x7F };
static struct Unk_unk68 hurt_box = { -8, -8, 16, 16 };
static struct MainObj core, expected;
static s8 banks[6];

static void zero(void* target, u32 size)
{
    u32 i;
    for (i = 0; i < size / 4; i++)
        ((u32*)target)[i] = 0;
}

static u32 ice_core_hit_run(u32 mode)
{
    const struct HitInput* input = &inputs[mode];
    u32 i, difference = 0, hit = input->weapon_id >= 0;
    for (i = 0; i < 6; i++)
        banks[i] = D_8013E198[i];
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    zero(weapon_objects, sizeof(weapon_objects));
    zero(visual_objects, sizeof(visual_objects));
    for (i = 0; i < 0x20; i++)
        visual_objects[i].active = 1;
    memset(&g_Player, 0, sizeof(g_Player));
    SPIKE_IMMUNE_SET(g_Player, 1);
    engine_obj.cur_character = input->character;
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    memset(damage, 0, sizeof(damage));
    for (i = 0; i < 0x80; i++)
        damage[i * 2 + 1] = 3;
    memset(&core, 0, sizeof(core));
    core.active = 0x41;
    core.id = 0x12;
    core.state = input->state;
    core.unk5 = 1;
    core.hp = 40;
    core.unk42 = 0x8456;
    core.invincibility_timer = input->invincible;
    core.x_pos.val = 0x00901111;
    core.y_pos.val = 0x00702222;
    core.collision_data = damage;
    core.hurt_box = &hurt_box;
    core.ext.main_18.saved_unk5 = 1;
    core.ext.main_18.state.runtime.unk80 = input->start_flags;
    core.ext.main_18.state.runtime.unk81 = 1;
    core.ext.main_18.state.runtime.unk83 = 7;
    if (hit) {
        weapon_objects[0].active = 1;
        weapon_objects[0].id = input->weapon_id;
        weapon_objects[0].x_pos = core.x_pos;
        weapon_objects[0].y_pos = core.y_pos;
        ((struct MainObj*)&weapon_objects[0])->attack_box = &weapon_box;
    }
    expected = core;
    func_80050874(&core);

    expected.unk18 = expected.x_pos;
    expected.unk1C = expected.y_pos;
    expected.on_screen = 1;
    if (input->state < 2) {
        if (input->invincible) {
            expected.invincibility_timer = input->invincible - 1;
            if (input->invincible == 1)
                expected.unk42 &= 0x7FFF;
        } else {
            expected.ext.main_18.saved_unk5 = 1;
            expected.unk42 &= 0x7FFF;
            if (hit) {
                expected.hp = 37;
                expected.invincibility_timer = input->character ? 1 : 6;
                expected.ext.main_18.state.runtime.unk87 = 1;
                expected.unk42 |= 0x8000;
                if (!(input->start_flags & 0xC0))
                    expected.ext.main_18.state.runtime.unk80 = (input->start_flags | 0x40) + 1;
                if (input->weapon_id == 0)
                    expected.ext.main_18.state.runtime.unk83 += 2;
                if (input->weapon_id == 9)
                    expected.ext.main_18.state.runtime.unk83 += 5;
                if (input->weapon_id == 18)
                    expected.ext.main_18.state.runtime.unk83 += 10;
            }
        }
    }
    for (i = 0; i < sizeof(core) / 4; i++)
        difference |= ((u32*)&core)[i] ^ ((u32*)&expected)[i];
    for (i = 1; i < COUNT(weapon_objects); i++)
        difference |= weapon_objects[i].active;
    for (i = 0; i < 0x20; i++)
        difference |= visual_objects[i].active ^ 1;
    assert(difference == 0);
    assert(SPIKE_IMMUNE(g_Player) == 1 && engine_obj.cur_character == input->character);
    i = (u8)core.hp | ((u32)(u8)core.invincibility_timer << 8) | ((u32)core.ext.main_18.state.runtime.unk83 << 16)
        | ((u32)core.ext.main_18.state.runtime.unk80 << 24);
    i ^= (u32)(u8)weapon_objects[0].unk98 << 4 ^ (u32)core.unk42;
    {
        u32 b;
        for (b = 0; b < 6; b++)
            D_8013E198[b] = banks[b];
    }
    return i;
}

static const u32 ice_core_hit_cases_expected[] = { 0x41098263u, 0x800C8563u, 0x80118263u, 0x80078573u, 0x8007857Eu, 0x8007047Eu, 0x8007047Eu, 0x8007847Eu };

static u8 sprite_data[4];
static u32 spray_case(u32 mode)
{
    struct MainObj obj, before;
    struct ShotObj pool_before[32];
    struct PlayerObj player_before = g_Player;
    u32 i, allocated = 0;
    static const u8 two_slots[2] = { 17, 31 };
    static const u8 four_slots[4] = { 17, 20, 28, 31 };
    u32 expected_count = mode == 1 ? 2 : mode == 2 ? 4
                                                   : 0;
    u8 variant = mode == 2 ? 1 : mode == 3 ? 8
                                           : 0;
    memset(&obj, 0, sizeof(obj));
    memset(shot_objects, 0, sizeof(shot_objects));
    for (i = 0; i < 32; i++) {
        shot_objects[i].active = 1;
        shot_objects[i].id = 0x27;
        shot_objects[i].state = 0x28;
    }
    if (mode == 1)
        shot_objects[17].active = shot_objects[31].active = 0;
    if (mode == 2)
        shot_objects[17].active = shot_objects[20].active = shot_objects[28].active = shot_objects[31].active = 0;
    obj.active = 0x41;
    obj.id = 18;
    obj.state = 1;
    obj.unk5 = 10;
    obj.unk6 = 2;
    obj.unk40 = 0x1234;
    obj.unk42 = 0x4567;
    obj.bg_offset = 1;
    obj.unk15 = PLAYER_FACING_RIGHT;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.sprite_frames = (void*)sprite_data;
    obj.animation_table = (const u8* const*)D_800FC2B4;
    obj.ext.main_18.state.runtime.unk86 = variant;
    set_animation(&obj, 0);
    D_8013E198[2] = -1;
    before = obj;
    memcpy(pool_before, shot_objects, sizeof(pool_before));
    ice_core_spray_fire(&obj);
    before.unk6 = 1;
    before.ext.main_18.state.runtime.unk86++;
    before.unk17 = variant + 13;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = (const u8*)D_800FC2B4[variant + 13];
    before.animation_step = *D_800FC2B4[variant + 13];
    for (i = 0; i < expected_count; i++) {
        struct ShotObj* shot = &pool_before[mode == 1 ? two_slots[i] : four_slots[i]];
        shot->active = 0x41;
        shot->id = 12;
        shot->unk2 = mode == 1 ? 1 + 2 * i : 2 * i;
        shot->unk40 = obj.unk40;
        shot->unk42 = obj.unk42;
        shot->animation_table = (u32**)obj.animation_table;
        shot->unk3C = (void*)obj.sprite_frames;
        shot->bg_offset = obj.bg_offset;
        shot->x_pos.val = obj.x_pos.val;
        shot->y_pos.val = obj.y_pos.val;
        shot->unk15 = obj.unk15;
        shot->unk7C = (struct WeaponObj*)&obj.state;
        shot->state = 0;
    }
    for (i = 0; i < 32; i++)
        if (shot_objects[i].active == 0x41 && shot_objects[i].id == 12)
            allocated++;
    assert(allocated == expected_count);
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(shot_objects, pool_before, sizeof(pool_before));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    assert(D_8013E198[2] == -1);
    return (u8)obj.unk6 | ((u32)obj.ext.main_18.state.runtime.unk86 << 8) | (allocated << 16);
}
static const u32 ice_core_spray_pool_cases_expected[] = { 0x101u, 0x20101u, 0x40201u, 0x901u };

struct func_80050874_case {
    u32 state, weapon;
    const u8* box;
    u32 damage, damage_flags, weapon_unk80;
    s32 unk63;
    u32 unk65, unk87;
};
static const struct func_80050874_case func_80050874_cases[] = {
    { 1, 1, (const u8*)lightning_web_shot_box, 255, 0, 6488163, -1, 1, 0 },
    { 2, 0, (const u8*)lemon_hit_box, 0, 1, 0, 0, 0, 7 },
};
static struct WeaponObj func_80050874_weapons_expected[16];
static struct VisualObj func_80050874_visuals_expected[32];
static u32 test_func_80050874(u32 row)
{
    const struct func_80050874_case* c = &func_80050874_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_expected;
    struct BackgroundObj background_expected;
    u32 slot;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 18;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.contact_damage = 4;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)D_800FC2B4;
    obj.terrain_box = &D_800FBF0C;
    obj.hurt_box = &D_800FBEF4;
    obj.attack_box = &D_800FBEF4;
    obj.collision_data = (const u16*)D_80106B74;
    set_animation(&obj, 1);
    obj.state = c->state;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.hp = 10;
    obj.ext.main_18.saved_unk5 = 1;
    obj.ext.main_18.state.runtime.unk81 = 1;
    obj.ext.main_18.state.runtime.unk87 = 7;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.hp = 16;
    SPIKE_IMMUNE_SET(g_Player, 1);
    engine_obj.cur_character = 1;
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    memset(D_8013E198, -1, sizeof(D_8013E198));
    for (slot = 0; slot < 32; ++slot)
        visual_objects[slot].active = 1;
    for (slot = 0; slot < 16; ++slot)
        weapon_objects[slot].active = 0;
    memset(&weapon_objects[0], 0, sizeof(weapon_objects[0]));
    weapon_objects[0].active = 0x21;
    weapon_objects[0].id = c->weapon;
    weapon_objects[0].unk64 = 1;
    weapon_objects[0].unk50 = c->box;
    weapon_objects[0].x_pos = obj.x_pos;
    weapon_objects[0].y_pos = obj.y_pos;
    assert(((const u8*)D_80106B74)[c->weapon * 2] == c->damage);
    assert(((const u8*)D_80106B74)[c->weapon * 2 + 1] == c->damage_flags);
    memcpy(func_80050874_weapons_expected, weapon_objects, sizeof(weapon_objects));
    TEST_SET_HALVES(func_80050874_weapons_expected[0].unk80, c->weapon_unk80 & 0xFFFF, c->weapon_unk80 >> 16);
    func_80050874_weapons_expected[0].unk98 = 0;
    memcpy(func_80050874_visuals_expected, visual_objects, sizeof(visual_objects));
    expected = obj;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.unk63 = c->unk63;
    expected.unk65 = c->unk65;
    expected.ext.main_18.state.runtime.unk80 = 0;
    expected.ext.main_18.state.runtime.unk83 = 0;
    expected.ext.main_18.state.runtime.unk87 = c->unk87;
    expected.on_screen = 1;
    player_expected = g_Player;
    player_expected.update_delay_request = 0;
    engine_expected = engine_obj;
    background_expected = background_objects[0];
    func_80050874(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    c_test_same_words(weapon_objects, func_80050874_weapons_expected, sizeof(weapon_objects));
    c_test_same_words(visual_objects, func_80050874_visuals_expected, sizeof(visual_objects));
    c_test_same_words(&background_objects[0], &background_expected, sizeof(background_expected));
    return 1;
}

struct func_800517D0_0_case {
    u32 full;
    u32 expected[3];
};
static const struct func_800517D0_0_case func_800517D0_0_cases[] = {
    { 1, { 0x83FFu, 1u, 1u } },
    { 0, { 0x83FFu, 0x41u, 0u } },
};
static u32 test_func_800517D0_0(u32 row)
{
    const struct func_800517D0_0_case* c = &func_800517D0_0_cases[row];
    u32 observed_values[3];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct ShotObj shots_expected[32];
    struct MiscObj misc_expected[64];
    u8 pools_full, full, event;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 18;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 48;
    obj.contact_damage = 4;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)D_800FC2B4;
    obj.terrain_box = &D_800FBF0C;
    obj.hurt_box = &D_800FBEF4;
    obj.attack_box = &D_800FBEF4;
    obj.collision_data = (const u16*)D_80106B74;
    set_animation(&obj, 1);
    obj.unk5 = 8;
    obj.unk6 = 1;
    obj.ext.main_18.ice_pieces = 0;
    set_animation(&obj, 8);
    obj.animation_cursor = (const u8*)&D_800FC2B4[8][30];
    obj.animation_step = D_800FC2B4[8][30];
    D_8013E198[2] = -1;
    pools_full = 1;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pools_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pools_full ? 1 : 0;
    }
    full = c->full;
    event = 3;
    if (!full) {
        memset(&shot_objects[31], 0, sizeof(shot_objects[31]));
    }
    if (!full) {
        memset(&misc_objects[63], 0, sizeof(misc_objects[63]));
    }
    memcpy(shots_expected, shot_objects, sizeof(shots_expected));
    memcpy(misc_expected, misc_objects, sizeof(misc_expected));
    if (!full && event == 3) {
        shots_expected[31].active = 0x41;
    }
    if (!full && event == 3) {
        shots_expected[31].id = 12;
    }
    if (!full && event == 3) {
        shots_expected[31].unk40 = obj.unk40;
    }
    if (!full && event == 3) {
        shots_expected[31].unk42 = obj.unk42;
    }
    if (!full && event == 3) {
        shots_expected[31].animation_table = (u32**)obj.animation_table;
    }
    if (!full && event == 3) {
        shots_expected[31].unk3C = (void*)obj.sprite_frames;
    }
    if (!full && event == 3) {
        shots_expected[31].x_pos.val = 0x17B10000;
    }
    if (!full && event == 3) {
        shots_expected[31].y_pos.val = 0x08200000;
    }
    if (!full && event == 3) {
        shots_expected[31].state = 3;
    }
    if (!full && event == 3) {
        shots_expected[31].unk7C = (struct WeaponObj*)&obj.ext.main_18.ice_pieces;
    }
    if (!full && event == 3) {
        shots_expected[31].bg_offset = obj.bg_offset;
    }
    if (!full && event == 2) {
        misc_expected[63].active = 0x41;
    }
    if (!full && event == 2) {
        misc_expected[63].id = 6;
    }
    if (!full && event == 2) {
        misc_expected[63].unk40 = obj.unk40;
    }
    if (!full && event == 2) {
        misc_expected[63].unk42 = obj.unk42 & 0x7FFF;
    }
    if (!full && event == 2) {
        misc_expected[63].animation_table = (u32**)obj.animation_table;
    }
    if (!full && event == 2) {
        misc_expected[63].unk3C = (void*)obj.sprite_frames;
    }
    if (!full && event == 2) {
        misc_expected[63].bg_offset = obj.bg_offset;
    }
    if (!full && event == 2) {
        misc_expected[63].x_pos = obj.x_pos;
    }
    if (!full && event == 2) {
        misc_expected[63].y_pos = obj.y_pos;
    }
    expected = obj;
    expected.animation_cursor = (const u8*)&D_800FC2B4[8][31];
    expected.animation_step = D_800FC2B4[8][31];
    if (event == 3) {
        expected.ext.main_18.ice_pieces = 0x83FF;
    }
    if (event == 2) {
        expected.invincibility_timer = -128;
    }
    player_expected = g_Player;
    engine_before = engine_obj;
    func_800517D0(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(shot_objects, shots_expected, sizeof(shots_expected));
    c_test_same_words(misc_objects, misc_expected, sizeof(misc_expected));
    assert(D_8013E198[2] == -1);
    observed_values[0] = (u32)obj.ext.main_18.ice_pieces;
    observed_values[1] = (u32)shot_objects[31].active;
    observed_values[2] = (u32)misc_objects[63].active;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}
static const u32 inputs_1[2][19] = {
    { 0x41, 18, 1, 1, 1, 0, 0x00641234, 0x00645678, 48, 4, 0x56, 0x1234, 8, 1, 0, -1, 1, 1, 2 },
    { 0x41, 18, 1, 1, 1, 0, 0x00641234, 0x00645678, 48, 4, 0x56, 0x1234, 8, 1, 0, -1, 1, 0, 2 },
};
struct func_800517D0_1_case {
    u32 expected[3];
};
static const struct func_800517D0_1_case func_800517D0_1_cases[] = {
    { { 0u, 1u, 1u } },
    { { 0u, 0u, 0x41u } },
};
static u32 test_func_800517D0_1(u32 row)
{
    const struct func_800517D0_1_case* c = &func_800517D0_1_cases[row];
    u32 observed_values[3];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct ShotObj shots_expected[32];
    struct MiscObj misc_expected[64];
    u8 pools_full, full, event;
    memset(&obj, 0, sizeof(obj));
    obj.active = inputs_1[row][0];
    obj.id = inputs_1[row][1];
    obj.state = inputs_1[row][2];
    obj.unk5 = inputs_1[row][3];
    obj.unk6 = inputs_1[row][4];
    obj.bg_offset = inputs_1[row][5];
    obj.x_pos.val = inputs_1[row][6];
    obj.y_pos.val = inputs_1[row][7];
    obj.hp = inputs_1[row][8];
    obj.contact_damage = inputs_1[row][9];
    obj.unk40 = inputs_1[row][10];
    obj.unk42 = inputs_1[row][11];
    obj.animation_table = (const u8* const*)D_800FC2B4;
    obj.terrain_box = &D_800FBF0C;
    obj.hurt_box = &D_800FBEF4;
    obj.attack_box = &D_800FBEF4;
    obj.collision_data = (const u16*)D_80106B74;
    set_animation(&obj, 1);
    obj.unk5 = inputs_1[row][12];
    obj.unk6 = inputs_1[row][13];
    obj.ext.main_18.ice_pieces = inputs_1[row][14];
    set_animation(&obj, 8);
    obj.animation_cursor = (const u8*)&D_800FC2B4[8][15];
    obj.animation_step = D_800FC2B4[8][15];
    D_8013E198[2] = inputs_1[row][15];
    pools_full = inputs_1[row][16];
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pools_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pools_full ? 1 : 0;
    }
    full = inputs_1[row][17];
    event = inputs_1[row][18];
    if (!full) {
        memset(&shot_objects[31], 0, sizeof(shot_objects[31]));
    }
    if (!full) {
        memset(&misc_objects[63], 0, sizeof(misc_objects[63]));
    }
    memcpy(shots_expected, shot_objects, sizeof(shots_expected));
    memcpy(misc_expected, misc_objects, sizeof(misc_expected));
    if (!full && event == 3) {
        shots_expected[31].active = 0x41;
    }
    if (!full && event == 3) {
        shots_expected[31].id = 12;
    }
    if (!full && event == 3) {
        shots_expected[31].unk40 = obj.unk40;
    }
    if (!full && event == 3) {
        shots_expected[31].unk42 = obj.unk42;
    }
    if (!full && event == 3) {
        shots_expected[31].animation_table = (u32**)obj.animation_table;
    }
    if (!full && event == 3) {
        shots_expected[31].unk3C = (void*)obj.sprite_frames;
    }
    if (!full && event == 3) {
        shots_expected[31].x_pos.val = 0x17B10000;
    }
    if (!full && event == 3) {
        shots_expected[31].y_pos.val = 0x08200000;
    }
    if (!full && event == 3) {
        shots_expected[31].state = 3;
    }
    if (!full && event == 3) {
        shots_expected[31].unk7C = (struct WeaponObj*)&obj.ext.main_18.ice_pieces;
    }
    if (!full && event == 3) {
        shots_expected[31].bg_offset = obj.bg_offset;
    }
    if (!full && event == 2) {
        misc_expected[63].active = 0x41;
    }
    if (!full && event == 2) {
        misc_expected[63].id = 6;
    }
    if (!full && event == 2) {
        misc_expected[63].unk40 = obj.unk40;
    }
    if (!full && event == 2) {
        misc_expected[63].unk42 = obj.unk42 & 0x7FFF;
    }
    if (!full && event == 2) {
        misc_expected[63].animation_table = (u32**)obj.animation_table;
    }
    if (!full && event == 2) {
        misc_expected[63].unk3C = (void*)obj.sprite_frames;
    }
    if (!full && event == 2) {
        misc_expected[63].bg_offset = obj.bg_offset;
    }
    if (!full && event == 2) {
        misc_expected[63].x_pos = obj.x_pos;
    }
    if (!full && event == 2) {
        misc_expected[63].y_pos = obj.y_pos;
    }
    expected = obj;
    expected.animation_cursor = (const u8*)&D_800FC2B4[8][16];
    expected.animation_step = D_800FC2B4[8][16];
    if (event == 3) {
        expected.ext.main_18.ice_pieces = 0x83FF;
    }
    if (event == 2) {
        expected.invincibility_timer = -128;
    }
    player_expected = g_Player;
    engine_before = engine_obj;
    func_800517D0(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(shot_objects, shots_expected, sizeof(shots_expected));
    c_test_same_words(misc_objects, misc_expected, sizeof(misc_expected));
    assert(D_8013E198[2] == -1);
    observed_values[0] = (u32)obj.ext.main_18.ice_pieces;
    observed_values[1] = (u32)shot_objects[31].active;
    observed_values[2] = (u32)misc_objects[63].active;
    return c_test_observe(1, row, observed_values, c->expected, 3);
}
static u32 test_func_800517D0(u32 index)
{
    if (index < 2)
        return test_func_800517D0_0(index);
    index -= 2;
    return test_func_800517D0_1(index);
}

static const u32 func_80052218_expected[] = { 1u, 0x74u, 0x41u, 0u, 0x41u };
static u32 test_func_80052218(u32 row)
{
    u32 observed_values[5];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct ItemObj items_expected[32];
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 18;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 48;
    obj.contact_damage = 4;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)D_800FC2B4;
    obj.terrain_box = &D_800FBF0C;
    obj.hurt_box = &D_800FBEF4;
    obj.attack_box = &D_800FBEF4;
    obj.collision_data = (const u16*)D_80106B74;
    set_animation(&obj, 1);
    obj.unk5 = 11;
    obj.unk6 = 0;
    obj.x_speed = 0x10000;
    obj.x_accel = 0x1000;
    obj.y_speed = -0x10000;
    obj.gravity = 0x2000;
    memset(item_objects, 0, sizeof(item_objects));
    FILL_ACTIVE(item_objects, 32, 1);
    item_objects[0].id = 8;
    item_objects[31].id = 8;
    item_objects[0].active = 0x41;
    item_objects[31].active = 0x41;
    memcpy(items_expected, item_objects, sizeof(items_expected));
    FILL_ACTIVE(items_expected, 32, 0);
    items_expected[0].active = 0x41;
    items_expected[31].active = 0x41;
    expected = obj;
    expected.x_speed = 0;
    expected.x_accel = 0;
    expected.y_speed = 0x10000;
    expected.gravity = 0;
    expected.unk7C = 0x74;
    expected.unk6 = 1;
    player_expected = g_Player;
    player_expected.script_state = 1;
    player_expected.script_action = 0x15;
    player_expected.script_facing = 0;
    SPIKE_IMMUNE_SET(player_expected, 1);
    engine_before = engine_obj;
    engine_before.gameplay_locked = 1;
    func_80052218(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(item_objects, items_expected, sizeof(items_expected));
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.unk7C;
    observed_values[2] = (u32)item_objects[0].active;
    observed_values[3] = (u32)item_objects[1].active;
    observed_values[4] = (u32)item_objects[31].active;
    return c_test_observe(0, row, observed_values, func_80052218_expected, 5);
}

struct func_800527F0_case {
    u32 hi, unk84, gravity;
};
static const struct func_800527F0_case func_800527F0_cases[] = {
    { 2192, 0, 4096 },
    { 2193, 0, -4096 },
    { 2224, 1, 4096 },
    { 2225, 1, -4096 },
};
static u32 test_func_800527F0(u32 row)
{
    const struct func_800527F0_case* c = &func_800527F0_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 18;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 48;
    obj.contact_damage = 4;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)D_800FC2B4;
    obj.terrain_box = &D_800FBF0C;
    obj.hurt_box = &D_800FBEF4;
    obj.attack_box = &D_800FBEF4;
    obj.collision_data = (const u16*)D_80106B74;
    set_animation(&obj, 1);
    obj.unk5 = 9;
    obj.unk6 = 2;
    obj.x_speed = 0x10000;
    obj.x_accel = 0x2000;
    obj.y_speed = -0x10000;
    obj.gravity = 0x2000;
    obj.y_pos.i.hi = c->hi;
    obj.ext.main_18.state.runtime.unk84 = c->unk84;
    expected = obj;
    player_expected = g_Player;
    engine_before = engine_obj;
    expected.unk5 = 7;
    expected.unk6 = 0;
    expected.x_speed = 0;
    expected.x_accel = 0;
    expected.y_speed = 0;
    expected.gravity = c->gravity;
    func_800527F0(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

struct ice_core_bob_move_case {
    u32 y_speed;
    u32 expected[3];
};
static const struct ice_core_bob_move_case ice_core_bob_move_cases[] = {
    { 98304, { 0x1000u, 0u, 0x18000u } },
    { -98304, { 0xFFFFF000u, 0xFFFFFFFFu, 0xFFFE8000u } },
};
static u32 test_ice_core_bob_move(u32 row)
{
    const struct ice_core_bob_move_case* c = &ice_core_bob_move_cases[row];
    u32 observed_values[3];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.animation_step.fields.event = 2;
    obj.y_speed = c->y_speed;
    ice_core_bob_move(&obj);
    observed_values[0] = (u32)obj.gravity;
    observed_values[1] = (u32)obj.unk7C;
    observed_values[2] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

struct ice_core_build_grow_case {
    u32 unk7E, obj_hp, expected_hp, unk85;
};
static const struct ice_core_build_grow_case ice_core_build_grow_cases[] = {
    { 255, 48, 48, 3 },
    { 255, 47, 48, 2 },
    { 0, 47, 47, 3 },
};
static u32 test_ice_core_build_grow(u32 row)
{
    const struct ice_core_build_grow_case* c = &ice_core_build_grow_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 18;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 48;
    obj.contact_damage = 4;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)D_800FC2B4;
    obj.terrain_box = &D_800FBF0C;
    obj.hurt_box = &D_800FBEF4;
    obj.attack_box = &D_800FBEF4;
    obj.collision_data = (const u16*)D_80106B74;
    set_animation(&obj, 1);
    obj.unk5 = 8;
    obj.unk6 = 2;
    *(u8*)&obj.unk7E = c->unk7E;
    obj.hp = c->obj_hp;
    obj.ext.main_18.state.runtime.unk85 = 3;
    set_animation(&obj, 9);
    expected = obj;
    player_expected = g_Player;
    engine_before = engine_obj;
    expected.hp = c->expected_hp;
    expected.ext.main_18.state.runtime.unk85 = c->unk85;
    expected.animation_step.fields.duration = 9;
    ice_core_build_grow(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

struct ice_core_charge_run_case {
    u32 unk15, x_speed, unk83, x_pos, reset_animation, unk6;
};
static const struct ice_core_charge_run_case ice_core_charge_run_cases[] = {
    { 0, -65536, 9, 6492724, 0, 4 },
    { 0, -65536, 10, 6492724, 1, 5 },
    { 64, 65536, 9, 6623796, 0, 4 },
    { 64, 65536, 10, 6623796, 1, 5 },
};
static u32 test_ice_core_charge_run(u32 row)
{
    const struct ice_core_charge_run_case* c = &ice_core_charge_run_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    u8 reset_animation;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 18;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 48;
    obj.contact_damage = 4;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)D_800FC2B4;
    obj.terrain_box = &D_800FBF0C;
    obj.hurt_box = &D_800FBEF4;
    obj.attack_box = &D_800FBEF4;
    obj.collision_data = (const u16*)D_80106B74;
    set_animation(&obj, 1);
    obj.unk5 = 4;
    obj.unk6 = 4;
    obj.unk15 = TEST_FACING(c->unk15);
    obj.collision_flags = 0;
    obj.x_speed = c->x_speed;
    obj.y_speed = 0x10000;
    obj.ext.main_18.state.runtime.unk83 = c->unk83;
    set_animation(&obj, 3);
    expected = obj;
    player_expected = g_Player;
    engine_before = engine_obj;
    expected.x_pos.val = c->x_pos;
    expected.y_pos.val = 0x00635678;
    reset_animation = c->reset_animation;
    if (reset_animation) {
        set_animation(&expected, 12);
    }
    if (!reset_animation) {
        expected.animation_step.fields.duration = 1;
    }
    expected.unk6 = c->unk6;
    ice_core_charge_run(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

struct ice_core_charge_slide_1_case {
    u32 obj_unk7C, unk15, collision_flags, obj_x_speed, x_pos, y_pos, expected_x_speed, x_accel, y_speed;
    u32 expected_unk7C, unk6;
};
static const struct ice_core_charge_slide_1_case ice_core_charge_slide_1_cases[] = {
    { 2, 0, 0, 65536, 6623796, 6510200, 0, 0, 61440, 1, 2 },
    { 2, 64, 0, -65536, 6492724, 6510200, 0, 0, 61440, 1, 2 },
    { 2, 0, 3, 65536, 6558260, 6575736, 65536, 65536, 65536, 1, 2 },
    { 1, 64, 0, -65536, 6492724, 6510200, 0, 0, 61440, 28, 3 },
};
static u32 test_ice_core_charge_slide_1(u32 row)
{
    const struct ice_core_charge_slide_1_case* c = &ice_core_charge_slide_1_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 18;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 48;
    obj.contact_damage = 4;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)D_800FC2B4;
    obj.terrain_box = &D_800FBF0C;
    obj.hurt_box = &D_800FBEF4;
    obj.attack_box = &D_800FBEF4;
    obj.collision_data = (const u16*)D_80106B74;
    set_animation(&obj, 1);
    obj.unk5 = 4;
    obj.unk6 = 2;
    obj.unk7C = c->obj_unk7C;
    obj.unk15 = TEST_FACING(c->unk15);
    obj.collision_flags = c->collision_flags;
    obj.x_speed = c->obj_x_speed;
    obj.x_accel = 0x10000;
    obj.y_speed = 0x10000;
    obj.gravity = 0x1000;
    set_animation(&obj, 2);
    expected = obj;
    player_expected = g_Player;
    engine_before = engine_obj;
    expected.x_pos.val = c->x_pos;
    expected.y_pos.val = c->y_pos;
    expected.x_speed = c->expected_x_speed;
    expected.x_accel = c->x_accel;
    expected.y_speed = c->y_speed;
    expected.unk7C = c->expected_unk7C;
    expected.unk6 = c->unk6;
    expected.animation_step.fields.duration = 17;
    ice_core_charge_slide(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

struct ice_core_check_rebuild_1_case {
    u32 unk88, rebuild;
};
static const struct ice_core_check_rebuild_1_case ice_core_check_rebuild_1_cases[] = {
    { 1, 0 },
    { 0, 1 },
};
static u32 test_ice_core_check_rebuild_1(u32 row)
{
    const struct ice_core_check_rebuild_1_case* c = &ice_core_check_rebuild_1_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    u8 rebuild;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 18;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 48;
    obj.contact_damage = 4;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)D_800FC2B4;
    obj.terrain_box = &D_800FBF0C;
    obj.hurt_box = &D_800FBEF4;
    obj.attack_box = &D_800FBEF4;
    obj.collision_data = (const u16*)D_80106B74;
    set_animation(&obj, 1);
    obj.unk5 = 7;
    obj.unk6 = 1;
    obj.hp = 1;
    obj.x_speed = 0x10000;
    obj.x_accel = 0x2000;
    obj.y_speed = -0x10000;
    obj.gravity = 0x2000;
    obj.ext.main_18.state.runtime.unk81 = 0;
    obj.ext.main_18.state.runtime.unk82 = 1;
    obj.ext.main_18.state.runtime.unk84 = 1;
    obj.ext.main_18.state.runtime.unk85 = 2;
    obj.ext.main_18.state.runtime.unk87 = 1;
    obj.ext.main_18.unk88 = c->unk88;
    expected = obj;
    player_expected = g_Player;
    engine_before = engine_obj;
    rebuild = c->rebuild;
    if (rebuild) {
        expected.ext.main_18.state.runtime.unk82 = 0;
    }
    if (rebuild) {
        expected.ext.main_18.state.runtime.unk85 = 0;
    }
    if (rebuild) {
        expected.ext.main_18.state.runtime.unk84 = 0;
    }
    if (rebuild) {
        set_animation(&expected, 7);
    }
    if (rebuild) {
        expected.x_speed = 0;
    }
    if (rebuild) {
        expected.x_accel = 0;
    }
    if (rebuild) {
        expected.y_speed = 0;
    }
    if (rebuild) {
        expected.gravity = 0;
    }
    if (rebuild) {
        expected.unk5 = 8;
    }
    if (rebuild) {
        expected.unk6 = 0;
    }
    ice_core_check_rebuild(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

struct ice_core_float_case {
    u32 hi;
    u32 expected[2];
};
static const struct ice_core_float_case ice_core_float_cases[] = {
    { 8192, { 0u, 0u } },
    { 0, { 2u, 0u } },
};
static u32 test_ice_core_float(u32 row)
{
    const struct ice_core_float_case* c = &ice_core_float_cases[row];
    u32 observed_values[2];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_800FBF0C, 0, sizeof(D_800FBF0C));
    obj.gravity = 458752;
    obj.ext.main_18.state.runtime.unk84 = 255;
    obj.y_pos.i.hi = c->hi;
    ice_core_float(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, c->expected, 2);
}

struct ice_core_pick_attack_case {
    u32 unk7E;
};
static const struct ice_core_pick_attack_case ice_core_pick_attack_cases[] = {
    { 2 },
    { 255 },
};
static u32 test_ice_core_pick_attack(u32 row)
{
    const struct ice_core_pick_attack_case* c = &ice_core_pick_attack_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    u16 random_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 18;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 48;
    obj.contact_damage = 4;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)D_800FC2B4;
    obj.terrain_box = &D_800FBF0C;
    obj.hurt_box = &D_800FBEF4;
    obj.attack_box = &D_800FBEF4;
    obj.collision_data = (const u16*)D_80106B74;
    set_animation(&obj, 1);
    obj.unk5 = 7;
    obj.unk6 = 1;
    *(u8*)&obj.unk7E = c->unk7E;
    obj.ext.main_18.state.runtime.unk80 = 0x43;
    random_before = cur_random;
    expected = obj;
    player_expected = g_Player;
    engine_before = engine_obj;
    expected.ext.main_18.state.runtime.unk80 = 0xC3;
    ice_core_pick_attack(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(cur_random == random_before);
    return 1;
}

struct ice_core_shed_ice_case {
    u32 shed_timer, ice_pieces;
    u32 expected[3];
};
static const struct ice_core_shed_ice_case ice_core_shed_ice_cases[] = {
    { 224, 0, { 0u, 0u, 0u } },
    { 225, 255, { 0xFEu, 0xCCu, 0u } },
};
static u32 test_ice_core_shed_ice(u32 row)
{
    const struct ice_core_shed_ice_case* c = &ice_core_shed_ice_cases[row];
    u32 observed_values[3];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&cur_random, 0, sizeof(cur_random));
    obj.ext.main_18.shed_timer = c->shed_timer;
    obj.ext.main_18.ice_pieces = c->ice_pieces;
    ice_core_shed_ice(&obj);
    observed_values[0] = (u32)obj.ext.main_18.ice_pieces;
    observed_values[1] = (u32)obj.ext.main_18.shed_timer;
    observed_values[2] = (u32)obj.ext.main_18.state.runtime.unk85;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

struct ice_core_stomp_drop_case {
    u32 obj_unk7C, expected_unk7C, unk82;
};
static const struct ice_core_stomp_drop_case ice_core_stomp_drop_cases[] = {
    { 2, 1, 1 },
    { 1, 0, 0 },
};
static u32 test_ice_core_stomp_drop(u32 row)
{
    const struct ice_core_stomp_drop_case* c = &ice_core_stomp_drop_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 18;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 48;
    obj.contact_damage = 4;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)D_800FC2B4;
    obj.terrain_box = &D_800FBF0C;
    obj.hurt_box = &D_800FBEF4;
    obj.attack_box = &D_800FBEF4;
    obj.collision_data = (const u16*)D_80106B74;
    set_animation(&obj, 1);
    obj.unk5 = 5;
    obj.unk6 = 3;
    obj.unk7C = c->obj_unk7C;
    obj.ext.main_18.state.runtime.unk82 = 1;
    obj.collision_flags = 0;
    obj.x_speed = 0x10000;
    obj.y_speed = -0x80000;
    obj.hurt_box = &D_800FBEFC;
    obj.attack_box = &D_800FBEFC;
    set_animation(&obj, 4);
    obj.animation_cursor = (const u8*)&D_800FC2B4[4][2];
    obj.animation_step = D_800FC2B4[4][2];
    expected = obj;
    player_expected = g_Player;
    engine_before = engine_obj;
    expected.x_pos.val = 0x00651234;
    expected.y_pos.val = 0x006C5678;
    expected.unk7C = c->expected_unk7C;
    expected.ext.main_18.state.runtime.unk82 = c->unk82;
    expected.hurt_box = &D_800FBEF4;
    expected.attack_box = &D_800FBEF4;
    expected.animation_step.fields.duration = 5;
    ice_core_stomp_drop(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

static const u32 ice_core_stomp_recover_expected[] = { 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_ice_core_stomp_recover(u32 row)
{
    u32 observed_values[6];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_800FBEF4, 0, sizeof(D_800FBEF4));
    obj.animation_step.fields.event = 2;
    obj.ext.main_18.ice_pieces = 32768;
    ice_core_stomp_recover(&obj);
    observed_values[0] = (u32)obj.ext.main_18.state.runtime.unk80;
    observed_values[1] = (u32)obj.ext.main_18.state.runtime.unk85;
    observed_values[2] = (u32)obj.gravity;
    observed_values[3] = (u32)obj.unk5;
    observed_values[4] = (u32)obj.unk6;
    observed_values[5] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, ice_core_stomp_recover_expected, 6);
}

struct ice_core_stomp_rise_case {
    u32 x_pos;
    u32 expected[5];
};
static const struct ice_core_stomp_rise_case ice_core_stomp_rise_cases[] = {
    { 0, { 3u, 0xAu, 0x17CDu, 0x17CD0000u, 0xFFF80000u } },
    { 536747807, { 3u, 0xAu, 0x18B5u, 0x18B51F1Fu, 0xFFF80000u } },
};
static u32 test_ice_core_stomp_rise(u32 row)
{
    const struct ice_core_stomp_rise_case* c = &ice_core_stomp_rise_cases[row];
    u32 observed_values[5];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.unk7C = 1;
    g_Player.x_pos.val = c->x_pos;
    ice_core_stomp_rise(&obj);
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.unk7C;
    observed_values[2] = (u32)obj.x_pos.i.hi;
    observed_values[3] = (u32)obj.x_pos.val;
    observed_values[4] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

extern union AnimationStep* D_800FC2B4[];
extern struct Unk_unk68 D_80106B74[];
static const u8 damages[] = { 2, 2, 1, 1 };
static struct WeaponObj weapons_expected[16];
static struct VisualObj visuals_before[32];
static u32 saber_meter(u32 row)
{
    struct MainObj obj, expected, *current = SP_CUR_MAIN_OBJ;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    u32 weapon = row % 4, character = row / 4 % 2, flags = row / 8 % 2, face = row / 16 % 2, meter = row / 32, i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 32; i++)
        visual_objects[i].active = 1;
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    g_Player.hp = 30;
    SPIKE_IMMUNE_SET(g_Player, 1);
    player_expected = g_Player;
    if (weapon >= 2)
        player_expected.update_delay_request = 1;
    engine_obj.cur_character = character;
    engine_before = engine_obj;
    obj.active = 0x41;
    obj.id = 18;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.unk15 = face ? PLAYER_FACING_RIGHT : 0;
    obj.hp = 40;
    obj.unk42 = 0x9234;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.collision_data = D_80106B74;
    obj.hurt_box = obj.attack_box = (const u8*)&D_800FBEF4;
    obj.terrain_box = &D_800FBF0C;
    obj.ext.main_18.saved_unk5 = 1;
    obj.ext.main_18.state.runtime.unk81 = 1;
    obj.ext.main_18.state.runtime.unk80 = flags ? 0x80 : 0;
    obj.ext.main_18.state.runtime.unk83 = meter ? 250 : 0;
    obj.animation_table = (const u8* const*)D_800FC2B4;
    set_animation(&obj, 1);
    assert(obj.animation_step.packed == C_TEST_STEP(0x00010002));
    weapon_objects[0].active = 0x21;
    weapon_objects[0].id = 24 + weapon;
    weapon_objects[0].unk50 = (const u8*)&D_800FBEF4;
    weapon_objects[0].x_pos = obj.x_pos;
    weapon_objects[0].y_pos = obj.y_pos;
    weapon_objects[0].unk15 = obj.unk15;
    assert(((const u8*)D_80106B74)[(24 + weapon) * 2] == 0 && ((const u8*)D_80106B74)[(24 + weapon) * 2 + 1] == damages[weapon]);
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    ((s16*)&weapons_expected[0].unk80)[0] = face ? 159 : 161;
    ((s16*)&weapons_expected[0].unk80)[1] = 122;
    expected = obj;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.hp -= damages[weapon];
    expected.unk42 |= 0x8000;
    expected.invincibility_timer = character ? 1 : 6;
    expected.on_screen = 1;
    expected.ext.main_18.state.runtime.unk87 = 1;
    expected.ext.main_18.state.runtime.unk80 = flags ? 0x80 : 0x41;
    if (weapon != 3)
        expected.ext.main_18.state.runtime.unk83 += 5;
    D_8013E198[0] = D_8013E198[1] = D_8013E198[5] = -1;
    cur_random = 0x1234;
    SP_CUR_MAIN_OBJ = &obj;
    func_80050874(&obj);
    assert(SP_CUR_MAIN_OBJ == &obj);
    SP_CUR_MAIN_OBJ = current;
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(c_test_word_difference((u32*)weapon_objects, (u32*)weapons_expected, sizeof(weapons_expected) / 4) == 0);
    assert(c_test_word_difference((u32*)visual_objects, (u32*)visuals_before, sizeof(visuals_before) / 4) == 0);
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(cur_random == 0x1234);
    return 1;
}

#include "support/tile_writes.h"
void ice_core_death_sink(struct MainObj*);
void ice_core_drift(struct MainObj*);
void ice_core_bob(struct MainObj*);
void ice_core_charge(struct MainObj*);
void ice_core_stomp(struct MainObj*);
void ice_core_build(struct MainObj*);
void ice_core_bounce(struct MainObj*);
void ice_core_spray(struct MainObj*);
void ice_core_intro(struct MainObj*);
void ice_core_fall(struct MainObj*);
extern struct Unk_unk68 D_800FBF00;
extern struct Unk_unk68 D_800FBF04;
extern struct Unk_unk68 D_800FBF08;
extern struct Unk_unk68 D_800FBF10;

static struct MainObj ic;
static struct Unk_unk68 ic_box = { -2, -2, 4, 4 };
static u8 ic_damage[0x80];
static s32 ic_sprites[4] = { 8, 12, 0, 0 };
#define IC ic.ext.main_18.state.runtime
static void ic_reset(u8 state, u8 unk5, u8 unk6)
{
    memset(&ic, 0, sizeof(ic));
    memset(shot_objects, 0, sizeof(shot_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(background_objects, 0, sizeof(background_objects));
    memset(&g_Player, 0, sizeof(g_Player));
    TEST_SPRITE_FRAMES = (u8*)ic_sprites;
    cur_random = 0;
    engine_obj.cur_character = CHARACTER_X;
    ic.active = 0x41;
    ic.id = 18;
    ic.state = state;
    ic.unk5 = unk5;
    ic.unk6 = unk6;
    ic.x_pos.i.hi = 0x1840;
    ic.y_pos.i.hi = 0x870;
    ic.collision_data = D_80106B74;
    ic.animation_table = (const u8* const*)D_800FC2B4;
    set_animation(&ic, 0);
    g_Player.x_pos.i.hi = 0x1800;
}
static void ic_step(s8 event)
{
    ic.animation_step.fields.duration = 5;
    ic.animation_step.fields.event = event;
    ic.animation_step.fields.relative_step = 1;
}

static void ic_death(void)
{
    ic_reset(2, 0, 0);
    IC.unk82 = 1;
    ic.y_pos.i.hi = 0x900;
    ic.unk7C = 2;
    ic.unk7E = 2;
    ice_core_update(&ic);
    assert(ic.y_pos.i.hi == 0x901 && ic.unk7C == 1 && ic.unk7E == 1 && visual_objects[0].active == 0);
    ice_core_update(&ic);
    assert(ic.y_pos.i.hi == 0x902 && ic.x_pos.i.hi == 0x1840 && ic.unk7C == 4 && ic.unk7E == 8 && visual_objects[1].active == 0x21);
    ic.state = 3;
    IC.unk82 = 0;
    ice_core_update(&ic);
    assert(ic.state == 4 && g_Player.script_action == 0x15 && g_Player.script_facing == PLAYER_FACING_RIGHT);
    g_Player.x_pos.i.hi = 0x18F0;
    ice_core_update(&ic);
    assert(ic.active == 0x41 && g_Player.script_state == 1);
    g_Player.x_pos.i.hi = 0x18F1;
    engine_obj.unkF = 0;
    ice_core_update(&ic);
    assert(g_Player.script_state == 0 && engine_obj.unkF == 0x40 && ic.ext.raw[0] == 0 && ic.ext.raw[5] == 0);
}
static void ic_drift(void)
{
    static const struct {
        u8 facing, wall, bobbing;
    } walls[] = { { 0, 2, 1 }, { 0, 2, 0 }, { 1, 1, 1 }, { 1, 1, 0 } };
    u32 i;
    ic_reset(1, 2, 0);
    ice_core_drift(&ic);
    assert(ic.unk6 == 1 && ic.x_speed == FIXED(-1.375) && ic.gravity == FIXED(-0.125));
    ic.unk6 = 0;
    ic.unk15 = PLAYER_FACING_RIGHT;
    ice_core_drift(&ic);
    assert(ic.x_speed == FIXED(1.375));
    ic.unk15 = 0;
    ic.y_speed = 0x2E000;
    ic.gravity = -0x2000;
    ice_core_drift(&ic);
    assert(ic.unk6 == 1 && ic.y_speed == 0x30000 && ic.gravity == 0x2000);
    ic.unk15 = PLAYER_FACING_RIGHT;
    ic.y_speed = -0x2E000;
    ice_core_drift(&ic);
    assert(ic.y_speed == -0x30000 && ic.gravity == -0x2000);
    for (i = 0; i < COUNT(walls); i++) {
        ic_reset(1, 2, 1);
        ic.unk15 = walls[i].facing ? PLAYER_FACING_RIGHT : 0;
        ic.collision_flags = walls[i].wall;
        IC.unk84 = walls[i].bobbing;
        ice_core_drift(&ic);
        if (walls[i].bobbing)
            assert(ic.unk5 == 3 && ic.unk6 == 2 && ic.unk17 == 6 && ic.unk15 == 0);
        else
            assert(ic.unk5 == 7 && ic.unk6 == 0 && ic.unk15 == (walls[i].facing ? 0 : PLAYER_FACING_RIGHT));
    }
}
static void ic_bob(void)
{
    ic_reset(1, 3, 0);
    ice_core_bob(&ic);
    assert(ic.unk6 == 1 && IC.unk84 == 1 && ic.unk7C == 1 && ic.gravity == FIXED(0.0625) && ic.unk17 == 1);
    assert(ic.hurt_box == &D_800FBF00 && ic.attack_box == &D_800FBF00);
    ic.unk7C = 2;
    ic.y_speed = -0x17000;
    ic.gravity = 0x1000;
    ic_step(0);
    ice_core_bob(&ic);
    assert(ic.unk6 == 1 && ic.unk7C == 1 && ic.gravity == -0x1000 && ic.collision_data == D_80106B74);
    ic.y_speed = -0x17000;
    ic.gravity = 0x1000;
    ice_core_bob(&ic);
    assert(ic.unk7C == 0 && ic.y_speed == 0 && ic.gravity == 0x1000 && ic.unk5 == 7 && ic.unk6 == 0);
    ic.unk5 = 3;
    ic.unk6 = 2;
    ic.collision_data = D_801060F0;
    ic_step(2);
    ice_core_bob(&ic);
    assert(ic.collision_data == D_80106B74 && ic.hurt_box == &D_800FBEF4 && ic.unk6 == 2);
    IC.unk80 = 0x45;
    ic_step(1);
    ice_core_bob(&ic);
    assert(IC.unk84 == 0 && IC.unk80 == 5 && ic.unk17 == 2 && ic.unk5 == 7 && ic.unk6 == 0);
}
static void ic_charge(void)
{
    ic_reset(1, 4, 0);
    ic.x_speed = 0x10000;
    ice_core_charge(&ic);
    assert(ic.unk6 == 1 && ic.unk7C == 0x1C && ic.x_speed == 0 && ic.unk15 == 0);
    ic.unk7C = 2;
    ice_core_charge(&ic);
    assert(ic.unk6 == 1 && ic.unk7C == 1);
    ice_core_charge(&ic);
    assert(ic.unk6 == 2 && ic.x_speed == FIXED(3) && ic.x_accel == FIXED(0.09375) && ic.unk7C == 0x14);
    ic.unk6 = 1;
    ic.unk7C = 1;
    ic.unk15 = PLAYER_FACING_RIGHT;
    ice_core_charge(&ic);
    assert(ic.x_speed == FIXED(-3));
    ic.unk15 = 0;
    ic.x_speed = 0x30000;
    ic.x_accel = 0x1800;
    ice_core_charge(&ic);
    assert(ic.unk6 == 2 && ic.x_speed == 0x2E800 && ic.x_accel == 0x1800);
    ic.unk6 = 3;
    ic.unk7C = 2;
    ice_core_charge(&ic);
    assert(ic.unk6 == 3 && ic.unk7C == 1);
    ice_core_charge(&ic);
    assert(ic.unk6 == 4 && ic.x_speed == FIXED(-4) && ic.contact_damage == 6 && IC.unk81 == 1 && ic.unk17 == 3);
    ic.unk6 = 3;
    ic.unk7C = 1;
    ic.unk15 = PLAYER_FACING_RIGHT;
    ice_core_charge(&ic);
    assert(ic.x_speed == FIXED(4));
}
static void ic_charge_walls(void)
{
    ic_reset(1, 4, 4);
    ic.collision_flags = 2;
    ic_step(0);
    ice_core_charge_run(&ic);
    assert(ic.unk6 == 5 && ic.unk17 == 0xC && ic.hurt_box == NULL);
    ic.unk6 = 4;
    ic.unk15 = PLAYER_FACING_RIGHT;
    ic.collision_flags = 1;
    ic_step(2);
    ice_core_charge_run(&ic);
    assert(ic.unk6 == 5 && ic.hurt_box == &D_800FBEFC && ic.attack_box == &D_800FBEFC);
    ic.contact_damage = 6;
    IC.unk81 = 1;
    IC.unk83 = 7;
    IC.unk80 = 0x41;
    ic_step(2);
    ice_core_charge(&ic);
    assert(ic.contact_damage == 4 && ic.attack_box == &D_800FBEF4 && ic.hurt_box == &D_800FBEF4 && ic.unk6 == 5);
    ic_step(1);
    ice_core_charge(&ic);
    assert(ic.unk5 == 7 && IC.unk83 == 0 && IC.unk81 == 0 && IC.unk80 == 0 && ic.unk17 == 2);
}
static void ic_stomp(void)
{
    ic_reset(1, 5, 0);
    ice_core_stomp(&ic);
    assert(ic.unk6 == 1 && IC.unk82 == 1 && ic.attack_box == &D_800FBF00 && ic.gravity == FIXED(0.2578125) && ic.unk7C == 0x5A);
    ic.unk7C = 3;
    ic.y_pos.i.hi = 0x8B9;
    ic_step(2);
    ice_core_stomp(&ic);
    assert(ic.unk7C == 2 && ic.collision_data == D_801060F0 && ic.y_pos.i.hi == 0x8B9 && ic.y_speed == -FIXED(0.2578125));
    ic.y_pos.i.hi = 0x8BA;
    ic_step(0);
    ice_core_stomp(&ic);
    assert(ic.unk7C == 1 && ic.y_pos.i.hi == 0x8BA && ic.y_speed == 0 && ic.gravity == 0);
    ic.unk7C = 2;
    ic.y_pos.i.hi = 0x8C0;
    ice_core_stomp(&ic);
    assert(ic.y_pos.i.hi == 0x8C0);
    ic.collision_flags = 8;
    ice_core_stomp(&ic);
    assert(ic.unk6 == 2 && ic.y_speed == FIXED(6) && ic.unk7C == 0x50 && ic.collision_flags == 0);
    ic.unk7C = 0x30;
    ice_core_stomp(&ic);
    assert(ic.unk6 == 2 && ic.unk7C == 0x2F && ic.y_pos.i.hi == 0x8BA);
    ic.unk6 = 3;
    ic.unk7C = 5;
    ic.collision_flags = 8;
    ic_step(0);
    ice_core_stomp(&ic);
    assert(ic.unk6 == 4 && ic.ext.main_18.shed_timer == 0xA6 && ic.unk17 == 5 && ic.attack_box == &D_800FBF00);
    ic_step(0);
    ice_core_stomp(&ic);
    assert(ic.unk6 == 4);
    ic_step(1);
    ice_core_stomp(&ic);
    assert(ic.unk6 == 5 && ic.unk17 == 6);
    ic.ext.main_18.ice_pieces = 0x8001;
    IC.unk85 = 9;
    ic_step(2);
    ice_core_stomp(&ic);
    assert(IC.unk85 == 9 && ic.collision_data == D_80106B74 && ic.unk6 == 5);
    IC.unk80 = 0x41;
    ic_step(1);
    ice_core_stomp(&ic);
    assert(ic.unk5 == 6 && ic.unk6 == 0 && ic.y_speed == FIXED(2) && ic.gravity == FIXED(0.0625) && IC.unk80 == 0 && ic.unk17 == 2);
}
static void ic_build(void)
{
    ic_reset(1, 8, 0);
    ic_step(2);
    ice_core_build(&ic);
    assert(ic.unk6 == 0 && ic.attack_box == &D_800FBF04 && ic.hurt_box == &D_800FBF04);
    ic_step(1);
    ice_core_build(&ic);
    assert(ic.unk6 == 1 && ic.unk17 == 8);
    ic.ext.main_18.ice_pieces = 5;
    ic_step(3);
    ice_core_build(&ic);
    assert(ic.ext.main_18.ice_pieces == 0x83FF && shot_objects[0].unk2 == 1 && shot_objects[1].unk2 == 3 && shot_objects[7].unk2 == 9);
    assert(shot_objects[8].active == 0 && shot_objects[7].x_pos.val == (9 << 21) + 0x17B10000 && shot_objects[7].y_pos.val == 0x8200000);
    ic_step(4);
    ice_core_build(&ic);
    assert(ic.attack_box == &D_800FBF08 && ic.hurt_box == &D_800FBF08);
    ic_step(1);
    ice_core_build(&ic);
    assert(ic.unk6 == 2 && ic.attack_box == &D_800FBEF8 && ic.unk17 == 0xA && IC.unk85 == 3);
    ic.unk6 = 1;
    ic.ext.main_18.unk88 = 1;
    ic_step(1);
    ice_core_build(&ic);
    assert(ic.unk6 == 2 && ic.attack_box == &D_800FBEF4 && ic.unk17 == 9 && ic.unk15 == 0);
    *(u8*)&ic.unk7E = 0xFF;
    ic.hp = 5;
    IC.unk85 = 2;
    ic_step(0);
    ice_core_build(&ic);
    assert(ic.hp == 6 && IC.unk85 == 1 && ic.unk6 == 2);
    ic_step(3);
    ice_core_build(&ic);
    assert(ic.hp == 7 && IC.unk85 == 3 && ic.unk6 == 2);
    ic.invincibility_timer = -0x80;
    ic_step(1);
    ice_core_build(&ic);
    assert(ic.unk6 == 3 && ic.unk7C == 0x1E && ic.ext.main_18.unk88 == 0 && ic.unk17 == 0 && ic.attack_box == &D_800FBEF4 && ic.invincibility_timer == 0);
    ic.unk6 = 2;
    ic_step(1);
    ice_core_build(&ic);
    assert(ic.unk6 == 3 && ic.ext.main_18.unk88 == 1 && ic.unk17 == 0xB && ic.attack_box == &D_800FBEF8);
}
static void ic_build_wait(void)
{
    ic_reset(1, 8, 3);
    *(u8*)&ic.unk7E = 0xFF;
    ic.hp = 5;
    IC.unk85 = 2;
    ic.unk7C = 3;
    ice_core_build(&ic);
    assert(ic.hp == 6 && IC.unk85 == 1 && ic.unk7C == 2);
    ice_core_build(&ic);
    assert(ic.hp == 7 && IC.unk85 == 3 && ic.unk7C == 1);
    *(u8*)&ic.unk7E = 0;
    ic_step(0);
    ice_core_build(&ic);
    assert(ic.hp == 7 && ic.unk7C == 1 && ic.unk6 == 3);
    *(u8*)&ic.unk7E = 0xFF;
    ic.hp = 0x30;
    g_Player.script_state = 1;
    ic_step(1);
    ice_core_build(&ic);
    assert(ic.unk5 == 7 && *(u8*)&ic.unk7E == 0 && g_Player.script_state == 0 && IC.unk85 == 0);
    ic.unk5 = 8;
    ic.unk6 = 3;
    ic.unk7C = 1;
    *(u8*)&ic.unk7E = 1;
    g_Player.script_state = 1;
    ic_step(1);
    ice_core_build(&ic);
    assert(ic.unk5 == 7 && *(u8*)&ic.unk7E == 1 && g_Player.script_state == 1);
    ic.unk5 = 8;
    ic.unk6 = 3;
    ic.unk7C = 1;
    ic.ext.main_18.unk88 = 1;
    ic_step(1);
    ice_core_build(&ic);
    assert(ic.unk5 == 9 && ic.unk6 == 0 && ic.unk17 == 0x10);
}
static void ic_bounce(void)
{
    ic_reset(1, 9, 0);
    ice_core_bounce(&ic);
    assert(ic.unk6 == 1 && IC.unk80 == 0x80 && ic.terrain_box == &D_800FBF10 && ic.unk7C == 0xF0);
    assert(ic.x_speed == FIXED(-3.53554) && ic.y_speed == FIXED(-3.53554));
    ic.unk6 = 0;
    g_Player.x_pos.i.hi = 0x1900;
    cur_random = 1;
    ice_core_bounce(&ic);
    assert(ic.x_speed == FIXED(3.53554) && ic.y_speed == FIXED(3.53554) && ic.unk15 == PLAYER_FACING_RIGHT);
    ic.unk6 = 2;
    ic.unk7C = 2;
    ice_core_bounce(&ic);
    assert(ic.unk7C == 1 && ic.unk5 == 9);
    ice_core_bounce(&ic);
    assert(ic.unk5 == 10 && ic.unk6 == 0);
    ic.unk5 = 9;
    ic.unk6 = 3;
    ic_step(2);
    ice_core_bounce(&ic);
    assert(ic.attack_box == &D_800FBF04 && ic.unk6 == 3);
    IC.unk86 = 2;
    ic_step(1);
    ice_core_bounce(&ic);
    assert(ic.terrain_box == &D_800FBF0C && IC.unk86 == 0 && ic.unk5 == 8 && ic.unk6 == 0);
}
static void ic_bounce_move(void)
{
    static const s16 spots[][3] = { { 0x1840, 0x870, 1 }, { 0x1840, 0x848, 0 }, { 0x1840, 0x890, 0 }, { 0x17D0, 0x870, 0 }, { 0x18C0, 0x870, 0 } };
    u32 i;
    ic_reset(1, 9, 1);
    ic.x_pos.i.lo = ic.y_pos.i.lo = 0x8000;
    ic.unk7C = 2;
    ic.x_speed = -1;
    ic.y_speed = -1;
    ic.collision_flags = 2 | 8;
    ice_core_bounce(&ic);
    assert(ic.x_speed == 1 && ic.y_speed == 1 && ic.unk15 == PLAYER_FACING_RIGHT && ic.unk7C == 1 && misc_objects[3].active == 0x41);
    ic.collision_flags = 1 | 4;
    ic.unk7C = 5;
    ice_core_bounce(&ic);
    assert(ic.x_speed == -1 && ic.y_speed == -1 && ic.unk15 == 0);
    ic.collision_flags = 0;
    ice_core_bounce(&ic);
    assert(ic.x_speed == -1 && ic.y_speed == -1 && ic.unk6 == 1);
    ic.x_speed = ic.y_speed = 1;
    ice_core_bounce(&ic);
    assert(ic.x_speed == 1 && ic.y_speed == 1);
    for (i = 0; i < COUNT(spots); i++) {
        ic.unk6 = 1;
        ic.unk7C = 1;
        ic.x_speed = ic.y_speed = 0;
        ic.x_pos.i.hi = spots[i][0];
        ic.y_pos.i.hi = spots[i][1];
        ice_core_bounce(&ic);
        assert(ic.unk6 == (spots[i][2] ? 2 : 1) && ic.unk7C == (spots[i][2] ? 0x30 : 1));
    }
    ic.unk6 = 1;
    IC.unk86 = 2;
    IC.unk87 = 0;
    ice_core_bounce(&ic);
    assert(ic.unk6 == 1);
    IC.unk87 = 1;
    ice_core_bounce(&ic);
    assert(ic.unk6 == 3 && ic.unk17 == 0xF);
}
static void ic_spray_intro(void)
{
    ic_reset(1, 10, 1);
    ic_step(0);
    ice_core_spray(&ic);
    assert(ic.unk6 == 1);
    ic_step(1);
    ice_core_spray(&ic);
    assert(ic.unk6 == 2 && ic.unk7C == 0x30);
    ic.unk7C = 2;
    ice_core_spray(&ic);
    assert(ic.unk7C == 1 && ic.unk5 == 10);
    ice_core_spray(&ic);
    assert(ic.unk5 == 9 && ic.unk6 == 0);
    ic.unk5 = 11;
    ic.unk6 = 1;
    g_Player.script_state = 1;
    ice_core_intro(&ic);
    assert(ic.unk6 == 1);
    g_Player.script_state = -1;
    ice_core_intro(&ic);
    assert(ic.unk6 == 2);
    ic.unk7C = 2;
    ic.y_speed = FIXED(1);
    ice_core_intro(&ic);
    assert(ic.unk6 == 2 && ic.y_pos.i.hi == 0x86F);
    ice_core_intro(&ic);
    assert(ic.unk6 == 3 && ic.y_speed == 0 && ic.gravity == FIXED(0.0078125) && ic.unk16 == VISUAL_SATURN_LAYER(5));
}
static void ic_intro_slow_start(void)
{
    ic_reset(1, 11, 3);
    ic.gravity = FIXED(0.0078125);
    ic.y_speed = 0x400;
    ice_core_intro(&ic);
    assert(ic.unk6 == 3 && ic.y_speed == 0x200);
    ic.y_speed = 0x200 - FIXED(0.75);
    ice_core_intro(&ic);
    assert(ic.unk6 == 4 && ic.y_speed == -FIXED(0.75) && ic.gravity == -FIXED(0.015625) && ic.unk7C == 0x64);
    ic.unk7C = 2;
    ic.gravity = 0;
    ic.y_speed = 0;
    IC.unk82 = 1;
    ice_core_intro(&ic);
    assert(ic.unk7C == 1 && ic.unk5 == 11);
    engine_obj.enable_boss = 0;
    ice_core_intro(&ic);
    assert(ic.unk5 == 8 && ic.unk6 == 0 && IC.unk82 == 0 && engine_obj.enable_boss == 1 && engine_obj.unk25 == 2 && engine_obj.boss_ptr == &ic);
    ic.unk5 = 6;
    ic.y_speed = 0x1000;
    ice_core_fall(&ic);
    assert(ic.unk5 == 6);
    ic.y_speed = 0;
    ice_core_fall(&ic);
    assert(ic.unk5 == 2 && ic.terrain_box == &D_800FBF0C);
}
static void ic_float(void)
{
    static const s16 floats[][4] = { { 0x1000, 0, 0x891, 1 }, { 0x1000, 0, 0x890, 0 }, { 0x1000, 1, 0x8B0, 0 }, { 0x1000, 1, 0x8B1, 1 }, { -0x1000, 1, 0x8B0, 0 }, { -0x1000, 1, 0x8AF, 1 }, { -0x1000, 0, 0x88F, 1 }, { -0x1000, 0, 0x890, 0 } };
    u32 i;
    for (i = 0; i < COUNT(floats); i++) {
        ic_reset(1, 7, 0);
        ic.gravity = floats[i][0];
        IC.unk84 = floats[i][1];
        ic.y_pos.i.hi = floats[i][2];
        ice_core_float(&ic);
        assert(ic.unk5 == (floats[i][3] ? 2 : 7) && ic.terrain_box == (floats[i][3] ? &D_800FBF0C : NULL));
    }
}
static void ic_pick(void)
{
    ic_reset(1, 2, 3);
    IC.unk80 = 0x41;
    cur_random = 2;
    ice_core_pick_attack(&ic);
    assert(IC.unk80 == 0xC1 && ic.unk5 == 3 && ic.unk6 == 0 && ic.terrain_box == &D_800FBF0C);
    IC.unk80 = 0x41;
    cur_random = 0;
    *(u8*)&ic.unk7E = 0;
    ice_core_pick_attack(&ic);
    assert(ic.unk5 == 4 && *(u8*)&ic.unk7E == 1);
    IC.unk80 = 0x44;
    ice_core_pick_attack(&ic);
    assert(ic.unk5 == 5 && ic.unk17 == 4 && *(u8*)&ic.unk7E == 0);
}
static void ic_rebuild(void)
{
    static const u8 checks[][3] = { { 10, 1, 0 }, { 5, 1, 1 }, { 5, 0, 0 } };
    u32 i;
    for (i = 0; i < COUNT(checks); i++) {
        ic_reset(1, 1, 3);
        ic.ext.main_18.saved_unk5 = 2;
        ic.hp = checks[i][0];
        IC.unk85 = 10;
        IC.unk87 = checks[i][1];
        IC.unk82 = 1;
        ic.ext.main_18.unk88 = checks[i][2];
        ice_core_update(&ic);
        assert(ic.unk5 == 2 && ic.unk6 == 3 && IC.unk82 == 1 && IC.unk85 == 10 && ic.unk17 == 0);
    }
}
static void ic_shed(void)
{
    ic_reset(1, 2, 3);
    ic.hp = 5;
    IC.unk85 = 10;
    ic.ext.main_18.shed_timer = 0x22;
    ic.ext.main_18.ice_pieces = 4;
    ice_core_shed_ice(&ic);
    assert(ic.ext.main_18.shed_timer == 0x21 && ic.ext.main_18.ice_pieces == 4);
    cur_random = 0x100;
    ice_core_shed_ice(&ic);
    assert(ic.ext.main_18.ice_pieces == 0 && ic.ext.main_18.shed_timer == 0xC && IC.unk85 == 10 && cur_random == 0x90C);
    ic.ext.main_18.shed_timer = 0x21;
    ic.ext.main_18.ice_pieces = 0x8200;
    ice_core_shed_ice(&ic);
    assert(ic.ext.main_18.ice_pieces == 0x8000 && IC.unk85 == 5 && ic.ext.main_18.shed_timer == 0xC);
}
static void ic_run_hits(void)
{
    struct MainObj* current = SP_CUR_MAIN_OBJ;
    ic_reset(1, 1, 0);
    SP_CUR_MAIN_OBJ = &ic;
    ic.hp = 20;
    ic.ext.main_18.saved_unk5 = 1;
    ic.collision_data = ic_damage;
    ic.hurt_box = &ic_box;
    ic.bg_offset = -1;
    weapon_objects[0].active = 1;
    weapon_objects[0].unk50 = &ic_box;
    weapon_objects[0].bg_offset = -1;
    weapon_objects[0].x_pos = ic.x_pos;
    weapon_objects[0].y_pos = ic.y_pos;
    ic_damage[1] = 1;
    ic_damage[23 * 2 + 1] = 1;
    ice_core_update(&ic);
    assert(ic.hp == 19 && ic.invincibility_timer == 6 && ic.unk42 == 0x8000 && IC.unk87 == 1 && IC.unk80 == 0x41 && IC.unk83 == 0);
    ic.invincibility_timer = 0;
    IC.unk80 = 0x80;
    IC.unk81 = 1;
    weapon_objects[0].id = 23;
    engine_obj.cur_character = CHARACTER_ZERO;
    ice_core_update(&ic);
    assert(ic.hp == 18 && ic.invincibility_timer == 1 && IC.unk83 == 5 && IC.unk80 == 0x80);
    ic.invincibility_timer = 0;
    ic.hp = 1;
    ice_core_update(&ic);
    SP_CUR_MAIN_OBJ = current;
    assert(ic.state == 2 && ic.hp == 0 && ic.unk7C == 4 && ic.unk7E == 8 && ic.terrain_box == NULL && SPIKE_IMMUNE(g_Player) == 1);
    assert(g_Player.invincibility_timer == 0x7F && ic.ext.main_18.ice_pieces == 0 && misc_objects[3].active == 0x41);
}
static void ic_death_sunk(void)
{
    ic_reset(2, 0, 0);
    engine_obj.stage = 2, engine_obj.substage = 0, engine_obj.enable_boss = 1, engine_obj.boss_ptr = &ic;
    background_objects[0].x_pos.i.hi = 0x1800, background_objects[0].y_pos.i.hi = 0x800;
    tile_writes_begin();
    tile_writes_expect(0x17, 0, 0, 1);
    ic.y_pos.i.hi = 0x930;
    ice_core_death_sink(&ic);
    tile_writes_end();
    assert(tile_write_count == 21);
    assert(ic.state == 3 && ic.y_pos.i.hi == 0x931 && engine_obj.enable_boss == 0 && engine_obj.boss_ptr == NULL);
    engine_obj.stage = 0;
}
static void (*const ic_cases[])(void) = {
    ic_death,
    ic_drift,
    ic_bob,
    ic_charge,
    ic_charge_walls,
    ic_stomp,
    ic_build,
    ic_build_wait,
    ic_bounce,
    ic_bounce_move,
    ic_spray_intro,
    ic_intro_slow_start,
    ic_float,
    ic_pick,
    ic_rebuild,
    ic_shed,
    ic_run_hits,
    ic_death_sunk,
};
static u32 ic_run(u32 row)
{
    ic_cases[row]();
    return 1;
}
#undef IC

const struct CTestGroup c_test_groups[] = {
    { "ice_core_hit", NULL, ice_core_hit_cases_expected, COUNT(ice_core_hit_cases_expected), ice_core_hit_run },
    { "ice_core_spray_pool", NULL, ice_core_spray_pool_cases_expected, COUNT(ice_core_spray_pool_cases_expected), spray_case },
    { "func_80050874", 0, 0, 2, test_func_80050874 },
    { "func_800517D0", 0, 0, 4, test_func_800517D0 },
    { "func_80052218", 0, 0, 1, test_func_80052218 },
    { "func_800527F0", 0, 0, 4, test_func_800527F0 },
    { "ice_core_bob_move", 0, 0, 2, test_ice_core_bob_move },
    { "ice_core_build_grow", 0, 0, 3, test_ice_core_build_grow },
    { "ice_core_charge_run", 0, 0, 4, test_ice_core_charge_run },
    { "ice_core_charge_slide_1", 0, 0, 4, test_ice_core_charge_slide_1 },
    { "ice_core_check_rebuild_1", 0, 0, 2, test_ice_core_check_rebuild_1 },
    { "ice_core_float", 0, 0, 2, test_ice_core_float },
    { "ice_core_pick_attack", 0, 0, 2, test_ice_core_pick_attack },
    { "ice_core_shed_ice", 0, 0, 2, test_ice_core_shed_ice },
    { "ice_core_stomp_drop", 0, 0, 2, test_ice_core_stomp_drop },
    { "ice_core_stomp_recover", 0, 0, 1, test_ice_core_stomp_recover },
    { "ice_core_stomp_rise", 0, 0, 2, test_ice_core_stomp_rise },
    { "saber_meter_bonus_and_followup_with_real_damage_table", NULL, NULL, 64, saber_meter },
    { "ice_core_state_steps", NULL, NULL, COUNT(ic_cases), ic_run },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(ice_core_hit_cases_expected) + COUNT(ice_core_spray_pool_cases_expected) + 2 + 4 + 1 + 4 + 2 + 3 + 4 + 4 + 2 + 2 + 2 + 2 + 2 + 1 + 2 + 64 + COUNT(ic_cases);
