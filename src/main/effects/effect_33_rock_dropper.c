// EffectObj, effect_object_update_funcs[33]
// 800BC748..800BCE48
#include "common.h"
#include "main/effects/effect_33_rock_dropper.h"
#include "main/objects.h"

// rock_dropper_state_funcs
extern void (*rock_dropper_state_funcs[])(struct EffectObj*);

void rock_dropper_idle(struct EffectObj*);
#include "weapon_resources.h"

void rock_dropper_update(struct EffectObj* self)
{
    rock_dropper_state_funcs[self->state](self);
}

// rock_dropper_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800BC784(struct EffectObj* arg0);
static void effect_33_spawn_dropper(struct EffectObj* arg0);
void func_800BC92C(struct EffectObj* arg0);
static void effect_33_spawn_dropper(struct EffectObj* arg0)
{
    struct ShotObj* shot = find_free_shot_obj();

    if (shot == NULL)
        return;
    shot->active = 0x41;
    shot->id = 0x21;
    shot->unk2 = arg0->ext.effect_33.variant;
    shot->x_pos.i.hi = arg0->x_pos.i.hi;
    shot->state = 6;
    shot->unk84.effect = arg0;
    shot->unk6 = arg0->unk6;
    arg0->unk6 = 1;
}
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/effects/effect_33_rock_dropper", func_800BC784);
#else
void func_800BC784(struct EffectObj* arg0)
{

    switch (arg0->unk2 & 0xF0) {
    case 0x00:
        if (g_Player.x_pos.i.hi > arg0->x_pos.i.hi) {
            arg0->ext.effect_33.timer = 1;
            arg0->ext.effect_33.period = 0x50;
            arg0->state = 1;
        }
        return;
    case 0x10:
        arg0->ext.effect_33.timer = 0x3C;
        arg0->ext.effect_33.period = 0x26;
        arg0->ext.effect_33.cooldown = 0x8C;
        arg0->ext.effect_33.burst = 4;
        arg0->state = 1;
        arg0->unk5 = 0;
        arg0->ext.effect_33.variant = arg0->unk2 & 0xF;
        return;
    case 0x20:
        switch (arg0->unk2 & 0xF) {
        case 0:
            arg0->ext.effect_33.timer = 1;
            arg0->ext.effect_33.period = 0x3C;
            arg0->ext.effect_33.proximity = 0;
            arg0->ext.effect_33.variant = 0;
            break;
        case 1:
            arg0->ext.effect_33.timer = 1;
            arg0->ext.effect_33.period = 0x50;
            arg0->ext.effect_33.proximity = 0;
            arg0->ext.effect_33.variant = 0;
            break;
        case 2:
            arg0->ext.effect_33.timer = 1;
            arg0->ext.effect_33.period = 0x64;
            arg0->ext.effect_33.proximity = 0;
            arg0->ext.effect_33.variant = 0;
            break;
        case 3:
            arg0->ext.effect_33.timer = 0xB4;
            arg0->ext.effect_33.period = 0xB4;
            arg0->ext.effect_33.proximity = 1;
            arg0->ext.effect_33.variant = 0;
            break;
        case 4:
            arg0->ext.effect_33.timer = 1;
            arg0->ext.effect_33.period = 0x78;
            arg0->ext.effect_33.proximity = 0;
            arg0->ext.effect_33.variant = 1;
            break;
        case 5:
            arg0->ext.effect_33.timer = 1;
            arg0->ext.effect_33.period = 0xB4;
            arg0->ext.effect_33.proximity = 0;
            arg0->ext.effect_33.variant = 1;
            break;
        case 6:
            arg0->ext.effect_33.timer = 0x3C;
            arg0->ext.effect_33.period = 0x3C;
            arg0->ext.effect_33.proximity = 1;
            arg0->ext.effect_33.variant = 0;
            break;
        case 7:
            arg0->ext.effect_33.timer = 1;
            arg0->ext.effect_33.period = 0x78;
            arg0->ext.effect_33.proximity = 0;
            arg0->ext.effect_33.variant = 2;
            break;
        case 8:
            arg0->ext.effect_33.timer = 1;
            arg0->ext.effect_33.period = 0xB4;
            arg0->ext.effect_33.proximity = 0;
            arg0->ext.effect_33.variant = 2;
            break;
        }
        arg0->state = 1;
        arg0->unk6 = 0;
        return;
    }
}
#endif

