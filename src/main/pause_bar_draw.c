// 80017340..80018000
#include "common.h"
#include "main/3D88.h"
#include "main/55C4.h"
#include "main/xa_sequence_data.h"
#include "main/323C.h"
#include "main/3A6C.h"
#include "main/main_palette_data.h"
#include "main/movie_hud_data.h"

#ifdef __MWERKS__
void func_800179BC(void);
#endif

#ifndef MMX4_SATURN

#ifdef MMX4_PC
#endif

#ifdef MMX4_WIN32
#endif
void func_80017E84(void);
void func_80017F2C(void);
#include "scratchpad.h"

struct HudLayoutData {
    s16 x;
    s16 y;
    u8 tile;
    u8 character;
    u8 clut;
    u8 alternate_clut;
};

struct MovieHudQuad {
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;
    s16 x3;
    s16 y3;
    s16 index;
};

struct MoviePlaybackData {
    u32 file_id;
    u16 arg2;
    u16 arg8;
    u16 arg9;
    u16 skip_button;
};

extern struct HudLayoutData D_800F1AD8[38];
extern /* The final record continues into g_BootTransitionDataRegion. */ s16 D_800F1C08[2];
extern struct MovieHudQuad D_800F1C18[13];
extern struct MoviePlaybackData D_800F1D04[11];

#ifdef VERSION_DEMO
struct DemoHudLayoutData {
    s16 x;
    s16 y;
    u8 tile;
    u8 character;
};

extern struct DemoHudLayoutData D_800C62BC_demo[27];

struct DemoMovieHudQuad {
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;
    s16 x3;
    s16 y3;
};

extern struct DemoMovieHudQuad D_800C63FC_demo[13];
#endif

#ifdef MMX4_PC
#include <psyz/audio.h>
#include <psyz/spu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#ifndef MMX4_PC
#endif

typedef struct {
    void (*unk0)(void);
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
} D_80010014_t;

#ifdef VERSION_JP
#define JP_VALUE(us, jp) jp
#else
#define JP_VALUE(us, jp) us
#endif
#undef JP_VALUE

extern void (*D_800F1640[3])(void);

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#ifndef MMX4_SATURN
#endif

#ifndef MMX4_PC
#endif

#ifndef MMX4_PC
#endif

#ifdef VERSION_JP
#define JP_VALUE(us, jp) jp
#else
#define JP_VALUE(us, jp) us
#endif

#ifdef VERSION_JP
#define CD_AUDIO_FIRST_TRACK 0x4C
#define CD_AUDIO_LAST_TRACK 0x4E
#elif defined(VERSION_EU)
#define CD_AUDIO_FIRST_TRACK 0x4B
#define CD_AUDIO_LAST_TRACK 0x4D
#else
#define CD_AUDIO_FIRST_TRACK 0x4A
#define CD_AUDIO_LAST_TRACK 0x4C
#endif

#define XA(sequence_, volume_) \
    {                          \
        sequence_, volume_     \
    }

extern void (*D_800F1AB0[])(void);

extern struct HudLayoutData D_800F1AD8[38];

extern struct MovieHudQuad D_800F1C18[13];

extern struct MoviePlaybackData D_800F1D04[11];
#endif

