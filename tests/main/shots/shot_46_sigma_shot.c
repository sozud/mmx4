#include "test_runtime.h"
#include "main/collision_bounds.h"
#include "main/sprite_animations.h"
extern void (*sigma_bolt_funcs[])(struct ShotObj*);
extern void (*sigma_dart_funcs[])(struct ShotObj*);
void sigma_bolt_gather(struct ShotObj*);
void sigma_dart_fly(struct ShotObj*);
void sigma_dart_wait(struct ShotObj*);
void sigma_shot_bolt(struct ShotObj*);
void sigma_shot_cloak_fire(struct ShotObj*);
void sigma_shot_cloak_scythe(struct ShotObj*);
void sigma_shot_dart(struct ShotObj*);
void sigma_shot_drift(struct ShotObj*);
void sigma_shot_dropped_scythe(struct ShotObj*);
void sigma_shot_planted_scythe(struct ShotObj*);
#include "main/shots/shot_46_sigma_shot.h"

static const u32 func_800A9544_expected[] = { 2u, 0xFFFFFFA6u, 0u, 0x30u, 0xFFFFFFE0u };
static u32 test_func_800A9544(u32 row)
{
    u32 observed_values[5];
    struct ShotObj obj;
    struct WeaponObj child_0;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk94 = 7;
    obj.unk96 = 1;
    obj.unk15 = 255;
    child_0.y_pos.i.hi = 10;
    child_0.state = 2;
    obj.unk7C = &child_0;
    func_800A9544(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk90.i.hi;
    observed_values[2] = (u32)obj.unk90.i.lo;
    observed_values[3] = (u32)obj.x_pos.i.hi;
    observed_values[4] = (u32)obj.y_pos.i.hi;
    return c_test_observe(0, row, observed_values, func_800A9544_expected, 5);
}

static const u32 inputs_0[2][4] = {
    { 255, 0, 0, 0 },
    { 255, 0, 0, -1 },
};
struct sigma_shot_flash_case {
    u32 expected[3];
};
static const struct sigma_shot_flash_case sigma_shot_flash_cases[] = {
    { { 2u, 0u, 0u } },
    { { 0u, 0u, 0u } },
};
static u32 test_sigma_shot_flash(u32 row)
{
    const struct sigma_shot_flash_case* c = &sigma_shot_flash_cases[row];
    u32 observed_values[3];
    struct ShotObj obj;
    struct WeaponObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    child_0_present = inputs_0[row][0];
    child_0.x_pos.u.hi = inputs_0[row][1];
    child_0.y_pos.u.hi = inputs_0[row][2];
    obj.animation_step.fields.relative_step = inputs_0[row][3];
    obj.unk7C = child_0_present ? &child_0 : NULL;
    sigma_shot_flash(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.x_pos.u.hi;
    observed_values[2] = (u32)obj.y_pos.u.hi;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

extern void* sigma_animations[44];
extern struct Unk_unk68 lemon_hit_box[1];
s32 sigma_shot_at_position(struct ShotObj*, s32, s32);
extern s8 sigma_shot_boxes[10][4];
extern u8 sigma_shot_init_box[4], sigma_shot_debris[20];
struct ShotInit {
    u8 animation, frame, damage;
    s8 attack, hurt, terrain, collision;
    u32 word;
};
static const struct ShotInit init_rules[11] = {
    { 5, 0, 9, -1, -1, -1, 0, 0x01010001 },
    { 3, 0, 6, 1, -1, 0, 1, 0x1E010003 },
    { 3, 0, 6, 1, -1, 0, 1, 0x1E010003 },
    { 30, 0, 9, 5, -1, 6, 0, 0x56010001 },
    { 35, 0, 6, 8, -1, -1, 0, 0x73010002 },
    { 37, 0, 6, 7, -1, -1, 0, 0x7E010002 },
    { 33, 2, 6, 2, 3, -1, 2, 0x69010001 },
    { 30, 0, 9, 5, -1, -1, 0, 0x56010001 },
    { 38, 0, 9, 9, -1, -1, 0, 0x82010001 },
    { 30, 0, 18, -1, -1, 6, 0, 0x56010001 },
    { 42, 0, 18, -1, -1, -1, 0, 0x8E010001 },
};
struct ShotAim {
    s16 dx, dy;
    u8 result;
    s32 vx, vy;
};
static const struct ShotAim aims[7] = {
    { 192, 0, 0, 0x10000, 0 },
    { 0, -16, 0, 0x10000, 0 },
    { -3, -16, 16, -0x10000, 0 },
    { -192, 0, 16, -0x10000, 0 },
    { -80, 16, 17, -0xFB14, -0x31F1 },
    { 0, 16, 24, 0, -0x10000 },
    { 80, 16, 31, 0xFB14, -0x31F1 },
};
static const s8 boxes[10][4] = {
    { 0, -1, 10, 10 },
    { -7, -8, 13, 14 },
    { -6, -7, 11, 12 },
    { -10, -10, 19, 19 },
    { -25, 82, 71, 24 },
    { -23, -25, 46, 48 },
    { 0, -11, 18, 14 },
    { -31, -5, 62, 7 },
    { -4, -33, 7, 63 },
    { -128, -18, -116, 25 },
};
static const u8 animation_lengths[44] = {
    4, 8, 3, 3, 1, 3, 38, 3, 2, 2, 11, 4, 4, 2, 9, 7,
    4, 4, 2, 2, 5, 4, 4, 2, 2, 5, 7, 8, 5, 2, 4, 3,
    3, 12, 7, 4, 7, 4, 6, 1, 1, 1, 4, 7
};
static const s8 dart_offsets[4] = { -35, -15, 15, 35 };
static struct {
    u32 before;
    struct ShotObj value;
    u32 after;
} guarded;
#define shot guarded.value
static struct ShotObj want, shots_before[32];
static u16 random_want;
static struct VisualObj visuals_want[32];
static union {
    struct QuadObj quad;
    struct WeaponObj storage;
} parent, parent_before;
static struct MainObj owner, owner_want;
static struct PlayerObj player_before, entity_before;
static struct EngineObj engine_before;
static struct MainBssState main_before;
static struct BackgroundObj backgrounds_before[3];
static u32 animation_before[224], sprites[4], commands[32];
static void* table_before[44];
#ifndef MMX4_PC
extern u8 D_80141F58[16];
static u32 sound_tail_want[4];
#endif

static void seed(u32 type, u32 facing, u32 layer)
{
    u32 i;
    c_test_zero_words((u32*)&owner, sizeof(owner) / 4);
    c_test_zero_words((u32*)&parent, sizeof(parent) / 4);
    memset(&guarded, 0xA5, sizeof(guarded));
    guarded.before = 0x12345678;
    guarded.after = 0x87654321;
    owner.active = 0x41;
    owner.id = 68;
    owner.state = 1;
    owner.bg_offset = layer == 0 ? -1 : layer - 1;
    owner.unk15 = facing * 0x40;
    owner.x_pos.val = (layer == 2 ? 1224 : 200) * 65536 + 0x1234;
    owner.y_pos.val = 120 * 65536 + 0x5678;
    owner.unk40 = 0x4567;
    owner.unk42 = 0x9234;
    owner.animation_table = (const u8* const*)sigma_animations;
    owner.sprite_frames = (u8*)sprites;
    owner.ext.main_68.active_shots = owner.ext.main_68.count = 2;
    parent.quad.x_pos.val = 300 * 65536 + 0xBEEF;
    parent.quad.y_pos.val = 100 * 65536 + 0xCAFE;
    parent.quad.vertices[2].x.val = -20 * 65536 + 0x1234;
    parent.quad.vertices[2].y.val = 30 * 65536 + 0x5678;
    parent.quad.unk5C = (struct PlayerObj*)&owner;
    shot.active = 0x41;
    shot.id = 46;
    shot.state = 0;
    shot.unk2 = type;
    shot.unk5 = 0;
    shot.unk15 = facing * 0x40;
    shot.bg_offset = owner.bg_offset;
    shot.on_screen = 0;
    shot.x_pos = owner.x_pos;
    shot.y_pos = owner.y_pos;
    shot.x_vel.val = 0x23456;
    shot.y_vel.val = -0x34567;
    shot.unk28 = 0x456;
    shot.unk2C = -0x567;
    shot.unk60 = 18;
    shot.timer = 2;
    shot.unk99 = facing;
    shot.unk9A = 0;
    shot.animation_table = (u32**)sigma_animations;
    shot.unk17 = init_rules[type].animation;
    shot.animation_cursor = (u32*)sigma_animations[shot.unk17] + init_rules[type].frame;
    shot.animation_step.packed = init_rules[type].word;
    shot.unk7C = (struct WeaponObj*)&owner;
    if (type == 8)
        shot.unk7C = (struct WeaponObj*)&parent.quad;
    for (i = 0; i < 3; i++) {
        background_objects[i].x_pos.val = i * 1024 * 65536;
        background_objects[i].y_pos.val = 0;
    }
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].unk50 = &g_Entity;
        visual_objects[i].x_pos.val = 0x12345678;
    }
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    c_test_zero_words(commands, COUNT(commands));
    D_80141F50[1] = (u8*)commands;
#ifdef MMX4_PC
    D_80141F50[2] = (u8*)commands;
#else
    c_test_copy_words(sound_tail_want, (u32*)D_80141F58, 4);
    sound_tail_want[0] = (u32)commands;
    memcpy(D_80141F58, sound_tail_want, sizeof(sound_tail_want));
#endif
    cur_random = random_want = 0x1234;
    need_palette_load = 0x20;
    controller_input.held = 0x1234;
    controller_input.previous = 0x5678;
    controller_input.pressed = 0x840;
}
static void capture(void)
{
    u32 i, n = 0;
    want = shot;
    owner_want = owner;
    parent_before = parent;
    player_before = g_Player;
    entity_before = g_Entity;
    engine_before = engine_obj;
    main_before = main_bss_state;
    c_test_copy_words((u32*)backgrounds_before, (u32*)background_objects, sizeof(backgrounds_before) / 4);
    c_test_copy_words((u32*)shots_before, (u32*)shot_objects, sizeof(shots_before) / 4);
    c_test_copy_words((u32*)visuals_want, (u32*)visual_objects, sizeof(visuals_want) / 4);
    c_test_copy_words((u32*)table_before, (u32*)sigma_animations, sizeof(table_before) / 4);
    for (i = 0; i < 44; i++) {
        c_test_copy_words(animation_before + n, sigma_animations[i], animation_lengths[i]);
        n += animation_lengths[i];
    }
    assert(n == COUNT(animation_before));
}
static void check(void)
{
    u32 i, j, n = 0;
    c_test_same_words(&shot, &want, sizeof(want));
    c_test_same_words(&owner, &owner_want, sizeof(owner));
    c_test_same_words(&parent, &parent_before, sizeof(parent));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&g_Entity, &entity_before, sizeof(g_Entity));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_bss_state));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    c_test_same_words(shot_objects, shots_before, sizeof(shots_before));
    c_test_same_words(visual_objects, visuals_want, sizeof(visuals_want));
    c_test_same_words(sigma_animations, table_before, sizeof(table_before));
    for (i = 0; i < 44; i++) {
        c_test_same_words(sigma_animations[i], animation_before + n, animation_lengths[i] * 4);
        n += animation_lengths[i];
    }
    for (i = 0; i < 10; i++)
        for (j = 0; j < 4; j++)
            assert(sigma_shot_boxes[i][j] == boxes[i][j]);
    for (i = 0; i < 4; i++)
        assert((s8)sigma_shot_init_box[i] == dart_offsets[i] && sprites[i] == 0);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    for (i = 0; i < 32; i++)
        assert(commands[i] == 0);
    assert(guarded.before == 0x12345678 && guarded.after == 0x87654321);
    assert(cur_random == random_want && need_palette_load == 0x20 && D_80141F50[1] == (u8*)commands);
