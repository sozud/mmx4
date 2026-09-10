#include "common.h"

#ifndef VERSION_JP
u8 D_800F9E50[] = { 6, 7, 8, 9, 10, 11, 12, 0 };
#endif

void (*D_800F9E58[])(struct MainObj*) = {
    func_80043390,
    func_800435C4,
    func_800436D0,
};
