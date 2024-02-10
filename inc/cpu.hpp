#ifndef CPU_HPP
#define CPU_HPP

#include <iostream>
#include <vector>
#include <iomanip>

#include "types.hpp"

enum class STATUS_FLAG : byte {
	N = 0b10000000,
	V = 0b01000000,
	_ = 0b00100000,
	B = 0b00010000,
	D = 0b00001000,
	I = 0b00000100,
	Z = 0b00000010,
	C = 0b00000001
};

constexpr int MAX_ADDRESSABLE = 0x10000;
// constexpr int MAX_RAM_SIZE = 0x800;
constexpr int MAX_RAM_SIZE = 0x10000;

class CPU {
	public:
		CPU(std::vector<byte>* ram = nullptr);

		// Debug log function
		void displayState() const;

		void updateState(byte value);

		void lda(byte opcode, byte operand);
		void lda(byte opcode, word operand);

		void ldx(byte opcode, byte operand);
		void ldx(byte opcode, word operand);

		void ldy(byte opcode, byte operand);
		void ldy(byte opcode, word operand);

		void sta(byte opcode, byte operand);
		void sta(byte opcode, word operand);

		void stx(byte opcode, word operand);
		void sty(byte opcode, word operand);

		// Carry flag specific functions
		void clc(); // CLear Carry
		void sec(); // SEt Carry 

		// Interrupt flag specific functions
		void cli(); // CLear Interrupt disable
		void sei(); // SEt Interrupt disable

		// Decimal flag specific functions
		void cld(); // CLear Decimal
		void sed(); // SEt Decimal

		// Overflow flag specific function
		void clv(); // CLear oVerflow

		// Interregisters transfer functions
		void tax(); // Transfer A to X
		void tay(); // Transfer A ot Y
		void tsx(); // Transfer Stack pointer
		void txa(); // Transfer X to A
		void txs(); // Transfer X to Stack pointer
		void tya(); // Transfer Y to A

		// DEC
		void dec(byte opcode, word address);

	private:
		void setFlag(STATUS_FLAG flag);
		void unsetFlag(STATUS_FLAG flag);

	private:
		std::vector<byte>* _ram = nullptr;
		word _addressBus = (word) 0x0000;
		byte _accumulator = (byte) 0x00; // A
		byte _indexX = (byte) 0x00; // X
		byte _indexY = (byte) 0x00; // Y
		byte _statusFlags = (byte) 0x00; // P
		byte _stackPointer = (byte) 0x00; // SP
		word _programCounter = (word) 0x0000; // PC
};

#endif // CPU_HPP
