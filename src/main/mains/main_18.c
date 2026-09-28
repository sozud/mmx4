// MainObj, main_object_update_funcs[18]
// 80050708..8005284C
#include "common.h"
#include "func_tables.h"

void ice_core_update(struct MainObj* self)
{
    ice_core_state_funcs[self->state](self);
    if (self->ext.main_18.state.runtime.unk82 == 0 && self->state < 2) {
        CollisionRelated(PLAYER_OBJECT(self));
    }
}

// ice_core_init
INCLUDE_ASM("main/nonmatchings/mains/main_18", func_8005077C);

// ice_core_run
INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80050874);

void ice_core_death_sink(struct MainObj* self)
{
    s16 value;

    value = self->y_pos.i.hi + 1;
    self->y_pos.i.hi = value;
    if (value >= 0x931) {
        func_800DABE4(0x17, 0, 0);
        engine_obj.enable_boss = 0;
        engine_obj.boss_ptr = NULL;
        self->state = 3;
    } else {
        value = self->unk7C - 1;
        self->unk7C = value;
        if (value == 0) {
            self->unk7C = 4;
            func_800AF95C(OBJECT_HEADER(self), 1, 0x20, 0x30, 2);
        }

        value = self->unk7E - 1;
        self->unk7E = value;
        if (value == 0) {
            self->ext.main_18.state.saved_position.x = self->x_pos.val;
            self->ext.main_18.state.saved_position.y = self->y_pos.val;
            self->unk7E = 8;
            self->x_pos.i.hi = 0x18E2;
            self->y_pos.i.hi = 0x89E;
            func_800AF95C(OBJECT_HEADER(self), 1, 0x18, 0x30, 2);
            self->x_pos.val = self->ext.main_18.state.saved_position.x;
            self->y_pos.val = self->ext.main_18.state.saved_position.y;
        }
    }

    func_8002B318(BASE_OBJECT(self), 0x80, 0x80);
}

void ice_core_death_release_camera(struct MainObj* self)
{
    func_80036AE4(0x15, 0x40);
    self->state = 4;
}

void ice_core_death_wait_player(struct MainObj* self)
{
    if (g_Player.x_pos.i.hi >= 0x18F1) {
        func_80036B18();
        self->ext.raw[0] = 0;
        self->ext.raw[1] = 0;
        self->ext.raw[2] = 0;
        self->ext.raw[3] = 0;
        self->ext.raw[4] = 0;
        self->ext.raw[5] = 0;
        engine_obj.unkF = 0x40;
        func_8002B0C8(OBJECT_HEADER(self));
    }
}

void ice_core_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_18.saved_unk5;
}

void ice_core_drift(struct MainObj* self)
{
    ice_core_drift_funcs[self->unk6](self);
}

void ice_core_drift_start(struct MainObj* self)
{
    if (self->unk15 == 0) {
        self->unk20 = FIXED(-1.375);
    } else {
        self->unk20 = FIXED(1.375);
    }
    self->unk28 = 0;
    self->unk24 = 0;
    self->unk2C = FIXED(-0.125);
    func_80015DC8(ANIMATED_OBJECT(self));
    self->unk6 = 1;
}

// ice_core_drift_move
INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80050D14);

void ice_core_bob(struct MainObj* self)
{
    ice_core_bob_funcs[self->unk6](self);
}

void ice_core_bob_start(struct MainObj* self)
{
    self->ext.main_18.state.runtime.unk84 = 1;
    func_80015D60(self, 1);
    self->unk7C = 1;
    self->unk2C = FIXED(0.0625);
    self->unk6 = 1;
    self->unk20 = 0;
    self->unk28 = 0;
    self->unk24 = 0;
    self->unk54 = (const u8*)&D_800FBF00;
    self->unk50 = (const u8*)&D_800FBF00;
}

void ice_core_bob_move(struct MainObj* self)
{
    s16 temp_v0;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->collision_data = (const u16*)D_801060F0;
    }
    func_8002B694(ANIMATED_OBJECT(self));
    if (self->unk24 == FIXED(1.5)) {
        self->unk2C = FIXED(0.0625);
    }
    if (self->unk24 == FIXED(-1.5)) {
        temp_v0 = (u16)self->unk7C - 1;
        self->unk7C = temp_v0;
        if (temp_v0 == 0) {
            self->unk24 = 0;
            self->unk2C = 0;
            func_800527F0(self);
            return;
        }
        self->unk2C = FIXED(-0.0625);
    }
}

