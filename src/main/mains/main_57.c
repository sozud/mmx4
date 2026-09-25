// MainObj, main_object_update_funcs[57]
// 80072194..800743FC
#include "common.h"

extern u8** frost_walrus_scripts[];
extern u8 frost_walrus_script_weights[][4];

void frost_walrus_choose_script(struct MainObj* arg0);

void frost_walrus_update(struct MainObj* self)
{
    frost_walrus_state_funcs[self->state](self);
    CollisionRelated(PLAYER_OBJECT(self));
    if (!(g_Player.unk5C & 0x7F)) {
        frost_walrus_set_floor_tiles(0x38);
    }
}

void frost_walrus_start(struct MainObj* self)
{
    frost_walrus_start_funcs[self->unk5](self);
}

void frost_walrus_start_warning(struct MainObj* self)
{
    struct EffectObj* effect = find_free_effect_obj();

    if (effect != NULL) {
        effect->active = 1;
        effect->id = 0x18;
        self->ext.main_57.effect = effect;
        func_80036AE4(0x14, 0x40);
        self->unk5++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_800722A0);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072418);

void frost_walrus_reset(struct MainObj* self)
{
    self->unk5 = 3;
    self->unk6 = 0;
}

void frost_walrus_death(struct BarObj* self)
{
    frost_walrus_death_funcs[self->unk5](self);
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072628);

void frost_walrus_death_explode(struct MainObj* self)
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
            self->ext.main_57.effect = effect;
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

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_800727C0);

void frost_walrus_intro(struct MainObj* self)
{
    frost_walrus_intro_funcs[self->unk6](self);
}

void frost_walrus_intro_walk(struct MainObj* self)
{
    s32 x_vel = FIXED(-0.75);

    self->unk6++;
    if (self->unk15 != 0) {
        x_vel = FIXED(0.75);
    }
    self->unk20 = x_vel;
    self->unk24 = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    engine_obj.enable_boss = 1;
    func_80015D60(self, 0x26);
}

void frost_walrus_intro_approach(struct MainObj* self)
{
    s16 temp_a0;
    s32 temp_v0;

    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        func_80028BAC(0x18, 2, 1);
        func_8001540C(2, 0x91, self);
    }

    temp_a0 = self->x_pos.i.hi;
    temp_v0 = temp_a0 - g_Player.x_pos.i.hi;
    if (temp_v0 >= 0) {
        if (temp_v0 < 0xC1) {
            goto update;
        }
        return;
    }

    if (g_Player.x_pos.i.hi - temp_a0 < 0xC1) {
    update:
        self->unk20 = 0;
        func_80015D60(self, 1);
        self->unk6++;
    }
}

void frost_walrus_intro_roar(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 3) {
        func_8001540C(2, 0x92, self);
    }
    if (self->animation_step.fields.relative_step == 0) {
        func_80015D60(self, 0x4);
        self->unk7C = 0x50;
        self->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072A84);

void frost_walrus_intro_start_health_bar(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (abc_object.unkC == 0) {
        self->unk7E = 3;
        self->unk6++;
        func_800921E8(1);
    }
}

void frost_walrus_intro_fill_health(struct MainObj* self)
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
        frost_walrus_choose_script(self);
        self->unk5 = 3;
        self->unk6 = 0;
        self->unk7E = 0;
        func_80036B18();
    }
}

void frost_walrus_think(struct MainObj* self)
{
    frost_walrus_think_funcs[self->unk6](self);
    frost_walrus_face_player(self);
}

void frost_walrus_think_next(struct MainObj* self)
{
    u8 value;

    if (*self->ext.main_57.script == 0xFF) {
        frost_walrus_choose_script(self);
    }

    value = *self->ext.main_57.script;
    if ((value & 0xFF) == 3) {
        func_80015D60(self, 0x1A);
        self->unk7C = 0x1E;
        self->unk6++;
    } else {
        self->unk5 = value;
        self->unk6 = 0;
    }

    self->ext.main_57.script++;
}

