// MainObj, main_object_update_funcs[73]
// 8008BA38..8008D460
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008BA38);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008BB6C);

void func_8008BCB0(struct MainObj* arg0)
{
    typedef void (*SignedSoundFunction)(u16, u8, s8);
    s8* engine_state = &engine_obj.character_state.bytes[9];

    arg0->on_screen = 1;
    arg0->unk7C = 2;
    arg0->unk6++;
    ((SignedSoundFunction)func_8002217C)(0x27, 0xFF, *engine_state);
    *engine_state = 1;
}

void func_8008BD10(struct MainObj* arg0)
{
    if (abc_object.unkC == 0) {
        arg0->unk6++;
        engine_obj.enable_boss = 1;
        func_8001540C(2, 0xF8, NULL);
    }
}

void func_8008BD5C(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk6++;
        func_800921E8(0xA);
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8008BDAC(struct MainObj* arg0)
{
    s16 temp_v0;

    if (func_8009227C() == 0) {
        if (arg0->animation_step.fields.relative_step == 0) {
            if (arg0->unk5C < 0x30) {
                temp_v0 = arg0->unk7C - 1;
                arg0->unk7C = temp_v0;
                if (temp_v0 == 0) {
                    func_8001540C(0, 0xE, 0);
                    arg0->unk7C = 2;
                }
                arg0->unk5C++;
                return;
            }
            arg0->state = 1;
            arg0->unk5 = 2;
            arg0->unk6 = 0;
            arg0->unk7 = 0;
            arg0->unk61 = 0;
            arg0->ext.main_73.pad84[4] = 0;
            func_80036B18();
            return;
        }
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
}

void func_8008BE74(struct MainObj* arg0)
{
    D_801052AC[arg0->unk6](arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

void func_8008BEC4(struct MainObj* arg0)
{
    D_801052BC[arg0->unk5](arg0);
}

void func_8008BF00(struct MainObj* arg0)
{
    if (arg0->unk70 & 3) {
        if (arg0->unk70 & 1) {
            arg0->unk15 = 0;
        } else {
            arg0->unk15 = 0x40;
        }
    } else if ((arg0->x_pos.i.hi - g_Player.x_pos.i.hi) < 0) {
        arg0->unk15 = 0x40;
    } else {
        arg0->unk15 = 0;
    }
}

void func_8008BF54(struct MainObj* arg0, s32 arg1, s32 arg2)
{
    struct ShotObj* temp_v0;

    temp_v0 = find_free_shot_obj();
    if (temp_v0 != NULL) {
        temp_v0->active = 0x41;
        temp_v0->id = arg1 + 0x30;
        temp_v0->unk2 = arg2;
        temp_v0->x_pos.val = arg0->x_pos.val;
        temp_v0->y_pos.val = arg0->y_pos.val;
        temp_v0->animation_table = (u32**)arg0->animation_table;
        temp_v0->unk40 = arg0->unk40;
        temp_v0->unk3C = (u8*)arg0->sprite_frames;
        temp_v0->unk42 = arg0->unk42 & 0x7FFF;
        temp_v0->unk16 = arg0->unk16;
        temp_v0->unk7C = WEAPON_OBJECT(arg0);
        temp_v0->unk15 = arg0->unk15;
    }
}

void func_8008C014(struct MainObj* arg0, s8 arg1)
{
    struct MainObj* source;
    struct MiscObj* temp_v0;

    source = arg0;
    temp_v0 = find_free_misc_obj();
    if (temp_v0 != 0) {
        temp_v0->active = 0x41;
        temp_v0->id = 0x31;
        temp_v0->unk2 = arg1;
        temp_v0->x_pos.val = source->x_pos.val;
        temp_v0->y_pos.val = source->y_pos.val;
        temp_v0->animation_table = (u32**)source->animation_table;
        temp_v0->unk40 = source->unk40;
        temp_v0->unk3C = (u8*)source->sprite_frames;
        temp_v0->unk42 = source->unk42 & 0x7FFF;
        temp_v0->unk16 = source->unk16;
        temp_v0->ext.pointer.unk50 = source;
        temp_v0->unk15 = 0;
    }
}

void func_8008C0C0(struct MainObj* arg0)
{
    arg0->unk7 = 0;
    arg0->unk7C = 0x3C;
    arg0->unk6++;
    func_8008BF00(arg0);
    func_80015D60(arg0, 1);
}

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008C10C);

void func_8008C204(struct MainObj* arg0)
{
    D_801052C8[arg0->unk6](arg0);
}

void func_8008C240(struct MainObj* arg0)
{
    arg0->unk6++;
    func_80015D60(arg0, 3);
    func_8001540C(2, 0xF4, NULL);
}

void func_8008BF54(struct MainObj*, s32, s32);

void func_8008C27C(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk7C = 0x32;
        arg0->unk6++;
        func_8008BF00(arg0);
        return;
    }

    if (arg0->animation_step.fields.event != 0) {
        func_8008BF00(arg0);
        func_8008BF54(arg0, 0, 0);
        func_8001540C(2, 0xF5, 0);
    }

    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8008C30C(struct MainObj* arg0)
{
    s16 timer = arg0->unk7C;

    if (timer == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 1;
        arg0->unk7C = 0;
        func_8008BF00(arg0);
        return;
    }
    arg0->unk7C = timer - 1;
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8008C360(struct MainObj* arg0)
{
    D_801052D0[arg0->unk6](arg0);
}

void func_8008C39C(struct MainObj* arg0)
{
    arg0->unk24 = FIXED(8);
    arg0->unk28 = 0;
    arg0->unk20 = 0;
    arg0->unk2C = 0;
    arg0->unk60 = 9;
    arg0->unk6++;
    func_80015D60(arg0, 4);
    func_8001540C(2, 0xF6, NULL);
}

void func_8008C3F4(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk6++;
    }
}

void func_8008C43C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 4) {
        arg0->unk6 += 1;
        func_80015D60(arg0, 5);
        func_8001540C(2, 0xF7, NULL);
    } else {
        func_8002B694(ANIMATED_OBJECT(arg0));
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008C4B4);

void func_8008C5A8(struct MainObj* arg0)
{
    s32 flags;
    s32 mask;

    flags = arg0->unk70;
    if (flags & 8) {
        arg0->unk7C = 0x1E;
        arg0->unk6++;
        func_80015D60(arg0, 6);
        arg0->unk54 = &D_80105264;
        arg0->unk50 = &D_80105260;
        func_8001540C(2, 0xF1, 0);
        return;
    }

    mask = 1;
    if (arg0->unk15 != 0) {
        mask = 2;
    }
    if (mask & flags) {
        arg0->unk20 = 0;
        arg0->unk28 = 0;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008C664);

void func_8008C7E4(struct MainObj* arg0)
{
    if (arg0->unk70 & 3) {
        arg0->unk7C = 0x1E;
        arg0->unk6++;
        func_80028B68(8, 4, 2);
        func_80015D60(arg0, 8);
        arg0->unk54 = (const u8*)&D_80105264;
        arg0->unk50 = (const u8*)&D_80105260;
        func_8001540C(2, 0xF7, 0);
    } else {
        func_8002B694(ANIMATED_OBJECT(arg0));
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
}

void func_8008C888(struct MainObj* arg0)
{
    s16 timer = arg0->unk7C;

    if (timer == 0) {
        arg0->unk24 = 0;
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk28 = 0;
        arg0->unk20 = 0;
        arg0->unk6++;
        return;
    }
    arg0->unk7C = timer - 1;
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8008C8E0(struct MainObj* arg0)
{
    if (arg0->unk70 & 8) {
        arg0->unk5 = 2;
        arg0->unk6 = 1;
        arg0->unk7C = 0;
        arg0->unk60 = 6;
        func_8008BF00(arg0);
        func_8001540C(2, 0xF1, NULL);
        return;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8008C95C(struct MainObj* arg0)
{
    D_801052DC[arg0->unk6](arg0);
}

void func_8008C998(struct MainObj* arg0)
{
    arg0->unk24 = FIXED(5);
    arg0->unk28 = 0;
    arg0->unk20 = 0;
    arg0->unk2C = FIXED(0.2578125);
    arg0->ext.main_73.unk89 = 0;
    arg0->unk6++;
    func_80015D60(arg0, 2);
}

void func_8008C9E0(struct MainObj* arg0)
{
    if (arg0->unk24 < 0) {
        arg0->unk7C = 0x32;
        arg0->unk6++;
        func_80015D60(arg0, 9);
        func_8008BF54(arg0, 1, 0);
        arg0->ext.main_73.unk89++;
        return;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8008CA60(struct MainObj* arg0)
{
    s16 timer;

    timer = arg0->unk7C;
    if (timer == 0) {
        func_80015D60(arg0, 0xA);
        if (arg0->ext.main_73.unk89 < 2) {
            arg0->unk7C = 0x14;
            arg0->unk20 = 0;
            arg0->unk28 = 0;
            arg0->unk24 = 0;
            arg0->unk2C = FIXED(0.2578125);
            arg0->unk6 += 1;
            func_80015D60(arg0, 2);
            arg0->ext.main_73.effect.position.x = arg0->x_pos.u.hi;
            arg0->ext.main_73.effect.position.y = arg0->y_pos.u.hi + 0x28;
            return;
        }
        arg0->unk7C = 0x1E;
        arg0->unk24 = 0;
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk6 += 3;
        return;
    }
    arg0->unk7C = timer - 1;
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008CB2C);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008CBF8);

void func_8008CC7C(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk6++;
        func_80015D60(arg0, 2);
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
}

void func_8008CCD4(struct MainObj* arg0)
{
    if (arg0->unk70 & 8) {
        arg0->unk5 = 2;
        arg0->unk6 = 1;
        arg0->unk7C = 0;
        func_8008BF00(arg0);
        func_80015D60(arg0, 1);
        return;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8008CD44(struct MainObj* arg0)
{
    D_80105300[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008CD80);

void func_8008CF68(struct MainObj* arg0)
{
    s16 timer = arg0->unk7C, next_timer = timer;
    u16 flags;
    if (timer == 0) {
        next_timer = 0x10;
        arg0->unk7C = next_timer;
        flags = arg0->unk42 | 0x8000;
    } else {
        next_timer--;
        arg0->unk7C = next_timer;
        flags = arg0->unk42 & 0x7FFF;
    }
    arg0->unk42 = flags;
}

void func_8008CFAC(struct MainObj* arg0)
{
    s32 var_a1;

    var_a1 = 0x40;
    if ((arg0->x_pos.val - g_Player.x_pos.val) < 0) {
        var_a1 = 0;
        arg0->unk15 = 0x40;
    } else {
        arg0->unk15 = 0;
    }
    func_80036AE4(0x14, var_a1);
    arg0->unk5 = 1;
    arg0->unk2C = FIXED(0.2578125);
    arg0->unk28 = 0;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk7C = 0x10;
    arg0->unk7E = 0x10;
    arg0->unk42 &= 0x7FFF;
    func_80015D60(arg0, 0xB);
    is_on_screen(BASE_OBJECT(arg0));
}

void func_8008D050(struct MainObj* arg0)
{
    func_8008CF68(arg0);
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        arg0->unk5 = 2;
        arg0->unk2C = 0;
        arg0->unk24 = 0;
        func_80015D60(arg0, 0);
        arg0->unk7E = 0x3C;
        func_80015D60(arg0, 0x1E);
    }
    CollisionRelated(PLAYER_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
}

void func_8008D0D0(struct MainObj* arg0)
{
    func_8008CF68(arg0);
    if (--arg0->unk7E == 0) {
        arg0->unk5 = 3;
        func_8002217C(0x28, 5, 0);
        engine_obj.enable_boss = 0;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_8008D138(struct MainObj* arg0)
{
    func_8008CF68(arg0);
    if (abc_object.unkC == 0) {
        arg0->unk5 = 4;
        arg0->unk7C = 0x19;
        arg0->ext.main_73.unk8B = 0x19;
        arg0->unk42 &= 0x7FFF;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_8008D19C(struct MainObj* arg0)
{
    struct EffectObj* effect;
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 5;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x1A;
            effect->x_pos.u.hi = arg0->x_pos.u.hi;
            effect->y_pos.u.hi = arg0->y_pos.u.hi;
            arg0->ext.main_73.unk80.effect = effect;
        }
    }
    is_on_screen(BASE_OBJECT(arg0));
    if (arg0->unk7E-- == 0) {
        u8 unk8B;
        arg0->ext.main_73.unk8B = unk8B = arg0->ext.main_73.unk8B - 5;
        arg0->unk42 ^= 0x8000;
        if (unk8B >= 0x1A) {
            arg0->ext.main_73.unk8B = 0;
        }
        arg0->unk7E = arg0->ext.main_73.unk8B < 6 ? 5 : arg0->ext.main_73.unk8B;
    }
}

void func_8008D278(struct MainObj* arg0)
{
    s8* script = arg0->ext.main_73.unk80.script;

    arg0->on_screen = 0;
    if (*script != 0) {
        if (script[7] == 0) {
            if (arg0->unk7E-- == 0) {
                arg0->unk7E = 5;
                arg0->unk42 ^= 0x8000;
            }
            is_on_screen(BASE_OBJECT(arg0));
        }
    } else {
        arg0->unk7C = 1;
        arg0->unk5 = 6;
    }
}

void func_8008D2FC(struct MainObj* arg0)
{
    s16 temp_v0;

    temp_v0 = arg0->unk7C - 1;
    arg0->unk7C = temp_v0;
    if (temp_v0 == 0) {
        engine_obj.unkF = 1;
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}

void func_8008D340(struct MainObj* arg0)
{
    D_80105334[arg0->unk5](arg0);
}

void func_8008D37C(struct MainObj* arg0)
{
    D_80105350[arg0->state](arg0);
}

s32 func_8008D3B8(struct MainObj* arg0, s8 arg1)
{
    struct EffectObj* effect;

    arg0->ext.main_73.effect.bytes.object_id = arg1;
    effect = find_free_effect_obj();
    if (effect != NULL) {
        effect->active = 1;
        effect->id = 0x2A;
        effect->unk2 = 0;
        effect->ext.effect_42.owner.main = arg0;
        D_8013B8AC = effect;
    }
}

void func_8008D410(struct MainObj* arg0)
{
    if (--arg0->ext.main_74.unk97 == 0) {
        arg0->ext.main_74.unk97 = 4;
        func_800AF95C(OBJECT_HEADER(arg0), 1, 0x60, 0x60, 2);
    }
}
