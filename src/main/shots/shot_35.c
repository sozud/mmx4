// ShotObj, shot_object_update_funcs[35]
// 800A22D4..800A3924
#include "common.h"

void walrus_ice_update(struct ShotObj* self)
{
    walrus_ice_state_funcs[self->state](self);
}

void walrus_ice_init(struct ShotObj* self)
{
    struct WeaponObj* temp_v1;

    self->unk58.data = (u8*)D_80105FF0;
    self->unk67 = 0;
    self->state = (u8)self->state + 1 + ((s8)self->unk2 >> 4);
    self->unk2 = (u8)self->unk2 & 0xF;
    if (self->state < 4) {
        temp_v1 = self->unk7C;
        self->unk3C = temp_v1->unk3C;
        self->unk40 = temp_v1->unk40;
        self->unk42 = temp_v1->unk42 & 0x7FFF;
        self->bg_offset = (s8)(u8)temp_v1->bg_offset;
        self->animation_table = temp_v1->animation_table;
        self->unk15 = temp_v1->unk15;
    }
    self->unk5 = 0;
    self->unk6 = 0;
}

void walrus_ice_break(struct ShotObj* self)
{
    self->state = 7;
}

void walrus_ice_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void walrus_ice_icicle(struct ShotObj* self)
{
    walrus_ice_icicle_funcs[self->unk5](self);
}

// walrus_ice_icicle_init
INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A241C);

void walrus_ice_icicle_main(struct ShotObj* self)
{
    struct WeaponObj* owner;
    s32 collision;
    u16 flags;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    walrus_ice_icicle_step_funcs[self->unk6](self);
    func_8002D9BC(self);
    if (self->unk6 != 0) {
        collision = func_8002DD04(MAIN_OBJECT(self));
        owner = self->unk7C;
        if (collision < 0 || owner->state == 2) {
            func_8001540C(2, 0x98, self);
            spawn_debris(4, walrus_ice_debris, self);
            self->state = 6;
            self->unk5 = 0;
            self->unk6 = 0;
            ZeroObjectState(OBJECT_HEADER(self));
        }
        if (collision > 0) {
            flags = self->unk42 | 0x8000;
        } else {
            flags = self->unk42 & 0x7FFF;
        }
        self->unk42 = flags;
    }
}

// walrus_ice_icicle_form
INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A25EC);

void walrus_ice_icicle_rise(struct ShotObj* self)
{
    move_object(MOVING_OBJECT(self));
    if ((u8)self->unk2 & 1) {
        is_on_screen(BASE_OBJECT(self));
    }
    if (background_objects[0].y_pos.i.hi - 0x30 >= self->y_pos.i.hi) {
        self->unk54 = (const u8*)&walrus_ice_icicle_hurt_box;
        self->unk50.data = (const u8*)&walrus_ice_icicle_attack_box;
        set_animation(ANIMATED_OBJECT(self), 0xA);
        self->y_vel.val = FIXED(-0.5);
        self->unk2C = FIXED(0.09375);
        self->timer = 0xF0;
        self->unk16 = 2;
        self->unk6++;
    }
}

void walrus_ice_icicle_wait_drop(struct ShotObj* self)
{
    s16 timer;
    struct MainObj* owner;
    u8 next_state;
    s8 index;
    u16* table;
    u16 background_x;
    u16 offset;

    owner = MAIN_OBJECT(self->unk7C);
    if (owner->unk6 != 5) {
        timer = (u16)self->timer - 1;
        self->timer = timer;
        if (timer != 0) {
            return;
        }
    }

    next_state = self->unk6 + 1;
    index = self->unk2;
    table = (u16*)owner->ext.main_57.rect;
    background_x = background_objects[0].unk1E;
    offset = table[index];

    self->timer = 15;
    self->unk6 = next_state;
    self->x_pos.i.hi = background_x + (offset + 0x10);
}

