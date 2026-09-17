// ItemObj, item_object_update_funcs[16]
// 800C3FEC..800C413C
#include "common.h"

void func_800C3FEC(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010D100[arg0->state](arg0);
    func_8002E184(arg0);
    if (!(BASE_OBJECT(arg0->unk7C.object)->on_screen & 1)) {
        if ((g_Player.unk4A != 0) || (arg0->unk76 != 0)) {
            arg0->ext.owner->active = 1;
        }
    }
    func_8002B318(BASE_OBJECT(arg0), 0x200, 0x100);
}

void func_800C40A4(struct ItemObj* arg0)
{
    arg0->unk16 = 6;
    arg0->unk68 = &D_8010D0FC;
    arg0->x_vel.val = FIXED(1);
    arg0->unk5C = 0;
    arg0->unk61 = 0;
    arg0->unk54 = 0;
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk75 = 1;
    arg0->unk76 = 0;
    arg0->state = 1;
    arg0->unk5 = 0;
}

void func_800C40F0(struct ItemObj* arg0)
{
    if (arg0->unk5 == 0) {
        if (arg0->x_pos.i.hi >= 0x1AA1) {
            arg0->unk5 = 1;
            return;
        }
        func_8002B718(MOVING_OBJECT(arg0));
    }
}

struct Unk_unk68 D_8010D0FC = { 0x27, 0x3C, 0x38, 0x1F };

void (*D_8010D100[])(struct ItemObj*) = {
    func_800C40A4,
    func_800C40F0,
};
