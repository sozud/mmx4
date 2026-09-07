#include "common.h"

long GetVideoMode(void)
{
    extern s32 D_8011DC80;

    return D_8011DC80;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", StSetRing);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CdInit);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", def_cbsync);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", def_cbready);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", def_cbread);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CdStatus);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CdMode);

extern u8 D_8011DD3D;

int CdLastCom(void)
{
    return D_8011DD3D;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CdLastPos);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CdReset);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CdFlush);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CdSetDebug);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CdComstr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CdIntstr);

int CD_sync(int mode, u_char* result);

int CdSync(int mode, u_char* result)
{
    return CD_sync(mode, result);
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CdReady);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CdSyncCallback);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CdReadyCallback);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CdControl);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CdControlF);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CdControlB);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CdMix);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CdGetSector);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CdDataCallback);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CdDataSync);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CdIntToPos);

int CdPosToInt(CdlLOC* p)
{
    char temp_a1;
    char temp_a2;
    char temp_v1;

    temp_v1 = p->minute;
    temp_a2 = p->second;
    temp_a1 = p->sector;
    return (((((((temp_v1 >> 4) * 0xA) + (temp_v1 & 0xF)) * 0x3C) + (((temp_a2 >> 4) * 0xA) + (temp_a2 & 0xF))) * 0x4B) + (((temp_a1 >> 4) * 0xA) + (temp_a1 & 0xF))) - 0x96;
}

INCLUDE_RODATA("main/nonmatchings/psxsdk/libgs/gs_125", D_800119C0);

INCLUDE_RODATA("main/nonmatchings/psxsdk/libgs/gs_125", D_80011B04);

INCLUDE_RODATA("main/nonmatchings/psxsdk/libgs/gs_125", D_80011B14);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", getintr);

const char D_80011B8C[] = "CD_sync";

typedef struct {
    u8 sync;
    u8 ready;
    u8 c;
} CdlIntr;

extern s32 D_8013BA90;
extern s32 D_8013BA94;
extern u8* D_8011DFE0;
extern u8 D_8013BA78;
extern void CD_flush(void);
extern void func_800EDC74(char*);
extern int printf(char*, char*, s32, s32, s32);
extern char D_80011B04;
extern char D_80011B14;
extern int (*D_8011DD1C)(u8, u8*);
extern int (*D_8011DD20)(u8, u8*);
extern const char* D_8011DD40[];
extern char* D_8011DDC0[];
extern volatile CdlIntr D_8011DFF8;
extern u8 D_8013BA80;
extern char* D_8013BA98[];

int CD_sync(int mode, u_char* result)
{
    s32 i;
    s32 intr;
    s32 sync;
    s32 flushed;
    s32 temp_s1;
    u8* src;
    u8* dst;
    char com, s, r;
    char** name;

    D_8013BA90 = VSync(-1) + 0x3C0;
    D_8013BA94 = 0;
    D_8013BA98[0] = D_80011B8C;

    while (1) {
        if ((D_8013BA90 < VSync(-1)) || D_8013BA94++ > 0x3C0000) {
            func_800EDC74(&D_80011B04);
            printf(&D_80011B14,
                D_8013BA98[0],
                D_8011DD40[D_8011DD3D],
                D_8011DDC0[D_8011DFF8.sync],
                D_8011DDC0[D_8011DFF8.ready]);
            CD_flush();
            flushed = -1;
        } else {
            flushed = 0;
        }

        if (flushed != 0) {
            return -1;
        }

        if (CheckCallback()) {
            temp_s1 = *D_8011DFE0 & 3;

            while (intr = getintr()) {
                if (intr & 4 && D_8011DD20 != 0) {
                    D_8011DD20(D_8011DFF8.ready, &D_8013BA80);
                }
                if (intr & 2 && D_8011DD1C != 0) {
                    D_8011DD1C(D_8011DFF8.sync, &D_8013BA78);
                }
            }
            *D_8011DFE0 = temp_s1;
        }

        sync = D_8011DFF8.sync;
        if (sync == 2 || sync == 5) {
            D_8011DFF8.sync = 2;
            dst = result;
            src = &D_8013BA78;
            if (dst != 0) {
                for (i = 7; i != -1; i--) {
                    *dst++ = *src++;
                }
            }
            return sync;
        }

        if (mode != 0) {
            break;
        }
    }
    return 0;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CD_ready);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CD_cw);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CD_vol);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CD_flush);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CD_initvol);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CD_initintr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CD_init);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CD_datasync);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgs/gs_125", CD_getsector);
