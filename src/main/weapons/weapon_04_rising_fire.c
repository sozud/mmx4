// WeaponObj, weapon_object_update_funcs[4]
// 800951C0..800957B0
#include "common.h"
#include "main/weapons/weapon_04_rising_fire.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/objects.h"

// rising_fire_state_funcs
extern void (*rising_fire_state_funcs[])(struct WeaponObj*);

void rising_fire_main(struct WeaponObj*);
void rising_fire_despawn(struct WeaponObj*);
void rising_fire_despawn(struct WeaponObj*);

// rising_fire_charged_state_funcs
extern struct Unk_unk68 rising_fire_charged_hit_boxes[4];
extern void (*rising_fire_charged_state_funcs[])(struct WeaponObj*);

void rising_fire_charged_main(struct WeaponObj*);

void rising_fire_despawn(struct WeaponObj*);
void rising_fire_despawn(struct WeaponObj*);

extern u8 rising_fire_charged_offsets[4];
extern struct Unk_unk68 rising_fire_hit_box[];
extern union AnimationStep* D_8011C0B0[];

#include "weapon_resources.h"

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

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80095254(struct WeaponObj* arg0);
void func_80095538(struct WeaponObj* arg0);
extern struct Unk_unk68 rising_fire_hit_box[];
extern u8 rising_fire_charged_offsets[4];
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/weapons/weapon_04_rising_fire", func_80095254);
#else
void func_80095254(struct WeaponObj* arg0)
{
    struct PlayerObj* player;

    arg0->on_screen = 1;
    arg0->unk50 = rising_fire_hit_box;
    arg0->unk64 = 1;
    arg0->unk38 = (u8*)SP_PLAYER_GFX + SP_PLAYER_GFX[5];
    arg0->unk3C = (u8*)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[0xD];
    arg0->animation_table = D_8011C0B0;
    arg0->unk40 = WEAPON_TEXTURE_SPECIAL_0;
    arg0->unk42 = WEAPON_PALETTE_1;
    arg0->unk16 = 1;
    arg0->unk15 = 0;
    player = &g_Player;
    if (g_Player.unk15 == 0)
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi + (s8)rising_fire_charged_offsets[arg0->unk2 * 2];
    else
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi - (s8)rising_fire_charged_offsets[arg0->unk2 * 2];
    arg0->y_pos.i.hi = player->y_pos.i.hi + (s8)rising_fire_charged_offsets[arg0->unk2 * 2 + 1];
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0x70000;
    arg0->unk28.val = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 1;
    arg0->unk49 = 0;
    set_animation(arg0, 1);
    func_8001540C(0, WEAPON_SOUND_FIRE, arg0);
    arg0->unk5 = 0;
    arg0->state++;
    rising_fire_draw(arg0);
}
#endif

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
    s32 should_reset = 0;

    if (g_Player.input_locked != 0) {
        should_reset = 1;
    }
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
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/weapons/weapon_04_rising_fire", func_80095538);
#else
void func_80095538(struct WeaponObj* arg0)
{
    arg0->on_screen = 1;
    arg0->unk64 = 1;
    arg0->unk38 = (u8*)SP_PLAYER_GFX + SP_PLAYER_GFX[5];
    arg0->unk3C = (u8*)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[0xD];
    arg0->animation_table = D_8011C0B0;
    arg0->unk40 = WEAPON_TEXTURE_SPECIAL_0;
    arg0->unk42 = WEAPON_PALETTE_1;
    arg0->unk16 = 1;
    arg0->unk15 = g_Player.unk15;
    arg0->x_pos.val = g_Player.x_pos.val;
    arg0->y_pos.val = g_Player.y_pos.val;
    arg0->x_vel.val = 0;
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0x70000;
    arg0->unk2C = 0;
    arg0->unk67 = 1;
    arg0->unk49 = 0;
    arg0->ext.weapon_13.timer = 4;
    if (arg0->unk2 == 0)
        set_animation(arg0, 3);
    else
        set_animation(arg0, 5);
    func_8001540C(0, WEAPON_SOUND_FIRE, arg0);
    arg0->unk5 = 0;
    arg0->state++;
    rising_fire_charged_draw(arg0);
}
#endif

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
