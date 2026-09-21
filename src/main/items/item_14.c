// ItemObj, item_object_update_funcs[14]
// 800C3880..800C3CF8
#include "common.h"

void func_800C3880(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010D040[arg0->state](arg0);
}

void func_800C38C8(struct ItemObj* self)
{
    s32 frame_index;
    s32 frame_offset;
    s32* archive;
    u8 bg_offset;

    self->active = 0x41;
    self->unk16 = 0x22;
    self->unk15 = 0;
    self->unk40 = D_801406A8[func_8002938C(0x8B) & 0xFF] >> 7;
    frame_index = func_8002938C(0x8B) & 0xFF;
    archive = SP_MENU_FRAMES;
    frame_offset = archive[frame_index];
    self->unk42 = 0x7947;
    self->animation_step.fields.frame_index = 0;
    self->unk68 = &D_8010D060;
    self->unk54 = NULL;
    self->unk58 = NULL;
    self->sprite_frames = (u8*)archive + frame_offset;
    bg_offset = g_Player.bg_offset;
    self->unk61 = 0;
    self->unk75 = 0;
    self->unk67 = 0;
    self->ext.item_2.unk80 = 1;
    self->bg_offset = bg_offset;
    background_objects[0].unk2C = 0;
    self->unk6 = 0;
    self->unk5 = 0;
    self->state++;
}

void func_800C39AC(struct ItemObj* arg0)
{
    D_8010D050[arg0->unk5](arg0);
    func_8002E184(PLAYER_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0xC0, 0x80);
}

void func_800C3A0C(struct ItemObj* arg0)
{
    arg0->state++;
}

void func_800C3A20(struct ItemObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800C3A40(struct ItemObj* arg0)
{
    D_8010D064[arg0->unk6](arg0);
}

void func_800C3A7C(struct ItemObj* arg0)
{
    if (g_Player.unk5 != 0) {
        arg0->unk7C.timer = 0x4000;
        func_80028BAC(0x20, 1, 1);
        arg0->unk6 = (u8)arg0->unk6 + 1;
    }
}

void func_800C3AD4(struct ItemObj* arg0)
{
    if (background_objects[0].unk34 != 0) {
        return;
    }

    if (arg0->y_pos.i.hi == 0x8D0) {
        arg0->unk6++;
        return;
    }

    if (arg0->unk7C.timer <= 0xFFFF) {
        arg0->unk7C.timer += FIXED(0.0625);
    }

    arg0->y_pos.val -= arg0->unk7C.timer;
}

void func_800C3B40(struct ItemObj* arg0)
{
    background_objects[0].unk28 = 0x2D0;
    background_objects[0].unk2A = 0x2D0;
    background_objects[0].unk47 = 1;
    func_8001540C(5, 5, NULL);
    arg0->unk6 = 0;
    arg0->unk5++;
}

INCLUDE_ASM("main/nonmatchings/items/item_14", func_800C3BA4);

void func_800C3C9C(struct ItemObj* arg0)
{
    if (background_objects[0].unk34 == 0) {
        background_objects[0].unk22 = 0x100;
        background_objects[0].unk2A = 0x100;
        background_objects[0].unk2C = 0x60;
        arg0->unk5++;
    }
}

void func_800C3CE4(struct ItemObj* arg0)
{
    background_objects[0].unk47 = 2;
}

void (*D_8010D040[])(struct ItemObj*) = {
    func_800C38C8,
    func_800C39AC,
    func_800C3A0C,
    func_800C3A20,
};

void (*D_8010D050[4])(struct ItemObj*) = {
    func_800C3A40,
    func_800C3BA4,
    func_800C3C9C,
    func_800C3CE4,
};

struct Unk_unk68 D_8010D060 = { 0, 0xFD, 0x80, 0x20 };

void (*D_8010D064[3])(struct ItemObj*) = {
    func_800C3A7C,
    func_800C3AD4,
    func_800C3B40,
};
