#ifndef MAIN_MAINS_MAIN_31_THORN_TRAP_H
#define MAIN_MAINS_MAIN_31_THORN_TRAP_H

void thorn_trap_update(struct MainObj* arg0);

// thorn_trap_state_funcs
void func_8005B8D0(struct MainObj*);
void func_8005C0E4(struct MainObj*);
void func_8005C474(struct MainObj*);

void func_8005BA2C(struct MainObj* arg0);
void thorn_trap_open(struct MainObj* arg0);

void func_8005BDE4(struct MainObj* arg0);

void func_8005BFC0(struct MainObj* arg0);

extern struct Unk_unk68 thorn_trap_attack_box[];

extern u8 D_800FDC28[];
extern u8 D_800FDC30[];
extern u8 D_800FDC34[];
extern u8 D_800FDC38[];
extern u8 D_800FDC3C[];
extern struct Unk_unk68 D_800FDA0C[];

extern void (*thorn_trap_step_funcs[10])();

#endif
