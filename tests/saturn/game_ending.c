// saturn-capability: disc
// saturn-step-budget: 1500000000
#include "test_runtime.h"
#include "support/saturn_disc.h"

void func_80023684(struct EngineObj* arg0);
void func_80023698(struct EngineObj* arg0);
s32 GFS_NameToId(const char* name);
extern s32 saturn_cd_file_id;
extern u8 saturn_display_mode;

static void font_thread(void) { func_80023684(&engine_obj); }
static u32 ending_font_body(u32 row)
{
    test_disc_startup();
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    engine_obj.unk1 = 1;
    saturn_cd_file_id = -1;
    test_disc_run_thread(font_thread, 0);
    assert(saturn_cd_file_id == GFS_NameToId("ASCII.ARC") && engine_obj.unk1 == 2);
    return engine_obj.unk1;
}
static u32 ending_font(u32 row) { return test_disc_on_fixture_stack(ending_font_body, row); }

static void stage_thread(void) { func_80023698(&engine_obj); }
static u32 ending_stage_body(u32 row)
{
    char* name = saturn_stream_track_info.name;
    struct MiscObj* obj;
    u32 i, sparkles = 0;
    test_disc_startup();
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(misc_objects, 0, sizeof(misc_objects));
    engine_obj.unk1 = 2;
    engine_obj.unk2 = 5;
    engine_obj.cur_character = row;
    memset(&engine_obj.character_state, 0x25, sizeof(engine_obj.character_state));
    need_palette_load = 0;
    saturn_display_mode = 0;
    name[2] = name[3] = '?';
    test_disc_run_thread(stage_thread, 1);
    assert(engine_obj.stage == 15 && engine_obj.substage == 1 && engine_obj.unk1 == 3 && engine_obj.unk2 == 0);
    for (i = 0; i < 16; i++)
        assert(engine_obj.character_state.bytes[i] == 0);
    assert(row == 0 ? background_objects[1].y_pos.val != FIXED(768) : background_objects[1].y_pos.val == FIXED(768));
    for (obj = misc_objects; obj < misc_objects + COUNT(misc_objects); obj++)
        sparkles += obj->active != 0 && obj->id == 0x38;
    assert(sparkles == 5);
    assert(name[0] == 'S' && name[1] == 'T' && name[2] == '5' && name[3] == '1');
    return sparkles;
}
static u32 ending_stage(u32 row) { return test_disc_on_fixture_stack(ending_stage_body, row); }

const struct CTestGroup c_test_groups[] = {
    { "saturn_ending_font", 0, 0, 1, ending_font },
    { "saturn_ending_stage", 0, 0, 2, ending_stage },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 2;
