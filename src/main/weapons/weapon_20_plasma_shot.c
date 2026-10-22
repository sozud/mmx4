#include "common.h"
#include "main/weapons/weapon_00_lemon.h"
#include "main/weapons/weapon_09_charge_shot.h"
#include "main/weapons/weapon_20_plasma_shot.h"
#include "main/55C4.h"
#include "main/objects.h"
#include "main/weapons/weapon_22_nova_strike_hitbox.h"

#ifdef MMX4_PC
#include "main/object_motion.h"
#include "main/sprite_animations.h"
#endif

// plasma_shot_state_funcs
extern void (*plasma_shot_state_funcs[])(struct WeaponObj*);

void plasma_shot_main(struct WeaponObj*);

void plasma_orb_linger(struct WeaponObj*);

void plasma_shot_update(struct WeaponObj* arg0)
{
    plasma_shot_state_funcs[arg0->state](arg0);
}

// plasma_shot_init
#ifdef MMX4_PC
void func_800929DC(struct WeaponObj* self);
void func_80092B5C(struct WeaponObj* self);
extern struct Unk_unk68 D_8010871C[];
extern struct Unk_unk68 D_80108720[];
#endif

#ifdef MMX4_PC
void func_800929DC(struct WeaponObj* self)
{
    self->on_screen = 1;
    self->animation_table = D_8011BF40;
    self->unk42 = 0x7802;
    self->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 12);
    self->unk40 = 0;
    if (self->id == 0x14) {
        self->unk16 = 0;
        self->unk50 = D_8010871C;
        self->unk64 = 1;
        self->x_vel.val = self->unk15 ? 0xB0000 : -0xB0000;
        set_animation(self, 0x1D);
    } else {
        self->unk50 = D_80108720;
        self->unk64 = 2;
        self->ext.weapon_20.lifetime = 0x5A;
        self->unk16 = 1;
        self->x_vel.val = 0;
        self->ext.weapon_20.timer = 4;
        set_animation(self, 0x1E);
    }
    self->unk28.val = 0;
    self->y_vel.val = 0;
    self->unk2C = 0;
    self->unk5 = 0;
    self->state++;
    update_on_screen(BASE_OBJECT(self), 0x2A, 0x22);
}
#else
INCLUDE_ASM("main/nonmatchings/weapons/weapon_20_plasma_shot", func_800929DC);
#endif

void plasma_shot_main(struct WeaponObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x2A, 0x22) == 0) {
        animate_object(ANIMATED_OBJECT(arg0));
        if (arg0->id == 0x14) {
            func_80092B5C(arg0);
            return;
        }
        plasma_orb_linger(arg0);
        return;
    }
    buster_shot_hide(arg0);
}

// plasma_shot_move
#ifdef MMX4_PC
void func_80092B5C(struct WeaponObj* self)
{
    struct WeaponObj* child;

    move_object(MOVING_OBJECT(self));
    if (self->unk98 != 0) {
        self->unk98 = 0;
        if (g_Player.shot_count < 4) {
            child = find_free_weapon_obj();
            if (child != NULL) {
                child->active = 0x21;
                child->id = 0x15;
                child->unk2 = 0;
                child->bg_offset = self->bg_offset;
                child->x_pos = self->x_pos;
                child->y_pos = self->y_pos;
                child->unk15 = self->unk15;
                g_Player.shot_count++;
            }
        }
    }
    update_on_screen(BASE_OBJECT(self), 0x2A, 0x22);
}
#else
INCLUDE_ASM("main/nonmatchings/weapons/weapon_20_plasma_shot", func_80092B5C);
#endif

void plasma_orb_linger(struct WeaponObj* arg0)
{
    u8 timer;
    u8 sub_timer;

    if (arg0->unk5 == 0) {
        struct Weapon20Ext* ext = &arg0->ext.weapon_20;

        timer = arg0->ext.weapon_20.lifetime;
        if (timer == 0) {
            set_animation(arg0, 0x1F);
            arg0->unk50 = 0;
            arg0->unk5 = 1;
        } else {
            ext->lifetime = timer - 1;
            sub_timer = ext->timer;
            if (sub_timer == 0) {
                ext->timer = 4;
                arg0->unk64 = (u8)arg0->unk64 + 1;
            } else {
                ext->timer = sub_timer - 1;
            }
        }
    } else if (arg0->animation_step.fields.relative_step == 0) {
        buster_shot_hide(arg0);
        return;
    }

    update_on_screen(BASE_OBJECT(arg0), 0x2A, 0x22);
}

void buster_shot_follow_muzzle(struct WeaponObj* arg0)
{
    struct PlayerObj* owner;

    if (arg0->unk84.word == 0) {
        owner = arg0->owner;
        if (owner->attacking == 0) {
            arg0->unk84.word = 1;
        }
        if (owner->unk15 != arg0->unk15) {
            arg0->unk84.word = 1;
        }
        if (arg0->unk84.word == 0) {
            buster_shot_place_at_muzzle(VISUAL_OBJECT(arg0), owner, arg0->id);
        }
    }
}

void (*plasma_shot_state_funcs[])(struct WeaponObj*) = {
    func_800929DC,
    plasma_shot_main,
    player_shot_despawn,
    player_shot_despawn,
};
