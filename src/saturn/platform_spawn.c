#include "common.h"
#include "saturn/platform.h"

#define SPAWN_LIST_END 0xFF
#define SPAWN_CONTROLLER_STATE 0xFF
#define SPAWN_CALLBACK 80
#define SPAWN_ARGUMENT 8
#define SPAWN_X 12
#define SPAWN_KIND 2
#define SPAWN_PARAM 7

struct UnkObj* find_free_unk_obj(void);

u8 saturn_spawn_controller_script[] = {
    0x70,
    0x00,
    0x90,
    0x01,
    0xFF,
    0x00,
    0x00,
    0x00,
};

void saturn_spawn_tile_objects(u8* list, s16 argument)
{
    u8* object;
    for (; *list != SPAWN_LIST_END; list += 3) {
        object = (u8*)find_free_unk_obj();
        if (object != NULL) {
            object[0] = 1;
            object[1] = 1;
            object[SPAWN_KIND] = list[0];
            *(u16*)(object + SPAWN_X) = list[1];
            object[SPAWN_PARAM] = list[2];
        }
    }
    object = (u8*)find_free_unk_obj();
    if (object != NULL) {
        object[0] = 1;
        object[1] = 0;
        object[SPAWN_KIND] = SPAWN_CONTROLLER_STATE;
        *(u8**)(object + SPAWN_CALLBACK) = saturn_spawn_controller_script;
        *(s16*)(object + SPAWN_ARGUMENT) = argument;
    }
}
