#include "corewar/arena.h"

int arena_wrap_addr(int addr)
{
    int addr_mod = addr % MEM_SIZE;

    if(addr_mod < 0) {
        addr_mod = MEM_SIZE + addr_mod;
    } 
    
    return addr_mod;
}