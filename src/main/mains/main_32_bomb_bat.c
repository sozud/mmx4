// MainObj, main_object_update_funcs[32]
// 8005C824..8005D1F4
#include "common.h"
#include "func_tables.h"

void bomb_bat_update(struct MainObj* self)
{
    bomb_bat_state_funcs[self->state](self);
}

// bomb_bat_init
INCLUDE_ASM("main/nonmatchings/mains/main_32_bomb_bat", func_8005C860);

void bomb_bat_main(struct MainObj* self)
{
    s32 hit;
    u8 i;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    bomb_bat_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    if (self->unk5 != 0) {
        self->ext.main_32.saved_unk5 = self->unk5;
    }
    for (i = 0; i < 2 - self->ext.main_32.unk88; i++) {
        self->hurt_box = (const u8*)bomb_bat_hurt_boxes[i];
        hit = func_8002DD04(self);
        if (hit < 0) {
            if (i == 0 && self->ext.main_32.unk88 == 0) {
                bomb_bat_drop_bomb(self);
            }
            spawn_explosion(BASE_OBJECT(self));
            spawn_debris(4, bomb_bat_debris, self);
            drop_item(BASE_OBJECT(self), 8);
            self->state++;
            return;
        }
        if (hit != 0) {
            break;
        }
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
    } else {
        self->state++;
    }
}

void bomb_bat_despawn(struct MainObj* self)
{
    despawn_object(OBJECT_HEADER(self));
}

void bomb_bat_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_32.saved_unk5;
}

void bomb_bat_hover(struct MainObj* self)
{
    bomb_bat_face_player(self);
    bomb_bat_hover_funcs[self->unk6](self);
}

void bomb_bat_hover_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    self->unk7C = 0xC8;
    self->unk6++;
}

// bomb_bat_hover_track
INCLUDE_ASM("main/nonmatchings/mains/main_32_bomb_bat", func_8005CB90);

void bomb_bat_drop(struct MainObj* self)
{
    bomb_bat_move_funcs[self->unk6](self);
}

void bomb_bat_drop_start(struct MainObj* self)
{
    set_animation(self, 1);
    self->ext.main_32.unk80 = 5;
    self->x_speed = 0;
    self->hurt_box = (const u8*)&bomb_bat_body_box;
    self->attack_box = (const u8*)&bomb_bat_body_box;
    self->unk6++;
}

void bomb_bat_drop_release(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->ext.main_32.unk80 == 0) {
        self->ext.main_32.unk88 = 1;
        bomb_bat_drop_bomb(self);
        self->ext.main_32.unk80 = 13;
        self->unk6++;
    }
}

void bomb_bat_drop_end(struct MainObj* self)
{
    animate_object((struct AnimatedObj*)self);
    if (--self->ext.main_32.unk80 == 0) {
        set_animation(self, 3);
        self->unk5 = 4;
        self->unk6 = 0;
    }
}

void bomb_bat_fly_off(struct MainObj* self)
{
    bomb_bat_move_funcs[self->unk6 + 2](self);
}

void bomb_bat_fly_off_start(struct MainObj* self)
{
    s32* velocity;
    s32 selected;
    u8 step;

    set_animation(self, 3);
    velocity = bomb_bat_fly_speeds;
    if (self->unk15 & 0x40) {
        velocity++;
    }
    selected = *velocity;
    step = self->unk6;
    self->y_speed = FIXED(0.3125);
    self->x_speed = selected;
    self->unk6 = step + 1;
}

void bomb_bat_fly_off_move(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}

void bomb_bat_flee(struct MainObj* self)
{
    bomb_bat_move_funcs[self->unk6 + 4](self);
}

void bomb_bat_flee_start(struct MainObj* self)
{
    s32* velocity;
    s32 selected;

    set_animation(self, 3);
    velocity = bomb_bat_fly_speeds;
    if (self->unk15 & 0x40) {
        velocity++;
    }
    selected = *velocity;
    self->attack_box = (const u8*)&bomb_bat_body_box;
    self->y_speed = 0;
    self->ext.main_32.unk88 = 1;
    self->x_speed = selected;
    self->unk6++;
}

void bomb_bat_flee_move(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}

void bomb_bat_dive(struct MainObj* self)
{
    bomb_bat_dive_funcs[self->unk6](self);
}

// bomb_bat_dive_start
INCLUDE_ASM("main/nonmatchings/mains/main_32_bomb_bat", func_8005CF9C);

