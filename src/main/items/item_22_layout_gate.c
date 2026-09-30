// ItemObj, item_object_update_funcs[22]
// 800C5544..800C5C4C
#include "common.h"

struct Item22LayoutDescriptor {
    u8 start;
    u8 length;
    u16 unused;
    u8* data;
};

struct Item22AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

u8 layout_gate_row_0[8] = { 0x3E, 0x3F, 0x43, 0x0B, 0x0C, 0, 0, 0 };
u8 layout_gate_row_1[8] = { 0x08, 0x09, 0x44, 0x41, 0x42, 0, 0, 0 };
u8 layout_gate_row_2[8] = { 0x3E, 0x3F, 0x40, 0x41, 0x42, 0, 0, 0 };
u8 layout_gate_row_3[4] = { 0x45, 0x46, 0, 0 };
u8 layout_gate_row_4[4] = { 0x47, 0x48, 0, 0 };
u8 layout_gate_row_5[4] = { 0x49, 0x4A, 0x4B, 0 };
u8 layout_gate_row_6[4] = { 0x4C, 0x4D, 0x4E, 0 };

struct Item22LayoutDescriptor layout_gate_layouts[7] = {
    { 4, 5, 0, layout_gate_row_0 },
    { 4, 5, 0, layout_gate_row_1 },
    { 4, 5, 0, layout_gate_row_2 },
    { 0x0B, 2, 0, layout_gate_row_3 },
    { 0x0D, 2, 0, layout_gate_row_4 },
    { 0x0F, 3, 0, layout_gate_row_5 },
    { 0x13, 3, 0, layout_gate_row_6 },
};

u8 layout_gate_terrain_box[4] = { 0, 0, 8, 8 };
u8 layout_gate_hurt_box[4] = { 0xF8, 0xF8, 0x10, 0x10 };
u8 layout_gate_frames[4] = { 3, 6, 4, 5 };

struct Item22AnimationStep layout_gate_anim_0 = { 1, 1, 0, 0 };

struct Item22AnimationStep layout_gate_anim_1 = { 1, 0, 0, 1 };

struct Item22AnimationStep layout_gate_anim_2 = { 1, 0, 0, 2 };

struct Item22AnimationStep layout_gate_anim_3 = { 1, 0, 0, 3 };

struct Item22AnimationStep layout_gate_anim_4 = { 1, 0, 0, 4 };

struct Item22AnimationStep layout_gate_anim_5 = { 1, 0, 0, 5 };

struct Item22AnimationStep layout_gate_anim_6 = { 1, 0, 0, 6 };

struct Item22AnimationStep layout_gate_anim_7 = { 1, 0, 0, 7 };

struct Item22AnimationStep layout_gate_anim_8 = { 1, 0, 0, 8 };

struct Item22AnimationStep layout_gate_anim_9 = { 1, 0, 0, 9 };

struct Item22AnimationStep* layout_gate_animations[10] = {
    &layout_gate_anim_0,
    &layout_gate_anim_1,
    &layout_gate_anim_2,
    &layout_gate_anim_3,
    &layout_gate_anim_4,
    &layout_gate_anim_5,
    &layout_gate_anim_6,
    &layout_gate_anim_7,
    &layout_gate_anim_8,
    &layout_gate_anim_9,
};

void layout_gate_update(struct ItemObj* arg0)
{
    layout_gate_state_funcs[arg0->state](arg0);
}

void layout_gate_init(struct ItemObj* self)
{
    s32 rand_x;
    s32 rand_y;
    s32 x_offset;
    s32 frame_index;
    const u8* archive;
    s8 state;

    self->unk54 = layout_gate_hurt_box;
    self->unk58 = (u8*)D_80108584;
    self->bg_offset = g_Player.bg_offset;
    self->unk5C = 3;
    self->unk40 = D_801406A8[func_8002938C(0x28)] >> 7;

    rand_x = func_8002938C(0x28);
    rand_y = func_8002938C(0x28);
    x_offset = rand_x * 4 + 0x18;
    self->unk42 = (x_offset % 16) | (((rand_y + 6) / 4 + 0x1E0) << 6);

    frame_index = func_8002938C(0x28) * 4;
    archive = (const u8*)SP_MENU_FRAMES;
    state = self->state + 1;
    self->sprite_frames = archive + *(const s32*)((unsigned long)frame_index + (unsigned long)archive);

    self->bg_offset = g_Player.bg_offset;
    self->animation_table = (u8**)layout_gate_animations;
    self->unk7C.timer = 0xC8;
    self->ext.packed = 0;
    self->state = state;
    self->unk5 = 0;
}

