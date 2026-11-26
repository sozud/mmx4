#ifndef MMX4_C_TEST_RUNTIME_H
#define MMX4_C_TEST_RUNTIME_H
#include "common.h"
#include "weapon_resources.h"

#ifndef DEMO_ALT
#define DEMO_ALT(retail, demo) (retail)
#endif
#ifndef OBJ_UNK74
#define OBJ_UNK74(obj) ((obj).unk74)
#define OBJ_UNK74_SET(obj, value) ((obj).unk74 = (value))
#define OBJ_UNK78(obj) ((obj).unk78)
#define OBJ_UNK78_SET(obj, value) ((obj).unk78 = (value))
#endif
#ifndef VERSION_DEMO
#define PLAYER_ANIM(n) (n)
#define PLAYER_ZERO_ANIM(n) (n)
#define PLAYER_ATTACK_ANIM_OFFSET 0x70
#endif

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
#ifdef MMX4_SATURN
#define C_TEST_PSX_WORD(word) ((u32)(((u32)(word) >> 24) | (((u32)(word) >> 8) & 0xFF00u) | (((u32)(word) << 8) & 0xFF0000u) | ((u32)(word) << 24)))
#define C_TEST_VISIBLE(layer) ((u8)(layer) >> 4 < 5 && ((u8)(layer)&15) < 4)
#else
#define C_TEST_PSX_WORD(word) ((u32)(word))
#define C_TEST_VISIBLE(layer) 1
#endif
#define C_TEST_STEP(word) C_TEST_PSX_WORD(word)
#define C_TEST_PSX_FACING(value) ((u8)(value)&PLAYER_FACING_RIGHT ? ((u8)(value) & ~PLAYER_FACING_RIGHT) | 0x40 : (u8)(value))
#define C_TEST_LE_WORD(pointer) ((u32)((const u8*)(pointer))[0] | (u32)((const u8*)(pointer))[1] << 8 | (u32)((const u8*)(pointer))[2] << 16 | (u32)((const u8*)(pointer))[3] << 24)
#define FILL_ACTIVE(pool, count, value)           \
    do {                                          \
        u32 slot_;                                \
        for (slot_ = 0; slot_ < (count); slot_++) \
            (pool)[slot_].active = (value);       \
    } while (0)

void c_test_skip(void);
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
#define TEST_DISC32(v) C_TEST_PSX_WORD(v)

#if defined(MMX4_SATURN) && !defined(MMX4_PC)
#define TEST_BG_TILE_PIXELS (*(u8**)&SP_BG_TILE_PIXELS)
#define TEST_BG_TILE_ATTRS (*(u8**)&SP_BG_TILE_ATTRS)
#else
#define TEST_BG_TILE_PIXELS TEST_SP_SLOT(0, 0x008)
#define TEST_BG_TILE_ATTRS TEST_SP_SLOT(1, 0x00C)
#endif
#ifdef MMX4_SATURN
#include "saturn/player_resources.h"
#define TEST_PLAYER_GFX (*(u8**)&SP_PLAYER_GFX)
#define TEST_SPRITE_FRAMES (*(u8**)&SP_SPRITE_FRAMES)
#define TEST_PALETTE (*(u8**)&SP_PALETTE)
#define TEST_PALETTE_BANK (*(u8**)&SP_PALETTE_BANK)
#define TEST_MENU_FRAMES (*(u8**)&SP_MENU_FRAMES)
#else
#define TEST_PLAYER_GFX TEST_SP_SLOT(2, 0x014)
#define TEST_SPRITE_FRAMES TEST_SP_SLOT(3, 0x01C)
#define TEST_PALETTE TEST_SP_SLOT(5, 0x028)
#define TEST_PALETTE_BANK TEST_SP_SLOT(9, 0x024)
#define TEST_MENU_FRAMES TEST_SP_SLOT(10, 0x020)
#endif
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
#ifndef C_TEST_FILE
#define C_TEST_FILE 0
#endif
#undef assert
#ifdef MMX4_C_TEST_RECORD
void c_test_note(u32 site, u32 value);
#define assert(expression) c_test_note(__LINE__ | (u32)C_TEST_FILE << 24, (expression) ? 1 : 0)
#else
#define assert(expression) ((expression) ? (void)0 : c_test_fail(__LINE__ | (u32)C_TEST_FILE << 24))
#endif
#endif
#endif
#endif
