// MainObj, main_object_update_funcs[11]
// 8004A718..8004B8C0
#include "common.h"
#include "func_tables.h"

void wall_crawler_update(struct MainObj* self)
{
    wall_crawler_state_funcs[self->state](self);
    if ((self->unk2 == 0) || (engine_obj.character_state.fields.active == 1)) {
        CollisionRelated(PLAYER_OBJECT(self));
    }
}

// wall_crawler_init
INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004A78C);

// wall_crawler_attach
INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004A9F4);

// wall_crawler_main
INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004AB6C);

void wall_crawler_next_state(struct MainObj* self)
{
    self->state++;
}

void wall_crawler_despawn(struct MainObj* self)
{
    self->state = 0;
    self->unk5 = 0;
    self->unk6 = 0;
    despawn_object(OBJECT_HEADER(self));
}

// wall_crawler_step_7
INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004AD18);

void wall_crawler_resume_step(struct MainObj* self)
{
    self->unk5 = SP_CUR_MAIN_OBJ->ext.main_11.saved_unk5;
}

void wall_crawler_drop(struct MainObj* self)
{
    move_object((struct MovingObj*)self);
}

// wall_crawler_crawl
INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004AE20);

void wall_crawler_turn(struct MainObj* self)
{
    if (self->animation_step.fields.event == 1) {
        self->unk15 ^= 0x40;
        set_animation(self, 0);
        if (self->unk2 == 0) {
            self->unk5 = 2;
        } else {
            self->unk5 = 4;
        }
    }
}

// wall_crawler_step_4
INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B0A0);

void wall_crawler_corner(struct MainObj* self)
{
    wall_crawler_corner_funcs[self->unk6](self);
}

// wall_crawler_corner_0
INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B2BC);

// wall_crawler_corner_1
INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B418);

// wall_crawler_corner_2
INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B514);

// wall_crawler_corner_3
INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B668);

void wall_crawler_corner_end(struct MainObj* self)
{
    u8 flags;

    if (self->unk2 == 0) {
        flags = SP_CUR_MAIN_OBJ->ext.main_11.unk80;
        if (flags & 3) {
            if (flags & 2) {
                self->unk15 = 0x40;
            } else {
                self->unk15 = 0;
            }
            set_animation(self, 0);
        } else {
            set_animation(self, 1);
        }
        self->unk5 = 2;
    } else {
        set_animation(self, 1);
        SP_CUR_MAIN_OBJ->ext.main_11.unk80 = 4;
        self->y_speed = FIXED(3);
        self->x_speed = 0;
        self->unk5 = 6;
    }
    self->unk6 = 0;
}

void wall_crawler_update_surface(struct MainObj* self)
{
    struct MainObj* current;
    u8 flags;

    current = SP_CUR_MAIN_OBJ;
    if (current->ext.main_11.unk80 & 3) {
        flags = self->collision_flags;
        if (flags & 4) {
            if (flags & 8) {
                if (flags & 2) {
                    if (!(flags & 1)) {
                        current->ext.main_11.unk80 = 2;
                    }
                } else {
                    current->ext.main_11.unk80 = 1;
                }
            } else {
                current->ext.main_11.unk80 = 8;
            }
        } else {
            current->ext.main_11.unk80 = 4;
        }
    } else {
        flags = self->collision_flags;
        if (flags & 2) {
            if (flags & 1) {
                if (flags & 4) {
                    if (!(flags & 8)) {
                        current->ext.main_11.unk80 = 8;
                    }
                } else {
                    current->ext.main_11.unk80 = 4;
                }
            } else {
                current->ext.main_11.unk80 = 2;
            }
        } else {
            current->ext.main_11.unk80 = 1;
        }
    }
}

union AnimationStep wall_crawler_anim_0[] = {
    { 0x00010001 },
    { 0x01010002 },
    { 0x2F010003 },
    { 0x01010002 },
    { 0x00010001 },
    { 0x30010002 },
    { 0x31010003 },
    { 0x30010002 },
    { 0x00F80001 },
};

union AnimationStep wall_crawler_anim_1[] = {
    { 0x02010001 },
    { 0x03FF0001 },
};

union AnimationStep wall_crawler_anim_2[] = {
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x06010001 },
    { 0x07010001 },
    { 0x06010001 },
    { 0x07010001 },
    { 0x06010001 },
    { 0x07010001 },
    { 0x06010001 },
    { 0x07010001 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x08010001 },
    { 0x09010101 },
    { 0x02000001 },
};

union AnimationStep wall_crawler_anim_3[] = {
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x0A010101 },
    { 0x0BFF0101 },
};

union AnimationStep wall_crawler_anim_4[] = {
    { 0x0B010001 },
    { 0x0A010001 },
    { 0x0B010001 },
    { 0x0A010001 },
    { 0x0B010001 },
    { 0x0A010001 },
    { 0x0B010001 },
    { 0x0A010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x03010101 },
    { 0x02FF0101 },
};

