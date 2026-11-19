#include "gc/assert.h"
#include "gc/collection.h"
#include "gc/dolphin.h"
#include "gc/libgpu.h"

struct GpuDrawState {
    short ofs[2];
    RECT tw;
    unsigned char page;
    unsigned char tp;
    unsigned char abr;
};

struct PrimCacheNode {
    struct PrimCacheNode* next;
    void* prim;
    short a;
    unsigned short state;
};

struct SemiNode {
    void* prim;
    short a;
    unsigned short state;
};

#define NUM_SEMI_PRIMS 1000
#define NUM_CACHE_NODES 3500
#define NUM_CACHE_LISTS 5
#define NUM_TEXTURE_PAGES 64
#define NUM_CLUT_SLOTS 256
#define NUM_DRAW_STATES 16

#define VRAM_PAGE_SIZE (64 * 256)
#define NUM_TLUTS 256

static int disp_mask;
static unsigned short (*convert_color)(unsigned short color);
static struct GpuDrawState* draw_state;
static struct GpuDrawState draw_states[NUM_DRAW_STATES];
static struct SemiNode* semi_next;
static struct SemiNode semi_list[NUM_SEMI_PRIMS];
static struct PrimCacheNode* cache_lists[NUM_CACHE_LISTS];
static struct PrimCacheNode* texture_lists[NUM_TEXTURE_PAGES][2][NUM_CLUT_SLOTS];
static struct PrimCacheNode* cache_next;
static struct PrimCacheNode cache_nodes[NUM_CACHE_NODES];

static unsigned short clut_slots[0x10000];
static GXTlutObj* tlut_next;
static unsigned short* tlut_data_next;
static GXTlutObj tluts[NUM_TLUTS];
static unsigned short tlut_data[NUM_TLUTS * 16];
static unsigned short* vram;
static unsigned short* texture_4bit;
static unsigned short* texture_16bit;

static void cache_push(struct PrimCacheNode** list, void* prim, short a, unsigned short state)
{
    cache_next->next = *list;
    cache_next->prim = prim;
    cache_next->a = a;
    cache_next->state = state;
    *list = cache_next;
    cache_next++;
}

unsigned short gc_clut_slot(unsigned short clut, unsigned short tp);

static unsigned short tpage_index(unsigned short tpage)
{
    short x = (tpage & 0xF) << 6;
    short y = ((tpage << 4) & 0x100) + ((tpage >> 2) & 0x200);

    return x / 64 + (y / 256) * 16;
}

int gc_intersect_rect(RECT* a, RECT* b, RECT* out);
void gc_load_page_rect(int page, RECT* part, unsigned long* p, RECT* rect, short x, short y);

void gc_fill_page_rect(int page, RECT* part, unsigned char r, unsigned char g, unsigned char b);

#define NUM_VRAM_PAGES 32

static int split_by_page(RECT* rect, RECT* parts, unsigned short* pages)
{
    unsigned short page;
    int n = 0;

    for (page = 0; page < NUM_VRAM_PAGES; page++) {
        RECT area;

        area.x = (page % 16) * 64;
        area.y = (page / 16) * 256;
        area.w = 64;
        area.h = 256;
        if (gc_intersect_rect(rect, &area, &parts[n])) {
            pages[n] = page;
            parts[n].x -= area.x;
            parts[n].y -= area.y;
            n++;
        }
    }
    return n;
}

int LoadImage(RECT* rect, unsigned long* p)
{
    RECT parts[NUM_VRAM_PAGES];
    unsigned short pages[NUM_VRAM_PAGES];
    unsigned short page;
    int n = split_by_page(rect, parts, pages);
    int i;

    for (i = 0; i < n; i++) {
        page = pages[i];
        gc_load_page_rect(page, &parts[i], p, rect, parts[i].x + (page % 16) * 64 - rect->x,
            parts[i].y + (page / 16) * 256 - rect->y);
    }
    return 0;
}

int ClearImage(RECT* rect, unsigned char r, unsigned char g, unsigned char b)
{
    RECT parts[NUM_VRAM_PAGES];
    unsigned short pages[NUM_VRAM_PAGES];
    int n = split_by_page(rect, parts, pages);
    int i;

    for (i = 0; i < n; i++) {
        gc_fill_page_rect(pages[i], &parts[i], r, g, b);
    }
    return 0;
}

int DrawSync(int mode)
{
    return 0;
}

int ResetGraph(int mode)
{
    return 0;
}

DISPENV* SetDefDispEnv(DISPENV* env, int x, int y, int w, int h)
{
    env->disp.x = x;
    env->disp.y = y;
    env->disp.w = w;
    env->disp.h = h;
    env->screen.x = 0;
    env->screen.y = 0;
    env->screen.w = 0;
    env->screen.h = 0;
    env->isinter = 0;
    env->isrgb24 = 0;
    return env;
}

DISPENV* PutDispEnv(DISPENV* env)
{
    return env;
}

DRAWENV* SetDefDrawEnv(DRAWENV* env, int x, int y, int w, int h)
{
    env->clip.x = x;
    env->clip.y = y;
    env->clip.w = w;
    env->clip.h = h;
    env->ofs[0] = x;
    env->ofs[1] = y;
    env->tw.x = 0;
    env->tw.y = 0;
    env->tw.w = 0;
    env->tw.h = 0;
    env->tpage = 10;
    env->dtd = 1;
    env->dfe = 1;
    env->isbg = 0;
    env->r0 = 0;
    env->g0 = 0;
    env->b0 = 0;
    return env;
}

DRAWENV* PutDrawEnv(DRAWENV* env)
{
    return env;
}

void SetDispMask(int mask)
{
    disp_mask = mask;
}

unsigned short GetTPage(int tp, int abr, int x, int y)
{
    return ((tp & 3) << 7) | ((abr & 3) << 5) | ((y & 0x100) >> 4) | ((x & 0x3FF) >> 6) | ((y & 0x200) << 2);
}

void SetDrawMode(DR_MODE* p, int dfe, int dtd, int tpage, RECT* tw)
{
    p->code = 0x80;
    p->tpage = tpage;
    p->mode = (dtd << 4) | dfe;
    p->tw = tw;
    p->tag |= GC_PRIM_ENABLED;
}

