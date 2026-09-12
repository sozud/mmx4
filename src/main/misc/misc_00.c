// MiscObj, misc_object_update_funcs[0]
// 800C7A68..800C7BF4
#include "common.h"

extern void (*D_8010D9EC[])(struct MiscObj*);

void func_800C7A68(struct MiscObj* arg0)
{
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    D_8010D9EC[arg0->state](arg0);
}
void func_800C7AB0(struct MiscObj* arg0)
{
    arg0->active = 1;
    arg0->unk16 = 0x11;
    arg0->unk40 = 0x1511;
    arg0->animation_step.fields.frame_index = (u8)arg0->unk2;

    arg0->bg_offset = (u8)g_Player.bg_offset;
    arg0->unk15 = 0;

    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[0x24 / 4];

    arg0->unk42 = 0x7904;
    arg0->state++;
}
void func_800C7B0C(struct MiscObj* arg0)
{
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x30, 0x10);
    } else {
        arg0->state++;
    }
}
void func_800C7B60(struct MiscObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/misc/misc_00", func_800C7B80);
