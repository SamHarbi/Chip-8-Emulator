#include "cpu.h"

CPU::CPU(){
    pc = START_ADDRESS;

	for (unsigned int i = 0; i < 80; ++i)
	{
		memory[FONT_START_ADDRESS + i] = font[i];
	}

    srand(time(0));

    loadROM("test/roms/IBM_Logo.ch8");

    cycle();

}

unsigned char CPU::randomVal() {
    return static_cast<unsigned char>(rand()); 
}

void CPU::loadROM(std::string filename) {
    auto filename_ptr = filename.c_str();
    std::ifstream file(filename_ptr, std::ios::binary | std::ios::ate);

    if(file.is_open()) {
		std::cout<<"Opened file"<<std::endl;
		std::streampos size = file.tellg();
		char* buffer = new char[size];

		file.seekg(0, std::ios::beg);
		file.read(buffer, size);
		file.close();

		for (long i = 0; i < size; ++i)
		{
			memory[START_ADDRESS + i] = buffer[i];
		}

		delete[] buffer;

    }

}

void CPU::cycle() {
	last_clock = std::chrono::steady_clock::now();
	opcode = (memory[pc] << 8u) | memory[pc];
	pc += 2;
	if (opcode == 0x00) {
		std::cout << "00" << std::endl;
	}
	if (opcode == 0xe0) {
		std::cout << "e0" << std::endl;
	}

}