#include "test_runtime.h"
#include "main/mains/main_14_ice_bird.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static u8 sound_entries[65 * 4];
static u32 bird_case(u32 mode)
{
    struct MainObj obj, expected;
    struct VisualObj pool[32];
    struct BackgroundObj backgrounds[3];
    struct EngineObj engine_before;
    struct PlayerObj player_before = g_Player;
    u8 spawn = 0xFF;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(sound_entries, 0, sizeof(sound_entries));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    D_80141F50[2] = sound_entries;
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 39;
        visual_objects[i].state = 40;
        visual_objects[i].unk2 = 9;
        visual_objects[i].unk5 = 3;
        visual_objects[i].unk6 = 4;
        visual_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        visual_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    if (mode == 1 || mode == 3)
        visual_objects[31].active = 0;
    obj.active = 0x41;
    obj.id = 14;
    obj.state = 1;
    obj.on_screen = 1;
    obj.unk5 = 2;
    obj.unk6 = 0;
    obj.unk7 = 7;
    obj.unk2 = 1;
    obj.unk15 = mode & 2 ? 0x40 : 0;
    obj.unk16 = 8;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = 123;
    obj.y_speed = 456;
    obj.x_accel = 789;
    obj.gravity = 987;
    obj.ext.main_14.unk80 = 9;
    obj.ext.main_14.unk84 = 8;
    obj.ext.main_14.visual_variant = 7;
    obj.ext.main_14.unk94 = mode == 5;
    obj.backref = &spawn;
    obj.animation_table = (const u8* const*)ice_bird_animations;
    set_animation(&obj, 0);
    engine_obj.character_state.bytes[0] = 7;
    expected = obj;
    engine_before = engine_obj;
    memcpy(pool, visual_objects, sizeof(pool));
    memcpy(backgrounds, background_objects, sizeof(backgrounds));
    if (mode < 4) {
        expected.animation_step.fields.duration = 4;
        expected.ext.main_14.unk80 = 0x20;
        expected.ext.main_14.unk84 = 1;
        assert(ice_bird_fly_speeds[0] == -131072 && ice_bird_fly_speeds[1] == 131072);
        expected.x_speed = mode & 2 ? 131072 : -131072;
        expected.unk6 = 1;
        if (mode == 1 || mode == 3) {
            struct VisualObj* child = &pool[31];
            expected.ext.main_14.visual_variant = 3;
            child->unk50 = PLAYER_OBJECT(&obj);
            child->active = 0x41;
            child->unk2 = 3;
            child->id = 0xB;
            child->state = child->unk5 = child->unk6 = 0;
            child->unk38 = 0;
            child->unk3C = ANIMATED_OBJECT(&obj)->unk3C;
            child->animation_table = ANIMATED_OBJECT(&obj)->animation_table;
            child->unk40 = obj.unk40;
            child->unk42 = obj.unk42;
            child->unk16 = 4;
            child->x_pos = obj.x_pos;
            child->y_pos = obj.y_pos;
        }
        ice_bird_fly_in_start(&obj);
    } else {
        expected.ext.main_14.unk80 = expected.ext.main_14.unk84 = 0;
        engine_before.character_state.bytes[0] = 0;
        expected.active = expected.id = expected.unk2 = expected.on_screen = 0;
        expected.state = expected.unk5 = expected.unk6 = expected.unk7 = 0;
        ice_bird_despawn(&obj);
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(pool) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)pool)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(backgrounds) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(spawn == (mode == 5 ? 0x70 : 0xFF));
    for (i = 0; i < sizeof(sound_entries); i++)
        assert(sound_entries[i] == 0);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    return (u8)obj.unk6 | ((u32)(u8)visual_objects[31].active << 8) | ((u32)spawn << 16);
}
#define CASE(m)                                           \
    static u32 ice_bird_flight_and_despawn_bird_##m(void) \
    {                                                     \
        return bird_case(m);                              \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
#define ENTRY(m) ice_bird_flight_and_despawn_bird_##m,
static const CTestCase ice_bird_flight_and_despawn_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) };
static const u32 ice_bird_flight_and_despawn_cases_expected[] = { 0xFF0101u, 0xFF4101u, 0xFF0101u, 0xFF4101u, 0xFF0100u, 0x700100u };
#undef CASE
#undef ENTRY

