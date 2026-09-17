// MainObj, main_object_update_funcs[56]
// 8006FD50..80072194
#include "common.h"

extern void* D_801008C8[];
extern u8 D_801008D4[];

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8006FD50);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8006FEC8);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8006FFC0);

void func_800700AC(struct MainObj* arg0)
{
    arg0->on_screen = 1;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk24 = 0;
        arg0->unk5++;
        func_80015D60(arg0, 0x27);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070118);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800701DC);

void func_80070294(struct MainObj* arg0)
{
    arg0->on_screen = 1;
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
        arg0->state++;
        func_80036B18();
    }
}

void func_800702E8(struct MainObj* arg0)
{
    D_80100D44[arg0->unk5](arg0);
    if (arg0->on_screen != 0) {
        is_on_screen(BASE_OBJECT(arg0));
    }
}

s32 func_80070348(struct MainObj* arg0, s32 arg1, s32 arg2)
{
    s32 v1, v2;
    v1 = arg1 << 0x10;
    v2 = arg2 << 0x10;
    POS_BOUNDS_CHECK_FAIL_RET0(arg0->x_pos.val, v1)
    POS_BOUNDS_CHECK_FAIL_RET0(arg0->y_pos.val, v2)
    return 1;
}

void func_800703E0(struct MainObj* arg0)
{
    u32 idx;
    u8** table;
    u8* weights;
    u8* base;
    u8 i;
    u32 rnd;
    u32 gr;

    idx = arg0->unk5C - 1;
    if ((s32)idx < 0)
        idx = arg0->unk5C + 0xE;
    idx >>= 4;
    idx &= 0xFF;
    table = ((u8**)D_801008C8)[idx];
    gr = get_random();
    i = 0;
    base = D_801008D4;
    weights = base + idx * 3;
    rnd = (gr >> 2) & 0xF;
    while (i < 3) {
        if (rnd < weights[i]) {
            arg0->ext.main_56.unk84 = table[i];
            return;
        }
        i++;
    }
}

void func_800704AC(struct MainObj* arg0)
{
    arg0->unk60 = 6;
    arg0->unk50 = (const u8*)&D_80100844;
    arg0->unk54 = (const u8*)&D_80100848;
    arg0->unk67 = 1;
    arg0->unk68 = NULL;
    arg0->unk70 = 0;
    arg0->unk6++;
    arg0->ext.main_56.flags &= ~2;
    func_80015D60(arg0, 1);
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070514);

void func_80070648(struct MainObj* arg0)
{
    u8 value;

    if (arg0->unk7C == 0) {
        if (arg0->ext.main_56.unk84 == NULL) {
            func_800703E0(arg0);
        } else if (*arg0->ext.main_56.unk84 == 0xFF) {
            func_800703E0(arg0);
        }
        value = *arg0->ext.main_56.unk84;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
        arg0->ext.main_56.unk84++;
        arg0->unk5 = value;
    } else {
        arg0->unk7C--;
    }
}

void func_800706D4(struct MainObj* arg0)
{
    D_80100D60[arg0->unk6](arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));

    if (((func_8006FCB8(PLAYER_OBJECT(arg0), 0, 0) & 0xFF) == 3) && !(arg0->ext.main_56.flags & 2)) {
        func_8006FBFC(arg0);
        arg0->ext.main_56.flags |= 2;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070778);

void func_800708DC(struct MainObj* arg0)
{
    if (arg0->unk7 == 0) {
        arg0->unk7++;
        arg0->ext.main_56.unk88 = 0;
        func_80015D60(arg0, 2);
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk7 = 0;
        arg0->unk7C = 0x14;
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070948);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070A38);

void func_80070C88(struct MainObj* arg0)
{
    if (arg0->ext.main_56.effect->active == 0) {
        arg0->unk5 = 6;
        arg0->unk6 = 0;
    }
}

void func_80070CB0(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
}

void func_80070CDC(struct MainObj* arg0)
{
    D_80100D9C[arg0->unk6](arg0);
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070D2C);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070DDC);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070EE8);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8007100C);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800710D4);

void func_80071228(struct MainObj* arg0)
{
    if (arg0->unk7 == 0) {
        arg0->unk7++;
        arg0->unk60 = 9;
        arg0->unk68 = NULL;
        arg0->unk20 = 0;
        arg0->unk24 = 0;
        func_80015D60(arg0, 5);
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk7 = 0;
        arg0->unk7C = 0x14;
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800712A4);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800713A4);

void func_80071468(struct MainObj* arg0)
{
    D_80100DC8[arg0->unk6](arg0);
    func_80015DC8(arg0);
    func_8002B718((struct MovingObj*)arg0);
}

void func_800714C0(struct MainObj* arg0)
{
    arg0->x_pos.val += arg0->unk20;
    arg0->y_pos.val -= arg0->unk24;
    arg0->unk24 -= arg0->unk2C;
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800714F4);

