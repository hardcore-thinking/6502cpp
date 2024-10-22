#include "cpu.hpp"

CPU::CPU(std::vector<Byte>* ram, Word ramStart, Word ramSize, std::vector<Byte>* rom, Word romStart, Word romSize) {
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

	_map = std::vector<Byte>(MAX_ADDRESSABLE, 0x00);

	for (int i = 0; i < ramSize; i++) {
		_map[(Word)(ramStart + i)] = (*ram)[i];
	}

	for (int i = 0; i < romSize; i++) {
		_map[(Word)(romStart + i)] = (*rom)[i];
	}

	_statusFlags = (Byte) STATUS_FLAG::_;

	SetProgramCounterFromResetVector();
}

void CPU::DisplayStatus() const {
	std::cout << "N V - B D I Z C" << "\n";

	for (int i = sizeof(Byte) * 8 - 1; i >= 0; i--) {
		std::cout << ((_statusFlags >> i) & 1) << " ";
	}

	std::cout << std::endl;
}

void CPU::DisplayStatusFlag(STATUS_FLAG flag) {
	switch (flag) {
		case STATUS_FLAG::N:
			std::cout << "N : " << (IsSet(STATUS_FLAG::N) ? "true" : "false") << std::endl;
			break;

		case STATUS_FLAG::V:
			std::cout << "V : " << (IsSet(STATUS_FLAG::V) ? "true" : "false") << std::endl;
			break;

		case STATUS_FLAG::_:
			break;

		case STATUS_FLAG::B:
			std::cout << "B : " << (IsSet(STATUS_FLAG::B) ? "true" : "false") << std::endl;
			break;

		case STATUS_FLAG::D:
			std::cout << "D : " << (IsSet(STATUS_FLAG::D) ? "true" : "false") << std::endl;
			break;

		case STATUS_FLAG::I:
			std::cout << "I : " << (IsSet(STATUS_FLAG::I) ? "true" : "false") << std::endl;
			break;

		case STATUS_FLAG::Z:
			std::cout << "Z : " << (IsSet(STATUS_FLAG::Z) ? "true" : "false") << std::endl;
			break;

		case STATUS_FLAG::C:
			std::cout << "C : " << (IsSet(STATUS_FLAG::C) ? "true" : "false") << std::endl;
			break;

		default:
			break;
	}
}

void CPU::DisplayAccumulator() const {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	std::cout << "A = $" << std::setfill('0') << std::setw(2) << (int)(_accumulator) << std::endl;

	std::cout.flags(f);
}

void CPU::DisplayIndexX() const {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	std::cout << "X = $" << std::setfill('0') << std::setw(2) << (int)(_indexX) << std::endl;

	std::cout.flags(f);
}

void CPU::DisplayIndexY() const {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	std::cout << "Y = $" << std::setfill('0') << std::setw(2) << (int)(_indexY) << std::endl;

	std::cout.flags(f);
}

void CPU::DisplayRegisters() const {
	DisplayAccumulator();
	DisplayIndexX();
	DisplayIndexY();
}

void CPU::DisplayStackPointer() const {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	std::cout << "SP = $" << std::setfill('0') << std::setw(2) << (int)(_stackPointer) << std::endl;

	std::cout.flags(f);
}

void CPU::DisplayAddressBus() const {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	std::cout << "Address bus = $" << std::setfill('0') << std::setw(4) << (int)(GetBigEndianAddress(_addressBus)) << std::endl;

	std::cout.flags(f);
}

void CPU::DisplayDataBus() const {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	std::cout << "Data bus = $" << std::setfill('0') << std::setw(2) << (int)(_dataBus) << std::endl;

	std::cout.flags(f);
}

void CPU::DisplayBuses() const {
	DisplayDataBus();
	DisplayAddressBus();
}

void CPU::DisplayProgramCounter() const {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	std::cout << "PC = $" << std::setfill('0') << std::setw(4) << (int)(GetBigEndianAddress(_programCounter)) << std::endl;

	std::cout.flags(f);
}

void CPU::DisplayState() const {
	DisplayStatus();
	DisplayRegisters();
	DisplayStackPointer();
	DisplayBuses();
	DisplayProgramCounter();
}

void CPU::DisplayRAM() const {
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

		std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(_map[(Word)(_ram + i)]) << " ";
	}

	std::cout << std::endl;

	std::cout.flags(f);
}

