// MainObj, main_object_update_funcs[12]
// 8004B8C0..8004C734
#include "common.h"
#include "func_tables.h"

void hover_sentry_update(struct MainObj* self)
{
    hover_sentry_state_funcs[self->state](self);
}

// hover_sentry_init
INCLUDE_ASM("main/nonmatchings/mains/main_12_hover_sentry", func_8004B8FC);

void hover_sentry_main(struct MainObj* self)
{
    s32 result;
    s8 mode = self->unk5;

    if (mode != 5 || self->unk6 != 4) {
        CollisionRelated(PLAYER_OBJECT(self));
    }
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    hover_sentry_check_player_near(self);
    hover_sentry_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    result = func_8002DD04(self);
    if (result < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(5, hover_sentry_debris, self);
        drop_item(BASE_OBJECT(self), 0xE);
    } else {
        if (result > 0) {
            SP_CUR_MAIN_OBJ->ext.main_12.saved_unk5 = self->unk5;
        }
        if (func_8002B160(BASE_OBJECT(self)) == 0) {
            is_on_screen(BASE_OBJECT(self));
            return;
        }
    }
    self->state++;
}

void hover_sentry_resume_step(struct MainObj* self)
{
    self->unk5 = SP_CUR_MAIN_OBJ->ext.main_12.saved_unk5;
}