void layout_gate_main(struct ItemObj* arg0)
{
    layout_gate_step_funcs[arg0->unk5](arg0);
}

void layout_gate_despawn(struct ItemObj* arg0)
{
    despawn_object(OBJECT_HEADER(arg0));
}

void layout_gate_finish(struct ItemObj* arg0)
{
    func_8002B560(0x25, arg0->unk2);
    g_FilterAmountR = 0;
    g_FilterAmountG = 0;
    g_FilterAmountB = 0;
    need_palette_load |= 1;
    despawn_object_permanently(OBJECT_HEADER(arg0));
}

void layout_gate_wait_hit(struct ItemObj* arg0)
{
    if (func_8002DD04(MAIN_OBJECT(arg0)) < 0) {
        arg0->ext.item_22.collision_side = 1;
        arg0->unk5++;
        layout_gate_spawn_alarm(arg0);
        return;
    }
    arg0->x_pos.i.hi += 0x1A0;
    if (func_8002DD04(MAIN_OBJECT(arg0)) < 0) {
        arg0->unk5++;
        layout_gate_spawn_alarm(arg0);
        arg0->ext.item_22.collision_side = 2;
    }
    arg0->x_pos.i.hi -= 0x1A0;
}

// layout_gate_open
INCLUDE_ASM("main/nonmatchings/items/item_22_layout_gate", func_800C580C);

void layout_gate_apply_layout(struct ItemObj* arg0)
{
    u8 start;
    u8 end;
    u8* data;

    start = layout_gate_layouts[arg0->unk2].start;
    end = start + layout_gate_layouts[arg0->unk2].length;
    data = layout_gate_layouts[arg0->unk2].data;
    while (start < end) {
        D_80141BE8[layout_width + start] = *data++;
        start++;
    }
    background_objects[0].unk4C = 1;
}

// layout_gate_restore_layout
INCLUDE_ASM("main/nonmatchings/items/item_22_layout_gate", func_800C5994);

void layout_gate_check_layout(struct ItemObj* arg0)
{
    arg0->tail_ext.unk1.unk84.bytes[0] = arg0->unk2;

    switch (arg0->unk2) {
    case 0:
        if (D_80141BE8[layout_width + 6] == 0x44) {
            arg0->unk2 = 2;
        }
        break;
    case 1:
        if (D_80141BE8[layout_width + 6] == 0x43) {
            arg0->unk2 = 2;
        }
        break;
    }
}

void layout_gate_spawn_alarm(struct ItemObj* arg0)
{
    struct EffectObj* effect;

    effect = find_free_effect_obj();
    if (effect != NULL) {
        effect->active = 1;
        effect->id = 0x25;
        effect->unk2 = (u8)arg0->unk2;
        effect->x_pos.val = arg0->x_pos.val;
        effect->y_pos.val = arg0->y_pos.val;
        effect->ext.effect_37.unk1E = 0x2D;
        effect->ext.effect_37.unk1F = 4;
        effect->ext.effect_37.unk20 = 3;
        effect->ext.effect_37.unk21 = 0x14;
    }
}

void (*layout_gate_state_funcs[])(struct ItemObj*) = {
    layout_gate_init,
    layout_gate_main,
    layout_gate_despawn,
    layout_gate_finish,
};

void (*layout_gate_step_funcs[2])(struct ItemObj*) = {
    layout_gate_wait_hit,
    func_800C580C,
};

s32 layout_gate_unused[4] = { 0, 1, 2, 3 };
