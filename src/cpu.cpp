#include "cpu.hpp"

CPU::CPU(std::vector<byte>* ram, word ramStart, word ramSize, std::vector<byte>* rom, word romStart, word romSize) {
	_instructionsNames  = {
	//  0      1      2      3      4      5      6      7     8      9      A      B      C      D      E      F
		"BRK", "ORA", "",    "",    "",    "ORA", "ASL", "",   "PHP", "ORA", "ASL", "",    "",    "ORA", "ASL", "", // 0
		"BPL", "ORA", "",    "",    "",    "ORA", "ASL", "",   "CLC", "ORA", "",    "",    "",    "ORA", "ASL", "", // 1
		"JSR", "AND", "",    "",    "BIT", "AND", "ROL", "",   "PLP", "AND", "ROL", "",    "BIT", "AND", "ROL", "", // 2
		"BMI", "AND", "",    "",    "",    "AND", "ROL", "",   "SEC", "AND", "",    "",    "",    "AND", "ROL", "", // 3
		"RTI", "EOR", "",    "",    "",    "EOR", "LSR", "",   "PHA", "EOR", "LSR", "",    "JMP", "EOR", "LSR", "", // 4
		"BVC", "EOR", "",    "",    "",    "EOR", "LSR", "",   "CLI", "EOR", "",    "",    "",    "EOR", "LSR", "", // 5
		"RTS", "ADC", "",    "",    "",    "ADC", "ROR", "",   "PLA", "ADC", "ROR", "",    "JMP", "ADC", "ROR", "", // 6
		"BVS", "ADC", "",    "",    "",    "ADC", "ROR", "",   "SEI", "ADC", "",    "",    "",    "ADC", "ROR", "", // 7
		"",    "STA", "",    "",    "STY", "STA", "STX", "",   "DEY", "",    "TXA", "",    "STY", "STA", "STX", "", // 8
		"BCC", "STA", "",    "",    "STY", "STA", "STX", "",   "TYA", "STA", "TXS", "",    "",    "STA", "",    "", // 9
		"LDY", "LDA", "LDX", "",    "LDY", "LDA", "LDX", "",   "TAY", "LDA", "TAX", "",    "LDY", "LDA", "LDX", "", // A
		"BCS", "LDA", "",    "",    "LDY", "LDA", "LDX", "",   "CLV", "LDA", "TSX", "",    "LDY", "LDA", "LDX", "", // B
		"CPY", "CMP", "",    "",    "CPY", "CMP", "DEC", "",   "INY", "CMP", "DEX", "",    "CPY", "CMP", "DEC", "", // C
		"BNE", "CMP", "",    "",    "",    "CMP", "DEC", "",   "CLD", "CMP", "",    "",    "",    "CMP", "DEC", "", // D
		"CPX", "SBC", "",    "",    "CPX", "SBC", "INC", "",   "INX", "SBC", "NOP", "",    "CPX", "SBC", "INC", "", // E
		"BEQ", "SBC", "",    "",    "",    "SBC", "INC", "",   "SED", "SBC", "",    "",    "",    "SBC", "INC", ""  // F
	};
	
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
		_map[(word)(ramStart + i)] = (*ram)[i];
	}

	for (int i = 0; i < romSize; i++) {
		_map[(word)(romStart + i)] = (*rom)[i];
	}

	_statusFlags = (byte) STATUS_FLAG::_;

	setProgramCounterFromResetVector();
}

void CPU::displayStatus() const {
	std::cout << "N V - B D I Z C" << "\n";

	for (int i = sizeof(byte) * 8 - 1; i >= 0; i--) {
		std::cout << ((_statusFlags >> i) & 1) << " ";
	}

	std::cout << std::endl;
}

