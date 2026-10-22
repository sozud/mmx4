// ItemObj, item_object_update_funcs[4]
// 800C081C..800C0E74
#include "common.h"
#include "main/items/item_04_destructible_core.h"
#include "main/visuals/visual_08_ice_shard.h"
#include "main/object_motion.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/CB184.h"
#include "main/objects.h"

extern u8 destructible_core_debris[];
extern s32 destructible_core_explosion_sounds[4];

// destructible_core_state_funcs
extern void (*destructible_core_state_funcs[])(struct ItemObj*);

void destructible_core_main(struct ItemObj*);
void destructible_core_destroyed(struct ItemObj*);
void destructible_core_finish(struct ItemObj*);
void destructible_core_flash_palette(struct ItemObj*);
#include "weapon_resources.h"

#ifdef MMX4_SATURN
struct Item04Data destructible_core_data = {
    0x0CC0,
    { 0x0168, 0x0CB0, 0x0CC0, 0x0CB0, 0, 0 },
    {
        0x00,
        0x00,
        0x06,
        0xC8,
        0x01,
        0x98,
        0x0C,
        0xB0,
        0x0C,
        0xC0,
        0x0C,
        0xB0,
        0x00,
        0x00,
        0x00,
        0x00,
        0x01,
        0x00,
        0x08,
        0xC8,
        0x01,
        0x98,
        0x0C,
        0xB0,
        0x0C,
        0xC0,
        0x0C,
        0xB0,
        0x00,
        0x00,
        0x00,
        0x00,
        0x02,
        0x00,
        0x0A,
        0xC8,
        0x01,
        0x98,
        0x0C,
        0xB0,
        0x0C,
        0xC0,
        0x0C,
        0xB0,
        0x00,
        0x00,
        0x00,
        0x00,
        0x03,
        0x00,
    },
};
#else
struct Item04Data destructible_core_data = {
    0x0CC0,
    { 0x0168, 0x0CB0, 0x0CC0, 0x0CB0, 0, 0 },
    {
        0,
        0,
        0xC8,
        6,
        0x98,
        1,
        0xB0,
        0xC,
        0xC0,
        0xC,
        0xB0,
        0xC,
        0,
        0,
        0,
        0,
        1,
        0,
        0xC8,
        8,
        0x98,
        1,
        0xB0,
        0xC,
        0xC0,
        0xC,
        0xB0,
        0xC,
        0,
        0,
        0,
        0,
        2,
        0,
        0xC8,
        0xA,
        0x98,
        1,
        0xB0,
        0xC,
        0xC0,
        0xC,
        0xB0,
        0xC,
        0,
        0,
        0,
        0,
        3,
        0,
    },
};
#endif

u8 destructible_core_boxes[4][4] = {
    { 0xE8, 0xA8, 0x18, 0xA0 },
    { 0xE8, 0xD8, 0x18, 0x50 },
    { 0xE8, 0xD8, 0x18, 0x50 },
    { 0xE8, 0xD8, 0x18, 0x50 },
};

u8 destructible_core_debris[4] = { 0x0A, 0x0B, 0x0C, 0x0D };

void destructible_core_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    destructible_core_state_funcs[arg0->state](arg0);
}

// destructible_core_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800C0864(struct ItemObj* arg0);
extern u32* dragon_rubble_animations[14];
extern struct Unk_unk68 D_80108504[];
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800C0864(struct ItemObj* arg0)
{
    const u16* layout = (const u16*)&destructible_core_data;
    s32 slot = arg0->unk2;

    if (engine_obj.checkpoint >= 2 && slot == 0) {
        apply_tile_effect(destructible_core_data.object_ids[slot * 0x10], 0, 0);
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }

    arg0->state = 0;
    arg0->unk5 = 1;
    arg0->active = 1;
    arg0->state = (u8)arg0->state + 1;
    arg0->animation_table = (const u8* const*)dragon_rubble_animations;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk42 = OBJECT_CLUT(0x78C0);
    arg0->unk40 = (u16)((u32)OBJECT_STAGE_TEXTURE(6));
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
    arg0->unk54 = (const u8*)destructible_core_boxes[slot];
    arg0->tail_ext.unk1.unk84.previous_value = arg0->unk5C;
}
#else
INCLUDE_ASM("main/nonmatchings/items/item_04_destructible_core", func_800C0864);
#endif

