#include "common.h"
#include "saturn/platform.h"

#define MENU_GROUP 11
#define MENU_HUD_COLOR 64
#define MENU_CHARACTER_BASE 0xF000
#define MENU_BANK 1
#define MENU_NO_ICON 0xFF
#define MENU_FRAME_TABLE 8
#define MENU_SELECTION 0x14
#define MENU_ARMOR_PART 0x17
#define MENU_WEAPONS 0x16
#define MENU_EXIT 0x25
#define MENU_HIGHLIGHT 16
#define MENU_BLINK 16
#define MENU_ITEMS 15
#define MENU_X_WEAPONS 10
#define MENU_ZERO_WEAPONS 8
#define MENU_ZERO_BRIGHT 10
#define MENU_TANKS 10
#define MENU_TANK_END 13
#define MENU_BAR_COLOR 0x121
#define MENU_HP_MASK 0x7F
#define PLAYER_CHARACTER 2
#define PLAYER_WEAPON 0x93
#define PLAYER_HP 0x5C
#define ENGINE_LIVES 0x44
#define ENGINE_MAX_HP 0x46

extern u8 saturn_engine_bytes[];
extern u8 saturn_player_bytes[];
extern u32 saturn_frame_counter;
extern u8 saturn_pause_menu[];
extern u8 saturn_pause_menu_resource[];
void saturn_vdp1_begin_group(u32 group);
void saturn_vdp1_end_group(void);

s16 saturn_pause_icon_x[] = {
    104,
    232,
    104,
    232,
    104,
    232,
    104,
    232,
    104,
    232,
    128,
    176,
    224,
    280,
    280,
    64,
    44,
    172,
    44,
    172,
    44,
    172,
    44,
    172,
    44,
    172,
    0,
    0,
    0,
    0,
    0,
    76,
    44,
    172,
    44,
    172,
    44,
    172,
    44,
    172,
    44,
    172,
    44,
    172,
};

s16 saturn_pause_icon_y[] = {
    40,
    40,
    64,
    64,
    88,
    88,
    112,
    112,
    136,
    136,
    176,
    176,
    176,
    168,
    200,
    192,
    36,
    36,
    60,
    60,
    84,
    84,
    108,
    108,
    132,
    132,
    0,
    0,
    0,
    0,
    0,
    216,
    44,
    172,
    36,
    36,
    60,
    60,
    84,
    84,
    108,
    108,
    132,
    132,
};

u8 saturn_pause_icon_frames[] = {
    0x00,
    0x01,
    0x02,
    0x03,
    0x04,
    0x05,
    0x06,
    0x07,
    0x08,
    0x09,
    0x23,
    0x23,
    0x24,
    0x0B,
    0x0C,
    0x0A,
    0x19,
    0x1A,
    0x1B,
    0x1C,
    0x1D,
    0x1E,
    0x1F,
    0x20,
    0x21,
    0x22,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0x17,
    0xFF,
    0xFF,
    0x25,
    0x25,
    0x25,
    0x25,
    0x25,
    0x25,
    0x25,
    0x25,
    0x25,
    0x25,
};

s16 saturn_pause_dim_colors[] = {
    68,
    68,
    68,
    68,
    68,
    68,
    68,
    68,
    68,
    68,
    70,
    70,
    70,
    72,
    72,
    74,
    68,
    68,
    68,
    68,
    68,
    68,
    68,
    68,
    68,
    68,
    70,
    70,
    70,
    72,
    72,
    74,
};

s16 saturn_pause_colors[] = {
    69,
    69,
    69,
    69,
    69,
    69,
    69,
    69,
    69,
    69,
    71,
    71,
    71,
    73,
    73,
    74,
    69,
    69,
    69,
    69,
    69,
    69,
    69,
    69,
    69,
    69,
    71,
    71,
    71,
    73,
    73,
    74,
};

s16 saturn_pause_dim_highlight_colors[] = {
    76,
    77,
    78,
    79,
    80,
    81,
    82,
    83,
    84,
    85,
    70,
    70,
    70,
    72,
    72,
    74,
    76,
    77,
    78,
    79,
    80,
    81,
    82,
    83,
    84,
    85,
    70,
    70,
    70,
    72,
    72,
    74,
};

s16 saturn_pause_highlight_colors[] = {
    86,
    87,
    88,
    89,
    90,
    91,
    92,
    93,
    94,
    95,
    71,
    71,
    71,
    73,
    73,
    74,
    86,
    87,
    88,
    89,
    90,
    91,
    92,
    93,
    94,
    95,
    71,
    71,
    71,
    73,
    73,
    74,
};

