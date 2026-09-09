#include "common.h"

#include <libspu.h>

void SelectACharacterUpdate(struct MiscObj*);

extern u16 D_800F1868[18];
extern u8 D_800F164C[4];
extern s16 D_800F1650[2];
extern union MainPaletteData D_800F1660;
extern const u32* D_800F2FD4[];
extern const u32* D_8011AFF0[];
extern struct StageObjectMarginData D_800F4334;
extern s8* D_800F49DC[10];
extern u16 D_800F4A04[10];
extern u8 D_800F2B5C[21][12];
extern struct HudSpriteOrigin D_800F30F4[8];
extern struct PlayerGaugePosition D_800F3124[2];
extern u16 D_800F312C[4];
extern s32 D_8010F678[3];
extern u16 D_80106070[64];
extern u8* D_80141EE8[];
extern u32* D_80137E08;

s32 func_800154E8(s32 arg0, s32 arg1, struct BaseObj* source, u8 pan);
s32 func_800157AC(u8 type, s32 unused, struct BaseObj* source);

s32 func_8002938C(s32 id)
{
    const u8* ids = s_StageMainIds[(u8)engine_obj.stage][(u8)engine_obj.substage];
    s32 index = 0;

    while (ids[index] != 0xFF && ids[index] != (u8)id)
        index++;
    return index;
}

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
    count = (u32*)D_80141EE8[group] - (u32*)D_80141F50[group];
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

s32 func_8002B1E8(struct BaseObj* object, s32 x_margin, s32 y_margin)
{
    s32 x = (u16)object->x_pos.i.hi;
    s32 y = (u16)object->y_pos.i.hi;

    if (object->bg_offset >= 0) {
        x -= (u16)background_objects[object->bg_offset].x_pos.i.hi;
        y -= (u16)background_objects[object->bg_offset].y_pos.i.hi;
    }

    if ((u16)(x + x_margin) >= (u16)(0x140 + 2 * x_margin))
        return 1;
    return (u16)(y + y_margin) >= (u16)(0xF0 + 2 * y_margin);
}

void func_80029A48(void)
{
    static const u16 sequence[] = { 0x20, 0x20, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000 };
    s8* phase = &engine_obj.character_state.fields.secret_code_phase;
    s8* index = &engine_obj.character_state.fields.secret_code_index;
    u16 input = controller_state;
    u16 held = D_80166C08;

    switch (*phase) {
    case 0:
        *index = 0;
        if (input != 0 && input == sequence[0] && held == input) {
            *index = 1;
            *phase = 1;
        }
        break;
    case 1:
        if (input == 0)
            break;
        if (input != sequence[(u8)*index] || held != input) {
            *phase = 0;
            break;
        }
        if (*index == 7)
            (*phase)++;
        (*index)++;
        break;
    case 2:
        if (input == 0)
            break;
        if (input & 0x840) {
            u16 expected = sequence[(u8)*index];

            if ((held & expected) == expected)
                engine_obj.unk37 = 1;
        } else if (input & sequence[(u8)*index]) {
            break;
        }
        *phase = 0;
        break;
    }
}

void func_80029BD8(void)
{
    static const u16 sequence[] = { 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x20 };
    s8* phase = &engine_obj.character_state.fields.secret_code_phase;
    s8* index = &engine_obj.character_state.fields.secret_code_index;
    u16 input = controller_state;
    u16 held = D_80166C08;

    switch (*phase) {
    case 0:
        *index = 0;
        if (input != 0 && input == sequence[0] && held == (input | 8)) {
            *index = 1;
            *phase = 1;
        } else if (input != 0) {
            *phase = 0;
        }
        break;
    case 1:
        if (input == 0)
            break;
        if (input != sequence[(u8)*index] || held != (input | 8)) {
            *phase = 0;
            break;
        }
        if (*index == 5)
            (*phase)++;
        (*index)++;
        break;
    case 2:
        if (held == 0) {
            (*phase)++;
        } else if (input == 0 || !(held & (sequence[(u8)*index - 1] | 8))) {
            *phase = 0;
        }
        break;
    case 3:
        if (input == 0)
            break;
        if (input & 0x840) {
            u16 expected = sequence[(u8)*index];

            if ((held & expected) == expected)
                engine_obj.unk37 = 1;
        } else if (input & sequence[(u8)*index]) {
            break;
        }
        *phase = 0;
        break;
    }
}

