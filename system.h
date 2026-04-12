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

void init_cpu_info(CPU_INFO cpu_info);
int read_cpus(CPU_INFO cpu_info[64]);
unsigned long ul_cpu_total(const CPU_INFO *c);
unsigned long cpu_idle(const CPU_INFO *c);
int get_cpus_usage(double cpu_usage[64]);

#endif
