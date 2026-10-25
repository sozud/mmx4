// RideArmorObj, D_800F2AD4[0]
// 8003B3DC..8003D3F8
#include "common.h"
#include "main/bike.h"
#include "main/misc/misc_00_static_sprite.h"
#include "main/objects.h"
#include "main/player_common.h"
#include "main/1CF60.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/object_motion.h"
#include "main/player_weapon.h"
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#define RIDE_U16(object, offset) (*(u16*)&RIDE_U8(object, offset))

MMX4_STATIC_ASSERT(ride_armor_tail_layout,
    MMX4_OFFSET_OF(struct RideArmorObj, saved_y_vel) - MMX4_OFFSET_OF(struct RideArmorObj, unk7C) == 0x9E - 0x7C);
MMX4_STATIC_ASSERT(ride_armor_player_unk9A,
    MMX4_OFFSET_OF(struct RideArmorObj, pad9A) == MMX4_OFFSET_OF(struct PlayerObj, shot_cycle));
extern s32 D_800F9090[2];
extern s32 D_800F9098[2];
void func_8003B458(void*, s8);
void func_8003CCBC(struct RideArmorObj*);

extern u8 ride_chaser_shot_hit_box[4];
extern u16 ride_chaser_shot_offsets[][2];
extern u8 ride_chaser_shot_angles[];
extern u8 ride_chaser_shot_animations[];
#endif

extern s32 D_800F9070[2];
extern s32 D_800F9078[2];
extern s32 D_800F9080[2];
extern s32 D_800F9088[2];

extern union AnimationStep D_800F8DC8[];

void func_8003D338(struct AnimatedObj*);
void func_8003D39C(struct MainObj*);

// D_800F90D8
extern void (*D_800F90D8[])(struct RideArmorObj*);

void func_8003BA24(struct RideArmorObj*);
void func_8003BAE8(struct RideArmorObj*);

void func_8003BDA0(struct RideArmorObj*);

void func_8003C8F4(struct RideArmorObj* arg0);
void func_8003CB08(struct RideArmorObj* arg0);
void func_8003CCBC(struct RideArmorObj* arg0);
void func_8003CD38(struct RideArmorObj* arg0);

void func_8003B3DC(struct RideArmorObj* arg0)
{
    arg0->unk8A = g_Player.input.buttons.held;
    arg0->unk8C.value = g_Player.pressed_input;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;

    D_800F90D8[arg0->state](arg0);
    arg0->hp &= ~0x80;
}

void func_8003B458(void* arg0, s8 arg1)
{
    g_Player.ride_animation = arg1;
    g_Player.unk6 = 0;
}

#define RIDE_U8(object, offset) (((u8*)&(object)->unk7C)[(offset)-0x7C])
extern union AnimationStep* D_800F8FC4[38];
extern u8 D_800F9068[4];
extern u8 D_800F906C[4];
extern u8 D_800F9100[4];
extern u8 D_800F9104[4];
extern u8 D_800F9108[4];
extern u8 D_800F910C[4];
extern u8 D_800F9110[4];
extern u8 D_800F9114[4];
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8003B470(struct RideArmorObj* arg0);
void func_8003B7B4(struct RideArmorObj* arg0);
void func_8003BB20(struct RideArmorObj* arg0);
static void ride_chaser_land_animation(struct RideArmorObj* arg0);
void func_8003BF1C(struct RideArmorObj* arg0);
void func_8003C08C(struct RideArmorObj* arg0);
void func_8003C6EC(struct RideArmorObj* arg0, u8 kind);
void func_8003CA44(struct RideArmorObj* arg0);
u8 func_8003CF24(struct RideArmorObj* arg0);
void func_8003D01C(struct RideArmorObj* arg0);
#define RIDE_S8(object, offset) (*(s8*)&RIDE_U8(object, offset))
extern u8 D_800F905C[12];
extern void (*D_800F90E8[])(struct RideArmorObj*);
void func_8003D164(struct VisualObj*, s32);
void func_8003CF6C(struct RideArmorObj*);
void func_8003CA44(struct RideArmorObj*);
void func_8003D01C(struct RideArmorObj*);
void func_8003D3B4(struct PlayerObj*);
void func_8003B98C(struct PlayerObj*);
void func_8003B694(struct RideArmorObj*);
void func_8003C9A4(struct RideArmorObj*);
extern ret_u8 func_8002938C(s32);
static void ride_chaser_land_animation(struct RideArmorObj* arg0)
{
    switch (arg0->unk80.bytes.unk82) {
    case 0:
        set_animation(arg0, 5);
        func_8003B458(arg0, 0x46);
        break;
    case 1:
        set_animation(arg0, 4);
        func_8003B458(arg0, 0x44);
        break;
    case 2:
        set_animation(arg0, 3);
        func_8003B458(arg0, 0x42);
        break;
    }
}
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/bike", func_8003B470);
#else
void func_8003B470(struct RideArmorObj* arg0)
{
    struct EffectObj* effect;
    u8 resource;

    arg0->state = 1;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->on_screen = 1;
    arg0->active |= 0x40;
    arg0->x_pos.val = g_Player.x_pos.val;
    arg0->y_pos.val = g_Player.y_pos.val;
    arg0->unk15 = PLAYER_FACING_RIGHT;
    arg0->animation_table = (u32**)D_800F8FC4;
    resource = func_8002938C(0x82);
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->unk40 = OBJECT_STAGE_TEXTURE(resource);
    arg0->unk42 = VISUAL_STAGE_PALETTE(resource);
    if (g_Player.unk2 != 0)
        arg0->unk42 += 2;
    arg0->hp = g_Player.hp;
    arg0->unk16 = VISUAL_SATURN_LAYER(4);
    arg0->unk54 = D_800F906C;
    arg0->unk60 = 0;
    arg0->unk61 = 0;
    arg0->unk67 = 0;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk50 = NULL;
    arg0->unk68 = (struct Unk_unk68*)D_800F9068;
    arg0->unk58 = NULL;
    func_8002C808((struct PlayerObj*)arg0);
    arg0->unk7D = 0;
    arg0->unk7E = 0;
    arg0->unk80.bytes.unk83 = 0;
    arg0->unk80.bytes.unk82 = 0;
    arg0->unk7C = 1;
    arg0->unk7D = 0;
    arg0->unk80.bytes.unk81 = 0;
    arg0->unk80.bytes.unk80 = 0;
    g_Player.ride_state = 1;
    RIDE_U8(arg0, 0x9B) = 1;
    arg0->unk8E.value = 0;
    set_animation(arg0, 0);
    func_8003B458(arg0, 0x41);
    RIDE_U8(arg0, 0x89) = 0;
    RIDE_U8(arg0, 0x98) = 0;
    RIDE_U8(arg0, 0x9A) = 0;
    arg0->saved_x_vel = 0;
    background_objects[arg0->bg_offset].unk30 = 0x200;
    func_8003D164((struct VisualObj*)arg0, 0);
    effect = find_free_effect_obj();
    if (effect != NULL) {
        effect->active = 1;
        effect->id = 0x1B;
        arg0->unkA0.chaser_effect = effect;
    }
    background_objects[0].unk44 = 1;
    background_objects[1].unk44 = 1;
    background_objects[2].unk44 = 1;
}
#endif

