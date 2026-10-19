#include "test_runtime.h"
#include "main/shots/shot_48_double_ball.h"
#include "main/collision_bounds.h"
#include "main/55C4.h"
extern void* double_animations[31];

static u32 travel_case(u32 mode, u32 observation)
{
    struct ShotObj obj, before;
    u32 i, actual, cursor_index = ~0u;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 48;
    obj.state = 1;
    obj.unk5 = 0;
    obj.unk6 = 0x35;
    obj.unk7 = 0x27;
    obj.unk15 = 0x40;
    obj.unk17 = 12;
    obj.previous_animation_index = 0xA5;
    obj.timer = 0x1234;
    obj.unk8A = mode == 0 ? -1 : mode == 1 ? 2
                                           : 0;
    obj.unk8C.halves[0] = mode == 0 ? 10 : -10;
    obj.unk8C.halves[1] = mode == 0 ? 20 : -20;
    obj.x_pos.val = (s32)obj.unk8C.halves[0] * 65536 + 0x24681;
    obj.y_pos.val = (s32)obj.unk8C.halves[1] * 65536 - 0x35792;
    obj.unk84.value = 0x24681357;
    obj.animation_table = (u32**)double_animations;
    obj.animation_cursor = (u32*)double_animations[12];
    obj.animation_step.packed = *obj.animation_cursor;
    obj.animation_step.fields.duration = mode == 1 ? 2 : 1;
    before = obj;
    double_ball_travel(&obj);
    before.x_pos = obj.x_pos;
    before.y_pos = obj.y_pos;
    before.unk5 = obj.unk5;
    before.timer = obj.timer;
    before.unk8A = obj.unk8A;
    before.unk84 = obj.unk84;
    before.animation_cursor = obj.animation_cursor;
    before.animation_step = obj.animation_step;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    assert(obj.animation_table == (u32**)double_animations);
    for (i = 0; i < 4; i++)
        if (obj.animation_cursor == (u32*)double_animations[12] + i)
            cursor_index = i;
    assert(cursor_index != ~0u);
    switch (observation) {
    case 0:
        actual = obj.x_pos.val;
        break;
    case 1:
        actual = obj.y_pos.val;
        break;
    case 2:
        actual = (u16)obj.unk8A | ((u32)(u8)obj.unk5 << 16);
        break;
    case 3:
        actual = (u16)obj.timer;
        break;
    case 4:
        actual = obj.unk84.value;
        break;
    case 5:
        actual = obj.animation_step.packed;
        break;
    default:
        actual = cursor_index;
        break;
    }
    return actual;
}
static const u32 double_ball_positions_cases_expected[] = { 0xE8D02u, 0xD50DCu, 0xFFFEu, 0x1234u, 0x15u, 0x34010001u, 0x1u, 0xFFF72341u, 0xFFEA5437u, 0x1u, 0x1234u, 0x15u, 0x33010001u, 0x0u, 0xFFF60000u, 0xFFEC0000u, 0x10000u, 0x5Au, 0x15u, 0x34010001u, 0x1u };
static u32 double_ball_positions_cases_row(u32 row)
{
    return travel_case(row / 7, row % 7);
}

void double_ball_run(struct ShotObj*);
extern void* double_animations[31];
extern u8 double_ball_boxes[2][4];
static const s16 screen_x[] = { -65, -64, 160, 383, 384 };
static struct WeaponObj weapons_expected[16];
static struct VisualObj visuals_before[32];
static u32 lifetime(u32 row)
{
    struct ShotObj obj, expected;
    struct MainObj owner, owner_before;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 position = row % COUNT(screen_x), dead = row / COUNT(screen_x) % 2, hit = row / COUNT(screen_x) / 2 % 2, facing = row / COUNT(screen_x) / 4, i;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.hp = 24;
    player_before = g_Player;
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    owner.active = 0x41;
    owner.id = 73;
    owner.state = dead ? 2 : 1;
    owner_before = owner;
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 39;
    }
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    obj.active = 0x41;
    obj.id = 48;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 7;
    obj.timer = 2;
    obj.on_screen = 7;
    obj.unk15 = facing ? 0x40 : 0;
    obj.unk42 = 0x1234;
    obj.unk5C = 1;
    obj.unk60 = 6;
    obj.unk7C = WEAPON_OBJECT(&owner);
    obj.x_pos.val = screen_x[position] * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.unk18.val = 0x12345;
    obj.unk1C.val = 0x23456;
    obj.unk50.data = obj.unk54 = double_ball_boxes[0];
    obj.unk58.collision_bounds = D_801060F0;
    obj.animation_table = (u32**)double_animations;
    set_animation(&obj, 12);
    assert(obj.animation_step.packed == 0x33010001);
    if (hit) {
        weapon_objects[0].active = 0x21;
        weapon_objects[0].id = 56;
        weapon_objects[0].unk15 = obj.unk15;
        weapon_objects[0].x_pos = obj.x_pos;
        weapon_objects[0].y_pos = obj.y_pos;
        weapon_objects[0].unk50 = double_ball_boxes[0];
    }
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    expected = obj;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.timer = 1;
    expected.animation_cursor = (u32*)double_animations[12] + 1;
    expected.animation_step.packed = 0x34010001;
    if (dead) {
        expected.state = 2;
        expected.on_screen = 0;
    } else if (hit) {
        expected.unk5C = 0;
        expected.unk42 |= 0x8000;
        expected.state = 2;
        expected.on_screen = 0;
        ((s16*)&weapons_expected[0].unk80)[0] = screen_x[position] + (facing ? 1 : -1);
        ((s16*)&weapons_expected[0].unk80)[1] = 119;
    } else if (position == 0 || position == 4) {
        expected.state = 2;
        expected.unk5 = expected.unk6 = expected.on_screen = 0;
    } else
        expected.on_screen = position == 2;
    D_8013E198[0] = D_8013E198[1] = -1;
    cur_random = 0x1234;
    double_ball_run(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_before, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    c_test_same_words(weapon_objects, weapons_expected, sizeof(weapons_expected));
    c_test_same_words(visual_objects, visuals_before, sizeof(visuals_before));
    assert(cur_random == (dead || hit ? 0x366A : 0x1234));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "double_ball_positions", NULL, double_ball_positions_cases_expected, COUNT(double_ball_positions_cases_expected), double_ball_positions_cases_row },
    { "owner_death_weapon_clear_and_viewport_edges", NULL, NULL, COUNT(screen_x) * 8, lifetime },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(double_ball_positions_cases_expected) + COUNT(screen_x) * 8;
