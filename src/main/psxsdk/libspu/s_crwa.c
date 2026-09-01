#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/s_crwa", SpuClearReverbWorkArea);

INCLUDE_RODATA("asm/us/main/nonmatchings/psxsdk/libspu/s_crwa", D_80011534);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/s_crwa", _spu_init);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/s_crwa", _spu_writeByIO);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/s_crwa", _spu_FiDMA);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/s_crwa", _spu_r_);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/s_crwa", _spu_t);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/s_crwa", _spu_write);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/s_crwa", _spu_read);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/s_crwa", _spu_FsetRXX);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/s_crwa", _spu_FsetRXXa);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/s_crwa", _spu_FgetRXXa);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/s_crwa", _spu_FsetPCR);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/s_crwa", _spu_FsetDelayW);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/s_crwa", _spu_FsetDelayR);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/s_crwa", _spu_FwaitFs);
