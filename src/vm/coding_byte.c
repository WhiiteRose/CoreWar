#include "corewar/coding_byte.h"

uint8_t coding_byte_get_arg_type(uint8_t coding_byte, int arg_index)
{
    switch (arg_index) {
        case 1:
            return (coding_byte >> 6) & 0x03;
        case 2:
            return (coding_byte >> 4) & 0x03;
        case 3:
            return (coding_byte >> 2) & 0x03;
        default:
            return ARG_NONE;
    }
}

uint8_t arg_type_size(uint8_t arg_type)
{
    switch (arg_type) {
        case ARG_REG:
            return 1;
        case ARG_DIR:
            return 4;
        case ARG_IND:
            return 2;
        default:
            return 0;
    }
}