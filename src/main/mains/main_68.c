// MainObj, main_object_update_funcs[68]
// 80083218..80085F08
#include "common.h"

extern void (*D_80104354[])(struct MainObj*);

void func_80083218(struct MainObj* arg0)
{
    struct EffectObj* effect;

    if (g_Player.unkC4 == 0) {
        arg0->on_screen = 0;
        background_objects[0].unk24 -= 0x10;
        func_80036AE4(0x14, 0x40);
        arg0->unk5++;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x18;
            arg0->ext.main_68.effect = effect;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_8008329C);

void func_800833D0(struct MainObj* arg0)
{
    s16 temp_v0;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk7E == 0) {
        if (arg0->unk5C < 0x30) {
            if (func_8009227C() == 0) {
                temp_v0 = arg0->unk7C - 1;
                arg0->unk7C = temp_v0;
                if (temp_v0 == 0) {
                    func_8001540C(0, 0xE, 0);
                    arg0->unk7C = 2;
                }
                arg0->unk5C++;
            }
        } else {
            arg0->unk7C = 0x1E;
            arg0->unk5++;
        }
    } else {
        arg0->unk7E--;
    }
    arg0->on_screen = 0;
    if (D_80141BD8.unk0 & 1) {
        is_on_screen(BASE_OBJECT(arg0));
    }
}

void func_800834B0(struct MainObj* self)
{
    s16 timer;

    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        func_8001540C(2, 3, self);
        self->unk7C = 0x3C;
        self->on_screen = 0;
        self->unk5 += 1;
        func_80036B18();
        return;
    }
    self->on_screen = 0;
    if (D_80141BD8.unk0 & 1) {
        is_on_screen(BASE_OBJECT(self));
    }
}

void func_80083544(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->state = 1;
        arg0->unk5 = 2;
    }
}

void func_80083574(struct MainObj* arg0)
{
    D_80104340[arg0->unk5](arg0);
}

void func_800835B0(struct MainObj* self)
{
    s16 x_pos;

    self->on_screen = 0;
    self->unk6++;
    self->x_pos.val = g_Player.x_pos.val;
    x_pos = self->x_pos.i.hi;
    if (x_pos < 0x470) {
        self->x_pos.i.hi = 0x470;
    } else if (x_pos >= 0x531) {
        self->x_pos.i.hi = 0x530;
    }
    self->y_pos.val = FIXED(0x150);
    self->unk7C = 5;
    self->ext.main_68.unk92 = 2;
    self->ext.main_68.unk8C = 0;
    self->ext.main_68.unk8E = 0;
    self->unk7E = 4;
    if (self->x_pos.i.hi >= 0x4D1) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
    func_80015D60(self, 0);
    func_80015D60(self->ext.main_68.unk80, 5);
    func_8001540C(2, 3, self);
}

void func_80083688(struct MainObj* arg0)
{
    arg0->unk54 = (const u8*)&D_80103EE8;
    arg0->unk50 = (const u8*)&D_80103EE4;
    if (arg0->unk7C == 0) {
        arg0->unk7C = 0x28;
        arg0->unk6++;
        return;
    }
    arg0->on_screen = 0;
    if (arg0->unk7C & 1) {
        is_on_screen(BASE_OBJECT(arg0));
    }
    arg0->unk7C--;
}

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083710);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800837FC);

void func_80083954(struct MainObj* arg0)
{
    if (arg0->ext.main_68.unk8E == 0) {
        arg0->unk7C = 0xA;
        arg0->unk6++;
        func_8001540C(2, 3, arg0);
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800839B0(struct MainObj* arg0)
{
    s16 timer = arg0->unk7C - 1;

    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->unk7C = 0x78;
        arg0->unk54 = NULL;
        arg0->unk50 = NULL;
        arg0->unk6++;
    }
    arg0->on_screen = 0;
    if (arg0->unk7C & 1) {
        is_on_screen(BASE_OBJECT(arg0));
    }
}

void func_80083A18(struct MainObj* arg0)
{
    s16 timer;
    arg0->on_screen = 0;
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->x_pos.i.hi = background_objects[0].x_pos.i.hi - 0x100;
    }
}

