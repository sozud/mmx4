#ifndef MMX4_TESTS_STATE_CASES_H
#define MMX4_TESTS_STATE_CASES_H

static union {
    struct MainObj obj;
    struct PlayerObj player;
    struct ShotObj shot;
    struct MiscObj misc;
    struct VisualObj visual;
    struct EffectObj effect;
    struct ItemObj item;
    struct RideArmorObj ride;
    struct UnkObj unk;
    struct WeaponObj weapon;
} state_room;
#define so state_room.obj
static u32 state_extra;
static u32 state_step[16] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
static u32* state_table[0x40];
static u8 state_sound_rows[0x400];

static void state_reset(u8 unk5, u8 unk6, u8 unk7)
{
    u32 i;
    memset(&state_room, 0, sizeof(state_room));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(effect_objects, 0, sizeof(effect_objects));
    memset(shot_objects, 0, sizeof(shot_objects));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(g_QuadObjects, 0, sizeof(g_QuadObjects));
    memset(background_objects, 0, sizeof(background_objects));
    for (i = 0; i < COUNT(state_table); i++)
        state_table[i] = state_step;
    so.animation_table = state_table;
    so.animation_cursor = state_step;
    so.animation_step.packed = state_step[0];
    so.unk5 = unk5;
    so.unk6 = unk6;
    so.unk7 = unk7;
    D_80141F50[2] = state_sound_rows;
    g_Player.x_pos.val = 0;
    g_Player.y_pos.val = 0;
}

static u32 state_run(void (*run)(void), u32 row, const u32* expected)
{
    u32 seen[10];
    state_extra = 0;
    run();
    seen[0] = (u8)so.unk5 | (u8)so.unk6 << 8 | (u8)so.unk7 << 16 | (u32)(u8)so.air_state << 24;
    seen[1] = (u16)so.unk7C | (u32)(u16)so.unk7E << 16;
    seen[2] = so.x_pos.val;
    seen[3] = so.x_speed;
    seen[4] = so.y_speed;
    seen[5] = so.x_accel ^ (u32)so.gravity << 8;
    seen[6] = (u8)so.unk17 | (u8)so.unk15 << 8 | (u32)(u16)so.unk42 << 16;
    seen[7] = (so.hurt_box != NULL) | (so.attack_box != NULL) << 1 | (u8)so.invincibility_timer << 8 | (u32)(u8)so.hp << 16;
    seen[8] = ((u8)g_Player.script_state | (u8)g_Player.script_action << 8 | (u8)engine_obj.enable_boss << 16 | (u32)(u8)engine_obj.unkF << 24) ^ state_extra;
    seen[9] = effect_objects[0].active | visual_objects[0].active << 8 | shot_objects[0].active << 16 | (u32)(u8)so.active << 24;
    return c_test_observe(0, row, seen, expected, 10);
}

static u32 object_run(void (*run)(void), u32 row, const u32* expected)
{
    struct AnimatedObj* self = (struct AnimatedObj*)&state_room;
    u32 seen[10];
    state_extra = 0;
    run();
    seen[0] = (u8)self->state | (u8)self->unk5 << 8 | (u8)self->unk6 << 16 | (u32)(u8)self->unk7 << 24;
    seen[1] = (u8)self->active | (u8)self->unk2 << 8 | (u8)self->unk15 << 16 | (u32)self->previous_animation_index << 24;
    seen[2] = self->x_pos.val;
    seen[3] = self->y_pos.val;
    seen[4] = self->x_vel.val;
    seen[5] = self->y_vel.val;
    seen[6] = self->unk28 ^ (u32)self->unk2C << 8;
    seen[7] = self->unk42 | (u32)(u8)self->animation_step.fields.duration << 16;
    seen[8] = state_extra;
    seen[9] = effect_objects[0].active | visual_objects[0].active << 8 | shot_objects[0].active << 16 | (u32)misc_objects[0].active << 24;
    return c_test_observe(0, row, seen, expected, 10);
}

static u8 state_tiles[128];
static u16 state_tile_pixels[512];
static u32 state_tile_attrs[3];

static void state_terrain(u8 attribute)
{
    memset(state_tiles, 1, sizeof(state_tiles));
    SP_BG_TILEMAP = state_tiles;
    TEST_BG_TILE_PIXELS = (u8*)state_tile_pixels;
    TEST_BG_TILE_ATTRS = (u8*)state_tile_attrs;
    state_tile_attrs[0] = attribute;
    layout_size = 128;
    layout_width = 16;
}

static struct Unk_unk68 state_hit_box = { -16, -16, 32, 32 };
static u8 state_damage[0x80];
static s32 state_sprite_frames[4];

static void state_hit(struct MainObj* target, u8 weapon, u8 kind, u8 damage)
{
    struct MainObj* hitter = (struct MainObj*)&weapon_objects[0];
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(state_damage, 0, sizeof(state_damage));
    state_damage[weapon * 2] = kind;
    state_damage[weapon * 2 + 1] = damage;
    hitter->active = 1;
    hitter->id = weapon;
    hitter->x_pos = target->x_pos;
    hitter->y_pos = target->y_pos;
    hitter->attack_box = &state_hit_box;
    target->hurt_box = &state_hit_box;
    target->collision_data = (const u16*)state_damage;
    TEST_SPRITE_FRAMES = (u8*)state_sprite_frames;
}

#endif
