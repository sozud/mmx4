#include "common.h"

#include <libspu.h>

void SelectACharacterUpdate(struct MiscObj*);
void func_80035048(struct PlayerObj*);

extern u16 D_800F1868[18];
extern u8 D_800F164C[4];
extern s16 D_800F1650[2];
extern union MainPaletteData D_800F1660;
extern const u32* D_800F2FD4[];
extern const u32* D_8011AFF0[];
extern struct StageObjectMarginData D_800F4334;
extern u16* D_8010B354[27];
extern s8** D_8010B3C0[27];
extern u8 D_800F2B5C[21][12];
extern struct HudSpriteOrigin D_800F30F4[8];
extern struct PlayerGaugePosition D_800F3124[2];
extern u16 D_800F312C[4];
extern s32 D_8010F678[3];
extern u32* D_80137E08;
extern struct Unk_unk68 D_80108704[];
extern u8 D_80108CD0[];
extern u8 D_80108CD8[];
extern u8 D_80108CF4[];
extern s8 D_8010A2B8[58][2];
extern s8 D_8010A32C[58][2];
extern s8 D_8010A3A0[58][2];
extern void (*D_8010A414[])(struct VisualObj*);
extern union AnimationStep* D_800FADD0[];
extern const u8* magma_dragoon_animations[38];
extern struct Unk_unk68 D_80107D7C[];
extern u8 magma_dragoon_arena_right[4];
extern u8 magma_dragoon_arena_left[4];
extern void (*magma_dragoon_step_funcs[14])(struct MainObj*);
extern u32 D_800FA734;
extern union AnimationStep* D_800FB63C[];
extern struct Unk_unk68 D_800FB684;
extern struct Unk_unk68 D_800FB688;
extern struct Unk_unk68 D_800FB68C;
extern struct Unk_unk68 D_800FB690;
extern struct Unk_unk68 D_800FB694;
extern struct Unk_unk68 D_800FB698;
extern struct Unk_unk68 D_800FB69C;
extern struct Unk_unk68 D_800FB6A0;
extern struct Unk_unk68 D_800FB6A4;
extern struct Unk_unk68 D_80106870[];
extern u8 D_800FB67C[];
extern void (*D_800FB6B4[])(struct MainObj*);
extern void* D_8010DA9C[];
extern union AnimationStep* D_800FBD0C[];
extern struct Unk_unk68 D_800FBBC8;
extern struct Unk_unk68 D_80106A74[];
extern u8 D_80108D94[4];
extern u8 D_80108D98[4];
extern s8 D_80108D9C[6][2];
extern union AnimationStep* D_800FC69C[];
extern struct Unk_unk68* D_800FC744[2];
extern struct Unk_unk68* D_800FC74C[2];
extern struct Unk_unk68 D_80106BF4[];
extern u8 D_800FC708[8];
extern void (*D_800FC79C[])(struct MainObj*);
extern u8 D_800FC7D4[4];
extern u8 D_800FC7D8[4];
extern s16 D_800FC7E8[6];
extern u8 D_80108E58[4];
extern u8 D_80105FA4[4];
extern u8 D_8010D3C8[4];
extern u8 D_8010D3D0[8];
extern u8 D_8010D414[8];
extern u8 D_8010D3D8[8];
extern void* D_8010D684[14];

struct Effect10Trigger {
    s16 left;
    s16 right;
    s16 top;
    s16 bottom;
    u8 sound_id;
    u8 pad;
};

extern struct Effect10Trigger* D_8010B590[2];
u8 func_800B7E88(s16* bounds);

s32 func_800154E8(s32 arg0, s32 arg1, struct BaseObj* source, u8 pan);
s32 func_8002BD58(struct MainObj*, struct MainObj*, s16*, s16*);
s32 func_8002DE30(struct MainObj*, struct WeaponObj*);
s32 func_8002C160(struct CollisionObj*, struct CollisionObj*);
void func_80046AA4(struct MainObj*);
void func_8004C6C4(struct MainObj*);
void func_8004C694(struct MainObj*);
void func_8004FC80(struct MainObj*);
u8 func_80053A88(struct PlayerObj*, s16, s16);
u8 func_80053B18(struct PlayerObj*, s16, s16);
u8 func_8005398C(struct MainObj*);
void func_80091AC4(struct MainObj*);
extern struct Unk_unk68 D_80108708[];

struct Effect00BackgroundUpdate {
    u16 object_index;
    u16 value;
};

extern struct Effect00BackgroundUpdate D_8010AE74[74];
extern u16* D_8010AF9C[4];

struct EffectSpawnData {
    u8 visual_id;
    s8 effect_type;
    s8 set_facing;
    s8 keep_facing;
    u8 animation_id;
};

extern struct EffectSpawnData D_800F460C[64];
void func_8002DF7C(struct WeaponObj*, s32);
extern u8 D_8010C6A0[24][6];
extern u8* D_8010A2A0[1];
extern s32 D_8010DB48[8];
extern s32 D_8010DB68[8];
extern s32 D_8010DB08[8];
extern s32 D_8010DB28[8];
extern s32 D_8010DAC8[8];
extern s32 D_8010DAE8[8];
extern struct Item02AnimationStep* D_8010C61C[11];
extern s8* D_8010C674[11];

struct PlayerInitialStateData {
    s32 unk20;
    s32 unk28;
    s32 unk24;
    s32 unk2C;
};

extern u8 D_800F8AD0[8];
extern struct PlayerInitialStateData D_800F8AD8[5];
extern u8 D_800F8B28[8];
extern union AnimationStep* D_800FE0FC[27];
extern u8 D_800FFB5C[4];
extern u8 D_800FFB60[];
extern u8 D_800FFB64[];
extern u32 D_801076F8[];
extern u8 D_80109150[4];
extern u8 D_80109154[4];
extern s8 D_80109158[8];
extern union AnimationStep* D_800F9934[16];
extern struct Unk_unk68 D_801062F0[32];
void func_80040760(struct PlayerObj*, s8);
extern void (*D_800F9988[13])(struct MainObj*);
extern s16 D_800F98EC[36];
extern u8 D_800F986C[128];
extern u16 D_800F99BC[4];
extern union AnimationStep* D_800F9C18[11];
extern u8 D_800F9C48[12];
extern struct Unk_unk68* D_800F9C68[2];
extern u8* D_800F9C70[2];
extern u8 D_800F9C78[4];
extern void (*D_800F9C7C[])(struct MainObj*);
extern struct Unk_unk68 D_801063F0[32];
extern struct Unk_unk68 D_801065F0[];
extern struct Unk_unk68 D_800FA424;
extern struct Unk_unk68 D_800FA428[2];
extern struct Unk_unk68 D_800FA430;
extern struct Unk_unk68 D_800FA434[2];
extern union AnimationStep* D_800FA4E8[16];
extern u8 D_800FA528[16];
extern void (*D_800FA544[])(struct MainObj*);
extern u8 D_80108C44[4];
extern u8 D_80108C4C[4];
extern u8 D_80108C54[4];
extern u8 D_80108C5C[4];
extern u8 D_80108C60[4];
extern u8 D_80108C64[4];
extern u8 D_80108C68[4];
extern u8 D_80108C6C[4];
extern u8 D_80108C70[4];
extern u32* D_8010DBC0[14];
extern u8 D_8010DBF8[8];
extern u8 D_8010DC00[8];
extern u8 D_8010DC08[8];
extern u8 D_8010DC10[8];
extern s8 D_8010E68C[4];
struct Misc04SpawnPosition {
    u16 x;
    u16 y;
};
extern struct Misc04SpawnPosition D_8010DC30[3];
extern struct Item04Data D_8010C8B4;
extern u8 D_8010C8F4[4][4];
extern struct Unk_unk68 D_80108504[];
extern struct Unk_unk68 D_800FA568;
extern union AnimationStep* D_800FA6BC[];
extern union AnimationStep* D_800FA300[];
extern struct Unk_unk68 D_800FA100;
extern struct Unk_unk68 D_800FA104;
extern u16 D_80106570[];
extern u8 D_800FA340[];
extern void (*D_800FA394[])(struct MainObj*);
extern union AnimationStep* D_8010F078[3];
extern union AnimationStep* D_800FAD68[];
extern u32 D_800FA724;
extern u32 D_800FA728;
extern u32 D_800FA738;
extern u32 D_800FA73C;
extern u32 D_800FA740;
extern u32 D_800FA744;
extern struct Unk_unk68 D_801066F0[];
extern void (*D_800FAE38[])(struct MainObj*);
extern u8 D_8010B434[16];
extern s16 D_8010F728[8][2];
extern s32 D_800F459C[];
extern s16 D_8010A63C[];
void func_800A38B0(struct ShotObj*);
extern s16 D_801096A0[2][2];
extern struct Unk_unk68 D_801096B4;
extern s32 D_800F45C0[];
extern u8 D_8010F87C[16];
void func_800D4984(struct QuadObj*);
extern u8 D_8010C250[];
extern u8 D_8010C28C[60];
extern u8 D_8010C2C8[16];
extern void (*D_8010C300[4])(struct ItemObj*);
struct PcItem03StageEntry {
    u16 x;
    u16 y;
    u16 velocity;
    u16 right;
    u16 trigger_x;
    u16 object_id;
    s16 width;
    s16 height;
};
extern struct PcItem03StageEntry D_8010C740[22];
struct PcItem01DebrisPosition {
    s16 x;
    s16 y;
};
extern struct PcItem01DebrisPosition D_8010C2D8[6];
extern u8 D_8010C8A0[4];
extern u8 D_80108CBC[4];
extern s8 D_80108CC0[2][2];
extern struct TileEffectRecord** D_80119388[26];
extern u8 D_8013B8E0[];
u8 func_800DAB40(s16, s16, s16, s16);
void func_800DADA0(struct TileEffectRecord*, u16, u16, u8, u8);
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

static s32 stage_tile_block(s8 layer, s16 x, s16 y)
{
    s32 block_x = x >> 8;
    s32 block_y = y >> 8;
    s32 index = layer * layout_size + block_y * layout_width + block_x;

    if (block_x < 0 || block_y < 0 || index < 0 || index >= PC_TILEMAP_SIZE)
        return 0;
    return SP_BG_TILEMAP[index];
}

static u8 get_stage_tile_attribute(s8 layer, s16 x, s16 y)
{
    u8 block;
    u16 tile;

    block = stage_tile_block(layer, x, y);
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
    u8 block;
    u16 tile;

    block = stage_tile_block(object->bg_offset, x, y);
    if (block == 0)
        return 0;
    object->unk6C = x & 0xF;
    object->unk6E = y & 0xF;
    tile = SP_BG_TILE_PIXELS[block * 0x100 + ((y & 0xF0) >> 4) * 0x10 + ((x & 0xF0) >> 4)];
    return SP_BG_TILE_ATTRS[tile & 0x3FFF] & 0xFF;
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
        func_80015D60(window, 0);
    }
}

void func_80028690(struct BackgroundObj* bg)
{
    s16 target;
    s16 origin;
    s16 delta;
    s16 next;

    target = bg->unk26;
    if (bg->unk1E != target) {
        origin = bg->x_pos.i.hi;
        if (target >= origin) {
            next = origin + (s8)bg->unk47;
        } else if ((s16)(g_Player.x_pos.i.hi - origin - bg->unk30 + 2) < 5) {
            next = target;
        } else {
            delta = g_Player.x_pos.i.hi - g_Player.unk18.i.hi;
            if (delta >= 0)
                delta = 0;
            next = delta + origin - (s8)bg->unk47;
        }
        bg->unk1E = next < target ? next : target;
    }

    target = bg->unk24;
    if (bg->unk1C != target) {
        origin = bg->x_pos.i.hi;
        if (target < origin) {
            next = origin - (s8)bg->unk47;
            bg->unk1C = next < target ? target : next;
        } else if ((s16)(g_Player.x_pos.i.hi - origin - bg->unk32 + 2) >= 4) {
            bg->unk1C = target;
        } else {
            delta = g_Player.x_pos.i.hi - g_Player.unk18.i.hi;
            if (delta < 0)
                delta = 0;
            next = delta + origin + (s8)bg->unk47;
            bg->unk1C = target < next ? next : target;
        }
    }

    target = bg->unk2A;
    if (bg->unk22 != target) {
        origin = bg->y_pos.i.hi;
        if (target >= origin) {
            next = origin + (s8)bg->unk47;
            bg->unk22 = next < target ? next : target;
        } else {
            next = g_Player.y_pos.i.hi - origin - bg->unk2C + 2;
            if (next < 4) {
                delta = g_Player.y_pos.i.hi - g_Player.unk1C.i.hi;
                if (delta >= 0)
                    delta = 0;
                next = delta + origin - (s8)bg->unk47;
                if (next < target)
                    next = target;
            }
            bg->unk22 = next;
        }
    }

    target = bg->unk28;
    if (bg->unk20 != target) {
        origin = bg->y_pos.i.hi;
        if (target < origin) {
            next = origin - (s8)bg->unk47;
            bg->unk20 = next < target ? target : next;
        } else if ((s16)(g_Player.y_pos.i.hi - origin - bg->unk2E + 2) >= 4) {
            bg->unk20 = target;
        } else {
            delta = g_Player.y_pos.i.hi - g_Player.unk1C.i.hi;
            if (delta < 0)
                delta = 0;
            next = delta + origin + (s8)bg->unk47;
            bg->unk20 = next < target ? next : target;
        }
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

void func_800B5D04(struct EffectObj* arg0)
{
    u32 stage_index;
    s8** animations;
    u16* destinations;
    const s8* animation;
    u16 destination;

    arg0->active = 1;
    stage_index = (u8)engine_obj.stage * 2 + (u8)engine_obj.substage;
    if (stage_index >= COUNT(D_8010B354))
        abort();
    animations = D_8010B3C0[stage_index];
    destinations = D_8010B354[stage_index];
    if (animations == NULL || destinations == NULL)
        abort();
    animation = animations[(u8)arg0->unk2];
    arg0->ext.palette_animation.cursor = (s8*)animation;
    if (animation == NULL) {
        func_8002B108(OBJECT_HEADER(arg0));
        return;
    }
    destination = destinations[(u8)arg0->unk2];
    arg0->ext.palette_animation.destination = (s32*)SP_PALETTE + (destination & 0xFF) * 8;
    arg0->ext.palette_animation.source = SP_ARC_30 + (u8)animation[0] * 8;
    arg0->ext.palette_animation.timer = animation[1];
    arg0->ext.palette_animation.palette_count = destination >> 8;
    func_800B5C60(arg0);
    arg0->state++;
}

void func_800B7EE8(struct EffectObj* arg0)
{
    struct Effect10Trigger* triggers;
    u8 index;

    if (arg0->state == 0) {
        arg0->state++;
        arg0->ext.unk_effect.unk14 = 0;
        return;
    }

    triggers = D_8010B590[(s8)engine_obj.substage];
    for (index = 0; index < 4; index++) {
        struct Effect10Trigger* trigger = &triggers[index];
        u8 bit = 1 << index;
        u8 active = arg0->ext.unk_effect.unk14;

        if (func_800B7E88(&trigger->left)) {
            if (!(active & bit)) {
                if (engine_obj.substage == 0 || active == 0)
                    func_8001540C(5, trigger->sound_id, NULL);
                arg0->ext.unk_effect.unk14 = active | bit;
            }
        } else if (active & bit) {
            if (engine_obj.substage == 0 || (active != 3 && active != 6))
                func_80015930(5, trigger->sound_id);
            arg0->ext.unk_effect.unk14 = active & ~bit;
        }
    }
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
    mmx4_pc_render_log_dump();
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
        if (!func_8002BD58((struct MainObj*)weapon, object,
                &((s16*)&weapon->unk80)[0], &((s16*)&weapon->unk80)[1]))
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
    switch (arg0->unk7C.value) {
    case 0:
        func_800BFF0C(arg0, 4, 1);
        break;
    case 1:
        func_800BFF0C(arg0, 0x10, 2);
        break;
    case 2:
    case 3:
    case 6:
        func_800BFCC0(arg0, arg0->unk7C.value);
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

void func_80038568(struct PlayerObj* arg0, s32 arg1)
{
    s32 relative;
    s8 duration;

    if (arg0->unk2 != 0) {
        return;
    }
    relative = arg1 + 0x70;
    if (arg0->unk90 == 0) {
        if (arg0->unk8E == 0 || arg0->unk17 == relative) {
            return;
        }
        arg1 = relative;
    }
    duration = arg0->animation_step.fields.duration;
    func_8003516C(arg0, arg1, arg0->animation_step.fields.event & 0x3F);
    arg0->animation_step.fields.duration = duration;
}

s32 func_8003A000(struct PlayerObj*);
void func_800347D0(struct PlayerObj*);

void func_8003B24C(struct PlayerObj*);

void func_800AED18(struct VisualObj* arg0)
{
    struct PlayerObj* owner = g_Player.unkDE != 0 ? &g_Entity : &g_Player;
    s32 finished;

    if (arg0->state == 0) {
        arg0->on_screen = 1;
        arg0->unk38 = NULL;
        arg0->animation_table = D_8011BF40;
        arg0->unk42 = 0x7802;
        arg0->unk40 = 0;
        arg0->unk16 = 3;
        arg0->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 1);
        func_800AEE5C(arg0, owner);
        func_80015D60(arg0, 2);
        arg0->state = (u8)arg0->state + 1;
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_800AEE5C(arg0, owner);
    finished = 0;
    if (owner->unk84 > 0) {
        if ((u8)owner->unk17 != 0x10) {
            finished = ((u8)owner->unk17 ^ 0x80) != 0;
        }
    } else if ((u8)owner->unk17 != 0x12) {
        finished = 1;
    }
    if (arg0->animation_step.fields.relative_step < 0) {
        finished = 1;
    }
    if (finished) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_80036BF4(struct PlayerObj* arg0, s16 ground_y)
{
    struct VisualObj* visual;
    s32 resource;
    s32 column;
    s32 row;

    if (func_8002D724(arg0, arg0->x_pos.i.hi, ground_y) != 0x24 || arg0->unkDF != 0) {
        return;
    }

    arg0->unkDF = 1;
    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 3;
        visual->unk2 = 9;
        visual->bg_offset = arg0->bg_offset;
        visual->unk16 = 1;
        visual->animation_table = D_8011BF40;
        resource = func_8002938C(0x84) & 0xFF;
        visual->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, resource);
        resource = func_8002938C(0x84) & 0xFF;
        visual->unk40 = D_801406A8[resource] >> 7;
        column = ((func_8002938C(0x84) & 0xFF) << 2) + 0x18;
        row = func_8002938C(0x84) & 0xFF;
        visual->unk42 = (u16)((column - (column & 0x7F0))
            | ((((row + 6) >> 2) + 0x1E0) << 6));
        visual->unk15 = arg0->unk15;
        visual->x_pos.i.hi = arg0->x_pos.i.hi;
        visual->y_pos.i.hi = ground_y - 8;
    }

    if (engine_obj.stage == 1) {
        func_8001540C(5, (get_random() & 1) + 3, arg0);
    } else {
        func_8001540C(2, 0xAE, arg0);
    }
}

void func_8004B8FC(struct MainObj* arg0)
{
    arg0->state = 1;
    arg0->unk6 = 0;
    arg0->unk7C = 0x90;
    arg0->unk61 = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->animation_table = (const u8* const*)D_800FB63C;
    arg0->unk15 = g_Player.x_pos.val < arg0->x_pos.val ? 0 : 0x40;
    arg0->ext.main_12.unk88 = 0;
    arg0->unk67 = 0;
    arg0->ext.main_12.unk81 = 0;
    arg0->collision_data = D_80106870;

    switch (arg0->unk2) {
    case 0:
        arg0->unk5C = 3;
        arg0->unk60 = 3;
        arg0->unk5 = 2;
        arg0->unk24 = -0x8000;
        arg0->unk2C = -0x800;
        arg0->unk16 = 6;
        arg0->unk68 = &D_800FB684;
        arg0->unk54 = &D_800FB68C;
        arg0->unk50 = &D_800FB688;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        func_80015D60(ANIMATED_OBJECT(arg0), 0);
        break;
    case 1:
        arg0->unk5C = 3;
        arg0->unk60 = 3;
        arg0->unk5 = 6;
        arg0->ext.main_12.unk86 = arg0->y_pos.u.hi;
        arg0->unk24 = 0x4000;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk2C = 0;
        arg0->unk16 = 6;
        arg0->unk68 = &D_800FB690;
        arg0->unk54 = NULL;
        arg0->unk50 = NULL;
        arg0->ext.main_12.unk8A = 0;
        func_80015D60(ANIMATED_OBJECT(arg0), 3);
        break;
    case 2:
        arg0->unk5C = 3;
        arg0->unk60 = 3;
        arg0->unk7E = 0;
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        arg0->ext.main_12.unk86 = arg0->y_pos.u.hi;
        arg0->unk16 = 6;
        arg0->unk68 = NULL;
        arg0->unk54 = NULL;
        arg0->unk50 = NULL;
        arg0->ext.main_12.unk8A = 0;
        func_80015D60(ANIMATED_OBJECT(arg0), 2);
        break;
    }
}

void func_8004BAF8(struct MainObj* arg0)
{
    s32 result;

    if (arg0->unk5 != 5 || arg0->unk6 != 4)
        CollisionRelated(PLAYER_OBJECT(arg0));
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    func_8004C6C4(arg0);
    D_800FB6B4[(u8)arg0->unk5](arg0);
    func_8002D9BC(arg0);
    result = func_8002DD04(arg0);
    if (result < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(5, D_800FB67C, arg0);
        func_800BF60C(BASE_OBJECT(arg0), 0xE);
        arg0->state++;
        return;
    }
    if (result > 0)
        arg0->ext.main_12.saved_unk5 = arg0->unk5;
    if (func_8002B160(BASE_OBJECT(arg0)) != 0) {
        arg0->state++;
        return;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_8004BCFC(struct MainObj* arg0)
{
    s32 transition = 0;

    switch (arg0->unk6) {
    case 0:
        if (arg0->unk7E-- != 0)
            return;
        arg0->unk6 = 1;
        arg0->unk7 = 0;
        arg0->unk67 = 1;
        arg0->ext.main_12.unk86 = arg0->y_pos.u.hi;
        arg0->unk24 = 0x80000;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        if (arg0->unk2 == 2) {
            if ((get_random() & 3) == 0) {
                arg0->ext.main_12.unk80 = 0x10;
                arg0->ext.main_12.unk81 = 1;
            } else {
                arg0->ext.main_12.unk80 = 0xF;
                arg0->ext.main_12.unk81 = 0;
            }
        } else {
            arg0->ext.main_12.unk80 = get_random() & 0xF;
        }
        arg0->unk2C = 0;
        arg0->unk68 = &D_800FB690;
        arg0->unk54 = &D_800FB698;
        arg0->unk50 = &D_800FB694;
        func_80015D60(ANIMATED_OBJECT(arg0), 2);
        break;

    case 1: {
        struct Unk_unk68* bounds;
        s16 x;
        s16 y;

        func_8002B694(ANIMATED_OBJECT(arg0));
        bounds = arg0->unk68;
        x = arg0->x_pos.i.hi + bounds->unk0;
        y = arg0->y_pos.i.hi + bounds->unk1 + bounds->unk3 + 4;
        if (func_8002D724(PLAYER_OBJECT(arg0), x, y) != 0x24) {
            arg0->unk6 = 2;
            func_80015D60(ANIMATED_OBJECT(arg0), 9);
        } else if (arg0->unk7 == 0) {
            func_800C7B80(arg0, 1);
            arg0->unk7 = 1;
            func_8001540C(2, 0x25, arg0);
        }
        transition = (u8)arg0->unk70 & 4;
        break;
    }

    case 2:
        func_8002B694(ANIMATED_OBJECT(arg0));
        transition = arg0->y_pos.i.hi < g_Player.y_pos.i.hi;
        break;
    }

    if (transition) {
        func_8004C694(arg0);
        arg0->unk5 = 5;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
        func_80015D60(ANIMATED_OBJECT(arg0), 0xA);
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8004BF5C(struct MainObj* arg0)
{
    switch (arg0->unk6) {
    case 0:
        if (arg0->animation_step.fields.event != 0) {
            arg0->unk6 = 1;
            func_80015D60(ANIMATED_OBJECT(arg0), 6);
        }
        break;
    case 1:
        if (arg0->animation_step.fields.event != 0) {
            arg0->unk6 = 2;
            func_80015D60(ANIMATED_OBJECT(arg0), 7);
            arg0->unk68 = &D_800FB69C;
            arg0->unk54 = &D_800FB6A4;
            arg0->unk50 = &D_800FB6A0;
        }
        break;
    case 2:
        if (arg0->animation_step.fields.event != 0) {
            arg0->unk6 = 3;
            arg0->unk7E = 10;
        }
        break;
    case 3:
        if (--arg0->unk7E == 0) {
            u8 direction;

            arg0->unk6 = 4;
            arg0->ext.main_12.unk8C = 0;
            direction = (u8)func_8002B7DC(
                OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
            if ((u8)(direction - 8) < 0x10) {
                arg0->unk15 = 0;
                if (direction < 0xC)
                    direction = 0xC;
                if (direction >= 0x15)
                    direction = 0x14;
            } else {
                arg0->unk15 = 0x40;
                if ((u8)(direction - 0x18) < 4)
                    direction = 0x1C;
                else if ((u8)(direction - 5) < 3)
                    direction = 4;
            }
            func_8002B93C(MOVING_OBJECT(arg0), direction);
            arg0->unk28 = 0;
            arg0->unk2C = 0;
            arg0->unk20 *= 6;
            arg0->unk24 *= 6;
            func_80015D60(ANIMATED_OBJECT(arg0), 8);
        }
        break;
    case 4: {
        struct Unk_unk68* bounds;
        s16 x;
        s16 y;

        func_8002B694(ANIMATED_OBJECT(arg0));
        bounds = arg0->unk68;
        x = arg0->x_pos.i.hi + bounds->unk0 + bounds->unk2;
        y = arg0->y_pos.i.hi + bounds->unk1 + bounds->unk3;
        if (func_8002D724(PLAYER_OBJECT(arg0), x, y) == 0x24) {
            s16 tile = x / 16;
            if ((u16)tile != arg0->ext.main_12.unk8C) {
                func_800C7B80(arg0, 1);
                func_8001540C(2, 0x25, arg0);
                arg0->ext.main_12.unk8C = tile;
            }
        }
        break;
    }
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8004E8E0(struct MainObj* arg0)
{
    arg0->unk5C = 0x10;
    arg0->unk60 = 3;
    arg0->unk61 = 0;
    arg0->collision_data = D_80106A74;
    arg0->animation_table = (const u8* const*)D_800FBD0C;
    arg0->unk16 = 6;
    arg0->unk68 = &D_800FBBC8;
    arg0->unk54 = &D_800FBBB8;
    arg0->unk50 = &D_800FBBC0;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    func_8004FC50(ANIMATED_OBJECT(arg0));

    arg0->ext.main_16.unk80 = 0;
    arg0->ext.main_16.unk84 = 0;
    arg0->ext.main_16.unk8C = 0;
    arg0->ext.main_16.unk90 = 0;
    arg0->ext.main_16.shot_09_active = 1;

    switch (arg0->unk2) {
    case 0:
        func_80015D60(ANIMATED_OBJECT(arg0), 0);
        arg0->unk5 = 2;
        break;
    case 1:
        func_80015D60(ANIMATED_OBJECT(arg0), 2);
        arg0->unk5 = 2;
        break;
    case 2:
        func_80015D60(ANIMATED_OBJECT(arg0), 1);
        arg0->unk7C = 0x14;
        arg0->unk5 = 9;
        break;
    case 3:
        func_80015D60(ANIMATED_OBJECT(arg0), 2);
        arg0->unk5 = 0xA;
        break;
    case 4:
        func_80015D60(ANIMATED_OBJECT(arg0), 0x11);
        arg0->unk7E = 3;
        arg0->unk5 = 8;
        arg0->unk42 += 2;
        break;
    case 5:
        func_80015D60(ANIMATED_OBJECT(arg0), 2);
        arg0->unk7E = 3;
        arg0->unk5 = 2;
        arg0->unk42 += 2;
        break;
    }

    arg0->state = 1;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
}

void func_8004FD38(struct MainObj* arg0, s32 animation)
{
    struct MiscObj* misc;
    struct Unk_unk68* bounds;
    s16 x;
    s16 y;
    s32 resource;

    if (arg0->unk67 != 0)
        return;

    bounds = arg0->unk68;
    x = arg0->x_pos.i.hi + bounds->unk0;
    y = arg0->y_pos.i.hi + bounds->unk1 + bounds->unk3 - 4;
    if (func_8002D724(PLAYER_OBJECT(arg0), x, y) != 0x24)
        return;

    misc = find_free_misc_obj();
    if (misc != NULL) {
        misc->active = 0x41;
        misc->id = 5;
        misc->animation_table = (u32**)D_8010DA9C;
        misc->unk42 = 0x7888;
        misc->unk40 = (u16)((u32)D_801406A8[4] >> 7);
        misc->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, 4);
        misc->bg_offset = arg0->bg_offset;
        misc->y_pos.val = arg0->y_pos.val + FIXED(6);
        misc->unk15 = arg0->unk15;
        if ((s8)animation == 2) {
            misc->unk2 = 1;
            misc->ext.misc_5.owner = arg0;
            misc->x_pos.val = arg0->x_pos.val - FIXED(13);
        } else {
            misc->unk2 = 0;
            misc->x_pos.val = arg0->x_pos.val;
        }
        misc->ext.misc_5.animation = (s8)animation;
        misc->state = 3;
    }

    if ((s8)animation != 2)
        return;

    misc = find_free_misc_obj();
    if (misc == NULL)
        return;
    misc->active = 0x41;
    misc->id = 5;
    misc->unk2 = 1;
    misc->animation_table = (u32**)D_8010DA9C;
    resource = func_8002938C(0x84);
    misc->unk40 = (u16)((u32)D_801406A8[resource] >> 7);
    resource = func_8002938C(0x84);
    misc->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, resource);
    misc->unk42 = 0x7888;
    misc->bg_offset = arg0->bg_offset;
    misc->y_pos.val = arg0->y_pos.val + FIXED(6);
    misc->unk15 = arg0->unk15;
    misc->state = 3;
    misc->ext.misc_5.animation = (s8)animation;
    misc->ext.misc_5.owner = arg0;
    misc->x_pos.val = arg0->x_pos.val + FIXED(13);
}

void func_8004ED60(struct MainObj* arg0)
{
    s32 random;
    s32 distance;

    func_8004FC50(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;

    arg0->ext.main_16.unk8C = 0;
    distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if (distance < 0)
        distance = -distance;

    if (distance < 0x61) {
        if (weapon_objects[0].active != 0)
            goto choose_state_6;
        if ((get_random() & 7) < 5)
            goto choose_state_6;
        func_80015D60(ANIMATED_OBJECT(arg0), 0x10);
        arg0->ext.main_16.unk80 = 1;
        arg0->ext.main_16.unk90 = 1;
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        return;
    }

    random = get_random() & 0xF;
    if (weapon_objects[0].active != 0) {
        if (random < 0xC) {
            func_80015D60(ANIMATED_OBJECT(arg0), 0x10);
            arg0->ext.main_16.unk90 = 1;
            arg0->ext.main_16.unk80 = 0;
            arg0->unk5 = 4;
            arg0->unk6 = 0;
            return;
        }
        if (random < 0xE) {
            func_80015D60(ANIMATED_OBJECT(arg0), 0x10);
            arg0->ext.main_16.unk80 = 1;
            arg0->ext.main_16.unk90 = 1;
            arg0->unk5 = 4;
            arg0->unk6 = 0;
            return;
        }
    } else {
        if (random < 0xC) {
            func_80015D60(ANIMATED_OBJECT(arg0), 0x11);
            arg0->unk5 = 8;
            arg0->unk6 = 0;
            return;
        }
        if (random < 0xE) {
            func_80015D60(ANIMATED_OBJECT(arg0), 0x10);
            arg0->ext.main_16.unk80 = 1;
            arg0->ext.main_16.unk90 = 1;
            arg0->unk5 = 4;
            arg0->unk6 = 0;
            return;
        }
    }

choose_state_6:
    arg0->ext.main_16.unk8C = 1;
    arg0->unk61 = (u8)engine_obj.cur_character;
    func_8004FC80(arg0);
    arg0->unk5 = 6;
    arg0->unk6 = 0;
}

void func_8004F1A0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 0)
        return;

    arg0->unk54 = &D_800FBBB8;
    func_8004FC50(ANIMATED_OBJECT(arg0));
    if (arg0->unk2 >= 4) {
        arg0->unk7E = 3;
        func_80015D60(ANIMATED_OBJECT(arg0), 0x11);
        arg0->unk5 = 8;
    } else {
        func_80015D60(ANIMATED_OBJECT(arg0), 0);
        arg0->unk5 = 2;
    }
    arg0->unk6 = 0;
}

void func_8009B0B8(struct ShotObj* arg0)
{
    arg0->unk58.collision_bounds = D_801060F0;
    arg0->unk16 = 5;
    arg0->unk54 = D_80108D94;
    arg0->unk50.data = D_80108D94;
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->unk60 = 3;
    arg0->unk68 = NULL;
    arg0->unk84.value = 0x1E;
    arg0->unk42 &= 0x7FFF;
    func_80015D60(ANIMATED_OBJECT(arg0), 5);
}

void func_8009B1E8(struct ShotObj* arg0)
{
    s32 index = arg0->unk2;

    arg0->state = 4;
    arg0->on_screen = 1;
    arg0->unk58.collision_data = D_80106070;
    arg0->unk54 = D_80108D98;
    arg0->unk50.data = D_80108D98;
    arg0->unk42 &= 0x7FFF;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    if (arg0->unk15 == 0)
        arg0->x_pos.i.hi += D_80108D9C[index][0];
    else
        arg0->x_pos.i.hi -= D_80108D9C[index][0];
    arg0->y_vel.val *= 4;
    arg0->x_vel.val *= 4;
    arg0->unk5C = 1;
    arg0->unk60 = 3;
    arg0->y_pos.i.hi += D_80108D9C[index][1];
    func_80015D60(ANIMATED_OBJECT(arg0), index + 8);
}

void func_8009B6B8(struct ShotObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->unk54 = D_80108E58;
    arg0->unk50.data = D_80108E58;
    arg0->unk58.collision_data = D_80106070;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->unk60 = 3;
    arg0->x_vel.val *= 3;
    arg0->y_vel.val *= 3;
    func_80015D60(ANIMATED_OBJECT(arg0), 0x11);
}

void func_80091B1C(struct MainObj* arg0)
{
    struct Unk_unk68* bounds;
    s32 velocity = arg0->unk20;
    s16 x;
    s16 y;
    s32 reverse = 0;

    if (!(arg0->unk70 & 8)) {
        arg0->unk5 = 1;
        arg0->unk6 = 0;
        arg0->unk7C = 0;
        arg0->unk20 = 0;
        arg0->unk24 = 0;
        arg0->unk28 = 0;
        arg0->unk2C = 0x4200;
        arg0->ext.main_76.saved_x_velocity = velocity;
        return;
    }

    bounds = arg0->unk68;
    y = arg0->y_pos.i.hi + bounds->unk1 + (u8)bounds->unk3 + 4;
    if (arg0->unk20 < 0) {
        reverse = (arg0->unk70 & 2) != 0;
        x = arg0->x_pos.i.hi + bounds->unk0 - (u8)bounds->unk2;
    } else {
        reverse = (arg0->unk70 & 1) != 0;
        x = arg0->x_pos.i.hi + bounds->unk0 + (u8)bounds->unk2;
    }
    if (func_8002D724(PLAYER_OBJECT(arg0), x, y) < 0x38)
        reverse = 1;
    if (reverse)
        arg0->unk20 = -arg0->unk20;
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_800C63BC(struct ItemObj* arg0)
{
    struct ItemObj* child;
    s32 discard;
    u8 resource;
    s32 column;
    s32 row;

    discard = g_Player.unk2 != 0;
    if (engine_obj.unk37 != 0) {
        if (g_Player.unkA7 != 0)
            discard = 1;
    } else {
        if (D_8010D3D0[(u8)arg0->unk2] & g_Player.unkA7)
            discard = 1;
        if (arg0->unk2 == 2 && g_Player.unkB8 == 2)
            discard = 0;
        if (arg0->unk2 == 3 && g_Player.unkB8 == 1)
            discard = 0;
    }

    if (discard) {
        func_8002B0C8(OBJECT_HEADER(arg0));
        return;
    }

    arg0->on_screen = 1;
    arg0->unk68 = (struct Unk_unk68*)D_8010D3C8;
    arg0->bg_offset = g_Player.bg_offset;
    resource = func_8002938C(0xA2) & 0xFF;
    arg0->animation_table = (const u8* const*)D_8010D684;
    arg0->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, resource);
    arg0->unk40 = (u16)((u32)D_801406A8[resource] >> 7);
    column = resource * 4 + 0x18;
    row = resource + 6;
    arg0->unk42 = (u16)((column - (column & 0x7F0)) | (((row >> 2) + 0x1E0) << 6));
    arg0->unk16 = 4;
    arg0->unk15 = 0;
    arg0->unk75 = 1;
    g_Player.unkE2 = 0;
    func_80015D60(ANIMATED_OBJECT(arg0), 0);

    do {
        arg0->y_pos.u.hi += 0x10;
        CollisionRelated(PLAYER_OBJECT(arg0));
    } while (!(arg0->unk70 & 8));

    child = find_free_item_obj();
    if (child != NULL) {
        child->active = 1;
        child->id = 0x1A;
        child->unk2 = 6;
        child->unk7C.object = arg0;
        child->bg_offset = arg0->bg_offset;
    }

    func_800C661C(arg0, 0x23, D_8010D3D8[(u8)arg0->unk2]);
    arg0->unk5 = 0;
    arg0->state++;
    func_8002E184(PLAYER_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x88, 0x88);
}

s32 func_800B8490(struct EffectObj* arg0)
{
    if ((u16)(arg0->x_pos.i.hi - background_objects[0].x_pos.i.hi + 0x40) >= 0x1C0)
        return 1;
    return (u16)(arg0->y_pos.i.hi - background_objects[0].y_pos.i.hi + 0x40) >= 0x170;
}

void func_800B8114(struct EffectObj* arg0)
{
    struct Effect12Ext* ext = &arg0->ext.effect_12;
    struct MainObj* child;
    s32 distance;
    u8 index;
    s16 i;

    if (func_800B8490(arg0) != 0) {
        arg0->state = 2;
        return;
    }

    for (i = 0; i < ext->child_count; i++) {
        child = ext->children[i];
        if (child != NULL && child->active == 0)
            ext->children[i] = NULL;
    }

    switch (arg0->unk5) {
    case 0:
        distance = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
        if (distance < 0)
            distance = -distance;
        if ((s16)distance < 0x80)
            arg0->unk5 = 1;
        break;
    case 1:
        for (i = 0; i < ext->child_count; i++) {
            if (ext->children[i] != NULL)
                continue;
            if (ext->cooldown != 0) {
                ext->cooldown--;
                continue;
            }
            child = find_free_main_obj();
            if (child == NULL)
                continue;
            ext->children[i] = child;
            child->active = 0x41;
            child->id = ext->child_id;
            child->unk2 = ext->child_subtype;
            child->x_pos.val = arg0->x_pos.val;
            child->y_pos.val = arg0->y_pos.val;
            ext->cooldown = 0x20;
            index = func_8002938C(child->id);
            child->unk40 = D_801406A8[index] >> 7;
            index = func_8002938C(child->id);
            child->unk42 = SOME_COORDINATE_CONVERSION(index);
            index = func_8002938C(child->id);
            child->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[index];
            ext->spawned++;
            if (ext->spawned >= ext->child_count)
                arg0->unk5 = 2;
        }
        break;
    case 2:
        child = NULL;
        for (i = 0; i < ext->child_count; i++)
            child = ext->children[i];
        if (child == NULL) {
            arg0->unk5 = 3;
            ext->spawned = 0;
            ext->cooldown = 0;
            ext->timer = 0x60;
        }
        break;
    case 3:
        if (--ext->timer == 0)
            arg0->unk5 = 0;
        break;
    }
}

struct Item05MotionConfig {
    u32 collision_mode;
    s32 velocity;
    s16 acceleration;
    s16 unused;
};

struct Item05StageConfig {
    u16 tile;
    u16 index;
    u16 x;
    u16 y;
};

extern void* D_8010C9B4[4];
extern struct Item05MotionConfig D_8010C9C4[9];
extern struct Item05StageConfig D_8010CA30[9];
extern u8 D_8010CA78[9][4];
void func_800C1244(struct ItemObj*);
void func_800C1318(void);

void func_800C0EBC(struct ItemObj* arg0)
{
    s8 index;

    arg0->active = 0x41;
    arg0->state++;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->animation_table = (const u8* const*)D_8010C9B4;
    arg0->unk42 = 0x788C;
    arg0->unk40 = D_801406A8[5] >> 7;
    arg0->unk16 = 6;
    arg0->unk5C = 0xF;
    arg0->unk61 = 0;
    arg0->unk54 = NULL;
    index = arg0->unk2;
    arg0->unk68 = (struct Unk_unk68*)D_8010CA78[index];
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[5];
    arg0->x_pos.i.hi = D_8010CA30[index].x;
    arg0->y_pos.i.hi = D_8010CA30[index].y;
    arg0->y_vel.val = D_8010C9C4[index].velocity;
    arg0->unk2C = (u16)D_8010C9C4[index].acceleration;
    arg0->unk75 = 1;
    arg0->unk76 = 0;
    func_80015D60(arg0, (u8)D_8010C9C4[index].collision_mode != 0 ? 2 : 0);
    func_800C1244(arg0);
    if (arg0->unk2 == 0)
        func_800C1318();
}

void func_800C1050(struct ItemObj* arg0)
{
    const struct Item05MotionConfig* config;
    s32 offset;
    s32 y;
    u8 old_flags;
    u8 flags;

    func_8002B318(BASE_OBJECT(arg0), D_8010CA78[arg0->unk2][2], D_8010CA78[arg0->unk2][3]);
    config = &D_8010C9C4[arg0->unk2];
    if (arg0->unk76 == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        arg0->y_vel.val = config->velocity;
    } else if ((u8)config->collision_mode != 0) {
        arg0->y_vel.val = -0x1A000;
    }

    offset = arg0->y_pos.val - g_Player.y_pos.val;
    old_flags = g_Player.unk71;
    func_8002B718((struct MovingObj*)arg0);
    func_8002E184(PLAYER_OBJECT(arg0));
    flags = g_Player.unk71;
    if (flags != old_flags && (flags & 3)) {
        y = arg0->y_pos.val - offset - arg0->y_vel.val / 4;
        g_Player.y_pos.val = y;
        g_Player.unk71 = 0;
        func_8002E184(PLAYER_OBJECT(arg0));
        g_Player.y_pos.val = y;
        if (g_Player.unk71 & 3)
            g_Player.y_pos.val = y + g_Player.y_vel.val;
        else
            g_Player.y_pos.val = y - arg0->y_vel.val * 3;
        g_Player.unk71 = flags;
    }

    if (arg0->y_pos.i.hi >= 0x621) {
        arg0->y_pos.i.hi = 0x4E0;
        arg0->y_vel.val = config->velocity;
    }
}

void func_80034C58(struct PlayerObj* arg0);
void func_80034D20(struct PlayerObj* arg0);

s32 func_80033FF0(struct PlayerObj* arg0)
{
    u8 attribute = func_8002D994(arg0);

    if (arg0->unk88.bytes.collision_flags & 8) {
        func_80034D20(arg0);
        return 1;
    }
    if ((arg0->input.buttons.held & 4) && attribute == 0x21) {
        func_80034C58(arg0);
        return 1;
    }
    if ((u8)(attribute - 0x20) < 2 && !(arg0->pressed_input & 0x80))
        return 0;
    func_800350A4(arg0, 0x1E);
    arg0->unk5 = 0xE;
    arg0->unk6 = 4;
    return 1;
}

void func_80037DB0(struct PlayerObj* arg0);
void func_80037DFC(struct PlayerObj* arg0);
void func_80037E4C(struct PlayerObj* arg0, s32 arg1);
void func_80037EAC(struct PlayerObj* arg0, s32 arg1);
void func_80037F78(struct PlayerObj* arg0);
s32 func_800375B4(struct PlayerObj* arg0);
void func_80037708(struct PlayerObj* arg0);
void func_800387A8(struct PlayerObj* arg0);

void func_80037484(struct PlayerObj* arg0, s32 arg1)
{
    switch ((s8)(arg0->unk96 - 2)) {
    case 0:
    case 9:
        func_80037DB0(arg0);
        break;
    case 10:
        func_80037DFC(arg0);
        break;
    case 2:
        func_80037E4C(arg0, arg1);
        break;
    case 11:
        func_80037EAC(arg0, arg1);
        break;
    case 5:
    case 14:
        func_80037F78(arg0);
        break;
    }
}

void func_800B6660(struct EffectObj* arg0);

static u8 effect_05_probe(s16 x, s32 y_offset)
{
    s16 y = (u16)g_Player.y_pos.i.hi + y_offset;

    if (g_Player.unk68 != NULL)
        y += (s8)g_Player.unk68->unk1 + g_Player.unk68->unk3;

    return func_8002D724(&g_Player, x, y);
}

static void effect_05_dispatch(struct EffectObj* arg0)
{
    if (arg0->state < 2)
        D_8010B450[arg0->state](arg0);
    else
        D_8010B458[arg0->state - 2](arg0);
}

void func_800B60BC(struct EffectObj* arg0)
{
    struct Effect5Ext* ext = &arg0->ext.effect_5;
    s32 delta;
    s32 step;
    u8 tile;

    ext->unk21 = ext->unk20;
    ext->unk20 = effect_05_probe(g_Player.x_pos.i.hi, 0);
    delta = g_Player.x_pos.val - g_Player.unk18.val;
    if (g_Player.state != 1)
        goto facing;

    for (;;) {
        switch (ext->unk20) {
        case 0:
            if (arg0->state == 2)
                D_8010B458[0](arg0);
            goto record;
        case 16:
            ext->unk20 = effect_05_probe(g_Player.x_pos.i.hi, -0x10);
            continue;
        case 17:
        case 18:
        case 19:
        case 20:
        case 25:
        case 26:
            arg0->state = 1;
            if (ext->unk21 == 0x3C && g_Player.unk15 != 0 && g_Player.unk5 != 0xC)
                goto hold;
            step = delta - 0x38000;
            if (step < -0x68000)
                step = -0x68000;
            goto push;
        case 21:
        case 22:
        case 23:
        case 24:
        case 27:
        case 28:
            arg0->state = 1;
            if (ext->unk21 == 0x3C && g_Player.unk15 == 0 && g_Player.unk5 != 0xC)
                goto hold;
            step = delta + 0x38000;
            if (step > 0x68000)
                step = 0x68000;
            goto push;
        case 60:
            effect_05_dispatch(arg0);
            goto record;
        default:
            arg0->state = 1;
            goto record;
        }
    }

hold:
    g_Player.x_pos.val = g_Player.unk18.val;
    goto probe;
push:
    g_Player.x_pos.val = g_Player.unk18.val + step;
probe:
    tile = effect_05_probe(g_Player.x_pos.i.hi, 0);
    ext->unk20 = tile;
    if (tile < 0x1D) {
        if (tile >= 0x10)
            goto facing;
        if (tile == 0 && arg0->state == 2)
            goto record;
    }
    effect_05_dispatch(arg0);
record:
    ext->unk1C = g_Player.unk5;
facing:
    if (g_Player.x_pos.val != g_Player.unk18.val)
        ext->unk1E = (g_Player.x_pos.val >= g_Player.unk18.val) << 6;
}

void func_800B64BC(struct EffectObj* arg0)
{
    struct Effect5Ext* ext = &arg0->ext.effect_5;

    ext->unk1F = 0;
    if (g_Player.state != 1)
        return;

    switch (g_Player.unk5) {
    case 48:
        if (ext->unk1C != 0x32)
            return;
        ext->unk14 = g_Player.x_vel.val;
        goto adjust;
    case 2:
        ext->unk14 = g_Player.x_pos.val - g_Player.unk18.val;
    adjust:
        if (ext->unk1C == 3)
            ext->unk14 = ext->unk1E != 0 ? 0x8000 : -0x8000;
        if (ext->unk1C == 4)
            ext->unk14 = ext->unk1E != 0 ? 0x20000 : -0x20000;
        goto accelerate;
    case 5:
    case 8:
        ext->unk14 = g_Player.x_vel.val;
    accelerate:
        if (ext->unk1E != 0) {
            ext->unk18 = -0x1800;
            ext->unk1D = 1;
        } else {
            ext->unk18 = 0x1800;
            ext->unk1D = 0;
        }
        break;
    case 12: {
        s32 speed;

        if (g_Player.unk6 != 2)
            return;
        ext->unk14 = 0;
        speed = g_Player.x_vel.val;
        if (speed < 0)
            speed = -speed;
        ext->unk1F = speed / 0xC000;
        ext->unk1E = g_Player.unk15;
        if (g_Player.unk15 != 0) {
            ext->unk18 = 0x2800;
            ext->unk1D = 3;
        } else {
            ext->unk18 = -0x2800;
            ext->unk1D = 2;
        }
        break;
    }
    default:
        return;
    }
    arg0->state++;
}

static int effect_05_tile_slides(u8 tile)
{
    return tile == 0x3C || tile == 0 || tile == 0x18 || tile == 0x1C || tile == 0x14 || tile == 0x1A;
}

void func_800B6660(struct EffectObj* arg0)
{
    struct Effect5Ext* ext = &arg0->ext.effect_5;
    s16 x;
    s16 previous;

    if (g_Player.unk5 == 6 || g_Player.unk5 == 9 || (g_Player.unk88.bytes.collision_flags & 3)) {
        arg0->state = 1;
        return;
    }

    if (ext->unk1D < 2) {
        arg0->x_pos.val = g_Player.x_pos.val + ext->unk14;
        ext->unk14 += ext->unk18;
        if (!effect_05_tile_slides(effect_05_probe(arg0->x_pos.i.hi, 0))) {
            g_Player.x_pos.val = arg0->x_pos.val;
            arg0->state = 1;
            return;
        }
        g_Player.x_pos.val = arg0->x_pos.val;
        if (ext->unk1D != 0 ? ext->unk14 < 0 : ext->unk14 >= 0)
            arg0->state = 1;
    } else if (--ext->unk1F == 0xFF) {
        ext->unk18 = ext->unk18 > 0 ? -0x600 : 0x600;
        ext->unk1D -= 2;
        func_800B6660(arg0);
    } else {
        s32 moved;

        arg0->x_pos.val = g_Player.x_pos.val + ext->unk14;
        ext->unk14 += ext->unk18;
        if (!effect_05_tile_slides(effect_05_probe(arg0->x_pos.i.hi, 0))) {
            g_Player.x_pos.val = arg0->x_pos.val;
            arg0->state = 1;
            return;
        }
        g_Player.x_pos.val = arg0->x_pos.val;
        if (g_Player.unk5 != 0xC && g_Player.unk6 != 2) {
            moved = arg0->x_pos.val - g_Player.unk18.val;
            if (ext->unk14 > 0 ? ext->unk14 < moved : moved < ext->unk14)
                arg0->state = 1;
        }
    }

    x = g_Player.x_pos.i.hi;
    previous = g_Player.unk18.i.hi;
    if (ext->unk1D & 1) {
        if (g_Player.x_pos.val < g_Player.unk18.val && previous == x)
            arg0->state = 1;
    } else if (g_Player.unk18.val < g_Player.x_pos.val) {
        if (x - previous < 0 ? x != (s16)(previous - 1) : x - previous != 1)
            arg0->state = 1;
    }
}

extern struct Effect21SpawnRecord* D_8010BD68[20];
extern u8* D_8010BDD8[8];

s32 func_800B9E54(struct Effect21SpawnRecord* record)
{
    struct BackgroundObj* background = &background_objects[g_Player.bg_offset];

    if ((u16)(record->x - background->x_pos.i.hi + 0x280) >= 0x640)
        return 0;
    return (u16)(record->y - background->y_pos.i.hi + 0x1E0) < 0x4B0;
}

void func_800B9EC0(struct EffectObj* arg0)
{
    struct Effect21Ext* ext = &arg0->ext.effect_21;

    ext->timer = 0;
    arg0->state++;
    switch (arg0->unk2) {
    case 0:
        ext->spawned = 0;
        ext->phase = 0;
        break;
    case 1:
    case 2:
    case 4:
    case 5:
        ext->cursor = D_8010BD68[ext->index & 0x7F];
        break;
    case 3:
        ext->index = 8;
        break;
    }
}

void func_800B9F38(struct EffectObj* arg0)
{
    struct Effect21Ext* ext = &arg0->ext.effect_21;
    struct EffectObj* effect;
    u8* list;
    u32 bit;
    u8 id;

    ext->was_inside = ext->inside;
    if ((u16)(g_Player.x_pos.i.hi - 0x2A1) < 0x9BF)
        ext->inside = 1;
    if (ext->inside == 0)
        return;
    if (ext->inside != ext->was_inside) {
        ext->phase = 0;
        ext->timer = 0;
    }
    if (ext->timer != 0) {
        ext->timer--;
        return;
    }

    list = D_8010BDD8[ext->phase * 2 + ext->inside - 1];
    do {
        id = *list & 0x7F;
        bit = 1 << id;
        if ((u8)func_800B9E54(D_8010BD68[id]) != 0 && !(ext->spawned & bit)) {
            effect = find_free_effect_obj();
            if (effect != NULL) {
                effect->active = 1;
                effect->id = 0x15;
                effect->unk2 = 1;
                effect->ext.effect_21.index = id;
                ext->spawned |= bit;
            }
        }
    } while (!(*list++ & 0x80));

    list = D_8010BDD8[((ext->phase + 2) & 3) * 2 + ext->inside - 1];
    do {
        id = *list & 0x7F;
        bit = 1 << id;
        if (ext->spawned & bit) {
            effect = find_free_effect_obj();
            if (effect != NULL) {
                effect->active = 1;
                effect->id = 0x15;
                effect->unk2 = 2;
                effect->ext.effect_21.index = id;
                ext->spawned &= ~bit;
            }
        }
    } while (!(*list++ & 0x80));

    ext->phase = (ext->phase + 1) & 3;
    ext->timer = ext->inside == 1 ? 0x96 : 0x8C;
}

void func_800BA178(struct EffectObj* arg0)
{
    struct Effect21Ext* ext = &arg0->ext.effect_21;
    struct MiscObj* misc;
    struct ItemObj* item;
    struct EffectObj* effect;

    if (arg0->unk5 != 0) {
        if (--ext->timer != 0)
            return;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x15;
            effect->unk2 = 5;
            effect->ext.effect_21.index = ext->index;
        }
        arg0->state++;
        return;
    }

    if (ext->timer != 0) {
        ext->timer--;
        return;
    }
    misc = find_free_misc_obj();
    if (misc == NULL)
        return;
    misc->active = 0x41;
    misc->id = 8;
    misc->x_pos.i.hi = ext->cursor->x;
    misc->y_pos.i.hi = ext->cursor->y;
    misc->unk2 = ext->cursor->object_id;
    if (!(arg0->unk2 & 1)) {
        misc->unk2 = ext->cursor->flags | 0x80;
        ext->timer = 4;
    } else {
        ext->timer = 3;
    }
    if (!(ext->cursor->flags & 0x80)) {
        ext->cursor++;
        return;
    }
    if (arg0->unk2 == 4) {
        ext->timer = 0x78;
        arg0->unk5++;
        return;
    }
    if (arg0->unk2 == 5) {
        item = find_free_item_obj();
        if (item != NULL) {
            item->active = 1;
            item->id = 0x11;
            item->unk2 = ext->index - 8;
        }
    }
    arg0->state++;
}

void func_800BA340(struct EffectObj* arg0)
{
    struct Effect21Ext* ext = &arg0->ext.effect_21;
    struct MiscObj* misc;
    struct ItemObj* item;

    switch (arg0->unk5) {
    case 0:
        if (g_Player.x_pos.i.hi >= 0xC60)
            arg0->unk5 = 1;
        break;
    case 1:
        arg0->unk5 = 2;
        ext->cursor = D_8010BD68[ext->index];
        break;
    case 2:
        if (ext->timer != 0) {
            ext->timer--;
            break;
        }
        misc = find_free_misc_obj();
        if (misc == NULL)
            break;
        misc->active = 0x41;
        misc->id = 8;
        misc->x_pos.i.hi = ext->cursor->x;
        misc->y_pos.i.hi = ext->cursor->y;
        misc->unk2 = ext->cursor->object_id;
        ext->timer = 1;
        if (!(ext->cursor->flags & 0x80)) {
            ext->cursor++;
            break;
        }
        item = find_free_item_obj();
        if (item != NULL) {
            item->active = 1;
            item->id = 0x11;
            item->unk2 = ext->index - 8;
        }
        if (ext->index == 0xD) {
            arg0->state++;
        } else {
            ext->index++;
            arg0->unk5 = 1;
        }
        break;
    }
}

extern u16 D_8010B6C4[6];

void func_800B8E74(struct EffectObj* arg0)
{
    s8 index;

    if (g_Player.y_pos.i.hi < 0x500) {
        for (index = 0; index < 2; index++) {
            if (g_Player.x_pos.i.hi - (s16)D_8010B6C4[index] < 0)
                break;
        }
        if (index == 2)
            index = 1;
    } else {
        for (index = 2; index < 5; index++) {
            if (g_Player.x_pos.i.hi - (s16)D_8010B6C4[index] < 0)
                break;
        }
    }
    arg0->ext.effect_15.unk14 = index;
    if (index != arg0->ext.effect_15.unk15) {
        arg0->unk5 = index;
        arg0->unk6 = 0;
    }
}

extern u8 D_8010B534[];

void func_800B76A4(struct EffectObj* arg0)
{
    struct Effect9Ext* ext = &arg0->ext.effect_9;

    if (ext->direction != 0) {
        background_objects[2].y_pos.val = 0;
        ext->transition_timer = 1;
        background_objects[2].unk4C = 1;
        arg0->unk5 = 0;
        arg0->state--;
        return;
    }
    background_objects[2].y_pos.val = 0x1800000;
    background_objects[2].unk4C = 1;
    ext->movement_timer = 0x168;
    ext->movement_table = D_8010B534;
    ext->timer = ext->movement_table[0];
    ext->frame = ext->movement_table[1];
    ext->target_x = ext->movement_table[2];
    background_objects[2].x_pos.i.hi = (ext->target_x << 9) + (u8)background_objects[2].x_pos.i.hi;
    ext->velocity = 0x10000;
    arg0->unk5++;
}

extern u8 D_8010B528[];

void func_800B7764(struct EffectObj* arg0)
{
    struct Effect9Ext* ext = &arg0->ext.effect_9;
    s32 target;

    if (--ext->movement_timer == 0) {
        ext->movement_table = D_8010B528;
        ext->timer = ext->movement_table[0];
        ext->frame = ext->movement_table[1];
        ext->target_x = ext->movement_table[2];
        ext->movement_timer = 0xB4;
        if (ext->direction != 0)
            arg0->unk5--;
        else
            arg0->unk5++;
        return;
    }
    if (--ext->timer == 0) {
        ext->movement_table += ext->frame * 4;
        ext->target_x = ext->movement_table[2];
        ext->timer = ext->movement_table[0];
        ext->frame = ext->movement_table[1];
        background_objects[2].unk4C = 1;
        background_objects[2].x_pos.i.hi = (ext->target_x << 9) + (u8)background_objects[2].x_pos.i.hi;
    }
    if (ext->direction != 0) {
        if (ext->velocity > 0x18000)
            ext->velocity -= 0x400;
    } else if (ext->velocity <= 0x17FFF) {
        ext->velocity += 0x400;
    }
    background_objects[2].x_pos.val += ext->velocity;
    target = ext->target_x << 9;
    if (background_objects[2].x_pos.i.hi >= target + 0xC0) {
        background_objects[2].x_pos.i.hi = target;
        background_objects[2].unk4C = 1;
    }
    background_objects[2].y_pos.val -= 0x20000;
    if (background_objects[2].y_pos.val == 0x1000000) {
        background_objects[2].y_pos.val = 0x1800000;
        background_objects[2].unk4C = 1;
    }
}

extern void (*D_800FBEC0[])(struct MainObj*);
void func_80050690(struct MainObj* arg0);

void func_800500D4(struct MainObj* arg0)
{
    s32 collision;
    s16 x;
    s16 y;

    func_80050690(arg0);
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FBEC0[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    arg0->ext.main_17.unk90 = arg0->unk5;
    collision = func_8002DD04(arg0);
    x = arg0->x_pos.i.hi + arg0->unk68->unk0;
    y = arg0->unk68->unk3 + (u16)(arg0->y_pos.i.hi + arg0->unk68->unk1);
    if (func_8002D724(PLAYER_OBJECT(arg0), x, y) == 0x3E) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(4, D_800FBEB0, arg0);
        arg0->state = 2;
        return;
    }
    if (collision < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(4, D_800FBEB0, arg0);
        func_800BF60C(BASE_OBJECT(arg0), 0);
        arg0->state = 2;
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x40, 0x40) != 0) {
        arg0->state = 2;
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
}

void func_80050278(struct MainObj* arg0)
{
    struct Main17Ext* ext = &arg0->ext.main_17;
    s32 dx;

    if (--ext->unk80 != 0) {
        if (arg0->unk70 & 3)
            arg0->unk15 ^= 0x40;
        arg0->unk20 = arg0->unk15 != 0 ? 0x10000 : -0x10000;
        arg0->unk24 = 0x80000;
        ext->saved_unk5 = arg0->y_pos.val;
        func_8002B718(MOVING_OBJECT(arg0));
        func_80015DC8(ANIMATED_OBJECT(arg0));
        return;
    }

    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk24 = 0;
    arg0->unk2C = 0;
    dx = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if (dx < 0)
        dx = -dx;
    if (!(dx < 0x61 && arg0->y_pos.i.hi - g_Player.y_pos.i.hi < 0x11) && --ext->unk88 != 0) {
        if (--ext->unk84 == 0) {
            arg0->unk5 = 3;
            arg0->unk6 = 0;
            func_80015D60(arg0, 1);
        } else {
            arg0->unk7C = 0x14;
            arg0->unk5 = 6;
            arg0->unk6 = 0;
        }
        return;
    }
    arg0->unk20 = arg0->unk15 != 0 ? 0x30000 : -0x30000;
    arg0->unk28 = -0x1000;
    ext->unk8C = 1;
    arg0->unk5 = 4;
    arg0->unk6 = 0;
    func_80015D60(arg0, 2);
}

extern void (*D_800FB868[])(struct MainObj*);
extern u8 D_800FB84C[];
void func_8004CE48(struct MainObj* arg0);
void func_8004CE94(struct MainObj* arg0);

void func_8004C860(struct MainObj* arg0)
{
    func_8004CE48(arg0);
    func_8004CE94(arg0);
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FB868[arg0->unk5](arg0);
    if (arg0->state != 2)
        func_8002D9BC(arg0);
    arg0->ext.main_13.saved_unk5 = arg0->unk5;
    if (func_8002DD04(arg0) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(9, D_800FB84C, arg0);
        func_800BF60C(BASE_OBJECT(arg0), 8);
        arg0->unk7C = 0x20;
        arg0->unk7E = 6;
        arg0->on_screen = 0;
        arg0->state = 2;
        return;
    }
    if (arg0->state == 2)
        return;
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x68, 0x68) != 0) {
        arg0->state = 3;
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x48, 0x48);
}

void func_8004CEF4(struct AnimatedObj* arg0);

void func_8004CA94(struct MainObj* arg0)
{
    u8 roll;
    s32 dx;
    u32 animation;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    roll = get_random() & 0xF;
    dx = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if (dx < 0)
        dx = -dx;
    if (roll < 2) {
        arg0->unk7C = 0x3C;
        return;
    }
    if (roll < 4) {
        arg0->ext.main_13.unk80 = 0x8001;
        return;
    }
    animation = roll < (dx < 0x81 ? 12 : 8) ? 2 : 1;
    func_8004CEF4(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, animation);
    arg0->ext.main_13.unk88 = animation;
    arg0->unk5 = 4;
    arg0->unk6 = 0;
}

void func_8004CCA0(struct MainObj* arg0)
{
    struct ShotObj* shot;
    s8 event;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    event = arg0->animation_step.fields.event;
    if (event == 1) {
        func_80015D60(arg0, 0);
        arg0->ext.main_13.unk88 = 0;
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        return;
    }
    if (event != 2)
        return;
    func_8001540C(2, 0x31, arg0);
    if (arg0->animation_step.fields.event == 0)
        return;
    shot = find_free_shot_obj();
    if (shot == NULL)
        return;
    shot->active = 0x41;
    shot->id = 5;
    shot->unk2 = 0;
    shot->unk40 = arg0->unk40;
    shot->unk42 = arg0->unk42;
    shot->animation_table = (u32**)arg0->animation_table;
    shot->unk3C = (void*)arg0->sprite_frames;
    shot->unk15 = arg0->unk15;
    shot->bg_offset = arg0->bg_offset;
    shot->x_pos.val = arg0->x_pos.val;
    shot->unk84.collision_state = (u32*)&arg0->ext.main_13.unk80;
    shot->y_pos.val = arg0->y_pos.val;
    if (arg0->ext.main_13.unk88 == (u32)event)
        shot->state = 3;
}

extern u8 D_80108D04[28];
extern u8 D_80108D20[8];

void func_8009A5F4(struct ShotObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk58.data = (const u8*)D_80105FF0;
    arg0->unk42 &= 0x7FFF;
    if (arg0->unk15 != 0)
        arg0->x_pos.i.hi += 0x20;
    else
        arg0->x_pos.i.hi -= 0x20;
    arg0->y_vel.val = 0x70000;
    arg0->unk2C = 0x4200;
    arg0->unk16 = 0;
    arg0->y_pos.i.hi = (u16)arg0->y_pos.i.hi + 0x18;
    arg0->x_vel.val = arg0->unk15 != 0 ? 0x2C000 : -0x2C000;
    arg0->unk54 = D_80108D04;
    arg0->unk50.data = D_80108D04;
    arg0->unk5C = 6;
    arg0->unk68 = NULL;
    arg0->unk60 = 2;
    func_80015D60(arg0, 5);
}

void func_800B7CFC(struct EffectObj* arg0)
{
    struct Effect9Ext* ext = &arg0->ext.effect_9;
    s32 target;

    if (--ext->movement_timer == 0) {
        ext->direction = 1;
        ext->movement_timer = 0x78;
        ext->movement_table = D_8010B528;
        ext->timer = ext->movement_table[0];
        ext->frame = ext->movement_table[1];
        arg0->unk5--;
        ext->target_x = ext->movement_table[2];
        return;
    }
    if (--ext->timer == 0) {
        ext->movement_table += ext->frame * 4;
        ext->target_x = ext->movement_table[2];
        ext->timer = ext->movement_table[0];
        ext->frame = ext->movement_table[1];
        background_objects[2].unk4C = 1;
        background_objects[2].x_pos.i.hi = (ext->target_x << 9) + (u8)background_objects[2].x_pos.i.hi;
    }
    if (ext->velocity <= 0x47FFF)
        ext->velocity += 0x400;
    background_objects[2].x_pos.val += ext->velocity;
    target = ext->target_x << 9;
    if (background_objects[2].x_pos.i.hi >= target + 0xC0) {
        background_objects[2].x_pos.i.hi = target;
        background_objects[2].unk4C = 1;
    }
    background_objects[2].y_pos.val -= 0x20000;
    if (background_objects[2].y_pos.val == 0x1000000) {
        background_objects[2].y_pos.val = 0x1800000;
        background_objects[2].unk4C = 1;
    }
}

extern union AnimationStep* D_8010DF48[57];

void func_800C9510(struct MiscObj* arg0)
{
    s32 resource;
    u8 alternate;

    arg0->animation_table = (u32**)D_8010DF48;
    alternate = (u8)arg0->unk2 >> 7;
    arg0->ext.misc_8.alternate = alternate;
    arg0->unk2 &= 0x7F;
    arg0->state++;
    arg0->bg_offset = g_Player.bg_offset;
    resource = func_8002938C(0x99);
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    resource = func_8002938C(0x99);
    arg0->unk40 = D_801406A8[resource] >> 7;
    resource = func_8002938C(0x99);
    arg0->unk42 = SOME_COORDINATE_CONVERSION(resource);
    arg0->unk16 = 7;
    arg0->unk15 = 0;
    if ((u8)(arg0->unk2 - 0xD) < 6) {
        arg0->unk15 = 0x40;
        arg0->x_pos.i.hi += 0x10;
    }
    arg0->ext.misc_8.timer = 0;
    if (arg0->ext.misc_8.alternate != 0)
        func_80015D60(arg0, D_8010E090.entries[arg0->unk2].first);
    else
        func_80015D60(arg0, D_8010E058[arg0->unk2].effect_id);
}

void func_800C833C(s32 count, u8* variants, struct MiscObj* owner, s32 x_offset, s32 y_offset)
{
    struct MiscObj* misc;

    while (count & 0xFF) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 3;
            misc->unk2 = 0;
            misc->unk15 = get_random() & 0x40;
            misc->state = 0;
            misc->unk5 = 0;
            misc->unk6 = 0;
            misc->x_pos.val = owner->x_pos.val + (get_random() & 3) + x_offset;
            misc->y_pos.val = owner->y_pos.val + (get_random() & 3) + y_offset;
            misc->ext.misc_2.owner = MAIN_OBJECT(owner);
            misc->ext.misc_2.unk58 = *variants++;
        }
        count--;
    }
}

extern u8 D_8010D198[4];
extern u8* D_8010D1BC[4];
extern struct Unk_unk68 D_80106270[32];

void func_800C42EC(struct ItemObj* arg0)
{
    static const s32 offsets[7][3] = {
        { 0, 0x300000, 0x200000 },
        { 1, -0x200000, 0x100000 },
        { 2, 0, 0 },
        { 3, 0x180000, -0x100000 },
        { 0, -0x180000, -0x200000 },
        { 1, 0x100000, -0x180000 },
        { 2, -0x100000, 0x180000 },
    };
    s32 resource;
    s32 i;

    if (arg0->state == 0) {
        arg0->state++;
        arg0->unk58 = (const u8*)D_80106270;
        arg0->unk54 = D_8010D198;
        arg0->animation_table = (const u8* const*)D_8010DF48;
        arg0->bg_offset = g_Player.bg_offset;
        resource = func_8002938C(0x99);
        arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
        resource = func_8002938C(0x99);
        arg0->unk40 = D_801406A8[resource] >> 7;
        resource = func_8002938C(0x99);
        arg0->unk42 = SOME_COORDINATE_CONVERSION(resource);
        arg0->unk16 = 7;
        arg0->unk15 = 0;
        return;
    }
    if (func_8002DD04(MAIN_OBJECT(arg0)) != 0) {
        func_800DABE4(0x26, 0x430, 0x170);
        get_random();
        for (i = 0; i < 7; i++)
            func_800C833C(5, D_8010D1BC[offsets[i][0]], (struct MiscObj*)arg0,
                offsets[i][1], offsets[i][2]);
        func_8002B108(OBJECT_HEADER(arg0));
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x70, 0x50) == 1)
        func_8002B0C8(OBJECT_HEADER(arg0));
}

extern union AnimationStep* D_800FCE04[];
extern struct Unk_unk68 D_800FCB48[];
extern struct Unk_unk68 D_800FCB4C[2];
extern struct VisualSpawnOffset D_800FCE90[5];
extern struct Unk_unk68 D_800FCE9C[];
extern union AnimationStep D_800FCF1C[];
extern struct Unk_unk68 D_80106DF4[];

void func_80055C54(struct MainObj* arg0)
{
    struct Main23Ext* ext = &arg0->ext.main_23;
    s16 x = arg0->x_pos.i.hi;
    s16 y = (u16)arg0->y_pos.i.hi + (s8)arg0->unk68->unk1 + arg0->unk68->unk3 + 1;
    u8 tile;

    ext->unk81 = ext->unk80;
    tile = func_8002D724(PLAYER_OBJECT(arg0), x, y);
    if (tile == 0) {
        tile = func_8002D724(PLAYER_OBJECT(arg0), x, y + 0x10);
        if (tile == 0) {
            ext->unk80 = 3;
            return;
        }
    }
    if ((u8)(tile - 0x11) < 0xE) {
        if (tile < 0x19) {
            ext->unk80 = 1;
            if (tile < 0x15 ? arg0->unk15 != 0 : arg0->unk15 == 0)
                ext->unk80 = 0x81;
        } else {
            ext->unk80 = 2;
            if (tile < 0x1B ? arg0->unk15 != 0 : arg0->unk15 == 0)
                ext->unk80 = 0x82;
        }
        return;
    }
    if (tile == 0x3E) {
        if (arg0->on_screen != 0) {
            func_800AF808(BASE_OBJECT(arg0));
            func_800C813C(7, D_800FCE80, arg0);
            arg0->state++;
        }
        return;
    }
    if (tile != 0x10)
        ext->unk80 = 0;
}

void func_800564B4(struct MainObj* arg0)
{
    arg0->unk5 = 1;
    arg0->state++;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->bg_offset = g_Player.bg_offset;
    switch (arg0->unk2) {
    case 0:
        arg0->unk15 = g_Player.x_pos.val < arg0->x_pos.val ? 0 : 0x40;
        break;
    case 1:
        arg0->unk15 = 0;
        break;
    case 2:
        arg0->unk15 = 0x40;
        break;
    }
    arg0->animation_table = (const u8* const*)D_800FCE04;
    arg0->unk16 = 6;
    arg0->unk68 = D_800FCB48;
    arg0->unk54 = D_800FCB4C;
    arg0->unk50 = D_800FCB4C;
    arg0->unk5C = 3;
    arg0->unk60 = 1;
    arg0->collision_data = (const u16*)D_80106DF4;
    arg0->ext.main_23.unk80 = 0;
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk24 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk7C = 10;
    arg0->ext.main_23.unk81 = 0;
    arg0->ext.main_23.unk82 = 0;
    func_80015D60(arg0, arg0->ext.main_23.unk80 + 4);
}

void func_80055F1C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->ext.main_23.unk80 & 0x80) {
        arg0->unk24 = 0x40000;
        arg0->unk20 = arg0->unk15 != 0 ? 0x30000 : -0x30000;
    } else {
        arg0->unk24 = 0x38000;
        arg0->unk20 = arg0->unk15 != 0 ? 0x48000 : -0x48000;
    }
    arg0->unk2C = 0x4200;
    arg0->unk67 = 1;
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk6++;
        func_80015D60(arg0, 0x11);
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
}

static struct VisualObj* main_23_spawn_visual(struct MainObj* arg0, u8 facing)
{
    struct VisualObj* visual = find_free_visual_obj();

    if (visual == NULL)
        return NULL;
    visual->active = 0x41;
    visual->id = 3;
    visual->unk2 = 5;
    visual->bg_offset = arg0->bg_offset;
    visual->unk15 = facing;
    visual->unk40 = arg0->unk40;
    visual->unk3C = (void*)arg0->sprite_frames;
    visual->animation_table = (u32**)arg0->animation_table;
    visual->unk42 = arg0->unk42;
    return visual;
}

void func_80056054(struct MainObj* arg0)
{
    struct VisualObj* visual;
    u8 i;

    if (arg0->unk6 == 0) {
        arg0->unk6++;
        func_80015D60(arg0, arg0->ext.main_23.unk80 + 0xA);
        return;
    }
    if (arg0->unk6 != 1)
        return;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 1) {
        if (arg0->ext.main_23.unk82 & 1) {
            arg0->unk5 = 1;
            arg0->unk6 = 0;
            arg0->ext.main_23.unk82 &= 0xFE;
            arg0->unk15 ^= 0x40;
        }
        return;
    }
    if (arg0->animation_step.fields.event != 2)
        return;
    for (i = 0; i < 5; i++) {
        visual = main_23_spawn_visual(arg0, arg0->unk15 ^ 0x40);
        if (visual == NULL)
            continue;
        if (arg0->unk15 != 0)
            visual->x_pos.i.hi = arg0->x_pos.i.hi - D_800FCE90[i].x;
        else
            visual->x_pos.i.hi = arg0->x_pos.i.hi + D_800FCE90[i].x;
        visual->y_pos.i.hi = (u16)arg0->y_pos.i.hi + D_800FCE90[i].y;
        visual->unk16 = arg0->unk16;
        arg0->animation_step.fields.event = 0;
    }
}

void func_800562AC(struct MainObj* arg0)
{
    struct Main23Ext* ext = &arg0->ext.main_23;
    struct VisualObj* visual;
    u8 wall;

    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80055C54(arg0);
    if (ext->unk81 != ext->unk80) {
        if (ext->unk80 == 3 || (ext->unk80 & 0x80)) {
            arg0->unk5 = 4;
            arg0->unk6 = 0;
            func_80015D60(arg0, ext->unk81 + 0xD);
        } else {
            func_80015D60(arg0, (ext->unk80 & 0x7F) + 4);
        }
    }
    wall = arg0->unk15 != 0 ? arg0->unk70 & 1 : arg0->unk70 & 2;
    if (wall) {
        arg0->unk5 = 5;
        arg0->unk6 = 0;
        ext->unk82 |= 1;
    }
    if (--arg0->unk7C != 0)
        return;
    visual = main_23_spawn_visual(arg0, arg0->unk15);
    if (visual == NULL)
        return;
    visual->x_pos.i.hi = arg0->unk15 != 0 ? arg0->x_pos.i.hi - 0x28 : arg0->x_pos.i.hi + 0x28;
    visual->y_pos.i.hi = (u16)arg0->y_pos.i.hi + (s8)(ext->unk80 < 0x80 ? ((u8*)D_800FCE9C)[ext->unk80] : ((u8*)D_800FCF1C)[ext->unk80 - 0x80]);
    visual->unk16 = arg0->unk16;
    arg0->unk7C = 5;
}

void func_800B8630(struct EffectObj* arg0)
{
    struct MainObj* main = find_free_main_obj();
    s32 resource;
    s32 row;

    if (main == NULL)
        return;
    main->active = 0x41;
    main->id = 0x15;
    main->unk2 = func_8002B780() % 4;
    main->x_pos.val = arg0->x_pos.val;
    main->y_pos.val = arg0->y_pos.val;
    main->unk40 = D_801406A8[(u8)func_8002938C(0x15)] >> 7;
    resource = (u8)func_8002938C(0x15);
    row = (u8)func_8002938C(0x15);
    main->unk42 = ((resource * 4 + 0x18) % 16) | ((((row + 6) / 4) + 0x1E0) << 6);
    resource = (u8)func_8002938C(0x15);
    main->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
}

void func_800B875C(struct EffectObj* arg0, s16 unused)
{
    s16 x;
    s16 y;
    u8 i;

    x = arg0->x_pos.i.hi - 0x10;
    arg0->x_pos.i.hi = x;
    y = arg0->y_pos.i.hi - 0x10;
    if (func_8002D724(PLAYER_OBJECT(arg0), x, y) != 0) {
        for (i = 1; i < 0x10; i++) {
            if (func_8002D724(PLAYER_OBJECT(arg0), arg0->x_pos.i.hi, y + i * 16) == 0) {
                arg0->y_pos.i.hi += i * 16;
                func_800B8630(arg0);
                return;
            }
        }
        return;
    }
    for (i = 1; i < 0x10; i++) {
        if (func_8002D724(PLAYER_OBJECT(arg0), arg0->x_pos.i.hi, y - i * 16) != 0) {
            arg0->y_pos.i.hi -= (i - 1) * 16;
            func_800B8630(arg0);
            return;
        }
    }
}

extern void (*D_800FCA0C[])(struct MainObj*);
extern u8 D_800FC9F0[];

void func_80054D8C(struct MainObj* arg0)
{
    s32 collision;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FCA0C[arg0->unk5](arg0);
    arg0->ext.main_21.saved_unk5 = arg0->unk5;
    collision = func_8002DD04(arg0);
    func_8002D9BC(arg0);
    if (collision < 0 || func_8002BB80(arg0, MAIN_OBJECT(&g_Player)) != 0 || (arg0->unk70 & 8)) {
        func_80015D60(arg0, 4);
        func_800C813C(3, D_800FC9F0, arg0);
        func_8001540C(5, 1, NULL);
        arg0->state = 2;
        return;
    }
    if (func_8002B160(BASE_OBJECT(arg0)) != 0) {
        arg0->state = 3;
        return;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

extern void* D_8010CB40[];
extern struct Unk_unk68 D_8010CB28[];

void func_800C16F0(struct ItemObj* arg0)
{
    s32 resource;
    s32 row;

    arg0->active = 0x41;
    arg0->animation_table = (const u8* const*)D_8010CB40;
    arg0->state++;
    arg0->bg_offset = g_Player.bg_offset;
    resource = func_8002938C(0x87);
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->unk40 = D_801406A8[func_8002938C(0x87)] >> 7;
    resource = func_8002938C(0x87);
    row = func_8002938C(0x87);
    arg0->unk42 = ((resource * 4 + 0x18) % 16) | ((((row + 6) / 4) + 0x1E0) << 6);
    arg0->unk16 = 6;
    arg0->unk15 = 0;
    arg0->unk68 = D_8010CB28;
    func_80015D60(ANIMATED_OBJECT(arg0), 0);
    arg0->unk76 = 0;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0x8000;
    arg0->unk7C.value = 0;
}

extern void* D_800FC2B4[];
extern struct Unk_unk68 D_800FBF0C;
extern void (*D_800FC358[])(struct MainObj*);
extern u8 D_800FC33C[];
void func_800527C0(struct AnimatedObj* arg0);
void func_800527F0(struct MainObj* arg0);
void func_80052524(struct MainObj* arg0);
void func_80052614(struct MainObj* arg0);
void func_800526AC(struct MainObj* arg0);

void func_8005077C(struct MainObj* arg0)
{
    struct Main18Ext* ext = &arg0->ext.main_18;

    arg0->unk60 = 4;
    arg0->unk61 = -0x80;
    arg0->unk5C = 0;
    arg0->collision_data = (const u16*)D_80106B74;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->animation_table = (const u8* const*)D_800FC2B4;
    arg0->unk16 = 0x22;
    arg0->unk67 = 0;
    arg0->unk68 = &D_800FBF0C;
    arg0->unk54 = NULL;
    arg0->unk50 = NULL;
    func_800527C0(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 0x21);
    ext->unk8A = 0x8000;
    *(u8*)&arg0->unk7E = 0xFF;
    ext->unk80 = 0;
    ext->unk81 = 0;
    ext->unk82 = 0;
    ext->unk83 = 0;
    ext->unk84 = 0;
    ext->unk85 = 0;
    ext->unk86 = 0;
    ext->unk87 = 0;
    ext->unk88 = 1;
    ext->unk89 = 0;
    ext->unk82 = 1;
    ext->unk8A = 0;
    ext->unk8C = 0;
    ext->unk90 = 0;
    arg0->state = 1;
    arg0->unk5 = 0xB;
    arg0->unk6 = 0;
}

void func_80050874(struct MainObj* arg0)
{
    struct Main18Ext* ext = &arg0->ext.main_18;
    s32 hit;
    u8 invulnerable;

    func_80052524(arg0);
    func_80052614(arg0);
    func_800526AC(arg0);
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FC358[arg0->unk5](arg0);
    if (arg0->state >= 2) {
        func_8002B318(BASE_OBJECT(arg0), 0x80, 0x80);
        return;
    }
    invulnerable = arg0->unk61;
    if (invulnerable & 0x7F) {
        arg0->unk61 = invulnerable - 1;
        if ((u8)(invulnerable - 1) == 0)
            arg0->unk42 &= 0x7FFF;
    } else {
        ext->saved_unk5 = arg0->unk5;
        hit = func_8002DD04(arg0);
        if (hit < 0) {
            g_Player.unk61 = 0x7F;
            func_8001540C(5, 2, NULL);
            func_800AF808(BASE_OBJECT(arg0));
            g_Player.unk7A = 1;
            func_800C813C(4, D_800FC33C, arg0);
            arg0->unk7C = 4;
            arg0->unk7E = 8;
            ext->unk8A = 0;
            ext->unk89 = 0;
            arg0->unk68 = NULL;
            arg0->state = 2;
            arg0->unk42 &= 0x7FFF;
            return;
        }
        if (hit == 0 || hit == 0x7F) {
            ext->unk87 = 0;
        } else {
            arg0->unk61 = engine_obj.cur_character != 0 ? 1 : 6;
            ext->unk87 = 1;
            arg0->unk42 |= 0x8000;
            if (!(ext->unk80 & 0xC0))
                ext->unk80 = (ext->unk80 | 0x40) + 1;
            if (ext->unk81 != 0) {
                switch (hit - 1) {
                case 0:
                    ext->unk83 += 2;
                    break;
                case 9:
                case 23:
                case 24:
                case 25:
                case 26:
                    ext->unk83 += 5;
                    break;
                case 18:
                    ext->unk83 += 10;
                    break;
                }
            }
        }
    }
    func_8002D9BC(arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x80, 0x80);
}

void func_80050A9C(struct MainObj* arg0)
{
    s32 saved[2];

    arg0->y_pos.i.hi++;
    if (arg0->y_pos.i.hi >= 0x931) {
        func_800DABE4(0x17, 0, 0);
        engine_obj.enable_boss = 0;
        engine_obj.boss_ptr = NULL;
        arg0->state = 3;
        func_8002B318(BASE_OBJECT(arg0), 0x80, 0x80);
        return;
    }
    if (--arg0->unk7C == 0) {
        arg0->unk7C = 4;
        func_800AF95C(OBJECT_HEADER(arg0), 1, 0x20, 0x30, 2);
    }
    if (--arg0->unk7E == 0) {
        saved[0] = arg0->x_pos.val;
        saved[1] = arg0->y_pos.val;
        memcpy(&arg0->ext.main_18.unk80, saved, sizeof(saved));
        arg0->unk7E = 8;
        arg0->x_pos.i.hi = 0x18E2;
        arg0->y_pos.i.hi = 0x89E;
        func_800AF95C(OBJECT_HEADER(arg0), 1, 0x18, 0x30, 2);
        memcpy(saved, &arg0->ext.main_18.unk80, sizeof(saved));
        arg0->x_pos.val = saved[0];
        arg0->y_pos.val = saved[1];
    }
    func_8002B318(BASE_OBJECT(arg0), 0x80, 0x80);
}

void func_80050D14(struct MainObj* arg0)
{
    if (arg0->unk15 == 0 ? (arg0->unk70 & 2) : (arg0->unk70 & 1)) {
        if (arg0->ext.main_18.unk84 != 0) {
            func_800527C0(ANIMATED_OBJECT(arg0));
            func_80015D60(arg0, 6);
            arg0->unk5 = 3;
            arg0->unk6 = 2;
        } else {
            arg0->unk15 = arg0->unk15 == 0 ? 0x40 : 0;
            func_800527F0(arg0);
        }
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk24 == 0x30000)
        arg0->unk2C = 0x2000;
    if (arg0->unk24 == -0x30000)
        arg0->unk2C = -0x2000;
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80052218(struct MainObj* arg0)
{
    u32 i;

    for (i = 0; i < 0x20; i++) {
        if (item_objects[i].id != 8)
            item_objects[i].active = 0;
    }
    arg0->unk24 = 0x10000;
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk7C = 0x74;
    func_80036AE4(0x15, 0);
    arg0->unk6 = 1;
}

void func_800527F0(struct MainObj* arg0)
{
    arg0->unk5 = 7;
    arg0->unk6 = 0;
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk24 = 0;
    if (arg0->ext.main_18.unk84 == 0)
        arg0->unk2C = arg0->y_pos.i.hi < 0x891 ? 0x1000 : -0x1000;
    else
        arg0->unk2C = arg0->y_pos.i.hi >= 0x8B1 ? -0x1000 : 0x1000;
}

extern u16 D_800FBEDC[12];
extern struct Unk_unk68 D_800FBF08;

void func_800517D0(struct MainObj* arg0)
{
    struct Main18Ext* ext = &arg0->ext.main_18;
    struct ShotObj* shot;
    struct MiscObj* misc;
    s16 i;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 3) {
        for (i = 0; i < 10; i++) {
            if (D_800FBEDC[i] & ext->unk8A)
                continue;
            shot = find_free_shot_obj();
            if (shot == NULL)
                continue;
            shot->active = 0x41;
            shot->id = 0xC;
            shot->unk2 = i;
            shot->unk40 = arg0->unk40;
            shot->unk42 = arg0->unk42;
            shot->animation_table = (u32**)arg0->animation_table;
            shot->unk3C = (void*)arg0->sprite_frames;
            shot->x_pos.val = (i << 21) + 0x17B10000;
            shot->y_pos.val = 0x8200000;
            shot->state = 3;
            shot->unk15 = 0;
            shot->unk7C = (struct WeaponObj*)&ext->unk8A;
            shot->bg_offset = arg0->bg_offset;
        }
        ext->unk8A = 0x83FF;
    }
    if (arg0->animation_step.fields.event == 4) {
        arg0->unk50 = (const u8*)&D_800FBF08;
        arg0->unk54 = (const u8*)&D_800FBF08;
    }
    if (arg0->animation_step.fields.event == 2) {
        func_8001540C(2, 0x34, arg0);
        for (i = 0; i < 8; i++) {
            misc = find_free_misc_obj();
            if (misc == NULL)
                continue;
            misc->active = 0x41;
            misc->id = 6;
            misc->unk2 = i;
            misc->unk40 = arg0->unk40;
            misc->unk42 = arg0->unk42 & 0x7FFF;
            misc->animation_table = (u32**)arg0->animation_table;
            misc->unk3C = (void*)arg0->sprite_frames;
            misc->bg_offset = arg0->bg_offset;
            misc->x_pos.val = arg0->x_pos.val;
            misc->unk15 = 0;
            misc->state = 0;
            misc->y_pos.val = arg0->y_pos.val;
        }
        arg0->unk61 = -0x80;
    }
    if (arg0->animation_step.fields.event != 1)
        return;
    if (ext->unk88 == 0) {
        arg0->unk50 = (const u8*)&D_800FBEF8;
        arg0->unk54 = (const u8*)&D_800FBEF8;
        func_80015D60(arg0, 0xA);
    } else {
        func_800527C0(ANIMATED_OBJECT(arg0));
        arg0->unk50 = (const u8*)&D_800FBEF4;
        arg0->unk54 = (const u8*)&D_800FBEF4;
        func_80015D60(arg0, 9);
    }
    ext->unk85 = 3;
    arg0->unk6 = 2;
}

void func_800C91EC(struct MiscObj* arg0)
{
    func_80015D60(arg0, arg0->unk2 + 0x11);
    arg0->ext.misc_6.saved_position.position.x = arg0->x_pos.i.hi;
    arg0->ext.misc_6.saved_position.position.y = arg0->y_pos.i.hi;
    func_8002B93C(MOVING_OBJECT(arg0), (arg0->unk2 * 4) & 0xFC);
    arg0->ext.misc_6.timer = 0x14;
    arg0->state = 1;
    arg0->x_pos.val += arg0->x_vel.val * 180;
    arg0->y_pos.val -= arg0->y_vel.val * 180;
    arg0->x_vel.val = -(arg0->x_vel.val * 4);
    arg0->y_vel.val = -(arg0->y_vel.val * 4);
}

extern u8 D_80108E68[4];
extern u8 D_80108E6C[4];
extern u8 D_80108E70[4];
extern u8 D_80108E98[4];

void func_8009B85C(struct ShotObj* arg0)
{
    const u8* offsets = (const u8*)&D_80108E74 + 0x14 + arg0->unk2 * 2;

    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk58.data = (const u8*)D_80105FF0;
    arg0->unk42 &= 0x7FFF;
    func_8002B93C(MOVING_OBJECT(arg0), (arg0->unk2 * 4) & 0xFC);
    arg0->y_vel.val *= 6;
    arg0->y_pos.i.hi = (u16)arg0->y_pos.i.hi + (s8)offsets[1];
    if (arg0->unk15 == 0) {
        arg0->x_vel.val *= 6;
        arg0->x_pos.i.hi = (u16)arg0->x_pos.i.hi + (s8)offsets[0];
    } else {
        arg0->x_vel.val = -(arg0->x_vel.val * 6);
        arg0->x_pos.i.hi = (u16)arg0->x_pos.i.hi - (s8)offsets[0];
    }
    arg0->unk54 = D_80108E68;
    arg0->unk50.data = D_80108E68;
    arg0->unk5C = 6;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->unk60 = 3;
    func_80015D60(arg0, arg0->unk2 + 0x11);
}

void func_8009BA6C(struct ShotObj* arg0)
{
    arg0->state = 4;
    arg0->unk58.data = (const u8*)D_80105FF0;
    arg0->unk68 = (struct Unk_unk68*)D_80108E70;
    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->unk54 = D_80108E6C;
    arg0->unk50.data = D_80108E6C;
    arg0->unk16 = 0;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk60 = 3;
    arg0->unk42 &= 0x7FFF;
    func_80015D60(arg0, 0x1D);
}

extern u8 D_8013B8E4[4];

void func_800AF95C(struct ObjectHeader* arg0, s32 type, s32 x_range, s32 y_range, s32 divisor)
{
    s16 x;
    s16 y;
    s32 roll;
    u8 variant;

    x_range &= get_random();
    if (get_random() & 1)
        x = arg0->x_pos.u.hi + (x_range & 0xFF);
    else
        x = arg0->x_pos.u.hi - (x_range & 0xFF);
    y_range &= get_random();
    if (get_random() & 1)
        y = arg0->y_pos.u.hi + (y_range & 0xFF);
    else
        y = arg0->y_pos.u.hi - (y_range & 0xFF);
    roll = func_8002B780();
    divisor &= 0xFF;
    if (divisor == 0 || roll % divisor == 0) {
        D_8013B8E4[0]++;
        variant = (D_8013B8E4[0] & 1) ? 2 : 3;
    } else {
        variant = 0xFF;
    }
    func_800AFAB4((s8)type, x, y, variant);
}

extern union AnimationStep* D_800FD1B8[];
extern struct Unk_unk68 D_80106F74[];
extern struct Unk_unk68 D_800FD19C[];
extern void (*D_800FD1E8[])(struct MainObj*);

void func_80058194(struct MainObj* arg0)
{
    arg0->state++;
    arg0->unk5 = 2;
    arg0->unk2 = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->animation_table = (const u8* const*)D_800FD1B8;
    arg0->unk16 = 6;
    arg0->collision_data = (const u16*)D_80106F74;
    arg0->unk54 = (const u8*)D_800FD19C;
    arg0->unk60 = 3;
    arg0->unk5C = 9;
    arg0->ext.main_26.last_health = 9;
    arg0->ext.main_26.stage = 2;
    arg0->unk15 = 0;
    arg0->unk68 = NULL;
    arg0->unk50 = NULL;
    arg0->unk61 = 0;
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk24 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->x_pos.i.hi &= ~0xF;
    arg0->y_pos.i.hi &= ~0xF;
}

void func_80058254(struct MainObj* arg0)
{
    struct Main26Ext* ext = &arg0->ext.main_26;
    s32 hit = func_8002DD04(arg0);
    s8 stage;

    if (ext->last_health != arg0->unk5C) {
        stage = ext->stage--;
        if (stage == 1) {
            func_800583B0(arg0, arg0->x_pos.i.hi, arg0->y_pos.i.hi, 5);
            arg0->unk5C = 1;
        } else if (stage == 2) {
            func_800583B0(arg0, arg0->x_pos.i.hi, arg0->y_pos.i.hi, 0);
        }
        ext->last_health = arg0->unk5C;
    }
    if (func_8002D724(PLAYER_OBJECT(arg0), arg0->x_pos.i.hi, arg0->y_pos.i.hi - 0x10) == 0 || hit < 0) {
        arg0->unk5 = 0;
        arg0->state++;
        arg0->unk42 &= 0x7FFF;
        func_8001540C(5, 1, NULL);
        return;
    }
    D_800FD1E8[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x50, 0x30) != 0)
        func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_800583B0(struct MainObj* arg0, s16 x, s16 y, s32 base)
{
    u8 above;
    u8 below;
    u8 tile;
    s16 left = (x & -0x10) - 0x10;
    s16 top = y & -0x10;

    above = func_8002D724(PLAYER_OBJECT(arg0), x, y - 0x20);
    if (above != 0x38)
        above = func_8002D724(PLAYER_OBJECT(arg0), x, y - 0x30);
    below = func_8002D724(PLAYER_OBJECT(arg0), x, y + 0x30);

    switch (above) {
    case 0x31:
        tile = 2;
        break;
    case 0:
        tile = 3;
        break;
    case 0x30:
        tile = 1;
        break;
    case 0x3C:
        tile = 0;
        break;
    default:
        tile = 4;
        break;
    }
    func_800DABE4(tile + base, left, top - 0x20);

    switch (below) {
    case 0x31:
        tile = 0x11;
        break;
    case 0:
        tile = 0x12;
        break;
    case 0x30:
        tile = 0x10;
        break;
    case 0x3C:
        tile = 0xF;
        break;
    default:
        tile = 0x13;
        break;
    }
    func_800DABE4(tile + base, left, top + 0x10);

    base &= 0xFF;
    func_800DABE4(base == 0 ? 0x1E : base == 5 ? 0x1F
                                               : 0x20,
        left, top);
}

extern union AnimationStep* D_800FD358[];
extern struct Unk_unk68 D_800FD200[10];
extern struct Unk_unk68* D_8013B828;
extern struct Unk_unk68* D_8013B82C;
extern struct Unk_unk68* D_8013B830;
extern struct Unk_unk68* D_8013B834;
extern void (*D_800FD39C[])(struct MainObj*);
extern struct Unk_unk68 D_80106FF4[];
extern u8 D_800FD388[];

void func_80058740(struct MainObj* arg0)
{
    struct Main27Ext* ext = &arg0->ext.main_27;
    u8 subtype;

    arg0->unk5C = 6;
    arg0->unk61 = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk67 = 0;
    arg0->animation_table = (const u8* const*)D_800FD358;
    arg0->unk16 = 6;
    arg0->unk54 = NULL;
    arg0->unk50 = NULL;
    arg0->unk70 = 0;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    ext->unk8B = 0;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;

    switch ((u8)arg0->unk2) {
    case 0:
    case 4:
        arg0->unk20 = -0x18000;
        ext->unk90 = 0;
        arg0->unk15 = 0;
        ext->unk80 = 0;
        ext->unk8C = 0x1E;
        func_8001540C(2, 0x51, arg0);
        arg0->unk5 = 2;
        break;
    case 1:
    case 5:
        arg0->unk15 = 0x40;
        ext->unk8C = 0x1E;
        arg0->unk5 = 3;
        ext->unk90 = 0;
        arg0->unk20 = 0x18000;
        ext->unk80 = 0;
        arg0->unk7A = 1;
        break;
    case 2:
    case 6:
        ext->unk82 = 0x1E;
        ext->unk80 = 1;
        ext->unk8C = 0x12C;
        ext->unk90 = 0;
        arg0->unk15 = 0;
        ext->unk88 = 0;
        ext->unk89 = 0x14;
        ext->unk8A = 0;
        func_8001540C(2, 0x51, arg0);
        arg0->unk5 = 6;
        break;
    case 3:
    case 7:
        arg0->unk15 = 0x40;
        ext->unk82 = 0x1E;
        ext->unk8C = 0x12C;
        ext->unk89 = 0x14;
        ext->unk90 = 0;
        ext->unk80 = 1;
        ext->unk88 = 1;
        ext->unk8A = 0;
        arg0->unk7A = 1;
        arg0->unk5 = 3;
        break;
    case 8:
    case 9:
    case 10:
    case 11:
        subtype = arg0->unk2;
        ext->unk90 = subtype < 10 ? 1 : 2;
        ext->unk91 = 0x30;
        if (subtype >= 10)
            ext->unk92 = 2;
        arg0->unk15 = (subtype & 1) ? 0x40 : 0;
        ext->unk80 = 0;
        ext->unk8A = 0;
        func_8001540C(2, 0x51, arg0);
        arg0->unk20 = (subtype & 1) ? 0x18000 : -0x18000;
        arg0->unk5 = 2;
        break;
    }

    subtype = arg0->unk2;
    if (subtype < 4 || (u8)(subtype - 8) < 4) {
        arg0->unk60 = 6;
        arg0->unk68 = &D_800FD200[4];
        D_8013B828 = &D_800FD200[0];
        D_8013B82C = &D_800FD200[1];
        D_8013B830 = &D_800FD200[3];
        D_8013B834 = &D_800FD200[2];
    } else {
        arg0->unk60 = 7;
        arg0->unk68 = &D_800FD200[9];
        D_8013B828 = &D_800FD200[5];
        D_8013B82C = &D_800FD200[6];
        D_8013B830 = &D_800FD200[8];
        D_8013B834 = &D_800FD200[7];
    }
    func_80015D60(arg0, 1);
    arg0->state = 1;
    arg0->unk6 = 0;
}

void func_80058AC8(struct MainObj* arg0)
{
    struct Main27Ext* ext = &arg0->ext.main_27;
    s32 facing_player;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FD39C[arg0->unk5](arg0);
    if (engine_obj.stage == 3 && arg0->x_pos.i.hi < 0x20)
        arg0->x_pos.i.hi = 0x20;
    if ((u8)arg0->unk2 < 4) {
        if (arg0->x_pos.i.hi > 0x780)
            arg0->x_pos.i.hi = 0x780;
    } else if (arg0->x_pos.i.hi > 0x980) {
        arg0->x_pos.i.hi = 0x980;
    }
    if (arg0->unk5 == 3)
        return;
    ext->saved_unk5 = arg0->unk5;
    ext->unk84 = g_Player.x_pos.val;
    if (arg0->state != 2) {
        arg0->unk50 = (const u8*)(ext->unk8B != 0 ? D_8013B82C : D_8013B828);
        func_8002D9BC(arg0);
        arg0->unk50 = (const u8*)D_8013B834;
        func_8002D9BC(arg0);
    }
    facing_player = arg0->unk15 == 0 ? g_Player.x_pos.i.hi < arg0->x_pos.i.hi
                                     : arg0->x_pos.i.hi < g_Player.x_pos.i.hi;
    if (ext->unk8B == 0 && facing_player) {
        arg0->collision_data = (const u16*)D_801060F0;
        arg0->unk54 = (const u8*)D_8013B828;
        func_8002DD04(arg0);
    } else {
        arg0->collision_data = (const u16*)D_80106FF4;
        arg0->unk54 = (const u8*)D_8013B830;
        if (func_8002DD04(arg0) < 0) {
            func_800AF808(BASE_OBJECT(arg0));
            func_800C813C(4, D_800FD388, arg0);
            func_800BF60C(BASE_OBJECT(arg0), 0x11);
            arg0->unk7C = 0x20;
            arg0->unk7E = 6;
            arg0->on_screen = 0;
            func_80015930(2, 0x51);
            arg0->state = 2;
            return;
        }
    }
    if (arg0->state == 2)
        return;
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x60, 0x60) != 0) {
        func_80015930(2, 0x51);
        arg0->state = 3;
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

static void main_27_halt(struct MainObj* arg0)
{
    func_80015D60(arg0, 3);
    arg0->unk20 = 0;
    func_80015930(2, 0x51);
    arg0->unk5 = 5;
    arg0->unk6 = 0;
}

static void main_27_turn(struct MainObj* arg0)
{
    arg0->unk7C = 0x14;
    arg0->unk24 = 0;
    arg0->unk5 = 4;
    arg0->unk6 = 0;
}

void func_80058E38(struct MainObj* arg0)
{
    struct Main27Ext* ext = &arg0->ext.main_27;

    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--ext->unk8C == 0) {
        main_27_halt(arg0);
        return;
    }
    if (ext->unk90 != 0 && --ext->unk91 == 0) {
        if (ext->unk90 == 2) {
            ext->unk91 = 0x30;
            if (--ext->unk92 == 0) {
                ext->unk92 = 2;
                main_27_halt(arg0);
                return;
            }
        } else {
            ext->unk91 = 0x60;
        }
        main_27_turn(arg0);
    }
    if (arg0->unk15 == 0 ? (arg0->unk70 & 2) : (arg0->unk70 & 1))
        main_27_turn(arg0);
}

void func_80059154(struct MainObj* arg0)
{
    struct Main27Ext* ext = &arg0->ext.main_27;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    func_80015D60(arg0, 1);
    if (ext->unk80 == 0) {
        arg0->unk20 = arg0->unk15 != 0 ? 0x18000 : -0x18000;
        arg0->unk5 = 2;
    } else {
        ext->unk89 = 0x14;
        ext->unk88 = 0;
        arg0->unk5 = 6;
    }
    arg0->unk6 = 0;
}

void func_80059344(struct MainObj* arg0)
{
    struct Main27Ext* ext = &arg0->ext.main_27;
    struct ShotObj* shot;
    u8 direction;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    direction = ext->collision_direction;
    if ((u32)(direction - 9) < 0xF) {
        if (arg0->unk15 != 0) {
            arg0->unk7C = 0xA;
            arg0->unk6 = 3;
        }
    } else if ((u32)(direction - 8) >= 0x11 && arg0->unk15 == 0) {
        arg0->unk7C = 0xA;
        arg0->unk6 = 3;
    }
    if (arg0->unk6 == 3)
        return;
    func_80015D60(arg0, 4);
    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0xE;
        shot->unk2 = arg0->unk2;
        shot->unk40 = arg0->unk40;
        shot->unk42 = arg0->unk42;
        shot->animation_table = (u32**)arg0->animation_table;
        shot->unk3C = (void*)arg0->sprite_frames;
        shot->unk15 = arg0->unk15;
        shot->bg_offset = arg0->bg_offset;
        shot->x_pos.val = arg0->x_pos.val;
        shot->y_pos.val = arg0->y_pos.val;
        func_8002B93C(MOVING_OBJECT(shot), ext->collision_direction);
        shot->state = 0;
        shot->x_vel.val *= 3;
        shot->y_vel.val *= 3;
    }
    if (--arg0->unk7C == 0) {
        arg0->unk7C = 0xA;
        arg0->unk6 = 3;
    } else {
        arg0->unk7E = 0x14;
        arg0->unk6 = 1;
    }
}

void func_80059590(struct MainObj* arg0)
{
    struct Main27Ext* ext = &arg0->ext.main_27;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    func_80015D60(arg0, 1);
    func_8001540C(2, 0x51, arg0);
    if (ext->unk80 == 0) {
        ext->unk8C = 0xB4;
        arg0->unk20 = arg0->unk15 != 0 ? 0x18000 : -0x18000;
        arg0->unk5 = 2;
    } else {
        ext->unk89 = 0x14;
        ext->unk8C = 0x12C;
        ext->unk88 = 0;
        arg0->unk5 = 6;
    }
    arg0->unk6 = 0;
}

void func_80059640(struct MainObj* arg0)
{
    struct Main27Ext* ext = &arg0->ext.main_27;
    s32 dy;
    s32 dx;

    if (--ext->unk8C == 0 && (arg0->unk15 == 0 ? g_Player.x_pos.i.hi < arg0->x_pos.i.hi : arg0->x_pos.i.hi < g_Player.x_pos.i.hi)) {
        func_80015D60(arg0, 3);
        arg0->unk20 = 0;
        func_80015930(2, 0x51);
        arg0->unk5 = 5;
        arg0->unk6 = 0;
        return;
    }
    if (--ext->unk82 == 0) {
        ext->unk82 = 0x1E;
        if ((get_random() & 7) < 5) {
            arg0->unk7C = 0xA;
            arg0->unk20 = 0;
            arg0->unk5 = 7;
            arg0->unk6 = 0;
            return;
        }
    }
    if (ext->unk89 != 0)
        ext->unk89--;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (ext->unk88 == 0) {
        dy = g_Player.y_pos.i.hi - arg0->y_pos.i.hi;
        if (dy < 0)
            dy = -dy;
        if (dy < 0x31) {
            dx = arg0->unk15 == 0 ? ext->unk84 - g_Player.x_pos.val
                                  : g_Player.x_pos.val - ext->unk84;
            if (dx > 0x3FFFF) {
                ext->unk88 = 1;
                func_80015D60(arg0, 7);
            }
        }
    } else {
        dx = g_Player.x_pos.val - ext->unk84;
        if (dx < 0)
            dx = ext->unk84 - g_Player.x_pos.val;
        if (dx <= 0x3FFFF) {
            ext->unk88 = 0;
            func_80015D60(arg0, 1);
        }
    }
    if (arg0->unk15 == 0 ? (arg0->unk70 & 2) : (arg0->unk70 & 1)) {
        arg0->unk7C = 0x14;
        arg0->unk28 = 0;
        arg0->unk24 = 0;
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        return;
    }
    if (ext->unk89 == 0 && (arg0->unk15 == 0 ? arg0->x_pos.i.hi < g_Player.x_pos.i.hi : g_Player.x_pos.i.hi < arg0->x_pos.i.hi)) {
        arg0->unk7C = 0x14;
        arg0->unk28 = -0x2000;
        arg0->unk24 = 0;
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        return;
    }
    if (ext->unk88 == 0)
        arg0->unk20 = arg0->unk15 != 0 ? 0x20000 : -0x20000;
    else
        arg0->unk20 = arg0->unk15 != 0 ? 0x40000 : -0x40000;
    func_8002B718(MOVING_OBJECT(arg0));
}

extern struct Unk_unk68 D_80107274[];
extern union AnimationStep* D_800FDD08[8];
extern struct Unk_unk68 D_800FDC88[2];
extern struct Unk_unk68* D_800FDD38[2];
extern void (*D_800FDD40[7])(struct MainObj*);
extern u8 D_800FDD28[4];
extern s32 D_800FDC98[2];

void func_8005C860(struct MainObj* arg0)
{
    struct Main32Ext* ext = &arg0->ext.main_32;

    arg0->active = 0x41;
    arg0->unk5C = 3;
    arg0->unk60 = 3;
    arg0->unk61 = 0;
    arg0->collision_data = (const u16*)D_80107274;
    arg0->animation_table = (const u8* const*)D_800FDD08;
    arg0->unk16 = 6;
    arg0->unk54 = (const u8*)&D_800FDC80;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk68 = NULL;
    arg0->unk50 = (const u8*)D_800FDC88;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    func_80015D60(arg0, 0);
    ext->unk80 = 0;
    ext->unk84 = 0;
    ext->unk88 = 0;
    ext->unk8C = 0;
    ext->unk90 = 0;
    ext->saved_unk5 = 0;
    arg0->state++;
    arg0->unk5 = arg0->unk2 == 0 ? 2 : arg0->unk2 == 1 ? 5
                                                       : 6;
    arg0->unk6 = 0;
}

void func_8005C960(struct MainObj* arg0)
{
    struct Main32Ext* ext = &arg0->ext.main_32;
    s32 hit;
    u8 i;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FDD40[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    if (arg0->unk5 != 0)
        ext->saved_unk5 = arg0->unk5;
    for (i = 0; (s32)i < 2 - (s32)ext->unk88; i++) {
        arg0->unk54 = (const u8*)D_800FDD38[i];
        hit = func_8002DD04(arg0);
        if (hit < 0) {
            if (i == 0 && ext->unk88 == 0)
                func_8005D148(arg0);
            func_800AF808(BASE_OBJECT(arg0));
            func_800C813C(4, D_800FDD28, arg0);
            func_800BF60C(BASE_OBJECT(arg0), 8);
            arg0->state++;
            return;
        }
        if (hit != 0)
            break;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) != 0) {
        arg0->state++;
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
}

void func_8005CB90(struct MainObj* arg0)
{
    s32 limit;
    s32 distance;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    func_8002B93C(MOVING_OBJECT(arg0),
        func_8002B7B0(OBJECT_HEADER(arg0), g_Player.x_pos.val, g_Player.y_pos.val - 0x500000) & 0xFF);
    arg0->unk20 += arg0->unk20 / 2;
    limit = arg0->unk20;
    if (limit < 0)
        limit = -limit;
    limit += 0x20000;
    distance = g_Player.x_pos.val - arg0->x_pos.val;
    if (distance < 0)
        distance = arg0->x_pos.val - g_Player.x_pos.val;
    if (limit < distance && --arg0->unk7C != 0)
        return;
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void func_8005CF9C(struct MainObj* arg0)
{
    s32 spread;

    func_80015D60(arg0, 3);
    spread = get_random() << 8;
    spread += get_random();
    arg0->unk20 = D_800FDC98[(arg0->unk15 & 0x40) ? 1 : 0];
    if (get_random() & 1)
        arg0->unk20 += spread & 0xFFFF;
    else
        arg0->unk20 -= spread & 0xFFFF;
    arg0->unk24 = 0x18000;
    arg0->unk28 = -0x1000;
    arg0->unk50 = (const u8*)&D_800FDC80;
    arg0->ext.main_32.unk88 = 1;
    if (arg0->unk2 == 2) {
        arg0->unk7C = get_random() & 0x3F;
        arg0->unk6++;
    } else {
        arg0->unk6 += 2;
    }
}

extern u8 D_80108D6C[4];
extern u8 D_80108D70[4];

void func_8009AD6C(struct ShotObj* arg0)
{
    arg0->y_vel.val = -0x10000;
    arg0->unk2C = 0x3000;
    arg0->unk68 = (struct Unk_unk68*)D_80108D6C;
    arg0->unk54 = D_80108D70;
    arg0->unk50.data = D_80108D70;
    arg0->unk58.data = (const u8*)D_80105FF0;
    arg0->unk60 = 5;
    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->state++;
    arg0->unk42 &= 0x7FFF;
    func_80015D60(arg0, 2);
}

extern struct Unk_unk68 D_80106E74[];
extern union AnimationStep* D_800FCF74[];
extern struct Unk_unk68 D_800FCED4[];
extern struct Unk_unk68 D_800FCED8[];

void func_800567C4(struct MainObj* arg0)
{
    static const s32 motion[4][3] = {
        { -0x4000, -0x1C000, 0x14 },
        { -0x2000, -0xC000, 0x24 },
        { 0x4000, 0x1C000, 0x14 },
        { 0x2000, 0xC000, 0x24 },
    };
    u8 subtype = arg0->unk2;

    arg0->unk5C = 2;
    arg0->unk60 = 3;
    arg0->unk61 = 0;
    arg0->collision_data = (const u16*)D_80106E74;
    arg0->animation_table = (const u8* const*)D_800FCF74;
    arg0->unk16 = 6;
    arg0->unk54 = (const u8*)D_800FCED4;
    arg0->unk67 = 0;
    arg0->unk68 = NULL;
    arg0->unk50 = (const u8*)D_800FCED8;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (subtype < 8) {
        arg0->unk28 = -0x8000;
        arg0->unk2C = motion[subtype & 3][0];
        arg0->unk24 = motion[subtype & 3][1];
        arg0->unk7C = motion[subtype & 3][2];
        if (subtype < 4) {
            arg0->unk20 = -0x50000;
            arg0->unk15 = 0;
            func_8001540C(2, 0x50, arg0);
            arg0->unk5 = 2;
        } else {
            arg0->unk7A = 1;
            arg0->unk15 = 0x40;
            arg0->unk20 = 0x50000;
            arg0->unk5 = 3;
        }
    }
    func_80015D60(arg0, 0);
    arg0->ext.main_24.unk80 = 0;
    arg0->state = 1;
    arg0->unk6 = 0;
}

extern void* D_8010CF98[5];
extern u8 D_8010CFCC[4];

void func_800C2C3C(struct ItemObj* arg0)
{
    s32 resource;
    s32 row;

    arg0->active = 0x41;
    arg0->unk16 = 6;
    arg0->unk15 = 0;
    arg0->unk40 = D_801406A8[func_8002938C(0x88)] >> 7;
    resource = func_8002938C(0x88);
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    resource = func_8002938C(0x88);
    row = func_8002938C(0x88);
    arg0->unk42 = ((resource * 4 + 0x18) % 16) | ((((row + 6) / 4) + 0x1E0) << 6);
    arg0->animation_table = (const u8* const*)D_8010CF98;
    arg0->unk67 = 0;
    arg0->unk75 = 0;
    arg0->unk68 = (struct Unk_unk68*)D_8010CFCC;
    func_80015D60(ANIMATED_OBJECT(arg0), 0);
    arg0->state = (arg0->unk2 & 0x80) ? 3 : 1;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
}

extern union AnimationStep* D_800FD990[];
extern struct Unk_unk68 D_800FD8AC[];
extern struct Unk_unk68 D_800FD8B0[];
extern struct Unk_unk68 D_80107174[];

void func_8005B438(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    arg0->state++;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk15 = arg0->unk2 != 0 ? 0x40 : 0;
    arg0->animation_table = (const u8* const*)D_800FD990;
    arg0->collision_data = (const u16*)D_80107174;
    arg0->unk54 = (const u8*)D_800FD8B0;
    arg0->unk50 = (const u8*)D_800FD8AC;
    arg0->unk16 = 6;
    arg0->unk68 = NULL;
    arg0->unk61 = 0;
    arg0->unk5C = 6;
    arg0->unk60 = 3;
    arg0->unk67 = 0;
    arg0->unk7C = 0;
    func_80015D60(arg0, 0);
    func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
}

#define MAIN_37_U8(object, offset) (((u8*)&(object)->ext.main_37)[(offset)-0x80])
#define MAIN_37_S16(object, offset) (*(s16*)&MAIN_37_U8(object, offset))

extern union AnimationStep* D_800FE65C[28];
extern struct Unk_unk68 D_800FE4D4;
extern struct Unk_unk68 D_800FE4D8;
extern struct Unk_unk68 D_800FE4DC;
extern struct Unk_unk68 D_800FE4E0;
extern struct Unk_unk68 D_800FE4E4;
extern struct Unk_unk68 D_80107474[];
extern u8 D_800FE6D8[12];
void func_80060A58(struct AnimatedObj* arg0);
void func_800B10E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void func_8005FE1C(struct MainObj* arg0)
{
    static const s16 lanes[3][3] = {
        { 0x3F0, 0x480, 0x410 },
        { 0x390, 0x40B, 0x3B0 },
        { 0x330, 0x380, 0x350 },
    };
    u8 lane;

    arg0->unk5C = 6;
    arg0->unk60 = 4;
    arg0->unk61 = 0;
    arg0->unk62 = 2;
    arg0->animation_table = (const u8* const*)D_800FE65C;
    arg0->unk68 = &D_800FE4E4;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk67 = 0;
    arg0->unk16 = 6;
    switch (arg0->unk2) {
    case 0:
        arg0->collision_data = (const u16*)D_80107474;
        arg0->unk54 = (const u8*)&D_800FE4D4;
        arg0->unk50 = (const u8*)&D_800FE4D8;
        func_80060A58(ANIMATED_OBJECT(arg0));
        arg0->unk20 = 0;
        arg0->unk24 = -0x18000;
        func_80015D60(arg0, 1);
        arg0->unk5 = 2;
        break;
    case 1:
    case 2:
        arg0->collision_data = (const u16*)D_80107474;
        arg0->unk54 = (const u8*)&D_800FE4D4;
        arg0->unk50 = (const u8*)&D_800FE4D8;
        arg0->unk15 = arg0->unk2 == 2 ? 0x40 : 0;
        arg0->unk20 = arg0->unk2 == 2 ? 0x18000 : -0x18000;
        arg0->unk24 = 0;
        func_80015D60(arg0, 0);
        arg0->unk5 = 3;
        break;
    case 3:
        arg0->collision_data = (const u16*)D_801060F0;
        arg0->unk54 = (const u8*)&D_800FE4DC;
        arg0->unk50 = (const u8*)&D_800FE4E0;
        arg0->unk24 = 0;
        arg0->unk42 += 2;
        if (arg0->x_pos.i.hi >= 0x1799) {
            MAIN_37_S16(arg0, 0x84) = 0x17E0;
            arg0->x_pos.val = 0x18180000;
            arg0->unk20 = 0x10000;
            arg0->unk15 = 0;
            MAIN_37_U8(arg0, 0x81) = 0;
        } else {
            MAIN_37_S16(arg0, 0x84) = 0x1710;
            arg0->x_pos.val = 0x17080000;
            arg0->unk20 = -0x10000;
            arg0->unk15 = 0x40;
            MAIN_37_U8(arg0, 0x81) = 1;
        }
        if (arg0->y_pos.i.hi < 0x370)
            MAIN_37_U8(arg0, 0x81) += 2;
        if (arg0->y_pos.i.hi < 0x3D0)
            MAIN_37_U8(arg0, 0x81) += 2;
        lane = MAIN_37_U8(arg0, 0x81);
        if (lane < 6) {
            MAIN_37_S16(arg0, 0x86) = lanes[lane / 2][0];
            MAIN_37_S16(arg0, 0x88) = lanes[lane / 2][1];
            arg0->y_pos.val = lanes[lane / 2][2] << 16;
        }
        func_80015D60(arg0, 7);
        arg0->unk5 = 4;
        break;
    }
    MAIN_37_U8(arg0, 0x8C) = 0;
    MAIN_37_U8(arg0, 0x8D) = 1;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->state = 1;
    arg0->unk6 = 0;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
}

static void main_37_rumble(struct MainObj* arg0)
{
    if (--MAIN_37_U8(arg0, 0x8D) == 0) {
        func_8001540C(2, 0x59, arg0);
        MAIN_37_U8(arg0, 0x8D) = 0x1E;
    }
}

void func_800C8214(s32 arg0, u8* arg1, struct MainObj* arg2, s32 arg3, s32 arg4, s32 arg5);

static void main_37_debris(struct MainObj* arg0)
{
    if ((arg0->unk7E & 3) == 0) {
        func_800C8214(1, &D_800FE6D8[MAIN_37_U8(arg0, 0x8C)], arg0, 0x7988,
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

void func_80060574(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    main_37_rumble(arg0);
    if (!(MAIN_37_S16(arg0, 0x88) < g_Player.y_pos.i.hi)) {
        arg0->unk7C = 0x26;
        arg0->unk6 = 1;
    }
    main_37_debris(arg0);
}

void func_800606D8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    main_37_rumble(arg0);
    if (--arg0->unk7C == 0) {
        func_800AFAB4(2, MAIN_37_S16(arg0, 0x84) + 0x18, MAIN_37_S16(arg0, 0x86) + 0x20, 1);
        func_800DABE4((MAIN_37_U8(arg0, 0x81) & 1) + 5, MAIN_37_S16(arg0, 0x84), MAIN_37_S16(arg0, 0x86));
        arg0->unk7C = 0x20;
        arg0->unk6 = 2;
    }
    main_37_debris(arg0);
}

void func_800608CC(struct MainObj* arg0)
{
    s32 velocity;

    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk15 == 0) {
        if (arg0->x_pos.i.hi >= 0x17A0)
            return;
        arg0->x_pos.i.hi = 0x17A0;
        func_8001540C(2, 0x5A, arg0);
        velocity = 0x58000;
    } else {
        if (arg0->x_pos.i.hi < 0x1781)
            return;
        velocity = -0x58000;
        arg0->x_pos.i.hi = 0x1780;
    }
    arg0->unk7C = 0x28;
    arg0->unk28 = 0x2000;
    arg0->unk20 = velocity;
    arg0->unk6 = 4;
}

extern u8 D_80108ED8[4];

void func_8009C12C(struct ShotObj* arg0)
{
    struct MainObj* owner = MAIN_OBJECT(arg0->unk7C);

    arg0->unk40 = owner->unk40;
    arg0->unk42 = owner->unk42 & 0x7FFF;
    arg0->animation_table = (u32**)owner->animation_table;
    arg0->unk3C = (void*)owner->sprite_frames;
    arg0->unk15 = owner->unk15;
    arg0->bg_offset = owner->bg_offset;
    arg0->x_pos.val = owner->x_pos.val;
    arg0->state++;
    arg0->unk5 = 2;
    arg0->y_pos.val = owner->y_pos.val;
    func_8002B93C(MOVING_OBJECT(arg0),
        func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player)) & 0xFF);
    arg0->unk58.data = (const u8*)D_80106070;
    arg0->unk54 = D_80108ED8;
    arg0->unk50.data = D_80108ED8;
    arg0->unk5C = 1;
    arg0->unk60 = 3;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->x_vel.val *= 2;
    arg0->y_vel.val *= 2;
    func_80015D60(arg0, 4);
}

extern void* D_8010D028[2];
extern u8 D_8010D03C[];

void func_800C3578(struct ItemObj* arg0)
{
    s32 resource;
    s32 row;

    arg0->active = 0x49;
    arg0->unk16 = 7;
    arg0->unk40 = D_801406A8[func_8002938C(0x81)] >> 7;
    resource = func_8002938C(0x81);
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    resource = func_8002938C(0x81);
    row = func_8002938C(0x81);
    arg0->unk42 = ((resource * 4 + 0x18) % 16) | ((((row + 6) / 4) + 0x1E0) << 6);
    arg0->animation_table = (const u8* const*)D_8010D028;
    arg0->unk68 = (struct Unk_unk68*)D_8010D03C;
    arg0->unk15 = 0;
    arg0->unk67 = 0;
    arg0->unk75 = 1;
    arg0->state = 1;
    arg0->unk5 = 0;
    arg0->bg_offset = g_Player.bg_offset;
    func_80015D60(ANIMATED_OBJECT(arg0), 0);
}

extern struct Unk_unk68 D_801072F4[];
extern union AnimationStep* D_800FDEE4[23];
extern struct Unk_unk68 D_800FDD88;
extern struct Unk_unk68 D_800FDD8C;
extern u8 D_800FDD90[8];
extern u8 D_800FDD98[8];
extern u16 D_800FDDA0[14];
extern u8 D_800FDF40[12];
extern u8 D_800FDF4C[8];
extern void (*D_800FDF64[7])(struct MainObj*);

#define MAIN_33_SLOT_X(index) ((s16)D_800FDDA0[(index)*2])
#define MAIN_33_SLOT_Y(index) ((s16)D_800FDDA0[(index)*2 + 1])

void func_8005D230(struct MainObj* arg0)
{
    struct Main33Ext* ext = &arg0->ext.main_33;

    arg0->unk5C = 0;
    arg0->unk60 = 6;
    arg0->unk61 = 0;
    arg0->collision_data = (const u16*)D_801072F4;
    arg0->unk16 = 6;
    arg0->y_pos.i.hi = 0x2E8;
    arg0->animation_table = (const u8* const*)D_800FDEE4;
    arg0->unk54 = (const u8*)&D_800FDD88;
    arg0->unk50 = (const u8*)&D_800FDD8C;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk68 = NULL;
    arg0->unk15 = 0x40;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    func_80015D60(arg0, 0);
    ext->unk80 = 0x7F;
    ext->unk90 = 0;
    ext->unk85 = 1;
    ext->unk86 = 2;
    ext->unk8E = arg0->unk42;
    engine_obj.enable_boss = 1;
    engine_obj.unk25 = 2;
    engine_obj.boss_ptr = arg0;
    func_80036AE4(0x14, 0);
    arg0->state = 1;
    arg0->unk5 = 2;
    arg0->unk6 = 0;
}

void func_8005D348(struct MainObj* arg0)
{
    struct Main33Ext* ext = &arg0->ext.main_33;
    s32 x;
    s32 y;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FDF64[arg0->unk5](arg0);
    if (ext->unk85 == 0) {
        ext->saved_unk5 = arg0->unk5;
        if (func_8002DD04(arg0) < 0) {
            g_Player.unk7A = 1;
            g_Player.unk61 = 0x7F;
            func_800AF808(BASE_OBJECT(arg0));
            func_800C813C(9, D_800FDF40, arg0);
            arg0->unk54 = NULL;
            arg0->unk50 = NULL;
            func_800DABE4(1, 0, 0);
            arg0->unk7C = 0x5A;
            arg0->unk7E = 4;
            arg0->on_screen = 0;
            arg0->state = 2;
            arg0->unk5 = 0;
            return;
        }
    }
    func_8002D9BC(arg0);
    if (ext->unk90 != 0) {
        ext->unk90--;
        if (--ext->unk91 == 0) {
            x = arg0->x_pos.val;
            y = arg0->y_pos.val;
            arg0->x_pos.i.hi = MAIN_33_SLOT_X(ext->unk87) + 0x20;
            arg0->y_pos.i.hi = MAIN_33_SLOT_Y(ext->unk87) + 0x20;
            func_800AF878(BASE_OBJECT(arg0), 1, 0x20, 0x20);
            arg0->x_pos.val = x;
            arg0->y_pos.val = y;
            ext->unk91 = 6;
        }
    }
    func_8002B318(BASE_OBJECT(arg0), 0x48, 0x48);
}

void func_8005D4E0(struct MainObj* arg0)
{
    struct Main33Ext* ext = &arg0->ext.main_33;
    s32 x;
    s32 y;
    s32 i;

    switch (arg0->unk5) {
    case 0:
        if (--arg0->unk7C == 0) {
            engine_obj.enable_boss = 0;
            engine_obj.boss_ptr = NULL;
            arg0->unk7C = 0x50;
            arg0->unk7E = 1;
            arg0->unk42 = 0x798F;
            for (i = 0; i < 7; i++) {
                if (!(D_800FDD90[i] & ext->unk80))
                    continue;
                arg0->x_pos.i.hi = MAIN_33_SLOT_X(i) + 0x20;
                arg0->y_pos.i.hi = MAIN_33_SLOT_Y(i) + 0x20;
                func_800DABE4(0, MAIN_33_SLOT_X(i), MAIN_33_SLOT_Y(i));
                func_800C813C(6, D_800FDF4C, arg0);
            }
            arg0->unk5 = 1;
            return;
        }
        if (!(--arg0->unk7E & 1)) {
            x = arg0->x_pos.val;
            y = arg0->y_pos.val;
            arg0->x_pos.i.hi = 0x12A0;
            arg0->y_pos.i.hi = 0x300;
            func_800AF95C(OBJECT_HEADER(arg0), 1, 0xA0, 0x18, 4);
            arg0->x_pos.val = x;
            arg0->y_pos.val = y;
        }
        if (arg0->unk7E == 0) {
            arg0->unk7E = 6;
            func_800AF95C(OBJECT_HEADER(arg0), 1, 0x20, 0x20, 4);
        }
        break;
    case 1:
        if (--arg0->unk7C == 0) {
            arg0->unk7C = 0x80;
            ext->unk88 = 0x1200;
            arg0->unk5 = 2;
            return;
        }
        if (--arg0->unk7E != 0)
            return;
        arg0->unk7E = 6;
        for (i = 0; i < 7; i++) {
            if (!(D_800FDD90[i] & ext->unk80))
                continue;
            arg0->x_pos.i.hi = MAIN_33_SLOT_X(i) + 0x20;
            arg0->y_pos.i.hi = MAIN_33_SLOT_Y(i) + 0x20;
            func_800AF95C(OBJECT_HEADER(arg0), 1, 0x28, 0x18, 4);
        }
        break;
    case 2:
        if (--arg0->unk7C == 0) {
            arg0->state = 3;
            return;
        }
        ext->unk88 -= 2;
        if (ext->unk88 < 0x1100)
            ext->unk88 = 0x1100;
        background_objects[0].unk26 = ext->unk88;
        break;
    }
}

void func_8005D8B8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (arg0->unk15 == 0 ? arg0->x_pos.i.hi < 0x1220 : arg0->x_pos.i.hi >= 0x1321) {
        func_80015D60(arg0, 1);
        arg0->unk28 = -0x2000;
        arg0->unk6 = 2;
        return;
    }
    if (arg0->ext.main_33.unk85 != 0 || --arg0->unk7C != 0)
        return;
    arg0->unk7C = 1;
    if (arg0->unk15 == 0 ? arg0->x_pos.i.hi >= 0x1231 : arg0->x_pos.i.hi < 0x1310) {
        func_80015D60(arg0, 2);
        arg0->unk5 = 4;
        arg0->unk6 = 0;
    }
}

void func_8005DC58(struct MainObj* arg0)
{
    struct Main33Ext* ext = &arg0->ext.main_33;
    s16 target;
    s32 delta;
    u8 slot;
    u8 first;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (ext->unk82 != 0) {
        arg0->unk6 = 3;
        return;
    }
    func_8002B718(MOVING_OBJECT(arg0));
    target = g_Player.x_pos.i.hi;
    if (--arg0->unk7C == 0) {
        if (g_Player.x_pos.i.hi < 0x1220) {
            ext->variant = 0;
            if (!(D_800FDD98[0] & ext->unk80)) {
                ext->variant = 1;
                if (!(D_800FDD98[1] & ext->unk80))
                    ext->variant = 0;
            }
        } else if (g_Player.x_pos.i.hi >= 0x1321) {
            ext->variant = 4;
            if (!(D_800FDD98[4] & ext->unk80)) {
                ext->variant = 3;
                if (!(D_800FDD98[3] & ext->unk80))
                    ext->variant = 4;
            }
        } else {
            delta = (u16)g_Player.x_pos.i.hi - 0x1220;
            slot = (u8)((s16)delta >> 6);
            ext->variant = (delta & 0x3F) < 0x21 ? slot : slot + 1;
            first = ext->variant;
            if (!(D_800FDD98[first] & ext->unk80)) {
                ext->variant = (delta & 0x3F) < 0x21 ? first + 1 : first - 1;
                if (!(D_800FDD98[ext->variant] & ext->unk80))
                    ext->variant = first;
            }
        }
        ext->unk82 = ext->variant * 64 + 0x1220;
        target = ext->unk82;
    }
    if (arg0->unk15 == 0) {
        if (!(arg0->x_pos.i.hi < 0x1220 && ext->unk82 == 0) && !(arg0->x_pos.i.hi < target))
            return;
    } else {
        if (!(arg0->x_pos.i.hi >= 0x1321 && ext->unk82 == 0) && !(target < arg0->x_pos.i.hi))
            return;
    }
    func_80015D60(arg0, 4);
    arg0->unk28 = -0x4000;
    arg0->unk6 = 2;
}

void func_8005DED4(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0)
        arg0->unk7C = 1;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk20 != 0)
        return;
    func_8001540C(2, 0x52, arg0);
    if (arg0->unk15 == 0) {
        arg0->unk15 = 0x40;
        arg0->unk20 = 0x40000;
    } else {
        arg0->unk20 = -0x40000;
        arg0->unk15 = 0;
    }
    func_80015D60(arg0, 3);
    arg0->unk28 = 0;
    arg0->unk6 = 1;
}

void func_8005E108(struct MainObj* arg0)
{
    struct Main33Ext* ext = &arg0->ext.main_33;
    u8 slot;
    u8 mask;

    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    slot = ext->variant;
    mask = ext->unk80;
    if (D_800FDD90[slot] & mask) {
        arg0->unk7C = 0xC;
    } else if (slot < 2 && (mask & 0x20)) {
        ext->variant = 5;
        arg0->unk7C = 0x22;
    } else if (slot >= 2 && (u8)(slot - 3) < 2 && (mask & 0x40)) {
        ext->variant = 6;
        arg0->unk7C = 0x22;
    } else {
        ext->variant = 0xFF;
        arg0->unk7C = 0x26;
    }
    arg0->unk6 = 1;
}

void func_8005E298(struct MainObj* arg0)
{
    struct Main33Ext* ext = &arg0->ext.main_33;
    u8 slot;
    s32 x;
    s32 y;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7E != 0)
        return;
    func_8001540C(2, 0x55, arg0);
    func_80028BAC(0x10, 8, 2);
    slot = ext->variant;
    func_800DABE4(0, MAIN_33_SLOT_X(slot), MAIN_33_SLOT_Y(slot));
    x = arg0->x_pos.val;
    y = arg0->y_pos.val;
    arg0->x_pos.i.hi = MAIN_33_SLOT_X(slot) + 0x20;
    arg0->unk42 = 0x798F;
    arg0->y_pos.i.hi = MAIN_33_SLOT_Y(slot) + 0x20;
    func_800C813C(6, D_800FDF4C, arg0);
    arg0->x_pos.val = x;
    arg0->y_pos.val = y;
    arg0->unk42 = ext->unk8E;
    ext->unk90 = 0x20;
    ext->unk91 = 6;
    ext->variant = 0xFF;
    ext->unk87 = slot;
    arg0->unk6 = 1;
    ext->unk80 ^= D_800FDD90[slot];
}

void func_800C6EDC(struct VisualObj* arg0)
{
    s32 resource;
    s32 column;
    s32 index;

    if (arg0->state == 0) {
        arg0->active = 1;
        arg0->on_screen = 1;
        resource = func_8002938C(0xA2) & 0xFF;
        column = resource * 4 + 0x18;
        index = (s8)D_8010D414[arg0->unk2];
        arg0->unk38 = SP_ARCHIVE_ENTRY(SP_PLAYER_GFX, index + 10);
        arg0->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, index + 18);
        arg0->animation_table = D_8011BF40;
        arg0->unk40 = 0x520;
        arg0->unk42 = (column - (column & 0x7F0)) | ((((resource + 6) >> 2) + 0x1E0) << 6);
        arg0->unk16 = 0;
        arg0->unk15 = g_Player.unk15;
        arg0->x_pos.val = g_Player.x_pos.val;
        arg0->y_pos.val = g_Player.y_pos.val;
        func_80015D60(ANIMATED_OBJECT(arg0), engine_obj.unk37 != 0 ? 0x26 : 0x25);
        arg0->state++;
        decompress_player_gfx((struct GraphicsObj*)arg0, 0x140, 0x20);
    } else if (arg0->animation_step.fields.relative_step == 0) {
        g_Player.unkE2 = 4;
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.event != 0) {
            arg0->animation_step.fields.event = 0;
            if (engine_obj.unk37 != 0) {
                g_Player.unkA7 = 0xF;
                g_Player.unkB8 = 2;
                engine_obj.unk48 = 2;
            } else {
                u8 bit = D_8010D3D0[arg0->unk2];

                g_Player.unkA7 |= bit;
                if (bit == 4) {
                    if (arg0->unk2 == 2)
                        g_Player.unkB8 = 1;
                    if (arg0->unk2 == 3)
                        g_Player.unkB8 = 2;
                    engine_obj.unk48 = g_Player.unkB8;
                }
            }
            engine_obj.unk47 = g_Player.unkA7;
        }
    }
    func_8002B318(BASE_OBJECT(arg0), 0x88, 0x88);
}

void func_800C670C(struct ItemObj* arg0)
{
    s16 dx = g_Player.x_pos.u.hi - arg0->x_pos.u.hi;
    s16 dy;

    if (dx < 0)
        dx = -dx;
    if (dx >= 0x41)
        return;

    dy = g_Player.y_pos.u.hi - arg0->y_pos.u.hi;
    if ((dy > 0 && dy >= 0x11) || (dy <= 0 && -dy >= 0x69))
        return;

    func_80015D60(ANIMATED_OBJECT(arg0), 0xA);
    if (g_Player.x_pos.val - arg0->x_pos.val > 0) {
        func_80036AE4(0x14, 0);
        arg0->unk15 = 0x40;
    } else {
        func_80036AE4(0x14, 0x40);
        arg0->unk15 = 0;
    }
    func_80016F0C();
    func_8001663C(0x1B, 0x7F);
    arg0->unk5++;
}

void func_800528BC(struct MainObj* arg0)
{
    s32 index;

    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk5 = 2;
    arg0->unk5C = 4;
    arg0->unk60 = 3;
    arg0->animation_table = (const u8* const*)D_800FC69C;
    arg0->unk6 = 0;
    arg0->unk7C = 0;
    arg0->unk61 = 0;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    CollisionRelated(PLAYER_OBJECT(arg0));
    arg0->unk67 = 0;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;

    switch (arg0->unk2) {
    case 0:
        arg0->unk20 = FIXED(8);
        arg0->unk15 = 0x40;
        break;
    case 1:
        arg0->unk20 = FIXED(-8);
        arg0->unk15 = 0;
        break;
    case 2:
        arg0->unk24 = FIXED(8);
        break;
    }
    arg0->unk16 = 6;

    arg0->ext.main_19.unk80 = get_random() & 1;
    arg0->ext.main_19.animation_index = (u8)arg0->unk2;
    index = arg0->unk2 >> 1;
    arg0->unk54 = D_800FC744[index];
    arg0->unk50 = D_800FC74C[index];
    arg0->unk68 = D_800FC73C[index];
    arg0->collision_data = D_80106BF4;
    func_8002C808(PLAYER_OBJECT(arg0));
    arg0->unk5 = arg0->unk70 != 0 ? 2 : 5;
}

void func_80052A68(struct MainObj* arg0)
{
    s32 collision;
    s16 x;
    s16 y;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FC79C[(u8)arg0->unk5](arg0);
    func_8002D9BC(arg0);
    collision = func_8002DD04(arg0);
    if (collision < 0) {
        arg0->unk20 = 0;
        arg0->unk24 = 0;
        arg0->unk28 = 0;
        arg0->unk2C = 0;
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(8, D_800FC708, arg0);
        x = arg0->x_pos.i.hi;
        y = arg0->y_pos.i.hi;
        if (arg0->ext.main_19.animation_index < 2) {
            x += arg0->unk15 != 0 ? -0x10 : 0x10;
        } else {
            y += 0x10;
        }
        func_800BF638(BASE_OBJECT(arg0), 0xC, x, y);
        arg0->state = 2;
        return;
    }

    if (func_8002B160(BASE_OBJECT(arg0)) != 0)
        arg0->state = 2;
    else
        is_on_screen(BASE_OBJECT(arg0));
}

u16 func_800537E0(struct MainObj* arg0, u8 direction, u8 vertical)
{
    struct Unk_unk68* bounds = arg0->unk68;
    s32 first;
    s32 second;
    s16 probe;
    s16 edge;

    if (vertical == 0) {
        if (direction == 0) {
            probe = -(u16)arg0->ext.main_19.unk8A;
            edge = probe - (u8)bounds->unk3;
        } else {
            probe = arg0->ext.main_19.unk8A;
            edge = probe + (u8)bounds->unk3;
        }
        if (arg0->unk15 == 0) {
            first = func_80053A88(PLAYER_OBJECT(arg0), -1, probe);
            second = func_80053B18(PLAYER_OBJECT(arg0), -4, edge);
        } else {
            first = func_80053A88(PLAYER_OBJECT(arg0), 1, probe);
            second = func_80053B18(PLAYER_OBJECT(arg0), 4, edge);
        }
        if ((first & 0xF) == (1 << arg0->ext.main_19.animation_index))
            return (u8)second < 0x38;
        return 1;
    }

    if (direction == 0) {
        probe = -(u16)arg0->ext.main_19.unk8A;
        edge = probe - (u8)bounds->unk2;
    } else {
        probe = arg0->ext.main_19.unk8A;
        edge = probe + (u8)bounds->unk2;
    }
    first = func_80053A88(PLAYER_OBJECT(arg0), probe, -1);
    second = func_80053B18(PLAYER_OBJECT(arg0), edge, -4);
    if ((first & 0xF) == 4)
        return (u8)second < 0x38;
    return 1;
}

void func_80052CB8(struct MainObj* arg0)
{
    u8 animation;
    u16 probe_result;

    if (arg0->ext.main_19.animation_index < 2) {
        if (arg0->ext.main_19.animation_index == 0) {
            arg0->unk15 = 0x40;
            arg0->ext.main_19.unk82 = 1;
        } else {
            arg0->unk15 = 0;
            arg0->ext.main_19.unk82 = 2;
        }
        arg0->ext.main_19.unk84 = (get_random() & 1) ? 0x50 : 0x20;
        probe_result = func_800537E0(arg0, arg0->ext.main_19.unk80, 0);
        if (probe_result != 0)
            arg0->ext.main_19.unk80 ^= 1;
        animation = D_800FC7D4[arg0->ext.main_19.unk80];
        arg0->ext.main_19.unk8A = 0x15;
    } else {
        arg0->ext.main_19.unk84 = (get_random() & 1) ? 0x40 : 0x20;
        if (func_800537E0(arg0, arg0->ext.main_19.unk80, 1) != 0)
            arg0->ext.main_19.unk80 ^= 1;
        arg0->unk15 = D_800FC7D8[arg0->ext.main_19.unk80];
        arg0->ext.main_19.unk8A = 0x17;
        arg0->ext.main_19.unk82 = 4;
        animation = 2;
    }

    arg0->unk68 = D_800FC73C[arg0->unk2 >> 1];
    func_80015D60(ANIMATED_OBJECT(arg0), animation);
    arg0->unk6 = 1;
    arg0->ext.main_19.unk86 = arg0->x_pos.u.hi;
    arg0->ext.main_19.unk88 = arg0->y_pos.u.hi;
}

u8 func_80053B54(struct MainObj* arg0)
{
    s16 dx = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    s16 dy = g_Player.y_pos.i.hi - arg0->y_pos.i.hi;
    u8 direction;
    s32 selected = 0;

    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;
    direction = (u8)func_8002B7DC(
        OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));

    if (arg0->ext.main_19.animation_index < 2) {
        if (dx < 0x40 && dy >= 0x60)
            return 0;
        if (arg0->ext.main_19.animation_index == 0)
            selected = (u8)(direction - 8) < 0x11;
        else
            selected = (u8)(direction - 9) >= 0xF;
    } else {
        if (dx >= 0x80)
            return 0;
        selected = (u8)(direction - 0x10) < 0x11;
    }

    if (selected)
        arg0->ext.main_19.unk83 = direction & 0x1E;
    return selected;
}

void func_80052E94(struct MainObj* arg0)
{
    s32 distance;
    u8 flags;

    if (arg0->ext.main_19.animation_index < 2) {
        if (arg0->animation_step.fields.relative_step < 0) {
            distance = arg0->y_pos.i.hi - (s16)arg0->ext.main_19.unk88;
            if (distance < 0)
                distance = -distance;
            if (distance <= arg0->ext.main_19.unk84 && func_800537E0(arg0, arg0->ext.main_19.unk80, 0) == 0) {
                if (arg0->unk7C >= 0x3C && func_80053B54(arg0) != 0) {
                    arg0->unk5 = 4;
                    arg0->unk6 = 0;
                }
                goto update_animation;
            }

            flags = func_8005398C(arg0);
            if (flags & 1) {
                arg0->unk6 = 4;
                arg0->ext.main_19.unk80 = arg0->unk24 < 0 ? 1 : 0;
                arg0->unk20 = 0;
                arg0->unk24 *= 3;
                func_80015D60(ANIMATED_OBJECT(arg0), 6);
            } else if (func_80053B54(arg0) != 0) {
                arg0->unk5 = 4;
                arg0->unk6 = 0;
            } else {
                arg0->unk6 = 2;
                func_80015D60(ANIMATED_OBJECT(arg0), 6);
            }
        } else if (arg0->animation_step.fields.event != 0) {
            if (arg0->ext.main_19.unk80 == 0)
                arg0->y_pos.u.hi -= arg0->ext.main_19.unk8A;
            else
                arg0->y_pos.u.hi += arg0->ext.main_19.unk8A;
            arg0->animation_step.fields.event = 0;
        }
    } else {
        if (arg0->animation_step.fields.relative_step < 0) {
            distance = arg0->x_pos.i.hi - (s16)arg0->ext.main_19.unk86;
            if (distance < 0)
                distance = -distance;
            if (distance <= arg0->ext.main_19.unk84 && func_800537E0(arg0, arg0->ext.main_19.unk80, 1) == 0) {
                if (arg0->unk7C >= 0x3C && func_80053B54(arg0) != 0) {
                    arg0->unk5 = 4;
                    arg0->unk6 = 0;
                }
                goto update_animation;
            }

            flags = func_8005398C(arg0);
            if (flags & 2) {
                arg0->unk6 = 4;
                if (arg0->unk20 >= 0) {
                    arg0->unk15 = 0x40;
                    arg0->ext.main_19.unk80 = 1;
                } else {
                    arg0->unk15 = 0;
                    arg0->ext.main_19.unk80 = 0;
                }
                arg0->unk24 = 0;
                arg0->unk20 *= 3;
                func_80015D60(ANIMATED_OBJECT(arg0), 5);
            } else if (func_80053B54(arg0) != 0) {
                arg0->unk5 = 4;
                arg0->unk6 = 0;
            } else {
                arg0->unk6 = 2;
                func_80015D60(ANIMATED_OBJECT(arg0), 5);
            }
        } else if (arg0->animation_step.fields.event != 0) {
            if (arg0->ext.main_19.unk80 == 0)
                arg0->x_pos.u.hi -= arg0->ext.main_19.unk8A;
            else
                arg0->x_pos.u.hi += arg0->ext.main_19.unk8A;
            arg0->animation_step.fields.event = 0;
        }
    }

update_animation:
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8005368C(struct MainObj* arg0)
{
    struct ShotObj* shot;
    s32 index;

    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->ext.main_19.unk80 = get_random() & 1;
        return;
    }

    if (arg0->animation_step.fields.event == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        return;
    }

    shot = find_free_shot_obj();
    if (shot != NULL) {
        index = arg0->ext.main_19.animation_index;
        shot->active = 0x41;
        shot->id = 0xB;
        shot->x_pos.i.hi = arg0->x_pos.i.hi + D_800FC7E8[index * 2];
        shot->y_pos.i.hi = arg0->y_pos.i.hi + D_800FC7E8[index * 2 + 1];
        shot->animation_table = (u32**)arg0->animation_table;
        shot->unk40 = arg0->unk40;
        shot->unk3C = (void*)arg0->sprite_frames;
        shot->unk42 = arg0->unk42 & 0x7FFF;
        shot->unk7C = (struct WeaponObj*)arg0;
        shot->unk16 = arg0->unk16;
        shot->unk15 = arg0->unk15;
        func_8002B93C(MOVING_OBJECT(shot), arg0->ext.main_19.unk83);
    }
    arg0->animation_step.fields.event = 0;
}

void func_80053338(struct MainObj* arg0)
{
    struct Unk_unk68* bounds;
    s16 probe_x;
    s16 probe_y;
    s32 distance;
    s32 nearby;
    u8 collision;
    u8 direction;

    func_8002B718(MOVING_OBJECT(arg0));
    CollisionRelated(PLAYER_OBJECT(arg0));
    bounds = arg0->unk68;
    nearby = 0;
    if (arg0->ext.main_19.animation_index < 2) {
        probe_y = arg0->y_pos.i.hi;
        if (arg0->ext.main_19.unk80 == 0)
            probe_y -= (u8)bounds->unk3;
        else
            probe_y += (u8)bounds->unk3;
        probe_x = arg0->x_pos.i.hi + (arg0->unk15 != 0 ? 4 : -4);
        distance = g_Player.y_pos.i.hi - arg0->y_pos.i.hi;
    } else {
        probe_x = arg0->x_pos.i.hi;
        if (arg0->unk15 == 0)
            probe_x -= (u8)bounds->unk2;
        else
            probe_x += (u8)bounds->unk2;
        probe_y = arg0->y_pos.i.hi - 4;
        distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    }
    if (distance < 0)
        distance = -distance;
    if (distance < 0x18)
        nearby = 1;

    collision = func_8002D724(PLAYER_OBJECT(arg0), probe_x, probe_y);
    if ((arg0->unk70 & (u8)~arg0->ext.main_19.unk82) == 0 && collision >= 0x38 && !nearby) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        return;
    }

    if (arg0->ext.main_19.animation_index < 2) {
        func_80015D60(ANIMATED_OBJECT(arg0), 0xB);
        arg0->unk6 = 6;
        arg0->ext.main_19.unk80 ^= 1;
        direction = arg0->ext.main_19.unk80;
        if ((arg0->unk70 >> (direction + 2)) & 1)
            arg0->ext.main_19.unk80 = direction ^ 1;
    } else {
        func_80015D60(ANIMATED_OBJECT(arg0), 0xA);
        arg0->unk6 = 6;
        arg0->unk15 ^= 0x40;
        arg0->ext.main_19.unk80 ^= 1;
        direction = arg0->ext.main_19.unk80;
        if ((arg0->unk70 >> direction) & 1)
            arg0->ext.main_19.unk80 = direction ^ 1;
    }
}

void func_800C7C30(struct MiscObj* arg0)
{
    s32 resource;
    s32 column;
    s32 row;

    arg0->state = 1;
    arg0->unk6 = 0;
    arg0->bg_offset = 0;
    arg0->animation_table = (u32**)D_8010DA9C;
    resource = func_8002938C(0x84);
    arg0->unk40 = (u16)((u32)D_801406A8[resource] >> 7);
    resource = func_8002938C(0x84);
    column = resource * 4 + 0x18;
    row = func_8002938C(0x84);
    arg0->unk42 = (u16)((column - ((column >> 4) << 4))
        | ((((row + 6) >> 2) + 0x1E0) << 6));
    resource = func_8002938C(0x84);
    arg0->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, resource);
    arg0->unk16 = arg0->unk2 == 5 ? 5 : 0x11;
    func_80015D60(ANIMATED_OBJECT(arg0), arg0->unk2);
}

s32 func_8002BD58(struct MainObj* obj0, struct MainObj* obj1, s16* out_x,
    s16* out_y)
{
    const struct Unk_unk68* box0;
    const struct Unk_unk68* box1;
    s32 flip0;
    s32 flip1;
    s32 a0;
    s32 a1;
    s32 a2;
    s32 sum;
    s32 t0;
    s32 t1;
    s32 t2;
    s32 result;

    if (obj1->unk61 != 0) {
        return 0;
    }
    box0 = (const struct Unk_unk68*)obj0->unk50;
    if (box0 == NULL) {
        return 0;
    }
    box1 = (const struct Unk_unk68*)obj1->unk54;
    if (box1 == NULL) {
        return 0;
    }

    flip0 = (u8)obj0->unk15 & 0x40;
    flip1 = (u8)obj1->unk15 & 0x40;
    t1 = box0->unk2;
    t2 = box1->unk2;
    sum = t1 + t2;
    a2 = flip0 ? obj0->x_pos.i.hi - box0->unk0 : obj0->x_pos.i.hi + box0->unk0;
    a0 = flip1 ? obj1->x_pos.i.hi - box1->unk0 : obj1->x_pos.i.hi + box1->unk0;
    a1 = a0 - a2;
    if (a1 < 0) {
        a1 = a2 - a0;
    }

    if (a0 < a2) {
        if (flip0 && flip1) {
            if (!(a1 < t1)) {
                return 0;
            }
            if (a2 < a0 || t1 < t2 + a1) {
                result = a0 + (t1 - a1) / 2;
            } else {
                result = a0 - (t2 >> 1);
            }
        } else if (flip0) {
            if (!(a1 < sum)) {
                return 0;
            }
            if (!(a0 < a2 - t1) && t2 < a1) {
                result = a0 + (t2 >> 1);
            } else if (!(t2 + a0 < a2) && t1 < a1) {
                result = a2 - (t1 >> 1);
            } else {
                t0 = a2 - t1;
                if (t0 < a0) {
                    result = a0 + a1 / 2;
                } else {
                    result = t0 + ((t2 + a0) - t0) / 2;
                }
            }
        } else if (flip1) {
            return 0;
        } else {
            if (!(a1 < t2)) {
                return 0;
            }
            if (a2 < a0 || t2 < a1 + t1) {
                result = a2 + (t2 - a1) / 2;
            } else {
                result = (t1 >> 1) + a2;
            }
        }
    } else if (flip0) {
        if (!flip1 || !(a1 < t2)) {
            return 0;
        }
        if (t2 < a1 + t1) {
            result = a2 - (t2 - a1) / 2;
        } else {
            result = a2 - (t1 >> 1);
        }
    } else if (flip1) {
        if (!(a1 < sum)) {
            return 0;
        }
        if (t1 < a1) {
            result = (t1 >> 1) + a2;
        } else if (t2 < a1) {
            result = a0 - (t2 >> 1);
        } else {
            result = a0 - (a0 - a2) / 2;
        }
    } else {
        if (!(a1 < t1)) {
            return 0;
        }
        result = a0 + (t1 - a1) / 2;
    }
    *out_x = (s16)result;

    t1 = box0->unk3;
    t2 = box1->unk3;
    a2 = obj0->y_pos.i.hi + box0->unk1;
    a0 = obj1->y_pos.i.hi + box1->unk1;
    a1 = a0 - a2;
    if (a1 < 0) {
        a1 = a2 - a0;
    }
    if (a0 < a2) {
        if (!(a1 < t2)) {
            return 0;
        }
        if (a2 < a0 || t2 < a1 + t1) {
            result = a2 + (t2 - a1) / 2;
        } else {
            result = (t1 >> 1) + a2;
        }
    } else {
        if (!(a1 < t1)) {
            return 0;
        }
        if (t1 < a1 + t2) {
            result = a0 + (t1 - a1) / 2;
        } else {
            result = a0 + (t2 >> 1);
        }
    }
    *out_y = (s16)result;
    return 1;
}

extern union AnimationStep* D_800F9E1C[];
extern struct Unk_unk68 D_800F9CCC;

void func_80043390(struct MainObj* arg0)
{
    s32 index;
    s32 column;
    s32 row;

    arg0->unk7C = 0;
    arg0->unk5C = 6;
    arg0->unk61 = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->unk15 = g_Player.x_pos.val < arg0->x_pos.val ? 0 : 0x40;
    arg0->animation_table = (const u8* const*)D_800F9E1C;
    arg0->unk68 = &D_800F9CCC;
    arg0->unk54 = (const u8*)&D_800F9CD4;
    arg0->unk50 = (const u8*)&D_800F9CD0;
    arg0->unk16 = 4;
    index = func_8002938C(3);
    arg0->unk40 = (u16)((u32)D_801406A8[index] >> 7);
    index = func_8002938C(3);
    arg0->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
    column = (func_8002938C(3) << 2) + 0x18;
    row = func_8002938C(3);
    arg0->unk42 = (u16)((column - ((column >> 4) << 4))
        | ((((row + 6) >> 2) + 0x1E0) << 6));
    arg0->unk67 = 0;
    switch (arg0->unk2) {
    case 0:
        arg0->collision_data = D_80106470;
        func_80015D60(arg0, 1);
        arg0->unk60 = 3;
        arg0->ext.main_3.turn_timer = 0x78;
        arg0->ext.main_3.alerted = 0;
        arg0->ext.main_3.player_ahead = 0;
        arg0->unk5 = 2;
        break;
    case 1:
        arg0->collision_data = (const u16*)D_801060F0;
        arg0->ext.main_3.turn_timer = 0x78;
        arg0->unk60 = 4;
        arg0->ext.main_3.alerted = 1;
        arg0->ext.main_3.player_ahead = 0;
        arg0->unk5 = 5;
        break;
    default:
        arg0->collision_data = (const u16*)D_801060F0;
        arg0->unk60 = 4;
        arg0->ext.main_3.alerted = 1;
        arg0->ext.main_3.player_ahead = 0;
        arg0->ext.main_3.turn_timer = 0x78;
        func_80015D60(arg0, 5);
        arg0->unk5 = 8;
        break;
    }
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->state = 1;
    arg0->unk6 = 0;
}

s32 func_8002BB80(struct MainObj* obj0, struct MainObj* obj1)
{
    const struct Unk_unk68* box0;
    const struct Unk_unk68* box1;
    s32 flip0;
    s32 flip1;
    s32 sum;
    s32 t1;
    s32 t2;
    s32 a0;
    s32 a1;
    s32 a2;
    s32 overlap;

    if (obj1->unk61 != 0) {
        return 0;
    }
    box0 = (const struct Unk_unk68*)obj0->unk50;
    if (box0 == NULL) {
        return 0;
    }
    box1 = (const struct Unk_unk68*)obj1->unk54;
    if (box1 == NULL) {
        return 0;
    }

    flip0 = (u8)obj0->unk15 & 0x40;
    flip1 = (u8)obj1->unk15 & 0x40;
    t1 = box0->unk2;
    t2 = box1->unk2;
    sum = t1 + t2;
    a2 = flip0 ? obj0->x_pos.i.hi - box0->unk0 : obj0->x_pos.i.hi + box0->unk0;
    a0 = flip1 ? obj1->x_pos.i.hi - box1->unk0 : obj1->x_pos.i.hi + box1->unk0;
    a1 = a0 - a2;
    if (a1 < 0) {
        a1 = a2 - a0;
    }

    if (a0 < a2) {
        if (flip0) {
            overlap = flip1 ? a1 < t1 : a1 < sum;
        } else if (flip1) {
            return 0;
        } else {
            overlap = a1 < t2;
        }
    } else if (flip0) {
        if (!flip1) {
            return 0;
        }
        overlap = a1 < t2;
    } else {
        overlap = flip1 ? a1 < sum : a1 < t1;
    }
    if (overlap == 0) {
        return 0;
    }

    a2 = obj0->y_pos.i.hi + box0->unk1;
    a0 = obj1->y_pos.i.hi + box1->unk1;
    a1 = a0 - a2;
    if (a1 < 0) {
        a1 = a2 - a0;
    }
    if (a0 < a2) {
        return a1 < box1->unk3;
    }
    return a1 < box0->unk3;
}

s32 func_8002D9BC(void* shot)
{
    struct ShotObj* arg0 = (struct ShotObj*)shot;
    s32 result;
    s8 health;
    s8 damage;
    u32 amount;
    u8 charge;

    if (g_Player.unk7A != 0) {
        return 0;
    }

    if (g_Player.unkC5 < 0) {
        if (qux_object.unk5C & 0x80) {
            return 0;
        }
        if (qux_object.unk85 != 0) {
            return 0;
        }
        if (!func_8002BB80(MAIN_OBJECT(arg0), MAIN_OBJECT(&qux_object))) {
            return 0;
        }
        qux_object.unk63 = 0;
        qux_object.unk86 = 0;
        qux_object.unk63 = arg0->unk60 < 5 ? 1 : 2;
        health = (u8)qux_object.unk5C - (u8)arg0->unk60;
        qux_object.unk5C = health;
        qux_object.unk5C = (health << 24) > 0 ? (s8)(health | 0x80) : (s8)-0x80;
        qux_object.unk84 = qux_object.x_pos.i.hi < arg0->x_pos.i.hi ? 0x40 : 0;
        return 1;
    }

    if (g_Player.unk5C & 0x80) {
        return 0;
    }
    if (g_Player.unkA4 != 0) {
        return 0;
    }
    if (!func_8002BB80(MAIN_OBJECT(arg0), MAIN_OBJECT(&g_Player))) {
        return 0;
    }

    g_Player.unkBA = 0;
    g_Player.unk63 = (u8)arg0->unk62;
    switch (arg0->unk62) {
    case 0:
        if (g_Player.unk2 == 0 && ((u8)g_Player.unkA7 & 2)) {
            g_Player.unk63 = 4;
        } else {
            g_Player.unk63 = arg0->unk60 < 5 ? 1 : 2;
        }
        break;
    case 3:
        g_Player.unkBA = 1;
        break;
    }

    damage = arg0->unk60;
    if (damage != 0) {
        if ((u8)g_Player.unkA7 & 2) {
            amount = damage < 3 ? 1 : (u32)(((arg0->unk60 / 3) << 24) >> 23);
            g_Player.unk5C = (u8)g_Player.unk5C - amount;
        } else {
            g_Player.unk5C = (u8)g_Player.unk5C - (u8)damage;
        }
    }
    g_Player.unk5C = g_Player.unk5C > 0 ? (s8)(g_Player.unk5C | 0x80) : (s8)-0x80;

    if (arg0->unk62 != 3) {
        g_Player.unkA5 = g_Player.x_pos.i.hi < arg0->x_pos.i.hi ? 0x40 : 0;
    }

    result = 1;
    if (g_Player.unk2 == 0) {
        if (!((u8)g_Player.unkA7 & 2)) {
            return 1;
        }
    } else if (!((u8)g_Player.unkB9 & 0x20)) {
        return 1;
    }

    if (g_Player.charge_levels[0] != 0x30) {
        charge = (s8)g_Player.charge_levels[0] + 6;
        g_Player.charge_levels[0] = charge;
        if ((s8)charge >= 0x31) {
            g_Player.charge_levels[0] = 0x30;
        }
    }
    return result;
}

void func_80092684(struct WeaponObj* arg0)
{
    s32 velocity;

    arg0->on_screen = 1;
    if (arg0->id == 9) {
        velocity = FIXED(8);
        arg0->unk2 = 0;
    } else {
        velocity = FIXED(10);
        arg0->unk2 = 1;
    }
    arg0->x_vel.val = velocity;
    arg0->unk50 = (const u8*)&D_80108708[arg0->unk2];
    if (arg0->unk15 == 0) {
        arg0->x_vel.val = -arg0->x_vel.val;
    }
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    func_80015D60(arg0, arg0->unk2 + 0x1A);
    arg0->state = (u8)arg0->state + 1;
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x14);
}

void func_80043C0C(struct MainObj* arg0)
{
    s32 magnitude = arg0->unk20;

    if (magnitude < 0) {
        magnitude = -magnitude;
    }
    if (magnitude <= 0xFFFF
        || ((arg0->unk70 & 2) && arg0->unk15 == 0)
        || ((arg0->unk70 & 1) && arg0->unk15 != 0)) {
        arg0->unk60 = 3;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk5 = 7;
        arg0->unk6 = 0;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

s32 func_8002B160(struct BaseObj* arg0)
{
    s32 x;
    s32 y;

    if (arg0->bg_offset < 0) {
        x = arg0->x_pos.u.hi;
        y = arg0->y_pos.u.hi;
    } else {
        x = arg0->x_pos.u.hi - background_objects[arg0->bg_offset].x_pos.u.hi;
        y = arg0->y_pos.u.hi - background_objects[arg0->bg_offset].y_pos.u.hi;
    }
    if ((u32)((x + 0x40) & 0xFFFF) < 0x1C0 && (u32)((y + 0x40) & 0xFFFF) < 0x170) {
        return 0;
    }
    return 1;
}

void func_8002DF7C(struct WeaponObj* arg0, s32 arg1)
{
    const struct EffectSpawnData* entry = &D_800F460C[arg0->id];
    struct VisualObj* visual;
    s32 visual_id;

    if (entry->effect_type == 4) {
        return;
    }

    if (arg1 < 0) {
        if (entry->set_facing != 0) {
            arg0->unk98 = -1;
        }
        func_8001540C(0, 6, arg0);
        visual_id = 0;
    } else {
        if (entry->set_facing != 0 && (arg1 == 0 || entry->keep_facing == 0)) {
            arg0->unk98 = 1;
        }
        switch (entry->effect_type) {
        case 0:
            func_8001540C(1, entry->animation_id, arg0);
            break;
        case 1:
            func_8001540C(1, arg1 != 0 ? 0xA : 9, arg0);
            break;
        case 2:
        case 3:
            func_8001540C(5, entry->animation_id, arg0);
            break;
        }
        visual_id = entry->visual_id;
    }

    visual = find_free_visual_obj();
    if (visual == NULL) {
        return;
    }
    visual->active = 0x21;
    visual->id = 3;
    visual->unk2 = (s8)visual_id;
    visual->bg_offset = arg0->bg_offset;
    visual->animation_table = D_8011BF40;
    visual->unk40 = 0;
    visual->unk42 = 0x7802;
    visual->unk16 = 0;
    visual->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 1);
    visual->x_pos.i.hi = (s16)((u16*)&arg0->unk80)[0];
    visual->y_pos.i.hi = (s16)((u16*)&arg0->unk80)[1];
    visual->unk15 = arg0->unk15 ^ 0x40;
}

s32 func_8002DE30(struct MainObj* arg0, struct WeaponObj* arg1)
{
    const u8* table;
    s8 hit;
    u8 id;
    u8 kind;

    hit = arg1->unk64;
    id = arg1->id;
    if (hit != 0) {
        if (hit == arg0->unk65) {
            return 0x7E;
        }
        arg0->unk65 = hit;
    } else {
        arg0->unk65 = 0;
    }

    table = (const u8*)arg0->collision_data;
    kind = table[(s8)id * 2];
    arg0->unk63 = kind;
    if ((s8)kind == 2) {
        return 0;
    }
    if (((s8)id >= 0x1A && (s8)id < 0x24)
        || ((s8)id >= 0x3D && (s8)id < 0x3F)) {
        g_Player.unkBD = 1;
    }
    if (arg0->unk63 == -1) {
        func_8002DF7C(arg1, -1);
        return 0x7F;
    }

    arg0->unk5C = (u8)arg0->unk5C - table[((s8)id * 2) + 1];
    arg0->unk42 |= 0x8000;
    if (arg0->unk5C <= 0) {
        arg0->unk5C = 0;
        func_8002DF7C(arg1, 1);
        return -1;
    }
    if (arg0->unk63 != 0) {
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    }
    func_8002DF7C(arg1, 0);
    return (s8)(id + 1);
}

void func_800BF638(struct BaseObj* arg0, s8 arg1, s16 arg2, s16 arg3)
{
    const u8* weights = &D_8010C6A0[0][0];
    s32 offset = (s8)arg1 * 6;
    s32 roll = get_random() & 0xFF;
    struct ItemObj* item;
    s32 index;
    s32 counter;

    if (engine_obj.stage == 5) {
        return;
    }

    counter = 0xFF;
    do {
        counter++;
        index = counter & 0xFF;
        roll = (roll & 0xFF) - weights[index + (offset & 0xFF)];
    } while ((u32)(roll & 0xFFFF) < 0x100);

    if (index == 0) {
        return;
    }
    item = find_free_item_obj();
    if (item == NULL) {
        return;
    }
    item->active = 0x21;
    item->id = 2;
    item->unk2 = counter - 1;
    item->x_pos.i.hi = arg2;
    item->y_pos.i.hi = arg3;
    item->backref = NULL;
    item->unk7C.value = 0;
    item->bg_offset = arg0->bg_offset;
}

void func_800AFB90(struct VisualObj* arg0)
{
    s32 index = arg0->unk2;
    s32 column = index + 4;
    s32 row = column < 0 ? index + 0x13 : column;

    arg0->on_screen = 1;
    arg0->unk38 = NULL;
    arg0->animation_table = (u32**)D_8010A2A0;
    arg0->unk40 = 0;
    arg0->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 2);
    row >>= 4;
    arg0->unk42 = (u16)((column - (row << 4)) | ((row + 0x1E0) << 6));
    func_80015D60(arg0, 0);
    if ((u8)arg0->unk5C.value != 0xFF) {
        func_8001540C(0, (u8)arg0->unk5C.value, arg0);
    }
    arg0->state = (u8)arg0->state + 1;
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800C8610(struct MiscObj* arg0)
{
    struct MainObj* owner = arg0->ext.misc_2.owner;

    arg0->on_screen = 1;
    if (arg0->unk2 == 0) {
        arg0->unk3C = (void*)owner->sprite_frames;
        arg0->animation_table = (u32**)owner->animation_table;
        arg0->unk40 = owner->unk40;
        arg0->unk42 = owner->unk42 & 0x7FFF;
    }
    arg0->unk16 = 1;
    arg0->unk2C = 0x5000;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->x_vel.val = D_8010DB48[get_random() & 7] + owner->unk20 / 2;
    arg0->y_vel.val = D_8010DB68[get_random() & 7];
    func_80015D60(arg0, arg0->ext.misc_2.unk58);
    arg0->state = (u8)arg0->state + 1;
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800BF76C(struct ItemObj* arg0)
{
    u16 flags;
    u8 kind;
    s32 blocked;

    arg0->active = 0x21;
    arg0->state = 1;
    arg0->unk5 = 0;
    arg0->unk15 = 0;
    arg0->animation_table = (const u8* const*)D_8010C61C;
    arg0->unk42 = 0x7807;
    arg0->unk16 = 6;
    arg0->unk40 = 0;
    arg0->bg_offset = 0;
    arg0->unk2 = (u8)arg0->unk2 & 0x7F;
    arg0->active |= 0x20;
    arg0->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 3);
    if (arg0->unk2 == 4) {
        arg0->unk42 = 0x780B;
    }

    kind = (u8)arg0->unk2;
    if ((u32)(kind - 7) < 8) {
        arg0->unk7C.value = 7;
    } else if ((u32)(kind - 0xF) < 2) {
        arg0->unk7C.value = 8;
    } else if ((s8)kind == 0x11) {
        arg0->unk7C.value = 9;
    } else if ((s8)kind == 0x12) {
        arg0->unk7C.value = 0xA;
        arg0->unk42 = 0x780B;
    } else {
        arg0->unk7C.value = kind;
    }

    kind = arg0->unk7C.value;
    arg0->unk68 = (struct Unk_unk68*)D_8010C674[kind];
    arg0->ext.item_2.unk82 = 0xF0;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    if (arg0->backref == NULL) {
        arg0->y_vel.val = FIXED(8);
        arg0->unk2C = 0x8000;
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->unk67 = 1;
    } else {
        arg0->y_vel.val = 0;
        arg0->unk2C = 0x8000;
        arg0->unk67 = 0;
    }

    blocked = 0;
    flags = engine_obj.unk5A;
    switch (kind) {
    case 7:
        if ((flags & 0xFF) == 0xFF
            || (((s32)flags >> (arg0->unk2 - 7)) & 1) != 0) {
            blocked = 1;
        }
        break;
    case 8:
        if ((flags & 0x3000) == 0x3000
            || (flags & (0x1000 << (arg0->unk2 - 0xF))) != 0) {
            blocked = 1;
        }
        break;
    case 9:
        if ((flags & 0x4000)
            || (flags & (0x4000 << (arg0->unk2 - 0x11))) != 0) {
            blocked = 1;
        }
        break;
    case 0xA:
        if ((flags & 0x8000)
            || (flags & (0x8000 << (arg0->unk2 - 0x12))) != 0) {
            blocked = 1;
        }
        break;
    }

    if (blocked) {
        arg0->state = 3;
        return;
    }
    ((u8*)&arg0->unk7C)[1] = 0;
    func_80015D60(arg0, kind);
    is_on_screen(BASE_OBJECT(arg0));
}

void func_80049E68(struct MainObj* arg0)
{
    u32 timer;
    s32 distance;

    func_8002B718(MOVING_OBJECT(arg0));

    timer = arg0->ext.main_10.timer - 1;
    arg0->ext.main_10.timer = timer;
    if (timer == 0) {
        arg0->unk24 = FIXED(2);
        arg0->unk20 = 0;
        arg0->unk62 = 0;
        arg0->unk50 = NULL;
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }

    if (arg0->unk15 == 0) {
        distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    } else {
        distance = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
    }
    if (distance >= 0x30) {
        arg0->ext.main_10.timer = 0x14;
        arg0->unk20 = 0;
        arg0->unk6 = 2;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_800BFCC0(struct ItemObj* arg0, u8 arg1)
{
    struct PlayerObj* player = &g_Player;
    s32 charge_step;
    s32 engine_step;
    u32 index;
    u32 selected;
    u8 buttons;
    u8 value;
    s8 current;
    s8 next;

    (void)arg0;
    if (arg1 == 2) {
        charge_step = 4;
        engine_step = 1;
    } else if (arg1 == 3) {
        charge_step = 0x10;
        engine_step = 2;
    } else if (arg1 == 6) {
        charge_step = 0x30;
        engine_step = 4;
    } else {
        charge_step = 0;
        engine_step = 0;
    }

    if (engine_obj.cur_character == 0 && g_Player.unk93 == 0) {
        index = 1;
        selected = 0;
        buttons = (u8)g_Player.unkB9;
        do {
            if (((buttons >> (index - 1)) & 1) != 0) {
                if (player->charge_levels[index] < player->charge_levels[selected]) {
                    selected = index;
                }
            }
            index++;
        } while (index < 9);

        if (selected != 0) {
            value = (u8)g_Player.charge_levels[0] + charge_step;
            g_Player.charge_levels[0] = value;
            if ((s8)value >= 0x31) {
                g_Player.charge_levels[0] = 0x30;
            }
        }
        value = (u8)player->charge_levels[selected] + charge_step;
        player->charge_levels[selected] = value;
        if ((s8)value >= 0x31) {
            player->charge_levels[selected] = 0x30;
        }
    } else {
        u8 mask = engine_obj.cur_character == 0
            ? (u8)((u8)g_Player.unkB9 >> (g_Player.unk93 - 1))
            : (u8)g_Player.unkB9;

        if ((mask & 1) != 0) {
            current = player->charge_levels[g_Player.unk93];
            if (current < 0x30) {
                next = current + charge_step;
                player->charge_levels[g_Player.unk93] = next;
                if (next >= 0x31) {
                    player->charge_levels[g_Player.unk93] = 0x30;
                }
                func_8001540C(0, 0x16, 0);
            } else {
                player->charge_levels[g_Player.unk93] = 0x30;
            }
        }
    }

    if ((engine_obj.unk5A & 0x4000) != 0) {
        value = (u8)engine_obj.unk5C[2] + engine_step;
        engine_obj.unk5C[2] = value;
        if ((s8)value >= 0x21) {
            engine_obj.unk5C[2] = 0x20;
        }
    }
}

void func_80033D54(struct PlayerObj* arg0)
{
    const struct PlayerInitialStateData* state;
    s32 index;

    func_80035EA4(arg0);
    arg0->unk5C = (u8)arg0->unk5C & 0x7F;
    if (arg0->unk5 == 0x11) {
        return;
    }

    arg0->unkA4 = 1;
    func_80033D10(arg0);
    index = arg0->unk63;
    arg0->unk15 = (u8)arg0->unkA5;
    func_800350A4(arg0, D_800F8AD0[index]);
    state = &D_800F8AD8[index];
    arg0->x_vel.val = state->unk20;
    arg0->unk28 = state->unk28;
    arg0->y_vel.val = state->unk24;
    arg0->unk2C = state->unk2C;
    if (arg0->unk15 != 0) {
        arg0->x_vel.val = -arg0->x_vel.val;
    }
    arg0->unk61 = D_800F8B28[index];
    if ((u8)(index - 2) < 2) {
        arg0->unk67 = 1;
    }
    func_8001540C(3, (get_random() & 1) ^ 1, arg0);
    arg0->unk5 = 0x11;
    arg0->unk6 = 0;
}

void func_8004A178(struct MainObj* arg0)
{
    s32 saved_x;
    s32 saved_y;
    s32 x_vel;
    s32 y_vel;
    u32 timer;
    s32 past_player;

    if (arg0->unk15 != 0) {
        past_player = arg0->x_pos.val > g_Player.x_pos.val;
    } else {
        past_player = g_Player.x_pos.val > arg0->x_pos.val;
    }

    if (!past_player) {
        timer = arg0->ext.main_10.timer - 1;
        arg0->ext.main_10.timer = timer;
        if (timer != 0
            && !(arg0->ext.main_10.hold_state == 1 && g_Player.unkBA != 0)) {
            saved_x = arg0->x_pos.val;
            saved_y = arg0->y_pos.val;
            if (arg0->unk15 != 0) {
                arg0->x_pos.i.hi = (u16)arg0->x_pos.i.hi + 0x18;
            } else {
                arg0->x_pos.i.hi = (u16)arg0->x_pos.i.hi - 0x18;
            }
            arg0->y_pos.i.hi = (u16)arg0->y_pos.i.hi + 0x18;
            func_8002B93C(MOVING_OBJECT(arg0), func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player)) & 0xFF);
            x_vel = arg0->unk20;
            y_vel = arg0->unk24;
            arg0->x_pos.val = saved_x;
            arg0->y_pos.val = saved_y;
            arg0->unk20 = x_vel + (x_vel / 2);
            arg0->unk24 = y_vel + (y_vel / 2);
            func_8002B718(MOVING_OBJECT(arg0));
            if (g_Player.unkBA != 0) {
                func_80015D60(arg0, 3);
                arg0->unk20 = 0;
                arg0->unk24 = 0;
                arg0->unk6 = 2;
            }
            func_80015DC8(ANIMATED_OBJECT(arg0));
            return;
        }
    }

    arg0->unk24 = FIXED(2);
    arg0->unk20 = 0;
    arg0->unk62 = 0;
    arg0->unk50 = NULL;
    arg0->unk5 = 5;
    arg0->unk6 = 0;
}

void func_80068548(struct MainObj* arg0)
{
    u8* shared = (u8*)&SP_CUR_MAIN_OBJ->ext;
    s32 column;
    s32 wrapped;
    s32 index;
    s32 row;
    s32 sub;
    s32 spawned_late;

    spawned_late = arg0->unk2 >= 6;
    if (!spawned_late) {
        shared[6] = 0;
        shared[5] = (s8)arg0->unk2 / 2;
        sub = (u8)arg0->unk2 & 1;
        arg0->unk2 = sub;
        index = func_8002938C(0x22);
        row = func_8002938C(0x22);
        if (shared[5] == 0 || (shared[5] == 2 && sub == 0)) {
            column = index * 4 + 0x18;
            wrapped = column < 0 ? index * 4 + 0x27 : column;
        } else {
            column = index * 4 + 0x1A;
            wrapped = column < 0 ? index * 4 + 0x29 : column;
        }
    } else {
        shared[6] = 1;
        if (arg0->unk2 != 9) {
            arg0->unk7A = 1;
        }
        index = func_8002938C(0x22);
        row = func_8002938C(0x22);
        column = index * 4 + 0x18;
        wrapped = column < 0 ? index * 4 + 0x27 : column;
    }

    row = row + 6 < 0 ? row + 9 : row + 6;
    arg0->unk42 = (u16)((column - ((wrapped >> 4) << 4))
        | (((row >> 2) + 0x1E0) << 6));
    if (spawned_late) {
        shared[5] = (u8)arg0->unk2;
    }

    arg0->unk40 = (u16)((u32)D_801406A8[func_8002938C(0x22)] >> 7);
    arg0->sprite_frames
        = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0x22));
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk15 = 0;
    arg0->unk61 = 0;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->animation_table = (const u8* const*)D_800FE0FC;
    arg0->unk68 = (struct Unk_unk68*)D_800FFB5C;
    arg0->unk50 = D_800FFB64;
    arg0->unk54 = D_800FFB60;
    arg0->collision_data = (const u16*)D_801076F8;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk16 = 6;
    arg0->unk5C = 6;
    arg0->unk60 = 3;
    func_80015D60(arg0, 1);
    arg0->state = 1;
    arg0->unk5 = shared[5] == 2 ? 7 : 2;
    if (shared[6] != 0) {
        arg0->unk15 = g_Player.x_pos.val < arg0->x_pos.val ? 0 : 0x40;
        if (arg0->unk2 != 9) {
            arg0->state = 3;
            arg0->unk5 = 0;
        } else {
            arg0->state = 1;
            arg0->unk5 = 2;
        }
    }
    arg0->unk6 = 0;
    shared[1] = 0;
    shared[3] = 0;
}

void func_8009EBA8(struct ShotObj* self)
{
    s32 velocity;
    s32 variant;
    s16 x;

    self->on_screen = 1;
    self->state = (u8)self->state + 1;
    variant = (u8)self->unk2 & 0xF;

    if (self->unk2 & 0x80) {
        self->y_vel.val = 0;
        velocity = variant == 1 ? -FIXED(3) : -FIXED(1.5);
        if (self->unk15 != 0) {
            velocity = FIXED(3);
        }
        self->x_vel.val = velocity;
        if (variant == 0) {
            self->y_vel.val = FIXED(1.5);
        }
        if (variant == 2) {
            self->y_vel.val = -FIXED(1.5);
        }
        self->unk28 = 0;
        self->unk2C = 0;
        func_80015D60(self, 0x10);
        self->unk60 = 2;
    } else {
        velocity = self->unk15 != 0 ? FIXED(3) : -FIXED(3);
        self->y_vel.val = FIXED(1.5);
        self->x_vel.val = velocity;
        self->unk28 = 0;
        self->unk2C = 0x4000;
        func_80015D60(self, 0x16);
        self->unk60 = 5;
    }

    x = self->x_pos.i.hi;
    if (self->unk15 != 0) {
        x += D_80109158[variant << 1];
    } else {
        x -= D_80109158[variant << 1];
    }
    self->x_pos.i.hi = x;

    self->unk16 = 6;
    self->unk68 = (struct Unk_unk68*)D_80109154;
    self->unk54 = D_80109150;
    self->unk50.data = D_80109150;
    self->unk67 = 0;
    self->y_pos.u.hi += (s8)D_80109158[(variant << 1) + 1];
}

void func_80068B80(struct MainObj* arg0)
{
    s32 velocity;

    arg0->collision_data = (const u16*)D_801076F8;
    arg0->unk54 = D_800FFB60;
    arg0->unk6 = (u8)arg0->unk6 + 1;
    arg0->unk50 = D_800FFB64;
    if (((u8*)&SP_CUR_MAIN_OBJ->ext)[6] == 0) {
        velocity = arg0->unk15 != 0 ? FIXED(1.75) : -FIXED(1.75);
    } else {
        velocity = arg0->unk15 != 0 ? FIXED(3) : -FIXED(3);
    }
    arg0->unk20 = velocity;
    arg0->unk28 = 0;
    arg0->unk24 = 0;
    arg0->unk2C = 0;
    func_80015D60(arg0, 1);
}

void func_80042950(struct MainObj* arg0)
{
    u8* ext = (u8*)&arg0->ext;
    u8 weapon;
    s32 flags;

    arg0->active = (u8)arg0->active | 4;
    weapon = (u8)g_Player.unk93;
    flags = 0;
    if (((s8)engine_obj.unk46 / 2) >= g_Player.unk5C) {
        flags = 1;
        ext[0] = 1;
    }
    if (engine_obj.cur_character == 0) {
        if (weapon != 0 && g_Player.charge_levels[weapon] < 0x19) {
            flags |= 2;
            ext[0] = 3;
        }
    }
    if ((flags & 0xFF) == 0) {
        func_8002B0C8(OBJECT_HEADER(arg0));
        return;
    }
    if ((flags & 0xFF) == 3) {
        ext[0] = g_Player.charge_levels[weapon] >= g_Player.unk5C ? 1 : 3;
    }
    arg0->state = (u8)arg0->state + 1;
}

void func_80040644(struct MainObj* arg0)
{
    u8* ext = (u8*)&arg0->ext;

    arg0->unk5C = 0x30;
    arg0->animation_table = (const u8* const*)D_800F9934;
    arg0->unk16 = 0x22;
    arg0->collision_data = (const u16*)D_801062F0;
    arg0->on_screen = 1;
    arg0->unk15 = 0;
    arg0->bg_offset = 0;
    arg0->unk60 = 1;
    arg0->unk61 = 0;
    arg0->unk50 = NULL;
    arg0->unk54 = NULL;
    engine_obj.enable_boss = 1;
    engine_obj.unk25 = 2;
    engine_obj.boss_ptr = arg0;
    arg0->x_pos.val = 0;
    arg0->y_pos.val = 0;
    func_80040760(PLAYER_OBJECT(arg0), 0);
    func_80040760(PLAYER_OBJECT(arg0), 1);
    func_80015D60(arg0, 0);

    arg0->unk5 = 6;
    arg0->unk24 = 0x18000;
    arg0->x_pos.val = 0x06200000;
    arg0->y_pos.val = 0;
    arg0->unk20 = 0;
    ext[0] = 1;
    ext[2] = 0;
    ext[3] = 0;
    ext[4] = 0;
    arg0->unk7C = 0;
    arg0->unk7E = 0;
    ext[6] = 0;
    ext[5] = 0;
    ext[1] = 0;
    arg0->state = (u8)arg0->state + 1;
    func_8002B318(BASE_OBJECT(arg0), 0xA0, 0xA0);
}

void func_80040838(struct MainObj* arg0)
{
    u8* ext = (u8*)&arg0->ext;
    s32 result;
    u8 saved_step;
    u8 saved_substep;
    s8 flash;
    s32 spawn;
    s32 blocked;
    u8 timer;
    u8 next;
    s16 x;
    s16 y;
    u8 offset_index;

    if (engine_obj.character_state.bytes[0] != 0) {
        ext[5] = 1;
    }
    saved_step = (u8)arg0->unk5;
    saved_substep = (u8)arg0->unk6;
    result = func_8002DD04(arg0);
    if (result < 0) {
        ext[5] = 2;
        arg0->unk5 = saved_step;
        arg0->unk6 = saved_substep;
        arg0->unk61 = 0x1E;
        arg0->unk42 &= 0x7FFF;
        func_8002B318(BASE_OBJECT(arg0), 0xA0, 0xA0);
        return;
    }
    if (result > 0) {
        arg0->unk5 = saved_step;
        arg0->unk6 = saved_substep;
        func_8001540C(2, 0xC, arg0);
        arg0->unk61 = 0x1E;
    }

    flash = arg0->unk61;
    if (flash != 0) {
        arg0->unk61 = flash - 1;
        if (flash & 2) {
            arg0->unk42 |= 0x8000;
        } else {
            arg0->unk42 &= ~0x8000;
        }
        if (arg0->unk61 == 0) {
            arg0->unk42 &= 0x7FFF;
        }
    }

    D_800F9988[arg0->unk5](arg0);

    blocked = func_8002B780() & 1;
    if (!blocked && ext[5] == 2) {
        spawn = ((u8)D_80141BD8.unk0 ^ 1) & 1;
        x = arg0->x_pos.i.hi;
        offset_index = (get_random() & 0x1F) % (COUNT(D_800F98EC) / 2);
        if (arg0->unk15 != 0) {
            x -= D_800F98EC[offset_index * 2];
        } else {
            x += D_800F98EC[offset_index * 2];
        }
        offset_index = (get_random() & 0x1F) % (COUNT(D_800F98EC) / 2);
        y = (s16)(arg0->y_pos.u.hi
            + (u16)D_800F98EC[offset_index * 2 + 1]);
        func_800AFAB4(0, x, y, (u8)spawn)->unk16 = 0x21;
        blocked = 1;
    }

    if (blocked && ext[5] == 2) {
        timer = ext[6];
        ext[6] = timer - 1;
        if (timer != 0) {
            return;
        }
        next = 4;
    } else {
        if (arg0->unk5C >= 0x18) {
            return;
        }
        timer = ext[6];
        ext[6] = timer - 1;
        if (timer != 0) {
            return;
        }
        next = 0x1E;
    }
    ext[6] = next;
    arg0->unk42 ^= 0x8000;
}

void func_800419B8(struct MainObj* arg0)
{
    s32 distance;

    func_8002B93C(MOVING_OBJECT(arg0),
        func_8002B7B0(OBJECT_HEADER(arg0), g_Player.x_pos.val, 0x01700000));

    distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if (distance < 0) {
        distance = -distance;
    }
    if (distance < 0x38) {
        distance = 0x38;
    } else if (distance >= 0x40) {
        distance = 0x40;
    }
    arg0->unk20 = (arg0->unk20 * distance) >> 4;

    distance = g_Player.y_pos.i.hi - (arg0->y_pos.i.hi + 0x40);
    if (distance < 0) {
        distance = -distance;
    }
    if (distance < 0x18) {
        distance = 0x18;
    } else if (distance >= 0x40) {
        distance = 0x40;
    }
    arg0->unk24 = (arg0->unk24 * distance) >> 4;

    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));

    distance = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
    if (distance < 0) {
        distance = -distance;
    }
    if (distance < 8) {
        s32 height = arg0->y_pos.i.hi - 0x170;

        if (height < 0) {
            height = -height;
        }
        if (height < 8) {
            arg0->y_pos.i.hi = 0x170;
            arg0->unk5 = 0xC;
            arg0->x_pos.i.hi = g_Player.x_pos.u.hi;
        }
    }

    func_8002B318(BASE_OBJECT(arg0), 0x90, 0x90);
}

void func_800B158C(struct VisualObj* arg0)
{
    struct PlayerObj* owner = arg0->unk50;

    if (owner->active == 0 || owner->state == 2) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk2 == 0) {
        arg0->x_pos.i.hi = (u16)owner->x_pos.i.hi + 0x58;
    } else {
        arg0->x_pos.i.hi = (u16)owner->x_pos.i.hi - 0x58;
    }
    arg0->y_pos.i.hi = (u16)owner->y_pos.i.hi - 0x38;

    if (((u8*)&MAIN_OBJECT(owner)->ext)[0] != 0) {
        arg0->unk42 = owner->unk42;
        func_8002B318(BASE_OBJECT(arg0), 0xA0, 0xA0);
        if (arg0->animation_step.fields.event != 0 && arg0->unk2 != 0) {
            arg0->animation_step.fields.event = 0;
            if (arg0->unk5 != 0) {
                func_8001540C(2, 5, owner);
            } else {
                func_8001540C(2, 6, owner);
            }
            arg0->unk5 ^= 1;
        }
    }
}

void func_80040CCC(struct MainObj* arg0)
{
    s32 distance;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    arg0->y_pos.u.hi += (s8)arg0->animation_step.fields.event;

    distance = g_Player.x_pos.val - arg0->x_pos.val;
    if (distance < 0) {
        distance = arg0->x_pos.val - g_Player.x_pos.val;
    }
    if (distance > 0x20000) {
        distance = 0x20000;
    }
    arg0->unk20 = distance;
    if (arg0->x_pos.val < g_Player.x_pos.val) {
        arg0->unk20 = -distance;
    }

    arg0->unk24 = 0;
    func_8002B718(MOVING_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x90, 0x90);

    arg0->unk15 = g_Player.x_pos.i.hi < arg0->x_pos.i.hi ? 0x40 : 0;
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5 = func_80040ABC(arg0);
    }
}

s32 func_80040ABC(struct MainObj* arg0)
{
    u8* ext = (u8*)&arg0->ext;
    const s8* flags = &engine_obj.character_state.bytes[1];
    s32 distance;
    s32 index;
    s32 kind;
    s32 value;
    s32 remainder;

    arg0->unk2 = get_random() & 1;
    if (ext[5] != 0) {
        return 8;
    }

    distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if (distance < 0) {
        distance = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
    }
    if (distance >= 0x49) {
        return 6;
    }

    index = (s32)(s16)arg0->x_pos.i.hi >> 4;
    if (index < 0x50) {
        return 0xC;
    }
    index -= 0x50;
    kind = D_800F986C[index];

    switch (kind) {
    case 0:
        value = get_random() & 3;
        if (value == 1) {
            ext[1] = 3;
            return 3;
        }
        if (value == 0) {
            return 0xC;
        }
        return value == 2 ? 2 : 5;
    case 1:
    case 2:
    case 3:
        ext[2 + ext[1]] = (u8)flags[ext[1]];
        kind = D_800F986C[index];
        if (ext[1 + kind] != 0) {
            return 2;
        }
        ext[1] = kind - 1;
        return 3;
    case 4:
        ext[1] = 3;
        return 3;
    case 5:
        return 2;
    case 6:
        return 5;
    case 8:
        value = func_8002B780();
        remainder = value - ((value >= 0 ? value >> 2 : (value + 3) >> 2) * 4);
        if (remainder >= 3) {
            return 0xC;
        }
        if (remainder > 0) {
            return 2;
        }
        if (remainder != 0) {
            return 0xC;
        }
        return 8;
    default:
        remainder = func_8002B780() % 3;
        if (remainder == 1) {
            ext[1] = 3;
            return 3;
        }
        return remainder == 0 ? 2 : 5;
    }
}

void func_80041060(struct MainObj* arg0)
{
    s32 velocity;
    u8 next_substep;
    u8 index = arg0->ext.main_0.index;
    s32 distance;

    if (index != 3) {
        distance = arg0->x_pos.i.hi - D_800F99BC[index];
        if (distance < 0) {
            distance = -distance;
        }
        if (distance < 2) {
            distance = arg0->y_pos.i.hi - 0x170;
            if (distance < 0) {
                distance = -distance;
            }
            if (distance < 2) {
                arg0->y_pos.val = 0x01700000;
                next_substep = (u8)arg0->unk6;
                velocity = -0xC000;
                arg0->unk15 = 0;
                goto start_attack;
            }
        }

        func_8002B93C(MOVING_OBJECT(arg0),
            func_8002B7B0(OBJECT_HEADER(arg0),
                (s32)D_800F99BC[index] << 16, 0x01700000));
        arg0->unk20 *= 2;
        arg0->unk24 *= 2;
        func_8002B718(MOVING_OBJECT(arg0));
        func_80015DC8(ANIMATED_OBJECT(arg0));
    } else {
        velocity = -0xC000;
        arg0->y_pos.val = 0x01700000;
        next_substep = (u8)arg0->unk6;

    start_attack:
        arg0->unk6 = next_substep + 1;
        if (arg0->unk15 != 0) {
            velocity = 0xC000;
        }
        arg0->unk20 = velocity;
        arg0->unk24 = 0x8000;
        func_80015D60(arg0, 1);
    }

    func_8002B318(BASE_OBJECT(arg0), 0x90, 0x90);
}

void func_800415B0(struct MainObj* arg0)
{
    s32 offset = engine_obj.cur_character == 0 ? 0x480000 : 0x4A0000;
    struct ShotObj* shot;
    struct MiscObj* misc;
    s32 target;
    s32 distance;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    target = arg0->unk15 != 0 ? g_Player.x_pos.val + offset
                              : g_Player.x_pos.val - offset;
    func_8002B93C(MOVING_OBJECT(arg0), func_8002B7B0(OBJECT_HEADER(arg0), target, 0x02140000));
    arg0->unk20 *= 4;
    arg0->unk24 *= 4;
    func_8002B718(MOVING_OBJECT(arg0));

    distance = arg0->x_pos.val - target;
    if (distance < 0) {
        distance = -distance;
    }
    if (distance <= 0x7FFFF) {
        distance = arg0->y_pos.i.hi - 0x214;
        if (distance < 0) {
            distance = -distance;
        }
        if (distance < 8) {
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0;
                shot->unk2 = 4;
                shot->unk7C = (struct WeaponObj*)arg0;
                shot->state = 0;
            }
            misc = find_free_misc_obj();
            if (misc != NULL) {
                misc->active = 0x41;
                misc->id = 4;
                misc->unk2 = 0;
                misc->ext.pointer.unk50 = arg0;
                misc->state = 2;
            }
            misc = find_free_misc_obj();
            if (misc != NULL) {
                misc->active = 0x41;
                misc->id = 4;
                misc->unk2 = 1;
                misc->ext.pointer.unk50 = arg0;
                misc->state = 2;
            }
            func_80015D60(arg0, arg0->unk7E != 0 ? 0xD : 0xF);
            arg0->unk20 = 0;
            arg0->x_pos.val = target;
            arg0->y_pos.i.hi = 0x214;
            arg0->unk6 = (u8)arg0->unk6 + 1;
            func_8001540C(2, 4, arg0);
        }
    }
    func_8002B318(BASE_OBJECT(arg0), 0x90, 0x90);
}

void func_800994DC(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;
    s32 animation;
    s32 x_offset;
    s32 velocity;

    arg0->unk40 = owner->unk40;
    arg0->animation_table = (u32**)owner->animation_table;
    arg0->unk3C = (void*)owner->sprite_frames;
    arg0->unk15 = owner->unk15;
    arg0->unk68 = NULL;
    arg0->unk54 = NULL;
    arg0->unk5C = 0;
    arg0->unk42 = owner->unk42;

    switch (arg0->unk2) {
    case 0:
    case 1:
        arg0->unk16 = 1;
        arg0->unk60 = 5;
        arg0->x_pos.val = owner->x_pos.val;
        arg0->y_pos.val = owner->y_pos.val;
        arg0->bg_offset = owner->bg_offset;
        if (arg0->unk2 == 0) {
            owner->unk54 = D_80108C68;
            arg0->unk50.data = D_80108C44;
            arg0->state = 1;
            func_80015D60(arg0, 2);
        } else {
            owner->unk54 = D_80108C6C;
            arg0->unk50.data = D_80108C4C;
            arg0->state = 2;
            func_80015D60(arg0, 4);
        }
        break;
    case 2:
    case 3:
        arg0->unk16 = 1;
        arg0->unk60 = 5;
        arg0->unk68 = (struct Unk_unk68*)D_80108C64;
        arg0->bg_offset = 0;
        arg0->unk42 &= 0x7FFF;
        x_offset = owner->unk15 == 0 ? 0x280000 : -0x280000;
        arg0->x_pos.val
            = owner->x_pos.val + (background_objects[0].x_pos.val + x_offset);
        arg0->y_pos.val = owner->y_pos.val + background_objects[0].y_pos.val;
        if (arg0->unk2 == 2) {
            velocity = owner->unk15 != 0 ? (-0x40000 | 0x8000) : 0x38000;
        } else {
            velocity = owner->unk15 != 0 ? (-0x30000 | 0x8000) : 0x28000;
        }
        arg0->x_vel.val = velocity;
        arg0->y_vel.val = 0x18000;
        arg0->unk2C = 0x1000;
        arg0->unk50.data = D_80108C54;
        arg0->unk28 = 0;
        arg0->state = 3;
        func_80015D60(arg0, 0xA);
        break;
    case 4:
        arg0->unk60 = 5;
        arg0->x_pos.val = owner->x_pos.val;
        arg0->bg_offset = 0;
        arg0->unk16 = 6;
        arg0->state = 5;
        arg0->y_pos.val = owner->y_pos.val;
        if (owner->unk7E != 0) {
            func_80015D60(arg0, 0xE);
            arg0->unk50.data = D_80108C5C;
            owner->unk54 = D_80108C70;
        } else {
            func_80015D60(arg0, 0xC);
            arg0->unk50.data = D_80108C60;
        }
        break;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x90, 0x90);
}

void func_800C899C(struct MiscObj* arg0)
{
    struct MainObj* owner = arg0->ext.pointer.unk50;
    s32 column;
    s32 wrapped;
    s32 row;
    s32 index;
    s16 count;

    arg0->animation_table = (u32**)D_8010DBC0;
    arg0->state = (u8)arg0->state + 1;

    index = func_8002938C(0x85);
    row = func_8002938C(0x85);
    column = index * 4 + 0x18;
    wrapped = column < 0 ? index * 4 + 0x27 : column;
    row = row + 6 < 0 ? row + 9 : row + 6;
    arg0->unk42 = (u16)((column - ((wrapped >> 4) << 4))
        | (((row >> 2) + 0x1E0) << 6));
    arg0->unk40 = (u16)((u32)D_801406A8[func_8002938C(0x85)] >> 7);
    arg0->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0x85));

    arg0->x_pos.val = (owner->unk15 == 0 ? owner->x_pos.i.hi + 0x30
                                         : owner->x_pos.i.hi - 0x30)
        << 16;
    arg0->y_pos.val = (owner->y_pos.i.hi - 0x5C) << 16;

    if (arg0->unk2 != 0) {
        func_800C813C(8, D_8010DBF8, arg0);
        func_800AF828(BASE_OBJECT(arg0), 2);
        arg0->unk16 = 1;
        arg0->animation_step.fields.frame_index = 2;
        func_80028BAC(0xA, 4, 2);
        func_8001540C(5, 1, arg0);
        arg0->bg_offset = 0;
    } else {
        arg0->unk16 = 6;
        arg0->animation_step.fields.frame_index = 1;
        arg0->bg_offset = 0;
    }
    arg0->unk15 = 0;
    arg0->x_vel.val = 0;

    count = owner->unk7C;
    if (count >= 0x15) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    owner->unk7C = count + 1;
    func_8002B318(BASE_OBJECT(arg0), 0x38, 0x20);
}

void func_800C0864(struct ItemObj* arg0)
{
    const u16* layout = (const u16*)&D_8010C8B4;
    s32 slot = arg0->unk2;

    if (engine_obj.checkpoint >= 2 && slot == 0) {
        func_800DABE4(D_8010C8B4.object_ids[slot * 0x10], 0, 0);
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }

    arg0->state = 0;
    arg0->unk5 = 1;
    arg0->active = 1;
    arg0->state = (u8)arg0->state + 1;
    arg0->animation_table = (const u8* const*)D_8010DBC0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk42 = 0x78C0;
    arg0->unk40 = (u16)((u32)D_801406A8[6] >> 7);
    arg0->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, 6);
    arg0->x_pos.i.hi = layout[slot * 8];
    arg0->unk58 = (const u8*)D_80108504;
    arg0->y_pos.i.hi = layout[slot * 8 + 1];
    arg0->unk5C = slot != 0 ? 0x20 : 0x50;
    arg0->unk75 = 1;
    arg0->ext.packed = 5;
    arg0->unk61 = 0;
    arg0->unk68 = NULL;
    arg0->on_screen = 0;
    arg0->unk7C.timer = 0;
    arg0->tail_ext.unk1.unk88 = 0;
    arg0->unk54 = (const u8*)D_8010C8F4[slot];
    arg0->tail_ext.unk1.unk84.previous_value = arg0->unk5C;
}

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

void func_800DABE4(u8 arg0, s32 arg1, s32 arg2)
{
    struct TileEffectRecord* record
        = D_80119388[engine_obj.stage * 2 + engine_obj.substage][arg0 & 0xFF];
    s16 origin_x = (s16)arg1;
    s16 origin_y = (s16)arg2;

    for (;;) {
        s16 x = record->x + origin_x;
        s16 y = record->y + origin_y;
        s32 count = record->packed_count >> 1;
        s32 horizontal = record->packed_count & 1;
        u16 bg_x = background_objects[record->layer].x_pos.i.hi;
        u16 bg_y = background_objects[record->layer].y_pos.i.hi;
        s32 i = 0;

        while (count != 0) {
            s16 tile_x = x;
            s16 tile_y = y;
            s32 visible = func_800DAB40((s16)bg_x, (s16)bg_y, tile_x, tile_y);

            if (tile_x < 0) {
                tile_x += 0xF;
            }
            if (tile_y < 0) {
                tile_y += 0xF;
            }
            func_800DADA0(record, (u16)(tile_x >> 4), (u16)(tile_y >> 4),
                (u8)i, (u8)visible);

            if (horizontal) {
                x += 0x10;
            } else {
                y += 0x10;
            }
            i++;
            if ((i & 0xFF) == count) {
                break;
            }
        }

        if (record->has_next == 0) {
            break;
        }
        record++;
    }
}

void func_800AF878(struct BaseObj* arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 x = arg2 & get_random();
    s16 y;
    u8 toggle;

    if (get_random() & 1) {
        x = arg0->x_pos.u.hi + (x & 0xFF);
    } else {
        x = arg0->x_pos.u.hi - (x & 0xFF);
    }

    y = arg3 & get_random();
    if (get_random() & 1) {
        y = arg0->y_pos.u.hi + (y & 0xFF);
    } else {
        y = arg0->y_pos.u.hi - (y & 0xFF);
    }

    toggle = D_8013B8E0[0] + 1;
    D_8013B8E0[0] = toggle;
    func_800AFAB4((s8)arg1, (s16)x, y, (toggle & 1) ^ 1);
}

void func_800C8BDC(struct MiscObj* arg0)
{
    struct MainObj* owner = arg0->ext.misc_4.owner;
    s32 column;
    s32 wrapped;
    s32 row;
    s32 index;

    arg0->unk5 = 0x10;
    arg0->state = (u8)arg0->state + 1;
    arg0->animation_table = (u32**)D_8010DBC0;

    index = func_8002938C(0x85);
    row = func_8002938C(0x85);
    column = index * 4 + 0x18;
    wrapped = column < 0 ? index * 4 + 0x27 : column;
    row = row + 6 < 0 ? row + 9 : row + 6;
    arg0->unk42 = (u16)((column - ((wrapped >> 4) << 4))
        | (((row >> 2) + 0x1E0) << 6));
    arg0->unk40 = (u16)((u32)D_801406A8[func_8002938C(0x85)] >> 7);
    arg0->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0x85));

    arg0->x_pos.i.hi = D_8010DC30[arg0->unk2].x;
    arg0->y_pos.i.hi = D_8010DC30[arg0->unk2].y;
    arg0->x_vel.val = owner->unk15 != 0 ? -0x60000 : 0x60000;

    func_8001540C(5, 1, arg0);
    func_8001540C(5, 0, arg0);
    func_800C813C(8, D_8010DC08, arg0);
    func_800C813C(8, D_8010DC10, arg0);
    func_800C813C(8, D_8010DC00, arg0);
    func_800C813C(8, D_8010DC10, arg0);

    func_800AFAB4(2, arg0->x_pos.i.hi + 0x10, arg0->y_pos.i.hi + 0x18, 0);
    func_800AFAB4(2, arg0->x_pos.i.hi - 8, arg0->y_pos.i.hi + 6, 1);
    func_800AFAB4(2, arg0->x_pos.i.hi, arg0->y_pos.i.hi - 0x1C, 0);
    func_800AFAB4(2, arg0->x_pos.i.hi - 0x16, arg0->y_pos.i.hi - 0x20, 1);
    func_800AFAB4(2, arg0->x_pos.i.hi + 6, arg0->y_pos.i.hi + 0x2C, 0);
    func_800AFAB4(2, arg0->x_pos.i.hi - 0xC, arg0->y_pos.i.hi + 0x20, 1);
}

void func_800C8E90(struct MiscObj* arg0)
{
    s8 timer = arg0->unk5;

    arg0->unk5--;
    switch (timer) {
    case 0:
        ZeroObjectState(OBJECT_HEADER(arg0));
        break;
    case 1:
        func_800AFAB4(2, arg0->x_pos.i.hi - 8, arg0->y_pos.i.hi + 6, 1);
        break;
    case 4:
        func_800AFAB4(2, arg0->x_pos.i.hi - 0xC,
            arg0->y_pos.i.hi + 0x20, 1);
        break;
    case 8:
        func_800AFAB4(2, arg0->x_pos.i.hi - 0x16,
            arg0->y_pos.i.hi - 0x20, 1);
        break;
    case 13:
        func_800AFAB4(2, arg0->x_pos.i.hi + 6,
            arg0->y_pos.i.hi + 0x2C, 0);
        break;
    case 15:
        func_800AFAB4(2, arg0->x_pos.i.hi, arg0->y_pos.i.hi - 0x1C, 0);
        break;
    }
}

void func_800B5798(struct EffectObj* arg0)
{
    const u16* trigger = arg0->ext.unk_effect.unk18;
    u32 i;

    if (func_8002B160(BASE_OBJECT(arg0)) != 0) {
        func_8002B0C8(OBJECT_HEADER(arg0));
        return;
    }

    if (trigger[0] < g_Player.x_pos.i.hi
        || g_Player.x_pos.i.hi < trigger[1]
        || trigger[2] < g_Player.y_pos.i.hi
        || g_Player.y_pos.i.hi < trigger[3]) {
        return;
    }

    background_objects[0].unk47 = 2;
    for (i = 4; trigger[i] != 0; i++) {
        const struct Effect00BackgroundUpdate* update
            = &D_8010AE74[trigger[i] - 1];
        *D_8010AF9C[update->object_index] = update->value;
    }
}

void func_800B10E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
    s32 arg5)
{
    s16 x_min = (s16)arg1;
    s16 y_min = (s16)arg2;
    s16 x_delta = (s16)((s16)arg3 - x_min);
    s16 y_delta = (s16)((s16)arg4 - y_min);
    s16 midpoint = x_min + x_delta / 2;
    s16 count = (s16)arg5;
    s16 i;

    for (i = 0; i < count; i++) {
        struct VisualObj* visual = find_free_visual_obj();
        u32 random_x;
        u32 random_y;
        u32 high;

        if (visual == NULL) {
            continue;
        }

        visual->active = 0x21;
        visual->id = 9;
        visual->unk2 = 0;

        high = (get_random() & 0xFF) << 8;
        random_x = (get_random() & 0xFF) + high + 1;
        high = (get_random() & 0xFF) << 8;
        random_y = (get_random() & 0xFF) + high + 1;

        visual->x_pos.i.hi
            = x_delta == 0 ? x_min
                           : x_min + ((s32)(u16)random_x % x_delta);
        visual->y_pos.i.hi
            = y_delta == 0 ? y_min
                           : y_min + ((s32)(u16)random_y % y_delta);
        visual->x_pos.i.lo = 0;
        visual->y_pos.i.lo = 0;

        switch ((u8)arg0 & 3) {
        case 1:
            visual->x_vel.val = 0;
            visual->y_vel.val = 0x10000;
            break;
        case 2:
            visual->x_vel.val
                = visual->x_pos.i.hi < midpoint ? -0x18000 : 0x18000;
            visual->y_vel.val = 0;
            break;
        default:
            visual->x_vel.val = 0;
            visual->y_vel.val = 0;
            break;
        }

        visual->unk15 = 0;
        visual->state = 0;
        visual->unk5 = 0;
        visual->unk6 = 0;
        visual->unk5C.value = (u8)arg0 >> 4;
    }
}

void func_80042A48(struct MainObj* arg0)
{
    arg0->unk5 = 0;
    arg0->unk2 = 0;
    arg0->state = (u8)arg0->state + 1;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->animation_table = (const u8* const*)D_800F9C18;
    arg0->unk16 = 4;
    arg0->unk5C = 1;
    arg0->unk60 = 1;
    arg0->unk50 = NULL;
    arg0->unk68 = NULL;
    arg0->collision_data = (const u16*)D_801063F0;
    arg0->unk67 = 0;
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk24 = 0;
    arg0->unk2C = 0;
    arg0->unk15 = (g_Player.x_pos.val >= arg0->x_pos.val) << 6;
    func_80015D60(arg0, 0);
}

void func_80042AFC(struct MainObj* arg0)
{
    struct ItemObj* item;
    s32 i;

    if (arg0->unk2 == 0) {
        for (i = 0; i < 2; i++) {
            arg0->unk54 = (const u8*)D_800F9C68[i];
            if (func_8002DD04(arg0) < 0) {
                func_800AF808(BASE_OBJECT(arg0));
                func_800C813C(D_800F9C78[i], D_800F9C70[i], arg0);
                if (i == 0) {
                    arg0->unk2 = 2;
                    arg0->unk5 = 2;
                    arg0->unk6 = 0;
                    arg0->unk5C = 1;
                    break;
                }
                goto spawn_item;
            }
        }
    } else if (func_8002DD04(arg0) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(3, D_800F9C48, arg0);
    spawn_item:
        item = find_free_item_obj();
        if (item != NULL) {
            item->active = 0x21;
            item->id = 2;
            item->unk2 = (u8)arg0->ext.main_10.timer;
            item->x_pos.val = arg0->x_pos.val;
            item->y_pos.val = arg0->y_pos.val;
            item->backref = NULL;
            item->bg_offset = arg0->bg_offset;
        }
        arg0->state = (u8)arg0->state + 1;
        return;
    }

    D_800F9C7C[arg0->unk5](arg0);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x40, 0x40) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
        return;
    }
    arg0->state = (u8)arg0->state + 1;
}

void func_80046B80(struct MainObj* arg0)
{
    arg0->unk5C = 0x7F;
    arg0->unk60 = 4;
    arg0->unk7C = 0;
    arg0->unk61 = 0;
    arg0->collision_data = (const u16*)D_801065F0;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk15 = g_Player.x_pos.val < arg0->x_pos.val ? 0 : 0x40;
    arg0->animation_table = (const u8* const*)D_800FA4E8;
    arg0->unk16 = 6;
    arg0->unk68 = &D_800FA424;
    arg0->unk54 = (const u8*)D_800FA428;
    arg0->unk50 = (const u8*)D_800FA428;
    arg0->ext.main_6.armor_broken = 0;
    arg0->ext.main_6.ground_probe_distance = 0;
    arg0->ext.main_6.armor_health = 0x12;
    arg0->ext.main_6.core_health = 9;
    arg0->ext.main_6.hitbox_toggle = 0;
    arg0->unk67 = 0;
    func_80015D60(arg0, 0);
    arg0->state = 1;
    arg0->unk5 = 2;
    arg0->unk6 = 0;
}

void func_80046C8C(struct MainObj* arg0)
{
    s32 facing_offset;

    func_80047378(arg0);
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FA544[arg0->unk5](arg0);

    arg0->unk5C = 0x7F;
    arg0->ext.main_6.hitbox_toggle ^= 1;
    if (arg0->ext.main_6.hitbox_toggle != 0) {
        arg0->unk54 += 4;
        arg0->unk50 += 4;
    } else {
        arg0->unk54 -= 4;
        arg0->unk50 -= 4;
    }
    func_8002D9BC(arg0);
    arg0->ext.main_6.saved_step = arg0->unk5;

    if (func_8002DD04(arg0) != 0) {
        if (arg0->ext.main_6.armor_broken == 0
            && arg0->ext.main_6.hitbox_toggle == 0) {
            arg0->ext.main_6.armor_health
                += arg0->unk5C - 0x7F;
        } else {
            arg0->ext.main_6.core_health += arg0->unk5C - 0x7F;
        }

        if ((s32)arg0->ext.main_6.core_health < 0) {
            if (arg0->ext.main_6.armor_broken == 0) {
                facing_offset = arg0->unk15 != 0 ? -0x24 : 0x24;
                func_800AFAB4(0, arg0->x_pos.i.hi + facing_offset,
                    arg0->y_pos.i.hi, 1);
                func_800AF808(BASE_OBJECT(arg0));
                facing_offset = arg0->unk15 != 0 ? 0x20 : -0x20;
                func_800AFAB4(0, arg0->x_pos.i.hi + facing_offset,
                    arg0->y_pos.i.hi, 1);
                facing_offset = arg0->unk15 != 0 ? 0x18 : -0x18;
                func_800AFAB4(0, arg0->x_pos.i.hi + facing_offset,
                    arg0->y_pos.i.hi - 0x1B, 1);
                func_800AFAB4(0, arg0->x_pos.i.hi + facing_offset,
                    arg0->y_pos.i.hi - 0x37, 1);
                func_800C813C(0xF, D_800FA528, arg0);
            } else {
                func_800AF808(BASE_OBJECT(arg0));
                facing_offset = arg0->unk15 != 0 ? -0x24 : 0x24;
                func_800AFAB4(0, arg0->x_pos.i.hi + facing_offset,
                    arg0->y_pos.i.hi, 1);
                func_800C813C(8, D_800FA528 + 7, arg0);
            }
            func_800BF60C(BASE_OBJECT(arg0), 0x13);
            arg0->state = 2;
            return;
        }

        if (arg0->ext.main_6.armor_broken == 0
            && (s32)arg0->ext.main_6.armor_health < 0) {
            facing_offset = arg0->unk15 != 0 ? 0x20 : -0x20;
            func_800AFAB4(0, arg0->x_pos.i.hi + facing_offset,
                arg0->y_pos.i.hi, 1);
            facing_offset = arg0->unk15 != 0 ? 0x18 : -0x18;
            func_800AFAB4(0, arg0->x_pos.i.hi + facing_offset,
                arg0->y_pos.i.hi - 0x1B, 1);
            func_800AFAB4(0, arg0->x_pos.i.hi + facing_offset,
                arg0->y_pos.i.hi - 0x37, 1);
            func_800C813C(7, D_800FA528, arg0);
            func_80015D60(arg0, 1);
            arg0->unk60 = 3;
            arg0->unk68 = &D_800FA430;
            arg0->unk54 = (const u8*)D_800FA434;
            arg0->unk50 = (const u8*)D_800FA434;
            arg0->unk5 = 2;
            arg0->unk6 = 0;
            arg0->ext.main_6.armor_broken = 1;
        }
    }

    if (func_8002B1E8(BASE_OBJECT(arg0), 0x68, 0x68) != 0) {
        arg0->state = 2;
    } else {
        func_8002B318(BASE_OBJECT(arg0), 0x48, 0x48);
    }
}

void func_80035C20(struct PlayerObj* arg0)
{
    s32 i;

    if ((arg0->unkC7 & 3) == 0) {
        for (i = 0; i < 4; i++) {
            func_80035D34((get_random() & 0x1F) | -0x80);
        }
    }

    if (arg0->unkC6 == 3) {
        arg0->unkC7 = 0x14;
        arg0->unk5 = (u8)arg0->unk5 + 1;
    } else if (arg0->unkC7 == 0) {
        func_80035D84(arg0->unkC6);
        if (arg0->unkC6 == 2) {
            func_80035D84(3);
        }
        arg0->unkC7 = 0x12;
        arg0->unkC6++;
    } else {
        arg0->unkC7--;
    }
}

void func_800CAE38(struct MiscObj* arg0)
{
    u8 variant = (u8)arg0->unk2;
    s32 animation;

    arg0->on_screen = 1;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk38 = NULL;
    arg0->animation_table = D_8011BF40;
    arg0->unk42 = 0x7802;
    arg0->unk40 = 0;
    arg0->unk16 = 0x10;
    arg0->unk15 = 0;
    arg0->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 1);
    arg0->x_pos.val = g_Player.x_pos.val;
    arg0->y_pos.val = g_Player.y_pos.val;

    func_8002B93C(MOVING_OBJECT(arg0), variant & 0x7F);
    if (variant & 0x80) {
        arg0->x_vel.val *= 8;
        arg0->y_vel.val *= 8;
        animation = 7;
    } else {
        arg0->x_vel.val += (arg0->x_vel.val / 2) * D_8010E68C[variant & 3];
        arg0->y_vel.val += (arg0->y_vel.val / 2) * D_8010E68C[variant & 3];
        animation = 6;
    }

    func_80015D60(arg0, animation);
    func_8002B718(MOVING_OBJECT(arg0));
    arg0->state = (u8)arg0->state + 1;
    func_8002B318(BASE_OBJECT(arg0), 0x80000, 0x80000);
}

void func_800200D4(struct EngineObj* arg0)
{
    s32 i;

    if (arg0->unkF > 0) {
        arg0->unk1E = 0;
        if (arg0->stage > 0 && arg0->stage < 9) {
            if (arg0->substage != 0) {
                arg0->state
                    = (((u8)arg0->palette_flags >> (arg0->stage - 1)) & 1)
                    ? 9
                    : 7;
            } else {
                arg0->substage++;
                arg0->state = 4;
            }
        } else if (arg0->substage == 0
            && (arg0->stage >= 0xB || arg0->stage == 0)) {
            arg0->substage = 1;
            arg0->state = 4;
        } else if (*(u16*)&arg0->stage == 0x10C) {
            arg0->state = 0xB;
        } else {
            arg0->state = 9;
            switch (arg0->stage) {
            case 0:
                arg0->unk5F = 2;
                break;
            case 9:
                arg0->unk5F = 4;
                break;
            case 0xA:
                arg0->unk5F = 7;
                break;
            case 0xB:
                arg0->unk5F = 0xA;
                break;
            }
        }
    } else if (arg0->unkF < 0) {
        arg0->unk1E = -1;
        func_8002B560(2, 0xE);
        arg0->unk45 = g_Player.unk5C;
        for (i = 0; i < 0x10; i++) {
            arg0->player_initial_data[i] = g_Player.charge_levels[i];
        }
        arg0->unk60 = g_Player.unk93;
        if (arg0->stage != 0xC
            || (*(u16*)&arg0->stage == 0xC && arg0->checkpoint == 0xA)) {
            arg0->unk42 = 1;
        }
        arg0->state = 5;
    } else {
        arg0->unk44--;
        if (arg0->unk44 < 0) {
            arg0->state = 8;
            if (*(u16*)&arg0->stage == 0xC) {
                for (i = 0; i < 0x10; i++) {
                    arg0->character_state.bytes[i] = 0;
                }
            }
        } else {
            arg0->unk1E = 0;
            if (func_8001FD7C(arg0) != 0) {
                arg0->checkpoint = 1;
            }
            if (*(u16*)&arg0->stage == 0x10C && D_80171EA8 != 0) {
                arg0->state = 4;
            } else {
                arg0->state = 5;
            }
        }
    }

    arg0->unk1 = 0;
    arg0->unkF = 0;
}

void func_800BFBD0(struct ItemObj* arg0)
{
    u8 health;
    u8 status;

    if (arg0->unk6 == 0) {
        arg0->ext.item_2.unk81--;
        if (arg0->ext.item_2.unk81 != 0) {
            return;
        }

        arg0->ext.item_2.unk81 = 2;
        health = g_Player.unk5C;
        status = health & 0x80;
        if ((health & 0x7F) >= engine_obj.unk46) {
            arg0->unk6 = 1;
            g_Player.unk5C = (u8)engine_obj.unk46 | status;
        } else {
            g_Player.unk5C = (health + 1) | status;
        }
        func_8001540C(0, 0xD, NULL);

        arg0->ext.item_2.unk80--;
        if (arg0->ext.item_2.unk80 == 0) {
            arg0->unk6 = 1;
        }
    } else {
        func_800C03BC(0);
        arg0->state = 3;
        arg0->unk5 = 0;
        arg0->active &= 0xF7;
    }
}

void func_800BBC50(struct EffectObj* arg0)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        D_8013E188[i] = -1;
    }
    g_FilterModeR = 0;
    g_FilterModeG = 0;
    g_FilterModeB = 0;
    g_FilterAmountR = 0;
    g_FilterAmountG = 0;
    g_FilterAmountB = 0;
    arg0->ext.effect_28.timer = 0x28;
    arg0->ext.effect_28.filter_timer = 4;
    arg0->ext.effect_28.pad1A = 3;
    arg0->ext.effect_28.palette_index = 0;
    func_8002B560(2, 1);
    arg0->state++;
    func_80028BAC(0x28, 4, 2);
    arg0->unk7 = 0x27;
}

void func_8002B560(s8 id, s8 subtype)
{
    s32 i;

    for (i = 0; i < 0x20; i++) {
        struct EffectObj* effect = &effect_objects[i];

        if (!effect->active)
            continue;
        if (id >= 0) {
            if (effect->id == id && effect->unk2 == subtype)
                ZeroObjectState(OBJECT_HEADER(effect));
        } else if (effect->id == (id & 0x7F)) {
            ZeroObjectState(OBJECT_HEADER(effect));
        }
    }
}

extern const void* D_8010CC5C[];
extern struct Unk_unk68 D_8010CC58;

void func_800C19F0(struct ItemObj* arg0)
{
    s32 index;
    s32 column;
    s32 row;

    arg0->active = 0x49;
    arg0->unk16 = 6;
    index = func_8002938C(0x80);
    arg0->unk40 = (u16)(D_801406A8[index] >> 7);
    index = func_8002938C(0x80);
    arg0->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
    column = (func_8002938C(0x80) << 2) + 0x18;
    row = func_8002938C(0x80);
    arg0->unk42 = (u16)((column - ((column >> 4) << 4))
        | ((((row + 6) >> 2) + 0x1E0) << 6));
    arg0->animation_table = (const u8* const*)D_8010CC5C;
    arg0->unk7C.timer = (u8)arg0->unk2 & 0x10;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk15 = 0;
    arg0->unk67 = 0;
    arg0->unk75 = 1;
    arg0->ext.packed = (u8)arg0->unk2 & 0x40;
    if ((u8)arg0->unk2 & 0xC0) {
        arg0->state = 2;
        arg0->unk68 = NULL;
    } else {
        arg0->state = 1;
        arg0->unk68 = &D_8010CC58;
    }
    arg0->unk5 = 0;
    arg0->unk2 &= 0xF;
    func_80015D60(ANIMATED_OBJECT(arg0), 0);
}

void func_800BBD88(struct EffectObj* arg0)
{
    if (arg0->ext.effect_28.finished) {
        D_8010BEE4[arg0->ext.effect_28.palette_index](arg0);
    } else if (--arg0->ext.effect_28.timer == 0) {
        arg0->ext.effect_28.finished = 1;
    }

    arg0->x_pos.i.hi = background_objects[0].x_pos.i.hi + 0xA0;
    arg0->y_pos.i.hi = background_objects[0].y_pos.i.hi + 0x80;
    if (--arg0->ext.effect_28.pad1A == 0) {
        func_800BBFCC(arg0);
        arg0->ext.effect_28.pad1A = 3;
    }
    if (arg0->unk7 == 0) {
        func_80028BAC(10, 4, 2);
        arg0->unk7 = 10;
    }
    arg0->unk7--;
}

void func_8002C26C(struct CollisionObj* arg0, struct CollisionObj* arg1)
{
    s16 center0 = arg0->x_pos.i.hi + arg0->collision_bounds->unk0;
    s16 center1 = arg1->x_pos.i.hi + arg1->collision_bounds->unk0;
    s16 edge0;
    s16 edge1;

    if (center1 < center0) {
        edge0 = center0 - arg0->collision_bounds->unk2;
        edge1 = center1 + arg1->collision_bounds->unk2;
    } else {
        edge0 = center0 + arg0->collision_bounds->unk2;
        edge1 = center1 - arg1->collision_bounds->unk2;
    }
    arg1->unk6C = edge0 - edge1;
}

void func_8002E294(struct PlayerObj* arg0, struct PlayerObj* arg1)
{
    s16 x_overlap;
    s16 y_overlap;

    if (arg1->unk68 == NULL || !func_8002C160(COLLISION_OBJECT(arg0), COLLISION_OBJECT(arg1)))
        return;
    func_8002C26C(COLLISION_OBJECT(arg0), COLLISION_OBJECT(arg1));
    func_8002C2EC(COLLISION_OBJECT(arg0), COLLISION_OBJECT(arg1));
    x_overlap = arg1->unk6C < 0 ? -arg1->unk6C : arg1->unk6C;
    y_overlap = arg1->unk6E < 0 ? -arg1->unk6E : arg1->unk6E;
    if ((arg0->unk66 == 0 && x_overlap < y_overlap) || arg0->unk66 > 0)
        arg1->x_pos.i.hi += arg1->unk6C;
    else
        arg1->y_pos.i.hi += arg1->unk6E;
}

void func_8002C36C(struct PlayerObj* arg0, struct PlayerObj* arg1, s32 slot)
{
    struct Unk_unk68* bounds0 = arg0->unk68;
    struct Unk_unk68* bounds1 = arg1->unk68;
    if (bounds0 == NULL || bounds1 == NULL) {
        if (slot == 0) {
            arg0->unk72 = 0;
            arg0->unk76 = 0;
        } else if (slot == 1) {
            arg0->unk73 = 0;
            arg0->unk77 = 0;
        } else if (slot == 2) {
            arg0->unk74 = 0;
            arg0->unk78 = 0;
        }
        return;
    }
    s16 x0 = arg0->x_pos.i.hi + bounds0->unk0;
    s16 y0 = arg0->y_pos.i.hi + bounds0->unk1;
    s16 x1 = arg1->x_pos.i.hi + bounds1->unk0;
    s16 y1 = arg1->y_pos.i.hi + bounds1->unk1;
    s16 dx = x0 >= x1 ? x0 - x1 : x1 - x0;
    s16 dy = y0 >= y1 ? y0 - y1 : y1 - y0;
    u8 flags = 0;

    if (dy == bounds0->unk3 + bounds1->unk3 && dx < bounds0->unk2 + bounds1->unk2) {
        flags |= y0 < y1 ? 4 : 8;
    }
    if (dx == bounds0->unk2 + bounds1->unk2 && dy < bounds0->unk3 + bounds1->unk3) {
        flags |= x0 < x1 ? 2 : 1;
        arg1->unk4A = arg0->unk75;
    }

    if (slot == 0)
        arg0->unk72 = flags;
    else if (slot == 1)
        arg0->unk73 = flags;
    else if (slot == 2)
        arg0->unk74 = flags;
    arg1->unk71 |= flags;

    if (slot == 0)
        arg0->unk76 = (flags & 0xB) != 0;
    else if (slot == 1)
        arg0->unk77 = (flags & 0xB) != 0;
    else if (slot == 2)
        arg0->unk78 = (flags & 0xB) != 0;
}

s8 func_800C1E7C(struct ItemObj* arg0)
{
    struct Unk_unk68* item_bounds;
    struct Unk_unk68* player_bounds;
    s16 item_x;
    s16 player_x;
    s16 dx;

    if (g_Player.unkA4 != 0 || g_Player.unk5 == 3 || g_Player.unk5 == 0xB)
        return 0;
    if (g_Player.unk2 != 0 && g_Player.unk8E != 0)
        return 0;
    if (g_Player.unk7A != 0 || arg0->x_pos.i.hi < g_Player.x_pos.i.hi)
        return 0;

    item_bounds = arg0->unk68;
    player_bounds = g_Player.unk68;
    item_x = arg0->x_pos.i.hi + item_bounds->unk0;
    player_x = g_Player.x_pos.i.hi + player_bounds->unk0;
    dx = item_x >= player_x ? item_x - player_x : player_x - item_x;
    if (dx > item_bounds->unk2 + player_bounds->unk2)
        return 0;
    if (g_Player.y_pos.i.hi - player_bounds->unk3 < arg0->y_pos.i.hi - item_bounds->unk3)
        return 0;
    return arg0->y_pos.i.hi + item_bounds->unk3 >= g_Player.y_pos.i.hi + player_bounds->unk3;
}

void func_80032FA4(struct PlayerObj* arg0)
{
    if (arg0->unkC4 == 0) {
        if (arg0->unk88.unsigned_bytes.collision_flags & 8) {
            func_8003443C(arg0);
            arg0->unk84 = 0;
        } else {
            func_800350A4(arg0, 0xB);
            arg0->unk2C = 0x4200;
            arg0->x_vel.val = 0;
            arg0->unk28 = 0;
            arg0->y_vel.val = 0;
            arg0->unk67 = -1;
            arg0->unk6++;
            arg0->unk84 = 0;
        }
        arg0->unk86 = 0;
    } else if (arg0->unk67 == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
}

void func_800C1C88(struct ItemObj* arg0, struct EngineObj* arg1,
    struct PlayerObj* arg2)
{
    static const s16 offsets[7] = { 0, 0x30, 0xA0, 0, 0x50, 0xB0, 0x5A0 };
    (void)arg2;

    if (arg0->animation_step.fields.event < 2) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.event == 1) {
            func_8001540C(0, 0x11, arg0);
            arg0->animation_step.fields.event = 0;
        }
        return;
    }

    arg1->unk10 = 0;
    arg1->unk12 = 0;
    if ((u8)arg0->unk2 < COUNT(offsets))
        background_objects[0].unk24 = arg0->x_pos.i.hi + offsets[(u8)arg0->unk2];
    background_objects[0].unk26 = arg0->x_pos.i.hi;
    arg0->unk5 = 3;
}

extern union AnimationStep* D_8010F008[3];

void func_800D03B0(struct MiscObj* arg0)
{
    s32 index;
    s32 column;
    s32 row;

    arg0->y_vel.val = 0xA0000;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0x2000;
    arg0->bg_offset = g_Player.bg_offset;
    index = func_8002938C(0x45);
    arg0->unk40 = (u16)(D_801406A8[index] >> 7);
    column = (func_8002938C(0x45) << 2) + 0x18;
    row = func_8002938C(0x45);
    arg0->unk42 = (u16)((column - ((column >> 4) << 4))
        | ((((row + 6) >> 2) + 0x1E0) << 6));
    index = func_8002938C(0x45);
    arg0->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
    arg0->animation_table = (u32**)D_8010F008;
    arg0->unk16 = 6;
    arg0->unk15 = 0;
    arg0->state = 1;
    arg0->unk5 = 0;
    func_80015D60(ANIMATED_OBJECT(arg0), 0);
}

s32 func_80034E2C(void)
{
    struct PlayerObj* player = &g_Player;

    player->unk6 = 0;
    player->unk5 = player->unkC1;
    func_80036088(player);
    switch ((u8)(player->unk5 - 0x14)) {
    case 0:
        if ((u8)(player->unk17 - 5) >= 2)
            func_80036534(player);
        player->unkC0 = -1;
        player->unk15 = player->unkC2;
        break;
    case 1:
        func_800350A4(player, 0x26);
        player->y_vel.val = 0;
        player->unk28 = 0;
        player->unk2C = 0;
        if (player->unkC2 == 0) {
            func_80034150(player);
            break;
        }
        player->unk15 = 0x40;
        break;
    case 2:
        func_800350A4(player, 3);
        player->unkC0 = -1;
        player->unk15 = player->unkC2;
        break;
    case 3:
        func_800350A4(player, 0xA);
        func_80035EA4(player);
        player->y_vel.val = 0x5D000;
        player->unk2C = 0x4200;
        player->x_vel.val = 0;
        player->unk28 = 0;
        player->unk67 = 1;
        player->unk15 = player->unkC2;
        break;
    case 4:
        func_800350A4(player, 0x6B);
        func_80036E98(player);
        player->unk15 = player->unkC2;
        break;
    }
    return 0;
}

void func_80033108(struct PlayerObj* arg0)
{
    if (engine_obj.unkF != 0) {
        func_80034F7C(arg0);
        return;
    }
    arg0->x_vel.val = arg0->animation_step.fields.event == 0 ? 0x8000 : 0x20000;
    if (arg0->unk15 == 0)
        arg0->x_vel.val = -arg0->x_vel.val;
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unkC2 == 0)
        func_80034150(arg0);
}

void func_800AFF78(struct VisualObj* arg0)
{
    struct PlayerObj* owner = arg0->unk50;
    u8 frame;
    s8 x_offset;
    s8 y_offset;

    arg0->x_pos.val = owner->x_pos.val;
    arg0->y_pos.val = owner->y_pos.val;
    arg0->on_screen = 0;
    arg0->unk15 = owner->unk15;

    switch (arg0->unk2) {
    case 0:
        frame = owner->animation_step.fields.frame_index;
        if (owner->unk15 == 0)
            arg0->x_pos.i.hi += (u8)D_8010A3A0[frame][0];
        else
            arg0->x_pos.i.hi -= (u8)D_8010A3A0[frame][0];
        arg0->y_pos.i.hi -= D_8010A3A0[frame][1];
        arg0->unk42 = owner->unk42;
        D_8010A414[arg0->state](arg0);
        return;

    case 1:
        arg0->x_pos.val += owner->unk15 == 0 ? -FIXED(75) : FIXED(75);
        arg0->y_pos.val += FIXED(2);
        arg0->unk42 = owner->unk42;
        break;

    case 3:
        frame = owner->animation_step.fields.frame_index;
        x_offset = D_8010A2B8[frame][0];
        y_offset = D_8010A2B8[frame][1];
        if (owner->unk15 == 0)
            arg0->x_pos.i.hi += x_offset;
        else
            arg0->x_pos.i.hi -= x_offset;
        arg0->y_pos.i.hi += y_offset;
        arg0->unk42 = (arg0->unk42 & 0x7FFF) | (owner->unk42 & 0x8000);
        D_8010A414[arg0->state](arg0);
        return;

    case 4:
        frame = owner->animation_step.fields.frame_index;
        x_offset = D_8010A32C[frame][0];
        y_offset = D_8010A32C[frame][1];
        if (owner->unk15 == 0)
            arg0->x_pos.i.hi += x_offset;
        else
            arg0->x_pos.i.hi -= x_offset;
        arg0->y_pos.i.hi += y_offset;
        arg0->unk42 = (arg0->unk42 & 0x7FFF) | (owner->unk42 & 0x8000);
        D_8010A414[arg0->state](arg0);
        return;

    case 5:
        arg0->unk42 = (arg0->unk42 & 0x7FFF) | (owner->unk42 & 0x8000);
        D_8010A414[arg0->state](arg0);
        return;
    }

    if (owner->state == 1)
        D_8010A414[arg0->state](arg0);
    else
        ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800B0320(struct VisualObj* arg0)
{
    struct PlayerObj* owner = arg0->unk50;
    s32 animation;

    if (arg0->unk2 == 3 || arg0->unk2 == 4) {
        s32 column;
        s32 row;
        s32 resource;

        arg0->animation_table = (u32**)D_800FADD0;
        column = (func_8002938C(9) << 2) + 0x18;
        row = func_8002938C(9);
        arg0->unk42 = (u16)((column - ((column >> 4) << 4))
            | ((((row + 6) >> 2) + 0x1E0) << 6));
        arg0->unk40 = (u16)((D_801406A8[1] >> 7) + 0xB0);
        resource = func_8002938C(9);
        arg0->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, resource);
    } else {
        arg0->unk3C = owner->unk3C;
        arg0->unk40 = owner->unk40;
        arg0->animation_table = owner->animation_table;
        arg0->unk42 = owner->unk42 & 0x7FFF;
    }

    arg0->bg_offset = 0;
    arg0->unk15 = owner->unk15;
    switch (arg0->unk2) {
    case 0:
        arg0->unk16 = 7;
        arg0->state++;
        animation = owner->unk17 + 1;
        break;
    case 1:
        arg0->unk16 = 7;
        animation = 0x15;
        break;
    case 2:
        arg0->unk16 = 5;
        animation = 0x16;
        break;
    case 3:
        animation = owner->unk17;
        arg0->unk16 = 7;
        arg0->unk54 = 0;
        arg0->state += 2;
        break;
    case 4:
        arg0->state += 2;
        animation = owner->unk17 + 1;
        break;
    case 5:
        animation = 0x17;
        arg0->unk16 = 4;
        arg0->state += 3;
        break;
    default:
        return;
    }

    func_80015D60(ANIMATED_OBJECT(arg0), animation);
    arg0->state++;
    func_8002B318(BASE_OBJECT(arg0), 0x90, 0x90);
}

void func_80047E58(struct MainObj* arg0)
{
    s32 collision;
    u8 frame;

    arg0->unk54 = engine_obj.cur_character == 0
        ? (const void*)&D_800FA740
        : (const void*)&D_800FA744;
    arg0->collision_data = (const u16*)D_801060F0;
    arg0->unk65 = arg0->ext.main_8.unk8B;
    func_8002DD04(arg0);

    arg0->collision_data = (const u16*)D_801066F0;
    frame = arg0->animation_step.fields.frame_index;
    if (frame >= 0x16 && frame < 0x18)
        arg0->unk54 = (const void*)&D_800FA73C;
    else if (frame >= 0x1F && frame < 0x21)
        arg0->unk54 = (const void*)&D_800FA738;
    else
        arg0->unk54 = (const void*)&D_800FA728;

    arg0->ext.main_8.unk8B = arg0->unk65;
    arg0->unk65 = arg0->ext.main_8.unk8C;
    collision = func_8002DD04(arg0);
    if (collision < 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        func_8002B318(BASE_OBJECT(arg0), 0x90, 0x90);
        g_Player.unk7A = 1;
        return;
    }
    if (collision > 0) {
        func_8001540C(2, 0x21, arg0);
        arg0->unk61 = 0x1E;
        if (arg0->unk7C != 0) {
            arg0->state = 3;
            arg0->unk5 = 0;
            arg0->unk6 = 0;
            arg0->unk42 |= 0x8000;
        }
    }

    arg0->ext.main_8.unk8C = arg0->unk65;
    D_800FAE38[arg0->unk5](arg0);

    if (arg0->unk61 != 0) {
        s8 timer = arg0->unk61--;
        if (timer & 2)
            arg0->unk42 |= 0x8000;
        else
            arg0->unk42 &= 0x7FFF;
        if (arg0->unk61 == 0)
            arg0->unk42 &= 0x7FFF;
    }

    func_8002D9BC(arg0);
    if (arg0->ext.main_8.unk88 != 0) {
        arg0->unk50 = arg0->ext.main_8.unk80;
        func_8002D9BC(arg0);
        arg0->unk50 = arg0->ext.main_8.unk84;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x90, 0x90);
}

void func_800BABA8(struct EffectObj* arg0)
{
    struct EffectObj* spawned;
    s32 stage = engine_obj.stage;

    if (stage >= 1 && stage <= 8
        && ((engine_obj.palette_flags >> (stage - 1)) & 1) != 0) {
        engine_obj.unkF = 1;
        return;
    }

    spawned = find_free_effect_obj();
    if (spawned != NULL) {
        spawned->active = 1;
        spawned->id = 4;
        arg0->ext.effect_24.spawned_effect = spawned;
    }
    arg0->ext.effect_24.timer = 0;
    arg0->ext.effect_24.unk1A = 5;
    arg0->ext.effect_24.unk1B = 0;
    arg0->state++;
}

void func_800BAC58(struct EffectObj* arg0)
{
    struct QuadObj* quad;

    if (arg0->ext.effect_24.timer != 0) {
        arg0->ext.effect_24.timer--;
        return;
    }

    quad = find_free_quad_obj();
    if (quad == NULL)
        return;
    quad->active = -0x7D;
    quad->id = 3;
    quad->unk2 = arg0->ext.effect_24.unk1B;
    D_8013B8E8[arg0->ext.effect_24.unk1B] = (struct EffectObj*)quad;
    arg0->ext.effect_24.timer = 2;
    arg0->ext.effect_24.unk1B++;
    if (arg0->ext.effect_24.unk1B == 0x16) {
        arg0->ext.effect_24.unk1B = 0;
        arg0->ext.effect_24.timer = 0xB4;
        arg0->unk5++;
    }
}

void func_800B5EEC(struct EffectObj* arg0)
{
    switch (arg0->unk5) {
    case 0:
        if (D_80173C84 != 0)
            break;
        if (ENGINE_STAGE_ID == 0x000A) {
            arg0->unk5 = D_80171EA8 == 0 ? 1 : 3;
        } else if (ENGINE_STAGE_ID == 0x010C || D_80171EA8 != 0) {
            arg0->unk5 = 3;
        } else if (engine_obj.substage != 0) {
            arg0->unk5++;
        } else {
            arg0->unk5 = 3;
        }
        break;

    case 1:
        D_80171EA8 = 1;
        func_80013AD8(D_8010B434[(u8)engine_obj.stage], 4,
            (CdLoadAddress)D_80141F38);
        arg0->unk5++;
        break;

    case 2:
        if (D_801406AC == 2 && D_8013BD40 == 0)
            arg0->unk5++;
        break;

    case 3:
        arg0->state++;
        break;
    }
}

void func_8008D5C8(struct MainObj* arg0)
{
    extern void* D_80105814[39];
    extern void* D_8013B8B4;
    extern struct MainObj* D_80171FE0;
    extern u8 D_80171FE5;
    s32 i;

    for (i = 0; i < 3; i++) {
        struct ShotObj* shot = find_free_shot_obj();

        if (shot == NULL)
            continue;
        shot->active = 0x41;
        shot->id = 0x35;
        shot->unk2 = i;
        shot->x_pos = arg0->x_pos;
        shot->y_pos = arg0->y_pos;
        shot->unk7C = (struct WeaponObj*)arg0;
        arg0->ext.main_74.children[i] = (struct MainObj*)shot;
    }

    arg0->unk15 = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->animation_table = (const u8* const*)D_80105814;
    arg0->unk16 = 6;
    arg0->collision_data = D_801062F0;
    arg0->unk60 = 9;
    arg0->unk61 = 0;
    arg0->unk62 = 0;
    D_8013B8B0 = NULL;
    D_8013B8B4 = NULL;
    arg0->unk68 = NULL;
    arg0->unk5C = 0;
    arg0->unk40 = (u16)((D_801406A8[0] >> 7) + 0xB0);
    D_80171FE0 = arg0;
    D_80171FE5 = 0;
    arg0->state = 3;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->ext.main_74.effect_state = 0;
    arg0->ext.main_74.pad8E = 0;
    arg0->ext.main_74.animation_index = 0x30;
    arg0->unk5++;
}

void func_800D4C50(struct QuadObj* arg0)
{
    u8 index = (u8)arg0->unk2;
    const u16* vertices = D_8010F774[index].vertex;

    arg0->bg_offset = -1;
    arg0->unk34 = 4;
    arg0->unk36 = 0x10;
    arg0->on_screen = 1;
    arg0->x_pos.val = 0;
    arg0->y_pos.val = 0;
    arg0->ext.quad_2.x_scale.bytes.fraction = 0;
    arg0->state++;
    arg0->unk14.val = (s32)vertices[0] << 16;
    arg0->unk18.val = (s32)vertices[1] << 16;
    arg0->unk1C.val = (s32)vertices[2] << 16;
    arg0->unk20.val = (s32)vertices[3] << 16;
    arg0->unk24.val = (s32)vertices[2] << 16;
    arg0->unk28.val = (s32)vertices[3] << 16;
    arg0->unk2C.val = (s32)vertices[0] << 16;
    arg0->unk30.val = (s32)vertices[1] << 16;
    arg0->ext.quad_2.x_scale.bytes.integer = index == 0x15 ? 0xF : 2;
    arg0->ext.quad_2.y_scale.bytes.fraction = 0;
    if (index == 0)
        D_8013B960[0] = 0;
}

void func_800D5144(struct QuadObj* arg0)
{
    u8 index;

    D_8010F88C[arg0->unk5](arg0);
    if (arg0->unk5 == 0 || D_8013B960[0] == 0
        || D_80141BD8.unk0 % 3 != 0) {
        return;
    }

    index = arg0->ext.quad_2.x_scale.bytes.fraction;
    arg0->unk34 = D_8010F87C[index];
    index++;
    arg0->ext.quad_2.x_scale.bytes.fraction = index;
    if (index == 0xE)
        arg0->ext.quad_2.x_scale.bytes.fraction = 0;
}

static u8 pc_func_800D41EC(s32* x, s32* y, s32 target_x, s32 target_y,
    s32 x_speed, s32 y_speed)
{
    u8 direction = func_8002B810(*x - target_x, *y - target_y);
    s32 table_index;
    s32 x_sign;
    s32 y_sign;

    if (direction < 8) {
        table_index = 8 - direction;
        x_sign = 1;
        y_sign = -1;
    } else if (direction < 0x10) {
        table_index = direction - 8;
        x_sign = -1;
        y_sign = -1;
    } else if (direction < 0x18) {
        table_index = 0x18 - direction;
        x_sign = -1;
        y_sign = 1;
    } else {
        table_index = direction - 0x18;
        x_sign = 1;
        y_sign = 1;
    }
    *x += (D_800F459C[table_index] * x_sign * x_speed) >> 4;
    *y += (D_800F45C0[table_index] * y_sign * y_speed) >> 4;
    return direction;
}

void func_800D4B30(struct QuadObj* arg0)
{
    u8 old_direction;
    u8 direction;
    s16 target_x = D_8010F728[(u8)arg0->unk2][0];
    s16 target_y = D_8010F728[(u8)arg0->unk2][1];

    arg0->ext.quad_2.x_scale.value += 0xC;
    old_direction = arg0->ext.quad_2.direction[0];
    arg0->ext.quad_2.direction[1] = old_direction;
    arg0->ext.quad_2.y_scale.value += 0xC;
    direction = pc_func_800D41EC(&arg0->x_pos.val, &arg0->y_pos.val,
        (s32)target_x << 16, (s32)target_y << 16, 0x28, 0x28);
    arg0->ext.quad_2.direction[1] = direction;
    if (((direction ^ old_direction) & 0x10) != 0) {
        arg0->x_pos.i.hi = target_x;
        arg0->y_pos.i.hi = target_y;
        arg0->state = 2;
        arg0->unk7 = 0x3C;
    }
    func_800D4984(arg0);
    quad_is_on_screen(arg0);
}

void func_8007DD98(struct MainObj* arg0)
{
    if (engine_obj.stage == 0xC) {
        *(s16*)magma_dragoon_arena_right = 0x2B0;
        magma_dragoon_arena_center[0] = 0x200;
        *(s16*)magma_dragoon_arena_left = 0x150;
        magma_dragoon_arena_floor[0] = 0x690;
        magma_dragoon_arena_ceiling[0] = 0x670;
    } else {
        *(s16*)magma_dragoon_arena_right = 0x1590;
        magma_dragoon_arena_center[0] = 0x14E0;
        *(s16*)magma_dragoon_arena_left = 0x1430;
        magma_dragoon_arena_floor[0] = 0x280;
        magma_dragoon_arena_ceiling[0] = 0x260;
    }

    arg0->animation_table = (const u8* const*)magma_dragoon_animations;
    arg0->unk16 = 5;
    arg0->unk50 = &D_80102A6C;
    arg0->unk61 = 0;
    arg0->ext.main_65.flash_timer = 0;
    arg0->unk62 = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk68 = NULL;
    arg0->collision_data = D_80107D7C;
    arg0->unk54 = NULL;
    arg0->unk40 = (u16)((D_801406A8[0] >> 7) + 0x160);

    if (engine_obj.stage == 0xC) {
        arg0->unk42 = 0x7888;
        arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[4];
        arg0->x_pos.i.hi = 0x2CE;
        arg0->y_pos.i.hi = 0x69F;
    } else {
        arg0->x_pos.i.hi = 0x15A5;
        arg0->y_pos.i.hi = 0x28F;
    }

    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    engine_obj.unk25 = 0;
    engine_obj.boss_ptr = arg0;
    arg0->unk60 = 4;
    arg0->unk5C = 0;
    arg0->unk67 = 0;
    arg0->unk5 = 2;
    arg0->state++;
    if (engine_obj.stage == 4)
        engine_obj.checkpoint = 3;
}

void func_8007F174(struct MainObj* arg0)
{
    s32 distance;

    if (arg0->ext.main_65.leap_frames != 0) {
        if (arg0->ext.main_65.leap_to_right != 0)
            distance = *(s16*)magma_dragoon_arena_right - (arg0->x_pos.i.hi + 0x30);
        else
            distance = (arg0->x_pos.i.hi - 0x30) - *(s16*)magma_dragoon_arena_left;
        if (distance < 0)
            distance = -distance;
        arg0->unk20 = (distance << 16)
            / arg0->ext.main_65.leap_frames;
        if (arg0->ext.main_65.leap_to_right == 0)
            arg0->unk20 = -arg0->unk20;
        arg0->ext.main_65.leap_frames--;
    }

    func_8002B694(ANIMATED_OBJECT(arg0));
    if ((arg0->unk70 & 8) != 0 && arg0->unk24 < 0) {
        if (arg0->ext.main_65.leap_to_right != 0)
            arg0->x_pos.i.hi = *(s16*)magma_dragoon_arena_right - 0x30;
        else
            arg0->x_pos.i.hi = *(s16*)magma_dragoon_arena_left + 0x30;
        func_80015D60(arg0, 6);
        magma_dragoon_spawn_flames(ANIMATED_OBJECT(arg0), 2);
        arg0->unk67 = 0;
        func_8001540C(2, 2, arg0);
        arg0->unk20 = 0;
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        arg0->unk6++;
    }
}

void func_8007FD24(struct MainObj* arg0)
{
    s32 hit = func_8002DD04(arg0);
    u8 flash;

    if (hit < 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->unk42 &= 0x7FFF;
        g_Player.unk7A = 1;
        func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
        return;
    }

    if (hit > 0 && hit != 0x7F) {
        arg0->ext.main_65.flash_timer = (hit == 0x19 || hit == 0x1A) ? 2 : 0x1E;
        arg0->collision_data = D_801060F0;
        if (hit == 8 || hit == 0x11) {
            arg0->unk5 = 0xD;
            arg0->unk6 = 0;
            arg0->ext.main_65.flash_timer = 0xFF;
        }
    }

    flash = arg0->ext.main_65.flash_timer;
    if (flash != 0) {
        arg0->ext.main_65.flash_timer--;
        if ((flash & 2) != 0)
            arg0->unk42 |= 0x8000;
        else
            arg0->unk42 &= 0x7FFF;
        if (arg0->ext.main_65.flash_timer == 0) {
            arg0->collision_data = D_80107D7C;
            arg0->unk42 &= 0x7FFF;
        }
    }

    magma_dragoon_step_funcs[(u8)arg0->unk5](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
    func_8002D9BC(arg0);
}

void func_800B06AC(struct VisualObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk50;
    u8 animation;

    if (owner->active == 0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (owner->unk7 != 0) {
        if (owner->unk7 >= 0)
            func_8002B318(BASE_OBJECT(arg0), 0x90, 0x90);
        return;
    }

    if (arg0->unk2 == 3) {
        animation = owner->unk17;
    } else {
        u8 frame = owner->animation_step.fields.frame_index;

        arg0->unk16 = (frame == 0x18 || frame == 0x1B
                          || frame == 0x1C || frame == 0x1D)
            ? 7
            : 5;
        animation = owner->unk17 + 1;
    }
    if (arg0->unk17 != animation)
        func_80015D60(ANIMATED_OBJECT(arg0), animation);
    else
        func_80015DC8(ANIMATED_OBJECT(arg0));

    if (arg0->animation_step.fields.event != 0) {
        owner->ext.main_8.unk89 = arg0->unk54 != 0 ? 0x1A : 0x1B;
        arg0->animation_step.fields.event = 0;
        arg0->unk54 ^= 1;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x90, 0x90);
}

void func_8004970C(struct MainObj* arg0)
{
    if (arg0->unk7E != 0) {
        arg0->unk7E--;
        return;
    }

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 1) {
        func_800B0CA0(0x21, 2, arg0, 0x18, 6);
        func_800B0CA0(0x22, 2, arg0, 0x18, 6);
        func_8001540C(2, 0x18, arg0);
        func_80028BAC(0xA, 4, 2);
        arg0->animation_step.fields.event = 0;
    }
    if (arg0->animation_step.fields.event < 0) {
        arg0->unk6++;
        engine_obj.enable_boss = 1;
        arg0->ext.main_9.animation_1 = (const u8*)&D_800FA734;
        arg0->unk7E = 3;
    }
}

void func_8004932C(struct MainObj* arg0)
{
    s32 x_pos = arg0->unk20;
    u8 frame = arg0->animation_step.fields.frame_index;

    if (frame >= 0x1C && frame <= 0x1D) {
        x_pos += arg0->unk15 != 0 ? -0x16 : 0x16;
    }
    arg0->x_pos.i.hi = (s16)x_pos;
    arg0->unk42 &= 0x7FFF;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->state = 1;
        if (arg0->unk7C != 0) {
            func_80015D60(ANIMATED_OBJECT(arg0), 0);
            arg0->unk5 = 1;
            arg0->unk7C = 1;
        } else {
            func_8004808C(arg0);
        }
        arg0->unk6 = 0;
        arg0->x_pos.i.hi = (s16)arg0->unk20;
    }
}

void func_800480D0(struct MainObj* arg0)
{
    s32 distance;
    u16 timer;
    u8 choice;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = (u16)arg0->unk7C;
    arg0->unk7C = (s16)(timer - 1);
    if (timer != 0)
        return;

    arg0->unk7C = 0;
    if (arg0->ext.main_8.unk8A++ >= 2) {
        arg0->ext.main_8.unk8A = 0;
        arg0->unk5 = arg0->unk5C < 0x19 ? 6 : 4;
        return;
    }

    distance = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
    if (distance < 0)
        distance = -distance;
    if (arg0->unk5C >= 0x19) {
        if (distance < 0x90) {
            if (arg0->unk15 != 0) {
                choice = 0x12B0 - arg0->x_pos.i.hi < 0xD0 ? 4 : 5;
            } else {
                choice = arg0->x_pos.i.hi - 0x11A0 < 0xD0 ? 4 : 5;
            }
        } else {
            choice = func_8002B780() % 8 < 3 ? 3 : 8;
        }
    } else if (distance < 0x90) {
        choice = func_8002B780() % 8 < 6 ? 7 : 5;
    } else {
        choice = func_8002B780() % 8 < 7 ? 7 : 6;
    }
    arg0->unk5 = choice;

    if (arg0->unk15 != 0) {
        if (g_Player.x_pos.val < arg0->x_pos.val)
            arg0->unk5 = 4;
    } else if (g_Player.x_pos.val >= arg0->x_pos.val) {
        arg0->unk5 = 4;
    }
}

static void main_8_crash_effects(struct MainObj* arg0)
{
    func_800B0CA0(0x21, 2, arg0, 0x18, 6);
    func_800B0CA0(0x22, 2, arg0, 0x18, 6);
    func_8001540C(2, 0x18, arg0);
    func_80028BAC(0xA, 4, 2);
}

void func_80048610(struct MainObj* arg0)
{
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 1) {
        main_8_crash_effects(arg0);
        arg0->animation_step.fields.event = 0;
    }
    if ((arg0->unk70 & 8) == 0)
        return;

    if (arg0->unk15 != 0)
        arg0->unk5 = g_Player.x_pos.val < arg0->x_pos.val ? 4 : 5;
    else
        arg0->unk5 = g_Player.x_pos.val < arg0->x_pos.val ? 5 : 4;
    arg0->unk6 = 0;
    main_8_crash_effects(arg0);
}

void func_80099F48(struct ShotObj* arg0)
{
    struct WeaponObj* owner = arg0->unk7C;
    s32 target;
    s32 offset;
    s32 subtype = arg0->unk2;
    s32 angle;

    arg0->unk40 = owner->unk40;
    arg0->unk42 = owner->unk42 & 0x7FFF;
    arg0->animation_table = owner->animation_table;
    arg0->unk3C = owner->unk3C;
    arg0->unk15 = owner->unk15;
    arg0->bg_offset = owner->bg_offset;
    arg0->x_pos.val = owner->x_pos.val
        + (owner->unk15 != 0 ? 0x530000 : -0x530000);
    arg0->y_pos.val = owner->y_pos.val;
    arg0->state = 1;
    arg0->on_screen = 1;

    if (subtype == 0) {
        angle = func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
        func_8002B93C(MOVING_OBJECT(arg0), angle & 0xFF);
        arg0->x_vel.val *= 4;
        arg0->y_vel.val *= 4;
    } else {
        offset = ((subtype - 1) * 11 << 17) - 0x200000;
        target = arg0->x_pos.val
            + (owner->unk15 != 0 ? offset : -offset);
        angle = func_8002B7B0(OBJECT_HEADER(arg0), target, 0x1E00000);
        func_8002B93C(MOVING_OBJECT(arg0), angle & 0xFF);
        arg0->x_vel.val *= 8;
        arg0->y_vel.val *= 8;
    }

    arg0->unk68 = (struct Unk_unk68*)D_80108CD8;
    arg0->unk50.data = D_80108CD0;
    arg0->unk5C = 1;
    arg0->unk60 = 3;
    arg0->unk16 = 0;
    arg0->unk54 = NULL;
    func_80015D60(ANIMATED_OBJECT(arg0), 0x17);
}

void func_8009A10C(struct ShotObj* arg0)
{
    struct WeaponObj* owner = arg0->unk7C;
    s32 subtype = arg0->unk2;
    s32 offset;
    s32 target;
    s32 angle;

    func_8002D9BC(arg0);
    if (subtype != 0) {
        offset = ((subtype - 1) * 19 << 16) - 0x200000;
        target = arg0->x_pos.val
            + (owner->unk15 != 0 ? offset : -offset);
        angle = func_8002B7B0(OBJECT_HEADER(arg0), target, 0x1E00000);
        func_8002B93C(MOVING_OBJECT(arg0), angle & 0xFF);
        arg0->x_vel.val *= 8;
        arg0->y_vel.val *= 8;
    }

    if (func_8002BB80(MAIN_OBJECT(arg0), MAIN_OBJECT(&g_Player)) != 0) {
        arg0->state = 2;
        return;
    }
    if ((arg0->unk70 & 8) != 0) {
        arg0->unk68 = NULL;
        arg0->state = 3;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x19, 0x19) != 0) {
        arg0->state = 2;
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x19, 0x19);
}

void func_8009A448(struct ShotObj* arg0)
{
    struct WeaponObj* owner = arg0->unk7C;

    arg0->unk40 = owner->unk40;
    arg0->animation_table = owner->animation_table;
    arg0->unk3C = owner->unk3C;
    arg0->unk15 = owner->unk15;
    arg0->unk16 = 5;
    arg0->unk68 = NULL;
    arg0->unk54 = NULL;
    arg0->unk60 = 5;
    arg0->state++;
    arg0->unk50.data = D_80108CF4;
    arg0->unk5C = 0x7F;
    arg0->bg_offset = owner->bg_offset;
    func_80015D60(ANIMATED_OBJECT(arg0), 0x14);
    func_8002B318(BASE_OBJECT(arg0), 0x90, 0x90);
}

void func_80048B04(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));

    if (arg0->animation_step.fields.frame_index != 0xC) {
        if (arg0->unk15 != 0) {
            arg0->x_pos.u.hi = arg0->unk20 - 8;
        } else {
            arg0->x_pos.u.hi = arg0->unk20 + 8;
        }
    }

    if (arg0->animation_step.fields.event == 2) {
        func_8001540C(2, 0x19, BASE_OBJECT(arg0));
        arg0->animation_step.fields.event = 0;
    }
    if (arg0->animation_step.fields.event == 1) {
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->x_pos.u.hi = arg0->unk20;
    }
}

void func_800BEBFC(struct ItemObj* arg0)
{
    u8 index = (u8)arg0->unk2;
    const struct Item01StageEntry* entry = &D_8010C160[index];

    arg0->active = 1;
    arg0->state++;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->x_pos.i.hi = entry->x;
    arg0->y_pos.i.hi = entry->y;
    arg0->animation_step.fields.frame_index = entry->flags_and_palette & 0x3F;
    arg0->y_vel.val = index == 9 ? 0x40000 : 0;
    arg0->unk2C = entry->velocity;
    arg0->unk40 = 0x1500;
    if (index == 8 || index == 9)
        arg0->unk42 = 0x7941;
    else if (index == 13)
        arg0->unk42 = 0x79C4;
    else
        arg0->unk42 = 0x7983;
    arg0->unk16 = 6;
    arg0->unk68 = (struct Unk_unk68*)&D_8010C250[index * 4];
    arg0->unk5C = 0x10;
    arg0->unk61 = 0;
    arg0->unk75 = 1;
    arg0->unk54 = &D_8010C28C[index * 4];
    arg0->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, 8);
    if (index == 1)
        arg0->unk66 = 1;
    arg0->unk58 = (const u8*)D_80108504;
    arg0->tail_ext.unk1.unk84.previous_value = 0;
    arg0->tail_ext.unk1.unk88 = 0;
}

void func_800BEFCC(struct ItemObj* arg0)
{
    u8 kind = (u8)arg0->unk2;
    const struct Item01StageEntry* entry = &D_8010C160[kind];
    u16 boundary;
    int reached_boundary;

    if (--arg0->ext.timer == 0) {
        if (kind == 8) {
            func_800B10E4(0x21, 0xA40, 0x1D0, 0xB80, 0x1F0, 1);
            func_800B10E4(0x22, 0xA40, 0x1D0, 0xB80, 0x1F0, 1);
        } else if (kind == 9) {
            func_800B10E4(0x21, 0xB80, 0x1D0, 0xC40, 0x1F0, 1);
            func_800B10E4(0x22, 0xB80, 0x1D0, 0xC40, 0x1F0, 1);
        }
        arg0->ext.timer = 4;
    }

    if ((kind == 5 || kind == 8) && arg0->tail_ext.unk1.unk84.previous_value == 0) {
        if (kind == 5 && arg0->tail_ext.unk1.unk88 == 0 && arg0->y_pos.i.hi >= 0x1C0) {
            func_8001540C(5, 0, NULL);
            func_80028BAC(0x20, 4, 1);
            arg0->tail_ext.unk1.unk88++;
        }
        if (arg0->y_pos.i.hi >= entry->trigger_x && !(entry->flags_and_palette & 0x40)) {
            func_800DABE4((u8)entry->sound_id, 0, 0);
            arg0->tail_ext.unk1.unk84.previous_value++;
        }
    }

    func_8002B694(ANIMATED_OBJECT(arg0));
    boundary = entry->right;
    reached_boundary = kind == 9
        ? arg0->y_pos.i.hi <= boundary
        : arg0->y_pos.i.hi >= boundary;
    if (reached_boundary) {
        arg0->y_pos.i.hi = boundary;
        arg0->ext.timer = 0;
        arg0->unk5++;
    }
}

void func_800BF1FC(struct ItemObj* arg0)
{
    u8 kind = (u8)arg0->unk2;
    const struct Item01StageEntry* entry = &D_8010C160[kind];
    int first;
    int last;
    int index;

    if (arg0->y_pos.i.hi == entry->trigger_x && !(entry->flags_and_palette & 0x40)) {
        func_800DABE4((u8)entry->sound_id, 0, 0);
        if (kind != 3 && kind != 4)
            arg0->state = 3;
    }
    if (kind != 13 && kind != 5 && kind != 1 && kind != 11) {
        func_8001540C(5, 0, NULL);
        func_80028BAC(0x20, 4, 1);
    }
    arg0->unk5++;

    if ((kind >= 2 && kind <= 7) || kind == 11 || kind == 13) {
        func_800B0CA0(0x21, 2, (struct MainObj*)arg0, 0x18, 6);
        func_800B0CA0(0x22, 2, (struct MainObj*)arg0, 0x18, 6);
    }

    if (kind == 1) {
        first = 0;
        last = 1;
    } else if (kind == 10) {
        first = 1;
        last = 4;
    } else if (kind == 11) {
        first = 4;
        last = 6;
    } else {
        return;
    }

    for (index = first; index < last; index++) {
        struct MainObj* obj = find_free_main_obj();
        s32 resource;

        if (obj == NULL)
            continue;
        obj->active = 0x41;
        obj->id = 7;
        obj->unk2 = index == 3 ? 3 : 2;
        obj->x_pos.i.hi = D_8010C2D8[index].x;
        obj->y_pos.i.hi = D_8010C2D8[index].y;
        resource = func_8002938C(7);
        obj->unk40 = (u16)((u32)D_801406A8[(u8)resource] >> 7);
        resource = func_8002938C(7);
        obj->unk42 = SOME_COORDINATE_CONVERSION((u8)resource);
        resource = func_8002938C(7);
        obj->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES,
            (u8)resource);
    }
}

void func_800BED6C(struct ItemObj* arg0)
{
    s32 collision;
    u8 index = (u8)arg0->unk2;

    if (index == 13)
        arg0->unk76 = -1;
    D_8010C300[(u8)arg0->unk5](arg0);
    func_8002B318(BASE_OBJECT(arg0), D_8010C250[index * 4 + 2],
        D_8010C250[index * 4 + 3]);
    func_8002E184((struct PlayerObj*)arg0);
    if (D_8010C160[index].flags_and_palette & 0x80)
        return;
    if (index == 12 && arg0->unk5 != 3)
        return;

    collision = func_8002DD04((struct MainObj*)arg0);
    if (collision < 0) {
        if (index == 12)
            func_800DABE4((u8)D_8010C160[12].sound_id, 0, 0);
        arg0->on_screen = 0;
        arg0->unk7C.timer = 60;
        arg0->state++;
        func_800C7DA4(15, D_8010C2C8, arg0, 0);
    } else if (collision > 0) {
        arg0->unk42 |= 0x8000;
    } else {
        arg0->unk42 &= 0x7FFF;
    }
}

void func_80047404(struct MainObj* arg0)
{
    u8 kind = (u8)arg0->unk2;

    arg0->unk5C = 6;
    arg0->unk60 = 3;
    arg0->unk61 = 0;
    arg0->collision_data = D_80106670;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk16 = 6;
    arg0->animation_table = (const u8* const*)D_800FA6BC;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk68 = NULL;
    arg0->unk50 = &D_800FA568;
    arg0->unk54 = &D_800FA568;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;

    if (kind == 1) {
        func_80015D60(arg0, 1);
        arg0->unk5 = 3;
        arg0->unk15 = 0x40;
        arg0->ext.main_7.unk90 = 1;
    } else if (kind >= 2 && kind <= 7) {
        func_80015D60(arg0, 0);
        arg0->unk5 = 2;
        arg0->unk7A = 1;
        arg0->unk61 = 1;
        arg0->unk15 = (kind & 1) ? 0x40 : 0;
        arg0->ext.main_7.unk80 = kind >= 6;
        arg0->ext.main_7.unk84 = kind >= 6 ? 0x28
            : kind >= 4                    ? 0x8C
                                           : 0x64;
        arg0->ext.main_7.unk90 = 0;
    } else {
        func_80015D60(arg0, 1);
        arg0->unk5 = 3;
        arg0->unk15 = 0;
        arg0->ext.main_7.unk90 = 1;
    }
    arg0->state = 1;
    arg0->unk6 = 0;
}

void func_80047818(struct MainObj* arg0)
{
    s32 distance;

    if (arg0->unk15 == 0) {
        if (g_Player.x_pos.val >= arg0->x_pos.val)
            return;
    } else if (arg0->x_pos.val >= g_Player.x_pos.val) {
        return;
    }
    distance = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
    if (distance < 0)
        distance = -distance;
    if ((!arg0->ext.main_7.unk80 && distance < (s32)arg0->ext.main_7.unk84) || (arg0->ext.main_7.unk80 && distance > (s32)arg0->ext.main_7.unk84)) {
        arg0->unk7A = 0;
        arg0->unk6 = 1;
    }
}

void func_80047D04(struct MainObj* arg0)
{
    struct VisualObj* visual;

    arg0->ext.main_8.unk89 = 0xFF;
    arg0->ext.main_8.unk8B = 0;
    arg0->ext.main_8.unk8C = 0;
    arg0->on_screen = 1;
    arg0->unk15 = 0;
    arg0->bg_offset = 0;
    arg0->unk67 = 1;
    arg0->unk5C = 0;
    arg0->unk60 = 3;
    arg0->unk61 = 0;
    arg0->unk16 = 6;
    arg0->animation_table = (const u8* const*)D_800FAD68;
    arg0->unk68 = (struct Unk_unk68*)&D_800FA724;
    arg0->collision_data = (const u16*)D_801066F0;
    arg0->unk54 = (const u8*)&D_800FA728;
    arg0->unk50 = (const u8*)&D_800FA72C;
    arg0->ext.main_8.unk84 = &D_800FA72C;
    arg0->ext.main_8.unk88 = 1;
    arg0->ext.main_8.unk80 = 0;
    arg0->unk40 = (u16)((D_801406A8[0] >> 7) + 0xB0);
    engine_obj.unk25 = 2;
    engine_obj.boss_ptr = arg0;
    func_80015D60(arg0, 0);
    arg0->unk5 = 9;
    arg0->state++;

    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 6;
        visual->unk50 = (struct PlayerObj*)arg0;
        visual->unk2 = 0;
    }
    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 6;
        visual->unk50 = (struct PlayerObj*)arg0;
        visual->unk2 = 5;
    }
    arg0->x_pos.val = FIXED(0xF60);
    arg0->y_pos.val = FIXED(0x170);
}

void func_80044F88(struct MainObj* arg0)
{
    arg0->state = 1;
    arg0->unk5 = 2;
    arg0->unk7C = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->animation_table = (const u8* const*)D_800FA300;
    arg0->unk54 = (const u8*)&D_800FA100;
    arg0->unk50 = (const u8*)&D_800FA104;
    arg0->collision_data = D_80106570;
    arg0->unk60 = 3;
    arg0->unk15 = g_Player.x_pos.val < arg0->x_pos.val ? 0 : 0x40;
    arg0->unk16 = 5;
    arg0->unk68 = NULL;
    arg0->unk5C = 2;
    arg0->unk61 = 0;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    if (arg0->unk2 == 1)
        arg0->unk5 = 5;
    else if (arg0->unk2 == 2)
        arg0->unk5 = 6;
    else if (arg0->unk2 == 3)
        arg0->unk5 = 8;
    else if (arg0->unk2 == 4)
        arg0->unk5 = 9;
    func_80015D60(arg0, 1);
}

void func_80099D54(struct ShotObj* arg0)
{
    u8 kind = (u8)arg0->unk2;

    arg0->unk58.animation_steps = D_80105FF0;
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk42 &= 0x7FFF;
    arg0->x_pos.i.hi += D_80108CC0[kind][0];
    arg0->x_vel.val *= 3;
    arg0->y_vel.val *= 3;
    arg0->unk54 = D_80108CBC;
    arg0->unk50.data = D_80108CBC;
    arg0->unk60 = 2;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->unk5C = 1;
    arg0->y_pos.i.hi += D_80108CC0[kind][1];
    func_80015D60(arg0, 8);
}

void func_800B0CA0(s32 type, s32 mode, struct MainObj* source, s32 radius,
    s32 count)
{
    const struct Unk_unk68* bounds = source->unk68;
    s32 left = source->x_pos.i.hi;
    s32 right = left;
    s32 base_y = source->y_pos.i.hi + bounds->unk1;
    s32 top = base_y;
    s32 bottom = base_y;
    s32 width;
    s32 height;
    s32 i;

    switch ((u8)mode) {
    case 1:
    case 2:
        if (source->unk15 == 0) {
            left = source->x_pos.i.hi + bounds->unk0 - bounds->unk2;
            right = left + bounds->unk2 * 2;
        } else {
            right = source->x_pos.i.hi - bounds->unk0 + bounds->unk2;
            left = right - bounds->unk2 * 2;
        }
        if ((u8)mode == 1)
            top = bottom = base_y - bounds->unk3;
        else
            top = bottom = base_y + bounds->unk3;
        break;
    case 3:
        left = source->unk15 == 0
            ? source->x_pos.i.hi + bounds->unk0 - bounds->unk2
            : source->x_pos.i.hi - bounds->unk0 + bounds->unk2;
        right = left;
        top -= bounds->unk3;
        bottom += bounds->unk3;
        break;
    case 4:
        left = source->unk15 == 0
            ? source->x_pos.i.hi + bounds->unk0 + bounds->unk2
            : source->x_pos.i.hi - bounds->unk0 - bounds->unk2;
        right = left;
        top -= bounds->unk3;
        bottom += bounds->unk3;
        break;
    default:
        break;
    }
    left -= radius;
    top -= radius;
    right += radius;
    bottom += radius;
    width = (s16)(right - left);
    height = (s16)(bottom - top);

    for (i = 0; i < (s16)count; i++) {
        struct VisualObj* visual = find_free_visual_obj();
        u32 random_value;

        if (visual == NULL)
            continue;
        visual->active = 0x21;
        visual->id = 9;
        visual->unk2 = 0;
        random_value = ((get_random() & 0xFF) << 8) | (get_random() & 0xFF);
        visual->x_pos.i.hi = width == 0 ? left : left + (random_value + 1) % width;
        random_value = ((get_random() & 0xFF) << 8) | (get_random() & 0xFF);
        visual->y_pos.i.hi = height == 0 ? top : top + (random_value + 1) % height;
        visual->x_pos.u.lo = 0;
        visual->y_pos.u.lo = 0;
        if (((u8)type & 3) == 1) {
            visual->x_vel.val = 0;
            visual->y_vel.val = FIXED(1);
        } else if (((u8)type & 3) == 2) {
            visual->x_vel.val = visual->x_pos.i.hi < source->x_pos.i.hi
                ? FIXED(-1.5)
                : FIXED(1.5);
            visual->y_vel.val = 0;
        } else {
            visual->x_vel.val = 0;
            visual->y_vel.val = 0;
        }
        visual->unk15 = 0;
        visual->state = 0;
        visual->unk5 = 0;
        visual->unk6 = 0;
        visual->unk5C.value = (u8)type >> 4;
    }
}

void func_800349F4(struct PlayerObj* arg0)
{
    func_80038524(arg0, 0xE);
    func_8001540C(1, 3, BASE_OBJECT(arg0));
    func_800363B8(arg0, 2);
    arg0->unk67 = 1;
    if (arg0->input.buttons.held & 0x100) {
        arg0->unk84 = 1;
        arg0->unk86 = 1;
        arg0->unk8C = 1;
    } else {
        func_80036034(arg0);
    }
    if (arg0->unk88.bytes.collision_flags & 1) {
        arg0->unk15 = 0x40;
        arg0->x_vel.val = arg0->unk84 != 0 ? FIXED(-4.125) : FIXED(-2);
    } else {
        arg0->unk15 = 0;
        arg0->x_vel.val = arg0->unk84 != 0 ? FIXED(4.125) : FIXED(2);
    }
    arg0->y_vel.val = FIXED(5.625);
    arg0->unk28 = 0;
    arg0->unk2C = 0x4200;
    arg0->unk8A.bytes.low = 10;
    func_8003698C(arg0);
    arg0->unk5 = 10;
    arg0->unk6 = 0;
}

void func_80034B64(struct PlayerObj* arg0)
{
    func_80038524(arg0, 0xB);
    arg0->x_vel.val = (arg0->unk88.bytes.collision_flags & 1)
        ? FIXED(-2)
        : FIXED(2);
    arg0->unk2C = 0x4200;
    arg0->unk8A.bytes.low = 4;
    arg0->unk67 = -1;
    arg0->unk5 = 0xB;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk6 = 1;
}

void func_800C044C(struct ItemObj* arg0)
{
    u8 index = (u8)arg0->unk2;
    const struct PcItem03StageEntry* entry = &D_8010C740[index];

    arg0->state++;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->x_pos.i.hi = entry->x;
    arg0->y_pos.i.hi = entry->y;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->animation_step.fields.frame_index = entry->object_id;
    arg0->x_vel.val = index < 10 || index == 20 ? 0x4000 : -0x4000;
    arg0->unk40 = 0x1500;
    arg0->unk42 = 0x79C1;
    arg0->unk16 = 6;
    arg0->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, 8);
    arg0->unk61 = 0;
    arg0->unk68 = index == 4 || index == 14
        ? (struct Unk_unk68*)D_8010C8A0
        : NULL;
    arg0->unk75 = 1;
    arg0->ext.packed = 0;
}

void func_800C7DA4(s32 count, const u8* variants, void* source, s32 x_velocity)
{
    struct BaseObj* source_obj = source;

    while ((u8)count != 0) {
        struct MiscObj* obj = find_free_misc_obj();

        if (obj != NULL) {
            obj->active = 0x41;
            obj->id = 2;
            obj->unk15 = get_random() & 0x40;
            obj->state = 0;
            obj->unk5 = 0;
            obj->unk6 = 0;
            if (x_velocity == -1) {
                obj->x_vel.val = 0;
                obj->unk2 = 1;
            } else {
                obj->x_vel.val = x_velocity;
                obj->unk2 = 0;
            }
            obj->x_pos.val = source_obj->x_pos.val + D_8010DB08[get_random() & 7];
            obj->y_pos.val = source_obj->y_pos.val + D_8010DB28[get_random() & 7];
            obj->ext.unk.unk54 = *variants++;
        }
        count--;
    }
}

void func_800C7F1C(struct MiscObj* arg0)
{
    s32 index;

    arg0->on_screen = 1;
    arg0->animation_step.fields.frame_index = arg0->ext.unk.unk54;
    if (engine_obj.stage == 3) {
        index = func_8002938C(0x8A);
        arg0->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
        index = func_8002938C(0x8A);
        arg0->unk40 = (u16)((u32)D_801406A8[index] >> 7);
        arg0->unk42 = 0x7987;
    } else {
        index = func_8002938C(0x83);
        arg0->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
        index = func_8002938C(0x83);
        arg0->unk40 = (u16)((u32)D_801406A8[index] >> 7);
        if (arg0->unk2 == 0)
            arg0->unk42 = 0x7983;
        else
            arg0->unk42 = SOME_COORDINATE_CONVERSION(func_8002938C(0x83));
    }
    arg0->unk16 = 1;
    arg0->unk2C = 0x5000;
    arg0->x_vel.val += D_8010DAC8[get_random() & 7];
    arg0->y_vel.val = D_8010DAE8[get_random() & 7];
    arg0->state++;
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800D0828(struct MiscObj* arg0)
{
    s32 resource;

    if (engine_obj.cur_character == 0 || engine_obj.character_state.bytes[8] != 0) {
        func_8002B108(OBJECT_HEADER(arg0));
        return;
    }
    arg0->bg_offset = g_Player.bg_offset;
    arg0->y_vel.val = FIXED(10);
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0x2000;
    resource = func_8002938C(0x42);
    arg0->unk40 = (u16)((u32)D_801406A8[resource] >> 7);
    resource = func_8002938C(0x42);
    arg0->unk42 = SOME_COORDINATE_CONVERSION(resource);
    resource = func_8002938C(0x42);
    arg0->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, resource);
    arg0->animation_table = (u32**)D_8010F078;
    arg0->unk16 = 6;
    arg0->unk15 = 0;
    arg0->state = 1;
    arg0->unk5 = 0;
    arg0->ext.unk.unk55 = 0;
    func_80015D60(arg0, 0);
}

void func_800BC784(struct EffectObj* arg0)
{
    struct Effect33Ext* ext = &arg0->ext.effect_33;

    switch (arg0->unk2 & 0xF0) {
    case 0x00:
        if (arg0->x_pos.i.hi < g_Player.x_pos.i.hi) {
            ext->timer = 1;
            ext->period = 0x50;
            arg0->state = 1;
        }
        return;
    case 0x10:
        ext->timer = 0x3C;
        ext->period = 0x26;
        ext->cooldown = 0x8C;
        ext->burst = 4;
        arg0->state = 1;
        arg0->unk5 = 0;
        ext->variant = arg0->unk2 & 0xF;
        return;
    case 0x20:
        switch (arg0->unk2 & 0xF) {
        case 0:
            ext->timer = 1;
            ext->period = 0x3C;
            ext->proximity = 0;
            ext->variant = 0;
            break;
        case 1:
            ext->timer = 1;
            ext->period = 0x50;
            ext->proximity = 0;
            ext->variant = 0;
            break;
        case 2:
            ext->timer = 1;
            ext->period = 0x64;
            ext->proximity = 0;
            ext->variant = 0;
            break;
        case 3:
            ext->timer = 0xB4;
            ext->period = 0xB4;
            ext->proximity = 1;
            ext->variant = 0;
            break;
        case 4:
            ext->timer = 1;
            ext->period = 0x78;
            ext->proximity = 0;
            ext->variant = 1;
            break;
        case 5:
            ext->timer = 1;
            ext->period = 0xB4;
            ext->proximity = 0;
            ext->variant = 1;
            break;
        case 6:
            ext->timer = 0x3C;
            ext->period = 0x3C;
            ext->proximity = 1;
            ext->variant = 0;
            break;
        case 7:
            ext->timer = 1;
            ext->period = 0x78;
            ext->proximity = 0;
            ext->variant = 2;
            break;
        case 8:
            ext->timer = 1;
            ext->period = 0xB4;
            ext->proximity = 0;
            ext->variant = 2;
            break;
        }
        arg0->state = 1;
        arg0->unk6 = 0;
        return;
    }
}

static void effect_33_spawn_dropper(struct EffectObj* arg0)
{
    struct ShotObj* shot = find_free_shot_obj();

    if (shot == NULL)
        return;
    shot->active = 0x41;
    shot->id = 0x21;
    shot->unk2 = arg0->ext.effect_33.variant;
    shot->x_pos.i.hi = arg0->x_pos.i.hi;
    shot->state = 6;
    shot->unk84.effect = arg0;
    shot->unk6 = arg0->unk6;
    arg0->unk6 = 1;
}

void func_800BC92C(struct EffectObj* arg0)
{
    struct Effect33Ext* ext = &arg0->ext.effect_33;
    struct ShotObj* shot;
    s32 x;
    s32 player_x;
    s32 bg_x;
    s32 distance;

    switch (arg0->unk2 & 0xF0) {
    case 0x00:
        if (arg0->x_pos.i.hi + 0x3B0 < g_Player.x_pos.i.hi) {
            arg0->state = 2;
            return;
        }
        if (--ext->timer != 0)
            return;
        ext->timer = ext->period;
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x21;
            shot->unk2 = 0;
            shot->state = 0;
        }
        return;

    case 0x10:
        if (ext->variant == 0) {
            if (arg0->x_pos.i.hi + 0x4C0 < g_Player.x_pos.i.hi) {
                arg0->state = 2;
                return;
            }
        } else if (arg0->x_pos.i.hi - g_Player.x_pos.i.hi < 0x181) {
            arg0->state = 3;
            return;
        }
        switch (arg0->unk5) {
        case 0:
            if (ext->variant == 0) {
                if (g_Player.x_pos.i.hi - arg0->x_pos.i.hi < 0x181)
                    return;
                shot = find_free_shot_obj();
                if (shot != NULL) {
                    shot->active = 0x41;
                    shot->id = 0x21;
                    shot->unk15 = 0;
                }
            } else {
                if ((u32)(arg0->x_pos.i.hi - g_Player.x_pos.i.hi - 0x181) >= 0x23F)
                    return;
                shot = find_free_shot_obj();
                if (shot != NULL) {
                    shot->active = 0x41;
                    shot->id = 0x21;
                    shot->unk15 = 0x40;
                }
            }
            if (shot != NULL) {
                shot->unk2 = 4 - ext->burst;
                shot->x_pos.i.hi = arg0->x_pos.i.hi;
                shot->state = 3;
                shot->y_pos.i.hi = arg0->y_pos.i.hi;
            }
            arg0->unk5 = 1;
            return;
        case 1:
            if (--ext->timer != 0)
                return;
            if (--ext->burst == 0) {
                arg0->unk5 = 2;
                return;
            }
            arg0->unk5 = 0;
            ext->timer = ext->period;
            return;
        case 2:
            if (--ext->cooldown != 0)
                return;
            ext->cooldown = 0x78;
            ext->burst = 4;
            arg0->unk5 = 0;
            ext->timer = ext->period;
            return;
        }
        return;

    case 0x20:
        x = arg0->x_pos.i.hi;
        bg_x = background_objects[g_Player.bg_offset].x_pos.i.hi;
        if (x + 0x240 - bg_x <= 0 || bg_x - (x - 0x3C0) <= 0) {
            arg0->state = 2;
            return;
        }
        if (ext->proximity == 0) {
            if (--ext->timer != 0)
                return;
            ext->timer = ext->period;
            effect_33_spawn_dropper(arg0);
            return;
        }
        player_x = g_Player.x_pos.i.hi;
        distance = player_x - x;
        if (distance < 0)
            distance = x - player_x;
        if (distance >= 0x20) {
            ext->timer = ext->period;
            return;
        }
        if (--ext->timer != 0)
            return;
        effect_33_spawn_dropper(arg0);
        return;
    }
}

extern union AnimationStep* D_80109320[];
extern union AnimationStep* D_801093B8[];
extern union AnimationStep* D_80109478[];
extern union AnimationStep* D_801094D0[];
extern struct Unk_unk68 D_80109268[];
extern struct Unk_unk68 D_8010926C[];
extern struct Unk_unk68 D_80109270[];
extern struct Unk_unk68 D_80109274[];
extern struct Unk_unk68 D_80109278[];
extern struct Unk_unk68 D_8010927C[];
extern u8 D_80109280[];
extern u8 D_80109288[];
extern u8 D_80109290[];
extern u8 D_80109298[];
extern u8 D_801092A0[];
extern u8 D_801092A8[];
extern u8 D_801092B0[];
void func_800C842C(s32, u8*, void*, s32, void*);

static void shot_33_load_graphics(struct ShotObj* arg0, s32 id)
{
    s32 resource;
    s32 clut_x;
    s32 clut_y;

    arg0->bg_offset = g_Player.bg_offset;
    resource = func_8002938C(id);
    arg0->unk40 = D_801406A8[resource] >> 7;
    resource = func_8002938C(id);
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    clut_x = func_8002938C(id);
    clut_y = func_8002938C(id);
    arg0->unk42 = ((clut_x * 4 + 0x18) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
}

static void shot_33_spawn_shadow(struct ShotObj* arg0, s8 shadow_kind, s8 unk6,
    s32 animation)
{
    struct MiscObj* misc = find_free_misc_obj();

    if (misc == NULL)
        return;
    misc->active = 0x41;
    misc->id = 0x1B;
    misc->unk16 = shadow_kind;
    misc->unk40 = arg0->unk40;
    misc->unk42 = arg0->unk42 & 0x7FFF;
    misc->animation_table = arg0->animation_table;
    misc->unk3C = arg0->unk3C;
    misc->bg_offset = arg0->bg_offset;
    misc->x_pos.val = arg0->x_pos.val;
    misc->y_pos.val = arg0->y_pos.val;
    misc->ext.misc_5.owner = (struct MainObj*)arg0;
    misc->state = 0;
    misc->unk6 = unk6;
    misc->unk7 = 0;
    misc->unk15 = arg0->unk15;
    func_80015D60(misc, animation);
    arg0->unk7C = (struct WeaponObj*)misc;
}

static s32 shot_33_touches_floor(struct ShotObj* arg0, s32 dx_extra, s32 dy_extra)
{
    const struct Unk_unk68* bounds = arg0->unk68;

    return func_8002D724((struct PlayerObj*)arg0,
               (s16)(arg0->x_pos.i.hi + bounds->unk0 + dx_extra),
               (s16)(arg0->y_pos.i.hi + bounds->unk1 + dy_extra))
        != 0;
}

static void shot_33_quake(void)
{
    if (!(background_objects[g_Player.bg_offset].unk34 & 0x10))
        func_80028B68(0x10, 6, 2);
}

static void shot_33_hit_sound(struct ShotObj* arg0)
{
    if (arg0->on_screen != 0)
        func_8001540C(2, 0xA0, arg0);
}

static s32 shot_33_below_screen(struct ShotObj* arg0)
{
    return background_objects[g_Player.bg_offset].y_pos.i.hi + 0x150 < arg0->y_pos.i.hi;
}

void func_800A03F4(struct ShotObj* arg0)
{
    s32 random;

    arg0->unk58.animation_steps = D_80105FF0;
    arg0->unk5C = 0xF;
    arg0->on_screen = 1;
    arg0->unk60 = 3;
    arg0->unk42 &= 0x7FFF;
    shot_33_load_graphics(arg0, 0x8E);
    arg0->animation_table = (u32**)D_80109320;
    random = get_random();
    random = ((random & 1) << 8) + (get_random() & 0xFF) + 0x40;
    arg0->x_pos.i.hi = background_objects[g_Player.bg_offset].x_pos.i.hi + random;
    arg0->x_vel.val = -0x10000;
    arg0->y_vel.val = -0x10000;
    arg0->unk28 = 0x400;
    arg0->unk2C = 0x400;
    arg0->unk68 = D_80109274;
    arg0->unk54 = (const u8*)D_80109268;
    arg0->unk50.data = (const u8*)D_80109268;
    arg0->unk16 = 1;
    arg0->unk15 = 0;
    arg0->unk62 = 2;
    arg0->y_pos.i.hi = background_objects[g_Player.bg_offset].y_pos.i.hi - 0x40;
    func_80015D60(arg0, 1);
    shot_33_spawn_shadow(arg0, 0, 0, 0);
    arg0->state = 1;
    arg0->unk5 = 0;
}

void func_800A068C(struct ShotObj* arg0)
{
    s32 hit;
    s32 collision;

    arg0->unk42 &= 0x7FFF;
    switch (arg0->unk5) {
    case 0:
        func_8002B694(ANIMATED_OBJECT(arg0));
        func_80015DC8(ANIMATED_OBJECT(arg0));
        hit = shot_33_touches_floor(arg0, -arg0->unk68->unk2, arg0->unk68->unk3);
        if (shot_33_touches_floor(arg0, -arg0->unk68->unk2, 0))
            hit = 1;
        if (shot_33_touches_floor(arg0, 0, arg0->unk68->unk3))
            hit = 1;
        if (hit) {
            shot_33_quake();
            arg0->x_vel.val = 0;
            arg0->unk28 = 0;
            arg0->y_vel.val = 0;
            arg0->unk2C = 0;
            func_80015D60(arg0, 2);
            arg0->unk5 = 1;
            return;
        }
        func_8002D9BC(arg0);
        if (func_8002BB80((struct MainObj*)arg0, (struct MainObj*)&g_Player) != 0) {
            func_80015D60(arg0, 2);
            arg0->unk5 = 1;
        }
        collision = func_8002DD04((struct MainObj*)arg0);
        if (collision < 0) {
            func_80015D60(arg0, 2);
            arg0->unk5 = 1;
        } else if (collision == 3 || collision == 0xC || collision == 0x22) {
            arg0->unk84.value = 8;
            func_80015D60(arg0, 8);
            arg0->unk7C->active = 0;
            arg0->unk7C->on_screen = 0;
            arg0->unk5 = 2;
        }
        break;
    case 1:
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.event == 0)
            break;
        func_800C813C(5, D_80109280, arg0);
        if (arg0->on_screen != 0)
            func_8001540C(2, 0xA0, arg0);
        arg0->state = 2;
        break;
    case 2:
        if (--arg0->unk84.value != 0)
            break;
        func_800C813C(5, D_80109288, arg0);
        arg0->state = 2;
        break;
    }
    if (shot_33_below_screen(arg0)) {
        arg0->state = 2;
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x60, 0x60);
}

void func_800A0A38(struct ShotObj* arg0)
{
    arg0->on_screen = 1;
    arg0->unk58.animation_steps = D_80105FF0;
    arg0->unk5C = 0x7F;
    arg0->unk60 = 6;
    arg0->unk42 &= 0x7FFF;
    shot_33_load_graphics(arg0, 0x8C);
    arg0->animation_table = (u32**)D_801093B8;
    arg0->unk16 = 0;
    arg0->x_vel.val = arg0->unk15 != 0 ? -0x38000 : 0x38000;
    arg0->unk68 = D_80109278;
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk54 = (const u8*)D_8010926C;
    arg0->unk50.data = (const u8*)D_8010926C;
    func_80015D60(arg0, 1);
    shot_33_spawn_shadow(arg0, 1, 1, 0);
    arg0->state = 4;
    arg0->unk5 = 0;
}

static void shot_33_burst(struct ShotObj* arg0, u8* effect)
{
    shot_33_quake();
    func_800C813C(5, effect, arg0);
    if (arg0->on_screen != 0) {
        func_8001540C(2, 0xA0, arg0);
        arg0->state = 5;
    } else {
        arg0->state = 5;
    }
}

void func_800A0C4C(struct ShotObj* arg0)
{
    s32 collision;

    arg0->unk42 &= 0x7FFF;
    if (arg0->unk5 != 0) {
        if (--arg0->unk84.value == 0) {
            func_800C813C(5, D_80109298, arg0);
            arg0->state = 5;
        }
    } else {
        if (!(background_objects[g_Player.bg_offset].unk34 & 0x10))
            func_80028B68(8, 4, 2);
        func_8002B694(ANIMATED_OBJECT(arg0));
        func_80015DC8(ANIMATED_OBJECT(arg0));
        CollisionRelated((struct PlayerObj*)arg0);
        if (!(arg0->unk70 & 8))
            arg0->unk2C = 0x8000;
        else
            arg0->unk2C = 0;
        if (arg0->unk15 != 0 ? (arg0->unk70 & 2) : (arg0->unk70 & 1)) {
            shot_33_burst(arg0, D_80109290);
            return;
        }
        func_8002D9BC(arg0);
        if (func_8002BB80((struct MainObj*)arg0, (struct MainObj*)&g_Player) != 0) {
            func_800C813C(5, D_80109290, arg0);
            shot_33_hit_sound(arg0);
            arg0->state = 5;
        }
        collision = func_8002DD04((struct MainObj*)arg0);
        if (collision < 0) {
            func_800C813C(5, D_80109290, arg0);
            shot_33_hit_sound(arg0);
            arg0->state = 5;
        } else if (collision == 3 || collision == 0xC || collision == 0x22) {
            arg0->unk84.value = 8;
            func_80015D60(arg0, 7);
            arg0->unk7C->active = 0;
            arg0->unk7C->on_screen = 0;
            arg0->unk5 = 1;
        }
    }
    if (shot_33_below_screen(arg0)) {
        arg0->state = 5;
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x60, 0x60);
}

void func_800A0FE8(struct ShotObj* arg0)
{
    if (engine_obj.character_state.bytes[0] != 0) {
        arg0->state = 8;
        return;
    }
    arg0->on_screen = 1;
    arg0->unk58.animation_steps = D_80105FF0;
    arg0->unk5C = 0xF;
    arg0->unk60 = 6;
    arg0->unk42 &= 0x7FFF;
    shot_33_load_graphics(arg0, 0x8D);
    arg0->animation_table = (u32**)D_80109478;
    arg0->unk16 = 0;
    arg0->unk15 = 0;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    if (arg0->unk2 == 0) {
        func_80015D60(arg0, 3);
        arg0->y_vel.val = -0x18000;
        arg0->unk2C = 0x2000;
        arg0->y_pos.i.hi = background_objects[g_Player.bg_offset].y_pos.i.hi - 0x40;
    } else {
        func_80015D60(arg0, 1);
        arg0->y_vel.val = 0xA0000;
        arg0->unk2C = 0x2000;
        if (engine_obj.substage != 0 && (u16)(arg0->x_pos.i.hi - 0x61) < 0x47F)
            arg0->y_pos.i.hi = 0x330;
        else
            arg0->y_pos.i.hi = background_objects[g_Player.bg_offset].y_pos.i.hi + 0x130;
    }
    arg0->unk68 = D_8010927C;
    arg0->unk54 = (const u8*)D_80109270;
    arg0->unk50.data = (const u8*)D_80109270;
    shot_33_spawn_shadow(arg0, 1, 1, arg0->unk2 == 0 ? 2 : 0);
    arg0->state = 7;
    arg0->unk5 = 0;
}

static void shot_33_release(struct ShotObj* arg0, u8* effect)
{
    arg0->unk84.effect->ext.effect_33.timer = 0xB4;
    func_800C813C(5, effect, arg0);
    arg0->state = 8;
}

void func_800A12EC(struct ShotObj* arg0)
{
    s32 collision;

    arg0->unk42 &= 0x7FFF;
    if (arg0->unk5 != 0) {
        if (--arg0->timer == 0)
            shot_33_release(arg0, D_801092A8);
    } else {
        func_8002B694(ANIMATED_OBJECT(arg0));
        CollisionRelated((struct PlayerObj*)arg0);
        if (arg0->unk70 & 4) {
            if (engine_obj.substage != 0 && (u16)(arg0->x_pos.i.hi - 0x61) < 0x47F) {
                if (arg0->unk6 != 0) {
                    arg0->y_pos.i.hi -= 0x28;
                    if (arg0->on_screen != 0)
                        func_8001540C(2, 0xA0, arg0);
                    func_800C842C(7, D_801092B0, arg0, 0x9A, D_801094D0);
                    arg0->y_pos.i.hi += 0x28;
                }
                func_800DABE4(arg0->unk6, (s16)(arg0->x_pos.i.hi - 0x18),
                    (s16)(arg0->y_pos.i.hi - 0x58));
            }
            shot_33_quake();
            shot_33_hit_sound(arg0);
            func_800C813C(5, D_801092A0, arg0);
            arg0->state = 8;
            return;
        }
        if (arg0->unk70 & 8) {
            shot_33_quake();
            shot_33_hit_sound(arg0);
            func_800C813C(5, D_801092A0, arg0);
            arg0->state = 8;
            return;
        }
        if (arg0->y_vel.val == 0) {
            if (arg0->unk2 == 2) {
                arg0->state = 8;
                return;
            }
            func_80015D60(arg0, 3);
            func_80015D60(arg0->unk7C, 2);
        }
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_8002D9BC(arg0);
        if (func_8002BB80((struct MainObj*)arg0, (struct MainObj*)&g_Player) != 0) {
            shot_33_hit_sound(arg0);
            func_800C813C(5, D_801092A0, arg0);
            arg0->state = 8;
        }
        collision = func_8002DD04((struct MainObj*)arg0);
        if (collision < 0 || engine_obj.character_state.bytes[0] != 0) {
            shot_33_hit_sound(arg0);
            shot_33_release(arg0, D_801092A0);
        } else if (collision == 3 || collision == 0xC || collision == 0x22) {
            arg0->timer = 8;
            func_80015D60(arg0, 9);
            arg0->unk7C->active = 0;
            arg0->unk7C->on_screen = 0;
            arg0->unk5 = 1;
        }
    }
    if (shot_33_below_screen(arg0)) {
        arg0->state = 8;
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x60, 0x60);
}

void func_800C842C(s32 count, u8* variants, void* owner, s32 id, void* animation_table)
{
    struct MiscObj* obj;
    s32 clut_x;
    s32 clut_y;
    s32 resource;

    for (; count & 0xFF; count--) {
        obj = find_free_misc_obj();
        if (obj == NULL)
            continue;
        obj->active = 0x41;
        obj->id = 3;
        obj->unk2 = 1;
        obj->unk15 = get_random() & 0x40;
        obj->state = 0;
        obj->unk5 = 0;
        obj->unk6 = 0;
        obj->x_pos.val = ((struct MainObj*)owner)->x_pos.val + ((get_random() & 3) << 16);
        obj->y_pos.val = ((struct MainObj*)owner)->y_pos.val + ((get_random() & 3) << 16);
        obj->ext.misc_2.owner = owner;
        obj->animation_table = animation_table;
        obj->ext.misc_2.unk58 = *variants++;
        clut_x = func_8002938C(id);
        clut_y = func_8002938C(id);
        obj->unk42 = ((clut_x * 4 + 0x18) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
        resource = func_8002938C(id);
        obj->unk40 = D_801406A8[resource] >> 7;
        resource = func_8002938C(id);
        obj->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    }
}

extern struct Unk_unk68 D_80107374[];
extern union AnimationStep* D_800FE280[9];
extern struct Unk_unk68 D_800FE1B0;
extern struct Unk_unk68 D_800FE1B4;
extern struct Unk_unk68 D_800FE1B8;
extern void (*D_800FE2B8[7])();
void func_8005F47C(struct MainObj*);

void func_8005ECA8(struct MainObj* arg0)
{
    arg0->unk60 = 3;
    arg0->unk5C = 4;
    arg0->unk61 = 0;
    arg0->collision_data = D_80107374;
    arg0->animation_table = (const u8* const*)D_800FE280;
    arg0->unk16 = 6;
    arg0->unk68 = &D_800FE1B8;
    arg0->unk54 = &D_800FE1B0;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk50 = &D_800FE1B4;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->bg_offset = g_Player.bg_offset;
    switch (arg0->unk2) {
    case 0:
        arg0->unk20 = -0x28000;
        arg0->unk15 = 0;
        arg0->ext.main_35.unk80 = 0;
        arg0->unk5 = 2;
        break;
    case 1:
        arg0->unk7A = 1;
        arg0->unk15 = 0x40;
        arg0->ext.main_35.unk80 = 0;
        arg0->unk20 = 0x28000;
        arg0->unk5 = 4;
        break;
    case 2:
        arg0->unk20 = -0x28000;
        arg0->unk15 = 0;
        arg0->ext.main_35.unk80 = 1;
        arg0->unk5 = 2;
        break;
    case 3:
        arg0->unk7A = 1;
        arg0->unk15 = 0x40;
        arg0->ext.main_35.unk80 = 1;
        arg0->unk20 = 0x28000;
        arg0->unk5 = 4;
        break;
    }
    func_80015D60(arg0, 0);
    arg0->state = 1;
    arg0->unk6 = 0;
}

void func_8005EE2C(struct MainObj* arg0)
{
    func_8005F47C(arg0);
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FE2B8[arg0->unk5](arg0);
    if (arg0->unk5 == 4)
        return;
    if (engine_obj.stage != 3 || g_Player.x_pos.i.hi < 0x9B7)
        func_8002D9BC(arg0);
    arg0->ext.main_35.saved_unk5 = arg0->unk5;
    if (func_8002DD04(arg0) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(5, D_800FE2A4, arg0);
        func_800BF60C(BASE_OBJECT(arg0), 0xC);
        arg0->state = 2;
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x40, 0x40) != 0) {
        arg0->state = 2;
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
}

void func_8005EFB0(struct MainObj* arg0)
{
    u32 mode;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        func_8001540C(2, 0x57, arg0);
        mode = arg0->ext.main_35.unk80;
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        if (mode == 0) {
            arg0->unk5 = 2;
        } else if (mode == 1) {
            arg0->ext.main_35.unk80 = 2;
            func_80015D60(arg0, 1);
            arg0->unk60 = 4;
            arg0->ext.main_35.sound_timer = 1;
            arg0->unk5 = 5;
        } else {
            arg0->unk20 = arg0->unk15 != 0 ? 0x40000 : -0x40000;
            arg0->ext.main_35.sound_timer = 1;
            arg0->unk5 = 5;
            arg0->unk6 = 3;
        }
        return;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->ext.main_35.unk80 == 2)
        return;
    if (arg0->unk15 == 0) {
        if (arg0->unk70 & 2) {
            arg0->unk15 = 0x40;
            arg0->unk20 = 0x28000;
        }
    } else if (arg0->unk70 & 1) {
        arg0->unk15 = 0;
        arg0->unk20 = -0x28000;
    }
}

extern u8 D_8010220C[8];
extern struct Unk_unk68 D_801021FC[2];
extern struct Unk_unk68 D_80102204[2];
extern union AnimationStep* D_801021D8[9];
extern struct Unk_unk68 D_80107C78[];
extern s16 D_8010222C[20];

static struct VisualObj* main_62_spawn_arm(struct MainObj* arg0, s8 side)
{
    struct VisualObj* visual = find_free_visual_obj();

    if (visual == NULL)
        return NULL;
    visual->active = 0x41;
    visual->id = 0x19;
    visual->unk2 = side;
    visual->x_pos.val = arg0->x_pos.val + (arg0->unk15 != 0 ? -0x690000 : 0x690000);
    visual->unk50 = (struct PlayerObj*)arg0;
    visual->y_pos.val = arg0->y_pos.val - 0x80000;
    return visual;
}

void func_8007B90C(struct MainObj* arg0)
{
    struct VisualObj* visual = NULL;

    arg0->active |= 4;
    arg0->unk15 = (arg0->unk2 & 1) ? 0x40 : 0;
    arg0->unk7C = D_8010220C[arg0->unk2];
    if (arg0->unk2 < 4) {
        main_62_spawn_arm(arg0, 1);
        visual = main_62_spawn_arm(arg0, 0);
        func_800C833C(6, (u8*)D_801021FC, (struct MiscObj*)arg0,
            arg0->unk15 != 0 ? -0x690000 : 0x690000, 0);
    }
    arg0->ext.main_62.unk80 = visual;
    arg0->ext.main_62.unk86 = 0;
    arg0->animation_table = (const u8* const*)D_801021D8;
    arg0->unk16 = 2;
    arg0->collision_data = D_80107C78;
    arg0->unk5C = 0x7F;
    arg0->unk68 = NULL;
    arg0->unk61 = 0;
    arg0->unk62 = 0;
    arg0->unk60 = 4;
    arg0->unk67 = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk5++;
}

u8 func_8007BABC(struct MainObj* arg0)
{
    struct WeaponObj* weapon;

    arg0->unk54 = &D_8010212C;
    for (weapon = weapon_objects; weapon < weapon_objects + COUNT(weapon_objects); weapon++) {
        if (!weapon->active)
            continue;
        if (!func_8002BD58((struct MainObj*)weapon, arg0,
                &((s16*)&weapon->unk80)[0], &((s16*)&weapon->unk80)[1]))
            continue;
        if (weapon->id == 2 || weapon->id == 0xB || weapon->id == 0x21)
            return 1;
    }
    return 0;
}

void func_8007BE40(struct MainObj* arg0)
{
    s32 index;
    s32 x_offset;

    if (--arg0->unk7E != 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x90, 0x90);
        arg0->ext.main_62.unk86 = arg0->on_screen;
        return;
    }
    arg0->unk5++;
    index = arg0->animation_step.fields.frame_index - 3;
    x_offset = D_8010222C[index * 2];
    if (arg0->unk15 != 0)
        x_offset = -x_offset;
    func_800C833C(8, (u8*)D_80102204, (struct MiscObj*)arg0, x_offset << 16,
        D_8010222C[index * 2 + 1] << 16);
    arg0->state = 1;
    arg0->unk5 = 3;
    arg0->unk7E = 0xC8;
    arg0->unk5C = 0x7F;
    arg0->unk42 -= 2;
    func_80015D60(arg0, 2);
}

void func_800B3D3C(struct VisualObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk50;

    arg0->unk40 = owner->unk40;
    arg0->unk42 = owner->unk42 & 0x7FFF;
    arg0->animation_table = (u32**)owner->animation_table;
    arg0->unk3C = (void*)owner->sprite_frames;
    arg0->unk15 = owner->unk15;
    arg0->bg_offset = owner->bg_offset;
    arg0->unk16 = arg0->unk2 != 0 ? 1 : 6;
    func_80015D60(arg0, arg0->unk2);
    arg0->state++;
}

extern struct Unk_unk68 D_800FBA4C;
extern struct Unk_unk68 D_800FBA54;
extern union AnimationStep* D_800FBB4C[14];
extern u8 D_800FBB84[4];
extern void (*D_800FBB88[6])();

void func_8004D9CC(struct MainObj* arg0)
{
    struct Main0Ext* ext = &arg0->ext.main_0;
    s32 dy;

    if (arg0->unk67 != 0 || (ext->background_relative & 3))
        return;
    if (ext->flags[1] != 0) {
        ext->flags[1]--;
        return;
    }
    dy = arg0->y_pos.i.hi - g_Player.y_pos.i.hi;
    if (dy < 0)
        dy = -dy;
    if (dy >= 0x28) {
        ext->index = 0;
        return;
    }
    if (arg0->unk15 != 0) {
        if (g_Player.x_pos.i.hi < arg0->x_pos.i.hi + 0x50)
            ext->index++;
        else
            ext->index = 0;
    } else {
        if (arg0->x_pos.i.hi - 0x50 < g_Player.x_pos.i.hi)
            ext->index++;
        else
            ext->index = 0;
    }
    if (ext->index >= 0x3D) {
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        func_80015D60(arg0, 7);
        ext->index = 0;
        ext->background_relative |= 2;
    }
}

void func_8004DB10(struct MainObj* arg0)
{
    const struct Unk_unk68* bounds;
    s32 x;

    if (arg0->unk67 != 0)
        return;
    CollisionRelated(PLAYER_OBJECT(arg0));
    if (!(arg0->unk70 & 8)) {
        func_80015D60(arg0, 3);
        arg0->unk5 = 2;
        arg0->unk2C = 0x4200;
        arg0->unk6 = 0;
        arg0->unk24 = 0;
        arg0->unk28 = 0;
        arg0->unk67 = -1;
        return;
    }
    bounds = arg0->unk68;
    if (arg0->unk15 != 0)
        x = arg0->x_pos.i.hi + bounds->unk0 + bounds->unk2;
    else
        x = arg0->x_pos.i.hi - bounds->unk0 - bounds->unk2;
    if (func_8002D724(PLAYER_OBJECT(arg0), (s16)x,
            (s16)(arg0->y_pos.i.hi + bounds->unk1 + bounds->unk3 + 8)))
        return;
    if (arg0->unk2 == 1) {
        arg0->unk15 = (arg0->unk15 == 0) << 6;
        arg0->unk20 = -arg0->unk20;
        return;
    }
    if (arg0->unk70 & 3)
        return;
    func_80015D60(arg0, 2);
    arg0->unk24 = 0x38000;
    arg0->unk5 = 5;
    arg0->unk6 = 0;
    arg0->unk2C = 0x4200;
    arg0->unk20 = arg0->unk15 != 0 ? 0x10000 : -0x10000;
    arg0->unk67 = 1;
}

void func_8004DCB0(struct MainObj* arg0)
{
    struct Main0Ext* ext = &arg0->ext.main_0;
    struct WeaponObj* weapon;
    s32 dy;

    if (arg0->unk67 != 0 || (ext->background_relative & 1))
        return;
    if (ext->flags[0] != 0) {
        ext->flags[0]--;
        return;
    }
    for (weapon = weapon_objects; weapon < weapon_objects + COUNT(weapon_objects); weapon++) {
        if (!weapon->active || weapon->id != 0)
            continue;
        if (arg0->unk15 != 0) {
            if (g_Player.unk15 == 0 && arg0->x_pos.val < g_Player.x_pos.val) {
                dy = weapon->y_pos.i.hi - arg0->y_pos.i.hi;
                if (dy < 0)
                    dy = -dy;
                if (dy < 0x18 && weapon->x_pos.i.hi < arg0->x_pos.i.hi + 0x80)
                    ext->background_relative |= 1;
            }
        } else {
            if (g_Player.unk15 != 0 && g_Player.x_pos.val < arg0->x_pos.val) {
                dy = weapon->y_pos.i.hi - arg0->y_pos.i.hi;
                if (dy < 0)
                    dy = -dy;
                if (dy < 0x18 && arg0->x_pos.i.hi - 0x80 < weapon->x_pos.i.hi)
                    ext->background_relative |= 1;
            }
        }
        if (ext->background_relative & 1) {
            arg0->unk5 = 3;
            arg0->unk6 = 0;
            func_80015D60(arg0, 5);
            return;
        }
    }
}

void func_8004DFEC(struct MainObj* arg0)
{
    struct Main0Ext* ext = &arg0->ext.main_0;

    switch (arg0->unk6) {
    case 0:
        arg0->unk6 = 1;
        func_80015D60(arg0, 5);
        arg0->unk7C = 0x3C;
        /* fallthrough */
    case 1:
        if (arg0->animation_step.fields.event != 0) {
            arg0->collision_data = D_801060F0;
            arg0->unk54 = &D_800FBA54;
            arg0->unk50 = &D_800FBA54;
        }
        if (--arg0->unk7C == 0) {
            arg0->unk6++;
            func_80015D60(arg0, 6);
        }
        break;
    case 2:
        if (arg0->animation_step.fields.relative_step == 0) {
            func_80015D60(arg0, 1);
            arg0->unk5 = 1;
            arg0->collision_data = D_801069F4;
            arg0->unk54 = &D_800FBA50;
            arg0->unk50 = &D_800FBA50;
            arg0->unk6 = 0;
            ext->flags[0] = 0x78;
            ext->background_relative &= 0xFE;
        }
        break;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

static void main_15_spawn_spark(struct MainObj* arg0, u8 index)
{
    struct ShotObj* shot = find_free_shot_obj();

    if (shot == NULL)
        return;
    shot->active = 0x41;
    shot->id = 0xA;
    shot->unk42 = 0x7885;
    shot->bg_offset = arg0->bg_offset;
    shot->x_pos.val = arg0->x_pos.val;
    shot->unk2 = index * 2;
    shot->y_pos.val = arg0->y_pos.val;
    func_8002B93C(MOVING_OBJECT(shot), (s8)(index * 2));
    arg0->unk7C = 0xA;
}

void func_8004E300(struct MainObj* arg0)
{
    u8 i;

    switch (arg0->unk6) {
    case 0:
        arg0->unk6++;
        arg0->unk2C = 0x4200;
        arg0->unk67 = -1;
        arg0->unk24 = 0;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->collision_data = D_801069F4;
        func_80015D60(arg0, 0xD);
        /* fallthrough */
    case 1:
        if (arg0->unk70 & 8) {
            arg0->unk2C = 0;
            arg0->unk67 = 0;
        }
        func_8002B694(ANIMATED_OBJECT(arg0));
        break;
    }
    if (func_8002DD04(arg0) != 0 || func_8002D9BC(arg0) != 0) {
        arg0->state = 2;
        func_800AF808(BASE_OBJECT(arg0));
        for (i = 0; i < 0x10; i += 2)
            main_15_spawn_spark(arg0, i);
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x40, 0x40) != 0) {
        arg0->state = 2;
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x25, 0x25);
}

void func_8004E490(struct MainObj* arg0)
{
    u8 i;

    if (--arg0->unk7C != 0)
        return;
    arg0->state = 2;
    for (i = 1; i < 0x10; i += 2)
        main_15_spawn_spark(arg0, i);
}

void func_8004E55C(struct MainObj* arg0)
{
    struct Main0Ext* ext = &arg0->ext.main_0;

    arg0->unk5 = 1;
    arg0->state++;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->animation_table = (const u8* const*)D_800FBB4C;
    arg0->unk16 = 6;
    arg0->unk68 = &D_800FBA4C;
    arg0->unk54 = &D_800FBA50;
    arg0->unk50 = &D_800FBA50;
    arg0->unk5C = 3;
    arg0->collision_data = D_801069F4;
    arg0->unk61 = 0;
    arg0->unk67 = 0;
    arg0->unk60 = 1;
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk24 = 0;
    arg0->unk2C = 0;
    ext->background_relative = 0;
    ext->flags[0] = 0;
    ext->index = 0;
    ext->flags[1] = 0;
    arg0->unk15 = g_Player.x_pos.val < arg0->x_pos.val ? 0 : 0x40;
    if ((u8)(arg0->unk2 - 2) < 2) {
        arg0->state = 5;
        arg0->unk54 = NULL;
        arg0->unk50 = NULL;
        arg0->x_pos.i.hi = (arg0->x_pos.i.hi & ~0xF) + 8;
        arg0->y_pos.i.hi = (arg0->y_pos.i.hi & ~0xF) + 0x14;
        func_80015D60(arg0, 0);
    } else {
        func_80015D60(arg0, 1);
    }
}

void func_8004E6A4(struct MainObj* arg0)
{
    u16 x;

    if (ENGINE_STAGE_ID == 0x102 && engine_obj.character_state.bytes[0] != 0) {
        x = arg0->x_pos.i.hi;
        if ((u16)(x - 0xC0F) < 0x1E2 || (u16)(x - 0x100F) < 0x1E2
            || (u16)(x - 0x1315) < 0x1DC || (u16)(x - 0x1613) < 0x1BF) {
            arg0->state = 3;
            arg0->unk6 = 0;
            return;
        }
    }
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (func_8002DD04(arg0) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(4, D_800FBB84, arg0);
        func_800BF60C(BASE_OBJECT(arg0), 0x12);
        arg0->state++;
        return;
    }
    func_8004DB10(arg0);
    func_8004D9CC(arg0);
    func_8004DCB0(arg0);
    D_800FBB88[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x40, 0x40) != 0) {
        arg0->state++;
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x25, 0x25);
}

extern struct Unk_unk68 D_80107778[];
extern struct Unk_unk68 D_800FFC54;
extern struct Unk_unk68 D_800FFC58;
extern struct Unk_unk68 D_800FFC5C;
extern u8 D_800FFD7C[8];
extern void (*D_800FFD94[7])(struct MainObj*);
void func_8006A26C(struct MainObj*);

void func_80069AD0(struct MainObj* arg0)
{
    struct Main51Ext* ext = &arg0->ext.main_51;

    arg0->active = 0x41;
    arg0->unk5C = 0x1E;
    arg0->unk60 = 4;
    arg0->unk61 = 0;
    arg0->collision_data = D_80107778;
    arg0->animation_table = (const u8* const*)D_800FFD44;
    arg0->unk16 = 5;
    arg0->unk68 = &D_800FFC5C;
    arg0->unk54 = &D_800FFC54;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk50 = &D_800FFC58;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk15 = g_Player.x_pos.val < arg0->x_pos.val ? 0 : 0x40;
    func_80015D60(arg0, 0);
    arg0->unk5 = 2;
    ext->unk80 = 0;
    ext->unk84 = 0;
    memset(ext->pad88, 0, sizeof(ext->pad88));
    ext->unk90 = 0;
    ext->saved_unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7C = 0x28;
    arg0->state++;
}

void func_80069BE4(struct MainObj* arg0)
{
    s32 collision;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FFD94[arg0->unk5](arg0);
    collision = func_8002DD04(arg0);
    func_8002D9BC(arg0);
    CollisionRelated(PLAYER_OBJECT(arg0));
    func_8006A26C(arg0);
    if (arg0->unk5 != 0)
        arg0->ext.main_51.saved_unk5 = arg0->unk5;
    if (collision < 0) {
        func_800C813C(5, D_800FFD7C, arg0);
        arg0->unk7C = 0x1E;
        arg0->on_screen = 0;
        arg0->unk7E = 5;
        arg0->state++;
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x60, 0x40) != 0) {
        arg0->state = 3;
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x30, 0x30);
}

void func_80069F28(struct MainObj* arg0)
{
    struct Main51Ext* ext = &arg0->ext.main_51;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    arg0->unk6 = 0;
    ext->unk84++;
    if (arg0->unk2 == 0) {
        if ((s32)ext->unk84 < engine_obj.cur_character + 3)
            return;
    } else if ((s32)ext->unk84 < 4) {
        return;
    }
    arg0->unk5 = 4;
    arg0->unk7C = 0x14;
    ext->unk84 = 0;
}

extern struct Unk_unk68 D_80106170[32];
extern u8 D_8010920C[4][4];
extern s32 D_8010921C[4];
void func_8009FE60(struct ShotObj*);

void func_8009FB9C(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;
    s32 dx;
    s32 dy;

    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->unk60 = 6;
    arg0->unk58.collision_bounds = D_80106170;
    arg0->unk50.data = (const u8*)D_8010920C;
    arg0->unk54 = (const u8*)D_8010920C;
    arg0->unk68 = NULL;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk42 &= 0x7FFF;
    arg0->state++;
    if (arg0->unk2 == 0) {
        dx = 0x20;
        dy = -8;
    } else if (arg0->unk2 == 1) {
        dx = 0x1D;
        dy = 0xE;
    } else {
        dx = 0xC;
        dy = 0x12;
    }
    arg0->x_pos.i.hi = owner->x_pos.i.hi + (arg0->unk15 != 0 ? dx : -dx);
    arg0->y_pos.i.hi = owner->y_pos.i.hi + dy;
    func_80015D60(arg0, 3);
    func_8009FE60(arg0);
    arg0->unk84.value = 0x10;
    arg0->unk8C.word = 0;
}

void func_8009FD00(struct ShotObj* arg0)
{
    s32 speed;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    speed = arg0->x_vel.val;
    if (speed < 0)
        speed = -speed;
    if (speed > 0x30000)
        arg0->unk28 = 0;
    if (func_8002DD04((struct MainObj*)arg0) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
    } else {
        func_8002D9BC(arg0);
        if (--arg0->unk84.value == 0 && arg0->unk17 != 4) {
            arg0->unk28 = 0x600;
            arg0->x_vel.val = D_8010921C[(arg0->unk15 & 0x40) ? 1 : 0];
            if (arg0->unk15 & 0x40)
                arg0->x_pos.i.hi += 0x10;
            else
                arg0->x_pos.i.hi -= 0x10;
            func_80015D60(arg0, 4);
        }
        if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) {
            func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
            return;
        }
    }
    arg0->unk8C.word = 1;
    arg0->state++;
}

void func_8009FE60(struct ShotObj* arg0)
{
    struct VisualObj* visual = find_free_visual_obj();

    if (visual == NULL)
        return;
    visual->active = 0x41;
    visual->id = 0x10;
    visual->unk2 = 1;
    visual->unk50 = (struct PlayerObj*)arg0;
    visual->unk42 = arg0->unk42;
    visual->animation_table = arg0->animation_table;
    visual->unk3C = arg0->unk3C;
    visual->unk40 = arg0->unk40;
    visual->unk16 = 3;
    visual->bg_offset = arg0->bg_offset;
    visual->unk15 = arg0->unk15;
    visual->x_pos.val = arg0->x_pos.val;
    visual->y_pos.val = arg0->y_pos.val;
}

void func_800B1F78(struct VisualObj* arg0)
{
    struct MainObj* owner;
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk2 == 0) {
        owner = (struct MainObj*)arg0->unk50;
        if (owner->ext.main_38.unk88 == 1 && owner->id == 0x26)
            func_80015D60(arg0, 0x13);
        if (owner->ext.main_38.unk88 == 2 || owner->unk5 != 3)
            arg0->state = 2;
        func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
        return;
    }
    shot = (struct ShotObj*)arg0->unk50;
    if (shot->active == 0 || shot->unk8C.word != 0)
        arg0->state = 2;
    arg0->x_pos.i.hi = shot->x_pos.i.hi;
    arg0->y_pos.i.hi = shot->y_pos.i.hi;
    func_8002B318(BASE_OBJECT(arg0), 0x30, 0x30);
}

extern struct Unk_unk68 D_801044F8;
extern void* D_80104770[25];
extern void (*D_801047E8[9])();
extern u8 D_801044A0[8];
extern u8 D_801044A8[8];
extern void* D_801044EC[2];
extern u8 D_801044F4[4];
void func_80088AD0(struct MainObj*);
void func_80088974(struct MainObj*);

void func_80086008(struct MainObj* arg0)
{
    struct Main69Ext* ext = &arg0->ext.main_69;

    if (ext->state.bytes.unk8C == 0) {
        if (ext->effect->active != 0)
            return;
        arg0->unk6 = 0;
    } else {
        arg0->unk6 = 1;
    }
    arg0->unk16 = 5;
    arg0->unk60 = 6;
    arg0->unk67 = 0;
    arg0->unk15 = 0;
    arg0->unk5C = 0;
    arg0->unk61 = 0;
    arg0->unk68 = &D_801044F8;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk54 = NULL;
    arg0->unk50 = NULL;
    arg0->collision_data = NULL;
    arg0->animation_table = (const u8* const*)D_80104770;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk40 = (D_801406A8[0] >> 7) + 0xB0;
    func_80015D60(arg0, 0);
    func_80088AD0(arg0);
    engine_obj.unk25 = 1;
    engine_obj.boss_ptr = arg0;
    arg0->state = 1;
    ext->state.bytes.unk8D = 0;
    ext->state.bytes.unk8E = 0;
    arg0->unk5 = 2;
}

void func_80086124(struct MainObj* arg0)
{
    struct Main69Ext* ext = &arg0->ext.main_69;
    s32 collision;

    D_801047E8[arg0->unk5](arg0);
    collision = func_8002DD04(arg0);
    if (ext->state.bytes.unk8D != 0) {
        if (ext->state.bytes.unk8D & 1)
            arg0->unk42 &= 0x7FFF;
        else
            arg0->unk42 |= 0x8000;
        if (--ext->state.bytes.unk8D == 0) {
            arg0->collision_data = D_80108084;
            ext->state.bytes.unk8E = 0;
        }
    } else if (collision < 0) {
        arg0->state = 2;
        arg0->unk5 = ext->state.bytes.unk8C != 0 ? 1 : 0;
        arg0->unk6 = 0;
        arg0->unk42 &= 0x7FFF;
        g_Player.unk7A = 1;
        is_on_screen(BASE_OBJECT(arg0));
        return;
    } else if (collision != 0 && collision != 0x7F) {
        arg0->collision_data = D_801060F0;
        ext->state.bytes.unk8D = 0x40;
        ext->state.bytes.unk8E = 1;
    }
    func_8002D9BC(arg0);
}

void func_8008654C(struct MainObj* arg0)
{
    struct EffectObj* effect;
    s16 timer;
    s8 level;

    if (--arg0->unk7C == 0) {
        arg0->unk6++;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x1A;
            effect->x_pos.i.hi = arg0->x_pos.i.hi;
            effect->y_pos.i.hi = arg0->y_pos.i.hi;
            arg0->ext.main_69.effect = effect;
        }
    }
    is_on_screen(BASE_OBJECT(arg0));
    timer = arg0->unk7E;
    arg0->unk7E = timer - 1;
    if (timer != 0)
        return;
    arg0->unk42 ^= 0x8000;
    arg0->unk61 -= 5;
    if (arg0->unk61 >= 0x1A)
        arg0->unk61 = 0;
    level = arg0->unk61;
    if (level < 5)
        level = 5;
    arg0->unk7E = level;
}

void func_80086860(struct MainObj* arg0)
{
    if (arg0->unk7C != 0) {
        arg0->unk7C--;
        return;
    }
    if (g_Player.unkC0 != -1)
        return;
    arg0->unk7C = 0x20;
    arg0->unk20 = 0x200000;
    arg0->unk28 = -0x10000;
    arg0->x_pos.i.hi = background_objects[0].unk1E + 0x100;
    func_80088974(arg0);
    func_8001540C(2, 0xD3, arg0);
    arg0->unk6++;
}

void func_80086C00(struct MainObj* arg0)
{
    struct VisualObj* visual = find_free_visual_obj();

    if (visual == NULL)
        return;
    visual->active = 0x41;
    visual->id = 0x1E;
    visual->unk2 = 0;
    visual->unk50 = PLAYER_OBJECT(arg0);
    arg0->ext.main_69.linked_object = (struct MainObj*)visual;
    arg0->unk7C = 0x10;
    arg0->unk7++;
    func_8001540C(2, 0xD7, arg0);
}

void func_800877A4(struct MainObj* arg0)
{
    s16 player_x;

    if (--arg0->unk7C != 0)
        return;
    player_x = g_Player.x_pos.i.hi;
    if (player_x < background_objects[0].x_pos.i.hi + 0xB0)
        arg0->x_pos.i.hi = player_x + 0x30;
    else
        arg0->x_pos.i.hi = player_x - 0x30;
    func_80088974(arg0);
    func_80015D60(arg0, 5);
    func_8001540C(2, 0xD4, arg0);
    arg0->unk54 = &D_80104508;
    arg0->unk50 = &D_80104504;
    arg0->unk7C = 0x1E;
    arg0->unk6++;
}

void func_80087A00(struct MainObj* arg0)
{
    s32 speed;

    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk15 != 0) {
        if (arg0->unk20 <= 0x41FFF)
            arg0->unk20 = 0x42000;
    } else if (arg0->unk20 > -0x42000) {
        arg0->unk20 = -0x42000;
    }
    if (arg0->unk15 != 0) {
        if (arg0->x_pos.i.hi < (s16)background_objects[0].unk1E + 0x110)
            return;
        speed = 0x42000;
    } else {
        if ((s16)background_objects[0].unk1E + 0x50 < arg0->x_pos.i.hi)
            return;
        speed = -0x42000;
    }
    arg0->unk20 = speed;
    arg0->unk28 = -0x3000;
    arg0->unk4B = -1;
    func_80015D60(arg0, 2);
    arg0->unk6++;
}

static struct VisualObj* main_69_spawn_part(struct MainObj* arg0, s8 part)
{
    struct VisualObj* visual = find_free_visual_obj();

    if (visual == NULL)
        return NULL;
    visual->active = 0x41;
    visual->id = 0x1E;
    visual->unk2 = part;
    visual->unk50 = PLAYER_OBJECT(arg0);
    return visual;
}

void func_800881F8(struct MainObj* arg0)
{
    struct VisualObj* visual;
    struct EffectObj* effect;

    if (arg0->animation_step.fields.event != 1) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    func_8001540C(2, 0xD5, arg0);
    visual = main_69_spawn_part(arg0, 0);
    if (visual != NULL) {
        arg0->unk7C = 0x30;
        arg0->ext.main_69.linked_object = (struct MainObj*)visual;
    }
    main_69_spawn_part(arg0, 0x20);
    visual = main_69_spawn_part(arg0, 0x10);
    if (visual != NULL)
        visual->unk54 = 0x50;
    effect = find_free_effect_obj();
    if (effect != NULL) {
        effect->active = 0x41;
        effect->id = 0x25;
        effect->unk2 = 0x10;
        effect->ext.effect_37.unk1E = 8;
        effect->ext.effect_37.unk1F = 2;
        effect->ext.effect_37.unk20 = 3;
        effect->ext.effect_37.unk21 = 6;
    }
    arg0->unk6++;
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800883CC(struct MainObj* arg0)
{
    struct ShotObj* shot;
    u8 i;

    if (arg0->animation_step.fields.relative_step != 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    for (i = 0; i < 2; i++) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x2D;
            shot->unk2 = i + 0x10;
            shot->unk7C = WEAPON_OBJECT(arg0);
            shot->unk8C.object = OBJECT_HEADER(arg0);
        }
        func_8001540C(2, 0xD7, arg0);
    }
    main_69_spawn_part(arg0, 0x30);
    func_80028BAC(0x10, 2, 1);
    arg0->unk7C = 0x50;
    arg0->unk6++;
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800889DC(struct MainObj* arg0)
{
    struct Main69Ext* ext = &arg0->ext.main_69;
    u8 roll = get_random() & 0xF;
    u8 level;
    u8** scripts;
    u8 i;

    if (ext->state.bytes.unk8C == 1) {
        ext->script = roll < 10 ? D_801044A0 : D_801044A8;
        return;
    }
    level = (arg0->unk5C - 1) / 6;
    scripts = D_801044EC[level];
    for (i = 0; i < 2; i++) {
        if (roll < D_801044F4[level * 2 + i]) {
            ext->script = scripts[i];
            return;
        }
    }
}

extern s16 D_80109A38[2][2];
extern s8 D_80109A40[14][4];

void func_800A7CE8(struct ShotObj* arg0)
{
    s32 speed;

    func_80015D60(arg0, 0xE);
    arg0->unk5C = 5;
    if (engine_obj.stage == 0xA) {
        arg0->unk60 = 7;
        speed = arg0->unk15 != 0 ? 0x60000 : -0x60000;
    } else {
        arg0->unk60 = 6;
        speed = arg0->unk15 != 0 ? 0x50000 : -0x50000;
    }
    arg0->x_vel.val = speed;
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    if (arg0->unk15 != 0)
        arg0->x_pos.i.hi += D_80109A38[arg0->unk2][0];
    else
        arg0->x_pos.i.hi -= D_80109A38[arg0->unk2][0];
    arg0->unk58.collision_bounds = D_801060F0;
    arg0->unk54 = (const u8*)D_80109A40[1];
    arg0->unk50.data = (const u8*)D_80109A40[0];
    arg0->unk6++;
    arg0->y_pos.i.hi += D_80109A38[arg0->unk2][1];
}

void func_800A83C4(struct ShotObj* arg0)
{
    u8 kind;

    arg0->unk60 = 9;
    arg0->unk50.data = (const u8*)D_80109A40[0];
    arg0->unk5C = 0;
    arg0->unk58.data = NULL;
    arg0->unk54 = NULL;
    kind = arg0->unk2 & 0xF;
    arg0->x_vel.val = arg0->unk15 != 0 ? 0x18000 : -0x18000;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->x_pos.i.hi += arg0->unk15 != 0 ? 0x10 : -0x10;
    if (kind < 5) {
        func_80015D60(arg0, 0xB);
    } else if (kind < 8) {
        func_80015D60(arg0, 0xC);
        arg0->x_pos.i.hi += arg0->unk15 != 0 ? 4 : -4;
    } else {
        func_80015D60(arg0, 0xD);
        arg0->x_pos.i.hi += arg0->unk15 != 0 ? 8 : -8;
    }
    arg0->unk6++;
}

void func_800A858C(struct ShotObj* arg0)
{
    static const u8 bounds[6] = { 2, 3, 4, 6, 7, 8 };
    u32 index = arg0->animation_step.fields.frame_index - 0x37;

    if (index < 6)
        arg0->unk50.data = (const u8*)D_80109A40[bounds[index]];
    else
        arg0->unk50.data = NULL;
}

void func_800BDDE8(s32, s32);

void func_800BDBD4(void)
{
    switch (engine_obj.checkpoint) {
    case 1:
        if (engine_obj.cur_character == 0) {
            func_800BDDE8(2, 4);
            func_800BDDE8(2, 0xF);
            func_800BDDE8(0x1A, 0);
        } else {
            func_800BDDE8(2, 0xC);
            func_800BDDE8(2, 0xF);
        }
        break;
    case 3:
        if (engine_obj.cur_character == 0) {
            func_800BDDE8(2, 4);
            func_800BDDE8(2, 0xC);
            func_800BDDE8(0x1A, 0);
        } else {
            func_800BDDE8(2, 4);
            func_800BDDE8(2, 0xF);
        }
        break;
    case 5:
        if (engine_obj.cur_character == 0) {
            func_800BDDE8(2, 4);
            func_800BDDE8(2, 0xC);
            func_800BDDE8(2, 0xF);
        } else {
            func_800BDDE8(2, 4);
            func_800BDDE8(2, 0xC);
        }
        break;
    }
}

extern struct Unk_unk68 D_80107574[];
extern s8 D_800FEE64[4];
extern s8 D_800FEE68[4];
extern union AnimationStep* D_800FEF50[7];

void func_80062D9C(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    arg0->state++;
    arg0->unk16 = 6;
    arg0->unk5C = 3;
    arg0->unk60 = 3;
    arg0->collision_data = D_80107574;
    arg0->unk50 = D_800FEE64;
    arg0->unk54 = D_800FEE68;
    arg0->unk15 = 0;
    arg0->unk68 = NULL;
    arg0->unk61 = 0;
    arg0->animation_table = (const u8* const*)D_800FEF50;
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk24 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk7C = 0xB4;
    arg0->ext.main_42.background_relative = 0;
    arg0->ext.main_42.unk84 = NULL;
    arg0->bg_offset = g_Player.bg_offset;
    func_80015D60(arg0, 0);
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
}

void func_80062F60(struct MainObj* arg0)
{
    struct MiscObj* misc;

    if (--arg0->unk7C == 0x5A) {
        arg0->unk28 = -arg0->unk28;
        arg0->unk2C = -arg0->unk2C;
    }
    if (--arg0->unk7C == 0) {
        if (arg0->ext.main_42.background_relative < 5) {
            arg0->unk7C = 0xB4;
            arg0->unk28 = 0;
            arg0->unk2C = 0;
            arg0->unk20 = 0;
            arg0->unk24 = 0;
            func_80015D60(arg0, 0);
            arg0->unk5 = 2;
        } else {
            arg0->unk20 = 0;
            arg0->unk24 = 0x20000;
            func_80015D60(arg0, 3);
            arg0->unk5 = 4;
            arg0->ext.main_42.unk84 = NULL;
        }
    }
    if ((arg0->unk7C & 3) == 0) {
        misc = func_8002AE90(arg0->ext.main_42.unk84, 0);
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 0xE;
            misc->ext.pointer.unk50 = arg0;
            misc->x_pos.val = arg0->x_pos.val;
            misc->y_pos.val = arg0->y_pos.val;
            misc->unk2 = arg0->animation_step.fields.event;
            arg0->ext.main_42.unk84 = misc;
        }
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
}

extern struct Unk_unk68 D_800FE2E8;
extern union AnimationStep* D_800FE48C[7];
extern struct Unk_unk68 D_801073F4[];

void func_8005F558(struct MainObj* arg0)
{
    struct MainObj* current;
    s32 resource;
    s32 clut_x;
    s32 clut_y;

    resource = func_8002938C(0x24);
    arg0->unk40 = D_801406A8[resource] >> 7;
    clut_x = func_8002938C(0x24);
    clut_y = func_8002938C(0x24);
    arg0->unk42 = ((clut_x * 4 + 0x18) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
    resource = func_8002938C(0x24);
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->unk50 = &D_800FE2E8;
    arg0->unk54 = &D_800FE2E8;
    arg0->animation_table = (const u8* const*)D_800FE48C;
    arg0->unk16 = 6;
    arg0->unk62 = 3;
    arg0->collision_data = D_801073F4;
    arg0->unk5C = 0x10;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk15 = 0;
    arg0->unk60 = 0;
    arg0->unk68 = NULL;
    arg0->unk61 = 0;
    arg0->bg_offset = g_Player.bg_offset;
    switch (arg0->unk2) {
    case 0:
        func_80015D60(arg0, 0);
        memset(SP_CUR_MAIN_OBJ->ext.main_36.pad80, 0, sizeof(SP_CUR_MAIN_OBJ->ext.main_36.pad80));
        break;
    case 1:
        func_80015D60(arg0, 1);
        arg0->unk20 = 0x18000;
        break;
    case 2:
        func_80015D60(arg0, 1);
        arg0->unk15 = 0x40;
        arg0->unk20 = -0x18000;
        break;
    }
    current = SP_CUR_MAIN_OBJ;
    current->ext.main_36.unk8A = 0x80;
    current->ext.main_36.unk8C = 0;
    SP_CUR_MAIN_OBJ->ext.main_36.unk8D = 0;
    arg0->state = 1;
    arg0->unk5 = 2;
}

void func_8005F87C(struct MainObj* arg0)
{
    struct MiscObj* misc;

    if (SP_CUR_MAIN_OBJ->ext.main_36.unk8D != 0 && g_Player.unkBA != 0) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            SP_CUR_MAIN_OBJ->ext.main_36.unk8C = 1;
            misc->active = 0x41;
            misc->id = 0xB;
            misc->unk16 = 1;
            misc->unk15 = arg0->unk15;
            misc->unk40 = arg0->unk40;
            misc->unk42 = arg0->unk42;
            misc->animation_table = (u32**)D_800FE48C;
            misc->unk3C = (void*)arg0->sprite_frames;
            misc->x_pos.val = arg0->x_pos.val;
            misc->y_pos.val = arg0->y_pos.val;
            misc->ext.misc_11.active = 0;
            misc->bg_offset = g_Player.bg_offset;
            SP_CUR_MAIN_OBJ->ext.main_36.unk84 = misc;
            func_80015D60(misc, 0);
            arg0->unk5 = 3;
            arg0->unk6 = 0;
            func_80015D60(arg0, 0);
        }
    }
    func_8002B718(MOVING_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
}

void func_8005F9F4(struct MainObj* arg0)
{
    struct MiscObj* misc;
    s32 dx;
    s32 dy;

    SP_CUR_MAIN_OBJ->ext.main_36.unk89 = func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
    func_8002B93C(MOVING_OBJECT(arg0), SP_CUR_MAIN_OBJ->ext.main_36.unk89);
    misc = SP_CUR_MAIN_OBJ->ext.main_36.unk84;
    misc->x_vel.val = arg0->unk20;
    misc->y_vel.val = arg0->unk24;
    func_8002B718(MOVING_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(SP_CUR_MAIN_OBJ->ext.main_36.unk84));
    dx = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if (dx < 0)
        dx = -dx;
    if (dx >= 2)
        return;
    dy = g_Player.y_pos.i.hi - arg0->y_pos.i.hi;
    if (dy < 0)
        dy = -dy;
    if (dy >= 2)
        return;
    func_80015D60(arg0, 3);
    func_80015D60(SP_CUR_MAIN_OBJ->ext.main_36.unk84, 3);
    arg0->unk6++;
}

extern union AnimationStep* D_8010EEB8[5];
extern u8 D_8010EECC[12];

void func_800CE8DC(struct MiscObj* arg0)
{
    struct Misc34Ext* ext = &arg0->ext.misc_34;
    s32 resource;
    s32 clut_x;
    s32 clut_y;

    arg0->unk16 = 2;
    arg0->unk15 = 0;
    arg0->animation_table = (u32**)D_8010EEB8;
    arg0->bg_offset = g_Player.bg_offset;
    resource = func_8002938C(0x90);
    arg0->unk40 = D_801406A8[resource] >> 7;
    resource = func_8002938C(0x90);
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    clut_x = func_8002938C(0x90);
    clut_y = func_8002938C(0x90);
    arg0->unk42 = ((clut_x * 4 + 0x18) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
    arg0->x_pos.i.hi = g_Player.x_pos.i.hi;
    arg0->state = 1;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    ext->timer = 0;
    ext->pad55 = 0;
    ext->variant = 0;
    ext->unk57 = 0;
    ext->unk58 = 0;
    ext->enabled = 0;
    ext->unk5A = 0;
    ext->unk5C = 0;
    ext->unk5D = 0;
    ext->timer = 0x24;
    arg0->y_pos.i.hi = g_Player.y_pos.i.hi;
    func_80015D60(arg0, 0);
    func_8001540C(2, 0xE9, arg0);
}

static void misc_34_track_axis(f32* position, s32 target, s16 target_hi)
{
    s32 delta = target - position->val;

    if (delta < 0)
        delta = -delta;
    if (delta <= 0x1FFFFF)
        return;
    position->i.hi = target < position->val ? target_hi + 0x20 : target_hi - 0x20;
}

void func_800CEBC0(struct MiscObj* arg0)
{
    struct EffectObj* related = arg0->ext.misc_34.related;
    s32 dx;
    s32 dy;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B93C(MOVING_OBJECT(arg0),
        (u8)func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player)));
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->x_vel.val *= 4;
    arg0->y_vel.val *= 3;
    misc_34_track_axis(&arg0->x_pos, g_Player.x_pos.val, g_Player.x_pos.i.hi);
    misc_34_track_axis(&arg0->y_pos, g_Player.y_pos.val, g_Player.y_pos.i.hi);
    dx = g_Player.x_pos.val - arg0->x_pos.val;
    if (dx < 0)
        dx = -dx;
    dy = g_Player.y_pos.val - arg0->y_pos.val;
    if (dy < 0)
        dy = -dy;
    if (dx > 0x20000 || dy > 0x20000) {
        func_8002B694(ANIMATED_OBJECT(arg0));
    } else {
        arg0->x_pos.val = g_Player.x_pos.val;
        arg0->y_pos.val = g_Player.y_pos.val;
    }
    if (related->state >= 3)
        arg0->ext.misc_34.enabled = 1;
    if (related->state >= 4)
        arg0->unk5 = 3;
}

void func_800CEFC0(struct MiscObj* arg0)
{
    struct Misc34Ext* ext = &arg0->ext.misc_34;
    u8 limit;
    u8 counter;

    if (ext->enabled == 0 || ext->variant == 2)
        return;
    limit = D_8010EECC[engine_obj.checkpoint * 2 + ext->variant];
    counter = ext->unk58;
    ext->unk58 = counter + 1;
    if (counter >= 0x3C) {
        if (++ext->unk57 == limit - 3 && arg0->unk17 != 3) {
            func_80015D60(arg0, 2);
            ext->unk5A = 0xB4;
        }
        ext->unk58 = 0;
    }
    if (ext->unk57 >= limit) {
        ext->variant = ext->variant == 0 ? 1 : 2;
        ext->unk57 = 0;
    }
}

extern union AnimationStep* D_8010EDAC[5];
extern s16 D_8010EDC0[6][2];
extern s16 D_8010EDD8[2];

void func_800CE388(struct MiscObj* arg0)
{
    s32 resource;
    s32 clut_x;
    s32 clut_y;

    arg0->unk16 = 2;
    arg0->unk15 = 0;
    arg0->animation_table = (u32**)D_8010EDAC;
    arg0->bg_offset = g_Player.bg_offset;
    resource = func_8002938C(0x9B);
    arg0->unk40 = D_801406A8[resource] >> 7;
    resource = func_8002938C(0x9B);
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    clut_x = func_8002938C(0x9B);
    clut_y = func_8002938C(0x9B);
    arg0->unk42 = ((clut_x * 4 + 0x18) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
    arg0->x_pos.i.hi = g_Player.x_pos.i.hi;
    arg0->y_pos.i.hi = g_Player.y_pos.i.hi;
    switch ((u32)arg0->unk2) {
    case 0:
        func_80015D60(arg0, 0);
        arg0->ext.misc_33.timer = 0x48;
        arg0->unk5 = 0;
        arg0->unk16 = 6;
        break;
    case 1:
        func_80015D60(arg0, 1);
        arg0->ext.misc_33.timer = 0x48;
        arg0->unk5 = 0;
        arg0->unk16 = 0x11;
        break;
    case 2:
    case 3:
    case 4:
        func_80015D60(arg0, arg0->unk2);
        arg0->unk5 = 1;
        arg0->unk16 = 0x10;
        break;
    }
    if (engine_obj.substage != 0) {
        arg0->x_pos.i.hi = D_8010EDD8[0];
        arg0->y_pos.i.hi = D_8010EDD8[1];
    } else if (arg0->unk2 >= 2) {
        arg0->x_pos.i.hi = D_8010EDC0[engine_obj.checkpoint][0];
        arg0->y_pos.i.hi = D_8010EDC0[engine_obj.checkpoint][1];
    } else {
        arg0->x_pos.i.hi = D_8010EDC0[engine_obj.checkpoint][0] - 0xA;
        arg0->y_pos.i.hi = D_8010EDC0[engine_obj.checkpoint][1] + 0x30;
    }
    arg0->state = 1;
    arg0->unk6 = 0;
}

extern union AnimationStep* D_8010E8FC[4];

void func_800CBF14(struct MiscObj* arg0)
{
    s32 resource;
    s32 clut_x;
    s32 clut_y;

    arg0->unk15 = arg0->x_pos.i.hi - g_Player.x_pos.i.hi > 0 ? 0 : 0x40;
    resource = func_8002938C(0x8F);
    arg0->unk40 = D_801406A8[resource] >> 7;
    resource = func_8002938C(0x8F);
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    clut_x = func_8002938C(0x8F);
    clut_y = func_8002938C(0x8F);
    arg0->unk42 = ((clut_x * 4 + 0x18) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
    arg0->animation_table = (u32**)D_8010E8FC;
    arg0->unk5 = 0;
    arg0->unk16 = 5;
    arg0->unk6 = 0;
    arg0->ext.misc_24.child_active = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->state++;
}

void func_800CC114(struct MiscObj* arg0)
{
    struct MiscObj* child;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step != 0)
        return;
    arg0->unk6 = 0;
    arg0->unk5 = 1;
    child = find_free_misc_obj();
    if (child == NULL)
        return;
    child->active = 0x41;
    child->id = 0xB;
    child->unk2 = 3;
    child->unk16 = 3;
    child->unk15 = arg0->unk15;
    child->unk40 = arg0->unk40;
    child->unk42 = arg0->unk42;
    child->unk3C = arg0->unk3C;
    child->animation_table = arg0->animation_table;
    child->bg_offset = arg0->bg_offset;
    child->x_pos.val = arg0->x_pos.val;
    child->y_pos.val = arg0->y_pos.val;
    func_80015D60(child, 2);
    child->ext.misc_11.active = 0;
    arg0->ext.misc_24.child = child;
    arg0->ext.misc_24.child_active = 1;
}

extern union AnimationStep* D_8010EF68[3];
extern u16 D_8010EF74[8];
extern s32 D_8010EF84[4];
extern s32 D_8010EF94[4];
extern u16 D_8010EFB4[4];

void func_800CFB70(struct MiscObj* arg0)
{
    u8 resource = func_8002938C(0x9F);

    arg0->active |= 0x40;
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->unk40 = D_801406A8[resource] >> 7;
    arg0->unk42 = SOME_COORDINATE_CONVERSION(resource);
    arg0->animation_table = (u32**)D_8010EF68;
    arg0->unk16 = 0x20;
    arg0->bg_offset = 1;
    arg0->unk15 = 0x40;
    arg0->state++;
    arg0->unk2 &= 3;
    arg0->ext.misc_24.timer = D_8010EFB4[arg0->unk2];
}

void func_800CFC6C(struct MiscObj* arg0)
{
    if (arg0->ext.misc_24.timer != 0) {
        arg0->ext.misc_24.timer--;
        return;
    }
    arg0->x_pos.i.hi = background_objects[1].x_pos.i.hi + 0x14A;
    arg0->y_pos.i.hi = background_objects[1].y_pos.i.hi + D_8010EF74[get_random() & 7];
    func_80015D60(arg0, 1);
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk5++;
    arg0->x_vel.val = D_8010EF84[arg0->unk2];
    arg0->unk2C = D_8010EF94[arg0->unk2];
}

void func_800DA750(struct LayerObj*);
void func_800DA5C4(struct LayerObj*);
extern void (*D_8010FFB0[])(struct LayerObj*);

static s32 layer_05_scroll(struct LayerObj* arg0)
{
    s32 value;

    memcpy(&value, &arg0->bg_offset, sizeof(value));
    return value;
}

void func_800DA2D4(struct LayerObj* arg0)
{
    s32 scroll = 0x8000;

    arg0->state++;
    background_objects[1].unk4D = 2;
    background_objects[2].unk4D = 2;
    background_objects[1].unk4E = 7;
    background_objects[2].unk4E = 8;
    memcpy(&arg0->bg_offset, &scroll, sizeof(scroll));
    arg0->unk18.val = -0x5800;
    arg0->private_state.value.val = 0;
    memset(arg0->pad20, 0, sizeof(arg0->pad20));
    arg0->unk24 = 3;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    func_800DA358(arg0);
}

void func_800DA358(struct LayerObj* arg0)
{
    s32 half = (background_objects[0].unk14.val - background_objects[0].x_pos.val) / 2;

    background_objects[1].x_pos.val += layer_05_scroll(arg0) - half;
    background_objects[2].x_pos.val -= layer_05_scroll(arg0) / 2 + half / 2;
    arg0->unk25 = arg0->unk24;
    if (engine_obj.substage != 0)
        return;
    func_800DA750(arg0);
    D_8010FFB0[arg0->unk5](arg0);
    if (engine_obj.substage != 0)
        return;
    func_800DA5C4(arg0);
    if (g_Player.x_pos.i.hi >= 0x18D0)
        engine_obj.unkF = 1;
}

extern struct Unk_unk68 D_80107F04[];
extern struct Unk_unk68 D_80103C84;
extern struct Unk_unk68 D_80103C88;
extern void (*D_80103E90[7])();
void func_80082FEC(struct MainObj*);
void func_8002E184(struct PlayerObj*);

void func_80082470(struct MainObj* arg0)
{
    struct Main67Ext* ext = &arg0->ext.main_67;

    arg0->active = 0x41;
    arg0->unk5C = 0x1E;
    arg0->unk60 = 0;
    arg0->unk61 = 0;
    arg0->collision_data = D_80107F04;
    arg0->animation_table = (const u8* const*)D_80103E08;
    arg0->unk16 = 6;
    arg0->unk68 = &D_80103C88;
    arg0->unk54 = &D_80103C84;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk50 = NULL;
    arg0->unk15 = 0;
    arg0->unk75 = 1;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    func_80015D60(arg0, 0);
    ext->vertical_speed = -0x5800;
    arg0->unk5 = 2;
    ext->delay = 0;
    ext->direction = 0;
    ext->unk89 = 0;
    ext->unk8A = 0;
    memset(ext->pad8B, 0, sizeof(ext->pad8B));
    ext->unk8D = 0;
    memset(ext->pad8E, 0, sizeof(ext->pad8E));
    ext->saved_unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7C = 0x28;
    arg0->state++;
}

void func_80082574(struct MainObj* arg0)
{
    s32 collision;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_80103E90[arg0->unk5](arg0);
    collision = func_8002DD04(arg0);
    func_8002D9BC(arg0);
    if (arg0->ext.main_67.unk89 == 0)
        func_80082FEC(arg0);
    func_8002E184(PLAYER_OBJECT(arg0));
    if (arg0->unk5 != 0)
        arg0->ext.main_67.saved_unk5 = arg0->unk5;
    if (collision < 0) {
        arg0->unk7C = 0x64;
        arg0->unk7E = 5;
        arg0->unk5 = 0;
        arg0->unk42 &= 0x7FFF;
        arg0->state++;
        return;
    }
    if (collision != 0
        && (engine_obj.cur_character == 0 ? (collision == 2 || collision == 0xB) : collision == 0x21)
        && arg0->unk5 != 6) {
        arg0->unk5 = 6;
        arg0->unk6 = 0;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x60, 0x60) != 0) {
        func_8002B0C8(OBJECT_HEADER(arg0));
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
}

void func_800828B4(struct MainObj* arg0)
{
    s32 dx;
    s32 dy;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    dx = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if (dx < 0)
        dx = -dx;
    if (--arg0->unk7C == 0) {
        if (dx < 0xC1) {
            dy = g_Player.y_pos.i.hi - arg0->y_pos.i.hi;
            if (dy < 0)
                dy = -dy;
            arg0->unk5 = dy < 0x31 ? 3 : 4;
        } else {
            arg0->unk5 = 4;
        }
        arg0->unk6 = 0;
        arg0->ext.main_67.unk8D = 0;
    }
    if (arg0->unk72 == 8 && arg0->ext.main_67.unk8D != 0) {
        dx = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
        if (dx < 0)
            dx = -dx;
        if (dx < 0xC1) {
            arg0->unk5 = 4;
            arg0->unk6 = 0;
            arg0->ext.main_67.unk8D = 1;
        }
    }
}

extern u8 D_801099B0[4];
extern u8 D_801099B4[4];
extern s32 D_801099B8[2];
void func_800A6DF4(struct ShotObj*);

void func_800A699C(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;

    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->unk60 = 5;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk42 &= 0x7FFF;
    if (arg0->unk2 < 2) {
        arg0->x_pos.i.hi = owner->x_pos.i.hi + (arg0->unk15 != 0 ? 0x45 : -0x45);
        arg0->y_pos.i.hi = owner->y_pos.i.hi + (arg0->unk2 == 0 ? -0x1A : -9);
        arg0->unk50.data = D_801099B0;
        arg0->unk58.collision_data = D_80106070;
        arg0->unk68 = NULL;
        arg0->unk54 = D_801099B0;
        arg0->x_vel.val = D_801099B8[arg0->unk15 != 0 ? 1 : 0];
        func_80015D60(arg0, 2);
        arg0->state = 1;
        arg0->unk60 = 4;
        return;
    }
    arg0->unk50.data = D_801099B4;
    arg0->unk54 = D_801099B4;
    arg0->unk58.animation_steps = D_80105FF0;
    arg0->unk68 = NULL;
    arg0->x_vel.val = -0x28000;
    arg0->y_vel.val = 0x28000;
    switch (arg0->unk2) {
    case 2:
        arg0->x_pos.i.hi = owner->x_pos.i.hi + 0x14;
        arg0->y_pos.i.hi = owner->y_pos.i.hi - 0x27;
        break;
    case 3:
        arg0->x_pos.i.hi = owner->x_pos.i.hi + 8;
        arg0->y_pos.i.hi = owner->y_pos.i.hi - 0x19;
        break;
    case 4:
        arg0->x_pos.i.hi = owner->x_pos.i.hi + 8;
        arg0->y_pos.i.hi = owner->y_pos.i.hi - 0x33;
        break;
    case 5:
        arg0->x_pos.i.hi = owner->x_pos.i.hi + 0x14;
        arg0->y_pos.i.hi = owner->y_pos.i.hi - 0x40;
        break;
    }
    arg0->unk90.bytes[1] = 0x14;
    arg0->unk90.bytes[0] = 0xC;
    arg0->unk8C.word = 0x5A;
    func_80015D60(arg0, 5);
    arg0->unk7 = 2;
    arg0->state = 2;
    arg0->unk60 = 6;
}

void func_800A6C7C(struct ShotObj* arg0)
{
    struct MiscObj* misc;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (func_8002DD04((struct MainObj*)arg0) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        arg0->state = 3;
        return;
    }
    if (func_8002D9BC(arg0) != 0) {
        func_800AF808(BASE_OBJECT(arg0));
        arg0->state++;
        return;
    }
    if (arg0->unk8C.word != 0) {
        func_800A6DF4(arg0);
        arg0->unk8C.word--;
    }
    if (arg0->unk7 == 0) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x21;
            misc->id = 0x17;
            misc->unk2 = 0;
            misc->unk15 = get_random() & 0x40;
            misc->ext.unk.unk54 = 0;
            misc->x_pos.i.hi = arg0->x_pos.i.hi;
            misc->unk7 = 1;
            misc->x_vel.val = 0;
            misc->y_vel.val = 0;
            misc->unk16 = 7;
            misc->y_pos.i.hi = arg0->y_pos.i.hi;
        }
        arg0->unk7 = 2;
    } else {
        arg0->unk7--;
    }
    if (func_8002B160(BASE_OBJECT(arg0)) != 0) {
        arg0->state++;
        return;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800A6DF4(struct ShotObj* arg0)
{
    u8 timer = arg0->unk90.bytes[1];
    u8 target;
    u8 current;
    u8 next;
    s32 animation;

    arg0->unk90.bytes[1] = timer - 1;
    if (timer != 0)
        return;
    arg0->unk90.bytes[1] = 1;
    arg0->unk16 = 5;
    target = func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
    current = arg0->unk90.bytes[0];
    if (current < target) {
        if (target == current + 1)
            return;
        if (target - current < 0x11)
            next = (current + 1) & 0x1F;
        else
            next = ((current | 0x20) - 1) & 0x1F;
    } else if (target < current) {
        if (target == current - 1)
            return;
        if (current - target < 0x11)
            next = ((current | 0x20) - 1) & 0x1F;
        else
            next = (current + 1) & 0x1F;
    } else {
        return;
    }
    arg0->unk90.bytes[0] = next;
    func_8002B93C(MOVING_OBJECT(arg0), next);
    arg0->x_vel.val <<= 2;
    arg0->y_vel.val <<= 2;
    animation = next / 2;
    func_80015D60(arg0, animation < 4 ? animation + 0xF : animation - 1);
}

extern u8 D_800FFBD8[4];
extern u8 D_800FFBDC[8];
extern u8 D_800FFBE4[8];
extern union AnimationStep* D_800FFC14[10];
extern void (*D_800FFC4C[2])();

void func_80069748(struct MainObj* arg0)
{
    s32 resource;
    s32 clut_x;
    s32 clut_y;

    arg0->on_screen = 0;
    arg0->unk60 = 0;
    arg0->unk61 = 0;
    resource = func_8002938C(0x28);
    arg0->unk40 = D_801406A8[resource] >> 7;
    clut_x = func_8002938C(0x28);
    clut_y = func_8002938C(0x28);
    arg0->unk42 = ((clut_x * 4 + 0x18) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
    resource = func_8002938C(0x28);
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->unk16 = 6;
    arg0->unk54 = D_800FFBD8;
    arg0->animation_table = (const u8* const*)D_800FFC14;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk50 = NULL;
    arg0->unk68 = NULL;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->ext.main_50.unk84 = (u8)arg0->unk2 >> 4;
    arg0->unk2 &= 0xF;
    arg0->collision_data = arg0->ext.main_50.unk84 == 8 ? D_80108584 : D_80108504;
    arg0->unk5C = 3;
    arg0->unk15 = 0;
    arg0->state = 1;
    arg0->unk5 = 1;
}

void func_800698D8(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FFC4C[arg0->unk5](arg0);
    if (func_8002DD04(arg0) >= 0) {
        if (func_8002B160(BASE_OBJECT(arg0)) != 0)
            func_8002B0C8(OBJECT_HEADER(arg0));
        return;
    }
    arg0->ext.main_50.timer = 0;
    func_800C813C(6, arg0->ext.main_50.unk84 == 8 ? D_800FFBE4 : D_800FFBDC, arg0);
    if (engine_obj.stage == 8) {
        func_800DABE4(arg0->unk2 + 8, arg0->x_pos.i.hi - 0x20, arg0->y_pos.i.hi - 0x40);
    } else {
        func_800DABE4(arg0->unk2, arg0->x_pos.i.hi - 0x20, arg0->y_pos.i.hi - 0x30);
        if (arg0->ext.main_50.unk84 != 0)
            func_800DABE4(arg0->ext.main_50.unk84, arg0->x_pos.i.hi - 0x20, arg0->y_pos.i.hi);
    }
    arg0->ext.main_50.unk84 = 0;
    arg0->state = 2;
    arg0->unk5 = 0;
}

void func_800DAB9C(struct TileEffectRecord*, s32, s32, s32);

void func_800DA984(s32 arg0, s32 arg1, s32 arg2)
{
    struct TileEffectRecord* record
        = D_80119388[engine_obj.stage * 2 + engine_obj.substage][(u8)arg0];

    for (;;) {
        u16 x = record->x + (u16)arg1;
        u16 y = record->y + (u16)arg2;
        s32 count = record->packed_count >> 1;
        s32 horizontal = record->packed_count & 1;
        u16 bg_x = background_objects[record->layer].x_pos.i.hi;
        u16 bg_y = background_objects[record->layer].y_pos.i.hi;
        u8 i = 0;

        while (count != 0) {
            s16 tile_x = x;
            s16 tile_y = y;

            if (func_800DAB40((s16)bg_x, (s16)bg_y, tile_x, tile_y)) {
                if (tile_x < 0)
                    tile_x += 0xF;
                if (tile_y < 0)
                    tile_y += 0xF;
                func_800DAB9C(record, (u16)(tile_x >> 4), (u16)(tile_y >> 4), i);
            }
            if (horizontal)
                x += 0x10;
            else
                y += 0x10;
            i++;
            if (i == count)
                break;
        }
        if (record->has_next == 0)
            break;
        record++;
    }
}

extern struct Unk_unk68 D_801074F4[];
extern struct Unk_unk68 D_800FE734;
extern struct Unk_unk68 D_800FE738;
extern struct Unk_unk68 D_800FE73C;
extern u8 D_800FE8E4[8];
extern void (*D_800FE8FC[7])();

void func_80060AC4(struct MainObj* arg0)
{
    struct Main38Ext* ext = &arg0->ext.main_38;

    arg0->active = 0x41;
    arg0->unk5C = 0x12;
    arg0->unk60 = 6;
    arg0->unk61 = 0;
    arg0->collision_data = D_801074F4;
    arg0->animation_table = (const u8* const*)D_800FE890;
    arg0->unk16 = 5;
    arg0->unk68 = &D_800FE73C;
    arg0->unk54 = &D_800FE734;
    arg0->unk15 = 0;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk50 = &D_800FE738;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    func_80015D60(arg0, 0);
    arg0->unk7E = 0xA;
    ext->saved_unk5 = 0;
    ext->unk84 = 0;
    ext->unk88 = 0;
    ext->unk8C = 0;
    ext->unk90 = 0;
    ext->unk94 = 0;
    arg0->unk7C = 0;
    arg0->unk5 = 2;
    arg0->unk6 = 0;
    arg0->state++;
}

void func_80060BC4(struct MainObj* arg0)
{
    s32 collision;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FE8FC[arg0->unk5](arg0);
    collision = func_8002DD04(arg0);
    func_8002D9BC(arg0);
    func_8002E184(PLAYER_OBJECT(arg0));
    if (arg0->unk5 != 0)
        arg0->ext.main_38.saved_unk5 = arg0->unk5;
    if (collision < 0) {
        func_800C813C(6, D_800FE8E4, arg0);
        if (engine_obj.stage == 8)
            func_800DABE4(0xB, (s16)(arg0->x_pos.i.hi - 0x28), arg0->y_pos.i.hi);
        arg0->ext.main_38.unk88 = 2;
        arg0->ext.main_38.unk8C = 1;
        arg0->unk7C = 0x20;
        arg0->unk7E = 5;
        arg0->on_screen = 0;
        arg0->state++;
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x50, 0x40) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x40, 0x20);
        return;
    }
    if (arg0->unk5 == 4)
        return;
    if (arg0->x_pos.val < g_Player.x_pos.val)
        arg0->state += 2;
    else
        arg0->unk5 = 2;
}

extern u8 D_80108FBC[4];
extern u8 D_80108FC0[4];

void func_8009D048(struct ShotObj* arg0)
{
    struct WeaponObj* owner = arg0->unk7C;
    s32 distance;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if ((u32)(arg0->unk84.value - 0x1A) < 0x4A)
        func_8002D9BC(arg0);
    if (arg0->unk84.value == 0x46)
        arg0->unk50.data = arg0->unk2 != 0 ? D_80108FC0 : D_80108FBC;
    if (arg0->unk84.value == 0x19)
        func_80015D60(arg0, arg0->unk2 != 0 ? 0xC : 0xB);
    distance = background_objects[0].x_pos.i.hi - owner->x_pos.i.hi;
    if (distance < 0)
        distance = -distance;
    if ((u16)distance >= 0x1A0) {
        if (arg0->unk2 != 0)
            arg0->x_pos.i.hi = owner->x_pos.i.hi - distance + 0x29;
        else
            arg0->x_pos.i.hi = owner->x_pos.i.hi - (distance - 0x129);
    }
    if (--arg0->unk84.value == 0 || owner->active == 0 || owner->state >= 2)
        arg0->state++;
    func_8002B318(BASE_OBJECT(arg0), 0x80, 0x20);
}

extern u8 D_80108FDC[4];
extern u8 D_80108FE0[4];
extern u8 D_80108FE4[4];
extern u8 D_80108FE8[4];
extern u8 D_80108FEC[4];
extern u8 D_80108FF0[4];
void func_8009D588(struct ShotObj*);

void func_8009D23C(struct ShotObj* arg0)
{
    struct WeaponObj* owner;
    s32 distance;
    u32 half;
    u32 steps;

    arg0->unk68 = (struct Unk_unk68*)D_80108FE8;
    arg0->unk58.animation_steps = D_80105FF0;
    arg0->unk60 = 3;
    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->unk54 = D_80108FDC;
    arg0->state++;
    arg0->unk42 &= 0x7FFF;
    owner = arg0->unk7C;
    if (arg0->unk2 != 0) {
        arg0->unk50.data = D_80108FE0;
        arg0->x_pos.i.hi = owner->x_pos.i.hi + 0xA;
        arg0->y_pos.i.hi = owner->y_pos.i.hi - 0x10;
    } else {
        arg0->unk50.data = D_80108FDC;
        arg0->x_pos.i.hi = owner->x_pos.i.hi + 0x12;
        arg0->y_pos.i.hi = owner->y_pos.i.hi;
    }
    arg0->x_vel.val = -0x28000;
    arg0->y_vel.val = 0x28000;
    arg0->unk28 = 0;
    distance = arg0->x_pos.val - g_Player.x_pos.val;
    if (distance < 0)
        distance = -distance;
    half = distance / 2;
    if (half <= 0x1FFFFF)
        half += 0x100000;
    if (half > 0x400000)
        half -= arg0->unk2 << 21;
    distance = arg0->x_vel.val;
    if (distance < 0)
        distance = -distance;
    steps = half / (u32)distance;
    if (steps == 0)
        steps = 1;
    arg0->unk84.value = 0;
    arg0->unk70 = 0;
    arg0->unk7 = 1;
    arg0->unk2C = (u32)arg0->y_vel.val / steps;
    func_80015D60(arg0, 7);
}

void func_8009D3F4(struct ShotObj* arg0)
{
    struct MiscObj* misc;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (func_8002DD04((struct MainObj*)arg0) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        arg0->state++;
        return;
    }
    func_8002D9BC(arg0);
    if (arg0->unk84.value != 0)
        CollisionRelated((struct PlayerObj*)arg0);
    func_8009D588(arg0);
    if (arg0->y_pos.i.hi >= background_objects[0].y_pos.i.hi + 0xE0)
        arg0->unk70 = 1;
    if (arg0->unk70 != 0) {
        func_800AF808(BASE_OBJECT(arg0));
        arg0->state++;
        return;
    }
    if (arg0->unk7 == 0) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x21;
            misc->id = 0x17;
            misc->unk2 = 0;
            misc->unk15 = get_random() & 0x40;
            misc->ext.unk.unk54 = 0;
            misc->x_pos.i.hi = arg0->x_pos.i.hi;
            misc->unk7 = 1;
            misc->x_vel.val = 0;
            misc->y_vel.val = 0;
            misc->unk16 = 7;
            misc->y_pos.i.hi = arg0->y_pos.i.hi;
        }
        arg0->unk7 = 1;
    } else {
        arg0->unk7--;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x120, 0x40) != 0) {
        arg0->state++;
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
}

static s32 shot_21_abs(s32 value)
{
    return value < 0 ? -value : value;
}

void func_8009D588(struct ShotObj* arg0)
{
    switch (arg0->unk84.value) {
    case 0:
        if (shot_21_abs(arg0->y_vel.val) >= shot_21_abs(arg0->x_vel.val / 2))
            return;
        func_80015D60(arg0, 8);
        arg0->unk68 = (struct Unk_unk68*)D_80108FEC;
        arg0->unk54 = D_80108FE0;
        arg0->unk50.data = D_80108FE0;
        break;
    case 1:
        if (shot_21_abs(arg0->y_vel.val) < shot_21_abs(arg0->x_vel.val / 2))
            return;
        func_80015D60(arg0, 9);
        arg0->unk68 = (struct Unk_unk68*)D_80108FE8;
        arg0->unk54 = D_80108FDC;
        arg0->unk50.data = D_80108FDC;
        break;
    case 2:
        if (shot_21_abs(arg0->x_vel.val) >= shot_21_abs(arg0->y_vel.val / 2))
            return;
        func_80015D60(arg0, 0xA);
        arg0->unk68 = (struct Unk_unk68*)D_80108FF0;
        arg0->unk54 = D_80108FE4;
        arg0->unk50.data = D_80108FE4;
        break;
    default:
        return;
    }
    arg0->unk84.value++;
}

extern s16 D_800FE18C[][2];

void func_8005E5C0(struct MainObj* arg0)
{
    s32 resource;
    s32 clut_x;
    s32 clut_y;

    resource = func_8002938C(0x22);
    arg0->unk40 = D_801406A8[resource] >> 7;
    clut_x = func_8002938C(0x22);
    clut_y = func_8002938C(0x22);
    arg0->unk42 = ((clut_x * 4 + 0x1A) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
    resource = func_8002938C(0x22);
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->bg_offset = g_Player.bg_offset;
    arg0->x_pos.i.hi = D_800FE18C[arg0->unk2][0];
    arg0->y_pos.i.hi = D_800FE18C[arg0->unk2][1];
    arg0->animation_table = (const u8* const*)D_800FE0FC;
    arg0->unk16 = 6;
    arg0->unk20 = -0x1C000;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk15 = 0;
    arg0->unk50 = NULL;
    arg0->unk54 = NULL;
    arg0->collision_data = NULL;
    arg0->unk61 = 0;
    arg0->unk5C = 1;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (arg0->unk2 != 2)
        arg0->unk68 = &D_800FDFB8;
    func_80015D60(arg0, 1);
    arg0->state = 1;
    arg0->unk5 = 0;
}

void func_8005EB40(struct MainObj* arg0)
{
    if (--SP_CUR_MAIN_OBJ->ext.main_34.unk80 > 0)
        return;
    if (arg0->unk2 == 0) {
        arg0->unk20 = -0x1C000;
        arg0->unk24 = 0xC000;
        arg0->unk2C = 0x2000;
        arg0->unk68 = NULL;
        func_80015D60(arg0, 5);
        arg0->unk5 = 4;
    } else {
        arg0->unk68 = NULL;
        arg0->unk15 = 0x40;
        arg0->unk20 = 0x38000;
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        func_80015D60(arg0, 1);
        arg0->unk5 = 5;
    }
}

extern u8 D_80108F9C[4];
extern u8 D_80108FA0[8];
extern s8 D_80108FA8[4];

void func_8009CCB4(struct ShotObj* arg0)
{
    arg0->unk68 = (struct Unk_unk68*)D_80108F9C;
    arg0->unk60 = 2;
    arg0->unk2C = 0x2000;
    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->y_vel.val = 0x1F000;
    arg0->unk28 = 0;
    arg0->unk67 = 0;
    arg0->unk16 = 0;
    arg0->unk54 = NULL;
    arg0->unk50.data = NULL;
    arg0->unk58.data = NULL;
    arg0->x_vel.val = -0x1C000;
    arg0->state++;
    arg0->unk42 &= 0x7FFF;
    arg0->x_pos.i.hi += D_80108FA8[0];
    arg0->y_pos.i.hi += D_80108FA8[1];
    func_80015D60(arg0, 6);
}

void func_8009CDE0(struct ShotObj* arg0)
{
    if (--arg0->unk84.value == 0) {
        arg0->state++;
        return;
    }
    if (arg0->unk84.value == 0x20)
        ((struct LayerObj*)arg0->unk7C)->private_state.signed_byte = 1;
    if (D_80141BD8.unk0 & 7)
        return;
    if (arg0->unk84.value >= 0x34) {
        func_800C842C(8, D_80108FA0, arg0, 0x28, D_800FFC14);
        arg0->x_pos.i.hi += 0x20;
        func_800C842C(8, D_80108FA0, arg0, 0x28, D_800FFC14);
        arg0->x_pos.i.hi -= 0x20;
    }
    func_800AF878(BASE_OBJECT(arg0), 1, 0x30, 0x20);
    func_800AF878(BASE_OBJECT(arg0), 1, 0x18, 0x10);
    func_80028BAC(8, 4, 1);
}

#define RIDE_U8(object, offset) (((u8*)&(object)->unk7C)[(offset)-0x7C])
#define RIDE_S8(object, offset) (*(s8*)&RIDE_U8(object, offset))
#define RIDE_U16(object, offset) (*(u16*)&RIDE_U8(object, offset))

MMX4_STATIC_ASSERT(ride_armor_tail_layout,
    MMX4_OFFSET_OF(struct RideArmorObj, saved_y_vel) - MMX4_OFFSET_OF(struct RideArmorObj, unk7C) == 0x9E - 0x7C);
MMX4_STATIC_ASSERT(ride_armor_player_unk9A,
    MMX4_OFFSET_OF(struct RideArmorObj, pad9A) == MMX4_OFFSET_OF(struct PlayerObj, unk9A));

extern union AnimationStep* D_800F8FC4[38];
extern u8 D_800F905C[12];
extern u8 D_800F9068[4];
extern u8 D_800F906C[4];
extern s32 D_800F9070[2];
extern s32 D_800F9078[2];
extern s32 D_800F9080[2];
extern s32 D_800F9088[2];
extern s32 D_800F9090[2];
extern s32 D_800F9098[2];
extern u8 D_800F9100[4];
extern u8 D_800F9104[4];
extern u8 D_800F9108[4];
extern u8 D_800F910C[4];
extern u8 D_800F9110[4];
extern u8 D_800F9114[4];
extern void (*D_800F90E8[])(struct RideArmorObj*);
void func_8003B458(void*, s8);
void func_8003D164(struct RideArmorObj*, s32);
void func_8003CF6C(struct RideArmorObj*);
u8 func_8003CF24(struct RideArmorObj*);
void func_8003CA44(struct RideArmorObj*);
void func_8003D01C(struct RideArmorObj*);
void func_8003D3B4(struct PlayerObj*);
void func_8003B98C(struct PlayerObj*);
void func_8003B694(struct RideArmorObj*);
void func_8003CCBC(struct RideArmorObj*);
void func_8003C9A4(struct RideArmorObj*);
void func_8003D338(struct RideArmorObj*);
void func_8003D39C(struct RideArmorObj*);

static u16 ride_chaser_clut(void)
{
    u8 resource = func_8002938C(0x82);

    return SOME_COORDINATE_CONVERSION(resource);
}

static void ride_chaser_spawn_body(struct RideArmorObj* arg0)
{
    struct WeaponObj* weapon = find_free_weapon_obj();
    u8 unk16;

    if (weapon == NULL)
        return;
    weapon->active = 0x41;
    weapon->id = 0x39;
    weapon->x_pos.i.hi = arg0->x_pos.i.hi;
    weapon->y_pos.i.hi = arg0->y_pos.i.hi;
    weapon->animation_table = (u32**)arg0->animation_table;
    weapon->unk40 = arg0->unk40;
    weapon->unk3C = arg0->unk3C;
    weapon->unk42 = ride_chaser_clut();
    weapon->owner = (struct PlayerObj*)arg0;
    unk16 = arg0->unk16;
    weapon->unk16 = unk16;
    weapon->unk15 = arg0->unk15;
}

void func_8003B470(struct RideArmorObj* arg0)
{
    struct EffectObj* effect;
    u8 resource;

    arg0->state = 1;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->on_screen = 1;
    arg0->active |= 0x40;
    arg0->x_pos.val = g_Player.x_pos.val;
    arg0->unk15 = 0x40;
    arg0->animation_table = (u32**)D_800F8FC4;
    arg0->y_pos.val = g_Player.y_pos.val;
    resource = func_8002938C(0x82);
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->unk40 = D_801406A8[resource] >> 7;
    arg0->unk42 = SOME_COORDINATE_CONVERSION(resource);
    if (g_Player.unk2 != 0)
        arg0->unk42 += 2;
    arg0->unk16 = 4;
    arg0->unk54 = D_800F906C;
    arg0->unk60 = 0;
    arg0->unk61 = 0;
    arg0->unk67 = 0;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk50 = NULL;
    arg0->unk68 = (struct Unk_unk68*)D_800F9068;
    arg0->unk58 = NULL;
    arg0->unk5C = g_Player.unk5C;
    func_8002C808((struct PlayerObj*)arg0);
    arg0->unk7D = 0;
    arg0->unk7E = 0;
    arg0->unk80.bytes.unk83 = 0;
    arg0->unk80.bytes.unk82 = 0;
    arg0->unk7C = 1;
    arg0->unk7D = 0;
    arg0->unk80.bytes.unk81 = 0;
    arg0->unk80.bytes.unk80 = 0;
    g_Player.unkC5 = 1;
    RIDE_U8(arg0, 0x9B) = 1;
    arg0->unk8E = 0;
    func_80015D60(arg0, 0);
    func_8003B458(arg0, 0x41);
    RIDE_U8(arg0, 0x89) = 0;
    RIDE_U8(arg0, 0x98) = 0;
    RIDE_U8(arg0, 0x9A) = 0;
    RIDE_U16(arg0, 0x9C) = 0;
    background_objects[arg0->bg_offset].unk30 = 0x200;
    func_8003D164(arg0, 0);
    effect = find_free_effect_obj();
    if (effect != NULL) {
        effect->active = 1;
        effect->id = 0x1B;
        arg0->unkA0.chaser_effect = effect;
    }
    background_objects[0].unk44 = 1;
    background_objects[1].unk44 = 1;
    background_objects[2].unk44 = 1;
}

void func_8003B694(struct RideArmorObj* arg0)
{
    const struct Unk_unk68* bounds = arg0->unk68;
    s32 x;

    if (arg0->unk15 == 0)
        x = arg0->x_pos.i.hi + bounds->unk0;
    else
        x = arg0->x_pos.i.hi - bounds->unk0;
    if ((u8)func_8002D724((struct PlayerObj*)arg0, (s16)x,
            (s16)(arg0->y_pos.i.hi + bounds->unk1 + bounds->unk3 - 0xF))
        != 0x24) {
        RIDE_U16(arg0, 0x9C) = 0;
        return;
    }
    if (RIDE_U16(arg0, 0x9C) != 0) {
        RIDE_U16(arg0, 0x9C) -= 1;
        return;
    }
    arg0->x_pos.i.hi -= 8;
    arg0->y_pos.i.hi += 0x10;
    func_800C7B80((struct MainObj*)arg0, 4);
    RIDE_U16(arg0, 0x9C) = 2;
    arg0->y_pos.i.hi -= 0x10;
    arg0->x_pos.i.hi += 8;
}

void func_8003B7B4(struct RideArmorObj* arg0)
{
    s8 health = arg0->unk5C;

    if (health == 0 || g_Player.unk5C == 0) {
        g_Player.unk5C = -0x80;
        arg0->unk5C = -0x80;
        func_800C813C(0xB, D_800F905C, arg0);
        arg0->state = 3;
        return;
    }
    if (health < 0 && (health & 0x7F) != 0) {
        RIDE_U8(arg0, 0x9A) = 1;
        arg0->unk61 = 0x79;
        arg0->unk85 = 1;
        g_Player.unk5C = arg0->unk5C & 0x7F;
    }
    if (background_objects[0].pad51[0] != 0) {
        RIDE_U8(arg0, 0x9B) = 0;
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    if (background_objects[0].unk4 == 1 && RIDE_S8(arg0, 0x9B) != 0) {
        arg0->x_pos.i.hi += background_objects[0].x_pos.i.hi - background_objects[0].unk14.i.hi;
        arg0->y_pos.i.hi += background_objects[0].y_pos.i.hi - background_objects[0].unk18.i.hi;
    }
    D_800F90E8[arg0->unk5](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
    func_8003B694(arg0);
    if (arg0->unk5 != 0) {
        func_8003CF6C(arg0);
        arg0->unk80.bytes.unk83 = arg0->unk80.bytes.unk82;
        arg0->unk80.bytes.unk82 = func_8003CF24(arg0);
        func_8003CA44(arg0);
        if (RIDE_U8(arg0, 0x89) != 0)
            RIDE_U8(arg0, 0x89) -= 1;
        func_8003D01C(arg0);
    }
    func_8003D3B4((struct PlayerObj*)arg0);
    func_8003B98C((struct PlayerObj*)arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

void func_8003BB20(struct RideArmorObj* arg0)
{
    s16 dx = arg0->x_pos.i.hi - background_objects[arg0->bg_offset].x_pos.i.hi;
    struct EffectObj* effect;
    s32 speed;

    switch (arg0->unk6) {
    case 0:
        arg0->unk6 = 1;
        arg0->unk7C = 1;
        arg0->x_vel.val = 0;
        arg0->y_vel.val = 0;
        arg0->unk28 = 0x8000;
        arg0->unk2C = 0;
        arg0->unk15 = 0x40;
        func_8001540C(5, 0, NULL);
        func_80015D60(arg0, 6);
        func_8003B458(arg0, 0x47);
        ride_chaser_spawn_body(arg0);
        func_8002B694(ANIMATED_OBJECT(arg0));
        return;
    case 1:
        speed = arg0->x_vel.val;
        if (speed < 0)
            speed = -speed;
        if (speed > 0x7FFFF) {
            arg0->x_vel.val = 0x80000;
            arg0->unk28 = 0;
        }
        if (dx >= 0xC0) {
            arg0->unk6 = 2;
            arg0->x_vel.val = 0x60000;
            arg0->unk28 = -0x4000;
        }
        break;
    case 2:
        if (dx < 0x91) {
            arg0->unk6 = 3;
            arg0->x_vel.val = 0;
            arg0->unk28 = 0;
            func_80015D60(arg0, 7);
            func_8003B458(arg0, 0x4B);
        }
        break;
    case 3:
        if (arg0->animation_step.fields.relative_step == 0)
            arg0->unk6 = 4;
        break;
    case 4:
        effect = arg0->unkA0.chaser_effect;
        if (effect->active == 0 || effect->unk5 == 3) {
            arg0->unk5 = 1;
            arg0->unk6 = 0;
        }
        break;
    default:
        func_8002B694(ANIMATED_OBJECT(arg0));
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
}

static void ride_chaser_land_animation(struct RideArmorObj* arg0)
{
    switch (arg0->unk80.bytes.unk82) {
    case 0:
        func_80015D60(arg0, 5);
        func_8003B458(arg0, 0x46);
        break;
    case 1:
        func_80015D60(arg0, 4);
        func_8003B458(arg0, 0x44);
        break;
    case 2:
        func_80015D60(arg0, 3);
        func_8003B458(arg0, 0x42);
        break;
    }
}

void func_8003BF1C(struct RideArmorObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        arg0->unk2C = 0x5000;
    }
    arg0->unk67 = 1;
    func_8003C6EC(arg0, 4);
    if (arg0->unk70 & 8) {
        arg0->unk67 = 0;
        arg0->unk2C = 0;
        arg0->y_vel.val = 0;
        if (arg0->unk7D != 0) {
            arg0->unk5 = 5;
            arg0->unk6 = 1;
            RIDE_U8(arg0, 0x99) = 0;
        } else {
            arg0->unk5 = 1;
            arg0->unk80.bytes.unk80 &= 0xFD;
            ride_chaser_land_animation(arg0);
        }
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (0x68000 - arg0->y_vel.val < 0)
        arg0->y_vel.val = 0x68000;
    func_8003CCBC(arg0);
    if (arg0->unk7D != 0)
        arg0->unk8E = 1;
    func_8003CBCC(arg0);
}

void func_8003C08C(struct RideArmorObj* arg0)
{
    u8 value;

    switch (arg0->unk6) {
    case 0:
        if (arg0->unk8E != 0) {
            arg0->unk6 = 6;
            arg0->y_vel.val = 0;
            arg0->unk2C = 0;
        } else {
            arg0->unk6 = 1;
        }
        arg0->spawned_parts = 1;
        arg0->x_vel.val = 0x40000;
        arg0->unk28 = -0x1000;
        arg0->unk90.value = 0x1000;
        arg0->unk94.value = 0;
        arg0->unk80.bytes.unk80 |= 1;
        background_objects[arg0->bg_offset].unk47 = 8;
        func_80015D60(arg0, D_800F9100[arg0->unk80.bytes.unk82]);
        func_8003B458(arg0, D_800F910C[arg0->unk80.bytes.unk82]);
        func_8002B694(ANIMATED_OBJECT(arg0));
        ride_chaser_spawn_body(arg0);
        goto end;
    case 1:
        if (arg0->x_vel.val <= 0) {
            arg0->unk6 = 4;
            func_80015D60(arg0, D_800F9104[arg0->unk80.bytes.unk82]);
            func_8003B458(arg0, D_800F9110[arg0->unk80.bytes.unk82]);
            arg0->spawned_parts = 0;
            func_8001540C(5, 0, NULL);
        } else if (arg0->unk70 & 8) {
            func_8003C9A4(arg0);
            if (arg0->unk8C & 0x80) {
                arg0->y_vel.val = 0x68000;
                arg0->unk6 = 2;
                arg0->unk2C = 0x5000;
                arg0->unk28 = 0;
                arg0->unk80.bytes.unk80 |= 2;
            }
        } else {
            arg0->unk6 = 3;
            arg0->unk2C = 0x5000;
        }
        break;
    case 2:
        func_8003C584(arg0);
        goto end;
    case 3:
        if (arg0->unk70 & 8) {
            arg0->unk6 = 4;
            arg0->unk67 = 0;
            arg0->unk28 = 0;
            arg0->unk2C = 0;
            arg0->y_vel.val = 0;
            arg0->spawned_parts = 0;
            ride_chaser_land_animation(arg0);
        }
        func_8003C624(arg0);
        goto end;
    case 4:
        if (arg0->animation_step.fields.relative_step == 0)
            arg0->unk6 = 5;
        break;
    case 5:
        arg0->unk5 = 1;
        arg0->spawned_parts = 0;
        arg0->unk6 = 0;
        arg0->unk7D = 0;
        arg0->unk80.bytes.unk80 &= 0xFC;
        background_objects[arg0->bg_offset].unk47 = 6;
        func_80015D60(arg0, D_800F9108[arg0->unk80.bytes.unk82]);
        func_8003B458(arg0, D_800F9114[arg0->unk80.bytes.unk82]);
        func_8002B694(ANIMATED_OBJECT(arg0));
        goto end;
    case 6:
        if (arg0->unk70 & 8) {
            RIDE_U8(arg0, 0x99) = 1;
        } else {
            value = arg0->unk80.bytes.unk81;
            if (value >= 0x38 || (value < 0x20 && value != 0))
                RIDE_U8(arg0, 0x99) = 1;
        }
        if (arg0->x_vel.val <= 0) {
            arg0->unk6 = 3;
            arg0->unk2C = 0x5000;
            arg0->unk8E = 0;
            RIDE_U8(arg0, 0x99) = 0;
            func_8001540C(5, 0, NULL);
        } else if (RIDE_U8(arg0, 0x99) == 0) {
            if (arg0->unk8A & 4)
                arg0->y_pos.val -= 0x8000;
            else if (arg0->unk8A & 8)
                arg0->y_pos.val += 0x8000;
        }
        break;
    default:
        goto end;
    }
    func_8003C624(arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));
end:
    func_8003C6EC(arg0, arg0->spawned_parts != 0 ? 3 : 2);
}

void func_8003C6EC(struct RideArmorObj* arg0, u8 kind)
{
    struct WeaponObj* weapon;
    struct VisualObj* visual;

    if (!(arg0->unk8C & 0x30) || RIDE_U8(arg0, 0x89) != 0 || RIDE_U8(arg0, 0x98) >= 3)
        return;
    weapon = find_free_weapon_obj();
    if (weapon != NULL) {
        weapon->active = 0x41;
        weapon->id = 0x38;
        weapon->unk2 = kind;
        weapon->x_pos.i.hi = arg0->x_pos.i.hi;
        weapon->y_pos.i.hi = arg0->y_pos.i.hi;
        weapon->animation_table = (u32**)arg0->animation_table;
        weapon->unk40 = arg0->unk40;
        weapon->unk3C = arg0->unk3C;
        weapon->unk42 = ride_chaser_clut();
        weapon->owner = (struct PlayerObj*)arg0;
        weapon->unk16 = arg0->unk16;
        weapon->unk15 = arg0->unk15;
    }
    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 0xC;
        visual->unk2 = kind;
        visual->x_pos.i.hi = arg0->x_pos.i.hi;
        visual->y_pos.i.hi = arg0->y_pos.i.hi;
        visual->animation_table = (u32**)arg0->animation_table;
        visual->unk40 = arg0->unk40;
        visual->unk3C = arg0->unk3C;
        visual->unk42 = ride_chaser_clut();
        visual->unk50 = (struct PlayerObj*)arg0;
        visual->unk16 = arg0->unk16;
        visual->unk15 = arg0->unk15;
    }
    RIDE_U8(arg0, 0x89) = 4;
    RIDE_U8(arg0, 0x98) += 1;
    func_8001540C(5, 2, arg0);
}

void func_8003CA44(struct RideArmorObj* arg0)
{
    if (arg0->unk80.bytes.unk82 == arg0->unk80.bytes.unk83 || (arg0->unk80.bytes.unk80 & 2))
        return;
    switch (arg0->unk80.bytes.unk82) {
    case 0:
        func_80015D60(arg0, 2);
        func_8003B458(arg0, 0x45);
        break;
    case 1:
        func_80015D60(arg0, 1);
        func_8003B458(arg0, 0x43);
        break;
    case 2:
        func_80015D60(arg0, 0);
        func_8003B458(arg0, 0x41);
        break;
    }
}

static void ride_chaser_accelerate(struct RideArmorObj* arg0)
{
    func_8003D338(arg0);
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_8003CD38(struct RideArmorObj* arg0)
{
    u8 slope = func_8003CF24(arg0);
    s32 limit;

    if (slope == 0) {
        if (arg0->unk7C == 0) {
            limit = D_800F9070[arg0->unk7D];
            if (arg0->x_vel.val <= limit) {
                arg0->x_vel.val = limit;
                func_8003D39C(arg0);
            } else {
                func_8002B694(ANIMATED_OBJECT(arg0));
            }
        } else {
            limit = D_800F9078[arg0->unk7D];
            if (arg0->x_vel.val < limit)
                ride_chaser_accelerate(arg0);
            else
                func_8002B694(ANIMATED_OBJECT(arg0));
        }
    } else if (slope == 1) {
        if (arg0->unk7C != 0) {
            limit = D_800F9080[arg0->unk7D];
            if (arg0->x_vel.val < limit) {
                ride_chaser_accelerate(arg0);
            } else {
                arg0->x_vel.val = limit;
                func_8003D39C(arg0);
            }
        } else {
            limit = D_800F9088[arg0->unk7D];
            if (limit < arg0->x_vel.val)
                ride_chaser_accelerate(arg0);
            else
                func_8002B694(ANIMATED_OBJECT(arg0));
        }
    } else if (arg0->unk7C == 0) {
        func_8002B694(ANIMATED_OBJECT(arg0));
        limit = D_800F9090[arg0->unk7D];
        if (limit - arg0->x_vel.val >= 0)
            arg0->x_vel.val = limit;
    } else {
        ride_chaser_accelerate(arg0);
        limit = D_800F9098[arg0->unk7D];
        if (limit - arg0->x_vel.val < 0)
            arg0->x_vel.val = limit;
    }
}

u8 func_8003CF24(struct RideArmorObj* arg0)
{
    u8 tile = arg0->unk80.bytes.unk81;

    if (tile != 0 && tile < 9)
        return tile < 5 ? 0 : 1;
    if (tile != 0x10)
        return 2;
    return arg0->unk80.bytes.unk83;
}

void func_8003CF6C(struct RideArmorObj* arg0)
{
    const struct Unk_unk68* bounds = arg0->unk68;
    s32 x;

    if (arg0->unk15 == 0)
        x = arg0->x_pos.i.hi + bounds->unk0;
    else
        x = arg0->x_pos.i.hi - bounds->unk0;
    arg0->unk80.bytes.unk81 = func_8002D724((struct PlayerObj*)arg0, (s16)x,
        (s16)(arg0->y_pos.i.hi + bounds->unk1 + bounds->unk3 + 1));
}

void func_8003D01C(struct RideArmorObj* arg0)
{
    const struct Unk_unk68* bounds = arg0->unk68;
    s32 offset = (u16)arg0->x_pos.i.hi - (u16)background_objects[arg0->bg_offset].x_pos.i.hi;
    s16 edge;

    if (arg0->unk15 != 0)
        offset -= bounds->unk0;
    else
        offset += bounds->unk0;
    edge = offset - bounds->unk2;
    if (edge <= 0 && !(arg0->unk70 & 1)) {
        arg0->x_pos.i.hi -= edge;
    } else if (edge < -8) {
        g_Player.unk5C = -0x80;
        arg0->unk5C = -0x80;
    }
    edge = offset + bounds->unk2;
    if (edge >= 0x100)
        arg0->x_pos.i.hi -= (s16)(edge - 0x100);
}

extern u8 D_80108B70[4];
extern u16 D_80108B74[][2];
extern u8 D_80108B94[];
extern u8 D_80108B9C[];

void func_80098630(struct WeaponObj* arg0)
{
    s32 dx;

    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->unk54 = NULL;
    arg0->unk50 = D_80108B70;
    dx = D_80108B74[arg0->unk2][0];
    if (arg0->unk15 != 0)
        dx = -dx;
    arg0->x_pos.i.hi += dx;
    arg0->y_pos.i.hi += D_80108B74[arg0->unk2][1];
    func_8002B93C(MOVING_OBJECT(arg0), D_80108B94[arg0->unk2]);
    arg0->unk60 = 3;
    arg0->x_vel.val <<= 3;
    arg0->unk5C = 1;
    arg0->y_vel.val <<= 3;
    func_80015D60(arg0, D_80108B9C[arg0->unk2]);
}

extern union AnimationStep* D_8010014C[27];
extern struct Unk_unk68 D_800FFFE4;
extern struct Unk_unk68 D_800FFFE8;
extern struct Unk_unk68 D_800FFFEC[2];
extern struct Unk_unk68 D_800FFFF4;
extern struct Unk_unk68 D_80107878[];
extern u8 D_801001B8[8];
extern u8 D_801001C0[8];
extern void (*D_801001D0[7])(struct MainObj*);
void func_8006B514(struct MainObj*);
s32 func_8006B568(struct MainObj*);

void func_8006AF70(struct MainObj* arg0)
{
    struct ShotObj* shot;
    struct VisualObj* visual;

    arg0->ext.main_53.unk84 = 0;
    switch (arg0->unk2) {
    case 0:
    case 1:
    case 2:
        arg0->unk20 = 0x80000;
        arg0->unk5 = 1;
        break;
    case 3:
        arg0->unk20 = 0x54000;
        arg0->unk5 = 2;
        arg0->state++;
        break;
    default:
        arg0->unk20 = 0x54000;
        arg0->unk5 = 5;
        arg0->state++;
        break;
    }
    arg0->unk15 = arg0->unk2 == 4 ? 0 : 0x40;
    arg0->ext.main_53.unk80 = func_8002D724(PLAYER_OBJECT(arg0), arg0->x_pos.i.hi,
        (s16)(arg0->y_pos.i.hi + 0x20));
    arg0->animation_table = (const u8* const*)D_8010014C;
    arg0->unk68 = &D_800FFFE4;
    arg0->unk50 = &D_800FFFF4;
    arg0->unk7C = 0x3C;
    arg0->collision_data = D_80107878;
    arg0->unk16 = 5;
    arg0->unk61 = 0;
    arg0->unk62 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk5C = 6;
    arg0->unk60 = 5;
    arg0->unk67 = 0;
    arg0->bg_offset = g_Player.bg_offset;
    func_80015D60(arg0, 0);
    if (arg0->unk2 == 0) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x1C;
            shot->unk2 = 0;
            shot->unk7C = WEAPON_OBJECT(arg0);
        }
    }
    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 0x15;
        visual->unk50 = PLAYER_OBJECT(arg0);
    }
}

s32 func_8006B1C4(struct MainObj* arg0, u8 side)
{
    const struct Unk_unk68* bounds = arg0->unk68;
    s32 x;
    s32 y;
    u8 tile;

    if (arg0->unk15 == 0)
        x = arg0->x_pos.i.hi + bounds->unk0;
    else
        x = arg0->x_pos.i.hi - bounds->unk0;
    y = arg0->y_pos.i.hi + bounds->unk1 + bounds->unk3;
    y += side != 0 ? -0xF : 1;
    for (;;) {
        tile = func_8002D724(PLAYER_OBJECT(arg0), (s16)x, (s16)y);
        if (tile != 0x10)
            return tile;
        y -= 0x10;
    }
}

void func_8006B2A4(struct MainObj* arg0)
{
    struct Main53Ext* ext = &arg0->ext.main_53;

    ext->unk81 = func_8006B1C4(arg0, 0);
    arg0->unk67 = 0;
    if (ext->unk81 == ext->unk80) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        return;
    }
    switch (ext->unk81) {
    case 0:
        func_80015D60(arg0, 2);
        arg0->unk24 = 0x68000;
        arg0->unk2C = 0x5000;
        arg0->unk67 = 1;
        arg0->unk6++;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        func_80015D60(arg0, 2);
        break;
    case 5:
    case 6:
    case 7:
    case 8:
        func_80015D60(arg0, 1);
        break;
    case 0x38:
        func_80015D60(arg0, 0);
        break;
    }
    ext->unk80 = ext->unk81;
}

void func_8006B398(struct MainObj* arg0)
{
    struct Main53Ext* ext = &arg0->ext.main_53;
    u8 tile;
    s16 x;
    s16 y;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    tile = func_8006B1C4(arg0, 0);
    ext->unk81 = tile;
    if (arg0->unk7E != 0) {
        arg0->unk7E--;
        return;
    }
    if (tile == 0)
        return;
    if (ext->unk84 != 0)
        arg0->unk20 = arg0->x_pos.val < background_objects[arg0->bg_offset].x_pos.val + 0x400000
            ? 0x80000
            : 0x50000;
    else
        arg0->unk20 = arg0->unk2 == 4 ? 0x10000 : 0x60000;
    arg0->unk28 = 0;
    arg0->unk67 = 0;
    arg0->unk6 = 0;
    func_80015D60(arg0, 0);
    if (ext->unk81 == 0x24)
        return;
    x = arg0->x_pos.i.hi;
    y = arg0->y_pos.i.hi;
    if (arg0->unk15 != 0)
        func_800B10E4(2, (s16)(x - 0x18), (s16)(y + 9), (s16)(x + 0xA), (s16)(y + 0x19), 0x10);
    else
        func_800B10E4(2, (s16)(x + 0x18), (s16)(y + 9), (s16)(x - 0xA), (s16)(y + 0x19), 0x10);
}

void func_8006B5F8(struct MainObj* arg0)
{
    if (func_8006B568(arg0) != 0) {
        switch (arg0->unk2) {
        case 0:
            arg0->unk20 = 0x60000;
            arg0->unk5 = 3;
            arg0->unk7C = 0x28;
            break;
        case 1:
            func_80015D60(arg0, 2);
            arg0->unk20 = 0x90000;
            arg0->unk24 = 0x80000;
            arg0->unk2C = 0x5000;
            arg0->unk5 = 2;
            arg0->unk67 = 1;
            arg0->unk6 = 1;
            arg0->unk7E = 2;
            break;
        }
    }
    func_8002B318(BASE_OBJECT(arg0), 0x30, 0x20);
}

void func_8006B6B0(struct MainObj* arg0)
{
    u8 tile;
    s32 animation;

    arg0->ext.main_53.unk84 = 0;
    func_8006B514(arg0);
    if (arg0->unk7C != 0) {
        arg0->unk7C--;
        func_8002B318(BASE_OBJECT(arg0), 0x30, 0x20);
        return;
    }
    if (arg0->unk67 != 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x30, 0x20);
        return;
    }
    tile = func_8006B1C4(arg0, 0);
    arg0->ext.main_53.unk81 = tile;
    if (tile == 0)
        animation = 3;
    else if (tile < 5)
        animation = 5;
    else if (tile < 9)
        animation = 4;
    else
        animation = 3;
    func_80015D60(arg0, animation);
    arg0->unk5 = 4;
    arg0->unk20 = 0x80000;
    arg0->unk28 = 0;
    arg0->unk67 = 1;
    func_8002B318(BASE_OBJECT(arg0), 0x30, 0x20);
}

void func_8006B8F4(struct MainObj* arg0)
{
    struct Main53Ext* ext = &arg0->ext.main_53;
    u8 unk65;

    arg0->unk54 = &D_800FFFE8;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->unk65 = ext->unk82;
    if (func_8002DD04(arg0) < 0)
        goto destroyed;
    unk65 = arg0->unk65;
    arg0->unk54 = &D_800FFFEC;
    ext->unk82 = unk65;
    arg0->unk65 = ext->unk83;
    if (func_8002DD04(arg0) < 0)
        goto destroyed;
    ext->unk83 = arg0->unk65;
    D_801001D0[arg0->unk5](arg0);
    if ((u8)func_8006B1C4(arg0, 1) == 0x24) {
        if (ext->unk85 == 0) {
            arg0->x_pos.i.hi -= 8;
            arg0->y_pos.i.hi += 0x10;
            func_800C7B80(arg0, 4);
            ext->unk85 = 2;
            arg0->x_pos.i.hi += 8;
            arg0->y_pos.i.hi -= 0x10;
        } else {
            ext->unk85--;
        }
    } else {
        ext->unk85 = 0;
    }
    CollisionRelated(PLAYER_OBJECT(arg0));
    func_8002D9BC(arg0);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x80, 0x80) != 0) {
        arg0->unk5 = 0;
        arg0->state++;
    }
    return;

destroyed:
    arg0->unk5 = 0;
    arg0->state++;
    arg0->unk42 &= 0x7FFF;
    func_800C813C(8, D_801001B8, arg0);
    func_800C813C(7, D_801001C0, arg0);
    func_800AF808(BASE_OBJECT(arg0));
}

extern union AnimationStep* D_800FFA98[13];
extern u8 D_800FFAD0[4];
extern u8 D_800FFAD4[4];
extern s8 D_800FFACC[4];
extern u32 D_801076F8[];

void func_8006738C(struct MainObj* arg0)
{
    s32 resource;
    s32 clut_x;
    s32 clut_y;

    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    resource = func_8002938C(0x30);
    arg0->unk40 = D_801406A8[resource] >> 7;
    resource = func_8002938C(0x30);
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    clut_x = func_8002938C(0x30);
    clut_y = func_8002938C(0x30);
    arg0->unk42 = ((clut_x * 4 + 0x18) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
    arg0->animation_table = (const u8* const*)D_800FFA98;
    arg0->unk16 = 4;
    arg0->unk68 = (struct Unk_unk68*)D_800FFAD0;
    arg0->unk50 = D_800FFAD4;
    arg0->unk54 = D_800FFACC;
    arg0->collision_data = D_801076F8;
    arg0->unk67 = 0;
    arg0->unk61 = 0;
    arg0->unk5C = 5;
    arg0->unk60 = 3;
    arg0->state = 1;
    arg0->unk6 = 0;
    SP_CUR_MAIN_OBJ->ext.main_48.unk81 = get_random() & 3;
    if (arg0->unk2 & 0x80) {
        func_80015D60(arg0, 0);
        arg0->unk5 = 2;
        arg0->unk67 = 1;
    } else {
        arg0->unk15 = 0;
        func_80015D60(arg0, 0);
        arg0->unk67 = 0;
        arg0->unk5 = 3;
    }
    if ((arg0->unk2 & 0xF) == 1)
        arg0->state = 3;
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
        func_80015D60(arg0, animation);
    arg0->unk6++;
}

void func_800678F8(struct MainObj* arg0)
{
    if (--SP_CUR_MAIN_OBJ->ext.main_48.unk80 != 0)
        return;
    if (g_Player.x_pos.i.hi - arg0->x_pos.i.hi > 0)
        arg0->unk15 = 0x40;
    SP_CUR_MAIN_OBJ->ext.main_48.collision_result
        = func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
    main_48_face_toward(arg0, 1);
}

void func_80067DAC(struct MainObj* arg0)
{
    if (--SP_CUR_MAIN_OBJ->ext.main_48.unk80 != 0)
        return;
    main_48_face_toward(arg0, 0);
}

void func_800681C4(struct MainObj* arg0)
{
    struct Main48Ext* ext = &SP_CUR_MAIN_OBJ->ext.main_48;

    ext->unk88 = ext->collision_result & 0xFE;
    switch ((u32)((s8)ext->collision_result & 0xFE)) {
    case 0:
        ext->unk86 = 0x1E;
        ext->unk87 = 2;
        break;
    case 2:
    case 4:
    case 6:
        ext->unk86 = 0;
        ext->unk87 = 8;
        break;
    case 8:
        ext->unk86 = 6;
        ext->unk87 = 0xA;
        break;
    case 10:
    case 12:
    case 14:
        ext->unk86 = 8;
        ext->unk87 = 0x10;
        break;
    case 16:
        ext->unk86 = 0xE;
        ext->unk87 = 0x12;
        break;
    case 18:
    case 20:
    case 22:
        ext->unk86 = 0x10;
        ext->unk87 = 0x18;
        break;
    case 24:
        ext->unk86 = 0x16;
        ext->unk87 = 0x1A;
        break;
    case 26:
    case 28:
    case 30:
        ext->unk86 = 0x18;
        ext->unk87 = 0;
        break;
    }
}

void func_80068340(struct MainObj* arg0)
{
    struct Main48Ext* ext = &SP_CUR_MAIN_OBJ->ext.main_48;

    switch ((u32)(s8)(ext->unk82 - 1)) {
    case 0:
    case 4:
        ext->collision_result = ext->unk86;
        break;
    case 2:
    case 6:
        ext->collision_result = ext->unk87;
        break;
    case 1:
    case 3:
    case 5:
    case 7:
        ext->collision_result = ext->unk88;
        break;
    }
}

extern u8 D_80109170[8];
extern u8 D_80109178[4];
extern s8 D_8010917C[16];

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

void func_8009EEC8(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;
    s32 pair;

    arg0->unk68 = (struct Unk_unk68*)D_80109178;
    arg0->unk54 = D_80109170;
    arg0->unk50.data = D_80109170;
    arg0->unk58.animation_steps = D_80105FF0;
    arg0->on_screen = 1;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk16 = 1;
    arg0->state++;
    arg0->unk40 = owner->unk40;
    arg0->unk42 = owner->unk42 & 0x7FFF;
    arg0->animation_table = (u32**)owner->animation_table;
    arg0->unk3C = (void*)owner->sprite_frames;
    arg0->unk15 = owner->unk15;
    arg0->bg_offset = owner->bg_offset;
    arg0->unk60 = 3;
    arg0->unk5C = 1;
    arg0->x_vel.val <<= 1;
    arg0->y_vel.val <<= 1;
    pair = main_48_direction_pair(arg0->unk2, arg0->unk15);
    arg0->x_pos.i.hi += D_8010917C[pair * 2];
    arg0->y_pos.i.hi += D_8010917C[pair * 2 + 1];
    func_80015D60(arg0, 6);
}

extern s8 D_8010E93C[16];

void func_800CC4E0(struct MiscObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->ext.unk.unk50;
    s32 pair;

    arg0->on_screen = 1;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk16 = 0;
    arg0->unk40 = owner->unk40;
    arg0->unk42 = owner->unk42 & 0x7FFF;
    arg0->animation_table = (u32**)owner->animation_table;
    arg0->unk3C = (void*)owner->sprite_frames;
    arg0->unk15 = owner->unk15;
    arg0->bg_offset = owner->bg_offset;
    func_80015D60(arg0, 7);
    pair = main_48_direction_pair(arg0->unk2, arg0->unk15);
    arg0->x_pos.i.hi += D_8010E93C[pair * 2];
    arg0->y_pos.i.hi += D_8010E93C[pair * 2 + 1];
    arg0->state++;
}

extern union AnimationStep* D_800FC968[9];
extern struct Unk_unk68 D_80106C74[];
extern struct Unk_unk68 D_800FC844;
extern struct Unk_unk68 D_800FC848;
extern struct Unk_unk68 D_800FC84C;
extern struct Unk_unk68 D_800FC850;
extern struct Unk_unk68 D_800FC854;
extern struct Unk_unk68 D_800FC858;
extern struct Unk_unk68 D_800FC85C;
extern void (*D_800FC99C[3])();
extern u8 D_800FC98C[4];
extern union AnimationStep* D_800FD1B8[];

void func_800545EC(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    arg0->state++;
    arg0->animation_table = (const u8* const*)D_800FC968;
    arg0->unk16 = 6;
    arg0->collision_data = D_80106C74;
    arg0->unk15 = 0;
    arg0->unk68 = NULL;
    arg0->unk61 = 0;
    arg0->unk5C = 9;
    arg0->unk60 = 3;
    arg0->ext.main_20.unk80 = 9;
    arg0->ext.main_20.unk81 = 2;
    arg0->bg_offset = g_Player.bg_offset;
    if (arg0->unk2 != 0) {
        arg0->unk50 = &D_800FC844;
        arg0->unk54 = &D_800FC848;
    } else {
        arg0->unk50 = NULL;
        arg0->unk54 = &D_800FC84C;
    }
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk24 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk7C = 0;
    arg0->x_pos.i.hi = (arg0->x_pos.i.hi & ~0xF) + 8;
    arg0->y_pos.i.hi = (arg0->y_pos.i.hi & ~0xF) + 0x14;
    func_80015D60(arg0, 0);
    func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
}

void func_80054758(struct MainObj* arg0)
{
    s32 collision = func_8002DD04(arg0);
    s8 countdown;

    if (arg0->unk2 == 0 && arg0->ext.main_20.unk80 != arg0->unk5C) {
        countdown = arg0->ext.main_20.unk81;
        arg0->ext.main_20.unk81 = countdown - 1;
        if (countdown == 1) {
            func_800583B0(arg0, arg0->x_pos.i.hi, (s16)(arg0->y_pos.i.hi - 0x10), 5);
            arg0->unk5C = 1;
        } else if (countdown == 2) {
            func_800583B0(arg0, arg0->x_pos.i.hi, (s16)(arg0->y_pos.i.hi - 0x10), 0);
        }
        arg0->ext.main_20.unk80 = arg0->unk5C;
    }
    if (collision < 0) {
        arg0->unk5 = 0;
        arg0->state++;
        arg0->unk42 &= 0x7FFF;
        return;
    }
    D_800FC99C[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x80, 0x80) != 0) {
        func_8002B0C8(OBJECT_HEADER(arg0));
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
}

void func_800548B8(struct MainObj* arg0)
{
    struct WeaponObj* weapon;
    u8 flags = 0;
    u8 top;
    u8 bottom;

    if (arg0->unk2 == 0) {
        func_800583B0(arg0, arg0->x_pos.i.hi, (s16)(arg0->y_pos.i.hi - 0x10), 0xA);
        top = func_8002D724(PLAYER_OBJECT(arg0), arg0->x_pos.i.hi, (s16)(arg0->y_pos.i.hi - 0x30));
        bottom = func_8002D724(PLAYER_OBJECT(arg0), arg0->x_pos.i.hi, (s16)(arg0->y_pos.i.hi + 0x30));
        if (top >= 0x30) {
            if (top < 0x32 || top == 0x3C)
                func_800583B0(arg0, arg0->x_pos.i.hi, (s16)(arg0->y_pos.i.hi - 0x40), 0xA);
            else if (top == 0x38)
                flags = 1;
        }
        if (bottom >= 0x30) {
            if (bottom < 0x32 || bottom == 0x3C)
                func_800583B0(arg0, arg0->x_pos.i.hi, (s16)(arg0->y_pos.i.hi + 0x20), 0xA);
            else if (bottom == 0x38)
                flags += 2;
        }
    }
    switch (flags) {
    case 1:
        func_80015D60(arg0, 7);
        arg0->unk50 = &D_800FC850;
        break;
    case 2:
        func_80015D60(arg0, 6);
        arg0->unk50 = &D_800FC854;
        break;
    case 3:
        arg0->unk7C = 1;
        arg0->unk50 = &D_800FC858;
        break;
    default:
        func_80015D60(arg0, 8);
        arg0->unk50 = &D_800FC85C;
        break;
    }
    weapon = find_free_weapon_obj();
    if (weapon != NULL) {
        weapon->active = 1;
        weapon->id = 0x3A;
        weapon->owner = PLAYER_OBJECT(arg0);
        weapon->state = 0;
        weapon->unk5 = 0;
        weapon->unk6 = 0;
        weapon->unk2 = flags;
    }
    arg0->unk5++;
    func_800AF808(BASE_OBJECT(arg0));
    func_800C813C(4, D_800FC98C, arg0);
    if (arg0->unk2 == 0)
        func_800C842C(0xC, D_800FD1D0, arg0, 0x1A, D_800FD1B8);
}

extern u8 D_80108BB4[4];
extern u8 D_80108BB8[4];
extern u8 D_80108BBC[4];

void func_800989CC(struct WeaponObj* arg0)
{
    struct PlayerObj* owner = arg0->owner;

    arg0->unk68 = NULL;
    arg0->unk54 = NULL;
    arg0->state++;
    switch (arg0->unk2) {
    case 1:
        arg0->unk50 = D_80108BBC;
        break;
    case 2:
        arg0->unk50 = D_80108BB8;
        break;
    case 3:
        arg0->unk50 = NULL;
        break;
    default:
        arg0->unk50 = D_80108BB4;
        break;
    }
    arg0->unk5C = 1;
    arg0->unk60 = 3;
    arg0->x_pos.val = owner->x_pos.val;
    arg0->unk5 = 0xC;
    arg0->y_pos.val = owner->y_pos.val;
}

extern s8* D_800FEA24[7];
extern union AnimationStep** D_800FEA40[7];
extern struct Unk_unk68 D_800FEAA0;
extern u8 D_800FEA1C[8];
u8 func_80062338(struct MainObj*);

void func_80061DFC(struct MainObj* arg0)
{
    struct Main40Ext* ext = &arg0->ext.main_40;

    arg0->unk61 = 0;
    ext->unk81 = arg0->unk2 & 0xF;
    ext->unk80 = arg0->unk2 >> 4;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->unk16 = 6;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk54 = D_800FEA24[ext->unk80];
    arg0->unk5C = 0;
    arg0->unk60 = 0;
    arg0->unk50 = NULL;
    arg0->unk68 = NULL;
    arg0->animation_table = (const u8* const*)D_800FEA40[ext->unk80];
    if (ext->unk80 == 1) {
        func_80015D60(arg0, 0);
        arg0->unk5C = 3;
        arg0->unk60 = 2;
        arg0->unk68 = &D_800FEAA0;
        arg0->unk50 = D_800FEA24[ext->unk80];
    }
    arg0->collision_data = D_80108504;
    arg0->unk15 = 0;
    arg0->state++;
}

void func_80061F2C(struct MainObj* arg0)
{
    struct Main40Ext* ext = &arg0->ext.main_40;
    s32 collision;
    s32 dy;

    arg0->unk1C.val = arg0->y_pos.val;
    arg0->unk18.val = arg0->x_pos.val;
    if (ext->unk80 == 1) {
        func_8002D9BC(arg0);
        collision = func_8002DD04(arg0);
        if (collision >= 0) {
            if (collision > 0)
                arg0->unk42 |= 0x8000;
            else
                arg0->unk42 &= 0x7FFF;
            if (!func_80062338(arg0))
                goto check;
        }
        ext->timer = 0x30;
        ext->trigger_time = 0x2F;
        arg0->on_screen = 0;
        func_800C813C(7, D_800FEA1C, arg0);
        arg0->state++;
        return;
    }
    if (ext->unk80 != 0 && ext->unk80 < 7) {
        dy = D_800FEA5C[(ext->unk80 - 2) * 2 + 1] << 16;
        if (arg0->y_pos.val - dy - background_objects[arg0->bg_offset].y_pos.val > 0xA80000) {
            ext->timer = 0x10;
            ext->trigger_time = 8;
            arg0->state++;
        }
    }
check:
    if (func_8002B160(BASE_OBJECT(arg0)) != 0) {
        func_8002B0C8(OBJECT_HEADER(arg0));
        return;
    }
    if (ext->unk80 == 1)
        is_on_screen(BASE_OBJECT(arg0));
}

static const struct Unk_unk68* psx_null_relative_bounds(const struct Unk_unk68* bounds)
{
    static const struct Unk_unk68 zero;

    return bounds != NULL ? bounds : &zero;
}

u8 func_80062338(struct MainObj* arg0)
{
    const struct Unk_unk68* bounds = psx_null_relative_bounds(arg0->unk68);
    const struct Unk_unk68* player_bounds = psx_null_relative_bounds(g_Player.unk68);
    s16 edge = arg0->x_pos.i.hi + bounds->unk0;
    s16 player_edge = g_Player.x_pos.i.hi + player_bounds->unk0;
    s16 distance = edge - player_edge >= 0 ? (s16)(edge - player_edge) : (s16)(player_edge - edge);

    return distance <= bounds->unk2 + player_bounds->unk2;
}

extern u8 D_80109258[4];

void func_800A0170(struct ShotObj* arg0)
{
    struct WeaponObj* owner;
    s32 resource;
    s32 clut_x;
    s32 clut_y;

    arg0->state++;
    arg0->unk60 = 6;
    arg0->unk15 = 0;
    arg0->unk16 = 1;
    arg0->unk68 = NULL;
    arg0->unk58.data = NULL;
    arg0->unk61 = 0;
    arg0->unk5C = 1;
    arg0->animation_table = (u32**)D_800FC968;
    arg0->bg_offset = g_Player.bg_offset;
    clut_x = func_8002938C(0x14);
    clut_y = func_8002938C(0x14);
    arg0->unk42 = ((clut_x * 4 + 0x18) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
    resource = func_8002938C(0x14);
    arg0->unk40 = D_801406A8[resource] >> 7;
    resource = func_8002938C(0x14);
    owner = arg0->unk7C;
    arg0->unk16 = 1;
    arg0->unk54 = NULL;
    arg0->unk68 = NULL;
    arg0->unk58.data = NULL;
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->x_pos.val = owner->x_pos.val + (arg0->unk2 != 0 ? 0x300000 : 0x100000);
    arg0->unk50.data = D_80109258;
    arg0->y_pos.val = owner->y_pos.val + 0x80000;
    func_80015D60(arg0, 8);
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
}

void func_800BD080(struct EffectObj* arg0)
{
    struct MainObj* main;
    s32 x;
    s32 y;
    u32 i;

    if (--arg0->ext.unk_effect.unk14 != 0)
        return;
    x = background_objects[0].x_pos.u.hi + (u16)arg0->ext.effect_4.unk16;
    y = background_objects[0].y_pos.i.hi + (arg0->ext.unk_effect.unk15 != 0 ? 0x20 : 0x10);
    for (i = 0; i < 5; i++) {
        main = find_free_main_obj();
        if (main == NULL)
            continue;
        main->active = 0x21;
        main->id = 0x3B;
        main->unk2 = 0;
        main->x_pos.i.hi = x + (get_random() & 0xF);
        main->y_pos.i.hi = y + (get_random() & 0x1F);
        y += 0x20;
        main->unk7C = get_random() & 0xF;
    }
    arg0->ext.unk_effect.unk14 = 7;
    arg0->ext.unk_effect.unk15 ^= 1;
    if ((s16)arg0->ext.effect_4.unk16 < 0x70)
        arg0->ext.effect_4.unk16 += 3;
}

void func_800CE114(struct MiscObj* arg0)
{
    const u8* rows = (const u8*)arg0->ext.unk.unk50;

    arg0->unk40 = 0x1E00;
    arg0->animation_table = (u32**)D_8010ECD4;
    arg0->bg_offset = -1;
    arg0->unk42 = 0x7806;
    arg0->unk15 = 0;
    arg0->unk3C = WINDOW_ARCHIVE_DATA + ((s32*)WINDOW_ARCHIVE_DATA)[2];
    arg0->x_pos.i.hi += 8;
    arg0->y_pos.i.hi = rows[D_80141BDF[0] * 2 + 2] + 8;
    arg0->unk16 = 0x10;
    arg0->state++;
    arg0->ext.unk.unk54 = D_80141BDF[0];
    func_80015D60(arg0, 0);
    is_on_screen(BASE_OBJECT(arg0));
}

static int misc_32_cancelled(s8 mode)
{
    return (controller_state & 0x10) || ((controller_state & 0x800) && game_info.unk0 == mode);
}

void func_800CE1D4(struct MiscObj* arg0)
{
    const u8* rows = (const u8*)arg0->ext.unk.unk50;

    if (arg0->ext.unk.unk55 == 0) {
        if (arg0->unk2 == -1 || misc_32_cancelled(0xA))
            arg0->unk2 = -1;
        if (arg0->unk2 == -1 || misc_32_cancelled(8))
            arg0->unk2 = -1;
    }
    if (arg0->unk2 != -1 && (u8)arg0->ext.unk.unk54 != D_80141BDF[0]) {
        arg0->y_pos.i.hi = rows[D_80141BDF[0] * 2 + 2] + 8;
        arg0->ext.unk.unk54 = D_80141BDF[0];
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
}

extern union AnimationStep* D_800F9428[31];
extern union AnimationStep* D_800F965C[38];
extern struct Unk_unk68 D_800F9120;
extern struct Unk_unk68 D_800F9124;
extern struct Unk_unk68 D_800F9128;
extern void (*D_800F9150[])(struct RideArmorObj*);
extern void (*D_800F9188[])(struct RideArmorObj*);
void func_8003DC44(struct BaseObj*, s8);
void func_8003DC1C(struct PlayerObj*, s8);
void func_8003D638(struct VisualObj*, u8);
s32 func_8003DE08(struct MainObj*);
void func_8003DDDC(struct PlayerObj*);
void func_800401F8(struct PlayerObj*);
void func_800400C8(struct PlayerObj*);
void func_800402C4(struct PlayerObj*);
void func_8003FF9C(struct RideArmorObj*);
void func_8003DF9C(struct PlayerObj*);
s32 func_8003DC8C(struct RideArmorObj*);
s32 func_8003DC50(struct RideArmorObj*);
void func_8003DD14(struct MainObj*);
void func_8003DD2C(struct MainObj*);
void func_8003DD54(struct RideArmorObj*);
void func_8003DDA0(struct RideArmorObj*);
void func_8003D7A0(void);
s32 func_8003E048(struct PlayerObj*);
void func_8003D9E0(struct RideArmorObj*);
void func_8003DE84(struct RideArmorObj*);
void func_80040248(struct RideArmorObj*);

#define RIDE_ARMOR_STATE(object, state) func_8003DC44(BASE_OBJECT(object), (state))
#define RIDE_ARMOR_FLAGS(object) ((object)->unk94.bytes.unk97)

void func_8003D4C8(struct RideArmorObj* arg0)
{
    u8 resource;

    arg0->on_screen = 1;
    arg0->state = 1;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->bg_offset = 0;
    arg0->unk15 = 0;
    arg0->active |= 0x40;
    arg0->animation_table = (u32**)(arg0->unk2 != 0 ? D_800F965C : D_800F9428);
    resource = func_8002938C(0x86);
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->unk40 = D_801406A8[resource] >> 7;
    arg0->unk42 = SOME_COORDINATE_CONVERSION(resource);
    arg0->unk5C = 0x20;
    arg0->unk16 = 3;
    arg0->unk68 = &D_800F9124;
    arg0->unk60 = 0;
    arg0->unk61 = 0;
    arg0->unk67 = 0;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk54 = NULL;
    arg0->unk50 = NULL;
    arg0->unk58 = NULL;
    arg0->unk7D = 0;
    arg0->unk7E = 0;
    arg0->unk80.bytes.unk83 = 0;
    arg0->unk80.bytes.unk82 = 0;
    arg0->unk7C = 1;
    arg0->unk86 = 0;
    arg0->unk80.bytes.unk81 = 0;
    arg0->unk80.bytes.unk80 = 0;
    arg0->spawned_parts = 0;
    RIDE_U8(arg0, 0x8E) = 0;
    RIDE_U8(arg0, 0x8D) = 0;
    RIDE_U8(arg0, 0x93) = 0;
    RIDE_ARMOR_FLAGS(arg0) = 0;
    arg0->unkA6 = 0;
    RIDE_U8(arg0, 0x8C) = 0;
    arg0->pad87 = 0;
}

void func_8003D7E4(struct RideArmorObj* arg0, s32 kind, s32 variant)
{
    struct WeaponObj* weapon = find_free_weapon_obj();

    if (weapon == NULL)
        return;
    weapon->active = 0x41;
    weapon->id = variant + 0x3D;
    weapon->unk2 = kind;
    weapon->x_pos.i.hi = arg0->x_pos.i.hi;
    weapon->y_pos.i.hi = arg0->y_pos.i.hi;
    weapon->animation_table = arg0->animation_table;
    weapon->unk40 = arg0->unk40;
    weapon->unk3C = arg0->unk3C;
    weapon->unk42 = arg0->unk42 & 0x7FFF;
    weapon->owner = (struct PlayerObj*)arg0;
    weapon->unk16 = arg0->unk16;
    weapon->unk15 = arg0->unk15;
}

void func_8003D8A8(struct RideArmorObj* arg0, s32 kind, s32 variant)
{
    struct WeaponObj* weapon;
    u8 resource;

    if (arg0->unk86 >= 3)
        return;
    weapon = find_free_weapon_obj();
    if (weapon == NULL)
        return;
    weapon->active = 0x41;
    weapon->id = variant + 0x3B;
    weapon->unk2 = kind;
    weapon->x_pos.i.hi = arg0->x_pos.i.hi;
    weapon->y_pos.i.hi = arg0->y_pos.i.hi;
    weapon->animation_table = arg0->animation_table;
    weapon->unk40 = arg0->unk40;
    weapon->unk3C = arg0->unk3C;
    resource = func_8002938C(0x86);
    weapon->unk42 = SOME_COORDINATE_CONVERSION(resource);
    weapon->owner = (struct PlayerObj*)arg0;
    weapon->unk16 = arg0->unk16;
    weapon->unk15 = arg0->unk15;
    if ((u8)variant == 0)
        arg0->unk86++;
}

void func_8003D9E0(struct RideArmorObj* arg0)
{
    u16 mode;
    u8 parts;
    u32 i;

    if (RIDE_ARMOR_FLAGS(arg0) & 2)
        return;
    mode = RIDE_U16(arg0, 0x96) & 0xC000;
    if (mode == 0x8000)
        return;
    switch (RIDE_U8(arg0, 0x94)) {
    case 0:
        if (arg0->collision_flags & 0x30) {
            RIDE_U8(arg0, 0x94) = 1;
            RIDE_U8(arg0, 0x95) = 0x3C;
            arg0->unkA6 = arg0->collision_flags & 0x30;
        }
        return;
    case 1:
        if (!(arg0->collision_flags & arg0->unkA6)) {
            RIDE_U8(arg0, 0x94) = 0;
            arg0->unkA6 = 0;
            return;
        }
        if (--RIDE_U8(arg0, 0x95) != 0)
            return;
        RIDE_U8(arg0, 0x94) = 2;
        if (arg0->unk2 == 0 || mode != 0x4000)
            return;
        func_8003D6EC(ANIMATED_OBJECT(arg0), 0x10);
        func_8001540C(5, 8, NULL);
        return;
    case 2:
        if (arg0->collision_flags & arg0->unkA6)
            return;
        if (arg0->unk2 == 0 || mode != 0x4000) {
            RIDE_U8(arg0, 0x94) = 0;
            arg0->unkA6 = 0;
            func_80015930(5, 8);
            return;
        }
        switch ((u8)arg0->unk5) {
        case 3:
        case 6:
        case 9:
        case 0xA:
        case 0xB:
        case 0xD:
        case 0x10:
        case 0x11:
            RIDE_U8(arg0, 0x94) = 0;
            arg0->unkA6 = 0;
            func_80015930(5, 8);
            return;
        }
        parts = arg0->spawned_parts;
        for (i = 0; i < 3; i++) {
            if (!(parts & 1)) {
                func_8003D8A8(arg0, i, 1);
                arg0->spawned_parts |= 1 << i;
            }
            parts >>= 1;
        }
        arg0->unk7E = 0x10;
        func_8001540C(5, 6, NULL);
        RIDE_U8(arg0, 0x94) = 0;
        arg0->unkA6 = 0;
        return;
    }
}

s32 func_8003DCD8(struct RideArmorObj* arg0)
{
    if (!(arg0->unk8A & 0x30))
        return 0;
    if (arg0->unk2 == 0)
        return 1;
    return arg0->unk7E == 0;
}

void func_8003DE84(struct RideArmorObj* arg0)
{
    u16 direction;

    if (RIDE_U8(arg0, 0x8D) != 0 || (RIDE_ARMOR_FLAGS(arg0) & 2))
        return;
    if (RIDE_U8(arg0, 0x8E) == 0) {
        direction = arg0->unk8A & 3;
        if (direction == 0 || direction == 3)
            return;
        RIDE_U8(arg0, 0x8E) = 1;
        RIDE_U16(arg0, 0x9A) = direction;
        RIDE_U8(arg0, 0x8F) = 0xC;
        return;
    }
    if ((arg0->unk8A & RIDE_U16(arg0, 0x9A)) && !func_8003DE08((struct MainObj*)arg0)) {
        if (arg0->unk67 == 0) {
            RIDE_ARMOR_STATE(arg0, 7);
            RIDE_ARMOR_FLAGS(arg0) ^= 8;
            return;
        }
        if (arg0->unk7D == 0) {
            RIDE_ARMOR_STATE(arg0, 0xF);
            RIDE_ARMOR_FLAGS(arg0) ^= 8;
            return;
        }
    }
    if (--RIDE_U8(arg0, 0x8F) == 0)
        RIDE_U8(arg0, 0x8E) = 0;
}

void func_8003E0D0(struct RideArmorObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        arg0->unk68 = &D_800F9124;
        RIDE_U8(arg0, 0x8C) = 0;
        func_80015D60(arg0, 0x11);
        return;
    }
    if (!(arg0->input_flags & 8)) {
        RIDE_ARMOR_STATE(arg0, 0xC);
        return;
    }
    if (g_Player.unkC0 != 0 || engine_obj.unkF != 0)
        return;
    if (g_Player.unk2 != 0 && g_Player.unk8E != 0)
        return;
    if (g_Player.unk7A != 0 || g_Player.unkE0 != 0)
        return;
    if (RIDE_U16(arg0, 0x96) & 0x8200)
        return;
    if (!func_8002C160(COLLISION_OBJECT(&g_Player), COLLISION_OBJECT(arg0)))
        return;
    if (engine_obj.unkF != 0 || g_Player.unk5C <= 0 || g_Player.unkA4 != 0 || g_Player.unk79 != 0)
        return;
    RIDE_ARMOR_STATE(arg0, 0xA);
    func_80015D60(arg0, 0x12);
    RIDE_ARMOR_FLAGS(arg0) |= 0x40;
    g_Player.unkC5 = 1;
}

void func_8003E274(struct RideArmorObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        RIDE_U8(arg0, 0x94) = 0;
        arg0->unkA6 = 0;
        arg0->unk68 = &D_800F9120;
        func_80015D60(arg0, 0x12);
        func_8003DC1C((struct PlayerObj*)arg0, 0x39);
        func_8001540C(5, arg0->id != 0 ? 4 : 6, NULL);
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        if (RIDE_U8(arg0, 0x8C) == 0)
            arg0->unk61 = 0;
        RIDE_U8(arg0, 0x94) = 0;
        arg0->unkA6 = 0;
        RIDE_ARMOR_STATE(arg0, 1);
        arg0->unk54 = &D_800F9128;
        return;
    }
    if (arg0->animation_step.fields.event & 1) {
        func_8003D638((struct VisualObj*)arg0, 7);
        arg0->animation_step.fields.event = 0;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8003E488(struct RideArmorObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        arg0->unk98.packed = 0x160;
        func_80015D60(arg0, 1);
        func_8003DC1C((struct PlayerObj*)arg0, 0x2A);
        arg0->pad87 = 0;
    }
    if (RIDE_U8(arg0, 0x94) == 2) {
        RIDE_ARMOR_STATE(arg0, 0xD);
        return;
    }
    if (func_8003DC8C(arg0)) {
        RIDE_ARMOR_STATE(arg0, 0xB);
        return;
    }
    if (!(arg0->input_flags & 8)) {
        RIDE_ARMOR_STATE(arg0, 0xC);
        return;
    }
    if (!(RIDE_ARMOR_FLAGS(arg0) & 2)) {
        if (!func_8003DC50(arg0)) {
            RIDE_ARMOR_STATE(arg0, 1);
            return;
        }
        if (arg0->unk8A & 0x80) {
            RIDE_ARMOR_STATE(arg0, 4);
            return;
        }
        if (func_8003DCD8(arg0)) {
            RIDE_ARMOR_STATE(arg0, 3);
            return;
        }
        func_8003DD2C((struct MainObj*)arg0);
        func_8003DD14((struct MainObj*)arg0);
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_8001540C(5, (u8)arg0->animation_step.fields.event, NULL);
        arg0->animation_step.fields.event = 0;
    }
}

void func_8003E5F8(struct RideArmorObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        if (arg0->pad87 == 1) {
            func_8003D7E4(arg0, 2, 1);
            func_80015D60(arg0, 0xA);
            func_8003DC1C((struct PlayerObj*)arg0, 0x32);
            func_8001540C(5, 5, NULL);
        } else {
            func_8003D7E4(arg0, 0, 0);
            func_80015D60(arg0, 8);
            func_8003DC1C((struct PlayerObj*)arg0, 0x31);
            func_8001540C(5, 0, NULL);
        }
        arg0->unk80.bytes.unk81 = 0;
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        if (arg0->unk80.bytes.unk81 != 0) {
            RIDE_ARMOR_STATE(arg0, 3);
        } else {
            arg0->pad87 = 0;
            arg0->unk80.bytes.unk81 = 0;
            RIDE_ARMOR_STATE(arg0, 1);
        }
        return;
    }
    if ((arg0->animation_step.fields.event & 1) && func_8003DCD8(arg0)
        && arg0->unk80.bytes.unk81 == 0 && (u8)arg0->pad87 < 2) {
        arg0->pad87++;
        arg0->unk80.bytes.unk81 = 1;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8003E750(struct RideArmorObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->y_vel.val = 0x58000;
        arg0->unk6 = 1;
        arg0->unk2C = 0x4200;
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->unk67 = 1;
        if (arg0->unk2 == 0)
            func_8003D638((struct VisualObj*)arg0, 6);
        func_80015D60(arg0, 2);
        func_8003DC1C((struct PlayerObj*)arg0, 0x2B);
        arg0->pad87 = 0;
        func_8001540C(5, arg0->unk2 == 0 ? 4 : 3, NULL);
    }
    if (func_8003DCD8(arg0)) {
        RIDE_ARMOR_STATE(arg0, 6);
        return;
    }
    if (func_8003DC8C(arg0)) {
        RIDE_ARMOR_STATE(arg0, 0xB);
        return;
    }
    if (RIDE_ARMOR_FLAGS(arg0) & 2)
        return;
    arg0->x_vel.val = 0;
    func_8003DD54(arg0);
    if (!(arg0->input_flags & 4) && arg0->y_vel.val >= 0 && (arg0->collision_flags & 0x80)) {
        func_8002B694(ANIMATED_OBJECT(arg0));
        return;
    }
    RIDE_ARMOR_STATE(arg0, 0xC);
}

void func_8003E8A0(struct RideArmorObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        arg0->unk98.packed = 0x160;
        arg0->unk67 = 0;
        arg0->unk7D = 0;
        func_80015D60(arg0, 4);
        func_8003DC1C((struct PlayerObj*)arg0, 0x2D);
        arg0->input_flags |= 8;
        if (arg0->unk2 == 0) {
            func_8001540C(5, 1, NULL);
        } else {
            func_8001540C(5, 0, NULL);
            func_80015930(5, 5);
            func_8001540C(5, 0, NULL);
        }
    }
    if (func_8003DC8C(arg0)) {
        RIDE_ARMOR_STATE(arg0, 0xB);
        return;
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        RIDE_ARMOR_STATE(arg0, 1);
        return;
    }
    if (!(RIDE_ARMOR_FLAGS(arg0) & 2)) {
        if (!(arg0->input_flags & 8)) {
            RIDE_ARMOR_STATE(arg0, 0xC);
        } else if (func_8003DCD8(arg0)) {
            RIDE_ARMOR_STATE(arg0, 3);
        } else if (func_8003DC50(arg0)) {
            func_8003DD2C((struct MainObj*)arg0);
            func_8003DD14((struct MainObj*)arg0);
        }
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

static void ride_armor_air_attack(struct RideArmorObj* arg0, s32 check_follow_up)
{
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    func_8003DDA0(arg0);
    if (arg0->y_vel.val >= 0 && ((arg0->input_flags & 4) || !(arg0->collision_flags & 0x80)))
        arg0->y_vel.val = 0;
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = arg0->y_vel.val >= 0 ? 4 : 0xC;
        return;
    }
    if (arg0->y_vel.val < -0x5E000)
        arg0->y_vel.val = -0x5E000;
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (check_follow_up && arg0->animation_step.fields.event != 0 && func_8003DCD8(arg0)
        && arg0->unk86 < 3)
        RIDE_ARMOR_STATE(arg0, 6);
}

void func_8003EA08(struct RideArmorObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        func_8003D7E4(arg0, 3, 1);
        func_80015D60(arg0, 0xB);
        func_8003DC1C((struct PlayerObj*)arg0, 0x33);
        func_8001540C(5, 5, NULL);
    }
    if (arg0->input_flags & 8) {
        RIDE_ARMOR_STATE(arg0, 5);
        return;
    }
    if (!(RIDE_ARMOR_FLAGS(arg0) & 2))
        ride_armor_air_attack(arg0, 0);
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8003EB4C(struct RideArmorObj* arg0)
{
    s8 timer;

    func_8003D7A0();
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        arg0->unk98.packed = 0x420;
        arg0->x_vel.val = arg0->unk15 != 0 ? 0x42000 : -0x42000;
        RIDE_U8(arg0, 0x90) = 0x1E;
        func_80015D60(arg0, 5);
        func_8003DC1C((struct PlayerObj*)arg0, 0x2F);
        if (arg0->unk2 == 0) {
            func_8001540C(5, 3, NULL);
            func_8003D638((struct VisualObj*)arg0, 5);
        } else {
            func_8001540C(5, 2, NULL);
        }
    }
    if (func_8003DC8C(arg0)) {
        RIDE_ARMOR_STATE(arg0, 0xB);
        return;
    }
    if (!(RIDE_ARMOR_FLAGS(arg0) & 2)) {
        if (arg0->unk8A & 0x80) {
            RIDE_ARMOR_STATE(arg0, 4);
        } else if (func_8003DCD8(arg0)) {
            RIDE_ARMOR_STATE(arg0, 9);
        } else if (!(arg0->input_flags & 8)) {
            RIDE_ARMOR_STATE(arg0, 0xC);
        } else if ((arg0->input_flags & 3) || !func_8003E048((struct PlayerObj*)arg0)) {
            RIDE_ARMOR_STATE(arg0, 8);
            return;
        } else {
            func_8003DD14((struct MainObj*)arg0);
            timer = RIDE_S8(arg0, 0x90);
            RIDE_U8(arg0, 0x90) = timer - 1;
            if (timer < 0) {
                RIDE_ARMOR_STATE(arg0, 8);
                return;
            }
        }
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8003EEF8(struct RideArmorObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        arg0->unk61 = 1;
        arg0->unk68 = &D_800F9124;
        RIDE_U8(arg0, 0x8C) = 0;
        RIDE_U8(arg0, 0x94) = 0;
        arg0->unkA6 = 0;
        func_80015930(5, 8);
        if (!(RIDE_ARMOR_FLAGS(arg0) & 2)) {
            arg0->y_vel.val = 0x20000;
            arg0->x_vel.val = 0;
            arg0->unk28 = 0;
            arg0->unk2C = 0x4000;
        }
        if (RIDE_ARMOR_FLAGS(arg0) & 0x40) {
            if (!(RIDE_ARMOR_FLAGS(arg0) & 2)) {
                arg0->y_vel.val = 0;
                arg0->unk2C = 0;
            }
            g_Player.unkC5 = 0;
            RIDE_ARMOR_FLAGS(arg0) ^= 0x40;
            func_80035EA4(&g_Player);
        }
        if (!(arg0->input_flags & 8))
            RIDE_ARMOR_STATE(arg0, 0xC);
        else
            func_80015D60(arg0, 0x13);
        arg0->unk42 &= 0x7FFF;
    }
    if (arg0->input_flags & 8)
        arg0->y_vel.val = 0;
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk6 = 0;
        arg0->unk5 = 0;
        func_80015930(5, 8);
        RIDE_U8(arg0, 0x8C) = 0;
        RIDE_U8(arg0, 0x94) = 0;
        arg0->unkA6 = 0;
    }
    if (!(RIDE_ARMOR_FLAGS(arg0) & 2))
        func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8003F068(struct RideArmorObj* arg0)
{
    u8 flags;

    if (arg0->unk6 == 0) {
        arg0->unk2C = 0x4200;
        arg0->unk6 = 1;
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->y_vel.val = 0;
        RIDE_U8(arg0, 0x96) = 0x28;
        arg0->unk67 = 1;
        if (RIDE_ARMOR_FLAGS(arg0) & 0x40)
            func_8003DC1C((struct PlayerObj*)arg0, 0x2C);
        func_80015D60(arg0, 3);
    }
    if ((RIDE_ARMOR_FLAGS(arg0) & 0x40) && func_8003DC8C(arg0)) {
        RIDE_ARMOR_STATE(arg0, 0xB);
        return;
    }
    if (arg0->input_flags & 8) {
        if (RIDE_ARMOR_FLAGS(arg0) & 0x40) {
            RIDE_ARMOR_STATE(arg0, 5);
            return;
        }
        arg0->unk67 = 0;
        RIDE_ARMOR_STATE(arg0, 0xB);
        return;
    }
    flags = RIDE_ARMOR_FLAGS(arg0);
    if (flags & 2)
        return;
    if (flags & 0x40) {
        if (func_8003DCD8(arg0)) {
            RIDE_ARMOR_STATE(arg0, 6);
            return;
        }
        if (arg0->unk2 != 0 && arg0->unk7D == 0 && (arg0->unk8A & 0x80)) {
            RIDE_ARMOR_STATE(arg0, 0xE);
            return;
        }
        arg0->x_vel.val = 0;
        func_8003DD54(arg0);
        if (arg0->y_vel.val < -0x5E000)
            arg0->y_vel.val = -0x5E000;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
}

void func_8003F76C(struct RideArmorObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        if (arg0->collision_flags & 8) {
            func_80015D60(arg0, 9);
            func_8003DC1C((struct PlayerObj*)arg0, 0x33);
            func_8003D8A8(arg0, 1, 0);
        } else {
            func_8003D8A8(arg0, 0, 0);
        }
        func_8001540C(5, 7, NULL);
    }
    if (arg0->input_flags & 8) {
        RIDE_ARMOR_STATE(arg0, 5);
        return;
    }
    if (!(RIDE_ARMOR_FLAGS(arg0) & 2))
        ride_armor_air_attack(arg0, 1);
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8003F908(struct RideArmorObj* arg0)
{
    s8 timer;

    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        arg0->unk7D = 1;
        arg0->unk98.packed = 0x420;
        arg0->x_vel.val = arg0->unk15 != 0 ? 0x42000 : -0x42000;
        RIDE_U8(arg0, 0x90) = 0x1E;
        arg0->unk2C = 0;
        arg0->y_vel.val = 0;
        func_80015D60(arg0, 0xC);
        func_8003DC1C((struct PlayerObj*)arg0, 0x2F);
        func_8001540C(5, 2, NULL);
    }
    if (func_8003DC8C(arg0)) {
        RIDE_ARMOR_STATE(arg0, 0xB);
        return;
    }
    if (!(RIDE_ARMOR_FLAGS(arg0) & 2)) {
        if (func_8003DCD8(arg0)) {
            RIDE_ARMOR_STATE(arg0, 0x10);
        } else if ((arg0->input_flags & 3) || !func_8003E048((struct PlayerObj*)arg0)) {
            RIDE_ARMOR_STATE(arg0, 0xC);
            return;
        } else {
            func_8003DD14((struct MainObj*)arg0);
            timer = RIDE_S8(arg0, 0x90);
            RIDE_U8(arg0, 0x90) = timer - 1;
            if (timer < 0) {
                RIDE_ARMOR_STATE(arg0, 0xC);
                return;
            }
        }
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8003FA58(struct RideArmorObj* arg0)
{
    u8 timer;

    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        if (arg0->collision_flags & 8) {
            func_8003D8A8(arg0, 1, 0);
            func_80015D60(arg0, 0xA);
            func_8003DC1C((struct PlayerObj*)arg0, 0x37);
        } else {
            func_8003D8A8(arg0, 0, 0);
        }
        func_8001540C(5, 7, NULL);
    }
    timer = RIDE_U8(arg0, 0x90) - 1;
    RIDE_U8(arg0, 0x90) = timer;
    if (!(RIDE_ARMOR_FLAGS(arg0) & 2)) {
        if ((arg0->input_flags & 3) || (s8)timer < 0) {
            RIDE_ARMOR_STATE(arg0, 0xC);
        } else if (arg0->animation_step.fields.relative_step == 0) {
            func_8003DD14((struct MainObj*)arg0);
            arg0->unk5 = 0xF;
            arg0->unk6 = 1;
        } else {
            if (func_8003E048((struct PlayerObj*)arg0))
                func_8003DD14((struct MainObj*)arg0);
            if (func_8003DCD8(arg0) && arg0->unk86 < 3) {
                RIDE_ARMOR_STATE(arg0, 0x10);
                func_80015D60(arg0, (arg0->collision_flags & 8) ? 0xA : 0xC);
            }
        }
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8003FD08(struct RideArmorObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        arg0->unk7D = 1;
        arg0->unk98.packed = 0x160;
        if (arg0->collision_flags & 8) {
            func_8003D8A8(arg0, 1, 0);
            func_80015D60(arg0, 0xB);
            func_8003DC1C((struct PlayerObj*)arg0, 0x3D);
        } else {
            func_8003D8A8(arg0, 0, 0);
        }
        arg0->pad87 = 0;
        func_8001540C(5, 7, NULL);
    }
    if (func_8003DC8C(arg0)) {
        RIDE_ARMOR_STATE(arg0, 0xB);
        return;
    }
    if (arg0->input_flags & 8) {
        RIDE_ARMOR_STATE(arg0, 5);
        return;
    }
    if (!(RIDE_ARMOR_FLAGS(arg0) & 2)) {
        if (arg0->unk8A & 0x80) {
            RIDE_ARMOR_STATE(arg0, 0xC);
            return;
        }
        if (arg0->animation_step.fields.relative_step < 0) {
            RIDE_ARMOR_STATE(arg0, 0xE);
            return;
        }
        if (arg0->animation_step.fields.event != 0 && func_8003DCD8(arg0) && arg0->unk86 < 3) {
            arg0->unk5 = 0x11;
            if (arg0->collision_flags & 8) {
                func_8003D8A8(arg0, 1, 0);
                func_80015D60(arg0, 0xB);
                func_8003DC1C((struct PlayerObj*)arg0, 0x3D);
            } else {
                func_80015D60(arg0, 0xD);
                func_8003DC1C((struct PlayerObj*)arg0, 0x3C);
                func_8003D8A8(arg0, 0, 0);
            }
            return;
        }
        if (func_8003DC50(arg0)) {
            func_8003DD2C((struct MainObj*)arg0);
            func_8003DD14((struct MainObj*)arg0);
        }
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80040248(struct RideArmorObj* arg0)
{
    u8 count;

    if (!(RIDE_ARMOR_FLAGS(arg0) & 0x80))
        return;
    arg0->unk42 &= 0x7FFF;
    if (--RIDE_U8(arg0, 0x92) != 0)
        return;
    count = RIDE_U8(arg0, 0x91);
    RIDE_U8(arg0, 0x91) = count - 1;
    arg0->unk42 |= 0x8000;
    RIDE_U8(arg0, 0x92) = count;
    if ((u8)(count - 1) != 0)
        return;
    RIDE_U8(arg0, 0x8D) = 1;
    arg0->unk42 &= 0x7FFF;
}

void func_800403DC(struct RideArmorObj* arg0)
{
    u8 flags;

    arg0->on_screen = 0;
    if (func_8002B160(BASE_OBJECT(arg0)) != 0)
        return;
    if (arg0->unk5C < 0) {
        if (arg0->unk5C == -0x80) {
            RIDE_U8(arg0, 0x92) = 0x1E;
            RIDE_U8(arg0, 0x91) = 0x1E;
            RIDE_U8(arg0, 0x8C) = 0;
            RIDE_ARMOR_FLAGS(arg0) |= 0x80;
        }
        arg0->launch_speed = 0x400;
        RIDE_U8(arg0, 0x8C) = 0x79;
        func_8003D638((struct VisualObj*)arg0, 8);
        RIDE_U8(arg0, 0x93) = 1;
        arg0->unk85 = 1;
        RIDE_ARMOR_FLAGS(arg0) |= 2;
    }
    if (RIDE_U8(arg0, 0x8C) != 0 && --RIDE_U8(arg0, 0x8C) == 0 && (RIDE_ARMOR_FLAGS(arg0) & 1))
        g_Player.on_screen = 1;
    flags = RIDE_ARMOR_FLAGS(arg0);
    if ((flags & 0x41) == 0x41 || (engine_obj.unkF != 0 && (flags & 0x40))) {
        RIDE_ARMOR_FLAGS(arg0) = flags ^ 1;
        RIDE_ARMOR_STATE(arg0, 0xB);
    }
    func_8003DE84(arg0);
    func_8003DF9C((struct PlayerObj*)arg0);
    func_8003D9E0(arg0);
    if (RIDE_U8(arg0, 0x8D) == 0) {
        if (arg0->unk2 == 0) {
            D_800F9150[arg0->unk5](arg0);
        } else {
            if (arg0->unk7E != 0)
                arg0->unk7E--;
            D_800F9188[arg0->unk5](arg0);
        }
        func_8003FF9C(arg0);
        CollisionRelated((struct PlayerObj*)arg0);
        if (RIDE_ARMOR_FLAGS(arg0) & 0x40)
            func_8003DDDC((struct PlayerObj*)arg0);
        func_800401F8((struct PlayerObj*)arg0);
        func_80040248(arg0);
        func_8002B3C0(BASE_OBJECT(arg0));
    }
    func_800400C8((struct PlayerObj*)arg0);
    func_800402C4((struct PlayerObj*)arg0);
}

static u16 misc_31_palette(struct MiscObj* arg0)
{
    return arg0->unk2 == 3 && D_800F1D90.save.character == 0xFF ? 0x7804 : 0x7800;
}

void func_800CDE44(struct MiscObj* arg0)
{
    arg0->unk40 = 0x1F00;
    arg0->bg_offset = -1;
    arg0->unk3C = WINDOW_ARCHIVE_DATA + ((s32*)WINDOW_ARCHIVE_DATA)[0];
    arg0->unk15 = 0;
    arg0->unk42 = arg0->y_pos.i.hi == 0x10 ? 0x7802 : misc_31_palette(arg0);
    arg0->x_pos.i.hi = 0xA0;
    arg0->unk16 = 0x10;
    if ((u8)(arg0->unk2 - 0x56) < 2) {
        arg0->state += 2;
        arg0->ext.misc_31.animation = D_80171EA9;
        arg0->animation_step.fields.frame_index = D_80171EA9 != 0 ? 0x56 : 0x57;
    } else {
        arg0->state++;
        arg0->animation_step.fields.frame_index = arg0->unk2;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800CDF4C(struct MiscObj* arg0)
{
    if (arg0->y_pos.i.hi != 0x10) {
        if (arg0->ext.title_logo.palette_shift_value == 0) {
            if (arg0->unk2 == -1 || misc_32_cancelled(0xA))
                arg0->unk2 = -1;
            if (arg0->unk2 == -1 || misc_32_cancelled(8))
                arg0->unk2 = -1;
            if (arg0->unk2 == -1) {
                is_on_screen(BASE_OBJECT(arg0));
                return;
            }
        }
        if (arg0->unk7 == D_80141BDF[0])
            arg0->unk42 = 0x7803;
        else
            arg0->unk42 = misc_31_palette(arg0);
    }
    is_on_screen(BASE_OBJECT(arg0));
}

extern u8 D_80108BCC[4];
extern s16 D_80108BD0[2][2];

void func_80098AF8(struct WeaponObj* arg0)
{
    s32 dx;
    s32 direction;

    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 3;
    arg0->unk68 = NULL;
    arg0->unk54 = NULL;
    arg0->unk50 = D_80108BCC;
    dx = (u16)D_80108BD0[arg0->unk2][0];
    if (arg0->unk15 != 0)
        dx = -dx;
    arg0->x_pos.i.hi += dx;
    arg0->y_pos.i.hi += D_80108BD0[arg0->unk2][1];
    if (arg0->unk2 == 0)
        direction = arg0->unk15 == 0 ? 0x10 : 0;
    else
        direction = arg0->unk15 != 0 ? 0x1C : 0x14;
    func_8002B93C(MOVING_OBJECT(arg0), direction);
    arg0->unk5C = 1;
    arg0->unk60 = 3;
    arg0->x_vel.val <<= 3;
    arg0->y_vel.val <<= 3;
    func_80015D60(arg0, arg0->unk2 + 0x1F);
}

static s32 weapon_59_distance(s32 x0, s32 y0, s32 x1, s32 y1)
{
    s32 dx = x0 - x1;
    s32 dy = y0 - y1;

    if (dx < 0)
        dx = x1 - x0;
    if (dy < 0)
        dy = y1 - y0;
    return dx + dy;
}

void func_80098DA0(struct WeaponObj* arg0)
{
    struct MainObj* main;
    struct MainObj* target;
    s32 found = 0;

    for (main = main_objects; main < main_objects + COUNT(main_objects); main++) {
        if (main->active == 0 || main->on_screen == 0 || main->unk7A != 0)
            continue;
        target = arg0->ext.target;
        if (target == NULL
            || weapon_59_distance(arg0->x_pos.val, arg0->y_pos.val, main->x_pos.val, main->y_pos.val)
                < weapon_59_distance(arg0->x_pos.val, arg0->y_pos.val, target->x_pos.val, target->y_pos.val))
            arg0->ext.target = main;
        found = 1;
    }
    if (!found)
        arg0->ext.target = NULL;
}

void func_80098EA8(struct WeaponObj* arg0)
{
    struct VisualObj* visual = find_free_visual_obj();

    if (visual == NULL)
        return;
    visual->id = 0x16;
    visual->unk2 = 0;
    visual->active = arg0->active;
    visual->x_pos.i.hi = arg0->x_pos.i.hi;
    visual->y_pos.i.hi = arg0->y_pos.i.hi;
    visual->animation_table = arg0->animation_table;
    visual->unk40 = arg0->unk40;
    visual->unk3C = arg0->unk3C;
    visual->unk42 = arg0->unk42;
    visual->unk50 = (struct PlayerObj*)arg0;
    visual->unk16 = arg0->unk16;
    visual->unk15 = arg0->unk15;
}

extern u8 D_80108BF0[4];
extern s16 D_80108BF4[3][2];

void func_80098F88(struct WeaponObj* arg0)
{
    s32 dx;
    u8 direction;

    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->unk54 = NULL;
    arg0->unk50 = D_80108BF0;
    dx = (u16)D_80108BF4[arg0->unk2][0];
    if (arg0->unk15 != 0)
        dx = -dx;
    arg0->x_pos.i.hi += dx;
    arg0->y_pos.i.hi += D_80108BF4[arg0->unk2][1];
    switch (arg0->unk2) {
    case 0:
        direction = arg0->unk15 == 0 ? 0x10 : 0;
        break;
    case 1:
        direction = arg0->unk15 != 0 ? 0x1C : 0x14;
        break;
    default:
        direction = arg0->unk15 != 0 ? 4 : 0xC;
        break;
    }
    arg0->ext.weapon_60.direction = direction;
    func_8002B93C(MOVING_OBJECT(arg0), direction);
    arg0->unk5C = 1;
    arg0->unk60 = 3;
    arg0->unk88.half = 8;
    arg0->unk28.val = 0;
    arg0->unk2C = 0;
    *(s16*)arg0->pad8A = 1;
    arg0->ext.target = NULL;
    arg0->unk84.word = 0;
    arg0->x_vel.val *= 6;
    arg0->y_vel.val *= 6;
    func_80015D60(arg0, 0x21);
}

void func_80099118(struct WeaponObj* arg0)
{
    s32 target_direction;
    s16 trail;

    if ((s16)arg0->unk88.half != 0) {
        arg0->unk88.half--;
        arg0->unk84.word = 0;
    }
    if (!(D_80141BD8.unk0 & 1) && (s16)arg0->unk88.half == 0) {
        if (++arg0->unk84.word >= 0x1E0)
            arg0->unk88.half = 0x3C;
        func_80098DA0(arg0);
        if (arg0->ext.target != NULL) {
            target_direction = func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(arg0->ext.target));
            if (((arg0->ext.weapon_60.direction - (u8)target_direction) & 0x1F) >= 2) {
                if (((target_direction - arg0->ext.weapon_60.direction) & 0x1F) < 0x10)
                    arg0->ext.weapon_60.direction += 2;
                else
                    arg0->ext.weapon_60.direction -= 2;
                arg0->ext.weapon_60.direction &= 0x1F;
            }
            func_8002B93C(MOVING_OBJECT(arg0), arg0->ext.weapon_60.direction);
            arg0->x_vel.val *= 6;
            arg0->y_vel.val *= 6;
        }
    }
    trail = *(s16*)arg0->pad8A;
    if (trail == 0) {
        func_80098EA8(arg0);
        *(s16*)arg0->pad8A = 1;
    } else {
        *(s16*)arg0->pad8A = trail - 1;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) != 0 || arg0->unk98 != 0) {
        arg0->state = 2;
        arg0->on_screen = 0;
        arg0->unk50 = NULL;
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x10, 0x10);
}

extern u8 D_801091D0[8];
extern s32 D_801091D8[2];
extern s32 D_801091E0[4];
extern void (*D_80109200[])(struct ShotObj*);

void func_8009F674(struct ShotObj* arg0)
{
    struct MainObj* owner;
    s32 dx;

    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->unk60 = 5;
    arg0->unk58.animation_steps = D_80105FF0;
    arg0->unk50.data = D_801091D0;
    arg0->unk54 = D_801091D0;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk68 = NULL;
    arg0->state++;
    arg0->unk42 &= 0x7FFF;
    owner = (struct MainObj*)arg0->unk7C;
    dx = arg0->unk15 != 0 ? -0x1A : 0x1A;
    arg0->x_pos.i.hi = owner->x_pos.i.hi + dx;
    arg0->y_pos.i.hi = owner->y_pos.i.hi + (arg0->unk2 == 0 ? -0x23 : -0x10);
    func_80015D60(arg0, 7);
    arg0->unk8C.bytes[3] = 0x20;
    arg0->unk5 = 0;
    arg0->unk8C.bytes[1] = 0;
    arg0->unk8C.bytes[2] = 0;
    arg0->unk90.bytes[2] = 0;
    arg0->unk90.bytes[0] = 2;
    arg0->unk90.bytes[1] = 0;
    arg0->unk8C.bytes[0] = arg0->unk2 * 20 + 0x1E;
}

void func_8009F7C0(struct ShotObj* arg0)
{
    s32 speed;

    D_80109200[arg0->unk5](arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_8002D9BC(arg0);
    if (func_8002DD04((struct MainObj*)arg0) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        arg0->state++;
        return;
    }
    speed = arg0->x_vel.val;
    if (speed < 0)
        speed = -speed;
    if (speed > 0x40000)
        arg0->unk28 = 0;
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x40, 0x20) != 0) {
        arg0->state++;
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
}

void func_8009F89C(struct ShotObj* arg0)
{
    u8 timer = arg0->unk8C.bytes[3];
    u8 blink;

    if (timer == 0) {
        arg0->x_vel.val = D_801091D8[(arg0->unk15 & 0x40) ? 1 : 0];
        arg0->y_vel.val = D_801091E0[arg0->unk2 != 0 ? 1 : 0];
        arg0->unk42 &= 0x7FFF;
        arg0->unk5++;
        return;
    }
    arg0->unk8C.bytes[3] = timer - 1;
    blink = arg0->unk90.bytes[0];
    arg0->unk90.bytes[0] = blink - 1;
    if (blink == 0) {
        arg0->unk90.bytes[0] = 2;
        arg0->unk42 &= 0x7FFF;
    } else {
        arg0->unk42 |= 0x8000;
    }
}

void func_8009F9E0(struct ShotObj* arg0)
{
    struct MiscObj* misc;
    s32 distance;
    s32 y;
    u8 timer;

    if (arg0->unk8C.bytes[1] != 0) {
        arg0->unk8C.bytes[1]--;
        y = arg0->y_pos.i.hi + 8;
        distance = g_Player.y_pos.i.hi - y;
        if (distance < 0)
            distance = y - g_Player.y_pos.i.hi;
        if (distance < 3)
            arg0->y_vel.val = 0;
        else
            arg0->y_vel.val = g_Player.y_pos.i.hi - 8 < arg0->y_pos.i.hi ? 0x20000 : -0x20000;
    } else {
        arg0->y_vel.val = 0;
    }
    timer = arg0->unk8C.bytes[2];
    if (timer != 0) {
        arg0->unk8C.bytes[2] = timer - 1;
        return;
    }
    if (arg0->unk90.bytes[1] == 0)
        return;
    misc = find_free_misc_obj();
    if (misc != NULL) {
        misc->active = 0x21;
        misc->id = 0x17;
        misc->unk2 = 0;
        misc->unk15 = get_random() & 0x40;
        misc->ext.unk.unk54 = 0;
        misc->x_pos.i.hi = arg0->x_pos.i.hi + (arg0->unk15 != 0 ? -0x10 : 0x10);
        misc->unk7 = 1;
        misc->x_vel.val = 0;
        misc->y_vel.val = 0;
        misc->unk16 = 7;
        misc->y_pos.i.hi = arg0->y_pos.i.hi;
    }
    arg0->unk8C.bytes[2] = 1;
}

extern struct Unk_unk68 D_801077F8[];
extern union AnimationStep* D_800FFF2C[28];
extern struct Unk_unk68 D_800FFDD0;
extern struct Unk_unk68 D_800FFDD4;
extern struct Unk_unk68 D_800FFDD8;

void func_8006A55C(struct MainObj* arg0)
{
    arg0->unk5C = 9;
    arg0->unk60 = 3;
    arg0->unk61 = 0;
    arg0->collision_data = D_801077F8;
    arg0->animation_table = (const u8* const*)D_800FFF2C;
    arg0->unk16 = 6;
    arg0->unk68 = &D_800FFDD8;
    arg0->unk54 = &D_800FFDD0;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk50 = &D_800FFDD4;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    func_8006AE50(ANIMATED_OBJECT(arg0));
    arg0->unk7C = 0x5A;
    arg0->ext.main_52.unk80 = 0;
    arg0->ext.main_52.unk8C = 0;
    arg0->state = 1;
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void func_8006A83C(struct MainObj* arg0)
{
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7E != 0) {
        return;
    }
    if (arg0->ext.main_52.unk80 == 0) {
        func_80015D60(arg0, arg0->ext.main_52.unk88 + 2);
    } else {
        func_80015D60(arg0, arg0->ext.main_52.unk88 + 7);
    }
    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x1B;
        shot->unk2 = arg0->ext.main_52.unk88 + arg0->ext.main_52.unk80 * 5;
        shot->unk40 = arg0->unk40;
        shot->unk42 = arg0->unk42;
        shot->animation_table = (u32**)arg0->animation_table;
        shot->unk3C = (void*)arg0->sprite_frames;
        shot->bg_offset = arg0->bg_offset;
        shot->x_pos.val = arg0->x_pos.val;
        shot->y_pos.val = arg0->y_pos.val;
        shot->unk15 = arg0->unk15;
        func_8002B93C(MOVING_OBJECT(shot), arg0->ext.main_52.unk84);
        shot->state = 0;
    }
    if (--arg0->unk7C == 0) {
        arg0->unk7C = 0x1E;
        arg0->unk6 = 3;
        arg0->ext.main_52.unk8C = 0;
    } else {
        arg0->unk7E = 0x10;
    }
}

void func_8006AAB4(struct MainObj* arg0)
{
    struct Unk_unk68* bounds;
    s16 x;
    s16 y;
    s32 dy;

    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    bounds = arg0->unk68;
    y = arg0->y_pos.i.hi + bounds->unk1 + (u8)bounds->unk3 + 0x10;
    x = arg0->x_pos.i.hi + bounds->unk0;
    x = arg0->unk15 == 0 ? x - 0x10 : x + 0x10;
    if (func_8002D724(PLAYER_OBJECT(arg0), x, y) == 0) {
        func_80015D60(arg0, 1);
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        return;
    }
    if (arg0->unk15 == 0) {
        if (g_Player.x_pos.i.hi - arg0->x_pos.i.hi > 0x40) {
            arg0->unk15 = 0x40;
            arg0->unk20 = 0x1CCCC;
            goto countdown;
        }
        if (!(arg0->unk70 & 2)) {
            goto countdown;
        }
    } else {
        if (arg0->x_pos.i.hi - g_Player.x_pos.i.hi > 0x40) {
            arg0->unk15 = 0;
            arg0->unk20 = -0x1CCCC;
            goto countdown;
        }
        if (!(arg0->unk70 & 1)) {
            goto countdown;
        }
    }
    func_80015D60(arg0, 1);
    arg0->unk5 = 4;
    arg0->unk6 = 0;
countdown:
    if (--arg0->unk7C != 0) {
        return;
    }
    arg0->ext.main_52.unk8C = 1;
    dy = g_Player.y_pos.i.hi - arg0->y_pos.i.hi;
    if (dy < 0) {
        dy = -dy;
    }
    if (dy > 0x20 || (get_random() & 0xF) < 3) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        return;
    }
    func_80015D60(arg0, 1);
    arg0->unk5 = 4;
    arg0->unk6 = 0;
}

void func_8006AE80(struct MainObj* arg0)
{
    u8 angle;
    u8 value;

    arg0->y_pos.i.hi -= 0x10;
    arg0->ext.main_52.unk84 = func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
    arg0->y_pos.i.hi += 0x10;
    angle = arg0->ext.main_52.unk84;
    if (arg0->unk15 == 0) {
        if ((u8)(angle - 8) > 0x10) {
            return;
        }
        if (angle < 10) {
            value = 0;
        } else if (angle < 14) {
            value = 1;
        } else if (angle < 19) {
            value = 2;
        } else if (angle < 23) {
            value = 3;
        } else {
            value = 4;
        }
    } else {
        if (angle >= 0x20) {
            return;
        }
        if (angle < 3) {
            value = 2;
        } else if (angle < 7) {
            value = 1;
        } else if (angle < 9) {
            value = 0;
        } else if (angle < 24) {
            return;
        } else if (angle < 26) {
            value = 4;
        } else if (angle < 30) {
            value = 3;
        } else {
            value = 2;
        }
    }
    arg0->ext.main_52.unk88 = value;
}

extern u8 D_8010919C[4];
extern s8 D_801091A0[20];

void func_8009F27C(struct ShotObj* arg0)
{
    s32 index = arg0->unk2;

    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk58.collision_data = D_80106070;
    arg0->unk42 &= 0x7FFF;
    arg0->unk28 *= 2;
    arg0->unk2C *= 2;
    if (arg0->unk15 == 0)
        arg0->x_pos.i.hi += D_801091A0[index * 2];
    else
        arg0->x_pos.i.hi -= D_801091A0[index * 2];
    arg0->y_vel.val *= 2;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->x_vel.val *= 2;
    arg0->unk54 = D_8010919C;
    arg0->unk50.data = D_8010919C;
    arg0->unk5C = 1;
    arg0->unk60 = 3;
    arg0->y_pos.i.hi += D_801091A0[index * 2 + 1];
    func_80015D60(ANIMATED_OBJECT(arg0), 0xC);
}

extern void* D_8010244C[13];

void func_8007BFF4(struct MainObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk7A = 1;
    arg0->unk7C = 0x30;
    arg0->unk5C = 3;
    arg0->unk60 = 3;
    arg0->animation_table = (const u8* const*)D_8010244C;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->unk61 = 0;
    arg0->unk54 = NULL;
    arg0->unk50 = NULL;
    arg0->unk68 = NULL;
    arg0->collision_data = NULL;
    arg0->unk67 = 0;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk16 = 5;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->unk18.val = arg0->x_pos.val;
    func_80015D60(arg0, 0);
}

void func_8007C090(struct MainObj* arg0)
{
    struct ShotObj* shot = find_free_shot_obj();

    if (shot == NULL) {
        return;
    }
    shot->id = 0x28;
    shot->active = arg0->active;
    shot->unk2 = arg0->unk2;
    shot->x_pos.val = arg0->x_pos.val;
    shot->y_pos.val = arg0->y_pos.val;
    shot->animation_table = (u32**)arg0->animation_table;
    shot->unk40 = arg0->unk40;
    shot->unk3C = (void*)arg0->sprite_frames;
    shot->unk42 = arg0->unk42;
    shot->unk7C = (struct WeaponObj*)arg0;
    shot->unk16 = arg0->unk16;
    shot->unk15 = arg0->unk15;
    arg0->unk7 = 1;
}

void func_8007C144(struct MainObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x80, 0x80) != 0) {
        arg0->state = 2;
        return;
    }
    switch (arg0->unk5) {
    case 0:
        if (arg0->unk7C == 0) {
            arg0->unk5 = 1;
            func_80015D60(arg0, 0);
        } else {
            arg0->unk7C--;
        }
        break;
    case 1:
        if (arg0->animation_step.fields.relative_step != 0) {
            func_80015DC8(ANIMATED_OBJECT(arg0));
            break;
        }
        arg0->unk5 = 2;
        func_8001540C(2, 0x78, arg0);
        func_80015D60(arg0, 1);
        break;
    case 2:
        if (arg0->animation_step.fields.relative_step != 0) {
            func_80015DC8(ANIMATED_OBJECT(arg0));
            break;
        }
        arg0->unk5 = 3;
        func_8001540C(2, 0x79, arg0);
        func_8007C090(arg0);
        break;
    case 3:
        if (arg0->unk7 == 0) {
            arg0->unk5 = 4;
            func_80015D60(arg0, 5);
        }
        break;
    case 4:
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->unk7C = 0x80;
            arg0->unk5 = 0;
        }
        func_80015DC8(ANIMATED_OBJECT(arg0));
        break;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x80, 0x80);
}

extern s16 D_80109898[4];
extern u8 D_801098A0[8];
extern u8 D_801098A8[16];
extern void (*D_801098C4[3])(struct ShotObj*);

void func_800A5540(struct ShotObj* arg0)
{
    s32 x_offset;
    s32 y_offset;

    if (arg0->unk7C->active == 0 || arg0->unk7C->id != 0x3F) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_801098C4[arg0->unk5](arg0);
    func_8002D9BC(MAIN_OBJECT(arg0));
    func_8002C808(PLAYER_OBJECT(arg0));
    if (arg0->unk8A != 0) {
        if (!(D_80141BD8.unk0 & 3)) {
            func_800AF878(BASE_OBJECT(arg0), 1, 0x60, 0x60);
            func_800AF878(BASE_OBJECT(arg0), 1, 0x30, 0x30);
            x_offset = get_random() & 0x30;
            y_offset = get_random() & 0x30;
            func_800C833C(7, D_801098A0, (struct MiscObj*)arg0, x_offset, y_offset);
        }
        if (--arg0->unk8A == 0) {
            func_800DABE4(0, D_80109898[arg0->unk2], 0x150);
            func_800C813C(0xE, D_801098A8, arg0);
        }
    }
    func_8002B318(BASE_OBJECT(arg0), 0x80, 0x80);
}

extern void* D_8010D964[11];
extern u8 D_8010D9B8[4];

void func_800C71C0(struct ItemObj* arg0)
{
    s32 resource;
    s32 row;
    struct MiscObj* misc;

    arg0->active = 0x41;
    arg0->unk16 = 6;
    arg0->unk15 = 0;
    arg0->unk40 = D_801406A8[func_8002938C(0x88)] >> 7;
    resource = func_8002938C(0x88);
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    resource = func_8002938C(0x88);
    row = func_8002938C(0x88);
    arg0->unk42 = ((resource * 4 + 0x18) % 16) | ((((row + 6) / 4) + 0x1E0) << 6);
    arg0->animation_table = (const u8* const*)D_8010D964;
    arg0->unk67 = 0;
    arg0->unk75 = 0;
    arg0->unk68 = (struct Unk_unk68*)D_8010D9B8;
    if (arg0->unk2 & 0x10) {
        resource = func_8002938C(0x88);
        row = func_8002938C(0x88);
        arg0->unk42 = ((resource * 4 + 0x1A) % 16) | ((((row + 6) / 4) + 0x1E0) << 6);
        func_80015D60(ANIMATED_OBJECT(arg0), 6);
        arg0->state = 1;
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        arg0->unk2 &= 0xF;
        return;
    }
    switch (engine_obj.character_state.bytes[6 + arg0->unk2]) {
    case 0:
        func_80015D60(ANIMATED_OBJECT(arg0), 1);
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 0x33;
            misc->unk2 = 0;
            misc->x_pos.val = arg0->x_pos.val;
            misc->y_pos.val = arg0->y_pos.val;
            misc->ext.misc_51.source = MAIN_OBJECT(arg0);
            arg0->unk7C.misc = misc;
        }
        arg0->state = 1;
        break;
    case 1:
        func_80015D60(ANIMATED_OBJECT(arg0), 10);
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 0x33;
            misc->unk2 = 0x30;
            misc->x_pos.val = arg0->x_pos.val;
            misc->y_pos.val = arg0->y_pos.val;
            misc->ext.misc_51.source = MAIN_OBJECT(arg0);
            arg0->unk7C.misc = misc;
        }
        arg0->state = 2;
        break;
    case 2:
        func_80015D60(ANIMATED_OBJECT(arg0), 6);
        arg0->state = 3;
        break;
    default:
        arg0->unk6 = 0;
        return;
    }
    arg0->unk5 = 0;
    arg0->unk6 = 0;
}

s8 func_800C7970(struct ItemObj* self, struct PlayerObj* player)
{
    struct Unk_unk68* other = player->unk68;
    struct Unk_unk68* box;
    u16 self_y;
    u16 other_y;
    s16 distance;

    if (other == NULL)
        return 0;
    box = self->unk68;
    if ((s16)(player->x_pos.i.hi - other->unk2) < (s16)(self->x_pos.i.hi - (box->unk2 - 0x10)))
        return 0;
    if ((s16)(self->x_pos.i.hi + box->unk2 - 0x10) < (s16)(player->x_pos.i.hi + other->unk2))
        return 0;
    self_y = self->y_pos.i.hi + box->unk1;
    other_y = player->y_pos.i.hi + other->unk1;
    distance = (s16)self_y - (s16)other_y >= 0 ? (s16)(self_y - other_y) : (s16)(other_y - self_y);
    return box->unk3 + other->unk3 >= distance;
}

void func_800D2094(struct MiscObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk16 = 1;
        func_80015D60(arg0, 7);
        arg0->ext.misc_51.unk54 = 0x78;
        arg0->unk6++;
    } else if (--arg0->ext.misc_51.unk54 != 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    } else {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

extern void* cyber_peacock_animations[38];
extern struct Unk_unk68 D_8010294C;
extern struct Unk_unk68 D_80107CFC[];

void func_8007C30C(struct MainObj* arg0)
{
    arg0->unk7C = 0x80;
    arg0->unk60 = 5;
    arg0->animation_table = (const u8* const*)cyber_peacock_animations;
    arg0->unk54 = &D_8010294C;
    arg0->unk50 = &D_80102948;
    arg0->collision_data = D_80107CFC;
    arg0->state = 0;
    arg0->unk5 = 1;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->on_screen = 0;
    arg0->unk2 = 0;
    arg0->unk5C = 0;
    arg0->unk61 = 0;
    arg0->ext.main_64.saved_health = 0;
    arg0->ext.main_64.flash_timer = 0;
    arg0->ext.main_64.force_laser = 0;
    arg0->ext.main_64.hit_count = 0;
    arg0->unk68 = NULL;
    arg0->unk67 = 0;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk16 = 3;
    arg0->ext.main_64.shot_count = 0;
    arg0->ext.main_64.unk8A = 0;
    arg0->ext.main_64.skip_attack = 1;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    engine_obj.character_state.bytes[7] = 0;
    if (engine_obj.stage == 6) {
        arg0->ext.main_64.arena_x = 0x3E0;
        arg0->ext.main_64.arena_y = 0x900;
    } else {
        arg0->ext.main_64.arena_x = 0x410;
        arg0->ext.main_64.arena_y = 0x600;
    }
}

extern union AnimationStep* web_spider_animations[40];
extern struct Unk_unk68 D_800FF5A8;
extern struct Unk_unk68 D_800FF5AC;

void func_80063334(struct MainObj* arg0)
{
    if (arg0->ext.main_43.effect->active != 0)
        return;
    arg0->unk5 = 2;
    arg0->unk54 = &D_800FF5AC;
    arg0->unk50 = &D_800FF5A8;
    arg0->unk68 = NULL;
    arg0->collision_data = D_801075F4;
    arg0->bg_offset = g_Player.bg_offset;
    if (engine_obj.stage != 0xC) {
        arg0->unk40 = (D_801406A8[0] >> 7) + 0xB0;
    } else {
        arg0->unk40 = (D_801406A8[0] >> 7) + 0x160;
        arg0->unk42 = 0x7888;
        arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[4];
    }
    arg0->animation_table = (const u8* const*)web_spider_animations;
    arg0->unk16 = 4;
    arg0->unk60 = 6;
    arg0->unk61 = -0x80;
    arg0->unk63 = 2;
    arg0->unk7C = 7;
    arg0->unk5C = 0;
    arg0->unk62 = 0;
    arg0->ext.main_43.flash_timer = 0;
    arg0->ext.main_43.shot = NULL;
    arg0->ext.main_43.hurt_collision = 0;
    arg0->ext.main_43.big_web_done = 0;
    engine_obj.enable_boss = 0;
    engine_obj.unk25 = 1;
    engine_obj.boss_ptr = arg0;
}

extern u8 D_800FF724[16];

static u8 main43_column(s16 index)
{
    static const u8 following_pointer_low_byte = 0x6C;

    return index < 16 ? D_800FF724[index] : following_pointer_low_byte;
}

void func_8006346C(struct MainObj* arg0)
{
    u8 column;

    switch (arg0->unk6) {
    case 0:
        column = main43_column(arg0->unk7C);
        arg0->unk7C++;
        arg0->unk7E = 0x10;
        arg0->unk6 = 1;
        arg0->x_pos.i.hi = web_spider_arena_x + 0x30 + (column << 5);
        func_800CAB10((struct MiscObj*)arg0, 2);
        break;
    case 1:
        if (--arg0->unk7E == 0) {
            if (arg0->unk7C >= 0x11) {
                arg0->unk5 = 3;
                arg0->unk6 = 0;
                arg0->unk7C = 0;
                arg0->x_pos.i.hi = web_spider_arena_x + 0xF0;
            } else {
                arg0->unk6 = 0;
            }
        }
        break;
    case 2:
        arg0->unk7E = 0x14;
        arg0->unk6 = 3;
        arg0->x_pos.i.hi = web_spider_arena_x + 0x30 + (arg0->unk7C << 5);
        arg0->unk7C++;
        func_800CAB10((struct MiscObj*)arg0, 2);
        break;
    case 3:
        if (--arg0->unk7E == 0) {
            if (arg0->unk7C >= 7) {
                arg0->unk5 = 3;
                arg0->unk6 = 0;
                arg0->unk7C = 0;
            } else {
                arg0->unk6 = 2;
            }
        }
        break;
    }
}

extern void (*web_spider_step_funcs[7])();
void web_spider_check_big_web(struct MainObj* arg0);

void func_8006398C(struct MainObj* arg0)
{
    s32 result;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    web_spider_check_big_web(arg0);
    ((void (*)(struct MainObj*))web_spider_step_funcs[arg0->unk5])(arg0);
    result = -1;
    if (arg0->unk5C > 0)
        result = func_8002DD04(arg0);
    if (arg0->ext.main_43.flash_timer != 0) {
        if ((arg0->ext.main_43.flash_timer & 1) == 0)
            arg0->unk42 |= 0x8000;
        else
            arg0->unk42 &= 0x7FFF;
        if (--arg0->ext.main_43.flash_timer == 0) {
            arg0->collision_data = D_801075F4;
            arg0->ext.main_43.hurt_collision = 0;
        }
    } else if (result < 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->unk42 &= 0x7FFF;
        g_Player.unk7A = 1;
    } else if (result != 0 && result != 0x7F) {
        arg0->collision_data = D_801060F0;
        arg0->ext.main_43.flash_timer = 0x40;
        web_spider_spawn_web_piece((struct VisualObj*)arg0, 0);
        arg0->ext.main_43.hurt_collision = 1;
    }
    func_8002D9BC(arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

void func_80063B20(struct MainObj* arg0)
{
    s32 threshold;

    switch (arg0->unk7) {
    case 0:
        arg0->unk7 = 1;
        arg0->unk7C = g_Player.unkBA != 0 ? 0x10 : 0x40;
        if (g_Player.unkBA == 0) {
            if ((get_random() & 7) < 5)
                arg0->ext.main_43.unk94 = ((g_Player.x_pos.i.hi - (s16)web_spider_arena_x) / 40 + 4) & 7;
            else
                arg0->ext.main_43.unk94 = get_random() & 7;
        } else {
            arg0->ext.main_43.unk94 = (g_Player.x_pos.i.hi - (s16)web_spider_arena_x) / 40;
        }
        arg0->unk2C = 0x8000;
        arg0->unk24 = 0;
        arg0->x_pos.i.hi = web_spider_arena_x + 0x30 + (arg0->ext.main_43.unk94 << 5);
        func_800CA9EC((struct MiscObj*)arg0, 8);
        func_80015D60(arg0, 0);
        break;
    case 1:
        if (arg0->unk7C != 0) {
            arg0->unk7C--;
            break;
        }
        if (arg0->unk24 <= -0x80000) {
            arg0->unk24 = -0x80000;
            arg0->unk2C = 0;
        }
        threshold = 0x80;
        if (g_Player.unkBA == 0 && (get_random() & 3) == 0)
            threshold = 0x50;
        if (arg0->y_pos.i.hi - background_objects[arg0->bg_offset].y_pos.i.hi >= threshold) {
            arg0->unk7 = 2;
            arg0->unk7C = 0xA;
            arg0->unk24 = 0x10000;
            arg0->unk2C = 0;
            func_80015D60(arg0, 0x20);
        }
        func_8002B694(ANIMATED_OBJECT(arg0));
        break;
    case 2:
        func_8002B694(ANIMATED_OBJECT(arg0));
        if (--arg0->unk7C == 0) {
            arg0->unk24 = 0;
            arg0->unk2C = 0;
        }
        if (arg0->unk7C == 0xF)
            arg0->unk24 = -0x10000;
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->unk6 = 1;
            arg0->unk7 = 0;
            arg0->unk7C = 0xA;
            func_80015D60(arg0, 0x21);
        }
        func_80015DC8(ANIMATED_OBJECT(arg0));
        break;
    }
}

void func_80063DD8(struct MainObj* arg0)
{
    switch (arg0->unk7) {
    case 0:
        if (arg0->unk7C != 0) {
            arg0->unk7C--;
            break;
        }
        if ((get_random() & 0xF) != 0 && g_Player.unkBA == 0) {
            arg0->unk5 = 3;
            arg0->unk6 = 0;
            arg0->unk7 = 0;
            arg0->unk15 = arg0->x_pos.i.hi - g_Player.x_pos.i.hi >= 0 ? 0 : 0x40;
            break;
        }
        arg0->unk24 = 0x38000;
        arg0->unk2C = 0;
        arg0->unk7 = 1;
        func_80015D60(arg0, 0x1F);
        func_8001540C(2, 0x70, arg0);
        break;
    case 1:
        if (arg0->on_screen == 0) {
            arg0->unk7 = 2;
            arg0->unk7C = 8;
            if (arg0->ext.main_43.hurt_collision != 0) {
                arg0->collision_data = D_801075F4;
                arg0->ext.main_43.hurt_collision = 0;
            }
        }
        if (arg0->animation_step.fields.event != 0) {
            arg0->animation_step.fields.event = 0;
            func_8001540C(2, 0x70, arg0);
        }
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_8002B694(ANIMATED_OBJECT(arg0));
        break;
    case 2:
        if (--arg0->unk7C == 0) {
            arg0->unk6 = 0;
            arg0->unk7 = 0;
        }
        break;
    }
}

extern RECT* web_spider_swing_paths[6];
extern u16 web_spider_arena_y;
s32 func_8002B810(s32 arg0, s32 arg1);

void func_80065168(struct MainObj* arg0, s16 x, s16 y)
{
    s32 dx = arg0->x_pos.val - (x << 16);
    s32 dy = arg0->y_pos.val - (y << 16);
    u8 direction = func_8002B810(dx, dy);

    if ((arg0->ext.main_43.move_direction ^ direction) & 0x10) {
        arg0->x_pos.i.lo = 0;
        arg0->y_pos.i.lo = 0;
    } else {
        arg0->x_pos.val -= dx / arg0->unk7C;
        arg0->y_pos.val -= dy / arg0->unk7C;
    }
    arg0->ext.main_43.move_direction = direction;
}

void func_80064154(struct MainObj* arg0)
{
    const u16* point;
    s16 dx;
    s16 dy;

    if (arg0->ext.main_43.attack_cooldown == 0) {
        arg0->ext.main_43.unk94 = 0;
        if (g_Player.unkBA != 0) {
            arg0->ext.main_43.unk94 = 1;
            arg0->unk5 = 5;
            arg0->unk6 = 0;
            arg0->unk7 = 0;
            return;
        }
        dx = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
        dy = arg0->y_pos.i.hi - g_Player.y_pos.i.hi;
        if ((dx < 0 ? -dx : dx) >= 0x40 && (dy < 0 ? -dy : dy) >= 0x50) {
            arg0->unk5 = 5;
            arg0->unk6 = 0;
            arg0->unk7 = 0;
            return;
        }
    } else {
        arg0->ext.main_43.attack_cooldown--;
    }
    point = (const u16*)web_spider_swing_paths[arg0->ext.main_43.animation_set] + arg0->ext.main_43.animation_index * 2;
    func_80065168(arg0, (s16)(point[0] + web_spider_arena_x + 0x10), (s16)(point[1] + web_spider_arena_y));
    if (--arg0->unk7C == 0) {
        arg0->ext.main_43.animation_index++;
        if (arg0->ext.main_43.animation_length < arg0->ext.main_43.animation_index) {
            arg0->unk6 = 2;
            arg0->ext.main_43.animation_index = 0;
            arg0->unk7C = 0x20;
            web_spider_set_move_timer(arg0);
        } else {
            web_spider_set_move_timer(arg0);
            web_spider_set_swing_animation(arg0);
        }
    }
    if (arg0->animation_step.fields.event != 0) {
        arg0->animation_step.fields.event = 0;
        func_8001540C(2, 0x70, arg0);
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_800643B0(struct MainObj* arg0)
{
    struct MainObj* child;
    u32 i;

    switch (arg0->unk6) {
    case 0:
        arg0->unk6 = 1;
        func_80015D60(arg0, 0xB);
        break;
    case 1:
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->unk6 = 2;
            func_80015D60(arg0, 0xC);
            break;
        }
        if (arg0->animation_step.fields.event == 0)
            break;
        for (i = 0; i < 4; i++) {
            child = find_free_main_obj();
            if (child == NULL)
                continue;
            child->active = 0x41;
            child->id = 0x2B;
            child->unk2 = i + 1;
            child->x_pos.val = arg0->x_pos.val;
            child->y_pos.val = arg0->y_pos.val;
            child->y_pos.i.hi -= 0x18;
            child->animation_table = arg0->animation_table;
            child->unk40 = arg0->unk40;
            child->sprite_frames = arg0->sprite_frames;
            child->unk42 = arg0->unk42 & 0x7FFF;
            child->unk16 = arg0->unk16;
            child->ext.main_43.effect = (struct EffectObj*)arg0;
            child->unk15 = arg0->unk15;
        }
        arg0->animation_step.fields.event = 0;
        func_8001540C(2, 0x71, arg0);
        break;
    case 2:
        if (arg0->animation_step.fields.relative_step != 0)
            break;
        arg0->unk5 = 4;
        arg0->unk6 = 1;
        arg0->unk7 = 0;
        func_80015D60(arg0, arg0->ext.main_43.animation_id);
        web_spider_set_attack_cooldown(arg0);
        if (++arg0->ext.main_43.attack_count >= 3)
            arg0->ext.main_43.attack_count = 0;
        break;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_800646EC(struct MainObj* arg0)
{
    switch (arg0->unk7) {
    case 0:
        arg0->unk7 = 1;
        arg0->unk7C = 0xC0;
        arg0->ext.main_43.attack_count = 0;
        arg0->unk2C = 0x8000;
        arg0->ext.main_43.attack_cooldown = 0;
        arg0->x_pos.i.lo = 0;
        arg0->unk24 = 0;
        arg0->ext.main_43.flash_timer = 0;
        arg0->collision_data = D_801060F0;
        arg0->x_pos.i.hi = web_spider_arena_x + 0xB0;
        func_800CA9EC((struct MiscObj*)arg0, 8);
        func_80015D60(arg0, 0);
        break;
    case 1:
        if (arg0->unk7C != 0) {
            arg0->unk7C--;
            break;
        }
        if (arg0->unk24 <= -0x80000) {
            arg0->unk24 = -0x80000;
            arg0->unk2C = 0;
        }
        if (arg0->y_pos.i.hi - background_objects[arg0->bg_offset].y_pos.i.hi >= 0x58) {
            arg0->unk7 = 2;
            arg0->unk7C = 0x1E;
            func_80015D60(arg0, 0x20);
            arg0->unk24 = 0x10000;
            arg0->unk2C = 0;
        }
        func_8002B694(ANIMATED_OBJECT(arg0));
        break;
    case 2:
        func_8002B694(ANIMATED_OBJECT(arg0));
        if (--arg0->unk7C == 0) {
            arg0->unk24 = 0;
            arg0->unk2C = 0;
        }
        if (arg0->unk7C == 0xF)
            arg0->unk24 = -0x10000;
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->unk6 = 1;
            arg0->unk7 = 0;
            arg0->unk7C = 0x14;
            func_80015D60(arg0, 0x21);
        }
        func_80015DC8(ANIMATED_OBJECT(arg0));
        break;
    }
}

extern struct FixedPointPosition spiderling_velocities[8];
extern struct Unk_unk68 D_800FF5B4;
extern struct Unk_unk68 D_800FF5B8;
extern struct Unk_unk68 D_800FF5BC;

void func_80065574(struct MainObj* arg0)
{
    const s32* velocity = (const s32*)&spiderling_velocities[((arg0->unk2 - 1) & 3) * 2];

    arg0->unk5 = 2;
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk63 = 1;
    arg0->unk60 = 4;
    arg0->unk6 = 0;
    arg0->unk7C = 0;
    arg0->unk5C = 3;
    arg0->unk61 = 0;
    arg0->unk62 = 0;
    arg0->unk67 = 0;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->unk20 = velocity[0];
    arg0->unk28 = velocity[1];
    arg0->unk24 = velocity[2];
    arg0->unk2C = velocity[3];
    arg0->unk54 = &D_800FF5B8;
    arg0->unk50 = &D_800FF5B4;
    arg0->unk68 = &D_800FF5BC;
    arg0->unk16 = 3;
    arg0->unk70 = 0;
    arg0->collision_data = D_801075F4;
    func_80015D60(arg0, 0x1B);
}

void func_800CACF0(struct MiscObj* arg0)
{
    if (arg0->unk5 == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_8002B694(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.event != 0) {
            arg0->animation_step.fields.event = 0;
            arg0->x_vel.val = -arg0->x_vel.val;
        }
        if (arg0->y_pos.i.hi >= (engine_obj.stage == 0xC ? 0x6D0 : 0x5D0)) {
            arg0->unk5 = 1;
            arg0->y_vel.val = 0;
            arg0->unk2C = 0;
            arg0->ext.misc_16.timer = 0x14;
        }
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    if (--arg0->ext.misc_16.timer == 0) {
        arg0->state = 2;
        return;
    }
    arg0->on_screen = 0;
    if (arg0->ext.misc_16.timer & 1)
        is_on_screen(BASE_OBJECT(arg0));
}

extern void (*D_801090B8[3])(struct ShotObj*);

void func_8009DE04(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;
    s32 hit = 0;

    arg0->x_pos.val = owner->x_pos.val + arg0->unk84.value;
    arg0->y_pos.val = owner->y_pos.val;
    arg0->y_pos.i.hi += arg0->timer;
    if (owner->ext.main_43.flash_timer != 0)
        arg0->unk61 = 1;
    if (owner->state == 2) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    D_801090B8[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    if (owner->ext.main_43.hurt_collision == 0 && owner->ext.main_43.big_web_done == 0)
        hit = func_8002DD04((struct MainObj*)arg0);
    if (arg0->unk61 != 0) {
        arg0->unk61--;
    } else if (hit != 0) {
        arg0->unk5 = 1;
        func_80015D60(arg0, 0x14);
        owner->unk5 = 1;
        owner->unk6 = 0;
        arg0->unk61 = 0x1E;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

MMX4_STATIC_ASSERT(bar_obj_size, sizeof(struct BarObj) == 0x34);
MMX4_STATIC_ASSERT(bar_obj_unk28_offset, MMX4_OFFSET_OF(struct BarObj, unk28) == 0x28);

#define BAR_BYTES(obj) ((u8*)(obj))

extern u8 D_800F48EC[8];
extern u8 D_8013B818[0x10];
void func_800170B0(void);

void func_8002FD70(struct BarObj* arg0)
{
    u8* bytes = BAR_BYTES(arg0);
    u32 i;

    if (D_80141BDC[0] != 0) {
        func_80023D68();
        return;
    }
    func_800170B0();
    func_800129A4(8);
    arg0->unk5 = 2;
    arg0->unk14 = 0;
    if (g_Player.unk2 == 0) {
        bytes[0x16] = 1;
        bytes[0x17] = (g_Player.unkA7 & 2) ? 1 : 0;
        for (i = 2; i < 10; i++)
            bytes[0x16 + i] = ((u8)g_Player.unkB9 >> (i - 2)) & 1;
    } else {
        for (i = 0; i < 8; i++)
            bytes[0x16 + D_800F48EC[i]] = ((u8)g_Player.unkB9 >> i) & 1;
        bytes[0x1F] = 0;
        bytes[0x20] = 0;
    }
    if (engine_obj.unk5A & 0x3000) {
        if (engine_obj.unk5A & 0x1000) {
            bytes[0x20] = 1;
            engine_obj.unk5C[0] |= 0x80;
        }
        if (engine_obj.unk5A & 0x2000) {
            bytes[0x21] = 1;
            engine_obj.unk5C[1] |= 0x80;
        }
    } else {
        bytes[0x20] = 0;
        bytes[0x21] = 0;
    }
    bytes[0x22] = (engine_obj.unk5A & 0x4000) ? 1 : 0;
    if (engine_obj.stage != 0)
        bytes[0x23] = ((u8)engine_obj.palette_flags >> (engine_obj.stage - 1)) & 1;
    bytes[0x24] = 1;
    if (g_Player.unk2 != 0 || (engine_obj.stage == 5 && engine_obj.checkpoint == 0) || g_Player.unkC5 < 0) {
        if (g_Player.unk2 == 0)
            arg0->unk2 = 1;
        for (i = 10; i < 15; i++) {
            if (bytes[0x16 + i] != 0) {
                arg0->unk14 = i;
                break;
            }
        }
    } else {
        arg0->unk2 = 0;
        if (g_Player.unk93 != 0)
            arg0->unk14 = g_Player.unk93 + 1;
    }
    bytes[0x25] = (engine_obj.unk5A & 0x8000) ? 1 : 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk30 = 0;
    D_8013B818[0] = g_Player.unk93;
}

void func_800301BC(struct BarObj* arg0)
{
    u8* bytes = BAR_BYTES(arg0);
    s32 original = (u8)arg0->unk14;
    s32 wrapped = 0;
    s32 target;
    s32 cursor;
    s32 count;

    switch (controller_state) {
    case 0x40:
        if ((u8)original < 10) {
            if ((s8)original < 2)
                g_Player.unk93 = 0;
            else
                g_Player.unk93 = original - 1;
        }
        func_8001540C(0, 0x22, 0);
        goto done;
    case 0x800:
        arg0->state = 2;
        arg0->unk5 = 0;
        goto done;
    case 0x1000:
        cursor = original;
        for (;;) {
            cursor -= 2;
            if ((s8)cursor < 0)
                cursor = (u8)arg0->unk14;
            if (arg0->unk14 == (s8)cursor || (s8)cursor == 0)
                goto store;
            if (bytes[0x16 + (s8)cursor] != 0)
                goto store;
        }
    case 0x4000:
        cursor = original;
        for (;;) {
            cursor += 2;
            if ((s8)cursor >= 10) {
                cursor = 9;
                for (count = 0; count < 5; count++) {
                    cursor++;
                    if (bytes[0x16 + (s8)cursor] != 0) {
                        arg0->unk5 = (s8)cursor < 0xD ? 1 : 2;
                        goto store;
                    }
                }
                goto store;
            }
            if (arg0->unk14 == (s8)cursor)
                goto store;
            if (bytes[0x16 + (s8)cursor] != 0)
                goto store;
        }
    case 0x2000:
        target = original + 1;
        cursor = target;
        if ((target & 1) == 0)
            goto done;
        original = target;
        if (bytes[0x16 + (s8)target] != 0) {
            original = target - 1;
            goto store;
        }
        for (;;) {
            if (wrapped == 0) {
                cursor += 2;
                if ((s8)cursor >= 0xB) {
                    cursor -= 2;
                    wrapped = 1;
                }
            } else {
                cursor -= 2;
            }
            if ((s8)cursor == (s8)target)
                goto unchanged;
            if (bytes[0x16 + (s8)cursor] != 0)
                goto store;
        }
    case 0x8000:
        target = original - 1;
        cursor = target;
        if (target & 1)
            goto done;
        original = target;
        if (bytes[0x16 + (s8)target] != 0) {
            original = target + 1;
            goto store;
        }
        for (;;) {
            if (wrapped == 0) {
                cursor -= 2;
                if ((s8)cursor < 0) {
                    cursor += 2;
                    wrapped = 1;
                }
            } else {
                cursor += 2;
            }
            if ((s8)cursor == (s8)target)
                goto unchanged;
            if (bytes[0x16 + (s8)cursor] != 0)
                goto store;
        }
    default:
        goto done;
    }
unchanged:
    original = (u8)arg0->unk14;
    cursor = original;
store:
    arg0->unk14 = cursor;
done:
    if (arg0->unk14 != (s8)original)
        func_8001540C(0, 0xC, 0);
}

void func_800304E4(struct BarObj* arg0)
{
    u8* bytes = BAR_BYTES(arg0);
    s32 original = (u8)arg0->unk14;
    s32 cursor;

    switch (controller_state) {
    case 0x800:
        arg0->state = 2;
        arg0->unk5 = 0;
        break;
    case 0x40:
        arg0->unk28 = 0;
        arg0->unk2C = 0;
        switch (arg0->unk14) {
        case 10:
            arg0->unk5 = 3;
            if ((engine_obj.unk5C[0] & 0x7F) == 0x20)
                arg0->unk28 = 1;
            break;
        case 11:
            arg0->unk5 = 3;
            if ((engine_obj.unk5C[1] & 0x7F) == 0x20)
                arg0->unk28 = 1;
            break;
        case 12:
            arg0->unk5 = 4;
            if ((engine_obj.unk5C[2] & 0x7F) == 0x20)
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

    if (controller_state & 0x800) {
        arg0->state = 2;
        arg0->unk5 = 0;
        goto done;
    }
    switch (controller_state) {
    case 0x40:
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
    s8 second = engine_obj.unk5C[1];

    if (second >= 0)
        return;
    engine_obj.unk5C[0] = second;
    engine_obj.unk5C[1] = second & 0x80;
}

void func_80030A2C(struct BarObj* arg0)
{
    s32 frame = D_80141BD8.unk0;
    u32 tank;
    u8 energy;
    u8 health;
    u8 player_health;

    if (frame & 1)
        return;
    tank = arg0->unk14 != 10;
    if (arg0->unk28 != 0) {
        energy = engine_obj.unk5C[tank] & 0x7F;
        if (energy != 0) {
            engine_obj.unk5C[tank] = (energy - 1) | 0x80;
            health = (g_Player.unk5C & 0x7F) + 1;
            if (engine_obj.unk46 < (s8)health)
                health = engine_obj.unk46;
            g_Player.unk5C = health;
            if ((D_80141BD8.unk0 & 3) == 0)
                func_8001540C(0, 0x17, 0);
            return;
        }
        if (g_Player.unk5C != engine_obj.unk46) {
            health = (g_Player.unk5C & 0x7F) + 1;
            if (engine_obj.unk46 < (s8)health)
                health = engine_obj.unk46;
            g_Player.unk5C = health;
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
    energy = engine_obj.unk5C[tank] & 0x7F;
    if (energy == 0) {
        arg0->unk5 = 1;
        if (tank == 0)
            bar_merge_sub_tanks();
        return;
    }
    engine_obj.unk5C[tank] = (energy - 1) | 0x80;
    player_health = g_Player.unk5C;
    health = (player_health & 0x7F) + 1;
    if (engine_obj.unk46 < (s8)health)
        health = engine_obj.unk46;
    g_Player.unk5C = health | (player_health & 0x80);
    if ((D_80141BD8.unk0 & 3) == 0)
        func_8001540C(0, 0x17, 0);
}

void func_80030C54(struct BarObj* arg0)
{
    u32 i;
    s32 refilled = 0;
    u8 energy;

    if (D_80141BD8.unk0 & 1)
        return;
    if (arg0->unk2C != 0) {
        for (i = 0; i < 9; i++) {
            if (g_Player.charge_levels[i] < 0x30) {
                g_Player.charge_levels[i]++;
                refilled = 1;
            } else {
                g_Player.charge_levels[i] = 0x30;
            }
        }
        if (refilled == 0) {
            energy = engine_obj.unk5C[2] & 0x7F;
            if (energy != 0) {
                engine_obj.unk5C[2] = energy - 1;
            } else {
                arg0->unk5 = 1;
                arg0->unk2C = 0;
            }
            return;
        }
    } else {
        if ((engine_obj.unk5C[2] & 0x7F) == 0) {
            arg0->unk5 = 1;
            return;
        }
        for (i = 0; i < 9; i++) {
            if (g_Player.charge_levels[i] < 0x30 && (s8)(g_Player.charge_levels[i] + 1) < 0x30) {
                g_Player.charge_levels[i]++;
                refilled = 1;
            } else {
                g_Player.charge_levels[i] = 0x30;
            }
        }
        if (refilled == 0) {
            arg0->unk5 = 1;
            return;
        }
    }
    energy = engine_obj.unk5C[2] & 0x7F;
    engine_obj.unk5C[2] = energy != 0 ? energy - 1 : energy;
    if ((D_80141BD8.unk0 & 3) == 0)
        func_8001540C(0, 0x17, 0);
}

void func_80030DF8(struct BarObj* arg0)
{
    switch (arg0->unk6) {
    case 0:
        func_800129F0(8);
        arg0->unk6++;
        break;
    case 1:
        if (D_80141BDC[0] == 0)
            arg0->unk6++;
        break;
    case 2:
        func_8002A41C((struct GameInfo*)arg0);
        return;
    case 3:
        func_800129A4(8);
        arg0->unk6++;
        break;
    case 4:
        if (D_80141BDC[0] == 0) {
            arg0->unk5 = 2;
            arg0->unk6 = 0;
            return;
        }
        break;
    default:
        return;
    }
    func_80023D90();
}

void func_80030EC8(struct BarObj* arg0)
{
    switch (arg0->unk6) {
    case 0:
        func_800129F0(8);
        arg0->unk6++;
        break;
    case 1:
        if (D_80141BDC[0] == 0)
            arg0->unk6++;
        break;
    case 2:
        func_80021104((struct EngineObj*)arg0);
        return;
    case 3:
        func_800129A4(8);
        arg0->unk6++;
        break;
    case 4:
        if (D_80141BDC[0] == 0) {
            arg0->unk6 = 0;
            arg0->unk5 = arg0->unk28;
            return;
        }
        break;
    default:
        return;
    }
    func_80023D90();
}

void func_800385EC(void);

void func_80031064(struct BarObj* arg0)
{
    if (arg0->unk30 == 0) {
        if (g_Player.unk2 == 0) {
            func_800385EC();
            if ((s8)D_8013B818[0] != g_Player.unk93) {
                func_800384DC(&g_Player);
                g_Player.unkA6 = 0;
            }
            func_80037104(&g_Player);
            if ((s8)D_8013B818[0] != g_Player.unk93)
                func_800371E4(&g_Player);
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

void func_80017E84(void)
{
    u32 buffer;
    u32 i;
    u32 j;

    for (buffer = 0; buffer < 2; buffer++) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 8; j++) {
                D_8013E1E8[buffer][i][j] = NULL;
                D_8013BC40[buffer][i][j] = (P_TAG*)&D_8013E1E8[buffer][i][j];
            }
        }
    }
}

void func_80017F2C(void)
{
    u32 buffer = SP_DRAW_BUFFER;
    u32 i;
    u32 j;

    for (i = 0; i < 4; i++) {
        OT_TYPE* ordering_tag = &cur_draw_info->ordering_table.start + D_80173C6C[i];

        for (j = 0; j < 8; j++) {
            P_TAG* head = D_8013E1E8[buffer][i][j];

            if (head != NULL) {
                setaddr(D_8013BC40[buffer][i][j], getaddr(ordering_tag));
                setaddr(ordering_tag, head);
            }
        }
    }
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
        x = ((s8)engine_obj.unk46 << 1) + 0x80;
    }
    if (index == 0x1F)
        frame = (const u16*)(archive + (layout->tile + engine_obj.unk44) * 4);
    else
        frame = (const u16*)(archive + layout->tile * 4);
    if (index == 0x26 && bar_object.unk25 != 0)
        frame = (const u16*)(archive + layout->tile * 4 + 0x28);
    count = frame[0];
    pieces = archive + frame[1] * 4;
    if (bar_object.unk14 == layout->character) {
        clut = pause_menu_clut((D_80141BD8.unk0 & 0x10) ? layout->alternate_clut : layout->clut);
    } else if (engine_obj.cur_character == CHARACTER_X) {
        clut = pause_menu_clut(layout->clut);
        if (g_Player.unk93 + 1 == layout->character || (g_Player.unk93 == 0 && layout->character == 0))
            clut = pause_menu_clut(layout->alternate_clut);
    } else {
        clut = pause_menu_clut(index < 0x21 ? layout->alternate_clut : layout->clut);
    }
    if (engine_obj.cur_character == CHARACTER_X && layout->character == 1)
        clut = pause_menu_clut(g_Player.charge_levels[0] < 0x30 ? layout->clut : layout->alternate_clut);
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
                amount = g_Player.charge_levels[i < 2 ? 0 : i - 1];
                if (amount != 0) {
                    poly->x1 = row[0] + amount * 2 - 1;
                    poly->x3 = row[4] + amount * 2 - 1;
                } else {
                    poly->x1 = poly->x0;
                    poly->x3 = poly->x2;
                }
            }
        } else if (i == 0xD) {
            if (g_Player.unk5C > 0) {
                poly->x0 = 0x6E;
                poly->y0 = 0xD2;
                poly->x2 = 0x67;
                poly->y2 = 0xD9;
                poly->y1 = 0xD2;
                poly->x1 = poly->x0 + (s8)g_Player.unk5C * 2;
                poly->y3 = 0xD9;
                poly->x3 = poly->x2 + (s8)g_Player.unk5C * 2;
            }
        } else if (i == 0xC) {
            poly->x1 = poly->x0 + (s8)engine_obj.unk5C[2];
            poly->x3 = poly->x2 + (s8)engine_obj.unk5C[2];
        } else {
            amount = engine_obj.unk5C[i - 10] & 0x7F;
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

void func_80037C28(struct PlayerObj* arg0)
{
    s32 count;
    s8 i;

    if (arg0->unk96 == 8) {
        count = 2;
        func_8001540C(1, 9, arg0);
    } else {
        count = 8;
        func_8001540C(1, 0xA, arg0);
        func_800363B8(arg0, 9);
    }
    for (i = 0; i < count; i++)
        func_80036DA0(1, arg0->unk96, i, NULL);
    arg0->unk98 += count;
    arg0->unk99 += count;
}

extern u32* D_8011C104[10];

void func_800978DC(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;

    arg0->on_screen = 1;
    arg0->unk50 = D_801089FC;
    arg0->unk38 = (u8*)player_gfx + player_gfx[9];
    arg0->animation_table = D_8011C104;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0x11];
    arg0->unk15 = g_Player.unk15;
    func_80092E2C((struct VisualObj*)arg0, &g_Player, arg0->id);
    func_8002B93C(MOVING_OBJECT(arg0), arg0->unk2 == 0 ? 2 : 0x1E);
    arg0->x_vel.val <<= 3;
    arg0->y_vel.val <<= 3;
    if (arg0->unk15 == 0)
        arg0->x_vel.val = -arg0->x_vel.val;
    arg0->unk28.val = 0;
    arg0->unk2C = 0;
    arg0->ext.weapon_8.timer = 0x18;
    func_80015D60(arg0, arg0->unk2);
    func_8002B718(MOVING_OBJECT(arg0));
    arg0->unk5 = 0;
    arg0->state++;
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
}

extern struct Unk_unk68 D_80108A14[];
extern u8 D_80108A44[];

void func_80097BA4(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;
    s32 level = arg0->unk2 >> 1;

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    arg0->unk50 = &D_80108A14[level];
    arg0->unk38 = (u8*)player_gfx + player_gfx[9];
    arg0->animation_table = D_8011C104;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0x11];
    arg0->unk15 = g_Player.unk15;
    func_80092E2C((struct VisualObj*)arg0, &g_Player, arg0->id);
    func_8002B93C(MOVING_OBJECT(arg0), D_80108A44[arg0->unk2]);
    arg0->unk28.val = 0;
    arg0->unk2C = 0;
    arg0->x_vel.val *= 9;
    arg0->y_vel.val *= 9;
    if (arg0->unk15 == 0)
        arg0->x_vel.val = -arg0->x_vel.val;
    func_80015D60(arg0, level + 2);
    func_8002B718(MOVING_OBJECT(arg0));
    arg0->ext.weapon_17.timer = 3;
    arg0->unk5 = 0;
    arg0->state++;
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
}

void func_80097DD8(struct MiscObj* arg0)
{
    s32* player_gfx;
    s32* sprite_frames;

    if (g_Player.unkC3 != 0 || g_Player.unkC4 != 0 || g_Player.unk93 != 8) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (arg0->state != 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.relative_step == 0) {
            ZeroObjectState(OBJECT_HEADER(arg0));
            return;
        }
    } else {
        player_gfx = SP_PLAYER_GFX;
        sprite_frames = SP_SPRITE_FRAMES;
        arg0->on_screen = 1;
        arg0->unk38 = (u8*)player_gfx + player_gfx[9];
        arg0->animation_table = D_8011C104;
        arg0->unk40 = 0x520;
        arg0->unk42 = 0x7801;
        arg0->unk16 = 1;
        arg0->unk3C = (u8*)sprite_frames + sprite_frames[0x11];
        func_80015D60(arg0, arg0->unk2 + 6);
        arg0->state++;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
}

extern s16 D_8010A550[4][2];
extern s16 D_8010A560[4][2];

static const s16* visual_17_target(struct VisualObj* arg0)
{
    return engine_obj.stage != 0xC ? D_8010A550[arg0->unk2 - 1] : D_8010A560[arg0->unk2 - 1];
}

void func_800B20CC(struct VisualObj* arg0)
{
    const s16* target;
    u8 direction;
    struct QuadObj* quad;

    arg0->state = 1;
    arg0->on_screen = 1;
    if (arg0->unk2 == 0) {
        arg0->unk16 = 3;
        func_80015D60(arg0, 0x18);
        return;
    }
    arg0->unk16 = 5;
    func_80015D60(arg0, 0x17);
    target = visual_17_target(arg0);
    direction = func_8002B810(arg0->x_pos.val - (target[0] << 16), arg0->y_pos.val - (target[1] << 16));
    func_8002B93C(MOVING_OBJECT(arg0), direction);
    arg0->unk54 = direction;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->x_vel.val <<= 1;
    arg0->y_vel.val <<= 1;
    quad = find_free_quad_obj();
    if (quad != NULL) {
        quad->active = -0x7F;
        quad->id = 5;
        arg0->unk5C.owner = (struct PlayerObj*)quad;
    }
}

void func_800B22B4(struct VisualObj* arg0)
{
    const s16* target = visual_17_target(arg0);
    s32 target_x = target[0] << 16;
    s32 target_y = target[1] << 16;
    u8 direction = func_8002B810(arg0->x_pos.val - target_x, arg0->y_pos.val - target_y);
    struct BaseObj* quad = (struct BaseObj*)arg0->unk5C.owner;

    if ((arg0->unk54 >> 3) != (direction >> 3)) {
        arg0->unk5 = 1;
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->y_vel.val = 0;
        arg0->unk2C = 0;
        arg0->x_pos.val = target_x;
        arg0->y_pos.val = target_y;
        quad->state = 2;
        func_8002B318(BASE_OBJECT(arg0), 0x10, 0x10);
    } else {
        func_8002B694(ANIMATED_OBJECT(arg0));
    }
    quad->x_pos.val = arg0->x_pos.val;
    quad->y_pos.val = arg0->y_pos.val;
}

extern u8 D_80109004[4];
extern void (*D_80109014[5])(struct ShotObj*);

void func_8009D788(struct ShotObj* arg0)
{
    s32 direction;

    arg0->unk54 = D_80109004;
    arg0->unk50.data = D_80109004;
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 3;
    arg0->unk68 = NULL;
    arg0->unk58.data = (u8*)D_80106070;
    direction = func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
    arg0->unk84.value = direction;
    func_8002B93C(MOVING_OBJECT(arg0), direction);
    arg0->timer = 0x14;
    arg0->unk8A = 0;
    arg0->unk5C = 1;
    arg0->unk60 = 0;
    arg0->unk8C.word = 1;
    arg0->unk62 = 3;
    arg0->unk90.val = 0;
    arg0->x_vel.val *= 3;
    arg0->y_vel.val *= 3;
    func_80015D60(arg0, 0x16);
}

void func_8009D8F0(struct ShotObj* arg0)
{
    s32 target;
    s32 direction;

    if (arg0->unk8C.word == 3 && g_Player.unkBA != 0) {
        arg0->unk5 = 2;
        func_8009DA28(arg0);
        return;
    }
    if (arg0->timer != 0) {
        if ((D_80141BD8.unk0 & 3) == 0) {
            target = func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
            direction = arg0->unk84.value;
            if ((direction - (target & 0xFF)) & 0x1F) {
                direction = ((u32)((target - direction) & 0x1F) < 0x10) ? direction + 1 : direction - 1;
                arg0->unk84.value = direction & 0x1F;
                func_8002B93C(MOVING_OBJECT(arg0), arg0->unk84.value);
                arg0->x_vel.val *= 3;
                arg0->y_vel.val *= 3;
            }
        }
        arg0->timer--;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_8009DB9C(struct ShotObj* arg0)
{
    struct BaseObj* owner;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_80109014[arg0->unk5](arg0);
    owner = (struct BaseObj*)arg0->unk7C;
    if (owner->state == 1 && arg0->unk8C.word != 0 && g_Player.unkBA == 0 && func_8002D9BC(arg0) != 0 && g_Player.unkBA != 0) {
        arg0->unk8C.word = 3;
        arg0->x_pos.val = g_Player.x_pos.val;
        arg0->y_pos.val = g_Player.y_pos.val;
    }
    owner = (struct BaseObj*)arg0->unk7C;
    if ((arg0->unk8C.word == 3 && g_Player.unkBA != 0 && owner->state == 2) || func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) != 0) {
        arg0->state = 2;
        return;
    }
    if (arg0->unk8A == 0)
        func_8002B318(BASE_OBJECT(arg0), 0x10, 0x10);
}

void func_800BB314(struct EffectObj* arg0);
void func_800BB508(struct EffectObj* arg0);
void func_800BB588(struct EffectObj* arg0);

static void effect_26_spawn_spark(struct EffectObj* arg0, u8 angle)
{
    struct QuadObj* quad = find_free_quad_obj();

    if (quad == NULL)
        return;
    quad->active = 1;
    quad->id = 4;
    quad->unk2 = angle;
    quad->x_pos.i.hi = arg0->x_pos.i.hi;
    quad->y_pos.i.hi = arg0->y_pos.i.hi;
}

void func_800BB364(struct EffectObj* arg0)
{
    effect_26_spawn_spark(arg0, arg0->unk2);
    effect_26_spawn_spark(arg0, (arg0->unk2 + 0xA) & 0x1F);
    effect_26_spawn_spark(arg0, (arg0->unk2 + 0x15) & 0x1F);
    func_8002B560(0x82, 0);
    if (arg0->ext.effect_26.timer != 0) {
        arg0->ext.effect_26.timer--;
        func_800AF808(BASE_OBJECT(arg0));
        return;
    }
    arg0->ext.effect_26.timer = 0x64;
    arg0->state++;
    g_FilterModeR = 0;
    g_FilterModeG = 0;
    g_FilterModeB = 0;
    g_FilterAmountR = 0;
    g_FilterAmountG = 0;
    g_FilterAmountB = 0;
    D_8013E188[0] = -1;
    D_8013E188[1] = -1;
    D_8013E188[2] = -1;
    D_8013E188[3] = -1;
    func_80016F0C();
    engine_obj.unk42 = 0;
}

void func_800BB750(struct EffectObj* arg0)
{
    arg0->ext.effect_26.timer++;
    func_800BB314(arg0);
    func_800BB508(arg0);
    func_800BB588(arg0);
    if (arg0->ext.effect_26.timer % 5 != 0)
        return;
    g_FilterAmountR += 1;
    g_FilterAmountG += 0x20;
    g_FilterAmountB += 0x400;
    if (g_FilterAmountR != 0x1F)
        return;
    arg0->state++;
    arg0->ext.effect_26.timer = (arg0->active & 0x80) ? 0xC8 : 0x28;
    arg0->unk7 = 1;
    engine_obj.enable_boss = 0;
    func_8001540C(0, 5, NULL);
}

void func_800BB888(struct EffectObj* arg0)
{
    if (++arg0->ext.effect_26.timer % 5 != 0)
        return;
    g_FilterAmountR -= 1;
    g_FilterAmountG -= 0x20;
    g_FilterAmountB -= 0x400;
    if (g_FilterAmountR == 0)
        arg0->state++;
}

extern s16 D_8010F8A4[64][2];

void func_800D52F4(struct QuadObj* arg0)
{
    u8 angle = arg0->ext.quad_4.unk38;
    const s16* outer = D_8010F8A4[(arg0->ext.quad_4.unk39 + 1) * 16 + (angle & 0xF)];
    const s16* inner = D_8010F8A4[arg0->ext.quad_4.unk39 * 16 + (angle & 0xF)];
    s32 sign = (angle & 0x1F) >= 0x10 ? -1 : 1;

    arg0->unk1C.val = sign * (outer[0] << 16);
    arg0->unk20.val = sign * (outer[1] << 16);
    arg0->unk24.val = sign * (inner[0] << 16);
    arg0->unk28.val = sign * (inner[1] << 16);
    arg0->unk2C.val = 0;
    arg0->unk30.val = 0;
    arg0->state++;
    arg0->ext.quad_4.timer = func_8002B780() % 7;
    quad_is_on_screen(arg0);
}

#define QUAD6_ANGLE(obj) ((obj)->ext.ready_line.x_vel.bytes[0])
#define QUAD6_DELAY(obj) ((obj)->ext.ready_line.x_vel.bytes[1])
#define QUAD6_AGE(obj) ((obj)->ext.ready_line.x_vel.bytes[2])
#define QUAD6_X_SPEED(obj) ((obj)->ext.ready_line.y_vel.val)
#define QUAD6_Y_SPEED(obj) ((obj)->ext.ready_line.x_accel.val)
#define QUAD6_X_SPEED2(obj) ((obj)->ext.ready_line.y_accel.val)
#define QUAD6_Y_SPEED2(obj) ((obj)->runtime.search_light.x_accumulator)
#define QUAD6_X_ACCEL(obj) ((obj)->runtime.search_light.y_accumulator)
#define QUAD6_Y_ACCEL(obj) (*(s32*)&(obj)->runtime.search_light.pause_timer)
#define QUAD6_X_ACCEL2(obj) ((obj)->runtime.search_light.base_speed)
#define QUAD6_Y_ACCEL2(obj) (*(s32*)&(obj)->link)

extern s32 D_800F459C[];
extern s32 D_800F45C0[];

void func_800D5934(struct QuadObj* arg0)
{
    u8 angle;
    s16 index;
    s16 x_sign;
    s16 y_sign;

    arg0->unk36 = 0;
    arg0->unk34 = 1;
    arg0->bg_offset = 0;
    arg0->active |= 0x82;
    angle = get_random() & 0x1F;
    QUAD6_ANGLE(arg0) = angle;
    if (angle < 0x10) {
        x_sign = -1;
        if (angle < 8) {
            index = 8 - angle;
            y_sign = 1;
        } else {
            index = angle - 8;
            y_sign = -1;
        }
    } else {
        x_sign = 1;
        if (angle < 0x18) {
            index = 0x18 - angle;
            y_sign = -1;
        } else {
            index = angle - 0x18;
            y_sign = 1;
        }
    }
    QUAD6_X_SPEED(arg0) = (s32)((u32)(D_800F459C[index] * y_sign) << 4) >> 4;
    QUAD6_Y_SPEED(arg0) = (s32)((u32)(D_800F45C0[index] * x_sign) << 4) >> 4;
    arg0->unk14.val = 0;
    arg0->unk18.val = 0;
    arg0->unk1C.val = 0;
    arg0->unk20.val = 0;
    arg0->unk24.val = 0;
    arg0->unk28.val = 0;
    arg0->unk2C.val = 0;
    arg0->unk30.val = 0;
    QUAD6_AGE(arg0) = 0;
    arg0->state++;
    QUAD6_X_ACCEL(arg0) = QUAD6_X_SPEED(arg0);
    QUAD6_X_SPEED2(arg0) = QUAD6_X_SPEED(arg0);
    QUAD6_Y_SPEED2(arg0) = QUAD6_Y_SPEED(arg0);
    QUAD6_Y_ACCEL(arg0) = QUAD6_Y_SPEED(arg0);
    QUAD6_DELAY(arg0) = 4;
    QUAD6_X_ACCEL2(arg0) = QUAD6_X_SPEED2(arg0) / 2;
    QUAD6_Y_ACCEL2(arg0) = QUAD6_Y_SPEED2(arg0) / 2;
}

void func_800D5AB0(struct QuadObj* arg0)
{
    if (++QUAD6_AGE(arg0) == 0)
        QUAD6_AGE(arg0) = 0xFE;
    arg0->unk14.val += QUAD6_X_SPEED(arg0);
    arg0->unk18.val += QUAD6_Y_SPEED(arg0);
    arg0->unk24.val += QUAD6_X_SPEED2(arg0);
    arg0->unk28.val += QUAD6_Y_SPEED2(arg0);
    QUAD6_X_SPEED(arg0) += QUAD6_X_ACCEL(arg0);
    QUAD6_Y_SPEED(arg0) += QUAD6_Y_ACCEL(arg0);
    QUAD6_X_SPEED2(arg0) += QUAD6_X_ACCEL2(arg0);
    QUAD6_Y_SPEED2(arg0) += QUAD6_Y_ACCEL2(arg0);
    arg0->unk1C.val = arg0->unk14.val + 0x10000;
    arg0->unk2C.val = arg0->unk24.val - 0x10000;
    arg0->unk20.val = arg0->unk18.val + 0x10000;
    arg0->unk30.val = arg0->unk28.val - 0x10000;
    if (QUAD6_DELAY(arg0) != 0) {
        QUAD6_DELAY(arg0)
        --;
        return;
    }
    quad_is_on_screen(arg0);
    if (arg0->on_screen == 0 && QUAD6_AGE(arg0) >= 0x3D)
        arg0->state++;
}

void func_800CF4B8(struct MiscObj* arg0)
{
    struct MainObj* source = arg0->ext.misc_7.position;

    arg0->x_pos.val = source->x_pos.val;
    arg0->y_pos.val = source->y_pos.val;
    arg0->unk40 = source->unk40;
    arg0->unk42 = source->unk42 & 0x7FFF;
    arg0->animation_table = (u32**)source->animation_table;
    arg0->unk3C = (void*)source->sprite_frames;
    arg0->unk15 = 0;
    arg0->bg_offset = source->bg_offset;
    switch ((u8)arg0->unk2) {
    case 2:
        func_80015D60(arg0, 0x18);
        arg0->unk16 = 7;
        arg0->state = 1;
        break;
    case 3:
        func_80015D60(arg0, 0x17);
        arg0->unk16 = 4;
        arg0->state = 1;
        break;
    case 4:
        func_80015D60(arg0, 0xE);
        arg0->unk16 = 4;
        arg0->state = 4;
        break;
    case 5:
        func_80015D60(arg0, 0x15);
        arg0->unk16 = 4;
        arg0->state = 4;
        break;
    default:
        func_80015D60(arg0, 0x19);
        arg0->unk16 = 4;
        arg0->state = 3;
        break;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800CF660(struct MiscObj* arg0)
{
    struct MainObj* source = arg0->ext.misc_7.position;

    arg0->x_pos.val = source->x_pos.val;
    arg0->y_pos.val = source->y_pos.val;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
    if (source->unk67 == 0) {
        func_80015D60(arg0, 0x1A);
        arg0->state -= 2;
    } else if (arg0->animation_step.fields.relative_step < 0 && arg0->unk2 != 0) {
        arg0->state--;
    }
}

extern struct Unk_unk68 D_80102A78;

void func_8007E350(struct MainObj* arg0)
{
    if (arg0->unk5C < 0x30) {
        if (--arg0->unk7E == 0) {
            func_8001540C(0, 0xE, 0);
            arg0->unk7E = 3;
        }
        arg0->unk5C++;
    } else {
        func_80015D60(arg0, 0);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
        arg0->unk54 = &D_80102A64;
        func_80036B18();
        if (engine_obj.stage == 0xC) {
            background_objects[0].unk26 = 0x110;
            background_objects[0].unk24 = 0x1B0;
        } else {
            background_objects[0].unk26 = 0x13F0;
            background_objects[0].unk24 = 0x1490;
        }
        background_objects[0].unk48 = 4;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void magma_dragoon_face_player(struct MainObj* arg0);

void func_8007E4C8(struct MainObj* arg0)
{
    u8 roll;

    magma_dragoon_face_player(arg0);
    roll = get_random() & 0xF;
    arg0->ext.main_65.attack_repeat = 0;
    if (arg0->unk5C >= 0x19) {
        if (roll < 6)
            arg0->ext.main_65.attack = 0;
        else if (roll < 10)
            arg0->ext.main_65.attack = 1;
        else if (roll < 13)
            arg0->ext.main_65.attack = 2;
        else
            arg0->ext.main_65.attack = 3;
    } else {
        if (roll < 6)
            arg0->ext.main_65.attack = 4;
        else if (roll < 9)
            arg0->ext.main_65.attack = 5;
        else
            arg0->ext.main_65.attack = 6;
    }
    switch (arg0->ext.main_65.attack) {
    case 0:
    case 1:
    case 4:
        arg0->unk5 = 4;
        break;
    case 2:
    case 5:
        arg0->unk5 = 5;
        break;
    case 3:
        arg0->unk5 = 8;
        break;
    case 6:
        arg0->unk5 = 0xA;
        break;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8007E6F8(struct MainObj* arg0)
{
    s16 x;

    arg0->unk50 = arg0->animation_step.fields.event != 0 ? &D_80102A78 : &D_80102A6C;
    if (arg0->unk70 & 8) {
        arg0->unk6++;
        func_80015D60(arg0, 6);
        arg0->unk50 = &D_80102A6C;
        arg0->unk60 = 4;
        arg0->unk67 = 0;
        func_8001540C(2, 2, arg0);
    }
    if (arg0->animation_step.fields.event == 2) {
        x = arg0->x_pos.i.hi;
        if (x < g_Player.x_pos.i.hi)
            arg0->unk15 = x < *(s16*)magma_dragoon_arena_right - 0x50 ? 0x40 : 0;
        else
            arg0->unk15 = x < *(s16*)magma_dragoon_arena_left + 0x50 ? 0x40 : 0;
        arg0->unk20 = arg0->unk15 != 0 ? 0x80000 : -0x80000;
    }
    if (arg0->animation_step.fields.event == 1)
        func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8007E848(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk6 = 0;
        if (arg0->ext.main_65.attack == 0)
            arg0->unk5 = 0xA;
        else if (arg0->ext.main_65.attack == 1)
            arg0->unk5 = 0xB;
        else
            arg0->unk5 = arg0->ext.main_65.attack_repeat++ != 0 ? 0xC : 0xB;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

static struct ShotObj* main_65_spawn_shot(struct MainObj* arg0, s8 subtype)
{
    struct ShotObj* shot = find_free_shot_obj();

    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x29;
        shot->unk2 = subtype;
        shot->unk7C = (struct WeaponObj*)arg0;
    }
    return shot;
}

void func_8007E95C(struct MainObj* arg0)
{
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        shot = main_65_spawn_shot(arg0, 0);
        func_8001540C(2, (arg0->animation_step.fields.event & 1) ? 6 : 7, shot);
        arg0->animation_step.fields.event = 0;
    }
    if (arg0->animation_step.fields.relative_step != 0)
        return;
    arg0->unk6 = 0;
    if (arg0->ext.main_65.attack == 6) {
        arg0->unk5 = 6;
    } else if (arg0->ext.main_65.attack == 5) {
        arg0->unk5 = 7;
    } else {
        arg0->unk5 = 3;
        func_80015D60(arg0, 0);
    }
}

static void main_65_throw(struct MainObj* arg0, s16 y_offset)
{
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 1)
        return;
    shot = main_65_spawn_shot(arg0, 3);
    if (shot != NULL) {
        shot->x_pos.i.hi = arg0->x_pos.i.hi + (arg0->unk15 != 0 ? 0x17 : -0x17);
        shot->y_pos.i.hi = arg0->y_pos.i.hi + y_offset;
        func_8001540C(2, 4, arg0);
    }
    arg0->animation_step.fields.event = 0;
}

void func_8007F404(struct MainObj* arg0)
{
    main_65_throw(arg0, 0);
    if (arg0->animation_step.fields.relative_step != 0)
        return;
    if (arg0->ext.main_65.attack == 0)
        arg0->unk5 = 0xB;
    else if (arg0->ext.main_65.attack == 1)
        arg0->unk5 = 0xC;
    else
        arg0->unk5 = arg0->ext.main_65.attack_repeat++ != 0 ? 5 : 0xB;
    arg0->unk6 = 0;
}

void func_8007F5B0(struct MainObj* arg0)
{
    main_65_throw(arg0, 0x28);
    if (arg0->animation_step.fields.relative_step != 0)
        return;
    arg0->unk50 = &D_80102A70;
    arg0->unk6 = 0;
    if (arg0->ext.main_65.attack == 0)
        arg0->unk5 = 9;
    else if (arg0->ext.main_65.attack == 4)
        arg0->unk5 = 4;
    else
        arg0->unk5 = 0xA;
}

void func_8007F780(struct MainObj* arg0)
{
    s16 distance;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 1)
        return;
    arg0->unk67 = 1;
    arg0->unk24 = 0x40000;
    arg0->unk2C = 0x1C00;
    arg0->animation_step.fields.event = 0;
    arg0->unk6++;
    arg0->unk15 = g_Player.x_pos.i.hi < arg0->x_pos.i.hi ? 0 : 0x40;
    distance = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
    if (distance < 0)
        distance = -distance;
    arg0->unk20 = arg0->unk15 != 0 ? 0x60000 : -0x60000;
    if (distance < 0x30)
        arg0->unk28 = -0x8000;
    else if (distance < 0x60)
        arg0->unk28 = -0x4000;
    else
        arg0->unk28 = -0x2000;
}

void func_8007FAA4(struct MainObj* arg0)
{
    struct MiscObj* misc;

    func_80015D60(arg0, 0xD);
    arg0->unk50 = &D_80102A6C;
    arg0->unk54 = &D_80102A64;
    arg0->unk24 = 0x40000;
    arg0->unk60 = 4;
    arg0->unk2C = 0x1C00;
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    misc = find_free_misc_obj();
    if (misc != NULL) {
        misc->active = 0x41;
        misc->id = 0x26;
        misc->unk2 = 4;
        misc->ext.misc_7.position = arg0;
        arg0->ext.main_65.object = (struct MainObj*)misc;
    }
    arg0->unk6++;
}

void func_8007FF00(struct MainObj* arg0)
{
    struct EffectObj* effect;
    u16 flash;

    if (--arg0->unk7C == 0) {
        arg0->unk5++;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = -0x7F;
            effect->id = 0x1A;
            effect->x_pos.i.hi = arg0->x_pos.i.hi;
            effect->y_pos.i.hi = arg0->y_pos.i.hi;
            arg0->ext.main_65.object = (struct MainObj*)effect;
        }
    }
    flash = arg0->unk7E;
    arg0->unk7E = flash - 1;
    if (flash == 0) {
        arg0->unk42 ^= 0x8000;
        arg0->unk61 -= 5;
        if (arg0->unk61 >= 0x1A)
            arg0->unk61 = 0;
        arg0->unk7E = arg0->unk61 < 5 ? 5 : arg0->unk61;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8007FFFC(struct MainObj* arg0)
{
    struct BaseObj* effect = (struct BaseObj*)arg0->ext.main_65.object;
    struct MiscObj* misc;
    u16 flash;
    s16 scroll;
    s16 y;

    if (effect->active == 0) {
        engine_obj.enable_boss = 0;
        engine_obj.boss_ptr = NULL;
        if (engine_obj.stage == 0xC) {
            engine_obj.unkF = -0x80;
            engine_obj.character_state.bytes[engine_obj.checkpoint + 6] = 1;
            engine_obj.checkpoint += 9;
        } else {
            engine_obj.unkF = 0x10;
        }
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (effect->unk7 == 0) {
        flash = arg0->unk7E;
        arg0->unk7E = flash - 1;
        if (flash == 0) {
            arg0->unk7E = 5;
            arg0->unk42 ^= 0x8000;
        }
        func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
        return;
    }
    if (engine_obj.stage != 4)
        return;
    arg0->unk5++;
    func_80015D60(arg0, 0x14);
    if (magma_dragoon_arena_center[0] < g_Player.x_pos.i.hi) {
        arg0->unk15 = 0;
        arg0->x_pos.i.hi = *(s16*)magma_dragoon_arena_right - 0x30;
        if (g_Player.unkC5 < 0)
            qux_object.unk15 = 0x40;
        func_80036AE4(0x14, 0x40);
        scroll = 0x1490;
    } else {
        arg0->unk15 = 0x40;
        arg0->x_pos.i.hi = *(s16*)magma_dragoon_arena_left + 0x30;
        if (g_Player.unkC5 < 0)
            qux_object.unk15 = 0;
        func_80036AE4(0x14, 0);
        scroll = 0x13F0;
    }
    background_objects[0].unk26 = scroll;
    background_objects[0].unk24 = scroll;
    y = magma_dragoon_arena_floor[0];
    arg0->y_pos.i.hi = y;
    if (g_Player.unkC5 < 0) {
        qux_object.y_pos.i.hi = y;
        qux_object.x_pos.i.hi = magma_dragoon_arena_center[0];
    } else {
        g_Player.y_pos.i.hi = y;
        g_Player.x_pos.i.hi = magma_dragoon_arena_center[0];
    }
    background_objects[0].unk2A = 0x1EB;
    background_objects[0].unk28 = 0x1EB;
    misc = find_free_misc_obj();
    if (misc != NULL) {
        misc->active = 0x41;
        misc->id = 0x26;
        misc->unk2 = 5;
        misc->ext.misc_7.position = arg0;
        arg0->ext.main_65.smoke = (struct MainObj*)misc;
    }
    engine_obj.enable_boss = 0;
    engine_obj.boss_ptr = NULL;
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

extern struct Unk_unk68 D_801089BC[];
extern u8 D_801089D4[4];
extern u32* D_8011C0F0[5];

void func_80096EA4(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;
    s8 dx = D_801089D4[arg0->unk2 * 2];
    s8 dy = D_801089D4[arg0->unk2 * 2 + 1];

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    arg0->unk50 = D_801089BC;
    arg0->unk38 = (u8*)player_gfx + player_gfx[8];
    arg0->unk16 = 1;
    arg0->animation_table = D_8011C0F0;
    arg0->unk42 = 0x7801;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0x10];
    if (arg0->unk2 == 0) {
        arg0->unk40 = 0x520;
        arg0->x_vel.val = -0x26000;
        arg0->unk15 = 0;
    } else {
        arg0->x_vel.val = 0x26000;
        arg0->unk40 = 0x530;
        arg0->unk15 = 0x40;
    }
    if (g_Player.unk15 == 0) {
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi + dx;
    } else {
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi - dx;
        arg0->unk15 ^= 0x40;
        arg0->x_vel.val = -arg0->x_vel.val;
    }
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->y_pos.i.hi = g_Player.y_pos.i.hi + dy;
    arg0->unk49 = arg0->unk2;
    arg0->ext.weapon_7.timer = 0x23;
    arg0->ext.weapon_7.unk90 = 8;
    arg0->ext.weapon_7.unk91 = 4;
    func_80015D60(arg0, 0);
    func_8001540C(0, 0x1E, arg0);
    arg0->state++;
    func_80097328(arg0);
}

extern u8 D_801089F8[4];
extern struct Unk_unk68 D_801089C0[];
void func_800977D4(struct WeaponObj* arg0);

void func_80097430(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;
    s32 side;
    s8 dx;
    s8 dy;

    arg0->unk38 = (u8*)player_gfx + player_gfx[8];
    arg0->animation_table = D_8011C0F0;
    arg0->unk40 = 0x530;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0x10];
    if (arg0->unk2 < 0) {
        side = 1;
        arg0->x_vel.val = 0x60000;
        arg0->unk15 = 0x40;
    } else {
        side = 0;
        arg0->x_vel.val = -0x60000;
        arg0->unk15 = 0;
    }
    dx = D_801089F8[side * 2];
    dy = D_801089F8[side * 2 + 1];
    if (g_Player.unk15 == 0) {
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi + dx;
    } else {
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi - dx;
        arg0->unk15 ^= 0x40;
        arg0->x_vel.val = -arg0->x_vel.val;
    }
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->y_pos.i.hi = g_Player.y_pos.i.hi + dy;
    arg0->ext.weapon_16.timer = 0x32;
    arg0->ext.weapon_16.unk91 = 4;
    arg0->ext.weapon_16.delay = (arg0->unk2 & 0x7F) << 2;
    arg0->unk49 = 1;
    func_80015D60(arg0, 4);
    func_8001540C(0, 0x1E, arg0);
    func_8001540C(1, 0xA, arg0);
    arg0->unk5 = 0;
    arg0->state++;
    func_800977D4(arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x18, 0x30);
}

void func_80097670(struct WeaponObj* arg0)
{
    if (arg0->ext.weapon_16.delay != 0) {
        arg0->ext.weapon_16.delay--;
        return;
    }
    arg0->on_screen = 1;
    arg0->unk64 = 1;
    arg0->unk50 = D_801089C0;
    arg0->unk5++;
    func_8002B318(BASE_OBJECT(arg0), 0x18, 0x30);
}

extern struct VisualSpawnOffset D_8010A584[2];
void func_800B2880(struct VisualObj* arg0);

void func_800B2698(struct VisualObj* arg0)
{
    s32* player_gfx;
    s32* sprite_frames;
    struct VisualSpawnOffset offset;

    if (g_Player.unkC3 != 0 || g_Player.unkC4 != 0 || g_Player.unk93 != 7 || g_Player.unkBF != 0 || g_Player.unk5C == 0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (arg0->state != 0) {
        if (arg0->unk5C.value == 0) {
            ZeroObjectState(OBJECT_HEADER(arg0));
            return;
        }
        arg0->unk5C.value--;
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_800B2880(arg0);
        return;
    }
    arg0->on_screen = 1;
    player_gfx = SP_PLAYER_GFX;
    sprite_frames = SP_SPRITE_FRAMES;
    arg0->unk38 = (u8*)player_gfx + player_gfx[8];
    arg0->animation_table = D_8011C0F0;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0x10];
    offset = D_8010A584[arg0->unk2];
    arg0->unk15 = arg0->unk2 != 0 ? 0x40 : 0;
    if (g_Player.unk15 == 0) {
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi + offset.x;
    } else {
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi - offset.x;
        arg0->unk15 ^= 0x40;
    }
    arg0->unk5C.value = 0x10;
    arg0->unk49 = 0;
    arg0->y_pos.i.hi = g_Player.y_pos.i.hi + offset.y;
    func_80015D60(arg0, 3);
    arg0->state++;
    func_800B2880(arg0);
}

extern u8 D_801098D0[4];
extern u8 D_801098D4[2][4];
extern u8 D_801098E0[4];
extern u8 D_801098E4[4];
extern u8 D_801098EC[4];
extern u8 D_801098F0[4];
extern s16 D_801098F4[8];

void func_800A56E4(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;

    arg0->unk40 = owner->unk40;
    arg0->animation_table = (u32**)owner->animation_table;
    arg0->unk3C = (void*)owner->sprite_frames;
    arg0->unk5C = 0;
    arg0->unk16 = 1;
    arg0->unk42 = owner->unk42 & 0x7FFF;
    arg0->bg_offset = owner->bg_offset;
    switch (arg0->unk2) {
    case 0:
        arg0->unk58.data = (u8*)D_801060F0;
        arg0->unk54 = NULL;
        arg0->unk60 = 9;
        arg0->unk15 = owner->unk15;
        arg0->x_pos.val = owner->x_pos.val + (arg0->unk15 != 0 ? 0x180000 : -0x180000);
        arg0->y_pos.val = owner->y_pos.val + 0x100000;
        arg0->y_vel.val = 0x20000;
        arg0->unk5 = 2;
        arg0->timer = 7;
        arg0->x_vel.val = arg0->unk15 != 0 ? 0x60000 : -0x60000;
        arg0->unk50.data = D_801098D0;
        arg0->unk68 = NULL;
        arg0->state++;
        func_80015D60(arg0, 0x1C);
        break;
    case 1:
        arg0->unk58.data = (u8*)D_80105FF0;
        arg0->unk15 = 0;
        arg0->unk54 = NULL;
        arg0->unk60 = 4;
        arg0->x_pos.val = owner->x_pos.val + (owner->unk15 != 0 ? -0x100000 : 0x100000);
        arg0->y_pos.val = owner->y_pos.val - 0x200000;
        arg0->x_vel.val = D_801098F4[arg0->unk7] << 12;
        if (arg0->unk15 != 0)
            arg0->x_vel.val = -arg0->x_vel.val;
        arg0->y_vel.val = 0x50000;
        arg0->unk5 = 3;
        arg0->unk50.data = (u8*)D_801098D4;
        arg0->unk68 = NULL;
        arg0->state++;
        func_80015D60(arg0, 0x1D);
        break;
    case 2:
        arg0->unk58.data = (u8*)D_801060F0;
        arg0->unk50.data = D_801098E0;
        arg0->unk54 = NULL;
        arg0->unk68 = (struct Unk_unk68*)D_801098E4;
        arg0->unk60 = 4;
        arg0->unk15 = owner->unk15;
        arg0->x_pos.val = owner->x_pos.val;
        arg0->y_pos.val = owner->y_pos.val - 0x400000;
        arg0->y_vel.val = 0x1C000;
        arg0->x_vel.val = arg0->unk15 != 0 ? 0x40000 : -0x40000;
        arg0->unk28 = 0;
        arg0->unk2C = 0x1300;
        arg0->unk5 = 4;
        arg0->state++;
        func_80015D60(arg0, 0x1F);
        break;
    case 3:
        arg0->unk58.data = (u8*)D_801060F0;
        arg0->unk50.data = D_801098EC;
        arg0->unk68 = (struct Unk_unk68*)D_801098F0;
        arg0->unk60 = 6;
        arg0->unk5 = 5;
        arg0->unk54 = NULL;
        arg0->timer = 3;
        arg0->state++;
        arg0->unk15 = owner->unk15;
        func_80015D60(arg0, 0x1B);
        break;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x30, 0x30);
}

extern u8 D_801098DC[4];
extern u8 D_801098E8[4];
extern u16 D_80109904[8];

void func_800A5AA4(struct ShotObj* arg0)
{
    struct BaseObj* owner = (struct BaseObj*)arg0->unk7C;

    func_8002D9BC(arg0);
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->on_screen != 0)
        return;
    if (owner->state != 1) {
        arg0->unk5 = 0;
        arg0->state++;
        return;
    }
    func_80015D60(arg0, 0x1E);
    arg0->unk54 = D_801098DC;
    arg0->x_pos.i.hi = background_objects[0].x_pos.i.hi + D_80109904[arg0->unk7] + (get_random() & 0x1F);
    arg0->x_vel.val = -0x60000;
    arg0->y_vel.val = -0x60000;
    arg0->unk6++;
    arg0->timer = (arg0->unk7 << 3) + 0x64;
    arg0->unk8A = 4;
    arg0->y_pos.i.hi = background_objects[0].y_pos.i.hi - 0x20;
}

void func_800A5BA8(struct ShotObj* arg0)
{
    s16 timer = arg0->timer;
    s16 floor;

    if (timer >= 2) {
        arg0->timer = timer - 1;
        return;
    }
    if (timer == 1) {
        arg0->timer = 0;
        func_80028BAC(0x78, 4, 2);
    }
    func_8002D9BC(arg0);
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    floor = engine_obj.stage == 0xC ? 0x6C8 : 0x2B8;
    if (arg0->y_pos.i.hi <= floor)
        return;
    func_80015D60(arg0, 0x20);
    arg0->y_pos.i.hi = floor;
    arg0->unk6++;
}

void func_800A5E60(struct ShotObj* arg0)
{
    func_8002D9BC(arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step != 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x30, 0x30);
        return;
    }
    arg0->unk60 = 9;
    arg0->unk6++;
    func_80015D60(arg0, 0x23);
    if (engine_obj.stage == 0xC)
        arg0->x_pos.i.hi = arg0->unk15 != 0 ? 0x2C8 : 0x138;
    else
        arg0->x_pos.i.hi = arg0->unk15 != 0 ? 0x15A8 : 0x1418;
    arg0->unk50.data = D_801098E8;
    arg0->y_vel.val = 0x40000;
    arg0->x_vel.val = 0;
    arg0->timer = 0xC8;
    arg0->y_pos.i.hi += 0x12C;
    func_8002B318(BASE_OBJECT(arg0), 0x30, 0x80);
}

void func_800A60D0(struct ShotObj* arg0)
{
    struct ShotObj* child;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002D9BC(arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x30, 0x30);
    if (--arg0->timer == 0 && (arg0->unk70 & 3) == 0) {
        child = find_free_shot_obj();
        if (child != NULL) {
            child->active = 0x41;
            child->id = 0x29;
            child->unk2 = 3;
            child->unk7C = (struct WeaponObj*)arg0;
            child->x_pos.i.hi = arg0->x_pos.i.hi + (arg0->unk15 != 0 ? 0x18 : -0x18);
            child->timer = 3;
            child->y_pos.i.hi = arg0->y_pos.i.hi;
        }
    }
    if (arg0->animation_step.fields.frame_index == 0x8A)
        arg0->unk50.data = NULL;
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->state++;
    }
}

void func_8007C3FC(struct MainObj* arg0)
{
    struct EffectObj* effect;

    if (g_Player.unkC4 != 0)
        return;
    switch (arg0->unk6) {
    case 0:
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x18;
            arg0->ext.main_64.object = effect;
        }
        func_80036AE4(0x14, 0x40);
        arg0->unk6 = 1;
        arg0->unk7 = 0;
        break;
    case 1:
        if (((struct BaseObj*)arg0->ext.main_64.object)->active != 0)
            break;
        arg0->unk6 = 2;
        arg0->bg_offset = g_Player.bg_offset;
        if (engine_obj.stage != 0xC) {
            arg0->unk40 = (D_801406A8[0] >> 7) + 0xB0;
        } else {
            arg0->unk40 = (D_801406A8[0] >> 7) + 0x160;
            arg0->unk42 = 0x7888;
            arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[4];
        }
        arg0->animation_table = (const u8* const*)cyber_peacock_animations;
        arg0->unk16 = 4;
        arg0->unk60 = 5;
        arg0->unk61 = -0x80;
        arg0->unk63 = 2;
        arg0->unk5C = 0;
        arg0->unk62 = 0;
        arg0->unk7C = 0x20;
        engine_obj.enable_boss = 0;
        engine_obj.unk25 = 0;
        engine_obj.boss_ptr = arg0;
        break;
    case 2:
        if (--arg0->unk7C == 0) {
            arg0->unk5 = 2;
            arg0->unk6 = 0;
            arg0->unk7 = 0;
        }
        break;
    }
}

void func_8007C6E8(struct MainObj* arg0)
{
    s8 health;

    if (func_8009227C() != 0)
        return;
    if (arg0->animation_step.fields.relative_step != 0) {
        if (arg0->animation_step.fields.event != 0) {
            arg0->animation_step.fields.event = 0;
            func_8001540C(2, 0xC2, arg0);
        }
        func_80015DC8(ANIMATED_OBJECT(arg0));
        return;
    }
    health = arg0->unk5C;
    if (health < 0x30) {
        if (--arg0->unk7C == 0) {
            func_8001540C(0, 0xE, 0);
            arg0->unk7C = 2;
        }
        arg0->unk5C++;
        return;
    }
    arg0->state = 1;
    arg0->ext.main_64.saved_health = health;
    arg0->unk5 = 2;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->unk61 = 0;
    func_80036B18();
}

void func_8007D174(struct MainObj* arg0)
{
    struct ItemObj* item = find_free_item_obj();

    if (item == NULL)
        return;
    item->id = 0x17;
    item->active = arg0->active;
    item->unk2 = arg0->ext.main_64.shot_count;
    item->x_pos.val = arg0->x_pos.val;
    item->y_pos.val = arg0->y_pos.val;
    item->animation_table = (void*)arg0->animation_table;
    item->unk40 = arg0->unk40;
    item->sprite_frames = (void*)arg0->sprite_frames;
    item->unk42 = arg0->unk42 & 0x7FFF;
    item->unk16 = arg0->unk16;
    item->backref = (void*)arg0;
    item->unk15 = arg0->unk15;
    arg0->ext.main_64.object = item;
    func_8001540C(2, 0xC4, arg0);
}

extern u8 cyber_peacock_attack_animations[];
extern u8 cyber_peacock_attack_steps[];
void cyber_peacock_face_player(struct MainObj* arg0);
u8 cyber_peacock_choose_attack(struct MainObj* arg0);
void cyber_peacock_start_teleport(struct MainObj* arg0);

void func_8007CA68(struct MainObj* arg0)
{
    s16 timer = --arg0->unk7C;
    u8 attack;
    s16 base;

    if (timer != 0) {
        if (timer == 0x14) {
            arg0->ext.main_64.target_x = g_Player.x_pos.i.hi;
            arg0->ext.main_64.target_y = g_Player.y_pos.i.hi - 0x18;
        }
        func_80015DC8(ANIMATED_OBJECT(arg0));
        return;
    }
    arg0->unk7 = 0;
    arg0->unk6++;
    arg0->x_pos.i.hi = arg0->ext.main_64.target_x;
    arg0->y_pos.i.hi = arg0->ext.main_64.target_y;
    cyber_peacock_face_player(arg0);
    attack = cyber_peacock_choose_attack(arg0);
    arg0->ext.main_64.next_step = cyber_peacock_attack_steps[attack];
    func_80015D60(arg0, cyber_peacock_attack_animations[attack]);
    arg0->unk2 = attack;
    if (attack == 0) {
        func_8001540C(2, 0xC7, arg0);
        return;
    }
    base = arg0->ext.main_64.arena_x;
    switch ((s8)attack) {
    case 1:
        arg0->y_pos.i.hi = arg0->ext.main_64.arena_y + 0xB3;
        arg0->ext.main_64.target_y = arg0->y_pos.i.hi;
        func_8001540C(2, 0xC7, arg0);
        break;
    case 2:
        if (g_Player.x_pos.i.hi - base < 0xA0) {
            arg0->x_pos.i.hi = base + 0x90;
            arg0->unk15 = 0x40;
        } else {
            arg0->x_pos.i.hi = base + 0xE0;
            arg0->unk15 = 0;
        }
        arg0->ext.main_64.target_x = arg0->x_pos.i.hi;
        arg0->y_pos.i.hi = arg0->ext.main_64.arena_y + 0xB3;
        arg0->ext.main_64.target_y = arg0->y_pos.i.hi;
        break;
    case 3:
        if (g_Player.x_pos.i.hi - base < 0xA0) {
            arg0->x_pos.i.hi = base + 0x110;
            arg0->unk15 = 0;
        } else {
            arg0->x_pos.i.hi = base + 0x50;
            arg0->unk15 = 0x40;
        }
        arg0->ext.main_64.target_x = arg0->x_pos.i.hi;
        arg0->y_pos.i.hi = arg0->ext.main_64.arena_y + 0x70;
        arg0->ext.main_64.target_y = arg0->y_pos.i.hi;
        break;
    }
    arg0->unk2--;
}

void func_8007D5D0(struct MainObj* arg0)
{
    switch (arg0->unk6) {
    case 0:
        arg0->ext.main_64.shot_count = 0;
        arg0->unk6++;
        cyber_peacock_start_teleport(arg0);
        func_80015D60(arg0, 0x20);
        break;
    case 1:
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->unk6++;
            arg0->unk7C = 0x3C;
            func_80015D60(arg0, 0x22);
            break;
        }
        arg0->unk20 += arg0->unk28;
        if (D_80141BD8.unk0 & 1)
            arg0->x_pos.val = ((s16)arg0->ext.main_64.target_x << 16) + arg0->unk20;
        else
            arg0->x_pos.val = ((s16)arg0->ext.main_64.target_x << 16) - arg0->unk20;
        func_80015DC8(ANIMATED_OBJECT(arg0));
        break;
    case 2:
        arg0->unk5 = 2;
        arg0->unk6 = 1;
        cyber_peacock_start_teleport(arg0);
        arg0->unk20 = 0x160000;
        arg0->ext.main_64.flash_timer = 0;
        func_80015D60(arg0, 0x22);
        break;
    }
}

void func_8007D710(struct MainObj* arg0)
{
    s16 count;

    switch (arg0->unk6) {
    case 0:
        arg0->ext.main_64.shot_count = 0;
        arg0->unk7C = 0;
        arg0->unk7 = 0;
        arg0->unk6++;
        func_80015D60(arg0, 0x21);
        func_8001540C(2, 0xC8, arg0);
        arg0->unk50 = NULL;
        arg0->unk54 = NULL;
        break;
    case 1:
        count = arg0->unk7C;
        if (count >= 3) {
            arg0->unk7C = 0x3C;
            arg0->unk6++;
            func_80015D60(arg0, 0x22);
            break;
        }
        if (arg0->animation_step.fields.relative_step < 0)
            arg0->unk7C = count + 1;
        func_80015DC8(ANIMATED_OBJECT(arg0));
        break;
    case 2:
        arg0->unk5 = 2;
        arg0->unk6 = 1;
        cyber_peacock_start_teleport(arg0);
        arg0->unk20 = 0x160000;
        arg0->ext.main_64.flash_timer = 0;
        func_80015D60(arg0, 0x22);
        break;
    }
}

extern void (*cyber_peacock_step_funcs[6])();

void func_8007D838(struct MainObj* arg0)
{
    s32 hit;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (arg0->ext.main_64.hit_count >= 7) {
        arg0->ext.main_64.hit_count = 0;
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
    }
    ((void (*)(struct MainObj*))cyber_peacock_step_funcs[arg0->unk5])(arg0);
    hit = func_8002DD04(arg0);
    if (arg0->ext.main_64.flash_timer != 0) {
        arg0->ext.main_64.flash_timer--;
        arg0->unk5C = arg0->ext.main_64.saved_health;
        if (arg0->ext.main_64.flash_timer & 1)
            arg0->unk42 |= 0x8000;
        else
            arg0->unk42 &= 0x7FFF;
    } else if (hit < 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->unk42 &= 0x7FFF;
        g_Player.unk7A = 1;
    } else if (hit > 0 && hit != 0x7F) {
        if (hit == 4 || hit == 0x24) {
            arg0->unk5 = 5;
            arg0->unk6 = 0;
            arg0->unk7 = 0;
            arg0->ext.main_64.flash_timer = 0x40;
            arg0->ext.main_64.saved_health = arg0->unk5C;
        } else {
            arg0->ext.main_64.flash_timer = 0x40;
            arg0->ext.main_64.saved_health = arg0->unk5C;
            arg0->ext.main_64.hit_count++;
        }
    }
    func_8002D9BC(arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

extern void (*D_8010D350[])(struct ItemObj*);
void func_800C5F30(struct ItemObj* arg0);

void func_800C5F90(struct ItemObj* arg0)
{
    struct MainObj* owner = arg0->unk7C.owner;

    if (owner->state != 1 || (owner->unk5 != 3 && owner->unk2 != 2)) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (owner->unk5 >= 4) {
        if (arg0->tail_ext.unk1.unk84.previous_value == 0)
            ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    D_8010D350[arg0->unk5](arg0);
    func_800C5F30(arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

extern u8 D_8010995C[4];
extern u8 D_80109960[4];
extern s16 D_80109968[8][2];
extern u8 D_80109988[8];
extern u8 D_80109990[8];

void func_800A63B0(struct ShotObj* arg0)
{
    struct MainObj* boss = arg0->backref;

    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->timer = 0xA;
    arg0->unk16 = 4;
    arg0->unk68 = (struct Unk_unk68*)D_80109960;
    arg0->unk50.data = D_8010995C;
    arg0->unk5C = 3;
    arg0->unk60 = 6;
    arg0->unk90.val = 0x6E;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->unk8A = 0;
    arg0->unk84.value = 0;
    arg0->unk54 = NULL;
    arg0->unk58.data = NULL;
    arg0->unk61 = 0;
    arg0->unk8C.word = 0;
    if (boss->unk15 != 0) {
        arg0->x_pos.i.hi -= D_80109968[arg0->unk2][0];
        arg0->unk84.value = D_80109990[arg0->unk2];
    } else {
        arg0->x_pos.i.hi += D_80109968[arg0->unk2][0];
        arg0->unk84.value = D_80109988[arg0->unk2];
    }
    arg0->y_pos.i.hi += D_80109968[arg0->unk2][1];
    func_80015D60(arg0, (arg0->unk84.value >> 1) + 0xD);
    func_8002B93C(MOVING_OBJECT(arg0), (u8)arg0->unk84.value);
    arg0->unk2C = 0;
    arg0->unk28 = 0;
    arg0->x_vel.val <<= 2;
    arg0->y_vel.val <<= 2;
}

void func_800A6510(struct ShotObj* arg0)
{
    s32 target;
    s32 direction;

    if (arg0->timer != 0) {
        arg0->timer--;
    } else if ((D_80141BD8.unk0 & 1) == 0) {
        target = func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(arg0->unk7C));
        direction = arg0->unk84.value;
        if (((direction - (target & 0xFF)) & 0x1F) >= 2) {
            direction = ((u32)((target - direction) & 0x1F) < 0x10) ? direction + 1 : direction - 1;
            arg0->unk84.value = direction & 0x1F;
            func_8002B93C(MOVING_OBJECT(arg0), direction & 0x1E);
            arg0->x_vel.val <<= 2;
            arg0->y_vel.val <<= 2;
            func_80015D60(arg0, (arg0->unk84.value >> 1) + 0xD);
        }
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_800A666C(struct ShotObj* arg0, s32 x_range, s32 y_range)
{
    struct MiscObj* misc = find_free_misc_obj();
    u8 amount;

    if (misc == NULL)
        return;
    misc->active = 0x41;
    misc->id = 0x31;
    misc->unk2 = 4;
    misc->x_pos.val = arg0->x_pos.val;
    misc->y_pos.val = arg0->y_pos.val;
    amount = x_range & get_random();
    if (get_random() & 1)
        misc->x_pos.i.hi += amount;
    else
        misc->x_pos.i.hi -= amount;
    amount = y_range & get_random();
    if (get_random() & 1)
        misc->y_pos.i.hi += amount;
    else
        misc->y_pos.i.hi -= amount;
    misc->animation_table = arg0->animation_table;
    misc->unk40 = arg0->unk40;
    misc->unk3C = arg0->unk3C;
    misc->unk42 = arg0->unk42 & 0x7FFF;
    misc->ext.misc_49.owner = arg0;
    misc->unk15 = 0;
    misc->unk16 = arg0->unk16;
}

extern u8 D_8010F1DC[4];

void func_800D1990(struct MiscObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 3;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    if (arg0->unk2 == 4) {
        arg0->ext.misc_49.timer = 0x14;
        func_80015D60(arg0, 0x1E);
        return;
    }
    func_80015D60(arg0, 0x12);
    func_8002B93C(MOVING_OBJECT(arg0), D_8010F1DC[arg0->unk2]);
    arg0->unk2C = 0x4000;
    arg0->ext.misc_49.timer = 0xA;
    arg0->unk28 = 0;
    arg0->x_vel.val <<= 1;
    arg0->y_vel.val *= 3;
}

void func_800D1A48(struct MiscObj* arg0)
{
    if (--arg0->ext.misc_49.timer == 0) {
        arg0->on_screen = 0;
        arg0->state = 2;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk2 != 4)
        func_8002B694(ANIMATED_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
}

extern struct Unk_unk68 D_801016B4;
extern void (*storm_owl_step_funcs[])(struct MainObj*);
void storm_owl_spawn_hit_flash(struct PlayerObj* arg0);

void func_800751AC(struct MainObj* arg0)
{
    arg0->unk5C = 0;
    arg0->unk60 = 6;
    arg0->unk61 = 0;
    if (engine_obj.stage != 0xC) {
        arg0->unk40 = (D_801406A8[0] >> 7) + 0xB0;
    } else {
        arg0->unk40 = (D_801406A8[0] >> 7) + 0x160;
        arg0->unk42 = 0x7888;
        arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[4];
    }
    arg0->collision_data = D_80107B78;
    arg0->animation_table = (const u8* const*)storm_owl_animations;
    arg0->unk16 = 5;
    arg0->unk68 = &D_801016C0;
    arg0->unk54 = &D_801016B4;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk50 = &D_801016B8;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk15 = g_Player.x_pos.val >= arg0->x_pos.val ? 0x40 : 0;
    func_80015D60(arg0, 1);
    arg0->state = 1;
    arg0->unk5 = 2;
    memset(&arg0->ext.main_60, 0, sizeof(arg0->ext.main_60));
    arg0->unk6 = 0;
    arg0->unk7 = 0x28;
}

static void main_60_flash(struct MainObj* arg0)
{
    storm_owl_spawn_hit_flash((struct PlayerObj*)arg0);
    arg0->collision_data = D_801060F0;
    arg0->ext.main_60.flash_timer = 0x40;
    arg0->ext.main_60.flash_mode = 1;
}

static void main_60_stagger(struct MainObj* arg0)
{
    if (arg0->unk5 != 0xB)
        func_8001540C(2, 0xBD, arg0);
    arg0->unk5 = 0xB;
    arg0->unk6 = 0;
}

void func_80075320(struct MainObj* arg0)
{
    s32 hit = func_8002DD04(arg0);

    if (arg0->unk5 != 0)
        arg0->ext.main_60.saved_unk5 = arg0->unk5;
    if (hit < 0) {
        g_Player.unk7A = 1;
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->unk42 &= 0x7FFF;
        return;
    }
    if (arg0->ext.main_60.flash_mode == 1) {
        if ((arg0->ext.main_60.flash_timer & 1) == 0)
            arg0->unk42 |= 0x8000;
        else
            arg0->unk42 &= 0x7FFF;
        if (--arg0->ext.main_60.flash_timer == 0) {
            arg0->collision_data = D_80107B78;
            arg0->ext.main_60.flash_mode = 0;
        }
    } else if (hit != 0) {
        if (engine_obj.cur_character == CHARACTER_X) {
            if (hit == 7 || hit == 0x10) {
                if (arg0->unk5 != 0xB)
                    func_8001540C(2, 0xBD, arg0);
                if (hit == 0x10) {
                    arg0->collision_data = D_80106070;
                    arg0->unk42 &= 0x7FFF;
                }
                arg0->unk5 = 0xB;
                arg0->unk6 = 0;
                arg0->active |= 4;
            } else {
                main_60_flash(arg0);
            }
        } else {
            switch (hit - 0x1A) {
            case 0:
            case 2:
            case 4:
            case 6:
            case 7:
            case 8:
                main_60_flash(arg0);
                break;
            case 9:
            case 10:
                if (arg0->ext.main_60.flash_mode == 0) {
                    arg0->ext.main_60.flash_mode = 2;
                    arg0->ext.main_60.flash_timer = 8;
                } else {
                    main_60_flash(arg0);
                }
                break;
            case 11:
                main_60_stagger(arg0);
                break;
            }
        }
    } else if (arg0->ext.main_60.flash_mode == 2) {
        if (--arg0->ext.main_60.flash_timer == 0)
            arg0->ext.main_60.flash_mode = 0;
    }
    if (arg0->unk17 < 2 && --arg0->unk7 == 0) {
        func_8001540C(2, (get_random() & 1) ? 0xB7 : 0xB8, arg0);
        arg0->unk7 = 0x28;
    }
    storm_owl_step_funcs[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x30, 0x30);
}

void func_800757F4(struct MainObj* arg0)
{
    struct BaseObj* effect = (struct BaseObj*)arg0->ext.main_60.effect;
    u16 flash;

    arg0->on_screen = 0;
    if (effect->active == 0) {
        memset(&arg0->ext.main_60, 0, sizeof(arg0->ext.main_60));
        engine_obj.enable_boss = 0;
        engine_obj.boss_ptr = NULL;
        if (engine_obj.stage == 0xC) {
            engine_obj.unkF = -0x80;
            engine_obj.character_state.bytes[engine_obj.checkpoint + 6] = 1;
            engine_obj.checkpoint += 9;
        } else {
            engine_obj.unkF = 0x10;
        }
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (effect->unk7 != 0)
        return;
    flash = arg0->unk7E;
    arg0->unk7E = flash - 1;
    if (flash == 0) {
        arg0->unk7E = 5;
        arg0->unk42 ^= 0x8000;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x60, 0x60);
}

void storm_owl_spawn_intro_wind(struct MainObj* arg0);

void func_80075944(struct MainObj* arg0)
{
    func_80015D60(arg0, 0);
    if (engine_obj.stage == 7) {
        arg0->unk15 = 0x40;
        arg0->x_pos.i.hi = background_objects[0].x_pos.i.hi + 0x20;
    } else {
        arg0->unk15 = 0;
        arg0->x_pos.i.hi = background_objects[0].x_pos.i.hi + 0x120;
    }
    arg0->unk24 = -0x20000;
    arg0->y_pos.i.hi = background_objects[0].y_pos.i.hi - 0x20;
    storm_owl_spawn_intro_wind(arg0);
    func_8001540C(2, 0xB4, arg0);
    arg0->unk6++;
}

void func_80075C6C(struct MainObj* arg0)
{
    const Main60Waypoint* waypoint;
    u8 index;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 1);
    index = (engine_obj.stage != 7) * 2;
    arg0->ext.main_60.corner = index;
    waypoint = &storm_owl_waypoints[index];
    func_8002B93C(MOVING_OBJECT(arg0),
        func_8002B7B0(OBJECT_HEADER(arg0), (waypoint->x + background_objects[0].x_pos.i.hi) << 16,
            (waypoint->y + background_objects[0].y_pos.i.hi) << 16)
            & 0xFF);
    arg0->unk20 <<= 1;
    arg0->unk24 <<= 1;
    arg0->unk6++;
}

void func_80075E78(struct MainObj* arg0)
{
    const Main60Waypoint* waypoint = &storm_owl_waypoints[arg0->ext.main_60.corner];
    s32 target_x = (waypoint->x + background_objects[0].x_pos.i.hi) << 16;
    s32 target_y = (waypoint->y + background_objects[0].y_pos.i.hi) << 16;
    s32 dx;
    s32 dy;
    u8 next;

    func_8002B93C(MOVING_OBJECT(arg0), func_8002B7B0(OBJECT_HEADER(arg0), target_x, target_y) & 0xFF);
    arg0->unk20 <<= 1;
    arg0->unk24 <<= 1;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    dx = target_x - arg0->x_pos.val;
    if (dx >= 0 ? dx > 0x3FFFF : arg0->x_pos.val - target_x > 0x3FFFF)
        return;
    dy = target_y - arg0->y_pos.val;
    if (dy >= 0 ? dy > 0x3FFFF : arg0->y_pos.val - target_y > 0x3FFFF)
        return;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    if (arg0->ext.main_60.pattern[0] == 0xFF)
        storm_owl_choose_pattern(arg0);
    next = *arg0->ext.main_60.pattern++;
    arg0->unk5 = next;
    if (arg0->unk5 == 3)
        arg0->unk6++;
    else
        arg0->unk6 = 0;
}

void storm_owl_choose_corner(struct MainObj* arg0);

static void main_60_release(struct MainObj* arg0)
{
    g_Player.unkBA = 0;
    arg0->unk60 = 6;
    arg0->unk68 = &D_801016C0;
    arg0->unk50 = &D_801016B8;
    arg0->unk62 = 0;
    arg0->unk16 = 5;
}

void func_800760C4(struct MainObj* arg0)
{
    s16 distance;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    arg0->unk24 += 0x400;
    distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if ((distance < 0 ? -distance : distance) > 0x30)
        return;
    if ((get_random() & 7) < 5) {
        arg0->unk5 = g_Player.y_pos.i.hi < arg0->y_pos.i.hi ? 6 : 4;
        arg0->unk6 = 0;
        arg0->unk20 = 0;
        arg0->unk24 = 0;
    } else {
        arg0->ext.main_60.corner ^= 2;
        arg0->unk6++;
    }
}

void func_80076364(struct MainObj* arg0)
{
    s16 distance;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (arg0->y_pos.i.hi + 0x14 >= g_Player.y_pos.i.hi) {
        arg0->unk20 = arg0->unk15 != 0 ? 0x20000 : -0x20000;
        arg0->unk24 = -0x10000;
        func_80015D60(arg0, 1);
        main_60_release(arg0);
        arg0->unk6 = 5;
        return;
    }
    if (g_Player.unkBA != 0) {
        func_8001540C(2, 0xBA, arg0);
        distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
        if ((distance < 0 ? -distance : distance) < 8)
            arg0->unk20 = 0;
        else
            arg0->unk20 = arg0->x_pos.i.hi < g_Player.x_pos.i.hi ? 0x10000 : -0x10000;
        arg0->unk24 = 0;
        arg0->unk6++;
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 1) {
        storm_owl_choose_corner(arg0);
        main_60_release(arg0);
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}

void func_8007651C(struct MainObj* arg0)
{
    s16 x;
    s16 background_x;
    s16 distance;
    s32 stop = 0;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if ((distance < 0 ? -distance : distance) >= 8)
        return;
    x = arg0->x_pos.i.hi;
    background_x = background_objects[0].x_pos.i.hi;
    if (x < background_x + 0x40 && arg0->unk20 < 0)
        stop = 1;
    else if (background_x + 0x100 < x && arg0->unk20 > 0)
        stop = 1;
    else if (arg0->unk15 == 0 ? arg0->unk20 > 0 : arg0->unk20 < 0)
        stop = 1;
    if (stop)
        arg0->unk20 = 0;
    arg0->unk24 = 0x10000;
    arg0->unk7C = 0x3C;
    arg0->unk6++;
}

void func_800766FC(struct MainObj* arg0)
{
    s16 background_x;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    background_x = background_objects[0].x_pos.i.hi;
    if (!(background_x + 0x10 < g_Player.x_pos.i.hi && g_Player.x_pos.i.hi < background_x + 0x130)) {
        arg0->unk20 = 0;
        arg0->unk28 = 0;
    }
    g_Player.x_pos.i.hi = arg0->x_pos.i.hi;
    g_Player.y_pos.i.hi = arg0->y_pos.i.hi + 0x1C;
    CollisionRelated(PLAYER_OBJECT(arg0));
    if ((arg0->unk70 & 8) == 0)
        return;
    func_8001540C(2, 0xBB, arg0);
    func_80028BAC(8, 4, 1);
    func_80036470(9);
    func_80015D60(arg0, 1);
    arg0->unk20 = arg0->unk15 != 0 ? 0x20000 : -0x20000;
    arg0->unk24 = -0x10000;
    g_Player.unkBA = 0;
    arg0->unk68 = &D_801016C0;
    arg0->unk62 = 0;
    arg0->unk50 = &D_801016B8;
    arg0->unk6++;
}

void storm_owl_spawn_volley_feather(struct MainObj* arg0, s8 arg1);

void func_80076D14(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    if (++arg0->ext.main_60.shot_count >= 4) {
        arg0->unk7C = 0x3C;
        arg0->unk6++;
    } else {
        arg0->unk7C = 0x3D;
    }
    storm_owl_spawn_volley_feather(arg0, arg0->ext.main_60.shot_count);
    func_8001540C(2, 0xB5, arg0);
}

void func_80077318(struct MainObj* arg0)
{
    s32 target_x = (background_objects[0].x_pos.i.hi + 0xA0) << 16;
    s32 target_y = (background_objects[0].y_pos.i.hi + 0x70) << 16;
    s32 dx;
    s32 dy;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    func_8002B93C(MOVING_OBJECT(arg0), func_8002B7B0(OBJECT_HEADER(arg0), target_x, target_y) & 0xFF);
    arg0->unk20 <<= 1;
    arg0->unk24 <<= 1;
    dx = arg0->x_pos.val - target_x;
    if (dx >= 0 ? dx > 0x3FFFF : target_x - arg0->x_pos.val > 0x3FFFF)
        return;
    dy = arg0->y_pos.val - target_y;
    if (dy >= 0 ? dy > 0x3FFFF : target_y - arg0->y_pos.val > 0x3FFFF)
        return;
    func_80015D60(arg0, 6);
    arg0->unk6++;
}

void func_80077580(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    if ((get_random() & 7) < 3) {
        arg0->unk6++;
        func_8001540C(2, 0xBC, arg0);
    } else {
        arg0->unk6 += 2;
    }
    arg0->unk7C = 0x1E;
}

static void main_60_shot_setup(struct ShotObj* shot, struct MainObj* arg0, s8 id, s8 subtype, s8 layer)
{
    shot->active = 0x41;
    shot->id = id;
    shot->unk2 = subtype;
    shot->unk7C = (struct WeaponObj*)arg0;
    shot->animation_table = (u32**)storm_owl_animations;
    shot->unk42 = arg0->unk42;
    shot->unk3C = (void*)arg0->sprite_frames;
    shot->unk40 = arg0->unk40;
    shot->unk16 = layer;
    shot->bg_offset = arg0->bg_offset;
    shot->unk15 = arg0->unk15;
}

void func_80078180(struct MainObj* arg0)
{
    struct ShotObj* shot;
    u32 i;

    if (arg0->ext.main_60.storm_active == 1) {
        if (--arg0->unk7E != 0)
            return;
        for (i = 0; i < 4; i++) {
            shot = find_free_shot_obj();
            if (shot != NULL)
                main_60_shot_setup(shot, arg0, 0x25, i + 5, 5);
        }
    }
    arg0->unk7E = 10;
}

void func_80078314(struct MainObj* arg0)
{
    static const s16 x_offsets[3] = { 0, -0x30, 0x30 };
    static const s16 shot_timers[3] = { 0x20, 0x28, 0x28 };
    struct VisualObj* visual;
    struct ShotObj* shot;
    u32 i;

    for (i = 0; i < 3; i++) {
        visual = find_free_visual_obj();
        if (visual == NULL)
            continue;
        visual->active = 0x41;
        visual->id = 0x1C;
        visual->unk2 = 1;
        visual->unk50 = (struct PlayerObj*)arg0;
        visual->animation_table = (u32**)storm_owl_animations;
        visual->unk42 = arg0->unk42;
        visual->unk3C = (void*)arg0->sprite_frames;
        visual->unk40 = arg0->unk40;
        visual->unk16 = 2;
        visual->bg_offset = arg0->bg_offset;
        visual->unk15 = arg0->unk15;
        visual->x_pos.i.hi = g_Player.x_pos.i.hi + x_offsets[i];
        visual->unk5C.fields.mode = i;
        visual->y_pos.i.hi = background_objects[0].y_pos.i.hi + 0x60;
    }
    for (i = 0; i < 3; i++) {
        shot = find_free_shot_obj();
        if (shot == NULL)
            continue;
        main_60_shot_setup(shot, arg0, 0x26, 5, 2);
        shot->timer = shot_timers[i];
        shot->x_pos.i.hi = g_Player.x_pos.i.hi + x_offsets[i];
        shot->y_pos.i.hi = background_objects[0].y_pos.i.hi + 0x150;
    }
}

void func_800B3FD4(struct VisualObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk50;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk2 >= 2) {
        if (arg0->unk2 == 2) {
            if (owner->ext.main_60.storm_active == 0) {
                arg0->state++;
                return;
            }
        } else {
            arg0->x_pos.val = owner->x_pos.val;
            arg0->y_pos.val = owner->y_pos.val;
            if (owner->ext.main_60.flash_mode == 0) {
                arg0->state++;
                return;
            }
        }
    } else if (--arg0->unk54 == 0) {
        if (arg0->unk2 == 0) {
            arg0->state++;
        } else {
            switch (arg0->unk5C.value) {
            case 0:
                func_80015D60(arg0, 0x1B);
                arg0->unk54 = 0xC;
                arg0->unk5C.value++;
                break;
            case 1:
                func_80015D60(arg0, 0x1D);
                arg0->unk54 = 0x3E;
                arg0->unk5C.value++;
                break;
            case 2:
                func_80015D60(arg0, 0x1C);
                arg0->unk54 = 0xC;
                arg0->unk5C.value++;
                break;
            default:
                arg0->state++;
                break;
            }
        }
    }
    if (owner->active == 0 || owner->state == 2 || (arg0->unk2 == 2 && owner->unk5 == 0xB)) {
        arg0->state++;
        return;
    }
    if (arg0->unk2 == 0)
        func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
    else
        func_8002B318(BASE_OBJECT(arg0), 0x20, 0x80);
}

extern s8 D_8010979C[4];
extern u16 D_801097A0[11][2];

void func_800A3CB4(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;
    s16 background_x;
    s16 background_y;
    u16 best;
    u16 dx;
    u16 dy;
    u8 index;
    u8 i;

    arg0->on_screen = 1;
    arg0->unk58.data = (u8*)D_801060F0;
    arg0->unk60 = 6;
    arg0->unk68 = NULL;
    arg0->unk54 = (u8*)D_8010979C;
    arg0->unk5C = 0;
    arg0->unk84.value = 0;
    arg0->unk8C.word = 0;
    arg0->state++;
    arg0->unk42 &= 0x7FFF;
    func_80015D60(arg0, 0xD);
    arg0->unk50.data = (u8*)D_8010979C;
    arg0->x_pos.i.hi = owner->x_pos.i.hi + (owner->unk15 != 0 ? 0x26 : -0x26);
    arg0->y_pos.i.hi = owner->y_pos.i.hi + 6;
    if (arg0->unk2 == 0) {
        func_8002B93C(MOVING_OBJECT(arg0), func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player)) & 0xFF);
        arg0->x_vel.val <<= 2;
        arg0->y_vel.val <<= 2;
        return;
    }
    if (arg0->unk2 >= 5) {
        arg0->x_pos.i.hi = owner->x_pos.i.hi;
        arg0->y_pos.i.hi = owner->y_pos.i.hi;
        func_8002B93C(MOVING_OBJECT(arg0), (owner->ext.main_60.storm_timer + (arg0->unk2 - 5) * 8 + 4) & 0x1F);
        arg0->x_vel.val <<= 3;
        arg0->y_vel.val <<= 3;
        return;
    }
    background_x = background_objects[0].x_pos.i.hi;
    background_y = background_objects[0].y_pos.i.hi;
    if (arg0->unk2 == 1) {
        best = 0xFFFF;
        index = 0;
        for (i = 0; i < 11; i++) {
            s32 point_x = background_x + D_801097A0[i][0];
            s32 point_y = background_y + D_801097A0[i][1];
            dx = g_Player.x_pos.i.hi - point_x >= 0 ? g_Player.x_pos.i.hi - point_x : point_x - g_Player.x_pos.i.hi;
            dy = g_Player.y_pos.i.hi - point_y >= 0 ? g_Player.y_pos.i.hi - point_y : point_y - g_Player.y_pos.i.hi;
            if ((u16)(dx + dy) < best) {
                best = dx + dy;
                index = i;
            }
        }
        arg0->unk84.value = index;
    } else {
        do {
            arg0->unk84.value = (u8)get_random() % 11;
        } while ((owner->ext.main_60.feather_mask >> arg0->unk84.value) & 1);
    }
    owner->ext.main_60.feather_mask += 1 << arg0->unk84.value;
    func_8002B93C(MOVING_OBJECT(arg0),
        func_8002B7B0(OBJECT_HEADER(arg0), (background_x + D_801097A0[arg0->unk84.value][0]) << 16,
            (background_y + D_801097A0[arg0->unk84.value][1]) << 16)
            & 0xFF);
    arg0->x_vel.val <<= 1;
    arg0->y_vel.val <<= 1;
}

void func_800A3FEC(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;
    s32 target_x;
    s32 target_y;
    s32 d;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    func_8002D9BC(arg0);
    func_8002DD04((struct MainObj*)arg0);
    if (arg0->unk2 != 0 && arg0->unk2 < 5) {
        if (owner->ext.main_60.feathers_holding == 0) {
            target_x = background_objects[0].x_pos.i.hi + D_801097A0[arg0->unk84.value][0];
            target_y = background_objects[0].y_pos.i.hi + D_801097A0[arg0->unk84.value][1];
            func_8002B93C(MOVING_OBJECT(arg0),
                func_8002B7B0(OBJECT_HEADER(arg0), target_x << 16, target_y << 16) & 0xFF);
            arg0->x_vel.val <<= 1;
            arg0->y_vel.val <<= 1;
            d = arg0->x_pos.i.hi - target_x;
            if ((d < 0 ? -d : d) < 8)
                arg0->x_vel.val = 0;
            d = arg0->y_pos.i.hi - target_y;
            if ((d < 0 ? -d : d) < 8)
                arg0->y_vel.val = 0;
        } else if (arg0->unk8C.word == 0) {
            func_8002B93C(MOVING_OBJECT(arg0), func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player)) & 0xFF);
            arg0->unk8C.word = 1;
            arg0->x_vel.val *= 5;
            arg0->y_vel.val *= 5;
        }
    }
    if (owner->state == 2 || owner->active == 0 || func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) != 0) {
        arg0->state++;
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
}

extern u8 D_801097DC[4];
extern u8 D_801097E0[4];
void func_800A46FC(struct ShotObj* arg0);

void func_800A42C8(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;
    s16 dx = 0;
    s16 dy = 0;

    arg0->unk58.data = (u8*)D_80105FF0;
    arg0->unk60 = 6;
    arg0->unk54 = D_801097DC;
    arg0->unk50.data = D_801097DC;
    arg0->unk84.value = 4;
    arg0->state++;
    arg0->on_screen = 1;
    arg0->unk68 = NULL;
    arg0->unk5C = 1;
    arg0->unk42 &= 0x7FFF;
    switch ((u8)arg0->unk2) {
    case 0:
        func_80015D60(arg0, 0xF);
        arg0->x_vel.val = 0x45000;
        arg0->y_vel.val = 0x45000;
        dx = 0xB;
        dy = -0x15;
        break;
    case 1:
        func_80015D60(arg0, 0x10);
        arg0->x_vel.val = 0x52800;
        arg0->y_vel.val = 0x2A000;
        dx = 0x10;
        dy = -0x13;
        break;
    case 2:
        func_80015D60(arg0, 0x11);
        arg0->x_vel.val = 0x60000;
        arg0->y_vel.val = 0;
        if (owner->unk17 == 4) {
            dx = 0x19;
            dy = -6;
        } else {
            dx = 0x13;
            dy = -0xD;
        }
        break;
    case 3:
        func_80015D60(arg0, 0x12);
        arg0->x_vel.val = 0x52800;
        arg0->y_vel.val = -0x2A000;
        dx = 0x19;
        dy = 0;
        break;
    case 4:
        func_80015D60(arg0, 0x13);
        arg0->x_vel.val = 0x45000;
        arg0->y_vel.val = -0x45000;
        dx = 0x14;
        dy = 5;
        break;
    case 5:
        arg0->unk58.data = (u8*)D_80105FF0;
        arg0->unk50.data = D_801097E0;
        arg0->unk54 = NULL;
        func_80015D60(arg0, 0x1D);
        arg0->unk60 = 9;
        arg0->on_screen = 0;
        arg0->x_vel.val = 0;
        arg0->y_vel.val = 0;
        arg0->unk28 = 0;
        arg0->unk2C = 0;
        arg0->unk84.value = 0;
        arg0->timer = 1;
        break;
    }
    if (arg0->unk2 >= 5)
        return;
    if (owner->unk15 == 0) {
        arg0->x_pos.i.hi = owner->x_pos.i.hi - dx;
        arg0->x_vel.val = -arg0->x_vel.val;
    } else {
        arg0->x_pos.i.hi = owner->x_pos.i.hi + dx;
    }
    arg0->y_pos.i.hi = owner->y_pos.i.hi + dy;
}

void func_800A4518(struct ShotObj* arg0)
{
    struct BaseObj* owner = (struct BaseObj*)arg0->unk7C;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    func_8002D9BC(arg0);
    if (arg0->unk2 < 5) {
        func_800A46FC(arg0);
        if (func_8002DD04((struct MainObj*)arg0) < 0) {
            func_800AF808(BASE_OBJECT(arg0));
            arg0->state++;
            return;
        }
    } else {
        if (owner->state == 2) {
            arg0->state++;
            return;
        }
        if (--arg0->timer == 0) {
            switch (arg0->unk84.value) {
            case 0:
                arg0->unk84.value = 1;
                arg0->timer = 0x2D;
                arg0->y_vel.val = 0;
                break;
            case 1:
                arg0->timer = 0xC;
                arg0->unk84.value = 2;
                arg0->y_vel.val = 0x150000;
                break;
            case 2:
                arg0->unk84.value = 3;
                arg0->timer = 0x3E;
                arg0->y_vel.val = 0;
                break;
            case 3:
                arg0->unk84.value = 4;
                arg0->y_vel.val = 0x150000;
                arg0->timer = 0xC;
                break;
            }
        }
    }
    if (owner->active == 0)
        arg0->state++;
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, arg0->unk2 < 5 ? 0x20 : 0x80) != 0) {
        arg0->state++;
        return;
    }
    if (arg0->unk2 < 5)
        func_8002B318(BASE_OBJECT(arg0), 0x10, 0x10);
}

extern struct Unk_unk68 D_80108990[];
void func_8009633C(struct WeaponObj* arg0, struct PlayerObj* arg1);
void func_80096584(struct WeaponObj* arg0, struct PlayerObj* arg1);

s32 func_8009663C(struct WeaponObj* arg0, struct PlayerObj* player, struct MainObj* target)
{
    s32 slot;

    if (target == player->weapon_06_slots[0] || target == player->weapon_06_slots[1] || target == player->weapon_06_slots[2])
        return 0;
    if (target->active == 0 || (target->active & 4) || target->unk7A != 0 || target->unk54 == NULL || target->unk5C == 0)
        return 0;
    slot = player->weapon_06_slots[2] == NULL ? 2 : -1;
    if (player->weapon_06_slots[1] == NULL)
        slot = 1;
    if (player->weapon_06_slots[0] == NULL)
        slot = 0;
    if (slot == -1)
        return 0;
    if (func_8002BB80((struct MainObj*)arg0, target) == 0)
        return 0;
    if (func_80036DA0(1, 6, slot, (struct PlayerObj*)target) != NULL) {
        player->weapon_06_slots[slot] = target;
        player->unk99++;
        func_8001540C(0, 0x1C, arg0);
    }
    arg0->unk50 = NULL;
    func_8002B318(BASE_OBJECT(arg0), 0x18, 0x18);
    return 1;
}

void func_800963E8(struct WeaponObj* arg0, struct PlayerObj* player)
{
    s32 hidden = player->charge_levels[6] == 0;
    u32 i;

    if (!(player->unkA7 & 1) && player->charge_levels[6] < D_800F8BE0.charge.initial_thresholds[0])
        hidden = 1;
    if (player->unk99 >= 3)
        hidden = 1;
    if (player->unkA4 > 0)
        hidden = 1;
    if (player->unk8E != 0 && (player->unk97 == 6 || player->unk97 == 0xF))
        hidden = 1;
    if (hidden) {
        arg0->on_screen = 0;
        return;
    }
    arg0->on_screen = 1;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->ext.weapon_6.direction != 0 && (player->input.buttons.held & 4))
        arg0->ext.weapon_6.direction--;
    if (arg0->ext.weapon_6.direction != 0x10 && (player->input.buttons.held & 8))
        arg0->ext.weapon_6.direction++;
    func_80096584(arg0, player);
    arg0->unk50 = D_80108990;
    for (i = 0; i < COUNT(main_objects); i++) {
        if (func_8009663C(arg0, player, &main_objects[i]))
            return;
    }
    arg0->unk50 = NULL;
}

void func_800961B0(struct WeaponObj* arg0)
{
    struct PlayerObj* player = &g_Player;
    struct MainObj* owner;
    s32 reset;

    if (arg0->unk2 == 3) {
        reset = engine_obj.unkF != 0;
        if (player->unk93 != 6)
            reset = 1;
        if (player->unk5C == 0)
            reset = 1;
        if (reset)
            ZeroObjectState(OBJECT_HEADER(arg0));
        else if (arg0->state == 0)
            func_8009633C(arg0, player);
        else
            func_800963E8(arg0, player);
        return;
    }
    owner = (struct MainObj*)arg0->owner;
    reset = player->unkC3 != 0;
    if (player->unkC4 != 0 || player->unk93 != 6 || player->unkBF != 0 || player->unk5C == 0 || owner->active == 0 || owner->unk5C == 0)
        reset = 1;
    if (reset)
        arg0->state = 3;
    arg0->x_pos.val = owner->x_pos.val;
    arg0->y_pos.val = owner->y_pos.val;
    ((void (*)(struct WeaponObj*, struct PlayerObj*, struct PlayerObj*))D_8010899C[arg0->state])(
        arg0, player, (struct PlayerObj*)owner);
}

void func_800D69A8(struct QuadObj* arg0, struct PlayerObj* player, struct PlayerObj* target)
{
    const s8* offsets = (const s8*)&D_8011B230 + player->animation_step.fields.frame_index * 2;
    s32 dx = target->x_pos.val - player->x_pos.val;
    s32 dy = target->y_pos.val - player->y_pos.val;
    s16 x;
    s16 y;
    s16 near_x;
    s16 far_x;
    s16 near_y;
    s16 far_y;

    if (player->unk15 == 0)
        x = player->x_pos.i.hi + offsets[0] + 3;
    else
        x = player->x_pos.i.hi - offsets[0] - 3;
    near_x = target->x_pos.i.hi - (x + 6);
    far_x = target->x_pos.i.hi - (x - 6);
    arg0->x_pos.i.hi = x;
    arg0->unk14.val = 0;
    arg0->unk18.val = 0;
    y = player->y_pos.i.hi + offsets[1];
    arg0->y_pos.i.hi = y;
    near_y = target->y_pos.i.hi - (y + 6);
    far_y = target->y_pos.i.hi - (y - 6);
    if (dx < 0) {
        arg0->unk1C.i.hi = far_x;
        arg0->unk24.i.hi = near_x;
        arg0->unk2C.i.hi = near_x;
    } else {
        arg0->unk1C.i.hi = near_x;
        arg0->unk24.i.hi = far_x;
        arg0->unk2C.i.hi = far_x;
    }
    if (dy < 0) {
        arg0->unk20.i.hi = near_y;
        arg0->unk28.i.hi = near_y;
        arg0->unk30.i.hi = far_y;
    } else {
        arg0->unk20.i.hi = far_y;
        arg0->unk28.i.hi = far_y;
        arg0->unk30.i.hi = near_y;
    }
}

void func_800CF184(struct MiscObj* arg0)
{
    struct BaseObj* source = arg0->ext.pointer.unk50;

    arg0->on_screen = 1;
    arg0->unk16 = 6;
    arg0->state++;
    if ((u8)arg0->unk2 < 5)
        func_80015D60(arg0, 0x14 + arg0->unk2);
    arg0->x_pos.i.hi = source->x_pos.i.hi;
    arg0->y_pos.i.hi = source->y_pos.i.hi;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk15 = source->unk15;
    is_on_screen(BASE_OBJECT(arg0));
}

struct MainObj* func_8006FB20(struct MainObj* arg0, s32 dx, s32 dy)
{
    struct VisualObj* visual = find_free_visual_obj();

    if (visual == NULL)
        return NULL;
    visual->active = 0x41;
    visual->id = 0x17;
    visual->unk2 = 1;
    visual->x_pos.i.hi = arg0->x_pos.i.hi + dx;
    visual->y_pos.i.hi = arg0->y_pos.i.hi + dy;
    visual->unk40 = arg0->unk40;
    visual->animation_table = (u32**)arg0->animation_table;
    visual->unk3C = (void*)arg0->sprite_frames;
    visual->unk42 = arg0->unk42;
    visual->unk15 = arg0->unk15;
    visual->unk50 = (struct PlayerObj*)arg0;
    visual->x_vel.val = 0;
    visual->y_vel.val = 0;
    visual->bg_offset = arg0->bg_offset;
    return (struct MainObj*)visual;
}

extern void* jet_stingray_animations[45];
extern struct Unk_unk68 D_80100884;
extern struct Unk_unk68 D_8010084C;
extern struct Unk_unk68 D_80100850;
s32 jet_stingray_at_target(struct MainObj* arg0, s32 arg1, s32 arg2);

void func_8006FD50(struct MainObj* arg0)
{
    struct BackgroundObj* background;

    if (g_Player.unkC4 != 0)
        return;
    func_80036AE4(0x14, 0x40);
    arg0->on_screen = 0;
    arg0->unk54 = NULL;
    arg0->unk50 = NULL;
    arg0->unk68 = NULL;
    arg0->collision_data = D_801079F8;
    arg0->unk5++;
    arg0->bg_offset = g_Player.bg_offset;
    if (engine_obj.stage != 0xC) {
        arg0->unk40 = (D_801406A8[0] >> 7) + 0xB0;
    } else {
        arg0->unk40 = (D_801406A8[0] >> 7) + 0x160;
        arg0->unk42 = 0x7888;
        arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[4];
    }
    arg0->animation_table = (const u8* const*)jet_stingray_animations;
    arg0->unk16 = 6;
    arg0->unk5C = 0;
    arg0->unk60 = 4;
    background = &background_objects[arg0->bg_offset];
    arg0->x_pos.val = (background->unk1E + 0x10B) << 16;
    arg0->unk62 = 0;
    arg0->unk63 = 2;
    arg0->ext.main_56.object.effect = NULL;
    arg0->ext.main_56.pattern = NULL;
    arg0->y_pos.val = (background_objects[arg0->bg_offset].unk22 + 0x130) << 16;
}

void func_80070514(struct MainObj* arg0)
{
    struct BackgroundObj* background = &background_objects[arg0->bg_offset];
    s16 target_x;
    s16 target_y;

    if (arg0->x_pos.val < background->x_pos.val + 0xA00000) {
        arg0->unk15 = 0x40;
        target_x = background->unk1E + 0x40;
    } else {
        arg0->unk15 = 0;
        target_x = background->unk1E + 0x120;
    }
    target_y = background->unk22 + 0x98;
    func_8002B93C(MOVING_OBJECT(arg0), func_8002B7B0(OBJECT_HEADER(arg0), target_x << 16, target_y << 16) & 0xFF);
    arg0->unk20 <<= 1;
    arg0->unk24 <<= 1;
    if (jet_stingray_at_target(arg0, target_x, target_y) & 0xFF) {
        arg0->unk20 = 0;
        arg0->unk24 = 0;
        arg0->unk7C = 0;
        arg0->unk6++;
    }
}

void func_80070778(struct MainObj* arg0)
{
    switch (arg0->unk6) {
    case 0:
        arg0->unk67 = -1;
        arg0->unk68 = &D_80100884;
        arg0->unk20 = 0;
        arg0->unk24 = -0x20000;
        arg0->ext.main_56.flags &= 2;
    case 1:
        if (arg0->unk70 & 8) {
            arg0->unk6++;
            arg0->unk67 = 0;
            arg0->unk24 = 0;
            func_80015D60(arg0, 0);
            arg0->unk7C = 0x28;
            arg0->unk50 = &D_8010084C;
            arg0->unk54 = &D_80100850;
        }
        break;
    case 2:
        if (--arg0->unk7C == 0) {
            arg0->unk5 = 4;
            arg0->unk6 = 0;
        }
        break;
    }
    CollisionRelated(PLAYER_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if ((jet_stingray_check_surface(PLAYER_OBJECT(arg0), 0, 0) & 0xFF) == 3 && !(arg0->ext.main_56.flags & 2)) {
        jet_stingray_spawn_splash(arg0);
        arg0->ext.main_56.flags |= 2;
    }
}

extern u16 jet_stingray_vortex_debris_offsets[24];
extern s8 jet_stingray_splash_x_offsets[4];
extern s8 jet_stingray_splash_y_offsets[4];
extern void (*jet_stingray_ambush_funcs[])(struct MainObj*);

void func_80070A38(struct MainObj* arg0)
{
    struct MainObj* debris;
    s16 dx;
    s16 dy;
    u32 roll;

    if (g_Player.x_pos.i.hi < arg0->x_pos.i.hi)
        g_Player.x_pos.i.hi += 3;
    else
        g_Player.x_pos.i.hi -= 3;
    if (arg0->y_pos.i.hi < g_Player.y_pos.i.hi)
        g_Player.y_pos.i.hi -= 1;
    else
        g_Player.y_pos.i.hi += 1;
    g_Player.y_pos.i.hi += 1;
    dy = g_Player.y_pos.i.hi - arg0->y_pos.i.hi;
    dx = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if ((dy < 0 ? -dy : dy) < 0x30 && (dx < 0 ? -dx : dx) < 0x20) {
        arg0->ext.main_56.vortex_result = 2;
        arg0->unk6++;
        return;
    }
    if (--arg0->unk7C == 0) {
        arg0->ext.main_56.vortex_result = 1;
        arg0->unk6++;
    }
    if (D_80141BD8.unk0 % 5 != 0)
        return;
    debris = func_8006FB20(arg0, 0, 0);
    roll = get_random();
    if (debris != NULL)
        debris->x_pos.i.hi = background_objects[0].unk1E + jet_stingray_vortex_debris_offsets[(arg0->unk15 != 0 ? 8 : 0) + (roll & 7)];
    roll = get_random();
    if (debris == NULL)
        return;
    debris->y_pos.i.hi = background_objects[0].unk22 + jet_stingray_vortex_debris_offsets[0x10 + (roll & 7)];
    debris->unk20 = arg0->unk15 != 0 ? -0x38000 : 0x38000;
    debris->unk24 = arg0->y_pos.i.hi < debris->y_pos.i.hi ? 0x10000 : -0x10000;
}

void func_800710D4(struct MainObj* arg0)
{
    struct MainObj* debris;
    u8 tile;
    s8 i;

    jet_stingray_ambush_funcs[arg0->unk6](arg0);
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    tile = jet_stingray_check_surface(PLAYER_OBJECT(arg0), 0, 0);
    if (tile == 0)
        return;
    if (tile < 3) {
        if (arg0->ext.main_56.flags & 1)
            return;
        for (i = 0; i < 4; i++) {
            debris = func_8006FB20(arg0, jet_stingray_splash_x_offsets[get_random() & 3], 0);
            if (debris != NULL)
                debris->y_pos.i.hi = jet_stingray_splash_y_offsets[get_random() & 3] + 0x13B;
            else
                get_random();
        }
        arg0->ext.main_56.flags |= 1;
    } else if (tile == 3) {
        if (arg0->ext.main_56.flags & 2)
            return;
        jet_stingray_spawn_splash(arg0);
        arg0->ext.main_56.flags |= 2;
    }
}

void func_80071740(struct MainObj* arg0)
{
    struct ShotObj* shot;

    switch (arg0->unk7) {
    case 0:
        arg0->unk7 = 1;
        func_8001540C(2, 0xB2, arg0);
        arg0->unk7C = 0x32;
    case 1:
        if (--arg0->unk7C == 0) {
            arg0->unk7E = arg0->unk5 == 9 ? 4 : 3;
            arg0->unk7++;
            func_80015D60(arg0, 9);
        }
        break;
    case 2:
        if (arg0->animation_step.fields.event == 1) {
            func_8001540C(2, 0xB1, arg0);
            arg0->animation_step.fields.event = 0;
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0x22;
                shot->unk2 = arg0->unk5 == 9 ? 3 : 2;
                shot->unk40 = arg0->unk40;
                shot->animation_table = (u32**)arg0->animation_table;
                shot->unk3C = (void*)arg0->sprite_frames;
                shot->unk42 = arg0->unk42;
                shot->bg_offset = arg0->bg_offset;
                shot->x_pos.val = arg0->x_pos.val;
                shot->y_pos.val = arg0->y_pos.val;
                shot->unk7C = (struct WeaponObj*)arg0;
                shot->unk15 = arg0->unk15;
            }
        }
        if (arg0->animation_step.fields.event == 2) {
            arg0->animation_step.fields.event = 0;
            arg0->unk7C = 0x14;
            arg0->unk6++;
        }
        break;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

extern void (*jet_stingray_step_funcs[])(struct MainObj*);

void func_80071D30(struct MainObj* arg0)
{
    s32 hit = func_8002DD04(arg0);
    s32 flash = 0;

    if (arg0->ext.main_56.flash_timer != 0) {
        arg0->ext.main_56.flash_timer--;
        if (arg0->ext.main_56.flash_timer & 1)
            arg0->unk42 |= 0x8000;
        else
            arg0->unk42 &= 0x7FFF;
    } else {
        arg0->collision_data = D_801079F8;
    }
    if (hit < 0) {
        arg0->unk5 = 0;
        arg0->state++;
        arg0->unk42 &= 0x7FFF;
        g_Player.unk7A = 1;
        return;
    }
    if (hit != 0) {
        if (engine_obj.cur_character == CHARACTER_X) {
            if (hit == 0xC || hit == 3) {
                arg0->state = 3;
                arg0->unk6 = 0;
                arg0->unk7 = 0;
                return;
            }
            flash = hit != 0x7F;
        } else {
            if (hit == 0x22) {
                arg0->state = 3;
                arg0->unk6 = 0;
                arg0->unk7 = 0;
                return;
            }
            flash = hit != 0x7F && hit != 0x19 && hit != 0x1A;
        }
    }
    if (flash && arg0->ext.main_56.flash_timer == 0) {
        arg0->collision_data = D_801060F0;
        arg0->ext.main_56.flash_timer = 0x40;
    }
    jet_stingray_step_funcs[arg0->unk5](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x80, 0x80);
    func_8002D9BC(arg0);
}

extern struct Unk_unk68 D_80108848[];
extern u32* D_8011C094[];

void func_80093D78(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    arg0->unk50 = D_80108848;
    arg0->unk38 = (u8*)player_gfx + player_gfx[3];
    arg0->animation_table = D_8011C094;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 3;
    arg0->unk15 = 0;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0xB];
    arg0->x_pos.i.hi = g_Player.x_pos.i.hi + (g_Player.unk15 != 0 ? -5 : 5);
    arg0->unk67 = 1;
    arg0->x_vel.val = 0;
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk49 = 0;
    arg0->y_pos.i.hi = g_Player.y_pos.i.hi - 6;
    arg0->ext.weapon_2.lifetime = 0x96;
    arg0->ext.weapon_2.timer = 8;
    func_80015D60(arg0, 0);
    arg0->unk5 = 0;
    arg0->state++;
    decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
    func_8002B318(BASE_OBJECT(arg0), 0x28, 0x38);
}

struct Shot34Data {
    struct Unk_unk68 bounds[6];
    u8 effect_animation_ids[3][4];
    s8 trailing_data[4];
};

extern struct Shot34Data D_80109510;
extern s32 D_80109538[4];
extern s32 D_80109548[4];
extern u8 D_80109564[4][4];
extern void (*D_80109574[])(struct ShotObj*);
void func_80021DBC(s16* arg0, s16* arg1, s32 arg2);
void func_800A18A8(struct ShotObj* arg0);

void func_800A16FC(struct ShotObj* arg0)
{
    arg0->x_vel.val = 0x60000;
    arg0->unk16 = 5;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->state = 1;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk1C.val = arg0->y_pos.val;
    switch (arg0->unk2) {
    case 0:
        arg0->unk54 = (u8*)&D_80109510.bounds[4];
        arg0->unk50.data = (u8*)&D_80109510.bounds[3];
        arg0->unk68 = &D_80109510.bounds[5];
        arg0->unk5C = 1;
        arg0->unk8C.bytes[3] = 0;
        arg0->timer = 0;
        arg0->unk15 = arg0->x_pos.val < g_Player.x_pos.val ? 0x40 : 0;
        break;
    case 1:
        arg0->unk54 = (u8*)&D_80109510.bounds[1];
        arg0->unk5C = 1;
        arg0->unk50.data = (u8*)&D_80109510.bounds[0];
        arg0->unk68 = NULL;
        arg0->timer = 0;
        break;
    case 2:
    case 3:
        arg0->unk5C = 3;
        arg0->unk54 = (u8*)&D_80109510.bounds[1];
        arg0->unk50.data = (u8*)&D_80109510.bounds[0];
        arg0->unk68 = &D_80109510.bounds[2];
        arg0->x_vel.val = arg0->unk15 != 0 ? 0x30000 : -0x30000;
        arg0->unk8C.bytes[3] = 1;
        arg0->timer = 0xE10;
        break;
    }
    arg0->unk60 = 6;
    arg0->unk5C = 3;
    arg0->unk58.data = (u8*)D_80105FF0;
    arg0->unk67 = 0;
    arg0->unk8C.bytes[0] = 7;
    arg0->unk8C.bytes[2] = 0;
    arg0->unk5 = D_80109548[arg0->unk2];
    func_80015D60(arg0, D_80109538[arg0->unk2]);
}

static void shot_34_orbit(struct ShotObj* arg0, struct MainObj* owner)
{
    arg0->unk84.halves[0] = 0x20;
    arg0->unk84.halves[1] = 0x20;
    func_80021DBC((s16*)&arg0->unk84.halves[0], (s16*)&arg0->unk84.halves[1], arg0->unk8C.bytes[0]);
}

void func_800A19A8(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;

    switch (arg0->unk7) {
    case 0:
        arg0->unk7 = 1;
        arg0->y_vel.val = 0xA0000;
        arg0->x_vel.val = 0;
        arg0->unk8C.bytes[1] = 2;
    case 1:
        if (arg0->unk8C.bytes[1] != 0) {
            arg0->unk8C.bytes[1]--;
        } else {
            arg0->y_vel.val = 0;
            arg0->unk7++;
        }
        func_8002B718(MOVING_OBJECT(arg0));
        break;
    case 2:
        if (owner->ext.main_55.unk87 != 0) {
            arg0->unk7 = 0;
            arg0->unk6++;
            break;
        }
        shot_34_orbit(arg0, owner);
        if (arg0->timer == 0) {
            arg0->timer = 3;
            arg0->unk8C.bytes[0] = (arg0->unk8C.bytes[0] - 1) & 0xF;
        } else {
            arg0->timer--;
        }
        arg0->x_pos.i.hi = owner->x_pos.i.hi + arg0->unk84.halves[0];
        arg0->y_pos.i.hi = owner->y_pos.i.hi + arg0->unk84.halves[1];
        break;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (owner->active == 0)
        arg0->state = 2;
}

void func_800A1B1C(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;

    if (!((owner->ext.main_55.unk88 >> arg0->unk8A) & 1)) {
        arg0->unk7 = 0;
        arg0->unk15 = g_Player.x_pos.val >= arg0->x_pos.val ? 0x40 : 0;
        arg0->unk6++;
    }
    shot_34_orbit(arg0, owner);
    arg0->x_pos.i.hi = owner->x_pos.i.hi + arg0->unk84.halves[0];
    arg0->y_pos.i.hi = owner->y_pos.i.hi + arg0->unk84.halves[1];
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (owner->active == 0)
        arg0->state = 2;
}

void func_800A1BEC(struct ShotObj* arg0)
{
    if (arg0->unk7 == 0) {
        arg0->unk7 = 1;
        arg0->unk15 = g_Player.x_pos.val >= arg0->x_pos.val ? 0x40 : 0;
        func_8002B93C(MOVING_OBJECT(arg0),
            func_8002B7B0(OBJECT_HEADER(arg0), g_Player.x_pos.val + 0x1400000, g_Player.y_pos.val) & 0xFF);
        arg0->y_vel.val -= 0x30000;
    }
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_800A1CCC(struct ShotObj* arg0)
{
    u8 flags;
    s32 reverse;

    arg0->unk8C.bytes[3] = 1;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    arg0->unk54 = (u8*)&D_80109510.bounds[1];
    arg0->unk50.data = (u8*)&D_80109510.bounds[0];
    arg0->unk68 = &D_80109510.bounds[2];
    if (arg0->unk6 == 0) {
        flags = arg0->unk70;
        if ((flags & 3) == 0)
            return;
        if (arg0->unk15 != 0)
            reverse = flags & 1;
        else
            reverse = (flags & 2) != 0;
        if (!(arg0->unk70 & 8)) {
            arg0->unk6++;
            arg0->x_vel.val = 0;
            arg0->unk15 ^= 0x40;
            func_80015D60(arg0, D_80109564[0][arg0->unk2]);
        } else if (reverse) {
            arg0->unk15 ^= 0x40;
            arg0->x_vel.val = -arg0->x_vel.val;
        }
        return;
    }
    if (arg0->animation_step.fields.relative_step != 0)
        return;
    arg0->unk5 = 4;
    arg0->unk6 = 0;
    arg0->y_vel.val = -0x30000;
    func_80015D60(arg0, D_80109564[1][arg0->unk2]);
    arg0->unk68 = &D_80109510.bounds[5];
    arg0->x_pos.i.hi += arg0->unk15 != 0 ? -0x10 : 0x10;
    arg0->unk67 = 0;
}

void func_800A1E3C(struct ShotObj* arg0)
{
    arg0->unk8C.bytes[3] = 0;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    arg0->unk54 = (u8*)&D_80109510.bounds[4];
    arg0->unk50.data = (u8*)&D_80109510.bounds[3];
    arg0->unk68 = &D_80109510.bounds[5];
    if (arg0->unk6 == 0) {
        if (arg0->unk70 & 8) {
            arg0->unk6 = 1;
            arg0->y_vel.val = 0;
            func_80015D60(arg0, D_80109564[2][arg0->unk2]);
        }
        return;
    }
    if (arg0->animation_step.fields.relative_step != 0)
        return;
    arg0->unk5 = 3;
    arg0->unk6 = 0;
    arg0->unk15 = arg0->x_pos.val < g_Player.x_pos.val ? 0x40 : 0;
    if (arg0->unk2 < 2)
        arg0->x_vel.val = arg0->unk15 != 0 ? 0x90000 : -0x10000;
    else
        arg0->x_vel.val = arg0->unk15 != 0 ? 0x30000 : -0x30000;
    func_80015D60(arg0, D_80109564[3][arg0->unk2]);
    arg0->unk68 = &D_80109510.bounds[2];
    arg0->unk67 = 0;
    arg0->y_pos.i.hi += 0x10;
}

void func_800A2098(struct ShotObj* arg0)
{
    s32 hit = func_8002DD04((struct MainObj*)arg0);

    if (arg0->unk2 >= 2) {
        if (((struct BaseObj*)arg0->unk7C)->state == 2)
            hit = -1;
        if (arg0->timer == 0)
            hit = -1;
        else
            arg0->timer--;
    }
    if (hit < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        if (arg0->unk2 == 2)
            func_800C813C(4, D_80109510.effect_animation_ids[1], arg0);
        else if (arg0->unk2 == 3)
            func_800C813C(4, D_80109510.effect_animation_ids[2], arg0);
        else if (arg0->unk2 >= 0 && arg0->unk2 < 2)
            func_800C813C(4, D_80109510.effect_animation_ids[0], arg0);
        arg0->state = 2;
        return;
    }
    arg0->unk8C.bytes[2] = 1;
    func_8002D9BC(arg0);
    if (arg0->unk2 == 0)
        func_800A18A8(arg0);
    D_80109574[arg0->unk5](arg0);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x80, 0x80) != 0)
        arg0->state = 2;
    else
        is_on_screen(BASE_OBJECT(arg0));
}

extern u16 D_80108890[];
void func_8009443C(s8 arg0);
void func_80094154(struct WeaponObj* arg0);

void func_80094280(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;

    arg0->unk40 = 0x520;
    arg0->previous_animation_index = 0xFF;
    arg0->state++;
    arg0->animation_step.fields.frame_index = 9;
    arg0->ext.raw[2] = 0;
    arg0->ext.raw[3] = 0;
    arg0->unk5 = 0;
    arg0->unk38 = (u8*)player_gfx + player_gfx[3];
    decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
}

void func_800942E8(struct WeaponObj* arg0)
{
    s32 strength = 0x20;

    if (arg0->ext.raw[2] != 0) {
        arg0->ext.raw[2]--;
        return;
    }
    arg0->ext.raw[2] = 0x28;
    switch (arg0->ext.raw[3]) {
    case 0:
        func_8009443C(1);
        break;
    case 1:
        func_8009443C(2);
        func_8009443C(-0x7E);
        break;
    case 2:
        func_8009443C(1);
        func_8009443C(3);
        func_8009443C(-0x7D);
        break;
    case 3:
        func_8009443C(4);
        func_8009443C(-0x7C);
        func_8009443C(5);
        func_8009443C(-0x7B);
        strength = 0x40;
        break;
    }
    func_8001540C(0, 0x1A, 0);
    func_80028B68(strength, 8, 1);
    if (++arg0->ext.raw[3] == 4)
        func_80094154(arg0);
}

void func_800944B8(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;
    struct BackgroundObj* background = &background_objects[g_Player.bg_offset];
    u16 base;

    arg0->on_screen = 1;
    arg0->unk38 = (u8*)player_gfx + player_gfx[3];
    arg0->animation_table = D_8011C094;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 1;
    arg0->unk15 = 0;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0xB];
    base = background->x_pos.i.hi + 0xA0;
    if (arg0->unk2 & 0x80)
        arg0->x_pos.i.hi = base - D_80108890[arg0->unk2 & 0x7F];
    else
        arg0->x_pos.i.hi = base + D_80108890[arg0->unk2 & 0x7F];
    arg0->x_vel.val = 0;
    arg0->unk28.val = 0;
    arg0->y_vel.val = -0x80000;
    arg0->unk2C = 0;
    arg0->y_pos.i.hi = background->y_pos.i.hi + 0x30;
    func_80015D60(arg0, 6);
    arg0->unk5 = 0;
    arg0->state++;
    func_8002B318(BASE_OBJECT(arg0), 0x28, 0x38);
}

extern struct Unk_unk68 D_80101338;
extern void* frost_walrus_animations[39];
extern void (*frost_walrus_step_funcs[12])();

void func_800722A0(struct MainObj* arg0)
{
    if (((struct BaseObj*)arg0->ext.main_57.effect)->active != 0)
        return;
    arg0->unk16 = 5;
    arg0->unk60 = 6;
    arg0->unk68 = &D_80101338;
    arg0->unk54 = &D_8010133C;
    arg0->unk50 = &D_80101344;
    arg0->collision_data = D_80107A78;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk15 = 0;
    arg0->unk5C = 0;
    arg0->unk61 = 0;
    arg0->animation_table = (const u8* const*)frost_walrus_animations;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (engine_obj.stage != 0xC) {
        arg0->unk40 = (D_801406A8[0] >> 7) + 0xB0;
    } else {
        arg0->unk40 = (D_801406A8[0] >> 7) + 0x160;
        arg0->unk42 = 0x7888;
        arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[4];
    }
    engine_obj.unk25 = 1;
    engine_obj.boss_ptr = arg0;
    func_80015D60(arg0, 0x26);
    arg0->ext.main_57.tusks_broken = 0;
    arg0->ext.main_57.flash_timer = 0;
    arg0->ext.main_57.flashing = 0;
    arg0->ext.main_57.staggered = 0;
    arg0->state = 1;
    arg0->unk5 = 2;
    arg0->unk6 = 0;
}

void func_80072418(struct MainObj* arg0)
{
    s32 hit;
    s32 flash = 0;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    ((void (*)(struct MainObj*))frost_walrus_step_funcs[arg0->unk5])(arg0);
    hit = func_8002DD04(arg0);
    if (arg0->ext.main_57.flash_timer != 0) {
        if (arg0->ext.main_57.flash_timer & 1)
            arg0->unk42 &= 0x7FFF;
        else
            arg0->unk42 |= 0x8000;
        if (--arg0->ext.main_57.flash_timer == 0) {
            arg0->collision_data = D_80107A78;
            arg0->ext.main_57.flashing = 0;
        }
    } else if (hit < 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->unk42 &= 0x7FFF;
        g_Player.unk7A = 1;
        func_8002B318(BASE_OBJECT(arg0), 0x60, 0x60);
        return;
    } else if (hit != 0) {
        s32 weakness = engine_obj.cur_character == CHARACTER_X ? (hit == 5 || hit == 0xE) : hit == 0x24;

        if (weakness && arg0->ext.main_57.staggered == 0) {
            arg0->unk5 = 0xA;
            arg0->unk6 = 0;
            return;
        }
        flash = engine_obj.cur_character == CHARACTER_X || hit != 0x7F;
    }
    if (flash) {
        arg0->collision_data = D_801060F0;
        arg0->ext.main_57.flash_timer = 0x40;
        arg0->ext.main_57.flashing = 1;
    }
    func_8002D9BC(arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x60, 0x60);
}

void func_80072628(struct MainObj* arg0)
{
    g_Player.unkBA = 0;
    func_80036AE4(0x14, g_Player.unk15);
    arg0->unk5 = 1;
    arg0->unk42 &= 0x7FFF;
    func_80015D60(arg0, arg0->ext.main_57.tusks_broken != 0 ? 0x1C : 0x1B);
    arg0->unk7C = 0x7F;
    arg0->unk7E = 0x19;
    arg0->unk61 = 0x19;
    frost_walrus_set_floor_tiles(0x38);
    func_8002B318(BASE_OBJECT(arg0), 0x60, 0x60);
}

void func_800727C0(struct MainObj* arg0)
{
    struct BaseObj* effect = (struct BaseObj*)arg0->ext.main_57.effect;
    u16 flash;

    arg0->on_screen = 0;
    if (effect->active == 0) {
        memset(&arg0->ext.main_57, 0, sizeof(arg0->ext.main_57));
        engine_obj.enable_boss = 0;
        engine_obj.boss_ptr = NULL;
        if (engine_obj.stage == 0xC) {
            engine_obj.unkF = -0x80;
            engine_obj.character_state.bytes[engine_obj.checkpoint + 6] = 1;
            engine_obj.checkpoint += 9;
        } else {
            engine_obj.unkF = 0x10;
        }
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (effect->unk7 != 0)
        return;
    flash = arg0->unk7E;
    arg0->unk7E = flash - 1;
    if (flash == 0) {
        arg0->unk7E = 5;
        arg0->unk42 ^= 0x8000;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x60, 0x60);
}

extern u8 frost_walrus_burst_subtypes[32];
extern s16 frost_walrus_burst_offsets[40];

void func_80072A84(struct MainObj* arg0)
{
    struct VisualObj* visual;
    u32 i;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 1) {
        for (i = 0; i < 20; i++) {
            visual = find_free_visual_obj();
            if (visual == NULL)
                continue;
            visual->active = 0x41;
            visual->id = 0x18;
            visual->unk2 = frost_walrus_burst_subtypes[i];
            visual->x_pos.i.hi = arg0->x_pos.i.hi + frost_walrus_burst_offsets[i * 2];
            visual->unk50 = (struct PlayerObj*)arg0;
            visual->y_pos.i.hi = arg0->y_pos.i.hi + frost_walrus_burst_offsets[i * 2 + 1];
        }
        func_8001540C(2, 0x94, arg0);
    }
    if (--arg0->unk7C != 0)
        return;
    func_80015D60(arg0, 0x1A);
    if (engine_obj.stage == 2) {
        ((void (*)(s32, s32, s32))func_8002217C)(9, 0xFF, (u8)engine_obj.character_state.bytes[8]);
        engine_obj.character_state.bytes[8] = 1;
    }
    arg0->unk6++;
}

void func_80073E80(struct MainObj* arg0)
{
    struct VisualObj* visual;
    u32 i;

    arg0->ext.main_57.staggered = 1;
    for (i = 0; i < 4; i++) {
        visual = find_free_visual_obj();
        if (visual == NULL)
            continue;
        visual->active = 0x41;
        visual->id = 0x18;
        visual->unk2 = i + 0x40;
        visual->unk50 = (struct PlayerObj*)arg0;
        visual->unk15 = arg0->unk15;
    }
    func_80015D60(arg0, 0x12);
    func_8001540C(2, 0x99, arg0);
    arg0->unk20 = arg0->x_pos.i.hi < g_Player.x_pos.i.hi ? -0x20000 : 0x20000;
    arg0->unk24 = 0x38000;
    arg0->unk2C = 0x4200;
    arg0->ext.main_57.flash_timer = 0xC8;
    arg0->unk67 = 1;
    arg0->ext.main_57.flashing = 1;
    arg0->unk28 = 0;
    arg0->collision_data = D_801060F0;
    arg0->unk6++;
}

extern struct Unk_unk68 D_8010890C[];
extern u32* D_8011C0B0[];
extern s8 D_80108930[];
void func_8009547C(struct WeaponObj* arg0);

void func_80095254(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;
    s8 dx = D_80108930[arg0->unk2 * 2];
    s8 dy = D_80108930[arg0->unk2 * 2 + 1];

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    arg0->unk50 = D_8010890C;
    arg0->unk38 = (u8*)player_gfx + player_gfx[5];
    arg0->animation_table = D_8011C0B0;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 1;
    arg0->unk15 = 0;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0xD];
    if (g_Player.unk15 == 0)
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi + dx;
    else
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi - dx;
    arg0->y_vel.val = 0x70000;
    arg0->x_vel.val = 0;
    arg0->unk28.val = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 1;
    arg0->unk49 = 0;
    arg0->y_pos.i.hi = g_Player.y_pos.i.hi + dy;
    func_80015D60(arg0, 1);
    func_8001540C(0, 0x1B, arg0);
    arg0->unk5 = 0;
    arg0->state++;
    func_8009547C(arg0);
}

void func_80095538(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    arg0->unk38 = (u8*)player_gfx + player_gfx[5];
    arg0->animation_table = D_8011C0B0;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 1;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0xD];
    arg0->unk15 = g_Player.unk15;
    arg0->x_pos.val = g_Player.x_pos.val;
    arg0->y_vel.val = 0x70000;
    arg0->x_vel.val = 0;
    arg0->unk28.val = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 1;
    arg0->unk49 = 0;
    arg0->ext.weapon_13.timer = 4;
    arg0->y_pos.val = g_Player.y_pos.val;
    func_80015D60(arg0, arg0->unk2 == 0 ? 3 : 5);
    func_8001540C(0, 0x1B, arg0);
    arg0->unk5 = 0;
    arg0->state++;
    func_80095770(arg0);
}

void func_800B3B94(struct VisualObj* arg0)
{
    struct PlayerObj* source = arg0->unk50;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    arg0->x_pos.val = source->x_pos.val + (D_8010A63C[(s8)arg0->unk2 * 2] << 16);
    arg0->y_pos.val = source->y_pos.val + (D_8010A63C[(s8)arg0->unk2 * 2 + 1] << 16);
    is_on_screen(BASE_OBJECT(arg0));
    if ((s8)source->unk6 == 2) {
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}

void func_800A241C(struct ShotObj* arg0)
{
    struct WeaponObj* owner = arg0->unk7C;

    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0x60000;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->x_pos.val = owner->x_pos.val;
    arg0->unk68 = &D_801096B4;
    arg0->unk5C = 5;
    arg0->unk60 = 6;
    arg0->unk16 = 4;
    arg0->unk54 = NULL;
    arg0->unk50.data = NULL;
    arg0->y_pos.val = owner->y_pos.val;
    arg0->unk42 = owner->unk42;
    func_80015D60(arg0, (s8)arg0->unk2 >= 2 ? 9 : 8);
    if ((s8)arg0->unk2 == 0) {
        func_800A38B0(arg0);
    }
    arg0->unk5++;
}

void func_800A25EC(struct ShotObj* arg0)
{
    struct WeaponObj* owner = arg0->unk7C;
    struct VisualObj* visual;
    u8 i;

    arg0->unk42 = owner->unk42;
    arg0->x_pos.val = owner->x_pos.val;
    arg0->y_pos.val = owner->y_pos.val;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if ((s8)owner->unk5 == 0xA) {
        arg0->state = 6;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        return;
    }
    if ((u8)arg0->unk2 & 1) {
        is_on_screen(BASE_OBJECT(arg0));
    }
    if (arg0->animation_step.fields.relative_step != 0) {
        return;
    }
    arg0->unk6++;
    if ((u8)arg0->unk2 & 1) {
        return;
    }
    func_8001540C(2, 0x95, arg0);
    for (i = 0; i < 2; i++) {
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 0x18;
            visual->unk2 = 0;
            if (owner->unk15 != 0) {
                visual->x_pos.i.hi = owner->x_pos.i.hi + D_801096A0[i][0];
            } else {
                visual->x_pos.i.hi = owner->x_pos.i.hi - D_801096A0[i][0];
            }
            visual->unk50 = (struct PlayerObj*)owner;
            visual->y_pos.i.hi = owner->y_pos.i.hi - 0x1F;
        }
    }
}

void func_800A2AA0(struct ShotObj* arg0)
{
    struct WeaponObj* owner = arg0->unk7C;

    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0x38000;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->x_pos.val = owner->x_pos.val;
    arg0->unk5C = 0x20;
    arg0->unk60 = 9;
    arg0->unk68 = &D_801096A8;
    arg0->unk54 = (const u8*)&D_801096C0;
    arg0->unk58.data = (u8*)D_801060F0;
    arg0->unk50.data = (const u8*)&D_801096C4;
    arg0->timer = 0x60;
    arg0->unk16 = 2;
    arg0->y_pos.val = owner->y_pos.val;
    func_80015D60(arg0, 0x1F);
    if (arg0->unk15 != 0) {
        arg0->x_pos.i.hi += 0x50;
    } else {
        arg0->x_pos.i.hi -= 0x50;
    }
    arg0->y_pos.i.hi += 0x10;
    arg0->unk5++;
}

void func_800A32B8(struct ShotObj* arg0)
{
    struct WeaponObj* owner = arg0->unk7C;

    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0x4800;
    arg0->x_pos.val = owner->x_pos.val;
    arg0->unk68 = &D_801096A8;
    arg0->unk54 = (const u8*)&D_801096C0;
    arg0->unk58.data = (u8*)D_801060F0;
    arg0->unk50.data = (const u8*)&D_801096C4;
    arg0->timer = 0x60;
    arg0->unk16 = 4;
    arg0->unk5C = 0x20;
    arg0->unk60 = 9;
    arg0->y_pos.val = owner->y_pos.val;
    func_80015D60(arg0, 0x1E);
    if (arg0->unk15 != 0) {
        arg0->x_pos.i.hi += 0x90;
    } else {
        arg0->x_pos.i.hi -= 0x90;
    }
    arg0->y_pos.i.hi -= 0x30;
    arg0->unk5++;
}

void func_800A348C(struct ShotObj* arg0)
{
    if (--arg0->timer == 0) {
        arg0->unk54 = (const u8*)&D_801096C0;
        arg0->unk50.data = (const u8*)&D_801096C4;
        func_8001540C(2, 0x96, arg0);
        arg0->unk6++;
    } else {
        arg0->on_screen ^= 1;
        if (arg0->on_screen != 0) {
            is_on_screen(BASE_OBJECT(arg0));
        }
    }
}

extern struct Unk_unk68 D_80107BF8[];
extern void* split_mushroom_animations[];
extern struct Unk_unk68 D_80101CA0;
extern struct Unk_unk68 D_80101CA4;
extern struct Unk_unk68 D_80101CAC;
extern s16 split_mushroom_hop_speeds[];
extern void (*split_mushroom_step_funcs[8])();
void split_mushroom_load_palette(void);

void func_8007877C(struct MainObj* arg0)
{
    arg0->unk60 = 5;
    arg0->unk5C = 0;
    arg0->unk61 = 0;
    arg0->collision_data = D_80107BF8;
    if (engine_obj.stage != 0xC) {
        arg0->unk15 = 0x40;
        arg0->unk40 = (D_801406A8[0] >> 7) + 0xB0;
    } else {
        arg0->unk40 = (D_801406A8[0] >> 7) + 0x160;
        arg0->unk42 = 0x7888;
        arg0->unk15 = 0;
        arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[4];
    }
    arg0->unk2C = 0x3800;
    arg0->animation_table = (const u8* const*)split_mushroom_animations;
    arg0->unk16 = 6;
    arg0->unk54 = &D_80101CA4;
    arg0->unk50 = &D_80101CA0;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk67 = 0;
    arg0->unk68 = &D_80101CA8;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    func_80015D60(arg0, 5);
    arg0->ext.main_61.flash_timer = 0;
    arg0->ext.main_61.split = 0;
    arg0->ext.main_61.stunned = 0;
    arg0->ext.main_61.split_hits = 3;
    arg0->ext.main_61.merge = 0;
    arg0->ext.main_61.hit_lock = 0;
    arg0->ext.main_61.active = 0;
    arg0->ext.main_61.speed_level = 0;
    arg0->ext.main_61.split_done = 0;
    split_mushroom_load_palette();
    arg0->state = 1;
    arg0->unk5 = 1;
    arg0->unk6 = 0;
}

static struct ShotObj* main61_spawn_shot(struct MainObj* self, s8 subtype, s8 state)
{
    struct ShotObj* shot = find_free_shot_obj();

    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x27;
        shot->unk2 = subtype;
        shot->unk40 = self->unk40;
        shot->unk42 = self->unk42;
        shot->animation_table = (void*)self->animation_table;
        shot->unk3C = (void*)self->sprite_frames;
        shot->unk15 = self->unk15;
        shot->bg_offset = self->bg_offset;
        shot->x_pos.val = self->x_pos.val;
        shot->y_pos.val = self->y_pos.val;
        shot->unk15 = self->unk15;
        if (self->unk2 == 0)
            shot->unk7C = (struct WeaponObj*)self;
        else
            shot->unk7C = (struct WeaponObj*)self->ext.main_61.partner;
        shot->state = state;
    }
    return shot;
}

void func_800788E4(struct MainObj* arg0)
{
    s32 hit;
    s8 flash;
    struct VisualObj* visual;
    struct MainObj* other;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    ((void (*)(struct MainObj*))split_mushroom_step_funcs[arg0->unk5])(arg0);
    if (arg0->unk2 == 0 && arg0->ext.main_61.active == 0)
        return;
    hit = 0;
    if (arg0->ext.main_61.split != 0xFF && arg0->ext.main_61.hit_lock == 0 && arg0->unk2 == 0)
        hit = func_8002DD04(arg0);
    flash = (s8)arg0->ext.main_61.flash_timer;
    if (flash == 0) {
        arg0->ext.main_61.hit_lock = 0;
        if (hit < 0) {
            g_Player.unk7A = 1;
            func_80015930(2, 0xA7);
            if (arg0->unk2 == 0) {
                arg0->state = 2;
                arg0->unk5 = 0;
                if (arg0->ext.main_61.split != 0) {
                    arg0->ext.main_61.partner->on_screen = 0;
                    ZeroObjectState(OBJECT_HEADER(arg0->ext.main_61.partner));
                }
            } else {
                arg0->ext.main_61.partner->state = 2;
                arg0->ext.main_61.partner->unk5 = 0;
                arg0->on_screen = 0;
                ZeroObjectState(OBJECT_HEADER(arg0));
            }
            return;
        }
        if (hit != 0 && hit != 0x7F) {
            if (arg0->unk5 != 6 && hit != 2 && hit != 0xB && hit != 0x21 && (get_random() & 0xF) < 4)
                main61_spawn_shot(arg0, 0, 7);
            if ((u32)(hit - 0x19) < 2) {
                arg0->ext.main_61.flash_timer = 6;
                arg0->ext.main_61.hit_lock = 1;
            } else {
                arg0->ext.main_61.flash_timer = 0x40;
            }
            if (hit != 2 && hit != 0xB && hit != 0x21) {
                visual = find_free_visual_obj();
                if (visual != NULL) {
                    visual->active = 0x41;
                    visual->id = 0x22;
                    visual->unk2 = 1;
                    visual->unk16 = 0;
                    visual->unk40 = arg0->unk40;
                    visual->unk42 = arg0->unk42;
                    visual->animation_table = (void*)arg0->animation_table;
                    visual->unk3C = (void*)arg0->sprite_frames;
                    visual->unk15 = arg0->unk15;
                    visual->unk15 = 0;
                    visual->unk50 = (struct PlayerObj*)arg0;
                    visual->bg_offset = arg0->bg_offset;
                    visual->state = 0;
                    visual->unk5C.value = arg0->ext.main_61.flash_timer;
                    func_80015D60(visual, 0x14);
                }
            }
            arg0->collision_data = D_801060F0;
            arg0->unk42 |= 0x8000;
            if ((hit == 2 || hit == 0xB || hit == 0x21) && arg0->ext.main_61.stunned == 0) {
                func_80015930(2, 0xA7);
                arg0->ext.main_61.stunned = 1;
                func_80015D60(arg0, 0x13);
                arg0->unk7E = 1;
                arg0->unk61 = 1;
                arg0->unk5 = 2;
                arg0->unk6 = 0;
                if (arg0->ext.main_61.split != 0) {
                    if (arg0->unk2 == 0) {
                        if (--arg0->ext.main_61.split_hits == 0)
                            arg0->ext.main_61.merge = 1;
                    } else {
                        other = arg0->ext.main_61.partner;
                        if (--other->ext.main_61.split_hits == 0)
                            arg0->ext.main_61.partner->ext.main_61.merge = 1;
                    }
                    func_80015D60(arg0->ext.main_61.partner, 0x13);
                    arg0->ext.main_61.partner->unk61 = 1;
                    arg0->ext.main_61.partner->unk5 = 2;
                    arg0->ext.main_61.partner->unk6 = 0;
                }
            }
        }
    } else {
        arg0->ext.main_61.flash_timer = --flash;
        if (flash == 0) {
            arg0->collision_data = D_80107BF8;
            arg0->unk42 &= 0x7FFF;
        } else if (flash & 1) {
            arg0->unk42 |= 0x8000;
        } else {
            arg0->unk42 &= 0x7FFF;
        }
    }
    if (arg0->ext.main_61.blink_timer != 0) {
        if ((--arg0->ext.main_61.blink_timer & 1) == 0) {
            arg0->on_screen = 0;
            return;
        }
    }
    arg0->ext.main_61.speed_level = 0;
    if (arg0->unk5C < 0x20)
        arg0->ext.main_61.speed_level = 1;
    else if (arg0->unk5C < 0x10)
        arg0->ext.main_61.speed_level = 2;
    if ((u32)((u8)arg0->unk5 - 1) >= 2)
        func_8002D9BC(arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x60, 0x60);
}

void func_80078FA4(struct MainObj* arg0)
{
    struct BaseObj* effect = (struct BaseObj*)arg0->ext.main_61.data.effect;
    u16 flash;

    arg0->on_screen = 0;
    if (effect->active == 0) {
        memset(&arg0->ext.main_61, 0, sizeof(arg0->ext.main_61));
        engine_obj.enable_boss = 0;
        engine_obj.boss_ptr = NULL;
        if (engine_obj.stage == 0xC) {
            engine_obj.unkF = -0x80;
            engine_obj.character_state.bytes[engine_obj.checkpoint + 6] = 1;
            engine_obj.checkpoint += 9;
        } else {
            engine_obj.unkF = 0x10;
        }
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (effect->unk7 != 0)
        return;
    flash = arg0->unk7E;
    arg0->unk7E = flash - 1;
    if (flash == 0) {
        arg0->unk7E = 5;
        arg0->unk42 ^= 0x8000;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x60, 0x60);
}

void func_800790E8(struct MainObj* arg0)
{
    struct EffectObj* effect;
    s8 facing;

    if (engine_obj.stage == 3) {
        if (engine_obj.cur_character != 0) {
            if (g_Player.y_pos.i.hi >= 0x1CB)
                return;
        } else if (g_Player.y_pos.i.hi >= 0x1CC) {
            return;
        }
        facing = 0;
    } else {
        facing = 0x40;
    }
    effect = find_free_effect_obj();
    if (effect != NULL) {
        effect->active = 1;
        effect->id = 0x18;
        arg0->ext.main_61.data.effect = effect;
    }
    func_80036AE4(0x14, facing);
    arg0->unk6 = 1;
}

void func_800793AC(struct MainObj* arg0)
{
    s32 i;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 1) {
        func_8001540C(2, 0xA9, arg0);
        for (i = 0; i < 5; i++)
            main61_spawn_shot(arg0, i, 7);
    }
    if (arg0->animation_step.fields.event == 2) {
        if (engine_obj.stage == 3) {
            func_8002217C(0xA, 0xFF, engine_obj.character_state.bytes[8]);
            engine_obj.character_state.bytes[8] = 1;
        }
        arg0->unk6 = 5;
    }
}

void func_80079824(struct MainObj* arg0)
{
    struct MainObj* other = arg0->ext.main_61.partner;
    s32 dx = arg0->x_pos.i.hi - other->x_pos.i.hi;
    s32 dy;

    if (dx < 0)
        dx = -dx;
    if (dx < 4) {
        dy = arg0->y_pos.i.hi - arg0->ext.main_61.partner->y_pos.i.hi;
        if (dy < 0)
            dy = -dy;
        if (dy < 4) {
            arg0->ext.main_61.partner->ext.main_61.split = 0;
            arg0->on_screen = 0;
            ZeroObjectState(OBJECT_HEADER(arg0));
            return;
        }
    }
    func_8002B93C(MOVING_OBJECT(arg0),
        (u8)func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(arg0->ext.main_61.partner)));
    arg0->unk20 *= 4;
    arg0->unk24 *= 4;
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_80079A8C(struct MainObj* arg0)
{
    s32 target;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 0)
        return;
    arg0->ext.main_61.stunned = 1;
    target = background_objects[g_Player.bg_offset].x_pos.val - (arg0->x_pos.val + (s32)0xFF600000);
    arg0->unk24 = 0x85C00;
    arg0->unk2C = 0x3800;
    arg0->unk7C = 0x30;
    arg0->unk6 = 1;
    arg0->unk20 = target / 48;
    func_8001540C(2, 0xA5, arg0);
}

void func_80079B50(struct MainObj* arg0)
{
    s32 row;
    s32 col;
    s32 x_step;
    s8 phase;
    u16 delay;
    u16 base_y;
    s16 base_x;
    s16 y;

    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    func_80015D60(arg0, 4);
    phase = 0;
    delay = 0x104;
    base_y = background_objects[g_Player.bg_offset].y_pos.i.hi - 0x20;
    base_x = background_objects[g_Player.bg_offset].x_pos.i.hi - 0x10;
    for (row = 0; row < 0xC0; row += 0x20) {
        y = base_y - row;
        for (col = 0, x_step = 0; col < 10; col++, x_step += 0x40) {
            if (!(col & 1)) {
                struct VisualObj* visual = find_free_visual_obj();

                if (visual == NULL)
                    continue;
                visual->active = 0x41;
                visual->id = 0x22;
                visual->unk2 = 0;
                visual->x_pos.i.hi = base_x + phase + x_step;
                visual->y_pos.i.hi = y;
                visual->unk15 = 0;
                visual->bg_offset = arg0->bg_offset;
                visual->animation_table = (void*)arg0->animation_table;
                visual->unk40 = arg0->unk40;
                visual->unk3C = (void*)arg0->sprite_frames;
                visual->unk42 = arg0->unk42 & 0x7FFF;
                visual->unk16 = row < 0x41 ? 0x13 : 0x12;
                visual->unk5C.value = phase;
                visual->unk50 = (struct PlayerObj*)arg0;
                visual->state = 0;
                visual->unk5C.fields.unk5E = delay;
                func_80015D60(visual, 0xE);
            } else {
                struct MiscObj* misc = find_free_misc_obj();

                if (misc == NULL)
                    continue;
                misc->active = 0x41;
                misc->id = 0x1E;
                misc->unk2 = 0;
                misc->x_pos.i.hi = base_x + phase + x_step;
                misc->y_pos.i.hi = y;
                misc->unk15 = 0;
                misc->bg_offset = arg0->bg_offset;
                misc->animation_table = (void*)arg0->animation_table;
                misc->unk40 = arg0->unk40;
                misc->unk3C = (void*)arg0->sprite_frames;
                misc->unk42 = arg0->unk42 & 0x7FFF;
                misc->unk16 = row < 0x41 ? 0x13 : 0x12;
                misc->ext.misc_30.unk54 = phase;
                misc->ext.misc_30.owner = arg0;
                misc->state = 0;
                misc->ext.misc_30.unk56 = delay;
                func_80015D60(misc, 0xE);
            }
        }
        phase ^= 0x20;
        delay += 0x20;
    }
    arg0->unk7C = 0xF0;
    arg0->unk6 = 2;
}

void func_80079DD8(struct MainObj* arg0)
{
    u32 rnd;
    struct MainObj* clone;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    func_8001540C(2, 0xAA, arg0);
    arg0->ext.main_61.split = 1;
    rnd = get_random();
    clone = find_free_main_obj();
    if (clone != NULL) {
        clone->unk5C = 0x7F;
        clone->active = 0x41;
        clone->id = 0x3D;
        clone->unk2 = 1;
        clone->unk60 = 5;
        clone->x_pos.val = arg0->x_pos.val;
        clone->unk67 = 0;
        clone->y_pos.val = arg0->y_pos.val;
        clone->collision_data = arg0->collision_data;
        clone->unk54 = arg0->unk54;
        clone->unk50 = arg0->unk50;
        clone->unk68 = arg0->unk68;
        clone->bg_offset = arg0->bg_offset;
        clone->animation_table = arg0->animation_table;
        clone->unk70 = 0;
        clone->unk40 = arg0->unk40;
        clone->sprite_frames = arg0->sprite_frames;
        clone->unk42 = arg0->unk42 & 0x7FFF;
        clone->unk5C = 0x30;
        clone->unk16 = arg0->unk16;
        if (!(rnd & 1)) {
            clone->unk15 = 0x40;
            clone->unk20 = -0x2C000;
        } else {
            clone->unk15 = 0;
            clone->unk20 = 0x2C000;
        }
        clone->unk2C = 0x3800;
        clone->unk28 = 0;
        clone->unk24 = 0;
        clone->state = 1;
        clone->unk5 = 3;
        clone->unk6 = 3;
        func_80015D60(clone, 3);
        clone->ext.main_61.partner = arg0;
        arg0->ext.main_61.partner = clone;
        clone->ext.main_61.split = 1;
        clone->ext.main_61.blink_timer = 0x7F;
    }
    func_80015D60(arg0, 3);
    if (!(rnd & 1)) {
        arg0->unk15 = 0;
        arg0->unk20 = 0x2C000;
    } else {
        arg0->unk15 = 0x40;
        arg0->unk20 = -0x2C000;
    }
    arg0->unk2C = 0x3800;
    arg0->unk28 = 0;
    arg0->unk24 = 0;
    arg0->ext.main_61.stunned = 0;
    arg0->unk6 = 3;
}

void func_8007A2B4(struct MainObj* arg0)
{
    s16 speed = split_mushroom_hop_speeds[arg0->ext.main_61.speed_level];

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 0)
        return;
    arg0->unk20 = (arg0->unk15 != 0 ? 0xE30000 : -0xE30000) / speed;
    arg0->unk24 = (speed + 1) * 7 << 10;
    arg0->unk2C = 0x3800;
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_8001540C(2, 0xA5, arg0);
    arg0->unk6 = 3;
    arg0->unk7 = 0;
}

void func_8007A444(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 0)
        return;
    arg0->unk15 ^= 0x40;
    if (--arg0->unk7C == 0)
        func_8007B6BC(ANIMATED_OBJECT(arg0));
    else
        arg0->unk6 = 0;
}

void func_8007A4EC(struct MainObj* arg0)
{
    struct MiscObj* misc;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    arg0->unk20 = arg0->unk15 != 0 ? 0x64E38 : (s32)0xFFF9B1C8;
    if (arg0->unk7E == 3) {
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 0x16;
            misc->unk2 = 8;
            misc->unk15 = arg0->unk15;
            misc->x_pos.i.hi = arg0->x_pos.i.hi;
            misc->y_pos.i.hi = arg0->y_pos.i.hi;
            misc->bg_offset = arg0->bg_offset;
            misc->animation_table = (void*)arg0->animation_table;
            misc->unk40 = arg0->unk40;
            misc->unk3C = (void*)arg0->sprite_frames;
            misc->unk16 = 5;
            misc->ext.misc_22.owner = arg0;
            misc->ext.misc_22.timer = 0x24;
            misc->unk42 = arg0->unk42 & 0x7FFF;
            func_80015D60(misc, 0x18);
            misc->state = 0;
            misc->unk5 = 0;
            misc->unk6 = 1;
        }
    } else {
        arg0->unk24 = 0x5D31C;
        arg0->unk2C = 0x3800;
    }
    arg0->unk6 = 1;
}

static void main61_wall_hit(struct MainObj* arg0)
{
    func_8001540C(2, 0xA8, arg0);
    split_mushroom_spawn_afterimage(arg0);
    if (!(background_objects[g_Player.bg_offset].unk34 & 0x10))
        func_80028B68(0x10, 8, 2);
}

void func_8007A63C(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk15 == 0) {
        if (!(arg0->unk70 & 2))
            return;
        main61_wall_hit(arg0);
        if (--arg0->unk7E != 0) {
            arg0->unk15 = 0x40;
            arg0->unk7C = 0xA;
            arg0->unk6 = 0;
            return;
        }
    } else {
        if (!(arg0->unk70 & 1))
            return;
        main61_wall_hit(arg0);
        if (--arg0->unk7E != 0) {
            arg0->unk15 = 0;
            arg0->unk7C = 0xA;
            arg0->unk6 = 0;
            return;
        }
    }
    arg0->unk15 ^= 0x40;
    func_80015D60(arg0, 3);
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0x3800;
    func_80015930(2, 0xA7);
    arg0->unk6 = 2;
}

void func_8007A96C(struct MainObj* arg0)
{
    s32 offset;
    s32 target;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    offset = arg0->unk15 != 0 ? (s32)0xFEE80000 : (s32)0xFFD40000;
    target = background_objects[g_Player.bg_offset].x_pos.val - (arg0->x_pos.val + offset);
    if (arg0->ext.main_61.combo_count == 0) {
        arg0->unk20 = target / 48;
        arg0->unk24 = 0x55C00;
        func_8001540C(2, 0xA5, arg0);
    } else {
        arg0->unk20 = target / 36;
        func_8001540C(2, 0xA5, arg0);
        arg0->unk24 = 0x5D31C;
    }
    arg0->unk2C = 0x3800;
    func_8002B694(ANIMATED_OBJECT(arg0));
    arg0->unk6 = 1;
    arg0->unk7 = 0;
}

void func_8007AB1C(struct MainObj* arg0)
{
    s32 dx;

    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->ext.main_61.stunned != 0 && arg0->unk24 < 0)
        arg0->ext.main_61.stunned = 0;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if ((s8)arg0->ext.main_61.combo_count == 0) {
        if (arg0->unk7 == 0) {
            func_80015D60(arg0, 3);
            arg0->unk7 = 1;
        }
        if (!(arg0->unk70 & 8))
            return;
        if (arg0->ext.main_61.split_done == 0) {
            func_8001540C(2, 0xA9, arg0);
            func_8001540C(2, 0xA8, arg0);
        } else {
            func_8001540C(2, 0xA6, arg0);
            arg0->ext.main_61.split_done = 0;
        }
        arg0->unk60 = 5;
        func_80015D60(arg0, 0);
        arg0->unk7C = 0x28;
        arg0->unk6 = 5;
        arg0->unk15 ^= 0x40;
        return;
    }
    if (arg0->unk7E == 0) {
        dx = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
        if (dx < 0)
            dx = -dx;
        if (dx < 0x1C) {
            func_80015930(2, 0xA7);
            arg0->unk7C = 0x14;
            arg0->unk6 = 2;
        }
    }
    if (arg0->unk15 == 0) {
        if (!(arg0->unk70 & 2))
            return;
        main61_wall_hit(arg0);
        arg0->unk15 = 0x40;
    } else {
        if (!(arg0->unk70 & 1))
            return;
        main61_wall_hit(arg0);
        arg0->unk15 = 0;
    }
    arg0->unk7E = 0;
    arg0->unk7C = 0xA;
    arg0->unk6 = 0;
}

void func_8007AE2C(struct MainObj* arg0)
{
    s32 i;

    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (!(arg0->unk70 & 8))
        return;
    func_8001540C(2, 0xA8, arg0);
    if (!(background_objects[g_Player.bg_offset].unk34 & 1))
        func_80028BAC(0x10, 8, 2);
    for (i = 0; i < 4; i++)
        main61_spawn_shot(arg0, i, 0);
    func_80015D60(arg0, 9);
    arg0->unk7C = 0x30;
    arg0->unk6 = 4;
}

void func_8007B1BC(struct MainObj* arg0)
{
    s32 offset;
    s32 target;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 0)
        return;
    arg0->unk68 = &D_80101CAC;
    if (arg0->x_pos.i.hi < background_objects[g_Player.bg_offset].x_pos.i.hi + 0xA0)
        arg0->unk15 = 0x40;
    else
        arg0->unk15 = 0;
    offset = arg0->unk15 != 0 ? (s32)0xFEE80000 : (s32)0xFFD40000;
    target = background_objects[g_Player.bg_offset].x_pos.val - (arg0->x_pos.val + offset);
    arg0->unk20 = target / 48;
    arg0->unk24 = 0x706AA;
    func_8001540C(2, 0xA5, arg0);
    arg0->unk2C = 0x3800;
    func_8002B694(ANIMATED_OBJECT(arg0));
    arg0->unk6 = 1;
    arg0->unk7 = 0;
}

void func_8007B418(struct MainObj* arg0)
{
    struct ShotObj* shot;
    s16 count;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    count = arg0->unk7E;
    arg0->unk7E = count - 1;
    if (count == 0) {
        func_80015D60(arg0, 0x17);
        arg0->unk6 = 4;
        return;
    }
    func_8001540C(2, 0xAA, arg0);
    arg0->unk7C = 0x28;
    shot = find_free_shot_obj();
    if (shot == NULL)
        return;
    shot->active = 0x41;
    shot->id = 0x27;
    shot->unk2 = 0;
    shot->unk40 = arg0->unk40;
    shot->unk42 = engine_obj.stage == 3 ? 0x78CC : 0x788C;
    shot->unk68 = arg0->unk68;
    shot->unk54 = arg0->unk54;
    shot->unk50.data = arg0->unk50;
    shot->animation_table = (void*)arg0->animation_table;
    shot->unk3C = (void*)arg0->sprite_frames;
    shot->unk15 = arg0->unk15 ^ 0x40;
    shot->bg_offset = arg0->bg_offset;
    shot->x_pos.val = arg0->x_pos.val;
    shot->y_pos.val = arg0->y_pos.val;
    if (arg0->unk2 == 0)
        shot->unk7C = (struct WeaponObj*)arg0;
    else
        shot->unk7C = (struct WeaponObj*)arg0->ext.main_61.partner;
    shot->state = 4;
    shot->unk6 = 0;
}

void func_8007B6BC(struct AnimatedObj* obj)
{
    struct MainObj* arg0 = (struct MainObj*)obj;
    s8 hp = arg0->unk2 == 0 ? arg0->unk5C : arg0->ext.main_61.partner->unk5C;

    func_80015D60(arg0, 5);
    func_8001540C(2, 0xA7, arg0);
    if (hp >= 0x19) {
        arg0->unk7C = 0x28;
        arg0->unk7E = 3;
        arg0->unk60 = 6;
        arg0->unk5 = 5;
    } else {
        arg0->unk7C = arg0->unk2 != 0 ? 0x50 : 0x28;
        arg0->unk7E = 1;
        arg0->ext.main_61.combo_count = 2;
        arg0->unk60 = 9;
        arg0->unk5 = 6;
    }
    arg0->unk6 = 0;
}

void func_800CDCFC(struct MiscObj* arg0)
{
    struct MainObj* owner = arg0->ext.misc_30.owner;

    if (owner->state >= 2) {
        arg0->on_screen = 0;
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (arg0->unk2 == 0) {
        if (--arg0->ext.misc_30.unk56 == 0) {
            arg0->state = 1;
            func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
            return;
        }
        if (arg0->ext.misc_30.unk54 == 0)
            arg0->x_pos.i.hi += 0x20;
        else
            arg0->x_pos.i.hi -= 0x20;
        arg0->y_pos.i.hi++;
        arg0->ext.misc_30.unk54 ^= 0x20;
    } else {
        if (--arg0->ext.misc_30.unk54 == 0)
            arg0->state = 1;
        arg0->x_pos.val = arg0->ext.misc_30.owner->x_pos.val;
        arg0->y_pos.val = arg0->ext.misc_30.owner->y_pos.val;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
}

extern u8 D_801097F4[];
extern u8 D_801097F8[];
extern u8 D_801097FC[];
extern u8 D_80109800[];
extern u8 D_80109804[];
extern u8 D_8010980C[];
extern s32 D_80109818[];
extern s32 D_80109828[];
extern s32 D_80109838[];
extern void (*D_80109874[7])(struct ShotObj*);

void func_800A4800(struct ShotObj* arg0)
{
    s8 index = arg0->unk2;

    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk61 = 1;
    arg0->unk2C = 0x2000;
    arg0->y_vel.val = 0x48000;
    arg0->unk58.data = NULL;
    arg0->unk42 &= 0x7FFF;
    arg0->unk28 = D_80109828[index];
    if (arg0->unk15 == 0) {
        arg0->x_pos.i.hi += (s8)D_80109804[index * 2];
        arg0->x_vel.val = D_80109818[index];
    } else {
        arg0->x_pos.i.hi -= (s8)D_80109804[index * 2];
        arg0->x_vel.val = -D_80109818[index];
    }
    arg0->unk50.data = D_801097F4;
    arg0->timer = 0x28;
    arg0->unk5C = 1;
    arg0->unk60 = 6;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->unk54 = NULL;
    arg0->y_pos.i.hi += (s8)D_80109804[index * 2 + 1];
    func_80015D60(arg0, 0xB);
}

void func_800A4B6C(struct ShotObj* arg0)
{
    u8 color;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_80109874[arg0->unk5](arg0);
    arg0->unk42 &= 0x7FFF;
    if (arg0->unk5 != 6)
        CollisionRelated(PLAYER_OBJECT(arg0));
    if (arg0->unk6 != 0) {
        func_8002D9BC(arg0);
        if (D_80141BD8.unk0 & 1) {
            if (++arg0->unk7 == 4)
                arg0->unk7 = 0;
            if (engine_obj.stage == 3)
                color = D_801097FC[arg0->unk7];
            else
                color = D_80109800[arg0->unk7];
            arg0->unk42 = (color & 0xF) | (((color >> 4) + 0x1E0) << 6);
        }
    }
    if (func_8002DD04(MAIN_OBJECT(arg0)) < 0)
        arg0->state = 6;
    if (arg0->unk7C->state == 2) {
        arg0->on_screen = 0;
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 1) {
        arg0->state = 6;
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
}

void func_800A4D20(struct ShotObj* arg0)
{
    s8 index = arg0->unk2;

    arg0->state = 8;
    arg0->on_screen = 1;
    arg0->unk61 = 1;
    arg0->y_vel.val = 0x18000;
    arg0->unk58.data = NULL;
    arg0->x_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk42 &= 0x7FFF;
    if (arg0->unk15 == 0)
        arg0->x_pos.i.hi += (s8)D_8010980C[index * 2];
    else
        arg0->x_pos.i.hi -= (s8)D_8010980C[index * 2];
    arg0->y_pos.i.hi += (s8)D_8010980C[index * 2 + 1];
    arg0->unk50.data = D_801097F8;
    arg0->unk5C = 1;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->unk54 = NULL;
    arg0->unk60 = 6;
    arg0->unk28 = D_80109838[index];
    func_80015D60(arg0, 0x12);
}

void func_800A5194(struct ShotObj* arg0)
{
    s32 dx;
    s32 steps;
    s16 divisor;
    s32 x = arg0->x_pos.val;
    s32 y = arg0->y_pos.val;
    s32 vx;
    s32 vy;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->timer != 0)
        return;
    dx = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if (dx < 0)
        dx = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
    steps = 0x2A - (0xCD - dx) / 6;
    do {
        divisor = steps;
        arg0->x_vel.val = (g_Player.x_pos.val - x) / divisor;
        steps += 5;
        arg0->y_vel.val = ((divisor + 1) << 11) + (y - g_Player.y_pos.val) / divisor;
        vx = arg0->x_vel.val < 0 ? -arg0->x_vel.val : arg0->x_vel.val;
        vy = arg0->y_vel.val < 0 ? -arg0->y_vel.val : arg0->y_vel.val;
    } while (vx > 0x60000 || vy > 0x60000);
    arg0->unk2C = 0x1000;
    arg0->unk5 = 6;
}

extern u8 D_801005B0[];
extern char D_801005B4[];
extern u16 D_801005B8[];
extern u16 D_801005C8[];
extern union AnimationStep* D_80100514[];
extern struct Unk_unk68 D_801078F8[];
extern union AnimationStep D_801001FC[];
extern struct Unk_unk68 D_8010020C;
extern struct Unk_unk68 D_80100218;
extern struct Unk_unk68 D_8010021C;
extern struct Unk_unk68 D_8010023C;
extern struct Unk_unk68 D_80100228;
extern struct Unk_unk68 D_8010022C;
extern union AnimationStep D_80100230[];
extern union AnimationStep D_80100234[];
extern union AnimationStep D_80100238[];
extern struct Unk_unk68 D_80100240;
extern struct Unk_unk68 D_80100244;
extern struct Unk_unk68 D_80100248;
extern struct Unk_unk68 D_8010024C;

#define M54_FLASH(o) ((o)->ext.main_54.pad80[0])
#define M54_81(o) ((o)->ext.main_54.pad80[1])
#define M54_82(o) ((o)->ext.main_54.pad80[2])
#define M54_84(o) ((o)->ext.main_54.pad80[4])
#define M54_85(o) ((o)->ext.main_54.pad80[5])

void func_8006E920(struct MainObj* arg0, s32 value)
{
    s32 start = 0;
    s32 end;
    s32 i;
    u32* attrs;
    u16 index;

    if (value == 0x38) {
        end = engine_obj.stage == 0xC ? 0xE : 8;
    } else if (arg0->unk15 == 0) {
        if (engine_obj.stage == 0xC) {
            start = 7;
            end = 0xE;
        } else {
            start = 4;
            end = 8;
        }
    } else {
        end = engine_obj.stage == 0xC ? 7 : 4;
    }
    for (i = start; i < end; i++) {
        index = engine_obj.stage == 0xC ? D_801005C8[i] : D_801005B8[i];
        attrs = SP_BG_TILE_ATTRS;
        attrs[index] &= ~0xFF;
        attrs[index] |= value;
    }
}

void func_8006BB70(struct MainObj* arg0)
{
    arg0->unk60 = 6;
    arg0->unk5C = 0;
    arg0->unk61 = 0;
    arg0->collision_data = D_801078F8;
    if (engine_obj.stage != 0xC) {
        arg0->unk40 = (D_801406A8[0] >> 7) + 0xB0;
    } else {
        arg0->unk40 = (D_801406A8[0] >> 7) + 0x160;
        arg0->unk42 = 0x7888;
        arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[4];
        arg0->y_pos.val = background_objects[g_Player.bg_offset].y_pos.val + (s32)0xFFD00000;
    }
    arg0->animation_table = (const u8* const*)D_80100514;
    arg0->unk16 = 6;
    arg0->unk54 = D_801001FC;
    arg0->unk50 = D_801001F8;
    arg0->unk15 = 0x40;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk68 = NULL;
    M54_FLASH(arg0) = 0;
    M54_81(arg0) = 1;
    M54_82(arg0) = 0;
    M54_84(arg0) = 0;
    M54_85(arg0) = 0;
    arg0->ext.main_54.unk86 = 0;
    arg0->ext.main_54.unk89 = 0;
    arg0->ext.main_54.unk8A = 1;
    arg0->ext.main_54.unk95 = 0;
    arg0->ext.main_54.unk96 = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    func_8006E920(arg0, 0x38);
    func_80015D60(arg0, 0);
    arg0->state = 1;
    arg0->unk5 = 9;
    arg0->unk6 = 0;
}

void func_8006BD1C(struct MainObj* arg0)
{
    s32 hit;
    s8 flash;
    const void* saved;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_801005F0[arg0->unk5](arg0);
    if (arg0->ext.main_54.pad88 != 0) {
        if (--arg0->ext.main_54.pad88 == 0)
            func_8006E920(arg0, 0x38);
    }
    if (engine_obj.stage == 8 && arg0->ext.main_54.unk89 == 1 && arg0->ext.main_54.unk95 != 0)
        engine_obj.character_state.bytes[1] = 1;
    if (M54_85(arg0) == 0)
        return;
    hit = func_8002DD04(arg0);
    flash = (s8)M54_FLASH(arg0);
    M54_82(arg0) = 0;
    if (flash == 0) {
        if (hit < 0) {
            func_8006E920(arg0, 0x38);
            g_Player.unk7A = 1;
            arg0->state = 2;
            arg0->unk5 = 0;
            return;
        }
        if (hit != 0 && hit != 0x7F) {
            M54_82(arg0) = 1;
            arg0->collision_data = D_801060F0;
            arg0->unk42 |= 0x8000;
            M54_FLASH(arg0) = (u32)(hit - 0x19) < 2 ? 4 : 0x40;
            if ((hit == 6 || hit == 0xF) && M54_84(arg0) == 0 && arg0->ext.main_54.unk86 == 0) {
                arg0->unk60 = 6;
                arg0->unk5 = 0xA;
                arg0->unk6 = 0;
            }
        }
    } else {
        M54_FLASH(arg0) = --flash;
        if (flash == 0) {
            arg0->collision_data = D_801078F8;
            arg0->unk42 &= 0x7FFF;
        } else if (flash & 1) {
            arg0->unk42 &= 0x7FFF;
        } else {
            arg0->unk42 |= 0x8000;
        }
    }
    if (arg0->unk5C < 0x11)
        arg0->ext.main_54.unk89 = 2;
    else if (arg0->unk5C < 0x21)
        arg0->ext.main_54.unk89 = 1;
    if (M54_84(arg0) & 0x80)
        arg0->unk50 = &D_80100218;
    func_8002D9BC(arg0);
    if (arg0->ext.main_54.unk86 != 0) {
        saved = arg0->unk50;
        arg0->unk50 = &D_8010021C;
        func_8002D9BC(arg0);
        arg0->unk50 = saved;
    }
    if (arg0->animation_step.fields.frame_index == 0x25) {
        saved = arg0->unk50;
        arg0->unk50 = &D_8010023C;
        func_8002D9BC(arg0);
        arg0->unk50 = saved;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x60, 0x60);
}

void func_8006C170(struct MainObj* arg0)
{
    struct BaseObj* effect = (struct BaseObj*)arg0->ext.main_54.unk8C;
    u16 flash;

    arg0->on_screen = 0;
    if (effect->active == 0) {
        memset(&arg0->ext.main_54, 0, sizeof(arg0->ext.main_54));
        engine_obj.enable_boss = 0;
        engine_obj.boss_ptr = NULL;
        if (engine_obj.stage == 0xC) {
            engine_obj.unkF = -0x80;
            engine_obj.character_state.bytes[engine_obj.checkpoint + 6] = 1;
            engine_obj.checkpoint += 9;
        } else {
            engine_obj.unkF = 0x10;
        }
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (effect->unk7 != 0)
        return;
    flash = arg0->unk7E;
    arg0->unk7E = flash - 1;
    if (flash == 0) {
        arg0->unk7E = 5;
        arg0->unk42 ^= 0x8000;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x60, 0x60);
}

static void main54_spawn_shot(struct MainObj* arg0, s8 subtype)
{
    struct ShotObj* shot = find_free_shot_obj();

    if (shot == NULL)
        return;
    shot->active = 0x41;
    shot->id = 0x1F;
    shot->unk2 = subtype;
    shot->unk40 = arg0->unk40;
    shot->unk42 = arg0->unk42;
    shot->animation_table = (void*)arg0->animation_table;
    shot->unk3C = (void*)arg0->sprite_frames;
    shot->bg_offset = arg0->bg_offset;
    shot->x_pos.val = arg0->x_pos.val;
    shot->y_pos.val = arg0->y_pos.val;
    shot->unk7C = (struct WeaponObj*)arg0;
    shot->state = 0;
    shot->unk15 = arg0->unk15;
}

void func_8006C378(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk20 == 0) {
        arg0->unk28 = 0;
        arg0->unk2C = 0;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    switch (arg0->animation_step.fields.event) {
    case 1:
        func_80015D60(arg0, 0x25);
        arg0->unk2C = 0x3800;
        arg0->unk6 = 2;
        break;
    case 2:
        arg0->unk50 = D_80100230;
        arg0->unk54 = D_80100234;
        func_8001540C(2, 0x84, arg0);
        main54_spawn_shot(arg0, 0);
        break;
    case 3:
        arg0->unk50 = D_80100238;
        arg0->unk54 = &D_80100240;
        func_8001540C(2, 0x84, arg0);
        if (M54_81(arg0) != 0)
            main54_spawn_shot(arg0, 1);
        break;
    case 4:
        arg0->unk50 = &D_80100228;
        arg0->unk54 = &D_8010022C;
        break;
    case 5:
        arg0->unk50 = &D_80100244;
        arg0->unk54 = &D_80100248;
        break;
    case 6:
        arg0->unk50 = D_801001F8;
        arg0->unk54 = D_801001FC;
    case 7:
        arg0->unk50 = &D_80100208;
        arg0->unk54 = &D_8010020C;
        break;
    }
}

static s32 main54_player_dx(struct MainObj* arg0)
{
    s32 dx = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;

    return dx < 0 ? -dx : dx;
}

static void main54_face_anim(struct MainObj* arg0, s32 anim)
{
    func_8006EA78(arg0);
    func_80015D60(arg0, anim);
}

void func_8006C6AC(struct MainObj* arg0)
{
    u8* cursor;
    s8 next;

    if (main54_player_dx(arg0) >= 0xA1 && (get_random() & 7) == 0) {
        if (arg0->unk5C < 0x10) {
            main54_face_anim(arg0, 0x26);
            M54_84(arg0) = 1;
            next = 7;
        } else {
            main54_face_anim(arg0, 8);
            next = 2;
        }
        goto set_state;
    }
    cursor = arg0->ext.main_54.unk90;
    arg0->ext.main_54.unk90 = cursor + 1;
    if (*cursor == 0xFF)
        func_8006EAA8(arg0);
    switch (*arg0->ext.main_54.unk90) {
    case 0:
        if ((get_random() & 7) == 0) {
            main54_face_anim(arg0, 8);
            next = 2;
            goto set_state;
        }
        main54_face_anim(arg0, 0xB);
        arg0->unk7C = 0x3C;
        arg0->unk6 = 1;
        return;
    case 1:
        if ((get_random() & 7) == 0) {
            main54_face_anim(arg0, 8);
            next = 2;
        } else if (main54_player_dx(arg0) < 0x70) {
            if (M54_81(arg0) != 0) {
                func_80015D60(arg0, 0x26);
                next = 0xB;
            } else {
                main54_face_anim(arg0, 0xC);
                arg0->unk7C = 0x24;
                arg0->unk7E = 2;
                next = 6;
            }
        } else {
            main54_face_anim(arg0, 1);
            arg0->ext.main_54.unk96 = 0;
            next = 4;
        }
        break;
    case 2:
        if (main54_player_dx(arg0) < 0x70 && (get_random() & 7) != 0) {
            if (M54_81(arg0) != 0) {
                func_80015D60(arg0, 0x26);
                next = 0xB;
            } else {
                main54_face_anim(arg0, 0xC);
                arg0->unk7C = 0x24;
                arg0->unk7E = 2;
                next = 6;
            }
        } else {
            main54_face_anim(arg0, 8);
            next = 2;
        }
        break;
    case 3:
        main54_face_anim(arg0, 0x26);
        next = 7;
        break;
    case 4:
        main54_face_anim(arg0, 0xC);
        arg0->unk7C = 0x24;
        arg0->unk7E = 2;
        next = 6;
        break;
    case 5:
        main54_face_anim(arg0, 0x14);
        func_8001540C(2, 0x85, arg0);
        arg0->unk7C = 0x5A;
        next = 5;
        break;
    case 6:
        main54_face_anim(arg0, 0x26);
        M54_84(arg0) = 1;
        next = 7;
        break;
    case 7:
        main54_face_anim(arg0, 1);
        arg0->ext.main_54.unk96 = 1;
        next = 4;
        break;
    default:
        return;
    }
set_state:
    arg0->unk5 = next;
    arg0->unk6 = 0;
}

void func_8006CB50(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        return;
    }
    arg0->unk28 = 0;
    func_80015D60(arg0, 2);
    arg0->unk54 = &D_8010020C;
    arg0->unk50 = &D_80100208;
    if (arg0->ext.main_54.unk96 == 0) {
        arg0->unk20 = arg0->unk15 != 0 ? 0x24000 : -0x24000;
        arg0->unk24 = 0x5C000;
    } else {
        arg0->unk20 = arg0->unk15 != 0 ? 0x36000 : -0x36000;
        arg0->unk24 = 0x7C000;
    }
    arg0->unk2C = 0x3800;
    func_8001540C(2, 0x81, arg0);
    func_8002B694(ANIMATED_OBJECT(arg0));
    arg0->unk6 = 1;
}

void func_8006CC3C(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        arg0->unk60 = 6;
        arg0->unk54 = D_801001FC;
        arg0->unk62 = 0;
        arg0->unk50 = D_801001F8;
    }
    if (M54_84(arg0) != 0 && g_Player.unkBA != 0) {
        func_8001540C(2, 0x86, arg0);
        g_Player.unk15 = arg0->unk15;
        if (arg0->unk15 == 0)
            g_Player.x_pos.i.hi = arg0->x_pos.i.hi - 0x12;
        else
            g_Player.x_pos.i.hi = arg0->x_pos.i.hi + 0x12;
        g_Player.y_pos.i.hi = arg0->y_pos.i.hi - 8;
        arg0->unk6 = 1;
    }
    if (arg0->unk70 & 8) {
        func_8001540C(2, 0x82, arg0);
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        if (M54_84(arg0) != 0) {
            arg0->unk7C = 0xA;
            arg0->unk5 = 8;
            arg0->unk6 = 0;
        } else {
            func_80015D60(arg0, 3);
            arg0->unk6 = 2;
        }
    }
}

void func_8006CDD4(struct MainObj* arg0)
{
    s32 behind;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (M54_82(arg0) != 0) {
        if (arg0->unk15 == 0)
            behind = g_Player.x_pos.i.hi < arg0->x_pos.i.hi;
        else
            behind = arg0->x_pos.i.hi < g_Player.x_pos.i.hi;
        if (behind) {
            arg0->unk5 = 2;
            arg0->unk6 = 0;
            return;
        }
    }
    if (--arg0->unk7C == 0) {
        arg0->unk7C = 0x1E;
        func_80015D60(arg0, 0);
        func_8006EA78(arg0);
        arg0->unk5 = 3;
        arg0->unk6 = 1;
    }
}

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
    if (--arg0->ext.main_54.unk87 != 0)
        return;
    main54_spawn_trail(arg0, 0x21, 0);
    if (M54_81(arg0) != 0)
        main54_spawn_trail(arg0, 0x20, 0x3C);
    arg0->ext.main_54.unk87 = 0xA;
}

void func_8006CFB8(struct MainObj* arg0)
{
    s32 limit;
    s32 speed;

    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    main54_trails(arg0);
    limit = M54_81(arg0) != 0 ? 0x77FFF : 0x5FFFF;
    speed = arg0->unk20 < 0 ? -arg0->unk20 : arg0->unk20;
    if (limit < speed)
        arg0->unk28 = 0;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk15 == 0) {
        if (!(arg0->unk70 & 2))
            return;
    } else {
        if (!(arg0->unk70 & 1))
            return;
    }
    func_80028B68(0x1E, 8, 2);
    arg0->unk60 = 6;
    func_80015D60(arg0, 0xF);
    arg0->unk6 = 3;
    arg0->unk54 = NULL;
    arg0->unk50 = NULL;
    arg0->ext.main_54.pad88 = 0x1E;
    func_8001540C(2, 0x88, arg0);
    func_8006E920(arg0, 0x39);
}

void func_8006D280(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        arg0->unk54 = D_801001FC;
        arg0->ext.main_54.unk86 = 0;
        arg0->unk50 = D_801001F8;
    }
    if (arg0->animation_step.fields.event != 1)
        return;
    arg0->unk15 ^= 0x40;
    if (--arg0->unk7E == 0) {
        func_80015D60(arg0, 0x25);
        arg0->unk2C = 0x3800;
        arg0->unk5 = 4;
        arg0->unk6 = 1;
    } else {
        func_80015D60(arg0, 0x10);
        if (arg0->unk15 == 0)
            arg0->x_pos.i.hi -= 0x20;
        else
            arg0->x_pos.i.hi += 0x20;
        arg0->unk6 = 4;
    }
}

void func_8006D3DC(struct MainObj* arg0)
{
    s32 target;
    s32 steps;
    s32 dist;
    s32 speed;
    s32 d;

    if (main54_player_dx(arg0) < 0x70) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
        return;
    }
    if (arg0->animation_step.fields.event == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        return;
    }
    arg0->unk28 = 0;
    if (M54_84(arg0) == 0) {
        func_80015D60(arg0, 2);
        target = arg0->x_pos.val;
        arg0->unk54 = &D_8010020C;
        arg0->unk50 = &D_80100208;
    } else {
        M54_84(arg0) |= 0x80;
        target = arg0->x_pos.val + (arg0->unk15 != 0 ? 0x100000 : (s32)0xFFF00000);
        arg0->unk60 = 0;
        arg0->unk62 = 3;
        func_80015D60(arg0, 4);
        func_8001540C(2, 0x87, arg0);
    }
    d = target - g_Player.x_pos.val;
    if (M54_84(arg0) != 0) {
        if (d >= 0) {
            steps = (u32)d >> 16;
        } else {
            d = g_Player.x_pos.val - target;
            if (d < 0)
                d += 0xFFFF;
            steps = (u32)d >> 16;
        }
        arg0->unk2C = 0x6800;
    } else {
        if (d < 0)
            d = g_Player.x_pos.val - target;
        steps = d / 0x24000;
        arg0->unk2C = 0x3800;
    }
    if (arg0->unk15 == 0)
        arg0->unk20 = -0x1C000 - (s16)steps * 0x480;
    else
        arg0->unk20 = (s16)steps * 0x480 + 0x1C000;
    dist = target - g_Player.x_pos.val;
    if (dist < 0)
        dist = g_Player.x_pos.val - target;
    speed = arg0->unk20 < 0 ? -arg0->unk20 : arg0->unk20;
    arg0->unk24 = (((s16)(dist / speed) + 1) * arg0->unk2C) / 2;
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_8001540C(2, 0x81, arg0);
    arg0->unk5 = 4;
    arg0->unk6 = 1;
}

void func_8006D6D8(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 6);
        arg0->unk16 = 6;
        arg0->unk60 = 6;
        arg0->unk54 = D_801001FC;
        arg0->unk50 = D_801001F8;
        arg0->unk5 = 4;
        arg0->unk62 = 0;
        M54_84(arg0) = 0;
        arg0->unk6 = 2;
    }
    if (g_Player.unkBA == 0)
        return;
    func_8001540C(2, 0x86, arg0);
    if (arg0->x_pos.i.hi - background_objects[0].x_pos.i.hi < 0xA1)
        arg0->unk15 = 0x40;
    else
        arg0->unk15 = 0;
    g_Player.unk15 = arg0->unk15;
    g_Player.y_pos.i.hi = arg0->y_pos.i.hi - 8;
    if (arg0->unk15 == 0) {
        g_Player.x_pos.i.hi = arg0->x_pos.i.hi - 0x23;
        arg0->unk20 = -0x60000;
    } else {
        g_Player.x_pos.i.hi = arg0->x_pos.i.hi + 0x23;
        arg0->unk20 = 0x60000;
    }
    func_80015D60(arg0, 5);
    arg0->unk16 = 1;
    arg0->unk7C = 0x30;
    arg0->unk6 = 1;
}

void func_8006D888(struct MainObj* arg0)
{
    s16 y;
    s16 x;

    func_8002B718(MOVING_OBJECT(arg0));
    main54_trails(arg0);
    y = arg0->y_pos.i.hi + arg0->unk68->unk1;
    if (arg0->unk15 == 0) {
        g_Player.x_pos.i.hi = arg0->x_pos.i.hi - 0x23;
        x = arg0->x_pos.i.hi + arg0->unk68->unk0 - 0x30;
    } else {
        g_Player.x_pos.i.hi = arg0->x_pos.i.hi + 0x23;
        x = arg0->x_pos.i.hi + arg0->unk68->unk0 + 0x30;
    }
    if (func_8002D724(PLAYER_OBJECT(arg0), x, y) == 0x38) {
        func_8001540C(2, 0x88, arg0);
        arg0->unk6 = 3;
    }
}

void func_8006DD44(struct MainObj* arg0)
{
    struct ItemObj* item;
    struct MiscObj* misc;

    if (--arg0->unk7E != 0)
        return;
    if (engine_obj.stage != 0xC) {
        item = find_free_item_obj();
        if (item != NULL) {
            item->active = 0x41;
            item->id = 0x12;
            item->unk16 = 5;
            item->unk2 = 3 - (u8)arg0->unk7C;
            item->unk40 = arg0->unk40;
            item->unk42 = arg0->unk42 & 0x7FFF;
            item->animation_table = arg0->animation_table;
            item->sprite_frames = arg0->sprite_frames;
            item->animation_step.fields.frame_index = 0x79;
            item->state = 0;
            item->bg_offset = arg0->bg_offset;
        }
    }
    if (--arg0->unk7C != 0 && engine_obj.stage != 0xC) {
        arg0->unk7E = 0x1E;
        return;
    }
    engine_obj.enable_boss = 1;
    engine_obj.unk25 = 1;
    engine_obj.boss_ptr = arg0;
    arg0->unk7C = 0xC8;
    misc = find_free_misc_obj();
    if (misc != NULL) {
        misc->active = 0x41;
        misc->id = 0x1A;
        misc->unk2 = 0;
        misc->unk16 = 5;
        misc->unk40 = arg0->unk40;
        misc->unk42 = arg0->unk42 & 0x7FFF;
        misc->animation_table = (void*)arg0->animation_table;
        misc->unk3C = (void*)arg0->sprite_frames;
        misc->bg_offset = arg0->bg_offset;
        misc->x_pos.val = arg0->x_pos.val;
        misc->y_pos.val = arg0->y_pos.val;
        misc->unk15 = arg0->unk15;
        misc->ext.misc_26.owner = arg0;
        misc->state = 0;
        misc->animation_step.fields.frame_index = arg0->animation_step.fields.frame_index + 0x3C;
    }
    if (engine_obj.stage == 8) {
        arg0->unk15 = 0x40;
        func_80015D60(arg0, 0x15);
        arg0->unk20 = 0x10000;
        arg0->unk6 = 3;
    } else {
        arg0->unk15 = 0;
        func_80015D60(arg0, 0x17);
        arg0->unk7E = 1;
        arg0->unk6 = 4;
    }
}

void func_8006E034(struct MainObj* arg0)
{
    s16 x;
    s16 y;

    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->x_pos.i.hi - background_objects[0].x_pos.i.hi >= 0xE0) {
        arg0->unk20 = 0;
        arg0->unk2C = 0x10000;
    }
    if (arg0->unk24 == 0) {
        arg0->unk68 = &D_8010024C;
        func_80015D60(arg0, 0x17);
    }
    if (arg0->unk24 < 0) {
        if (arg0->unk7E == 0) {
            x = arg0->x_pos.i.hi + arg0->unk68->unk0;
            y = arg0->unk68->unk3 + (arg0->y_pos.i.hi + arg0->unk68->unk1) + 0x40;
            if (func_8002D724(PLAYER_OBJECT(arg0), x, y) == 0x38) {
                if (engine_obj.stage == 8) {
                    func_800DABE4(8, 0x2580, 0x140);
                    func_8001540C(2, 0x80, arg0);
                    func_800C813C(4, D_801005B0, arg0);
                }
                arg0->unk7E = 1;
            }
        } else if (arg0->unk7E == 1) {
            x = arg0->x_pos.i.hi + arg0->unk68->unk0;
            y = arg0->unk68->unk3 + (arg0->y_pos.i.hi + arg0->unk68->unk1) + 0x10;
            if (func_8002D724(PLAYER_OBJECT(arg0), x, y) == 0x38) {
                arg0->unk7E = 2;
                func_80015D60(arg0, 3);
                if (engine_obj.stage == 0xC)
                    func_8001540C(2, 0x82, arg0);
            }
        }
    }
    if (arg0->unk70 & 8) {
        func_80028BAC(0x10, 4, 2);
        M54_85(arg0) = 1;
        arg0->unk6 = 5;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x60, 0x60);
}

void func_8006E450(struct MainObj* arg0)
{
    s16 x;
    s16 y;

    if (--arg0->ext.main_54.unk8A == 0) {
        y = arg0->y_pos.i.hi;
        arg0->y_pos.i.hi = y - 4;
        x = arg0->x_pos.i.hi;
        if (arg0->unk15 == 0)
            arg0->x_pos.i.hi = x + 0x1B;
        else
            arg0->x_pos.i.hi = x - 0x1B;
        func_800C813C(3, D_801005B4, arg0);
        arg0->y_pos.i.hi = y + 0xC;
        if (arg0->unk15 == 0)
            arg0->x_pos.i.hi = x + 0x1D;
        else
            arg0->x_pos.i.hi = x - 0x1D;
        func_800C813C(3, D_801005B4, arg0);
        arg0->x_pos.i.hi = x;
        arg0->y_pos.i.hi = y;
        M54_81(arg0) = 0;
    }
    func_80015D60(arg0, 0x11);
    if (arg0->x_pos.i.hi < g_Player.x_pos.i.hi) {
        arg0->unk15 = 0;
        arg0->unk20 = -0x10000;
    } else {
        arg0->unk15 = 0x40;
        arg0->unk20 = 0x10000;
    }
    arg0->unk24 = 0x40000;
    arg0->unk28 = 0;
    arg0->unk2C = 0x8000;
    func_8002B718(MOVING_OBJECT(arg0));
    arg0->unk6 = 1;
}

void func_800CC7F8(struct MiscObj* arg0)
{
    struct MainObj* owner = arg0->ext.misc_26.owner;

    if (arg0->unk2 == 0) {
        arg0->x_pos.val = owner->x_pos.val;
        arg0->y_pos.val = arg0->ext.misc_26.owner->y_pos.val;
        arg0->unk15 = arg0->ext.misc_26.owner->unk15;
        arg0->unk42 = arg0->ext.misc_26.owner->unk42;
        arg0->animation_step.fields.frame_index = arg0->ext.misc_26.owner->animation_step.fields.frame_index + 0x3C;
        owner = arg0->ext.misc_26.owner;
        if (owner->state >= 2 || owner->ext.main_54.pad80[1] == 0) {
            arg0->state = 1;
            return;
        }
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    arg0->ext.misc_26.timer--;
    if (owner->state >= 2 || arg0->ext.misc_26.timer == 0) {
        arg0->state = 1;
        return;
    }
    if (arg0->ext.misc_26.timer & 3)
        arg0->on_screen = 0;
    else
        is_on_screen(BASE_OBJECT(arg0));
}

extern u32* D_8011C0C8[];
extern struct Unk_unk68 D_8010894C[];

void func_80095854(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    arg0->unk50 = D_80108944;
    arg0->unk68 = D_8010894C;
    arg0->unk38 = (u8*)player_gfx + player_gfx[6];
    arg0->animation_table = D_8011C0C8;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0xE];
    arg0->unk15 = g_Player.unk15;
    func_80092E2C((struct VisualObj*)arg0, &g_Player, arg0->id);
    arg0->x_vel.val = arg0->unk15 != 0 ? 0x60000 : -0x60000;
    arg0->y_vel.val = -0x20000;
    arg0->unk28.val = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 1;
    func_80015D60(arg0, 0);
    func_8001540C(1, 8, arg0);
    arg0->unk5 = 0;
    arg0->state++;
    func_8002B318(BASE_OBJECT(arg0), 0x2C, 0x20);
}
