#include "common.h"
#include "saturn/platform.h"
#include "main/player_weapon.h"

#define HUD_GROUP 11
#define HUD_COLOR 17
#define HUD_ALT_COLOR 1
#define HUD_CHARACTER_BASE 0x1000
#define HUD_BANK 1
#define HUD_COMMAND_LIMIT 0x3C0
#define HUD_COMMAND_BYTES 0x20
#define HUD_POLYGON 4
#define HUD_POLYGON_MODE 0xC0
#define HUD_SPRITE_MODE 0x80
#define HUD_SPRITE_SIZE 0x210
#define HUD_NO_GOURAUD 0xFFFF
#define HUD_BAR_TOP 79
#define HUD_BAR_WIDTH 4
#define HUD_BAR_DRAIN 0x123
#define HUD_BAR_HIGH 0x121
#define HUD_BAR_LOW 0x122
#define HUD_HP_MASK 0x7F
#define HUD_HP_HIT 0x80
#define HUD_BAR_DELAY 16
#define HUD_RIDE_MAX 48
#define HUD_RIDE_LOW 12
#define HUD_DIVIDE_ERROR 0x44E
#define OBJ_HP 0x5C
#define OBJ_BAR_SHOWN 0x5D
#define OBJ_BAR_TARGET 0x5E
#define OBJ_BAR_DELAY 0x5F
#define PLAYER_CHARACTER 2
#define PLAYER_WEAPON 0x93
#define PLAYER_ARMOR 0x94
#define PLAYER_WEAPON_ENERGY 0xA8
#define PLAYER_WEAPONS 0xB9
#define PLAYER_ZERO_WEAPON 0x20
#define PLAYER_WEAPON_THREE 3
#define ENGINE_RIDE 0x20
#define ENGINE_HUD 0x1F
#define ENGINE_RIDE_HUD 0x24
#define ENGINE_RIDE_KIND 0x25
#define ENGINE_LIVES 0x44
#define ENGINE_MAX_HP 0x46
#define FRAME_LIFE 69
#define FRAME_DIGIT 59
#define FRAME_WEAPON 78
#define FRAME_RIDE 87

extern u8 saturn_engine_bytes[];
extern u8 saturn_player_bytes[];
extern u32 saturn_frame_counter;
extern s32 saturn_runtime_error;
void saturn_vdp1_begin_group(u32 group);
void saturn_vdp1_end_group(void);

void saturn_hud_draw(void)
{
    u8* ride;
    saturn_hud_offsets.x[3] = 0;
    saturn_hud_offsets.x[2] = 0;
    saturn_hud_offsets.x[1] = 0;
    saturn_hud_offsets.x[0] = 0;
    saturn_hud_offsets.y[3] = 0;
    saturn_hud_offsets.y[2] = 0;
    saturn_hud_offsets.y[1] = 0;
    saturn_hud_offsets.y[0] = 0;
    saturn_vdp1_begin_group(HUD_GROUP);
    saturn_hud_color = HUD_COLOR;
    if (saturn_engine_bytes[ENGINE_HUD]) {
        saturn_hud_update_bar(saturn_player_bytes, (s8)saturn_engine_bytes[ENGINE_MAX_HP]);
        saturn_hud_draw_life();
        if (saturn_player_bytes[PLAYER_CHARACTER] == 0) {
            saturn_hud_draw_x_weapon();
        } else {
            saturn_hud_draw_zero_weapon();
        }
    }
    if (saturn_engine_bytes[ENGINE_RIDE_HUD]) {
        ride = *(u8**)(saturn_engine_bytes + ENGINE_RIDE);
        if (ride != NULL) {
            saturn_hud_update_bar(ride, HUD_RIDE_MAX);
            saturn_hud_draw_ride(ride);
        }
    }
    saturn_vdp1_end_group();
}

void saturn_hud_update_bar(u8* object, s8 maximum)
{
    s8 previous = (s8)object[OBJ_BAR_TARGET];
    s8 raw = (s8)object[OBJ_HP];
    u8 hp = (u8)(raw & HUD_HP_MASK);
    s8 value;
    if (raw < 0) {
        object[OBJ_BAR_DELAY] = HUD_BAR_DELAY;
    }
    value = (s8)hp;
    if ((s8)object[OBJ_BAR_TARGET] < value) {
        object[OBJ_BAR_SHOWN] = hp;
    }
    object[OBJ_BAR_TARGET] = hp;
    if ((s8)object[OBJ_BAR_SHOWN] == value && previous == value) {
        return;
    }
    if (value > previous) {
        if (value > maximum) {
            hp = (u8)maximum;
        }
        object[OBJ_HP] = (u8)((object[OBJ_HP] & HUD_HP_HIT) | hp);
        object[OBJ_BAR_SHOWN] = hp;
        object[OBJ_BAR_TARGET] = hp;
        return;
    }
    if ((s8)object[OBJ_BAR_SHOWN] == previous || object[OBJ_BAR_SHOWN] == 0) {
        return;
    }
    if (object[OBJ_BAR_DELAY] == 0) {
        if ((saturn_frame_counter & 3) == 0) {
            object[OBJ_BAR_SHOWN]--;
        }
    } else {
        object[OBJ_BAR_DELAY]--;
    }
}