#ifdef MMX4_PC
    assert(D_80141F50[2] == (u8*)commands);
#else
    c_test_same_words(D_80141F58, sound_tail_want, sizeof(sound_tail_want));
#endif
    assert(controller_input.held == 0x1234 && controller_input.previous == 0x5678 && controller_input.pressed == 0x840);
}
static u32 test_sigma_init(u32 row)
{
    u32 type = row % 11, a = (row / 11) % 7, facing = (type + a) % 2, layer = facing;
    const struct ShotInit* c = &init_rules[type];
    seed(type, facing, layer);
    shot.timer = row / 77;
    g_Player.x_pos.val = owner.x_pos.val + aims[a].dx * 65536;
    g_Player.y_pos.val = owner.y_pos.val + aims[a].dy * 65536;
    capture();
    want.state = 1;
    want.unk40 = owner.unk40;
    want.unk42 = owner.unk42;
    want.unk15 = owner.unk15;
    want.animation_table = (u32**)sigma_animations;
    want.unk3C = sprites;
    want.bg_offset = owner.bg_offset;
    want.x_pos = owner.x_pos;
    want.y_pos = owner.y_pos;
    want.unk16 = 5;
    want.unk58.data = c->collision == 1 ? (u8*)D_80106070 : c->collision == 2 ? (u8*)D_801060F0
                                                                              : 0;
    want.unk50.data = c->attack < 0 ? 0 : (u8*)sigma_shot_boxes[c->attack];
    want.unk54 = c->hurt < 0 ? 0 : (u8*)sigma_shot_boxes[c->hurt];
    want.unk68 = c->terrain < 0 ? 0 : (struct Unk_unk68*)sigma_shot_boxes[c->terrain];
    want.unk60 = c->damage;
    if (type == 3) {
        want.unk94 = aims[a].result;
        want.x_pos.i.hi += facing ? 33 : -33;
        want.y_pos.i.hi -= 21;
        want.x_vel.val = aims[a].vx;
        want.y_vel.val = aims[a].vy;
    }
    if (type == 4 || type == 5) {
        want.x_vel.val = type == 5 ? (shot.timer ? 0x80000 : -0x80000) : 0;
        want.y_vel.val = type == 4 ? (shot.timer ? 0x80000 : -0x80000) : 0;
    }
    if (type == 6) {
        want.unk95 = shot.timer;
        want.unk90.i.lo = owner.x_pos.i.hi + (facing ? -1 : 1) * dart_offsets[shot.timer];
        want.unk90.i.hi = owner.y_pos.i.hi - 64;
    }
    if (type == 7) {
        want.unk96 = 6;
        want.unk94 = facing ? 5 : 7;
    }
    if (type == 8) {
        want.unk15 ^= 0x40;
        want.x_pos.u.lo = 0xBEEF;
        want.y_pos.u.lo = 0xCAFE;
        want.x_pos.i.hi = 284;
        want.y_pos.i.hi = 122;
    }
    if (type == 9) {
        want.x_vel.val = want.unk28 = 0;
        want.y_vel.val = 0x60000;
        want.unk2C = 0x4200;
    }
    want.unk17 = c->animation;
    want.previous_animation_index = 0xFF;
    want.animation_cursor = (u32*)sigma_animations[c->animation] + c->frame;
    want.animation_step.packed = c->word;
    assert(((u32*)sigma_animations[c->animation])[c->frame] == c->word);
    sigma_shot_update(&shot);
    check();
    return 1;
}
static u32 test_sigma_bolt_edges(u32 row)
{
    static const u8 hits[5] = { 0, 1, 2, 3, 8 };
    u32 type = row % 2 + 1, facing = (row / 2) % 2, phase = (row / 4) % 5 + 1;
    seed(type, facing, 0);
    shot.state = 1;
    shot.unk5 = phase;
    shot.unk70 = hits[(row / 20) % 5];
    shot.timer = row / 100 + 1;
    capture();
    if (phase == 1) {
        want.animation_step.fields.duration--;
        want.timer--;
        if (!want.timer) {
            want.unk5 += type == 1 ? 1 : 2;
            want.x_vel.val = type == 1 ? (facing ? -0x50000 : 0x50000) : 0;
            want.y_vel.val = type == 1 ? 0 : -0x50000;
        }
    } else if ((phase == 2 || phase == 4) && (shot.unk70 & 3)) {
        want.unk5++;
        want.x_vel.val = 0;
        want.y_vel.val = phase == 2 ? -0x50000 : 0x50000;
    } else if (phase == 3 && (shot.unk70 & 8)) {
        want.unk5++;
        want.y_vel.val = 0;
        want.x_vel.val = (facing == (type == 1)) ? 0x50000 : -0x50000;
    }
    sigma_bolt_funcs[phase](&shot);
    check();
    return 1;
}
static u32 test_sigma_despawn(u32 row)
{
    u32 type = row % 11;
    seed(type, (row / 11) % 2, 0);
    shot.state = 2;
    owner.ext.main_68.active_shots = owner.ext.main_68.count = row / 22 + 1;
    capture();
    if (type == 1 || type == 2)
        owner_want.ext.main_68.active_shots--;
    if (type == 6)
        owner_want.ext.main_68.count--;
    want.active = want.id = want.unk2 = want.on_screen = want.state = want.unk5 = want.unk6 = want.unk7 = 0;
    sigma_shot_update(&shot);
    check();
    return 1;
}
static u32 test_sigma_position(u32 row)
{
    static const s32 offsets[6] = { -0x30000, -0x2FFFF, -1, 0, 0x2FFFF, 0x30000 };
    u32 x = row % 6, y = (row / 6) % 6;
    seed(0, 0, row / 36);
    capture();
    assert(sigma_shot_at_position(&shot, shot.x_pos.val + offsets[x], shot.y_pos.val + offsets[y]) == (x > 0 && x < 5 && y > 0 && y < 5));
    check();
    return 1;
}
static u32 test_sigma_wait(u32 row)
{
    seed(6, row % 2, row / 4);
    shot.state = 1;
    shot.unk5 = 1;
    shot.timer = (row / 2) % 2 + 1;
    g_Player.x_pos.val = -100 * 65536 + 0xCAFE;
    g_Player.y_pos.val = 300 * 65536 + 0xBEEF;
    capture();
    want.timer--;
    if (!want.timer) {
        want.unk5++;
        want.unk90.i.lo = -100;
        want.unk90.i.hi = 300;
    }
    sigma_dart_wait(&shot);
    check();
    return 1;
}
static u32 test_sigma_motion(u32 row)
{
    u32 drift = row % 2;
    seed(drift ? 4 : 6, (row / 2) % 2, row / 4);
    shot.state = 1;
    capture();
    want.animation_step.fields.duration--;
    want.x_pos.val += shot.x_vel.val;
    want.y_pos.val -= shot.y_vel.val;
    if (!drift) {
        want.animation_cursor = (u32*)sigma_animations[33] + 3;
        want.animation_step.packed = 0x68010001;
    }
    if (drift)
        want.on_screen = 1;
    if (drift)
        sigma_shot_drift(&shot);
    else
        sigma_dart_fly(&shot);
    check();
    return 1;
}

