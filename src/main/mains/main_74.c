// MainObj, main_object_update_funcs[74]
// 8008D460..8008FB38
#include "common.h"

#ifdef VERSION_JP
extern u8 D_8013B980_jp[];
#define D_8013B8A0_VERSION D_8013B980_jp
#else
#define D_8013B8A0_VERSION D_8013B8A0
#endif

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008D460);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008D4E8);

void func_8008D548(struct MainObj* arg0)
{
    if ((D_801406AC == 2) && (D_8013BD40 == 0)) {
        D_80171EA8 = 1;
        arg0->unk5++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008D590);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008D5C8);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008D764);

void func_8008D830(struct MainObj* arg0)
{
    D_801058B0[arg0->unk5](arg0);
}

void func_8008D86C(struct MainObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008D874);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008D8DC);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008D95C);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008D9C8);

void func_8008DAAC(struct MainObj* arg0)
{
    D_801058C4[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008DAE8);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008DC5C);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008DC9C);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008DD38);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008DDE8);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008DE5C);

void func_8008DEC4(struct MainObj* arg0)
{
    D_801058DC[arg0->unk6](arg0);
    func_8002B318((struct BaseObj*)arg0, 0x40, 0x40);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008DF1C);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008DF8C);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008E040);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008E0CC);

void func_8008E14C(struct MainObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}

void func_8008E18C(struct MainObj* arg0)
{
    D_801058F0[arg0->unk6](arg0);
    func_8002B318((struct BaseObj*)arg0, 0x40, 0x40);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008E1E4);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008E244);

void func_8008E318(struct MainObj* arg0)
{
    D_80105904[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008E354);

void func_8008E3C0(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        D_8013B8A0_VERSION[0] = 0x1E;
    }

    func_80015DC8(arg0);
}

void func_8008E404(struct MainObj* arg0)
{
    D_8010590C[arg0->unk6](arg0);
    func_8002B318((struct BaseObj*)arg0, 0x40, 0x40);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008E45C);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008E4BC);

void func_8008E590(struct MainObj* arg0)
{
    D_80105914[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008E5CC);

void func_8008E638(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        D_8013B8A0_VERSION[0] = 0xA;
    }
    func_80015DC8(arg0);
}

void func_8008E67C(struct MainObj* arg0)
{
    D_8010591C[arg0->unk6](arg0);
    func_8002B318((struct BaseObj*)arg0, 0x40, 0x40);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008E6D4);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008E748);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008E8C8);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008E99C);

void func_8008E9B8(struct MainObj* arg0)
{
    D_80105924[arg0->unk6](arg0);
    if (arg0->animation_step.fields.event != 0) {
        D_8013B8B0 = &D_80105374;
    } else {
        D_8013B8B0 = NULL;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008EA3C);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008EA88);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008EAE4);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008EBC0);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008EC48);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008ED18);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008EDE8);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008EED4);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008EF94);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F01C);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F0A4);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F134);

void func_8008F16C(struct MainObj* arg0)
{
    D_80105954[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F1A8);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F3F4);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F4BC);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F578);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F6FC);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F76C);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F7F0);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F884);

void func_8008F938(struct MainObj* arg0)
{
    D_80105994[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F974);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008FA0C);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008FA88);
