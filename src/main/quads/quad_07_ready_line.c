// QuadObj, quad_object_update_funcs[7]
// 800D5C54..800D6694
#include "common.h"

u16 ready_line_sweep_vertices[8] = {
    0x0000,
    0x0000,
    0x0140,
    0x0000,
    0x0140,
    0x0004,
    0x0000,
    0x0004,
};

s16 ready_line_shutter_columns[10] = {
    0x0000,
    0x0040,
    0x0080,
    0x00C0,
    0x0100,
    0x0000,
    0x0040,
    0x0080,
    0x00C0,
    0x0100,
};

s16 ready_line_shutter_open_vertices[10][4][2] = {
    0x0040,
    0x0078,
    0x0060,
    0x0078,
    0x0040,
    0x0000,
    0x0000,
    0x0000,
    0x0068,
    0x0078,
    0x0088,
    0x0078,
    0x0080,
    0x0000,
    0x0040,
    0x0000,
    0x0090,
    0x0078,
    0x00B0,
    0x0078,
    0x00C0,
    0x0000,
    0x0080,
    0x0000,
    0x00B8,
    0x0078,
    0x00D8,
    0x0078,
    0x0100,
    0x0000,
    0x00C0,
    0x0000,
    0x00E0,
    0x0078,
    0x0100,
    0x0078,
    0x0140,
    0x0000,
    0x0100,
    0x0000,
    0x0040,
    0x0078,
    0x0060,
    0x0078,
    0x0040,
    0x00F0,
    0x0000,
    0x00F0,
    0x0068,
    0x0078,
    0x0088,
    0x0078,
    0x0080,
    0x00F0,
    0x0040,
    0x00F0,
    0x0090,
    0x0078,
    0x00B0,
    0x0078,
    0x00C0,
    0x00F0,
    0x0080,
    0x00F0,
    0x00B8,
    0x0078,
    0x00D8,
    0x0078,
    0x0100,
    0x00F0,
    0x00C0,
    0x00F0,
    0x00E0,
    0x0078,
    0x0100,
    0x0078,
    0x0140,
    0x00F0,
    0x0100,
    0x00F0,
};

s16 ready_line_shutter_close_vertices[10][4][2] = {
    0x0040,
    0x0078,
    0x0060,
    0x0078,
    0x0060,
    0x0078,
    0x0040,
    0x0078,
    0x0068,
    0x0078,
    0x0088,
    0x0078,
    0x0088,
    0x0078,
    0x0068,
    0x0078,
    0x0090,
    0x0078,
    0x00B0,
    0x0078,
    0x00B0,
    0x0078,
    0x0090,
    0x0078,
    0x00B8,
    0x0078,
    0x00D8,
    0x0078,
    0x00D8,
    0x0078,
    0x00B8,
    0x0078,
    0x00E0,
    0x0078,
    0x0100,
    0x0078,
    0x0100,
    0x0078,
    0x00E0,
    0x0078,
    0x0040,
    0x0078,
    0x0060,
    0x0078,
    0x0060,
    0x0078,
    0x0040,
    0x0078,
    0x0068,
    0x0078,
    0x0088,
    0x0078,
    0x0088,
    0x0078,
    0x0068,
    0x0078,
    0x0090,
    0x0078,
    0x00B0,
    0x0078,
    0x00B0,
    0x0078,
    0x0090,
    0x0078,
    0x00B8,
    0x0078,
    0x00D8,
    0x0078,
    0x00D8,
    0x0078,
    0x00B8,
    0x0078,
    0x00E0,
    0x0078,
    0x0100,
    0x0078,
    0x0100,
    0x0078,
    0x00E0,
    0x0078,
};

s16 ready_line_streak_vertices[3][4][2] = {
    0x0000,
    0x0000,
    0x00B0,
    0x0000,
    0x00B0,
    0x0003,
    0x0000,
    0x0003,
    0x0000,
    0x0000,
    0x0080,
    0x0000,
    0x0080,
    0x0002,
    0x0000,
    0x0002,
    0x0000,
    0x0000,
    0x0060,
    0x0000,
    0x0060,
    0x0001,
    0x0000,
    0x0001,
};

u16 ready_line_shutter_repeats = 0;

void ready_line_converge_vertex(struct QuadObj* arg0, arg_u8 arg1, s32 arg2, const s16 target[2]);

// QuadObj #7
// megaman never appears in intro stage if nopped out
void ready_line_update(struct QuadObj* arg0)
{
    ready_line_state_funcs[arg0->state](arg0);
}

