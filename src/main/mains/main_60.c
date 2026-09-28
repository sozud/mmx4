// MainObj, main_object_update_funcs[60]
// 8007501C..8007872C
#include "common.h"
#include "func_tables.h"

extern void* storm_owl_patterns[];
extern u8 storm_owl_pattern_weights[];

void storm_owl_update(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    storm_owl_state_funcs[self->state](self);
}

void storm_owl_start(struct MainObj* self)
{
    storm_owl_start_funcs[self->unk5](self);
}

void storm_owl_start_wait_player(struct MainObj* self)
{
    if (engine_obj.stage == 7) {
        if (g_Player.x_pos.i.hi >= 0x9E1) {
            return;
        }
        player_start_script_action(0x14, 0);
    } else {
        if (g_Player.y_pos.i.hi < 0x6B0) {
            return;
        }
        player_start_script_action(0x14, 0x40);
    }
    self->unk5++;
}

void storm_owl_start_warning(struct MainObj* self)
{
    struct EffectObj* effect = find_free_effect_obj();

    if (effect != NULL) {
        effect->active = 1;
        effect->id = 0x18;
        self->ext.main_60.effect = effect;
    }
    self->unk5++;
}

void storm_owl_start_wait_warning(struct MainObj* self)
{
    if (self->ext.main_60.effect->active == 0) {
        self->unk5++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800751AC);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075320);

void storm_owl_death(struct MainObj* self)
{
    storm_owl_death_funcs[self->unk5](self);
}

void storm_owl_death_start(struct MainObj* self)
{
    func_80015930(2, 0xBC);
    g_Player.stun_timer = 0;
    player_start_script_action(0x14, g_Player.unk15);
    self->unk5++;
    self->unk42 &= 0x7FFF;
    func_80015D60(self, 0xB);
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->unk61 = 0x19;
    func_8002B318(BASE_OBJECT(self), 0x30, 0x30);
}

void storm_owl_death_explode(struct MainObj* self)
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
            self->ext.main_60.effect = effect;
        }
    }
    func_8002B318(BASE_OBJECT(self), 0x30, 0x30);
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

void func_800757F4(struct MainObj* arg0)
{
    struct EffectObj* effect = arg0->ext.main_60.effect;
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

void storm_owl_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_60.saved_unk5;
}

void storm_owl_intro(struct MainObj* self)
{
    storm_owl_intro_funcs[self->unk6](self);
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075944);

void storm_owl_intro_land(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    CollisionRelated(PLAYER_OBJECT(self));
    if (self->unk70 & 8) {
        func_80015D60(self, 9);
        self->unk7C = 0x49;
        self->unk6++;
    }
}

void storm_owl_intro_roar(struct MainObj* self)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        func_8001540C(2, 0xBB, self);
        func_80028BAC(0x18, 8, 1);
        storm_owl_spawn_roar(ANIMATED_OBJECT(self));
        self->unk7C = 0x2F;
        self->unk6++;
    }
}

void storm_owl_intro_pose(struct MainObj* self)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        if (engine_obj.stage == 7) {
            func_8002217C(0xF, 0xFF, engine_obj.character_state.bytes[8]);
            engine_obj.character_state.bytes[8] = 1;
        }
        self->unk6++;
    }
}

void storm_owl_intro_start_health_bar(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (abc_object.unkC == 0) {
        engine_obj.boss_ptr = self;
        engine_obj.enable_boss = 1;
        engine_obj.unk25 = 1;
        self->unk7C = 3;
        self->unk6++;
        func_800921E8(6);
    }
}

void storm_owl_intro_fill_health(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (func_8009227C() == 0) {
        if (--self->unk7C == 0) {
            func_8001540C(0, 0xE, 0);
            self->unk7C = 3;
        }
        if ((s8)++self->unk5C == 0x30) {
            player_end_script_action();
            storm_owl_choose_pattern(self);
            self->unk6++;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075C6C);

void storm_owl_intro_rise(struct MainObj* self)
{
    u8 index;

    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    index = (engine_obj.stage != 7) * 2;
    self->ext.main_60.corner = index;
    if (self->y_pos.i.hi < (s16)(background_objects[0].y_pos.i.hi + (u16)storm_owl_waypoints[index & 0xFF].y)) {
        self->unk5 = 3;
        self->unk20 = 0;
        self->unk24 = 0;
        self->unk6 = 2;
    }
}

void storm_owl_patrol(struct MainObj* self)
{
    storm_owl_patrol_funcs[self->unk6](self);
}

void storm_owl_patrol_start(struct MainObj* self)
{
    s32 x_pos;

    func_80015DC8(ANIMATED_OBJECT(self));
    func_80015D60(self, 1);
    x_pos = self->x_pos.val;
    self->unk15 = (g_Player.x_pos.val >= x_pos) << 6;
    self->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075E78);

void storm_owl_patrol_wait(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));

    if (self->ext.main_60.patrol_delay == 0) {
        self->unk20 = storm_owl_waypoints[self->ext.main_60.corner].vx;
        self->unk24 = storm_owl_waypoints[self->ext.main_60.corner].vy;
        self->unk28 = FIXED(0.015625);
        self->unk6++;
        self->unk15 = ((~self->unk20 >> 31) & 0x40);
    } else {
        self->ext.main_60.patrol_delay--;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800760C4);

void storm_owl_patrol_return(struct MainObj* self)
{
    s16 target_x;
    s16 x_pos;
    s32 distance;

    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B694(ANIMATED_OBJECT(self));
    self->unk24 += FIXED(0.015625);

    target_x = background_objects[0].x_pos.i.hi + (u16)storm_owl_waypoints[self->ext.main_60.corner].x;
    x_pos = self->x_pos.i.hi;
    distance = x_pos - target_x;
    if (distance < 0) {
        goto check_negative;
    }
    if (distance < 0x21) {
        goto reset;
    }
    return;

check_negative:
    if ((target_x - x_pos) < 0x21) {
        goto reset;
    }
    return;

reset:
    self->unk6 = 0;
    self->unk20 = 0;
    self->unk24 = 0;
    self->ext.main_60.patrol_delay = 0x14;
}

void storm_owl_grab(struct MainObj* self)
{
    storm_owl_grab_funcs[self->unk6](self);
}

void storm_owl_grab_dive(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_80015D60(self, 7);
    func_8002B93C(MOVING_OBJECT(self),
        func_8002B7DC(OBJECT_HEADER(self),
            OBJECT_HEADER(&g_Player))
            & 0xFF);

    self->unk20 *= 3;
    self->unk24 *= 4;
    if (self->unk15 == 0) {
        if (self->unk20 > 0) {
            self->unk20 = 0;
        }
    } else if (self->unk20 < 0) {
        self->unk20 = 0;
    }
    self->unk50 = &D_801016BC;
    self->unk68 = &D_801016C4;
    self->unk62 = 3;
    self->unk60 = 0;
    self->unk16 = 2;
    self->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80076364);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_8007651C);

