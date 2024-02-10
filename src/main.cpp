#include <iostream>
#include <vector>

#include "cpu.hpp"

void displayRAM(std::vector<byte>* ram) {
	std::cout << "\t";

	for (int i = 0; i < 16; i++) {
		std::cout << std::hex << std::setw(2) << i << " ";
	}
;
	std::cout << std::endl << "$" << std::hex << std::setw(4) << std::setfill('0') << 0 << "\t";

	for (int i = 0; i < MAX_RAM_SIZE; i++) {
		if (i != 0 && i % 16 == 0) {
			std::cout << std::endl << "$" << std::hex << std::setw(4) << std::setfill('0') << i << "\t";
		}
		
		std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>((*ram)[i]) << " ";
	}

	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::endl;
}

int main(int argc, char* argv[]) {
	std::vector<byte> ram(MAX_RAM_SIZE, (byte) 0x00);

	CPU cpu(&ram);

	for (int i = MAX_RAM_SIZE - 1; i >= 0; i--) {
		cpu.lda(0xA9, (byte) i);
		
		if ((MAX_RAM_SIZE - 1) - i < 0x100) {
			cpu.sta(0x85, (byte) 0x00);
		}

		else {
			cpu.sta(0x8D, (word) 0x00);
		}
	}
	
	cpu.displayState();

	/*cpu.lda(0xA9, (byte) 0x87);
	cpu.sta(0x85, (byte) 0x04);
	cpu.lda(0xA9, (byte) 0x97);
	cpu.sta(0x85, (byte) 0x87);
	cpu.ldx(0xA2, (byte) 0x02);
	cpu.lda(0xA9, (byte) 0xE9);
	cpu.sta(0x8D, (word) 0xFA87);
	cpu.lda(0xA1, (byte) 0x02);

	displayRAM(&ram);
	cpu.displayState();*/

	cpu.lda(0xA9, (byte) 0x87);
	cpu.sta(0x85, (byte) 0x04);
	cpu.lda(0xA9, (byte) 0x97);
	cpu.sta(0x85, (byte) 0x89);
	cpu.ldy(0xA0, (byte) 0x02);
	cpu.lda(0xB1, (byte) 0x04);

	displayRAM(&ram);
	cpu.displayState();

	//cpu.sec();
	//cpu.displayState(); std::cout << std::endl;

	//cpu.clc();
	//cpu.displayState(); std::cout << std::endl;

	//cpu.clv();
	//cpu.displayState(); std::cout << std::endl;

	//cpu.ldy((u8) 0x54);
	//cpu.displayState(); std::cout << std::endl;

	//cpu.ldx((u8) 0x9B);
	//cpu.displayState(); std::cout << std::endl;

	//cpu.txs();
	//cpu.displayState(); std::cout << std::endl;

	return 0;
}