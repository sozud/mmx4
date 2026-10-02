// ItemObj, item_object_update_funcs[1]
// 800BEBB4..800BF730
#include "common.h"

void stage_block_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    stage_block_state_funcs[arg0->state](arg0);
}

// stage_block_init
INCLUDE_ASM("main/nonmatchings/items/item_01_stage_block", func_800BEBFC);

void stage_block_main(struct ItemObj* arg0)
{
    s32 collision;
    s8 index;

    if (arg0->unk2 == 13) {
        arg0->unk76 = -1;
    }
    stage_block_step_funcs[arg0->unk5](arg0);
    update_on_screen(BASE_OBJECT(arg0), stage_block_bounds[arg0->unk2].width, stage_block_bounds[arg0->unk2].height);
    collide_with_players(PLAYER_OBJECT(arg0));
    index = arg0->unk2;
    if (!((u8)stage_block_entries[index].flags_and_palette & 0x80) && (index != 12 || arg0->unk5 == 3)) {
        collision = func_8002DD04(MAIN_OBJECT(arg0));
        if (collision < 0) {
            if (arg0->unk2 == 12) {
                apply_tile_effect((u8)stage_block_entries[12].sound_id, 0, 0);
            }
            arg0->on_screen = 0;
            arg0->unk7C.timer = 60;
            arg0->state++;
            spawn_rubble(15, stage_block_debris, arg0, 0);
            return;
        }
        if (collision > 0) {
            arg0->unk42 |= 0x8000;
        } else {
            arg0->unk42 &= 0x7FFF;
        }
    }
}

void stage_block_wait_trigger(struct ItemObj* self)
{
    s8 index;

    index = self->unk2;
    if (g_Player.x_pos.i.hi < stage_block_entries[index].left) {
        return;
    }
    if (index == 9) {
        func_8001540C(5, 1, NULL);
    }
    if (self->unk2 == 0xD) {
        func_8001540C(5, 0, NULL);
    }
    start_screen_shake_x(0x18, 3, 1);
    self->ext.timer = 1;
    self->unk5 = (u8)self->unk5 + 1;
    if (self->unk2 == 0xD) {
        func_800B10E4(0x21, 0xE10, 0x1E0, 0xF10, 0x1F0, 6);
        func_800B10E4(0x22, 0xE10, 0x1E0, 0xF10, 0x1F0, 6);
    }
}

// stage_block_fall
INCLUDE_ASM("main/nonmatchings/items/item_01_stage_block", func_800BEFCC);

// stage_block_land
INCLUDE_ASM("main/nonmatchings/items/item_01_stage_block", func_800BF1FC);

void stage_block_stop(struct ItemObj* self)
{
    if ((self->unk2 == 5) || (self->unk2 == 0xD)) {
        self->state = 3;
    }
}

extern u32 stage_block_explosion_sounds[4];

void stage_block_destroyed(struct ItemObj* arg0)
{
    if (--arg0->unk7C.timer != 0) {
        if ((main_bss_state.frame_counter & 7) == 0) {
            func_800AF878(BASE_OBJECT(arg0), 1, 0x1F, 0x1F);
        }
        if ((main_bss_state.frame_counter & 0xF) == 0) {
            func_8001540C(0, stage_block_explosion_sounds[get_random() & 3], arg0);
        }
    } else {
        arg0->unk5 = 0;
        arg0->state++;
    }
}

void stage_block_despawn(struct ItemObj* arg0)
{
    despawn_object_permanently(OBJECT_HEADER(arg0));
}

void drop_item(struct BaseObj* arg0, s8 arg1)
{
    func_800BF638(arg0, arg1, arg0->x_pos.i.hi, arg0->y_pos.i.hi);
}

// drop_item_at
INCLUDE_ASM("main/nonmatchings/items/item_01_stage_block", func_800BF638);

