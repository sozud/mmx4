// MainObj, main_object_update_funcs[38]
// 80060A88..80061590
#include "common.h"
#include "func_tables.h"

void train_cannon_update(struct MainObj* self)
{
    train_cannon_state_funcs[self->state](self);
}

void train_cannon_init(struct MainObj* obj)
{
    obj->active = 0x41;
    obj->hp = 0x12;
    obj->contact_damage = 6;
    obj->invincibility_timer = 0;
    obj->bg_offset = g_Player.bg_offset;
    obj->collision_data = &D_801074F4;
    obj->animation_table = (const u8* const*)train_cannon_animations;
    obj->unk16 = 5;
    obj->terrain_box = &train_cannon_terrain_box;
    obj->hurt_box = &train_cannon_hurt_box;
    obj->unk15 = 0;
    obj->x_speed = 0;
    obj->y_speed = 0;
    obj->x_accel = 0;
    obj->gravity = 0;
    obj->air_state = 0;
    obj->attack_box = &train_cannon_attack_box;
    obj->unk18.val = obj->x_pos.val;
    obj->unk1C.val = obj->y_pos.val;
    set_animation(obj, 0);
    obj->unk7E = 0xA;
    obj->ext.main_38.saved_unk5 = 0;
    obj->ext.main_38.unk84 = 0;
    obj->ext.main_38.unk88 = 0;
    obj->ext.main_38.unk8C = 0;
    obj->ext.main_38.unk90 = 0;
    obj->ext.main_38.unk94 = 0;
    obj->unk7C = 0;
    obj->unk5 = 2;
    obj->unk6 = 0;
    obj->state++;
}

void train_cannon_main(struct MainObj* self)
{
    s32 collision;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    train_cannon_step_funcs[self->unk5](self);
    collision = func_8002DD04(self);
    func_8002D9BC(self);
    collide_with_players(PLAYER_OBJECT(self));
    if (self->unk5 != 0) {
        self->ext.main_38.saved_unk5 = self->unk5;
    }
    if (collision < 0) {
        spawn_debris(6, train_cannon_debris, self);
        if (engine_obj.stage == 8) {
            apply_tile_effect(0xB, (s16)(self->x_pos.i.hi - 0x28), self->y_pos.i.hi);
        }
        self->ext.main_38.unk88 = 2;
        self->ext.main_38.unk8C = 1;
        self->unk7C = 0x20;
        self->unk7E = 5;
        self->on_screen = 0;
        self->state++;
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x50, 0x40) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x40, 0x20);
        return;
    }
    if (self->unk5 != 4) {
        if (g_Player.x_pos.val > self->x_pos.val) {
            self->state += 2;
        } else {
            self->unk5 = 2;
        }
    }
}

void train_cannon_explode(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        drop_item(BASE_OBJECT(self), 8);
        self->state++;
    }
    if (--self->unk7E == 0) {
        func_800AF878(BASE_OBJECT(self), 0, 0x18, 0x10);
        self->unk7E = 5;
    }
}

void train_cannon_despawn(struct MainObj* self)
{
    self->ext.main_38.unk88 = 2;
    if (self->ext.main_38.unk8C != 0) {
        ZeroObjectState(OBJECT_HEADER(self));
    } else {
        despawn_object(OBJECT_HEADER(self));
    }
}

void train_cannon_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_38.saved_unk5;
}

void train_cannon_idle(struct MainObj* self)
{
    train_cannon_idle_funcs[self->unk6](self);
}

void train_cannon_idle_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(ANIMATED_OBJECT(self), 0);
    self->unk6++;
}

void train_cannon_idle_pick(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7E == 0) {
        switch (self->ext.main_38.unk84) {
        case 0:
            self->unk5 = 3;
            self->unk7E = 0x14;
            break;
        case 1:
            self->unk5 = 5;
            self->unk7E = 0x14;
            break;
        case 2:
            self->unk5 = 5;
            self->unk7E = 0xA;
            break;
        }
        self->unk6 = 0;
        if (self->ext.main_38.unk84 != 2) {
            self->ext.main_38.unk84++;
        } else {
            self->ext.main_38.unk84 = 0;
        }
    }
}

void train_cannon_charge(struct MainObj* self)
{
    train_cannon_charge_funcs[self->unk6](self);
}

void train_cannon_charge_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 1);
    func_8001540C(2, 0x60, self);
    train_cannon_spawn_charge_glow(VISUAL_OBJECT(self));
    self->unk7C = 0x50;
    self->unk6++;
}

void train_cannon_charge_wait(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk5 = 4;
        self->ext.main_38.unk88 = 1;
        self->unk6 = 0;
    }
}

