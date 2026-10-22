// MainObj, main_object_update_funcs[28]
// 80059C48..8005A4CC
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_28_spawner_pod.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "main/objects.h"
#include "main/object_motion.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/object_motion.h"
#endif

struct Main28InitData {
    u8 unk84;
    u8 unk15;
};

extern struct Main28InitData spawner_pod_init_data[];

extern u8 spawner_pod_debris[];

void spawner_pod_main(struct MainObj*);

void spawner_pod_explode(struct MainObj*);

// spawner_pod_step_funcs
extern void (*spawner_pod_step_funcs[])(struct MainObj*);

extern void (*spawner_pod_state_funcs[])(struct MainObj*);

void spawner_pod_update(struct MainObj* self)
{
    spawner_pod_state_funcs[self->state](self);
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_28_spawner_pod", spawner_pod_init);
#else
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
    self->unk16 = VISUAL_SATURN_LAYER(5);
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
#ifdef MMX4_SATURN
    self->unk15 = (((u8*)spawner_pod_init_data)[tableIndex + 1] & 0x40) ? PLAYER_FACING_RIGHT : 0;
#else
    self->unk15 = ((u8*)spawner_pod_init_data)[tableIndex + 1];
#endif
    set_animation(arg0, arg0->ext.main_28.unk84);
}
#endif