void storm_owl_grab_carry(struct MainObj* self)
{
    s16 x_pos;
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    CollisionRelated(PLAYER_OBJECT(self));
    if (self->unk70 & 4) {
        self->unk24 = 0;
        self->unk2C = 0;
    }
    if (self->unk15 == 0) {
        x_pos = (u16)self->x_pos.i.hi - 0xA;
    } else {
        x_pos = (u16)self->x_pos.i.hi + 0xA;
    }
    g_Player.x_pos.i.hi = x_pos;
    g_Player.y_pos.i.hi = (u16)self->y_pos.i.hi + 0x1E;
    timer = (u16)self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        func_80015D60(self, 8);
        self->unk24 = FIXED(-4);
        self->unk6++;
    }
}

void func_800766FC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (g_Player.x_pos.i.hi <= background_objects[0].x_pos.i.hi + 0x10
        || g_Player.x_pos.i.hi >= background_objects[0].x_pos.i.hi + 0x130) {
        arg0->unk20 = 0;
        arg0->unk28 = 0;
    }
    g_Player.x_pos.i.hi = arg0->x_pos.i.hi;
    g_Player.y_pos.i.hi = arg0->y_pos.i.hi + 0x1C;
    CollisionRelated(PLAYER_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        func_8001540C(2, 0xBB, arg0);
        func_80028BAC(8, 4, 1);
        player_damage(9);
        func_80015D60(arg0, 1);
        if (arg0->unk15 == 0) {
            arg0->unk20 = FIXED(-2);
        } else {
            arg0->unk20 = FIXED(2);
        }
        arg0->unk24 = FIXED(-1);
        g_Player.stun_timer = 0;
        arg0->unk68 = &D_801016C0;
        arg0->unk62 = 0;
        arg0->unk50 = (const u8*)&D_801016B8;
        arg0->unk6++;
    }
}

void storm_owl_grab_leave(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    if (self->unk24 <= FIXED(2.99999)) {
        self->unk24 += FIXED(0.125);
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 1) {
        g_Player.stun_timer = 0;
        self->unk60 = 6;
        self->unk68 = &D_801016C0;
        self->unk62 = 0;
        self->unk50 = (const u8*)&D_801016B8;
        self->unk16 = 5;
        storm_owl_choose_corner(self);
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

void storm_owl_reenter(struct MainObj* self)
{
    storm_owl_reenter_funcs[self->unk6](self);
}

void storm_owl_reenter_warp(struct MainObj* self)
{
    u16 background_x = background_objects[0].x_pos.u.hi;
    u16 background_y = background_objects[0].y_pos.u.hi;
    u8 variant;
    s32 player_x;

    func_80015DC8(ANIMATED_OBJECT(self));
    variant = self->ext.main_60.corner;
    switch (variant) {
    case 0:
        self->x_pos.i.hi = background_x - 0x40;
        self->y_pos.i.hi = background_y + 0x10;
        break;
    case 1:
        self->x_pos.i.hi = background_x - 0x40;
        self->y_pos.i.hi = background_y + 0xC8;
        break;
    case 2:
        self->x_pos.i.hi = background_x + 0x180;
        self->y_pos.i.hi = background_y + 0x10;
        break;
    case 3:
        self->x_pos.i.hi = background_x + 0x180;
        self->y_pos.i.hi = background_y + 0xC8;
        break;
    }
    player_x = g_Player.x_pos.val;
    self->unk7C = 0x3C;
    self->active = 0x41;
    self->unk15 = (player_x >= self->x_pos.val) << 6;
    self->unk6++;
}

void storm_owl_reenter_wait(struct MainObj* self)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->ext.main_60.flash_mode == 1) {
        self->collision_data = (const u16*)D_801060F0;
    } else {
        self->collision_data = (const u16*)D_80107B78;
    }
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void storm_owl_feather(struct MainObj* self)
{
    storm_owl_feather_funcs[self->unk6](self);
}

void storm_owl_feather_start(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_80015D60(self, 3);
    self->unk15 = (self->x_pos.val <= g_Player.x_pos.val) << 6;
    self->unk7C = 0x1F;
    self->unk6++;
}

void storm_owl_feather_fire(struct MainObj* self)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        storm_owl_spawn_feather(self);
        func_8001540C(2, 0xB6, self);
        self->unk7C = 0x1C;
        self->unk6++;
    }
}

