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

void process_advance_pc(process_t *process, int offset)
{
    int new_pc = process->pc + offset;
    process->pc = arena_wrap_addr(new_pc);
}

bool process_valid_register(int reg)
{
    return reg >= 1 && reg <= NUM_REGISTERS;
}

uint32_t process_read_register(process_t *process, int reg)
{
    if (!process_valid_register(reg)) {
        return 0;
    }
    return process->registers[reg - 1];
}

void process_write_register(process_t *process, int reg, uint32_t value)
{
    if (!process_valid_register(reg)) {
        return;
    }
    process->registers[reg - 1] = value;
}