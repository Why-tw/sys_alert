#ifndef ANALYZER_H
#define ANALYZER_H
#include "types.h"

unsigned long ul_cpu_total(const CPU_INFO *c);

int calc_cpu_usage(CPU_INFO prev_cpu_info[], CPU_INFO new_cpu_info[], double cpu_usage[], int ncpus, ALERT_STATE cpu_alert_state[]);

double calc_mem_usage(MEM_INFO mem_info);

#endif
