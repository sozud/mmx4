// MainObj, main_object_update_funcs[41]
// 800623C4..80062D60
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_41_data_hopper.h"
#include "main/objects.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/collision_bounds.h"
#include "main/object_motion.h"
#include "main/1CF60.h"
#include "main/1E1BC.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1CF60.h"
#include "main/1E1BC.h"
#endif

extern struct Unk_unk68 data_hopper_attack_box;

void data_hopper_despawn(struct MainObj*);

// data_hopper_step_funcs
void data_hopper_idle(struct MainObj* arg0);
void data_hopper_stand(struct MainObj* arg0);
void data_hopper_fall(struct MainObj* arg0);

void data_hopper_land(struct MainObj* arg0);

extern void (*data_hopper_state_funcs[])(struct MainObj*);

void data_hopper_update(struct MainObj* self)
{
    data_hopper_state_funcs[self->state](self);
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_41_data_hopper", data_hopper_init);
#else
void data_hopper_init(struct MainObj* self)
{
    s8 mode = 2;

    self->state = 1;
    if (0 != self->unk2) {
        mode = 6;
    }
    self->unk5 = mode;
    self->hp = 3;
    self->contact_damage = 3;
    self->animation_table = (const u8* const*)data_hopper_animations;
    self->attack_box = &data_hopper_attack_box;
    self->terrain_box = &data_hopper_terrain_box;
    self->collision_data = D_801060F0;
    self->unk16 = VISUAL_SATURN_LAYER(5);
    self->unk6 = 0;
    self->unk7C = 0;
    self->bg_offset = 0;
    self->invincibility_timer = 0;
    self->hurt_box = NULL;
    self->air_state = 0;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->ext.main_41.unk84 = 0;
    self->ext.main_41.unk83 = 0;
    self->ext.main_41.unk82 = 0;
    self->unk7E = 0xF0;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
}
#endif

void data_hopper_spawn_item(struct MainObj* self)
{
    struct ItemObj* item;

    item = find_free_item_obj();
    if (item != NULL) {
        item->active = self->active;
        item->id = 0x13;
        item->unk2 = -0x80;
        item->animation_table = self->animation_table;
        item->sprite_frames = self->sprite_frames;
        item->unk40 = self->unk40;
        item->unk42 = self->unk42;
        item->x_pos = self->x_pos;
        item->y_pos = self->y_pos;
        item->unk15 = self->unk15;
        item->ext.owner = self;
    }
}

void data_hopper_stand(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->ext.main_41.unk84 = 0;
        self->ext.main_41.unk83 = 1;
        set_animation(self, self->ext.main_41.unk82 + 5);
    }
    if (!(self->collision_flags & 8)) {
        self->unk5 = 3;
        self->unk6 = 0;
        return;
    }
    animate_object(self);
}

void data_hopper_fall(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->ext.main_41.unk84 = 1;
        self->ext.main_41.unk83 = 0;
        self->x_speed = 0;
        self->x_accel = 0;
        self->y_speed = 0;
        self->gravity = FIXED(0.2578125);
        set_animation(self, 4);
    }
    if (self->collision_flags & 8) {
        self->unk5 = 4;
        self->unk6 = 0;
    } else {
        animate_object(self);
        move_with_gravity(ANIMATED_OBJECT(self));
    }
}

// data_hopper_pick_direction

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void data_hopper_spawn_item(struct MainObj*);
ret_s8 func_8002DD04(struct MainObj* object);
#endif

extern void (*data_hopper_step_funcs[8])();
extern struct Unk_unk68 data_hopper_hurt_box;
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80062778(struct MainObj* self);
void func_80062BBC(struct MainObj* self);
void func_80062650(struct MainObj* self);
void func_80062AEC(struct MainObj*);
void collide_with_players(struct PlayerObj*);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_41_data_hopper", func_80062650);
#else
void func_80062650(struct MainObj* self)
{
    switch (func_8002D724(PLAYER_OBJECT(self), self->x_pos.i.hi,
        self->y_pos.i.hi + self->terrain_box->unk1 + self->terrain_box->unk3)) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 9:
    case 10:
        self->ext.main_41.unk80 = 2;
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 11:
    case 12:
        self->ext.main_41.unk80 = 1;
        break;
    case 16:
        break;
    default:
        self->ext.main_41.unk80 = 0;
        break;
    }
}
#endif

