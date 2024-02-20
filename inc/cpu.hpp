#ifndef CPU_HPP
#define CPU_HPP

#include <iostream>
#include <vector>
#include <iomanip>

#include "types.hpp"
#include "addressing_mode.hpp"
#include "tools.hpp"

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

enum class DATA_BUS_OPERATION : bool {
	WRITE = false,
	READ  = true
};

constexpr int MAX_ADDRESSABLE = 0x10000;

class CPU {
	public:
		CPU(std::vector<byte>* ram = nullptr, std::vector<byte>* rom = nullptr);

		// Debug log function
		void displayStatus() const;
		void displayRegisters() const;
		void displayStackPointer() const;
		void displayBuses() const;
		void displayProgramCounter() const;
		void displayState() const;

		void updateState(byte value);

	private:
		// ADd with Carry
		void ADC(byte opcode, byte operand);
		void ADC(byte opcode, word operand);

		// AND
		void AND(byte opcode, byte operand);
		void AND(byte opcode, word operand);

		// Arithmetical Shift Left
		void ASL(byte opcode);
		void ASL(byte opcode, byte operand);
		void ASL(byte opcode, word operand);

		// Branch on Carry Clear
		void BCC(byte opcode);

		// Branch on Carry Set
		void BCS(byte opcode);

		// Branch on EQual
		void BEQ(byte opcode);

		// BIT
		void BIT(byte opcode, byte operand);
		void BIT(byte opcode, word operand);

		// Branch on MInus
		void BMI(byte opcode);

		// Branch on Not Equal
		void BNE(byte opcode);

		// Branch on PLus
		void BPL(byte opcode);

		// BReaK
		void BRK(byte opcode);

		// Branch on oVerflow Clear
		void BVC(byte opcode);

		// Branch on oVerflow Set
		void BVS(byte opcode);

		// CLear Carry
		void CLC(byte opcode);

		// CLear Decimal
		void CLD(byte opcode);

		// CLear Interrupt
		void CLI(byte opcode); 

		// CLear oVerflow
		void CLV(byte opcode);

		// CoMPare
		void CMP(byte opcode, byte operand);
		void CMP(byte opcode, word operand);

		// ComPare X
		void CPX(byte opcode, byte operand);
		void CPX(byte opcode, word operand);

		// ComPare Y
		void CPY(byte opcode, byte operand);
		void CPY(byte opcode, word operand);

		// DECrement
		void DEC(byte opcode, byte operand);
		void DEC(byte opcode, word operand);

		// DEcrement X
		void DEX(byte opcode);
		
		// DEcrement Y
		void DEY(byte opcode);

		// Exclusif OR
		void EOR(byte opcode, byte operand);
		void EOR(byte opcode, word operand);

		// INCrement
		void INC(byte opcode, byte operand);
		void INC(byte opcode, word operand);

		// INcrement X
		void INX(byte opcode);

		// INcrement Y
		void INY(byte opcode);

		// JuMP
		void JMP(byte opcode, word operand);

		// Jump to SubRoutine
		void JSR(byte opcode, word operand);

		// LoaD A
		void LDA(byte opcode, byte operand);
		void LDA(byte opcode, word operand);

		// LoaD X
		void LDX(byte opcode, byte operand);
		void LDX(byte opcode, word operand);

		// LoaD Y
		void LDY(byte opcode, byte operand);
		void LDY(byte opcode, word operand);

		// Logical Shift Right
		void LSR(byte opcode);
		void LSR(byte opcode, byte operand);
		void LSR(byte opcode, word operand);

		// No OPeration
		void NOP(byte opcode);

		// ORA
		void ORA(byte opcode, byte operand);
		void ORA(byte opcode, word operand);

		// PusH Accumulator
		void PHA(byte opcode);

		// PusH Processor status
		void PHP(byte opcode);

		// PulL Accumulator
		void PLA(byte opcode);

		// PulL Processor status
		void PLP(byte opcode);

		// ROtate Left
		void ROL(byte opcode);
		void ROL(byte opcode, byte operand);
		void ROL(byte opcode, word operand);

		// ROtate Right
		void ROR(byte opcode);
		void ROR(byte opcode, byte operand);
		void ROR(byte opcode, word operand);

		// ReTurn from Interrupt
		void RTI(byte opcode);

		// ReTurn from Subroutine
		void RTS(byte opcode);

		// SuBtract with Carry
		void SBC(byte opcode, byte operand);
		void SBC(byte opcode, word operand);

		// SEt Carry 
		void SEC(byte opcode);

		// SEt Decimal
		void SED(byte opcode);

		// SEt Interrupt
		void SEI(byte opcode);

		// STore A
		void STA(byte opcode, byte operand);
		void STA(byte opcode, word operand);

		// STore X
		void STX(byte opcode, byte operand);
		void STX(byte opcode, word operand);
		
		// STore Y
		void STY(byte opcode, byte operand);
		void STY(byte opcode, word operand);

		// Transfer A to X
		void TAX(byte opcode);

		// Transfer A ot Y
		void TAY(byte opcode);

		// Transfer Stack pointer to X
		void TSX(byte opcode);

		// Transfer X to A
		void TXA(byte opcode);

		// Transfer X to Stack pointer
		void TXS(byte opcode);

		// Transfer Y to A
		void TYA(byte opcode);

		void setFlag(STATUS_FLAG flag);
		void unsetFlag(STATUS_FLAG flag);

		void setAddressBusFromDataBusPreIndexed();
		void setAddressBusFromDataBusPostIndexed();

	private:
		// Pins :
		// (Doesn't include RDY, VCC and VSS since this program assume 
		// the CPU is always running the moment it's ran)
		bool _readWrite         = (bool) DATA_BUS_OPERATION::READ; // 0 : Write / 1 : Read
		byte _dataBus           = (byte) 0x00;  // D0-D7
		word _addressBus        = (word) 0x0000; // A0-A15

		// Internals :
		byte _accumulator       = (byte) 0x00; // A
		byte _indexX            = (byte) 0x00; // X
		byte _indexY            = (byte) 0x00; // Y
		byte _statusFlags       = (byte) STATUS_FLAG::_; // SR
		byte _stackPointer      = (byte) 0x00; // SP
		word _programCounter    = (word) 0x0000; // PC

		// Vectors
		word _nmi = (word) 0x0000; // Non Maskable Interrupt vector
		word _res = (word) 0x0000; // RESet vector
		word _irq = (word) 0x0000; // Interrupt ReQuest vector


		// Links :
		std::vector<byte>* _ram = nullptr;
		std::vector<byte>* _rom = nullptr;
};

#endif // CPU_HPP