void CPU::displayStatusFlag(STATUS_FLAG flag) {
	switch (flag) {
		case STATUS_FLAG::N:
			std::cout << "N : " << (isSet(STATUS_FLAG::N) ? "true" : "false") << std::endl;
			break;

		case STATUS_FLAG::V:
			std::cout << "V : " << (isSet(STATUS_FLAG::V) ? "true" : "false") << std::endl;
			break;

		case STATUS_FLAG::_:
			break;

		case STATUS_FLAG::B:
			std::cout << "B : " << (isSet(STATUS_FLAG::B) ? "true" : "false") << std::endl;
			break;

		case STATUS_FLAG::D:
			std::cout << "D : " << (isSet(STATUS_FLAG::D) ? "true" : "false") << std::endl;
			break;

		case STATUS_FLAG::I:
			std::cout << "I : " << (isSet(STATUS_FLAG::I) ? "true" : "false") << std::endl;
			break;

		case STATUS_FLAG::Z:
			std::cout << "Z : " << (isSet(STATUS_FLAG::Z) ? "true" : "false") << std::endl;
			break;

		case STATUS_FLAG::C:
			std::cout << "C : " << (isSet(STATUS_FLAG::C) ? "true" : "false") << std::endl;
			break;

		default:
			break;
	}
}

void CPU::displayAccumulator() const {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	std::cout << "A = $" << std::setfill('0') << std::setw(2) << (int) _accumulator << std::endl;

	std::cout.flags(f);
}

void CPU::displayIndexX() const {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	std::cout << "X = $" << std::setfill('0') << std::setw(2) << (int) _indexX << std::endl;

	std::cout.flags(f);
}

void CPU::displayIndexY() const {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	std::cout << "Y = $" << std::setfill('0') << std::setw(2) << (int) _indexY << std::endl;

	std::cout.flags(f);
}

void CPU::displayRegisters() const {
	displayAccumulator();
	displayIndexX();
	displayIndexY();
}

void CPU::displayStackPointer() const {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	std::cout << "SP = $" << std::setfill('0') << std::setw(2) << (int) _stackPointer << std::endl;

	std::cout.flags(f);
}

void CPU::displayAddressBus() const {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	std::cout << "Address bus = $" << std::setfill('0') << std::setw(4) << (int)(getBigEndianAddress(_addressBus)) << std::endl;

	std::cout.flags(f);
}

void CPU::displayDataBus() const {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	std::cout << "Data bus = $" << std::setfill('0') << std::setw(2) << (int)_dataBus << std::endl;

	std::cout.flags(f);
}

void CPU::displayBuses() const {
	displayDataBus();
	displayAddressBus();
}

void CPU::displayProgramCounter() const {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	std::cout << "PC = $" << std::setfill('0') << std::setw(4) << (int)(getBigEndianAddress(_programCounter)) << std::endl;

	std::cout.flags(f);
}

void CPU::displayState() const {
	displayStatus();
	displayRegisters();
	displayStackPointer();
	displayBuses();
	displayProgramCounter();
}

void CPU::displayRAM() const {
	std::ios_base::fmtflags f(std::cout.flags());

	std::cout << "\t";
	std::cout << std::hex;

	for (int i = 0; i < 0x10; i++) {
		std::cout << std::uppercase << std::setw(2) << std::setfill('0') << i << " ";
	}

	std::cout << std::endl << "$" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << _ram << "\t";

	for (int i = 0; i < MAX_RAM_SIZE; i++) {
		if (i != 0 && i % 16 == 0) {
			std::cout << std::endl << "$" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << _ram + i << "\t";
		}

		std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(_map[(word)(_ram + i)]) << " ";
	}

	std::cout << std::endl;

	std::cout.flags(f);
}

void CPU::displayZeroPage() const {
	displayRAMPage(0x00);
}

