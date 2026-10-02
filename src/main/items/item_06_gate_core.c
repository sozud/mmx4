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
    u8 frame_index;

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
    arg0->unk40 = D_801406A8[frame_index] >> 7;
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[frame_index];
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
        arg0->unk42 = arg0->unk42 | 0x8000;
    } else {
        arg0->unk42 = arg0->unk42 & 0x7FFF;
    }
}

void gate_core_destroyed(struct ItemObj* self)
{
    s32 timer;

    timer = self->unk7C.timer - 1;
    self->unk7C.timer = timer;
    if (timer != 0) {
        if (!(main_bss_state.frame_counter & 7)) {
            func_800AF878(BASE_OBJECT(self), 1, 0x1F, 0x3F);
        }
        if (!(main_bss_state.frame_counter & 0xF)) {
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
    if (g_Player.x_pos.i.hi > gate_core_exit_x[arg0->unk2]) {
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

extern u8 gate_core_box_data[2][8];

extern u8* gate_core_terrain_boxes[2];
extern u8* gate_core_hurt_boxes[2];

extern struct Item06AnimationStep gate_core_anim_steps[6];

extern struct Item06AnimationStep* gate_core_animations[5];

extern u8 gate_core_debris[3][4];

extern u8 gate_core_explosion_sounds[4][4];
extern s16 gate_core_exit_x[2];
extern u16 rising_platform_start_y[2];

extern struct Item06AnimationStep rising_platform_anim_steps[5];

extern struct Item06AnimationStep* rising_platform_animations[5];

extern u8 rising_platform_debris[2][4];
