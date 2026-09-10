#include "common.h"

u8 D_80108CD0[4] = { 0xF7, 0xF5, 0x12, 0x13 };
u8 D_80108CD4[4] = { 0xF6, 0xE5, 0x12, 0x1D };
u8 D_80108CD8[4] = { 0, 0xFE, 8, 7 };
u8 D_80108CDC[2][4] = { { 1, 2, 3, 4 }, { 1, 2, 3, 4 } };

void (*D_80108CE4[])(struct ShotObj*) = {
    func_80099F48,
    func_8009A10C,
    func_8009A338,
    func_8009A264,
};
