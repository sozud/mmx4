// 800350A4..80036E98
#include "common.h"

struct PlayerHurtVelocity {
    s32 x_vel;
    s32 x_accel;
    s32 y_vel;
    s32 gravity;
};

void player_update(void);

void player_update_normal(struct PlayerObj* self);

void player_beam_in(struct PlayerObj* self);

void player_beam_out(struct PlayerObj* self);

void player_idle(struct PlayerObj* self);

void player_walk_start(struct PlayerObj* self);

void player_walk(struct PlayerObj* self);

void player_settle(struct PlayerObj* self);

void player_jump(struct PlayerObj* self);

void player_fall(struct PlayerObj* self);

void player_land(struct PlayerObj* self);

void player_wall_cling(struct PlayerObj* self);

void player_wall_jump(struct PlayerObj* self);

void player_wall_jump_push(struct PlayerObj* self);

void player_wall_jump_rise(struct PlayerObj* self);

void player_wall_slide_down(struct PlayerObj* self);

void player_wall_slide_release(struct PlayerObj* self);

void player_wall_slide(struct PlayerObj* self);

void player_wall_slide_down(struct PlayerObj* self);

void player_wall_slide_release(struct PlayerObj* self);

void player_dash(struct PlayerObj* self);

void player_dash_start(struct PlayerObj* self);

void player_dash_move(struct PlayerObj* self);

void player_dash_end(struct PlayerObj* self);

void player_air_dash(struct PlayerObj* self);

void player_air_dash_start(struct PlayerObj* self);

void player_air_dash_move(struct PlayerObj* self);

void player_air_dash_end(struct PlayerObj* self);

void player_ladder_transition(struct PlayerObj* self);

void player_ladder_grab(struct PlayerObj* self);

void player_ladder_climb_off_top(struct PlayerObj* self);

void player_ladder_climb_on_top(struct PlayerObj* self);

void player_ladder_step_off_bottom(struct PlayerObj* self);

void player_ladder_let_go(struct PlayerObj* self);

void player_ladder_up(struct PlayerObj* self);

void player_ladder_down(struct PlayerObj* self);

void player_hurt(struct PlayerObj* self);

void player_hurt_slide(struct PlayerObj* self);

void player_hurt_knockback(struct PlayerObj* self);

void player_hurt_launch(struct PlayerObj* self);

void player_hurt_stun(struct PlayerObj* self);

void player_hurt_slide(struct PlayerObj* self);

void player_ride(struct PlayerObj* self);

void player_capsule(struct PlayerObj* self);

// player_capsule_enter

void player_capsule_fall(struct PlayerObj* self);

void player_script_wait(struct PlayerObj* self);

// player_script_walk

void player_script_vanish(struct PlayerObj* self);

void player_script_jump(struct PlayerObj* self);

void player_script_victory(struct PlayerObj* self);

void player_stage_clear(struct PlayerObj* self);

s32 player_check_dash_jump_walk(struct PlayerObj* self);

s32 player_check_dash_jump(struct PlayerObj* self);

s32 player_check_walk_start(struct PlayerObj* self);

s32 player_check_walk(struct PlayerObj* self);

void player_check_fall(struct PlayerObj* self);

s32 player_check_dash_input(struct PlayerObj* self);

void player_update_double_tap(struct PlayerObj* self);

s32 player_dash_should_end(struct PlayerObj* self);

void player_check_capsule(struct PlayerObj* self);

void player_check_ride(struct PlayerObj* self);

s32 player_check_air_move(struct PlayerObj* self);

s32 player_check_wall(struct PlayerObj* self);

s32 player_check_wall_jump(struct PlayerObj* self);

s32 player_is_pushing_wall(struct PlayerObj* self);

void player_check_damage(struct PlayerObj* self);

void player_reset_actions(struct PlayerObj* self);

// player_take_hit

u8 func_8002D8B8(struct PlayerObj* arg0);

u8 func_8002D94C(struct PlayerObj* arg0);

s32 player_check_ladder(struct PlayerObj* self);

s32 player_check_ladder_air(struct PlayerObj* self);

// player_check_ladder_end

s32 player_check_off_ladder(struct PlayerObj* self);

s32 player_check_script(struct PlayerObj* self);

void player_script_walk_to_mark(struct PlayerObj* self);

s32 player_leap_check_peak(struct PlayerObj* self);

void player_leap_check_wall(struct PlayerObj* self);

void player_noop(void);

void player_enter_idle(struct PlayerObj* self);

void player_enter_stand(struct PlayerObj* self);

