#include "test_runtime.h"
extern struct Unk_unk68 item_carrier_hitboxes;
extern struct Unk_unk68 item_carrier_capsule_hurtbox;

static u32 energy_priority(void)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u32 actual, i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    obj.active = 0x41;
    obj.id = 2;
    obj.state = -1;
    ((u8*)&obj.ext)[0] = 0x27;
    g_Player.weapon = 1;
    g_Player.hp = 20;
    g_Player.weapon_energy[1] = 10;
    engine_obj.max_hp = 48;
    before = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    func_80042950(&obj);
    actual = ((u8*)&obj.ext)[0] | ((u32)(u8)obj.active << 8) | ((u32)(u8)obj.state << 16);
    assert(actual == 0x4503u);
    before.active = obj.active;
    before.state = obj.state;
    ((u8*)&before.ext)[0] = ((u8*)&obj.ext)[0];
    for (i = 0; i < sizeof(obj); i++)
        assert(((u8*)&obj)[i] == ((u8*)&before)[i]);
    for (i = 0; i < sizeof(g_Player); i++)
        assert(((u8*)&g_Player)[i] == ((u8*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj); i++)
        assert(((u8*)&engine_obj)[i] == ((u8*)&engine_before)[i]);
    return actual;
}
static const CTestCase carrier_energy_priority_cases[] = { energy_priority };
static const u32 carrier_energy_priority_cases_expected[] = { 0x4503u };

struct func_80042950_case {
    u32 weapon, unk46, hp, weapon_energy_15;
    u32 expected[3];
};
static const struct func_80042950_case func_80042950_cases[] = {
    { 8, 0, 0, 0, { 1u, 4u, 1u } },
    { 15, -1, 1, 32, { 0u, 0u, 0u } },
};
static u32 test_func_80042950(u32 row)
{
    const struct func_80042950_case* c = &func_80042950_cases[row];
    u32 observed_values[3];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.weapon = c->weapon;
    engine_obj.max_hp = c->unk46;
    g_Player.hp = c->hp;
    g_Player.weapon_energy[15] = c->weapon_energy_15;
    func_80042950(&obj);
    observed_values[0] = (u32)((u8*)&obj.ext)[0];
    observed_values[1] = (u32)obj.active;
    observed_values[2] = (u32)obj.state;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

static const u32 func_80042AFC_expected[] = { 2u, 0u, 2u, 1u };
static u32 test_func_80042AFC(u32 row)
{
    u32 observed_values[4];
    struct MainObj obj;
    struct ItemObj items_before[32];
    struct Unk_unk68 attack;
    u8 pool_full;
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&weapon_objects, 0, sizeof(weapon_objects));

    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.spike_immune = 1;
    obj.active = 0x41;
    obj.id = 2;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    func_80042A48(&obj);
    memset(&attack, 0, sizeof(attack));
    D_8013E198[0] = -1;
    D_8013E198[1] = -1;
    D_8013E198[2] = -1;
    D_8013E198[3] = -1;
    D_8013E198[4] = -1;
    D_8013E198[5] = -1;
    pool_full = 1;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            item_objects[slot].active = pool_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pool_full ? 1 : 0;
    }
    memcpy(items_before, item_objects, sizeof(items_before));
    obj.unk2 = 2;
    obj.unk5 = 2;
    obj.unk6 = 3;
    obj.hurt_box = &item_carrier_capsule_hurtbox;
    attack.unk0 = -2;
    attack.unk1 = -2;
    attack.unk2 = 4;
    attack.unk3 = 4;
    weapon_objects[0].active = 1;
    weapon_objects[0].id = 0;
    weapon_objects[0].unk50 = (const u8*)&attack;
    weapon_objects[0].x_pos.val = obj.x_pos.val;
    weapon_objects[0].y_pos.val = obj.y_pos.val;
    func_80042AFC(&obj);
    c_test_same_words(item_objects, items_before, sizeof(item_objects));
    observed_values[0] = (u32)(u8)obj.state;
    observed_values[1] = (u32)(u8)obj.hp;
    observed_values[2] = (u32)(u8)obj.unk2;
    observed_values[3] = (u32)(u8)weapon_objects[0].unk98;
    return c_test_observe(0, row, observed_values, func_80042AFC_expected, 4);
}

static const u32 item_carrier_drop_fall_expected[] = { 3u, 0x640000u, 0x4F0000u, 0u, 0u, 0u, 4u };
static u32 test_item_carrier_drop_fall(u32 row)
{
    u32 observed_values[7];
    struct MainObj obj;
    u32 map_words[64], pixels_words[256], attributes[1];
    u32 map_before[64], pixels_before[256], attributes_before[1];
    struct MainObj landed_before;
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&weapon_objects, 0, sizeof(weapon_objects));

    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.spike_immune = 1;
    obj.active = 0x41;
    obj.id = 2;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    func_80042A48(&obj);
    memset(&map_words, 0, sizeof(map_words));
    memset(&pixels_words, 0, sizeof(pixels_words));
    memset(&attributes, 0, sizeof(attributes));
    SP_BG_TILEMAP = (u8*)map_words;
    TEST_BG_TILE_PIXELS = (void*)pixels_words;
    TEST_BG_TILE_ATTRS = (void*)attributes;
    layout_width = 16;
    layout_size = 256;
    memcpy(map_before, map_words, sizeof(map_before));
    memcpy(pixels_before, pixels_words, sizeof(pixels_before));
    memcpy(attributes_before, attributes, sizeof(attributes_before));
    obj.terrain_box = &item_carrier_hitboxes;
    obj.unk6 = 2;
    obj.collision_flags = 8;
    obj.air_state = 1;
    obj.y_speed = 65536;
    obj.gravity = 0x4200;
    item_carrier_drop_fall(&obj);
    landed_before = obj;
    item_carrier_drop(&obj);
    c_test_same_words(&obj, &landed_before, sizeof(obj));
    assert(obj.terrain_box == &item_carrier_hitboxes);
    c_test_same_words(map_words, map_before, sizeof(map_words));
    c_test_same_words(pixels_words, pixels_before, sizeof(pixels_words));
    c_test_same_words(attributes, attributes_before, sizeof(attributes));
    observed_values[0] = (u32)(u8)obj.unk6;
    observed_values[1] = (u32)obj.x_pos.val;
    observed_values[2] = (u32)obj.y_pos.val;
    observed_values[3] = (u32)(u8)obj.air_state;
    observed_values[4] = (u32)obj.collision_flags;
    observed_values[5] = (u32)obj.gravity;
    observed_values[6] = (u32)(u8)obj.unk17;
    return c_test_observe(0, row, observed_values, item_carrier_drop_fall_expected, 7);
}

