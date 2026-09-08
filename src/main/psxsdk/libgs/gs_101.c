#include "common.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_101", CD_set_test_parmnum);

#ifdef VERSION_JP
INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_101", callback);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_101", cb_read);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_101", cd_read_retry);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_101", CdReadBreak);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_101", CdRead);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_101", CdReadSync);

#else
extern u8* D_8011DFE0;
extern u8 D_8011DFF9;
extern void (*D_8011DD1C)(u8, u8*);
extern void (*D_8011DD20)(u8, u8*);
extern u8 D_8013BA78[];
extern u8 D_8013BA80[];

void callback(void)
{
    int intr;
    int temp_s1;
    u8* ready;
    u8* sync;

    temp_s1 = *D_8011DFE0 & 3;
    ready = &D_8011DFF9;
    sync = ready - 1;

    while (intr = getintr()) {
        if (intr & 4 && D_8011DD20 != 0) {
            D_8011DD20(*ready, D_8013BA80);
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

#endif
INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_101", CdReadCallback);