void player_enter_walk_start(struct PlayerObj* self);

void player_enter_walk(struct PlayerObj* self);

void player_enter_jump(struct PlayerObj* self);

void player_enter_fall(struct PlayerObj* self);

void player_enter_land(struct PlayerObj* self);

void player_enter_land_or_fall(struct PlayerObj* self);

void player_enter_dash(struct PlayerObj* self);

void player_enter_dash_end(struct PlayerObj* self);

void player_enter_air_dash(struct PlayerObj* self);

void player_enter_air_dash_end(struct PlayerObj* self);

void player_enter_fall_shooting(struct PlayerObj* self);

void player_enter_wall_cling(struct PlayerObj* self);

// player_enter_wall_jump

void player_enter_wall_slide(struct PlayerObj* self);

// player_enter_wall_slide_release

void player_enter_ladder_grab(struct PlayerObj* self);

void player_enter_ladder_climb_off_top(struct PlayerObj* self);

void player_enter_ladder_climb_on_top(struct PlayerObj* self);

void player_enter_ladder_step_off_bottom(struct PlayerObj* self);

void player_enter_ladder_up(struct PlayerObj* self);

void player_enter_ladder_down(struct PlayerObj* self);

// player_start_script

void player_start_stage_clear(struct PlayerObj* self);

void player_enter_beam_out(struct PlayerObj* self);

s16 player_afterimage_cluts[4] = { 0x780D, 0x780E, 0x780F, 0 };

void (*player_entry_funcs[])(struct PlayerObj*) = {
    player_entry_beam_in,
    player_entry_placed,
    player_entry_ride,
};

u16 player_stage_3_entry_y[2][4] = {
    { 0x0000, 0x00AB, 0x09CB, 0x025B },
    { 0x0000, 0x01AB, 0x08AB, 0x0000 },
};

u16 player_stage_6_entry_y[6] = {
    0x00CB,
    0x03BB,
    0x02CB,
    0x03BB,
    0x09CB,
    0x03BB,
};

u16 player_stage_12_entry_y[20] = {
    0x0000,
    0x0000,
    0x069B,
    0x06CB,
    0x06CB,
    0x06B3,
    0x06BB,
    0x06BB,
    0x09BB,
    0x09BB,
    0x09CB,
    0x035B,
    0x03CB,
    0x04AB,
    0x043B,
    0x03CB,
    0x035B,
    0x04AB,
    0x043B,
    0x0000,
};

void (*player_death_funcs[])(struct PlayerObj*) = {
    player_death_start,
    player_death_wait,
    func_80035C20,
    player_death_end,
};

u8 player_death_orb_directions[4][8] = {
    { 0x00, 0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C },
    { 0x02, 0x06, 0x0A, 0x0E, 0x12, 0x16, 0x1A, 0x1E },
    { 0x01, 0x05, 0x09, 0x0D, 0x11, 0x15, 0x19, 0x1D },
    { 0x03, 0x07, 0x0B, 0x0F, 0x13, 0x17, 0x1B, 0x1F },
};

struct Unk_unk68 player_x_collision_bounds = { 0, 2, 0x0B, 0x13 };

struct Unk_unk68 player_zero_collision_bounds = { 0, 3, 0x0A, 0x13 };

u16 player_dash_effect_offsets[6] = { 0x10, 0x0E, 0x1A, 0x11, 0x10, 0x1A };

f32 player_wall_kick_spark_offsets[2] = {
    { 0x000CFFF5 },
    { 0x0009FFF6 },
};

s32 player_set_animation(struct PlayerObj* self, s32 animation)
{
    if (self->unk2 == 0) {
        self->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 0);
    } else if (D_8011AF60[animation] == 0) {
        self->unk38 = SP_ARCHIVE_ENTRY(SP_PLAYER_GFX, 0);
        self->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 0);
    } else {
        self->unk38 = SP_ARCHIVE_ENTRY(SP_PLAYER_GFX, 1);
        self->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 5);
    }

    return set_animation(self, animation);
}

