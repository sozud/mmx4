#include "common.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", ResetCallback);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", InterruptCallback);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", DMACallback);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", VSyncCallback);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", VSyncCallbacks);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", StopCallback);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", RestartCallback);

extern u16 D_8011CB96;

int CheckCallback(void)
{
    return D_8011CB96;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", GetIntrMask);

extern volatile unsigned short* D_8011DC24;

unsigned short SetIntrMask(unsigned short arg0)
{
    unsigned short temp_v0;

    temp_v0 = *D_8011DC24;
    *D_8011DC24 = arg0;
    return temp_v0;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", startIntr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", trapIntr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", setIntr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", stopIntr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", restartIntr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", memclr);
