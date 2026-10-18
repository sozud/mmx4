#include "test_runtime.h"
#include "main/mains/main_38_train_cannon.h"
#include "main/55C4.h"

static u32 signed_default(void)
{
    struct MainObj obj, before;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 38;
    obj.state = 1;
    obj.unk5 = 0x27;
    obj.unk6 = 0x28;
    obj.ext.main_38.unk84 = 0xFFFFFFFFu;
    obj.unk7E = 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_step.fields.duration = 2;
    before = obj;
    train_cannon_idle_pick(&obj);
    before.animation_step.fields.duration = 1;
    before.unk7E = 0;
    before.unk6 = 0;
    before.ext.main_38.unk84 = 0;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    actual = obj.ext.main_38.unk84 | ((u32)(u8)obj.unk5 << 16);
    return actual;
}
static const CTestCase train_cannon_signed_default_cases[] = { signed_default };
static const u32 train_cannon_signed_default_cases_expected[] = { 0x270000u };

static const u32 train_cannon_fire_blast_0_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_train_cannon_fire_blast_0(u32 row)
{
    u32 observed_values[8];
    struct PlayerObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_0_full ? 1 : 0;
    }
    train_cannon_fire_blast(&obj);
    observed_values[0] = (u32)shot_objects[0].active;
    observed_values[1] = (u32)shot_objects[0].bg_offset;
    observed_values[2] = (u32)shot_objects[0].id;
    observed_values[3] = (u32)shot_objects[0].unk15;
    observed_values[4] = (u32)shot_objects[0].unk16;
    observed_values[5] = (u32)shot_objects[0].unk2;
    observed_values[6] = (u32)shot_objects[0].unk40;
    observed_values[7] = (u32)shot_objects[0].unk42;
    return c_test_observe(0, row, observed_values, train_cannon_fire_blast_0_expected, 8);
}

struct train_cannon_fire_blast_1_case {
    u32 free_last;
    u32 expected[8];
};
static const struct train_cannon_fire_blast_1_case train_cannon_fire_blast_1_cases[] = {
    { 0, { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 1, { 0x41u, 0x14u, 0u, 1u, 0x1234u, 0x40u, 0x56u, 0u } },
};
static u32 test_train_cannon_fire_blast_1(u32 row)
{
    const struct train_cannon_fire_blast_1_case* c = &train_cannon_fire_blast_1_cases[row];
    u32 observed_values[8];
    struct PlayerObj obj, object_before;
    struct PlayerObj player_before;
    struct ShotObj expected[32];
    u8 pools_full, free_last;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 38;
    obj.unk42 = 0x1234;
    obj.unk40 = 0x56;
    obj.unk15 = 0x40;
    obj.animation_table = (const u8* const*)train_cannon_animations;
    obj.x_pos.val = 52433460;
    obj.y_pos.val = 6575736;
    obj.unk2 = 1;
    pools_full = 1;
    free_last = c->free_last;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pools_full ? 1 : 0;
    }
    if (free_last) {
        shot_objects[31].active = 0;
    }
    memcpy(expected, shot_objects, sizeof(expected));
    if (free_last) {
        expected[31].active = 0x41;
    }
    if (free_last) {
        expected[31].id = 20;
    }
    if (free_last) {
        expected[31].unk2 = 0;
    }
    if (free_last) {
        expected[31].unk7C = WEAPON_OBJECT(&obj);
    }
    if (free_last) {
        expected[31].unk42 = obj.unk42;
    }
    if (free_last) {
        expected[31].animation_table = (const u8* const*)train_cannon_animations;
    }
    if (free_last) {
        expected[31].unk3C = (void*)obj.unk3C;
    }
    if (free_last) {
        expected[31].unk40 = obj.unk40;
    }
    if (free_last) {
        expected[31].unk15 = obj.unk15;
    }
    if (free_last) {
        expected[31].bg_offset = obj.bg_offset;
    }
    if (free_last) {
        expected[31].unk16 = 1;
    }
    object_before = obj;
    player_before = g_Player;
    train_cannon_fire_blast(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&obj, &object_before, sizeof(obj));
    c_test_same_words(shot_objects, expected, sizeof(shot_objects));
    observed_values[0] = (u32)shot_objects[31].active;
    observed_values[1] = (u32)shot_objects[31].id;
    observed_values[2] = (u32)shot_objects[31].unk2;
    observed_values[3] = (u32)shot_objects[31].unk16;
    observed_values[4] = (u32)shot_objects[31].unk42;
    observed_values[5] = (u32)shot_objects[31].unk15;
    observed_values[6] = (u32)shot_objects[31].unk40;
    observed_values[7] = (u32)shot_objects[31].bg_offset;
    return c_test_observe(0, row, observed_values, c->expected, 8);
}

