#ifndef GC_DOLPHIN_H
#define GC_DOLPHIN_H

typedef struct {
    unsigned long dummy[3];
} GXTlutObj;

typedef struct {
    unsigned long dummy[8];
} GXTexObj;

#define GX_QUADS 0x80
#define GX_TRIANGLES 0x90
#define GX_LINES 0xA8

typedef enum {
    GX_TL_IA8,
    GX_TL_RGB565,
    GX_TL_RGB5A3
} GXTlutFmt;

typedef struct DVDFileInfo DVDFileInfo;
typedef void (*DVDCallback)(long result, DVDFileInfo* fileInfo);

struct DVDFileInfo {
    unsigned char cb[0x30];
    unsigned long startAddr;
    unsigned long length;
    DVDCallback callback;
};

#define OSRoundUp32B(x) (((unsigned long)(x) + 31) & ~31)

typedef union {
    unsigned char u8;
    signed char s8;
    unsigned short u16;
    short s16;
    unsigned long u32;
    long s32;
    float f32;
} PPCWGPipe;

#define GXWGFifo (*(volatile PPCWGPipe*)0xCC008000)

static inline void GXPosition3s16(short x, short y, short z)
{
    GXWGFifo.s16 = x;
    GXWGFifo.s16 = y;
    GXWGFifo.s16 = z;
}

static inline void GXColor3u8(unsigned char r, unsigned char g, unsigned char b)
{
    GXWGFifo.u8 = r;
    GXWGFifo.u8 = g;
    GXWGFifo.u8 = b;
}

static inline void GXTexCoord2u16(unsigned short s, unsigned short t)
{
    GXWGFifo.u16 = s;
    GXWGFifo.u16 = t;
}

void OSReport(const char* msg, ...);
void OSPanic(const char* file, int line, const char* msg, ...);
int DVDOpen(const char* fileName, DVDFileInfo* fileInfo);
int DVDClose(DVDFileInfo* fileInfo);
int DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, long length, long offset, DVDCallback callback, long prio);
void DCFlushRangeNoSync(void* addr, unsigned long nbytes);
void GXInitTlutObj(GXTlutObj* tlut_obj, void* lut, GXTlutFmt fmt, unsigned short n_entries);
void GXSetScissor(unsigned long left, unsigned long top, unsigned long wd, unsigned long ht);
void GXSetNumChans(unsigned char nChans);
void GXSetTexCoordGen2(int dst_coord, int func, int src_param, unsigned long mtx, int normalize, unsigned long pt_texmtx);
void GXSetNumTexGens(unsigned char nTexGens);
void GXSetChanCtrl(int chan, int enable, int amb_src, int mat_src, unsigned long light_mask, int diff_fn, int attn_fn);
void GXSetNumTevStages(unsigned char nStages);
void GXSetTevOrder(int stage, int coord, unsigned long map, int color);
void GXSetTevOp(int id, int mode);
void GXSetBlendMode(int type, int src_factor, int dst_factor, int op);
void GXClearVtxDesc(void);
void GXSetVtxDesc(int attr, int type);
void GXSetVtxAttrFmt(int vtxfmt, int attr, int cnt, int type, unsigned char frac);
void GXLoadTlut(GXTlutObj* tlut_obj, unsigned long tlut_name);
void GXLoadTexObj(GXTexObj* obj, int id);
void GXBegin(int type, int vtxfmt, unsigned short nverts);
void GXSetTevColorIn(int stage, int a, int b, int c, int d);
void GXSetTevAlphaIn(int stage, int a, int b, int c, int d);
void GXSetTevColorOp(int stage, int op, int bias, int scale, int clamp, int out_reg);
void GXSetTevAlphaOp(int stage, int op, int bias, int scale, int clamp, int out_reg);
void fn_800763F0(int stage, int sel);
void GXSetColorUpdate(int update_enable);
void GXSetAlphaUpdate(int update_enable);
void GXSetZMode(int compare_enable, int func, int update_enable);
void GXSetZCompLoc(int before_tex);
void GXSetAlphaCompare(int comp0, unsigned char ref0, int op, int comp1, unsigned char ref1);
void GXSetProjection(float mtx[4][4], int type);
void GXLoadPosMtxImm(float mtx[3][4], unsigned long id);
void GXGetScissor(unsigned long* left, unsigned long* top, unsigned long* wd, unsigned long* ht);
void GXSetClipMode(int mode);
void fn_80073FAC(int arg);
void fn_800739C0(void);
void PSMTXIdentity(float m[3][4]);
void C_MTXOrtho(float m[4][4], float t, float b, float l, float r, float n, float f);

#endif
