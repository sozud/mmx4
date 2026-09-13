// MainObj, main_object_update_funcs[68]
// 80083218..80085F08
#include "common.h"

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

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800833D0);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800834B0);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083544);

void func_80083574(struct MainObj* arg0)
{
    D_80104340[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800835B0);

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

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083A18);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083A58);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083B20);

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

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083D30);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083DC8);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083E44);

void func_80083E70(struct MainObj* arg0)
{
    D_80104370[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083EAC);

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

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083FFC);

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

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80084254);

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

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80084394);

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

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800845C0);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_8008460C);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800846D0);

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

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800847B0);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80084870);

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

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80084CD4);

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

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800852C4);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800853A4);

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

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800856C4);

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

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800857C8);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085814);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800858DC);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085988);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085A44);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085BE4);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085C38);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085D38);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085DCC);

INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085E70);

void func_80085ECC(struct MainObj* arg0)
{
    D_8010448C[arg0->state](arg0);
}