void frost_walrus_think_pause(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7C <= 0) {
        self->unk6 = 0;
    }
}

void frost_walrus_charge(struct MainObj* self)
{
    frost_walrus_charge_funcs[self->unk6](self);
}

void frost_walrus_charge_start(struct MainObj* self)
{
    s32 var_v1;

    self->unk24 = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    self->unk6 = (u8)self->unk6 + 1;
    if (self->ext.main_57.tusks_broken != 0) {
        func_80015D60(self, 0x17);
        var_v1 = -0x18000;
        if (self->unk15 != 0) {
            var_v1 = 0x18000;
        }
        self->unk54 = (u8*)&D_80101340;
        self->unk20 = var_v1;
        self->unk50 = (u8*)&D_80101348;
        func_8001540C(2, 0x93, self);
        self->unk6 = 3;
        return;
    }
    self->unk54 = (u8*)&D_8010133C;
    self->unk50 = (u8*)&D_80101344;
    func_80015D60(self, 1);
}

void frost_walrus_charge_windup(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 3) {
        func_8001540C(2, 0x92, self);
    }
    if (self->animation_step.fields.event == 2) {
        func_80015D60(self, 2);
        self->unk6++;
    }
}

void frost_walrus_charge_run(struct MainObj* self)
{
    s32 value;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        value = FIXED(-3);
        if (self->unk15 != 0) {
            value = FIXED(3);
        }
        self->unk54 = (const u8*)&D_80101340;
        self->unk20 = value;
        self->unk50 = (const u8*)&D_80101348;
        func_8001540C(2, 0x93, self);
        self->unk6++;
    }
}

void frost_walrus_charge_slide(struct MainObj* self)
{
    s32 mask;
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    mask = 2;
    if (self->unk15 != 0) {
        mask = 1;
    }
    if (mask & self->unk70) {
        frost_walrus_set_floor_tiles(0x39);
        func_80028B68(0x1E, 4, 1);
        func_8001540C(2, 0x90, self);
        self->unk7C = 0x28;
        self->unk6++;
    }
}

void frost_walrus_charge_recover(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7C <= 0) {
        self->unk54 = (const u8*)&D_8010133C;
        self->unk50 = (const u8*)&D_80101344;
        frost_walrus_set_floor_tiles(0x38);
        func_80015D60(self, 3);
        self->unk6++;
    }
}

void frost_walrus_charge_finish(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        if (self->ext.main_57.tusks_broken == 0) {
            func_80015D60(self, 0);
        }
        frost_walrus_face_player(self);
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void frost_walrus_leap(struct MainObj* self)
{
    frost_walrus_leap_funcs[self->unk6](self);
}

void frost_walrus_leap_start(struct MainObj* self)
{
    s32 x_vel = FIXED(-3);

    if (self->unk15 != 0) {
        x_vel = FIXED(3);
    }
    self->unk24 = FIXED(6.5);
    self->unk2C = FIXED(0.2578125);
    self->unk54 = (const u8*)&D_8010133C;
    self->unk20 = x_vel;
    self->unk28 = 0;
    self->unk50 = (const u8*)&D_80101344;
    func_80015D60(self, 1);
    self->ext.main_57.leap_grounded = 0;
    self->unk6++;
}

void frost_walrus_leap_windup(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 3) {
        func_8001540C(2, 0x92, self);
    }
    if (self->animation_step.fields.relative_step == 0) {
        func_80015D60(self, 2);
        self->unk6++;
    }
}

void frost_walrus_leap_jump(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->unk54 = (const u8*)&D_80101340;
        self->unk50 = (const u8*)&D_80101348;
        if (self->unk70 & 8) {
            self->ext.main_57.leap_grounded = 1;
            self->unk67 = 1;
        }
        self->unk6++;
    }
}

