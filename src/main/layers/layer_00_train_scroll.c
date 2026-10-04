// LayerObj, layer_object_update_funcs[0]
// 800D8648..800D8ED4
#include "common.h"

void train_scroll_section_0_skip(struct LayerObj* arg0);
void train_scroll_section_0_wait(struct LayerObj* arg0);
void train_scroll_section_1_event(struct LayerObj* arg0);
void train_scroll_section_1_lock(struct LayerObj* arg0);
void train_scroll_section_2_event(struct LayerObj* arg0);
void train_scroll_section_2_lock(struct LayerObj* arg0);
void train_scroll_section_3_event(struct LayerObj* arg0);
void train_scroll_section_3_lock(struct LayerObj* arg0);
void train_scroll_section_4_event(struct LayerObj* arg0);
void train_scroll_section_4_lock(struct LayerObj* arg0);
void train_scroll_shake(struct LayerObj* arg0);

void train_scroll_update_section(struct LayerObj* arg0);

void train_scroll_update(struct LayerObj* arg0)
{
    train_scroll_state_funcs[arg0->state](arg0);
}

void train_scroll_init(struct LayerObj* arg0)
{
    arg0->unk5 = 4;
    arg0->state++;
    arg0->bg_offset = 5;
    arg0->unk18.val = FIXED(8);
    arg0->unk16 = 0x78;
    background_objects[1].unk4D = 2;
    background_objects[1].unk4E = 7;
    background_objects[2].unk4D = 2;
    background_objects[2].unk4E = 5;
    background_objects[0].unk2E = 0xA0;
    background_objects[0].unk2C = 0x30;
    func_8001540C(5, 9, NULL);
    train_scroll_main(arg0);
}

void train_scroll_main(struct LayerObj* arg0)
{
    arg0->unk15 = arg0->bg_offset;
    train_scroll_update_section(arg0);
    train_scroll_section_funcs[arg0->unk5](arg0);
    train_scroll_shake(arg0);
    background_objects[1].x_pos.val += arg0->unk18.val;
    background_objects[2].x_pos.val += arg0->unk18.val >> 1;
}

void train_scroll_despawn(struct LayerObj* arg0)
{
    despawn_object_permanently(arg0);
}

void train_scroll_section_0(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        train_scroll_section_0_wait(arg0);
    } else {
        train_scroll_section_0_skip(arg0);
    }
}

void train_scroll_section_0_wait(struct LayerObj* arg0)
{
    arg0->unk6++;
}

void train_scroll_section_0_skip(struct LayerObj* arg0)
{
    arg0->unk5 = 5;
    arg0->unk6 = 0;
}

void train_scroll_section_1(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        train_scroll_section_1_lock(arg0);
    } else {
        train_scroll_section_1_event(arg0);
    }
}

void train_scroll_section_1_lock(struct LayerObj* arg0)
{
    if (train_scroll_player_at_lock(arg0)) {
        background_objects[0].unk24 = 0x8D0;
        background_objects[0].unk26 = 0x8D0;
        player_start_script_action(0x14, 0x40);
        arg0->unk7 = 0;
        arg0->unk6++;
    }
}

void train_scroll_section_1_event(struct LayerObj* arg0)
{
    if (background_objects[0].x_pos.i.hi == background_objects[0].unk26) {
        train_scroll_event_funcs[arg0->unk7](arg0);
    }
}

void train_scroll_section_2(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        train_scroll_section_2_lock(arg0);
    } else {
        train_scroll_section_2_event(arg0);
    }
}

void train_scroll_section_2_lock(struct LayerObj* arg0)
{
    if (train_scroll_player_at_lock(arg0)) {
        background_objects[0].unk24 = 0xD30;
        background_objects[0].unk26 = 0xD30;
        player_start_script_action(0x14, 0x40);
        arg0->unk7 = 0;
        arg0->unk6++;
    }
}

void train_scroll_section_2_event(struct LayerObj* arg0)
{
    if (background_objects[0].x_pos.i.hi == background_objects[0].unk26) {
        train_scroll_event_funcs[arg0->unk7](arg0);
    }
}

void train_scroll_section_3(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        train_scroll_section_3_lock(arg0);
    } else {
        train_scroll_section_3_event(arg0);
    }
}

void train_scroll_section_3_lock(struct LayerObj* arg0)
{
}

void train_scroll_section_3_event(struct LayerObj* arg0)
{
    if (background_objects[0].x_pos.i.hi == background_objects[0].unk26) {
        train_scroll_event_funcs[arg0->unk7](arg0);
    }
}

