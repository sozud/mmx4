// WeaponObj, weapon_object_update_funcs[1]
// 80092F08..80093CBC
#include "common.h"

void lightning_web_update(struct WeaponObj* self)
{
    s32 should_reset;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;

    should_reset = g_Player.input_locked != 0;
    if (g_Player.capsule_state != 0) {
        should_reset = 1;
    }
    if (g_Player.weapon != 1) {
        should_reset = 1;
    }
    if (should_reset != 0) {
        self->state = 3;
    }

    lightning_web_state_funcs[self->state](self);
    if (self->unk75 != 0) {
        collide_with_players(PLAYER_OBJECT(self));
        if (self->unk72 & 4) {
            g_Player.unk71 &= 0xB;
        }
        if (self->unk72 & 8) {
            g_Player.unk71 &= 7;
        }
    }
}

void lightning_web_init(struct WeaponObj* arg0)
{
    struct PlayerObj* player = &g_Player;
    s32* player_gfx;
    s32* sprite_frames;
    s32 gfx_offset;
    s32 frames_offset;
    struct Weapon1Ext* ext;

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    player_gfx = SP_PLAYER_GFX;
    arg0->unk50 = (const u8*)lightning_web_shot_box;
    gfx_offset = player_gfx[2];
    sprite_frames = SP_SPRITE_FRAMES;
    arg0->unk38 = (u8*)player_gfx + gfx_offset;
    frames_offset = sprite_frames[10];
    arg0->animation_table = D_8011C070;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + frames_offset;
    arg0->unk15 = player->unk15;
    ext = &arg0->ext.weapon_1;
    buster_shot_place_at_muzzle((struct VisualObj*)arg0, player, arg0->id);
    if (arg0->unk15 != 0) {
        arg0->x_vel.val = FIXED(8);
    } else {
        arg0->x_vel.val = FIXED(-8);
    }
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk49 = 0;
    ext->lifetime = 0x69;
    ext->timer = 0x10;
    set_animation(arg0, 0);
    func_8001540C(1, 8, arg0);
    arg0->unk5 = 0;
    arg0->state++;
    lightning_web_draw(arg0);
}

void lightning_web_fly(struct WeaponObj* arg0)
{
    u8 temp_v0;

    temp_v0 = arg0->ext.weapon_1.timer - 1;
    arg0->ext.weapon_1.timer = temp_v0;
    if (temp_v0 == 0) {
        set_animation(arg0, 1);
        arg0->unk16 = 3;
        arg0->state++;
    } else {
        animate_object(ANIMATED_OBJECT(arg0));
        move_object(MOVING_OBJECT(arg0));
    }
    lightning_web_draw(arg0);
}

void lightning_web_main(struct WeaponObj* arg0)
{
    s32 expired;
    u8 timer;

    if (func_8002B1E8(BASE_OBJECT(arg0), 0x18, 0x28) == 0) {
        timer = arg0->ext.weapon_1.lifetime - 1;
        expired = (timer & 0xFF) == 0;
        arg0->ext.weapon_1.lifetime = timer;
        if (arg0->unk72 & 0xC) {
            expired = 1;
        }
        if (expired != 0) {
            lightning_web_start_vanish(arg0);
        } else {
            lightning_web_step_funcs[arg0->unk5](arg0);
        }
        lightning_web_draw(arg0);
    } else {
        arg0->on_screen = 0;
        arg0->state = 3;
        arg0->unk50 = 0;
        arg0->unk75 = 0;
    }
}

void lightning_web_start_vanish(struct WeaponObj* arg0)
{
    set_animation(arg0, 3);
    arg0->unk50 = 0;
    arg0->unk75 = 0;
    arg0->state = 4;
    arg0->unk5 = 0;
}

void lightning_web_spread(struct WeaponObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        set_animation(arg0, 2);
        arg0->unk50 = (const u8*)lightning_web_net_box;
        arg0->unk68 = lightning_web_terrain_box;
        arg0->ext.weapon_1.unk90 = 0;
        arg0->unk75 = 1;
        arg0->unk5++;
    }
}

void lightning_web_hang(struct WeaponObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    lightning_web_buzz_sound(arg0, &arg0->ext.weapon_1.lifetime);
    if ((arg0->unk76 != 0) && ((arg0->unk72 & 3) != 0)) {
        set_animation(arg0, 4);
        if (arg0->unk72 & 1) {
            arg0->unk15 = 0x40;
        } else {
            arg0->unk15 = 0;
        }
        arg0->unk5++;
    }
}

void lightning_web_buzz_sound(struct WeaponObj* arg0, u8* arg1)
{
    if (arg1[4] == 0) {
        arg1[4] = 0xA;
        func_8001540C(0, 0x19, arg0);
        return;
    }
    arg1[4]--;
}

void lightning_web_stuck(struct WeaponObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->unk76 == 0) {
        set_animation(arg0, 5);
        arg0->unk5++;
    }
}

void lightning_web_release(struct WeaponObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        lightning_web_start_vanish(arg0);
    }
}

