#include "common.h"

#include <libspu.h>

void SelectACharacterUpdate(struct MiscObj*);

extern u16 D_800F1868[18];

u32 D_800F45E4[10] = {
    0,
    0x1936,
    0x4DA8,
    0x88D5,
    0xD218,
    0x137EF,
    0x1DEF1,
    0x34BEB,
    0xA2736,
    0xFFFFFFFF,
};

struct ControllerButtons {
    u16 current;
    u16 previous;
    u16 pressed;
};

struct ControllerButtons D_80166D50;
u16 D_8016949A[23][4];

static u16 decode_pad_buttons(const u8* pad)
{
    u16 buttons;

    if (pad[0] == 0xFF || pad[1] != 0x41)
        return 0;
    buttons = ~((pad[2] << 8) | pad[3]);
    if ((buttons & 0xA000) == 0xA000)
        buttons &= 0x5FFF;
    if ((buttons & 0x5000) == 0x5000)
        buttons &= 0xAFFF;
    return buttons;
}

void func_80012328(void)
{
    u16 buttons;

    mmx4_pc_input_update(D_80166D68);
    buttons = decode_pad_buttons(D_80166D68);
    D_80166C0A = D_80166C08;
    D_80166C08 = buttons;
    controller_state = buttons & (buttons ^ D_80166C0A);

    buttons = decode_pad_buttons(D_8012F46C);
    D_80166D50.previous = D_80166D50.current;
    D_80166D50.current = buttons;
    D_80166D50.pressed = buttons & (buttons ^ D_80166D50.previous);
}

void func_80016124(void)
{
    SPRT* sprites = D_80139268[SP_DRAW_BUFFER];
    DR_MODE* draw_mode = &D_80139250[SP_DRAW_BUFFER];
    s16 x = 0;
    s16 y = 0;
    s32 i;

    for (i = 0; i < 17; i++) {
        SPRT* sprite = &sprites[i];
        s16 width;

        setSprt(sprite);
        switch (D_800F1868[i]) {
        case 0:
            setUV0(sprite, 0x00, 0xD0);
            width = 0x70;
            break;
        case 1:
            setUV0(sprite, 0x70, 0xD0);
            width = 0x60;
            break;
        case 2:
            setUV0(sprite, 0x00, 0xD0);
            width = 0x10;
            break;
        default:
            abort();
        }

        sprite->clut = 0x784C;
        setWH(sprite, width, 0x30);
        setXY0(sprite, x, y);
        setShadeTex(sprite, 1);
        setSemiTrans(sprite, 0);
        addPrim(&cur_draw_info->ordering_table.ui, sprite);

        x += width;
        if ((u16)x >= 0x140) {
            x = 0;
            y += 0x30;
        }
    }

    SetDrawMode(draw_mode, 0, 0, GetTPage(0, 0, 0x380, 0x100), 0);
    addPrim(&cur_draw_info->ordering_table.ui, draw_mode);
}

void func_8001A9EC(struct EngineObj* obj)
{
    u8 previous_character = 0;

    if (engine_obj.unk1 != 0)
        previous_character = D_80141BDF[0];

    D_800F1FA0[obj->unk1](obj);
    if (D_80141BDF[0] != previous_character && (controller_state & 0x50) == 0) {
        func_8001540C(0, 0xC, 0);
    }

    func_80016124();
    update_misc_objects();
    init_objects();
}

void func_8002B3C0(struct BaseObj* obj)
{
    func_8002B318(obj, 0x60, 0x50);
}

