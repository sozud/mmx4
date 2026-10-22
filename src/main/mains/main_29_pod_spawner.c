// MainObj, main_object_update_funcs[29]
// 8005A4CC..8005B3FC
#include "common.h"
#include "main/mains/main_29_pod_spawner.h"
#include "main/objects.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/object_motion.h"

#ifdef MMX4_PC
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

#ifdef MMX4_PC
extern union AnimationStep* pod_spawner_animations[16];
extern struct Unk_unk68 D_800FD830[1];
extern struct Unk_unk68 D_800FD834[1];
extern s16 D_800FD86C[12];
extern s16 D_800FD884[12];
extern u8 D_800FD89C[16];
u8 pod_spawner_player_quadrant(struct MainObj*);
void func_8005ABC0(struct WeaponObj*, s8);
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
#ifdef MMX4_PC
void func_8005A538(struct MainObj* self);
void func_8005A758(struct MainObj* self);
void func_8005AA14(struct MainObj* self);
void func_8005AD00(struct MainObj* self);
void func_8005AF5C(struct MainObj* self);
void func_8005B24C(struct MainObj* self);
void func_8005B2C8(struct MainObj* self);
extern ret_u8 func_8002938C(s32);
#endif

#ifdef MMX4_PC
// src/main/mains/main_29_pod_spawner.c

