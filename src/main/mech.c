// RideArmorObj, D_800F2AD4[1]
// 8003D3F8..80040608
#include "common.h"
#include "func_tables.h"

void func_8003D3F8(struct RideArmorObj* arg0)
{
    u8 previous_input;

    if (g_Player.unkC0 == 0) {
        arg0->collision_flags = g_Player.input.buttons.held;
        arg0->unk8A = g_Player.pressed_input;
    } else {
        arg0->collision_flags = 0;
        arg0->unk8A = 0;
    }
    if (g_Player.unkBC != 0) {
        func_8002B3C0(BASE_OBJECT(arg0));
        return;
    }

    arg0->unk18 = arg0->x_pos;
    arg0->unk1C = arg0->y_pos;

    previous_input = arg0->unk71;
    arg0->unk71 = 0;
    arg0->input_flags = arg0->unk70 | previous_input;
    D_800F912C[arg0->state](arg0);
    arg0->unk5C &= ~0x80;
}

INCLUDE_ASM("main/nonmatchings/mech", func_8003D4C8);

void func_8003D638(struct VisualObj* arg0, u8 arg1)
{
    struct VisualObj* obj;
    u8 active;
    u8 unk16;
    u8 unk15;

    obj = find_free_visual_obj();
    if (obj == NULL) {
        return;
    }
    active = arg0->active;
    obj->id = 0xC;
    obj->unk2 = arg1;
    obj->active = active;
    obj->x_pos.val = arg0->x_pos.val;
    obj->y_pos.val = arg0->y_pos.val;
    obj->animation_table = arg0->animation_table;
    obj->unk40 = arg0->unk40;
    obj->unk3C = arg0->unk3C;
    obj->unk42 = arg0->unk42 & 0x7FFF;
    unk16 = arg0->unk16;
    obj->unk16 = unk16;
    unk15 = arg0->unk15;
    obj->unk50 = (struct PlayerObj*)arg0;
    obj->unk15 = unk15;
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
    if (!(D_80141BD8.unk0 & 3) && (get_random() & 1)) {
        get_random();
    }
}

INCLUDE_ASM("main/nonmatchings/mech", func_8003D7E4);

INCLUDE_ASM("main/nonmatchings/mech", func_8003D8A8);

INCLUDE_ASM("main/nonmatchings/mech", func_8003D9E0);

