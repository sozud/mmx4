#include "common.h"

#include <SDL3/SDL.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct InputEvent {
    unsigned long frame;
    u16 buttons;
};

static struct InputEvent events[256];
static size_t event_count;
static unsigned long frame_number;
static unsigned long max_frames;
static int initialized;

static u16 button_mask(const char* name)
{
    if (!strcmp(name, "start")) return PADstart;
    if (!strcmp(name, "select")) return PADselect;
    if (!strcmp(name, "up")) return PADLup;
    if (!strcmp(name, "down")) return PADLdown;
    if (!strcmp(name, "left")) return PADLleft;
    if (!strcmp(name, "right")) return PADLright;
    if (!strcmp(name, "cross")) return PADRdown;
    if (!strcmp(name, "circle")) return PADRright;
    if (!strcmp(name, "square")) return PADRleft;
    if (!strcmp(name, "triangle")) return PADRup;
    return 0;
}

static void parse_script(void)
{
    const char* script = getenv("MMX4_INPUT_SCRIPT");
    char* copy;
    char* item;

    if (script == NULL || *script == '\0')
        return;
    copy = strdup(script);
    if (copy == NULL)
        abort();
    for (item = strtok(copy, ","); item != NULL && event_count < COUNT(events);
         item = strtok(NULL, ",")) {
        char* colon = strchr(item, ':');
        char* button;
        u16 buttons = 0;

        if (colon == NULL)
            continue;
        *colon = '\0';
        button = colon + 1;
        while (button != NULL) {
            char* plus = strchr(button, '+');
            char* cursor;

            if (plus != NULL)
                *plus = '\0';
            for (cursor = button; *cursor != '\0'; cursor++)
                *cursor = (char)tolower((unsigned char)*cursor);
            buttons |= button_mask(button);
            button = plus == NULL ? NULL : plus + 1;
        }
        events[event_count].frame = strtoul(item, NULL, 0);
        events[event_count].buttons = buttons;
        event_count++;
    }
    free(copy);
}

static u16 scripted_input(void)
{
    size_t i;
    u16 buttons = 0;

    for (i = 0; i < event_count; i++) {
        if (events[i].frame == frame_number)
            buttons |= events[i].buttons;
    }
    return buttons;
}

static u16 keyboard_input(void)
{
    const bool* keys = SDL_GetKeyboardState(NULL);
    u16 buttons = 0;

    if (keys == NULL)
        return 0;
    if (keys[SDL_SCANCODE_RETURN]) buttons |= PADstart;
    if (keys[SDL_SCANCODE_BACKSPACE]) buttons |= PADselect;
    if (keys[SDL_SCANCODE_UP]) buttons |= PADLup;
    if (keys[SDL_SCANCODE_DOWN]) buttons |= PADLdown;
    if (keys[SDL_SCANCODE_LEFT]) buttons |= PADLleft;
    if (keys[SDL_SCANCODE_RIGHT]) buttons |= PADLright;
    if (keys[SDL_SCANCODE_X]) buttons |= PADRdown;
    if (keys[SDL_SCANCODE_C]) buttons |= PADRright;
    if (keys[SDL_SCANCODE_Z]) buttons |= PADRleft;
    if (keys[SDL_SCANCODE_V]) buttons |= PADRup;
    return buttons;
}

void mmx4_pc_input_update(u8* pad_buffer)
{
    u16 buttons;

    if (!initialized) {
        const char* value = getenv("MMX4_MAX_FRAMES");
        parse_script();
        if (value != NULL)
            max_frames = strtoul(value, NULL, 0);
        initialized = 1;
    }
    if (max_frames != 0 && frame_number >= max_frames)
        exit(EXIT_SUCCESS);
    buttons = scripted_input() | keyboard_input();
    pad_buffer[0] = 0;
    pad_buffer[1] = 0x41;
    pad_buffer[2] = (u8)(~buttons >> 8);
    pad_buffer[3] = (u8)~buttons;
    frame_number++;
}

unsigned long mmx4_pc_frame_number(void)
{
    return frame_number;
}
