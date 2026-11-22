#include "common.h"
#include "main/shots/eregion_fireball_data.h"
#include "main/shots/shot_02_gunner_shot.h"

u8 eregion_fireball_hit_box[4] = { 0xF7, 0xF5, 0x12, 0x13 };

u8 eregion_fireball_explode_box[4] = { 0xF6, 0xE5, 0x12, 0x1D };

u8 eregion_fireball_terrain_box[4] = { 0, 0xFE, 8, 7 };

#ifdef VERSION_DEMO
void func_8008A660_demo(struct ShotObj*);
void func_8008A82C_demo(struct ShotObj*);
void func_8008AA74_demo(struct ShotObj*);
void func_8008A994_demo(struct ShotObj*);
void func_8008AA94_demo(struct ShotObj*);

void (*eregion_fireball_state_funcs[])(struct ShotObj*) = {
    func_8008A660_demo,
    func_8008A82C_demo,
    func_8008AA74_demo,
    func_8008A994_demo,
    func_8008AA94_demo,
};

u8 eregion_fireball_debris[2][4] = { { 1, 2, 3, 4 }, { 1, 2, 3, 4 } };
#else
u8 eregion_fireball_debris[2][4] = { { 1, 2, 3, 4 }, { 1, 2, 3, 4 } };

void (*eregion_fireball_state_funcs[])(struct ShotObj*) = {
    func_80099F48,
    func_8009A10C,
    eregion_fireball_despawn,
    eregion_fireball_explode,
};
#endif
