#include "test_runtime.h"
struct RenderVector {
    u8 flags, flip, active;
    u16 texture, clut, result_clut, tpage;
    u8 code, length;
    s8 left, right, top, bottom;
    u32 uv01, uv23, mode;
};
static const struct RenderVector render_vectors[12] = {
    { 0x00, 0x00, 0x01, 0x000F, 0x780C, 0x780C, 0x0000, 0x7D, 3, -3, 13, 5, 21, 0x000000F0, 0, 0xE1000020 },
    { 0x00, 0x40, 0x01, 0x0010, 0x780C, 0x780C, 0x0020, 0x2D, 9, -13, 2, 5, 21, 0x1000100F, 0x2000200F, 0xE1000020 },
    { 0x40, 0x00, 0x01, 0x000F, 0x8000, 0x7840, 0x0020, 0x2D, 9, -3, 13, 5, 21, 0x00EF00FF, 0x10EF10FF, 0xE1000020 },
    { 0x40, 0x40, 0x51, 0x00AF, 0x780C, 0x780C, 0, 0x7F, 3, -13, 3, 5, 21, 0x0000A0F0, 0, 0xE1000026 },
    { 0x80, 0x00, 0x01, 0x000F, 0x780C, 0x780C, 0x0020, 0x2D, 9, -3, 12, 5, 20, 0x0FFF0FF0, 0x00FF00F0, 0xE1000020 },
    { 0x80, 0x40, 0x01, 0x0010, 0x8000, 0x7840, 0x0020, 0x2D, 9, -13, 2, 5, 21, 0x1F001F0F, 0x0F000F0F, 0xE1000020 },
    { 0xC0, 0x00, 0x51, 0x00AF, 0x780C, 0x780C, 0x0026, 0x2F, 9, -3, 13, 5, 21, 0xAFEFAFFF, 0x9FEF9FFF, 0xE1000020 },
    { 0xC0, 0x40, 0x51, 0x0010, 0x8000, 0x7840, 0x0026, 0x2F, 9, -13, 3, 5, 21, 0x1F101F00, 0x0F100F00, 0xE1000020 },
    { 0x0C, 0x00, 0x21, 0x00AF, 0x780C, 0x780F, 0, 0x7D, 3, -3, 13, 5, 21, 0x0000B0F0, 0, 0xE1000027 },
    { 0x4C, 0x00, 0x31, 0x000F, 0x780C, 0x780F, 0x0025, 0x2F, 9, -3, 13, 5, 21, 0xB0EFB0FF, 0xC0EFC0FF, 0xE1000020 },
    { 0x8C, 0x40, 0x21, 0x0010, 0x780C, 0x780F, 0x0025, 0x2D, 9, -13, 2, 5, 21, 0xCF00CF0F, 0xBF00BF0F, 0xE1000020 },
    { 0xCC, 0x00, 0x31, 0x00AF, 0x8000, 0x7840, 0x0027, 0x2F, 9, -3, 13, 5, 21, 0xBFEFBFFF, 0xAFEFAFFF, 0xE1000020 },
};
static POLY_FT4 primitives[4], expected_primitives[4];
static DR_TPAGE modes[4], expected_modes[4];
static P_TAG heads[2][4][8], expected_heads[2][4][8];
static P_TAG* expected_tails[2][4][8];
static struct BackgroundObj expected_backgrounds[3];
static u32 frames[8], expected_frames[8];
static u32 object_before[(sizeof(main_objects) + sizeof(misc_objects)) / 4];
static void* pool;
static u32 pool_size, buffer, group, priority;
static struct VisualObj* object;
#define R_COPY(a, b) c_test_copy_words((u32*)&(a), (u32*)&(b), sizeof(a) / 4)
#define R_SAME(a, b) assert(c_test_word_difference((u32*)&(a), (u32*)&(b), sizeof(a) / 4) == 0)
#define BIND(one, region, field)                            \
    do {                                                    \
        pool = &(region);                                   \
        pool_size = sizeof(region);                         \
        c_test_zero_words((u32*)pool, pool_size / 4);       \
        (one).field = (void*)frames;                        \
        (one).unk40 = v->texture;                           \
        (one).unk42 = v->clut;                              \
        (one).animation_step.packed = 0x01120034;           \
        (one).animation_step.fields.frame_index = slot & 1; \
        object = (struct VisualObj*)&(one);                 \
    } while (0)
#define PICK(array) (slot == 0 ? 0 : slot == 1 ? COUNT(array) / 2 \
                                               : COUNT(array) - 1)
