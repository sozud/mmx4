#include "all.h"

#include <libspu.h>
#include "memcard.h"
#include "pc_replay.h"

extern u16 D_800F44E8[8], D_800F44F8[8];
extern const char D_80010058[], D_8001005C[];
extern u8 D_800F1FBC[4];

void func_80012D88(const u32* src, u32* dst, u32 count);
void func_80012DC0(const u32* src, u32* dst, u32 count);

extern u16 D_800F1868[18];
extern u8 D_800F164C[4];
extern s16 D_800F1650[2];
extern union MainPaletteData D_800F1660;
extern const u32* D_800F2FD4[];
extern struct StageObjectMarginData D_800F4334;
extern struct HudSpriteOrigin D_800F30F4[8];
extern struct PlayerGaugePosition D_800F3124[2];
extern u32* D_80137E08;

s32 func_800154E8(s32 arg0, s32 arg1, struct BaseObj* source, u8 pan);
void func_800DADA0(struct TileEffectRecord*, u16, u16, u8, u8);
s32 func_800157AC(u8 type, s32 unused, struct BaseObj* source);

s32 func_8001540C(s32 arg0, s32 arg1, void* arg2)
{
    u32 bank = arg0 & 0x7F;
    u32 group = arg0 & 0xF;
    u32 index = arg1 & 0xFF;
    u32* command;
    u32 count;

    if (bank >= COUNT(D_8013E198) || D_8013E198[bank] == -1)
        return -1;
    if (D_80141F50[group] == NULL || D_80141EE8[group] == NULL)
        return -2;
    count = (u8)((u32*)D_80141EE8[group] - (u32*)D_80141F50[group]);
    if (index >= count)
        return -2;
    command = &((u32*)D_80141F50[group])[index];
    D_80137E08 = command;
    if (*command == 0)
        return -5;
    if (D_800F164C[*(u8*)command >> 6] != 0)
        return func_800157AC(D_800F164C[*(u8*)command >> 6], index, arg2);
    return func_800154E8(arg0 & 0xFF, *(u8*)command & 0x3F, arg2, arg0 & 0xFF);
}

s32 func_800154E8(s32 arg0, s32 arg1, struct BaseObj* source, u8 pan)
{
    VagAtr tone;
    u8 packed1 = ((u8*)D_80137E08)[1];
    u8 packed2 = ((u8*)D_80137E08)[2];
    u8 packed3 = ((u8*)D_80137E08)[3];
    u8 fixed_pan = packed1 >> 7;
    u8 priority = packed2 & 0xF;
    s16 program = packed2 >> 4;
    s16 vag = packed1 & 0x7F;
    s16 voice = packed3 & 0x1F;
    s8 remaining = (packed3 & 0x60) >> 5;

    if (source != NULL) {
        if (arg0 & 0x80) {
            pan = source->unk2;
        } else {
            s16 x = source->x_pos.i.hi;
            s8 background = source->bg_offset;

            if (background >= 0 && background < COUNT(background_objects))
                x -= background_objects[background].x_pos.i.hi;
            pan = x / 10;
            if ((s8)pan < 5)
                pan = 5;
            if ((s8)pan >= 0x1C)
                pan = 0x1B;
        }
    }

    while (remaining-- >= 0) {
        s32 left;
        s32 right;
        u8 voice_index = voice & 0xFF;

        SsUtGetVagAtr(arg1 & 0xFF, vag, program, &tone);
        left = right = tone.vol;
        if (!fixed_pan && source != NULL) {
            if ((s8)pan < 0x10)
                left = (s8)pan * ((u32)left >> 4);
            else if ((s8)pan >= 0x11)
                right = (left >> 4) * (0x20 - (s8)pan);
        }
        if (SpuGetKeyStatus(1u << voice_index) != 0 && priority < D_80139234[voice_index])
            return -4;
        SsUtKeyOnV(voice_index, arg1 & 0xFF, vag, program, tone.min, tone.shift, right, left);
        D_80139234[voice_index] = priority;
        if (++program >= 0x10) {
            vag++;
            program = 0;
        }
        voice++;
    }
    return 0;
}

s32 func_800157AC(u8 type, s32 unused, struct BaseObj* source)
{
    u8 packed1 = ((u8*)D_80137E08)[1];
    u8 packed2 = ((u8*)D_80137E08)[2];
    u8 packed3 = ((u8*)D_80137E08)[3];
    u8 fixed_pan = packed1 >> 7;
    u8 access = packed1 & 0x7F;
    u8 priority = packed2 & 0xF;
    u8 slot = packed2 >> 4;
    u8 current = D_8013924C[slot];
    u8 sequence = packed3 & 0x1F;

    (void)unused;
    (void)source;
    if (current != 0xFF && SsIsEos(access, current & 0x1F)) {
        if (priority < (current >> 5))
            return -1;
        if ((current & 0x1F) == 0x1F)
            SsSeqStop(access);
        else
            SsSepStop(access, current & 0xF);
    }
    if (type == 2) {
        SsSepPlay(access, sequence, SSPLAY_PLAY, D_800F1650[fixed_pan]);
        D_8013924C[slot] = sequence | (priority << 5);
    } else {
        SsSeqPlay(access, SSPLAY_PLAY, D_800F1650[fixed_pan]);
        D_8013924C[slot] = 0x1F | (priority << 5);
    }
    return 0;
}

struct ControllerButtons {
    u16 current;
    u16 previous;
    u16 pressed;
};

struct ControllerButtons D_80166D50;
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

    mmx4_pc_input_update(pad_port1_packet);
    buttons = decode_pad_buttons(pad_port1_packet);
    controller_input.previous = controller_input.held;
    controller_input.held = buttons;
    controller_input.pressed = buttons & (buttons ^ controller_input.previous);

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

void func_8002217C(arg_u16 message, u8 portrait, s32 delay_only)
{
    struct MiscObj* window;
    u8* window_archive;
    u32 window_frame_offset;
    u16* dialogue_palette;
    u16* messages;

    if (abc_object.unkC != 0) {
        abc_object.unk10 = message | 0x8000;
        if (abc_object.unkC != 0x80) {
            struct MiscObj* parts[] = {
                D_801397C0,
                D_801397C4,
                D_801397CC,
                D_801397C8,
                D_801397D4,
                D_801397D0,
            };
            u32 i;
            for (i = 0; i < COUNT(parts); i++) {
                if (parts[i] != NULL && parts[i]->id == 0x16) {
                    parts[i]->active = 0;
                    parts[i]->on_screen = 0;
                }
            }
            abc_object.unkC = 0x80;
            abc_object.unkA = 0x27;
            abc_object.unkD = 4;
        }
        return;
    }
    abc_object.unkC = 0x80;
    abc_object.unk10 = 0;
    abc_object.unkE = 0;
    D_801397D8 = portrait;
    if (!(portrait & 0x80)) {
        D_801397DC = (struct Func80022730Config*)(D_800F2DD0[(u8)engine_obj.cur_character]
            + portrait * sizeof(struct Func80022730Config));
        if (engine_obj.cur_character == 0) {
            u8 palette_index = ((u8*)D_801397DC)[3];
            u16* portrait_palette = (u16*)((u8*)SP_PALETTE
                + 0x360 + palette_index * 0x80);

            memcpy(portrait_palette, D_800F2F40, sizeof(D_800F2F40));
        }
    }
    D_801397BC = D_801397C0 = D_801397C4 = D_801397C8 = NULL;
    D_801397CC = D_801397D0 = D_801397D4 = NULL;
    if (delay_only) {
        abc_object.unkA = 0x3C;
        abc_object.unkD = 6;
        return;
    }
    D_80139828 = engine_obj.enable_boss;
    D_80139824 = engine_obj.unk1F;
    engine_obj.enable_boss = 0;
    engine_obj.unk1F = 0;
    dialogue_palette = SP_PALETTE + (engine_obj.stage == 0xD ? 0x7C0 / 2 : 0x2A0 / 2);
    memcpy(D_801397E4, dialogue_palette, sizeof(D_801397E4));
    memcpy(dialogue_palette, D_800F1660.dialogue_palette, sizeof(D_800F1660.dialogue_palette));
    messages = (u16*)pc_archive_slots[21];
    abc_object.unk0 = (u16*)((u8*)messages + messages[message]);
    abc_object.unk4 = *abc_object.unk0;
    abc_object.unk6 = -0x78;
    abc_object.unk8 = 0x1D;
    abc_object.unkF = 1;
    abc_object.unkA = 0x27;
    abc_object.unkD = 0;
    D_801397E0 = 0;
    need_palette_load |= 1;
    window = find_free_misc_obj();
    D_801397BC = window;
    if (window != NULL) {
        window_archive = WINDOW_ARCHIVE_DATA;
        memcpy(&window_frame_offset, window_archive + 8, sizeof(window_frame_offset));
        window->active = 1;
        window->id = 0x16;
        window->unk2 = 2;
        window->unk16 = 0x11;
        window->animation_table = (u32**)D_800F2FD4;
        window->unk40 = 0x1E00;
        window->unk42 = engine_obj.stage == 0xD ? 0x78CF : 0x7846;
        window->bg_offset = -1;
        window->x_pos.i.hi = 0xA0;
        window->y_pos.i.hi = (abc_object.unk4 & 0x800)
            ? (portrait == 0xFF ? 0xB4 : 0xAC)
            : (portrait == 0x80 ? 0x74 : 0x3C);
        window->unk3C = window_archive + window_frame_offset;
        window->unk15 = 0;
        set_animation(window, 0);
    }
}

