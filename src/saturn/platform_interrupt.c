#include "common.h"
#include "saturn/platform.h"

#define VDP1_TVMR (*(volatile u16*)0x25D00000)
#define VDP1_FBCR (*(volatile u16*)0x25D00002)
#define VDP1_ENDR (*(volatile u16*)0x25D0000C)
#define VDP1_TVMR_ROTATE_OFF 8
#define VDP1_FBCR_MANUAL_CHANGE 3
#define FRAME_REQUESTED 1
#define FRAME_PRESENTED 2
#define VDP1_PHASE_DRAWN 1
#define VDP1_PHASE_ENDED 3
#define HBLANK_END_LINE 0xEF

extern u16 saturn_vblank_count;
extern volatile u16 saturn_frame_request;
extern u16 saturn_present_inhibit;
extern volatile u16 saturn_vdp1_phase;
extern u16 saturn_vdp1_uploaded_pending;
extern volatile u16 saturn_frame_ready;
extern volatile u16 saturn_peripheral_ready;
extern u16 saturn_vdp1_ticks;
extern u16 saturn_vdp1_end_tick;
extern u8 saturn_movie_active;
void saturn_movie_vblank(void);
void saturn_stream_vblank(void);

void saturn_interrupt_vblank_in(void)
{
    saturn_vblank_count++;
    if (saturn_frame_request == FRAME_REQUESTED) {
        if (saturn_present_inhibit == 0 && saturn_vdp1_phase == VDP1_PHASE_DRAWN) {
            if (saturn_vdp1_uploaded_pending) {
                VDP1_TVMR = VDP1_TVMR_ROTATE_OFF;
                VDP1_FBCR = VDP1_FBCR_MANUAL_CHANGE;
            }
            saturn_vdp2_frame_upload();
        }
        saturn_frame_request = FRAME_PRESENTED;
    }
    if (saturn_movie_active) {
        saturn_movie_vblank();
    }
    saturn_frame_ready = 1;
    saturn_peripheral_ready = 0;
}

void saturn_interrupt_vblank_out(void)
{
    if (saturn_frame_request == FRAME_PRESENTED) {
        if (saturn_present_inhibit == 0 && saturn_vdp1_phase == VDP1_PHASE_DRAWN && saturn_vdp1_uploaded_pending) {
            VDP1_TVMR = 0;
        }
        saturn_frame_request = 0;
    }
    saturn_stream_vblank();
    saturn_cd_vblank();
    saturn_vdp1_ticks = 0;
    saturn_frame_ready = 0;
    saturn_peripheral_ready = 1;
}

void saturn_interrupt_hblank(void)
{
    if (saturn_vdp1_phase == 0 && saturn_vdp1_ticks > HBLANK_END_LINE && saturn_vdp1_uploaded_pending) {
        VDP1_ENDR = 0;
        saturn_vdp1_phase = VDP1_PHASE_ENDED;
    }
    saturn_vdp1_ticks++;
}

void saturn_interrupt_dma(void)
{
    saturn_vdp1_phase = VDP1_PHASE_DRAWN;
    saturn_vdp1_end_tick = saturn_vdp1_ticks;
}
