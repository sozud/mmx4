#include "test_runtime.h"
void func_80012D68(u32*, u32*, s32);

static u32 same_bytes(const void* lhs, const void* rhs, u32 size)
{
    const u8* a = lhs;
    const u8* b = rhs;
    u32 i;
    for (i = 0; i < size; i++)
        if (a[i] != b[i])
            return 0;
    return 1;
}

static u32 copy_words(void)
{
    u32 source[3] = { 0x01234567, 0x89ABCDEF, 0xFEDCBA98 };
    u32 before[3];
    u32 destination[5] = { 0xCAFEBABE, 0, 0, 0, 0xDEADBEEF };
    u32 actual;
    memcpy(before, source, sizeof(before));
    func_80012D68(source, destination + 1, COUNT(source));
    assert(destination[0] == 0xCAFEBABE && destination[4] == 0xDEADBEEF);
    assert(same_bytes(source, before, sizeof(source)));
    actual = same_bytes(destination + 1, source, sizeof(source));
    return actual;
}

static u32 decode_pair(u32 pair)
{
    u16 source[23], before[23], destination[22];
    u32 i;
    source[0] = 0x4000;
    source[1] = 0xABCD;
    source[2] = 0x0801;
    for (i = 2; i < 16; i++)
        source[i + 1] = 0x1000 + i;
    source[17] = 0xE000;
    source[18] = 0x1000;
    source[19] = 1;
    source[20] = 2;
    source[21] = 0;
    source[22] = 0;
    memcpy(before, source, sizeof(before));
    for (i = 0; i < COUNT(destination); i++)
        destination[i] = 0xCCCC;
    destination[0] = 0xBEEF;
    destination[21] = 0xC0DE;
    decompress_gfx(source, destination + 1);
    assert(destination[0] == 0xBEEF && destination[21] == 0xC0DE);
    assert(same_bytes(source, before, sizeof(source)));
    return destination[1 + pair * 2] | ((u32)destination[2 + pair * 2] << 16);
}
#define DECODE_CASE(index)          \
    static u32 decode_##index(void) \
    {                               \
        return decode_pair(index);  \
    }
DECODE_CASE(0)
DECODE_CASE(1)
DECODE_CASE(2)
DECODE_CASE(3)
DECODE_CASE(4)
DECODE_CASE(5)
DECODE_CASE(6)
DECODE_CASE(7)
DECODE_CASE(8)
DECODE_CASE(9)
static const CTestCase buffer_primitives_cases[] = {
    copy_words,
    decode_0,
    decode_1,
    decode_2,
    decode_3,
    decode_4,
    decode_5,
    decode_6,
    decode_7,
    decode_8,
    decode_9,
};
static const u32 buffer_primitives_cases_expected[] = { 0x1u, 0xABCDABCDu, 0x10031002u, 0x10051004u, 0x10071006u, 0x10091008u, 0x100B100Au, 0x100D100Cu, 0x100F100Eu, 0x0u, 0x0u };
#undef DECODE_CASE

const struct CTestGroup c_test_groups[] = {
    { "buffer_primitives", buffer_primitives_cases, buffer_primitives_cases_expected, COUNT(buffer_primitives_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(buffer_primitives_cases);
