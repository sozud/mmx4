// MainObj, main_object_update_funcs[8]
// 80047C88..800498C0
#include "common.h"
#include "func_tables.h"

void func_80047C88(struct MainObj* arg0)
{
    u8 sound_id;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    CollisionRelated(PLAYER_OBJECT(arg0));
    D_800FAE20[arg0->state](arg0);
    sound_id = arg0->ext.main_8.unk89;
    if (sound_id != 0xFF) {
        func_8001540C(2, sound_id, arg0);
        arg0->ext.main_8.unk89 = 0xFF;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_08", func_80047D04);

INCLUDE_ASM("main/nonmatchings/mains/main_08", func_80047E58);

void func_8004808C(struct MainObj* arg0)
{
    arg0->unk7C = 0x2B;
    func_80015D60(arg0, 0);
    arg0->unk5++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_08", func_800480D0);

void func_8004831C(struct MainObj* arg0)
{
    arg0->unk6++;
    func_80015D60(arg0, 0xE);
}

void func_80048348(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event == 2) {
        arg0->animation_step.fields.event = 0;
        func_8001540C(2, 0x22, arg0);
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 1) {
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    }
}

void func_800483AC(struct MainObj* arg0)
{
    D_800FAE60[arg0->unk6](arg0);
}

void func_800483E8(struct MainObj* arg0)
{
    s32 x_vel;

    x_vel = FIXED(-0.5);
    arg0->unk6++;
    if (arg0->unk15 != 0) {
        x_vel = FIXED(0.5);
    }
    arg0->unk20 = x_vel;
    arg0->unk24 = FIXED(1.5);
    func_80015D60(arg0, 2);
}

void func_80048434(struct MainObj* arg0)
{
    s32 x_vel;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_8002B718(MOVING_OBJECT(arg0));
    }
    if (arg0->animation_step.fields.event == 1) {
        func_80015D60(arg0, 4);
        x_vel = FIXED(-1.5);
        arg0->unk6++;
        if (arg0->unk15 != 0) {
            x_vel = FIXED(1.5);
        }
        arg0->unk20 = x_vel;
        arg0->unk24 = 0;
        arg0->unk50 = (const u8*)&D_800FA730;
        arg0->ext.main_8.unk88 = 0;
    }
}

void func_800484C8(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event != 0) {
        func_8002B718(MOVING_OBJECT(arg0));
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk6++;
    }
}

void func_8004852C(struct MainObj* arg0)
{
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step < 0) {
        func_80015D60(arg0, 4);
        arg0->unk6++;
    }
}

void func_80048584(struct MainObj* arg0)
{
    s32 x_vel;

    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60(arg0, 6);
        x_vel = FIXED(-0.75);
        arg0->unk6++;
        if (arg0->unk15 != 0) {
            x_vel = FIXED(0.75);
        }
        arg0->unk24 = FIXED(-1.5);
        arg0->unk50 = (const u8*)&D_800FA72C;
        arg0->unk20 = x_vel;
        arg0->ext.main_36.saved_unk5 = 1;
    }
}

void func_80048610(struct MainObj* arg0)
{
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 1) {
        func_800B0CA0(0x21, 2, arg0, 0x18, 6);
        func_800B0CA0(0x22, 2, arg0, 0x18, 6);
        func_8001540C(2, 0x18, arg0);
        func_80028BAC(0xA, 4, 2);
        arg0->animation_step.fields.event = 0;
    }
    if (arg0->unk70 & 8) {
        if (arg0->unk15 != 0) {
            if (g_Player.x_pos.val < arg0->x_pos.val) {
                arg0->unk5 = 4;
            } else {
                arg0->unk5 = 5;
            }
        } else {
            if (g_Player.x_pos.val < arg0->x_pos.val) {
                arg0->unk5 = 5;
            } else {
                arg0->unk5 = 4;
            }
        }
        arg0->unk6 = 0;
        func_800B0CA0(0x21, 2, arg0, 0x18, 6);
        func_800B0CA0(0x22, 2, arg0, 0x18, 6);
        func_8001540C(2, 0x18, arg0);
        func_80028BAC(0xA, 4, 2);
    }
}

void func_80048770(struct MainObj* arg0)
{
    D_800FAE68[arg0->unk6](arg0);
}

void func_800487AC(struct MainObj* arg0)
{
    arg0->unk24 = FIXED(0.75);
    arg0->ext.main_487.unk8A = 0;
    arg0->unk20 = 0;
    arg0->unk28 = FIXED(1.0 / 16);
    arg0->unk6++;
    func_80015D60(arg0, 2);
}

