#include "common.h"

// search lights in background of intro stage
void SearchLightUpdate(struct QuadObj* arg0)
{
    g_SearchLightUpdateFuncs[arg0->state](arg0);
}

// SearchLight state 0
void func_800D3AFC(struct QuadObj* arg0)
{
    u16 temp_a0;
    struct SearchLightInit* temp_v0;
    s16 temp = arg0->unk2;

    arg0->active |= 0x90;
    arg0->unk36 = D_8010F68C.values[arg0->unk2 >> 1];
    temp_a0 = D_8010F684.values[temp >> 1];
    temp_v0 = &D_8010F600[arg0->unk2];
    arg0->state = 1;
    arg0->unk34 = temp_a0;
    arg0->unk14.i.hi = temp_v0->vertices[0];
    arg0->unk18.i.hi = temp_v0->vertices[1];
    arg0->unk1C.i.hi = temp_v0->vertices[2];
    arg0->unk20.i.hi = temp_v0->vertices[3];
    arg0->unk24.i.hi = temp_v0->vertices[4];
    arg0->unk28.i.hi = temp_v0->vertices[5];
    arg0->unk2C.i.hi = temp_v0->vertices[6];
    arg0->unk30.i.hi = temp_v0->vertices[7];
    arg0->runtime.search_light.extent = temp_v0->extent;
    arg0->runtime.search_light.x_accumulator = 0;
    arg0->runtime.search_light.y_accumulator = 0;
    arg0->ext.search_light.velocity = D_8010F66C[arg0->unk2 >> 1];
    if (!(get_random(temp_a0) & 3)) {
        arg0->ext.search_light.velocity += 0x4000;
    }
    arg0->ext.search_light.vertical_velocity = 0;
    arg0->ext.search_light.acceleration = 0;
    arg0->ext.search_light.vertical_acceleration = 0;
    arg0->runtime.search_light.pause_timer = 0;
    arg0->link.direction = 0;
    arg0->runtime.search_light.base_speed = arg0->ext.search_light.velocity;
}

// SearchLight state 1
INCLUDE_ASM("asm/us/main/nonmatchings/search_light", func_800D3C58);

// SearchLight state 2
INCLUDE_ASM("asm/us/main/nonmatchings/search_light", func_800D3FBC);

// search light helper
void func_800D3FE0(struct Unk22* arg0)
{
    arg0->unk48 += arg0->unk38;
    arg0->unk4C += arg0->unk40;
    arg0->unk38 += arg0->unk3C;
    arg0->unk40 += arg0->unk44;
}

// search light helper
INCLUDE_ASM("asm/us/main/nonmatchings/search_light", func_800D4024);