void spawner_pod_main(struct MainObj* self)
{
    s32 hit;
    struct MainObj* context = self->ext.main_28.context;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    self->x_pos.val = context->x_pos.val;
    self->y_pos.val = context->y_pos.val;

    spawner_pod_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    hit = func_8002DD04(self);
    if (hit < 0) {
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

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80059E40(struct MainObj* self);
void func_80059F60(struct MainObj* self);
extern u8 D_800FD5C8[32];
extern struct FixedPointPosition D_800FD618[4];
extern struct FixedPointPosition D_800FD638[4];
extern u8 D_800FD5C8[32];
extern struct Unk_unk68* D_800FD5B0[2];
extern struct Unk_unk68* D_800FD5B8[2];
extern struct Unk_unk68* D_800FD5C0[2];
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80059E40(struct MainObj* self)
{
    struct Main28Ext* ext = &self->ext.main_28;
    if (self->animation_step.fields.relative_step == 0) {
        u8 index = (u8)self->unk2 * 2;
        self->unk5 = 3;
        ext->context->unk7C = 0;
        set_animation(self, ext->unk84 + 1);
        self->x_speed = 0;
        self->y_speed = 0;
        if (get_random() & 7) {
            self->x_accel = D_800FD618[index / 2].x;
            self->gravity = D_800FD618[index / 2].y;
        } else {
            self->x_accel = D_800FD638[index / 2].x;
            self->gravity = D_800FD638[index / 2].y;
        }
        self->unk7C = 0;
        self->unk7E = D_800FD5C8[get_random() & 0x1F];
        self->hurt_box = D_800FD5B8[0];
        self->attack_box = D_800FD5C0[0];
        self->terrain_box = D_800FD5B0[0];
    }
    animate_object(ANIMATED_OBJECT(self));
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_28_spawner_pod", func_80059E40);
#endif

// spawner_pod_step_3
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80059F60(struct MainObj* self)
{
    struct Main28Ext* ext = &self->ext.main_28;
    struct ShotObj* shot;
    s32 turn = 0;

    switch (self->unk2) {
    case 0:
        turn = (self->x_speed <= -0x500000 && self->unk15 == 0) || (self->x_speed >= -0x10000 && self->unk15 != 0);
        break;
    case 1:
        turn = (self->x_speed > 0x4FFFFF && self->unk15 != 0) || (self->x_speed <= 0x10000 && self->unk15 == 0);
        break;
    case 2:
        turn = (self->y_speed <= -0x500000 && self->unk15 == 0) || (self->y_speed >= -0x10000 && self->unk15 != 0);
        break;
    case 3:
        turn = (self->y_speed > 0x4FFFFF && self->unk15 != 0) || (self->y_speed <= 0x10000 && self->unk15 == 0);
        break;
    }
    if (self->unk7E != 0)
        self->unk7E--;

    switch ((u8)self->unk6) {
    case 0:
        if (self->unk7E == 0 || turn) {
            ext->unk85++;
            self->unk6 = 1;
            self->unk7C = 0x3C;
        } else {
            self->x_speed += self->x_accel;
            self->y_speed += self->gravity;
            animate_object(ANIMATED_OBJECT(self));
        }
        break;
    case 1:
        if (ext->unk85 >= 4) {
            ext->unk85 = 0;
            set_animation(self, ext->unk84 + 2);
            self->unk6 = 2;
            break;
        }
        self->unk15 ^= PLAYER_FACING_RIGHT;
        if (self->unk2 >= 2) {
            ext->unk84 ^= 8;
            set_animation(self, ext->unk84 + 1);
        }
        self->unk7C = 0x20;
        self->unk6 = 4;
        self->x_accel = -self->x_accel;
        self->gravity = -self->gravity;
        self->unk7E = 0;
        break;
    case 2:
        if (self->animation_step.fields.relative_step == 0) {
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0x12;
                shot->x_pos.val = self->x_pos.val + self->x_speed;
                shot->y_pos.val = self->y_pos.val + self->y_speed;
                shot->animation_table = (u32**)self->animation_table;
                shot->unk40 = self->unk40;
                shot->unk3C = (void*)self->sprite_frames;
                shot->unk42 = self->unk42 & 0x7FFF;
                shot->unk7C = (struct WeaponObj*)self;
                shot->unk16 = self->unk16;
                shot->unk15 = self->unk15;
            }
            self->unk7C = 0x10;
            self->unk6 = 3;
        }
        animate_object(ANIMATED_OBJECT(self));
        break;
    case 3:
        if (self->unk7C != 0) {
            self->unk7C--;
            break;
        }
        self->unk15 ^= PLAYER_FACING_RIGHT;
        if (self->unk2 >= 2)
            ext->unk84 ^= 8;
        self->x_accel = -self->x_accel;
        self->gravity = -self->gravity;
        self->unk6 = 0;
        self->unk7C = 0;
        self->unk7E = D_800FD5C8[get_random() & 0x1F];
        set_animation(self, ext->unk84 + 1);
        break;
    case 4:
        if (self->unk7C != 0) {
            self->unk7C--;
            break;
        }
        self->unk7C = 0;
        self->unk7E = D_800FD5C8[get_random() & 0x1F];
        self->unk6 = 0;
        break;
    }
    self->x_pos.val += self->x_speed;
    self->y_pos.val += self->y_speed;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_28_spawner_pod", func_80059F60);
#endif

void spawner_pod_step_4(struct MainObj* self)
{
}

void spawner_pod_detach(struct MainObj* self)
{
    struct MainObj* context;

    context = self->ext.main_28.context;
    if (context->active != 0 && (&context->ext)->main_29.slots.children[self->ext.main_28.index] == self) {
        context->ext.main_29.unk94--;
        (&context->ext)->main_29.slots.children[self->ext.main_28.index] = NULL;
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
    { 1, 0, 0, 0x00 },
};

union AnimationStep spawner_pod_anim_1[] = {
    { 3, 0, 1, 0x01 },
    { 3, 0, 1, 0x02 },
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x03 },
    { 3, 0, 0, 0x00 },
};

union AnimationStep spawner_pod_anim_2[] = {
    { 3, 0, 1, 0x04 },
    { 3, 0, 1, 0x05 },
    { 3, 0, 1, 0x06 },
    { 3, 0, 1, 0x07 },
    { 3, 0, -4, 0x08 },
};

union AnimationStep spawner_pod_anim_3[] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x0A },
    { 2, 0, 1, 0x0B },
    { 2, 0, 1, 0x0A },
    { 2, 0, 1, 0x0B },
    { 2, 0, 1, 0x0A },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x0A },
    { 2, 0, 1, 0x0B },
    { 2, 0, 1, 0x0A },
    { 2, 0, 1, 0x0B },
    { 2, 0, 1, 0x0A },
    { 2, 0, 0, 0x09 },
};

