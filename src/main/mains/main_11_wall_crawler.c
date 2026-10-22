// MainObj, main_object_update_funcs[11]
// 8004A718..8004B8C0
#include "common.h"
#include "main/mains/main_11_wall_crawler.h"
#include "main/objects.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/object_motion.h"

#ifdef MMX4_PC
#include "main/1CF60.h"
#include "main/1E1BC.h"
#endif

// wall_crawler_state_funcs
extern void (*wall_crawler_state_funcs[])(struct MainObj*);

void wall_crawler_next_state(struct MainObj*);
void wall_crawler_despawn(struct MainObj*);

// wall_crawler_step_funcs
void wall_crawler_resume_step(struct MainObj* arg0);
void func_8004AE20(struct MainObj* arg0);

void wall_crawler_corner(struct MainObj* arg0);
void wall_crawler_drop(struct MainObj* arg0);

// wall_crawler_corner_funcs
void func_8004B2BC(struct MainObj*);

void func_8004B514(struct MainObj*);

void wall_crawler_corner_end(struct MainObj*);

extern void (*wall_crawler_corner_funcs[])(struct MainObj*);

void wall_crawler_update_surface(struct MainObj* self);

void wall_crawler_update(struct MainObj* self)
{
    wall_crawler_state_funcs[self->state](self);
    if ((self->unk2 == 0) || (engine_obj.character_state.fields.active == 1)) {
        CollisionRelated(PLAYER_OBJECT(self));
    }
}

// wall_crawler_init
#ifdef MMX4_PC
void func_8004B418(struct MainObj* self);
void func_8004B0A0(struct MainObj* self);
void func_8004A78C(struct MainObj* self);
void func_8004A9F4(struct MainObj* self);
void func_8004AD18(struct MainObj* self);
void func_8004B668(struct MainObj* self);
void func_8004AB6C(struct MainObj* self);
extern struct Unk_unk68 wall_crawler_terrain_box;
extern struct Unk_unk68 D_800FB568;
extern struct Unk_unk68 D_800FB56C;
extern struct Unk_unk68 D_801067F0[];
extern union AnimationStep* wall_crawler_animations[];
extern u8 wall_crawler_debris[];
extern void (*wall_crawler_step_funcs[])(struct MainObj*);
#endif

