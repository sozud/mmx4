// MainObj, main_object_update_funcs[39]
// 80061590..80061DC0
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_39_falling_ceiling.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/CB184.h"
#include "main/object_motion.h"
#include "main/objects.h"
#include "main/collision_bounds.h"
#include "main/visuals/visual_03_small_effect.h"
#include "main/stage_objects.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/collision_bounds.h"
#include "main/stage_objects.h"
#include "main/visuals/visual_03_small_effect.h"
#endif

void falling_ceiling_main(struct MainObj*);
void falling_ceiling_despawn(struct MainObj*);

// falling_ceiling_step_funcs
extern void (*falling_ceiling_step_funcs[])(struct MainObj*);

void falling_ceiling_drop(struct MainObj* arg0);
void falling_ceiling_sink(struct MainObj* arg0);

// falling_ceiling_drop_funcs
void falling_ceiling_drop_start(struct MainObj*);

void falling_ceiling_drop_land(struct MainObj*);

extern void (*falling_ceiling_state_funcs[])(struct MainObj*);
extern void (*falling_ceiling_drop_funcs[])(struct MainObj*);

void falling_ceiling_update(struct MainObj* self)
{
    falling_ceiling_state_funcs[self->state](self);
}

// falling_ceiling_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
s32 func_8001540C(s32 arg0, s32 arg1, void* arg2);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80061B58(struct MainObj* self);
void func_80061918(struct MainObj* self);
void func_800615CC(struct MainObj* self);
extern s8 D_800FE944[4];
extern s8 D_800FE948[4];
extern s8 D_800FE94C[4];
extern union AnimationStep* falling_ceiling_animations[4];
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800615CC(struct MainObj* self)
{
    u8* ext;
    static const u16 top[6] = { 0xB20, 0xC20, 0xD20, 0xE20, 0xEA0, 0xF20 };
    static const u16 left[6] = { 0xB60, 0xC60, 0xD60, 0xE60, 0xEE0, 0xF60 };
    static const u16 center[6] = { 0xB70, 0xBF0, 0xCE0, 0xDD0, 0xE50, 0xEB0 };
    ext = (u8*)&self->ext;

    self->contact_damage = 0x14;
    self->hp = 6;
    self->invincibility_timer = 0;
    self->collision_data = D_801060F0;
    self->animation_table = (const u8* const*)falling_ceiling_animations;
    self->terrain_box = (struct Unk_unk68*)D_800FE94C;
    self->hurt_box = D_800FE944;
    self->attack_box = D_800FE948;
    self->air_state = 0;
    self->unk16 = VISUAL_SATURN_LAYER(6);
    self->unk15 = 0;
    self->bg_offset = g_Player.bg_offset;
    set_animation(self, 0);

    if ((u8)self->unk2 < 12) {
        u8 group = (u8)self->unk2 >> 1;
        *(u16*)(ext + 2) = top[group];
        if (!(self->unk2 & 1)) {
            *(u16*)(ext + 0) = left[group];
            *(u16*)(ext + 6) = group < 4 ? 0x188 : 0x180;
        }
        self->x_pos.val = (u32)(top[group] + ((self->unk2 & 1) ? 0x70 : 0x10)) << 16;
        *(u16*)(ext + 4) = center[group];
    }
    *(u32*)(ext + 0xC) = 0x1200000;
    self->y_pos.val = 0x1100000;
    ext[8] = 0;
    *(u32*)(ext + 0x10) = 0;
    ext[0x14] = 1;
    self->unk7E = 0;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0x2000;
    self->state = 1;
    self->unk5 = 0;
    self->unk6 = 0;
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_39_falling_ceiling", func_800615CC);
#endif

void falling_ceiling_main(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    falling_ceiling_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    func_8002DD04(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x1000, 0x40) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
        return;
    }
    self->state = 2;
}

void falling_ceiling_despawn(struct MainObj* self)
{
    self->ext.main_39.unk80.w = 0;
    self->ext.main_39.unk84.w = 0;
    despawn_object_permanently(OBJECT_HEADER(self));
}

