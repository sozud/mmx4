#include "test_runtime.h"
#include "main/effects/effect_17_freeze_blast.h"
#include "weapon_resources.h"

void func_800B94B8(struct EffectObj* self);

static u32 metadata[32];
static s32 frames[32];
static u32 spawn(u32 row)
{
    static const u32 expected[5] = { 0x150C080Au, 0x150C1807u, 0x150C2806u, 0x150C380Bu, 0x01600190u };
    struct EffectObj blast;
    u8* old_frames = TEST_MENU_FRAMES;
    u32* old_metadata = D_801406A8;
    u32 observed[5], i;
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    for (i = 4; i < COUNT(main_objects); i++)
        main_objects[i].active = 1;
    for (i = 0; i < COUNT(metadata); i++) {
        metadata[i] = (i + 1) * 128;
        frames[i] = (i + 1) * 64;
    }
    D_801406A8 = metadata;
#ifdef MMX4_SATURN
    saturn_stage_graphics_offsets_pointer = metadata;
#endif
    TEST_MENU_FRAMES = (u8*)frames;
    engine_obj.stage = 0;
    engine_obj.substage = 0;
    memset(&blast, 0, sizeof(blast));
    blast.active = 1;
    blast.id = 17;
    blast.unk2 = 0;
    cur_random = 0x1234;
    func_800B94B8(&blast);
    for (i = 0; i < 4; i++) {
        struct MainObj* enemy = &main_objects[i];
        assert(enemy->active == 0x41 && enemy->unk40 == (u16)OBJECT_STAGE_TEXTURE(func_8002938C(0x15)) && enemy->unk42 == (u16)OBJECT_STAGE_CLUT(0x15));
        assert(enemy->sprite_frames == (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0x15)));
        observed[i] = (u8)enemy->unk2 | (u32)(u16)enemy->x_pos.i.hi << 8 | (u32)(u8)enemy->id << 24;
    }
    observed[4] = (u16)main_objects[0].y_pos.i.hi | (u32)(u16)main_objects[2].y_pos.i.hi << 16;
    D_801406A8 = old_metadata;
    TEST_MENU_FRAMES = old_frames;
    return c_test_observe(0, row, observed, expected, 5);
}

#ifndef VERSION_DEMO
void freeze_blast_finish(struct EffectObj*);
static u32 freeze_finish(u8 count)
{
    struct EffectObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.active = 1;
    obj.ext.effect_17.timer = count;
    engine_obj.character_state.fields.active = 1;
    freeze_blast_finish(&obj);
    return (u8)obj.active | (u32)obj.ext.effect_17.timer << 8 | (u32)engine_obj.character_state.fields.active << 16;
}
static u32 fz_end(void) { return freeze_finish(2); }
static u32 fz_tick(void) { return freeze_finish(1); }
static const CTestCase freeze_blast_finish_cases[] = {
    fz_end,
    fz_tick,
};
static const u32 freeze_blast_finish_cases_expected[] = { 0x100u, 0x10001u };
#define FREEZE_FINISH_CASES COUNT(freeze_blast_finish_cases)
#else
#define FREEZE_FINISH_CASES 0
#endif

const struct CTestGroup c_test_groups[] = {
#ifndef VERSION_DEMO
    { "freeze_blast_finish", freeze_blast_finish_cases, freeze_blast_finish_cases_expected, COUNT(freeze_blast_finish_cases), 0 },
#endif
    { "first_group_into_four_free_slots", NULL, NULL, 1, spawn },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + FREEZE_FINISH_CASES;