static u8 get_stage_tile_attribute(s8 layer, s16 x, s16 y)
{
    s32 block_x = x >> 8;
    s32 block_y = y >> 8;
    u8 block;
    u16 tile;

    if (layer < 0 || layer >= 3 || block_x < 0 || block_y < 0 || block_x >= layout_width || block_y >= layout_height)
        return 0;
    block = SP_BG_TILEMAP[layer * layout_size + block_y * layout_width + block_x];
    if (block == 0)
        return 0;
    tile = SP_BG_TILE_PIXELS[block * 0x100 + ((y & 0xF0) >> 4) * 0x10 + ((x & 0xF0) >> 4)];
    return SP_BG_TILE_ATTRS[tile & 0x3FFF] & 0xFF;
}

u8 func_8002D724(struct PlayerObj* object, s16 x, s16 y)
{
    return get_stage_tile_attribute(object->bg_offset, x, y);
}

u8 func_8002D7E4(struct PlayerObj* object, s16 x, s16 y)
{
    u8 attribute = get_stage_tile_attribute(object->bg_offset, x, y);

    if (attribute == 0)
        return 0;
    object->unk6C = x & 0xF;
    object->unk6E = y & 0xF;
    return attribute;
}

s32 func_8002CC34(struct PlayerObj* object, u8 attribute)
{
    switch (attribute) {
    case 0x38:
    case 0x39:
    case 0x3A:
    case 0x3C:
    case 0x3E:
    case 0x3F:
        D_8013B7DC |= 1;
        D_8013B800 = ~object->unk6C;
        return -1;
    default:
        return 0;
    }
}

s32 func_8002CAF0(struct PlayerObj* object, u8 attribute)
{
    switch (attribute) {
    case 0x38:
    case 0x39:
    case 0x3A:
    case 0x3C:
    case 0x3E:
    case 0x3F:
        D_8013B7DC |= 2;
        D_8013B800 = 0x10 - object->unk6C;
        return -1;
    default:
        return 0;
    }
}

s32 func_8002CD70(struct PlayerObj* object, u8 attribute)
{
    switch (attribute) {
    case 0x38:
    case 0x39:
    case 0x3A:
    case 0x3C:
    case 0x3E:
    case 0x3F:
        D_8013B7DC |= 4;
        D_8013B804 = 0x10 - object->unk6E;
        return -1;
    default:
        return 0;
    }
}

s32 func_8002D490(struct PlayerObj* object)
{
    s16 offset = D_8013B800;
    s16 x;

    if (D_8013B7DC & 1) {
        if (object->unk15)
            x = D_8013B7F0 + offset + D_8013B7E8 + D_8013B7E0 - 1;
        else
            x = D_8013B7F0 + offset - D_8013B7E8 + D_8013B7E0 - 1;
    } else {
        if (object->unk15)
            x = D_8013B7F0 + offset + D_8013B7E8 - D_8013B7E0;
        else
            x = D_8013B7F0 + offset - D_8013B7E8 - D_8013B7E0;
    }
    if (func_8002D5E4(object, x))
        return -1;
    object->x_pos.i.lo = 0;
    object->x_pos.i.hi += offset;
    return 0;
}

