#include "include/collect.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "include/types.h"

int read_cpu(CPU_INFO cpu_info[]) {
    int fd = open("/proc/stat", O_RDONLY);
    char buf[8192];
    ssize_t bytes = read(fd, buf, sizeof(buf)-1);
    buf[bytes] = '\0';
    int idx = 0;
    char *line = strtok(buf, "\n");
    while (line != NULL) {
        if (idx >= 64) break;
        if (!strncmp(line, "cpu", 3)) {
            int ret = sscanf(line, "%*s %lu %lu %lu %lu %lu %lu %lu %lu", &cpu_info[idx].user, &cpu_info[idx].nice, &cpu_info[idx].system, &cpu_info[idx].idle, &cpu_info[idx].iowait, &cpu_info[idx].irq, &cpu_info[idx].softirq, &cpu_info[idx].steal);
            idx ++;
        }
        line = strtok(NULL, "\n");
    }
    close(fd);
    return idx;
}

int read_mem(MEM_INFO* mem_info) {
    int fd = open("/proc/meminfo", O_RDONLY);
    char buf[8192];
    ssize_t bytes = read(fd, buf, sizeof(buf)-1);
    buf[bytes] = '\0';
    char *line = strtok(buf, "\n");
    while (line != NULL) {
        if (!strncmp(line, "MemTotal", 8)) sscanf(line, "%*s %lu %*s", &mem_info->MemTotal);
        else if (!strncmp(line, "MemAvailable", 12)) sscanf(line, "%*s %lu %*s", &mem_info->MemAvailable);
        else if (!strncmp(line, "MemFree", 7)) sscanf(line, "%*s %lu %*s", &mem_info->MemFree);
        else if (!strncmp(line, "Dirty", 5)) sscanf(line, "%*s %lu %*s", &mem_info->Dirty);
        line = strtok(NULL, "\n");
    }
    close(fd);
    return 0;
}
