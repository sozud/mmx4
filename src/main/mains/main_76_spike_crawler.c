// MainObj, main_object_update_funcs[76]
// 800919C4..800922D8
#include "common.h"

void spike_crawler_update(struct MainObj* self)
{
    spike_crawler_state_funcs[self->state](self);
}

void spike_crawler_init(struct MainObj* arg0)
{
    struct MainObj* self = arg0;

    self->state = 1;
    self->hp = 3;
    self->contact_damage = 4;
    self->animation_table = (const u8* const*)spike_crawler_animations;
    self->hurt_box = spike_crawler_hurt_box;
    self->attack_box = spike_crawler_attack_box;
    self->terrain_box = (struct Unk_unk68*)spike_crawler_terrain_box;
    self->collision_data = D_80108484;
    self->x_speed = FIXED(2);
    self->unk5 = 0;
    self->unk6 = 0;
    self->unk7C = 0;
    self->unk7E = 0;
    self->bg_offset = 0;
    self->invincibility_timer = 0;
    self->air_state = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->unk16 = 5;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    self->ext.main_76.saved_x_velocity = self->x_speed;
    set_animation(self, 0);
}

void spike_crawler_fall(struct MainObj* self)
{
    if (self->collision_flags & 8) {
        self->unk5 = 0;
        self->unk6 = 0;
        self->unk7C = 0;
        self->x_speed = self->ext.main_76.saved_x_velocity;
        self->y_speed = 0;
        self->x_accel = 0;
        self->gravity = 0;
        return;
    }

    move_with_gravity(ANIMATED_OBJECT(self));
}

// spike_crawler_crawl
INCLUDE_ASM("main/nonmatchings/mains/main_76_spike_crawler", func_80091B1C);

void spike_crawler_update_speed(struct MainObj* self)
{
    s16 object_y;
    s16 player_y;
    s16 current_timer;
    s16 new_timer;
    s32 distance;
    s32 velocity;

    object_y = self->y_pos.u.hi - 8;
    player_y = g_Player.y_pos.i.hi;
    distance = player_y - object_y;

    if (distance >= 0) {
        if (distance < 0x10) {
            goto close_range;
        }
        goto far_range;
    }
    if ((object_y - player_y) < 0x10) {
        goto close_range;
    }
    goto far_range;

close_range:
    velocity = self->x_speed;
    if (velocity < 0) {
        velocity = FIXED(-4);
    } else {
        velocity = FIXED(4);
    }
    self->x_speed = velocity;
    new_timer = 0x78;
    goto store_timer;

far_range:
    current_timer = self->unk7E;
    if (current_timer == 0) {
        if (self->x_speed < 0) {
            self->x_speed = FIXED(-2);
        } else {
            self->x_speed = FIXED(2);
        }
        return;
    }
    new_timer = current_timer - 1;

store_timer:
    self->unk7E = new_timer;
}

void spike_crawler_main(struct MainObj* self)
{
    s32 collision;

    self->unk18.val = self->x_pos.val;
    self->on_screen = 0;
    self->unk1C.val = self->y_pos.val;

    if (self->unk5 == 0) {
        if (self->unk7C != 0) {
            self->unk7C--;
        }
        spike_crawler_update_speed(self);
        if (self->unk7C == 0) {
            func_80091B1C(self);
        }
    } else {
        spike_crawler_fall(self);
    }

    CollisionRelated(PLAYER_OBJECT(self));
    collision = func_8002DD04(self);
    if (collision < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(4, spike_crawler_debris, self);
        self->state = 2;
        return;
    }

    if (collision != 0) {
        self->unk7C = 0x3C;
    }
    func_8002D9BC(self);
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
    } else {
        self->state = 2;
    }
}

void spike_crawler_despawn(struct MainObj* self)
{
    despawn_object(OBJECT_HEADER(self));
}

void spike_crawler_hit_flash(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6++;
        self->invincibility_timer = 0x28;
    }
    if (self->invincibility_timer & 7) {
        self->unk42 &= 0x7FFF;
    } else {
        self->unk42 |= 0x8000;
    }
    if (--self->invincibility_timer == 0) {
        self->unk5 = 1;
        self->unk6 = 0;
        self->unk42 &= 0x7FFF;
    }
}

// spike_crawler_hit_bounce
INCLUDE_ASM("main/nonmatchings/mains/main_76_spike_crawler", func_80091EC4);

extern s32 spike_crawler_knockback_speeds[2];

