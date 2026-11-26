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
#ifdef MMX4_SATURN
#define LAST_KIND 6
#define LAST_FACET 0x2560245u, 0x2340223u, 0x18A0179u, 0x1680157u
#ifdef VERSION_SATURN_PROTO
#define FACET_DEPTH 0x3C11015Fu
#else
#define FACET_DEPTH 0x3C11017Fu
#endif
#else
#define LAST_KIND 8
#define LAST_FACET 0x1F001DFu, 0x2560245u, 0x1240113u, 0x10200F1u
#define FACET_DEPTH 0x3C117FFFu
#endif
static void tf_init_4(void)
{
    TF(4);
}
static void tf_init_last(void) { TF(LAST_KIND); }

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
    tf_init_last,
};
static const u32 title_facet_init_states_expected[] = { 0xFF000181u, 0x140003u, 0x360025u, 0xBE00ADu, 0x9C008Bu, FACET_DEPTH, 0xFF040181u, 0x10200F1u, 0x1240113u, 0x1460135u, 0x1460135u, FACET_DEPTH, 0xFF000181u | LAST_KIND << 16, LAST_FACET, FACET_DEPTH };

static u32 test_title_facet_init_states(u32 row)
{
    return title_facet_run(title_facet_init_states_cases[row], row, &title_facet_init_states_expected[row * 6]);
}

void title_facet_update(struct QuadObj*);
static u32 facet(u8 state, u8 kind, u8 timer, u32 misc_full)
{
    u32 i;
    memset(&title_quad, 0, sizeof(title_quad));
    memset(misc_objects, 0, sizeof(misc_objects));
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = misc_full;
    title_quad.active = 0x81;
    title_quad.bg_offset = -1;
    title_quad.state = state;
    title_quad.unk2 = kind;
    title_quad.ext.unk_ext.unk38 = timer;
    title_facet_update(&title_quad);
    return title_quad.state | (u32)(u8)title_quad.ext.unk_ext.unk38 << 8 | (u32)misc_objects[0].id << 16 | (u32)misc_objects[0].unk2 << 24;
}
static u32 tf_spinning(void)
{
    u32 seen;
    game_info.unk6 = 1;
    seen = facet(1, 4, 0x3C, 0);
    game_info.unk6 = 0;
    return seen;
}
static u32 tf_spun(void)
{
    game_info.unk6 = 0;
    return facet(1, 4, 0x3C, 0);
}
static u32 tf_holding(void) { return facet(2, 0, 2, 0); }
static u32 tf_done_other(void) { return facet(2, 4, 1, 0); }
static u32 tf_done_logo(void) { return facet(2, 0, 1, 0); }
static u32 tf_done_logo_full(void) { return facet(2, 0, 1, 1); }
static const CTestCase title_facet_steps_cases[] = {
    tf_spinning,
    tf_spun,
    tf_holding,
    tf_done_other,
    tf_done_logo,
    tf_done_logo_full,
};
static const u32 title_facet_steps_cases_expected[] = { 0x3C01u, 0x0502u, 0x0102u, 0x0003u, 0x0B130003u, 0x0003u };

const struct CTestGroup c_test_groups[] = {
    { "title_facet_init_states", 0, 0, COUNT(title_facet_init_states_cases), test_title_facet_init_states },
    { "title_facet_steps", title_facet_steps_cases, title_facet_steps_cases_expected, COUNT(title_facet_steps_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(title_facet_init_states_cases) + COUNT(title_facet_steps_cases);