void player_set_animation_frame(struct PlayerObj* self, s32 animation, s32 frame)
{
    s32* x_gfx;
    s32* zero_gfx;
    s32* zero_saber_gfx;
    s32* x_frames;
    s32* zero_frames;
    s32* zero_saber_frames;
    if (self->unk2 == 0) {
        x_gfx = SP_PLAYER_GFX;
        x_frames = SP_SPRITE_FRAMES;
        self->unk38 = SP_ARCHIVE_ENTRY(x_gfx, 0);
        self->unk3C = SP_ARCHIVE_ENTRY(x_frames, 0);
    } else if (D_8011AF60[animation] == 0) {
        zero_gfx = SP_PLAYER_GFX;
        zero_frames = SP_SPRITE_FRAMES;
        self->unk38 = SP_ARCHIVE_ENTRY(zero_gfx, 0);
        self->unk3C = SP_ARCHIVE_ENTRY(zero_frames, 0);
    } else {
        zero_saber_gfx = SP_PLAYER_GFX;
        zero_saber_frames = SP_SPRITE_FRAMES;
        self->unk38 = SP_ARCHIVE_ENTRY(zero_saber_gfx, 1);
        self->unk3C = SP_ARCHIVE_ENTRY(zero_saber_frames, 5);
    }

    set_animation_frame(ANIMATED_OBJECT(self), animation, frame);
}

extern s16 player_afterimage_cluts[];

void player_spawn(void)
{
    struct PlayerObj* player = &g_Player;
    struct EngineObj* engine = &engine_obj;
    struct UnkObj* object;
    struct UnkObj* active_object;
    struct UnkObj* previous;
    struct BazObj* baz;
    struct VisualObj* visual;
    struct MiscObj* misc;
    s32* sprite_frames;
    s8* initial_data;
    s8* player_data;
    s32 frame_offset;
    u32 i;

    player->active = 1;
    player->unk2 = engine->cur_character;
    player->on_screen = 0;
    player->bg_offset = 0;
    player->is_clone = 0;
    player->boss_flags = engine->palette_flags;

    switch (engine->unk1E) {
    case 0:
        i = 0;
    case -2:
        i = 0;
        player->hp = engine->unk46;
        player->hud_hp = engine->unk46;
        player->unk5E = engine->unk46;
        do {
            player->weapon_energy[i++] = 0x30;
        } while (i < 0x10);
        break;

    case -1:
        player_data = player->weapon_energy;
        initial_data = engine->player_initial_data;
        i = 0;
        player->hp = engine->unk45;
        player->hud_hp = engine->unk45;
        player->unk5E = engine->unk45;
        do {
            *player_data++ = *initial_data++;
            i++;
        } while (i < 0x10);
        player->weapon = engine->unk60;
        player_equip_weapon(player);
        player_update_shot_types(player);
        break;
    }

    if (player->unk2 == 0) {
        player->animation_table = D_80119DF0;
    } else {
        player->animation_table = D_8011AFF0;
    }

    player->unk38 = (s32*)((u8*)SP_PLAYER_GFX + SP_PLAYER_GFX[0]);
    player->unk3C = (u8*)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[0];
    player->unk40 = 0x500;
    player->unk16 = 2;
    player->unk42 = 0x7800;
    player->unk49 = 3;
    player_reset_palette(player);
    player_init_clone();

    i = 0;
    active_object = foo_objects;
    object = foo_objects;
    do {
        active_object->active = 0x11;
        object->unk2 = i;
        object->bg_offset = player->bg_offset;
        object->unk38 = player->unk38;
        object->unk3C = player->unk3C;
        object->unk40 = player->unk40;
        object->unk42 = player_afterimage_cluts[object->unk2];
        object->unk16 = 4;
        if (i != 0) {
            object->link.previous = previous;
        } else {
            object->link.player = &g_Player;
        }
        previous = object;
        object++;
        i++;
        active_object++;
    } while (i < 3);

    baz = baz_objects;
    i = 0;
    do {
        baz->active = 0x21;
        baz->unk2 = i;
        baz->bg_offset = player->bg_offset;
        baz->unk38 = 0;
        sprite_frames = SP_SPRITE_FRAMES;
        frame_offset = sprite_frames[1];
        baz->unk3C = (u8*)sprite_frames + frame_offset;
        baz->animation_table = D_8011BF40;
        baz->unk40 = 0;
        baz->unk42 = 0x7800;
        baz->unk16 = 2;
        baz->unk15 = 0;
        baz++;
    } while (++i < 2);

    if (engine->stage == 1) {
        i = 0;
        do {
            visual = find_free_visual_obj();
            if (visual != 0) {
                visual->active = 0x41;
                visual->id = 7;
                visual->unk2 = i;
            }
            i++;
        } while (i < 4);
    }

    if (player->unk2 == 0) {
        misc = find_free_misc_obj();
        if (misc != 0) {
            misc->active = 0x21;
            misc->id = 0x36;
        }
    }

    background_objects[0].unk44 = 0;
    background_objects[1].unk44 = 0;
    background_objects[2].unk44 = 0;
}

