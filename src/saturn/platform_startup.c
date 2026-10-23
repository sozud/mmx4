#include "common.h"
#include "saturn/platform.h"

#define SMPC_RETRIES 0x400
#define SMPC_BOOT_DELAY 0xE00
#define SMPC_COMMAND_INTBACK 2
#define SMPC_INTBACK_PARAMETER 12
#define SR_IMASK_CLEAR 0xFF0F
#define SR_IMASK_ALL 0xF0
#define SCU_MASK_ALL (-1)
#define SCU_MASK_RESET 0xBFFF

typedef void (*SaturnScuMask)(s32 mask, s32 bits);

extern volatile u16 saturn_frame_request;
extern volatile u16 saturn_vdp1_phase;
extern volatile u16 saturn_frame_ready;
extern volatile u16 saturn_peripheral_ready;
extern u16 saturn_vdp1_uploaded_pending;
extern u16 saturn_sprite_pending;
extern u32 saturn_smpc_attempts;
extern volatile s32 saturn_smpc_result;
extern u32 saturn_peripheral_attempts;
extern u8 saturn_smpc_status;
extern u8 saturn_smpc_output[];
extern u8* volatile saturn_peripheral_record;
extern u8 saturn_smpc_parameters[];
extern u8 saturn_reset_flag_a;
extern u8 saturn_reset_flag_b;
extern u8 saturn_save_options[];
extern u16 saturn_button_masks[];
extern SaturnScuMask saturn_bios_change_scu_mask;
s32 saturn_smpc_command(s32 command, s32 parameter, s32 count, void* output, s32 wait);
s32 saturn_peripheral_query(void* data, void* work);
void saturn_stage_commit_video(void);
__attribute__((noipa)) void saturn_frame_finish(void);
void saturn_vdp1_present(void);
__attribute__((noipa)) void saturn_vdp1_init_commands(void);
__attribute__((noipa)) void saturn_vdp1_upload_commands(void);
extern volatile u16 saturn_vdp1_status;
extern volatile u16 saturn_vdp1_command_0;
extern volatile u16 saturn_vdp1_command_1;
extern volatile u32 saturn_frame_counter;
void saturn_entry(void);

static void wait_for_frame(void)
{
    while (saturn_frame_ready == 0) {
    }
    while (saturn_peripheral_ready == 0) {
    }
}

static void request_frame(void)
{
    saturn_frame_request = 1;
    saturn_vdp1_phase = 1;
    wait_for_frame();
}

void saturn_peripheral_initialize(void)
{
    volatile s32 delay;
    request_frame();
    saturn_smpc_command(0, 0, 0, 0, 0);
    for (delay = SMPC_BOOT_DELAY; delay != 0; delay -= 2) {
    }
    saturn_smpc_attempts = 0;
    do {
        saturn_peripheral_record = saturn_smpc_status ? saturn_smpc_output : NULL;
        saturn_smpc_attempts++;
        if (saturn_smpc_attempts - 1 > SMPC_RETRIES) {
            break;
        }
    } while (saturn_peripheral_record == NULL);
    request_frame();
    request_frame();
    saturn_peripheral_attempts = 0;
    do {
        saturn_smpc_result = saturn_smpc_command(SMPC_COMMAND_INTBACK, SMPC_INTBACK_PARAMETER, SMPC_COMMAND_INTBACK, saturn_smpc_parameters, 0);
        saturn_peripheral_attempts++;
        if (saturn_peripheral_attempts - 1 > SMPC_RETRIES) {
            break;
        }
    } while (saturn_smpc_result != 0);
    request_frame();
    saturn_peripheral_attempts = 0;
    do {
        saturn_smpc_result = saturn_peripheral_query(&saturn_peripheral_data, &saturn_peripheral_work);
        saturn_peripheral_attempts++;
        if (saturn_peripheral_attempts - 1 > SMPC_RETRIES) {
            break;
        }
    } while (saturn_smpc_result != 0);
    request_frame();
}

static void present_frame(void)
{
    saturn_frame_request = 1;
    saturn_frame_ready = 0;
    wait_for_frame();
    if (saturn_vdp1_uploaded_pending) {
        saturn_vdp1_present();
    }
}

void saturn_soft_restart(void)
{
    u32 i;
    saturn_reset_flag_a = 1;
    saturn_reset_flag_b = 1;
    for (i = 0; i < 16; i++) {
        ((u16*)(saturn_save_options + 2))[i] = saturn_button_masks[i];
    }
    saturn_stage_commit_video();
    saturn_frame_finish();
    present_frame();
    saturn_vdp2_set_display(0);
    saturn_sprite_pending = 1;
    saturn_frame_finish();
    present_frame();
    saturn_sprite_pending = 1;
    saturn_frame_finish();
    _builtin_set_cr((_builtin_get_cr() & SR_IMASK_CLEAR) | SR_IMASK_ALL);
    saturn_bios_change_scu_mask(SCU_MASK_ALL, SCU_MASK_RESET);
    _builtin_set_cr(_builtin_get_cr() & SR_IMASK_CLEAR);
    saturn_entry();
}

void saturn_frame_finish(void)
{
    if (saturn_sprite_pending) {
        while (!saturn_vdp1_phase) { }
        if (saturn_vdp1_phase == 1) {
            saturn_vdp1_upload_commands();
        } else if (saturn_vdp1_phase == 3) {
            if (!saturn_vdp1_status) {
                saturn_vdp1_command_0 = 0x8000;
            } else {
                saturn_vdp1_command_0 = 0x5000;
                saturn_vdp1_command_1 = saturn_vdp1_status;
            }
        }
    } else {
        saturn_vdp1_init_commands();
        saturn_vdp1_uploaded_pending = saturn_sprite_pending;
    }
    saturn_frame_counter++;
}
