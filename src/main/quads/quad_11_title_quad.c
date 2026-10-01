// QuadObj, quad_object_update_funcs[11]
// 800D6F94..800D7734
#include "common.h"

// white quad that turns into "MEGAMAN" on title screen

// TitleUpdate2 state 0
extern s16 title_quad_shapes[][8];
#ifdef VERSION_JP
extern s16 title_quad_delays[];
extern u16 title_quad_palette[][15];
#else
extern u16 title_quad_palette[];
extern s16 title_quad_morph_targets[][2];
#endif

void title_quad_init(struct QuadObj* arg0)
{
    struct QuadObj* entity = arg0;
    u16* ptr;
#ifndef VERSION_JP
#endif

    entity->bg_offset = -1;
    entity->ext.title_quad.unk42 = 1; // 0x42
    entity->x_pos.i.hi = 0;
    entity->y_pos.i.hi = 0;
    entity->active |= 0x80;

    ptr = title_quad_shapes[entity->unk2];
    entity->vertices[0].x.i.hi = *ptr++;
    entity->vertices[0].y.i.hi = *ptr++;
    entity->vertices[1].x.i.hi = *ptr++;
    entity->vertices[1].y.i.hi = *ptr++;
    entity->vertices[2].x.i.hi = *ptr++;
    entity->vertices[2].y.i.hi = *ptr++;
    entity->vertices[3].x.i.hi = *ptr++;
    entity->vertices[3].y.i.hi = *ptr;

#ifdef VERSION_JP
    switch (entity->unk2) {
    case 0:
    case 1:
    case 9: {
        u16 color = title_quad_palette[1][0];

        entity->unk36 = 0x11;
        entity->ext.title_quad.unk38 = 0x3C;
        entity->state = 1;
        entity->unk34 = color;
        quad_is_on_screen(entity);
        break;
    }

    case 2:
    case 3:
    case 4: {
        u16 color = title_quad_palette[0][0];

        entity->unk36 = 0x10;
        entity->state = 3;
        entity->unk34 = color;
        entity->vertices[1].x = entity->vertices[0].x;
        entity->vertices[1].y = entity->vertices[0].y;
        entity->vertices[2].x = entity->vertices[3].x;
        entity->vertices[2].y = entity->vertices[3].y;
        entity->ext.title_quad.unk38 = title_quad_delays[entity->unk2 - 2];
        entity->ext.title_quad.unk43 = 0;
        break;
    }

    case 5: {
        u16 color = title_quad_palette[1][0];

        entity->unk36 = 0x12;
        entity->state = 4;
        entity->unk2 = 4;
        entity->ext.title_quad.unk43 = 0;
        entity->unk34 = color;
        break;
    }
    }
#else
    entity->unk34 = title_quad_palette[0];
    entity->unk36 = 0x10;
    entity->state = 3;
    entity->ext.title_quad.unk38 = 0x14;
    entity->ext.title_quad.unk43 = 0; // 0x43
#endif
}

// TitleUpdate2 state 1
void title_quad_split(struct QuadObj* self)
{
    s32 velocity;

    if (game_info.unkA != 1) {
        quad_is_on_screen(self);
        return;
    }

    if (self->unk2 == 0) {
        self->vertices[2].y.val += FIXED(-8);
        self->vertices[3].y.val += FIXED(-8);
        if (self->vertices[2].y.i.hi < self->vertices[1].y.i.hi) {
            self->state = 2;
            return;
        }
    } else {
        velocity = FIXED(8);
        self->vertices[0].y.val += velocity;
        self->vertices[1].y.val += velocity;
        if (self->vertices[1].y.i.hi > self->vertices[2].y.i.hi) {
            self->state = 2;
            return;
        }
    }
    quad_is_on_screen(self);
}

// TitleUpdate2 state 3
void title_quad_delay(struct QuadObj* arg0)
{
    // seems to be a timer before the white Quad appears
    if (arg0->ext.title_quad.unk38 != 0) {
        arg0->ext.title_quad.unk38--;
        return;
    }
    arg0->ext.title_quad.unk38 = 3;
    quad_is_on_screen(arg0);
#ifdef VERSION_JP
    arg0->state = 6;
#else
    arg0->state = 4;
#endif
}

// TitleUpdate2 state 4
void TitleSetWhiteQuadSpeed(struct QuadObj* arg0)
{
#ifdef VERSION_JP
    s16* ptr;

    if (game_info.unkA == 2) {
        if (arg0->unk2 == 4) {
            arg0->state = 2;
        } else {
            ptr = title_quad_shapes[arg0->unk2 + 3];
            arg0->vertices[0].x.i.hi = *ptr++;
            arg0->vertices[0].y.i.hi = *ptr++;
            arg0->vertices[1].x.i.hi = *ptr++;
            arg0->vertices[1].y.i.hi = *ptr++;
            arg0->vertices[2].x.i.hi = *ptr++;
            arg0->vertices[2].y.i.hi = *ptr++;
            arg0->vertices[3].x.i.hi = *ptr++;
            arg0->vertices[3].y.i.hi = *ptr;
            if (arg0->unk2 == 2) {
                arg0->unk34 = title_quad_palette[0][0];
                arg0->unk36 = 0x11;
            } else {
                arg0->unk34 = title_quad_palette[1][0];
                arg0->unk36 = 0x10;
            }
            arg0->ext.title_quad.unk38 = 0x2C;
            arg0->state = 5;
        }
    }
    quad_is_on_screen(arg0);
#else
    if (game_info.unkA == 2) {
        arg0->ext.title_quad.unk38 = 0x2C; // sets animation speed of white quad that transforms into "MEGAMAN"
        arg0->state = 5;
    }
    quad_is_on_screen(arg0);
#endif
}