static const u32 func_8004D6FC_0_expected[] = { 0u, 7u };
static u32 test_func_8004D6FC_0(u32 row)
{
    u32 observed_values[2];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.ext.main_14.unk84 = 1;
    obj.ext.main_14.visual_variant = 7;
    func_8004D6FC(&obj);
    observed_values[0] = (u32)obj.ext.main_14.unk84;
    observed_values[1] = (u32)obj.ext.main_14.visual_variant;
    return c_test_observe(0, row, observed_values, func_8004D6FC_0_expected, 2);
}

struct func_8004D6FC_1_case {
    u32 unk5, obj_main_14_unk84, obj_main_14_visual_variant, expected_main_14_unk84;
    u32 expected_main_14_visual_variant;
    u32 expected[2];
};
static const struct func_8004D6FC_1_case func_8004D6FC_1_cases[] = {
    { 3, 1, 2, 0, 3, { 0u, 3u } },
    { 3, 1, 3, 30, 4, { 0x1Eu, 4u } },
    { 3, 1, 4, 20, 5, { 0x14u, 5u } },
    { 3, 1, 5, 50, 6, { 0x32u, 6u } },
    { 3, 1, 6, 0, 7, { 0u, 7u } },
    { 3, 1, 7, 0, 7, { 0u, 7u } },
    { 3, 0, 2, 4294967295, 2, { 0xFFFFFFFFu, 2u } },
    { 2, 1, 2, 1, 2, { 1u, 2u } },
    { 5, 1, 2, 1, 2, { 1u, 2u } },
};
static u32 test_func_8004D6FC_1(u32 row)
{
    const struct func_8004D6FC_1_case* c = &func_8004D6FC_1_cases[row];
    u32 observed_values[2];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 14;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 14;
    obj.contact_damage = 3;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)ice_bird_animations;
    obj.hurt_box = &ice_bird_body_box;
    obj.attack_box = &ice_bird_body_box;
    obj.collision_data = D_80106974;
    obj.ext.main_14.unk84 = 2;
    set_animation(&obj, 0);
    obj.unk5 = c->unk5;
    obj.ext.main_14.unk84 = c->obj_main_14_unk84;
    obj.ext.main_14.visual_variant = c->obj_main_14_visual_variant;
    expected = obj;
    expected.ext.main_14.unk84 = c->expected_main_14_unk84;
    expected.ext.main_14.visual_variant = c->expected_main_14_visual_variant;
    player_expected = g_Player;
    engine_before = engine_obj;
    func_8004D6FC(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    observed_values[0] = (u32)obj.ext.main_14.unk84;
    observed_values[1] = (u32)obj.ext.main_14.visual_variant;
    return c_test_observe(0, row, observed_values, c->expected, 2);
}

