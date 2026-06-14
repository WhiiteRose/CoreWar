#ifndef _ARENA_H_
#define _ARENA_H_

#define MEM_SIZE 4096

typedef struct arena_s {
    unsigned char memory[MEM_SIZE];
} arena_t;

int arena_wrap_addr(int addr);
void arena_init(arena_t *arena);
unsigned char arena_read_u8(arena_t *arena, int addr);
void arena_write_u8(arena_t *arena, int addr, unsigned char value);
unsigned short arena_read_u16(arena_t *arena, int addr);
void arena_write_u16(arena_t *arena, int addr, unsigned short value);
unsigned int arena_read_u32(arena_t *arena, int addr);
void arena_write_u32(arena_t *arena, int addr, unsigned int value);
#endif // _ARENA_H_