void spike_crawler_hit_knockback(struct MainObj* self)
{
    s8 step;
    s32 speed;

    step = self->unk6;
    if (step == 0) {
        self->unk6 = step + 1;
        if (g_Player.x_pos.val < self->x_pos.val) {
            self->x_speed = spike_crawler_knockback_speeds[self->unk63 - 5];
        } else {
            self->x_speed = -spike_crawler_knockback_speeds[self->unk63 - 5];
        }
        self->x_accel = 0x3000;
        self->y_speed = 0;
        self->gravity = 0;
        if (self->unk63 == 5) {
            self->invincibility_timer = 0x12;
        } else {
            self->invincibility_timer = 1;
        }
    }

    move_with_gravity(ANIMATED_OBJECT(self));

    speed = self->x_speed;
    if (speed < 0) {
        speed = -speed;
    }
    if (speed < 0x6000) {
        self->x_speed = 0;
        self->x_accel = 0;
    }
    if (self->collision_flags & 3) {
        self->x_speed = 0;
        self->x_accel = 0;
    }

    if ((s8)self->invincibility_timer % 9 != 0) {
        self->unk42 &= 0x7FFF;
    } else {
        self->unk42 |= 0x8000;
    }

    self->invincibility_timer--;
    if (self->invincibility_timer == 0) {
        self->unk5 = 1;
        self->unk6 = 0;
        self->x_speed = 0;
        self->x_accel = 0;
        self->unk42 &= 0x7FFF;
    }
}

void enemy_hit_reaction(void* arg0)
{
    struct Main76HandlerTable handlers = { {
        NULL,
        (void (*)(void*))spike_crawler_hit_flash,
        NULL,
        (void (*)(void*))func_80091EC4,
        (void (*)(void*))func_80091EC4,
        (void (*)(void*))spike_crawler_hit_knockback,
        (void (*)(void*))spike_crawler_hit_knockback,
    } };
    struct MainObj* object = arg0;

    handlers.funcs[object->unk63](arg0);
}

union AnimationStep spike_crawler_anim_0[16] = {
    { 0x00010002 },
    { 0x01010002 },
    { 0x02010002 },
    { 0x03010002 },
    { 0x04010002 },
    { 0x05010002 },
    { 0x06010002 },
    { 0x07010002 },
    { 0x08010002 },
    { 0x09010002 },
    { 0x0A010002 },
    { 0x0B010002 },
    { 0x0C010002 },
    { 0x0D010002 },
    { 0x0E010002 },
    { 0x0FF10002 },
};

union AnimationStep spike_crawler_anim_1[1] = { { 0x10000002 } };

union AnimationStep spike_crawler_anim_2[1] = { { 0x11000002 } };

union AnimationStep spike_crawler_anim_3[1] = { { 0x12000002 } };

union AnimationStep spike_crawler_anim_4[1] = { { 0x13000002 } };

union AnimationStep* spike_crawler_animations[5] = {
    spike_crawler_anim_0,
    spike_crawler_anim_1,
    spike_crawler_anim_2,
    spike_crawler_anim_3,
    spike_crawler_anim_4,
};

u8 spike_crawler_debris[4] = { 1, 2, 3, 4 };

s8 spike_crawler_terrain_box[4] = { -1, 0, 11, 11 };

s8 spike_crawler_attack_box[4] = { -9, -6, 16, 15 };

s8 spike_crawler_hurt_box[4] = { -11, -8, 20, 18 };

void play_boss_voice(s32 arg0)
{
    u32 object_id;
    u32 random_value;

#ifndef VERSION_JP
    object_id = arg0 & 0xFF;
    if (object_id >= 8U) {
#endif
        random_value = get_random() & 0xFF;
        random_value %= 3U;
#ifdef VERSION_JP
        object_id = arg0 & 0xFF;
#endif
        func_8001663C(boss_voice_tracks[object_id][random_value & 0xFF], 0x7F);
        engine_obj.unk36.value = 1;
#ifndef VERSION_JP
    } else {
        engine_obj.unk36.value = 0x3C;
    }
#endif
}

s32 update_boss_music_delay(void)
{
#ifdef VERSION_JP
    if (D_80173C84 == 0) {
        engine_obj.unk36.timer = 0;
        func_8001653C();
    }
#else
    if ((D_80173C84 == 0) && (engine_obj.unk36.timer != 0)) {
        engine_obj.unk36.timer--;
        if (engine_obj.unk36.timer == 0) {
            engine_obj.unk36.timer = 0;
            func_8001653C();
        }
    }
#endif
    return engine_obj.unk36.timer;
}

void (*spike_crawler_state_funcs[])(struct MainObj*) = {
    spike_crawler_init,
    spike_crawler_main,
    spike_crawler_despawn,
};

extern s32 spike_crawler_knockback_speeds[2];

extern u8 boss_voice_tracks[13][3];

extern u8 D_80105FEF_padding;
