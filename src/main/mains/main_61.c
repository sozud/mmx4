// MainObj, main_object_update_funcs[61]
// 8007872C..8007B90C
#include "common.h"
#include "func_tables.h"

void split_mushroom_update(struct MainObj* self)
{
    split_mushroom_state_funcs[self->state](self);
    CollisionRelated((struct PlayerObj*)self);
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007877C);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_800788E4);

void split_mushroom_death(struct MainObj* self)
{
    split_mushroom_death_funcs[self->unk5](self);
}

void split_mushroom_death_start(struct MainObj* self)
{
    g_Player.stun_timer = 0;
    player_start_script_action(0x14, g_Player.unk15);
    self->unk5 = 1;
    self->unk42 &= 0x7FFF;
    func_80015D60(self, 0x15);
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->unk61 = 0x19;
    func_8002B318(BASE_OBJECT(self), 0x60, 0x60);
}

void split_mushroom_death_explode(struct MainObj* self)
{
    struct EffectObj* effect;
    u8 value;

    if (--self->unk7C == 0) {
        self->unk5 = 2;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x1A;
            effect->x_pos.i.hi = self->x_pos.i.hi;
            effect->y_pos.i.hi = self->y_pos.i.hi;
            self->ext.main_61.data.effect = effect;
        }
    }

    func_8002B318(BASE_OBJECT(self), 0x60, 0x60);

    if (self->unk7E-- == 0) {
        self->unk42 ^= 0x8000;
        self->unk61 -= 5;
        if ((s8)self->unk61 >= 0x1A) {
            self->unk61 = 0;
        }
        value = self->unk61;
        if ((s8)self->unk61 < 5) {
            value = 5;
        }
        self->unk7E = (s8)value;
    }
}

void func_80078FA4(struct MainObj* arg0)
{
    struct EffectObj* effect = arg0->ext.main_61.data.effect;
    arg0->on_screen = 0;
    if (effect->active != 0) {
        if (effect->unk7 == 0) {
            if (arg0->unk7E-- == 0) {
                arg0->unk7E = 5;
                arg0->unk42 ^= 0x8000;
            }
            func_8002B318(BASE_OBJECT(arg0), 0x60, 0x60);
        }
    } else {
        arg0->ext.raw[0] = 0;
        arg0->ext.raw[1] = 0;
        arg0->ext.raw[2] = 0;
        arg0->ext.raw[3] = 0;
        arg0->ext.raw[4] = 0;
        arg0->ext.raw[5] = 0;
        engine_obj.enable_boss = 0;
        engine_obj.boss_ptr = NULL;
        if (engine_obj.stage != 0xC) {
            engine_obj.unkF = 0x10;
        } else {
            engine_obj.unkF = -0x80;
            engine_obj.character_state.bytes[engine_obj.checkpoint + 6] = 1;
            engine_obj.checkpoint += 9;
        }
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}

void split_mushroom_intro(struct MainObj* self)
{
    split_mushroom_intro_funcs[self->unk6](self);
}

void func_800790E8(struct MainObj* arg0)
{
    struct EffectObj* effect;

    if (engine_obj.stage == 3) {
        if (engine_obj.cur_character == 0 ? g_Player.y_pos.i.hi < 0x1CC : g_Player.y_pos.i.hi < 0x1CB) {
            effect = find_free_effect_obj();
            if (effect != NULL) {
                effect->active = 1;
                effect->id = 0x18;
                arg0->ext.main_61.data.effect = effect;
            }
            player_start_script_action(0x14, 0);
        } else {
            return;
        }
    } else {
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x18;
            arg0->ext.main_61.data.effect = effect;
        }
        player_start_script_action(0x14, 0x40);
    }
    arg0->unk6 = 1;
}

void split_mushroom_intro_drop(struct MainObj* self)
{
    if (*self->ext.main_61.data.script == 0) {
        s16* y_pos = &background_objects[g_Player.bg_offset].y_pos.i.hi;
        engine_obj.enable_boss = 1;
        engine_obj.unk25 = 0;
        engine_obj.boss_ptr = self;
        self->y_pos.i.hi = *y_pos - 0x20;
        self->ext.main_61.active = 1;
        func_8001540C(2, 0xA7, self);
        self->unk7C = 2;
        self->unk6 = 2;
    }
}