void ice_core_bob_recover(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->collision_data = (const u16*)D_80106B74;
        self->unk54 = (const u8*)&D_800FBEF4;
        self->unk50 = (const u8*)&D_800FBEF4;
    }
    if (self->animation_step.fields.event == 1) {
        self->ext.main_18.state.runtime.unk84 = 0;
        self->ext.main_18.state.runtime.unk80 &= 0x3F;
        func_80015D60(self, 2);
        func_800527F0(self);
    }
}

void ice_core_charge(struct MainObj* self)
{
    ice_core_charge_funcs[self->unk6](self);
}

void ice_core_charge_face(struct MainObj* self)
{
    ice_core_face_player(ANIMATED_OBJECT(self));
    self->unk7C = 0x1C;
    self->unk20 = 0;
    self->unk24 = 0;
    self->unk6 = 1;
}

void ice_core_charge_back_off(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        if (self->unk15 != 0) {
            self->unk20 = FIXED(-3);
        } else {
            self->unk20 = FIXED(3);
        }
        self->unk28 = FIXED(0.09375);
        self->unk7C = 0x14;
        self->unk24 = 0;
        self->unk2C = 0;
        self->unk6 = 2;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

void ice_core_charge_slide(struct MainObj* self)
{
    if (!(self->unk70 & 3)) {
        func_8002B694(ANIMATED_OBJECT(self));
        if (self->unk20 == 0) {
            self->unk20 = 0;
            self->unk28 = 0;
        }
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk7C = 0x1C;
        self->unk6 = 3;
    }
}

void ice_core_charge_start(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        func_8001540C(2, 0x35, self);
        self->unk60 = 6;
        self->ext.main_18.state.runtime.unk81 = 1;
        func_80015D60(self, 3);
        if (self->unk15 != 0) {
            self->unk20 = FIXED(4);
        } else {
            self->unk20 = FIXED(-4);
        }
        self->unk6 = 4;
    }
}

void ice_core_charge_run(struct MainObj* self)
{
    s32 blocked;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->unk54 = &D_800FBEFC;
        self->unk50 = &D_800FBEFC;
    }
    if (self->ext.main_18.state.runtime.unk83 >= 0xA) {
        func_80015D60(self, 0xC);
        self->unk6 = 5;
    }
    if (self->unk15 == 0) {
        blocked = self->unk70 & 2;
    } else {
        blocked = self->unk70 & 1;
    }
    if (blocked != 0) {
        func_8001540C(2, 0x37, self);
        func_80028B68(0x10, 8, 2);
        func_80015D60(self, 0xC);
        self->unk6 = 5;
    }
    func_8002B718(MOVING_OBJECT(self));
}

void ice_core_charge_recover(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));

    if (self->animation_step.fields.event == 2) {
        self->unk60 = 4;
        self->unk50 = (const u8*)&D_800FBEF4;
        self->unk54 = (const u8*)&D_800FBEF4;
    }

    if (self->animation_step.fields.event == 1) {
        func_80015D60(self, 2);
        func_800527F0(self);
        self->ext.main_18.state.runtime.unk83 = 0;
        self->ext.main_18.state.runtime.unk81 = 0;
        self->ext.main_18.state.runtime.unk80 = 0;
    }
}

void ice_core_stomp(struct MainObj* self)
{
    ice_core_stomp_funcs[self->unk6](self);
}

void ice_core_stomp_start(struct MainObj* self)
{
    self->ext.main_18.state.runtime.unk82 = 1;
    self->unk50 = (const u8*)&D_800FBF00;
    self->unk54 = (const u8*)&D_800FBF00;
    ice_core_face_player(ANIMATED_OBJECT(self));
    self->unk2C = FIXED(0.2578125);
    self->unk20 = 0;
    self->unk24 = 0;
    self->unk28 = 0;
    self->unk7C = 0x5A;
    self->unk6 = 1;
}

void ice_core_stomp_land(struct MainObj* self)
{
    s16 temp_v0;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->collision_data = D_801060F0;
    }
    temp_v0 = (u16)self->unk7C - 1;
    self->unk7C = temp_v0;
    if (temp_v0 == 0) {
        self->unk24 = FIXED(6);
        self->unk7C = 0x50;
        self->unk70 = 0;
        self->unk2C = 0;
        self->unk6 = 2;
        return;
    }
    func_8002B694(ANIMATED_OBJECT(self));
    if ((self->y_pos.i.hi >= 0x8BA) && (self->unk2C != 0)) {
        self->y_pos.i.hi = 0x8BA;
        self->unk24 = 0;
        self->unk2C = 0;
        func_8001540C(2, 0x38, self);
    }
}

