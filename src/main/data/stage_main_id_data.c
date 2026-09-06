#include "common.h"

extern u8 D_800F4A50[16];
extern u8 D_800F4A60[16];
extern u8 D_800F5008[12];
extern u8 D_800F5014[12];
extern u8 D_800F55E0[12];
extern u8 D_800F55EC[12];
extern u8 D_800F611C[12];
extern u8 D_800F6128[16];
extern u8 D_800F669C[12];
extern u8 D_800F66A8[12];
extern u8 D_800F6AC4[8];
extern u8 D_800F6ACC[12];
extern u8 D_800F7204[8];
extern u8 D_800F720C[12];
extern u8 D_800F76A0[12];
extern u8 D_800F76AC[12];
extern u8 D_800F7AAC[12];
extern u8 D_800F7AB8[12];
extern u8 D_800F817C[8];
extern u8 D_800F81E0[12];
extern u8 D_800F8470[12];
extern u8 D_800F847C[16];
extern u8 D_800F87C8[8];
extern u8 D_800F87D0[16];

const u8* s_StageMainIds[13][2] = {
    { D_800F4A50, D_800F4A60 },
    { D_800F5008, D_800F5014 },
    { D_800F55E0, D_800F55EC },
    { D_800F611C, D_800F6128 },
    { D_800F669C, D_800F66A8 },
    { D_800F6AC4, D_800F6ACC },
    { D_800F7204, D_800F720C },
    { D_800F76A0, D_800F76AC },
    { D_800F7AAC, D_800F7AB8 },
    { D_800F817C, NULL },
    { D_800F81E0, NULL },
    { D_800F8470, D_800F847C },
    { D_800F87C8, D_800F87D0 },
};