static const u32 train_cannon_fire_volley_0_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_train_cannon_fire_volley_0(u32 row)
{
    u32 observed_values[8];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_0_full ? 1 : 0;
    }
    train_cannon_fire_volley(&obj);
    observed_values[0] = (u32)shot_objects[0].active;
    observed_values[1] = (u32)shot_objects[0].bg_offset;
    observed_values[2] = (u32)shot_objects[0].id;
    observed_values[3] = (u32)shot_objects[0].unk15;
    observed_values[4] = (u32)shot_objects[0].unk16;
    observed_values[5] = (u32)shot_objects[0].unk2;
    observed_values[6] = (u32)shot_objects[0].unk40;
    observed_values[7] = (u32)shot_objects[0].unk42;
    return c_test_observe(0, row, observed_values, train_cannon_fire_volley_0_expected, 8);
}

struct train_cannon_fire_volley_1_case {
    u32 free_last;
    u32 expected[8];
};
static const struct train_cannon_fire_volley_1_case train_cannon_fire_volley_1_cases[] = {
    { 0, { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 1, { 0x41u, 0x15u, 0u, 4u, 0x1234u, 0x40u, 0x56u, 0u } },
};
static u32 test_train_cannon_fire_volley_1(u32 row)
{
    const struct train_cannon_fire_volley_1_case* c = &train_cannon_fire_volley_1_cases[row];
    u32 observed_values[8];
    struct MainObj obj, object_before;
    struct PlayerObj player_before;
    struct ShotObj expected[32];
    u8 pools_full, free_last;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 38;
    obj.unk42 = 0x1234;
    obj.unk40 = 0x56;
    obj.unk15 = 0x40;
    obj.animation_table = (const u8* const*)train_cannon_animations;
    obj.x_pos.val = 52433460;
    obj.y_pos.val = 6575736;
    obj.unk2 = 0;
    pools_full = 1;
    free_last = c->free_last;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pools_full ? 1 : 0;
    }
    if (free_last) {
        shot_objects[31].active = 0;
    }
    memcpy(expected, shot_objects, sizeof(expected));
    if (free_last) {
        expected[31].active = 0x41;
    }
    if (free_last) {
        expected[31].id = 21;
    }
    if (free_last) {
        expected[31].unk2 = 0;
    }
    if (free_last) {
        expected[31].unk7C = WEAPON_OBJECT(&obj);
    }
    if (free_last) {
        expected[31].unk42 = obj.unk42;
    }
    if (free_last) {
        expected[31].animation_table = (const u8* const*)train_cannon_animations;
    }
    if (free_last) {
        expected[31].unk3C = (void*)obj.sprite_frames;
    }
    if (free_last) {
        expected[31].unk40 = obj.unk40;
    }
    if (free_last) {
        expected[31].unk15 = obj.unk15;
    }
    if (free_last) {
        expected[31].bg_offset = obj.bg_offset;
    }
    if (free_last) {
        expected[31].unk16 = 4;
    }
    object_before = obj;
    player_before = g_Player;
    train_cannon_fire_volley(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&obj, &object_before, sizeof(obj));
    c_test_same_words(shot_objects, expected, sizeof(shot_objects));
    observed_values[0] = (u32)shot_objects[31].active;
    observed_values[1] = (u32)shot_objects[31].id;
    observed_values[2] = (u32)shot_objects[31].unk2;
    observed_values[3] = (u32)shot_objects[31].unk16;
    observed_values[4] = (u32)shot_objects[31].unk42;
    observed_values[5] = (u32)shot_objects[31].unk15;
    observed_values[6] = (u32)shot_objects[31].unk40;
    observed_values[7] = (u32)shot_objects[31].bg_offset;
    return c_test_observe(0, row, observed_values, c->expected, 8);
}

static const u32 train_cannon_idle_pick_expected[] = { 0x100u, 0u, 0u, 0u };
static u32 test_train_cannon_idle_pick(u32 row)
{
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk7E = 1;
    obj.ext.main_38.unk84 = 255;
    train_cannon_idle_pick(&obj);
    observed_values[0] = (u32)obj.ext.main_38.unk84;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk7E;
    return c_test_observe(0, row, observed_values, train_cannon_idle_pick_expected, 4);
}