void frost_walrus_leap_air(struct MainObj* self)
{
    s32 side_mask;

    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B694(ANIMATED_OBJECT(self));
    if (self->unk67 == 1 && self->unk24 < 0) {
        self->unk67 = -1;
    }
    if (self->unk67 == -1 && (self->unk70 & 8)) {
        func_8001540C(2, 0x90, self);
        func_8001540C(2, 0x93, self);
        func_80028BAC(0x18, 3, 1);
        self->unk67 = 0;
    }
    if (self->unk67 == 0) {
        side_mask = 2;
        if (self->unk15 != 0) {
            side_mask = 1;
        }
        if (side_mask & self->unk70) {
            frost_walrus_set_floor_tiles(0x39);
            func_8001540C(2, 0x90, self);
            func_80028B68(0x1E, 4, 1);
            self->unk7C = 0x28;
            self->unk6++;
        }
    }
}

void frost_walrus_leap_recover(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7C <= 0) {
        self->unk54 = (const u8*)&D_8010133C;
        self->unk50 = (const u8*)&D_80101344;
        frost_walrus_set_floor_tiles(0x38);
        func_80015D60(self, 3);
        self->unk6++;
    }
}

void frost_walrus_leap_finish(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        func_80015D60(self, 0);
        frost_walrus_face_player(self);
        self->unk5 = 3;
        self->unk6 = 0;
        self->ext.main_57.leap_grounded = 0;
    }
}

void frost_walrus_walk(struct MainObj* self)
{
    frost_walrus_walk_funcs[self->unk6](self);
}

void frost_walrus_walk_start(struct MainObj* self)
{
    s32 x_vel = FIXED(-0.75);

    self->unk6++;
    if (self->unk15 != 0) {
        x_vel = FIXED(0.75);
    }
    self->unk20 = x_vel;
    self->unk24 = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    func_80015D60(self, 6);
    self->unk54 = (const u8*)&D_8010133C;
    self->unk50 = (const u8*)&D_80101344;
    self->unk7C = 0x80;
}

void frost_walrus_walk_stomp(struct MainObj* self)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        func_8001540C(2, 0x92, self);
        func_80028BAC(0x18, 3, 1);
    }
    if (self->animation_step.fields.event != 2) {
        func_8002B718(MOVING_OBJECT(self));
    }
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer <= 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void frost_walrus_shards(struct MainObj* self)
{
    frost_walrus_shards_funcs[self->unk6](self);
}

void frost_walrus_shards_start(struct MainObj* self)
{
    func_80015D60(self, 7);
    self->unk54 = (const u8*)&D_8010133C;
    self->unk50 = (const u8*)&D_80101344;
    self->unk6++;
}

void frost_walrus_shards_count(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->ext.main_57.leap_grounded = 0;
        if (self->unk5C >= 0x18) {
            self->ext.main_57.shard_count = 4;
        } else {
            self->ext.main_57.shard_count = 8;
        }
        self->unk7C = 0;
        self->unk6++;
    }
}

void frost_walrus_shards_fire(struct MainObj* self)
{
    u8 i;
    struct ShotObj* shot;

    i = 0;
    do {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x23;
            shot->unk2 = i + self->unk7C;
            shot->unk7C = WEAPON_OBJECT(self);
            shot->unk7 = self->ext.main_57.shard_count;
            self->ext.main_57.shot = shot;
        }
        i++;
    } while (i < 2);

    self->unk7E = 0x20;
    self->unk7C += 2;
    self->unk6++;
}

void frost_walrus_shards_repeat(struct MainObj* self)
{
    if (self->unk7E != 0) {
        self->unk7E--;
        return;
    }
    if (self->unk7C == self->ext.main_57.shard_count) {
        func_80015D60(self, 1);
        self->unk7C = 0;
        self->unk6++;
    } else {
        self->unk6--;
    }
}

void frost_walrus_shards_finish(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 3) {
        func_8001540C(2, 0x92, self);
    }
    if (self->animation_step.fields.event == 2) {
        func_80015D60(self, 0x1A);
        self->unk7C = 0x40;
        self->unk6++;
    }
}