void func_8003B694(struct RideArmorObj* self)
{
    s16 x;
    s16 y;

    if (self->unk15 == 0) {
        x = self->x_pos.u.hi + self->unk68->unk0;
    } else {
        x = self->x_pos.u.hi - self->unk68->unk0;
    }
    y = self->unk68->unk3 + (self->y_pos.u.hi + self->unk68->unk1) - 15;
    if (func_8002D724(PLAYER_OBJECT(self), x, y) == 0x24) {
        if ((u16)self->saved_x_vel == 0) {
            self->x_pos.i.hi -= 8;
            self->y_pos.i.hi += 0x10;
            spawn_common_effect(MAIN_OBJECT(self), 4);
            self->saved_x_vel = 2;
            self->y_pos.i.hi -= 0x10;
            self->x_pos.i.hi += 8;
        } else {
            self->saved_x_vel--;
        }
    } else {
        self->saved_x_vel = 0;
    }
}

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8003B7B4(struct RideArmorObj* arg0)
{
    s8 health = arg0->hp;

    if (health == 0 || g_Player.hp == 0) {
        g_Player.hp = -0x80;
        arg0->hp = -0x80;
        spawn_debris(0xB, D_800F905C, arg0);
        arg0->state = 3;
        return;
    }
    if (health < 0 && HP_VALUE(health) != 0) {
        RIDE_U8(arg0, 0x9A) = 1;
        arg0->unk61 = 0x79;
        arg0->unk85 = 1;
        g_Player.hp = HP_VALUE(arg0->hp);
    }
    if (background_objects[0].unk51 != 0) {
        RIDE_U8(arg0, 0x9B) = 0;
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    if (background_objects[0].unk4 == 1 && RIDE_S8(arg0, 0x9B) != 0) {
        arg0->x_pos.i.hi += background_objects[0].x_pos.i.hi - background_objects[0].unk14.i.hi;
        arg0->y_pos.i.hi += background_objects[0].y_pos.i.hi - background_objects[0].unk18.i.hi;
    }
    D_800F90E8[arg0->unk5](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
    func_8003B694(arg0);
    if (arg0->unk5 != 0) {
        func_8003CF6C(arg0);
        arg0->unk80.bytes.unk83 = arg0->unk80.bytes.unk82;
        arg0->unk80.bytes.unk82 = func_8003CF24(arg0);
        func_8003CA44(arg0);
        if (RIDE_U8(arg0, 0x89) != 0)
            RIDE_U8(arg0, 0x89) -= 1;
        func_8003D01C(arg0);
    }
    func_8003D3B4((struct PlayerObj*)arg0);
    func_8003B98C((struct PlayerObj*)arg0);
    is_on_screen(BASE_OBJECT(arg0));
}
#else
INCLUDE_ASM("main/nonmatchings/bike", func_8003B7B4);
#endif

void func_8003B98C(struct PlayerObj* arg0)
{
    s8 timer;

    if (arg0->charge_state[0] == 0) {
        return;
    }
    if ((u8)arg0->shot_cycle == 0) {
        return;
    }

    timer = arg0->invincibility_timer;
    if (timer == 0) {
        arg0->shot_cycle = 0;
        arg0->dash_timer = 0;
        arg0->unk42 &= 0x7FFF;
        func_8003D254(VISUAL_OBJECT(arg0));
        return;
    }

    timer -= 1;
    arg0->invincibility_timer = timer;
    if (BLINK_CLOCK(timer) & 2) {
        arg0->unk42 |= 0x8000;
    } else {
        arg0->unk42 &= 0x7FFF;
    }
}

void func_8003BA24(struct RideArmorObj* arg0)
{
    if (arg0->on_screen != 0) {
        if (arg0->unk5 == 0) {
            arg0->unk5 = 1;
            arg0->x_vel.val = FIXED(10);
            arg0->unk28 = 0;
            arg0->y_vel.val = 0;
            arg0->unk2C = FIXED(0.265625);
            g_Player.ride_state = 0;
            player_start_script_action(0x17, PLAYER_FACING_RIGHT);
        } else {
            if (arg0->unk70 & 8) {
                arg0->y_vel.val = 0;
                arg0->unk2C = 0;
            }
            move_with_gravity(ANIMATED_OBJECT(arg0));
        }
    } else {
        arg0->state = 3;
        arg0->unk5 = 0;
        player_end_script_action();
    }
    CollisionRelated(PLAYER_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
}

void func_8003BAE8(struct RideArmorObj* arg0)
{
    STOP_SOUND(5, 0, 2);
    ZeroObjectState(OBJECT_HEADER(arg0));
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/bike", func_8003BB20);
#else
void func_8003BB20(struct RideArmorObj* arg0)
{
    s16 dx = arg0->x_pos.i.hi - background_objects[arg0->bg_offset].x_pos.i.hi;
    struct EffectObj* effect;
    s32 speed;

    switch (arg0->unk6) {
    case 0:
        arg0->unk6 = 1;
        arg0->x_vel.val = 0;
        arg0->y_vel.val = 0;
        arg0->unk28 = 0x8000;
        arg0->unk2C = 0;
        arg0->unk7C = 1;
        arg0->unk15 = PLAYER_FACING_RIGHT;
        func_8001540C(5, SATURN_SOUND(0, 50), NULL);
        set_animation(arg0, 6);
        func_8003B458(arg0, 0x47);
        {
            struct WeaponObj* weapon = find_free_weapon_obj();
            u8 unk16;
            u8 resource;

            if (weapon != NULL) {
                weapon->active = 0x41;
                weapon->id = 0x39;
                weapon->x_pos.i.hi = arg0->x_pos.i.hi;
                weapon->y_pos.i.hi = arg0->y_pos.i.hi;
                weapon->animation_table = (u32**)arg0->animation_table;
                weapon->unk40 = arg0->unk40;
                weapon->unk3C = arg0->unk3C;
                resource = func_8002938C(0x82);
                weapon->unk42 = VISUAL_STAGE_PALETTE(resource);
                unk16 = arg0->unk16;
                weapon->unk16 = unk16;
                weapon->owner = (struct PlayerObj*)arg0;
                weapon->unk15 = arg0->unk15;
            }
        }
        move_with_gravity(ANIMATED_OBJECT(arg0));
        return;
    case 1:
        speed = arg0->x_vel.val >= 0 ? arg0->x_vel.val : -arg0->x_vel.val;
        if (speed >= 0x80000) {
            arg0->x_vel.val = 0x80000;
            arg0->unk28 = 0;
        }
        if (dx >= 0xC0) {
            arg0->unk6 = 2;
            arg0->x_vel.val = 0x60000;
            arg0->unk28 = -0x4000;
        }
        break;
    case 2:
        if (dx <= 0x90) {
            arg0->unk6 = 3;
            arg0->x_vel.val = 0;
            arg0->unk28 = 0;
            set_animation(arg0, 7);
            func_8003B458(arg0, 0x4B);
        }
        break;
    case 3:
        if (arg0->animation_step.fields.relative_step == 0)
            arg0->unk6 = 4;
        break;
    case 4:
        effect = arg0->unkA0.chaser_effect;
        if (effect->active == 0 || effect->unk5 == 3) {
            arg0->unk5 = 1;
            arg0->unk6 = 0;
        }
        break;
    default:
        move_with_gravity(ANIMATED_OBJECT(arg0));
        return;
    }
    animate_object(ANIMATED_OBJECT(arg0));
    move_with_gravity(ANIMATED_OBJECT(arg0));
}
#endif

void func_8003BDA0(struct RideArmorObj* arg0)
{
    if (!(arg0->unk70 & 8)) {
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        return;
    }
    func_8003C6EC(arg0, arg0->unk80.bytes.unk82);
    func_8003CCBC(arg0);
    if (arg0->unk7D == 0) {
        func_8003CB08(arg0);
    }
    func_8003C8F4(arg0);
    animate_object(ANIMATED_OBJECT(arg0));
    func_8003CD38(arg0);
}

void func_8003BE28(struct RideArmorObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->unk2C = FIXED(0.3125);
    }
    self->unk67 = 1;
    func_8003C6EC(self, 4);
#ifdef MMX4_SATURN
    if ((self->unk70 & 5) != 5) {
#else
    if ((*(u32*)&self->unk70 & 5) != 5) {
#endif
        move_with_gravity(ANIMATED_OBJECT(self));
        if (self->y_vel.val < 0) {
            self->unk5 = 4;
            self->unk6 = 0;
        } else if (!((u16)self->unk8A & 0x80)) {
            self->unk5 = 4;
            self->unk6 = 0;
            self->y_vel.val = 0;
        }
    } else {
        self->unk5 = 4;
        self->unk6 = 0;
        self->y_vel.val = 0;
        if (self->unk70 & 1) {
            self->x_vel.val = 0;
            self->unk28 = 0;
        }
    }
    func_8003CCBC(self);
    if (self->unk7D != 0) {
        self->unk8E.value = 1;
    }
    func_8003CBCC(self);
}

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8003BF1C(struct RideArmorObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        arg0->unk2C = 0x5000;
    }
    arg0->unk67 = 1;
    func_8003C6EC(arg0, 4);
    if (arg0->unk70 & 8) {
        arg0->unk67 = 0;
        arg0->unk2C = 0;
        arg0->y_vel.val = 0;
        if (arg0->unk7D != 0) {
            arg0->unk5 = 5;
            arg0->unk6 = 1;
            RIDE_U8(arg0, 0x99) = 0;
        } else {
            arg0->unk5 = 1;
            arg0->unk80.bytes.unk80 &= 0xFD;
            ride_chaser_land_animation(arg0);
        }
    }
    move_with_gravity(ANIMATED_OBJECT(arg0));
    if (0x68000 - arg0->y_vel.val < 0)
        arg0->y_vel.val = 0x68000;
    func_8003CCBC(arg0);
    if (arg0->unk7D != 0)
        arg0->unk8E.value = 1;
    func_8003CBCC(arg0);
}
#else
INCLUDE_ASM("main/nonmatchings/bike", func_8003BF1C);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/bike", func_8003C08C);
#else
void func_8003C08C(struct RideArmorObj* arg0)
{
    u8 value;
    u8 resource;

    switch (arg0->unk6) {
    case 0:
        if (arg0->unk8E.value != 0) {
            arg0->unk6 = 6;
            arg0->y_vel.val = 0;
            arg0->unk2C = 0;
        } else {
            arg0->unk6 = 1;
        }
        arg0->spawned_parts = 1;
        arg0->x_vel.val = 0x40000;
        arg0->unk28 = -0x1000;
        arg0->unk90.value = 0x1000;
        arg0->unk94.value = 0;
        arg0->unk80.bytes.unk80 |= 1;
        background_objects[arg0->bg_offset].unk47 = 8;
        set_animation(arg0, D_800F9100[arg0->unk80.bytes.unk82]);
        ((void (*)(void*, s32))func_8003B458)(arg0, D_800F910C[arg0->unk80.bytes.unk82]);
        move_with_gravity(ANIMATED_OBJECT(arg0));
        {
            struct WeaponObj* weapon = find_free_weapon_obj();
            u8 unk16;

            if (weapon != NULL) {
                weapon->active = 0x41;
                weapon->id = 0x39;
                weapon->x_pos.i.hi = arg0->x_pos.i.hi;
                weapon->y_pos.i.hi = arg0->y_pos.i.hi;
                weapon->animation_table = (u32**)arg0->animation_table;
                weapon->unk40 = arg0->unk40;
                weapon->unk3C = arg0->unk3C;
                resource = func_8002938C(0x82);
                weapon->unk42 = VISUAL_STAGE_PALETTE(resource);
                unk16 = arg0->unk16;
                weapon->owner = (struct PlayerObj*)arg0;
                weapon->unk16 = unk16;
                weapon->unk15 = arg0->unk15;
            }
        }
        goto end;
    case 1:
        if (arg0->x_vel.val <= 0) {
            arg0->unk6 = 4;
            set_animation(arg0, D_800F9104[arg0->unk80.bytes.unk82]);
            ((void (*)(void*, s32))func_8003B458)(arg0, D_800F9110[arg0->unk80.bytes.unk82]);
            arg0->spawned_parts = 0;
            func_8001540C(5, SATURN_SOUND(0, 50), NULL);
        } else if (arg0->unk70 & 8) {
            func_8003C9A4(arg0);
            if (arg0->unk8C.value & 0x80) {
                arg0->unk6 = 2;
                arg0->y_vel.val = 0x68000;
                arg0->unk2C = 0x5000;
                arg0->unk28 = 0;
                arg0->unk80.bytes.unk80 |= 2;
            }
        } else {
            arg0->unk6 = 3;
            arg0->unk2C = 0x5000;
        }
        break;
    case 2:
        func_8003C584(arg0);
        goto end;
    case 3:
        if (arg0->unk70 & 8) {
            arg0->unk6 = 4;
            arg0->unk67 = 0;
            arg0->unk28 = 0;
            arg0->unk2C = 0;
            arg0->y_vel.val = 0;
            arg0->spawned_parts = 0;
            switch (arg0->unk80.bytes.unk82) {
            case 0:
                set_animation(arg0, 5);
                func_8003B458(arg0, 0x46);
                break;
            case 1:
                set_animation(arg0, 4);
                func_8003B458(arg0, 0x44);
                break;
            case 2:
                set_animation(arg0, 3);
                func_8003B458(arg0, 0x42);
                break;
            }
        }
        func_8003C624(arg0);
        goto end;
    case 4:
        if (arg0->animation_step.fields.relative_step == 0)
            arg0->unk6 = 5;
        break;
    case 5:
        arg0->unk5 = 1;
        arg0->spawned_parts = 0;
        arg0->unk6 = 0;
        arg0->unk7D = 0;
        arg0->unk80.bytes.unk80 &= 0xFC;
        background_objects[arg0->bg_offset].unk47 = 6;
        set_animation(arg0, D_800F9108[arg0->unk80.bytes.unk82]);
        ((void (*)(void*, s32))func_8003B458)(arg0, D_800F9114[arg0->unk80.bytes.unk82]);
        move_with_gravity(ANIMATED_OBJECT(arg0));
        goto end;
    case 6:
        if (arg0->unk70 & 8) {
            RIDE_U8(arg0, 0x99) = 1;
        } else {
            value = arg0->unk80.bytes.unk81;
            if (value >= 0x38 || (value < 0x20 && value != 0))
                RIDE_U8(arg0, 0x99) = 1;
        }
        if (arg0->x_vel.val <= 0) {
            arg0->unk6 = 3;
            arg0->unk2C = 0x5000;
            arg0->unk8E.value = 0;
            RIDE_U8(arg0, 0x99) = 0;
            func_8001540C(5, SATURN_SOUND(0, 50), NULL);
        } else if (RIDE_U8(arg0, 0x99) == 0) {
            if (arg0->unk8A & 4)
                arg0->y_pos.val -= 0x8000;
            else if (arg0->unk8A & 8)
                arg0->y_pos.val += 0x8000;
        }
        break;
    default:
        goto end;
    }
    func_8003C624(arg0);
    animate_object(ANIMATED_OBJECT(arg0));
end:
    if (arg0->spawned_parts != 0)
        func_8003C6EC(arg0, 3);
    else
        func_8003C6EC(arg0, 2);
}
#endif

void func_8003C584(struct RideArmorObj* arg0)
{
    arg0->unk67 = 1;
    func_8003C6EC(arg0, 3);
    if (!(arg0->unk70 & 4)) {
        func_8003C624(arg0);
        if (arg0->y_vel.val < 0) {
            arg0->unk6 = 3;
            func_8001540C(5, SATURN_SOUND(0, 50), NULL);
        }
    } else {
        arg0->unk6 = 3;
        arg0->y_vel.val = 0;
        if (arg0->unk70 & 1) {
            arg0->x_vel.val = 0;
            arg0->unk28 = 0;
        }
    }
    animate_object(ANIMATED_OBJECT(arg0));
}

void func_8003C624(struct RideArmorObj* arg0)
{
    if ((s8)arg0->unk6 >= 1 && (s8)arg0->unk6 < 5) {
        arg0->unk94.value += arg0->unk90.value;
        background_objects[arg0->bg_offset].unk47 -= arg0->unk94.value >> 16;
        if (background_objects[arg0->bg_offset].unk47 < 6) {
            background_objects[arg0->bg_offset].unk47 = 6;
        }
    }
    move_with_gravity(ANIMATED_OBJECT(arg0));
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/bike", func_8003C6EC);
#else
void func_8003C6EC(struct RideArmorObj* arg0, u8 kind)
{
    struct WeaponObj* weapon;
    struct VisualObj* visual;
    u8 resource;

    if (!(arg0->unk8C.value & 0x30) || RIDE_U8(arg0, 0x89) != 0 || RIDE_U8(arg0, 0x98) >= 3)
        return;
    weapon = find_free_weapon_obj();
    if (weapon != NULL) {
        weapon->active = 0x41;
        weapon->id = 0x38;
        weapon->unk2 = kind;
        weapon->x_pos.i.hi = arg0->x_pos.i.hi;
        weapon->y_pos.i.hi = arg0->y_pos.i.hi;
        weapon->animation_table = (u32**)arg0->animation_table;
        weapon->unk40 = arg0->unk40;
        weapon->unk3C = arg0->unk3C;
        resource = func_8002938C(0x82);
        weapon->unk42 = VISUAL_STAGE_PALETTE(resource);
        weapon->unk16 = arg0->unk16;
        weapon->owner = (struct PlayerObj*)arg0;
        weapon->unk15 = arg0->unk15;
    }
    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 0xC;
        visual->unk2 = kind;
        visual->x_pos.i.hi = arg0->x_pos.i.hi;
        visual->y_pos.i.hi = arg0->y_pos.i.hi;
        visual->animation_table = (u32**)arg0->animation_table;
        visual->unk40 = arg0->unk40;
        visual->unk3C = arg0->unk3C;
        resource = func_8002938C(0x82);
        visual->unk42 = VISUAL_STAGE_PALETTE(resource);
        visual->unk16 = arg0->unk16;
        visual->unk50 = (struct PlayerObj*)arg0;
        visual->unk15 = arg0->unk15;
    }
    RIDE_U8(arg0, 0x89) = 4;
    RIDE_U8(arg0, 0x98) += 1;
    func_8001540C(5, SATURN_SOUND(2, 52), arg0);
}
#endif

void func_8003C8F4(struct RideArmorObj* arg0)
{
    if (arg0->unk8C.value & 0x80) {
        if (arg0->unk7D == 0) {
            arg0->unk5 = 2;
            arg0->unk6 = 0;
            arg0->y_vel.val = FIXED(6.5);
            arg0->unk80.bytes.unk80 |= 2;
            set_animation(arg0, 2);
            func_8003B458(arg0, 0x45);
        } else {
            arg0->unk6 = 0;
            arg0->unk80.bytes.unk80 |= 2;
            arg0->y_vel.val = FIXED(6.5);
            arg0->unk8E.value = 1;
            arg0->unk67 = 1;
        }
    }
}

void func_8003C9A4(struct RideArmorObj* arg0)
{
    if ((arg0->unk80.bytes.unk82 != arg0->unk80.bytes.unk83) && (arg0->unk80.bytes.unk80 & 1) && (arg0->unk80.bytes.unk83 == 0) && (arg0->unk80.bytes.unk82 == 2)) {
        arg0->y_vel.val = (((arg0->x_vel.val < 0 ? -arg0->x_vel.val : arg0->x_vel.val) * 2) / 237) << 8;
        arg0->unk80.bytes.unk80 |= 2;
        arg0->unk2C = FIXED(0.3125);
        arg0->unk6 = 2;
    }
}

void func_8003CA44(struct RideArmorObj* arg0)
{
    if (arg0->unk80.bytes.unk82 == arg0->unk80.bytes.unk83 || (arg0->unk80.bytes.unk80 & 2))
        return;
    switch (arg0->unk80.bytes.unk82) {
    case 0:
        set_animation(arg0, 2);
        func_8003B458(arg0, 0x45);
        break;
    case 1:
        set_animation(arg0, 1);
        func_8003B458(arg0, 0x43);
        break;
    case 2:
        set_animation(arg0, 0);
        func_8003B458(arg0, 0x41);
        break;
    }
}

void func_8003CB08(struct RideArmorObj* arg0)
{
    u16 flags;

    flags = arg0->unk8A;
    arg0->unk80.bytes.unk80 &= 0xFE;
    if (flags & 3) {
        if (flags & 1) {
            if (arg0->x_vel.val < D_800F9098[arg0->unk7D]) {
                arg0->x_vel.val = D_800F9098[arg0->unk7D];
                arg0->unk28 = 0;
            }
            arg0->unk7C = 1;
            return;
        }
        if (flags & 2) {
            if (arg0->x_vel.val >= D_800F9090[arg0->unk7D]) {
                arg0->x_vel.val = D_800F9090[arg0->unk7D];
                arg0->unk28 = 0;
            }
            arg0->unk7C = 0;
        }
    } else {
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->unk7C = 1;
        arg0->unk80.bytes.unk80 &= 0xFE;
    }
}

void func_8003CBCC(struct RideArmorObj* arg0)
{
    u16 flags;
    s32 velocity;
    s32 limit;

    flags = arg0->unk8A;
    if ((flags & 3) || arg0->unk7D != 0) {
        if (flags & 1) {
            velocity = arg0->x_vel.val;
            if (velocity == 0) {
                arg0->unk28 = FIXED(0.125);
            } else {
                limit = D_800F9098[arg0->unk7D];
                if (velocity >= limit) {
                    arg0->x_vel.val = limit;
                    arg0->unk28 = 0;
                }
            }
            arg0->unk7C = 1;
        } else if (flags & 2) {
            velocity = arg0->x_vel.val;
            if (velocity == 0) {
                arg0->unk28 = FIXED(-0.125);
            } else {
                limit = D_800F9090[arg0->unk7D];
                if (velocity < limit) {
                    arg0->x_vel.val = limit;
                    arg0->unk28 = 0;
                }
            }
            arg0->unk7C = 0;
        }
    } else {
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->unk7C = 1;
    }
}

void func_8003CCBC(struct RideArmorObj* arg0)
{
    if (arg0->unk7D == 0 && (arg0->unk7E != 0 || (arg0->unk8C.value & 0x100) != 0)) {
        arg0->unk7D = 1;
        arg0->unk5 = 5;
        arg0->unk6 = 0;
        arg0->unk80.bytes.unk80 |= 3;
        arg0->unk98.bytes.high = 0;
        func_8001540C(5, SATURN_SOUND(1, 51), NULL);
    }
}

void func_8003CD38(struct RideArmorObj* arg0)
{
    s32 limit;
    u8 state;

    state = func_8003CF24(arg0);
    switch (state) {
    case 0:
        if (arg0->unk7C == 0) {
            limit = D_800F9070[arg0->unk7D];
            if (arg0->x_vel.val <= limit) {
                arg0->x_vel.val = limit;
                func_8003D39C(MAIN_OBJECT(arg0));
            } else {
                move_with_gravity(ANIMATED_OBJECT(arg0));
            }
        } else {
            limit = D_800F9078[arg0->unk7D];
            if (arg0->x_vel.val >= limit) {
                move_with_gravity(ANIMATED_OBJECT(arg0));
            } else {
                func_8003D338(ANIMATED_OBJECT(arg0));
                move_object(MOVING_OBJECT(arg0));
            }
        }
        break;
    case 1:
        if (arg0->unk7C != 0) {
            limit = D_800F9080[arg0->unk7D];
            if (limit > arg0->x_vel.val) {
                func_8003D338(ANIMATED_OBJECT(arg0));
                move_object(MOVING_OBJECT(arg0));
            } else {
                arg0->x_vel.val = limit;
                func_8003D39C(MAIN_OBJECT(arg0));
            }
        } else {
            limit = D_800F9088[arg0->unk7D];
            if (arg0->x_vel.val > limit) {
                func_8003D338(ANIMATED_OBJECT(arg0));
                move_object(MOVING_OBJECT(arg0));
            } else {
                move_with_gravity(ANIMATED_OBJECT(arg0));
            }
        }
        break;
    default:
        if (arg0->unk7C == 0) {
            move_with_gravity(ANIMATED_OBJECT(arg0));
            limit = D_800F9090[arg0->unk7D];
            if (limit - arg0->x_vel.val >= 0) {
                arg0->x_vel.val = limit;
            }
        } else {
            func_8003D338(ANIMATED_OBJECT(arg0));
            move_object(MOVING_OBJECT(arg0));
            limit = D_800F9098[arg0->unk7D];
            if (limit - arg0->x_vel.val < 0) {
                arg0->x_vel.val = limit;
            }
        }
        break;
    }
}

#if defined(MMX4_PC) || defined(MMX4_SATURN)
u8 func_8003CF24(struct RideArmorObj* arg0)
{
    u8 tile = arg0->unk80.bytes.unk81;

    if (tile != 0 && tile < 9)
        return tile < 5 ? 0 : 1;
    if (tile != 0x10)
        return 2;
    return arg0->unk80.bytes.unk83;
}
#else
INCLUDE_ASM("main/nonmatchings/bike", func_8003CF24);
#endif

void func_8003CF6C(struct RideArmorObj* ride_armor)
{
    s16 tile_x;

    if (ride_armor->unk15 == 0) {
        tile_x = ride_armor->x_pos.i.hi + (s8)ride_armor->unk68->unk0;
    } else {
        tile_x = ride_armor->x_pos.i.hi - (s8)ride_armor->unk68->unk0;
    }

    ride_armor->unk80.bytes.unk81 = func_8002D724(PLAYER_OBJECT(ride_armor), tile_x,
        ride_armor->unk68->unk3 + (ride_armor->y_pos.i.hi + (s8)ride_armor->unk68->unk1) + 1);
}

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8003D01C(struct RideArmorObj* arg0)
{
    const struct Unk_unk68* bounds = arg0->unk68;
    s32 offset = (u16)arg0->x_pos.i.hi - (u16)background_objects[arg0->bg_offset].x_pos.i.hi;
    s16 edge;

    if (arg0->unk15 != 0)
        offset -= bounds->unk0;
    else
        offset += bounds->unk0;
    edge = offset - bounds->unk2;
    if (edge <= 0 && !(arg0->unk70 & 1)) {
        arg0->x_pos.i.hi -= edge;
    } else if (edge < -8) {
        g_Player.hp = -0x80;
        arg0->hp = -0x80;
    }
    edge = offset + bounds->unk2;
    if (edge >= 0x100)
        arg0->x_pos.i.hi -= (s16)(edge - 0x100);
}
#else
INCLUDE_ASM("main/nonmatchings/bike", func_8003D01C);
#endif

void func_8003D164(struct VisualObj* arg0, s32 arg1)
{
    u8 v;
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0xD;
        obj->unk2 = arg1;
        obj->x_pos.i.hi = arg0->x_pos.i.hi;
        obj->y_pos.i.hi = arg0->y_pos.i.hi;
        obj->animation_table = arg0->animation_table;
        obj->unk40 = arg0->unk40;
        obj->unk3C = arg0->unk3C;
        v = (u8)func_8002938C(0x82);
        obj->unk42 = VISUAL_STAGE_PALETTE(v);
        obj->unk16 = arg0->unk16;
        obj->unk50 = arg0;
        obj->unk15 = arg0->unk15;
    }
}

void func_8003D254(struct VisualObj* arg0)
{
    u8 v;
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0xF;
        obj->unk2 = 0;
        obj->x_pos.i.hi = arg0->x_pos.i.hi;
        obj->y_pos.i.hi = arg0->y_pos.i.hi;
        obj->animation_table = arg0->animation_table;
        obj->unk40 = arg0->unk40;
        obj->unk3C = arg0->unk3C;
        v = (u8)func_8002938C(0x82);
        obj->unk42 = VISUAL_STAGE_PALETTE(v);
        obj->unk16 = arg0->unk16;
        obj->unk50 = arg0;
        obj->unk15 = arg0->unk15;
    }
}

void func_8003D338(struct AnimatedObj* arg0)
{
    arg0->y_vel.val -= arg0->unk2C;
    arg0->x_vel.val -= arg0->unk28;
}

void func_8003D35C(struct MainObj* arg0)
{
    arg0->y_pos.val -= arg0->y_speed;
    arg0->y_speed -= arg0->gravity;
    if (arg0->y_speed < -FIXED(6.5)) {
        arg0->y_speed = -FIXED(6.5);
    }
}

void func_8003D39C(struct MainObj* arg0)
{
    arg0->x_pos.val += arg0->x_speed;
}

void func_8003D3B4(struct PlayerObj* arg0)
{
    if (g_Player.ride_state != 0 && arg0->charge_state[0] != PLAYER_CHARGE_NONE) {
        g_Player.x_pos = arg0->x_pos;
        g_Player.y_pos = arg0->y_pos;
    }
}

union AnimationStep D_800F8DC8[] = { { 1, 0, 0, 0x00 } };

union AnimationStep D_800F8DCC[] = { { 1, 0, 0, 0x01 } };

union AnimationStep D_800F8DD0[] = { { 1, 0, 0, 0x02 } };

union AnimationStep D_800F8DD4[] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x04 },
    { 6, 0, 1, 0x05 },
    { 1, 0, 1, 0x04 },
    { 1, 0, 1, 0x00 },
    { 3, 0, 1, 0x06 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep D_800F8DF0[] = {
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x07 },
    { 6, 0, 1, 0x08 },
    { 1, 0, 1, 0x07 },
    { 1, 0, 1, 0x01 },
    { 3, 0, 1, 0x09 },
    { 1, 0, 0, 0x01 },
};

