#include "cpu.hpp"

CPU::CPU(std::vector<byte>* ram, std::vector<byte>* rom) {
	_ram = ram;
}

void CPU::displayStatus() const {
	std::cout << "N V - B D I Z C" << "\n";

	for (int i = sizeof(byte) * 8 - 1; i >= 0; i--) {
		std::cout << ((_statusFlags >> i) & 1) << " ";
	}

	std::cout << std::endl;

	std::ios_base::fmtflags f(std::cout.flags());
}

void CPU::displayRegisters() const {
	std::cout << std::hex << std::uppercase;

	std::cout << "A = $" << std::setfill('0') << std::setw(2) << (int) _accumulator << std::endl;
	std::cout << "X = $" << std::setfill('0') << std::setw(2) << (int) _indexX << std::endl;
	std::cout << "Y = $" << std::setfill('0') << std::setw(2) << (int) _indexY << std::endl;

	std::ios_base::fmtflags f(std::cout.flags());
}

void CPU::displayStackPointer() const {
	std::cout << "SP = $" <<  std::hex << std::setfill('0') << std::setw(2) << (int) _stackPointer << std::endl;

	std::ios_base::fmtflags f(std::cout.flags());
}

void CPU::displayBuses() const {
	std::cout << std::hex << std::uppercase;

	std::cout << "Data bus = $" << std::setfill('0') << std::setw(2) << (int) _dataBus << std::endl;
	std::cout << "Address bus = $" << std::setfill('0') << std::setw(4) << (int) _addressBus << std::endl;

	std::ios_base::fmtflags f(std::cout.flags());
}

void CPU::displayProgramCounter() const {
	std::cout << "PC = $" << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << (int) _programCounter << std::endl;

	std::ios_base::fmtflags f(std::cout.flags());
}

void CPU::displayState() const {
	displayStatus();
	displayRegisters();
	displayStackPointer();
	displayBuses();
	displayProgramCounter();

	std::ios_base::fmtflags f(std::cout.flags());
}

void CPU::updateState(byte value) {
	if (value == (byte) 0x00) {
		unsetFlag(STATUS_FLAG::N);
		setFlag(STATUS_FLAG::Z);
	}

	else if (value >= (byte) 0x80 && value <= 0xFF) {
		setFlag(STATUS_FLAG::N);
		unsetFlag(STATUS_FLAG::Z);
	}

	else {
		unsetFlag(STATUS_FLAG::N);
		unsetFlag(STATUS_FLAG::Z);
	}
}

void CPU::ADC(byte opcode, byte operand) {}

void CPU::ADC(byte opcode, word operand) {}

void CPU::AND(byte opcode, byte operand) {}

void CPU::AND(byte opcode, word operand) {}

void CPU::ASL(byte opcode) {}

void CPU::ASL(byte opcode, byte operand) {}

void CPU::ASL(byte opcode, word operand) {}

void CPU::BCC(byte opcode) {}

void CPU::BCS(byte opcode) {}

void CPU::BEQ(byte opcode) {}

void CPU::BIT(byte opcode, byte operand) {}

void CPU::BIT(byte opcode, word operand) {}

void CPU::BMI(byte opcode) {}

void CPU::BNE(byte opcode) {}

void CPU::BPL(byte opcode) {}

void CPU::BRK(byte opcode) {
	std::cout << "BRK" << std::endl;

	_dataBus = (byte) ADDRESSING_MODES_BRK::IMPLIED;
}

void CPU::BVC(byte opcode) {}

void CPU::BVS(byte opcode) {}

void CPU::CLC(byte opcode) {
	unsetFlag(STATUS_FLAG::C);
}

void CPU::CLD(byte opcode) {
	unsetFlag(STATUS_FLAG::D);
}

void CPU::CLI(byte opcode) {
	unsetFlag(STATUS_FLAG::I);
}

void CPU::CLV(byte opcode) {
	unsetFlag(STATUS_FLAG::V);
}

void CPU::CMP(byte opcode, byte operand) {}

void CPU::CMP(byte opcode, word operand) {}

void CPU::CPX(byte opcode, byte operand) {}

void CPU::CPX(byte opcode, word operand) {}

void CPU::CPY(byte opcode, byte operand) {}

void CPU::CPY(byte opcode, word operand) {}

