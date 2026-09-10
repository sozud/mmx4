#include "common.h"
#include "func_tables.h"

void (*D_800FE8FC[7])() = {
    func_8009216C,
    func_80060E08,
    func_80060E14,
    func_80060F5C,
    func_8006104C,
    func_8006114C,
    func_8006128C,
};
void (*D_800FE918[2])() = { func_80060E50, func_80060E94 };
void (*D_800FE920[2])() = { func_80060F98, func_80060FF8 };
void (*D_800FE928[2])() = { func_80061088, func_800610F0 };
void (*D_800FE930[3])() = { func_80061188, func_800611E0, func_80061240 };
void (*D_800FE93C[2])() = { func_800612C8, func_80061310 };

s8 D_800FE944[4] = { -16, -7, 29, 29 };
s8 D_800FE948[4] = { -12, -5, 22, 26 };
s8 D_800FE94C[4] = { 0, 0, 16, 26 };

union AnimationStep D_800FE950[] = {
    { 0x00010001 },
    { 0x01010001 },
    { 0x02FE0001 },
};
union AnimationStep D_800FE95C[] = {
    { 0x03010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x05000101 },
};
union AnimationStep D_800FE974[] = {
    { 0x07010003 },
    { 0x08010003 },
    { 0x09010003 },
    { 0x0A010003 },
    { 0x0B010003 },
    { 0x0C010003 },
    { 0x0D010003 },
    { 0x06F90003 },
};
union AnimationStep* D_800FE994[4] = {
    D_800FE950,
    D_800FE95C,
    D_800FE974,
    NULL,
};
