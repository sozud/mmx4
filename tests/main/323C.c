#include "test_runtime.h"
#ifndef MMX4_SATURN
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
#define BLOCK_COPY_CASES COUNT(block_copy_primitives_cases)
#else
#define BLOCK_COPY_CASES 0
#endif

#ifdef MMX4_PC
#include "main/3D88.h"
#include "main/55C4.h"
#include "main/323C.h"
#include "support/cd_disc.h"
#include <psyz/spu.h>
#include <stdlib.h>
void func_800129A4(s8 arg0);
void func_800129F0(s32 amount);
void func_80012F44(void);
void func_80015C10(void);
extern s32 mmx4_pc_canonical_load;
extern u8 D_80110064[64];
extern u8 D_800F1654[4];
extern u8 D_800EE480[8];
extern union SepBundle D_801459C8;
extern u8 stage_common_archives[16][2], stage_x_archives[16][2], stage_zero_archives[16][2];
extern u8 stage13_common_substage_archives[8], stage13_character_archives[8];
struct CharacterArchiveVariants {
    u8 archive_ids[2];
    u8 unused[2];
};
extern struct CharacterArchiveVariants stage_common_stage13_variants;

static u32 test_fade(u32 row)
{
    struct DrawInfo draw, *saved_draw = cur_draw_info;
    struct MainBssState saved_main = main_bss_state;
    s32 level = row == 0 ? 0xFF : 0, frame;
    DISPENV display, seen;
    u32 i;
    ResetGraph(0);
    mmx4_pc_threads_init();
    memset(&draw, 0, sizeof(draw));
    cur_draw_info = &draw;
    SP_DRAW_BUFFER = 1;
    main_bss_state.transition.active = 0;
    SetDefDispEnv(&display, 0, 0, 320, 240);
    PutDispEnv(&display);
    if (row == 0)
        func_800129A4(8);
    else
        func_800129F0(8);
    assert(main_bss_state.transition.active == (row == 0 ? 1 : -1) && main_bss_state.transition.fade_amount == 8);
    mmx4_pc_thread_run(2);
    assert(D_8016DEA0.unk0 == 0 && D_8016DEA2 == 0 && D_8016DEA4 == level);
    for (frame = 0; mmx4_pc_thread_slot(2)->state != 0; frame++) {
        TILE* tile = &D_80169D78[1];
        DR_TPAGE* page = &D_8012F498[1];
        setaddr(&draw.ordering_table.fade, 0x00ABCDEF);
        memset(tile, 0, sizeof(*tile));
        mmx4_pc_thread_run(2);
        assert(getcode(tile) == 0x62 && getlen(tile) == 3 && tile->x0 == 0 && tile->y0 == 0 && tile->w == 320 && tile->h == 240);
        assert(tile->r0 == level && tile->g0 == level && tile->b0 == level);
        assert(getlen(page) == 1 && (u32)page->code[0] == 0xE1000045 && (void*)getaddr(page) == tile);
        assert(getaddr(tile) == 0x00ABCDEF && (void*)getaddr(&draw.ordering_table.fade) == page);
        if (frame < 32) {
            level = row == 0 ? level - 8 : level + 8;
            level = level < 0 ? 0 : level > 0xFF ? 0xFF
                                                 : level;
            assert(D_8016DEA4 == level && D_8016DEA0.unk0 == (frame == 31));
            assert(main_bss_state.transition.fade_amount == (frame == 31 ? 2 : 8));
        } else {
            assert(main_bss_state.transition.fade_amount == (frame < 34 ? 33 - frame : 0));
        }
    }
    assert(frame == 35 && main_bss_state.transition.active == 0);
    GetDispEnv(&seen);
    for (i = 0; i < sizeof(seen); i++)
        assert(((u8*)&seen)[i] == (row == 0 ? ((u8*)&display)[i] : 0xFF));
    cur_draw_info = saved_draw;
    main_bss_state = saved_main;
    SetDispMask(1);
    return frame;
}

static u8 load_buffer[0x6000];
static u16 load_colors[0x800];
static u8* load_saved_slots[22];
static s32 load_place(u32 index, u32 row, u32 rows)
{
    s32 size, start = func_80013614(index, &size);
    cd_disc_place(start, row, rows ? rows : (size + 0x7FF) / 0x800);
    return size;
}
static void load_begin(void)
{
    u32 i;
    ResetGraph(0);
    memcpy(load_saved_slots, pc_archive_slots, sizeof(load_saved_slots));
    cd_disc_insert(CD_DISC_NOWHERE);
    memset(load_buffer, 0xA5, sizeof(load_buffer));
    for (i = 0; i < COUNT(load_colors); i++)
        load_colors[i] = 0x1000 + i;
    mmx4_pc_canonical_load = 0;
    D_801406AC = 0;
    D_8013E198[2] = -1;
}
static void load_end(void)
{
    cd_disc_eject();
    memcpy(pc_archive_slots, load_saved_slots, sizeof(load_saved_slots));
}