void func_8002C9E4(struct PlayerObj* object)
{
    object->x_pos.i.lo = 0;
    object->y_pos.i.lo = 0;
    object->x_pos.i.hi += D_8013B800;
    object->y_pos.i.hi += D_8013B804;
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

    for (i = 0; i < index; i++) {
        if (*entry & 0x8000) {
            channel++;
            entry++;
        }
        entry++;
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

void func_8002217C(u16 message, u8 portrait, u8 delay_only)
{
    struct MiscObj* window;
    u8* window_archive;
    u32 window_frame_offset;
    u16* dialogue_palette;
    u16* messages;

    if (abc_object.unkC != 0) {
        abc_object.unk10 = message | 0x8000;
        if (abc_object.unkC != 0x80) {
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
    D_801397BC = D_801397C0 = D_801397C4 = D_801397C8 = NULL;
    D_801397CC = D_801397D0 = D_801397D4 = NULL;
    if (delay_only) {
        abc_object.unkA = 0x3C;
        abc_object.unkD = 6;
        return;
    }
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
        window->animation_table = D_800F2FD4;
        window->unk40 = 0x1E00;
        window->unk42 = engine_obj.stage == 0xD ? 0x78CF : 0x7846;
        window->bg_offset = -1;
        window->x_pos.i.hi = 0xA0;
        window->y_pos.i.hi = (abc_object.unk4 & 0x800)
            ? (portrait == 0xFF ? 0xB4 : 0xAC)
            : (portrait == 0x80 ? 0x74 : 0x3C);
        window->unk3C = window_archive + window_frame_offset;
        window->unk15 = 0;
        func_80015D60(window, 0);
    }
}

void func_80028690(struct BackgroundObj* bg)
{
    s16 step = (s8)bg->unk47;
    s16 player_x = g_Player.x_pos.i.hi;
    s16 player_y = g_Player.y_pos.i.hi;

    if (bg->unk1E != bg->unk26) {
        s16 next = bg->unk1E;
        if (bg->unk26 >= bg->x_pos.i.hi)
            next = bg->x_pos.i.hi + step;
        else if (player_x - bg->x_pos.i.hi - bg->unk30 >= 5)
            next = bg->x_pos.i.hi - step;
        if ((step >= 0 && next < bg->unk26) || (step < 0 && next > bg->unk26))
            bg->unk1E = next;
        else
            bg->unk1E = bg->unk26;
    }
    if (bg->unk1C != bg->unk24) {
        s16 next = bg->unk1C;
        if (bg->unk24 < bg->x_pos.i.hi)
            next = bg->x_pos.i.hi - step;
        else if (player_x - bg->x_pos.i.hi - bg->unk32 < 4)
            next = bg->x_pos.i.hi + step;
        if ((step >= 0 && next > bg->unk24) || (step < 0 && next < bg->unk24))
            bg->unk1C = next;
        else
            bg->unk1C = bg->unk24;
    }
    if (bg->unk22 != bg->unk2A) {
        s16 next = bg->unk22;
        if (bg->unk2A >= bg->y_pos.i.hi)
            next = bg->y_pos.i.hi + step;
        else if (player_y - bg->y_pos.i.hi - bg->unk2C < 4)
            next = bg->y_pos.i.hi - step;
        if ((step >= 0 && next < bg->unk2A) || (step < 0 && next > bg->unk2A))
            bg->unk22 = next;
        else
            bg->unk22 = bg->unk2A;
    }
    if (bg->unk20 != bg->unk28) {
        s16 next = bg->unk20;
        if (bg->unk28 < bg->y_pos.i.hi)
            next = bg->y_pos.i.hi - step;
        else if (player_y - bg->y_pos.i.hi - bg->unk2E < 4)
            next = bg->y_pos.i.hi + step;
        if ((step >= 0 && next > bg->unk28) || (step < 0 && next < bg->unk28))
            bg->unk20 = next;
        else
            bg->unk20 = bg->unk28;
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
                        main->unk42 = ((index * 4 + 0x18) & 0xF) | (((index + 6) / 4 + 0x1E0) << 6);
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

void func_800B5D04(struct EffectObj* arg0)
{
    const s8* animation;
    u16 destination;

    arg0->active = 1;
    if (engine_obj.stage != 0 || engine_obj.substage != 0)
        abort();
    animation = D_800F49DC[(u8)arg0->unk2];
    arg0->ext.palette_animation.cursor = (s8*)animation;
    if (animation == NULL) {
        func_8002B108(OBJECT_HEADER(arg0));
        return;
    }
    destination = D_800F4A04[(u8)arg0->unk2];
    arg0->ext.palette_animation.destination = (s32*)SP_PALETTE + (destination & 0xFF) * 8;
    arg0->ext.palette_animation.source = SP_ARC_30 + (u8)animation[0] * 8;
    arg0->ext.palette_animation.timer = animation[1];
    arg0->ext.palette_animation.palette_count = destination >> 8;
    func_800B5C60(arg0);
    arg0->state++;
}

s32 func_800D4024(struct QuadObj* arg0)
{
    struct BackgroundObj* bg = &background_objects[arg0->bg_offset];
    s32 x = (u16)arg0->x_pos.i.hi - (u16)bg->x_pos.i.hi;
    s32 y = (u16)arg0->y_pos.i.hi - (u16)bg->y_pos.i.hi;
    u32 half_width = abs((s16)(arg0->unk1C.i.hi - arg0->unk14.i.hi));
    u32 half_height = abs((s16)(arg0->unk30.i.hi - arg0->unk18.i.hi));
    s32 visible = 0;

    if ((u16)(x + half_width) < (u16)(0x140 + half_width * 2) && (u16)(y + half_height) < (u16)(0xF0 + half_height * 2))
        visible = 1;
    x += arg0->unk14.i.hi + (half_width >> 1);
    y += arg0->unk18.i.hi + (half_height >> 1);
    if ((u16)(x + half_width) < (u16)(0x140 + half_width * 2) && (u16)(y + half_height) < (u16)(0xF0 + half_height * 2))
        visible = 1;
    return visible;
}

void func_800D3C58(struct QuadObj* arg0)
{
    const struct SearchLightInit* init = &D_8010F600[(u8)arg0->unk2];
    s16 origin = init->vertices[0];
    s16 span = (s16)(init->vertices[2] - origin);
    s32 x_accum = arg0->runtime.search_light.x_accumulator;
    s32 y_accum = arg0->runtime.search_light.y_accumulator;
    u16 direction = arg0->link.direction;

    if (arg0->runtime.search_light.pause_timer != 0) {
        arg0->runtime.search_light.pause_timer--;
    } else {
        x_accum += arg0->ext.search_light.velocity;
        y_accum += arg0->ext.search_light.vertical_velocity;
        arg0->ext.search_light.velocity += arg0->ext.search_light.acceleration;
        arg0->ext.search_light.vertical_velocity += arg0->ext.search_light.vertical_acceleration;
        arg0->unk14.val += arg0->ext.search_light.velocity;
        arg0->unk1C.val += arg0->ext.search_light.velocity;
        switch (arg0->unk5) {
        case 0:
            if ((!direction && arg0->unk14.i.hi >= (s16)(arg0->runtime.search_light.extent + origin - 0x20)) || (direction && arg0->unk14.i.hi <= (s16)(origin + 0x20 - arg0->runtime.search_light.extent))) {
                arg0->unk5 = 1;
                arg0->ext.search_light.acceleration = direction
                    ? D_8010F678[(u8)arg0->unk2 >> 1]
                    : -D_8010F678[(u8)arg0->unk2 >> 1];
            }
            break;
        case 1:
            if (!direction) {
                if (arg0->ext.search_light.velocity <= 0x7FFF) {
                    arg0->ext.search_light.velocity = 0x8000;
                    arg0->ext.search_light.acceleration = 0;
                }
                if (arg0->unk14.i.hi >= (s16)(origin + arg0->runtime.search_light.extent)) {
                    arg0->unk5 = 2;
                    arg0->ext.search_light.velocity = 0;
                    arg0->ext.search_light.acceleration = 0;
                    arg0->unk14.val = 0;
                    arg0->unk1C.val = 0;
                    arg0->unk14.i.hi = origin + arg0->runtime.search_light.extent;
                    arg0->unk1C.i.hi = span + origin + arg0->runtime.search_light.extent;
                    arg0->runtime.search_light.pause_timer = get_random() & 7;
                    direction ^= 1;
                }
            } else {
                if (arg0->ext.search_light.velocity >= -0x7FFF) {
                    arg0->ext.search_light.velocity = -0x8000;
                    arg0->ext.search_light.acceleration = 0;
                }
                if (arg0->unk14.i.hi <= (s16)(origin - arg0->runtime.search_light.extent)) {
                    arg0->unk5 = 2;
                    arg0->ext.search_light.velocity = 0;
                    arg0->ext.search_light.acceleration = 0;
                    arg0->unk14.val = 0;
                    arg0->unk1C.val = 0;
                    arg0->unk14.i.hi = origin - arg0->runtime.search_light.extent;
                    arg0->unk1C.i.hi = span + origin - arg0->runtime.search_light.extent;
                    arg0->runtime.search_light.pause_timer = get_random() & 7;
                    direction ^= 1;
                }
            }
            break;
        case 2:
            arg0->ext.search_light.acceleration = direction
                ? -D_8010F678[(u8)arg0->unk2 >> 1]
                : D_8010F678[(u8)arg0->unk2 >> 1];
            arg0->unk5 = 3;
            arg0->runtime.search_light.base_speed = -arg0->runtime.search_light.base_speed;
            break;
        case 3:
            if ((!direction && arg0->unk14.i.hi >= (s16)(origin + 0x20 - arg0->runtime.search_light.extent)) || (direction && arg0->unk14.i.hi <= (s16)(arg0->runtime.search_light.extent + origin - 0x20))) {
                arg0->ext.search_light.acceleration = 0;
                arg0->unk5 = 0;
                arg0->ext.search_light.velocity = arg0->runtime.search_light.base_speed;
            }
            break;
        }
        arg0->runtime.search_light.x_accumulator = x_accum;
        arg0->runtime.search_light.y_accumulator = y_accum;
        arg0->link.direction = direction;
    }
    if (func_800D4024(arg0)) {
        arg0->on_screen = 1;
    } else {
        arg0->on_screen = 0;
        arg0->state = 2;
        arg0->unk5 = 0;
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
        frame->index = unknown->animation_step.fields.frame_index;
    } else if (PC_OBJECT_IN_ARRAY(object, main_objects)) {
        struct MainObj* main = (struct MainObj*)object;

        frame->data = (void*)main->sprite_frames;
        frame->texture = main->unk40;
        frame->clut = main->unk42;
        frame->index = main->animation_step.fields.frame_index;
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
        frame->index = visual->animation_step.fields.frame_index;
    } else if (PC_OBJECT_IN_ARRAY(object, misc_objects)) {
        struct MiscObj* misc = (struct MiscObj*)object;

        frame->data = misc->unk3C;
        frame->texture = misc->unk40;
        frame->clut = misc->unk42;
        frame->index = misc->animation_step.fields.frame_index;
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
            P_TAG* head = D_8013E1E8[buffer][i][j];

            if (head != NULL) {
                setaddr(D_8013BC40[buffer][i][j], getaddr(ordering_tag));
                setaddr(ordering_tag, head);
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
    group = (ordering >> 4) & 3;
    priority = ordering & 0xF;
    buffer = SP_DRAW_BUFFER;
    setaddr(D_8013BC40[buffer][group][priority], draw_mode);
    setaddr(draw_mode, primitive);
    D_8013BC40[buffer][group][priority] = (P_TAG*)primitive;

    SP_PRIM_CURSOR = primitive + 1;
    SP_DRAW_MODE_CURSOR = draw_mode + 1;
}

void func_80024B9C(struct QuadObj* arg0)
{
    POLY_G4* primitive;
    DR_MODE* draw_mode;
    const u8* color;
    s32 x;
    s32 y;
    u32 group;
    u32 priority;
    u32 buffer;

    if (SP_SPRITE_COUNT >= 1000 || arg0->unk34 >= COUNT(D_800F2B5C))
        return;
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
    color = D_800F2B5C[arg0->unk34];
    setPolyG4(primitive);
    setSemiTrans(primitive, (arg0->active & 0x10) != 0);
    setXY4(primitive,
        x + arg0->unk14.i.hi, y + arg0->unk18.i.hi,
        x + arg0->unk1C.i.hi, y + arg0->unk20.i.hi,
        x + arg0->unk2C.i.hi, y + arg0->unk30.i.hi,
        x + arg0->unk24.i.hi, y + arg0->unk28.i.hi);
    setRGB0(primitive, color[0], color[1], color[2]);
    setRGB1(primitive, color[3], color[4], color[5]);
    setRGB2(primitive, color[6], color[7], color[8]);
    setRGB3(primitive, color[9], color[10], color[11]);
    SetDrawMode(draw_mode, 0, 0, 0, NULL);
    group = ((u8)arg0->unk36 >> 4) & 3;
    priority = (u8)arg0->unk36 & 0xF;
    if (priority >= 8)
        return;
    buffer = SP_DRAW_BUFFER;
    setaddr(D_8013BC40[buffer][group][priority], draw_mode);
    setaddr(draw_mode, primitive);
    D_8013BC40[buffer][group][priority] = (P_TAG*)primitive;
    SP_PRIM_CURSOR = primitive + 1;
    SP_DRAW_MODE_CURSOR = draw_mode + 1;
    SP_SPRITE_COUNT++;
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
        DR_MODE* mode = SP_OT_CURSOR;
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

void func_800253F0(struct PlayerObj* player, s32 gauge)
{
    s8 value = player->unk5C & 0x7F;
    s8 target = gauge == 0 ? engine_obj.unk46 : 0x30;
    s16 x = D_800F3124[gauge].x;
    u16 bottom = D_800F3124[gauge].bottom;

    func_80025588(x, x + 5, bottom - value, bottom, value < target / 3);
    if (value == player->unk5D)
        return;
    if (player->unk5D < value) {
        player->unk5D = value;
        return;
    }
    if (player->unk5C & 0x80)
        player->unk5F = 0x10;
    func_80025588(x, x + 5, bottom - (s8)player->unk5D, bottom - value, 2);
    if (player->unk5F != 0) {
        player->unk5F--;
        return;
    }
    if (!(D_80141BD8.unk0 & 3))
        player->unk5D--;
}

void func_80036F50(struct PlayerObj* player)
{
    static const u8 weapon_masks[] = { 0, 1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80 };
    u16 input;
    s8 weapon;

    if (player->unkC3 != 0 || player->unkD9 != 0 || player->unk99 != 0 || player->unkC5 != 0 || player->unkE0 != 0 || engine_obj.unk1C != 0)
        return;
    input = player->pressed_input;
    if (((player->input.buttons.held & 0x600) == 0x600) || ((input & 0x600) == 0x600)) {
        if (player->unk93 != 0) {
            player->unk93 = 0;
            func_800384DC(player);
            func_8001540C(0, 0xC, 0);
        }
        return;
    }
    if (!(input & 0x600))
        return;
    weapon = player->unk93;
    if (input & 0x200) {
        do {
            if (++weapon == 9) {
                weapon = 0;
                break;
            }
        } while (!(weapon_masks[(u8)weapon] & player->unkB9));
    } else {
        do {
            if (--weapon < 0)
                weapon = 8;
            if (weapon == 0)
                break;
        } while (!(weapon_masks[(u8)weapon] & player->unkB9));
    }
    if (player->unk93 != weapon) {
        player->unk93 = weapon;
        func_800384DC(player);
        func_8001540C(0, 0xC, 0);
        player->unkA6 = 0;
    }
}

s32 func_8002DD04(struct MainObj* object)
{
    struct WeaponObj* weapon;

    if (object->unk7A != 0) {
        object->unk65 = 0;
        return 0;
    }
    if (object->collision_data == D_80106070 && (g_Player.unk2 == 0 || !(g_Player.unkB9 & 0x40)))
        return 0;
    if (object->unk5 != 0)
        object->unk42 &= 0x7FFF;
    for (weapon = weapon_objects; weapon < weapon_objects + COUNT(weapon_objects); weapon++) {
        s32 result;

        if (!weapon->active)
            continue;
        if (!func_8002BD58(weapon, object, (s16*)((u8*)weapon + 0x80),
                (s16*)((u8*)weapon + 0x82)))
            continue;
        result = (s8)func_8002DE30(object, weapon);
        if (result == 0x7E)
            return 0;
        if (result != 0)
            return result;
    }
    object->unk65 = 0;
    return 0;
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
            obj->active = 1;
            obj->id = 0x13;
            obj->unk2 = 0xC;
        }
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 0x13;
            obj->unk2 = 0x14;
        }
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 0x13;
            obj->unk2 = 0x15;
        }
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 0x1D;
            obj->unk2 = 0x21;
        }
        D_80139690 = OBJECT_HEADER(obj);
    }
}

void func_800924F8(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    if (arg0->unk98 > 0) {
        func_80092600(arg0);
        return;
    }

    arg0->x_vel.val = -arg0->x_vel.val;
    if (get_random() & 1) {
        arg0->y_vel.val = FIXED(4.05);
    } else {
        arg0->y_vel.val = FIXED(-4.05);
    }
    arg0->state = 2;
    arg0->unk5 = 0;
    arg0->unk15 ^= 0x40;
    func_8002B318(BASE_OBJECT(arg0), 0xC, 8);
}

void func_800C00BC(struct ItemObj* arg0)
{
    struct CollisionObj* player;
    u16 flag;
    s32 shift;

    if (g_Player.unkC5 == 0) {
        player = (struct CollisionObj*)&g_Player;
        if (!(g_Player.unk5C & 0x7F)) {
            return;
        }
    } else {
        player = (struct CollisionObj*)&qux_object;
        if (!(qux_object.unk5C & 0x7F)) {
            return;
        }
    }
    if (!func_8002C160((struct CollisionObj*)arg0, player)) {
        return;
    }

    arg0->unk5 = 0;
    switch (arg0->unk7C) {
    case 0:
        func_800BFF0C(arg0, 4, 1);
        break;
    case 1:
        func_800BFF0C(arg0, 0x10, 2);
        break;
    case 2:
    case 3:
    case 6:
        func_800BFCC0(arg0, arg0->unk7C);
        arg0->state = 3;
        break;
    case 4:
        engine_obj.unk44++;
        if (engine_obj.unk44 >= 10) {
            engine_obj.unk44 = 9;
        } else {
            func_8001540C(0, 0x15, 0);
        }
        arg0->state = 3;
        break;
    case 5:
        func_800BFF0C(arg0, engine_obj.unk46, 4);
        break;
    case 7:
        flag = engine_obj.unk5A;
        if ((flag & 0xFF) == 0xFF) {
            arg0->state = 3;
            break;
        }
        shift = arg0->unk2 - 7;
        if (flag & (1 << shift)) {
            arg0->state = 3;
            break;
        }
        engine_obj.unk5A = flag | (1 << shift);
        engine_obj.unk46 += 2;
        func_8001540C(0, 0x15, 0);
        arg0->state = 3;
        break;
    case 8:
        flag = engine_obj.unk5A;
        if ((flag & 0x3000) == 0x3000) {
            break;
        }
        shift = arg0->unk2 - 15;
        if (flag & (0x1000 << shift)) {
            break;
        }
        engine_obj.unk5A = flag | (0x1000 << shift);
        arg0->state = 3;
        engine_obj.unk5C[arg0->unk2 == 15 ? 0 : 1] = -0x80;
        func_8001540C(0, 0x15, 0);
        break;
    case 9:
        flag = engine_obj.unk5A;
        if ((flag & 0x4000) || (flag & (0x4000 << (arg0->unk2 - 17)))) {
            break;
        }
        engine_obj.unk5A = flag | (0x4000 << (arg0->unk2 - 17));
        arg0->state = 3;
        func_8001540C(0, 0x15, 0);
        engine_obj.unk5C[2] = 0;
        break;
    case 10:
        flag = engine_obj.unk5A;
        if ((flag & 0x8000) || (flag & (0x8000 << (arg0->unk2 - 18)))) {
            break;
        }
        engine_obj.unk5A = flag | (0x8000 << (arg0->unk2 - 18));
        arg0->state = 3;
        func_8001540C(0, 0x15, 0);
        break;
    default:
        arg0->state = 3;
        break;
    }
}

void func_800C0DFC(struct ItemObj* arg0)
{
    s32 i;
    s32* source;
    s32* destination;

    destination = (s32*)((u8*)SP_PALETTE + 0xEE0);
    if (arg0->unk88 != 0) {
        source = (s32*)((u8*)SP_ARC_30 + 0x9A0);
    } else {
        source = (s32*)((u8*)SP_ARC_30 + 0xA80);
    }
    for (i = 0; i < 0x38; i++) {
        destination[i] = source[i];
    }
    need_palette_load |= 1;
}

void func_80068D6C(struct MainObj* arg0)
{
    s16 x;
    s16 y;

    if (arg0->unk67 != 0) {
        return;
    }

    CollisionRelated((struct PlayerObj*)arg0);
    if (!(arg0->unk70 & 8)) {
        func_80015D60(arg0, 0xF);
        SP_CUR_MAIN_OBJ->ext.main_49.unk80 = 5;
        arg0->unk5 = 3;
        arg0->unk2C = 0x4200;
        arg0->unk6 = 0;
        arg0->unk24 = 0;
        arg0->unk28 = 0;
        arg0->unk67 = -1;
        return;
    }

    if (SP_CUR_MAIN_OBJ->ext.main_49.unk85 == 2 || arg0->unk5 == 6) {
        return;
    }

    if (arg0->unk15 != 0) {
        x = arg0->x_pos.i.hi + arg0->unk68->unk0 + arg0->unk68->unk2;
    } else {
        x = arg0->x_pos.i.hi - arg0->unk68->unk0 - arg0->unk68->unk2;
    }
    y = arg0->y_pos.i.hi + arg0->unk68->unk1 + arg0->unk68->unk3 + 8;
    if (func_8002D724((struct PlayerObj*)arg0, x, y) != 0) {
        return;
    }

    if (arg0->unk2 == 0) {
        arg0->unk15 = arg0->unk15 == 0 ? 0x40 : 0;
        arg0->unk20 = -arg0->unk20;
        return;
    }
    if (arg0->unk70 & 3) {
        return;
    }

    func_80015D60(arg0, 0x19);
    arg0->unk5 = 4;
    arg0->unk6 = 0;
    if (SP_CUR_MAIN_OBJ->ext.main_49.unk86 == 0) {
        arg0->unk24 = 0x38000;
        arg0->unk2C = 0x4200;
        arg0->unk20 = arg0->unk15 == 0 ? -0x10000 : 0x10000;
    } else {
        arg0->unk24 = 0x48000;
        arg0->unk2C = 0x5200;
        arg0->unk20 = arg0->unk15 == 0 ? -0x20000 : 0x20000;
    }
    arg0->unk67 = 1;
}

void func_80069000(struct MainObj* arg0)
{
    s16 distance;
    s16 y_distance;
    u8 mode;

    if (arg0->unk67 != 0 || arg0->unk5 == 6) {
        return;
    }
    if (SP_CUR_MAIN_OBJ->ext.main_49.unk83 != 0) {
        SP_CUR_MAIN_OBJ->ext.main_49.unk83--;
        return;
    }

    distance = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
    if (distance < 0) {
        distance = -distance;
    }
    if (distance > 0x80) {
        return;
    }

    arg0->unk15 = g_Player.x_pos.i.hi < arg0->x_pos.i.hi ? 0 : 0x40;
    mode = SP_CUR_MAIN_OBJ->ext.main_49.unk85;
    if (mode == 1 || (mode == 2 && arg0->unk2 != 0)) {
        SP_CUR_MAIN_OBJ->ext.main_49.unk82 = 0x40;
    } else {
        y_distance = arg0->y_pos.i.hi - g_Player.y_pos.i.hi;
        if (y_distance >= 0x21) {
            SP_CUR_MAIN_OBJ->ext.main_49.unk82 = 0x80;
        } else if (y_distance < -0x10) {
            SP_CUR_MAIN_OBJ->ext.main_49.unk82 = 0x82;
        } else {
            SP_CUR_MAIN_OBJ->ext.main_49.unk82 = 0x81;
        }
    }
    func_80015D60(arg0, 0xA);
    arg0->unk5 = 6;
    arg0->unk6 = 0;
}

void func_800998D4(struct ShotObj* arg0)
{
    struct MiscObj* misc;

    func_8002B694((struct AnimatedObj*)arg0);
    func_80015DC8(arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x19, 0x19);
    if (arg0->unk70 & 8) {
        arg0->unk60 = 5;
        arg0->unk68 = 0;
        arg0->unk50.data = D_80108C58;
        arg0->unk5++;
        func_80015D60(arg0, 0xB);
        if (!(arg0->unk70 & 3)) {
            misc = find_free_misc_obj();
            if (misc != NULL) {
                misc->active = 0x41;
                misc->id = 4;
                misc->unk2 = 0;
                misc->state = 0;
                misc->ext.pointer.unk50 = arg0->unk7C;
                misc->x_pos.val = arg0->x_pos.val + (get_random() & 3);
                misc->y_pos.val = arg0->y_pos.val + (get_random() & 3);
            }
        }
    }
    func_8002D9BC(arg0);
}
