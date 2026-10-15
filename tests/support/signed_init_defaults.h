#ifndef MMX4_TESTS_SIGNED_INIT_DEFAULTS_H
#define MMX4_TESTS_SIGNED_INIT_DEFAULTS_H

extern union AnimationStep* slope_skier_animations[];
extern union AnimationStep* hover_sentry_animations[];
extern struct Unk_unk68 D_80106870[], D_80106DF4[];
extern struct Unk_unk68 slope_skier_hurt_box[], slope_skier_terrain_box;
static u32 defaults_case(u32 mode, u32 skier)
{
    struct MainObj obj, expected;
    struct PlayerObj saved_player = g_Player, player_expected;
    struct MainObj* saved_current = SP_CUR_MAIN_OBJ;
    struct Unk_unk68 box = { -2, -3, 4, 5 };
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = skier ? 23 : 12;
    obj.unk2 = mode == 0 ? 3 : mode == 1 ? -128
                                         : 127;
    obj.state = 0;
    obj.unk5 = 8;
    obj.unk6 = 9;
    obj.unk7 = 10;
    obj.bg_offset = 1;
    obj.unk15 = 0x20;
    obj.hp = 9;
    obj.contact_damage = 8;
    obj.invincibility_timer = 7;
    obj.air_state = 6;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = 123;
    obj.y_speed = 456;
    obj.x_accel = 789;
    obj.gravity = 987;
    obj.terrain_box = &box;
    obj.attack_box = &box;
    obj.hurt_box = &box;
    obj.ext.main_12.unk81 = 7;
    obj.ext.main_12.unk88 = 8;
    g_Player.bg_offset = 2;
    g_Player.x_pos.val = 99 * 65536 + 0xBEEF;
    expected = obj;
    player_expected = g_Player;
    SP_CUR_MAIN_OBJ = &obj;
    expected.state = 1;
    expected.bg_offset = 2;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.air_state = 0;
    if (skier) {
        expected.unk5 = 1;
        expected.unk16 = 6;
        expected.hp = 3;
        expected.contact_damage = 1;
        expected.animation_table = (const u8* const*)slope_skier_animations;
        expected.terrain_box = slope_skier_hurt_box;
        expected.hurt_box = expected.attack_box = &slope_skier_terrain_box;
        expected.collision_data = (const u16*)D_80106DF4;
        expected.ext.main_23.unk80 = expected.ext.main_23.unk81 = expected.ext.main_23.unk82 = 0;
        expected.x_speed = expected.y_speed = expected.x_accel = expected.gravity = 0;
        expected.unk7C = 10;
        expected.unk17 = 4;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (const u8*)slope_skier_animations[4];
        expected.animation_step = slope_skier_animations[4][0];
        func_800564B4(&obj);
    } else {
        expected.unk6 = 0;
        expected.unk7C = 0x90;
        expected.invincibility_timer = 0;
        expected.animation_table = (const u8* const*)hover_sentry_animations;
        expected.unk15 = 0;
        expected.ext.main_12.unk88 = expected.ext.main_12.unk81 = 0;
        expected.collision_data = (const u16*)D_80106870;
        func_8004B8FC(&obj);
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    assert(SP_CUR_MAIN_OBJ == &obj);
    assert(box.unk0 == -2 && box.unk1 == -3 && box.unk2 == 4 && box.unk3 == 5);
    SP_CUR_MAIN_OBJ = saved_current;
    g_Player = saved_player;
    return (u8)obj.state | ((u32)(u8)obj.unk15 << 8) | ((u32)(u8)obj.unk5 << 16) | ((u32)(u8)obj.hp << 24);
}
#define DEFAULTS_CASE(m, s)                                              \
    static u32 hover_skier_signed_init_defaults_defaults_##m##_##s(void) \
    {                                                                    \
        return defaults_case(m, s);                                      \
    }
#define DEFAULTS_ENTRY(m, s) hover_skier_signed_init_defaults_defaults_##m##_##s,
#endif
