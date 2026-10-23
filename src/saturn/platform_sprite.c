#include "common.h"
#include "saturn/platform.h"
#include "saturn.h"

#define SPRITE_ACTIVE 0x01
#define SPRITE_SEMI_TRANSPARENT 0x02
#define SPRITE_SHADOW 0x10
#define SPRITE_QUAD 0x80
#define SPRITE_VISIBLE 3
#define SPRITE_CAMERA 55
#define SPRITE_X 8
#define SPRITE_Y 12
#define SPRITE_CORNERS 20
#define SPRITE_COLOR 52
#define CAMERA_STRIDE 84
#define CAMERA_X 8
#define CAMERA_Y 12
#define COMMAND_BYTES 0x20
#define COMMAND_LIMIT 0x3C0
#define COMMAND_POLYGON 4
#define POLYGON_MODE 0xC0
#define POLYGON_MODE_HALF 0xEC
#define POLYGON_HALF_COLOR 0xC210
#define GOURAUD_NONE 0xFFFF
#define GOURAUD_BASE 0xFFE0
#define PLAYER_CHARACTER 2
#define PLAYER_PARTS 0xA7
#define PLAYER_ARMOR_KIND 0xB8
#define PART_HEAD 0x08
#define PART_BODY 0x01
#define PART_ARM 0x04
#define PART_LEGS 0x02
#define PART_PALETTE 19
#define OVERLAY_COUNT 2
#define OVERLAY_STRIDE 0x60

extern u8 saturn_player_bytes[];
extern u8 saturn_entity_bytes[];
extern u8 saturn_player_part[];
extern u8 saturn_overlay_objects[];
extern u8 saturn_player_companion_0[];
extern u8 saturn_player_companion_1[];
extern u8 saturn_sprite_cameras[];
extern u16 saturn_sprite_palette_group;
extern u16 saturn_sprite_pass_count;
void saturn_draw_normal_sprite(volatile u8* object);
void saturn_sprite_draw_passes(void);

extern const volatile u8 saturn_sprite_hidden_mode, saturn_sprite_hidden_bits;

extern void saturn_sprite_draw_overlay(void), saturn_sprite_draw_player(void);
extern const volatile s8 saturn_sprite_group_ids[4];
extern volatile s8 saturn_sprite_list_counts[20];
extern volatile u32 saturn_sprite_object_lists[768];

static const SaturnSpriteDrawLists sprite_final_lists = {
    saturn_sprite_list_counts + 2, saturn_sprite_object_lists + 64, 3
};

static const SaturnSpriteDrawLists sprite_foreground = {
    saturn_sprite_list_counts + 3, saturn_sprite_object_lists + 96, 1
};

static const SaturnSpritePassState sprite_passes[4] = {
    { (volatile u16*)&saturn_sprite_palette_group, saturn_sprite_group_ids + 0,
        { saturn_sprite_list_counts + 19, saturn_sprite_object_lists + 736, 4 } },
    { (volatile u16*)&saturn_sprite_palette_group, saturn_sprite_group_ids + 1,
        { saturn_sprite_list_counts + 7, saturn_sprite_object_lists + 256, 4 } },
    { (volatile u16*)&saturn_sprite_palette_group, saturn_sprite_group_ids + 2,
        { saturn_sprite_list_counts + 11, saturn_sprite_object_lists + 416, 4 } },
    { (volatile u16*)&saturn_sprite_palette_group, saturn_sprite_group_ids + 3,
        { saturn_sprite_list_counts + 15, saturn_sprite_object_lists + 576, 4 } }
};

static const SaturnSpritePassIO sprite_pass_io = {
    saturn_vdp1_begin_group, saturn_vdp1_end_group, (void (*)(u32))saturn_sprite_draw_object,
    saturn_sprite_draw_overlay, saturn_sprite_draw_player
};

static const SaturnSpriteState sprite_state = {
    (volatile SaturnSpriteCommand*)saturn_sprite_commands, (volatile u16*)&saturn_sprite_command_count,
    (volatile u16*)&saturn_sprite_pass_count, (volatile u16*)&saturn_sprite_pending,
    (volatile u16*)&saturn_sprite_palette_group, saturn_sprite_cameras,
    &saturn_sprite_hidden_mode, &saturn_sprite_hidden_bits
};

void saturn_sprite_draw_passes(void)
{
    saturn_sprite_pass_count = 0;
    saturn_sprite_draw_pass_3();
    saturn_sprite_draw_pass_2();
    saturn_sprite_draw_pass_1();
    saturn_sprite_draw_main_pass();
}

static void draw_part(u32 frames_offset, s16 palette)
{
    u8* resource = (u8*)saturn_player_resource_section1;
    *(s16*)(saturn_player_part + 66) = palette;
    *(u8**)(saturn_player_part + 60) = resource + *(s32*)(resource + frames_offset);
    saturn_draw_normal_sprite(saturn_player_part);
}

