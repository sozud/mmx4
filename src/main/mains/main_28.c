// MainObj, main_object_update_funcs[28]
// 80059C48..8005A4CC
#include "common.h"
#include "func_tables.h"

void spawner_pod_update(struct MainObj* self)
{
    spawner_pod_state_funcs[self->state](self);
}

void spawner_pod_init(struct MainObj* arg0)
{
    volatile struct MainObj* self = arg0;
    s32 value8 = self->x_pos.val;
    s32 valueC = self->y_pos.val;
    u16 high8 = self->x_pos.i.hi;
    s32 tableIndex;
    u16 valueE;

    tableIndex = 1;
    self->state = tableIndex;
    self->on_screen = tableIndex;
    tableIndex = ((volatile u8*)self)[2];
    self->unk5 = 2;
    self->hp = 3;
    self->contact_damage = 3;
    self->animation_table = (const u8* const*)spawner_pod_animations;
    self->collision_data = D_80107074;
    self->unk16 = 5;
    valueE = self->y_pos.i.hi;
    self->unk6 = 0;
    self->unk7C = 0;
    self->invincibility_timer = 0;
    self->ext.main_28.unk85 = 0;
    self->hurt_box = 0;
    self->attack_box = 0;
    self->terrain_box = 0;
    self->air_state = 0;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    tableIndex = (tableIndex << 1) & 0xFF;
    self->unk18.val = value8;
    self->unk1C.val = valueC;
    self->ext.main_28.unk86 = high8;
    self->ext.main_28.unk88 = valueE;
    self->ext.main_28.unk84 = ((u8*)spawner_pod_init_data)[tableIndex];
    self->unk15 = ((u8*)spawner_pod_init_data)[tableIndex + 1];
    set_animation(arg0, arg0->ext.main_28.unk84);
}

void spawner_pod_main(struct MainObj* self)
{
    struct MainObj* context = self->ext.main_28.context;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    self->x_pos.val = context->x_pos.val;
    self->y_pos.val = context->y_pos.val;

    spawner_pod_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    if (func_8002DD04(self) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        self->x_speed = 0;
        self->y_speed = 0;
        spawn_debris(2, spawner_pod_debris, self);
        drop_item(BASE_OBJECT(self), 0xC);
        self->state = 2;
        return;
    }
    update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
}

void spawner_pod_idle(struct MainObj* self)
{
}

// spawner_pod_step_2
INCLUDE_ASM("main/nonmatchings/mains/main_28", func_80059E40);

// spawner_pod_step_3
INCLUDE_ASM("main/nonmatchings/mains/main_28", func_80059F60);

void spawner_pod_step_4(struct MainObj* self)
{
}

void spawner_pod_detach(struct MainObj* self)
{
    struct MainObj* context;

    context = self->ext.main_28.context;
    if (context->active != 0 && context->ext.main_29.slots.children[self->ext.main_28.index] == self) {
        context->ext.main_29.unk94--;
        context->ext.main_29.slots.children[self->ext.main_28.index] = NULL;
    }
    ZeroObjectState(OBJECT_HEADER(self));
}

void spawner_pod_explode(struct MainObj* self)
{
    spawn_explosion(BASE_OBJECT(self));
    self->x_speed = 0;
    self->y_speed = 0;
    spawn_debris(2, spawner_pod_debris, self);
    ZeroObjectState(OBJECT_HEADER(self));
}