s16 saturn_pause_bar_positions[] = {
    56,
    27,
    184,
    27,
    56,
    51,
    184,
    51,
    56,
    75,
    184,
    75,
    56,
    99,
    184,
    99,
    56,
    123,
    184,
    123,
    107,
    196,
    155,
    196,
    203,
    196,
};

s8* saturn_pause_bar_values[] = {
    &g_Player.weapon_energy[0],
    &g_Player.weapon_energy[0],
    &g_Player.weapon_energy[1],
    &g_Player.weapon_energy[2],
    &g_Player.weapon_energy[3],
    &g_Player.weapon_energy[4],
    &g_Player.weapon_energy[5],
    &g_Player.weapon_energy[6],
    &g_Player.weapon_energy[7],
    &g_Player.weapon_energy[8],
    &engine_obj.sub_tanks[0],
    &engine_obj.sub_tanks[1],
    &engine_obj.sub_tanks[2],
};

void saturn_pause_draw(void)
{
    struct SaturnHudSprite* sprite = &saturn_hud_sprite;
    s8 selection;
    u32 count;
    u32 i;
    s32 weapon;
    saturn_vdp1_begin_group(MENU_GROUP);
    saturn_hud_color = MENU_HUD_COLOR;
    sprite->frames = saturn_pause_menu_resource + *(u32*)(saturn_pause_menu_resource + MENU_FRAME_TABLE);
    sprite->character_base = (s16)MENU_CHARACTER_BASE;
    sprite->bank = MENU_BANK;
    saturn_pause_draw_icon(sprite, 15, 74);
    count = saturn_player_bytes[PLAYER_CHARACTER] ? MENU_ZERO_WEAPONS : MENU_X_WEAPONS;
    for (i = 0; i < count; i++) {
        if (saturn_pause_menu[MENU_WEAPONS + i] != 0) {
            saturn_pause_draw_icon(sprite, i + 34, 72);
        }
    }
    selection = (s8)saturn_pause_menu[MENU_SELECTION];
    if (saturn_frame_counter & MENU_BLINK) {
        saturn_pause_draw_icon(sprite, selection + MENU_HIGHLIGHT, saturn_pause_dim_highlight_colors[selection]);
        saturn_pause_draw_icon(sprite, selection, saturn_pause_dim_colors[selection]);
    } else {
        saturn_pause_draw_icon(sprite, selection + MENU_HIGHLIGHT, saturn_pause_highlight_colors[selection]);
        saturn_pause_draw_icon(sprite, selection, saturn_pause_colors[selection]);
    }
    if (saturn_player_bytes[PLAYER_CHARACTER] == 0) {
        if (saturn_pause_menu[MENU_ARMOR_PART] != 0 && (s8)saturn_pause_menu[MENU_SELECTION] != 1) {
            saturn_pause_draw_icon(sprite, 1, saturn_pause_colors[1]);
            saturn_pause_draw_icon(sprite, 17, saturn_pause_highlight_colors[1]);
        }
        weapon = (s8)saturn_player_bytes[PLAYER_WEAPON];
        if (weapon != 0) {
            weapon++;
        }
        if ((s8)saturn_pause_menu[MENU_SELECTION] != weapon) {
            saturn_pause_draw_icon(sprite, weapon, saturn_pause_colors[weapon]);
            saturn_pause_draw_icon(sprite, weapon + MENU_HIGHLIGHT, saturn_pause_highlight_colors[weapon]);
        }
        for (i = 0; i < MENU_ITEMS; i++) {
            if (i != 1 && (s32)i != weapon && (s32)i != (s8)saturn_pause_menu[MENU_SELECTION] && saturn_pause_menu[MENU_WEAPONS + i] != 0) {
                saturn_pause_draw_icon(sprite, i + MENU_HIGHLIGHT, saturn_pause_dim_highlight_colors[i]);
                saturn_pause_draw_icon(sprite, i, saturn_pause_dim_colors[i]);
            }
        }
    } else {
        for (i = 0; i < MENU_ITEMS; i++) {
            if ((s32)i != (s8)saturn_pause_menu[MENU_SELECTION] && saturn_pause_menu[MENU_WEAPONS + i] != 0) {
                if (i < MENU_ZERO_BRIGHT) {
                    saturn_pause_draw_icon(sprite, i + MENU_HIGHLIGHT, saturn_pause_highlight_colors[i]);
                    saturn_pause_draw_icon(sprite, i, saturn_pause_colors[i]);
                } else {
                    saturn_pause_draw_icon(sprite, i + MENU_HIGHLIGHT, saturn_pause_dim_highlight_colors[i]);
                    saturn_pause_draw_icon(sprite, i, saturn_pause_dim_colors[i]);
                }
            }
        }
    }
    sprite->x = (s16)(((s8)saturn_engine_bytes[ENGINE_MAX_HP] - 32) * 2 + 0xC0);
    sprite->y = 0xD8;
    sprite->frame = 24;
    sprite->color = MENU_HUD_COLOR;
    saturn_hud_draw_sprite(sprite);
    saturn_pause_draw_bars();
    sprite->x = 92;
    sprite->y = 0xD8;
    sprite->frame = (u8)(saturn_engine_bytes[ENGINE_LIVES] + 13);
    sprite->color = 68;
    saturn_hud_draw_sprite(sprite);
    if (saturn_pause_menu[MENU_EXIT] != 0) {
        saturn_pause_draw_icon(sprite, 31, 68);
    }
    saturn_vdp1_end_group();
}

