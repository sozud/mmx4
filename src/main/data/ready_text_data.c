#include "common.h"

u8 D_800F2C58[] = {
    0x0A, 0x0B, 0xFF, 0x09, 0x00, 0x01, 0x03, 0x04, 0x93, 0x09, 0x01, 0x00,
    0x03, 0x03, 0xFF, 0x09, 0x01, 0x01, 0x01, 0x02, 0x93, 0x01, 0x01, 0x00,
    0x01, 0x02, 0x93, 0x06, 0x01, 0x00, 0x06, 0x07, 0x94, 0x06, 0x00, 0x00,
    0x02, 0x03, 0x95, 0x09, 0x01, 0x00, 0x02, 0x06, 0x96, 0x08, 0x01, 0x00,
    0x02, 0x03, 0x95, 0x07, 0x01, 0x00, 0x09, 0x0A, 0xFF, 0x08, 0x00, 0x01,
};

u8 x_ready_text_flags[] = {
    0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1,
    1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
    0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0,
    0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0,
    0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0,
};

static struct MiscUnk50_1* x_ready_text[] = {
    (struct MiscUnk50_1*)(x_ready_text_flags + 0x00),
    (struct MiscUnk50_1*)(x_ready_text_flags + 0x04),
    (struct MiscUnk50_1*)(x_ready_text_flags + 0x1C),
    (struct MiscUnk50_1*)(x_ready_text_flags + 0x20),
    (struct MiscUnk50_1*)(x_ready_text_flags + 0x24),
    (struct MiscUnk50_1*)(x_ready_text_flags + 0x30),
    (struct MiscUnk50_1*)(x_ready_text_flags + 0x40),
    (struct MiscUnk50_1*)(x_ready_text_flags + 0x48),
    (struct MiscUnk50_1*)(x_ready_text_flags + 0x50),
    (struct MiscUnk50_1*)(x_ready_text_flags + 0x58),
};

u8 D_800F2D18[] = {
    0x0A, 0x0B, 0xFF, 0x09, 0x00, 0x01, 0x09, 0x0A, 0x98, 0x08, 0x00, 0x00,
    0x09, 0x0A, 0xFF, 0x08, 0x00, 0x01, 0x03, 0x04, 0x93, 0x09, 0x01, 0x00,
    0x03, 0x04, 0xFF, 0x09, 0x01, 0x01, 0x01, 0x02, 0x93, 0x06, 0x01, 0x00,
    0x02, 0x03, 0x95, 0x09, 0x01, 0x00, 0x02, 0x06, 0x96, 0x08, 0x01, 0x00,
    0x02, 0x03, 0x95, 0x07, 0x01, 0x00, 0x09, 0x0A, 0xFF, 0x08, 0x00, 0x01,
};

static u8 zero_ready_text_flags[] = {
    0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1,
    1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
    0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0,
    1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0,
    0, 0, 0, 0,
};

static struct MiscUnk50_1* zero_ready_text[] = {
    (struct MiscUnk50_1*)(zero_ready_text_flags + 0x00),
    (struct MiscUnk50_1*)(zero_ready_text_flags + 0x04),
    (struct MiscUnk50_1*)(zero_ready_text_flags + 0x0C),
    (struct MiscUnk50_1*)(zero_ready_text_flags + 0x10),
    (struct MiscUnk50_1*)(zero_ready_text_flags + 0x28),
    (struct MiscUnk50_1*)(zero_ready_text_flags + 0x2C),
    (struct MiscUnk50_1*)(zero_ready_text_flags + 0x38),
    (struct MiscUnk50_1*)(zero_ready_text_flags + 0x40),
    (struct MiscUnk50_1*)(zero_ready_text_flags + 0x48),
    (struct MiscUnk50_1*)(zero_ready_text_flags + 0x50),
};

const u8* D_800F2DD0[] = { D_800F2C58, D_800F2D18 };
struct MiscUnk50_1* const* D_800F2DD8[] = {
    x_ready_text, zero_ready_text,
};

static u32 anim_91_0[] = { 0x00000101 };
static u32 anim_91_1[] = { 0x00010007, 0x04010006, 0x04000101 };
static u32 anim_91_2[] = { 0x01000101 };
static u32 anim_91_3[] = { 0x01010007, 0x05010006, 0x05000101 };
static u32 anim_91_4[] = { 0x02000101 };
static u32 anim_91_5[] = { 0x02010007, 0x06010006, 0x06000101 };
static u32 anim_91_6[] = { 0x03000101 };
static u32 anim_91_7[] = { 0x03010007, 0x07010006, 0x07000101 };
static const u32* animation_91[] = {
    anim_91_0, anim_91_1, anim_91_2, anim_91_3,
    anim_91_4, anim_91_5, anim_91_6, anim_91_7,
};

static u32 anim_92_0[] = { 0x00000101 };
static u32 anim_92_1[] = { 0x01010007, 0x02010006, 0x02000101 };
static const u32* animation_92[] = { anim_92_0, anim_92_1 };

static u32 anim_93_0[] = { 0x00000101 };
static u32 anim_93_1[] = { 0x01010007, 0x02010006, 0x02000101 };
static const u32* animation_93[] = { anim_93_0, anim_93_1 };

static u32 anim_94_0[] = { 0x00000101 };
static u32 anim_94_1[] = { 0x00010007, 0x01010006, 0x01000101 };
static const u32* animation_94[] = { anim_94_0, anim_94_1 };

static u32 anim_95_0[] = { 0x00000101 };
static u32 anim_95_1[] = { 0x00010007, 0x01010006, 0x01000101 };
static const u32* animation_95[] = { anim_95_0, anim_95_1 };

static u32 anim_96_0[] = { 0x00000101 };
static u32 anim_96_1[] = { 0x00010007, 0x01010006, 0x01000101 };
static const u32* animation_96[] = { anim_96_0, anim_96_1 };

static u32 anim_97_0[] = {
    0x00010003, 0x01010003, 0x02010003, 0x03010003, 0x04FC0003,
};
static const u32* animation_97[] = { anim_97_0 };

static u32 anim_98_0[] = { 0x00000101 };
static u32 anim_98_1[] = { 0x00010007, 0x01010006, 0x01000101 };
static const u32* animation_98[] = { anim_98_0, anim_98_1 };

const u32* const* D_800F2EE8[] = {
    animation_91, animation_92, animation_93,
    animation_94, animation_95, animation_96,
};
const u32* const* D_800F2F00[] = { animation_97, animation_98 };

#ifdef MMX4_PC
const u32* const* ready_text_animation(u8 id)
{
    if (id < 0x91 || id > 0x98)
        abort();
    if (id < 0x97)
        return D_800F2EE8[id - 0x91];
    return D_800F2F00[id - 0x97];
}
#endif