void SetDrawTPage(DR_TPAGE* p, int dfe, int dtd, int tpage)
{
    p->tag |= GC_PRIM_ENABLED;
    p->code = 0xC0;
    p->tpage = tpage;
}

unsigned long* ClearOTagR(unsigned long* ot, int n)
{
    unsigned long* p;

    for (p = ot + n - 1; p != ot; p--) {
        *p = (unsigned long)(p - 1);
    }
    *ot = 0;
    return 0;
}

void addSemiPrimitiveCache(unsigned long* ot);

void DrawOTag(unsigned long* ot)
{
    addSemiPrimitiveCache(ot);
}

static void (*dr_exec_funcs[5])();
static void (*dr_flush_funcs[5])();
static void (*queue_funcs[32])(void* prim, short a, unsigned short state);
static unsigned short ortho_width;
static unsigned short ortho_height;
void drawPrimitiveCache(void);
void drawSemiTransPrimitive(void* prim, short a, unsigned short state);

static void clearPrimitiveCache(void)
{
    int page;
    int kind;
    int slot;
    int i;

    for (page = 0; page < NUM_TEXTURE_PAGES; page++) {
        for (kind = 0; kind < 2; kind++) {
            for (slot = 0; slot < NUM_CLUT_SLOTS; slot++) {
                texture_lists[page][kind][slot] = 0;
            }
        }
    }
    for (i = 0; i < NUM_CACHE_LISTS; i++) {
        cache_lists[i] = 0;
    }
}

static void clearSemiPrimitiveCache(void)
{
    int i;

    for (i = 0; i < NUM_SEMI_PRIMS; i++) {
        semi_list[i].prim = 0;
    }
    semi_next = semi_list;
}

static void drawSemiPrimitiveCache(void)
{
    struct SemiNode* s;
    int i;

    GXSetZMode(1, 1, 0);
    for (i = 0, s = semi_list; i < NUM_SEMI_PRIMS; i++, s++) {
        if (s->prim == 0) {
            return;
        }
        drawSemiTransPrimitive(s->prim, s->a, s->state);
    }
    OSPanic("gcGPU.c", 0xACE, "[fatal] Overflow Semi primitive buffer in gcGPU.c\n");
}

static void clearDepth(void)
{
    GXSetColorUpdate(0);
    GXSetAlphaUpdate(0);
    GXSetZMode(1, 7, 1);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(11, 1);
    GXSetVtxAttrFmt(0, 11, 0, 1, 0);
    GXSetVtxAttrFmt(0, 9, 1, 3, 0);
    GXBegin(GX_QUADS, 0, 4);
    GXPosition3s16(0, 0, -29990);
    GXColor3u8(0, 0, 0);
    GXPosition3s16(640, 0, -29990);
    GXColor3u8(0, 0, 0);
    GXPosition3s16(640, 480, -29990);
    GXColor3u8(0, 0, 0);
    GXPosition3s16(0, 480, -29990);
    GXColor3u8(0, 0, 0);
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(1);
    GXSetZMode(1, 1, 1);
}

static void flushPrimitiveCache(void)
{
    drawPrimitiveCache();
    clearPrimitiveCache();
    drawSemiPrimitiveCache();
    clearSemiPrimitiveCache();
    clearDepth();
}

#line 2717
void addSemiPrimitiveCache(unsigned long* ot)
{
    float mtx[3][4];
    float proj[4][4];
    unsigned long sx, sy, sw, sh;
    unsigned long* prim = ot;
    int a = -29900;
    int state = 0;
    unsigned char code;
    int idx;
    struct GpuDrawState* next;
    void (*queue)(void* prim, short a, unsigned short state);

    if (disp_mask == 0) {
        return;
    }
    gc_memset(clut_slots, 0xFFFF, sizeof(clut_slots));
    tlut_data_next = tlut_data;
    tlut_next = tluts;
    PSMTXIdentity(mtx);
    GXLoadPosMtxImm(mtx, 0);
    fn_80073FAC(0);
    GXSetClipMode(0);
    GXSetNumChans(1);
    GXSetTexCoordGen2(0, 1, 4, 0x3C, 0, 0x7D);
    GXSetNumTexGens(1);
    GXSetChanCtrl(0, 1, 1, 1, 0, 0, 2);
    GXSetChanCtrl(2, 1, 1, 1, 0, 0, 2);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevOp(0, 0);
    GXSetBlendMode(1, 4, 5, 0);
    draw_state = draw_states;
    draw_state->ofs[0] = 0;
    draw_state->ofs[1] = 0;
    draw_state->tw.x = 0;
    draw_state->tw.y = 0;
    draw_state->tw.w = 0;
    draw_state->tw.h = 0;
    draw_state->page = 10;
    draw_state->tp = 0;
    draw_state->abr = 0;
    cache_next = cache_nodes;
    clearPrimitiveCache();
    clearSemiPrimitiveCache();
    GXGetScissor(&sx, &sy, &sw, &sh);
    fn_80073FAC(0);
    C_MTXOrtho(proj, 0.0f, ortho_height, 0.0f, ortho_width, 1.0f, 30000.0f);
    GXSetProjection(proj, 1);
    GXSetZMode(1, 1, 1);
    GXSetZCompLoc(0);
    GXSetAlphaCompare(5, 0, 0, 7, 0);
    fn_800739C0();
    while (prim != 0) {
        if (*prim & GC_PRIM_ENABLED) {
            code = ((unsigned char*)prim)[7] >> 2;
            if (code & 0xE0) {
                idx = (code >> 2) & 7;
                dr_flush_funcs[idx](prim);
                next = draw_state + 1;
                gc_memcpy(next, draw_state, sizeof(*draw_state));
                draw_state = next;
                dr_exec_funcs[idx](prim);
                state++;
            } else {
                queue = queue_funcs[code];
                if (queue != 0) {
                    if (!(((unsigned char*)prim)[7] & 2)) {
                        queue(prim, a, state);
                    } else {
                        assert(prim);
                        semi_next->prim = prim;
                        semi_next->a = a;
                        semi_next->state = state;
                        semi_next++;
                    }
                    if (((unsigned char*)prim)[7] & 1) {
                        ((unsigned char*)prim)[4] = ((unsigned char*)prim)[6] = ((unsigned char*)prim)[5] = 0xFF;
                    }
                    a++;
                }
            }
        } else {
            a++;
        }
        prim = (unsigned long*)(*prim & ~GC_PRIM_ENABLED);
    }
    DCFlushRange(tlut_data, tlut_data_next - tlut_data);
    drawPrimitiveCache();
    drawSemiPrimitiveCache();
    GXSetScissor(sx, sy, sw, sh);
    clearDepth();
}