void walrus_ice_icicle_fall(struct ShotObj* self)
{
    s16 temp_v0;

    move_with_gravity(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
    temp_v0 = self->timer;
    if (temp_v0 != 0) {
        self->timer = temp_v0 - 1;
        return;
    }
    CollisionRelated(PLAYER_OBJECT(self));
    if (self->unk70 & 8) {
        set_animation(ANIMATED_OBJECT(self), 0xB);
        spawn_debris(4, walrus_ice_debris, self);
        func_8001540C(2, 0x9A, self);
        start_screen_shake_y(0x10, 3, 1);
        self->timer = 0x100;
        self->unk6++;
    }
}

void walrus_ice_icicle_stuck(struct ShotObj* self)
{
    s16 temp_v0;

    animate_object(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
    if (func_8002BB80(MAIN_OBJECT(self), MAIN_OBJECT(self->unk7C)) != 0) {
        func_8001540C(2, 0x98, self);
        spawn_debris(4, walrus_ice_debris, self);
        self->state = 6;
        self->unk5 = 0;
        self->unk6 = 0;
    }
    temp_v0 = (u16)self->timer - 1;
    self->timer = temp_v0;
    if (temp_v0 == 0) {
        self->timer = 0x32;
        self->unk6++;
    }
}

void walrus_ice_icicle_blink(struct ShotObj* self)
{
    s16 timer;

    timer = self->timer - 1;
    self->timer = timer;
    if (timer == 0) {
        func_8001540C(2, 0x98, self);
        spawn_debris(4, walrus_ice_debris, self);
        self->state = 6;
        self->unk5 = 0;
        self->unk6 = 0;
    } else {
        self->on_screen ^= 1;
        if (self->on_screen != 0) {
            is_on_screen(BASE_OBJECT(self));
        }
    }
}

void walrus_ice_ball(struct ShotObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    walrus_ice_ball_funcs[self->unk5](self);
}

// walrus_ice_ball_init
INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A2AA0);

void walrus_ice_ball_main(struct ShotObj* self)
{
    struct WeaponObj* weapon;
    s32 collision_result;
    u16 flags;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    walrus_ice_ball_step_funcs[self->unk6](self);
    func_8002D9BC(self);
    collision_result = func_8002DD04(MAIN_OBJECT(self));
    weapon = self->unk7C;
    if ((collision_result < 0) || (weapon->unk5 != 8)) {
        func_8001540C(2, 0x97, self);
        spawn_debris(4, walrus_ice_debris, self);
        self->state = 6;
        self->unk5 = 0;
        self->unk6 = 0;
    }
    if (collision_result > 0) {
        flags = self->unk42 | 0x8000;
    } else {
        flags = self->unk42 & 0x7FFF;
    }
    self->unk42 = flags;
}

void walrus_ice_ball_blink(struct ShotObj* self)
{
    s16 timer;
    s8 on_screen;

    timer = self->timer - 1;
    self->timer = timer;
    if (timer == 0) {
        func_8001540C(2, 0x96, self);
        self->unk6++;
        return;
    }

    on_screen = self->on_screen ^ 1;
    self->on_screen = on_screen;
    if (on_screen != 0) {
        is_on_screen(BASE_OBJECT(self));
    }
}

void walrus_ice_ball_grow(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk54 = (const u8*)&walrus_ice_ball_hurt_box;
        self->unk50.data = (const u8*)&walrus_ice_ball_attack_box;
        self->unk8C.word = 0;
        self->unk6++;
    }
    is_on_screen(BASE_OBJECT(self));
}

void walrus_ice_ball_burst(struct ShotObj* self)
{
    s32 i;
    struct ShotObj* shot;

    if (self->unk8C.word != 0) {
        i = 0;
        do {
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0x23;
                shot->unk2 = i + 0x40;
                shot->x_pos.val = self->x_pos.val;
                shot->y_pos.val = self->y_pos.val + FIXED(4);
                shot->unk3C = self->unk3C;
                shot->unk40 = self->unk40;
                shot->unk42 = self->unk42 & 0x7FFF;
                shot->bg_offset = (u8)self->bg_offset;
                shot->animation_table = self->animation_table;
                shot->unk15 = self->unk15;
                shot->unk7C = self->unk7C;
            }
            i++;
        } while ((u8)i < 9);
        func_8001540C(2, 0x97, self);
        self->unk8C.word = 0;
        self->state = 6;
        self->unk5 = 0;
        self->unk6 = 0;
    }
    is_on_screen(BASE_OBJECT(self));
}

