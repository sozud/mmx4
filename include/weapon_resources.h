#ifndef MMX4_WEAPON_RESOURCES_H
#define MMX4_WEAPON_RESOURCES_H

#ifdef MMX4_SATURN
#include "saturn/weapon_resources.h"
#define WEAPON_TEXTURE_BASE 0x1000
#define WEAPON_TEXTURE_PLAYER 0xC000
#define WEAPON_TEXTURE_SPECIAL_0 0xC200
#define WEAPON_TEXTURE_SPECIAL_1 0xC300
#define WEAPON_TEXTURE_SPECIAL_2 0xC400
#define WEAPON_PALETTE_1 1
#define WEAPON_PALETTE_2 2
#define WEAPON_PALETTE_3 3
#define WEAPON_PALETTE_4 4
#define WEAPON_PALETTE_5 5
#define WEAPON_PALETTE_6 6
#define WEAPON_PALETTE_10 10
#define VISUAL_STAGE_PALETTE(index) ((index) * 4 + 0x18)
#define VISUAL_SATURN_LAYER(value) (((value) & ~4) | (((value) & 4) ? 0x40 : 0))
#define VISUAL_SOUND_HOVER 0x0A
#define VISUAL_SOUND_EREGION_SLASH 0x0B
#define WEAPON_SOUND_WEB 0x22
#define WEAPON_SOUND_FROST 0x23
#define WEAPON_SOUND_FIRE 0x24
#define WEAPON_SOUND_LASER_LOCK 8
#define WEAPON_SOUND_LASER_CHARGE 9
#define WEAPON_SOUND_CYCLONE 0x25
#define OBJECT_STAGE_TEXTURE(index) PLAYER_STAGE_TEXTURE(index)
#define OBJECT_STAGE_CLUT(id) (func_8002938C(id) * 4 + 0x18)
#define SATURN_SOUND(psx, saturn) (saturn)
#define SATURN_ALT(psx, saturn) (saturn)
#define OBJECT_TEXTURE_OFFSET(units) ((units) << 4)
#define OBJECT_CLUT(clut) (((((clut) >> 6) - 0x1E0) << 4) + ((clut) & 0x3F))
#define OBJECT_PALETTE_FROM_COLOR(color) ((u8)(color))
#define QUAD_SET_ON_SCREEN(quad) saturn_queue_frozen_quad(quad)
#define SATURN_TILE_ATTRS (*(u32**)0x0600D02C)
#define TILE_ATTR_VALUE(value) ((u32)(value) << 24)
#define QUAD_QUEUE(quad) saturn_queue_frozen_quad(quad)
#define STOP_SOUND(channel, id, saturn_slot) func_8001540C(6, (saturn_slot), NULL)
#else
#define WEAPON_FRAME_COUNTER main_bss_state.frame_counter
#define WEAPON_TEXTURE_BASE 0
#define WEAPON_TEXTURE_PLAYER 0x500
#define WEAPON_TEXTURE_SPECIAL_0 0x520
#define WEAPON_TEXTURE_SPECIAL_1 0x530
#define WEAPON_TEXTURE_SPECIAL_2 0x540
#define WEAPON_PALETTE_1 0x7801
#define WEAPON_PALETTE_2 0x7802
#define WEAPON_PALETTE_3 0x7803
#define WEAPON_PALETTE_4 0x7804
#define WEAPON_PALETTE_5 0x7805
#define WEAPON_PALETTE_6 0x7806
#define WEAPON_PALETTE_10 0x780A
#define VISUAL_STAGE_PALETTE(index) SOME_COORDINATE_CONVERSION(index)
#define VISUAL_SATURN_LAYER(value) value
#define VISUAL_SOUND_HOVER 0x1F
#define VISUAL_SOUND_EREGION_SLASH 0x20
#define WEAPON_SOUND_WEB 0x19
#define WEAPON_SOUND_FROST 0x1A
#define WEAPON_SOUND_FIRE 0x1B
#define WEAPON_SOUND_LASER_LOCK 0x1C
#define WEAPON_SOUND_LASER_CHARGE 0x1D
#define WEAPON_SOUND_CYCLONE 0x1E
#define OBJECT_STAGE_TEXTURE(index) (D_801406A8[index] >> 7)
#define OBJECT_STAGE_CLUT(id) CLUT_FROM_ID(id)
#define SATURN_SOUND(psx, saturn) (psx)
#define SATURN_ALT(psx, saturn) (psx)
#define OBJECT_TEXTURE_OFFSET(units) (units)
#define OBJECT_CLUT(clut) (clut)
#define OBJECT_PALETTE_FROM_COLOR(color) (((color) & 0xF) | ((((color) >> 4) + 0x1E0) << 6))
#define QUAD_SET_ON_SCREEN(quad) ((quad)->on_screen = 1)
#define QUAD_QUEUE(quad) ((void)0)
#define TILE_ATTR_VALUE(value) (value)
#define STOP_SOUND(channel, id, saturn_slot) stop_sound((channel), (id))
#endif

#endif
