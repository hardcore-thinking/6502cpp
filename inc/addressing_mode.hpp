#ifndef ADDRESSING_MODE_H
#define ADDRESSING_MODE_H

#include "types.hpp"

/*
Different modes :
 - IMPLIED
 - IMMEDIATE
 - INDIRECT
 - RELATIVE
 - ACCUMULATOR
 - ZEROPAGE
 - ZEROPAGE_X
 - ZEROPAGE_Y
 - ZEROPAGE_PRE_X
 - ZEROPAGE_POST_Y
 - ABSOLUTE
 - ABSOLUTE_X
 - ABSOLUTE_Y
*/

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

/*
Branching exceptions :

!! branching doesn't use the method above !!
!! branching all end with 100 00 !!
!! the three MSBs selects the type of branching !!

In the end we have :

- BPL -> $10 -> 001 100 00
- BVC -> $50 -> 010 100 00
- BMI -> $30 -> 011 100 00
- BCC -> $90 -> 100 100 00
- BCS -> $B0 -> 101 100 00
- BNE -> $D0 -> 110 100 00
- BEQ -> $F0 -> 111 100 00
*/

enum class ADDRESSING_MODES_ADC : byte {
	ZEROPAGE_PRE_X   = 0x61, // 011 000 01
	ZEROPAGE         = 0x65, // 011 001 01
	IMMEDIATE        = 0x69, // 011 010 01
	ABSOLUTE         = 0x6D, // 011 011 01
	ZEROPAGE_POST_Y  = 0x71, // 011 100 01
	ZEROPAGE_X       = 0x75, // 011 101 01
	ABSOLUTE_Y       = 0x79, // 011 110 01
	ABSOLUTE_X       = 0x7D  // 011 111 01
};

enum class ADDRESSING_MODES_AND : byte {
	ZEROPAGE_PRE_X   = 0x21, // 001 000 01
	ZEROPAGE         = 0x25, // 001 001 01
	IMMEDIATE        = 0x29, // 001 010 01
	ABSOLUTE         = 0x2D, // 001 011 01
	ZEROPAGE_POST_Y  = 0x31, // 001 100 01
	ZEROPAGE_X       = 0x35, // 001 101 01
	ABSOLUTE_Y       = 0x39, // 001 110 01
	ABSOLUTE_X       = 0x3D  // 001 111 01
};

enum class ADDRESSING_MODES_ASL : byte {
	ZEROPAGE         = 0x06, // 000 001 10
	ACCUMULATOR      = 0x0A, // 000 010 10
	ABSOLUTE         = 0x0E, // 000 011 10
	ZEROPAGE_X       = 0x16, // 000 101 10
	ABSOLUTE_X       = 0x1E  // 000 111 10
};

enum class ADDRESSING_MODES_BCC : byte {
	RELATIVE         = 0x90  // 100 100 00
};

enum class ADDRESSING_MODES_BCS : byte {
	RELATIVE         = 0xB0  // 101 100 00
};

enum class ADDRESSING_MODES_BEQ : byte {
	RELATIVE         = 0xF0  // 111 100 00
};

enum class ADDRESSING_MODES_BIT : byte {
	ZEROPAGE         = 0x24, // 001 001 00
	ABSOLUTE         = 0x2C  // 001 011 00
};

enum class ADDRESSING_MODES_BMI : byte {
	RELATIVE         = 0x30  // 001 100 00
};

enum class ADDRESSING_MODES_BNE : byte {
	RELATIVE         = 0xD0  // 110 100 00
};

enum class ADDRESSING_MODES_BPL : byte {
	RELATIVE         = 0x10  // 000 100 00
};

enum class ADDRESSING_MODES_BRK : byte {
	IMPLIED          = 0x00  // 000 000 00
};

enum class ADDRESSING_MODES_BVC : byte {
	RELATIVE         = 0x50  // 010 100 00
};

enum class ADDRESSING_MODES_BVS : byte {
	RELATIVE         = 0x70  // 011 100 00
};

enum class ADDRESSING_MODES_CLC : byte {
	IMPLIED          = 0x18  // 000 110 00
};

enum class ADDRESSING_MODES_CLD : byte {
	IMPLIED          = 0xD8  // 110 110 00
};

enum class ADDRESSING_MODES_CLI : byte {
	IMPLIED          = 0x58  // 010 110 00
};

enum class ADDRESSING_MODES_CLV : byte {
	IMPLIED          = 0xB8  // 101 110 00
};

enum class ADDRESSING_MODES_CMP : byte {
	ZEROPAGE_PRE_X   = 0xC1, // 110 000 01
	ZEROPAGE         = 0xC5, // 110 001 01
	IMMEDIATE        = 0xC9, // 110 010 01
	ABSOLUTE         = 0xCD, // 110 011 01
	ZEROPAGE_POST_Y  = 0xD1, // 110 100 01
	ZEROPAGE_X       = 0xD5, // 110 101 01
	ABSOLUTE_Y       = 0xD9, // 110 110 01
	ABSOLUTE_X       = 0xDD  // 110 111 01
};

