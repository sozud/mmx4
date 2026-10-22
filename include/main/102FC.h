#ifndef MAIN_102FC_H
#define MAIN_102FC_H

// D_800F23E8 engine_update_funcs
void engine_state_0(struct EngineObj* arg0);

void engine_state_2(struct EngineObj* arg0);

void engine_state_4(struct EngineObj* arg0);
void func_8001FC20(struct EngineObj* arg0);
void engine_state_6(struct EngineObj* arg0);
void func_8001FAFC(struct EngineObj* arg0);

void func_80020464(struct EngineObj* arg0);

void func_8001FF8C(struct EngineObj*);
void func_80020060(struct EngineObj*);
void func_80020368(struct EngineObj*);

#ifdef MMX4_PC
extern s32 func_8001FD7C (struct EngineObj *arg0);

extern void func_80020390 (struct EngineObj *arg0);
extern void func_8002044C (struct EngineObj *arg0);
#endif

extern void (*engine_update_funcs[])(struct EngineObj*);

void func_8001FB50(void);

extern u8 pad_port1_packet[0x22];

void func_8001FDBC(void);
void func_8001FEC0(void);

#endif