void func_8003DC1C(struct PlayerObj* arg0, s8 arg1)
{
    if (arg0->unk8D == 0) {
        g_Player.unkD4 = arg1;
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
        arg0->unk15 = 0x40;
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
    } else if (g_Player.unk5C == -0x80) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("main/nonmatchings/mech", func_8003DCD8);

void func_8003DD14(struct MainObj* arg0)
{
    arg0->x_pos.val += arg0->unk20;
}

void func_8003DD2C(struct MainObj* arg0)
{
    if (arg0->unk15 != 0) {
        arg0->unk20 = FIXED(1.375);
    } else {
        arg0->unk20 = FIXED(-1.375);
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

INCLUDE_ASM("main/nonmatchings/mech", func_8003DE84);

void func_8003DF9C(struct PlayerObj* arg0)
{
    struct BaseObj* base;
    s8 effect;

    if ((arg0->unk8D == 0) && !(arg0->unk97 & 2) && (arg0->unk8A.packed & 0x100) && (func_8003DE08(MAIN_OBJECT(arg0)) == 0)) {
        base = BASE_OBJECT(arg0);
        if (arg0->unk67 == 0) {
            effect = 7;
        } else {
            effect = 0xF;
            if (arg0->input.bytes.held_high != 0) {
                return;
            }
        }

        func_8003DC44(base, effect);
        arg0->unk97 |= 8;
    }
}

s32 func_8003E048(struct PlayerObj* arg0)
{
    s32 mask;
    s32 flags;
    s32 result;

    if (!(arg0->unk97 & 8)) {
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
    result = mask & flags;
    if (result == 0) {
        result = flags & 0x100;
    }
    return result;
}

s32 func_8003E0B0(struct PlayerObj* arg0)
{
    s32 mask;

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
        func_80015D60(self, 0x11);
    } else if (!(self->input_flags & 8)) {
        func_8003DC44(BASE_OBJECT(self), 0xC);
    } else if (g_Player.unkC0 == 0 && engine_obj.unkF == 0
        && (g_Player.unk2 == 0 || g_Player.unk8E == 0) && g_Player.unk7A == 0
        && g_Player.unkE0 == 0 && !(self->unk94.halves[1] & 0x8200)
        && func_8002C160(COLLISION_OBJECT(&g_Player), COLLISION_OBJECT(self))
        && engine_obj.unkF == 0 && g_Player.unk5C > 0 && g_Player.unkA4 == 0
        && g_Player.unk79 == 0) {
        func_8003DC44(BASE_OBJECT(self), 0xA);
        func_80015D60(self, 0x12);
        self->unk94.bytes.unk97 |= 0x40;
        g_Player.unkC5 = 1;
    }
}

INCLUDE_ASM("main/nonmatchings/mech", func_8003E274);

void func_8003E368(struct RideArmorObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->unk98.packed = 0x160;
        func_80015D60(self, 0);
        func_8003DC1C(PLAYER_OBJECT(self), 0x29);
        self->pad87 = 0;
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
    func_80015DC8(ANIMATED_OBJECT(self));
}

INCLUDE_ASM("main/nonmatchings/mech", func_8003E488);

INCLUDE_ASM("main/nonmatchings/mech", func_8003E5F8);

INCLUDE_ASM("main/nonmatchings/mech", func_8003E750);

INCLUDE_ASM("main/nonmatchings/mech", func_8003E8A0);

INCLUDE_ASM("main/nonmatchings/mech", func_8003EA08);

INCLUDE_ASM("main/nonmatchings/mech", func_8003EB4C);

void func_8003ED00(struct RideArmorObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->unk98.packed = 0x160;
        func_80015D60(self, 7);
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
    func_80015DC8(ANIMATED_OBJECT(self));
}

void func_8003EDF0(struct RideArmorObj* self)
{
    s8 timer;
    u8 input;

    func_8003D7A0();
    if (self->unk6 == 0) {
        self->unk6 = 1;
        func_8003D7E4(self, 1, 1);
        func_80015D60(self, 9);
        func_8003DC1C(PLAYER_OBJECT(self), 0x37);
        func_8001540C(5, 0, 0);
    }

    input = self->input_flags;
    timer = self->unk90.byte - 1;
    self->unk90.byte = timer;
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

    func_80015DC8(ANIMATED_OBJECT(self));
}

INCLUDE_ASM("main/nonmatchings/mech", func_8003EEF8);

INCLUDE_ASM("main/nonmatchings/mech", func_8003F068);

void func_8003F204(struct RideArmorObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        func_8003DC44(BASE_OBJECT(arg0), 1);
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
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
                func_80015D60(arg0, 0x10);
                func_8003DC1C(PLAYER_OBJECT(arg0), 0x29);
            }
        }
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
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
                    func_80015D60(self, 0xF);
                    func_8003DC1C(PLAYER_OBJECT(self), 0x36);
                    if (self->unk2 == 0) {
                        func_8001540C(5, 5, 0);
                    } else {
                        func_8001540C(5, 6, 0);
                    }
                }
            }
        }
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

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
                    func_8001540C(5, 6, 0);
                }
            }
        }
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

