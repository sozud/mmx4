// ItemObj, item_object_update_funcs[17]
// 800C413C..800C42EC
#include "common.h"

struct Item17SpawnPosition {
    s16 x;
    s16 y;
};

u8 crumble_trigger_boxes_0[4][4] = {
    { 0xB0, 0xE0, 0x10, 0x10 },
    { 0xD0, 0xF0, 0x10, 0x10 },
    { 0xF0, 0x00, 0x10, 0x10 },
    { 0x40, 0x10, 0x40, 0x10 },
};
u8 crumble_trigger_boxes_1[4][4] = {
    { 0xA0, 0xE0, 0x20, 0x10 },
    { 0xE0, 0xF0, 0x20, 0x10 },
    { 0x20, 0x00, 0x20, 0x10 },
    { 0x60, 0x20, 0x20, 0x10 },
};
u8 crumble_trigger_boxes_2[4][4] = {
    { 0xB0, 0xD0, 0x20, 0x10 },
    { 0xF0, 0xF0, 0x20, 0x10 },
    { 0x30, 0x10, 0x20, 0x10 },
    { 0x70, 0x30, 0x20, 0x10 },
};
u8 crumble_trigger_boxes_3[4] = { 0, 0, 0x20, 0x10 };
u8 crumble_trigger_boxes_4[4][4] = {
    { 0x60, 0xD0, 0x20, 0x10 },
    { 0x20, 0xF0, 0x20, 0x10 },
    { 0xE0, 0x10, 0x20, 0x10 },
    { 0xA0, 0x30, 0x20, 0x10 },
};
u8 crumble_trigger_boxes_5[4][4] = {
    { 0x60, 0xD0, 0x20, 0x10 },
    { 0x20, 0xF0, 0x20, 0x10 },
    { 0xE0, 0x00, 0x20, 0x10 },
    { 0xA0, 0x20, 0x20, 0x10 },
};

u8* crumble_trigger_box_sets[6] = {
    crumble_trigger_boxes_0,
    crumble_trigger_boxes_1,
    crumble_trigger_boxes_2,
    crumble_trigger_boxes_3,
    crumble_trigger_boxes_4,
    crumble_trigger_boxes_5,
};

struct Item17SpawnPosition crumble_trigger_positions[6] = {
    { 0x0D80, 0x01D0 },
    { 0x0FA0, 0x0290 },
    { 0x11C0, 0x0320 },
    { 0x1390, 0x02F0 },
    { 0x1500, 0x0350 },
    { 0x1360, 0x0480 },
};

void crumble_trigger_init(struct ItemObj* arg0)
{
    arg0->active = 1;
    arg0->state = arg0->state + 1;
    arg0->animation_table = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->sprite_frames = 0;
    arg0->unk16 = 6;
    arg0->unk15 = 0;
    arg0->on_screen = 0;
    arg0->x_pos.val = crumble_trigger_positions[arg0->unk2].x << 16;
    arg0->y_pos.val = crumble_trigger_positions[arg0->unk2].y << 16;
    arg0->unk7C.object = crumble_trigger_box_sets[arg0->unk2];
}

void crumble_trigger_wait_player(struct ItemObj* self)
{
    u8 i;
    struct EffectObj* effect;

    for (i = 0; i < 4; i++) {
        self->unk68 = &self->unk7C.bounds[i];
        if (func_8002C160(self, &g_Player) != 0) {
            effect = find_free_effect_obj();
            if (effect != NULL) {
                effect->active = 1;
                effect->id = 0x15;
                effect->unk2 = 4;
                effect->ext.effect_21.index = self->unk2 + 8;
            }
            self->state++;
            return;
        }
        if (self->unk2 == 3) {
            return;
        }
    }
}

void crumble_trigger_despawn(struct ItemObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void crumble_trigger_update(struct ItemObj* arg0)
{
    crumble_trigger_state_funcs[arg0->state](arg0);
}

void (*crumble_trigger_state_funcs[])(struct ItemObj*) = {
    crumble_trigger_init,
    crumble_trigger_wait_player,
    crumble_trigger_despawn,
};
