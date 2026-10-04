// WeaponObj, weapon_object_update_funcs[4]
// 800951C0..800957B0
#include "common.h"

void rising_fire_draw(struct WeaponObj* arg0);

void rising_fire_update(struct WeaponObj* arg0)
{
    s32 disabled;

    disabled = 0;
    if (g_Player.input_locked != 0) {
        disabled = 1;
    }
    if (g_Player.capsule_state != 0) {
        disabled = 1;
    }
    if (g_Player.weapon != 4) {
        disabled = 1;
    }
    if (g_Player.shot_type == 0xD) {
        disabled = 1;
    }
    if (disabled != 0) {
        arg0->state = 3;
    }
    rising_fire_state_funcs[arg0->state](arg0);
}

// rising_fire_init
INCLUDE_ASM("main/nonmatchings/weapons/weapon_04_rising_fire", func_80095254);

void rising_fire_main(struct WeaponObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x28) == 0) {
        animate_object(ANIMATED_OBJECT(arg0));
        move_object(MOVING_OBJECT(arg0));
        rising_fire_draw(arg0);
        return;
    }

    arg0->on_screen = 0;
    arg0->state = 3;
}

void rising_fire_despawn(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    g_Player.shot_count--;
    g_Player.special_shot_count--;
    ZeroObjectState((struct ObjectHeader*)arg0);
}

void rising_fire_draw(struct WeaponObj* arg0)
{
    decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
    update_on_screen(BASE_OBJECT(arg0), 0x20, 0x28);
}

// WeaponObj, weapon_object_update_funcs[13]

void rising_fire_charged_update(struct WeaponObj* arg0)
{
    s32 should_reset = g_Player.input_locked != 0;

    if (g_Player.capsule_state != 0) {
        should_reset = 1;
    }
    if (g_Player.weapon != 4) {
        should_reset = 1;
    }
    if (should_reset != 0) {
        arg0->state = 3;
    }
    rising_fire_charged_state_funcs[arg0->state](arg0);
}

// rising_fire_charged_init
INCLUDE_ASM("main/nonmatchings/weapons/weapon_04_rising_fire", func_80095538);

void rising_fire_charged_main(struct WeaponObj* self)
{
    u8 timer;
    s8 event;
    u8* timer_ptr = &self->ext.weapon_13.timer;
    struct PlayerObj* player = &g_Player;

    if (func_8002B1E8(BASE_OBJECT(self), 0x38, 0x38) == 0) {
        animate_object(ANIMATED_OBJECT(self));
        if (self->unk5 == 0) {
            if (player->unk17 == 0x67) {
                move_object(MOVING_OBJECT(self));
                self->unk5++;
            } else {
                self->x_pos.val = player->x_pos.val;
                self->y_pos.val = player->y_pos.val;
            }
        } else {
            move_object(MOVING_OBJECT(self));
        }

        event = self->animation_step.fields.event;
        if (event != 0) {
            self->unk50 = &rising_fire_charged_hit_boxes[event];
        } else {
            self->unk50 = NULL;
        }

        timer = *timer_ptr;
        if (timer == 0) {
            *timer_ptr = 4;
            self->unk64++;
        } else {
            *timer_ptr = timer - 1;
        }
        rising_fire_charged_draw(self);
    } else {
        self->on_screen = 0;
        self->state = 3;
    }
}

void rising_fire_charged_draw(struct WeaponObj* arg0)
{
    decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
    update_on_screen(BASE_OBJECT(arg0), 0x38, 0x38);
}

struct Unk_unk68 rising_fire_hit_box[] = {
    { -22, -32, 0x2A, 0x36 },
};

struct Unk_unk68 rising_fire_charged_hit_boxes[] = {
    { 0, 0, 0, 0 },
    { -16, -10, 0x1C, 0x14 },
    { -34, -36, 0x3C, 0x34 },
    { -40, -50, 0x40, 0x56 },
};

void (*rising_fire_state_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80095254,
    (void (*)(struct WeaponObj*))rising_fire_main,
    (void (*)(struct WeaponObj*))rising_fire_despawn,
    (void (*)(struct WeaponObj*))rising_fire_despawn,
};

u8 rising_fire_charged_offsets[4] = {
    0xF5,
    0xF6,
    0x06,
    0xF4,
};

void (*rising_fire_charged_state_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80095538,
    (void (*)(struct WeaponObj*))rising_fire_charged_main,
    (void (*)(struct WeaponObj*))rising_fire_despawn,
    (void (*)(struct WeaponObj*))rising_fire_despawn,
};
