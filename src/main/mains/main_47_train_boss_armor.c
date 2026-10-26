// MainObj, main_object_update_funcs[47]
// 80066DAC..80067350
#include "common.h"
#include "main/mains/main_47_train_boss_armor.h"
#include "main/visuals/visual_08_ice_shard.h"
#include "main/object_motion.h"
#include "main/collision_bounds.h"
#include "main/objects.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1E1BC.h"
#include "main/collision_bounds.h"
#include "main/objects.h"
#endif

// train_boss_armor_step_funcs
void train_boss_armor_start_idle(struct MainObj* arg0);
void train_boss_armor_arrive(struct MainObj* arg0);

extern void (*train_boss_armor_state_funcs[])(struct MainObj*);

extern u16 train_boss_armor_smoke_offsets[3][2];

extern s8 train_boss_armor_hurt_boxes[3][16];
extern void (*train_boss_armor_step_funcs[3])(struct MainObj*);
#if defined(MMX4_PC) || defined(MMX4_SATURN)
extern u8 D_800FF9FC[4], D_800FFA00[4], D_800FFA04[8];
#endif

void train_boss_armor_update(struct MainObj* self)
{
    train_boss_armor_state_funcs[self->state](self);
}

// train_boss_armor_init
#if defined(MMX4_PC) || defined(MMX4_SATURN)
ret_s8 func_8002DD04(struct MainObj* object);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80066DE8(struct MainObj* self);
void func_80066F1C(struct MainObj* self);
#endif

void func_80066DE8(struct MainObj* self)
{
    struct ShotObj* shot;

    self->hp = 0x10;
    self->unk5D = 0x10;
    self->contact_damage = 2;
    self->collision_data = D_80107678;
    self->invincibility_timer = 0;
    self->x_speed = FIXED(1);
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
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
        shot->unk7C = (struct WeaponObj*)self->ext.main_47.train_boss;
        shot->state = 3;
    }
    self->state = 1;
    self->unk5 = 2;
    self->unk6 = 0;
}

// train_boss_armor_main
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_47_train_boss_armor", func_80066F1C);
#else
extern u8 D_800FF9FC[4], D_800FFA00[4], D_800FFA04[8];
void func_80066F1C(struct MainObj* self)
{
    s32 collision;
    u16* x_offsets;
    u16* y_offsets;
    s32 unused[2];

    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    train_boss_armor_step_funcs[self->unk5](self);
    if (self->invincibility_timer == 0) {
#ifdef VERSION_JP
        if (self->ext.main_47.train_boss->unk8A - 8 < g_Player.x_pos.i.hi
            && ((self->ext.main_47.train_boss->unk87 & D_800FF9FC[self->unk2]) || (self->ext.main_47.train_boss->attack_flags & D_800FFA00[self->unk2]))) {
#else
        if ((self->ext.main_47.train_boss->unk87 & D_800FF9FC[self->unk2]) || (self->ext.main_47.train_boss->attack_flags & D_800FFA00[self->unk2])) {
#endif
            collision = func_8002DD04(self);
            if (collision < 0) {
                self->x_pos.i.hi += train_boss_armor_smoke_offsets[self->unk2][0];
                x_offsets = train_boss_armor_smoke_offsets[0];
                y_offsets = x_offsets + 1;
                self->y_pos.i.hi += y_offsets[self->unk2 * 2];
                spawn_debris(6, D_800FFA04, self);
                spawn_explosion(BASE_OBJECT(self));
                self->x_pos.i.hi -= x_offsets[self->unk2 * 2];
                self->y_pos.i.hi -= y_offsets[self->unk2 * 2];
                *self->ext.main_47.boss_hp -= (u8)self->unk5D - (u8)self->hp;
                self->ext.main_47.train_boss->attack_flags |= D_800FF9FC[self->unk2];
                self->ext.main_47.train_boss->attack_flags |= D_800FFA00[self->unk2];
                if ((self->ext.main_47.train_boss->attack_flags & 7) == 7) {
                    g_Player.spike_immune = 1;
                    self->on_screen = 0;
                    self->state = 3;
                } else {
                    self->unk7C = 0xB4;
                    self->unk7E = 1;
                    self->on_screen = 0;
                    self->state = 2;
                }
                return;
            }
            if (collision != 0)
                self->invincibility_timer = 2;
            if (collision == 0x7F) {
                *(u8*)&self->ext.main_47.unk88 = 1;
            } else {
                *(u8*)&self->ext.main_47.unk88 = 0;
                if (self->unk42 & 0x8000)
                    self->ext.main_47.train_boss->layer_signals->unk16 = 1;
            }
            *self->ext.main_47.boss_hp -= (u8)self->unk5D - (u8)self->hp;
            self->unk5D = self->hp;
        }
    } else {
        self->invincibility_timer--;
        if (*(u8*)&self->ext.main_47.unk88 == 0)
            self->ext.main_47.train_boss->layer_signals->unk16 = 1;
    }
    update_on_screen(BASE_OBJECT(self), 0x100, 0x100);
}
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
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
