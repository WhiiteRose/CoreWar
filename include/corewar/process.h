#ifndef _PROCESS_H_
#define _PROCESS_H_
#include "corewar/arena.h"

#define NUM_REGISTERS 16

typedef struct process_s {
    int pc;
    int carry;
    unsigned int registers[NUM_REGISTERS];
} process_t;

void process_init(process_t *process, int pc);

#endif // _PROCESS_H_