#include "common.h"

typedef struct
{
    int unk0;
    int unk4;
    void (*unk8)(void);
    int (*unkC)();
} D_800320D4_t;

extern D_800320D4_t* D_8011DC1C;

int ResetCallback(void)
{
    return D_8011DC1C->unkC();
}

void InterruptCallback(void)
{
    D_8011DC1C->unk8();
}

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

void ResetEntryInt(int*);
extern u16 D_8011CB94;
extern u16 D_8011CBC6;
extern s32 D_8011CBC8;
extern u16* D_8011DC20;
extern volatile u16* D_8011DC24;
extern s32* D_8011DC28;

u16* stopIntr(void)
{
    u16* p = &D_8011CB94;
    volatile s32* p2;
    volatile u16* mask;

    if (*p == 0) {
        return 0;
    }
    EnterCriticalSection();
    mask = D_8011DC24;
    D_8011CBC6 = *mask;
    D_8011CBC8 = *D_8011DC28;
    *D_8011DC20 = *mask = 0;
    p2 = D_8011DC28;
    *p2 &= 0x77777777;
    ResetEntryInt(p2);
    *p = 0;
    return p;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", restartIntr);

void memclr(int* ptr, int size)
{
    int i;
    int* e = ptr;

    for (i = size - 1; i != -1; i--) {
        *e = 0;
        e++;
    }
}
