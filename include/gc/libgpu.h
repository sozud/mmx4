#ifndef GC_LIBGPU_H
#define GC_LIBGPU_H

typedef struct {
    short x, y;
    short w, h;
} RECT;

typedef struct {
    unsigned long tag;
    unsigned char pad[3];
    unsigned char code;
    RECT clip;
    unsigned short ofs[2];
    RECT tw;
    unsigned short tpage;
} DR_ENV;

typedef struct {
    RECT clip;
    short ofs[2];
    RECT tw;
    unsigned short tpage;
    unsigned char dtd;
    unsigned char dfe;
    unsigned char isbg;
    unsigned char r0, g0, b0;
    DR_ENV dr_env;
} DRAWENV;

typedef struct {
    RECT disp;
    RECT screen;
    unsigned char isinter;
    unsigned char isrgb24;
    unsigned char pad0, pad1;
} DISPENV;

typedef struct {
    unsigned long tag;
    unsigned short tpage;
    unsigned char mode;
    unsigned char code;
    RECT* tw;
} DR_MODE;

typedef struct {
    unsigned long tag;
    unsigned short tpage;
    unsigned char pad;
    unsigned char code;
} DR_TPAGE;

typedef struct {
    unsigned long tag;
    unsigned char pad[3];
    unsigned char code;
    RECT area;
} DR_AREA;

typedef struct {
    unsigned long tag;
    unsigned char pad[3];
    unsigned char code;
    unsigned short x, y;
} DR_OFFSET;

typedef struct {
    unsigned long tag;
    unsigned char r0, g0, b0, code;
    short x0, y0;
    unsigned char u0, v0;
    unsigned short clut;
    short w, h;
} SPRT;

typedef struct {
    unsigned long tag;
    unsigned char r0, g0, b0, code;
    short x0, y0;
    short x1, y1;
    short x2, y2;
} POLY_F3;

typedef struct {
    unsigned long tag;
    unsigned char r0, g0, b0, code;
    short x0, y0;
    short x1, y1;
    short x2, y2;
    short x3, y3;
} POLY_F4;

typedef struct {
    unsigned long tag;
    unsigned char r0, g0, b0, code;
    short x0, y0;
    unsigned char r1, g1, b1, pad1;
    short x1, y1;
    unsigned char r2, g2, b2, pad2;
    short x2, y2;
    unsigned char r3, g3, b3, pad3;
    short x3, y3;
} POLY_G4;

typedef struct {
    unsigned long tag;
    unsigned char r0, g0, b0, code;
    short x0, y0;
    short x1, y1;
} LINE_F2;

typedef struct {
    unsigned long tag;
    unsigned char r0, g0, b0, code;
    short x0, y0;
    short x1, y1;
    short x2, y2;
    short x3, y3;
    unsigned long pad;
} LINE_F4;

typedef struct {
    unsigned long tag;
    unsigned char r0, g0, b0, code;
    short x0, y0;
    unsigned char u0, v0;
    unsigned short clut;
} SPRT_8;

typedef SPRT_8 SPRT_16;

typedef struct {
    unsigned long tag;
    unsigned char r0, g0, b0, code;
    short x0, y0;
    short w, h;
} TILE;

typedef struct {
    unsigned long tag;
    unsigned char r0, g0, b0, code;
    short x0, y0;
    unsigned char u0, v0;
    unsigned short clut;
    short x1, y1;
    unsigned char u1, v1;
    unsigned short tpage;
    short x2, y2;
    unsigned char u2, v2;
    unsigned short pad1;
} POLY_FT3;

typedef struct {
    unsigned long tag;
    unsigned char r0, g0, b0, code;
    short x0, y0;
    unsigned char u0, v0;
    unsigned short clut;
    short x1, y1;
    unsigned char u1, v1;
    unsigned short tpage;
    short x2, y2;
    unsigned char u2, v2;
    unsigned short pad1;
    short x3, y3;
    unsigned char u3, v3;
    unsigned short pad2;
} POLY_FT4;

#define GC_PRIM_ENABLED 1

DISPENV* SetDefDispEnv(DISPENV* env, int x, int y, int w, int h);
DRAWENV* SetDefDrawEnv(DRAWENV* env, int x, int y, int w, int h);
void SetDispMask(int mask);
int DrawSync(int mode);
int LoadImage(RECT* rect, unsigned long* p);
int MoveImage(RECT* rect, int x, int y);
int ClearImage(RECT* rect, unsigned char r, unsigned char g, unsigned char b);
unsigned long* ClearOTagR(unsigned long* ot, int n);
unsigned short GetTPage(int tp, int abr, int x, int y);
void SetDrawMode(DR_MODE* p, int dfe, int dtd, int tpage, RECT* tw);
void SetDrawTPage(DR_TPAGE* p, int dfe, int dtd, int tpage);

#endif
