// MainObj, main_object_update_funcs[69]
// 80085F08..80088BA0
#include "common.h"

void func_80085F08(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_801047D4[arg0->state](arg0);
}

void func_80085F50(struct MainObj* arg0)
{
    D_801047E0[arg0->unk5](arg0);
}

void func_80085F8C(struct MainObj* arg0)
{
    struct EffectObj* effect;
    u8 value;

    value = arg0->unk2;
    arg0->ext.main_69.state.bytes.unk8C = value;
    if (value != 1) {
        effect = find_free_effect_obj();
        if (effect == NULL) {
            return;
        }
        effect->active = 1;
        effect->id = 0x18;
        arg0->ext.main_69.effect = effect;
        func_80036AE4(0x15, 0);
    }
    arg0->unk5++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086008);

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086124);

void func_80086268(struct MainObj* arg0)
{
    D_8010480C[arg0->unk5](arg0);
}

void func_800862A4(struct MainObj* arg0)
{
    D_80104814[arg0->unk6](arg0);
    CollisionRelated(PLAYER_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800862F4);

void func_800863E8(struct MainObj* self)
{
    u8 flags;

    func_8002B694(ANIMATED_OBJECT(self));
    flags = self->unk70;
    if (flags & 8) {
        func_8001540C(2, 0xD1, self);
        func_80015D60(self, 4);
        func_80028BAC(0x18, 2, 1);
        self->unk67 = 0;
        func_80015D60(self, 0x18);
        self->unk6++;
        return;
    }
    if (flags & 3) {
        self->unk20 = 0;
    }
    is_on_screen(BASE_OBJECT(self));
}

void func_80086488(struct MainObj* arg0)
{
    arg0->unk6++;
}

void func_8008649C(struct MainObj* arg0)
{
    if (engine_obj.cur_character == 0) {
        func_8002217C(0x33, 4, 0);
    } else {
        func_8002217C(0x2E, 5, 0);
    }
    arg0->unk6++;
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800864FC(struct MainObj* arg0)
{
    if (abc_object.unkC == 0) {
        arg0->unk7C = 0x7F;
        arg0->unk7E = 0x19;
        arg0->unk61 = 0x19;
        arg0->unk6++;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_8008654C);

void func_80086640(struct MainObj* self)
{
    struct MainObj* linked_object;

    linked_object = (struct MainObj*)self->ext.main_69.effect;
    self->on_screen = 0;
    if (linked_object->active != 0) {
        if (linked_object->unk7 == 0) {
            if (self->unk7E-- == 0) {
                self->unk7E = 5;
                self->unk42 ^= 0x8000;
            }
            is_on_screen(BASE_OBJECT(self));
        }
    } else {
        self->ext.main_69.effect = NULL;
        self->ext.main_69.linked_object = NULL;
        self->ext.main_69.script = NULL;
        self->ext.main_69.state.word = 0;
        self->ext.main_69.unk90 = 0;
        self->ext.main_69.unk94 = 0;
        func_80036B18();
        engine_obj.enable_boss = 0;
        engine_obj.boss_ptr = NULL;
        engine_obj.unkF = 1;
        ZeroObjectState(OBJECT_HEADER(self));
    }
}

void func_80086704(struct MainObj* arg0)
{
    D_80104830[arg0->unk6](arg0);
}

void func_80086740(struct MainObj* arg0)
{
    func_80036AE4(0x15, 0);
    func_80015D60(arg0, 6);
    arg0->unk7C = 0x20;
    arg0->unk20 = 0;
    arg0->unk28 = FIXED(1);
    arg0->unk24 = 0;
    arg0->unk2C = 0;
    arg0->unk54 = NULL;
    arg0->unk50 = NULL;
    arg0->unk6++;
    func_8001540C(2, 0xD3, arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800867C4(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (--arg0->unk7C == 0) {
        arg0->on_screen = 0;
        arg0->unk7C = 0x20;
        arg0->unk6++;
    } else {
        arg0->unk20 += arg0->unk28;
        if (arg0->unk7C & 1) {
            arg0->x_pos.val += arg0->unk20;
        } else {
            arg0->x_pos.val -= arg0->unk20;
        }
        is_on_screen(BASE_OBJECT(arg0));
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086860);

void func_80086900(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        func_80015D60(self, 0x18);
        func_80088974(self);
        func_8002217C(0x23, 3, 0);
        self->unk6++;
    } else {
        func_80015DC8(ANIMATED_OBJECT(self));
        self->unk20 += self->unk28;
        if (self->unk7C & 1) {
            self->x_pos.val += self->unk20;
        } else {
            self->x_pos.val -= self->unk20;
        }
    }
    is_on_screen(BASE_OBJECT(self));
}

void func_800869BC(struct MainObj* arg0)
{
    if (abc_object.unkC == 0) {
        arg0->unk6++;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800869F8(struct MainObj* arg0)
{
    func_80015D60(arg0, 6);
    arg0->unk7C = 0x20;
    arg0->unk20 = 0;
    arg0->unk28 = FIXED(1);
    arg0->unk24 = 0;
    arg0->unk2C = 0;
    arg0->unk54 = NULL;
    arg0->unk50 = NULL;
    arg0->unk6++;
    func_8001540C(2, 0xD3, arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

void func_80086A6C(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (--arg0->unk7C == 0) {
        arg0->on_screen = 0;
        arg0->unk7C = 0x20;
        arg0->unk6++;
    } else {
        arg0->unk20 += arg0->unk28;
        if (arg0->unk7C & 1) {
            arg0->x_pos.val += arg0->unk20;
        } else {
            arg0->x_pos.val -= arg0->unk20;
        }
        is_on_screen(BASE_OBJECT(arg0));
    }
}

void func_80086B08(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        func_80036B18();
        engine_obj.enable_boss = 0;
        engine_obj.boss_ptr = 0;
        engine_obj.unkF = 1;
    }
}

void func_80086B60(struct MainObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
}

void func_80086B74(struct MainObj* arg0)
{
    D_80104850[arg0->unk6](arg0);
}

void func_80086BB0(struct MainObj* arg0)
{
    D_80104858[arg0->unk7](arg0);
    CollisionRelated(PLAYER_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086C00);

void func_80086C70(struct PlayerObj* self)
{
    s16 timer;
    struct VisualObj* visual_obj;

    timer = (s16)self->input.buttons.held;
    if (timer == 0) {
        visual_obj = find_free_visual_obj();
        if (visual_obj != NULL) {
            visual_obj->active = 0x41;
            visual_obj->id = 0x1E;
            visual_obj->unk2 = 0x10;
            visual_obj->unk50 = self;
            visual_obj->unk54 = 0x20;
            self->input.buttons.held = 0x20;
            func_80015D60(self, 0x16);
            self->unk7 = (u8)self->unk7 + 1;
        }
    } else {
        self->input.buttons.held = timer - 1;
    }
}

void func_80086D04(struct MainObj* arg0)
{
    arg0->on_screen ^= 1;
    if (arg0->on_screen != 0) {
        is_on_screen(BASE_OBJECT(arg0));
    }
    if (--arg0->unk7C == 0) {
        arg0->ext.main_69.linked_object->unk5C = 1;
        engine_obj.enable_boss = 1;
        arg0->unk7++;
    }
}

void func_80086D84(struct MainObj* arg0)
{
    u16 value;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 1) {
        func_8001540C(2, 0xD5, arg0);
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 0);
        value = 0x1E;
        if (engine_obj.cur_character == 0) {
            value = 0x25;
        }
        func_8002217C(value, 0xFFU, ENGINE_UNK2E);
        ENGINE_UNK2E = 1;
        arg0->unk7++;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_80086E2C(struct MainObj* arg0)
{
    if (abc_object.unkC == 0) {
        arg0->unk7E = 3;
        arg0->unk7++;
        func_800921E8(8);
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_80086E80(struct MainObj* self)
{
    s16 timer;

    if (func_8009227C() == 0) {
        timer = self->unk7E - 1;
        self->unk7E = timer;
        if (timer == 0) {
            func_8001540C(0, 0xE, NULL);
            self->unk7E = 3;
        }
        if (++self->unk5C == 0x30) {
            func_800889DC(self);
            self->unk5 = 3;
            self->unk6 = 0;
            self->unk7 = 0;
            self->unk7E = 0;
            func_80036B18();
        }
    }
    is_on_screen(BASE_OBJECT(self));
}

void func_80086F28(struct MainObj* arg0)
{
    D_80104870[arg0->unk7](arg0);
    CollisionRelated(PLAYER_OBJECT(arg0));
}

void func_80086F78(struct MainObj* self)
{
    s16 object_x;
    s32 delta;

    object_x = self->x_pos.i.hi;
    delta = g_Player.x_pos.i.hi - object_x;
    if ((delta >= 0) ? (delta < 0xB1)
                     : ((object_x - g_Player.x_pos.i.hi) < 0xB1)) {
        func_80036AE4(0x14, 0x40);
        background_objects[0].unk24 = 0x2C0;
        background_objects[0].unk26 = 0x2A0;
        self->unk7C = 0x78;
        self->unk7++;
    }
}

void func_8008700C(struct MainObj* arg0)
{
    struct QuadObj* quad;

    if (--arg0->unk7C == 0) {
        quad = find_free_quad_obj();
        if (quad != NULL) {
            quad->active = 1;
            quad->id = 0xE;
            quad->unk2 = 0;
            quad->unk5C = PLAYER_OBJECT(arg0);
            arg0->unk7C = 0x3C;
            arg0->unk7++;
        }
    }
}

void func_80087088(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        func_8002217C(0x22, 0xFF, ENGINE_UNK2E);
        ENGINE_UNK2E = 1;
        arg0->unk7++;
    }
}

void func_800870FC(struct MainObj* arg0)
{
    struct QuadObj* quad;

    if (abc_object.unkC == 0) {
        quad = find_free_quad_obj();
        if (quad != NULL) {
            quad->active = 1;
            quad->id = 0xE;
            quad->unk2 = 1;
            quad->unk5C = PLAYER_OBJECT(arg0);
            arg0->unk7C = 0x3C;
            arg0->unk7++;
        }
    }
}

void func_80087168(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk7C = 0x30;
        func_80015D60(arg0, 2);
        arg0->unk7++;
    }
}

void func_800871C4(struct MainObj* arg0)
{
    if (--arg0->unk7C != 0) {
        if (arg0->on_screen ^= 1) {
            is_on_screen(BASE_OBJECT(arg0));
        }
    } else {
        func_80015D60(arg0, 1);
        engine_obj.enable_boss = 1;
        arg0->unk7++;
        func_800921E8(8);
    }
}

void func_80087254(struct MainObj* arg0)
{
    struct EffectObj* effect;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 2);
        arg0->unk7E = 3;
        arg0->unk7++;
        func_8002B560(2, 0xF);
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 0x41;
            effect->id = 3;
            effect->unk2 = 0;
            arg0->unk7C = 1;
        }
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800872E8(struct MainObj* arg0)
{
    struct EffectObj* effect;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 0x41;
            effect->id = 2;
            effect->unk2 = 0x10;
        }
        arg0->unk7++;
    }
}

void func_80087364(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (func_8009227C() == 0) {
        if (--arg0->unk7E == 0) {
            func_8001540C(0, 0xE, NULL);
            arg0->unk7E = 3;
        }
        if (++arg0->unk5C == 0x30) {
            func_800889DC(arg0);
            arg0->unk5 = 3;
            arg0->unk6 = 0;
            arg0->unk7 = 0;
            arg0->unk7E = 0;
            func_80036B18();
        }
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_80087414(struct MainObj* arg0)
{
    D_80104894[arg0->unk6](arg0);
    func_80088974(arg0);
    is_on_screen((struct BaseObj*)arg0);
}

void func_8008746C(struct MainObj* arg0)
{
    u8 value;

    if (*arg0->ext.main_69.script == 0xFF) {
        func_800889DC(arg0);
    }
    arg0->unk54 = &D_801044FC;
    arg0->unk50 = &D_80104500;
    arg0->collision_data = (const u16*)D_80108084;
    arg0->ext.main_69.state.bytes.unk8D = 0;
    value = *arg0->ext.main_69.script;
    if (value == 3) {
        func_80015D60(arg0, 2);
        arg0->unk7C = 0x3C;
        arg0->unk6++;
    } else {
        arg0->unk5 = value;
        arg0->unk6 = 0;
    }
    arg0->ext.main_69.script++;
}

void func_8008752C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    arg0->unk7C--;
    if (arg0->unk7C <= 0) {
        arg0->unk6 = 0;
    } else if ((s8)func_800888D0(arg0)) {
        arg0->unk7C = 0x10;
        arg0->unk6++;
    }
}

void func_8008759C(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 9);
        arg0->collision_data = (const u16*)D_801060F0;
        arg0->unk7C = 0x3C;
        arg0->unk6++;
    }
}

void func_80087604(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->collision_data = (const u16*)D_80108084;
        arg0->ext.main_69.state.bytes.unk8D = 0;
        arg0->unk6 = 0;
    }
}

void func_8008765C(struct MainObj* arg0)
{
    D_801048A4[arg0->unk6](arg0);
}

void func_80087698(struct MainObj* arg0)
{
    func_80015D60(arg0, 6);
    arg0->unk7C = 0x20;
    arg0->unk20 = 0;
    arg0->unk28 = FIXED(1);
    arg0->unk24 = 0;
    arg0->unk2C = 0;
    arg0->unk54 = NULL;
    arg0->unk50 = NULL;
    func_8001540C(2, 0xD3, arg0);
    arg0->unk6++;
}

void func_80087708(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (--arg0->unk7C == 0) {
        arg0->on_screen = 0;
        arg0->unk7C = 0x28;
        arg0->unk6++;
    } else {
        arg0->unk20 += arg0->unk28;
        if (arg0->unk7C & 1) {
            arg0->x_pos.val += arg0->unk20;
        } else {
            arg0->x_pos.val -= arg0->unk20;
        }
        is_on_screen(BASE_OBJECT(arg0));
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800877A4);

void func_80087860(struct MainObj* arg0)
{
    struct ShotObj* shot_obj;
    s16 timer;

    if (arg0->animation_step.fields.relative_step == 0) {
        timer = arg0->unk7C - 1;
        arg0->unk7C = timer;
        if (timer == 0) {
            arg0->unk54 = &D_80104508;
            arg0->unk50 = &D_80104504;
            arg0->unk5 = 3;
            arg0->unk6 = 0;
        }
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.event != 0) {
            shot_obj = find_free_shot_obj();
            if (shot_obj != 0) {
                shot_obj->active = 0x41;
                shot_obj->id = 0x2D;
                shot_obj->unk2 = 0x40;
                shot_obj->unk7C = WEAPON_OBJECT(arg0);
                shot_obj->unk8C.object = OBJECT_HEADER(arg0);
            }
        }
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_80087928(struct MainObj* arg0)
{
    D_801048B4[arg0->unk6](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
    is_on_screen((struct BaseObj*)arg0);
}

void func_80087980(struct MainObj* arg0)
{
    func_800889A4(BASE_OBJECT(arg0));
    arg0->unk28 = FIXED(-0.1875);
    arg0->unk7C = 0x1E;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk2C = 0;
    arg0->unk54 = NULL;
    arg0->unk50 = NULL;
    arg0->unk4B = 1;
    func_80015D60(arg0, 6);
    func_8001540C(2, 0xD2, arg0);
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80087A00);

void func_80087AF8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk15 != 0) {
        if (arg0->unk20 < 0) {
            arg0->unk20 = 0;
        }
    } else if (arg0->unk20 > 0) {
        arg0->unk20 = 0;
    }
    if (arg0->unk20 == 0) {
        arg0->unk54 = (const u8*)&D_801044FC;
        arg0->unk50 = (const u8*)&D_80104500;
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_80087B98(struct MainObj* arg0)
{
    D_801048C0[arg0->unk6](arg0);
    is_on_screen((struct BaseObj*)arg0);
}

void func_80087BE8(struct MainObj* arg0)
{
    func_80015D60(arg0, 4);
    func_8001540C(2, 0xDA, arg0);
    arg0->unk54 = (const u8*)&D_80104508;
    arg0->unk50 = (const u8*)&D_80104504;
    if (arg0->ext.main_69.state.bytes.unk8C == 0) {
        arg0->ext.main_69.state.bytes.unk8F = 0x14;
    } else {
        arg0->ext.main_69.state.bytes.unk8F = 0x28;
    }
    arg0->unk7C = arg0->ext.main_69.state.bytes.unk8F;
    arg0->unk6++;
}

void func_80087C70(struct MainObj* arg0)
{
    struct ShotObj* shot;

    if (arg0->animation_step.fields.relative_step == 0) {
        if (--arg0->unk7C == 0) {
            func_80015D60(arg0, 5);
            func_8001540C(2, 0xDA, arg0);
            arg0->unk7C = (s8)arg0->ext.main_69.state.bytes.unk8F;
            arg0->unk6++;
        }
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.event != 0) {
            shot = find_free_shot_obj();
            if (shot != 0) {
                shot->active = 0x41;
                shot->id = 0x2D;
                shot->unk2 = 0;
                shot->unk7C = WEAPON_OBJECT(arg0);
                shot->unk8C.object = OBJECT_HEADER(arg0);
            }
        }
    }
}

void func_80087D3C(struct MainObj* arg0)
{
    struct ShotObj* shot;

    if (arg0->animation_step.fields.relative_step == 0) {
        if (--arg0->unk7C == 0) {
            func_80015D60(ANIMATED_OBJECT(arg0), 4);
            func_8001540C(2, 0xDA, arg0);
            arg0->unk7C = arg0->ext.main_69.state.bytes.unk8F;
            arg0->unk6++;
        }
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.event != 0) {
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0x2D;
                shot->unk2 = 1;
                shot->unk7C = WEAPON_OBJECT(arg0);
                shot->unk8C.object = OBJECT_HEADER(arg0);
            }
        }
    }
}

void func_80087E0C(struct MainObj* arg0)
{
    struct ShotObj* shot;
    s16 timer;

    if (arg0->animation_step.fields.relative_step == 0) {
        timer = arg0->unk7C - 1;
        arg0->unk7C = timer;
        if (timer == 0) {
            arg0->unk54 = &D_801044FC;
            arg0->unk50 = &D_80104500;
            func_80015D60(arg0, 0x17);
            arg0->unk7C = 0x28;
            arg0->unk6++;
        }
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.event != 0) {
            shot = find_free_shot_obj();
            if (shot != 0) {
                shot->active = 0x41;
                shot->id = 0x2D;
                shot->unk2 = 0;
                shot->unk7C = WEAPON_OBJECT(arg0);
                shot->unk8C.object = OBJECT_HEADER(arg0);
            }
        }
    }
}

void func_80087ED4(struct MainObj* arg0)
{
    arg0->unk7C--;
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 2);
        arg0->unk6++;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80087F30(struct MainObj* arg0)
{
    s16 timer;

    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
}

void func_80087F78(struct MainObj* arg0)
{
    D_801048D8[arg0->unk6](arg0);
}

void func_80087FB4(struct MainObj* arg0)
{
    func_80015D60(arg0, 6);
    func_8001540C(2, 0xD3, arg0);
    arg0->unk7C = 0x20;
    arg0->unk20 = 0;
    arg0->unk28 = FIXED(1);
    arg0->unk24 = 0;
    arg0->unk2C = 0;
    arg0->unk54 = NULL;
    arg0->unk50 = NULL;
    arg0->unk6++;
}

void func_80088020(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (--arg0->unk7C == 0) {
        arg0->on_screen = 0;
        arg0->unk7C = 0x28;
        arg0->unk6++;
    } else {
        arg0->unk20 += arg0->unk28;
        if (arg0->unk7C & 1) {
            arg0->x_pos.val += arg0->unk20;
        } else {
            arg0->x_pos.val -= arg0->unk20;
        }
        is_on_screen(BASE_OBJECT(arg0));
    }
}

void func_800880BC(struct MainObj* self)
{
    s16 timer;
    u16 background;

    timer = self->unk7C - 1;
    self->unk7C = timer;
    if ((timer << 0x10) == 0) {
        background = background_objects[0].unk1E;
        self->unk7C = 0x14;
        self->unk20 = FIXED(32);
        self->unk28 = (s32)0xFFFF0000;
        self->x_pos.i.hi = (s16)(background + 0xA0);
        func_8001540C(2, 0xD3, self);
        self->unk6++;
    }
}

void func_80088140(struct MainObj* self)
{
    u16 timer;
    s32 delta;

    timer = self->unk7C - 1;
    self->unk7C = timer;
    if ((timer << 0x10) == 0) {
        self->unk54 = &D_801044FC;
        self->unk50 = &D_80104500;
        func_80015D60(self, 7);
        self->unk6 = (u8)self->unk6 + 1;
    } else {
        func_80015DC8(ANIMATED_OBJECT(self));
        delta = self->unk20 + self->unk28;
        self->unk20 = delta;
        if (self->unk7C & 1) {
            self->x_pos.val += delta;
        } else {
            self->x_pos.val -= delta;
        }
    }
    is_on_screen(BASE_OBJECT(self));
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800881F8);

void func_80088338(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->ext.main_69.linked_object->unk5C = 1;
        func_8002B560(0x25, 0x10);
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        func_8001540C(2, 0xD6, arg0);
        arg0->unk6++;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800883CC);

void func_800884D0(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 8);
        arg0->unk6++;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_80088530(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 2);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_80088584(struct MainObj* arg0)
{
    D_801048FC[arg0->unk6](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
    is_on_screen((struct BaseObj*)arg0);
}

void func_800885DC(struct MainObj* arg0)
{
    arg0->unk24 = FIXED(6.5);
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = FIXED(0.2578125);
    func_80015D60(arg0, 3);
    func_8001540C(2, 0xD0, arg0);
    arg0->unk54 = (const u8*)&D_80104510;
    arg0->unk50 = (const u8*)&D_8010450C;
    arg0->unk6++;
}

void func_80088658(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 1) {
        arg0->unk6++;
    }
}

void func_800886A0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        arg0->unk67 = 1;
        arg0->unk7C = 0;
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800886F0);

void func_800887DC(struct MainObj* arg0)
{
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 1) {
        func_8001540C(2, 0xD5, arg0);
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x2D;
            shot->unk2 = 0x50;
            shot->timer = 1;
            shot->unk7C = WEAPON_OBJECT(arg0);
            shot->unk8C.word = (s32)arg0;
        }
        func_8001540C(2, 0xD9, arg0);
        arg0->unk7C = 0x50;
        arg0->unk6++;
    }
}

