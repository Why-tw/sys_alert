#include "system.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int read_cpus(CPU_INFO cpu_info[64]) {
	int fd = open("/proc/stat", O_RDONLY);
	if (fd < 0) {
		perror("open proc/stat file");
		return -1;
	}
	char buf[8192];
	ssize_t	bytes = read(fd, buf, sizeof(buf)-1); 
	if (bytes < 0) {
		perror("read");
		close(fd);
		return -1;
	}
	close(fd);
	buf[bytes] = '\0';
	int idx = 0;
	char *line = strtok(buf, "\n");
	while (line) {
		if (idx < 64) {
			if (!strncmp(line, "cpu", 3)) {
				int ret = sscanf(line, "%*s %lu %lu %lu %lu %lu %lu %lu %lu", &cpu_info[idx].user, &cpu_info[idx].nice, &cpu_info[idx].system, &cpu_info[idx].idle, &cpu_info[idx].iowait, &cpu_info[idx].irq, &cpu_info[idx].softirq, &cpu_info[idx].steal);
			if (ret != 8) break;	
			}	
			else break;
		}
		else break;
		line = strtok(NULL, "\n");
		idx ++;
	}
	return idx;
}

unsigned long ul_cpu_total(const CPU_INFO *c) {
    return c->user + c->nice + c->system + c->idle +
           c->iowait + c->irq + c->softirq + c->steal;
}

unsigned long cpu_idle(const CPU_INFO *c) {
    return c->idle + c->iowait;
}

int get_cpus_usage(double cpu_usage[64]) {
    CPU_INFO prev[64], curr[64];
    int ncpu1 = read_cpus(prev);
    sleep(1);
    int ncpu2 = read_cpus(curr);
	if (ncpu2 < 0) return -1;
	if (ncpu2 < ncpu1) ncpu1 = ncpu2;
    for (int i = 0; i < ncpu1; i++) {
        unsigned long total1 = ul_cpu_total(&prev[i]);
        unsigned long total2 = ul_cpu_total(&curr[i]);
        unsigned long idle1 = cpu_idle(&prev[i]);
        unsigned long idle2 = cpu_idle(&curr[i]);
        unsigned long delta_total = total2 - total1;
        unsigned long delta_idle  = idle2 - idle1;
        if (delta_total == 0) {
            cpu_usage[i] = 0.0;
        } else {
            cpu_usage[i] = 100.0 * (delta_total - delta_idle) / delta_total;
        }
    }
	return ncpu2;
}


