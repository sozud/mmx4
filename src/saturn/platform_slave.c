#include "common.h"
#include "saturn/platform.h"

#define SMPC_BUSY 1
#define SLAVE_VECTOR 0x94
#define SR_IMASK_CLEAR 0xFF0F
#define SR_IMASK_ALL 0xF0
#define FRT_TIER (*(volatile u8*)0xFFFFFE10)
#define FRT_FTCSR (*(volatile u8*)0xFFFFFE11)
#define FRT_OCRA (*(volatile u16*)0xFFFFFE60)
#define FRT_ICR (*(volatile u16*)0xFFFFFEE2)
#define FRT_INPUT_CAPTURE 0x80
#define FRT_ICIE 1
#define CACHE_THROUGH 0x20000000
#define VDP1_EWLR (*(volatile u16*)0x25D00008)
#define VDP1_EWRR (*(volatile u16*)0x25D0000A)
#define VDP1_ERASE_RIGHT 0x50EF

typedef void (*SaturnSlaveVector)(s32 vector, void (*entry)(void));
typedef void (*SaturnGfxJob)(void);
extern SaturnSlaveVector saturn_bios_set_slave_vector;
extern SaturnGfxJob saturn_gfx_job;
extern u16 saturn_sprite_pending;
extern u16 saturn_vdp1_frame_started;
void saturn_vdp1_init_commands(void);

u8 saturn_smpc_slave_on = 0x02;

u8 saturn_smpc_slave_off = 0x03;

volatile u8* saturn_smpc_command_register = (volatile u8*)0x2010001F;

volatile u8* saturn_smpc_status_register = (volatile u8*)0x20100063;

static void smpc_wait(void)
{
    while ((*saturn_smpc_status_register & SMPC_BUSY) == SMPC_BUSY) {
    }
}

void saturn_video_start(void)
{
    smpc_wait();
    *saturn_smpc_status_register = SMPC_BUSY;
    *saturn_smpc_command_register = saturn_smpc_slave_off;
    smpc_wait();
    saturn_bios_set_slave_vector(SLAVE_VECTOR, saturn_slave_main);
    *saturn_smpc_status_register = SMPC_BUSY;
    *saturn_smpc_command_register = saturn_smpc_slave_on;
    smpc_wait();
}

void saturn_slave_main(void)
{
    _builtin_set_cr((_builtin_get_cr() & SR_IMASK_CLEAR) | SR_IMASK_ALL);
    FRT_ICR = 0;
    FRT_OCRA = 0;
    FRT_TIER = FRT_ICIE;
    for (;;) {
        while ((FRT_FTCSR & FRT_INPUT_CAPTURE) != FRT_INPUT_CAPTURE) {
        }
        FRT_FTCSR = 0;
        (*(SaturnGfxJob*)((u32)&saturn_gfx_job + CACHE_THROUGH))();
        saturn_gfx_job = NULL;
    }
}

void saturn_vdp1_erase_setup(void)
{
    VDP1_EWLR = 0;
    VDP1_EWRR = VDP1_ERASE_RIGHT;
    saturn_vdp1_init_commands();
}

void saturn_stage_commit_video(void)
{
    saturn_vdp1_erase_setup();
    saturn_sprite_pending = 1;
    saturn_vdp1_frame_started = 1;
}
