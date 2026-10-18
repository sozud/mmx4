#ifndef MAIN_QUADS_QUAD_05_WEB_PIECE_QUAD_H
#define MAIN_QUADS_QUAD_05_WEB_PIECE_QUAD_H

void web_piece_quad_update(struct QuadObj* arg0);

void web_piece_quad_main(struct QuadObj*);

s32 web_piece_quad_is_visible(struct QuadObj*);

extern s32* web_piece_quad_frame_table[8];

#endif
