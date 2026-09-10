#include "common.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_101", CD_set_test_parmnum);

extern u8* D_8011DFE0;
extern u8 D_8011DFF8[];
extern void (*D_8011DD1C)(u8, u8*);
extern void (*D_8011DD20)(u8, u8*);
extern u8 D_8013BA78[];
#ifdef VERSION_JP
extern u8 D_8013BB60_jp[];
#define D_8013BA80_VERSION D_8013BB60_jp
#else
extern u8 D_8013BA80[];
#define D_8013BA80_VERSION D_8013BA80
#endif

void callback(void)
{
    int intr;
    int temp_s1;
    u8* ready;
    u8* sync;

    temp_s1 = *D_8011DFE0 & 3;
    ready = &D_8011DFF8[1];
    sync = ready - 1;

    while (intr = getintr()) {
        if (intr & 4 && D_8011DD20 != 0) {
            D_8011DD20(*ready, D_8013BA80_VERSION);
        }
        if (intr & 2 && D_8011DD1C != 0) {
            D_8011DD1C(*sync, D_8013BA78);
        }
    }
    *D_8011DFE0 = temp_s1;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_101", cb_read);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_101", cd_read_retry);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_101", CdReadBreak);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_101", CdRead);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_101", CdReadSync);
CdlCB CdReadCallback(CdlCB func)
{
    extern s32 D_8011E028;
    CdlCB previous;

    previous = (CdlCB)D_8011E028;
    D_8011E028 = (s32)func;
    return previous;
}