static const u8 live_angles[7] = { 0, 8, 9, 16, 17, 24, 31 };
static const s32 live_vectors[7][2] = {
    { 0x10000, 0 },
    { 0, 0x10000 },
    { -0x31F1, 0xFB14 },
    { -0x10000, 0 },
    { -0xFB14, -0x31F1 },
    { 0, -0x10000 },
    { 0xFB14, -0x31F1 },
};
static void install_step(u32 animation, u32 frame, u32 word)
{
    shot.unk17 = animation;
    shot.animation_cursor = (u32*)sigma_animations[animation] + frame;
    shot.animation_step.packed = word;
    assert(((u32*)sigma_animations[animation])[frame] == word);
}
static void expect_step(u32 frame, u32 word)
{
    want.animation_cursor = (u32*)sigma_animations[want.unk17] + frame;
    want.animation_step.packed = word;
    assert(((u32*)sigma_animations[want.unk17])[frame] == word);
}
static u32 test_planted_scythe(u32 row)
{
    u32 mode = row % 3, a = (row / 3) % 8, facing = (mode + a) % 2, layer = facing;
    u32 available = row / 24 == 1, dead = row / 24 == 2, direction = a == 7 ? 0 : a;
    seed(3, facing, layer);
    shot.state = 1;
    shot.unk5 = mode + 1;
    shot.timer = a / 3;
    shot.unk95 = a % 3 + 2;
    owner.state = dead ? 2 : 1;
    owner.ext.main_68.scythe = (struct MainObj*)&shot;
    if (available)
        visual_objects[31].active = 0;
    if (mode == 0 && (a & 1))
        install_step(30, 3, 0x59FD0001);
    if (mode == 2) {
        shot.x_pos.val = owner.x_pos.val - (a == 7 ? 6 : aims[a].dx) * 65536;
        shot.y_pos.val = owner.y_pos.val - (a == 7 ? 0 : aims[a].dy) * 65536;
    }
    capture();
    want.on_screen = mode == 2 && a == 3 ? 0 : 1;
    if (mode == 0) {
        owner_want.ext.main_68.next_attack = shot.unk95 - 2;
        expect_step((a & 1) ? 0 : 1, (a & 1) ? 0x56010001 : 0x57010001);
        if (--want.timer == 0 && available) {
            visuals_want[31].active = 0x41;
            visuals_want[31].id = 0x20;
            visuals_want[31].unk2 = shot.unk95;
            visuals_want[31].unk50 = (struct PlayerObj*)&shot;
            want.timer = shot.unk95 == 4 ? 36 : 24;
        }
    } else if (mode == 1) {
        want.unk5++;
        want.unk90.i.lo = owner.x_pos.i.hi + (facing ? 33 : -33);
        want.unk90.i.hi = owner.y_pos.i.hi - 21;
        want.unk17 = 30;
        want.previous_animation_index = 0xFF;
        expect_step(0, 0x56010001);
    } else {
        want.unk94 = live_angles[direction];
        want.x_vel.val = live_vectors[direction][0] * 6;
        want.y_vel.val = live_vectors[direction][1] * 6;
        want.x_pos.val += want.x_vel.val;
        want.y_pos.val -= want.y_vel.val;
        expect_step(1, 0x57010001);
        if (a == 7) {
            want.state = 2;
            owner_want.ext.main_68.scythe = 0;
        }
    }
    if (dead)
        want.state = 2;
    sigma_shot_planted_scythe(&shot);
    check();
    return 1;
}
static u32 test_dart_attack(u32 row)
{
    u32 mode = row % 3, a = (row / 3) % 8, facing = (row / 24) % 2, layer = facing;
    u32 hit = (row / 96) % 2, index = row / 192, direction = a == 7 ? 0 : a;
    seed(6, facing, layer);
    shot.state = 1;
    shot.unk5 = mode == 0 ? 0 : mode + 1;
    shot.timer = (row / 48) % 2 + 1;
    shot.unk98 = hit;
    shot.unk95 = index;
    shot.unk90.i.lo = owner.x_pos.i.hi;
    shot.unk90.i.hi = owner.y_pos.i.hi;
    shot.x_pos.val = ((s32)owner.x_pos.i.hi - (a == 7 ? 1 : aims[a].dx)) * 65536;
    shot.y_pos.val = ((s32)owner.y_pos.i.hi - (a == 7 ? 0 : aims[a].dy)) * 65536;
    g_Player.x_pos.val = (s32)owner.x_pos.i.hi * 65536;
    g_Player.y_pos.val = (s32)owner.y_pos.i.hi * 65536;
    capture();
    if (mode < 2 || shot.timer == 1) {
        want.unk94 = live_angles[direction];
        want.x_vel.val = live_vectors[direction][0] * (mode == 0 ? 3 : 6);
        want.y_vel.val = live_vectors[direction][1] * (mode == 0 ? 3 : 6);
    }
    if (mode == 0) {
        want.x_pos.val += want.x_vel.val;
        want.y_pos.val -= want.y_vel.val;
        if (a == 7) {
            want.unk5++;
            want.timer = (index + 1) * 40;
        }
    } else if (mode == 1) {
        if (a == 7 || hit) {
            want.unk5++;
            want.timer = 240;
        }
        want.x_pos.val += want.x_vel.val;
        want.y_pos.val -= want.y_vel.val;
        expect_step(3, 0x68010001);
    } else {
        if (--want.timer == 0)
            want.unk5++;
        expect_step(3, 0x68010001);
    }
    sigma_dart_funcs[shot.unk5](&shot);
    check();
    return 1;
}
static u32 test_dropped_scythe(u32 row)
{
    u32 scene = row % 6, facing = (row / 6) % 2;
    seed(9, facing, row / 12);
    shot.state = 1;
    shot.unk5 = scene < 3 ? 0 : scene < 5 ? 1
                                          : 2;
    shot.x_vel.val = shot.unk28 = 0;
    shot.unk2C = 0x4200;
    shot.unk70 = scene == 4 ? 8 : 0;
    shot.y_vel.val = scene < 3 ? 0x4200 + (s32)scene - 1 : -0x10000;
    capture();
    want.on_screen = 1;
    if (scene < 5) {
        want.y_pos.val -= shot.y_vel.val;
        want.y_vel.val -= 0x4200;
        expect_step(1, 0x57010001);
        if (scene == 0) {
            want.y_vel.val = 0;
            want.unk5 = 1;
        }
        if (scene == 4) {
            want.unk5 = 2;
            want.unk17 = 32;
            want.previous_animation_index = 0xFF;
            expect_step(0, 0x5D010001);
        }
    }
    sigma_shot_dropped_scythe(&shot);
    check();
    return 1;
}
static u32 test_cloak_scythe(u32 row)
{
    u32 event = row % 2, visible = (row / 2) % 2, facing = (row / 4) % 2;
    seed(0, facing, row / 8);
    shot.state = 1;
    owner.on_screen = visible;
    shot.unk15 ^= 0x40;
    shot.x_pos.val += 0x12345;
    shot.y_pos.val -= 0x23456;
    if (event)
        install_step(6, 35, 0x12010101);
    capture();
    want.x_pos = owner.x_pos;
    want.y_pos = owner.y_pos;
    want.unk15 = owner.unk15;
    want.on_screen = visible;
    want.unk50.data = event && visible ? (u8*)sigma_shot_boxes[4] : 0;
    expect_step(event ? 36 : 1, event ? 0x13010101 : 0x02010001);
    sigma_shot_cloak_scythe(&shot);
    check();
    return 1;
}

