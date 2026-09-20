// MainObj, main_object_update_funcs[65]
// 8007DD98..800806A0
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007DD98);

void func_8007DF50(struct MainObj* self)
{
    struct EffectObj* effect;

    effect = find_free_effect_obj();
    if (effect != 0) {
        effect->active = 1;
        effect->id = 0x18;
        effect->x_pos.i.hi = self->x_pos.i.hi;
        effect->y_pos.i.hi = self->y_pos.i.hi;
        self->ext.main_65.unk80 = (struct MainObj*)effect;
    }
    self->unk15 = 0;
    self->unk6++;
    func_80036AE4(0x14, 0x40);
    if (engine_obj.stage == 0xC) {
        background_objects[0].unk26 = 0x1B0;
        background_objects[0].unk24 = 0x1B0;
        background_objects[0].unk2A = 0x5FB;
        background_objects[0].unk28 = 0x5FB;
    } else {
        background_objects[0].unk26 = 0x1490;
        background_objects[0].unk24 = 0x1490;
        background_objects[0].unk2A = 0x1EB;
        background_objects[0].unk28 = 0x1EB;
    }
}

void func_8007E01C(struct MainObj* arg0)
{
    if (arg0->ext.main_65.unk80->active == 0) {
        arg0->unk24 = FIXED(2);
        arg0->unk20 = 0;
        arg0->unk28 = FIXED(0.0078125);
        arg0->unk6++;
        func_80015D60(arg0, 0xF);
        func_8007DC54(ANIMATED_OBJECT(arg0), 0);
        arg0->unk67 = 1;
        arg0->unk7E = 0x14;
    }
}

