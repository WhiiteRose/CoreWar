#ifndef _CODING_BYTE_H_
#define _CODING_BYTE_H_

#include <stdint.h>

#define ARG_NONE 0
#define ARG_REG 1
#define ARG_DIR 2
#define ARG_IND 3

uint8_t coding_byte_get_arg_type(uint8_t coding_byte, int arg_index);

#endif // _CODING_BYTE_H_