#include "common.h"

// uncomment to skip movies
// #define SKIP_MDEC

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80012A3C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80012D28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80012D4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80012D68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80012D88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80012DC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80012E18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80012E2C);

void func_80012E38(void)
{
    func_80013AD8(0x40, 0, 0);
    func_80014C70();
    func_80013890(0x41, 0x801F3000);
    func_80014C70();
}

void func_80012E80()
{
    func_80013AD8(0, 0, 0);
    func_80014C70();
}

void func_80012EB0(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80012EB8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80012F44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80013014);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001326C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80013404);

void func_80013530(void)
{
    func_800129F0(0x10);
    if (D_80141BDC[0] != 0) {
        do {
            func_80013404(0);
            func_800127C8(1);
        } while (D_80141BDC[0] != 0);
    }
}

void func_80013588(s32 arg0)
{
    u8 sp10;
    sp10 = 0xA0;
    do {
    } while (CdInit() == 0);
    do {

    } while (CdControl(0xE, &sp10, 0) == 0);
    VSync(3);
    D_80137CE4 = 0;
    D_801406AC = 0;
    D_8013BD40 = 0;
    D_801374B8 = 0;
    D_801374B4 = 0;
    D_80137CF0 = 0;
    D_80137CF4 = 0;
    func_80016334();
}

s32 func_80013614(s32 arg0, s32* arg1)
{
    struct Unk5* temp_v0;
    temp_v0 = &D_800F0E18[arg0];
    *arg1 = temp_v0->unk4;
    D_80137CC0 = temp_v0->unk8;
    return temp_v0->unk0;
}

void func_80013650(void)
{

    if (D_80137CD8 == 0) {
        CdReadyCallback(&MyCdReadyCallback);
    } else {
        CdReadyCallback(&func_80013E68);
    }
    while (CdControl(6, 0, 0) == 0)
        ;
    D_801406AC = 1;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800136B0);

void func_800137F0(void)
{
    CdReadyCallback(0);
    D_801406AC = 0;
    do {

    } while (CdControl(9, 0, 0) == 0);
    D_801406AC = 2;
    D_8015D9C8 = D_80137DC4;
    D_80142F70 = D_80137DD0;
}

u8 func_8001385C(void)
{
    u8 sp10;

    do {

    } while (CdControlB(1, 0, &sp10) == 0);
    return sp10;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80013890);

void func_80013968(void)
{
    u8 sp10;

    sp10 = 0xA0;
    D_801406AC = 0;
    D_80137CEC = 0;
    CdIntToPos(D_80137CCC, &D_80137CF8);
    D_80137CCC -= 1;
    do {
    loop_1:
        if (CdReady(1, NULL) != 0) {
            goto loop_1;
        }
        if (CdControl(0xEU, &sp10, NULL) == 0) {
            goto loop_1;
        }
        VSync(3);
    } while (CdControl(2U, &D_80137CF8.minute, NULL) == 0);
    func_80013650();
}

void MyCdReadyCallback(void)
{
    if (D_801406AC != 0) {
        D_80137CEC += 1;
        if (CdReady(1, NULL) != 1) {
        pos:
            CdReadyCallback(NULL);
            CdControlB(9U, NULL, NULL);
            D_801406AC = 0x80;
        } else {
            if (func_800136B0() != -1) {
                if (D_80137CBC == 0) {
                    func_800137F0();
                }
            } else {
                goto pos;
            }
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80013AD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80013DA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80013E68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80014140);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800141BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800142BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80014514);

s32 func_800147AC();
extern u8 D_8013BD40;

void func_80014780(void)
{
    if (D_8013BD40 != 0) {
        func_800147AC();
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800147AC);

void func_800148E4(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800148EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80014968);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80014A90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80014C70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80014DC4);

void func_8001512C(void)
{
    SsStart();
    SsSetMVol(0x7F, 0x7F);
    SsSetSerialAttr(0, 0, 0);
    SsSetSerialVol(0, 0x4A, 0x4A);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80015178);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80015284);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800153D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001540C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800154E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800157AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80015930);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80015A10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80015A50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80015C10);

void func_80015D60(struct Unk19* arg0, s32 arg1)
{
    arg0->unk34 = arg0->unk30[arg1];
    arg0->unk17 = arg1;
    arg0->unk48 = 0xFF;
    arg0->unk44 = *arg0->unk34;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80015D90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80015DC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80015E0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80015E54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80015ECC);

void func_80016004(void)
{
    if (D_80166BB0 != 0) {
        if (D_80166BB0 & 1) {
            LoadImage(&D_800F1658, *(volatile u32**)0x1F800028);
        } else if (D_80166BB0 & 2) {
            LoadImage(&D_800F1658, &D_80141F70);
        }

        D_80166BB0 = 0;
    }
}

// copy scratchpad to memory location
void func_80016074(void)
{
    u16* var_a0;
    u16* var_a1;
    u32 var_v1;

    var_a1 = &D_80141F70;
    var_a0 = *(u16**)0x1F800028;
    var_v1 = 0;
    do {
        *var_a1++ = *var_a0++;
        var_v1 += 1;
    } while (var_v1 < 0x800U);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800160AC);

extern s32 D_800F1660;
extern s32 D_800F1860;

void func_800160F4(void)
{
    LoadImage(&D_800F1860, &D_800F1660);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80016124);

void func_80016334(void)
{
    func_80016420(0);
    D_80171EA9 = 1;
    D_8013956C = 1;
    D_801419AC = 0;
    D_801441B8 = 0;
    D_80141F4A = 0;
    D_8013952C = 0;
    D_80141BD4 = 0;
    D_80139524 = 0x80;
    D_80139530 = 0;
    D_80141BD0 = 0;
    D_80139564 = 0;
    D_801441B0 = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800163BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800163EC);

void func_80016448(u8 arg0);
extern u8 D_80139524;

void func_80016420(s8 arg0)
{
    D_80139524 = arg0;
    func_80016448(arg0);
}

void func_80016448(u8 arg0)
{
    s32 temp_v0;
    D_80139528 = arg0;
    if (D_80171EA9 == 1) {
        D_80139520.val0 = arg0;
        D_80139520.val1 = 0;
        D_80139520.val2 = arg0;
        D_80139520.val3 = 0;
    } else {
        temp_v0 = arg0 >> 1;
        D_80139520.val0 = temp_v0; // volume for CD(L) -> SPU (L)
        D_80139520.val1 = temp_v0; // volume for CD(L) -> SPU (R)
        D_80139520.val2 = temp_v0; // volume for CD(R) -> SPU (L)
        D_80139520.val3 = temp_v0; // volume for CD(R) -> SPU (R)
    }
    CdMix(&D_80139520);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800164D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001653C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001663C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800168D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800169D8);

extern s32 D_80139564;
extern s8 D_80141BD0;
extern s32 D_80141BD4;

void func_80016B38(void)
{
    D_80141BD0 = 0;
    D_80141BD4 = 0;
    D_80139564 = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80016B58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80016BDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80016C5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80016D0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80016DAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80016E34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80016E84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80016F0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80016FB4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80016FF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800170B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800170E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80017100);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80017268);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80017340);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800175AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800179BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80017E84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80017F2C);

// general movie playing code
#ifndef SKIP_MDEC
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80018000);
#else
void func_80018000(s32 temp)
{
    asm(".rept 184 ; nop ; .endr");
}
#endif

// capcom logo playing code
#ifndef SKIP_MDEC
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800182E8);
#else
void func_800182E8(void)
{
    asm(".rept 194 ; nop ; .endr");
}
#endif

void Set24BitDisp(s32 w, s32 h)
{
    RECT rect;
    old_dispenv[0] = draw_infos[0].dispenv;
    old_dispenv[1] = draw_infos[1].dispenv;
    ResetGraph(0);
    rect.x = 0;
    rect.y = 0;
    rect.w = 480;
    rect.h = 480;
    VSync(0);
    ClearImage(&rect, 0, 0, 0);
    DrawSync(0);
    SetDispMask(1);
    SetDefDispEnv(&draw_infos[0].dispenv, 0, 0, w, h);
    SetDefDispEnv(&draw_infos[1].dispenv, 0, 240, w, h);
    draw_infos[1].dispenv.isrgb24 = 1;
    draw_infos[0].dispenv.isrgb24 = 1;
    draw_infos[1].dispenv.isinter = 0;
    draw_infos[0].dispenv.isinter = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80018788);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80018AD0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80018B88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80018E50);

void func_80018EEC(void)
{
    do {

    } while (D_80139634 != 0);
    D_801395E4 = D_801395E8;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80018F18);

void func_80018FD0(u32 arg0)
{
    D_800F1D8C = arg0;
    if (D_80171EA9 != 0) {
        D_80139644.val0 = arg0;
        D_80139644.val1 = 0;
        D_80139644.val2 = arg0;
        D_80139644.val3 = 0;
    } else {
        D_80139644.val0 = arg0 >> 1; // volume for CD(L) -> SPU (L)
        D_80139644.val1 = arg0 >> 1; // volume for CD(L) -> SPU (R)
        D_80139644.val2 = arg0 >> 1; // volume for CD(R) -> SPU (L)
        D_80139644.val3 = arg0 >> 1; // volume for CD(R) -> SPU (R)
    }
    CdMix(&D_80139644);
}

void func_80019058(s8 arg0)
{
    u32 temp_v0;

    D_80171EA9 = arg0;
    if (arg0 & 0xFF) {
        D_80139644.val1 = 0;
        D_80139644.val3 = 0;
        D_80139644.val0 = D_800F1D8C;
        D_80139644.val2 = D_800F1D8C;
    } else {
        temp_v0 = D_800F1D8C >> 1;
        D_80139644.val0 = temp_v0; // volume for CD(L) -> SPU (L)
        D_80139644.val1 = temp_v0; // volume for CD(L) -> SPU (R)
        D_80139644.val2 = temp_v0; // volume for CD(R) -> SPU (L)
        D_80139644.val3 = temp_v0; // volume for CD(R) -> SPU (R)
    }
    CdMix(&D_80139644);
}

extern s32 D_80139614;

void func_800190F0(s32 arg0)
{
    D_80139614 = arg0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80019100);

extern s32 D_80139610;

void func_80019208(void)
{
    D_80139610 += 1;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80019228);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800192F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800193D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800194C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001961C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001989C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80019B64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80019BA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80019BF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80019D04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80019EF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001A178);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001A308);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001A498);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001A710);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001A7D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001A860);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001A8E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001A9EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001AA98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001ABDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001AE8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001B10C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001B388);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001B4E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001B558);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001B644);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001B718);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001B7C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001B8B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001BCAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001BE10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001C008);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001C07C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001C210);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001C30C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001C3E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001C4B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001C5A8);

void InitMemcards(void)
{
    EnterCriticalSection();
    D_80139670 = OpenEvent(SwCARD, EvSpIOE, EvMdNOINTR, NULL);
    D_80139674 = OpenEvent(SwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    D_80139678 = OpenEvent(SwCARD, EvSpNEW, EvMdNOINTR, NULL);
    D_8013967C = OpenEvent(SwCARD, EvSpERROR, EvMdNOINTR, NULL);
    D_80139680 = OpenEvent(HwCARD, EvSpIOE, EvMdNOINTR, NULL);
    D_80139684 = OpenEvent(HwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    D_80139688 = OpenEvent(HwCARD, EvSpERROR, EvMdNOINTR, NULL);
    ExitCriticalSection();
    EnableEvent(D_80139670);
    EnableEvent(D_80139674);
    EnableEvent(D_80139678);
    EnableEvent(D_8013967C);
    EnableEvent(D_80139680);
    EnableEvent(D_80139684);
    EnableEvent(D_80139688);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001C854);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001C8AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001C8F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001CB24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001CC5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001CD70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001CDE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001CE84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001CEDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001CF74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001CFF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001D064);

void func_8001D104(void)
{
}

void PlayCapcomLogo(void)
{
    func_800182E8(); // nop out to skip capcom logo
    SetDispMask(0);
}

void func_8001D134(void)
{
    func_80023D30();
    func_80016F0C();
    func_80015930(0xFF, 0);
    func_8002A7D0();
    func_8002AB20();
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001D178);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001D1A4);

void func_8001D1F0(struct Unk* arg0)
{
    if (arg0->id == 0) {
        func_8001D230();
        return;
    }
    func_8001D284();
}

void func_8001D230(struct GameInfo* arg0)
{
    arg0->unkD = 1;
    D_80173C80 = 0x80178000;
    func_80018000(1); // nop out to skip opening cinematic
    arg0->mode++;
}