static const u32 item_carrier_drop_start_expected[] = { 3u, 0x600000u, 0x500000u, 0u, 0xFu, 0x4200u };
static u32 test_item_carrier_drop_start(u32 row)
{
    u32 observed_values[6];
    struct MainObj obj;
    u32 map_words[64], pixels_words[256], attributes[1];
    u32 map_before[64], pixels_before[256], attributes_before[1];
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&weapon_objects, 0, sizeof(weapon_objects));

    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.spike_immune = 1;
    obj.active = 0x41;
    obj.id = 2;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    func_80042A48(&obj);
    memset(&map_words, 0, sizeof(map_words));
    memset(&pixels_words, 0, sizeof(pixels_words));
    memset(&attributes, 0, sizeof(attributes));
    SP_BG_TILEMAP = (u8*)map_words;
    TEST_BG_TILE_PIXELS = (void*)pixels_words;
    TEST_BG_TILE_ATTRS = (void*)attributes;
    layout_width = 16;
    layout_size = 256;
    map_words[0] = 0x01010101;
    attributes[0] = 0x38;
    memcpy(map_before, map_words, sizeof(map_before));
    memcpy(pixels_before, pixels_words, sizeof(pixels_before));
    memcpy(attributes_before, attributes, sizeof(attributes_before));
    obj.unk6 = 0;
    obj.unk18.val = 6291456;
    obj.unk1C.val = 5242880;
    item_carrier_drop_start(&obj);
    assert(obj.terrain_box == &item_carrier_hitboxes);
    c_test_same_words(map_words, map_before, sizeof(map_words));
    c_test_same_words(pixels_words, pixels_before, sizeof(pixels_words));
    c_test_same_words(attributes, attributes_before, sizeof(attributes));
    observed_values[0] = (u32)(u8)obj.unk6;
    observed_values[1] = (u32)obj.x_pos.val;
    observed_values[2] = (u32)obj.y_pos.val;
    observed_values[3] = (u32)(u8)obj.air_state;
    observed_values[4] = (u32)obj.collision_flags;
    observed_values[5] = (u32)obj.gravity;
    return c_test_observe(0, row, observed_values, item_carrier_drop_start_expected, 6);
}

struct item_carrier_hover_turn_case {
    u32 relative_step, obj_x_pos, g_Player_x_pos;
    u32 expected[3];
};
static const struct item_carrier_hover_turn_case item_carrier_hover_turn_cases[] = {
    { -1, 0, 0, { 0u, 0u, 0u } },
    { 0, -1, 1, { 0x40u, 0u, 0u } },
    { 0, 0, 0, { 0u, 0u, 0u } },
};
static u32 test_item_carrier_hover_turn(u32 row)
{
    const struct item_carrier_hover_turn_case* c = &item_carrier_hover_turn_cases[row];
    u32 observed_values[3];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.animation_step.fields.relative_step = c->relative_step;
    obj.x_pos.val = c->obj_x_pos;
    g_Player.x_pos.val = c->g_Player_x_pos;
    item_carrier_hover_turn(&obj);
    observed_values[0] = (u32)obj.unk15;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

struct item_carrier_leave_up_case {
    u32 unk7, on_screen;
    u32 expected[4];
};
static const struct item_carrier_leave_up_case item_carrier_leave_up_cases[] = {
    { 0, 0, { 0u, 1u, 0u, 0x10000u } },
    { -1, 0, { 1u, 0xFFFFFFFFu, 0u, 0u } },
    { -1, -1, { 0u, 0xFFFFFFFFu, 0u, 0u } },
};
static u32 test_item_carrier_leave_up(u32 row)
{
    const struct item_carrier_leave_up_case* c = &item_carrier_leave_up_cases[row];
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk7 = c->unk7;
    obj.on_screen = c->on_screen;
    item_carrier_leave_up(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk7;
    observed_values[2] = (u32)obj.x_speed;
    observed_values[3] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

const struct CTestGroup c_test_groups[] = {
    { "carrier_energy_priority", carrier_energy_priority_cases, carrier_energy_priority_cases_expected, COUNT(carrier_energy_priority_cases), 0 },
    { "func_80042950", 0, 0, 2, test_func_80042950 },
    { "func_80042AFC", 0, 0, 1, test_func_80042AFC },
    { "item_carrier_drop_fall", 0, 0, 1, test_item_carrier_drop_fall },
    { "item_carrier_drop_start", 0, 0, 1, test_item_carrier_drop_start },
    { "item_carrier_hover_turn", 0, 0, 3, test_item_carrier_hover_turn },
    { "item_carrier_leave_up", 0, 0, 3, test_item_carrier_leave_up },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(carrier_energy_priority_cases) + 2 + 1 + 1 + 1 + 3 + 3;