static void hud_draw_bar(u8* object, s16 x, s16 low_threshold)
{
    struct SaturnHudRect rect;
    s8 shown = (s8)object[OBJ_BAR_SHOWN];
    s8 target = (s8)object[OBJ_BAR_TARGET];
    if (shown > target) {
        rect.x = x;
        rect.y = (s16)(HUD_BAR_TOP - shown);
        rect.w = HUD_BAR_WIDTH;
        rect.h = (s16)(shown - target - 1);
        rect.color = HUD_BAR_DRAIN;
        saturn_hud_draw_rect(&rect);
    }
    target = (s8)object[OBJ_BAR_TARGET];
    if (target > 0) {
        rect.color = target > low_threshold ? HUD_BAR_HIGH : HUD_BAR_LOW;
        rect.x = x;
        rect.y = (s16)(HUD_BAR_TOP - target);
        rect.w = HUD_BAR_WIDTH;
        rect.h = (s16)(target - 1);
        saturn_hud_draw_rect(&rect);
    }
}

static u8* hud_frames(void)
{
    u8* resource = (u8*)saturn_player_resource_section1;
    return resource + ((s32*)resource)[1];
}

static void hud_sprite_setup(s16 x, s16 y, u8 frame)
{
    saturn_hud_sprite.x = x;
    saturn_hud_sprite.y = y;
    saturn_hud_sprite.frames = hud_frames();
    saturn_hud_sprite.character_base = HUD_CHARACTER_BASE;
    saturn_hud_sprite.color = HUD_COLOR;
    saturn_hud_sprite.frame = frame;
    saturn_hud_sprite.bank = HUD_BANK;
}

void saturn_hud_draw_life(void)
{
    s32 hp = (s8)saturn_engine_bytes[ENGINE_MAX_HP] - 32;
    hud_sprite_setup(28, 56, (u8)(hp / 2 + FRAME_LIFE));
    saturn_hud_draw_sprite(&saturn_hud_sprite);
    saturn_hud_sprite.x = 35;
    saturn_hud_sprite.y = 88;
    saturn_hud_sprite.frame = (u8)((s8)saturn_engine_bytes[ENGINE_LIVES] + FRAME_DIGIT);
    saturn_hud_draw_sprite(&saturn_hud_sprite);
    hud_draw_bar(saturn_player_bytes, 18, (s16)((s8)saturn_engine_bytes[ENGINE_MAX_HP] / 3));
}

void saturn_hud_draw_rect(struct SaturnHudRect* rect)
{
    u16* command = (u16*)(saturn_sprite_commands + saturn_sprite_command_count * HUD_COMMAND_BYTES);
    command[0] = HUD_POLYGON;
    command[2] = HUD_POLYGON_MODE;
    command[3] = rect->color;
    command[6] = (u16)(rect->x + saturn_hud_offsets.x[0]);
    command[7] = (u16)(rect->y + saturn_hud_offsets.y[0]);
    command[8] = (u16)(saturn_hud_offsets.x[1] + rect->x + rect->w);
    command[9] = (u16)(rect->y + saturn_hud_offsets.y[1]);
    command[10] = (u16)(saturn_hud_offsets.x[2] + rect->x + rect->w);
    command[11] = (u16)(rect->y + saturn_hud_offsets.y[2] + rect->h);
    command[12] = (u16)(saturn_hud_offsets.x[3] + rect->x);
    command[13] = (u16)(rect->y + saturn_hud_offsets.y[3] + rect->h);
    command[14] = HUD_NO_GOURAUD;
    saturn_sprite_command_count++;
}

static void hud_draw_energy_bar(s8 energy)
{
    struct SaturnHudRect rect;
    if (energy > 0) {
        rect.x = 32;
        rect.y = 78;
        rect.w = HUD_BAR_WIDTH;
        rect.h = (s16)(1 - energy);
        rect.color = HUD_BAR_HIGH;
        saturn_hud_draw_rect(&rect);
    }
}