// rock_dropper_drop
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800BC92C(struct EffectObj* arg0)
{
    struct Effect33Ext* ext = &arg0->ext.effect_33;
    struct ShotObj* shot;
    s32 x;
    s32 player_x;
    s32 bg_x;
    s32 distance;

    switch (arg0->unk2 & 0xF0) {
    case 0x00:
        if (arg0->x_pos.i.hi + 0x3B0 < g_Player.x_pos.i.hi) {
            arg0->state = 2;
            return;
        }
        if (--ext->timer != 0)
            return;
        ext->timer = ext->period;
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x21;
            shot->unk2 = 0;
            shot->state = 0;
        }
        return;

    case 0x10:
        if (ext->variant == 0) {
            if (arg0->x_pos.i.hi + 0x4C0 < g_Player.x_pos.i.hi) {
                arg0->state = 2;
                return;
            }
        } else if (arg0->x_pos.i.hi - g_Player.x_pos.i.hi < 0x181) {
            arg0->state = 3;
            return;
        }
        switch (arg0->unk5) {
        case 0:
            if (ext->variant == 0) {
                if (g_Player.x_pos.i.hi - arg0->x_pos.i.hi < 0x181)
                    return;
                shot = find_free_shot_obj();
                if (shot != NULL) {
                    shot->active = 0x41;
                    shot->id = 0x21;
                    shot->unk15 = 0;
                }
            } else {
                if ((u32)(arg0->x_pos.i.hi - g_Player.x_pos.i.hi - 0x181) >= 0x23F)
                    return;
                shot = find_free_shot_obj();
                if (shot != NULL) {
                    shot->active = 0x41;
                    shot->id = 0x21;
                    shot->unk15 = PLAYER_FACING_RIGHT;
                }
            }
            if (shot != NULL) {
                shot->unk2 = 4 - ext->burst;
                shot->x_pos.i.hi = arg0->x_pos.i.hi;
                shot->state = 3;
                shot->y_pos.i.hi = arg0->y_pos.i.hi;
            }
            arg0->unk5 = 1;
            return;
        case 1:
            if (--ext->timer != 0)
                return;
            if (--ext->burst == 0) {
                arg0->unk5 = 2;
                return;
            }
            arg0->unk5 = 0;
            ext->timer = ext->period;
            return;
        case 2:
            if (--ext->cooldown != 0)
                return;
            ext->cooldown = 0x78;
            ext->burst = 4;
            arg0->unk5 = 0;
            ext->timer = ext->period;
            return;
        }
        return;

    case 0x20:
        x = arg0->x_pos.i.hi;
        bg_x = background_objects[g_Player.bg_offset].x_pos.i.hi;
        if (x + 0x240 - bg_x <= 0 || bg_x - (x - 0x3C0) <= 0) {
            arg0->state = 2;
            return;
        }
        if (ext->proximity == 0) {
            if (--ext->timer != 0)
                return;
            ext->timer = ext->period;
            effect_33_spawn_dropper(arg0);
            return;
        }
        player_x = g_Player.x_pos.i.hi;
        distance = player_x - x;
        if (distance < 0)
            distance = x - player_x;
        if (distance >= 0x20) {
            ext->timer = ext->period;
            return;
        }
        if (--ext->timer != 0)
            return;
        effect_33_spawn_dropper(arg0);
        return;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/effects/effect_33_rock_dropper", func_800BC92C);
#endif

void rock_dropper_despawn(struct EffectObj* self)
{
    switch (self->unk2 & 0xF0) {
    case 0:
        if (self->backref != NULL) {
            despawn_object_permanently(OBJECT_HEADER(self));
        } else {
            ZeroObjectState(OBJECT_HEADER(self));
        }
        break;
    case 0x10:
        if (self->backref != NULL) {
            despawn_object_permanently(OBJECT_HEADER(self));
        } else {
            ZeroObjectState(OBJECT_HEADER(self));
        }
        break;
    case 0x20:
        if (self->backref != NULL) {
            despawn_object(OBJECT_HEADER(self));
        } else {
            ZeroObjectState(OBJECT_HEADER(self));
        }
        break;
    }
}

void rock_dropper_idle(struct EffectObj* self)
{
}

void (*rock_dropper_state_funcs[])(struct EffectObj*) = {
    func_800BC784,
    func_800BC92C,
    rock_dropper_despawn,
    rock_dropper_idle,
};
