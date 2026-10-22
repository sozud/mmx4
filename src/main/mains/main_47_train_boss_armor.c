// MainObj, main_object_update_funcs[47]
// 80066DAC..80067350
#include "common.h"
#include "main/mains/main_47_train_boss_armor.h"
#include "main/visuals/visual_08_ice_shard.h"
#include "main/object_motion.h"

#ifdef MMX4_PC
#include "main/1E1BC.h"
#include "main/collision_bounds.h"
#include "main/objects.h"
#endif

// train_boss_armor_step_funcs
void train_boss_armor_start_idle(struct MainObj* arg0);
void train_boss_armor_arrive(struct MainObj* arg0);

extern void (*train_boss_armor_state_funcs[])(struct MainObj*);

extern u16 train_boss_armor_smoke_offsets[3][2];

#ifdef MMX4_PC
extern s8 train_boss_armor_hurt_boxes[3][16];
extern u8 D_800FF9FC[4], D_800FFA00[4], D_800FFA04[8];
extern void (*train_boss_armor_step_funcs[3])(struct MainObj*);
#endif

void train_boss_armor_update(struct MainObj* self)
{
    train_boss_armor_state_funcs[self->state](self);
}

// train_boss_armor_init
#ifdef MMX4_PC
void func_80066DE8(struct MainObj* self);
void func_80066F1C(struct MainObj* self);
#endif

#ifdef MMX4_PC
// src/main/mains/main_47_train_boss_armor.c

void func_80066DE8(struct MainObj* self)
{
    struct ShotObj* shot;

    self->hp = self->unk5D = 0x10;
    self->collision_data = D_80107678;
    self->contact_damage = 2;
    self->invincibility_timer = 0;
    self->x_speed = FIXED(1);
    self->y_speed = self->x_accel = self->gravity = 0;
    self->air_state = 0;
    self->unk16 = 3;
    self->terrain_box = NULL;
    self->attack_box = NULL;
    self->hurt_box = (u8*)train_boss_armor_hurt_boxes[self->unk2];
    self->unk15 = 0;
    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x18;
        shot->unk2 = self->unk2;
        shot->unk40 = self->unk40;
        shot->unk42 = self->unk42;
        shot->animation_table = (u32**)self->animation_table;
        shot->unk3C = (void*)self->sprite_frames;
        shot->bg_offset = self->bg_offset;
        shot->x_pos = self->x_pos;
        shot->y_pos = self->y_pos;
        shot->unk15 = 0;
        shot->state = 3;
        shot->unk7C = (struct WeaponObj*)self->ext.main_47.train_boss;
    }
    self->state = 1;
    self->unk5 = 2;
    self->unk6 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_47_train_boss_armor", func_80066DE8);
#endif

// train_boss_armor_main
#ifdef MMX4_PC
void func_80066F1C(struct MainObj* self)
{
    struct Main45Ext* owner = self->ext.main_47.train_boss;
    u8* reflected = (u8*)&self->ext.main_47.unk88;
    s32 subtype = self->unk2;

    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    train_boss_armor_step_funcs[self->unk5](self);
    if (self->invincibility_timer == 0) {
        s32 collision;
        if (!(owner->unk87 & D_800FF9FC[subtype]) && !(owner->attack_flags & D_800FFA00[subtype])) {
            update_on_screen(BASE_OBJECT(self), 0x100, 0x100);
            return;
        }
        collision = func_8002DD04(self);
        if (collision < 0) {
            self->x_pos.i.hi = (u16)self->x_pos.i.hi + train_boss_armor_smoke_offsets[subtype][0];
            self->y_pos.i.hi = (u16)self->y_pos.i.hi + train_boss_armor_smoke_offsets[subtype][1];
            spawn_debris(6, D_800FFA04, self);
            spawn_explosion(BASE_OBJECT(self));
            self->x_pos.i.hi = (u16)self->x_pos.i.hi - train_boss_armor_smoke_offsets[subtype][0];
            self->y_pos.i.hi = (u16)self->y_pos.i.hi - train_boss_armor_smoke_offsets[subtype][1];
            *self->ext.main_47.boss_hp = (u8)*self->ext.main_47.boss_hp - ((u8)self->unk5D - (u8)self->hp);
            owner->attack_flags |= D_800FF9FC[subtype];
            owner->attack_flags |= D_800FFA00[subtype];
            if ((owner->attack_flags & 7) == 7) {
                g_Player.spike_immune = 1;
                self->state = 3;
            } else {
                self->unk7C = 0xB4;
                self->unk7E = 1;
                self->state = 2;
            }
            self->on_screen = 0;
            return;
        }
        if (collision != 0)
            self->invincibility_timer = 2;
        if (collision == 0x7F) {
            *reflected = 1;
        } else {
            *reflected = 0;
            if (self->unk42 & 0x8000)
                owner->layer_signals->unk16 = 1;
        }
        *self->ext.main_47.boss_hp = (u8)*self->ext.main_47.boss_hp - ((u8)self->unk5D - (u8)self->hp);
        self->unk5D = self->hp;
    } else {
        self->invincibility_timer = (u8)self->invincibility_timer - 1;
        if (*reflected == 0)
            owner->layer_signals->unk16 = 1;
    }
    update_on_screen(BASE_OBJECT(self), 0x100, 0x100);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_47_train_boss_armor", func_80066F1C);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_47_train_boss_armor", train_boss_armor_smoke);