void ice_core_stomp_rise(struct MainObj* self)
{
    s16 timer;

    if (self->unk7C >= 0x29) {
        func_8002B718(MOVING_OBJECT(self));
    }

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = (u16)self->unk7C - 1;
    self->unk7C = timer;

    if (timer == 0) {
        self->x_pos.val = g_Player.x_pos.val;
        if (self->x_pos.i.hi < 0x17CD) {
            self->x_pos.i.hi = 0x17CD;
        }
        if (self->x_pos.i.hi >= 0x18B6) {
            self->x_pos.i.hi = 0x18B5;
        }
        self->unk24 = FIXED(-8);
        self->unk7C = 0xA;
        self->unk6 = 3;
    }
}

void ice_core_stomp_drop(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->ext.main_18.state.runtime.unk82 = 0;
        self->unk68 = &D_800FBF0C;
    }
    func_8002B718(MOVING_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->unk50 = &D_800FBEF4;
        self->unk54 = &D_800FBEF4;
    }
    if (self->unk70 & 8) {
        func_8001540C(2, 0x37, self);
        func_80028BAC(0x10, 8, 2);
        self->ext.main_18.shed_timer = 0xA6;
        func_80015D60(self, 5);
        self->unk6 = 4;
    }
}

void ice_core_stomp_impact(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        func_80015D60((struct Unk19*)self, 6);
        self->unk6 = 5;
    }
}

void ice_core_stomp_recover(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        if (self->ext.main_18.ice_pieces == 0x8000) {
            self->ext.main_18.state.runtime.unk85 = self->unk5C;
        }
        self->collision_data = (const u16*)D_80106B74;
        self->unk50 = (const u8*)&D_800FBEF4;
        self->unk54 = (const u8*)&D_800FBEF4;
    }
    if (self->animation_step.fields.event == 1) {
        ice_core_face_player(ANIMATED_OBJECT(self));
        func_80015D60(self, 2);
        self->unk24 = FIXED(2);
        self->unk2C = FIXED(0.0625);
        self->unk5 = 6;
        self->unk6 = 0;
        self->ext.main_18.state.runtime.unk80 = 0;
    }
}

void ice_core_build(struct MainObj* self)
{
    ice_core_build_funcs[self->unk6](self);
}

void ice_core_build_open(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->unk50 = (const u8*)&D_800FBF04;
        self->unk54 = (const u8*)&D_800FBF04;
    }
    if (self->animation_step.fields.event == 1) {
        func_80015D60(self, 8);
        self->unk6 = 1;
    }
}

// ice_core_build_gather
INCLUDE_ASM("main/nonmatchings/mains/main_18", func_800517D0);

void ice_core_build_grow(struct MainObj* self)
{

    func_80015DC8(ANIMATED_OBJECT(self));
    if (*(u8*)&self->unk7E == 0xFF && self->unk5C < 0x30) {
        if (--self->ext.main_18.state.runtime.unk85 == 0) {
            func_8001540C(0, 0xE, NULL);
            self->ext.main_18.state.runtime.unk85 = 3;
        }
        self->unk5C++;
    }
    if (self->animation_step.fields.event == 3) {
        func_8001540C(2, 0x39, self);
    }
    if (self->animation_step.fields.event != 1) {
        return;
    }
    self->unk61 = 0;
    if (self->ext.main_18.unk88 == 0) {
        self->ext.main_18.unk88 = 1;
        func_80015D60(self, 0xB);
        self->unk50 = &D_800FBEF8;
        ice_core_face_player(ANIMATED_OBJECT(self));
    } else {
        self->ext.main_18.unk88 = 0;
        func_80015D60(self, 0);
        self->unk50 = &D_800FBEF4;
    }
    self->unk6 = 3;
    self->unk7C = 0x1E;
}

void ice_core_build_wait(struct MainObj* self)
{

    if (*(u8*)&self->unk7E == 0xFF && self->unk5C < 0x30) {
        if (--self->ext.main_18.state.runtime.unk85 == 0) {
            func_8001540C(0, 0xE, NULL);
            self->ext.main_18.state.runtime.unk85 = 3;
        }
        self->unk5C++;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        if (self->animation_step.fields.event != 0) {
            if (self->ext.main_18.unk88 == 0) {
                self->ext.main_18.state.runtime.unk85 = 0;
                self->ext.main_18.state.runtime.unk80 = 0;
                func_800527F0(self);
                if (*(u8*)&self->unk7E == 0xFF) {
                    *(u8*)&self->unk7E = get_random() & 1;
                    func_80036B18();
                }
            } else {
                func_80015D60(self, 0x10);
                self->unk5 = 9;
                self->unk6 = 0;
            }
        } else {
            self->unk7C = 1;
        }
    }
}

