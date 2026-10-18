#include "test_runtime.h"
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
    g_Player.spike_immune = 1;
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
    assert(g_Player.spike_immune == 1 && engine_obj.cur_character == input->character);
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

#define CASE(name)                              \
    static u32 ice_core_hit_##name##_case(void) \
    {                                           \
        return ice_core_hit_run(name);          \
    }
CASE(HIT_BONUS_2)
CASE(HIT_BONUS_5)
CASE(HIT_BONUS_10)
CASE(HIT_NO_BONUS)
CASE(INVINCIBLE_TICK)
CASE(INVINCIBLE_END)
CASE(NO_HIT)
CASE(DEFEATED)
#define ENTRY(name) ice_core_hit_##name##_case,
static const CTestCase ice_core_hit_cases[]
    = {
          ENTRY(HIT_BONUS_2) ENTRY(HIT_BONUS_5) ENTRY(HIT_BONUS_10) ENTRY(HIT_NO_BONUS) ENTRY(INVINCIBLE_TICK) ENTRY(INVINCIBLE_END)
              ENTRY(NO_HIT) ENTRY(DEFEATED)
      };
static const u32 ice_core_hit_cases_expected[] = { 0x41098263u, 0x800C8563u, 0x80118263u, 0x80078573u, 0x8007857Eu, 0x8007047Eu, 0x8007047Eu, 0x8007847Eu };
#undef CASE
#undef ENTRY

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
    obj.unk15 = 0x40;
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
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(D_8013E198[2] == -1);
    return (u8)obj.unk6 | ((u32)obj.ext.main_18.state.runtime.unk86 << 8) | (allocated << 16);
}
#define CASE(m)                                    \
    static u32 ice_core_spray_pool_spray_##m(void) \
    {                                              \
        return spray_case(m);                      \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
#define ENTRY(m) ice_core_spray_pool_spray_##m,
static const CTestCase ice_core_spray_pool_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) };
static const u32 ice_core_spray_pool_cases_expected[] = { 0x101u, 0x20101u, 0x40201u, 0x901u };
#undef CASE
#undef ENTRY