void storm_owl_feather_takeoff(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));

    if (--self->unk7C == 0) {
        func_80015D60(self, 1);
        storm_owl_choose_corner(self);
        if (self->ext.main_60.corner >> 1) {
            self->unk20 = FIXED(2);
            self->unk15 = 0x40;
        } else {
            self->unk20 = FIXED(-2);
            self->unk15 = 0;
        }
        self->unk24 = FIXED(3);
        self->unk6++;
    }
}

void storm_owl_feather_leave(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 1) {
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

void storm_owl_feather_volley(struct MainObj* self)
{
    storm_owl_feather_volley_funcs[self->unk6](self);
}

void storm_owl_feather_volley_start(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_80015D60(self, 3);
    self->unk7C = 0x1C;
    self->collision_data = (const u16*)D_80107B78;
    self->ext.main_60.shot_count = 0;
    self->unk15 = (self->ext.main_60.corner < 2) << 6;
    self->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80076D14);

void storm_owl_feather_volley_aim(struct MainObj* self)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        func_80015D60(self, 6);
        self->collision_data = (const u16*)D_80107B78;
        self->unk7C = 0x3C;
        self->unk6++;
    }
}

void storm_owl_feather_volley_release(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        func_8001540C(2, 0xB6, self);
        self->ext.main_60.feathers_holding = 1;
        self->unk7C = 0x78;
        self->unk6++;
    }
}

void storm_owl_feather_volley_wait(struct MainObj* self)
{
    s32 direction;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->ext.main_60.feather_mask == 0) {
        self->ext.main_60.feathers_holding = 0;
        func_80015D60(self, 1);
        direction = (self->x_pos.val >= g_Player.x_pos.val) << 6;
        self->unk15 = direction;
        if (direction == 0) {
            self->unk20 = FIXED(-2);
        } else {
            self->unk20 = FIXED(2);
        }
        self->unk24 = FIXED(3);
        self->unk6++;
    }
}

void storm_owl_feather_volley_leave(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 1) {
        storm_owl_choose_corner(self);
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

void storm_owl_cyclone(struct MainObj* self)
{
    storm_owl_cyclone_funcs[self->unk6](self);
}

void storm_owl_cyclone_start(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (!(self->ext.main_60.corner & 1)) {
        func_80015D60(self, 4);
    } else {
        func_80015D60(self, 5);
    }
    self->unk7C = 0x63;
    self->unk15 = ((self->ext.main_60.corner >> 1) == 0) << 6;
    self->unk6++;
}

void storm_owl_cyclone_fire(struct MainObj* self)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        func_8001540C(2, 0xB9, self);
        storm_owl_spawn_cyclones(self);
        self->unk7C = 0x1E;
        self->unk6++;
        return;
    }
    if ((timer < 0x29) && (((timer - 0x3B) % 20) == 0)) {
        storm_owl_spawn_cyclones(self);
        func_8001540C(2, 0xB9, self);
    }
}

void storm_owl_cyclone_finish(struct MainObj* self)
{
    s16 timer;
    s32 direction;

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        if (self->ext.main_60.pattern[0] == 3) {
            self->unk5 = 0xA;
            self->unk6 = 0;
            return;
        }
        func_80015D60(self, 1);
        direction = (self->x_pos.val >= g_Player.x_pos.val) << 6;
        self->unk15 = direction;
        if (direction == 0) {
            self->unk20 = FIXED(-2);
        } else {
            self->unk20 = FIXED(2);
        }
        self->unk24 = FIXED(3);
        self->unk6++;
    }
}

void storm_owl_cyclone_leave(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 1) {
        storm_owl_choose_corner(self);
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

void storm_owl_storm(struct MainObj* self)
{
    func_80078180(self);
    storm_owl_storm_funcs[self->unk6](self);
}

void storm_owl_storm_start(struct MainObj* self)
{
    s32 threshold;
    s32 velocity_x;
    s32 velocity_y;

    func_80015DC8(ANIMATED_OBJECT(self));
    threshold = (background_objects[0].x_pos.i.hi + 0xA0) << 16;
    func_8002B93C(
        MOVING_OBJECT(self),
        func_8002B7B0(OBJECT_HEADER(self), threshold,
            (background_objects[0].y_pos.i.hi + 0x70) << 16)
            & 0xFF);

    velocity_x = self->unk20;
    velocity_y = self->unk24;
    velocity_x <<= 1;
    velocity_y <<= 1;
    self->unk20 = velocity_x;
    self->unk24 = velocity_y;

    if (velocity_y > 0) {
        func_80015D60(self, 1);
    } else {
        func_80015D60(self, 0);
    }
    self->unk15 = (threshold >= self->x_pos.val) << 6;
    self->unk6++;
}

void func_80077318(struct MainObj* arg0)
{
    s32 target_x = (background_objects[0].x_pos.i.hi + 0xA0) << 16;
    s32 target_y = (background_objects[0].y_pos.i.hi + 0x70) << 16;
    s32 x;
    s32 y;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    func_8002B93C(MOVING_OBJECT(arg0), func_8002B7B0(OBJECT_HEADER(arg0), target_x, target_y) & 0xFF);
    arg0->unk20 *= 2;
    x = arg0->x_pos.val;
    arg0->unk24 *= 2;
    if (x - target_x >= 0 ? x - target_x <= FIXED(3.99999) : target_x - x <= FIXED(3.99999)) {
        y = arg0->y_pos.val;
        if (y - target_y >= 0 ? y - target_y <= FIXED(3.99999) : target_y - y <= FIXED(3.99999)) {
            func_80015D60(arg0, 6);
            arg0->unk6++;
        }
    }
}

void storm_owl_storm_charge(struct MainObj* self)
{
    storm_owl_spawn_storm_charge(ANIMATED_OBJECT(self));
    func_8001540C(2, 0xBE, self);
    self->unk7C = 0x3C;
    self->unk6++;
}

void storm_owl_storm_begin(struct MainObj* self)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        func_8001540C(2, 0xBC, self);
        self->ext.main_60.storm_active = 1;
        self->ext.main_60.storm_timer = 0x10;
        self->unk7C = 0x5A;
        self->unk6++;
    }
}