void CPU::DisplayZeroPage() const {
	DisplayRAMPage(0x00);
}

void CPU::DisplayRAMPage(Byte page) const {
	std::ios_base::fmtflags f(std::cout.flags());

	Word const pageAddress = (Word)(page << 8);

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

		std::cout << std::setfill('0') << std::setw(2) << (int) _map[(Word)(_ram + pageAddress + i)] << " ";
	}

	std::cout << std::endl;

	std::cout.flags(f);
}

void CPU::DisplayStack() const {
	DisplayRAMPage(0x01);
}

void CPU::DisplayROM(bool stopOnBreak) const {
	std::ios_base::fmtflags f(std::cout.flags());

	std::cout << "\t";
	std::cout << std::hex;

	for (int i = 0; i < 16; i++) {
		std::cout << std::uppercase << std::setw(2) << std::setfill('0') << i << " ";
	}

	std::cout << std::endl << "$" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << _rom << "\t";
	for (int i = 0; i < MAX_ROM_SIZE; i++) {
		if (i != 0 && i % 16 == 0) {
			if (_map[(Word)(_rom + i)] == 0x00 && stopOnBreak) break; // TO DELETE
			std::cout << std::endl << "$" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << _rom + i << "\t";
		}

		std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(_map[(Word)(_rom + i)]) << " ";
	}

	std::cout << std::endl;

	std::cout.flags(f);
}

void CPU::DisplayInstructionAsBytes(size_t bytesN) const {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	for (int i = 0; i < (bytesN - 1); i++) {
		std::cout << std::setfill('0') << std::setw(2) << (int) _map[(Word)(GetBigEndianAddress(_programCounter) + i)] << " ";
	}

	std::cout << std::setfill('0') << std::setw(2) << (int) _map[(Word)(GetBigEndianAddress(_programCounter) + (bytesN - 1))];

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

void CPU::DisplayMap() const {
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

void CPU::Run(bool stepByStep) {
	while (_map[GetBigEndianAddress(_programCounter)] != 0x00) {
		FetchAndExecute();
		if (stepByStep) {
			char _ = getchar(); // wait for enter press
		}
		else {
			std::cout << std::endl;
		}
	}
}

void CPU::FetchAndExecute()  {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	_readWrite = (bool)(DATA_BUS_OPERATION::READ);
	SetDataBusFromByteAtPC(); // get opcode

	std::cout << "$" << std::setfill('0') << std::setw(4) << GetBigEndianAddress(_programCounter) << "    ";

	if (this->_instructionsMatrix[_dataBus] != nullptr) {
		(this->*_instructionsMatrix[_dataBus])();
	}

	else {
		std::cout << "(no instruction)" << std::endl;
	}

	std::cout.flags(f);
}

void CPU::UpdateState(Byte reg, Byte* cmpVal, ARITHMETIC_OPERATION operation) {
	// check N and Z flag
	if (reg == (Byte)(0x00)) {
		UnsetFlag(STATUS_FLAG::N);
		SetFlag(STATUS_FLAG::Z);
	}

	else if (reg >= (Byte)(0x80) && reg <= (Byte)(0xFF)) {
		SetFlag(STATUS_FLAG::N);
		UnsetFlag(STATUS_FLAG::Z);
	}

	else {
		UnsetFlag(STATUS_FLAG::N);
		UnsetFlag(STATUS_FLAG::Z);
	}

	if (cmpVal != nullptr) {
		if (reg < *cmpVal) {
			UnsetFlag(STATUS_FLAG::Z);
			UnsetFlag(STATUS_FLAG::C);
			
			if ((reg - *cmpVal) & 0x80) SetFlag(STATUS_FLAG::N); else UnsetFlag(STATUS_FLAG::N);
		}

		else if (reg > *cmpVal) {
			UnsetFlag(STATUS_FLAG::Z);
			SetFlag(STATUS_FLAG::C);

			if ((reg - *cmpVal) & 0x80) SetFlag(STATUS_FLAG::N); else UnsetFlag(STATUS_FLAG::N);
		}

		else {
			SetFlag(STATUS_FLAG::Z);
			SetFlag(STATUS_FLAG::C);
			UnsetFlag(STATUS_FLAG::N);
		}
	}

	// check V flag
	switch (operation) {
		case ARITHMETIC_OPERATION::ADDITION:
			// if sides of the operation are both negative
			if (IsNegative(reg) && IsNegative(_accumulator)) {
				// if their sum is positive
				if (!IsNegative((Byte)(reg + _accumulator))) {
					SetFlag(STATUS_FLAG::V);
				}
				else {
					UnsetFlag(STATUS_FLAG::V);
				}
			}
			break;

		case ARITHMETIC_OPERATION::SUBTRACTION:
			// if sides of the operation are both negative
			if (!IsNegative(reg) && !IsNegative(_accumulator)) {
				// if their sum is negative
				if (IsNegative((Byte)(reg + _accumulator))) {
					SetFlag(STATUS_FLAG::V);
				}
				else {
					UnsetFlag(STATUS_FLAG::V);
				}
			}
			break;

		default:
			UnsetFlag(STATUS_FLAG::V);
			break;
	}
}

void CPU::ADC() {
	UseFullAddressingModeSet();

	UpdateState(_dataBus, nullptr, ARITHMETIC_OPERATION::ADDITION);

	_accumulator += _dataBus + ((_statusFlags & (Byte)(STATUS_FLAG::C)) ? 1 : 0);

	IncrementProgramCounter();
}

void CPU::AND() {
	UseFullAddressingModeSet();

	_accumulator &= _dataBus;

	IncrementProgramCounter();
}

void CPU::ASL() {
	UsePartialAddressingModeSet(INDEX::INDEX_X);

	// TODO

	IncrementProgramCounter();
}

void CPU::BCC() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::TWO_BYTES));

	std::cout << "BCC $";
	CheckBranching(STATUS_FLAG::C, false);
}