void CPU::DEC(byte opcode, byte operand) {}

void CPU::DEC(byte opcode, word operand) {}

void CPU::DEX(byte opcode) {}

void CPU::DEY(byte opcode) {}

void CPU::EOR(byte opcode, byte operand) {}

void CPU::EOR(byte opcode, word operand) {}

void CPU::INC(byte opcode, byte operand) {}

void CPU::INC(byte opcode, word operand) {}

void CPU::INX(byte opcode) {}

void CPU::INY(byte opcode) {}

void CPU::JMP(byte opcode, word operand) {}

void CPU::JSR(byte opcode, word operand) {}

void CPU::LDA(byte opcode, byte operand) {
	std::ios_base::fmtflags f(std::cout.flags());

	std::cout << std::hex << std::uppercase;

	switch (opcode) {
		case (byte) ADDRESSING_MODES_LDA::IMMEDIATE:
			std::cout << "LDA #$" << std::setfill('0') << std::setw(2) << (int) operand << std::endl;

			break;

		case (byte) ADDRESSING_MODES_LDA::ZEROPAGE:
			std::cout << "LDA $" << std::setfill('0') << std::setw(2) << (int) operand << std::endl;

			break;

		case (byte) ADDRESSING_MODES_LDA::ZEROPAGE_X:
			std::cout << "LDA $" << std::setfill('0') << std::setw(2) << (int) operand << ", X" << std::endl;

			break;

		case (byte) ADDRESSING_MODES_LDA::ZEROPAGE_PRE_X:
			std::cout << "LDA ($" << std::setfill('0') << std::setw(2) << (int) operand << ", X)" << std::endl;

			break;

		case (byte) ADDRESSING_MODES_LDA::ZEROPAGE_POST_Y:
			std::cout << "LDA ($" << std::setfill('0') << std::setw(2) << (int) operand << "), Y" << std::endl;

			break;

		default:
			break;
	}

	updateState(_accumulator);

	std::cout.flags(f);
}

void CPU::LDA(byte opcode, word operand) {
	std::ios_base::fmtflags f(std::cout.flags());

	std::cout << std::hex << std::uppercase;

	switch (opcode) {
		case (byte) ADDRESSING_MODES_LDA::ABSOLUTE:
			std::cout << "LDA $" << std::setfill('0') << std::setw(4) << (int) operand << std::endl;

			break;

		case (byte) ADDRESSING_MODES_LDA::ABSOLUTE_X:
			std::cout << "LDA $" << std::setfill('0') << std::setw(4) << (int) operand << ", X" << std::endl;

			break;

		case (byte) ADDRESSING_MODES_LDA::ABSOLUTE_Y:
			std::cout << "LDA $" << std::setfill('0') << std::setw(4) << (int) operand << ", Y" << std::endl;

			break;

		default:
			break;
	}

	updateState(_accumulator);

	std::cout.flags(f);
}

void CPU::LDX(byte opcode, byte operand) {
	std::ios_base::fmtflags f(std::cout.flags());

	std::cout << std::hex << std::uppercase;

	switch (opcode) {
		case (byte) ADDRESSING_MODES_LDX::IMMEDIATE:
			std::cout << "LDX #$" << std::setfill('0') << std::setw(2) << (int) operand << std::endl;

			break;

		case (byte) ADDRESSING_MODES_LDX::ZEROPAGE:
			std::cout << "LDX $" << std::setfill('0') << std::setw(2) << (int) operand << std::endl;

			break;

		case (byte) ADDRESSING_MODES_LDX::ZEROPAGE_Y:
			std::cout << "LDX $" << std::setfill('0') << std::setw(2) << (int) operand << ", Y)" << std::endl;

			break;

		default:
			break;
	}
	
	updateState(_indexX);

	std::cout.flags(f);
}

void CPU::LDX(byte opcode, word operand) {
	std::ios_base::fmtflags f(std::cout.flags());

	std::cout << std::hex << std::uppercase;

	switch (opcode) {
		case (byte) ADDRESSING_MODES_LDX::ABSOLUTE:
			std::cout << "LDX $" << std::setfill('0') << std::setw(4) << (int) operand << std::endl;

			break;

		case (byte) ADDRESSING_MODES_LDX::ABSOLUTE_Y:
			std::cout << "LDX ($" << std::setfill('0') << std::setw(4) << (int) operand << ", Y)" << std::endl;

			break;

		default:
			break;
	}

	updateState(_indexX);

	std::cout.flags(f);
}