void func_80071598(struct MainObj* arg0)
{
    if (arg0->unk24 > 0) {
        arg0->unk2C = -FIXED(0.8125);
        arg0->unk24 = 0;
        arg0->unk6++;
        arg0->ext.main_56.flags &= ~2;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800715D4);

void func_8007168C(struct MainObj* arg0)
{
    s32 direction;
    s32 result;

    D_80100DD4[arg0->unk6](arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_800714C0(arg0);

    direction = -0x30;
    if (arg0->unk15 != 0) {
        direction = 0x30;
    }

    result = func_8006FCB8(PLAYER_OBJECT(arg0), direction, 0);
    if ((result & 0xFF) == 3 && !(arg0->ext.main_56.flags & 2)) {
        func_8006FBFC(arg0);
        arg0->ext.main_56.flags |= 2;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071740);

void func_800718F4(struct MainObj* arg0)
{
    if (arg0->unk7C == 0) {
        if (arg0->unk7E != 0) {
            arg0->unk6--;
            arg0->unk7E--;
        } else {
            arg0->unk6++;
            arg0->unk7 = 0;
            func_80015D60(arg0, 0xA);
        }
    } else {
        arg0->unk7C--;
    }
}

void func_8007196C(struct MainObj* arg0)
{
    if (arg0->unk7 == 0 && arg0->animation_step.fields.relative_step == 0) {
        arg0->unk7++;
        arg0->unk7C = 0x28;
        func_80015D90(ANIMATED_OBJECT(arg0), 1, 2);
    }
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 1;
        arg0->unk7 = 0;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_800719FC(struct MainObj* arg0)
{
    D_80100DE0[arg0->unk6](arg0);
}

void func_80071A38(struct MainObj* arg0)
{
    D_80100DEC[arg0->unk6](arg0);
}

void func_80071A74(struct MainObj* arg0)
{
    arg0->collision_data = (const u16*)D_801060F0;
    arg0->unk42 &= 0x7FFF;
    arg0->unk6++;
    func_8001540C(2, 0xB3, arg0);
    func_80015D60(arg0, 0x16);
}

void func_80071AD8(struct MainObj* arg0)
{
    if (arg0->unk7 == 0) {
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->unk7++;
            arg0->unk7C = 0x78;
        }
    } else if (--arg0->unk7C == 0) {
        arg0->unk7C = 0xA;
        arg0->unk7 = 0;
        arg0->ext.main_56.unk89.value = 5;
        arg0->unk6++;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80071B60(struct MainObj* arg0)
{
    s16 timer;
    s8 step;

    timer = (u16)arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer != 0) {
        step = arg0->ext.main_56.unk89.value;
        arg0->x_pos.i.hi = arg0->x_pos.u.hi + step;
        arg0->ext.main_56.unk89.signed_value *= -1;
        return;
    }

    arg0->unk6++;
    func_80015D60(arg0, 0x17);
    func_8001540C(2, 0xCA, arg0);
    func_800C813C(6, D_80100D38, arg0);
}

void func_80071C00(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk24 = FIXED(8);
        arg0->unk20 = 0;
        arg0->unk6++;
        func_80015D60(arg0, 7);
        func_8001540C(2, 0xAF, arg0);
    }
}

void func_80071C60(struct MainObj* arg0)
{
    if (arg0->on_screen == 0) {
        arg0->state = 1;
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
        arg0->collision_data = (const u16*)D_801079F8;
    }
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_80071CB0(struct MainObj* arg0)
{
    func_8002DD04(arg0);
    D_80100DF8[arg0->unk6](arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002D9BC(arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x80, 0x80);
}

void func_80071D1C(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071D30);

void func_80071EEC(struct MainObj* arg0)
{
    func_80036AE4(0x14, g_Player.unk15);
    arg0->unk7C = 0x7F;
    arg0->unk7E = 0x19;
    arg0->ext.main_56.unk89.value = 0x19;
    arg0->unk5++;
    func_80015D90(ANIMATED_OBJECT(arg0), 0x16, 0);
    is_on_screen(BASE_OBJECT(arg0));
}

void func_80071F5C(struct MainObj* arg0)
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
            arg0->ext.main_56.effect = effect;
        }
    }
    is_on_screen(BASE_OBJECT(arg0));
    if (arg0->unk7E-- == 0) {
        arg0->ext.main_56.unk89.value -= 5;
        var_a0 = arg0->ext.main_56.unk89.value;
        arg0->unk42 ^= 0x8000;
        if (var_a0 < 5) {
            var_a0 = 5;
        }
        arg0->unk7E = var_a0;
    }
}

void func_8007203C(struct MainObj* arg0)
{
    struct EffectObj* effect = arg0->ext.main_56.effect;
    arg0->on_screen = 0;
    if (effect->active != 0) {
        if (effect->unk7 == 0) {
            if (arg0->unk7E-- == 0) {
                arg0->unk7E = 5;
                arg0->unk42 ^= 0x8000;
            }
            is_on_screen(BASE_OBJECT(arg0));
        }
    } else {
        if (engine_obj.stage != 0xC) {
            engine_obj.unkF = 0x10;
        } else {
            engine_obj.unkF = -0x80;
            engine_obj.character_state.bytes[engine_obj.checkpoint + 6] = 1;
            engine_obj.checkpoint += 9;
        }
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
}

void func_8007211C(struct MainObj* arg0)
{
    D_80100E34[arg0->unk5](arg0);
}

void func_80072158(struct MainObj* arg0)
{
    D_80100E40[arg0->state](arg0);
}