void walrus_ice_shard(struct ShotObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    walrus_ice_shard_funcs[self->unk5](self);
}

void walrus_ice_shard_init(struct ShotObj* self)
{
    self->unk68 = &walrus_ice_shard_terrain_box;
    self->unk54 = (const u8*)&walrus_ice_shard_hurt_box;
    self->unk50.data = (const u8*)&walrus_ice_shard_attack_box;
    self->unk5C = 3;
    self->unk60 = 6;
    self->unk16 = 4;
    set_animation(self, 0x20);
    self->unk5++;
}

void walrus_ice_shard_main(struct ShotObj* self)
{
    struct MainObj* owner;
    s32 collision;
    u16 flags;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    walrus_ice_shard_step_funcs[self->unk6](self);
    func_8002D9BC(self);
    collision = func_8002DD04(MAIN_OBJECT(self));
    owner = self->unk7C;
    if (collision < 0 || owner->state == 2) {
        func_8001540C(2, 0x98, self);
        spawn_debris(4, walrus_ice_debris, self);
        self->state = 6;
        self->unk5 = 0;
        self->unk6 = 0;
    }
    if (collision > 0) {
        flags = self->unk42 | 0x8000;
    } else {
        flags = self->unk42 & 0x7FFF;
    }
    self->unk42 = flags;
}

void walrus_ice_shard_launch(struct ShotObj* self)
{
    set_velocity_from_angle(MOVING_OBJECT(self), self->unk2 + 0xC);
    self->x_vel.val *= 4;
    if (self->unk15 == 0x40) {
        self->x_vel.val = -self->x_vel.val;
    }
    self->y_vel.val *= 4;
    self->unk6++;
}

void walrus_ice_shard_fly(struct ShotObj* self)
{
    u8 flags;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    CollisionRelated(PLAYER_OBJECT(self));
    if (func_8002B160(BASE_OBJECT(self)) == 1) {
        self->state = 6;
        self->unk5 = 0;
        self->unk6 = 0;
    } else {
        flags = self->unk70;
        if (flags & 2) {
            func_8001540C(2, 0x9A, self);
            set_animation(self, 0x22);
        } else if (flags & 1) {
            func_8001540C(2, 0x9A, self);
            set_animation(self, 0x22);
            self->unk15 = 0x40;
        } else if (flags & 8) {
            func_8001540C(2, 0x9A, self);
            set_animation(self, 0x21);
        } else {
            is_on_screen(BASE_OBJECT(self));
            return;
        }
        self->timer = 0x100;
        self->unk6++;
    }
    is_on_screen(BASE_OBJECT(self));
}

void walrus_ice_shard_stuck(struct ShotObj* self)
{
    s16 temp_v0;

    animate_object(ANIMATED_OBJECT(self));
    temp_v0 = self->timer - 1;
    self->timer = temp_v0;
    if (temp_v0 == 0) {
        self->timer = 0x32;
        self->unk6++;
    }
    is_on_screen(BASE_OBJECT(self));
}

void walrus_ice_shard_blink(struct ShotObj* self)
{
    s16 timer;

    timer = self->timer - 1;
    self->timer = timer;
    if (timer == 0) {
        func_8001540C(2, 0x98, self);
        spawn_debris(4, walrus_ice_debris, self);
        self->state = 6;
        self->unk5 = 0;
        self->unk6 = 0;
    } else {
        self->on_screen ^= 1;
        if (self->on_screen != 0) {
            is_on_screen(BASE_OBJECT(self));
        }
    }
}