union AnimationStep D_800F8E0C[] = {
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x0A },
    { 6, 0, 1, 0x0B },
    { 1, 0, 1, 0x0A },
    { 1, 0, 1, 0x02 },
    { 3, 0, 1, 0x0C },
    { 1, 0, 0, 0x02 },
};

union AnimationStep D_800F8E28[] = { { 2, 0, 1, 0x00 }, { 2, 0, 1, 0x02 }, { 8, 0, 1, 0x03 }, { 1, 0, 0, 0x03 } };

union AnimationStep D_800F8E38[] = { { 8, 0, 1, 0x03 }, { 2, 0, 1, 0x02 }, { 2, 0, 1, 0x00 }, { 1, 0, 0, 0x00 } };

union AnimationStep D_800F8E48[] = { { 2, 0, 1, 0x01 }, { 2, 0, 1, 0x00 }, { 2, 0, 1, 0x02 }, { 8, 0, 1, 0x03 }, { 1, 0, 0, 0x03 } };

union AnimationStep D_800F8E5C[] = { { 8, 0, 1, 0x03 }, { 2, 0, 1, 0x02 }, { 2, 0, 1, 0x00 }, { 2, 0, 1, 0x01 }, { 1, 0, 0, 0x01 } };

union AnimationStep D_800F8E70[] = { { 2, 0, 1, 0x02 }, { 8, 0, 1, 0x03 }, { 1, 0, 0, 0x03 } };

