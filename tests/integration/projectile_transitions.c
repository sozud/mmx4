#include "test_runtime.h"
#include "main/sprite_animations.h"
#include "main/player.h"
#include "main/player_check.h"
#include "main/55C4.h"

void ground_hunter_main(struct WeaponObj*);
void ground_hunter_update(struct WeaponObj*);
void func_800981CC(struct WeaponObj*);
extern struct Unk_unk68 ground_hunter_crawl_box[];
extern struct Unk_unk68 ground_hunter_rise_box[];
extern struct Unk_unk68 ground_hunter_terrain_box[];
extern struct Unk_unk68 rakuhouha_orb_box[];

static u32 sprite_archive[64];
static struct WeaponObj expected, weapons_before[16];
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
} hunter_edges[] = {
    { 160, 120 },
    { -44, 120 },
    { -45, 120 },
    { 363, 120 },
    { 364, 120 },
    { 160, -32 },
    { 160, -33 },
    { 160, 271 },
    { 160, 272 },
};
static const struct {
    s16 x, y;
} orb_edges[] = {
    { 160, 120 },
    { -32, 120 },
    { -33, 120 },
    { 351, 120 },
    { 352, 120 },
    { 160, -32 },
    { 160, -33 },
    { 160, 271 },
    { 160, 272 },
};

static void prepare(struct WeaponObj* obj, u32 layer, u32 facing)
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
    memset(sprite_archive, 0x35, sizeof(sprite_archive));
    for (i = 0; i < 16; i++)
        sprite_archive[i] = 0x80 + i * 4;
    for (i = 0; i < 3; i++) {
        background_objects[i].x_pos.val = cameras[i].x * 65536;
        background_objects[i].y_pos.val = cameras[i].y * 65536;
    }
    TEST_SPRITE_FRAMES = (u8*)sprite_archive;
    obj->active = 1;
    obj->id = 5;
    obj->unk2 = 0;
    obj->on_screen = 1;
    obj->state = 1;
    obj->bg_offset = layer;
    obj->unk15 = facing ? 0x40 : 0;
    obj->x_pos.val = (cameras[layer].x + 160) * 65536 + 0x1234;
    obj->y_pos.val = (cameras[layer].y + 120) * 65536 + 0x5678;
    obj->unk50 = ground_hunter_crawl_box;
    obj->unk68 = ground_hunter_terrain_box;
    obj->unk67 = 1;
    obj->unk70 = 0;
    obj->unk98 = 0;
    obj->owner = &g_Player;
    obj->animation_table = D_8011C0C8;
    g_Player.active = 0x41;
    g_Player.state = PLAYER_STATE_NORMAL;
    g_Player.hp = 24;
    g_Player.weapon = 5;
    g_Player.bg_offset = layer;
    g_Player.unk15 = obj->unk15;
    g_Player.shot_count = 3;
    g_Player.special_shot_count = 2;
    g_Player.x_pos.val = (cameras[layer].x + 160) * 65536 + 0x8765;
    g_Player.y_pos.val = (cameras[layer].y + 120) * 65536 + 0x4321;
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
    assert(TEST_SPRITE_FRAMES == (u8*)sprite_archive);
    for (i = 0; i < COUNT(sprite_archive); i++)
        assert(sprite_archive[i] == (i < 16 ? 0x80 + i * 4 : 0x35353535));
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
}

static u32 visible(const struct WeaponObj* obj, s32 x_margin, s32 y_margin)
{
    s16 x = obj->x_pos.u.hi - backgrounds_before[(u8)obj->bg_offset].x_pos.u.hi;
    s16 y = obj->y_pos.u.hi - backgrounds_before[(u8)obj->bg_offset].y_pos.u.hi;
    return x >= -x_margin && x < 320 + x_margin && y >= -y_margin && y < 240 + y_margin;
}

static void hunter_animation(u32 animation)
{
    expected.unk17 = animation;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = D_8011C0C8[animation];
    expected.animation_step.packed = *expected.animation_cursor;
}

enum { KEEP,
    CRAWL,
    RISE,
    BURST };
static void hunter_transition(u32 transition)
{
    if (transition == RISE) {
        hunter_animation(2);
        expected.unk67 = 1;
        expected.x_vel.val = 0;
        expected.y_vel.val = -0x60000;
        expected.unk5 = 2;
    } else if (transition == CRAWL) {
        hunter_animation(1);
        expected.unk67 = 0;
        expected.x_vel.val = expected.unk15 ? 0x60000 : -0x60000;
        expected.y_vel.val = 0;
        expected.unk5 = 1;
    } else if (transition == BURST) {
        hunter_animation(6);
        expected.x_vel.val = expected.y_vel.val = 0;
        expected.unk50 = expected.unk68 = NULL;
        expected.state = 2;
        expected.unk5 = 0;
    }
}