void func_80083A58(struct MainObj* arg0)
{
    D_80104354[arg0->unk6](arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (D_80141BD8.unk0 % 10 == 0) {
        arg0->y_pos.i.hi += arg0->ext.main_68.unk92;
        if (--arg0->unk7E == 0) {
            s32 t;
            arg0->unk7E = 4;
            t = arg0->ext.main_68.unk92;
            arg0->ext.main_68.unk92 = -t;
        }
    }
}

void func_80083B20(struct MainObj* arg0)
{
    if (g_Player.x_pos.i.hi >= 0x4D1) {
        arg0->x_pos.i.hi = 0x460;
        arg0->unk15 = 0x40;
    } else {
        arg0->x_pos.i.hi = 0x540;
        arg0->unk15 = 0;
    }
    arg0->y_pos.i.hi = 0x150;
    arg0->unk7C = 0xA;
    arg0->unk6++;
    func_80015D60(arg0, 0);
    func_80015D60(arg0->ext.main_68.unk80, 5);
    func_8001540C(2, 3, arg0);
}

void func_80083BB8(struct MainObj* arg0)
{
    s16 timer = arg0->unk7C - 1;

    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->unk7C = 0x28;
        arg0->unk6++;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    arg0->on_screen = 0;
    if (arg0->unk7C & 1) {
        is_on_screen(BASE_OBJECT(arg0));
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083C2C);

void func_80083D30(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (arg0->unk70 & 3) {
        arg0->unk7C = 0xA;
        arg0->unk68 = NULL;
        arg0->unk6++;
        func_8001540C(2, 3, arg0);
        arg0->unk4B = -1;
        arg0->ext.main_68.unk80->unk50 = NULL;
    }
    CollisionRelated(PLAYER_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
}

void func_80083DC8(struct MainObj* self)
{
    s16 timer;

    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        self->unk7C = 0x78;
        self->unk54 = 0;
        self->unk50 = 0;
        self->unk6++;
        self->x_pos.i.hi = background_objects[0].x_pos.u.hi - 0x100;
    }
    self->on_screen = 0;
    if (self->unk7C & 1) {
        is_on_screen(BASE_OBJECT(self));
    }
}

void func_80083E44(struct MainObj* arg0)
{
    arg0->on_screen = 0;
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
}

void func_80083E70(struct MainObj* arg0)
{
    D_80104370[arg0->unk6](arg0);
}

void func_80083EAC(struct MainObj* self)
{
    s8 state;
    s32 x_pos;

    state = self->unk7;
    if (state == 0) {
        self->unk7 = state + 1;
        x_pos = self->x_pos.val;
        self->unk15 = (g_Player.x_pos.val >= x_pos) << 6;
        func_80015D60(self, 0x16);
        return;
    }

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->unk50 = &D_80103F08;
        self->unk7 = 0;
        self->unk54 = &D_80103F0C;
        self->unk6++;
        func_80015D60(self, 0x17);
        func_8001540C(2, 0, self);
    }
}

void func_80083F6C(struct MainObj* arg0)
{
    func_8002B93C(MOVING_OBJECT(arg0),
        func_8002B7B0(OBJECT_HEADER(arg0), FIXED(1232), FIXED(336)) & 0xFF);
    arg0->unk20 *= 4;
    arg0->unk24 *= 4;
    if (func_8008318C(arg0, FIXED(1232), FIXED(336)) & 0xFF) {
        arg0->unk7C = 0x28;
        arg0->unk6++;
    }
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80083FFC(struct MainObj* arg0)
{
    s16 timer;
    struct ShotObj* shot;

    if (arg0->unk7 == 0) {
        timer = arg0->unk7C;
        timer--;
        arg0->unk7C = timer;
        if (timer == 0) {
            arg0->unk7++;
            func_80015D60(arg0, 0x1A);
        }
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.event != 0) {
            arg0->animation_step.fields.event = 0;
            shot = find_free_shot_obj();
            if (shot != 0) {
                shot->active = 0x41;
                shot->id = 0x2E;
                shot->unk2 = 7;
                shot->unk7C = WEAPON_OBJECT(arg0);
                arg0->ext.main_68.unk80 = (struct MainObj*)shot;
            }
        }
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->unk7 = 0;
            arg0->unk6++;
        }
    }
}