union AnimationStep spawner_pod_anim_8[] = {
    { 1, 0, 0, 0x1F },
};

union AnimationStep spawner_pod_anim_9[] = {
    { 3, 0, 1, 0x20 },
    { 3, 0, 1, 0x21 },
    { 3, 0, 1, 0x1F },
    { 3, 0, 1, 0x22 },
    { 3, 0, 0, 0x1F },
};

union AnimationStep spawner_pod_anim_10[] = {
    { 3, 0, 1, 0x23 },
    { 3, 0, 1, 0x24 },
    { 3, 0, 1, 0x25 },
    { 3, 0, 1, 0x26 },
    { 3, 0, -4, 0x27 },
};

union AnimationStep spawner_pod_anim_11[] = {
    { 2, 0, 1, 0x1F },
    { 2, 0, 1, 0x28 },
    { 2, 0, 1, 0x29 },
    { 2, 0, 1, 0x2A },
    { 2, 0, 1, 0x29 },
    { 2, 0, 1, 0x2A },
    { 2, 0, 1, 0x29 },
    { 2, 0, 1, 0x28 },
    { 2, 0, 1, 0x1F },
    { 2, 0, 1, 0x28 },
    { 2, 0, 1, 0x29 },
    { 2, 0, 1, 0x2A },
    { 2, 0, 1, 0x29 },
    { 2, 0, 1, 0x2A },
    { 2, 0, 1, 0x29 },
    { 2, 0, 0, 0x28 },
};

union AnimationStep spawner_pod_anim_4[] = {
    { 1, 0, 0, 0x0C },
};

union AnimationStep spawner_pod_anim_5[] = {
    { 3, 0, 1, 0x0D },
    { 3, 0, 1, 0x0E },
    { 3, 0, 1, 0x0C },
    { 3, 0, 1, 0x0F },
    { 3, 0, 0, 0x0C },
};

union AnimationStep spawner_pod_anim_6[] = {
    { 3, 0, 1, 0x10 },
    { 3, 0, 1, 0x11 },
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x13 },
    { 3, 0, -4, 0x14 },
};

union AnimationStep spawner_pod_anim_7[] = {
    { 2, 0, 1, 0x0C },
    { 2, 0, 1, 0x15 },
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x15 },
    { 2, 0, 1, 0x0C },
    { 2, 0, 1, 0x15 },
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x16 },
    { 2, 0, 0, 0x15 },
};

union AnimationStep spawner_pod_anim_12[] = {
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x19 },
    { 1, 0, 1, 0x1A },
    { 1, 0, -3, 0x1B },
};

union AnimationStep spawner_pod_anim_13[] = {
    { 1, 0, 0, 0x1C },
};

union AnimationStep spawner_pod_anim_14[] = {
    { 1, 0, 0, 0x1D },
};

union AnimationStep spawner_pod_anim_15[] = {
    { 1, 0, 0, 0x1E },
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

struct Unk_unk68 D_800FD598 = { -5, -5, 10, 11 };

struct Unk_unk68 D_800FD59C = { -5, -5, 10, 11 };

struct Unk_unk68 D_800FD5A0 = { -11, -11, 21, 21 };

struct Unk_unk68 D_800FD5A4 = { -11, -11, 21, 21 };

struct Unk_unk68 D_800FD5A8 = { 22, 0, 22, 18 };

struct Unk_unk68 D_800FD5AC = { 0, 21, 18, 21 };

struct Unk_unk68* D_800FD5B0[] = {
    &D_800FD5A8,
    &D_800FD5AC,
};

struct Unk_unk68* D_800FD5B8[] = {
    &D_800FD5A0,
    &D_800FD5A4,
};

struct Unk_unk68* D_800FD5C0[] = {
    &D_800FD598,
    &D_800FD59C,
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