void func_8003F570(struct RideArmorObj* arg0)
{
    if (arg0->unk2 == 0) {
        arg0->unk6 = 1;
        func_80015D60(arg0, 0xC);
        func_8003DC1C(PLAYER_OBJECT(arg0), 0x34);
        func_8003F31C(arg0);
        func_8001540C(5, 7, NULL);
        return;
    }

    arg0->unk6 = 4;
    func_8003D6EC(ANIMATED_OBJECT(arg0), 0x10);
    func_80015D60(arg0, 0xE);
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
        func_80015D60(arg0, 8);
        func_8003DC1C(PLAYER_OBJECT(arg0), 0x3F);
        func_8001540C(5, 7, 0);
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->pad87 = 0;
        func_8003DC44(BASE_OBJECT(arg0), 1);
        return;
    }
    if (arg0->animation_step.fields.event != 0 && func_8003DCD8(arg0) != 0 && arg0->unk86 < 3U) {
        func_8003DC44(BASE_OBJECT(arg0), 3);
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mech", func_8003F76C);

INCLUDE_ASM("main/nonmatchings/mech", func_8003F908);

INCLUDE_ASM("main/nonmatchings/mech", func_8003FA58);

void func_8003FBD8(struct RideArmorObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->unk7D = 1;
        self->unk98.packed = 0x160;
        func_80015D60(self, 0xD);
        func_8003DC1C(PLAYER_OBJECT(self), 0x3C);
        self->pad87 = 0;
        func_8001540C(5, 5, 0);
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
    func_80015DC8(ANIMATED_OBJECT(self));
}

INCLUDE_ASM("main/nonmatchings/mech", func_8003FD08);

void func_8003FF14(struct MainObj* arg0)
{
    arg0->unk20 -= arg0->unk28;
    arg0->unk24 -= arg0->unk2C;
    arg0->x_pos.val += arg0->unk20;
    arg0->y_pos.val += arg0->unk24;
}

void func_8003FF58(struct MainObj* arg0)
{
    arg0->unk20 += arg0->unk28;
    arg0->unk24 -= arg0->unk2C;
    arg0->x_pos.val += arg0->unk20;
    arg0->y_pos.val += arg0->unk24;
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
            velocity = self->launch_speed << 8;
        } else {
            velocity = -(self->launch_speed << 8);
        }
        self->x_vel.val = velocity;
        self->unk28 = 0x5800;
        self->y_vel.val = 0;
        self->unk2C = 0x5800;
        break;
    case 2:
        func_8002B694(ANIMATED_OBJECT(self));
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
        *(u8*)&self->unk8C = 0xFF;
        g_Player.unkC5 = 0;
        self->unk97 ^= 0x40;
        func_80035EA4(&g_Player);
        self->unk90 = 0x1E;
        self->unk97 |= 4;
        func_800C813C(7, D_800F9118, self);
        return;
    case 2:
        temp_v0 = (u8)self->unk90 - 1;
        self->unk90 = temp_v0;
        if (temp_v0 == 0) {
            self->state = 2;
            self->on_screen = 0;
            func_800AF808(BASE_OBJECT(self));
            func_80015930(5, 8);
            return;
        }
        func_800AF878(BASE_OBJECT(self), 0, 0x1F, 0x1F);
        return;
    default:
        if ((*(u8*)&self->unk8C == 0) && !(*(u8*)&self->unk97 & 0x80)) {
            self->unk85 = 0;
            self->unk42 &= 0x7FFF;
        }
        return;
    }
}

void func_800401F8(struct PlayerObj* arg0)
{
    u8 temp_v0;

    if (arg0->unk97 & 0x40) {
        temp_v0 = arg0->unk8C;
        if (temp_v0 != 0) {
            if ((temp_v0 & 3) == 0) {
                arg0->unk42 |= 0x8000;
            } else {
                arg0->unk42 &= 0x7FFF;
            }
        }
    }
}

INCLUDE_ASM("main/nonmatchings/mech", func_80040248);

