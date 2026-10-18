#ifndef MAIN_TILE_EFFECTS_H
#define MAIN_TILE_EFFECTS_H

struct TileEffectRecord {
    u8 layer;
    u8 pad1[3];
    u8 packed_count;
    u8 pad5;
    s16 x, y;
    u16 padA;
    u16* tiles;
    u8 has_next;
};

#endif
