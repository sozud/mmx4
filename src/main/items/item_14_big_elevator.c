// ItemObj, item_object_update_funcs[14]
// 800C3880..800C3CF8
#include "common.h"

void big_elevator_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    big_elevator_state_funcs[arg0->state](arg0);
}

void big_elevator_init(struct ItemObj* self)
{
    s32 frame_index;
    s32 frame_offset;
    s32* archive;

    self->active = 0x41;
    self->unk16 = 0x22;
    self->unk15 = 0;
    self->unk40 = D_801406A8[func_8002938C(0x8B) & 0xFF] >> 7;
    frame_index = func_8002938C(0x8B) & 0xFF;
    archive = SP_MENU_FRAMES;
    frame_offset = archive[frame_index];
    self->unk42 = 0x7947;
    self->animation_step.fields.frame_index = 0;
    self->unk68 = &big_elevator_terrain_box;
    self->unk54 = NULL;
    self->unk58 = NULL;
    self->sprite_frames = (u8*)archive + frame_offset;
    self->bg_offset = g_Player.bg_offset;
    self->unk61 = 0;
    self->unk75 = 0;
    self->unk67 = 0;
    self->ext.item_2.unk80 = 1;
    background_objects[0].unk2C = 0;
    self->unk6 = 0;
    self->unk5 = 0;
    self->state++;
}

void big_elevator_main(struct ItemObj* arg0)
{
    big_elevator_step_funcs[arg0->unk5](arg0);
    collide_with_players(PLAYER_OBJECT(arg0));
    update_on_screen(BASE_OBJECT(arg0), 0xC0, 0x80);
}

void big_elevator_next(struct ItemObj* arg0)
{
    arg0->state++;
}

void big_elevator_despawn(struct ItemObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void big_elevator_ride(struct ItemObj* arg0)
{
    big_elevator_ride_funcs[arg0->unk6](arg0);
}

void big_elevator_wait_player(struct ItemObj* arg0)
{
    if (g_Player.unk5 != 0) {
        arg0->unk7C.timer = 0x4000;
        start_screen_shake_y(0x20, 1, 1);
        arg0->unk6 = (u8)arg0->unk6 + 1;
    }
}

void big_elevator_rise(struct ItemObj* arg0)
{
    if (background_objects[0].unk34 != 0) {
        return;
    }

    if (arg0->y_pos.i.hi == 0x8D0) {
        arg0->unk6++;
        return;
    }

    if (arg0->unk7C.timer < 0x10000) {
        arg0->unk7C.timer += FIXED(0.0625);
    }

    arg0->y_pos.val -= arg0->unk7C.timer;
}

void big_elevator_arrive(struct ItemObj* arg0)
{
    background_objects[0].unk28 = 0x2D0;
    background_objects[0].unk2A = 0x2D0;
    background_objects[0].unk47 = 1;
    func_8001540C(5, 5, NULL);
    arg0->unk6 = 0;
    arg0->unk5++;
}

// big_elevator_transition
INCLUDE_ASM("main/nonmatchings/items/item_14_big_elevator", func_800C3BA4);

void big_elevator_restore_camera(struct ItemObj* arg0)
{
    if (background_objects[0].unk34 == 0) {
        background_objects[0].unk22 = 0x100;
        background_objects[0].unk2A = 0x100;
        background_objects[0].unk2C = 0x60;
        arg0->unk5++;
    }
}

void big_elevator_finish(struct ItemObj* arg0)
{
    background_objects[0].unk47 = 2;
}

void (*big_elevator_state_funcs[])(struct ItemObj*) = {
    big_elevator_init,
    big_elevator_main,
    big_elevator_next,
    big_elevator_despawn,
};

void (*big_elevator_step_funcs[4])(struct ItemObj*) = {
    big_elevator_ride,
    func_800C3BA4,
    big_elevator_restore_camera,
    big_elevator_finish,
};

struct Unk_unk68 big_elevator_terrain_box = { 0, 0xFD, 0x80, 0x20 };

void (*big_elevator_ride_funcs[3])(struct ItemObj*) = {
    big_elevator_wait_player,
    big_elevator_rise,
    big_elevator_arrive,
};
