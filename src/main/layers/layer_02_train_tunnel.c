// LayerObj, layer_object_update_funcs[2]
// 800D9218..800D9C84
#include "common.h"

s16 train_tunnel_lock_positions[4] = { 0x16B0, 0x1DE0, 0x2700, 0x2710 };

void train_tunnel_update(struct LayerObj* arg0)
{
    train_tunnel_state_funcs[arg0->state](arg0);
    func_800D9B48(arg0);
}

// train_tunnel_init
INCLUDE_ASM("main/nonmatchings/layers/layer_02_train_tunnel", func_800D9268);

void train_tunnel_main(struct LayerObj* arg0)
{
    f32* bg1_x = &background_objects[1].x_pos;

    arg0->unk15 = (u8)arg0->bg_offset;
    train_tunnel_update_section(arg0);
    train_tunnel_section_funcs[arg0->unk5](arg0);
    bg1_x->val += arg0->unk18.val;
    background_objects[2].x_pos.val += arg0->unk18.val >> 1;
    switch (arg0->unk17) {
    case 1:
        train_tunnel_shake_running(arg0);
        break;
    case 2:
        train_tunnel_shake_braking(arg0);
        break;
    }
    train_tunnel_spawn_scroll_prop(arg0);
}

void train_tunnel_despawn(struct LayerObj* arg0)
{
    despawn_object_permanently(arg0);
}

void train_tunnel_section_0(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        train_tunnel_section_0_wait(arg0);
    } else {
        train_tunnel_section_0_skip(arg0);
    }
}

void train_tunnel_section_0_wait(struct LayerObj* arg0)
{
    arg0->unk6++;
}

void train_tunnel_section_0_skip(struct LayerObj* arg0)
{
    arg0->unk5 = 5;
    arg0->unk6 = 0;
}

void train_tunnel_section_1(struct LayerObj* arg0)
{
    switch (arg0->unk6) {
    case 0:
        train_tunnel_wait_stop_point(arg0);
        return;
    case 1:
        train_tunnel_start_braking(arg0);
        return;
    case 2:
        train_tunnel_brake(arg0);
        return;
    }
}

void train_tunnel_wait_stop_point(struct LayerObj* arg0)
{
    switch (arg0->unk7) {
    case 0:
        if (train_tunnel_player_at_lock(arg0)) {
            background_objects[0].unk24 = 0x16B0;
            background_objects[0].unk26 = 0x16B0;
            player_start_script_action(0x14, 0x40);
            arg0->unk7 = 1;
            return;
        }
        return;
    case 1:
        if (get_layout_screen(1, 0x40, 0x40) == 0x1E) {
            arg0->unk7 = 2;
            return;
        }
        break;
    case 2:
        if (get_layout_screen(1, 0x40, 0x40) == 0x18) {
            arg0->unk7 = 0;
            arg0->unk6++;
        }
        break;
    }
}

void train_tunnel_start_braking(struct LayerObj* arg0)
{
    arg0->unk17 = 2;
    engine_obj.character_state.bytes[0] = 1;
    func_8001540C(5, 0xA, NULL);
    arg0->unk7 = 0;
    arg0->unk6++;
}

void train_tunnel_brake(struct LayerObj* arg0)
{
    s32 temp_v1;

    if (arg0->unk7 == 0) {
        if (arg0->unk18.val != 0) {
            arg0->unk18.val -= 0x800;
            return;
        }
        background_objects[0].unk1C = 0x24E0;
        background_objects[0].unk24 = 0x24E0;
        player_end_script_action();
        func_8001540C(5, 0xB, NULL);
        arg0->unk7 = 1;
        arg0->unk17 = 0;
        return;
    }
    if (g_Player.update_delay == 0) {
        temp_v1 = background_objects[0].x_pos.val - background_objects[0].unk14.val;
        background_objects[1].x_pos.val += temp_v1;
        background_objects[2].x_pos.val += temp_v1 >> 1;
    }
}

void train_tunnel_section_2(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        train_tunnel_start_departure(arg0);
    } else {
        train_tunnel_accelerate(arg0);
    }
}

