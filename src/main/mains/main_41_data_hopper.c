// MainObj, main_object_update_funcs[41]
// 800623C4..80062D60
#include "common.h"
#include "func_tables.h"

void data_hopper_update(struct MainObj* self)
{
    data_hopper_state_funcs[self->state](self);
}

void data_hopper_init(struct MainObj* self)
{
    s8 mode = 2;

    self->state = 1;
    if (self->unk2 != 0) {
        mode = 6;
    }
    self->unk5 = mode;
    self->hp = 3;
    self->contact_damage = 3;
    self->animation_table = (const u8* const*)data_hopper_animations;
    self->attack_box = &data_hopper_attack_box;
    self->terrain_box = &data_hopper_terrain_box;
    self->collision_data = D_801060F0;
    self->unk16 = 5;
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
INCLUDE_ASM("main/nonmatchings/mains/main_41_data_hopper", func_80062650);

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
INCLUDE_ASM("main/nonmatchings/mains/main_41_data_hopper", func_80062778);

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
                func_8001540C(2, 0xEB, self);
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
INCLUDE_ASM("main/nonmatchings/mains/main_41_data_hopper", func_80062AEC);

// data_hopper_main
INCLUDE_ASM("main/nonmatchings/mains/main_41_data_hopper", func_80062BBC);

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
    { 0x00010005 },
    { 0x01010105 },
    { 0x02010205 },
    { 0x03010305 },
    { 0x04010405 },
    { 0x05FB0505 },
};

union AnimationStep data_hopper_anim_1[] = {
    { 0x62010002 },
    { 0x06010002 },
    { 0x07010002 },
    { 0x08010002 },
    { 0x09010002 },
    { 0x0A010002 },
    { 0x0BFB0002 },
};

union AnimationStep data_hopper_anim_2[] = {
    { 0x0F010001 },
    { 0x3B010001 },
    { 0x0F010001 },
    { 0x3B010001 },
    { 0x0F010001 },
    { 0x3B010001 },
    { 0x10010001 },
    { 0x3B010001 },
    { 0x11010001 },
    { 0x3B010001 },
    { 0x12010001 },
    { 0x3B010001 },
    { 0x13010001 },
    { 0x3B010001 },
    { 0x14010001 },
    { 0x3B010001 },
    { 0x15010001 },
    { 0x3BEF0001 },
};

union AnimationStep data_hopper_anim_3[] = {
    { 0x16010001 },
    { 0x17010001 },
    { 0x18FE0001 },
};

union AnimationStep data_hopper_anim_4[] = {
    { 0x00010004 },
    { 0x0C010005 },
    { 0x0D010006 },
    { 0x0E010007 },
    { 0x0D010006 },
    { 0x0C010005 },
    { 0x1C010004 },
    { 0x1D000001 },
};

union AnimationStep data_hopper_anim_5[] = {
    { 0x19010005 },
    { 0x1A010006 },
    { 0x1B010007 },
    { 0x1C010008 },
    { 0x1D000009 },
};

union AnimationStep data_hopper_anim_6[] = {
    { 0x1E010005 },
    { 0x1F010006 },
    { 0x20010007 },
    { 0x21010008 },
    { 0x22000009 },
};

union AnimationStep data_hopper_anim_7[] = {
    { 0x23010005 },
    { 0x24010006 },
    { 0x25010007 },
    { 0x26010008 },
    { 0x27000009 },
};

union AnimationStep data_hopper_anim_8[] = {
    { 0x28010005 },
    { 0x29010006 },
    { 0x2A010007 },
    { 0x2B010008 },
    { 0x2C000009 },
};

union AnimationStep data_hopper_anim_9[] = {
    { 0x2D010005 },
    { 0x2E010006 },
    { 0x2F010007 },
    { 0x30010008 },
    { 0x31000009 },
};

union AnimationStep data_hopper_anim_10[] = {
    { 0x32010005 },
    { 0x33010006 },
    { 0x34010007 },
    { 0x35010008 },
    { 0x36000009 },
};

union AnimationStep data_hopper_anim_11[] = {
    { 0x16010001 },
    { 0x3C010001 },
    { 0x3DFE0001 },
};