void gc_set_primitive_enabled(unsigned long* tag, unsigned char enabled)
{
    if (enabled) {
        *tag |= GC_PRIM_ENABLED;
    } else {
        *tag &= ~GC_PRIM_ENABLED;
    }
}

void gc_set_primitive_next(unsigned long* tag, unsigned long next)
{
    if (((unsigned long)tag & 0xFFFFFF00) == 0) {
        OSReport("error prim\n");
    } else {
        *tag = (*tag & GC_PRIM_ENABLED) | next;
    }
}

unsigned long gc_get_primitive_next(unsigned long* tag)
{
    return *tag & ~GC_PRIM_ENABLED;
}

int MoveImage(RECT* rect, int x, int y)
{
    short dx = x;
    short dy = y;
    unsigned short src_page = rect->x / 64 + (rect->y / 256) * 16;
    unsigned short dst_page = dx / 64 + (dy / 256) * 16;
    short src_x = rect->x % 64;
    short src_y = rect->y % 256;
    short dst_x = dx % 64;
    short dst_y = dy % 256;
    int src = src_x + src_y * 64;
    int dst = dst_x + dst_y * 64;
    int w = rect->w;
    int h = rect->h;
    unsigned short* s;
    unsigned short* d;
    int i;
    int j;

    s = vram + src_page * VRAM_PAGE_SIZE + src;
    d = vram + dst_page * VRAM_PAGE_SIZE + dst;
    for (j = 0; j < h; j++) {
        for (i = 0; i < w * 2; i++) {
            *d++ = *s++;
        }
        s += 64 - w * 2;
        d += 64 - w * 2;
    }
    s = texture_16bit + src_page * VRAM_PAGE_SIZE + src;
    d = texture_16bit + dst_page * VRAM_PAGE_SIZE + dst;
    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            *d++ = *s++;
        }
        s += 64 - w;
        d += 64 - w;
    }
    s = texture_4bit + src_page * VRAM_PAGE_SIZE + src;
    d = texture_4bit + dst_page * VRAM_PAGE_SIZE + dst;
    for (j = 0; j < h; j++) {
        for (i = 0; i < w * 2; i++) {
            *d++ = *s++;
        }
        s += 64 - w * 2;
        d += 64 - w * 2;
    }
    return 0;
}

unsigned short gc_convert_color(unsigned short color)
{
    unsigned short c;

    c = (color & 0x83E0) | ((color & 0x1F) << 10) | ((color >> 10) & 0x1F);
    if (c != 0) {
        c |= 0x8000;
    }
    return c;
}

unsigned short gc_clut_slot(unsigned short clut, unsigned short tp)
{
    unsigned short key = clut + ((tp << 6) / 16) * 0x2000;
    short x, y;
    short u, v;
    unsigned short* src;
    unsigned short* dst;
    int ofs;
    int rows;
    short per_row;
    unsigned short count;
    int i, j;
    unsigned short slot;

    slot = clut_slots[key];
    if (slot != 0xFFFF) {
        return slot;
    }
    x = (clut & 0x3F) << 4;
    y = (unsigned short)(clut >> 6);
    u = x % 64;
    v = y % 256;
    src = vram + (unsigned short)(x / 64 + (y / 256) * 16) * VRAM_PAGE_SIZE;
    dst = tlut_data_next;
    rows = 1;
    count = 16;
    per_row = 16;
    if (tp == 1) {
        rows = 4;
        per_row = 64;
        count = 256;
    }
    ofs = v * 64 + u;
    for (i = 0; i < rows; i++) {
        unsigned short* p = src + ofs;

        for (j = 0; j < per_row; j++) {
            *dst = convert_color(*p);
            p++;
            dst++;
        }
        src += VRAM_PAGE_SIZE;
    }
    DCFlushRangeNoSync(tlut_data_next, count * 2);
    GXInitTlutObj(tlut_next, tlut_data_next, GX_TL_RGB5A3, count);
    slot = tlut_next - tluts;
    tlut_next++;
    tlut_data_next = dst;
    clut_slots[key] = slot;
    return slot;
}

int gc_intersect_rect(RECT* a, RECT* b, RECT* out)
{
    RECT* first;
    RECT* second;

    second = a;
    first = b;
    if (a->x <= b->x) {
        second = b;
        first = a;
    }
    if (first->x + first->w <= second->x) {
        out->w = 0;
    } else {
        out->x = second->x;
        if (first->x + first->w > second->x + second->w) {
            out->w = second->w;
        } else {
            out->w = first->x + first->w - second->x;
        }
    }

    if (a->y <= b->y) {
        second = b;
        first = a;
    } else {
        second = a;
        first = b;
    }
    if (first->y + first->h <= second->y) {
        out->h = 0;
    } else {
        out->y = second->y;
        if (first->y + first->h > second->y + second->h) {
            out->h = second->h;
        } else {
            out->h = first->y + first->h - second->y;
        }
    }

    if (out->w == 0 || out->h == 0) {
        return 0;
    }
    return 1;
}

