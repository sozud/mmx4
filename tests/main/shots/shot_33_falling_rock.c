#include "test_runtime.h"
#include "support/state_cases.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "main/shots/shot_33_falling_rock.h"
void func_800A12EC(struct ShotObj*);

extern union AnimationStep* falling_rock_c_animations[];

static struct ShotObj rock;
static struct WeaponObj shadow;
static struct EffectObj controller;
static struct Unk_unk68 terrain_box = { 0, 0, 4, 4 };

static void prepare_rock(u8 on_screen)
{
    u32 i;
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(background_objects, 0, sizeof(background_objects));
    memset(&rock, 0, sizeof(rock));
    memset(&shadow, 0, sizeof(shadow));
    memset(&controller, 0, sizeof(controller));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(D_80141F50, 0, sizeof(D_80141F50));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    D_80141F50[2] = state_sound_rows;
    cur_random = 0xD37;
    g_Player.spike_immune = 1;
    rock.active = 0x41;
    rock.id = 33;
    rock.state = 7;
    rock.on_screen = on_screen;
    rock.x_pos.val = 64 * 65536;
    rock.y_pos.val = 90 * 65536;
    rock.unk18 = rock.x_pos;
    rock.unk1C = rock.y_pos;
    rock.y_vel.val = -65536;
    rock.unk5C = 15;
    rock.unk42 = 0x8001;
    rock.animation_table = (u32**)falling_rock_c_animations;
    set_animation(&rock, 3);
    shadow.active = 1;
    shadow.on_screen = 1;
    shadow.animation_table = rock.animation_table;
    set_animation(&shadow, 2);
    rock.unk7C = &shadow;
    rock.unk84.effect = &controller;
    controller.ext.effect_33.timer = 11;
}

static void check_debris(u32 first)
{
    u32 i;
    for (i = 0; i < COUNT(misc_objects); i++) {
        struct MiscObj* piece = &misc_objects[i];
        if (i >= 5) {
            assert(piece->active == 0);
            continue;
        }
        assert(piece->active == 0x41 && piece->id == 3);
        assert(piece->unk2 == 0 && piece->state == 0);
        assert(piece->ext.misc_2.unk58 == first + i);
        assert(piece->ext.misc_2.owner == MAIN_OBJECT(&rock));
        assert(piece->unk15 == 0 || piece->unk15 == 0x40);
        assert(piece->x_pos.val >= rock.x_pos.val);
        assert(piece->x_pos.val <= rock.x_pos.val + 3 * 65536);
        assert(piece->y_pos.val >= rock.y_pos.val);
        assert(piece->y_pos.val <= rock.y_pos.val + 3 * 65536);
    }
}

static u32 test_freezing_weapon(u32 row)
{
    static const u8 weapons[] = { 2, 11, 33 };
    struct WeaponObj expected_shadow;
    prepare_rock(row & 1);
    state_hit(MAIN_OBJECT(&rock), weapons[row / 2], 0, 1);
    expected_shadow = shadow;
    expected_shadow.active = expected_shadow.on_screen = 0;
    func_800A12EC(&rock);
    assert(rock.state == 7 && rock.unk5 == 1);
    assert(rock.timer == 8 && rock.unk5C == 14);
    assert(rock.unk17 == 9 && rock.previous_animation_index == 0xFF);
    assert(rock.animation_cursor == (u32*)falling_rock_c_animations[9]);
    assert(rock.animation_step.packed == falling_rock_c_animations[9][0].packed);
    assert(rock.y_pos.val == 91 * 65536 && rock.y_vel.val == -65536);
    assert(rock.on_screen == 1 && rock.unk42 == 0x8001);
    assert(controller.ext.effect_33.timer == 11);
    assert(misc_objects[0].active == 0);
    c_test_same_words(&shadow, &expected_shadow, sizeof(shadow));
    return 1;
}

