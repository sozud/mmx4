// MainObj, main_object_update_funcs[56]
// 8006FD50..80072194
#include "common.h"

extern void* D_801008C8[];
extern u8 D_801008D4[];

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8006FD50);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8006FEC8);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8006FFC0);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800700AC);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070118);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800701DC);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070294);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800702E8);

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

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800704AC);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070514);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070648);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800706D4);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070778);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800708DC);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070948);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070A38);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070C88);

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

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071228);

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

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8007168C);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071740);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800718F4);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8007196C);

void func_800719FC(struct MainObj* arg0)
{
    D_80100DE0[arg0->unk6](arg0);
}

void func_80071A38(struct MainObj* arg0)
{
    D_80100DEC[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071A74);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071AD8);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071B60);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071C00);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071C60);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071CB0);

void func_80071D1C(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071D30);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071EEC);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071F5C);

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

void func_8007211C(struct BarObj* arg0)
{
    D_80100E34[arg0->unk5](arg0);
}

void func_80072158(struct MainObj* arg0)
{
    D_80100E40[arg0->state](arg0);
}