void func_8002E994(struct EngineObj* arg0)
{
    u16 direction = D_80166C08 & 0xF000;
    s8 selection = arg0->unk3;
    s8 next = selection;
    int moved = 0;

    if (direction == PADLup || direction == PADLright || direction == PADLdown || direction == PADLleft) {
        if ((D_80166C08 ^ controller_state) & direction) {
            if (arg0->unk8 != 0) {
                arg0->unk8--;
            } else {
                s16 repeats = arg0->unkA++;
                arg0->unk8 = repeats < 3 ? 0x1E : 0xA;
                if (direction == PADLup) {
                    if ((u8)arg0->unk5F >= 5) {
                        if (selection == 8)
                            next = 0;
                        else if (selection >= 4)
                            next = 8;
                    } else if (selection >= 4) {
                        next = selection - 4;
                    }
                } else if (direction == PADLdown) {
                    if ((u8)arg0->unk5F >= 5) {
                        if (selection == 8)
                            next = 4;
                        else if (selection < 4)
                            next = 8;
                    } else if (selection < 4) {
                        next = selection + 4;
                    }
                } else if (direction == PADLright) {
                    if (selection != 8 && (selection & 3) != 3)
                        next = selection + 1;
                } else {
                    if (selection != 8 && (selection & 3) != 0)
                        next = selection - 1;
                }
                moved = next != selection;
            }
        }
    } else {
        arg0->unk8 = 0;
        arg0->unkA = 0;
    }

    if (moved) {
        arg0->unk3 = next;
        func_8001540C(5, 0, 0);
    }

    if (controller_state & (PADstart | PADRdown)) {
        if (arg0->unk3 == 8) {
            if ((u8)arg0->unk5F < 7) {
                arg0->stage = 0xA;
                arg0->unk40 = arg0->cur_character == 0 ? 0x31 : 0x11;
            } else {
                arg0->stage = (u8)arg0->unk5F < 0xA ? 0xB : 0xC;
                arg0->unk40 = 0x11;
            }
            D_8013B814 = 0;
        } else {
            arg0->unk40 = arg0->cur_character == 0 ? 0x31 : 0x11;
            arg0->stage = D_800F474C.stage_order[(u8)arg0->unk3];
            arg0->substage = D_8013B814;
        }
        func_8001540C(5, 1, 0);
        arg0->unk2 = 0;
        arg0->unk1++;
    }
}

extern const u16* D_800F19E0;
extern const u16* D_800F19E4;
extern const u16* D_800F19E8;
extern const u16* D_800F19EC;
extern const u16* D_800F19F0;
extern const u16* D_800F19F4;
extern const u16* D_800F19F8;
extern const u16* D_800F19FC;
extern const u16* D_800F1A00;
extern const u16* D_800F1A04;
extern const u16* D_800F1A08;
extern s16 D_80139560;
extern s32 D_80139538;
extern s32 D_80139540;
extern s32 D_80139544;
s32 func_80013614(s32 arg0, s32* arg1);
void func_80016420(s8 arg0);

void func_8001663C(u8 selection, u8 volume)
{
    const u16* entry;
    u8 index = selection;
    u8 channel = 0;
    s32 start;
    u16 i;

    D_80139568 = 0;
    switch (selection >> 3) {
    case 0:
        D_80139560 = 0x95;
        entry = D_800F19E0;
        if (selection == 0)
            D_80139568 = 1;
        break;
    case 1:
        D_80139560 = 0x96;
        entry = D_800F19E4;
        index &= 7;
        break;
    case 2:
        D_80139560 = 0x97;
        entry = D_800F19E8;
        index &= 7;
        break;
    case 3:
        D_80139560 = 0x98;
        entry = D_800F19EC;
        index &= 7;
        break;
    case 4:
        D_80139560 = 0x99;
        entry = D_800F19F0;
        index &= 7;
        D_80139568 = 1;
        break;
    case 5:
        D_80139560 = 0x9B;
        entry = D_800F19F4;
        index &= 7;
        D_80139568 = 1;
        break;
    case 6:
        D_80139560 = 0x9C;
        entry = D_800F19F8;
        index &= 7;
        D_80139568 = 1;
        break;
    case 7:
        D_80139560 = 0x9D;
        entry = D_800F19FC;
        index &= 7;
        D_80139568 = 1;
        break;
    case 8:
        D_80139560 = 0x9E;
        entry = D_800F1A00;
        index &= 7;
        D_80139568 = 1;
        break;
    case 9:
        D_80139560 = 0x9F;
        entry = D_800F1A04;
        index &= 7;
        D_80139568 = 1;
        break;
    case 10:
        D_80139560 = 0x9A;
        entry = D_800F1A08;
        index &= 7;
        D_80139568 = 1;
        break;
    default:
        return;
    }

    for (i = 1; i < index; i++) {
        if (*entry & 0x8000) {
            channel++;
            entry += 2;
        }
        entry += 2;
    }

    ((u8*)D_80175EE8)[0] = 1;
    ((u8*)D_80175EE8)[1] = channel;
    start = func_80013614(D_80139560, &D_80139538) + channel;
    D_80139540 = start + ((entry[0] & 0x7FFF) * 8);
    D_80139544 = start + ((entry[1] & 0x7FFF) * 8);
    CdIntToPos(D_80139540, (CdlLOC*)&D_80139514);
    SsSetSerialAttr(0, 0, 1);
    func_80016420(volume);
    D_80141BD4 = 2;
    D_80173C84 = 1;
    D_80139530 = 7;
}

