#include "test_runtime.h"
#include "main/background.h"

void func_80027A5C(struct BackgroundObj*);
void func_80027AAC(struct BackgroundObj*);
void func_80027AFC(struct BackgroundObj*);
void func_80027B70(struct BackgroundObj*);

static const u32 func_80027BE4_expected[] = { 0xFFFFFF80u, 0u, 6u, 0xFFFFFFFFu };
static u32 test_func_80027BE4(u32 row)
{
    u32 observed_values[4];
    struct BackgroundObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.unk1C = 6;
    obj.x_pos.i.hi = 8;
    engine_obj.stage = 5;
    g_Player.ride_state = -1;
    obj.unk20 = -1;
    g_Player.y_pos.i.hi = 13944;
    func_80027BE4(&obj);
    observed_values[0] = (u32)g_Player.hp;
    observed_values[1] = (u32)g_Player.x_pos.i.hi;
    observed_values[2] = (u32)obj.x_pos.i.hi;
    observed_values[3] = (u32)obj.y_pos.i.hi;
    return c_test_observe(0, row, observed_values, func_80027BE4_expected, 4);
}

struct CameraBoundsRow {
    u8 stage, ride_state;
    s16 x, player_x, y, player_y;
};
static const struct CameraBoundsRow camera_bounds_rows[] = {
    { 0, 0, 300, 515, 50, 0 },
    { 5, 0, 300, 400, 70, 0 },
    { 0, 0, 50, 104, 100, 343 },
    { 5, 0, 50, 200, 70, 0 },
    { 5, 1, 50, 50, 70, 0 },
};
static const u32 camera_bounds_expected[] = {
    0x003C00C8u,
    0x00000200u,
    0x004600C8u,
    0x00000190u,
    0x00500064u,
    0x0000006Cu,
    0x00460064u,
    0x000000C8u,
    0x00460064u,
    0x00000032u,
};
static u32 test_camera_bounds(u32 row)
{
    const struct CameraBoundsRow* in = &camera_bounds_rows[row];
    struct BackgroundObj obj;
    u32 seen[2];
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    engine_obj.stage = in->stage;
    g_Player.ride_state = in->ride_state;
    g_Player.x_pos.i.hi = in->player_x;
    g_Player.y_pos.i.hi = in->player_y;
    obj.x_pos.i.hi = in->x;
    obj.y_pos.i.hi = in->y;
    obj.unk1C = 200;
    obj.unk1E = 100;
    obj.unk20 = 80;
    obj.unk22 = 60;
    func_80027BE4(&obj);
    seen[0] = (u16)obj.x_pos.i.hi | (u32)(u16)obj.y_pos.i.hi << 16;
    seen[1] = (u16)g_Player.x_pos.i.hi | (u32)(u8)g_Player.hp << 16;
    return c_test_observe(1, row, seen, &camera_bounds_expected[row * 2], 2);
}

static void (*const camera_axis_functions[])(struct BackgroundObj*) = { func_80027A5C, func_80027AAC, func_80027AFC, func_80027B70 };
static const s16 camera_axis_rows[][2] = {
    { 0, 180 },
    { 0, 228 },
    { 0, 308 },
    { 1, 280 },
    { 1, 328 },
    { 1, 408 },
    { 2, 188 },
    { 2, 197 },
    { 2, 212 },
    { 2, 203 },
    { 3, 88 },
    { 3, 97 },
    { 3, 112 },
    { 3, 103 },
};
static const u32 camera_axis_expected[] = {
    0x00C80000u,
    0x00540000u,
    0x00C80000u,
    0x00640000u,
    0x00C80000u,
    0x00740000u,
    0x00B80000u,
    0x00640000u,
    0x00C80000u,
    0x00640000u,
    0x00D80000u,
    0x00640000u,
    0x00C40000u,
    0x00640000u,
    0x00C80000u,
    0x00640000u,
    0x00CC0000u,
    0x00640000u,
    0x00C80000u,
    0x00640000u,
    0x00C80000u,
    0x00600000u,
    0x00C80000u,
    0x00640000u,
    0x00C80000u,
    0x00680000u,
    0x00C80000u,
    0x00640000u,
};
static u32 test_camera_axis(u32 row)
{
    struct BackgroundObj obj;
    u32 seen[2];
    s16 value = camera_axis_rows[row][1];
    memset(&obj, 0, sizeof(obj));
    obj.x_pos.val = 200 << 16;
    obj.y_pos.val = 100 << 16;
    obj.unk2C = obj.unk30 = 0x60;
    obj.unk2E = obj.unk32 = 0xC0;
    obj.unk48 = 8;
    obj.unk49 = -8;
    g_Player.x_pos.i.hi = camera_axis_rows[row][0] == 1 ? value : 0;
    g_Player.y_pos.i.hi = camera_axis_rows[row][0] == 0 ? value : 0;
    obj.unk14.i.hi = camera_axis_rows[row][0] == 2 ? value : 0;
    obj.unk18.i.hi = camera_axis_rows[row][0] == 3 ? value : 0;
    camera_axis_functions[camera_axis_rows[row][0]](&obj);
    seen[0] = obj.x_pos.val;
    seen[1] = obj.y_pos.val;
    return c_test_observe(2, row, seen, &camera_axis_expected[row * 2], 2);
}