static const s8 orbit[16][2] = {
    { 64, 64 },
    { 83, 34 },
    { 90, 0 },
    { 83, -35 },
    { 64, -64 },
    { 34, -84 },
    { 0, -90 },
    { -35, -84 },
    { -64, -64 },
    { -84, -35 },
    { -90, 0 },
    { -84, 34 },
    { -64, 64 },
    { -35, 83 },
    { 0, 90 },
    { 34, 83 },
};
static u32 test_scythe_orbit(u32 row)
{
    u32 angle = row % 16, delay = (row / 16) % 2 + 1, facing = (row / 32) % 2, dead = (row / 64) % 2;
    seed(7, facing, row / 128);
    shot.state = 1;
    shot.unk94 = angle;
    shot.unk96 = delay;
    owner.state = dead ? 2 : 1;
    capture();
    if (delay == 1)
        angle = (angle + (facing ? 15 : 1)) % 16;
    want.unk94 = angle;
    want.unk96 = delay == 1 ? 6 : 1;
    want.unk90.i.lo = orbit[angle][0];
    want.unk90.i.hi = orbit[angle][1];
    want.x_pos.i.hi = owner.x_pos.i.hi + orbit[angle][0] + (facing ? 48 : -48);
    want.y_pos.i.hi = owner.y_pos.i.hi + orbit[angle][1] + 48;
    want.on_screen = 1;
    if (angle == 6 || dead)
        want.state = 2;
    expect_step(1, 0x57010001);
    func_800A9544(&shot);
    check();
    return 1;
}
static u32 test_bolt_gather(u32 row)
{
    static const s32 distances[6] = { -0x30000, -0x2FFFF, -0x10000, 0x10000, 0x2FFFF, 0x30000 };
    u32 d = row % 6, type = (row / 6) % 2 + 1, facing = (row / 12) % 2, vertical = (row / 24) % 2, axis = (row / 48) % 2;
    s32 dx = axis ? 0 : distances[d], dy = axis ? distances[d] : 0;
    seed(type, facing, row / 96);
    shot.state = 1;
    shot.unk9A = vertical;
    shot.x_pos.val += (facing ? -1 : 1) * (type == 1 ? 32 : 16) * 65536 - dx;
    shot.y_pos.val += (type == 1 ? (vertical ? 0 : 32) : 40) * 65536 - dy;
    capture();
    want.x_vel.val = axis ? 0 : (dx > 0 ? 0x10000 : -0x10000);
    want.y_vel.val = axis ? (dy > 0 ? -0x10000 : 0x10000) : 0;
    if (d > 0 && d < 5) {
        want.timer = 20;
        want.unk5 = 1;
    }
    sigma_bolt_gather(&shot);
    check();
    return 1;
}
static u32 test_sigma_run(u32 row)
{
    static const struct {
        s16 x, y;
        u8 visible, far;
    } positions[16] = {
        { -65, 120, 0, 1 },
        { -64, 120, 0, 0 },
        { -33, 120, 0, 0 },
        { -32, 120, 1, 0 },
        { 351, 120, 1, 0 },
        { 352, 120, 0, 0 },
        { 383, 120, 0, 0 },
        { 384, 120, 0, 1 },
        { 200, -65, 0, 1 },
        { 200, -64, 0, 0 },
        { 200, -33, 0, 0 },
        { 200, -32, 1, 0 },
        { 200, 271, 1, 0 },
        { 200, 272, 0, 0 },
        { 200, 303, 0, 0 },
        { 200, 304, 0, 1 },
    };
    u32 p = row % 16, phase = row / 16, type = phase != 0, facing = phase == 1, layer = facing, contact = phase == 2;
    type = type == 0 ? 0 : type + 3;
    seed(type, facing, layer);
    shot.state = 1;
    shot.x_pos.i.hi = positions[p].x + (layer == 2 ? 1024 : 0);
    shot.y_pos.i.hi = positions[p].y;
    owner.x_pos = shot.x_pos;
    owner.y_pos = shot.y_pos;
    owner.on_screen = 1;
    shot.x_vel.val = shot.y_vel.val = 0;
    shot.unk68 = 0;
    shot.unk42 = 0x9234;
    shot.unk62 = 0;
    shot.unk60 = 6;
    shot.unk50.data = type ? (u8*)sigma_shot_boxes[init_rules[type].attack] : 0;
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    g_Player.hp = 24;
    g_Player.unk54 = type ? (const u32*)shot.unk50.data : 0;
    g_Player.unk15 = shot.unk15;
    g_Player.x_pos.val = shot.x_pos.val + (contact ? 0 : 512 * 65536);
    g_Player.y_pos = shot.y_pos;
    g_Player.stun_timer = 9;
    g_Player.hurt_type = 7;
    g_Player.hit_facing = 0x33;
    capture();
    want.unk18 = shot.x_pos;
    want.unk1C = shot.y_pos;
    want.unk42 = 0x1234;
    want.on_screen = positions[p].visible;
    if (type) {
        want.animation_step.fields.duration--;
        if (positions[p].far)
            want.state = 2;
        else {
            want.unk70 = 0;
            ((u8*)&want)[MMX4_OFFSET_OF(struct PlayerObj, touching_spikes)] = 0;
        }
        if (contact) {
            player_before.hp = (s8)0x92;
            player_before.stun_timer = 0;
            player_before.hurt_type = 2;
            player_before.hit_facing = 0;
        }
    } else {
        want.unk50.data = 0;
        expect_step(1, 0x02010001);
    }
    sigma_shot_update(&shot);
    check();
    return 1;
}

