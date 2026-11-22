#ifndef MAIN_10CA4_H
#define MAIN_10CA4_H

void func_800204AC(struct EngineObj* arg0);

void func_80020580(struct EngineObj*);
void func_80020638(struct EngineObj*);
void func_800206D0(struct EngineObj*);
void func_80020808(struct EngineObj*);
void func_8002088C(struct EngineObj*);

#ifdef MMX4_PC
extern void func_800204A4(void);
#endif

void func_800204CC(s8*, u32);

#ifdef VERSION_DEMO
void func_800311E4_demo(s8 selection, s8 menu);

#define DEMO_MENU_SELECT(engine, count, menu)                      \
    if (main_bss_state.transition.active == 0) {                   \
        func_800204CC(&(engine)->unk2, count);                     \
        if (controller_input.pressed & (PAD_CONFIRM | PADstart)) { \
            func_800129F0(8);                                      \
            (engine)->unk1++;                                      \
        }                                                          \
        func_800311E4_demo((engine)->unk2, menu);                  \
    }
#endif

#endif
