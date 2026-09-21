// MainObj, main_object_update_funcs[56]
// 8006FD50..80072194
#include "common.h"

extern struct Unk_unk68 D_8010085C;
extern struct Unk_unk68 D_80100864;

extern void* D_801008C8[];
extern u8 D_801008D4[];

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8006FD50);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8006FEC8);

void func_8006FFC0(struct MainObj* arg0)
{
    struct MainObj* obj;
    u8 counter;

    arg0->on_screen = 1;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk7C = 0x1E;
        arg0->unk24 = FIXED(1);
        arg0->unk5 = (u8)arg0->unk5 + 1;
        func_80015D60(arg0, 0x26);
        engine_obj.enable_boss = 1;
        engine_obj.unk25 = 1;
        engine_obj.boss_ptr = arg0;
        D_8013B838 = 0;
        do {
            obj = func_8006FB20(arg0, D_80100D40[D_8013B838], 0x18);
            obj->unk24 = FIXED(0.875);
            counter = D_8013B838 + 1;
            D_8013B838 = counter;
        } while ((u32)(counter & 0xFF) < 3U);
        func_8001540C(2, 0xAD, arg0);
    }
}

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

void func_80070118(struct MainObj* arg0)
{
    arg0->on_screen = 1;
    if (arg0->unk6 == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.event != 0) {
            if (engine_obj.stage == 5) {
                ((void (*)(s32, s32, s32))func_8002217C)(
                    0xD, 0xFF, (s32)(s8)ENGINE_UNK2E);
                ENGINE_UNK2E = 1;
            }
            arg0->unk6 = (u8)arg0->unk6 + 1;
        }
    } else if (abc_object.unkC == 0) {
        arg0->unk6 = 0;
        arg0->unk7C = 2;
        arg0->unk5 = (u8)arg0->unk5 + 1;
        func_800921E8(4);
    }
}

void func_800701DC(struct MainObj* arg0)
{
    s16 temp_v0;

    arg0->on_screen = 1;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if ((func_8009227C() == 0) && (arg0->animation_step.fields.relative_step == 0)) {
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
        arg0->unk7C = 0x3C;
        arg0->unk5++;
    }
}

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

