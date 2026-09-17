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

void func_8007C69C(struct MainObj* arg0)
{
    if (abc_object.unkC == 0) {
        arg0->unk6++;
        func_80015D60(arg0, 1);
        engine_obj.enable_boss = 1;
        func_800921E8(5);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007C6E8);

void func_8007C7D4(struct MainObj* arg0)
{
    D_80102968[arg0->unk6](arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

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

void func_8007C968(struct MainObj* arg0)
{
    func_8007C914(arg0);
    arg0->unk7 = 0;
    arg0->unk6++;
    func_80015D60(arg0, 2);
    arg0->ext.main_64.unk88 = 0;
}

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007C9B0);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007CA68);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007CC8C);

void func_8007CD54(struct MainObj* arg0)
{
    s16 timer;

    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->unk6 = 0;
        arg0->unk7 = 0;
        arg0->ext.main_64.unk90 = 0;
        arg0->unk5 = arg0->ext.main_64.unk89;
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
}

void func_8007CDA8(struct MainObj* arg0)
{
    D_801029D4[arg0->unk6](arg0);
}

void func_8007CDE4(struct MainObj* arg0)
{
    arg0->unk6++;
    func_80015D60(arg0, 4);
    arg0->unk54 = (const u8*)&D_80102954;
    arg0->unk50 = (const u8*)&D_80102950;
    arg0->unk60 = 6;
}

void func_8007CE3C(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk67 = 1;
        arg0->unk24 = FIXED(8);
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk2C = FIXED(0.34375);
        arg0->unk6++;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8007CE98(struct MainObj* arg0)
{
    if (arg0->unk24 < 0) {
        arg0->unk6++;
        func_80015D60(arg0, 5);
        return;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8007CEF8(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 1;
        func_8007C914(arg0);
        arg0->unk20 = FIXED(22);
        arg0->unk67 = 0;
        func_80015D60(arg0, 0x22);
        arg0->unk60 = 5;
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
}

void func_8007CF68(struct MainObj* arg0)
{
    D_801029E8[arg0->unk6](arg0);
}

void func_8007CFA4(struct MainObj* arg0)
{
    arg0->unk7C = 0;
    arg0->unk6++;
    func_80015D60(arg0, 6);
    func_8001540C(2, 0xC9, arg0);
    arg0->unk54 = (const u8*)&D_8010295C;
    arg0->unk50 = (const u8*)&D_80102958;
    arg0->unk60 = 9;
}

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007D010);

void func_8007D0CC(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 1;
        func_8007C914(arg0);
        arg0->unk20 = FIXED(22);
        func_80015D60(arg0, 0x22);
        arg0->unk60 = 5;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8007D138(struct MainObj* arg0)
{
    D_801029F8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007D174);

void func_8007D234(struct MainObj* arg0)
{
    struct ShotObj* shot;

    shot = find_free_shot_obj();
    if (shot != 0) {
        shot->active = arg0->active;
        shot->id = 0x2A;
        shot->unk2 = arg0->ext.main_5.pad81[0xA];
        shot->x_pos.val = arg0->x_pos.val;
        shot->y_pos.val = arg0->y_pos.val;
        shot->animation_table = arg0->animation_table;
        shot->unk40 = arg0->unk40;
        shot->unk3C = arg0->sprite_frames;
        shot->unk42 = arg0->unk42 & 0x7FFF;
        shot->unk16 = arg0->unk16;
        shot->unk15 = 0;
        shot->unk7C = arg0->ext.main_64.object;
        shot->backref = arg0;
        func_8001540C(2, 0xC3, arg0);
    }
}

void func_8007D2F4(struct MainObj* arg0)
{
    arg0->ext.main_64.unk8B = 0;
    arg0->unk6++;
    func_80015D60(arg0, 0x25);
}

void func_8007D324(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk7C = 0x1E;
        arg0->unk6++;
        func_80015D60(arg0, 9);
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
}

void func_8007D374(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk6++;
        func_8007D174(arg0);
        func_80015D60(arg0, 0x24);
        arg0->unk7C = 0x1E;
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
}

void func_8007D3DC(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk6++;
        func_80015D60(arg0, 0xC);
    }
}

void func_8007D424(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk6++;
        func_8007D234(arg0);
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8007D470(struct MainObj* arg0)
{
    arg0->ext.main_64.unk8B++;
    if (arg0->ext.main_64.unk8B >= 8) {
        arg0->unk7C = 0x3C;
        arg0->unk6++;
        func_80015D60(arg0, 2);
        return;
    }
    arg0->unk7C = 0x5A;
    arg0->unk6 = 3;
    func_80015D90(ANIMATED_OBJECT(arg0), 9, 3);
}

void func_8007D4E4(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = 2;
        arg0->ext.main_64.unk8B = 0;
        arg0->unk2 = 0;
        arg0->unk6 = 1;
        func_8007C914(arg0);
        arg0->unk20 = FIXED(22);
        func_80015D60(arg0, 0x22);
        arg0->unk60 = 5;
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
}

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

void func_8007D9AC(struct MainObj* arg0)
{
    arg0->unk5 = 1;
    arg0->unk7C = 0x7F;
    arg0->unk7E = 0x19;
    arg0->ext.main_64.unk92 = 0x19;
    arg0->unk42 &= 0x7FFF;
    func_80036AE4(0x14, g_Player.unk15);
    func_80015D60(arg0, 0x20);
    is_on_screen(BASE_OBJECT(arg0));
}

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
            arg0->ext.main_64.object = effect;
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
    struct EffectObj* effect = arg0->ext.main_64.object;
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

void func_8007DC54(struct AnimatedObj* arg0, u32 arg1)
{
    struct MiscObj* obj;

    obj = find_free_misc_obj();
    if (obj != 0) {
        obj->active = 0x41;
        obj->id = 0x26;
        obj->unk2 = 2;
        obj->ext.misc_7.position = arg0;
    }

    obj = find_free_misc_obj();
    if (obj != 0) {
        obj->active = 0x41;
        obj->id = 0x26;
        obj->unk2 = 3;
        obj->ext.misc_7.position = arg0;
    }

    if (arg1 < 2U) {
        obj = find_free_misc_obj();
        if (obj != 0) {
            obj->active = 0x41;
            obj->id = 0x26;
            obj->unk2 = arg1;
            obj->ext.misc_7.position = arg0;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007DD0C);