void gc_fill_page_rect(int page, RECT* part, unsigned char r, unsigned char g, unsigned char b)
{
    unsigned short color = ((b >> 3) << 10) | ((g >> 3) << 5) | (r >> 3);
    unsigned short* dst;
    unsigned short* fill;
    unsigned short* src;
    unsigned short* tex;
    int i, j;

    dst = &vram[page * VRAM_PAGE_SIZE];
    dst += part->y * 64 + part->x;
    for (i = 0; i < part->h; i++) {
        for (j = 0; j < part->w; j++) {
            *dst++ = color;
        }
        dst += 64 - part->w;
    }

    fill = vram + VRAM_PAGE_SIZE;
    for (i = 0; i < part->w * part->h; i++) {
        *fill++ = color;
    }

    src = fill;
    tex = texture_4bit + page * VRAM_PAGE_SIZE;
    for (i = 0; i < part->h; i++) {
        int y = part->y + i;
        int row = (y >> 3) * 512;
        int sub = (y & 7) * 2;

        for (j = 0; j < part->w; j++) {
            int x = part->x + j;
            unsigned short c = *src++;
            unsigned short* tile = tex + ((x >> 1) * 16 + row);

            tile[(x & 1) + sub] = ((c & 0xF0F0) >> 4) | ((c & 0x0F0F) << 4);
        }
    }
    DCFlushRangeNoSync(tex, VRAM_PAGE_SIZE * 2);

    src = fill;
    tex = texture_16bit + page * VRAM_PAGE_SIZE;
    for (i = 0; i < part->h; i++) {
        int y = part->y + i;
        int row = (y >> 2) * 256;
        int sub = (y & 3) * 4;

        for (j = 0; j < part->w; j++) {
            int x = part->x + j;
            unsigned short* tile = tex + ((x >> 2) * 16 + row);

            tile[(x & 3) + sub] = *src++;
        }
    }
    DCFlushRangeNoSync(tex, VRAM_PAGE_SIZE * 2);
}

void gc_load_page_rect(int page, RECT* part, unsigned long* p, RECT* rect, short x, short y)
{
    unsigned short* image = (unsigned short*)p;
    unsigned short* src;
    unsigned short* dst;
    unsigned short* tex;
    int i, j;

    src = image + (x + y * rect->w);
    dst = &vram[page * VRAM_PAGE_SIZE];
    dst += part->y * 64 + part->x;
    for (i = 0; i < part->h; i++) {
        for (j = 0; j < part->w; j++) {
            *dst++ = *src++;
        }
        dst += 64 - part->w;
        src += rect->w - part->w;
    }

    image += y * rect->w + ((x / 64) * 0x4000 + x % 64);
    src = image;
    tex = texture_4bit + page * VRAM_PAGE_SIZE;
    for (i = 0; i < part->h; i++) {
        int ty = part->y + i;
        int row = (ty >> 3) * 512;
        int sub = (ty & 7) * 2;

        for (j = 0; j < part->w; j++) {
            int tx = part->x + j;
            unsigned short c = *src++;
            unsigned short* tile = tex + ((tx >> 1) * 16 + row);

            tile[(tx & 1) + sub] = ((c & 0xF0F0) >> 4) | ((c & 0x0F0F) << 4);
        }
    }
    DCFlushRangeNoSync(tex, VRAM_PAGE_SIZE * 2);

    src = image;
    tex = texture_16bit + page * VRAM_PAGE_SIZE;
    for (i = 0; i < part->h; i++) {
        int ty = part->y + i;
        int row = (ty >> 2) * 256;
        int sub = (ty & 3) * 4;

        for (j = 0; j < part->w; j++) {
            int tx = part->x + j;
            unsigned short* tile = tex + ((tx >> 2) * 16 + row);

            tile[(tx & 3) + sub] = *src++;
        }
    }
    DCFlushRangeNoSync(tex, VRAM_PAGE_SIZE * 2);
}

void gc_draw_poly_g4(struct PrimCacheNode* node);
void gc_draw_poly_f3(struct PrimCacheNode* node);
void gc_draw_poly_ft3(struct PrimCacheNode* node);
void gc_draw_poly_f4(struct PrimCacheNode* node);
void gc_draw_poly_ft4(struct PrimCacheNode* node);
void gc_draw_line_f2(struct PrimCacheNode* node);
void gc_draw_line_f4(struct PrimCacheNode* node);
void gc_draw_tile(struct PrimCacheNode* node);
void gc_draw_sprt(struct PrimCacheNode* node);
void gc_draw_sprt_8(struct PrimCacheNode* node);
void gc_draw_sprt_16(struct PrimCacheNode* node);

void execDrMode(DR_MODE* prim);
void execDrEnv(DR_ENV* prim);
void execDrArea(DR_AREA* prim);
void execDrOffset(DR_OFFSET* prim);
void execDrTPage(DR_TPAGE* prim);
void gc_flush_dr_mode(DR_MODE* prim);
void gc_flush_dr_env(DR_ENV* prim);
void gc_flush_dr_area(DR_AREA* prim);
void gc_flush_dr_none(void* prim);
void gc_queue_poly_f3(void* prim, short a, unsigned short state);
void gc_queue_poly_ft3(void* p, short a, unsigned short state);
void gc_queue_poly_f4(void* prim, short a, unsigned short state);
void gc_queue_poly_g4(void* prim, short a, unsigned short state);
void gc_queue_poly_ft4(void* p, short a, unsigned short state);
void gc_queue_line_f2(void* prim, short a, unsigned short state);
void gc_queue_line_f4(void* prim, short a, unsigned short state);
void gc_queue_sprt(void* p, short a, unsigned short state);
void gc_queue_tile(void* prim, short a, unsigned short state);

static void (*dr_exec_funcs[5])() = {
    execDrMode,
    execDrEnv,
    execDrArea,
    execDrOffset,
    execDrTPage,
};
static void (*dr_flush_funcs[5])() = {
    gc_flush_dr_mode,
    gc_flush_dr_env,
    gc_flush_dr_area,
    gc_flush_dr_none,
    gc_flush_dr_none,
};
static void (*queue_funcs[32])(void* prim, short a, unsigned short state) = {
    0,
    0,
    0,
    0,
    0,
    0,
    gc_queue_poly_g4,
    0,
    gc_queue_poly_f3,
    gc_queue_poly_ft3,
    gc_queue_poly_f4,
    gc_queue_poly_ft4,
    0,
    0,
    gc_queue_poly_g4,
    0,
    gc_queue_line_f2,
    0,
    0,
    gc_queue_line_f4,
    0,
    0,
    0,
    0,
    gc_queue_tile,
    gc_queue_sprt,
    0,
    0,
    0,
    gc_queue_sprt,
    0,
    gc_queue_sprt,
};

void gc_tex_poly_ft3(struct PrimCacheNode* node);
void gc_tex_poly_ft4(struct PrimCacheNode* node);
void gc_tex_sprt(struct PrimCacheNode* node);