void train_cannon_blast(struct MainObj* self)
{
    train_cannon_blast_funcs[self->unk6](self);
}

void train_cannon_blast_fire(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    func_8001540C(2, 0x61, self);
    set_animation(self, 2);
    self->ext.main_38.unk88 = 2;
    train_cannon_fire_blast(self);
    self->unk7C = 0x6E;
    self->unk6++;
}

void train_cannon_blast_end(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        set_animation(self, 0);
        self->ext.main_38.unk88 = 0;
        self->unk5 = 2;
        self->unk6 = 0;
    }
}

void train_cannon_volley(struct MainObj* self)
{
    train_cannon_volley_funcs[self->unk6](self);
}

void train_cannon_volley_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    func_8001540C(2, 0x62, self);
    set_animation(self, 5);
    self->unk7C = 0xA;
    self->unk6++;
}

void train_cannon_volley_fire(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        train_cannon_fire_volley(self);
        self->unk7C = 0x14;
        self->unk6++;
    }
}

void train_cannon_volley_end(struct MainObj* self)
{
    animate_object((struct AnimatedObj*)self);
    if (--self->unk7C == 0) {
        self->unk5 = 6;
        self->unk6 = 0;
    }
}

void train_cannon_recoil(struct MainObj* self)
{
    train_cannon_recoil_funcs[self->unk6](self);
}

void train_cannon_recoil_start(struct MainObj* self)
{
    animate_object((struct AnimatedObj*)self);
    set_animation(self, 6);
    self->unk7C = 0x28;
    self->unk6++;
}

void train_cannon_recoil_end(struct MainObj* self)
{
    animate_object((struct AnimatedObj*)self);
    if (--self->unk7C == 0) {
        self->unk5 = 2;
        self->unk6 = 0;
    }
}

void train_cannon_fire_blast(struct PlayerObj* self)
{
    s32 is_zero;
    struct ShotObj* shot;
    u8 i;
    for (i = 0; i < 2; i++) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x14;
            shot->unk2 = i;
            shot->unk7C = WEAPON_OBJECT(self);
            shot->unk42 = self->unk42;
            shot->animation_table = train_cannon_animations;
            shot->unk3C = self->unk3C;
            shot->unk40 = self->unk40;
            shot->unk15 = self->unk15;
            shot->bg_offset = self->bg_offset;
            is_zero = (self->unk2 == 0);
            shot->unk16 = is_zero ? 2 : 1;
        }
    }
}

void train_cannon_fire_volley(struct MainObj* self)
{
    s32 is_zero;
    struct ShotObj* shot;
    u8 i;
    for (i = 0; i < 2; i++) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x15;
            shot->unk2 = i;
            shot->unk7C = WEAPON_OBJECT(self);
            shot->unk42 = self->unk42;
            shot->animation_table = (u32**)train_cannon_animations;
            shot->unk3C = (void*)self->sprite_frames;
            shot->unk40 = self->unk40;
            shot->unk15 = self->unk15;
            shot->bg_offset = self->bg_offset;
            is_zero = (i == 0);
            shot->unk16 = is_zero ? 4 : 6;
        }
    }
}

void train_cannon_spawn_charge_glow(struct VisualObj* self)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x10;
        obj->unk2 = 0;
        obj->unk50 = (struct PlayerObj*)self;
        obj->unk42 = self->unk42;
        obj->animation_table = train_cannon_animations;
        obj->unk3C = self->unk3C;
        obj->unk40 = self->unk40;
        obj->bg_offset = self->bg_offset;
        obj->unk16 = 4;
        obj->unk15 = self->unk15;
        obj->x_pos.val = self->x_pos.val;
        obj->y_pos.val = self->y_pos.val;
    }
}

struct Unk_unk68 train_cannon_hurt_box = { -54, -9, 90, 25 };

struct Unk_unk68 train_cannon_attack_box = { -52, -11, 86, 25 };

struct Unk_unk68 train_cannon_terrain_box = { -10, 8, 45, 11 };

union AnimationStep train_cannon_anim_0[] = {
    { 0x00000001 },
};

union AnimationStep train_cannon_anim_1[] = {
    { 0x00010001 },
    { 0x01010006 },
    { 0x02010005 },
    { 0x03010004 },
    { 0x04010004 },
    { 0x05010004 },
    { 0x06010004 },
    { 0x07FD0004 },
};

union AnimationStep train_cannon_anim_2[] = {
    { 0x0C010002 },
    { 0x0DFF0002 },
};

union AnimationStep train_cannon_anim_3[] = {
    { 0x0F01000A },
    { 0x10010008 },
    { 0x11010004 },
    { 0x12010001 },
    { 0x13010001 },
    { 0x14010001 },
    { 0x15FD0001 },
};

