#ifndef MAIN_E47C_MENU_DATA_H
#define MAIN_E47C_MENU_DATA_H

struct GameInfoAuxData {
    u8 scripts[3][16];
    u32 lookup[8];
};

extern u8 D_800F22D0[];
extern u8 D_800F22E0[];
extern u8 D_800F22F0[16];
extern u8 D_800F2300[];
extern u8 D_800F2310[12];
extern u8 D_800F231C[12];
extern u8 D_800F2328[16];

extern struct GameInfoAuxData D_800F2338;
extern RECT D_800F2388;

#endif
