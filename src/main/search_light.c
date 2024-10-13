#include "common.h"

// search lights in background of intro stage
void SearchLightUpdate(struct QuadObj* arg0)
{
    g_SearchLightUpdateFuncs[arg0->state]();
}

// SearchLight state 0
INCLUDE_ASM("asm/us/main/nonmatchings/search_light", func_800D3AFC);

// SearchLight state 1
INCLUDE_ASM("asm/us/main/nonmatchings/search_light", func_800D3C58);

// SearchLight state 2
INCLUDE_ASM("asm/us/main/nonmatchings/search_light", func_800D3FBC);

// search light helper
void func_800D3FE0(struct Unk22* arg0)
{
    arg0->unk48 += arg0->unk38;
    arg0->unk4C += arg0->unk40;
    arg0->unk38 += arg0->unk3C;
    arg0->unk40 += arg0->unk44;
}

// search light helper
INCLUDE_ASM("asm/us/main/nonmatchings/search_light", func_800D4024);