static unsigned short semi_prim_verts[32] = {
    0,
    0,
    0,
    0,
    0,
    0,
    4,
    0,
    3,
    3,
    6,
    4,
    3,
    3,
    4,
    0,
    2,
    0,
    4,
    6,
    2,
    0,
    4,
    6,
    4,
    4,
    4,
    0,
    4,
    4,
    4,
    4,
};
static unsigned long semi_prim_types[32] = {
    0,
    0,
    0,
    0,
    0,
    0,
    GX_QUADS,
    0,
    GX_TRIANGLES,
    GX_TRIANGLES,
    GX_TRIANGLES,
    GX_QUADS,
    GX_TRIANGLES,
    GX_TRIANGLES,
    GX_QUADS,
    0,
    GX_LINES,
    0,
    GX_TRIANGLES,
    GX_LINES,
    GX_LINES,
    0,
    GX_LINES,
    GX_LINES,
    GX_QUADS,
    GX_QUADS,
    GX_QUADS,
    0,
    GX_QUADS,
    GX_QUADS,
    GX_QUADS,
    GX_QUADS,
};
static void (*semi_tex_funcs[32])(struct PrimCacheNode* node) = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    gc_tex_poly_ft3,
    0,
    gc_tex_poly_ft4,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    gc_tex_sprt,
    0,
    0,
    0,
    gc_tex_sprt,
    0,
    gc_tex_sprt,
};

static void (*draw_funcs[32])(struct PrimCacheNode* node) = {
    0,
    0,
    0,
    0,
    0,
    0,
    gc_draw_poly_g4,
    0,
    gc_draw_poly_f3,
    gc_draw_poly_ft3,
    gc_draw_poly_f4,
    gc_draw_poly_ft4,
    0,
    0,
    gc_draw_poly_g4,
    0,
    gc_draw_line_f2,
    0,
    0,
    gc_draw_line_f4,
    0,
    0,
    0,
    0,
    gc_draw_tile,
    gc_draw_sprt,
    0,
    0,
    0,
    gc_draw_sprt_8,
    0,
    gc_draw_sprt_16,
};

static unsigned short ortho_width = 320;
static unsigned short ortho_height = 240;

static unsigned long tex_prim_types[2] = { GX_QUADS, GX_TRIANGLES };
static unsigned long tex_prim_verts[2] = { 4, 3 };
static unsigned long cache_prim_types[NUM_CACHE_LISTS] = { GX_LINES, GX_QUADS, GX_TRIANGLES, GX_LINES, GX_TRIANGLES };
static unsigned long cache_prim_verts[NUM_CACHE_LISTS] = { 2, 4, 3, 6, 6 };

static GXTexObj texobjs_8bit[NUM_TEXTURE_PAGES / 2];
static GXTexObj texobjs_4bit[NUM_TEXTURE_PAGES / 2];

void drawPrimitiveCache(void)
{
    int page;
    int kind;
    int slot;
    int i;
    unsigned short count;
    struct PrimCacheNode* node;

    GXSetNumChans(1);
    GXSetTexCoordGen2(0, 1, 4, 0x3C, 0, 0x7D);
    GXSetNumTexGens(1);
    GXSetChanCtrl(0, 1, 1, 1, 0, 0, 2);
    GXSetChanCtrl(2, 1, 1, 1, 0, 0, 2);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevOp(0, 0);
    GXSetBlendMode(1, 4, 5, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(11, 1);
    GXSetVtxDesc(13, 1);
    GXSetVtxAttrFmt(0, 11, 0, 1, 0);
    GXSetVtxAttrFmt(0, 9, 1, 3, 0);
    GXSetVtxAttrFmt(0, 13, 1, 3, 8);
    for (page = 0; page < NUM_TEXTURE_PAGES; page++) {
        for (kind = 0; kind < 2; kind++) {
            for (slot = 0; slot < NUM_CLUT_SLOTS; slot++) {
                count = 0;
                for (node = texture_lists[page][kind][slot]; node != 0; node = node->next) {
                    count++;
                }
                if (count == 0) {
                    continue;
                }
                GXLoadTlut(&tluts[slot], 0);
                if (page < NUM_TEXTURE_PAGES / 2) {
                    GXLoadTexObj(&texobjs_4bit[page], 0);
                } else if (page < NUM_TEXTURE_PAGES) {
                    GXLoadTexObj(&texobjs_8bit[page - NUM_TEXTURE_PAGES / 2], 0);
                } else {
                    OSReport("i = %d/%d  ", page, NUM_TEXTURE_PAGES / 2);
                    OSPanic("gcGPU.c", 0xA77, "fatal error in drawPrimitiveCache\n");
                }
                GXBegin(tex_prim_types[kind], 0, count * tex_prim_verts[kind]);
                for (node = texture_lists[page][kind][slot]; node != 0; node = node->next) {
                    draw_funcs[((unsigned char*)node->prim)[7] >> 2](node);
                }
            }
        }
    }
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(11, 1);
    GXSetVtxAttrFmt(0, 11, 0, 1, 0);
    GXSetVtxAttrFmt(0, 9, 1, 3, 0);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 0xFF, 0xFF, 4);
    GXSetTevOp(0, 4);
    for (i = 0; i < NUM_CACHE_LISTS; i++) {
        count = 0;
        for (node = cache_lists[i]; node != 0; node = node->next) {
            count++;
        }
        if (count == 0) {
            continue;
        }
        GXBegin(cache_prim_types[i], 0, count * cache_prim_verts[i]);
        for (node = cache_lists[i]; node != 0; node = node->next) {
            draw_funcs[((unsigned char*)node->prim)[7] >> 2](node);
        }
    }
}

