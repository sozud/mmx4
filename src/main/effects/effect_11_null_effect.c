// EffectObj, effect_object_update_funcs[11]
// 800B8064..800B806C
#include "common.h"
#include "main/effects/effect_11_null_effect.h"

#ifdef MMX4_SATURN
#define LINE_SCROLL_CONTROL 0x9A
#define LINE_SCROLL_TABLE_A 0xA0
#define LINE_SCROLL_TABLE_B 0xA4
#define LINE_SCROLL_OFF 0
#define LINE_SCROLL_WAVE_INIT 6
#define LINE_SCROLL_WAVE 0x600
#define LINE_SCROLL_SPLIT 0x402
#define LINE_SCROLL_VERTICAL 0x400
#define LINE_TABLE_A_ADDRESS 0x12F37000
#define LINE_TABLE_B_ADDRESS 0x12F37200
#define LINE_SCROLL_X ((s32*)0x06002000)
#define LINE_SCROLL_Y ((s32*)0x06002400)
#define LINE_SCROLL_VRAM 0x25E6E000
#define LINE_SCROLL_BYTES 0x800
#define LINE_COUNT 0x100
#define LINE_ONE 0x10000
#define WAVE_SURFACE 0x200
#define WAVE_EDGE_X 120
#define WAVE_EDGE_SHIFT 0x20000
#define WAVE_X_SCALE 16
#define WAVE_Y_SCALE 8
#define WAVE_X_PERIOD 16
#define WAVE_Y_PERIOD 32
#define WAVE_DELAY 3

struct LineWave {
    u16 phase_x;
    u16 delay_x;
    u16 phase_y;
    u16 delay_y;
};

extern u16 saturn_vdp2_shadow[];
const u16 null_effect_wave_table[] = {
    0x0,
    0x312,
    0x645,
    0x978,
    0xc8b,
    0xf9d,
    0x12b0,
    0x15c2,
    0x18f5,
    0x1c08,
    0x1ef9,
    0x220c,
    0x251e,
    0x2810,
    0x2b02,
    0x2df3,
    0x30e5,
    0x33d7,
    0x36a7,
    0x3978,
    0x3c49,
    0x3ef9,
    0x41ca,
    0x447a,
    0x470a,
    0x49ba,
    0x4c28,
    0x4eb8,
    0x5126,
    0x5395,
    0x55e3,
    0x5831,
    0x5a7e,
    0x5cac,
    0x5eb8,
    0x60e5,
    0x62f1,
    0x64dd,
    0x66c8,
    0x6893,
    0x6a5e,
    0x6c08,
    0x6db2,
    0x6f5c,
    0x70c4,
    0x724d,
    0x7395,
    0x74fd,
    0x7624,
    0x774b,
    0x7872,
    0x7978,
    0x7a5e,
    0x7b43,
    0x7c28,
    0x7ced,
    0x7d70,
    0x7e14,
    0x7e97,
    0x7ef9,
    0x7f5c,
    0x7f9d,
    0x7fbe,
    0x7fdf,
    0x8000,
};
void saturn_transfer_enqueue(u32 source, u32 destination, u32 byte_length);
void saturn_transfer_profile(u32 add_a, u32 add_b, u32 attribute_index);

#define SHADOW16(offset) (*(u16*)((u8*)saturn_vdp2_shadow + (offset)))
#define SHADOW32(offset) (*(u32*)((u8*)saturn_vdp2_shadow + (offset)))
#define LINE_WAVE(self) ((struct LineWave*)((u8*)(self) + 0x14))

static s32 line_wave(s32 line, u16 phase, u16 scale)
{
    u32 angle = (u32)(phase + line) * scale;
    u32 index = angle & 63;
    s32 value;
    if (angle & 64)
        index = 64 - index;
    value = null_effect_wave_table[index];
    if (angle & 0x80)
        value = -value;
    return value;
}

static void line_wave_init(struct EffectObj* self)
{
    struct LineWave* wave = LINE_WAVE(self);
    wave->phase_x = 0;
    wave->delay_x = WAVE_DELAY;
    wave->phase_y = 0;
    wave->delay_y = WAVE_DELAY;
}

static void line_wave_step_x(struct LineWave* wave)
{
    if (--wave->delay_x == 0) {
        wave->delay_x = WAVE_DELAY;
        if (++wave->phase_x == WAVE_X_PERIOD)
            wave->phase_x = 0;
    }
}

static void line_wave_step_y(struct LineWave* wave)
{
    if (--wave->delay_y == 0) {
        wave->delay_y = WAVE_DELAY;
        if (++wave->phase_y == WAVE_Y_PERIOD)
            wave->phase_y = 0;
    }
}

static s32 line_wave_y(struct LineWave* wave, s32 line, s32 multiplier)
{
    s32 value = (line << 16) + line_wave(line, wave->phase_y, WAVE_Y_SCALE) * multiplier;
    return value < LINE_ONE ? LINE_ONE : value;
}

