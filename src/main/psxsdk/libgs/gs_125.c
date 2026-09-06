#include "common.h"

long GetVideoMode(void)
{
    extern s32 D_8011DC80;

    return D_8011DC80;
}

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", StSetRing);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CdInit);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", def_cbsync);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", def_cbready);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", def_cbread);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CdStatus);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CdMode);

extern u8 D_8011DD3D;

int CdLastCom(void)
{
    return D_8011DD3D;
}

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CdLastPos);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CdReset);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CdFlush);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CdSetDebug);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CdComstr);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CdIntstr);

int CD_sync(int mode, u_char* result);

int CdSync(int mode, u_char* result)
{
    return CD_sync(mode, result);
}

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CdReady);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CdSyncCallback);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CdReadyCallback);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CdControl);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CdControlF);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CdControlB);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CdMix);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CdGetSector);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CdDataCallback);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CdDataSync);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CdIntToPos);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CdPosToInt);

INCLUDE_RODATA("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", D_800119C0);

INCLUDE_RODATA("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", D_80011B04);

INCLUDE_RODATA("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", D_80011B14);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", getintr);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CD_sync);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CD_ready);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CD_cw);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CD_vol);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CD_flush);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CD_initvol);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CD_initintr);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CD_init);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CD_datasync);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libgs/gs_125", CD_getsector);
