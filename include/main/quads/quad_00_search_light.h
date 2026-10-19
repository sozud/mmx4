#ifndef MAIN_QUADS_QUAD_00_SEARCH_LIGHT_H
#define MAIN_QUADS_QUAD_00_SEARCH_LIGHT_H

struct SearchLightColorLookup {
    u16 values[3];
    u16 alignment;
};

struct SearchLightIntensityLookup {
    u8 values[3];
    u8 alignment;
};

struct Unk22 {
    u8 pad0[8];
    s32 unk8;
    s32 unkC;
    u8 pad[0x28];
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
};

struct SearchLightInit {
    s16 vertices[8];
    u16 extent;
};

void SearchLightUpdate(struct QuadObj* arg0);

void func_800D3C58(struct QuadObj*);

extern struct SearchLightInit search_light_shapes[6];

s32 search_light_is_visible(struct QuadObj*);

#endif
