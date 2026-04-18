#include <stdio.h>
#include "system.h"


void clear_windows(void) {
    printf("\033[H\033[J");
}

void draw_home(void) {
    printf("home: 1\ndraw cpu: 2\ndraw mem: 3\ndraw proc: 4\n");
}

void draw_cpu(double cpu_usage[64], int ncpu) {
    for (int i = 0; i < ncpu; i ++) {
        if (i == 0) printf("CPU total: %.2f %%\n", cpu_usage[i]);
        else printf("CPU%d: %.2f %%\n", i - 1, cpu_usage[i]);
	}
}

void draw_mem(MEM_INFO mem_info) {
    printf("MemTotal: %lu kB\nMemAvilable: %lu kB\nSwapTotal: %lu kB\nSwapFree: %lu kB\nDirty: %lu kB\nWriteBack: %lu kB\n", mem_info.MemTotal, mem_info.MemAvailable, mem_info.SwapTotal, mem_info.SwapFree, mem_info.Dirty, mem_info.WriteBack);
}

void draw_proc(PROC_INFO proc_info[1000]) {
    for (int idx = 0; idx < 5; idx ++) {
        printf("Name: %s\nState: %s\nPid: %d\nPPid: %d\nVmRSS: %d\n", proc_info[idx].Name, proc_info[idx].State, proc_info[idx].Pid, proc_info[idx].PPid, proc_info[idx].VmRSS);
    }
}
