#include "cpu.h"

CPU::CPU(){
    pc = START_ADDRESS;

	for (unsigned int i = 0; i < 80; ++i)
	{
		memory[FONT_START_ADDRESS + i] = font[i];
	}

    srand(time(0));

    loadROM("test/roms/IBM_Logo.ch8");
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

uint32_t* CPU::getDisplayData() {
	return screen;
}

std::chrono::time_point<std::chrono::steady_clock> CPU::cycle() {
	opcode = (memory[pc] << 8u) | memory[pc + 1];
	pc += 2;
	//std::cout << std::format("{:x} {:#x} {}\n", opcode, (opcode) >> 12u, opcode);
	if (opcode >> 12u == 0x00) {
		//std::cout << "Ignored opcode 00" << std::endl;
	}
	else if (opcode >> 12u == 0xe0) {
		std::cout << "00E0 (clear screen)" << std::endl;
		instruct_00E0();
	}
	else if (opcode >> 12u == 0x1) {
		std::cout << "1NNN (jump)" << std::endl;
		instruct_1NNN(opcode);
	}
	else if (opcode >> 12u == 0x6) {
		std::cout << "6XNN (set register VX)" << std::endl;
		instruct_6XNN(opcode);
	}
	else if (opcode >> 12u == 0x7) {
		std::cout << "7XNN (add value to register VX)" << std::endl;
		instruct_7XNN(opcode);
	}
	else if (opcode >> 12u == 0xA) {
		std::cout << "ANNN (set index register I)" << std::endl;
		instruct_ANNN(opcode);
	}
	else if (opcode >> 12u == 0xD) {
		std::cout << "DXYN (display/draw)" << std::endl;
		instruct_DXYN(opcode);
	}
	else {
		//printf("Unknown opcode: %d", opcode);
	}
	return std::chrono::steady_clock::now();
}

void CPU::instruct_00E0() {
    std::fill(std::begin(screen), std::end(screen), 0);
}

void CPU::instruct_1NNN(uint16_t opcode) {
	pc = opcode & 0x0FFFu;
}

void CPU::instruct_6XNN(uint16_t opcode) {
	uint8_t reg = ((opcode) >> 8u) & 0x0Fu;
	uint8_t value = opcode & 0x00FFu;

	registers[reg] = value;
}

void CPU::instruct_7XNN(uint16_t opcode) {
	uint8_t reg = ((opcode) >> 8u) & 0x0Fu;
	uint8_t value = opcode & 0x00FFu;

	registers[reg] += value;
}

void CPU::instruct_ANNN(uint16_t opcode) {
	index = opcode & 0x0FFF;
}

void CPU::instruct_DXYN(uint16_t opcode) {
	uint8_t x = registers[(opcode & 0x0F00u) >> 8u] & 63;
	uint8_t y = registers[(opcode & 0x00F0u) >> 4u] & 31;
	uint8_t rows = opcode & 0x000Fu;

	registers[0xF] = 0;

	for(uint8_t row=0; row<rows; row++ ) {
		uint8_t spriteVal = memory[index + row];

		for(uint8_t col = 0; col < 8; col++) {
			uint8_t pixel = spriteVal & ((0x80u >> col));
			uint32_t* screenPixel = &screen[(y + row) * 64 + (x + col)];

			if (pixel) {
				if (*screenPixel == 0xFFFFFFFF) registers[0xF] = 1;
				*screenPixel ^= 0xFFFFFFFF; // XOR with sprite pixel
			}
		}
	}
}