void func_8001D284(u8* arg0)
{
    arg0[0] = 1;
    arg0[1] = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001D294);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001D2D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001D364);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001D460);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001D514);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001D57C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001D5C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001D64C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001D698);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001D6DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001D77C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001D7D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001D8DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001D9D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001DA70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001DAA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001DAD0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001DAF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001DC30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001DC7C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001DCCC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001DDB0);

void func_8001DE20(struct Unk800F2294* arg0)
{
    arg0->unk4--;
    if (arg0->unk4 == 0) {
        arg0->unkA = 2;
        arg0->unk1++;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001DE54);

void func_8001DF48(struct Unk800F2294* arg0)
{
    if (D_80139690->unk1 == 0x13) {
        arg0->unk4 = 0x32;
        arg0->unk1 += 1;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001DF7C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001E000);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001E130);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001E3FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001E458);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001E4F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001E54C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001E638);

void func_8001E690(struct Unk800F2294* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->unk1++;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001E6BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001E708);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001E850);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001E954);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001E980);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001E9E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001EA90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001EBA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001EC34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001EC90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001ED44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001EE08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001EF48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001EFF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F0BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F118);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F150);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F198);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F2BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F398);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F3D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F488);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F5D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F634);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F6E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F798);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F850);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F8DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F8FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F93C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F968);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F9A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F9DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001FA24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001FAC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001FAFC);

void func_8001FB50(void)
{
    while (1) {
        D_800F23E8[D_801721C0.unk0](&D_801721C0);
        func_800127C8(1);
    }
}

void func_8001FBB8(struct EngineObj* arg0)
{
    arg0->unk44 = 2;
    arg0->unk46 = 0x20;
    arg0->unk0 = 1;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001FBD4);

void func_8001FBE0(struct EngineObj* arg0)
{
    func_80013014();
    arg0->unk1D = 0;
    arg0->unk1E = 0;
    D_80171EA8 = 0;
    arg0->unk0 = 5;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001FC20);

s32 func_8001FD7C(struct EngineObj* arg0)
{
    if (arg0->unkC != 0xC) {
        return 0;
    } else if (arg0->unkD != 0) {
        return 0;
    } else if (arg0->unk1D >= 2) {
        return arg0->unk1D < 0xA;
    }
    return 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001FDBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001FEC0);

void func_8001FF50(struct EngineObj* arg0)
{
    D_800F241C[arg0->unk1]();
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001FF8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020060);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800200D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020368);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020390);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002044C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020464);

void func_800204A4(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800204AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800204CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020580);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020638);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800206D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020808);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002088C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020984);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020A08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020AC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020B1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020B8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020C24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020CB8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020D3C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020D98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020DEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020ED4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020F24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800210B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80021104);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80021158);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80021234);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80021340);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002144C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80021558);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002166C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002174C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80021858);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002196C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80021A20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80021B34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80021C14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80021CC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80021D20);

void func_80021D84(void)
{
    func_800AE6B4(&D_8013E470);
    func_800AE6B4(&D_8013E470 + 0x50);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80021DBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80021E3C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80021E74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80021F34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80022074);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800220C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80022138);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002217C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80022730);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002328C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80023624);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80023684);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80023698);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800237E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80023870);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800238F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80023970);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800239E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80023A54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80023AA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80023B98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80023C0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80023CA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80023CE0);

void func_80023D30(void)
{
    D_80173C6C = 3;
    D_80173C6D = 4;
    D_80173C6E = 5;
    D_80173C6F = 6;
}

void func_80023D68(void)
{
    func_80026648();
    func_80023DB8();
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80023D90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80023DB8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800241E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80024260);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80024334);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80024920);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80024B9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80024E70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80024F5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002509C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80025188);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800253F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80025588);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800257BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002588C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80025CDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80025DA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80026118);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800261B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800262B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800264D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800265B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80026648);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80026720);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800267D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80026894);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80026AA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80026CEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800270F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002728C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027344);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800275DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002771C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027850);

void func_80027908(struct BackgroundObj* arg0)
{
    arg0->unk47 = 2;
    arg0->unk48 = 8;
    arg0->unk2C = 0x60;
    arg0->unk2E = 0xC0;
    arg0->unk30 = 0xA0;
    arg0->unk32 = 0xA0;
    arg0->unk14.val = arg0->unk8.val;
    arg0->unk18.val = arg0->unkC.val;
    arg0->unk24 = arg0->unk1C;
    arg0->unk26 = arg0->unk1E;
    arg0->unk28 = arg0->unk20;
    arg0->unk2A = arg0->unk22;
    arg0->unk4++;
}

void func_80027974(struct BackgroundObj* arg0)
{
    s32 temp_a1;
    arg0->unk14 = arg0->unk8.val;
    temp_a1 = arg0->unkC.val;
    arg0->unk18 = temp_a1;
    arg0->unk49 = -arg0->unk48;
    func_80027A5C(arg0, temp_a1);
    func_80027AAC(arg0);
    func_80027AFC(arg0);
    func_80027B70(arg0);
    func_80027BE4(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800279D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027A5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027AAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027AFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027B70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027BE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027D40);

void func_80027DC0(struct BackgroundObj* arg0)
{
    // overlap with D_800F32D5
    arg0->unk4 = D_800F32D4[D_801721CD << 1][D_801721CC << 2];
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027DF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027E28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027E48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027E68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027E90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027EBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027EE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027F08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027F28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027F50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027F7C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027FA8);

void func_80028070(struct BackgroundObj* arg0)
{
    arg0->unk8.i.hi = D_801419BA[0] + arg0->unk40;
    arg0->unkC.i.hi = D_801419BE[0] + arg0->unk42;
    func_80027FA8(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800280BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800280F4);

void func_80028138(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028140);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028178);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800281B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800281E8);

extern u8 D_800F32D5[1][1];
extern s8 D_801721CC;
extern s8 D_801721CD;

void func_80028268(struct BackgroundObj* arg0)
{
    arg0->unk4 = D_800F32D5[D_801721CD << 1][D_801721CC << 2];
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028298);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800282D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800282F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028310);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028338);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028364);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028390);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800283B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800283D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800283F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028424);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028450);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028518);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028564);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002859C);

void func_800285E0(struct BackgroundObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800285E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028620);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028658);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028690);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028A48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028AD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028B68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028BAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028BF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028DB4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028E24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028F58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028FEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800292D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002938C);

extern void (*g_MakeObjectFuncs[1])(s32 arg0);

void MakeObject(u8 arg0)
{
    g_MakeObjectFuncs[arg0](arg0 << 2);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80029420);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002951C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80029604);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800296A8);

void func_8002979C(struct EngineObj* arg0)
{
    D_800F4498[arg0->unk2]();
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800297D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800298B4);

void func_80029928(struct EngineObj* arg0)
{
    if (arg0->unk4 == 0) {
        arg0->unk1++;
        func_800129F0(8);
        return;
    }
    arg0->unk4--;
}

void func_80029978(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        func_8001D134();
        D_801419B3 = 0;
        D_80141A07 = 0;
        D_80141A5B = 0;
        func_8002A7D0();
        func_80012EB8();
        arg0->unk0 = 3;
        arg0->unk1 = 0;
        arg0->unkC = 0;
        arg0->unkD = 0;
    }
}

void func_800299EC(struct EngineObj* arg0)
{
    D_800F44A8[arg0->unk1]();
    func_8002B460();
    func_80021858();
    func_8002A484();
    func_80023D68();
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80029A48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80029BD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80029DBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80029E1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002A098);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002A394);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002A41C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002A484);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002A6FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002A728);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002A74C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002A7D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002AB20);

struct Unk* find_free_game_obj(void)
{
    struct Unk* var_v1;
    for (var_v1 = &game_objects[0]; var_v1 < &game_objects[0x30]; var_v1++) {
        if (!var_v1->active) {
            var_v1->unk50 = 0;
            var_v1->unk54 = 0;
            var_v1->unk68 = 0;
            var_v1->unk61 = 0;
            var_v1->unk64 = 0;
            var_v1->unk65 = 0;
            var_v1->unk66 = 0;
            var_v1->unk72 = 0;
            var_v1->unk73 = 0;
            var_v1->unk74 = 0;
            var_v1->unk76 = 0;
            var_v1->unk77 = 0;
            var_v1->unk78 = 0;
            var_v1->unk62 = 0;
            var_v1->unk63 = 0;
            var_v1->unk7A = 0;
            var_v1->unk5D = 0;
            var_v1->unk75 = 0;
            return var_v1;
        }
    }

    return NULL;
}

struct WeaponObj* func_8002AC0C()
{
    struct WeaponObj* current;
    for (current = &weapon_objects[0]; current < &weapon_objects[0x10]; current++) {
        if (!current->active) {
            current->unk50 = 0;
            current->unk54 = 0;
            current->unk68 = 0;
            current->unk98 = 0;
            current->unk61 = 0;
            current->unk64 = 0;
            current->unk65 = 0;
            current->unk66 = 0;
            current->unk72 = 0;
            current->unk73 = 0;
            current->unk74 = 0;
            current->unk76 = 0;
            current->unk77 = 0;
            current->unk78 = 0;
            current->unk62 = 0;
            current->unk63 = 0;
            current->unk7A = 0;
            current->unk75 = 0;
            return current;
        }
    }

    return NULL;
}

struct ShotObj* func_8002ACA4(void)
{
    struct ShotObj* current;
    for (current = &shot_objects[0]; current < &shot_objects[0x20]; current++) {
        if (!current->active) {
            current->unk50 = 0;
            current->unk54 = 0;
            current->unk68 = 0;
            current->unk98 = 0;
            current->unk61 = 0;
            current->unk64 = 0;
            current->unk65 = 0;
            current->unk66 = 0;
            current->unk72 = 0;
            current->unk73 = 0;
            current->unk74 = 0;
            current->unk76 = 0;
            current->unk77 = 0;
            current->unk78 = 0;
            current->unk62 = 0;
            current->unk63 = 0;
            current->unk7A = 0;
            current->unk75 = 0;
            return current;
        }
    }

    return NULL;
}

struct VisualObj* func_8002AD3C()
{
    struct VisualObj* current;
    for (current = &visual_objects[0]; current < &visual_objects[0x20]; current++) {
        if (current->active == NULL) {
            return current;
        }
    }

    return NULL;
}

struct EffectObj* find_free_effect_obj(void)
{
    struct EffectObj* var_v0;
    for (var_v0 = &effect_objects[0]; var_v0 < &effect_objects[0x20]; var_v0++) {
        if (!var_v0->active) {
            return var_v0;
        }
    }
    return NULL;
}

struct ItemObj* func_8002ADBC()
{
    struct ItemObj* current;
    for (current = &item_objects[0]; current < &item_objects[0x20]; current++) {
        if (!current->active) {
            current->unk50 = 0;
            current->unk54 = 0;
            current->unk68 = 0;
            current->unk61 = 0;
            current->unk64 = 0;
            current->unk65 = 0;
            current->unk66 = 0;
            current->unk72 = 0;
            current->unk73 = 0;
            current->unk74 = 0;
            current->unk76 = 0;
            current->unk77 = 0;
            current->unk78 = 0;
            current->unk62 = 0;
            current->unk63 = 0;
            current->unk7A = 0;
            current->unk75 = 0;
            return current;
        }
    }

    return NULL;
}

