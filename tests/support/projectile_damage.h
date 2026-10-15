#ifndef MMX4_TESTS_PROJECTILE_DAMAGE_H
#define MMX4_TESTS_PROJECTILE_DAMAGE_H

extern u8* dragon_spread_shot_animations[16];
extern void* frost_walrus_animations[39];
static u32 damage_case(u32 mode)
{
    struct ShotObj obj, before;
    struct WeaponObj owner, owner_before, weapons_before[16];
    struct VisualObj visuals_before[32];
    struct MiscObj misc_before[64];
    struct PlayerObj saved_player = g_Player, player_before;
    struct Unk_unk68 box = { -2, -2, 4, 4 };
    s8 saved_bank0 = D_8013E198[0], saved_bank2 = D_8013E198[2];
    u16 saved_random = cur_random;
    u32 i, kind = mode < 2 ? 0 : 1 + (mode - 2) / 3, hit = mode == 1 || (mode >= 2 && (mode - 2) % 3 != 0);
    u32 fatal = mode == 1 || (mode >= 2 && (mode - 2) % 3 == 1);
    u32 x = kind == 0 && !hit ? 500 : 100, y = 200;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(misc_objects, 0, sizeof(misc_objects));
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 0x27;
    }
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = 1;
        misc_objects[i].id = 0x27;
    }
    obj.active = 0x41;
    obj.id = kind == 0 ? 10 : 35;
    obj.state = 1;
    obj.unk5 = kind == 3 && mode != 9 ? 0 : 1;
    obj.unk6 = kind == 1 || kind == 2 ? 1 : 0;
    obj.bg_offset = -1;
    obj.unk42 = 0x9234;
    obj.unk5C = fatal ? 1 : 10;
    obj.unk54 = (const u8*)&box;
    obj.unk58.animation_steps = D_80105FF0;
    obj.x_pos.val = x * 65536 + 0x1234;
    obj.y_pos.val = y * 65536 + 0x5678;
    obj.x_vel.val = 65536;
    obj.y_vel.val = -32768;
    obj.unk2C = 0x1000;
    obj.unk84.value = 3;
    obj.animation_table = kind == 0 ? (const u8* const*)dragon_spread_shot_animations : (const u8* const*)frost_walrus_animations;
    set_animation(&obj, 0);
    owner.active = 0x41;
    owner.id = 57;
    owner.state = hit ? 1 : 2;
    owner.unk5 = hit ? 8 : 7;
    obj.unk7C = &owner;
    g_Player.spike_immune = 1;
    if (hit) {
        weapon_objects[0].active = 1;
        weapon_objects[0].id = 0;
        weapon_objects[0].unk50 = (const u8*)&box;
        weapon_objects[0].x_pos.val = obj.x_pos.val + (kind == 0 || kind == 2 || mode == 9 ? 65536 : 0);
        weapon_objects[0].y_pos.val = obj.y_pos.val + (kind == 0 || kind == 2 || mode == 9 ? 32768 : 0);
    }
    before = obj;
    owner_before = owner;
    player_before = g_Player;
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memcpy(misc_before, misc_objects, sizeof(misc_before));
    D_8013E198[0] = D_8013E198[2] = -1;
    cur_random = 0x1234;
    if (kind == 0)
        dragon_spread_shot_fly(&obj);
    else if (kind == 1)
        walrus_ice_ball_main(&obj);
    else if (kind == 2)
        walrus_ice_chunk_main(&obj);
    else
        walrus_ice_lob(&obj);
    if (kind == 0 || kind == 2 || mode == 9) {
        before.x_pos.val += 65536;
        before.y_pos.val += 32768;
    }
    if (kind != 0) {
        before.unk18.val = x * 65536 + 0x1234;
        before.unk1C.val = y * 65536 + 0x5678;
        before.on_screen = 1;
    }
    if (kind == 2 || mode == 9)
        before.y_vel.val -= 0x1000;
    if (kind == 3 && mode != 9) {
        before.x_vel.val = 3 * 65536;
        before.y_vel.val = 0x68000;
        before.unk28 = 0;
        before.unk2C = 0x4200;
        before.unk5C = 5;
        before.unk60 = 6;
        before.unk68 = &walrus_ice_lob_terrain_box;
        before.unk54 = (const u8*)&walrus_ice_icicle_hurt_box;
        before.unk50.data = (const u8*)&walrus_ice_icicle_attack_box;
        before.unk16 = 2;
        before.unk5 = 1;
        before.unk17 = 10;
        before.previous_animation_index = 0xFF;
        before.animation_cursor = frost_walrus_animations[10];
        before.animation_step = *(union AnimationStep*)frost_walrus_animations[10];
    }
    if (hit) {
        before.unk5C = fatal ? 0 : kind == 3 ? 2
                                             : 7;
        before.unk42 = kind == 0 || !fatal ? 0x9234 : 0x1234;
        weapons_before[0].unk98 = 1;
        weapons_before[0].unk80.word = (u16)(x + (kind == 0 || kind == 2 || mode == 9 ? 1 : 0)) | ((u32)y << 16);
    } else
        before.unk42 = 0x1234;
    if (kind == 0) {
        before.state = 2;
        if (!hit)
            before.unk84.value = 4;
    } else if (!hit || fatal) {
        before.state = 6;
        before.unk5 = before.unk6 = 0;
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(weapons_before) / 4; i++)
        assert(((u32*)weapon_objects)[i] == ((u32*)weapons_before)[i]);
    for (i = 0; i < sizeof(visuals_before) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)visuals_before)[i]);
    for (i = 0; i < sizeof(misc_before) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)misc_before)[i]);
    assert(cur_random == (kind == 0 && hit ? 0x366A : 0x1234));
    assert(D_8013E198[0] == -1 && D_8013E198[2] == -1);
    D_8013E198[0] = saved_bank0;
    D_8013E198[2] = saved_bank2;
    cur_random = saved_random;
    g_Player = saved_player;
    return (u8)obj.state | ((u32)(u8)obj.unk5C << 8) | ((u32)(u8)obj.on_screen << 16) | ((u32)obj.unk42 << 16);
}
#define DAMAGE_CASE(m)                                      \
    static u32 projectile_damage_and_owner_damage_##m(void) \
    {                                                       \
        return damage_case(m);                              \
    }
#define DAMAGE_ENTRY(m) projectile_damage_and_owner_damage_##m,
#endif
