#include "test_runtime.h"
#include "saturn/platform.h"

static u8 header[4];
static u8 entries[32];

static void entry(u32 index, u8 type, u8 id, u16 raw)
{
    entries[index * 4] = type;
    entries[index * 4 + 1] = id;
    entries[index * 4 + 2] = raw >> 8;
    entries[index * 4 + 3] = raw;
}

static void ports(u8 type, u8 first, u8 second)
{
    saturn_peripheral_work = header;
    saturn_peripheral_data = entries;
    header[0] = type;
    header[1] = first;
    header[3] = second;
}

static void read_analog_wrong_id(void)
{
    ports(0, 1, 0);
    entry(0, 0x10, 2, 0);
    saturn_pads[0].held = 0x1234;
    saturn_pad_read(0, &saturn_pads[0]);
}

static void select_first_two(void)
{
    ports(0, 3, 0);
    entry(0, 0xF0, 15, 0);
    entry(1, 0x00, 2, 0);
    entry(2, 0x10, 5, 0);
    saturn_controller_refresh = 1;
    saturn_controller_select_ports();
}

static void select_first_then_port_two(void)
{
    ports(0, 2, 3);
    entry(0, 0x00, 2, 0);
    entry(1, 0xF0, 15, 0);
    entry(2, 0xF0, 15, 0);
    entry(3, 0x10, 5, 0);
    saturn_controller_refresh = 1;
    saturn_controller_select_ports();
}

static void select_second_after_first(void)
{
    ports(0, 3, 0);
    entry(0, 0x00, 2, 0);
    entry(1, 0xF0, 15, 0);
    entry(2, 0x00, 2, 0);
    saturn_pads[0].port = 0;
    saturn_controller_refresh = 2;
    saturn_controller_select_ports();
}

static void update_no_port(void)
{
    ports(0, 1, 0);
    saturn_controller_refresh = 0;
    saturn_pads[0].port = -1;
    saturn_pads[0].held = 0x55;
    saturn_controller_update();
}

static void update_port_gone(void)
{
    ports(0, 1, 0);
    saturn_controller_refresh = 0;
    saturn_pads[0].port = 1;
    saturn_pads[0].held = 0x0101;
    saturn_controller_update();
}

static void update_single_pad_header(void)
{
    ports(0xF0, 1, 0);
    entry(0, 0x10, 5, 0xFFFF & ~0x0002);
    saturn_controller_refresh = 0;
    saturn_pads[0].port = 0;
    saturn_controller_update();
}

static void update_no_pad_header_second_port(void)
{
    ports(0xF0, 1, 0);
    saturn_controller_refresh = 0;
    saturn_pads[0].port = 1;
    saturn_controller_update();
}

static void update_refreshes(void)
{
    ports(0, 1, 0);
    entry(0, 0x00, 2, 0xFFFF & ~0x0810);
    saturn_pads[0].held = 0x0011;
    saturn_controller_refresh = 1;
    saturn_controller_update();
}

static void (*const pad_cases[])(void) = {
    read_analog_wrong_id,
    select_first_two,
    select_first_then_port_two,
    select_second_after_first,
    update_no_port,
    update_port_gone,
    update_single_pad_header,
    update_no_pad_header_second_port,
    update_refreshes,
};

#define WORDS 5
static const u32 pad_expected[][WORDS] = {
#include "platform_pad_expected.inc"
};

static u32 pad_run(u32 row)
{
    const struct SaturnPad* a = &saturn_pads[0];
    const struct SaturnPad* b = &saturn_pads[1];
    u32 observed[WORDS];
    saturn_pads[0].port = 0x7F;
    saturn_pads[1].port = 0x7F;
    pad_cases[row]();
    observed[0] = a->type | a->id << 8 | (u8)a->port << 16 | (u8)b->port << 24;
    observed[1] = a->held | (u32)a->previous << 16;
    observed[2] = a->pressed | (u32)a->released << 16;
    observed[3] = saturn_pause_request;
    observed[4] = b->type | b->id << 8 | (u32)b->held << 16;
    return c_test_observe(0, row, observed, pad_expected[row], WORDS);
}

const struct CTestGroup c_test_groups[] = {
    { "saturn_pad", 0, 0, COUNT(pad_cases), pad_run },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(pad_cases);