void func_800487F0(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event != 0) {
        func_8002B694(ANIMATED_OBJECT(arg0));
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 1) {
        arg0->unk24 = FIXED(3);
        func_80015D60(arg0, 4);
        arg0->unk6++;
    }
}

void func_80048864(struct MainObj* arg0)
{
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->y_pos.i.hi < 0x90) {
        if (arg0->unk15 != 0) {
            arg0->x_pos.i.hi = 0x12B0;
        } else {
            arg0->x_pos.i.hi = 0x11A0;
        }
        arg0->unk24 = FIXED(-2.5);
        arg0->unk7E = 0x3C;
        arg0->unk28 = 0;
        arg0->unk20 = 0;
        arg0->unk15 ^= 0x40;
        arg0->unk6++;
    }
}

void func_800488F4(struct MainObj* arg0)
{
    if (arg0->unk7E != 0) {
        arg0->unk7E--;
        return;
    }

    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        func_80015D60(arg0, 6);
        arg0->unk6++;
    }
}

void func_80048970(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 1) {
        func_800B0CA0(0x21, 2, arg0, 0x18, 6);
        func_800B0CA0(0x22, 2, arg0, 0x18, 6);
        func_8001540C(2, 0x18, arg0);
        func_80028BAC(0xA, 4, 2);
        arg0->animation_step.fields.event = 0;
    }
    if (arg0->animation_step.fields.event < 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
}

void func_80048A1C(struct MainObj* arg0)
{
    D_800FAE84[arg0->unk6](arg0);
}

void func_80048A58(struct MainObj* arg0)
{
    struct ShotObj* shot;
    struct VisualObj* visual;
    arg0->unk6++;
    func_80015D60(arg0, 8);
    shot = find_free_shot_obj();
    if (shot != 0) {
        shot->active = 0x41;
        shot->id = 4;
        shot->unk7C = WEAPON_OBJECT(arg0);
        shot->state = 0;
        shot->unk5 = 0;
        shot->unk6 = 0;
    }
    visual = find_free_visual_obj();
    if (visual != 0) {
        visual->active = 0x41;
        visual->id = 6;
        visual->state = 0;
        visual->unk5 = 0;
        visual->unk6 = 0;
        visual->unk50 = PLAYER_OBJECT(arg0);
        visual->unk2 = 1;
    }

    arg0->unk20 = arg0->x_pos.i.hi;
}

INCLUDE_ASM("main/nonmatchings/mains/main_08", func_80048B04);

void func_80048B98(struct MainObj* arg0)
{
    D_800FAE98[arg0->unk6](arg0);
}

void func_80048BD4(struct MainObj* arg0)
{
    s32 velocity = FIXED(3);
    arg0->unk6++;
    if (arg0->unk15 != 0) {
        velocity = FIXED(-3);
    }
    arg0->unk20 = velocity;
    arg0->unk24 = FIXED(1.5);
    func_80015D60(arg0, 2);
}

void func_80048C20(struct MainObj* arg0)
{
    s32 x_velocity;

    if (arg0->animation_step.fields.event != 0) {
        func_8002B718(MOVING_OBJECT(arg0));
    }
    if (arg0->animation_step.fields.event == 3) {
        func_8001540C(2, 0x1F, arg0);
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 1) {
        x_velocity = FIXED(-8.5);
        if (arg0->unk15 != 0) {
            x_velocity = FIXED(8.5);
        }
        arg0->unk20 = x_velocity;
        arg0->unk24 = FIXED(-4);
        arg0->unk2C = FIXED(-0.1875);
        arg0->unk28 = 0;
        arg0->unk6++;
        func_80015D60(arg0, 4);
        arg0->unk60 = 5;
        arg0->unk50 = (const u8*)&D_800FA730;
        arg0->ext.main_8.unk88 = 0;
        arg0->unk7E = 0x14;
    }
}

void func_80048CF8(struct MainObj* arg0)
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
        if (arg0->unk15 != 0) {
            arg0->x_pos.i.hi = 0x12B0;
        } else {
            arg0->x_pos.i.hi = 0x11A0;
        }
        arg0->unk24 = FIXED(-2.5);
        arg0->unk60 = 3;
        arg0->unk50 = (const u8*)&D_800FA72C;
        arg0->ext.main_8.unk88 = 1;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk2C = 0;
        arg0->unk6++;
        arg0->unk15 ^= 0x40;
    }
}

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

