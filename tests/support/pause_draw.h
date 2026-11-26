#ifndef MMX4_TESTS_PAUSE_DRAW_H
#define MMX4_TESTS_PAUSE_DRAW_H
struct PauseDrawHudLayout {
    s16 x, y;
    u8 tile, character, clut, alternate_clut;
};
extern struct PauseDrawHudLayout D_800F1AD8[38];
struct PauseDrawQuad {
    s16 x0, y0, x1, y1, x2, y2, x3, y3, index;
};
extern struct PauseDrawQuad D_800F1C18[13];
extern s16 D_800F1D04[];
extern s16 D_800F1C08[2];
void func_80017340(void);

struct PauseDrawPrim {
    u8 bar;
    s16 x0, y0, x1, x2, x3;
};
static u32 pause_draw_archive[1001];
static struct DrawInfo pause_draw_info;
static struct PauseDrawPrim pause_drawn[64];
static u32 pause_drawn_count;

static void pause_draw_begin(void)
{
    u32 i;
    for (i = 0; i < 1000; i++) {
        u16* header = (u16*)&pause_draw_archive[i];
        header[0] = 1;
        header[1] = 1000;
    }
    pause_draw_archive[1000] = 0;
    TEST_TITLE_FRAMES = (u8*)pause_draw_archive;
    memset(&pause_draw_info, 0, sizeof(pause_draw_info));
    cur_draw_info = &pause_draw_info;
    SP_DRAW_BUFFER = 0;
    memset(D_80173C6C, 0, 4);
}

static void pause_draw_collect(void)
{
    P_TAG* node = (P_TAG*)D_8013E1E8[0][0][5];
    P_TAG* tail = D_8013BC40[0][0][5];
    pause_drawn_count = 0;
    while (node != NULL) {
        P_TAG* prim = (P_TAG*)nextPrim(node);
        struct PauseDrawPrim* out = &pause_drawn[pause_drawn_count++];
        assert(getlen(node) == 1 && pause_drawn_count <= COUNT(pause_drawn));
        if (getlen(prim) == 3) {
            SPRT_16* s = (SPRT_16*)prim;
            out->bar = 0;
            out->x0 = s->x0;
            out->y0 = s->y0;
        } else {
            POLY_F4* p = (POLY_F4*)prim;
            assert(getlen(prim) == 5);
            out->bar = 1;
            out->x0 = p->x0;
            out->y0 = p->y0;
            out->x1 = p->x1;
            out->x2 = p->x2;
            out->x3 = p->x3;
        }
        if (prim == tail)
            break;
        node = (P_TAG*)nextPrim(prim);
    }
}
#endif
