// VisualObj, visual_object_update_funcs[6]
// 800AFF78..800B0890
#include "common.h"

s8 eregion_part_offsets_left[58][2] = {
    { -6, -78 },
    { -8, -76 },
    { -9, -75 },
    { -10, -74 },
    { -10, -74 },
    { -10, -74 },
    { -9, -75 },
    { -8, -76 },
    { 0, -10 },
    { 0, -10 },
    { 0, -10 },
    { 0, -10 },
    { -9, -75 },
    { -23, -71 },
    { -18, -95 },
    { -17, -95 },
    { -17, -94 },
    { -17, -93 },
    { -14, -90 },
    { -16, -79 },
    { -23, -64 },
    { -17, -73 },
    { -27, -66 },
    { -27, -66 },
    { -51, -50 },
    { 0, -10 },
    { 0, -10 },
    { -50, -50 },
    { -20, -56 },
    { -18, -57 },
    { -20, -64 },
    { -32, -45 },
    { -32, -45 },
    { 0, -10 },
    { 0, -10 },
    { 0, -10 },
    { 0, -10 },
    { 0, -10 },
    { -30, -46 },
    { 0, -10 },
    { 0, -10 },
    { 0, -10 },
    { 0, -10 },
    { 0, -10 },
    { 0, -10 },
    { 0, -10 },
    { 0, -10 },
    { 0, -10 },
    { 0, -10 },
    { 0, -10 },
    { 0, -10 },
    { -7, -79 },
    { -4, -81 },
    { -1, -82 },
    { 0, -10 },
    { -20, -56 },
    { 0, -10 },
    { 0, 0 },
};

s8 eregion_part_offsets_right[58][2] = {
    { 76, -67 },
    { 74, -65 },
    { 73, -64 },
    { 72, -63 },
    { 72, -63 },
    { 72, -63 },
    { 73, -64 },
    { 74, -65 },
    { 10, -10 },
    { 10, -10 },
    { 10, -10 },
    { 10, -10 },
    { 73, -64 },
    { 59, -60 },
    { 64, -84 },
    { 65, -84 },
    { 75, -83 },
    { 75, -82 },
    { 68, -79 },
    { 66, -68 },
    { 59, -53 },
    { 63, -62 },
    { 41, -50 },
    { 41, -50 },
    { 54, -45 },
    { 10, -10 },
    { 10, -10 },
    { 55, -45 },
    { 85, -51 },
    { 87, -52 },
    { 62, -53 },
    { 50, -34 },
    { 50, -34 },
    { 10, -10 },
    { 10, -10 },
    { 10, -10 },
    { 10, -10 },
    { 10, -10 },
    { 52, -35 },
    { 10, -10 },
    { 10, -10 },
    { 10, -10 },
    { 10, -10 },
    { 10, -10 },
    { 10, -10 },
    { 10, -10 },
    { 10, -10 },
    { 10, -10 },
    { 10, -10 },
    { 10, -10 },
    { 10, -10 },
    { 75, -68 },
    { 78, -70 },
    { 81, -71 },
    { 10, -10 },
    { 85, -51 },
    { 10, -10 },
    { 0, 0 },
};

s8 eregion_part_offsets_center[58][2] = {
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -96, 0 },
    { -110, -1 },
    { -107, 15 },
    { -107, 16 },
    { -107, 15 },
    { -107, 14 },
    { -107, 16 },
    { -104, 8 },
    { -111, -7 },
    { -104, 0 },
    { -102, 0 },
    { -101, 0 },
    { 122, 0 },
    { -100, 0 },
    { -100, 0 },
    { 122, 0 },
    { -106, 0 },
    { -104, 1 },
    { -96, 0 },
    { -95, 0 },
    { -95, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -95, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { -97, 0 },
    { -98, 0 },
    { -99, 0 },
    { -100, 0 },
    { -100, 0 },
    { -100, 0 },
    { 0, 0 },
};

void (*eregion_part_funcs[])(struct VisualObj*) = {
    func_800B0320,
    eregion_part_slash,
    eregion_part_mouth,
    eregion_part_legs,
    eregion_part_mirror,
};

// eregion_part_update
INCLUDE_ASM("main/nonmatchings/visuals/visual_06_eregion_part", func_800AFF78);

// eregion_part_init
INCLUDE_ASM("main/nonmatchings/visuals/visual_06_eregion_part", func_800B0320);

void eregion_part_slash(struct VisualObj* arg0)
{
    if (arg0->animation_step.fields.event == 2) {
        MAIN_OBJECT(arg0->unk50)->ext.main_8.queued_sound = 0x20;
    }
    if (arg0->animation_step.fields.event == 1 || (arg0->unk2 == 1 && (arg0->unk50->state != 1 || arg0->unk50->unk5 != 5))) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (arg0->unk2 != 1 || g_Player.update_delay == 0) {
        animate_object(ANIMATED_OBJECT(arg0));
    }
    update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);
}

void eregion_part_mouth(struct VisualObj* arg0)
{
    struct PlayerObj* player;
    s32 animation;

    player = arg0->unk50;
    if (player->active == 0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (player->unk7 == 0) {
        animation = player->unk17 + 1;
        if (arg0->unk17 != animation) {
            set_animation(arg0, animation);
        } else {
            animate_object(ANIMATED_OBJECT(arg0));
        }
    }
    if (arg0->unk50->unk7 >= 0) {
        update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);
    }
}

void eregion_part_legs(struct VisualObj* arg0)
{
    s32 animation;

    if (0 == arg0->unk50->active) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (arg0->unk50->unk7 != 0) {
        if (arg0->unk50->unk7 < 0) {
            return;
        }
    } else {
        if (arg0->unk2 == 3) {
            if (arg0->unk17 != arg0->unk50->unk17) {
                set_animation(ANIMATED_OBJECT(arg0), arg0->unk50->unk17);
            } else {
                animate_object(ANIMATED_OBJECT(arg0));
            }
        } else {
            if ((u8)arg0->unk50->animation_step.fields.frame_index == 0x18 || (u8)arg0->unk50->animation_step.fields.frame_index == 0x1B || (u8)arg0->unk50->animation_step.fields.frame_index == 0x1C || (u8)arg0->unk50->animation_step.fields.frame_index == 0x1D) {
                arg0->unk16 = 7;
            } else {
                arg0->unk16 = 5;
            }
            animation = arg0->unk50->unk17 + 1;
            if (arg0->unk17 != animation) {
                set_animation(ANIMATED_OBJECT(arg0), animation);
            } else {
                animate_object(ANIMATED_OBJECT(arg0));
            }
        }
        if (arg0->animation_step.fields.event != 0) {
            if (arg0->unk54 != 0) {
                MAIN_OBJECT(arg0->unk50)->ext.main_8.queued_sound = 0x1A;
            } else {
                MAIN_OBJECT(arg0->unk50)->ext.main_8.queued_sound = 0x1B;
            }
            arg0->animation_step.fields.event = 0;
            arg0->unk54 ^= 1;
        }
    }
    update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);
}

void eregion_part_mirror(struct VisualObj* arg0)
{
    struct PlayerObj* player;

    player = arg0->unk50;
    if (0 == player->active) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (arg0->animation_step.fields.frame_index != player->animation_step.fields.frame_index) {
        set_animation_frame(ANIMATED_OBJECT(arg0), 0x19, player->animation_step.fields.frame_index);
    }
    if (arg0->unk50->unk7 >= 0) {
        update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);
    }
}
