#include "common.h"

void func_800312B4(struct PlayerObj* arg0)
{
    arg0->unkC3 = arg0->unkC0 | engine_obj.unkF;
    arg0->unkC3 |= arg0->unkC4;
    arg0->unk88.bytes.collision_flags = arg0->unk70 | arg0->unk71;
    arg0->unk8F = 0;
    arg0->unk90 = 0;
    arg0->unkBF = 0;

    if (engine_obj.unk10 == 0) {
        func_80033BC8(arg0);
        if (arg0->unk5C == 0) {
            return;
        }

        if (arg0->unk92) {
            arg0->unk92--;
        }

        if (arg0->unk91 != 0) {
            arg0->unk91--;
            if (!arg0->unk91) {
                arg0->unk90 = 1;
                arg0->unk8E = 0;
            }
        }

        if (arg0->unkD7 > 0) {
            arg0->unkD7--;
            if (!arg0->unkD7) {
                arg0->unkD7 = -1;
            }
        }

        func_800338CC(arg0);
        func_80033974(arg0);
        func_80033750(arg0);
        func_800335E4(arg0);
        func_80036EE8(arg0);

        D_800F8990[arg0->unk5](arg0);
        arg0->unk71 = 0;
        arg0->unk4A = 0;
    }
    func_80037FF0(arg0);
    func_800360B8(arg0);
    func_80035DE4(arg0);
}

void func_80031410(struct PlayerObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk6 == 0) {
        if (arg0->unkBE != 0) {
            if (--arg0->unkBE == 0) {
                func_80035EA4(arg0);
            }
            func_8002B718((struct MovingObj*)arg0);
            return;
        }
        if (arg0->unk88.bytes.collision_flags & 8) {
            func_800350A4(arg0, 2);
            arg0->unk67 = 0;
            background_objects[0].unk44 = 1;
            background_objects[1].unk44 = 1;
            background_objects[2].unk44 = 1;
            arg0->unk6++;
            return;
        }
        func_8002B718((struct MovingObj*)arg0);
        func_80036B88(arg0);
        return;
    }
    if (arg0->animation_step.fields.event != 0) {
        arg0->animation_step.fields.event = 0;
        arg0->unkA7 = engine_obj.unk47;
        arg0->unkB8 = engine_obj.unk48;
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        engine_obj.unk1C = 0;
        func_800343A4(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/21AB4", func_80031540);

void func_800315E0(struct PlayerObj* arg0)
{
    if (func_80034100(arg0) == 0 && func_80033EA4(arg0) == 0 && func_80037290(arg0) == 0 && func_80039880(arg0) == 0 && func_80033494(arg0) == 0 && func_800398F0(arg0) == 0) {
        if (func_800334F4(arg0) != 0) {
            func_800344A0(arg0);
        } else {
            func_80038678(arg0);
        }
    }
}

void func_80031688(struct PlayerObj* arg0)
{
    if ((func_80034100(arg0) == 0) && (func_80033EA4(arg0) == 0) && (func_80037290(arg0) == 0) && (func_80039880(arg0) == 0) && (func_80033494(arg0) == 0) && (func_800398F0(arg0) == 0)) {
        if (func_800334F4(arg0) != 0) {
            func_80015DC8(ANIMATED_OBJECT(arg0));
            if (arg0->animation_step.fields.relative_step < 0) {
                func_800344EC(arg0);
                return;
            }
            func_8002B718((struct MovingObj*)arg0);
            func_80038568(arg0, 7);
            return;
        }
        func_8003443C(arg0);
    }
}

void func_80031764(struct PlayerObj* arg0)
{
    if (func_80034100(arg0) == 0 && func_80033EA4(arg0) == 0 && func_80037290(arg0) == 0 && func_80039880(arg0) == 0 && func_80033494(arg0) == 0 && func_800398F0(arg0) == 0) {
        if (func_8003356C(arg0) != 0) {
            func_80015DC8(ANIMATED_OBJECT(arg0));
            func_8002B718((struct MovingObj*)arg0);
            func_80038568(arg0, 8);
        } else {
            func_8003443C(arg0);
        }
    }
}

INCLUDE_ASM("main/nonmatchings/21AB4", func_80031820);

void func_800318D0(struct PlayerObj* arg0)
{
    if (arg0->unkC3) {
        arg0->y_vel.val = 0;
    }
    if (arg0->unk88.bytes.collision_flags & 4) {
        arg0->y_vel.val = 0;
    }
    if (!(arg0->input.buttons.held & 0x80)) {
        arg0->y_vel.val = 0;
    }
    if (func_80037338(arg0) == 0 && func_8003996C(arg0) == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.event & 0x80) {
            arg0->animation_step.fields.event &= 0x3F;
            func_8001540C(1, 1, arg0);
        }
        if (func_80033F5C(arg0) == 0) {
            if (arg0->unk8A.bytes.high == 0) {
                if (func_80033AC0(arg0) != 0) {
                    return;
                }
            } else {
                arg0->unk8A.bytes.high--;
            }
            if (func_800339E0(arg0) == 0) {
                func_800365A4(arg0);
                func_80036B88(arg0);
                if (arg0->y_vel.val <= 0) {
                    func_80038524(arg0, 0xB);
                    arg0->unk67 = -1;
                    arg0->unk5 = 7;
                    arg0->unk6 = 0;
                } else {
                    func_80038568(arg0, 0xA);
                }
            }
        }
    }
}

void func_80031A24(struct PlayerObj* arg0)
{
    if (arg0->unk88.bytes.collision_flags & 8) {
        func_80034668(arg0);
        return;
    }

    if ((func_80037338(arg0) == 0) && (func_80039A00(arg0) == 0) && (func_80033F5C(arg0) == 0) && (func_80033AC0(arg0) == 0) && (func_800339E0(arg0) == 0)) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_800365A4(arg0);
        func_80036B88(arg0);
        func_80038568(arg0, 0xB);
    }
}