void destructible_core_main(struct ItemObj* arg0)
{
    s32 temp_s1;
    u8 state;

    temp_s1 = func_8002DD04(MAIN_OBJECT(arg0));
    if (((arg0->unk5C < arg0->tail_ext.unk1.unk84.previous_value) && (arg0->unk5C != 0)) || (arg0->tail_ext.unk1.unk88 != 0)) {
        destructible_core_flash_palette(arg0);
        arg0->tail_ext.unk1.unk88 ^= 1;
    }

    arg0->tail_ext.unk1.unk84.previous_value = arg0->unk5C;
    if (arg0->unk2 == 0) {
        arg0->ext.timer = arg0->ext.timer - 1;
        if (arg0->ext.timer == 0) {
            arg0->ext.timer = 5;
            if (arg0->unk5C < 0x50) {
                func_800B10E4(0x11, 0xCA8, 0x198, 0xCB8, 0x1A8, 1);
            }
            if (arg0->unk5C < 0x3C) {
                func_800B10E4(0x11, 0xC90, 0x168, 0xCA0, 0x180, 1);
            }
            if (arg0->unk5C < 0x28) {
                func_800B10E4(0x11, 0xCA8, 0x140, 0xCB8, 0x160, 1);
            }
        }
    }

    if (temp_s1 < 0) {
        apply_tile_effect(destructible_core_data.object_ids[arg0->unk2 * 0x10], 0, 0);
        switch (arg0->unk2) {
        case 0:
            engine_obj.character_state.bytes[0] = 1;
            break;
        case 1:
            engine_obj.character_state.bytes[1] = 1;
            break;
        case 2:
            engine_obj.character_state.bytes[2] = 1;
            break;
        case 3:
            engine_obj.character_state.bytes[3] = 1;
            break;
        }

        if (arg0->unk2 != 0) {
            arg0->unk7C.timer = 0x1E;
        } else {
            arg0->unk7C.timer = 0x50;
        }
        state = arg0->state;
        arg0->state = state + 1;
    } else {
        if (engine_obj.character_state.bytes[1] != 0 && arg0->unk2 == 1) {
            arg0->state += 2;
        }
        if (engine_obj.character_state.bytes[2] != 0 && arg0->unk2 == 2) {
            arg0->state += 2;
        }
        if (engine_obj.character_state.bytes[3] == 0 || arg0->unk2 != 3) {
            return;
        }
        state = arg0->state;
        arg0->state = state + 2;
    }
}

void destructible_core_destroyed(struct ItemObj* arg0)
{
    u32 temp_v0;
    u32 var_v0;

    temp_v0 = arg0->unk7C.timer - 1;
    arg0->unk7C.timer = temp_v0;
    if (temp_v0 != 0) {
        if ((WEAPON_FRAME_COUNTER & 3) == 0) {
            if (arg0->unk2 != 0) {
                func_800AF878(arg0, 1, 0x20, 0x30);
            } else {
                func_800AF878(arg0, 1, 0x20, 0x70);
            }
        }
        if (arg0->unk2 != 0) {
            var_v0 = WEAPON_FRAME_COUNTER & 3;
        } else {
            var_v0 = WEAPON_FRAME_COUNTER & 7;
        }
        if (var_v0 == 0) {
            spawn_debris(4, destructible_core_debris, arg0);
        }
        if ((WEAPON_FRAME_COUNTER & 0xF) == 0) {
            func_8001540C(
                0, destructible_core_explosion_sounds[get_random() & 3], (struct Unk6*)arg0);
        }
    } else {
        arg0->state++;
    }
}

void destructible_core_finish(struct ItemObj* arg0)
{
    if (arg0->unk2 == 0) {
        background_objects[0].unk1C = 0x11C0;
        background_objects[0].unk24 = 0x11C0;
    }
    if (arg0->tail_ext.unk1.unk88 != 0) {
        destructible_core_flash_palette(arg0);
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void destructible_core_flash_palette(struct ItemObj* arg0)
{
    s32* destination;
    s32* source;
    u32 i;

#ifdef MMX4_SATURN
    destination = (s32*)SP_PALETTE + 0x3B8;
    if (arg0->tail_ext.unk1.unk88 != 0) {
        source = (s32*)0x060A59E0;
    } else {
        source = (s32*)0x060A5AC0;
    }
#else
    destination = SP_PALETTE_WORDS + 0x3B8;
    if (arg0->tail_ext.unk1.unk88 != 0) {
        source = SP_ARC_30 + 0x268;
    } else {
        source = SP_ARC_30 + 0x2A0;
    }
#endif
    i = 0;
    do {
        *destination++ = *source++;
        i++;
    } while (i < 0x38);
    need_palette_load |= 1;
}

void (*destructible_core_state_funcs[])(struct ItemObj*) = {
    func_800C0864,
    destructible_core_main,
    destructible_core_destroyed,
    destructible_core_finish,
};

s32 destructible_core_explosion_sounds[4] = { 0, 1, 2, 3 };