static u32 test_checkpoint_palette(u32 row)
{
    u8 checkpoint = row == 0 ? 1 : 3;
    u32 index = row == 0 ? 0x80 : D_800EE480[1], i;
    u8* saved_data = D_8015D9C8;
    u32 words[0x200];
    load_begin();
    load_place(index, 0, 2);
    cd_disc_archive(0, 13, 0x800);
    memcpy(words, cd_disc_data[1], sizeof(words));
    pc_archive_slots[5] = (u8*)load_colors;
    D_8015D9C8 = load_buffer;
    engine_obj.checkpoint = checkpoint;
    need_palette_load = 0x10;
    func_80012F44();
    load_end();
    assert(cd_disc_reads[0] == 1 && cd_disc_reads[1] == 1);
    for (i = 0; i < 0x800; i++) {
        u32 word = i / 2 - 0x140, half = i & 1;
        u16 expected = i >= 0x280 && i < 0x380 ? (u16)(words[checkpoint * 32 + 0xA0 + word] >> (half * 16)) : 0x1000 + i;
        assert(load_colors[i] == expected);
    }
    assert(D_8015D9C8 == load_buffer && need_palette_load == 0x11 && D_80171EA8 == checkpoint);
    D_8015D9C8 = saved_data;
    need_palette_load = 0;
    return index;
}

struct StageLoadRow {
    u8 stage, substage, character, room;
};
static const struct StageLoadRow stage_load_rows[] = {
    { 13, 0, CHARACTER_X, 0 },
    { 13, 1, CHARACTER_ZERO, 2 },
    { 14, 0, CHARACTER_X, 0 },
};
static u32 test_stage_load(u32 row)
{
    const struct StageLoadRow* in = &stage_load_rows[row];
    u8 saved_common[16][2], saved_x[16][2], saved_zero[16][2];
    u8 *saved_arena = D_80173C80, *saved_data = D_8015D9C8, *tiles;
    u32 common, character, i;
    memcpy(saved_common, stage_common_archives, sizeof(saved_common));
    memcpy(saved_x, stage_x_archives, sizeof(saved_x));
    memcpy(saved_zero, stage_zero_archives, sizeof(saved_zero));
    load_begin();
    engine_obj.stage = in->stage;
    engine_obj.substage = in->substage;
    engine_obj.cur_character = in->character;
    engine_obj.unk40 = in->room;
    if (in->stage == 13 && in->substage != 0) {
        common = stage13_common_substage_archives[in->room - 1];
        character = stage13_character_archives[in->room - 1];
    } else {
        common = in->stage == 13 ? stage_common_stage13_variants.archive_ids[in->character] : stage_common_archives[in->stage][in->substage];
        character = (in->character == CHARACTER_X ? stage_x_archives : stage_zero_archives)[in->stage][in->substage];
    }
    load_place(common, 0, 2);
    cd_disc_archive(0, 0, 0x800);
    load_place(character, 8, 2);
    cd_disc_archive(8, 1, 0x800);
    pc_archive_slots[5] = (u8*)load_colors;
    D_80173C80 = load_buffer;
    need_palette_load = 0x10;
    func_80013014();
    load_end();
    assert(cd_disc_reads[0] == 1 && cd_disc_reads[1] == 1 && cd_disc_reads[8] == 1 && cd_disc_reads[9] == 1);
    tiles = in->stage == 14 ? MAIN_ARCHIVE_ARENA : load_buffer;
    assert(memcmp(tiles, cd_disc_data[1], 0x800) == 0);
    assert(memcmp(tiles + 0x800, cd_disc_data[9], 0x800) == 0 && memcmp(tiles + 0x1000, cd_disc_data[1], 0x800) == 0);
    assert(D_801441B4 == (u16*)(tiles + 0x1000) && D_8015D9C8 == tiles + 0x1800);
    assert(layout_width == D_80110064[in->stage * 4 + in->substage * 2] && layout_height == D_80110064[in->stage * 4 + in->substage * 2 + 1]);
    assert(layout_size == layout_width * layout_height);
    for (i = 0; i < COUNT(load_colors); i++)
        assert(D_80141F70[i] == 0x1000 + i);
    assert(need_palette_load == 0x11);
    SetDispMask(1);
    need_palette_load = 0;
    memcpy(stage_common_archives, saved_common, sizeof(saved_common));
    memcpy(stage_x_archives, saved_x, sizeof(saved_x));
    memcpy(stage_zero_archives, saved_zero, sizeof(saved_zero));
    D_80173C80 = saved_arena;
    D_8015D9C8 = saved_data;
    return common << 8 | character;
}

