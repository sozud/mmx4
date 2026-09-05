#ifndef MMX4_PC_BUILD_H
#define MMX4_PC_BUILD_H

struct UnkObj* find_free_unk_obj(void);
void func_80012024(void);
void update_misc_objects(void);
s32 func_8002D1F8(struct PlayerObj*, u8, s32);
s32 func_800380F0(struct PlayerObj*, s8);
s32 func_8001E850(u8*, u8);

void _SsNoteOn(s16, s16, u8, u8);
void _SsSetProgramChange(s16, s16, u8);
void _SsSetControlChange(s16, s16, u8);
void _SsContMainVol(s16, s16, u8);
void _SsContRpn1(s16, s16, u8);

void mmx4_pc_input_update(u8* pad_buffer);
unsigned long mmx4_pc_frame_number(void);
void mmx4_pc_threads_init(void);
struct GameThread* mmx4_pc_thread_slot(s32 slot);
void mmx4_pc_thread_create(s32 slot, void (*entry)(void));
void mmx4_pc_thread_run(s32 slot);
void mmx4_pc_thread_yield(void);
void mmx4_pc_thread_close(void);
void mmx4_pc_thread_replace(void (*entry)(void));

extern DR_MODE D_80139250[2];
extern SPRT D_80139268[2][17];

#endif