void ice_core_bounce(struct MainObj* self)
{
    ice_core_bounce_funcs[self->unk6](self);
}

void ice_core_bounce_start(struct MainObj* self)
{
    self->ext.main_18.state.runtime.unk80 = 0x80;
    ice_core_face_player(ANIMATED_OBJECT(self));
    self->unk68 = &D_800FBF10;

    if (self->unk15 == 0) {
        self->unk20 = FIXED(-3.53554);
    } else {
        self->unk20 = FIXED(3.53554);
    }

    if (!(get_random() & 1)) {
        self->unk24 = FIXED(-3.53554);
    } else {
        self->unk24 = FIXED(3.53554);
    }

    self->unk7C = 0xF0;
    self->unk6 = 1;
}

void ice_core_bounce_move(struct MainObj* self)
{
    s32 hit;

    if (self->unk20 < 0) {
        if (self->unk70 & 2) {
            func_800C813C(2, D_800FC340, self);
            func_8001540C(2, 0x37, self);
            func_80028B68(8, 4, 2);
            self->unk15 = 0x40;
            self->unk20 = -self->unk20;
        }
    } else if (self->unk70 & 1) {
        func_800C813C(2, D_800FC340, self);
        func_8001540C(2, 0x37, self);
        func_80028B68(8, 4, 2);
        self->unk15 = 0;
        self->unk20 = -self->unk20;
    }

    if (self->unk24 < 0) {
        hit = self->unk70 & 8;
    } else {
        hit = self->unk70 & 4;
    }
    if (hit != 0) {
        func_8001540C(5, 2, NULL);
        func_800C813C(2, D_800FC340, self);
        func_8001540C(2, 0x37, self);
        func_80028BAC(8, 4, 2);
        self->unk24 = -self->unk24;
    }

    func_8002B718(MOVING_OBJECT(self));
    if (self->ext.main_18.state.runtime.unk86 != 2) {
        if (--self->unk7C == 0) {
            if ((u16)(self->y_pos.i.hi - 0x849) < 0x47 && (u16)(self->x_pos.i.hi - 0x17D1) < 0xEF) {
                self->unk7C = 0x30;
                self->unk6 = 2;
                ice_core_face_player(ANIMATED_OBJECT(self));
                return;
            }
            self->unk7C = 1;
        }
    } else if (self->ext.main_18.state.runtime.unk87 != 0) {
        func_80015D60(self, 0xF);
        self->unk6 = 3;
    }
}

void ice_core_bounce_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk5 = 10;
        self->unk6 = 0;
    }
}

void ice_core_bounce_reform(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->unk50 = (const u8*)&D_800FBF04;
        self->unk54 = (const u8*)&D_800FBF04;
    }
    if (self->animation_step.fields.event == 1) {
        self->unk68 = &D_800FBF0C;
        self->ext.main_18.state.runtime.unk86 = 0;
        self->unk5 = 8;
        self->unk6 = 0;
    }
}

void ice_core_spray(struct MainObj* self)
{
    ice_core_spray_funcs[self->unk6](self);
}

void ice_core_spray_fire(struct MainObj* self)
{
    struct ShotObj* shot;
    s16 i;

    for (i = (self->ext.main_18.state.runtime.unk86 ^ 1) & 0xFF; i < 8; i += 2) {
        shot = find_free_shot_obj();
        if (shot == NULL) {
            continue;
        }
        shot->active = 0x41;
        shot->id = 0xC;
        shot->unk2 = i;
        shot->unk40 = self->unk40;
        shot->unk42 = self->unk42;
        shot->animation_table = (u32**)self->animation_table;
        shot->unk3C = (void*)self->sprite_frames;
        shot->bg_offset = self->bg_offset;
        shot->x_pos.val = self->x_pos.val;
        shot->y_pos.val = self->y_pos.val;
        shot->unk15 = self->unk15;
        shot->unk7C = (struct WeaponObj*)&self->state;
        shot->state = 0;
    }
    func_80015D60(self, self->ext.main_18.state.runtime.unk86 + 0xD);
    self->ext.main_18.state.runtime.unk86++;
    func_8001540C(2, 0x36, self);
    self->unk6 = 1;
}