s32 func_80015D60(struct Unk19* arg0, s32 animation)
{
    struct MiscObj* object = (struct MiscObj*)arg0;

    object->animation_cursor = object->animation_table[animation];
    object->base.unk17 = animation;
    object->pad47[0] = 0xFF;
    object->unk44 = *object->animation_cursor;
    return 0;
}

static P_TAG* quad_heads[2][4][8];
static P_TAG* quad_tails[2][4][8];
static P_TAG* background_heads[2][6][8];
static P_TAG* background_tails[2][6][8];

struct PcSpriteFrame {
    void* data;
    u16 texture;
    u16 clut;
    u8 index;
};

#define PC_OBJECT_IN_ARRAY(object, array) \
    ((uintptr_t)(object) >= (uintptr_t) & (array)[0] && (uintptr_t)(object) < (uintptr_t) & (array)[COUNT(array)])

static s32 get_pc_sprite_frame(struct VisualObj* object,
    struct PcSpriteFrame* frame)
{
    if (object == (struct VisualObj*)&g_Player || object == (struct VisualObj*)&g_Entity) {
        struct PlayerObj* player = (struct PlayerObj*)object;

        frame->data = player->unk3C;
        frame->texture = player->unk40;
        frame->clut = player->unk42;
        frame->index = player->cur_anim;
    } else if (PC_OBJECT_IN_ARRAY(object, baz_objects)) {
        struct BazObj* baz = (struct BazObj*)object;

        frame->data = baz->unk3C;
        frame->texture = baz->unk40;
        frame->clut = baz->unk42;
        frame->index = ((u8*)baz)[0x4B];
    } else if (PC_OBJECT_IN_ARRAY(object, foo_objects) || PC_OBJECT_IN_ARRAY(object, unk_objects)) {
        struct UnkObj* unknown = (struct UnkObj*)object;

        frame->data = unknown->unk3C;
        frame->texture = unknown->unk40;
        frame->clut = unknown->unk42;
        frame->index = unknown->unk47;
    } else if (PC_OBJECT_IN_ARRAY(object, main_objects)) {
        struct Unk* main = (struct Unk*)object;

        frame->data = (void*)main->sprite_frames;
        frame->texture = main->unk40;
        frame->clut = main->unk42;
        frame->index = main->animation_index;
    } else if (PC_OBJECT_IN_ARRAY(object, weapon_objects)) {
        struct WeaponObj* weapon = (struct WeaponObj*)object;

        frame->data = weapon->unk3C;
        frame->texture = weapon->unk40;
        frame->clut = weapon->unk42;
        frame->index = ((u8*)weapon)[0x4B];
    } else if (PC_OBJECT_IN_ARRAY(object, visual_objects)) {
        struct VisualObj* visual = object;

        frame->data = visual->unk3C;
        frame->texture = visual->unk40;
        frame->clut = visual->unk42;
        frame->index = visual->unk47;
    } else if (PC_OBJECT_IN_ARRAY(object, misc_objects)) {
        struct MiscObj* misc = (struct MiscObj*)object;

        frame->data = misc->unk3C;
        frame->texture = misc->unk40;
        frame->clut = misc->unk42;
        frame->index = misc->unk47;
    } else {
        return 0;
    }

    if (frame->data != NULL && pc_archive_slots[0] != NULL && ((uintptr_t)frame->data >> 32) != ((uintptr_t)pc_archive_slots[0] >> 32)) {
        frame->data = (void*)(((uintptr_t)pc_archive_slots[0] & ~(uintptr_t)UINT32_MAX) | ((uintptr_t)frame->data & UINT32_MAX));
    }

