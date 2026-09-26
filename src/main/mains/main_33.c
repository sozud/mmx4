// MainObj, main_object_update_funcs[33]
// 8005D1F4..8005E570
#include "common.h"

void func_8005D1F4(struct MainObj* arg0)
{
    D_800FDF54[arg0->state](arg0);
}

void func_8005D230(struct MainObj* arg0)
{
    u8 bg_offset;
    u16 unk42;
    s32 x_pos;
    s32 y_pos;

    arg0->unk5C = 0;
    arg0->unk60 = 6;
    arg0->unk61 = 0;
    arg0->collision_data = D_801072F4;
    bg_offset = (u8)g_Player.bg_offset;
    arg0->unk16 = 6;
    x_pos = arg0->x_pos.val;
    arg0->y_pos.i.hi = 0x2E8;
    y_pos = arg0->y_pos.val;
    arg0->animation_table = (const u8* const*)D_800FDEE4;
    arg0->unk54 = &D_800FDD88;
    arg0->unk50 = &D_800FDD8C;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk68 = NULL;
    arg0->unk15 = 0x40;
    arg0->bg_offset = bg_offset;
    arg0->unk18.val = x_pos;
    arg0->unk1C.val = y_pos;
    func_80015D60(arg0, 0);
    arg0->ext.main_33.unk80 = 0x7F;
    unk42 = arg0->unk42;
    arg0->ext.main_33.unk90 = 0;
    arg0->ext.main_33.unk85 = 1;
    arg0->ext.main_33.unk86 = 2;
    arg0->ext.main_33.unk8E = unk42;
    engine_obj.enable_boss = 1;
    engine_obj.unk25 = 2;
    engine_obj.boss_ptr = arg0;
    func_80036AE4(0x14, 0);
    arg0->state = 1;
    arg0->unk5 = 2;
    arg0->unk6 = 0;
}

void func_8005D348(struct MainObj* arg0)
{
    s32 x;
    s32 y;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FDF64[arg0->unk5](arg0);
    if (arg0->ext.main_33.unk85 == 0) {
        arg0->ext.main_33.saved_unk5 = arg0->unk5;
        if (func_8002DD04(arg0) < 0) {
            g_Player.unk7A = 1;
            g_Player.unk61 = 0x7F;
            func_800AF808(BASE_OBJECT(arg0));
            func_800C813C(9, D_800FDF40, arg0);
            arg0->unk54 = NULL;
            arg0->unk50 = NULL;
            func_800DABE4(1, 0, 0);
            arg0->unk7C = 0x5A;
            arg0->unk7E = 4;
            arg0->on_screen = 0;
            arg0->state = 2;
            arg0->unk5 = 0;
            return;
        }
    }
    func_8002D9BC(arg0);
    if (arg0->ext.main_33.unk90 != 0) {
        arg0->ext.main_33.unk90--;
        if (--arg0->ext.main_33.unk91 == 0) {
            x = arg0->x_pos.val;
            y = arg0->y_pos.val;
            arg0->x_pos.i.hi = D_800FDDA0[arg0->ext.main_33.unk87 * 2] + 0x20;
            arg0->y_pos.i.hi = D_800FDDA0[arg0->ext.main_33.unk87 * 2 + 1] + 0x20;
            func_800AF878(BASE_OBJECT(arg0), 1, 0x20, 0x20);
            arg0->x_pos.val = x;
            arg0->y_pos.val = y;
            arg0->ext.main_33.unk91 = 6;
        }
    }
    func_8002B318(BASE_OBJECT(arg0), 0x48, 0x48);
}

INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005D4E0);

void func_8005D7E8(struct MainObj* arg0)
{
    arg0->ext.raw[0] = 0;
    arg0->ext.raw[1] = 0;
    arg0->ext.raw[2] = 0;
    arg0->ext.raw[3] = 0;
    arg0->ext.raw[5] = 0;
    background_objects[0].unk26 = 0x1100;
    background_objects[0].unk2A = 0x220;
    background_objects[0].unk28 = FIXED(0.00831);
    g_Player.unk61 = 0;
    func_8002B108(OBJECT_HEADER(arg0));
}

void func_8005D844(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_33.saved_unk5;
}

void func_8005D850(struct MainObj* arg0)
{
    D_800FDF80[arg0->unk6](arg0);
}

void func_8005D88C(struct MainObj* arg0)
{
    arg0->unk7C = 0xB4;
    if (arg0->unk15 == 0) {
        arg0->unk20 = FIXED(-2.5);
    } else {
        arg0->unk20 = FIXED(2.5);
    }
    arg0->unk6 = 1;
}

void func_8005D8B8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (arg0->unk15 == 0 ? arg0->x_pos.i.hi >= 0x1220 : arg0->x_pos.i.hi < 0x1321) {
    } else {
        func_80015D60(arg0, 1);
        arg0->unk28 = FIXED(-0.125);
        arg0->unk6 = 2;
        return;
    }
    if (arg0->ext.main_33.unk85 == 0 && --arg0->unk7C == 0) {
        arg0->unk7C = 1;
        if (arg0->unk15 == 0 ? arg0->x_pos.i.hi < 0x1231 : arg0->x_pos.i.hi >= 0x1310) {
        } else {
            func_80015D60(arg0, 2);
            arg0->unk5 = 4;
            arg0->unk6 = 0;
        }
    }
}