union AnimationStep D_800F8E7C[] = { { 2, 0, 1, 0x03 }, { 8, 0, 1, 0x02 }, { 1, 0, 0, 0x02 } };

union AnimationStep D_800F8E88[] = { { 1, 0, 1, 0x0D }, { 1, 0, 1, 0x0E }, { 1, 0, -2, 0x0F } };

union AnimationStep D_800F8E94[] = { { 2, 0, 1, 0x10 }, { 2, 0, 1, 0x11 }, { 3, 0, -2, 0x12 } };

union AnimationStep D_800F8EA0[] = { { 2, 0, 1, 0x13 }, { 2, 0, 1, 0x14 }, { 3, 0, -2, 0x15 } };

union AnimationStep D_800F8EAC[] = { { 2, 0, 1, 0x16 }, { 2, 0, 1, 0x17 }, { 3, 0, -2, 0x18 } };

union AnimationStep D_800F8EB8[] = { { 2, 0, 1, 0x19 }, { 2, 0, 1, 0x1A }, { 3, 0, -2, 0x1B } };

union AnimationStep D_800F8EC4[] = { { 2, 0, 1, 0x1C }, { 1, 0, 1, 0x1D }, { 2, 0, 1, 0x1E }, { 1, 0, -3, 0x1F } };