void CPU::displayRAMPage(byte page) const {
	std::ios_base::fmtflags f(std::cout.flags());

	word const pageAddress = (word)(page << 8);

	std::cout << std::hex << std::uppercase;
	std::cout << "\t";

	for (int i = 0; i < 0x10; i++) {
		std::cout << std::uppercase << std::setw(2) << std::setfill('0') << i << " ";
	}

	std::cout << std::endl << "$" << std::setfill('0') << std::setw(4) << pageAddress << "\t";
	for (int i = 0; i < MAX_PAGE_SIZE; i++) {
		if (i != 0 && i % 16 == 0) {
			std::cout << std::endl << "$" << std::setw(4) << std::setfill('0') << pageAddress + i << "\t";
		}

		std::cout << std::setfill('0') << std::setw(2) << (int) _map[(word)(_ram + pageAddress + i)] << " ";
	}

	std::cout << std::endl;

	std::cout.flags(f);
}

void CPU::displayStack() const {
	displayRAMPage(0x01);
}

void CPU::displayROM(bool stopOnBreak) const {
	std::ios_base::fmtflags f(std::cout.flags());

	std::cout << "\t";
	std::cout << std::hex;

	for (int i = 0; i < 16; i++) {
		std::cout << std::uppercase << std::setw(2) << std::setfill('0') << i << " ";
	}

	std::cout << std::endl << "$" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << _rom << "\t";
	for (int i = 0; i < MAX_ROM_SIZE; i++) {
		if (i != 0 && i % 16 == 0) {
			if (_map[(word)(_rom + i)] == 0x00 && stopOnBreak) break; // TO DELETE
			std::cout << std::endl << "$" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << _rom + i << "\t";
		}

		std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(_map[(word)(_rom + i)]) << " ";
	}

	std::cout << std::endl;

	std::cout.flags(f);
}

void CPU::displayInstructionAsBytes(size_t bytesN) const {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	for (int i = 0; i < (bytesN - 1); i++) {
		std::cout << std::setfill('0') << std::setw(2) << (int) _map[(word)(getBigEndianAddress(_programCounter) + i)] << " ";
	}

	std::cout << std::setfill('0') << std::setw(2) << (int) _map[(word)(getBigEndianAddress(_programCounter) + (bytesN - 1))];

	switch (bytesN) {
		case (size_t) BYTES_USED::ONE_BYTE:
			std::cout << "          ";
			break;

		case (size_t) BYTES_USED::TWO_BYTES:
			std::cout << "       ";
			break;

		case (size_t) BYTES_USED::THREE_BYTES:
			std::cout << "    ";
			break;

		default:
			break;
	}

	std::cout.flags(f);
}

void CPU::displayMap() const {
	std::ios_base::fmtflags f(std::cout.flags());

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

	std::cout << std::endl;

	std::cout.flags(f);
}

void CPU::run(bool stepByStep) {
	while (_map[getBigEndianAddress(_programCounter)] != 0x00) {
		fetchAndExecute();
		if (stepByStep) {
			char _ = getchar(); // wait for enter press
		}
		else {
			std::cout << std::endl;
		}
	}
}

void CPU::fetchAndExecute()  {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	_readWrite = (bool) DATA_BUS_OPERATION::READ;
	setDataBusFromByteAtPC(); // get opcode

	std::cout << "$" << std::setfill('0') << std::setw(4) << getBigEndianAddress(_programCounter) << "    ";

	if (this->_instructionsMatrix[_dataBus] != nullptr) {
		(this->*_instructionsMatrix[_dataBus])();
	}

	else {
		std::cout << "(no instruction)" << std::endl;
	}

	std::cout.flags(f);
}

