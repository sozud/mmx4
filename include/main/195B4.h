#ifndef MAIN_195B4_H
#define MAIN_195B4_H

struct StageObjectMarginData {
    u16 margins[5];
    u16 alignment_padding;
};

extern const u8* s_StageMainIds[13][2];

void func_80028FEC(s16, s16, s16, s16, u8);

void func_800292D0(struct StageObjectRecord*);
struct ObjectHeader* MakeObject(u8);

void func_80028DB4(void);
void func_80028F58(void);

#endif
