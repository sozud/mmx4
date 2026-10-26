// LayerObj, layer_object_update_funcs[5]
// 800DA298..800DA7C0
#include "common.h"
#include "main/layers/layer_05_airship_bob.h"
#include "main/objects.h"

// airship_bob_state_funcs
extern void (*airship_bob_state_funcs[])(struct LayerObj*);

void airship_bob_despawn(struct LayerObj*);

extern s16 airship_bob_section_positions[2];

void airship_bob_section_0(struct LayerObj*);
void airship_bob_section_1(struct LayerObj*);
void airship_bob_section_2(struct LayerObj*);
void airship_bob_idle(struct LayerObj*);

// airship_bob_sway_funcs
extern void (*airship_bob_sway_funcs[])(struct LayerObj*);
void airship_bob_sway_up(struct LayerObj*);
void airship_bob_sway_down(struct LayerObj*);

void airship_bob_section_0_done(struct LayerObj* arg0);
void airship_bob_section_0_wait(struct LayerObj* arg0);
void airship_bob_section_1_done(struct LayerObj* arg0);
void airship_bob_section_1_wait(struct LayerObj* arg0);
void airship_bob_section_2_done(struct LayerObj* arg0);
void airship_bob_section_2_wait(struct LayerObj* arg0);

void airship_bob_update(struct LayerObj* arg0)
{
    airship_bob_state_funcs[arg0->state](arg0);
}

// airship_bob_init

void airship_bob_update_section(struct LayerObj*);
void airship_bob_sway(struct LayerObj*);
extern void (*airship_bob_section_funcs[])(struct LayerObj*);

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800DA2D4(struct LayerObj* arg0)
{
    s32 scroll = 0x8000;

    arg0->state++;
    background_objects[1].unk4D = 2;
    background_objects[2].unk4D = 2;
    background_objects[1].unk4E = 7;
    background_objects[2].unk4E = 8;
    memcpy(&arg0->bg_offset, &scroll, sizeof(scroll));
    arg0->unk18.val = -0x5800;
    arg0->private_state.value.val = 0;
    memset(arg0->unk20, 0, sizeof(arg0->unk20));
    arg0->unk24 = 3;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    func_800DA358(arg0);
}
#else
INCLUDE_ASM("main/nonmatchings/layers/layer_05_airship_bob", func_800DA2D4);
#endif

// airship_bob_main
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/layers/layer_05_airship_bob", func_800DA358);
#else
void func_800DA358(struct LayerObj* arg0)
{
    s32 half = (background_objects[0].unk14.val - background_objects[0].x_pos.val) / 2;

    background_objects[1].x_pos.val += *(s32*)&arg0->bg_offset - half;
    background_objects[2].x_pos.val -= *(s32*)&arg0->bg_offset / 2 + half / 2;
    arg0->unk25 = arg0->unk24;
    if (engine_obj.substage == 0) {
        airship_bob_update_section(arg0);
        airship_bob_section_funcs[arg0->unk5](arg0);
        if (engine_obj.substage == 0) {
            airship_bob_sway(arg0);
            if (g_Player.x_pos.i.hi >= 0x18D0)
                engine_obj.unkF = 1;
        }
    }
}
#endif

void airship_bob_despawn(struct LayerObj* arg0)
{
    despawn_object_permanently(arg0);
}

void airship_bob_section_0(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        airship_bob_section_0_wait(arg0);
    } else {
        airship_bob_section_0_done(arg0);
    }
}

void airship_bob_section_0_wait(struct LayerObj* arg0)
{
    arg0->unk6++;
}

void airship_bob_section_0_done(struct LayerObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void airship_bob_section_1(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        airship_bob_section_1_wait(arg0);
    } else {
        airship_bob_section_1_done(arg0);
    }
}

void airship_bob_section_1_wait(struct LayerObj* arg0)
{
    arg0->unk6++;
}

void airship_bob_section_1_done(struct LayerObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void airship_bob_section_2(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        airship_bob_section_2_wait(arg0);
    } else {
        airship_bob_section_2_done(arg0);
    }
}

void airship_bob_section_2_wait(struct LayerObj* arg0)
{
    arg0->unk6++;
}

void airship_bob_section_2_done(struct LayerObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void airship_bob_sway(struct LayerObj* arg0)
{
    airship_bob_sway_funcs[arg0->unk7](arg0);
}

void airship_bob_sway_up(struct LayerObj* arg0)
{
    if (arg0->unk18.val <= 0x5800) {
        if (arg0->unk18.val > 0) {
            if (arg0->private_state.value.val != 0) {
                arg0->private_state.value.val--;
                return;
            }
        }
        arg0->unk18.val += 0x400;
        background_objects[1].y_pos.val -= arg0->unk18.val / 2;
        background_objects[2].y_pos.val -= arg0->unk18.val;
        return;
    }
    arg0->private_state.value.val = 0x1E;
    arg0->unk7++;
}

void airship_bob_sway_down(struct LayerObj* arg0)
{
    if (arg0->unk18.val >= -0x5800) {
        if (arg0->unk18.val < 0) {
            if (arg0->private_state.value.val != 0) {
                arg0->private_state.value.val--;
                return;
            }
        }
        arg0->unk18.val -= 0x400;
        background_objects[1].y_pos.val -= arg0->unk18.val / 2;
        background_objects[2].y_pos.val -= arg0->unk18.val;
        return;
    }
    arg0->private_state.value.val = 0x1E;
    arg0->unk7--;
}

void airship_bob_idle(struct LayerObj* arg0)
{
}

void airship_bob_update_section(struct LayerObj* arg0)
{
    s8 offset = 0;
    s16 player_x = g_Player.x_pos.i.hi;

    while (1) {
        if (player_x - airship_bob_section_positions[offset] < 0) {
            break;
        }
        offset++;
        if (offset >= 2) {
            break;
        }
    }
    arg0->unk24 = offset;
    if (offset != arg0->unk25) {
        arg0->unk5 = offset;
        arg0->unk6 = 0;
    }
}

void (*airship_bob_state_funcs[])(struct LayerObj*) = {
    func_800DA2D4,
    func_800DA358,
    airship_bob_despawn,
};

s16 airship_bob_section_positions[2] = { 0x6A0, 0x810 };

void (*airship_bob_section_funcs[])(struct LayerObj*) = {
    airship_bob_section_0,
    airship_bob_section_1,
    airship_bob_section_2,
    airship_bob_idle,
};

void (*airship_bob_sway_funcs[])(struct LayerObj*) = {
    airship_bob_sway_up,
    airship_bob_sway_down,
};
