// ItemObj, item_object_update_funcs[20]
// 800C4CE4..800C52CC
#include "common.h"

struct Item20BackgroundConfig {
    u16 first;
    u16 second;
};

u8 gravity_switch_terrain_box[4] = { 0, 0, 8, 8 };
u8 gravity_switch_hit_box[4] = { 0xF8, 0xF8, 0x10, 0x10 };

struct Item20BackgroundConfig gravity_switch_camera_bounds[8] = {
    { 0x0400, 0x0400 },
    { 0x0300, 0x0300 },
    { 0x0400, 0x0400 },
    { 0x0400, 0x0700 },
    { 0x0400, 0x0700 },
    { 0x0100, 0x0300 },
    { 0x0100, 0x0300 },
    { 0x0100, 0x0300 },
};

void gravity_switch_update(struct ItemObj* arg0)
{
    gravity_switch_state_funcs[arg0->state](arg0);
}

// gravity_switch_init
void func_800C4D20(struct ItemObj* self)
{
    self->active = 0x41;
    self->unk16 = 6;
    self->unk40 = D_801406A8[func_8002938C(0x9C)] >> 7;

    self->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0x9C));

    self->unk42 = SOME_COORDINATE_CONVERSION(func_8002938C(0x9C));

    self->animation_step.fields.frame_index = self->unk2 & 7;
    if (self->unk2 & 8) {
        self->unk15 = 0x40;
    } else {
        self->unk15 = 0;
    }

    self->unk68 = (struct Unk_unk68*)gravity_switch_terrain_box;
    self->unk54 = gravity_switch_hit_box;
    self->unk50 = gravity_switch_hit_box;
    self->unk58 = NULL;
    self->bg_offset = g_Player.bg_offset;
    self->unk61 = 0;
    self->unk75 = 0;
    self->unk67 = 0;
    self->state = 1;
    self->unk5 = 0;
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
}

void gravity_switch_main(struct ItemObj* arg0)
{
    gravity_switch_step_funcs[arg0->unk5](arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

void gravity_switch_wait_touch(struct ItemObj* arg0)
{
    if (func_8002BB80(arg0, &g_Player) != 0) {
        arg0->unk5 = 1;
    }
}

void gravity_switch_activate(struct ItemObj* arg0)
{
    func_8001540C(2, 0xEC, arg0);
    arg0->unk5 = 2;
}

// gravity_switch_flip
INCLUDE_ASM("main/nonmatchings/items/item_20_gravity_switch", func_800C4F40);

void gravity_switch_despawn(struct ItemObj* arg0)
{
    despawn_object(OBJECT_HEADER(arg0));
}

void gravity_switch_flip_objects(void)
{
    u32 i;
    struct MainObj* p1;
    struct MiscObj* p2;
    struct WeaponObj* p3;
    struct ShotObj* p4;
    struct VisualObj* p5;

    p1 = main_objects;
    for (i = 0; i < COUNT(main_objects); p1++, i++) {
        if (p1->active != 0) {
            p1->y_pos.val = FIXED(0x800) - p1->y_pos.val;
            p1->unk1C.val = FIXED(0x800) - p1->unk1C.val;
        }
    }
    p2 = misc_objects;
    for (i = 0; i < COUNT(misc_objects); p2++, i++) {
        if (p2->active != 0) {
            p2->y_pos.val = FIXED(0x800) - p2->y_pos.val;
            p2->unk1C.val = FIXED(0x800) - p2->unk1C.val;
        }
    }
    p3 = weapon_objects;
    for (i = 0; i < COUNT(weapon_objects); p3++, i++) {
        if (p3->active != 0) {
            p3->y_pos.val = FIXED(0x800) - p3->y_pos.val;
            p3->unk1C.val = FIXED(0x800) - p3->unk1C.val;
        }
    }
    p4 = shot_objects;
    for (i = 0; i < COUNT(shot_objects); p4++, i++) {
        if (p4->active != 0) {
            p4->y_pos.val = FIXED(0x800) - p4->y_pos.val;
            p4->unk1C.val = FIXED(0x800) - p4->unk1C.val;
        }
    }
    p5 = visual_objects;
    for (i = 0; i < COUNT(visual_objects); p5++, i++) {
        if (p5->active != 0) {
            p5->y_pos.val = FIXED(0x800) - p5->y_pos.val;
            p5->unk1C.val = FIXED(0x800) - p5->unk1C.val;
        }
    }
}

// gravity_switch_flip_camera
INCLUDE_ASM("main/nonmatchings/items/item_20_gravity_switch", func_800C5210);

void (*gravity_switch_state_funcs[])(struct ItemObj*) = {
    func_800C4D20,
    gravity_switch_main,
    gravity_switch_despawn,
};

void (*gravity_switch_step_funcs[3])(struct ItemObj*) = {
    gravity_switch_wait_touch,
    gravity_switch_activate,
    func_800C4F40,
};
