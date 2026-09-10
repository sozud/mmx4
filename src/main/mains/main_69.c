// MainObj, main_object_update_funcs[69]
// 80085F08..80088BA0
#include "common.h"

void func_80085F08(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_801047D4[arg0->state](arg0);
}

void func_80085F50(struct BarObj* arg0)
{
    D_801047E0[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80085F8C);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086008);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086124);

void func_80086268(struct MainObj* arg0)
{
    D_8010480C[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800862A4);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800862F4);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800863E8);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086488);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_8008649C);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800864FC);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_8008654C);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086640);

void func_80086704(struct PlayerObj* arg0)
{
    D_80104830[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086740);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800867C4);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086860);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086900);

void func_800869BC(struct MainObj* arg0)
{
    if (abc_object.unkC == 0) {
        arg0->unk6++;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800869F8);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086A6C);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086B08);

void func_80086B60(struct MainObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
}

void func_80086B74(struct MainObj* arg0)
{
    D_80104850[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086BB0);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086C00);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086C70);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086D04);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086D84);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086E2C);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086E80);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086F28);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086F78);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_8008700C);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80087088);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800870FC);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80087168);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800871C4);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80087254);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800872E8);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80087364);

void func_80087414(struct MainObj* arg0)
{
    D_80104894[arg0->unk6](arg0);
    func_80088974(arg0);
    is_on_screen((struct BaseObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_8008746C);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_8008752C);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_8008759C);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80087604);

void func_8008765C(struct MainObj* arg0)
{
    D_801048A4[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80087698);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80087708);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800877A4);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80087860);

void func_80087928(struct MainObj* arg0)
{
    D_801048B4[arg0->unk6](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
    is_on_screen((struct BaseObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80087980);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80087A00);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80087AF8);

void func_80087B98(struct MainObj* arg0)
{
    D_801048C0[arg0->unk6](arg0);
    is_on_screen((struct BaseObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80087BE8);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80087C70);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80087D3C);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80087E0C);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80087ED4);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80087F30);

void func_80087F78(struct MainObj* arg0)
{
    D_801048D8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80087FB4);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80088020);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800880BC);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80088140);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800881F8);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80088338);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800883CC);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800884D0);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80088530);

void func_80088584(struct MainObj* arg0)
{
    D_801048FC[arg0->unk6](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
    is_on_screen((struct BaseObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800885DC);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80088658);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800886A0);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800886F0);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800887DC);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_8008888C);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800888D0);

void func_80088974(struct MainObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

void func_800889A4(struct BaseObj* arg0)
{
    s16 right_edge = background_objects[0].x_pos.i.hi + 0xB0;

    if (arg0->x_pos.i.hi < right_edge) {
        arg0->unk15 = 0x40;
    } else {
        arg0->unk15 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800889DC);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80088AD0);
