// WeaponObj, weapon_object_update_funcs[24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35]
// 80097EEC..800985F4
#include "common.h"
#include "main/weapons/weapon_24_zero_saber.h"
#include "main/55C4.h"
#include "main/objects.h"

#ifdef MMX4_PC
#include "main/object_motion.h"
#include "main/player_common.h"
#include "main/sprite_animations.h"
#endif

void zero_saber_follow(struct WeaponObj*, struct PlayerObj*);

void zero_saber_update(struct WeaponObj* arg0)
{
    s32 var_a0;
    struct PlayerObj* ptr = &g_Player;

    var_a0 = 0;
    if (g_Player.hp == 0) {
        var_a0 = 1;
    }
    if (g_Player.input_locked != 0) {
        var_a0 = 1;
    }
    if (g_Player.actions_reset != 0) {
        var_a0 = 1;
    }
    if (arg0->unk84.word != g_Player.unk17) {
        var_a0 = 1;
    }
    if (var_a0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }

    if (arg0->state != 0) {
        animate_object(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.relative_step == 0) {
            ZeroObjectState(OBJECT_HEADER(arg0));
        } else {
            zero_saber_follow(arg0, ptr);
        }
    } else {
        func_80097FC4(arg0, ptr);
        zero_saber_follow(arg0, ptr);
    }
}

// zero_saber_init
#ifdef MMX4_PC
void func_80097FC4(struct WeaponObj* weapon, struct PlayerObj* player);
void func_800981CC(struct WeaponObj* self);
void func_80098474(struct MiscObj* self);
extern u8 zero_saber_animations[24];
// src/main/weapons/weapon_24_zero_saber.c

extern struct Unk_unk68 rakuhouha_orb_box[];
extern u8 ryuenjin_flame_animations[];
extern u16 ryuenjin_flame_offsets[8];
#endif

#ifdef MMX4_PC
void func_80097FC4(struct WeaponObj* weapon, struct PlayerObj* player)
{
    u8 animation;
    u8 palette;
    s32 index;

    weapon->on_screen = 1;
    if (weapon->id == 0x21) {
        weapon->active = 0x21;
        weapon->unk40 = 0;
        weapon->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 6);
    } else {
        weapon->unk40 = player->unk40;
        weapon->unk3C = player->unk3C;
    }
    weapon->unk42 = 0x7801;
    weapon->unk16 = 2;
    weapon->animation_table = player->animation_table;
    index = (weapon->id - 0x18) * 2;
    animation = zero_saber_animations[index];
    palette = zero_saber_animations[index + 1];
    if (palette == 3 && ((u8)player->boss_flags & 0x40)) {
        palette = 4;
    }
    if (weapon->id == 0x20 && weapon->unk2 != 0) {
        animation = 0x78;
    }
    if (weapon->id == 0x1C) {
        set_animation_frame(ANIMATED_OBJECT(weapon), 0x74, (u8)player->animation_step.fields.event & 0x1F);
        weapon->animation_step.fields.duration = player->animation_step.fields.duration;
    } else {
        set_animation(weapon, animation);
    }
    player_copy_palette(player, palette, 1);
    need_palette_load |= 1;
    weapon->state++;
}
#else
INCLUDE_ASM("main/nonmatchings/weapons/weapon_24_zero_saber", func_80097FC4);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/weapons/weapon_24_zero_saber", zero_saber_follow);
#else
void zero_saber_follow(struct WeaponObj* arg0, struct PlayerObj* arg1)
{
    u8 id;
    u8 value;

    arg0->x_pos.val = arg1->x_pos.val;
    arg0->y_pos.val = arg1->y_pos.val;
    arg0->unk15 = arg1->unk15;
    if (arg0->animation_step.fields.event == 0) {
        arg0->unk50 = 0;
    } else {
        arg0->unk50 = (u8*)&zero_saber_hit_boxes[arg0->animation_step.fields.event];
    }
    id = arg0->id;
    if (id - 0x18 < 2U) {
        value = arg0->unk2 + 1;
    } else {
        value = arg0->animation_step.fields.event;
    }
    arg0->unk64 = value;
    update_on_screen(BASE_OBJECT(arg0), 0x80, 0x80);
}
#endif

