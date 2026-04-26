#ifndef UI_H
#define UI_H

#include "system.h"

typedef enum {
    SCREEN_HOME,
    SCREEN_CPU,
    SCREEN_MEM,
    SCREEN_PROC
} Screen;

void clear_windows(void);
void draw_home(ERROR_INFO[], int n);
void draw_cpu(double cpu_usage[64], int ncpu);
void draw_mem(MEM_INFO mem_info);
void draw_proc(PROC_INFO proc_info[1000]);

#endif