struct MiscObj* find_free_misc_obj(void)
{
    struct MiscObj* var_v0;
    for (var_v0 = &misc_objects[0]; var_v0 < &misc_objects[0x40]; var_v0++) {
        if (!var_v0->active) {
            return var_v0;
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002AE90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002AF4C);

struct QuadObj* find_free_quad_obj()
{
    struct QuadObj* current = g_QuadObjects;
    struct QuadObj* end = &g_QuadObjects[32];

    while (current < end) {
        if (current->first_byte == 0) {
            return current;
        }
        current++;
    }

    return NULL;
}

struct LayerObj* func_8002B048()
{
    struct LayerObj* current;
    for (current = &layer_objects[0]; current < &layer_objects[4]; current++) {
        if (!current->active) {
            return current;
        }
    }

    return NULL;
}

struct UnkObj* func_8002B088()
{
    struct UnkObj* current;

    for (current = &unk_objects[0]; current < &unk_objects[20]; current++) {
        if (!current->active) {
            return current;
        }
    }

    return NULL;
}

void func_8002B0C8(struct Unk18* arg0)
{

    if (arg0->unk10 != NULL) {
        *arg0->unk10 &= 0x70;
    }
    ZeroObjectState(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002B108);

void ZeroObjectState(struct Unk18* arg0)
{
    arg0->unk0 = 0;
    arg0->unk1 = 0;
    arg0->unk2 = 0;
    arg0->unk3 = 0;
    arg0->unk4 = 0;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002B160);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002B1E8);

void func_8002B288(struct Unk* arg0)
{
    s32 temp_v0;
    s16 var_v0;
    s16 var_a0;

    arg0->unk3 = 0;
    if (arg0->unk14 < 0) {
        var_v0 = arg0->x_pos.i.hi;
        var_a0 = arg0->y_pos.i.hi;
    } else {
        temp_v0 = arg0->unk14 * 42;
        var_v0 = arg0->x_pos.i.hi - D_801419BA[temp_v0];
        var_a0 = arg0->y_pos.i.hi - D_801419BE[temp_v0];
    }
    if (var_v0 >= -0x20 && var_v0 < 0x160 && var_a0 >= -0x20 && var_a0 < 0x110) {
        arg0->unk3 = 1;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002B318);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002B3C0);

void func_8002B450(void)
{
}

void func_8002B458(void)
{
}

void func_8002B460(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002B468);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002B560);

void func_8002B694(struct Unk* arg0)
{
    arg0->x_pos.val += arg0->unk20;
    arg0->y_pos.val -= arg0->unk24;

    if (arg0->unk15) {
        arg0->unk20 += arg0->unk28;
    } else {
        arg0->unk20 -= arg0->unk28;
    }

    arg0->unk24 -= arg0->unk2C;
    if (arg0->unk24 < FIXED(-6.5)) {
        arg0->unk24 = FIXED(-6.5);
    }
}

void func_8002B718(struct Unk19* arg0)
{
    arg0->unk8 += arg0->unk20;
    arg0->unkC -= arg0->unk24;
}

u8 func_8002B73C()
{
    u16 temp = D_8013E2E8 * 3;
    u32 temp_v1;
    u8 pad[2];

    temp_v1 = temp >> 8;
    D_8013E2E8 += temp_v1;
    D_8013E2E8 &= 0xFF;
    D_8013E2E8 |= temp_v1 << 8;

    return D_8013E2E8;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002B780);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002B7B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002B7DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002B810);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002B93C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002B9F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002BAA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002BAD0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002BB80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002BD58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002C160);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002C26C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002C2EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002C36C);

// megaman falls through floor in intro stage if nopped out
// asm(".rept 81 ; nop ; .endr");
void CollisionRelated(struct PlayerObj* arg0) // was func_8002C614
{
    s32 temp_v1;

    arg0->unk70 = 0;
    arg0->unk79 = 0;

    if (arg0->unk68 != NULL) {
        func_8002C760(arg0);
        temp_v1 = arg0->x_pos.val - arg0->unk18;
        D_8013B7D8 = 0;
        D_8013B7DC = 0;

        if (temp_v1 != 0) {
            if (temp_v1 > 0) {
                func_8002CB58(arg0);
            } else {
                func_8002CA18(arg0);
            }
        }

        if (arg0->y_pos.val - arg0->unk1C >= 0) {
            func_8002CDD4(arg0);
            if (D_8013B7D8 != 0) {
                return;
            }
        } else {
            func_8002CC98(arg0);
        }

        if (D_8013B7DC & 0xC) {
            if ((D_8013B7DC & 3) != 0) {
                if ((D_8013B7DC & 4) || (D_8013B804 >= -8)) {
                    func_8002C954(arg0);
                } else {
                    func_8002C99C(arg0);
                }
            } else {
                func_8002D25C(arg0);
            }
        } else if ((D_8013B7DC & 3) != 0) {
            func_8002D490(arg0);
        }

        func_8002C808(arg0);
    }
}

void func_8002C760(struct PlayerObj* arg0)
{
    struct Unk_unk68* temp_v1 = arg0->unk68;
    u16 temp_a1 = arg0->x_pos.i.hi;
    u16 temp_v0 = temp_v1->unk0;

    D_8013B7E8 = temp_v1->unk0;
    D_8013B7EC = temp_v1->unk1;
    D_8013B7E0 = temp_v1->unk2;
    D_8013B7E4 = temp_v1->unk3;

    D_8013B7F0 = temp_a1;
    D_8013B7F4 = arg0->y_pos.i.hi;

    if (arg0->unk15 == 0) {
        D_8013B7F8 = temp_a1 + temp_v0;
    } else {
        D_8013B7F8 = temp_a1 - temp_v0;
    }
    D_8013B7FC = D_8013B7F4 + D_8013B7EC;
}

void func_8002C808(struct PlayerObj* arg0)
{
    arg0->unk70 = 0;
    arg0->unk79 = 0;
    if (arg0->unk68 != NULL) {
        func_8002C760(arg0);
        if (func_8002D5E4(arg0, D_8013B7F8 - D_8013B7E0 - 1)) {
            arg0->unk70 |= 2;
        }
        if (func_8002D5E4(arg0, D_8013B7F8 + D_8013B7E0)) {
            arg0->unk70 |= 1;
        }
        if (func_8002D32C(arg0, D_8013B7F4 + D_8013B7EC + D_8013B7E4, 1)) {
            arg0->unk70 |= 8;
        }
        if (func_8002D32C(arg0, D_8013B7F4 + D_8013B7EC - D_8013B7E4 - 1, 0)) {
            arg0->unk70 |= 4;
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002C954);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002C99C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002C9E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002CA18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002CAF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002CB58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002CC34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002CC98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002CD70);

void func_8002CDD4(struct PlayerObj* arg0)
{
    u8 temp_s3;
    u8 temp_s4;
    u8 temp_s5;
    u8 temp_v0_4;
    s32 var_s0;
    s16 temp_v0 = D_8013B7FC + D_8013B7E4;

    temp_s3 = func_8002D7E4(arg0, D_8013B7F8 - D_8013B7E0, temp_v0);
    temp_s4 = func_8002D7E4(arg0, D_8013B7F8 + D_8013B7E0 - 1, temp_v0);
    temp_s5 = func_8002D7E4(arg0, D_8013B7F8, temp_v0);

    if (func_8002CF98(arg0, temp_s5, D_8013B7F8, temp_v0) == 0) {
        if (arg0->unk67 == 0) {
            var_s0 = 0;
            if (temp_s3 > 0 && temp_s3 < 0x20) {
                var_s0 = 1;
            }
            if (temp_s4 > 0 && temp_s4 < 0x20) {
                var_s0 = 1;
            }

            temp_v0_4 = func_8002D7E4(arg0, D_8013B7F8, (temp_v0 + 0x10));
            if (temp_v0_4 > 0 && temp_v0_4 < 0x20) {
                var_s0 = 1;
            }

            if (var_s0) {
                arg0->y_pos.i.hi += 0x10;
                if (func_8002CF98(arg0, temp_v0_4, D_8013B7F8, temp_v0 + 0x10)) {
                    return;
                }
            }
        }

        if (func_8002D1F8(arg0, temp_s3, temp_v0) == 0) {
            func_8002D1F8(arg0, temp_s4, temp_v0);
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002CF98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002D180);

s32 func_8002D1F8(struct PlayerObj* arg0, u8 arg1, s32 arg2)
{
    switch (arg1) {
    case 0x21:
    case 0x22:
    case 0x38:
    case 0x39:
    case 0x3A:
    case 0x3C:
    case 0x3E:
    case 0x3F:
        D_8013B7DC |= 8;
        D_8013B804 = -arg0->unk6E;
        return -1;
    default:
        return 0;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002D25C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002D32C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002D41C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002D490);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002D5E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002D6BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002D724);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002D7E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002D8B8);

u8 func_8002D900(struct PlayerObj* arg0)
{
    s16 x = arg0->x_pos.i.hi;
    s16 y = arg0->y_pos.i.hi + arg0->unk68->unk1 + arg0->unk68->unk3 - 1;

    return func_8002D724(arg0, x, y);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002D94C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002D994);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002D9BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002DD04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002DE30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002DF7C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002E184);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002E294);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002E380);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002E420);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002E5E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002E698);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002E7BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002E8D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002E994);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002ED80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002ED98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002EDD4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002EF14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002F048);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002F1B4);

void func_8002F264(struct EngineObj* arg0)
{
    if (D_8013BC34 != 0x80) {
        arg0->unk2++;
        func_8002F048();
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002F2A0);

void func_8002F47C(struct EngineObj* arg0)
{
    if ((D_8013BC34 == 1) || (D_8013BC34 == 0x80)) {
        arg0->unk2--;
        func_8002F048();
    }
}

void func_8002F4C4(struct EngineObj* arg0)
{
    arg0->unk40 = 0;
    D_800F485C[arg0->unk2]();
    func_80022730(&D_8013BC28);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002F510);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002F524);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002F584);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002F5E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002F698);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002F6E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002F7A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002F828);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002F87C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002F8F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002F92C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002F9EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002FAB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002FAE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002FB54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002FBDC);

void func_8002FC38(struct EngineObj* arg0)
{
    func_8002B460();
    D_800F48A4[arg0->unk1](arg0);
    func_8002166C();
    func_80021858();
    func_80021A20();
    func_8002A484();
    func_80023D68();
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002FCAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002FCEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002FD28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002FD70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800300AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80030128);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800301BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800304E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80030728);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80030A2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80030C54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80030DF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80030EC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80030F9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80030FD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80031014);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80031064);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80031130);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800311EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800312B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80031410);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80031540);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800315E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80031688);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80031764);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80031820);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800318D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80031A24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80031AE0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80031B90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80031CAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80031CEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80031DD4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80031EDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80031F1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003200C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800320E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80032140);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80032224);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80032300);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80032468);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003253C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800325EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003267C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80032740);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003277C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800327CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80032840);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800328CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80032910);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80032950);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80032A28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80032B04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80032B50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80032BF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80032D28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80032DE0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80032E94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80032F64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80032FA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80033054);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800330B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80033108);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800331A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80033210);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800332C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80033368);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80033414);

s32 func_80033494(struct PlayerObj* arg0)
{
    if (func_80033694() != 0) {
        func_80034754(arg0);
        return 1;
    }
    if (arg0->unk80 & 0x80) {
        func_80034538(arg0);
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800334F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003356C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800335E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80033694);

void func_80033750(struct PlayerObj* arg0)
{
    s8 temp_v1;

    arg0->unk87 = 0;
    if ((arg0->unkC3 == 0) && (temp_v1 = arg0->unk5, (temp_v1 != 0)) && (temp_v1 != 1)) {
        if (arg0->unk88 == 0) {
            arg0->unk82 = arg0->unk80 & 3;
            if (arg0->unk82 != 0) {
                arg0->unk88 = 0xC;
            }
        } else {
            arg0->unk88--;
            if (arg0->unk80 & arg0->unk82) {
                arg0->unk87 = 1;
                arg0->unk88 = 0;
            }
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800337DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800338CC);

void func_80033974(struct PlayerObj* arg0)
{
    if (arg0->unkC5 > 0) {
        func_80036088();
        func_80038490(arg0);
        func_80036E98(arg0);
        arg0->unk68 = 0;
        arg0->unk67 = 1;
        arg0->unkC5 = -1;
        arg0->unk5 = 0x12;
        arg0->unk6 = 1;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800339E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80033AC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80033B34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80033B8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80033BC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80033D10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80033D54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80033EA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80033F5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80033FF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800340BC);

s32 func_80034100(struct PlayerObj* arg0)
{
    if (D_801721CF != 0) {
        func_80034F7C();
        return 1;
    }

    if (arg0->unkC0 > 0) {
        func_80034E2C();
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80034150);

s32 func_80034238(struct Unk11* arg0)
{
    s32 result = 0;

    if (arg0->unk89 & 0x4) {
        result = 1;
        arg0->unk24 = 0;
    }

    if (arg0->unk24 <= 0) {
        result = 1;
    }

    if (result != 0) {
        s8 index = arg0->unk02;
        func_800350A4(arg0, D_800F8B30[index]);

        if (arg0->unk02 != 0) {
            struct Unk11* new_obj = func_8002AD3C();
            if (new_obj != NULL) {
                new_obj->unk00 = 1;
                new_obj->unk01 = 0x27;
                new_obj->unk02 = 0;
                new_obj->unk14 = arg0->unk14;
            }
        }

        arg0->unk67 = -1;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk06 = 3;
        return 1;
    } else {
        func_8002B694(arg0);
        func_80036B88(arg0);
        return 0;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80034320);

void func_8003439C(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800343A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003443C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800344A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800344EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80034538);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80034604);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80034668);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003470C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80034754);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800347D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003484C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800348B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003490C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80034968);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800349F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80034AFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80034B64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80034BDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80034C58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80034CB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80034D20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80034D64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80034DC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80034E2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80034F7C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80035048);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800350A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003516C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80035240);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800355C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80035694);

