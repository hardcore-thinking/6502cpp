#ifndef ADDRESSING_MODE_HPP
#define ADDRESSING_MODE_HPP

#include "types.hpp"

/*
Form of an instruction : AAA BBB CC

- AAA and CC are the opcode of the instruction
- BBB is the addressing mode
*/

constexpr Byte ADDRESSING_MODE_MASK = 0b00011100; // $1C
constexpr Byte OPCODE_MASK          = 0b11100011; // $E3

// For the following, these 8 instructions are included : 
// ADC, AND, CMP, EOR, LDA, ORA, SBC (STA is also included as an exception since it only lacks IMMEDIATE mode)
enum class FULL_ADDRESSING_MODES_SET : Byte {
	ZEROPAGE_PRE_X   = 0b00000000, // $00
	ZEROPAGE         = 0b00000100, // $04
	IMMEDIATE        = 0b00001000, // $08
	ABSOLUTE         = 0b00001100, // $0C
	ZEROPAGE_POST_Y  = 0b00010000, // $10
	ZEROPAGE_X       = 0b00010100, // $14
	ABSOLUTE_Y       = 0b00011000, // $18
	ABSOLUTE_X       = 0b00011100  // $1C
};

// For the following, these 13 instructions are included : 
// ASL (X), BIT (_), CPX (_), CPY (_), DEC (X), INC (X), LDX (Y), LDY (X), LSR (X), ROL (X), ROR (X), STX (Y), STY (X)
enum class PARTIAL_ADDRESSING_MODES_SET : Byte {
	IMMEDIATE        = 0b00000000, // $00
	ZEROPAGE         = 0b00000100, // $04
	ACCUMULATOR      = 0b00001000, // $08
	ABSOLUTE         = 0b00001100, // $0C
	ZEROPAGE_INDEXED = 0b00010100, // $14, could be X or Y depending on the instruction used
	ABSOLUTE_INDEXED = 0b00011100  // $1C, could be X or Y depending on the instruction used
};

enum class JMP_ADDRESSING_MODES : Byte {
	ABSOLUTE         = 0x4C,
	INDIRECT         = 0x6C
};

enum class INDEX : Byte {
	UNUSED,
	INDEX_X,
	INDEX_Y
};

enum class BYTES_USED : size_t {
	ONE_BYTE = 1,
	TWO_BYTES,
	THREE_BYTES
};

enum class ARITHMETIC_OPERATION : Byte {
	NO_OPERATION,
	ADDITION,
	SUBTRACTION
};

#endif // ADDRESSING_MODE_HPP