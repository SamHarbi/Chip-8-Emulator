#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <stack>

class CPU {
    public:
        uint8_t registers[16]{};
        uint8_t memory[4096]{};
        uint16_t index{};
        uint16_t pc{};
        std::stack<uint16_t> stack; // Max length should be 16
        uint8_t delayTimer{};
        uint8_t soundTimer{};
        uint8_t keypad[16]{};
        uint32_t screen[64 * 32]{};
        uint16_t opcode;

        const unsigned int START_ADDRESS = 0x200;
        const unsigned int FONT_START_ADDRESS = 0x50;

        uint8_t font[80] = {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };

        CPU();
        void loadROM(std::string filename);
        unsigned char pseudoRandomVal();
        std::chrono::time_point<std::chrono::steady_clock> cycle();
        uint32_t* getDisplayData();

        void instruct_00E0();
        void instruct_00EE(uint16_t opcode);
        void instruct_1NNN(uint16_t opcode);
        void instruct_2NNN(uint16_t opcode);
        void instruct_6XNN(uint16_t opcode);
        void instruct_7XNN(uint16_t opcode);
        void instruct_ANNN(uint16_t opcode);
        void instruct_DXYN(uint16_t opcode);
        void instruct_3XNN(uint16_t opcode);
        void instruct_4XNN(uint16_t opcode);
        void instruct_5XY0(uint16_t opcode);
        void instruct_9XY0(uint16_t opcode);

        void instruct_8(uint16_t opcode);
        void instruct_8XY0(uint16_t opcode);
        void instruct_8XY1(uint16_t opcode);
        void instruct_8XY2(uint16_t opcode);
        void instruct_8XY3(uint16_t opcode);
        void instruct_8XY4(uint16_t opcode);
        void instruct_8XY6(uint16_t opcode);

        void instruct_BNNN(uint16_t opcode);
        void instruct_CXNN(uint16_t opcode);

        void instruct_F(uint16_t opcode);
        void instruct_FX07(uint16_t opcode);
        void instruct_FX15(uint16_t opcode);
        void instruct_FX18(uint16_t opcode);
        void instruct_FX1E(uint16_t opcode);

};