void split_mushroom_intro_bounce(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk7C == 0 && self->unk24 < 0) {
        func_80015930(2, 0xA7);
        func_80015D60(self, 3);
        self->unk7C = 0xFF;
    }
    if (self->unk70 & 8) {
        if (self->unk7C == 0xFF) {
            func_80015D60(self, 0xA);
            func_8001540C(2, 0xA6, self);
            self->unk6 = 3;
        } else {
            func_8001540C(2, 0xA8, self);
            self->unk24 = FIXED(6);
            self->unk7C--;
            func_8001540C(2, 0xA5, self);
        }
    }
    func_8002B694(ANIMATED_OBJECT(self));
}

void split_mushroom_intro_land(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        func_80015D60((struct Unk19*)self, 17);
        self->unk6 = 4;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_800793AC);

void split_mushroom_intro_start_health_bar(struct MainObj* self)
{
    if (abc_object.unkC == 0) {
        func_80015D60(self, 0);
        self->unk7E = 3;
        self->unk6 = 6;
        func_800921E8(2);
    }
}

void split_mushroom_intro_fill_health(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (func_8009227C() != 0) {
        return;
    }
    if (--self->unk7E == 0) {
        func_8001540C(0, 0xE, NULL);
        self->unk7E = 3;
    }
    if (++self->unk5C == 0x30) {
        func_80015D60(self, 2);
        self->unk5 = 7;
        self->unk6 = 0;
        player_end_script_action();
    }
}

void split_mushroom_stun(struct MainObj* self)
{
    split_mushroom_stun_funcs[self->unk6](self);
}

void split_mushroom_stun_start(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk2 == 0) {
        if (--self->unk7E == 0) {
            self->unk7E = 0xC;
            func_8001540C(2, 0xAB, self);
        }
    }
    if (self->animation_step.fields.event != 0) {
        self->unk60 = 5;
        self->unk68 = &D_80101CA8;
        self->unk7C = 0x1E;
        self->unk6 = 1;
    }
}

void split_mushroom_stun_wait(struct MainObj* self)
{
    s16 temp_v0;
    s8 state;

    temp_v0 = self->unk7C - 1;
    self->unk7C = temp_v0;
    if (temp_v0 != 0) {
        return;
    }

    if (self->ext.main_61.split != 0) {
        if (self->unk2 == 0) {
            if (self->ext.main_61.merge != 0) {
                self->unk6 = 3;
                return;
            }
        } else if (self->ext.main_61.partner->ext.main_61.merge != 0) {
            self->ext.main_61.blink_timer = 0xFF;
            self->unk15 = self->ext.main_61.partner->unk15;
            self->unk6 = 4;
            return;
        }

        self->unk2C = 0x3800;
        state = 5;
    } else {
        self->unk2C = 0x3800;
        state = 2;
    }

    self->unk20 = 0;
    self->unk28 = 0;
    self->unk24 = 0;
    self->unk6 = state;
}

void split_mushroom_stun_fall(struct MainObj* self)
{
    func_8002B694(ANIMATED_OBJECT(self));
    if (self->unk70 & 8) {
        self->unk61 = 0;
        func_80015D60(self, 2);
        self->unk5 = 7;
        self->unk6 = 0;
    }
}