INCLUDE_ASM("main/nonmatchings/mains/main_08", func_8004932C);

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

void func_8004955C(struct MainObj* self)
{
    s32 x_velocity;
    struct VisualObj* visual;

    if (self->ext.main_9.effect->active == 0) {
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 6;
            visual->unk50 = PLAYER_OBJECT(self);
            visual->unk2 = 3;
        }
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 6;
            visual->unk50 = PLAYER_OBJECT(self);
            visual->unk2 = 4;
        }
        self->unk6 = (u8)self->unk6 + 1;
        func_80028BAC(-1, 4, 2);
        x_velocity = FIXED(-8.5);
        if (self->unk15 != 0) {
            x_velocity = FIXED(8.5);
        }
        self->unk24 = FIXED(-6);
        self->unk20 = x_velocity;
        self->unk28 = 0;
        self->unk2C = FIXED(-0.09375);
        func_80015D60(self, 4);
        self->unk7E = 0x14;
    }
}

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

INCLUDE_ASM("main/nonmatchings/mains/main_08", func_8004970C);

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

u32 D_800FA724 = 0x06545922;

u32 D_800FA728 = 0x5953B4E2;

u32 D_800FA72C = 0x4760B4D7;

u32 D_800FA730 = 0xA371A3E5;

u32 D_800FA734 = 0x488118EC;

u32 D_800FA738 = 0x415ADABC;

u32 D_800FA73C = 0x415ACCBC;

u32 D_800FA740 = 0x507510EE;

u32 D_800FA744 = 0x3A6626FD;

union AnimationStep D_800FA748[] = {
    { 0x00010010 },
    { 0x01010010 },
    { 0x02010010 },
    { 0x03010010 },
    { 0x04010009 },
    { 0x05010009 },
    { 0x0601000B },
    { 0x07F9010E },
};

union AnimationStep D_800FA768[] = {
    { 0x0801004B },
    { 0x09010008 },
    { 0x0A010010 },
    { 0x0BFD0108 },
};

union AnimationStep D_800FA778[] = {
    { 0x0C010008 },
    { 0x0D010010 },
    { 0x0E010301 },
    { 0x0E010207 },
    { 0x0F010207 },
    { 0x0FFC0101 },
};

union AnimationStep D_800FA790[] = {
    { 0x08010008 },
    { 0x09010008 },
    { 0x0A010008 },
    { 0x0B010008 },
    { 0x08FC0108 },
};

union AnimationStep D_800FA7A4[] = {
    { 0x10010008 },
    { 0x11010008 },
    { 0x11010208 },
    { 0x10010208 },
    { 0x0FFC0110 },
};

union AnimationStep D_800FA7B8[] = {
    { 0x09010008 },
    { 0x0B010010 },
    { 0x09010008 },
    { 0x0AFD0110 },
};

union AnimationStep D_800FA7C8[] = {
    { 0x12010010 },
    { 0x13010008 },
    { 0x14010118 },
    { 0x0C010010 },
    { 0x0CFCFF01 },
};

union AnimationStep D_800FA7DC[] = {
    { 0x09010008 },
    { 0x0B010008 },
    { 0x09010008 },
    { 0x0A010010 },
    { 0x09010008 },
    { 0x0B010008 },
    { 0x08FA0110 },
};

union AnimationStep D_800FA7F8[] = {
    { 0x0C010008 },
    { 0x15010008 },
    { 0x1601001E },
    { 0x17010005 },
    { 0x18010208 },
    { 0x18010007 },
    { 0x1B010004 },
    { 0x18010013 },
    { 0x0CF80101 },
};

union AnimationStep D_800FA81C[] = {
    { 0x08010008 },
    { 0x08010008 },
    { 0x0901001E },
    { 0x0A010005 },
    { 0x0B010008 },
    { 0x0B010007 },
    { 0x0B010004 },
    { 0x08F90114 },
};

union AnimationStep D_800FA83C[] = {
    { 0x36010008 },
    { 0x36010008 },
    { 0x3601001E },
    { 0x36010005 },
    { 0x1901FF08 },
    { 0x36010007 },
    { 0x36010004 },
    { 0x36F90114 },
};

union AnimationStep D_800FA85C[] = {
    { 0x36010008 },
    { 0x36010008 },
    { 0x3601001E },
    { 0x36010005 },
    { 0x1A010008 },
    { 0x36010007 },
    { 0x36010004 },
    { 0x36F90114 },
};