static u32 test_sigma_debris(u32 row)
{
    static const u8 hits[5] = { 0, 1, 2, 3, 8 }, slots[6] = { 3, 20, 31, 47, 61, 63 }, free_counts[4] = { 0, 1, 3, 6 };
    static const u8 debris[20] = { 39, 40, 39, 40, 39, 40, 0, 0, 15, 6, 22, 240, 248, 22, 2, 255, 13, 12, 13, 11 };
    static const u8 draws[6][3] = { { 106, 13, 246 }, { 179, 236, 153 }, { 161, 186, 7 }, { 238, 165, 203 }, { 63, 155, 176 }, { 241, 182, 7 } };
    static const u16 states[7] = { 4660, 59894, 44441, 19719, 9931, 5552, 20743 };
    static struct MiscObj misc_want[64];
    u32 scene = row % 9, facing = (row / 9) % 2, layer = facing, available = free_counts[(row / 18) % 4], a = row / 72;
    u32 i, fire = scene >= 5, emit = fire ? (scene & 1) == 0 : scene != 0;
    s32 xoff = 0, yoff = 0;
    seed(fire ? 8 : 3, facing, layer);
    shot.state = 1;
    shot.unk94 = live_angles[a];
    if (fire) {
        parent.quad.vertices[1].y.val = 12 * 65536 + 0x5432;
        shot.x_pos.u.lo = 0xBEEF;
        shot.y_pos.u.lo = 0xCAFE;
        main_bss_state.frame_counter = emit ? 8 : 1;
        if (scene >= 7)
            install_step(38, 5, 0x87000001);
    } else
        shot.unk70 = hits[scene];
    memset(misc_objects, 0xA5, sizeof(misc_objects));
    for (i = 0; i < 64; i++)
        misc_objects[i].active = 1;
    for (i = 0; i < available; i++)
        misc_objects[slots[i]].active = 0;
    c_test_copy_words((u32*)misc_want, (u32*)misc_objects, sizeof(misc_want) / 4);
    capture();
    if (fire) {
        want.x_pos.i.hi = 280;
        want.y_pos.i.hi = 130;
        want.on_screen = layer != 2;
        expect_step(scene >= 7 ? 5 : 1, scene >= 7 ? 0x87000001 : 0x83010001);
        if (scene >= 7)
            want.state = 2;
    } else {
        want.x_pos.val += shot.x_vel.val;
        want.y_pos.val -= shot.y_vel.val;
        expect_step(1, 0x57010001);
        want.x_vel.val = live_vectors[a][0] * 6;
        want.y_vel.val = live_vectors[a][1] * 6;
        if (emit) {
            struct BackgroundObj* bg = &backgrounds_before[0];
            want.unk5 = 1;
            want.previous_animation_index = 0xFF;
            if (scene < 4) {
                want.unk15 = scene == 2 || scene == 3 ? 0 : 0x40;
                want.unk95 = 3;
                want.timer = 24;
                want.unk17 = 31;
                expect_step(0, 0x5A010001);
                bg->unk36 = 20;
                bg->unk45 = bg->unk3E.bytes[0] = 4;
                bg->unk3C = bg->unk3A = 2;
                bg->unk34 |= 0x10;
                xoff = (want.unk15 ? -19 : 19) * 65536;
                yoff = -22 * 65536;
            } else {
                want.unk15 ^= 0x40;
                want.unk95 = 4;
                want.timer = 36;
                want.unk17 = 32;
                expect_step(0, 0x5D010001);
                bg->unk37 = 20;
                bg->unk46 = bg->unk3E.bytes[1] = 4;
                bg->unk3D = bg->unk3B = 2;
                bg->unk34 |= 1;
                xoff = (want.unk15 ? -15 : 15) * 65536;
            }
        }
    }
    for (i = 0; emit && i < available; i++) {
        struct MiscObj* m = &misc_want[slots[i]];
        m->active = 0x41;
        m->id = 3;
        m->unk2 = m->state = m->unk5 = m->unk6 = 0;
        m->unk15 = draws[i][0] & 0x40;
        m->x_pos.val = want.x_pos.val + xoff + (draws[i][1] & 3) * (fire ? 65536 : 1);
        m->y_pos.val = want.y_pos.val + yoff + (draws[i][2] & 3) * (fire ? 65536 : 1);
        m->ext.misc_2.owner = (struct MainObj*)&shot;
        m->ext.misc_2.unk58 = debris[i];
    }
    random_want = states[emit ? available : 0];
    if (fire)
        sigma_shot_cloak_fire(&shot);
    else
        func_800A8E50(&shot);
    c_test_same_words(misc_objects, misc_want, sizeof(misc_want));
    for (i = 0; i < 20; i++)
        assert(sigma_shot_debris[i] == debris[i]);
    check();
    return 1;
}

