#ifndef MAIN_MAINS_MAIN_62_FLAME_JET_H
#define MAIN_MAINS_MAIN_62_FLAME_JET_H

void flame_jet_update(struct MainObj *arg0);

void func_8007B90C(struct MainObj*);
void flame_jet_wait_sync(struct MainObj*);

u8 func_8007BABC(struct MainObj*);

void func_8007BE40(struct MainObj*);

void flame_jet_main(struct MainObj*);

extern struct Unk_unk68 flame_jet_vent_box;
extern struct Unk_unk68* flame_jet_hurt_boxes[9];
extern struct Unk_unk68* flame_jet_attack_boxes[9];

#endif
