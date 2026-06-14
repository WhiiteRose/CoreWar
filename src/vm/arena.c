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

unsigned short arena_read_u16(arena_t *arena, int addr)
{
    int wrapped_addr = arena_wrap_addr(addr);
    unsigned char high_byte = arena->memory[wrapped_addr];
    unsigned char low_byte = arena->memory[arena_wrap_addr(wrapped_addr + 1)];
    return (high_byte << 8) | low_byte;
}

void arena_write_u16(arena_t *arena, int addr, unsigned short value)
{
    int wrapped_addr = arena_wrap_addr(addr);
    arena->memory[wrapped_addr] = (value >> 8) & 0xFF;
    arena->memory[arena_wrap_addr(wrapped_addr + 1)] = value & 0xFF;
}

unsigned int arena_read_u32(arena_t *arena, int addr)
{
    int wrapped_addr = arena_wrap_addr(addr);
    unsigned char b0 = arena->memory[wrapped_addr];
    unsigned char b1 = arena->memory[arena_wrap_addr(wrapped_addr + 1)];
    unsigned char b2 = arena->memory[arena_wrap_addr(wrapped_addr + 2)];
    unsigned char b3 = arena->memory[arena_wrap_addr(wrapped_addr + 3)];
    return (b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
}

void arena_write_u32(arena_t *arena, int addr, unsigned int value)
{
    int wrapped_addr = arena_wrap_addr(addr);
    arena->memory[wrapped_addr] = (value >> 24) & 0xFF;
    arena->memory[arena_wrap_addr(wrapped_addr + 1)] = (value >> 16) & 0xFF;
    arena->memory[arena_wrap_addr(wrapped_addr + 2)] = (value >> 8) & 0xFF;
    arena->memory[arena_wrap_addr(wrapped_addr + 3)] = value & 0xFF;
}