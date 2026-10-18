#ifndef MAIN_MISC_MISC_19_TITLE_H
#define MAIN_MISC_MISC_19_TITLE_H

struct TitleObjectInit {
    s16 x, y;
    s8 sprite, flags;
};

void title_draw(struct MiscObj* arg0);

#ifdef MMX4_PC
extern void TitleUpdate (struct MiscObj *arg0);
#endif

#endif
