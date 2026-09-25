// MainObj, main_object_update_funcs[54]
// 8006BB00..8006EB40
#include "common.h"

void func_8006BB00(struct MainObj* arg0)
{
    D_801005E4[arg0->state](arg0);
    CollisionRelated(arg0);
    if (!(g_Player.unk5C & 0x7F)) {
        func_8006E920(arg0, 0x38);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006BB70);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006BD1C);

void func_8006BFBC(struct MainObj* arg0)
{
    D_80100620[arg0->unk5](arg0);
}

void func_8006BFF8(struct MainObj* arg0)
{
    g_Player.unkBA = 0;
    func_80036AE4(0x14, g_Player.unk15);
    arg0->unk5 = 1;
    arg0->unk42 &= 0x7FFF;
    func_80015D60(arg0, 0x13);
    arg0->unk7C = 0x7F;
    arg0->unk7E = 0x19;
    arg0->unk61 = 0x19;
    func_8002B318(BASE_OBJECT(arg0), 0x60, 0x60);
}

void func_8006C07C(struct MainObj* self)
{
    struct EffectObj* effect;
    s8 delay;
    s8 next_delay;

    self->unk7C--;
    if (self->unk7C == 0) {
        self->unk5 = 2;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x1A;
            effect->x_pos.i.hi = self->x_pos.u.hi;
            effect->y_pos.i.hi = self->y_pos.u.hi;
            self->ext.main_54.unk8C = effect;
        }
    }
    func_8002B318(BASE_OBJECT(self), 0x60, 0x60);
    if (self->unk7E-- == 0) {
        self->unk42 ^= 0x8000;
        delay = self->unk61 - 5;
        self->unk61 = delay;
        if (delay >= 0x1A) {
            self->unk61 = 0;
        }
        next_delay = self->unk61;
        if (self->unk61 < 5) {
            next_delay = 5;
        }
        self->unk7E = next_delay;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006C170);

void func_8006C278(struct MainObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void func_8006C288(struct MainObj* arg0)
{
    D_8010062C[arg0->unk6](arg0);
}

void func_8006C2C4(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        arg0->unk50 = &D_80100220;
        arg0->unk54 = &D_80100224;
    }
    if (arg0->animation_step.fields.event == 1) {
        if (arg0->unk15 != 0) {
            arg0->unk20 = FIXED(3);
        } else {
            arg0->unk20 = FIXED(-3);
        }
        arg0->unk28 = FIXED(-0.125);
        arg0->unk24 = FIXED(3);
        arg0->unk2C = FIXED(0.125);
        func_80015D60(arg0, 9);
        func_8001540C(2, 0x81, arg0);
        arg0->unk6 = 1;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006C378);

void func_8006C598(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        func_8001540C(2, 0x82, arg0);
        func_80015D60(arg0, 0xA);
        arg0->unk54 = (const u8*)D_801001FC;
        arg0->unk50 = (const u8*)D_801001F8;
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        arg0->unk6 = 3;
    }
}

void func_8006C61C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60(arg0, 0);
        func_8006EA78(arg0);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_8006C670(struct MainObj* arg0)
{
    D_8010063C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006C6AC);

void func_8006CA80(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        arg0->unk54 = (const u8*)&D_80100204;
        arg0->unk50 = (const u8*)&D_80100200;
        func_8001540C(2, 0x87, arg0);
    }
    if (--arg0->unk7C == 0) {
        arg0->unk54 = (const u8*)D_801001FC;
        arg0->unk50 = (const u8*)D_801001F8;
        arg0->unk6 = 0;
    }
}

void func_8006CB14(struct MainObj* arg0)
{
    D_80100644[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006CB50);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006CC3C);

void func_8006CD80(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60(arg0, 0);
        func_8006EA78(arg0);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006CDD4);

void func_8006CE9C(struct MainObj* arg0)
{
    D_80100650[arg0->unk6](arg0);
}

