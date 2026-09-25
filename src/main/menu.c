// 800193D8..8001C6DC
#include "common.h"

#ifdef MMX4_PC
#include <psyz/audio.h>
#include <psyz/spu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif
extern u8 D_80171EA9;
extern u8 D_800F1DFC[];
extern u8 D_800F1E0C[];
extern u8 D_800F1E24[];
extern u8 D_800F1E34[];
extern u8 D_800F1E4C[];
extern u8 D_800F1E68[];
extern u8 D_800F1E78[];
extern u8 D_800F1E88[];
extern u8 D_800F1EB4[];
extern u8 D_800F1EC4[];
extern u8 D_800F1ED0[];
extern u8 D_800F1EE0[];
extern u8 D_800F1EF0[];
extern u8 D_800F1F00[];
extern u8 D_800F1F10[];
extern u8 D_800F1F20[];
extern u8 D_800F1F30[];
extern u8 D_800F1F48[];
extern u8 D_800F1F58[];
extern u8 D_800F1FBC[4];
extern const char D_80010058[];
extern const char D_8001005C[];

#ifdef MMX4_PC
const char D_80010058[4] = "";
const char D_8001005C[16] = "BASLUS-00561";
#else
INCLUDE_RODATA("main/nonmatchings/menu", D_80010058);

INCLUDE_RODATA("main/nonmatchings/menu", D_8001005C);
#endif

void func_800193D8(struct EngineObj* arg0)
{
    u8* ptr = D_80141BDF;
    u8 temp_s1 = *ptr;
    u8 temp_s3 = engine_obj.unk1;
    u8 temp_s4 = engine_obj.unk2;

    D_800F1F64[arg0->unk1](arg0);

    if (*ptr != temp_s1 && engine_obj.unk1 == temp_s3 && engine_obj.unk2 == temp_s4) {
        func_8001540C(0, 12, NULL);
    }
    if (arg0->unk1 != 10) {
        func_80016124();
        update_misc_objects();
        init_objects();
    }
}

INCLUDE_ASM("main/nonmatchings/menu", func_800194C8);

INCLUDE_ASM("main/nonmatchings/menu", func_8001961C);

void func_8001989C(struct EngineObj* arg0)
{
    u8* timer;
    u8* script;
    s32 status;
    u8 remaining;
    u8 result;

    timer = &D_801721BA;
    remaining = *timer - 1;
    *timer = remaining;
    if (remaining != 0) {
        return;
    }

    status = func_8001CDE4(D_801721B6);
    if (status != 0) {
        if (status == 1) {
            script = D_800F1DFC;
            arg0->unk1 = 0xB;
            result = 1;
        } else {
            script = D_800F1E24;
            arg0->unk1 = 0xB;
            result = 2;
        }
        D_801721B8 = result;
        func_8001B644(script);
        D_80141BDF[0] = 0;
        return;
    }

    status = func_8001CD70(D_801721B6);
    D_80141BDF[0] = 0;
    switch ((u32)status) {
    case 1:
        script = D_800F1DFC;
        arg0->unk1 = 0xB;
        result = 1;
        goto set_result;
    case 2:
        arg0->unk1 = (u8)arg0->unk1 + 1;
        return;
    case 3:
        script = D_800F1E24;
        arg0->unk1 = 0xB;
        result = 2;
    set_result:
        D_801721B8 = result;
        func_8001B644(script);
        return;
    case 0:
        arg0->unk1 = (u8)arg0->unk1 + 2;
        func_8001CC5C(D_801721B6, &D_80173AE0, D_80010058);
        if (D_80173AE0.total_size == 0x1E000) {
            func_8001CC5C(D_801721B6, &D_80173AE0, D_8001005C);
            if (D_80173AE0.count == 0) {
                arg0->unk1 = 0xB;
                D_801721B8 = 3;
                D_80141BDF[0] = 0;
                reset_objects();
                func_8001B644(D_800F1E34);
                return;
            }
            func_8001CB24(D_801721B0, D_801721B6, 0x2000);
        } else {
            func_8001CC5C(D_801721B6, &D_80173AE0, D_8001005C);
            if (D_80173AE0.count != 0) {
                func_8001CB24(D_801721B0, D_801721B6, 0x2000);
            } else {
                D_801721BC[0].character = 0xFF;
                D_801721BC[1].character = 0xFF;
                D_801721BC[2].character = 0xFF;
            }
        }
        reset_objects();
        func_8001B718(0x30, (D_801721B6 + 0x11) & 0xFF, 0xFF);
        func_8001B644(D_800F1E4C);
        func_8001B7C0(0xD0, 0x88, 0);
        func_8001C008(3, 3);
        return;
    }
}

