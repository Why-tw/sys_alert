#include "include/analyzer.h"
#include "include/types.h"
#include <stdio.h>
#include <ncurses.h>

unsigned long ul_cpu_total(const CPU_INFO *c) {
    return c->user + c->nice + c->system + c->idle + c->iowait + c->irq + c->softirq + c->steal;
}

int calc_cpu_usage(CPU_INFO prev_cpu_info[], CPU_INFO new_cpu_info[], double cpu_usage[], const int ncpus, ALERT_STATE cpu_alert_state[]) {
    for (int i = 0; i < ncpus; i ++) {
        unsigned long prev_total = ul_cpu_total(&prev_cpu_info[i]);
        unsigned long new_total = ul_cpu_total(&new_cpu_info[i]);
        unsigned long total_delta = new_total - prev_total;
        unsigned long idle_delta = (new_cpu_info[i].idle + new_cpu_info[i].iowait) - (prev_cpu_info[i].idle + prev_cpu_info[i].iowait);
        if (total_delta == 0) cpu_usage[i] = 0.0;
        else if (total_delta < 0) {
            perror("total_delta can not smaller than zero");
            return 1;
        }
        else cpu_usage[i] = 100.0 * (total_delta - idle_delta) / total_delta;
        // alert
        if (cpu_usage[i] > 80) {
            if (cpu_alert_state[i].active == 0) {
                cpu_alert_state[i].active = 1;
                cpu_alert_state[i].duration = 0;
            }
            else {
                cpu_alert_state[i].duration ++;
            }
        }
        else {
            cpu_alert_state[i].active = 0;
            cpu_alert_state[i].duration = 0;
        }
    }
    return 0;
}

double calc_mem_usage(MEM_INFO mem_info) {
     return 100*(double)(mem_info.MemTotal-mem_info.MemAvailable) / mem_info.MemTotal;
}
