#ifndef CPU_HPP
#define CPU_HPP

#include <iostream>
#include <vector>
#include <iomanip>
#include <functional>

#include "types.hpp"
#include "addressing_mode.hpp"
#include "tools.hpp"

enum class STATUS_FLAG : Byte {
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
constexpr Word NMI_LOW    = 0xFFFA;
constexpr Word NMI_HIGH   = 0xFFFB;
constexpr Word RESET_LOW  = 0xFFFC;
constexpr Word RESET_HIGH = 0xFFFD;
constexpr Word IRQ_LOW    = 0xFFFE;
constexpr Word IRQ_HIGH   = 0xFFFF;

class CPU {
	using Instruction = void (CPU::*)(void);

	public:
		CPU(std::vector<Byte>* ram, Word ramStart, Word ramSize, std::vector<Byte>* rom, Word romStart, Word romSize);

		// Debug log function
		void DisplayStatus() const;
		void DisplayStatusFlag(STATUS_FLAG flag);

		// Registers specific logs
		void DisplayAccumulator() const;
		void DisplayIndexX() const;
		void DisplayIndexY() const;
		void DisplayRegisters() const;

		// Stack pointer log
		void DisplayStackPointer() const;
		
		// Buses specific logs
		void DisplayAddressBus() const;
		void DisplayDataBus() const;
		void DisplayBuses() const;
		
		// Program counter log
		void DisplayProgramCounter() const;

		// All logs at once
		void DisplayState() const;

		// RAM specific display
		void DisplayRAM() const;
		void DisplayZeroPage() const;
		void DisplayRAMPage(Byte page) const;
		void DisplayStack() const;
		
		// ROM display
		void DisplayROM(bool stopOnBreak) const;
		void DisplayInstructionAsBytes(size_t bytesN) const;

		// Map display
		void DisplayMap() const;

		// Run execution of the CPU
		void Run(bool stepByStep);

	private:
		void FetchAndExecute();

		void UpdateState(Byte reg, Byte* cmpVal = nullptr, ARITHMETIC_OPERATION operation = ARITHMETIC_OPERATION::NO_OPERATION);

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

		void SetFlag(STATUS_FLAG flag);
		void UnsetFlag(STATUS_FLAG flag);

		bool IsNegative(Byte value) const;

		bool IsSet(STATUS_FLAG flag) const;

		void UseFullAddressingModeSet();
		void UsePartialAddressingModeSet(INDEX index = INDEX::UNUSED);

		void IncrementProgramCounter();

		inline void SetDataBusFromByteAtPC();
		inline void SetDataBusFromAddressBus();

		void SetAddressBusFromTwoNextBytesInROM();

		void PushToStack(Byte value);
		Byte PullFromStack();

		// checkSet checks if the function must check for the flag to be set or for it to be unset
		// true : isSet(flag)
		// false : !isSet(flag)
		void CheckBranching(STATUS_FLAG flag, bool checkSet);

		void SetProgramCounterFromResetVector();

	private:
		// Pins
		// (Doesn't include RDY, VCC and VSS since this program assumes 
		// the CPU is always running the moment it's ran)
		bool _readWrite         = (bool) DATA_BUS_OPERATION::READ; // 0 : Write / 1 : Read
		Byte _dataBus           = (Byte) 0x00;  // D0-D7
		Word _addressBus        = (Word) 0x0000; // A0-A15

		// Internals
		Byte _accumulator       = (Byte) 0x00; // A
		Byte _indexX            = (Byte) 0x00; // X
		Byte _indexY            = (Byte) 0x00; // Y
		Byte _statusFlags       = (Byte) STATUS_FLAG::_; // SR
		Byte _stackPointer      = (Byte) 0x00; // SP
		Word _programCounter    = (Word) 0x0000; // PC

		// Vectors
		Word _nmi = (Word) 0x0000; // Non Maskable Interrupt vector
		Word _res = (Word) 0x0000; // RESet vector
		Word _irq = (Word) 0x0000; // Interrupt ReQuest vector

		// Memory map
		std::vector<Byte> _map;

		// Links
		Word _ram         = (Word) 0x0000;
		Word _ramSize     = (Word) 0x0000;
		Word const _stack = (Word) 0x0100;
		Word _rom         = (Word) 0x0000;
		Word _romSize     = (Word) 0x0000;
		
		// Instructions
		std::vector<std::string> _instructionsNames;
		std::vector<Instruction> _instructionsMatrix;
};

#endif // CPU_HPP
