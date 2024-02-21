#ifndef ADDRESSING_MODE_H
#define ADDRESSING_MODE_H

#include "types.hpp"

/*
Form of an instruction : AAA BBB CC

- AAA and CC are the opcode of the instruction
- BBB is the addressing mode

In the end we have :

- ZEROPAGE_PRE_X   -> ... 000 ..
- ZEROPAGE         -> ... 001 ..
- IMMEDIATE        -> ... 010 ..
- ABSOLUTE         -> ... 011 ..
- ZEROPAGE_POST_Y  -> ... 100 ..
- ZEROPAGE_X       -> ... 101 ..
- ABSOLUTE_Y       -> ... 110 ..
- ABSOLUTE_X       -> ... 111 ..
*/

#include "types.hpp"

constexpr byte ADDRESSING_MODE_MASK = 0b00011100;

enum class ADDRESSING_MODES {
	ZEROPAGE_PRE_X   = 0b00000000,
	ZEROPAGE         = 0b00000100,
	IMMEDIATE        = 0b00001000,
	ABSOLUTE         = 0b00001100,
	ZEROPAGE_POST_Y  = 0b00010000,
	ZEROPAGE_X       = 0b00010100,
	ABSOLUTE_Y       = 0b00011000,
	ABSOLUTE_X       = 0b00011100
};

#endif // ADDRESSING_MODE_H