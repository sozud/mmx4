#include "test_runtime.h"
#include "main/sprite_animations.h"
#include "main/player_check.h"
#include "main/player.h"
#include "main/weapons/weapon_00_lemon.h"
#include "main/55C4.h"
extern struct Unk_unk68 frost_tower_charged_part_box[];
extern struct Unk_unk68 frost_tower_terrain_box[];

void frost_tower_charged_update(struct WeaponObj*);
void frost_tower_charged_part_main(struct WeaponObj*);
void ground_hunter_charged_update(struct WeaponObj*);
void nova_strike_hitbox_update(struct WeaponObj*);
extern struct Unk_unk68 ground_hunter_charged_hit_box[];
extern struct Unk_unk68 ground_hunter_charged_shot_box[];

static u32 gfx[64], frames[64];
static struct WeaponObj expected;
static struct WeaponObj weapons_before[16];
static struct MiscObj misc_before[64];
static struct PlayerObj player_expected, entity_before;
static struct EngineObj engine_before;
static struct MainBssState main_before;
static struct BackgroundObj backgrounds_before[3];

static const struct {
    s16 x, y;
} cameras[] = {
    { 0, 0 },
    { 1024, 512 },
    { -320, -240 },
};
static const struct {
    s16 x, y;
} edges[] = {
    { 160, 120 },
    { -40, 120 },
    { -41, 120 },
    { 359, 120 },
    { 360, 120 },
    { 160, -56 },
    { 160, -57 },
    { 160, 295 },
    { 160, 296 },
};
static const struct {
    s16 x, y;
} hunter_edges[] = {
    { 160, 120 },
    { -44, 120 },
    { -45, 120 },
    { 363, 120 },
    { 364, 120 },
    { 160, -24 },
    { 160, -25 },
    { 160, 263 },
    { 160, 264 },
};

static void prepare(struct WeaponObj* obj, u32 layer, u32 profile)
{
    u32 i;
    memset(obj, 0x25, sizeof(*obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&g_Entity, 0x35, sizeof(g_Entity));
    memset(&engine_obj, 0x45, sizeof(engine_obj));
    memset(&main_bss_state, 0x55, sizeof(main_bss_state));
    memset(background_objects, 0x65, sizeof(background_objects));
    memset(weapon_objects, 0x75, sizeof(weapon_objects));
    memset(misc_objects, 0x35, sizeof(misc_objects));
    memset(gfx, 0x35, sizeof(gfx));
    memset(frames, 0x35, sizeof(frames));
    for (i = 0; i < 16; i++)
        gfx[i] = frames[i] = 0x80 + i * 4;
    for (i = 0; i < 3; i++) {
        background_objects[i].x_pos.val = cameras[(profile + i) % 3].x * 65536;
        background_objects[i].y_pos.val = cameras[(profile + i) % 3].y * 65536;
    }
    TEST_PLAYER_GFX = (u8*)gfx;
    TEST_SPRITE_FRAMES = (u8*)frames;
    obj->active = 1;
    obj->id = 11;
    obj->unk2 = 1;
    obj->state = 0;
    obj->on_screen = 1;
    obj->bg_offset = layer;
    obj->owner = &g_Player;
    obj->x_pos.val = (background_objects[layer].x_pos.i.hi + 160) * 65536 + 0x1234;
    obj->y_pos.val = (background_objects[layer].y_pos.i.hi + 120) * 65536 + 0x5678;
    obj->unk50 = frost_tower_charged_part_box;
    obj->unk68 = frost_tower_terrain_box;
    g_Player.active = 0x41;
    g_Player.state = PLAYER_STATE_NORMAL;
    g_Player.hp = 24;
    g_Player.bg_offset = layer;
    g_Player.weapon = 2;
    g_Player.shot_count = 3;
    g_Player.special_shot_count = 2;
    g_Player.x_pos.val = (background_objects[layer].x_pos.i.hi + 160) * 65536 + 0x8765;
    g_Player.y_pos.val = (background_objects[layer].y_pos.i.hi + 120) * 65536 + 0x4321;
    controller_input.held = 0x1234;
    controller_input.previous = 0x5678;
    controller_input.pressed = 0x840;
    need_palette_load = 0x20;
    cur_random = 0x1234;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
}

static void capture(const struct WeaponObj* obj)
{
    expected = *obj;
    player_expected = g_Player;
    entity_before = g_Entity;
    engine_before = engine_obj;
    main_before = main_bss_state;
    c_test_copy_words((u32*)backgrounds_before, (const u32*)background_objects, sizeof(backgrounds_before) / 4);
    c_test_copy_words((u32*)weapons_before, (const u32*)weapon_objects, sizeof(weapons_before) / 4);
    c_test_copy_words((u32*)misc_before, (const u32*)misc_objects, sizeof(misc_before) / 4);
}

static void check(const struct WeaponObj* obj)
{
    u32 i;
    c_test_same_words(obj, &expected, sizeof(expected));
    c_test_same_words(&g_Player, &player_expected, sizeof(player_expected));
    c_test_same_words(&g_Entity, &entity_before, sizeof(entity_before));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_before));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_before));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(c_test_word_difference((const u32*)weapon_objects,
               (const u32*)weapons_before, sizeof(weapons_before) / 4)
        == 0);
    assert(c_test_word_difference((const u32*)misc_objects,
               (const u32*)misc_before, sizeof(misc_before) / 4)
        == 0);
    assert(controller_input.held == 0x1234 && controller_input.previous == 0x5678
        && controller_input.pressed == 0x840);
    assert(need_palette_load == 0x20 && cur_random == 0x1234);
    assert(TEST_PLAYER_GFX == (u8*)gfx && TEST_SPRITE_FRAMES == (u8*)frames);
    for (i = 0; i < 64; i++) {
        assert(gfx[i] == (i < 16 ? 0x80 + i * 4 : 0x35353535));
        assert(frames[i] == gfx[i]);
    }
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
}