#ifndef MMX4_SATURN
#ifdef VERSION_DEMO
void func_8002E764_demo(u8 index);
void func_8002EA00_demo(void);
#endif
void func_80017340(void)
{
    u8 start;
    s8 end;
    u8 var_v0;

    SP_PRIM_CURSOR = temp1[SP_DRAW_BUFFER].data;
    SP_DRAW_MODE_CURSOR = temp2[SP_DRAW_BUFFER].data;
    SP_AUX_CURSOR = &temp1[SP_DRAW_BUFFER];

    func_80017E84();
#ifdef VERSION_DEMO
    for (start = 0; start < 0x1B; start++) {
        func_8002E764_demo(start);
    }
    func_8002EA00_demo();
    func_80017F2C();
#else

    end = engine_obj.cur_character == CHARACTER_X ? 10 : 8;

    if (engine_obj.cur_character == CHARACTER_X) {
        func_800175AC(0x14);
        func_800175AC(0);
        func_800175AC(1);
        if (bar_object.options.items[1] != 0) {
            func_800175AC(0x15);
            func_800175AC(2);
            func_800175AC(3);
        }
    }

    start = engine_obj.cur_character != CHARACTER_X ? 0 : 2;

    while (start < end) {
        if (bar_object.options.items[start] != 0) {
            func_800175AC(start + 0x14);
            func_800175AC(start * 2);
            func_800175AC(start * 2 + 1);
        }
        start++;
    }

    if (bar_object.options.fields.unk20 != 0) {
        func_800175AC(0x23);
    }
    if (bar_object.options.fields.unk21 != 0) {
        func_800175AC(0x24);
    }
    if (bar_object.options.fields.unk22 != 0) {
        func_800175AC(0x25);
    }
    func_800175AC(0x1F);
    if (bar_object.options.fields.unk25 != 0) {
        func_800175AC(0x26);
    }
    func_800175AC(0x1E);
    func_800175AC(0x20);
    if (engine_obj.stage >= 1 && engine_obj.stage <= 8) {
        if (engine_obj.cur_character == CHARACTER_X) {
            if (bar_object.options.items[engine_obj.stage + 1] != 0) {
                func_800175AC(0x21);
            }
        } else if (bar_object.options.items[D_800F1C10[engine_obj.stage - 1]] != 0) {
            func_800175AC(0x21);
        }
    }
    func_800175AC(0x22);
    func_800179BC();
    func_80017F2C();
#endif
}

#if !defined(MMX4_PC)
static inline u16 pause_menu_clut(u8 value)
{
    return (value & 0xF) | (((value >> 4) + 0x1E0) << 6);
}

