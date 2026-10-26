// MainObj, main_object_update_funcs[29]
// 8005A4CC..8005B3FC
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_29_pod_spawner.h"
#include "main/objects.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/collision_bounds.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/collision_bounds.h"
#endif

extern void (*pod_spawner_step_funcs[])(struct MainObj*);

void pod_spawner_main(struct MainObj*);

// pod_spawner_copy_state_funcs
void pod_spawner_copy_init(struct MainObj*);

// pod_spawner_step_funcs
void pod_spawner_idle(struct MainObj* arg0);

void pod_spawner_wait(struct MainObj* arg0);

extern void (*pod_spawner_state_funcs[])(struct MainObj*);
extern void (*pod_spawner_copy_state_funcs[])(struct MainObj*);

extern s16 D_800FD86C[12];
extern s16 D_800FD884[12];
u8 pod_spawner_player_quadrant(struct MainObj*);
void func_8005ABC0(struct WeaponObj*, s8);
extern union AnimationStep* pod_spawner_animations[16];
extern struct Unk_unk68 D_800FD830[1];
extern struct Unk_unk68 D_800FD834[1];
#if defined(MMX4_PC) || defined(MMX4_SATURN)
extern u8 D_800FD89C[16];
#endif

void pod_spawner_update(struct MainObj* self)
{
    if (self->unk2 >= 0) {
        pod_spawner_state_funcs[self->state](self);
    } else {
        pod_spawner_copy_state_funcs[self->state](self);
    }
}

// pod_spawner_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8005A538(struct MainObj* self);
void func_8005A758(struct MainObj* self);
void func_8005AA14(struct MainObj* self);
void func_8005AD00(struct MainObj* self);
void func_8005AF5C(struct MainObj* self);
void func_8005B24C(struct MainObj* self);
void func_8005B2C8(struct MainObj* self);
extern ret_u8 func_8002938C(s32);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_29_pod_spawner", func_8005A538);
#else
void func_8005A538(struct MainObj* self)
{
    struct MainObj* child;
    u32 i;

    self->unk5 = 2;
    self->hp = 8;
    self->state = 1;
    self->contact_damage = 3;
    self->unk6 = 0;
    self->unk7C = 0;
    self->on_screen = 1;
    self->invincibility_timer = 0;
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    SP_CUR_MAIN_OBJ->ext.main_29_controller.x = self->x_pos.u.hi;
    SP_CUR_MAIN_OBJ->ext.main_29_controller.y = self->y_pos.u.hi;
    self->animation_table = (const u8* const*)pod_spawner_animations;
    self->hurt_box = D_800FD834;
    self->attack_box = D_800FD830;
    self->collision_data = D_801060F0;
    self->terrain_box = NULL;
    self->air_state = 0;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->unk16 = VISUAL_SATURN_LAYER(7);
    SP_CUR_MAIN_OBJ->ext.main_29_controller.unk80 = 0;
    if (self->unk2 == 3) {
        SP_CUR_MAIN_OBJ->ext.main_29_controller.unk81 = 1;
    } else {
        SP_CUR_MAIN_OBJ->ext.main_29_controller.unk81 = 0;
    }
    SP_CUR_MAIN_OBJ->ext.main_29.slots.controller.target = NULL;
    SP_CUR_MAIN_OBJ->ext.main_29.slots.controller.record = NULL;
    child = find_free_main_obj();
    if (child != NULL) {
        child->active = self->active;
        child->id = self->id;
        child->unk2 = -0x80;
        SP_CUR_MAIN_OBJ->ext.main_29.slots.controller.target = (struct Main29Record*)child;
        child->ext.main_29.source = self;
        for (i = 0; i < 4; i++)
            child->ext.main_29.slots.children[i] = NULL;
    }
    set_animation(self, 0);
}
#endif

void pod_spawner_main(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    pod_spawner_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x68, 0x68) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x68, 0x68);
    } else {
        self->state = 2;
    }
}

void pod_spawner_idle(struct MainObj* self)
{
}

