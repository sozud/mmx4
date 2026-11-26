#include "test_runtime.h"
#include "main/afterimage.h"

void func_800AE7DC(struct UnkObj* arg0);

struct AfterimageRow {
    s8 state, unk5, unk2, afterimage;
    s16 position_timer, blink_timer, palette_offset;
};
static const struct AfterimageRow afterimage_rows[] = {
    { 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 1, 5, 0, 0, 0 },
    { 0, 0, 1, -1, 0, 0, 0 },
    { 1, 0, 1, 0, 0, 0, 0 },
    { 1, 0, 1, 1, 2, 0, 0 },
    { 1, 0, 1, -1, 0, 0, 0 },
    { 1, 1, 1, 1, 0, 0, 0 },
    { 1, 1, 1, -1, 0, 4, 0 },
    { 1, 1, 1, -1, 0, 3, 0 },
    { 1, 1, 1, -1, 0, 0, 0 },
    { 1, 2, 1, 1, 0, 0, 0 },
    { 1, 2, 1, -1, 0, 0, 2 },
    { 1, 2, 2, -1, 0, 0, 0 },
    { 1, 2, 1, -1, 0, 0, 0 },
};
static const u32 afterimage_expected[] = {
    0x00000000u, 0x00100000u, 0x00200000u, 0x00000000u, 0x00000000u,
    0x05010001u, 0x00500000u, 0x00600000u, 0x00080003u, 0x00000008u,
    0x00000000u, 0x00100000u, 0x00200000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00100000u, 0x00200000u, 0x00000000u, 0x00000000u,
    0x01010001u, 0x00100000u, 0x00200000u, 0x00000001u, 0x00000000u,
    0xFF010101u, 0x00410000u, 0x00420000u, 0x00000003u, 0x00000000u,
    0x01010001u, 0x00500000u, 0x00600000u, 0x00080003u, 0x00000008u,
    0xFF010101u, 0x00410000u, 0x00420000u, 0x00030000u, 0x00000000u,
    0xFF010101u, 0x00100000u, 0x00200000u, 0x00020000u, 0x00000000u,
    0xFF010201u, 0x00100000u, 0x00200000u, 0x00000000u, 0x00000000u,
    0x01010001u, 0x00500000u, 0x00600000u, 0x00080003u, 0x00000008u,
    0xFF010201u, 0x00410000u, 0x00420000u, 0x00000000u, 0x00000001u,
    0x00000200u, 0x00100000u, 0x00200000u, 0x00000000u, 0x00000000u,
    0xFF000200u, 0x00100000u, 0x00200000u, 0x00000000u, 0x00000000u,
};
static struct UnkObj afterimage;
static struct PlayerObj afterimage_leader;
static u32 test_afterimage(u32 row)
{
    const struct AfterimageRow* in = &afterimage_rows[row];
    u32 seen[5];
    memset(&afterimage, 0, sizeof(afterimage));
    memset(&afterimage_leader, 0, sizeof(afterimage_leader));
    g_Player.afterimage = in->afterimage;
    g_Player.x_pos.val = 0x00500000;
    g_Player.y_pos.val = 0x00600000;
    g_Player.animation_step.fields.frame_index = 7;
    g_Player.unk15 = 0x21;
    afterimage_leader.unk18.val = 0x00410000;
    afterimage_leader.unk1C.val = 0x00420000;
    afterimage.state = in->state;
    afterimage.on_screen = in->state;
    afterimage.unk5 = in->unk5;
    afterimage.unk2 = in->unk2;
    afterimage.x_pos.val = 0x00100000;
    afterimage.y_pos.val = 0x00200000;
    afterimage.link.player = &afterimage_leader;
    afterimage.ext.afterimage.position_timer = in->position_timer;
    afterimage.ext.afterimage.blink_timer = in->blink_timer;
    afterimage.ext.afterimage.palette_offset = in->palette_offset;
    func_800AE7DC(&afterimage);
    assert(afterimage.unk18.val == 0x00100000 && afterimage.unk1C.val == 0x00200000);
    assert(afterimage.animation_step.fields.frame_index == 7 && afterimage.unk15 == 0x21);
    seen[0] = (u8)afterimage.state | (u8)afterimage.unk5 << 8 | (u8)afterimage.on_screen << 16 | (u32)(u8)g_Player.afterimage << 24;
    seen[1] = afterimage.x_pos.val;
    seen[2] = afterimage.y_pos.val;
    seen[3] = (u16)afterimage.ext.afterimage.position_timer | (u32)(u16)afterimage.ext.afterimage.blink_timer << 16;
    seen[4] = (u16)afterimage.ext.afterimage.palette_offset;
    return c_test_observe(0, row, seen, &afterimage_expected[row * 5], 5);
}

const struct CTestGroup c_test_groups[] = {
    { "player_afterimage_states", 0, 0, COUNT(afterimage_rows), test_afterimage },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(afterimage_rows);
