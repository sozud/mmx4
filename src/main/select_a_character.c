#include "common.h"

enum SubTypes {
    X_PORTRAIT,
    ZERO_PORTRAIT,
    PLAYER_SELECT_UPPER,
    PLAYER_SELECT_LOWER,
    SELECTOR = 6,
    X_CHARACTER,
    ZERO_CHARACTER,
};

// SelectACharacterUpdate state 0
void func_800CCA34(struct MiscObj* arg0)
{
    s8 temp_v0;
    s8 temp_v1_2;
    u8 temp_a1;

    temp_v0 = arg0->base.unk2 - 7;
    switch (temp_v0) {
    case 0:
    case 2:
    case 3:
        arg0->unk40 = D_801406A8[2] >> 7;
        arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[2];
        arg0->unk42 = 0x7840;
        arg0->animation_table = (const u32* const*)D_8010EAC8;
        arg0->base.unk15 = 0x40;
        break;
    case 1:
    case 4:
        arg0->unk40 = D_801406A8[0] >> 7;
        arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[0];
        arg0->unk42 = 0x7800;
        arg0->animation_table = (const u32* const*)D_8010EAE4;
        arg0->base.unk15 = 0;
        break;
    default:
        arg0->unk40 = D_801406A8[1] >> 7;
        arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[1];
        temp_a1 = D_8010EB34[arg0->base.unk2];
        arg0->unk42 = (((temp_a1 * 4) + 4) % 16) | ((((temp_a1 + 1) / 4) + 0x1E0) << 6);
        arg0->animation_table = (const u32* const*)D_8010EAFC;
        break;
    }
    temp_v1_2 = 2;
    if (arg0->base.unk2 < 9) {
        arg0->base.x_pos.val = FIXED(D_8010EB54[arg0->base.unk2].x);
        arg0->base.y_pos.val = FIXED(D_8010EB54[arg0->base.unk2].y);
    }
    if (arg0->base.unk2 >= 0xC) {
        s32 temp = arg0->base.unk2 - 0xC;
        arg0->base.x_pos.val = FIXED(D_8010EB78[temp].x);
        arg0->base.y_pos.val = FIXED(D_8010EB78[(arg0->base.unk2 - 0xC)].y);
    }
    arg0->base.unk16 = D_8010EB44[arg0->base.unk2];
    func_80015D60(arg0, D_8010EB24[arg0->base.unk2]);
    arg0->base.bg_offset = -1;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->ext.title_logo.palette_shift_speed = 0;
    arg0->ext.title_logo.unk57 = 0;
    arg0->base.unk6 = 0;
    arg0->base.unk7 = 0;
    arg0->base.state++;
    arg0->base.unk5 = arg0->base.unk2;
}

// D_8010EB84 state 0
void func_800CCCA0(struct MiscObj* arg0)
{
    // set speeds of portraits when "select a character"
    // screen first starts and portraits come in
    if (arg0->base.unk2 == X_PORTRAIT) {
        arg0->x_vel.val = FIXED(16); // speed of X portrait
    } else {
        arg0->x_vel.val = FIXED(-16); // speed of Zero portrait
    }
    if (((arg0->base.unk2 == X_PORTRAIT) && (arg0->base.x_pos.i.hi == 96)) || ((arg0->base.unk2 == ZERO_PORTRAIT) && (arg0->base.x_pos.i.hi == 224))) {
        engine_obj.character_state.bytes[2] |= 1 << arg0->base.unk2;
        arg0->base.unk6++;
        return;
    }
    func_8002B718(arg0);
}

// D_8010EB84 state 1
void func_800CCD48(struct MiscObj* arg0)
{
    if (engine_obj.character_state.bytes[1] & 0x80) {
        arg0->base.unk6++;
        // sets how fast the X and Zero portraits move
        // to the left and right after selecting a character
        if (arg0->base.unk2 != X_PORTRAIT) {
            arg0->x_vel.val = FIXED(16);
        } else {
            arg0->x_vel.val = FIXED(-16);
        }
    }
}

// D_8010EB84 state 2
void func_800CCD8C(struct MiscObj* arg0)
{
    func_8002B718(arg0);
    if (arg0->base.on_screen == 0) {
        arg0->base.state++;
    }
}