void bomb_bat_dive_wait(struct MainObj* self)
{
    s32 unused[1];
    s16 timer = self->unk7C;
    if (timer == 0) {
        self->unk6++;
    } else {
        self->unk7C = timer - 1;
    }
}

void bomb_bat_dive_fall(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    self->y_speed += 0x100;
}

void bomb_bat_face_player(struct MainObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
}

void bomb_bat_drop_bomb(struct MainObj* self)
{
    struct ShotObj* temp_v0;

    temp_v0 = find_free_shot_obj();
    if (temp_v0 != NULL) {
        temp_v0->active = 0x41;
        temp_v0->id = 7;
        temp_v0->unk2 = 0;
        temp_v0->unk40 = self->unk40;
        temp_v0->unk42 = self->unk42;
        temp_v0->animation_table = (u32**)self->animation_table;
        temp_v0->unk3C = (u8*)self->sprite_frames;
        temp_v0->bg_offset = self->bg_offset;
        temp_v0->unk15 = self->unk15;
        temp_v0->x_pos.val = self->x_pos.val;
        temp_v0->y_pos.val = self->y_pos.val;
        temp_v0->unk7C = WEAPON_OBJECT(self);
        temp_v0->unk16 = 6;
    }
}

struct Unk_unk68 bomb_bat_body_box = { -11, -10, 21, 23 };

struct Unk_unk68 D_800FDC84 = { -9, 13, 16, 19 };

struct Unk_unk68 D_800FDC88[2] = {
    { -11, -10, 20, 42 },
    { -10, 27, 26, 3 },
};

s32 bomb_bat_fly_speeds[2] = { (s32)0xFFFD0000, (s32)0x00030000 };

s32 D_800FDC98[2] = { (s32)0xFFFC8000, (s32)0x00038000 };

union AnimationStep bomb_bat_anim_0[] = {
    { 0x00010003 },
    { 0x01010003 },
    { 0x02010004 },
    { 0x03010003 },
    { 0x04010003 },
    { 0x05FB0005 },
};

union AnimationStep bomb_bat_anim_1[] = {
    { 0x06010002 },
    { 0x07010002 },
    { 0x03010002 },
    { 0x08010003 },
    { 0x09010003 },
    { 0x0A000003 },
};

union AnimationStep bomb_bat_anim_2[] = {
    { 0x0B010002 },
    { 0x0C010002 },
    { 0x0B010002 },
    { 0x0DFD0002 },
};

union AnimationStep bomb_bat_anim_3[] = {
    { 0x0E010005 },
    { 0x0F010002 },
    { 0x10010002 },
    { 0x11010005 },
    { 0x12010003 },
    { 0x13FB0003 },
};

union AnimationStep bomb_bat_anim_4[] = {
    { 0x14000001 },
};

union AnimationStep bomb_bat_anim_5[] = {
    { 0x15000001 },
};

union AnimationStep bomb_bat_anim_6[] = {
    { 0x16000001 },
};

union AnimationStep bomb_bat_anim_7[] = {
    { 0x17000001 },
};

union AnimationStep* bomb_bat_animations[8] = {
    bomb_bat_anim_0,
    bomb_bat_anim_1,
    bomb_bat_anim_2,
    bomb_bat_anim_3,
    bomb_bat_anim_4,
    bomb_bat_anim_5,
    bomb_bat_anim_6,
    bomb_bat_anim_7,
};

u8 bomb_bat_debris[4] = { 0x04, 0x05, 0x06, 0x07 };

void (*bomb_bat_state_funcs[3])() = {
    func_8005C860,
    bomb_bat_main,
    bomb_bat_despawn,
};

struct Unk_unk68* bomb_bat_hurt_boxes[2] = {
    &bomb_bat_body_box,
    &D_800FDC84,
};

void (*bomb_bat_step_funcs[7])() = {
    enemy_hit_reaction,
    bomb_bat_resume_step,
    bomb_bat_hover,
    bomb_bat_drop,
    bomb_bat_fly_off,
    bomb_bat_flee,
    bomb_bat_dive,
};

void (*bomb_bat_hover_funcs[2])() = {
    bomb_bat_hover_start,
    func_8005CB90,
};

void (*bomb_bat_move_funcs[6])() = {
    bomb_bat_drop_start,
    bomb_bat_drop_release,
    bomb_bat_fly_off_start,
    bomb_bat_fly_off_move,
    bomb_bat_flee_start,
    bomb_bat_flee_move,
};

void (*bomb_bat_dive_funcs[3])() = {
    func_8005CF9C,
    bomb_bat_dive_wait,
    bomb_bat_dive_fall,
};
