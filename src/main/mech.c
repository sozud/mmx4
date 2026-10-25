// RideArmorObj, D_800F2AD4[1]
// 8003D3F8..80040608
#include "common.h"
#include "main/mech.h"
#include "main/mech_state_data.h"
#include "main/objects.h"
#include "main/object_motion.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/player_common.h"
#include "weapon_resources.h"

s32 func_8003D7E4(struct RideArmorObj*, u8, s32);

void func_8003D3F8(struct RideArmorObj* arg0)
{
    if (g_Player.script_state == 0) {
        arg0->collision_flags = g_Player.input.buttons.held;
        arg0->unk8A = g_Player.pressed_input;
    } else {
        arg0->collision_flags = 0;
        arg0->unk8A = 0;
    }
    if (g_Player.update_delay != 0) {
        func_8002B3C0(BASE_OBJECT(arg0));
        return;
    }

    arg0->unk18 = arg0->x_pos;
    arg0->unk1C = arg0->y_pos;

    arg0->input_flags = arg0->unk70 | arg0->unk71;
    arg0->unk71 = 0;
    D_800F912C[arg0->state](arg0);
    arg0->hp &= ~0x80;
}

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#define RIDE_S8(object, offset) (*(s8*)&RIDE_U8(object, offset))
s32 func_8003DE08(struct MainObj*);
s32 func_8003DC8C(struct RideArmorObj*);
s32 func_8003DC50(struct RideArmorObj*);
void func_8003DD14(struct MainObj*);
void func_8003DD2C(struct MainObj*);
void func_8003DD54(struct RideArmorObj*);
void func_8003DDA0(struct RideArmorObj*);
void func_8003D7A0(void);
s32 func_8003E048(struct PlayerObj*);
#endif

#define RIDE_U8(object, offset) (((u8*)&(object)->unk7C)[(offset)-0x7C])
#define RIDE_U16(object, offset) (*(u16*)&RIDE_U8(object, offset))
extern union AnimationStep* D_800F9428[31];
extern union AnimationStep* D_800F965C[38];
extern struct Unk_unk68 D_800F9120;
extern struct Unk_unk68 D_800F9128;
#define RIDE_ARMOR_STATE(object, state) func_8003DC44(BASE_OBJECT(object), (state))
#define RIDE_ARMOR_FLAGS(object) ((object)->unk94.bytes.unk97)
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8003D4C8(struct RideArmorObj* arg0);
void func_8003D9E0(struct RideArmorObj* arg0);
s32 func_8003DCD8(struct RideArmorObj* arg0);
void func_8003E274(struct RideArmorObj* arg0);
void func_80040248(struct RideArmorObj* arg0);
void func_800403DC(struct RideArmorObj* arg0);
extern void (*D_800F9150[])(struct RideArmorObj*);
extern void (*D_800F9188[])(struct RideArmorObj*);
void func_8003DC44(struct BaseObj*, s8);
void func_8003DC1C(struct PlayerObj*, s8);
void func_8003D638(struct VisualObj*, u8);
void func_8003DDDC(struct PlayerObj*);
void func_800401F8(struct PlayerObj*);
void func_800400C8(struct PlayerObj*);
void func_800402C4(struct PlayerObj*);
void func_8003FF9C(struct RideArmorObj*);
void func_8003DF9C(struct PlayerObj*);
void func_8003D9E0(struct RideArmorObj*);
void func_8003DE84(struct RideArmorObj*);
void func_80040248(struct RideArmorObj*);
extern ret_u8 func_8002938C(s32);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mech", func_8003D4C8);
#else
void func_8003D4C8(struct RideArmorObj* arg0)
{
    u8 resource;

    arg0->active |= 0x40;
    arg0->on_screen = 1;
    arg0->state = 1;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->bg_offset = 0;
    arg0->unk15 = 0;
    if (arg0->unk2 == 0)
        arg0->animation_table = (u32**)D_800F9428;
    else
        arg0->animation_table = (u32**)D_800F965C;
    resource = func_8002938C(0x86);
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->unk40 = OBJECT_STAGE_TEXTURE(resource);
    arg0->unk42 = VISUAL_STAGE_PALETTE(resource);
    arg0->hp = 0x20;
    arg0->unk60 = 0;
    arg0->unk61 = 0;
    arg0->unk67 = 0;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk16 = 3;
    arg0->unk54 = NULL;
    arg0->unk50 = NULL;
    arg0->unk68 = &D_800F9124;
    arg0->unk58 = NULL;
    arg0->unk7D = 0;
    arg0->unk7E = 0;
    arg0->unk80.bytes.unk83 = 0;
    arg0->unk80.bytes.unk82 = 0;
    arg0->unk7C = 1;
    arg0->unk86 = 0;
    arg0->unk80.bytes.unk81 = 0;
    arg0->unk80.bytes.unk80 = 0;
    arg0->spawned_parts = 0;
    RIDE_U8(arg0, 0x8E) = 0;
    RIDE_U8(arg0, 0x8D) = 0;
    RIDE_U8(arg0, 0x93) = 0;
    RIDE_ARMOR_FLAGS(arg0) = 0;
    arg0->unkA6 = 0;
    RIDE_U8(arg0, 0x8C) = 0;
    arg0->unk87 = 0;
}
#endif

void func_8003D638(struct VisualObj* arg0, u8 arg1)
{
    struct VisualObj* obj;
    u8 unk16;

    obj = find_free_visual_obj();
    if (obj == NULL) {
        return;
    }
    obj->active = arg0->active;
    obj->id = 0xC;
    obj->unk2 = arg1;
    obj->x_pos.val = arg0->x_pos.val;
    obj->y_pos.val = arg0->y_pos.val;
    obj->animation_table = arg0->animation_table;
    obj->unk40 = arg0->unk40;
    obj->unk3C = arg0->unk3C;
    obj->unk42 = arg0->unk42 & 0x7FFF;
    unk16 = arg0->unk16;
    obj->unk16 = unk16;
    obj->unk15 = arg0->unk15;
    obj->unk50 = (struct PlayerObj*)arg0;
}

void func_8003D6EC(struct AnimatedObj* arg0, s32 arg1)
{
    struct AnimatedObj* animated_obj;
    struct VisualObj* visual_obj;

    animated_obj = arg0;
    visual_obj = find_free_visual_obj();
    if (visual_obj != 0) {
        visual_obj->active = 0x41;
        visual_obj->id = 0x16;
        visual_obj->unk2 = (char)arg1;
        visual_obj->x_pos.i.hi = (short)(unsigned short)animated_obj->x_pos.i.hi;
        visual_obj->y_pos.i.hi = (short)(unsigned short)animated_obj->y_pos.i.hi;
        visual_obj->animation_table = animated_obj->animation_table;
        visual_obj->unk40 = animated_obj->unk40;
        visual_obj->unk3C = animated_obj->unk3C;
        visual_obj->unk42 = animated_obj->unk42 & 0x7FFF;
        visual_obj->unk16 = animated_obj->unk16;
        visual_obj->unk50 = (struct PlayerObj*)animated_obj;
        visual_obj->unk15 = animated_obj->unk15;
    }
}

void func_8003D7A0(void)
{
    if (!(main_bss_state.frame_counter & 3) && (get_random() & 1)) {
        get_random();
    }
}

// The unused integer return type preserves the original delay-slot scheduling.
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mech", func_8003D7E4);
#else
s32 func_8003D7E4(struct RideArmorObj* arg0, u8 kind, s32 variant)
{
    struct WeaponObj* weapon = find_free_weapon_obj();
    if (weapon != NULL) {
        weapon->active = 0x41;
        weapon->id = variant + 0x3D;
        weapon->unk2 = kind;
        weapon->x_pos.i.hi = arg0->x_pos.i.hi;
        weapon->y_pos.i.hi = arg0->y_pos.i.hi;
        weapon->animation_table = arg0->animation_table;
        weapon->unk40 = arg0->unk40;
        weapon->unk3C = arg0->unk3C;
        weapon->unk42 = arg0->unk42 & 0x7FFF;
        weapon->unk16 = arg0->unk16;
        weapon->owner = (struct PlayerObj*)arg0;
        weapon->unk15 = arg0->unk15;
    }
}
#endif

