// MainObj, main_object_update_funcs[37]
// 8005FDBC..80060A88
#include "common.h"
#include "main/mains/main_37_rocket_spiker.h"
#include "main/visuals/visual_08_ice_shard.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/CB184.h"
#include "main/collision.h"
#include "main/misc/misc_02_rubble.h"
#include "main/object_motion.h"
#include "main/objects.h"
#include "main/visuals/visual_03_small_effect.h"

#ifdef MMX4_PC
#include "main/collision_bounds.h"
#endif

void rocket_spiker_main(struct MainObj*);
void rocket_spiker_despawn(struct MainObj* arg0);

// rocket_spiker_step_funcs
void rocket_spiker_resume_step(struct MainObj* arg0);
void rocket_spiker_drop(struct MainObj* arg0);
void rocket_spiker_crawl(struct MainObj* arg0);
void rocket_spiker_boost(struct MainObj* arg0);

// rocket_spiker_drop_funcs
void rocket_spiker_drop_fall(struct MainObj*);

void rocket_spiker_drop_land(struct MainObj*);

// rocket_spiker_crawl_funcs
void rocket_spiker_crawl_move(struct MainObj*);
void rocket_spiker_crawl_fall(struct MainObj*);
void rocket_spiker_crawl_turn(struct MainObj*);

// rocket_spiker_boost_funcs
void rocket_spiker_boost_wait(struct MainObj*);
void func_800606D8(struct MainObj*);
void rocket_spiker_boost_launch(struct MainObj*);

void rocket_spiker_boost_pause(struct MainObj*);
void rocket_spiker_boost_brake(struct MainObj*);
void rocket_spiker_boost_rest(struct MainObj*);

extern void (*rocket_spiker_state_funcs[])(struct MainObj*);
extern void (*rocket_spiker_drop_funcs[])(struct MainObj*);
extern void (*rocket_spiker_crawl_funcs[])(struct MainObj*);
extern void (*rocket_spiker_boost_funcs[])(struct MainObj*);

extern u8 rocket_spiker_debris[12];

void rocket_spiker_update(struct MainObj* self)
{
    rocket_spiker_state_funcs[self->state](self);
    if (self->unk5 != 4) {
        CollisionRelated(PLAYER_OBJECT(self));
    }
}

// rocket_spiker_init
#ifdef MMX4_PC
void func_8005FE1C(struct MainObj* arg0);
void func_800608CC(struct MainObj* arg0);
#define MAIN_37_U8(object, offset) (((u8*)&(object)->ext.main_37)[(offset)-0x80])
#define MAIN_37_S16(object, offset) (*(s16*)&MAIN_37_U8(object, offset))
extern union AnimationStep* rocket_spiker_animations[28];
extern struct Unk_unk68 D_800FE4D4;
extern struct Unk_unk68 D_800FE4D8;
extern struct Unk_unk68 D_800FE4DC;
extern struct Unk_unk68 D_800FE4E0;
extern struct Unk_unk68 D_800FE4E4;
extern struct Unk_unk68 D_80107474[];
void rocket_spiker_face_player(struct AnimatedObj* arg0);
#endif