static void render_setup(u32 kind, u32 slot, const struct RenderVector* v, u32 context)
{
    u32 b, g, p;
    memset(primitives, 0xA5, sizeof(primitives));
    memset(modes, 0x5A, sizeof(modes));
    memset(heads, 0x36, sizeof(heads));
    memset(background_objects, 0, sizeof(background_objects));
    memset(frames, 0x27, sizeof(frames));
    frames[0] = frames[1] = 0x00020001;
    frames[2] = frames[3] = v->flags | (0xFDu << 16) | (5u << 24);
    switch (kind) {
    case 0:
        BIND(g_Player, g_Player, unk3C);
        break;
    case 1:
        BIND(g_Entity, g_Entity, unk3C);
        break;
    case 2:
        BIND(qux_object, qux_object, unk3C);
        break;
    case 3:
        BIND(baz_objects[PICK(baz_objects)], baz_objects, unk3C);
        break;
    case 4:
        BIND(foo_objects[PICK(foo_objects)], foo_objects, unk3C);
        break;
    case 5:
        BIND(unk_objects[PICK(unk_objects)], unk_objects, unk3C);
        break;
    case 6:
        BIND(main_objects[PICK(main_objects)], main_objects, sprite_frames);
        break;
    case 7:
        BIND(shot_objects[PICK(shot_objects)], shot_objects, unk3C);
        break;
    case 8:
        BIND(weapon_objects[PICK(weapon_objects)], weapon_objects, unk3C);
        break;
    case 9:
        BIND(visual_objects[PICK(visual_objects)], visual_objects, unk3C);
        break;
    case 10:
        BIND(misc_objects[PICK(misc_objects)], misc_objects, unk3C);
        break;
    default:
        BIND(item_objects[PICK(item_objects)], item_objects, sprite_frames);
        break;
    }
    object->active = v->active;
    object->unk15 = v->flip;
    object->x_pos.val = 100 * 65536 + 0x1357;
    object->y_pos.val = 80 * 65536 + 0x2468;
    object->bg_offset = context ? 1 : -1;
    object->unk16 = ((kind % 4) << 4) | ((kind + slot) % 8);
    background_objects[1].x_pos.val = 7 * 65536 + 0xAAAA;
    background_objects[1].y_pos.val = -9 * 65536 + 0xBBBB;
    buffer = kind & 1;
    group = kind % 4;
    priority = (kind + slot) % 8;
    for (b = 0; b < 2; b++)
        for (g = 0; g < 4; g++)
            for (p = 0; p < 8; p++)
                D_8013BC40[b][g][p] = &heads[b][g][p];
    TEST_BG_TILE_PIXELS = context ? (u8*)frames : NULL;
    SP_DRAW_BUFFER = buffer;
    SP_SPRITE_COUNT = 0;
    SP_PRIM_CURSOR = &primitives[1];
    SP_DRAW_MODE_CURSOR = &modes[1];
}
static void render_snapshot(void)
{
    assert(pool_size <= sizeof(object_before));
    c_test_copy_words(object_before, pool, pool_size / 4);
    R_COPY(expected_primitives, primitives);
    R_COPY(expected_modes, modes);
    R_COPY(expected_heads, heads);
    R_COPY(expected_tails, D_8013BC40);
    R_COPY(expected_frames, frames);
    R_COPY(expected_backgrounds, background_objects);
}
static void expected_command(const struct RenderVector* v, u32 context, u32 linked)
{
    POLY_FT4* p = &expected_primitives[1];
    DR_TPAGE* d = &expected_modes[1];
    s32 x = context ? 93 : 100, y = context ? 89 : 80;
    setlen(p, v->length);
    p->code = v->code;
    p->x0 = x + v->left;
    p->y0 = y + v->top;
    p->clut = v->result_clut;
    p->u0 = v->uv01;
    p->v0 = v->uv01 >> 8;
    if (v->length == 9) {
        p->x1 = x + v->right;
        p->y1 = y + v->top;
        p->x2 = x + v->left;
        p->y2 = y + v->bottom;
        p->x3 = x + v->right;
        p->y3 = y + v->bottom;
        p->tpage = v->tpage;
        p->u1 = v->uv01 >> 16;
        p->v1 = v->uv01 >> 24;
        p->u2 = v->uv23;
        p->v2 = v->uv23 >> 8;
        p->u3 = v->uv23 >> 16;
        p->v3 = v->uv23 >> 24;
    }
    setlen(d, 1);
    d->code[0] = v->mode;
    setaddr(d, &primitives[1]);
    setaddr(p, &modes[2]);
    if (linked) {
        setaddr(&expected_heads[buffer][group][priority], &modes[1]);
        expected_tails[buffer][group][priority] = (P_TAG*)&primitives[1];
    }
}
static u32 render_check(u32 count, u32 advanced)
{
    R_SAME(primitives, expected_primitives);
    R_SAME(modes, expected_modes);
    R_SAME(heads, expected_heads);
    R_SAME(D_8013BC40, expected_tails);
    R_SAME(frames, expected_frames);
    R_SAME(background_objects, expected_backgrounds);
    assert(c_test_word_difference(pool, object_before, pool_size / 4) == 0);
    assert(SP_SPRITE_COUNT == count && SP_DRAW_BUFFER == buffer);
    assert(SP_PRIM_CURSOR == &primitives[1 + advanced] && SP_DRAW_MODE_CURSOR == &modes[1 + advanced]);
    return 1;
}
static u32 render_pool_case(u32 row)
{
    u32 vector = row % 12, kind = (row + row / 12) % 4, context = row / 12;
    render_setup(kind, 0, &render_vectors[vector], context);
    render_snapshot();
    expected_command(&render_vectors[vector], context, 1);
    func_80024334(object);
    return render_check(1, 1);
}
static u32 render_limit_case(u32 row)
{
    u32 mode = row % 3, vector = row / 3;
    render_setup(9, 1, &render_vectors[vector], 0);
    if (mode == 0)
        frames[1] = 0x00020000;
    else if (mode == 1)
        SP_SPRITE_COUNT = 1000;
    else {
        frames[1] = 0x00020002;
        SP_SPRITE_COUNT = 999;
    }
    render_snapshot();
    if (mode == 2)
        expected_command(&render_vectors[vector], 0, 0);
#ifndef MMX4_PC
    if (mode == 0) {
        setaddr(&expected_heads[buffer][group][priority], &modes[1]);
        expected_tails[buffer][group][priority] = (P_TAG*)&primitives[0];
    }
#endif
    func_80024334(object);
    return render_check(mode == 0 ? 0 : 1000, 0);
}