void train_scroll_section_4(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        train_scroll_section_4_lock(arg0);
    } else {
        train_scroll_section_4_event(arg0);
    }
}

void train_scroll_section_4_lock(struct LayerObj* arg0)
{
    if (train_scroll_player_at_lock(arg0)) {
        background_objects[0].unk24 = 0x1A50;
        background_objects[0].unk26 = 0x1A50;
        player_start_script_action(0x14, 0x40);
        arg0->unk7 = 0;
        arg0->unk6++;
    }
}

void train_scroll_section_4_event(struct LayerObj* arg0)
{
    if (background_objects[0].x_pos.i.hi == background_objects[0].unk26) {
        train_scroll_event_funcs[arg0->unk7](arg0);
    }
}

void train_scroll_section_5(struct LayerObj* arg0)
{
}

void train_scroll_update_section(struct LayerObj* arg0)
{
    s8 offset = 0;
    s16 player_x = g_Player.x_pos.i.hi;

    while (1) {
        if (player_x - train_scroll_lock_positions[offset] < 0) {
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
    }
}

void train_scroll_spawn_trooper(struct LayerObj* arg0)
{
    struct BaseObj* temp_v0;

    temp_v0 = (struct BaseObj*)find_free_main_obj();
    if (temp_v0 != NULL) {
        temp_v0->active = 0x41;
        temp_v0->id = 0x22;
        temp_v0->unk2 = arg0->bg_offset - 1;
        temp_v0->backref = arg0;
    }
    arg0->unk7++;
}

void train_scroll_spawn_crusher(struct LayerObj* arg0)
{
    struct BaseObj* temp_v0;

    if (arg0->private_state.signed_byte == 1) {
        arg0->unk7++;
        temp_v0 = (struct BaseObj*)find_free_item_obj();
        if (temp_v0 != NULL) {
            temp_v0->active = 0x41;
            temp_v0->id = 0xC;
            temp_v0->unk2 = arg0->bg_offset - 1;
            temp_v0->state = 0;
        }
    }
}

void train_scroll_open_tiles(struct LayerObj* arg0)
{
    u8 temp = arg0->bg_offset;
    switch (temp) {
    case 1:
        apply_tile_effect(0xD, 0x8C0, 0x160);
        apply_tile_effect(0xC, 0x970, 0x190);
        break;
    case 2:
        apply_tile_effect(0, 0xD20, 0x160);
        apply_tile_effect(7, 0xE10, 0x170);
        break;
    case 3:
        apply_tile_effect(0, 0x13B0, 0x160);
        apply_tile_effect(7, 0x14A0, 0x170);
        break;
    case 4:
        apply_tile_effect(0, 0x1A40, 0x160);
        apply_tile_effect(7, 0x1B30, 0x170);
        break;
    }
    arg0->unk7++;
}

void train_scroll_release(struct LayerObj* arg0)
{
    if (g_Player.script_state < 0) {
        player_end_script_action();
        background_objects[0].unk1C = 0x1A50;
        background_objects[0].unk24 = 0x1A50;
        arg0->unk5 = 5;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
        arg0->private_state.signed_byte = 0;
    }
}

void train_scroll_shake(struct LayerObj* arg0)
{
    if (--arg0->unk16 == 0) {
        start_screen_shake_y(0x30, 2, 1);
        arg0->unk16 = 0x78;
    }
}

u8 train_scroll_player_at_lock(struct LayerObj* arg0)
{
    s16 player_x;
    s16 lock_x;

    player_x = g_Player.x_pos.i.hi;
    lock_x = train_scroll_lock_positions[(u8)arg0->bg_offset - 1];
    if (player_x >= lock_x && player_x <= (lock_x + 16))
        return 1;
    return 0;
}

s16 train_scroll_lock_positions[] = { 0x8D0, 0xD30, 0x13C0, 0x1A50 };

void (*train_scroll_state_funcs[])(struct LayerObj*) = {
    train_scroll_init,
    train_scroll_main,
    train_scroll_despawn,
};

void (*train_scroll_section_funcs[])(struct LayerObj*) = {
    train_scroll_section_0,
    train_scroll_section_1,
    train_scroll_section_2,
    train_scroll_section_3,
    train_scroll_section_4,
    train_scroll_section_5,
};

void (*train_scroll_event_funcs[])(struct LayerObj*) = {
    train_scroll_spawn_trooper,
    train_scroll_spawn_crusher,
    train_scroll_open_tiles,
    train_scroll_release,
};
