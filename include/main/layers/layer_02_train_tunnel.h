#ifndef MAIN_LAYERS_LAYER_02_TRAIN_TUNNEL_H
#define MAIN_LAYERS_LAYER_02_TRAIN_TUNNEL_H

void train_tunnel_update(struct LayerObj*);

void train_tunnel_section_3(struct LayerObj*);
void train_tunnel_section_4(struct LayerObj*);

void train_tunnel_update_section(struct LayerObj*);

#ifdef MMX4_PC
extern void train_tunnel_accelerate (struct LayerObj *arg0);
#endif

u8 train_tunnel_player_at_lock(struct LayerObj*);

#endif