    return frame->data != NULL;
}

#undef PC_OBJECT_IN_ARRAY

void func_80024260(void)
{
    u32 buffer = SP_DRAW_BUFFER;
    u32 i;

    for (i = 0; i < 4; i++) {
        OT_TYPE* ordering_tag = &cur_draw_info->ordering_table.start + D_80173C6C[i];
        u32 j;

        for (j = 0; j < 8; j++) {
            P_TAG* head = quad_heads[buffer][i][j];

            if (head != NULL) {
                setaddr(quad_tails[buffer][i][j], getaddr(ordering_tag));
                setaddr(ordering_tag, head);
                quad_heads[buffer][i][j] = NULL;
                quad_tails[buffer][i][j] = NULL;
            }
        }
    }
}

void func_80024334(struct VisualObj* object)
{
    POLY_FT4* primitive;
    DR_TPAGE* draw_mode;
    u8* frame_data;
    u16* frame_header;
    s32 frame_count;
    s32 origin_x;
    s32 origin_y;
    u8 flipped;
    u16 texture;
    u16 clut;
    P_TAG* first_draw_mode;
    struct PcSpriteFrame frame;

    if (SP_SPRITE_COUNT >= 1000)
        return;

    if (!get_pc_sprite_frame(object, &frame))
        return;

    if (object->base.bg_offset < 0) {
        origin_x = object->base.x_pos.i.hi;
        origin_y = object->base.y_pos.i.hi;
    } else {
        struct BackgroundObj* background = &background_objects[object->base.bg_offset];

        origin_x = object->base.x_pos.i.hi - background->x_pos.i.hi;
        origin_y = object->base.y_pos.i.hi - background->y_pos.i.hi;
    }

    primitive = SP_PRIM_CURSOR;
    draw_mode = SP_DRAW_MODE_CURSOR;
    first_draw_mode = (P_TAG*)draw_mode;
    frame_header = (u16*)((u8*)frame.data + frame.index * 4);
    frame_count = frame_header[0];
    frame_data = (u8*)frame.data + frame_header[1] * 4;
    flipped = object->base.unk15;
    texture = frame.texture;
    clut = frame.clut;

    while (frame_count-- != 0) {
        u8 flags;
        u32 texture_index;
        s32 x0;
        s32 x1;
        s32 y0;
        s32 y1;
        s32 u0;
        s32 u1;
        s32 v0;
        s32 v1;
        u16 primitive_clut;

        if (SP_SPRITE_COUNT >= 1000)
            return;
        SP_SPRITE_COUNT++;

        flags = frame_data[0];
        x0 = (s8)frame_data[2];
        if (flipped == 0) {
            x1 = x0 + 16;
        } else {
            x1 = -x0;
            x0 = -(x0 + 16);
        }
        x0 += origin_x;
        x1 += origin_x;
        y0 = origin_y + (s8)frame_data[3];
        y1 = y0 + 16;

        texture_index = texture + (frame_data[1] | ((flags & 3) << 8));
        if (object->base.active & 0x40) {
            u32 index = texture_index & 0xFFFF;

            texture_index = ((index / 176) << 8) + index % 176 + 0x600;
        }
        if (object->base.active & 0x20) {
            u32 index = texture_index & 0xFFFF;

            texture_index = ((index / 80) << 8) + index % 80 + 0x5B0;
        }

        if (clut & 0x8000) {
            primitive_clut = 0x7840;
        } else {
            primitive_clut = clut + ((flags & 0xC) >> 2);
            if (primitive_clut & 0x30)
                primitive_clut += 0x30;
        }

        v0 = texture_index & 0xF0;
        if (!(flags & 0x80) && ((flags & 0x40) ^ flipped) == 0) {
            setSprt16(primitive);
            setShadeTex(primitive, 1);
            setSemiTrans(primitive, object->base.active & 0x10);
            primitive->clut = primitive_clut;
            primitive->x0 = x0;
            primitive->y0 = y0;
            primitive->u0 = texture_index * 16;
            primitive->v0 = v0;
        } else {
            if (!(flags & 0x80)) {
                setPolyFT4(primitive);
                setShadeTex(primitive, 1);
                setSemiTrans(primitive, object->base.active & 0x10);
                u0 = texture_index * 16 - 1;
                u1 = texture_index * 16 | 0xF;
                if ((u8)u0 == 0xFF) {
                    u0 = texture_index * 16;
                    x1--;
                }
                v1 = v0 + 16;
                if ((u8)v1 == 0) {
                    v1 = v0 + 15;
                    y1--;
                }
            } else {
                setlen(primitive, 9);
                setcode(primitive,
                    object->base.active & 0x10 ? 0x2F : 0x2D);
                v1 = (texture_index & 0xF0) - 1;
                v0 = (texture_index & 0xF0) | 0xF;
                if ((u8)v1 == 0xFF) {
                    v1 = texture_index & 0xF0;
                    y1--;
                }
                if (((flags & 0x40) ^ flipped) == 0) {
                    u0 = texture_index * 16 + 16;
                    u1 = texture_index * 16;
                    if ((u8)u0 == 0) {
                        u0 = texture_index * 16 | 0xF;
                        x1--;
                    }
                } else {
                    u0 = texture_index * 16 - 1;
                    u1 = texture_index * 16 | 0xF;
                    if ((u8)u0 == 0xFF) {
                        u0 = texture_index * 16;
                        x1--;
                    }
                }
            }

            primitive->clut = primitive_clut;
            primitive->tpage = (texture_index >> 8) | 0x20;
            setXY4(primitive, x0, y0, x1, y0, x0, y1, x1, y1);
            setUV4(primitive, u1, v0, u0, v0, u1, v1, u0, v1);
        }

        setlen(draw_mode, 1);
        draw_mode->code[0] = !(flags & 0x80) && ((flags & 0x40) ^ flipped) == 0
            ? (texture_index >> 8) | 0xE1000020
            : 0xE1000020;
        setaddr(draw_mode, primitive);
        setaddr(primitive, draw_mode + 1);
        primitive++;
        draw_mode++;
        frame_data += 4;
    }

    if (primitive != SP_PRIM_CURSOR) {
        u32 buffer = SP_DRAW_BUFFER;
        u32 group = object->base.unk16 >> 4;
        u32 priority = object->base.unk16 & 0xF;
        P_TAG* tail = quad_tails[buffer][group][priority];

        if (tail == NULL) {
            quad_heads[buffer][group][priority] = first_draw_mode;
        } else {
            setaddr(tail, first_draw_mode);
        }
        quad_tails[buffer][group][priority] = (P_TAG*)(primitive - 1);
    }

    SP_PRIM_CURSOR = primitive;
    SP_DRAW_MODE_CURSOR = draw_mode;
}