void split_mushroom_stun_merge(struct MainObj* self)
{
    if (self->ext.main_61.split == 0) {
        self->ext.main_61.split_hits = 3;
        self->unk2C = FIXED(0.21875);
        self->ext.main_61.merge = 0;
        self->unk20 = 0;
        self->unk28 = 0;
        self->unk24 = 0;
        self->unk6 = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80079824);

void split_mushroom_stun_land(struct MainObj* self)
{
    func_8002B694(ANIMATED_OBJECT(self));
    if (self->unk70 & 8) {
        self->unk61 = 0;
        func_80015D60(self, 0);
        self->unk7C = 0x14;
        self->unk6 = 6;
    }
}

void split_mushroom_stun_split(struct MainObj* self)
{
    struct MainObj* parent;
    u16 timer;
    s16 backgroundY;
    int drawFlags;
    int one;

    timer = self->unk7C - 1;
    self->unk7C = timer;
    if ((timer << 16) == 0) {
        parent = self->ext.main_61.partner;
        if (parent->unk5 != 6) {
            backgroundY = background_objects[g_Player.bg_offset].x_pos.i.hi;
            if (self->x_pos.i.hi < backgroundY + 0xA0) {
                drawFlags = 0x40;
                self->unk15 = drawFlags;
            } else {
                self->unk15 = 0;
            }
        } else {
            drawFlags = parent->unk15 ^ 0x40;
            self->unk15 = drawFlags;
        }
        one = 1;
        self->ext.main_61.split = one;
        func_80015D60(self, 2);
        self->unk5 = 6;
        self->ext.main_61.split_done = one;
        self->ext.main_61.combo_count = 0;
        self->unk6 = 7;
    }
}

void split_mushroom_spore_rain(struct MainObj* self)
{
    split_mushroom_spore_rain_funcs[self->unk6](self);
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80079A8C);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80079B50);

void func_80079DD8(struct MainObj* arg0)
{
    s32 rnd;
    struct MainObj* clone;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0) {
        return;
    }
    func_8001540C(2, 0xAA, arg0);
    arg0->ext.main_61.split = 1;
    rnd = get_random();
    clone = find_free_main_obj();
    if (clone != NULL) {
        clone->unk5C = 0x7F;
        clone->active = 0x41;
        clone->id = 0x3D;
        clone->unk2 = 1;
        clone->unk60 = 5;
        clone->x_pos.val = arg0->x_pos.val;
        clone->y_pos.val = arg0->y_pos.val;
        clone->unk67 = 0;
        clone->collision_data = arg0->collision_data;
        clone->unk54 = arg0->unk54;
        clone->unk50 = arg0->unk50;
        clone->unk68 = arg0->unk68;
        clone->bg_offset = arg0->bg_offset;
        clone->animation_table = arg0->animation_table;
        clone->unk40 = arg0->unk40;
        clone->unk70 = 0;
        clone->sprite_frames = arg0->sprite_frames;
        clone->unk42 = arg0->unk42 & 0x7FFF;
        clone->unk16 = arg0->unk16;
        clone->unk5C = 0x30;
        if (!(rnd & 1)) {
            clone->unk15 = 0x40;
            clone->unk20 = FIXED(-2.75);
        } else {
            clone->unk15 = 0;
            clone->unk20 = FIXED(2.75);
        }
        clone->unk2C = FIXED(0.21875);
        clone->unk28 = 0;
        clone->unk24 = 0;
        clone->state = 1;
        clone->unk5 = 3;
        clone->unk6 = 3;
        func_80015D60(clone, 3);
        clone->ext.main_61.partner = arg0;
        arg0->ext.main_61.partner = clone;
        clone->ext.main_61.split = 1;
        clone->ext.main_61.blink_timer = 0x7F;
    }
    func_80015D60(arg0, 3);
    if (!(rnd & 1)) {
        arg0->unk15 = 0;
        arg0->unk20 = FIXED(2.75);
    } else {
        arg0->unk15 = 0x40;
        arg0->unk20 = FIXED(-2.75);
    }
    arg0->unk2C = FIXED(0.21875);
    arg0->unk28 = 0;
    arg0->unk24 = 0;
    arg0->ext.main_61.stunned = 0;
    arg0->unk6 = 3;
}

void split_mushroom_spore_rain_land(struct MainObj* self)
{
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk70 & 8) {
        func_80015D60(self, 0xA);
        func_8001540C(2, 0xA6, self);
        self->unk6 = 4;
    }
}

void split_mushroom_spore_rain_recover(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->ext.main_61.blink_timer = 0;
        func_80015D60(self, 0);
        self->unk7C = 0x1E;
        self->unk6 = 5;
    }
}