void data_hopper_land(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->unk7C = 1;
        self->ext.main_41.unk84 = 0;
        self->ext.main_41.unk83 = 1;
    }
    if (self->animation_step.fields.relative_step == 0) {
        func_80062650(self);
        if (self->ext.main_41.unk80 == 0) {
            self->unk5 = 2;
        } else {
            self->unk5 = 5;
        }
        self->unk6 = 0;
        return;
    }
    animate_object(self);
}

// data_hopper_hop
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80062778(struct MainObj* self)
{
    struct Main41Ext* ext = &self->ext.main_41;
    u8 flags;
    u8 direction;

    if (self->unk6 == 0) {
        self->unk6 = 1;
        ext->unk84 = 1;
        ext->unk83 = 0;
        self->x_speed = 0;
        self->y_speed = 0;
        self->gravity = 0;
        self->x_accel = 0x2000;
        self->unk15 = (ext->unk80 & 1) ? PLAYER_FACING_RIGHT : 0;
        set_animation(self, 0);
        data_hopper_spawn_item(self);
        ext->unk81 = ext->unk80;
    }
    func_80062650(self);
    flags = self->collision_flags;
    if (!(flags & 8)) {
        self->unk5 = 3;
        self->unk6 = 0;
        return;
    }
    direction = self->unk15 ? 1 : 2;
    if (((flags & 3) && (flags & direction)) || ext->unk80 == (self->unk15 ? 2 : 1)) {
        self->unk5 = 2;
        self->unk6 = 0;
        ext->unk82 = self->animation_step.fields.event;
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
    if (self->x_speed > 0x41FFF || self->x_speed < -0x41FFF) {
        if (ext->unk80 == 1)
            self->x_speed = 0x42000;
        else if (ext->unk80 == 2)
            self->x_speed = -0x42000;
        self->x_accel = 0;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
    ext->unk81 = ext->unk80;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_41_data_hopper", func_80062778);
#endif

void data_hopper_blink(struct MainObj* self)
{
    s16 timer;

    switch (self->unk6) {
    case 0:
        self->unk6 = 1;
        self->ext.main_41.unk84 = 0;
        self->ext.main_41.unk83 = 0;
        self->unk7C = 0;
        set_animation(self, 2);
        break;
    case 1:
        if (self->animation_step.fields.relative_step < 0) {
            self->unk6 = 2;
            set_animation(self, 3);
            return;
        }
        animate_object(ANIMATED_OBJECT(self));
        break;
    case 2:
        timer = self->unk7C;
        if (timer >= 6) {
            self->unk5 = 2;
            self->unk6 = 0;
            if (self->on_screen != 0) {
                func_8001540C(2, SATURN_SOUND(0xEB, 0xAC), self);
            }
            return;
        }
        if (self->animation_step.fields.relative_step < 0) {
            self->unk7C = timer + 1;
        }
        animate_object(ANIMATED_OBJECT(self));
        break;
    }
}

void data_hopper_vanish(struct MainObj* self)
{
    s16 animation_count;
    s8 state;

    state = self->unk6;
    switch (state) {
    case 0:
        self->unk6 = 1;
        self->ext.main_41.unk84 = 0;
        self->ext.main_41.unk83 = 0;
        self->unk7C = 0;
        set_animation(self, 0xB);
        return;
    case 1:
        animation_count = self->unk7C;
        if (animation_count >= 6) {
            self->unk6 = 2;
            set_animation(self, 0xC);
            return;
        }
        if (self->animation_step.fields.relative_step < 0) {
            self->unk7C = animation_count + 1;
        }
        break;
    case 2:
        if (self->animation_step.fields.relative_step < 0) {
            self->state = 2;
            self->unk5 = 0;
            self->unk6 = 0;
            return;
        }
        break;
    default:
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
}

// data_hopper_check_player
void func_80062AEC(struct MainObj* self)
{
    struct ItemObj* item;

    for (item = item_objects; item < item_objects + COUNT(item_objects); item++) {
        if ((item->active != 0) && (item->id == 0x13) && ((u8)(item->unk2 - 1) < 3)) {
            if (func_8002C160(self, item) != 0) {
                self->unk5 = 7;
                self->unk6 = 0;
                item->unk7C.item_19.open_requested = 1;
                return;
            }
        }
    }
}

// data_hopper_main
void func_80062BBC(struct MainObj* self)
{
    s32 status;

    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    self->on_screen = 0;
    if (self->unk5 != 7)
        func_80062AEC(self);
    ((void (*)(struct MainObj*))data_hopper_step_funcs[self->unk5])(self);
    CollisionRelated(PLAYER_OBJECT(self));
    if (self->ext.main_41.unk84 != 0) {
        func_8002D9BC(self);
        status = func_8002DD04(self);
    } else {
        status = 0;
    }
    if (self->ext.main_41.unk83 != 0) {
        self->unk76 = -1;
        self->unk75 = 1;
        collide_with_players(PLAYER_OBJECT(self));
    } else {
        self->unk76 = 0;
        self->unk75 = 0;
    }
    if (status < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(4, &data_hopper_hurt_box, self);
        self->state = 2;
        return;
    }
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
        self->unk7E = 0xF0;
    } else if (self->unk2 != 0) {
        if (self->unk7E == 0)
            self->state = 2;
        else
            self->unk7E--;
    }
}

void data_hopper_idle(struct MainObj* self)
{
}

void data_hopper_despawn(struct MainObj* self)
{
    if (self->unk2 == 0) {
        despawn_object(OBJECT_HEADER(self));
    } else {
        ZeroObjectState(OBJECT_HEADER(self));
    }
}

union AnimationStep data_hopper_anim_0[] = {
    { 5, 0, 1, 0x00 },
    { 5, 1, 1, 0x01 },
    { 5, 2, 1, 0x02 },
    { 5, 3, 1, 0x03 },
    { 5, 4, 1, 0x04 },
    { 5, 5, -5, 0x05 },
};

union AnimationStep data_hopper_anim_1[] = {
    { 2, 0, 1, 0x62 },
    { 2, 0, 1, 0x06 },
    { 2, 0, 1, 0x07 },
    { 2, 0, 1, 0x08 },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x0A },
    { 2, 0, -5, 0x0B },
};

union AnimationStep data_hopper_anim_2[] = {
    { 1, 0, 1, 0x0F },
    { 1, 0, 1, 0x3B },
    { 1, 0, 1, 0x0F },
    { 1, 0, 1, 0x3B },
    { 1, 0, 1, 0x0F },
    { 1, 0, 1, 0x3B },
    { 1, 0, 1, 0x10 },
    { 1, 0, 1, 0x3B },
    { 1, 0, 1, 0x11 },
    { 1, 0, 1, 0x3B },
    { 1, 0, 1, 0x12 },
    { 1, 0, 1, 0x3B },
    { 1, 0, 1, 0x13 },
    { 1, 0, 1, 0x3B },
    { 1, 0, 1, 0x14 },
    { 1, 0, 1, 0x3B },
    { 1, 0, 1, 0x15 },
    { 1, 0, -17, 0x3B },
};

union AnimationStep data_hopper_anim_3[] = {
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x17 },
    { 1, 0, -2, 0x18 },
};

union AnimationStep data_hopper_anim_4[] = {
    { 4, 0, 1, 0x00 },
    { 5, 0, 1, 0x0C },
    { 6, 0, 1, 0x0D },
    { 7, 0, 1, 0x0E },
    { 6, 0, 1, 0x0D },
    { 5, 0, 1, 0x0C },
    { 4, 0, 1, 0x1C },
    { 1, 0, 0, 0x1D },
};

union AnimationStep data_hopper_anim_5[] = {
    { 5, 0, 1, 0x19 },
    { 6, 0, 1, 0x1A },
    { 7, 0, 1, 0x1B },
    { 8, 0, 1, 0x1C },
    { 9, 0, 0, 0x1D },
};

union AnimationStep data_hopper_anim_6[] = {
    { 5, 0, 1, 0x1E },
    { 6, 0, 1, 0x1F },
    { 7, 0, 1, 0x20 },
    { 8, 0, 1, 0x21 },
    { 9, 0, 0, 0x22 },
};

union AnimationStep data_hopper_anim_7[] = {
    { 5, 0, 1, 0x23 },
    { 6, 0, 1, 0x24 },
    { 7, 0, 1, 0x25 },
    { 8, 0, 1, 0x26 },
    { 9, 0, 0, 0x27 },
};

union AnimationStep data_hopper_anim_8[] = {
    { 5, 0, 1, 0x28 },
    { 6, 0, 1, 0x29 },
    { 7, 0, 1, 0x2A },
    { 8, 0, 1, 0x2B },
    { 9, 0, 0, 0x2C },
};

union AnimationStep data_hopper_anim_9[] = {
    { 5, 0, 1, 0x2D },
    { 6, 0, 1, 0x2E },
    { 7, 0, 1, 0x2F },
    { 8, 0, 1, 0x30 },
    { 9, 0, 0, 0x31 },
};

union AnimationStep data_hopper_anim_10[] = {
    { 5, 0, 1, 0x32 },
    { 6, 0, 1, 0x33 },
    { 7, 0, 1, 0x34 },
    { 8, 0, 1, 0x35 },
    { 9, 0, 0, 0x36 },
};

union AnimationStep data_hopper_anim_11[] = {
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x3C },
    { 1, 0, -2, 0x3D },
};