union AnimationStep D_800F8ED4[] = { { 2, 0, 1, 0x20 }, { 1, 0, 1, 0x21 }, { 2, 0, 1, 0x22 }, { 1, 0, -3, 0x23 } };

union AnimationStep D_800F8EE4[] = { { 2, 0, 1, 0x24 }, { 1, 0, 1, 0x25 }, { 2, 0, 1, 0x26 }, { 1, 0, -3, 0x27 } };

union AnimationStep D_800F8EF4[] = { { 2, 0, 1, 0x28 }, { 1, 0, 1, 0x29 }, { 2, 0, 1, 0x2A }, { 1, 0, -3, 0x2B } };

union AnimationStep D_800F8F04[] = {
    { 2, 0, 1, 0x2C },
    { 1, 1, 1, 0x2D },
    { 1, 2, 1, 0x2E },
    { 1, 3, 1, 0x2F },
    { 2, 4, 1, 0x30 },
    { 1, 5, 1, 0x31 },
    { 1, 5, -6, 0x31 },
};

union AnimationStep D_800F8F20[] = {
    { 2, 0, 1, 0x32 },
    { 1, 1, 1, 0x33 },
    { 1, 2, 1, 0x34 },
    { 1, 3, 1, 0x35 },
    { 2, 4, 1, 0x36 },
    { 1, 5, 1, 0x37 },
    { 1, 5, -6, 0x37 },
};