void split_mushroom_spore_rain_finish(struct MainObj* self)
{
    u16 timer;
    func_80015DC8(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if ((timer << 16) == 0) {
        self->unk24 = 0;
        if (self->unk2 == 0) {
            self->unk7C = 6;
            self->unk5 = 4;
            self->unk6 = 0;
        } else {
            self->unk7C = 6;
            func_80015D60(self, 2);
            self->unk5 = 4;
            self->unk6 = 2;
        }
    }
}

void split_mushroom_walk(struct MainObj* self)
{
    split_mushroom_walk_funcs[self->unk6](self);
}

void split_mushroom_walk_start(struct MainObj* self)
{
    s32 x_vel;

    func_80015D60(self, 1);
    if (self->unk15 == 0) {
        x_vel = -split_mushroom_walk_speeds[self->ext.main_61.speed_level];
    } else {
        x_vel = split_mushroom_walk_speeds[self->ext.main_61.speed_level];
    }
    self->unk20 = x_vel;
    self->unk6 = 1;
}

void split_mushroom_walk_move(struct MainObj* self)
{
    u16 timer;
    u16 timer2;

    func_8002B718(MOVING_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk15 == 0) {
        if ((self->unk70 & 2) == 0) {
            goto done;
        }
        timer = self->unk7C;
        self->unk15 = 0x40;
        timer--;
        self->unk7C = timer;
        if ((timer << 16) == 0) {
            goto destroy;
        }
        goto update;
    }

    if ((self->unk70 & 1) == 0) {
        goto done;
    }
    timer2 = self->unk7C;
    self->unk15 = 0;
    timer2--;
    self->unk7C = timer2;
    if ((timer2 << 16) != 0) {
        goto update;
    }

destroy:
    func_8007B6BC(ANIMATED_OBJECT(self));
    goto done;

update:
    func_80015D60(self, 2);
    self->unk6 = 2;

done:;
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A2B4);

void split_mushroom_walk_fall(struct MainObj* self)
{
    func_8002B694(ANIMATED_OBJECT(self));
    if ((self->unk7 == 0) && (self->unk24 < 0)) {
        func_80015D60(self, 3);
        self->unk7 = 1;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk70 & 8) {
        func_80015D60(self, 0xA);
        func_8001540C(2, 0xA6, self);
        self->unk6 = 4;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A444);

void split_mushroom_dash(struct MainObj* self)
{
    split_mushroom_dash_funcs[self->unk6](self);
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A4EC);

void func_8007A63C(struct MainObj* self)
{
    u16 resetValue;

    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));

    if (self->unk15 != 0) {
        goto state1;
    }
    if ((self->unk70 & 2) == 0) {
        goto done;
    }

    func_8001540C(2, 0xA8, self);
    split_mushroom_spawn_afterimage(self);
    if ((background_objects[g_Player.bg_offset].unk34 & 0x10) == 0) {
        func_80028B68(0x10, 8, 2);
    }

    if (--self->unk7E == 0) {
        goto complete;
    }
    self->unk15 = 0x40;
    resetValue = 0xA;
    goto reset;

state1:
    if ((self->unk70 & 1) == 0) {
        goto done;
    }

    func_8001540C(2, 0xA8, self);
    split_mushroom_spawn_afterimage(self);
    if ((background_objects[g_Player.bg_offset].unk34 & 0x10) == 0) {
        func_80028B68(0x10, 8, 2);
    }

    if (--self->unk7E != 0) {
        goto state_off;
    }

complete:
    self->unk15 ^= 0x40;
    func_80015D60(self, 3);
    self->unk20 = 0;
    self->unk24 = 0;
    self->unk28 = 0;
    self->unk2C = 0x3800;
    func_80015930(2, 0xA7);
    self->unk6 = 2;
    goto done;

state_off:
    resetValue = 0xA;
    self->unk15 = 0;
reset:
    self->unk7C = resetValue;
    self->unk6 = 0;
done:
    return;
}

void split_mushroom_dash_land(struct MainObj* self)
{
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk70 & 8) {
        func_80015D60(self, 0xA);
        func_8001540C(2, 0xA6, self);
        self->unk6 = 3;
    }
}

void split_mushroom_dash_recover(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk60 = 5;
        func_80015D60(self, 0);
        self->unk7C = 0x28;
        self->unk6 = 4;
    }
}

