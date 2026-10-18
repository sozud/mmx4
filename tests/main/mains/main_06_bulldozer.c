#include "test_runtime.h"
#include "main/mains/main_06_bulldozer.h"
#include "support/state_cases.h"
#include "main/sprite_animations.h"
#include "main/55C4.h"
void bulldozer_charge_move(struct MainObj* arg0);
void bulldozer_charge_start(struct MainObj*);
void bulldozer_resume_step(struct MainObj* arg0);
extern struct Unk_unk68 bulldozer_hurt_boxes[2];
extern union AnimationStep* D_800FA4E8[];

static const u32 bulldozer_fall_1_expected[] = { 4u, 0u, 0x640000u, 0x770000u, 0u, 0xBE00u, 0u, 0x4200u, 1u, 0x10002u };
static u32 test_bulldozer_fall_1(u32 row)
{
    u32 observed_values[10];
    struct MainObj obj;
    struct PlayerObj player_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 6;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 7864320;
    func_80046B80(&obj);
    obj.unk5 = 4;
    obj.unk6 = 0;
    obj.air_state = 1;
    obj.collision_flags = 0;
    obj.y_speed = 65536;
    obj.gravity = 16896;
    player_before = g_Player;
    bulldozer_fall(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.x_pos.val;
    observed_values[3] = (u32)obj.y_pos.val;
    observed_values[4] = (u32)obj.x_speed;
    observed_values[5] = (u32)obj.y_speed;
    observed_values[6] = (u32)obj.x_accel;
    observed_values[7] = (u32)obj.gravity;
    observed_values[8] = (u32)obj.air_state;
    observed_values[9] = (u32)obj.animation_step.packed;
    return c_test_observe(0, row, observed_values, bulldozer_fall_1_expected, 10);
}

static const u32 func_80046C8C_expected[] = { 2u, 2u, 1u, 0x7Eu, 0x40u, 0x8000u, 1u, 0u, 0x12u, 0xFFFFFFFFu, 1u, 2u, 0x640000u, 0x780000u, 0u, 0x770054u, 0xA30Du, 1u, 1u };
static u32 test_func_80046C8C(u32 row)
{
    u32 observed_values[19];
    struct MainObj obj;
    struct EngineObj engine_before;
    struct PlayerObj player_before;
    struct VisualObj visuals_before[32];
    struct MiscObj misc_before[64];
    struct ItemObj items_before[32];
    u8 pools_full;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    pools_full = 1;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pools_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pools_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            item_objects[slot].active = pools_full ? 1 : 0;
    }
    memset(&D_8013E198, -1, sizeof(D_8013E198));
    engine_obj.stage = 1;
    cur_random = 0x1234;
    g_Player.spike_immune = 1;
    g_Player.bg_offset = -1;
    g_Player.x_pos.i.hi = 1000;
    obj.active = 0x41;
    obj.id = 6;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 7864320;
    func_80046B80(&obj);
    obj.unk6 = 1;
    obj.unk7C = 2;
    obj.collision_flags = 8;
    obj.ext.main_6.core_health = 0;
    assert(obj.unk15 == 0x40 && obj.ext.main_6.hitbox_toggle == 0);
    assert(obj.animation_table == (const u8* const*)D_800FA4E8);
    weapon_objects[0].active = 1;
    weapon_objects[0].id = 1;
    weapon_objects[0].unk15 = 0x40;
    weapon_objects[0].unk50 = (const u8*)&bulldozer_hurt_boxes[1];
    weapon_objects[0].x_pos = obj.x_pos;
    weapon_objects[0].y_pos = obj.y_pos;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memcpy(misc_before, misc_objects, sizeof(misc_before));
    memcpy(items_before, item_objects, sizeof(items_before));
    func_80046C8C(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(visual_objects, visuals_before, sizeof(visual_objects));
    c_test_same_words(misc_objects, misc_before, sizeof(misc_objects));
    c_test_same_words(item_objects, items_before, sizeof(item_objects));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.hp;
    observed_values[4] = (u32)obj.unk15;
    observed_values[5] = (u32)obj.unk42;
    observed_values[6] = (u32)obj.unk7C;
    observed_values[7] = (u32)obj.ext.main_6.armor_broken;
    observed_values[8] = (u32)obj.ext.main_6.armor_health;
    observed_values[9] = (u32)obj.ext.main_6.core_health;
    observed_values[10] = (u32)obj.ext.main_6.hitbox_toggle;
    observed_values[11] = (u32)obj.ext.main_6.saved_step;
    observed_values[12] = (u32)obj.x_pos.val;
    observed_values[13] = (u32)obj.y_pos.val;
    observed_values[14] = (u32)weapon_objects[0].unk98;
    observed_values[15] = (u32)weapon_objects[0].unk80.word;
    observed_values[16] = (u32)cur_random;
    observed_values[17] = (u32)(obj.hurt_box == (const void*)&bulldozer_hurt_boxes[1]);
    observed_values[18] = (u32)(obj.attack_box == (const void*)&bulldozer_hurt_boxes[1]);
    return c_test_observe(0, row, observed_values, func_80046C8C_expected, 19);
}

#define BD(step, sub) (state_reset(step, sub, 0), so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x40, so.terrain_box = &state_hit_box)
#define HIT(broken, toggle, armor, core) (BD(1, 0), so.hp = 0x7F, state_hit(&so, 0, 0, 2), so.hurt_box = so.attack_box = &bulldozer_hurt_boxes[toggle], so.air_state = 1, so.ext.main_6.armor_broken = broken, so.ext.main_6.hitbox_toggle = toggle, so.ext.main_6.armor_health = armor, so.ext.main_6.core_health = core, so.ext.main_6.saved_step = 1, func_80046C8C(&so), state_extra = so.ext.main_6.armor_health ^ so.ext.main_6.core_health << 8)
static void bd_fall(void)
{
    BD(4, 0);
    so.gravity = 0x4000;
    bulldozer_fall(&so);
}
static void bd_land(void)
{
    BD(4, 0);
    so.collision_flags = 8;
    so.air_state = 1;
    so.x_speed = 0x10000;
    bulldozer_fall(&so);
}
static void bd_charge_left(void)
{
    BD(3, 0);
    bulldozer_charge_start(&so);
}
static void bd_charge_left_fast(void)
{
    BD(3, 0);
    so.ext.main_6.armor_broken = 1;
    bulldozer_charge_start(&so);
}
static void bd_charge_right(void)
{
    BD(3, 0);
    so.unk15 = 0x40;
    bulldozer_charge_start(&so);
}
static void bd_charge_right_fast(void)
{
    BD(3, 0);
    so.unk15 = 0x40;
    so.ext.main_6.armor_broken = 1;
    bulldozer_charge_start(&so);
}
static void bd_resume(void)
{
    BD(1, 0);
    so.ext.main_6.saved_step = 3;
    bulldozer_resume_step(&so);
}
static void bd_move_left(void)
{
    BD(3, 1);
    state_terrain(0x38);
    so.x_speed = -0x10000;
    bulldozer_charge_move(&so);
}
static void bd_move_right(void)
{
    BD(3, 1);
    state_terrain(0x38);
    so.unk15 = 0x40;
    so.x_speed = 0x10000;
    bulldozer_charge_move(&so);
}
static void bd_move_edge(void)
{
    BD(3, 1);
    state_terrain(0);
    so.x_speed = 0x10000;
    bulldozer_charge_move(&so);
}
static void bd_hit_armor(void) { HIT(0, 1, 8, 8); }
static void bd_hit_core(void) { HIT(0, 0, 8, 8); }
static void bd_hit_broken(void) { HIT(1, 1, 8, 8); }
static void bd_hit_armor_break(void) { HIT(0, 1, 1, 8); }

static void (*const bulldozer_states_cases[])(void) = {
    bd_fall,
    bd_land,
    bd_charge_left,
    bd_charge_left_fast,
    bd_charge_right,
    bd_charge_right_fast,
    bd_resume,
    bd_move_left,
    bd_move_right,
    bd_move_edge,
    bd_hit_armor,
    bd_hit_core,
    bd_hit_broken,
    bd_hit_armor_break,
};
static const u32 bulldozer_states_expected[] = { 4u, 0u, 0x800000u, 0u, 0xFFFFC000u, 0x400000u, 0u, 0u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x103u, 0u, 0x7F8000u, 0xFFFF8000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x103u, 0u, 0x7E0000u, 0xFFFE0000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x103u, 0u, 0x808000u, 0x8000u, 0u, 0u, 0x4000u, 0u, 0u, 0u, 0x103u, 0u, 0x820000u, 0x20000u, 0u, 0u, 0x4000u, 0u, 0u, 0u, 3u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x103u, 0u, 0x7F0000u, 0xFFFF0000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x103u, 0u, 0x810000u, 0x10000u, 0u, 0u, 0x4000u, 0u, 0u, 0u, 0x103u, 0u, 0x800000u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x1000001u, 0u, 0x800000u, 0u, 0u, 0u, 0x80000000u, 0x7D0003u, 0x806u, 0x2100u, 0x1000001u, 0u, 0x800000u, 0u, 0u, 0u, 0x80000000u, 0x7D0003u, 0x608u, 0x2100u, 0x1000001u, 0u, 0x800000u, 0u, 0u, 0u, 0x80000000u, 0x7D0003u, 0x608u, 0x2100u, 0x1000002u, 0u, 0x800000u, 0u, 0u, 0u, 0x80000001u, 0x7D0003u, 0xFFFFF7FFu, 0x2100u };

static u32 test_bulldozer_states(u32 row)
{
    return state_run(bulldozer_states_cases[row], row, &bulldozer_states_expected[row * 10]);
}

extern union AnimationStep* D_800FA4E8[];
extern struct Unk_unk68 bulldozer_hurt_boxes[2], D_800FA434[2], D_800FA430, bulldozer_terrain_box, D_801065F0[];
static const u8 capacities[] = { 0, 1, 6 };
static const s8 explosion_x[3][5] = { { -32, -24, -24 }, { 36, 0, -32, -24, -24 }, { 0, 36 } };
static const s8 explosion_y[3][5] = { { 0, -27, -55 }, { 0, 0, 0, -27, -55 }, { 0, 0 } };
static const u8 explosion_count[] = { 3, 5, 2 };
static u32 directory[8] = { 0, 16, 0, 0, 0x12345678, 0x76543210, 0, 0 };
static struct WeaponObj weapons_expected[16];
static struct VisualObj visuals_expected[32];
static struct MiscObj misc_before[64];
static struct ItemObj items_before[32];
#define COPY(a, b) c_test_copy_words((u32*)&(a), (u32*)&(b), sizeof(a) / 4)
#define SAME(a, b) assert(c_test_word_difference((u32*)&(a), (u32*)&(b), sizeof(a) / 4) == 0)
static u32 break_effects(u32 row)
{
    struct MainObj obj, expected, *current = SP_CUR_MAIN_OBJ;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    u32 mode = row % 4, face = row / 4 % 2, capacity = capacities[row / 8], toggle = mode == 0, i, used = 0;
    const struct Unk_unk68* boxes = mode == 2 ? D_800FA434 : bulldozer_hurt_boxes;
    s32 x = mode == 3 ? 1000 : 160, impact_x = face ? x - (mode == 0 ? -27 : 16) : x + (mode == 0 ? -27 : 16), impact_y = mode == 0 ? 94 : 119;
    c_test_zero_words((u32*)&obj, sizeof(obj) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    c_test_zero_words((u32*)item_objects, sizeof(item_objects) / 4);
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = i < capacity ? 0 : 1;
        item_objects[i].active = 1;
    }
    for (i = 0; i < 64; i++)
        misc_objects[i].active = 1;
    COPY(visuals_expected, visual_objects);
    COPY(misc_before, misc_objects);
    COPY(items_before, item_objects);
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    engine_obj.stage = 1;
    engine_before = engine_obj;
    g_Player.hp = 30;
    g_Player.spike_immune = 1;
    player_before = g_Player;
    TEST_SPRITE_FRAMES = (u8*)directory;
    obj.active = 0x41;
    obj.id = 6;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.on_screen = 7;
    obj.unk42 = 0x9234;
    obj.unk15 = face ? 0x40 : 0;
    obj.collision_flags = 8;
    obj.x_pos.val = x * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.collision_data = D_801065F0;
    obj.hurt_box = obj.attack_box = (const u8*)&boxes[toggle];
    obj.terrain_box = mode == 2 ? &D_800FA430 : &bulldozer_terrain_box;
    obj.ext.main_6.saved_step = 2;
    obj.ext.main_6.hitbox_toggle = toggle;
    obj.ext.main_6.armor_broken = mode == 2;
    obj.ext.main_6.armor_health = mode == 0 ? 0 : 18;
    obj.ext.main_6.core_health = mode == 0 ? 9 : 0;
    obj.animation_table = (const u8* const*)D_800FA4E8;
    set_animation(&obj, mode == 2 ? 1 : 0);
    if (mode < 3) {
        weapon_objects[0].active = 0x21;
        weapon_objects[0].id = 1;
        weapon_objects[0].unk15 = obj.unk15;
        weapon_objects[0].unk50 = (const u8*)&boxes[!toggle];
        weapon_objects[0].x_pos = obj.x_pos;
        weapon_objects[0].y_pos = obj.y_pos;
    }
    COPY(weapons_expected, weapon_objects);
    expected = obj;
    expected.unk5 = 2;
    expected.hp = mode == 3 ? 127 : 126;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.ext.main_6.hitbox_toggle = !toggle;
    expected.hurt_box = expected.attack_box = (const u8*)&boxes[!toggle];
    expected.unk42 = mode == 3 ? 0x1234 : 0x9234;
    if (mode < 3) {
        ((s16*)&weapons_expected[0].unk80)[0] = impact_x;
        ((s16*)&weapons_expected[0].unk80)[1] = impact_y;
        if (mode == 0) {
            expected.ext.main_6.armor_health = -1;
            expected.ext.main_6.armor_broken = 1;
            expected.unk6 = 0;
            expected.on_screen = 1;
            expected.contact_damage = 3;
            expected.terrain_box = &D_800FA430;
            expected.hurt_box = expected.attack_box = (const u8*)D_800FA434;
            expected.unk17 = 1;
            expected.previous_animation_index = 255;
            expected.animation_cursor = (const u8*)D_800FA4E8[1];
            expected.animation_step.packed = 0x08010002;
        } else {
            expected.ext.main_6.core_health = -1;
            expected.state = 2;
        }
        if (capacity) {
            struct VisualObj* hit = &visuals_expected[used++];
            hit->active = 0x21;
            hit->id = 3;
            hit->unk2 = 3;
            hit->animation_table = D_8011BF40;
            hit->unk42 = 0x7802;
            hit->unk3C = (u8*)directory + 16;
            hit->x_pos.i.hi = impact_x;
            hit->y_pos.i.hi = impact_y;
            hit->unk15 = obj.unk15 ^ 0x40;
        }
        for (i = 0; i < explosion_count[mode] && used < capacity; i++) {
            struct VisualObj* child = &visuals_expected[used++];
            child->active = 0x21;
            child->id = 4;
            child->unk5C.value = 1;
            child->unk16 = 1;
            child->x_pos.i.hi = x + (face ? -explosion_x[mode][i] : explosion_x[mode][i]);
            child->y_pos.i.hi = 120 + explosion_y[mode][i];
        }
    } else
        expected.state = 2;
    assert(((const u8*)D_801065F0)[2] == 0 && ((const u8*)D_801065F0)[3] == 1);
    D_8013E198[0] = D_8013E198[1] = D_8013E198[5] = -1;
    cur_random = 0x1234;
    SP_CUR_MAIN_OBJ = &obj;
    func_80046C8C(&obj);
    assert(SP_CUR_MAIN_OBJ == &obj);
    SP_CUR_MAIN_OBJ = current;
    SAME(obj, expected);
    SAME(g_Player, player_before);
    SAME(engine_obj, engine_before);
    SAME(background_objects, backgrounds_before);
    SAME(weapon_objects, weapons_expected);
    SAME(visual_objects, visuals_expected);
    SAME(misc_objects, misc_before);
    SAME(item_objects, items_before);
    assert(cur_random == (mode == 1 || mode == 2 ? 0xA30D : 0x1234));
    assert(TEST_SPRITE_FRAMES == (u8*)directory && directory[1] == 16 && directory[4] == 0x12345678 && directory[5] == 0x76543210);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "bulldozer_states", 0, 0, COUNT(bulldozer_states_cases), test_bulldozer_states },
    { "bulldozer_fall_1", 0, 0, 1, test_bulldozer_fall_1 },
    { "func_80046C8C", 0, 0, 1, test_func_80046C8C },
    { "armor_core_break_facing_explosion_positions_and_far_cleanup", NULL, NULL, 24, break_effects },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(bulldozer_states_cases) + 1 + 1 + 24;