void lightning_web_despawn(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    arg0->unk75 = 0;
    if (arg0->unk2 == 0) {
        g_Player.shot_count--;
        g_Player.special_shot_count--;
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void lightning_web_vanish(struct WeaponObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->on_screen = 0;
        arg0->state = 3;
    } else {
        lightning_web_draw(arg0);
    }
}

void lightning_web_draw(struct WeaponObj* arg0)
{
    decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
    update_on_screen(BASE_OBJECT(arg0), 0x18, 0x28);
}

// WeaponObj, weapon_object_update_funcs[10]

void lightning_web_charged_update(struct WeaponObj* arg0)
{
    s32 disabled;

    disabled = g_Player.input_locked != 0;
    if (g_Player.capsule_state != 0) {
        disabled = 1;
    }
    if (g_Player.weapon != 1) {
        disabled = 1;
    }
    if (disabled != 0) {
        arg0->state = 3;
    }
    if (arg0->unk2 == 0) {
        lightning_web_charged_state_funcs[arg0->state](arg0);
    } else {
        lightning_web_charged_part_state_funcs[arg0->state](arg0);
    }
}

void lightning_web_charged_init(struct WeaponObj* arg0)
{
    struct PlayerObj* player = &g_Player;
    s32* player_gfx;
    s32* sprite_frames;
    s32 gfx_offset;
    s32 frames_offset;
    struct Weapon10Ext* ext;

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    player_gfx = SP_PLAYER_GFX;
    arg0->unk50 = (const u8*)lightning_web_charged_shot_box;
    gfx_offset = player_gfx[2];
    sprite_frames = SP_SPRITE_FRAMES;
    arg0->unk38 = (u8*)player_gfx + gfx_offset;
    frames_offset = sprite_frames[10];
    arg0->animation_table = D_8011C070;
    arg0->unk40 = 0x530;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + frames_offset;
    arg0->unk15 = player->unk15;
    ext = &arg0->ext.weapon_10;
    buster_shot_place_at_muzzle((struct VisualObj*)arg0, player, arg0->id);
    if (arg0->unk15 != 0) {
        arg0->x_vel.val = FIXED(8);
    } else {
        arg0->x_vel.val = FIXED(-8);
    }
    arg0->unk49 = 1;
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    ext->timer = 0x10;
    ext->unk8F = 0;
    set_animation(arg0, 0);
    func_8001540C(1, 8, arg0);
    arg0->unk5 = 0;
    arg0->state++;
    lightning_web_charged_draw(arg0);
}

void lightning_web_charged_main(struct WeaponObj* arg0)
{
    lightning_web_charged_step_funcs[arg0->unk5](arg0);
    lightning_web_charged_draw(arg0);
}

void lightning_web_charged_fly(struct WeaponObj* arg0)
{
    if (arg0->ext.weapon_10.timer == 0) {
        set_animation(arg0, 6);
        arg0->unk15 = 0;
        arg0->unk5++;
        return;
    }
    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    arg0->ext.weapon_10.timer--;
}

void lightning_web_charged_spread(struct WeaponObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        set_animation(arg0, 7);
        arg0->unk50 = (const u8*)lightning_web_charged_net_box;
        arg0->unk64 = 2;
        arg0->ext.weapon_10.timer = 0x3C;
        arg0->ext.weapon_10.unk90 = 0;
        arg0->unk5++;
    }
}

void lightning_web_charged_hold(struct WeaponObj* arg0)
{
    u8 temp_v0;

    animate_object(ANIMATED_OBJECT(arg0));
    lightning_web_buzz_sound(arg0, &arg0->ext.weapon_10.timer);
    temp_v0 = arg0->ext.weapon_10.timer;
    if (temp_v0 == 0) {
        temp_v0 = 0x98;
        arg0->ext.weapon_10.timer = temp_v0;
        arg0->ext.weapon_10.unk8F = 1;
        arg0->unk5++;
    } else {
        arg0->ext.weapon_10.timer = temp_v0 - 1;
    }
}

void lightning_web_charged_fade(struct WeaponObj* arg0)
{
    u8* timer_ptr;

    timer_ptr = &arg0->ext.weapon_10.timer;
    if (arg0->ext.weapon_10.timer == 0) {
        set_animation(arg0, 8);
        arg0->unk50 = 0;
        arg0->state = 4;
    } else {
        arg0->ext.weapon_10.timer--;
        animate_object(ANIMATED_OBJECT(arg0));
        lightning_web_buzz_sound(arg0, timer_ptr);
    }
}

// lightning_web_charged_part_init
INCLUDE_ASM("main/nonmatchings/weapons/weapon_01", func_80093930);

void lightning_web_charged_part_wait(struct WeaponObj* arg0)
{
    struct PlayerObj* owner;
    u8 state;
    s32 y;

    owner = arg0->owner;
    if ((u8)owner->shot_fired != 0) {
        arg0->on_screen = 1;
        state = (u8)arg0->state + 1;
        arg0->x_pos.val = owner->x_pos.val;
        y = owner->y_pos.val;
        arg0->ext.weapon_10.timer = 0x10;
        arg0->state = state;
        arg0->unk5 = 0;
        arg0->y_pos.val = y;
        lightning_web_charged_draw(arg0);
    }
}