void CPU::BCS() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::TWO_BYTES));

	std::cout << "BCS $";
	CheckBranching(STATUS_FLAG::C, true);
}

void CPU::BEQ() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::TWO_BYTES));

	std::cout << "BEQ $";
	CheckBranching(STATUS_FLAG::Z, true);
}

void CPU::BIT() {
	UsePartialAddressingModeSet();

	_dataBus = _accumulator & _map[_addressBus];

	if (_dataBus & (Byte)(STATUS_FLAG::N)) { SetFlag(STATUS_FLAG::N); } else { UnsetFlag(STATUS_FLAG::N); }
	if (_dataBus & (Byte)(STATUS_FLAG::V)) { SetFlag(STATUS_FLAG::V); } else { UnsetFlag(STATUS_FLAG::V); }

	IncrementProgramCounter();
}

void CPU::BMI() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::TWO_BYTES));

	std::cout << "BMI $";
	CheckBranching(STATUS_FLAG::N, true);
}

void CPU::BNE() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::TWO_BYTES));
	
	std::cout << "BNE $";
	CheckBranching(STATUS_FLAG::Z, false);
}

void CPU::BPL() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::TWO_BYTES));

	std::cout << "BPL $";
	CheckBranching(STATUS_FLAG::N, false);
}

void CPU::BRK() {
	std::cout << "BRK";

	// TODO

	IncrementProgramCounter();
}

void CPU::BVC() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::TWO_BYTES));

	std::cout << "BVC $";
	CheckBranching(STATUS_FLAG::V, false);
}

void CPU::BVS() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::TWO_BYTES));
	
	std::cout << "BVS $";
	CheckBranching(STATUS_FLAG::V, true);
}

void CPU::CLC() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "CLC";

	UnsetFlag(STATUS_FLAG::C);

	IncrementProgramCounter();
}

void CPU::CLD() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "CLD";

	UnsetFlag(STATUS_FLAG::D);

	IncrementProgramCounter();
}

void CPU::CLI() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "CLI";

	UnsetFlag(STATUS_FLAG::I);

	IncrementProgramCounter();
}

void CPU::CLV() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "CLV";

	UnsetFlag(STATUS_FLAG::V);

	IncrementProgramCounter();
}

void CPU::CMP() {
	UseFullAddressingModeSet();

	_dataBus = _accumulator - _dataBus;

	IncrementProgramCounter();
}

void CPU::CPX() {
	UsePartialAddressingModeSet();

	_dataBus = _indexX - _dataBus;

	UpdateState(_dataBus);

	IncrementProgramCounter();
}

void CPU::CPY() {
	UsePartialAddressingModeSet();

	_dataBus = _indexY - _dataBus;

	UpdateState(_dataBus);

	IncrementProgramCounter();
}

