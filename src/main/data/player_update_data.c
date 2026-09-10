#include "common.h"
#include "func_tables.h"

void (*D_800F9988[13])(struct MainObj*) = {
    func_80040810,
    func_80040DF8,
    func_80041020,
    func_80041384,
    func_80041524,
    func_80041958,
    func_800419B8,
    func_80041C94,
    func_80041DF0,
    func_80041F88,
    func_8004205C,
    func_800420E8,
    func_80040CCC,
};

u16 D_800F99BC[4] = { 0x6A0, 0x8A0, 0xAA0, 0 };