void saturn_pause_draw_icon(struct SaturnHudSprite* sprite, u32 index, s16 color)
{
    if (saturn_pause_icon_frames[index] == MENU_NO_ICON) {
        return;
    }
    sprite->x = saturn_pause_icon_x[index];
    sprite->y = saturn_pause_icon_y[index];
    sprite->frame = saturn_pause_icon_frames[index];
    sprite->color = color;
    saturn_hud_draw_sprite(sprite);
}

static void menu_draw_item_bar(struct SaturnHudRect* rect, u32 index)
{
    s8* value = saturn_pause_bar_values[index];
    rect->x = saturn_pause_bar_positions[index * 2];
    rect->y = saturn_pause_bar_positions[index * 2 + 1];
    if (*value != 0) {
        rect->w = (s16)((*value - 1) * 2);
        saturn_hud_draw_rect(rect);
    }
}

static void menu_set_offsets(s16 value)
{
    saturn_hud_offsets.x[1] = value;
    saturn_hud_offsets.x[0] = value;
}

void saturn_pause_draw_bars(void)
{
    struct SaturnHudRect rect;
    s32 hp;
    u32 i;
    menu_set_offsets(6);
    rect.x = 103;
    rect.y = 0xD2;
    rect.h = 6;
    rect.color = MENU_BAR_COLOR;
    hp = saturn_player_bytes[PLAYER_HP] & MENU_HP_MASK;
    if (hp != 0) {
        rect.w = (s16)(hp * 2);
        saturn_hud_draw_rect(&rect);
    }
    if (saturn_player_bytes[PLAYER_CHARACTER] == 0) {
        menu_set_offsets(4);
        rect.h = 4;
        rect.color = MENU_BAR_COLOR;
        rect.x = saturn_pause_bar_positions[0];
        rect.y = saturn_pause_bar_positions[1];
        rect.w = 94;
        saturn_hud_draw_rect(&rect);
    } else if (saturn_pause_menu[MENU_WEAPONS] != 0) {
        menu_set_offsets(4);
        rect.h = 4;
        rect.color = MENU_BAR_COLOR;
        menu_draw_item_bar(&rect, 0);
    }
    if (saturn_player_bytes[PLAYER_CHARACTER] == 0 && saturn_pause_menu[MENU_ARMOR_PART] != 0) {
        menu_draw_item_bar(&rect, 1);
    }
    if (saturn_player_bytes[PLAYER_CHARACTER] == 0) {
        for (i = 2; i < MENU_TANKS; i++) {
            if (saturn_pause_menu[MENU_WEAPONS + i] != 0) {
                menu_draw_item_bar(&rect, i);
            }
        }
    }
    menu_set_offsets(3);
    rect.h = 3;
    for (i = MENU_TANKS; i < MENU_TANK_END; i++) {
        if (saturn_pause_menu[MENU_WEAPONS + i] != 0) {
            s8* value = saturn_pause_bar_values[i];
            rect.x = saturn_pause_bar_positions[i * 2];
            rect.y = saturn_pause_bar_positions[i * 2 + 1];
            if (*value & MENU_HP_MASK) {
                rect.w = (s16)(*value & MENU_HP_MASK);
                saturn_hud_draw_rect(&rect);
            }
        }
    }
}
