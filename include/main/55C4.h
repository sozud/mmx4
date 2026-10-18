#ifndef MAIN_55C4_H
#define MAIN_55C4_H

enum XaArchive {
#ifdef VERSION_JP
    XA_ARCHIVE_BGM1 = 0x94,
#elif defined(VERSION_EU)
    XA_ARCHIVE_BGM1 = 0x97,
#else
    XA_ARCHIVE_BGM1 = 0x95,
#endif
    XA_ARCHIVE_BGM2,
    XA_ARCHIVE_BGM3,
    XA_ARCHIVE_BGM4,
    XA_ARCHIVE_BGM5,
    XA_ARCHIVE_BOSS_INTRO,
    XA_ARCHIVE_VOICE1,
    XA_ARCHIVE_VOICE2,
    XA_ARCHIVE_VOICE3,
    XA_ARCHIVE_VOICE4,
    XA_ARCHIVE_VOICE5,
};

union MainPaletteData {
    u8 raw[0x200];
    struct {
        u8 preceding_palettes[0xA0];
        u16 dialogue_palette[0x20];
        u8 trailing_palettes[0x120];
    };
};

enum SelectedPlayer {
    CHARACTER_X,
    CHARACTER_ZERO
};

void func_80016B38(void);
void func_80016B58(void);
void func_80016BDC(void);
void func_80016C5C(void);
void func_80016D0C(void);
void func_80016DAC(void);
void func_80016E34(void);
void func_80016E84(void);
void func_80016FB4(s32);

#ifdef MMX4_PC
extern s32 func_800169D8 (void);

extern void clear_vram_rect_ptrs (void);
extern void decompress_gfx (u16 *src, u16 *dest);

extern void func_80014DC4 (void);
extern void func_8001512C (void);
extern void func_80015C10 (void);
extern void func_80016074 (void);

extern void func_80016420 (arg_u8 arg0);

extern void func_800164D8 (void);
extern void func_800168D8 (void);

extern void func_800170E0 (void);
extern void func_80017340(void);

extern void load_palette (void);
extern void load_vram_rect_ptrs (void);
#endif

extern s8 D_80141F4A;

s32 func_8001540C(s32, arg_u8, void*);
s32 is_sound_finished(s32, struct MainObj*);

void func_80015284(void);

s32 set_animation(void*, s32);
void set_animation_frame(struct AnimatedObj*, s32, s32);
void animate_object(struct AnimatedObj*);

void func_8001653C(void);

void stop_sound(u8, u8);
void func_80016F0C();

void func_80016334(void);

void func_8001663C(u8, u8);
void func_800175AC(u8);

void func_80018000(arg_u8);

void decompress_player_gfx(struct GraphicsObj* arg0, s16 x, s16 y);

void func_800160AC(void);
void func_800160F4(void);

#endif