#else
void train_boss_armor_smoke(struct MainObj* self)
{
    s32 tableIndex;
    s16 x;
    s16 y;
    s32 frameArea[2];

    if (--self->unk7C == 0) {
        self->state = 3;
        return;
    }

    if (--self->unk7E == 0) {
        tableIndex = self->unk2;
        y = (u16)((struct BaseObj*)self->ext.main_47.train_boss)->x_pos.i.hi + train_boss_armor_smoke_offsets[tableIndex][0];
        x = (u16)self->y_pos.i.hi + train_boss_armor_smoke_offsets[tableIndex][1];
        func_800B10E4(0x11, (s16)(y - 6), (s16)(x - 6),
            (s16)(y + 6), (s16)(x + 6), 1);
        self->unk7E = 10;
    }
}
#endif

void train_boss_armor_clear(struct MainObj* self)
{
    self->ext.main_47.train_boss = 0;
    self->ext.main_47.boss_hp = 0;
    self->ext.main_47.unk88 = 0;
    self->ext.main_47.unk8C = 0;
    self->ext.main_47.unk90 = 0;
    self->ext.main_47.unk94 = 0;
}

void train_boss_armor_start_idle(struct MainObj* self)
{
    self->unk5 = 2;
    self->unk6 = 1;
}

void train_boss_armor_arrive(struct MainObj* self)
{
    if (self->unk6 == 0) {
        if (self->x_pos.i.hi > 0x1AA0) {
            self->unk6 = 1;
            return;
        }
        move_object(MOVING_OBJECT(self));
        return;
    }
    self->unk42 &= 0x7FFF;
}

s8 train_boss_armor_hurt_boxes[3][16] = {
    { -47, -72, 29, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { -31, -39, 17, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { -31, -6, 17, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

u16 train_boss_armor_smoke_offsets[3][2] = { { -30, -61 }, { -24, -26 }, { -23, 8 } };

u8 D_800FF9FC[4] = { 1, 2, 4, 0 };

u8 D_800FFA00[4] = { 0x10, 0x20, 0x40, 0 };

u8 D_800FFA04[8] = { 11, 12, 11, 12, 11, 12, 0, 0 };

void (*train_boss_armor_state_funcs[])(struct MainObj*) = {
    func_80066DE8,
    func_80066F1C,
    train_boss_armor_smoke,
    train_boss_armor_clear,
};

#ifdef MMX4_PC
void (*train_boss_armor_step_funcs[3])(struct MainObj*) = {
    (void (*)(struct MainObj*))enemy_hit_reaction,
    train_boss_armor_start_idle,
    train_boss_armor_arrive,
};
#else
void (*train_boss_armor_step_funcs[3])() = { enemy_hit_reaction, train_boss_armor_start_idle, train_boss_armor_arrive };
#endif