static u32 visible(const struct WeaponObj* obj, s32 x_margin, s32 y_margin)
{
    s16 x = (u16)obj->x_pos.i.hi - backgrounds_before[(u8)obj->bg_offset].x_pos.u.hi;
    s16 y = (u16)obj->y_pos.i.hi - backgrounds_before[(u8)obj->bg_offset].y_pos.u.hi;
    return x >= -x_margin && x < 320 + x_margin && y >= -y_margin && y < 240 + y_margin;
}

static void expect_animation(u32** table, u32 animation)
{
    expected.animation_table = table;
    expected.unk17 = animation;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = table[animation];
    expected.animation_step.packed = *table[animation];
}

static const s8 part_types[] = { 1, 2, -126, 3, -125, 4, -124, 5, -123 };
static const u16 part_offsets[] = { 0, 0, 64, 96, 40, 112 };
static const u32 frost_animation[] = {
    0x09010001, 0x0A010001, 0x0B010001, 0x0C010001, 0x09010001, 0x0A010001, 0x0B010001, 0x0C010001,
    0x09010001, 0x0D010001, 0x0E010001, 0x0F010001, 0x10010002, 0x11010002, 0x12010002, 0x13010002,
    0x1401010F, 0x14010202, 0x14000060
};

static u32 test_frost_init(u32 row)
{
    struct WeaponObj obj;
    u32 type = row % COUNT(part_types), layer = row / COUNT(part_types) % 3;
    u16 base;
    prepare(&obj, layer, row / (3 * COUNT(part_types)));
    obj.unk2 = part_types[type];
    g_Player.unk15 = row % 2 ? 0x40 : 0;
    capture(&obj);
    expected.on_screen = 1;
    expected.unk38 = (u8*)gfx + 0x8C;
    expected.unk3C = (u8*)frames + 0xAC;
    expected.unk40 = 0x520;
    expected.unk42 = 0x7801;
    expected.unk16 = 1;
    expected.unk15 = 0;
    base = background_objects[layer].x_pos.u.hi + 160;
    expected.x_pos.u.hi = base + (part_types[type] < 0 ? -part_offsets[part_types[type] & 0x7F] : part_offsets[part_types[type]]);
    expected.y_pos.u.hi = background_objects[layer].y_pos.u.hi + 48;
    expected.x_vel.val = expected.unk28.val = expected.unk2C = 0;
    expected.y_vel.val = -0x80000;
    expected.unk5 = 0;
    expected.state = 1;
    expect_animation(D_8011C094, 6);
    frost_tower_charged_update(&obj);
    check(&obj);
    return 1;
}

