#include "common.h"
#include "func_tables.h"

void (*D_800FF978[2])(struct MainObj*) = { func_80066580, func_8006692C };
void (*D_800FF980[4])(struct MainObj*) = {
    func_800665BC,
    func_80066804,
    func_80066858,
    func_8006689C,
};
void (*D_800FF990[1])(struct MainObj*) = { func_80066968 };

u8 D_800FF994[4] = { 0xA1, 0x94, 0x2A, 0x23 };
u8 D_800FF998[4] = { 0xA1, 0x9A, 0x24, 0x1C };
char D_800FF99C[8] = "\t\n\t\n\t\n";
