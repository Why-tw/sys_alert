#include "system.h"
#include <stdio.h>

int main () {
    double cpu_usage[64];
    MEM_INFO mem_info = {0};
    PROC_INFO proc_info[1000] = {0};
	while (1) {
		printf("\033[H\033[2J");
		for (int i = 0; i < 64; i ++) cpu_usage[i] = 0;
		int ncpu = get_cpus_usage(cpu_usage);
		for (int i = 0; i < ncpu; i ++) {
            if (i == 0) printf("CPU total: %.2f %%\n", cpu_usage[i]);
            else printf("CPU%d: %.2f %%\n", i - 1, cpu_usage[i]);
		}
		printf("\n");
		read_mem(&mem_info);
		printf("MemTotal: %lu kB\nMemAvilable: %lu kB\nSwapTotal: %lu kB\nSwapFree: %lu kB\nDirty: %lu kB\nWriteBack: %lu kB\n", mem_info.MemTotal, mem_info.MemAvailable, mem_info.SwapTotal, mem_info.SwapFree, mem_info.Dirty, mem_info.WriteBack);
		printf("\n");
		read_process(proc_info);
		printf("Name: %s\nState: %s\nPid: %d\nPPid: %d\nVmRSS: %d", proc_info[0].Name, proc_info[0].State, proc_info[0].Pid, proc_info[0].PPid, proc_info[0].VmRSS);
	}
	return 0;
}