void func_80024920(struct QuadObj* arg0)
{
    POLY_F4* primitive;
    DR_MODE* draw_mode;
    s32 x;
    s32 y;
    u32 red;
    u32 green;
    u32 blue;
    u8 ordering;
    u32 group;
    u32 priority;
    u32 buffer;

    if (SP_SPRITE_COUNT >= 1000)
        return;
    SP_SPRITE_COUNT++;

    if (arg0->bg_offset < 0) {
        x = arg0->x_pos.i.hi;
        y = arg0->y_pos.i.hi;
    } else {
        struct BackgroundObj* background = &background_objects[arg0->bg_offset];

        x = arg0->x_pos.i.hi - background->x_pos.i.hi;
        y = arg0->y_pos.i.hi - background->y_pos.i.hi;
    }

    primitive = SP_PRIM_CURSOR;
    draw_mode = SP_DRAW_MODE_CURSOR;
    setPolyF4(primitive);
    setSemiTrans(primitive, (arg0->active & 0x10) != 0);
    setXY4(primitive,
        x + arg0->unk14.i.hi, y + arg0->unk18.i.hi,
        x + arg0->unk1C.i.hi, y + arg0->unk20.i.hi,
        x + arg0->unk2C.i.hi, y + arg0->unk30.i.hi,
        x + arg0->unk24.i.hi, y + arg0->unk28.i.hi);

    red = arg0->unk34 & 0x1F;
    green = (arg0->unk34 >> 5) & 0x1F;
    blue = arg0->unk34 >> 10;
    setRGB0(primitive,
        red * 8 + (red >> 2),
        green * 8 + (green >> 2),
        blue * 8 + (blue >> 2));
    setlen(draw_mode, 1);
    draw_mode->code[0] = 0xE1000000;

    ordering = arg0->unk36;
    group = ordering >> 4;
    priority = ordering & 0xF;
    buffer = SP_DRAW_BUFFER;
    if (quad_heads[buffer][group][priority] == NULL) {
        quad_heads[buffer][group][priority] = (P_TAG*)draw_mode;
    } else {
        setaddr(quad_tails[buffer][group][priority], draw_mode);
    }
    setaddr(draw_mode, primitive);
    quad_tails[buffer][group][priority] = (P_TAG*)primitive;

    SP_PRIM_CURSOR = primitive + 1;
    SP_DRAW_MODE_CURSOR = draw_mode + 1;
}

