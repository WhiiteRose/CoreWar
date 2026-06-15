#ifndef _ARENA_H_
#define _ARENA_H_

#include <stdint.h>

#define MEM_SIZE 4096

typedef struct arena_s {
    uint8_t memory[MEM_SIZE];
} arena_t;

int arena_wrap_addr(int addr);
void arena_init(arena_t *arena);
uint8_t arena_read_u8(arena_t *arena, int addr);
void arena_write_u8(arena_t *arena, int addr, uint8_t value);
uint16_t arena_read_u16(arena_t *arena, int addr);
void arena_write_u16(arena_t *arena, int addr, uint16_t value);
uint32_t arena_read_u32(arena_t *arena, int addr);
void arena_write_u32(arena_t *arena, int addr, uint32_t value);
#endif // _ARENA_H_