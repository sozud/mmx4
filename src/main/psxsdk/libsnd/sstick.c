#include "common.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/sstick", SsSetTickMode);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/sstick", _SsSndSetVol);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/sstick", SsSeqSetVol);

void _SsVmSetSeqVol(s16, s32, s32, s16);

void SsSepSetVol(s16 sep_access_num, s16 seq_num, s16 voll, s16 volr)
{
    _SsVmSetSeqVol(sep_access_num | (seq_num << 8), voll & 0xFFFF, volr & 0xFFFF, 1);
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/sstick", SsSeqGetVol);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/sstick", _SsSndTempo);