// TitleUpdate2 state 5
#ifdef VERSION_JP
INCLUDE_ASM("main/nonmatchings/quads/quad_11_title_quad", title_quad_morph);
#else
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/quads/quad_11_title_quad", title_quad_morph);
#else
void title_quad_morph(struct QuadObj* arg0)
{
    f32* xy_ptr;
    s32 x_diff;
    s32 y_diff;
    s32 pos;
    s16* ptr;
    u16* palette;
    u16* var_v0;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 temp_v1;

    xy_ptr = &arg0->vertices[0].x;
    pos = 0;
    do {
        ptr = &title_quad_morph_targets[pos][0];
        x_diff = xy_ptr[0].val - FIXED(ptr[0]);
        y_diff = xy_ptr[1].val - FIXED(ptr[1]);
        temp_v0 = angle_from_delta(x_diff, y_diff);
        if ((((arg0->ext.title_quad.unk3E[pos] ^ temp_v0) & 0x10) || (arg0->ext.title_quad.unk3A[pos] != 0)) && (arg0->ext.title_quad.unk42 == 0)) {
            xy_ptr[0].val = FIXED(ptr[0]);
            xy_ptr[1].val = FIXED(ptr[1]);
            arg0->ext.title_quad.unk3A[pos] = 1;
        } else {
            xy_ptr[0].val -= x_diff / arg0->ext.title_quad.unk38;
            xy_ptr[1].val -= y_diff / arg0->ext.title_quad.unk38;
            arg0->ext.title_quad.unk3A[pos] = 0;
            if (pos == 3) {
                arg0->ext.title_quad.unk42 = 0;
            }
        }
        xy_ptr += 2;
        arg0->ext.title_quad.unk3E[pos] = temp_v0;
        pos++;
    } while (pos < 4);

    if ((arg0->ext.title_quad.unk38 % 3) == 0) {
        palette = title_quad_palette;
        temp_v1 = arg0->ext.title_quad.unk43;
        temp_v0_2 = temp_v1 + 1;
        arg0->ext.title_quad.unk43 = temp_v0_2;
        if (temp_v0_2 < 0xE) {
            temp_v0_2 = temp_v1 + 2;
            arg0->ext.title_quad.unk43 = temp_v0_2;
            var_v0 = &palette[temp_v0_2];
        } else {
            var_v0 = &palette[14];
        }
        arg0->unk34 = *var_v0;
    }

    arg0->ext.title_quad.unk38--;
    if (arg0->ext.title_quad.unk38 == 0) {
        arg0->state = 2;
        ptr = title_quad_morph_targets[0];
        arg0->vertices[0].x.i.hi = *(u16*)ptr++;
        arg0->vertices[0].y.i.hi = *(u16*)ptr++;
        arg0->vertices[1].x.i.hi = *(u16*)ptr++;
        arg0->vertices[1].y.i.hi = *(u16*)ptr++;
        arg0->vertices[2].x.i.hi = *(u16*)ptr++;
        arg0->vertices[2].y.i.hi = *(u16*)ptr++;
        arg0->vertices[3].x.i.hi = *(u16*)ptr++;
        arg0->vertices[3].y.i.hi = *(u16*)ptr;
        arg0->unk2 = 4;
        arg0->ext.title_quad.unk38 = 3;
    }
    quad_is_on_screen(arg0);
}
#endif
#endif