void func_80028FEC(s16 left, s16 right, s16 top, s16 bottom, u8 direction)
{
    struct StageObjectRecord* start;
    struct StageObjectRecord* record;

    if ((u8)engine_obj.stage >= 13 || (u8)engine_obj.substage >= 2)
        abort();
    start = D_800F43C8[engine_obj.stage][engine_obj.substage];
    record = start;
    while (record->object_type != 0xFF) {
        u8 flags = record->flags;
        s16 scan_left = left;
        s16 scan_right = right;
        s16 scan_top = top;
        s16 scan_bottom = bottom;
        s16 x = record->x;
        s16 y = record->y;

        if (!(flags & 0x81)) {
            if (flags & 0x70) {
                u16 margin = D_800F4334.margins[(flags >> 4) - 1];

                if (direction == 1) {
                    scan_left += margin;
                    scan_right += margin;
                }
                if (direction == 2) {
                    scan_left -= margin;
                    scan_right -= margin;
                }
                if (direction == 3) {
                    scan_top += margin;
                    scan_bottom += margin;
                }
                if (direction == 4) {
                    scan_top -= margin;
                    scan_bottom -= margin;
                }
            }
            if (scan_left < x && x < scan_right && scan_top < y && y < scan_bottom) {
                struct ObjectHeader* object = MakeObject(record->object_type);

                if (object != NULL) {
                    u8 index;

                    object->active = 0x41;
                    object->id = record->id;
                    object->unk2 = record->subtype;
                    object->x_pos.i.hi = x;
                    object->y_pos.i.hi = y;
                    object->backref = record;
                    if (record->object_type == 0) {
                        struct MainObj* main = (struct MainObj*)object;

                        index = (u8)func_8002938C(record->id);
                        main->unk40 = D_801406A8[index] >> 7;
                        main->unk42 = SOME_COORDINATE_CONVERSION(index);
                        main->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[index];
                    }
                    record->flags |= 1;
                }
            }
        }
        record++;
    }
}

void func_80028E24(void)
{
    struct BackgroundObj* bg = &background_objects[0];
    s16 old_x = bg->unk14.i.hi;
    s16 x = bg->x_pos.i.hi;
    s16 old_y = bg->unk18.i.hi;
    s16 y = bg->y_pos.i.hi;

    if (old_x != x) {
        if (old_x < x)
            func_80028FEC(x + 0x150, x + 0x170, y - 0x30, y + 0x120, 1);
        else
            func_80028FEC(x - 0x30, x - 0x10, y - 0x30, y + 0x120, 2);
    }
    if (old_y != y) {
        if (old_y < y)
            func_80028FEC(x - 0x30, x + 0x170, y + 0x100, y + 0x120, 3);
        else
            func_80028FEC(x - 0x30, x + 0x170, y - 0x30, y - 0x10, 4);
    }
}

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
        frame->index = player->animation_step.fields.frame_index;
    } else if (object == (struct VisualObj*)&qux_object) {
        frame->data = qux_object.unk3C;
        frame->texture = qux_object.unk40;
        frame->clut = qux_object.unk42;
        frame->index = qux_object.animation_step.fields.frame_index;
    } else if (PC_OBJECT_IN_ARRAY(object, baz_objects)) {
        struct BazObj* baz = (struct BazObj*)object;

        frame->data = baz->unk3C;
        frame->texture = baz->unk40;
        frame->clut = baz->unk42;
        frame->index = baz->animation_step.fields.frame_index;
    } else if (PC_OBJECT_IN_ARRAY(object, foo_objects) || PC_OBJECT_IN_ARRAY(object, unk_objects)) {
        struct UnkObj* unknown = (struct UnkObj*)object;

        frame->data = unknown->unk3C;
        frame->texture = unknown->unk40;
        frame->clut = unknown->unk42;
        frame->index = unknown->animation_step.fields.frame_index;
    } else if (PC_OBJECT_IN_ARRAY(object, main_objects)) {
        struct MainObj* main = (struct MainObj*)object;

        frame->data = (void*)main->sprite_frames;
        frame->texture = main->unk40;
        frame->clut = main->unk42;
        frame->index = main->animation_step.fields.frame_index;
    } else if (PC_OBJECT_IN_ARRAY(object, shot_objects)) {
        struct ShotObj* shot = (struct ShotObj*)object;

        frame->data = shot->unk3C;
        frame->texture = shot->unk40;
        frame->clut = shot->unk42;
        frame->index = shot->animation_step.fields.frame_index;
    } else if (PC_OBJECT_IN_ARRAY(object, weapon_objects)) {
        struct WeaponObj* weapon = (struct WeaponObj*)object;

        frame->data = weapon->unk3C;
        frame->texture = weapon->unk40;
        frame->clut = weapon->unk42;
        frame->index = weapon->animation_step.fields.frame_index;
    } else if (PC_OBJECT_IN_ARRAY(object, visual_objects)) {
        struct VisualObj* visual = object;

        frame->data = visual->unk3C;
        frame->texture = visual->unk40;
        frame->clut = visual->unk42;
        frame->index = visual->animation_step.fields.frame_index;
    } else if (PC_OBJECT_IN_ARRAY(object, misc_objects)) {
        struct MiscObj* misc = (struct MiscObj*)object;

        frame->data = misc->unk3C;
        frame->texture = misc->unk40;
        frame->clut = misc->unk42;
        frame->index = misc->animation_step.fields.frame_index;
    } else if (PC_OBJECT_IN_ARRAY(object, item_objects)) {
        struct ItemObj* item = (struct ItemObj*)object;

        frame->data = (void*)item->sprite_frames;
        frame->texture = item->unk40;
        frame->clut = item->unk42;
        frame->index = item->animation_step.fields.frame_index;
    } else {
        return 0;
    }

    if (frame->data != NULL && pc_archive_slots[0] != NULL && ((uintptr_t)frame->data >> 32) != ((uintptr_t)pc_archive_slots[0] >> 32)) {
        frame->data = (void*)(((uintptr_t)pc_archive_slots[0] & ~(uintptr_t)UINT32_MAX) | ((uintptr_t)frame->data & UINT32_MAX));
    }

    return frame->data != NULL;
}

#undef PC_OBJECT_IN_ARRAY

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

    if (object->bg_offset < 0) {
        origin_x = object->x_pos.i.hi;
        origin_y = object->y_pos.i.hi;
    } else {
        struct BackgroundObj* background = &background_objects[object->bg_offset];

        origin_x = object->x_pos.i.hi - background->x_pos.i.hi;
        origin_y = object->y_pos.i.hi - background->y_pos.i.hi;
    }

    primitive = SP_PRIM_CURSOR;
    draw_mode = SP_DRAW_MODE_CURSOR;
    first_draw_mode = (P_TAG*)draw_mode;
    frame_header = (u16*)((u8*)frame.data + frame.index * 4);
    frame_count = frame_header[0];
    frame_data = (u8*)frame.data + frame_header[1] * 4;
    flipped = object->unk15;
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
        if (object->active & 0x40) {
            u32 index = texture_index & 0xFFFF;

            texture_index = ((index / 176) << 8) + index % 176 + 0x600;
        }
        if (object->active & 0x20) {
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
            setSemiTrans(primitive, object->active & 0x10);
            primitive->clut = primitive_clut;
            primitive->x0 = x0;
            primitive->y0 = y0;
            primitive->u0 = texture_index * 16;
            primitive->v0 = v0;
        } else {
            if (!(flags & 0x80)) {
                setPolyFT4(primitive);
                setShadeTex(primitive, 1);
                setSemiTrans(primitive, object->active & 0x10);
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
                    object->active & 0x10 ? 0x2F : 0x2D);
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
        u32 group = (object->unk16 >> 4) & 3;
        u32 priority = object->unk16 & 7;

        setaddr(D_8013BC40[buffer][group][priority], first_draw_mode);
        D_8013BC40[buffer][group][priority] = (P_TAG*)(primitive - 1);
    }

    SP_PRIM_CURSOR = primitive;
    SP_DRAW_MODE_CURSOR = draw_mode;
}