void func_80031AE0(struct PlayerObj* arg0)
{
    if ((func_80034100(arg0) == 0) && (func_80033EA4(arg0) == 0) && (func_80037290(arg0) == 0) && (func_80039880(arg0) == 0) && (func_80033414(arg0) == 0) && (func_800398F0(arg0) == 0)) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.relative_step < 0) {
            func_8003443C(arg0);
        } else {
            func_80038568(arg0, 0xC);
        }
    }
}

void func_80031B90(struct PlayerObj* arg0)
{
    s8 timer;

    if (arg0->unk88.bytes.collision_flags & 8) {
        func_80034668(arg0);
        return;
    }
    if (arg0->unkC3 != 0) {
        func_80034604(arg0);
        return;
    }
    if (func_80037338(arg0) != 0) {
        return;
    }
    if ((arg0->unk88.bytes.collision_flags & 3) == 0) {
        func_80034604(arg0);
        return;
    }
    if (func_80033B34(arg0) != 0) {
        return;
    }

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event & 0x80) {
        if (arg0->unk88.bytes.collision_flags & 1) {
            arg0->unk15 = 0;
        } else {
            arg0->unk15 = 0x40;
        }
        arg0->animation_step.fields.event &= 0x3F;
    }

    timer = arg0->unk8A.bytes.low - 1;
    arg0->unk8A.bytes.low = timer;
    if (timer == 0) {
        func_80034AFC(arg0);
        return;
    }
    func_80038568(arg0, 0xD);
}
void func_80031CAC(struct PlayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_80031CEC(arg0);
    } else {
        func_80031DD4(arg0);
    }
}

void func_80031CEC(struct PlayerObj* arg0)
{
    s32 should_end_state;
    s32 direction_mask;
    s32 vertical_mask;
    u8 collision_flags;
    s8 timer;

    if (arg0->unkC3 != 0) {
        func_80034604(arg0);
        return;
    }

    if (func_80037338(arg0) != 0) {
        return;
    }

    collision_flags = arg0->unk88.bytes.collision_flags;
    vertical_mask = collision_flags & 4;
    should_end_state = vertical_mask != 0;
    if (arg0->unk15 != 0) {
        direction_mask = collision_flags & 2;
    } else {
        direction_mask = collision_flags & 1;
    }
    if (direction_mask != 0) {
        should_end_state = 1;
    }

    if (should_end_state != 0) {
        func_80034604(arg0);
        return;
    }

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80036B88(arg0);

    timer = arg0->unk8A.bytes.low - 1;
    arg0->unk8A.bytes.low = timer;
    if (timer == 0) {
        arg0->x_vel.val = 0;
        arg0->unk6++;
        return;
    }

    func_80038568(arg0, 0xE);
}

