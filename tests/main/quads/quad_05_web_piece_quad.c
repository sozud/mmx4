#include "test_runtime.h"
#include "main/quads/quad_05_web_piece_quad.h"

static u32 quad_case(u32 mode, u32 observation)
{
    struct QuadObj obj, before;
    struct BackgroundObj background_before[3];
    u32 i, index, scale;
    s32* frame;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 0xC1;
    obj.id = 5;
    obj.state = 1;
    obj.unk5 = 0x27;
    obj.bg_offset = 0;
    obj.x_pos.i.hi = mode == 0 ? 2000 : 100;
    obj.y_pos.i.hi = mode == 0 ? 2000 : 100;
    obj.ext.quad_5.index = 7;
    obj.ext.quad_5.scale = mode == 0 ? 0x100 : 0x500;
    obj.ext.quad_5.update_timer = mode == 0 ? 0 : 2;
    before = obj;
    memcpy(background_before, background_objects, sizeof(background_before));
    web_piece_quad_main(&obj);
    index = mode == 0 ? 7 : 0;
    scale = 0x100;
    frame = web_piece_quad_frame_table[index];
    before.ext.quad_5.index = index;
    before.ext.quad_5.scale = scale;
    before.ext.quad_5.update_timer = mode == 0 ? 1 : 0;
    before.ext.quad_5.data = frame;
    for (i = 0; i < 4; i++) {
        before.vertices[i].x.val = frame[i * 2] * scale;
        before.vertices[i].y.val = frame[i * 2 + 1] * scale;
    }
    before.on_screen = mode == 0 ? 0 : 1;
    if (mode == 0) {
        before.state = 2;
        before.unk5 = 0;
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(background_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)background_before)[i]);
    return observation == 0 ? (u8)obj.state | ((u32)(u8)obj.on_screen << 8) | ((u32)obj.ext.quad_5.index << 16) : (u32)obj.vertices[1].x.val;
}
static const u32 web_piece_quad_visibility_context_cases_expected[] = { 0x70002u, 0x10000u, 0x101u, 0x80000u };
static u32 web_piece_quad_visibility_context_cases_row(u32 row)
{
    return quad_case(row / 2, row % 2);
}

const struct CTestGroup c_test_groups[] = {
    { "web_piece_quad_visibility_context", NULL, web_piece_quad_visibility_context_cases_expected, COUNT(web_piece_quad_visibility_context_cases_expected), web_piece_quad_visibility_context_cases_row },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(web_piece_quad_visibility_context_cases_expected);
