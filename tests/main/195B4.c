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
static const u32 stage_record_checkpoint_pool_cases_expected[] = { 0x25u, 0x25u, 0x642827u };

extern struct StageObjectRecord* D_800F43C8[13][2];
static struct StageObjectRecord records_before[256];
static struct EffectObj effects_before[32];
static const s16 positions[3] = { 6048, 6176, 6304 };
static u32 scan(u32 row)
{
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before;
    struct StageObjectRecord* records = D_800F43C8[4][0];
    u32 i, count = 0, found = 0;
    engine_obj.stage = 4;
    engine_obj.substage = 0;
    engine_before = engine_obj;
    while (records[count].object_type != 255) {
        assert(count + 1 < COUNT(records_before));
        count++;
    }
    count++;
    c_test_copy_words((u32*)records_before, (const u32*)records, count * sizeof(*records) / 4);
    for (i = 0; i < count; i++)
        if (records[i].x == positions[row] && records[i].y == 640 && !(records[i].flags & 0x81)) {
            assert(records[i].object_type == 3 && records[i].id == 33 && records[i].subtype == 0x23);
            found++;
        }
    assert(found == 1);
    c_test_zero_words((u32*)effect_objects, sizeof(effect_objects) / 4);
    for (i = 0; i < COUNT(effect_objects); i++) {
        effect_objects[i].active = 1;
        effect_objects[i].id = 33;
        effect_objects[i].state = 1;
        effect_objects[i].unk2 = 0x22;
        effect_objects[i].x_pos.val = i * 65536 + 0x1234;
    }
    memcpy(effects_before, effect_objects, sizeof(effects_before));
    func_80028FEC(positions[row] - 1, positions[row] + 1, 639, 641, 1);
    c_test_same_words(records, records_before, count * sizeof(*records));
    c_test_same_words(effect_objects, effects_before, sizeof(effects_before));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(D_800F43C8[4][0] == records);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "stage_record_checkpoint_pool", NULL, stage_record_checkpoint_pool_cases_expected, COUNT(stage_record_checkpoint_pool_cases_expected), record_case },
    { "three_real_jungle_records_remain_unspawned_when_effect_pool_is_full", NULL, NULL, 3, scan },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(stage_record_checkpoint_pool_cases_expected) + 3;
