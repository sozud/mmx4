#include "common.h"
#include "gc/collection.h"
#include "gc/dolphin.h"

typedef void (*GcConverter)(void* src, void* dst, u32 size);

extern GcConverter gc_converters[];

static u8* gc_convert_buffer;
static u8 gc_endian_copy_buffer[0x800];

void gc_init_convert_buffer(void)
{
    gc_convert_buffer = gc_get_convert_buffer();
}

void gc_convert_entry(u8* src, u8* dst, u32 kind, u32 size)
{
    gc_converters[kind](src, gc_convert_buffer, size);
    gc_memcpy(dst, gc_convert_buffer, size);
}

#define SWAP16(x) ((u16)((((x)&0xFF) << 8) | (((x) >> 8) & 0xFF)))
#define MAX_PATTERNS 50

#define CONVERT_PATTERN(s, d)                               \
    {                                                       \
        u16 count = SWAP16(((u16*)(s))[1]);                 \
        u32 end = count;                                    \
        u16 j;                                              \
                                                            \
        for (j = 0; j < end; j++) {                         \
            if (j >= count) {                               \
                ((u16*)(d))[0] = ((u16*)(s))[0];            \
                ((u16*)(d))[1] = ((u16*)(s))[1];            \
            } else {                                        \
                __sthbrx(((u16*)(s))[0], (u16*)(d), 0);     \
                __sthbrx(((u16*)(s))[1], (u16*)(d) + 1, 0); \
                end += ((u16*)(d))[0];                      \
            }                                               \
            (d) += 4;                                       \
            (s) += 4;                                       \
        }                                                   \
    }

#line 135
void convPatData(u8* src, u8* dst, u32 size)
{
    u32 offsets[MAX_PATTERNS];
    u8* s = src;
    u8* d = dst;
    u32 n = 0;
    u16 i = 0;
    u16 k;

    while (SWAP16(((u16*)s)[1]) == 0) {
        __stwbrx(*(u32*)s, d, 0);
        n++;
        offsets[i++] = *(u32*)d;
        s += 4;
        d += 4;
    }
    if (n > MAX_PATTERNS) {
        OSPanic(__FILE__, __LINE__, "fatal error in convPatData\n");
    }
    if (n == 0) {
        CONVERT_PATTERN(s, d);
    } else {
        for (k = 0; k < n; k++) {
            u8* ps = src + offsets[k];
            u8* pd = dst + offsets[k];

            CONVERT_PATTERN(ps, pd);
        }
    }
}

void gc_conv_swap16_kind00(u16* src, u16* dst, u32 size)
{
    u32 n;

    for (n = size / 2; n != 0; n--) {
        __sthbrx(*src++, dst++, 0);
    }
}

void gc_conv_swap32(u32* src, u32* dst, u32 size)
{
    u32 n;

    for (n = size / 4; n != 0; n--) {
        __stwbrx(*src++, dst++, 0);
    }
}

void gc_conv_swap32_kind0C(u32* src, u32* dst, u32 size)
{
    u32 n;

    for (n = size / 4; n != 0; n--) {
        __stwbrx(*src++, dst++, 0);
    }
}

void gc_conv_swap16_kind15(u16* src, u16* dst, u32 size)
{
    u32 n;

    for (n = size / 2; n != 0; n--) {
        __sthbrx(*src++, dst++, 0);
    }
}

void gc_conv_kind02(u8* src, u8* dst, u32 size)
{
    u32* s32 = (u32*)src;
    u32* d32 = (u32*)dst;
    u16* s16 = (u16*)src;
    u16* d16 = (u16*)gc_endian_copy_buffer;
    u32 n;

    for (n = size / 4; n != 0; n--) {
        __stwbrx(*s32++, d32++, 0);
    }
    for (n = size / 2; n != 0; n--) {
        __sthbrx(*s16++, d16++, 0);
    }
}

void* gc_get_endian_copy_buffer(void)
{
    return gc_endian_copy_buffer;
}

void gc_conv_swap16_kind14(u16* src, u16* dst, u32 size)
{
    u32 n;

    for (n = size / 2; n != 0; n--) {
        __sthbrx(*src++, dst++, 0);
    }
}

void gc_conv_swap16(u16* src, u16* dst, u32 size)
{
    u32 n;

    for (n = size / 2; n != 0; n--) {
        __sthbrx(*src++, dst++, 0);
    }
}

void gc_conv_copy(void* src, void* dst, u32 size)
{
    gc_memcpy(dst, src, size);
}
