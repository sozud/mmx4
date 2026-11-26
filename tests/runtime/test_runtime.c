#include "test_runtime.h"

#ifdef MMX4_SATURN_TESTS
extern volatile u32 c_test_mismatch[6];
#else
volatile struct CTestStatus c_test_status;
#ifdef MMX4_SATURN
volatile u32 c_test_mismatch[6];
#endif
#ifdef MMX4_C_TEST_RECORD
volatile u32 c_test_log_count;
volatile u32 c_test_log[1024];

void c_test_note(u32 site, u32 value)
{
    if (c_test_log_count + 2 <= COUNT(c_test_log)) {
        c_test_log[c_test_log_count++] = site;
        c_test_log[c_test_log_count++] = value;
    }
}
#endif

void c_test_fail(u32 line)
{
    c_test_status.failure_line = line;
    for (;;) { }
}
#endif

#ifdef MMX4_PC
#include <stdio.h>
#include <unistd.h>

void c_test_skip(void)
{
    fflush(stdout);
    _exit(77);
}
#else
void c_test_skip(void)
{
    c_test_status.failure_line = 0xFFFFFFFF;
    for (;;) { }
}
#endif

u32 c_test_observe(u32 group, u32 row, const u32* observed, const u32* expected, u32 count)
{
    u32 i;
    for (i = 0; i < count; ++i) {
#ifdef MMX4_C_TEST_RECORD
        c_test_note(0xFE000000u | group << 16 | (row & 0xFF) << 8 | (i & 0xFF), observed[i]);
#endif
#ifdef MMX4_PC
        if (observed[i] != expected[i])
            fprintf(stderr, "observation mismatch: group=%u row=%u index=%u expected=0x%08X actual=0x%08X\n",
                group, row, i, expected[i], observed[i]);
#endif
#ifdef MMX4_SATURN
        if (observed[i] != expected[i]) {
            c_test_mismatch[0] = group;
            c_test_mismatch[1] = row;
            c_test_mismatch[2] = i;
            c_test_mismatch[3] = expected[i];
            c_test_mismatch[4] = observed[i];
        }
#endif
        assert(observed[i] == expected[i]);
#if defined(MMX4_PC) && defined(MMX4_COMPACT_OBSERVATIONS)
        printf("OBS\t%u\t%u\t%u\t%u\n", group, row, i, observed[i]);
#endif
    }
    return observed[0];
}

#ifdef MMX4_SATURN_TESTS
void c_test_fail_at(u32 pc, u32 line);
#endif
#ifdef MMX4_SATURN
static u32 load_word(const void* base, u32 word)
{
    const u8* p = (const u8*)base + word * 4;
    return (u32)p[0] << 24 | (u32)p[1] << 16 | (u32)p[2] << 8 | p[3];
}
#define LOAD_WORD(base, word) load_word(base, word)
#else
#define LOAD_WORD(base, word) (((const u32*)(base))[word])
#endif

void c_test_same_words(const void* actual, const void* expected, u32 size)
{
    u32 word;
#ifdef MMX4_C_TEST_RECORD
    for (word = 0; word < size / 4; ++word)
        if (LOAD_WORD(actual, word) != LOAD_WORD(expected, word))
            break;
    c_test_note(0xFD000000u | (word & 0xFFFFFF), word < size / 4 ? LOAD_WORD(actual, word) : 0xC0FFEEu);
    return;
#endif
    for (word = 0; word < size / 4; ++word) {
#ifdef MMX4_SATURN_TESTS
        if (LOAD_WORD(actual, word) != LOAD_WORD(expected, word)) {
            c_test_mismatch[2] = word * 4;
            c_test_mismatch[3] = LOAD_WORD(expected, word);
            c_test_mismatch[4] = LOAD_WORD(actual, word);
            c_test_fail_at((u32)__builtin_return_address(0), 0x8000 | (word * 4));
        }
#endif
#if defined(MMX4_SATURN) && !defined(MMX4_SATURN_TESTS)
        if (LOAD_WORD(actual, word) != LOAD_WORD(expected, word)) {
            c_test_mismatch[0] = 0xFFFFFFFF;
            c_test_mismatch[1] = (u32)actual;
            c_test_mismatch[2] = word * 4;
            c_test_mismatch[3] = LOAD_WORD(expected, word);
            c_test_mismatch[4] = LOAD_WORD(actual, word);
            c_test_mismatch[5] = (u32)expected;
        }
#endif
        assert(LOAD_WORD(actual, word) == LOAD_WORD(expected, word));
    }
}

u32 c_test_word_difference(const u32* a, const u32* b, u32 count)
{
    u32 difference = 0;
#if defined(MMX4_SATURN) && !defined(MMX4_SATURN_TESTS)
    u32 word;
    for (word = 0; word < count; word++) {
        if (a[word] != b[word]) {
            c_test_mismatch[0] = 0xFFFFFFFF;
            c_test_mismatch[1] = (u32)a;
            c_test_mismatch[2] = word * 4;
            c_test_mismatch[3] = b[word];
            c_test_mismatch[4] = a[word];
            c_test_mismatch[5] = (u32)b;
            break;
        }
    }
#endif
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
    if (!group->cases && !group->expected)
        return group->run(index);
    actual = group->cases ? group->cases[index]() : group->run(index);
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
    while (local >= c_test_groups[group].count) {
        local -= c_test_groups[group++].count;
        if (group >= c_test_group_count)
            c_test_fail(__LINE__);
    }
    c_test_status.value = c_test_group_run(&c_test_groups[group], local);
    c_test_status.passed = 1;
    return c_test_status.value;
}
#endif
