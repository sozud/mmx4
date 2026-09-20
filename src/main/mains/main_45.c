// MainObj, main_object_update_funcs[45]
// 80065B8C..80066A48
#include "common.h"

void func_80065B8C(struct MainObj* arg0)
{
    D_800FF964[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_45", func_80065BC8);

INCLUDE_ASM("main/nonmatchings/mains/main_45", func_80065CD4);

void func_80065DCC(struct MainObj* arg0)
{
    s16 timer;

    func_80066970();
    timer = (u16)arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        if (func_8002BAD0(1, -0x20, 0x80) == 0x1C) {
            arg0->state = 3;
            arg0->unk5 = 0;
        } else {
            arg0->unk7C = 1;
        }
    }
    if ((arg0->unk6 == 0) && ((arg0->x_pos.i.hi + 0x69 >= g_Player.x_pos.i.hi) || (g_Player.x_pos.i.hi >= 0x1B36))) {
        func_80036AE4(0x14, 0x40);
        arg0->unk6 = 1;
    }
    func_8002E184(PLAYER_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x100, 0x100);
}

INCLUDE_ASM("main/nonmatchings/mains/main_45", func_80065EA4);

INCLUDE_ASM("main/nonmatchings/mains/main_45", func_800661AC);

INCLUDE_ASM("main/nonmatchings/mains/main_45", func_8006630C);

INCLUDE_ASM("main/nonmatchings/mains/main_45", func_80066478);

void func_80066580(struct MainObj* arg0)
{
    D_800FF980[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_45", func_800665BC);

void func_80066804(struct MainObj* arg0)
{
    if (arg0->x_pos.i.hi >= 0x19A1) {
        engine_obj.enable_boss = 1;
        engine_obj.unk25 = 2;
        engine_obj.boss_ptr = arg0;
        arg0->unk6 = 2;
    }
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_80066858(struct MainObj* arg0)
{
    if (arg0->x_pos.i.hi >= 0x1AA1) {
        arg0->unk7E = 3;
        arg0->unk6 = 3;
    } else {
        func_8002B718(MOVING_OBJECT(arg0));
    }
}

void func_8006689C(struct MainObj* arg0)
{
    s16 timer;

    if (arg0->unk5C < 0x30) {
        timer = (u16)arg0->unk7E - 1;
        arg0->unk7E = timer;
        if (timer == 0) {
            func_8001540C(0, 0xE, NULL);
            arg0->unk7E = 3;
        }
        arg0->unk5C = (u8)arg0->unk5C + 1;
        return;
    }
    arg0->ext.main_45.unk88 = 0xFF;
    arg0->unk5 = 1;
    arg0->unk6 = 0;
    func_80036B18();
}

void func_8006692C(struct MainObj* arg0)
{
    D_800FF990[arg0->unk6](arg0);
}

void func_80066968(void)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_45", func_80066970);