void func_8006CED8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 0xD);
        arg0->unk6 = 1;
    }
}

void func_8006CF2C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk60 = 9;
        func_80015D60(arg0, 0xE);
        if (arg0->unk15 == 0) {
            arg0->unk20 = FIXED(-1);
        } else {
            arg0->unk20 = FIXED(1);
        }
        arg0->ext.main_54.unk86 = 1;
        arg0->ext.main_54.unk87 = 1;
        func_8001540C(2, 0x83, arg0);
        arg0->unk28 = FIXED(0.5);
        arg0->unk6 = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006CFB8);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006D280);

void func_8006D368(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk60 = 9;
        arg0->ext.main_54.unk86 = 1;
        arg0->unk20 = -arg0->unk20;
        func_80015D60(arg0, 0xE);
        func_8001540C(2, 0x83, arg0);
        arg0->unk6 = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006D3DC);

void func_8006D69C(struct MainObj* arg0)
{
    D_80100664[arg0->unk6](arg0);
}

void func_8006D6D8(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 6);
        arg0->unk16 = 6;
        arg0->unk60 = 6;
        arg0->unk54 = D_801001FC;
        arg0->unk50 = D_801001F8;
        arg0->unk5 = 4;
        arg0->unk62 = 0;
        arg0->ext.main_54.unk84 = 0;
        arg0->unk6 = 2;
    }
    if (g_Player.unkBA == 0) {
        return;
    }
    func_8001540C(2, 0x86, arg0);
    if (arg0->x_pos.i.hi - background_objects[0].x_pos.i.hi >= 0xA1) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
    g_Player.unk15 = arg0->unk15;
    g_Player.y_pos.i.hi = arg0->y_pos.i.hi - 8;
    if (arg0->unk15 == 0) {
        g_Player.x_pos.i.hi = arg0->x_pos.i.hi - 0x23;
        arg0->unk20 = FIXED(-6);
    } else {
        g_Player.x_pos.i.hi = arg0->x_pos.i.hi + 0x23;
        arg0->unk20 = FIXED(6);
    }
    func_80015D60(arg0, 5);
    arg0->unk16 = 1;
    arg0->unk7C = 0x30;
    arg0->unk6 = 1;
}

void func_8006D830(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 7);
        arg0->unk6 = 2;
        arg0->ext.main_54.unk87 = 1;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006D888);

void func_8006DB04(struct MainObj* arg0)
{
    g_Player.x_pos.i.hi = arg0->x_pos.u.hi;
    func_80028B68(0x1E, 8, 2);
    func_80015D60(arg0, 2);
    arg0->unk16 = 6;
    arg0->unk54 = &D_8010020C;
    arg0->unk50 = &D_80100208;
    arg0->unk28 = 0;
    if (arg0->unk15 != 0) {
        arg0->unk20 = FIXED(-3.244140625);
    } else {
        arg0->unk20 = FIXED(3.244140625);
    }
    arg0->unk2C = FIXED(0.21875);
    arg0->unk24 = FIXED(6.5625);
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_8001540C(2, 0x81, arg0);
    arg0->unk5 = 4;
    arg0->unk6 = 1;
    arg0->unk62 = 0;
    arg0->unk60 = 9;
    arg0->ext.main_54.unk84 = 0;
    g_Player.unkBA = 0;
}

void func_8006DBE8(struct MainObj* arg0)
{
    D_80100674[arg0->unk6](arg0);
}

void func_8006DC24(struct MainObj* arg0)
{
    struct EffectObj* temp_v0;

    if (g_Player.x_pos.i.hi >= 0x2500 || engine_obj.stage == 0xC) {
        temp_v0 = find_free_effect_obj();
        if (temp_v0 != 0) {
            temp_v0->active = 1;
            temp_v0->id = 0x18;
            arg0->ext.main_54.unk8C = temp_v0;
        }

        func_80036AE4(0x14, 0x40);
        if (engine_obj.stage == 8) {
            background_objects[0].unk26 = 0x24A0;
            background_objects[0].unk24 = 0x24E0;
            background_objects[0].unk2A = 0xF8;
            background_objects[0].unk28 = 0xF8;
        }

        arg0->unk7C = 3;
        arg0->unk7E = 1;
        arg0->unk6 = 1;
    }
}