// ready_line_state_funcs state 0
void ready_line_init(struct QuadObj* arg0)
{
    arg0->active |= 0x92;
    if (arg0->unk2 == 0) {
        arg0->unk36 = 0x10;
    } else {
        arg0->unk36 = 0x13;
    }
    arg0->unk34 = 5;
    arg0->state = 1;
    arg0->bg_offset = -1;
    arg0->x_pos.val = 0;
    arg0->y_pos.val = 0;
    arg0->vertices[0].x.val = 0;
    arg0->vertices[0].y.val = 0;
    arg0->vertices[1].x.val = 0;
    arg0->vertices[1].y.val = 0;
    arg0->vertices[2].x.val = 0;
    arg0->vertices[2].y.val = 0;
    arg0->vertices[3].x.val = 0;
    arg0->vertices[3].y.val = 0;
}

// ready_line_state_funcs state 1
// "READY" never appears if noppped out
//  asm(".rept 20 ; nop ; .endr");
void ready_line_main(struct QuadObj* arg0)
{
    ready_line_type_funcs[arg0->unk2](arg0);
    arg0->on_screen = 1;
    func_8002B458(arg0);
}

// ready_line_type_funcs state 0
void ready_line_sweep(struct QuadObj* arg0)
{
    u16* verts;
    struct EffectObj* temp_s1;
    struct MiscObj* misc_obj;
    switch (arg0->unk5) {
    case 0:
        arg0->unk5 = 1;
        // set position of blue line that goes left to right before
        // ready text appears
        arg0->x_pos.i.hi = -320;
        arg0->y_pos.i.hi = 112;
        verts = ready_line_sweep_vertices;
        arg0->vertices[0].x.i.hi = *verts++;
        arg0->vertices[0].y.i.hi = *verts++;
        arg0->vertices[1].x.i.hi = *verts++;
        arg0->vertices[1].y.i.hi = *verts++;
        arg0->vertices[2].x.i.hi = *verts++;
        arg0->vertices[2].y.i.hi = *verts++;
        arg0->vertices[3].x.i.hi = *verts++;
        arg0->vertices[3].y.i.hi = *verts;
        arg0->ext.ready_line.x_vel.val = FIXED(32);
        arg0->ext.ready_line.y_vel.val = 0;
        arg0->ext.ready_line.x_accel.val = 0;
        arg0->ext.ready_line.y_accel.val = 0;
        ready_line_move(arg0);
        return;
    case 1:
        temp_s1 = arg0->link.owner;
        // spawn "READY" text and shadow when blue line reaches center of screen
        if ((arg0->x_pos.i.hi >= 0 && arg0->x_pos.i.hi <= 2) && (temp_s1->ext.unk_effect.unk15 == 0)) {
            misc_obj = find_free_misc_obj();
            if (misc_obj != NULL) {
                misc_obj->active = 1;
                misc_obj->id = 0x12;
                misc_obj->unk2 = 0;
                temp_s1->ext.unk_effect.unk15 = 0;
                misc_obj->ext.ready_text.owner = arg0->link.owner;
            }
            misc_obj = find_free_misc_obj();
            if (misc_obj != NULL) {
                misc_obj->active = 1;
                misc_obj->id = 0x12;
                misc_obj->unk2 = 1;
                temp_s1->ext.unk_effect.unk15 = 0;
                misc_obj->ext.ready_text.owner = arg0->link.owner;
            }
        }
        if (arg0->x_pos.i.hi >= 320) {
            arg0->unk5 = 2;
            return;
        }
        ready_line_move(arg0);
        return;
    case 2:
        temp_s1 = arg0->link.owner;
        temp_s1->ext.unk_effect.unk14 = 0;
        arg0->state = 2;
        arg0->unk5 = 0;
        return;
    }
}

