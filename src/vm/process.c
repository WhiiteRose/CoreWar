#include "corewar/process.h"
#include "corewar/arena.h"

void process_init(process_t *process, int pc)
{
    process->pc = arena_wrap_addr(pc);
    process->carry = 0;
    for (int i = 0; i < NUM_REGISTERS; i++) {
        process->registers[i] = 0;
    }
}