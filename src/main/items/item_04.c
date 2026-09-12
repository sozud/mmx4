// ItemObj, item_object_update_funcs[4]
// 800C081C..800C0E74
#include "common.h"

struct Item04Data D_8010C8B4 = {
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

u8 D_8010C8F4[4][4] = {
    { 0xE8, 0xA8, 0x18, 0xA0 },
    { 0xE8, 0xD8, 0x18, 0x50 },
    { 0xE8, 0xD8, 0x18, 0x50 },
    { 0xE8, 0xD8, 0x18, 0x50 },
};

u8 D_8010C904[4] = { 0x0A, 0x0B, 0x0C, 0x0D };

void func_800C081C(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010C908[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_04", func_800C0864);

void func_800C09C4(struct ItemObj* arg0)
{
    s32 temp_s1;
    s32 temp_v0;
    s32 next_state;
    u32 temp_a0;
    u8 state;

    temp_s1 = func_8002DD04(MAIN_OBJECT(arg0));
    temp_a0 = arg0->unk5C;
    if (((temp_a0 < arg0->unk84.previous_value) && (temp_a0 != 0)) || (arg0->unk88 != 0)) {
        func_800C0DFC(arg0);
        arg0->unk88 ^= 1;
    }

    arg0->unk84.previous_value = arg0->unk5C;
    if (arg0->unk2 == 0) {
        temp_v0 = arg0->ext.item_4.timer - 1;
        arg0->ext.item_4.timer = temp_v0;
        if (temp_v0 == 0) {
            arg0->ext.item_4.timer = 5;
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
        func_800DABE4(D_8010C8B4.object_ids[arg0->unk2 * 0x10], 0, 0);
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
            arg0->unk7C.item_4_timer = 0x1E;
        } else {
            arg0->unk7C.item_4_timer = 0x50;
        }
        state = arg0->state;
        next_state = state + 1;
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
        next_state = state + 2;
    }

    arg0->state = next_state;
}

void func_800C0C78(struct ItemObj* arg0)
{
    s32 temp_v0;
    s32 var_v0;

    temp_v0 = arg0->unk7C.item_4_timer - 1;
    arg0->unk7C.item_4_timer = temp_v0;
    if (temp_v0 != 0) {
        if ((D_80141BD8.unk0 & 3) == 0) {
            if (arg0->unk2 != 0) {
                func_800AF878(arg0, 1, 0x20, 0x30);
            } else {
                func_800AF878(arg0, 1, 0x20, 0x70);
            }
        }
        if (arg0->unk2 != 0) {
            var_v0 = D_80141BD8.unk0 & 3;
        } else {
            var_v0 = D_80141BD8.unk0 & 7;
        }
        if (var_v0 == 0) {
            func_800C813C(4, D_8010C904, arg0);
        }
        if ((D_80141BD8.unk0 & 0xF) == 0) {
            func_8001540C(
                0, D_8010C918[get_random() & 3], (struct Unk6*)arg0);
        }
    } else {
        arg0->state++;
    }
}

void func_800C0D98(struct ItemObj* arg0)
{
    if (arg0->unk2 == 0) {
        background_objects[0].unk1C = 0x11C0;
        background_objects[0].unk24 = 0x11C0;
    }
    if (arg0->unk88 != 0) {
        func_800C0DFC(arg0);
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800C0DFC(struct ItemObj* arg0)
{
    s32* destination;
    s32* source;
    u32 i;

    destination = SP_PALETTE_WORDS + 0x3B8;
    if (arg0->unk88 != 0) {
        source = SP_ARC_30 + 0x268;
    } else {
        source = SP_ARC_30 + 0x2A0;
    }
    i = 0;
    do {
        *destination++ = *source++;
        i++;
    } while (i < 0x38);
    need_palette_load |= 1;
}

void (*D_8010C908[])(struct ItemObj*) = {
    func_800C0864,
    func_800C09C4,
    func_800C0C78,
    func_800C0D98,
};

s32 D_8010C918[4] = { 0, 1, 2, 3 };
