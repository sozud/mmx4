// MiscObj, misc_object_update_funcs[44]
// 800D07EC..800D0E48
#include "common.h"

void stage_cutscene_update(struct MiscObj* self)
{
    stage_cutscene_state_funcs[self->state](self);
}

// stage_cutscene_init
INCLUDE_ASM("main/nonmatchings/misc/misc_44", func_800D0828);

void stage_cutscene_main(struct MiscObj* self)
{
    func_800D0C68(self);
    stage_cutscene_step_funcs[self->unk5](UNK_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x48, 0x48);
}

void stage_cutscene_despawn(struct MiscObj* self)
{
    despawn_object_permanently(OBJECT_HEADER(self));
}

void stage_cutscene_wait_player(struct UnkObj* self)
{
    if (g_Player.x_pos.i.hi >= 0xFE0) {
        player_start_script_action(0x14, 0x40);
        background_objects[g_Player.bg_offset].unk26 = 0xFD0;
        background_objects[g_Player.bg_offset].unk24 = 0xFD0;
        self->unk5 = 1;
    }
}

void stage_cutscene_wait_scroll(struct UnkObj* self)
{
    if (background_objects[g_Player.bg_offset].x_pos.i.hi == 0xFD0) {
        player_start_script_action(0x15, 0);
        self->ext.timer = 0x3C;
        self->unk5 = 2;
    }
}

void stage_cutscene_first_line(struct UnkObj* self)
{
    s8 timer;

    timer = self->ext.timer - 1;
    self->ext.timer = timer;
    if (timer == 0) {
        func_8002217C(0x29, 1, 0);
        self->unk5 = 3;
    }
}

void stage_cutscene_wait_first(struct UnkObj* self)
{
    if (abc_object.unkC == 0) {
        self->ext.timer = 0x3C;
        self->unk5 = 4;
    }
}

void stage_cutscene_second_line(struct UnkObj* self)
{
    s8 timer;

    timer = self->ext.timer - 1;
    self->ext.timer = timer;
    if (timer == 0) {
        func_8002217C(0x2A, 2, 0);
        self->unk5 = 5;
    }
}

void stage_cutscene_finish(struct UnkObj* self)
{
    if (abc_object.unkC == 0) {
        background_objects[g_Player.bg_offset].unk24 = 0x11B0;
        player_end_script_action();
        engine_obj.character_state.bytes[8] = 1;
        self->unk5 = 6;
    }
}

void stage_cutscene_idle(struct UnkObj* self)
{
}

// stage_cutscene_animate
INCLUDE_ASM("main/nonmatchings/misc/misc_44", func_800D0C68);

// stage_cutscene_spawn_part
INCLUDE_ASM("main/nonmatchings/misc/misc_44", func_800D0D68);

union AnimationStep stage_cutscene_anim_0[6] = {
    { .packed = 0x00010048 },
    { .packed = 0x01010002 },
    { .packed = 0x02010003 },
    { .packed = 0x00010006 },
    { .packed = 0x01010002 },
    { .packed = 0x02FB0003 },
};

union AnimationStep stage_cutscene_anim_1[2] = {
    { .packed = 0x03010005 },
    { .packed = 0x03000101 },
};

union AnimationStep stage_cutscene_anim_2[6] = {
    { .packed = 0x04010048 },
    { .packed = 0x05010002 },
    { .packed = 0x06010003 },
    { .packed = 0x04010006 },
    { .packed = 0x05010002 },
    { .packed = 0x06FB0003 },
};

union AnimationStep* stage_cutscene_animations[3] = {
    stage_cutscene_anim_0,
    stage_cutscene_anim_1,
    stage_cutscene_anim_2,
};

void (*stage_cutscene_state_funcs[3])(struct MiscObj*) = {
    func_800D0828,
    stage_cutscene_main,
    stage_cutscene_despawn,
};

void (*stage_cutscene_step_funcs[7])(struct UnkObj*) = {
    stage_cutscene_wait_player,
    stage_cutscene_wait_scroll,
    stage_cutscene_first_line,
    stage_cutscene_wait_first,
    stage_cutscene_second_line,
    stage_cutscene_finish,
    stage_cutscene_idle,
};

u8 stage_cutscene_data[24] = {
    0,
    2,
    4,
    5,
    6,
    7,
    9,
    10,
    12,
    1,
    13,
    14,
    15,
    16,
    17,
    18,
    19,
    20,
    3,
    8,
    11,
#ifdef VERSION_JP
    0,
#else
    21,
#endif
    0,
    0,
};