void ice_core_spray_wait_event(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk7C = 0x30;
        self->unk6 = 2;
    }
}

void ice_core_spray_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk5 = 9;
        self->unk6 = 0;
    }
}

void ice_core_intro(struct MainObj* self)
{
    ice_core_intro_funcs[self->unk6](self);
}

// ice_core_intro_appear
INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80052218);

void ice_core_intro_wait_player(struct MainObj* self)
{
    if (g_Player.unkC0 == -1) {
        self->unk6 = 2;
    }
}

void ice_core_intro_descend(struct MainObj* self)
{
    func_8002B694(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk2C = FIXED(0.0078125);
        self->unk16 = 5;
        self->unk24 = 0;
        self->unk6 = 3;
    }
}

void ice_core_intro_slow(struct MainObj* self)
{
    func_8002B694(ANIMATED_OBJECT(self));
    if (self->unk24 == FIXED(-0.75)) {
        self->unk2C = FIXED(-0.015625);
        self->unk7C = 0x64;
        self->unk6 = 4;
    }
}

void ice_core_intro_start_fight(struct MainObj* self)
{
    func_8002B694(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        engine_obj.enable_boss = 1;
        engine_obj.unk25 = 2;
        engine_obj.boss_ptr = self;
        self->ext.main_18.state.runtime.unk82 = 0;
        self->unk24 = 0;
        self->unk2C = 0;
        self->unk5 = 8;
        self->unk6 = 0;
    }
}

void ice_core_fall(struct MainObj* self)
{
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk24 == 0) {
        self->unk68 = &D_800FBF0C;
        self->unk5 = 2;
        self->unk6 = 0;
    }
}

void ice_core_float(struct MainObj* self)
{
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));

    if (self->unk2C == FIXED(0.0625)) {
        if (self->ext.main_18.state.runtime.unk84 == 0) {
            if (self->y_pos.i.hi >= 0x891) {
                goto landed;
            }
            return;
        }
        if (self->y_pos.i.hi >= 0x8B1) {
            goto landed;
        }
        return;
    }

    if (self->ext.main_18.state.runtime.unk84 == 0) {
        if (self->y_pos.i.hi < 0x890) {
            goto landed;
        }
        return;
    }
    if (self->y_pos.i.hi >= 0x8B0) {
        return;
    }

landed:
    self->unk68 = &D_800FBF0C;
    self->unk5 = 2;
    self->unk6 = 0;
}

void ice_core_pick_attack(struct MainObj* self)
{
    u8 flags, next_flags, phase_value;

    flags = self->ext.main_18.state.runtime.unk80;
    if ((flags & 0xC0) == 0x40) {
        next_flags = flags | 0x80;
        self->ext.main_18.state.runtime.unk80 = next_flags;
        if ((next_flags & 0x3F) < 3 && (get_random() & 3) >= 2) {
            ice_core_face_player(ANIMATED_OBJECT(self));
            self->unk68 = &D_800FBF0C;
            self->unk5 = 3;
            self->unk6 = 0;
            return;
        }
        phase_value = *(u8*)&self->unk7E;
        switch (phase_value) {
        case 0:
            self->unk68 = &D_800FBF0C;
            self->unk5 = 4;
            self->unk6 = 0;
            *(u8*)&self->unk7E = 1;
            break;
        case 1:
            self->unk68 = &D_800FBF0C;
            func_80015D60(self, 4);
            self->unk5 = 5;
            self->unk6 = 0;
            *(u8*)&self->unk7E = 0;
            break;
        }
    }
}

void ice_core_check_rebuild(struct MainObj* self)
{
    if (self->ext.main_18.state.runtime.unk81 == 0 && self->unk5C < self->ext.main_18.state.runtime.unk85 && self->ext.main_18.state.runtime.unk87 != 0 && self->ext.main_18.unk88 == 0) {
        self->ext.main_18.state.runtime.unk82 = 0;
        self->ext.main_18.state.runtime.unk85 = 0;
        self->ext.main_18.state.runtime.unk84 = 0;
        func_80015D60(self, 7);
        self->unk20 = 0;
        self->unk28 = 0;
        self->unk24 = 0;
        self->unk2C = 0;
        self->unk5 = 8;
        self->unk6 = 0;
    }
}

