#ifndef CPU_HPP
#define CPU_HPP

#include <iostream>
#include <vector>
#include <iomanip>
#include <functional>

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

// Size of various memory map areas
constexpr int MAX_ADDRESSABLE = 0x10000;
constexpr int MAX_RAM_SIZE    = 0x800;
constexpr int MAX_PAGE_SIZE   = 0x100;
constexpr int MAX_STACK_SIZE  = 0x100;
constexpr int MAX_ROM_SIZE    = 0x8000;

// Vectors nibbles
constexpr word NMI_LOW    = 0xFFFA;
constexpr word NMI_HIGH   = 0xFFFB;
constexpr word RESET_LOW  = 0xFFFC;
constexpr word RESET_HIGH = 0xFFFD;
constexpr word IRQ_LOW    = 0xFFFE;
constexpr word IRQ_HIGH   = 0xFFFF;

class CPU {
	using Instruction = void (CPU::*)(void);

	public:
		CPU(std::vector<byte>* ram, word ramStart, word ramSize, std::vector<byte>* rom, word romStart, word romSize);

		// Debug log function
		void displayStatus() const;

		// Registers specific logs
		void displayAccumulator() const;
		void displayIndexX() const;
		void displayIndexY() const;
		void displayRegisters() const;

		// Stack pointer log
		void displayStackPointer() const;
		
		// Buses specific logs
		void displayAddressBus() const;
		void displayDataBus() const;
		void displayBuses() const;
		
		// Program counter log
		void displayProgramCounter() const;

		// All logs at once
		void displayState() const;

		// RAM specific display
		void displayRAM() const;
		void displayZeroPage() const;
		void displayRAMPage(byte page) const;
		void displayStack() const;
		
		// ROM display
		void displayROM(bool stopOnBreak) const;
		void displayInstructionAsBytes(size_t bytesN) const;

		// Map display
		void displayMap() const;

		// Run execution of the CPU
		void run(bool stepByStep);

	private:
		void fetchAndExecute();

		void updateState(byte value);

		// ADd with Carry
		void ADC();

		// AND
		void AND();

		// Arithmetical Shift Left
		void ASL();

		// Branch on Carry Clear
		void BCC();

		// Branch on Carry Set
		void BCS();

		// Branch on EQual
		void BEQ();

		// BIT
		void BIT();

		// Branch on MInus
		void BMI();

		// Branch on Not Equal
		void BNE();

		// Branch on PLus
		void BPL();

		// BReaK
		void BRK();

		// Branch on oVerflow Clear
		void BVC();

		// Branch on oVerflow Set
		void BVS();

		// CLear Carry
		void CLC();

		// CLear Decimal
		void CLD();

		// CLear Interrupt
		void CLI(); 

		// CLear oVerflow
		void CLV();

		// CoMPare
		void CMP();

		// ComPare X
		void CPX();

		// ComPare Y
		void CPY();

		// DECrement
		void DEC();

		// DEcrement X
		void DEX();
		
		// DEcrement Y
		void DEY();

		// Exclusif OR
		void EOR();

		// INCrement
		void INC();

		// INcrement X
		void INX();

		// INcrement Y
		void INY();

		// JuMP
		void JMP();

		// Jump to SubRoutine
		void JSR();

		// LoaD A
		void LDA();

		// LoaD X
		void LDX();

		// LoaD Y
		void LDY();

		// Logical Shift Right
		void LSR();

		// No OPeration
		void NOP();

		// ORA
		void ORA();

		// PusH Accumulator
		void PHA();

		// PusH Processor status
		void PHP();

		// PulL Accumulator
		void PLA();

		// PulL Processor status
		void PLP();

		// ROtate Left
		void ROL();

		// ROtate Right
		void ROR();

		// ReTurn from Interrupt
		void RTI();

		// ReTurn from Subroutine
		void RTS();

		// SuBtract with Carry
		void SBC();

		// SEt Carry 
		void SEC();

		// SEt Decimal
		void SED();

		// SEt Interrupt
		void SEI();

		// STore A
		void STA();

		// STore X
		void STX();
		
		// STore Y
		void STY();

		// Transfer A to X
		void TAX();

		// Transfer A ot Y
		void TAY();

		// Transfer Stack pointer to X
		void TSX();

		// Transfer X to A
		void TXA();

		// Transfer X to Stack pointer
		void TXS();

		// Transfer Y to A
		void TYA();

		void setFlag(STATUS_FLAG flag);
		void unsetFlag(STATUS_FLAG flag);

		bool isSet(STATUS_FLAG flag);

		void useFullAddressingModeSet();
		void usePartialAddressingModeSet(INDEX index = INDEX::UNUSED);

		void incrementProgramCounter();

		inline void setDataBusFromByteAtPC();
		inline void setDataBusFromAddressBus();

		void setAddressBusFromTwoNextBytesInROM();

		void setProgramCounterFromResetVector();

	private:
		// Pins
		// (Doesn't include RDY, VCC and VSS since this program assume 
		// the CPU is always running the moment it's ran)
		bool _readWrite         = (bool) DATA_BUS_OPERATION::READ; // 0 : Write / 1 : Read
		byte _dataBus           = (byte) 0x00;  // D0-D7
		word _addressBus        = (word) 0x0000; // A0-A15

		// Internals
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

		// Memory map
		std::vector<byte> _map;

		// Links
		word _ram         = (word) 0x0000;
		word _ramSize     = (word) 0x0000;
		word const _stack = (word) 0x0100;
		word _rom         = (word) 0x0000;
		word _romSize     = (word) 0x0000;
		
		// Instructions
		std::vector<std::string> _instructionsNames;
		std::vector<Instruction> _instructionsMatrix;
};

#endif // CPU_HPP