void player_init_clone(void)
{
    struct PlayerObj* entity = &g_Entity;

    reset_entity(entity);
    entity->is_clone = 1;
    entity->animation_table = D_80119DF0;
    entity->unk50 = 0;
    entity->unk54 = 0;
    entity->unk68 = NULL;
    entity->hp = engine_obj.unk46;
    entity->hud_hp = engine_obj.unk46;
    entity->unk5E = engine_obj.unk46;
    entity->unk38 = (s32*)((u8*)SP_PLAYER_GFX + SP_PLAYER_GFX[0]);
    entity->unk3C = (u8*)SP_PLAYER_GFX + SP_PLAYER_GFX[0];
    entity->unk40 = 0x540;
    entity->unk16 = 2;
    entity->unk42 = 0x7800;
    entity->unk49 = 1;
}

void player_update_init(struct PlayerObj* self)
{
    struct EngineObj* engine = &engine_obj;
    s32 entry;

    if (self->is_clone != 0) {
        self->on_screen = 1;
        player_set_animation(self, 0x61);
        self->unk5 = PLAYER_SOUL_BODY_CLONE;
        self->state++;
        return;
    }
    if (engine->unk1E != 0) {
        self->on_screen = 1;
        engine->unk1F = 1;
        entry = 0;
        switch (engine->stage) {
        case 3:
            if (engine->unk1E == -1 && engine->checkpoint != 0) {
                entry = 1;
            }
            break;
        case 5:
            entry = 2;
            if (engine->substage != 0) {
                if (engine->checkpoint == 0) {
                    entry = 2;
                } else {
                    entry = 0;
                }
            }
            break;
        case 6:
            if (engine->unk1E == -1) {
                entry = 1;
            }
            break;
        case 12:
            if (engine->substage == 0) {
                if (engine->checkpoint >= 2) {
                    entry = 1;
                }
            } else if (engine->checkpoint == 0) {
                entry = 1;
            }
            break;
        }
        self->state++;
        player_entry_funcs[entry](self);
    }
}

void player_entry_beam_in(struct PlayerObj* self)
{
    player_set_animation(self, 1);
    func_8001540C(1, 0xD, self);
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = FIXED(-8);
    self->unk2C = 0;
    self->air_state = -1;
    self->unk5 = PLAYER_BEAM_IN;
}

void player_entry_placed(struct PlayerObj* self)
{
    struct EngineObj* engine = &engine_obj;

    switch (engine_obj.stage) {
    case 3:
        self->y_pos.i.hi = player_stage_3_entry_y[engine_obj.substage][engine_obj.checkpoint];
        break;
    case 6:
        if (engine_obj.substage == 0) {
            self->y_pos.i.hi = player_stage_6_entry_y[engine_obj.checkpoint];
        } else {
            self->y_pos.i.hi = 0x9CB;
        }
        break;
    case 12:
        if (engine_obj.substage == 0) {
            self->y_pos.i.hi = player_stage_12_entry_y[engine_obj.checkpoint];
        } else {
            self->y_pos.i.hi = 0x1CB;
        }
        break;
    }

    if (self->unk2 == 0) {
        self->armor_parts = engine->unk47;
        self->arm_type = engine->unk48;
    } else {
        self->y_pos.i.hi--;
    }
    self->y_pos.i.lo = 0;
    engine->unk1C = 0;
    player_set_collision_bounds(self);
    player_enter_idle(self);
    background_objects[0].unk44 = 1;
    background_objects[1].unk44 = 1;
    background_objects[2].unk44 = 1;
}

void player_entry_ride(struct PlayerObj* self)
{
    qux_object.active = 1;
    self->armor_parts = engine_obj.unk47;
    self->arm_type = engine_obj.unk48;
    self->ride_state = -1;
    self->air_state = 1;
    self->ride_animation = 0x29;
    self->unk5 = PLAYER_RIDE;
    self->unk6 = 1;
}

void player_update_death(struct PlayerObj* self)
{
    player_death_funcs[self->unk5](self);
}

void player_death_start(struct PlayerObj* self)
{
    stop_sound(1, 5);
    stop_sound(1, 7);
    if (self->ride_state != 0) {
        self->on_screen = 0;
        self->death_timer = 1;
    } else {
        engine_obj.unk12 = 1;
        engine_obj.unk13 = 1;
        engine_obj.unk14 = 1;
        engine_obj.unk15 = 1;
        engine_obj.unk16 = 1;
        engine_obj.unk17 = 1;
        engine_obj.unk18 = 1;
        engine_obj.unk19 = 1;
        engine_obj.unk1A = 1;
        self->death_timer = 8;
        player_set_animation(self, 0x21);
    }
    self->unk5 = (u8)self->unk5 + 1;
}

