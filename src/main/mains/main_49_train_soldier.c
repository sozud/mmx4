// MainObj, main_object_update_funcs[49]
// 800684F8..8006970C
#include "common.h"

extern u8 train_soldier_guard_attack_box[];
extern s16 main49_activation_distances[4];

void train_soldier_update(struct MainObj* self)
{
    train_soldier_state_funcs[self->state](self);
    CollisionRelated((struct PlayerObj*)self);
}

// train_soldier_init
INCLUDE_ASM("main/nonmatchings/mains/main_49_train_soldier", func_80068548);

void train_soldier_main(struct MainObj* self)
{
    u8 temp_v1;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    if (func_8002DD04(self) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(5, train_soldier_debris, self);
        drop_item(BASE_OBJECT(self), 0x12);
        goto block_12;
    }
    temp_v1 = SP_CUR_MAIN_OBJ->ext.main_49.unk85;
    if (temp_v1 != 2 && temp_v1 < 6U) {
        train_soldier_check_guard(self);
    }
    func_80068D6C(self);
    if (SP_CUR_MAIN_OBJ->ext.main_49.unk86 == 0) {
        train_soldier_check_shoot(self);
    }
    train_soldier_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    if (SP_CUR_MAIN_OBJ->ext.main_49.unk86 == 0) {
        if (func_8002B160(BASE_OBJECT(self)) == 0) {
            is_on_screen(BASE_OBJECT(self));
        } else {
            self->state = 2;
        }
    } else if (func_8002B1E8(BASE_OBJECT(self), 0x70, 0) != 0) {
        self->state = 2;
    } else {
        is_on_screen(BASE_OBJECT(self));
    }
    return;
block_12:
    self->state = 2;
}

void train_soldier_despawn(struct MainObj* self)
{
    if (SP_CUR_MAIN_OBJ->ext.main_49.unk86 == 0 || self->unk2 == 9) {
        despawn_object(OBJECT_HEADER(self));
    } else {
        despawn_object_permanently(OBJECT_HEADER(self));
    }
}

void train_soldier_wait_for_player(struct MainObj* self)
{
    s8 temp_a2;
    s16 threshold;
    u8 temp_v0;
    u8* temp_v1;

    if (self->unk6 == 0) {
        temp_a2 = self->unk2;
        threshold = main49_activation_distances[temp_a2 - 6];
        if ((g_Player.x_pos.i.hi - self->x_pos.i.hi) >= threshold) {
            temp_v1 = (u8*)SP_CUR_MAIN_OBJ;
            temp_v1[0x81] = (u8)((temp_a2 - 6) * 0x10);
            self->unk6 = (u8)self->unk6 + 1;
        }
    } else {
        temp_v1 = (u8*)SP_CUR_MAIN_OBJ;
        temp_v0 = temp_v1[0x81];
        if (temp_v0 == 0) {
            self->state = 1;
            self->unk5 = 2;
            self->unk6 = 0;
            self->unk7A = 0;
            if (g_Player.x_pos.val < self->x_pos.val) {
                self->unk15 = 0;
                return;
            }
            self->unk15 = 0x40;
            return;
        }
        temp_v1[0x81] = temp_v0 - 1;
    }
}

void train_soldier_idle(struct MainObj* self)
{
}

void train_soldier_walk(struct MainObj* self)
{
    train_soldier_walk_funcs[self->unk6](self);
}

// train_soldier_walk_start
INCLUDE_ASM("main/nonmatchings/mains/main_49_train_soldier", func_80068B80);

void train_soldier_walk_move(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));

    if (self->unk15 != 0) {
        if (self->collision_flags & 1) {
            self->unk15 = 0;
            self->x_speed = -self->x_speed;
        }
    } else if (self->collision_flags & 2) {
        self->unk15 = 0x40;
        self->x_speed = -self->x_speed;
    }
}

void train_soldier_guard(struct MainObj* self)
{
    train_soldier_guard_funcs[self->unk6](self);
}

extern u32 D_801076F8[];
extern u8 train_soldier_guard_hurt_box[];

void train_soldier_guard_start(struct MainObj* self)
{
    self->collision_data = (const u16*)D_801076F8;
    self->hurt_box = train_soldier_guard_hurt_box;
    self->attack_box = train_soldier_guard_attack_box;
    self->x_speed = 0;
    self->x_accel = 0;
    self->y_speed = 0;
    self->gravity = 0;
    self->unk6++;
    set_animation(self, 8);
}

