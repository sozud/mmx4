#ifndef MMX4_TESTS_PLAYER_ARCHIVE_CONTEXT_H
#define MMX4_TESTS_PLAYER_ARCHIVE_CONTEXT_H

static u32 keyframe = 0x2A010107u;
static u32* animations[0x80];
static s32 player_archive_context_sprite_archive[2] = { 4, 0x11223344 };
static Palette player_archive_context_palette_bank[4];
static u16 player_archive_context_palette_storage[0x152];
static u16* saved_palette;
static Palette* saved_bank;
static s32* saved_sprites;

static void begin_context(struct PlayerObj* obj)
{
    u32 i;
    memset(obj, 0, sizeof(*obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    saved_palette = SP_PALETTE;
    saved_bank = SP_PALETTE_BANK;
    saved_sprites = SP_SPRITE_FRAMES;
    TEST_PALETTE = (u8*)&player_archive_context_palette_storage[1];
    TEST_PALETTE_BANK = (u8*)player_archive_context_palette_bank;
    TEST_SPRITE_FRAMES = (u8*)player_archive_context_sprite_archive;
    for (i = 0; i < COUNT(animations); i++)
        animations[i] = &keyframe;
    for (i = 0; i < 4; i++) {
        u32 j;
        for (j = 0; j < 16; j++)
            player_archive_context_palette_bank[i][j] = 0x1200 + i * 16 + j;
    }
    for (i = 0; i < COUNT(player_archive_context_palette_storage); i++)
        player_archive_context_palette_storage[i] = 0xBEEF;
    need_palette_load = 0x80;
    obj->animation_table = animations;
    obj->animation_cursor = &keyframe;
}

static void end_context(void)
{
    assert(player_archive_context_palette_storage[0] == 0xBEEF && player_archive_context_palette_storage[0x151] == 0xBEEF);
    assert(player_archive_context_sprite_archive[0] == 4 && player_archive_context_sprite_archive[1] == 0x11223344);
    assert(keyframe == 0x2A010107u);
    TEST_PALETTE = (u8*)saved_palette;
    TEST_PALETTE_BANK = (u8*)saved_bank;
    TEST_SPRITE_FRAMES = (u8*)saved_sprites;
}

static u32 capsule_case(s8 animation)
{
    struct PlayerObj obj;
    u32 i, actual;
    begin_context(&obj);
    obj.capsule_state = 1;
    obj.unk17 = animation;
    obj.unk5 = 7;
    obj.unk6 = 9;
    obj.unk15 = 0x20;
    obj.afterimage = 1;
    obj.attacking = obj.shot_fired = obj.attack_ended = 1;
    obj.attack_pose_timer = obj.shot_cooldown = obj.shot_palette_timer = 1;
    obj.animation_step.packed = 0x07080004u;
    player_check_capsule(&obj);
    assert(obj.capsule_state == -1 && obj.afterimage == 0);
    assert(obj.attacking == 0 && obj.shot_fired == 0 && obj.attack_ended == 0);
    assert(obj.attack_pose_timer == 0 && obj.shot_cooldown == 0 && obj.shot_palette_timer == 0);
    assert(need_palette_load == 0x81);
    for (i = 0; i < 0x150; i++) {
        if (i < 16)
            assert(player_archive_context_palette_storage[i + 1] == 0x1200 + i);
        else if (i >= 0x130)
            assert(player_archive_context_palette_storage[i + 1] == 0x1210 + i - 0x130);
        else
            assert(player_archive_context_palette_storage[i + 1] == 0xBEEF);
    }
    if (animation == 5 || animation == 6 || animation == 0xC) {
        assert(obj.animation_step.packed == keyframe);
        assert(obj.animation_cursor == &keyframe && obj.previous_animation_index == 0xFF);
        assert(obj.unk3C == (u8*)&player_archive_context_sprite_archive[1]);
    } else
        assert(obj.animation_step.packed == 0x07080004u);
    actual = (u8)obj.unk17 | ((u32)(u8)obj.unk5 << 8) | ((u32)(u8)obj.unk6 << 16) | ((u32)obj.unk15 << 24);
    end_context();
    return actual;
}

static u32 capsule_hurt_blocked(void)
{
    struct PlayerObj obj, before;
    u32 i, actual;
    begin_context(&obj);
    obj.capsule_state = 1;
    obj.hurt_phase = 1;
    obj.unk5 = 7;
    obj.unk6 = 9;
    obj.unk15 = 0x20;
    obj.attacking = 1;
    before = obj;
    player_check_capsule(&obj);
    for (i = 0; i < sizeof(obj); i++)
        assert(((u8*)&obj)[i] == ((u8*)&before)[i]);
    for (i = 0; i < COUNT(player_archive_context_palette_storage); i++)
        assert(player_archive_context_palette_storage[i] == 0xBEEF);
    assert(need_palette_load == 0x80);
    actual = (u8)obj.capsule_state | ((u32)(u8)obj.hurt_phase << 8);
    assert(actual == 0x101u);
    end_context();
    return actual;
}

static u32 clone_case(u32 mode, u32 observation)
{
    struct PlayerObj obj;
    u32 actual;
    begin_context(&obj);
    obj.is_clone = 1;
    obj.unk5 = 7;
    obj.unk6 = 9;
    obj.x_pos.val = 300 * 65536 + 0x2468;
    obj.y_pos.val = 200 * 65536 + 0x1234;
    obj.clone_offset.value = mode == 3 ? 0x40 : 8;
    obj.unk88.bytes.collision_flags = mode == 1 ? PLAYER_COLLIDE_LEFT : mode == 2 ? PLAYER_COLLIDE_RIGHT | PLAYER_COLLIDE_GROUND
                                                                                  : 0;
    g_Player.unk15 = mode == 0 || mode == 2 ? 0x40 : 0;
    g_Player.x_pos.i.hi = 100;
    player_soul_body_clone_advance(&obj);
    assert(obj.x_pos.i.lo == 0x2468 && obj.y_pos.val == 200 * 65536 + 0x1234);
    assert(obj.unk15 == g_Player.unk15 && g_Player.x_pos.i.hi == 100);
    actual = observation == 0 ? (u32)obj.x_pos.val : (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)(u16)obj.clone_offset.value << 16);
    end_context();
    return actual;
}

#define ARCHIVE_CAPSULE(name, animation) \
    static u32 name(void)                \
    {                                    \
        return capsule_case(animation);  \
    }
#define ARCHIVE_CLONE(mode, observation)                                 \
    static u32 player_archive_context_clone_##mode##_##observation(void) \
    {                                                                    \
        return clone_case(mode, observation);                            \
    }
#define ARCHIVE_CLONE_ENTRY(mode, observation) player_archive_context_clone_##mode##_##observation,
#endif