void func_80035848(struct PlayerObj* arg0)
{
    func_800350A4(arg0, 1);
    func_8001540C(1, 0xD, arg0);
    arg0->unk24 = 0xFFF80000;
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = -1;
    arg0->unk5 = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800358A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80035A24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80035A6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80035AA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80035B6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80035C20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80035D00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80035D34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80035D84);

void func_80035DDC(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80035DE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80035EA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80035EF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80035FC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80036034);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80036054);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80036088);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800360B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800360B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800361B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800361F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800362F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800363B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800363EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80036470);

void func_80036534(struct PlayerObj* arg0)
{
    if (arg0->unk5C >= (D_80172206 / 3)) {
        func_800350A4(arg0, 5);
    } else {
        func_800350A4(arg0, 6);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800365A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003666C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800366C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800367F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003698C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80036A94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80036AE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80036B18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80036B38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80036B88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80036BF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80036DA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80036E1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80036E98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80036EE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80036F50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80037104);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003718C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800371E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80037290);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80037338);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800373DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80037484);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003751C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800375B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80037708);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003795C);

void func_80037A24(struct PlayerObj* arg0)
{
    if (arg0->unk96 == -1) {
        if (arg0->unk80 & 0x20) {
            arg0->unk96 = arg0->unk95;
            return;
        }
        if ((arg0->unk7C & 0x200020) == 0x200000) {
            if ((arg0->unk95 != 0) && (arg0->unk95 != 0x13)) {
                arg0->unk96 = arg0->unk95;
            }
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80037A98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80037B1C);

void func_80037B90(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80037B98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80037BC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80037C28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80037D08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80037DB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80037DFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80037E4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80037EAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80037F78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80037FF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800380F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80038158);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800381FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80038378);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80038490);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800384DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80038524);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80038568);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800385EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80038678);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80038748);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800387A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800387F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80038854);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800388F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80038970);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800389DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80038A80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80038AE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80038B80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80038C10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80038CA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80038D38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80038D88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80038E44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80038E90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80038F0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80038F64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003904C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800390C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80039120);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80039160);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80039230);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80039270);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80039328);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80039378);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80039570);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80039700);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003974C);

void func_800397B0(struct Unk11* arg0)
{
    if (func_80034238(arg0) == 0) {
        func_80034320(arg0);
    }
}

void func_800397E8(struct Unk11* arg0)
{
    func_80034238(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80039808);

s32 func_80039880(struct PlayerObj* arg0)
{
    if (arg0->unk2 == 0) {
        return 0;
    } else if (arg0->unkC3 != 0) {
        return 0;
    } else if (func_80039F28(arg0) != 0) {
        return 1;
    } else if (func_80039E5C(arg0) == 0) {
        return func_80039C34(arg0) != 0;
    }
    return 1;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800398F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003996C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80039A00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80039AC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80039B44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80039BB8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80039C20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80039C34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80039CC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80039D9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80039E5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80039F28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003A000);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003A104);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003A1DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003A328);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003A374);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003A3EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003A5E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003A7B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003A8A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003A9F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003AAE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003AB34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003ABE0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003AD74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003AE08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003AE54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003AEE0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003AF20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003AF58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003AFD4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003B044);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003B1A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003B1E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003B24C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003B340);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003B3DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003B458);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003B470);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003B694);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003B7B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003B98C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003BA24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003BAE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003BB20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003BDA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003BE28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003BF1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003C08C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003C584);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003C624);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003C6EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003C8F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003C9A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003CA44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003CB08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003CBCC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003CCBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003CD38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003CF24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003CF6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003D01C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003D164);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003D254);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003D338);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003D35C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003D39C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003D3B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003D3F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003D4C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003D638);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003D6EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003D7A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003D7E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003D8A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003D9E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003DC1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003DC44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003DC50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003DC8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003DCD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003DD14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003DD2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003DD54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003DDA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003DDDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003DE08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003DE84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003DF9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003E048);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003E0B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003E0D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003E274);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003E368);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003E488);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003E5F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003E750);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003E8A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003EA08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003EB4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003ED00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003EDF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003EEF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003F068);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003F204);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003F244);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003F31C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003F44C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003F570);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003F618);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003F648);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003F698);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003F76C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003F908);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003FA58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003FBD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003FD08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003FF14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003FF58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8003FF9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800400C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800401F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80040248);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800402C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800403DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800405D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80040608);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80040644);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80040760);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80040810);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80040838);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80040ABC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80040CCC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80040DF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80040E44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80040EFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80041020);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80041060);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800411D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80041384);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800413C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004140C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80041524);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80041564);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800415B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80041854);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80041958);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800419B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80041C94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80041DF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80041F88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004205C);

void func_800420E8(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800420F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042120);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042170);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042248);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004234C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042384);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800423A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042414);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800424CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004258C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800425C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042648);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800426BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004272C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800427C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042824);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042884);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042914);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042950);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042A48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042AFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042CB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042CC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042CE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042D20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042D60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042DD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042E18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042E70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042EB8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042F18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042F80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80042FBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043064);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800430C0);

void func_80043128(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043130);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004316C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043198);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043214);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043250);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043280);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800432F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043340);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043390);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800435C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800436D0);

void func_80043720(struct Unk* arg0)
{
    arg0->unk5 = arg0->unk90;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004372C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043768);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800437A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004381C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043858);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043898);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043900);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004393C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043978);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043A48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043A84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043B0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043C0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043CB8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043D54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043D90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043DE0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043E90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043ECC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043F04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80043F78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004415C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800441E4);

void func_80044314(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004431C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004441C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80044458);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80044508);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80044630);

void func_80044694(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004469C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800446D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80044738);

void func_800447A4(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800447AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800447E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80044814);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800448C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800448E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80044920);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80044978);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800449D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80044A4C);

void func_80044AA0(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80044AA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80044AE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80044B18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80044B78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80044BA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80044BE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80044BFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80044C58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80044D8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80044DE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80044F4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80044F88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800450A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80045198);

void func_80045240(struct Unk* arg0)
{
    arg0->unk5 = arg0->unk8C;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004524C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800452B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800452FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004539C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80045404);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80045464);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800454A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004550C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80045560);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800455BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80045648);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80045694);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80045728);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800457A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004583C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800458B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80045940);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80045D80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80045DD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80046104);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80046134);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004619C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80046220);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004636C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80046400);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80046610);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80046640);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800466A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004677C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80046818);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80046864);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800468CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800469A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80046A4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80046AA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80046B30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80046B80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80046C8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80047038);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80047078);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80047084);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800470C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80047140);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80047188);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800471C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80047244);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80047314);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80047378);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800473C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80047404);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80047660);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80047794);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800477D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800477DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80047818);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80047900);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80047974);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800479E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80047A20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80047A34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80047B04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80047C88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80047D04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80047E58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004808C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800480D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004831C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80048348);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800483AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800483E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80048434);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800484C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004852C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80048584);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80048610);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80048770);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800487AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800487F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80048864);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800488F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80048970);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80048A1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80048A58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80048B04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80048B98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80048BD4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80048C20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80048CF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80048DD0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80048E0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80048E70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80048EF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80048F34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80048F98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80049028);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80049064);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800490D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800491BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80049288);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800492C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004932C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800493F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800494E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004955C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80049654);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004970C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800497FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80049884);

void func_800498C0(struct MainObj* arg0)
{
}

// didn't notice any differences when nopped out
void func_800498C8(struct MainObj* arg0)
{
    D_800FB0F4[arg0->unk4]();
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80049904);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80049AA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80049C0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80049C78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80049CBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80049CC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80049DE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80049E24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80049E68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80049F20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80049FE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004A0AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004A0FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004A178);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004A31C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004A378);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004A468);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004A5B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004A5E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004A644);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004A690);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004A6E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004A718);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004A78C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004A9F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004AB6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004ACDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004ACF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004AD18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004ADE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004AE00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004AE20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004B040);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004B0A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004B280);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004B2BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004B418);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004B514);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004B668);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004B748);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004B808);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004B8C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004B8FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004BAF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004BC14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004BC2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004BCC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004BCFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004BF5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004C210);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004C394);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004C56C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004C654);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004C694);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004C6C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004C734);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004C784);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004C860);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004C97C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004C9E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004CA14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004CA20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004CA5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004CA94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004CBD4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004CC64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004CCA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004CDC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004CE48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004CE94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004CEF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004CF24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004CF60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D044);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D160);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D1C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D1D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D210);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D290);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D2E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D31C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D370);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D3C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D408);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D444);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D480);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D4D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D580);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D5E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D61C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D69C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D6CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D6FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D784);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D84C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D930);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004D9CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004DB10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004DCB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004DEA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004DF40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004DFEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004E128);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004E218);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004E300);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004E490);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004E55C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004E6A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004E810);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004E830);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004E890);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004E8E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004EA88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004EC44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004ECB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004ECE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004ED20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004ED60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004EF14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004EFA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004EFE0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004F0C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004F118);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004F1A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004F228);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004F264);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004F2A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004F34C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004F424);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004F460);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004F4D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004F62C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004F67C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004F6B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004F7D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004F910);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004F9B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004FAAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004FAE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004FBF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004FC50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004FC80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004FD38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004FF90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8004FFE0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800500D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80050238);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005026C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80050278);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80050418);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80050480);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80050540);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80050644);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80050690);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800506D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80050708);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005077C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80050874);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80050A9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80050BC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80050BFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80050C64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80050C70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80050CAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80050D14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80050E08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80050E44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80050EB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80050F60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80050FE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80051020);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80051060);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800510D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005115C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800511E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800512BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80051338);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80051374);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800513DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800514A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80051564);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80051630);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80051678);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005172C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80051768);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800517D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80051A4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80051B74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80051C94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80051CD0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80051D60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80051F68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80051F94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80052008);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80052044);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005216C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800521B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800521DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80052218);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800522A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800522C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80052324);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80052374);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800523EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80052444);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80052524);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80052614);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800526AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800527C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800527F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005284C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800528BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80052A68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80052B94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80052C2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80052C70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80052CB8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80052E94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800531B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80053224);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80053274);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80053338);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800535CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80053604);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80053640);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005368C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800537E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005398C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80053A88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80053B18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80053B54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80053D04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80053D24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80053EB8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005402C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005440C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80054518);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005458C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800545EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80054710);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80054738);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80054758);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800548B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80054B38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80054B98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80054BBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80054C50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80054CA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80054D8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80054EF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80054F14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80054F34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80054F98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80054FBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80054FDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80054FE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80055024);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80055164);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005529C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800552C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800552D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005530C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80055358);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800555B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80055604);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80055640);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005567C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800556D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80055710);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80055758);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800557B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800557FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80055838);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80055880);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800558D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80055910);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005594C);

void func_800559B4(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800559BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80055C54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80055E04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80055E9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80055F1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80055FD0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80056018);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80056054);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80056230);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800562AC);

void func_80056470(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80056478);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800564B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800565EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80056618);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80056718);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80056738);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80056788);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800567C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80056AC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80056BA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80056BD0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80056BDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80056C18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80056D20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80056DB4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80056EF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800570A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80057100);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80057160);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80057308);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80057488);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800574B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800574C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800574FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005754C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800576F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800577E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80057824);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80057874);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80057978);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80057A44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80057A80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80057AE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80057C00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80057D58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80057D94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80057DDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80057E34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80057F34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80058044);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005807C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800580AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80058158);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80058194);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80058240);

void func_8005824C(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80058254);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800583B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800585F4);

void func_80058658(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80058660);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80058680);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800586F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80058740);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80058AC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80058D50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80058DBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80058DF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80058DFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80058E38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80058F94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80059010);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005904C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800590BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80059154);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800591F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005922C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80059290);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80059344);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800594D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005952C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80059590);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80059640);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80059978);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800599B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80059A94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80059B0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80059B7C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80059C48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80059C84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80059D6C);

void func_80059E38(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80059E40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80059F60);

void func_8005A3DC(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005A3E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005A460);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005A4AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005A4CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005A538);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005A6C0);

void func_8005A750(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005A758);

void func_8005AA0C(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005AA14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005AB34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005ABC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005ACA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005AD00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005AEB4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005AF5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005B24C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005B2C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005B3FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005B438);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005B504);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005B52C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005B578);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005B64C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005B708);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005B760);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005B7AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005B818);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005B894);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005B8D0);

