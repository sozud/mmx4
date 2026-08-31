#include "common.h"

RECT D_800F2428 = { 0x140, 0xB0, 0x100, 0x50 };
RECT D_800F2430 = { 0x240, 0, 0x100, 0x50 };

void (*D_800F2438[7])(struct EngineObj*) = {
    func_80020580, func_80020638, func_800206D0, func_80020808,
    func_8002088C, func_80020984, func_80020A08,
};

void (*D_800F2454[5])(struct EngineObj*) = {
    func_80020B1C, func_80020B8C, func_80020C24,
    func_80020CB8, func_80020D3C,
};