void hover_sentry_bob(struct MainObj* self)
{
    struct MainObj* current;

    move_with_gravity(ANIMATED_OBJECT(self));
    current = SP_CUR_MAIN_OBJ;
    if (current->ext.main_12.unk88 == 0) {
        if (self->y_speed >= 0) {
            self->y_speed = FIXED(0.5);
            self->gravity = -self->gravity;
            current->ext.main_12.unk88 = 1;
        }
    } else if (self->y_speed < 0) {
        self->y_speed = FIXED(-0.5);
        self->gravity = -self->gravity;
        current->ext.main_12.unk88 = 0;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void hover_sentry_alert(struct MainObj* self)
{
    self->unk5 = 4;
    self->unk6 = 0;
    self->unk7 = 0;
    self->unk7E = 8;
    animate_object(self);
}

// hover_sentry_attack_0
INCLUDE_ASM("main/nonmatchings/mains/main_12_hover_sentry", func_8004BCFC);

// hover_sentry_attack_1
INCLUDE_ASM("main/nonmatchings/mains/main_12_hover_sentry", func_8004BF5C);

// hover_sentry_attack_2
INCLUDE_ASM("main/nonmatchings/mains/main_12_hover_sentry", func_8004C210);

// hover_sentry_attack_3
INCLUDE_ASM("main/nonmatchings/mains/main_12_hover_sentry", func_8004C394);

// hover_sentry_attack_4
INCLUDE_ASM("main/nonmatchings/mains/main_12_hover_sentry", func_8004C56C);

void hover_sentry_despawn(struct MainObj* self)
{
    if (self->unk2 == 2) {
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }
    despawn_object(OBJECT_HEADER(self));
}

void hover_sentry_face_player(struct MainObj* self)
{
    if (self->x_pos.val < g_Player.x_pos.val) {
        self->unk15 = 0x40;
    } else {
        self->unk15 = 0;
    }
}

void hover_sentry_check_player_near(struct MainObj* self)
{
    s16 distance;

    if (self->unk7C != 0) {
        if (self->unk5 == 2) {
            distance = (g_Player.x_pos.i.hi - self->x_pos.i.hi) < 0 ? self->x_pos.i.hi - g_Player.x_pos.i.hi : g_Player.x_pos.i.hi - self->x_pos.i.hi;
            if (distance < 0x90) {
                self->unk5 = 3;
                self->unk6 = 0;
            }
        }
    }
}

union AnimationStep hover_sentry_anim_0[] = {
    { 0x0001000A },
    { 0x0101001C },
    { 0x02FE000F },
};

union AnimationStep hover_sentry_anim_1[] = {
    { 0x03010004 },
    { 0x04010004 },
    { 0x05010004 },
    { 0x06FD0004 },
};

union AnimationStep hover_sentry_anim_2[] = {
    { 0x07010001 },
    { 0x07FF0003 },
};

union AnimationStep hover_sentry_anim_3[] = {
    { 0x08010006 },
    { 0x09010006 },
    { 0x0AFE0006 },
};

union AnimationStep hover_sentry_anim_4[] = {
    { 0x0B010005 },
    { 0x0C010006 },
    { 0x0DFE0106 },
};

union AnimationStep hover_sentry_anim_5[] = {
    { 0x0E010006 },
    { 0x0F010006 },
    { 0x10010105 },
    { 0x11010104 },
    { 0x12010106 },
    { 0x0B018106 },
    { 0x0C018106 },
    { 0x13010106 },
    { 0x14010006 },
    { 0x15010005 },
    { 0x16F60004 },
};

union AnimationStep hover_sentry_anim_6[] = {
    { 0x17010008 },
    { 0x18FF010C },
};

union AnimationStep hover_sentry_anim_7[] = {
    { 0x19010002 },
    { 0x1A010002 },
    { 0x1B010008 },
    { 0x1BFF0101 },
};

union AnimationStep hover_sentry_anim_8[] = {
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1F010002 },
    { 0x20010002 },
    { 0x1B010002 },
    { 0x20FE0002 },
};

union AnimationStep hover_sentry_anim_9[] = {
    { 0x0B010002 },
    { 0x0CFF0002 },
};

union AnimationStep hover_sentry_anim_10[] = {
    { 0x0D010006 },
    { 0x0DFF0101 },
};

union AnimationStep hover_sentry_anim_11[] = {
    { 0x21000001 },
};

union AnimationStep hover_sentry_anim_12[] = {
    { 0x22000001 },
};

union AnimationStep hover_sentry_anim_13[] = {
    { 0x23000001 },
};

union AnimationStep hover_sentry_anim_14[] = {
    { 0x24000001 },
};

union AnimationStep hover_sentry_anim_15[] = {
    { 0x25010001 },
    { 0x26010001 },
    { 0x25010001 },
    { 0x27FD0001 },
};

union AnimationStep* hover_sentry_animations[] = {
    hover_sentry_anim_0,
    hover_sentry_anim_1,
    hover_sentry_anim_2,
    hover_sentry_anim_3,
    hover_sentry_anim_4,
    hover_sentry_anim_5,
    hover_sentry_anim_6,
    hover_sentry_anim_7,
    hover_sentry_anim_8,
    hover_sentry_anim_9,
    hover_sentry_anim_10,
    hover_sentry_anim_11,
    hover_sentry_anim_12,
    hover_sentry_anim_13,
    hover_sentry_anim_14,
    hover_sentry_anim_15,
};

u8 hover_sentry_debris[] = {
    0x0B,
    0x0C,
    0x0D,
    0x0E,
    0x0F,
    0x00,
    0x00,
    0x00,
};

struct Unk_unk68 D_800FB684 = { -2, 3, 18, 4 };

struct Unk_unk68 D_800FB688 = { -12, -2, 21, 11 };

struct Unk_unk68 D_800FB68C = { -16, -9, 34, 20 };

struct Unk_unk68 D_800FB690 = { 0, -5, 7, 17 };

struct Unk_unk68 D_800FB694 = { -7, -18, 13, 28 };

struct Unk_unk68 D_800FB698 = { -8, -24, 15, 38 };

struct Unk_unk68 D_800FB69C = { -5, 0, 17, 9 };

struct Unk_unk68 D_800FB6A0 = { -10, -15, 11, 31 };

struct Unk_unk68 D_800FB6A4 = { -15, -27, 25, 54 };

void (*hover_sentry_state_funcs[])(struct MainObj*) = {
    func_8004B8FC,
    hover_sentry_main,
    hover_sentry_despawn,
};

void (*hover_sentry_step_funcs[9])() = {
    enemy_hit_reaction,
    hover_sentry_resume_step,
    hover_sentry_bob,
    hover_sentry_alert,
    func_8004BCFC,
    func_8004BF5C,
    func_8004C210,
    func_8004C394,
    func_8004C56C,
};

u16 D_800FB6D8[18] = {
    0x0010,
    0x0010,
    0x0010,
    0x0010,
    0x0040,
    0x0040,
    0x0040,
    0x0040,
    0x0040,
    0x0040,
    0x0080,
    0x0080,
    0x0080,
    0x0080,
    0x00A0,
    0x00A0,
    0x00C0,
    0x0000,
};
