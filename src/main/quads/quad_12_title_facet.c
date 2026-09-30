// QuadObj, quad_object_update_funcs[12]
// 800D7734..800D7A4C
#include "common.h"

extern u8 title_facet_vertex_indices[][4];
extern union TitleScratch D_80169498;

void title_facet_init(struct QuadObj* arg0)
{
    u16* points;
    u16* vertex;
    u16 x;
    u8 state;

    arg0->active |= 0x80;
    arg0->bg_offset = -1;
    arg0->x_pos.i.hi = 0;
    arg0->y_pos.i.hi = 0;
    points = &D_80169498.title.coordinates[0].u.hi;
    vertex = &points[title_facet_vertex_indices[arg0->unk2][0] * 4];
    arg0->unk14.i.hi = vertex[0];
    arg0->unk18.i.hi = vertex[2];
    vertex = &points[title_facet_vertex_indices[arg0->unk2][1] * 4];
    arg0->unk1C.i.hi = vertex[0];
    arg0->unk20.i.hi = vertex[2];
    vertex = &points[title_facet_vertex_indices[arg0->unk2][2] * 4];
    arg0->unk24.i.hi = vertex[0];
    arg0->unk28.i.hi = vertex[2];
    vertex = &points[title_facet_vertex_indices[arg0->unk2][3] * 4];
    state = arg0->state;
    x = vertex[0];
    state++;
    arg0->unk2C.i.hi = x;
    arg0->unk30.i.hi = vertex[2];
    arg0->unk36 = 0x11;
    arg0->ext.unk_ext.unk38 = 0x3C;
    arg0->state = state;
    arg0->unk34 = 0x7FFF;
    arg0->on_screen = 1;
}

void title_facet_follow(struct QuadObj* arg0)
{
    u16* points;
    u16* vertex;

    points = &D_80169498.title.coordinates[0].u.hi;
    vertex = &points[title_facet_vertex_indices[arg0->unk2][0] * 4];
    arg0->unk14.i.hi = vertex[0];
    arg0->unk18.i.hi = vertex[2];
    vertex = &points[title_facet_vertex_indices[arg0->unk2][1] * 4];
    arg0->unk1C.i.hi = vertex[0];
    arg0->unk20.i.hi = vertex[2];
    vertex = &points[title_facet_vertex_indices[arg0->unk2][2] * 4];
    arg0->unk24.i.hi = vertex[0];
    arg0->unk28.i.hi = vertex[2];
    vertex = &points[title_facet_vertex_indices[arg0->unk2][3] * 4];
    arg0->unk2C.i.hi = vertex[0];
    arg0->unk30.i.hi = vertex[2];
    if (game_info.unk6 == 0) {
        arg0->state++;
        arg0->ext.unk_ext.unk38 = 5;
    }
    arg0->on_screen = 1;
}

void title_facet_finish(struct QuadObj* arg0)
{
    struct MiscObj* misc;
    if (--(arg0->ext.unk_ext.unk38) == 0) {
        if (arg0->unk2 == 0) {
            misc = find_free_misc_obj();
            if (misc != NULL) {
                misc->active = 1;
                misc->id = 0x13;
                misc->unk2 = 0xB;
            }
        }
        arg0->state++;
    }
    quad_is_on_screen(arg0);
}

void title_facet_despawn(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void title_facet_update(struct QuadObj* arg0)
{
    title_facet_state_funcs[arg0->state](arg0);
}

u8 title_facet_vertex_indices[9][4] = {
    { 0, 1, 5, 4 },
    { 2, 3, 6, 6 },
    { 4, 5, 15, 14 },
    { 6, 3, 16, 15 },
    { 7, 8, 9, 9 },
    { 10, 11, 13, 12 },
    { 17, 16, 11, 10 },
    { 14, 15, 16, 17 },
    { 14, 17, 8, 7 },
};

void (*title_facet_state_funcs[])(struct QuadObj*) = {
    title_facet_init,
    title_facet_follow,
    title_facet_finish,
    title_facet_despawn,
};
