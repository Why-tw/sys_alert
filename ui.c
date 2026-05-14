#include "include/ui.h"
#include "include/types.h"
#include <ncurses.h>

void display_home(ALERT_STATE cpu_alert_state[], int ncpus) {
    printw("[1] Home \t[2] CPU \t[3]MEM \t\t [q]Quit\n\n");
    printw("ERROR:\n");
    for (int i = 0; i < ncpus; i ++) {
        if (cpu_alert_state[i].active == 1 && cpu_alert_state[i].duration >=3) {
            if (i == 0) printw("Total CPU:\tusage too high\n");
            else printw("CPU%d:\t\tusage too high\n", i);
        }
    }
}

void display_cpu_usage(double cpu_usage[], int ncpus) {
    printw("Cores: %d\n", ncpus-1);
    printw("Total CPU usage: %.2f%%\n", cpu_usage[0]);
    for (int i = 1; i < ncpus; i ++) {
        printw("CPU%d: %.2f%%\n", i, cpu_usage[i]);
    }
}

void display_mem_info(MEM_INFO mem_info, double mem_usage) {
    printw("MemUsage: %.2f%%\n", mem_usage);
    printw("MemTotal: %lu kb\n", mem_info.MemTotal);
    printw("MemAvailable: %lu kb\n", mem_info.MemAvailable);
    printw("MemFree: %lu kb\n", mem_info.MemFree);
    printw("Dirty: %lu kb\n", mem_info.Dirty);
}

void test_cpu_info(CPU_INFO cpu_info[], int ncpus) {
    printw("Cores: %d\n", ncpus-1);
    printw("Total CPU: %lu\n", cpu_info[0].user);
    for (int i = 1; i < ncpus; i ++) {
        printw("CPU%d: %lu\n",i , cpu_info[i].user);
    }
}

void test_mem_info(MEM_INFO mem_info) {
    printw("MemTotal: %lu kb\n", mem_info.MemTotal);
    printw("MemAvailable: %lu kb\n", mem_info.MemAvailable);
    printw("MemFree: %lu kb\n", mem_info.MemFree);
    printw("Dirty: %lu kb\n", mem_info.Dirty);
}

void test_cpu_alert_system(ALERT_STATE cpu_alert_state[], int ncpus) {
    printw("NAME\t\tACTIVE\t\tDURATION\n");
    printw("Total CPU\t%d\t\t%d\n", cpu_alert_state[0].active, cpu_alert_state[0].duration);
    for (int i = 1; i < ncpus; i ++) {
        printw("CPU%d\t\t%d\t\t%d\n", i, cpu_alert_state[i].active, cpu_alert_state[i].duration);
    }
}