void func_80070948(struct MainObj* arg0)
{
    struct VisualObj* visual_obj;

    if (--arg0->unk7C == 0) {
        arg0->unk6++;
        func_80015D60(arg0, 3);
        arg0->unk7C = 0xF0;
        visual_obj = find_free_visual_obj();
        if (visual_obj != NULL) {
            visual_obj->active = 0x41;
            visual_obj->id = 0x17;
            visual_obj->unk40 = arg0->unk40;
            visual_obj->animation_table = (u32**)arg0->animation_table;
            visual_obj->unk3C = (void*)arg0->sprite_frames;
            visual_obj->unk42 = arg0->unk42;
            visual_obj->unk15 = arg0->unk15;
            visual_obj->bg_offset = arg0->bg_offset;
            visual_obj->x_pos.val = arg0->x_pos.val;
            visual_obj->y_pos.val = arg0->y_pos.val;
            visual_obj->unk50 = PLAYER_OBJECT(arg0);
            visual_obj->unk2 = 0;
            arg0->ext.main_56.unk80.visual = visual_obj;
        }
        func_8001540C(2, 0xB0, arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070A38);

void func_80070C88(struct MainObj* arg0)
{
    if (arg0->ext.main_56.unk80.effect->active == 0) {
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
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80070D2C(struct MainObj* self)
{
    if (self->unk7 == 0) {
        self->unk60 = 9;
        self->unk50 = &D_8010085C;
        self->unk54 = &D_80100860;
        self->unk24 = FIXED(9);
        self->unk20 = 0;
        self->ext.main_56.flags &= 0xFC;
        self->unk7++;
        func_80015D60(self, 7);
        func_8001540C(2, 0xAF, self);
    }

    if (self->on_screen == 0) {
        self->unk7 = 0;
        self->unk7C = 0x3C;
        self->unk6++;
    }
}

void func_80070DDC(struct MainObj* arg0)
{
    switch (arg0->unk7) {
    case 0:
        if (--arg0->unk7C != 0)
            break;
        arg0->unk7++;
        arg0->x_pos = g_Player.x_pos;
        arg0->unk24 = 0xFFF70000;
        arg0->unk50 = &D_80100864;
        arg0->ext.main_56.flags &= 0xFE;
        func_80015D60(arg0, 8);
        break;
    case 1:
        if (arg0->on_screen == 0)
            break;
        arg0->unk7++;
        func_8001540C(2, 0xAF, arg0);
        break;
    case 2:
        if (arg0->on_screen != 0)
            break;
        arg0->unk7 = 0;
        arg0->unk7C = 0x28;
        arg0->unk6++;
        break;
    }
}

void func_80070EE8(struct MainObj* arg0)
{
    switch (arg0->unk7) {
    case 0:
        if (--arg0->unk7C == 0) {
            arg0->unk7++;
            arg0->x_pos.val = g_Player.x_pos.val;
            arg0->y_pos.val = (background_objects[0].unk20 + 0x140) << 0x10;
            arg0->unk24 = 0x90000;
            arg0->unk50 = &D_8010085C;
            arg0->ext.main_56.flags &= 0xFE;
            func_80015D60(arg0, 7);
        }
        break;
    case 1:
        if (arg0->on_screen != 0) {
            arg0->unk7++;
            func_8001540C(2, 0xAF, arg0);
        }
        break;
    case 2:
        if (arg0->on_screen == 0) {
            arg0->unk7 = 0;
            arg0->unk7C = 0x5A;
            arg0->unk6++;
        }
        break;
    }
}

void func_8007100C(struct MainObj* arg0)
{
    s32 bg_idx;

    if (--arg0->unk7C != 0) {
        return;
    }
    bg_idx = arg0->bg_offset;
    arg0->unk5 = 2;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    if (arg0->x_pos.i.hi < background_objects[bg_idx].x_pos.i.hi + 0xA0) {
        arg0->x_pos.i.hi = background_objects[bg_idx].unk1E + 0x40;
    } else {
        arg0->x_pos.i.hi = background_objects[bg_idx].unk1E + 0x120;
    }
    arg0->y_pos.i.hi = background_objects[arg0->bg_offset].y_pos.u.hi - 0x50;
}

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

void func_800713A4(struct MainObj* arg0)
{
    s32 bg_idx;

    if (--arg0->unk7C != 0) {
        return;
    }
    bg_idx = arg0->bg_offset;
    arg0->unk5 = 2;
    arg0->unk6 = 0;

    if (arg0->x_pos.i.hi < background_objects[bg_idx].x_pos.i.hi) {
        arg0->x_pos.i.hi = background_objects[bg_idx].unk1E + 0x40;
    } else {
        arg0->x_pos.i.hi = background_objects[bg_idx].unk1E + 0x120;
    }

    arg0->y_pos.i.hi = background_objects[arg0->bg_offset].y_pos.u.hi - 0x50;
}

void func_80071468(struct MainObj* arg0)
{
    D_80100DC8[arg0->unk6](arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_800714C0(struct MainObj* arg0)
{
    arg0->x_pos.val += arg0->unk20;
    arg0->y_pos.val -= arg0->unk24;
    arg0->unk24 -= arg0->unk2C;
}

void func_800714F4(struct MainObj* self)
{
    s32 value = -0x50000;

    self->unk60 = 7;
    self->unk50 = &D_80100868;
    self->unk54 = &D_8010086C;
    self->unk6++;

    if (self->unk15 != 0) {
        value = 0x50000;
    }

    self->unk24 = FIXED(-9.5);
    self->unk20 = value;
    self->unk28 = 0;
    self->unk2C = FIXED(-0.2578125);
    self->ext.main_56.flags &= 0xFD;

    func_80015D60(self, 4);
    func_8001540C(2, 0xAF, self);
}

void func_80071598(struct MainObj* arg0)
{
    if (arg0->unk24 > 0) {
        arg0->unk2C = -FIXED(0.8125);
        arg0->unk24 = 0;
        arg0->unk6++;
        arg0->ext.main_56.flags &= ~2;
    }
}

void func_800715D4(struct MainObj* entity)
{
    if (entity->on_screen == 0) {
        entity->unk5 = 2;
        entity->unk6 = 0;

        if (entity->x_pos.i.hi < background_objects[entity->bg_offset].x_pos.i.hi) {
            entity->x_pos.i.hi = background_objects[entity->bg_offset].unk1E + 0x40;
        } else {
            entity->x_pos.i.hi = background_objects[entity->bg_offset].unk1E + 0x120;
        }

        entity->y_pos.i.hi = background_objects[entity->bg_offset].y_pos.i.hi - 0x50;
    }
}

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
            arg0->ext.main_56.unk80.effect = effect;
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
    struct EffectObj* effect = arg0->ext.main_56.unk80.effect;
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