void func_8005BA24(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005BA2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005BB70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005BC50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005BCA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005BD6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005BDE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005BF48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005BFC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005C0E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005C474);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005C804);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005C824);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005C860);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005C960);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005CADC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005CAFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005CB08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005CB54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005CB90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005CC6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005CCA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005CCFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005CD5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005CDB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005CDEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005CE50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005CE80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005CEBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005CF30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005CF60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005CF9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005D0A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005D0D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005D118);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005D148);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005D1F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005D230);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005D348);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005D4E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005D7E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005D844);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005D850);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005D88C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005D8B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005D9C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005DAB8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005DB84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005DBC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005DC58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005DED4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005DF84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005E044);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005E0CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005E108);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005E1BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005E298);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005E3E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005E424);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005E47C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005E500);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005E570);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005E5C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005E754);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005E7CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005E7EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005E860);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005E8B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005E8F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005E9C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005EA18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005EA78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005EAF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005EB40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005EBF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005EC38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005EC58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005ECA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005EE2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005EF40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005EF6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005EF78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005EFB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005F0F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005F124);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005F160);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005F1A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005F230);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005F2F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005F3D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005F47C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005F4E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005F510);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005F558);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005F758);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005F844);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005F864);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005F87C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005F9A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005F9F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005FB38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005FBBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005FCAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005FCD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005FDBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8005FE1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80060144);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80060228);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006025C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80060268);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800602A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80060354);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800603A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800603DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800604A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800604EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80060538);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80060574);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800606D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80060870);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800608CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006097C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800609C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80060A10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80060A58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80060A88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80060AC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80060BC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80060D3C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80060DC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80060E08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80060E14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80060E50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80060E94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80060F5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80060F98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80060FF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006104C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80061088);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800610F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006114C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80061188);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800611E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80061240);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006128C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800612C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80061310);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006135C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80061424);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800614E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80061590);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800615CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006185C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800618F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80061918);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80061AA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80061AE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80061B58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80061D18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80061D90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80061DC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80061DFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80061F2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800620C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800621C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80062240);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80062338);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800623C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80062400);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800624B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80062550);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800625C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80062650);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800626F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80062778);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80062910);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80062A0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80062AEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80062BBC);

void func_80062D18(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80062D20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80062D60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80062D9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80062E70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80062E90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80062F60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800630AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800630DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800631A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800631C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80063234);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800632A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80063334);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006346C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80063600);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006364C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800636A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800637A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80063814);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80063854);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80063914);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006398C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80063AE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80063B20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80063DD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80063F80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80063FBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80063FE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800640B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800640F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80064154);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80064338);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80064360);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800643B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006458C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800646B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800646EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800648D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800649C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80064AE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80064B38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80064BA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80064C0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80064C84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80064CF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80064DC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80064E58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80064F24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80064FD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80065088);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80065168);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80065268);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006528C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800652C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006530C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006537C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80065458);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80065538);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80065574);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006565C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80065704);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80065794);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80065898);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80065910);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80065930);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006596C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80065A54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80065B04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80065B24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80065B30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80065B6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80065B8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80065BC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80065CD4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80065DCC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80065EA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800661AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006630C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80066478);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80066580);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800665BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80066804);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80066858);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006689C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006692C);

void func_80066968(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80066970);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80066A48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80066A84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80066B00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80066C40);

void func_80066C64(struct Unk* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80066C74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80066CCC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80066DAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80066DE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80066F1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800671D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800672BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800672D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800672EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80067350);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006738C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80067550);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80067628);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80067640);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006767C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800676E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80067740);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006777C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800677F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80067860);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800678B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800678F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80067A80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80067AA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80067BB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80067C34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80067CB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80067D00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80067DAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80067EE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80068000);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80068060);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80068074);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006808C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800680C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80068108);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80068138);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800681C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80068340);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80068404);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800684BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800684F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80068548);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800688B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80068A10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80068A68);

void func_80068B3C(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80068B44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80068B80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80068C2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80068CB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80068CEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80068D4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80068D6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80068F88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069000);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006917C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800691B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069248);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800692AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800692E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069330);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800693AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069414);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069450);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006951C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069610);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069660);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006970C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069748);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800698D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069A08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069A6C);

void func_80069A8C(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069A94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069AD0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069BE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069CE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069D74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069D94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069DA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069DDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069E28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069E64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069F28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80069FDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006A018);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006A078);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006A0E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006A130);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006A16C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006A1B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006A208);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006A26C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006A2BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006A388);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006A450);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006A50C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006A55C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006A638);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006A70C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006A740);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006A74C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006A788);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006A7F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006A83C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006A998);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006AA18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006AA54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006AAB4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006AC8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006ACC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006AD84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006AE0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006AE50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006AE80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006AF70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006B114);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006B180);

void func_8006B1BC(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006B1C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006B2A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006B398);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006B514);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006B568);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006B5F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006B6B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006B79C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006B848);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006B8BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006B8F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006BAA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006BAC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006BB00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006BB70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006BD1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006BFBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006BFF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006C07C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006C170);

void func_8006C278(struct Unk* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006C288);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006C2C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006C378);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006C598);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006C61C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006C670);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006C6AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006CA80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006CB14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006CB50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006CC3C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006CD80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006CDD4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006CE9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006CED8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006CF2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006CFB8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006D280);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006D368);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006D3DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006D69C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006D6D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006D830);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006D888);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006DB04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006DBE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006DC24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006DCF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006DD44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006DF68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006E034);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006E260);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006E2E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006E334);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006E414);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006E450);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006E594);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006E604);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006E674);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006E6B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006E750);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006E7CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006E88C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006E920);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006EA78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006EAA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006EB40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006ECC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006ED44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006EF28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006F0A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006F0DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006F244);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006F304);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006F41C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006F494);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006F504);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006F584);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006F5F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006F7B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006F83C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006F86C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006FA24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006FABC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006FAE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006FB20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006FBFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006FCB8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006FD50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006FEC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8006FFC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800700AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80070118);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800701DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80070294);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800702E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80070348);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800703E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800704AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80070514);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80070648);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800706D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80070778);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800708DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80070948);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80070A38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80070C88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80070CB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80070CDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80070D2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80070DDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80070EE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007100C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800710D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80071228);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800712A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800713A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80071468);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800714C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800714F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80071598);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800715D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007168C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80071740);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800718F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007196C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800719FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80071A38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80071A74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80071AD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80071B60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80071C00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80071C60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80071CB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80071D1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80071D30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80071EEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80071F5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007203C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007211C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80072158);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80072194);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80072204);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80072240);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800722A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80072418);

void func_800725DC(struct Unk* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800725EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80072628);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800726CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800727C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800728C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80072904);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80072960);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80072A14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80072A84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80072BCC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80072C20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80072CC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80072D14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80072DB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80072DF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80072E34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80072EF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80072F68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80072FF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073084);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073100);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073164);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800731A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073228);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073294);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007330C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007342C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800734A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073500);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007353C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800735BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073650);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007368C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800736DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073748);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800737FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073878);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800738EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073938);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073974);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800739D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073B00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073B58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073BDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073C08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073C44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073CA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073DDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073E10);

void func_80073E3C(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073E44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073E80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80073F90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074068);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800740CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074158);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074194);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074220);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007427C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800742AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074368);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800743FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074438);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800745E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800747EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007482C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074838);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074874);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800748B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007491C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074958);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800749B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074A0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074A48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074AA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074B10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074B68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074BD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074C14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074CB8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074D10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074DDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074E84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074F4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074FC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80074FE0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007501C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80075064);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800750A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80075128);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007517C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800751AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80075320);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80075630);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007566C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80075700);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800757F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800758FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80075908);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80075944);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800759EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80075A54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80075AD0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80075B54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80075BC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80075C6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80075D38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80075DDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80075E18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80075E78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007601C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800760C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800761A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007624C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80076288);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80076364);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007651C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007662C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800766FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007681C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800768CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80076908);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800769FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80076A74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80076AB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80076B14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80076B84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80076C1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80076C70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80076CAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80076D14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80076DB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80076E1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80076E88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80076F14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80076F74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80076FB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077028);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800770F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800771AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007720C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077258);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077318);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077444);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077490);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077504);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077580);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077614);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077694);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077738);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077798);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800777D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007781C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077868);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800778A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077954);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800779D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077A44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077A80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077B0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077B74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077BD0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077C40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077C74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077CE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077D48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077DF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077ED0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077F60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80077FFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800780D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80078180);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007826C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80078314);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007856C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800785E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800786AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007872C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007877C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800788E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80078DF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80078E2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80078EB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80078FA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800790AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800790E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800791D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007927C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80079364);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800793AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80079518);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80079568);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80079608);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80079644);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800796DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80079794);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800797E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80079824);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80079914);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007996C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80079A50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80079A8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80079B50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80079DD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80079FE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007A048);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007A09C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007A12C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007A168);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007A1EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007A2B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007A3B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007A444);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007A4B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007A4EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007A63C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007A7F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007A854);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007A8AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007A930);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007A96C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007AB1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007ADB4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007AE2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007AFB4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007B054);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007B0F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007B140);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007B180);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007B1BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007B2FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007B3A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007B418);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007B588);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007B5F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007B640);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007B68C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007B6BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007B7B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007B834);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007B90C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007BABC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007BB90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007BC0C);

void func_8007BC48(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007BC50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007BCC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007BD4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007BE40);

void func_8007BF74(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007BF7C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007BFB8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007BFF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007C090);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007C144);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007C2B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007C2D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007C30C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007C3FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007C5C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007C5F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007C69C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007C6E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007C7D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007C824);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007C860);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007C890);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007C914);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007C968);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007C9B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007CA68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007CC8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007CD54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007CDA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007CDE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007CE3C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007CE98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007CEF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007CF68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007CFA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007D010);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007D0CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007D138);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007D174);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007D234);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007D2F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007D324);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007D374);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007D3DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007D424);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007D470);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007D4E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007D558);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007D594);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007D5D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007D710);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007D838);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007D9AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007DA20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007DAFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007DBDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007DC18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007DC54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007DD0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007DD98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007DF50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007E01C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007E098);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007E128);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007E1C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007E25C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007E2B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007E350);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007E45C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007E498);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007E4C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007E5D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007E66C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007E6F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007E848);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007E8C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007E918);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007E95C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007EA3C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007EA94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007EAE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007EBD0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007EC1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007EC74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007ECEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007EDC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007EE18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007EED8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007EF94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007F00C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007F05C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007F0B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007F174);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007F2F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007F360);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007F3B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007F404);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007F50C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007F564);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007F5B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007F690);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007F71C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007F780);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007F878);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007F93C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007F9C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007FA4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007FAA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007FB48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007FB98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007FBFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007FC78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007FCC4);

void func_8007FD1C(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007FD24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007FE84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007FF00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8007FFFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800802A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008030C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80080370);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800804A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800805D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80080604);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80080640);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800806A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80080700);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80080834);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80080D20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80080D5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80080DF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80080F04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008107C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800810C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80081104);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80081198);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800811D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80081230);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008127C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800812E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008134C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800813BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80081404);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800814E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80081508);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80081564);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800815B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80081624);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800816DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80081718);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80081830);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008186C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800818C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80081954);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800819C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80081AD0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80081B64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80081BA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80081CF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80081D30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80081E44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082014);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082050);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800820A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082170);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008225C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082354);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082404);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082434);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082470);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082574);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800826C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082710);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082784);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008284C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008286C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082878);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800828B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800829EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082A28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082AA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082B2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082B68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082BA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082C04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082C70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082CC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082D00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082D48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082D9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082DD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082E30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082E88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082F20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80082FEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800830D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008318C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80083218);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008329C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800833D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800834B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80083544);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80083574);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800835B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80083688);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80083710);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800837FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80083954);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800839B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80083A18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80083A58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80083B20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80083BB8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80083C2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80083D30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80083DC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80083E44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80083E70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80083EAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80083F6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80083FFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800840D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80084154);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800841D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80084218);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80084254);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80084338);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80084394);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008442C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800844AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80084534);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80084570);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800845C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008460C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800846D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80084724);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80084774);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800847B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80084870);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80084910);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008498C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800849FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80084A40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80084A7C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80084B14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80084CD4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80084DB8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80084E10);

void func_80084E4C(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80084E54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80084EE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008502C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800851FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80085238);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800852C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800853A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80085460);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80085580);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80085604);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80085640);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800856C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80085768);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800857C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80085814);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800858DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80085988);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80085A44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80085BE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80085C38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80085D38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80085DCC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80085E70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80085ECC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80085F08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80085F50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80085F8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086008);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086124);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086268);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800862A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800862F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800863E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086488);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008649C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800864FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008654C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086640);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086704);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086740);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800867C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086860);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086900);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800869BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800869F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086A6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086B08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086B60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086B74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086BB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086C00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086C70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086D04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086D84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086E2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086E80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086F28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80086F78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008700C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087088);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800870FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087168);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800871C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087254);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800872E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087364);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087414);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008746C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008752C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008759C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087604);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008765C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087698);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087708);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800877A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087860);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087928);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087980);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087A00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087AF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087B98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087BE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087C70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087D3C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087E0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087ED4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087F30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087F78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80087FB4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80088020);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800880BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80088140);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800881F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80088338);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800883CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800884D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80088530);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80088584);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800885DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80088658);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800886A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800886F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800887DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008888C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800888D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80088974);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800889A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800889DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80088AD0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80088BA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80088BE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80088C40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80088D30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80088D8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80088E04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80088EA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80088F78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80088FF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800890B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80089138);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800891C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008924C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80089314);

