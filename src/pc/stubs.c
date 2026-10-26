
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long mmx4_pc_frame_number(void);
long mmx4_pc_replay_frame(void);

struct RideArmorObj;
static const char* mmx4_pc_seen_stubs[2048];
static size_t mmx4_pc_seen_stub_count;
static int mmx4_pc_stub_continue = -1;

static int mmx4_pc_stub_first_visit(const char* name)
{
    size_t i;

    for (i = 0; i < mmx4_pc_seen_stub_count; i++) {
        if (mmx4_pc_seen_stubs[i] == name)
            return 0;
    }
    if (mmx4_pc_seen_stub_count < sizeof(mmx4_pc_seen_stubs) / sizeof(mmx4_pc_seen_stubs[0]))
        mmx4_pc_seen_stubs[mmx4_pc_seen_stub_count++] = name;
    return 1;
}

static void mmx4_pc_unimplemented(const char* name)
{
    if (mmx4_pc_stub_continue < 0)
        mmx4_pc_stub_continue = getenv("MMX4_PC_STUB_CONTINUE") != NULL;
    if (!mmx4_pc_stub_continue) {
        fprintf(stderr,
            "MMX4 PC: unimplemented traced game function at replay sample %ld: %s\n",
            mmx4_pc_replay_frame(), name);
        assert(!"undecompiled function-table target reached");
        abort();
    }
    if (mmx4_pc_stub_first_visit(name)) {
        fprintf(stderr, "MMX4 PC: stub visit %zu frame %lu: %s\n",
            mmx4_pc_seen_stub_count, mmx4_pc_frame_number(), name);
        fflush(stderr);
    }
}

#define PC_GAME_STUB(name)                \
    __attribute__((weak)) void name(void) \
    {                                     \
        mmx4_pc_unimplemented(#name);     \
    }

PC_GAME_STUB(func_8003DCD8)

PC_GAME_STUB(func_800154E8)
PC_GAME_STUB(func_80018788)
PC_GAME_STUB(func_80018B88)
PC_GAME_STUB(func_8002217C)
PC_GAME_STUB(func_80028690)
PC_GAME_STUB(func_80028E24)
PC_GAME_STUB(func_8002588C)
PC_GAME_STUB(func_800AF95C)

PC_GAME_STUB(ChangeTh)
PC_GAME_STUB(CloseTh)
PC_GAME_STUB(OpenTh)
PC_GAME_STUB(dmy_SsContBankChange)
PC_GAME_STUB(dmy_SsContDamper)
PC_GAME_STUB(dmy_SsContDataEntry)
PC_GAME_STUB(dmy_SsContExpression)
PC_GAME_STUB(dmy_SsContExternal)
PC_GAME_STUB(dmy_SsContNrpn1)
PC_GAME_STUB(dmy_SsContNrpn2)
PC_GAME_STUB(dmy_SsContPanpot)
PC_GAME_STUB(dmy_SsContResetAll)
PC_GAME_STUB(dmy_SsContRpn2)
PC_GAME_STUB(dmy_SsGetMetaEvent)
PC_GAME_STUB(dmy_SsSetNrpnVabAttr0)
PC_GAME_STUB(dmy_SsSetNrpnVabAttr1)
PC_GAME_STUB(dmy_SsSetNrpnVabAttr10)
PC_GAME_STUB(dmy_SsSetNrpnVabAttr11)
PC_GAME_STUB(dmy_SsSetNrpnVabAttr12)
PC_GAME_STUB(dmy_SsSetNrpnVabAttr13)
PC_GAME_STUB(dmy_SsSetNrpnVabAttr14)
PC_GAME_STUB(dmy_SsSetNrpnVabAttr15)
PC_GAME_STUB(dmy_SsSetNrpnVabAttr16)
PC_GAME_STUB(dmy_SsSetNrpnVabAttr17)
PC_GAME_STUB(dmy_SsSetNrpnVabAttr18)
PC_GAME_STUB(dmy_SsSetNrpnVabAttr19)
PC_GAME_STUB(dmy_SsSetNrpnVabAttr2)
PC_GAME_STUB(dmy_SsSetNrpnVabAttr3)
PC_GAME_STUB(dmy_SsSetNrpnVabAttr4)
PC_GAME_STUB(dmy_SsSetNrpnVabAttr5)
PC_GAME_STUB(dmy_SsSetNrpnVabAttr6)
PC_GAME_STUB(dmy_SsSetNrpnVabAttr7)
PC_GAME_STUB(dmy_SsSetNrpnVabAttr8)
PC_GAME_STUB(dmy_SsSetNrpnVabAttr9)
PC_GAME_STUB(dmy_SsSetPitchBend)
PC_GAME_STUB(func_800B60BC)
PC_GAME_STUB(func_800D9C84)
PC_GAME_STUB(func_80098630)
PC_GAME_STUB(func_80098AF8)
PC_GAME_STUB(func_80098F88)
PC_GAME_STUB(func_80099118)
PC_GAME_STUB(func_8009B85C)
PC_GAME_STUB(func_800A03F4)
PC_GAME_STUB(func_800AE450)
PC_GAME_STUB(func_800BC92C)
PC_GAME_STUB(boss_door_wait_player)
PC_GAME_STUB(boss_door_walk_through)
PC_GAME_STUB(boss_door_close)
PC_GAME_STUB(trap_floor_open)
PC_GAME_STUB(func_800D802C)
PC_GAME_STUB(func_800DA2D4)
PC_GAME_STUB(func_8002A098)
PC_GAME_STUB(func_8001540C)
PC_GAME_STUB(func_80025188)
PC_GAME_STUB(func_800253F0)
PC_GAME_STUB(func_80028FEC)
PC_GAME_STUB(func_800D3C58)
PC_GAME_STUB(func_800567C4)
PC_GAME_STUB(func_80058194)
PC_GAME_STUB(func_80061F2C)
PC_GAME_STUB(func_8005E5C0)
PC_GAME_STUB(func_8006AE80)
PC_GAME_STUB(func_80054D8C)
PC_GAME_STUB(func_80085460)
PC_GAME_STUB(func_800B9F38)
PC_GAME_STUB(func_800CE388)
PC_GAME_STUB(func_800D0E48)
PC_GAME_STUB(func_800D1B44)
PC_GAME_STUB(func_800D3084)

PC_GAME_STUB(func_80045DD8)
PC_GAME_STUB(func_8005077C)
PC_GAME_STUB(func_8005DC58)
PC_GAME_STUB(func_8006F5F4)
PC_GAME_STUB(func_8006F86C)
PC_GAME_STUB(func_8009027C)
PC_GAME_STUB(func_8009E8E0)
PC_GAME_STUB(func_800B6660)
PC_GAME_STUB(func_800889DC)