// ready_line_type_funcs state 1
void ready_line_shutter(struct QuadObj* arg0)
{
    u16* verts;
    u16* temp_v1_2;
    u32 var_s1;
    u32 var_s1_2;
    u8 pad[0x10];

    switch (arg0->unk5) {
    case 0:
        arg0->unk5 = 1;
        arg0->x_pos.i.hi = 0;
        temp_v1_2 = &ready_line_shutter_columns[arg0->unk7];
        arg0->vertices[0].x.i.hi = *temp_v1_2;
        arg0->vertices[3].x.i.hi = *temp_v1_2;
        arg0->vertices[1].x.i.hi = *temp_v1_2 + 63;
        arg0->vertices[2].x.i.hi = *temp_v1_2 + 63;
        arg0->y_pos.i.hi = 0;
        if (arg0->unk7 < 5) {
            arg0->vertices[0].y.i.hi = 0;
            arg0->vertices[1].y.i.hi = 0;
            arg0->vertices[2].y.i.hi = 0;
            arg0->vertices[3].y.i.hi = 0;
        } else {
            arg0->vertices[0].y.i.hi = 240;
            arg0->vertices[1].y.i.hi = 240;
            arg0->vertices[2].y.i.hi = 240;
            arg0->vertices[3].y.i.hi = 240;
        }
        arg0->runtime.legacy.unk55 = 1;
        arg0->runtime.legacy.unk54 = 1;
        arg0->runtime.legacy.unk4C = 0;
        arg0->runtime.legacy.unk4D = 0;
        arg0->runtime.legacy.unk4E = 0;
        arg0->runtime.legacy.unk4F = 0;
        arg0->runtime.legacy.unk50 = 8;
        return;
    case 1:
        var_s1 = 0;
        do {
            ready_line_converge_vertex(arg0, arg0->unk7 & 0xFF, var_s1 & 0xFF, &ready_line_shutter_open_vertices[arg0->unk7][var_s1]);
            var_s1 += 1;
        } while (var_s1 < 4);
        if (--arg0->runtime.legacy.unk50 == 0) {
            verts = &ready_line_shutter_open_vertices[arg0->unk7][0];
            arg0->vertices[0].x.i.hi = *verts++;
            arg0->vertices[0].y.i.hi = *verts++;
            arg0->vertices[1].x.i.hi = *verts++;
            arg0->vertices[1].y.i.hi = *verts++;
            arg0->vertices[2].x.i.hi = *verts++;
            arg0->vertices[2].y.i.hi = *verts++;
            arg0->vertices[3].x.i.hi = *verts++;
            arg0->vertices[3].y.i.hi = *verts++;
            arg0->unk5 = 2;
            arg0->runtime.legacy.unk55 = 1;
            arg0->runtime.legacy.unk54 = 1;
            arg0->runtime.legacy.unk4C = 0;
            arg0->runtime.legacy.unk4D = 0;
            arg0->runtime.legacy.unk4E = 0;
            arg0->runtime.legacy.unk4F = 0;
            arg0->runtime.legacy.unk50 = 8;
            return;
        }
        return;
    case 2:
        var_s1_2 = 0;
        do {
            ready_line_converge_vertex(arg0, arg0->unk7 & 0xFF, var_s1_2 & 0xFF, &ready_line_shutter_close_vertices[arg0->unk7][var_s1_2]);
            var_s1_2 += 1;
        } while (var_s1_2 < 4);
        if (--arg0->runtime.legacy.unk50 == 0) {
            verts = &ready_line_shutter_close_vertices[arg0->unk7][0];
            arg0->vertices[0].x.i.hi = *verts++;
            arg0->vertices[0].y.i.hi = *verts++;
            arg0->vertices[1].x.i.hi = *verts++;
            arg0->vertices[1].y.i.hi = *verts++;
            arg0->vertices[2].x.i.hi = *verts++;
            arg0->vertices[2].y.i.hi = *verts++;
            arg0->vertices[3].x.i.hi = *verts++;
            arg0->vertices[3].y.i.hi = *verts++;
            arg0->unk5 = 3;
            arg0->runtime.legacy.unk55 = 1;
            arg0->runtime.legacy.unk54 = 1;
            arg0->runtime.legacy.unk4C = 0;
            arg0->runtime.legacy.unk4D = 0;
            arg0->runtime.legacy.unk4E = 0;
            arg0->runtime.legacy.unk4F = 0;
            arg0->runtime.legacy.unk50 = 16;
            if (ready_line_shutter_repeats != 0) {
                ready_line_shutter_repeats -= 1;
                return;
            }
        }
        break;
    case 3:
        arg0->link.owner->ext.unk_effect.unk14 = 0;
        arg0->state = 2;
        arg0->unk5 = 0;
        break;
    }
}

extern u8 ready_line_streak_shapes[];

