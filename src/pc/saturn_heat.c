
#include "common.h"
#include <string.h>

#define VDP2_SCRCTL 0x9A
#define VDP2_LSTA0 0xA0
#define VDP2_LSTA1 0xA4
#define LINE_TABLE_BASE 0x6E000
#define LINE_TABLE_WORDS 512

int mmx4_pc_saturn_heat;
struct Mmx4PcLineScroll mmx4_pc_line_scroll;
static unsigned long alive_frame;
static int alive;

void mmx4_pc_line_scroll_commit(void)
{
    memcpy(mmx4_pc_line_scroll.table, mmx4_pc_line_scroll.work, sizeof(mmx4_pc_line_scroll.table));
}

void mmx4_pc_line_scroll_alive(void)
{
    alive_frame = mmx4_pc_frame_number();
    alive = 1;
}

void mmx4_pc_line_scroll_reset(void)
{
    memset(&mmx4_pc_line_scroll, 0, sizeof(mmx4_pc_line_scroll));
    alive = 0;
}

static u16 vdp2_read16(u32 offset)
{
    u16 value;
    memcpy(&value, (u8*)mmx4_pc_line_scroll.vdp2 + offset, sizeof(value));
    return value;
}

static u32 vdp2_read32(u32 offset)
{
    u32 value;
    memcpy(&value, (u8*)mmx4_pc_line_scroll.vdp2 + offset, sizeof(value));
    return value;
}

int mmx4_pc_heat_layer_plane(s32 layer)
{
    return mmx4_pc_heat_plane_for(engine_obj.stage, engine_obj.substage, layer);
}

int mmx4_pc_line_scroll_active(void)
{
    return mmx4_pc_saturn_heat && alive && mmx4_pc_frame_number() - alive_frame <= 1;
}

static s32 table_word(u32 byte_address)
{
    u32 index;
    if (byte_address < LINE_TABLE_BASE)
        return 0;
    index = (byte_address - LINE_TABLE_BASE) / 4;
    return index < LINE_TABLE_WORDS ? mmx4_pc_line_scroll.table[index] : 0;
}

static s32 scroll_value(s32 fixed16) { return (((fixed16 >> 16) & 0x7FF) << 8) | ((fixed16 >> 8) & 0xFF); }

static s32 wrap_delta(s32 delta) { return ((delta + 1024) & 0x7FF) - 1024; }

int mmx4_pc_heat_line_offsets(int plane, s32 scroll_x, s32 scroll_y, s32* world_x, s32* world_y, int lines)
{
    u8 control;
    u32 address;
    u32 stride;
    s32 base_x = scroll_x >> 16;
    s32 base_y = scroll_y >> 16;
    int line;

    if (!mmx4_pc_line_scroll_active())
        return 0;
    control = (u8)(vdp2_read16(VDP2_SCRCTL) >> (plane * 8));
    if (!(control & 6))
        return 0;
    {
        u32 lsta = vdp2_read32(plane == 0 ? VDP2_LSTA0 : VDP2_LSTA1);
        address = (((lsta >> 16) & 7) << 16 | (lsta & 0xFFFE)) * 2;
    }
    stride = (((control & 2) != 0) + ((control & 4) != 0) + ((control & 8) != 0)) * 4;
    for (line = 0; line < lines; line++) {
        u32 entry = address + (u32)line * stride;
        s32 x = base_x;
        s32 y = base_y + line;
        if (control & 2) {
            s32 value = scroll_value(table_word(entry)) + scroll_value(scroll_x);
            x = base_x + wrap_delta((value >> 8) - base_x);
            entry += 4;
        }
        if (control & 4) {
            s32 value = scroll_value(table_word(entry)) + scroll_value(scroll_y);
            y = base_y + wrap_delta((value >> 8) - base_y);
        }
        world_x[line] = x;
        world_y[line] = y;
    }
    return 1;
}

struct HeatStagePlanes {
    s8 stage;
    s8 substage;
    s8 planes[3];
};

static const struct HeatStagePlanes heat_stage_planes[] = {
    { 0, 1, { 0, -1, 1 } },
    { 4, 0, { -1, 0, 1 } },
    { 4, 1, { 0, -1, 1 } },
};

int mmx4_pc_heat_plane_for(s32 stage, s32 substage, s32 layer)
{
    size_t i;
    if (layer < 0 || layer >= 3)
        return -1;
    for (i = 0; i < sizeof(heat_stage_planes) / sizeof(heat_stage_planes[0]); i++) {
        if (heat_stage_planes[i].stage == stage && heat_stage_planes[i].substage == substage)
            return heat_stage_planes[i].planes[layer];
    }
    return -1;
}

static struct StageObjectRecord heat_records_0_1[] = {
    { 0x00, 0x0B, 0x00, 0x03, 0, 256 },
    { 0x00, 0x00, 0x00, 0xFF, 0, 0 },
};
static struct StageObjectRecord heat_records_none[] = {
    { 0x00, 0x00, 0x00, 0xFF, 0, 0 },
};

struct StageObjectRecord* mmx4_pc_saturn_heat_records(s32 stage, s32 substage)
{
    return stage == 0 && substage == 1 ? heat_records_0_1 : heat_records_none;
}
