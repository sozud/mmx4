// ItemObj, item_object_update_funcs[15]
// 800C3CF8..800C3FEC
#include "common.h"

void rising_slab_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    rising_slab_state_funcs[arg0->state](arg0);
}

void rising_slab_init(struct ItemObj* arg0)
{
    arg0->unk16 = 6;
    arg0->animation_table = NULL;
    arg0->animation_step.fields.frame_index = (u8)arg0->unk2;
    arg0->unk40 = D_801406A8[func_8002938C(0x89)] >> 7;
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[func_8002938C(0x89)];
    arg0->unk42 = 0x7943;
    arg0->unk5C = 0;
    arg0->unk61 = 0;
    arg0->unk68 = (struct Unk_unk68*)rising_slab_terrain_boxes[arg0->unk2];
    arg0->unk50 = NULL;
    arg0->unk54 = NULL;
    arg0->unk58 = NULL;
    arg0->unk15 = 0;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = FIXED(0.0625);
    arg0->unk75 = 1;
    arg0->unk76 = 0;
    arg0->unk7C.timer = 0;
    arg0->ext.packed = 0;
    update_on_screen(BASE_OBJECT(arg0), 0x40, 0x60);
    func_8001540C(5, 3, NULL);
    arg0->state = 1;
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/items/item_15_rising_slab", rising_slab_rise);
#else
void rising_slab_rise(struct ItemObj* arg0)
{
    if (!(++arg0->unk7C.timer & 7)
        && (!(background_objects[0].unk34 & 0x10)
            || (background_objects[0].unk3E.bytes[0] & 7) != 2)) {
        start_screen_shake_x(8, 2, 2);
    }
    move_with_gravity(ANIMATED_OBJECT(arg0));
    if (arg0->y_vel.val < FIXED(-1)) {
        arg0->y_vel.val = FIXED(-1);
        arg0->unk2C = 0;
    }
    arg0->unk68 = (struct Unk_unk68*)rising_slab_crush_boxes[arg0->unk2];
    if (!(arg0->unk7C.timer & 7)) {
        func_800B0CA0(0x10, (arg0->ext.packed + 3) & 0xFF, MAIN_OBJECT(arg0), 4, 1);
        arg0->ext.packed ^= 1;
    }
    arg0->unk68 = (struct Unk_unk68*)rising_slab_terrain_boxes[arg0->unk2];
    collide_with_players(PLAYER_OBJECT(arg0));
    update_on_screen(BASE_OBJECT(arg0), 0x40, 0x60);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x40, 0x60) == 1) {
        arg0->state = 2;
    }
}
#endif

void rising_slab_finish(struct ItemObj* arg0)
{
    stop_sound(5U, 3U);
    func_8001540C(5, 4, NULL);
    arg0->unk7C.timer = 0;
    arg0->ext.timer = 0;
    arg0->on_screen = 0;
    despawn_object(OBJECT_HEADER(arg0));
}

void (*rising_slab_state_funcs[])(struct ItemObj*) = {
    rising_slab_init,
    rising_slab_rise,
    rising_slab_finish,
};

u8 rising_slab_crush_boxes[4][16] = {
    { 0x00, 0xD8, 0x30, 0x28 },
    { 0x00, 0x28, 0x30, 0x28 },
    { 0x00, 0xD8, 0x30, 0x30 },
    { 0x00, 0x30, 0x30, 0x28 },
};

u8 rising_slab_terrain_boxes[4][16] = {
    { 0x00, 0xB8, 0x30, 0x10 },
    { 0x00, 0x48, 0x30, 0x10 },
    { 0x00, 0xC0, 0x30, 0x10 },
    { 0x00, 0x40, 0x30, 0x10 },
};