void storm_owl_storm_rain(struct MainObj* self)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        if (--self->ext.main_60.storm_timer == 0) {
            self->unk7C = 0x3C;
            self->unk6++;
        } else {
            self->unk7C = 0x14;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077580);

void storm_owl_storm_rain_again(struct MainObj* self)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        self->ext.main_60.storm_timer++;
        if (self->ext.main_60.storm_timer >= 0x10) {
            self->unk7C = 0x3C;
            self->unk6++;
            return;
        }
        self->unk7C = 0x14;
    }
}

void storm_owl_storm_end(struct MainObj* self)
{
    s16 timer;
    s32 direction;

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        func_80015930(2, 0xBC);
        func_80015D60(self, 1);
        self->ext.main_60.storm_active = 0;
        direction = (self->x_pos.val >= g_Player.x_pos.val) << 6;
        self->unk15 = direction;
        if (direction == 0) {
            self->unk20 = FIXED(-2);
        } else {
            self->unk20 = FIXED(2);
        }
        self->unk24 = FIXED(3);
        self->unk6++;
    }
}

void storm_owl_storm_leave(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 1) {
        storm_owl_choose_corner(self);
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

void storm_owl_hover(struct MainObj* self)
{
    storm_owl_hover_funcs[self->unk6](self);
}

void storm_owl_hover_start(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_80015D60(self, 0);
    self->unk7C = 0x5A;
    self->unk6++;
}

void storm_owl_hover_wait(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void storm_owl_stagger(struct MainObj* self)
{
    storm_owl_stagger_funcs[self->unk6](self);
}

void storm_owl_stagger_start(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_80015D60(self, 0xC);
    g_Player.stun_timer = 0;
    self->unk60 = 6;
    self->unk68 = &D_801016C0;
    self->unk50 = (const u8*)&D_801016B8;
    self->unk16 = 5;
    self->unk62 = 0;
    if (self->collision_data == (const u16*)D_80107B78) {
        self->unk7C = 0x28;
    } else {
        self->unk7C = 0xF;
    }
    self->ext.main_60.feathers_holding = 0;
    self->ext.main_60.feather_mask = 0;
    storm_owl_clear_shots();
    func_80015930(2, 0xBC);
    self->unk6++;
}

void storm_owl_stagger_recover(struct MainObj* self)
{
    s32 x_vel;
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        func_80015D60(self, 1);
        x_vel = FIXED(2);
        self->collision_data = (const u16*)D_80107B78;
        if (self->unk15 == 0) {
            x_vel = FIXED(-2);
        }
        self->unk20 = x_vel;
        self->unk24 = FIXED(3);
        self->unk6++;
    }
}

void storm_owl_stagger_leave(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    if ((func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 1) && (self->ext.main_60.feather_mask == 0)) {
        storm_owl_choose_corner(self);
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

void storm_owl_ground_cyclone(struct MainObj* self)
{
    storm_owl_ground_cyclone_funcs[self->unk6](self);
}

void storm_owl_ground_cyclone_start(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_80015D60(self, 1);
    if (!(self->ext.main_60.corner & 1)) {
        self->unk24 = FIXED(-3);
        self->unk6++;
    } else {
        self->unk7C = 0xA;
        self->unk6 += 2;
    }
    if (self->ext.main_60.corner < 2) {
        self->unk15 = 0x40;
    } else {
        self->unk15 = 0;
    }
}

void storm_owl_ground_cyclone_drop(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    CollisionRelated(PLAYER_OBJECT(self));
    if (self->unk70 & 8) {
        func_80015D60(self, 9);
        self->unk7C = 0x1E;
        self->unk6++;
    }
}

void storm_owl_ground_cyclone_land(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        func_80015D60(self, 3);
        self->unk7C = 0x1E;
        self->unk6++;
    }
}

void storm_owl_ground_cyclone_fire(struct MainObj* self)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        self->unk7C = 0xA;
        func_8001540C(2, 0xB4, self);
        func_80078314(self);
        self->unk6++;
    }
}

void storm_owl_ground_cyclone_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk7C = 0x5F;
        self->unk6++;
    }
}

void storm_owl_ground_cyclone_takeoff(struct MainObj* self)
{
    s32 x_vel;
    s16 timer;

    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer != 0) {
        return;
    }
    func_80015D60(self, 1);
    x_vel = FIXED(2);
    if (self->unk15 == 0) {
        x_vel = FIXED(-2);
    }
    self->unk20 = x_vel;
    self->unk24 = FIXED(3);
    self->unk6++;
}

