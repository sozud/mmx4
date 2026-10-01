// WeaponObj, weapon_object_update_funcs[3]
// 80094A78..800951C0
#include "common.h"

void soul_body_update(struct WeaponObj* arg0)
{
    s32 var_a1;

    var_a1 = 0;
    if (g_Player.input_locked != 0) {
        var_a1 = 1;
    }
    if (g_Player.capsule_state != 0) {
        var_a1 = 1;
    }
    if (g_Player.weapon != 3) {
        var_a1 = 1;
    }
    if (g_Player.actions_reset != 0) {
        var_a1 = 1;
    }
    if (g_Player.hp == 0) {
        var_a1 = 1;
    }
    if (var_a1 != 0) {
        arg0->state = 3;
    }
    soul_body_state_funcs[arg0->state](arg0);
}

void soul_body_init(struct WeaponObj* arg0)
{
    u32** animation_table;

    arg0->on_screen = 1;
    arg0->unk50 = soul_body_hit_box;
    arg0->unk64 = 1;
    arg0->unk38 = g_Player.unk38;
    arg0->unk3C = g_Player.unk3C;
    animation_table = g_Player.animation_table;
    arg0->unk40 = 0x500;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 1;
    arg0->animation_table = animation_table;
    arg0->unk15 = g_Player.unk15;
    arg0->animation_step.fields.frame_index = g_Player.animation_step.fields.frame_index;
    arg0->x_pos.val = g_Player.x_pos.val;
    arg0->y_pos.val = g_Player.y_pos.val;
    arg0->ext.weapon_3.lifetime = 0x96;
    arg0->ext.weapon_3.offset = 0;
    arg0->ext.weapon_3.unk90 = 0;
    arg0->ext.weapon_3.unk91 = 8;
    func_8001540C(1, 9, arg0);
    arg0->unk5 = 0;
    arg0->state = (u8)arg0->state + 1;
    update_on_screen(BASE_OBJECT(arg0), 0x80, 0x20);
}

void soul_body_main(struct WeaponObj* self)
{
    struct Weapon3Ext* ext = &self->ext.weapon_3;
    s8 timer;

    self->y_pos.val = g_Player.y_pos.val;
    self->animation_step.fields.frame_index = g_Player.animation_step.fields.frame_index;
    self->unk15 = g_Player.unk15;
    soul_body_step_funcs[self->unk5](self);

    if (BLINK_TIMER.unk0 & 1) {
        soul_body_load_palette(soul_body_palettes[ext->unk90]);
        ext->unk90 += 1;
        if (ext->unk90 == 6) {
            ext->unk90 = 0;
        }
    }

    if (self->unk50 != NULL) {
        timer = ext->unk91;
        if (timer == 0) {
            ext->unk91 = 8;
            self->unk64++;
        } else {
            ext->unk91 = timer - 1;
        }
    }

    if (self->on_screen != 0) {
        update_on_screen(BASE_OBJECT(self), 0x80, 0x20);
    }
}

void soul_body_extend(struct WeaponObj* arg0)
{
    u16* offset_ptr;
    s16 x_pos;
    s16 offset;

    arg0->on_screen = 1;
    offset_ptr = &arg0->ext.weapon_3.offset;
    if (arg0->unk15 != 0) {
        arg0->x_pos.i.hi = g_Player.x_pos.u.hi + *offset_ptr;
    } else {
        arg0->x_pos.i.hi = g_Player.x_pos.u.hi - *offset_ptr;
    }

    offset = *(s16*)offset_ptr;
    if (offset == 0x40) {
        arg0->unk5++;
        return;
    }
    *(s16*)offset_ptr = offset + 8;
}

void soul_body_hold(struct WeaponObj* arg0)
{
    u16 temp_v0;
    u16* field_8c;

    field_8c = &arg0->ext.weapon_3.offset;
    if (arg0->unk15 != 0) {
        arg0->x_pos.i.hi = g_Player.x_pos.u.hi + 0x40;
    } else {
        arg0->x_pos.i.hi = g_Player.x_pos.u.hi - 0x40;
    }

    temp_v0 = field_8c[1];
    if (temp_v0 == 0) {
        arg0->on_screen = 1;
        arg0->unk50 = 0;
        arg0->unk5++;
        return;
    }

    if (temp_v0 <= 0x1E) {
        arg0->on_screen ^= 1;
    }
    field_8c[1]--;
}