void CPU::updateState(byte value, ARITHMETIC_OPERATION operation) {
	// check N and Z flag
	if (value == (byte) 0x00) {
		unsetFlag(STATUS_FLAG::N);
		setFlag(STATUS_FLAG::Z);
	}

	else if (value >= (byte) 0x80 && value <= (byte) 0xFF) {
		setFlag(STATUS_FLAG::N);
		unsetFlag(STATUS_FLAG::Z);
	}

	else {
		unsetFlag(STATUS_FLAG::N);
		unsetFlag(STATUS_FLAG::Z);
	}

	// check V flag
	switch (operation) {
		case ARITHMETIC_OPERATION::ADDITION:
			// if sides of the operation are both negative
			if (isNegative(value) && isNegative(_accumulator)) {
				// if their sum is positive
				if (!isNegative((byte)(value + _accumulator))) {
					setFlag(STATUS_FLAG::V);
				}
				else {
					unsetFlag(STATUS_FLAG::V);
				}
			}
			break;

		case ARITHMETIC_OPERATION::SUBTRACTION:
			// if sides of the operation are both negative
			if (!isNegative(value) && !isNegative(_accumulator)) {
				// if their sum is negative
				if (isNegative((byte)(value + _accumulator))) {
					setFlag(STATUS_FLAG::V);
				}
				else {
					unsetFlag(STATUS_FLAG::V);
				}
			}
			break;

		default:
			unsetFlag(STATUS_FLAG::V);
			break;
	}
}

void CPU::ADC() {
	useFullAddressingModeSet();

	updateState(_dataBus, ARITHMETIC_OPERATION::ADDITION);

	_accumulator += _dataBus + ((_statusFlags & (byte)(STATUS_FLAG::C)) ? 1 : 0);

	incrementProgramCounter();
}

void CPU::AND() {
	useFullAddressingModeSet();

	incrementProgramCounter();
}

void CPU::ASL() {
	usePartialAddressingModeSet(INDEX::INDEX_X);

	incrementProgramCounter();
}

void CPU::BCC() {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	displayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

	std::cout << "BCC $";
	checkBranching(STATUS_FLAG::C, false);

	std::cout.flags(f);
}

void CPU::BCS() {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	displayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

	std::cout << "BCS $";
	checkBranching(STATUS_FLAG::C, true);

	std::cout.flags(f);
}

void CPU::BEQ() {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	displayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

	std::cout << "BEQ $";
	checkBranching(STATUS_FLAG::Z, true);

	std::cout.flags(f);
}

void CPU::BIT() {
	usePartialAddressingModeSet();

	incrementProgramCounter();
}

void CPU::BMI() {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	displayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

	std::cout << "BMI $";
	checkBranching(STATUS_FLAG::N, true);

	std::cout.flags(f);
}

void CPU::BNE() {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	displayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);
	
	std::cout << "BNE $";
	checkBranching(STATUS_FLAG::Z, false);

	std::cout.flags(f);
}

void CPU::BPL() {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	displayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

	std::cout << "BPL $";
	checkBranching(STATUS_FLAG::N, false);

	std::cout.flags(f);
}

void CPU::BRK() {
	std::cout << "BRK";

	incrementProgramCounter();
}

void CPU::BVC() {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	displayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

	std::cout << "BVC $";
	checkBranching(STATUS_FLAG::V, false);

	std::cout.flags(f);
}

void CPU::BVS() {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	displayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);
	
	std::cout << "BVS $";
	checkBranching(STATUS_FLAG::V, true);

	std::cout.flags(f);
}

void CPU::CLC() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "CLC";

	unsetFlag(STATUS_FLAG::C);

	incrementProgramCounter();
}

void CPU::CLD() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "CLD";

	unsetFlag(STATUS_FLAG::D);

	incrementProgramCounter();
}

void CPU::CLI() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "CLI";

	unsetFlag(STATUS_FLAG::I);

	incrementProgramCounter();
}

void CPU::CLV() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "CLV";

	unsetFlag(STATUS_FLAG::V);

	incrementProgramCounter();
}

void CPU::CMP() {
	useFullAddressingModeSet();

	incrementProgramCounter();
}

void CPU::CPX() {
	usePartialAddressingModeSet();

	_dataBus = _indexX - _dataBus;

	updateState(_dataBus);

	incrementProgramCounter();
}

void CPU::CPY() {
	usePartialAddressingModeSet();

	_dataBus = _indexY - _dataBus;

	updateState(_dataBus);

	incrementProgramCounter();
}