void storm_owl_ground_cyclone_leave(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 1) {
        storm_owl_choose_corner(self);
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

void storm_owl_spawn_roar(struct AnimatedObj* self)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x1C;
        obj->unk2 = 0;
        obj->unk50 = PLAYER_OBJECT(self);
        obj->unk42 = self->unk42;
        obj->animation_table = storm_owl_animations;
        obj->unk3C = self->unk3C;
        obj->unk40 = self->unk40;
        obj->bg_offset = self->bg_offset;
        obj->unk16 = 4;
        obj->unk15 = self->unk15;
        obj->x_pos.val = self->x_pos.val;
        obj->y_pos.val = self->y_pos.val;
    }
}

void storm_owl_spawn_intro_wind(struct MainObj* self)
{
    struct VisualObj* obj = find_free_visual_obj();

    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x1C;
        obj->unk2 = 1;
        obj->unk50 = PLAYER_OBJECT(self);
        obj->unk42 = self->unk42;
        obj->animation_table = storm_owl_animations;
        obj->unk3C = self->sprite_frames;
        obj->unk40 = self->unk40;
        obj->bg_offset = self->bg_offset;
        obj->unk16 = 3;
        obj->unk15 = self->unk15;
        if (engine_obj.stage == 7) {
            obj->x_pos.i.hi = background_objects[0].x_pos.i.hi + 0x20;
        } else {
            obj->x_pos.i.hi = background_objects[0].x_pos.i.hi + 0x120;
        }
        obj->y_pos.i.hi = background_objects[0].y_pos.i.hi + 0x60;
    }
}

void storm_owl_spawn_feather(struct MainObj* self)
{
    struct ShotObj* shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x25;
        shot->unk2 = 0;
        shot->unk7C = WEAPON_OBJECT(self);
        shot->unk42 = self->unk42;
        shot->animation_table = storm_owl_animations;
        shot->unk3C = (void*)self->sprite_frames;
        shot->unk40 = self->unk40;
        shot->bg_offset = self->bg_offset;
        shot->unk16 = 5;
        shot->unk15 = self->unk15;
    }
}

void storm_owl_spawn_volley_feather(struct MainObj* self, s8 arg1)
{
    struct ShotObj* shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x25;
        shot->unk2 = arg1;
        shot->unk7C = WEAPON_OBJECT(self);
        shot->unk42 = self->unk42;
        shot->animation_table = storm_owl_animations;
        shot->unk3C = (void*)self->sprite_frames;
        shot->unk40 = self->unk40;
        shot->bg_offset = self->bg_offset;
        shot->unk16 = 5;
        shot->unk15 = self->unk15;
    }
}

void storm_owl_spawn_cyclones(struct MainObj* arg0)
{
    struct MainObj* self;
    s32 variant;
    s32 i;
    struct ShotObj* shot;

    self = arg0;
    i = 0;
    variant = ((self->ext.main_60.corner & 1) == 0) * 2;
    do {
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x26;
            shot->unk2 = variant + i;
            shot->unk7C = WEAPON_OBJECT(self);
            shot->unk42 = self->unk42;
            shot->animation_table = (u32**)storm_owl_animations;
            shot->unk3C = self->sprite_frames;
            shot->unk40 = self->unk40;
            shot->bg_offset = (s8)(u8)self->bg_offset;
            shot->unk16 = 4;
            shot->unk15 = self->unk15;
        }
        i += 1;
    } while ((u8)i < 3);
}

void storm_owl_spawn_storm_charge(struct AnimatedObj* self)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x1C;
        obj->unk2 = 2;
        obj->unk50 = PLAYER_OBJECT(self);
        obj->unk42 = self->unk42;
        obj->animation_table = storm_owl_animations;
        obj->unk3C = self->unk3C;
        obj->unk40 = self->unk40;
        obj->bg_offset = self->bg_offset;
        obj->unk16 = 3;
        obj->unk15 = self->unk15;
        obj->x_pos.val = self->x_pos.val;
        obj->y_pos.val = self->y_pos.val;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80078180);

void storm_owl_spawn_hit_flash(struct PlayerObj* self)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x1C;
        obj->unk2 = 3;
        obj->unk50 = self;
        obj->unk42 = self->unk42;
        obj->animation_table = storm_owl_animations;
        obj->unk3C = self->unk3C;
        obj->unk40 = self->unk40;
        obj->bg_offset = self->bg_offset;
        obj->unk16 = 3;
        obj->unk15 = self->unk15;
        obj->x_pos.val = self->x_pos.val;
        obj->y_pos.val = self->y_pos.val;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80078314);

void storm_owl_choose_corner(struct MainObj* self)
{
    s32 player_x = g_Player.x_pos.val;

    if (self->x_pos.val < player_x) {
        if (func_8002B780() & 1) {
            self->ext.main_60.corner = 0;
        } else {
            self->ext.main_60.corner = 1;
        }
    } else {
        if (func_8002B780() & 1) {
            self->ext.main_60.corner = 2;
        } else {
            self->ext.main_60.corner = 3;
        }
    }
}

