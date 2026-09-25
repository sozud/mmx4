// PlayerObj
// 800311EC..8003B3DC
#include "common.h"

struct PlayerInitialStateData {
    s32 unk20;
    s32 unk28;
    s32 unk24;
    s32 unk2C;
};

void func_800311EC(void)
{
    engine_obj.unk38 = &g_Player;
    if (g_Player.unkBD != 0) {
        g_Player.unkBC = 5;
        g_Player.unkBD = 0;
        return;
    }
    if (g_Player.unkBC == 0 || --g_Player.unkBC == 0) {
        g_Player.unk18.val = g_Player.x_pos.val;
        g_Player.unk1C.val = g_Player.y_pos.val;
        D_800F8980[g_Player.state](&g_Player);
        func_80094F74();
    }
}

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
            func_8002B718(MOVING_OBJECT(arg0));
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
        func_8002B718(MOVING_OBJECT(arg0));
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

void func_80031540(struct PlayerObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk6 == 0) {
        if (arg0->animation_step.fields.relative_step == 0) {
            func_800350A4(arg0, 4);
            arg0->unk6 = (u8)arg0->unk6 + 1;
        }
    } else {
        if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x40) == 0) {
            func_8002B718(MOVING_OBJECT(arg0));
            func_80036B88(arg0);
            return;
        }
        arg0->on_screen = 0;
        arg0->state = 3;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    }
}

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
            func_8002B718(MOVING_OBJECT(arg0));
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
            func_8002B718(MOVING_OBJECT(arg0));
            func_80038568(arg0, 8);
        } else {
            func_8003443C(arg0);
        }
    }
}

void func_80031820(struct PlayerObj* arg0)
{
    if ((func_80034100(arg0) == 0) && (func_80033EA4(arg0) == 0) && (func_80039880(arg0) == 0) && (func_80033494(arg0) == 0) && (func_800398F0(arg0) == 0)) {
        if (func_800334F4(arg0) != 0) {
            func_800344A0(arg0);
            return;
        }
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.relative_step < 0) {
            func_800343A4(arg0);
        }
    }
}

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
        func_8002B718(MOVING_OBJECT(arg0));
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

void func_80032140(struct PlayerObj* arg0)
{
    s8 event;
    u8 unsigned_event;

    if ((func_80037290(arg0) == 0) && (func_80039880(arg0) == 0)) {
        if (arg0->pressed_input & 0x80) {
            func_80034538(arg0);
            return;
        }
        if (func_800398F0(arg0) == 0) {
            unsigned_event = arg0->animation_step.fields.event;
            if (unsigned_event & 0x20) {
                arg0->animation_step.fields.event = unsigned_event & 0xF;
                func_800366C0(arg0);
            }
            event = arg0->animation_step.fields.event;
            if (event & 0x80) {
                arg0->animation_step.fields.event = event & 0xF;
                func_8001540C(1, 5, arg0);
                arg0->unk8C = 1;
                arg0->unk6++;
                return;
            }
            func_80038568(arg0, 0x10);
        }
    }
}

void func_80032224(struct PlayerObj* arg0)
{
    u8 event;

    if ((func_80037290(arg0) == 0) && (func_8003A000(arg0) == 0)) {
        if (arg0->pressed_input & 0x80) {
            func_80034538(arg0);
            return;
        }
        if (func_800398F0(arg0) == 0) {
            if (func_800337DC(arg0) != 0) {
                func_800347D0(arg0);
                return;
            }
            event = arg0->animation_step.fields.event;
            if (event & 0x40) {
                arg0->animation_step.fields.event = event & 0xF;
                func_8003666C(arg0);
            }
            if (!(arg0->unk85 & 3)) {
                func_800367F8(arg0);
            }
            func_80038568(arg0, 0x10);
        }
    }
}

INCLUDE_ASM("main/nonmatchings/player", func_80032300);

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

void func_8003253C(struct PlayerObj* arg0)
{
    s8 temp_v0;
    u8 temp_v1;

    if (func_80039A00(arg0) != 0) {
        arg0->unk2C = FIXED(0.2578125);
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->y_vel.val = 0;
        arg0->unk67 = -1;
        arg0->unk84 = 0;
        return;
    }

    temp_v1 = (u8)arg0->animation_step.fields.event;
    if (temp_v1 & 0x40) {
        arg0->animation_step.fields.event = temp_v1 & 0x3F;
        func_8003666C(arg0);
    }

    temp_v0 = arg0->animation_step.fields.event;
    if (temp_v0 & 0x80) {
        arg0->animation_step.fields.event = temp_v0 & 0x3F;
        func_8001540C(1, 5, arg0);
        arg0->unk8C = 1;
        arg0->unk6 = (u8)arg0->unk6 + 1;
    }
}

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