static void line_wave_commit(void)
{
    saturn_transfer_profile(LINE_COUNT, 1, 0);
    saturn_transfer_enqueue((u32)LINE_SCROLL_X, LINE_SCROLL_VRAM, LINE_SCROLL_BYTES);
}

static void line_wave_surface(struct EffectObj* self)
{
    struct LineWave* wave = LINE_WAVE(self);
    s32* table = LINE_SCROLL_X;
    s32 depth;
    s32 line = 0;
    s32 tail;
    s32 x;
    if (background_objects[0].y_pos.i.hi >= WAVE_SURFACE) {
        SHADOW16(LINE_SCROLL_CONTROL) = LINE_SCROLL_OFF;
        return;
    }
    SHADOW16(LINE_SCROLL_CONTROL) = LINE_SCROLL_WAVE;
    depth = WAVE_SURFACE - background_objects[0].y_pos.i.hi;
    for (; line < depth; line++) {
        x = line_wave(line, wave->phase_x, WAVE_X_SCALE) << 1;
        if (background_objects[0].x_pos.i.hi < WAVE_EDGE_X)
            x += WAVE_EDGE_SHIFT;
        *table++ = x;
        *table++ = line_wave_y(wave, line, 4);
    }
    tail = line << 16;
    while (line < LINE_COUNT - depth) {
        line++;
        *table++ = 0;
        *table++ = tail;
        tail += LINE_ONE;
    }
    line_wave_commit();
    line_wave_step_x(wave);
    line_wave_step_y(wave);
}

static void line_wave_split(struct EffectObj* self)
{
    struct LineWave* wave = LINE_WAVE(self);
    s32 line;
    if (background_objects[2].y_pos.i.hi > WAVE_SURFACE) {
        SHADOW16(LINE_SCROLL_CONTROL) = LINE_SCROLL_OFF;
        return;
    }
    SHADOW16(LINE_SCROLL_CONTROL) = LINE_SCROLL_SPLIT;
    for (line = 0; line < LINE_COUNT; line++) {
        LINE_SCROLL_X[line] = line_wave(line, wave->phase_x, WAVE_X_SCALE) << 1;
        LINE_SCROLL_Y[line] = line_wave_y(wave, line, 3);
    }
    line_wave_commit();
    line_wave_step_x(wave);
    line_wave_step_y(wave);
}

static void line_wave_vertical(struct EffectObj* self)
{
    struct LineWave* wave = LINE_WAVE(self);
    s32 line;
    if (background_objects[2].y_pos.i.hi > WAVE_SURFACE) {
        SHADOW16(LINE_SCROLL_CONTROL) = LINE_SCROLL_OFF;
        return;
    }
    SHADOW16(LINE_SCROLL_CONTROL) = LINE_SCROLL_VERTICAL;
    for (line = 0; line < LINE_COUNT; line++) {
        LINE_SCROLL_X[line] = 0;
        LINE_SCROLL_Y[line] = line_wave_y(wave, line, 3);
    }
    line_wave_commit();
    line_wave_step_y(wave);
}

static void null_effect_surface(struct EffectObj* self)
{
    if (self->state == 0) {
        SHADOW16(LINE_SCROLL_CONTROL) = LINE_SCROLL_WAVE_INIT;
        line_wave_init(self);
        SHADOW32(LINE_SCROLL_TABLE_B) = LINE_TABLE_A_ADDRESS;
        self->state = 1;
    }
    line_wave_surface(self);
}

static void null_effect_split(struct EffectObj* self)
{
    if (self->state == 0) {
        SHADOW16(LINE_SCROLL_CONTROL) = LINE_SCROLL_SPLIT;
        line_wave_init(self);
        SHADOW32(LINE_SCROLL_TABLE_A) = LINE_TABLE_A_ADDRESS;
        SHADOW32(LINE_SCROLL_TABLE_B) = LINE_TABLE_B_ADDRESS;
        self->state = 1;
    }
    line_wave_split(self);
}

static void null_effect_vertical(struct EffectObj* self)
{
    if (self->state == 0) {
        SHADOW16(LINE_SCROLL_CONTROL) = LINE_SCROLL_VERTICAL;
        line_wave_init(self);
        SHADOW32(LINE_SCROLL_TABLE_B) = LINE_TABLE_B_ADDRESS;
        self->state = 1;
    }
    line_wave_vertical(self);
}

static void (*const null_effect_variants[])(struct EffectObj*) = {
    null_effect_surface,
    null_effect_split,
    null_effect_vertical,
};

void null_effect_update(struct EffectObj* self)
{
    null_effect_variants[self->unk2](self);
}
#else
void null_effect_update(struct EffectObj* self)
{
}
#endif