void player_death_wait(struct PlayerObj* self)
{
    if (--self->death_timer == 0) {
        engine_obj.unk12 = 0;
        engine_obj.unk13 = 0;
        engine_obj.unk14 = 0;
        engine_obj.unk15 = 0;
        engine_obj.unk16 = 0;
        engine_obj.unk17 = 0;
        engine_obj.unk18 = 0;
        engine_obj.unk19 = 0;
        engine_obj.unk1A = 0;
        self->on_screen = 0;
        func_8001540C(3, 0xC, self);
        self->death_timer = 0;
        self->unkC6 = 0;
        self->unk5 = (u8)self->unk5 + 1;
        func_80035C20(self);
    }
}

// player_death_explode
INCLUDE_ASM("main/nonmatchings/player_common", func_80035C20);
void player_death_end(struct PlayerObj* self)
{
    if (self->death_timer != 0) {
        self->death_timer--;
        return;
    }
    self->state = PLAYER_STATE_INACTIVE;
    self->unk5 = 0;
}

void player_spawn_death_orb(s8 direction)
{
    struct MiscObj* obj;

    obj = find_free_misc_obj();
    if (obj != NULL) {
        obj->active = 0x21;
        obj->id = 0x11;
        obj->unk2 = direction;
        obj->state = 0;
        obj->unk5 = 0;
        obj->unk6 = 0;
    }
}

void player_spawn_death_orbs(s8 pattern)
{
    const s8* entry;
    const s8* end;
    s32 index;
    const s8* table;

    index = pattern;
    table = (const s8*)player_death_orb_directions;
    index *= 8;
    entry = table + index;
    end = entry + 8;

    do {
        player_spawn_death_orb(*entry++);
    } while (entry < end);
}

void player_update_inactive(struct PlayerObj* self)
{
}

void player_update_frame_hitbox(struct PlayerObj* self)
{
    u8 zero_hitbox;
    u8 x_hitbox;

    if (self->unk2 == 0) {
        if (self->is_clone == 0) {
            x_hitbox = D_801193F0[self->animation_step.fields.frame_index];
            if (D_801193F0[self->animation_step.fields.frame_index] != 0) {
                self->unk54 = &D_801194F0[x_hitbox];
                return;
            }
        }
        self->unk54 = NULL;
        return;
    }
    if (D_8011AF60[self->unk17] == 0) {
        zero_hitbox = D_8011A030[self->animation_step.fields.frame_index];
    } else {
        zero_hitbox = D_8011A130[self->animation_step.fields.frame_index];
    }
    if (zero_hitbox == 0) {
        self->unk54 = NULL;
        return;
    }
    self->unk54 = &D_8011A230[zero_hitbox];
}

void player_set_collision_bounds(struct PlayerObj* self)
{
    if (self->ride_state < 0) {
        self->unk68 = NULL;
        return;
    }
    if (self->unk2 == 0) {
        self->unk68 = &player_x_collision_bounds;
        return;
    }
    self->unk68 = &player_zero_collision_bounds;
}

void player_read_input(void)
{
    if (g_Player.controlling_clone == 0) {
        g_Player.input.buttons.held = player_map_buttons(D_80166C08);
        g_Player.input.buttons.previous = player_map_buttons(D_80166C0A);
        g_Player.pressed_input = player_map_buttons(controller_state);
        return;
    }
    g_Player.input.buttons.held = 0;
    g_Player.input.buttons.previous = 0;
    g_Player.pressed_input = 0;
    g_Entity.input.buttons.held = player_map_buttons(D_80166C08);
    g_Entity.input.buttons.previous = player_map_buttons(D_80166C0A);
    g_Entity.pressed_input = player_map_buttons(controller_state);
}

s32 player_map_buttons(s32 pad)
{
    u16 result = 0;
    u32 bit = 1;
    u32 i = 0;

    for (i = 0; i < 16; i++) {
        if (D_800EE430[i] & pad) {
            result |= bit;
        }
        bit *= 2;
    }

    if ((result & 3) == 3) {
        result &= ~0x3;
    }

    if ((result & 0xC) == 0xC) {
        result &= ~0xC;
    }

    return result;
}

void player_clear_dash(struct PlayerObj* self)
{
    self->dash_momentum = 0;
    self->air_action = 0;
    if (self->afterimage > 0) {
        self->afterimage = -1;
    }
}