// pod_spawner_spawn
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_29_pod_spawner", func_8005A758);
#else
void func_8005A758(struct MainObj* self)
{
    u8 direction;
    u8 angle;
    s8 state;

    if ((WEAPON_FRAME_COUNTER & 3) == 0) {
        SP_CUR_MAIN_OBJ->ext.main_29_controller.unk80++;
        if (SP_CUR_MAIN_OBJ->ext.main_29_controller.unk80 >= 12)
            SP_CUR_MAIN_OBJ->ext.main_29_controller.unk80 = 0;
        SP_CUR_MAIN_OBJ->ext.main_29_controller.offset_x = D_800FD86C[SP_CUR_MAIN_OBJ->ext.main_29_controller.unk80];
        SP_CUR_MAIN_OBJ->ext.main_29_controller.offset_y = D_800FD884[SP_CUR_MAIN_OBJ->ext.main_29_controller.unk80];
        self->x_pos.i.hi = SP_CUR_MAIN_OBJ->ext.main_29_controller.x + SP_CUR_MAIN_OBJ->ext.main_29_controller.offset_x;
        self->y_pos.i.hi = SP_CUR_MAIN_OBJ->ext.main_29_controller.y + SP_CUR_MAIN_OBJ->ext.main_29_controller.offset_y;
    }

    if (SP_CUR_MAIN_OBJ->ext.main_29_controller.unk81 == 0
        && ABS(g_Player.x_pos.i.hi, self->x_pos.i.hi) < 0x81
        && ABS(g_Player.y_pos.i.hi, self->y_pos.i.hi) < 0x41) {
        state = self->unk2;
        if (state == 0) {
            ((void (*)(struct MainObj*, s32))func_8005ABC0)(self, pod_spawner_player_quadrant(self));
        } else {
            if (state == 1) {
                direction = pod_spawner_player_quadrant(self);
                if (direction >= 2) {
                    ((void (*)(struct MainObj*, s32))func_8005ABC0)(self, direction);
                } else {
                    angle = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
                    if (direction == 0) {
                        if (angle < 0x10)
                            ((void (*)(struct MainObj*, s32))func_8005ABC0)(self, 2);
                        else
                            ((void (*)(struct MainObj*, s32))func_8005ABC0)(self, 3);
                    } else if (angle < 5) {
                        ((void (*)(struct MainObj*, s32))func_8005ABC0)(self, 2);
                    } else {
                        ((void (*)(struct MainObj*, s32))func_8005ABC0)(self, 3);
                    }
                }
            }
            state = self->unk2;
            if (state == 2) {
                direction = pod_spawner_player_quadrant(self);
                if (direction < 2) {
                    ((void (*)(struct MainObj*, s32))func_8005ABC0)(self, direction);
                } else {
                    angle = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
                    if (direction == state) {
                        if (angle >= 8)
                            ((void (*)(struct MainObj*, s32))func_8005ABC0)(self, 0);
                        else
                            ((void (*)(struct MainObj*, s32))func_8005ABC0)(self, 1);
                    } else if (angle >= 0x18) {
                        ((void (*)(struct MainObj*, s32))func_8005ABC0)(self, 1);
                    } else {
                        ((void (*)(struct MainObj*, s32))func_8005ABC0)(self, 0);
                    }
                }
            }
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}
#endif

void pod_spawner_wait(struct MainObj* self)
{
}

// pod_spawner_step_4
void func_8005AA14(struct MainObj* self)
{
    switch (self->unk6) {
    case 0:
        set_animation(self, 1);
        self->unk6 = 1;
        break;
    case 1:
        if (self->animation_step.fields.relative_step == 0) {
            set_animation(self, 2);
            self->unk6 = 2;
        }
        break;
    case 2:
        if (self->animation_step.fields.relative_step == 0) {
            struct MainObj* controller = (struct MainObj*)SP_CUR_MAIN_OBJ->ext.main_29.slots.controller.target;
#ifdef MMX4_PC
            if (controller != NULL)
#endif
                controller->unk6 = 1;
            self->unk6 = 3;
        }
        break;
    case 4:
        if (self->unk7C == 0) {
            set_animation(self, 4);
            self->unk6 = 5;
        } else {
            self->unk7C--;
        }
        break;
    case 5:
        if (self->animation_step.fields.relative_step == 0)
            self->unk6 = 6;
        break;
    case 6:
        self->unk5 = 2;
        self->unk6 = 0;
        break;
    }
    animate_object(ANIMATED_OBJECT(self));
}

u8 pod_spawner_player_quadrant(struct MainObj* self)
{
    s32 state;

    state = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
    if ((u8)(state - 4) >= 24) {
        state = 1;
    }
    if ((u8)(state - 4) < 8) {
        state = 2;
    }
    if ((u8)(state - 12) < 8) {
        state = 0;
    }
    if ((u8)(state - 20) < 8) {
        state = 3;
    }
    return state;
}

// pod_spawner_find_slot
void func_8005ABC0(struct WeaponObj* self, s8 direction)
{
    struct ShotObj* shot;
    struct MainObj* controller;

    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = self->active;
        shot->id = 0x10;
        shot->unk2 = direction;
        shot->x_pos.val = self->x_pos.val;
        shot->y_pos.val = self->y_pos.val;
        shot->animation_table = self->animation_table;
        shot->unk38 = self->unk38;
        shot->unk3C = self->unk3C;
        shot->unk40 = self->unk40;
        shot->unk42 = self->unk42;
        shot->unk16 = VISUAL_SATURN_LAYER(7);
        shot->unk42 = self->unk42 & 0x7FFF;
        shot->unk16 = self->unk16;
        shot->unk7C = self;
        controller = SP_CUR_MAIN_OBJ;
        controller->ext.main_29_controller.unk81 = 1;
        controller->ext.main_29.slots.controller.record = (struct Main29Record*)shot;
        self->unk5 = 3;
    }
}

void pod_spawner_despawn(struct MainObj* self)
{
    struct Main29Record* record;
    struct Main29Record* target;

    target = SP_CUR_MAIN_OBJ->ext.main_29.slots.controller.target;
    record = SP_CUR_MAIN_OBJ->ext.main_29.slots.controller.record;
    if (record != NULL && record->unk0 != 0 && record->unk1 == 0x10) {
        record->unk4 = 2;
    }
#ifdef MMX4_PC
    if (target != NULL)
#endif
        target->unk4 = 2;
    despawn_object(OBJECT_HEADER(self));
}

// pod_spawner_state_3
void func_8005AD00(struct MainObj* self)
{
    struct Main29Record* record;
    struct ObjectHeader* target;

    switch (self->unk5) {
    case 0:
        target = (struct ObjectHeader*)SP_CUR_MAIN_OBJ->ext.main_29.slots.controller.target;
        record = SP_CUR_MAIN_OBJ->ext.main_29.slots.controller.record;
        if (record != NULL && record->unk0 != 0 && record->unk1 == 0x10) {
            record->unk4 = 2;
        }
#ifdef MMX4_PC
        if (target != NULL) {
#endif
            target->state = 3;
            target->unk5 = 0;
#ifdef MMX4_PC
        }
#endif
        self->unk5 = 1;
        self->unk7C = 0x3C;
        self->x_speed = 0;
        self->x_accel = 0;
        self->y_speed = -0x8000;
        self->gravity = 0;
        self->unk42 &= 0x7FFF;
        set_animation(self, 0);
        update_on_screen(BASE_OBJECT(self), 0x68, 0x68);
        break;
    case 1:
        if (--self->unk7C == 0) {
            target = (struct ObjectHeader*)SP_CUR_MAIN_OBJ->ext.main_29.slots.controller.target;
#ifdef MMX4_PC
            if (target != NULL)
#endif
                target->unk5 = 2;
            self->unk5 = 2;
        } else {
            move_with_gravity(ANIMATED_OBJECT(self));
        }
        self->on_screen = 0;
        if (WEAPON_FRAME_COUNTER & 3) {
            update_on_screen(BASE_OBJECT(self), 0x68, 0x68);
        }
        if (!(WEAPON_FRAME_COUNTER & 0xF)) {
            func_800AF878(BASE_OBJECT(self), 0, 8, 4);
        }
        break;
    case 2:
        drop_item(BASE_OBJECT(self), 0x13);
        despawn_object(OBJECT_HEADER(self));
        break;
    }
}

void pod_spawner_copy_init(struct MainObj* self)
{
    struct MainObj* source = self->ext.main_29.source;

    self->state = 1;
    self->unk5 = 2;
    self->unk6 = 0;
    self->on_screen = 1;
    self->x_pos.val = source->x_pos.val;
    self->y_pos.val = source->y_pos.val;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    self->animation_table = source->animation_table;
    __builtin_memcpy(&self->animation_speed, &source->animation_speed, sizeof(u32));
    self->sprite_frames = source->sprite_frames;
    self->unk40 = source->unk40;
    self->unk42 = source->unk42;
    self->unk16 = VISUAL_SATURN_LAYER(7);
    self->unk7C = 0;
    self->ext.main_29.unk94 = 0;
    set_animation(self, 5);
}

// pod_spawner_copy_main
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8005AF5C(struct MainObj* self)
{
    struct MainObj* source = self->ext.main_29.source;
    u8* source_ext = (u8*)&source->ext;

    self->x_pos = source->x_pos;
    self->y_pos = source->y_pos;
    self->unk42 = source->unk42;
    animate_object(ANIMATED_OBJECT(self));

    switch (self->unk6) {
    case 0:
        self->unk7C = 0;
        self->ext.main_29.unk96 = D_800FD89C[get_random() & 0xF];
        break;
    case 1: {
        u16 count = self->ext.main_29.unk96;
        u16* spawned = &self->ext.main_29.unk94;
        if (count != 0) {
            u32 i;
            for (i = 0; i < count; i++) {
                struct MainObj* slot = self->ext.main_29.slots.children[i];
                if (slot == NULL && self->unk7C == 0) {
                    struct MainObj* child = find_free_main_obj();
                    if (child != NULL) {
                        s32 index;
                        s32 column;
                        s32 row;
                        self->ext.main_29.slots.children[i] = child;
                        child->id = 0x1C;
                        child->state = 0;
                        child->unk5 = 0;
                        child->unk6 = 0;
                        child->active = self->active;
                        child->unk2 = ((u8*)source->ext.main_29.slots.controller.record)[2];
                        child->x_pos = self->x_pos;
                        child->y_pos = self->y_pos;
                        index = func_8002938C(child->id);
                        child->unk40 = OBJECT_STAGE_TEXTURE(index);
                        index = func_8002938C(child->id);
                        column = index * 4 + 0x18;
                        row = index + 6;
#ifdef MMX4_SATURN
                        child->unk42 = column;
#else
                        child->unk42 = (column - (column / 16) * 16) | (((row / 4 + 0x1E0) << 6) & 0xFFFF);
#endif
                        index = func_8002938C(child->id);
                        child->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
                        self->unk7C = 1;
                        child->ext.main_28.context = self;
                        child->ext.main_28.index = i;
                        (*spawned)++;
                    }
                }
                if (*spawned >= count) {
                    self->unk6 = 2;
                    break;
                }
            }
        }
        break;
    }
    case 2:
        self->unk6 = 3;
        source->unk6 = 4;
        source->unk7C = 0x1E;
        break;
    case 3:
        if (self->ext.main_29.unk94 == 0) {
            self->unk6 = 4;
            self->unk7C = 0x78;
            if (source->ext.main_29.slots.controller.record != NULL && source->ext.main_29.slots.controller.record->unk0 != 0) {
                source->ext.main_29.slots.controller.record->unk4 = 2;
                source_ext[1] |= 2;
            }
        }
        break;
    case 4:
        if (self->unk7C == 0) {
            self->unk6 = 0;
            source_ext[1] = 0;
        } else {
            self->unk7C--;
        }
        break;
    }
    update_on_screen(BASE_OBJECT(self), 0x68, 0x68);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_29_pod_spawner", func_8005AF5C);
#endif

// pod_spawner_copy_state_2
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_29_pod_spawner", func_8005B24C);
#else
void func_8005B24C(struct MainObj* self)
{
    u32 i;

    self->ext.main_29.unk94 = 0;
    for (i = 0; i < 4; i++) {
        struct MainObj* child = self->ext.main_29.slots.children[i];
        if (child != NULL) {
            if (child->active != 0 && child->id == 0x1C)
                child->state = 3;
            self->ext.main_29.slots.children[i] = NULL;
        }
    }
    ZeroObjectState(OBJECT_HEADER(self));
}
#endif

// pod_spawner_copy_state_3
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_29_pod_spawner", func_8005B2C8);
#else
void func_8005B2C8(struct MainObj* self)
{
    struct MainObj* source = self->ext.main_29.source;
    struct MainObj* child;
    u32 i;

    self->x_pos.val = source->x_pos.val;
    self->y_pos.val = source->y_pos.val;
    switch (self->unk5) {
    case 0:
        self->ext.main_29.unk94 = 0;
        for (i = 0; i < 4; i++) {
            child = self->ext.main_29.slots.children[i];
            if (child != NULL) {
                if (child->active != 0 && child->id == 0x1C) {
                    child->state = 3;
                }
                self->ext.main_29.slots.children[i] = NULL;
            }
        }
        self->unk5 = 1;
        self->unk42 &= 0x7FFF;
        animate_object(ANIMATED_OBJECT(self));
        update_on_screen(BASE_OBJECT(self), 0x68, 0x68);
        break;
    case 1:
        animate_object(ANIMATED_OBJECT(self));
        self->on_screen = 0;
        if (WEAPON_FRAME_COUNTER & 3) {
            update_on_screen(BASE_OBJECT(self), 0x68, 0x68);
        }
        break;
    case 2:
        ZeroObjectState((struct ObjectHeader*)self);
        break;
    }
}
#endif

union AnimationStep pod_spawner_anim_0[] = {
    { 1, 0, 0, 0x00 },
};

union AnimationStep pod_spawner_anim_1[] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x04 },
    { 2, 0, 1, 0x05 },
    { 2, 0, 1, 0x04 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 0, 0x00 },
};