#ifdef VERSION_DEMO
void func_8002E764_demo(u8 index)
{
    struct DemoHudLayoutData* layout = &D_800C62BC_demo[index];
    s16 x;
    s16 y;
    u8* archive;
    u16* frame;
    u8* pieces;
    u32 count;
    u16 clut;
    SPRT_16* slot;
    SPRT_16* sprite;
    DR_TPAGE* page;
    u32 texture;
    u16 uv;
    u16 base;
    u8 code;
    u8 flags;
    s16 sx;
    s16 sy;
    u8 u;
    u8 v;

    if (layout->character != 0xFF && bar_object.options.items[layout->character] == 0)
        return;
    x = layout->x;
    y = layout->y;
    archive = SP_TITLE_FRAMES;
    if (layout->tile == 0xD)
        frame = (u16*)(archive + (layout->tile + engine_obj.player_lives) * 4);
    else
        frame = (u16*)(archive + layout->tile * 4);
    count = frame[0];
    pieces = archive + frame[1] * 4;
    base = 0x1D60;
    slot = SP_PRIM_CURSOR;
    page = SP_DRAW_MODE_CURSOR;
    for (; count != 0; count--) {
        flags = pieces[0];
        code = 0x7D;
        sx = (s8)pieces[2];
        sx += x;
        sy = y + (s8)pieces[3];
        texture = base + (pieces[1] | ((flags & 3) << 8));
        if (index == 2)
            clut = 0x7840;
        else
            clut = 0x7900 | ((flags & 0xC) >> 2);
        uv = texture;
        v = uv & 0xF0;
        u = uv << 4;
        sprite = slot;
        setlen(sprite, 3);
        sprite->code = code;
        sprite->clut = clut;
        sprite->x0 = sx;
        sprite->y0 = sy;
        sprite->u0 = u;
        sprite->v0 = v;
        BG_DRAW_TPAGE(page, (texture >> 8) | 0x20);
        setaddr(page, sprite);
        setaddr(sprite, page + 1);
        page++;
        slot = (SPRT_16*)((POLY_FT4*)slot + 1);
        pieces += 4;
    }
    SP_PRIM_CURSOR = slot;
    {
        u32 buffer = SP_DRAW_BUFFER;
        u8 ordering = 5;
        setaddr(D_8013BC40[buffer][ordering >> 4][ordering & 0xF], SP_DRAW_MODE_CURSOR);
        D_8013BC40[buffer][ordering >> 4][ordering & 0xF] = (P_TAG*)((POLY_FT4*)slot - 1);
    }
    SP_DRAW_MODE_CURSOR = page;
}
#else
void func_800175AC(u8 index)
{
    struct HudLayoutData* layout = &D_800F1AD8[index];
    s16 x = layout->x;
    s16 y = layout->y;
    u8* archive;
    u16* frame;
    u8* pieces;
    u32 count;
    u16 clut;
    SPRT_16* slot;
    SPRT_16* sprite;
    DR_TPAGE* page;
    u16 texture;
    u16 base;
    u8 code;
    u8 flags;
    s16 sx;
    s16 sy;
    u8 u;
    u8 v;

    if (index == 0x20) {
        y = 0xD8;
        x = ((s8)engine_obj.max_hp << 1) + 0x80;
    }
    archive = SP_TITLE_FRAMES;
    if (index != 0x1F)
        frame = (u16*)(archive + layout->tile * 4);
    else
        frame = (u16*)(archive + (layout->tile + engine_obj.player_lives) * 4);
    if (index == 0x26 && bar_object.options.fields.unk25 != 0)
        frame = (u16*)(archive + (layout->tile * 4 + 0x28));
    count = frame[0];
    pieces = archive + frame[1] * 4;
    base = 0x1D60;
    if (bar_object.unk14 == layout->character) {
        if (main_bss_state.frame_counter & 0x10)
            clut = pause_menu_clut(layout->alternate_clut);
        else
            clut = pause_menu_clut(layout->clut);
    } else if (engine_obj.cur_character == CHARACTER_X) {
        clut = pause_menu_clut(layout->clut);
        if (g_Player.weapon + 1 == layout->character)
            clut = pause_menu_clut(layout->alternate_clut);
        else if (g_Player.weapon == 0 && layout->character == 0)
            clut = pause_menu_clut(layout->alternate_clut);
    } else {
        if (index < 0x21)
            clut = pause_menu_clut(layout->alternate_clut);
        else
            clut = pause_menu_clut(layout->clut);
    }
    if (engine_obj.cur_character == CHARACTER_X && layout->character == 1) {
        if (g_Player.weapon_energy[0] >= 0x30)
            clut = pause_menu_clut(layout->alternate_clut);
        else
            clut = pause_menu_clut(layout->clut);
    }
    code = 0x7D;
    slot = SP_PRIM_CURSOR;
    page = SP_DRAW_MODE_CURSOR;
    for (; count != 0; count--) {
        flags = pieces[0];
        sx = (s8)pieces[2] + x;
        sy = y + (s8)pieces[3];
        texture = base + (pieces[1] | ((flags & 3) << 8));
        sprite = slot;
        setlen(sprite, 3);
        sprite->code = code;
        sprite->clut = clut + ((flags & 0xC) >> 2);
        sprite->x0 = sx;
        sprite->y0 = sy;
        v = texture & 0xF0;
        sprite->u0 = texture << 4;
        sprite->v0 = v;
        BG_DRAW_TPAGE(page, (texture >> 8) | 0x20);
        setaddr(page, sprite);
        setaddr(sprite, page + 1);
        page++;
        slot = (SPRT_16*)((POLY_FT4*)slot + 1);
        pieces += 4;
    }
    SP_PRIM_CURSOR = slot;
    {
        u32 buffer = SP_DRAW_BUFFER;
        u8 ordering = 5;
        setaddr(D_8013BC40[buffer][ordering >> 4][ordering & 0xF], SP_DRAW_MODE_CURSOR);
        D_8013BC40[buffer][ordering >> 4][ordering & 0xF] = (P_TAG*)((POLY_FT4*)slot - 1);
    }
    SP_DRAW_MODE_CURSOR = page;
}
#endif
#endif