void func_80019B64(struct EngineObj* arg0)
{
    D_800F1F94[arg0->unk2](arg0);
}

void func_80019BA0(struct EngineObj* arg0)
{
    arg0->unk2 = (u8)arg0->unk2 + 1;
    reset_objects();
    func_8001B644(D_800F1E90);
#ifndef VERSION_JP
    D_80141BDF[0] = 1;
#endif
    func_8001C008(4, 2);
}

void func_80019BF4(struct EngineObj* arg0)
{
    u16* controller = &controller_state;

    if (*controller & (PADLup | PADLdown)) {
        D_80141BDF[0] ^= 1;
    }
    if (*controller & PAD_SELECTION_BUTTONS) {
        func_8001540C(0, 0x22, 0);
        if (D_80141BDF[0] == 0 && !(*controller & PAD_SELECTION_ALT)) {
            arg0->unk2 = (u8)arg0->unk2 + 1;
            reset_objects();
            func_8001B644(D_800F1EAC);
            func_8001B718(0x40, (D_801721B6 + 0xB) & 0xFF, 0xFF);
            D_801721BA = 2;
            return;
        }
        reset_objects();
        D_80141BDF[0] = 0;
        arg0->unk1 = 0;
        arg0->unk2 = 0;
    }
}

void func_80019D04(struct EngineObj* arg0)
{
    u8* timer;
    u8* script;
    u8 status;
    u8 empty;

    timer = &D_801721BA;
    if (*timer != 0) {
        (*timer)--;
        return;
    }

    status = func_8001CD70(D_801721B6);
    if (status != 0 && status != 2) {
        reset_objects();
        D_80141BDF[0] = 0;
        arg0->unk1 = 0xB;
        arg0->unk2 = 0;
        if (status == 1) {
            D_801721B8 = 0;
            script = D_800F1F00;
        } else {
            D_801721B8 = 4;
            script = D_800F1EE0;
        }
        func_8001B644(script);
    } else if (func_8001CE84(D_801721B6) == 0) {
        reset_objects();
        arg0->unk2 = 0;
        arg0->unk1++;
        empty = 0xFF;
        D_801721BC[0].character = empty;
        D_801721BC[1].character = empty;
        D_801721BC[2].character = empty;
        if (D_801721B9 != 0) {
            func_8001B644(D_800F1EB4);
        } else {
            func_8001B644(D_800F1EC4);
        }
        func_8001B718(0x30, D_801721B6 + 0x11, 0xFF);
        func_8001B644(D_800F1ED0);
        func_8001B7C0(0xD0, 0x88, 0);
        func_8001C008(3, 3);
        D_80173AE0.count = 0;
        D_801721BA = 2;
    } else {
        reset_objects();
        D_801721B8 = 4;
        if (D_801721B9 == 0) {
            arg0->unk1 = 6;
        } else {
            arg0->unk1 = 0xB;
        }
        arg0->unk2 = 0;
        func_8001B644(D_800F1EE0);
    }
}

INCLUDE_ASM("main/nonmatchings/menu", func_80019EF0);

void func_8001A178(struct EngineObj* arg0)
{
    u16* controller;

    if (controller_state & (PADLup | PADLdown)) {
        if (D_80141BDF[0] == 0) {
            D_80141BDF[0] = 1;
        } else {
            D_80141BDF[0] = 0;
        }
        func_8001B7C0(0xD0, 0x88, 0);
    }

    controller = &controller_state;
    if (*controller & PAD_SELECTION_BUTTONS) {
        func_8001540C(0, 0x22, 0);
        if (D_80141BDF[0] != 0 || (*controller & PAD_SELECTION_ALT)) {
            reset_objects();
            D_801721BC = (struct MemcardSaveSlot*)(D_801721B0 + 0x200);
            arg0->unk1 = 4;
            D_80141BDF[0] = 0;
            func_8001B718(0x30, (D_801721B6 + 0x11) & 0xFF, 0xFF);
            func_8001B644(D_800F1E4C);
            func_8001B7C0(0xD0, 0x88, 0);
            func_8001C008(3, 3);
            return;
        }

        arg0->unk1 = (u8)arg0->unk1 + 2;
        reset_objects();
        func_8001B718(0x40, (D_801721B6 + 0xB) & 0xFF, 0xFF);
        func_8001B644(D_800F1E0C);
        D_801721BA = 2;
    }
}

