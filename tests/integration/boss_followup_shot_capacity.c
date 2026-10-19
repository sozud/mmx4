#include "test_runtime.h"
#include "main/shots/shot_49_double_aerial.h"
#include "main/shots/shot_53_sigma_head.h"
#include "main/55C4.h"
void double_mine_fire(struct ShotObj*);
void func_800A2AA0(struct ShotObj*);
void sigma_head_freeze_drop(struct ShotObj*);
void sigma_head_freeze_open(struct ShotObj*);
void sigma_head_freeze_start(struct ShotObj*);
void walrus_ice_ball_burst(struct ShotObj*);
void walrus_ice_init(struct ShotObj*);
extern void* frost_walrus_animations[39];
extern void* double_animations[31];
extern void* sigma_final_animations[39];
static struct ShotObj pool_expected[32];
static u32 burst(u32 row)
{
    struct MainObj owner, owner_expected;
    struct ShotObj* obj = &shot_objects[0];
    struct ShotObj* expected = &pool_expected[0];
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before;
    struct BackgroundObj background_before;
    u32 kind = row % 3, slots = row / 3 % 3, side = row / 9 % 2, profile = row / 18, layer = kind == 1 ? 0 : profile, available = slots == 2 ? kind == 0 ? 9 : 2 : slots, emitted = kind == 0 ? available : available != 0, i;
    engine_obj.stage = kind == 0 ? 2 : kind == 1 ? 11
                                                 : 12;
    engine_obj.substage = kind == 1 ? 0 : 1;
    engine_before = engine_obj;
    memset(&owner, 0, sizeof(owner));
    owner.active = 0x41;
    owner.id = kind == 0 ? 57 : kind == 1 ? 73
                                          : 74;
    owner.state = 1;
    owner.hp = 48;
    owner.unk5 = kind == 0 ? 8 : 1;
    owner.unk15 = side ? 0x40 : 0;
    owner.bg_offset = layer;
    owner.x_pos.i.hi = kind == 0 ? 7288 : kind == 1 ? 2304
                                                    : 1473;
    owner.y_pos.i.hi = kind == 0 ? 400 : kind == 1 ? 446
                                                   : 707;
    owner.x_pos.u.lo = profile * 0x1234;
    owner.y_pos.u.lo = profile * 0x1357;
    owner.animation_table = (const u8* const*)(kind == 0 ? frost_walrus_animations : kind == 1 ? double_animations
                                                                                               : sigma_final_animations);
    background_objects[layer].x_pos.val = (owner.x_pos.i.hi - 160) * 65536;
    background_objects[layer].y_pos.val = (owner.y_pos.i.hi - 120) * 65536;
    background_before = background_objects[layer];
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    for (i = 0; i < COUNT(shot_objects); i++)
        shot_objects[i].active = i >= 32 - available ? 0 : 1;
    obj->active = 0x41;
    obj->on_screen = 1;
    obj->id = kind == 0 ? 35 : kind == 1 ? 51
                                         : 53;
    obj->state = kind == 0 ? 2 : 1;
    obj->unk5 = kind == 0 ? 1 : kind == 1 ? 5
                                          : 6;
    obj->unk6 = 2;
    obj->unk7C = WEAPON_OBJECT(&owner);
    obj->animation_table = (u32**)owner.animation_table;
    obj->unk15 = kind == 2 ? 0 : owner.unk15;
    obj->bg_offset = layer;
    obj->x_pos.val = owner.x_pos.val;
    obj->y_pos.val = owner.y_pos.val;
    if (kind == 0) {
        obj->state = 0;
        obj->unk2 = 16;
        walrus_ice_init(obj);
        func_800A2AA0(obj);
        obj->unk6 = 2;
        obj->unk8C.word = 1;
        owner.ext.main_57.shot = obj;
        set_animation_frame(ANIMATED_OBJECT(obj), 31, 4);
        assert(obj->animation_step.packed == 0x68000102);
    } else if (kind == 1) {
        double_toss_init(obj);
        obj->unk5 = 5;
        obj->unk6 = 2;
        obj->timer = 60;
        obj->x_vel.val = side ? -0x80000 : 0x80000;
        obj->y_vel.val = obj->unk2C = 0;
        set_animation_frame(ANIMATED_OBJECT(obj), 22, 4);
        assert(obj->animation_step.packed == 0x5C010101);
    } else {
        obj->state = 0;
        obj->unk2 = 2;
        func_800AAC98(obj);
        owner.ext.main_74.effect_state = 2;
        owner.ext.main_74.unk8C = 2;
        obj->unk8C.bytes[0] = 1;
        obj->unk8C.bytes[2] = 2;
        obj->x_pos.i.hi = 1432;
        obj->y_pos.i.hi = 648;
        func_800AB050(obj);
        assert(obj->unk5 == 6 && obj->on_screen == 1);
        obj->x_pos.i.hi = side ? 1240 : 1246;
        obj->unk6 = 0;
        sigma_head_freeze_start(obj);
        set_animation_frame(ANIMATED_OBJECT(obj), 9, 3);
        sigma_head_freeze_open(obj);
        assert(obj->animation_step.packed == 0x0A000001);
    }
    owner_expected = owner;
    memcpy(pool_expected, shot_objects, sizeof(pool_expected));
    if (kind == 0) {
        expected->unk8C.word = 0;
        expected->state = 6;
        expected->unk5 = expected->unk6 = 0;
        expected->on_screen = 1;
    } else if (kind == 1) {
        expected->animation_cursor++;
        expected->animation_step.packed = 0x5D010002;
    } else {
        expected->timer = 6;
        expected->x_pos.val -= 0x10000;
        if (side) {
            expected->unk5 = 3;
            expected->unk6 = 0;
            owner_expected.ext.main_74.unk8E = 1;
        }
    }
    for (i = 0; i < emitted; i++) {
        struct ShotObj* s = &pool_expected[32 - available + i];
        s->active = 0x41;
        s->id = kind == 0 ? 35 : kind == 1 ? 52
                                           : 54;
        s->unk2 = kind == 0 ? i + 64 : kind == 1 ? 0
                                                 : 2;
        s->x_pos = obj->x_pos;
        s->y_pos.val = obj->y_pos.val + (kind == 0 ? 0x40000 : 0);
        s->unk7C = kind == 1 ? WEAPON_OBJECT(obj) : WEAPON_OBJECT(&owner);
        if (kind != 2) {
            s->animation_table = obj->animation_table;
            s->unk3C = obj->unk3C;
            s->unk40 = obj->unk40;
            s->unk42 = obj->unk42 & 0x7FFF;
            s->unk15 = obj->unk15;
            if (kind == 0)
                s->bg_offset = layer;
            else
                s->unk16 = obj->unk16;
        }
    }
    D_8013E198[2] = -1;
    if (kind == 0)
        walrus_ice_ball_burst(obj);
    else if (kind == 1)
        double_mine_fire(obj);
    else
        sigma_head_freeze_drop(obj);
    c_test_same_words(shot_objects, pool_expected, sizeof(pool_expected));
    c_test_same_words(&owner, &owner_expected, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&background_objects[layer], &background_before, sizeof(background_before));
    assert(D_8013E198[2] == -1);
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "own_Walrus_nine_shards_Double_mine_event_Sigma_freeze_full_partial_pools", NULL, NULL, 54, burst } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 54;