#ifdef MMX4_PC
void func_8004A78C(struct MainObj* self)
{
    u16 x;

    self->contact_damage = 3;
    self->invincibility_timer = 0;
    self->bg_offset = g_Player.bg_offset;
    self->animation_table = (const u8* const*)wall_crawler_animations;
    self->unk16 = 6;
    self->collision_data = D_801067F0;
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->attack_box = &wall_crawler_terrain_box;
    if (self->unk2 == 2) {
        self->hp = 5;
        set_animation(self, 0x17);
        self->terrain_box = &D_800FB568;
        self->unk5 = 7;
        self->unk6 = 0;
        self->hurt_box = NULL;
        self->state++;
        self->x_pos.u.hi = (self->x_pos.u.hi & -0x10) + 8;
        self->y_pos.u.hi = (self->y_pos.u.hi & -0x10) + 0x14;
        return;
    }

    self->hurt_box = &wall_crawler_terrain_box;
    if (g_Player.x_pos.val < self->x_pos.val) {
        self->unk15 = 0;
        SP_CUR_MAIN_OBJ->ext.main_11.unk80 = 1;
        self->x_speed = -0x18000;
    } else {
        self->unk15 = 0x40;
        SP_CUR_MAIN_OBJ->ext.main_11.unk80 = 2;
        self->x_speed = 0x18000;
    }
    move_object(MOVING_OBJECT(self));
    x = self->x_pos.u.hi;
    if (engine_obj.character_state.fields.active != 0 && ((u32)(x - 0xC0F) < 0x1E2 || (u32)(x - 0x100F) < 0x1E2 || (u32)(x - 0x1315) < 0x1DC || (u32)(x - 0x1613) < 0x1BF)) {
        set_animation(self, 0x16);
        self->state = 2;
        self->hp = 1;
        self->gravity = 0x8000;
        self->x_speed = 0;
        self->y_speed = 0;
        self->x_accel = 0;
        self->terrain_box = &D_800FB56C;
        return;
    }
    if (engine_obj.character_state.fields.active == 0) {
        self->hp = 5;
        set_animation(self, 0);
        self->terrain_box = &D_800FB568;
        self->state++;
    }
    self->unk5 = 2;
    self->unk6 = 0;
    *(u16*)((u8*)&SP_CUR_MAIN_OBJ->ext + 2) = self->unk2 == 0 ? 0x3C : 0xB4;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_11_wall_crawler", func_8004A78C);
#endif

// wall_crawler_attach
#ifdef MMX4_PC
void func_8004A9F4(struct MainObj* self)
{
    u16* timer = (u16*)((u8*)&SP_CUR_MAIN_OBJ->ext + 2);

    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    if (engine_obj.character_state.fields.active != 0) {
        set_animation(self, 0x16);
        self->hp = 1;
        self->gravity = 0x8000;
        self->x_speed = 0;
        self->y_speed = 0;
        self->x_accel = 0;
        self->terrain_box = &D_800FB56C;
        self->state++;
        return;
    }
    if (self->unk2 == 0 && self->unk5 == 2) {
        --*timer;
        if (*timer == 0)
            self->unk5 = 4;
    }
    SP_CUR_MAIN_OBJ->ext.main_11.saved_unk5 = self->unk5;
    if (func_8002DD04(self) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(5, wall_crawler_debris, self);
        drop_item(BASE_OBJECT(self), 7);
        self->state = 4;
        return;
    }
    wall_crawler_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    if (func_8002B160(BASE_OBJECT(self)) != 0) {
        self->state = 4;
    } else {
        animate_object(ANIMATED_OBJECT(self));
        is_on_screen(BASE_OBJECT(self));
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_11_wall_crawler", func_8004A9F4);
#endif

// wall_crawler_main
#ifdef MMX4_PC
void func_8004AB6C(struct MainObj* self)
{
    s32 collision;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    func_8002D9BC(self);
    SP_CUR_MAIN_OBJ->ext.main_11.saved_unk5 = self->unk5;
    collision = func_8002DD04(self);
    if (func_8002BB80(self, MAIN_OBJECT(&g_Player)) != 0)
        collision = -1;
    if (collision < 0) {
        spawn_explosion(BASE_OBJECT(self));
        SP_CUR_MAIN_OBJ->ext.main_11.unk86 = 0x10;
        for (s32 i = 0; i < 0x10; i++) {
            struct ShotObj* shot = find_free_shot_obj();
            if (shot == NULL)
                continue;
            shot->active = 0x41;
            shot->id = 0xA;
            shot->bg_offset = self->bg_offset;
            shot->x_pos = self->x_pos;
            shot->y_pos = self->y_pos;
            shot->unk2 = i * 2;
            set_velocity_from_angle(MOVING_OBJECT(shot), i * 2);
        }
        self->state++;
        return;
    }
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        animate_object(ANIMATED_OBJECT(self));
        is_on_screen(BASE_OBJECT(self));
    } else {
        self->state = 4;
    }
    if (!(self->collision_flags & 8))
        move_with_gravity(ANIMATED_OBJECT(self));
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_11_wall_crawler", func_8004AB6C);
#endif

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
#ifdef MMX4_PC
void func_8004AD18(struct MainObj* self)
{
    if (func_8002D724(PLAYER_OBJECT(self), self->x_pos.i.hi, self->y_pos.i.hi) != 0)
        return;
    set_animation(self, 0);
    if (g_Player.x_pos.val < self->x_pos.val) {
        self->unk15 = 0;
        SP_CUR_MAIN_OBJ->ext.main_11.unk80 = 1;
        self->x_speed = -0x18000;
    } else {
        self->unk15 = 0x40;
        SP_CUR_MAIN_OBJ->ext.main_11.unk80 = 2;
        self->x_speed = 0x18000;
    }
    move_object(MOVING_OBJECT(self));
    self->unk2 = 0;
    self->unk5 = 2;
    *(u16*)((u8*)&SP_CUR_MAIN_OBJ->ext + 2) = 0x3C;
    self->hurt_box = &wall_crawler_terrain_box;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_11_wall_crawler", func_8004AD18);
#endif

void wall_crawler_resume_step(struct MainObj* self)
{
    self->unk5 = SP_CUR_MAIN_OBJ->ext.main_11.saved_unk5;
}

void wall_crawler_drop(struct MainObj* self)
{
    move_object((struct MovingObj*)self);
}

// wall_crawler_crawl
void func_8004AE20(struct MainObj* self)
{
    struct MainObj** current = &SP_CUR_MAIN_OBJ;
    struct MainObj* owner;

    owner = *current;
    if (owner->ext.main_11.unk80 & 0x10) {
        wall_crawler_update_surface(self);
        switch ((*current)->ext.main_11.unk80) {
        case 1:
            self->x_speed = -0x18000;
            self->y_speed = 0;
            if (self->unk15 != 0) {
                self->unk5 = 3;
                set_animation(self, 2);
            } else {
                set_animation(self, 0);
            }
            break;
        case 2:
            self->x_speed = 0x18000;
            self->y_speed = 0;
            if (self->unk15 != 0x40) {
                self->unk5 = 3;
                set_animation(self, 2);
            } else {
                set_animation(self, 0);
            }
            break;
        case 4:
            self->x_speed = 0;
            self->y_speed = 0x18000;
            set_animation(self, 1);
            break;
        case 8:
            self->x_speed = 0;
            self->y_speed = -0x18000;
            set_animation(self, 1);
            break;
        }
    } else {
        if (self->unk2 == 0) {
            switch (owner->ext.main_11.unk80) {
            case 1:
                if (self->collision_flags & 2) {
                    owner->ext.main_11.unk80 |= 0x10;
                }
                break;
            case 2:
                if (self->collision_flags & 1) {
                    owner->ext.main_11.unk80 |= 0x10;
                }
                break;
            case 4:
                if (self->collision_flags & 4) {
                    owner->ext.main_11.unk80 |= 0x10;
                }
                break;
            case 8:
                if (self->collision_flags & 8) {
                    owner->ext.main_11.unk80 |= 0x10;
                }
                break;
            }
        } else {
            if (self->unk15 != 0) {
                if (self->x_pos.i.hi - g_Player.x_pos.i.hi >= 0x20) {
                    set_animation(self, 2);
                    self->unk5 = 3;
                }
            } else {
                if (g_Player.x_pos.i.hi - self->x_pos.i.hi >= 0x20) {
                    set_animation(self, 2);
                    self->unk5 = 3;
                }
            }
        }
    }
    move_object(MOVING_OBJECT(self));
}

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
#ifdef MMX4_PC
void func_8004B0A0(struct MainObj* self)
{
    u8* context = (u8*)&SP_CUR_MAIN_OBJ->ext;
    u16* timer = (u16*)(context + 2);

    if (self->unk2 == 0) {
        s32 dx = self->x_pos.i.hi - g_Player.x_pos.i.hi;
        s32 dy = self->y_pos.i.hi - g_Player.y_pos.i.hi;
        if (dx > -0x90 && dx < 0x90 && dy > -0x90 && dy < 0x90) {
            self->unk5 = 5;
            *timer = 0x78;
        } else {
            self->unk5 = 2;
            *timer = 0x3C;
        }
        return;
    }

    if (self->x_pos.i.hi < g_Player.x_pos.i.hi - 0x10 || self->x_pos.i.hi > g_Player.x_pos.i.hi + 0x10) {
        if (--*timer != 0) {
            s16 old_y = g_Player.y_pos.i.hi;
            g_Player.y_pos.i.hi = old_y - 0x30;
            context[4] = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
            g_Player.y_pos.i.hi = old_y;
            set_velocity_from_angle(MOVING_OBJECT(self), context[4]);
            move_object(MOVING_OBJECT(self));
            return;
        }
    }
    context[4] = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
    self->unk5 = 5;
    self->unk6 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_11_wall_crawler", func_8004B0A0);
#endif

void wall_crawler_corner(struct MainObj* self)
{
    wall_crawler_corner_funcs[self->unk6](self);
}

// wall_crawler_corner_0
void func_8004B2BC(struct MainObj* self)
{
    SP_CUR_MAIN_OBJ->ext.main_11.angle = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
    switch (SP_CUR_MAIN_OBJ->ext.main_11.angle & 0xFE) {
    case 2:
    case 4:
    case 6:
        self->unk15 = 0x40;
    case 10:
    case 12:
    case 14:
        if (SP_CUR_MAIN_OBJ->ext.main_11.angle >= 0xA) {
            self->unk15 = 0;
        }
        set_animation(self, 7);
        break;
    case 8:
        set_animation(self, 3);
        break;
    case 18:
    case 20:
    case 22:
        self->unk15 = 0;
    case 26:
    case 28:
    case 30:
        if (SP_CUR_MAIN_OBJ->ext.main_11.angle >= 0x1A) {
            self->unk15 = 0x40;
        }
        set_animation(self, 9);
        break;
    case 24:
        set_animation(self, 5);
        break;
    case 0:
        self->unk15 = 0x40;
        break;
    case 16:
        self->unk15 = 0;
        break;
    }
    SP_CUR_MAIN_OBJ->ext.main_11.unk86 = 0x14;
    SP_CUR_MAIN_OBJ->ext.main_11.unk85 = 0;
    self->unk6++;
}

// wall_crawler_corner_1
#ifdef MMX4_PC
void func_8004B418(struct MainObj* self)
{
    u8* context = (u8*)&SP_CUR_MAIN_OBJ->ext;
    u8 angle = context[4] & 0xFE;
    u8 animation = 0x11;
    switch (angle) {
    case 2:
    case 4:
    case 6:
    case 10:
    case 12:
    case 14:
        animation = 0x12;
        break;
    case 8:
        animation = 0x13;
        break;
    case 18:
    case 20:
    case 22:
    case 26:
    case 28:
    case 30:
        animation = 0x14;
        break;
    case 24:
        animation = 0x15;
        break;
    }
    if (animation != 0x11 && self->animation_step.fields.event != 1)
        return;
    set_animation(self, animation);
    context[5]++;
    self->unk6++;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_11_wall_crawler", func_8004B418);
#endif

// wall_crawler_corner_2
void func_8004B514(struct MainObj* self)
{
    struct ShotObj* shot;

    if (self->animation_step.fields.event == 1) {
        if ((s8)SP_CUR_MAIN_OBJ->ext.main_11.unk85 == 3) {
            SP_CUR_MAIN_OBJ->ext.main_11.unk86 = 0x20;
            self->unk6++;
        } else if ((s8)--SP_CUR_MAIN_OBJ->ext.main_11.unk86 <= 0) {
            SP_CUR_MAIN_OBJ->ext.main_11.unk86 = 0x20;
            self->unk6--;
        }
    }
    if (self->animation_step.fields.event != 2) {
        return;
    }
    shot = find_free_shot_obj();
    if (shot == NULL) {
        return;
    }
    shot->active = 0x41;
    shot->id = 6;
    shot->unk40 = self->unk40;
    shot->unk42 = self->unk42;
    shot->animation_table = (u32**)self->animation_table;
    shot->unk3C = (void*)self->sprite_frames;
    shot->unk15 = self->unk15;
    shot->bg_offset = self->bg_offset;
    shot->x_pos = self->x_pos;
    shot->y_pos = self->y_pos;
    shot->unk2 = SP_CUR_MAIN_OBJ->ext.main_11.angle;
    set_velocity_from_angle(MOVING_OBJECT(shot), SP_CUR_MAIN_OBJ->ext.main_11.angle);
}

// wall_crawler_corner_3
#ifdef MMX4_PC
void func_8004B668(struct MainObj* self)
{
    struct Main11Ext* ext = &SP_CUR_MAIN_OBJ->ext.main_11;
    u8 angle;
    s32 animation = -1;

    if ((s8)--ext->unk86 != 0)
        return;
    angle = ext->angle & 0xFE;
    switch (angle) {
    case 2:
    case 4:
    case 6:
    case 10:
    case 12:
    case 14:
        animation = 0x12;
        break;
    case 8:
        animation = 0x13;
        break;
    case 18:
    case 20:
    case 22:
    case 26:
    case 28:
    case 30:
        animation = 0x14;
        break;
    case 24:
        animation = 0x15;
        break;
    }
    if (animation >= 0)
        set_animation(self, animation);
    self->unk6++;
    ext->unk85 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_11_wall_crawler", func_8004B668);
#endif

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
        self->x_speed = 0;
        self->y_speed = FIXED(3);
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