// ready_line_type_funcs state 2
void ready_line_streak(struct QuadObj* arg0)
{
    s32 var_s1;
    struct EffectObj* temp_v0_9;
    u16 temp_v0_8;
    s16* verts;

    switch (arg0->unk5) {
    case 0:
        arg0->unk5 = 1;
        verts = &ready_line_streak_vertices[ready_line_streak_shapes[get_random() & 0xF]][0];
        arg0->vertices[0].x.i.hi = *verts++;
        arg0->vertices[0].y.i.hi = *verts++;
        arg0->vertices[1].x.i.hi = *verts++;
        arg0->vertices[1].y.i.hi = *verts++;
        arg0->vertices[2].x.i.hi = *verts++;
        arg0->vertices[2].y.i.hi = *verts++;
        arg0->vertices[3].x.i.hi = *verts++;
        arg0->vertices[3].y.i.hi = *verts++;
        var_s1 = 1;
        if (get_random() & 1) {
            var_s1 = 2;
        }
        if (get_random() & 1) {
            arg0->x_pos.i.hi = -176;
            arg0->ext.ready_line.x_vel.val = var_s1 * FIXED(24);
            arg0->ext.ready_line.y_vel.val = 0;
            arg0->ext.ready_line.x_accel.val = 0;
            arg0->ext.ready_line.y_accel.val = 0;
            arg0->runtime.legacy.unk48 = 0;
        } else {
            arg0->x_pos.i.hi = 496;
            arg0->ext.ready_line.x_vel.val = -(var_s1 * FIXED(24));
            arg0->ext.ready_line.y_vel.val = 0;
            arg0->ext.ready_line.x_accel.val = 0;
            arg0->ext.ready_line.y_accel.val = 0;
            arg0->runtime.legacy.unk48 = 1;
        }
        arg0->y_pos.i.hi = ((get_random() & 7) * 4) + 104;
        arg0->runtime.legacy.unk52 = arg0->unk7 << 3;
        return;
    case 1:
        temp_v0_8 = arg0->runtime.legacy.unk52;
        if (temp_v0_8 != 0) {
            arg0->runtime.legacy.unk52--;
            return;
        }
        if (arg0->runtime.legacy.unk48 == 0) {
            if (arg0->x_pos.i.hi >= 320) {
                arg0->unk5 = 2;
                return;
            }
            ready_line_move(arg0);
            return;
        }
        if (arg0->x_pos.i.hi < -176) {
            arg0->unk5 = 2;
            return;
        }
        ready_line_move(arg0);
        return;
    case 2:
        temp_v0_9 = arg0->link.owner;
        temp_v0_9->ext.unk_effect.unk14--;
        arg0->state = 2;
        arg0->unk5 = 0;
        return;
    }
}

void ready_line_move(struct QuadObj* arg0)
{
    arg0->x_pos.val += arg0->ext.ready_line.x_vel.val;
    arg0->y_pos.val += arg0->ext.ready_line.y_vel.val;
    arg0->ext.ready_line.x_vel.val += arg0->ext.ready_line.x_accel.val;
    arg0->ext.ready_line.y_vel.val += arg0->ext.ready_line.y_accel.val;
}

void ready_line_converge_vertex(struct QuadObj* arg0, arg_u8 arg1, s32 arg2, const s16 target[2])
{
    f32* vertex;
    s32 temp_s2;
    s32 temp_s3;
    s32 i;
    u8 vertex_index;
    s32 quadrant;

    vertex = &arg0->vertices[0].x;
    vertex_index = arg2;
    for (i = 0; i < (vertex_index & 0xFF); i++) {
        vertex += 2;
    }
    temp_s2 = vertex[0].val - (target[0] << 0x10);
    temp_s3 = vertex[1].val - (target[1] << 0x10);
    quadrant = angle_from_delta(temp_s2, temp_s3);
    if (((((arg0->runtime.ready_line.directions[vertex_index & 0xFF] ^ quadrant) & 0x10) != 0) || (arg0->runtime.ready_line.crossed[vertex_index & 0xFF] != 0)) && (arg0->runtime.ready_line.converging == 0)) {
        arg0->x_pos.i.lo = 0;
        arg0->y_pos.i.lo = 0;
        arg0->runtime.ready_line.crossed[vertex_index & 0xFF] = 1;
    } else {
        vertex[0].val -= temp_s2 / (s32)arg0->runtime.ready_line.interpolation_frames;
        vertex[1].val -= temp_s3 / (s32)arg0->runtime.ready_line.interpolation_frames;
        arg0->runtime.ready_line.crossed[vertex_index & 0xFF] = 0;
        if ((vertex_index & 0xFF) == 3) {
            arg0->runtime.ready_line.converging = 0;
        }
    }
    arg0->runtime.ready_line.directions[vertex_index & 0xFF] = quadrant;
}

// ready_line_state_funcs state 2
void ready_line_despawn(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void ready_line_nop(void)
{
}

void (*ready_line_state_funcs[])(struct QuadObj*) = {
    ready_line_init,
    ready_line_main,
    ready_line_despawn,
};

void (*ready_line_type_funcs[])(struct QuadObj*) = {
    ready_line_sweep,
    ready_line_shutter,
    ready_line_streak,
};

u8 ready_line_streak_shapes[16] = { 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0 };
