#include "common.h"

extern void MDEC_reset(s32 mode);

void DecDCTReset(s32 mode)
{
    if (mode == 0) {
        ResetCallback();
    }
    MDEC_reset(mode);
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libpress/libpress", DecDCTGetEnv);

INCLUDE_ASM("main/nonmatchings/psxsdk/libpress/libpress", DecDCTPutEnv);

INCLUDE_ASM("main/nonmatchings/psxsdk/libpress/libpress", DecDCTBufSize);

extern void MDEC_in(int* arg0, unsigned int arg1);

void DecDCTin(u_long* buf, int mode)
{
    if (mode & 1) {
        *buf &= 0xF7FFFFFF;
    } else {
        *buf |= 0x08000000;
    }
    if (mode & 2) {
        *buf |= 0x02000000;
    } else {
        *buf &= 0xFDFFFFFF;
    }
    MDEC_in((int*)buf, (u16)*buf);
}

extern void MDEC_out(u_long* buf, int size);

void DecDCTout(u_long* buf, int size)
{
    MDEC_out(buf, size);
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libpress/libpress", DecDCTinSync);

INCLUDE_ASM("main/nonmatchings/psxsdk/libpress/libpress", DecDCToutSync);

INCLUDE_ASM("main/nonmatchings/psxsdk/libpress/libpress", DecDCTinCallback);

int DecDCToutCallback(void (*func)())
{
    return DMACallback(1, func);
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libpress/libpress", MDEC_reset);

INCLUDE_ASM("main/nonmatchings/psxsdk/libpress/libpress", MDEC_in);

INCLUDE_ASM("main/nonmatchings/psxsdk/libpress/libpress", MDEC_out);

INCLUDE_ASM("main/nonmatchings/psxsdk/libpress/libpress", MDEC_in_sync);

INCLUDE_ASM("main/nonmatchings/psxsdk/libpress/libpress", MDEC_out_sync);

INCLUDE_ASM("main/nonmatchings/psxsdk/libpress/libpress", MDEC_status);

INCLUDE_ASM("main/nonmatchings/psxsdk/libpress/libpress", timeout);
