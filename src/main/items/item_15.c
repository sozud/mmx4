// ItemObj, item_object_update_funcs[15]
// 800C3CF8..800C3FEC
#include "common.h"

void func_800C3CF8(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010D070[arg0->state](arg0);
}

void func_800C3D40(struct ItemObj* arg0)
{
    arg0->unk16 = 6;
    arg0->animation_table = NULL;
    arg0->animation_step.fields.frame_index = (u8)arg0->unk2;
    arg0->unk40 = D_801406A8[func_8002938C(0x89)] >> 7;
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[func_8002938C(0x89)];
    arg0->unk42 = 0x7943;
    arg0->unk5C = 0;
    arg0->unk61 = 0;
    arg0->unk68 = (struct Unk_unk68*)D_8010D0BC[arg0->unk2];
    arg0->unk50 = NULL;
    arg0->unk54 = NULL;
    arg0->unk58 = NULL;
    arg0->unk15 = 0;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = FIXED(0.0625);
    arg0->unk75 = 1;
    arg0->unk76 = 0;
    arg0->unk7C.timer = 0;
    arg0->ext.packed = 0;
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x60);
    func_8001540C(5, 3, NULL);
    arg0->state = 1;
}

INCLUDE_ASM("main/nonmatchings/items/item_15", func_800C3E4C);

void func_800C3F98(struct ItemObj* arg0)
{
    func_80015930(5U, 3U);
    func_8001540C(5, 4, NULL);
    arg0->unk7C.timer = 0;
    arg0->ext.timer = 0;
    arg0->on_screen = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void (*D_8010D070[])(struct ItemObj*) = {
    func_800C3D40,
    func_800C3E4C,
    func_800C3F98,
};

u8 D_8010D07C[4][16] = {
    { 0x00, 0xD8, 0x30, 0x28 },
    { 0x00, 0x28, 0x30, 0x28 },
    { 0x00, 0xD8, 0x30, 0x30 },
    { 0x00, 0x30, 0x30, 0x28 },
};

u8 D_8010D0BC[4][16] = {
    { 0x00, 0xB8, 0x30, 0x10 },
    { 0x00, 0x48, 0x30, 0x10 },
    { 0x00, 0xC0, 0x30, 0x10 },
    { 0x00, 0x40, 0x30, 0x10 },
};
