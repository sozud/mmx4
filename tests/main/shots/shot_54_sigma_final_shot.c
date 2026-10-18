#include "test_runtime.h"
#include "main/shots/shot_54_sigma_final_shot.h"
#include "main/55C4.h"
extern void* sigma_final_animations[39];

static u32 lightning_case(u32 mode)
{
    struct ShotObj obj, before, pool_before[32];
    struct MainObj owner, owner_before;
    struct PlayerObj player_before = g_Player;
    u32 i, free_count = mode == 2 || mode == 4 ? 2 : mode == 3 ? 1
                                                               : 0;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(shot_objects, 0, sizeof(shot_objects));
    for (i = 0; i < 32; i++) {
        shot_objects[i].active = 1;
        shot_objects[i].id = 0x27;
        shot_objects[i].state = 0x28;
    }
    for (i = 0; i < free_count; i++)
        shot_objects[32 - free_count + i].active = 0;
    obj.active = 0x41;
    obj.id = 54;
    obj.state = 1;
    obj.unk6 = 2;
    obj.timer = 0x27;
    obj.unk70 = mode == 0 ? 0 : mode == 2 ? 4
                                          : 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = 65536;
    obj.y_vel.val = -32768;
    obj.animation_table = (const u8* const*)sigma_final_animations;
    set_animation(&obj, 0);
    owner.active = 0x41;
    owner.id = 74;
    owner.state = 1;
    obj.unk7C = WEAPON_OBJECT(&owner);
    D_8013E198[2] = -1;
    before = obj;
    owner_before = owner;
    memcpy(pool_before, shot_objects, sizeof(pool_before));
    sigma_lightning_fly(&obj);
    before.x_pos.val += 65536;
    before.y_pos.val += 32768;
    before.animation_step.fields.duration--;
    if (mode != 0) {
        before.timer = 10;
        before.unk6++;
    }
    for (i = 0; i < free_count; i++) {
        struct ShotObj* shot = &pool_before[32 - free_count + i];
        shot->active = 0x41;
        shot->id = 54;
        shot->unk2 = (mode == 2 ? 3 : 5) + i;
        shot->x_pos.val = 100 * 65536 + 0x1234;
        shot->y_pos.val = 200 * 65536 + 0x5678;
        shot->unk7C = WEAPON_OBJECT(&owner);
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(D_8013E198[2] == -1);
    return (u8)obj.unk6 | ((u32)(u16)obj.timer << 8) | ((u32)(u8)shot_objects[31].unk2 << 24);
}
#define CASE(m)                    \
    static u32 lightning_##m(void) \
    {                              \
        return lightning_case(m);  \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
#define ENTRY(m) lightning_##m,
static const CTestCase sigma_lightning_shot_pool_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) };
static const u32 sigma_lightning_shot_pool_cases_expected[] = { 0x2702u, 0xA03u, 0x4000A03u, 0x5000A03u, 0x6000A03u };
#undef CASE
#undef ENTRY

const struct CTestGroup c_test_groups[] = {
    { "sigma_lightning_shot_pool", sigma_lightning_shot_pool_cases, sigma_lightning_shot_pool_cases_expected, COUNT(sigma_lightning_shot_pool_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(sigma_lightning_shot_pool_cases);