static void hunter_expected(void)
{
    u32 phase = expected.unk5, flags = expected.unk70;
    u32 wall = flags & (expected.unk15 ? PLAYER_COLLIDE_RIGHT : PLAYER_COLLIDE_LEFT);
    u32 ground = flags & PLAYER_COLLIDE_GROUND, move = 1, transition = KEEP;
    if (!visible(&expected, 44, 32) || expected.unk98) {
        expected.on_screen = 0;
        expected.state = 3;
        expected.unk50 = expected.unk68 = NULL;
        return;
    }
    expected.animation_step.fields.duration--;
    if (phase == 2) {
        if (ground)
            transition = wall ? BURST : CRAWL;
    } else if (wall) {
        transition = ground ? BURST : RISE;
        move = 0;
    } else if (phase == 0) {
        if (player_expected.input.buttons.held & PLAYER_INPUT_DOWN)
            transition = RISE;
        if (ground)
            transition = CRAWL;
    } else if (!ground) {
        transition = RISE;
    }
    hunter_transition(transition);
    if (move) {
        expected.x_pos.val += expected.x_vel.val;
        expected.y_pos.val -= expected.y_vel.val;
    }
    expected.on_screen = visible(&expected, 44, 32);
    if (expected.unk50 != NULL)
        expected.unk50 = expected.unk17 == 2 ? ground_hunter_rise_box : ground_hunter_crawl_box;
}

static void hunter_phase(struct WeaponObj* obj, u32 phase)
{
    obj->unk5 = phase;
    obj->x_vel.val = phase == 2 ? 0 : (obj->unk15 ? 0x60000 : -0x60000);
    obj->y_vel.val = phase == 0 ? -0x20000 : phase == 1 ? 0
                                                        : -0x60000;
    obj->unk28.val = obj->unk2C = 0;
    set_animation(obj, phase);
}

static u32 test_hunter_flags(u32 row)
{
    struct WeaponObj obj;
    u32 flags = row % 16, step = row / 16, down = step == 1, facing = step == 2;
    u32 phase = step < 3 ? 0 : step - 2, layer = (flags + phase + facing) % 3;
    prepare(&obj, layer, facing);
    hunter_phase(&obj, phase);
    obj.unk70 = flags;
    if (flags & PLAYER_COLLIDE_CEILING)
        obj.unk50 = NULL;
    g_Player.input.buttons.held = down ? PLAYER_INPUT_DOWN : 0;
    capture(&obj);
    hunter_expected();
    ground_hunter_main(&obj);
    check(&obj);
    return 1;
}

static u32 test_hunter_edges(u32 row)
{
    struct WeaponObj obj;
    u32 edge = row % COUNT(hunter_edges), hit = row / COUNT(hunter_edges) % 2;
    u32 facing = row / (2 * COUNT(hunter_edges)) % 2;
    u32 phase = row / (4 * COUNT(hunter_edges)), layer = row % 3;
    prepare(&obj, layer, facing);
    hunter_phase(&obj, phase);
    obj.unk70 = phase == 1 ? PLAYER_COLLIDE_GROUND : 0;
    obj.unk98 = hit;
    obj.x_pos.i.hi = cameras[layer].x + hunter_edges[edge].x;
    obj.y_pos.i.hi = cameras[layer].y + hunter_edges[edge].y;
    capture(&obj);
    hunter_expected();
    ground_hunter_main(&obj);
    check(&obj);
    return 1;
}

static u32 test_hunter_locked(u32 row)
{
    struct WeaponObj obj;
    u32 state = row % 3, facing = row / 3 % 2, layer = row / 6;
    prepare(&obj, layer, facing);
    obj.state = state;
    obj.unk70 = 0xA5;
    assert(MMX4_OFFSET_OF(struct PlayerObj, touching_spikes) < sizeof(obj));
    ((u8*)&obj)[MMX4_OFFSET_OF(struct PlayerObj, touching_spikes)] = 0x27;
    g_Player.input_locked = 1;
    capture(&obj);
    expected.unk18 = expected.x_pos;
    expected.unk1C = expected.y_pos;
    memset(&expected, 0, 8);
    expected.unk50 = expected.unk68 = NULL;
    expected.unk70 = 0;
    ((u8*)&expected)[MMX4_OFFSET_OF(struct PlayerObj, touching_spikes)] = 0;
    player_expected.shot_count--;
    player_expected.special_shot_count--;
    ground_hunter_update(&obj);
    check(&obj);
    return 1;
}

static const struct {
    s32 x, y;
} orb_directions[] = {
    { -0x10000, 0 },
    { -0xEC83, 0x61F7 },
    { -0xB505, 0xB505 },
    { -0x61F7, 0xEC83 },
    { 0, 0x10000 },
    { 0x61F7, 0xEC83 },
    { 0xB505, 0xB505 },
    { 0xEC83, 0x61F7 },
    { 0x10000, 0 },
};

