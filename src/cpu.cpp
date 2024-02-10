#include "cpu.hpp"

CPU::CPU(std::vector<byte>* ram) {
	_ram = ram;
}

void CPU::displayState() const {
	std::cout << "N V - B D I Z C" << "\n";
	for (int i = sizeof(byte) * 8 - 1; i >= 0; i--) { std::cout << ((_statusFlags >> i) & 1) << " "; }
	std::cout << std::endl;

	std::cout << "A = $" << std::hex << std::setfill('0') << std::setw(2) << (int) _accumulator << std::endl;
	std::cout << "X = $" << std::hex << std::setfill('0') << std::setw(2) << (int) _indexX << std::endl;
	std::cout << "Y = $" << std::hex << std::setfill('0') << std::setw(2) << (int) _indexY << std::endl;
	std::cout << "SP = $" << std::hex << std::setfill('0') << std::setw(2) << (int) _stackPointer << std::endl;
	std::cout << "PC = $" << std::hex << std::setfill('0') << std::setw(4) << (int) _programCounter << std::endl;
	std::cout << "Address = $" << std::hex << std::setfill('0') << std::setw(4) << (int) _addressBus << std::endl;

	std::ios_base::fmtflags f(std::cout.flags());
}

void CPU::updateState(byte value) {
	if (value == (byte) 0) {
		unsetFlag(STATUS_FLAG::N);
		setFlag(STATUS_FLAG::Z);
	}

	else if (value >= (byte)0x80 && value <= 0xFF) {
		setFlag(STATUS_FLAG::N);
		unsetFlag(STATUS_FLAG::Z);
	}

	else {
		unsetFlag(STATUS_FLAG::N);
		unsetFlag(STATUS_FLAG::Z);
	}
}

void CPU::lda(byte opcode, byte operand) {
	switch (opcode) {
		case 0xA9: // immediate
			if (_ram) {
				_accumulator = operand;
			}
			break;
		case 0xA5: // zeropage
			if (_ram) {
				_accumulator = (*_ram)[(word)(operand)];
			}
			break;
		case 0xB5: // zeropage, X
			if (_ram) {
				_accumulator = (*_ram)[(word)(operand + _indexX)];
			}
			break;
		case 0xA1: // (indirect, X)
			if (_ram) {
				word zeroPageIndex = (word)((byte)(operand + _indexX));
				if (zeroPageIndex == (word) 0xFF) {
					_addressBus = ((word)(*_ram)[(word)(0x00)] << 8) | (word)(*_ram)[(word)(0xFF)];
				}

				else {
					_addressBus = ((word)(*_ram)[(word)(zeroPageIndex) + word(1)] << 8) | (word)(*_ram)[(word)(zeroPageIndex)];
				}

				_accumulator = (*_ram)[_addressBus];
			}
			break;
		case 0xB1: // (indirect), Y
			if (_ram) {
				_addressBus = (((word)(*_ram)[(word)(operand) + (word)(0x01)] << 8) | (word)(*_ram)[(word)(operand)]) + (word)(_indexY);
				
				_accumulator = (*_ram)[_addressBus];
			}
			break;
		default:
			break;
	}

	updateState(_accumulator);
}

void CPU::lda(byte opcode, word operand) {
	switch (opcode) {
		case 0xAD: // absolute
			if (_ram) {
				_accumulator = (*_ram)[operand];
			}
			break;
		case 0xBD: // absolute, X
			if (_ram) {
				_accumulator = (*_ram)[operand + _indexX];
			}
			break;
		case 0xB9: // absolute, Y
			if (_ram) {
				_accumulator = (*_ram)[operand + _indexY];
			}
			break;
		default:
			break;
	}

	updateState(_accumulator);
}

void CPU::ldx(byte opcode, byte operand) {
	switch (opcode) {
	case 0xA2: // immediate
		if (_ram) {
			_indexX = operand;
		}
		break;
	case 0xA6: // zeropage
		break;
	case 0xB6: // zeropage, Y
		break;
	default:
		break;
	}
	
	updateState(_indexX);
}

void CPU::ldx(byte opcode, word operand) {
	switch (opcode) {
	case 0xAE: // absolute
		if (_ram) {
			_indexX = (*_ram)[operand];
		}
		break;
	case 0xBE: // absolute, Y
		break;
	default:
		break;
	}

	updateState(_indexX);
}

void CPU::ldy(byte opcode, byte operand) {
	switch (opcode) {
		case 0xA0: // immediate
			if (_ram) {
				_indexY = operand;
			}
			break;
		case 0xA4: // zeropage
			break;
		case 0xB4: // zeropage, Y
			break;
		default:
			break;
	}

	updateState(_indexY);
}

void CPU::ldy(byte opcode, word operand) {
	switch (opcode) {
		case 0xAC: // absolute
			break;
		case 0xBC: // absolute, Y
			break;
		default:
			break;
	}

	updateState(_indexY);
}

void CPU::sta(byte opcode, byte operand) {
	switch (opcode) {
		case 0x85: // zeropage
			if (_ram) {
				(*_ram)[(word) operand] = _accumulator;
			}
			break;
		case 0x95: // zeropage, X
			break;
		case 0x81: // (indirect, X)
			break;
		case 0x91: // (indirect), Y
			break;
		default:
			break;
	}
}

void CPU::sta(byte opcode, word operand) { 
	switch (opcode) {
		case 0x8D: // absolute
			if (_ram) {
				(*_ram)[operand] = _accumulator;
			}
			break;
		case 0x9D: // absolute, X
			break;
		case 0x99: // absolute, Y
			break;
		default:
			break;
	}
}

//void CPU::stx(byte opcode, word operand) {
//	if (_ram) (*_ram)[address] = _indexX;
//}
//
//void CPU::sty(byte opcode, word operand) {
//	if (_ram) (*_ram)[address] = _indexY;
//}

void CPU::clc() { unsetFlag(STATUS_FLAG::C); }
void CPU::sec() { setFlag(STATUS_FLAG::C); }

void CPU::cli() { unsetFlag(STATUS_FLAG::I); }
void CPU::sei() { setFlag(STATUS_FLAG::I); }

void CPU::cld() { unsetFlag(STATUS_FLAG::D); }
void CPU::sed() { setFlag(STATUS_FLAG::D); }

void CPU::clv() { unsetFlag(STATUS_FLAG::V); }

void CPU::tax() { _indexX = _accumulator; }
void CPU::tay() { _indexY = _accumulator; }
void CPU::tsx() { _indexX = _stackPointer; }
void CPU::txa() { _accumulator = _indexX; }
void CPU::txs() { _stackPointer = _indexX; }
void CPU::tya() { _accumulator = _indexY; }

//void CPU::dec(byte address) { if (_ram) --(*_ram)[(word)address]; }
//void CPU::dec(word address) { if (_ram) --(*_ram)[address]; }

void CPU::setFlag(STATUS_FLAG flag) { _statusFlags ^= (byte) flag; }
void CPU::unsetFlag(STATUS_FLAG flag) { _statusFlags &= ~((byte) flag); }