void soul_body_retract(struct WeaponObj* arg0)
{
    s16 temp_v0;
    s16 var_v0;
    u16* field_8c;

    arg0->on_screen = 1;
    field_8c = &arg0->ext.weapon_3.offset;
    if (arg0->unk15 != 0) {
        arg0->x_pos.i.hi = (u16)g_Player.x_pos.i.hi + *field_8c;
    } else {
        arg0->x_pos.i.hi = (u16)g_Player.x_pos.i.hi - *field_8c;
    }

    temp_v0 = (s16)*field_8c;
    if (temp_v0 == 0) {
        arg0->state = 3;
    } else {
        *field_8c = temp_v0 - 8;
    }
}

void soul_body_despawn(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    g_Player.shot_count--;
    g_Player.special_shot_count--;
    ZeroObjectState((struct ObjectHeader*)arg0);
}

void soul_body_load_palette(s32 arg0)
{
    u16* var_a0;
    u16* var_v1;
    u32 var_a1;

    var_a1 = 0;
    var_a0 = SP_PALETTE_BANK[(s16)arg0];
    var_v1 = SP_PALETTES[1];
    do {
        *var_v1++ = *var_a0++;
        var_a1 += 1;
    } while (var_a1 < 0x10U);
    need_palette_load |= 1;
}

void soul_body_clone_update(void)
{
    s32 var_a0;
    struct BackgroundObj* obj;
    struct PlayerObj* entity = &g_Entity;

    obj = &background_objects[g_Player.bg_offset];
    if (entity->active != 0) {
        var_a0 = 0;
        if (g_Player.input_locked != 0) {
            var_a0 = 1;
        }
        if (g_Player.capsule_state != 0) {
            var_a0 = 1;
        }
        if (g_Player.weapon != 3) {
            var_a0 = 1;
        }
        if (g_Player.actions_reset != 0) {
            var_a0 = 1;
        }
        if (g_Player.hp == 0) {
            var_a0 = 1;
        }
        if (entity->y_pos.i.hi >= obj->y_pos.i.hi + 328) {
            var_a0 = 1;
        }
        if (var_a0 != 0) {
            entity->active = 0;
            entity->on_screen = 0;
            g_Player.controlling_clone = 0;
            g_Player.spike_immune = 0;
            return;
        }
        engine_obj.unk38 = entity;
        if (entity->unk5 != 0x25) {
            if (--entity->clone_timer == 0) {
                player_set_animation(entity, 0x62);
                entity->on_screen = 1;
                entity->unk5 = 0x25;
            }
        }
        entity->unk18.val = entity->x_pos.val;
        entity->unk1C.val = entity->y_pos.val;
        player_state_funcs[entity->state](entity);
        if (entity->active != 0) {
            CollisionRelated(entity);
            if (entity->x_pos.i.hi <= obj->x_pos.i.hi) {
                entity->x_pos.i.hi = obj->x_pos.i.hi;
            }
            if (entity->x_pos.i.hi >= (obj->x_pos.i.hi + 320)) {
                entity->x_pos.i.hi = obj->x_pos.i.hi + 320;
            }
            if (entity->y_pos.i.hi <= obj->y_pos.i.hi) {
                entity->y_pos.i.hi = obj->y_pos.i.hi;
            }
            decompress_player_gfx(GRAPHICS_OBJECT(entity), 320, 64);
            if (entity->clone_timer != 0 && entity->clone_timer < 60) {
                entity->on_screen ^= 1;
            }
        }
    }
}

struct Unk_unk68 soul_body_hit_box[] = {
    { -21, -24, 0x28, 0x30 },
};

void (*soul_body_state_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))soul_body_init,
    (void (*)(struct WeaponObj*))soul_body_main,
    (void (*)(struct WeaponObj*))soul_body_despawn,
    (void (*)(struct WeaponObj*))soul_body_despawn,
};

void (*soul_body_step_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))soul_body_extend,
    (void (*)(struct WeaponObj*))soul_body_hold,
    (void (*)(struct WeaponObj*))soul_body_retract,
};

u8 soul_body_palettes[] = {
    0x35,
    0x36,
    0x37,
    0x38,
    0x37,
    0x36,
    0x00,
    0x00,
};