static void hud_draw_energy(s8 energy)
{
    saturn_hud_sprite.x = 17;
    saturn_hud_sprite.y = 22;
    saturn_hud_sprite.frame = (u8)(energy / 10 + FRAME_DIGIT);
    saturn_hud_draw_sprite(&saturn_hud_sprite);
    saturn_hud_sprite.x = 22;
    saturn_hud_sprite.y = 22;
    saturn_hud_sprite.frame = (u8)(energy % 10 + FRAME_DIGIT);
    saturn_hud_draw_sprite(&saturn_hud_sprite);
}

void saturn_hud_draw_x_weapon(void)
{
    s8 weapon = (s8)saturn_player_bytes[PLAYER_WEAPON];
    s8 divisor;
    s8 energy;
    u32 bit;
    if (weapon == 0) {
        return;
    }
    bit = (u32)(weapon - 1) >= 32 ? 0 : 1u << (weapon - 1);
    if ((saturn_player_bytes[PLAYER_WEAPONS] & bit) == 0) {
        return;
    }
    hud_sprite_setup(28, 56, FRAME_WEAPON);
    saturn_hud_draw_sprite(&saturn_hud_sprite);
    saturn_hud_sprite.x = 33;
    saturn_hud_sprite.y = 20;
    saturn_hud_sprite.color = (s8)saturn_player_bytes[PLAYER_WEAPON] == PLAYER_WEAPON_THREE ? HUD_COLOR : HUD_ALT_COLOR;
    saturn_hud_sprite.frame = (u8)((s8)saturn_player_bytes[PLAYER_WEAPON] + FRAME_WEAPON);
    saturn_hud_draw_sprite(&saturn_hud_sprite);
    saturn_hud_sprite.color = HUD_COLOR;
    divisor = player_weapon_energy.hud.health_divisors[(s8)saturn_player_bytes[PLAYER_ARMOR]];
    energy = (s8)saturn_player_bytes[PLAYER_WEAPON_ENERGY + (s8)saturn_player_bytes[PLAYER_WEAPON]];
    if (divisor == 0) {
        saturn_runtime_error = HUD_DIVIDE_ERROR;
        energy = 0;
    } else {
        energy = (s8)(energy / divisor);
    }
    hud_draw_energy(energy);
    hud_draw_energy_bar((s8)saturn_player_bytes[PLAYER_WEAPON_ENERGY + (s8)saturn_player_bytes[PLAYER_WEAPON]]);
}

void saturn_hud_draw_zero_weapon(void)
{
    if ((saturn_player_bytes[PLAYER_WEAPONS] & PLAYER_ZERO_WEAPON) == 0) {
        return;
    }
    hud_sprite_setup(28, 56, FRAME_WEAPON);
    saturn_hud_draw_sprite(&saturn_hud_sprite);
    saturn_hud_sprite.color = HUD_COLOR;
    hud_draw_energy((s8)((s8)saturn_player_bytes[PLAYER_WEAPON_ENERGY] / 12));
    hud_draw_energy_bar((s8)saturn_player_bytes[PLAYER_WEAPON_ENERGY]);
}

void saturn_hud_draw_ride(u8* ride)
{
    hud_sprite_setup(0x128, 65, (u8)(saturn_engine_bytes[ENGINE_RIDE_KIND] + FRAME_RIDE));
    saturn_hud_draw_sprite(&saturn_hud_sprite);
    hud_draw_bar(ride, 0x125, HUD_RIDE_LOW);
}

void saturn_hud_draw_sprite(struct SaturnHudSprite* sprite)
{
    u8* frames = sprite->frames;
    u8* entry = frames + sprite->frame * 4;
    u8* piece = frames + *(u16*)(entry + 2) * 4;
    u16 color = (u16)(sprite->color | (sprite->bank << 8));
    s16 x = sprite->x;
    s16 y = sprite->y;
    s32 count = *(s16*)entry;
    u16* command;
    if (saturn_sprite_command_count + count + 1 >= HUD_COMMAND_LIMIT) {
        return;
    }
    command = (u16*)(saturn_sprite_commands + saturn_sprite_command_count * HUD_COMMAND_BYTES);
    while ((s16)count != 0) {
        count--;
        command[0] = (u16)((piece[0] & 0xC0) >> 2);
        command[2] = HUD_SPRITE_MODE;
        command[3] = (u16)((u16)(((piece[0] & 0x0C) >> 2) + color) << 4);
        command[4] = (u16)((piece[1] << 4) + sprite->character_base + ((piece[0] & 3) << 12));
        command[5] = HUD_SPRITE_SIZE;
        command[6] = (u16)((s8)piece[2] + x);
        command[7] = (u16)((s8)piece[3] + y);
        piece += 4;
        command += HUD_COMMAND_BYTES / 2;
        saturn_sprite_command_count++;
    }
    saturn_sprite_pending = 1;
}