void func_800840D0(struct MainObj* arg0)
{
    if (arg0->ext.main_68.unk80->active == 0) {
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk24 = 0;
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk6++;
        func_80015D60(arg0, 0x18);
        func_80015930(2, 5);
        func_8001540C(2, 8, arg0);
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80084154(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        arg0->unk50 = (const u8*)&D_80103F00;
        arg0->unk54 = (const u8*)&D_80103F04;
        arg0->unk6++;
        func_80015D60(arg0, 0x19);
        func_8001540C(2, 1, arg0);
    }
}

void func_800841D4(struct MainObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
    }
}

void func_80084218(struct MainObj* arg0)
{
    D_80104388[arg0->unk6](arg0);
}

void func_80084254(struct MainObj* arg0)
{
    if (arg0->unk7 == 0) {
        arg0->ext.main_68.unk8F = 0;
        arg0->unk15 = (arg0->x_pos.val <= g_Player.x_pos.val) << 6;
        arg0->unk7 = (u8)(*(volatile u8*)&arg0->unk7 + 1);
        func_80015D60(arg0, 0x16);
        return;
    }

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk24 = FIXED(6.5);
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk50 = &D_80103F08;
        arg0->unk7 = 0;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk54 = &D_80103F0C;
        arg0->unk6++;
        func_80015D60(arg0, 0x17);
        func_8001540C(2, 0, arg0);
    }
}

void func_80084338(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk24 < 0) {
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        arg0->unk6++;
        func_80015D60(arg0, 0x1A);
    }
}

void func_80084394(struct MainObj* self)
{
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->animation_step.fields.event = 0;
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x2E;
            shot->unk2 = 3;
            shot->unk7C = WEAPON_OBJECT(self);
            self->ext.main_68.unk80 = (struct MainObj*)shot;
        }
    }
    if (self->animation_step.fields.relative_step == 0) {
        self->unk24 = 0;
        self->unk2C = FIXED(0.2578125);
        self->unk6++;
        func_80015D60(self, 0x13);
    }
}

void func_8008442C(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        arg0->unk50 = (const u8*)&D_80103F00;
        arg0->unk54 = (const u8*)&D_80103F04;
        arg0->unk6++;
        func_80015D60(arg0, 0x14);
        func_8001540C(2, 1, arg0);
    }
}

void func_800844AC(struct MainObj* arg0)
{
    s8 step;
    u8 index;
    u8 state;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    step = arg0->unk7;
    if (step == 0) {
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->unk7 = step + 1;
            func_80015D60(arg0, 0x10);
        }
    } else {
        index = arg0->ext.main_68.unk8F;
        if (index != 0) {
            state = D_8010439C[index + 3];
            arg0->unk6 = 0;
            arg0->unk7 = 0;
            arg0->unk5 = state;
        }
    }
}

void func_80084534(struct MainObj* arg0)
{
    D_801043A4[arg0->unk6](arg0);
}

void func_80084570(struct MainObj* arg0)
{
    u8 index;

    arg0->unk5 = D_801043B8[arg0->ext.main_68.unk8F];
    index = arg0->ext.main_68.unk8F + 1;
    arg0->ext.main_68.unk8F = index;
    arg0->unk54 = (const u8*)&D_80103EF4;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    if (index == 3) {
        arg0->ext.main_68.unk8F = 0;
    }
}

void func_800845C0(struct MainObj* arg0)
{
    arg0->unk6++;
    arg0->unk15 = (arg0->x_pos.val <= g_Player.x_pos.val) << 6;
    arg0->ext.main_68.unk8C = 0;
    func_80015D60(arg0, 0x1B);
}

void func_8008460C(struct MainObj* arg0)
{
    u8 var_s1;
    struct ShotObj* temp_v0;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    var_s1 = 0;
    if (arg0->animation_step.fields.event != 0) {
        arg0->animation_step.fields.event = 0;
        arg0->unk6 = (u8)arg0->unk6 + 1;
        do {
            temp_v0 = find_free_shot_obj();
            if (temp_v0 != 0) {
                temp_v0->active = 0x41;
                temp_v0->id = 0x2E;
                temp_v0->unk2 = 6;
                temp_v0->timer = var_s1;
                temp_v0->unk7C = WEAPON_OBJECT(arg0);
                arg0->ext.main_68.unk8C += 1;
                func_8001540C(2, 0xA, arg0);
            }
            var_s1 += 1;
        } while (var_s1 < 4);
    }
}

