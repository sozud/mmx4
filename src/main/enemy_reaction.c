// 80091E38..800922D8
#include "common.h"
#include "main/enemy_reaction.h"
#include "main/object_motion.h"
#include "main/55C4.h"
#ifdef MMX4_SATURN
#include "saturn/platform.h"
#endif
#include "main/xa_sequence_data.h"

struct Main76HandlerTable {
    void (*funcs[7])(struct MainObj*);
};

void spike_crawler_hit_flash(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6++;
        self->invincibility_timer = 0x28;
    }
    if (BLINK_CLOCK(self->invincibility_timer) & 7) {
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
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80091EC4(struct MainObj* self)
{
    s8 step;

    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->x_speed = 0;
        self->x_accel = 0;
        self->invincibility_timer = self->unk63 == 3 ? 0x12 : 3;
        self->ext.main_76.bounce_step = 2;
    }
    step = self->ext.main_76.bounce_step;
    self->ext.main_76.bounce_step = -step;
    self->x_pos.u.hi = (u16)(self->x_pos.u.hi + step);
    if ((s8)self->invincibility_timer % 9 != 0)
        self->unk42 &= 0x7FFF;
    else
        self->unk42 |= 0x8000;
    self->invincibility_timer = (u8)(self->invincibility_timer - 1);
    if (self->invincibility_timer == 0) {
        self->unk5 = 1;
        self->unk6 = 0;
        self->unk42 &= 0x7FFF;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/enemy_reaction", func_80091EC4);
#endif

void spike_crawler_hit_knockback(struct MainObj* self)
{
    s32 speed;
    if (self->unk6 == 0) {
        self->unk6 = self->unk6 + 1;
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

void enemy_hit_reaction(struct MainObj* arg0)
{
    struct Main76HandlerTable handlers = { {
        NULL,
        spike_crawler_hit_flash,
        NULL,
        func_80091EC4,
        func_80091EC4,
        spike_crawler_hit_knockback,
        spike_crawler_hit_knockback,
    } };
    struct MainObj* object = arg0;

    handlers.funcs[object->unk63](arg0);
}

#ifdef MMX4_SATURN
void play_boss_voice(s32 arg0)
{
    u8 object_id = arg0 & 0xFF;

    if (object_id >= 8) {
        u8 track = object_id * 3 + (get_random() & 0xFF) % 3U + 0x21;
        saturn_music_play(track, 0);
        engine_obj.unk36.value = 1;
    } else {
        engine_obj.unk36.value = 0x3C;
    }
}
#else
void play_boss_voice(s32 arg0)
{
    s16 object_id;
    u32 random_value;

#ifndef VERSION_JP
    object_id = arg0 & 0xFF;
    if (object_id >= 8U) {
#endif
        random_value = get_random() & 0xFF;
        random_value %= 3U;
#ifdef VERSION_JP
#endif
        func_8001663C(boss_voice_tracks[(arg0 & 0xFF)][random_value & 0xFF], 0x7F);
        engine_obj.unk36.value = 1;
#ifndef VERSION_JP
    } else {
        engine_obj.unk36.value = 0x3C;
    }
#endif
}
#endif

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

s32 spike_crawler_knockback_speeds[2] = { FIXED(3), FIXED(10) };

u8 boss_voice_tracks[13][3] = {
    { VOICE_WEB_SPIDER_1, VOICE_WEB_SPIDER_1, VOICE_WEB_SPIDER_2 },
    { VOICE_FROST_WALRUS_1, VOICE_FROST_WALRUS_2, VOICE_FROST_WALRUS_3 },
    { VOICE_SPLIT_MUSHROOM_1, VOICE_SPLIT_MUSHROOM_2, VOICE_SPLIT_MUSHROOM_3 },
    { VOICE_MAGMA_DRAGOON_1, VOICE_MAGMA_DRAGOON_2, VOICE_MAGMA_DRAGOON_3 },
    { VOICE_JET_STINGRAY_1, VOICE_JET_STINGRAY_2, VOICE_JET_STINGRAY_3 },
    { VOICE_CYBER_PEACOCK_1, VOICE_CYBER_PEACOCK_2, VOICE_CYBER_PEACOCK_3 },
    { VOICE_STORM_OWL_1, VOICE_STORM_OWL_2, VOICE_STORM_OWL_3 },
    { VOICE_SLASH_BEAST_1, VOICE_SLASH_BEAST_2, VOICE_SLASH_BEAST_3 },
    { VOICE_COLONEL_1, VOICE_COLONEL_2, VOICE_COLONEL_3 },
    { VOICE_IRIS_1, VOICE_IRIS_2, VOICE_IRIS_3 },
    { VOICE_DOUBLE_1, VOICE_DOUBLE_2, VOICE_DOUBLE_3 },
    { VOICE_GENERAL_1, VOICE_GENERAL_2, VOICE_GENERAL_3 },
    { VOICE_SIGMA_1, VOICE_SIGMA_2, VOICE_SIGMA_3 },
};

u8 D_80105FEF_padding = 0;
