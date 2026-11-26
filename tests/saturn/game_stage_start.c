// saturn-capability: disc
// saturn-step-budget: 1500000000
#include "test_runtime.h"
#include "support/saturn_disc.h"
#include "saturn/player_resources.h"
#include "main/stage_object_record_tables.h"
#include "main/10CA4.h"

void func_8001FC20(struct EngineObj* arg0);
s32 saturn_archive_load_blocking(const char* path);
s32 GFS_NameToId(const char* name);
extern s32 saturn_cd_file_id;
extern u8 D_80171EA8;

static const struct {
    u8 stage, character, checkpoint, music_kept, loaded;
} starts[] = {
    { 3, 0, 0, 0, 0 },
    { 9, 0, 0, 1, 0 },
    { 12, 1, 5, 1, 0 },
    { 12, 1, 5, 1, 5 },
};
static void load_thread(void)
{
    saturn_archive_load_blocking("ASCII.ARC");
    saturn_archive_load_blocking(engine_obj.cur_character != 0 ? "PL01.ARC" : "PL00.ARC");
    engine_state_4(&engine_obj);
}
static void start_thread(void) { func_8001FC20(&engine_obj); }
static u32 stage_start_body(u32 row)
{
    char* name = saturn_stream_track_info.name;
    struct StageObjectRecord* record;
    u32 i, spawned;
    test_disc_startup();
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    engine_obj.state = 4;
    engine_obj.stage = starts[row].stage;
    engine_obj.cur_character = starts[row].character;
    engine_obj.player_lives = 2;
    engine_obj.max_hp = 0x20;
    test_disc_run_thread(load_thread, 1);
    assert(engine_obj.state == 5);
    engine_obj.checkpoint = starts[row].checkpoint;
    engine_obj.unk42 = starts[row].music_kept;
    D_80171EA8 = starts[row].loaded;
    for (i = 0; i < 0x20; i++)
        ((u16*)((u8*)SP_PALETTE + 0xA00))[i] = 0x1234;
    need_palette_load = 0;
    saturn_display_mode = 0;
    name[2] = name[3] = '?';
    saturn_cd_file_id = -1;
    test_disc_run_thread(start_thread, 1);
    assert(engine_obj.state == 6 && engine_obj.unk42 == 0 && engine_obj.gameplay_locked == 1);
    for (spawned = 0, record = D_800F43C8[engine_obj.stage][engine_obj.substage]; record->object_type != 0xFF; record++) {
        assert((record->flags & ~0x71) == 0);
        spawned += record->flags & 1;
    }
    assert(starts[row].stage == 9 ? spawned == 0 : spawned != 0);
    if (starts[row].music_kept)
        assert(name[2] == '?' && name[3] == '?');
    else
        assert(name[0] == 'S' && name[1] == 'T' && name[2] == '0' && name[3] == '3');
    if (row == 1) {
        for (i = 0; i < 0x20; i++)
            assert(((u16*)((u8*)SP_PALETTE + 0xA00))[i] == 0);
        assert((need_palette_load & 1) && saturn_display_mode == 11);
    } else {
        assert(((u16*)((u8*)SP_PALETTE + 0xA00))[0] == 0x1234 && saturn_display_mode == 0);
    }
    if (starts[row].stage == 12) {
        assert(D_80171EA8 == 5);
        if (starts[row].loaded)
            assert(saturn_cd_file_id != GFS_NameToId("STC_0_5.ARC"));
        else
            assert(saturn_cd_file_id == GFS_NameToId("STC_0_5.ARC"));
    }
    return engine_obj.state;
}
static u32 stage_start(u32 row) { return test_disc_on_fixture_stack(stage_start_body, row); }

void func_80020A08(struct EngineObj*);
static void (*const retries[])(struct EngineObj*) = { func_800206D0, func_8002088C, func_80020A08 };
static void (*retry_fn)(struct EngineObj*);
static void retry_thread(void) { retry_fn(&engine_obj); }
static u32 retry_reload_body(u32 row)
{
    test_disc_startup();
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    engine_obj.state = 6;
    engine_obj.unk1 = 3;
    engine_obj.stage = 3;
    engine_obj.checkpoint = 2;
    D_80171EA8 = 5;
    saturn_cd_file_id = -1;
    retry_fn = retries[row];
    test_disc_run_thread(retry_thread, 1);
    assert(D_80171EA8 == 0 && saturn_cd_file_id != -1);
    assert(engine_obj.state == 5 && engine_obj.unk1 == 0 && engine_obj.checkpoint == 0 && engine_obj.player_lives == 2);
    return engine_obj.state;
}
static u32 retry_reload(u32 row) { return test_disc_on_fixture_stack(retry_reload_body, row); }

const struct CTestGroup c_test_groups[] = {
    { "saturn_stage_start", 0, 0, COUNT(starts), stage_start },
    { "saturn_retry_reload", 0, 0, COUNT(retries), retry_reload },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(starts) + COUNT(retries);
