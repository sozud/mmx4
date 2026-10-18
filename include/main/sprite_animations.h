#ifndef MAIN_SPRITE_ANIMATIONS_H
#define MAIN_SPRITE_ANIMATIONS_H

union PlayerFrameOffsetData {
    struct PlayerFrameOffset offsets[256];
    s8 components[512];
};

extern union PlayerFrameOffsetData D_8011B230;

extern u32* D_8011BF40[];
extern u32* D_8011C070[9];
extern u32* D_8011C094[7];
extern u32* D_8011C0E4[3];

extern u32* D_8011C018[22];

extern u32* D_8011C0C8[7];

#endif