void split_mushroom_dash_finish(struct MainObj* self)
{
    s16 timer;

    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer != 0) {
        return;
    }
    if (self->unk2 == 0) {
        self->unk7C = 6;
        self->unk5 = 4;
        self->unk6 = 0;
        return;
    }
    self->unk7C = 6;
    func_80015D60(self, 2);
    self->unk5 = 4;
    self->unk6 = 2;
}

void split_mushroom_combo(struct MainObj* self)
{
    split_mushroom_combo_funcs[self->unk6](self);
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A96C);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007AB1C);

void split_mushroom_combo_swing(struct MainObj* self)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        func_8001540C(2, 0xAC, self);
        func_80015D60(self, 8);
        self->unk2C = FIXED(0.21875);
        self->unk20 = 0;
        self->unk28 = 0;
        self->unk24 = 0;
        self->unk6 = 3;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007AE2C);

void split_mushroom_combo_repeat(struct MainObj* self)
{
    s8 temp_v0_2;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        temp_v0_2 = self->ext.main_61.combo_count - 1;
        self->ext.main_61.combo_count = temp_v0_2;
        if (temp_v0_2 == 0) {
            func_80015D60(self, 0xF);
            self->unk6 = 6;
        } else {
            func_80015D60(self, 5);
            func_8001540C(2, 0xA7, self);
            self->unk7C = 0x28;
            self->unk6 = 0;
            self->unk7E = 1;
        }
    }
}

void split_mushroom_combo_sync(struct MainObj* self)
{
    self->unk7C--;
    if (self->unk7C == 0) {
        self->unk7C = 1;
        self->unk5 = 5;
        self->unk6 = 4;
        return;
    }

    if ((self->unk2 != 0) && ((*(u32*)&self->ext.main_61.partner->state & 0xFFFF00) == 0x50600)) {
        self->unk7C = 1;
        self->unk5 = 5;
        self->unk6 = 4;
        self->ext.main_61.partner->unk7C = 1;
        self->ext.main_61.partner->unk5 = 5;
        self->ext.main_61.partner->unk6 = 4;
    }
}

void split_mushroom_combo_end(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        func_80015D60((struct Unk19*)self, 2);
        self->unk6 = 7;
    }
}

void split_mushroom_combo_restart(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk7C = 1;
        self->unk6 = 0;
    }
}

void split_mushroom_wall_jump(struct MainObj* self)
{
    split_mushroom_wall_jump_funcs[self->unk6](self);
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007B1BC);

void split_mushroom_wall_jump_air(struct MainObj* self)
{
    s32 flags;

    func_8002B694(ANIMATED_OBJECT(self));
    if ((self->unk7 == 0) && (self->unk24 < 0)) {
        self->unk7 = 1;
        func_80015D60(self, 3);
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk15 == 0) {
        flags = self->unk70 & 2;
    } else {
        flags = self->unk70 & 1;
    }
    if (flags != 0) {
        self->ext.main_61.stunned = 0;
        func_80015D60(self, 6);
        self->unk7C = 0x28;
        self->unk6 = 2;
    }
}

void split_mushroom_wall_jump_cling(struct MainObj* self)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        self->unk68 = &D_80101CA8;
        func_80015D60(self, 7);
        self->unk7C = 0x28;
        self->unk6 = 3;
        self->unk7E = 6;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007B418);

void split_mushroom_wall_jump_turn(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk20 = 0;
        self->unk28 = 0;
        self->unk24 = 0;
        self->unk2C = FIXED(0.21875);
        self->unk15 ^= 0x40;
        func_80015D60(self, 3);
        self->unk6 = 5;
    }
}

void split_mushroom_wall_jump_land(struct MainObj* self)
{
    func_8002B694(ANIMATED_OBJECT(self));
    if (self->unk70 & 8) {
        func_8001540C(2, 0xA6, self);
        self->unk6 = 6;
    }
}