void CPU::LDY(byte opcode, byte operand) {
	std::ios_base::fmtflags f(std::cout.flags());

	std::cout << std::hex << std::uppercase;

	switch (opcode) {
		case (byte) ADDRESSING_MODES_LDY::IMMEDIATE:
			std::cout << "LDY #$" << std::setfill('0') << std::setw(2) << (int) operand << std::endl;

			break;

		case (byte) ADDRESSING_MODES_LDY::ZEROPAGE:
			std::cout << "LDY $" << std::setfill('0') << std::setw(2) << (int) operand << std::endl;

			break;

		case (byte) ADDRESSING_MODES_LDY::ZEROPAGE_X:
			std::cout << "LDY ($" << std::setfill('0') << std::setw(2) << (int) operand << ", X)" << std::endl;

			break;

		default:
			break;
	}

	updateState(_indexY);

	std::cout.flags(f);
}

void CPU::LDY(byte opcode, word operand) {
	std::ios_base::fmtflags f(std::cout.flags());

	std::cout << std::hex << std::uppercase;

	switch (opcode) {
		case (byte) ADDRESSING_MODES_LDY::ABSOLUTE:
			std::cout << "LDY $" << std::setfill('0') << std::setw(4) << (int) operand << std::endl;

			break;

		case (byte) ADDRESSING_MODES_LDY::ABSOLUTE_X:
			std::cout << "LDY ($" << std::setfill('0') << std::setw(4) << (int) operand << ", X)" << std::endl;

			break;

		default:
			break;
	}

	updateState(_indexY);

	std::cout.flags(f);
}

void CPU::LSR(byte opcode) {}

void CPU::LSR(byte opcode, byte operand) {}

void CPU::LSR(byte opcode, word operand) {}

void CPU::NOP(byte opcode) {}

void CPU::ORA(byte opcode, byte operand) {}

void CPU::ORA(byte opcode, word operand) {}

void CPU::PHA(byte opcode) {}

void CPU::PHP(byte opcode) {}

void CPU::PLA(byte opcode) {}

void CPU::PLP(byte opcode) {}

void CPU::ROL(byte opcode) {}

void CPU::ROL(byte opcode, byte operand) {}

void CPU::ROL(byte opcode, word operand) {}

void CPU::RTI(byte opcode) {}

void CPU::RTS(byte opcode) {}

void CPU::SBC(byte opcode, byte operand) {}

void CPU::SBC(byte opcode, word operand) {}

void CPU::SEC(byte opcode) {
	setFlag(STATUS_FLAG::C);
}

void CPU::SED(byte opcode) {
	setFlag(STATUS_FLAG::D);
}

void CPU::SEI(byte opcode) {
	setFlag(STATUS_FLAG::I);
}

void CPU::STA(byte opcode, byte operand) {
	std::ios_base::fmtflags f(std::cout.flags());

	std::cout << std::hex << std::uppercase;

	switch (opcode) {
		case (byte) ADDRESSING_MODES_STA::ZEROPAGE:
			std::cout << "STA $" << std::setfill('0') << std::setw(2) << (int) operand << std::endl;

			break;

		case (byte) ADDRESSING_MODES_STA::ZEROPAGE_X:
			std::cout << "STA $" << std::setfill('0') << std::setw(2) << (int) operand << ", X" << std::endl;

			break;

		case (byte)ADDRESSING_MODES_STA::ZEROPAGE_PRE_X:
			std::cout << "STA ($" << std::setfill('0') << std::setw(2) << (int) operand << ", X)" << std::endl;

			break;

		case (byte) ADDRESSING_MODES_STA::ZEROPAGE_POST_Y:
			std::cout << "STA ($" << std::setfill('0') << std::setw(2) << (int) operand << "), Y" << std::endl;

			break;

		default:
			break;
	}

	std::cout.flags(f);
}