void func_80089334(struct Unk* arg0)
{
    arg0->unk5 = arg0->unk94;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80089340);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008937C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800893DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80089438);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80089474);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800894BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80089524);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80089588);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80089798);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80089910);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80089984);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80089A10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80089AA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80089B58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80089C0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80089C7C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80089EBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80089EC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80089F58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80089F94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80089FAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80089FD4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008A024);

void func_8008A05C(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008A064);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008A180);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008A2E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008A3B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008A4D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008A60C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008A778);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008A8E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008A9F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008AAF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008AC20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008AC40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008AD48);

void func_8008AD74(void)
{
}

void func_8008AD7C(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008AD84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008ADC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008ADFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008AE94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008AEC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008AED0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008AEE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008AF10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008AF30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008B020);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008B188);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008B270);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008B33C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008B42C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008B4B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008B5C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008B69C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008B7D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008B898);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008B8B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008B984);

void func_8008B9B0(void)
{
}

void func_8008B9B8(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008B9C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008B9FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008BA38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008BB6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008BCB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008BD10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008BD5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008BDAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008BE74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008BEC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008BF00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008BF54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008C014);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008C0C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008C10C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008C204);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008C240);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008C27C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008C30C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008C360);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008C39C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008C3F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008C43C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008C4B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008C5A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008C664);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008C7E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008C888);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008C8E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008C95C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008C998);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008C9E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008CA60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008CB2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008CBF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008CC7C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008CCD4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008CD44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008CD80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008CF68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008CFAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008D050);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008D0D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008D138);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008D19C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008D278);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008D2FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008D340);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008D37C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008D3B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008D410);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008D460);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008D4E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008D548);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008D590);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008D5C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008D764);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008D830);

void func_8008D86C(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008D874);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008D8DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008D95C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008D9C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008DAAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008DAE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008DC5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008DC9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008DD38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008DDE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008DE5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008DEC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008DF1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008DF8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008E040);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008E0CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008E14C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008E18C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008E1E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008E244);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008E318);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008E354);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008E3C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008E404);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008E45C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008E4BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008E590);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008E5CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008E638);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008E67C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008E6D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008E748);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008E8C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008E99C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008E9B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008EA3C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008EA88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008EAE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008EBC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008EC48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008ED18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008EDE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008EED4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008EF94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008F01C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008F0A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008F134);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008F16C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008F1A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008F3F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008F4BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008F578);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008F6FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008F76C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008F7F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008F884);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008F938);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008F974);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008FA0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008FA88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008FB38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008FBCC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008FD6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008FDF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008FEE0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8008FF50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009002C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800900E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80090148);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800901B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009027C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80090470);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80090508);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800905D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800906E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80090720);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80090838);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009093C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009099C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80090A28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80090AC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80090B04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80090BD4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80090BE0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80090C54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80090CFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80090D24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80090D6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80090E2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80090F0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80090FC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80091008);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800910E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009114C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800911DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80091218);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80091448);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800914EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800915C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80091754);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800917AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80091898);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009197C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800919C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80091A00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80091AC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80091B1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80091C64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80091D1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80091E18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80091E38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80091EC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80091FC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009216C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800921E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009227C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800922D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80092314);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80092408);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80092490);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800924F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80092598);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80092600);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80092614);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80092648);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80092684);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009273C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800927B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800927EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80092828);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80092918);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800929A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800929DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80092AE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80092B5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80092C2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80092CEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80092D64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80092E2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80092F08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80093014);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80093130);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800931A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80093260);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800932A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80093310);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800933A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800933EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009343C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009347C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800934D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80093524);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80093564);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80093610);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009372C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009377C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800937EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80093858);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800938C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80093930);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800939F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80093A5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80093AAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80093B4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80093BA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80093C08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80093C54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80093CBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80093D78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80093EB4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80093FC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009403C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80094078);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80094104);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80094154);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009416C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800941D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80094280);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800942E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009443C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800944B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009462C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800946F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80094794);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009481C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009485C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800948D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80094A04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80094A78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80094B24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80094C18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80094D40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80094DC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80094E50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80094EC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80094F14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80094F74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800951C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80095254);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800953D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80095430);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009547C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800954BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80095538);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009564C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80095770);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800957B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80095854);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009596C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80095A28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80095AAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80095B10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80095B94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80095BE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80095C38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80095CC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80095D18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80095D60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80095DA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80095DC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80095E3C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80095F9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80096018);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80096060);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80096170);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800961B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009633C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800963E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80096584);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009663C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80096794);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80096834);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800968F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80096994);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800969D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80096A84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80096B54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80096C8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80096DC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80096E10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80096EA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80097048);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800970EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80097144);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800971D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80097214);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80097278);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800972C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800972DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80097328);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80097384);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80097430);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800975DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80097670);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800976DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80097740);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80097780);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800977D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80097804);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80097860);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800978DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80097A24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80097AC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80097B14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80097B28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80097BA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80097CF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80097DD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80097EEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80097FC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80098138);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800981CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80098338);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80098474);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800985F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80098630);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80098728);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800987A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800987DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80098838);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80098874);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800988C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80098970);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80098990);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800989CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80098A78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80098A9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80098ABC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80098AF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80098C08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80098C84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80098CC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80098D64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80098DA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80098EA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80098F4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80098F88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80099118);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800992C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800992FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80099338);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80099388);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80099480);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800994A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800994DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80099784);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009982C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800998D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800999D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80099A28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80099A8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80099B0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80099B30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80099B6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80099C68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80099CF0);

void func_80099D10(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80099D18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80099D54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80099E34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80099F28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80099F48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009A10C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009A264);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009A338);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009A358);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009A3B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009A448);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009A4F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009A598);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009A5B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009A5F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009A6B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009A7D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009A7F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009A87C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009A964);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009A984);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009A9E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009AC40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009AD08);

void func_8009AD28(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009AD30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009AD6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009ADF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009AEBC);

void func_8009AEDC(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009AEE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009AF98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009B020);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009B040);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009B07C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009B0B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009B12C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009B1C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009B1E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009B2F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009B3C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009B3E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009B424);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009B594);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009B654);

void func_8009B674(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009B67C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009B6B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009B734);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009B7D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009B7F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009B85C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009B9B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009BA4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009BA6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009BAE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009BC14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009BD08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009BD28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009BD64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009BE14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009BEF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009BF14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009BF50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009BFE0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009C0D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009C0F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009C12C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009C238);

void func_8009C258(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009C260);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009C298);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009C344);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009C364);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009C3A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009C45C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009C588);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009C5F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009C638);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009C784);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009C860);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009C96C);

void func_8009C9C8(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009C9D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009C9F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009CAA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009CAC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009CAFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009CBA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009CC44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009CC64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009CCB4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009CD80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009CDE0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009CF18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009CF38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009CF74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009D048);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009D1D8);

void func_8009D1F8(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009D200);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009D23C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009D3F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009D560);

void func_8009D580(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009D588);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009D74C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009D788);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009D85C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009D8F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009DA08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009DA28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009DA7C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009DB1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009DB9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009DCF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009DD40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009DD7C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009DE04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009DF40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009DF60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009DFA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009E098);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009E0B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009E0F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009E188);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009E34C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009E3A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009E490);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009E5A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009E5B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009E608);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009E690);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009E718);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009E7B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009E7EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009E8E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009E9EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009EAA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009EAF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009EB6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009EBA8);

void func_8009ED70(struct Unk* arg0)
{
    func_80015DC8(arg0);
    func_8002B694(arg0);
    func_8002D9BC(arg0);

    if (func_8002BB80(arg0, &D_801418C8) != 0) {
        if (arg0->unk2 & 0x40) {
        label:
            func_800AF808(arg0);
        }
    } else if (!(arg0->unk2 & 0x40) || (CollisionRelated(arg0), arg0->unk70 == 0)) {
        if (func_8002B160(arg0) == 0) {
            func_8002B288(arg0);
            return;
        }
    } else {
        goto label; // unfortunately seems to be necessary for a match
    }

    arg0->state++;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009EE40);

void func_8009EE60(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009EE68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009EEC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009F160);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009F218);

void func_8009F238(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009F240);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009F27C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009F3A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009F44C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009F46C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009F4C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009F594);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009F618);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009F638);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009F674);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009F7C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009F89C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009F94C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009F9E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009FB38);

void func_8009FB58(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009FB60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009FB9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009FD00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009FE38);

void func_8009FE58(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009FE60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009FF10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8009FF4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A00C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A0150);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A0170);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A02FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A035C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A037C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A03B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A03F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A068C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A0A18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A0A38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A0C4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A0FC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A0FE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A12EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A16DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A16FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A18A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A18F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A19A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A1B1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A1BEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A1C90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A1CCC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A1E3C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A1F7C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A2098);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A220C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A2278);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A22D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A2310);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A23B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A23C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A23E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A241C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A24F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A25EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A2748);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A27F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A2870);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A2928);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A29C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A2A58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A2AA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A2B8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A2C70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A2CEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A2D54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A2E6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A2EB4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A2F2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A3010);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A3078);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A3170);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A31CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A325C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A32B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A33A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A348C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A3520);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A3658);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A366C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A3758);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A382C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A38B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A3924);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A3960);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A3A4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A3C50);

void func_800A3C70(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A3C78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A3CB4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A3FEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A4230);

void func_800A4284(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A428C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A42C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A4518);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A46D4);

void func_800A46F4(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A46FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A47C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A4800);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A4968);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A4A50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A4ABC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A4ADC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A4B6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A4D00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A4D20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A4E48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A4F04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A4F24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A4FEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A5070);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A50EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A5144);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A5194);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A5318);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A5348);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A5384);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A5404);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A5460);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A5500);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A5540);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A56C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A56E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A5A04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A5AA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A5BA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A5C90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A5D20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A5D78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A5DEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A5E60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A5F4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A6028);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A6094);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A60D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A61CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A6238);

void func_800A6258(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A6260);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A62D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A62F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A6374);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A63B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A6510);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A6600);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A666C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A6794);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A67FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A6860);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A6940);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A6960);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A699C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A6C00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A6C7C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A6DCC);

void func_800A6DEC(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A6DF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A6FCC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7008);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7104);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7208);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7240);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7318);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A73A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A73C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7458);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A74E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7504);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7570);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7600);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A766C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A77D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7820);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7878);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7928);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A79A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A79E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7A54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7A90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7AF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7B2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7BC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7BE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7C50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7CE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7E10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7E40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7E98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7F44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A7FF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A8074);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A80D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A8164);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A81E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A826C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A829C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A82EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A833C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A836C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A83C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A84D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A858C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A8628);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A8A58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A8AE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A8B88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A8C88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A8D1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A8D68);

void func_800A8DB8(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A8DC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A8E50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A8FBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A9054);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A90C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A916C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A91D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A9210);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A92C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A9334);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A93FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A94A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A94D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A9544);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A9654);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A96F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A97C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A9818);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A98AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A9928);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A9964);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A9AEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A9C24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A9C7C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A9CBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A9D98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A9DB8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A9DF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A9EC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A9F30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800A9FD0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AA000);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AA030);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AA10C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AA148);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AA20C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AA2FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AA3A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AA488);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AA5A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AA5E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AA68C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AA730);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AA7B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AA85C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AA954);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AA994);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AAA98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AAAD4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AAB74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AAC5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AAC98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AAD44);

void func_800AAD64(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AAD6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AAE94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AAFF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB050);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB128);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB170);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB224);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB32C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB384);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB3A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB4C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB518);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB564);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB5A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB66C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB6C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB710);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB768);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB7C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB814);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB868);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB8C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB8EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB98C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AB9C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800ABB50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800ABB70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800ABE08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AC114);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AC180);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AC204);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AC31C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AC364);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AC3BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AC440);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AC4A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AC4F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AC550);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AC5BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AC610);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AC66C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AC6A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AC6E8);

void func_800AC708(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AC710);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AC7CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AC7EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AC848);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AC8C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800ACCAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800ACD04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800ACD84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800ACDE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800ACE90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800ACF60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AD00C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AD080);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AD12C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AD1B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AD224);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AD338);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AD404);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AD440);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AD47C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AD4DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AD538);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AD630);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AD66C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AD6DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AD820);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AD868);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AD8C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AD92C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AD9C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800ADA0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800ADA64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800ADAD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800ADBE0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800ADCE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800ADD40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800ADDB4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800ADE04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800ADE54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800ADED4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800ADEF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800ADF30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AE1BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AE2AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AE2FC);

