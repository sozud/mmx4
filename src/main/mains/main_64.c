// MainObj, main_object_update_funcs[64]
// 8007C30C..8007DD98
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007C30C);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007C3FC);

void func_8007C5C4(struct MainObj* arg0)
{
    arg0->on_screen = 1;
    arg0->unk6++;
    func_80015D60(arg0, 0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007C5F8);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007C69C);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007C6E8);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007C7D4);

void func_8007C824(struct MainObj* arg0)
{
    D_80102978[arg0->unk5](arg0);
}

void func_8007C860(struct MainObj* arg0)
{
    if ((arg0->x_pos.val - g_Player.x_pos.val) < 0) {
        arg0->unk15 = 0x40;
    } else {
        arg0->unk15 = 0;
    }
}

u8 func_8007C890(struct MainObj* arg0)
{
    if (arg0->ext.main_64.unk88 == 0) {
        if (arg0->ext.main_64.unk91 == 0) {
            if (arg0->unk5C < 0x18) {
                return D_801029A4[get_random() & 0x1F];
            }
            return D_80102984[get_random() & 0x1F];
        }
        return 3;
    }
    return 0;
}

void func_8007C914(struct MainObj* arg0)
{
    arg0->unk20 = 0;
    arg0->unk28 = FIXED(1);
    arg0->unk24 = 0;
    arg0->unk2C = 0;
    arg0->unk54 = NULL;
    arg0->unk50 = NULL;
    arg0->ext.main_64.unk84 = arg0->x_pos.u.hi;
    arg0->ext.main_64.unk86 = arg0->y_pos.u.hi;
    func_8001540C(2, 0xC6, arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007C968);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007C9B0);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007CA68);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007CC8C);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007CD54);

void func_8007CDA8(struct MainObj* arg0)
{
    D_801029D4[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007CDE4);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007CE3C);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007CE98);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007CEF8);

void func_8007CF68(struct MainObj* arg0)
{
    D_801029E8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007CFA4);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007D010);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007D0CC);

void func_8007D138(struct MainObj* arg0)
{
    D_801029F8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007D174);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007D234);

void func_8007D2F4(struct MainObj* arg0)
{
    arg0->ext.main_64.unk8B = 0;
    arg0->unk6++;
    func_80015D60(arg0, 0x25);
}

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007D324);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007D374);

void func_8007D3DC(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk6++;
        func_80015D60(arg0, 0xC);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007D424);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007D470);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007D4E4);

void func_8007D558(struct MainObj* arg0)
{
    D_80102A04[arg0->unk6](arg0);
}

void func_8007D594(struct MainObj* arg0)
{
    D_80102A20[arg0->unk2](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007D5D0);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007D710);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007D838);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007D9AC);

void func_8007DA20(struct MainObj* arg0)
{
    struct EffectObj* effect;
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 2;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x1A;
            effect->x_pos.u.hi = arg0->x_pos.u.hi;
            effect->y_pos.u.hi = arg0->y_pos.u.hi;
            arg0->ext.main_64.effect = effect;
        }
    }
    is_on_screen(BASE_OBJECT(arg0));
    if (arg0->unk7E-- == 0) {
        u8 unk92;
        arg0->ext.main_64.unk92 = unk92 = arg0->ext.main_64.unk92 - 5;
        arg0->unk42 ^= 0x8000;
        if (unk92 >= 0x1A) {
            arg0->ext.main_64.unk92 = 0;
        }
        arg0->unk7E = arg0->ext.main_64.unk92 < 6 ? 5 : arg0->ext.main_64.unk92;
    }
}

void func_8007DAFC(struct MainObj* arg0)
{
    struct EffectObj* effect = arg0->ext.main_64.effect;
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

void func_8007DBDC(struct BarObj* arg0)
{
    D_80102A48[arg0->unk5](arg0);
}

void func_8007DC18(struct MainObj* arg0)
{
    D_80102A54[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007DC54);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007DD0C);
