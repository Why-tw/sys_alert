#ifndef SYSTEM_H
#define SYSTEM_H

typedef struct {
	unsigned long user;
	unsigned long nice;
	unsigned long system;
	unsigned long idle;
	unsigned long iowait;
	unsigned long irq;
	unsigned long softirq;
	unsigned long steal;
} CPU_INFO;

typedef struct {
	unsigned long MemTotal;
	unsigned long MemAvailable;
	unsigned long SwapTotal;
	unsigned long SwapFree;
	unsigned long Dirty;
	unsigned long WriteBack;
} MEM_INFO;

typedef struct {
    char Name[256];
    char State[32];
    int Pid;
    int PPid;
    int VmRSS;
} PROC_INFO;

int read_cpus(CPU_INFO cpu_info[64]);
unsigned long ul_cpu_total(const CPU_INFO *c);
unsigned long cpu_idle(const CPU_INFO *c);
int calc_cpu_usage(int ncpu, CPU_INFO old_cpu_info[1000], CPU_INFO new_cpu_info[1000], double cpu_usage[1000]);
int read_mem(MEM_INFO *mem_info);
int read_process(PROC_INFO proc_info[1000]);

#endif