// D_8010EB84 state 3
void func_800CCDD4(struct MiscObj* arg0)
{
    switch (arg0->base.unk7) {
    case 0:
        arg0->x_vel.val = FIXED(16);
        /* fallthrough */
    case 1:
        func_8002B718(arg0);
        if (arg0->base.on_screen == 0) {
            arg0->ext.sel_char.blast_timer = 20;
            arg0->base.unk7++;
            return;
        }
        return;
    case 2:
        if (--arg0->ext.sel_char.blast_timer == 0) {
            arg0->x_vel.val = FIXED(-16);
            arg0->base.unk7++;
            return;
        }
        break;
    case 3:
        func_8002B718(arg0);
        if (arg0->base.x_pos.i.hi == 0xE0) {
            arg0->base.unk6 = 1;
            arg0->base.unk7 = 0;
        }
        break;
    }
}

// D_8010EBB4 state 0, 1
void func_800CCEB4(struct MiscObj* arg0)
{
    D_8010EB84[arg0->base.unk6]();
}

// D_8010EB98 state 0
void func_800CCEF0(struct MiscObj* arg0)
{
    switch (arg0->base.unk2) {
    case PLAYER_SELECT_UPPER:
        // set velocity of upper "PLAYER SELECT" text
        arg0->x_vel.val = FIXED(-2) | FIXED(.5);
        break;
    case PLAYER_SELECT_LOWER:
        // lower player select text
        arg0->x_vel.val = FIXED(1) | FIXED(.5);
        break;
    case 12:
    case 14:
        arg0->x_vel.val = FIXED(4);
        break;
    case 13:
        arg0->x_vel.val = FIXED(-4);
        break;
    default:
        arg0->x_vel.val = FIXED(0);
        break;
    }
    arg0->base.unk6++;
}

const u32 padding = 0;

// D_8010EB98 state 1
void func_800CCF70(struct MiscObj* arg0)
{
    func_8002B718(arg0);
    switch (arg0->base.unk2) {
    case PLAYER_SELECT_UPPER:
        // when top "PLAYER SELECT" goes off to the left,
        // wrap it around
        if (arg0->base.x_pos.i.hi < -112) {
            arg0->base.x_pos.i.hi = 432;
        }
        break;
    case PLAYER_SELECT_LOWER:
        // when bottom "PLAYER SELECT" goes off to the right,
        // wrap it around
        if (arg0->base.x_pos.i.hi >= 433) {
            arg0->base.x_pos.i.hi = -112;
            return;
        }
        break;
    case 12:
        if (arg0->base.x_pos.i.hi == 126) {
            arg0->x_vel.val = 0;
        }
        break;
    case 13:
        if (arg0->base.x_pos.i.hi == 160) {
            arg0->x_vel.val = 0;
        }
        break;
    case 14:
        if (arg0->base.x_pos.i.hi == 278) {
            arg0->x_vel.val = 0;
        }
        break;
    }
}

// scrolling text doesn't appear if nopped out
// asm(".rept 26 ; nop ; .endr");
// D_8010EBB4 state 2,3,4,5,12,13,14
void func_800CD034(struct MiscObj* arg0)
{
    D_8010EB98[arg0->base.unk6]();
    if (engine_obj.character_state.bytes[1] & 0x80) {
        arg0->base.state++;
    }
}

// D_8010EBA0 state 0
void func_800CD0A4(struct MiscObj* arg0)
{
    s16 x_pos;

    if (engine_obj.cur_character != CHARACTER_X) {
        func_80015D60(arg0, 9);
        x_pos = 224; // zero is selected, move selector graphic to right
    } else {
        func_80015D60(arg0, 8);
        x_pos = 96; // X is selected, move selector graphic to left
    }
    arg0->base.x_pos.i.hi = x_pos;
    arg0->base.y_pos.i.hi = 120; // set y pos of green selector
    do {
    } while (0);
    arg0->base.unk6++;
}

// D_8010EBA0 state 1
void func_800CD110(struct MiscObj* arg0)
{
    func_80015DC8();
    if (engine_obj.cur_character != arg0->ext.sel_char.cur_character_selected) {
        arg0->base.unk6 = 0;
        func_8001540C(5, 0, NULL);
    }
    arg0->ext.sel_char.cur_character_selected = engine_obj.cur_character;
}

// D_8010EBB4 state 6
// green selector graphic around X doesn't animate if nopped out
// asm(".rept 26 ; nop ; .endr");
void func_800CD178(struct MiscObj* arg0)
{
    D_8010EBA0[arg0->base.unk6]();
    if (engine_obj.character_state.bytes[1] & 0x80) {
        arg0->base.state++;
    }
}