void drawSemiTransPrimitive(void* prim, short a, unsigned short state)
{
    struct PrimCacheNode node;
    struct GpuDrawState* st = &draw_states[state];
    unsigned char code = ((unsigned char*)prim)[7] >> 2;

    node.prim = prim;
    node.a = a;
    node.state = state;
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(11, 1);
    GXSetVtxAttrFmt(0, 11, 0, 1, 0);
    GXSetVtxAttrFmt(0, 9, 1, 3, 0);
    if (semi_tex_funcs[code] != 0) {
        GXSetVtxDesc(13, 1);
        GXSetVtxAttrFmt(0, 13, 1, 3, 8);
        semi_tex_funcs[code](&node);
        GXSetChanCtrl(0, 1, 1, 1, 0, 0, 2);
        GXSetChanCtrl(2, 1, 1, 1, 0, 0, 2);
        GXSetNumTevStages(1);
        GXSetTevOrder(0, 0, 0, 4);
        GXSetTevOp(0, 0);
    } else {
        GXSetNumTevStages(1);
        GXSetTevOrder(0, 0xFF, 0xFF, 4);
        GXSetTevOp(0, 4);
    }
    if (((unsigned char*)prim)[7] & 2) {
        switch (st->abr) {
        case 0:
            GXSetBlendMode(1, 4, 5, 0);
            GXSetTevAlphaOp(0, 0, 0, 3, 1, 0);
            break;
        case 1:
            GXSetBlendMode(1, 1, 1, 0);
            break;
        case 2:
            GXSetBlendMode(3, 0, 0, 0);
            break;
        case 3:
            GXSetBlendMode(1, 4, 1, 0);
            GXSetTevAlphaIn(0, 1, 7, 6, 7);
            fn_800763F0(0, 2);
            break;
        default:
            OSPanic("gcGPU.c", 0xB25, "fatal error(1) in drawSemiTransPrimitive\n");
            break;
        }
    } else {
        OSPanic("gcGPU.c", 0xB29, "fatal error(2) in drawSemiTransPrimitive\n");
    }
    if (code == 0) {
        OSReport("error semitrans prim\n");
        return;
    }
    GXBegin(semi_prim_types[code], 0, semi_prim_verts[code]);
    draw_funcs[code](&node);
}

void gc_queue_poly_f3(void* prim, short a, unsigned short state)
{
    cache_push(&cache_lists[2], prim, a, state);
}

void gc_queue_poly_ft3(void* p, short a, unsigned short state)
{
    POLY_FT3* prim = p;
    unsigned short slot = gc_clut_slot(prim->clut, (prim->tpage >> 7) & 3);

    cache_push(&texture_lists[tpage_index(prim->tpage)][1][slot], prim, a, state);
}

void gc_queue_poly_f4(void* prim, short a, unsigned short state)
{
    cache_push(&cache_lists[4], prim, a, state);
}

void gc_queue_poly_g4(void* prim, short a, unsigned short state)
{
    cache_push(&cache_lists[1], prim, a, state);
}

void gc_queue_poly_ft4(void* p, short a, unsigned short state)
{
    POLY_FT4* prim = p;
    int page = ((prim->tpage >> 7) & 3) << 5;
    unsigned short slot = gc_clut_slot(prim->clut, (prim->tpage >> 7) & 3);

    if (((prim->tpage >> 7) & 3) == 1U) {
        int next = 0;

        if (prim->u0 >= 0x80 || prim->u1 >= 0x80) {
            next = 1;
            if (prim->u0 == 0x7F) {
                prim->u0 = 0;
                prim->u2 = 0;
            } else {
                prim->u0 -= 0x80;
                prim->u2 -= 0x80;
            }
            if (prim->u1 == 0x7F) {
                prim->u1 = 0;
                prim->u3 = 0;
            } else {
                prim->u1 -= 0x80;
                prim->u3 -= 0x80;
            }
        }
        page += next;
    }
    cache_push(&texture_lists[page + tpage_index(prim->tpage)][0][slot], prim, a, state);
}

void gc_queue_line_f2(void* prim, short a, unsigned short state)
{
    cache_push(&cache_lists[0], prim, a, state);
}

void gc_queue_line_f4(void* prim, short a, unsigned short state)
{
    cache_push(&cache_lists[3], prim, a, state);
}

void gc_queue_sprt(void* p, short a, unsigned short state)
{
    SPRT* prim = p;
    struct GpuDrawState* st = &draw_states[state];
    int page = st->tp << 5;
    unsigned short slot = gc_clut_slot(prim->clut, st->tp);

    if (prim->u0 >= 0x80 && st->tp == 1) {
        page++;
        prim->u0 -= 0x80;
    }
    cache_push(&texture_lists[st->page + page][0][slot], prim, a, state);
}

void gc_queue_tile(void* prim, short a, unsigned short state)
{
    cache_push(&cache_lists[1], prim, a, state);
}

