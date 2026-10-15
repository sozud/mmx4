#include "test_runtime.h"

volatile struct CTestStatus c_test_status;

void c_test_fail(u32 line)
{
    c_test_status.failure_line = line;
    for (;;) { }
}

#if defined(MMX4_PC) && defined(MMX4_COMPACT_OBSERVATIONS)
#include <stdio.h>
#endif

u32 c_test_observe(u32 group, u32 row, const u32* observed, const u32* expected, u32 count)
{
    u32 i;
    for (i = 0; i < count; ++i) {
        assert(observed[i] == expected[i]);
#if defined(MMX4_PC) && defined(MMX4_COMPACT_OBSERVATIONS)
        printf("OBS\t%u\t%u\t%u\t%u\n", group, row, i, observed[i]);
#endif
    }
    return observed[0];
}

void c_test_same_words(const void* actual, const void* expected, u32 size)
{
    u32 word;
    for (word = 0; word < size / 4; ++word)
        assert(((const u32*)actual)[word] == ((const u32*)expected)[word]);
}

u32 c_test_word_difference(const u32* a, const u32* b, u32 count)
{
    u32 difference = 0;
    while (count >= 8) {
        difference |= (a[0] ^ b[0]) | (a[1] ^ b[1]) | (a[2] ^ b[2]) | (a[3] ^ b[3]);
        difference |= (a[4] ^ b[4]) | (a[5] ^ b[5]) | (a[6] ^ b[6]) | (a[7] ^ b[7]);
        a += 8;
        b += 8;
        count -= 8;
    }
    while (count != 0) {
        difference |= *a++ ^ *b++;
        count--;
    }
    return difference;
}

void c_test_copy_words(u32* dest, const u32* src, u32 count)
{
    while (count >= 8) {
        dest[0] = src[0];
        dest[1] = src[1];
        dest[2] = src[2];
        dest[3] = src[3];
        dest[4] = src[4];
        dest[5] = src[5];
        dest[6] = src[6];
        dest[7] = src[7];
        dest += 8;
        src += 8;
        count -= 8;
    }
    while (count != 0) {
        *dest++ = *src++;
        count--;
    }
}

void c_test_zero_words(u32* dest, u32 count)
{
    while (count >= 8) {
        dest[0] = 0;
        dest[1] = 0;
        dest[2] = 0;
        dest[3] = 0;
        dest[4] = 0;
        dest[5] = 0;
        dest[6] = 0;
        dest[7] = 0;
        dest += 8;
        count -= 8;
    }
    while (count != 0) {
        *dest++ = 0;
        count--;
    }
}

u32 c_test_group_run(const struct CTestGroup* group, u32 index)
{
    u32 actual;
    if (!group->cases)
        return group->run(index);
    actual = group->cases[index]();
    return c_test_observe(0, index, &actual, &group->expected[index], 1);
}

#ifndef MMX4_PC
u32 c_test_run(u32 index)
{
    u32 group = 0, local = index;
    c_test_status.magic = 0x43544553;
    c_test_status.case_id = index;
    c_test_status.passed = 0;
    c_test_status.failure_line = 0;
    if (index >= c_test_count)
        c_test_fail(__LINE__);
    while (local >= c_test_groups[group].count)
        local -= c_test_groups[group++].count;
    c_test_status.value = c_test_group_run(&c_test_groups[group], local);
    c_test_status.passed = 1;
    return c_test_status.value;
}
#endif