// WeaponObj, weapon_object_update_funcs[36]

// rakuhouha_orb_update
#ifdef MMX4_PC
void func_800981CC(struct WeaponObj* self)
{
    if (self->state == 0) {
        self->on_screen = 1;
        self->unk50 = rakuhouha_orb_box;
        self->animation_table = D_8011C018;
        self->unk42 = 0x7803;
        self->unk16 = 1;
        self->unk40 = 0;
        self->unk3C = (u8*)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[6];
        self->x_pos.u.hi = g_Player.x_pos.u.hi;
        self->y_pos.u.hi = g_Player.y_pos.u.hi + 0x15;
        self->unk15 = 0;
        set_velocity_from_angle(MOVING_OBJECT(self), (0x10 - self->unk2 * 2) & 0xFE);
        self->x_vel.val *= 7;
        self->y_vel.val *= 7;
        set_animation(self, self->unk2 + 0xA);
        move_object(MOVING_OBJECT(self));
        move_object(MOVING_OBJECT(self));
        move_object(MOVING_OBJECT(self));
        self->state++;
    } else {
        if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) != 0 || self->unk98 != 0) {
            ZeroObjectState(OBJECT_HEADER(self));
            return;
        }
        animate_object(ANIMATED_OBJECT(self));
        move_object(MOVING_OBJECT(self));
    }
    is_on_screen(BASE_OBJECT(self));
}
#else
INCLUDE_ASM("main/nonmatchings/weapons/weapon_24_zero_saber", func_800981CC);
#endif

// rising_flame_trail_update
void func_80098338(struct VisualObj* self)
{
    struct PlayerObj* player = &g_Player;
    s32 should_reset = player->hp == 0;

    if (player->input_locked != 0) {
        should_reset = 1;
    }
    if (player->actions_reset != 0) {
        should_reset = 1;
    }
    if (player->unk17 != 0x66) {
        should_reset = 1;
    }
    if (should_reset != 0) {
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }
    if (self->state != 0) {
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.relative_step == 0) {
            ZeroObjectState(OBJECT_HEADER(self));
            return;
        }
    } else {
        self->on_screen = 1;
        self->unk3C = player->unk3C;
        self->animation_table = player->animation_table;
        self->unk40 = player->unk40;
        self->unk42 = 0x7801;
        self->unk16 = 2;
        set_animation(self, 0x7C);
        self->state++;
    }
    self->x_pos.val = player->x_pos.val;
    self->y_pos.val = player->y_pos.val;
    self->unk15 = player->unk15;
    update_on_screen(BASE_OBJECT(self), 0x80, 0x80);
}

// ryuenjin_flame_update
#ifdef MMX4_PC
void func_80098474(struct MiscObj* self)
{
    if (self->state == 0) {
        u16 offset;
        self->on_screen = 1;
        self->unk3C = (u8*)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[6];
        self->animation_table = D_8011C018;
        self->unk40 = 0;
        self->unk42 = 0x7804;
        self->unk16 = 1;
        offset = ryuenjin_flame_offsets[(get_random() & 3) * 2];
        self->x_pos.u.hi = g_Player.x_pos.u.hi + (g_Player.unk15 ? -offset : offset);
        self->y_pos.u.hi = g_Player.y_pos.u.hi
            + ryuenjin_flame_offsets[(get_random() & 3) * 2 + 1];
        self->unk15 = g_Player.unk15;
        set_animation(self, ryuenjin_flame_animations[get_random() & 3]);
        self->state++;
    } else {
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.relative_step == 0) {
            ZeroObjectState(OBJECT_HEADER(self));
            return;
        }
    }
    update_on_screen(BASE_OBJECT(self), 0x18, 0x18);
}
#else
INCLUDE_ASM("main/nonmatchings/weapons/weapon_24_zero_saber", func_80098474);
#endif

