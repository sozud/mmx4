// MainObj, main_object_update_funcs[21]
// 80054C50..80054FE8
#include "common.h"

void func_80054C50(struct MainObj* arg0)
{
    D_800FC9FC[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_21", func_80054CA8);

INCLUDE_ASM("main/nonmatchings/mains/main_21", func_80054D8C);

void func_80054EF8(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event == 1) {
        arg0->state = 3;
    }
}

void func_80054F14(struct MainObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_80054F34(struct MainObj* arg0)
{
    if (arg0->ext.main_21.timer_80 == 0) {
        if (arg0->ext.main_21.timer_82 == 0) {
            arg0->unk5 = 3;
            func_80015D60(arg0, 0);
            return;
        }
        arg0->ext.main_21.timer_82--;
        return;
    }
    arg0->ext.main_21.timer_80--;
}

void func_80054F98(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event == 1) {
        arg0->unk2C = 0x5000;
        arg0->unk5 = 4;
    }
}

void func_80054FBC(struct MainObj* arg0)
{
    func_8002B694((struct AnimatedObj*)arg0);
}

void func_80054FDC(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_21.saved_unk5;
}
