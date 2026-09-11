// MainObj, main_object_update_funcs[20]
// 8005458C..80054C50
#include "common.h"

void func_8005458C(struct MainObj* arg0)
{
    D_800FC990[arg0->state](arg0);
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    CollisionRelated(PLAYER_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_20", func_800545EC);

void func_80054710(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    func_80015D60(arg0, 0);
}

void func_80054738(struct MainObj* arg0)
{
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_20", func_80054758);

INCLUDE_ASM("main/nonmatchings/mains/main_20", func_800548B8);

INCLUDE_ASM("main/nonmatchings/mains/main_20", func_80054B38);

void func_80054B98(struct MainObj* arg0)
{
    arg0->unk7C = 1;
    func_8002B108(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_20", func_80054BBC);