void func_8006DCF4(struct MainObj* arg0)
{
    if (arg0->ext.main_54.unk8C->active == 0 && (background_objects[0].x_pos.i.hi == 0x24A0 || engine_obj.stage == 0xC)) {
        arg0->unk6 = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006DD44);

void func_8006DF68(struct MainObj* arg0)
{
    s16 timer;

    timer = (u16)arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        background_objects[0].unk26 = 0x24C0;
        background_objects[0].unk24 = 0x24D0;
        background_objects[0].unk2A = 0xD0;
        background_objects[0].unk28 = 0xD0;
        func_80015D60(arg0, 0x16);
        arg0->unk2C = FIXED(0.125);
        arg0->unk24 = FIXED(7.5);
        arg0->unk20 = FIXED(1.875);
        arg0->unk7E = 0;
        func_8001540C(2, 0x81, arg0);
        arg0->unk6 = 4;
    }
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x60, 0x60);
}

void func_8006E034(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->x_pos.i.hi - background_objects[0].x_pos.i.hi >= 0xE0) {
        arg0->unk20 = 0;
        arg0->unk2C = FIXED(1);
    }
    if (arg0->unk24 == 0) {
        arg0->unk68 = &D_8010024C;
        func_80015D60(arg0, 0x17);
    }
    if (arg0->unk24 < 0) {
        switch (arg0->unk7E) {
        case 0:
            if (func_8002D724(PLAYER_OBJECT(arg0), arg0->x_pos.i.hi + arg0->unk68->unk0,
                    arg0->unk68->unk3 + (arg0->y_pos.i.hi + arg0->unk68->unk1) + 0x40)
                == 0x38) {
                if (engine_obj.stage == 8) {
                    func_800DABE4(8, 0x2580, 0x140);
                    func_8001540C(2, 0x80, arg0);
                    func_800C813C(4, D_801005B0, arg0);
                }
                arg0->unk7E = 1;
            }
            break;
        case 1:
            if (func_8002D724(PLAYER_OBJECT(arg0), arg0->x_pos.i.hi + arg0->unk68->unk0,
                    arg0->unk68->unk3 + (arg0->y_pos.i.hi + arg0->unk68->unk1) + 0x10)
                == 0x38) {
                arg0->unk7E = 2;
                func_80015D60(arg0, 3);
                if (engine_obj.stage == 0xC) {
                    func_8001540C(2, 0x82, arg0);
                }
            }
            break;
        }
    }
    if (arg0->unk70 & 8) {
        func_80028BAC(0x10, 4, 2);
        arg0->ext.main_54.unk85 = 1;
        arg0->unk6 = 5;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x60, 0x60);
}

void func_8006E260(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        if (engine_obj.stage == 8) {
            arg0->unk15 = 0;
            func_80015D60(arg0, 0x18);
            func_8002217C(0x10, 0xFF, engine_obj.character_state.bytes[8]);
            engine_obj.character_state.bytes[8] = 1;
        }
        arg0->unk6 = 6;
    }
}

void func_8006E2E4(struct MainObj* arg0)
{
    if (abc_object.unkC == 0) {
        func_80015D60(arg0, 0x19);
        arg0->unk7E = 3;
        arg0->unk6 = 7;
        func_800921E8(7);
    }
}

