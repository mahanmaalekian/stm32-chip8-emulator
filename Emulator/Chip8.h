#ifndef CHIP8_H
#define CHIP8_H
#include <cstdint>
#include "Chip8Interface.h"

class Chip8 {
    public:
        static const int MEMORY_SIZE {4096};
        static const int REGISTER_COUNT {16};
        static const int FONT_START_ADDR{0x50};
        static const int FONT_END_ADDR{0x9F};
        using instruction_parts = struct {
            uint8_t first_nibble;
            uint8_t x;
            uint8_t y;
            uint8_t n;
            uint8_t nn;
            uint16_t nnn;
        };
        Chip8Interface chip8_interface;
        uint8_t memory[4096];
        uint16_t pc{0x200};
        uint16_t index_register{0};
        uint16_t stack[16]{};
        uint8_t sp{0};
        uint8_t delay_timer{0};
        uint8_t sound_timer{0};
        uint8_t variable_registers[16]{};
        uint16_t curr_instruction{0};
        uint8_t fontset[80] {
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
        float cycle_delay {2};
        float timer_delay {2};


        Chip8();
        void fetch();
        void decode();
        void execute0(instruction_parts instr_parts);
        void execute1(instruction_parts instr_parts);
        void execute2(instruction_parts instr_parts);
        void execute3(instruction_parts instr_parts);
        void execute4(instruction_parts instr_parts);
        void execute5(instruction_parts instr_parts);
        void execute6(instruction_parts instr_parts);
        void execute7(instruction_parts instr_parts);
        void execute8(instruction_parts instr_parts);
        void execute9(instruction_parts instr_parts);
        void executeA(instruction_parts instr_parts);
        void executeB(instruction_parts instr_parts);
        void executeC(instruction_parts instr_parts);
        void executeD(instruction_parts instr_parts);
        void executeE(instruction_parts instr_parts);
        void executeF(instruction_parts instr_parts);
        void display();
    private:
        void print_debug() const;
        void print_video_buffer();

};
#endif