static u32 test_destruction(u32 row)
{
    struct WeaponObj shadow_before;
    prepare_rock(row & 1);
    shadow_before = shadow;
    if (row < 2) {
        rock.unk5C = 1;
        state_hit(MAIN_OBJECT(&rock), 0, 0, 2);
    } else {
        engine_obj.character_state.fields.active = 1;
    }
    func_800A12EC(&rock);
    assert(rock.state == 8 && rock.unk5 == 0);
    assert(rock.unk5C == (row < 2 ? 0 : 15));
    assert(controller.ext.effect_33.timer == 180);
    assert(rock.y_pos.val == 91 * 65536);
    check_debris(4);
    c_test_same_words(&shadow, &shadow_before, sizeof(shadow));
    return 1;
}

static u32 test_player_contact(u32 row)
{
    struct PlayerObj player_before;
    prepare_rock(row);
    rock.unk50.data = (const u8*)&state_hit_box;
    MAIN_OBJECT(&g_Player)->hurt_box = (const u8*)&state_hit_box;
    g_Player.x_pos = rock.x_pos;
    g_Player.y_pos = rock.y_pos;
    player_before = g_Player;
    func_800A12EC(&rock);
    assert(rock.state == 8 && rock.unk5 == 0);
    assert(rock.unk5C == 15 && rock.timer == 0);
    assert(controller.ext.effect_33.timer == 11);
    check_debris(4);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    return 1;
}

static u32 test_frozen_countdown(u32 row)
{
    static const s16 timers[] = { 1, 2, 8, 1 };
    struct ShotObj expected;
    prepare_rock(1);
    rock.unk5 = 1;
    rock.timer = timers[row];
    if (row == 3)
        rock.y_pos.val = 337 * 65536;
    expected = rock;
    expected.unk42 = 1;
    expected.timer--;
    expected.state = row == 0 || row == 3 ? 8 : 7;
    func_800A12EC(&rock);
    c_test_same_words(&rock, &expected, sizeof(rock));
    assert(controller.ext.effect_33.timer == (expected.timer == 0 ? 180 : 11));
    if (expected.timer == 0)
        check_debris(10);
    else
        assert(misc_objects[0].active == 0);
    return 1;
}

static u32 test_terrain_impact(u32 row)
{
    u32 i, ceiling = row >= 4, shaking = row & 2;
    struct BackgroundObj expected_background;
    prepare_rock(row & 1);
    state_terrain(0);
    memset(state_tile_pixels, 0, sizeof(state_tile_pixels));
    state_tile_attrs[1] = 0x38;
    for (i = 0; i < 256; i++)
        state_tile_pixels[256 + i] = ceiling ? i / 16 < 4 : i / 16 >= 6;
    rock.unk68 = &terrain_box;
    rock.y_pos.val = (ceiling ? 70 : 90) * 65536;
    rock.unk1C = rock.y_pos;
    rock.y_vel.val = (ceiling ? 4 : -4) * 65536;
    engine_obj.substage = 1;
    if (shaking)
        background_objects[0].unk34 = 0x10;
    expected_background = background_objects[0];
    if (!shaking) {
        expected_background.unk36 = 16;
        expected_background.unk45 = expected_background.unk3E.bytes[0] = 6;
        expected_background.unk3C = expected_background.unk3A = 2;
        expected_background.unk34 |= 0x10;
    }
    func_800A12EC(&rock);
    assert(rock.unk70 == (ceiling ? 4 : 8));
    assert(rock.state == 8 && rock.unk5 == 0);
    assert(rock.y_pos.i.hi == (ceiling ? 68 : 92));
    assert(rock.y_vel.val == (ceiling ? 4 : -4) * 65536);
    assert(rock.unk42 == 1 && rock.unk5C == 15);
    assert(controller.ext.effect_33.timer == 11);
    c_test_same_words(&background_objects[0], &expected_background, sizeof(expected_background));
    check_debris(4);
    return 1;
}

static u32 test_apex(u32 row)
{
    prepare_rock(1);
    rock.y_vel.val = 0;
    rock.unk2 = row ? 2 : 0;
    set_animation(&rock, 1);
    set_animation(&shadow, 1);
    func_800A12EC(&rock);
    assert(rock.state == (row ? 8 : 7));
    assert(rock.unk17 == (row ? 1 : 3));
    assert(shadow.unk17 == (row ? 1 : 2));
    assert(rock.y_pos.val == 90 * 65536 && rock.unk42 == 1);
    assert(controller.ext.effect_33.timer == 11);
    assert(misc_objects[0].active == 0);
    return 1;
}