void walrus_ice_chunk(struct ShotObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    walrus_ice_chunk_funcs[self->unk5](self);
    func_8002D9BC(self);
}

// walrus_ice_chunk_init
INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A32B8);

void walrus_ice_chunk_main(struct ShotObj* self)
{
    struct ShotObj* owner;
    s32 collision;
    u16 flags;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    walrus_ice_chunk_step_funcs[self->unk6](self);
    func_8002D9BC(self);
    collision = func_8002DD04(MAIN_OBJECT(self));
    owner = SHOT_OBJECT(self->unk7C);
    if (collision < 0 || owner->state == 2) {
        func_8001540C(2, 0x97, self);
        spawn_debris(4, walrus_ice_debris, self);
        self->state = 6;
        self->unk5 = 0;
        self->unk6 = 0;
    }
    if (collision > 0) {
        flags = self->unk42 | 0x8000;
    } else {
        flags = self->unk42 & 0x7FFF;
    }
    self->unk42 = flags;
    CollisionRelated(self);
}

// walrus_ice_chunk_launch
INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A348C);

void walrus_ice_chunk_fall(struct ShotObj* obj)
{
    struct ShotObj* shot;
    u8 i;

    animate_object(ANIMATED_OBJECT(obj));
    move_with_gravity(ANIMATED_OBJECT(obj));
    is_on_screen(BASE_OBJECT(obj));
    if (obj->unk70 & 8) {
        func_8001540C(2, 0x97, obj);
        spawn_debris(0xA, walrus_ice_chunk_debris, obj);
        i = 0;
        do {
            shot = find_free_shot_obj();
            if (shot != 0) {
                shot->active = 0x41;
                shot->id = 0x23;
                shot->unk2 = i + 0x30;
                shot->x_pos.val = obj->x_pos.val;
                shot->y_pos.val = obj->y_pos.val + FIXED(-16);
                shot->unk3C = obj->unk3C;
                shot->unk40 = obj->unk40;
                shot->unk42 = obj->unk42 & 0x7FFF;
                shot->bg_offset = obj->bg_offset;
                shot->animation_table = obj->animation_table;
                shot->unk15 = obj->unk15;
                shot->unk7C = obj->unk7C;
            }
            i++;
        } while (i < 6);
        obj->unk6++;
    }
}

void walrus_ice_chunk_break(struct ShotObj* self)
{
    self->state = 6;
    self->unk5 = 0;
    self->unk6 = 0;
}

void walrus_ice_lob(struct ShotObj* self)
{
    struct BaseObj* target;
    s32 collision;
    u16 flags;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    walrus_ice_lob_funcs[self->unk5](self);
    func_8002D9BC(self);
    collision = func_8002DD04(MAIN_OBJECT(self));
    target = BASE_OBJECT(self->unk7C);
    if (collision < 0 || target->state == 2) {
        func_8001540C(2, 0x98, self);
        spawn_debris(4, walrus_ice_debris, self);
        self->state = 6;
        self->unk5 = 0;
        self->unk6 = 0;
    }
    if (collision > 0) {
        flags = self->unk42 | 0x8000;
    } else {
        flags = self->unk42 & 0x7FFF;
    }
    self->unk42 = flags;
    is_on_screen(BASE_OBJECT(self));
}

void walrus_ice_lob_init(struct ShotObj* object)
{
    struct ShotObj* arg0;
    s8 index;

    arg0 = (struct ShotObj*)object;
    index = arg0->unk2;
    if (index < 3) {
        arg0->x_vel.val = walrus_ice_lob_speeds[index];
    } else {
        arg0->x_vel.val = -walrus_ice_lob_speeds[index - 3];
    }
    arg0->y_vel.val = FIXED(6.5);
    arg0->unk2C = FIXED(0.2578125);
    arg0->unk5C = 5;
    arg0->unk60 = 6;
    arg0->unk68 = &walrus_ice_lob_terrain_box;
    arg0->unk54 = (const u8*)&walrus_ice_icicle_hurt_box;
    arg0->unk50.data = (const u8*)&walrus_ice_icicle_attack_box;
    arg0->unk28 = 0;
    arg0->unk16 = 2;
    set_animation(arg0, 0xA);
    arg0->unk5++;
}