void func_8005D9C4(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk7C = 1;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk20 != 0) {
        return;
    }
    if (arg0->unk15 == 0) {
        arg0->unk15 = 0x40;
        arg0->unk20 = FIXED(2.5);
    } else {
        arg0->unk15 = 0;
        arg0->unk20 = -FIXED(2.5);
    }
    func_80015D60(arg0, 0);
    arg0->unk28 = 0;
    if (--arg0->ext.main_33.unk86 == 0 && arg0->ext.main_33.unk85 != 0) {
        arg0->unk7C = 0x40;
        arg0->unk20 = FIXED(1);
        arg0->unk5 = 6;
        arg0->unk6 = 0;
        return;
    }
    arg0->unk6 = 1;
}

void func_8005DAB8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));

    if (arg0->unk6 == 0) {
        func_8002B694(ANIMATED_OBJECT(arg0));

        if (arg0->unk1C.i.hi == arg0->y_pos.i.hi) {
            if (arg0->ext.main_33.unk84 == 0) {
                arg0->unk7C = 0x1E;
                arg0->unk6 = 1;
            }
        }

        if (arg0->y_pos.i.hi >= 0x2E9) {
            arg0->y_pos.i.hi = 0x2E8;
            arg0->unk24 = 0;
            arg0->unk2C = 0;
            func_80015D60(arg0, 2);
            arg0->unk5 = 4;
            arg0->unk6 = 0;
        }
    } else {
        if (--arg0->unk7C == 0) {
            arg0->ext.main_33.unk84 = 1;
            arg0->unk6 = 0;
        }
    }
}

void func_8005DB84(struct MainObj* arg0)
{
    D_800FDF8C[arg0->unk6](arg0);
}

void func_8005DBC0(struct MainObj* arg0)
{
    arg0->ext.main_33.unk82 = 0;
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        func_8001540C(2, 0x52, arg0);
    }
    if (arg0->animation_step.fields.event == 1) {
        if (arg0->unk15 != 0) {
            arg0->unk20 = FIXED(4);
        } else {
            arg0->unk20 = FIXED(-4);
        }
        func_80015D60(arg0, 3);
        arg0->unk7C = 0xB4;
        arg0->unk6 = 1;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005DC58);

INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005DED4);

void func_8005DF84(struct MainObj* self)
{
    s16 target;
    s16 position;
    s16 distance;

    target = self->ext.main_33.unk82;
    position = self->x_pos.i.hi;
    if ((target - position) >= 0) {
        distance = target - position;
    } else {
        distance = position - target;
    }

    if (distance == 0) {
        func_80015D60(self, 5);
        self->unk7C = 0x1E;
        self->unk6 = 4;
    } else if (distance < 6) {
        if (self->unk15 != 0) {
            self->unk20 = FIXED(1);
        } else {
            self->unk20 = FIXED(-1);
        }
    } else if (distance < 0x18) {
        if (self->unk15 != 0) {
            self->unk20 = FIXED(2);
        } else {
            self->unk20 = FIXED(-2);
        }
    }

    func_8002B718(MOVING_OBJECT(self));
}

void func_8005E044(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        func_8001540C(2, 0x53, arg0);
    }
    if (arg0->animation_step.fields.event == 1) {
        arg0->unk24 = FIXED(4);
        arg0->unk20 = 0;
        func_8001540C(2, 0x54, arg0);
        func_80015D60(arg0, 6);
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}

void func_8005E0CC(struct MainObj* arg0)
{
    D_800FDFA0[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005E108);

void func_8005E1BC(struct MainObj* arg0)
{
    s32 variant;
    s32 should_transition;
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));

    variant = arg0->ext.main_33.variant;
    if (variant == 5) {
        goto state_5;
    }
    if (variant >= 6) {
        if (variant == 6) {
            goto state_6;
        }
        goto timer_update;
    }
    if (variant >= 0) {
        goto state_low;
    }
    goto timer_update;

state_low:
    should_transition = arg0->y_pos.i.hi < 0x2F0;
    goto transition_check;

state_5:
    should_transition = arg0->y_pos.i.hi < 0x2A0;
    goto transition_check;

state_6:
    should_transition = arg0->y_pos.i.hi < 0x280;

transition_check:
    if (should_transition != 0) {
        arg0->unk7E = 4;
        arg0->unk6 = 2;
        return;
    }

timer_update:
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->unk2C = FIXED(0.2578125);
        arg0->ext.main_33.unk84 = 0;
        arg0->unk5 = 3;
        arg0->unk6 = 0;
        func_80015D60(arg0, 7);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005E298);

void func_8005E3E8(struct MainObj* arg0)
{
    D_800FDFAC[arg0->unk6](arg0);
}

void func_8005E424(struct MainObj* arg0)
{
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk7E = 3;
        arg0->unk6 = 1;
    }
}

void func_8005E47C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7E == 0) {
        func_8001540C(0, 0xE, NULL);
        arg0->unk7E = 3;
    }
    if (++arg0->unk5C == 0x30) {
        arg0->unk6 = 2;
        arg0->unk7C = 0x3C;
    }
}

void func_8005E500(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        func_800DABE4(0, 0x1340, 0x2A0);
        arg0->ext.main_33.unk85 = 0;
        func_80036B18();
        func_80015D60(arg0, 2);
        arg0->unk5 = 4;
        arg0->unk6 = 0;
    }
}
