#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "system.h"
#include "ui.h"
#include "util.h"

struct termios old_termios;
void restore_termainal(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
    printf("\033[0m\n");
}
int enable_raw_mode(void){
    struct termios new_termios;
    if (tcgetattr(STDIN_FILENO, &old_termios)) {
        perror("tcgetattr");
        return -1;
    }
    new_termios = old_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) == -1) {
        perror("tcsetattr");
        return -1;
    }
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl F_GETFL");
        return -1;
    }
    if (fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl F_SETFL");
        return -1;
    }
    atexit(restore_termainal);
    return 0;
}

int main () {
    if (enable_raw_mode() < 0) return 1;
    MEM_INFO mem_info;
    double cpu_usage[1000];
    PROC_INFO proc_info[1000];
    CPU_INFO old_cpu_info[1000], new_cpu_info[1000];
    ERROR_INFO err_info[100];
    Screen state = SCREEN_HOME;
    int ncpu = read_cpus(old_cpu_info);
    int err_idx = 0;
    while (1) {
        err_idx = 0;
        clear_windows();
        read_mem(&mem_info);
        read_process(proc_info);
        read_cpus(new_cpu_info);
        calc_cpu_usage(ncpu, old_cpu_info, new_cpu_info, cpu_usage);
        err_idx = detect_cpu_usage_error(cpu_usage, err_info, ncpu, err_idx);
        err_idx = detect_memory_usage_error(mem_info, err_info, err_idx);

        char c;
        ssize_t n = read(STDIN_FILENO, &c, 1);
        if (n > 0) {
            if (c == '1') state = SCREEN_HOME;
            if (c == '2') state = SCREEN_CPU;
            if (c == '3') state = SCREEN_PROC;
            if (c == '4') state = SCREEN_MEM;
            if (c == 'q') break;
        }
        if (state == SCREEN_HOME) draw_home(err_info, err_idx);
        else if (state == SCREEN_CPU) draw_cpu(cpu_usage, ncpu);
        else if (state == SCREEN_PROC) draw_proc(proc_info);
        else if (state == SCREEN_MEM) draw_mem(mem_info);
        memcpy(old_cpu_info, new_cpu_info, sizeof(CPU_INFO) * ncpu);
        usleep(500000);
    }
    return 0;
}
