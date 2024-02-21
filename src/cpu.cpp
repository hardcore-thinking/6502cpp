#include "cpu.hpp"

CPU::CPU(std::vector<byte>* ram, word ramStart, word ramSize, std::vector<byte>* rom, word romStart, word romSize) {
	_instructionsMatrix = {
	//  0          1          2          3          4          5          6          7          8          9          A          B          C          D          E          F
		&CPU::BRK, &CPU::ORA, nullptr,   nullptr,   nullptr,   &CPU::ORA, &CPU::ASL, nullptr,   &CPU::PHP, &CPU::ORA, &CPU::ASL, nullptr,   nullptr,   &CPU::ORA, &CPU::ASL, nullptr, // 0
		&CPU::BPL, &CPU::ORA, nullptr,   nullptr,   nullptr,   &CPU::ORA, &CPU::ASL, nullptr,   &CPU::CLC, &CPU::ORA, nullptr,   nullptr,   nullptr,   &CPU::ORA, &CPU::ASL, nullptr, // 1
		&CPU::JSR, &CPU::AND, nullptr,   nullptr,   &CPU::BIT, &CPU::AND, &CPU::ROL, nullptr,   &CPU::PLP, &CPU::AND, &CPU::ROL, nullptr,   &CPU::BIT, &CPU::AND, &CPU::ROL, nullptr, // 2
		&CPU::BMI, &CPU::AND, nullptr,   nullptr,   nullptr,   &CPU::AND, &CPU::ROL, nullptr,   &CPU::SEC, &CPU::AND, nullptr,   nullptr,   nullptr,   &CPU::AND, &CPU::ROL, nullptr, // 3
		&CPU::RTI, &CPU::EOR, nullptr,   nullptr,   nullptr,   &CPU::EOR, &CPU::LSR, nullptr,   &CPU::PHA, &CPU::EOR, &CPU::LSR, nullptr,   &CPU::JMP, &CPU::EOR, &CPU::LSR, nullptr, // 4
		&CPU::BVC, &CPU::EOR, nullptr,   nullptr,   nullptr,   &CPU::EOR, &CPU::LSR, nullptr,   &CPU::CLI, &CPU::EOR, nullptr,   nullptr,   nullptr,   &CPU::EOR, &CPU::LSR, nullptr, // 5
		&CPU::RTS, &CPU::ADC, nullptr,   nullptr,   nullptr,   &CPU::ADC, &CPU::ROR, nullptr,   &CPU::PLA, &CPU::ADC, &CPU::ROR, nullptr,   &CPU::JMP, &CPU::ADC, &CPU::ROR, nullptr, // 6
		&CPU::BVS, &CPU::ADC, nullptr,   nullptr,   nullptr,   &CPU::ADC, &CPU::ROR, nullptr,   &CPU::SEI, &CPU::ADC, nullptr,   nullptr,   nullptr,   &CPU::ADC, &CPU::ROR, nullptr, // 7
		nullptr,   &CPU::STA, nullptr,   nullptr,   &CPU::STY, &CPU::STA, &CPU::STX, nullptr,   &CPU::DEY, nullptr,   &CPU::TXA, nullptr,   &CPU::STY, &CPU::STA, &CPU::STX, nullptr, // 8
		&CPU::BCC, &CPU::STA, nullptr,   nullptr,   &CPU::STY, &CPU::STA, &CPU::STX, nullptr,   &CPU::TYA, &CPU::STA, &CPU::TXS, nullptr,   nullptr,   &CPU::STA, nullptr,   nullptr, // 9
		&CPU::LDY, &CPU::LDA, &CPU::LDX, nullptr,   &CPU::LDY, &CPU::LDA, &CPU::LDX, nullptr,   &CPU::TAY, &CPU::LDA, &CPU::TAX, nullptr,   &CPU::LDY, &CPU::LDA, &CPU::LDX, nullptr, // A
		&CPU::BCS, &CPU::LDA, nullptr,   nullptr,   &CPU::LDY, &CPU::LDA, &CPU::LDX, nullptr,   &CPU::CLV, &CPU::LDA, &CPU::TSX, nullptr,   &CPU::LDY, &CPU::LDA, &CPU::LDX, nullptr, // B
		&CPU::CPY, &CPU::CMP, nullptr,   nullptr,   &CPU::CPY, &CPU::CMP, &CPU::DEC, nullptr,   &CPU::INY, &CPU::CMP, &CPU::DEX, nullptr,   &CPU::CPY, &CPU::CMP, &CPU::DEC, nullptr, // C
		&CPU::BNE, &CPU::CMP, nullptr,   nullptr,   nullptr,   &CPU::CMP, &CPU::DEC, nullptr,   &CPU::CLD, &CPU::CMP, nullptr,   nullptr,   nullptr,   &CPU::CMP, &CPU::DEC, nullptr, // D
		&CPU::CPX, &CPU::SBC, nullptr,   nullptr,   &CPU::CPX, &CPU::SBC, &CPU::INC, nullptr,   &CPU::INX, &CPU::SBC, &CPU::NOP, nullptr,   &CPU::CPX, &CPU::SBC, &CPU::INC, nullptr, // E
		&CPU::BEQ, &CPU::SBC, nullptr,   nullptr,   nullptr,   &CPU::SBC, &CPU::INC, nullptr,   &CPU::SED, &CPU::SBC, nullptr,   nullptr,   nullptr,   &CPU::SBC, &CPU::INC, nullptr  // F
	};
	
	_ram = ramStart;
	_rom = romStart;
	
	_ramSize = ramSize;
	_romSize = romSize;

	_map = std::vector<byte>(MAX_ADDRESSABLE, 0x00);

	for (int i = 0; i < ramSize; i++) {
		_map[ramStart + i] = (*ram)[i];
	}

	for (int i = 0; i < romSize; i++) {
		_map[romStart + i] = (*rom)[i];
	}

	setProgramCounterFromResetVector();
}

