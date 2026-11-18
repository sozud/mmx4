#include "gc/assert.h"
#include "gc/collection.h"
#include "gc/dolphin.h"
#include "gc/libgpu.h"

struct GpuDrawState {
    unsigned short ofs[2];
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

#define NUM_CACHE_LISTS 5
#define NUM_TEXTURE_PAGES 64
#define NUM_CLUT_SLOTS 256
#define NUM_DRAW_STATES 16

#define VRAM_PAGE_SIZE (64 * 256)
#define NUM_TLUTS 1024

static int disp_mask;
static unsigned short (*convert_color)(unsigned short color);
static struct GpuDrawState* draw_state;
static struct GpuDrawState draw_states[NUM_DRAW_STATES];
static struct PrimCacheNode* cache_lists[NUM_CACHE_LISTS];
static struct PrimCacheNode* texture_lists[NUM_TEXTURE_PAGES][2][NUM_CLUT_SLOTS];
static struct PrimCacheNode* cache_next;

static unsigned short clut_slots[0x10000];
static GXTlutObj* tlut_next;
static unsigned short* tlut_data_next;
static GXTlutObj tluts[NUM_TLUTS];
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

void gc_queue_poly_f3(void* prim, short a, unsigned short state)
{
    cache_push(&cache_lists[2], prim, a, state);
}

void gc_queue_poly_ft3(POLY_FT3* prim, short a, unsigned short state)
{
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

void gc_queue_poly_ft4(POLY_FT4* prim, short a, unsigned short state)
{
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

void gc_queue_sprt(SPRT* prim, short a, unsigned short state)
{
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