void ice_core_shed_ice(struct MainObj* self)
{
    u8 timer;
    u8 random;
    u16 flags;
    s32 value;

    timer = self->ext.main_18.shed_timer;
    if (timer & 0xE0) {
        if ((self->ext.main_18.ice_pieces & 0x3FF) == 0) {
            self->ext.main_18.shed_timer = 0;
            return;
        }

        timer--;
        self->ext.main_18.shed_timer = timer;
        if ((timer & 0x1F) == 0) {
            do {
                random = get_random();
                if (random) {
                    random %= 10;
                }
                flags = self->ext.main_18.ice_pieces;
            } while ((flags & D_800FBEDC[random]) == 0);

            value = flags ^ D_800FBEDC[random];
            self->ext.main_18.ice_pieces = value;
            if (value == 0x8000) {
                self->ext.main_18.state.runtime.unk85 = self->unk5C;
            }
            self->ext.main_18.shed_timer = (self->ext.main_18.shed_timer - 0x20) | 0xC;
        }
    }
}

void ice_core_face_player(struct AnimatedObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
}

// ice_core_end_attack
INCLUDE_ASM("main/nonmatchings/mains/main_18", func_800527F0);

u16 D_800FBEDC[12] = {
    0x0001,
    0x0002,
    0x0004,
    0x0008,
    0x0010,
    0x0020,
    0x0040,
    0x0080,
    0x0100,
    0x0200,
    0xF3F8,
    0x1A0F,
};

struct Unk_unk68 D_800FBEF4 = { -18, -33, 38, 70 };

struct Unk_unk68 D_800FBEF8 = { -16, -19, 34, 34 };

struct Unk_unk68 D_800FBEFC = { -24, -66, 29, 111 };

struct Unk_unk68 D_800FBF00 = { -26, -15, 33, 30 };

struct Unk_unk68 D_800FBF04 = { -14, -9, 24, 19 };

struct Unk_unk68 D_800FBF08 = { -16, -22, 27, 51 };

struct Unk_unk68 D_800FBF0C = { 0, -17, 24, 39 };

struct Unk_unk68 D_800FBF10 = { 0, -3, 24, 20 };

union AnimationStep D_800FBF14[] = {
    { 0x00010008 },
    { 0x01010009 },
    { 0x0201000A },
    { 0x03FD0109 },
};

union AnimationStep D_800FBF24[] = {
    { 0x00010002 },
    { 0x04010004 },
    { 0x00010001 },
    { 0x05010002 },
    { 0x0601021D },
    { 0x06000101 },
};

union AnimationStep D_800FBF3C[] = {
    { 0x00010012 },
    { 0x0701000E },
    { 0x04010010 },
    { 0x07FD000E },
};

union AnimationStep D_800FBF4C[] = {
    { 0x00010002 },
    { 0x08010006 },
    { 0x01010004 },
    { 0x09010203 },
    { 0x0A010002 },
    { 0x0BFF0102 },
};

union AnimationStep D_800FBF64[] = {
    { 0x06010003 },
    { 0x0C010007 },
    { 0x0D010206 },
    { 0x0E010005 },
    { 0x0D000101 },
};

union AnimationStep D_800FBF78[] = {
    { 0x0D010001 },
    { 0x0E010007 },
    { 0x0D01001D },
    { 0x0D000101 },
};

union AnimationStep D_800FBF88[] = {
    { 0x0C010003 },
    { 0x06010005 },
    { 0x05010002 },
    { 0x40010201 },
    { 0x04010006 },
    { 0x40000101 },
};

union AnimationStep D_800FBFA0[] = {
    { 0x00010004 },
    { 0x10010204 },
    { 0x11010003 },
    { 0x12010002 },
    { 0x13010001 },
    { 0x12010001 },
    { 0x13010001 },
    { 0x12010001 },
    { 0x13010001 },
    { 0x12010001 },
    { 0x13010007 },
    { 0x14010004 },
    { 0x15010003 },
    { 0x16010002 },
    { 0x17010001 },
    { 0x16010001 },
    { 0x17010001 },
    { 0x16010001 },
    { 0x17010001 },
    { 0x16010001 },
    { 0x17000101 },
};

