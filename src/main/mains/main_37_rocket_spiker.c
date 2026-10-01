// MainObj, main_object_update_funcs[37]
// 8005FDBC..80060A88
#include "common.h"

extern u8 rocket_spiker_debris[12];
#include "func_tables.h"

void rocket_spiker_update(struct MainObj* self)
{
    rocket_spiker_state_funcs[self->state](self);
    if (self->unk5 != 4) {
        CollisionRelated(PLAYER_OBJECT(self));
    }
}

// rocket_spiker_init
INCLUDE_ASM("main/nonmatchings/mains/main_37_rocket_spiker", func_8005FE1C);

extern void (*rocket_spiker_step_funcs[])(struct MainObj*);

void rocket_spiker_main(struct MainObj* self)
{
    s32 hit;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    rocket_spiker_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    self->ext.main_37.saved_unk5 = self->unk5;
    hit = func_8002DD04(self);
    if (hit < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(0xA, rocket_spiker_debris, self);
        drop_item(BASE_OBJECT(self), 0x13);
        self->state = 2;
    } else if (self->unk2 == 3) {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
    } else if (func_8002B1E8(BASE_OBJECT(self), 0x60, 0x40) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
    } else {
        self->state = 2;
    }
}

void rocket_spiker_despawn(struct MainObj* self)
{
    self->unk62 = 0;
    self->ext.main_37.unk80.word = 0;
    self->ext.main_37.unk84.val = 0;
    self->ext.main_37.unk88.val = 0;
    self->ext.main_37.unk8C.val = 0;
    self->ext.main_37.saved_unk5 = 0;
    despawn_object(OBJECT_HEADER(self));
}

void rocket_spiker_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_37.saved_unk5;
}

void rocket_spiker_drop(struct MainObj* self)
{
    rocket_spiker_drop_funcs[self->unk6](self);
}

void rocket_spiker_drop_fall(struct MainObj* self)
{
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        self->ext.main_37.unk80.saved_direction = self->unk15;
        rocket_spiker_face_player(ANIMATED_OBJECT(self));
        self->y_speed = 0;
        if (self->unk15 == 0) {
            self->x_speed = FIXED(-1.5);
        } else {
            self->x_speed = FIXED(1.5);
        }
        if (self->unk15 != self->ext.main_37.unk80.saved_direction) {
            set_animation(self, 2);
            self->unk5 = 3;
            self->unk6 = 2;
        } else {
            set_animation(self, 3);
            self->unk6 = 1;
        }
    }
}

void rocket_spiker_drop_land(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        set_animation(self, 0);
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void rocket_spiker_crawl(struct MainObj* self)
{
    rocket_spiker_crawl_funcs[self->unk6](self);
}

void rocket_spiker_crawl_move(struct MainObj* self)
{
    s8 direction_mask;

    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->unk15 == 0) {
        direction_mask = self->collision_flags & 2;
    } else {
        direction_mask = self->collision_flags & 1;
    }
    if (direction_mask != 0) {
        self->unk6 = 2;
        self->unk15 ^= 0x40;
        self->x_speed = -self->x_speed;
        set_animation(self, 2);
        return;
    }
    if ((self->collision_flags & 8) == 0) {
        self->x_speed = 0;
        self->y_speed = FIXED(-1.5);
        set_animation(self, 3);
        self->unk6 = 1;
    }
}

void rocket_spiker_crawl_fall(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        set_animation(self, 1);
        self->unk5 = 2;
        self->unk6 = 0;
    }
}

void rocket_spiker_crawl_turn(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        set_animation(self, 0);
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void rocket_spiker_boost(struct MainObj* self)
{
    rocket_spiker_boost_funcs[self->unk6](self);
}

void rocket_spiker_boost_wait(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->ext.main_37.unk8C.bytes[1] == 0) {
        func_8001540C(2, 0x59, self);
        self->ext.main_37.unk8C.bytes[1] = 0x1E;
    }
    if (g_Player.y_pos.i.hi <= self->ext.main_37.unk88.i.lo) {
        self->unk7C = 0x26;
        self->unk6 = 1;
    }
    if (!(self->unk7E & 3)) {
        if (self->unk15 == 0) {
            spawn_owner_debris(1, &rocket_spiker_exhaust_variants[self->ext.main_37.unk8C.bytes[0]], self, 0x7988, FIXED(-32), 0);
        } else {
            spawn_owner_debris(1, &rocket_spiker_exhaust_variants[self->ext.main_37.unk8C.bytes[0]], self, 0x7988, FIXED(32), 0);
        }
        if (++self->ext.main_37.unk8C.bytes[0] == 0xA) {
            self->ext.main_37.unk8C.bytes[0] = 0;
        }
    }
    if (!(++self->unk7E & 7)) {


        func_800B10E4(0x11, (s16)(self->ext.main_37.unk84.i.lo + 0x10), (s16)(self->ext.main_37.unk84.u.hi + 0x10), (s16)(self->ext.main_37.unk84.i.lo + 0x20), (s16)(self->ext.main_37.unk84.u.hi + 0x30), 1);
    }
}