void func_800262B8(u8 layer)
{
    struct BackgroundObj* background = &background_objects[layer];
    s32 source_tile_x = background->x_pos.i.hi / 16;
    s32 source_tile_y = background->y_pos.i.hi / 16;
    s32 block_x = source_tile_x / 16;
    s32 block_y = source_tile_y / 16;
    s32 tile_y = source_tile_y & 31;
    s32 inner_y = source_tile_y & 15;
    s32 layer_offset = layer * layout_size;
    s32 row_offset = block_y * layout_width;
    s32 row;

    for (row = 0; row < 17; row++) {
        s32 current_block_x = block_x;
        s32 tile_x = source_tile_x & 31;
        s32 inner_x = source_tile_x & 15;
        u8 block = SP_BG_TILEMAP[layer_offset + row_offset + current_block_x];
        s32 column;

        for (column = 0; column < 22; column++) {
            D_801441C8[layer][tile_y][tile_x] = SP_BG_TILE_PIXELS[block * 256 + inner_y * 16 + inner_x];
            tile_x = (tile_x + 1) & 31;
            inner_x++;
            if (inner_x == 16) {
                inner_x = 0;
                current_block_x++;
                block = SP_BG_TILEMAP[layer_offset + row_offset + current_block_x];
            }
        }

        tile_y = (tile_y + 1) & 31;
        inner_y++;
        if (inner_y == 16) {
            inner_y = 0;
            row_offset += layout_width;
        }
    }

    background->unk4C = 0;
}

void func_80026894(s32 layer)
{
    s32 buffer = SP_DRAW_BUFFER;
    s32 back_layer = layer + 3;
    s32 i;

    for (i = 0; i < 8; i++) {
        P_TAG* head = background_heads[buffer][layer][i];

        if (head != NULL) {
            DR_TPAGE* page = &D_80171EB0[buffer][layer][i];

            setaddr(page, head);
            addPrims(&cur_draw_info->ordering_table.start + *(s8*)&background_objects[layer].unk4A,
                page,
                background_tails[buffer][layer][i]);
            background_heads[buffer][layer][i] = NULL;
            background_tails[buffer][layer][i] = NULL;
        }

        head = background_heads[buffer][back_layer][i];
        if (head != NULL) {
            DR_TPAGE* page = &D_80171EB0[buffer][back_layer][i];

            setaddr(page, head);
            addPrims(&cur_draw_info->ordering_table.start + *(s8*)&background_objects[layer].unk4B,
                page,
                background_tails[buffer][back_layer][i]);
            background_heads[buffer][back_layer][i] = NULL;
            background_tails[buffer][back_layer][i] = NULL;
        }
    }
}

