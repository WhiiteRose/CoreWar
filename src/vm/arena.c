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

uint8_t arena_read_u8(arena_t *arena, int addr)
{
    int wrapped_addr = arena_wrap_addr(addr);
    return arena->memory[wrapped_addr];
}

void arena_write_u8(arena_t *arena, int addr, uint8_t value)
{
    int wrapped_addr = arena_wrap_addr(addr);
    arena->memory[wrapped_addr] = value;
}

uint16_t arena_read_u16(arena_t *arena, int addr)
{
    int wrapped_addr = arena_wrap_addr(addr);
    uint8_t high_byte = arena->memory[wrapped_addr];
    uint8_t low_byte = arena->memory[arena_wrap_addr(wrapped_addr + 1)];
    return (high_byte << 8) | low_byte;
}

void arena_write_u16(arena_t *arena, int addr, uint16_t value)
{
    int wrapped_addr = arena_wrap_addr(addr);
    arena->memory[wrapped_addr] = (value >> 8) & 0xFF;
    arena->memory[arena_wrap_addr(wrapped_addr + 1)] = value & 0xFF;
}

uint32_t arena_read_u32(arena_t *arena, int addr)
{
    int wrapped_addr = arena_wrap_addr(addr);
    uint8_t b0 = arena->memory[wrapped_addr];
    uint8_t b1 = arena->memory[arena_wrap_addr(wrapped_addr + 1)];
    uint8_t b2 = arena->memory[arena_wrap_addr(wrapped_addr + 2)];
    uint8_t b3 = arena->memory[arena_wrap_addr(wrapped_addr + 3)];
    return ((uint32_t)b0 << 24) | ((uint32_t)b1 << 16) | ((uint32_t)b2 << 8) | (uint32_t)b3;
}

void arena_write_u32(arena_t *arena, int addr, uint32_t value)
{
    int wrapped_addr = arena_wrap_addr(addr);
    arena->memory[wrapped_addr] = (value >> 24) & 0xFF;
    arena->memory[arena_wrap_addr(wrapped_addr + 1)] = (value >> 16) & 0xFF;
    arena->memory[arena_wrap_addr(wrapped_addr + 2)] = (value >> 8) & 0xFF;
    arena->memory[arena_wrap_addr(wrapped_addr + 3)] = value & 0xFF;
}