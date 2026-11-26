#include "test_runtime.h"
void func_800DA358(struct LayerObj*);
static u32 end(u32 row)
{
    struct LayerObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_expected;
    struct BackgroundObj backgrounds_expected[3];
    u32 crossed = row % 2, down = row / 2 % 2, camera = row / 4, scroll = 0x8000;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    engine_obj.stage = 7;
    engine_obj.substage = 0;
    engine_obj.unkF = 0;
    engine_expected = engine_obj;
    if (crossed)
        engine_expected.unkF = 1;
    g_Player.x_pos.val = (crossed ? 0x18D0 : 0x18CF) * 65536 + 0x1234;
    player_before = g_Player;
    background_objects[0].x_pos.val = 0x1800 * 65536 + 0x1234;
    background_objects[0].unk14.val = background_objects[0].x_pos.val + (camera ? 0x10004 : 0);
    background_objects[1].x_pos.val = 0x2345;
    background_objects[2].x_pos.val = 0x3456;
    background_objects[1].y_pos.val = 0x1234;
    background_objects[2].y_pos.val = 0x2345;
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    obj.active = 1;
    obj.id = 5;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk7 = down;
    obj.unk24 = obj.unk25 = 2;
    memcpy(&obj.bg_offset, &scroll, 4);
    expected = obj;
    expected.unk18.val = down ? -0x400 : 0x400;
    backgrounds_expected[1].x_pos.val += 0x8000 - (camera ? 0x8002 : 0);
    backgrounds_expected[2].x_pos.val -= 0x4000 + (camera ? 0x4001 : 0);
    backgrounds_expected[1].y_pos.val += down ? 0x200 : -0x200;
    backgrounds_expected[2].y_pos.val += down ? 0x400 : -0x400;
    func_800DA358(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    return 1;
}
static u32 bob_paths(u32 row);
void func_800DA2D4(struct LayerObj*);
static u32 bob_init(u32 row)
{
    struct LayerObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    engine_obj.stage = 7;
    engine_obj.substage = row;
    obj.active = 1;
    obj.id = 5;
    memset(obj.unk20, 0x55, sizeof(obj.unk20));
    func_800DA2D4(&obj);
    assert(obj.state == 1 && obj.unk25 == 3);
    assert(background_objects[1].unk4D == 2 && background_objects[1].unk4E == 7);
    assert(background_objects[2].unk4D == 2 && background_objects[2].unk4E == 8);
    assert(background_objects[1].x_pos.val == 0x8000 && background_objects[2].x_pos.val == -0x4000);
    return obj.state;
}

const struct CTestGroup c_test_groups[] = {
    { "shipped_airship_layer_end_position_and_fractional_camera_motion_both_sway_phases", NULL, NULL, 8, end },
    { "bob_paths", 0, 0, 13, bob_paths },
    { "bob_init", 0, 0, 2, bob_init },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 8 + 13 + 2;

static u32 bob_paths(u32 row)
{
    static const s16 player_x[] = { 0x100, 0x100, 0x100, 0x700, 0x700, 0x900, 0x900 };
    struct LayerObj obj;
    s32 scroll = 0;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(&obj.bg_offset, &scroll, sizeof(scroll));
    engine_obj.stage = 7;
    engine_obj.substage = row == 0;
    obj.active = 1;
    obj.state = 1;
    g_Player.x_pos.i.hi = row <= 6 ? player_x[row] : 0x100;
    obj.unk24 = row == 1 ? 3 : row <= 2 ? 0 : row <= 4 ? 1 : row <= 6 ? 2 : 0;
    obj.unk5 = obj.unk24 == 3 ? 3 : obj.unk24;
    obj.unk6 = row == 2 || row == 4 || row == 6;
    obj.unk7 = row == 9 || row == 10 || row == 12;
    obj.unk18.val = row <= 6 ? -0x5800 : row <= 8 ? 0x100 : row <= 10 ? -0x100 : row == 11 ? 0x5C00 : -0x5C00;
    obj.private_state.value.val = row == 7 || row == 9 ? 3 : 0;
    func_800DA358(&obj);
    if (row == 0) {
        assert(obj.unk5 == 0 && obj.unk6 == 0 && obj.unk18.val == -0x5800);
        return 1;
    }
    if (row <= 6) {
        assert(obj.unk24 == (row <= 2 ? 0 : row <= 4 ? 1 : 2));
        assert(obj.unk5 == (obj.unk6 == 0 ? 3 : (row <= 2 ? 0 : row <= 4 ? 1 : 2)));
        assert(obj.unk6 == (row == 1 || row == 3 || row == 5));
        assert(obj.unk18.val == -0x5400 && background_objects[2].y_pos.val == 0x5400);
        return 1;
    }
    if (row >= 11) {
        assert(obj.unk7 == (row == 11) && obj.private_state.value.val == 0x1E);
        assert(obj.unk18.val == (row == 11 ? 0x5C00 : -0x5C00));
        return 1;
    }
    assert(obj.private_state.value.val == (row == 7 || row == 9 ? 2 : 0));
    assert(obj.unk18.val == (row == 7 ? 0x100 : row == 8 ? 0x500 : row == 9 ? -0x100 : -0x500));
    return 1;
}