void saturn_sprite_draw_player(void)
{
    u8* player = saturn_player_bytes;
    u8 parts;
    if (player[0] == 0 || player[SPRITE_VISIBLE] == 0) {
        return;
    }
    saturn_draw_normal_sprite(player);
    if (player[PLAYER_CHARACTER] != 0) {
        return;
    }
    if (player[PLAYER_PARTS] != 0) {
        *(u16*)(saturn_player_part + 64) = *(u16*)(player + 64);
        saturn_player_part[71] = player[71];
        saturn_player_part[21] = player[21];
        saturn_player_part[3] = player[3];
        saturn_player_part[20] = player[20];
        *(s32*)(saturn_player_part + 8) = *(s32*)(player + 8);
        *(s32*)(saturn_player_part + 12) = *(s32*)(player + 12);
        parts = player[PLAYER_PARTS];
        if (parts & PART_HEAD) {
            draw_part(32, PART_PALETTE);
        }
        if (player[PLAYER_PARTS] & PART_BODY) {
            draw_part(20, PART_PALETTE);
        }
        if (player[PLAYER_PARTS] & PART_ARM) {
            draw_part(28, (s16)(player[PLAYER_ARMOR_KIND] == 2 ? PART_PALETTE + 1 : PART_PALETTE));
        }
        if (player[PLAYER_PARTS] & PART_LEGS) {
            draw_part(24, PART_PALETTE);
        }
    }
    if (saturn_entity_bytes[3]) {
        saturn_draw_normal_sprite(saturn_entity_bytes);
    }
    if (saturn_player_companion_0[3]) {
        saturn_draw_normal_sprite(saturn_player_companion_0);
    }
    if (saturn_player_companion_1[3]) {
        saturn_draw_normal_sprite(saturn_player_companion_1);
    }
}

void saturn_sprite_draw_overlay(void)
{
    u8* object;
    if (saturn_player_bytes[0] == 0 || saturn_player_bytes[SPRITE_VISIBLE] == 0) {
        return;
    }
    for (object = saturn_overlay_objects + OVERLAY_COUNT * OVERLAY_STRIDE; object >= saturn_overlay_objects;
         object -= OVERLAY_STRIDE) {
        if (object[SPRITE_VISIBLE]) {
            saturn_draw_normal_sprite(object);
        }
    }
}

static u16 sprite_be16(const volatile u8* bytes)
{
    return ((u16)bytes[0] << 8) | bytes[1];
}

void saturn_draw_normal_sprite_state(volatile u8* object, const u8* bank,
    const SaturnSpriteState* state)
{
    if (!object[3])
        return;
    const u8* header = bank + 4 * object[0x47];
    const u8* piece = bank + 4 * sprite_be16(header + 2);
    u16 pieces = sprite_be16(header);
    u32 palette_override = (sprite_be16(object + 0x42) & 0x8000) != 0;
    u32 palette = (palette_override ? 16 : sprite_be16(object + 0x42)) | ((u32)*state->palette_group << 8);
    s32 origin_x = (s16)sprite_be16(object + 8);
    s32 origin_y = (s16)sprite_be16(object + 12);
    s32 camera_index = (s8)object[0x14];
    if (camera_index >= 0) {
        const volatile u8* camera = state->cameras + ((84U * camera_index) & 255U);
        origin_x -= (s16)sprite_be16(camera + 8);
        origin_y -= (s16)sprite_be16(camera + 12);
    }
    if ((s32)*state->count + (s16)pieces + 1 >= SATURN_SPRITE_COMMAND_LIMIT)
        return;
    volatile SaturnSpriteCommand* command = state->commands + *state->count;
    for (; pieces; --pieces, piece += 4) {
        s32 x = (object[0x15] & 0x10) ? -(s8)piece[2] - 16 : (s8)piece[2];
        x += origin_x;
        if ((u16)(x + 16) >= 335)
            continue;
        s32 y = (object[0x15] & 0x20) ? -(s8)piece[3] - 16 : (s8)piece[3];
        y += origin_y;
        if ((u16)(y + 16) >= 255)
            continue;
        u32 hidden = *state->hidden_mode;
        if (hidden && hidden != 128 && (s8)object[0x14] != -1) {
            u32 bits = *state->hidden_bits;
            s32 sx = (s16)x, sy = (s16)y;
            if ((bits & 1) && sx >= 38 && sx <= 249 && sy >= 30 && sy <= 57)
                continue;
            if ((bits & 2) && sx >= 38 && sx <= 249 && sy >= 146 && sy <= 173)
                continue;
            if ((bits & 4) && sy >= 28 && sy <= 85 && ((sx >= 24 && sx <= 102) || (sx >= 184 && sx <= 262)))
                continue;
        }
        command->words[0] = object[0x15] ^ ((piece[0] & 0xC0) >> 2);
        command->words[2] = 0x80;
        command->words[3] = (u16)((palette + (palette_override ? 0 : (piece[0] & 12) >> 2)) << 4);
        command->words[4] = (u16)(sprite_be16(object + 0x40) + piece[1] * 16 + ((piece[0] & 3) << 12));
        command->words[5] = 0x210;
        command->words[6] = (u16)x;
        command->words[7] = (u16)y;
        ++command;
        ++*state->count;
        ++*state->pass_count;
    }
    *state->pending = 1;
    object[0x48] = object[0x47];
}

