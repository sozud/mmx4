// QuadObj, quad_object_update_funcs[7]
// 800D5C54..800D67A0
#include "common.h"

u16 D_8010FAEC[8] = {
    0x0000,
    0x0000,
    0x0140,
    0x0000,
    0x0140,
    0x0004,
    0x0000,
    0x0004,
};
s16 D_8010FAFC[10] = {
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
s16 D_8010FB10[10][4][2] = {
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
s16 D_8010FBB0[10][4][2] = {
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
s16 D_8010FC50[3][4][2] = {
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
u16 D_8010FC80 = 0;

void func_800D64D8(struct QuadObj* arg0, s32 arg1, s32 arg2, const s16 target[2]);

// QuadObj #7
// megaman never appears in intro stage if nopped out
void func_800D5C54(struct QuadObj* arg0)
{
    D_8010FC84[arg0->state](arg0);
}

// D_8010FC84 state 0
void func_800D5C90(struct QuadObj* arg0)
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
    arg0->unk14.val = 0;
    arg0->unk18.val = 0;
    arg0->unk1C.val = 0;
    arg0->unk20.val = 0;
    arg0->unk24.val = 0;
    arg0->unk28.val = 0;
    arg0->unk2C.val = 0;
    arg0->unk30.val = 0;
}

// D_8010FC84 state 1
// "READY" never appears if noppped out
//  asm(".rept 20 ; nop ; .endr");
void func_800D5CF8(struct QuadObj* arg0)
{
    D_8010FC90[arg0->unk2](arg0);
    arg0->on_screen = 1;
    func_8002B458(arg0);
}

// D_8010FC90 state 0
void func_800D5D50(struct QuadObj* arg0)
{
    u16* verts;
    struct BaseObj* temp_s1;
    struct MiscObj* misc_obj;
    switch (arg0->unk5) {
    case 0:
        arg0->unk5 = 1;
        // set position of blue line that goes left to right before
        // ready text appears
        arg0->x_pos.i.hi = -320;
        arg0->y_pos.i.hi = 112;
        verts = D_8010FAEC;
        arg0->unk14.i.hi = *verts++;
        arg0->unk18.i.hi = *verts++;
        arg0->unk1C.i.hi = *verts++;
        arg0->unk20.i.hi = *verts++;
        arg0->unk24.i.hi = *verts++;
        arg0->unk28.i.hi = *verts++;
        arg0->unk2C.i.hi = *verts++;
        arg0->unk30.i.hi = *verts;
        arg0->ext.ready_line.x_vel.val = FIXED(32);
        arg0->ext.ready_line.y_vel.val = 0;
        arg0->ext.ready_line.x_accel.val = 0;
        arg0->ext.ready_line.y_accel.val = 0;
        func_800D6494(arg0);
        return;
    case 1:
        temp_s1 = arg0->link.owner;
        // spawn "READY" text and shadow when blue line reaches center of screen
        if ((arg0->x_pos.i.hi >= 0 && arg0->x_pos.i.hi < 3) && (temp_s1->unk15 == 0)) {
            misc_obj = find_free_misc_obj();
            if (misc_obj != NULL) {
                misc_obj->base.active = 1;
                misc_obj->base.id = 0x12;
                misc_obj->base.unk2 = 0;
                temp_s1->unk15 = 0;
                misc_obj->ext.ready_text.unk50 = (void*)arg0->link.owner;
            }
            misc_obj = find_free_misc_obj();
            if (misc_obj != NULL) {
                misc_obj->base.active = 1;
                misc_obj->base.id = 0x12;
                misc_obj->base.unk2 = 1;
                temp_s1->unk15 = 0;
                misc_obj->ext.ready_text.unk50 = (void*)arg0->link.owner;
            }
        }
        if (arg0->x_pos.i.hi >= 320) {
            arg0->unk5 = 2;
            return;
        }
        func_800D6494(arg0);
        return;
    case 2:
        temp_s1 = arg0->link.owner;
        temp_s1->bg_offset = 0;
        arg0->state = 2;
        arg0->unk5 = 0;
        return;
    }
}

// D_8010FC90 state 1
void func_800D5F1C(struct QuadObj* arg0)
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
        temp_v1_2 = &D_8010FAFC[arg0->unk7];
        arg0->unk14.i.hi = *temp_v1_2;
        arg0->unk2C.i.hi = *temp_v1_2;
        arg0->unk1C.i.hi = *temp_v1_2 + 63;
        arg0->unk24.i.hi = *temp_v1_2 + 63;
        arg0->y_pos.i.hi = 0;
        if (arg0->unk7 < 5) {
            arg0->unk18.i.hi = 0;
            arg0->unk20.i.hi = 0;
            arg0->unk28.i.hi = 0;
            arg0->unk30.i.hi = 0;
        } else {
            arg0->unk18.i.hi = 240;
            arg0->unk20.i.hi = 240;
            arg0->unk28.i.hi = 240;
            arg0->unk30.i.hi = 240;
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
            func_800D64D8(arg0, arg0->unk7 & 0xFF, var_s1 & 0xFF, &D_8010FB10[arg0->unk7][var_s1]);
            var_s1 += 1;
        } while (var_s1 < 4);
        if (--arg0->runtime.legacy.unk50 == 0) {
            verts = &D_8010FB10[arg0->unk7][0];
            arg0->unk14.i.hi = *verts++;
            arg0->unk18.i.hi = *verts++;
            arg0->unk1C.i.hi = *verts++;
            arg0->unk20.i.hi = *verts++;
            arg0->unk24.i.hi = *verts++;
            arg0->unk28.i.hi = *verts++;
            arg0->unk2C.i.hi = *verts++;
            arg0->unk30.i.hi = *verts++;
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
            func_800D64D8(arg0, arg0->unk7 & 0xFF, var_s1_2 & 0xFF, &D_8010FBB0[arg0->unk7][var_s1_2]);
            var_s1_2 += 1;
        } while (var_s1_2 < 4);
        if (--arg0->runtime.legacy.unk50 == 0) {
            verts = &D_8010FBB0[arg0->unk7][0];
            arg0->unk14.i.hi = *verts++;
            arg0->unk18.i.hi = *verts++;
            arg0->unk1C.i.hi = *verts++;
            arg0->unk20.i.hi = *verts++;
            arg0->unk24.i.hi = *verts++;
            arg0->unk28.i.hi = *verts++;
            arg0->unk2C.i.hi = *verts++;
            arg0->unk30.i.hi = *verts++;
            arg0->unk5 = 3;
            arg0->runtime.legacy.unk55 = 1;
            arg0->runtime.legacy.unk54 = 1;
            arg0->runtime.legacy.unk4C = 0;
            arg0->runtime.legacy.unk4D = 0;
            arg0->runtime.legacy.unk4E = 0;
            arg0->runtime.legacy.unk4F = 0;
            arg0->runtime.legacy.unk50 = 16;
            if (D_8010FC80 != 0) {
                D_8010FC80 -= 1;
                return;
            }
        }
        break;
    case 3:
        arg0->link.owner->bg_offset = 0;
        arg0->state = 2;
        arg0->unk5 = 0;
        break;
    }
}

extern u8 D_8010FC9C[];

// D_8010FC90 state 2
void func_800D6260(struct QuadObj* arg0)
{
    s32 var_s1;
    struct BaseObj* temp_v0_9;
    u16 temp_v0_8;
    s16* verts;

    switch (arg0->unk5) {
    case 0:
        arg0->unk5 = 1;
        verts = &D_8010FC50[D_8010FC9C[get_random() & 0xF]][0];
        arg0->unk14.i.hi = *verts++;
        arg0->unk18.i.hi = *verts++;
        arg0->unk1C.i.hi = *verts++;
        arg0->unk20.i.hi = *verts++;
        arg0->unk24.i.hi = *verts++;
        arg0->unk28.i.hi = *verts++;
        arg0->unk2C.i.hi = *verts++;
        arg0->unk30.i.hi = *verts++;
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
            if (arg0->x_pos.i.hi < 320) {
                func_800D6494(arg0);
                return;
            }
            goto block_18;
        }
        if (arg0->x_pos.i.hi < -176) {
        block_18:
            arg0->unk5 = 2;
            return;
        }
        func_800D6494(arg0);
        return;
    case 2:
        temp_v0_9 = arg0->link.owner;
        temp_v0_9->bg_offset--;
        arg0->state = 2;
        arg0->unk5 = 0;
        return;
    }
}

