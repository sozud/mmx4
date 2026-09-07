#include "common.h"

u8 D_800F9E50[] = { 6, 7, 8, 9, 10, 11, 12, 0 };

void (*D_800F9E58[])(struct MainObj*) = {
    func_80043390,
    func_800435C4,
    func_800436D0,
};

void (*D_800F9E64[])(struct MainObj*) = {
    (void (*)(struct MainObj*))func_8009216C,
    func_80043720,
    func_8004372C,
    func_8004381C,
    func_80043900,
    func_80043A48,
    func_80043CB8,
    func_80043D54,
    func_80043E90,
};