void func_8002588C(struct PlayerObj* arg0, s32 part, s32 clut)
{
    POLY_FT4* primitive;
    DR_TPAGE* draw_mode;
    P_TAG* first_draw_mode;
    P_TAG** tail;
    u8* table;
    u8* frame_data;
    u16* frame_header;
    s32 frame_count;
    s32 origin_x;
    s32 origin_y;
    u8 flipped;
    u16 texture;

    if (arg0->bg_offset < 0) {
        origin_x = arg0->x_pos.i.hi;
        origin_y = arg0->y_pos.i.hi;
    } else {
        struct BackgroundObj* background = &background_objects[arg0->bg_offset];

        origin_x = (u16)(arg0->x_pos.i.hi - background->x_pos.i.hi);
        origin_y = (u16)(arg0->y_pos.i.hi - background->y_pos.i.hi);
    }
    origin_x = (s16)origin_x;
    origin_y = (s16)origin_y;

    primitive = SP_PRIM_CURSOR;
    draw_mode = SP_DRAW_MODE_CURSOR;
    first_draw_mode = (P_TAG*)draw_mode;
    table = (u8*)SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, part + 5);
    frame_header = (u16*)(table + arg0->animation_step.fields.frame_index * 4);
    frame_count = frame_header[0];
    frame_data = table + frame_header[1] * 4;
    flipped = arg0->unk15;
    texture = arg0->unk40;

    if (frame_count == 0)
        return;

    while (frame_count-- != 0) {
        u8 flags = frame_data[0];
        s32 x0 = (s8)frame_data[2];
        s32 x1;
        s32 y0;
        s32 y1;
        u32 texture_index;
        u16 primitive_clut;
        s32 v0;

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
        primitive_clut = clut + ((flags & 0xC) >> 2);
        texture_index = texture + (frame_data[1] | ((flags & 3) << 8));
        v0 = texture_index & 0xF0;

        if (((flags & 0x40) ^ flipped) == 0) {
            setlen(primitive, 3);
            setcode(primitive, arg0->active & 0x10 ? 0x7F : 0x7D);
            primitive->clut = primitive_clut;
            primitive->x0 = x0;
            primitive->y0 = y0;
            primitive->u0 = texture_index * 16;
            primitive->v0 = v0;
            draw_mode->code[0] = ((texture_index & 0xFFFF) >> 8) | 0xE1000020;
        } else {
            s32 u0 = texture_index * 16 - 1;
            s32 u1 = texture_index * 16 | 0xF;
            s32 v1 = v0 + 16;

            setlen(primitive, 9);
            setcode(primitive, arg0->active & 0x10 ? 0x2F : 0x2D);
            primitive->tpage = ((texture_index & 0xFFFF) >> 8) | 0x20;
            primitive->clut = primitive_clut;
            if ((u8)u0 == 0xFF) {
                u0 = texture_index * 16;
                x1--;
            }
            if ((u8)v1 == 0) {
                v1 = v0 | 0xF;
                y1--;
            }
            setXY4(primitive, x0, y0, x1, y0, x0, y1, x1, y1);
            setUV4(primitive, u1, v0, u0, v0, u1, v1, u0, v1);
            draw_mode->code[0] = 0xE1000020;
        }

        setlen(draw_mode, 1);
        setaddr(draw_mode, primitive);
        setaddr(primitive, draw_mode + 1);
        primitive++;
        draw_mode++;
        frame_data += 4;
    }

    SP_PRIM_CURSOR = primitive;
    tail = &((P_TAG**)D_8013BC40[SP_DRAW_BUFFER])[(arg0->unk16 >> 4) * 8 + (arg0->unk16 & 0xF)];
    setaddr(*tail, first_draw_mode);
    *tail = (P_TAG*)(primitive - 1);
    SP_DRAW_MODE_CURSOR = draw_mode;
}

void func_80025188(s32 slot, u8 index)
{
    const u8* archive = (const u8*)SP_SPRITE_FRAMES;
    const u8* table;
    const u8* pieces;
    u16 count;

    if ((u32)slot >= COUNT(D_800F30F4) || archive == NULL)
        return;
    table = archive + *(const s32*)(archive + 4);
    count = *(const u16*)(table + (u32)index * 4);
    pieces = table + *(const u16*)(table + (u32)index * 4 + 2) * 4;
    while (count-- != 0 && SP_SPRITE_COUNT < 1000) {
        SPRT_16* sprite = SP_BG_PRIM_CURSOR;
        DR_TPAGE* mode = SP_OT_CURSOR;
        u8 flags = pieces[0];
        u16 texture = pieces[1] | ((flags & 3) << 8);
        s32 texture_index = texture % 80 + ((texture / 80) << 8);
        u16 clut = D_800F30F4[slot].clut + ((flags & 0xC) >> 2);

        setSprt16(sprite);
        sprite->code |= 1;
        setXY0(sprite, D_800F30F4[slot].x + (s8)pieces[2],
            D_800F30F4[slot].y + (s8)pieces[3]);
        setUV0(sprite, (u8)((texture_index + 0x5B0) << 4),
            (u8)((texture_index + 0x5B0) & 0xF0));
        sprite->clut = clut;
        setlen(mode, 1);
        mode->code[0] = 0xE1000000 | ((texture_index + 0x5B0) >> 8);
        addPrim(&cur_draw_info->ordering_table.unk3, sprite);
        addPrim(&cur_draw_info->ordering_table.unk3, mode);
        SP_BG_PRIM_CURSOR = sprite + 1;
        SP_OT_CURSOR = mode + 1;
        SP_SPRITE_COUNT++;
        pieces += 4;
    }
}