union AnimationStep D_800FA87C[] = {
    { 0x1C010003 },
    { 0x1D010003 },
    { 0x1C010003 },
    { 0x1D010003 },
    { 0x0C010105 },
    { 0x0CFB0101 },
};

union AnimationStep D_800FA894[] = {
    { 0x0A010003 },
    { 0x0A010003 },
    { 0x0A010003 },
    { 0x0A010003 },
    { 0x0AFC0106 },
};

union AnimationStep D_800FA8A8[] = {
    { 0x0C010008 },
    { 0x1E01000C },
    { 0x1F010002 },
    { 0x20010006 },
    { 0x2001002A },
    { 0x26010004 },
    { 0x20010214 },
    { 0x20010214 },
    { 0x1F010206 },
    { 0x1E01000C },
    { 0x0C010007 },
    { 0x0CF60001 },
};

union AnimationStep D_800FA8D8[] = {
    { 0x08010008 },
    { 0x09010006 },
    { 0x0A010006 },
    { 0x0B010002 },
    { 0x0B010003 },
    { 0x08010003 },
    { 0x08010052 },
    { 0x08010006 },
    { 0x08F80114 },
};

union AnimationStep D_800FA8FC[] = {
    { 0x0C010014 },
    { 0x33010014 },
    { 0x34010216 },
    { 0x35010018 },
    { 0x3401000C },
    { 0x33010004 },
    { 0x0C010007 },
    { 0x0CF90101 },
};

union AnimationStep D_800FA91C[] = {
    { 0x08010014 },
    { 0x08010014 },
    { 0x08010016 },
    { 0x08010018 },
    { 0x0801000C },
    { 0x08010004 },
    { 0x08FA0108 },
};

union AnimationStep D_800FA938[] = {
    { 0x29010004 },
    { 0x2A010004 },
    { 0x2B010004 },
    { 0x2CFD0104 },
};

union AnimationStep D_800FA948[] = {
    { 0x2D010003 },
    { 0x2E010003 },
    { 0x2F010004 },
    { 0x30010003 },
    { 0x31010004 },
    { 0x32010002 },
    { 0x32FA0001 },
};

union AnimationStep D_800FA964[] = {
    { 0x36010008 },
    { 0x3601000C },
    { 0x36010002 },
    { 0x36010006 },
    { 0x21010206 },
    { 0x22010004 },
    { 0x23010003 },
    { 0x22010004 },
    { 0x23010003 },
    { 0x21010006 },
    { 0x22010005 },
    { 0x23010004 },
    { 0x24010003 },
    { 0x25010004 },
    { 0x27010001 },
    { 0x28010001 },
    { 0x36010006 },
    { 0x3601000C },
    { 0x36EC0108 },
};

union AnimationStep D_800FA9B0[] = {
    { 0x37010001 },
    { 0x38FF0001 },
};

union AnimationStep D_800FA9B8[] = {
    { 0x0A010001 },
    { 0x0AFF0001 },
};

union AnimationStep D_800FA9C0[] = {
    { 0x0C010008 },
    { 0x1E01000C },
    { 0x1F010002 },
    { 0x20010006 },
    { 0x2001002A },
    { 0x26010002 },
    { 0x20010103 },
    { 0x26010002 },
    { 0x20010103 },
    { 0x26010002 },
    { 0x20010203 },
    { 0x26010002 },
    { 0x20010203 },
    { 0x26010002 },
    { 0x20010303 },
    { 0x26010002 },
    { 0x20010303 },
    { 0x26010002 },
    { 0x20010403 },
    { 0x26010002 },
    { 0x20010403 },
    { 0x26010002 },
    { 0x20010503 },
    { 0x26010002 },
    { 0x20010503 },
    { 0x26010002 },
    { 0x20010603 },
    { 0x26010002 },
    { 0x20010603 },
    { 0x26010002 },
    { 0x20010703 },
    { 0x26010002 },
    { 0x20010703 },
    { 0x26010002 },
    { 0x20010803 },
    { 0x26010002 },
    { 0x20010803 },
    { 0x26010002 },
    { 0x20010903 },
    { 0x26010002 },
    { 0x20010903 },
    { 0x26010002 },
    { 0x20010A03 },
    { 0x26010002 },
    { 0x1F010A06 },
    { 0x1E01000C },
    { 0x0C010007 },
    { 0x0CF60001 },
};