void frost_walrus_shards_wait(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void frost_walrus_breath(struct MainObj* self)
{
    frost_walrus_breath_funcs[self->unk6](self);
}

void frost_walrus_breath_start(struct MainObj* self)
{
    func_80015D60(self, 4);
    self->unk54 = (const u8*)&D_8010133C;
    self->unk50 = (const u8*)&D_80101344;
    self->unk7C = 0x80;
    self->unk7E = 0x18;
    self->unk6++;
}

void frost_walrus_breath_blow(struct MainObj* self)
{
    struct VisualObj* vobj;
    struct ShotObj* sobj;

    func_80015DC8(ANIMATED_OBJECT(self));

    if (--self->unk7E == 0) {
        func_8001540C(2, 0x94, self);
        self->unk7E = 0x18;
    }

    if (--self->unk7C == 0) {
        self->unk7C = 0x30;
        self->unk6++;
    }

    if (self->animation_step.fields.event == 2) {
        vobj = find_free_visual_obj();
        if (vobj != NULL) {
            vobj->active = 0x41;
            vobj->id = 0x18;
            vobj->unk2 = 0x10;
            vobj->unk15 = self->unk15;
            vobj->unk50 = self;
            vobj->x_pos.i.hi = self->x_pos.i.hi + (self->unk15 ? 0x15 : -0x15);
            vobj->y_pos.i.hi = self->y_pos.i.hi;
        }
    }

    if (self->unk7C == 0x40) {
        sobj = find_free_shot_obj();
        if (sobj != NULL) {
            sobj->active = 0x41;
            sobj->id = 0x23;
            sobj->unk2 = 0x10;
            sobj->unk7C = self;
            self->ext.main_57.shot = sobj;
        }
    }
}

void frost_walrus_breath_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        func_80015D60(self, 1);
        self->unk6++;
    }
}

void frost_walrus_breath_launch(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        self->ext.main_57.shot->unk8C.word = self->animation_step.fields.event;
        func_800C813C(0xA, D_801013BC, self->ext.main_57.shot);
    }
    if (self->animation_step.fields.event == 2) {
        func_80015D60(self, 0);
        self->unk7C = 0x20;
        self->unk6++;
    }
}

void frost_walrus_breath_finish(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void frost_walrus_blizzard(struct MainObj* self)
{
    frost_walrus_blizzard_funcs[self->unk6](self);
}

void frost_walrus_blizzard_start(struct MainObj* self)
{
    func_80015D60(self, 0x16);
    self->unk54 = (const u8*)&D_8010133C;
    self->unk50 = (const u8*)&D_80101344;
    self->unk7C = 0x100;
    self->unk7E = 0x18;
    self->unk6++;
}

void frost_walrus_blizzard_blow(struct MainObj* self)
{
    struct VisualObj* vobj;
    struct ShotObj* sobj;

    func_80015DC8(ANIMATED_OBJECT(self));

    if (--self->unk7E == 0) {
        func_8001540C(2, 0x94, self);
        self->unk7E = 0x18;
    }

    if (--self->unk7C == 0) {
        func_80015D60(self, 0x16);
        self->unk7C = 0x80;
        self->unk6++;
    }

    if (self->animation_step.fields.event == 2) {
        vobj = find_free_visual_obj();
        if (vobj != NULL) {
            vobj->active = 0x41;
            vobj->id = 0x18;
            vobj->unk2 = 0x30;
            vobj->unk15 = self->unk15;
            vobj->unk50 = self;
            vobj->x_pos.i.hi = self->x_pos.i.hi + (self->unk15 ? 0x15 : -0x15);
            vobj->y_pos.i.hi = self->y_pos.i.hi;
        }
    }

    if (self->unk7C == 0x40) {
        sobj = find_free_shot_obj();
        if (sobj != NULL) {
            sobj->active = 0x41;
            sobj->id = 0x23;
            sobj->unk2 = 0x20;
            sobj->unk7C = self;
            self->ext.main_57.shot = sobj;
        }
    }
}

void frost_walrus_blizzard_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk7C = 0x60;
        self->unk6++;
    }
}