enum class ADDRESSING_MODES_CPX : byte {
	IMMEDIATE        = 0xE0, // 111 000 00
	ZEROPAGE         = 0xE4, // 111 001 00
	ABSOLUTE         = 0xEC  // 111 011 00
};

enum class ADDRESSING_MODES_CPY : byte {
	IMMEDIATE        = 0xC0, // 110 000 00
	ZEROPAGE         = 0xC4, // 110 001 00
	ABSOLUTE         = 0xCC  // 110 011 00
};

enum class ADDRESSING_MODES_DEC : byte {
	ZEROPAGE         = 0xC6, // 110 001 10
	ABSOLUTE         = 0xCE, // 110 011 10
	ZEROPAGE_X       = 0xD6, // 110 101 10
	ABSOLUTE_X       = 0xDE  // 110 111 10
};

enum class ADDRESSING_MODES_DEX : byte {
	IMPLIED          = 0xCA  // 110 010 10
};

enum class ADDRESSING_MODES_DEY : byte {
	IMPLIED          = 0x88  // 100 010 00
};

enum class ADDRESSING_MODES_EOR : byte {
	ZEROPAGE_PRE_X   = 0x41, // 010 000 01
	ZEROPAGE         = 0x45, // 010 001 01
	IMMEDIATE        = 0x49, // 010 010 01
	ABSOLUTE         = 0x4D, // 010 011 01
	ZEROPAGE_POST_Y  = 0x51, // 010 100 01
	ZEROPAGE_X       = 0x55, // 010 101 01
	ABSOLUTE_Y       = 0x59, // 010 110 01
	ABSOLUTE_X       = 0x5D  // 010 111 01
};

enum class ADDRESSING_MODES_INC : byte {
	ZEROPAGE         = 0xE6, // 111 001 10
	ABSOLUTE         = 0xEE, // 111 011 10
	ZEROPAGE_X       = 0xF6, // 111 101 10
	ABSOLUTE_X       = 0xFE  // 111 111 10
};

enum class ADDRESSING_MODES_INX : byte {
	IMPLIED          = 0xE8  // 111 010 00
};

enum class ADDRESSING_MODES_INY : byte {
	IMPLIED          = 0xC8  // 110 010 00
};

enum class ADDRESSING_MODES_JMP : byte {
	ABSOLUTE         = 0x4C, // 010 011 00
	INDIRECT         = 0x6C  // 011 011 00
};

enum class ADDRESSING_MODES_JSR : byte {
	ABSOLUTE         = 0x20  // 001 000 00
};

enum class ADDRESSING_MODES_LDA : byte {
	ZEROPAGE_PRE_X   = 0xA1, // 101 000 01
	ZEROPAGE         = 0xA5, // 101 001 01
	IMMEDIATE        = 0xA9, // 101 010 01
	ABSOLUTE         = 0xAD, // 101 011 01
	ZEROPAGE_POST_Y  = 0xB1, // 101 100 01
	ZEROPAGE_X       = 0xB5, // 101 101 01
	ABSOLUTE_Y       = 0xB9, // 101 110 01
	ABSOLUTE_X       = 0xBD  // 101 111 01
};

enum class ADDRESSING_MODES_LDX : byte {
	IMMEDIATE        = 0xA2, // 101 000 10
	ZEROPAGE         = 0xA6, // 101 001 10
	ABSOLUTE         = 0xAE, // 101 011 10
	ZEROPAGE_Y       = 0xB6, // 101 101 10
	ABSOLUTE_Y       = 0xBE  // 101 111 10
};

enum class ADDRESSING_MODES_LDY : byte {
	IMMEDIATE        = 0xA0, // 101 000 00
	ZEROPAGE         = 0xA4, // 101 001 00
	ABSOLUTE         = 0xAC, // 101 011 00
	ZEROPAGE_X       = 0xB4, // 101 100 00
	ABSOLUTE_X       = 0xBC  // 101 111 00
};

enum class ADDRESSING_MODES_LSR : byte {
	ZEROPAGE         = 0x46, // 010 001 10
	ACCUMULATOR      = 0x4A, // 010 010 10
	ABSOLUTE         = 0x4E, // 010 011 10
	ZEROPAGE_X       = 0x56, // 010 101 10
	ABSOLUTE_X       = 0x5E  // 010 111 10
};

enum class ADDRESSING_MODES_NOP : byte {
	IMPLIED          = 0xEA  // 111 010 10
};

