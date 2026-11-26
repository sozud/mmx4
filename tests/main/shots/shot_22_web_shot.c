#include "test_runtime.h"
#ifndef VERSION_DEMO
#include "main/shots/shot_22_web_shot.h"
#include "main/55C4.h"
#include "main/mains/main_43_web_spider.h"
extern u8 web_shot_hit_box[4];

static u32 web_case(u32 mode)
{
    struct ShotObj obj, before;
    struct WeaponObj owner, owner_before;
    struct PlayerObj player_before;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 22;
    obj.state = 1;
    obj.bg_offset = -1;
    obj.timer = 2;
    obj.unk8C.word = mode == 1 ? 0 : mode == 3 ? 3
                                               : 1;
    obj.unk62 = mode == 4 ? 3 : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = 65536;
    obj.y_vel.val = 0;
    obj.unk50.data = web_shot_hit_box;
    obj.animation_table = (const u8* const*)web_spider_animations;
    set_animation(&obj, 22);
    owner.active = 0x41;
    owner.id = 43;
    owner.state = mode == 0 ? 0 : mode == 3 ? 2
                                            : 1;
    obj.unk7C = &owner;
    g_Player.hp = 100;
    g_Player.hit_facing = 0x29;
    g_Player.stun_timer = mode == 3 ? 1 : 0;
    g_Player.x_pos.val = 101 * 65536 + 0x2345;
    g_Player.y_pos.val = obj.y_pos.val;
    g_Player.unk54 = (const u32*)web_shot_hit_box;
    before = obj;
    owner_before = owner;
    player_before = g_Player;
    web_shot_main(&obj);
    before.unk18 = before.x_pos;
    before.unk1C = before.y_pos;
    if (mode == 3) {
        before.unk5 = 3;
        before.timer = 120;
        before.unk90.val = 48;
        before.x_vel.val = 0;
        before.y_vel.val = 0;
        before.unk28 = 0;
        before.unk2C = 0;
        before.state = 2;
        player_before.x_pos = before.x_pos;
        player_before.y_pos = before.y_pos;
    } else {
        before.timer = 1;
        before.animation_cursor = (const u8*)&web_spider_animations[22][1];
        before.animation_step = web_spider_animations[22][1];
        before.x_pos.val += 65536;
        before.on_screen = 1;
        if (mode == 2 || mode == 4) {
            player_before.hp = (s8)0xE4;
            player_before.hurt_type = mode == 4 ? 3 : 1;
            if (mode == 2)
                player_before.hit_facing = 0;
            else {
                player_before.stun_timer = 1;
                before.unk8C.word = 3;
                before.x_pos = g_Player.x_pos;
                before.y_pos = g_Player.y_pos;
            }
        }
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.state | ((u32)(u8)obj.unk5 << 8) | ((u32)(u8)obj.unk8C.word << 16) | ((u32)(u8)player_before.stun_timer << 24);
}
static const u32 web_shot_owner_and_hit_cases_expected[] = { 0x10001u, 0x1u, 0x10001u, 0x1030302u, 0x1030001u };

static u32 web_steps(u32 index);
const struct CTestGroup c_test_groups[] = {
    { "web_steps", 0, 0, 20, web_steps },
    { "web_shot_owner_and_hit", NULL, web_shot_owner_and_hit_cases_expected, COUNT(web_shot_owner_and_hit_cases_expected), web_case },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(web_shot_owner_and_hit_cases_expected) + 20;

#include "weapon_resources.h"
#include "main/object_motion.h"
#include "support/state_cases.h"
void web_shot_fly(struct ShotObj*);
void web_shot_home(struct ShotObj*);
void web_shot_hold(struct ShotObj*);
void web_shot_fade(struct ShotObj*);
void web_shot_main(struct ShotObj*);
void web_shot_despawn(struct ShotObj*);
static u32 web_steps(u32 index)
{
    static const u8 scenarios[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 16, 17, 18, 19, 20 };
    u32 row = scenarios[index];
    static const u8 home_offsets[] = { 0, 0, 0, 0, 0, 3, 0x1D };
    struct ShotObj obj;
    struct WeaponObj owner;
    s32 target;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    owner.state = 1;
    obj.active = 0x41;
    obj.id = 22;
    obj.state = 1;
    obj.unk7C = &owner;
    obj.x_pos.i.hi = 100;
    obj.y_pos.i.hi = 100;
    obj.x_vel.val = 0x10000;
    obj.unk8C.word = 1;
    g_Player.hp = 16;
    g_Player.x_pos.i.hi = 160;
    g_Player.y_pos.i.hi = 140;
    if (row == 0) {
        obj.unk8C.word = 3;
        obj.timer = 1;
        web_shot_fly(&obj);
        assert(obj.unk5 == 1 && obj.timer == 0x28 && obj.x_pos.i.hi == 101);
    } else if (row <= 6) {
        obj.unk5 = 1;
        obj.unk8C.word = row == 1 || row == 3 ? 3 : 1;
        g_Player.stun_timer = row == 1 ? 5 : 0;
        obj.timer = row == 2 ? 0 : 5;
        WEAPON_FRAME_COUNTER = row == 3 ? 1 : 4;
        target = angle_to_object(OBJECT_HEADER(&obj), OBJECT_HEADER(&g_Player));
        obj.unk84.value = (target - home_offsets[row]) & 0x1F;
        web_shot_home(&obj);
        if (row == 1) {
            assert(obj.unk5 == 3 && obj.timer == 0x78 && obj.x_vel.val == 0 && obj.unk90.val == 0x30);
            assert(g_Player.x_pos.val == obj.x_pos.val && g_Player.y_pos.val == obj.y_pos.val);
        } else {
            assert(obj.unk5 == 1 && obj.timer == (row == 2 ? 0 : 4));
            assert(obj.unk84.value == ((target - home_offsets[row] + (row == 5 ? 1 : row == 6 ? -1 : 0)) & 0x1F));
            assert(row <= 4 ? obj.x_vel.val == 0x10000 : obj.x_vel.val != 0x10000);
        }
    } else if (row <= 9) {
        obj.unk5 = 3;
        obj.timer = row == 7 ? 0 : 10;
        obj.unk90.val = row == 8 ? 1 : 2;
        obj.unk50.data = (const u8*)&state_hit_box;
        g_Player.pressed_input = row == 7 ? 1 : 0;
        g_Player.stun_timer = 5;
        web_shot_hold(&obj);
        assert(g_Player.x_pos.val == obj.x_pos.val);
        assert(obj.unk5 == (row == 7 ? 4 : 3) && obj.timer == (row == 7 ? 0x1E : 9));
        assert(row == 7 ? obj.unk50.data == NULL && g_Player.stun_timer == 0 : obj.unk50.data != NULL);
        assert(obj.unk90.val == (row == 8 ? 0x30 : row == 9 ? 1 : 2) && (g_Player.hp == 16) == (row != 8));
    } else if (row <= 12) {
        obj.unk5 = 4;
        obj.timer = row == 10 ? 1 : 5;
        WEAPON_FRAME_COUNTER = row == 11 ? 4 : 5;
        web_shot_fade(&obj);
        assert(obj.state == (row == 10 ? 2 : 1));
        assert(row == 10 || (obj.on_screen == (row == 12) && obj.unk8A == (row == 11)));
    } else if (row <= 17) {
        obj.unk5 = 0;
        obj.timer = 5;
        obj.unk8C.word = row == 15 ? 3 : 1;
        g_Player.stun_timer = row == 13 ? 5 : 0;
        obj.unk50.data = (const u8*)&state_hit_box;
        if (row == 16)
            obj.x_pos.i.hi = 0x400;
        obj.unk8A = row == 17;
        obj.on_screen = 7;
        web_shot_main(&obj);
        assert(obj.state == (row == 16 ? 2 : 1) && obj.unk8C.word == (row == 15 ? 3 : 1));
        assert(obj.on_screen == (row == 16 ? 7 : row == 17 ? 7 : 1));
    } else {
        obj.state = 2;
        obj.unk8C.word = row == 20 ? 1 : 3;
        g_Player.stun_timer = row == 19 ? 0 : 5;
        web_shot_despawn(&obj);
        assert(obj.active == 0 && g_Player.stun_timer == (row == 20 ? 5 : 0));
    }
    return 1;
}
#else
const struct CTestGroup c_test_groups[] = {};
const u32 c_test_group_count = 0;
const u32 c_test_count = 0;
#endif