void CPU::DEC() {
	UsePartialAddressingModeSet(INDEX::INDEX_X);

	// TODO

	IncrementProgramCounter();
}

void CPU::DEX() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "DEX";

	--_indexX;

	IncrementProgramCounter();
}

void CPU::DEY() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "DEY";
	
	--_indexY;

	IncrementProgramCounter();
}

void CPU::EOR() {
	UseFullAddressingModeSet();

	_accumulator ^= _dataBus;

	IncrementProgramCounter();
}

void CPU::INC() {
	UsePartialAddressingModeSet(INDEX::INDEX_X);

	++_map[_addressBus];

	IncrementProgramCounter();
}

void CPU::INX() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "INX";

	++_indexX;

	IncrementProgramCounter();
}

void CPU::INY() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "INY";

	++_indexY;

	IncrementProgramCounter();
}

void CPU::JMP() {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	DisplayInstructionAsBytes((size_t) BYTES_USED::THREE_BYTES);

	switch (_dataBus) {
		case (Byte) JMP_ADDRESSING_MODES::ABSOLUTE:
			SetAddressBusFromTwoNextBytesInROM();
			std::cout << "JMP $" << std::setfill('0') << std::setw(4) << (int)(GetBigEndianAddress(_addressBus));
			break;

		case (Byte) JMP_ADDRESSING_MODES::INDIRECT:
			SetAddressBusFromTwoNextBytesInROM();
			std::cout << "JMP ($" << std::setfill('0') << std::setw(4) << (int)(GetBigEndianAddress(_addressBus)) << ")";
			
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

	DisplayInstructionAsBytes((size_t) BYTES_USED::THREE_BYTES);

	/// BEGIN INSTRUCTION
	PushToStack((Byte)GetLittleEndianAddress(GetBigEndianAddress(_programCounter) + 3)); // saving next address high byte in stack for RTS
	PushToStack((Byte)(GetBigEndianAddress(_programCounter) + 3)); // saving next address low byte in stack for RTS

	IncrementProgramCounter();
	SetDataBusFromByteAtPC(); // get operand low byte
	_addressBus = ((Word)(_dataBus) << 8);

	IncrementProgramCounter();
	SetDataBusFromByteAtPC(); // get operand high byte
	_addressBus |= _dataBus;

	_programCounter = _addressBus;
	/// END INSTRUCTION

	std::cout << "JSR $" << std::setfill('0') << std::setw(4) << (int)GetBigEndianAddress(_addressBus);

	std::cout.flags(f);
}

void CPU::LDA() {
	UseFullAddressingModeSet();

	_accumulator = _dataBus;

	UpdateState(_accumulator);

	IncrementProgramCounter();
}

void CPU::LDX() {
	UsePartialAddressingModeSet(INDEX::INDEX_Y);

	_indexX = _dataBus;

	UpdateState(_indexX);

	IncrementProgramCounter();
}

void CPU::LDY() {
	UsePartialAddressingModeSet(INDEX::INDEX_X);

	_indexY = _dataBus;

	UpdateState(_indexY);

	IncrementProgramCounter();
}

void CPU::LSR() {
	UsePartialAddressingModeSet(INDEX::INDEX_X);
	
	// TODO

	IncrementProgramCounter();
}

void CPU::NOP() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "NOP";

	IncrementProgramCounter();
}

void CPU::ORA() {
	UseFullAddressingModeSet();

	// TODO

	IncrementProgramCounter();
}

void CPU::PHA() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "PHA";

	_addressBus = (Word) _stackPointer;
	_map[(Word)(_stack + _addressBus)] = _accumulator;

	_stackPointer--;

	IncrementProgramCounter();
}

void CPU::PHP() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "PHP";

	_addressBus = (Word) _stackPointer;
	_map[(Word)(_stack + _addressBus)] = _statusFlags;

	_stackPointer--;

	IncrementProgramCounter();
}

void CPU::PLA() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "PLA";
	
	_stackPointer++;
	
	_addressBus = (Word) _stackPointer;
	_accumulator = _map[(Word)(_stack + _addressBus)];

	IncrementProgramCounter();
}

void CPU::PLP() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "PLP";

	_stackPointer++;

	_addressBus = (Word) _stackPointer;
	_statusFlags = _map[(Word)(_stack + _addressBus)];

	IncrementProgramCounter();
}