// falling_ceiling_wait
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80061918(struct MainObj* self)
{
    struct Main39Ext* ext = &self->ext.main_39;
    s32 target_x;

    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->y_speed == 0x10000 || self->y_speed == -0x10000)
        self->gravity = -self->gravity;
    if (ext->unk88 == 0) {
        if (ext->unk84.h.unk84 < g_Player.x_pos.i.hi) {
            self->gravity = 0x2000;
            set_animation(self, 1);
            self->unk5 = 1;
        }
        return;
    }
    ext->unk8C += ext->unk90;
    ext->unk90 += 0x1000;
    if (ext->unk90 > 0x10000)
        ext->unk90 = 0x10000;
    if (ext->unk8C > 0x3000000)
        ext->unk8C = 0x3000000;
    if (g_Player.y_pos.val >= ext->unk8C || self->y_pos.val >= g_Player.y_pos.val)
        return;
    target_x = g_Player.x_pos.i.hi + (self->unk2 & 1 ? 0x10 : -0x10);
    if (target_x - self->x_pos.i.hi >= -0x10 && target_x - self->x_pos.i.hi <= 0x10) {
        self->gravity = 0x8000;
        self->unk5 = 2;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_39_falling_ceiling", func_80061918);
#endif

void falling_ceiling_drop(struct MainObj* self)
{
    falling_ceiling_drop_funcs[self->unk6](self);
}

void falling_ceiling_drop_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->y_pos.i.hi > 0x118) {
        self->y_speed = 0;
        self->gravity = 0;
    }
    if (self->animation_step.fields.event != 0) {
        self->unk7C = 0x3C;
        set_animation(self, 2);
        self->unk6 = 1;
    }
}

// falling_ceiling_drop_fall
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_39_falling_ceiling", func_80061B58);
#else
void func_80061B58(struct MainObj* self)
{
    s32 i;
    if (--self->ext.main_39.unk94 == 0) {
        func_8001540C(2, SATURN_SOUND(0x59, 0x40), self);
        self->ext.main_39.unk94 = 0x1E;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->y_pos.i.hi >= 0x119) {
        self->y_speed = 0;
        self->gravity = 0;
    }
    self->unk7E++;
    if ((self->unk7E & 7) == 0 && (!(background_objects[0].unk34 & 0x10) || (((u8*)&background_objects[0].unk3E)[0] & 7) != 4))
        start_screen_shake_x(8, 4, 2);
    if ((self->unk7E & 0xF) == 0)
        ((void (*)(s32, s32, s32, s32))spawn_explosion_at)(0, self->x_pos.i.hi, self->y_pos.i.hi + 0x10, 1);
    if (--self->unk7C != 0)
        return;
    if (self->unk2 & 1) {
        self->unk6 = 2;
        return;
    }
    for (i = 0; i < 2; i++) {
        struct ItemObj* item = find_free_item_obj();
        if (item != NULL) {
            item->active = 0x41;
            item->id = 0xF;
            if (self->unk2 < 8)
                item->unk2 = i;
            else
                item->unk2 = i + 2;
            item->bg_offset = self->bg_offset;
            item->x_pos.val = 0;
            item->x_pos.u.hi = self->ext.main_39.unk80.h.unk80;
            item->y_pos.val = 0;
            item->y_pos.u.hi = self->ext.main_39.unk84.h.unk86;
            item->state = 0;
        }
    }
    self->unk6 = 2;
}
#endif

void falling_ceiling_drop_land(struct MainObj* self)
{
    u8 object_id;

    animate_object(ANIMATED_OBJECT(self));
    object_id = self->unk2;
    if (!(object_id & 1)) {
        apply_tile_effect((s8)object_id / 2, self->ext.main_39.unk80.h.unk82, 0x120);
    }
    self->ext.main_39.unk88 = 1;
    self->gravity = FIXED(0.125);
    self->unk5 = 0;
    self->unk6 = 0;
}

void falling_ceiling_sink(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
}

s8 D_800FE944[4] = { -16, -7, 29, 29 };

s8 D_800FE948[4] = { -12, -5, 22, 26 };

s8 D_800FE94C[4] = { 0, 0, 16, 26 };

union AnimationStep falling_ceiling_anim_0[] = {
    { 1, 0, 1, 0x00 },
    { 1, 0, 1, 0x01 },
    { 1, 0, -2, 0x02 },
};

union AnimationStep falling_ceiling_anim_1[] = {
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x04 },
    { 1, 0, 1, 0x05 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x04 },
    { 1, 1, 0, 0x05 },
};

union AnimationStep falling_ceiling_anim_2[] = {
    { 3, 0, 1, 0x07 },
    { 3, 0, 1, 0x08 },
    { 3, 0, 1, 0x09 },
    { 3, 0, 1, 0x0A },
    { 3, 0, 1, 0x0B },
    { 3, 0, 1, 0x0C },
    { 3, 0, 1, 0x0D },
    { 3, 0, -7, 0x06 },
};

union AnimationStep* falling_ceiling_animations[4] = {
    falling_ceiling_anim_0,
    falling_ceiling_anim_1,
    falling_ceiling_anim_2,
    NULL,
};

void (*falling_ceiling_state_funcs[])(struct MainObj*) = {
    func_800615CC,
    falling_ceiling_main,
    falling_ceiling_despawn,
};

void (*falling_ceiling_step_funcs[3])(struct MainObj*) = {
    func_80061918,
    falling_ceiling_drop,
    falling_ceiling_sink,
};

void (*falling_ceiling_drop_funcs[3])(struct MainObj*) = { falling_ceiling_drop_start, func_80061B58, falling_ceiling_drop_land };
