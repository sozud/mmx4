#include "test_runtime.h"
#include "support/state_cases.h"
#include "support/player_cases.h"
#include "main/sprite_animations.h"
#include "main/55C4.h"
#include "main/weapons/weapon_00_lemon.h"
void stock_shot_init(struct WeaponObj*);

#define sw state_room.weapon
#define STOCK(facing) (player_reset(1, 0, 0), memset(&state_room, 0, sizeof(state_room)), memset(&shot_objects[0], 0, sizeof(shot_objects[0])), memset(&effect_objects[0], 0, sizeof(effect_objects[0])), pl.unk15 = facing, sw.active = 1, sw.id = 0x13, sw.owner = &g_Player, stock_shot_init(&sw))
static void sts_init_left(void)
{
    STOCK(0);
}
static void sts_init_right(void) { STOCK(0x40); }

static void (*const stock_shot_init_states_cases[])(void) = {
    sts_init_left,
    sts_init_right,
};
static const u32 stock_shot_init_states_expected[] = { 1u, 0xFF000021u, 0u, 0u, 0xFFF60000u, 0u, 0u, 0x27802u, 0u, 0u, 1u, 0xFF400021u, 0u, 0u, 0xA0000u, 0u, 0u, 0x27802u, 0u, 0u };

static u32 test_stock_shot_init_states(u32 row)
{
    return object_run(stock_shot_init_states_cases[row], row, &stock_shot_init_states_expected[row * 10]);
}

void stock_shot_main(struct WeaponObj*);
static const s16 edges[9][2] = {
    { 160, 120 },
    { -26, 120 },
    { -27, 120 },
    { 345, 120 },
    { 346, 120 },
    { 160, -18 },
    { 160, -19 },
    { 160, 257 },
    { 160, 258 },
};
static const u8 outside[] = { 0, 0, 1, 0, 1, 0, 1, 0, 1 };
static struct WeaponObj pool_before[16];
static u32 stock_flight(u32 row)
{
    struct WeaponObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 edge = row % 9, hit = row / 9 % 2, layer = row / 18 % 3, facing = row / 54;
    s32 camera_x = (s32)layer * 512 - 320, camera_y = (s32)layer * 256 - 240;
    memcpy(pool_before, weapon_objects, sizeof(pool_before));
    background_objects[layer].x_pos.val = camera_x * 65536;
    background_objects[layer].y_pos.val = camera_y * 65536;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x21;
    obj.id = 19;
    obj.state = 1;
    obj.unk5 = 1;
    obj.on_screen = 1;
    obj.bg_offset = layer;
    obj.unk15 = facing ? 0x40 : 0;
    obj.x_pos.val = (camera_x + edges[edge][0]) * 65536 + 0x1234;
    obj.y_pos.val = (camera_y + edges[edge][1]) * 65536 + 0x5678;
    obj.x_vel.val = facing ? 0xA0000 : -0xA0000;
    obj.y_vel.val = 0;
    obj.unk50 = (const u8*)stock_shot_hit_box;
    obj.unk98 = hit;
    obj.animation_table = D_8011BF40;
    set_animation(&obj, 24);
    assert(obj.animation_step.packed == 0x72010002);
    expected = obj;
    if (outside[edge]) {
        expected.state = 3;
        expected.on_screen = 0;
    } else {
        expected.animation_step.fields.duration = 1;
        if (hit) {
            expected.state = 3;
            expected.on_screen = 0;
            expected.unk50 = NULL;
        } else {
            expected.x_pos.val += obj.x_vel.val;
            expected.on_screen = !(edge == 1 && !facing || edge == 3 && facing);
        }
    }
    stock_shot_main(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(weapon_objects, pool_before, sizeof(pool_before));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "stock_shot_init_states", 0, 0, COUNT(stock_shot_init_states_cases), test_stock_shot_init_states },
    { "stock_shot_flight_edges", NULL, NULL, 18, stock_flight },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(stock_shot_init_states_cases) + 18;
