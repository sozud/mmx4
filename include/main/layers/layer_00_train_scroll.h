#ifndef MAIN_LAYERS_LAYER_00_TRAIN_SCROLL_H
#define MAIN_LAYERS_LAYER_00_TRAIN_SCROLL_H

void train_scroll_update(struct LayerObj*);


// train_scroll_state_funcs
extern void (*train_scroll_state_funcs[])(struct LayerObj*);
void train_scroll_init(struct LayerObj*);
void train_scroll_main(struct LayerObj*);
void train_scroll_despawn(struct LayerObj*);

// train_scroll_section_funcs
extern void (*train_scroll_section_funcs[])(struct LayerObj*);
void train_scroll_section_0(struct LayerObj*);
void train_scroll_section_1(struct LayerObj*);
void train_scroll_section_2(struct LayerObj*);
void train_scroll_section_3(struct LayerObj*);
void train_scroll_section_4(struct LayerObj*);
void train_scroll_section_5(struct LayerObj*);

// train_scroll_event_funcs
extern void (*train_scroll_event_funcs[])(struct LayerObj*);
void train_scroll_spawn_trooper(struct LayerObj*);
void train_scroll_spawn_crusher(struct LayerObj*);
void train_scroll_open_tiles(struct LayerObj*);

#ifdef MMX4_PC
extern void train_scroll_update (struct LayerObj *arg0);
extern void train_scroll_main (struct LayerObj *arg0);
extern void train_scroll_despawn (struct LayerObj *arg0);
extern void train_scroll_section_0 (struct LayerObj *arg0);
extern void train_scroll_section_0_wait (struct LayerObj *arg0);
extern void train_scroll_section_0_skip (struct LayerObj *arg0);
extern void train_scroll_section_1 (struct LayerObj *arg0);
extern void train_scroll_section_1_lock (struct LayerObj *arg0);
extern void train_scroll_section_1_event (struct LayerObj *arg0);
extern void train_scroll_section_2 (struct LayerObj *arg0);
extern void train_scroll_section_2_lock (struct LayerObj *arg0);
extern void train_scroll_section_2_event (struct LayerObj *arg0);
extern void train_scroll_section_3 (struct LayerObj *arg0);
extern void train_scroll_section_3_lock (struct LayerObj *arg0);
extern void train_scroll_section_3_event (struct LayerObj *arg0);
extern void train_scroll_section_4 (struct LayerObj *arg0);
extern void train_scroll_section_4_lock (struct LayerObj *arg0);
extern void train_scroll_section_4_event (struct LayerObj *arg0);
extern void train_scroll_section_5 (struct LayerObj *arg0);
extern void train_scroll_spawn_trooper (struct LayerObj *arg0);
extern void train_scroll_spawn_crusher (struct LayerObj *arg0);
extern void train_scroll_open_tiles (struct LayerObj *arg0);
extern void train_scroll_shake (struct LayerObj *arg0);
#endif

u8 train_scroll_player_at_lock(struct LayerObj*);

#endif
