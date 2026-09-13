// MainObj, main_object_update_funcs[34]
// 8005E570..8005EC58
#include "common.h"

void func_8005E570(struct MainObj* arg0)
{
    D_800FE168[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_34", func_8005E5C0);

void func_8005E754(struct MainObj* arg0)
{
    D_800FE174[arg0->unk5](arg0);
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    arg0->state = 2;
    arg0->unk5 = 0;
}

void func_8005E7CC(struct MainObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8005E7EC(struct MainObj* arg0)
{
    if (D_800FDFBC[arg0->unk2] >= arg0->x_pos.i.hi) {
        SP_CUR_MAIN_OBJ->ext.main_34.unk80 = 1;
        func_80015D60(arg0, 0);
        arg0->unk5 = 1;
    }
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_8005E860(struct MainObj* arg0)
{
    if (--SP_CUR_MAIN_OBJ->ext.main_34.unk80 <= 0) {
        func_80015D60(arg0, 2);
        arg0->unk5 = 2;
    }
}

void func_8005E8B4(struct MainObj* arg0)
{
    D_800FE19C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_34", func_8005E8F0);

void func_8005E9C0(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event == 2) {
        if (arg0->unk2 == arg0->animation_step.fields.event) {
            arg0->unk68 = &D_800FDFB8;
        }
        arg0->unk6++;
        func_80015D60(arg0, 3);
    }
}

void func_8005EA18(struct MainObj* arg0)
{
    s32 value20;
    s32 value24;

    value20 = FIXED(-0.9375);
    value24 = FIXED(1.75);
    arg0->unk24 = value24;
    arg0->unk2C = FIXED(0.5);
    arg0->unk20 = value20;
    arg0->unk67 = 1;
    func_8002B694(ANIMATED_OBJECT(arg0));
    arg0->unk6++;
}

void func_8005EA78(struct MainObj* arg0)
{
    s8 step;
    u8 count;

    if (arg0->unk70 & 8) {
        arg0->unk67 = 0;
        count = SP_CUR_MAIN_OBJ->ext.main_34.unk82 + 1;
        SP_CUR_MAIN_OBJ->ext.main_34.unk82 = count;
        if (count == 3) {
            step = arg0->unk6 + 1;
        } else {
            step = arg0->unk6 - 1;
        }
        arg0->unk6 = step;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_34", func_8005EAF8);

INCLUDE_ASM("main/nonmatchings/mains/main_34", func_8005EB40);

INCLUDE_ASM("main/nonmatchings/mains/main_34", func_8005EBF4);

void func_8005EC38(struct MainObj* arg0)
{
    func_8002B718((struct MovingObj*)arg0);
}