static void expect_frost_tick(void)
{
    u32 frame;
    if (expected.state == 3) {
        expected.unk50 = expected.unk68 = NULL;
        memset(&expected, 0, 8);
        player_expected.shot_count--;
        player_expected.special_shot_count--;
        return;
    }
    if (!visible(&expected, 40, 56)) {
        expected.on_screen = 0;
        expected.state = 3;
        expected.unk50 = expected.unk68 = NULL;
        return;
    }
    if (--expected.animation_step.fields.duration == 0) {
        frame = expected.animation_cursor - D_8011C094[6];
        if (frame != 18)
            frame++;
        expected.animation_cursor = D_8011C094[6] + frame;
        expected.animation_step.packed = frost_animation[frame];
    }
    if (expected.unk5 == 0) {
        if (expected.animation_step.fields.event == 1) {
            expected.animation_step.fields.event = 0;
            expected.unk50 = frost_tower_charged_part_box;
            expected.unk64 = 1;
        }
        if (expected.animation_step.fields.event == 2) {
            expected.animation_step.fields.event = 0;
            expected.unk5 = 1;
        }
    } else {
        expected.x_pos.val += expected.x_vel.val;
        expected.y_pos.val -= expected.y_vel.val;
    }
    expected.on_screen = visible(&expected, 40, 56);
}

static u32 test_frost_lifecycle(u32 row)
{
    static const u8 ticks[] = { 20, 35, 36, 68 };
    struct WeaponObj obj;
    u32 type = row % COUNT(part_types), layer = row / COUNT(part_types) % 3;
    u32 tick, count = ticks[row / (3 * COUNT(part_types))];
    prepare(&obj, layer, layer);
    obj.unk2 = part_types[type];
    frost_tower_charged_update(&obj);
    capture(&obj);
    for (tick = 0; tick < count; tick++) {
        expect_frost_tick();
        frost_tower_charged_update(&obj);
        assert(c_test_word_difference((const u32*)&obj,
                   (const u32*)&expected, sizeof(expected) / 4)
            == 0);
    }
    check(&obj);
    for (tick = 0; tick < COUNT(frost_animation); tick++)
        assert(D_8011C094[6][tick] == frost_animation[tick]);
    return 1;
}

static u32 test_frost_edges(u32 row)
{
    struct WeaponObj obj;
    u32 edge = row % COUNT(edges), layer = row / COUNT(edges) % 3;
    u32 moving = row / (3 * COUNT(edges));
    prepare(&obj, layer, layer);
    frost_tower_charged_update(&obj);
    obj.x_pos.i.hi = background_objects[layer].x_pos.i.hi + edges[edge].x;
    obj.y_pos.i.hi = background_objects[layer].y_pos.i.hi + edges[edge].y;
    obj.unk5 = moving;
    set_animation_frame(ANIMATED_OBJECT(&obj), 6, moving ? 18 : 16);
    capture(&obj);
    expect_frost_tick();
    frost_tower_charged_part_main(&obj);
    check(&obj);
    return 1;
}