void func_800253F0(struct MainObj* player, s32 gauge)
{
    s8 value = HP_VALUE(player->hp);
    s8 target = gauge == 0 ? engine_obj.max_hp : 0x30;
    s16 x = D_800F3124[gauge].x;
    u16 bottom = D_800F3124[gauge].bottom;

    func_80025588(x, x + 5, bottom - value, bottom, value < target / 3);
    if (value == player->unk5D)
        return;
    if (player->unk5D < value) {
        player->unk5D = value;
        return;
    }
    if (HP_DAMAGE_FLAG(player->hp))
        player->drain_hold_timer = 0x10;
    func_80025588(x, x + 5, bottom - (s8)player->unk5D, bottom - value, 2);
    if (player->drain_hold_timer != 0) {
        player->drain_hold_timer--;
        return;
    }
    if (!(main_bss_state.frame_counter & 3))
        player->unk5D--;
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

    if (mmx4_pc_hide_background)
        return;

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

void func_800270F8(s32 x, s32 y, s32 tile_x, s32 tile_y)
{
    SPRT_16* sprite = SP_BG_PRIM_CURSOR;
    u32 row, column;

    for (row = 0; row < SP_BG_BLOCK_HEIGHT; row++) {
        for (column = 0; column < SP_BG_BLOCK_WIDTH; column++) {
            u32 attributes = SP_BG_TILE_ATTRS[SP_BG_BLOCK * 256
                + (tile_y + row) * 16 + tile_x + column];
            u8 page = attributes >> 8;

            if (page != 0) {
                u16 bucket = page - 0x15;
                P_TAG* tail = background_tails[SP_DRAW_BUFFER][SP_CUR_BG_INDEX][bucket];

                setXY0(sprite, x + column * 16, y + row * 16);
                setUV0(sprite, (attributes & 15) * 16, attributes & 0xF0);
                sprite->clut = attributes >> 16;
                if (tail == NULL) {
                    background_heads[SP_DRAW_BUFFER][SP_CUR_BG_INDEX][bucket] = (P_TAG*)sprite;
                } else {
                    setaddr(tail, sprite);
                }
                background_tails[SP_DRAW_BUFFER][SP_CUR_BG_INDEX][bucket] = (P_TAG*)sprite;
                sprite++;
            }
        }
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

#define MAIN_37_U8(object, offset) (((u8*)&(object)->ext.main_37)[(offset)-0x80])
#define MAIN_37_S16(object, offset) (*(s16*)&MAIN_37_U8(object, offset))

static void main_37_rumble(struct MainObj* arg0)
{
    if (--MAIN_37_U8(arg0, 0x8D) == 0) {
        func_8001540C(2, 0x59, arg0);
        MAIN_37_U8(arg0, 0x8D) = 0x1E;
    }
}

static void main_37_debris(struct MainObj* arg0)
{
    if ((arg0->unk7E & 3) == 0) {
        spawn_owner_debris(1, &rocket_spiker_exhaust_variants[MAIN_37_U8(arg0, 0x8C)], arg0, 0x7988,
            arg0->unk15 != 0 ? 0x200000 : -0x200000, 0);
        if (++MAIN_37_U8(arg0, 0x8C) == 0xA)
            MAIN_37_U8(arg0, 0x8C) = 0;
    }
    if ((++arg0->unk7E & 7) == 0) {
        func_800B10E4(0x11, (s16)(MAIN_37_S16(arg0, 0x84) + 0x10),
            (s16)(MAIN_37_S16(arg0, 0x86) + 0x10), (s16)(MAIN_37_S16(arg0, 0x84) + 0x20),
            (s16)(MAIN_37_S16(arg0, 0x86) + 0x30), 1);
    }
}

void func_80033108(struct PlayerObj* arg0)
{
    if (engine_obj.unkF != 0) {
        player_start_stage_clear(arg0);
        return;
    }
    arg0->x_vel.val = arg0->animation_step.fields.event == 0 ? 0x8000 : 0x20000;
    if (arg0->unk15 == 0)
        arg0->x_vel.val = -arg0->x_vel.val;
    move_object(MOVING_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->script_facing == 0)
        player_script_walk_to_mark(arg0);
}

static s32 shot_33_touches_floor(struct ShotObj* arg0, s32 dx_extra, s32 dy_extra)
{
    const struct Unk_unk68* bounds = arg0->unk68;

    return func_8002D724((struct PlayerObj*)arg0,
               (s16)(arg0->x_pos.i.hi + bounds->unk0 + dx_extra),
               (s16)(arg0->y_pos.i.hi + bounds->unk1 + dy_extra))
        != 0;
}

static void shot_33_release(struct ShotObj* arg0, u8* effect)
{
    arg0->unk84.effect->ext.effect_33.timer = 0xB4;
    spawn_debris(5, effect, arg0);
    arg0->state = 8;
}

static void main_48_face_toward(struct MainObj* arg0, s32 initial_face)
{
    s8 direction = SP_CUR_MAIN_OBJ->ext.main_48.collision_result;
    s32 animation = -1;

    switch ((u32)(direction & 0xFE)) {
    case 0:
        arg0->unk15 = 0x40;
        if (!initial_face)
            animation = 1;
        break;
    case 2:
    case 4:
    case 6:
        arg0->unk15 = 0x40;
        /* fallthrough */
    case 10:
    case 12:
    case 14:
        if (direction >= 0xA)
            arg0->unk15 = 0;
        animation = 4;
        break;
    case 8:
        animation = 2;
        break;
    case 16:
        arg0->unk15 = 0;
        if (!initial_face)
            animation = 1;
        break;
    case 18:
    case 20:
    case 22:
        arg0->unk15 = 0;
        /* fallthrough */
    case 26:
    case 28:
    case 30:
        if (direction >= 0x1A)
            arg0->unk15 = 0x40;
        animation = 5;
        break;
    case 24:
        animation = 3;
        break;
    }
    if (animation >= 0)
        set_animation(arg0, animation);
    arg0->unk6++;
}

static s32 main_48_direction_pair(s8 direction, u8 facing)
{
    switch (direction & 0xFE) {
    case 2:
    case 4:
    case 6:
        return 3;
    case 8:
        return 4;
    case 10:
    case 12:
    case 14:
        return 2;
    case 18:
    case 20:
    case 22:
        return 6;
    case 24:
        return 5;
    case 26:
    case 28:
    case 30:
        return 7;
    default:
        return (facing & 0x40) ? 1 : 0;
    }
}

static int misc_32_cancelled(s8 mode)
{
    return (controller_input.pressed & PAD_SELECTION_ALT) || ((controller_input.pressed & 0x800) && game_info.unk0 == mode);
}

#define BAR_BYTES(obj) ((u8*)(obj))
extern u8 D_8013B818[0x10];

void func_800304E4(struct BarObj* arg0)
{
    u8* bytes = BAR_BYTES(arg0);
    s32 original = (u8)arg0->unk14;
    s32 cursor;

    switch (controller_input.pressed) {
    case 0x800:
        arg0->state = 2;
        arg0->unk5 = 0;
        break;
    case PAD_CONFIRM:
        arg0->unk28 = 0;
        arg0->unk2C = 0;
        switch (arg0->unk14) {
        case 10:
            arg0->unk5 = 3;
            if (TANK_VALUE(engine_obj.sub_tanks[0]) == 0x20)
                arg0->unk28 = 1;
            break;
        case 11:
            arg0->unk5 = 3;
            if (TANK_VALUE(engine_obj.sub_tanks[1]) == 0x20)
                arg0->unk28 = 1;
            break;
        case 12:
            arg0->unk5 = 4;
            if (TANK_VALUE(engine_obj.sub_tanks[2]) == 0x20)
                arg0->unk2C = 1;
            break;
        }
        break;
    case 0x1000:
        if (g_Player.unk2 != 0 || arg0->unk2 != 0)
            break;
        cursor = 9;
        while ((s8)cursor != 0 && bytes[0x16 + (s8)cursor] == 0)
            cursor--;
        arg0->unk5 = 0;
        arg0->unk14 = cursor;
        break;
    case 0x2000:
        cursor = original;
        for (;;) {
            cursor++;
            if ((s8)cursor >= 0xD) {
                if (bytes[0x16 + (s8)cursor] == 0)
                    cursor++;
                arg0->unk5 = 2;
                break;
            }
            if (bytes[0x16 + (s8)cursor] != 0)
                break;
        }
        arg0->unk14 = cursor;
        break;
    case 0x8000:
        cursor = original;
        for (;;) {
            cursor--;
            if ((s8)cursor < 10) {
                cursor = original;
                break;
            }
            if (bytes[0x16 + (s8)cursor] != 0)
                break;
        }
        arg0->unk14 = cursor;
        break;
    }
    if (arg0->unk14 != (s8)original)
        func_8001540C(0, 0xC, 0);
}

void func_80030728(struct BarObj* arg0)
{
    u8* bytes = BAR_BYTES(arg0);
    s32 original = (u8)arg0->unk14;
    s32 cursor;

    if (controller_input.pressed & 0x800) {
        arg0->state = 2;
        arg0->unk5 = 0;
        goto done;
    }
    switch (controller_input.pressed) {
    case PAD_CONFIRM:
        if ((s8)original == 0xD) {
            arg0->state = 2;
            arg0->unk5 = 0;
            arg0->unk30 = 1;
        } else {
            arg0->unk5 = 5;
            arg0->unk6 = 0;
            func_80023D90();
        }
        func_8001540C(0, 0x22, 0);
        break;
    case 0x1000:
        cursor = original;
        if (g_Player.unk2 != 0 || arg0->unk2 != 0) {
            cursor--;
            if ((s8)cursor < 0xD)
                cursor = 0xD;
            if (bytes[0x16 + (s8)cursor] != 0)
                arg0->unk14 = cursor;
            break;
        }
        for (;;) {
            cursor--;
            if ((s8)cursor < 0xD) {
                cursor = 9;
                while ((s8)cursor != 0 && bytes[0x16 + (s8)cursor] == 0)
                    cursor--;
                arg0->unk5 = 0;
                break;
            }
            if (arg0->unk14 == (s8)cursor || bytes[0x16 + (s8)cursor] != 0)
                break;
        }
        arg0->unk14 = cursor;
        break;
    case 0x4000:
        cursor = original;
        for (;;) {
            cursor++;
            if ((s8)cursor >= 0xF) {
                cursor = 0xE;
                break;
            }
            if (arg0->unk14 == (s8)cursor || bytes[0x16 + (s8)cursor] != 0)
                break;
        }
        arg0->unk14 = cursor;
        break;
    case 0x8000:
        cursor = 0xC;
        if (g_Player.unk2 != 0 || arg0->unk2 != 0) {
            for (;;) {
                if ((s8)cursor == 0 || bytes[0x16 + (s8)cursor] != 0) {
                    arg0->unk14 = cursor;
                    arg0->unk5 = 1;
                    break;
                }
                cursor--;
                if ((s8)cursor < 10)
                    break;
            }
            break;
        }
        while ((s8)cursor != 0 && bytes[0x16 + (s8)cursor] == 0)
            cursor--;
        arg0->unk14 = cursor;
        arg0->unk5 = (s8)cursor < 10 ? 0 : 1;
        break;
    }
done:
    if (arg0->unk14 != (s8)original)
        func_8001540C(0, 0xC, 0);
}

static void bar_merge_sub_tanks(void)
{
    s8 second = engine_obj.sub_tanks[1];

    if (second >= 0)
        return;
    engine_obj.sub_tanks[0] = second;
    engine_obj.sub_tanks[1] = TANK_DRAINED(second);
}

void func_80030A2C(struct BarObj* arg0)
{
    s32 frame = main_bss_state.frame_counter;
    u32 tank;
    u8 energy;
    u8 health;
    u8 player_health;

    if (frame & 1)
        return;
    tank = arg0->unk14 != 10;
    if (arg0->unk28 != 0) {
        energy = TANK_VALUE(engine_obj.sub_tanks[tank]);
        if (energy != 0) {
            engine_obj.sub_tanks[tank] = (energy - 1) | 0x80;
            health = HP_VALUE(g_Player.hp) + 1;
            if (engine_obj.max_hp < (s8)health)
                health = engine_obj.max_hp;
            g_Player.hp = health;
            if ((main_bss_state.frame_counter & 3) == 0)
                func_8001540C(0, 0x17, 0);
            return;
        }
        if (g_Player.hp != engine_obj.max_hp) {
            health = HP_VALUE(g_Player.hp) + 1;
            if (engine_obj.max_hp < (s8)health)
                health = engine_obj.max_hp;
            g_Player.hp = health;
            if ((frame & 3) == 0)
                func_8001540C(0, 0x17, 0);
            return;
        }
        arg0->unk5 = 1;
        arg0->unk28 = 0;
        if (tank == 0)
            bar_merge_sub_tanks();
        return;
    }
    energy = TANK_VALUE(engine_obj.sub_tanks[tank]);
    if (energy == 0) {
        arg0->unk5 = 1;
        if (tank == 0)
            bar_merge_sub_tanks();
        return;
    }
    engine_obj.sub_tanks[tank] = (energy - 1) | 0x80;
    player_health = g_Player.hp;
    health = HP_VALUE(player_health) + 1;
    if (engine_obj.max_hp < (s8)health)
        health = engine_obj.max_hp;
    g_Player.hp = health | HP_DAMAGE_FLAG(player_health);
    if ((main_bss_state.frame_counter & 3) == 0)
        func_8001540C(0, 0x17, 0);
}

void func_80030C54(struct BarObj* arg0)
{
    u32 i;
    s32 refilled = 0;
    u8 energy;

    if (main_bss_state.frame_counter & 1)
        return;
    if (arg0->unk2C != 0) {
        for (i = 0; i < 9; i++) {
            if (g_Player.weapon_energy[i] < 0x30) {
                g_Player.weapon_energy[i]++;
                refilled = 1;
            } else {
                g_Player.weapon_energy[i] = 0x30;
            }
        }
        if (refilled == 0) {
            energy = TANK_VALUE(engine_obj.sub_tanks[2]);
            if (energy != 0) {
                engine_obj.sub_tanks[2] = energy - 1;
            } else {
                arg0->unk5 = 1;
                arg0->unk2C = 0;
            }
            return;
        }
    } else {
        if (TANK_VALUE(engine_obj.sub_tanks[2]) == 0) {
            arg0->unk5 = 1;
            return;
        }
        for (i = 0; i < 9; i++) {
            if (g_Player.weapon_energy[i] < 0x30 && (s8)(g_Player.weapon_energy[i] + 1) < 0x30) {
                g_Player.weapon_energy[i]++;
                refilled = 1;
            } else {
                g_Player.weapon_energy[i] = 0x30;
            }
        }
        if (refilled == 0) {
            arg0->unk5 = 1;
            return;
        }
    }
    energy = TANK_VALUE(engine_obj.sub_tanks[2]);
    engine_obj.sub_tanks[2] = energy != 0 ? energy - 1 : energy;
    if ((main_bss_state.frame_counter & 3) == 0)
        func_8001540C(0, 0x17, 0);
}

void player_cancel_released_charge(void);

void func_80031064(struct BarObj* arg0)
{
    if (arg0->unk30 == 0) {
        if (g_Player.unk2 == 0) {
            player_cancel_released_charge();
            if ((s8)D_8013B818[0] != g_Player.weapon) {
                player_reset_charge(&g_Player);
                g_Player.stock_charge = 0;
            }
            player_update_shot_types(&g_Player);
            if ((s8)D_8013B818[0] != g_Player.weapon)
                player_equip_weapon(&g_Player);
        }
        func_80021158();
        func_800129A4(8);
    }
    arg0->unk5 = 3;
}

static const u16* pause_screen_tiles;
static SPRT_16* pause_screen_sprites;
static DR_TPAGE pause_screen_page[2];

void func_80017268(s16 x_start)
{
    SPRT_16* sprite = pause_screen_sprites;
    u32 row;
    u32 column;
    s16 x;
    s16 y = 0;
    u16 tile;

    for (row = 0; row < 16; row++, y += 16) {
        x = x_start;
        for (column = 0; column < 16; column++, x += 16) {
            tile = *pause_screen_tiles++;
            if (x >= 0x140)
                continue;
            sprite->clut = (tile >> 12) | 0x7900;
            sprite->u0 = (tile & 0xF) << 4;
            sprite->v0 = tile & 0xF0;
            sprite->x0 = x;
            sprite->y0 = y;
            sprite->code &= 0xFD;
            setaddr(sprite, sprite + 1);
            sprite++;
        }
    }
    pause_screen_sprites = sprite;
}

void func_80017100(void)
{
    DR_TPAGE* page = &pause_screen_page[SP_DRAW_BUFFER];

    pause_screen_tiles = (const u16*)SP_ARC_34;
    pause_screen_sprites = D_8015D9D0[SP_DRAW_BUFFER].sprites;
    setlen(page, 1);
    page->code[0] = (GetGraphType() == 1 || GetGraphType() == 2) ? 0xE100002D : 0xE100001D;
    setaddr(page, pause_screen_sprites);
    func_80017268(0);
    func_80017268(0x100);
    setaddr(pause_screen_sprites - 1, getaddr(&cur_draw_info->ordering_table.ui));
    setaddr(&cur_draw_info->ordering_table.ui, page);
}

extern struct HudLayoutData {
    s16 x;
    s16 y;
    u8 tile;
    u8 character;
    u8 clut;
    u8 alternate_clut;
} D_800F1AD8[38];

extern s16 D_800F1C08[2];

static struct HudLayoutData pause_menu_layout(u8 index)
{
    struct HudLayoutData layout;
    const u8* tail = (const u8*)&g_BootTransitionDataRegion;

    if (index < COUNT(D_800F1AD8))
        return D_800F1AD8[index];
    layout.x = D_800F1C08[0];
    layout.y = D_800F1C08[1];
    layout.tile = tail[0];
    layout.character = tail[1];
    layout.clut = tail[2];
    layout.alternate_clut = tail[3];
    return layout;
}

static u16 pause_menu_clut(u8 value)
{
    return (value & 0xF) | (((value >> 4) + 0x1E0) << 6);
}

void func_800175AC(u8 index)
{
    struct HudLayoutData entry = pause_menu_layout(index);
    struct HudLayoutData* layout = &entry;
    const u8* archive = SP_TITLE_FRAMES;
    const u16* frame;
    const u8* pieces;
    POLY_FT4* slot = SP_PRIM_CURSOR;
    DR_TPAGE* page = SP_DRAW_MODE_CURSOR;
    DR_TPAGE* first_page = page;
    SPRT_16* sprite = NULL;
    u32 count;
    s16 x = layout->x;
    s16 y = layout->y;
    u16 clut = 0;
    u16 texture;
    u32 buffer;

    if (index == 0x20) {
        y = 0xD8;
        x = ((s8)engine_obj.max_hp << 1) + 0x80;
    }
    if (index == 0x1F)
        frame = (const u16*)(archive + (layout->tile + engine_obj.player_lives) * 4);
    else
        frame = (const u16*)(archive + layout->tile * 4);
    if (index == 0x26 && bar_object.options.fields.unk25 != 0)
        frame = (const u16*)(archive + layout->tile * 4 + 0x28);
    count = frame[0];
    pieces = archive + frame[1] * 4;
    if (bar_object.unk14 == layout->character) {
        clut = pause_menu_clut((main_bss_state.frame_counter & 0x10) ? layout->alternate_clut : layout->clut);
    } else if (engine_obj.cur_character == CHARACTER_X) {
        clut = pause_menu_clut(layout->clut);
        if (g_Player.weapon + 1 == layout->character || (g_Player.weapon == 0 && layout->character == 0))
            clut = pause_menu_clut(layout->alternate_clut);
    } else {
        clut = pause_menu_clut(index < 0x21 ? layout->alternate_clut : layout->clut);
    }
    if (engine_obj.cur_character == CHARACTER_X && layout->character == 1)
        clut = pause_menu_clut(g_Player.weapon_energy[0] < 0x30 ? layout->clut : layout->alternate_clut);
    if (count == 0)
        return;
    while (count-- != 0) {
        sprite = (SPRT_16*)slot;
        setSprt16(sprite);
        setShadeTex(sprite, 1);
        sprite->x0 = (s8)pieces[2] + x;
        sprite->y0 = y + (s8)pieces[3];
        sprite->clut = clut + ((pieces[0] & 0xC) >> 2);
        texture = 0x1D60 + (pieces[1] | ((pieces[0] & 3) << 8));
        sprite->u0 = texture << 4;
        sprite->v0 = texture & 0xF0;
        setlen(page, 1);
        page->code[0] = 0xE1000000 | 0x20 | (texture >> 8);
        setaddr(page, sprite);
        setaddr(sprite, page + 1);
        page++;
        slot++;
        pieces += 4;
    }
    SP_PRIM_CURSOR = slot;
    SP_DRAW_MODE_CURSOR = page;
    buffer = SP_DRAW_BUFFER;
    setaddr(D_8013BC40[buffer][0][5], first_page);
    D_8013BC40[buffer][0][5] = (P_TAG*)sprite;
}

extern s16 D_800F1C18[13][9];
extern u8 D_800F1D04[];

static const s16* pause_bar_geometry(u32 index)
{
    return index < 13 ? D_800F1C18[index] : (const s16*)D_800F1D04;
}

void func_800179BC(void)
{
    const s16* row;
    POLY_F4* poly;
    DR_TPAGE* page;
    u32 buffer;
    u32 i;
    u8 flag;
    s8 amount;

    for (i = 0; i < 0xE; i++) {
        poly = SP_PRIM_CURSOR;
        page = SP_DRAW_MODE_CURSOR;
        setPolyF4(poly);
        flag = ((u8*)&bar_object)[0x16 + i];
        if (flag != 0 ? (i != 0 && engine_obj.cur_character != CHARACTER_X && i < 9) : i < 0xD)
            continue;
        row = pause_bar_geometry(i);
        poly->x0 = row[0];
        poly->y0 = row[1];
        poly->x1 = row[2];
        poly->y1 = row[3];
        poly->x2 = row[4] - 1;
        poly->y2 = row[5];
        poly->x3 = row[6];
        poly->y3 = row[7];
        if (i < 10) {
            if (i >= 2 || (i == 0) != (engine_obj.cur_character == CHARACTER_X)) {
                amount = g_Player.weapon_energy[i < 2 ? 0 : i - 1];
                if (amount != 0) {
                    poly->x1 = row[0] + amount * 2 - 1;
                    poly->x3 = row[4] + amount * 2 - 1;
                } else {
                    poly->x1 = poly->x0;
                    poly->x3 = poly->x2;
                }
            }
        } else if (i == 0xD) {
            if (g_Player.hp > 0) {
                poly->x0 = 0x6E;
                poly->y0 = 0xD2;
                poly->x2 = 0x67;
                poly->y2 = 0xD9;
                poly->y1 = 0xD2;
                poly->x1 = poly->x0 + (s8)g_Player.hp * 2;
                poly->y3 = 0xD9;
                poly->x3 = poly->x2 + (s8)g_Player.hp * 2;
            }
        } else if (i == 0xC) {
            poly->x1 = poly->x0 + (s8)engine_obj.sub_tanks[2];
            poly->x3 = poly->x2 + (s8)engine_obj.sub_tanks[2];
        } else {
            amount = TANK_VALUE(engine_obj.sub_tanks[i - 10]);
            poly->x1 = poly->x0 + amount;
            poly->x3 = poly->x2 + amount;
        }
        setRGB0(poly, 0x29, 0xC6, 0x29);
        setlen(page, 1);
        page->code[0] = 0xE1000000;
        buffer = SP_DRAW_BUFFER;
        setaddr(D_8013BC40[buffer][0][5], page);
        setaddr(page, poly);
        D_8013BC40[buffer][0][5] = (P_TAG*)poly;
        SP_DRAW_MODE_CURSOR = page + 1;
        SP_PRIM_CURSOR = (POLY_FT4*)poly + 1;
    }
}

#define M54_81(o) ((o)->ext.main_54.powered_up)

static void main54_spawn_trail(struct MainObj* arg0, u8 layer, u8 frame_offset)
{
    struct MiscObj* misc = find_free_misc_obj();

    if (misc == NULL)
        return;
    misc->active = 0x41;
    misc->id = 0x1A;
    misc->unk2 = 1;
    misc->unk16 = layer;
    misc->unk40 = arg0->unk40;
    misc->unk42 = arg0->unk42 & 0x7FFF;
    misc->animation_table = (void*)arg0->animation_table;
    misc->unk3C = (void*)arg0->sprite_frames;
    misc->bg_offset = arg0->bg_offset;
    misc->x_pos.val = arg0->x_pos.val;
    misc->y_pos.val = arg0->y_pos.val;
    misc->unk15 = arg0->unk15;
    misc->ext.misc_26.timer = 0x1E;
    misc->ext.misc_26.owner = arg0;
    misc->state = 0;
    misc->animation_step.fields.frame_index = arg0->animation_step.fields.frame_index + frame_offset;
}

static void main54_trails(struct MainObj* arg0)
{
    if (--arg0->ext.main_54.afterimage_timer != 0)
        return;
    main54_spawn_trail(arg0, 0x21, 0);
    if (M54_81(arg0) != 0)
        main54_spawn_trail(arg0, 0x20, 0x3C);
    arg0->ext.main_54.afterimage_timer = 0xA;
}

extern union AnimationStep* cutscene_actor_animations[8];

void func_800D1B44(struct MiscObj* self)
{
    u32 row;
    u32 i;

    if (self->unk2 != 0) {
        self->animation_table = (void*)cutscene_actor_animations;
        self->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, 0);
        self->unk42 = 0x7880;
        self->unk40 = (u16)(D_801406A8[0] >> 7);
        for (row = 0; row < 4; row++) {
            for (i = 0; i < 15; i++)
                SP_PALETTE[0x201 + row * 0x10 + i] = 0x8000;
        }
        need_palette_load |= 1;
        set_animation(self, self->unk2 - 1);
        self->state = 1;
        self->unk16 = 0x10;
    } else {
        self->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, 1);
        self->unk42 = 0x784C;
        self->x_pos.i.hi = 0x88;
        self->y_pos.i.hi = 0x78;
        self->state = 2;
        self->animation_step.fields.frame_index = 0;
        self->unk16 = 0x11;
        self->unk40 = (u16)(D_801406A8[1] >> 7);
    }
    self->bg_offset = -1;
    self->unk15 = 0;
    is_on_screen(BASE_OBJECT(self));
}

static void main68_hit_flicker(struct MainObj* self, const void* idle_collision)
{
    if (self->ext.main_68.flash_timer != 0) {
        if (--self->ext.main_68.flash_timer & 1)
            self->unk42 |= 0x8000;
        else
            self->unk42 &= 0x7FFF;
    } else {
        self->collision_data = idle_collision;
    }
}

static void main68_start_hit_flicker(struct MainObj* self)
{
    if (self->ext.main_68.flash_timer == 0) {
        self->collision_data = D_801060F0;
        self->ext.main_68.flash_timer = 0x40;
    }
}

#include "memcard.h"
extern u8 D_800F1DEC[], D_800F1DFC[], D_800F1E14[], D_800F1E24[], D_800F1E34[];
extern u8 D_800F1E78[], D_800F1E88[];
void func_8001B8B0(s16, s16, u8);
void func_8001C5A8(u8**);
void func_8001C07C(void);
void func_8001BCAC(s16, s16, u8);
void func_8001BE10(s16, s16, u8);

static void save_icon_lifetime(struct MiscObj* obj, u8 mode)
{
    obj->ext.misc_42.unk55 = mode ? 1 : 3;
    obj->ext.misc_42.unk54 = mode ? engine_obj.unk1 : main_bss_state.transition.selection;
}

#include <string.h>

// src/main/1263C.c

void func_80021C14(void);
void func_80021D84(void);
void func_80021CC8(void);
void player_update(void);
void update_weapon_objects(void);
void update_main_objects(void);
void update_shot_objects(void);
void update_visual_objects(void);
void update_item_objects(void);
void update_layer_objects(void);

void func_80021F34(void)
{
    struct ReplayData* replay = (struct ReplayData*)REPLAY_DATA;

    g_Player.input.buttons.previous = g_Player.input.buttons.held;
    if (replay->frame == 0xE10) {
        g_Player.input.buttons.held = 0;
    } else {
        g_Player.input.buttons.held = replay->inputs[replay->frame++];
    }
    g_Player.pressed_input = g_Player.input.buttons.held & (g_Player.input.buttons.held ^ g_Player.input.buttons.previous);
    func_80021C14();
    player_update();
    update_weapon_objects();
    update_main_objects();
    update_shot_objects();
    update_visual_objects();
    update_effect_objects();
    update_item_objects();
    update_misc_objects();
    update_quad_objects();
    func_80028E24();
    CollisionRelated(&g_Player);
    func_80027850();
    func_80027D40();
    func_800281E8();
    update_layer_objects();
    func_8002A484();
    func_80021D84();
    func_80021CC8();
    decompress_player_gfx(GRAPHICS_OBJECT(&g_Player), 0x140, 0);
}

// src/main/1A5BC.c

void func_8002A098(struct GameInfo* info)
{
    u8 index;
    u8 binding = 0xFF;
    u16 old;
    u16 pressed;

    (void)info;
    if (main_bss_state.transition.active != 0)
        return;
    pressed = controller_input.pressed;
    if ((pressed & PADstart) || ((pressed & PAD_CONFIRM) && main_bss_state.transition.selection == 7)) {
        func_8001540C(0, 0x22, NULL);
        func_800129F0(8);
        D_8013B7D0++;
        return;
    }
    if (pressed & PADLup) {
        func_8001540C(0, 0xC, NULL);
        if (main_bss_state.transition.selection == 0)
            main_bss_state.transition.selection = 7;
        else
            main_bss_state.transition.selection--;
        if (main_bss_state.character_mode == 0 && engine_obj.cur_character != 0 && main_bss_state.transition.selection == 6)
            main_bss_state.transition.selection = 4;
    }
    if (pressed & PADLdown) {
        func_8001540C(0, 0xC, NULL);
        if (main_bss_state.transition.selection == 7)
            main_bss_state.transition.selection = 0;
        else
            main_bss_state.transition.selection++;
        if (main_bss_state.character_mode == 0 && engine_obj.cur_character != 0 && main_bss_state.transition.selection == 5)
            main_bss_state.transition.selection = 7;
    }
    for (index = 4; index < 16; index++) {
        if (D_800F44E8[main_bss_state.transition.selection] == (1U << index)) {
            binding = index;
            break;
        }
    }
    if (binding == 0xFF)
        return;
    for (index = 0; index < 8; index++) {
        if (controller_input.pressed == D_800F44F8[index]) {
            func_8001540C(0, 0x22, NULL);
            old = D_800EE430[binding];
            D_800EE430[binding] = D_800F44F8[index];
            for (index = 0; D_800EE430[index] != 0; index++) {
                if (index != binding && D_800EE430[index] == D_800EE430[binding])
                    D_800EE430[index] = old;
            }
            return;
        }
    }
}

// src/main/323C.c

void func_80012D88(const u32* src, u32* dst, u32 count)
{
    u32 a, b, c, d;

    do {
        a = src[0];
        b = src[1];
        c = src[2];
        d = src[3];
        dst[0] = a;
        dst[1] = b;
        dst[2] = c;
        dst[3] = d;
        src += 4;
        dst += 4;
    } while (--count);
}

void func_80012DC0(const u32* src, u32* dst, u32 count)
{
    u32 a, b, c, d, e, f, g, h;

    do {
        a = src[0];
        b = src[1];
        c = src[2];
        d = src[3];
        e = src[4];
        f = src[5];
        g = src[6];
        h = src[7];
        dst[0] = a;
        dst[1] = b;
        dst[2] = c;
        dst[3] = d;
        dst[4] = e;
        dst[5] = f;
        dst[6] = g;
        dst[7] = h;
        src += 8;
        dst += 8;
    } while (--count);
}

// src/main/CB184.c

void func_800DADA0(struct TileEffectRecord* arg0, u16 arg1, u16 arg2, u8 arg3,
    u8 arg4)
{
    u32 x = arg1;
    u32 y = arg2;
    u16 tile = arg0->tiles[arg3];
    u8 block;

    block = (SP_BG_TILEMAP + arg0->layer * layout_size
        + layout_width * (y >> 4))[x >> 4];
    *(u16*)((u8*)SP_BG_TILE_PIXELS + (block << 9) + ((y & 0xF) << 5)
        + ((x & 0xF) * 2))
        = tile;

    if (arg4 != 0) {
        D_801441C8[arg0->layer][arg2 & 0x1F][arg1 & 0x1F] = tile;
    }
}
extern ret_u8 func_8002938C(s32);

// src/main/memcard.c

static const u8 memcard_save_title[21] = {
    0x82, 0x6C, 0x82, 0x64, 0x82, 0x66, 0x82, 0x60, 0x82, 0x6C,
    0x82, 0x60, 0x82, 0x6D, 0x81, 0x40, 0x82, 0x77, 0x82, 0x53, 0
};

s32 func_8001C8F4(u8* buffer, s32 device_num, s32 size)
{
    u8 verification[0x200];
    s32 result;

    buffer[3] = ((u32)size >> 13) + ((size & 0x1FFF) != 0);
    memcpy(buffer + 4, memcard_save_title, sizeof(memcard_save_title));
    result = mmx4_pc_card_write(device_num, buffer, size);
    if (result != 0)
        return result;
    return mmx4_pc_card_read(device_num, verification, sizeof(verification)) == 0 ? 0 : 2;
}

s32 func_8001CB24(u8* buffer, s32 device_num, s32 size)
{
    (void)size;
    return mmx4_pc_card_read(device_num, buffer, 0x800);
}

// src/main/menu.c

void func_8001A498(struct EngineObj* engine)
{
    s32 status;
    memcard_menu.timer--;
    if (memcard_menu.timer != 0)
        return;
    status = func_8001CDE4(memcard_menu.port);
    if (status != 0) {
        engine->unk1 = 11;
        memcard_menu.result = status == 1 ? 1 : 2;
        func_8001B644(status == 1 ? D_800F1DFC : D_800F1E24);
        main_bss_state.transition.selection = 0;
        return;
    }
    status = func_8001CD70(memcard_menu.port);
    if (status == 1) {
        engine->unk1 = 11;
        memcard_menu.result = 1;
        func_8001B644(D_800F1DFC);
        return;
    }
    if (status == 2) {
        reset_objects();
        engine->unk1 = 3;
        engine->unk2 = 0;
        return;
    }
    if (status == 3) {
        reset_objects();
        engine->unk1 = 11;
        memcard_menu.result = 1;
        main_bss_state.transition.selection = 0;
        func_8001B644(D_800F1E24);
        return;
    }
    if (status == 0) {
        func_8001CC5C(memcard_menu.port, (&memcard_files), D_80010058);
        if (memcard_files.total_size == 0x1E000) {
            func_8001CC5C(memcard_menu.port, (&memcard_files), D_8001005C);
            if (memcard_files.count == 0) {
                engine->unk1 = 11;
                memcard_menu.result = 3;
                main_bss_state.transition.selection = 0;
                reset_objects();
                func_8001B644(D_800F1E34);
                return;
            }
        }
    }
    engine->unk1 = 8;
    reset_objects();
    memcard_menu.timer = 5;
    func_8001B718(0x30, (memcard_menu.selection + memcard_menu.port * 3 + 0x1A) & 0xFF, 0xFF);
    func_8001B644(D_800F1E78);
    func_8001B7C0(0xA0, 0x78, 1);
}

void func_8001A710(struct EngineObj* engine)
{
    memcard_menu.timer--;
    if (memcard_menu.timer != 0)
        return;
    func_8001C07C();
    func_8001C4B4(&memcard_menu);
    if (engine->unk1 == 11)
        return;
    engine->unk1 = 9;
    reset_objects();
    func_8001B718(0x30, (memcard_menu.selection + memcard_menu.port * 3 + 0x1A) & 0xFF, 0xFF);
    func_8001B644(D_800F1E88);
    func_8001B7C0(0xA0, 0x78, 1);
    memcard_menu.timer = 0x8C;
}

static void menu_icon_set_lifetime(struct MiscObj* obj, u8 persistent)
{
    obj->ext.misc_42.unk55 = persistent ? 1 : 3;
    obj->ext.misc_42.unk54 = persistent ? engine_obj.unk1 : main_bss_state.transition.selection;
}

void func_8001B7C0(s16 x, s16 y, u8 persistent)
{
    struct MiscObj* obj = find_free_misc_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x2A;
        obj->animation_step.fields.frame_index = 0x2A;
        obj->unk2 = 1;
        menu_icon_set_lifetime(obj, persistent);
        obj->x_pos.i.hi = x;
        obj->y_pos.i.hi = y;
    }
    func_8001BCAC((s16)(x - 0x40), y, persistent);
    func_8001BE10((s16)(x - 0x40), y, persistent);
    func_8001B8B0(x, y, persistent);
}

