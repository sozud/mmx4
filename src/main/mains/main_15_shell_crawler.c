// MainObj, main_object_update_funcs[15]
// 8004D930..8004E890
#include "common.h"
#include "func_tables.h"

void shell_crawler_buried(struct MainObj* self)
{
    if (!(func_8002D724(PLAYER_OBJECT(self), self->x_pos.i.hi,
              self->y_pos.i.hi)
            & 0xFF)) {
        self->state = 1;
        self->unk5 = 1;
        self->unk2 = 0;
        self->hurt_box = &shell_crawler_body_box;
        self->attack_box = &shell_crawler_body_box;
    }

    if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x40) == 0) {
        if (self->unk2 == 2) {
            update_on_screen(BASE_OBJECT(self), 0x25, 0x25);
        }
    } else {
        self->state = 2;
    }
}

// shell_crawler_check_hop
INCLUDE_ASM("main/nonmatchings/mains/main_15_shell_crawler", func_8004D9CC);

// shell_crawler_check_shell
INCLUDE_ASM("main/nonmatchings/mains/main_15_shell_crawler", func_8004DB10);

// shell_crawler_check_shoot
INCLUDE_ASM("main/nonmatchings/mains/main_15_shell_crawler", func_8004DCB0);

void shell_crawler_hop(struct MainObj* self)
{
    s8 state;

    animate_object(ANIMATED_OBJECT(self));
    state = self->unk6;
    if (state == 0) {
        if (self->animation_step.fields.event != 0) {
            self->unk6 = state + 1;
        }
    } else {
        move_with_gravity(ANIMATED_OBJECT(self));
        if (self->y_speed < 0) {
            self->unk6++;
            set_animation(self, 3);
            self->unk5 = 2;
            self->unk6 = 0;
            self->y_speed = 0;
            self->gravity = FIXED(0.2578125);
            self->x_accel = 0;
            self->air_state = -1;
        }
    }
}

void shell_crawler_land(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->unk6 == 0) {
        self->collision_data = (const u16*)D_801069F4;
        move_with_gravity(ANIMATED_OBJECT(self));
        if (self->collision_flags & 8) {
            set_animation(self, 4);
            self->unk6++;
            self->y_speed = 0;
            self->gravity = 0;
            self->x_speed = 0;
            self->x_accel = 0;
        }
    } else if (self->animation_step.fields.relative_step == 0) {
        set_animation(self, 1);
        self->unk5 = 1;
        self->unk6 = 0;
        self->air_state = 0;
    }
}

void shell_crawler_shell(struct MainObj* self)
{
    switch (self->unk6) {
    case 0:
        self->unk6++;
        set_animation(self, 5);
        self->unk7C = 0x3C;
    case 1:
        if (0 != self->animation_step.fields.event) {
            self->collision_data = D_801060F0;
            self->hurt_box = &shell_crawler_shell_box;
            self->attack_box = &shell_crawler_shell_box;
        }
        if (--self->unk7C == 0) {
            self->unk6++;
            set_animation(self, 6);
        }
        break;
    case 2:
        if (self->animation_step.fields.relative_step == 0) {
            set_animation(self, 1);
            self->ext.main_0.background_relative &= 0xFE;
            self->unk5 = 1;
            self->unk6 = 0;
            self->collision_data = D_801069F4;
            self->hurt_box = &shell_crawler_body_box;
            self->attack_box = &shell_crawler_body_box;
            self->ext.main_0.flags[0] = 0x78;
        }
        break;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void shell_crawler_shoot(struct MainObj* self)
{
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->animation_step.fields.event = 0;
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 8;
            shot->x_pos.val = self->x_pos.val;
            shot->y_pos.val = self->y_pos.val;
            shot->unk3C = (void*)self->sprite_frames;
            shot->unk40 = self->unk40;
            shot->unk42 = self->unk42;
            shot->bg_offset = (u8)self->bg_offset;
            shot->animation_table = (u32**)self->animation_table;
            shot->unk15 = self->unk15;
        }
    }
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5 = 1;
        self->unk6 = 0;
        set_animation(self, 1);
        self->ext.main_0.flags[1] = 0x78;
        self->ext.main_0.background_relative &= 0xFD;
    }
}

void shell_crawler_walk(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->collision_data = D_801069F4;
        self->hurt_box = &shell_crawler_body_box;
        self->attack_box = &shell_crawler_body_box;
        self->unk6++;
        set_animation(self, 1);
        self->x_speed = (self->unk15 != 0 ? FIXED(0.375) : FIXED(-0.375));
        self->x_accel = 0;
        self->y_speed = 0;
        self->gravity = 0;
    }

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

// shell_crawler_frozen
INCLUDE_ASM("main/nonmatchings/mains/main_15_shell_crawler", func_8004E300);

// shell_crawler_thaw
INCLUDE_ASM("main/nonmatchings/mains/main_15_shell_crawler", func_8004E490);

// shell_crawler_init
INCLUDE_ASM("main/nonmatchings/mains/main_15_shell_crawler", func_8004E55C);