union AnimationStep pod_spawner_anim_2[] = {
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x06 },
    { 3, 0, 1, 0x07 },
    { 3, 0, 1, 0x08 },
    { 3, 0, 0, 0x09 },
};

union AnimationStep pod_spawner_anim_4[] = {
    { 3, 0, 1, 0x08 },
    { 3, 0, 1, 0x07 },
    { 3, 0, 1, 0x06 },
    { 3, 0, 0, 0x00 },
};

union AnimationStep pod_spawner_anim_3[] = {
    { 1, 0, 1, 0x0A },
    { 1, 0, 1, 0x14 },
    { 1, 0, 1, 0x0B },
    { 1, 0, 1, 0x14 },
    { 1, 0, 1, 0x0C },
    { 1, 0, 1, 0x14 },
    { 1, 0, 1, 0x0D },
    { 1, 0, 0, 0x0E },
};

union AnimationStep pod_spawner_anim_5[] = {
    { 1, 0, 1, 0x0F },
    { 1, 0, 1, 0x0E },
    { 1, 0, 1, 0x10 },
    { 1, 0, 1, 0x0E },
    { 1, 0, 1, 0x13 },
    { 1, 0, 1, 0x0E },
    { 1, 0, 1, 0x10 },
    { 1, 0, 1, 0x0E },
    { 1, 0, 1, 0x11 },
    { 1, 0, 1, 0x0E },
    { 1, 0, 1, 0x10 },
    { 1, 0, 1, 0x0E },
    { 1, 0, 1, 0x12 },
    { 1, 0, 1, 0x0E },
    { 1, 0, 1, 0x10 },
    { 1, 0, -15, 0x0E },
};