struct train_cannon_main_case {
    u32 g_Player_x_pos, obj_x_pos, unk5, saved_unk5;
    u32 expected[16];
};
static const struct train_cannon_main_case train_cannon_main_cases[] = {
    { 65536000, 13111860, 1, 0, { 1u, 0u, 1u, 0u, 1u, 1u, 7u, 3u, 0u, 0x1234u, 0x12u, 0xC81234u, 0x645678u, 0xC81234u, 0x645678u, 1u } },
    { 65536000, 52433460, 4, 2, { 1u, 4u, 1u, 4u, 1u, 0u, 6u, 3u, 0u, 0x1234u, 0x12u, 0x3201234u, 0x645678u, 0x3201234u, 0x645678u, 0xC010001u } },
    { 45879860, 52433460, 2, 4, { 1u, 2u, 1u, 2u, 1u, 0u, 7u, 2u, 0u, 0x1234u, 0x12u, 0x3201234u, 0x645678u, 0x3201234u, 0x645678u, 1u } },
};
static u32 test_train_cannon_main(u32 row)
{
    const struct train_cannon_main_case* c = &train_cannon_main_cases[row];
    u32 observed_values[16];
    struct MainObj obj;
    struct PlayerObj player_before, entity_before;
    struct EngineObj engine_before;
    struct BackgroundObj cameras_before[3];
    struct WeaponObj weapons_before[16];
    u8 pools_full;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 38;
    obj.unk42 = 0x1234;
    obj.unk40 = 0x56;
    obj.unk15 = 0x40;
    obj.animation_table = (const u8* const*)train_cannon_animations;
    obj.x_pos.val = 52433460;
    obj.y_pos.val = 6575736;
    g_Entity.active = 0;
    qux_object.active = 0;
    g_Player.bg_offset = 0;
    g_Player.spike_immune = 1;
    g_Player.x_pos.val = c->g_Player_x_pos;
    g_Player.y_pos.val = 65536000;
    g_Player.unk68 = NULL;
    train_cannon_init(&obj);
    obj.x_pos.val = c->obj_x_pos;
    obj.unk5 = c->unk5;
    obj.unk6 = 1;
    obj.unk63 = 0;
    obj.invincibility_timer = 0;
    obj.ext.main_38.saved_unk5 = c->saved_unk5;
    obj.ext.main_38.unk88 = 1;
    obj.unk7C = 7;
    obj.unk7E = 3;
    if (obj.unk5 == 4) {
        set_animation(&obj, 2);
    }
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    pools_full = 0;
    {
        u32 slot;
        for (slot = 0; slot < 16; ++slot)
            weapon_objects[slot].active = pools_full ? 1 : 0;
    }
    player_before = g_Player;
    entity_before = g_Entity;
    engine_before = engine_obj;
    memcpy(cameras_before, background_objects, sizeof(cameras_before));
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    train_cannon_main(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&g_Entity, &entity_before, sizeof(g_Entity));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, cameras_before, sizeof(background_objects));
    c_test_same_words(weapon_objects, weapons_before, sizeof(weapon_objects));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.ext.main_38.saved_unk5;
    observed_values[4] = (u32)obj.ext.main_38.unk88;
    observed_values[5] = (u32)obj.on_screen;
    observed_values[6] = (u32)obj.unk7C;
    observed_values[7] = (u32)obj.unk7E;
    observed_values[8] = (u32)obj.invincibility_timer;
    observed_values[9] = (u32)obj.unk42;
    observed_values[10] = (u32)obj.hp;
    observed_values[11] = (u32)obj.x_pos.val;
    observed_values[12] = (u32)obj.y_pos.val;
    observed_values[13] = (u32)obj.unk18.val;
    observed_values[14] = (u32)obj.unk1C.val;
    observed_values[15] = (u32)obj.animation_step.packed;
    return c_test_observe(0, row, observed_values, c->expected, 16);
}

static const u32 train_cannon_spawn_charge_glow_0_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_train_cannon_spawn_charge_glow_0(u32 row)
{
    u32 observed_values[10];
    struct VisualObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_0_full ? 1 : 0;
    }
    train_cannon_spawn_charge_glow(&obj);
    observed_values[0] = (u32)visual_objects[0].active;
    observed_values[1] = (u32)visual_objects[0].bg_offset;
    observed_values[2] = (u32)visual_objects[0].id;
    observed_values[3] = (u32)visual_objects[0].unk15;
    observed_values[4] = (u32)visual_objects[0].unk16;
    observed_values[5] = (u32)visual_objects[0].unk2;
    observed_values[6] = (u32)visual_objects[0].unk40;
    observed_values[7] = (u32)visual_objects[0].unk42;
    observed_values[8] = (u32)visual_objects[0].x_pos.val;
    observed_values[9] = (u32)visual_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, train_cannon_spawn_charge_glow_0_expected, 10);
}