void saturn_draw_normal_sprite_body(volatile u8* object)
{
    u32 bank = ((u32)sprite_be16(object + 0x3C) << 16) | sprite_be16(object + 0x3E);
    saturn_draw_normal_sprite_state(object, (const u8*)(u32)bank, &sprite_state);
}

static void sprite_draw_lists(const SaturnSpriteDrawLists* lists, const SaturnSpritePassIO* io)
{
    for (u32 channel = 0; channel < lists->channels; ++channel) {
        s32 count = lists->counts[-(s32)channel];
        const volatile u32* objects = lists->objects - channel * 32;
        for (s32 i = 0; i < count; ++i)
            io->draw(objects[i]);
    }
}

static void sprite_begin_pass(const SaturnSpritePassState* state, const SaturnSpritePassIO* io)
{
    *state->palette = (u16)(s16)*state->group;
    io->begin(*state->palette);
    *state->palette ^= 7;
    sprite_draw_lists(&state->lists, io);
}

void saturn_sprite_main_pass_state(const SaturnSpritePassState* state, const SaturnSpritePassIO* io,
    const SaturnSpriteDrawLists* foreground,
    const SaturnSpriteDrawLists* final_lists)
{
    sprite_begin_pass(state, io);
    io->overlay();
    sprite_draw_lists(foreground, io);
    io->player();
    sprite_draw_lists(final_lists, io);
    io->end();
}

void saturn_sprite_draw_main_pass(void)
{
    saturn_sprite_main_pass_state(&sprite_passes[0], &sprite_pass_io,
        &sprite_foreground, &sprite_final_lists);
}

void saturn_sprite_pass_state(const SaturnSpritePassState* state, const SaturnSpritePassIO* io)
{
    sprite_begin_pass(state, io);
    io->end();
}

void saturn_sprite_draw_pass_1(void) { saturn_sprite_pass_state(&sprite_passes[1], &sprite_pass_io); }

void saturn_sprite_draw_pass_2(void) { saturn_sprite_pass_state(&sprite_passes[2], &sprite_pass_io); }

void saturn_sprite_draw_pass_3(void) { saturn_sprite_pass_state(&sprite_passes[3], &sprite_pass_io); }

void saturn_draw_quad(u8* quad)
{
    u16* command;
    u8* camera;
    s32 x;
    s32 y;
    u16 color;
    if ((quad[0] & SPRITE_ACTIVE) == 0 || quad[SPRITE_VISIBLE] == 0) {
        return;
    }
    if (saturn_sprite_command_count + 1 >= COMMAND_LIMIT) {
        return;
    }
    command = (u16*)(saturn_sprite_commands + saturn_sprite_command_count * COMMAND_BYTES);
    if ((s8)quad[SPRITE_CAMERA] >= 0) {
        camera = saturn_sprite_cameras + (u8)(quad[SPRITE_CAMERA] * CAMERA_STRIDE);
        x = *(s16*)(quad + SPRITE_X) - *(s16*)(camera + CAMERA_X);
        y = *(s16*)(quad + SPRITE_Y) - *(s16*)(camera + CAMERA_Y);
    } else {
        x = *(s16*)(quad + SPRITE_X);
        y = *(s16*)(quad + SPRITE_Y);
    }
    command[0] = COMMAND_POLYGON;
    if (quad[0] & SPRITE_SEMI_TRANSPARENT) {
        command[2] = (u16)(((quad[0] & SPRITE_SHADOW) << 4) | POLYGON_MODE_HALF);
        color = POLYGON_HALF_COLOR;
    } else {
        command[2] = (u16)(((quad[0] & SPRITE_SHADOW) << 4) | POLYGON_MODE);
        color = (u16)((saturn_sprite_palette_group << 12) | *(u16*)(quad + SPRITE_COLOR));
    }
    command[3] = color;
    command[6] = (u16)(*(s16*)(quad + 20) + x);
    command[7] = (u16)(*(s16*)(quad + 24) + y);
    command[8] = (u16)(*(s16*)(quad + 28) + x);
    command[9] = (u16)(*(s16*)(quad + 32) + y);
    command[10] = (u16)(*(s16*)(quad + 36) + x);
    command[11] = (u16)(*(s16*)(quad + 40) + y);
    command[12] = (u16)(*(s16*)(quad + 44) + x);
    command[13] = (u16)(*(s16*)(quad + 48) + y);
    if (quad[0] & SPRITE_SEMI_TRANSPARENT) {
        command[14] = (u16)((*(u16*)(quad + SPRITE_COLOR) & 0x7FFF) + GOURAUD_BASE);
    } else {
        command[14] = GOURAUD_NONE;
    }
    saturn_sprite_command_count++;
    saturn_sprite_pass_count++;
    saturn_sprite_pending = 1;
}

void saturn_sprite_draw_object(u8* object)
{
    if (object[0] & SPRITE_QUAD) {
        saturn_draw_quad(object);
    } else {
        saturn_draw_normal_sprite(object);
    }
}
