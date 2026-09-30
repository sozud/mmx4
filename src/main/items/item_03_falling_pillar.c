// ItemObj, item_object_update_funcs[3]
// 800C0404..800C081C
#include "common.h"

struct Item03StageEntry falling_pillar_entries[22] = {
    { 0x0DE0, 0x0218, 0x03B0, 0x0E50, 0x0DF8, 0x000B, 0x0050, 0x0018 },
    { 0x0DE0, 0x0248, 0x03B0, 0x0E50, 0x0E08, 0x000C, 0x0050, 0x0018 },
    { 0x0DE0, 0x0278, 0x03B0, 0x0E50, 0x0E18, 0x0014, 0x0050, 0x0018 },
    { 0x0DE0, 0x02A8, 0x03B0, 0x0E50, 0x0E28, 0x000C, 0x0050, 0x0018 },
    { 0x0DE0, 0x02D8, 0x03B0, 0x0E50, 0x0E38, 0x0014, 0x0050, 0x0018 },
    { 0x0DE0, 0x0308, 0x03B0, 0x0E50, 0x0E48, 0x000C, 0x0050, 0x0018 },
    { 0x0DE0, 0x0338, 0x03B0, 0x0E50, 0x0E50, 0x0014, 0x0050, 0x0018 },
    { 0x0DE0, 0x0368, 0x03B0, 0x0E50, 0x0E50, 0x000C, 0x0050, 0x0018 },
    { 0x0DE0, 0x0398, 0x03B0, 0x0E50, 0x0E50, 0x0014, 0x0050, 0x0018 },
    { 0x0DE0, 0x03C8, 0x03B0, 0x0E50, 0x0E50, 0x000C, 0x0050, 0x0018 },
    { 0x0F60, 0x0218, 0x03B0, 0x0EF0, 0x0EF0, 0x000D, 0x0050, 0x0018 },
    { 0x0F60, 0x0248, 0x03B0, 0x0EF0, 0x0EF0, 0x000E, 0x0050, 0x0018 },
    { 0x0F60, 0x0278, 0x03B0, 0x0EF0, 0x0EF0, 0x0015, 0x0050, 0x0018 },
    { 0x0F60, 0x02A8, 0x03B0, 0x0EF0, 0x0EF0, 0x000E, 0x0050, 0x0018 },
    { 0x0F60, 0x02D8, 0x03B0, 0x0EF0, 0x0F08, 0x0015, 0x0050, 0x0018 },
    { 0x0F60, 0x0308, 0x03B0, 0x0EF0, 0x0F18, 0x000E, 0x0050, 0x0018 },
    { 0x0F60, 0x0338, 0x03B0, 0x0EF0, 0x0F28, 0x0015, 0x0050, 0x0018 },
    { 0x0F60, 0x0368, 0x03B0, 0x0EF0, 0x0F38, 0x000E, 0x0050, 0x0018 },
    { 0x0F60, 0x0398, 0x03B0, 0x0EF0, 0x0F48, 0x0015, 0x0050, 0x0018 },
    { 0x0F60, 0x03C8, 0x03B0, 0x0EF0, 0x0F58, 0x000E, 0x0050, 0x0018 },
    { 0x0DE0, 0x01E8, 0x03B0, 0x0E50, 0x0E50, 0x0011, 0x0050, 0x0018 },
    { 0x0F60, 0x01E8, 0x03B0, 0x0EF0, 0x0EF8, 0x0012, 0x0050, 0x0018 },
};

u8 falling_pillar_box[4] = { 0x00, 0x08, 0x50, 0xF0 };

void falling_pillar_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    falling_pillar_state_funcs[arg0->state](arg0);
}

// falling_pillar_init
INCLUDE_ASM("main/nonmatchings/items/item_03_falling_pillar", func_800C044C);

void falling_pillar_wait_player(struct ItemObj* arg0)
{
    s8 index;

    index = arg0->unk2;
    if (g_Player.y_pos.i.hi >= falling_pillar_entries[index].velocity) {
        if (index == 0) {
            func_8001540C(5, 2, NULL);
        }
        arg0->unk7C.timer = 10;
        arg0->state++;
    }
    update_on_screen(BASE_OBJECT(arg0), falling_pillar_entries[arg0->unk2].width, falling_pillar_entries[arg0->unk2].height);
}

// falling_pillar_fall
void func_800C05FC(struct ItemObj* pillar)
{
    s32 in_range;
    u16 right;

    if (pillar->unk2 < 0xA || pillar->unk2 == 0x14) {
        if (pillar->x_pos.i.hi >= falling_pillar_entries[pillar->unk2].trigger_x && pillar->ext.packed == 0) {
            apply_tile_effect(pillar->unk2 + 0xB, 0, 0);
            pillar->ext.packed = 1;
        }
        right = falling_pillar_entries[pillar->unk2].right;
        in_range = pillar->x_pos.i.hi < right;
    } else {
        if (pillar->x_pos.i.hi <= falling_pillar_entries[pillar->unk2].trigger_x && pillar->ext.packed == 0) {
            apply_tile_effect(pillar->unk2 + 0xB, 0, 0);
            pillar->ext.packed = 1;
        }
        right = falling_pillar_entries[pillar->unk2].right;
        in_range = pillar->x_pos.i.hi > right;
    }
    if (in_range == 0) {
        pillar->x_pos.i.hi = right;
        pillar->state++;
    }
    if (--pillar->unk7C.timer == 0 && pillar->unk2 == 0) {
        pillar->unk7C.timer = 0x28;
        start_screen_shake_x(0x20, 3, 1);
    }
    move_object(MOVING_OBJECT(pillar));
    if (pillar->unk2 == 4 || pillar->unk2 == 0xE) {
        collide_with_players(pillar);
    }
    update_on_screen(BASE_OBJECT(pillar), falling_pillar_entries[pillar->unk2].width, falling_pillar_entries[pillar->unk2].height);
}

void falling_pillar_finish(struct ItemObj* arg0)
{
    if (arg0->unk2 == 0) {
        func_8001540C(5, 0, NULL);
        start_screen_shake_y(0x20, 2, 1);
    }
    arg0->unk7C.timer = 0;
    arg0->ext.timer = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*falling_pillar_state_funcs[])(struct ItemObj*) = {
    func_800C044C,
    falling_pillar_wait_player,
    func_800C05FC,
    falling_pillar_finish,
};