struct Unk_unk68 rakuhouha_orb_box[] = {
    { -26, -26, 0x34, 0x34 },
};

struct Unk_unk68 zero_saber_hit_boxes[] = {
    { 0, 0, 0, 0 },
    { -23, -43, 0x1F, 0x1F },
    { -57, -43, 0x33, 0x36 },
    { -60, -39, 0x28, 0x3A },
    { -59, -16, 0x26, 0x24 },
    { -57, 5, 0x25, 0x10 },
    { -48, -9, 0x1E, 0x11 },
    { -66, -8, 0x49, 0x11 },
    { -67, -6, 0x69, 0x13 },
    { 18, -6, 0x20, 0x14 },
    { 20, -6, 0x1E, 0xF },
    { -13, -41, 0x2C, 0x1D },
    { -81, -44, 0x5B, 0x3E },
    { -83, -44, 0x4B, 0x4E },
    { -83, -34, 0x4C, 0x44 },
    { -83, -8, 0x4C, 0x29 },
    { -50, 6, 0x28, 0x1B },
    { -68, 4, 0x46, 0x1A },
    { -92, -16, 0x56, 0x2C },
    { -84, -16, 0x4A, 0x2C },
    { -54, -22, 0x44, 0x10 },
    { 8, -18, 0x1A, 0x14 },
    { -72, -36, 0x36, 0x3E },
    { -72, -6, 0x38, 0x30 },
    { -72, 11, 0x38, 0x1A },
    { -44, -32, 0x2B, 0x26 },
    { -64, -30, 0x4E, 0x34 },
    { -74, -26, 0x6A, 0x3E },
    { 8, -14, 0x18, 0x22 },
    { -44, -36, 0x2B, 0x26 },
    { -64, -34, 0x4E, 0x34 },
    { -74, -30, 0x6A, 0x3E },
    { 8, -18, 0x18, 0x22 },
    { -80, -36, 0x42, 0x30 },
    { -80, -28, 0x42, 0x28 },
    { -80, -6, 0x40, 0x12 },
    { 6, -26, 0x18, 0x14 },
    { 14, -18, 0x22, 0x22 },
    { -14, -10, 0x32, 0x18 },
    { -62, -10, 0x26, 0x18 },
    { -80, -16, 0x2A, 0x24 },
    { -80, -16, 0x2A, 0x24 },
    { -92, -16, 0x36, 0x24 },
    { -128, -16, 0x5A, 0x24 },
    { -128, -16, 0x5A, 0x24 },
    { -32, -12, 0x24, 0x50 },
    { -32, -12, 0x24, 0x50 },
    { -50, -56, 0x3E, 0x44 },
    { -54, -40, 0x34, 0x46 },
    { -54, 2, 0x44, 0x30 },
    { -32, 2, 0x3E, 0x34 },
    { -12, -14, 0x3C, 0x46 },
    { 2, -30, 0x34, 0x44 },
    { -16, -50, 0x46, 0x2E },
    { -32, -56, 0x40, 0x34 },
    { -8, -14, 0x20, 0x22 },
    { -60, 4, 0x46, 0x1E },
    { -64, -76, 0x3E, 0x54 },
    { -64, -76, 0x3E, 0x54 },
    { -64, -76, 0x3E, 0x54 },
    { -64, -76, 0x3E, 0x54 },
};

u8 zero_saber_animations[24] = {
    0x70,
    0x03,
    0x71,
    0x03,
    0x72,
    0x03,
    0x73,
    0x03,
    0x74,
    0x03,
    0x7D,
    0x09,
    0x75,
    0x03,
    0x76,
    0x03,
    0x77,
    0x05,
    0x79,
    0x07,
    0x7A,
    0x03,
    0x7B,
    0x08,
};

u8 ryuenjin_flame_animations[] = {
    0x13,
    0x14,
    0x15,
    0x14,
};

u16 ryuenjin_flame_offsets[8] = {
    0xFFCE,
    0xFFFA,
    0xFFE0,
    0x0000,
    0xFFEC,
    0xFFF2,
    0xFFE8,
    0x0002,
};