void func_80026AA0(s32 layer)
{
    struct BackgroundObj* bg = &background_objects[layer];
    SPRT_16* sprite = SP_BG_PRIM_CURSOR;
    s32 tile_x = (bg->x_pos.i.hi / 16) & 31;
    s32 tile_y = (bg->y_pos.i.hi / 16) & 31;
    s32 screen_y = -(bg->y_pos.i.hi & 15);
    s32 row;

    for (row = 0; row < 16; row++) {
        s32 current_tile_x = tile_x;
        s32 screen_x = -(bg->x_pos.i.hi & 15);
        s32 column;

        for (column = 0; column < 21; column++) {
            u16 tile = D_801441C8[layer][tile_y][current_tile_x];

            if (tile != 0) {
                u32 attributes;
                s32 ordering_layer;
                s32 priority;
                P_TAG* tail;

                if (SP_BG_SPRITE_COUNT >= 1000)
                    return;
                SP_BG_SPRITE_COUNT++;

                attributes = SP_BG_TILE_ATTRS[tile & 0x3FFF];
                sprite->clut = 0x7900 | ((attributes & 0xF000) >> 6) | ((attributes & 0xF00) >> 8);
                setSemiTrans(sprite, (tile & 0x4000) != 0);
                setUV0(sprite, (attributes >> 12) & 0xF0,
                    (attributes >> 16) & 0xF0);
                setXY0(sprite, screen_x, screen_y);

                ordering_layer = layer + ((tile & 0x8000) != 0 ? 3 : 0);
                priority = attributes >> 24;
                tail = background_tails[SP_DRAW_BUFFER][ordering_layer][priority];
                if (tail == NULL) {
                    background_heads[SP_DRAW_BUFFER][ordering_layer][priority] = (P_TAG*)sprite;
                } else {
                    setaddr(tail, sprite);
                }
                background_tails[SP_DRAW_BUFFER][ordering_layer][priority] = (P_TAG*)sprite;
                sprite++;
            }

            screen_x += 16;
            current_tile_x = (current_tile_x + 1) & 31;
        }

        screen_y += 16;
        tile_y = (tile_y + 1) & 31;
    }

    SP_BG_PRIM_CURSOR = sprite;
}

void func_80027344(s32 layer, s32 x, s32 y)
{
    struct BackgroundObj* bg = &background_objects[layer];
    s32 tile_count = 18;
    s32 block_x, block_y;
    s32 tile_x, tile_y;
    s32 inner_x, inner_y;
    s32 min_block_x, max_block_x;
    s32 layer_offset, row_offset;
    s32 width;
    s32 i;
    u8 block;

    if (x < 0)
        return;
    if (y < 0) {
        y = 0;
        tile_count = 17;
    }

    block_x = x / 256;
    block_y = y / 256;
    tile_x = (x % 512) / 16;
    tile_y = (y % 512) / 16;
    inner_x = tile_x & 15;
    inner_y = tile_y & 15;
    min_block_x = bg->unk4D;
    max_block_x = bg->unk4E;

    if ((u32)block_x < min_block_x) {
        block_x += max_block_x - min_block_x + 1;
        if (bg->x_pos.i.hi <= (min_block_x - 1) * 256) {
            bg->x_pos.i.hi = max_block_x * 256;
            return;
        }
    }
    if ((u32)block_x > max_block_x) {
        block_x -= max_block_x - min_block_x + 1;
        if (bg->x_pos.i.hi >= (max_block_x + 1) * 256) {
            bg->x_pos.i.hi = min_block_x * 256;
            return;
        }
    }

    layer_offset = layer * layout_size;
    width = layout_width;
    row_offset = width * block_y;
    block = SP_BG_TILEMAP[layer_offset + row_offset + block_x];
    for (i = 0; i < tile_count; i++) {
        D_801441C8[layer][tile_y][tile_x] = SP_BG_TILE_PIXELS[block * 256 + inner_y * 16 + inner_x];
        tile_y = (tile_y + 1) & 31;
        inner_y++;
        if (inner_y == 16) {
            inner_y = 0;
            row_offset += width;
            block = SP_BG_TILEMAP[layer_offset + row_offset + block_x];
        }
    }
}

void func_800275DC(s32 layer, s32 x, s32 y)
{
    s32 block_x, block_y;
    s32 tile_x, tile_y;
    s32 inner_x, inner_y;
    s32 layer_offset, row_offset;
    s32 i;
    u8 block;

    if (y < 0)
        return;

    block_x = x / 256;
    block_y = y / 256;
    tile_x = (x % 512) / 16;
    tile_y = (y % 512) / 16;
    inner_x = tile_x & 15;
    inner_y = tile_y & 15;
    layer_offset = layer * layout_size;
    row_offset = layout_width * block_y;
    block = SP_BG_TILEMAP[layer_offset + row_offset + block_x];

    for (i = 0; i < 21; i++) {
        D_801441C8[layer][tile_y][tile_x] = SP_BG_TILE_PIXELS[block * 256 + inner_y * 16 + inner_x];
        tile_x = (tile_x + 1) & 31;
        inner_x++;
        if (inner_x == 16) {
            inner_x = 0;
            block_x++;
            block = SP_BG_TILEMAP[layer_offset + row_offset + block_x];
        }
    }
}

