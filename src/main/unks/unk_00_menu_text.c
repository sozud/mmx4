// UnkObj, unk_object_update_funcs[0]
// 800D3928..800D3964
#include "common.h"

void menu_text_update(struct UnkObj* arg0)
{
    arg0->on_screen = 0;
    menu_text_state_funcs[arg0->state](arg0);
}

void (*menu_text_state_funcs[4])(struct UnkObj*) = {
    menu_text_init,
    menu_text_highlight,
    func_800D3798,
    menu_text_cursor,
};