struct LayerShakeRow {
    s8 unk44, update_delay;
    u16 unk34;
    s8 unk36, unk37, unk3C, unk3D;
    u8 x_phase, y_phase;
};
static const struct LayerShakeRow layer_shake_rows[] = {
    { 0, 0, 0x11, 5, 5, 2, 2, 0, 0 },
    { 1, 1, 0x11, 5, 5, 2, 2, 0, 0 },
    { 1, 0, 0x11, 1, 1, 2, 2, 0, 0 },
    { 1, 0, 0x10, 5, 5, 1, 2, 0, 0 },
    { 1, 0, 0x01, 5, 5, 2, 1, 0, 0 },
    { 1, 0, 0x11, 5, 5, 2, 2, 0, 0 },
};
static const u32 layer_shake_expected[] = {
    0x00110000u,
    0x00C80000u,
    0x00640000u,
    0x02020505u,
    0x0000u,
    0x00110000u,
    0x00C80000u,
    0x00640000u,
    0x02020505u,
    0x0000u,
    0x00000201u,
    0x00C80000u,
    0x00640000u,
    0x02020000u,
    0x0000u,
    0x00100201u,
    0x00C80000u,
    0x00640000u,
    0x02060504u,
    0x0080u,
    0x00010201u,
    0x00C80000u,
    0x00640000u,
    0x07020405u,
    0x8000u,
    0x00110201u,
    0x00CB0000u,
    0x00620000u,
    0x01010404u,
    0x0000u,
};
static u32 test_layer_shake(u32 row)
{
    const struct LayerShakeRow* in = &layer_shake_rows[row];
    struct BackgroundObj* bg = &background_objects[0];
    u32 seen[5];
    memset(bg, 0, sizeof(*bg));
    g_Player.update_delay = in->update_delay;
    bg->unk44 = in->unk44;
    bg->x_pos.val = 200 << 16;
    bg->y_pos.val = 100 << 16;
    bg->unk1C = 300;
    bg->unk1E = 50;
    bg->unk20 = 150;
    bg->unk22 = 20;
    bg->unk45 = 3;
    bg->unk46 = -2;
    bg->unk3A = 6;
    bg->unk3B = 7;
    bg->unk34 = in->unk34;
    bg->unk36 = in->unk36;
    bg->unk37 = in->unk37;
    bg->unk3C = in->unk3C;
    bg->unk3D = in->unk3D;
    bg->unk3E.bytes[0] = in->x_phase;
    bg->unk3E.bytes[1] = in->y_phase;
    func_80027850();
    g_Player.update_delay = 0;
    seen[0] = (u8)bg->unk4 | (u8)bg->unk47 << 8 | (u32)bg->unk34 << 16;
    seen[1] = bg->x_pos.val;
    seen[2] = bg->y_pos.val;
    seen[3] = (u8)bg->unk36 | (u8)bg->unk37 << 8 | (u8)bg->unk3C << 16 | (u32)(u8)bg->unk3D << 24;
    seen[4] = (u8)bg->unk3E.bytes[0] | (u8)bg->unk3E.bytes[1] << 8;
    return c_test_observe(3, row, seen, &layer_shake_expected[row * 5], 5);
}