void func_8007E098(struct MainObj* arg0)
{
    if ((arg0->y_pos.i.hi - background_objects[0].y_pos.i.hi) < 0x20) {
        arg0->unk20 = FIXED(-2);
        arg0->unk24 = FIXED(-2);
        arg0->unk2C = FIXED(0.1875);
        arg0->unk28 = 0;
        arg0->unk68 = &D_80102A60;
        arg0->unk6++;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8007E128(struct MainObj* arg0)
{
    if (arg0->unk70 & 8) {
        func_80015D60(arg0, 0x10);
        arg0->unk67 = 0;
        func_8001540C(2, 2, arg0);
        arg0->unk20 = 0;
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        arg0->unk6++;
        func_8007DC54(ANIMATED_OBJECT(arg0), 2);
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8007E1C0(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 0x11);
        arg0->unk6++;
        if (engine_obj.stage == 4) {
            ((void (*)(u16, u8, s8))func_8002217C)(
                0xB, 0xFF, engine_obj.character_state.bytes[8]);
            engine_obj.character_state.bytes[8] = 1;
        }
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8007E25C(struct MainObj* arg0)
{
    if (abc_object.unkC == 0) {
        arg0->unk6++;
        func_800921E8(3);
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8007E2B8(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0 && func_8009227C() == 0) {
        func_80015D60(arg0, 0x12);
        engine_obj.enable_boss = 1;
        arg0->unk7E = 3;
        arg0->unk20 = 0;
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        arg0->unk6++;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007E350);

void func_8007E45C(struct MainObj* arg0)
{
    D_801034B8[arg0->unk6](arg0);
}

void func_8007E498(struct MainObj* arg0)
{
    if (g_Player.x_pos.i.hi > arg0->x_pos.i.hi) {
        arg0->unk15 = 0x40;
    } else {
        arg0->unk15 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007E4C8);

void func_8007E5D0(struct MainObj* arg0)
{
    s32 var_a0;

    func_8007E498(arg0);
    func_80015D60(arg0, 3);
    func_8007DC54(ANIMATED_OBJECT(arg0), 2);
    arg0->unk67 = 1;
    func_8001540C(2, 0, arg0);
    var_a0 = FIXED(-0.75);
    arg0->unk6 = (u8)arg0->unk6 + 1;
    if (arg0->unk15 != 0) {
        var_a0 = FIXED(0.75);
    }
    arg0->unk24 = FIXED(4);
    arg0->unk28 = FIXED(0.03125);
    arg0->unk20 = var_a0;
    arg0->unk2C = FIXED(-0.03125);
    arg0->ext.main_65.unk88 = (u16)arg0->y_pos.i.hi;
}

void func_8007E66C(struct MainObj* arg0)
{
    if ((arg0->ext.main_65.unk88 - arg0->y_pos.i.hi) >= 0x51) {
        arg0->unk6++;
        func_80015D60(arg0, 4);
        func_8001540C(2, 1, arg0);
        arg0->unk60 = 6;
        arg0->unk24 = FIXED(-6);
        arg0->unk28 = 0;
        arg0->unk2C = 0;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007E6F8);

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007E848);

void func_8007E8C0(struct MainObj* arg0)
{
    D_801034D8[arg0->unk6](arg0);
    func_8002B318((struct BaseObj*)arg0, 0x40, 0x40);
}

void func_8007E918(struct MainObj* arg0)
{
    func_8007E498(arg0);
    func_80015D60(ANIMATED_OBJECT(arg0), 0xB);
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007E95C);

void func_8007EA3C(struct MainObj* arg0)
{
    D_801034E8[arg0->unk6](arg0);
    func_8002B318((struct BaseObj*)arg0, 0x40, 0x40);
}

void func_8007EA94(struct MainObj* arg0)
{
    func_8007E498(arg0);
    func_80015D60(arg0, 0xC);
    func_8001540C(2, 3, arg0);
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007EAE8);

void func_8007EBD0(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 9;
        arg0->unk6 = 0;
    }
}

void func_8007EC1C(struct MainObj* arg0)
{
    D_801034F0[arg0->unk6](arg0);
    func_8002B318((struct BaseObj*)arg0, 0x40, 0x40);
}

void func_8007EC74(struct MainObj* arg0)
{
    if (arg0->x_pos.i.hi > D_8013B844[0]) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
    func_80015D60(arg0, 0xA);
    func_8001540C(2, 3, arg0);
    arg0->unk6++;
}

void func_8007ECEC(struct WeaponObj* self)
{
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x29;
            shot->unk2 = 2;
            shot->unk7C = self;
        }
        self->unk80.word = (s32)shot;
        self->animation_step.fields.event = 0;
    }
    if (self->animation_step.fields.event == 2) {
        shot = (struct ShotObj*)self->unk80.word;
        shot->unk6++;
        self->animation_step.fields.event = 0;
    }
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6 = 0;
        if (self->ext.raw[1] == 3) {
            self->unk5 = 0xC;
        } else {
            self->unk5 = 3;
        }
        func_80015D60(self, 0);
    }
}

void func_8007EDC0(struct MainObj* arg0)
{
    D_801034FC[arg0->unk6](arg0);
    func_8002B318((struct BaseObj*)arg0, 0x40, 0x40);
}

void func_8007EE18(struct MainObj* arg0)
{
    s32 var_v1;

    if (arg0->x_pos.i.hi > D_8013B844[0]) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
    func_80015D60(arg0, 3);
    func_8007DC54(ANIMATED_OBJECT(arg0), 2);
    arg0->unk67 = 1;
    func_8001540C(2, 0, arg0);
    var_v1 = FIXED(-5);
    if (arg0->unk15 != 0) {
        var_v1 = FIXED(5);
    }
    arg0->unk24 = FIXED(3);
    arg0->unk2C = FIXED(-0.03125);
    arg0->unk20 = var_v1;
    arg0->unk28 = 0;
    arg0->unk50 = (const u8*)&D_80102A70;
    arg0->unk6++;
}

void func_8007EED8(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B694(ANIMATED_OBJECT(self));

    if (self->y_pos.i.hi < D_8013B84C[2]) {
        self->y_pos.i.hi = D_8013B84C[2];
        self->unk24 = 0;
        self->unk2C = 0;
    }

    if (self->unk15 == 0
            ? self->x_pos.i.hi < (*D_8013B844 - 0x10)
            : (*D_8013B844 + 0x10) < self->x_pos.i.hi) {
        self->unk2C = FIXED(0.12109375);
        self->unk6++;
    }
}

void func_8007EF94(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        arg0->unk6++;
        func_80015D60(arg0, 6);
        func_8007DC54(ANIMATED_OBJECT(arg0), 2);
        arg0->unk67 = 0;
        func_8001540C(2, 2, arg0);
    }
}

void func_8007F00C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk50 = (const u8*)&D_80102A6C;
        arg0->unk6 = 0;
        arg0->unk5 = 7;
    }
}

void func_8007F05C(struct MainObj* arg0)
{
    D_80103504[arg0->unk6](arg0);
    func_8002B318((struct BaseObj*)arg0, 0x40, 0x40);
}

void func_8007F0B4(struct MainObj* arg0)
{
    arg0->ext.main_65.pad8B[0] = 0x40;
    func_8007E498(arg0);
    arg0->unk24 = FIXED(6);
    arg0->unk2C = FIXED(0.1875);
    arg0->unk28 = 0;
    arg0->unk50 = (const u8*)&D_80102A70;
    func_80015D60(arg0, 3);
    func_8007DC54(ANIMATED_OBJECT(arg0), 2);
    arg0->unk67 = 1;
    func_8001540C(2, 0, arg0);
    if (arg0->x_pos.i.hi < D_8013B844[0]) {
        arg0->ext.main_65.pad8B[1] = 1;
    } else {
        arg0->ext.main_65.pad8B[1] = 0;
    }
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007F174);

