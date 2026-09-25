#include "common.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/ext", LoadTPage);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/ext", LoadClut);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/ext", LoadClut2);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/ext", SetDefDrawEnv);

DISPENV* SetDefDispEnv(DISPENV* env, s32 x, s32 y, s32 w, s32 h)
{
    env->disp.x = (s16)x;
    env->disp.y = (s16)y;
    env->disp.w = (s16)w;
    env->disp.h = (s16)h;
    env->screen.x = 0;
    env->screen.y = 0;
    env->screen.w = 0;
    env->screen.h = 0;
    env->isrgb24 = 0;
    env->isinter = 0;
    env->pad1 = 0;
    env->pad0 = 0;

    return env;
}