void lightning_web_charged_part_main(struct WeaponObj* arg0)
{
    lightning_web_charged_part_step_funcs[arg0->unk5](arg0);
    lightning_web_charged_draw(arg0);
}

void lightning_web_charged_part_fly(struct WeaponObj* arg0)
{
    u8* timer;
    u8 temp_v0;

    timer = &arg0->ext.weapon_10.timer;
    if (arg0->animation_step.fields.relative_step == 0) {
        set_animation(arg0, 7);
    } else {
        animate_object(ANIMATED_OBJECT(arg0));
    }

    temp_v0 = *timer;
    if (temp_v0 == 0) {
        arg0->unk50 = (const u8*)lightning_web_charged_part_box;
        arg0->unk64 = 1;
        *timer = 0x78;
        arg0->unk5++;
        return;
    }

    *timer = temp_v0 - 1;
    move_object(MOVING_OBJECT(arg0));
}

void lightning_web_charged_part_hold(struct WeaponObj* arg0)
{
    u8 temp_v0;

    animate_object(ANIMATED_OBJECT(arg0));
    temp_v0 = arg0->ext.weapon_10.timer;
    if (temp_v0 == 0) {
        arg0->unk64 = 2;
        arg0->ext.weapon_10.timer = 0x10;
        arg0->unk5++;
        return;
    }
    arg0->ext.weapon_10.timer = temp_v0 - 1;
}

void lightning_web_charged_part_drift(struct WeaponObj* arg0)
{
    u8 timer;

    animate_object(ANIMATED_OBJECT(arg0));
    timer = arg0->ext.weapon_10.timer;
    if (timer == 0) {
        set_animation(arg0, 8);
        arg0->unk50 = 0;
        arg0->state = 4;
    } else {
        arg0->ext.weapon_10.timer = timer - 1;
        move_object(MOVING_OBJECT(arg0));
    }
}

void lightning_web_charged_vanish(struct WeaponObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->on_screen = 0;
        arg0->state = 3;
    } else {
        lightning_web_charged_draw(arg0);
    }
}

void lightning_web_charged_draw(struct WeaponObj* arg0)
{
    if (arg0->unk2 == 0) {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x30);
    }
    if (arg0->unk2 == 1) {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x40);
    }
    update_on_screen(BASE_OBJECT(arg0), 0x28, 0x28);
}

struct Unk_unk68 lightning_web_charged_shot_box[] = {
    { -8, -8, 0xE, 0xE },
};

struct Unk_unk68 lightning_web_charged_net_box[] = {
    { -22, -22, 0x2C, 0x2C },
};

struct Unk_unk68 lightning_web_charged_part_box[] = {
    { -22, -22, 0x2C, 0x2C },
};

void (*lightning_web_state_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))lightning_web_init,
    (void (*)(struct WeaponObj*))lightning_web_fly,
    (void (*)(struct WeaponObj*))lightning_web_main,
    (void (*)(struct WeaponObj*))lightning_web_despawn,
    (void (*)(struct WeaponObj*))lightning_web_vanish,
};

struct Unk_unk68 lightning_web_shot_box[] = {
    { -8, -8, 0xE, 0xE },
};

void (*lightning_web_step_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))lightning_web_spread,
    lightning_web_hang,
    (void (*)(struct WeaponObj*))lightning_web_stuck,
    (void (*)(struct WeaponObj*))lightning_web_release,
};

struct Unk_unk68 lightning_web_net_box[] = {
    { -12, -22, 0x18, 0x2A },
};

struct Unk_unk68 lightning_web_terrain_box[] = {
    { 0, 0, 8, 0x16 },
};

void (*lightning_web_charged_state_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))lightning_web_charged_init,
    (void (*)(struct WeaponObj*))lightning_web_charged_main,
    (void (*)(struct WeaponObj*))lightning_web_despawn,
    (void (*)(struct WeaponObj*))lightning_web_despawn,
    (void (*)(struct WeaponObj*))lightning_web_charged_vanish,
};

void (*lightning_web_charged_part_state_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80093930,
    (void (*)(struct WeaponObj*))lightning_web_charged_part_wait,
    (void (*)(struct WeaponObj*))lightning_web_charged_part_main,
    (void (*)(struct WeaponObj*))lightning_web_despawn,
    (void (*)(struct WeaponObj*))lightning_web_charged_vanish,
};

void (*lightning_web_charged_step_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))lightning_web_charged_fly,
    (void (*)(struct WeaponObj*))lightning_web_charged_spread,
    (void (*)(struct WeaponObj*))lightning_web_charged_hold,
    (void (*)(struct WeaponObj*))lightning_web_charged_fade,
};

void (*lightning_web_charged_part_step_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))lightning_web_charged_part_fly,
    (void (*)(struct WeaponObj*))lightning_web_charged_part_hold,
    (void (*)(struct WeaponObj*))lightning_web_charged_part_drift,
};