void shell_crawler_main(struct MainObj* self)
{
    s32 hit;

    if ((engine_obj.stage == 0x2 && engine_obj.substage == 1) && engine_obj.character_state.bytes[0] != 0) {
        if ((self->x_pos.i.hi >= 0xC0F && self->x_pos.i.hi <= 0xDF0) || (u16)(self->x_pos.i.hi - 0x100F) < 0x1E2
            || (u16)(self->x_pos.i.hi - 0x1315) < 0x1DC || (self->x_pos.i.hi >= 0x1613 && self->x_pos.i.hi <= 0x17D1)) {
            self->state = 3;
            self->unk6 = 0;
            return;
        }
    }
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    hit = func_8002DD04(self);
    if (hit < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(4, shell_crawler_debris, self);
        drop_item(BASE_OBJECT(self), 0x12);
        self->state++;
        return;
    }
    func_8004DB10(self);
    func_8004D9CC(self);
    func_8004DCB0(self);
    shell_crawler_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x40) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x25, 0x25);
    } else {
        self->state++;
    }
}

void shell_crawler_despawn(struct MainObj* self)
{
    despawn_object(OBJECT_HEADER(self));
}

void shell_crawler_update(struct MainObj* self)
{
    shell_crawler_state_funcs[self->state](self);
    if (self->state != 5) {
        CollisionRelated(PLAYER_OBJECT(self));
    }
}

struct Unk_unk68 shell_crawler_terrain_box = { 0, 1, 11, 12 };

struct Unk_unk68 shell_crawler_body_box = { -11, -16, 21, 29 };

struct Unk_unk68 shell_crawler_shell_box = { -12, -4, 21, 18 };

union AnimationStep shell_crawler_anim_0[] = {
    { 0x00000001 },
};

union AnimationStep shell_crawler_anim_1[] = {
    { 0x01010008 },
    { 0x02010008 },
    { 0x03010008 },
    { 0x04010003 },
    { 0x05010005 },
    { 0x06010008 },
    { 0x07010008 },
    { 0x08010008 },
    { 0x09010003 },
    { 0x0AF70005 },
};

union AnimationStep shell_crawler_anim_2[] = {
    { 0x00010006 },
    { 0x0B01000A },
    { 0x0C010102 },
    { 0x0D010002 },
    { 0x0E010003 },
    { 0x0E000001 },
};

union AnimationStep shell_crawler_anim_3[] = {
    { 0x0F010002 },
    { 0x10FF0002 },
};

union AnimationStep shell_crawler_anim_4[] = {
    { 0x11010003 },
    { 0x0B01000A },
    { 0x12010002 },
    { 0x00010003 },
    { 0x12010002 },
    { 0x12000001 },
};

union AnimationStep shell_crawler_anim_5[] = {
    { 0x00010006 },
    { 0x12010001 },
    { 0x13010002 },
    { 0x14010102 },
    { 0x15010001 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x17010002 },
    { 0x18000001 },
};

union AnimationStep shell_crawler_anim_6[] = {
    { 0x18010006 },
    { 0x17010001 },
    { 0x16010002 },
    { 0x15010002 },
    { 0x14010001 },
    { 0x13010002 },
    { 0x12010002 },
    { 0x00010002 },
    { 0x12010002 },
    { 0x00000001 },
};

union AnimationStep shell_crawler_anim_7[] = {
    { 0x00010006 },
    { 0x19010006 },
    { 0x1A010008 },
    { 0x1B010102 },
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x0001000A },
    { 0x00000001 },
};

union AnimationStep shell_crawler_anim_8[] = {
    { 0x1E010002 },
    { 0x1F010002 },
    { 0x20FE0002 },
};

union AnimationStep shell_crawler_anim_9[] = {
    { 0x21000001 },
};

union AnimationStep shell_crawler_anim_10[] = {
    { 0x22000001 },
};

union AnimationStep shell_crawler_anim_11[] = {
    { 0x23000001 },
};

union AnimationStep shell_crawler_anim_12[] = {
    { 0x24000001 },
};

union AnimationStep shell_crawler_anim_13[] = {
    { 0x25000001 },
};

union AnimationStep* shell_crawler_animations[14] = {
    shell_crawler_anim_0,
    shell_crawler_anim_1,
    shell_crawler_anim_2,
    shell_crawler_anim_3,
    shell_crawler_anim_4,
    shell_crawler_anim_5,
    shell_crawler_anim_6,
    shell_crawler_anim_7,
    shell_crawler_anim_8,
    shell_crawler_anim_9,
    shell_crawler_anim_10,
    shell_crawler_anim_11,
    shell_crawler_anim_12,
    shell_crawler_anim_13,
};

u8 shell_crawler_debris[4] = { 9, 10, 11, 12 };

void (*shell_crawler_step_funcs[6])() = {
    enemy_hit_reaction,
    shell_crawler_walk,
    shell_crawler_land,
    shell_crawler_shell,
    shell_crawler_shoot,
    shell_crawler_hop,
};

void (*shell_crawler_state_funcs[6])(struct MainObj*) = {
    func_8004E55C,
    shell_crawler_main,
    shell_crawler_despawn,
    func_8004E300,
    func_8004E490,
    shell_crawler_buried,
};
