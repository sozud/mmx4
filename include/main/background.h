#ifndef MAIN_BACKGROUND_H
#define MAIN_BACKGROUND_H

struct BackgroundLayoutConfig {
    u8 object_ids[4];
    u8 layer_ids[3][2];
};

struct BackgroundLayoutConfigData {
    struct BackgroundLayoutConfig records[33];
    u8 alignment_padding[2];
};

void func_80027BE4(struct BackgroundObj*);

void func_8002771C(void);
void func_80027850(void);
void func_80027D40(void);
void func_800281E8(void);

#endif
