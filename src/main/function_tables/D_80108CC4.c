#include "common.h"

void (*D_80108CB8[])(struct ShotObj*) = { func_80099D10 };
u8 D_80108CBC[4] = { 0xFC, 0xFC, 7, 8 };
s8 D_80108CC0[2][2] = { { -0x12, -2 }, { 0x12, -2 } };

void (*D_80108CC4[])(struct ShotObj*) = {
    func_80099D54,
    func_80099E34,
    func_80099F28,
};
