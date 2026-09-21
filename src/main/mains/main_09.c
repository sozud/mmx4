// MainObj, main_object_update_funcs[9]
// 80048DD0..800498C8
#include "common.h"

void func_80048DD0(struct MainObj* arg0)
{
    D_800FAEA0[arg0->unk6](arg0);
}

void func_80048E0C(struct MainObj* arg0)
{
    struct VisualObj* visual;

    arg0->unk6++;
    func_80015D60(arg0, 0xC);
    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 6;
        visual->unk50 = PLAYER_OBJECT(arg0);
        visual->unk2 = 2;
    }
}

void func_80048E70(struct MainObj* arg0)
{
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        func_8001540C(2, 0x1E, arg0);
        shot = find_free_shot_obj();
        if (shot != NULL) {
            arg0->animation_step.fields.event = 0;
            shot->active = 0x41;
            shot->id = 3;
            shot->unk2 = 0;
            shot->unk7C = WEAPON_OBJECT(arg0);
        }
    }
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
}

void func_80048EF8(struct MainObj* arg0)
{
    D_800FAEB4[arg0->unk6](arg0);
}

void func_80048F34(struct MainObj* arg0)
{
    struct VisualObj* visual;

    arg0->unk6++;
    func_80015D60(arg0, 0x12);
    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 6;
        visual->unk50 = PLAYER_OBJECT(arg0);
        visual->unk2 = 2;
    }
}

void func_80048F98(struct MainObj* arg0)
{
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event >= 2) {
        func_8001540C(2, 0x1E, arg0);
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 3;
            shot->unk2 = arg0->animation_step.fields.event;
            shot->unk7C = WEAPON_OBJECT(arg0);
            arg0->animation_step.fields.event = 0;
        }
    }
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
}

void func_80049028(struct MainObj* arg0)
{
    D_800FAEBC[arg0->unk6](arg0);
}

void func_80049064(struct MainObj* arg0)
{
    func_80036AE4(0x14, g_Player.unk15);
    arg0->unk7 = 1;
    arg0->unk7C = 0x7F;
    arg0->unk7E = 0x19;
    arg0->ext.main_9.object_id = 0x19;
    arg0->unk6++;
    func_8002B318(BASE_OBJECT(arg0), 0x90, 0x90);
}

void func_800490D4(struct MainObj* arg0)
{
    struct EffectObj* effect;
    s8 var_a0;

    if (--arg0->unk7C == 0) {
        arg0->unk6++;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x1A;
            effect->x_pos.i.hi = arg0->x_pos.i.hi;
            effect->y_pos.i.hi = arg0->y_pos.i.hi;
            arg0->ext.main_9.effect = effect;
        }
    }
    func_8002B318(BASE_OBJECT(arg0), 0x90, 0x90);
    if (arg0->unk7E-- == 0) {
        arg0->ext.main_9.object_id -= 5;
        var_a0 = arg0->ext.main_9.object_id;
        arg0->unk42 ^= 0x8000;
        if (var_a0 < 5) {
            var_a0 = 5;
        }
        arg0->unk7E = var_a0;
    }
}

void func_800491BC(struct MainObj* self)
{
    struct MiscObj* misc;
    s8* data;
    u16 timer;

    data = (s8*)self->ext.main_9.effect;
    self->on_screen = 0;
    if (data[0] != 0) {
        if (data[7] == 0) {
            timer = self->unk7E;
            self->unk7E = timer - 1;
            if (timer == 0) {
                self->unk7E = 5;
                self->unk42 = self->unk42 ^ 0x8000;
            }
            func_8002B318(BASE_OBJECT(self), 0x90, 0x90);
            return;
        }
        self->unk7 = -0x80;
        return;
    }
    misc = find_free_misc_obj();
    if (misc != 0) {
        misc->active = 0x41;
        misc->id = 0x2E;
        misc->state = 0;
    }
    func_80036AE4(0x14, 0x40);
    ZeroObjectState(OBJECT_HEADER(self));
}

void func_80049288(struct MainObj* arg0)
{
    D_800FAEC4[arg0->unk6](arg0);
}

void func_800492C4(struct MainObj* arg0)
{
    s32 x_pos;
    u8 frame;

    arg0->unk6++;
    func_80015D60(arg0, 0xA);
    x_pos = arg0->x_pos.i.hi;
    arg0->unk20 = x_pos;
    frame = arg0->animation_step.fields.frame_index;
    if (frame >= 0x1C && frame <= 0x1D) {
        arg0->x_pos.i.hi = (arg0->unk15 != 0) ? x_pos - 0x16 : x_pos + 0x16;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_09", func_8004932C);

void func_800493F8(struct MainObj* self)
{
    s8 timer;

    D_800FAED0[self->unk6](self);
    func_8002D9BC(self);
    if (self->ext.main_9.animation_timer != 0) {
        self->unk50 = self->ext.main_9.animation_1;
        func_8002D9BC(self);
        self->unk50 = self->ext.main_9.animation_2;
    }

    timer = self->unk61;
    if (timer != 0) {
        self->unk61 = timer - 1;
        self->unk42 = (timer & 2) ? self->unk42 | 0x8000
                                  : self->unk42 & 0x7FFF;
        if (self->unk61 == 0) {
            self->unk42 &= 0x7FFF;
        }
    }
    func_8002B318(BASE_OBJECT(self), 0x90, 0x90);
}

void func_800494E0(struct MainObj* arg0)
{
    struct EffectObj* effect;

    effect = find_free_effect_obj();
    if (effect != NULL) {
        effect->active = 1;
        effect->id = 0x18;
        effect->x_pos.u.hi = arg0->x_pos.u.hi;
        effect->y_pos.u.hi = arg0->y_pos.u.hi;
        arg0->ext.main_9.effect = effect;
    }
    arg0->unk15 = 0x40;
    arg0->unk6++;
    func_80036AE4(0x15, 0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_09", func_8004955C);

void func_80049654(struct MainObj* arg0)
{
    if (arg0->unk7E != 0) {
        arg0->unk7E--;
    } else {
        func_8002B694(ANIMATED_OBJECT(arg0));
    }

    if (arg0->animation_step.fields.event != 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }

    if (arg0->y_pos.i.hi < 0x90) {
        func_80028BAC(-1, 4, 2);
        arg0->x_pos.i.hi = 0x1240;
        arg0->unk24 = FIXED(-2.5);
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk2C = 0;
        arg0->unk15 = 0;
        arg0->unk7E = 0x78;
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_09", func_8004970C);

void func_800497FC(struct MainObj* arg0)
{
    if (arg0->unk5C < 0x30) {
        if (--arg0->unk7E == 0) {
            func_8001540C(0, 0xE, NULL);
            arg0->unk7E = 3;
        }
        arg0->unk5C++;
    } else {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        func_80036B18();
    }
}

void func_80049884(struct MainObj* arg0)
{
    D_800FAED8[arg0->unk6](arg0);
}

void func_800498C0(struct MainObj* arg0)
{
}
