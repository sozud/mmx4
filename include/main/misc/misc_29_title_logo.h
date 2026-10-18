#ifndef MAIN_MISC_MISC_29_TITLE_LOGO_H
#define MAIN_MISC_MISC_29_TITLE_LOGO_H

void title_logo_init(struct MiscObj* arg0);
void title_logo_star_delay(struct MiscObj* arg0);
void title_logo_star_fly(struct MiscObj* arg0);
void title_logo_star_hold(struct MiscObj* arg0);
void title_logo_trail_fade(struct MiscObj* arg0);

#ifdef MMX4_PC
extern void TitleLogoUpdate (struct MiscObj *arg0);
#endif

#endif
