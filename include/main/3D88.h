#ifndef MAIN_3D88_H
#define MAIN_3D88_H

struct Unk5 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};

struct CdImageOrigin {
    u16 x, y;
};

typedef unsigned long CdLoadAddress;

// D_800F1640
void func_800148E4(void);
void func_800148EC(void);
void func_80014968(void);

#ifdef MMX4_PC
extern s32 func_80013614 (s32 arg0, s32 *arg1);

extern u8 func_8001385C (void);

extern void func_80013588 ();

extern void func_80014780 (void);
#endif

void func_80013AD8(s32, u8, CdLoadAddress);
void func_80013890(u32, u8*);

extern void func_80013E68(u8 status, u8* result);
void func_80013650(void);
s8 func_800136B0();
void func_800137F0(void);
void MyCdReadyCallback(u8 status, u8* result);

void func_80014C70(void);

#endif
