#include "test_runtime.h"
#include "main/weapons/weapon_04_rising_fire.h"
#include "support/state_cases.h"
#include "support/player_cases.h"
#include "main/player.h"
void rising_fire_charged_main(struct WeaponObj*);
extern u32* D_80137E08;
extern u8* D_80141EE8[6];
extern s32 player_gfx_buf_0[1024];

static u32 disabled(void)
{
    struct WeaponObj obj, before;
    struct PlayerObj player_before;
    struct Unk_unk68 box = { 1, 2, 3, 4 };
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.capsule_state = -1;
    g_Player.weapon = 0;
    g_Player.shot_type = 13;
    g_Player.shot_count = 3;
    g_Player.special_shot_count = 2;
    obj.active = 0x21;
    obj.id = 4;
    obj.unk2 = 0x27;
    obj.on_screen = 1;
    obj.unk5 = 0x28;
    obj.unk6 = 0x29;
    obj.unk7 = 0x2A;
    obj.unk50 = &box;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.unk64 = 0x2B;
    before = obj;
    player_before = g_Player;
    rising_fire_update(&obj);
    before.active = 0;
    before.id = 0;
    before.unk2 = 0;
    before.on_screen = 0;
    before.state = 0;
    before.unk5 = 0;
    before.unk6 = 0;
    before.unk7 = 0;
    before.unk50 = NULL;
    player_before.shot_count = g_Player.shot_count;
    player_before.special_shot_count = g_Player.special_shot_count;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(box.unk0 == 1 && box.unk1 == 2 && box.unk2 == 3 && box.unk3 == 4);
    actual = (u8)g_Player.shot_count | ((u32)(u8)g_Player.special_shot_count << 8);
    return actual;
}
static const CTestCase rising_fire_disable_state_cases[] = { disabled };
static const u32 rising_fire_disable_state_cases_expected[] = { 0x102u };

#define sw state_room.weapon
#define FLARE(step, pose, setup) (player_reset(1, 0, 0), memset(&state_room, 0, sizeof(state_room)), memset(&shot_objects[0], 0, sizeof(shot_objects[0])), memset(&effect_objects[0], 0, sizeof(effect_objects[0])), pl.unk17 = pose, sw.active = 1, sw.state = 1, sw.id = 0xD, sw.unk5 = step, sw.x_pos.i.hi = 100, sw.y_pos.i.hi = 200, sw.y_vel.val = -0x20000, setup, rising_fire_charged_main(&sw), state_extra = sw.ext.weapon_13.timer | (u8)sw.unk64 << 8 | (sw.unk50 != NULL) << 16)
static void rfc_follow(void)
{
    FLARE(0, 0x62, sw.ext.weapon_13.timer = 2);
}
static void rfc_launch(void) { FLARE(0, 0x67, sw.ext.weapon_13.timer = 0); }
static void rfc_rise(void) { FLARE(1, 0x62, (sw.animation_step.fields.event = 1, sw.animation_step.fields.duration = 9)); }
static void rfc_away(void) { FLARE(1, 0x62, sw.x_pos.i.hi = 0x1000); }

static void (*const rising_fire_charged_states_cases[])(void) = {
    rfc_follow,
    rfc_launch,
    rfc_rise,
    rfc_away,
};
static const u32 rising_fire_charged_states_expected[] = { 1u, 1u, 0x640000u, 0xC80000u, 0u, 0xFFFE0000u, 0u, 0xFF0000u, 1u, 0u, 0x101u, 1u, 0x640000u, 0xCA0000u, 0u, 0xFFFE0000u, 0u, 0xFF0000u, 0x104u, 0u, 0x101u, 1u, 0x640000u, 0xCA0000u, 0u, 0xFFFE0000u, 0u, 0x80000u, 0x10104u, 0u, 0x103u, 1u, 0x10000000u, 0xC80000u, 0u, 0xFFFE0000u, 0u, 0u, 0u, 0u };

static u32 test_rising_fire_charged_states(u32 row)
{
    return object_run(rising_fire_charged_states_cases[row], row, &rising_fire_charged_states_expected[row * 10]);
}

extern u32* D_8011C0B0[6];
extern struct Unk_unk68 rising_fire_hit_box[];
extern struct Unk_unk68 rising_fire_charged_hit_boxes[];

#define FRAMES 13

static struct {
    u32 root[8];
    u32 bank[FRAMES];
    u16 streams[FRAMES][24];
} archive;
static u32 sprites[32];
static struct WeaponObj obj, expected;
static struct PlayerObj player_expected;
static struct RectPtrPair uploads_expected[8];
static u32 queue_expected;