static u32 test_nova_hitbox(u32 row)
{
    static const u8 timers[] = { 0, 1, 2, 4 };
    struct WeaponObj obj;
    u32 phase, layer, facing, timer = 0, counter = 0, cancellation = row >= 60;
    if (row < 12) {
        phase = 0;
        layer = row % 3;
        facing = row / 6;
    } else if (row < 60) {
        u32 index = row - 12;
        phase = 1;
        timer = timers[index % 4];
        counter = index / 4 % 2 ? 4 : 1;
        facing = index / 8 % 2;
        layer = index / 16;
    } else {
        u32 index = row - 60;
        phase = index / 2 % 2;
        facing = index / 4 % 2;
        layer = index / 8;
    }
    prepare(&obj, layer, row % 3);
    obj.id = 22;
    obj.unk2 = 0;
    obj.state = phase;
    obj.ext.raw[0] = row < 12 ? 0xA5 : timer;
    obj.unk64 = row < 12 ? 0xA5 : counter;
    g_Player.unk17 = cancellation ? (row % 2 ? 5 : 0xB) : 0x6A;
    g_Player.unk15 = facing ? 0x40 : 0;
    capture(&obj);
    if (cancellation) {
        memset(&expected, 0, 8);
    } else {
        if (phase == 0) {
            expected.unk50 = nova_strike_hit_box;
            expected.unk64 = 1;
            expected.ext.raw[0] = 4;
            expected.state = 1;
        } else if (timer == 0) {
            expected.ext.raw[0] = 4;
            expected.unk64 = counter + 1;
        } else {
            expected.ext.raw[0] = timer - 1;
        }
        expected.x_pos = g_Player.x_pos;
        expected.y_pos = g_Player.y_pos;
        expected.unk15 = g_Player.unk15;
    }
    nova_strike_hitbox_update(&obj);
    check(&obj);
    return 1;
}

static u32 test_hunter_init(u32 row)
{
    static const u8 player_frames[] = { 0, 0x30, 0x50 };
    struct WeaponObj obj;
    u32 type = row % 3, facing = row / 3 % 2, layer = row / 6 % 3;
    u32 frame = player_frames[row / 18];
    s16 dx, dy;
    prepare(&obj, layer, layer);
    obj.id = 14;
    obj.unk2 = type;
    g_Player.weapon = 5;
    g_Player.unk15 = facing ? 0x40 : 0;
    g_Player.animation_step.fields.frame_index = frame;
    capture(&obj);
    expected.on_screen = 1;
    expected.unk38 = (u8*)gfx + 0x98;
    expected.unk3C = (u8*)frames + 0xB8;
    expected.unk40 = 0x520;
    expected.unk42 = 0x7801;
    expected.x_vel.val = expected.unk28.val = expected.y_vel.val = expected.unk2C = 0;
    expected.unk15 = g_Player.unk15;
    expect_animation(D_8011C0C8, type + 3);
    expected.state = 1;
    if (type == 0) {
        expected.unk16 = 0;
        expected.unk50 = ground_hunter_charged_hit_box;
        expected.unk64 = 1;
        dx = D_8011B230.components[frame * 2];
        dy = D_8011B230.components[frame * 2 + 1];
        expected.x_pos.u.hi = g_Player.x_pos.u.hi + (facing ? -dx : dx);
        expected.y_pos.u.hi = g_Player.y_pos.u.hi + dy;
        expected.x_vel.val = facing ? 0x60000 : -0x60000;
        expected.unk5 = 0;
    } else {
        expected.unk50 = ground_hunter_charged_shot_box;
        expected.unk16 = 1;
        expected.unk64 = 0;
        expected.y_vel.val = type == 1 ? 0x80000 : -0x80000;
        expected.unk5 = 2;
    }
    expected.on_screen = visible(&expected, 44, 24);
    ground_hunter_charged_update(&obj);
    check(&obj);
    return 1;
}

static u32 test_hunter_cancel(u32 row)
{
    struct WeaponObj obj;
    u32 mask = row % 7 + 1, type = row / 7 % 3, layer = row / 21;
    prepare(&obj, layer, layer);
    obj.id = 14;
    obj.unk2 = type;
    obj.state = 1;
    g_Player.input_locked = (mask & 1) != 0;
    g_Player.capsule_state = (mask & 2) != 0;
    g_Player.weapon = mask & 4 ? 0 : 5;
    capture(&obj);
    memset(&expected, 0, 8);
    expected.unk50 = expected.unk68 = NULL;
    player_expected.shot_count--;
    player_expected.special_shot_count--;
    ground_hunter_charged_update(&obj);
    check(&obj);
    return 1;
}