void storm_owl_choose_pattern(struct MainObj* self)
{
    u32 idx;
    u8** table;
    u8* weights;
    u8* base;
    u8 i;
    u32 rnd;
    u32 gr;

    idx = self->unk5C - 1;
    if ((s32)idx < 0)
        idx = self->unk5C + 0xE;
    idx >>= 4;
    idx &= 0xFF;
    table = ((u8**)storm_owl_patterns)[idx];
    gr = get_random();
    i = 0;
    base = storm_owl_pattern_weights;
    weights = base + idx * 3;
    rnd = gr & 0xF;
    while (i < 3) {
        if (rnd < weights[i]) {
            self->ext.main_60.pattern = table[i];
            return;
        }
        i++;
    }
}

void storm_owl_clear_shots(void)
{
    u8 clear_value;
    u32 i;
    s32 j;
    u8* dst;

    clear_value = 0;
    for (i = 0; i < 0x20; i++) {
        if ((shot_objects[i].id == 0x25) || ((shot_objects[i].unk2 != 0) && (shot_objects[i].unk2 < 5))) {
            dst = (u8*)&shot_objects[i];
            j = sizeof(shot_objects[i]) - 1;
            do {
                *dst++ = clear_value;
            } while (j-- != 0);
        }
    }
}

struct Unk_unk68 D_801016B4 = { -14, -21, 30, 40 };

struct Unk_unk68 D_801016B8 = { -14, -21, 30, 40 };

struct Unk_unk68 D_801016BC = { -16, 15, 12, 9 };

struct Unk_unk68 D_801016C0 = { 5, 19, 11, 5 };

struct Unk_unk68 D_801016C4 = { 0, 27, 14, 25 };

struct Unk_unk68 D_801016C8[6] = {
    { 6, 0, 1, 6 },
    { 4, 0, 1, 7 },
    { 4, 0, 1, 8 },
    { 6, 0, 1, 9 },
    { 4, 0, 1, 10 },
    { 4, 0, -5, 11 },
};

struct Unk_unk68 D_801016E0[6] = {
    { 4, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 4, 0, 1, 3 },
    { 2, 0, 1, 4 },
    { 2, 0, -5, 5 },
};

struct Unk_unk68 D_801016F8[3] = {
    { 1, 0, 1, 16 },
    { 2, 0, 1, 17 },
    { 6, 0, -2, 18 },
};

struct Unk_unk68 D_80101704[6] = {
    { 4, 0, 1, 19 },
    { 6, 0, 1, 20 },
    { 14, 0, 1, 21 },
    { 2, 0, 1, 22 },
    { 2, 0, 1, 23 },
    { 33, 0, -5, 24 },
};

union AnimationStep D_8010171C[] = {
    { 0x19010006 },
    { 0x1A010003 },
    { 0x1B01000A },
    { 0x1C010003 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x1D000021 },
};

union AnimationStep D_80101738[] = {
    { 0x1E010006 },
    { 0x1F010003 },
    { 0x2001000A },
    { 0x21010003 },
    { 0x22010002 },
    { 0x23010002 },
    { 0x24000021 },
};

union AnimationStep D_80101754[] = {
    { 0x26010006 },
    { 0x25010008 },
    { 0x27010002 },
    { 0x29010002 },
    { 0x28000021 },
};

u8 D_80101768[8] = { 2, 0, 1, 12, 2, 0, 255, 13 };

u8 D_80101770[8] = { 2, 0, 1, 14, 2, 0, 255, 15 };

union AnimationStep D_80101778[] = {
    { 0x06010006 },
    { 0x5A010002 },
    { 0x5B010002 },
    { 0x5A010018 },
    { 0x5C010008 },
    { 0x5D010008 },
    { 0x5E010008 },
    { 0x5F01000B },
    { 0x60010002 },
    { 0x61010002 },
    { 0x60010002 },
    { 0x6100002F },
};

union AnimationStep D_801017A8[] = {
    { 0x62010002 },
    { 0x63010002 },
    { 0x64010002 },
    { 0x65010001 },
    { 0x66010001 },
    { 0x67000001 },
};

u8 D_801017C0[8] = { 2, 0, 1, 104, 2, 0, 255, 105 };

struct Unk_unk68 D_801017C8[5] = {
    { 3, 0, 1, 104 },
    { 3, 0, 1, 106 },
    { 3, 0, 1, 107 },
    { 3, 0, 1, 108 },
    { 3, 0, -4, 109 },
};

struct Unk_unk68 D_801017DC[16] = {
    { 1, 0, 1, 62 },
    { 1, 0, 1, 51 },
    { 1, 0, 1, 52 },
    { 1, 0, 1, 53 },
    { 1, 0, 1, 54 },
    { 1, 0, 1, 48 },
    { 1, 0, 1, 47 },
    { 1, 0, 1, 49 },
    { 1, 0, 1, 50 },
    { 1, 0, 1, 55 },
    { 1, 0, 1, 56 },
    { 1, 0, 1, 57 },
    { 1, 0, 1, 58 },
    { 1, 0, 1, 59 },
    { 1, 0, 1, 60 },
    { 1, 0, -15, 61 },
};

struct Unk_unk68 D_8010181C[19] = {
    { 1, 0, 1, 63 },
    { 1, 0, 1, 64 },
    { 1, 0, 1, 69 },
    { 1, 0, 1, 63 },
    { 1, 0, 1, 68 },
    { 1, 0, 1, 64 },
    { 1, 0, 1, 67 },
    { 1, 0, 1, 63 },
    { 1, 0, 1, 66 },
    { 1, 0, 1, 64 },
    { 1, 0, 1, 65 },
    { 1, 0, 1, 63 },
    { 1, 0, 1, 70 },
    { 1, 0, 1, 64 },
    { 1, 0, 1, 71 },
    { 1, 0, 1, 63 },
    { 1, 0, 1, 72 },
    { 1, 0, 1, 64 },
    { 1, 0, -18, 73 },
};

