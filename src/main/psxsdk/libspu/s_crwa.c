#include "common.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libspu/s_crwa", SpuClearReverbWorkArea);

INCLUDE_RODATA("main/nonmatchings/psxsdk/libspu/s_crwa", D_80011534);

INCLUDE_ASM("main/nonmatchings/psxsdk/libspu/s_crwa", _spu_init);

INCLUDE_ASM("main/nonmatchings/psxsdk/libspu/s_crwa", _spu_writeByIO);

INCLUDE_ASM("main/nonmatchings/psxsdk/libspu/s_crwa", _spu_FiDMA);

INCLUDE_ASM("main/nonmatchings/psxsdk/libspu/s_crwa", _spu_r_);

INCLUDE_ASM("main/nonmatchings/psxsdk/libspu/s_crwa", _spu_t);

INCLUDE_ASM("main/nonmatchings/psxsdk/libspu/s_crwa", _spu_write);

INCLUDE_ASM("main/nonmatchings/psxsdk/libspu/s_crwa", _spu_read);

INCLUDE_ASM("main/nonmatchings/psxsdk/libspu/s_crwa", _spu_FsetRXX);

extern s32 D_8011C12C;
extern s32 D_8011C150;
extern s32 D_8011C154;
extern u32 D_8011C158;
extern s32 D_8011C15C;

u32 _spu_FsetRXXa(s32 arg0, u32 arg1)
{
    u32 temp_a3;

    if ((D_8011C150 != 0) && ((arg1 % (u32)D_8011C158) != 0)) {
        arg1 += D_8011C158;
        arg1 &= ~D_8011C15C;
    }

    temp_a3 = arg1 >> D_8011C154;
    switch (arg0) {
    case -1:
        return temp_a3 & 0xFFFF;
    case -2:
        return arg1;
    default:
        ((s16*)D_8011C12C)[arg0] = (s16)temp_a3;
    }

    return arg1;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libspu/s_crwa", _spu_FgetRXXa);

INCLUDE_ASM("main/nonmatchings/psxsdk/libspu/s_crwa", _spu_FsetPCR);

extern s32* D_8011C140;

void _spu_FsetDelayW(void)
{
    volatile s32* spu = D_8011C140;

    *spu = (*spu & 0xF0FFFFFF) | 0x20000000;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libspu/s_crwa", _spu_FsetDelayR);

void _spu_FwaitFs(void)
{
    volatile s32 counter;
    volatile s32 value;

    value = 13;
    for (counter = 0; counter < 240; counter++) {
        value *= 3;
    }
}