void CPU::ROL() {
	UsePartialAddressingModeSet(INDEX::INDEX_X);

	// TODO

	IncrementProgramCounter();
}

void CPU::ROR() {
	UsePartialAddressingModeSet(INDEX::INDEX_X);

	// TODO

	IncrementProgramCounter();
}

void CPU::RTI() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	// TODO

	std::cout << "RTI";
}

void CPU::RTS() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "RTS";

	_addressBus = PullFromStack() << 8;
	_addressBus |= PullFromStack();

	_programCounter = _addressBus;
}

void CPU::SBC() {
	UseFullAddressingModeSet();

	_accumulator -= _dataBus - ((_statusFlags & (Byte)(STATUS_FLAG::C)) ? 1 : 0);
	UpdateState(_accumulator, nullptr, ARITHMETIC_OPERATION::SUBTRACTION);

	IncrementProgramCounter();
}

void CPU::SEC() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "SEC";

	SetFlag(STATUS_FLAG::C);

	IncrementProgramCounter();
}

void CPU::SED() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "SED";

	SetFlag(STATUS_FLAG::D);

	IncrementProgramCounter();
}

void CPU::SEI() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "SEI";

	SetFlag(STATUS_FLAG::I);

	IncrementProgramCounter();
}

void CPU::STA() {
	UseFullAddressingModeSet(); // exception

	_indexY = _map[_addressBus];

	IncrementProgramCounter();
}

void CPU::STX() {
	UsePartialAddressingModeSet(INDEX::INDEX_Y);

	_indexX = _map[_addressBus];

	IncrementProgramCounter();
}

void CPU::STY() {
	UsePartialAddressingModeSet(INDEX::INDEX_X);

	_indexY = _map[_addressBus];

	IncrementProgramCounter();
}

void CPU::TAX() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "TAX";

	_indexX = _accumulator;

	IncrementProgramCounter();
}

void CPU::TAY() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "TAY";

	_indexY = _accumulator;

	IncrementProgramCounter();
}

void CPU::TSX() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "TSX";
	
	_indexX = _stackPointer;

	IncrementProgramCounter();
}

void CPU::TXA() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "TXA";

	_accumulator = _indexX;

	IncrementProgramCounter();
}

void CPU::TXS() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "TXS";

	_stackPointer = _indexX;

	IncrementProgramCounter();
}

void CPU::TYA() {
	DisplayInstructionAsBytes((size_t)(BYTES_USED::ONE_BYTE));

	std::cout << "TYA";

	_accumulator = _indexY;

	IncrementProgramCounter();
}

void CPU::SetFlag(STATUS_FLAG flag) {
	_statusFlags |= (Byte)(flag);
}

void CPU::UnsetFlag(STATUS_FLAG flag) {
	_statusFlags &= ~((Byte)(flag));
}

bool CPU::IsSet(STATUS_FLAG flag) const {
	return _statusFlags & (Byte)(flag);
}

bool CPU::IsNegative(Byte value) const {
	return value & 0x80; // check bit 8 is 1
}