union AnimationStep data_hopper_anim_12[] = {
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x3B },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x3B },
    { 1, 0, 1, 0x14 },
    { 1, 0, 1, 0x3B },
    { 1, 0, 1, 0x13 },
    { 1, 0, 1, 0x3B },
    { 1, 0, 1, 0x12 },
    { 1, 0, 1, 0x3B },
    { 1, 0, 1, 0x11 },
    { 1, 0, 1, 0x3B },
    { 1, 0, 1, 0x10 },
    { 1, 0, 1, 0x3B },
    { 1, 0, 1, 0x0F },
    { 1, 0, 1, 0x3B },
    { 1, 0, 1, 0x0F },
    { 1, 0, -17, 0x3B },
};

union AnimationStep data_hopper_anim_13[] = {
    { 1, 0, 0, 0x1D },
};

union AnimationStep data_hopper_anim_14[] = {
    { 1, 0, 1, 0x4A },
    { 1, 0, 1, 0x4B },
    { 1, 0, 1, 0x4A },
    { 1, 0, 1, 0x4B },
    { 1, 0, 1, 0x4A },
    { 1, 0, 1, 0x4C },
    { 1, 0, 1, 0x4A },
    { 1, 0, 1, 0x4C },
    { 1, 0, 1, 0x4D },
    { 1, 0, 1, 0x4C },
    { 1, 0, 1, 0x4D },
    { 1, 0, 1, 0x4C },
    { 1, 0, 1, 0x4E },
    { 1, 0, 1, 0x4C },
    { 1, 0, 1, 0x4E },
    { 1, 0, 1, 0x4F },
    { 1, 0, 1, 0x4E },
    { 1, 0, 1, 0x4F },
    { 1, 0, 1, 0x4E },
    { 1, 0, 1, 0x50 },
    { 1, 0, 1, 0x4E },
    { 1, 0, 1, 0x50 },
    { 1, 0, 1, 0x51 },
    { 1, 0, 1, 0x50 },
    { 1, 0, 1, 0x51 },
    { 1, 0, 1, 0x50 },
    { 1, 0, 1, 0x52 },
    { 1, 0, 1, 0x50 },
    { 1, 0, 1, 0x52 },
    { 1, 0, 1, 0x53 },
    { 1, 0, 1, 0x52 },
    { 1, 0, 1, 0x53 },
    { 1, 0, 1, 0x52 },
    { 1, 0, 1, 0x54 },
    { 1, 0, 1, 0x52 },
    { 1, 0, 1, 0x54 },
    { 1, 0, 1, 0x55 },
    { 1, 0, 1, 0x54 },
    { 1, 0, 1, 0x55 },
    { 1, 0, 1, 0x54 },
    { 1, 0, 1, 0x56 },
    { 1, 0, 1, 0x54 },
    { 1, 0, 1, 0x56 },
    { 1, 0, 1, 0x57 },
    { 1, 0, 1, 0x56 },
    { 1, 0, 1, 0x57 },
    { 1, 0, 1, 0x56 },
    { 1, 0, 1, 0x58 },
    { 1, 0, 1, 0x56 },
    { 1, 0, 1, 0x58 },
    { 1, 0, 1, 0x59 },
    { 1, 0, 1, 0x58 },
    { 1, 0, 1, 0x59 },
    { 1, 0, 1, 0x58 },
    { 1, 0, 1, 0x5A },
    { 1, 0, 1, 0x58 },
    { 1, 0, 1, 0x5A },
    { 1, 0, 1, 0x5B },
    { 1, 0, 1, 0x5A },
    { 1, 0, 1, 0x5B },
    { 1, 0, 1, 0x5A },
    { 1, 0, 1, 0x5C },
    { 1, 0, 1, 0x5A },
    { 1, 0, 1, 0x5C },
    { 1, 0, 1, 0x5D },
    { 1, 0, 1, 0x5C },
    { 1, 0, 1, 0x5D },
    { 1, 0, 1, 0x5C },
    { 1, 0, 1, 0x5E },
    { 1, 0, 1, 0x5C },
    { 1, 0, 1, 0x5E },
    { 1, 0, 1, 0x5F },
    { 1, 0, 1, 0x5E },
    { 1, 0, 1, 0x5F },
    { 1, 0, 1, 0x5E },
    { 1, 0, 1, 0x60 },
    { 1, 0, 1, 0x5E },
    { 1, 0, 1, 0x60 },
    { 1, 0, 1, 0x61 },
    { 1, 0, 1, 0x60 },
    { 1, 0, 1, 0x61 },
    { 1, 0, 1, 0x60 },
    { 1, 0, 1, 0x3B },
    { 1, 0, 1, 0x60 },
    { 1, 0, 0, 0x3B },
};