union AnimationStep D_80101868[] = {
    { 0x2E000001 },
};

union AnimationStep D_8010186C[] = {
    { 0x2D000001 },
};

union AnimationStep D_80101870[] = {
    { 0x2A000001 },
};

union AnimationStep D_80101874[] = {
    { 0x2C000001 },
};

union AnimationStep D_80101878[] = {
    { 0x2B000001 },
};

union AnimationStep D_8010187C[] = {
    { 0x6E010008 },
    { 0x6F010008 },
    { 0x70010008 },
    { 0x71000008 },
};

union AnimationStep D_8010188C[] = {
    { 0x56010008 },
    { 0x57010008 },
    { 0x58010008 },
    { 0x59000008 },
};

union AnimationStep D_8010189C[] = {
    { 0x4A010008 },
    { 0x4B010008 },
    { 0x4C010008 },
    { 0x4D000008 },
};

union AnimationStep D_801018AC[] = {
    { 0x4E010008 },
    { 0x4F010008 },
    { 0x50010008 },
    { 0x51000008 },
};

union AnimationStep D_801018BC[] = {
    { 0x52010008 },
    { 0x53010008 },
    { 0x54010008 },
    { 0x55000008 },
};

struct Unk_unk68 D_801018CC[9] = {
    { 1, 0, 1, 69 },
    { 1, 0, 1, 68 },
    { 1, 0, 1, 67 },
    { 1, 0, 1, 66 },
    { 1, 0, 1, 65 },
    { 1, 0, 1, 70 },
    { 1, 0, 1, 71 },
    { 1, 0, 1, 72 },
    { 1, 0, -8, 73 },
};

struct Unk_unk68 D_801018F0[8] = {
    { 2, 0, 1, -88 },
    { 2, 0, 1, -87 },
    { 2, 0, 1, -86 },
    { 2, 0, 1, -85 },
    { 2, 0, 1, -88 },
    { 2, 0, 1, -87 },
    { 2, 0, 1, -86 },
    { 2, 0, -7, -85 },
};

union AnimationStep D_80101910[] = {
    { 0x90010002 },
    { 0x91010002 },
    { 0x92010002 },
    { 0x93010002 },
    { 0x94010002 },
    { 0x95010002 },
    { 0x96010002 },
    { 0x97010002 },
    { 0x98010002 },
    { 0x99010002 },
    { 0x9A010002 },
    { 0x9B000002 },
};

union AnimationStep D_80101940[] = {
    { 0xA7010001 },
    { 0xA6010001 },
    { 0xA5010001 },
    { 0xA4010001 },
    { 0xA3010001 },
    { 0xA2010001 },
    { 0xA1010001 },
    { 0xA0010001 },
    { 0x9F010001 },
    { 0x9E010001 },
    { 0x9D010001 },
    { 0x9C000001 },
};

union AnimationStep D_80101970[] = {
    { 0x78010001 },
    { 0x79010001 },
    { 0x7A010001 },
    { 0x7B010001 },
    { 0x7C010001 },
    { 0x78010001 },
    { 0x7D010001 },
    { 0x72010001 },
    { 0x73010001 },
    { 0x74010001 },
    { 0x75010001 },
    { 0x76010001 },
    { 0x72010001 },
    { 0x77010001 },
    { 0x7E010001 },
    { 0x7F010001 },
    { 0x80010001 },
    { 0x81010001 },
    { 0x82010001 },
    { 0x7E010001 },
    { 0x83010001 },
    { 0x7E010001 },
    { 0x7F010001 },
    { 0x80010001 },
    { 0x81010001 },
    { 0x82010001 },
    { 0x7E010001 },
    { 0x83010001 },
    { 0x84010001 },
    { 0x85010001 },
    { 0x86010001 },
    { 0x87010001 },
    { 0x88010001 },
    { 0x84010001 },
    { 0x89010001 },
    { 0x84010001 },
    { 0x85010001 },
    { 0x86010001 },
    { 0x87010001 },
    { 0x88010001 },
    { 0x84010001 },
    { 0x89010001 },
    { 0x84010001 },
    { 0x85010001 },
    { 0x86010001 },
    { 0x87010001 },
    { 0x88010001 },
    { 0x84010001 },
    { 0x89010001 },
    { 0x8A010001 },
    { 0x8B010001 },
    { 0x8C010001 },
    { 0x8D010001 },
    { 0x8E010001 },
    { 0x8A010001 },
    { 0x8F010001 },
    { 0x8A010001 },
    { 0x8B010001 },
    { 0x8C010001 },
    { 0x8D010001 },
    { 0x8E010001 },
    { 0x8A010001 },
    { 0x8F000001 },
};

void* storm_owl_animations[30] = {
    D_801016C8,
    D_801016E0,
    D_801016F8,
    D_80101704,
    D_8010171C,
    D_80101738,
    D_80101754,
    D_80101768,
    D_80101770,
    D_80101778,
    D_801017A8,
    D_801017C0,
    D_801017C8,
    D_801017DC,
    D_8010181C,
    D_80101868,
    D_8010186C,
    D_80101870,
    D_80101874,
    D_80101878,
    D_8010187C,
    D_8010188C,
    D_8010189C,
    D_801018AC,
    D_801018BC,
    D_801018CC,
    D_801018F0,
    D_80101910,
    D_80101940,
    D_80101970,
};

