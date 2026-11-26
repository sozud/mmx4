#include "test_runtime.h"
#include "main/3A6C.h"
#include "main/archive_stage_data.h"
#include "main/55C4.h"
#ifndef MMX4_SATURN
void func_8001326C(u8 arg0);
void func_80013404(u8 arg0);
extern struct Prim D_800EE504[9];

struct HudRow {
    u8 arg, character, stage, substage, blink;
    u8 sprites[8];
};
static const struct HudRow hud_rows[] = {
    { 1, CHARACTER_X, 12, 0, 0, { 0, 1, 2, 3, 5, 6, 0xFF } },
    { 1, CHARACTER_ZERO, 2, 1, 1, { 1, 2, 4, 5, 6, 8, 0xFF } },
    { 1, CHARACTER_X, 3, 0, 0, { 0, 1, 2, 3, 5, 6, 7, 0xFF } },
    { 0, CHARACTER_X, 3, 0, 0, { 0, 1, 2, 0xFF } },
};
static u32 test_hud(u32 row)
{
    const struct HudRow* in = &hud_rows[row];
    struct DrawInfo draw, *saved_draw = cur_draw_info;
    SPRT* sprites = (SPRT*)temp1[1].data;
    DR_MODE* modes = (DR_MODE*)temp2[1].data;
    void* link = (void*)0x00ABCDEF;
    u32 count, i;
    ResetGraph(0);
    memset(&draw, 0, sizeof(draw));
    cur_draw_info = &draw;
    setaddr(&draw.ordering_table.mid, link);
    SP_DRAW_BUFFER = 1;
    SP_PRIM_CURSOR = SP_DRAW_MODE_CURSOR = NULL;
    main_bss_state.frame_counter = in->blink ? 0x30 : 0x2F;
    engine_obj.cur_character = in->character;
    engine_obj.stage = in->stage;
    engine_obj.substage = in->substage;
    memset(sprites, 0xEE, 9 * sizeof(SPRT));
    func_80013404(in->arg);
    for (count = 0; in->sprites[count] != 0xFF; count++) {
        const struct Prim* prim = &D_800EE504[in->sprites[count]];
        SPRT* sprite = &sprites[count];
        DR_MODE* mode = &modes[count];
        u8 uv = in->sprites[count] == 6 ? D_800EE54C.stage_archive_indices[in->stage == 12 ? 11 : in->stage] : prim->uv;
        assert(getlen(sprite) == 4 && getcode(sprite) == 0x65);
        assert(sprite->x0 == prim->x && sprite->y0 == prim->y && sprite->w == prim->w * 16 && sprite->h == prim->h * 16);
        assert(sprite->u0 == (uv & 0xF) * 16 && sprite->v0 == (uv & 0xF0));
        assert(sprite->clut == ((prim->clut & 0xF) | ((prim->clut >> 4) + 0x1E0) << 6));
        assert(getlen(mode) == 2 && (u32)mode->code[0] == 0xE100001E && (u32)mode->code[1] == 0);
        assert((void*)getaddr(mode) == sprite && (void*)getaddr(sprite) == link);
        link = mode;
    }
    assert((void*)getaddr(&draw.ordering_table.mid) == link);
    for (i = 0; i < sizeof(SPRT); i++)
        assert(((u8*)&sprites[count])[i] == 0xEE);
    assert(SP_PRIM_CURSOR == &sprites[count] && SP_DRAW_MODE_CURSOR == &modes[count]);
    if (in->arg)
        assert(D_800EE504[6].uv == D_800EE54C.stage_archive_indices[in->stage == 12 ? 11 : in->stage]);
    cur_draw_info = saved_draw;
    return count;
}
#define HUD_CASES COUNT(hud_rows)
#else
#define HUD_CASES 0
#endif

const struct CTestGroup c_test_groups[] = {
#ifndef MMX4_SATURN
    { "loading_hud_sprites", 0, 0, COUNT(hud_rows), test_hud },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = HUD_CASES;
