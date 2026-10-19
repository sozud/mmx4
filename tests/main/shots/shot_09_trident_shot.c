#include "test_runtime.h"
#include "main/collision_bounds.h"
#include "main/55C4.h"
void trident_shot_flash(struct ShotObj*);
extern union AnimationStep* trident_mech_animations[29];
extern u8 trident_shot_flash_box[4];
static u32 flash(u32 row)
{
    struct ShotObj obj, expected;
    struct MainObj owner, owner_before;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 live = row % 2, expired = row / 2 % 2, outside = row / 4 % 2, face = row / 8, i;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    owner.active = 0x41;
    owner.id = 16;
    owner.state = 1;
    owner.ext.main_16.shot_09_active = live;
    owner_before = owner;
    g_Player.spike_immune = 1;
    player_before = g_Player;
    obj.active = 0x41;
    obj.id = 9;
    obj.state = 1;
    obj.on_screen = 1;
    obj.unk15 = face ? 0x40 : 0;
    obj.unk50.data = obj.unk54 = trident_shot_flash_box;
    obj.unk58.data = (const u8*)D_801060F0;
    obj.unk5C = 1;
    obj.unk60 = 3;
    obj.unk7C = (struct WeaponObj*)&owner.ext.main_16.shot_09_active;
    obj.unk84.value = expired ? 1 : 30;
    obj.x_pos.val = (outside ? 400 : 160) * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.animation_table = (u32**)trident_mech_animations;
    set_animation(&obj, 5);
    assert(obj.animation_step.packed == 0x04010001);
    expected = obj;
    expected.animation_cursor++;
    expected.animation_step.packed = 0x08010001;
    expected.unk84.value--;
    if (!live || expired || outside)
        expected.state = 2;
    trident_shot_flash(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_before, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    for (i = 0; i < 16; i++)
        assert(weapon_objects[i].active == 0);
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "real_owner_latch_timer_and_expanded_viewport_cleanup", NULL, NULL, 16, flash } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 16;
