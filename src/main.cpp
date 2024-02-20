#include <iostream>
#include <vector>
#include <fstream>

#include "cpu.hpp"

constexpr int MAX_RAM_SIZE = 0x800;
constexpr int MAX_ROM_SIZE = 0x8000;

void displayRAM(std::vector<byte> const& ram) {
	std::cout << "\t";
	std::cout << std::hex;

	for (int i = 0; i < 16; i++) {
		std::cout << std::uppercase << std::setw(2) << std::setfill('0') << i << " ";
	}

	std::cout << std::endl << "$" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << 0 << "\t";

	for (int i = 0; i < MAX_RAM_SIZE; i++) {
		if (i != 0 && i % 16 == 0) {
			std::cout << std::endl << "$" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << i << "\t";
		}

		std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(ram[i]) << " ";
	}

	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::endl;
}

void displayRAMPage(std::vector<byte> const& ram, byte page) {
	word const pageAddress = (word)(page << 8);

	std::cout << "\t";

	for (int i = 0; i < 16; i++) {
		std::cout << std::uppercase << std::setw(2) << std::setfill('0') << i << " ";
	}

	std::cout << std::hex << std::uppercase;

	std::cout << std::endl << "$" << std::setfill('0') << std::setw(4) << pageAddress << "\t";
	for (int i = 0; i < 0xFF + 1; i++) {
		if (i != 0 && i % 16 == 0) {
			std::cout << std::endl << "$" << std::setw(4) << std::setfill('0') << i << "\t";
		}

		std::cout << std::setfill('0') << std::setw(2) << (int) ram[(word)(pageAddress + i)] << " ";
	}

	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::endl;
}

void loadRAM(std::vector<byte>& ram, std::string filepath) {
	std::ifstream ram_load(filepath, std::ios::in | std::ios::binary | std::ios::ate);

	if (ram_load.is_open()) {
		const std::streampos fileSize = ram_load.tellg();
		ram_load.seekg(0, std::ios::beg);

		ram_load.read(reinterpret_cast<char*>(ram.data()), static_cast<std::streamsize>(MAX_RAM_SIZE));
	}
}

int main(int argc, char* argv[]) {
	std::vector<byte> ram(MAX_RAM_SIZE, (byte) 0x00);
	
	std::vector<byte> rom(MAX_ROM_SIZE, (byte) 0x00);

	// LDA $057D
	rom[0x0000] = 0xAD;
	rom[0x0001] = 0x7D;
	rom[0x0002] = 0x05;

	// reset vector
	rom[0x7FFC] = 0x00;
	rom[0x7FFD] = 0x80;
		
	loadRAM(ram, "C:/Users/ajvp/Desktop/random_bytes_dump");

	CPU cpu(&ram);

	for (byte romByte : rom) {

	}

	cpu.displayRegisters();
	cpu.displayBuses();

	displayRAMPage(ram, 0x00);
	displayRAMPage(ram, 0x07);

	return 0;
}