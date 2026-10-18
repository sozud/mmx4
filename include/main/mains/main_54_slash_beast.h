#ifndef MAIN_MAINS_MAIN_54_SLASH_BEAST_H
#define MAIN_MAINS_MAIN_54_SLASH_BEAST_H

void slash_beast_update(struct MainObj* arg0);

void func_8006BB70(struct MainObj*);
void func_8006BD1C(struct MainObj*);

// slash_beast_step_funcs
extern void (*slash_beast_step_funcs[])(struct MainObj*);

void func_8006CDD4(struct MainObj*);

void func_8006D3DC(struct MainObj*);

void slash_beast_death_blink(struct MainObj*);

void func_8006C378(struct MainObj*);

void func_8006C6AC(struct MainObj*);

void func_8006CB50(struct MainObj*);
void func_8006CC3C(struct MainObj*);

void func_8006D280(struct MainObj*);

void slash_beast_intro_wait_player(struct MainObj*);
void slash_beast_intro_wait_warning(struct MainObj*);
void func_8006DD44(struct MainObj*);

void func_8006E450(struct MainObj*);

void slash_beast_pick_pattern(struct MainObj*);

extern union AnimationStep D_801001F8[];
extern union AnimationStep D_801001FC[];

extern struct Unk_unk68 D_8010024C;

extern struct Unk_unk68 D_80100208;
extern struct Unk_unk68 D_8010020C;

void slash_beast_face_player(struct MainObj*);

#endif