static void hunter_main_expected(u32 hit)
{
    if (!visible(&expected, 44, 24)) {
        expected.on_screen = 0;
        expected.state = 3;
        expected.unk50 = expected.unk68 = NULL;
        return;
    }
    expected.animation_cursor++;
    expected.animation_step.packed = *expected.animation_cursor;
    expected.x_pos.val += expected.x_vel.val;
    expected.y_pos.val -= expected.y_vel.val;
    if (expected.unk5 == 0) {
        if (player_expected.input.buttons.held & 0xC) {
            expected.ext.weapon_14.unk8C = 0;
            expected.ext.weapon_14.unk8D = 5;
            expected.unk5 = 1;
        }
    } else if (hit) {
        expected.on_screen = 0;
        expected.state = 3;
        expected.unk50 = expected.unk68 = NULL;
        return;
    }
    expected.on_screen = visible(&expected, 44, 24);
}

static u32 test_hunter_wait(u32 row)
{
    static const u16 inputs[] = { 0, PLAYER_INPUT_UP, PLAYER_INPUT_DOWN,
        PLAYER_INPUT_UP | PLAYER_INPUT_DOWN, PLAYER_INPUT_LEFT };
    struct WeaponObj obj;
    u32 edge = row % COUNT(hunter_edges), input = row / COUNT(hunter_edges) % COUNT(inputs);
    u32 layer = row % 3;
    prepare(&obj, layer, layer);
    obj.id = 14;
    obj.unk2 = 0;
    g_Player.weapon = 5;
    g_Player.unk15 = row / (COUNT(hunter_edges) * COUNT(inputs)) ? 0x40 : 0;
    ground_hunter_charged_update(&obj);
    obj.x_pos.i.hi = background_objects[layer].x_pos.i.hi + hunter_edges[edge].x;
    obj.y_pos.i.hi = background_objects[layer].y_pos.i.hi + hunter_edges[edge].y;
    g_Player.input.buttons.held = inputs[input];
    capture(&obj);
    hunter_main_expected(0);
    ground_hunter_charged_update(&obj);
    check(&obj);
    return 1;
}

static u32 test_hunter_shot(u32 row)
{
    struct WeaponObj obj;
    u32 edge = row % COUNT(hunter_edges), hit = row / COUNT(hunter_edges) % 2;
    u32 type = row / (2 * COUNT(hunter_edges)) % 2 + 1, layer = row % 3;
    prepare(&obj, layer, layer);
    obj.id = 14;
    obj.unk2 = type;
    g_Player.weapon = 5;
    g_Player.unk15 = row / (4 * COUNT(hunter_edges)) ? 0x40 : 0;
    ground_hunter_charged_update(&obj);
    obj.x_pos.i.hi = background_objects[layer].x_pos.i.hi + hunter_edges[edge].x;
    obj.y_pos.i.hi = background_objects[layer].y_pos.i.hi + hunter_edges[edge].y;
    obj.unk98 = hit;
    capture(&obj);
    hunter_main_expected(hit);
    ground_hunter_charged_update(&obj);
    check(&obj);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "frost_part_initialization", 0, 0, 3, test_frost_init },
    { "frost_part_lifecycle", 0, 0, 57, test_frost_lifecycle },
    { "frost_part_viewport_edges", 0, 0, 3, test_frost_edges },
    { "nova_hitbox_interval", 0, 0, 66, test_nova_hitbox },
    { "charged_hunter_initialization", 0, 0, 3, test_hunter_init },
    { "charged_hunter_cancellation", 0, 0, 7, test_hunter_cancel },
    { "charged_hunter_wait", 0, 0, 90, test_hunter_wait },
    { "charged_hunter_shot", 0, 0, 10, test_hunter_shot },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 3 + 57 + 3 + 66 + 3 + 7 + 90 + 10;