void gc_draw_poly_f3(struct PrimCacheNode* node)
{
    struct GpuDrawState* st = &draw_states[node->state];
    POLY_F3* p = node->prim;

    GXPosition3s16(st->ofs[0] + p->x0, st->ofs[1] + p->y0, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXPosition3s16(st->ofs[0] + p->x1, st->ofs[1] + p->y1, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXPosition3s16(st->ofs[0] + p->x2, st->ofs[1] + p->y2, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
}

void gc_draw_poly_ft3(struct PrimCacheNode* node)
{
    POLY_FT3* p = node->prim;
    struct GpuDrawState* st = &draw_states[node->state];

    if (p->r0 == 0x80 && p->g0 == 0x80 && p->b0 == 0x80) {
        p->r0 = p->g0 = p->b0 = 0xFF;
    }
    GXPosition3s16(st->ofs[0] + p->x0, st->ofs[1] + p->y0, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXTexCoord2u16(p->u0, p->v0);
    GXPosition3s16(st->ofs[0] + p->x1, st->ofs[1] + p->y1, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXTexCoord2u16(p->u1, p->v1);
    GXPosition3s16(st->ofs[0] + p->x2, st->ofs[1] + p->y2, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXTexCoord2u16(p->u2, p->v2);
}

void gc_draw_poly_f4(struct PrimCacheNode* node)
{
    struct GpuDrawState* st = &draw_states[node->state];
    POLY_F4* p = node->prim;

    GXPosition3s16(st->ofs[0] + p->x0, st->ofs[1] + p->y0, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXPosition3s16(st->ofs[0] + p->x1, st->ofs[1] + p->y1, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXPosition3s16(st->ofs[0] + p->x2, st->ofs[1] + p->y2, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXPosition3s16(st->ofs[0] + p->x2, st->ofs[1] + p->y2, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXPosition3s16(st->ofs[0] + p->x1, st->ofs[1] + p->y1, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXPosition3s16(st->ofs[0] + p->x3, st->ofs[1] + p->y3, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
}

void gc_draw_poly_ft4(struct PrimCacheNode* node)
{
    struct GpuDrawState* st = &draw_states[node->state];
    POLY_FT4* p = node->prim;
    short du0 = 0;
    short du1 = 0;
    short dv0 = 0;
    short dv1 = 0;

    if (p->u0 & 1) {
        du0 = 1;
    }
    if (p->u1 & 1) {
        du1 = 1;
    }
    if (p->v0 & 1) {
        dv0 = 1;
    }
    if (p->v1 & 1) {
        dv1 = 1;
    }
    if (p->r0 == 0x80 && p->g0 == 0x80 && p->b0 == 0x80) {
        p->r0 = p->g0 = p->b0 = 0xFF;
    }
    if (((p->tpage >> 7) & 3) == 1) {
        if (p->u0 != 0) {
            if (p->u0 == 0x7F) {
                du0 = 2;
            } else {
                p->u0++;
                p->u2++;
            }
            p->u0 <<= 1;
            p->u2 <<= 1;
        }
        if (p->u1 != 0) {
            if (p->u1 == 0x7F) {
                du1 = 2;
            } else {
                p->u1++;
                p->u3++;
            }
            p->u1 <<= 1;
            p->u3 <<= 1;
        }
    } else if (p->u1 == 0) {
        p->x1++;
        p->x3++;
    }
    GXPosition3s16(st->ofs[0] + p->x0, st->ofs[1] + p->y0, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXTexCoord2u16(p->u0 + du0, p->v0 + dv0);
    GXPosition3s16(st->ofs[0] + p->x1, st->ofs[1] + p->y1, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXTexCoord2u16(p->u1 + du1, p->v1 + dv0);
    GXPosition3s16(st->ofs[0] + p->x3, st->ofs[1] + p->y3, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXTexCoord2u16(p->u3 + du1, p->v3 + dv1);
    GXPosition3s16(st->ofs[0] + p->x2, st->ofs[1] + p->y2, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXTexCoord2u16(p->u2 + du0, p->v2 + dv1);
}

void gc_draw_poly_g4(struct PrimCacheNode* node)
{
    POLY_G4* p = node->prim;
    struct GpuDrawState* st = &draw_states[node->state];

    GXPosition3s16(st->ofs[0] + p->x0, st->ofs[1] + p->y0, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXPosition3s16(st->ofs[0] + p->x1, st->ofs[1] + p->y1, node->a);
    GXColor3u8(p->r1, p->g1, p->b1);
    GXPosition3s16(st->ofs[0] + p->x3, st->ofs[1] + p->y3, node->a);
    GXColor3u8(p->r3, p->g3, p->b3);
    GXPosition3s16(st->ofs[0] + p->x2, st->ofs[1] + p->y2, node->a);
    GXColor3u8(p->r2, p->g2, p->b2);
}

void gc_draw_line_f2(struct PrimCacheNode* node)
{
    struct GpuDrawState* st = &draw_states[node->state];
    LINE_F2* p = node->prim;

    GXPosition3s16(st->ofs[0] + p->x0, st->ofs[1] + p->y0, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXPosition3s16(st->ofs[0] + p->x1, st->ofs[1] + p->y1, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
}

void gc_draw_line_f4(struct PrimCacheNode* node)
{
    struct GpuDrawState* st = &draw_states[node->state];
    LINE_F4* p = node->prim;

    GXPosition3s16(st->ofs[0] + p->x0, st->ofs[1] + p->y0, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXPosition3s16(st->ofs[0] + p->x1, st->ofs[1] + p->y1, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXPosition3s16(st->ofs[0] + p->x1, st->ofs[1] + p->y1, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXPosition3s16(st->ofs[0] + p->x2, st->ofs[1] + p->y2, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXPosition3s16(st->ofs[0] + p->x2, st->ofs[1] + p->y2, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXPosition3s16(st->ofs[0] + p->x3, st->ofs[1] + p->y3, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
}

void gc_draw_sprt_8(struct PrimCacheNode* node)
{
    struct GpuDrawState* st = &draw_states[node->state];
    SPRT_8* p = node->prim;

    GXPosition3s16(st->ofs[0] + p->x0, st->ofs[1] + p->y0, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXTexCoord2u16(p->u0, p->v0);
    GXPosition3s16(st->ofs[0] + (p->x0 + 8), st->ofs[1] + p->y0, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXTexCoord2u16(p->u0 + 8, p->v0);
    GXPosition3s16(st->ofs[0] + (p->x0 + 8), st->ofs[1] + (p->y0 + 8), node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXTexCoord2u16(p->u0 + 8, p->v0 + 8);
    GXPosition3s16(st->ofs[0] + p->x0, st->ofs[1] + (p->y0 + 8), node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXTexCoord2u16(p->u0, p->v0 + 8);
    if (p->r0 == 0x80 && p->g0 == 0x80 && p->b0 == 0x80) {
        p->r0 = p->g0 = p->b0 = 0xFF;
    }
}

void gc_draw_sprt_16(struct PrimCacheNode* node)
{
    struct GpuDrawState* st = &draw_states[node->state];
    SPRT_16* p = node->prim;
    short tex_w = 0x10;

    if (st->tp == 1) {
        tex_w = 0x20;
        p->u0 <<= 1;
    }
    if (p->r0 == 0x80 && p->g0 == 0x80 && p->b0 == 0x80) {
        p->r0 = p->g0 = p->b0 = 0xFF;
    }
    GXPosition3s16(st->ofs[0] + p->x0, st->ofs[1] + p->y0, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXTexCoord2u16(p->u0, p->v0);
    GXPosition3s16(st->ofs[0] + (p->x0 + 0x10), st->ofs[1] + p->y0, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXTexCoord2u16(p->u0 + tex_w, p->v0);
    GXPosition3s16(st->ofs[0] + (p->x0 + 0x10), st->ofs[1] + (p->y0 + 0x10), node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXTexCoord2u16(p->u0 + tex_w, p->v0 + 0x10);
    GXPosition3s16(st->ofs[0] + p->x0, st->ofs[1] + (p->y0 + 0x10), node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXTexCoord2u16(p->u0, p->v0 + 0x10);
}

void gc_draw_sprt(struct PrimCacheNode* node)
{
    struct GpuDrawState* st = &draw_states[node->state];
    SPRT* p = node->prim;
    short ul;
    short ur;
    short vb;

    if (st->tp == 1) {
        ul = p->u0 * 2;
        ur = (p->u0 + p->w) * 2;
    } else {
        ul = p->u0;
        ur = p->u0 + p->w;
    }
    vb = p->v0 + p->h;
    if (p->r0 == 0x80 && p->g0 == 0x80 && p->b0 == 0x80) {
        p->r0 = p->g0 = p->b0 = 0xFF;
    }
    GXPosition3s16(st->ofs[0] + p->x0, st->ofs[1] + p->y0, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXTexCoord2u16(ul, p->v0);
    GXPosition3s16(st->ofs[0] + (p->x0 + p->w), st->ofs[1] + p->y0, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXTexCoord2u16(ur, p->v0);
    GXPosition3s16(st->ofs[0] + (p->x0 + p->w), st->ofs[1] + (p->y0 + p->h), node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXTexCoord2u16(ur, vb);
    GXPosition3s16(st->ofs[0] + p->x0, st->ofs[1] + (p->y0 + p->h), node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXTexCoord2u16(ul, vb);
}

void gc_draw_tile(struct PrimCacheNode* node)
{
    struct GpuDrawState* st = &draw_states[node->state];
    TILE* p = node->prim;

    if (p->r0 == 0x80 && p->g0 == 0x80 && p->b0 == 0x80) {
        p->r0 = p->g0 = p->b0 = 0xFF;
    }
    GXPosition3s16(st->ofs[0] + p->x0, st->ofs[1] + p->y0, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXPosition3s16(st->ofs[0] + (p->x0 + p->w), st->ofs[1] + p->y0, node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXPosition3s16(st->ofs[0] + (p->x0 + p->w), st->ofs[1] + (p->y0 + p->h), node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
    GXPosition3s16(st->ofs[0] + p->x0, st->ofs[1] + (p->y0 + p->h), node->a);
    GXColor3u8(p->r0, p->g0, p->b0);
}

void execDrMode(DR_MODE* prim)
{
    draw_state->page = tpage_index(prim->tpage);
    draw_state->tp = (prim->tpage >> 7) & 3;
    draw_state->abr = (prim->tpage >> 5) & 3;
    if (prim->tw) {
        draw_state->tw.x = prim->tw->x;
        draw_state->tw.y = prim->tw->y;
        draw_state->tw.w = prim->tw->w;
        draw_state->tw.h = prim->tw->h;
    }
}

#line 3652
void execDrEnv(DR_ENV* prim)
{
    assert(prim);
    if (prim->clip.w != 0 && prim->clip.h != 0) {
        if (gc_get_screen_height() > 400) {
            GXSetScissor(prim->clip.x * 2, prim->clip.y * 2, prim->clip.w * 2, prim->clip.h * 2);
        } else {
            GXSetScissor(prim->clip.x, prim->clip.y, prim->clip.w, prim->clip.h);
        }
    }
    draw_state->ofs[0] = prim->ofs[0];
    draw_state->ofs[1] = prim->ofs[1];
    draw_state->tw.x = prim->tw.x;
    draw_state->tw.y = prim->tw.y;
    draw_state->tw.w = prim->tw.w;
    draw_state->tw.h = prim->tw.h;
    draw_state->page = tpage_index(prim->tpage);
    draw_state->tp = (prim->tpage >> 7) & 3;
    draw_state->abr = (prim->tpage >> 5) & 3;
}

#line 3696
void execDrArea(DR_AREA* prim)
{
    assert(prim);
    if (prim->area.w != 0 && prim->area.h != 0) {
        if (gc_get_screen_height() > 400) {
            GXSetScissor(prim->area.x * 2, prim->area.y * 2, prim->area.w * 2, prim->area.h * 2);
        } else {
            GXSetScissor(prim->area.x, prim->area.y, prim->area.w, prim->area.h);
        }
    }
}

void execDrOffset(DR_OFFSET* prim)
{
    draw_state->ofs[0] = prim->x;
    draw_state->ofs[1] = prim->y;
}

void execDrTPage(DR_TPAGE* prim)
{
    unsigned short tpage = prim->tpage;

    draw_state->page = tpage_index(tpage);
    draw_state->tp = (tpage >> 7) & 3;
    draw_state->abr = (tpage >> 5) & 3;
}

void gc_flush_dr_mode(DR_MODE* prim)
{
    if (prim->tw) {
        flushPrimitiveCache();
    }
}

void gc_flush_dr_env(DR_ENV* prim)
{
    if (prim->clip.w != 0 && prim->clip.h != 0) {
        flushPrimitiveCache();
    }
}

void gc_flush_dr_area(DR_AREA* prim)
{
    if (prim->area.w != 0 && prim->area.h != 0) {
        flushPrimitiveCache();
    }
}

void gc_flush_dr_none(void* prim)
{
}

static void setCurrentTexture(unsigned char page, unsigned char tp)
{
    if (tp == 0) {
        GXLoadTexObj(&texobjs_4bit[page], 0);
    } else if (tp == 1) {
        GXLoadTexObj(&texobjs_8bit[page], 0);
    } else {
        OSPanic("gcGPU.c", 0x8B1, "fatal error in setCurrentTexture\n");
    }
}

void gc_tex_poly_ft3(struct PrimCacheNode* node)
{
    struct GpuDrawState* st = &draw_states[node->state];
    POLY_FT3* prim = node->prim;

    GXLoadTlut(&tluts[gc_clut_slot(prim->clut, (prim->tpage >> 7) & 3)], 0);
    setCurrentTexture(tpage_index(prim->tpage), st->tp);
}

void gc_tex_poly_ft4(struct PrimCacheNode* node)
{
    struct GpuDrawState* st = &draw_states[node->state];
    POLY_FT4* prim = node->prim;

    GXLoadTlut(&tluts[gc_clut_slot(prim->clut, (prim->tpage >> 7) & 3)], 0);
    setCurrentTexture(tpage_index(prim->tpage), st->tp);
}

void gc_tex_sprt(struct PrimCacheNode* node)
{
    struct GpuDrawState* st = &draw_states[node->state];
    SPRT* prim = node->prim;

    GXLoadTlut(&tluts[gc_clut_slot(prim->clut, st->tp)], 0);
    if (prim->u0 >= 0x80 && st->tp == 1) {
        prim->u0 -= 0x80;
        setCurrentTexture(st->page + 1, st->tp);
    } else {
        setCurrentTexture(st->page, st->tp);
    }
}