#ifdef VERSION_DEMO
void func_8002EA00_demo(void)
{
    u8 i;
    P_TAG*(*ot)[8];
    POLY_F4* poly;
    struct DemoMovieHudQuad* row;
    DR_TPAGE* page;

    page = SP_DRAW_MODE_CURSOR;
    poly = SP_PRIM_CURSOR;
    row = D_800C63FC_demo;
    for (i = 0; i < 13; i++) {
        setPolyF4(poly);
        poly->x0 = row->x0;
        poly->y0 = row->y0;
        poly->x2 = row->x2;
        poly->y2 = row->y2;
        if (i < 10) {
            poly->x1 = row->x0 + g_Player.weapon_energy[i] * 2;
            poly->x3 = row->x2 + g_Player.weapon_energy[i] * 2;
        } else {
            poly->x1 = row->x1;
            poly->x3 = row->x3;
        }
        poly->y1 = row->y1;
        poly->y3 = row->y3;
        setRGB0(poly, 0x29, 0xC6, 0x29);
        setlen(page, 1);
        page->code[0] = (GetGraphType() == 1 || GetGraphType() == 2) ? 0xE1000000 : 0xE1000000;
        ot = D_8013BC40[SP_DRAW_BUFFER];
        setaddr(ot[0][5], page);
        setaddr(page, poly);
        ot[0][5] = (P_TAG*)poly;
        SP_PRIM_CURSOR = (POLY_FT4*)SP_PRIM_CURSOR + 1;
        SP_DRAW_MODE_CURSOR = (DR_TPAGE*)SP_DRAW_MODE_CURSOR + 1;
        page = SP_DRAW_MODE_CURSOR;
        poly = SP_PRIM_CURSOR;
        row++;
    }
}
#elif defined(MMX4_PC) || defined(MMX4_SATURN)
static const s16* pause_bar_geometry(u32 index)
{
    return index < 13 ? &D_800F1C18[index].x0 : (const s16*)D_800F1D04;
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
#elif defined(VERSION_EU)
INCLUDE_ASM("main/nonmatchings/pause_bar_draw", func_800179BC);
#else
void func_800179BC(void)
{
    s32 amount;
    u8 i;
    P_TAG*(*ot)[8];
    s8* energy;
    s8* hp;
    volatile u8* tank;
    POLY_F4* poly;
    struct MovieHudQuad* row;
    DR_TPAGE* page;

    page = SP_DRAW_MODE_CURSOR;
    poly = SP_PRIM_CURSOR;
    row = D_800F1C18;
    i = 0;
    energy = &g_Player.weapon_energy[0];
    hp = &g_Player.hp;

    for (; i < 0xE; i++) {
        setPolyF4(poly);

        if (((u8*)&bar_object)[0x16 + i] == 0) {
            if (i < 13) {
                row++;
                continue;
            }
        } else if (i != 0 && engine_obj.cur_character != CHARACTER_X && i < 9) {
            row++;
            continue;
        }
        poly->x0 = row->x0;
        poly->y0 = row->y0;
        poly->x1 = row->x1;
        poly->y1 = row->y1;
        poly->x2 = row->x2 - 1;
        poly->y2 = row->y2;
        poly->x3 = row->x3;
        poly->y3 = row->y3;

        if (i < 10) {
            if (i < 2) {
                if (engine_obj.cur_character == CHARACTER_X) {
                    if (i == 0) {
                        poly->x1 = row->x1;
                        poly->x3 = row->x3;
                    } else if (*energy != 0) {
                        poly->x1 = row->x0 + *energy * 2 - 1;
                        poly->x3 = row->x2 + *energy * 2 - 1;
                    } else {
                        poly->x1 = poly->x0;
                        poly->x3 = poly->x2;
                    }
                } else if (i == 0) {
                    if (*energy != 0) {
                        poly->x1 = row->x0 + *energy * 2 - 1;
                        poly->x3 = row->x2 + *energy * 2 - 1;
                    } else {
                        poly->x1 = poly->x0;
                        poly->x3 = poly->x2;
                    }
                }
            } else if (g_Player.weapon_energy[i - 1] != 0) {
                poly->x1 = row->x0 + g_Player.weapon_energy[i - 1] * 2 - 1;
                poly->x3 = row->x2 + g_Player.weapon_energy[i - 1] * 2 - 1;
            } else {
                poly->x1 = poly->x0;
                poly->x3 = poly->x2;
            }
        } else if (i == 13) {
            if (*hp > 0) {
                poly->x0 = 110;
                poly->y0 = 210;
                poly->x2 = 103;
                poly->y2 = 217;
                poly->x1 = poly->x0 + ((s8)*hp << 1);
                poly->y1 = 210;
                poly->x3 = poly->x2 + ((s8)*hp << 1);
                poly->y3 = 217;
            }
        } else {
            switch (i) {
            case 10:
                tank = &engine_obj.sub_tanks[0];
                amount = *tank & 0x7F;
                if (amount != 0) {
                    poly->x1 = poly->x0 + amount;
                    poly->x3 = poly->x2 + (*tank & 0x7F);
                } else {
                    poly->x1 = poly->x0;
                    poly->x3 = poly->x2;
                }
                break;
            case 11:
                tank = &engine_obj.sub_tanks[1];
                amount = *tank & 0x7F;
                if (amount != 0) {
                    poly->x1 = poly->x0 + amount;
                    poly->x3 = poly->x2 + (*tank & 0x7F);
                } else {
                    poly->x1 = poly->x0;
                    poly->x3 = poly->x2;
                }
                break;
            case 12:
                tank = &engine_obj.sub_tanks[2];
                poly->x1 = poly->x0 + (s8)*tank;
                poly->x3 = poly->x2 + (s8)*tank;
                break;
            }
        }

        setRGB0(poly, 0x29, 0xC6, 0x29);
        setlen(page, 1);
        page->code[0] = (GetGraphType() == 1 || GetGraphType() == 2) ? 0xE1000000 : 0xE1000000;
        ot = D_8013BC40[SP_DRAW_BUFFER];
        setaddr(ot[0][5], page);
        setaddr(page, poly);
        ot[0][5] = (P_TAG*)poly;
        SP_PRIM_CURSOR = (POLY_FT4*)SP_PRIM_CURSOR + 1;
        SP_DRAW_MODE_CURSOR = (DR_TPAGE*)SP_DRAW_MODE_CURSOR + 1;
        page = SP_DRAW_MODE_CURSOR;
        poly = SP_PRIM_CURSOR;
        row++;
    }
}
#endif

void func_80017E84(void)
{
    u32 row;
    u32 column;

    for (row = 0; row < 4; row++) {
        for (column = 0; column < 8; column++) {
            D_8013E1E8[0][row][column] = NULL;
            D_8013E1E8[1][row][column] = NULL;
            D_8013BC40[0][row][column] = (P_TAG*)&D_8013E1E8[0][row][column];
            D_8013BC40[1][row][column] = (P_TAG*)&D_8013E1E8[1][row][column];
        }
    }
}
void func_80017F2C(void)
{
    u32 buffer;
    u32 i;
    u32 j;
    OT_TYPE* otag;

    buffer = SP_DRAW_BUFFER;

    for (i = 0; i < 4; i++) {
        otag = &cur_draw_info->ordering_table.start + D_80173C6C[i];

        for (j = 0; j < 8; j++) {
            if (D_8013E1E8[buffer][i][j] != NULL) {
                setaddr(D_8013BC40[buffer][i][j], getaddr(otag));
                setaddr(otag, D_8013E1E8[buffer][i][j]);
            }
        }
    }
}

#ifdef VERSION_DEMO
void func_8002ED84_demo(void)
{
}

void func_8002ED8C_demo(void)
{
}
#endif
#endif