extern union AnimationStep* falling_rock_c_animations[];
extern struct Unk_unk68 falling_rock_box_2[], falling_rock_box_5[];
static u32 metadata[7], archive[16];
static struct MiscObj expected_pool[64];
static u32 rock_falling_rock_c_capacity(u32 row)
{
    struct ShotObj obj, expected;
    struct EffectObj owner, owner_before;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    u32 kind = row % 2, full = row / 2 % 2, stopped = row / 4 % 2, layer = row / 8, i, animation = kind ? 1 : 3;
    engine_obj.stage = 4;
    engine_obj.substage = 1;
    engine_obj.character_state.bytes[0] = stopped;
    engine_before = engine_obj;
    g_Player.bg_offset = layer;
    player_before = g_Player;
    memset(background_objects, 0, sizeof(background_objects));
    background_objects[layer].y_pos.i.hi = 640;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    for (i = 0; i < COUNT(metadata); i++)
        metadata[i] = (i + 1) * 128;
    for (i = 0; i < COUNT(archive); i++)
        archive[i] = i < 7 ? 28 + i * 4 : 0x13570000 + i;
    D_801406A8 = metadata;
    TEST_MENU_FRAMES = (u8*)archive;
    assert(func_8002938C(0x8D) == 6);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = i == 63 && !full ? 0 : 1;
    memcpy(expected_pool, misc_objects, sizeof(expected_pool));
    memset(&owner, 0, sizeof(owner));
    owner.active = 1;
    owner.id = 33;
    owner.state = 1;
    owner.unk2 = kind ? 0x24 : 0x22;
    owner.unk6 = 1;
    owner.x_pos.i.hi = kind ? 512 : 384;
    owner.y_pos.i.hi = 647;
    owner.ext.effect_33.variant = kind;
    owner_before = owner;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 33;
    obj.state = 6;
    obj.unk2 = kind;
    obj.x_pos = owner.x_pos;
    obj.y_pos = owner.y_pos;
    obj.unk84.effect = &owner;
    expected = obj;
    if (stopped)
        expected.state = 8;
    else {
        expected.on_screen = 1;
        expected.bg_offset = layer;
        expected.unk58.animation_steps = D_80105FF0;
        expected.unk5C = 15;
        expected.unk60 = 6;
        expected.unk40 = 7;
        expected.unk3C = (u8*)archive + 52;
        expected.unk42 = 0x78C0;
        expected.animation_table = (u32**)falling_rock_c_animations;
        expected.unk17 = animation;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (u32*)falling_rock_c_animations[animation];
        expected.animation_step.packed = kind ? 0x04010002 : 0x10010002;
        expected.y_vel.val = kind ? 0xA0000 : -0x18000;
        expected.unk2C = 0x2000;
        expected.y_pos.i.hi = kind ? 0x330 : 576;
        expected.unk68 = falling_rock_box_5;
        expected.unk54 = expected.unk50.data = (const u8*)falling_rock_box_2;
        expected.state = 7;
        if (!full) {
            struct MiscObj* m = &expected_pool[63];
            u32 a = kind ? 0 : 2;
            m->active = 0x41;
            m->id = 27;
            m->unk16 = 1;
            m->unk40 = 7;
            m->unk42 = 0x78C0;
            m->animation_table = expected.animation_table;
            m->unk3C = expected.unk3C;
            m->bg_offset = layer;
            m->x_pos = expected.x_pos;
            m->y_pos = expected.y_pos;
            m->ext.misc_5.owner = (struct MainObj*)&obj;
            m->unk6 = 1;
            m->unk17 = a;
            m->previous_animation_index = 0xFF;
            m->animation_cursor = (u32*)falling_rock_c_animations[a];
            m->animation_step.packed = kind ? 0x00010002 : 0x0C010002;
            expected.unk7C = (struct WeaponObj*)&misc_objects[63];
        }
    }
    func_800A0FE8(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(misc_objects, expected_pool, sizeof(expected_pool));
    c_test_same_words(&owner, &owner_before, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(D_801406A8 == metadata && TEST_MENU_FRAMES == (u8*)archive);
    for (i = 0; i < COUNT(metadata); i++)
        assert(metadata[i] == (i + 1) * 128);
    for (i = 0; i < COUNT(archive); i++)
        assert(archive[i] == (i < 7 ? 28 + i * 4 : 0x13570000 + i));
    return 1;
}

void func_800A068C(struct ShotObj*);
extern union AnimationStep *falling_rock_a_animations[], *falling_rock_b_animations[];
extern struct Unk_unk68 falling_rock_box_0[], falling_rock_box_1[], falling_rock_box_3[], falling_rock_box_4[];
static const u8 weapons[] = { 2, 11, 33 }, damages[] = { 4, 8, 8 };
static const u32 initial_words[] = { 0x04010002, 0x05010004 }, frozen_words[] = { 0x13000101, 0x12000101 };
static u8 tilemap[256];
static u16 pixels[2][16][16];
static u32 attributes[1];
static struct WeaponObj weapons_expected[16];
static struct MiscObj misc_before[64];
static struct VisualObj visuals_before[32];
#define SAME(a, b) assert(c_test_word_difference((const u32*)&(a), (const u32*)&(b), sizeof(a) / 4) == 0)
static u32 weapon_transition(u32 row)
{
    struct ShotObj obj, expected;
    struct WeaponObj shadow, shadow_expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 kind = row % 2, weapon = row / 2 % 3, lethal = row / 6 % 2, facing = row / 12 % 2, visible = row / 24, i;
    union AnimationStep** animations = kind ? falling_rock_b_animations : falling_rock_a_animations;
    void (*run)(struct ShotObj*) = kind ? func_800A0C4C : func_800A068C;
    memset(tilemap, 1, sizeof(tilemap));
    memset(pixels, 0, sizeof(pixels));
    attributes[0] = 0;
    SP_BG_TILEMAP = tilemap;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    layout_width = layout_height = 16;
    layout_size = 256;
    memset(background_objects, 0, sizeof(background_objects));
    background_objects[0].unk34 = 0x10;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.spike_immune = 1;
    player_expected = g_Player;
    if (weapon == 2)
        player_expected.update_delay_request = 1;
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(misc_objects, 0, sizeof(misc_objects));
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 39;
    }
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = 1;
        misc_objects[i].id = 39;
    }
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memcpy(misc_before, misc_objects, sizeof(misc_before));
    memset(&obj, 0, sizeof(obj));
    memset(&shadow, 0, sizeof(shadow));
    shadow.active = shadow.on_screen = 1;
    shadow.id = 27;
    shadow.unk2 = 9;
    shadow.x_pos.val = 0x12345678;
    shadow_expected = shadow;
    obj.active = 0x41;
    obj.id = 33;
    obj.state = kind ? 4 : 1;
    obj.on_screen = visible;
    obj.bg_offset = 0;
    obj.unk15 = facing ? 0x40 : 0;
    obj.unk42 = 0x9234;
    obj.unk5C = lethal ? 1 : 15;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.unk18 = obj.x_pos;
    obj.unk1C = obj.y_pos;
    obj.unk7C = &shadow;
    obj.unk68 = kind ? falling_rock_box_4 : falling_rock_box_3;
    obj.unk54 = obj.unk50.data = (const u8*)(kind ? falling_rock_box_1 : falling_rock_box_0);
    obj.unk58.animation_steps = D_80105FF0;
    obj.animation_table = (u32**)animations;
    set_animation(&obj, 1);
    assert(obj.animation_step.packed == initial_words[kind]);
    weapon_objects[0].active = 0x21;
    weapon_objects[0].id = weapons[weapon];
    weapon_objects[0].unk15 = obj.unk15;
    weapon_objects[0].x_pos = obj.x_pos;
    weapon_objects[0].y_pos = obj.y_pos;
    weapon_objects[0].unk50 = obj.unk54;
    weapon_objects[0].unk98 = 7;
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    ((s16*)&weapons_expected[0].unk80)[0] = 160 + (kind ? 0 : facing ? 3
                                                                     : -3);
    ((s16*)&weapons_expected[0].unk80)[1] = kind ? 119 : 114;
    expected = obj;
    expected.unk5C = lethal ? 0 : 15 - damages[weapon];
    expected.on_screen = 1;
    expected.animation_step.fields.duration--;
    if (kind) {
        expected.unk2C = 0x8000;
        MAIN_OBJECT(&expected)->unk6C = 0;
        MAIN_OBJECT(&expected)->unk6E = 10;
    }
    if (lethal && kind)
        expected.state = 5;
    else {
        u32 animation = lethal ? 2 : kind ? 7
                                          : 8;
        expected.unk5 = lethal ? 1 : kind ? 1
                                          : 2;
        expected.unk17 = animation;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (u32*)animations[animation];
        expected.animation_step.packed = lethal ? 0x0B010002 : frozen_words[kind];
        if (!lethal) {
            expected.unk84.value = 8;
            shadow_expected.active = shadow_expected.on_screen = 0;
        }
    }
    D_8013E198[1] = D_8013E198[2] = D_8013E198[5] = -1;
    cur_random = 0x1234;
    run(&obj);
    SAME(obj, expected);
    SAME(shadow, shadow_expected);
    if (!lethal) {
        for (i = 0; i < 8; i++) {
            expected.unk42 &= 0x7FFF;
            expected.unk84.value--;
            if (i == 7)
                expected.state = kind ? 5 : 2;
            run(&obj);
            SAME(obj, expected);
            SAME(shadow, shadow_expected);
        }
    }
    SAME(g_Player, player_expected);
    SAME(engine_obj, engine_before);
    SAME(background_objects, backgrounds_before);
    SAME(weapon_objects, weapons_expected);
    SAME(visual_objects, visuals_before);
    SAME(misc_objects, misc_before);
    assert(cur_random == 0x1234 && D_8013E198[1] == -1 && D_8013E198[2] == -1 && D_8013E198[5] == -1);
    return 1;
}
static const s8 unknown_phases[] = { -1, 3, 127 };
static u32 default_phase(u32 row)
{
    struct ShotObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    g_Player.bg_offset = 0;
    player_before.bg_offset = 0;
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 33;
    obj.state = 1;
    obj.unk5 = unknown_phases[row];
    obj.on_screen = 7;
    obj.unk42 = 0x9234;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_vel.val = 0x12345;
    obj.y_vel.val = -0x2468;
    obj.unk28 = 0x1357;
    obj.unk2C = 0x3456;
    obj.animation_table = (u32**)falling_rock_a_animations;
    set_animation(&obj, 1);
    expected = obj;
    expected.unk42 = 0x1234;
    expected.on_screen = 1;
    func_800A068C(&obj);
    SAME(obj, expected);
    SAME(g_Player, player_before);
    SAME(engine_obj, engine_before);
    SAME(background_objects, backgrounds_before);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "freezing_weapon", 0, 0, 6, test_freezing_weapon },
    { "destruction", 0, 0, 4, test_destruction },
    { "player_contact", 0, 0, 2, test_player_contact },
    { "frozen_countdown", 0, 0, 4, test_frozen_countdown },
    { "terrain_impact", 0, 0, 6, test_terrain_impact },
    { "apex", 0, 0, 2, test_apex },
    { "stage4_1_shipped_dropper_variants_character_stop_and_shadow_capacity", NULL, NULL, 24, rock_falling_rock_c_capacity },
    { "weapon_freeze_countdown_and_lethal_hits", NULL, NULL, 48, weapon_transition },
    { "defined_unknown_phase_fallthrough", NULL, NULL, 3, default_phase },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 6 + 4 + 2 + 4 + 6 + 2 + 24 + 48 + 3;