union AnimationStep D_800FBFF4[] = {
    { 0x18010003 },
    { 0x19010005 },
    { 0x18010003 },
    { 0x17010014 },
    { 0x1A010005 },
    { 0x1B010005 },
    { 0x17010005 },
    { 0x1A010004 },
    { 0x1B010004 },
    { 0x17010004 },
    { 0x1A010003 },
    { 0x1B010003 },
    { 0x17010003 },
    { 0x1A010001 },
    { 0x1B010001 },
    { 0x17010001 },
    { 0x1C010201 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1C010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1C010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1C010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1C010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1F010301 },
    { 0x20010001 },
    { 0x21010001 },
    { 0x22010001 },
    { 0x23010001 },
    { 0x24010001 },
    { 0x25010001 },
    { 0x26010001 },
    { 0x27010001 },
    { 0x28010001 },
    { 0x29010001 },
    { 0x2A010001 },
    { 0x2B010401 },
    { 0x2C010001 },
    { 0x2D010001 },
    { 0x55010001 },
    { 0x56010001 },
    { 0x57010001 },
    { 0x2B010001 },
    { 0x2C010001 },
    { 0x2D010001 },
    { 0x55010001 },
    { 0x56010001 },
    { 0x57010001 },
    { 0x58010001 },
    { 0x59010001 },
    { 0x5A010001 },
    { 0x5B010001 },
    { 0x5C010001 },
    { 0x5D010001 },
    { 0x58010001 },
    { 0x59010001 },
    { 0x5A010001 },
    { 0x5B010001 },
    { 0x5C010001 },
    { 0x5D010001 },
    { 0x58010001 },
    { 0x59010001 },
    { 0x5A010001 },
    { 0x5B010001 },
    { 0x5C010001 },
    { 0x5D010001 },
    { 0x58010001 },
    { 0x59010001 },
    { 0x5A010001 },
    { 0x5B010001 },
    { 0x5C010001 },
    { 0x5D000101 },
};

union AnimationStep D_800FC130[] = {
    { 0x0601000A },
    { 0x05010001 },
    { 0x40010001 },
    { 0x04010006 },
    { 0x40010201 },
    { 0x3E010002 },
    { 0x3F010304 },
    { 0x3E010001 },
    { 0x3E000101 },
};

union AnimationStep D_800FC154[] = {
    { 0x13010008 },
    { 0x2E010001 },
    { 0x41010202 },
    { 0x42010305 },
    { 0x41010002 },
    { 0x2E000101 },
};

union AnimationStep D_800FC16C[] = {
    { 0x2E010005 },
    { 0x3A010006 },
    { 0x3B010207 },
    { 0x3A010006 },
    { 0x2E010005 },
    { 0x3C010006 },
    { 0x3D010007 },
    { 0x3CF90006 },
};

union AnimationStep D_800FC18C[] = {
    { 0x0B010004 },
    { 0x0A010005 },
    { 0x0F010007 },
    { 0x09010205 },
    { 0x02010004 },
    { 0x01010003 },
    { 0x0001000E },
    { 0x00000101 },
};

union AnimationStep D_800FC1AC[] = {
    { 0x2F010004 },
    { 0x30010005 },
    { 0x31010006 },
    { 0x32010001 },
    { 0x31010001 },
    { 0x32010001 },
    { 0x31010001 },
    { 0x32010001 },
    { 0x31010001 },
    { 0x32000101 },
};

union AnimationStep D_800FC1D4[] = {
    { 0x33010004 },
    { 0x34010005 },
    { 0x35010006 },
    { 0x36010001 },
    { 0x35010001 },
    { 0x36010001 },
    { 0x35010001 },
    { 0x36010001 },
    { 0x35010001 },
    { 0x36000101 },
};

union AnimationStep D_800FC1FC[] = {
    { 0x37010004 },
    { 0x38010005 },
    { 0x39010006 },
    { 0x13010001 },
    { 0x39010001 },
    { 0x13010001 },
    { 0x39010001 },
    { 0x13010001 },
    { 0x39010001 },
    { 0x13010007 },
    { 0x14010004 },
    { 0x15010003 },
    { 0x16010002 },
    { 0x17010201 },
    { 0x16010001 },
    { 0x17010001 },
    { 0x16010001 },
    { 0x17010001 },
    { 0x16010001 },
    { 0x17000101 },
};

union AnimationStep D_800FC24C[] = {
    { 0x3B000101 },
};

union AnimationStep D_800FC250[] = {
    { 0x45000101 },
};

union AnimationStep D_800FC254[] = {
    { 0x44000101 },
};

union AnimationStep D_800FC258[] = {
    { 0x43000101 },
};

union AnimationStep D_800FC25C[] = {
    { 0x4A000101 },
};

union AnimationStep D_800FC260[] = {
    { 0x49000101 },
};