static u32 load_sep(u8* out, u32 sequences)
{
    static const u8 body[] = { 0, 48, 0x07, 0xA1, 0x20, 4, 2, 0, 0, 0, 4, 0, 0xFF, 0x2F, 0 };
    u32 length = 8, i;
    memcpy(out, "pQES\0\0\0\0", 8);
    for (i = 0; i < sequences; i++) {
        if (i != 0) {
            out[length++] = 0;
            out[length++] = i;
        }
        memcpy(out + length, body, sizeof(body));
        length += sizeof(body);
    }
    return length;
}
static const u8 weapon_rows[][2] = { { CHARACTER_X, 0 }, { CHARACTER_X, 1 }, { CHARACTER_ZERO, 0 } };
static u32 test_weapon_load(u32 row)
{
    u8 character = weapon_rows[row][0];
    u32 index, bundle, i, sequences = 2;
    s32 size, stale;
    u8* saved_arena = D_80173C80;
    int success = setenv("SDL_AUDIODRIVER", "dummy", 1);
    assert(success == 0);
    Psyz_SpuInit();
    func_80014DC4();
    load_begin();
#if defined(VERSION_EU)
    index = character != CHARACTER_X ? 0x4E : weapon_rows[row][1] ? 0x4F
                                                                  : 0x4C;
#elif defined(VERSION_JP)
    index = character != CHARACTER_X ? 0x4D : weapon_rows[row][1] ? 0x4F
                                                                  : 0x4B;
#else
    index = character != CHARACTER_X ? 0x4D : weapon_rows[row][1] ? 0x4E
                                                                  : 0x4B;
#endif
    load_place(index, 0, 2);
    cd_disc_archive(0, 19, 0x800);
    bundle = D_800F1654[character];
    size = load_place(bundle, 8, 0);
    assert(size <= 0x4000);
    memset(cd_disc_data[8], 0, 0x4000);
    cd_disc_put_word(8, 0, 0x10);
    cd_disc_put_word(8, 1, 0x200);
    load_sep(&cd_disc_data[8][0x10], 8);
    load_sep(&cd_disc_data[8][0x200], 2);
    stale = SsSepOpenJ((unsigned long*)&cd_disc_data[8][0x200], 0, 2);
    assert(stale == 0);
    D_8013E1C8[3] = stale;
    engine_obj.cur_character = character;
    engine_obj.unk37 = weapon_rows[row][1];
    func_80012EB8();
    assert(pc_archive_slots[19] == MAIN_ARCHIVE_ARENA && memcmp(MAIN_ARCHIVE_ARENA, cd_disc_data[1], 0x800) == 0);
    load_end();
    assert(cd_disc_reads[0] == 1 && cd_disc_reads[1] == 1);
    for (i = 0; i < (u32)(size + 0x7FF) / 0x800; i++)
        assert(cd_disc_reads[8 + i] == 1);
    assert(D_80173C80 == MAIN_ARCHIVE_ARENA + 0x800 && D_8015D9C8 == D_80173C80);
    assert(saved_vab_address == loaded_vab_address && loaded_vab_address == 0x1010);
    assert(memcmp(D_801459C8.raw, cd_disc_data[8], size) == 0);
    assert(D_8013E1C8[0] == 0 && D_8013E1C8[1] == 1 && D_8013E1C8[2] == -1 && D_8013E1C8[3] == -1);
    stale = SsSepOpenJ((unsigned long*)&cd_disc_data[8][0x200], 0, sequences);
    assert(stale == 2);
    SsSepClose(stale);
    SsSepClose(D_8013E1C8[0]);
    SsSepClose(D_8013E1C8[1]);
    func_80014DC4();
    D_80173C80 = saved_arena;
    SetDispMask(1);
    return index;
}
#endif

const struct CTestGroup c_test_groups[] = {
#ifndef MMX4_SATURN
    { "block_copy_primitives", block_copy_primitives_cases, block_copy_primitives_cases_expected, COUNT(block_copy_primitives_cases), 0 },
#endif
#ifdef MMX4_PC
    { "fade_thread", 0, 0, 2, test_fade },
    { "checkpoint_palette_reload", 0, 0, 2, test_checkpoint_palette },
    { "stage_archive_load", 0, 0, COUNT(stage_load_rows), test_stage_load },
    { "weapon_archive_and_sequences", 0, 0, COUNT(weapon_rows), test_weapon_load },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = BLOCK_COPY_CASES
#ifdef MMX4_PC
    + 2 + 2 + COUNT(stage_load_rows) + COUNT(weapon_rows)
#endif
    ;
