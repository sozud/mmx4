// ItemObj, item_object_update_funcs[4]
// 800C081C..800C0E74
#include "common.h"

void func_800C081C(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010C908[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_04", func_800C0864);

INCLUDE_ASM("main/nonmatchings/items/item_04", func_800C09C4);

INCLUDE_ASM("main/nonmatchings/items/item_04", func_800C0C78);

void func_800C0D98(struct ItemObj* arg0)
{
    if (arg0->unk2 == 0) {
        background_objects[0].unk1C = 0x11C0;
        background_objects[0].unk24 = 0x11C0;
    }
    if (arg0->unk88 != 0) {
        func_800C0DFC(arg0);
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800C0DFC(struct ItemObj* arg0)
{
    s32* destination;
    s32* source;
    u32 i;

    destination = SP_PALETTE_WORDS + 0x3B8;
    if (arg0->unk88 != 0) {
        source = SP_ARC_30 + 0x268;
    } else {
        source = SP_ARC_30 + 0x2A0;
    }
    i = 0;
    do {
        *destination++ = *source++;
        i++;
    } while (i < 0x38);
    need_palette_load |= 1;
}

void (*D_8010C908[])(struct ItemObj*) = {
    func_800C0864,
    func_800C09C4,
    func_800C0C78,
    func_800C0D98,
};
