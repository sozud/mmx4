// ItemObj, item_object_update_funcs[24]
// 800C6054..800C62DC
#include "common.h"

struct Item24AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

struct Item24AnimationStep breakable_panel_anim_steps[7] = {
    { 1, 0, 0, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 2 },
    { 1, 0, 0, 3 },
    { 1, 0, 0, 4 },
    { 1, 0, 0, 5 },
    { 1, 0, 0, 6 },
};

struct Item24AnimationStep* breakable_panel_animations[7] = {
    &breakable_panel_anim_steps[0],
    &breakable_panel_anim_steps[1],
    &breakable_panel_anim_steps[2],
    &breakable_panel_anim_steps[3],
    &breakable_panel_anim_steps[4],
    &breakable_panel_anim_steps[5],
    &breakable_panel_anim_steps[6],
};

u8 breakable_panel_debris[12] = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 0, 0 };
u8 breakable_panel_terrain_box[4] = { 0, 0, 0x17, 0x26 };
u32 breakable_panel_hit_box = 0x4927DBEC;

void breakable_panel_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    breakable_panel_state_funcs[arg0->state](arg0);
}

// breakable_panel_init
INCLUDE_ASM("main/nonmatchings/items/item_24_breakable_panel", func_800C609C);

void breakable_panel_main(struct ItemObj* arg0)
{
    s32 collision;
    u16 flags;

    collision = func_8002DD04(MAIN_OBJECT(arg0));
    if (collision < 0) {
        arg0->on_screen = 0;
        spawn_debris(0xA, breakable_panel_debris, arg0);
        arg0->unk7C.timer = 0x1E;
        arg0->state++;
        return;
    }
    if (collision > 0) {
        flags = arg0->unk42 | 0x8000;
    } else {
        flags = arg0->unk42 & 0x7FFF;
    }
    arg0->unk42 = flags;
    collide_with_players(arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

extern u32 breakable_panel_explosion_types[];

void breakable_panel_destroyed(struct ItemObj* arg0)
{
    if (--arg0->unk7C.timer != 0) {
        if ((D_80141BD8.unk0 & 7) == 0) {
            func_800AF878(BASE_OBJECT(arg0), 1, 0xF, 0x3F);
        }
        if ((D_80141BD8.unk0 & 0xF) == 0) {
            func_8001540C(0, breakable_panel_explosion_types[get_random() & 3], arg0);
        }
    } else {
        despawn_object_permanently(OBJECT_HEADER(arg0));
    }
}

void (*breakable_panel_state_funcs[])(struct ItemObj*) = {
    func_800C609C,
    breakable_panel_main,
    breakable_panel_destroyed,
};

u32 breakable_panel_explosion_types[4] = { 0, 1, 2, 3 };