void CPU::displayStatus() const {
	std::ios_base::fmtflags f(std::cout.flags());

	std::cout << "N V - B D I Z C" << "\n";

	for (int i = sizeof(byte) * 8 - 1; i >= 0; i--) {
		std::cout << ((_statusFlags >> i) & 1) << " ";
	}

	std::cout << std::endl;

	std::cout.flags(f);
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
	std::cout << "Address bus = $" << std::setfill('0') << std::setw(4) << (int) (getBigEndianAddress(_addressBus)) << std::endl;

	std::ios_base::fmtflags f(std::cout.flags());
}

void CPU::displayProgramCounter() const {
	std::cout << "PC = $" << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << (int) (getBigEndianAddress(_programCounter)) << std::endl;

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

void CPU::displayMap() const {
	std::cout << "\t";
	std::cout << std::hex;

	for (int i = 0; i < 16; i++) {
		std::cout << std::uppercase << std::setw(2) << std::setfill('0') << i << " ";
	}

	std::cout << std::endl << "$" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << 0 << "\t";

	for (int i = 0; i < MAX_ADDRESSABLE; i++) {
		if (i != 0 && i % 16 == 0) {
			std::cout << std::endl << "$" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << i << "\t";
		}

		std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(_map[i]) << " ";
	}

	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::endl;
}

void CPU::run() {
	while (true) {
		fetchAndExecute();
		char _ = getchar();
	}
}

void CPU::fetchAndExecute() {
	_readWrite = (bool) DATA_BUS_OPERATION::READ;
	displayProgramCounter();
	_dataBus = _map[getBigEndianAddress(_programCounter)];

	if (this->_instructionsMatrix[_dataBus] != nullptr) {
		(this->*_instructionsMatrix[_dataBus])();
	}
	else {
		std::cout << "(no instruction)" << std::endl;
	}
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

void CPU::ADC() {
	std::cout << "ADC" << std::endl;
}

void CPU::AND() {
	std::cout << "AND" << std::endl;
}

void CPU::ASL() {
	std::cout << "ASL" << std::endl;
}

void CPU::BCC() {
	std::cout << "BCC" << std::endl;
}

void CPU::BCS() {
	std::cout << "BCS" << std::endl;
}

void CPU::BEQ() {
	std::cout << "BEQ" << std::endl;
}

void CPU::BIT() {
	std::cout << "BIT" << std::endl;
}

void CPU::BMI() {
	std::cout << "BMI" << std::endl;
}

void CPU::BNE() {
	std::cout << "BNE" << std::endl;
}

void CPU::BPL() {
	std::cout << "BPL" << std::endl;
}

void CPU::BRK() {
	std::cout << "BRK" << std::endl;
}

void CPU::BVC() {
	std::cout << "BVC" << std::endl;
}

void CPU::BVS() {
	std::cout << "BVS" << std::endl;
}

void CPU::CLC() {
	std::cout << "CLC" << std::endl;

	unsetFlag(STATUS_FLAG::C);
}

void CPU::CLD() {
	std::cout << "CLD" << std::endl;

	unsetFlag(STATUS_FLAG::D);
}

void CPU::CLI() {
	std::cout << "CLI" << std::endl;

	unsetFlag(STATUS_FLAG::I);
}

void CPU::CLV() {
	std::cout << "CLV" << std::endl;

	unsetFlag(STATUS_FLAG::V);
}

void CPU::CMP() {
	std::cout << "CMP" << std::endl;
}

void CPU::CPX() {
	std::cout << "CPX" << std::endl;
}

void CPU::CPY() {
	std::cout << "CPY" << std::endl;
}

void CPU::DEC() {
	std::cout << "DEC" << std::endl;
}

void CPU::DEX() {
	std::cout << "DEX" << std::endl;
}

void CPU::DEY() {
	std::cout << "DEY" << std::endl;
}

void CPU::EOR() {
	std::cout << "EOR" << std::endl;
}

void CPU::INC() {
	std::cout << "INC" << std::endl;
}

void CPU::INX() {
	std::cout << "INX" << std::endl;
}

void CPU::INY() {
	std::cout << "INY" << std::endl;
}

void CPU::JMP() {
	std::cout << "JMP" << std::endl;
}

void CPU::JSR() {
	std::cout << "JSR" << std::endl;
}

void CPU::LDA() {
	std::cout << "LDA" << std::endl;

	std::ios_base::fmtflags f(std::cout.flags());

	std::cout << std::hex << std::uppercase;

	switch (_dataBus & ADDRESSING_MODE_MASK) {}

	updateState(_accumulator);

	std::cout.flags(f);

	for (int i = 0; i < 3; i++) {
		increaseProgramCounter();
	}
}

void CPU::LDX() {
	std::cout << "LDX" << std::endl;

	std::ios_base::fmtflags f(std::cout.flags());

	std::cout << std::hex << std::uppercase;

	switch (_dataBus & ADDRESSING_MODE_MASK) {}
	
	updateState(_indexX);

	std::cout.flags(f);
}

void CPU::LDY() {
	std::cout << "LDY" << std::endl;

	std::ios_base::fmtflags f(std::cout.flags());

	std::cout << std::hex << std::uppercase;

	switch (_dataBus & ADDRESSING_MODE_MASK) {}

	updateState(_indexY);

	std::cout.flags(f);
}

void CPU::LSR() {
	std::cout << "LSR" << std::endl;
}

void CPU::NOP() {
	std::cout << "NOP" << std::endl;

	increaseProgramCounter();
}

void CPU::ORA() {
	std::cout << "ORA" << std::endl;
}

void CPU::PHA() {
	std::cout << "PHA" << std::endl;
}

void CPU::PHP() {
	std::cout << "PHP" << std::endl;
}

void CPU::PLA() {
	std::cout << "PLA" << std::endl;
}

void CPU::PLP() {
	std::cout << "PLP" << std::endl;
}

void CPU::ROL() {
	std::cout << "ROL" << std::endl;
}

void CPU::ROR() {
	std::cout << "ROR" << std::endl;
}

void CPU::RTI() {
	std::cout << "RTI" << std::endl;
}

void CPU::RTS() {
	std::cout << "RTS" << std::endl;
}

void CPU::SBC() {
	std::cout << "SBC" << std::endl;
}

void CPU::SEC() {
	std::cout << "SEC" << std::endl;

	setFlag(STATUS_FLAG::C);
}

void CPU::SED() {
	std::cout << "SED" << std::endl;

	setFlag(STATUS_FLAG::D);
}

void CPU::SEI() {
	std::cout << "SEI" << std::endl;

	setFlag(STATUS_FLAG::I);
}

void CPU::STA() {
	std::cout << "STA" << std::endl;

	std::ios_base::fmtflags f(std::cout.flags());

	std::cout << std::hex << std::uppercase;

	switch (_dataBus & ADDRESSING_MODE_MASK) {}

	std::cout.flags(f);
}

void CPU::STX() {
	std::cout << "STX" << std::endl;
}

void CPU::STY() {
	std::cout << "STY" << std::endl;

	std::ios_base::fmtflags f(std::cout.flags());

	std::cout << std::hex << std::uppercase;

	std::cout.flags(f);
}

void CPU::TAX() {
	std::cout << "TAX" << std::endl;

	_indexX = _accumulator;
}

void CPU::TAY() {
	std::cout << "TAY" << std::endl;

	_indexY = _accumulator;
}

void CPU::TSX() {
	std::cout << "TSX" << std::endl;

	_indexX = _stackPointer;
}

void CPU::TXA() {
	std::cout << "TXA" << std::endl;

	_accumulator = _indexX;
}

void CPU::TXS() {
	std::cout << "TXS" << std::endl;

	_stackPointer = _indexX;
}

void CPU::TYA() {
	std::cout << "TYA" << std::endl;

	_accumulator = _indexY;
}

void CPU::setFlag(STATUS_FLAG flag) {
	_statusFlags ^= (byte) flag;
}

void CPU::unsetFlag(STATUS_FLAG flag) {
	_statusFlags &= ~((byte) flag);
}

void CPU::increaseProgramCounter() {
	_programCounter = getLittleEndianAddress(getBigEndianAddress(_programCounter) + (word)(0x01));
}

void CPU::setAddressBusFromDataBusPreIndexed() {
	_dataBus += _indexX; // pre add Y to the high byte in the data bus

	_addressBus = _dataBus; // transfer the instruction's operand from the data bus to the address bus
	_dataBus = _map[_addressBus]; // get the low byte from the address stored in the address bus
	_addressBus |= ((word)(~0xFF) & ((word)(_dataBus) << 8)); // shift the newly loaded low byte in the address bus (low byte area)

	_dataBus = (byte)(_addressBus); // retransfer the high byte of the address bus to the data bus
	_dataBus++; // add one to the data bus to get the memory address of the high byte

	_addressBus |= 0xFF; // prepare the address high byte to receive the new address stored in the data bus
	_addressBus &= (word)(~0xFF) | (word)(_dataBus); // transfer the data bus value to the high byte of the address bus

	_dataBus = _map[(byte)_addressBus]; // get the high byte of the address stored in memory from the high byte in the address bus

	_addressBus &= (word)(0xFF00); // prepare the high byte of the address bus to receive the high byte of the address stored in memory currently in the databus
	_addressBus |= _dataBus; // transfer the high byte from the data bus to the high byte of the address bus
}

void CPU::setAddressBusFromDataBusPostIndexed() {
	_addressBus = _dataBus; // transfer the instruction's operand from the data bus to the address bus
	_dataBus = _map[_addressBus]; // get the low byte from the address stored in the address bus
	_addressBus |= ((word)(~0xFF) & ((word)(_dataBus) << 8)); // shift the newly loaded low byte in the address bus (low byte area)

	_dataBus = (byte)(_addressBus); // retransfer the high byte of the address bus to the data bus
	_dataBus++; // add one to the data bus to get the memory address of the high byte

	_addressBus |= 0xFF; // prepare the address high byte to receive the new address stored in the data bus
	_addressBus &= (word)(~0xFF) | (word)(_dataBus); // transfer the data bus value to the high byte of the address bus

	_dataBus = _map[(byte)_addressBus]; // get the high byte of the address stored in memory from the high byte in the address bus
	_dataBus += _indexY; // post add Y to the high byte in the data bus

	_addressBus &= (word)(0xFF00); // prepare the high byte of the address bus to receive the high byte of the address stored in memory currently in the databus
	_addressBus |= _dataBus; // transfer the high byte from the data bus to the high byte of the address bus
}

void CPU::setProgramCounterFromResetVector() {
	_readWrite = (bool) DATA_BUS_OPERATION::READ;

	_dataBus = _map[0xFFFC];
	_addressBus = _dataBus;
	_addressBus <<= 8;
	_dataBus = _map[0xFFFD];
	_addressBus |= 0xFF;
	_addressBus &= (word)(~0xFF) | (word)(_dataBus);

	_programCounter = _addressBus;
}