void func_800846D0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk7C = 0x5A;
        arg0->unk6++;
        func_80015D60(arg0, 0x2B);
    }
}

void func_80084724(struct MainObj* arg0)
{
    func_80015DC8(arg0);
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 5;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
    }
}

void func_80084774(struct MainObj* arg0)
{
    D_801043BC[arg0->unk6](arg0);
}

void func_800847B0(struct MainObj* arg0)
{
    if (arg0->unk7 == 0) {
        s32 other_x = arg0->ext.main_68.unk80->x_pos.val;

        arg0->unk7 = (u8)(*(volatile u8*)&arg0->unk7 + 1);
        arg0->unk15 = (arg0->x_pos.val < other_x) << 6;
        func_80015D60(arg0, 0x11);
        return;
    }

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk50 = &D_80103F08;
        arg0->unk7 = 0;
        arg0->unk54 = &D_80103F0C;
        arg0->unk6 = (u8)arg0->unk6 + 1;
        func_80015D60(arg0, 0x12);
        func_8001540C(2, 0, arg0);
    }
}

void func_80084870(struct MainObj* arg0)
{
    struct ObjectHeader* temp_v1;

    func_8002B93C(MOVING_OBJECT(arg0),
        func_8002B7B0(OBJECT_HEADER(arg0), FIXED(1232), FIXED(336)) & 0xFF);
    arg0->unk20 *= 4;
    arg0->unk24 *= 4;
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (func_8008318C(arg0, FIXED(1232), FIXED(336)) & 0xFF) {
        temp_v1 = OBJECT_HEADER(arg0->ext.main_68.unk80);
        arg0->unk6++;
        temp_v1->unk5++;
    }
}

void func_80084910(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->ext.main_68.unk80 == NULL) {
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk24 = 0;
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk6++;
        func_80015D60(arg0, 0x18);
        func_80015930(2, 5);
        func_8001540C(2, 8, arg0);
    }
}

void func_8008498C(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        arg0->unk50 = (const u8*)&D_80103F00;
        arg0->unk54 = (const u8*)&D_80103F04;
        arg0->unk6++;
        func_80015D60(arg0, 0x19);
    }
}

void func_800849FC(struct MainObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = 6;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
    }
}

void func_80084A40(struct MainObj* arg0)
{
    D_801043CC[arg0->unk6](arg0);
}

void func_80084A7C(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk50 = (const u8*)&D_80103F00;
        arg0->unk54 = (const u8*)&D_80103F04;
        arg0->unk6++;
        func_80015D60(arg0, 0x15);
        arg0->unk7C = 0x28;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80084B14);

void func_80084CD4(struct MainObj* arg0)
{
    struct QuadObj* quad;
    s8 quad_type;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->animation_step.fields.event = 0;
        func_8001540C(2, 9, arg0);

        quad = find_free_quad_obj();
        if (quad != 0) {
            quad->active = 1;
            quad->id = 0xF;
            quad->unk2 = (arg0->unk15 != 0) * 2;
            quad->unk5C = PLAYER_OBJECT(arg0);
            arg0->ext.main_68.effect = (struct EffectObj*)quad;
        }

        quad = find_free_quad_obj();
        if (quad != 0) {
            quad->active = 1;
            quad->id = 0xF;
            quad_type = 1;
            if (arg0->unk15 != 0) {
                quad_type = 3;
            }
            quad->unk2 = quad_type;
            quad->unk5C = PLAYER_OBJECT(arg0);
            arg0->ext.main_68.effect = (struct EffectObj*)quad;
        }
    }

    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk6++;
        func_80015D60(arg0, 0x1D);
    }
}

void func_80084DB8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (*(s8*)arg0->ext.main_68.effect == 0) {
        func_80015930(2, 9);
        arg0->unk5 = 5;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
    }
}

void func_80084E10(struct MainObj* arg0)
{
    D_801043E0[arg0->unk6](arg0);
}

void func_80084E4C(struct MainObj* arg0)
{
}

void func_80084E54(struct MainObj* arg0)
{
    struct VisualObj* visual;

    if (arg0->unk7 == 0) {
        arg0->unk7++;
        arg0->unk7C = 0x78;
        func_80015D60(arg0, 0x29);
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 0x20;
            visual->unk2 = 5;
        }
    } else {
        func_80015DC8(arg0);
        arg0->unk7C--;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80084EE4);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_8008502C);