void CPU::STA(byte opcode, word operand) { 
	std::ios_base::fmtflags f(std::cout.flags());

	std::cout << std::hex << std::uppercase;

	switch (opcode) {
	case (byte) ADDRESSING_MODES_STA::ABSOLUTE:
			std::cout << "STA $" << std::setfill('0') << std::setw(4) << (int) operand << std::endl;

			break;

		case (byte) ADDRESSING_MODES_STA::ABSOLUTE_X:
			std::cout << "STA $" << std::setfill('0') << std::setw(4) << (int) operand << ", X" << std::endl;

			break;

		case (byte) ADDRESSING_MODES_STA::ABSOLUTE_Y:
			std::cout << "STA $" << std::setfill('0') << std::setw(4) << (int) operand << ", Y" << std::endl;

			break;

		default:
			break;
	}
}

void CPU::STX(byte opcode, byte operand) {}

void CPU::STX(byte opcode, word operand) {}

void CPU::STY(byte opcode, byte operand) {
	std::ios_base::fmtflags f(std::cout.flags());

	std::cout << std::hex << std::uppercase;

	std::cout << "STY $" << std::setfill('0') << std::setw(4) << (int) operand << std::endl;
}

void CPU::STY(byte opcode, word operand) {
	std::ios_base::fmtflags f(std::cout.flags());

	std::cout << std::hex << std::uppercase;

	std::cout << "STY $" << std::setfill('0') << std::setw(4) << (int)operand << std::endl;
}

void CPU::TAX(byte opcode) {
	_indexX = _accumulator;
}

void CPU::TAY(byte opcode) {
	_indexY = _accumulator;
}

void CPU::TSX(byte opcode) {
	_indexX = _stackPointer;
}

void CPU::TXA(byte opcode) {
	_accumulator = _indexX;
}

void CPU::TXS(byte opcode) {
	_stackPointer = _indexX;
}

void CPU::TYA(byte opcode) {
	_accumulator = _indexY;
}

void CPU::setFlag(STATUS_FLAG flag) {
	_statusFlags ^= (byte) flag;
}

void CPU::unsetFlag(STATUS_FLAG flag) {
	_statusFlags &= ~((byte) flag);
}

void CPU::setAddressBusFromDataBusPreIndexed() {
	_dataBus += _indexX; // pre add Y to the high byte in the data bus

	_addressBus = _dataBus; // transfer the instruction's operand from the data bus to the address bus
	_dataBus = (*_ram)[_addressBus]; // get the low byte from the address stored in the address bus
	_addressBus |= ((word)(~0xFF) & ((word)(_dataBus) << 8)); // shift the newly loaded low byte in the address bus (low byte area)

	_dataBus = (byte)(_addressBus); // retransfer the high byte of the address bus to the data bus
	_dataBus++; // add one to the data bus to get the memory address of the high byte

	_addressBus |= 0xFF; // prepare the address high byte to receive the new address stored in the data bus
	_addressBus &= (word)(~0xFF) | (word)(_dataBus); // transfer the data bus value to the high byte of the address bus

	_dataBus = (*_ram)[(byte)_addressBus]; // get the high byte of the address stored in memory from the high byte in the address bus

	_addressBus &= (word)(0xFF00); // prepare the high byte of the address bus to receive the high byte of the address stored in memory currently in the databus
	_addressBus |= _dataBus; // transfer the high byte from the data bus to the high byte of the address bus
}

void CPU::setAddressBusFromDataBusPostIndexed() {
	_addressBus = _dataBus; // transfer the instruction's operand from the data bus to the address bus
	_dataBus = (*_ram)[_addressBus]; // get the low byte from the address stored in the address bus
	_addressBus |= ((word)(~0xFF) & ((word)(_dataBus) << 8)); // shift the newly loaded low byte in the address bus (low byte area)

	_dataBus = (byte)(_addressBus); // retransfer the high byte of the address bus to the data bus
	_dataBus++; // add one to the data bus to get the memory address of the high byte

	_addressBus |= 0xFF; // prepare the address high byte to receive the new address stored in the data bus
	_addressBus &= (word)(~0xFF) | (word)(_dataBus); // transfer the data bus value to the high byte of the address bus

	_dataBus = (*_ram)[(byte)_addressBus]; // get the high byte of the address stored in memory from the high byte in the address bus
	_dataBus += _indexY; // post add Y to the high byte in the data bus

	_addressBus &= (word)(0xFF00); // prepare the high byte of the address bus to receive the high byte of the address stored in memory currently in the databus
	_addressBus |= _dataBus; // transfer the high byte from the data bus to the high byte of the address bus
}
