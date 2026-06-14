#include "corewar/arena.h"

int arena_wrap_addr(int addr)
{
    int addr_mod = addr % MEM_SIZE;

    if (addr_mod < 0) {
        addr_mod = MEM_SIZE + addr_mod;
    } 

    return addr_mod;
}

void arena_init(arena_t *arena)
{
    for (int i = 0; i < MEM_SIZE; i++) {
        arena->memory[i] = 0;
    }
}

unsigned char arena_read_u8(arena_t *arena, int addr)
{
    int wrapped_addr = arena_wrap_addr(addr);
    return arena->memory[wrapped_addr];
}

void arena_write_u8(arena_t *arena, int addr, unsigned char value)
{
    int wrapped_addr = arena_wrap_addr(addr);
    arena->memory[wrapped_addr] = value;
}