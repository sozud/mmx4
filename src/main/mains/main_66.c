// MainObj, main_object_update_funcs[66]
// 800806A0..80082434
#include "common.h"

void func_800806A0(struct MainObj* arg0)
{
    D_80103BDC[arg0->state](arg0);
    if (arg0->unk2 == 0) {
        CollisionRelated(PLAYER_OBJECT(arg0));
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80080700);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80080834);

void func_80080D20(struct BarObj* arg0)
{
    D_80103C0C[arg0->unk5](arg0);
}

void func_80080D5C(struct MainObj* arg0)
{
    struct MainObj* other;

    g_Player.unkBA = 0;
    func_80036AE4(0x14, g_Player.unk15);
    arg0->unk5 = 1;
    other = arg0->ext.main_66.unk94;
    arg0->unk42 &= 0x7FFF;
    other->unk42 &= 0x7FFF;
    func_80015D60(arg0->ext.main_66.unk94, 8);
    arg0->unk7C = 0x7F;
    arg0->unk7E = 0x19;
    arg0->unk61 = 0x19;
    func_8002B318(BASE_OBJECT(arg0), 0x60, 0x60);
}

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80080DF4);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80080F04);

void func_8008107C(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        engine_obj.unkF = 0x40;
    }
    func_8002B318(BASE_OBJECT(self), 0x60, 0x60);
}

void func_800810C4(struct MainObj* arg0)
{
    if (arg0->unk5 == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x60, 0x60);
    } else {
        arg0->on_screen = 0;
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}

void func_80081104(struct MainObj* arg0)
{
    s8 state;

    if ((arg0->ext.main_66.unk86 == 0) && (--arg0->ext.main_66.unk87 == 0)) {
        func_80015D60(arg0, 0x20);
        arg0->collision_data = (const u16*)D_80107E84;
        state = 5;
    } else {
        func_80015D60(arg0, 1);
        func_8001540C(2, 0xE1, arg0);
        state = 3;
    }
    arg0->unk5 = state;
    arg0->unk6 = 0;
}

void func_80081198(struct MainObj* arg0)
{
    D_80103C1C[arg0->unk6](arg0);
}

void func_800811D4(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (g_Player.x_pos.i.hi >= 0x80B) {
        background_objects[0].unk26 = 0x7F0;
        background_objects[0].unk24 = 0x830;
        arg0->unk6 = 1;
    }
}

void func_80081230(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (background_objects[0].x_pos.i.hi == 0x7F0) {
        func_80036AE4(0x15, 0);
        arg0->unk6 = 2;
    }
}

void func_8008127C(struct MainObj* arg0)
{
    struct EffectObj* effect;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (g_Player.unkC0 == -1) {
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x18;
            arg0->ext.main_66.effect = effect;
        }
        arg0->unk6 = 3;
    }
}

void func_800812E4(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->ext.main_66.effect->active == 0) {
        engine_obj.enable_boss = 1;
        engine_obj.unk25 = 1;
        engine_obj.boss_ptr = arg0;
        arg0->unk7C = 0x3C;
        arg0->unk6 = 4;
    }
}

void func_8008134C(struct MainObj* arg0)
{
    s8* state;
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        state = &engine_obj.character_state.bytes[9];
        func_8002217C(0x20, 0xFF, *state);
        *state = 1;
        arg0->unk6 = 5;
    }
}

void func_800813BC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (abc_object.unkC == 0) {
        arg0->unk7C = 0x28;
        arg0->unk6 = 6;
    }
}

void func_80081404(struct MainObj* self)
{
    struct MiscObj* obj;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        func_80015D60(self, 0xA);
        obj = find_free_misc_obj();
        if (obj != 0) {
            obj->active = 0x41;
            obj->id = 0x27;
            obj->x_pos.val = self->x_pos.val + FIXED(-1);
            obj->y_pos.val = self->y_pos.val + FIXED(-31);
            obj->bg_offset = self->bg_offset;
            obj->animation_table = self->animation_table;
            obj->unk40 = self->unk40;
            obj->unk3C = self->sprite_frames;
            obj->unk42 = self->unk42 & 0x7FFF;
            obj->ext.misc_7.position = self;
            obj->state = 0;
            obj->unk5 = 0;
        }
        self->unk7C = 0x3E;
        self->unk6 = 7;
    }
}