static void build_archive(void)
{
    u32 frame;
    c_test_zero_words((u32*)&archive, sizeof(archive) / 4);
    archive.root[5] = 0x20;
    for (frame = 0; frame < FRAMES; frame++) {
        u16* s = archive.streams[frame];
        u32 i;
        archive.bank[frame] = 1 << 20 | ((u8*)s - (u8*)archive.bank);
        for (i = 1; i <= 16; i++)
            s[i] = 0x1100 + frame;
        s[17] = 0x7000;
        s[18] = 0x1100 + frame;
        s[19] = 0x1001;
        s[21] = 2;
    }
}

static void prepare(u32 facing, u32 layer, u32 queue)
{
    u32 i;
    c_test_zero_words((u32*)&obj, sizeof(obj) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    c_test_zero_words((u32*)vram_rect_ptrs, sizeof(uploads_expected) / 4);
    for (i = 0; i < 24; i++)
        ((u16*)player_gfx_buf_1)[i] = 0xEEEE;
    build_archive();
    vram_rect_ptr = &vram_rect_ptrs[queue];
    sprites[13] = 0x40;
    TEST_PLAYER_GFX = (u8*)&archive;
    TEST_SPRITE_FRAMES = (u8*)sprites;
    background_objects[1].x_pos.i.hi = 1024;
    obj.active = 0x41;
    obj.id = 13;
    obj.bg_offset = layer;
    obj.on_screen = 1;
    obj.owner = &g_Player;
    obj.unk50 = rising_fire_hit_box;
    obj.x_pos.i.hi = 100 + (layer == 1 ? 1024 : 0);
    obj.y_pos.i.hi = 200;
    obj.unk15 = 0x40;
    g_Player.active = 0x41;
    g_Player.state = PLAYER_STATE_NORMAL;
    g_Player.weapon = 4;
    g_Player.bg_offset = layer;
    g_Player.unk15 = facing ? 0x40 : 0;
    g_Player.x_pos.i.hi = 160 + (layer == 1 ? 1024 : 0);
    g_Player.y_pos.i.hi = 120;
    g_Player.shot_count = 3;
    g_Player.special_shot_count = 2;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
}

static void capture(void)
{
    expected = obj;
    player_expected = g_Player;
    queue_expected = vram_rect_ptr - vram_rect_ptrs;
    c_test_copy_words((u32*)uploads_expected, (const u32*)vram_rect_ptrs, sizeof(uploads_expected) / 4);
}

static void check(void)
{
    c_test_same_words(&obj, &expected, sizeof(expected));
    c_test_same_words(&g_Player, &player_expected, sizeof(player_expected));
    c_test_same_words(vram_rect_ptrs, uploads_expected, sizeof(uploads_expected));
    assert(vram_rect_ptr == &vram_rect_ptrs[queue_expected]);
}

static void expect_animation(u32 animation, u32 frame)
{
    expected.unk17 = animation;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = D_8011C0B0[animation] + frame;
    expected.animation_step.packed = D_8011C0B0[animation][frame];
}

static void expect_init(u32 charged)
{
    s32 subtype = expected.unk2;
    expected.on_screen = 1;
    expected.unk64 = 1;
    expected.unk38 = (void*)archive.bank;
    expected.animation_table = D_8011C0B0;
    expected.unk40 = 0x520;
    expected.unk42 = 0x7801;
    expected.unk16 = 1;
    expected.unk3C = (u8*)sprites + 0x40;
    expected.x_vel.val = 0;
    expected.y_vel.val = 0x70000;
    expected.unk28.val = 0;
    expected.unk2C = 0;
    expected.unk67 = 1;
    expected.unk49 = 0;
    expected.unk5 = 0;
    expected.state = 1;
    if (charged) {
        expected.unk15 = g_Player.unk15;
        expected.x_pos = g_Player.x_pos;
        expected.y_pos = g_Player.y_pos;
        expected.ext.weapon_13.timer = 4;
        expect_animation(subtype ? 5 : 3, 0);
    } else {
        expected.unk50 = rising_fire_hit_box;
        expected.unk15 = 0;
        expected.x_pos.i.hi = g_Player.x_pos.i.hi + (g_Player.unk15 ? -1 : 1) * (subtype ? 6 : -11);
        expected.y_pos.i.hi = g_Player.y_pos.i.hi + (subtype ? -12 : -10);
        expect_animation(1, 0);
    }
}

static void expect_draw(void)
{
    u32 frame = expected.animation_step.fields.frame_index;
    struct RectPtrPair* upload;
    if (expected.previous_animation_index == frame)
        return;
    expected.previous_animation_index = frame;
    upload = &uploads_expected[queue_expected++];
    upload->rect.x = 320;
    upload->rect.y = 32;
    upload->rect.w = 4;
    upload->rect.h = 16;
    upload->ptr = (u_long*)player_gfx_buf_1;
    uploads_expected[queue_expected].ptr = NULL;
}

static void check_pixels(u32 frame)
{
    const u16* pixels = (const u16*)player_gfx_buf_1;
    u32 i;
    for (i = 0; i < 21; i++)
        assert(pixels[i] == (i < 19 ? 0x1100 + frame : 0));
}

static u32 init(u32 row)
{
    u32 subtype = row % 2, facing = (row / 2) % 2, layer = (row / 4) % 3, queue = ((row / 12) % 3) * 3, charged = row / 36;
    prepare(facing, layer, queue);
    obj.id = charged ? 13 : 4;
    obj.unk2 = subtype;
    capture();
    expect_init(charged);
    expect_draw();
    if (charged)
        rising_fire_charged_update(&obj);
    else
        rising_fire_update(&obj);
    check();
    check_pixels(obj.animation_step.fields.frame_index);
    return 1;
}

static u32 cancel(u32 row)
{
    u32 charged = row >= 15, mask = charged ? row - 14 : row + 1, i;
    prepare(0, 0, 3);
    obj.id = charged ? 13 : 4;
    obj.state = row % 4;
    g_Player.input_locked = (mask & 1) != 0;
    g_Player.capsule_state = (mask & 2) != 0;
    g_Player.weapon = mask & 4 ? 5 : 4;
    g_Player.shot_type = mask & 8 ? 13 : 0;
    capture();
    for (i = 0; i < 8; i++)
        ((u8*)&expected)[i] = 0;
    expected.unk50 = NULL;
    player_expected.shot_count--;
    player_expected.special_shot_count--;
    if (charged)
        rising_fire_charged_update(&obj);
    else
        rising_fire_update(&obj);
    check();
    return 1;
}

static u32 charged_frame(u32 row)
{
    static const u8 timers[] = { 0, 1, 4 };
    u32 sample = row, subtype = sample >= 17, frame = subtype ? sample - 17 : sample;
    u32 timer = row % 3, context = row / 3 % 3, duration = row / 9 % 2;
    u32 animation = subtype ? 5 : 3, current, next;
    prepare(0, frame % 3, timer * 3);
    obj.unk2 = subtype;
    expected = obj;
    expect_init(1);
    obj = expected;
    obj.unk5 = context == 2;
    obj.animation_cursor = D_8011C0B0[animation] + frame;
    obj.animation_step.packed = D_8011C0B0[animation][frame];
    if (duration)
        obj.animation_step.fields.duration = 1;
    current = obj.animation_step.fields.frame_index;
    obj.previous_animation_index = current;
    obj.unk50 = obj.animation_step.fields.event ? &rising_fire_charged_hit_boxes[(u8)obj.animation_step.fields.event] : NULL;
    obj.ext.weapon_13.timer = timers[timer];
    g_Player.unk17 = context == 1 ? 0x67 : 0x62;
    if (context != 2) {
        obj.x_pos.val += 0x10000;
        obj.y_pos.val += 0x20000;
    }
    capture();
    if (expected.animation_step.fields.duration == 1) {
        next = frame == (subtype ? 13 : 16) ? (subtype ? 2 : 5) : frame + 1;
        expected.animation_cursor = D_8011C0B0[animation] + next;
        expected.animation_step.packed = D_8011C0B0[animation][next];
    } else
        expected.animation_step.fields.duration--;
    if (context == 0) {
        expected.x_pos = g_Player.x_pos;
        expected.y_pos = g_Player.y_pos;
    } else {
        expected.x_pos.val += expected.x_vel.val;
        expected.y_pos.val -= expected.y_vel.val;
        if (context == 1)
            expected.unk5 = 1;
    }
    expected.unk50 = expected.animation_step.fields.event ? &rising_fire_charged_hit_boxes[(u8)expected.animation_step.fields.event] : NULL;
    expected.ext.weapon_13.timer = timers[timer] ? timers[timer] - 1 : 4;
    if (timers[timer] == 0)
        expected.unk64++;
    expect_draw();
    rising_fire_charged_update(&obj);
    check();
    if (obj.animation_step.fields.frame_index != current)
        check_pixels(obj.animation_step.fields.frame_index);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "rising_fire_charged_states", 0, 0, COUNT(rising_fire_charged_states_cases), test_rising_fire_charged_states },
    { "rising_fire_disable_state", rising_fire_disable_state_cases, rising_fire_disable_state_cases_expected, COUNT(rising_fire_disable_state_cases), 0 },
    { "rising_fire_initialization", NULL, NULL, 38, init },
    { "rising_fire_cancellation", NULL, NULL, 22, cancel },
    { "rising_fire_charged_frames", NULL, NULL, 31, charged_frame },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(rising_fire_charged_states_cases) + COUNT(rising_fire_disable_state_cases) + 38 + 22 + 31;
