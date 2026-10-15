#include "test_runtime.h"
void func_80012D88(const u32* src, u32* dst, u32 count);
void func_80012DC0(const u32* src, u32* dst, u32 count);

#define COPY_CASE(name, function, words)                               \
    static u32 name(void)                                              \
    {                                                                  \
        u32 source[18], destination[18];                               \
        u32 i, actual;                                                 \
        source[0] = 0xABCD1234u;                                       \
        source[17] = 0x5678CDEFu;                                      \
        for (i = 1; i < 17; i++)                                       \
            source[i] = 0x81234500u + i;                               \
        for (i = 0; i < COUNT(destination); i++)                       \
            destination[i] = 0xDEADBEEFu;                              \
        function(&source[1], &destination[1], 2);                      \
        actual = destination[1];                                       \
        for (i = 1; i <= words; i++)                                   \
            assert(destination[i] == source[i]);                       \
        assert(destination[0] == 0xDEADBEEFu);                         \
        for (i = words + 1; i < COUNT(destination); i++)               \
            assert(destination[i] == 0xDEADBEEFu);                     \
        assert(source[0] == 0xABCD1234u && source[17] == 0x5678CDEFu); \
        for (i = 1; i < 17; i++)                                       \
            assert(source[i] == 0x81234500u + i);                      \
        return actual;                                                 \
    }
COPY_CASE(copy_16_byte_blocks, func_80012D88, 8)
COPY_CASE(copy_32_byte_blocks, func_80012DC0, 16)

#define OVERLAP_CASE(name, function, width)                                          \
    static u32 name(void)                                                            \
    {                                                                                \
        u32 buffer[18];                                                              \
        u32 i, actual;                                                               \
        for (i = 0; i < COUNT(buffer); i++)                                          \
            buffer[i] = 0x12340000u + i;                                             \
        function(buffer, &buffer[1], 2);                                             \
        actual = buffer[width + 1];                                                  \
        assert(buffer[0] == 0x12340000u);                                            \
        for (i = 1; i <= width * 2; i++)                                             \
            assert(buffer[i] == 0x12340000u + (i == width + 1 ? width - 1 : i - 1)); \
        for (i = width * 2 + 1; i < COUNT(buffer); i++)                              \
            assert(buffer[i] == 0x12340000u + i);                                    \
        return actual;                                                               \
    }
OVERLAP_CASE(overlap_16_byte_blocks, func_80012D88, 4)
OVERLAP_CASE(overlap_32_byte_blocks, func_80012DC0, 8)
static const CTestCase block_copy_primitives_cases[] = {
    copy_16_byte_blocks,
    copy_32_byte_blocks,
    overlap_16_byte_blocks,
    overlap_32_byte_blocks,
};
static const u32 block_copy_primitives_cases_expected[] = { 0x81234501u, 0x81234501u, 0x12340003u, 0x12340007u };
#undef COPY_CASE
#undef OVERLAP_CASE

const struct CTestGroup c_test_groups[] = {
    { "block_copy_primitives", block_copy_primitives_cases, block_copy_primitives_cases_expected, COUNT(block_copy_primitives_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(block_copy_primitives_cases);