void func_8001A308(struct EngineObj* arg0)
{
    u16* controller;

    if (controller_state & (PADLup | PADLdown)) {
        if (D_80141BDF[0] == 0) {
            D_80141BDF[0] = 1;
        } else {
            D_80141BDF[0] = 0;
        }
        func_8001B7C0(0xD0, 0x88, 0);
    }

    controller = &controller_state;
    if (*controller & PAD_SELECTION_BUTTONS) {
        func_8001540C(0, 0x22, 0);
        if (D_80141BDF[0] != 0 || (*controller & PAD_SELECTION_ALT)) {
            reset_objects();
            D_801721BC = (struct MemcardSaveSlot*)(D_801721B0 + 0x200);
            arg0->unk1 = 4;
            D_80141BDF[0] = 0;
            func_8001B718(0x30, (D_801721B6 + 0x11) & 0xFF, 0xFF);
            func_8001B644(D_800F1E4C);
            func_8001B7C0(0xD0, 0x88, 0);
            func_8001C008(3, 3);
            return;
        }

        arg0->unk1 = (u8)arg0->unk1 + 1;
        reset_objects();
        func_8001B718(0x40, (D_801721B6 + 0xB) & 0xFF, 0xFF);
        func_8001B644(D_800F1E0C);
        D_801721BA = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/menu", func_8001A498);

INCLUDE_ASM("main/nonmatchings/menu", func_8001A710);

void func_8001A7D4(struct EngineObj* arg0)
{
    u8* timer_ptr;
    u8 temp_v1;
    u32 temp_v1_2;

    timer_ptr = &D_801721BA;
    temp_v1 = *timer_ptr - 1;
    *timer_ptr = temp_v1;
    temp_v1_2 = temp_v1 & 0xFF;
    if (temp_v1_2 < 0x79U) {
        if (!(controller_state & PAD_CONFIRM)) {
            if (temp_v1_2 != 0) {
                return;
            }
        } else {
            func_8001540C(0, 0x22, 0);
        }
        arg0->unk1 = (u8)arg0->unk1 + 1;
    }
}

void func_8001A860(struct EngineObj* arg0)
{
    s8 next_state;

    reset_objects();
    arg0->unk1 = 3;
    arg0->unk2 = 0;
    arg0->unk3 = 0;
    D_80141BDF[0] = 0;
    if (arg0->unk4 == 8) {
        arg0->unk8 = func_8001E850(D_800F2338.scripts[0], 1);
        next_state = 8;
    } else {
#ifdef VERSION_JP
        arg0->unk8 = func_8001E850(D_800F2474_jp, 1);
#else
        arg0->unk8 = func_8001E850(D_800F2310, 1);
#endif
        next_state = 9;
    }
    arg0->state = next_state;
}

void func_8001A8E8(struct EngineObj* arg0)
{
    if (controller_state & (PADstart | PADRup | PADRdown | PADRleft | PADRright)) {
        func_8001540C(0, 0x22, 0);
        reset_objects();
        switch (D_801721B8) {
        case 0:
        case 1:
        case 2:
        case 3:
            if (arg0->unk4 == 8) {
                arg0->unk8 = func_8001E850(&D_800F2328, 1);
                arg0->state = 8;
                D_80141BDF[0] = 2;
            } else {
                arg0->unk8 = func_8001E850(&D_800F2300, 1);
                arg0->state = 9;
                D_80141BDF[0] = 0;
            }
            arg0->unk1 = 1;
            break;
        case 4:
            reset_objects();
            D_80141BDF[0] = 0;
            arg0->unk1 = 0;
            arg0->unk2 = 0;
            break;
        }
    }
}

void func_8001A9EC(struct EngineObj* arg0)
{
    u8 previous_selection;

    if (engine_obj.unk1 != 0) {
        previous_selection = D_80141BDF[0];
    } else {
        previous_selection = 0;
    }
    D_800F1FA0[arg0->unk1](arg0);
    if ((D_80141BDF[0] != previous_selection) && !(controller_state & PAD_SELECTION_BUTTONS)) {
        func_8001540C(0, 0xC, 0);
    }
    func_80016124();
    update_misc_objects();
    init_objects();
}

INCLUDE_ASM("main/nonmatchings/menu", func_8001AA98);

INCLUDE_ASM("main/nonmatchings/menu", func_8001ABDC);

void func_8001AE8C(struct EngineObj* arg0)
{
    u8* timer;
    u8* script;
    s32 status;
    u8 remaining;
    u8 empty;

    timer = &D_801721BA;
    remaining = *timer - 1;
    *timer = remaining;
    if (remaining != 0) {
        return;
    }

    status = func_8001CDE4(D_801721B6);
    if (status != 0) {
        if (status == 1) {
            script = D_800F1F00;
            arg0->unk1 = 6;
            D_801721B8 = 0;
        } else {
            script = D_800F1F20;
            arg0->unk1 = 6;
            D_801721B8 = 1;
        }
        func_8001B644(script);
        D_80141BDF[0] = 0;
        return;
    }

    switch ((u32)func_8001CD70(D_801721B6)) {
    case 1:
        reset_objects();
        script = D_800F1F00;
        arg0->unk1 = 6;
        D_801721B8 = 0;
        D_80141BDF[0] = 0;
        func_8001B644(script);
        break;
    case 2:
        reset_objects();
        script = D_800F1F58;
        arg0->unk1 = 6;
        D_801721B8 = 1;
        D_80141BDF[0] = 0;
        func_8001B644(script);
        break;
    case 3:
        reset_objects();
        script = D_800F1F20;
        arg0->unk1 = 6;
        D_801721B8 = 1;
        D_80141BDF[0] = 0;
        func_8001B644(script);
        break;
    case 0:
        arg0->unk1++;
        func_8001CC5C(D_801721B6, &D_80173AE0, D_8001005C);
        if (D_80173AE0.count != 0) {
            if (func_8001CB24(D_801721B0, D_801721B6, 0x2000) != 0) {
                reset_objects();
                D_801721B8 = 2;
                D_80141BDF[0] = 0;
                arg0->unk1 = 6;
                func_8001B644(D_800F1F10);
                return;
            }
        } else {
            empty = 0xFF;
            D_801721BC[0].character = empty;
            D_801721BC[1].character = empty;
            D_801721BC[2].character = empty;
        }
        reset_objects();
        func_8001B718(0x30, (D_801721B6 + 0x11) & 0xFF, 0xFF);
        func_8001B644(D_800F1F30);
        func_8001B7C0(0xD0, 0x88, 0);
        func_8001C008(3, 1);
        break;
    }
    D_80141BDF[0] = 0;
}

void func_8001B10C(struct EngineObj* arg0)
{
    u8 i;
    u8 j;
    u8 selected;
    u8* character;

    if (controller_state & PADLup) {
        u8* cursor = D_80141BDF;
        u8 current = *cursor;

        if (current == 0) {
            struct MemcardSaveSlot** slot;

            i = 0;
            slot = &D_801721BC;
            do {
                (*slot)++;
                i++;
            } while (i < 3);
            D_80141BDF[0] = 3;
        } else {
            struct MemcardSaveSlot** slot = &D_801721BC;

            *cursor = current - 1;
            (*slot)--;
        }
        if (D_80141BDF[0] != 3) {
            func_8001B7C0(0xD0, 0x88, 0);
        }
    }

    if (controller_state & PADLdown) {
        u8* cursor = D_80141BDF;
        u8 current = *cursor;

        if (current == 3) {
            struct MemcardSaveSlot** slot;

            j = 0;
            slot = &D_801721BC;
            do {
                (*slot)--;
                j++;
            } while (j < 3);
            D_80141BDF[0] = 0;
        } else {
            struct MemcardSaveSlot** slot = &D_801721BC;

            *cursor = current + 1;
            (*slot)++;
        }
        if (D_80141BDF[0] != 3) {
            func_8001B7C0(0xD0, 0x88, 0);
        }
    }

    if (controller_state & PAD_SELECTION_BUTTONS) {
        if (D_80141BDF[0] == 3 || (controller_state & PAD_SELECTION_ALT)) {
            func_8001540C(0, 0x22, 0);
            arg0->unk1 = 0;
            D_80141BDF[0] = 0;
            return;
        }
        if (D_801721BC->character == 0xFF) {
            func_8001540C(0, 0x14, 0);
            return;
        }

        func_8001540C(0, 0x22, 0);
        selected = D_80141BDF[0];
        D_80141BDF[0] = 0;
        character = &D_801721B7;
        *character = selected;
        reset_objects();
        arg0->unk1 = (u8)arg0->unk1 + 1;
        func_8001B718(0x30, (*character + D_801721B6 * 3 + 0x1A) & 0xFF, 0xFF);
        func_8001B644(D_800F1F48);
        func_8001B7C0(0xD0, 0x88, 1);
        func_8001C008(0, 1);
    }
}
void func_8001B388(struct EngineObj* arg0)
{
    u16* controller;
    u8* toggle;

    if (controller_state & (PADLup | PADLdown)) {
        if (D_80141BDF[0] == 0) {
            D_80141BDF[0] = 1;
        } else {
            D_80141BDF[0] = 0;
        }
    }

    controller = &controller_state;
    if (*controller & PAD_SELECTION_BUTTONS) {
        toggle = D_80141BDF;
        func_8001540C(0, 0x22, 0);
        if (*toggle != 0 || (*controller & PAD_SELECTION_ALT)) {
            reset_objects();
            arg0->unk1 = (u8)arg0->unk1 - 1;
            *toggle = 0;
            D_801721BC = (struct MemcardSaveSlot*)(D_801721B0 + 0x200);
            func_8001B718(0x30, (D_801721B6 + 0x11) & 0xFF, 0xFF);
            func_8001B644(D_800F1F30);
            func_8001B7C0(0xD0, 0x88, 0);
            func_8001C008(3, 1);
            return;
        }
        arg0->unk1 = (u8)arg0->unk1 + 1;
        func_8001C210();
        reset_objects();
        func_800129F0(8);
    }
}

void func_8001B4E4(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        reset_objects();
        func_8001E980(1);
        engine_obj.state = 1;
        engine_obj.unk1 = 6;
        engine_obj.unk2 = 0;
        engine_obj.unk3 = 0;
        func_80012740(1, &func_8001FB50);
        func_800127FC();
    }
}

void func_8001B558(struct EngineObj* arg0)
{
    s32 temp;
    if (controller_state & (PADstart | PADRup | PADRdown | PADRleft | PADRright)) {
        func_8001540C(0, 0x22, 0);
        reset_objects();
        switch (D_801721B8) {
        case 0 ... 4:
            game_info.unk0 = 7;
            game_info.unk2 = 0;
            game_info.unk3 = 0;
            if (D_800F1D90.save.character != 0xFF) {
                game_info.unk8 = func_8001E850(&D_800F22D0, 0);
                game_info.mode = 1;
                D_80141BDF[0] = 1;
            } else {
                game_info.unk8 = func_8001E850(&D_800F22E0, 0);
                game_info.mode = 3;
                D_80141BDF[0] = 0;
            }
        }
    }
}

void func_8001B644(u8* arg0)
{
    struct MiscObj* obj;
    u8* data;
    u8 engine_state;

    data = arg0;
    while (*data != 0xFF) {
        obj = find_free_misc_obj();
        if (obj != 0) {
            obj->active = 0x41;
            obj->id = 0x2A;
            obj->unk2 = 0;
            obj->x_pos.i.hi = 0xA0;
            obj->y_pos.i.hi = *data++;
            obj->animation_step.fields.frame_index = *data++;
            if (engine_obj.unk1 != 3) {
                obj->ext.misc_42.unk54 = engine_obj.unk1;
                obj->ext.misc_42.unk55 = 1;
            } else {
                engine_state = (u8)engine_obj.unk2;
                obj->ext.misc_42.unk55 = 2;
                obj->ext.misc_42.unk54 = engine_state;
            }
            obj->ext.misc_42.unk56 = *data++;
        }
    }
}

void func_8001B718(s16 arg0, u8 arg1, u8 arg2)
{
    struct MiscObj* obj;
    u8 engine_state;

    obj = find_free_misc_obj();
    if (obj != 0) {
        obj->active = 0x41;
        obj->id = 0x2A;
        obj->unk2 = 0;
        obj->animation_step.fields.frame_index = arg1;
        obj->x_pos.i.hi = 0xA0;
        obj->y_pos.i.hi = arg0;
        if (engine_obj.unk1 != 3) {
            obj->ext.misc_42.unk54 = engine_obj.unk1;
            obj->ext.misc_42.unk55 = 1;
        } else {
            engine_state = (u8)engine_obj.unk2;
            obj->ext.misc_42.unk55 = 2;
            obj->ext.misc_42.unk54 = engine_state;
        }
        obj->ext.misc_42.unk56 = arg2;
    }
}

INCLUDE_ASM("main/nonmatchings/menu", func_8001B7C0);

INCLUDE_ASM("main/nonmatchings/menu", func_8001B8B0);

INCLUDE_RODATA("main/nonmatchings/menu", D_80010090);

INCLUDE_ASM("main/nonmatchings/menu", func_8001BCAC);

INCLUDE_ASM("main/nonmatchings/menu", func_8001BE10);

INCLUDE_ASM("main/nonmatchings/menu", func_8001C008);

void func_8001C07C(void)
{
    struct MemcardSaveSlot* slot = D_801721BC;
    u8 i;

    slot->character = engine_obj.cur_character;
    slot->unk1 = engine_obj.unk46;
    slot->unk2 = engine_obj.unk48;
    slot->unk4 = engine_obj.palette_flags;
    slot->unk5 = engine_obj.unk5F;
    slot->unk6 = engine_obj.unk5A;
    slot->unk3 = engine_obj.unk47;
    slot->unk29 = engine_obj.unk37;
    for (i = 0; i < 16; i++) {
        slot->unk8[i] = D_800EE430[i];
    }
    slot->unk28 = D_80171EA9;
    D_800F1D90.save = *D_801721BC;
}

INCLUDE_ASM("main/nonmatchings/menu", func_8001C210);

INCLUDE_ASM("main/nonmatchings/menu", func_8001C30C);

void func_8001C3E8(void)
{
    u8 i;
    struct MemcardSaveSlot* save;

    save = &D_800F1D90.save;
    save->character = engine_obj.cur_character;
    save->unk1 = engine_obj.unk46;
    save->unk2 = engine_obj.unk48;
    save->unk4 = engine_obj.palette_flags;
    save->unk5 = engine_obj.unk5F;
    save->unk6 = engine_obj.unk5A;
    save->unk3 = engine_obj.unk47;
    save->unk29 = engine_obj.unk37;
    for (i = 0; i < 0x10; i++) {
        save->unk8[i] = D_800EE430[i];
    }
    save->unk28 = D_80171EA9;
}

INCLUDE_ASM("main/nonmatchings/menu", func_8001C4B4);

void func_8001C5A8(u8** arg0)
{
    __builtin_memcpy(*arg0 + 0x60, D_800F1FC0, 0x20);
    __builtin_memcpy(*arg0 + 0x80, D_800F1FE0.texture, 0x180);
}

struct MenuRuntimeData D_800F1D90 = {
    { 0xFF },
    { 0 },
    {
        1,
        0,
        2,
        0x20,
        5,
        0,
        0x40,
        6,
        5,
        8,
        3,
        4,
        0x10,
        4,
        3,
        4,
        2,
        1,
        0x80,
        7,
        7,
        2,
        1,
        6,
    },
    {
        0x0001,
        0x0002,
        0x0004,
        0x0008,
        0x0010,
        0x0020,
        0x0040,
        0x0080,
    },
    { 0x1000, 0x2000, 0x4000 },
    0x8000,
};

#ifdef VERSION_JP
u8 D_800F1DEC[] = { 0x10, 0x32, 0xFF, 0x30, 0x09, 0xFF, 0x40, 0x0A, 0xFF, 0xB0, 0x33, 0x02, 0xD0, 0x05, 0xFF, 0xFF };
#else
u8 D_800F1DEC[] = { 0x10, 0x32, 0xFF, 0x30, 0x09, 0xFF, 0x40, 0x0A, 0xFF, 0xB0, 0x0D, 0x02, 0xD0, 0x05, 0xFF, 0xFF };
#endif

u8 D_800F1DFC[] = { 0x10, 0x3E, 0xFF, 0x40, 0x40, 0xFF, 0x60, 0x41, 0xFF, 0x70, 0x42, 0xFF, 0xD0, 0x3F, 0xFF, 0xFF };

u8 D_800F1E0C[] = { 0x10, 0x3C, 0xFF, 0x70, 0x3D, 0xFF, 0xFF, 0 };

#ifdef VERSION_JP
u8 D_800F1E14[] = { 0x10, 0x3E, 0xFF, 0x40, 0x4B, 0xFF, 0x60, 0x4D, 0xFF, 0xD0, 0x3F, 0xFF, 0xFF, 0, 0, 0 };
#else
u8 D_800F1E14[] = { 0x10, 0x3E, 0xFF, 0x40, 0x4D, 0xFF, 0x50, 0x4B, 0xFF, 0xD0, 0x3F, 0xFF, 0xFF, 0, 0, 0 };
#endif

u8 D_800F1E24[] = { 0x10, 0x3E, 0xFF, 0x40, 0x48, 0xFF, 0x60, 0x49, 0xFF, 0xD0, 0x3F, 0xFF, 0xFF, 0, 0, 0 };

u8 D_800F1E34[] = { 0x10, 0x3E, 0xFF, 0x40, 0x43, 0xFF, 0x50, 0x44, 0xFF, 0x70, 0x45, 0xFF, 0x80, 0x46, 0xFF, 0x90, 0x47, 0xFF, 0xD0, 0x3F, 0xFF, 0xFF, 0, 0 };

#ifdef VERSION_JP
u8 D_800F1E4C[] = { 0x10, 0x32, 0xFF, 0x40, 0x34, 0xFF, 0x70, 0x14, 0, 0x80, 0x15, 1, 0x90, 0x16, 2, 0xB0, 0x35, 3, 0xD0, 5, 0xFF, 0xFF, 0, 0 };
#else
u8 D_800F1E4C[] = { 0x10, 0x32, 0xFF, 0x40, 0x34, 0xFF, 0x50, 0x74, 0xFF, 0x70, 0x14, 0, 0x80, 0x15, 1, 0x90, 0x16, 2, 0xB0, 0x17, 3, 0xD0, 5, 0xFF, 0xFF, 0, 0, 0 };
#endif

u8 D_800F1E68[] = { 0x10, 0x32, 0xFF, 0x70, 0x21, 0, 0x90, 0x22, 1, 0xD0, 5, 0xFF, 0xFF, 0, 0, 0 };

u8 D_800F1E78[] = { 0x10, 0x32, 0xFF, 0xA0, 0x38, 0xFF, 0xFF, 0, 0x10, 0x32, 0xFF, 0xA0, 0x38, 0xFF, 0xFF, 0 };

u8 D_800F1E88[] = { 0x10, 0x32, 0xFF, 0xA0, 0x39, 0xFF, 0xFF, 0 };

#ifdef VERSION_JP
u8 D_800F1E90[] = { 0x10, 0x3E, 0xFF, 0x30, 0x4E, 0xFF, 0x40, 0x4F, 0xFF, 0x60, 0x50, 0xFF, 0x90, 0x51, 0, 0xB0, 0x52, 1, 0xD0, 5, 0xFF, 0xFF, 0, 0 };
#else
u8 D_800F1E90[] = { 0x10, 0x3E, 0xFF, 0x30, 0x4E, 0xFF, 0x40, 0x4F, 0xFF, 0x50, 0x76, 0xFF, 0x70, 0x50, 0xFF, 0x80, 0x77, 0xFF, 0xA0, 0x51, 0, 0xB0, 0x52, 1, 0xD0, 5, 0xFF, 0xFF };
#endif

u8 D_800F1EAC[] = { 0x10, 0x3A, 0xFF, 0x70, 0x3B, 0xFF, 0xFF, 0 };

#ifdef VERSION_JP
u8 D_800F1EB4[] = { 0x10, 0x32, 0xFF, 0x40, 0x34, 0xFF, 0xB0, 0x35, 3, 0xFF, 0, 0 };
#else
u8 D_800F1EB4[] = { 0x10, 0x32, 0xFF, 0x40, 0x34, 0xFF, 0x50, 0x74, 0xFF, 0xB0, 0x17, 3, 0xFF, 0, 0, 0 };
#endif

u8 D_800F1EC4[] = { 0x10, 8, 0xFF, 0x40, 0x13, 0xFF, 0xB0, 0x17, 3, 0xFF, 0, 0 };

u8 D_800F1ED0[] = { 0x70, 0x14, 0, 0x80, 0x15, 1, 0x90, 0x16, 2, 0xD0, 5, 0xFF, 0xFF, 0, 0, 0 };

#ifdef VERSION_JP
u8 D_800F1EE0[] = { 0x10, 0x3E, 0xFF, 0x40, 0x4C, 0xFF, 0x60, 0x4D, 0xFF, 0xD0, 0x3F, 0xFF, 0xFF, 0, 0, 0 };
#else
u8 D_800F1EE0[] = { 0x10, 0x3E, 0xFF, 0x40, 0x4C, 0xFF, 0x50, 0x75, 0xFF, 0xD0, 0x3F, 0xFF, 0xFF, 0, 0, 0 };
#endif

u8 D_800F1EF0[] = { 0x10, 8, 0xFF, 0x30, 9, 0xFF, 0x40, 0x0A, 0xFF, 0xB0, 0x0D, 2, 0xD0, 5, 0xFF, 0xFF };

#ifdef VERSION_JP
u8 D_800F1F00[] = { 0x10, 0x3E, 0xFF, 0x40, 0x40, 0xFF, 0x70, 0x42, 0xFF, 0xD0, 0x3F, 0xFF, 0xFF, 0, 0, 0 };
u8 D_800F1F10[] = { 0x10, 0x3E, 0xFF, 0x40, 0x4A, 0xFF, 0x70, 0x4D, 0xFF, 0xD0, 0x3F, 0xFF, 0xFF, 0, 0, 0 };
#else
u8 D_800F1F00[] = { 0x10, 0x3E, 0xFF, 0x40, 0x40, 0xFF, 0x60, 0x41, 0xFF, 0x70, 0x42, 0xFF, 0xD0, 0x3F, 0xFF, 0xFF };
u8 D_800F1F10[] = { 0x10, 0x3E, 0xFF, 0x40, 0x4D, 0xFF, 0x50, 0x4A, 0xFF, 0xD0, 0x3F, 0xFF, 0xFF, 0, 0, 0 };
#endif

u8 D_800F1F20[] = { 0x10, 0x3E, 0xFF, 0x40, 0x48, 0xFF, 0x60, 0x49, 0xFF, 0xD0, 0x3F, 0xFF, 0xFF, 0, 0, 0 };

u8 D_800F1F30[] = { 0x10, 8, 0xFF, 0x40, 0x13, 0xFF, 0x70, 0x14, 0, 0x80, 0x15, 1, 0x90, 0x16, 2, 0xB0, 0x17, 3, 0xD0, 5, 0xFF, 0xFF, 0, 0 };

u8 D_800F1F48[] = { 0x10, 8, 0xFF, 0x40, 0x20, 0xFF, 0x70, 0x21, 0, 0x90, 0x22, 1, 0xD0, 5, 0xFF, 0xFF };

#ifdef VERSION_JP
u8 D_800F1F58[] = { 0x10, 0x3E, 0xFF, 0x40, 0x4E, 0xFF, 0x60, 0x4F, 0xFF, 0xD0, 0x3F, 0xFF, 0xFF, 0, 0, 0 };
#else
u8 D_800F1F58[] = { 0x10, 0x3E, 0xFF, 0x60, 0x7A, 0xFF, 0xD0, 0x3F, 0xFF, 0xFF, 0, 0 };
#endif

void (*D_800F1F64[12])(struct EngineObj*) = {
    func_800194C8,
    func_8001961C,
    func_8001989C,
    func_80019B64,
    func_80019EF0,
    func_8001A178,
    func_8001A308,
    func_8001A498,
    func_8001A710,
    func_8001A7D4,
    func_8001A860,
    func_8001A8E8,
};

void (*D_800F1F94[3])(struct EngineObj*) = {
    func_80019BA0,
    func_80019BF4,
    func_80019D04,
};

void (*D_800F1FA0[])(struct EngineObj*) = {
    func_8001AA98,
    func_8001ABDC,
    func_8001AE8C,
    func_8001B10C,
    func_8001B388,
    func_8001B4E4,
    func_8001B558,
};

u8 D_800F1FBC[4] = { 1, 2, 4, 8 };

u8 D_800F1FC0[32] = {
    0,
    0,
    0x44,
    0xFF,
    0,
    0xFE,
    0x24,
    0xD9,
    0xBD,
    0xB5,
    0x5E,
    0x80,
    0x12,
    0x80,
    0x0C,
    0x80,
    0xDE,
    0xFB,
    0xD5,
    0xE6,
    0xAC,
    0xC1,
    0xA4,
    0xA4,
    0x1E,
    0xCB,
    0x19,
    0xB2,
    0x73,
    0xA1,
    0x7A,
    0xF7,
};

struct MenuTextureData D_800F1FE0 = {
    {
        0x00000700,
        0x00000600,
        0x00007600,
        0x00006500,
        0x00076600,
        0x00066450,
        0xFFF96600,
        0x00065859,
        0x88888660,
        0x70665845,
        0x98888F60,
        0x77665445,
        0x58888866,
        0x77665464,
        0x548188F6,
        0x77665566,
        0x65481816,
        0x777665E9,
        0x87549156,
        0x07A895E8,
        0x8A754560,
        0x07AB85E8,
        0x8BDE77A0,
        0x00AB9569,
        0xCCCCDEA0,
        0x00AA9555,
        0xCECDE700,
        0x00007656,
        0xCCEE7000,
        0x0000076D,
        0xDDE00000,
        0x0000000E,
        0x00000700,
        0x00000600,
        0x00007600,
        0x00006500,
        0x00076600,
        0x00066450,
        0xFFF96600,
        0x00065859,
        0x88888660,
        0x70665845,
        0x98888F60,
        0x77665445,
        0x58888866,
        0x77665464,
        0x558218F6,
        0x77665566,
        0x65582127,
        0x777665EC,
        0xC7559277,
        0x07A895ED,
        0x8E765670,
        0x07AB85E8,
        0x8BDE77A0,
        0x00AB9569,
        0xCCCCDEA0,
        0x00AA9555,
        0xCECDE700,
        0x00007656,
        0xCCEE7000,
        0x0000076D,
        0xDDE00000,
        0x0000000E,
        0x00000700,
        0x00000600,
        0x00007600,
        0x00006500,
        0x00076600,
        0x00066450,
        0xFFF96600,
        0x00065859,
        0x88888660,
        0x70665845,
        0x98888F60,
        0x77665445,
        0x58888866,
        0x77665464,
        0x558321F6,
        0x77665566,
        0x65583237,
        0x777665EC,
        0xC7559377,
        0x07A895EC,
        0xCD765670,
        0x07AB85ED,
        0xDEDE77A0,
        0x00AB956E,
        0xCCCCDEA0,
        0x00AA9555,
        0xCECDE700,
        0x00007656,
        0xCCEE7000,
        0x0000076D,
        0xDDE00000,
        0x0000000E,
    },
    { 0, 488, 64, 24, 64, 488, 64, 1 },
};
