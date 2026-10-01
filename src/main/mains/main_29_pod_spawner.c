// MainObj, main_object_update_funcs[29]
// 8005A4CC..8005B3FC
#include "common.h"
#include "func_tables.h"

void pod_spawner_update(struct MainObj* self)
{
    if (self->unk2 >= 0) {
        pod_spawner_state_funcs[self->state](self);
    } else {
        pod_spawner_copy_state_funcs[self->state](self);
    }
}

// pod_spawner_init
INCLUDE_ASM("main/nonmatchings/mains/main_29_pod_spawner", func_8005A538);

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
INCLUDE_ASM("main/nonmatchings/mains/main_29_pod_spawner", func_8005A758);

void pod_spawner_wait(struct MainObj* self)
{
}

// pod_spawner_step_4
INCLUDE_ASM("main/nonmatchings/mains/main_29_pod_spawner", func_8005AA14);

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
INCLUDE_ASM("main/nonmatchings/mains/main_29_pod_spawner", func_8005ABC0);

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_29_pod_spawner", pod_spawner_despawn);
#else
void pod_spawner_despawn(struct MainObj* self)
{
    struct Main29Ext* context;
    struct Main29Record* record;
    struct Main29Record* target;

    context = &SP_CUR_MAIN_OBJ->ext.main_29;
    target = context->slots.controller.target;
    record = context->slots.controller.record;
    if (record != NULL && record->unk0 != 0 && record->unk1 == 0x10) {
        record->unk4 = 2;
    }
    target->unk4 = 2;
    despawn_object(OBJECT_HEADER(self));
}
#endif

// pod_spawner_state_3
INCLUDE_ASM("main/nonmatchings/mains/main_29_pod_spawner", func_8005AD00);

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
INCLUDE_ASM("main/nonmatchings/mains/main_29_pod_spawner", func_8005AF5C);

// pod_spawner_copy_state_2
INCLUDE_ASM("main/nonmatchings/mains/main_29_pod_spawner", func_8005B24C);

// pod_spawner_copy_state_3
INCLUDE_ASM("main/nonmatchings/mains/main_29_pod_spawner", func_8005B2C8);

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