struct ice_bird_blast_release_case {
    u32 full;
    u32 expected[4];
};
static const struct ice_bird_blast_release_case ice_bird_blast_release_cases[] = {
    { 1, { 3u, 0x10004u, 1u, 0u } },
    { 0, { 3u, 0x10004u, 1u, 0x11u } },
};
static u32 test_ice_bird_blast_release(u32 row)
{
    const struct ice_bird_blast_release_case* c = &ice_bird_blast_release_cases[row];
    u32 observed_values[4];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct EffectObj effects_expected[32];
    struct VisualObj visuals_before[32];
    u8 sound[264], sound_before[264];
    u8 full, pools_full;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 14;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 14;
    obj.contact_damage = 3;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)ice_bird_animations;
    obj.hurt_box = &ice_bird_body_box;
    obj.attack_box = &ice_bird_body_box;
    obj.collision_data = D_80106974;
    obj.ext.main_14.unk84 = 2;
    set_animation(&obj, 0);
    obj.unk5 = 4;
    obj.unk6 = 2;
    obj.unk2 = 3;
    obj.ext.main_14.visual_variant = 0xFF;
    D_8013E198[2] = -1;
    memset(sound, 0, sizeof(sound));
    D_80141F50[2] = sound;
    memcpy(sound_before, sound, sizeof(sound_before));
    pools_full = 1;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            effect_objects[slot].active = pools_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pools_full ? 1 : 0;
    }
    full = c->full;
    if (!full) {
        memset(&effect_objects[31], 0, sizeof(effect_objects[31]));
    }
    memcpy(effects_expected, effect_objects, sizeof(effects_expected));
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    if (!full) {
        effects_expected[31].active = 1;
    }
    if (!full) {
        effects_expected[31].id = 0x11;
    }
    if (!full) {
        effects_expected[31].unk2 = obj.unk2;
    }
    if (!full) {
        effects_expected[31].x_pos = obj.x_pos;
    }
    if (!full) {
        effects_expected[31].y_pos = obj.y_pos;
    }
    if (!full) {
        effects_expected[31].ext.effect_17.source = ANIMATED_OBJECT(&obj);
    }
    expected = obj;
    expected.animation_step.fields.duration = 4;
    expected.unk6 = 3;
    player_expected = g_Player;
    engine_before = engine_obj;
    ice_bird_blast_release(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(effect_objects, effects_expected, sizeof(effects_expected));
    c_test_same_words(visual_objects, visuals_before, sizeof(visuals_before));
    c_test_same_words(sound, sound_before, sizeof(sound));
    assert(D_80141F50[2] == sound);
    assert(D_8013E198[2] == -1);
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.animation_step.packed;
    observed_values[2] = (u32)effect_objects[31].active;
    observed_values[3] = (u32)effect_objects[31].id;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

static const u32 ice_bird_face_player_expected[] = { 0x40u };
static u32 test_ice_bird_face_player(u32 row)
{
    u32 observed_values[1];
    struct AnimatedObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    ice_bird_face_player(&obj);
    observed_values[0] = (u32)obj.unk15;
    return c_test_observe(0, row, observed_values, ice_bird_face_player_expected, 1);
}

struct ice_bird_leave_start_case {
    u32 unk15, x_speed;
    u32 expected[4];
};
static const struct ice_bird_leave_start_case ice_bird_leave_start_cases[] = {
    { 0, -131072, { 0xFFFE0000u, 1u, 0x10004u, 0u } },
    { 64, 131072, { 0x20000u, 1u, 0x10004u, 0u } },
};
static u32 test_ice_bird_leave_start(u32 row)
{
    const struct ice_bird_leave_start_case* c = &ice_bird_leave_start_cases[row];
    u32 observed_values[4];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 14;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 14;
    obj.contact_damage = 3;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)ice_bird_animations;
    obj.hurt_box = &ice_bird_body_box;
    obj.attack_box = &ice_bird_body_box;
    obj.collision_data = D_80106974;
    obj.ext.main_14.unk84 = 2;
    set_animation(&obj, 0);
    obj.unk5 = 5;
    obj.unk6 = 0;
    obj.unk15 = c->unk15;
    obj.x_speed = 0x4567;
    engine_obj.character_state.bytes[0] = 7;
    expected = obj;
    set_animation(&expected, 0);
    expected.animation_step.fields.duration = 4;
    expected.x_speed = c->x_speed;
    expected.unk6 = 1;
    player_expected = g_Player;
    engine_before = engine_obj;
    engine_before.character_state.bytes[0] = 0;
    ice_bird_leave_start(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    observed_values[0] = (u32)obj.x_speed;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.animation_step.packed;
    observed_values[3] = (u32)engine_obj.character_state.bytes[0];
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

struct ice_bird_main_0_case {
    u32 unk8C;
    u32 expected[5];
};
static const struct ice_bird_main_0_case ice_bird_main_0_cases[] = {
    { 4278190080, { 0u, 0u, 2u, 0x3FC0C0C0u, 0u } },
    { 0, { 0u, 1u, 2u, 0x3FC0C0C0u, 0u } },
};
static u32 test_ice_bird_main_0(u32 row)
{
    const struct ice_bird_main_0_case* c = &ice_bird_main_0_cases[row];
    u32 observed_values[5];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&cur_random, 0, sizeof(cur_random));
    memset(&effect_objects, 0, sizeof(effect_objects));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&item_objects, 0, sizeof(item_objects));
    memset(&misc_objects, 0, sizeof(misc_objects));

    memset(&qux_object, 0, sizeof(qux_object));
    memset(&visual_objects, 0, sizeof(visual_objects));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    obj.x_pos.val = 1069596864;
    obj.y_pos.val = 0;
    obj.unk5 = 1;
    g_Player.x_pos.val = 0;
    obj.ext.main_14.unk8C = c->unk8C;
    ice_bird_main(&obj);
    observed_values[0] = (u32)obj.ext.main_14.saved_unk5;
    observed_values[1] = (u32)obj.ext.main_14.unk94;
    observed_values[2] = (u32)obj.state;
    observed_values[3] = (u32)obj.unk18.val;
    observed_values[4] = (u32)obj.unk1C.val;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

struct ice_bird_main_1_case {
    u32 saved_unk5, unk8C, obj_x_pos_hi, g_Player_x_pos_hi, unk5, state, on_screen, unk42, unk84, unk94;
    u32 expected[5];
};
static const struct ice_bird_main_1_case ice_bird_main_1_cases[] = {
    { 0, 0, 500, 100, 0, 2, 0, 37428, 1, 1, { 2u, 1u, 0u, 0x9234u, 0u } },
    { 5, 1, 500, 100, 5, 2, 0, 4660, 2, 0, { 2u, 0u, 5u, 0x1234u, 0u } },
    { 5, 0, -100, 100, 5, 2, 0, 4660, 2, 0, { 2u, 0u, 5u, 0x1234u, 0u } },
    { 0, 0, 100, 200, 0, 1, 1, 37428, 1, 0, { 1u, 0u, 0u, 0x9234u, 1u } },
};
static u32 test_ice_bird_main_1(u32 row)
{
    const struct ice_bird_main_1_case* c = &ice_bird_main_1_cases[row];
    u32 observed_values[5];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct WeaponObj weapons_before[16];
    struct BackgroundObj background_before;
    u8 pools_full;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 14;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 14;
    obj.contact_damage = 3;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)ice_bird_animations;
    obj.hurt_box = &ice_bird_body_box;
    obj.attack_box = &ice_bird_body_box;
    obj.collision_data = D_80106974;
    obj.ext.main_14.unk84 = 2;
    set_animation(&obj, 0);
    obj.unk5 = 1;
    obj.ext.main_14.saved_unk5 = c->saved_unk5;
    obj.ext.main_14.unk8C = c->unk8C;
    obj.x_pos.i.hi = c->obj_x_pos_hi;
    obj.unk42 = 0x9234;
    g_Player.x_pos.i.hi = c->g_Player_x_pos_hi;
    g_Player.spike_immune = 1;
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    pools_full = 0;
    {
        u32 slot;
        for (slot = 0; slot < 16; ++slot)
            weapon_objects[slot].active = pools_full ? 1 : 0;
    }
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    expected = obj;
    expected.unk5 = c->unk5;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.state = c->state;
    expected.on_screen = c->on_screen;
    expected.unk42 = c->unk42;
    expected.ext.main_14.unk84 = c->unk84;
    expected.ext.main_14.unk94 = c->unk94;
    player_expected = g_Player;
    engine_before = engine_obj;
    background_before = background_objects[0];
    ice_bird_main(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(weapon_objects, weapons_before, sizeof(weapons_before));
    c_test_same_words(&background_objects[0], &background_before, sizeof(background_before));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.ext.main_14.unk94;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.unk42;
    observed_values[4] = (u32)obj.on_screen;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

static const u32 ice_bird_spawn_ice_shards_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_ice_bird_spawn_ice_shards(u32 row)
{
    u32 observed_values[12];
    struct AnimatedObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_0_full ? 1 : 0;
    }
    ice_bird_spawn_ice_shards(&obj);
    observed_values[0] = (u32)visual_objects[0].active;
    observed_values[1] = (u32)visual_objects[0].bg_offset;
    observed_values[2] = (u32)visual_objects[0].id;
    observed_values[3] = (u32)visual_objects[0].state;
    observed_values[4] = (u32)visual_objects[0].unk16;
    observed_values[5] = (u32)visual_objects[0].unk2;
    observed_values[6] = (u32)visual_objects[0].unk40;
    observed_values[7] = (u32)visual_objects[0].unk42;
    observed_values[8] = (u32)visual_objects[0].unk5;
    observed_values[9] = (u32)visual_objects[0].unk6;
    observed_values[10] = (u32)visual_objects[0].x_pos.val;
    observed_values[11] = (u32)visual_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, ice_bird_spawn_ice_shards_expected, 12);
}

const struct CTestGroup c_test_groups[] = {
    { "ice_bird_flight_and_despawn", ice_bird_flight_and_despawn_cases, ice_bird_flight_and_despawn_cases_expected, COUNT(ice_bird_flight_and_despawn_cases), 0 },
    { "func_8004D6FC_0", 0, 0, 1, test_func_8004D6FC_0 },
    { "func_8004D6FC_1", 0, 0, 9, test_func_8004D6FC_1 },
    { "ice_bird_blast_release", 0, 0, 2, test_ice_bird_blast_release },
    { "ice_bird_face_player", 0, 0, 1, test_ice_bird_face_player },
    { "ice_bird_leave_start", 0, 0, 2, test_ice_bird_leave_start },
    { "ice_bird_main_0", 0, 0, 2, test_ice_bird_main_0 },
    { "ice_bird_main_1", 0, 0, 4, test_ice_bird_main_1 },
    { "ice_bird_spawn_ice_shards", 0, 0, 1, test_ice_bird_spawn_ice_shards },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(ice_bird_flight_and_despawn_cases) + 1 + 9 + 2 + 1 + 2 + 2 + 4 + 1;
