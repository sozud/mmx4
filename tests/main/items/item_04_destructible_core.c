#include "test_runtime.h"
void destructible_core_main(struct ItemObj*);
extern struct Unk_unk68 D_80108504[];
static struct WeaponObj weapons_before[16];
static u32 completion(u32 row)
{
    struct ItemObj obj, expected;
    struct EngineObj engine_before;
    struct PlayerObj player_before = g_Player;
    struct BackgroundObj backgrounds_before[3];
    u32 slot = row % 4, flags = row / 4, i;
    memset(&obj, 0, sizeof(obj));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    obj.active = 1;
    obj.id = 4;
    obj.state = 1;
    obj.unk2 = slot;
    obj.unk5 = 1;
    obj.unk42 = 0x9234;
    obj.unk5C = slot ? 32 : 80;
    obj.tail_ext.unk1.unk84.previous_value = obj.unk5C;
    obj.ext.timer = 2;
    obj.unk58 = (const u8*)D_80108504;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    for (i = 1; i < 4; i++)
        engine_obj.character_state.bytes[i] = (flags >> (i - 1)) & 1;
    engine_before = engine_obj;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    expected = obj;
    expected.unk42 = 0x1234;
    if (!slot)
        expected.ext.timer = 1;
    else if (flags & (1 << (slot - 1)))
        expected.state = 3;
    destructible_core_main(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    c_test_same_words(weapon_objects, weapons_before, sizeof(weapons_before));
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "all_core_slots_and_shared_completion_flag_combinations", NULL, NULL, 32, completion } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 32;
