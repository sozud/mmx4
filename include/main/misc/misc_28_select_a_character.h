#ifndef MAIN_MISC_MISC_28_SELECT_A_CHARACTER_H
#define MAIN_MISC_MISC_28_SELECT_A_CHARACTER_H

struct CharacterSelectPosition {
    s16 x, y;
};

void select_char_portrait_bounce(struct MiscObj* arg0);

// select_char_scroll_text_funcs
void select_char_scroll_text_init(struct MiscObj* arg0);
void select_char_scroll_text_move(struct MiscObj* arg0);

void select_char_character_shoot(struct MiscObj* arg0);

void select_char_shot_burst(struct MiscObj* arg0);
void select_char_shot_burst(struct MiscObj* arg0);

// D_8010EBF4
void select_char_init(struct MiscObj* arg0);

#ifdef MMX4_PC
extern void SelectACharacterUpdate (struct MiscObj *arg0);
#endif

extern u32* select_char_x_animations[7];
extern u32* select_char_zero_animations[6];
extern u32* select_char_menu_animations[10];
extern u8 select_char_initial_animations[16];

extern u8 select_char_priorities[16];
extern struct CharacterSelectPosition select_char_positions[9];
extern struct CharacterSelectPosition select_char_text_positions[3];

#endif