union AnimationStep D_800FC264[] = {
    { 0x48000101 },
};

union AnimationStep D_800FC268[] = {
    { 0x47000101 },
};

union AnimationStep D_800FC26C[] = {
    { 0x46000101 },
};

union AnimationStep D_800FC270[] = {
    { 0x4B000101 },
};

union AnimationStep D_800FC274[] = {
    { 0x4C000101 },
};

union AnimationStep D_800FC278[] = {
    { 0x4D000101 },
};

union AnimationStep D_800FC27C[] = {
    { 0x4E000101 },
};

union AnimationStep D_800FC280[] = {
    { 0x62010001 },
    { 0x63010009 },
    { 0x64010009 },
    { 0x65010009 },
    { 0x66010009 },
    { 0x67010009 },
    { 0x68010009 },
    { 0x69010009 },
    { 0x5E000101 },
};

union AnimationStep D_800FC2A4[] = {
    { 0x5F000101 },
};

union AnimationStep D_800FC2A8[] = {
    { 0x60000101 },
};

union AnimationStep D_800FC2AC[] = {
    { 0x61000101 },
};

union AnimationStep D_800FC2B0[] = {
    { 0x18000101 },
};

union AnimationStep* D_800FC2B4[34] = {
    D_800FBF14,
    D_800FBF24,
    D_800FBF3C,
    D_800FBF4C,
    D_800FBF64,
    D_800FBF78,
    D_800FBF88,
    D_800FBFA0,
    D_800FBFF4,
    D_800FC130,
    D_800FC154,
    D_800FC16C,
    D_800FC18C,
    D_800FC1AC,
    D_800FC1D4,
    D_800FC1FC,
    D_800FC24C,
    D_800FC250,
    D_800FC254,
    D_800FC258,
    D_800FC25C,
    D_800FC260,
    D_800FC264,
    D_800FC268,
    D_800FC26C,
    D_800FC270,
    D_800FC274,
    D_800FC278,
    D_800FC27C,
    D_800FC280,
    D_800FC2A4,
    D_800FC2A8,
    D_800FC2AC,
    D_800FC2B0,
};

u8 D_800FC33C[4] = { 25, 26, 27, 28 };

u8 D_800FC340[4] = { 31, 32, 0, 0 };

void (*ice_core_state_funcs[5])() = {
    func_8005077C,
    func_80050874,
    ice_core_death_sink,
    ice_core_death_release_camera,
    ice_core_death_wait_player,
};

void (*ice_core_step_funcs[12])() = {
    func_8009216C,
    ice_core_resume_step,
    ice_core_drift,
    ice_core_bob,
    ice_core_charge,
    ice_core_stomp,
    ice_core_fall,
    ice_core_float,
    ice_core_build,
    ice_core_bounce,
    ice_core_spray,
    ice_core_intro,
};

void (*ice_core_drift_funcs[2])(struct MainObj*) = {
    ice_core_drift_start,
    func_80050D14,
};

void (*ice_core_bob_funcs[3])(struct MainObj*) = {
    ice_core_bob_start,
    ice_core_bob_move,
    ice_core_bob_recover,
};

void (*ice_core_charge_funcs[6])(struct MainObj*) = {
    ice_core_charge_face,
    ice_core_charge_back_off,
    ice_core_charge_slide,
    ice_core_charge_start,
    ice_core_charge_run,
    ice_core_charge_recover,
};

void (*ice_core_stomp_funcs[6])(struct MainObj*) = {
    ice_core_stomp_start,
    ice_core_stomp_land,
    ice_core_stomp_rise,
    ice_core_stomp_drop,
    ice_core_stomp_impact,
    ice_core_stomp_recover,
};

void (*ice_core_build_funcs[4])(struct MainObj*) = {
    ice_core_build_open,
    func_800517D0,
    ice_core_build_grow,
    ice_core_build_wait,
};

void (*ice_core_bounce_funcs[4])(struct MainObj*) = {
    ice_core_bounce_start,
    ice_core_bounce_move,
    ice_core_bounce_wait,
    ice_core_bounce_reform,
};

void (*ice_core_spray_funcs[3])() = {
    ice_core_spray_fire,
    ice_core_spray_wait_event,
    ice_core_spray_wait,
};

void (*ice_core_intro_funcs[5])() = {
    func_80052218,
    ice_core_intro_wait_player,
    ice_core_intro_descend,
    ice_core_intro_slow,
    ice_core_intro_start_fight,
};
