// MainObj, main_object_update_funcs[55]
// 8006EB40..8006FD50
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006EB40);

void func_8006ECC4(struct MainObj* arg0)
{
    s32 distance;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    distance = arg0->x_pos.val - background_objects[arg0->bg_offset].x_pos.val;
    if (distance > FIXED(48) && distance < FIXED(272)) {
        arg0->unk5 = 1;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006ED44);

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006EF28);

void func_8006F0A0(struct MainObj* arg0)
{
    D_801007F8[arg0->unk2](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006F0DC);

void func_8006F244(struct MainObj* arg0)
{
    if (arg0->unk2 == 1) {
        if (arg0->y_pos.val < background_objects[arg0->bg_offset].y_pos.val + FIXED(64)) {
            arg0->unk24 = 0;
            arg0->unk6 = (u8)arg0->unk6 + 1;
            func_80015D60(arg0, 2);
            arg0->unk7C = 0;
            arg0->unk7E = 4;
        }
    } else {
        arg0->unk7C = 0;
        arg0->unk7E = 4;
        arg0->unk6 = (u8)arg0->unk6 + 1;
        func_80015D60(arg0, 2);
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8006F304(struct MainObj* arg0)
{
    s16 timer = arg0->unk7C;
    s16 remaining;
    u32** animation_table;
    struct ShotObj* shot;

    if (timer == 0) {
        if (arg0->animation_step.fields.event == 1) {
            arg0->animation_step.fields.event = 0;
            shot = find_free_shot_obj();
            if (shot != 0) {
                shot->active = 0x41;
                shot->id = 0x22;
                shot->unk40 = arg0->unk40;
                shot->unk42 = arg0->unk42;
                shot->unk3C = ANIMATED_OBJECT(arg0)->unk3C;
                shot->bg_offset = arg0->bg_offset;
                shot->x_pos.val = arg0->x_pos.val;
                shot->y_pos.val = arg0->y_pos.val;
                animation_table = ANIMATED_OBJECT(arg0)->animation_table;
                shot->unk7C = WEAPON_OBJECT(arg0);
                shot->unk2 = 0;
                shot->animation_table = animation_table;
            }
        }
        if (arg0->animation_step.fields.event == 2) {
            arg0->animation_step.fields.event = 0;
            arg0->unk7C = 10;
            remaining = (u16)arg0->unk7E - 1;
            arg0->unk7E = remaining;
            if (remaining == 0) {
                arg0->unk6++;
                func_80015D60(arg0, 3);
            }
        }
        func_80015DC8(ANIMATED_OBJECT(arg0));
    } else {
        arg0->unk7C = timer - 1;
    }
}

void func_8006F41C(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 0);
        if (arg0->unk2 == 1) {
            arg0->unk24 = FIXED(-2);
            arg0->unk6++;
        } else {
            arg0->unk5 = 1;
            arg0->unk6 = 0;
            arg0->unk7 = 0;
        }
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8006F494(struct MainObj* arg0)
{
    s32 y_diff;

    y_diff = g_Player.y_pos.val - arg0->y_pos.val;
    if (y_diff >= 0) {
        if (y_diff <= 0xFFFFF) {
            goto set_state;
        }
    } else if (arg0->y_pos.val - g_Player.y_pos.val <= 0xFFFFF) {
    set_state:
        arg0->unk5 = 1;
        arg0->unk6 = 0;
    }
    func_80015DC8(arg0);
}

void func_8006F504(struct MainObj* arg0)
{
    D_80100800[arg0->unk6](arg0);
    arg0->unk20 = background_objects[arg0->bg_offset].unk47 << 0x10;
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_8006F584(struct MainObj* arg0)
{
    if (arg0->unk7 == 0) {
        arg0->unk7++;
        func_80015D60(arg0, 4);
    }
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk7 = 0;
        arg0->unk7C = 0;
        arg0->ext.main_55.unk85 = 0;
        arg0->ext.main_55.unk86 = 0;
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006F5F4);

void func_8006F7B4(struct MainObj* arg0)
{
    D_80100810[arg0->unk6](arg0);
    arg0->unk20 = background_objects[arg0->bg_offset].unk47 << 0x10;
    func_80015DC8(arg0);
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_8006F83C(struct MainObj* arg0)
{
    func_80015DC8(arg0);
    func_8002B718(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006F86C);

void func_8006FA24(struct MainObj* self)
{
    if (func_8002DD04(self) < 0) {
        self->unk5 = 7;
        self->unk6 = 0;
    }

    func_8002D9BC(BASE_OBJECT(self));
    D_80100818[self->unk5](self);

    if (func_8002B1E8(BASE_OBJECT(self), 0x80, 0x60) == 0) {
        func_8002B318(BASE_OBJECT(self), 0x40, 0x30);
    } else {
        self->state = 2;
    }
}

void func_8006FABC(struct MainObj* arg0)
{
    engine_obj.enable_boss = 0;
    func_8002B108(OBJECT_HEADER(arg0));
}

void func_8006FAE4(struct MainObj* arg0)
{
    D_80100838[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006FB20);

struct VisualObj* jet_stingray_spawn_splash(struct MainObj* self)
{
    struct VisualObj* visual = find_free_visual_obj();

    if (visual != 0) {
        visual->active = 0x41;
        visual->id = 0x17;
        visual->unk2 = 2;
        visual->x_pos.val = self->x_pos.val;
        visual->y_pos.val = self->y_pos.val - FIXED(8);
        visual->unk40 = self->unk40;
        visual->animation_table = ANIMATED_OBJECT(self)->animation_table;
        visual->unk3C = ANIMATED_OBJECT(self)->unk3C;
        visual->unk15 = self->unk15;
        visual->bg_offset = self->bg_offset;
        visual->unk50 = PLAYER_OBJECT(self);
        func_8001540C(2, 0xAE, self);
        return visual;
    }
    return 0;
}

s32 jet_stingray_check_surface(struct PlayerObj* self, s32 arg1, s32 arg2)
{
    s16 temp_a1;
    s16 temp_a2;
    s32 temp_v0;
    u8 tile;
    s32 temp_v1;
    s32 var_v0;

    temp_a1 = self->x_pos.u.hi + arg1;
    temp_a2 = self->y_pos.u.hi + arg2;
    temp_v0 = ((s32(*)(struct PlayerObj*, s16, s16))func_8002D724)(
        self, temp_a1, temp_a2);
    tile = temp_v0;
    var_v0 = 1;
    if ((u32)((temp_v0 - 0x10) & 0xFF) >= 9U) {
        temp_v1 = tile;
        if (temp_v1 == 0x38) {
            return (self->y_pos.i.hi >= 0x121) * 2;
        }
        var_v0 = -(temp_v1 == 0x24) & 3;
        return var_v0;
    }
    return var_v0;
}