union AnimationStep D_800F8F3C[] = {
    { 2, 0, 1, 0x38 },
    { 1, 1, 1, 0x39 },
    { 1, 2, 1, 0x3A },
    { 1, 0, 1, 0x3B },
    { 2, 4, 1, 0x3C },
    { 1, 5, 1, 0x3D },
    { 1, 0, -6, 0x3D },
};

union AnimationStep D_800F8F58[] = {
    { 2, 0, 1, 0x3E },
    { 1, 1, 1, 0x3F },
    { 1, 2, 1, 0x40 },
    { 1, 3, 1, 0x41 },
    { 2, 4, 1, 0x42 },
    { 1, 5, 1, 0x43 },
    { 1, 5, -6, 0x43 },
};

union AnimationStep D_800F8F74[] = {
    { 3, 0, 1, 0x44 },
    { 2, 0, 1, 0x45 },
    { 2, 0, 1, 0x46 },
    { 3, 0, 1, 0x47 },
    { 3, 0, 1, 0x48 },
    { 2, 0, 1, 0x49 },
    { 2, 0, 1, 0x4A },
    { 3, 0, -6, 0x4B },
};

union AnimationStep D_800F8F94[] = { { 1, 0, 0, 0x4C } };

union AnimationStep D_800F8F98[] = { { 1, 0, 0, 0x4D } };

