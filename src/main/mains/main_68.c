// MainObj, main_object_update_funcs[68]
// 80083218..80085F08
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083218);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_8008329C);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800833D0);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800834B0);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083544);

void func_80083574(struct MainObj* arg0)
{
    D_80104340[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800835B0);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083688);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083710);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800837FC);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083954);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800839B0);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083A18);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083A58);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083B20);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083BB8);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083C2C);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083D30);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083DC8);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083E44);

void func_80083E70(struct MainObj* arg0)
{
    D_80104370[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083EAC);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083F6C);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083FFC);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800840D0);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80084154);

void func_800841D4(struct MainObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
    }
}

void func_80084218(struct MainObj* arg0)
{
    D_80104388[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80084254);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80084338);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80084394);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_8008442C);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800844AC);

void func_80084534(struct MainObj* arg0)
{
    D_801043A4[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80084570);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800845C0);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_8008460C);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800846D0);

void func_80084724(struct MainObj* arg0)
{
    func_80015DC8(arg0);
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 5;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
    }
}

void func_80084774(struct MainObj* arg0)
{
    D_801043BC[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800847B0);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80084870);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80084910);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_8008498C);

void func_800849FC(struct MainObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = 6;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
    }
}

void func_80084A40(struct MainObj* arg0)
{
    D_801043CC[arg0->unk6](arg0);
}

void func_80084A7C(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk50 = (const u8*)&D_80103F00;
        arg0->unk54 = (const u8*)&D_80103F04;
        arg0->unk6++;
        func_80015D60(arg0, 0x15);
        arg0->unk7C = 0x28;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80084B14);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80084CD4);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80084DB8);

void func_80084E10(struct MainObj* arg0)
{
    D_801043E0[arg0->unk6](arg0);
}

void func_80084E4C(struct MainObj* arg0)
{
}

void func_80084E54(struct MainObj* arg0)
{
    struct VisualObj* visual;

    if (arg0->unk7 == 0) {
        arg0->unk7++;
        arg0->unk7C = 0x78;
        func_80015D60(arg0, 0x29);
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 0x20;
            visual->unk2 = 5;
        }
    } else {
        func_80015DC8(arg0);
        arg0->unk7C--;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80084EE4);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_8008502C);

void func_800851FC(struct BarObj* arg0)
{
    D_80104424[arg0->unk2](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085238);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800852C4);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800853A4);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085460);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085580);

void func_80085604(struct MainObj* arg0)
{
    D_8010444C[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085640);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800856C4);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085768);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800857C8);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085814);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800858DC);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085988);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085A44);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085BE4);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085C38);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085D38);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085DCC);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085E70);

void func_80085ECC(struct MainObj* arg0)
{
    D_8010448C[arg0->state](arg0);
}