static u32 orb_frame(u32 direction, u32 frame)
{
    u32 sprite = frame == 0 ? 0x1B + direction : frame == 1 ? 0x24
                                                            : 0x23 + direction * 4 + frame;
    return (sprite << 24) | (frame == 5 ? 0xFD0001 : 0x010001);
}

static void orb_prepare(struct WeaponObj* obj, u32 direction, u32 layer)
{
    prepare(obj, layer, 0);
    obj->active = 0x21;
    obj->id = 36;
    obj->unk2 = direction;
    obj->state = 0;
    g_Player.unk2 = 1;
    g_Player.weapon = 0;
}

static void orb_birth(u32 direction)
{
    expected.on_screen = 1;
    expected.unk50 = rakuhouha_orb_box;
    expected.animation_table = D_8011C018;
    expected.unk42 = 0x7803;
    expected.unk16 = 1;
    expected.unk40 = 0;
    expected.unk3C = (u8*)sprite_archive + 0x98;
    expected.x_pos.u.hi = player_expected.x_pos.u.hi;
    expected.y_pos.u.hi = player_expected.y_pos.u.hi + 21;
    expected.unk15 = 0;
    expected.x_vel.val = orb_directions[direction].x * 7;
    expected.y_vel.val = orb_directions[direction].y * 7;
    expected.unk17 = direction + 10;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = D_8011C018[direction + 10];
    expected.animation_step.packed = orb_frame(direction, 0);
    expected.x_pos.val += expected.x_vel.val * 3;
    expected.y_pos.val -= expected.y_vel.val * 3;
    expected.state = 1;
    expected.on_screen = visible(&expected, 32, 32);
}

static void orb_tick(u32 direction)
{
    u32 frame;
    if (!visible(&expected, 32, 32) || expected.unk98) {
        memset(&expected, 0, 8);
        return;
    }
    frame = expected.animation_cursor - (u32*)D_8011C018[direction + 10];
    frame = frame == 5 ? 2 : frame + 1;
    expected.animation_cursor = D_8011C018[direction + 10] + frame;
    expected.animation_step.packed = orb_frame(direction, frame);
    expected.x_pos.val += expected.x_vel.val;
    expected.y_pos.val -= expected.y_vel.val;
    expected.on_screen = visible(&expected, 32, 32);
}

static u32 test_orb_birth(u32 row)
{
    struct WeaponObj obj;
    u32 direction = row % 9, layer = row / 9 % 3;
    orb_prepare(&obj, direction, layer);
    if (row / 27) {
        obj.x_pos.u.lo = 0;
        obj.y_pos.u.lo = 0;
    }
    capture(&obj);
    orb_birth(direction);
    func_800981CC(&obj);
    check(&obj);
    return 1;
}

static u32 test_orb_timeline(u32 row)
{
    static const u8 ticks[] = { 1, 2, 5, 6, 15, 32, 60 };
    struct WeaponObj obj;
    u32 direction = row % 9, layer = row / 9 % 3, count = ticks[row / 27];
    u32 tick, frame;
    orb_prepare(&obj, direction, layer);
    capture(&obj);
    orb_birth(direction);
    func_800981CC(&obj);
    for (tick = 0; tick < count && expected.active; tick++) {
        orb_tick(direction);
        func_800981CC(&obj);
        assert(c_test_word_difference((const u32*)&obj,
                   (const u32*)&expected, sizeof(expected) / 4)
            == 0);
    }
    check(&obj);
    if (count == 60)
        assert(obj.active == 0 && obj.on_screen == 0);
    for (frame = 0; frame < 6; frame++)
        assert(D_8011C018[direction + 10][frame].packed == orb_frame(direction, frame));
    return 1;
}

static u32 test_orb_edges(u32 row)
{
    struct WeaponObj obj;
    u32 edge = row % COUNT(orb_edges), hit = row / COUNT(orb_edges) % 2;
    u32 direction = row / (2 * COUNT(orb_edges)), layer = row % 3;
    orb_prepare(&obj, direction, layer);
    func_800981CC(&obj);
    obj.x_pos.i.hi = cameras[layer].x + orb_edges[edge].x;
    obj.y_pos.i.hi = cameras[layer].y + orb_edges[edge].y;
    obj.unk98 = hit;
    capture(&obj);
    orb_tick(direction);
    func_800981CC(&obj);
    check(&obj);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "ground_hunter_contact_transitions", 0, 0, 80, test_hunter_flags },
    { "ground_hunter_viewport_collision", 0, 0, 92, test_hunter_edges },
    { "ground_hunter_input_lock", 0, 0, 3, test_hunter_locked },
    { "rakuhouha_launch", 0, 0, 9, test_orb_birth },
    { "rakuhouha_lifecycle", 0, 0, 9, test_orb_timeline },
    { "rakuhouha_viewport_collision", 0, 0, 94, test_orb_edges },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 80 + 92 + 3 + 9 + 9 + 94;
