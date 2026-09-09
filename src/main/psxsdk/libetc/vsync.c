#include "common.h"

#ifdef VERSION_JP
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

#else
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

#endif
extern volatile s32 D_8011DC50;
extern void func_800EDC74(const char*);
extern void ChangeClearRCnt(long, long);

void v_wait(int v, int timeout)
{
    volatile int t = timeout << 15;
    while (D_8011DC50 < v) {
        if (!t--) {
            func_800EDC74(
                "VSync: timeout\n\0"
                "$Id: intr.c,v 1.74 1996/12/04 07:30:16 makoto Exp $");
            ChangeClearPAD(0);
            ChangeClearRCnt(3, 0);
            return;
        }
    }
}
