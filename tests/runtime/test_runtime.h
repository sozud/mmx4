#ifndef MMX4_C_TEST_RUNTIME_H
#define MMX4_C_TEST_RUNTIME_H
#include "common.h"

typedef u32 (*CTestCase)(void);
struct CTestGroup {
    const char* name;
    const CTestCase* cases;
    const u32* expected;
    u32 count;
    u32 (*run)(u32 index);
};
struct CTestStatus {
    u32 magic, case_id, value, passed, failure_line;
};
extern const struct CTestGroup c_test_groups[];
extern const u32 c_test_group_count;
extern const u32 c_test_count;
extern volatile struct CTestStatus c_test_status;
u32 c_test_run(u32 index);
void c_test_fail(u32 line);
u32 c_test_group_run(const struct CTestGroup* group, u32 index);
u32 c_test_observe(u32 group, u32 row, const u32* observed, const u32* expected, u32 count);
void c_test_same_words(const void* actual, const void* expected, u32 size);
u32 c_test_word_difference(const u32* a, const u32* b, u32 count);
void c_test_copy_words(u32* dest, const u32* src, u32 count);
void c_test_zero_words(u32* dest, u32 count);

#ifdef MMX4_PC
extern u8* D_80141F50[8];
extern s32 player_gfx_buf_1[0x4000];
#else
extern u8* D_80141F50[2];
extern s32 player_gfx_buf_1[0xC00];
#endif

#ifdef MMX4_PC
#define TEST_SP_SLOT(slot, offset) pc_archive_slots[slot]
#else
#define TEST_SP_SLOT(slot, offset) (*(u8**)SP(offset))
#endif
#define TEST_BG_TILE_PIXELS TEST_SP_SLOT(0, 0x008)
#define TEST_BG_TILE_ATTRS TEST_SP_SLOT(1, 0x00C)
#define TEST_PLAYER_GFX TEST_SP_SLOT(2, 0x014)
#define TEST_SPRITE_FRAMES TEST_SP_SLOT(3, 0x01C)
#define TEST_PALETTE TEST_SP_SLOT(5, 0x028)
#define TEST_PALETTE_BANK TEST_SP_SLOT(9, 0x024)
#define TEST_MENU_FRAMES TEST_SP_SLOT(10, 0x020)
#define TEST_ARC_2C TEST_SP_SLOT(11, 0x02C)
#define TEST_ARC_30 TEST_SP_SLOT(13, 0x030)
#define TEST_ARC_34 TEST_SP_SLOT(16, 0x034)
#define TEST_VRAM_IMAGE TEST_SP_SLOT(17, 0x038)
#define TEST_TITLE_FRAMES TEST_SP_SLOT(18, 0x03C)
#define TEST_ARC_40 TEST_SP_SLOT(19, 0x040)
#define TEST_ARC_44 TEST_SP_SLOT(20, 0x044)
#define TEST_ARC_48 TEST_SP_SLOT(21, 0x048)

#ifdef MMX4_C_TEST_COLLECT
#define assert(expression) ((void)0)
#else
#ifdef MMX4_PC
#include <assert.h>
#else
#define assert(expression) ((expression) ? (void)0 : c_test_fail(__LINE__))
#endif
#endif
#endif