static u32 test_sigma_weapon_contact(u32 row)
{
    static struct WeaponObj weapons_want[16];
    static u32 collision_before[32];
    static s32 archive[3] = { 8, 8, 0x11223344 };
    u32 kind = row % 3, mode = (row / 3) % 3, dead = (row / 9) % 2, facing = (row / 18) % 2, available = row / 108;
    struct WeaponObj* weapon = &weapon_objects[7];
    u8* saved_archive = (u8*)SP_SPRITE_FRAMES;
    seed(kind == 2 ? 6 : kind + 1, facing, (row / 36) % 3);
    shot.state = 1;
    shot.unk5 = kind == 2 ? 4 : 5;
    shot.unk7A = shot.unk61 = 0;
    shot.unk65 = mode == 2 ? 9 : 0;
    shot.unk58.data = kind == 2 ? (u8*)D_801060F0 : (u8*)D_80106070;
    shot.unk54 = kind == 2 ? (u8*)sigma_shot_boxes[3] : 0;
    owner.state = dead ? (kind == 2 ? 2 : 4) : 1;
    g_Player.unk2 = 1;
    g_Player.boss_flags = 0x40;
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    weapon->active = 0x21;
    weapon->id = 0;
    weapon->state = 1;
    weapon->unk15 = shot.unk15;
    weapon->bg_offset = shot.bg_offset;
    weapon->unk50 = lemon_hit_box;
    weapon->unk64 = 9;
    weapon->x_pos.val = shot.x_pos.val + (mode ? 0 : 512 * 65536);
    weapon->y_pos = shot.y_pos;
    if (available)
        visual_objects[31].active = 0;
    TEST_SPRITE_FRAMES = (u8*)archive;
    capture();
    c_test_copy_words((u32*)weapons_want, (u32*)weapon_objects, sizeof(weapons_want) / 4);
    c_test_copy_words(collision_before, (u32*)shot.unk58.data, sizeof(collision_before) / 4);
    want.unk42 &= 0x7FFF;
    want.unk65 = mode && kind == 2 ? 9 : 0;
    if (kind == 2) {
        want.unk98 = mode == 1 ? 0x7F : 0;
        expect_step(3, 0x68010001);
        if (mode) {
            ((s16*)&weapons_want[7].unk80)[0] = shot.x_pos.i.hi + (facing ? 1 : -1);
            ((s16*)&weapons_want[7].unk80)[1] = shot.y_pos.i.hi - 1;
        }
        if (mode == 1) {
            want.unk63 = -1;
            weapons_want[7].unk98 = -1;
            if (available) {
                struct VisualObj* v = &visuals_want[31];
                v->active = 0x21;
                v->id = 3;
                v->unk2 = 0;
                v->bg_offset = shot.bg_offset;
                v->animation_table = D_8011BF40;
                v->unk40 = 0;
                v->unk42 = 0x7802;
                v->unk16 = 0;
                v->unk3C = (u8*)&archive[2];
                v->x_pos.i.hi = shot.x_pos.i.hi + (facing ? 1 : -1);
                v->y_pos.i.hi = shot.y_pos.i.hi - 1;
                v->unk15 = shot.unk15 ^ 0x40;
            }
        }
    } else
        want.animation_step.fields.duration--;
    want.x_pos.val += shot.x_vel.val;
    want.y_pos.val -= shot.y_vel.val;
    want.on_screen = 1;
    if (dead)
        want.state = 2;
    if (kind == 2)
        sigma_shot_dart(&shot);
    else
        sigma_shot_bolt(&shot);
    c_test_same_words(weapon_objects, weapons_want, sizeof(weapons_want));
    c_test_same_words(shot.unk58.data, collision_before, sizeof(collision_before));
    assert(lemon_hit_box[0].unk0 == -10 && lemon_hit_box[0].unk1 == -6 && lemon_hit_box[0].unk2 == 18 && lemon_hit_box[0].unk3 == 11);
    assert(SP_SPRITE_FRAMES == archive && archive[0] == 8 && archive[1] == 8 && archive[2] == 0x11223344);
    check();
    TEST_SPRITE_FRAMES = saved_archive;
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "sigma_weapon_contact", 0, 0, 24, test_sigma_weapon_contact },
    { "sigma_debris", 0, 0, 27, test_sigma_debris },
    { "scythe_orbit", 0, 0, 32, test_scythe_orbit },
    { "bolt_gather", 0, 0, 12, test_bolt_gather },
    { "sigma_run", 0, 0, 48, test_sigma_run },
    { "planted_scythe", 0, 0, 72, test_planted_scythe },
    { "dart_attack", 0, 0, 99, test_dart_attack },
    { "dropped_scythe", 0, 0, 12, test_dropped_scythe },
    { "cloak_scythe", 0, 0, 2, test_cloak_scythe },
    { "sigma_init", 0, 0, 88, test_sigma_init },
    { "sigma_bolt_edges", 0, 0, 102, test_sigma_bolt_edges },
    { "sigma_despawn", 0, 0, 11, test_sigma_despawn },
    { "sigma_position", 0, 0, 6, test_sigma_position },
    { "sigma_wait", 0, 0, 4, test_sigma_wait },
    { "sigma_motion", 0, 0, 2, test_sigma_motion },
    { "func_800A9544", 0, 0, 1, test_func_800A9544 },
    { "sigma_shot_flash", 0, 0, 2, test_sigma_shot_flash },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 24 + 27 + 32 + 12 + 48 + 72 + 99 + 12 + 2 + 88 + 102 + 11 + 6 + 4 + 2 + 1 + 2;