void CPU::DEC() {
	usePartialAddressingModeSet(INDEX::INDEX_X);

	incrementProgramCounter();
}

void CPU::DEX() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "DEX";

	--_indexX;

	incrementProgramCounter();
}

void CPU::DEY() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "DEY";
	
	--_indexY;

	incrementProgramCounter();
}

void CPU::EOR() {
	useFullAddressingModeSet();

	incrementProgramCounter();
}

void CPU::INC() {
	usePartialAddressingModeSet(INDEX::INDEX_X);

	incrementProgramCounter();
}

void CPU::INX() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "INX";

	++_indexX;

	incrementProgramCounter();
}

void CPU::INY() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "INY";

	++_indexY;

	incrementProgramCounter();
}

void CPU::JMP() {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	displayInstructionAsBytes((size_t)BYTES_USED::THREE_BYTES);

	switch (_dataBus) {
		case (byte) JMP_ADDRESSING_MODES::ABSOLUTE:
			setAddressBusFromTwoNextBytesInROM();
			std::cout << "JMP $" << std::setfill('0') << std::setw(4) << (int) getBigEndianAddress(_addressBus);
			break;

		case (byte) JMP_ADDRESSING_MODES::INDIRECT:
			setAddressBusFromTwoNextBytesInROM();
			std::cout << "JMP ($" << std::setfill('0') << std::setw(4) << (int) getBigEndianAddress(_addressBus) << ")";
			
			break;

		default:
			break;
	}

	_programCounter = _addressBus;
	
	std::cout.flags(f);
}

void CPU::JSR() {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	displayInstructionAsBytes((size_t) BYTES_USED::THREE_BYTES);

	incrementProgramCounter();
	setDataBusFromByteAtPC(); // get operand low byte
	_addressBus = ((word)(_dataBus) << 8);

	incrementProgramCounter();
	setDataBusFromByteAtPC(); // get operand high byte
	_addressBus |= _dataBus;

	std::cout << "JSR $" << std::setfill('0') << std::setw(4) << (int) getBigEndianAddress(_addressBus);

	_programCounter = _addressBus;

	std::cout.flags(f);
}

void CPU::LDA() {
	useFullAddressingModeSet();

	_accumulator = _dataBus;

	updateState(_accumulator);

	incrementProgramCounter();
}

void CPU::LDX() {
	usePartialAddressingModeSet(INDEX::INDEX_Y);

	_indexX = _dataBus;

	updateState(_indexX);

	incrementProgramCounter();
}

void CPU::LDY() {
	usePartialAddressingModeSet(INDEX::INDEX_X);

	_indexY = _dataBus;

	updateState(_indexY);

	incrementProgramCounter();
}

void CPU::LSR() {
	usePartialAddressingModeSet(INDEX::INDEX_X);

	incrementProgramCounter();
}

void CPU::NOP() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "NOP";

	incrementProgramCounter();
}

void CPU::ORA() {
	useFullAddressingModeSet();

	incrementProgramCounter();
}

void CPU::PHA() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "PHA";

	_addressBus = (word) _stackPointer;
	_map[(word)(_stack + _addressBus)] = _accumulator;

	_stackPointer--;

	incrementProgramCounter();
}

void CPU::PHP() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "PHP";

	_addressBus = (word) _stackPointer;
	_map[(word)(_stack + _addressBus)] = _statusFlags;

	_stackPointer--;

	incrementProgramCounter();
}

void CPU::PLA() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "PLA";
	
	_stackPointer++;
	
	_addressBus = (word) _stackPointer;
	_accumulator = _map[(word)(_stack + _addressBus)];

	incrementProgramCounter();
}

void CPU::PLP() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "PLP";

	_stackPointer++;

	_addressBus = (word) _stackPointer;
	_statusFlags = _map[(word)(_stack + _addressBus)];

	incrementProgramCounter();
}