union AnimationStep train_cannon_anim_4[] = {
    { 0x1601000A },
    { 0x17010008 },
    { 0x18010004 },
    { 0x19010001 },
    { 0x1A010001 },
    { 0x1B010001 },
    { 0x1CFD0001 },
};

union AnimationStep train_cannon_anim_5[] = {
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1F010002 },
    { 0x20010003 },
    { 0x21010004 },
    { 0x22000005 },
};

union AnimationStep train_cannon_anim_6[] = {
    { 0x22010005 },
    { 0x23010005 },
    { 0x2401000A },
    { 0x25010005 },
    { 0x2601000A },
    { 0x27000005 },
};

union AnimationStep train_cannon_anim_7[] = {
    { 0x28000001 },
};

union AnimationStep train_cannon_anim_8[] = {
    { 0x29000001 },
};

union AnimationStep train_cannon_anim_9[] = {
    { 0x2A000001 },
};

union AnimationStep train_cannon_anim_10[] = {
    { 0x2B000001 },
};

union AnimationStep train_cannon_anim_11[] = {
    { 0x14010001 },
    { 0x13010001 },
    { 0x12010001 },
    { 0x11010004 },
    { 0x10010008 },
    { 0x0F00000A },
};

union AnimationStep train_cannon_anim_12[] = {
    { 0x1B010001 },
    { 0x1A010001 },
    { 0x19010001 },
    { 0x18010004 },
    { 0x17010008 },
    { 0x1600000A },
};

union AnimationStep train_cannon_anim_13[] = {
    { 0x2C000001 },
};

union AnimationStep train_cannon_anim_14[] = {
    { 0x2D000001 },
};

union AnimationStep train_cannon_anim_15[] = {
    { 0x2E000001 },
};

union AnimationStep train_cannon_anim_16[] = {
    { 0x2F000001 },
};

union AnimationStep train_cannon_anim_17[] = {
    { 0x30000001 },
};

union AnimationStep train_cannon_anim_18[] = {
    { 0x31000001 },
};

union AnimationStep train_cannon_anim_19[] = {
    { 0x08010003 },
    { 0x09010004 },
    { 0x0A010005 },
    { 0x09010004 },
    { 0x08FC0003 },
};

union AnimationStep train_cannon_anim_20[] = {
    { 0x37010003 },
    { 0x0B010003 },
    { 0x37010003 },
    { 0x32010003 },
    { 0x37010003 },
    { 0x33010003 },
    { 0x37010003 },
    { 0x34010003 },
    { 0x37010003 },
    { 0x35010003 },
    { 0x37010003 },
    { 0x36F60003 },
};

union AnimationStep* train_cannon_animations[21] = {
    train_cannon_anim_0,
    train_cannon_anim_1,
    train_cannon_anim_2,
    train_cannon_anim_3,
    train_cannon_anim_4,
    train_cannon_anim_5,
    train_cannon_anim_6,
    train_cannon_anim_7,
    train_cannon_anim_8,
    train_cannon_anim_9,
    train_cannon_anim_10,
    train_cannon_anim_11,
    train_cannon_anim_12,
    train_cannon_anim_13,
    train_cannon_anim_14,
    train_cannon_anim_15,
    train_cannon_anim_16,
    train_cannon_anim_17,
    train_cannon_anim_18,
    train_cannon_anim_19,
    train_cannon_anim_20,
};

u8 train_cannon_debris[8] = { 13, 14, 15, 16, 17, 18, 0, 0 };

void (*train_cannon_state_funcs[])(struct MainObj*) = {
    train_cannon_init,
    train_cannon_main,
    train_cannon_explode,
    train_cannon_despawn,
};

void (*train_cannon_step_funcs[7])() = {
    enemy_hit_reaction,
    train_cannon_resume_step,
    train_cannon_idle,
    train_cannon_charge,
    train_cannon_blast,
    train_cannon_volley,
    train_cannon_recoil,
};

void (*train_cannon_idle_funcs[2])() = { train_cannon_idle_start, train_cannon_idle_pick };

void (*train_cannon_charge_funcs[2])() = { train_cannon_charge_start, train_cannon_charge_wait };

void (*train_cannon_blast_funcs[2])(struct MainObj*) = { train_cannon_blast_fire, train_cannon_blast_end };

void (*train_cannon_volley_funcs[3])(struct MainObj*) = { train_cannon_volley_start, train_cannon_volley_fire, train_cannon_volley_end };

void (*train_cannon_recoil_funcs[2])() = { train_cannon_recoil_start, train_cannon_recoil_end };
