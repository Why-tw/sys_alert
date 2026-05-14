#ifndef UI_H
#define UI_H
#include "types.h"

void display_home(ALERT_STATE cpu_alert_state[], int ncpus);

void display_cpu_usage(double cpu_usage[], int ncpus);

void display_mem_info(MEM_INFO mem_info, double mem_usage);

void test_cpu_info(CPU_INFO cpu_info[], int ncpus);

void test_mem_info(MEM_INFO mem_info);

void test_cpu_alert_system(ALERT_STATE cpu_alert_state[], int ncpus);

#endif