union AnimationStep D_800F8F9C[] = { { 1, 0, 0, 0x4E } };

union AnimationStep D_800F8FA0[] = { { 1, 0, 0, 0x4F } };

union AnimationStep D_800F8FA4[] = { { 1, 0, 0, 0x50 } };

union AnimationStep D_800F8FA8[] = { { 1, 0, 0, 0x51 } };

union AnimationStep D_800F8FAC[] = { { 1, 0, 0, 0x52 } };

union AnimationStep D_800F8FB0[] = { { 1, 0, 0, 0x53 } };

union AnimationStep D_800F8FB4[] = { { 1, 0, 0, 0x54 } };

union AnimationStep D_800F8FB8[] = { { 1, 0, 0, 0x55 } };

union AnimationStep D_800F8FBC[] = { { 1, 0, 0, 0x56 } };

union AnimationStep D_800F8FC0[] = { { 1, 0, 0, 0x57 } };

union AnimationStep* D_800F8FC4[38] = {
    D_800F8DC8,
    D_800F8DCC,
    D_800F8DD0,
    D_800F8DD4,
    D_800F8DF0,
    D_800F8E0C,
    D_800F8E28,
    D_800F8E38,
    D_800F8E48,
    D_800F8E5C,
    D_800F8E70,
    D_800F8E7C,
    D_800F8E88,
    D_800F8E94,
    D_800F8EAC,
    D_800F8EA0,
    D_800F8EB8,
    D_800F8EC4,
    D_800F8ED4,
    D_800F8EE4,
    D_800F8EF4,
    D_800F8F04,
    D_800F8F20,
    D_800F8F3C,
    D_800F8F58,
    D_800F8F74,
    D_800F8F94,
    D_800F8F98,
    D_800F8F9C,
    D_800F8FA0,
    D_800F8FA4,
    D_800F8FA8,
    D_800F8FAC,
    D_800F8FB0,
    D_800F8FB4,
    D_800F8FB8,
    D_800F8FBC,
    D_800F8FC0,
};

