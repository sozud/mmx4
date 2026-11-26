// saturn-capability: disc
// saturn-step-budget: 400000000
#include "test_runtime.h"
#include "support/saturn_disc.h"
#include "main/menu.h"

void func_8001EE08(struct GameInfo* arg0);
void func_8001FB50(void);
s32 GFS_NameToId(const char* name);
extern s32 saturn_cd_file_id;

#define SAVE_CHARACTER 0
#define SAVE_ARMOR 0x29
#define HOST_SLOT 5
static const struct {
    u8 character, armor;
    const char* archive;
} saves[] = {
    { 1, 0, "PL01.ARC" },
    { 0, 1, "PL02.ARC" },
    { 0, 0, "PL00.ARC" },
};
static struct GameInfo info;
static void continue_thread(void) { func_8001EE08(&info); }
static u32 continue_load_body(u32 row)
{
    u8* record = (u8*)&D_800F1D90.save;
    test_disc_startup();
    memset(&info, 0, sizeof(info));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    engine_obj.cur_character = !saves[row].character;
    engine_obj.unk37 = !saves[row].armor;
    engine_obj.unk1 = engine_obj.unk2 = engine_obj.unk3 = 9;
    record[SAVE_CHARACTER] = saves[row].character;
    record[SAVE_ARMOR] = saves[row].armor;
    saturn_cd_file_id = -1;
    test_disc_run_thread_in(HOST_SLOT, continue_thread, 0);
    assert(engine_obj.cur_character == saves[row].character && engine_obj.unk37 == saves[row].armor);
    assert(saturn_cd_file_id == GFS_NameToId(saves[row].archive));
    assert(engine_obj.state == 1 && engine_obj.unk1 == 6 && engine_obj.unk2 == 0 && engine_obj.unk3 == 0);
    assert(saturn_threads[1].state == 1 && saturn_threads[1].entry == (u32)func_8001FB50);
    saturn_threads[1].state = 0;
    return engine_obj.unk1;
}
static u32 continue_load(u32 row) { return test_disc_on_fixture_stack(continue_load_body, row); }

const struct CTestGroup c_test_groups[] = {
    { "saturn_continue_load", 0, 0, COUNT(saves), continue_load },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(saves);