void frost_walrus_blizzard_finish(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void frost_walrus_blizzard_idle(struct MainObj* self)
{
}

void frost_walrus_stagger(struct MainObj* self)
{
    frost_walrus_stagger_funcs[self->unk6](self);
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80073E80);

void frost_walrus_stagger_fall(struct MainObj* self)
{
    struct VisualObj* temp_v0;

    func_8002B694(ANIMATED_OBJECT(self));
    if (self->unk24 < 0) {
        self->unk67 = -1;
    }
    if ((self->unk67 == -1) && (self->unk70 & 8)) {
        func_80015D60(self, 0x14);
        if (self->ext.main_57.tusks_broken == 0) {
            temp_v0 = find_free_visual_obj();
            if (temp_v0 != 0) {
                temp_v0->active = 0x41;
                temp_v0->id = 0x18;
                temp_v0->unk2 = 0x50;
                temp_v0->unk15 = self->unk15;
                temp_v0->unk50 = PLAYER_OBJECT(self);
                self->ext.main_57.tusks_broken = 1;
            }
        }
        self->unk67 = 0;
        func_80028BAC(0x10, 3, 1);
        self->unk6++;
    }
}

void frost_walrus_stagger_slide(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    if (self->unk70 & 3) {
        func_80028B68(0x10, 3, 1);
        self->unk7C = 0x20;
        self->unk6++;
    }
}

void frost_walrus_stagger_recover(struct MainObj* self)
{
    if (--self->unk7C != 0) {
        func_80015DC8(ANIMATED_OBJECT(self));
        return;
    }
    if (self->unk5C >= 0x18) {
        self->ext.main_57.script = frost_walrus_script_recover_high;
    } else {
        self->ext.main_57.script = frost_walrus_script_recover_low;
    }
    self->unk5 = 3;
    self->unk6 = 0;
    self->ext.main_57.flashing = 0;
    self->ext.main_57.flash_timer = 1;
}

void frost_walrus_regrow(struct MainObj* self)
{
    frost_walrus_regrow_funcs[self->unk6](self);
}

void frost_walrus_regrow_start(struct MainObj* self)
{
    struct VisualObj* visual;

    self->collision_data = (const u16*)D_801060F0;
    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 0x18;
        visual->unk2 = 0x20;
        visual->unk15 = self->unk15;
        visual->unk50 = PLAYER_OBJECT(self);
        visual->x_pos.u.hi = self->x_pos.u.hi;
        visual->y_pos.u.hi = self->y_pos.u.hi;
        func_80015D60(self, 0x19);
        self->unk6++;
    }
}

void frost_walrus_regrow_finish(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->collision_data = (const u16*)D_80107A78;
        self->ext.main_57.flash_timer = 0;
        self->ext.main_57.tusks_broken = 0;
        self->ext.main_57.staggered = 0;
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void frost_walrus_face_player(struct MainObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
}

void frost_walrus_choose_script(struct MainObj* self)
{
    u8 index;
    u8** choices;
    u8* thresholds;
    u8 i;
    u32 rnd;

    index = (self->unk5C - 1) / 16;
    choices = frost_walrus_scripts[index];
    rnd = get_random();
    i = 0;
    thresholds = frost_walrus_script_weights[index];
    rnd &= 0xF;
    while (i < 4) {
        if (rnd < thresholds[i]) {
            self->ext.main_57.script = choices[i];
            return;
        }
        i++;
    }
}

void frost_walrus_set_floor_tiles(s32 self)
{
    u16* list;
    u32* attrs;

    list = frost_walrus_floor_tiles;
    if (engine_obj.stage == 0xC) {
        list = frost_walrus_floor_tiles_rush;
    }
    while (*list != 0) {
        attrs = SP_BG_TILE_ATTRS;
        attrs[*list] &= ~0xFF;
        attrs[*list] |= self;
        list++;
    }
}