void func_8003267C(struct PlayerObj* arg0)
{
    if (arg0->unk88.bytes.collision_flags & 8) {
        func_80034668(arg0);
        return;
    }
    if (func_80039A00(arg0) != 0) {
        arg0->unk2C = FIXED(0.2578125);
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->y_vel.val = 0;
        arg0->unk67 = -1;
        arg0->unk84 = 0;
        return;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80036B88(arg0);
    if ((arg0->animation_step.fields.relative_step < 0) || (arg0->input.buttons.held & 3)) {
        func_800350A4(arg0, 0x14);
        arg0->unk5 = 7;
        arg0->unk6 = 0;
    }
}

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
        arg0->unk1C.i.hi = y - 0x20;
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

void func_80032950(struct PlayerObj* arg0)
{
    u16 buttons;
    u8 duration;

    if ((func_80033FF0(arg0) == 0) && (func_800373DC(arg0) == 0) && (func_80039AC8(arg0) == 0)) {
        if (arg0->pressed_input & 2) {
            arg0->unk15 = 0;
        }
        if (arg0->pressed_input & 1) {
            arg0->unk15 = 0x40;
        }
        buttons = arg0->input.buttons.held;
        if (buttons & 4) {
            func_80015DC8(ANIMATED_OBJECT(arg0));
            func_8002B718(MOVING_OBJECT(arg0));
            return;
        }
        if (buttons & 8) {
            duration = arg0->animation_step.fields.duration;
            func_8003516C(arg0, 0x20, arg0->animation_step.fields.event);
            arg0->animation_step.fields.duration = duration;
            func_80034DC8(arg0);
        }
    }
}

void func_80032A28(struct PlayerObj* arg0)
{
    u16 buttons;
    s8 duration;

    if ((func_80033FF0(arg0) == 0) && (func_800373DC(arg0) == 0) && (func_80039AC8(arg0) == 0)) {
        if (arg0->pressed_input & 2) {
            arg0->unk15 = 0;
        }
        if (arg0->pressed_input & 1) {
            arg0->unk15 = 0x40;
        }

        buttons = arg0->input.buttons.held;
        if (buttons & 4) {
            duration = arg0->animation_step.fields.duration;
            func_8003516C(arg0, 0x1F, arg0->animation_step.fields.event);
            arg0->animation_step.fields.duration = duration;
            func_80034D64(arg0);
            return;
        }
        if (buttons & 8) {
            func_80015DC8(ANIMATED_OBJECT(arg0));
            func_8002B718(MOVING_OBJECT(arg0));
        }
    }
}

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

void func_80032E94(struct PlayerObj* arg0)
{
    if (engine_obj.unkF != 0) {
        func_80034F7C(arg0);
        return;
    }
    if ((arg0->unkC0 > 0) && (arg0->unkC1 == 0x17)) {
        func_80034E2C(arg0);
        return;
    }
    if (arg0->unkC5 == 0) {
        func_80035EA4(arg0);
        func_80034538(arg0);
        arg0->unk86 = 1;
        return;
    }
    if (arg0->unk6 == 0) {
        func_800350A4(arg0, (u8)arg0->unkD4);
        arg0->unk6++;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80032F64(struct PlayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_80032FA4(arg0);
    } else {
        func_80033054(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/player", func_80032FA4);

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

void func_800330B4(struct PlayerObj* arg0)
{
    if (func_80034100(arg0) == 0) {
        if (arg0->unkC0 == 0) {
            arg0->unk5 = 2;
            arg0->unk6 = 0;
        } else {
            func_80015DC8(ANIMATED_OBJECT(arg0));
        }
    }
}

INCLUDE_ASM("main/nonmatchings/player", func_80033108);

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

void func_80033210(struct PlayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_8002B694(ANIMATED_OBJECT(arg0));
        if (arg0->y_vel.val <= 0) {
            func_800350A4(arg0, 0xB);
            arg0->unk67 = -1;
            arg0->y_vel.val = 0;
            arg0->unk6 = (u8)arg0->unk6 + 1;
        }
    } else {
        if (arg0->unk88.bytes.collision_flags & 8) {
            arg0->unkC0 = 0;
            func_80034668(arg0);
            return;
        }
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_8002B694(ANIMATED_OBJECT(arg0));
    }
}

void func_800332C0(struct PlayerObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));

    if (arg0->unk6 == 0) {
        if (arg0->unkE2 == 4) {
            func_800350A4(arg0, 0x27);
            arg0->unk6 = (u8)arg0->unk6 + 1;
        }
    } else {
        if (arg0->animation_step.fields.event & 0x80) {
            arg0->animation_step.fields.event = 0;
            func_8001540C(0, 0x21, 0);
        }

        if (arg0->animation_step.fields.relative_step == 0) {
            func_80036B18();
            func_800343A4(arg0);
        }
    }
}

void func_80033368(struct PlayerObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk6 == 0) {
        if (D_80173C84 == 0) {
            func_800350A4(arg0, 0x27);
            arg0->unk6 = (u8)arg0->unk6 + 1;
        }
    } else {
        if (arg0->animation_step.fields.event & 0x80) {
            arg0->animation_step.fields.event = 0;
            func_8001540C(0, 0x21, 0);
        }
        if (arg0->animation_step.fields.relative_step == 0) {
            func_800350A4(arg0, 0x28);
            func_80035048(arg0);
        }
    }
}

s32 func_80033414(struct PlayerObj* arg0)
{
    if (func_80033694(arg0) != 0) {
        func_80034754(arg0);
        return 1;
    }
    if ((arg0->pressed_input & 0x80) != 0) {
        func_80034538(arg0);
        return 1;
    }
    if (func_8003356C(arg0) == 0) {
        return 0;
    }
    func_800344EC(arg0);
    return 1;
}

s32 func_80033494(struct PlayerObj* arg0)
{
    if (func_80033694(arg0) != 0) {
        func_80034754(arg0);
        return 1;
    }
    if (arg0->pressed_input & 0x80) {
        func_80034538(arg0);
        return 1;
    }
    return 0;
}

s32 func_800334F4(struct PlayerObj* arg0)
{
    if (arg0->unkC3) {
        return 0;
    }

    if (!(arg0->input.buttons.held & 3)) {
        return 0;
    }

    if (arg0->input.buttons.held & 1) {
        arg0->unk15 = 0x40;
        if (!(arg0->unk88.bytes.collision_flags & 1)) {
            arg0->x_vel.val = FIXED(0.5);
            return 1;
        } else {
            return 0;
        }
    }

    arg0->unk15 = 0;
    if (!(arg0->unk88.bytes.collision_flags & 2)) {
        arg0->x_vel.val = FIXED(-0.5);
        return 1;
    } else {
        return 0;
    }
}

s32 func_8003356C(struct PlayerObj* arg0)
{
    u16 buttons;

    if (arg0->unkC3 != 0) {
        return 0;
    }

    buttons = arg0->input.buttons.held;
    if ((buttons & 3) == 0) {
        return 0;
    }

    if (buttons & 1) {
        arg0->unk15 = 0x40;
        if (arg0->unk88.bytes.collision_flags & 1) {
            return 0;
        }
        arg0->x_vel.val = FIXED(2);
    } else {
        arg0->unk15 = 0;
        if (arg0->unk88.bytes.collision_flags & 2) {
            return 0;
        }
        arg0->x_vel.val = FIXED(-2);
    }

    return 1;
}

void func_800335E4(struct PlayerObj* arg0)
{
    s8 temp_v1;

    temp_v1 = arg0->unk5; // fake
    if ((arg0->unk5 != 0) && (temp_v1 != 1) && (arg0->unk67 == 0) && (arg0->unkA4 <= 0) && (arg0->unkC5 >= 0) && (arg0->unkC4 == 0) && !(arg0->unk88.bytes.collision_flags & 8)) {
        if (arg0->unk2 != 0) {
            func_80036054(arg0);
        }
        func_80034604(arg0);
    }
}

s32 func_80033694(struct PlayerObj* arg0)
{
    if (arg0->unkC3 || (!arg0->unk87 && !(arg0->pressed_input & 0x100))) {
        return 0;
    }

    if (arg0->input.buttons.held & 1) {
        arg0->unk15 = 0x40;
    }
    if (arg0->input.buttons.held & 2) {
        arg0->unk15 = 0;
    }
    if (arg0->unk15 != 0) {
        if ((arg0->unk88.bytes.collision_flags & 1)) {
            return 0;
        } else {
            arg0->x_vel.val = FIXED(6.5);
            return 1;
        }
    } else if (!(arg0->unk88.bytes.collision_flags & 2)) {
        arg0->x_vel.val = FIXED(-6.5);
        return 1;
    } else {
        return 0;
    }
}

void func_80033750(struct PlayerObj* arg0)
{
    s8 temp_v1;

    arg0->unk87 = 0;
    if ((arg0->unkC3 == 0) && (temp_v1 = arg0->unk5, (temp_v1 != 0)) && (temp_v1 != 1)) {
        if (arg0->unk88.bytes.timer == 0) {
            arg0->unk82 = arg0->pressed_input & 3;
            if (arg0->unk82 != 0) {
                arg0->unk88.bytes.timer = 0xC;
            }
        } else {
            arg0->unk88.bytes.timer--;
            if (arg0->pressed_input & arg0->unk82) {
                arg0->unk87 = 1;
                arg0->unk88.bytes.timer = 0;
            }
        }
    }
}

s32 func_800337DC(struct PlayerObj* self)
{
    s32 collision_side;
    u16 held;
    u8 timer;

    collision_side = 2;
    if (self->unk15 != 0) {
        collision_side = 1;
    }
    if (collision_side & self->unk88.bytes.collision_flags) {
        return 1;
    }

    func_8002B694(ANIMATED_OBJECT(self));
    if (self->unk15 != 0) {
        if (self->x_vel.val <= FIXED(4.125) - 1) {
            self->x_vel.val = FIXED(4.125);
        }
    } else if (self->x_vel.val > FIXED(-4.125)) {
        self->x_vel.val = FIXED(-4.125);
    }

    timer = self->unk85 - 1;
    self->unk85 = timer;
    if ((timer << 24) == 0) {
        return 1;
    }

    held = self->input.buttons.held;
    if (!(held & 0x103)) {
        return 1;
    }
    if (self->unk15 != 0) {
        if (held & 2) {
            return 1;
        }
    } else if (held & 1) {
        return 1;
    }
    return 0;
}

void func_800338CC(struct PlayerObj* arg0)
{
    s32 var_v1;

    if (arg0->unkC4 > 0 && arg0->unkA4 <= 0) {
        func_80036054(arg0);

        // maybe these can be combined? couldn't get a match
        var_v1 = 0;
        if (arg0->unk17 == 5) {
            var_v1 = 1;
        }
        if (arg0->unk17 == 6) {
            var_v1 = 1;
        }
        if (arg0->unk17 == 0xC) {
            var_v1 = 1;
        }
        if (var_v1) {
            func_800350A4(arg0, 0x26);
        }

        arg0->unk15 = 0x40;
        arg0->unkC4 = -1;
        arg0->unk8C = 0;
        arg0->unk5 = 0x13;
        arg0->unk6 = 0;
    }
}

void func_80033974(struct PlayerObj* arg0)
{
    if (arg0->unkC5 > 0) {
        func_80036088(arg0);
        func_80038490(arg0);
        func_80036E98(arg0);
        arg0->unk68 = 0;
        arg0->unk67 = 1;
        arg0->unkC5 = -1;
        arg0->unk5 = 0x12;
        arg0->unk6 = 1;
    }
}

s32 func_800339E0(struct PlayerObj* arg0)
{
    if (arg0->unkC3 != 0) {
        return 0;
    }
    if (arg0->unk86 != 0) {
        return 0;
    }
    if (arg0->unk2 == 0) {
        if (func_8003751C(arg0) != 0) {
            return 1;
        }
    } else if (func_80039D9C(arg0) != 0) {
        return 1;
    }

    if (arg0->unk2 == 0) {
        if (arg0->unk92 != 0) {
            return 0;
        }
        if ((arg0->unkA7 & 8) == 0) {
            return 0;
        }
    } else if ((arg0->unkB9 & 0x10) == 0) {
        return 0;
    }

    if (func_80033694(arg0) != 0) {
        func_8003484C(arg0);
        return 1;
    }
    return 0;
}

s32 func_80033AC0(struct PlayerObj* arg0)
{
    if (arg0->unkC3) {
        return 0;
    }

    if (!(arg0->unk88.bytes.collision_flags & 3)) {
        return 0;
    }

    if (func_80033B34(arg0)) {
        return 1;
    }

    if (func_80033B8C(arg0)) {
        func_80034968(arg0);
        return 1;
    }

    return 0;
}

s32 func_80033B34(struct PlayerObj* arg0)
{
    if (arg0->unkC3 == 0) {
        if (arg0->pressed_input & 0x80) {
            if (arg0->unk4A > 0) {
                func_800349F4(arg0);
                return 1;
            }
        }
    }
    return 0;
}

s32 func_80033B8C(struct PlayerObj* arg0)
{
    if ((arg0->unkC3 != 0) || (arg0->unk4A == 0)) {
        return 0;
    }
    return (arg0->input.buttons.held & 3 & arg0->unk88.bytes.collision_flags) != 0;
}

void func_80033BC8(struct PlayerObj* arg0)
{
    s8 temp_v1;
    if (arg0->unkD9 == 0 && (temp_v1 = arg0->unk5, temp_v1 != 0) && (temp_v1 != 1)) {
        if ((arg0->unk88.bytes.collision_flags & 0xC) == 0xC) {
            arg0->unk5C = -0x80;
        }
        if ((arg0->unk88.bytes.collision_flags & 3) == 3) {
            arg0->unk5C = -0x80;
        }
        if (arg0->unk79 != 0 && arg0->unk61 == 0 && arg0->unk7A == 0) {
            arg0->unk5C = -0x80;
        }
        if (arg0->unk5C == -0x80) {
            arg0->unk5C = 0;
            engine_obj.unk1C = 1;
            func_80033D10(arg0);
            func_80038490(arg0);
            arg0->unk68 = 0;
            arg0->unk54 = 0;
            arg0->state = 2;
            arg0->unk5 = 0;
            arg0->unk6 = 0;
            return;
        }
        if (arg0->unk61 != 0) {
            arg0->unk61--;
            if (arg0->unk61 == 0) {
                arg0->unkA4 = 0;
                func_800361F8(arg0);
                return;
            }
        }
        if (arg0->unk5C <= 0) {
            func_80033D54(arg0);
        }
    }
}

void func_80033D10(struct PlayerObj* arg0)
{
    arg0->unkBF = 1;
    arg0->unk84 = 0;
    arg0->unk86 = 0;
    arg0->unk8C = 0;
    func_80036054(arg0);
    func_800360B0(arg0);
}

INCLUDE_ASM("main/nonmatchings/player", func_80033D54);

u8 func_8002D8B8(struct PlayerObj* arg0);

u8 func_8002D94C(struct PlayerObj* arg0);

s32 func_80033EA4(struct PlayerObj* arg0)
{
    if (arg0->unkC3 || arg0->unk92) {
        return 0;
    }
    if (arg0->input.buttons.held & 4 && func_8002D8B8(arg0) == 0x20) {
        func_80034BDC(arg0);
        return 1;
    }
    if (arg0->input.buttons.held & 8 && func_8002D94C(arg0) == 0x21) {
        func_80034CB0(arg0);
        return 1;
    }
    return 0;
}

s32 func_80033F5C(struct PlayerObj* arg0)
{
    if (arg0->unkC3 != 0 || !(arg0->input.buttons.held & 4)) {
        return 0;
    }

    if (func_8002D994(arg0) == 0x20) {
        if (arg0->unk8E) {
            func_800387A8(arg0);
            return 1;
        }
        func_800350A4(arg0, 0x1F);
        func_80034D64(arg0);
        return 1;
    }
    return 0;
}

INCLUDE_ASM("main/nonmatchings/player", func_80033FF0);

s32 func_800340BC(struct PlayerObj* arg0)
{
    if (func_8002D994(arg0) == 0x20) {
        return 0;
    }

    func_80034604(arg0);
    return 1;
}

s32 func_80034100(struct PlayerObj* arg0)
{
    if (engine_obj.unkF != 0) {
        func_80034F7C(arg0);
        return 1;
    }

    if (arg0->unkC0 > 0) {
        func_80034E2C();
        return 1;
    }
    return 0;
}

void func_80034150(struct PlayerObj* arg0)
{
    s16 temp_v1;
    u16 temp_v1_2;
    s32 var_a0;

    temp_v1 = (arg0->x_pos.u.hi - 0x40) - background_objects[arg0->bg_offset].x_pos.u.hi;
    var_a0 = 0;
    if (temp_v1 != 0) {
        if (temp_v1 > 0) {
            arg0->unk15 = 0;
            var_a0 = temp_v1 < 3;
        } else {
            arg0->unk15 = 0x40;
            if (temp_v1 >= -2) {
                var_a0 = 1;
            }
        }
    } else {
        var_a0 = 1;
    }
    if (var_a0 != 0) {
        func_80036534(arg0);
        temp_v1_2 = background_objects[arg0->bg_offset].x_pos.u.hi;
        arg0->unkC0 = -1;
        arg0->unk15 = 0x40;
        arg0->unk5 = 0x14;
        arg0->x_pos.i.hi = temp_v1_2 + 0x40;
    }
}

s32 func_80034238(struct PlayerObj* arg0)
{
    s32 result = 0;

    if (arg0->unk88.bytes.collision_flags & 4) {
        result = 1;
        arg0->y_vel.val = 0;
    }

    if (arg0->y_vel.val <= 0) {
        result = 1;
    }

    if (result != 0) {
        s8 index = arg0->unk2;
        func_800350A4(arg0, D_800F8B30[index]);

        if (arg0->unk2 != 0) {
            struct VisualObj* new_obj = find_free_visual_obj();
            if (new_obj != NULL) {
                new_obj->active = 1;
                new_obj->id = 0x27;
                new_obj->unk2 = 0;
                new_obj->bg_offset = arg0->bg_offset;
            }
        }

        arg0->unk67 = -1;
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->unk6 = 3;
        return 1;
    } else {
        func_8002B694(ANIMATED_OBJECT(arg0));
        func_80036B88(arg0);
        return 0;
    }
}

void func_80034320(struct PlayerObj* arg0)
{
    s32 blocked;

    blocked = 0;
    if (arg0->unk15 != 0) {
        blocked = arg0->unk88.bytes.collision_flags & 1;
        if (arg0->x_vel.val <= 0) {
            blocked = 1;
        }
    } else {
        if (arg0->unk88.bytes.collision_flags & 2) {
            blocked = 1;
        }
        if (arg0->x_vel.val >= 0) {
            blocked = 1;
        }
    }
    if (blocked != 0) {
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->unk6++;
    }
}

void func_8003439C(void)
{
}

void func_800343A4(struct PlayerObj* arg0)
{
    s32 var_a2; // ???

    if (func_80034100(arg0) == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        if ((arg0->unk2 == 0) && (arg0->unk8E != 0)) {
            var_a2 = arg0->unk91 < 9;
            if (arg0->unk91 < 5) {
                var_a2 = 2;
            }
            func_8003516C(arg0, 0x5E, var_a2);
            if (arg0->unk91 >= 9) {
                arg0->animation_step.fields.duration = arg0->unk91 - 8;
            }
        } else {
            func_80036534(arg0);
        }
    }
}

void func_8003443C(struct PlayerObj* arg0)
{
    if (func_80034100(arg0) == 0) {
        if (arg0->unk2 == 0) {
            func_800343A4(arg0);
        } else {
            func_800350A4(arg0, 9);
            arg0->unk5 = 5;
            arg0->unk6 = 0;
        }
    }
}

void func_800344A0(struct PlayerObj* arg0)
{
    func_80038524(arg0, 7);
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    func_8002B718((struct MovingObj*)arg0);
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void func_800344EC(struct PlayerObj* arg0)
{
    func_80038524(arg0, 8);
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    func_8002B718((struct MovingObj*)arg0);
    arg0->unk5 = 4;
    arg0->unk6 = 0;
}

void func_80034538(struct PlayerObj* arg0)
{
    arg0->y_vel.val = FIXED(5.8125);
    arg0->unk67 = 1;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0x4200;
    if ((arg0->unk84 != 0) || ((arg0->input.buttons.held & 0x100) != 0)) {
        arg0->unk84 = 1;
        arg0->unk86 = 2;
        arg0->unk8C = 1;
    }
    arg0->unk8A.bytes.high = 0xA;
    func_80038524(arg0, 0xA);
    func_800363B8(arg0, D_800F8B34[arg0->unk2][get_random() & 3]);
    func_800365A4(arg0);
    arg0->unk5 = 6;
    arg0->unk6 = 0;
}

void func_80034604(struct PlayerObj* arg0)
{
    func_80038524(arg0, 0xB);
    arg0->unk2C = 0x4200;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk67 = -1;
    if (arg0->unk84 != 0) {
        arg0->unk84 = 0;
        arg0->unk8C = -1;
    }
    arg0->unk5 = 7;
    arg0->unk6 = 0;
}

void func_80034668(struct PlayerObj* arg0)
{
    func_8001540C(1, 2, arg0);
    arg0->unk67 = 0;
    func_80036034(arg0);
    if ((func_80034100(arg0) == 0) && (func_80037290(arg0) == 0) && (func_80039880(arg0) == 0) && (func_80033414(arg0) == 0) && (func_800398F0(arg0) == 0)) {
        func_80038524(arg0, 0xC);
        arg0->unk5 = 8;
        arg0->unk6 = 0;
    }
}

void func_8003470C(struct PlayerObj* arg0)
{
    if (arg0->unk88.bytes.collision_flags & 8) {
        arg0->unk67 = 0;
        arg0->unk86 = 0;
        func_800343A4(arg0);
    } else {
        func_80034604(arg0);
    }
}

void func_80034754(struct PlayerObj* arg0)
{
    arg0->unk84 = 1;
    arg0->unk86 = 1;
    if (arg0->pressed_input & 0x80) {
        func_80034538(arg0);
        return;
    }
    func_80038524(arg0, 0x10);
    arg0->unk28 = FIXED(-0.1875);
    arg0->unk85 = 0x1E;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk5 = 0xC;
    arg0->unk6 = 0;
}

void func_800347D0(struct PlayerObj* arg0)
{
    func_80038524(arg0, 0x11);
    func_80015930(1, 5);
    if (arg0->unk15 != 0) {
        arg0->x_vel.val = FIXED(4.125);
    } else {
        arg0->x_vel.val = FIXED(-4.125);
    }
    arg0->unk28 = FIXED(-0.1875);
    arg0->unk8C = -1;
    arg0->unk84 = 0;
    arg0->unk86 = 0;
    arg0->unk6 = 2;
}

void func_8003484C(struct PlayerObj* arg0)
{
    func_800350A4(arg0, 0x12);
    arg0->unk28 = FIXED(-0.1875);
    arg0->unk84 = -1;
    arg0->unk85 = 0x12;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk86 = 3;
    func_80036054(arg0);
    arg0->unk5 = 0xD;
    arg0->unk6 = 0;
}

void func_800348B4(struct PlayerObj* arg0)
{
    func_800350A4(arg0, 0x13);
    arg0->unk2C = FIXED(0.2578125);
    arg0->unk67 = -1;
    arg0->unk8C = -1;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk84 = 0;
    arg0->unk6 = 2;
}

void func_8003490C(struct PlayerObj* arg0)
{
    func_800350A4(arg0, 0x84);
    arg0->unk2C = FIXED(0.2578125);
    arg0->unk67 = -1;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk84 = 0;
    arg0->unk8C = 0;
    arg0->unk5 = 7;
    arg0->unk6 = 0;
}

void func_80034968(struct PlayerObj* arg0)
{
    func_80038524(arg0, 0xD);
    func_8001540C(1, 4, arg0);
    arg0->unk8C = -1;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk84 = 0;
    arg0->unk86 = 0;
    arg0->unk8A.bytes.low = 8;
    if (arg0->unk88.bytes.collision_flags & 1) {
        arg0->unk15 = 0x40;
    } else {
        arg0->unk15 = 0;
    }
    arg0->unk5 = 9;
    arg0->unk6 = 0;
}

INCLUDE_ASM("main/nonmatchings/player", func_800349F4);

void func_80034AFC(struct PlayerObj* arg0)
{
    func_80038524(arg0, 0xF);
    func_80036A94(arg0);
    arg0->unk67 = -1;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = FIXED(-1.4375);
    arg0->unk2C = 0;
    func_80036034(arg0);
    arg0->unk5 = 0xB;
    arg0->unk6 = 0;
}

INCLUDE_ASM("main/nonmatchings/player", func_80034B64);

void func_80034BDC(struct PlayerObj* arg0)
{
    func_800350A4(arg0, 0x1B);
    arg0->y_vel.val = FIXED(1);
    arg0->x_pos.u.lo = 0;
    arg0->y_pos.u.lo = 0;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 1;
    arg0->x_pos.u.hi = (arg0->x_pos.u.hi & 0xFFF0) + 8;
    func_80036034(arg0);
    func_80036054(arg0);
    arg0->unk5 = 0xE;
    arg0->unk6 = 0;
}

void func_80034C58(struct PlayerObj* arg0)
{
    func_800350A4(arg0, 0x1C);
    arg0->unk68 = 0;
    arg0->y_pos.u.lo = 0;
    arg0->y_pos.u.hi &= 0xFFF0;
    func_80036054(arg0);
    arg0->unk5 = 0xE;
    arg0->unk6 = 1;
}

void func_80034CB0(struct PlayerObj* arg0)
{
    func_800350A4(arg0, 0x1D);
    arg0->x_pos.u.lo = 0;
    arg0->y_pos.u.lo = 0;
    arg0->unk68 = 0;
    arg0->unk67 = 1;
    arg0->x_pos.u.hi = (arg0->x_pos.u.hi & 0xFFF0) + 8;
    func_80036034(arg0);
    func_80036054(arg0);
    arg0->unk5 = 0xE;
    arg0->unk6 = 2;
}

void func_80034D20(struct PlayerObj* arg0)
{
    func_800350A4(arg0, 0x1E);
    func_80036054(arg0);
    arg0->unk5 = 0xE;
    arg0->unk6 = 3;
}

void func_80034D64(struct PlayerObj* arg0)
{
    arg0->x_pos.i.lo = 0;
    arg0->y_pos.i.lo = 0;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = FIXED(1.5);
    arg0->unk2C = 0;
    arg0->x_pos.u.hi = (arg0->x_pos.u.hi & 0xFFF0) + 8;
    func_80036034(arg0);
    arg0->unk5 = 0xF;
    arg0->unk6 = 0;
}

void func_80034DC8(struct PlayerObj* arg0)
{
    arg0->x_pos.i.lo = 0;
    arg0->y_pos.i.lo = 0;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = FIXED(-1.5);
    arg0->unk2C = 0;
    arg0->x_pos.u.hi = (arg0->x_pos.u.hi & 0xFFF0) + 8;
    func_80036034(arg0);
    arg0->unk5 = 0x10;
    arg0->unk6 = 0;
}

INCLUDE_ASM("main/nonmatchings/player", func_80034E2C);

void func_80034F7C(struct PlayerObj* arg0)
{
    u8 flags;
    u8 sound_id;
    u8 sound_arg;

    func_80036088(arg0);
    func_80038490(arg0);

    flags = engine_obj.unkF;
    engine_obj.unk1C = 1;

    if (flags & 0x10) {
        func_80036534(arg0);
        func_80036E98(arg0);

        sound_id = 0x21;
        if (arg0->unk2 == 0) {
            sound_id = 0x22;
            sound_arg = 0x75;
        } else {
            sound_arg = 0x72;
        }
        func_8001663C(sound_id, sound_arg);

        arg0->unk5 = 0x19;
        arg0->unk6 = 0;
        return;
    }

    if (flags & 0x40) {
        arg0->state = 3;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        return;
    }

    func_800350A4(arg0, 3);
    func_80036E98(arg0);
    func_80035048(arg0);
}

void func_80035048(struct PlayerObj* arg0)
{
    func_8001540C(1, 0xB, arg0);
    arg0->y_vel.val = FIXED(8);
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk68 = 0;
    arg0->unk67 = 1;
    arg0->unk5 = 1;
    arg0->unk6 = 0;
}

s32 func_800350A4(struct PlayerObj* arg0, s32 arg1)
{
    if (arg0->unk2 == 0) {
        arg0->unk3C = (s32)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[0];
    } else if (D_8011AF60[arg1] == 0) {
        arg0->unk38 = (s32*)((s32)SP_PLAYER_GFX + SP_PLAYER_GFX[0]);
        arg0->unk3C = (s32)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[0];
    } else {
        arg0->unk38 = (s32*)((s32)SP_PLAYER_GFX + SP_PLAYER_GFX[1]);
        arg0->unk3C = (s32)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[5];
    }

    return func_80015D60(arg0, arg1);
}

void func_8003516C(struct PlayerObj* arg0, s32 arg1, s32 arg2)
{
    s32* temp_v0;
    s32* temp_v0_2;
    s32* temp_v0_3;
    s32* temp_v1;
    s32* temp_v1_2;
    s32* temp_v1_3;
    if (arg0->unk2 == 0) {
        temp_v0 = SP_PLAYER_GFX;
        temp_v1 = SP_SPRITE_FRAMES;
        arg0->unk38 = SP_ARCHIVE_ENTRY(temp_v0, 0);
        arg0->unk3C = SP_ARCHIVE_ENTRY(temp_v1, 0);
    } else if (D_8011AF60[arg1] == 0) {
        temp_v0_2 = SP_PLAYER_GFX;
        temp_v1_2 = SP_SPRITE_FRAMES;
        arg0->unk38 = SP_ARCHIVE_ENTRY(temp_v0_2, 0);
        arg0->unk3C = SP_ARCHIVE_ENTRY(temp_v1_2, 0);
    } else {
        temp_v0_3 = SP_PLAYER_GFX;
        temp_v1_3 = SP_SPRITE_FRAMES;
        arg0->unk38 = SP_ARCHIVE_ENTRY(temp_v0_3, 1);
        arg0->unk3C = SP_ARCHIVE_ENTRY(temp_v1_3, 5);
    }

    func_80015D90(ANIMATED_OBJECT(arg0), arg1, arg2);
}

extern s16 D_800F8B3C[];

void func_80035240(void)
{
    struct PlayerObj* player = &g_Player;
    struct EngineObj* engine = &engine_obj;
    struct UnkObj* object;
    struct UnkObj* active_object;
    struct UnkObj* previous;
    struct BazObj* baz;
    struct VisualObj* visual;
    struct MiscObj* misc;
    s32* sprite_frames;
    s8* initial_data;
    s8* player_data;
    s32 frame_offset;
    u32 i;

    player->active = 1;
    player->unk2 = engine->cur_character;
    player->on_screen = 0;
    player->bg_offset = 0;
    player->unkD9 = 0;
    player->unkB9 = engine->palette_flags;

    switch (engine->unk1E) {
    case 0:
        i = 0;
    case -2:
        i = 0;
        player->unk5C = engine->unk46;
        player->unk5D = engine->unk46;
        player->unk5E = engine->unk46;
        do {
            player->charge_levels[i++] = 0x30;
        } while (i < 0x10);
        break;

    case -1:
        player_data = player->charge_levels;
        initial_data = engine->player_initial_data;
        i = 0;
        player->unk5C = engine->unk45;
        player->unk5D = engine->unk45;
        player->unk5E = engine->unk45;
        do {
            *player_data++ = *initial_data++;
            i++;
        } while (i < 0x10);
        player->unk93 = engine->unk60;
        func_800371E4(player);
        func_80037104(player);
        break;
    }

    if (player->unk2 == 0) {
        player->animation_table = D_80119DF0;
    } else {
        player->animation_table = D_8011AFF0;
    }

    player->unk38 = (s32*)((u8*)SP_PLAYER_GFX + SP_PLAYER_GFX[0]);
    player->unk3C = (u8*)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[0];
    player->unk40 = 0x500;
    player->unk16 = 2;
    player->unk42 = 0x7800;
    player->unk49 = 3;
    func_800361F8(player);
    func_800355C0();

    i = 0;
    active_object = foo_objects;
    object = foo_objects;
    do {
        active_object->active = 0x11;
        object->unk2 = i;
        object->bg_offset = player->bg_offset;
        object->unk38 = player->unk38;
        object->unk3C = player->unk3C;
        object->unk40 = player->unk40;
        object->unk42 = D_800F8B3C[object->unk2];
        object->unk16 = 4;
        if (i != 0) {
            object->link.previous = previous;
        } else {
            object->link.player = &g_Player;
        }
        previous = object;
        object++;
        i++;
        active_object++;
    } while (i < 3);

    baz = baz_objects;
    i = 0;
    do {
        baz->active = 0x21;
        baz->unk2 = i;
        baz->bg_offset = player->bg_offset;
        baz->unk38 = 0;
        sprite_frames = SP_SPRITE_FRAMES;
        frame_offset = sprite_frames[1];
        baz->unk3C = (u8*)sprite_frames + frame_offset;
        baz->animation_table = D_8011BF40;
        baz->unk40 = 0;
        baz->unk42 = 0x7800;
        baz->unk16 = 2;
        baz->unk15 = 0;
        baz++;
    } while (++i < 2);

    if (engine->stage == 1) {
        i = 0;
        do {
            visual = find_free_visual_obj();
            if (visual != 0) {
                visual->active = 0x41;
                visual->id = 7;
                visual->unk2 = i;
            }
            i++;
        } while (i < 4);
    }

    if (player->unk2 == 0) {
        misc = find_free_misc_obj();
        if (misc != 0) {
            misc->active = 0x21;
            misc->id = 0x36;
        }
    }

    background_objects[0].unk44 = 0;
    background_objects[1].unk44 = 0;
    background_objects[2].unk44 = 0;
}

void func_800355C0(void)
{
    struct PlayerObj* entity = &g_Entity;

    reset_entity(entity);
    entity->unkD9 = 1;
    entity->animation_table = D_80119DF0;
    entity->unk50 = 0;
    entity->unk54 = 0;
    entity->unk68 = NULL;
    entity->unk5C = engine_obj.unk46;
    entity->unk5D = engine_obj.unk46;
    entity->unk5E = engine_obj.unk46;
    entity->unk38 = (s32*)((u8*)SP_PLAYER_GFX + SP_PLAYER_GFX[0]);
    entity->unk3C = (u8*)SP_PLAYER_GFX + SP_PLAYER_GFX[0];
    entity->unk40 = 0x540;
    entity->unk16 = 2;
    entity->unk42 = 0x7800;
    entity->unk49 = 1;
}

void func_80035694(struct PlayerObj* arg0)
{
    struct EngineObj* engine = &engine_obj;
    s32 var_a0;

    if (arg0->unkD9 != 0) {
        arg0->on_screen = 1;
        func_800350A4(arg0, 0x61);
        arg0->unk5 = 0x24;
        arg0->state++;
        return;
    }
    if (engine->unk1E != 0) {
        arg0->on_screen = 1;
        engine->unk1F = 1;
        var_a0 = 0;
        switch (engine->stage) {
        case 3:
            if (engine->unk1E == -1 && engine->checkpoint != 0) {
                var_a0 = 1;
            }
            break;
        case 5:
            var_a0 = 2;
            if (engine->substage != 0) {
                if (engine->checkpoint == 0) {
                    var_a0 = 2;
                } else {
                    var_a0 = 0;
                }
            }
            break;
        case 6:
            if (engine->unk1E == -1) {
                var_a0 = 1;
            }
            break;
        case 12:
            if (engine->substage == 0) {
                if (engine->checkpoint >= 2) {
                    var_a0 = 1;
                }
            } else if (engine->checkpoint == 0) {
                var_a0 = 1;
            }
            break;
        }
        arg0->state++;
        D_800F8B44[var_a0](arg0);
    }
}

void func_80035848(struct PlayerObj* arg0)
{
    func_800350A4(arg0, 1);
    func_8001540C(1, 0xD, arg0);
    arg0->y_vel.val = FIXED(-8);
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = -1;
    arg0->unk5 = 0;
}

INCLUDE_ASM("main/nonmatchings/player", func_800358A4);

void func_80035A24(struct PlayerObj* arg0)
{
    qux_object.active = 1;
    arg0->unkA7 = engine_obj.unk47;
    arg0->unkB8 = engine_obj.unk48;
    arg0->unkC5 = -1;
    arg0->unkD4 = 0x29;
    arg0->unk67 = 1;
    arg0->unk5 = 0x12;
    arg0->unk6 = 1;
}

void func_80035A6C(struct PlayerObj* arg0)
{
    D_800F8B94[arg0->unk5](arg0);
}

void func_80035AA8(struct PlayerObj* arg0)
{
    func_80015930(1, 5);
    func_80015930(1, 7);
    if (arg0->unkC5 != 0) {
        arg0->on_screen = 0;
        arg0->unkC7 = 1;
    } else {
        engine_obj.unk12 = 1;
        engine_obj.unk13 = 1;
        engine_obj.unk14 = 1;
        engine_obj.unk15 = 1;
        engine_obj.unk16 = 1;
        engine_obj.unk17 = 1;
        engine_obj.unk18 = 1;
        engine_obj.unk19 = 1;
        engine_obj.unk1A = 1;
        arg0->unkC7 = 8;
        func_800350A4(arg0, 0x21);
    }
    arg0->unk5 = (u8)arg0->unk5 + 1;
}

void func_80035B6C(struct PlayerObj* arg0)
{
    if (--arg0->unkC7 == 0) {
        engine_obj.unk12 = 0;
        engine_obj.unk13 = 0;
        engine_obj.unk14 = 0;
        engine_obj.unk15 = 0;
        engine_obj.unk16 = 0;
        engine_obj.unk17 = 0;
        engine_obj.unk18 = 0;
        engine_obj.unk19 = 0;
        engine_obj.unk1A = 0;
        arg0->on_screen = 0;
        func_8001540C(3, 0xC, arg0);
        arg0->unkC7 = 0;
        arg0->unkC6 = 0;
        arg0->unk5 = (u8)arg0->unk5 + 1;
        func_80035C20(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/player", func_80035C20);

void func_80035D00(struct PlayerObj* arg0)
{
    if (arg0->unkC7 != 0) {
        arg0->unkC7--;
        return;
    }
    arg0->state = 3;
    arg0->unk5 = 0;
}

void func_80035D34(s8 arg0)
{
    struct MiscObj* obj;

    obj = find_free_misc_obj();
    if (obj != NULL) {
        obj->active = 0x21;
        obj->id = 0x11;
        obj->unk2 = arg0;
        obj->state = 0;
        obj->unk5 = 0;
        obj->unk6 = 0;
    }
}

void func_80035D84(s8 arg0)
{
    const s8* entry;
    const s8* end;
    s32 index;
    const s8* table;

    index = arg0;
    table = (const s8*)D_800F8BA4;
    index *= 8;
    entry = table + index;
    end = entry + 8;

    do {
        func_80035D34(*entry++);
    } while (entry < end);
}

void func_80035DDC(struct PlayerObj* arg0)
{
}

void func_80035DE4(struct PlayerObj* arg0)
{
    u8 var_v0_2;
    u8 temp_v0;

    if (arg0->unk2 == 0) {
        if (arg0->unkD9 == 0) {
            temp_v0 = D_801193F0[arg0->animation_step.fields.frame_index];
            if (D_801193F0[arg0->animation_step.fields.frame_index] != 0) {
                arg0->unk54 = &D_801194F0[temp_v0];
                return;
            }
        }
        arg0->unk54 = NULL;
        return;
    }
    if (D_8011AF60[arg0->unk17] == 0) {
        var_v0_2 = D_8011A030[arg0->animation_step.fields.frame_index];
    } else {
        var_v0_2 = D_8011A130[arg0->animation_step.fields.frame_index];
    }
    if (var_v0_2 == 0) {
        arg0->unk54 = NULL;
        return;
    }
    arg0->unk54 = &D_8011A230[var_v0_2];
}

void func_80035EA4(struct PlayerObj* arg0)
{
    if (arg0->unkC5 < 0) {
        arg0->unk68 = NULL;
        return;
    }
    if (arg0->unk2 == 0) {
        arg0->unk68 = &D_800F8BC4;
        return;
    }
    arg0->unk68 = &D_800F8BC8;
}

void func_80035EF0(void)
{
    if (g_Player.unkDE == 0) {
        g_Player.input.buttons.held = func_80035FC4(D_80166C08);
        g_Player.input.buttons.previous = func_80035FC4(D_80166C0A);
        g_Player.pressed_input = func_80035FC4(controller_state);
        return;
    }
    g_Player.input.buttons.held = 0;
    g_Player.input.buttons.previous = 0;
    g_Player.pressed_input = 0;
    g_Entity.input.buttons.held = func_80035FC4(D_80166C08);
    g_Entity.input.buttons.previous = func_80035FC4(D_80166C0A);
    g_Entity.pressed_input = func_80035FC4(controller_state);
}

s32 func_80035FC4(s32 arg0)
{
    u16 result = 0;
    u32 var_a3 = 1;
    u32 var_i = 0;

    for (var_i = 0; var_i < 16; var_i++) {
        if (D_800EE430[var_i] & arg0) {
            result |= var_a3;
        }
        var_a3 *= 2;
    }

    if ((result & 3) == 3) {
        result &= ~0x3;
    }

    if ((result & 0xC) == 0xC) {
        result &= ~0xC;
    }

    return result;
}

void func_80036034(struct PlayerObj* arg0)
{
    arg0->unk84 = 0;
    arg0->unk86 = 0;
    if (arg0->unk8C > 0) {
        arg0->unk8C = -1;
    }
}

void func_80036054(struct PlayerObj* arg0)
{
    arg0->unk8E = 0;
    arg0->unk8F = 0;
    arg0->unk90 = 0;
    arg0->unk91 = 0;
    arg0->unk92 = 0;
    arg0->unkA2 = 0;
    func_800361F8(arg0);
}

void func_80036088(struct PlayerObj* arg0)
{
    arg0->unk84 = 0;
    arg0->unk86 = 0;
    arg0->unk8C = 0;
    func_80036054(arg0);
}

void func_800360B0(struct PlayerObj* arg0)
{
    arg0->unkA1 = 0;
}

void func_800360B8(struct PlayerObj* arg0)
{
    s8 temp_v1 = arg0->unk5; // likely fake
    if ((arg0->unk5 != 0) && (temp_v1 != 1) && (arg0->unkA4 <= 0)) {
        if (arg0->unkA2 != 0) {
            if (--arg0->unkA2 == 0) {
                func_800361F8(arg0);
            }
        }
        if (arg0->unkA4 < 0) {
            arg0->unkA1 = 0x23;
        }
        if (arg0->unkA1 != 0) {
            if (arg0->unk9F != 0) {
                arg0->unk9F--;
            } else {
                if (arg0->unkA0 == 0) {
                    func_800362F8(arg0, arg0->unkA1);
                } else {
                    func_800361F8(arg0);
                }
                arg0->unk9F = 1;
                arg0->unkA0 ^= 1;
            }
            arg0->unkA1 = 0;
        }
    }
}

void func_800361B0(struct PlayerObj* arg0, s32 arg1, s32 arg2)
{
    u16* var_a0;
    u16* var_v1;
    u32 var_a3;

    var_a0 = SP_PALETTE_BANK[arg1];
    var_v1 = SP_PALETTES[arg2];

    for (var_a3 = 0; var_a3 < 16; var_a3++) {
        *var_v1++ = *var_a0++;
    }
}

void func_800361F8(struct PlayerObj* arg0)
{
    u16* var_a0;
    u16* var_v1;
    u32 a2;
    s32 temp;

    if (arg0->unk2 == 0) {
        if (arg0->unkD9 == 0) {
            if (arg0->unk93 == 0) {
                func_800362F8(arg0, 0);
            } else {
                temp = ((arg0->unk93 - 1) << 6);
                var_a0 = SP_PALETTE;
                var_v1 = SP_PALETTE_BANK[3] + temp;
                for (a2 = 0; a2 < 0x20; a2++) {
                    *var_a0++ = *var_v1++;
                }
                var_a0 = SP_PALETTE + 0x130;
                for (a2 = 0; a2 < 0x20; a2++) {
                    *var_a0++ = *var_v1++;
                }
            }
            need_palette_load |= 1;
        }
    } else {
        if (engine_obj.unk37) {
            func_800361B0(arg0, 0xD, 0);
        } else {
            func_800361B0(arg0, 0, 0);
        }
        need_palette_load |= 1;
    }
}

void func_800362F8(struct PlayerObj* arg0, s32 arg1)
{
    u16* var_a0;
    u16* var_v1;
    u32 var_a2;

    if (arg0->unk2 == 0) {
        if (arg0->unkD9 == 0) {
            var_a0 = SP_PALETTE;
            var_v1 = SP_PALETTE_BANK[arg1];
            for (var_a2 = 0; var_a2 < 0x10; var_a2++) {
                *var_a0++ = *var_v1++;
            }
            var_a0 = SP_PALETTE + 0x130;
            for (var_a2 = 0; var_a2 < 0x20; var_a2++) {
                *var_a0++ = *var_v1++;
            }
            need_palette_load |= 1;
        }
    } else {
        func_800361B0(arg0, arg1, 0);
        need_palette_load |= 1;
    }
}

void func_800363B8(struct PlayerObj* arg0, u8 arg1)
{
    if (arg0->unkD7 <= 0) {
        func_8001540C(3, arg1, arg0);
    }
}

void func_800363EC(struct PlayerObj* arg0)
{
    if (arg0->unkD7 == 0 && arg0->unk5C < (engine_obj.unk46 / 3)) {
        func_8001540C(3, 0xB, 0);
        arg0->unkD7 = 0x78;
    }
}

void func_80036470(s8 arg0)
{
    struct PlayerObj* player;
    u8 amount;
    s8 value;

    player = &g_Player;
    g_Player.unkBA = -1;
    if (arg0 != 0) {
        if (g_Player.unkA7 & 2) {
            if (arg0 < 3) {
                amount = 1;
            } else {
                amount = (arg0 / 3) * 2;
            }
            player->unk5C = (u8)(player->unk5C - amount);
        } else {
            g_Player.unk5C = (u8)(g_Player.unk5C - arg0);
        }
    }
    if (player->unk5C > 0) {
        value = player->unk5C | 0x80;
    } else {
        value = -0x80;
        player->unkBA = 0;
    }
    player->unk5C = value;
}

void func_80036534(struct PlayerObj* arg0)
{
    if (arg0->unk5C >= (engine_obj.unk46 / 3)) {
        func_800350A4(arg0, 5);
    } else {
        func_800350A4(arg0, 6);
    }
}

void func_800365A4(struct PlayerObj* arg0)
{
    if (!arg0->unkC3 && (arg0->input.buttons.held & 3)) {
        if (arg0->input.buttons.held & 1) {
            arg0->unk15 = 0x40;
            if (!(arg0->unk88.bytes.collision_flags & 1)) {
                if (arg0->unk84 != 0) {
                    arg0->x_vel.val = FIXED(4.125);
                } else {
                    arg0->x_vel.val = FIXED(2);
                }
            } else {
                arg0->x_vel.val = 0;
            }
        } else {
            arg0->unk15 = 0;
            if (!(arg0->unk88.bytes.collision_flags & 2)) {
                if (arg0->unk84 != 0) {
                    arg0->x_vel.val = FIXED(-4.125);
                } else {
                    arg0->x_vel.val = FIXED(-2);
                }
            } else {
                arg0->x_vel.val = 0;
            }
        }
    } else {
        arg0->x_vel.val = 0;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
}

void func_8003666C(struct PlayerObj* arg0)
{
    struct VisualObj* visual_obj;
    u8 bg_offset;

    visual_obj = find_free_visual_obj();
    if (visual_obj != NULL) {
        visual_obj->active = 0x21;
        visual_obj->id = 1;
        bg_offset = arg0->bg_offset;
        visual_obj->state = 0;
        visual_obj->unk5 = 0;
        visual_obj->unk6 = 0;
        visual_obj->bg_offset = bg_offset;
    }
}

INCLUDE_ASM("main/nonmatchings/player", func_800366C0);

INCLUDE_ASM("main/nonmatchings/player", func_800367F8);

extern f32 D_800F8BD8[];

void func_8003698C(struct PlayerObj* arg0)
{
    s16 x_pos;
    s32 frame_offset;
    u8 facing;
    struct VisualObj* visual_obj;
    s32* sprite_frames;

    visual_obj = find_free_visual_obj();
    if (visual_obj != 0) {
        visual_obj->active = 0x21;
        visual_obj->id = 3;
        visual_obj->unk2 = 1;
        visual_obj->bg_offset = arg0->bg_offset;
        visual_obj->state = 0;
        visual_obj->unk5 = 0;
        visual_obj->unk6 = 0;
        sprite_frames = SP_SPRITE_FRAMES;
        visual_obj->unk38 = 0;
        frame_offset = sprite_frames[1];
        visual_obj->animation_table = D_8011BF40;
        visual_obj->unk40 = 0;
        visual_obj->unk42 = 0x7802;
        visual_obj->unk16 = 0;
        visual_obj->unk3C = (u8*)sprite_frames + frame_offset;
        facing = arg0->unk15;
        visual_obj->unk15 = facing;
        if (facing == 0) {
            x_pos = arg0->x_pos.u.hi + D_800F8BD8[arg0->unk2].u.lo;
        } else {
            x_pos = arg0->x_pos.u.hi - D_800F8BD8[arg0->unk2].u.lo;
        }
        visual_obj->x_pos.i.hi = x_pos;
        visual_obj->y_pos.i.hi = arg0->y_pos.u.hi + D_800F8BD8[arg0->unk2].u.hi;
    }
}

void func_80036A94(struct PlayerObj* arg0)
{
    struct VisualObj* visual_obj;
    u8 bg_offset;

    visual_obj = find_free_visual_obj();
    if (visual_obj != NULL) {
        visual_obj->active = 0x21;
        visual_obj->id = 0;
        bg_offset = arg0->bg_offset;
        visual_obj->state = 0;
        visual_obj->unk5 = 0;
        visual_obj->unk6 = 0;
        visual_obj->bg_offset = bg_offset;
    }
}

void func_80036AE4(s8 arg0, s8 arg1)
{
    g_Player.unkC0 = 1;
    g_Player.unkC1 = arg0;
    g_Player.unkC2 = arg1;
    g_Player.unk7A = 1;
    engine_obj.unk1C = 1;
}

void func_80036B18(void)
{
    g_Player.unkC0 = 0;
    g_Player.unk7A = 0;
    engine_obj.unk1C = 0;
}

void func_80036B38(struct PlayerObj* arg0)
{
    if (func_8002D994(arg0) == 0x24) {
        s16 y = arg0->y_pos.u.hi & 0xFFF0;
        func_80036BF4(arg0, y);
    }
}

void func_80036B88(struct PlayerObj* arg0)
{
    if (func_8002D900(arg0) == 0x24) {
#ifdef MMX4_PC
        s16 temp = arg0->y_pos.i.hi;

        if (arg0->unk68 != NULL)
            temp += arg0->unk68->unk1 + arg0->unk68->unk3;
#else
        s16 temp = arg0->y_pos.i.hi + arg0->unk68->unk1 + arg0->unk68->unk3;
#endif
        func_80036BF4(arg0, temp & ~0xF);
    }
}

INCLUDE_ASM("main/nonmatchings/player", func_80036BF4);

struct WeaponObj* func_80036DA0(s8 active, s8 id, s8 type, struct PlayerObj* owner)
{
    struct WeaponObj* weapon = find_free_weapon_obj();

    if (weapon == NULL) {
        return NULL;
    }

    weapon->active = active;
    weapon->id = id;
    weapon->unk2 = type;
    weapon->bg_offset = g_Player.bg_offset;
    if (owner != NULL) {
        weapon->owner = owner;
    }
    return weapon;
}

struct VisualObj* func_80036E1C(s8 arg0, s8 arg1, s8 arg2, void* arg3)
{
    struct VisualObj* visual_obj = find_free_visual_obj();

    if (visual_obj == NULL) {
        return NULL;
    }

    visual_obj->active = arg0;
    visual_obj->id = arg1;
    visual_obj->unk2 = arg2;
    visual_obj->bg_offset = g_Player.bg_offset;
    if (arg3) {
        visual_obj->unk50 = arg3;
    }
    return visual_obj;
}

void func_80036E98(struct PlayerObj* arg0)
{
    if (arg0->unk2 == 0) {
        arg0->unk93 = 0;
        arg0->unkA6 = 0;
        func_800384DC(arg0);
        func_80037104(arg0);
        func_800371E4(arg0);
    }
}

void func_80036EE8(struct PlayerObj* arg0)
{
    s8 temp_s0;

    if (arg0->unk2 == 0) {
        temp_s0 = arg0->unk93;
        func_80036F50(arg0);
        func_80037104(arg0);
        if (temp_s0 != arg0->unk93) {
            func_800371E4(arg0);
        }
    }
}

INCLUDE_ASM("main/nonmatchings/player", func_80036F50);

void func_80037104(struct PlayerObj* arg0)
{
    if (arg0->unkD9 != 0) {
        arg0->unk94[0] = 0;
        arg0->unk94[1] = 0;
        return;
    }
    arg0->unk94[0] = arg0->unk93;
    if (arg0->unk93 != 0) {
        if (arg0->charge_state[0] == PLAYER_CHARGE_FULL) {
            arg0->unk94[0] += 9;
        }
    } else {
        func_8003718C(arg0, 0);
    }
    arg0->unk94[1] = 0;
    func_8003718C(arg0, 1);
}

void func_8003718C(struct PlayerObj* arg0, s32 arg1)
{
    if (arg0->unkA6 != 0) {
        arg0->unk94[arg1] = 0x13;
        return;
    }

    if (arg0->charge_state[arg1] != PLAYER_CHARGE_NONE) {
        if (arg0->charge_state[arg1] == PLAYER_CHARGE_PARTIAL) {
            arg0->unk94[arg1] = 9;
        } else if (arg0->unkB8 == 0) {
            arg0->unk94[arg1] = 0x12;
        } else {
            arg0->unk94[arg1] = 0x14;
        }
    }
}

void func_800371E4(struct PlayerObj* arg0)
{
    func_800361F8(arg0);
    if (arg0->unk93 == 5) {
        func_80036E1C(1, 0x1B, 0, 0);
    }
    if (arg0->unk93 == 6) {
        func_80036E1C(1, 0x12, 0, 0);
        func_80036DA0(1, 6, 3, 0);
        arg0->weapon_06_slots[0] = 0;
        arg0->weapon_06_slots[1] = 0;
        arg0->weapon_06_slots[2] = 0;
    }
    if (arg0->unk93 == 8) {
        func_80036E1C(1, 0x1B, 1, 0);
    }
}

s32 func_80037290(struct PlayerObj* arg0)
{
    if (arg0->unkC3 != 0) {
        return 0;
    }

    if (arg0->unk2 != 0) {
        return 0;
    }

    if (func_800375B4(arg0) != 0) {
        return 1;
    }

    func_80037708(arg0);

    if (arg0->unk8F == 0) {
        return 0;
    }

    if (D_800F8BF8[arg0->unk96] == 0) {
        return 0;
    }

    arg0->unk84 = 0;
    arg0->unk86 = 0;
    arg0->unk8C = 0;
    func_80037484(arg0, 0);

    return 1;
}

s32 func_80037338(struct PlayerObj* arg0)
{
    if (arg0->unkC3 != 0 || arg0->unk2 != 0) {
        return 0;
    }

    if (func_800375B4(arg0) != 0) {
        return 1;
    }

    func_80037708(arg0);

    if (arg0->unk8F == 0) {
        return 0;
    }

    if (D_800F8BF8[arg0->unk96] == 0) {
        return 0;
    }

    arg0->unk84 = 0;
    arg0->unk8C = 0;
    func_80037484(arg0, 1);
    return 1;
}

s32 func_800373DC(struct PlayerObj* arg0)
{
    if (arg0->unkC3 != 0 || arg0->unk2 != 0) {
        return 0;
    }
    if (func_800375B4(arg0) != 0) {
        return 1;
    }
    func_80037708(arg0);
    if (arg0->unk8F == 0) {
        return 0;
    }
    if (D_800F8BF8[arg0->unk96] == 0) {
        func_800387A8(arg0);
    } else {
        arg0->unk8C = 0;
        func_80037484(arg0, 1);
    }
    return 1;
}

INCLUDE_ASM("main/nonmatchings/player", func_80037484);

s32 func_8003751C(struct PlayerObj* arg0)
{
    if (!(arg0->unkA7 & 8)) {
        return 0;
    }
    if (!(arg0->pressed_input & 0x80)) {
        return 0;
    }
    func_80038524(arg0, 0x15);
    arg0->unk86 = 4;
    arg0->unkD5 = 0xB4;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk84 = 0;
    arg0->unk8C = 0;
    arg0->unkD6 = 0;
    arg0->unk5 = 0x21;
    arg0->unk6 = 0;
    return 1;
}

s32 func_800375B4(struct PlayerObj* arg0)
{
    s32 var_v1;

    if (arg0->unk92 || !(arg0->unkA7 & 2) || arg0->charge_levels[0] != 0x30 || arg0->unk86) {
        return 0;
    }

    var_v1 = 2;
    if (arg0->unk15) {
        var_v1 = 1;
    }
    if ((var_v1 & arg0->unk88.bytes.collision_flags) || !(arg0->pressed_input & 0x40)) {
        return 0;
    }

    func_800350A4(arg0, 0x6A);
    func_80036054(arg0);
    func_80036E98(arg0);
    arg0->unk84 = 0;
    arg0->unk86 = 5;
    arg0->unk8C = 0;
    arg0->unk61 = 0;
    arg0->unkA4 = 0;
    arg0->unk67 = 1;
    if (engine_obj.unk37 == 0) {
        arg0->charge_levels[0] = 0;
    }
    arg0->unk7A = 1;
    arg0->unkE0 = 1;
    arg0->unkE1 = 0x18;
    engine_obj.unk1C = 1;

    if (arg0->unk15) {
        arg0->x_vel.val = FIXED(2.5);
    } else {
        arg0->x_vel.val = FIXED(-2.5);
    }
    arg0->y_vel.val = FIXED(3.5);
    arg0->unk2C = 0x4200;
    arg0->unk28 = 0;
    arg0->unk5 = 0x22;
    arg0->unk6 = 0;

    return 1;
}

void func_80037708(struct PlayerObj* arg0)
{
    s8 temp_s1;

    if (arg0->unk92 == 0) {
        arg0->unk96 = -1;
        func_8003795C(arg0);
        func_80037A24(arg0);
        temp_s1 = arg0->unk96;
        if (arg0->unk96 != -1 && arg0->unk98 < D_800F8CCC[arg0->unk96] && (D_800F8CE4[arg0->unk96] == 0 || arg0->unk99 == 0)) {
            if ((D_800F8C28[arg0->unk96] == 0 || arg0->unk99 == 0 || arg0->unk97 != arg0->unk96)) {
                if ((temp_s1 != 6 || arg0->unk99 != 0)) {
                    D_800F8C78[temp_s1](arg0);
                    arg0->unk97 = temp_s1;
                    arg0->unk8E = 1;
                    arg0->unk8F = 1;
                    arg0->unk90 = 0;
                    arg0->unk91 = D_800F8C4C[temp_s1].first;
                    arg0->unk92 = D_800F8C4C[temp_s1].second;
                    if (D_800F8CFC[temp_s1] != 0) {
                        arg0->unk98++;
                    }
                    if (D_800F8D14[temp_s1] != 0) {
                        arg0->unk99++;
                    }
                    if (++arg0->unk9A == 3) {
                        arg0->unk9A = 0;
                    }
                    if (temp_s1 == 0x13) {
                        arg0->unkA6--;
                    }
                    func_80037B1C(arg0, temp_s1);
                    if (arg0->unkD9 == 0 && arg0->unk93 == 0 && arg0->unkA4 == 0) {
                        if (temp_s1 == 0) {
                            arg0->unkA2 = 6;
                        }
                        if (temp_s1 == 9) {
                            arg0->unkA2 = 5;
                        }
                        if (temp_s1 == 0x12) {
                            arg0->unkA2 = 7;
                        }
                    }
                }
            }
        }
    }
}

void func_8003795C(struct PlayerObj* arg0)
{
    if (arg0->pressed_input & 0x10) {
        if (arg0->unk93 != 0) {
            arg0->unkA6 = 0;
            if (func_80037A98(arg0) == 0) {
                return;
            }
        }
        arg0->unk96 = arg0->unk94[0];
    } else if ((arg0->input.history & 0x100010) == 0x100000) { // flags?
        s8 temp = arg0->unk94[0];
        if ((temp != 0) && (D_800F8C10[temp] == 0) && (temp != 0x13)) {
            if (arg0->unk93 != 0) {
                arg0->unkA6 = 0;
                if (func_80037A98(arg0) == 0) {
                    return;
                }
            }
            arg0->unk96 = arg0->unk94[0];
        }
    }
}

void func_80037A24(struct PlayerObj* arg0)
{
    if (arg0->unk96 == -1) {
        if (arg0->pressed_input & 0x20) {
            arg0->unk96 = arg0->unk94[1];
            return;
        }
        if ((arg0->input.history & 0x200020) == 0x200000) {
            if ((arg0->unk94[1] != 0) && (arg0->unk94[1] != 0x13)) {
                arg0->unk96 = arg0->unk94[1];
            }
        }
    }
}

s32 func_80037A98(struct PlayerObj* arg0)
{
    s8 charge_level;
    s8 charge_type;

    charge_level = arg0->charge_levels[arg0->unk93];
    if (charge_level == 0) {
        return 0;
    }

    charge_type = arg0->unk94[0];
    if (D_800F8C10[charge_type] != 0 && (arg0->unkA7 & 1) != 0) {
        return 1;
    }

    return charge_level >= D_800F8BE0.charge.animation_indices[charge_type];
}

void func_80037B1C(struct PlayerObj* arg0, s8 arg1)
{
    s8 animation_cost;

    animation_cost = D_800F8BE0.charge.animation_indices[arg1];
    if ((animation_cost != 0) && ((D_800F8C10[arg1] == 0) || !(arg0->unkA7 & 1))) {
        arg0->charge_levels[arg0->unk93] -= animation_cost;
    }
}

void func_80037B90(struct PlayerObj* arg0)
{
}

void func_80037B98(struct PlayerObj* arg0)
{
    func_80036DA0(1, arg0->unk96, 0, arg0);
}

void func_80037BC4(struct PlayerObj* arg0)
{
    func_80036E1C(0x21, 2, arg0->unk96, 0);
    if ((arg0->unk96 == 0x12) && (get_random() & 1)) {
        func_800363B8(arg0, 8);
    }
}

INCLUDE_ASM("main/nonmatchings/player", func_80037C28);

void func_80037D08(struct PlayerObj* arg0)
{
    s8 i;
    struct PlayerObj* player;
    struct WeaponObj* weapon;
    struct WeaponObj* first_weapon;

    player = arg0;
    i = 0;
    do {
        weapon = find_free_weapon_obj();
        if (weapon != 0) {
            weapon->active = 1;
            weapon->id = player->unk96;
            weapon->unk2 = i;
            weapon->bg_offset = player->bg_offset;
            if (i == 0) {
                first_weapon = weapon;
            } else {
                weapon->owner = (struct PlayerObj*)first_weapon;
            }
        }
        i++;
    } while (i < 9);
}

void func_80037DB0(struct PlayerObj* arg0)
{
    func_800350A4(arg0, 0x5F);
    func_800363B8(arg0, 5);
    arg0->unk67 = 1;
    arg0->unk5 = 0x26;
    arg0->unk6 = 0;
}

void func_80037DFC(struct PlayerObj* player)
{
    func_800350A4(player, 0x60);
    player->unkDE = 1;
    player->unk7A = 1;
    player->unk67 = 1;
    player->unk61 = 0;
    player->unkA4 = 0;
    player->unk5 = 0x23;
    player->unk6 = 0;
}

void func_80037E4C(struct PlayerObj* arg0, s32 arg1)
{
    if (arg1 == 0) {
        func_800350A4(arg0, 0x63);
    } else {
        func_800350A4(arg0, 0x64);
    }
    func_800363B8(arg0, 7);
    arg0->unk67 = 1;
    arg0->unk5 = 0x27;
    arg0->unk6 = 0;
}

void func_80037EAC(struct PlayerObj* arg0, s32 arg1)
{
    struct WeaponObj* weapon;

    if (arg1 == 0) {
        func_800350A4(arg0, 0x65);
        weapon = func_80036DA0(1, 0xD, 0, NULL);
        if (weapon != NULL) {
            func_80036E1C(1, 0x1A, 2, weapon);
        }
    } else {
        func_800350A4(arg0, 0x66);
        weapon = func_80036DA0(1, 0xD, 1, NULL);
        if (weapon != NULL) {
            func_80036E1C(1, 0x1A, 3, weapon);
        }
    }

    func_800363B8(arg0, 7);
    arg0->unk67 = 1;
    arg0->unk7A = 1;
    arg0->unk5 = 0x28;
    arg0->unk6 = 0;
    arg0->unk98++;
    arg0->unk99++;
}

void func_80037F78(struct PlayerObj* arg0)
{
    if (arg0->unk96 == 7) {
        func_800350A4(arg0, 0x68);
        func_800363B8(arg0, 4);
    } else {
        func_800350A4(arg0, 0x69);
        func_800363B8(arg0, 8);
    }
    arg0->unk67 = 1;
    arg0->unk5 = 0x26;
    arg0->unk6 = 0;
}

void func_80037FF0(struct PlayerObj* arg0)
{
    s8 temp_v1; // probably fake

    if ((arg0->unk2 == 0) && (arg0->unkD9 == 0) && (arg0->unkE0 == 0) && (temp_v1 = arg0->unk5, (arg0->unk5 != 0)) && (arg0->unk5 != 1) && (arg0->unk5 != 0x19) && (temp_v1 != 0x18) && (arg0->unkC5 == 0)) {
        if (func_80038158(arg0) != 0) {
            func_800384DC(arg0);
            if (arg0->unkA2 != 0) {
                func_800362F8(arg0, 0x32);
                return;
            }
            func_800361F8(arg0);
            return;
        }
        func_800381FC(arg0);
        func_80038378(arg0);
        if (func_800380F0(arg0, 0) == 0) {
            func_800380F0(arg0, 1);
        }
    }
}

s32 func_800380F0(struct PlayerObj* arg0, s8 arg1)
{
    s8 temp_v1_2;
    if (arg0->charge_state[arg1] == PLAYER_CHARGE_NONE) {
        return 0;
    }
    if (arg0->charge_state[arg1] == PLAYER_CHARGE_PARTIAL) {
        arg0->unkA1 = 0x26;
    } else {
        temp_v1_2 = arg0->unk94[arg1];
        if (temp_v1_2 == 0x13) {
            arg0->unkA1 = 0x2C;
        } else {
            arg0->unkA1 = (temp_v1_2 == 0x14) ? 0x2F : 0x29;
        }
    }
    return 1;
}

s32 func_80038158(struct PlayerObj* arg0)
{
    if (arg0->pressed_input & 0x10) {
        return 1;
    }
    if (arg0->pressed_input & 0x20) {
        return 1;
    }
    if ((arg0->input.history & 0x100010) == 0x100000) {
        return 1;
    }
    if ((arg0->input.history & 0x200020) == 0x200000) {
        return 1;
    }
    if (arg0->unk9D && (arg0->input.buttons.held & 0x10) == 0) {
        return 1;
    }
    if (arg0->unk9E && !(arg0->input.buttons.held & 0x20)) {
        return 1;
    }
    return 0;
}

void func_800381FC(struct PlayerObj* arg0)
{
    u8 var_a1;
    u8* ptr = (u8*)arg0;

    if ((arg0->input.buttons.held & 0x10)
        && arg0->charge_state[0] != PLAYER_CHARGE_FULL
        && ((arg0->unk93 == 0) || ((arg0->unkA7 & 4) && (arg0->charge_levels[arg0->unk93] >= D_800F8BE0.charge.linked_thresholds[arg0->unk93])))) {
        arg0->unk9D = (u8)(arg0->unk9D + 1);
        if (arg0->unk93 == 0) {
            if (arg0->unkB8 == 0) {
                var_a1 = 0x5A;
            }
            if (arg0->unkB8 == 1) {
                var_a1 = 0x96;
            }
            if (arg0->unkB8 == 2) {
                var_a1 = 0x5A;
            }
        } else {
            var_a1 = 0x5A;
        }
        if (arg0->unk9D == 0x19) {
            func_8001540C(1, 7, arg0);
            arg0->charge_state[0] = PLAYER_CHARGE_PARTIAL;
            return;
        }
        if (arg0->unk9D == var_a1) {
            arg0->charge_state[0] = PLAYER_CHARGE_FULL;
        }
        if ((arg0->unk93 == 0) && (arg0->unkB8 == 1)) {
#ifndef VERSION_JP
            if (arg0->unkA6 != 4) {
#endif
                if (arg0->unk9D == 0x5A) {
                    if (arg0->unkA6 < 2) {
                        arg0->unkA6 = 2;
                    }
                }
                if (arg0->unk9D == 0x78) {
                    arg0->unkA6 = 3;
                }
                if (arg0->unk9D == 0x96) {
                    arg0->unkA6 = 4;
                }
#ifndef VERSION_JP
            }
#endif
        }
    }
}

void func_80038378(struct PlayerObj* arg0)
{
    u8 var_a1;

    if ((arg0->input.buttons.held & 0x20) && (arg0->charge_state[1] != PLAYER_CHARGE_FULL)) {
        arg0->unk9E++;
        if (arg0->unkB8 == 0) {
            var_a1 = 0x5A;
        }
        if (arg0->unkB8 == 1) {
            var_a1 = 0x96;
        }
        if (arg0->unkB8 == 2) {
            var_a1 = 0x5A;
        }
        if (arg0->unk9E == 0x19) {
            func_8001540C(1, 7, arg0);
            arg0->charge_state[1] = PLAYER_CHARGE_PARTIAL;
            return;
        }
        if (arg0->unk9E == var_a1) {
            arg0->charge_state[1] = PLAYER_CHARGE_FULL;
        }
        if (arg0->unkB8 == 1) {
#ifndef VERSION_JP
            if (arg0->unkA6 != 4) {
#endif
                if (arg0->unk9E == 0x5A) {
                    if (arg0->unkA6 < 2) {
                        arg0->unkA6 = 2;
                    }
                }
                if (arg0->unk9E == 0x78) {
                    arg0->unkA6 = 3;
                }
                if (arg0->unk9E == 0x96) {
                    arg0->unkA6 = 4;
                }
#ifndef VERSION_JP
            }
#endif
        }
    }
}

void func_80038490(struct PlayerObj* arg0)
{
    if (arg0->unk2 == 0) {
        func_800384DC(arg0);
        func_80037104(arg0);
        func_800371E4(arg0);
    }
}

void func_800384DC(struct PlayerObj* arg0)
{
    func_80015930(1, 7);
    func_800360B0(arg0);
    arg0->charge_state[0] = PLAYER_CHARGE_NONE;
    arg0->charge_state[1] = PLAYER_CHARGE_NONE;
    arg0->unk9D = 0;
    arg0->unk9E = 0;
}

void func_80038524(struct PlayerObj* arg0, s32 arg1)
{
    if (arg0->unk2 == 0 && arg0->unk8E != 0) {
        arg1 += 0x70;
    }
    func_800350A4(arg0, arg1);
}

INCLUDE_ASM("main/nonmatchings/player", func_80038568);

void func_800385EC(void)
{
    struct PlayerObj* player = &g_Player;
    u16 held = player->input.buttons.held;

    if (!(held & 0x10)) {
        player->charge_state[0] = 0;
        player->unk9D = 0;
    }
    if (!(held & 0x20)) {
        player->charge_state[1] = 0;
        player->unk9E = 0;
    }
    if (player->unk9D == 0 && player->unk9E == 0) {
        func_800384DC(player);
        func_800361F8(player);
    }
}

void func_80038678(struct PlayerObj* arg0)
{
    if (arg0->unk2 == 0) {
        if (arg0->unk8F != 0) {
            func_80038748(arg0);
            return;
        }
        if (arg0->unk90 != 0) {
            func_80036534(arg0);
            return;
        }
    }
    if (arg0->unk17 == 6) {
        if (arg0->unk5C >= engine_obj.unk46 / 3) {
            func_800350A4(arg0, 5);
            return;
        }
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

extern u8 D_800F8D2C[];

void func_80038748(struct PlayerObj* arg0)
{
    u8 temp_s0;

    temp_s0 = D_800F8D2C[arg0->unk96];
    func_800350A4(arg0, temp_s0);
    if (temp_s0 == 0x59) {
        arg0->animation_step.fields.duration = arg0->unk91 - 8;
    }
}

void func_800387A8(struct PlayerObj* arg0)
{
    func_800387F4(arg0);
    arg0->x_pos.i.lo = 0;
    arg0->y_pos.i.lo = 0;
    arg0->unk5 = 0x20;
    arg0->unk6 = 0;
    arg0->x_pos.i.hi = (arg0->x_pos.i.hi & 0xFFF0) + 8;
}

void func_800387F4(struct PlayerObj* arg0)
{
    u8 temp_s0;

    temp_s0 = D_800F8D44[arg0->unk97];
    func_800350A4(arg0, temp_s0);
    if (temp_s0 == 0x5D) {
        arg0->animation_step.fields.duration = arg0->unk91 - 8;
    }
}

void func_80038854(struct PlayerObj* arg0)
{
    if ((func_800340BC(arg0) == 0) && (func_800373DC(arg0) == 0)) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->pressed_input & 2) {
            arg0->unk15 = 0;
        }
        if (arg0->pressed_input & 1) {
            arg0->unk15 = 0x40;
        }
        if (arg0->unk90 != 0) {
            func_8003516C(arg0, 0x20, 3);
            func_80034DC8(arg0);
        }
    }
}

void func_800388F0(struct PlayerObj* arg0)
{
    if (arg0->unkC3 != 0) {
        func_80034604(arg0);
    } else if (func_80037338(arg0) == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        D_800F8D5C[arg0->unk6](arg0);
    }
}

void func_80038970(struct PlayerObj* arg0)
{
    func_80038568(arg0, 0x15);
    if (arg0->animation_step.fields.event & 0x80) {
        arg0->animation_step.fields.event &= 0x7F;
        func_80036E1C(0x21, 0x21, 0, 0);
        arg0->unk6++;
    }
}

void func_800389DC(struct PlayerObj* arg0)
{
    s32 direction;

    if (func_80038D38(arg0) != 0) {
        return;
    }
    if (func_80033AC0(arg0) != 0) {
        return;
    }
    if ((func_80033694(arg0) != 0) && (arg0->unk92 == 0)) {
        func_8003484C(arg0);
        return;
    }
    direction = func_80038D88(arg0);
    if (direction != 0) {
        arg0->unkD5 = 0x28;
        func_80038E44(arg0, direction);
        return;
    }
    func_80038568(arg0, 0x15);
}

void func_80038A80(struct PlayerObj* arg0)
{
    s32 temp_v0;

    if ((func_80038D38(arg0) == 0) && (func_80033AC0(arg0) == 0)) {
        temp_v0 = func_80038D88(arg0);
        if (temp_v0 != 0) {
            func_80038E44(arg0, temp_v0);
            return;
        }
        func_80038568(arg0, 0x16);
    }
}

void func_80038AE8(struct PlayerObj* arg0)
{
    s32 direction;
    s8 next_state;

    if (func_80038D38(arg0) != 0 || func_80033AC0(arg0) != 0) {
        return;
    }

    direction = func_80038D88(arg0);
    if (direction != 0) {
        if (direction > 0) {
            func_8002B718(MOVING_OBJECT(arg0));
            func_80038568(arg0, 0x17);
            return;
        }
        func_80038524(arg0, 0x19);
        next_state = 5;
    } else {
        func_80038524(arg0, 0x18);
        next_state = 4;
    }
    arg0->unk6 = next_state;
}

void func_80038B80(struct PlayerObj* arg0)
{
    s32 action;

    if (func_80038D38(arg0) == 0 && func_80033AC0(arg0) == 0) {
        action = func_80038D88(arg0);
        if (action != 0) {
            func_80038E44(arg0, action);
            return;
        }
        if (arg0->animation_step.fields.relative_step == 0) {
            func_80038524(arg0, 0x16);
            arg0->unk6 = 2;
            return;
        }
        func_80038568(arg0, 0x18);
    }
}

void func_80038C10(struct PlayerObj* arg0)
{
    s32 direction;
    s8 next_state;

    if ((func_80038D38(arg0) == 0) && (func_80033AC0(arg0) == 0)) {
        direction = func_80038D88(arg0);
        if (direction != 0) {
            if (direction > 0) {
                func_80038524(arg0, 0x17);
                next_state = 3;
            } else {
                func_8002B718(MOVING_OBJECT(arg0));
                func_80038568(arg0, 0x19);
                return;
            }
        } else {
            func_80038524(arg0, 0x1A);
            next_state = 6;
        }
        arg0->unk6 = next_state;
    }
}

void func_80038CA8(struct PlayerObj* arg0)
{
    s32 action;

    if (func_80038D38(arg0) == 0 && func_80033AC0(arg0) == 0) {
        action = func_80038D88(arg0);
        if (action != 0) {
            func_80038E44(arg0, action);
            return;
        }
        if (arg0->animation_step.fields.relative_step == 0) {
            func_80038524(arg0, 0x16);
            arg0->unk6 = 2;
            return;
        }
        func_80038568(arg0, 0x1A);
    }
}

s32 func_80038D38(struct PlayerObj* arg0)
{
    s32 result;
    s32 trigger;
    u8 timer;

    trigger = arg0->pressed_input & 0x80;
    timer = arg0->unkD5 - 1;
    arg0->unkD5 = timer;
    trigger = trigger != 0;
    if (!(timer & 0xFF)) {
        trigger = 1;
    }
    result = 0;
    if (trigger != 0) {
        func_80034604(arg0);
        result = 1;
    }
    return result;
}

s32 func_80038D88(struct PlayerObj* arg0)
{
    u16 buttons;

    buttons = arg0->input.buttons.held;
    arg0->y_pos.i.hi += D_800F8D78[arg0->unkD6];
    arg0->unkD6 = (arg0->unkD6 + 1) & 0xF;
    arg0->x_vel.val = 0;

    if (buttons & 3) {
        if (buttons & 1) {
            if (arg0->unk88.bytes.collision_flags & 1) {
                return 0;
            }
            arg0->x_vel.val = FIXED(2);
            if (arg0->unk15 != 0) {
                return 1;
            }
            return -1;
        }
        if (!(arg0->unk88.bytes.collision_flags & 2)) {
            goto move_left;
        }
    }

return_zero:
    return 0;

move_left:
    arg0->x_vel.val = FIXED(-2);
    if (arg0->unk15 != 0) {
        return -1;
    }
    return 1;
}

void func_80038E44(struct PlayerObj* arg0, s32 arg1)
{
    s8 value;

    if (arg1 > 0) {
        func_80038524(arg0, 0x17);
        value = 3;
    } else {
        func_80038524(arg0, 0x19);
        value = 5;
    }
    arg0->unk6 = value;
}

void func_80038E90(struct PlayerObj* arg0)
{
    if (arg0->unkC3 != 0) {
        arg0->unk7A = 0;
        arg0->unkE0 = 0;
        func_800361F8(arg0);
        func_8003470C(arg0);
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        D_800F8D88[arg0->unk6](arg0);
    }
}

void func_80038F0C(struct PlayerObj* arg0)
{
    func_800390C4(arg0);
    if (arg0->animation_step.fields.event & 0x80) {
        arg0->animation_step.fields.event = 0;
        arg0->unk6++;
        return;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/player", func_80038F64);

void func_8003904C(struct PlayerObj* arg0)
{
    s32 should_reset;
    u8 timer;

    should_reset = func_800390C4(arg0) != 0;
    timer = arg0->unkE1;
    if (timer == 0) {
        should_reset = 1;
    }
    if (should_reset != 0) {
        arg0->unk7A = 0;
        arg0->unkE0 = 0;
        engine_obj.unk1C = 0;
        func_800361F8(arg0);
        func_8003470C(arg0);
    } else {
        arg0->unkE1 = timer - 1;
        func_8002B718(MOVING_OBJECT(arg0));
    }
}

s32 func_800390C4(struct PlayerObj* arg0)
{
    s32 wall_flag;

    if (arg0->unk88.bytes.collision_flags & 4) {
        arg0->y_vel.val = 0;
        arg0->unk2C = 0;
    }
    wall_flag = 2;
    if (arg0->unk15 != 0) {
        wall_flag = 1;
    }
    if (wall_flag & arg0->unk88.bytes.collision_flags) {
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        return 1;
    }
    return 0;
}

void func_80039120(struct PlayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_80039160(arg0);
    } else {
        func_80039230(arg0);
    }
}

void func_80039160(struct PlayerObj* arg0)
{
    s8 event;
    u8 temp_a1;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    event = arg0->animation_step.fields.event;
    if (event & 0x80) {
        arg0->animation_step.fields.event = event & 0x7F;
        func_8001540C(1, 9, arg0);
        func_800363B8(arg0, 5U);
        func_800355C0();
        g_Entity.active = 1;
        g_Entity.x_pos.val = arg0->x_pos.val;
        g_Entity.y_pos.val = arg0->y_pos.val;
        temp_a1 = arg0->unk15;
        g_Entity.unk67 = 1;
        g_Entity.unkDA = 0xF0;
        g_Entity.unkDC.value = 0;
        g_Entity.unk15 = temp_a1;
        func_80035EA4(&g_Entity);
        arg0->unk6 = (u8)arg0->unk6 + 1;
    }
}

void func_80039230(struct PlayerObj* arg0)
{
    if (arg0->unkDE == 0) {
        func_8003470C(arg0);
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
}

void func_80039270(struct PlayerObj* arg0)
{
    u8 temp_v0;
    s16 temp_v1;
    s32 var_a2;

    var_a2 = 0;
    temp_v0 = g_Player.unk15;
    arg0->unk15 = temp_v0;
    if (temp_v0 != 0) {
        if (arg0->unk88.bytes.collision_flags & 1) {
            var_a2 = 1;
        } else {
            arg0->x_pos.i.hi = g_Player.x_pos.u.hi + arg0->unkDC.unsigned_value;
        }
    } else if (arg0->unk88.bytes.collision_flags & 2) {
        var_a2 = 1;
    } else {
        arg0->x_pos.i.hi = g_Player.x_pos.u.hi - arg0->unkDC.unsigned_value;
    }

    temp_v1 = arg0->unkDC.value;
    if (temp_v1 == 0x40) {
        var_a2 = 1;
    }
    if (var_a2 != 0) {
        func_8003470C(arg0);
    } else {
        arg0->unkDC.value = temp_v1 + 8;
    }
}

void func_80039328(struct PlayerObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->active = 0;
        arg0->on_screen = 0;
        g_Player.unkDE = 0;
        g_Player.unk7A = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/player", func_80039378);

INCLUDE_ASM("main/nonmatchings/player", func_80039570);

void func_80039700(struct PlayerObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    D_800F8D94[arg0->unk6](arg0);
}

void func_8003974C(struct PlayerObj* arg0)
{
    if (arg0->animation_step.fields.event != 0) {
        arg0->animation_step.fields.event &= 0x7F;
        if (arg0->unk15 != 0) {
            arg0->x_vel.val = FIXED(4);
        } else {
            arg0->x_vel.val = FIXED(-4);
        }
        arg0->unk28 = FIXED(-0.25);
        arg0->y_vel.val = FIXED(6.75);
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk6++;
    }
}

void func_800397B0(struct PlayerObj* arg0)
{
    if (func_80034238(arg0) == 0) {
        func_80034320(arg0);
    }
}

void func_800397E8(struct PlayerObj* arg0)
{
    func_80034238(arg0);
}

void func_80039808(struct PlayerObj* arg0)
{
    if (arg0->unk88.bytes.collision_flags & 8) {
        arg0->unk7A = 0;
        func_80034668(arg0);
        return;
    }

    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80038524(arg0, 0xB);
        arg0->unk7A = 0;
        arg0->unk5 = 7;
        arg0->unk6 = 0;
    }
}

s32 func_80039880(struct PlayerObj* arg0)
{
    if (arg0->unk2 == 0) {
        return 0;
    } else if (arg0->unkC3 != 0) {
        return 0;
    } else if (func_80039F28(arg0) != 0) {
        return 1;
    } else if (func_80039E5C(arg0) == 0) {
        return func_80039C34(arg0) != 0;
    }
    return 1;
}

s32 func_800398F0(struct PlayerObj* arg0)
{
    if (func_80039BB8(arg0) == 0) {
        return 0;
    }
    func_800350A4(arg0, 0x58);
    func_8001540C(1, 7, arg0);
    func_800363B8(arg0, 3);
    arg0->unk84 = 0;
    arg0->unk86 = 0;
    arg0->unk5 = 0x30;
    arg0->unk6 = 0;
    func_8003A104(arg0);
    return 1;
}

s32 func_8003996C(struct PlayerObj* arg0)
{
    if (func_80039BB8(arg0) != 0) {
        if (arg0->unkB9 & 4) {
            func_800350A4(arg0, 0x64);
            func_8001540C(1, 7, arg0);
            arg0->unk5 = 0x37;
        } else {
            func_800350A4(arg0, 0x5B);
            func_8001540C(1, 8, arg0);
            arg0->unk5 = 0x31;
        }
        arg0->unk6 = 0;
        func_8003A3EC(arg0);
        return 1;
    }
    return 0;
}

s32 func_80039A00(struct PlayerObj* arg0)
{
    if (arg0->unk2 == 0) {
        return 0;
    }
    if (arg0->unkC3 != 0) {
        return 0;
    }
    if (func_80039CC4(arg0) != 0) {
        return 1;
    }
    if (func_80039BB8(arg0) == 0) {
        return 0;
    }

    if (arg0->unkB9 & 4) {
        func_800350A4(arg0, 0x64);
        func_8001540C(1, 7, arg0);
        arg0->unk5 = 0x38;
    } else {
        func_800350A4(arg0, 0x5B);
        func_8001540C(1, 8, arg0);
        arg0->unk5 = 0x32;
    }

    arg0->unk6 = 0;
    func_8003A5E4(arg0);
    return 1;
}

s32 func_80039AC8(struct PlayerObj* arg0)
{
    if (func_80039BB8(arg0) == 0) {
        return 0;
    }
    func_800350A4(arg0, 0x5D);
    func_8001540C(1, 7, arg0);
    func_800363B8(arg0, 8);
    arg0->unk84 = 0;
    arg0->unk86 = 0;
    arg0->unk5 = 0x33;
    arg0->unk6 = 0;
    func_8003A7B4(arg0);
    return 1;
}

s32 func_80039B44(struct PlayerObj* arg0)
{
    if (func_80039BB8(arg0) == 0) {
        return 0;
    }

    func_800350A4(arg0, 0x5E);
    func_8001540C(1, 7, arg0);
    func_800363B8(arg0, 8);
    arg0->unk5 = 0x34;
    arg0->unk6 = 0;
    func_8003A8A0(arg0);
    return 1;
}

s32 func_80039BB8(struct PlayerObj* arg0)
{
    if (arg0->unk2 != 0 && arg0->unkC3 == 0 && (arg0->pressed_input & 0x10) && arg0->unk8E == 0) {
        func_80039C20(arg0);
        return 1;
    }
    return 0;
}

void func_80039C20(struct PlayerObj* arg0)
{
    arg0->unk8E = 1;
    arg0->unkBB = 0;
    arg0->unk8C = 0;
}

s32 func_80039C34(struct PlayerObj* arg0)
{
    if (!(arg0->unkB9 & 1))
        return 0;
    if (arg0->pressed_input & 0x20) {
        if (arg0->unk8E == 0) {
            func_80039C20(arg0);
            func_800350A4(arg0, 0x5F);
            arg0->unk5 = 0x35;
            arg0->unk6 = 0;
            func_8003A9F0(arg0);
            return 1;
        }
    }
    return 0;
}

s32 func_80039CC4(struct PlayerObj* arg0)
{
    if (!(arg0->unkB9 & 2)) {
        return 0;
    }
    if (!(arg0->input.buttons.held & 8)) {
        return 0;
    }
    if (!(arg0->pressed_input & 0x20)) {
        return 0;
    }
    if (arg0->unk8E != 0) {
        return 0;
    }

    func_80039C20(arg0);
    func_800350A4(arg0, 0x61);
    func_800363B8(arg0, 5);
    if (arg0->input.buttons.held & 2) {
        arg0->unk15 = 0;
    }
    if (arg0->input.buttons.held & 1) {
        arg0->unk15 = 0x40;
    }
    arg0->unk5 = 0x36;
    arg0->unk6 = 0;
    func_8003AAE8(arg0);
    return 1;
}

s32 func_80039D9C(struct PlayerObj* arg0)
{
    if (!(arg0->unkB9 & 4)) {
        return 0;
    } else if (!(arg0->pressed_input & 0x80)) {
        return 0;
    } else {
        func_800350A4(arg0, 0x63);
        func_8001540C(1, 1, arg0);
        func_800363B8(arg0, 7);
        arg0->y_vel.val = FIXED(5.8125);
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk84 = 0;
        arg0->unk86 = 6;
        arg0->unk8C = 0;
        func_800365A4(arg0);
        arg0->unk5 = 6;
        arg0->unk6 = 0;
        return 1;
    }
}

s32 func_80039E5C(struct PlayerObj* arg0)
{
    if (!(arg0->unkB9 & 8)) {
        return 0;
    }
    if (!(arg0->input.buttons.held & 4)) {
        return 0;
    }
    if (!(arg0->pressed_input & 0x20)) {
        return 0;
    }
    if (arg0->unk8E != 0) {
        return 0;
    }

    func_80039C20(arg0);
    func_800350A4(arg0, 0x65);
    func_8001540C(0, 0x1B, arg0);
    func_800363B8(arg0, 9);
    arg0->unk67 = 1;
    arg0->unk7A = 1;
    arg0->unk5 = 0x39;
    arg0->unk6 = 0;
    func_8003AE08(arg0);
    return 1;
}

INCLUDE_ASM("main/nonmatchings/player", func_80039F28);

INCLUDE_ASM("main/nonmatchings/player", func_8003A000);

void func_8003A104(struct PlayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6++;
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_8003B1A0(arg0, 0x18);
        if (func_8003A1DC(arg0) != 0) {
            return;
        }
    }

    if (arg0->unkC3 == 0) {
        arg0->unk8E = 0;
        if (func_80033494(arg0) != 0) {
            return;
        }
        if (arg0->animation_step.fields.event & 0x40) {
            if (func_80039880(arg0) != 0 || func_800398F0(arg0) != 0 || func_8003A328(arg0) != 0) {
                return;
            }
        }
        arg0->unk8E = 1;
    }
    func_8003A374(arg0);
}

INCLUDE_ASM("main/nonmatchings/player", func_8003A1DC);

s32 func_8003A328(struct PlayerObj* arg0)
{
    if (func_80033EA4(arg0) != 0) {
        return 1;
    }
    if (func_800334F4(arg0) == 0) {
        return 0;
    }
    func_800344A0(arg0);
    return 1;
}

void func_8003A374(struct PlayerObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk8E = 0;
        if (engine_obj.unkF != 0) {
            func_80034F7C(arg0);
            return;
        }
        if (arg0->unkC0 != 0) {
            func_80034E2C();
            return;
        }
        func_800343A4(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/player", func_8003A3EC);

INCLUDE_ASM("main/nonmatchings/player", func_8003A5E4);

void func_8003A7B4(struct PlayerObj* arg0)
{
    s8 state;

    if (func_800340BC(arg0) != 0) {
        arg0->unk8E = 0;
        return;
    }

    state = arg0->unk6;
    if (state == 0) {
        arg0->unk6 = state + 1;
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }

    func_8003B1A0(arg0, 0x1E);
    if ((u8)arg0->animation_step.fields.event & 0x40) {
        arg0->unk8E = 0;
        if (func_80039AC8(arg0) != 0) {
            return;
        }
        arg0->unk8E = 1;
    }

    if (arg0->pressed_input & 2) {
        arg0->unk15 = 0;
    }
    if (arg0->pressed_input & 1) {
        arg0->unk15 = 0x40;
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk8E = 0;
        func_8003516C(arg0, 0x1F, 2);
        func_80034D64(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/player", func_8003A8A0);

void func_8003A9F0(struct PlayerObj* player)
{
    if (player->unk6 == 0) {
        player->unk6++;
    } else {
        func_80015DC8(ANIMATED_OBJECT(player));
    }
    func_8003B1A0(player, 0x20);
    if (player->animation_step.fields.event & 0x10) {
        player->animation_step.fields.event = 0;
        func_8001540C(1, 8, player);
        func_800363B8(player, 6);
    }
    if (player->unkC3 == 0) {
        player->unk8E = 0;
        if (func_80033494(player) != 0) {
            return;
        }
        if (player->animation_step.fields.event & 0x40) {
            if (func_80039880(player) != 0) {
                return;
            }
            if (func_800398F0(player) != 0) {
                return;
            }
            if (func_8003A328(player) != 0) {
                return;
            }
        }
        player->unk8E = 1;
    }
    func_8003A374(player);
}

void func_8003AAE8(struct PlayerObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    D_800F8DAC[arg0->unk6](arg0);
}

void func_8003AB34(struct PlayerObj* arg0)
{
    func_8003B1A0(arg0, 0x21);

    if (arg0->unkC3 == 0) {
        if (arg0->input.buttons.held & 2) {
            arg0->unk15 = 0;
        }
        if (arg0->input.buttons.held & 1) {
            arg0->unk15 = 0x40;
        }
    }

    if (arg0->animation_step.fields.event & 0x10) {
        arg0->y_vel.val = FIXED(-3);
        arg0->unk2C = FIXED(0.2578125);
        arg0->animation_step.fields.event = 0;
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->unk67 = -1;
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/player", func_8003ABE0);

void func_8003AD74(struct PlayerObj* arg0)
{
    if (arg0->unkC3 == 0) {
        arg0->unk8E = 0;
        if (func_80033494(arg0) != 0) {
            return;
        }
        if (arg0->animation_step.fields.event & 0x40) {
            if (func_80039880(arg0) != 0 || func_800398F0(arg0) != 0 || func_8003A328(arg0) != 0) {
                return;
            }
        }
        arg0->unk8E = 1;
    }
    func_8003A374(arg0);
}

void func_8003AE08(struct PlayerObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    D_800F8DB8[arg0->unk6](arg0);
}

void func_8003AE54(struct PlayerObj* arg0)
{
    u8 event;
    s32 scratch;

    func_8003B1A0(arg0, 0x23);
    event = arg0->animation_step.fields.event;
    if (event & 0x20) {
        arg0->animation_step.fields.event = event & 0x1F;
        if (arg0->unk15 != 0) {
            arg0->x_vel.val = FIXED(4);
        } else {
            arg0->x_vel.val = -FIXED(4);
        }
        scratch = FIXED(6.75);
        arg0->y_vel.val = scratch;
        scratch = (u8)arg0->unk6;
        arg0->unk28 = -FIXED(0.25);
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk7A = 0;
        scratch += 1;
        arg0->unk6 = scratch;
    }
}

void func_8003AEE0(struct PlayerObj* arg0)
{
    if (func_80034238(arg0) == 0) {
        func_80034320(arg0);
        func_8003AFD4(arg0);
    }
}

void func_8003AF20(struct PlayerObj* arg0)
{
    if (func_80034238(arg0) == 0) {
        func_8003AFD4(arg0);
    }
}

void func_8003AF58(struct PlayerObj* arg0)
{
    if (arg0->unk88.bytes.collision_flags & 8) {
        arg0->unk8E = 0;
        func_80034668(arg0);
        return;
    }

    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        func_8003516C(arg0, 0xB, 4);
        arg0->unk8E = 0;
        arg0->unk5 = 7;
        arg0->unk6 = 0;
    }
}

void func_8003AFD4(struct PlayerObj* arg0)
{
    struct MiscObj* obj;

    if (!(D_80141BD8.unk0 & 1)) {
        arg0->animation_step.fields.event &= 0xFE;
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 0x21;
            obj->id = 0x30;
            obj->unk2 = 0;
            obj->bg_offset = arg0->bg_offset;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/player", func_8003B044);

void func_8003B1A0(struct PlayerObj* arg0, s8 arg1)
{
    s8 event;

    event = arg0->animation_step.fields.event;
    if (event & 0x80) {
        arg0->animation_step.fields.event = event & 0x7F;
        func_8003B1E0(arg0, arg1);
    }
}

void func_8003B1E0(struct PlayerObj* arg0, s8 arg1)
{
    struct WeaponObj* weapon;

    weapon = find_free_weapon_obj();
    if (weapon != NULL) {
        weapon->active = 1;
        weapon->id = arg1;
        weapon->unk2 = arg0->unkBB;
        weapon->bg_offset = arg0->bg_offset;
        weapon->unk84.word = arg0->unk17;
    }
}

void func_8003B24C(struct PlayerObj* self)
{
    s32 side_mask;

    if (self->unk6 == 0) {
        self->unk6++;
    } else {
        func_80015DC8(ANIMATED_OBJECT(self));
    }
    func_8003B1A0(self, 0x1D);
    if (func_8003B340(self) == 0) {
        if (self->animation_step.fields.event & 0x20) {
            self->animation_step.fields.event = 0;
            self->x_vel.val = 0;
        }
        if (self->unk15 != 0) {
            side_mask = 1;
            if (self->x_vel.val < 0) {
                self->x_vel.val = 0;
            }
        } else {
            side_mask = 2;
            if (self->x_vel.val > 0) {
                self->x_vel.val = 0;
            }
        }
        if (side_mask & self->unk88.bytes.collision_flags) {
            self->x_vel.val = 0;
        }
        if (self->x_vel.val != 0) {
            func_8002B694(ANIMATED_OBJECT(self));
        }
        func_8003A374(self);
    }
}

s32 func_8003B340(struct PlayerObj* arg0)
{
    if (arg0->unkC3 != 0 || !(arg0->animation_step.fields.event & 0x40)) {
        return 0;
    }

    arg0->unk8E = 0;
    if (func_80033EA4(arg0) != 0 || func_80039880(arg0) != 0 || func_80033414(arg0) != 0) {
        return 1;
    }
    if (func_800398F0(arg0) != 0) {
        return 1;
    }
    arg0->unk8E = 1;
    return 0;
}

void (*D_800F8980[])(struct PlayerObj*) = {
    func_80035694,
    func_800312B4,
    func_80035A6C,
    func_80035DDC,
};

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

u8 D_800F8AD0[8] = { 0, 0x21, 0x22, 0x24, 0x23, 0, 0, 0 };

struct PlayerInitialStateData D_800F8AD8[5] = {
    { 0, 0, 0, 0 },
    { 0x28000, 0x3000, 0, 0 },
    { 0xC000, 0, 0x2C000, 0x4200 },
    { 0, 0, 0, 0 },
    { 0x28000, 0x3000, 0, 0 },
};

u8 D_800F8B28[8] = { 0, 0x4B, 0x64, 0, 0x4B, 0, 0, 0 };

u8 D_800F8B30[2] = { 0x67, 0x66 };

static u16 s_PlayerEffectIdPad = 0;

u8 D_800F8B34[][4] = { { 2, 3, 6, 6 }, { 2, 4, 7, 7 } };

s16 D_800F8B3C[4] = { 0x780D, 0x780E, 0x780F, 0 };

void (*D_800F8B44[])(struct PlayerObj*) = {
    func_80035848,
    func_800358A4,
    func_80035A24,
};

u16 D_800F8B50[8] = {
    0x0000,
    0x00AB,
    0x09CB,
    0x025B,
    0x0000,
    0x01AB,
    0x08AB,
    0x0000,
};

u16 D_800F8B60[6] = {
    0x00CB,
    0x03BB,
    0x02CB,
    0x03BB,
    0x09CB,
    0x03BB,
};

u16 D_800F8B6C[20] = {
    0x0000,
    0x0000,
    0x069B,
    0x06CB,
    0x06CB,
    0x06B3,
    0x06BB,
    0x06BB,
    0x09BB,
    0x09BB,
    0x09CB,
    0x035B,
    0x03CB,
    0x04AB,
    0x043B,
    0x03CB,
    0x035B,
    0x04AB,
    0x043B,
    0x0000,
};

void (*D_800F8B94[])(struct PlayerObj*) = {
    func_80035AA8,
    func_80035B6C,
    func_80035C20,
    func_80035D00,
};

u8 D_800F8BA4[4][8] = {
    { 0x00, 0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C },
    { 0x02, 0x06, 0x0A, 0x0E, 0x12, 0x16, 0x1A, 0x1E },
    { 0x01, 0x05, 0x09, 0x0D, 0x11, 0x15, 0x19, 0x1D },
    { 0x03, 0x07, 0x0B, 0x0F, 0x13, 0x17, 0x1B, 0x1F },
};

struct Unk_unk68 D_800F8BC4 = { 0, 2, 0x0B, 0x13 };

struct Unk_unk68 D_800F8BC8 = { 0, 3, 0x0A, 0x13 };

u16 D_800F8BCC[6] = { 0x10, 0x0E, 0x1A, 0x11, 0x10, 0x1A };

f32 D_800F8BD8[2] = {
    { 0x000CFFF5 },
    { 0x0009FFF6 },
};

union PlayerChargeData D_800F8BE0 = {
    {
        { 0, 4, 3, 6, 3, 1 },
        { 1, 1, 1 },
        { 0, 12, 12, 12, 12, 6, 12, 12, 6, 0, 0, 0, 0, 0, 0 },
    },
};

s8 D_800F8BF8[24] = { 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1 };

s8 D_800F8C10[24] = { 0, 1, 1, 1, 1, 1, 1, 1, 1 };

s8 D_800F8C28[24] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 };

u8 D_800F8C40[12] = { 0, 1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80 };

struct PlayerModeTiming D_800F8C4C[22] = {
    { 0x14, 0x06 },
    { 0x19, 0x0F },
    { 0x01, 0x01 },
    { 0x14, 0x0F },
    { 0x0A, 0x0A },
    { 0x14, 0x0A },
    { 0x46, 0x46 },
    { 0x01, 0x01 },
    { 0x14, 0x06 },
    { 0x19, 0x0F },
    { 0x19, 0x14 },
    { 0x01, 0x01 },
    { 0x01, 0x01 },
    { 0x01, 0x01 },
    { 0x19, 0x14 },
    { 0xFA, 0xFA },
    { 0x01, 0x01 },
    { 0x23, 0x14 },
    { 0x23, 0x0F },
    { 0x19, 0x06 },
    { 0x23, 0x0F },
    { 0, 0 },
};

void (*D_800F8C78[])(struct PlayerObj*) = {
    func_80037B98,
    func_80037B98,
    func_80037B90,
    func_80037B98,
    func_80037B90,
    func_80037B98,
    func_80037B90,
    func_80037B90,
    func_80037C28,
    func_80037BC4,
    func_80037D08,
    func_80037B90,
    func_80037B90,
    func_80037B90,
    func_80037B98,
    func_80037B98,
    func_80037B90,
    func_80037C28,
    func_80037BC4,
    func_80037B98,
    func_80037BC4,
};

s8 D_800F8CCC[24] = { 3, 3, 3, 3, 3, 3, 3, 3, 4, 3, 4, 4, 4, 4, 4, 1, 4, 4, 3, 4, 4 };

s8 D_800F8CE4[24] = { 0, 1, 1, 1, 1, 0, 0, 1 };

s8 D_800F8CFC[24] = { 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1 };

s8 D_800F8D14[24] = { 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1 };

u8 D_800F8D2C[] = {
    0x58,
    0x58,
    0x00,
    0x58,
    0x00,
    0x58,
    0x59,
    0x00,
    0x58,
    0x5A,
    0x58,
    0x00,
    0x00,
    0x00,
    0x58,
    0x59,
    0x00,
    0x5B,
    0x5B,
    0x5A,
    0x5B,
    0x00,
    0x00,
    0x00,
};

u8 D_800F8D44[] = {
    0x5C,
    0x5C,
    0x00,
    0x5C,
    0x00,
    0x5C,
    0x5D,
    0x00,
    0x5C,
    0x5C,
    0x5C,
    0x00,
    0x00,
    0x00,
    0x5C,
    0x5D,
    0x00,
    0x5C,
    0x5C,
    0x5C,
    0x5C,
    0x00,
    0x00,
    0x00,
};

void (*D_800F8D5C[])(struct PlayerObj*) = {
    func_80038970,
    func_800389DC,
    func_80038A80,
    func_80038AE8,
    func_80038B80,
    func_80038C10,
    func_80038CA8,
};

s8 D_800F8D78[16] = {
    0,
    1,
    0,
    1,
    1,
    0,
    1,
    0,
    0,
    -1,
    0,
    -1,
    -1,
    0,
    -1,
    0,
};

void (*D_800F8D88[])(struct PlayerObj*) = {
    func_80038F0C,
    func_80038F64,
    func_8003904C,
};

void (*D_800F8D94[])(struct PlayerObj*) = {
    func_8003974C,
    func_800397B0,
    func_800397E8,
    func_80039808,
};

u8 D_800F8DA4[4][2] = {
    { 7, 3 },
    { 8, 4 },
    { 7, 5 },
    { 0, 0 },
};

void (*D_800F8DAC[])(struct PlayerObj*) = {
    func_8003AB34,
    func_8003ABE0,
    func_8003AD74,
};

void (*D_800F8DB8[])(struct PlayerObj*) = {
    func_8003AE54,
    func_8003AEE0,
    func_8003AF20,
    func_8003AF58,
};
