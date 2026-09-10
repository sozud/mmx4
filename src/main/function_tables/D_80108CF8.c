#include "common.h"

u8 D_80108CF4[4] = { 0x8C, 0xB8, 0x96, 0x87 };

void (*D_80108CF8[])(struct ShotObj*) = {
    func_8009A448,
    func_8009A4F4,
    func_8009A598,
};
