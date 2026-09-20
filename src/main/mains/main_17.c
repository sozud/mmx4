// MainObj, main_object_update_funcs[17]
// 8004FF90..80050708
#include "common.h"

void func_8004FF90(struct MainObj* arg0)
{
    D_800FBEB4[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

void func_8004FFE0(struct MainObj* arg0)
{
    arg0->unk5C = 6;
    arg0->unk60 = 2;
    arg0->unk61 = 0;
    arg0->collision_data = D_80106AF4;
    arg0->bg_offset = (u8)g_Player.bg_offset;
    arg0->unk16 = 6;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->animation_table = (const u8* const*)D_800FBE94;
    arg0->unk68 = &D_800FBE08;
    arg0->unk54 = &D_800FBE00;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk50 = &D_800FBE04;
    func_800506D8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 0);
    arg0->ext.main_17.unk80 = 4;
    arg0->ext.main_17.unk84 = 3;
    arg0->ext.main_17.unk88 = 0xC;
    arg0->ext.main_17.unk8C = 0;
    arg0->state = 1;
    arg0->unk5 = 2;
    arg0->unk6 = 0;
    arg0->ext.main_17.saved_unk5 = arg0->y_pos.val;
}

INCLUDE_ASM("main/nonmatchings/mains/main_17", func_800500D4);

void func_80050238(struct MainObj* arg0)
{
    arg0->ext.main_17.unk80 = 0;
    arg0->ext.main_17.unk84 = 0;
    arg0->ext.main_17.unk88 = 0;
    arg0->ext.main_17.unk8C = 0;
    arg0->ext.main_17.unk90 = 0;
    arg0->ext.main_17.saved_unk5 = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8005026C(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.raw[4];
}

INCLUDE_ASM("main/nonmatchings/mains/main_17", func_80050278);

void func_80050418(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_800506D8(ANIMATED_OBJECT(arg0));
        arg0->unk5 = 2;
        arg0->ext.main_17.unk80 = 4;
        arg0->unk6 = 0;
        arg0->ext.main_17.unk84 = 3;
        func_80015D60(arg0, 0);
    }
}

void func_80050480(struct MainObj* arg0)
{
    if (arg0->unk20 != 0) {
        func_8002B694(ANIMATED_OBJECT(arg0));
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        arg0->unk68 = &D_800FBE14;
        arg0->unk54 = &D_800FBE0C;
        arg0->unk50 = &D_800FBE10;
    }
    if (arg0->animation_step.fields.event == 1) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(4, D_800FBEB0, arg0);
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        func_80015D60(arg0, 0);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_17", func_80050540);

void func_80050644(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->ext.main_17.unk80 = 4;
        func_80015D60(arg0, 0);
    }
}

void func_80050690(struct MainObj* arg0)
{
    if (arg0->unk67 == 0 && !(arg0->unk70 & 8)) {
        arg0->unk5 = 5;
        arg0->unk2C = 0x4200;
        arg0->unk6 = 0;
        arg0->unk24 = 0;
        arg0->unk67 = 1;
    }
}

void func_800506D8(struct AnimatedObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}