void func_8008888C(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 3;
        arg0->unk54 = (const u8*)&D_801044FC;
        arg0->unk6 = 0;
        arg0->unk50 = (const u8*)&D_80104500;
    }
}

s32 func_800888D0(struct MainObj* arg0)
{
    volatile struct WeaponObj* weapon;
    s32 active;
    s32 i;
    s32 x_diff;

    i = 0;
    weapon = weapon_objects;
    active = weapon_objects->active;
    do {
        if (active != 0 && weapon->unk50 != 0) {
            x_diff = (u16)weapon->x_pos.i.hi - (u16)arg0->x_pos.i.hi;
            if (arg0->unk15 == 0) {
                if ((x_diff << 16) <= 0 && weapon->x_vel.val >= 0) {
                    return 1;
                }
            } else if ((x_diff << 16) >= 0 && weapon->x_vel.val <= 0) {
                return 1;
            }
        }
        i += 1;
    } while ((u32)(i & 0xFF) < 0x10U);

    return 0;
}

void func_80088974(struct MainObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

void func_800889A4(struct BaseObj* arg0)
{
    s16 right_edge = background_objects[0].x_pos.i.hi + 0xB0;

    if (arg0->x_pos.i.hi < right_edge) {
        arg0->unk15 = 0x40;
    } else {
        arg0->unk15 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800889DC);

void func_80088AD0(struct MainObj* arg0)
{
    u8 i;
    struct VisualObj* visual_obj;
    struct VisualObj* previous;

    for (i = 0; i < 3; i++) {
        visual_obj = func_8002AF4C(NULL, 1);
        if (visual_obj != NULL) {
            visual_obj->active = 0x41;
            visual_obj->id = 5;
            visual_obj->unk2 = i;
            visual_obj->bg_offset = g_Player.bg_offset;
            visual_obj->unk40 = arg0->unk40;
            visual_obj->unk3C = (void*)arg0->sprite_frames;
            visual_obj->animation_table = (u32**)arg0->animation_table;
            visual_obj->unk42 = arg0->unk42;
            visual_obj->unk5C.owner = PLAYER_OBJECT(arg0);
            visual_obj->unk16 = 6;
            if (i != 0) {
                visual_obj->unk50 = PLAYER_OBJECT(previous);
            } else {
                visual_obj->unk50 = PLAYER_OBJECT(arg0);
            }
        }
        previous = visual_obj;
    }
}