union AnimationStep wall_crawler_anim_5[] = {
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0E010101 },
    { 0x0FFF0101 },
};

union AnimationStep wall_crawler_anim_6[] = {
    { 0x0F010001 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x0E010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x03010101 },
    { 0x02FF0101 },
};

union AnimationStep wall_crawler_anim_7[] = {
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x04010101 },
    { 0x05FF0101 },
};

union AnimationStep wall_crawler_anim_8[] = {
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x03010101 },
    { 0x02FF0101 },
};

union AnimationStep wall_crawler_anim_9[] = {
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x0C010101 },
    { 0x0DFF0101 },
};

union AnimationStep wall_crawler_anim_10[] = {
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x03010101 },
    { 0x02FF0101 },
};

union AnimationStep wall_crawler_anim_11[] = {
    { 0x10010001 },
    { 0x11010001 },
    { 0x12010001 },
    { 0x13FD0001 },
};

union AnimationStep wall_crawler_anim_12[] = {
    { 0x1F000001 },
};

union AnimationStep wall_crawler_anim_13[] = {
    { 0x20000001 },
};

union AnimationStep wall_crawler_anim_14[] = {
    { 0x21000001 },
};

union AnimationStep wall_crawler_anim_15[] = {
    { 0x22000001 },
};

union AnimationStep wall_crawler_anim_16[] = {
    { 0x23000001 },
};

union AnimationStep wall_crawler_anim_17[] = {
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x24010201 },
    { 0x25010001 },
    { 0x02010101 },
    { 0x03FF0101 },
};

union AnimationStep wall_crawler_anim_18[] = {
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x26010201 },
    { 0x27010001 },
    { 0x04010101 },
    { 0x05FF0101 },
};

union AnimationStep wall_crawler_anim_19[] = {
    { 0x0A010001 },
    { 0x0B010001 },
    { 0x0A010001 },
    { 0x0B010001 },
    { 0x0A010001 },
    { 0x0B010001 },
    { 0x28010201 },
    { 0x29010001 },
    { 0x0A010101 },
    { 0x0BFF0101 },
};

union AnimationStep wall_crawler_anim_20[] = {
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x2A010201 },
    { 0x2B010001 },
    { 0x0C010101 },
    { 0x0DFF0101 },
};

union AnimationStep wall_crawler_anim_21[] = {
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x2C010201 },
    { 0x2D010001 },
    { 0x0E010101 },
    { 0x0FFF0101 },
};

union AnimationStep wall_crawler_anim_22[] = {
    { 0x2E000001 },
};

union AnimationStep wall_crawler_anim_23[] = {
    { 0x34000001 },
};

union AnimationStep wall_crawler_anim_24[] = {
    { 0x32010001 },
    { 0x33000001 },
};

union AnimationStep* wall_crawler_animations[] = {
    wall_crawler_anim_0,
    wall_crawler_anim_1,
    wall_crawler_anim_2,
    wall_crawler_anim_3,
    wall_crawler_anim_4,
    wall_crawler_anim_5,
    wall_crawler_anim_6,
    wall_crawler_anim_7,
    wall_crawler_anim_8,
    wall_crawler_anim_9,
    wall_crawler_anim_10,
    wall_crawler_anim_11,
    wall_crawler_anim_12,
    wall_crawler_anim_13,
    wall_crawler_anim_14,
    wall_crawler_anim_15,
    wall_crawler_anim_16,
    wall_crawler_anim_17,
    wall_crawler_anim_18,
    wall_crawler_anim_19,
    wall_crawler_anim_20,
    wall_crawler_anim_21,
    wall_crawler_anim_22,
    wall_crawler_anim_23,
    wall_crawler_anim_24,
};

u8 wall_crawler_debris[] = {
    0x0C,
    0x0D,
    0x0E,
    0x0F,
    0x10,
    0x00,
    0x00,
    0x00,
};

void (*wall_crawler_state_funcs[])(struct MainObj*) = {
    func_8004A78C,
    func_8004A9F4,
    func_8004AB6C,
    wall_crawler_next_state,
    wall_crawler_despawn,
};

void (*wall_crawler_step_funcs[])() = {
    enemy_hit_reaction,
    wall_crawler_resume_step,
    func_8004AE20,
    wall_crawler_turn,
    func_8004B0A0,
    wall_crawler_corner,
    wall_crawler_drop,
    func_8004AD18,
};

void (*wall_crawler_corner_funcs[])() = {
    func_8004B2BC,
    func_8004B418,
    func_8004B514,
    func_8004B668,
    wall_crawler_corner_end,
};

struct Unk_unk68 wall_crawler_terrain_box = { -9, -9, 23, 18 };

struct Unk_unk68 D_800FB568 = { 0, 7, 13, 24 };

struct Unk_unk68 D_800FB56C = { 0, 0, 11, 11 };
