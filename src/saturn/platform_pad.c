#include "common.h"
#include "saturn/platform.h"

#define PAD_TYPE_DIGITAL 0x00
#define PAD_TYPE_ANALOG 0x10
#define PAD_TYPE_NONE 0xF0
#define PAD_ID_DIGITAL 2
#define PAD_ID_ANALOG 5
#define PAD_ID_NONE 15
#define PAD_NO_PORT (-1)
#define PAD_SECOND_PORT_BASE 6
#define PAD_REFRESH_FIRST 1
#define PAD_REFRESH_SECOND 2
#define PAD_ENTRY_BYTES 4

void saturn_controller_update(void)
{
    u8* header;
    s8 port;
    if (saturn_controller_refresh != 0) {
        saturn_controller_select_ports();
    }
    port = saturn_pads[0].port;
    if (port == PAD_NO_PORT) {
        saturn_pad_clear(&saturn_pads[0]);
        return;
    }
    header = saturn_peripheral_work;
    if ((header[0] != PAD_TYPE_NONE && port < header[1]) || (header[0] == PAD_TYPE_NONE && header[1] == 1 && port == 0)) {
        saturn_pad_read(port, &saturn_pads[0]);
        return;
    }
    saturn_pad_clear(&saturn_pads[0]);
    saturn_pause_request = 1;
}

static u8* pad_entry(s8 index)
{
    return saturn_peripheral_data + index * PAD_ENTRY_BYTES;
}

static s32 pad_usable(s8 index)
{
    u8 type = pad_entry(index)[0];
    return type == PAD_TYPE_DIGITAL || type == PAD_TYPE_ANALOG;
}

static void pad_find_second_port(s8 index)
{
    u8* header = saturn_peripheral_work;
    while (index < header[1] + header[3]) {
        if (pad_usable(index)) {
            saturn_pads[1].port = (s8)(index - header[1] + PAD_SECOND_PORT_BASE);
            return;
        }
        index++;
    }
}

void saturn_controller_select_ports(void)
{
    u8* header = saturn_peripheral_work;
    s8 index;
    if (saturn_controller_refresh == PAD_REFRESH_FIRST) {
        saturn_pads[0].port = PAD_NO_PORT;
        saturn_pads[1].port = PAD_NO_PORT;
        if (header[1] == 0) {
            return;
        }
        for (index = 0; index < header[1]; index++) {
            if (pad_usable(index)) {
                saturn_pads[0].port = index;
                break;
            }
        }
        if (index == header[1]) {
            return;
        }
        for (index++; index < header[1]; index++) {
            if (pad_usable(index)) {
                saturn_pads[1].port = index;
                break;
            }
        }
        if (index != header[1]) {
            return;
        }
        pad_find_second_port(index);
    } else if (saturn_controller_refresh == PAD_REFRESH_SECOND) {
        saturn_pads[1].port = PAD_NO_PORT;
        if (header[1] != 0) {
            for (index = (s8)(saturn_pads[0].port + 1); index < header[1]; index++) {
                if (pad_usable(index)) {
                    saturn_pads[1].port = index;
                    break;
                }
            }
        } else {
            index = 0;
        }
        if (index != header[1]) {
            return;
        }
        pad_find_second_port(index);
    }
}

void saturn_pad_read(s8 index, struct SaturnPad* pad)
{
    u8* entry = pad_entry(index);
    u8 type = entry[0];
    u16 raw;
    if ((type == PAD_TYPE_DIGITAL && entry[1] == PAD_ID_DIGITAL) || (type == PAD_TYPE_ANALOG && entry[1] == PAD_ID_ANALOG)) {
        pad->type = PAD_TYPE_DIGITAL;
        pad->id = PAD_ID_DIGITAL;
        pad->previous = pad->held;
        raw = (u16)(((entry[2] << 8) & 0xFF00) | (entry[3] & 0xFF));
        pad->held = (u16)~raw;
        pad->pressed = pad->held & (u16)~pad->previous;
        pad->released = pad->previous & (u16)~pad->held;
        saturn_pause_request = 0;
    } else {
        pad->type = PAD_TYPE_NONE;
        pad->id = PAD_ID_NONE;
        pad->previous = 0;
        pad->held = 0;
        pad->pressed = 0;
        pad->released = 0;
        saturn_pause_request = 1;
    }
}

void saturn_pad_clear(struct SaturnPad* pad)
{
    pad->type = PAD_TYPE_NONE;
    pad->id = PAD_ID_NONE;
    pad->previous = 0;
    pad->held = 0;
    pad->pressed = 0;
    pad->released = 0;
}