union AnimationStep data_hopper_anim_12[] = {
    { 0x16010001 },
    { 0x3B010001 },
    { 0x15010001 },
    { 0x3B010001 },
    { 0x14010001 },
    { 0x3B010001 },
    { 0x13010001 },
    { 0x3B010001 },
    { 0x12010001 },
    { 0x3B010001 },
    { 0x11010001 },
    { 0x3B010001 },
    { 0x10010001 },
    { 0x3B010001 },
    { 0x0F010001 },
    { 0x3B010001 },
    { 0x0F010001 },
    { 0x3BEF0001 },
};

union AnimationStep data_hopper_anim_13[] = {
    { 0x1D000001 },
};

union AnimationStep data_hopper_anim_14[] = {
    { 0x4A010001 },
    { 0x4B010001 },
    { 0x4A010001 },
    { 0x4B010001 },
    { 0x4A010001 },
    { 0x4C010001 },
    { 0x4A010001 },
    { 0x4C010001 },
    { 0x4D010001 },
    { 0x4C010001 },
    { 0x4D010001 },
    { 0x4C010001 },
    { 0x4E010001 },
    { 0x4C010001 },
    { 0x4E010001 },
    { 0x4F010001 },
    { 0x4E010001 },
    { 0x4F010001 },
    { 0x4E010001 },
    { 0x50010001 },
    { 0x4E010001 },
    { 0x50010001 },
    { 0x51010001 },
    { 0x50010001 },
    { 0x51010001 },
    { 0x50010001 },
    { 0x52010001 },
    { 0x50010001 },
    { 0x52010001 },
    { 0x53010001 },
    { 0x52010001 },
    { 0x53010001 },
    { 0x52010001 },
    { 0x54010001 },
    { 0x52010001 },
    { 0x54010001 },
    { 0x55010001 },
    { 0x54010001 },
    { 0x55010001 },
    { 0x54010001 },
    { 0x56010001 },
    { 0x54010001 },
    { 0x56010001 },
    { 0x57010001 },
    { 0x56010001 },
    { 0x57010001 },
    { 0x56010001 },
    { 0x58010001 },
    { 0x56010001 },
    { 0x58010001 },
    { 0x59010001 },
    { 0x58010001 },
    { 0x59010001 },
    { 0x58010001 },
    { 0x5A010001 },
    { 0x58010001 },
    { 0x5A010001 },
    { 0x5B010001 },
    { 0x5A010001 },
    { 0x5B010001 },
    { 0x5A010001 },
    { 0x5C010001 },
    { 0x5A010001 },
    { 0x5C010001 },
    { 0x5D010001 },
    { 0x5C010001 },
    { 0x5D010001 },
    { 0x5C010001 },
    { 0x5E010001 },
    { 0x5C010001 },
    { 0x5E010001 },
    { 0x5F010001 },
    { 0x5E010001 },
    { 0x5F010001 },
    { 0x5E010001 },
    { 0x60010001 },
    { 0x5E010001 },
    { 0x60010001 },
    { 0x61010001 },
    { 0x60010001 },
    { 0x61010001 },
    { 0x60010001 },
    { 0x3B010001 },
    { 0x60010001 },
    { 0x3B000001 },
};

union AnimationStep data_hopper_anim_16[] = {
    { 0x37010001 },
    { 0x38010001 },
    { 0x39010001 },
    { 0x3A010001 },
    { 0x39010001 },
    { 0x38010001 },
    { 0x37000001 },
};

union AnimationStep data_hopper_anim_18[] = {
    { 0x3E010001 },
    { 0x3F010001 },
    { 0x40010001 },
    { 0x41010001 },
    { 0x40010001 },
    { 0x3F010001 },
    { 0x3E000001 },
};

union AnimationStep data_hopper_anim_15[] = {
    { 0x42010001 },
    { 0x43010001 },
    { 0x44010001 },
    { 0x45010001 },
    { 0x44010001 },
    { 0x43010001 },
    { 0x42000001 },
};

union AnimationStep data_hopper_anim_17[] = {
    { 0x46010001 },
    { 0x47010001 },
    { 0x48010001 },
    { 0x49010001 },
    { 0x48010001 },
    { 0x47010001 },
    { 0x46000001 },
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