enum class ADDRESSING_MODES_ORA : byte {
	ZEROPAGE_PRE_X   = 0x01, // 000 000 01
	ZEROPAGE         = 0x05, // 000 001 01
	IMMEDIATE        = 0x09, // 000 010 01
	ABSOLUTE         = 0x0D, // 000 011 01
	ZEROPAGE_POST_Y  = 0x11, // 000 100 01
	ZEROPAGE_X       = 0x15, // 000 101 01
	ABSOLUTE_Y       = 0x19, // 000 110 01
	ABSOLUTE_X       = 0x1D  // 000 111 01
};

enum class ADDRESSING_MODES_PHA : byte {
	IMPLIED          = 0x48  // 010 010 00
};

enum class ADDRESSING_MODES_PHP : byte {
	IMPLIED          = 0x08  // 000 010 00
};

enum class ADDRESSING_MODES_PLA : byte {
	IMPLIED          = 0x68  // 011 010 00
};

enum class ADDRESSING_MODES_PLP : byte {
	IMPLIED          = 0x28  // 001 010 00
};

enum class ADDRESSING_MODES_ROL : byte {
	ZEROPAGE         = 0x26, // 001 001 10
	ACCUMULATOR      = 0x2A, // 001 010 10
	ABSOLUTE         = 0x2E, // 001 011 10
	ZEROPAGE_X       = 0x36, // 001 101 10
	ABSOLUTE_X       = 0x3E  // 001 111 10
};

enum class ADDRESSING_MODES_ROR : byte {
	ZEROPAGE         = 0x66, // 011 001 10
	ACCUMULATOR      = 0x6A, // 011 010 10
	ABSOLUTE         = 0x6E, // 011 011 10
	ZEROPAGE_X       = 0x76, // 011 101 10
	ABSOLUTE_X       = 0x7E  // 011 111 10
};

enum class ADDRESSING_MODES_RTI : byte {
	IMPLIED          = 0x40  // 010 000 00
};

enum class ADDRESSING_MODES_RTS : byte {
	IMPLIED          = 0x60  // 011 000 00
};

enum class ADDRESSING_MODES_SBC : byte {
	ZEROPAGE_PRE_X   = 0xE1, // 111 000 01
	ZEROPAGE         = 0xE5, // 111 001 01
	IMMEDIATE        = 0xE9, // 111 010 01
	ABSOLUTE         = 0xED, // 111 011 01
	ZEROPAGE_POST_Y  = 0xF1, // 111 100 01
	ZEROPAGE_X       = 0xF5, // 111 101 01
	ABSOLUTE_Y       = 0xF9, // 111 110 01
	ABSOLUTE_X       = 0xFD  // 111 111 01
};

enum class ADDRESSING_MODES_SEC : byte {
	IMPLIED          = 0x38  // 001 110 00
};

enum class ADDRESSING_MODES_SED : byte {
	IMPLIED          = 0xF8  // 111 110 00
};

enum class ADDRESSING_MODES_SEI : byte {
	IMPLIED          = 0x78  // 011 110 00
};

enum class ADDRESSING_MODES_STA : byte {
	ZEROPAGE_PRE_X   = 0x81, // 100 000 01
	ZEROPAGE         = 0x85, // 100 001 01
	ABSOLUTE         = 0x8D, // 100 011 01
	ZEROPAGE_POST_Y  = 0x91, // 100 100 01
	ZEROPAGE_X       = 0x95, // 100 101 01
	ABSOLUTE_Y       = 0x99, // 100 110 01
	ABSOLUTE_X       = 0x9D  // 100 111 01
};

enum class ADDRESSING_MODES_STX : byte {
	ZEROPAGE         = 0x86, // 100 001 10
	ABSOLUTE         = 0x8E, // 100 011 10
	ZEROPAGE_Y       = 0x96  // 100 101 10
	
};

enum class ADDRESSING_MODES_STY : byte {
	ZEROPAGE         = 0x84, // 100 001 00
	ABSOLUTE         = 0x8C, // 100 011 00
	ZEROPAGE_Y       = 0x94  // 100 101 00
	
};

enum class ADDRESSING_MODES_TAX : byte {
	IMPLIED          = 0xAA  // 101 010 10
};

enum class ADDRESSING_MODES_TAY : byte {
	IMPLIED          = 0xA8  // 101 010 00
};

enum class ADDRESSING_MODES_TSX : byte {
	IMPLIED          = 0xBA  // 101 110 10
};

enum class ADDRESSING_MODES_TXA : byte {
	IMPLIED          = 0x8A  // 100 010 10
};

enum class ADDRESSING_MODES_TXS : byte {
	IMPLIED          = 0x9A  // 100 110 10
};

enum class ADDRESSING_MODES_TYA : byte {
	IMPLIED          = 0x98  // 100 110 00
};

#endif // ADDRESSING_MODE_H