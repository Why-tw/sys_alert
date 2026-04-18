#include "system.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

int only_number(const char *s) {
    if (s[0] == '\0') return 0;
    for (int i = 0; s[i]; i++) {
        if (!isdigit((unsigned char)s[i])) return 0;
    }
    return 1;
}

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

int calc_cpu_usage(int ncpu, CPU_INFO old_cpu_info[1000], CPU_INFO new_cpu_info[1000], double cpu_usage[1000]) {
    for (int i = 0; i < ncpu; i ++) {
        unsigned long old_total = ul_cpu_total(&old_cpu_info[i]);
        unsigned long new_total = ul_cpu_total(&new_cpu_info[i]);

        unsigned long total_delta = new_total - old_total;

        unsigned long old_idle = cpu_idle(&old_cpu_info[i]);
        unsigned long new_idle = cpu_idle(&new_cpu_info[i]);

        unsigned long idle_delta = new_idle - old_idle;
        // avoid something devided by zero and error
        if (total_delta == 0) {
            cpu_usage[i] = 0.0;
        }
        else if (total_delta < 0) {
            perror("new total smaller than old total");
            return -1;
        }
        else {
            cpu_usage[i] = 100.0 * (total_delta - idle_delta) / total_delta;
        }
    }
    return 0;
}

int read_mem(MEM_INFO *mem_info) {
	int fd = open("/proc/meminfo", O_RDONLY);
	if (fd < 0) {
		perror("open proc/meminfo file");
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
	char *line = strtok(buf, "\n");
	while (line) {
		if (!strncmp(line, "MemTotal:", 9)) {
			sscanf(line, "%*s %lu kB", &mem_info->MemTotal);
		}
		else if (!strncmp(line, "MemAvailable:", 13)) {
		    sscanf(line, "%*s %lu kB", &mem_info->MemAvailable);
		}
		else if (!strncmp(line, "SwapTotal:", 10)) {
		    sscanf(line, "%*s %lu kB", &mem_info->SwapTotal);
		}
		else if (!strncmp(line, "SwapFree:", 9)) {
		    sscanf(line, "%*s %lu kB", &mem_info->SwapFree);
		}
		else if (!strncmp(line, "Dirty:", 6)) {
		    sscanf(line, "%*s %lu kB", &mem_info->Dirty);
		}
		else if (!strncmp(line, "WriteBack:", 10)) {
		    sscanf(line, "%*s %lu kB", &mem_info->WriteBack);
		}
		line = strtok(NULL, "\n");
	}
	return 0;
}

int read_process(PROC_INFO proc_info[1000]) {
    DIR *dir = opendir("/proc");
    if (dir == NULL) {
        perror("opendir");
        return -1;
    }
    struct dirent *entry;
    int idx = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (only_number(entry->d_name)) {
            char filepath[256];
            snprintf(filepath, sizeof(filepath), "/proc/%s/status", entry->d_name);
            PROC_INFO cur_proc;
            char buf[4096];
            int fd = open(filepath, O_RDONLY);
            if (fd == -1) {
                perror("open process file");
                return -1;
            }
            ssize_t n = read(fd, buf, sizeof(buf)-1);
            close(fd);
            if (n <= 0) return -1;
            buf[n] = '\0';
            char *line = strtok(buf, "\n");
            while (line) {
                if (!strncmp(line, "Name:", 5)) {
                    sscanf(line, "%*s %s", proc_info[idx].Name);
                }
                else if (!strncmp(line, "State:", 6)) {
                    sscanf(line, "%*s %s %*s", proc_info[idx].State);
                }
                else if (!strncmp(line, "Pid:", 4)) {
                    sscanf(line, "%*s %d", &proc_info[idx].Pid);
                }
                else if (!strncmp(line, "PPid:", 5)) {
                    sscanf(line, "%*s %d", &proc_info[idx].PPid);
                }
                else if (!strncmp(line, "VmRSS:", 6)) {
                    sscanf(line, "%*s %d", &proc_info[idx].VmRSS);
                }
                line = strtok(NULL, "\n");
            }
            idx ++;
        }
    }
    return idx;
}