void func_800851FC(struct BarObj* arg0)
{
    D_80104424[arg0->unk2](arg0);
}

void func_80085238(struct MainObj* arg0)
{
    func_80015930(2, 5);
    func_80015930(2, 9);
    func_80036AE4(0x15, 0);
    engine_obj.unk1C = 1;
    arg0->unk7C = 0x7F;
    arg0->unk7E = 0x19;
    arg0->ext.main_68.unk90 = 0x19;
    arg0->unk5++;
    func_80015D60(arg0, 0x29);
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800852C4(struct MainObj* arg0)
{
    struct EffectObj* effect;
    s8 var_a0;

    if (--arg0->unk7C == 0) {
        arg0->unk5++;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x1A;
            effect->x_pos.i.hi = arg0->x_pos.i.hi;
            effect->y_pos.i.hi = arg0->y_pos.i.hi;
            arg0->ext.main_68.effect = effect;
        }
    }
    is_on_screen(BASE_OBJECT(arg0));
    if (arg0->unk7E-- == 0) {
        arg0->ext.main_68.unk90 -= 5;
        var_a0 = arg0->ext.main_68.unk90;
        arg0->unk42 ^= 0x8000;
        if (var_a0 < 5) {
            var_a0 = 5;
        }
        arg0->unk7E = var_a0;
    }
}

