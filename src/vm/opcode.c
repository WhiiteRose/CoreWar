#include "corewar/opcode.h"

bool opcode_is_valid(uint8_t opcode)
{
    return opcode >= 0x01 && opcode <= 0x10;
}