union AnimationStep D_800FAA80[] = {
    { 0x08010008 },
    { 0x09010006 },
    { 0x0A010006 },
    { 0x0B010002 },
    { 0x0B010003 },
    { 0x08010003 },
    { 0x08010063 },
    { 0x08010028 },
    { 0x08010006 },
    { 0x08F80114 },
};

union AnimationStep D_800FAAA8[] = {
    { 0x39010001 },
    { 0x3A010001 },
    { 0x3B010001 },
    { 0x3C010001 },
    { 0x3D010001 },
    { 0x3E010001 },
    { 0x3F010001 },
    { 0x40010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x41010001 },
    { 0x42010001 },
    { 0x43010001 },
    { 0x44010001 },
    { 0x45010001 },
    { 0x46010001 },
    { 0x47010001 },
    { 0x48010001 },
    { 0x49010001 },
    { 0x4A010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x4B010001 },
    { 0x4C010001 },
    { 0x4C010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x4D010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x4E010001 },
    { 0x4F010001 },
    { 0x50FF0001 },
};

union AnimationStep D_800FAB80[] = {
    { 0x00010010 },
    { 0x00010010 },
    { 0x00010010 },
    { 0x00010009 },
    { 0x00010009 },
    { 0x0001000B },
    { 0x00010010 },
    { 0x00F9000E },
};

union AnimationStep D_800FABA0[] = {
    { 0x01010010 },
    { 0x01010010 },
    { 0x01010010 },
    { 0x01010009 },
    { 0x01010009 },
    { 0x0101000B },
    { 0x01010010 },
    { 0x01F9000E },
};

union AnimationStep D_800FABC0[] = {
    { 0x02010008 },
    { 0x03010008 },
    { 0x04010008 },
    { 0x05010108 },
    { 0x06FC0008 },
};

union AnimationStep D_800FABD4[] = {
    { 0x08010008 },
    { 0x09010008 },
    { 0x0A010008 },
    { 0x0B010008 },
    { 0x0CFC0008 },
};

union AnimationStep D_800FABE8[] = {
    { 0x07010008 },
    { 0x02010108 },
    { 0x03010008 },
    { 0x04010008 },
    { 0x05010008 },
    { 0x06FB0008 },
};

union AnimationStep D_800FAC00[] = {
    { 0x0D010008 },
    { 0x08010008 },
    { 0x09010008 },
    { 0x0A010008 },
    { 0x0B010008 },
    { 0x0CFB0008 },
};

union AnimationStep D_800FAC18[] = {
    { 0x07010008 },
    { 0x02010108 },
    { 0x03010008 },
    { 0x04010008 },
    { 0x02010008 },
    { 0x00FB0008 },
};

union AnimationStep D_800FAC30[] = {
    { 0x0D010008 },
    { 0x08010008 },
    { 0x09010008 },
    { 0x0A010008 },
    { 0x08010008 },
    { 0x01FB0008 },
};

union AnimationStep D_800FAC48[] = {
    { 0x00010008 },
    { 0x02010008 },
    { 0x0201001E },
    { 0x02010005 },
    { 0x05010004 },
    { 0x05010007 },
    { 0x05010004 },
    { 0x05F90014 },
};

union AnimationStep D_800FAC68[] = {
    { 0x01010008 },
    { 0x08010008 },
    { 0x0801001E },
    { 0x08010005 },
    { 0x0B010004 },
    { 0x0B010007 },
    { 0x0B010004 },
    { 0x0BF90014 },
};

union AnimationStep D_800FAC88[] = {
    { 0x05010003 },
    { 0x05010003 },
    { 0x05010003 },
    { 0x05010003 },
    { 0x05FC0006 },
};

union AnimationStep D_800FAC9C[] = {
    { 0x0B010003 },
    { 0x0B010003 },
    { 0x0B010003 },
    { 0x0B010003 },
    { 0x0BFC0006 },
};

union AnimationStep D_800FACB0[] = {
    { 0x00010008 },
    { 0x0001000C },
    { 0x02010008 },
    { 0x02010050 },
    { 0x02010006 },
    { 0x0001000C },
    { 0x00FA0008 },
};

union AnimationStep D_800FACCC[] = {
    { 0x01010008 },
    { 0x0101000C },
    { 0x08010008 },
    { 0x08010050 },
    { 0x08010006 },
    { 0x0101000C },
    { 0x01FA0008 },
};