void walrus_ice_lob_fall(struct ShotObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    move_with_gravity(ANIMATED_OBJECT(self));
    CollisionRelated(PLAYER_OBJECT(self));
    if (self->unk70 & 8) {
        func_8001540C(2, 0x98, self);
        spawn_debris(5, walrus_ice_debris, self);
        self->state = 6;
        self->unk5 = 0;
        self->unk6 = 0;
    }
}

void walrus_ice_choose_drop_pattern(struct ShotObj* self)
{
    RECT** table;
    struct MainObj* owner;

    owner = MAIN_OBJECT(self->unk7C);
    if (self->unk7 == 4) {
        table = walrus_ice_drop_patterns_a;
    } else {
        table = walrus_ice_drop_patterns_b;
    }
    owner->ext.main_57.rect = table[get_random() & 7];
}

RECT walrus_ice_drop_pattern_data_a[8] = {
    { 0x30, 0x90, 0xF0, 0x150 },
    { 0x30, 0x70, 0xB0, 0xF0 },
    { 0x70, 0xD0, 0x130, 0x190 },
    { 0x70, 0x90, 0xB0, 0xD0 },
    { 0xB0, 0x110, 0x170, 0x1B0 },
    { 0x110, 0x150, 0x190, 0x1B0 },
    { 0xD0, 0x110, 0x150, 0x190 },
    { 0x130, 0x150, 0x170, 0x190 },
};

RECT walrus_ice_drop_pattern_data_b[8][2] = {
    { { 0x30, 0x70, 0xB0, 0xF0 }, { 0x130, 0x170, 0x190, 0x1B0 } },
    { { 0x30, 0x50, 0x70, 0xB0 }, { 0xF0, 0x130, 0x170, 0x1B0 } },
    { { 0x30, 0x50, 0x70, 0xD0 }, { 0xF0, 0x110, 0x170, 0x190 } },
    { { 0x30, 0x50, 0xB0, 0xD0 }, { 0xF0, 0x150, 0x170, 0x190 } },
    { { 0x30, 0x50, 0x70, 0x90 }, { 0x150, 0x170, 0x190, 0x1B0 } },
    { { 0x50, 0x70, 0x90, 0xF0 }, { 0x110, 0x170, 0x190, 0x1B0 } },
    { { 0x30, 0x50, 0x70, 0xD0 }, { 0xF0, 0x150, 0x170, 0x190 } },
    { { 0x50, 0x70, 0xB0, 0xD0 }, { 0x110, 0x130, 0x170, 0x190 } },
};

RECT* walrus_ice_drop_pattern_list_a[8] = {
    &walrus_ice_drop_pattern_data_a[0],
    &walrus_ice_drop_pattern_data_a[1],
    &walrus_ice_drop_pattern_data_a[2],
    &walrus_ice_drop_pattern_data_a[3],
    &walrus_ice_drop_pattern_data_a[4],
    &walrus_ice_drop_pattern_data_a[5],
    &walrus_ice_drop_pattern_data_a[6],
    &walrus_ice_drop_pattern_data_a[7],
};

RECT* walrus_ice_drop_pattern_list_b[8] = {
    walrus_ice_drop_pattern_data_b[0],
    walrus_ice_drop_pattern_data_b[1],
    walrus_ice_drop_pattern_data_b[2],
    walrus_ice_drop_pattern_data_b[3],
    walrus_ice_drop_pattern_data_b[4],
    walrus_ice_drop_pattern_data_b[5],
    walrus_ice_drop_pattern_data_b[6],
    walrus_ice_drop_pattern_data_b[7],
};

