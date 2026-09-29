// ItemObj, item_object_update_funcs[6]
// 800C1390..800C16F0
#include "common.h"

void gate_core_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    gate_core_state_funcs[arg0->state](arg0);
}

void gate_core_init(struct ItemObj* arg0)
{
    u8 bg_offset;
    s32* archive;
    s32 frame_index;

    arg0->active = 0x41;
    arg0->unk75 = 1;
    bg_offset = g_Player.bg_offset;
    arg0->unk16 = 5;
    arg0->unk5C = 0x20;
    arg0->unk15 = 0;
    arg0->unk61 = 0;
    arg0->bg_offset = bg_offset;
    arg0->unk68 = (struct Unk_unk68*)gate_core_terrain_boxes[arg0->unk2];
    arg0->unk54 = gate_core_hurt_boxes[arg0->unk2];
    arg0->unk58 = (u8*)D_80108504;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->animation_step.fields.frame_index = 0;
    frame_index = func_8002938C(0x98) & 0xFF;
    archive = SP_MENU_FRAMES;
    arg0->unk40 = D_801406A8[frame_index] >> 7;
    arg0->sprite_frames = (u8*)archive + archive[frame_index];
    if (arg0->unk2 == 0) {
        arg0->unk42 = 0x79CE;
    } else {
        arg0->unk42 = 0x7946;
    }
    arg0->animation_table = (const u8* const*)gate_core_animations;
    arg0->state = (u8)arg0->state + 1;
}

void gate_core_main(struct ItemObj* arg0)
{
    s32 collision;
    u16 flags;

    is_on_screen(BASE_OBJECT(arg0));
    collide_with_players(arg0);
    collision = func_8002DD04(MAIN_OBJECT(arg0));
    if (collision < 0) {
        engine_obj.character_state.fields.active = 1;
        arg0->on_screen = 0;
        arg0->unk7C.timer = 0x3C;
        spawn_debris(0xB, gate_core_debris, arg0);
        arg0->state++;
        return;
    }
    if (collision > 0) {
        flags = arg0->unk42 | 0x8000;
    } else {
        flags = arg0->unk42 & 0x7FFF;
    }
    arg0->unk42 = flags;
}

void gate_core_destroyed(struct ItemObj* self)
{
    s32 timer;

    timer = self->unk7C.timer - 1;
    self->unk7C.timer = timer;
    if (timer != 0) {
        if (!(D_80141BD8.unk0 & 7)) {
            func_800AF878(BASE_OBJECT(self), 1, 0x1F, 0x3F);
        }
        if (!(D_80141BD8.unk0 & 0xF)) {
            func_8001540C(0, gate_core_explosion_sounds[get_random() & 3][0], self);
        }
    } else {
        engine_obj.enable_boss = 0;
        engine_obj.boss_ptr = NULL;
        self->state++;
    }
}

void gate_core_exit(struct ItemObj* arg0)
{
    player_start_script_action(0x15, 0x40);
    arg0->state++;
}

void gate_core_wait_exit(struct ItemObj* arg0)
{
    if (gate_core_exit_x[arg0->unk2] < g_Player.x_pos.i.hi) {
        engine_obj.unkF = 0x40;
        despawn_object_permanently(OBJECT_HEADER(arg0));
    }
}

void (*gate_core_state_funcs[])(struct ItemObj*) = {
    gate_core_init,
    gate_core_main,
    gate_core_destroyed,
    gate_core_exit,
    gate_core_wait_exit,
};

struct Item06AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

u8 gate_core_box_data[2][8] = {
    { 0x08, 0x00, 0x08, 0x38, 0x00, 0xC8, 0x08, 0x70 },
    { 0xF8, 0x00, 0x08, 0x38, 0x00, 0xC8, 0x08, 0x70 },
};

u8* gate_core_terrain_boxes[2] = { gate_core_box_data[0], gate_core_box_data[1] };
u8* gate_core_hurt_boxes[2] = { &gate_core_box_data[0][4], &gate_core_box_data[1][4] };

struct Item06AnimationStep gate_core_anim_steps[6] = {
    { 1, 0, 0, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 2 },
    { 1, 0, 0, 3 },
    { 1, 0, 0, 4 },
    { 1, 0, 0, 5 },
};

struct Item06AnimationStep* gate_core_animations[5] = {
    &gate_core_anim_steps[1],
    &gate_core_anim_steps[2],
    &gate_core_anim_steps[3],
    &gate_core_anim_steps[4],
    &gate_core_anim_steps[5],
};

u8 gate_core_debris[3][4] = {
    { 0, 1, 4, 3 },
    { 4, 2, 3, 2 },
    { 2, 3, 4, 0 },
};

u8 gate_core_explosion_sounds[4][4] = { { 0 }, { 1 }, { 2 }, { 3 } };
s16 gate_core_exit_x[2] = { 0x18C0, 0x18E8 };
u16 rising_platform_start_y[2] = { 0x1028, 0x1028 };

struct Item06AnimationStep rising_platform_anim_steps[5] = {
    { 1, 0, 0, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 2 },
    { 1, 0, 0, 3 },
    { 1, 0, 0, 4 },
};

struct Item06AnimationStep* rising_platform_animations[5] = {
    &rising_platform_anim_steps[0],
    &rising_platform_anim_steps[1],
    &rising_platform_anim_steps[2],
    &rising_platform_anim_steps[3],
    &rising_platform_anim_steps[4],
};

u8 rising_platform_debris[2][4] = {
    { 1, 4, 3, 2 },
    { 3, 1, 2, 4 },
};