static const s8 parallax_gate_rows[][2] = { { 0, 0 }, { 1, 1 }, { 1, 0 } };
static const u32 parallax_gate_expected[] = {
    0x0000u,
    0u,
    0u,
    0u,
    0u,
    0x0000u,
    0u,
    0u,
    0u,
    0u,
    0x0102u,
    0x00401234u,
    0x00505678u,
    0x00607777u,
    0x00708888u,
};
static u32 test_parallax_gate(u32 row)
{
    struct BackgroundObj* first = &background_objects[1];
    struct BackgroundObj* second = &background_objects[2];
    u32 seen[5];
    memset(background_objects, 0, sizeof(background_objects));
    engine_obj.stage = 1;
    engine_obj.substage = 0;
    g_Player.update_delay = parallax_gate_rows[row][1];
    first->unk44 = second->unk44 = parallax_gate_rows[row][0];
    first->x_pos.val = 0x00401234;
    first->y_pos.val = 0x00505678;
    second->x_pos.val = 0x00607777;
    second->y_pos.val = 0x00708888;
    func_80027D40();
    func_800281E8();
    g_Player.update_delay = 0;
    seen[0] = (u8)first->unk4 | (u8)second->unk4 << 8;
    seen[1] = first->unk14.val;
    seen[2] = first->unk18.val;
    seen[3] = second->unk14.val;
    seen[4] = second->unk18.val;
    return c_test_observe(4, row, seen, &parallax_gate_expected[row * 5], 5);
}

static const u32 layer_setup_expected[] = {
#ifdef MMX4_SATURN
    0x01020604u,
    0x00010101u,
    0x000B2700u,
    0x0402u,
    0x0300u,
    0x0401u,
#else
    0x0A090306u,
    0x00010101u,
    0x000B2700u,
    0x0805u,
    0x0704u,
    0x0A09u,
#endif
};
static u32 test_layer_setup(u32 row)
{
    u32 seen[6], i;
    memset(background_objects, 0, sizeof(background_objects));
    engine_obj.stage = 1;
    engine_obj.substage = 0;
    layout_width = 40;
    layout_height = 12;
    func_8002771C();
    seen[0] = (u8)D_80173C6C[0] | (u8)D_80173C6C[1] << 8 | (u8)D_80173C6C[2] << 16 | (u32)(u8)D_80173C6C[3] << 24;
    seen[1] = background_objects[0].unk0 | background_objects[0].unk3 << 8 | background_objects[0].unk44 << 16 | (u32)background_objects[0].unk4D << 24;
    seen[2] = (u8)background_objects[0].min_y | background_objects[0].unk4E << 8 | (u8)background_objects[0].max_y << 16;
    for (i = 1; i < 3; i++) {
        assert(background_objects[i].unk0 == 1 && background_objects[i].unk3 == 1 && background_objects[i].unk44 == 1);
        assert(background_objects[i].unk4D == 0 && background_objects[i].min_y == 0);
        assert(background_objects[i].unk4E == 39 && background_objects[i].max_y == 11);
    }
    for (i = 0; i < 3; i++)
        seen[3 + i] = (u8)background_objects[i].unk4B | (u8)background_objects[i].unk4A << 8;
    return c_test_observe(5, row, seen, layer_setup_expected, 6);
}

void func_80027FA8(struct BackgroundObj*);
static const s16 bg_step_rows[][4] = {
    { 200, 195, 200, 205 },
    { 200, 100, 100, 200 },
    { 600, 100, 100, 600 },
    { 200, 205, 200, 195 },
    { 100, 200, 200, 100 },
    { 100, 600, 600, 100 },
};
static const u32 bg_step_expected[] = { 0x00C800C8u, 0x00B80074u, 0x01A40118u, 0x00C800C8u, 0x007400B8u, 0x011801A4u };
static u32 test_bg_step(u32 row)
{
    struct BackgroundObj obj;
    u32 seen;
    memset(&obj, 0, sizeof(obj));
    obj.x_pos.i.hi = bg_step_rows[row][0];
    obj.unk14.i.hi = bg_step_rows[row][1];
    obj.y_pos.i.hi = bg_step_rows[row][2];
    obj.unk18.i.hi = bg_step_rows[row][3];
    func_80027FA8(&obj);
    assert(obj.unk14.i.hi == bg_step_rows[row][1] && obj.unk18.i.hi == bg_step_rows[row][3]);
    seen = (u16)obj.x_pos.i.hi | (u32)(u16)obj.y_pos.i.hi << 16;
    return c_test_observe(6, row, &seen, &bg_step_expected[row], 1);
}