void func_800AE31C(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AE324);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AE3D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AE3F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AE450);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AE4F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AE594);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AE63C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AE65C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AE6B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AE714);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AE790);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AE7DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AE848);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AE88C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AE8E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AE95C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AE9D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AEA58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AEAA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AEAC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AEB1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AEBA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AEC48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AEC9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AED18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AEE5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AEED8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AEF18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AF02C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AF084);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AF15C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AF1AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AF22C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AF28C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AF388);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AF488);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AF504);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AF58C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AF610);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AF658);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AF6A0);

void func_800AF808(struct Unk* arg0)
{
    func_800AF828(arg0, 0);
}

void func_800AF828(struct Unk* arg0, s8 arg1)
{
    func_800AFAB4(arg1, arg0->x_pos.i.hi, arg0->y_pos.i.hi, (func_8002B73C() & 1) ^ 1);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AF878);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AF95C);

struct Unk* func_800AFAB4(s8 arg0, s16 x, s16 y, s8 arg3)
{
    struct Unk* temp_v0 = func_8002AD3C();
    if (temp_v0 != NULL) {
        temp_v0->active = 0x21;
        temp_v0->id = 4;
        temp_v0->unk2 = arg0;
        temp_v0->state = 0;
        temp_v0->unk5 = 0;
        temp_v0->unk6 = 0;
        temp_v0->unk5C = arg3;
        temp_v0->x_pos.i.hi = x;
        temp_v0->x_pos.i.lo = 0;
        temp_v0->y_pos.i.hi = y;
        temp_v0->y_pos.i.lo = 0;
        temp_v0->unk15 = 0;
        temp_v0->unk14 = 0;
        temp_v0->unk16 = 1;
    }
    return temp_v0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AFB50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AFB90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AFC4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AFC9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AFD20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AFD6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AFDA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AFE20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AFEA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AFF08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AFF28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800AFF78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B0320);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B054C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B0600);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B06AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B0804);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B0890);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B08CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B0B48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B0C78);

void func_800B0C98(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B0CA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B10E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1354);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1394);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1450);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B14E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1524);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B158C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B16B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1758);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B17AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B17CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1808);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1864);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B199C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B19BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B19F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1A48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1AD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1AF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1B34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1B74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1C3C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1C5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1C98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1CF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1D4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1D6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1DA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1DE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1E84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1EA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1EE0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B1F78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B2070);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B2090);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B20CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B2200);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B22B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B23DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B2444);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B2544);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B2698);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B2880);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B28CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B2A3C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B2AD0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B2C8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B2D48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B2D84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B2DD0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B2E98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B2F60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3000);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3020);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3074);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B30B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3100);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B320C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B322C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3358);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3444);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B34EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3508);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B355C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B357C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B35B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B35F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B36F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B372C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3768);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B37F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3848);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3884);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B392C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B397C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B39B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3A60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3AB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3B1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3B58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3B94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3C34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3C90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3CCC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3D3C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3DE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3E20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3E40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3E7C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3EB8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B3FD4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B41AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B41CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4208);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4274);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4450);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4480);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4558);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4578);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4598);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4610);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B464C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B46C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B46E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4754);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4790);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4808);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4858);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4894);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B490C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4960);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B499C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4A18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4A6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4AA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4B0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4B64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4BA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4CC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4D00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4E14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B4E34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B518C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B51E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B522C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B5280);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B52D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B5348);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B5448);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B54B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B54EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B5534);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B5570);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B55AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B56D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B56F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B5730);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B5798);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B58A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B58DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B58F4);

// scaling X animation in logo graphics
void TitleScalingXUpdate(struct EffectObj* arg0)
{
    g_TitleScalingXUpdateFuncs[arg0->state]();
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B599C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B5B54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B5C60);

void func_800B5CC4(struct EffectObj* arg0)
{
    if (arg0->state == 0) {
        func_800B5D04();
        return;
    }
    func_800B5E2C();
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B5D04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B5E2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B5EB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B5EEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B6060);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B6080);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B60BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B649C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B64BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B6660);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B6A0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B6A48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B6A90);

// didn't notice what this is
void func_800B6B18(struct EffectObj* arg0)
{
    D_8010B4C4[arg0->state]();
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B6B54);

void func_800B6C74(s32 arg0)
{
    func_800B6C9C(arg0);
}

void func_800B6C94(s32 arg0)
{
}

void func_800B6C9C(s32 arg0)
{
    func_800B6D1C(arg0, 0, func_800B6FF4(arg0, 0));
    func_800B6D1C(arg0, 1, func_800B6FF4(arg0, 1));
    func_800B6D1C(arg0, 2, func_800B6FF4(arg0, 2));
}

void func_800B6D1C(s32 arg0, s8 arg1, s8 arg2)
{
    s8 temp;
    u16 a1, a3;
    struct BackgroundObj* temp_s0;

    temp_s0 = &D_801419B0[arg1];
    if (arg2 != 0) {
        if (arg2 & 1) {
            a1 = temp_s0->unk8.i.hi;
            a3 = temp_s0->unkC.i.hi;
            func_800B6EB4(a1 + 0x130, a1 + 0x190, a3 - 0x50, a3 + 0x140, arg0);
        }
        temp = arg2 & 2;
        if (temp != 0) {
            a1 = temp_s0->unk8.i.hi;
            a3 = temp_s0->unkC.i.hi;
            func_800B6EB4(a1 - 0x50, a1 - 0x10, a3 - 0x50, a3 + 0x140, arg0);
        }
        temp = arg2 & 4;
        if (temp != 0) {
            a1 = temp_s0->unk8.i.hi;
            a3 = temp_s0->unkC.i.hi;
            func_800B6EB4(a1 - 0x50, a1 + 0x190, a3 + 0x100, a3 + 0x140, arg0);
        }
        temp = arg2 & 8;
        if (temp != 0) {
            a1 = temp_s0->unk8.i.hi;
            a3 = temp_s0->unkC.i.hi;
            func_800B6EB4(a1 - 0x50, a1 + 0x190, a3 - 0x50, a3 - 0x10, arg0);
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B6EB4);

s8 func_800B6FF4(s32 arg0, s8 arg1)
{
    struct BackgroundObj* ptr = &D_801419B0[arg1];
    s8 result = 0;

    if (ptr->unk14.i.hi != ptr->unk8.i.hi) {
        if (ptr->unk14.i.hi < ptr->unk8.i.hi) {
            result = 1;
        } else {
            result = 2;
        }
    }

    if (ptr->unk18.i.hi != ptr->unkC.i.hi) {
        if (ptr->unk18.i.hi < ptr->unkC.i.hi) {
            result |= 4;
        } else {
            result |= 8;
        }
    }

    return result;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B7078);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B70B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B70EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B7140);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B7180);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B71A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B72C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B7304);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B7318);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B7328);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B7368);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B7394);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B73D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B7414);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B7440);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B7480);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B74C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B74EC);

void func_800B7520(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B7528);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B75C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B7604);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B7630);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B7668);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B76A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B7764);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B7934);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B7B18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B7CFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B7E88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B7EE8);

void func_800B8064(struct EffectObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B806C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B80A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8114);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8470);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8490);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B84DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8518);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8554);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8610);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8630);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B875C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B887C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B89B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B89CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8A9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8ABC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8AF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8B34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8B6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8BC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8C00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8C20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8C30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8C70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8C90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8CA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8CE0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8D00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8D10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8D50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8D7C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8D8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8DCC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8DEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8DFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8E3C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8E5C);

void func_800B8E6C(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8E74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8F5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B8F98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B902C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9070);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9100);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B913C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B91E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9310);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9354);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B94B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9690);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B96CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B96E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B97B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B97D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9940);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B997C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B99B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9A08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9A48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9A68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9A78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9AB8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9AD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9AE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9B28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9B48);

void func_800B9B58(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9B60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9BD0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9C0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9C44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9C98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9CD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9CF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9D08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9D48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9D68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9D78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9DB8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9DCC);

void func_800B9DDC(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9DE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9E54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9EC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800B9F38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA178);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA340);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA4E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA520);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA540);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA57C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA5B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA5F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA644);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA684);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA6AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA7C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA808);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA81C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA82C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA86C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA898);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA8CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA90C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA938);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA948);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA988);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA9A8);

void func_800BA9B8(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BA9C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BAA30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BAA6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BAAE0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BAB3C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BABA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BAC58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BAD10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BAD44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BADD0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BAE5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BAE94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BAF04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BAF24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BAF60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BAF9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BAFD4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB028);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB068);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB088);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB098);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB0D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB0F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB108);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB148);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB168);

void func_800BB178(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB180);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB1F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB314);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB364);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB508);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB588);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB5F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB68C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB750);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB85C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB888);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB928);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BB97C);

// megaman never teleports in if nopped out
// asm(".rept 13 ; nop ; .endr");
void TeleportRelatedObjectUpdate(struct EffectObj* arg0)
{
    D_8010BEC8[arg0->state]();
}

void func_800BB9F4(struct Unk21* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->unk14 = 0;
        arg0->unk15 = 0;
        arg0->unk16 = 0;
        arg0->unk4 = 1;
        arg0->unk5 = 0;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BBA24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BBBF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BBC14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BBC50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BBD24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BBD88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BBE84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BBEA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BBF34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BBFCC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BC144);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BC180);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BC210);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BC258);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BC2E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BC370);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BC3E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BC4D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BC518);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BC554);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BC568);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BC5D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BC63C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BC6FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BC748);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BC784);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BC92C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BCD84);

void func_800BCE40(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BCE48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BCE84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BCEE4);

void func_800BD01C(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BD024);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BD080);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BD1A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BD1E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BD23C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BD280);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BD31C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BD348);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BD384);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BD3C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BD478);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BD4EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BD50C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BD5AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BD654);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BD690);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BD708);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BD7B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BD890);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BD8C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BD938);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BDA2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BDA4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BDA94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BDB10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BDBD4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BDD08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BDDE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BDE68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BDEA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BDF20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BDF40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BDFC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE038);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE074);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE0DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE0FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE184);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE1C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE214);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE25C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE2C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE30C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE32C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE364);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE434);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE4A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE4D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE510);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE540);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE57C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE598);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE5F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE6D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE714);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE730);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE7C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE800);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE83C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE878);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE8E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE960);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE9A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BE9E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BEB14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BEB94);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BEBB4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BEBFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BED6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BEED4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BEFCC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BF1FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BF508);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BF530);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BF5EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BF60C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BF638);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BF730);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BF76C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BFA00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BFB90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BFBB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BFBD0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BFCC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800BFF0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C00BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C03BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C0404);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C044C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C0558);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C05FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C07B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C081C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C0864);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C09C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C0C78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C0D98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C0DFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C0E74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C0EBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C1050);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C1224);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C1244);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C1318);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C1390);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C13D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C14F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C1590);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C165C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C169C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C16F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C1820);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C1938);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C1958);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C1994);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C19F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C1B54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C1B98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C1C24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C1C88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C1D90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C1E10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C1E7C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C1FE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C204C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C20AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C20F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C229C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C24C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C24E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C2528);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C2638);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C27D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C2850);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C28E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C2918);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C2A04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C2AF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C2BE0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C2C3C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C2D6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C2DE0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C2E00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C2E20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C2EAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C2F18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C2F54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3030);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3114);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3198);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C31C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3224);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C32BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3364);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3438);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3484);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C34A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C34D4);

void func_800C34E8(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C34F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C351C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3578);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C369C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C36E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C37C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3828);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3880);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C38C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C39AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3A0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3A20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3A40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3A7C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3AD4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3B40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3BA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3C9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3CE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3CF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3D40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3E4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3F98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C3FEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C40A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C40F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C413C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C41C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C4290);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C42B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C42EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C4544);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C458C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C460C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C4678);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C470C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C4778);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C49BC);

void func_800C4BE4(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C4BEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C4C64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C4CE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C4D20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C4E78);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C4EC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C4F04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C4F40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C5058);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C5078);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C5210);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C52CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C53A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C5444);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C54DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C54FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C5544);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C5580);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C56B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C56F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C5710);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C5774);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C580C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C5904);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C5994);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C5B5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C5BCC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C5C4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C5C88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C5D44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C5F04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C5F30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C5F50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C5F70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C5F90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C6054);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C609C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C6198);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C6228);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C62DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C63BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C661C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C6680);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C670C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C6814);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C6894);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C68E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C6928);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C6984);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C6A0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C6A7C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C6ACC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C6B30);