void func_800814E8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80081508(struct MainObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        func_80015D60(arg0, 0x1F);
        arg0->unk7C = 0xC8;
        arg0->unk6 = 9;
    }
}

void func_80081564(struct MainObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        func_80015D60(arg0, 0);
        arg0->unk6 = 0xA;
    }
}

void func_800815B8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        func_8001540C(2, 0xDF, arg0);
    }
    if (arg0->animation_step.fields.event == 1) {
        arg0->unk6 = 0xB;
        arg0->unk7E = 3;
        func_800921E8(9);
    }
}

void func_80081624(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (func_8009227C() == 0) {
        if (--arg0->unk7E == 0) {
            func_8001540C(0, 0xE, 0);
            arg0->unk7E = 3;
        }
        if (++arg0->unk5C == 0x30) {
            arg0->ext.main_66.pad88[4] = 1;
            func_80015D60(arg0, 1);
            func_8001540C(2, 0xE1, arg0);
            arg0->unk5 = 3;
            arg0->unk6 = 0;
            func_80036B18();
        }
    }
}

void func_800816DC(struct MainObj* arg0)
{
    D_80103C4C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081718);

void func_80081830(struct MainObj* arg0)
{
    D_80103C50[arg0->unk6](arg0);
}

void func_8008186C(struct MainObj* arg0)
{
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        func_80015D60(arg0, 3);
        arg0->unk24 = 0;
        arg0->unk6 = 1;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_800818C4);

void func_80081954(struct MainObj* arg0)
{
    s32 flags;

    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk15 == 0) {
        flags = arg0->unk70 & 1;
    } else {
        flags = arg0->unk70 & 2;
    }
    if (flags != 0) {
        func_80015D60(arg0, 5);
        arg0->unk6 = 3;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_800819C4);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081AD0);

void func_80081B64(struct MainObj* arg0)
{
    D_80103C64[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081BA0);

void func_80081CF8(struct MainObj* arg0)
{
    if (arg0->unk5C >= 0x18) {
        arg0->ext.main_66.unk85 = 0xF0;
    } else {
        arg0->ext.main_66.unk85 = 0xB4;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081D30);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081E44);

void func_80082014(struct MainObj* arg0)
{
    D_80103C70[arg0->unk6](arg0);
}

void func_80082050(struct MainObj* arg0)
{
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->y_pos.i.hi >= 0x1DD) {
        arg0->y_pos.i.hi = 0x1DC;
        arg0->unk24 = 0;
        arg0->unk6 = 1;
    }
}

void func_800820A4(struct MainObj* arg0)
{
    s16 x_pos;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (!(D_80141BD8.unk0 & 1)) {
        if (arg0->x_pos.i.hi < g_Player.x_pos.i.hi) {
            arg0->unk20 = FIXED(4);
        } else {
            arg0->unk20 = FIXED(-4);
        }
    }

    x_pos = arg0->x_pos.i.hi;
    if (x_pos - g_Player.x_pos.i.hi >= 0) {
        if (x_pos - g_Player.x_pos.i.hi < 3) {
        } else {
            func_8002B718(MOVING_OBJECT(arg0));
        }
    } else if (g_Player.x_pos.i.hi - x_pos >= 3) {
        func_8002B718(MOVING_OBJECT(arg0));
    }

    if (arg0->ext.main_66.unk94->unk6 == 4) {
        arg0->unk7C = 0x3C;
        arg0->unk6 = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80082170);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_8008225C);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80082354);

void func_80082404(struct MainObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}