void func_800402C4(struct PlayerObj* self)
{
    s16 x_limit;
    s16 y_limit;
    if (self->unk97 & 0x40) {
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
        if (self->unk97 & 0x40) {
            g_Player.unk5C = -0x80;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/mech", func_800403DC);

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

u8 D_800F9118[8] = { 24, 25, 26, 27, 28, 29, 30, 0 };

struct Unk_unk68 D_800F9120 = { 0, -1, 15, 33 };

struct Unk_unk68 D_800F9124 = { 0, 22, 15, 10 };

struct Unk_unk68 D_800F9128 = { -8, -14, 16, 46 };

void (*D_800F912C[3])() = {
    func_8003D4C8,
    func_800403DC,
    func_800405D4,
};

void (*D_800F9138[6])() = {
    func_8003F570,
    func_8003F31C,
    func_8003F244,
    func_8003F204,
    func_8003F44C,
    func_8003F618,
};

void (*D_800F9150[14])() = {
    func_8003E0D0,
    func_8003E368,
    func_8003E488,
    func_8003E5F8,
    func_8003E750,
    func_8003E8A0,
    func_8003EA08,
    func_8003EB4C,
    func_8003ED00,
    func_8003EDF0,
    func_8003E274,
    func_8003EEF8,
    func_8003F068,
    func_8003F648,
};

void (*D_800F9188[18])() = {
    func_8003E0D0,
    func_8003E368,
    func_8003E488,
    func_8003F698,
    func_8003E750,
    func_8003E8A0,
    func_8003F76C,
    func_8003EB4C,
    func_8003ED00,
    func_8003F698,
    func_8003E274,
    func_8003EEF8,
    func_8003F068,
    func_8003F648,
    func_8003FBD8,
    func_8003F908,
    func_8003FA58,
    func_8003FD08,
};

union AnimationStep D_800F91D0[] = {
    { 0x00010064 },
    { 0x0B010007 },
    { 0x0C010132 },
    { 0x0BFD0008 },
};

union AnimationStep D_800F91E0[] = {
    { 0x01010006 },
    { 0x02010006 },
    { 0x03010006 },
    { 0x0401010A },
    { 0x05010006 },
    { 0x06010006 },
    { 0x07010006 },
    { 0x08F9010A },
};

union AnimationStep D_800F9200[] = {
    { 0x09000008 },
};

union AnimationStep D_800F9204[] = {
    { 0x0A000008 },
};

union AnimationStep D_800F9208[] = {
    { 0x0B010002 },
    { 0x0C010008 },
    { 0x0B010007 },
    { 0x00000008 },
};

union AnimationStep D_800F9218[] = {
    { 0x0D010004 },
    { 0x0E010008 },
    { 0x0D000008 },
};

union AnimationStep D_800F9224[] = {
    { 0x0D000008 },
};

union AnimationStep D_800F9228[] = {
    { 0x0F010001 },
    { 0x10010001 },
    { 0x11011002 },
    { 0x12011002 },
    { 0x11011102 },
    { 0x12011102 },
    { 0x11011102 },
    { 0x12011102 },
    { 0x10010103 },
    { 0x0F010105 },
    { 0x0F000001 },
};

union AnimationStep D_800F9254[] = {
    { 0x0F010001 },
    { 0x10010001 },
    { 0x11011102 },
    { 0x12FF1102 },
};

union AnimationStep D_800F9264[] = {
    { 0x18010001 },
    { 0x19010001 },
    { 0x1A010001 },
    { 0x1B010001 },
    { 0x1C010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1F012001 },
    { 0x20013001 },
    { 0x21013001 },
    { 0x20013001 },
    { 0x21013001 },
    { 0x20013001 },
    { 0x21013001 },
    { 0x20013001 },
    { 0x21013001 },
    { 0x20013001 },
    { 0x2101300A },
    { 0x12010005 },
    { 0x0F000005 },
};

union AnimationStep D_800F92B4[] = {
    { 0x09010001 },
    { 0x22010001 },
    { 0x23010001 },
    { 0x24010001 },
    { 0x25010001 },
    { 0x26010001 },
    { 0x27014001 },
    { 0x28015001 },
    { 0x29015001 },
    { 0x28015001 },
    { 0x29015001 },
    { 0x28015001 },
    { 0x29015001 },
    { 0x28015001 },
    { 0x29015001 },
    { 0x28015001 },
    { 0x29015006 },
    { 0x2A010006 },
    { 0x2B010006 },
    { 0x2B000001 },
};

union AnimationStep D_800F9304[] = {
    { 0x16010005 },
    { 0x17010004 },
};

union AnimationStep D_800F930C[] = {
    { 0x18010001 },
    { 0x19010001 },
    { 0x1AFE0001 },
};

union AnimationStep D_800F9318[] = {
    { 0x10010001 },
    { 0x12010001 },
    { 0x11000001 },
};

union AnimationStep D_800F9324[] = {
    { 0x13016001 },
    { 0x14016001 },
    { 0x15FE6001 },
};

union AnimationStep D_800F9330[] = {
    { 0x11010005 },
    { 0x12010002 },
    { 0x0F000002 },
};

union AnimationStep D_800F933C[] = {
    { 0x31000002 },
};

union AnimationStep D_800F9340[] = {
    { 0x2F01000A },
    { 0x3001000A },
    { 0x2E01000A },
    { 0x2D01000A },
    { 0x00010005 },
    { 0x2C010106 },
    { 0x00000008 },
};

union AnimationStep D_800F935C[] = {
    { 0x2C010005 },
    { 0x2D010005 },
    { 0x2E010005 },
    { 0x30010005 },
    { 0x31010003 },
    { 0x32010003 },
    { 0x31000008 },
};

union AnimationStep D_800F9378[] = {
    { 0x33010005 },
    { 0x34010005 },
    { 0x35010005 },
    { 0x36010005 },
    { 0x37010005 },
    { 0x38010005 },
    { 0x39010005 },
    { 0x3A010005 },
    { 0x3B010005 },
    { 0x3BF70001 },
};

union AnimationStep D_800F93A0[] = {
    { 0x3C010002 },
    { 0x3D010002 },
    { 0x3E010002 },
    { 0x3F010002 },
    { 0x40010002 },
    { 0x41010002 },
    { 0x3C010001 },
    { 0x3D010001 },
    { 0x3E010001 },
    { 0x3F010001 },
    { 0x40010001 },
    { 0x41010001 },
    { 0x41F40001 },
};

union AnimationStep D_800F93D4[] = {
    { 0x49010001 },
    { 0x4A010002 },
    { 0x49010001 },
    { 0x4A010002 },
    { 0x49010001 },
    { 0x4A010002 },
    { 0x49010001 },
    { 0x4A010001 },
    { 0x4AF80001 },
};

union AnimationStep D_800F93F8[] = {
    { 0x4B010001 },
    { 0x4C010002 },
    { 0x4B010001 },
    { 0x4C010001 },
    { 0x4CFC0001 },
};

union AnimationStep D_800F940C[] = {
    { 0x42000002 },
};

union AnimationStep D_800F9410[] = {
    { 0x43000002 },
};

union AnimationStep D_800F9414[] = {
    { 0x44000002 },
};

union AnimationStep D_800F9418[] = {
    { 0x45000002 },
};

union AnimationStep D_800F941C[] = {
    { 0x46000002 },
};

union AnimationStep D_800F9420[] = {
    { 0x47000002 },
};

union AnimationStep D_800F9424[] = {
    { 0x48000002 },
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
    { 0x25010005 },
    { 0x26010108 },
    { 0x25010106 },
    { 0x25000101 },
    { 0x00000001 },
};

union AnimationStep D_800F94B8[] = {
    { 0x0F010008 },
    { 0x0F01010C },
    { 0x0F000101 },
};

union AnimationStep D_800F94C4[] = {
    { 0x0F010002 },
    { 0x24010003 },
    { 0x13010001 },
    { 0x21010001 },
    { 0x14010001 },
    { 0x22010001 },
    { 0x23010001 },
    { 0x24010013 },
    { 0x24000001 },
};

union AnimationStep D_800F94E8[] = {
    { 0x19010001 },
    { 0x1A010001 },
    { 0x1B010001 },
    { 0x1C010001 },
    { 0x19010001 },
    { 0x1A010001 },
    { 0x1B010001 },
    { 0x1C010001 },
    { 0x19010101 },
    { 0x1A010101 },
    { 0x1B010101 },
    { 0x1C010101 },
    { 0x19010101 },
    { 0x1A010101 },
    { 0x1B010101 },
    { 0x1C010101 },
    { 0x1CFC0101 },
};

union AnimationStep D_800F952C[] = {
    { 0x10010002 },
    { 0x20010003 },
    { 0x11010001 },
    { 0x1D010001 },
    { 0x12010001 },
    { 0x1E010001 },
    { 0x1F010001 },
    { 0x20010013 },
    { 0x20000001 },
};

union AnimationStep D_800F9550[] = {
    { 0x15010101 },
    { 0x16010101 },
    { 0x17010101 },
    { 0x18FD0101 },
};

union AnimationStep D_800F9560[] = {
    { 0x2C000001 },
};

union AnimationStep D_800F9564[] = {
    { 0x2A01000A },
    { 0x2B01000A },
    { 0x2901000A },
    { 0x2801000A },
    { 0x00010005 },
    { 0x27010106 },
    { 0x00010005 },
    { 0x00000001 },
};

union AnimationStep D_800F9584[] = {
    { 0x27010005 },
    { 0x28010005 },
    { 0x29010005 },
    { 0x2B010005 },
    { 0x2C010003 },
    { 0x2D010003 },
    { 0x2C000008 },
};

union AnimationStep D_800F95A0[] = {
    { 0x2E010005 },
    { 0x2F010005 },
    { 0x30010005 },
    { 0x31010005 },
    { 0x32010005 },
    { 0x33010005 },
    { 0x34010005 },
    { 0x35010005 },
    { 0x36010005 },
    { 0x36F70001 },
};

union AnimationStep D_800F95C8[] = {
    { 0x37010002 },
    { 0x38010002 },
    { 0x39010002 },
    { 0x3A010002 },
    { 0x3B010002 },
    { 0x3C010002 },
    { 0x37010001 },
    { 0x38010001 },
    { 0x39010001 },
    { 0x3A010001 },
    { 0x3B010001 },
    { 0x3C010001 },
    { 0x3CF40001 },
};

union AnimationStep D_800F95FC[] = {
    { 0x44010002 },
    { 0x46010002 },
    { 0x45010002 },
    { 0x47FD0002 },
};

union AnimationStep D_800F960C[] = {
    { 0x48010002 },
    { 0x49010002 },
    { 0x4A010002 },
    { 0x4BFD0002 },
};

union AnimationStep D_800F961C[] = {
    { 0x4C000002 },
};

union AnimationStep D_800F9620[] = {
    { 0x4D000002 },
};

union AnimationStep D_800F9624[] = {
    { 0x4E000002 },
};

union AnimationStep D_800F9628[] = {
    { 0x4F000002 },
};

union AnimationStep D_800F962C[] = {
    { 0x50010002 },
    { 0x51010002 },
    { 0x52010002 },
    { 0x53FD0002 },
};

union AnimationStep D_800F963C[] = {
    { 0x25000005 },
};

union AnimationStep D_800F9640[] = {
    { 0x3D000002 },
};

union AnimationStep D_800F9644[] = {
    { 0x3E000002 },
};

union AnimationStep D_800F9648[] = {
    { 0x3F000002 },
};

union AnimationStep D_800F964C[] = {
    { 0x40000002 },
};

union AnimationStep D_800F9650[] = {
    { 0x41000002 },
};

union AnimationStep D_800F9654[] = {
    { 0x42000002 },
};

union AnimationStep D_800F9658[] = {
    { 0x43000002 },
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