void func_800C6B7C(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C6B84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C6C2C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C6CE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C6DD4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C6EDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C7164);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C71C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C7460);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C74D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C7538);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C7558);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C7578);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C7648);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C76A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C76E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C7754);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C77BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C7830);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C785C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C78BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C7970);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C7A68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C7AB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C7B0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C7B60);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C7B80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C7BF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C7C30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C7D40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C7D84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C7DA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C7EDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C7F1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C80D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C813C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C8214);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C833C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C842C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C85D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C8610);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C8708);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C8774);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C87B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C8938);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C899C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C8B74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C8BDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C8E90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C8FA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C8FE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C903C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C90A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C90C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C90F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C9190);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C91B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C91EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C92B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C92E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C9368);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C938C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C93C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C9450);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C94F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C9510);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C969C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C9914);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C993C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C99CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C9C64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C9CB0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C9D08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C9D28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C9D64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C9DA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C9E34);

// megaman standing in the briefing room. doesn't show
// up if nopped out
// asm(".rept 13 ; nop ; .endr");
void MegamanInBriefingRoomUpdate(struct MiscObj* arg0)
{
    g_MegamanInBriefingRoomUpdateFuncs[arg0->state]();
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800C9EE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA030);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA0C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA110);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA188);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA208);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA228);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA3C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA40C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA46C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA4B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA4F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA52C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA60C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA6F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA718);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA754);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA7E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA830);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA86C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA954);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA9B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CA9EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CAB10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CAC18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CAC54);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CACF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CADD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CADF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CAE38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CAF90);

// megaman never appears in stage if nopped out
void MegamanRelatedUpdate(struct MiscObj* arg0)
{
    g_MegamanRelatedUpdateFuncs[arg0->state]();
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CB048);

void func_800CB1F0(struct Unk* arg0)
{
    D_8010E6FC[arg0->unk2](); // the animation before ready appears but "READY" doesn't if nopped out
}

// animation leading up to "READY" shows up but "READY" never apprears
// if nopped out
// asm(".rept 18 ; nop ; .endr");
void func_800CB22C(struct Unk* arg0)
{
    ReadyTextUpdateFuncs[arg0->unk5]();
    func_8002B288(arg0);
}

// ReadyText State 0
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CB27C);

// ReadyText State 1
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CB394);

// ReadyText State 2
// "READY" never disappears if nopped out
// asm(".rept 26 ; nop ; .endr");
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CB4E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CB554);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CB590);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CB5B4);

void func_800CB614(struct Unk* arg0)
{
    ZeroObjectState(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CB634);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CB708);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CB828);

// title object. Includes the logo and the menu graphics
void TitleUpdate(struct MiscObj* arg0)
{
    g_TitleUpdateFuncs[arg0->state]();
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CB884);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CB8F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CB940);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CB9C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CBA5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CBA80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CBD40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CBD80);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CBE34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CBECC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CBF14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CC040);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CC0AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CC0E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CC114);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CC1F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CC234);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CC304);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CC350);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CC38C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CC3D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CC418);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CC460);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CC4E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CC738);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CC79C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CC7BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CC7F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CC8E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CC908);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CC944);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CCA14);

// SelectACharacterUpdate state 0
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CCA34);

// D_8010EB84 state 0
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CCCA0);

// D_8010EB84 state 1
void func_800CCD48(struct MiscObj* arg0)
{
    if (D_801721E7 & 0x80) {
        arg0->unk6++;
        // sets how fast the X and Zero portraits move
        // to the left and right after selecting a character
        if (arg0->unk2 != 0) {
            arg0->unk20 = FIXED(16);
        } else {
            arg0->unk20 = FIXED(-16);
        }
    }
}

// D_8010EB84 state 2
void func_800CCD8C(struct MiscObj* arg0)
{
    func_8002B718(arg0);
    if (arg0->unk3 == 0) {
        arg0->state++;
    }
}

// D_8010EB84 state 3
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CCDD4);

void func_800CCEB4(struct MiscObj* arg0)
{
    D_8010EB84[arg0->unk6]();
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CCEF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CCF70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CD034);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CD0A4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CD110);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CD178);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CD1E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CD2BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CD390);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CD408);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CD498);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CD530);

// SelectACharacterUpdate state 1
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CD6D8);

// SelectACharacterUpdate state 2
void func_800CD730(struct Unk18* arg0)
{
    ZeroObjectState(arg0);
}

// select a character menu never appears if nopped out
void SelectACharacterUpdate(struct MiscObj* arg0)
{
    g_SelectACharacterUpdateFuncs[arg0->state]();
}

// TitleLogoUpdate state 0
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CD78C);

// TitleLogoUpdate state 1
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CD90C);

// TitleLogoUpdate state 2
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CD974);

// TitleLogoUpdate state 3
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CDA90);

// TitleLogoUpdate state 4
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CDAD0);

// TitleLogoUpdate state 5
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CDB10);

// TitleLogoUpdate state 6
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CDB84);

// TitleLogoUpdate state 7
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CDC34);

// part of the title logo animation
void TitleLogoUpdate(struct MiscObj* arg0)
{
    arg0->unk3 = 0;
    g_TitleLogoUpdateFuncs[arg0->state]();
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CDCC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CDCFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CDE24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CDE44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CDF4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CE080);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CE0D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CE114);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CE1D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CE304);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CE340);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CE388);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CE670);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CE6AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CE6CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CE754);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CE7C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CE81C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CE894);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CE8DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CEA40);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CEAC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CEAE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CEB44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CEBC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CEE30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CEE6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CEEC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CEF34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CEFC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CF0B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CF144);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CF184);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CF268);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CF2B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CF300);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CF428);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CF498);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CF4B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CF5F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CF640);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CF660);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CF708);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CF754);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CF790);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CF7CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CF824);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CF844);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CF898);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CF8F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CF950);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CFAC8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CFB20);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CFB70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CFC6C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CFD38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CFE00);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CFE3C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CFE5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CFE98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800CFEE0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D0118);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D0374);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D03B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D04D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D0528);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D0548);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D05B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D05F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D0658);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D0698);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D06E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D0754);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D07C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D07EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D0828);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D0988);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D09E4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D0A04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D0AA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D0B14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D0B68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D0B90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D0BE4);

void func_800D0C60(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D0C68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D0D68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D0E48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1060);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D10E4);

void func_800D115C(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1164);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D11B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D11CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1228);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1248);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1284);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D12C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1464);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D14D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D14F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D154C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D15A8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1614);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D166C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D16E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1708);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D177C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D17F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1864);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D188C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D18C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1990);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1A48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1AE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1B08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1B44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1CF8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1D38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1D58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1D88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1DC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1E0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1E9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1F04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1F24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1F74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D1FB8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D2010);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D2030);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D2094);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D212C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D2190);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D2420);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D24B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D254C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D25AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D25FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D26F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D2794);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D2854);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D28BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D28E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D2924);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D2970);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D29C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D29FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D2A38);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D2A74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D2B9C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D2C04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D2CA4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D2D7C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D2DCC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D2E1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D2E64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D2EDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D2F34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D2FC4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D301C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D3048);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D3084);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D31F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D323C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D3288);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D330C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D332C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D3388);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D34AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D34F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D3510);

void func_800D354C(struct UnkObj* arg0)
{
    s32* addr_801F3000 = (s32*)0x801F3000;
    s32 temp_v1;

    arg0->unk40 = 0x1F00;
    temp_v1 = *addr_801F3000;
    arg0->unk14 = -1;
    arg0->unk3C = temp_v1 + (s32)addr_801F3000;
    arg0->unk15 = 0;
    if (arg0->y_pos.i.hi == 0x10) {
        arg0->unk42 = 0x7802;
    } else {
        arg0->unk42 = 0x7800;
    }
    arg0->x_pos.i.hi = 0xA0;
    arg0->unk16 = 0;
    arg0->unk47 = arg0->unk2;
    arg0->unk4++;
    if (arg0->unk2 < 9) {
        arg0->unk4++;
    }
}

void func_800D35D0(struct UnkObj* arg0)
{
    s32* addr_801F3000 = (s32*)0x801F3000;
    s32* addr_801F3008 = (s32*)0x801F3008;
    u32 temp_v1;

    arg0->unk40 = 0x1E00;
    arg0->unk30 = D_8010ECD4;
    temp_v1 = *addr_801F3008;
    arg0->unk14 = -1;
    arg0->unk3C = temp_v1 + (s32)addr_801F3000;
    arg0->unk15 = 0;
    if (arg0->unk2 == -1) {
        arg0->unk42 = 0x7806;
        arg0->y_pos.i.hi = arg0->unk50[D_80141BDF[0] * 2] + 8;
        arg0->unk54 = D_80141BDF[0];
        func_80015D60(arg0, 0);
    } else {
        arg0->unk42 = 0x784B;
        arg0->x_pos.i.hi = 0x60;
        arg0->y_pos.i.hi = 0xD0;
        arg0->unk47 = 0x29;
    }
    arg0->unk16 = 0;
    arg0->unk4 = 3;
}

void func_800D36AC(struct UnkObj* arg0)
{
    if (arg0->unk2 < 0) {
        func_800D35D0(arg0);
    } else {
        func_800D354C(arg0);
    }
    func_8002B288(arg0);
}

void func_800D3700(struct UnkObj* arg0)
{
    s8 temp_v1; // probably fake

    if (arg0->y_pos.i.hi != 0x10) {
        if (arg0->unk7 == D_80141BDF[0]) {
            arg0->unk42 = 0x7803;
        } else {
            arg0->unk42 = 0x7800;
        }
    }
    if ((D_80141BE0 == 0) && (D_80172203 != 0)) {
        temp_v1 = arg0->unk7;
        if ((arg0->unk7 < 7) && (temp_v1 >= 5)) {
            arg0->unk42 = 0x7804;
        }
    }
    func_8002B288(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D3798);

void func_800D38A0(struct UnkObj* arg0)
{
    if (arg0->unk2 == -1) {
        if (arg0->unk54 != D_80141BDF[0]) {
            arg0->y_pos.i.hi = arg0->unk50[D_80141BDF[0] * 2] + 8;
            arg0->unk54 = D_80141BDF[0];
        }
        func_80015DC8(arg0, D_80141BDF);
    }
    func_8002B288(arg0);
}

void func_800D3928(struct UnkObj* arg0)
{
    arg0->unk3 = 0;
    D_8010F5E8[arg0->unk4]();
}

void func_800D3964(struct UnkObj* arg0)
{
    s16 var_v0;
    s32* addr_801F3000 = (s32*)0x801F3000;
    s32 temp_v1;

    arg0->unk40 = 0x1F00;
    temp_v1 = *addr_801F3000;
    arg0->unk14 = -1;
    arg0->unk3C = temp_v1 + (s32)addr_801F3000;
    arg0->unk15 = 0;
    if (arg0->y_pos.i.hi == 0x10) {
        arg0->unk42 = 0x7802;
    } else {
        arg0->unk42 = 0x7800;
    }
    arg0->x_pos.i.hi = 0xA0;
    arg0->unk16 = 0;
    arg0->unk47 = arg0->unk2;
    arg0->unk4++;
    func_8002B288(arg0);
}

void func_800D39EC(struct UnkObj* arg0)
{
    s8 temp_v1; // probably fake

    if (arg0->y_pos.i.hi != 0x10) {
        if (arg0->unk7 == D_80141BDF[0]) {
            arg0->unk42 = 0x7803;
        } else {
            arg0->unk42 = 0x7800;
        }
    }
    if ((D_80141BE0 == 0) && (D_80172203 != 0)) {
        temp_v1 = arg0->unk7;
        if ((arg0->unk7 < 7) && (temp_v1 >= 5)) {
            arg0->unk42 = 0x7804;
        }
    }
    func_8002B288(arg0);
}

void func_800D3A84(struct UnkObj* arg0)
{
    arg0->unk3 = 0;
    D_8010F5F8[arg0->unk4]();
}

// search lights in background of intro stage
void SearchLightUpdate(struct QuadObj* arg0)
{
    g_SearchLightUpdateFuncs[arg0->state]();
}

// SearchLight state 0
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D3AFC);

// SearchLight state 1
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D3C58);

// SearchLight state 2
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D3FBC);

void func_800D3FE0(struct Unk22* arg0)
{
    arg0->unk48 += arg0->unk38;
    arg0->unk4C += arg0->unk40;
    arg0->unk38 += arg0->unk3C;
    arg0->unk40 += arg0->unk44;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D4024);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D41B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D41EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D4334);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D43F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D46D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D46F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D4948);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D4984);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D4A64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D4B30);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D4C14);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D4C50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D4DE0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D4F84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D4FA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800D5144);