#ifdef MMX4_PC
void func_8005FE1C(struct MainObj* arg0)
{
    static const s16 lanes[3][3] = {
        { 0x3F0, 0x480, 0x410 },
        { 0x390, 0x40B, 0x3B0 },
        { 0x330, 0x380, 0x350 },
    };
    u8 lane;

    arg0->hp = 6;
    arg0->contact_damage = 4;
    arg0->invincibility_timer = 0;
    arg0->unk62 = 2;
    arg0->animation_table = (const u8* const*)rocket_spiker_animations;
    arg0->terrain_box = &D_800FE4E4;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->air_state = 0;
    arg0->unk16 = 6;
    switch (arg0->unk2) {
    case 0:
        arg0->collision_data = (const u16*)D_80107474;
        arg0->hurt_box = (const u8*)&D_800FE4D4;
        arg0->attack_box = (const u8*)&D_800FE4D8;
        rocket_spiker_face_player(ANIMATED_OBJECT(arg0));
        arg0->x_speed = 0;
        arg0->y_speed = -0x18000;
        set_animation(arg0, 1);
        arg0->unk5 = 2;
        break;
    case 1:
    case 2:
        arg0->collision_data = (const u16*)D_80107474;
        arg0->hurt_box = (const u8*)&D_800FE4D4;
        arg0->attack_box = (const u8*)&D_800FE4D8;
        arg0->unk15 = arg0->unk2 == 2 ? 0x40 : 0;
        arg0->x_speed = arg0->unk2 == 2 ? 0x18000 : -0x18000;
        arg0->y_speed = 0;
        set_animation(arg0, 0);
        arg0->unk5 = 3;
        break;
    case 3:
        arg0->collision_data = (const u16*)D_801060F0;
        arg0->hurt_box = (const u8*)&D_800FE4DC;
        arg0->attack_box = (const u8*)&D_800FE4E0;
        arg0->y_speed = 0;
        arg0->unk42 += 2;
        if (arg0->x_pos.i.hi >= 0x1799) {
            MAIN_37_S16(arg0, 0x84) = 0x17E0;
            arg0->x_pos.val = 0x18180000;
            arg0->x_speed = 0x10000;
            arg0->unk15 = 0;
            MAIN_37_U8(arg0, 0x81) = 0;
        } else {
            MAIN_37_S16(arg0, 0x84) = 0x1710;
            arg0->x_pos.val = 0x17080000;
            arg0->x_speed = -0x10000;
            arg0->unk15 = 0x40;
            MAIN_37_U8(arg0, 0x81) = 1;
        }
        if (arg0->y_pos.i.hi < 0x370)
            MAIN_37_U8(arg0, 0x81) += 2;
        if (arg0->y_pos.i.hi < 0x3D0)
            MAIN_37_U8(arg0, 0x81) += 2;
        lane = MAIN_37_U8(arg0, 0x81);
        if (lane < 6) {
            MAIN_37_S16(arg0, 0x86) = lanes[lane / 2][0];
            MAIN_37_S16(arg0, 0x88) = lanes[lane / 2][1];
            arg0->y_pos.val = lanes[lane / 2][2] << 16;
        }
        set_animation(arg0, 7);
        arg0->unk5 = 4;
        break;
    }
    MAIN_37_U8(arg0, 0x8C) = 0;
    MAIN_37_U8(arg0, 0x8D) = 1;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->state = 1;
    arg0->unk6 = 0;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_37_rocket_spiker", func_8005FE1C);
#endif

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
#ifdef MMX4_PC
void func_800608CC(struct MainObj* arg0)
{
    s32 velocity;

    move_with_gravity(ANIMATED_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->unk15 == 0) {
        if (arg0->x_pos.i.hi >= 0x17A0)
            return;
        arg0->x_pos.i.hi = 0x17A0;
        func_8001540C(2, 0x5A, arg0);
        velocity = 0x58000;
    } else {
        if (arg0->x_pos.i.hi < 0x1781)
            return;
        velocity = -0x58000;
        arg0->x_pos.i.hi = 0x1780;
    }
    arg0->unk7C = 0x28;
    arg0->x_accel = 0x2000;
    arg0->x_speed = velocity;
    arg0->unk6 = 4;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_37_rocket_spiker", func_800608CC);
#endif

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

#if defined(MMX4_PC) && !defined(MMX4_WIN32)
static struct {
    union AnimationStep rocket_spiker_anim_6[45];
    union AnimationStep rocket_spiker_anim_7[8];
} rocket_spiker_anim_run = {
    {
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
    },
    {
        { 0x17010003 },
        { 0x18010003 },
        { 0x19010003 },
        { 0x1A010003 },
        { 0x1B010003 },
        { 0x1C010003 },
        { 0x1D010003 },
        { 0x1EF90003 },
    },
};
#define rocket_spiker_anim_6 rocket_spiker_anim_run.rocket_spiker_anim_6
#define rocket_spiker_anim_7 rocket_spiker_anim_run.rocket_spiker_anim_7
#endif

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