void spawner_pod_remove(struct MainObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

union AnimationStep spawner_pod_anim_0[] = {
    { 0x00000001 },
};

union AnimationStep spawner_pod_anim_1[] = {
    { 0x01010003 },
    { 0x02010003 },
    { 0x00010003 },
    { 0x03010003 },
    { 0x00000003 },
};

union AnimationStep spawner_pod_anim_2[] = {
    { 0x04010003 },
    { 0x05010003 },
    { 0x06010003 },
    { 0x07010003 },
    { 0x08FC0003 },
};

union AnimationStep spawner_pod_anim_3[] = {
    { 0x00010002 },
    { 0x09010002 },
    { 0x0A010002 },
    { 0x0B010002 },
    { 0x0A010002 },
    { 0x0B010002 },
    { 0x0A010002 },
    { 0x09010002 },
    { 0x00010002 },
    { 0x09010002 },
    { 0x0A010002 },
    { 0x0B010002 },
    { 0x0A010002 },
    { 0x0B010002 },
    { 0x0A010002 },
    { 0x09000002 },
};

union AnimationStep spawner_pod_anim_8[] = {
    { 0x1F000001 },
};

union AnimationStep spawner_pod_anim_9[] = {
    { 0x20010003 },
    { 0x21010003 },
    { 0x1F010003 },
    { 0x22010003 },
    { 0x1F000003 },
};

union AnimationStep spawner_pod_anim_10[] = {
    { 0x23010003 },
    { 0x24010003 },
    { 0x25010003 },
    { 0x26010003 },
    { 0x27FC0003 },
};

union AnimationStep spawner_pod_anim_11[] = {
    { 0x1F010002 },
    { 0x28010002 },
    { 0x29010002 },
    { 0x2A010002 },
    { 0x29010002 },
    { 0x2A010002 },
    { 0x29010002 },
    { 0x28010002 },
    { 0x1F010002 },
    { 0x28010002 },
    { 0x29010002 },
    { 0x2A010002 },
    { 0x29010002 },
    { 0x2A010002 },
    { 0x29010002 },
    { 0x28000002 },
};

union AnimationStep spawner_pod_anim_4[] = {
    { 0x0C000001 },
};

union AnimationStep spawner_pod_anim_5[] = {
    { 0x0D010003 },
    { 0x0E010003 },
    { 0x0C010003 },
    { 0x0F010003 },
    { 0x0C000003 },
};

union AnimationStep spawner_pod_anim_6[] = {
    { 0x10010003 },
    { 0x11010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x14FC0003 },
};

union AnimationStep spawner_pod_anim_7[] = {
    { 0x0C010002 },
    { 0x15010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x16010002 },
    { 0x15010002 },
    { 0x0C010002 },
    { 0x15010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x16010002 },
    { 0x15000002 },
};

union AnimationStep spawner_pod_anim_12[] = {
    { 0x18010001 },
    { 0x19010001 },
    { 0x1A010001 },
    { 0x1BFD0001 },
};

union AnimationStep spawner_pod_anim_13[] = {
    { 0x1C000001 },
};

union AnimationStep spawner_pod_anim_14[] = {
    { 0x1D000001 },
};

union AnimationStep spawner_pod_anim_15[] = {
    { 0x1E000001 },
};

union AnimationStep* spawner_pod_animations[] = {
    spawner_pod_anim_0,
    spawner_pod_anim_1,
    spawner_pod_anim_2,
    spawner_pod_anim_3,
    spawner_pod_anim_4,
    spawner_pod_anim_5,
    spawner_pod_anim_6,
    spawner_pod_anim_7,
    spawner_pod_anim_8,
    spawner_pod_anim_9,
    spawner_pod_anim_10,
    spawner_pod_anim_11,
    spawner_pod_anim_12,
    spawner_pod_anim_13,
    spawner_pod_anim_14,
    spawner_pod_anim_15,
};

u8 spawner_pod_debris[] = {
    0x0D,
    0x0E,
    0x0F,
    0x00,
};

struct Unk_unk68 D_800FD598[6] = {
    { -5, -5, 10, 11 },
    { -5, -5, 10, 11 },
    { -11, -11, 21, 21 },
    { -11, -11, 21, 21 },
    { 22, 0, 22, 18 },
    { 0, 21, 18, 21 },
};

struct Unk_unk68* D_800FD5B0[] = {
    D_800FD598 + 4,
    D_800FD598 + 5,
};

struct Unk_unk68* D_800FD5B8[] = {
    D_800FD598 + 2,
    D_800FD598 + 3,
};

struct Unk_unk68* D_800FD5C0[] = {
    D_800FD598,
    D_800FD598 + 1,
};

u8 D_800FD5C8[] = {
    0x0A,
    0x14,
    0x1E,
    0x28,
    0x32,
    0x0A,
    0x14,
    0x1E,
    0x28,
    0x32,
    0x0A,
    0x14,
    0x1E,
    0x28,
    0x32,
    0x0A,
    0x14,
    0x1E,
    0x28,
    0x32,
    0x0A,
    0x14,
    0x1E,
    0x28,
    0x32,
    0x0A,
    0x14,
    0x1E,
    0x28,
    0x32,
    0x0A,
    0x14,
};

void (*spawner_pod_state_funcs[])(struct MainObj*) = {
    spawner_pod_init,
    spawner_pod_main,
    spawner_pod_detach,
    spawner_pod_explode,
    spawner_pod_remove,
};

struct Main28InitData spawner_pod_init_data[4] = {
    { 5, 0x00 },
    { 5, 0x40 },
    { 1, 0x00 },
    { 9, 0x40 },
};

void (*spawner_pod_step_funcs[])(struct MainObj*) = {
    enemy_hit_reaction,
    spawner_pod_idle,
    func_80059E40,
    func_80059F60,
    spawner_pod_step_4,
};

struct FixedPointPosition D_800FD618[4] = {
    { (s32)0xFFFD0000, 0 },
    { (s32)0x00030000, 0 },
    { 0, (s32)0xFFFD0000 },
    { 0, (s32)0x00030000 },
};

struct FixedPointPosition D_800FD638[4] = {
    { (s32)0xFFFF0000, 0 },
    { (s32)0x00010000, 0 },
    { 0, (s32)0xFFFF0000 },
    { 0, (s32)0x00010000 },
};
