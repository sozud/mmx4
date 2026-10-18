#include "test_runtime.h"
#include "main/player_common.h"
void crumble_trigger_init(struct ItemObj*);
void crumble_trigger_wait_player(struct ItemObj*);
extern u8* crumble_trigger_box_sets[6];
extern s16 crumble_trigger_positions[6][2];
static struct EffectObj effects_expected[32];
static u32 crumble(u32 row)
{
    struct ItemObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u32 kind = row % 6, full = row / 6, i;
    const s8* box = (const s8*)crumble_trigger_box_sets[kind];
    engine_obj.stage = 2;
    engine_obj.substage = 0;
    engine_before = engine_obj;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.active = 0x41;
    g_Player.hp = 24;
    g_Player.x_pos.i.hi = crumble_trigger_positions[kind][0] + box[0];
    g_Player.y_pos.i.hi = crumble_trigger_positions[kind][1] + box[1];
    player_set_collision_bounds(&g_Player);
    player_before = g_Player;
    c_test_zero_words((u32*)effect_objects, sizeof(effect_objects) / 4);
    for (i = 0; i < COUNT(effect_objects); i++)
        effect_objects[i].active = i == 31 && !full ? 0 : 1;
    memcpy(effects_expected, effect_objects, sizeof(effects_expected));
    memset(&obj, 0, sizeof(obj));
    obj.active = 1;
    obj.id = 17;
    obj.state = 0;
    obj.unk2 = kind;
    crumble_trigger_init(&obj);
    expected = obj;
    expected.state = 2;
    expected.unk68 = &obj.unk7C.bounds[0];
    if (!full) {
        struct EffectObj* e = &effects_expected[31];
        e->active = 1;
        e->id = 21;
        e->unk2 = 4;
        e->ext.effect_21.index = kind + 8;
    }
    crumble_trigger_wait_player(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(effect_objects, effects_expected, sizeof(effects_expected));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "six_original_trigger_box_sets_full_last_effect_slot", NULL, NULL, 12, crumble } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 12;