void CPU::ROL() {
	usePartialAddressingModeSet(INDEX::INDEX_X);

	incrementProgramCounter();
}

void CPU::ROR() {
	usePartialAddressingModeSet(INDEX::INDEX_X);

	incrementProgramCounter();
}

void CPU::RTI() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "RTI";
}

void CPU::RTS() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "RTS";
}

void CPU::SBC() {
	useFullAddressingModeSet();

	_accumulator -= _dataBus - ((_statusFlags & (byte)(STATUS_FLAG::C)) ? 1 : 0);

	updateState(_accumulator, ARITHMETIC_OPERATION::SUBTRACTION);

	incrementProgramCounter();
}

void CPU::SEC() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "SEC";

	setFlag(STATUS_FLAG::C);

	incrementProgramCounter();
}

void CPU::SED() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "SED";

	setFlag(STATUS_FLAG::D);

	incrementProgramCounter();
}

void CPU::SEI() {
	displayInstructionAsBytes((size_t)BYTES_USED::ONE_BYTE);

	std::cout << "SEI";

	setFlag(STATUS_FLAG::I);

	incrementProgramCounter();
}

void CPU::STA() {
	useFullAddressingModeSet(); // exception

	incrementProgramCounter();
}

void CPU::STX() {
	usePartialAddressingModeSet(INDEX::INDEX_Y);

	incrementProgramCounter();
}

void CPU::STY() {
	usePartialAddressingModeSet(INDEX::INDEX_X);

	incrementProgramCounter();
}

void CPU::TAX() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "TAX";

	_indexX = _accumulator;

	incrementProgramCounter();
}

void CPU::TAY() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "TAY";

	_indexY = _accumulator;

	incrementProgramCounter();
}

void CPU::TSX() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "TSX";
	
	_indexX = _stackPointer;

	incrementProgramCounter();
}

void CPU::TXA() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "TXA";

	_accumulator = _indexX;

	incrementProgramCounter();
}

void CPU::TXS() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "TXS";

	_stackPointer = _indexX;

	incrementProgramCounter();
}

void CPU::TYA() {
	displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

	std::cout << "TYA";

	_accumulator = _indexY;

	incrementProgramCounter();
}

void CPU::setFlag(STATUS_FLAG flag) {
	_statusFlags |= (byte) flag;
}

void CPU::unsetFlag(STATUS_FLAG flag) {
	_statusFlags &= ~((byte) flag);
}

bool CPU::isSet(STATUS_FLAG flag) {
	return _statusFlags & (byte) flag;
}

bool CPU::isNegative(byte value) {
	return value & 0x80; // check bit 8 is 1
}

