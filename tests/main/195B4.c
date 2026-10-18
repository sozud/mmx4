#include "test_runtime.h"
#include "main/195B4.h"

static u32 record_case(u32 mode)
{
    struct StageObjectRecord records[] = { { 0, 0x27, 0x28, 0, 100, 200 }, { 0, 0, 0, 0xFF, 0, 0 } };
    struct StageObjectRecord records_before[2];
    struct MainObj pool_before[48];
    struct EngineObj engine_before;
    u32 i;
    memset(main_objects, 0, sizeof(main_objects));
    memset(&engine_obj, 0, sizeof(engine_obj));
    for (i = 0; i < 48; i++) {
        main_objects[i].active = 1;
        main_objects[i].id = 0x25;
        main_objects[i].state = 0x26;
    }
    if (mode == 0)
        records[0].flags = 1;
    if (mode == 2)
        main_objects[17].active = 0;
    memcpy(pool_before, main_objects, sizeof(pool_before));
    memcpy(records_before, records, sizeof(records_before));
    engine_before = engine_obj;
    func_800292D0(records);
    if (mode == 2) {
        pool_before[17].active = 1;
        pool_before[17].id = 0x27;
        pool_before[17].unk2 = 0x28;
        pool_before[17].x_pos.i.hi = 100;
        pool_before[17].y_pos.i.hi = 200;
        pool_before[17].backref = &records[0];
    }
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)main_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(records) / 4; i++)
        assert(((u32*)records)[i] == ((u32*)records_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    return main_objects[17].id | ((u32)main_objects[17].unk2 << 8) | ((u32)(u16)main_objects[17].x_pos.i.hi << 16);
}
#define CASE(m)                 \
    static u32 record_##m(void) \
    {                           \
        return record_case(m);  \
    }
CASE(0)
CASE(1)
CASE(2)
#define ENTRY(m) record_##m,
static const CTestCase stage_record_checkpoint_pool_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) };
static const u32 stage_record_checkpoint_pool_cases_expected[] = { 0x25u, 0x25u, 0x642827u };
#undef CASE
#undef ENTRY

const struct CTestGroup c_test_groups[] = {
    { "stage_record_checkpoint_pool", stage_record_checkpoint_pool_cases, stage_record_checkpoint_pool_cases_expected, COUNT(stage_record_checkpoint_pool_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(stage_record_checkpoint_pool_cases);
