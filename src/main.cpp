#include <iostream>
#include <vector>
#include <fstream>

#include "cpu.hpp"

void loadRAM(std::vector<byte>& ram, std::string filepath) {
	std::ifstream ram_load(filepath, std::ios::in | std::ios::binary | std::ios::ate);

	if (ram_load.is_open()) {
		const std::streampos fileSize = ram_load.tellg();
		ram_load.seekg(0, std::ios::beg);

		ram_load.read(reinterpret_cast<char*>(ram.data()), static_cast<std::streamsize>(MAX_RAM_SIZE));
	}
}

void loadROM(std::vector<byte>& rom, std::string filepath) {
	std::ifstream rom_load(filepath, std::ios::in | std::ios::binary | std::ios::ate);

	if (rom_load.is_open()) {
		const std::streampos fileSize = rom_load.tellg();
		rom_load.seekg(0, std::ios::beg);

		//rom_load.seekg(0x8000);

		rom_load.read(reinterpret_cast<char*>(rom.data()), static_cast<std::streamsize>(MAX_ROM_SIZE));
	}
}

int main(int argc, char* argv[]) {
	std::vector<byte> ram(MAX_RAM_SIZE, (byte) 0x00);
	
	std::vector<byte> rom(MAX_ROM_SIZE, (byte) 0x00);

	loadRAM(ram, "C:/Users/ajvp/Desktop/Misc/random_bytes_dump");
	loadROM(rom, "C:/Users/ajvp/Desktop/Misc/rom1");
	//loadROM(rom, "C:/Users/ajvp/Desktop/Misc/smb1.bin");

	CPU cpu(&ram, (word) 0x0000, (word) MAX_RAM_SIZE, &rom, (word) 0x8000, (word) MAX_ROM_SIZE);

	cpu.displayROM(true);
	std::cout << std::endl;

	cpu.run(true);

	return 0;
}