void CPU::UseFullAddressingModeSet() {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	std::string const instructionName = _instructionsNames[_dataBus];

	switch (_dataBus & ADDRESSING_MODE_MASK) {
		case (Byte) FULL_ADDRESSING_MODES_SET::ZEROPAGE_PRE_X: // TODO
			DisplayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

			IncrementProgramCounter();
			SetDataBusFromByteAtPC(); // get operand

			std::cout << instructionName << " ($" << std::setfill('0') << std::setw(2) << (int)(_dataBus) << ", X)";
			break;

		case (Byte) FULL_ADDRESSING_MODES_SET::ZEROPAGE:
			DisplayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

			IncrementProgramCounter();
			SetDataBusFromByteAtPC(); // get operand

			std::cout << instructionName << " $" << std::setfill('0') << std::setw(2) << (int)(_dataBus);

			_addressBus = _dataBus;
			SetDataBusFromAddressBus();
			break;

		case (Byte) FULL_ADDRESSING_MODES_SET::IMMEDIATE:
			DisplayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

			IncrementProgramCounter();
			SetDataBusFromByteAtPC(); // get operand

			std::cout << instructionName << " #$" << std::setfill('0') << std::setw(2) << (int)(_dataBus);
			break;

		case (Byte) FULL_ADDRESSING_MODES_SET::ABSOLUTE:
			DisplayInstructionAsBytes((size_t) BYTES_USED::THREE_BYTES);

			SetAddressBusFromTwoNextBytesInROM();

			_dataBus = _map[GetBigEndianAddress(_addressBus)];

			std::cout << instructionName << " $" << std::setfill('0') << std::setw(4) << (int)(GetBigEndianAddress(_addressBus));
			break;

		case (Byte) FULL_ADDRESSING_MODES_SET::ZEROPAGE_POST_Y: // TODO
			DisplayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

			IncrementProgramCounter();
			SetDataBusFromByteAtPC(); // get operand

			std::cout << instructionName << " ($" << std::setfill('0') << std::setw(2) << (int)(_dataBus) << "), X";
			break;

		case (Byte) FULL_ADDRESSING_MODES_SET::ZEROPAGE_X: // TODO
			DisplayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

			IncrementProgramCounter();
			SetDataBusFromByteAtPC(); // get operand

			std::cout << instructionName << " $" << std::setfill('0') << std::setw(2) << (int)(_dataBus) << ", X";
			break;

		case (Byte) FULL_ADDRESSING_MODES_SET::ABSOLUTE_Y:
			DisplayInstructionAsBytes((size_t) BYTES_USED::THREE_BYTES);

			SetDataBusFromByteAtPC(); // get operand low byte

			SetAddressBusFromTwoNextBytesInROM();

			std::cout << instructionName << " $" << std::setfill('0') << std::setw(4) << (int)(GetBigEndianAddress(_addressBus)) << ", Y";

			_addressBus = GetLittleEndianAddress(GetBigEndianAddress(_addressBus) + _indexY);
			break;

		case (Byte) FULL_ADDRESSING_MODES_SET::ABSOLUTE_X:
			DisplayInstructionAsBytes((size_t) BYTES_USED::THREE_BYTES);

			SetDataBusFromByteAtPC(); // get operand low byte

			SetAddressBusFromTwoNextBytesInROM();

			std::cout << instructionName << " $" << std::setfill('0') << std::setw(4) << (int)(GetBigEndianAddress(_addressBus)) << ", X";

			_addressBus = GetLittleEndianAddress(GetBigEndianAddress(_addressBus) + _indexX);
			break;

		default:
			break;
	}

	std::cout.flags(f);
}

void CPU::UsePartialAddressingModeSet(INDEX index) {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::hex << std::uppercase;

	std::string const instructionName = _instructionsNames[_dataBus];

	switch (_dataBus & ADDRESSING_MODE_MASK) {
		case (Byte) PARTIAL_ADDRESSING_MODES_SET::IMMEDIATE:
			DisplayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

			IncrementProgramCounter();
			SetDataBusFromByteAtPC(); // get operand

			std::cout << instructionName << " #$" << std::setfill('0') << std::setw(2) << (int)(_dataBus);
			break;

		case (Byte) PARTIAL_ADDRESSING_MODES_SET::ZEROPAGE:
			DisplayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

			IncrementProgramCounter();
			SetDataBusFromByteAtPC(); // get operand

			std::cout << instructionName << " $" << std::setfill('0') << std::setw(2) << (int)(_dataBus);

			_addressBus = _dataBus;
			SetDataBusFromAddressBus();
			break;

		case (Byte) PARTIAL_ADDRESSING_MODES_SET::ACCUMULATOR:
			DisplayInstructionAsBytes((size_t) BYTES_USED::ONE_BYTE);

			std::cout << instructionName << ", A";
			break;

		case (Byte) PARTIAL_ADDRESSING_MODES_SET::ABSOLUTE:
			DisplayInstructionAsBytes((size_t) BYTES_USED::THREE_BYTES);

			SetAddressBusFromTwoNextBytesInROM();

			_dataBus = _map[GetBigEndianAddress(_addressBus)];

			std::cout << instructionName << " $" << std::setfill('0') << std::setw(4) << (int)(_addressBus);
			break;

		case (Byte) PARTIAL_ADDRESSING_MODES_SET::ZEROPAGE_INDEXED:
			DisplayInstructionAsBytes((size_t) BYTES_USED::TWO_BYTES);

			IncrementProgramCounter();
			SetDataBusFromByteAtPC(); // get operand

			switch (index) {
				case INDEX::INDEX_X:
					std::cout << instructionName << " $" << std::setfill('0') << std::setw(2) << (int)(_dataBus) << ", X";
					break;

				case INDEX::INDEX_Y:
					std::cout << instructionName << " $" << std::setfill('0') << std::setw(2) << (int)(_dataBus) << ", Y";
					break;

				default:
					break;
			}
			break;

		case (Byte) PARTIAL_ADDRESSING_MODES_SET::ABSOLUTE_INDEXED:
			DisplayInstructionAsBytes((size_t) BYTES_USED::THREE_BYTES);

			SetDataBusFromByteAtPC(); // get operand low byte

			SetAddressBusFromTwoNextBytesInROM();

			switch (index) {
				case INDEX::INDEX_X:
					std::cout << instructionName << " $" << std::setfill('0') << std::setw(2) << (int)(_dataBus) << ", X";
					break;

				case INDEX::INDEX_Y:
					std::cout << instructionName << " $" << std::setfill('0') << std::setw(2) << (int)(_dataBus) << ", Y";
					break;

				default:
					break;
			}

			_addressBus = GetLittleEndianAddress(GetBigEndianAddress(_addressBus) + _indexX);
			break;

		default:
			break;
	}

	std::cout.flags(f);
}