void train_soldier_guard_hold(struct MainObj* self)
{
    animate_object(self);
}

// train_soldier_check_jump
INCLUDE_ASM("main/nonmatchings/mains/main_49_train_soldier", func_80068D6C);

void train_soldier_check_guard(struct MainObj* self)
{
    u8 timer;

    if (self->unk5 == 2) {
        timer = SP_CUR_MAIN_OBJ->ext.main_49.index + 1;
        SP_CUR_MAIN_OBJ->ext.main_49.index = timer;
        if ((timer & 0xFF) == 0x5A) {
            self->unk5 = 5;
            self->unk6 = 0;
            SP_CUR_MAIN_OBJ->ext.main_49.index = 0;
            self->y_speed = 0;
            self->gravity = 0;
            self->x_speed = 0;
            set_animation(self, 7);
        }
    }
}

void train_soldier_check_shoot(struct MainObj* arg0)
{
    s16 distance;
    s32 y_distance;
    struct MainObj* self;
    struct MainObj* current;

    if ((arg0->air_state == 0) && (arg0->unk5 != 6)) {
        self = SP_CUR_MAIN_OBJ;
        if (self->ext.main_49.unk83 != 0) {
            self->ext.main_49.unk83--;
            return;
        }

        if ((arg0->x_pos.i.hi - g_Player.x_pos.i.hi) >= 0) {
            distance = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
        } else {
            distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
        }

        if (distance < 0x81) {
            if (arg0->x_pos.i.hi > g_Player.x_pos.i.hi) {
                arg0->unk15 = 0;
            } else {
                arg0->unk15 = 0x40;
            }

            current = SP_CUR_MAIN_OBJ;
            if ((current->ext.main_49.unk85 == 1) || ((current->ext.main_49.unk85 == 2) && (arg0->unk2 != 0))) {
                current->ext.main_49.unk82 = 0x40;
            } else {
                y_distance = arg0->y_pos.i.hi - g_Player.y_pos.i.hi;
                if (y_distance >= 0x21) {
                    SP_CUR_MAIN_OBJ->ext.main_49.unk82 = 0x80;
                } else if (y_distance < -0x10) {
                    SP_CUR_MAIN_OBJ->ext.main_49.unk82 = 0x82;
                } else {
                    SP_CUR_MAIN_OBJ->ext.main_49.unk82 = 0x81;
                }
            }

            set_animation(arg0, 0xA);
            arg0->unk5 = 6;
            arg0->unk6 = 0;
        }
    }
}

void train_soldier_fall(struct MainObj* self)
{
    train_soldier_fall_funcs[self->unk6](self);
}

void train_soldier_fall_drop(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        if (SP_CUR_MAIN_OBJ->ext.main_49.unk80 == 4) {
            set_animation(self, 0x17);
        } else {
            set_animation(self, 0x18);
        }
        self->y_speed = 0;
        self->gravity = 0;
        self->x_speed = 0;
        self->x_accel = 0;
        self->unk6++;
    }
}

void train_soldier_fall_land(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        if (SP_CUR_MAIN_OBJ->ext.main_49.unk85 == 2) {
            self->unk5 = 7;
        } else {
            self->unk5 = 2;
        }
        self->unk6 = 0;
        self->air_state = 0;
    }
}

void train_soldier_jump(struct MainObj* self)
{
    train_soldier_jump_funcs[self->unk6](self);
}

void train_soldier_jump_crouch(struct MainObj* self)
{
    animate_object((struct AnimatedObj*)self);
    if (self->animation_step.fields.event != 0) {
        self->unk6++;
    }
}

void train_soldier_jump_rise(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->y_speed < 0) {
        SP_CUR_MAIN_OBJ->ext.main_49.unk80 = 4;
        set_animation(self, 9);
        self->unk5 = 3;
        self->gravity = FIXED(0.2578125);
        self->unk6 = 0;
        self->y_speed = 0;
        self->x_accel = 0;
        self->air_state = -1;
    }
}

void train_soldier_rest(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (++SP_CUR_MAIN_OBJ->ext.main_49.index == 0x3C) {
        set_animation(self, 1);
        self->unk5 = 2;
        self->unk6 = 0;
    }
}