// D_8010EBA8 state 0
void func_800CD1E8(struct MiscObj* arg0)
{
    struct MiscObj* obj;

    if (engine_obj.character_state.bytes[0] != 0) {
        arg0->base.unk5 = 0xF;
        arg0->base.unk6 = 0;
        return;
    }
    if (engine_obj.cur_character == (arg0->base.unk2 - 7)) {
        if (arg0->ext.sel_char.blast_timer == 0) {
            arg0->base.unk6++;
            func_80015D60(arg0, 1);
            if (arg0->base.unk2 == X_CHARACTER) {
                obj = find_free_misc_obj();
                // create "blast" right before charged shot comes out
                // still id 0x1C but different unk2
                if (obj != NULL) {
                    obj->base.active = 0x41;
                    obj->base.id = 0x1C;
                    obj->base.unk2 = 0xA;
                    obj->base.x_pos.i.hi = arg0->base.x_pos.i.hi;
                    obj->base.y_pos.i.hi = arg0->base.y_pos.i.hi;
                }
            }
        } else {
            arg0->ext.sel_char.blast_timer--;
        }
    }
}

// D_8010EBA8 state 1
void func_800CD2BC(struct MiscObj* arg0)
{
    struct BaseObj* obj;

    func_80015DC8();
    if (arg0->unk45 != 0) {
        arg0->unk45 = 0;
        obj = (struct BaseObj*)find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 0x41;
            obj->id = 0x1C;
            obj->unk2 = 0xB;
            obj->x_pos.i.hi = arg0->base.x_pos.i.hi;
            obj->y_pos.i.hi = arg0->base.y_pos.i.hi;
        }
    }

    if (arg0->unk46 == 0) {
        arg0->base.unk6 = 0;
        arg0->ext.sel_char.blast_timer = (arg0->ext.sel_char.unk54 & 1) ? 0x96 : 0x5A;
        arg0->ext.sel_char.unk54++;
        if (engine_obj.character_state.bytes[0] != 0) {
            arg0->base.unk5 = 0xF;
        }
        func_80015D60(arg0, 0);
    }
}

// D_8010EBB4 state 7,8
void func_800CD390(struct MiscObj* arg0)
{
    D_8010EBA8[arg0->base.unk6]();
    if ((engine_obj.cur_character != (arg0->base.unk2 - 7)) && (arg0->unk46 == 0)) {
        arg0->base.unk6 = 0;
        arg0->ext.sel_char.blast_timer = 0;
    }
}

// D_8010EBB4 state 9
void func_800CD408(struct MiscObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        arg0->base.unk6++;
        // set speed and position of X's charged shot
        arg0->x_vel.val = FIXED(10);
        arg0->base.x_pos.i.hi += 3;
        arg0->base.y_pos.i.hi -= 7;
    }
    func_80015DC8(arg0);
    func_8002B718(arg0);
    if (arg0->base.x_pos.i.hi >= 161) {
        arg0->base.state++;
    }
}

// D_8010EBB4 state 10, 11
void func_800CD498(struct MiscObj* arg0)
{
    struct MiscObj* temp_v0;

    func_80015DC8();
    if (arg0->unk45 != 0) {
        arg0->unk45 = 0;
        temp_v0 = find_free_misc_obj();
        // create X charged shot object
        if (temp_v0 != NULL) {
            temp_v0->base.active = 0x41;
            temp_v0->base.id = 0x1C;
            temp_v0->base.unk2 = 9;
            temp_v0->base.x_pos.i.hi = arg0->base.x_pos.i.hi;
            temp_v0->base.y_pos.i.hi = arg0->base.y_pos.i.hi;
        }
    }
    if (arg0->unk46 == 0) {
        arg0->base.state++;
    }
}

// D_8010EBB4 state 15
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

// SelectACharacterUpdate state 1
void func_800CD6D8(struct MiscObj* arg0)
{
    D_8010EBB4[arg0->base.unk5](arg0);
    func_8002B318(arg0, 0x80, 0x30);
}

// SelectACharacterUpdate state 2
void func_800CD730(struct MiscObj* arg0)
{
    ZeroObjectState(arg0);
}

// select a character menu never appears if nopped out
void SelectACharacterUpdate(struct MiscObj* arg0)
{
    g_SelectACharacterUpdateFuncs[arg0->base.state]();
}
