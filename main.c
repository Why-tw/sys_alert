#include "include/collect.h"
#include "include/analyzer.h"
#include "include/types.h"
#include "include/ui.h"
#include <bits/time.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#define MAX_CPU 64

int main () {
    // initialize
    double cpu_usage[MAX_CPU];
    CPU_INFO prev_cpu_info[MAX_CPU];
    CPU_INFO new_cpu_info[MAX_CPU];
    MEM_INFO mem_info;
    double mem_usage;
    int ncpus = read_cpu(prev_cpu_info);
    ALERT_STATE cpu_alert_state[MAX_CPU];
    int page_state = 1; // home 1, cpu 2, mem 3

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    struct timespec last, now;
    clock_gettime(CLOCK_MONOTONIC, &last);
    int running = 1;

    while (running) {
        int ch = getch();
        if (ch != ERR) {
            switch (ch) {
                case 'q':
                    running = false;
                    break;
                case '1':
                    page_state = 1;
                    break;
                case '2':
                    page_state = 2;
                    break;
                case '3':
                    page_state = 3;
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &now);
        long elapsed_ms = (now.tv_sec - last.tv_sec) * 1000 + (now.tv_nsec - last.tv_nsec) / 1000000;

        if (elapsed_ms >= 1000) {
            read_cpu(new_cpu_info);
            calc_cpu_usage(prev_cpu_info, new_cpu_info, cpu_usage, ncpus, cpu_alert_state);
            read_mem(&mem_info);
            mem_usage = calc_mem_usage(mem_info);
            memcpy(prev_cpu_info, new_cpu_info, sizeof(prev_cpu_info));
            last = now;
        }
        erase();

        if (page_state == 1) display_home(cpu_alert_state, ncpus);
        else if (page_state == 2) display_cpu_usage(cpu_usage, ncpus);
        else if (page_state == 3) display_mem_info(mem_info, mem_usage);
        refresh();
        usleep(10000);
    }
     endwin();
     return 0;
}