void split_mushroom_wall_jump_finish(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        func_80015D60(self, 2);
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void split_mushroom_face_player(struct AnimatedObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007B6BC);

void split_mushroom_load_palette(void)
{
    s32 i;
    u16* source;
    u16* destination;

    source = SP_PALETTE_BANK[53];
    if (engine_obj.stage == 3) {
        destination = SP_PALETTES[60];
    } else {
        destination = SP_PALETTES[44];
    }
    i = 0;
    do {
        *destination++ = *source++;
        i++;
    } while (i < 0x40);
    need_palette_load |= 1;
}

void split_mushroom_spawn_afterimage(struct MainObj* self)
{
    struct MainObj* source;
    struct MiscObj* temp_v0;

    source = self;
    temp_v0 = find_free_misc_obj();
    if (temp_v0 != 0) {
        temp_v0->active = 0x41;
        temp_v0->id = 0x16;
        temp_v0->unk2 = 8;
        temp_v0->unk15 = source->unk15;
        temp_v0->x_pos.i.hi = source->x_pos.i.hi;
        temp_v0->y_pos.i.hi = source->y_pos.i.hi;
        temp_v0->bg_offset = (u8)source->bg_offset;
        temp_v0->animation_table = (u32**)source->animation_table;
        temp_v0->unk40 = source->unk40;
        temp_v0->unk3C = (void*)source->sprite_frames;
        temp_v0->unk42 = source->unk42 & 0x7FFF;
        temp_v0->unk16 = 5;
        temp_v0->ext.misc_22.owner = source;
        temp_v0->ext.misc_22.timer = 0xA;
        func_80015D60(temp_v0, 0x19);
        temp_v0->state = 0;
        temp_v0->unk5 = 0;
        temp_v0->unk6 = 1;
    }
}

struct Unk_unk68 D_80101CA0 = { -11, -16, 20, 35 };

struct Unk_unk68 D_80101CA4 = { -16, -17, 30, 37 };

struct Unk_unk68 D_80101CA8 = { 0, 0, 8, 23 };

struct Unk_unk68 D_80101CAC = { -16, 0, 8, 23 };

s16 split_mushroom_hop_speeds[4] = {
    (s16)0x0040,
    (s16)0x003A,
    (s16)0x0034,
    (s16)0x0000,
};

s32 split_mushroom_walk_speeds[3] = {
    FIXED(3),
    FIXED(4.5),
    FIXED(6),
};

struct Unk_unk68 D_80101CC4[4] = {
    { 13, 0, 1, 0 },
    { 11, 0, 1, 1 },
    { 13, 0, 1, 2 },
    { 13, 1, -3, 1 },
};

struct Unk_unk68 D_80101CD4[8] = {
    { 3, 0, 1, 3 },
    { 5, 0, 1, 4 },
    { 4, 0, 1, 5 },
    { 3, 0, 1, 6 },
    { 3, 0, 1, 7 },
    { 5, 0, 1, 8 },
    { 4, 0, 1, 9 },
    { 3, 1, -7, 10 },
};

union AnimationStep D_80101CF4[] = {
    { 0x00010002 },
    { 0x0B010003 },
    { 0x0C010002 },
    { 0x0D000101 },
};

union AnimationStep D_80101D04[] = {
    { 0x0E000101 },
};

struct Unk_unk68 D_80101D08[9] = {
    { 3, 0, 1, 15 },
    { 3, 0, 1, 16 },
    { 3, 0, 1, 17 },
    { 3, 0, 1, 18 },
    { 3, 0, 1, 19 },
    { 3, 0, 1, 20 },
    { 3, 0, 1, 21 },
    { 3, 0, 1, 22 },
    { 3, 1, -7, 23 },
};

struct Unk_unk68 D_80101D2C[8] = {
    { 2, 0, 1, 24 },
    { 2, 0, 1, 25 },
    { 2, 0, 1, 26 },
    { 2, 0, 1, 27 },
    { 2, 0, 1, 28 },
    { 2, 0, 1, 29 },
    { 2, 0, 1, 30 },
    { 2, 0, -7, 31 },
};

union AnimationStep D_80101D4C[] = {
    { 0x20010003 },
    { 0x21000101 },
};

union AnimationStep D_80101D54[] = {
    { 0x22010004 },
    { 0x6E010003 },
    { 0x21010003 },
    { 0x75010018 },
    { 0x7601001B },
    { 0x76000101 },
};

union AnimationStep D_80101D6C[] = {
    { 0x73010003 },
    { 0x74010002 },
    { 0x73010009 },
    { 0x73000101 },
};

union AnimationStep D_80101D7C[] = {
    { 0x23000101 },
};

union AnimationStep D_80101D80[] = {
    { 0x24010002 },
    { 0x25010002 },
    { 0x26010002 },
    { 0x27010002 },
    { 0x28010002 },
    { 0x29010009 },
    { 0x29000101 },
};

union AnimationStep D_80101D9C[] = {
    { 0x2A010003 },
    { 0x2B010003 },
    { 0x2B000101 },
};

union AnimationStep D_80101DA8[] = {
    { 0x2C010003 },
    { 0x2D010003 },
    { 0x2E010003 },
    { 0x2F010003 },
    { 0x30010108 },
    { 0x31010108 },
    { 0x32010108 },
    { 0x31FD0108 },
};

union AnimationStep D_80101DC8[] = {
    { 0x33010108 },
    { 0x34010108 },
    { 0x35010108 },
    { 0x36010108 },
    { 0x37010007 },
    { 0x37000201 },
};

struct Unk_unk68 D_80101DE0[4] = {
    { 4, 0, 1, 56 },
    { 4, 0, 1, 57 },
    { 4, 0, 1, 58 },
    { 4, 1, -3, 59 },
};

union AnimationStep D_80101DF0[] = {
    { 0x10010003 },
    { 0x0F010004 },
    { 0x3C010006 },
    { 0x2A010002 },
    { 0x2B010003 },
    { 0x00000101 },
};

union AnimationStep D_80101E08[] = {
    { 0x3D010002 },
    { 0x3E010002 },
    { 0x3F010002 },
    { 0x40010002 },
    { 0x41010002 },
    { 0x42010002 },
    { 0x43010002 },
    { 0x44010002 },
    { 0x45010002 },
    { 0x46010002 },
    { 0x47010002 },
    { 0x48010002 },
    { 0x49010002 },
    { 0x4A010002 },
    { 0x4B010002 },
    { 0x4C010001 },
    { 0x4C000101 },
};

union AnimationStep D_80101E4C[] = {
    { 0x00010014 },
    { 0x4D010018 },
    { 0x4E010008 },
    { 0x4D010002 },
    { 0x4F010101 },
    { 0x4F01001F },
    { 0x50010001 },
    { 0x50000201 },
};

union AnimationStep D_80101E6C[] = {
    { 0x51010002 },
    { 0x52010102 },
    { 0x53010103 },
    { 0x54010103 },
    { 0x55010103 },
    { 0x56010103 },
    { 0x57010104 },
    { 0x58010104 },
    { 0x59010004 },
    { 0x5A010003 },
    { 0x5A000201 },
};

union AnimationStep D_80101E98[] = {
    { 0x5B010002 },
    { 0x5C010002 },
    { 0x5D010002 },
    { 0x5E010002 },
    { 0x5F010002 },
    { 0x60010002 },
    { 0x5B010002 },
    { 0x5C010002 },
    { 0x5D010002 },
    { 0x5E010002 },
    { 0x5F010002 },
    { 0x60010002 },
    { 0x61010002 },
    { 0x62010002 },
    { 0x63010002 },
    { 0x64010002 },
    { 0x65010002 },
    { 0x66010002 },
    { 0x61010002 },
    { 0x62010002 },
    { 0x63010002 },
    { 0x64010002 },
    { 0x65010002 },
    { 0x66010002 },
    { 0x67010002 },
    { 0x68010002 },
    { 0x69010002 },
    { 0x6A010002 },
    { 0x6B010002 },
    { 0x6C010002 },
    { 0x67010002 },
    { 0x68010002 },
    { 0x69010002 },
    { 0x6A010002 },
    { 0x6B010002 },
    { 0x6C010002 },
    { 0x6D010005 },
    { 0x6D000101 },
};

struct Unk_unk68 D_80101F30[4] = {
    { 4, 0, 1, 111 },
    { 4, 0, 1, 112 },
    { 4, 0, 1, 113 },
    { 4, 0, -3, 114 },
};

union AnimationStep D_80101F40[] = {
    { 0x77000101 },
};

struct Unk_unk68 D_80101F44[9] = {
    { 2, 0, 1, 15 },
    { 2, 0, 1, 16 },
    { 2, 0, 1, 17 },
    { 2, 0, 1, 18 },
    { 2, 0, 1, 19 },
    { 2, 0, 1, 20 },
    { 2, 0, 1, 21 },
    { 2, 0, 1, 22 },
    { 2, 1, -7, 23 },
};

struct Unk_unk68 D_80101F68[5] = {
    { 1, 0, 1, 120 },
    { 1, 0, 1, 121 },
    { 1, 0, 1, 122 },
    { 1, 0, 1, 123 },
    { 1, 0, -4, 124 },
};

union AnimationStep D_80101F7C[] = {
    { 0x7D010001 },
    { 0x7E010001 },
    { 0x7F010001 },
    { 0x80010001 },
    { 0x81FC0001 },
};

void* split_mushroom_animations[26] = {
    D_80101CC4,
    D_80101CD4,
    D_80101CF4,
    D_80101D04,
    D_80101D08,
    D_80101D2C,
    D_80101D4C,
    D_80101D54,
    D_80101D7C,
    D_80101D80,
    D_80101D9C,
    D_80101DA8,
    &D_80101DA8[4],
    D_80101DC8,
    D_80101DE0,
    D_80101DF0,
    D_80101E08,
    D_80101E4C,
    D_80101E6C,
    D_80101E98,
    D_80101F30,
    D_80101F40,
    D_80101F44,
    D_80101D6C,
    D_80101F68,
    D_80101F7C,
};

void (*split_mushroom_state_funcs[3])() = {
    func_8007877C,
    func_800788E4,
    split_mushroom_death,
};

void (*split_mushroom_step_funcs[8])() = {
    func_8009216C,
    split_mushroom_intro,
    split_mushroom_stun,
    split_mushroom_spore_rain,
    split_mushroom_walk,
    split_mushroom_dash,
    split_mushroom_combo,
    split_mushroom_wall_jump,
};

void (*split_mushroom_death_funcs[3])(struct MainObj*) = {
    split_mushroom_death_start,
    split_mushroom_death_explode,
    func_80078FA4,
};

void (*split_mushroom_intro_funcs[7])() = {
    func_800790E8,
    split_mushroom_intro_drop,
    split_mushroom_intro_bounce,
    split_mushroom_intro_land,
    func_800793AC,
    split_mushroom_intro_start_health_bar,
    split_mushroom_intro_fill_health,
};

void (*split_mushroom_stun_funcs[7])() = {
    split_mushroom_stun_start,
    split_mushroom_stun_wait,
    split_mushroom_stun_fall,
    split_mushroom_stun_merge,
    func_80079824,
    split_mushroom_stun_land,
    split_mushroom_stun_split,
};

void (*split_mushroom_spore_rain_funcs[6])() = {
    func_80079A8C,
    func_80079B50,
    func_80079DD8,
    split_mushroom_spore_rain_land,
    split_mushroom_spore_rain_recover,
    split_mushroom_spore_rain_finish,
};

void (*split_mushroom_walk_funcs[5])() = {
    split_mushroom_walk_start,
    split_mushroom_walk_move,
    func_8007A2B4,
    split_mushroom_walk_fall,
    func_8007A444,
};

void (*split_mushroom_dash_funcs[5])() = {
    func_8007A4EC,
    func_8007A63C,
    split_mushroom_dash_land,
    split_mushroom_dash_recover,
    split_mushroom_dash_finish,
};

void (*split_mushroom_combo_funcs[8])() = {
    func_8007A96C,
    func_8007AB1C,
    split_mushroom_combo_swing,
    func_8007AE2C,
    split_mushroom_combo_repeat,
    split_mushroom_combo_sync,
    split_mushroom_combo_end,
    split_mushroom_combo_restart,
};

void (*split_mushroom_wall_jump_funcs[7])() = {
    func_8007B1BC,
    split_mushroom_wall_jump_air,
    split_mushroom_wall_jump_cling,
    func_8007B418,
    split_mushroom_wall_jump_turn,
    split_mushroom_wall_jump_land,
    split_mushroom_wall_jump_finish,
};