// TitleUpdate2 state 6
// title_quad_flash
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/quads/quad_11_title_quad", func_800D7468);
#else
void func_800D7468(struct QuadObj* quad)
{
    struct QuadVertex* vertex;
    s16* point;
    s32 dx;
    s32 dy;
    s32 i;
    u8 hit;

    vertex = quad->vertices;
    for (i = 0; i < 4; i++) {
        point = &title_quad_shapes[quad->unk2][i * 2];
        dx = vertex->x.val - FIXED(point[0]);
        dy = vertex->y.val - FIXED(point[1]);
        hit = angle_from_delta(dx, dy);
        if ((((quad->ext.title_quad.unk3E[i] ^ hit) & 0x10) || quad->ext.title_quad.unk3A[i] != 0) && quad->ext.title_quad.unk42 == 0) {
            vertex->x.val = FIXED(point[0]);
            vertex->y.val = FIXED(point[1]);
            quad->ext.title_quad.unk3A[i] = 1;
        } else {
            vertex->x.val -= dx / quad->ext.title_quad.unk38;
            vertex->y.val -= dy / quad->ext.title_quad.unk38;
            quad->ext.title_quad.unk3A[i] = 0;
            if (i == 3) {
                quad->ext.title_quad.unk42 = 0;
            }
        }
        vertex++;
        quad->ext.title_quad.unk3E[i] = hit;
    }
    if (--quad->ext.title_quad.unk38 == 0) {
        point = title_quad_shapes[quad->unk2];
        quad->vertices[0].x.i.hi = *point++;
        quad->vertices[0].y.i.hi = *point++;
        quad->vertices[1].x.i.hi = *point++;
        quad->vertices[1].y.i.hi = *point++;
        quad->vertices[2].x.i.hi = *point++;
        quad->vertices[2].y.i.hi = *point++;
        quad->vertices[3].x.i.hi = *point++;
        quad->vertices[3].y.i.hi = *point;
        quad->state = 4;
        quad->ext.title_quad.unk42 = 1;
    }
    quad_is_on_screen(quad);
}
#endif

// TitleUpdate2 state 2
void title_quad_despawn(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

// title screen doesn't appear if nopped out
void TitleUpdate2(struct QuadObj* arg0)
{
    g_TitleUpdate2Funcs[arg0->state](arg0);
}

#ifdef VERSION_JP
s16 title_quad_shapes[10][8] = {
    { 0, 0, 319, 0, 319, 120, 0, 120 },
    { 80, 192, 319, 121, 319, 240, 80, 240 },
    { 330, 120, 80, 191, 81, 192, 331, 121 },
    { 80, 191, 0, 120, 4, 121, 84, 192 },
    { 0, 120, 330, 120, 331, 121, 1, 121 },
    { 0, 120, 330, 120, 80, 192, 80, 192 },
    { 6, 122, 316, 122, 81, 188, 81, 188 },
    { 80, 104, 19, 59, 230, 59, 230, 59 },
    { 80, 102, 24, 61, 217, 61, 217, 61 },
    { 80, 191, 0, 119, 0, 240, 80, 240 },
};

s16 title_quad_delays[4] = { 0, 20, 40, 0 };

u16 title_quad_palette[2][15] = {
    {
        0x83E0,
        0x8BC2,
        0x93C4,
        0x9BC6,
        0xA3C8,
        0xAFCB,
        0xB7CD,
        0xBFCF,
        0xC7D1,
        0xCFD3,
        0xDBD6,
        0xE3D8,
        0xEBDA,
        0xF3DC,
        0xFFFF,
    },
    {
        0x8421,
        0x8422,
        0x8424,
        0x8426,
        0x8428,
        0x842A,
        0x842C,
        0x842E,
        0x8430,
        0x8432,
        0x8433,
        0x8435,
        0x8437,
        0x8439,
        0x845F,
    },
};
#else
s16 title_quad_shapes[11][8] = {
    { 0, 0, 319, 0, 319, 120, 0, 120 },
    { 80, 192, 319, 121, 319, 240, 80, 240 },
    { 330, 120, 80, 191, 81, 192, 331, 121 },
    { 80, 191, 0, 120, 4, 121, 84, 192 },
    { 0, 120, 330, 120, 331, 121, 1, 121 },
    { 0, 120, 330, 120, 80, 192, 80, 192 },
    { 6, 122, 316, 122, 81, 188, 81, 188 },
    { 80, 104, 19, 59, 230, 59, 230, 59 },
    { 80, 102, 24, 61, 217, 61, 217, 61 },
    { 80, 191, 0, 119, 0, 240, 80, 240 },
    { 319, 0, 319, 239, 0, 239, 0, 0 },
};

s16 title_quad_morph_targets[6][2] = {
    { 23, 72 },
    { 216, 65 },
    { 216, 67 },
    { 23, 74 },
    { 0, 20 },
    { 40, 0 },
};

u16 title_quad_palette[30] = {
    0x8421,
    0x8C63,
    0x94A5,
    0xA108,
    0xAD6B,
    0xB5AD,
    0xC210,
    0xC631,
    0xCE73,
    0xDAD6,
    0xDEF7,
    0xE739,
    0xEF7B,
    0xF7BD,
    0x7FFF,
    0x8421,
    0x8422,
    0x8424,
    0x8426,
    0x8428,
    0x842A,
    0x842C,
    0x842E,
    0x8430,
    0x8432,
    0x8433,
    0x8435,
    0x8437,
    0x8439,
    0x845F,
};

#endif

void TitleSetWhiteQuadSpeed(struct QuadObj*);

void (*g_TitleUpdate2Funcs[])(struct QuadObj*) = {
    title_quad_init,
    title_quad_split,
    title_quad_despawn,
    title_quad_delay,
    TitleSetWhiteQuadSpeed,
    title_quad_morph,
    func_800D7468,
};