struct Item01StageEntry stage_block_entries[15] = {
    { 0x0240, 0x00E0, 0x0200, 0x0100, 0x0100, 0x0040, 0x0C00, 0x0000 },
    { 0x02F0, 0x00D8, 0x0250, 0x0130, 0x0130, 0x0081, 0x2C00, 0x0021 },
    { 0x0390, 0x00E0, 0x02F0, 0x01B0, 0x01B0, 0x0082, 0x1F00, 0x0000 },
    { 0x0430, 0x0140, 0x046B, 0x0197, 0x0197, 0x0003, 0x3D00, 0x0001 },
    { 0x04D0, 0x0140, 0x046B, 0x0197, 0x0197, 0x0003, 0x3D00, 0x0002 },
    { 0x0870, 0x0120, 0x07D0, 0x0230, 0x01C0, 0x0003, 0x2C00, 0x0003 },
    { 0x0930, 0x00E0, 0x08A0, 0x01B0, 0x01B0, 0x0085, 0x1C00, 0x0004 },
    { 0x09E0, 0x00E0, 0x0930, 0x01A0, 0x01A0, 0x0086, 0x1C00, 0x0005 },
    { 0x0AE0, 0x01A8, 0x0A90, 0x0228, 0x0208, 0x0087, 0x0800, 0x0006 },
    { 0x0BE0, 0x0228, 0x0BA0, 0x0198, 0x0198, 0x0088, 0x0D00, 0x0007 },
    { 0x0CA0, 0x0090, 0x0BE0, 0x0148, 0x0148, 0x0089, 0x2C00, 0x0008 },
    { 0x0DB0, 0x00B0, 0x0CE0, 0x0170, 0x0170, 0x008A, 0x1C00, 0x0009 },
    { 0x0DB0, 0x00A8, 0x0CE0, 0x0168, 0x0168, 0x004F, 0x1C00, 0x000A },
    { 0x0EA0, 0x01E0, 0x0EA0, 0x03D0, 0x03D0, 0x00D0, 0x5000, 0x0000 },
    { 0x02F0, 0x0130, 0x0250, 0x0188, 0x0188, 0x0053, 0x2C00, 0x0000 },
};

struct Item01SpriteBounds stage_block_bounds[15] = {
    { 0x00, 0x00, 0x40, 0x20 },
    { 0x00, 0xF8, 0x30, 0x48 },
    { 0x00, 0x08, 0x30, 0x40 },
    { 0x00, 0x08, 0x30, 0x30 },
    { 0x00, 0x08, 0x30, 0x30 },
    { 0x00, 0x00, 0x30, 0x40 },
    { 0x00, 0x08, 0x30, 0x28 },
    { 0x00, 0x08, 0x40, 0x38 },
    { 0x00, 0x10, 0x80, 0x58 },
    { 0x00, 0x10, 0x40, 0x68 },
    { 0x00, 0x00, 0x40, 0x48 },
    { 0x00, 0x00, 0x50, 0x70 },
    { 0x00, 0x00, 0x50, 0x28 },
    { 0x00, 0x08, 0x70, 0x18 },
    { 0x00, 0x00, 0x30, 0x38 },
};

u8 stage_block_boxes[60] = {
    0xC0,
    0xE0,
    0x80,
    0x40,
    0xD0,
    0xA8,
    0x60,
    0xB0,
    0xD0,
    0xB8,
    0x60,
    0x90,
    0xD0,
    0xC8,
    0x60,
    0x70,
    0xD0,
    0xC8,
    0x60,
    0x70,
    0xD0,
    0xC0,
    0x60,
    0x80,
    0xD0,
    0xD0,
    0x60,
    0x60,
    0xC0,
    0xC0,
    0x70,
    0x80,
    0x80,
    0xA8,
    0xFF,
    0xB0,
    0xC0,
    0x98,
    0x80,
    0xD0,
    0xC0,
    0xB8,
    0x80,
    0x90,
    0xB0,
    0xD0,
    0xA0,
    0x60,
    0xB0,
    0xD8,
    0xA0,
    0x50,
    0xB0,
    0xD8,
    0xA0,
    0x50,
    0xD0,
    0xD8,
    0x60,
    0x50,
};

u8 stage_block_debris[16] = {
    0x00,
    0x01,
    0x02,
    0x03,
    0x04,
    0x00,
    0x01,
    0x02,
    0x03,
    0x04,
    0x00,
    0x01,
    0x02,
    0x03,
    0x04,
    0x00,
};

struct Item01DebrisPosition {
    s16 x;
    s16 y;
};

struct Item01DebrisPosition stage_block_spawn_positions[6] = {
    { 0x02BF, 0x014C },
    { 0x0C5F, 0x0127 },
    { 0x0C5F, 0x017B },
    { 0x0CE0, 0x017B },
    { 0x0D5F, 0x0127 },
    { 0x0D5F, 0x01A7 },
};

void (*stage_block_state_funcs[])(struct ItemObj*) = {
    func_800BEBFC,
    stage_block_main,
    stage_block_destroyed,
    stage_block_despawn,
};

void (*stage_block_step_funcs[4])(struct ItemObj*) = {
    stage_block_wait_trigger,
    func_800BEFCC,
    func_800BF1FC,
    stage_block_stop,
};

u32 stage_block_explosion_sounds[4] = { 0, 1, 2, 3 };