void func_800853A4(struct MainObj* self)
{
    struct MainObj* target;

    target = self->ext.main_68.effect;
    self->on_screen = 0;
    if (target->active != 0) {
        if (target->unk7 == 0) {
            if (self->unk7E-- == 0) {
                self->unk7E = 5;
                self->unk42 ^= 0x8000;
            }
            is_on_screen(BASE_OBJECT(self));
        }
    } else {
        func_80036AE4(0x14, 0x40);
        self->unk7C = 0x78;
        self->unk5++;
        background_objects[0].unk28 += 0x100;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085460);

void func_80085580(struct MainObj* arg0)
{
    if (background_objects[0].y_pos.i.hi == background_objects[0].unk20) {
        func_800DABE4(7, 0, 0);
        background_objects[0].unk2A = background_objects[0].unk28;
        background_objects[0].unk24 += 0x280;
        func_80036B18();
        g_Player.unk7A = 0;
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}

void func_80085604(struct MainObj* arg0)
{
    D_8010444C[arg0->unk5](arg0);
}

void func_80085640(struct MainObj* arg0)
{
    arg0->unk4B = -1;
    arg0->unk7C = 0x40;
    arg0->unk7E = 4;
    arg0->unk54 = NULL;
    arg0->unk42 &= 0x7FFF;
    arg0->unk5++;
    func_80015D60(arg0, 8);
    func_80015D60(arg0->ext.main_68.unk80, 9);
    func_8001540C(2, 4, arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800856C4(struct MainObj* self)
{
    struct VisualObj* visual;
    s16 held;

    if (!(D_80141BD8.unk0 & 7)) {
        visual = find_free_visual_obj();
        if (visual != 0) {
            visual->active = 0x41;
            visual->id = 0x20;
            visual->unk2 = 2;
            visual->unk50 = PLAYER_OBJECT(self);
        }
    }

    held = self->unk7C - 1;
    self->unk7C = held;
    if (held == 0) {
        self->unk7C = 10;
        self->unk5++;
        func_8001540C(2, 3, self);
    }

    is_on_screen(BASE_OBJECT(self));
}

void func_80085768(struct MainObj* arg0)
{
    s16 timer = arg0->unk7C - 1;

    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->unk7C = 0x78;
        arg0->unk5++;
    }
    arg0->on_screen = 0;
    if (arg0->unk7C & 1) {
        is_on_screen(BASE_OBJECT(arg0));
    }
}

void func_800857C8(struct MainObj* arg0)
{
    s16 timer = arg0->unk7C;
    arg0->on_screen = 0;
    timer--;
    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->state = 1;
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
        arg0->x_pos.i.hi = background_objects[0].x_pos.i.hi - 0x70;
    }
}

void func_80085814(struct MainObj* arg0)
{
    D_80104460[arg0->unk5](arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (D_80141BD8.unk0 % 10 == 0) {
        arg0->y_pos.i.hi += arg0->ext.main_68.unk92;
        if (--arg0->unk7E == 0) {
            s32 t;
            arg0->unk7E = 4;
            t = arg0->ext.main_68.unk92;
            arg0->ext.main_68.unk92 = -t;
        }
    }
}

void func_800858DC(struct MainObj* arg0)
{
    u8 state = arg0->unk5;

    arg0->unk4B = -1;
    arg0->unk68 = &D_80103EF0;
    arg0->unk24 = FIXED(-1);
    arg0->unk54 = 0;
    arg0->ext.main_68.unk8C = 0;
    arg0->unk20 = 0;
    state++;
    arg0->unk42 &= 0x7FFF;
    arg0->unk5 = state;
    arg0->unk15 = (g_Player.x_pos.i.hi >= arg0->x_pos.i.hi) << 6;
    func_80015D60(arg0, 8);
    func_8001540C(2, 0xE, arg0);
    func_80015D60(arg0->ext.main_68.unk80, 9);
    is_on_screen(BASE_OBJECT(arg0));
}

void func_80085988(struct MainObj* arg0)
{
    struct VisualObj* temp_v0;

    if (D_80141BD8.unk0 == ((D_80141BD8.unk0 / 5) * 5)) {
        temp_v0 = find_free_visual_obj();
        if (temp_v0 != 0) {
            temp_v0->active = 0x41;
            temp_v0->id = 0x20;
            temp_v0->unk2 = 2;
            temp_v0->unk50 = PLAYER_OBJECT(arg0);
        }
    }
    if (arg0->unk70 & 8) {
        arg0->unk7C = 0x78;
        arg0->unk5++;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085A44);

void func_80085BE4(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->ext.main_68.unk8C == 0) {
        arg0->unk5++;
        func_80015D60(arg0, 0xF);
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_80085C38(struct MainObj* self)
{
    u16 sound_id;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk6 == 0) {
        if (self->animation_step.fields.relative_step == 0) {
            self->unk15 = (g_Player.x_pos.i.hi >= self->x_pos.i.hi) << 6;
            func_80036AE4(0x14, (self->x_pos.i.hi >= g_Player.x_pos.i.hi) << 6);
            self->unk6 = (u8)self->unk6 + 1;
            sound_id = 0x2C;
            if (engine_obj.cur_character == 0) {
                sound_id = 0x31;
            }
            ((void (*)(s32, s32, s32))func_8002217C)(
                sound_id, 0xFFU, engine_obj.character_state.bytes[9]);
            engine_obj.character_state.bytes[9] = 1;
        }
    } else if (abc_object.unkC == 0) {
        self->unk6 = 0;
        self->unk7C = 1;
        self->unk5 = (u8)self->unk5 + 1;
    }
    is_on_screen(BASE_OBJECT(self));
}

void func_80085D38(struct MainObj* self)
{
    u16 temp_v0;

    if (self->unk5C < 0x30) {
        temp_v0 = self->unk7C - 1;
        self->unk7C = temp_v0;
        if ((temp_v0 << 0x10) == 0) {
            func_8001540C(0, 0xE, 0);
            self->unk7C = 2;
        }
        self->unk5C = (s8)((u8)self->unk5C + 1);
    } else {
        self->unk7C = 0x5A;
        self->unk5 = (s8)((u8)self->unk5 + 1);
    }
    is_on_screen(BASE_OBJECT(self));
}

void func_80085DCC(struct MainObj* arg0)
{
    s16 temp_v0;
    u32 temp_v1;

    temp_v0 = arg0->unk7C - 1;
    arg0->unk7C = temp_v0;
    if (temp_v0 == 0) {
        temp_v1 = 1;
        arg0->collision_data = (const u16*)D_80108004;
        arg0->unk50 = (const u8*)&D_80103F00;
        arg0->unk54 = (const u8*)&D_80103F04;
        arg0->unk2 = temp_v1;
        arg0->state = temp_v1;
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
        arg0->ext.main_68.unk91 = 0;
        func_80036B18();
        temp_v1 = (u32)arg0->ext.main_68.unk80;
        ((struct MainObj*)temp_v1)->state++;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_80085E70(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_80104470[arg0->unk5](arg0);
    CollisionRelated(PLAYER_OBJECT(arg0));
}

void func_80085ECC(struct MainObj* arg0)
{
    D_8010448C[arg0->state](arg0);
}