void func_8006E334(struct MainObj* arg0)
{
    if (func_8009227C() == 0) {
        if (engine_obj.stage == 8) {
            s16* background_object = &background_objects[0].unk26;

            if (*background_object != 0x24B0) {
                *background_object -= 1;
            }
        }

        if (--arg0->unk7E == 0) {
            func_8001540C(0, 0xE, 0);
            arg0->unk7E = 3;
        }

        if (++arg0->unk5C == 0x30) {
            arg0->ext.main_54.unk89 = 0;
            arg0->ext.main_54.unk95 = 1;
            func_8006EAA8(arg0);
            arg0->unk5 = 3;
            arg0->unk6 = 0;
            arg0->ext.main_54.unk90--;
            func_80036B18();
        }
    }
}

void func_8006E414(struct MainObj* arg0)
{
    D_80100694[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E450);

void func_8006E594(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        func_8001540C(2, 0x88, arg0);
        arg0->unk20 = 0;
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        func_80015D60(arg0, 0x12);
        arg0->unk6 = 2;
    }
}

void func_8006E604(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_8006EA78(arg0);
        func_80015D60(arg0, 0xC);
        arg0->unk7C = 0x14;
        arg0->unk7E = 1;
        arg0->unk5 = 6;
        arg0->unk6 = 0;
        arg0->ext.main_54.unk86 = 1;
    }
}

void func_8006E674(struct MainObj* arg0)
{
    D_801006A0[arg0->unk6](arg0);
}

void func_8006E6B0(struct AnimatedObj* self)
{
    func_80015DC8(self);
    if (self->animation_step.fields.event != 0) {
        if (self->unk15 == 0) {
            self->x_vel.val = FIXED(-1.75);
        } else {
            self->x_vel.val = FIXED(1.75);
        }
        self->y_vel.val = FIXED(7.4375);
        self->unk28 = 0;
        self->unk2C = FIXED(0.21875);
        func_8002B694(self);
        func_8001540C(2, 0x81, self);
        func_80015D60(self, 2);
        self->unk6 = 1;
    }
}

void func_8006E750(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk24 == 0) {
        arg0->unk2C = FIXED(2);
        arg0->unk20 = 0;
        arg0->unk6 = 2;
        func_80015D60(arg0, 0x17);
        arg0->unk60 = 7;
        arg0->unk50 = (const u8*)&D_80100210;
        arg0->unk54 = (const u8*)&D_80100214;
    }
}

void func_8006E7CC(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if ((func_8002D724(
             PLAYER_OBJECT(arg0),
             (s16)((u16)arg0->x_pos.i.hi + arg0->unk68->unk0),
             (s16)(arg0->unk68->unk3 + ((u16)arg0->y_pos.i.hi + arg0->unk68->unk1) + 0x10))
            & 0xFF)
        == 0x38) {
        func_8001540C(2, 0x88, arg0);
        func_80028BAC(0x10, 4, 2);
        func_80015D60(arg0, 3);
        arg0->unk6 = 3;
    }
}

void func_8006E88C(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        arg0->unk60 = 5;
        arg0->unk24 = 0;
        arg0->unk2C = 0;
    }
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk50 = (const u8*)D_801001F8;
        arg0->unk54 = (const u8*)D_801001FC;
        func_80015D60(arg0, 0);
        func_8006EA78(arg0);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E920);

void func_8006EA78(struct MainObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

void func_8006EAA8(struct MainObj* arg0)
{
    u8* base;
    u8* current;
    u8* thresholds;
    u32 random;
    u8 index;
    s32 i;

    random = get_random();
    i = 0;
    random &= 0xF;
    index = arg0->ext.main_54.unk89;
    thresholds = D_801002B0;
    base = D_801002A4[index][0];
    thresholds += (index << 1) + index;
    current = base;

    for (; i < 3; i++) {
        if (random < *thresholds) {
            arg0->ext.main_54.unk90 = current;
            return;
        }
        current += 4;
        thresholds++;
    }

    arg0->ext.main_54.unk90 = base + i * 4;
}

void (*D_801005E4[])(struct MainObj*) = {
    func_8006BB70,
    func_8006BD1C,
    func_8006BFBC,
};
