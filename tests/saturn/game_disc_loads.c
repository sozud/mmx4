// saturn-capability: disc
// saturn-step-budget: 400000000
#include "test_runtime.h"
#include "support/saturn_disc.h"
#include "saturn/weapon_resources.h"

void func_8002E420(struct EngineObj* arg0);
void func_8002E698(struct EngineObj* arg0);
void func_8002EDD4(struct EngineObj* arg0);
extern u8 mission_palette_order[];

#define run_game_thread test_disc_run_thread

static const struct {
    u8 character, story, cleared, video, step, next_story;
} missions[] = {
    { 0, 0, 0, 0, 8, 0 },
    { 1, 0, 0, 1, 8, 0 },
    { 0, 1, 0, 2, 8, 1 },
    { 0, 3, 7, 0, 1, 3 },
    { 0, 3, 15, 2, 1, 3 },
    { 1, 3, 15, 7, 1, 3 },
    { 0, 5, 15, 3, 1, 5 },
    { 1, 5, 15, 8, 1, 5 },
    { 0, 7, 255, 4, 1, 7 },
    { 1, 7, 255, 9, 1, 7 },
    { 0, 8, 255, 0, 1, 8 },
    { 1, 8, 255, 0, 1, 9 },
    { 0, 9, 255, 0, 1, 9 },
};
static void mission_init_thread(void) { func_8002E420(&engine_obj); }
static void mission_setup(u32 row)
{
    test_disc_startup();
    memset(&engine_obj, 0, sizeof(engine_obj));
    engine_obj.state = 3;
    engine_obj.unk1 = 0;
    engine_obj.unk2 = 2;
    engine_obj.unk3 = 3;
    engine_obj.unk1F = engine_obj.enable_boss = 1;
    engine_obj.cur_character = missions[row].character;
    engine_obj.unk5F = missions[row].story;
    engine_obj.palette_flags = missions[row].cleared;
    engine_obj.unk8 = engine_obj.unkA = 0x1234;
    memset(&engine_obj.character_state, 0x25, sizeof(engine_obj.character_state));
    main_bss_state.character_mode = 1;
    D_8013B810 = D_8013B814 = 1;
    D_80171EA8 = 1;
}
static u32 mission_init(u32 row)
{
    u32 i;
    mission_setup(row);
    run_game_thread(mission_init_thread, 1);
    assert(engine_obj.state == 3 && engine_obj.unk1 == missions[row].step);
    assert(engine_obj.unk2 == 0 && engine_obj.unk3 == 0);
    assert(engine_obj.stage == 13 && engine_obj.substage == 0 && engine_obj.checkpoint == 0);
    assert(engine_obj.unkE == missions[row].video);
    assert(engine_obj.unk5F == missions[row].next_story);
    assert(engine_obj.cur_character == missions[row].character);
    assert((u8)engine_obj.palette_flags == missions[row].cleared);
    assert(engine_obj.unk1F == 0 && engine_obj.enable_boss == 0);
    assert(engine_obj.unk8 == 0 && engine_obj.unkA == 0);
    for (i = 0; i < sizeof(engine_obj.character_state.bytes); i++)
        assert(engine_obj.character_state.bytes[i] == 0);
    assert(main_bss_state.character_mode == 0 && D_8013B810 == 0 && D_8013B814 == 0 && D_80171EA8 == 0);
    return engine_obj.unk1;
}