struct train_cannon_spawn_charge_glow_1_case {
    u32 free_last;
    u32 expected[6];
};
static const struct train_cannon_spawn_charge_glow_1_case train_cannon_spawn_charge_glow_1_cases[] = {
    { 0, { 1u, 0u, 0u, 0u, 0u, 0u } },
    { 1, { 0x41u, 0x10u, 4u, 0x1234u, 0x3201234u, 0x645678u } },
};
static u32 test_train_cannon_spawn_charge_glow_1(u32 row)
{
    const struct train_cannon_spawn_charge_glow_1_case* c = &train_cannon_spawn_charge_glow_1_cases[row];
    u32 observed_values[6];
    struct VisualObj obj, object_before, expected[32];
    struct PlayerObj player_before;
    u8 pools_full, free_last;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 38;
    obj.unk42 = 0x1234;
    obj.unk40 = 0x56;
    obj.unk15 = 0x40;
    obj.animation_table = (const u8* const*)train_cannon_animations;
    obj.x_pos.val = 52433460;
    obj.y_pos.val = 6575736;
    pools_full = 1;
    free_last = c->free_last;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pools_full ? 1 : 0;
    }
    if (free_last) {
        visual_objects[31].active = 0;
    }
    memcpy(expected, visual_objects, sizeof(expected));
    if (free_last) {
        expected[31].active = 0x41;
    }
    if (free_last) {
        expected[31].id = 0x10;
    }
    if (free_last) {
        expected[31].unk2 = 0;
    }
    if (free_last) {
        expected[31].unk50 = (struct PlayerObj*)&obj;
    }
    if (free_last) {
        expected[31].unk42 = obj.unk42;
    }
    if (free_last) {
        expected[31].animation_table = (const u8* const*)train_cannon_animations;
    }
    if (free_last) {
        expected[31].unk3C = (void*)obj.unk3C;
    }
    if (free_last) {
        expected[31].unk40 = obj.unk40;
    }
    if (free_last) {
        expected[31].bg_offset = obj.bg_offset;
    }
    if (free_last) {
        expected[31].unk16 = 4;
    }
    if (free_last) {
        expected[31].unk15 = obj.unk15;
    }
    if (free_last) {
        expected[31].x_pos.val = obj.x_pos.val;
    }
    if (free_last) {
        expected[31].y_pos.val = obj.y_pos.val;
    }
    object_before = obj;
    player_before = g_Player;
    train_cannon_spawn_charge_glow(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&obj, &object_before, sizeof(obj));
    c_test_same_words(visual_objects, expected, sizeof(visual_objects));
    observed_values[0] = (u32)visual_objects[31].active;
    observed_values[1] = (u32)visual_objects[31].id;
    observed_values[2] = (u32)visual_objects[31].unk16;
    observed_values[3] = (u32)visual_objects[31].unk42;
    observed_values[4] = (u32)visual_objects[31].x_pos.val;
    observed_values[5] = (u32)visual_objects[31].y_pos.val;
    return c_test_observe(0, row, observed_values, c->expected, 6);
}

const struct CTestGroup c_test_groups[] = {
    { "train_cannon_signed_default", train_cannon_signed_default_cases, train_cannon_signed_default_cases_expected, COUNT(train_cannon_signed_default_cases), 0 },
    { "train_cannon_fire_blast_0", 0, 0, 1, test_train_cannon_fire_blast_0 },
    { "train_cannon_fire_blast_1", 0, 0, 2, test_train_cannon_fire_blast_1 },
    { "train_cannon_fire_volley_0", 0, 0, 1, test_train_cannon_fire_volley_0 },
    { "train_cannon_fire_volley_1", 0, 0, 2, test_train_cannon_fire_volley_1 },
    { "train_cannon_idle_pick", 0, 0, 1, test_train_cannon_idle_pick },
    { "train_cannon_main", 0, 0, 3, test_train_cannon_main },
    { "train_cannon_spawn_charge_glow_0", 0, 0, 1, test_train_cannon_spawn_charge_glow_0 },
    { "train_cannon_spawn_charge_glow_1", 0, 0, 2, test_train_cannon_spawn_charge_glow_1 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(train_cannon_signed_default_cases) + 1 + 2 + 1 + 2 + 1 + 3 + 1 + 2;