union AnimationStep D_800FACE8[] = {
    { 0x00010014 },
    { 0x00010014 },
    { 0x00010016 },
    { 0x00010018 },
    { 0x0001000C },
    { 0x00FB0004 },
};

union AnimationStep D_800FAD00[] = {
    { 0x01010014 },
    { 0x01010014 },
    { 0x01010016 },
    { 0x01010018 },
    { 0x0101000C },
    { 0x01FB0004 },
};

union AnimationStep D_800FAD18[] = {
    { 0x05010001 },
    { 0x05FF0001 },
};

union AnimationStep D_800FAD20[] = {
    { 0x0B010001 },
    { 0x0BFF0001 },
};

union AnimationStep D_800FAD28[] = {
    { 0x00010008 },
    { 0x0001000C },
    { 0x02010008 },
    { 0x02010063 },
    { 0x02010028 },
    { 0x02010006 },
    { 0x0001000C },
    { 0x00FA0008 },
};

union AnimationStep D_800FAD48[] = {
    { 0x01010008 },
    { 0x0101000C },
    { 0x08010008 },
    { 0x08010063 },
    { 0x08010028 },
    { 0x08010006 },
    { 0x0101000C },
    { 0x01FA0008 },
};

union AnimationStep* D_800FAD68[] = {
    D_800FA748,
    D_800FA768,
    D_800FA778,
    D_800FA790,
    D_800FA7A4,
    D_800FA7B8,
    D_800FA7C8,
    D_800FA7DC,
    D_800FA7F8,
    D_800FA81C,
    D_800FA87C,
    D_800FA894,
    D_800FA8A8,
    D_800FA8D8,
    D_800FA8FC,
    D_800FA91C,
    D_800FA9B0,
    D_800FA9B8,
    D_800FA9C0,
    D_800FAA80,
    D_800FA83C,
    D_800FA85C,
    D_800FA964,
    D_800FA938,
    D_800FA948,
    D_800FAAA8,
};

union AnimationStep* D_800FADD0[] = {
    D_800FAB80,
    D_800FABA0,
    D_800FABC0,
    D_800FABD4,
    D_800FABE8,
    D_800FAC00,
    D_800FAC18,
    D_800FAC30,
    D_800FAC48,
    D_800FAC68,
    D_800FAC88,
    D_800FAC9C,
    D_800FACB0,
    D_800FACCC,
    D_800FACE8,
    D_800FAD00,
    D_800FAD18,
    D_800FAD20,
    D_800FAD28,
    D_800FAD48,
};

void (*D_800FAE20[4])(struct MainObj*) = {
    func_80047D04,
    func_80047E58,
    func_80049288,
    func_800493F8,
};

s16 D_800FAE30[4] = { -1, 1, 1, -1 };

void (*D_800FAE38[10])() = {
    func_8004808C,
    func_800480D0,
    func_800483AC,
    func_80048770,
    func_80048A1C,
    func_80048B98,
    func_80048DD0,
    func_80049028,
    func_80048EF8,
    func_80049884,
};

void (*D_800FAE60[2])() = {
    func_8004831C,
    func_80048348,
};

void (*D_800FAE68[7])(struct MainObj*) = {
    func_800483E8,
    func_80048434,
    func_800484C8,
    func_8004852C,
    func_8004852C,
    func_80048584,
    func_80048610,
};

void (*D_800FAE84[5])(struct MainObj*) = {
    func_800487AC,
    func_800487F0,
    func_80048864,
    func_800488F4,
    func_80048970,
};

void (*D_800FAE98[2])(struct MainObj*) = {
    func_80048A58,
    func_80048B04,
};

void (*D_800FAEA0[5])() = {
    func_80048BD4,
    func_80048C20,
    func_80048CF8,
    func_800488F4,
    func_80048970,
};

void (*D_800FAEB4[2])() = {
    func_80048E0C,
    func_80048E70,
};

void (*D_800FAEBC[2])() = {
    func_80048F34,
    func_80048F98,
};

void (*D_800FAEC4[3])(struct MainObj*) = {
    func_80049064,
    func_800490D4,
    func_800491BC,
};

void (*D_800FAED0[2])(struct MainObj*) = {
    func_800492C4,
    func_8004932C,
};

void (*D_800FAED8[6])(struct MainObj*) = {
    func_800494E0,
    func_8004955C,
    func_80049654,
    func_800488F4,
    func_8004970C,
    func_800497FC,
};