union AnimationStep pod_spawner_anim_6[] = {
    { 2, 1, 1, 0x20 },
    { 2, 2, 1, 0x1F },
    { 2, 3, 1, 0x1E },
    { 2, 4, 1, 0x1D },
    { 2, 4, 1, 0x1C },
    { 2, 4, 0, 0x1B },
};

union AnimationStep pod_spawner_anim_7[] = {
    { 2, 0, 1, 0x15 },
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x18 },
    { 2, 0, 1, 0x19 },
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x1A },
    { 2, 0, -7, 0x18 },
};

union AnimationStep pod_spawner_anim_8[] = {
    { 2, 0, 1, 0x1B },
    { 2, 0, 1, 0x1C },
    { 2, 0, 1, 0x1D },
    { 2, 0, 1, 0x1E },
    { 2, 0, 1, 0x1F },
    { 2, 0, 0, 0x20 },
};

union AnimationStep pod_spawner_anim_9[] = {
    { 2, 5, 1, 0x2C },
    { 2, 6, 1, 0x2B },
    { 2, 7, 1, 0x2A },
    { 2, 8, 1, 0x29 },
    { 2, 8, 1, 0x28 },
    { 2, 8, 0, 0x27 },
};

union AnimationStep pod_spawner_anim_10[] = {
    { 2, 0, 1, 0x21 },
    { 2, 0, 1, 0x22 },
    { 2, 0, 1, 0x23 },
    { 2, 0, 1, 0x24 },
    { 2, 0, 1, 0x25 },
    { 2, 0, 1, 0x22 },
    { 2, 0, 1, 0x26 },
    { 2, 0, -7, 0x24 },
};