struct func_80050874_case {
    u32 state, weapon;
    const u8* box;
    u32 damage, damage_flags, weapon_unk80;
    s32 unk63;
    u32 unk65, unk87;
    u32 expected[5];
};
static const struct func_80050874_case func_80050874_cases[] = {
    { 1, 1, (const u8*)lightning_web_shot_box, 255, 0, 6488163, -1, 1, 0, { 0xAu, 0u, 0u, 0u, 1u } },
    { 2, 0, (const u8*)lemon_hit_box, 0, 1, 0, 0, 0, 7, { 0xAu, 0u, 0u, 7u, 2u } },
};
static struct WeaponObj func_80050874_weapons_expected[16];
static struct VisualObj func_80050874_visuals_expected[32];
static u32 test_func_80050874(u32 row)
{
    const struct func_80050874_case* c = &func_80050874_cases[row];
    u32 observed_values[5];
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
    g_Player.spike_immune = 1;
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
    func_80050874_weapons_expected[0].unk80.word = c->weapon_unk80;
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
    observed_values[0] = (u32)obj.hp;
    observed_values[1] = (u32)obj.invincibility_timer;
    observed_values[2] = (u32)obj.ext.main_18.state.runtime.unk83;
    observed_values[3] = (u32)obj.ext.main_18.state.runtime.unk87;
    observed_values[4] = (u32)obj.state;
    return c_test_observe(0, row, observed_values, c->expected, 5);
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
    u8 pools_full;
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
    pools_full = 1;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            item_objects[slot].active = pools_full ? 1 : 0;
    }
    item_objects[0].id = 8;
    item_objects[31].id = 8;
    item_objects[0].active = 0x41;
    item_objects[31].active = 0x41;
    memcpy(items_expected, item_objects, sizeof(items_expected));
    pools_full = 0;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            items_expected[slot].active = pools_full ? 1 : 0;
    }
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
    player_expected.spike_immune = 1;
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
    u32 expected[4];
};
static const struct func_800527F0_case func_800527F0_cases[] = {
    { 2192, 0, 4096, { 7u, 0u, 0x1000u, 0x8905678u } },
    { 2193, 0, -4096, { 7u, 0u, 0xFFFFF000u, 0x8915678u } },
    { 2224, 1, 4096, { 7u, 0u, 0x1000u, 0x8B05678u } },
    { 2225, 1, -4096, { 7u, 0u, 0xFFFFF000u, 0x8B15678u } },
};
static u32 test_func_800527F0(u32 row)
{
    const struct func_800527F0_case* c = &func_800527F0_cases[row];
    u32 observed_values[4];
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
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.gravity;
    observed_values[3] = (u32)obj.y_pos.val;
    return c_test_observe(0, row, observed_values, c->expected, 4);
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
    u32 expected[4];
};
static const struct ice_core_build_grow_case ice_core_build_grow_cases[] = {
    { 255, 48, 48, 3, { 0x30u, 3u, 0x6010009u, 2u } },
    { 255, 47, 48, 2, { 0x30u, 2u, 0x6010009u, 2u } },
    { 0, 47, 47, 3, { 0x2Fu, 3u, 0x6010009u, 2u } },
};
static u32 test_ice_core_build_grow(u32 row)
{
    const struct ice_core_build_grow_case* c = &ice_core_build_grow_cases[row];
    u32 observed_values[4];
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
    obj.unk7E = c->unk7E;
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
    observed_values[0] = (u32)obj.hp;
    observed_values[1] = (u32)obj.ext.main_18.state.runtime.unk85;
    observed_values[2] = (u32)obj.animation_step.packed;
    observed_values[3] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

struct ice_core_charge_run_case {
    u32 unk15, x_speed, unk83, x_pos, reset_animation, unk6;
    u32 expected[4];
};
static const struct ice_core_charge_run_case ice_core_charge_run_cases[] = {
    { 0, -65536, 9, 6492724, 0, 4, { 4u, 0x10001u, 0x631234u, 0x635678u } },
    { 0, -65536, 10, 6492724, 1, 5, { 5u, 0xB010004u, 0x631234u, 0x635678u } },
    { 64, 65536, 9, 6623796, 0, 4, { 4u, 0x10001u, 0x651234u, 0x635678u } },
    { 64, 65536, 10, 6623796, 1, 5, { 5u, 0xB010004u, 0x651234u, 0x635678u } },
};
static u32 test_ice_core_charge_run(u32 row)
{
    const struct ice_core_charge_run_case* c = &ice_core_charge_run_cases[row];
    u32 observed_values[4];
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
    obj.unk15 = c->unk15;
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
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.animation_step.packed;
    observed_values[2] = (u32)obj.x_pos.val;
    observed_values[3] = (u32)obj.y_pos.val;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

static const u32 ice_core_charge_slide_0_expected[] = { 3u, 0x1Cu, 0u, 0u };
static u32 test_ice_core_charge_slide_0(u32 row)
{
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk7C = 1;
    ice_core_charge_slide(&obj);
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.unk7C;
    observed_values[2] = (u32)obj.x_accel;
    observed_values[3] = (u32)obj.x_speed;
    return c_test_observe(0, row, observed_values, ice_core_charge_slide_0_expected, 4);
}

struct ice_core_charge_slide_1_case {
    u32 obj_unk7C, unk15, collision_flags, obj_x_speed, x_pos, y_pos, expected_x_speed, x_accel, y_speed;
    u32 expected_unk7C, unk6;
    u32 expected[5];
};
static const struct ice_core_charge_slide_1_case ice_core_charge_slide_1_cases[] = {
    { 2, 0, 0, 65536, 6623796, 6510200, 0, 0, 61440, 1, 2, { 0u, 0u, 0x651234u, 0x635678u, 2u } },
    { 2, 64, 0, -65536, 6492724, 6510200, 0, 0, 61440, 1, 2, { 0u, 0u, 0x631234u, 0x635678u, 2u } },
    { 2, 0, 3, 65536, 6558260, 6575736, 65536, 65536, 65536, 1, 2, { 0x10000u, 0x10000u, 0x641234u, 0x645678u, 2u } },
    { 1, 64, 0, -65536, 6492724, 6510200, 0, 0, 61440, 28, 3, { 0u, 0u, 0x631234u, 0x635678u, 3u } },
};
static u32 test_ice_core_charge_slide_1(u32 row)
{
    const struct ice_core_charge_slide_1_case* c = &ice_core_charge_slide_1_cases[row];
    u32 observed_values[5];
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
    obj.unk15 = c->unk15;
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
    observed_values[0] = (u32)obj.x_speed;
    observed_values[1] = (u32)obj.x_accel;
    observed_values[2] = (u32)obj.x_pos.val;
    observed_values[3] = (u32)obj.y_pos.val;
    observed_values[4] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

static const u32 ice_core_check_rebuild_0_expected[] = { 0u, 0u, 8u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_ice_core_check_rebuild_0(u32 row)
{
    u32 observed_values[9];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.hp = 6;
    obj.ext.main_18.state.runtime.unk85 = 8;
    obj.ext.main_18.state.runtime.unk87 = 255;
    obj.ext.main_18.unk88 = 255;
    ice_core_check_rebuild(&obj);
    observed_values[0] = (u32)obj.ext.main_18.state.runtime.unk82;
    observed_values[1] = (u32)obj.ext.main_18.state.runtime.unk84;
    observed_values[2] = (u32)obj.ext.main_18.state.runtime.unk85;
    observed_values[3] = (u32)obj.gravity;
    observed_values[4] = (u32)obj.unk5;
    observed_values[5] = (u32)obj.unk6;
    observed_values[6] = (u32)obj.x_accel;
    observed_values[7] = (u32)obj.x_speed;
    observed_values[8] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, ice_core_check_rebuild_0_expected, 9);
}

struct ice_core_check_rebuild_1_case {
    u32 unk88, rebuild;
    u32 expected[4];
};
static const struct ice_core_check_rebuild_1_case ice_core_check_rebuild_1_cases[] = {
    { 1, 0, { 7u, 1u, 1u, 0x10002u } },
    { 0, 1, { 8u, 0u, 0u, 0x10004u } },
};
static u32 test_ice_core_check_rebuild_1(u32 row)
{
    const struct ice_core_check_rebuild_1_case* c = &ice_core_check_rebuild_1_cases[row];
    u32 observed_values[4];
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
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.ext.main_18.state.runtime.unk84;
    observed_values[3] = (u32)obj.animation_step.packed;
    return c_test_observe(0, row, observed_values, c->expected, 4);
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
    u32 expected[4];
};
static const struct ice_core_pick_attack_case ice_core_pick_attack_cases[] = {
    { 2, { 7u, 1u, 0xC3u, 2u } },
    { 255, { 7u, 1u, 0xC3u, 0xFFu } },
};
static u32 test_ice_core_pick_attack(u32 row)
{
    const struct ice_core_pick_attack_case* c = &ice_core_pick_attack_cases[row];
    u32 observed_values[4];
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
    obj.unk7E = c->unk7E;
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
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.ext.main_18.state.runtime.unk80;
    observed_values[3] = (u32)obj.unk7E;
    return c_test_observe(0, row, observed_values, c->expected, 4);
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
    u32 expected[5];
};
static const struct ice_core_stomp_drop_case ice_core_stomp_drop_cases[] = {
    { 2, 1, 1, { 1u, 1u, 0xD010205u, 0x651234u, 0x6C5678u } },
    { 1, 0, 0, { 0u, 0u, 0xD010205u, 0x651234u, 0x6C5678u } },
};
static u32 test_ice_core_stomp_drop(u32 row)
{
    const struct ice_core_stomp_drop_case* c = &ice_core_stomp_drop_cases[row];
    u32 observed_values[5];
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
    observed_values[0] = (u32)obj.unk7C;
    observed_values[1] = (u32)obj.ext.main_18.state.runtime.unk82;
    observed_values[2] = (u32)obj.animation_step.packed;
    observed_values[3] = (u32)obj.x_pos.val;
    observed_values[4] = (u32)obj.y_pos.val;
    return c_test_observe(0, row, observed_values, c->expected, 5);
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

const struct CTestGroup c_test_groups[] = {
    { "ice_core_hit", ice_core_hit_cases, ice_core_hit_cases_expected, COUNT(ice_core_hit_cases), 0 },
    { "ice_core_spray_pool", ice_core_spray_pool_cases, ice_core_spray_pool_cases_expected, COUNT(ice_core_spray_pool_cases), 0 },
    { "func_80050874", 0, 0, 2, test_func_80050874 },
    { "func_800517D0", 0, 0, 4, test_func_800517D0 },
    { "func_80052218", 0, 0, 1, test_func_80052218 },
    { "func_800527F0", 0, 0, 4, test_func_800527F0 },
    { "ice_core_bob_move", 0, 0, 2, test_ice_core_bob_move },
    { "ice_core_build_grow", 0, 0, 3, test_ice_core_build_grow },
    { "ice_core_charge_run", 0, 0, 4, test_ice_core_charge_run },
    { "ice_core_charge_slide_0", 0, 0, 1, test_ice_core_charge_slide_0 },
    { "ice_core_charge_slide_1", 0, 0, 4, test_ice_core_charge_slide_1 },
    { "ice_core_check_rebuild_0", 0, 0, 1, test_ice_core_check_rebuild_0 },
    { "ice_core_check_rebuild_1", 0, 0, 2, test_ice_core_check_rebuild_1 },
    { "ice_core_float", 0, 0, 2, test_ice_core_float },
    { "ice_core_pick_attack", 0, 0, 2, test_ice_core_pick_attack },
    { "ice_core_shed_ice", 0, 0, 2, test_ice_core_shed_ice },
    { "ice_core_stomp_drop", 0, 0, 2, test_ice_core_stomp_drop },
    { "ice_core_stomp_recover", 0, 0, 1, test_ice_core_stomp_recover },
    { "ice_core_stomp_rise", 0, 0, 2, test_ice_core_stomp_rise },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(ice_core_hit_cases) + COUNT(ice_core_spray_pool_cases) + 2 + 4 + 1 + 4 + 2 + 3 + 4 + 1 + 4 + 1 + 2 + 2 + 2 + 2 + 2 + 1 + 2;