void CPU::IncrementProgramCounter() {
	_programCounter = GetLittleEndianAddress(GetBigEndianAddress(_programCounter) + (Word)(0x01));
}

inline void CPU::SetDataBusFromByteAtPC() {
	_dataBus = _map[GetBigEndianAddress(_programCounter)];
}

inline void CPU::SetDataBusFromAddressBus() {
	_dataBus = _map[GetBigEndianAddress(_addressBus)];
}

void CPU::SetAddressBusFromTwoNextBytesInROM() {
	IncrementProgramCounter();
	SetDataBusFromByteAtPC(); // get operand low byte
	_addressBus = ((Word)(_dataBus) << 8);

	IncrementProgramCounter();
	SetDataBusFromByteAtPC(); // get operand high byte
	_addressBus |= _dataBus;
}

void CPU::PushToStack(Byte value) {
	_map[(Word)(_stack + _stackPointer)] = value; // set value to the stack
	_stackPointer--;                              // decrement stack pointer
}

Byte CPU::PullFromStack() {
	_stackPointer++;                             // increment stack pointer
	return _map[(Word)(_stack + _stackPointer)]; // return value from the stack
}

void CPU::CheckBranching(STATUS_FLAG flag, bool checkSet) {	
	// get operand
	IncrementProgramCounter();
	SetDataBusFromByteAtPC();

	// particularly ugly but works : if we check for a flag to be set (eg. BCS) check isSet(flag). Else check !isSet(flag)
	if (checkSet ? IsSet(flag) : !IsSet(flag)) {
		UpdateState(_accumulator, &_dataBus);
		IncrementProgramCounter();

		if (IsSet(STATUS_FLAG::N)) {
			_programCounter = GetLittleEndianAddress(GetBigEndianAddress(_programCounter) - (Byte)(0xFF - _dataBus) - (Word)(BYTES_USED::ONE_BYTE));
		}

		else {
			_programCounter = GetLittleEndianAddress(GetBigEndianAddress(_programCounter) + (Byte)(_dataBus));
		}

		std::cout << std::setfill('0') << std::setw(4) << (int)(GetBigEndianAddress(_programCounter));
	}

	else {
		UpdateState(_accumulator, &_dataBus);
		IncrementProgramCounter();

		if (IsSet(STATUS_FLAG::N)) {
			std::cout << std::setfill('0') << std::setw(4) << (int)(GetBigEndianAddress(_programCounter) - (Byte)(0xFF - _dataBus) - (Word)(BYTES_USED::ONE_BYTE));
		}

		else {
			std::cout << std::setfill('0') << std::setw(4) << (int)(GetBigEndianAddress(_programCounter) + _dataBus);
		}
	}

	//std::cout << "    -> $" << std::setfill('0') << std::setw(4) << (int) GetBigEndianAddress(_programCounter);
}

void CPU::SetProgramCounterFromResetVector() {
	_readWrite = (bool) DATA_BUS_OPERATION::READ;

	_dataBus = _map[RESET_LOW];
	_addressBus = _dataBus;
	_addressBus <<= 8;

	_dataBus = _map[RESET_HIGH];
	_addressBus |= 0xFF;
	_addressBus &= (Word)(~0xFF) | (Word)(_dataBus);

	_programCounter = _addressBus;
}
