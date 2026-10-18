#ifndef MAIN_MISC_MISC_52_NPC_CUTSCENE_H
#define MAIN_MISC_MISC_52_NPC_CUTSCENE_H

void npc_cutscene_update(struct MiscObj* arg0);

void npc_cutscene_talk_wait_player(struct MiscObj*);
void npc_cutscene_talk_line(struct MiscObj*);
void npc_cutscene_talk_wait_line(struct MiscObj*);

void npc_cutscene_fade_out(struct MiscObj*);

void npc_cutscene_finish_wait(struct MiscObj*);

#endif