struct CameraLimitRow {
    s16 x, player_x, player_x_before, y, player_y, player_y_before;
    s16 limit[4], target[4];
};
static const struct CameraLimitRow camera_limit_rows[] = {
    { 100, 110, 0, 100, 110, 0, { 0, 0, 0, 0 }, { 200, 200, 200, 200 } },
    { 100, 100, 150, 100, 100, 150, { 0, 50, 0, 50 }, { 200, 102, 200, 102 } },
    { 100, 100, 90, 100, 100, 90, { 0, 7, 0, 7 }, { 102, 7, 102, 7 } },
    { 300, 300, 0, 300, 300, 290, { 0, 250, 0, 0 }, { 298, 200, 298, 200 } },
    { 300, 310, 305, 300, 310, 0, { 0, 0, 0, 0 }, { 200, 200, 200, 200 } },
    { 300, 310, 400, 300, 300, 400, { 5, 0, 5, 0 }, { 5, 290, 5, 200 } },
};
static const u32 camera_limit_expected[][2] = {
    { 0x006800C8u, 0x006800C8u },
    { 0x006600C8u, 0x00660068u },
    { 0x00070072u, 0x00070066u },
    { 0x00C8012Au, 0x0128012Au },
    { 0x00C80128u, 0x000C0128u },
    { 0x00CE0005u, 0x00C80005u },
};
static u32 test_camera_limits(u32 row)
{
    const struct CameraLimitRow* in = &camera_limit_rows[row];
    struct BackgroundObj obj;
    u32 seen[2];
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.x_pos.i.hi = in->x;
    obj.y_pos.i.hi = in->y;
    obj.unk47 = 4;
    g_Player.x_pos.i.hi = in->player_x;
    g_Player.unk18.i.hi = in->player_x_before;
    g_Player.y_pos.i.hi = in->player_y;
    g_Player.unk1C.i.hi = in->player_y_before;
    obj.unk1C = in->limit[0];
    obj.unk1E = in->limit[1];
    obj.unk20 = in->limit[2];
    obj.unk22 = in->limit[3];
    obj.unk24 = in->target[0];
    obj.unk26 = in->target[1];
    obj.unk28 = in->target[2];
    obj.unk2A = in->target[3];
    func_80028690(&obj);
    seen[0] = (u16)obj.unk1C | (u32)(u16)obj.unk1E << 16;
    seen[1] = (u16)obj.unk20 | (u32)(u16)obj.unk22 << 16;
    return c_test_observe(7, row, seen, camera_limit_expected[row], 2);
}

const struct CTestGroup c_test_groups[] = {
    { "func_80027BE4", 0, 0, 1, test_func_80027BE4 },
    { "camera_bounds", 0, 0, COUNT(camera_bounds_rows), test_camera_bounds },
    { "camera_axis_steps", 0, 0, COUNT(camera_axis_rows), test_camera_axis },
    { "layer0_camera_and_shake", 0, 0, COUNT(layer_shake_rows), test_layer_shake },
    { "parallax_layer_gate", 0, 0, COUNT(parallax_gate_rows), test_parallax_gate },
    { "layer_setup", 0, 0, 1, test_layer_setup },
    { "layer_step_limit", 0, 0, COUNT(bg_step_rows), test_bg_step },
    { "camera_limit_easing", 0, 0, COUNT(camera_limit_rows), test_camera_limits },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + COUNT(camera_bounds_rows) + COUNT(camera_axis_rows) + COUNT(layer_shake_rows) + COUNT(parallax_gate_rows) + 1
    + COUNT(bg_step_rows) + COUNT(camera_limit_rows);