void func_80031DD4(struct PlayerObj* arg0)
{
    if (arg0->unkC3 != 0) {
        arg0->y_vel.val = 0;
    }
    if ((arg0->unk88.bytes.collision_flags & 4) != 0) {
        arg0->y_vel.val = 0;
    }
    if ((arg0->input.buttons.held & 0x80) == 0) {
        arg0->y_vel.val = 0;
    }
    if ((func_80037338(arg0) == 0) && (func_8003996C(arg0) == 0) && (func_80033F5C(arg0) == 0) && (func_80033AC0(arg0) == 0) && (func_800339E0(arg0) == 0)) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_800365A4(arg0);
        func_80036B88(arg0);
        if (arg0->y_vel.val <= 0) {
            func_80038524(arg0, 0xB);
            arg0->unk67 = -1;
            arg0->unk5 = 7;
            arg0->unk6 = 0;
            return;
        }
        func_80038568(arg0, 0xE);
    }
}

void func_80031F1C(struct PlayerObj* arg0);
void func_8003200C(struct PlayerObj* arg0);

void func_80031EDC(struct PlayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_80031F1C(arg0);
    } else {
        func_8003200C(arg0);
    }
}

void func_80031F1C(struct PlayerObj* arg0)
{
    if (arg0->unk88.bytes.collision_flags & 8) {
        func_80034668(arg0);
        return;
    }

    if (arg0->unkC3 != 0) {
        func_80034604(arg0);
        return;
    }
    if (func_80037338(arg0) != 0) {
        return;
    }
    if (func_80039B44(arg0) != 0) {
        return;
    }
    if ((arg0->unk88.bytes.collision_flags & 3) == 0) {
        func_80034604(arg0);
        return;
    }

    if (func_80033B34(arg0) != 0) {
        return;
    }
    if (func_80033B8C(arg0) != 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_8002B718((struct MovingObj*)arg0);
        func_80036B88(arg0);
        func_80038568(arg0, 0xF);
        return;
    }
    func_80034B64(arg0);
}

void func_8003200C(struct PlayerObj* arg0)
{
    s8 timer;

    if (arg0->unk88.bytes.collision_flags & 8) {
        func_80034668(arg0);
        return;
    }
    if (arg0->unkC3 != 0) {
        func_80034604(arg0);
        return;
    }
    if ((func_80037338(arg0) == 0) && (func_80039A00(arg0) == 0)) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_8002B694(ANIMATED_OBJECT(arg0));
        func_80036B88(arg0);
        timer = arg0->unk8A.bytes.low - 1;
        arg0->unk8A.bytes.low = timer;
        if (timer == 0) {
            arg0->x_vel.val = 0;
            arg0->unk5 = 7;
            arg0->unk6 = 0;
            return;
        }
        func_80038568(arg0, 0xB);
    }
}

