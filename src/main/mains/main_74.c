// MainObj, main_object_update_funcs[74]
// 8008D460..8008FB38
#include "common.h"

void func_8008D460(struct MainObj* arg0)
{
    D_8013B8B8[0] = 0;
    arg0->ext.main_74.unk94 = 0;
    arg0->ext.main_74.unk96 = 0;
    background_objects[0].unk26 = 0x410;
    background_objects[0].unk24 = 0x480;
    background_objects[0].unk2A = 0x200;
    background_objects[0].unk28 = 0x200;
    func_80036AE4(0x14, 0x40);
    arg0->ext.main_74.timer = 0x64;
    arg0->unk5++;
    func_80016FB4(3);
}

void func_8008D4E8(struct MainObj* arg0)
{
    if (--arg0->ext.main_74.timer == 0) {
        func_80013AD8(
#ifdef VERSION_JP
            0x80,
#else
            0x81,
#endif
            4, D_80141F30[2]);
        arg0->unk5++;
    }
}

void func_8008D548(struct MainObj* arg0)
{
    if ((D_801406AC == 2) && (D_8013BD40 == 0)) {
        D_80171EA8 = 1;
        arg0->unk5++;
    }
}

void func_8008D590(struct MainObj* arg0)
{
    func_8001653C();
    arg0->unk5++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008D5C8);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008D764);

void func_8008D830(struct MainObj* arg0)
{
    D_801058B0[arg0->unk5](arg0);
}

void func_8008D86C(struct MainObj* arg0)
{
}

