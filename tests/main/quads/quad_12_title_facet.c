#include "test_runtime.h"
#include "main/323C.h"
void title_facet_init(struct QuadObj*);
extern union TitleScratch D_80169498;

static struct QuadObj title_quad;
static f32 facet_saved[36];
#define TF(kind)                                                                \
    do {                                                                        \
        u32 i;                                                                  \
        memcpy(facet_saved, D_80169498.title.coordinates, sizeof(facet_saved)); \
        for (i = 0; i < 36; i++)                                                \
            D_80169498.title.coordinates[i].val = (s32)((i * 0x11 + 3) << 16);  \
        memset(&title_quad, 0, sizeof(title_quad));                             \
        title_quad.active = 1;                                                  \
        title_quad.unk2 = kind;                                                 \
        title_facet_init(&title_quad);                                          \
        memcpy(D_80169498.title.coordinates, facet_saved, sizeof(facet_saved)); \
    } while (0)
static void tf_init_0(void)
{
    TF(0);
}
static void tf_init_4(void) { TF(4); }
static void tf_init_8(void) { TF(8); }

static u32 title_facet_run(void (*run)(void), u32 row, const u32* expected)
{
    u32 seen[6];
    run();
    seen[0] = (u8)title_quad.active | (u8)title_quad.state << 8 | (u8)title_quad.unk2 << 16 | (u32)(u8)title_quad.bg_offset << 24;
    seen[1] = (u16)title_quad.vertices[0].x.i.hi | (u32)(u16)title_quad.vertices[0].y.i.hi << 16;
    seen[2] = (u16)title_quad.vertices[1].x.i.hi | (u32)(u16)title_quad.vertices[1].y.i.hi << 16;
    seen[3] = (u16)title_quad.vertices[2].x.i.hi | (u32)(u16)title_quad.vertices[2].y.i.hi << 16;
    seen[4] = (u16)title_quad.vertices[3].x.i.hi | (u32)(u16)title_quad.vertices[3].y.i.hi << 16;
    seen[5] = title_quad.unk34 | (u32)title_quad.unk36 << 16 | (u32)(u8)title_quad.ext.unk_ext.unk38 << 24;
    return c_test_observe(0, row, seen, expected, 6);
}

static void (*const title_facet_init_states_cases[])(void) = {
    tf_init_0,
    tf_init_4,
    tf_init_8,
};
static const u32 title_facet_init_states_expected[] = { 0xFF000181u, 0x140003u, 0x360025u, 0xBE00ADu, 0x9C008Bu, 0x3C117FFFu, 0xFF040181u, 0x10200F1u, 0x1240113u, 0x1460135u, 0x1460135u, 0x3C117FFFu, 0xFF080181u, 0x1F001DFu, 0x2560245u, 0x1240113u, 0x10200F1u, 0x3C117FFFu };

static u32 test_title_facet_init_states(u32 row)
{
    return title_facet_run(title_facet_init_states_cases[row], row, &title_facet_init_states_expected[row * 6]);
}

const struct CTestGroup c_test_groups[] = {
    { "title_facet_init_states", 0, 0, COUNT(title_facet_init_states_cases), test_title_facet_init_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(title_facet_init_states_cases);
