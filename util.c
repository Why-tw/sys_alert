#include "system.h"
#include <linux/limits.h>
#include <string.h>
#include <stdio.h>

int detect_cpu_usage_error(double cpu_usage[], ERROR_INFO err_info[], int ncpu, int cur_idx) {
    for (int i = 0; i < ncpu; i ++) {
        if (cpu_usage[i] > 50) {
            snprintf(err_info[cur_idx].name, sizeof(err_info[cur_idx].name), "CPU%d usage: ", i-1);
            err_info[cur_idx].val = cpu_usage[i];
            err_info[cur_idx].status = 1;
            if (err_info[cur_idx].val > 70) err_info[cur_idx].status = 2;
            if (err_info[cur_idx].val > 90) err_info[cur_idx].status = 3;
            cur_idx ++;
        }
    }
    return cur_idx;
}

int detect_memory_usage_error(MEM_INFO mem_info, ERROR_INFO err_info[], int cur_idx) {
    if (mem_info.MemUsage > 50) {
        strcpy(err_info->name, "Memory usage: ");
        err_info->val = mem_info.MemUsage;
        err_info->status = 1;
        if (mem_info.MemUsage > 70) err_info->status = 2;
        if (mem_info.MemUsage > 90) err_info->status = 3;
    }
    return cur_idx+1;
}