Main60Waypoint storm_owl_waypoints[4] = {
    { 0x0018, 0x0028, 0x00020000, 0xFFFF0000 },
    { 0x0018, 0x00B0, 0x00028000, 0x00000800 },
    { 0x0128, 0x0028, 0xFFFE0000, 0xFFFF0000 },
    { 0x0128, 0x00B0, 0xFFFD8000, 0x00000800 },
};

u8 storm_owl_pattern_0[4] = { 3, 3, 8, 255 };

u8 storm_owl_pattern_1[4] = { 3, 3, 255, 0 };

u8 storm_owl_pattern_2[4] = { 3, 3, 8, 255 };

u8 storm_owl_pattern_3[4] = { 3, 7, 255, 0 };

u8 storm_owl_pattern_4[4] = { 12, 7, 3, 255 };

u8 storm_owl_pattern_5[4] = { 12, 12, 3, 255 };

u8 storm_owl_pattern_6[4] = { 12, 9, 3, 255 };

u8* storm_owl_patterns_high_health[2] = {
    storm_owl_pattern_0,
    storm_owl_pattern_1,
};

u8* storm_owl_patterns_mid_health[2] = {
    storm_owl_pattern_2,
    storm_owl_pattern_3,
};

u8* storm_owl_patterns_low_health[3] = {
    storm_owl_pattern_4,
    storm_owl_pattern_5,
    storm_owl_pattern_6,
};

void* storm_owl_patterns[3] = {
    storm_owl_patterns_low_health,
    storm_owl_patterns_mid_health,
    storm_owl_patterns_high_health,
};

u8 storm_owl_pattern_weights[12] = { 0x04, 0x0A, 0x10, 0x08, 0x10, 0x10, 0x0A, 0x10, 0x10, 0x00, 0x00, 0x00 };

void (*storm_owl_state_funcs[3])() = {
    storm_owl_start,
    func_80075320,
    storm_owl_death,
};

void (*storm_owl_start_funcs[4])() = {
    storm_owl_start_wait_player,
    storm_owl_start_warning,
    storm_owl_start_wait_warning,
    func_800751AC,
};

void (*storm_owl_step_funcs[13])() = {
    func_8009216C,
    storm_owl_resume_step,
    storm_owl_intro,
    storm_owl_patrol,
    storm_owl_grab,
    storm_owl_reenter,
    storm_owl_feather,
    storm_owl_feather_volley,
    storm_owl_cyclone,
    storm_owl_storm,
    storm_owl_hover,
    storm_owl_stagger,
    storm_owl_ground_cyclone,
};

void (*storm_owl_death_funcs[3])() = {
    storm_owl_death_start,
    storm_owl_death_explode,
    func_800757F4,
};

void (*storm_owl_intro_funcs[8])() = {
    func_80075944,
    storm_owl_intro_land,
    storm_owl_intro_roar,
    storm_owl_intro_pose,
    storm_owl_intro_start_health_bar,
    storm_owl_intro_fill_health,
    func_80075C6C,
    storm_owl_intro_rise,
};

void (*storm_owl_patrol_funcs[5])() = {
    storm_owl_patrol_start,
    func_80075E78,
    storm_owl_patrol_wait,
    func_800760C4,
    storm_owl_patrol_return,
};

void (*storm_owl_grab_funcs[6])() = {
    storm_owl_grab_dive,
    func_80076364,
    func_8007651C,
    storm_owl_grab_carry,
    func_800766FC,
    storm_owl_grab_leave,
};

void (*storm_owl_reenter_funcs[2])() = {
    storm_owl_reenter_warp,
    storm_owl_reenter_wait,
};

void (*storm_owl_feather_funcs[4])() = {
    storm_owl_feather_start,
    storm_owl_feather_fire,
    storm_owl_feather_takeoff,
    storm_owl_feather_leave,
};

void (*storm_owl_feather_volley_funcs[6])() = {
    storm_owl_feather_volley_start,
    func_80076D14,
    storm_owl_feather_volley_aim,
    storm_owl_feather_volley_release,
    storm_owl_feather_volley_wait,
    storm_owl_feather_volley_leave,
};

void (*storm_owl_cyclone_funcs[4])() = {
    storm_owl_cyclone_start,
    storm_owl_cyclone_fire,
    storm_owl_cyclone_finish,
    storm_owl_cyclone_leave,
};

void (*storm_owl_storm_funcs[9])() = {
    storm_owl_storm_start,
    func_80077318,
    storm_owl_storm_charge,
    storm_owl_storm_begin,
    storm_owl_storm_rain,
    func_80077580,
    storm_owl_storm_rain_again,
    storm_owl_storm_end,
    storm_owl_storm_leave,
};

void (*storm_owl_hover_funcs[2])() = {
    storm_owl_hover_start,
    storm_owl_hover_wait,
};

void (*storm_owl_stagger_funcs[3])() = {
    storm_owl_stagger_start,
    storm_owl_stagger_recover,
    storm_owl_stagger_leave,
};

void (*storm_owl_ground_cyclone_funcs[7])() = {
    storm_owl_ground_cyclone_start,
    storm_owl_ground_cyclone_drop,
    storm_owl_ground_cyclone_land,
    storm_owl_ground_cyclone_fire,
    storm_owl_ground_cyclone_wait,
    storm_owl_ground_cyclone_takeoff,
    storm_owl_ground_cyclone_leave,
};
