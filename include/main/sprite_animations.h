#ifndef MAIN_SPRITE_ANIMATIONS_H
#define MAIN_SPRITE_ANIMATIONS_H

union PlayerFrameOffsetData {
    s8 components[512];
    struct PlayerFrameOffset offsets[256];
};

extern union PlayerFrameOffsetData D_8011B230;

extern union AnimationStep* D_8011BF40[];
extern union AnimationStep* D_8011C070[9];
extern union AnimationStep* D_8011C094[7];
extern union AnimationStep* D_8011C0E4[3];

extern union AnimationStep* D_8011C018[22];

extern union AnimationStep* D_8011C0C8[7];

#endif