void func_8008D874(struct MainObj* arg0)
{
    arg0->x_pos.i.hi = 0x567;
    arg0->y_pos.i.hi = 0x287;
    arg0->unk6++;
    func_80015D60(arg0, 0x18);
    func_8001540C(2, 9, arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008D8DC(struct MainObj* arg0)
{
    u16 sound_id;

    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk6++;
        sound_id = 0x2D;
        if (engine_obj.cur_character == 0) {
            sound_id = 0x32;
        }
        func_8002217C(sound_id, 0xFF, 0);
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008D95C(struct MainObj* arg0)
{
    if (abc_object.unkC == 0) {
        func_8008D764(arg0, 1);
        arg0->unk7E = 3;
        arg0->unk6++;
        func_800921E8(0xC);
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008D9C8);

void func_8008DAAC(struct MainObj* arg0)
{
    D_801058C4[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008DAE8);

void func_8008DC5C(struct MainObj* arg0)
{
    func_8008D3B8(arg0, 5);
    arg0->unk7C = 5;
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008DC9C);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008DD38);

void func_8008DDE8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (D_8013B8A8->active == 0) {
        func_80015930(2, 5);
        arg0->unk6++;
        func_80015D60(arg0,
            D_801058D4[arg0->ext.main_74.animation_index * 2 + 1]);
    }
}

void func_8008DE5C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        if (--arg0->unk7C == 0) {
            arg0->unk5 = 5;
            arg0->unk6 = 0;
        } else {
            arg0->unk6 = 1;
        }
    }
}

void func_8008DEC4(struct MainObj* arg0)
{
    D_801058DC[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008DF1C(struct MainObj* arg0)
{
    arg0->ext.main_74.animation_index = 1;
    func_80015D60(arg0, 0x1D);
    func_8008D3B8(arg0, 3);
    func_8001540C(2, 6, arg0);
    func_8001540C(2, 1, arg0);
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008DF8C);

void func_8008E040(struct MainObj* arg0)
{
    struct QuadObj* quad;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (D_8013B8A8->active == 0) {
        quad = find_free_quad_obj();
        if (quad != NULL) {
            quad->active = 1;
            quad->id = 0x10;
            quad->unk2 = arg0->ext.main_74.animation_index + 0x10;
            quad->unk5C = PLAYER_OBJECT(arg0);
        }
        D_8013B8A8 = OBJECT_HEADER(quad);
        arg0->unk6++;
    }
}

void func_8008E0CC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (D_8013B8A8->active == 0) {
        func_80015930(2, 1);
        if (arg0->ext.main_74.animation_index != 0) {
            func_80015D60(arg0, 0x22);
        } else {
            func_80015D60(arg0, 0x24);
        }
        arg0->unk6++;
    }
}

void func_8008E14C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}

void func_8008E18C(struct MainObj* arg0)
{
    D_801058F0[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008E1E4(struct MainObj* arg0)
{
    arg0->ext.main_74.unk8C = 3;
    arg0->unk6++;
    func_80015D60(arg0, 0x19);
    func_8001540C(2, 9, arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008E244);

void func_8008E318(struct MainObj* arg0)
{
    D_80105904[arg0->unk6](arg0);
}

void func_8008E354(struct MainObj* arg0)
{
    arg0->unk60 = 9;
    arg0->x_pos.i.hi = 0x567;
    arg0->y_pos.i.hi = 0x287;
    func_8008D764(arg0, 1);
    arg0->unk6++;
    func_80015D60(arg0, 0x18);
    func_8001540C(2, 9, arg0);
}

void func_8008E3C0(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        D_8013B8A0[0] = 0x1E;
    }

    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8008E404(struct MainObj* arg0)
{
    D_8010590C[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008E45C(struct MainObj* arg0)
{
    arg0->ext.main_74.unk8C = 3;
    arg0->unk6++;
    func_80015D60(arg0, 0x1B);
    func_8001540C(2, 9, arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008E4BC);

void func_8008E590(struct MainObj* arg0)
{
    D_80105914[arg0->unk6](arg0);
}

void func_8008E5CC(struct MainObj* arg0)
{
    arg0->unk60 = 9;
    arg0->x_pos.i.hi = 0x450;
    arg0->y_pos.i.hi = 0x2B8;
    func_8008D764(arg0, 2);
    arg0->unk6++;
    func_80015D60(arg0, 0x1A);
    func_8001540C(2, 9, arg0);
}

void func_8008E638(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        D_8013B8A0[0] = 0xA;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8008E67C(struct MainObj* arg0)
{
    D_8010591C[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008E6D4(struct MainObj* arg0)
{
    func_8008D3B8(arg0, 7);
    func_80015D60(arg0, 2);
    arg0->unk7C = 0x3C;
    arg0->unk62 = 3;
    arg0->unk50 = (const u8*)&D_80105364;
    arg0->unk60 = 0;
    arg0->unk6++;
    func_8001540C(2, 0xB, arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008E748);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008E8C8);

void func_8008E99C(struct MainObj* arg0)
{
    arg0->unk60 = 9;
    arg0->unk62 = 0;
    arg0->unk5 = 0xB;
    arg0->unk6 = 0;
}

void func_8008E9B8(struct MainObj* arg0)
{
    D_80105924[arg0->unk6](arg0);
    if (arg0->animation_step.fields.event != 0) {
        D_8013B8B0 = &D_80105374;
    } else {
        D_8013B8B0 = NULL;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008EA3C(struct MainObj* arg0)
{
    func_80015D60(arg0, 3);
    arg0->unk7C = 0x1E;
    arg0->unk50 = (const u8*)&D_80105360;
    arg0->unk6++;
}

void func_8008EA88(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk6++;
        func_80015D60(arg0, 4);
        arg0->unk7C = 0xF1;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008EAE4);

void func_8008EBC0(struct MainObj* arg0)
{
    D_80105934[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
    if (arg0->animation_step.fields.event != 0) {
        D_8013B8B0 = &D_80105374;
    } else {
        D_8013B8B0 = NULL;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008EC48);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008ED18);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008EDE8);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008EED4);

void func_8008EF94(struct MainObj* arg0)
{
    s16 timer = arg0->unk7C - 1;

    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->unk5 = 7;
        arg0->unk6 = 0;
        return;
    }
    if ((timer % 10) == 0) {
        func_8001540C(2, 10, arg0);
    }
}

void func_8008F01C(struct MainObj* arg0)
{
    D_80105940[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
    if (arg0->animation_step.fields.event != 0) {
        D_8013B8B0 = &D_80105374;
        return;
    }
    D_8013B8B0 = NULL;
}

void func_8008F0A4(struct MainObj* arg0)
{
    u8 choice = (u32)(get_random() & 0xFF) % 3;
    switch (choice) {
    case 0:
        func_8008D3B8(arg0, 1);
        break;
    case 1:
        func_8008D3B8(arg0, 2);
        break;
    default:
        func_8008D3B8(arg0, 0);
        break;
    }
    arg0->unk6++;
}

void func_8008F134(struct MainObj* arg0)
{
    if (D_8013B8AC->active == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        D_8013B8A0[0] = 0x1E;
    }
}

void func_8008F16C(struct MainObj* arg0)
{
    D_80105954[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F1A8);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F3F4);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F4BC);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F578);

void func_8008F6FC(struct MainObj* arg0)
{
    struct EffectObj* effect;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5 = 4;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x2B;
            effect->unk2 = 1;
        }
    }
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008F76C(struct MainObj* arg0)
{
    u16 sound_id;

    if (g_Player.unkC0 != -1) {
        func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
        return;
    }
    func_8008D764(arg0, 0);
    sound_id = 0x25;
    if (engine_obj.cur_character == 0) {
        sound_id = 0x2C;
    }
    func_8002217C(sound_id, 7, 0);
    arg0->unk5 = 5;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008F7F0(struct MainObj* arg0)
{
    struct EffectObj* effect;

    if (abc_object.unkC == 0) {
        arg0->unk5 = 6;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = -0x7F;
            effect->id = 0x1A;
            effect->x_pos.i.hi = arg0->x_pos.i.hi;
            D_8013B8A8 = OBJECT_HEADER(effect);
            effect->y_pos.i.hi = arg0->y_pos.i.hi;
        }
        func_80015D60(arg0, 0);
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F884);

void func_8008F938(struct MainObj* arg0)
{
    D_80105994[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F974);

u8 func_8008FA0C(struct ObjectHeader* arg0, s16 arg1, s16 arg2)
{
    s16 temp_v1;
    s16 temp_a0;

    temp_v1 = arg0->x_pos.i.hi;
    if ((temp_v1 - arg1 >= 0) ? (temp_v1 - arg1 < 3) : (arg1 - temp_v1 < 3)) {
        temp_a0 = arg0->y_pos.i.hi;
        if ((temp_a0 - arg2 >= 0) ? (temp_a0 - arg2 < 3) : (arg2 - temp_a0 < 3)) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008FA88);
