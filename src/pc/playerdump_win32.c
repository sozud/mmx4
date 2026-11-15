#include "common.h"
#include <stdlib.h>

int mmx4_pc_hide_background;

u16 mmx4_pc_player_poke_input(void) { return 0; }

void mmx4_pc_player_dump(long frame)
{
    static int initialized;
    (void)frame;
    if (!initialized) {
        initialized = 1;
        mmx4_pc_hide_background = getenv("MMX4_HIDE_BACKGROUND") != NULL;
    }
}