void func_8001B8B0(s16 x, s16 y, u8 persistent)
{
    s32 i, count = 0;
    struct MiscObj* obj;

    for (i = 0; i < 8; i++) {
        if (!(memcard_menu.slot->unk4 & D_800F1D90.button_lookup[i * 3]))
            continue;
        obj = find_free_misc_obj();
        if (obj == NULL)
            continue;
        obj->active = 0x41;
        obj->id = 0x2A;
        obj->unk2 = 3;
        obj->animation_step.fields.frame_index = D_800F1D90.button_lookup[i * 3 + 1] + ((memcard_menu.slot->character & 1) << 3);
        if (memcard_menu.slot->character == 0) {
            u8 frame = D_800F1D90.button_lookup[i * 3 + 1];
            obj->animation_step.fields.frame_index = frame;
            obj->unk42 = ((0x1E0 + (frame + 12) / 16) << 6) | ((frame + 12) % 16);
        } else {
            u8 frame = D_800F1D90.button_lookup[i * 3 + 2];
            obj->animation_step.fields.frame_index = frame + 8;
            switch (frame) {
            case 0:
            case 1:
                obj->unk42 = 0x7844;
                break;
            case 2:
            case 7:
                obj->unk42 = 0x7845;
                break;
            case 3:
            case 5:
                obj->unk42 = 0x7846;
                break;
            case 4:
            case 6:
                obj->unk42 = 0x7847;
                break;
            }
        }
        menu_icon_set_lifetime(obj, persistent);
        obj->x_pos.i.hi = (s16)(x + count++ * 16 - 0x28);
        obj->y_pos.i.hi = (s16)(y - 0x10);
    }

    count = 0;
    for (i = 0; i < 8; i++) {
        if (!(memcard_menu.slot->unk6 & D_800F1D90.low_button_masks[i]))
            continue;
        obj = find_free_misc_obj();
        if (obj == NULL)
            continue;
        obj->active = 0x41;
        obj->id = 0x2A;
        obj->animation_step.fields.frame_index = 0x13;
        obj->unk42 = 0x784A;
        obj->x_pos.i.hi = (s16)(x + count * 16 - 0x28);
        obj->unk2 = 3;
        obj->y_pos.i.hi = y;
        menu_icon_set_lifetime(obj, persistent);
        count++;
    }

    count = 0;
    for (i = 0; i < 4; i++) {
        u16 mask = i == 3 ? D_800F1D90.sign_bit_mask : D_800F1D90.high_button_masks[i];
        if (!(memcard_menu.slot->unk6 & mask))
            continue;
        obj = find_free_misc_obj();
        if (obj == NULL)
            continue;
        obj->active = 0x41;
        obj->id = 0x2A;
        obj->unk2 = 3;
        if (i < 2) {
            obj->animation_step.fields.frame_index = 0x11;
            obj->unk42 = 0x7848;
        } else if (i == 2) {
            obj->animation_step.fields.frame_index = 0x10;
            obj->unk42 = 0x7848;
        } else {
            obj->animation_step.fields.frame_index = 0x12;
            obj->unk42 = 0x7849;
        }
        obj->x_pos.i.hi = (s16)(x + count * 32 - 0x20);
        obj->y_pos.i.hi = (s16)(y + 0x10);
        menu_icon_set_lifetime(obj, persistent);
        count++;
    }
}

