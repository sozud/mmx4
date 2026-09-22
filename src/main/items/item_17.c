// ItemObj, item_object_update_funcs[17]
// 800C413C..800C42EC
#include "common.h"

struct Item17SpawnPosition {
    s16 x;
    s16 y;
};

u8 D_8010D108[4][4] = {
    { 0xB0, 0xE0, 0x10, 0x10 },
    { 0xD0, 0xF0, 0x10, 0x10 },
    { 0xF0, 0x00, 0x10, 0x10 },
    { 0x40, 0x10, 0x40, 0x10 },
};
u8 D_8010D118[4][4] = {
    { 0xA0, 0xE0, 0x20, 0x10 },
    { 0xE0, 0xF0, 0x20, 0x10 },
    { 0x20, 0x00, 0x20, 0x10 },
    { 0x60, 0x20, 0x20, 0x10 },
};
u8 D_8010D128[4][4] = {
    { 0xB0, 0xD0, 0x20, 0x10 },
    { 0xF0, 0xF0, 0x20, 0x10 },
    { 0x30, 0x10, 0x20, 0x10 },
    { 0x70, 0x30, 0x20, 0x10 },
};
u8 D_8010D138[4] = { 0, 0, 0x20, 0x10 };
u8 D_8010D13C[4][4] = {
    { 0x60, 0xD0, 0x20, 0x10 },
    { 0x20, 0xF0, 0x20, 0x10 },
    { 0xE0, 0x10, 0x20, 0x10 },
    { 0xA0, 0x30, 0x20, 0x10 },
};
u8 D_8010D14C[4][4] = {
    { 0x60, 0xD0, 0x20, 0x10 },
    { 0x20, 0xF0, 0x20, 0x10 },
    { 0xE0, 0x00, 0x20, 0x10 },
    { 0xA0, 0x20, 0x20, 0x10 },
};

u8* D_8010D15C[6] = {
    D_8010D108,
    D_8010D118,
    D_8010D128,
    D_8010D138,
    D_8010D13C,
    D_8010D14C,
};

struct Item17SpawnPosition D_8010D174[6] = {
    { 0x0D80, 0x01D0 },
    { 0x0FA0, 0x0290 },
    { 0x11C0, 0x0320 },
    { 0x1390, 0x02F0 },
    { 0x1500, 0x0350 },
    { 0x1360, 0x0480 },
};

void func_800C413C(struct ItemObj* arg0)
{
    u8 state;
    u8 bg_offset;
    s32 index;

    state = arg0->state;
    arg0->active = 1;
    arg0->animation_table = 0;
    arg0->state = state + 1;
    bg_offset = g_Player.bg_offset;
    index = arg0->unk2;
    arg0->sprite_frames = 0;
    arg0->unk16 = 6;
    arg0->unk15 = 0;
    arg0->on_screen = 0;
    arg0->bg_offset = bg_offset;
    arg0->x_pos.val = D_8010D174[index].x << 16;
    arg0->y_pos.val = D_8010D174[arg0->unk2].y << 16;
    arg0->unk7C.object = D_8010D15C[arg0->unk2];
}

void func_800C41C8(struct ItemObj* self)
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

void func_800C4290(struct ItemObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800C42B0(struct ItemObj* arg0)
{
    D_8010D18C[arg0->state](arg0);
}

void (*D_8010D18C[])(struct ItemObj*) = {
    func_800C413C,
    func_800C41C8,
    func_800C4290,
};