void func_800320E4(struct PlayerObj* arg0)
{
    if (func_80034100(arg0) == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        D_800F8A90[arg0->unk6](arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/21AB4", func_80032140);

INCLUDE_ASM("main/nonmatchings/21AB4", func_80032224);

INCLUDE_ASM("main/nonmatchings/21AB4", func_80032300);

void func_80032468(struct PlayerObj* arg0)
{
    if (arg0->unk88.bytes.collision_flags & 8) {
        func_80034668(arg0);
    } else if (arg0->unkC3 != 0) {
        func_80034604(arg0);

    } else if (arg0->unk2 == 0) {
        if (func_80037338(arg0) == 0) {
            if (arg0->unk8E != 0) {
                func_8003490C(arg0);
            } else {
                func_80015DC8(ANIMATED_OBJECT(arg0));
                D_800F8A9C[arg0->unk6](arg0);
            }
        }
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        D_800F8A9C[arg0->unk6](arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/21AB4", func_8003253C);

void func_800325EC(struct PlayerObj* arg0)
{
    u8 event;

    if (func_80039A00(arg0) != 0) {
        arg0->unk2C = FIXED(0.2578125);
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->y_vel.val = 0;
        arg0->unk67 = -1;
        arg0->unk84 = 0;
    } else if (func_800337DC(arg0) != 0) {
        func_800348B4(arg0);
    } else {
        event = arg0->animation_step.fields.event;
        if (event & 0x40) {
            arg0->animation_step.fields.event = event & 0x3F;
            func_8003666C(arg0);
        }
    }
}

INCLUDE_ASM("main/nonmatchings/21AB4", func_8003267C);

void func_80032740(struct PlayerObj* arg0)
{
    D_800F8AA8[arg0->unk6](arg0);
}

void func_8003277C(struct PlayerObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step < 0) {
        func_800350A4(arg0, 0x1F);
        func_80034D64(arg0);
    }
}

void func_800327CC(struct PlayerObj* arg0)
{
    u16 y;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event & 0x80) {
        y = arg0->y_pos.u.hi;
        arg0->animation_step.fields.event = 0;
        arg0->y_pos.i.hi = y - 0x10;
        ((f32*)&arg0->unk1C)->i.hi = y - 0x20;
        func_80035EA4(arg0);
    }
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk67 = 0;
        func_8003443C(arg0);
    }
}

void func_80032840(struct PlayerObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event & 0x80) {
        arg0->animation_step.fields.event = 0;
        arg0->y_pos.i.hi = (arg0->y_pos.u.hi & 0xFFF0) + 0x20;
    }
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->y_pos.i.hi = arg0->y_pos.u.hi + 0x10;
        func_80035EA4(arg0);
        func_8003516C(arg0, 0x20, 3);
        func_80034DC8(arg0);
    }
}

void func_800328CC(struct PlayerObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk67 = 0;
        func_8003443C(arg0);
    }
}