void player_clear_attack(struct PlayerObj* self)
{
    self->attacking = 0;
    self->shot_fired = 0;
    self->attack_ended = 0;
    self->attack_pose_timer = 0;
    self->shot_cooldown = 0;
    self->shot_palette_timer = 0;
    player_reset_palette(self);
}

void player_clear_dash_and_attack(struct PlayerObj* self)
{
    self->dash_momentum = 0;
    self->air_action = 0;
    self->afterimage = 0;
    player_clear_attack(self);
}

void player_clear_flash(struct PlayerObj* self)
{
    self->flash_palette = 0;
}

void player_update_flash(struct PlayerObj* self)
{
    s8 action = self->unk5; // likely fake
    if ((self->unk5 != PLAYER_BEAM_IN) && (action != PLAYER_BEAM_OUT) && (self->hurt_phase <= 0)) {
        if (self->shot_palette_timer != 0) {
            if (--self->shot_palette_timer == 0) {
                player_reset_palette(self);
            }
        }
        if (self->hurt_phase < 0) {
            self->flash_palette = 0x23;
        }
        if (self->flash_palette != 0) {
            if (self->flash_delay != 0) {
                self->flash_delay--;
            } else {
                if (self->flash_phase == 0) {
                    player_set_palette(self, self->flash_palette);
                } else {
                    player_reset_palette(self);
                }
                self->flash_delay = 1;
                self->flash_phase ^= 1;
            }
            self->flash_palette = 0;
        }
    }
}

void player_copy_palette(struct PlayerObj* self, s32 source, s32 dest)
{
    u16* src;
    u16* dst;
    u32 i;

    src = SP_PALETTE_BANK[source];
    dst = SP_PALETTES[dest];

    for (i = 0; i < 16; i++) {
        *dst++ = *src++;
    }
}

void player_reset_palette(struct PlayerObj* self)
{
    u16* dst;
    u16* src;
    u32 a2;

    if (self->unk2 == 0) {
        if (self->is_clone == 0) {
            if (self->weapon == 0) {
                player_set_palette(self, 0);
            } else {
                src = SP_PALETTE_BANK[3] + (((self->weapon - 1) << 6));
                dst = SP_PALETTE;
                for (a2 = 0; a2 < 0x20; a2++) {
                    *dst++ = *src++;
                }
                dst = SP_PALETTE + 0x130;
                for (a2 = 0; a2 < 0x20; a2++) {
                    *dst++ = *src++;
                }
            }
            need_palette_load |= 1;
        }
    } else {
        if (engine_obj.unk37) {
            player_copy_palette(self, 0xD, 0);
        } else {
            player_copy_palette(self, 0, 0);
        }
        need_palette_load |= 1;
    }
}

void player_set_palette(struct PlayerObj* self, s32 palette)
{
    u16* dst;
    u16* src;
    u32 i;

    if (self->unk2 == 0) {
        if (self->is_clone == 0) {
            src = SP_PALETTE_BANK[palette];
            dst = SP_PALETTE;
            for (i = 0; i < 0x10; i++) {
                *dst++ = *src++;
            }
            dst = SP_PALETTE + 0x130;
            for (i = 0; i < 0x20; i++) {
                *dst++ = *src++;
            }
            need_palette_load |= 1;
        }
    } else {
        player_copy_palette(self, palette, 0);
        need_palette_load |= 1;
    }
}

void player_play_voice(struct PlayerObj* self, u8 voice)
{
    if (self->voice_timer <= 0) {
        func_8001540C(3, voice, self);
    }
}

void player_check_low_hp_alarm(struct PlayerObj* self)
{
    if (self->voice_timer == 0 && self->hp < (engine_obj.unk46 / 3)) {
        func_8001540C(3, 0xB, 0);
        self->voice_timer = 0x78;
    }
}

void player_damage(s8 damage)
{
    struct PlayerObj* player;
    u8 amount;
    s8 value;

    player = &g_Player;
    g_Player.stun_timer = -1;
    if (damage != 0) {
        if (g_Player.armor_parts & 2) {
            if (damage < 3) {
                amount = 1;
            } else {
                amount = (damage / 3) * 2;
            }
            player->hp = (u8)(player->hp - amount);
        } else {
            g_Player.hp = (u8)(g_Player.hp - damage);
        }
    }
    if (player->hp > 0) {
        value = player->hp | 0x80;
    } else {
        value = -0x80;
        player->stun_timer = 0;
    }
    player->hp = value;
}

