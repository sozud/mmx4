#ifndef MAIN_QUADS_QUAD_00_SEARCH_LIGHT_H
#define MAIN_QUADS_QUAD_00_SEARCH_LIGHT_H

struct SearchLightInit {
    s16 vertices[8];
    u16 extent;
};

void SearchLightUpdate(struct QuadObj* arg0);

void func_800D3C58(struct QuadObj*);

extern struct SearchLightInit search_light_shapes[6];

s32 search_light_is_visible(struct QuadObj*);

#endif
