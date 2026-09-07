#include "common.h"

extern volatile s32* D_8011CB84;
extern volatile s32* D_8011CB88;
extern volatile s32 D_8011CB8C;
extern volatile s32 D_8011CB90;
extern volatile s32 D_8011DC50;
extern void v_wait(int v, int timeout);

int VSync(int mode)
{
    int syncFlag;
    int elapsed;
    int timeout;
    int v;
    int n;

    syncFlag = *D_8011CB84;
    elapsed = (*D_8011CB88 - D_8011CB8C) & 0xFFFF;
    if (mode < 0) {
        return D_8011DC50;
    }
    if (mode == 1) {
        return elapsed;
    }
    n = 1;
    v = mode > 0 ? D_8011CB90 - n + mode : D_8011CB90;
    timeout = mode > 0 ? mode - n : 0;
    v_wait(v, timeout);
    syncFlag = *D_8011CB84;
    v_wait(D_8011DC50 + 1, 1);
    if (syncFlag & 0x400000 && (syncFlag ^ *D_8011CB84) >= 0) {
        do {
        } while (!((syncFlag ^ *D_8011CB84) & 0x80000000));
    }
    D_8011CB90 = D_8011DC50;
    D_8011CB8C = *D_8011CB88;
    return elapsed;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/vsync", v_wait);