u8 D_800F905C[12] = { 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25 };

u8 D_800F9068[4] = { 0xFF, 0x0F, 0x1A, 0x0B };

u8 D_800F906C[4] = { 0xEB, 0xFC, 0x25, 0x16 };

s32 D_800F9070[2] = { -0x28000, -0x48000 };

s32 D_800F9078[2] = { 0x18000, 0x38000 };

s32 D_800F9080[2] = { 0x28000, 0x48000 };

s32 D_800F9088[2] = { -0x18000, -0x38000 };

s32 D_800F9090[2] = { -0x20000, -0x40000 };

s32 D_800F9098[2] = { 0x20000, 0x40000 };

u16 D_800F90A0[14] = {
    0xA2,
    0xA6,
    0xAA,
    0xAE,
    0xA3,
    0xA4,
    0xA5,
    0xA7,
    0xA8,
    0xA9,
    0xAB,
    0xAC,
    0xAD,
    0,
};

u16 D_800F90BC[14] = {
    0xAF,
    0xB1,
    0xB3,
    0xB5,
    0xAF,
    0xAF,
    0xAF,
    0xB1,
    0xB1,
    0xB1,
    0xB3,
    0xB3,
    0xB3,
    0,
};

void (*D_800F90D8[])(struct RideArmorObj*) = {
    func_8003B470,
    func_8003B7B4,
    func_8003BA24,
    func_8003BAE8,
};

void (*D_800F90E8[6])() = {
    func_8003BB20,
    func_8003BDA0,
    func_8003BE28,
    func_8003C584,
    func_8003BF1C,
    func_8003C08C,
};

u8 D_800F9100[4] = {
    0x0A,
    0x08,
    0x06,
    0x00,
};

u8 D_800F9104[4] = {
    0x0B,
    0x09,
    0x07,
    0x00,
};

u8 D_800F9108[4] = {
    0x02,
    0x01,
    0x00,
    0x00,
};

u8 D_800F910C[4] = {
    0x49,
    0x48,
    0x47,
    0x00,
};

u8 D_800F9110[4] = {
    0x4C,
    0x4B,
    0x4A,
    0x00,
};

u8 D_800F9114[4] = {
    0x45,
    0x43,
    0x41,
    0x00,
};
