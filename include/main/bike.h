#ifndef MAIN_BIKE_H
#define MAIN_BIKE_H

void func_8003B3DC(struct RideArmorObj*);

void func_8003B470(struct RideArmorObj*);
void func_8003B7B4(struct RideArmorObj*);

// D_800F90E8
extern void (*D_800F90E8[])(struct RideArmorObj*);
void func_8003BB20(struct RideArmorObj*);

void func_8003BE28(struct RideArmorObj*);
void func_8003CBCC(struct RideArmorObj*);
void func_8003C584(struct RideArmorObj*);
void func_8003BF1C(struct RideArmorObj*);
void func_8003C08C(struct RideArmorObj*);

#ifdef MMX4_PC
extern void func_8003C6EC (struct RideArmorObj *arg0, u8 arg1);

extern void func_8003CB08 (struct RideArmorObj *arg0);
extern void func_8003CCBC (struct RideArmorObj *arg0);
#endif

extern s32 D_800F9090[2];
extern s32 D_800F9098[2];

u8 func_8003CF24(struct RideArmorObj*);

void func_8003C624(struct RideArmorObj*);

void func_8003D254(struct VisualObj*);

#endif
