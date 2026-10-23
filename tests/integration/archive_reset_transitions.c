#include "test_runtime.h"
#include "main/game_info.h"
#include "main/1AC84.h"
void character_select_state_6(struct EngineObj*);
#ifdef MMX4_PC
#include <unistd.h>
#include <psyz/cd.h>
#include <psyz/spu.h>
#include <psyz/video.h>
#include <stdlib.h>
#include <stdint.h>
void func_8001213C(void);
extern s32 mmx4_pc_sfx_group, mmx4_pc_canonical_load;
extern const char* mmx4_pc_sfx_raw;
static struct MiscObj expected_misc[64];
static const struct {
    u32 file_id, bytes, hash;
} frame_payloads[] = {
    { 0, 68, 0xB7D13DBC },
    { 0x4B, 36696, 0xBFE47356 },
    { 0x4D, 28616, 0x6E626105 },
    { 0x4E, 39616, 0x2E6745EC },
};
#define POOLS(X)       \
    X(g_Player);       \
    X(g_Entity);       \
    X(foo_objects);    \
    X(baz_objects);    \
    X(weapon_objects); \
    X(main_objects);   \
    X(shot_objects);   \
    X(visual_objects); \
    X(effect_objects); \
    X(item_objects);   \
    X(unk_objects);    \
    X(layer_objects);  \
    X(g_QuadObjects);  \
    X(qux_object);     \
    X(bar_object);     \
    X(abc_object)
static void fill(void* data, u32 size, u32 word)
{
    u32 i;
    for (i = 0; i < size / 4; i++)
        ((u32*)data)[i] = word;
}
static void check_value(const void* data, u32 size, u32 word)
{
    u32 i;
    for (i = 0; i < size / 4; i++)
        assert(((const u32*)data)[i] == word);
}
#define PRIME(pool) fill(&(pool), sizeof(pool), 0x25252525)
#define CHECK(pool) check_value(&(pool), sizeof(pool), reset ? 0 : 0x25252525)
static u32 archive_reset(u32 row)
{
    struct GameInfo info, info_expected;
    struct EngineObj engine_expected;
    struct MainBssState main_expected;
    struct BackgroundObj backgrounds_expected[3];
    char cue[sizeof(__FILE__) + 32];
    char* suffix;
    u32 title = row % 2 == 0, character = row / 2 % 2, powered = row / 4 % 2, active = row / 8, reset = title || !active, i;
    strcpy(cue, __FILE__);
    suffix = strstr(cue, "/tests/integration/archive_reset_transitions.c");
    assert(suffix != NULL);
    strcpy(suffix, "/disks/mmx4.us.cue");
    if (access(cue, R_OK) != 0)
        c_test_skip();
    assert(setenv("SDL_AUDIODRIVER", "dummy", 1) == 0);
    assert(unsetenv("MMX4_ORACLE_SCENE") == 0);
    mmx4_pc_sfx_group = -1;
    mmx4_pc_sfx_raw = NULL;
    mmx4_pc_canonical_load = 0;
    assert(Psyz_CdSetDiskPath(cue) == 0);
    Psyz_SpuInit();
    assert(Psyz_VideoSetVsyncMode(PSYZ_VSYNC_LIMITLESS) == 0);
    func_8001213C();
    D_80173C80 = MAIN_ARCHIVE_ARENA;
    D_8015D9C8 = MAIN_ARCHIVE_ARENA;
    fill(MAIN_ARCHIVE_ARENA, sizeof(pc_archive_arena), 0xA55AA55A);
    pc_archive_slots[3] = NULL;
    POOLS(PRIME);
    PRIME(misc_objects);
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&info, 0x25, sizeof(info));
    info.unk0 = 3;
    info.mode = 0;
    info_expected = info;
    engine_obj.state = 1;
    engine_obj.unk1 = 6;
    engine_obj.stage = 14;
    engine_obj.substage = 1;
    engine_obj.cur_character = character;
    engine_obj.unk37 = powered;
    engine_expected = engine_obj;
    main_bss_state.transition.active = active;
    main_bss_state.transition.fade_amount = 3;
    main_expected = main_bss_state;
    for (i = 0; i < 3; i++) {
        memset(&background_objects[i], 0, sizeof(background_objects[i]));
        background_objects[i].unk3 = 1;
        background_objects[i].x_pos.val = i * 0x12345;
    }
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    if (reset) {
        memset(backgrounds_expected, 0, sizeof(backgrounds_expected));
        for (i = 0; i < 3; i++)
            backgrounds_expected[i].unk2 = i;
        memset(expected_misc, 0, sizeof(expected_misc));
    } else
        memcpy(expected_misc, misc_objects, sizeof(expected_misc));
    if (title) {
        info_expected.unkD = 1;
        info_expected.unk4 = 300;
        info_expected.mode = 1;
        expected_misc[0].active = 1;
        expected_misc[0].id = 21;
        if (!active) {
            main_expected.transition.active = 1;
            main_expected.transition.fade_amount = 8;
        }
        func_8001D5C8(&info);
    } else {
        if (reset) {
            engine_expected.state = 3;
            engine_expected.unk1 = 0;
            engine_expected.stage = engine_expected.substage = 0;
        }
        character_select_state_6(&engine_obj);
    }
    POOLS(CHECK);
    c_test_same_words(misc_objects, expected_misc, sizeof(expected_misc));
    c_test_same_words(&info, &info_expected, sizeof(info));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    c_test_same_words(&main_bss_state, &main_expected, sizeof(main_bss_state));
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    if (reset) {
        u32 payload = title ? 0 : character ? 2
            : powered                       ? 3
                                            : 1,
            hash = 2166136261u;
        uintptr_t frames = (uintptr_t)pc_archive_slots[3], base = (uintptr_t)MAIN_ARCHIVE_ARENA;
        assert(frames >= base && frames < base + sizeof(pc_archive_arena));
        assert(frame_payloads[payload].bytes <= base + sizeof(pc_archive_arena) - frames);
        for (i = 0; i < frame_payloads[payload].bytes; i++)
            hash = (hash ^ pc_archive_slots[3][i]) * 16777619u;
        assert(hash == frame_payloads[payload].hash);
        assert((uintptr_t)D_8015D9C8 >= base && (uintptr_t)D_8015D9C8 < base + sizeof(pc_archive_arena));
        for (i = 0; i < 4; i++)
            assert(D_80173C6C[i] == i + 3);
        assert(g_FilterAmountR == 0 && g_FilterAmountG == 0 && g_FilterAmountB == 0);
        assert(g_FilterModeR == 0 && g_FilterModeG == 0 && g_FilterModeB == 0);
    } else {
        check_value(MAIN_ARCHIVE_ARENA, sizeof(pc_archive_arena), 0xA55AA55A);
        assert(pc_archive_slots[3] == NULL);
    }
    return 1;
}
#endif
const struct CTestGroup c_test_groups[] = {
#ifdef MMX4_PC
    { "archive_reset_transitions", NULL, NULL, 16, archive_reset },
#else
    { "native_archive_reset_budget", NULL, NULL, 0, NULL },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
#ifdef MMX4_PC
const u32 c_test_count = 0
#ifdef MMX4_PC
    + 16
#else
    + 0
#endif
    ;
#else
const u32 c_test_count = 0;
#endif
