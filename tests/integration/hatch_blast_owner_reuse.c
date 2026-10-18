#include "test_runtime.h"
#include "main/objects.h"
#include "main/mains/main_63_hatch_turret.h"
void func_8007BFF4(struct MainObj*);
void hatch_blast_init(struct ShotObj*);
void hatch_blast_main(struct ShotObj*);
void hatch_turret_despawn(struct MainObj* arg0);
struct MainObj* find_free_main_obj(void);
static struct MainObj mains_before[48];
static struct ShotObj shots_expected[32];
static const s16 hatch_x[3] = { 2832, 5408, 5984 };
static u32 lifetime(u32 row)
{
    struct MainObj* owner = &main_objects[0];
    struct ShotObj* child = &shot_objects[31];
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before;
    u32 kind = row % 3, reuse = row / 3, i;
    engine_obj.stage = 7;
    engine_obj.substage = 0;
    engine_before = engine_obj;
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    for (i = 0; i < COUNT(main_objects); i++)
        main_objects[i].active = 0x41;
    for (i = 0; i < COUNT(shot_objects); i++)
        shot_objects[i].active = i == 31 ? 0 : 0x41;
    owner->id = 63;
    owner->unk2 = kind;
    owner->x_pos.val = hatch_x[kind] * 65536 + 0x1234;
    owner->y_pos.val = 296 * 65536 + 0x5678;
    func_8007BFF4(owner);
    func_8007C090(WEAPON_OBJECT(owner));
    assert(child->id == 40 && child->unk7C == WEAPON_OBJECT(owner));
    hatch_blast_init(child);
    hatch_turret_despawn(owner);
    assert(owner->active == 0);
    if (reuse) {
        struct MainObj* recycled = find_free_main_obj();
        assert(recycled == owner);
        recycled->active = 0x41;
        recycled->id = 67;
        recycled->unk2 = 0;
        recycled->x_pos.i.hi = 416;
        recycled->y_pos.i.hi = 399;
    }
    memcpy(mains_before, main_objects, sizeof(mains_before));
    memcpy(shots_expected, shot_objects, sizeof(shots_expected));
    memset(&shots_expected[31], 0, 8);
    hatch_blast_main(child);
    c_test_same_words(main_objects, mains_before, sizeof(mains_before));
    c_test_same_words(shot_objects, shots_expected, sizeof(shots_expected));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "real_turret_child_then_owner_despawn_and_pool_slot_reallocation", NULL, NULL, 6, lifetime } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 6;
