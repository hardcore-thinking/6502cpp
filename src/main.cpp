#include <iostream>
#include <vector>
#include <fstream>

#include "cpu.hpp"

bool LoadRAM(std::vector<Byte>& ram, std::string filepath) {
	std::ifstream ram_load(filepath, std::ios::in | std::ios::binary | std::ios::ate);

	if (ram_load.is_open()) {
		const std::streampos fileSize = ram_load.tellg();
		ram_load.seekg(0, std::ios::beg);

		ram_load.read(reinterpret_cast<char*>(ram.data()), static_cast<std::streamsize>(MAX_RAM_SIZE));
		
		return true;
	}

	else {
		return false;
	}
}

bool LoadROM(std::vector<Byte>& rom, std::string filepath) {
	std::ifstream rom_load(filepath, std::ios::in | std::ios::binary | std::ios::ate);

	if (rom_load.is_open()) {
		const std::streampos fileSize = rom_load.tellg();
		rom_load.seekg(0, std::ios::beg);

		//rom_load.seekg(0x8000);

		rom_load.read(reinterpret_cast<char*>(rom.data()), static_cast<std::streamsize>(MAX_ROM_SIZE));

		return true;
	}

	else {
		return false;
	}
}

int main(int argc, char* argv[]) {
	std::vector<Byte> ram(MAX_RAM_SIZE, (Byte) 0x00);
	
	std::vector<Byte> rom(MAX_ROM_SIZE, (Byte) 0x00);

	//loadRAM(ram, "C:/Users/ajvp/Desktop/Misc/random_bytes_dump");
	//loadROM(rom, "C:/Users/ajvp/Desktop/Misc/rom1");
	//loadROM(rom, "C:/Users/Alexy/Desktop/Misc/rom1");
	LoadROM(rom, "C:/Users/ajvp/Desktop/Misc files/a.out");
	
	// loadROM(rom, "C:/Users/ajvp/Desktop/Misc/smb1.bin");

	CPU cpu(&ram, (Word) 0x0000, (Word) MAX_RAM_SIZE, &rom, (Word) 0x8000, (Word) MAX_ROM_SIZE);

	cpu.DisplayROM(true);
	std::cout << std::endl;

	cpu.Run(false);

	return 0;
}