void func_80032910(struct PlayerObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step < 0) {
        func_80034604(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/21AB4", func_80032950);

INCLUDE_ASM("main/nonmatchings/21AB4", func_80032A28);

void func_80032B04(struct PlayerObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    D_800F8ABC[arg0->unk63](arg0);
}

void func_80032DE0(struct PlayerObj* arg0);

void func_80032B50(struct PlayerObj* arg0)
{
    func_80032DE0(arg0);
    if (arg0->unk2 == 0) {
        if (arg0->animation_step.fields.frame_index == 0xEC) {
            func_800362F8(arg0, 0x49);
        } else {
            func_800361F8(arg0);
        }
    }
    if (arg0->unk61 == 0x3C) {
        func_8003470C(arg0);
        if (arg0->unkC3 != 0) {
            arg0->unkA4 = 0;
            arg0->unk61 = 0;
            return;
        }
        func_800363EC(arg0);
        arg0->unkA4 = -1;
    }
}

void func_80032BF4(struct PlayerObj* arg0)
{
    s8 temp_v0;

    func_80032DE0(arg0);
    func_80036B88(arg0);
    temp_v0 = arg0->unk6;
    if (temp_v0 == 0) {
        arg0->unk6 = temp_v0 + 1;
        return;
    }
    if ((arg0->unk67 != 0) && (arg0->unk88.bytes.collision_flags & 8)) {
        arg0->unk67 = 0;
        if (arg0->unk15 != 0) {
            arg0->x_vel.val = FIXED(-0.5);
        } else {
            arg0->x_vel.val = FIXED(0.5);
        }
        arg0->y_vel.val = 0;
        arg0->unk2C = 0;
    }
    if (arg0->unk61 == 0x3C) {
        if (arg0->unk88.bytes.collision_flags & 8) {
            arg0->unk67 = 0;
            func_800343A4(arg0);
        } else if (arg0->unk2C != 0) {
            func_800350A4(arg0, 0xB);
            arg0->unk67 = -1;
            arg0->unk5 = 7;
            arg0->unk6 = 0;
        } else {
            func_80034604(arg0);
        }
        if (arg0->unkC3 != 0) {
            arg0->unkA4 = 0;
            arg0->unk61 = 0;
            return;
        }
        func_800363EC(arg0);
        arg0->unkA4 = -1;
    }
}

void func_80032D28(struct PlayerObj* arg0)
{
    s8 temp_v1;
    s8 var_v0;

    if (arg0->input.buttons.held & 2) {
        arg0->unk15 = 0;
    }
    if (arg0->input.buttons.held & 1) {
        arg0->unk15 = 0x40;
    }

    temp_v1 = arg0->unkBA;
    if (temp_v1 > 0) {
        return;
    }
    if (temp_v1 == 0) {
        arg0->unkA4 = 0;
        func_8003470C(arg0);
        return;
    }

    if (temp_v1 == -1) {
        func_800350A4(arg0, 0x25);
        var_v0 = -2;
    } else if (arg0->animation_step.fields.relative_step < 0) {
        func_800350A4(arg0, 0x24);
        var_v0 = 1;
    } else {
        return;
    }
    arg0->unkBA = var_v0;
}

void func_80032DE0(struct PlayerObj* arg0)
{
    s32 velocity;
    s32 direction;

    if (arg0->unkC4 != 0) {
        return;
    }

    velocity = arg0->x_vel.val;
    if (velocity != 0) {
        direction = 2;
        if (velocity > 0) {
            direction = 1;
        }
        if ((direction & arg0->unk88.bytes.collision_flags) != 0) {
            arg0->x_vel.val = 0;
            arg0->unk28 = 0;
        }
    }

    func_8002B694(ANIMATED_OBJECT(arg0));

    if (arg0->unk15 != 0) {
        if (arg0->x_vel.val <= 0) {
            return;
        }
    } else if (arg0->x_vel.val >= 0) {
        return;
    }

    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
}

INCLUDE_ASM("main/nonmatchings/21AB4", func_80032E94);

void func_80032F64(struct PlayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_80032FA4(arg0);
    } else {
        func_80033054(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/21AB4", func_80032FA4);

void func_80033054(struct PlayerObj* arg0)
{
    if (arg0->unk88.bytes.collision_flags & 8) {
        func_80034668(arg0);
        return;
    }

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80036B88(arg0);
}

INCLUDE_ASM("main/nonmatchings/21AB4", func_800330B4);

INCLUDE_ASM("main/nonmatchings/21AB4", func_80033108);

void func_800331A8(struct PlayerObj* arg0)
{
    if (func_80034100(arg0) == 0 && arg0->unk6 == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->on_screen = 0;
            arg0->unk6++;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/21AB4", func_80033210);

INCLUDE_ASM("main/nonmatchings/21AB4", func_800332C0);

INCLUDE_ASM("main/nonmatchings/21AB4", func_80033368);

void (*D_800F8990[])(struct PlayerObj*) = {
    func_80031410,
    func_80031540,
    func_800315E0,
    func_80031688,
    func_80031764,
    func_80031820,
    func_800318D0,
    func_80031A24,
    func_80031AE0,
    func_80031B90,
    func_80031CAC,
    func_80031EDC,
    func_800320E4,
    func_80032468,
    func_80032740,
    func_80032950,
    func_80032A28,
    func_80032B04,
    func_80032E94,
    func_80032F64,
    func_800330B4,
    func_80033108,
    func_800331A8,
    func_80033210,
    func_800332C0,
    func_80033368,
    func_800315E0,
    func_800315E0,
    func_800315E0,
    func_800315E0,
    func_800315E0,
    func_800315E0,
    func_80038854,
    func_800388F0,
    func_80038E90,
    func_80039120,
    func_80039270,
    func_80039328,
    func_80039378,
    func_80039570,
    func_80039700,
    func_800315E0,
    func_800315E0,
    func_800315E0,
    func_800315E0,
    func_800315E0,
    func_800315E0,
    func_800315E0,
    func_8003A104,
    func_8003A3EC,
    func_8003A5E4,
    func_8003A7B4,
    func_8003A8A0,
    func_8003A9F0,
    func_8003AAE8,
    func_8003A3EC,
    func_8003A5E4,
    func_8003AE08,
    func_8003B044,
    func_8003B24C,
    func_800315E0,
    func_800315E0,
    func_800315E0,
    func_800315E0,
};

void (*D_800F8A90[])(struct PlayerObj*) = {
    func_80032140,
    func_80032224,
    func_80032300,
};

void (*D_800F8A9C[])(struct PlayerObj*) = {
    func_8003253C,
    func_800325EC,
    func_8003267C,
};

void (*D_800F8AA8[])(struct PlayerObj*) = {
    func_8003277C,
    func_800327CC,
    func_80032840,
    func_800328CC,
    func_80032910,
};

void (*D_800F8ABC[])(struct PlayerObj*) = {
    func_80032B50,
    func_80032B50,
    func_80032BF4,
    func_80032D28,
    func_80032B50,
};
