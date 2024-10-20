#include "common.h"

// entrypoint
void func_80012024(void)
{
    func_800DAE84();
    func_8001213C();
    while (1) {
        VSync(0);
        PutDispEnv(&cur_draw_info->dispenv);
        PutDrawEnv(&cur_draw_info->drawenv);
        DrawOTag(&cur_draw_info->unk9C);
        SP_DRAW_INFO_POS ^= 1;
        cur_draw_info = &draw_infos[SP_DRAW_INFO_POS];
        ClearOTagR(&cur_draw_info->unk70, 0xC);
        func_800168D8();
        func_800169D8();
        func_80012328();
        func_80015E0C();
        D_80141BD8.unk0++;
        func_80012600();
        func_80014780();
        DrawSync(0);
        func_80015E54();
        load_palette();
        DrawSync(0);
        func_80012454();
    }
}

void func_8001213C(void)
{
    ResetCallback();
    StopCallback();
    ResetGraph(0);
    func_800E9040();
    SetGeomOffset(0xA0, 0x78);
    SetGeomScreen(0x200);
    InitPAD(&D_80166D68, 0x22, &D_8012F46C, 0x22);
    StartPAD();
    InitCARD(1);
    StartCARD();
    _bu_init();
    InitMemcards();
    func_80014DC4();
    func_80013588();
    ChangeClearPAD(0);
    ClearImage(&D_800EE450, 0U, 0U, 0U);
    DrawSync(0);
    SetDefDrawEnv(&draw_infos[0].drawenv, 0, 0, 0x140, 0xF0);
    SetDefDispEnv(&draw_infos[0].dispenv, 0, 0xF0, 0x140, 0xF0);
    SetDefDrawEnv(&draw_infos[1].drawenv, 0, 0xF0, 0x140, 0xF0);
    SetDefDispEnv(&draw_infos[1].dispenv, 0, 0, 0x140, 0xF0);
    func_800122E0(&draw_infos[0]);
    func_800122E0(&draw_infos[1]);
    func_80012560();
    cur_random = 0xD37; // seed RNG
    SP_DRAW_INFO_POS = 0;
    cur_draw_info = &draw_infos[0];
    D_8013BD44 = 0;
    D_80141BD2 = 0x78;
    func_80012740(0, &func_8001D064);
}

void func_800122E0(struct DrawInfo* arg0)
{
    ClearOTagR(&arg0->unk70, 0xC);
    arg0->drawenv.dtd = 0;
    arg0->drawenv.isbg = 1;
    arg0->drawenv.r0 = 0;
    arg0->drawenv.g0 = 0;
    arg0->drawenv.b0 = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/2824", func_80012328);

INCLUDE_ASM("asm/us/main/nonmatchings/2824", func_80012454);

INCLUDE_ASM("asm/us/main/nonmatchings/2824", func_80012560);

INCLUDE_ASM("asm/us/main/nonmatchings/2824", func_80012600);

INCLUDE_ASM("asm/us/main/nonmatchings/2824", func_80012740);

void func_800127C8(s32 arg0)
{
    D_801F8300[1] = arg0;
    D_801F8300[0] = 1;
    ChangeTh(0xFF000000);
}

void func_800127FC(s32 arg0) {
    (*(s16** )0x801F8300)[0] = 0;
    EnterCriticalSection();
    CloseTh((*(s32** )0x801F8300)[2]);
    ExitCriticalSection();
    ChangeTh(0xFF000000);
}

INCLUDE_ASM("asm/us/main/nonmatchings/2824", func_80012854);

void func_800128B8(s32 arg0)
{
    D_8012F490 = arg0;
    D_800EE458 = 1;
    ChangeTh(0xFF000000);
}

INCLUDE_ASM("asm/us/main/nonmatchings/2824", func_800128EC);

INCLUDE_ASM("asm/us/main/nonmatchings/2824", func_80012910);

void func_80012934(s32 arg0)
{
}

void func_8001293C(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/2824", func_80012944);

void func_800129A4(s8 arg0)
{
    if (D_80141BDC[0] == 0) {
        D_80141BDC[0] = 1;
        D_80141BDC[1] = arg0;
        func_80012740(2, func_80012A3C);
    }
}

void func_800129F0(s32 arg0)
{
    if (D_80141BDC[0] == 0) {
        D_80141BDC[0] = -1;
        D_80141BDC[1] = arg0;
        func_80012740(2, func_80012A3C);
    }
}