void train_soldier_shoot(struct MainObj* self)
{
    train_soldier_shoot_funcs[self->unk6](self);
}

void train_soldier_shoot_aim(struct MainObj* self)
{
    u8 flags;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        flags = SP_CUR_MAIN_OBJ->ext.main_49.unk82;
        if (flags & 0x80) {
            switch (flags & 3) {
            case 0:
                set_animation(self, 0xD);
                break;
            case 1:
                set_animation(self, 0xC);
                break;
            case 2:
                set_animation(self, 0xE);
                break;
            }
        } else {
            set_animation(self, 0x1A);
        }
        self->unk6++;
    }
}

void train_soldier_shoot_fire(struct MainObj* self)
{
    s8 event;
    struct ShotObj* shot;
    animate_object(ANIMATED_OBJECT(self));
    event = self->animation_step.fields.event;
    if (event != 0) {
        if (event == 3) {
            func_8001540C(2, 0x66, self);
        }
        self->unk6++;
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x19;
            shot->unk2 = SP_CUR_MAIN_OBJ->ext.main_49.unk82;
            shot->x_pos.val = self->x_pos.val;
            shot->y_pos.val = self->y_pos.val;
            shot->unk3C = (void*)self->sprite_frames;
            shot->unk40 = self->unk40;
            shot->unk42 = self->unk42 & 0x7FFF;
            shot->bg_offset = self->bg_offset;
            shot->animation_table = (u32**)self->animation_table;
            shot->unk15 = self->unk15;
        }
    }
}

void train_soldier_shoot_recoil(struct MainObj* self)
{
    animate_object((struct AnimatedObj*)self);
    if (self->animation_step.fields.relative_step == 0) {
        set_animation(self, 11);
        self->unk6++;
    }
}

void train_soldier_shoot_end(struct MainObj* self)
{
    struct MainObj* main;
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        if (SP_CUR_MAIN_OBJ->ext.main_49.unk85 == 2) {
            self->unk5 = 7;
        } else {
            self->unk5 = 5;
        }
        self->unk6 = 0;
        self->y_speed = 0;
        self->gravity = 0;
        self->x_speed = 0;
        SP_CUR_MAIN_OBJ->ext.main_49.index = 0;
        main = SP_CUR_MAIN_OBJ;
        if (main->ext.main_49.unk85 == 2) {
            main->ext.main_49.unk83 = 0x5A;
        } else {
            main->ext.main_49.unk83 = 0xB4;
        }
        set_animation(self, 7);
    }
}

u8 train_soldier_guard_hurt_box[] = { 0xF3, 0xEF, 0x1A, 0x25 };

u8 train_soldier_guard_attack_box[] = { 0xF3, 0xEF, 0x1A, 0x22 };

u8 train_soldier_debris[] = {
    0x11,
    0x12,
    0x13,
    0x14,
    0x15,
    0x00,
    0x00,
    0x00,
};

s16 main49_activation_distances[4] = { 128, 144, 160, 0 };

void (*train_soldier_state_funcs[])(struct MainObj*) = {
    func_80068548,
    train_soldier_main,
    train_soldier_despawn,
    train_soldier_wait_for_player,
};

void (*train_soldier_step_funcs[])(struct MainObj*) = {
    (void (*)(struct MainObj*))enemy_hit_reaction,
    train_soldier_idle,
    train_soldier_walk,
    train_soldier_fall,
    train_soldier_jump,
    train_soldier_rest,
    train_soldier_shoot,
    train_soldier_guard,
};

void (*train_soldier_walk_funcs[])(struct MainObj*) = {
    func_80068B80,
    train_soldier_walk_move,
};

void (*train_soldier_guard_funcs[])(struct MainObj*) = {
    train_soldier_guard_start,
    train_soldier_guard_hold,
};

void (*train_soldier_fall_funcs[])(struct MainObj*) = {
    train_soldier_fall_drop,
    train_soldier_fall_land,
};

void (*train_soldier_jump_funcs[])(struct MainObj*) = {
    train_soldier_jump_crouch,
    train_soldier_jump_rise,
};

void (*train_soldier_shoot_funcs[])(struct MainObj*) = {
    train_soldier_shoot_aim,
    train_soldier_shoot_fire,
    train_soldier_shoot_recoil,
    train_soldier_shoot_end,
};
