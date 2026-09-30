// MiscObj, misc_object_update_funcs[4]
// 800C8774..800C8FA8
#include "common.h"

void dragon_rubble_update(struct MiscObj* self)
{
    dragon_rubble_state_funcs[self->state](self);
}

void dragon_rubble_init(struct MiscObj* self)
{
    s16 owner_count;
    s32 adjusted_x;
    s32 random_y;
    s32 random_x;
    s32 resource_index;
    s32 clut_x;
    s32* menu_frame_offsets;
    s32 adjusted_y;
    struct MainObj* owner;

    owner = self->ext.misc_4.owner;
    self->animation_table = dragon_rubble_animations;
    random_x = func_8002938C(0x85);
    random_y = func_8002938C(0x85);
    clut_x = random_x * 4 + 0x18;
    adjusted_x = clut_x;
    if (clut_x < 0) {
        adjusted_x = clut_x + 0xF;
    }
    adjusted_y = random_y + 6;
    clut_x -= (adjusted_x >> 4) * 0x10;
    if (adjusted_y < 0) {
        adjusted_y = random_y + 9;
    }
    self->unk42 = clut_x | (((adjusted_y >> 2) + 0x1E0) << 6);
    resource_index = func_8002938C(0x85, adjusted_y, random_y);
    self->unk40 = D_801406A8[resource_index] >> 7;

    resource_index = func_8002938C(0x85);
    menu_frame_offsets = SP_MENU_FRAMES;
    resource_index = menu_frame_offsets[resource_index];
    self->bg_offset = 0;
    self->unk3C = (u8*)menu_frame_offsets + resource_index;
    self->unk15 = get_random() & 0x40;
    self->unk16 = 7;
    self->x_vel.val = 0;
    spawn_debris(8, dragon_rubble_debris, self);
    spawn_explosion_variant(self, 2);
    func_8001540C(5, 1, self);
    start_screen_shake_y(0x14, 4, 2);

    self->animation_step.fields.frame_index = self->unk2;
    self->state++;
    owner_count = owner->unk7C;
    if (owner_count > 0x14) {
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }
    owner->unk7C = owner_count + 1;
    is_on_screen(BASE_OBJECT(self));
}

void dragon_rubble_wait(struct MiscObj* self)
{
    struct MainObj* temp_s1;

    temp_s1 = self->ext.misc_4.owner;
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
        return;
    }

    temp_s1->unk7C--;
    ZeroObjectState(OBJECT_HEADER(self));
}

// dragon_rubble_b_init
INCLUDE_ASM("main/nonmatchings/misc/misc_04_dragon_rubble", func_800C899C);

void dragon_rubble_b_wait(struct MiscObj* self)
{
    struct MainObj* main_obj;

    main_obj = self->ext.misc_24.main;
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x38, 0x20);
        return;
    }
    main_obj->unk7C = (u16)main_obj->unk7C - 1;
    ZeroObjectState(OBJECT_HEADER(self));
}

// dragon_rubble_c_init
INCLUDE_ASM("main/nonmatchings/misc/misc_04_dragon_rubble", func_800C8BDC);

// dragon_rubble_c_explode
INCLUDE_ASM("main/nonmatchings/misc/misc_04_dragon_rubble", func_800C8E90);

struct Misc04AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

struct Misc04AnimationStep dragon_rubble_anim_steps[14] = {
    { 1, 0, 0, 4 },
    { 1, 0, 0, 5 },
    { 1, 0, 0, 6 },
    { 1, 0, 0, 7 },
    { 1, 0, 0, 14 },
    { 1, 0, 0, 15 },
    { 1, 0, 0, 16 },
    { 1, 0, 0, 17 },
    { 1, 0, 0, 12 },
    { 1, 0, 0, 13 },
    { 1, 0, 0, 8 },
    { 1, 0, 0, 9 },
    { 1, 0, 0, 10 },
    { 1, 0, 0, 11 },
};

u32* dragon_rubble_animations[14] = {
    (u32*)&dragon_rubble_anim_steps[0],
    (u32*)&dragon_rubble_anim_steps[1],
    (u32*)&dragon_rubble_anim_steps[2],
    (u32*)&dragon_rubble_anim_steps[3],
    (u32*)&dragon_rubble_anim_steps[4],
    (u32*)&dragon_rubble_anim_steps[5],
    (u32*)&dragon_rubble_anim_steps[6],
    (u32*)&dragon_rubble_anim_steps[7],
    (u32*)&dragon_rubble_anim_steps[8],
    (u32*)&dragon_rubble_anim_steps[9],
    (u32*)&dragon_rubble_anim_steps[10],
    (u32*)&dragon_rubble_anim_steps[11],
    (u32*)&dragon_rubble_anim_steps[12],
    (u32*)&dragon_rubble_anim_steps[13],
};

u8 dragon_rubble_debris[8] = { 0, 1, 2, 3, 0, 1, 2, 3 };
u8 dragon_rubble_c_debris_0[8] = { 4, 5, 6, 7, 4, 5, 6, 7 };
u8 dragon_rubble_c_debris_1[8] = { 8, 9, 8, 9, 8, 9, 8, 9 };
u8 dragon_rubble_c_debris_2[8] = { 10, 11, 12, 13, 10, 11, 12, 13 };

void (*dragon_rubble_state_funcs[])(struct MiscObj*) = {
    dragon_rubble_init,
    dragon_rubble_wait,
    func_800C899C,
    dragon_rubble_b_wait,
    func_800C8BDC,
    func_800C8E90,
};

struct Misc04SpawnPosition {
    u16 x;
    u16 y;
};

struct Misc04SpawnPosition dragon_rubble_c_positions[3] = {
    { 0x06C0, 0x018D },
    { 0x08C0, 0x018D },
    { 0x0AC0, 0x018D },
};
