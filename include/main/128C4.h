#ifndef MAIN_128C4_H
#define MAIN_128C4_H

struct HudSpriteOrigin {
    s16 x, y;
    u16 clut;
};

struct PlayerGaugePosition {
    s16 x;
    u16 bottom;
};

void func_8002217C(arg_u16, u8, s32);
void func_80022730(struct AbcObj*);

#endif
