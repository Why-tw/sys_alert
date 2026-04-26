#ifndef UTIL_H
#define UTIL_H

#include "system.h"

int detect_cpu_usage_error(double cpu_usage[], ERROR_INFO err_info[], int ncpu, int cur_idx);
int detect_memory_usage_error(MEM_INFO mem_info, ERROR_INFO err_info[], int cur_idx);
#endif