static const struct {
    u8 mission, free_slots, icons, next_step;
    s8 video;
} briefings[] = {
    { 0, 64, 2, 9, 0 },
    { 3, 64, 2, 2, -1 },
    { 6, 64, 2, 9, -1 },
    { 12, 64, 1, 2, -1 },
    { 0, 64, 1, 9, 10 },
    { 7, 64, 2, 9, -1 },
    { 9, 64, 1, 9, -1 },
    { 7, 64, 1, 9, 5 },
    { 6, 0, 0, 9, -1 },
    { 6, 1, 1, 9, -1 },
};
static void briefing_thread(void) { func_8002E698(&engine_obj); }
static u32 briefing(u32 row)
{

    u32 i, j, spawned = 0;
    u8 story, character, cleared, video;
    mission_setup(briefings[row].mission);
    run_game_thread(mission_init_thread, row != 0);
    if (briefings[row].video >= 0)
        engine_obj.unkE = briefings[row].video;
    story = engine_obj.unk5F;
    character = engine_obj.cur_character;
    cleared = engine_obj.palette_flags;
    video = engine_obj.unkE;

    for (i = 0; i < COUNT(misc_objects); i++) {
        misc_objects[i].active = i < COUNT(misc_objects) - briefings[row].free_slots;
        misc_objects[i].id = 0x55;
    }
    engine_obj.unk2 = 3;
    if (row == 0) {
        assert(saturn_archive_queue_busy);
        func_8002E698(&engine_obj);
        assert(engine_obj.unk1 == missions[0].step && engine_obj.unk2 == 3);
        for (i = 0; i < COUNT(misc_objects); i++)
            assert(misc_objects[i].id == 0x55);
        return 0;
    }
    run_game_thread(briefing_thread, 0);
    assert(engine_obj.unk1 == briefings[row].next_step && engine_obj.unk2 == 0);
    assert(engine_obj.cur_character == character && engine_obj.unk5F == story && engine_obj.unkE == video);
    assert(main_bss_state.transition.active == 1);
    for (i = 0; i < COUNT(misc_objects); i++) {
        if (misc_objects[i].id == 0xA) {
            assert(misc_objects[i].active == 0x41 && misc_objects[i].unk2 == spawned);
            spawned++;
        } else
            assert(misc_objects[i].id == 0x55);
    }
    assert(spawned == briefings[row].icons);
    for (i = 0; i < 8; i++) {
        u16* colors = SP_PALETTES[mission_palette_order[i]];
        u32 coloured = 0;
        for (j = 0; j < 16; j++)
            coloured += (colors[j] & 31) != ((colors[j] >> 5) & 31) || (colors[j] & 31) != ((colors[j] >> 10) & 31);
        assert((cleared & (1 << i)) ? coloured == 0 : coloured != 0);
    }

    return spawned;
}

static const struct {
    u8 character, stage, story, video, defeated;
    u8 expected_state, expected_step, expected_video;
} entries[] = {
    { 0, 11, 8, 0, 0, 3, 8, 3 },
    { 0, 11, 9, 0, 0, 4, 0, 0 },
    { 0, 0, 1, 0, 0, 4, 0, 0 },
    { 0, 1, 4, 0, 0, 3, 11, 0 },
    { 0, 8, 4, 0, 0, 3, 11, 0 },
    { 0, 1, 4, 0, 1, 4, 0, 0 },
    { 0, 8, 4, 0, 0x80, 4, 0, 0 },
    { 0, 9, 4, 0, 0, 4, 0, 0 },
    { 1, 8, 3, 9, 0, 3, 8, 4 },
    { 1, 8, 4, 9, 0, 3, 11, 9 },
    { 1, 8, 3, 8, 0, 3, 11, 8 },
    { 1, 9, 5, 0, 0, 9, 0, 0 },
    { 1, 10, 5, 0, 0, 4, 0, 0 },
    { 1, 0, 1, 0, 0, 4, 0, 0 },
    { 1, 1, 4, 0, 1, 4, 0, 0 },
    { 1, 8, 4, 0, 0, 3, 11, 0 },
};
static void entry_thread(void) { func_8002EDD4(&engine_obj); }
static u32 mission_entry(u32 row)
{
    test_disc_startup();
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    engine_obj.state = 3;
    engine_obj.unk1 = 7;
    engine_obj.unk2 = 4;
    engine_obj.unk3 = 5;
    engine_obj.cur_character = entries[row].character;
    engine_obj.stage = entries[row].stage;
    engine_obj.unk5F = entries[row].story;
    engine_obj.unkE = entries[row].video;
    engine_obj.palette_flags = entries[row].defeated;
    run_game_thread(entry_thread, 0);
    assert(engine_obj.state == entries[row].expected_state);
    assert(engine_obj.unk1 == entries[row].expected_step);
    assert(engine_obj.unkE == entries[row].expected_video);
    assert(engine_obj.unk2 == 0 && engine_obj.unk3 == 0);
    assert(engine_obj.cur_character == entries[row].character && engine_obj.stage == entries[row].stage);
    assert(engine_obj.unk5F == entries[row].story && (u8)engine_obj.palette_flags == entries[row].defeated);
    return engine_obj.unk1;
}

const struct CTestGroup c_test_groups[] = {
    { "saturn_mission_initialization", 0, 0, COUNT(missions), mission_init },
    { "saturn_briefing_initialization", 0, 0, COUNT(briefings), briefing },
    { "saturn_mission_entry", 0, 0, COUNT(entries), mission_entry },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(missions) + COUNT(briefings) + COUNT(entries);
