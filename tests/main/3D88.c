#include "test_runtime.h"
#include "main/3D88.h"
void MyCdReadyCallback(u8, u8*);
extern s32 D_80137CC8;
static u32 sectors[2048], sectors_before[2048];
static u32 inactive(u32 row)
{
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    u32 response = 0x03020101, i;
    s32 remaining = row ? 6144 : 8192, sector = row ? 31 : 27;
    for (i = 0; i < COUNT(sectors); i++)
        sectors[i] = sectors_before[i] = 0x13570000 + i;
    D_801406AC = 0;
    D_80137CD8 = 0;
    D_80137CCC = func_80013614(row, &D_80137CC8) - 1;
    D_80137CBC = D_80137CC8;
    D_80137CC4 = (u8*)sectors;
    D_80137CEC = 0;
    MyCdReadyCallback(CdlDataReady, (u8*)&response);
    assert(D_801406AC == 0 && D_80137CD8 == 0 && D_80137CBC == remaining && D_80137CC8 == remaining && D_80137CC4 == (u8*)sectors && D_80137CCC == sector && D_80137CC0 == (row ? 1 : 2) && D_80137CEC == 0 && response == 0x03020101);
    c_test_same_words(sectors, sectors_before, sizeof(sectors));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "normal_CD_ready_callback_registered_before_read_active_flag_ignores_notification", NULL, NULL, 2, inactive } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2;
