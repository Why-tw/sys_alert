#include "ui.h"
#include <stdio.h>
#include "system.h"


void clear_windows(void) {
    printf("\033[H\033[J");
}

void draw_home(ERROR_INFO error_info[10], int n) {
    printf("[1] HOME [2] CPU [3] PROC [4] MEM [q] QUIT\n\n");
    printf("ERRORS: \n\n");
    for (int i = 0; i < n; i ++) {
        if (error_info[i].status == 1) printf("\033[32m%s%.2f%%\033[0m\n" , error_info[i].name, error_info[i].val);
        else if (error_info[i].status == 2) printf("\033[33m%s%.2f%%\033[0m\n" , error_info[i].name, error_info[i].val);
        else if (error_info[i].status == 3) printf("\033[31m%s%.2f%%\033[0m\n" , error_info[i].name, error_info[i].val);
    }
}

void draw_cpu(double cpu_usage[64], int ncpu) {
    for (int i = 0; i < ncpu; i ++) {
        if (i == 0) printf("CPU total: %.2f %%\n", cpu_usage[i]);
        else printf("CPU%d: %.2f %%\n", i - 1, cpu_usage[i]);
	}
}

void draw_mem(MEM_INFO mem_info) {
    printf("MemUsage: %2.f%%\nMemTotal: %lu kB\nMemAvilable: %lu kB\nSwapTotal: %lu kB\nSwapFree: %lu kB\nDirty: %lu kB\nWriteBack: %lu kB\n",mem_info.MemUsage, mem_info.MemTotal, mem_info.MemAvailable, mem_info.SwapTotal, mem_info.SwapFree, mem_info.Dirty, mem_info.WriteBack, mem_info.MemUsage);
}

void draw_proc(PROC_INFO proc_info[1000]) {
    for (int idx = 0; idx < 5; idx ++) {
        printf("Name: %s\nState: %s\nPid: %d\nPPid: %d\nVmRSS: %d\n", proc_info[idx].Name, proc_info[idx].State, proc_info[idx].Pid, proc_info[idx].PPid, proc_info[idx].VmRSS);
    }
}
