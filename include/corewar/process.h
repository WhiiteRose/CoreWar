#ifndef _PROCESS_H_
#define _PROCESS_H_
#include "corewar/arena.h"
#include <stdbool.h>

#define NUM_REGISTERS 16

typedef struct process_s {
    int pc;
    int carry;
    unsigned int registers[NUM_REGISTERS];
} process_t;

void process_init(process_t *process, int pc);
void process_advance_pc(process_t *process, int offset);
bool process_valid_register(int reg);
unsigned int process_read_register(process_t *process, int reg);
void process_write_register(process_t *process, int reg, unsigned int value);

#endif // _PROCESS_H_