void func_8007F2F4(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        if (arg0->ext.main_65.unk8D == 3) {
            arg0->unk5 = 5;
        } else {
            arg0->unk5 = 3;
            func_80015D60(arg0, 0);
        }
        arg0->unk6 = 0;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8007F360(struct MainObj* arg0)
{
    D_80103514[arg0->unk6](arg0);
    func_8002B318((struct BaseObj*)arg0, 0x40, 0x40);
}

void func_8007F3B8(struct MainObj* arg0)
{
    func_8007E498(arg0);
    func_80015D60(arg0, 8);
    arg0->unk50 = (const u8*)&D_80102A70;
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007F404);

void func_8007F50C(struct MainObj* arg0)
{
    D_80103520[arg0->unk6](arg0);
    func_8002B318((struct BaseObj*)arg0, 0x40, 0x40);
}

void func_8007F564(struct MainObj* arg0)
{
    func_8007E498(arg0);
    func_80015D60(arg0, 9);
    arg0->unk50 = (const u8*)&D_80102A70;
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007F5B0);

void func_8007F690(struct MainObj* arg0)
{
    D_80103528[arg0->unk6](arg0);
    if ((u32)(arg0->animation_step.fields.frame_index - 0x19) < 2U) {
        arg0->unk54 = (const u8*)&D_80102A68;
    } else {
        arg0->unk54 = (const u8*)&D_80102A64;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8007F71C(struct MainObj* arg0)
{
    arg0->unk60 = 8;
    func_8007E498(arg0);
    func_80015D60(arg0, 5);
    func_8001540C(2, 5, arg0);
    arg0->unk50 = (const u8*)&D_80102A70;
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007F780);

void func_8007F878(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));

    if (arg0->animation_step.fields.event == 2) {
        arg0->unk50 = (const u8*)&D_80102A74;
    }

    if (arg0->unk15 != 0) {
        if (arg0->unk20 < 0) {
            goto reset_velocity;
        }
    } else if (arg0->unk20 >= 0) {
    reset_velocity:
        arg0->unk20 = 0;
        arg0->unk28 = 0;
    }

    if (arg0->unk24 < 0) {
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk6++;
        func_80015D60(arg0, 7);
        arg0->unk50 = (const u8*)&D_80102A6C;
    }
}

void func_8007F93C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        arg0->unk6++;
        func_80015D60(arg0, 6);
        arg0->unk50 = (const u8*)&D_80102A6C;
        arg0->unk60 = 4;
        func_8007DC54(ANIMATED_OBJECT(arg0), 2);
        arg0->unk67 = 0;
        func_8001540C(2, 2, arg0);
    }
}

void func_8007F9C8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step != 0) {
        return;
    }
    arg0->unk6 = 0;
    if ((arg0->y_pos.i.hi <= D_8013B84C[0]) && (arg0->ext.main_65.unk8D == 3)) {
        if (arg0->ext.main_65.unk8E++ == 0) {
            return;
        }
    }
    arg0->unk5 = 9;
}

void func_8007FA4C(struct MainObj* arg0)
{
    D_80103530[arg0->unk6](arg0);
    func_8002B318((struct BaseObj*)arg0, 0x40, 0x40);
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007FAA4);

void func_8007FB48(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk24 < 0) {
        arg0->unk6++;
    }
}

void func_8007FB98(struct MainObj* arg0)
{
    struct MainObj* child;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    child = arg0->ext.main_65.unk80;
    if (child->animation_step.fields.relative_step < 0) {
        child->state = 2;
        arg0->unk24 = 0;
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk6++;
    }
}

void func_8007FBFC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        arg0->unk6++;
        func_80015D60(arg0, 0);
        if (arg0->ext.main_65.unk8A & 1) {
            arg0->ext.main_65.unk8A = 0x3D;
        } else {
            arg0->ext.main_65.unk8A = 0x3E;
        }
        arg0->unk7C = 1;
    }
}

void func_8007FC78(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 9;
        arg0->unk6 = 0;
    }
}

void func_8007FCC4(struct MainObj* arg0)
{
    D_80103544[arg0->unk6](arg0);
    func_8002B318((struct BaseObj*)arg0, 0x40, 0x40);
}

void func_8007FD1C(struct MainObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007FD24);

void func_8007FE84(struct MainObj* arg0)
{
    arg0->unk7C = 0x7F;
    arg0->unk7E = 0x19;
    arg0->unk61 = 0x19;
    arg0->unk5++;
    arg0->unk42 &= 0x7FFF;
    func_80015D60(arg0, 0xD);
    func_80036AE4(0x14, g_Player.unk15);
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007FF00);

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007FFFC);

void func_800802A4(struct MainObj* arg0, s32 arg1, s32 arg2)
{
    if (arg0->ext.main_65.unk80->active == 0) {
        arg0->unk5++;
        ((void (*)(u16, u8, s32))func_8002217C)(0xC, 0xFF, arg2);
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008030C(struct MainObj* arg0)
{
    if (abc_object.unkC == 0) {
        func_80015D60(arg0, 0x13);
        arg0->unk7C = 0x50;
        arg0->unk5++;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_80080370);

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_800804A0);

void func_800805D8(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        engine_obj.unkF = 1;
    }
}

void func_80080604(struct MainObj* arg0)
{
    D_80103590[arg0->unk5](arg0);
}

void func_80080640(struct MainObj* arg0)
{
    arg0->on_screen = 0;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    CollisionRelated((struct PlayerObj*)arg0);
    D_801035B0[arg0->state](arg0);
}
