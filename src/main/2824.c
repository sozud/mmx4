#include "common.h"

// entrypoint
void func_80012024(void)
{
    func_800DAE84();
    func_8001213C();
    while (1) {
        u32 addr = 0x1F800000;

        VSync(0);
        PutDispEnv(&D_80142F80->dispenv);
        PutDrawEnv(&D_80142F80->drawenv);
        DrawOTag(&D_80142F80->unk9C);
        *(s32*)addr ^= 1;
        D_80142F80 = &D_80166C10[*(s32*)addr];
        ClearOTagR(&D_80142F80->unk70, 0xC);
        func_800168D8();
        func_800169D8();
        func_80012328();
        func_80015E0C();
        D_80141BD8.unk0++;
        func_80012600();
        func_80014780();
        DrawSync(0);
        func_80015E54();
        func_80016004();
        DrawSync(0);
        func_80012454();
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/2824", func_8001213C);

void func_800122E0(struct Unk10* arg0)
{
    ClearOTagR(arg0 + 2, 0xC);
    arg0->unk2A = 0;
    arg0->unk2C = 1;
    arg0->unk2D = 0;
    arg0->unk2E = 0;
    arg0->unk2F = 0;
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

INCLUDE_ASM("asm/us/main/nonmatchings/2824", func_800127FC);

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

INCLUDE_ASM("asm/us/main/nonmatchings/2824", func_800129A4);

INCLUDE_ASM("asm/us/main/nonmatchings/2824", func_800129F0);