void func_8005A538(struct MainObj* self)
{
    struct MainObj* controller = SP_CUR_MAIN_OBJ;
    struct MainObj* child;
    u8* context = (u8*)&controller->ext;

    self->unk5 = 2;
    self->hp = 8;
    self->contact_damage = 3;
    self->state = 1;
    self->unk6 = 0;
    self->unk7C = 0;
    self->on_screen = 1;
    self->invincibility_timer = 0;
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    *(u16*)(context + 2) = self->x_pos.u.hi;
    *(u16*)(context + 4) = self->y_pos.u.hi;
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
    self->unk16 = 7;
    context[0] = 0;
    context[1] = self->unk2 == 3;
    controller->ext.main_29.slots.controller.target = NULL;
    controller->ext.main_29.slots.controller.record = NULL;

    child = find_free_main_obj();
    if (child != NULL) {
        child->active = self->active;
        child->id = self->id;
        child->unk2 = -0x80;
        controller->ext.main_29.slots.controller.target = (struct Main29Record*)child;
        child->ext.main_29.source = self;
        __builtin_memset(child->ext.main_29.slots.children, 0, sizeof(child->ext.main_29.slots.children));
    }
    set_animation(self, 0);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_29_pod_spawner", func_8005A538);
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
#ifdef MMX4_PC
void func_8005A758(struct MainObj* self)
{
    u8* context = (u8*)&SP_CUR_MAIN_OBJ->ext;
    u8 direction;
    u8 result;
    s32 dx;
    s32 dy;

    if ((main_bss_state.frame_counter & 3) == 0) {
        context[0]++;
        if (context[0] >= 12)
            context[0] = 0;
        *(s16*)(context + 6) = D_800FD86C[context[0]];
        *(s16*)(context + 8) = D_800FD884[context[0]];
        self->x_pos.u.hi = *(u16*)(context + 2) + *(u16*)(context + 6);
        self->y_pos.u.hi = *(u16*)(context + 4) + *(u16*)(context + 8);
    }

    if (context[1] == 0) {
        dx = g_Player.x_pos.i.hi - self->x_pos.i.hi;
        dy = g_Player.y_pos.i.hi - self->y_pos.i.hi;
        if (dx > -0x81 && dx < 0x81 && dy > -0x41 && dy < 0x41) {
            direction = pod_spawner_player_quadrant(self);
            if (self->unk2 == 0) {
                func_8005ABC0(self, direction);
            } else if (self->unk2 == 1) {
                if (direction < 2) {
                    result = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
                    if ((direction == 0 && result < 0x10) || (direction == 1 && result < 5))
                        direction = 2;
                    else
                        direction = 3;
                }
                func_8005ABC0(self, direction);
            } else if (self->unk2 == 2) {
                if (direction >= 2) {
                    result = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
                    if ((direction == 2 && result < 8) || (direction != 2 && result >= 0x18))
                        direction = 1;
                    else
                        direction = 0;
                }
                func_8005ABC0(self, direction);
            }
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_29_pod_spawner", func_8005A758);
#endif

void pod_spawner_wait(struct MainObj* self)
{
}

// pod_spawner_step_4
#ifdef MMX4_PC
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
            if (controller != NULL) {
                controller->unk6 = 1;
            }
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
#else
INCLUDE_ASM("main/nonmatchings/mains/main_29_pod_spawner", func_8005AA14);
#endif

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
        shot->unk16 = 7;
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
#ifdef MMX4_PC
void func_8005AD00(struct MainObj* self)
{
    struct Main29Record* record;
    struct ObjectHeader* target;

    switch (self->unk5) {
    case 0:
        record = SP_CUR_MAIN_OBJ->ext.main_29.slots.controller.record;
        target = (struct ObjectHeader*)SP_CUR_MAIN_OBJ->ext.main_29.slots.controller.target;
        if (record != NULL && record->unk0 != 0 && record->unk1 == 0x10) {
            record->unk4 = 2;
        }
        if (target != NULL) {
            target->state = 3;
            target->unk5 = 0;
        }
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
            if (target != NULL)
                target->unk5 = 2;
            self->unk5 = 2;
        } else {
            move_with_gravity(ANIMATED_OBJECT(self));
        }
        self->on_screen = 0;
        if (main_bss_state.frame_counter & 3) {
            update_on_screen(BASE_OBJECT(self), 0x68, 0x68);
        }
        if (!(main_bss_state.frame_counter & 0xF)) {
            func_800AF878(BASE_OBJECT(self), 0, 8, 4);
        }
        break;
    case 2:
        drop_item(BASE_OBJECT(self), 0x13);
        despawn_object(OBJECT_HEADER(self));
        break;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_29_pod_spawner", func_8005AD00);
#endif

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
    self->unk16 = 7;
    self->unk7C = 0;
    self->ext.main_29.unk94 = 0;
    set_animation(self, 5);
}

// pod_spawner_copy_main
#ifdef MMX4_PC
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
            for (u32 i = 0; i < count; i++) {
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
                        child->unk40 = D_801406A8[index] >> 7;
                        index = func_8002938C(child->id);
                        column = index * 4 + 0x18;
                        row = index + 6;
                        child->unk42 = (column - (column / 16) * 16) | (((row / 4 + 0x1E0) << 6) & 0xFFFF);
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
#ifdef MMX4_PC
void func_8005B24C(struct MainObj* self)
{
    struct Main29Ext* ext = &self->ext.main_29;

    ext->unk94 = 0;
    for (u32 i = 0; i < 4; i++) {
        struct MainObj* child = ext->slots.children[i];
        if (child != NULL && child->active != 0 && child->id == 0x1C)
            child->state = 3;
        ext->slots.children[i] = NULL;
    }
    ZeroObjectState(OBJECT_HEADER(self));
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_29_pod_spawner", func_8005B24C);
#endif

// pod_spawner_copy_state_3
#ifdef MMX4_PC
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
        if (main_bss_state.frame_counter & 3) {
            update_on_screen(BASE_OBJECT(self), 0x68, 0x68);
        }
        break;
    case 2:
        ZeroObjectState((struct ObjectHeader*)self);
        break;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_29_pod_spawner", func_8005B2C8);
#endif

union AnimationStep pod_spawner_anim_0[] = {
    { 0x00000001 },
};

union AnimationStep pod_spawner_anim_1[] = {
    { 0x00010002 },
    { 0x01010002 },
    { 0x02010002 },
    { 0x03010002 },
    { 0x04010002 },
    { 0x05010002 },
    { 0x04010002 },
    { 0x03010002 },
    { 0x02010002 },
    { 0x01010002 },
    { 0x00000002 },
};

union AnimationStep pod_spawner_anim_2[] = {
    { 0x00010003 },
    { 0x06010003 },
    { 0x07010003 },
    { 0x08010003 },
    { 0x09000003 },
};

union AnimationStep pod_spawner_anim_4[] = {
    { 0x08010003 },
    { 0x07010003 },
    { 0x06010003 },
    { 0x00000003 },
};

union AnimationStep pod_spawner_anim_3[] = {
    { 0x0A010001 },
    { 0x14010001 },
    { 0x0B010001 },
    { 0x14010001 },
    { 0x0C010001 },
    { 0x14010001 },
    { 0x0D010001 },
    { 0x0E000001 },
};

union AnimationStep pod_spawner_anim_5[] = {
    { 0x0F010001 },
    { 0x0E010001 },
    { 0x10010001 },
    { 0x0E010001 },
    { 0x13010001 },
    { 0x0E010001 },
    { 0x10010001 },
    { 0x0E010001 },
    { 0x11010001 },
    { 0x0E010001 },
    { 0x10010001 },
    { 0x0E010001 },
    { 0x12010001 },
    { 0x0E010001 },
    { 0x10010001 },
    { 0x0EF10001 },
};

union AnimationStep pod_spawner_anim_6[] = {
    { 0x20010102 },
    { 0x1F010202 },
    { 0x1E010302 },
    { 0x1D010402 },
    { 0x1C010402 },
    { 0x1B000402 },
};

union AnimationStep pod_spawner_anim_7[] = {
    { 0x15010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x19010002 },
    { 0x16010002 },
    { 0x1A010002 },
    { 0x18F90002 },
};

union AnimationStep pod_spawner_anim_8[] = {
    { 0x1B010002 },
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1F010002 },
    { 0x20000002 },
};

union AnimationStep pod_spawner_anim_9[] = {
    { 0x2C010502 },
    { 0x2B010602 },
    { 0x2A010702 },
    { 0x29010802 },
    { 0x28010802 },
    { 0x27000802 },
};

union AnimationStep pod_spawner_anim_10[] = {
    { 0x21010002 },
    { 0x22010002 },
    { 0x23010002 },
    { 0x24010002 },
    { 0x25010002 },
    { 0x22010002 },
    { 0x26010002 },
    { 0x24F90002 },
};

union AnimationStep pod_spawner_anim_11[] = {
    { 0x27010002 },
    { 0x28010002 },
    { 0x29010002 },
    { 0x2A010002 },
    { 0x2B010002 },
    { 0x2C000002 },
};

union AnimationStep pod_spawner_anim_12[] = {
    { 0x3A010902 },
    { 0x39010A02 },
    { 0x38010B02 },
    { 0x37010C02 },
    { 0x36010C02 },
    { 0x35000C02 },
};

union AnimationStep pod_spawner_anim_13[] = {
    { 0x2F010002 },
    { 0x30010002 },
    { 0x31010002 },
    { 0x32010002 },
    { 0x33010002 },
    { 0x30010002 },
    { 0x34010002 },
    { 0x31F90002 },
};

union AnimationStep pod_spawner_anim_14[] = {
    { 0x2D000001 },
};

union AnimationStep pod_spawner_anim_15[] = {
    { 0x2E000001 },
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
