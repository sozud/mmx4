// EngineObj
// 80020DEC..80021158
#include "common.h"
#include "main/quit_menu.h"
#include "main/102FC.h"
#include "main/10CA4.h"
#include "main/11184.h"
#include "main/11184_dispatch_data.h"
#include "main/2824.h"
#include "main/engine.h"
#include "main/engine_transition_data.h"
#include "main/1A5BC.h"
#include "main/55C4.h"
#include "main/144A4.h"
#include "main/14A60.h"
#include "main/323C.h"
#include "main/E47C.h"
#include "main/E47C_menu_data.h"
#include "main/game_info.h"
#include "main/menu.h"
#include "main/object_update.h"
#include "main/objects.h"
#ifdef MMX4_SATURN
#include "saturn/menu.h"
#include "saturn/player_resources.h"
#endif

extern u8 D_800F2468[];
extern u8 D_800F247C[];
extern u8 D_800F2490[];
extern void (*D_800F2498[])(struct EngineObj*);

void func_80029DBC(void);

void func_80020DEC(u8* arg0, s16 arg1)
{
    struct UnkObj* obj;

    while (arg0[0] != 0xFF) {
        obj = find_free_unk_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 1;
            obj->unk2 = arg0[0];
            obj->y_pos.i.hi = arg0[1];
            obj->unk7 = arg0[2];
        }
        arg0 += 3;
    }

    obj = find_free_unk_obj();
    if (obj != NULL) {
        obj->active = 1;
        obj->id = 0;
        obj->unk2 = -1;
        obj->link.data = D_800F2490;
        obj->x_pos.i.hi = arg1;
    }
}

#ifndef MMX4_SATURN
void func_80020ED4(struct EngineObj* arg0)
{
    arg0->unk7 = 1;
    arg0->character_state.fields.menu_state = 0;
    func_80029DBC();
    main_bss_state.transition.selection = 0;
    func_80020DEC(&D_800F2468, 0x40);
    func_8001E980(0);
    func_800129A4(8);
}

void func_80020F24(struct EngineObj* arg0)
{
    if (main_bss_state.transition.active == 0) {
        if (arg0->character_state.fields.menu_state == 0) {
            func_800204CC((s8*)&main_bss_state.transition.selection, 1);
            if (controller_input.pressed & PAD_CONFIRM) {
                func_8001540C(0, 0x22, 0);
                if (main_bss_state.transition.selection == 0) {
                    func_800129F0(8);
                    arg0->unk7 = 2;
                } else {
                    arg0->character_state.fields.menu_state = 1;
                    func_80029DBC();
#ifdef VERSION_JP
                    main_bss_state.transition.selection = 1;
#else
                    main_bss_state.transition.selection = 0;
#endif
                    func_80020DEC(&D_800F247C, 0x78);
                }
            }
        } else {
            func_800204CC((s8*)&main_bss_state.transition.selection, 1);
            if (controller_input.pressed & PAD_CONFIRM) {
                func_8001540C(0, 0x22, 0);
                arg0->character_state.fields.menu_state = 0;
                if (main_bss_state.transition.selection ==
#ifdef VERSION_JP
                    0
#else
                    1
#endif
                ) {
                    arg0->unk7 = 0;
                    if (engine_obj.stage != 0 && engine_obj.unk5F >= 3) {
                        func_8001C3E8();
                    }
                    SetDispMask(0);
                    func_8001D134();
                    func_80015284();
                    reset_game_engine();
                    func_8001DC30();
                    func_800127FC();
                } else {
                    func_80029DBC();
                    main_bss_state.transition.selection = 0;
                    func_80020DEC(&D_800F2468, 0x40);
                    arg0->unk7 = 1;
                }
            }
        }
    }
}

void func_800210B8(struct EngineObj* arg0)
{
    if (main_bss_state.transition.active == 0) {
        arg0->unk6++;
        func_80029DBC();
        arg0->unk7 = 0;
        arg0->character_state.fields.menu_state = 0;
    }
}

void func_80021104(struct EngineObj* arg0)
{
    D_800F2498[arg0->unk7](arg0);
    update_unk_objects();
    func_80016124();
    func_80025CDC();
}
#endif
