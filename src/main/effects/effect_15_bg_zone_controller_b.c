// EffectObj, effect_object_update_funcs[15]
// 800B8AF8..800B8F5C
#include "common.h"
#include "main/effects/effect_15_bg_zone_controller_b.h"

// bg_zone_controller_b_state_funcs
extern void (*bg_zone_controller_b_state_funcs[])(struct EffectObj*);
void bg_zone_controller_b_init(struct EffectObj*);
void bg_zone_controller_b_main(struct EffectObj*);

// bg_zone_controller_b_zone_funcs
extern void (*bg_zone_controller_b_zone_funcs[])(struct EffectObj*);
void bg_zone_controller_b_zone_0(struct EffectObj*);
void bg_zone_controller_b_zone_1(struct EffectObj*);
void bg_zone_controller_b_zone_2(struct EffectObj*);
void bg_zone_controller_b_zone_3(struct EffectObj*);
void bg_zone_controller_b_zone_4(struct EffectObj*);
void bg_zone_controller_b_zone_5(struct EffectObj*);
void bg_zone_controller_b_idle(struct EffectObj*);
void bg_zone_controller_b_zone_0_enter(struct EffectObj*);
void bg_zone_controller_b_zone_0_done(struct EffectObj*);
void bg_zone_controller_b_zone_1_enter(struct EffectObj*);
void bg_zone_controller_b_zone_1_done(struct EffectObj*);
void bg_zone_controller_b_zone_2_enter(struct EffectObj*);
void bg_zone_controller_b_zone_2_done(struct EffectObj*);
void bg_zone_controller_b_zone_3_enter(struct EffectObj*);
void bg_zone_controller_b_zone_3_done(struct EffectObj*);
void bg_zone_controller_b_zone_4_enter(struct EffectObj*);
void bg_zone_controller_b_zone_4_done(struct EffectObj*);
void bg_zone_controller_b_zone_5_enter(struct EffectObj*);
void bg_zone_controller_b_zone_5_done(struct EffectObj*);

void bg_zone_controller_b_update(struct EffectObj* self)
{
    bg_zone_controller_b_state_funcs[self->state](self);
}

void bg_zone_controller_b_init(struct EffectObj* self)
{
    self->unk5 = 1;
    self->ext.effect_15.unk14 = 6;
    self->state++;
    bg_zone_controller_b_main(self);
}

void bg_zone_controller_b_main(struct EffectObj* self)
{
    self->ext.effect_15.unk15 = self->ext.effect_15.unk14;
    func_800B8E74(self);
    bg_zone_controller_b_zone_funcs[self->unk5](self);
}

void bg_zone_controller_b_zone_0(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_b_zone_0_enter(self);
    } else {
        bg_zone_controller_b_zone_0_done(self);
    }
}

void bg_zone_controller_b_zone_0_enter(struct EffectObj* self)
{
    background_objects[0].unk2E = 0xC0;
    self->unk6++;
}

void bg_zone_controller_b_zone_0_done(struct EffectObj* self)
{
    self->unk5 = 6;
    self->unk6 = 0;
}

void bg_zone_controller_b_zone_1(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_b_zone_1_enter(self);
    } else {
        bg_zone_controller_b_zone_1_done(self);
    }
}

void bg_zone_controller_b_zone_1_enter(struct EffectObj* self)
{
    background_objects[0].unk2E = 0x80;
    self->unk6++;
}

void bg_zone_controller_b_zone_1_done(struct EffectObj* self)
{
    self->unk5 = 6;
    self->unk6 = 0;
}

void bg_zone_controller_b_zone_2(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_b_zone_2_enter(self);
    } else {
        bg_zone_controller_b_zone_2_done(self);
    }
}

void bg_zone_controller_b_zone_2_enter(struct EffectObj* self)
{
    background_objects[0].unk2E = 0xC0;
    self->unk6++;
}

void bg_zone_controller_b_zone_2_done(struct EffectObj* self)
{
    self->unk5 = 6;
    self->unk6 = 0;
}

void bg_zone_controller_b_zone_3(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_b_zone_3_enter(self);
    } else {
        bg_zone_controller_b_zone_3_done(self);
    }
}

void bg_zone_controller_b_zone_3_enter(struct EffectObj* self)
{
    background_objects[0].unk2E = 0x70;
    background_objects[0].unk24 = 0x1660;
    self->unk6++;
}

void bg_zone_controller_b_zone_3_done(struct EffectObj* self)
{
    self->unk5 = 6;
    self->unk6 = 0;
}

void bg_zone_controller_b_zone_4(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_b_zone_4_enter(self);
    } else {
        bg_zone_controller_b_zone_4_done(self);
    }
}

void bg_zone_controller_b_zone_4_enter(struct EffectObj* self)
{
    background_objects[0].unk2E = 0xC0;
    self->unk6++;
}

void bg_zone_controller_b_zone_4_done(struct EffectObj* self)
{
    self->unk5 = 6;
    self->unk6 = 0;
}

void bg_zone_controller_b_zone_5(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_b_zone_5_enter(self);
    } else {
        bg_zone_controller_b_zone_5_done(self);
    }
}

void bg_zone_controller_b_zone_5_enter(struct EffectObj* self)
{
#ifdef MMX4_SATURN
    background_objects[2].unk4A = 4;
#else
    background_objects[2].unk4A = 9;
#endif
    self->unk6++;
}

void bg_zone_controller_b_zone_5_done(struct EffectObj* self)
{
    self->unk5 = 6;
    self->unk6 = 0;
}

void bg_zone_controller_b_idle(struct EffectObj* self)
{
}

// bg_zone_controller_b_update_zone

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800B8E74(struct EffectObj* arg0);
extern u16 bg_zone_controller_b_zone_bounds[6];
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800B8E74(struct EffectObj* arg0)
{
    s8 index;

    if (g_Player.y_pos.i.hi < 0x500) {
        for (index = 0; index < 2; index++) {
            if (g_Player.x_pos.i.hi - (s16)bg_zone_controller_b_zone_bounds[index] < 0)
                break;
        }
        if (index == 2)
            index = 1;
    } else {
        for (index = 2; index < 5; index++) {
            if (g_Player.x_pos.i.hi - (s16)bg_zone_controller_b_zone_bounds[index] < 0)
                break;
        }
    }
    arg0->ext.effect_15.unk14 = index;
    if (index != arg0->ext.effect_15.unk15) {
        arg0->unk5 = index;
        arg0->unk6 = 0;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/effects/effect_15_bg_zone_controller_b", func_800B8E74);
#endif

u16 bg_zone_controller_b_zone_bounds[6] = { 0x0760, 0x0BA0, 0x13F0, 0x1700, 0x1775, 0 };

void (*bg_zone_controller_b_state_funcs[])(struct EffectObj*) = {
    bg_zone_controller_b_init,
    bg_zone_controller_b_main,
};

void (*bg_zone_controller_b_zone_funcs[7])(struct EffectObj*) = {
    bg_zone_controller_b_zone_0,
    bg_zone_controller_b_zone_1,
    bg_zone_controller_b_zone_2,
    bg_zone_controller_b_zone_3,
    bg_zone_controller_b_zone_4,
    bg_zone_controller_b_zone_5,
    bg_zone_controller_b_idle,
};