void CPU::useFullAddressingModeSet() {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	std::string const instructionName = _instructionsNames[_dataBus];

	switch (_dataBus & ADDRESSING_MODE_MASK) {
		case (byte) FULL_ADDRESSING_MODES_SET::ZEROPAGE_PRE_X: // TODO
			displayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

			incrementProgramCounter();
			setDataBusFromByteAtPC(); // get operand

			std::cout << instructionName << " ($" << std::setfill('0') << std::setw(2) << (int) _dataBus << ", X)";
			break;

		case (byte) FULL_ADDRESSING_MODES_SET::ZEROPAGE:
			displayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

			incrementProgramCounter();
			setDataBusFromByteAtPC(); // get operand

			std::cout << instructionName << " $" << std::setfill('0') << std::setw(2) << (int) _dataBus;

			_addressBus = _dataBus;
			setDataBusFromAddressBus();
			break;

		case (byte) FULL_ADDRESSING_MODES_SET::IMMEDIATE:
			displayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

			incrementProgramCounter();
			setDataBusFromByteAtPC(); // get operand

			std::cout << instructionName << " #$" << std::setfill('0') << std::setw(2) << (int) _dataBus;
			break;

		case (byte) FULL_ADDRESSING_MODES_SET::ABSOLUTE:
			displayInstructionAsBytes((size_t) BYTES_USED::THREE_BYTES);

			setAddressBusFromTwoNextBytesInROM();

			_dataBus = _map[getBigEndianAddress(_addressBus)];

			std::cout << instructionName << " $" << std::setfill('0') << std::setw(4) << (int) getBigEndianAddress(_addressBus);
			break;

		case (byte) FULL_ADDRESSING_MODES_SET::ZEROPAGE_POST_Y: // TODO
			displayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

			incrementProgramCounter();
			setDataBusFromByteAtPC(); // get operand

			std::cout << instructionName << " ($" << std::setfill('0') << std::setw(2) << (int) _dataBus << "), X";
			break;

		case (byte) FULL_ADDRESSING_MODES_SET::ZEROPAGE_X: // TODO
			displayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

			incrementProgramCounter();
			setDataBusFromByteAtPC(); // get operand

			std::cout << instructionName << " $" << std::setfill('0') << std::setw(2) << (int) _dataBus << ", X";
			break;

		case (byte) FULL_ADDRESSING_MODES_SET::ABSOLUTE_Y:
			displayInstructionAsBytes((size_t) BYTES_USED::THREE_BYTES);

			setDataBusFromByteAtPC(); // get operand low byte

			setAddressBusFromTwoNextBytesInROM();

			std::cout << instructionName << " $" << std::setfill('0') << std::setw(4) << (int) getBigEndianAddress(_addressBus) << ", Y";

			_addressBus = getLittleEndianAddress(getBigEndianAddress(_addressBus) + _indexY);
			break;

		case (byte) FULL_ADDRESSING_MODES_SET::ABSOLUTE_X:
			displayInstructionAsBytes((size_t) BYTES_USED::THREE_BYTES);

			setDataBusFromByteAtPC(); // get operand low byte

			setAddressBusFromTwoNextBytesInROM();

			std::cout << instructionName << " $" << std::setfill('0') << std::setw(4) << (int) getBigEndianAddress(_addressBus) << ", X";

			_addressBus = getLittleEndianAddress(getBigEndianAddress(_addressBus) + _indexX);
			break;

		default:
			break;
	}

	std::cout.flags(f);
}

void CPU::usePartialAddressingModeSet(INDEX index) {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	std::string const instructionName = _instructionsNames[_dataBus];

	switch (_dataBus & ADDRESSING_MODE_MASK) {
		case (byte) PARTIAL_ADDRESSING_MODES_SET::IMMEDIATE:
			displayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

			incrementProgramCounter();
			setDataBusFromByteAtPC(); // get operand

			std::cout << instructionName << " #$" << std::setfill('0') << std::setw(2) << (int) _dataBus;
			break;

		case (byte) PARTIAL_ADDRESSING_MODES_SET::ZEROPAGE:
			displayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

			incrementProgramCounter();
			setDataBusFromByteAtPC(); // get operand

			std::cout << instructionName << " $" << std::setfill('0') << std::setw(2) << (int) _dataBus;

			_addressBus = _dataBus;
			setDataBusFromAddressBus();
			break;

		case (byte) PARTIAL_ADDRESSING_MODES_SET::ACCUMULATOR:
			displayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

			std::cout << instructionName << ", A";
			break;

		case (byte) PARTIAL_ADDRESSING_MODES_SET::ABSOLUTE:
			displayInstructionAsBytes((size_t) BYTES_USED::THREE_BYTES);

			setAddressBusFromTwoNextBytesInROM();

			_dataBus = _map[getBigEndianAddress(_addressBus)];

			std::cout << instructionName << " $" << std::setfill('0') << std::setw(4) << (int) _addressBus;
			break;

		case (byte) PARTIAL_ADDRESSING_MODES_SET::ZEROPAGE_INDEXED:
			displayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

			incrementProgramCounter();
			setDataBusFromByteAtPC(); // get operand

			switch (index) {
				case INDEX::INDEX_X:
					std::cout << instructionName << " $" << std::setfill('0') << std::setw(2) << (int) _dataBus << ", X";
					break;

				case INDEX::INDEX_Y:
					std::cout << instructionName << " $" << std::setfill('0') << std::setw(2) << (int) _dataBus << ", Y";
					break;

				default:
					break;
			}
			break;

		case (byte) PARTIAL_ADDRESSING_MODES_SET::ABSOLUTE_INDEXED:
			displayInstructionAsBytes((size_t) BYTES_USED::THREE_BYTES);

			setDataBusFromByteAtPC(); // get operand low byte

			setAddressBusFromTwoNextBytesInROM();

			switch (index) {
				case INDEX::INDEX_X:
					std::cout << instructionName << " $" << std::setfill('0') << std::setw(2) << (int) _dataBus << ", X";
					break;

				case INDEX::INDEX_Y:
					std::cout << instructionName << " $" << std::setfill('0') << std::setw(2) << (int) _dataBus << ", Y";
					break;

				default:
					break;
			}

			_addressBus = getLittleEndianAddress(getBigEndianAddress(_addressBus) + _indexX);
			break;

		default:
			break;
	}

	std::cout.flags(f);
}