// rocket_spiker_boost_aim
void func_800606D8(struct MainObj* main)
{
    animate_object(ANIMATED_OBJECT(main));
    if (--main->ext.main_37.unk8C.bytes[1] == 0) {
        func_8001540C(2, 0x59, main);
        main->ext.main_37.unk8C.bytes[1] = 0x1E;
    }
    if (--main->unk7C == 0) {
        // original build had no prototype here: args are passed unnarrowed
        ((struct VisualObj * (*)()) spawn_explosion_at)(2, main->ext.main_37.unk84.i.lo + 0x18, main->ext.main_37.unk84.i.hi + 0x20, 1);
        apply_tile_effect((main->ext.main_0.index & 1) + 5, main->ext.main_37.unk84.i.lo,
            main->ext.main_37.unk84.i.hi);
        main->unk7C = 0x20;
        main->unk6 = 2;
    }
    if (!(main->unk7E & 3)) {
        if (main->unk15 == 0) {
            spawn_owner_debris(1, &rocket_spiker_exhaust_variants[main->ext.main_37.unk8C.bytes[0]], main, 0x7988, FIXED(-32), 0);
        } else {
            spawn_owner_debris(1, &rocket_spiker_exhaust_variants[main->ext.main_37.unk8C.bytes[0]], main, 0x7988, FIXED(32), 0);
        }
        if (++main->ext.main_37.unk8C.bytes[0] == 0xA) {
            main->ext.main_37.unk8C.bytes[0] = 0;
        }
    }
    if (!(++main->unk7E & 7)) {
        func_800B10E4(0x11, (s16)(main->ext.main_37.unk84.i.lo + 0x10), (s16)(main->ext.main_37.unk84.i.hi + 0x10), (s16)(main->ext.main_37.unk84.i.lo + 0x20), (s16)(main->ext.main_37.unk84.i.hi + 0x30), 1);
    }
}

void rocket_spiker_boost_launch(struct MainObj* self)
{
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->x_speed = 0;
        self->x_accel = FIXED(0.125);
        self->unk6 = 3;
    }
}

// rocket_spiker_boost_fly
INCLUDE_ASM("main/nonmatchings/mains/main_37_rocket_spiker", func_800608CC);

void rocket_spiker_boost_pause(struct MainObj* self)
{
    animate_object((struct AnimatedObj*)self);
    if (--self->unk7C == 0) {
        self->unk6 = 5;
    }
}

void rocket_spiker_boost_brake(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->x_speed == 0) {
        self->unk7C = 0x28;
        self->unk6 = 6;
    }
}

void rocket_spiker_boost_rest(struct MainObj* self)
{
    animate_object((struct AnimatedObj*)self);
    if (--self->unk7C == 0) {
        self->unk6 = 3;
    }
}

void rocket_spiker_face_player(struct AnimatedObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
}

struct Unk_unk68 D_800FE4D4 = { -19, -18, 37, 28 };

struct Unk_unk68 D_800FE4D8 = { -14, -12, 26, 17 };

struct Unk_unk68 D_800FE4DC = { -23, -14, 37, 31 };

struct Unk_unk68 D_800FE4E0 = { -18, -13, 22, 27 };

struct Unk_unk68 D_800FE4E4 = { 0, 0, 23, 20 };

union AnimationStep rocket_spiker_anim_0[] = {
    { 0x06010002 },
    { 0x07010002 },
    { 0x08FE0002 },
};

union AnimationStep rocket_spiker_anim_1[] = {
    { 0x20010002 },
    { 0x21010002 },
    { 0x22FE0002 },
};

union AnimationStep rocket_spiker_anim_2[] = {
    { 0x09010009 },
    { 0x0A010009 },
    { 0x0A000101 },
};

union AnimationStep rocket_spiker_anim_3[] = {
    { 0x20010004 },
    { 0x20000101 },
};

union AnimationStep rocket_spiker_anim_4[] = {
    { 0x00010001 },
    { 0x01010001 },
    { 0x02FE0001 },
};

union AnimationStep rocket_spiker_anim_5[] = {
    { 0x03010002 },
    { 0x04010002 },
    { 0x05010002 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x05000101 },
};

union AnimationStep rocket_spiker_anim_6[] = {
    { 0x03010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x06010001 },
    { 0x07010001 },
    { 0x08010001 },
    { 0x06010001 },
    { 0x07010001 },
    { 0x08010001 },
    { 0x0B010002 },
    { 0x0C010002 },
    { 0x0D010002 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x10010001 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x10010001 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x10010001 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x14010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x14010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x14010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x14010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x1A010003 },
    { 0x1B010003 },
    { 0x1C010003 },
    { 0x1D010003 },
    { 0x1E010002 },
    { 0x1E010101 },
};

