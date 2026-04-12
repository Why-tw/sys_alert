#include "system.h"
#include <stdio.h>

int main () {
	double cpu_usage[64];
	for (int i = 0; i < 64; i ++) cpu_usage[i] = 0;
	int ncpu = get_cpus_usage(cpu_usage);
	for (int i = 0; i < ncpu; i ++) {
		printf("CPU: %d %.2f%%\n", i, cpu_usage[i]);
	}
	return 0;
}