void train_tunnel_start_departure(struct LayerObj* arg0)
{
    if (engine_obj.checkpoint != 3) {
        background_objects[0].unk26 = 0x1DE0;
        player_start_script_action(0x14, 0x40);
        func_8001540C(5, 9, NULL);
        arg0->unk18.val = FIXED(2);
    } else {
        arg0->unk18.val = FIXED(8);
    }

    arg0->unk17 = 1;
    engine_obj.character_state.bytes[0] = 0;
    arg0->unk7 = 0;
    arg0->unk6++;
}

void train_tunnel_accelerate(struct LayerObj* arg0)
{
    if (background_objects[0].x_pos.i.hi == background_objects[0].unk26 && g_Player.script_state < 0) {
        player_end_script_action();
    }
    if (arg0->unk18.val != 0x80000) {
        arg0->unk18.val += 0x400;
    } else {
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}

void train_tunnel_section_3(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        train_tunnel_section_3_wait(arg0);
    } else {
        train_tunnel_section_3_skip(arg0);
    }
}

void train_tunnel_section_3_wait(struct LayerObj* arg0)
{
    arg0->unk7 = 0;
    arg0->unk6++;
}

void train_tunnel_section_3_skip(struct LayerObj* arg0)
{
    arg0->unk5 = 5;
    arg0->unk6 = 0;
}

void train_tunnel_section_4(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        train_tunnel_section_4_wait(arg0);
    } else {
        train_tunnel_section_4_skip(arg0);
    }
}

void train_tunnel_section_4_wait(struct LayerObj* arg0)
{
    arg0->unk7 = 0;
    arg0->unk6++;
}

void train_tunnel_section_4_skip(struct LayerObj* arg0)
{
    arg0->unk5 = 5;
    arg0->unk6 = 0;
}

void train_tunnel_idle(struct LayerObj* arg0)
{
}

void train_tunnel_update_section(struct LayerObj* arg0)
{
    s16 player_x = g_Player.x_pos.i.hi;
    s8 offset = 0;

    while (1) {
        if (player_x - train_tunnel_lock_positions[offset] < 0) {
            break;
        }
        offset++;
        if (offset >= 4) {
            break;
        }
    }
    arg0->bg_offset = offset;
    if (offset != arg0->unk15) {
        arg0->unk5 = offset;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
    }
}

void train_tunnel_shake_running(struct LayerObj* arg0)
{
    if (--arg0->unk16 == 0) {
        start_screen_shake_y(0x30, 2, 1);
        arg0->unk16 = 0x78;
    }
}

void train_tunnel_shake_braking(struct LayerObj* arg0)
{
    if (--arg0->unk16 == 0) {
        start_screen_shake_y(0x10, 1, 1);
        arg0->unk16 = 0x1E;
    }
}

void train_tunnel_spawn_scroll_prop(struct LayerObj* arg0)
{
    struct MiscObj* misc;
    u8 state = arg0->private_state.value.bytes[0];

    if (state != 1) {
        if (state == 0) {
            if ((s16)get_layout_screen(1, 0, 0x40) == 0x18) {
                misc = find_free_misc_obj();
                if (misc != 0) {
                    misc->active = 0x41;
                    misc->id = 0x14;
                    misc->ext.misc_20.owner = arg0;
                    arg0->private_state.value.bytes[0] = 1;
                }
            }
        } else if ((s16)get_layout_screen(1, 0, 0x40) != 0x18) {
            arg0->private_state.value.bytes[0] = 0;
        }
    }
}

u8 train_tunnel_player_at_lock(struct LayerObj* arg0)
{
    s32 left = train_tunnel_lock_positions[(u8)arg0->bg_offset - 1];
    s32 x = g_Player.x_pos.i.hi;
    if (x >= left && x <= left + 0x10) {
        return 1;
    }
    return 0;
}

// train_tunnel_update_lights
INCLUDE_ASM("main/nonmatchings/layers/layer_02_train_tunnel", func_800D9B48);

void (*train_tunnel_state_funcs[])(struct LayerObj*) = {
    func_800D9268,
    train_tunnel_main,
    train_tunnel_despawn,
};

void (*train_tunnel_section_funcs[])(struct LayerObj*) = {
    train_tunnel_section_0,
    train_tunnel_section_1,
    train_tunnel_section_2,
    train_tunnel_section_3,
    train_tunnel_section_4,
    train_tunnel_idle,
};