union AnimationStep rocket_spiker_anim_7[] = {
    { 0x17010003 },
    { 0x18010003 },
    { 0x19010003 },
    { 0x1A010003 },
    { 0x1B010003 },
    { 0x1C010003 },
    { 0x1D010003 },
    { 0x1EF90003 },
};

union AnimationStep rocket_spiker_anim_8[] = {
    { 0x23000101 },
};

union AnimationStep rocket_spiker_anim_9[] = {
    { 0x24000101 },
};

union AnimationStep rocket_spiker_anim_10[] = {
    { 0x25000101 },
};

union AnimationStep rocket_spiker_anim_11[] = {
    { 0x26000101 },
};

union AnimationStep rocket_spiker_anim_12[] = {
    { 0x27000101 },
};

union AnimationStep rocket_spiker_anim_13[] = {
    { 0x28000101 },
};

union AnimationStep rocket_spiker_anim_14[] = {
    { 0x29000101 },
};

union AnimationStep rocket_spiker_anim_15[] = {
    { 0x2A000101 },
};

union AnimationStep rocket_spiker_anim_16[] = {
    { 0x2B000101 },
};

union AnimationStep rocket_spiker_anim_17[] = {
    { 0x2C000101 },
};

union AnimationStep rocket_spiker_anim_18[] = {
    { 0x2D000101 },
};

union AnimationStep rocket_spiker_anim_19[] = {
    { 0x2E000101 },
};

union AnimationStep rocket_spiker_anim_20[] = {
    { 0x2F000101 },
};

union AnimationStep rocket_spiker_anim_21[] = {
    { 0x30000101 },
};

union AnimationStep rocket_spiker_anim_22[] = {
    { 0x31000101 },
};

union AnimationStep rocket_spiker_anim_23[] = {
    { 0x32000101 },
};

union AnimationStep rocket_spiker_anim_24[] = {
    { 0x33000101 },
};

union AnimationStep rocket_spiker_anim_25[] = {
    { 0x34000101 },
};

union AnimationStep rocket_spiker_anim_26[] = {
    { 0x35000101 },
};

union AnimationStep rocket_spiker_anim_27[] = {
    { 0x36000101 },
};

union AnimationStep* rocket_spiker_animations[28] = {
    rocket_spiker_anim_0,
    rocket_spiker_anim_1,
    rocket_spiker_anim_2,
    rocket_spiker_anim_3,
    rocket_spiker_anim_4,
    rocket_spiker_anim_5,
    rocket_spiker_anim_6,
    rocket_spiker_anim_7,
    rocket_spiker_anim_8,
    rocket_spiker_anim_9,
    rocket_spiker_anim_10,
    rocket_spiker_anim_11,
    rocket_spiker_anim_12,
    rocket_spiker_anim_13,
    rocket_spiker_anim_14,
    rocket_spiker_anim_15,
    rocket_spiker_anim_16,
    rocket_spiker_anim_17,
    rocket_spiker_anim_18,
    rocket_spiker_anim_19,
    rocket_spiker_anim_20,
    rocket_spiker_anim_21,
    rocket_spiker_anim_22,
    rocket_spiker_anim_23,
    rocket_spiker_anim_24,
    rocket_spiker_anim_25,
    rocket_spiker_anim_26,
    rocket_spiker_anim_27,
};

u8 rocket_spiker_debris[12] = { 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 0, 0 };

u8 rocket_spiker_exhaust_variants[12] = { 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 0, 0 };

void (*rocket_spiker_state_funcs[3])() = {
    func_8005FE1C,
    rocket_spiker_main,
    rocket_spiker_despawn,
};

void (*rocket_spiker_step_funcs[5])() = {
    enemy_hit_reaction,
    rocket_spiker_resume_step,
    rocket_spiker_drop,
    rocket_spiker_crawl,
    rocket_spiker_boost,
};

void (*rocket_spiker_drop_funcs[2])(struct MainObj*) = {
    rocket_spiker_drop_fall,
    rocket_spiker_drop_land,
};

void (*rocket_spiker_crawl_funcs[3])() = {
    rocket_spiker_crawl_move,
    rocket_spiker_crawl_fall,
    rocket_spiker_crawl_turn,
};

void (*rocket_spiker_boost_funcs[7])() = {
    rocket_spiker_boost_wait,
    func_800606D8,
    rocket_spiker_boost_launch,
    func_800608CC,
    rocket_spiker_boost_pause,
    rocket_spiker_boost_brake,
    rocket_spiker_boost_rest,
};
