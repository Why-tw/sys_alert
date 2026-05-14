#ifndef TYPES_H
#define TYPES_H

typedef struct {
    unsigned long user;
    unsigned long nice;
    unsigned long system;
    unsigned long idle;
    unsigned long iowait;
    unsigned long irq;
    unsigned long softirq;
    unsigned long steal;
} CPU_INFO;

typedef struct {
    unsigned long MemTotal;
    unsigned long MemFree;
    unsigned long MemAvailable;
    unsigned long Dirty;
} MEM_INFO;

typedef struct {
    int active;
    int duration;
} ALERT_STATE;

#endif
