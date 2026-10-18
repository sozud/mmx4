#ifndef MAIN_323C_H
#define MAIN_323C_H

union TitleScratch {
    s32 sector[0x200];
    struct TitlePointState title;
};
union SepBundle {
    s32 offsets[0x1000];
    u8 raw[0x4000];
};

#ifdef MMX4_PC
extern void func_80012E38 (void);
extern void func_80012E80 (void);
extern void func_80012EB0 (void);
#endif

void func_80012E18(u8* arg0, u8* arg1);

void func_80012A3C();

void func_80012EB8();

void func_80013014();

#endif
