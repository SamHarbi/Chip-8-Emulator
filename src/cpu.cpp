#include "cpu.h"

CPU::CPU(){
    pc = START_ADDRESS;

	for (unsigned int i = 0; i < 80; ++i) {
		memory[FONT_START_ADDRESS + i] = font[i];
	}

    srand(time(0));

    loadROM("test/roms/3-corax+.ch8");
	//loadROM("test/roms/octojam1title.ch8");
}

unsigned char CPU::pseudoRandomVal() {
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

		for (long i = 0; i < size; ++i) {
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

	if (opcode >> 12u == 0x0) {
		std::cout << "0x0 | Series Instructions" << std::endl;
		instruct_0(opcode);
	}
	else if (opcode >> 12u == 0x1) {
		std::cout << "1NNN (jump)" << std::endl;
		instruct_1NNN(opcode);
	}
	else if (opcode >> 12u == 0x2) {
		std::cout << "2NNN (jump)" << std::endl;
		instruct_2NNN(opcode);
	}
	else if (opcode >> 12u == 0x3) {
		std::cout << "3XNN (Skip conditionally)" << std::endl;
		instruct_3XNN(opcode);
	}
	else if (opcode >> 12u == 0x4) {
		std::cout << "4XNN (Skip conditionally)" << std::endl;
		instruct_4XNN(opcode);
	}
	else if (opcode >> 12u == 0x4) {
		std::cout << "5XY0 (Skip conditionally)" << std::endl;
		instruct_5XY0(opcode);
	}
	else if (opcode >> 12u == 0x4) {
		std::cout << "9XY0 (Skip conditionally)" << std::endl;
		instruct_9XY0(opcode);
	}
	else if (opcode >> 12u == 0x6) {
		std::cout << "6XNN (set register VX)" << std::endl;
		instruct_6XNN(opcode);
	}
	else if (opcode >> 12u == 0x7) {
		std::cout << "7XNN (add value to register VX)" << std::endl;
		instruct_7XNN(opcode);
	}
	else if (opcode >> 12u == 0x8) {
		std::cout << "0x8 | Series Instructions" << std::endl;
		instruct_8(opcode);
	}
	else if (opcode >> 12u == 0xA) {
		std::cout << "ANNN (set index register I)" << std::endl;
		instruct_ANNN(opcode);
	}
	else if (opcode >> 12u == 0xA) {
		std::cout << "CXNN (random)" << std::endl;
		instruct_CXNN(opcode);
	}
	else if (opcode >> 12u == 0xD) {
		std::cout << "DXYN (display/draw)" << std::endl;
		instruct_DXYN(opcode);
	}
	else if (opcode >> 12u == 0xF) {
		std::cout << "0xF | Series Instructions" << std::endl;
		instruct_F(opcode);
	}
	else {
		printf("Unknown opcode: %d \n", opcode);
	}
	return std::chrono::steady_clock::now();
}

void CPU::instruct_0(uint16_t opcode) {
	uint8_t byte = opcode & 0x00FF;
	if (byte == 0xe0) {
		std::cout << "00E0 (clear screen)" << std::endl;
		instruct_00E0();
	} 
	else if (byte == 0xEE) {
		std::cout << "00EE (Subroutine)" << std::endl;
		instruct_00EE(opcode);
	}
}

void CPU::instruct_00E0() {
    std::fill(std::begin(screen), std::end(screen), 0);
}

void CPU::instruct_00EE(uint16_t opcode) {
	if(!stack.empty()) {
		pc = stack.top();
		stack.pop();
	}
}

void CPU::instruct_1NNN(uint16_t opcode) {
	pc = opcode & 0x0FFFu;
}

void CPU::instruct_2NNN(uint16_t opcode) {
	stack.push(pc);
	pc = opcode & 0x0FFFu;
}

void CPU::instruct_3XNN(uint16_t opcode) {
	uint8_t reg = ((opcode) >> 8u) & 0x0Fu;
	uint8_t val = opcode & 0x00FFu;

	if(registers[reg] == val) {
		pc+=2;
	}
}

void CPU::instruct_4XNN(uint16_t opcode) {
	uint8_t reg = ((opcode) >> 8u) & 0x0Fu;
	uint8_t val = opcode & 0x00FFu;

	if(registers[reg] != val) {
		pc+=2;
	}
}

void CPU::instruct_5XY0(uint16_t opcode) {
	uint8_t regx = (opcode >> 8u) & 0x0Fu;
	uint8_t regy = (opcode >> 4u) & 0x00Fu;

	if(registers[regx] == registers[regy]) {
		pc+=2;
	}
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

void CPU::instruct_8(uint16_t opcode) {
	uint8_t lastNibble = opcode & 0x000Fu;
	if (lastNibble == 0) {
		std::cout << "0x8 | 0 Set" << std::endl;
		instruct_8XY0(opcode);
	}
	else if (lastNibble == 1) {
		std::cout << "0x8 | 1 Binary OR" << std::endl;
		instruct_8XY1(opcode);
	}
	else if (lastNibble == 2) {
		std::cout << "0x8 | 2 Binary AND" << std::endl;
		instruct_8XY2(opcode);
	}
	else if (lastNibble == 3) {
		std::cout << "0x8 | 3 Logical XOR" << std::endl;
		instruct_8XY3(opcode);
	}
	else if (lastNibble == 4) {
		std::cout << "0x8 | 4 Add" << std::endl;
		instruct_8XY4(opcode);
	}
	else if (lastNibble == 5) {
		std::cout << "0x8 | 5 Subtract VX" << std::endl;
		instruct_8XY5(opcode);
	}
	else if (lastNibble == 6) {
		std::cout << "0x8 | 6 Shift" << std::endl;
		instruct_8XY6(opcode);
	}
	else if (lastNibble == 7) {
		std::cout << "0x8 | 7 Subtract VY" << std::endl;
		instruct_8XY7(opcode);
	}
	else if (lastNibble == 0xE) {
		std::cout << "0x8 | 7 Subtract VY" << std::endl;
		instruct_8XYE(opcode);
	}
}

void CPU::instruct_8XY0(uint16_t opcode) {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;

	registers[vx] = registers[vy];
}

void CPU::instruct_8XY1(uint16_t opcode) {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;

	registers[vx] = registers[vx] | registers[vy];
}

void CPU::instruct_8XY2(uint16_t opcode) {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;

	registers[vx] = registers[vx] & registers[vy];
}

void CPU::instruct_8XY3(uint16_t opcode) {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;

	registers[vx] = registers[vx] ^ registers[vy];
}

void CPU::instruct_8XY4(uint16_t opcode) {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;

	if( registers[vx] > (255 - registers[vy]) ) {
		registers[15] = 1;
	} else {
		registers[15] = 0;
	}

	registers[vx] = registers[vx] + registers[vy];
}

void CPU::instruct_8XY5(uint16_t opcode) {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;

	if( registers[vx] > registers[vy] ) {
		registers[15] = 1;
	} else {
		registers[15] = 0;
	}

	registers[vx] -= registers[vy];
}

void CPU::instruct_8XY6(uint16_t opcode) {
	// Need to be able to configure for older different behaviour
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t valueShifted = registers[vx] & 1;

	registers[vx] = registers[vx] >> 1u;
}

void CPU::instruct_8XY7(uint16_t opcode) {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;

	if( registers[vy] > registers[vx] ) {
		registers[15] = 1;
	} else {
		registers[15] = 0;
	}

	registers[vx] = registers[vy] - registers[vx];
}

void CPU::instruct_8XYE(uint16_t opcode) {
	// Need to be able to configure for older different behaviour
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t valueShifted = registers[vx] & 1;

	registers[vx] = registers[vx] << 1u;
}

void CPU::instruct_9XY0(uint16_t opcode) {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;

	if(registers[vx] != registers[vy]) {
		pc+=2;
	}
}

void CPU::instruct_ANNN(uint16_t opcode) {
	index = opcode & 0x0FFF;
}

void CPU::instruct_BNNN(uint16_t opcode) {
	// TODO, two common differing behaviors
}

void CPU::instruct_CXNN(uint16_t opcode) {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t byte = opcode & 0x00FFu;

	registers[vx] = pseudoRandomVal() & byte;
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

void CPU::instruct_EX9E(uint16_t opcode) {

}

void CPU::instruct_EXA1(uint16_t opcode) {
	
}

void CPU::instruct_F(uint16_t opcode) {
	uint8_t lastNibbles = opcode & 0x00FFu;
	if (lastNibbles == 07) {
		std::cout << "0xF | 07 Timer" << std::endl;
		instruct_FX07(opcode);
	}
	else if (lastNibbles == 15) {
		std::cout << "0xF | 15 Timer" << std::endl;
		instruct_FX15(opcode);
	}
	else if (lastNibbles == 18) {
		std::cout << "0xF | 18 Timer" << std::endl;
		instruct_FX18(opcode);
	}
	else if (lastNibbles == 0x1E) {
		std::cout << "0xF | 1E Timer" << std::endl;
		instruct_FX1E(opcode);
	}
	else if (lastNibbles == 0x29) {
		std::cout << "0xF | 29 Font character" << std::endl;
		instruct_FX29(opcode);
	}
	else if (lastNibbles == 0x55) {
		std::cout << "0xF | 55 Store Memory" << std::endl;
		instruct_FX55(opcode);
	}
	else if (lastNibbles == 0x65) {
		std::cout << "0xF | 65 Load Memory" << std::endl;
		instruct_FX65(opcode);
	}
}

void CPU::instruct_FX07(uint16_t opcode) {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	registers[vx] = delayTimer;
}

void CPU::instruct_FX15(uint16_t opcode) {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	delayTimer = registers[vx];
}

void CPU::instruct_FX18(uint16_t opcode) {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	soundTimer = registers[vx];
}

void CPU::instruct_FX1E(uint16_t opcode) {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;

	// Not confirmed behaviour, need to be able to config this!
	if( registers[vx] > (255 - index) ) {
		registers[15] = 1;
	} else {
		registers[15] = 0;
	}

	index += registers[vx];
}

void CPU::instruct_FX29(uint16_t opcode) {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	index = FONT_START_ADDRESS + (5 * registers[vx]);
}

// -- These need to have configuration to choose between i and i++ behaviour
void CPU::instruct_FX55(uint16_t opcode) {
	uint8_t max = (opcode & 0x0F00u) >> 8u;
	for(int i=0; i<=max; i++) {
		memory[index+i] = registers[i];
	}
}

void CPU::instruct_FX65(uint16_t opcode) {
	uint8_t max = (opcode & 0x0F00u) >> 8u;
	for(int i=0; i<=max; i++) {
		registers[i] = memory[index+i];
	}
}
// -- 