#ifndef MMX4_PC_BUILD_H
#define MMX4_PC_BUILD_H

struct UnkObj* find_free_unk_obj(void);
s32 func_8002D1F8(struct PlayerObj*, u8, s32);
s32 func_800380F0(struct PlayerObj*, s8);
s32 func_8001E850(u8*, u8);

void _SsNoteOn(s16, s16, u8, u8);
void _SsSetProgramChange(s16, s16, u8);
void _SsSetControlChange(s16, s16, u8);
void _SsContMainVol(s16, s16, u8);
void _SsContRpn1(s16, s16, u8);

#endif