void func_8001BCAC(s16 x, s16 y, u8 persistent)
{
    struct MiscObj* obj = find_free_misc_obj();
    if (obj == NULL)
        return;
    obj->active = 1;
    obj->id = 0x2A;
    obj->unk16 = 4;
    if (memcard_menu.slot->character != 0xFF) {
        obj->unk2 = 2;
        obj->animation_step.fields.frame_index = memcard_menu.slot->character == 0 ? 0x2C : 0x2B;
        obj->unk42 = memcard_menu.slot->unk29 ? (memcard_menu.slot->character == 0 ? 0x784F : 0x784B) : 0x7808;
        obj->x_pos.i.hi = x;
        obj->y_pos.i.hi = y;
    } else {
        obj->animation_step.fields.frame_index = 0x5D;
        obj->x_pos.i.hi = (s16)(x + 0x14);
        obj->y_pos.i.hi = (s16)(y - 8);
        obj->unk2 = 0;
        obj->ext.misc_42.unk56 = -1;
    }
    menu_icon_set_lifetime(obj, persistent);
}

void func_8001BE10(s16 x, s16 y, u8 persistent)
{
    s32 i;
    struct MiscObj* obj;
    if (memcard_menu.slot->character != 0)
        return;
    if (memcard_menu.slot->unk29 == 0) {
        for (i = 0; i < 4; i++) {
            if (!(memcard_menu.slot->unk3 & D_800F1FBC[i]))
                continue;
            obj = find_free_misc_obj();
            if (obj == NULL)
                continue;
            obj->id = 0x2A;
            obj->active = 1;
            obj->unk2 = 2;
            obj->unk16 = 3;
            obj->animation_step.fields.frame_index = i + 0x2D;
            obj->unk42 = D_800F1FBC[i] == 4 && memcard_menu.slot->unk2 == 2 ? 0x780A : 0x7808;
            obj->x_pos.i.hi = x;
            obj->y_pos.i.hi = y;
            menu_icon_set_lifetime(obj, persistent);
        }
    } else if (memcard_menu.slot->unk3 & 0xF) {
        obj = find_free_misc_obj();
        if (obj == NULL)
            return;
        obj->id = 0x2A;
        obj->unk2 = 2;
        obj->animation_step.fields.frame_index = 0x34;
        obj->unk42 = 0x784E;
        obj->active = 1;
        obj->unk16 = 3;
        obj->x_pos.i.hi = x;
        obj->y_pos.i.hi = y;
        menu_icon_set_lifetime(obj, persistent);
    }
}

void func_8001C4B4(struct MemcardMenuState* menu)
{
    u8* buffer = menu->buffer;
    u8 port = menu->port;
    u8* message;
    buffer[0] = 's';
    buffer[1] = 'c';
    buffer[2] = 0x13;
    menu->result = func_8001CDE4(port);
    if (menu->result != 0) {
        engine_obj.unk1 = 11;
        reset_objects();
        message = D_800F1DFC;
    } else {
        func_8001C5A8(&menu->buffer);
        menu->result = func_8001C8F4(buffer, port, 0x2000);
        if (menu->result == 0)
            return;
        engine_obj.unk1 = 11;
        reset_objects();
        message = D_800F1E14;
    }
    main_bss_state.transition.selection = 0;
    func_8001B644(message);
}

void enemy_hit_reaction_shot(struct ShotObj* object)
{
    enemy_hit_reaction(MAIN_OBJECT(object));
}
