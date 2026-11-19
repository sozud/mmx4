#ifndef GC_COLLECTION_H
#define GC_COLLECTION_H

unsigned short gc_get_screen_height(void);

int gc_get_disc_state(void);

void gc_disc_error_screen(void);

void gc_vab_open(unsigned char* head, int slot, unsigned long size);
signed char gc_vab_transfer(unsigned char* body, int slot, unsigned long size);

void* gc_get_convert_buffer(void);
void* gc_get_dvd_buffer(void);

void gc_memcpy(void* dst, const void* src, unsigned long n);
void gc_memset(void* dst, int c, unsigned long n);

void gc_set_main_flag(unsigned char value);

#endif