union AnimationStep data_hopper_anim_16[] = {
    { 1, 0, 1, 0x37 },
    { 1, 0, 1, 0x38 },
    { 1, 0, 1, 0x39 },
    { 1, 0, 1, 0x3A },
    { 1, 0, 1, 0x39 },
    { 1, 0, 1, 0x38 },
    { 1, 0, 0, 0x37 },
};

union AnimationStep data_hopper_anim_18[] = {
    { 1, 0, 1, 0x3E },
    { 1, 0, 1, 0x3F },
    { 1, 0, 1, 0x40 },
    { 1, 0, 1, 0x41 },
    { 1, 0, 1, 0x40 },
    { 1, 0, 1, 0x3F },
    { 1, 0, 0, 0x3E },
};

union AnimationStep data_hopper_anim_15[] = {
    { 1, 0, 1, 0x42 },
    { 1, 0, 1, 0x43 },
    { 1, 0, 1, 0x44 },
    { 1, 0, 1, 0x45 },
    { 1, 0, 1, 0x44 },
    { 1, 0, 1, 0x43 },
    { 1, 0, 0, 0x42 },
};

union AnimationStep data_hopper_anim_17[] = {
    { 1, 0, 1, 0x46 },
    { 1, 0, 1, 0x47 },
    { 1, 0, 1, 0x48 },
    { 1, 0, 1, 0x49 },
    { 1, 0, 1, 0x48 },
    { 1, 0, 1, 0x47 },
    { 1, 0, 0, 0x46 },
};

