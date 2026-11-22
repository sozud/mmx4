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

void func_8002217C(arg_u16, arg_u8, arg_u8);
#ifdef VERSION_DEMO
void demo_start_dialogue(arg_u16 message, arg_u8 portrait);
#define DEMO_START_DIALOGUE(message, portrait) \
    do {                                       \
        demo_start_dialogue(message, portrait); \
    } while (0)
#endif
void func_80022730(struct AbcObj*);

#endif