union AnimationStep pod_spawner_anim_11[] = {
    { 2, 0, 1, 0x27 },
    { 2, 0, 1, 0x28 },
    { 2, 0, 1, 0x29 },
    { 2, 0, 1, 0x2A },
    { 2, 0, 1, 0x2B },
    { 2, 0, 0, 0x2C },
};

union AnimationStep pod_spawner_anim_12[] = {
    { 2, 9, 1, 0x3A },
    { 2, 10, 1, 0x39 },
    { 2, 11, 1, 0x38 },
    { 2, 12, 1, 0x37 },
    { 2, 12, 1, 0x36 },
    { 2, 12, 0, 0x35 },
};

union AnimationStep pod_spawner_anim_13[] = {
    { 2, 0, 1, 0x2F },
    { 2, 0, 1, 0x30 },
    { 2, 0, 1, 0x31 },
    { 2, 0, 1, 0x32 },
    { 2, 0, 1, 0x33 },
    { 2, 0, 1, 0x30 },
    { 2, 0, 1, 0x34 },
    { 2, 0, -7, 0x31 },
};

union AnimationStep pod_spawner_anim_14[] = {
    { 1, 0, 0, 0x2D },
};

union AnimationStep pod_spawner_anim_15[] = {
    { 1, 0, 0, 0x2E },
};