union AnimationStep* data_hopper_animations[19] = {
    data_hopper_anim_0,
    data_hopper_anim_1,
    data_hopper_anim_2,
    data_hopper_anim_3,
    data_hopper_anim_4,
    data_hopper_anim_5,
    data_hopper_anim_6,
    data_hopper_anim_7,
    data_hopper_anim_8,
    data_hopper_anim_9,
    data_hopper_anim_10,
    data_hopper_anim_11,
    data_hopper_anim_12,
    data_hopper_anim_13,
    data_hopper_anim_14,
    data_hopper_anim_15,
    data_hopper_anim_16,
    data_hopper_anim_17,
    data_hopper_anim_18,
};

struct Unk_unk68 data_hopper_hurt_box = { 14, 15, 16, 17 };

struct Unk_unk68 data_hopper_terrain_box = { 0, 0, 25, 23 };

struct Unk_unk68 data_hopper_attack_box = { -23, -24, 45, 49 };

void (*data_hopper_state_funcs[])(struct MainObj*) = {
    data_hopper_init,
    func_80062BBC,
    data_hopper_despawn,
};

void (*data_hopper_step_funcs[8])() = {
    enemy_hit_reaction,
    data_hopper_idle,
    data_hopper_stand,
    data_hopper_fall,
    data_hopper_land,
    func_80062778,
    data_hopper_blink,
    data_hopper_vanish,
};