void func_800D6494(struct QuadObj* arg0)
{
    arg0->x_pos.val += arg0->ext.ready_line.x_vel.val;
    arg0->y_pos.val += arg0->ext.ready_line.y_vel.val;
    arg0->ext.ready_line.x_vel.val += arg0->ext.ready_line.x_accel.val;
    arg0->ext.ready_line.y_vel.val += arg0->ext.ready_line.y_accel.val;
}

void func_800D64D8(struct QuadObj* arg0, s32 arg1, s32 arg2, const s16 target[2])
{
    f32* vertex;
    s32 temp_s2;
    s32 temp_s3;
    s32 i;
    s32 vertex_index;
    s32 quadrant;

    vertex = &arg0->unk14;
    vertex_index = arg2;
    for (i = 0; i < (vertex_index & 0xFF); i++) {
        vertex += 2;
    }
    temp_s2 = vertex[0].val - (target[0] << 0x10);
    temp_s3 = vertex[1].val - (target[1] << 0x10);
    quadrant = func_8002B810(temp_s2, temp_s3);
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

// D_8010FC84 state 2
void func_800D666C(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800D668C(void)
{
}

void func_800D6694(struct QuadObj* arg0)
{
    arg0->unk34 = 3;
    arg0->ext.ready_line.x_vel.val = FIXED(4);
    arg0->unk36 = 0;
    arg0->bg_offset = 0;
    arg0->unk14.val = 0;
    arg0->unk18.val = 0;
    arg0->unk1C.val = 0;
    arg0->unk20.val = 0;
    arg0->unk24.val = 0;
    arg0->unk28.val = 0;
    arg0->unk2C.val = 0;
    arg0->unk30.val = 0;
    arg0->active |= 0x82;
    arg0->state++;
    quad_is_on_screen(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/quads/ready_line", func_800D6700);

void func_800D6780(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*D_8010FC84[])(struct QuadObj*) = {
    func_800D5C90,
    func_800D5CF8,
    func_800D666C,
};

void (*D_8010FC90[])(struct QuadObj*) = {
    func_800D5D50,
    func_800D5F1C,
    func_800D6260,
};

u8 D_8010FC9C[16] = { 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0 };
