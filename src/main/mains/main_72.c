// MainObj, main_object_update_funcs[72]
// 8008ADFC..8008BA38
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008ADFC);

void func_8008AE94(struct MainObj* arg0)
{
    if ((arg0->x_pos.val - g_Player.x_pos.val) < 0) {
        arg0->unk15 = 0x40;
        return;
    }

    arg0->unk15 = 0;
}

void func_8008AEC4(struct BaseObj* arg0, s8 arg1)
{
    arg0->unk5 = arg1;
    arg0->unk6 = 0;
}

void func_8008AED0(struct MainObj* arg0)
{
    arg0->x_pos.val += arg0->unk20;
}

void func_8008AEE8(struct MainObj* arg0)
{
    if (arg0->unk15 != 0) {
        arg0->unk20 = FIXED(1.375);
    } else {
        arg0->unk20 = FIXED(-1.375);
    }
}

void func_8008AF10(struct MainObj* arg0)
{
    s32 value;

    value = arg0->ext.main_72.unk84 << 8;
    if (arg0->unk15 == 0) {
        value = -value;
    }
    arg0->unk20 = value;
}

void func_8008AF30(struct MainObj* arg0, s32 arg1)
{
    s32 v;
    struct ShotObj* obj = find_free_shot_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x2F;
        obj->unk2 = arg1;
        obj->x_pos.i.hi = arg0->x_pos.i.hi;
        obj->y_pos.i.hi = arg0->y_pos.i.hi;
        obj->animation_table = arg0->animation_table;
        obj->unk40 = arg0->unk40;
        obj->unk3C = arg0->sprite_frames;
        v = (u8)func_8002938C(0x48);
        obj->unk42 = SOME_COORDINATE_CONVERSION(v);
        obj->unk16 = arg0->unk16;
        obj->unk7C = arg0;
        obj->unk15 = arg0->unk15;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B020);

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B188);

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B270);

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B33C);

void func_8008B42C(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6++;
        arg0->unk67 = 0;
        func_80015D60(arg0, 4);
        arg0->unk70 |= 8;
        func_8001540C(2, 0x45, arg0);
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        func_8008AEC4(BASE_OBJECT(arg0), 7);
        return;
    }
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B4B8);

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B5C0);

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B69C);

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B7D4);

void func_8008B898(struct MainObj* arg0)
{
    func_8008AEC4(BASE_OBJECT(arg0), 2);
}

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B8B8);

void func_8008B984(struct MainObj* arg0)
{
    arg0->unk42 &= 0x7FFF;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8008B9B0(void)
{
}

void func_8008B9B8(void)
{
}

void func_8008B9C0(struct MainObj* arg0)
{
    D_80104F3C[arg0->unk5](arg0);
}

void func_8008B9FC(struct MainObj* arg0)
{
    D_80104F48[arg0->state](arg0);
}
