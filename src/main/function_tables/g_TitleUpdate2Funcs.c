#include "common.h"

void TitleSetWhiteQuadSpeed(struct QuadObj*);

void (*g_TitleUpdate2Funcs[])(struct QuadObj*) = {
    func_800D6F94, func_800D7058, func_800D76D8, func_800D7100,
    TitleSetWhiteQuadSpeed, func_800D7194, func_800D7468,
};