void func_800E0D0C(void)
{
    SpuSetReverb(1);
}

void func_800E9040(void)
{
    Psyz_GteCtrlWrite(29, 0x155);
    Psyz_GteCtrlWrite(30, 0x100);
    Psyz_GteCtrlWrite(26, 0x3E8);
    Psyz_GteCtrlWrite(27, (u32)-0x1062);
    Psyz_GteCtrlWrite(28, 0x01400000);
    Psyz_GteCtrlWrite(24, 0);
    Psyz_GteCtrlWrite(25, 0);
}

extern s16 D_800F224C[];
extern union TitleScratch D_80169498;
u8 func_8002B810(s32 arg0, s32 arg1);

void func_8001E130(struct GameInfo* arg0)
{
    s16* target;
    s32* x;
    s32* y;
    u8* flags;
    s32 x_diff;
    s32 y_diff;
    s32 i;
    struct MiscObj* obj;
    u8 direction;

    x = &D_80169498.sector[0];
    i = 0;
    flags = (u8*)&D_80169498;
    y = &D_80169498.sector[1];
    do {
        target = &D_800F224C[i * 2];
        x_diff = *x - (target[0] << 16);
        y_diff = *y - (target[1] << 16);
        direction = func_8002B810(x_diff, y_diff);
        if (((((flags[0xA2] ^ direction) & 0x10) != 0) || (flags[0x90] != 0)) && (D_80169498.title.settled == 0)) {
            *x = target[0] << 16;
            *y = target[1] << 16;
            flags[0x90] = 1;
        } else {
            *x -= x_diff / arg0->unk6;
            *y -= y_diff / arg0->unk6;
            flags[0x90] = 0;
            if (i == 0x11) {
                D_80169498.title.settled = 0;
            }
        }
        y += 2;
        x += 2;
        flags[0xA2] = direction;
        i++;
        flags++;
    } while (i < 0x12);

    arg0->unk6--;
    if (arg0->unk6 == 0) {
        target = D_800F224C;
        x = D_80169498.sector;
        i = 0;
        do {
            *x = *target << 16;
            target++;
            x++;
            i++;
        } while (i < 0x24);
        arg0->mode++;

        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->base.active = 1;
            obj->base.id = 0x13;
            obj->base.unk2 = 0xC;
        }
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->base.active = 1;
            obj->base.id = 0x13;
            obj->base.unk2 = 0x14;
        }
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->base.active = 1;
            obj->base.id = 0x13;
            obj->base.unk2 = 0x15;
        }
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->base.active = 1;
            obj->base.id = 0x1D;
            obj->base.unk2 = 0x21;
        }
        D_80139690 = &obj->base;
    }
}

void func_800CD530(struct MiscObj* arg0)
{
    switch (arg0->base.unk6) {
    case 0:
        arg0->base.unk6++;
        if (engine_obj.cur_character == (arg0->base.unk2 - 7)) {
            func_80015D60(arg0, 3);
        } else {
            func_80015D60(arg0, 0);
        }
        break;
    case 1:
        func_80015DC8(arg0);
        if (arg0->unk46 == 0) {
            engine_flags |= (1 << (arg0->base.unk2 - 7));
        }
        if ((s8)engine_flags & 0x80) {
            arg0->base.unk6 = (u8)arg0->base.unk6 + 1;
            func_80015D60(arg0, 4);
        }
        break;
    case 2:
        func_80015DC8(arg0);
        if (arg0->unk46 == 0) {
            arg0->base.unk6 = (u8)arg0->base.unk6 + 1;
            func_80015D60(arg0, 5);
            arg0->y_vel.val = 0x80000;
        }
        break;
    case 3:
        func_80015DC8(arg0);
        func_8002B718(arg0);
        if (arg0->base.on_screen == 0) {
            engine_flags &= ~(1 << (arg0->base.unk2 - 7));
            arg0->base.state = (u8)arg0->base.state + 1;
        }
        break;
    }
}