void CPU::incrementProgramCounter() {
	_programCounter = getLittleEndianAddress(getBigEndianAddress(_programCounter) + (word)(0x01));
}

inline void CPU::setDataBusFromByteAtPC() {
	_dataBus = _map[getBigEndianAddress(_programCounter)];
}

inline void CPU::setDataBusFromAddressBus() {
	_dataBus = _map[getBigEndianAddress(_addressBus)];
}

void CPU::setAddressBusFromTwoNextBytesInROM() {
	incrementProgramCounter();
	setDataBusFromByteAtPC(); // get operand low byte
	_addressBus = ((word)(_dataBus) << 8);

	incrementProgramCounter();
	setDataBusFromByteAtPC(); // get operand high byte
	_addressBus |= _dataBus;
}

void CPU::checkBranching(STATUS_FLAG flag, bool checkSet) {	
	// get operand
	incrementProgramCounter();
	setDataBusFromByteAtPC();

	// particularly ugly but works : if we check for a flag to be set (eg. BCS) check isSet(flag). Else check !isSet(flag)
	if (checkSet ? isSet(flag) : !isSet(flag)) {
		updateState(_dataBus);
		incrementProgramCounter();

		if (isSet(STATUS_FLAG::N)) {
			_programCounter = getLittleEndianAddress(getBigEndianAddress(_programCounter) - (byte)(0xFF - _dataBus) - (word) BYTES_USED::TWO_BYTES);
		}

		else {
			_programCounter = getLittleEndianAddress(getBigEndianAddress(_programCounter) + (byte) _dataBus);
		}

		std::cout << std::setfill('0') << std::setw(4) << (int) getBigEndianAddress(_programCounter);
	}

	else {
		updateState(_dataBus);
		incrementProgramCounter();

		if (isSet(STATUS_FLAG::N)) {
			std::cout << std::setfill('0') << std::setw(4) << (int)getBigEndianAddress(_programCounter) - (byte)(0xFF - _dataBus) - (word) BYTES_USED::TWO_BYTES;
		}

		else {
			std::cout << std::setfill('0') << std::setw(4) << (int)getBigEndianAddress(_programCounter) + _dataBus;
		}
	}

	std::cout << "    -> $" << std::setfill('0') << std::setw(4) << (int) getBigEndianAddress(_programCounter);
}

void CPU::setProgramCounterFromResetVector() {
	_readWrite = (bool) DATA_BUS_OPERATION::READ;

	_dataBus = _map[RESET_LOW];
	_addressBus = _dataBus;
	_addressBus <<= 8;

	_dataBus = _map[RESET_HIGH];
	_addressBus |= 0xFF;
	_addressBus &= (word)(~0xFF) | (word)(_dataBus);

	_programCounter = _addressBus;
}
