// MainObj, main_object_update_funcs[75]
// 8008FB38..800919C4
#include "common.h"

void func_8008FB38(struct MainObj* arg0)
{
    struct EffectObj* effect;

    if (g_Player.unkC4 == 0) {
        if (g_Player.x_pos.i.hi >= 0xD31) {
            background_objects[1].unk3 = 0;
        }
        arg0->active |= 4;
        func_80036AE4(0x14, 0x40);
        arg0->unk5++;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x18;
            arg0->ext.main_75.unk80.effect = effect;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_8008FBCC);

void func_8008FD6C(struct MainObj* arg0)
{
    if (g_Player.x_pos.i.hi >= 0xDF1) {
        arg0->unk5++;
        arg0->ext.main_75.background_unk1E = background_objects[0].unk1E;
        func_80036AE4(0x14, 0x40);
        background_objects[0].unk26 = 0xDD0;
        background_objects[0].unk2A = 0x190;
        engine_obj.enable_boss = 1;
        engine_obj.unk25 = 1;
        engine_obj.boss_ptr = arg0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_8008FDF8);

void func_8008FEE0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->ext.main_75.weapon->animation_step.fields.relative_step == 0) {
        arg0->unk5++;
        arg0->ext.main_75.unk80.child->unk5++;
        func_8001540C(2, 8, arg0);
        arg0->unk7C = 0x1E;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_8008FF50);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_8009002C);

void func_800900E0(struct MainObj* arg0)
{
    if (background_objects[0].unk1E == background_objects[0].unk26) {
        func_80036B18();
        background_objects[0].unk48 = 8;
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
        arg0->state++;
    }
}

void func_80090148(struct MainObj* arg0)
{
    D_80105E98[arg0->unk5](arg0);
    if (arg0->unk5 >= 2) {
        func_8002B318(BASE_OBJECT(arg0), 0xA0, 0xA0);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_800901B0);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_8009027C);

void func_80090470(struct MainObj* arg0)
{
    arg0->unk6++;
    func_80015D60(arg0->ext.main_75.weapon, 6);
    func_8001540C(2, 2, arg0);
    arg0->unk20 = 0;
    arg0->unk24 = FIXED(-0.5);
    arg0->ext.main_75.random_index = (get_random() & 0xFF) % 3U;
    arg0->unk7C = arg0->ext.main_75.random_index * 0x3C;
}

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80090508);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_800905D4);

void func_800906E4(struct MainObj* arg0)
{
    D_80105EB8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80090720);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80090838);

void func_8009093C(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk6++;
        func_80015D60(arg0, 0xC);
        arg0->unk7C = 0x46;
        arg0->unk7E = 0;
    }
}

void func_8009099C(struct MainObj* arg0)
{
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x37;
            shot->unk2 = arg0->unk7E + 4;
            shot->unk7C = WEAPON_OBJECT(arg0);
            arg0->unk7E ^= 1;
        }
        arg0->unk7C = 0x3C;
    }
}

void func_80090A28(struct MainObj* arg0)
{
    s16 timer;

    timer = D_8013B8C0->timer;
    if ((timer == 0x80) && (D_8013B8C4->timer == timer)) {
        arg0->unk6++;
        D_8013B8C0->state++;
        D_8013B8C4->state++;
        func_80015D60(arg0, 0x17);
    }
}

void func_80090AC0(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
    }
}

void func_80090B04(struct MainObj* arg0)
{
    D_80105EC4[arg0->unk6](arg0);
    if ((arg0->unk6 >= 3) && (D_80141BD8.unk0 % 10 == 0)) {
        u8 unk93;
        arg0->y_pos.i.hi += arg0->ext.main_75.unk94;
        unk93 = --arg0->ext.main_75.unk93;
        if (unk93 == 0) {
            arg0->ext.main_75.unk93 = 0xA;
            arg0->ext.main_75.unk94 *= -1;
        }
    }
}

void func_80090BD4(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_75.saved_unk5;
}

void func_80090BE0(struct MainObj* arg0)
{
    arg0->unk6++;
    func_80015D60(arg0->ext.main_75.weapon, 6);
    func_8001540C(2, 2, NULL);
    arg0->unk24 = FIXED(-0.5);
    arg0->unk7C = 0x64;
    arg0->ext.main_75.unk94 = 1;
    arg0->unk20 = 0;
    arg0->ext.main_75.unk92 = 0;
    arg0->ext.main_75.unk93 = 0xA;
}

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80090C54);

void func_80090CFC(struct MainObj* arg0)
{
    if (arg0->ext.main_75.unk92 != 0) {
        arg0->unk7C = 0x78;
        arg0->unk6++;
    }
}

void func_80090D24(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80090D6C(struct MainObj* arg0)
{
    D_80105EDC[arg0->unk6](arg0);
    if (D_80141BD8.unk0 % 10 == 0) {
        u8 unk93;
        arg0->y_pos.i.hi += arg0->ext.main_75.unk94;
        unk93 = --arg0->ext.main_75.unk93;
        if (unk93 == 0) {
            arg0->ext.main_75.unk93 = 0xA;
            arg0->ext.main_75.unk94 *= -1;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80090E2C);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80090F0C);

void func_80090FC0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk7C = 0x28;
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80091008);

void func_800910E0(struct MainObj* arg0)
{
    s32 velocity;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk6++;
        velocity = FIXED(-2);
        if (arg0->unk15 != 0) {
            velocity = FIXED(2);
        }
        arg0->unk20 = velocity;
        arg0->unk24 = 0;
    }
}

void func_8009114C(struct MainObj* arg0)
{
    u8 flags;
    u8 reset;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    flags = arg0->unk70;
    reset = 0;
    if (flags & 3) {
        if (arg0->unk15 != 0) {
            reset = flags & 1;
        } else if (flags & 2) {
            reset = 1;
        }
        if (reset != 0) {
            arg0->unk5 = 2;
            arg0->unk6 = 0;
            arg0->unk7 = 0;
            arg0->unk20 = 0;
            arg0->unk15 ^= 0x40;
        }
    }
}

void func_800911DC(struct MainObj* arg0)
{
    D_80105EEC[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80091218);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80091448);

void func_800914EC(struct MainObj* arg0)
{
    struct EffectObj* effect;
    s8 var_a0;

    if (--arg0->unk7C == 0) {
        arg0->unk5++;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = -0x7F;
            effect->id = 0x1A;
            effect->x_pos.i.hi = arg0->x_pos.i.hi;
            effect->y_pos.i.hi = arg0->y_pos.i.hi;
            arg0->ext.main_75.unk80.effect = effect;
        }
    }
    if (arg0->unk7E-- == 0) {
        arg0->ext.main_75.unk95 -= 5;
        var_a0 = arg0->ext.main_75.unk95;
        arg0->unk42 ^= 0x8000;
        if (var_a0 < 5) {
            var_a0 = 5;
        }
        arg0->unk7E = var_a0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_800915C4);

void func_80091754(struct MainObj* arg0)
{
    if (arg0->ext.main_75.unk80.child->active == 0) {
        func_80036AE4(0x14, 0x40);
        arg0->unk7C = 0x78;
        arg0->unk5++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_800917AC);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80091898);

void func_8009197C(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_80105F34[arg0->state](arg0);
}

void (*D_80105F34[])(struct MainObj*) = {
    func_80090148,
    func_80091218,
    func_80091898,
};