RECT** walrus_ice_drop_patterns_a = walrus_ice_drop_pattern_list_a;
RECT** walrus_ice_drop_patterns_b = walrus_ice_drop_pattern_list_b;

s16 walrus_ice_icicle_offsets[2][2] = {
    { -19, -31 },
    { 36, -31 },
};

struct Unk_unk68 walrus_ice_chunk_terrain_box = { -39, 21, 27, 30 };
struct Unk_unk68 walrus_ice_lob_terrain_box = { 0, 10, 9, 3 };
struct Unk_unk68 walrus_ice_shard_terrain_box = { 0, 0, 6, 6 };
struct Unk_unk68 walrus_ice_ball_terrain_box = { 0, -4, 10, 7 };
struct Unk_unk68 walrus_ice_icicle_hurt_box = { -12, -32, 23, 63 };
struct Unk_unk68 walrus_ice_icicle_attack_box = { -4, -20, 9, 30 };
struct Unk_unk68 walrus_ice_ball_hurt_box = { -37, -56, 73, 118 };
struct Unk_unk68 walrus_ice_ball_attack_box = { -28, -48, 55, 88 };
struct Unk_unk68 walrus_ice_shard_hurt_box = { -13, -12, 23, 23 };
struct Unk_unk68 walrus_ice_shard_attack_box = { -5, -8, 9, 15 };

s32 walrus_ice_lob_speeds[3] = { 0x30000, 0x20000, 0x10000 };

u8 walrus_ice_debris[12] = { 12, 13, 14, 15, 13, 15, 12, 14, 13, 15, 0, 0 };

u8 walrus_ice_chunk_debris[12] = { 12, 13, 35, 15, 35, 15, 36, 14, 36, 15, 0, 0 };

void (*walrus_ice_state_funcs[])(struct ShotObj*) = {
    walrus_ice_init,
    walrus_ice_icicle,
    walrus_ice_ball,
    walrus_ice_chunk,
    walrus_ice_lob,
    walrus_ice_shard,
    walrus_ice_break,
    walrus_ice_despawn,
};

void (*walrus_ice_icicle_funcs[])(struct ShotObj*) = {
    func_800A241C,
    walrus_ice_icicle_main,
};

void (*walrus_ice_icicle_step_funcs[])(struct ShotObj*) = {
    func_800A25EC,
    walrus_ice_icicle_rise,
    walrus_ice_icicle_wait_drop,
    walrus_ice_icicle_fall,
    walrus_ice_icicle_stuck,
    walrus_ice_icicle_blink,
};

void (*walrus_ice_ball_funcs[])(struct ShotObj*) = {
    func_800A2AA0,
    walrus_ice_ball_main,
};

void (*walrus_ice_ball_step_funcs[])(struct ShotObj*) = {
    walrus_ice_ball_blink,
    walrus_ice_ball_grow,
    walrus_ice_ball_burst,
};

void (*walrus_ice_shard_funcs[])(struct ShotObj*) = {
    walrus_ice_shard_init,
    walrus_ice_shard_main,
};

void (*walrus_ice_shard_step_funcs[])(struct ShotObj*) = {
    walrus_ice_shard_launch,
    walrus_ice_shard_fly,
    walrus_ice_shard_stuck,
    walrus_ice_shard_blink,
};

void (*walrus_ice_chunk_funcs[])(struct ShotObj*) = {
    func_800A32B8,
    walrus_ice_chunk_main,
};

void (*walrus_ice_chunk_step_funcs[])(struct ShotObj*) = {
    func_800A348C,
    walrus_ice_chunk_fall,
    walrus_ice_chunk_break,
};

void (*walrus_ice_lob_funcs[])(struct ShotObj*) = {
    walrus_ice_lob_init,
    walrus_ice_lob_fall,
};

s16 drone_beam_boxes[4][2] = {
    { -0x1280, 0x2AFF },
    { -0x1280, 0x2AFF },
    { -0xA80, 0x19FF },
    { -0xA80, 0x19FF },
};
