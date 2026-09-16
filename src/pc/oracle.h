#ifndef MMX4_PC_ORACLE_H
#define MMX4_PC_ORACLE_H

void mmx4_oracle_capture_object_changes(unsigned long frame);
void mmx4_pc_object_log_dump(void);
void mmx4_pc_frame_end(void);
void mmx4_pc_write_replay_frame(long frame);

#endif