// Callers discard the legacy integer return value.
s32 func_8003D8A8(struct RideArmorObj* owner, s32 shot_kind, s32 shot_variant)
{
    struct RideArmorObj* ride_armor = owner;
    s32 variant = shot_variant;
    s8 kind = shot_kind;
    struct WeaponObj* weapon;
    u8 resource;
    u8 type = variant;

    if (ride_armor->unk86 < 3) {
        weapon = find_free_weapon_obj();
        if (weapon != NULL) {
            weapon->active = 0x41;
            weapon->id = variant + 0x3B;
            weapon->unk2 = kind;
            weapon->x_pos.i.hi = ride_armor->x_pos.i.hi;
            weapon->y_pos.i.hi = ride_armor->y_pos.i.hi;
            weapon->animation_table = ride_armor->animation_table;
            weapon->unk40 = ride_armor->unk40;
            weapon->unk3C = ride_armor->unk3C;
            resource = func_8002938C(0x86);
            weapon->unk42 = VISUAL_STAGE_PALETTE(resource);
            weapon->unk16 = ride_armor->unk16;
            weapon->owner = PLAYER_OBJECT(ride_armor);
            weapon->unk15 = ride_armor->unk15;
            if (type == 0) {
                ride_armor->unk86++;
            }
        }
    }
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mech", func_8003D9E0);
#else
void func_8003D9E0(struct RideArmorObj* arg0)
{
    u16 mode;
    u8 parts;
    u32 i;

    if (RIDE_ARMOR_FLAGS(arg0) & 2)
        return;
    mode = RIDE_U16(arg0, 0x96) & 0xC000;
    if (mode == 0x8000)
        return;
    switch (RIDE_U8(arg0, 0x94)) {
    case 0:
        if (arg0->collision_flags & 0x30) {
            RIDE_U8(arg0, 0x94) = 1;
            RIDE_U8(arg0, 0x95) = 0x3C;
            arg0->unkA6 = arg0->collision_flags & 0x30;
        }
        return;
    case 1:
        if (!(arg0->collision_flags & arg0->unkA6)) {
            RIDE_U8(arg0, 0x94) = 0;
            arg0->unkA6 = 0;
            return;
        }
        if (--RIDE_U8(arg0, 0x95) != 0)
            return;
        RIDE_U8(arg0, 0x94) = 2;
        if (arg0->unk2 == 0 || (RIDE_U16(arg0, 0x96) & 0xC000) != 0x4000)
            return;
        func_8003D6EC(ANIMATED_OBJECT(arg0), 0x10);
        func_8001540C(5, SATURN_SOUND(8, 78), NULL);
        return;
    case 2:
        if (arg0->collision_flags & arg0->unkA6)
            return;
        if (arg0->unk2 == 0 || mode != 0x4000) {
            RIDE_U8(arg0, 0x94) = 0;
            arg0->unkA6 = 0;
            STOP_SOUND(5, 8, 1);
            return;
        }
        if ((u8)arg0->unk5 == 3)
            goto stop;
        if ((u8)arg0->unk5 == 6)
            goto stop;
        if ((u8)arg0->unk5 == 9)
            goto stop;
        if ((u8)arg0->unk5 == 0xA)
            goto stop;
        if ((u8)arg0->unk5 == 0xB)
            goto stop;
        if ((u8)arg0->unk5 == 0xD)
            goto stop;
        if ((u8)arg0->unk5 == 0x10)
            goto stop;
        if ((u8)arg0->unk5 == 0x11)
            goto stop;
        parts = arg0->spawned_parts;
        for (i = 0; i < 3; i++) {
            if (!(parts & 1)) {
                func_8003D8A8(arg0, (u8)i, 1);
                arg0->spawned_parts |= 1 << i;
            }
            parts >>= 1;
        }
        arg0->unk7E = 0x10;
        func_8001540C(5, SATURN_SOUND(6, 76), NULL);
        RIDE_U8(arg0, 0x94) = 0;
        arg0->unkA6 = 0;
        return;
    stop:
        RIDE_U8(arg0, 0x94) = 0;
        arg0->unkA6 = 0;
        STOP_SOUND(5, 8, 1);
        return;
    }
}
#endif

void func_8003DC1C(struct PlayerObj* arg0, s8 arg1)
{
    if (arg0->unk8D == 0) {
        g_Player.ride_animation = arg1;
        g_Player.unk6 = 0;
    }
}

void func_8003DC44(struct BaseObj* arg0, s8 arg1)
{
    arg0->unk5 = arg1;
    arg0->unk6 = 0;
}

s32 func_8003DC50(struct RideArmorObj* arg0)
{
    u16 collision_flags = arg0->collision_flags;

    if (collision_flags & 2) {
        arg0->unk15 = 0;
        return 1;
    }
    if (collision_flags & 1) {
        arg0->unk15 = PLAYER_FACING_RIGHT;
        return 1;
    }
    return 0;
}

s32 func_8003DC8C(struct RideArmorObj* arg0)
{
    if (arg0->collision_flags & 4) {
        if (arg0->unk8A & 0x80) {
            return 1;
        }
    } else if (g_Player.hp == -0x80) {
        return 1;
    }
    return 0;
}

#if defined(MMX4_PC) || defined(MMX4_SATURN)
s32 func_8003DCD8(struct RideArmorObj* arg0)
{
    if (!(arg0->unk8A & 0x30))
        return 0;
    if (arg0->unk2 == 0)
        return 1;
    return arg0->unk7E == 0;
}
#else
INCLUDE_ASM("main/nonmatchings/mech", func_8003DCD8);
#endif

void func_8003DD14(struct MainObj* arg0)
{
    arg0->x_pos.val += arg0->x_speed;
}

void func_8003DD2C(struct MainObj* arg0)
{
    if (arg0->unk15 != 0) {
        arg0->x_speed = FIXED(1.375);
    } else {
        arg0->x_speed = FIXED(-1.375);
    }
}

void func_8003DD54(struct RideArmorObj* arg0)
{
    s32 velocity;

    if (func_8003DC50(arg0) != 0) {
        velocity = arg0->unk98.packed << 8;
        if (arg0->unk15 == 0) {
            velocity = -velocity;
        }
        arg0->x_vel.val = velocity;
    }
}

void func_8003DDA0(struct RideArmorObj* arg0)
{
    u16 collision_flags = arg0->collision_flags;
    if (collision_flags & 3) {
        s32 x_velocity = arg0->unk98.packed << 8;
        if (!(collision_flags & 1)) {
            x_velocity = -x_velocity;
        }
        arg0->x_vel.val = x_velocity;
    }
}

void func_8003DDDC(struct PlayerObj* arg0)
{
    g_Player.x_pos = arg0->x_pos;
    g_Player.y_pos = arg0->y_pos;
    g_Player.unk15 = arg0->unk15;
}

s32 func_8003DE08(struct MainObj* arg0)
{
    if (arg0->unk2 == 0) {
        if (arg0->unk5 != 1) {
            if (arg0->unk5 != 2) {
                if (arg0->unk5 != 5) {
                    return 1;
                }
            }
        }
    } else {
        if (arg0->unk5 == 0) {
            return 1;
        }
        if (arg0->unk5 != 1) {
            if (arg0->unk5 != 2) {
                if (arg0->unk5 != 5) {
                    if (arg0->unk5 != 4) {
                        if (arg0->unk5 != 0xC) {
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

void func_8003DE84(struct RideArmorObj* arg0)
{
    u16 active_mask;
    u32 buttons;
    u16 current_mask;
    s8 mode;

    if (arg0->unk8C.bytes.cooldown != 0 || (arg0->unk94.bytes.unk97 & 2) != 0) {
        return;
    }

    if (arg0->unk8E.bytes.active == 0) {
        buttons = arg0->unk8A & 3;
        if ((u16)buttons != 0 && (u16)buttons != 3) {
            arg0->pad9A = buttons;
            arg0->unk8E.bytes.active = 1;
            arg0->unk8E.bytes.timer = 12;
        }
        return;
    }

    active_mask = arg0->pad9A;
    current_mask = arg0->unk8A;
    if ((active_mask & current_mask) != 0 && func_8003DE08(MAIN_OBJECT(arg0)) == 0) {
        mode = arg0->unk67;
        if (mode == 0) {
            func_8003DC44(BASE_OBJECT(arg0), 7);
            arg0->unk94.bytes.unk97 ^= 8;
            return;
        }
        if (arg0->unk7D == 0) {
            func_8003DC44(BASE_OBJECT(arg0), 15);
            arg0->unk94.bytes.unk97 ^= 8;
            return;
        }
    }

    arg0->unk8E.bytes.timer--;
    if (arg0->unk8E.bytes.timer == 0) {
        arg0->unk8E.bytes.active = 0;
    }
}

void func_8003DF9C(struct PlayerObj* arg0)
{
    struct BaseObj* base;
    s8 effect;

    if ((arg0->unk8D == 0) && !(arg0->last_shot_type & 2) && (arg0->unk8A.packed & 0x100) && (func_8003DE08(MAIN_OBJECT(arg0)) == 0)) {
        base = BASE_OBJECT(arg0);
        if (arg0->air_state == 0) {
            effect = 7;
        } else if (arg0->input.bytes.held_high == 0) {
            effect = 0xF;
        } else {
            return;
        }

        func_8003DC44(base, effect);
        arg0->last_shot_type |= 8;
    }
}

s32 func_8003E048(struct PlayerObj* arg0)
{
    u16 mask;
    u16 flags;

    if (!(arg0->last_shot_type & 8)) {
        mask = 2;
        if (arg0->unk15 != 0) {
            mask = 1;
        }
        return mask & arg0->unk88.value;
    }

    mask = 2;
    if (arg0->unk15 != 0) {
        mask = 1;
    }
    flags = arg0->unk88.value;
    return (flags & mask) ? (flags & mask) : (u16)(flags & 0x100);
}

s32 func_8003E0B0(struct PlayerObj* arg0)
{
    u16 mask;

    mask = 1;
    if (arg0->unk15 != 0) {
        mask = 2;
    }
    return arg0->unk88.value & mask;
}

void func_8003E0D0(struct RideArmorObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->unk68 = &D_800F9124;
        *(u8*)&self->unk8C = 0;
        set_animation(self, 0x11);
    } else if (!(self->input_flags & 8)) {
        func_8003DC44(BASE_OBJECT(self), 0xC);
    } else if (g_Player.script_state == 0 && engine_obj.unkF == 0
        && (g_Player.unk2 == 0 || g_Player.attacking == 0) && g_Player.spike_immune == 0
        && g_Player.nova_strike_active == 0 && !(self->unk94.halves[1] & 0x8200)
        && func_8002C160(COLLISION_OBJECT(&g_Player), COLLISION_OBJECT(self))
        && engine_obj.unkF == 0 && g_Player.hp > 0 && g_Player.hurt_phase == 0
        && g_Player.touching_spikes == 0) {
        func_8003DC44(BASE_OBJECT(self), 0xA);
        set_animation(self, 0x12);
        self->unk94.bytes.unk97 |= 0x40;
        g_Player.ride_state = 1;
    }
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mech", func_8003E274);
#else
void func_8003E274(struct RideArmorObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        RIDE_U8(arg0, 0x94) = 0;
        arg0->unkA6 = 0;
        arg0->unk68 = &D_800F9120;
        set_animation(arg0, 0x12);
        func_8003DC1C((struct PlayerObj*)arg0, 0x39);
        if (arg0->id == 0)
            func_8001540C(5, SATURN_SOUND(6, 62), NULL);
        else
            func_8001540C(5, SATURN_SOUND(4, 74), NULL);
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        if (RIDE_U8(arg0, 0x8C) == 0)
            arg0->unk61 = 0;
        RIDE_U8(arg0, 0x94) = 0;
        arg0->unkA6 = 0;
        RIDE_ARMOR_STATE(arg0, 1);
        arg0->unk54 = &D_800F9128;
        return;
    }
    if (arg0->animation_step.fields.event & 1) {
        func_8003D638((struct VisualObj*)arg0, 7);
        arg0->animation_step.fields.event = 0;
        return;
    }
    animate_object(ANIMATED_OBJECT(arg0));
}
#endif

void func_8003E368(struct RideArmorObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->unk98.packed = 0x160;
        set_animation(self, 0);
        func_8003DC1C(PLAYER_OBJECT(self), 0x29);
        self->unk87 = 0;
    }
    if (self->unk94.bytes.pad94[0] == 2) {
        func_8003DC44(BASE_OBJECT(self), 0xD);
        return;
    }
    if (func_8003DC8C(self)) {
        func_8003DC44(BASE_OBJECT(self), 0xB);
        return;
    }
    if (!(self->input_flags & 8)) {
        func_8003DC44(BASE_OBJECT(self), 0xC);
        return;
    }
    if (!(self->unk94.bytes.unk97 & 2)) {
        if (func_8003DC50(self)) {
            func_8003DC44(BASE_OBJECT(self), 2);
        } else if ((u16)self->unk8A & 0x80) {
            func_8003DC44(BASE_OBJECT(self), 4);
        } else if (func_8003DCD8(self)) {
            func_8003DC44(BASE_OBJECT(self), 3);
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_8003E488(struct RideArmorObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->unk98.packed = 0x160;
        set_animation(self, 1);
        func_8003DC1C(PLAYER_OBJECT(self), 0x2A);
        self->unk87 = 0;
    }
    if (self->unk94.bytes.pad94[0] == 2) {
        func_8003DC44(BASE_OBJECT(self), 0xD);
        return;
    }
    if (func_8003DC8C(self)) {
        func_8003DC44(BASE_OBJECT(self), 0xB);
        return;
    }
    if (!(self->input_flags & 8)) {
        func_8003DC44(BASE_OBJECT(self), 0xC);
        return;
    }
    if (!(self->unk94.bytes.unk97 & 2)) {
        if (!func_8003DC50(self)) {
            func_8003DC44(BASE_OBJECT(self), 1);
            return;
        }
        if ((u16)self->unk8A & 0x80) {
            func_8003DC44(BASE_OBJECT(self), 4);
            return;
        }
        if (func_8003DCD8(self)) {
            func_8003DC44(BASE_OBJECT(self), 3);
            return;
        }
        func_8003DD2C(MAIN_OBJECT(self));
        func_8003DD14(MAIN_OBJECT(self));
    }
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        func_8001540C(5, SATURN_SOUND((u8)self->animation_step.fields.event, self->unk2 != 0 ? 69 : 57), NULL);
        self->animation_step.fields.event = 0;
    }
}

void func_8003E5F8(struct RideArmorObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        if ((u8)self->unk87 == 1) {
            func_8003D7E4(self, 2, 1);
            set_animation(self, 0xA);
            func_8003DC1C(PLAYER_OBJECT(self), 0x32);
            func_8001540C(5, SATURN_SOUND(5, 61), NULL);
        } else {
            func_8003D7E4(self, 0, 0);
            set_animation(self, 8);
            func_8003DC1C(PLAYER_OBJECT(self), 0x31);
            func_8001540C(5, SATURN_SOUND(0, 56), NULL);
        }
        self->unk80.bytes.unk81 = 0;
    }
    if (self->animation_step.fields.relative_step == 0) {
        if (self->unk80.bytes.unk81 != 0) {
            func_8003DC44(BASE_OBJECT(self), 3);
        } else {
            self->unk87 = 0;
            self->unk80.bytes.unk81 = 0;
            func_8003DC44(BASE_OBJECT(self), 1);
        }
        return;
    }
    if ((self->animation_step.fields.event & 1) && func_8003DCD8(self)
        && self->unk80.bytes.unk81 == 0 && (u8)self->unk87 < 2) {
        self->unk87++;
        self->unk80.bytes.unk81 = 1;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_8003E750(struct RideArmorObj* self)
{
    if (self->unk6 == 0) {
        self->y_vel.val = FIXED(5.5);
        self->unk6 = 1;
        self->unk2C = FIXED(0.2578125);
        self->x_vel.val = 0;
        self->unk28 = 0;
        self->unk67 = 1;
        if (self->unk2 == 0) {
            func_8003D638(VISUAL_OBJECT(self), 6);
        }
        set_animation(self, 2);
        func_8003DC1C(PLAYER_OBJECT(self), 0x2B);
        self->unk87 = 0;
        if (self->unk2 == 0) {
            func_8001540C(5, SATURN_SOUND(4, 60), NULL);
        } else {
            func_8001540C(5, SATURN_SOUND(3, 72), NULL);
        }
    }
    if (func_8003DCD8(self)) {
        func_8003DC44(BASE_OBJECT(self), 6);
        return;
    }
    if (func_8003DC8C(self)) {
        func_8003DC44(BASE_OBJECT(self), 0xB);
        return;
    }
    if (self->unk94.bytes.unk97 & 2) {
        return;
    }
    self->x_vel.val = 0;
    func_8003DD54(self);
    if (!(self->input_flags & 4) && self->y_vel.val >= 0 && (self->collision_flags & 0x80)) {
        move_with_gravity(ANIMATED_OBJECT(self));
        return;
    }
    func_8003DC44(BASE_OBJECT(self), 0xC);
}

void func_8003E8A0(struct RideArmorObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->unk98.packed = 0x160;
        self->unk67 = 0;
        self->unk7D = 0;
        set_animation(self, 4);
        func_8003DC1C(PLAYER_OBJECT(self), 0x2D);
        self->input_flags |= 8;
        if (self->unk2 == 0) {
            func_8001540C(5, SATURN_SOUND(1, 57), NULL);
        } else {
#ifdef MMX4_SATURN
            func_8001540C(5, 69, NULL);
#else
            func_8001540C(5, 0, NULL);
            stop_sound(5, 5);
            func_8001540C(5, 0, NULL);
#endif
        }
    }
    if (func_8003DC8C(self)) {
        func_8003DC44(BASE_OBJECT(self), 0xB);
        return;
    }
    if (self->animation_step.fields.relative_step == 0) {
        func_8003DC44(BASE_OBJECT(self), 1);
        return;
    }
    if (!(self->unk94.bytes.unk97 & 2)) {
        if (!(self->input_flags & 8)) {
            func_8003DC44(BASE_OBJECT(self), 0xC);
        } else if (func_8003DCD8(self)) {
            func_8003DC44(BASE_OBJECT(self), 3);
        } else if (func_8003DC50(self)) {
            func_8003DD2C(MAIN_OBJECT(self));
            func_8003DD14(MAIN_OBJECT(self));
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_8003EA08(struct RideArmorObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        func_8003D7E4(self, 3, 1);
        set_animation(self, 0xB);
        func_8003DC1C(PLAYER_OBJECT(self), 0x33);
        func_8001540C(5, SATURN_SOUND(5, 61), NULL);
    }
    if (self->input_flags & 8) {
        func_8003DC44(BASE_OBJECT(self), 5);
        return;
    }
    if (!(self->unk94.bytes.unk97 & 2)) {
        self->x_vel.val = 0;
        self->unk28 = 0;
        func_8003DDA0(self);
        if (self->y_vel.val >= 0 && ((self->input_flags & 4) || !(self->collision_flags & 0x80))) {
            self->y_vel.val = 0;
        }
        if (self->animation_step.fields.relative_step == 0) {
            self->unk5 = self->y_vel.val < 0 ? 0xC : 4;
        } else {
            if (self->y_vel.val < FIXED(-5.875)) {
                self->y_vel.val = FIXED(-5.875);
            }
            move_with_gravity(ANIMATED_OBJECT(self));
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_8003EB4C(struct RideArmorObj* self)
{
    s8 timer;

    func_8003D7A0();
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->unk98.packed = 0x420;
        if (self->unk15 != 0) {
            self->x_vel.val = FIXED(4.125);
        } else {
            self->x_vel.val = FIXED(-4.125);
        }
        self->unk90.byte = 0x1E;
        set_animation(self, 5);
        func_8003DC1C(PLAYER_OBJECT(self), 0x2F);
        if (self->unk2 == 0) {
            func_8001540C(5, SATURN_SOUND(3, 59), NULL);
            func_8003D638(VISUAL_OBJECT(self), 5);
        } else {
            func_8001540C(5, SATURN_SOUND(2, 71), NULL);
        }
    }
    if (func_8003DC8C(self)) {
        func_8003DC44(BASE_OBJECT(self), 0xB);
        return;
    }
    if (!(self->unk94.bytes.unk97 & 2)) {
        if ((u16)self->unk8A & 0x80) {
            func_8003DC44(BASE_OBJECT(self), 4);
        } else if (func_8003DCD8(self)) {
            func_8003DC44(BASE_OBJECT(self), 9);
        } else if (!(self->input_flags & 8)) {
            func_8003DC44(BASE_OBJECT(self), 0xC);
        } else if ((self->input_flags & 3) || !func_8003E048(PLAYER_OBJECT(self))) {
            func_8003DC44(BASE_OBJECT(self), 8);
            return;
        } else {
            func_8003DD14(MAIN_OBJECT(self));
            timer = self->unk90.byte--;
            if (timer < 0) {
                func_8003DC44(BASE_OBJECT(self), 8);
                return;
            }
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_8003ED00(struct RideArmorObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->unk98.packed = 0x160;
        set_animation(self, 7);
        func_8003DC1C(PLAYER_OBJECT(self), 0x30);
    }
    if (func_8003DC8C(self) != 0) {
        func_8003DC44(BASE_OBJECT(self), 0xB);
        return;
    }
    if (!(self->unk94.bytes.unk97 & 2)) {
        if (self->animation_step.fields.relative_step == 0) {
            func_8003DC44(BASE_OBJECT(self), 1);
        } else if ((u16)self->unk8A & 0x80) {
            func_8003DC44(BASE_OBJECT(self), 4);
        } else if (func_8003DCD8(self) != 0 || (self->collision_flags & 3)) {
            func_8003DC44(BASE_OBJECT(self), 3);
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_8003EDF0(struct RideArmorObj* self)
{
    s8 timer;
    u8 input;

    func_8003D7A0();
    if (self->unk6 == 0) {
        self->unk6 = 1;
        func_8003D7E4(self, 1, 1);
        set_animation(self, 9);
        func_8003DC1C(PLAYER_OBJECT(self), 0x37);
        func_8001540C(5, SATURN_SOUND(0, 56), 0);
    }

    timer = --self->unk90.byte;
    input = self->input_flags;
    if (!(input & 8)) {
        func_8003DC44(BASE_OBJECT(self), 0xC);
        return;
    }

    if (!(self->unk94.bytes.unk97 & 2)) {
        if ((input & 3) || (self->animation_step.fields.event & 1)) {
            if (timer < 0) {
                func_8003DC44(BASE_OBJECT(self), 8);
            } else {
                func_8003DD14(MAIN_OBJECT(self));
            }
        } else if (func_8003E048(PLAYER_OBJECT(self)) != 0) {
            func_8003DD14(MAIN_OBJECT(self));
        }
    }

    animate_object(ANIMATED_OBJECT(self));
}

void func_8003EEF8(struct RideArmorObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->unk61 = 1;
        self->unk68 = &D_800F9124;
        *(u8*)&self->unk8C = 0;
        self->unk94.bytes.pad94[0] = 0;
        self->unkA6 = 0;
        STOP_SOUND(5, 8, 1);
        if (!(self->unk94.bytes.unk97 & 2)) {
            self->x_vel.val = 0;
            self->unk28 = 0;
            self->y_vel.val = FIXED(2);
            self->unk2C = FIXED(0.25);
        }
        if (self->unk94.bytes.unk97 & 0x40) {
            if (!(self->unk94.bytes.unk97 & 2)) {
                self->y_vel.val = 0;
                self->unk2C = 0;
            }
            g_Player.ride_state = 0;
            self->unk94.bytes.unk97 ^= 0x40;
            player_set_collision_bounds(&g_Player);
        }
        if (!(self->input_flags & 8)) {
            func_8003DC44(BASE_OBJECT(self), 0xC);
        } else {
            set_animation(self, 0x13);
        }
        self->unk42 &= 0x7FFF;
    }
    if (self->input_flags & 8) {
        self->y_vel.val = 0;
    }
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6 = 0;
        self->unk5 = 0;
        STOP_SOUND(5, 8, 1);
        *(u8*)&self->unk8C = 0;
        self->unk94.bytes.pad94[0] = 0;
        self->unkA6 = 0;
    }
    if (!(self->unk94.bytes.unk97 & 2)) {
        move_with_gravity(ANIMATED_OBJECT(self));
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_8003F068(struct RideArmorObj* self)
{
    u8 flags;

    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->x_vel.val = 0;
        self->unk28 = 0;
        self->y_vel.val = 0;
        self->unk2C = FIXED(0.2578125);
        self->unk94.bytes.pad94[2] = 0x28;
        self->unk67 = 1;
        if (self->unk94.bytes.unk97 & 0x40) {
            func_8003DC1C(PLAYER_OBJECT(self), 0x2C);
        }
        set_animation(self, 3);
    }
    if ((self->unk94.bytes.unk97 & 0x40) && func_8003DC8C(self)) {
        func_8003DC44(BASE_OBJECT(self), 0xB);
        return;
    }
    if (self->input_flags & 8) {
        if (self->unk94.bytes.unk97 & 0x40) {
            func_8003DC44(BASE_OBJECT(self), 5);
            return;
        }
        self->unk67 = 0;
        func_8003DC44(BASE_OBJECT(self), 0xB);
        return;
    }
    flags = self->unk94.bytes.unk97;
    if (flags & 2) {
        return;
    }
    if (flags & 0x40) {
        if (func_8003DCD8(self)) {
            func_8003DC44(BASE_OBJECT(self), 6);
            return;
        }
        if (self->unk2 != 0 && self->unk7D == 0 && ((u16)self->unk8A & 0x80)) {
            func_8003DC44(BASE_OBJECT(self), 0xE);
            return;
        }
        self->x_vel.val = 0;
        func_8003DD54(self);
        if (self->y_vel.val < FIXED(-5.875)) {
            self->y_vel.val = FIXED(-5.875);
        }
    }
    move_with_gravity(ANIMATED_OBJECT(self));
}

void func_8003F204(struct RideArmorObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        func_8003DC44(BASE_OBJECT(arg0), 1);
        return;
    }
    animate_object(ANIMATED_OBJECT(arg0));
}

void func_8003F244(struct RideArmorObj* arg0)
{
    func_8003D7A0();
    if (func_8003DC8C(arg0) != 0) {
        func_8003DC44(BASE_OBJECT(arg0), 0xB);
        return;
    }
    if (!(arg0->unk94.bytes.unk97 & 2)) {
        if (!(arg0->input_flags & 8)) {
            func_8003DC44(BASE_OBJECT(arg0), 0xC);
        } else {
            func_8003DD14(MAIN_OBJECT(arg0));
            if ((func_8003E0B0(PLAYER_OBJECT(arg0)) != 0) || (--arg0->unk90.byte == 0)) {
                arg0->unk6 = 3;
                set_animation(arg0, 0x10);
                func_8003DC1C(PLAYER_OBJECT(arg0), 0x29);
            }
        }
    }
    animate_object(ANIMATED_OBJECT(arg0));
}

void func_8003F31C(struct RideArmorObj* self)
{
    if (func_8003DC8C(self)) {
        func_8003DC44(BASE_OBJECT(self), 0xB);
        return;
    }
    if (!(self->unk94.bytes.unk97 & 2)) {
        if (!(self->input_flags & 8)) {
            func_8003DC44(BASE_OBJECT(self), 0xC);
        } else {
            func_8003DC50(self);
            if (!(self->unk94.bytes.unk97 & 0x10)) {
                if (self->unk94.bytes.pad94[0] == 0) {
                    self->unk6 = 2;
                    self->unk98.packed = 0x420;
                    if (self->unk15 == 0) {
                        self->x_vel.val = FIXED(-4.125);
                    } else {
                        self->x_vel.val = FIXED(4.125);
                    }
                    self->unk90.byte = 0x1E;
                    func_8003D7E4(self, 4, 1);
                    set_animation(self, 0xF);
                    func_8003DC1C(PLAYER_OBJECT(self), 0x36);
                    if (self->unk2 == 0) {
                        func_8001540C(5, SATURN_SOUND(5, 61), 0);
                    } else {
                        func_8001540C(5, SATURN_SOUND(6, 76), 0);
                    }
                }
            }
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mech", func_8003F44C);
#else
void func_8003F44C(struct RideArmorObj* self)
{
    u32 i;
    u8 parts;

    if (func_8003DC8C(self)) {
        func_8003DC44(BASE_OBJECT(self), 0xB);
        return;
    }
    if (!(self->unk94.bytes.unk97 & 2)) {
        if (!(self->input_flags & 8)) {
            func_8003DC44(BASE_OBJECT(self), 0xC);
        } else {
            func_8003DC50(self);
            if (!(self->unk94.bytes.unk97 & 0x10)) {
                if (self->unk94.bytes.pad94[0] == 0) {
                    self->unk6 = 5;
                    parts = self->spawned_parts;
                    for (i = 0; i < 3; i++, parts >>= 1) {
                        if (!(parts & 1)) {
                            func_8003D8A8(self, (u8)i, 1);
                            self->spawned_parts |= 1 << i;
                        }
                    }
                    self->unk7E = 0x10;
                    func_8001540C(5, SATURN_SOUND(6, 76), 0);
                }
            }
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}
#endif

void func_8003F570(struct RideArmorObj* arg0)
{
    if (arg0->unk2 == 0) {
        arg0->unk6 = 1;
        set_animation(arg0, 0xC);
        func_8003DC1C(PLAYER_OBJECT(arg0), 0x34);
        func_8003F31C(arg0);
        func_8001540C(5, SATURN_SOUND(7, 63), NULL);
        return;
    }

    arg0->unk6 = 4;
    func_8003D6EC(ANIMATED_OBJECT(arg0), 0x10);
    set_animation(arg0, 0xE);
    func_8003DC1C(PLAYER_OBJECT(arg0), 0x40);
    arg0->unk7E = 8;
    func_8003F44C(arg0);
}

void func_8003F618(struct RideArmorObj* arg0)
{
    if (arg0->unk7E == 0) {
        func_8003DC44(BASE_OBJECT(arg0), 1);
    }
}

void func_8003F648(struct RideArmorObj* arg0)
{
    if (!(arg0->unk94.bytes.unk97 & 2)) {
        D_800F9138[arg0->unk6](arg0);
    }
}

void func_8003F698(struct RideArmorObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        func_8003D8A8(arg0, 0, 0);
        set_animation(arg0, 8);
        func_8003DC1C(PLAYER_OBJECT(arg0), 0x3F);
        func_8001540C(5, SATURN_SOUND(7, 77), 0);
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk87 = 0;
        func_8003DC44(BASE_OBJECT(arg0), 1);
        return;
    }
    if (arg0->animation_step.fields.event != 0 && func_8003DCD8(arg0) != 0 && arg0->unk86 < 3U) {
        func_8003DC44(BASE_OBJECT(arg0), 3);
    }
    animate_object(ANIMATED_OBJECT(arg0));
}

void func_8003F76C(struct RideArmorObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        if (self->collision_flags & 8) {
            set_animation(self, 9);
            func_8003DC1C(PLAYER_OBJECT(self), 0x33);
            func_8003D8A8(self, 1, 0);
        } else {
            func_8003D8A8(self, 0, 0);
        }
        func_8001540C(5, SATURN_SOUND(7, 77), NULL);
    }
    if (self->input_flags & 8) {
        func_8003DC44(BASE_OBJECT(self), 5);
        return;
    }
    if (!(self->unk94.bytes.unk97 & 2)) {
        self->x_vel.val = 0;
        self->unk28 = 0;
        func_8003DDA0(self);
        if (self->y_vel.val >= 0 && ((self->input_flags & 4) || !(self->collision_flags & 0x80))) {
            self->y_vel.val = 0;
        }
        if (self->animation_step.fields.relative_step == 0) {
            self->unk5 = self->y_vel.val < 0 ? 0xC : 4;
        } else {
            if (self->y_vel.val < FIXED(-5.875)) {
                self->y_vel.val = FIXED(-5.875);
            }
            move_with_gravity(ANIMATED_OBJECT(self));
            if (self->animation_step.fields.event != 0 && func_8003DCD8(self) && self->unk86 < 3) {
                func_8003DC44(BASE_OBJECT(self), 6);
            }
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_8003F908(struct RideArmorObj* self)
{
    s8 timer;

    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->unk7D = 1;
        self->unk98.packed = 0x420;
        if (self->unk15 != 0) {
            self->x_vel.val = FIXED(4.125);
        } else {
            self->x_vel.val = FIXED(-4.125);
        }
        self->unk90.byte = 0x1E;
        self->unk2C = 0;
        self->y_vel.val = 0;
        set_animation(self, 0xC);
        func_8003DC1C(PLAYER_OBJECT(self), 0x2F);
        func_8001540C(5, SATURN_SOUND(2, 71), NULL);
    }
    if (func_8003DC8C(self)) {
        func_8003DC44(BASE_OBJECT(self), 0xB);
        return;
    }
    if (!(self->unk94.bytes.unk97 & 2)) {
        if (func_8003DCD8(self)) {
            func_8003DC44(BASE_OBJECT(self), 0x10);
        } else if ((self->input_flags & 3) || !func_8003E048(PLAYER_OBJECT(self))) {
            func_8003DC44(BASE_OBJECT(self), 0xC);
            return;
        } else {
            func_8003DD14(MAIN_OBJECT(self));
            timer = self->unk90.byte--;
            if (timer < 0) {
                func_8003DC44(BASE_OBJECT(self), 0xC);
                return;
            }
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_8003FA58(struct RideArmorObj* self)
{
    s8 timer;

    if (self->unk6 == 0) {
        self->unk6 = 1;
        if (self->collision_flags & 8) {
            func_8003D8A8(self, 1, 0);
            set_animation(self, 0xA);
            func_8003DC1C(PLAYER_OBJECT(self), 0x37);
        } else {
            func_8003D8A8(self, 0, 0);
        }
        func_8001540C(5, SATURN_SOUND(7, 77), NULL);
    }
    timer = --self->unk90.byte;
    if (!(self->unk94.bytes.unk97 & 2)) {
        if (self->input_flags & 3) {
            func_8003DC44(BASE_OBJECT(self), 0xC);
        } else if (timer < 0) {
            func_8003DC44(BASE_OBJECT(self), 0xC);
        } else if (self->animation_step.fields.relative_step == 0) {
            func_8003DD14(MAIN_OBJECT(self));
            self->unk5 = 0xF;
            self->unk6 = 1;
        } else {
            if (func_8003E048(PLAYER_OBJECT(self))) {
                func_8003DD14(MAIN_OBJECT(self));
            }
            if (func_8003DCD8(self) && self->unk86 < 3) {
                func_8003DC44(BASE_OBJECT(self), 0x10);
                if (self->collision_flags & 8) {
                    set_animation(self, 0xA);
                } else {
                    set_animation(self, 0xC);
                }
            }
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_8003FBD8(struct RideArmorObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->unk7D = 1;
        self->unk98.packed = 0x160;
        set_animation(self, 0xD);
        func_8003DC1C(PLAYER_OBJECT(self), 0x3C);
        self->unk87 = 0;
        func_8001540C(5, SATURN_SOUND(5, 75), 0);
    }
    if (func_8003DC8C(self)) {
        func_8003DC44(BASE_OBJECT(self), 0xB);
        return;
    }
    if (self->input_flags & 8) {
        func_8003DC44(BASE_OBJECT(self), 5);
        return;
    }
    if (!(self->unk94.bytes.unk97 & 2)) {
        if ((u16)self->unk8A & 0x80) {
            func_8003DC44(BASE_OBJECT(self), 0xC);
            return;
        }
        if (func_8003DCD8(self)) {
            func_8003DC44(BASE_OBJECT(self), 0x11);
            return;
        }
        if (func_8003DC50(self)) {
            func_8003DD2C(MAIN_OBJECT(self));
            func_8003DD14(MAIN_OBJECT(self));
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_8003FD08(struct RideArmorObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->unk7D = 1;
        self->unk98.packed = 0x160;
        if (self->collision_flags & 8) {
            func_8003D8A8(self, 1, 0);
            set_animation(self, 0xB);
            func_8003DC1C(PLAYER_OBJECT(self), 0x3D);
        } else {
            func_8003D8A8(self, 0, 0);
        }
        self->unk87 = 0;
        func_8001540C(5, SATURN_SOUND(7, 77), NULL);
    }
    if (func_8003DC8C(self)) {
        func_8003DC44(BASE_OBJECT(self), 0xB);
        return;
    }
    if (self->input_flags & 8) {
        func_8003DC44(BASE_OBJECT(self), 5);
        return;
    }
    if (!(self->unk94.bytes.unk97 & 2)) {
        if ((u16)self->unk8A & 0x80) {
            func_8003DC44(BASE_OBJECT(self), 0xC);
            return;
        }
        if (self->animation_step.fields.relative_step < 0) {
            func_8003DC44(BASE_OBJECT(self), 0xE);
            return;
        }
        if (self->animation_step.fields.event != 0 && func_8003DCD8(self) && self->unk86 < 3) {
            self->unk5 = 0x11;
            if (self->collision_flags & 8) {
                func_8003D8A8(self, 1, 0);
                set_animation(self, 0xB);
                func_8003DC1C(PLAYER_OBJECT(self), 0x3D);
            } else {
                set_animation(self, 0xD);
                func_8003DC1C(PLAYER_OBJECT(self), 0x3C);
                func_8003D8A8(self, 0, 0);
            }
            return;
        }
        if (func_8003DC50(self)) {
            func_8003DD2C(MAIN_OBJECT(self));
            func_8003DD14(MAIN_OBJECT(self));
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_8003FF14(struct MainObj* arg0)
{
    arg0->x_speed -= arg0->x_accel;
    arg0->y_speed -= arg0->gravity;
    arg0->x_pos.val += arg0->x_speed;
    arg0->y_pos.val += arg0->y_speed;
}

void func_8003FF58(struct MainObj* arg0)
{
    arg0->x_speed += arg0->x_accel;
    arg0->y_speed -= arg0->gravity;
    arg0->x_pos.val += arg0->x_speed;
    arg0->y_pos.val += arg0->y_speed;
}

void func_8003FF9C(struct RideArmorObj* self)
{
    s32 velocity;

    switch (self->unk90.bytes.action_state) {
    case 1:
        self->unk90.bytes.action_state = 2;
        self->saved_x_vel = self->x_vel.val >> 8;
        self->saved_y_vel = self->y_vel.val >> 8;
        self->unkA0.saved_accel.x = self->unk28 >> 8;
        self->unkA0.saved_accel.y = self->unk2C >> 8;
        if (self->unk15 == 0) {
            self->x_vel.val = (self->launch_speed << 8);
        } else {
            self->x_vel.val = (-(self->launch_speed << 8));
        }
        self->unk28 = 0x5800;
        self->y_vel.val = 0;
        self->unk2C = 0x5800;
        break;
    case 2:
        move_with_gravity(ANIMATED_OBJECT(self));
        velocity = self->x_vel.val;
        if (velocity < 0) {
            velocity = -velocity;
        }
        if (velocity < 0x4800) {
            self->unk90.bytes.action_state = 0;
            self->unk94.bytes.unk97 ^= 2;
            self->x_vel.val = self->saved_x_vel << 8;
            self->unk28 = self->unkA0.saved_accel.x << 8;
            self->unk2C = self->unkA0.saved_accel.y << 8;
        }
        if (self->input_flags & 8) {
            self->y_vel.val = 0;
        }
        break;
    }
}

void func_800400C8(struct PlayerObj* self)
{
    s8 temp_v0;
    u8 temp_v1;

    temp_v1 = self->unk8D;
    switch (temp_v1) {
    case 1:
        self->unk8D = 2;
        *(u8*)&self->afterimage = 0xFF;
        g_Player.ride_state = 0;
        self->last_shot_type ^= 0x40;
        player_set_collision_bounds(&g_Player);
        self->attack_ended = 0x1E;
        self->last_shot_type |= 4;
        spawn_debris(7, D_800F9118, self);
        return;
    case 2:
        temp_v0 = (u8)self->attack_ended - 1;
        self->attack_ended = temp_v0;
        if (temp_v0 == 0) {
            self->state = 2;
            self->on_screen = 0;
            spawn_explosion(BASE_OBJECT(self));
            STOP_SOUND(5, 8, 1);
            return;
        }
        func_800AF878(BASE_OBJECT(self), 0, 0x1F, 0x1F);
        return;
    default:
        if ((*(u8*)&self->afterimage == 0) && !(*(u8*)&self->last_shot_type & 0x80)) {
            self->dash_timer = 0;
            self->unk42 &= 0x7FFF;
        }
        return;
    }
}

void func_800401F8(struct PlayerObj* arg0)
{
    u8 temp_v0;

    if (arg0->last_shot_type & 0x40) {
        temp_v0 = arg0->afterimage;
        if (temp_v0 != 0) {
            if ((BLINK_CLOCK(temp_v0) & 3) == 0) {
                arg0->unk42 |= 0x8000;
            } else {
                arg0->unk42 &= 0x7FFF;
            }
        }
    }
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mech", func_80040248);
#else
void func_80040248(struct RideArmorObj* arg0)
{
    if ((u8)RIDE_ARMOR_FLAGS(arg0) & 0x80) {
        arg0->unk42 &= 0x7FFF;
        if (--RIDE_U8(arg0, 0x92) == 0) {
            arg0->unk42 |= 0x8000;
            RIDE_U8(arg0, 0x92) = RIDE_U8(arg0, 0x91);
            if (--RIDE_U8(arg0, 0x91) == 0) {
                RIDE_U8(arg0, 0x8D) = 1;
                arg0->unk42 &= 0x7FFF;
            }
        }
    }
}
#endif

void func_800402C4(struct PlayerObj* self)
{
    s16 x_limit;
    s16 y_limit;
    if (self->last_shot_type & 0x40) {
        x_limit = (u16)background_objects[self->bg_offset].unk1C + 0x140;
        if (self->x_pos.i.hi + 0x20 >= x_limit) {
            self->x_pos.i.hi = background_objects[self->bg_offset].unk1C + 0x120;
        }
        if (self->x_pos.i.hi - 0x20 < background_objects[self->bg_offset].unk1E) {
            self->x_pos.i.hi = background_objects[self->bg_offset].unk1E + 0x20;
        }
    }
    y_limit = (u16)background_objects[self->bg_offset].unk20 + 0xF0;
    if (self->y_pos.i.hi - 0x20 >= y_limit) {
        self->state = 2;
        if (self->last_shot_type & 0x40) {
            g_Player.hp = -0x80;
        }
    }
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mech", func_800403DC);
#else
void func_800403DC(struct RideArmorObj* arg0)
{
    s32 flag;

    arg0->on_screen = 0;
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        if (arg0->hp < 0) {
            if (arg0->hp == -0x80) {
                RIDE_U8(arg0, 0x91) = RIDE_U8(arg0, 0x92) = 0x1E;
                RIDE_U8(arg0, 0x8C) = 0;
                flag = 0x80;
                RIDE_ARMOR_FLAGS(arg0) |= flag;
            }
            arg0->launch_speed = 0x400;
            RIDE_U8(arg0, 0x8C) = 0x79;
            func_8003D638((struct VisualObj*)arg0, 8);
            RIDE_U8(arg0, 0x93) = 1;
            arg0->unk85 = 1;
            RIDE_ARMOR_FLAGS(arg0) |= 2;
        }
        if (RIDE_U8(arg0, 0x8C) != 0) {
            RIDE_U8(arg0, 0x8C)
            --;
            if (RIDE_U8(arg0, 0x8C) == 0 && (RIDE_ARMOR_FLAGS(arg0) & 1))
                g_Player.on_screen = 1;
        }
        if ((RIDE_ARMOR_FLAGS(arg0) & 0x41) == 0x41 || (engine_obj.unkF != 0 && (RIDE_ARMOR_FLAGS(arg0) & 0x40))) {
            RIDE_ARMOR_FLAGS(arg0) ^= 1;
            RIDE_ARMOR_STATE(arg0, 0xB);
        }
        func_8003DE84(arg0);
        func_8003DF9C((struct PlayerObj*)arg0);
        func_8003D9E0(arg0);
        if (RIDE_U8(arg0, 0x8D) == 0) {
            if (arg0->unk2 == 0) {
#if defined(MMX4_PC) || defined(MMX4_SATURN)
                if ((u8)arg0->unk5 >= 14)
                    D_800F9188[(u8)arg0->unk5 - 14](arg0);
                else
#endif
                    D_800F9150[arg0->unk5](arg0);
            } else {
                if (arg0->unk7E != 0)
                    arg0->unk7E--;
                D_800F9188[arg0->unk5](arg0);
            }
            func_8003FF9C(arg0);
            CollisionRelated((struct PlayerObj*)arg0);
            if (RIDE_ARMOR_FLAGS(arg0) & 0x40)
                func_8003DDDC((struct PlayerObj*)arg0);
            func_800401F8((struct PlayerObj*)arg0);
            func_80040248(arg0);
            func_8002B3C0(BASE_OBJECT(arg0));
        }
        func_800400C8((struct PlayerObj*)arg0);
        func_800402C4((struct PlayerObj*)arg0);
    }
}
#endif

void func_800405D4(struct RideArmorObj* arg0)
{
    u8* backref = arg0->backref;

    if (backref != NULL) {
        *backref = 0x80;
    }
    arg0->active = 0;
    arg0->unk2 = 0;
    arg0->on_screen = 0;
    arg0->state = 0;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
}

union AnimationStep D_800F91D0[] = {
    { 100, 0, 1, 0x00 },
    { 7, 0, 1, 0x0B },
    { 50, 1, 1, 0x0C },
    { 8, 0, -3, 0x0B },
};

union AnimationStep D_800F91E0[] = {
    { 6, 0, 1, 0x01 },
    { 6, 0, 1, 0x02 },
    { 6, 0, 1, 0x03 },
    { 10, 1, 1, 0x04 },
    { 6, 0, 1, 0x05 },
    { 6, 0, 1, 0x06 },
    { 6, 0, 1, 0x07 },
    { 10, 1, -7, 0x08 },
};

union AnimationStep D_800F9200[] = {
    { 8, 0, 0, 0x09 },
};

union AnimationStep D_800F9204[] = {
    { 8, 0, 0, 0x0A },
};

union AnimationStep D_800F9208[] = {
    { 2, 0, 1, 0x0B },
    { 8, 0, 1, 0x0C },
    { 7, 0, 1, 0x0B },
    { 8, 0, 0, 0x00 },
};

union AnimationStep D_800F9218[] = {
    { 4, 0, 1, 0x0D },
    { 8, 0, 1, 0x0E },
    { 8, 0, 0, 0x0D },
};

union AnimationStep D_800F9224[] = {
    { 8, 0, 0, 0x0D },
};

union AnimationStep D_800F9228[] = {
    { 1, 0, 1, 0x0F },
    { 1, 0, 1, 0x10 },
    { 2, 16, 1, 0x11 },
    { 2, 16, 1, 0x12 },
    { 2, 17, 1, 0x11 },
    { 2, 17, 1, 0x12 },
    { 2, 17, 1, 0x11 },
    { 2, 17, 1, 0x12 },
    { 3, 1, 1, 0x10 },
    { 5, 1, 1, 0x0F },
    { 1, 0, 0, 0x0F },
};

union AnimationStep D_800F9254[] = {
    { 1, 0, 1, 0x0F },
    { 1, 0, 1, 0x10 },
    { 2, 17, 1, 0x11 },
    { 2, 17, -1, 0x12 },
};

union AnimationStep D_800F9264[] = {
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x19 },
    { 1, 0, 1, 0x1A },
    { 1, 0, 1, 0x1B },
    { 1, 0, 1, 0x1C },
    { 1, 0, 1, 0x1D },
    { 1, 0, 1, 0x1E },
    { 1, 32, 1, 0x1F },
    { 1, 48, 1, 0x20 },
    { 1, 48, 1, 0x21 },
    { 1, 48, 1, 0x20 },
    { 1, 48, 1, 0x21 },
    { 1, 48, 1, 0x20 },
    { 1, 48, 1, 0x21 },
    { 1, 48, 1, 0x20 },
    { 1, 48, 1, 0x21 },
    { 1, 48, 1, 0x20 },
    { 10, 48, 1, 0x21 },
    { 5, 0, 1, 0x12 },
    { 5, 0, 0, 0x0F },
};

union AnimationStep D_800F92B4[] = {
    { 1, 0, 1, 0x09 },
    { 1, 0, 1, 0x22 },
    { 1, 0, 1, 0x23 },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x25 },
    { 1, 0, 1, 0x26 },
    { 1, 64, 1, 0x27 },
    { 1, 80, 1, 0x28 },
    { 1, 80, 1, 0x29 },
    { 1, 80, 1, 0x28 },
    { 1, 80, 1, 0x29 },
    { 1, 80, 1, 0x28 },
    { 1, 80, 1, 0x29 },
    { 1, 80, 1, 0x28 },
    { 1, 80, 1, 0x29 },
    { 1, 80, 1, 0x28 },
    { 6, 80, 1, 0x29 },
    { 6, 0, 1, 0x2A },
    { 6, 0, 1, 0x2B },
    { 1, 0, 0, 0x2B },
};

union AnimationStep D_800F9304[] = {
    { 5, 0, 1, 0x16 },
    { 4, 0, 1, 0x17 },
};

union AnimationStep D_800F930C[] = {
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x19 },
    { 1, 0, -2, 0x1A },
};

#if defined(MMX4_PC) && !defined(MMX4_WIN32)
static struct {
    union AnimationStep D_800F9304[2];
    union AnimationStep D_800F930C[3];
} ride_armor_land_run = {
    {
        { 5, 0, 1, 0x16 },
        { 4, 0, 1, 0x17 },
    },
    {
        { 1, 0, 1, 0x18 },
        { 1, 0, 1, 0x19 },
        { 1, 0, -2, 0x1A },
    },
};
#define D_800F9304 ride_armor_land_run.D_800F9304
#define D_800F930C ride_armor_land_run.D_800F930C
#endif

union AnimationStep D_800F9318[] = {
    { 1, 0, 1, 0x10 },
    { 1, 0, 1, 0x12 },
    { 1, 0, 0, 0x11 },
};

union AnimationStep D_800F9324[] = {
    { 1, 96, 1, 0x13 },
    { 1, 96, 1, 0x14 },
    { 1, 96, -2, 0x15 },
};

union AnimationStep D_800F9330[] = {
    { 5, 0, 1, 0x11 },
    { 2, 0, 1, 0x12 },
    { 2, 0, 0, 0x0F },
};

union AnimationStep D_800F933C[] = {
    { 2, 0, 0, 0x31 },
};

union AnimationStep D_800F9340[] = {
    { 10, 0, 1, 0x2F },
    { 10, 0, 1, 0x30 },
    { 10, 0, 1, 0x2E },
    { 10, 0, 1, 0x2D },
    { 5, 0, 1, 0x00 },
    { 6, 1, 1, 0x2C },
    { 8, 0, 0, 0x00 },
};

union AnimationStep D_800F935C[] = {
    { 5, 0, 1, 0x2C },
    { 5, 0, 1, 0x2D },
    { 5, 0, 1, 0x2E },
    { 5, 0, 1, 0x30 },
    { 3, 0, 1, 0x31 },
    { 3, 0, 1, 0x32 },
    { 8, 0, 0, 0x31 },
};

union AnimationStep D_800F9378[] = {
    { 5, 0, 1, 0x33 },
    { 5, 0, 1, 0x34 },
    { 5, 0, 1, 0x35 },
    { 5, 0, 1, 0x36 },
    { 5, 0, 1, 0x37 },
    { 5, 0, 1, 0x38 },
    { 5, 0, 1, 0x39 },
    { 5, 0, 1, 0x3A },
    { 5, 0, 1, 0x3B },
    { 1, 0, -9, 0x3B },
};

union AnimationStep D_800F93A0[] = {
    { 2, 0, 1, 0x3C },
    { 2, 0, 1, 0x3D },
    { 2, 0, 1, 0x3E },
    { 2, 0, 1, 0x3F },
    { 2, 0, 1, 0x40 },
    { 2, 0, 1, 0x41 },
    { 1, 0, 1, 0x3C },
    { 1, 0, 1, 0x3D },
    { 1, 0, 1, 0x3E },
    { 1, 0, 1, 0x3F },
    { 1, 0, 1, 0x40 },
    { 1, 0, 1, 0x41 },
    { 1, 0, -12, 0x41 },
};

union AnimationStep D_800F93D4[] = {
    { 1, 0, 1, 0x49 },
    { 2, 0, 1, 0x4A },
    { 1, 0, 1, 0x49 },
    { 2, 0, 1, 0x4A },
    { 1, 0, 1, 0x49 },
    { 2, 0, 1, 0x4A },
    { 1, 0, 1, 0x49 },
    { 1, 0, 1, 0x4A },
    { 1, 0, -8, 0x4A },
};

union AnimationStep D_800F93F8[] = {
    { 1, 0, 1, 0x4B },
    { 2, 0, 1, 0x4C },
    { 1, 0, 1, 0x4B },
    { 1, 0, 1, 0x4C },
    { 1, 0, -4, 0x4C },
};

union AnimationStep D_800F940C[] = {
    { 2, 0, 0, 0x42 },
};

union AnimationStep D_800F9410[] = {
    { 2, 0, 0, 0x43 },
};

union AnimationStep D_800F9414[] = {
    { 2, 0, 0, 0x44 },
};

union AnimationStep D_800F9418[] = {
    { 2, 0, 0, 0x45 },
};

union AnimationStep D_800F941C[] = {
    { 2, 0, 0, 0x46 },
};

union AnimationStep D_800F9420[] = {
    { 2, 0, 0, 0x47 },
};

union AnimationStep D_800F9424[] = {
    { 2, 0, 0, 0x48 },
};

union AnimationStep* D_800F9428[31] = {
    D_800F91D0,
    D_800F91E0,
    D_800F9200,
    D_800F9204,
    D_800F9208,
    D_800F9218,
    D_800F9218,
    D_800F9224,
    D_800F9228,
    D_800F9254,
    D_800F9264,
    D_800F92B4,
    D_800F9304,
    D_800F930C,
    D_800F9318,
    D_800F9324,
    D_800F9330,
    D_800F933C,
    D_800F9340,
    D_800F935C,
    D_800F9378,
    D_800F93A0,
    D_800F93D4,
    D_800F93F8,
    D_800F940C,
    D_800F9410,
    D_800F9414,
    D_800F9418,
    D_800F941C,
    D_800F9420,
    D_800F9424,
};

union AnimationStep D_800F94A4[] = {
    { 5, 0, 1, 0x25 },
    { 8, 1, 1, 0x26 },
    { 6, 1, 1, 0x25 },
    { 1, 1, 0, 0x25 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep D_800F94B8[] = {
    { 8, 0, 1, 0x0F },
    { 12, 1, 1, 0x0F },
    { 1, 1, 0, 0x0F },
};

union AnimationStep D_800F94C4[] = {
    { 2, 0, 1, 0x0F },
    { 3, 0, 1, 0x24 },
    { 1, 0, 1, 0x13 },
    { 1, 0, 1, 0x21 },
    { 1, 0, 1, 0x14 },
    { 1, 0, 1, 0x22 },
    { 1, 0, 1, 0x23 },
    { 19, 0, 1, 0x24 },
    { 1, 0, 0, 0x24 },
};

union AnimationStep D_800F94E8[] = {
    { 1, 0, 1, 0x19 },
    { 1, 0, 1, 0x1A },
    { 1, 0, 1, 0x1B },
    { 1, 0, 1, 0x1C },
    { 1, 0, 1, 0x19 },
    { 1, 0, 1, 0x1A },
    { 1, 0, 1, 0x1B },
    { 1, 0, 1, 0x1C },
    { 1, 1, 1, 0x19 },
    { 1, 1, 1, 0x1A },
    { 1, 1, 1, 0x1B },
    { 1, 1, 1, 0x1C },
    { 1, 1, 1, 0x19 },
    { 1, 1, 1, 0x1A },
    { 1, 1, 1, 0x1B },
    { 1, 1, 1, 0x1C },
    { 1, 1, -4, 0x1C },
};

union AnimationStep D_800F952C[] = {
    { 2, 0, 1, 0x10 },
    { 3, 0, 1, 0x20 },
    { 1, 0, 1, 0x11 },
    { 1, 0, 1, 0x1D },
    { 1, 0, 1, 0x12 },
    { 1, 0, 1, 0x1E },
    { 1, 0, 1, 0x1F },
    { 19, 0, 1, 0x20 },
    { 1, 0, 0, 0x20 },
};

union AnimationStep D_800F9550[] = {
    { 1, 1, 1, 0x15 },
    { 1, 1, 1, 0x16 },
    { 1, 1, 1, 0x17 },
    { 1, 1, -3, 0x18 },
};

union AnimationStep D_800F9560[] = {
    { 1, 0, 0, 0x2C },
};

union AnimationStep D_800F9564[] = {
    { 10, 0, 1, 0x2A },
    { 10, 0, 1, 0x2B },
    { 10, 0, 1, 0x29 },
    { 10, 0, 1, 0x28 },
    { 5, 0, 1, 0x00 },
    { 6, 1, 1, 0x27 },
    { 5, 0, 1, 0x00 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep D_800F9584[] = {
    { 5, 0, 1, 0x27 },
    { 5, 0, 1, 0x28 },
    { 5, 0, 1, 0x29 },
    { 5, 0, 1, 0x2B },
    { 3, 0, 1, 0x2C },
    { 3, 0, 1, 0x2D },
    { 8, 0, 0, 0x2C },
};

union AnimationStep D_800F95A0[] = {
    { 5, 0, 1, 0x2E },
    { 5, 0, 1, 0x2F },
    { 5, 0, 1, 0x30 },
    { 5, 0, 1, 0x31 },
    { 5, 0, 1, 0x32 },
    { 5, 0, 1, 0x33 },
    { 5, 0, 1, 0x34 },
    { 5, 0, 1, 0x35 },
    { 5, 0, 1, 0x36 },
    { 1, 0, -9, 0x36 },
};

union AnimationStep D_800F95C8[] = {
    { 2, 0, 1, 0x37 },
    { 2, 0, 1, 0x38 },
    { 2, 0, 1, 0x39 },
    { 2, 0, 1, 0x3A },
    { 2, 0, 1, 0x3B },
    { 2, 0, 1, 0x3C },
    { 1, 0, 1, 0x37 },
    { 1, 0, 1, 0x38 },
    { 1, 0, 1, 0x39 },
    { 1, 0, 1, 0x3A },
    { 1, 0, 1, 0x3B },
    { 1, 0, 1, 0x3C },
    { 1, 0, -12, 0x3C },
};

union AnimationStep D_800F95FC[] = {
    { 2, 0, 1, 0x44 },
    { 2, 0, 1, 0x46 },
    { 2, 0, 1, 0x45 },
    { 2, 0, -3, 0x47 },
};

union AnimationStep D_800F960C[] = {
    { 2, 0, 1, 0x48 },
    { 2, 0, 1, 0x49 },
    { 2, 0, 1, 0x4A },
    { 2, 0, -3, 0x4B },
};

union AnimationStep D_800F961C[] = {
    { 2, 0, 0, 0x4C },
};

union AnimationStep D_800F9620[] = {
    { 2, 0, 0, 0x4D },
};

union AnimationStep D_800F9624[] = {
    { 2, 0, 0, 0x4E },
};

union AnimationStep D_800F9628[] = {
    { 2, 0, 0, 0x4F },
};

union AnimationStep D_800F962C[] = {
    { 2, 0, 1, 0x50 },
    { 2, 0, 1, 0x51 },
    { 2, 0, 1, 0x52 },
    { 2, 0, -3, 0x53 },
};

union AnimationStep D_800F963C[] = {
    { 5, 0, 0, 0x25 },
};

union AnimationStep D_800F9640[] = {
    { 2, 0, 0, 0x3D },
};

union AnimationStep D_800F9644[] = {
    { 2, 0, 0, 0x3E },
};

union AnimationStep D_800F9648[] = {
    { 2, 0, 0, 0x3F },
};

union AnimationStep D_800F964C[] = {
    { 2, 0, 0, 0x40 },
};

union AnimationStep D_800F9650[] = {
    { 2, 0, 0, 0x41 },
};

union AnimationStep D_800F9654[] = {
    { 2, 0, 0, 0x42 },
};

union AnimationStep D_800F9658[] = {
    { 2, 0, 0, 0x43 },
};

union AnimationStep* D_800F965C[38] = {
    D_800F91D0,
    D_800F91E0,
    D_800F9200,
    D_800F9204,
    D_800F9208,
    D_800F9218,
    D_800F9218,
    D_800F9224,
    D_800F94A4,
    D_800F94B8,
    D_800F94C4,
    D_800F94E8,
    D_800F952C,
    D_800F9550,
    D_800F963C,
    D_800F91D0,
    D_800F91D0,
    D_800F9560,
    D_800F9564,
    D_800F9584,
    D_800F95A0,
    D_800F95C8,
    D_800F93D4,
    D_800F93F8,
    D_800F9640,
    D_800F9644,
    D_800F9648,
    D_800F964C,
    D_800F9650,
    D_800F9654,
    D_800F9658,
    D_800F95FC,
    D_800F960C,
    D_800F961C,
    D_800F9620,
    D_800F9624,
    D_800F9628,
    D_800F962C,
};
