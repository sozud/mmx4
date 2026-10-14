#ifndef MMX4_PC_MEMCARD_H
#define MMX4_PC_MEMCARD_H
int mmx4_pc_card_info(int port);
int mmx4_pc_card_load(int port);
int mmx4_pc_card_format(int port);
void mmx4_pc_card_list(int port, struct MemcardFileList* list, const char* pattern);
int mmx4_pc_card_read(int port, void* buffer, int size);
int mmx4_pc_card_write(int port, const void* buffer, int size);
#endif