void player_set_idle_animation(struct PlayerObj* self)
{
    if (self->hp >= (engine_obj.unk46 / 3)) {
        player_set_animation(self, 5);
    } else {
        player_set_animation(self, 6);
    }
}

void player_air_steer(struct PlayerObj* self)
{
    if (!self->input_locked && (self->input.buttons.held & (PLAYER_INPUT_RIGHT | PLAYER_INPUT_LEFT))) {
        if (self->input.buttons.held & PLAYER_INPUT_RIGHT) {
            self->unk15 = 0x40;
            if (!(self->unk88.bytes.collision_flags & PLAYER_COLLIDE_RIGHT)) {
                if (self->dash_momentum != 0) {
                    self->x_vel.val = FIXED(4.125);
                } else {
                    self->x_vel.val = FIXED(2);
                }
            } else {
                self->x_vel.val = 0;
            }
        } else {
            self->unk15 = 0;
            if (!(self->unk88.bytes.collision_flags & PLAYER_COLLIDE_LEFT)) {
                if (self->dash_momentum != 0) {
                    self->x_vel.val = FIXED(-4.125);
                } else {
                    self->x_vel.val = FIXED(-2);
                }
            } else {
                self->x_vel.val = 0;
            }
        }
    } else {
        self->x_vel.val = 0;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
}

void player_spawn_dash_dust(struct PlayerObj* self)
{
    struct VisualObj* visual_obj;
    u8 bg_offset;

    visual_obj = find_free_visual_obj();
    if (visual_obj != NULL) {
        visual_obj->active = 0x21;
        visual_obj->id = 1;
        bg_offset = self->bg_offset;
        visual_obj->bg_offset = bg_offset;
        visual_obj->state = 0;
        visual_obj->unk5 = 0;
        visual_obj->unk6 = 0;
    }
}

void player_spawn_dash_spark(struct PlayerObj* self)
{
    u8 facing;
    struct VisualObj* visual_obj;
    s32* sprite_frames;

    if (func_8002D900(self) == 0x24) {
        player_spawn_dash_splash(self);
        return;
    }

    visual_obj = find_free_visual_obj();
    if (visual_obj == NULL) {
        return;
    }

    visual_obj->active = 0x21;
    visual_obj->id = 3;
    visual_obj->unk2 = 2;
    visual_obj->state = 0;
    visual_obj->unk5 = 0;
    visual_obj->unk6 = 0;
    visual_obj->bg_offset = self->bg_offset;
    sprite_frames = SP_SPRITE_FRAMES;
    visual_obj->unk38 = 0;
    visual_obj->unk3C = (u8*)sprite_frames + sprite_frames[1];
    visual_obj->animation_table = D_8011BF40;
    visual_obj->unk42 = 0x7804;
    visual_obj->unk40 = 0;
    visual_obj->unk16 = 1;
    facing = self->unk15;
    visual_obj->unk15 = facing;
    if (facing == 0) {
        visual_obj->x_pos.i.hi = self->x_pos.u.hi + player_dash_effect_offsets[self->unk2 * 2];
    } else {
        visual_obj->x_pos.i.hi = self->x_pos.u.hi - player_dash_effect_offsets[self->unk2 * 2];
    }
    visual_obj->y_pos.i.hi = self->y_pos.u.hi + player_dash_effect_offsets[self->unk2 * 2 + 1];
}

void player_spawn_dash_splash(struct PlayerObj* self)
{
    s16 x_pos;
    u8 facing;
    struct VisualObj* visual_obj;
    s32* menu_frames;
    s32 column;
    s32 row;
    s32 index;
    u8 bg_offset;

    if (func_8002D900(self) == 0x24) {
        visual_obj = find_free_visual_obj();
        if (visual_obj != NULL) {
            visual_obj->active = 0x41;
            visual_obj->id = 3;
            visual_obj->unk2 = 8;
            bg_offset = self->bg_offset;
            visual_obj->unk16 = 1;
            visual_obj->animation_table = D_8011BF40;
            visual_obj->bg_offset = bg_offset;
            index = func_8002938C(0x84) & 0xFF;
            menu_frames = SP_MENU_FRAMES;
            visual_obj->unk3C = (u8*)menu_frames + menu_frames[index];
            index = func_8002938C(0x84) & 0xFF;
            visual_obj->unk40 = D_801406A8[index] >> 7;
            column = func_8002938C(0x84);
            row = func_8002938C(0x84);
            visual_obj->unk42 = (((column & 0xFF) * 4 + 0x18) % 16) | ((((row & 0xFF) + 6) / 4 + 0x1E0) << 6);
            facing = self->unk15;
            visual_obj->unk15 = facing;
            if (facing == 0) {
                x_pos = self->x_pos.u.hi + player_dash_effect_offsets[4 + self->unk2];
            } else {
                x_pos = self->x_pos.u.hi - player_dash_effect_offsets[4 + self->unk2];
            }
            visual_obj->x_pos.i.hi = x_pos;
            visual_obj->y_pos.i.hi = self->y_pos.u.hi;
        }
    }
}

extern f32 player_wall_kick_spark_offsets[];

void player_spawn_wall_kick_spark(struct PlayerObj* self)
{
    u8 facing;
    struct VisualObj* visual_obj;
    s32* sprite_frames;

    visual_obj = find_free_visual_obj();
    if (visual_obj != 0) {
        visual_obj->active = 0x21;
        visual_obj->id = 3;
        visual_obj->unk2 = 1;
        visual_obj->bg_offset = self->bg_offset;
        visual_obj->state = 0;
        visual_obj->unk5 = 0;
        visual_obj->unk6 = 0;
        sprite_frames = SP_SPRITE_FRAMES;
        visual_obj->unk38 = 0;
        visual_obj->unk3C = (u8*)sprite_frames + sprite_frames[1];
        visual_obj->animation_table = D_8011BF40;
        visual_obj->unk40 = 0;
        visual_obj->unk42 = 0x7802;
        visual_obj->unk16 = 0;
        facing = self->unk15;
        visual_obj->unk15 = facing;
        if (facing == 0) {
            visual_obj->x_pos.i.hi = self->x_pos.u.hi + player_wall_kick_spark_offsets[self->unk2].u.lo;
        } else {
            visual_obj->x_pos.i.hi = self->x_pos.u.hi - player_wall_kick_spark_offsets[self->unk2].u.lo;
        }
        visual_obj->y_pos.i.hi = self->y_pos.u.hi + player_wall_kick_spark_offsets[self->unk2].u.hi;
    }
}

void player_spawn_wall_slide_dust(struct PlayerObj* self)
{
    struct VisualObj* visual_obj;

    visual_obj = find_free_visual_obj();
    if (visual_obj != NULL) {
        visual_obj->active = 0x21;
        visual_obj->id = 0;
        visual_obj->bg_offset = self->bg_offset;
        visual_obj->state = 0;
        visual_obj->unk5 = 0;
        visual_obj->unk6 = 0;
    }
}

void player_start_script_action(s8 action, s8 facing)
{
    g_Player.script_state = 1;
    g_Player.script_action = action;
    g_Player.script_facing = facing;
    g_Player.spike_immune = 1;
    engine_obj.unk1C = 1;
}

void player_end_script_action(void)
{
    g_Player.script_state = 0;
    g_Player.spike_immune = 0;
    engine_obj.unk1C = 0;
}

void player_check_splash_tile(struct PlayerObj* self)
{
    if (func_8002D994(self) == 0x24) {
        s16 y = self->y_pos.u.hi & 0xFFF0;
        func_80036BF4(self, y);
    }
}

void player_check_splash(struct PlayerObj* self)
{
    if (func_8002D900(self) == 0x24) {
#ifdef MMX4_PC
        s16 temp = self->y_pos.i.hi;

        if (self->unk68 != NULL)
            temp += self->unk68->unk1 + self->unk68->unk3;
#else
        s16 temp = self->y_pos.i.hi + self->unk68->unk1 + self->unk68->unk3;
#endif
        func_80036BF4(self, temp & ~0xF);
    }
}

// player_spawn_splash
INCLUDE_ASM("main/nonmatchings/player_common", func_80036BF4);
struct WeaponObj* player_spawn_weapon(s8 active, s8 id, s8 type, struct PlayerObj* owner)
{
    struct WeaponObj* weapon = find_free_weapon_obj();

    if (weapon == NULL) {
        return NULL;
    }

    weapon->active = active;
    weapon->id = id;
    weapon->unk2 = type;
    weapon->bg_offset = g_Player.bg_offset;
    if (owner != NULL) {
        weapon->owner = owner;
    }
    return weapon;
}

struct VisualObj* player_spawn_visual(s8 active, s8 id, s8 variant, void* owner)
{
    struct VisualObj* visual_obj = find_free_visual_obj();

    if (visual_obj == NULL) {
        return NULL;
    }

    visual_obj->active = active;
    visual_obj->id = id;
    visual_obj->unk2 = variant;
    visual_obj->bg_offset = g_Player.bg_offset;
    if (owner) {
        visual_obj->unk50 = owner;
    }
    return visual_obj;
}
