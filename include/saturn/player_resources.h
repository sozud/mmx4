#ifndef MMX4_SATURN_PLAYER_RESOURCES_H
#define MMX4_SATURN_PLAYER_RESOURCES_H

extern s32* saturn_player_resource_section0;
extern s32* saturn_player_resource_section1;
extern s32* saturn_stage_frame_banks;
extern Palette* saturn_player_palette_source;
extern u16* saturn_player_palette_destination;
extern u32* saturn_stage_graphics_offsets_pointer;
extern u16 saturn_pad_held, saturn_pad_previous, saturn_pad_pressed;

#undef SP_PLAYER_GFX
#undef SP_SPRITE_FRAMES
#undef SP_MENU_FRAMES
#undef SP_PALETTE_BANK
#undef SP_PALETTE
#undef SP_PALETTES
#define SP_PLAYER_GFX saturn_player_resource_section0
#define SP_SPRITE_FRAMES saturn_player_resource_section1
#define SP_MENU_FRAMES saturn_stage_frame_banks
#define SP_PALETTE_BANK saturn_player_palette_source
#define SP_PALETTE saturn_player_palette_destination
#define SP_PALETTES ((Palette*)saturn_player_palette_destination)

#define PLAYER_TEXTURE_BASE 0xC000
#define PLAYER_CLONE_TEXTURE_BASE 0xC400
#define PLAYER_EFFECT_TEXTURE_BASE 0x1000
#define PLAYER_PALETTE_BASE 0
#define PLAYER_AFTERIMAGE_DRAW_FLAGS 0x40
#define PLAYER_STAGE_TEXTURE(index) \
    (((saturn_stage_graphics_offsets_pointer[index] & ~127u) + 0x25C24000u) >> 3)
#define PLAYER_STAGE_PALETTE() ((u8)func_8002938C(0x84) * 4 + 0x18)
#define PLAYER_PAD_HELD saturn_pad_held
#define PLAYER_PAD_PREVIOUS saturn_pad_previous
#define PLAYER_PAD_PRESSED saturn_pad_pressed

#endif
