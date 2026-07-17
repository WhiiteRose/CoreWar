#ifndef _OPCODE_H_
#define _OPCODE_H_

#include <stdbool.h>
#include <stdint.h>

#define OP_LIVE 1
#define OP_LD 2
#define OP_ST 3
#define OP_ADD 4
#define OP_SUB 5
#define OP_AND 6
#define OP_OR 7
#define OP_XOR 8
#define OP_ZJMP 9
#define OP_LDI 10
#define OP_STI 11
#define OP_FORK 12
#define OP_LLD 13
#define OP_LLDI 14
#define OP_LFORK 15
#define OP_AFF 16

bool opcode_is_valid(uint8_t opcode);


#endif // _OPCODE_H_