union AnimationStep* pod_spawner_animations[] = {
    pod_spawner_anim_0,
    pod_spawner_anim_1,
    pod_spawner_anim_2,
    pod_spawner_anim_3,
    pod_spawner_anim_4,
    pod_spawner_anim_5,
    pod_spawner_anim_6,
    pod_spawner_anim_7,
    pod_spawner_anim_8,
    pod_spawner_anim_9,
    pod_spawner_anim_10,
    pod_spawner_anim_11,
    pod_spawner_anim_12,
    pod_spawner_anim_13,
    pod_spawner_anim_14,
    pod_spawner_anim_15,
};

u8 pod_spawner_debris[4] = { 0x0E, 0x0F, 0, 0 };

struct Unk_unk68 D_800FD830[] = {
    { -20, -18, 0x27, 0x24 },
};

struct Unk_unk68 D_800FD834[] = {
    { -13, -14, 0x1A, 0x1B },
};

void (*pod_spawner_state_funcs[])() = {
    func_8005A538,
    pod_spawner_main,
    pod_spawner_despawn,
    func_8005AD00,
};

void (*pod_spawner_copy_state_funcs[])(struct MainObj*) = {
    pod_spawner_copy_init,
    func_8005AF5C,
    func_8005B24C,
    func_8005B2C8,
};

void (*pod_spawner_step_funcs[])(struct MainObj*) = {
    enemy_hit_reaction,
    pod_spawner_idle,
    func_8005A758,
    pod_spawner_wait,
    func_8005AA14,
};

s16 D_800FD86C[] = {
    0x0001,
    0x0002,
    0x0003,
    0x0003,
    0x0002,
    0x0001,
    -1,
    -2,
    -3,
    -3,
    -2,
    -1,
};

s16 D_800FD884[] = {
    -3,
    -2,
    -1,
    0x0001,
    0x0002,
    0x0003,
    0x0003,
    0x0002,
    0x0001,
    -1,
    -2,
    -3,
};

u8 D_800FD89C[] = {
    0x01,
    0x01,
    0x01,
    0x01,
    0x02,
    0x02,
    0x02,
    0x02,
    0x01,
    0x01,
    0x01,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
};
