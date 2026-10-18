#include "test_runtime.h"
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

const struct CTestGroup c_test_groups[] = {
    { "web_shot_owner_and_hit", NULL, web_shot_owner_and_hit_cases_expected, COUNT(web_shot_owner_and_hit_cases_expected), web_case },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(web_shot_owner_and_hit_cases_expected);
