// MainObj, main_object_update_funcs[46]
// 80066A48..80066DAC
#include "common.h"
#include "func_tables.h"

void train_boss_turret_update(struct MainObj* self)
{
    train_boss_turret_state_funcs[self->state](self);
}

void train_boss_turret_init(struct MainObj* self)
{
    self->hp = 0x20;
    self->unk5D = 0x20;
    self->contact_damage = 4;
    self->collision_data = (const u16*)D_80106670;
    self->x_speed = FIXED(1);
    self->unk16 = 3;
    self->hurt_box = train_boss_turret_hurt_box;
    self->attack_box = train_boss_turret_attack_box;
    self->state = 1;
    self->invincibility_timer = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->terrain_box = NULL;
    self->unk15 = 0;
    self->unk5 = 2;
    self->unk6 = 0;
}

void train_boss_turret_main(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    train_boss_turret_step_funcs[self->unk5](self);
    func_8002D9BC(self);

    if (func_8002DD04(self) < 0) {
        goto hit;
    }
    if ((self->ext.main_46.owner->attack_flags & 7) != 7) {
        goto active;
    }

hit:
    self->x_pos.i.hi = (u16)self->x_pos.i.hi - 0x54;
    self->y_pos.i.hi = (u16)self->y_pos.i.hi - 0x5B;
    spawn_explosion(BASE_OBJECT(self));
    spawn_debris(6, train_boss_turret_debris, self);
    self->x_pos.i.hi = (u16)self->x_pos.i.hi + 0x54;
    self->y_pos.i.hi = (u16)self->y_pos.i.hi + 0x5B;
    self->unk42 &= 0x7FFF;
    set_animation(self, 0xE);
    self->ext.main_46.owner->attack_flags |= 8;
    self->state = 2;
    return;

active:
    if (self->unk42 & 0x8000) {
        self->ext.main_46.owner->layer_signals->collision_state = 2;
    }
    update_on_screen(BASE_OBJECT(self), 0x100, 0x100);
}

void train_boss_turret_destroyed(struct MainObj* self)
{
    update_on_screen(BASE_OBJECT(self), 0x100, 0x100);
}

void train_boss_turret_start_idle(struct MainObj* self)
{
    self->unk5 = 3;
    self->unk6 = 0;
}

void train_boss_turret_arrive(struct MainObj* self)
{
    if (self->unk6 == 0) {
        if (self->x_pos.i.hi >= 0x1AA1) {
            self->unk7C = 0x78;
            self->unk5 = 3;
            self->unk6 = 0;
            return;
        }
        move_object(MOVING_OBJECT(self));
    }
}

void train_boss_turret_fire(struct MainObj* self)
{
    struct ShotObj* shot;

    if (self->ext.main_46.owner->projectile_command == 3) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x18;
            shot->unk2 = 0;
            shot->unk40 = self->unk40;
            shot->unk42 = self->unk42;
            shot->animation_table = (u32**)self->animation_table;
            shot->unk3C = (void*)self->sprite_frames;
            shot->bg_offset = (u8)self->bg_offset;
            shot->x_pos.i.hi = (u16)self->x_pos.i.hi - 0x2D;
            shot->y_pos.i.hi = (u16)self->y_pos.i.hi - 0x5D;
            shot->unk15 = 0;
            shot->unk7C = (struct WeaponObj*)self->ext.main_46.owner;
            shot->state = 0;
        }
        set_animation(self, 0xD);
        self->ext.main_46.owner->projectile_command = 0x80;
    }
}

u8 train_boss_turret_hurt_box[4] = { 0xA1, 0x94, 0x2A, 0x23 };

u8 train_boss_turret_attack_box[4] = { 0xA1, 0x9A, 0x24, 0x1C };

char train_boss_turret_debris[8] = "\t\n\t\n\t\n";

void (*train_boss_turret_state_funcs[])(struct MainObj*) = {
    train_boss_turret_init,
    train_boss_turret_main,
    train_boss_turret_destroyed,
};

void (*train_boss_turret_step_funcs[4])(struct MainObj*) = {
    (void (*)(struct MainObj*))enemy_hit_reaction,
    train_boss_turret_start_idle,
    train_boss_turret_arrive,
    train_boss_turret_fire,
};
