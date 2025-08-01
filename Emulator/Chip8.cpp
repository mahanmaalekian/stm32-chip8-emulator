#include "Chip8.h"
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>

Chip8::Chip8() {
  for (int i{FONT_START_ADDR}; i <= FONT_END_ADDR; i++) {
    memory[i] = fontset[i - FONT_START_ADDR];
  }
}

int Chip8::run(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Usage: emu <rom_file>\n";
    return -1;
  }
  if (0 != load_rom(argv[1])) {
    std::cout << "Cannot load rom file\n";
    return -1;
  }
  bool quit = false;
  auto start_time_cycle = std::chrono::high_resolution_clock::now();

  auto start_time_timer = std::chrono::high_resolution_clock::now();

  while (!quit) {
    quit = chip8_interface.process_input();
    auto current_time_cycle = std::chrono::high_resolution_clock::now();
    float elapsed_cycle =
        std::chrono::duration<float, std::chrono::milliseconds::period>(
            current_time_cycle - start_time_cycle)
            .count();
    if (elapsed_cycle > cycle_delay) {
      fetch();
      decode();
      start_time_cycle = current_time_cycle;
    }

    auto current_time_timer = std::chrono::high_resolution_clock::now();
    float elapsed_timer =
        std::chrono::duration<float, std::chrono::milliseconds::period>(
            current_time_timer - start_time_timer)
            .count();

    if (elapsed_timer > timer_delay) {
      chip8_interface.draw_display();

      if (delay_timer > 0)
        delay_timer--;
      if (sound_timer > 0) {
        sound_timer--;
        chip8_interface.beep();
      }
      start_time_timer = current_time_timer;
    }
  }
  return 0;
}

int Chip8::load_rom(char *file_name) {
  std::ifstream file(file_name, std::ios::binary |
                                    std::ios::ate); // open at end to get size
  if (file.is_open()) {
    std::streamsize romSize = file.tellg();
    file.seekg(0, std::ios::beg);
    if (romSize > 4096 - 0x200) {
      return -1;
    }
    file.read(reinterpret_cast<char *>(memory + 0x200), romSize);
    file.close();
  } else {
    return -1;
  }
  return 0;
}

void Chip8::init() {}

void Chip8::fetch() {
  uint8_t hi = memory[pc];
  uint8_t lo = memory[pc + 1];
  curr_instruction = lo | (hi << 8);
  pc += 2;
}

void Chip8::decode() {
  instruction_parts instr_parts = {
      .first_nibble = static_cast<uint8_t>(curr_instruction >> 12),
      .x = static_cast<uint8_t>((curr_instruction >> 8) & 0xF),
      .y = static_cast<uint8_t>((curr_instruction >> 4) & 0xF),
      .n = static_cast<uint8_t>((curr_instruction) & 0xF),
      .nn = static_cast<uint8_t>(curr_instruction & 0xFF),
      .nnn = static_cast<uint16_t>(curr_instruction & 0xFFF)};
  switch (instr_parts.first_nibble) {
  case 0x0:
    execute0(instr_parts);
    break;
  case 0x1:
    execute1(instr_parts);
    break;
  case 0x2:
    execute2(instr_parts);
    break;
  case 0x3:
    execute3(instr_parts);
    break;
  case 0x4:
    execute4(instr_parts);
    break;
  case 0x5:
    execute5(instr_parts);
    break;
  case 0x6:
    execute6(instr_parts);
    break;
  case 0x7:
    execute7(instr_parts);
    break;
  case 0x8:
    execute8(instr_parts);
    break;
  case 0x9:
    execute9(instr_parts);
    break;
  case 0xA:
    executeA(instr_parts);
    break;
  case 0xB:
    executeB(instr_parts);
    break;
  case 0xC:
    executeC(instr_parts);
    break;
  case 0xD: {
    executeD(instr_parts);
    break;
  }
  case 0xE:
    executeE(instr_parts);
    break;
  case 0xF:
    executeF(instr_parts);
    break;
  }
}

void Chip8::execute0(instruction_parts instr_parts) {
  switch (instr_parts.n) {
  case 0x0:
    for (int i{0}; i < Chip8Interface::DISPLAY_HEIGHT; ++i) {
      for (int j{0}; j < Chip8Interface::DISPLAY_WIDTH; ++j) {
        chip8_interface.display_arr[i][j] = false;
      }
    }
    break;
  case 0xE:
    sp--;
    pc = stack[sp];
    break;
  default:
    NO_IMPL
    break;
  }
}

void Chip8::execute1(instruction_parts instr_parts) { pc = instr_parts.nnn; }

void Chip8::execute2(instruction_parts instr_parts) {
  stack[sp] = pc;
  sp++;
  pc = instr_parts.nnn;
}

void Chip8::execute3(instruction_parts instr_parts) {
  if (instr_parts.nn == variable_registers[instr_parts.x]) {
    pc += 2;
  }
}

void Chip8::execute4(instruction_parts instr_parts) {
  if (instr_parts.nn != variable_registers[instr_parts.x]) {
    pc += 2;
  }
}
void Chip8::execute5(instruction_parts instr_parts) {
  if (variable_registers[instr_parts.x] == variable_registers[instr_parts.y]) {
    pc += 2;
  }
}

void Chip8::execute6(instruction_parts instr_parts) {
  variable_registers[instr_parts.x] = instr_parts.nn;
}

void Chip8::execute7(instruction_parts instr_parts) {
  variable_registers[instr_parts.x] += instr_parts.nn;
}

void Chip8::execute8(instruction_parts instr_parts) {
  uint8_t Vx = variable_registers[instr_parts.x];
  uint8_t Vy = variable_registers[instr_parts.y];
  switch (instr_parts.n) {
  case 0x0:
    variable_registers[instr_parts.x] = Vy;
    break;
  case 0x1:
    variable_registers[instr_parts.x] = Vx | Vy;
    variable_registers[0xF] = 0;
    break;
  case 0x2:
    variable_registers[instr_parts.x] = Vx & Vy;
    variable_registers[0xF] = 0;
    break;
  case 0x3:
    variable_registers[instr_parts.x] = Vx ^ Vy;
    break;
  case 0x4:
    variable_registers[instr_parts.x] = (Vx + Vy) & 0xFFu;
    variable_registers[0xF] = ((Vx + Vy) > 255) ? 1 : 0;
    break;
  case 0x5:
    variable_registers[instr_parts.x] = (Vx - Vy);
    variable_registers[0xF] = (Vx >= Vy) ? 1 : 0;
    break;
  case 0x6:
    variable_registers[instr_parts.x] >>= 1;
    variable_registers[0xF] = Vx & 1;
    break;
  case 0x7:
    variable_registers[instr_parts.x] = Vy - Vx;
    variable_registers[0xF] = (Vx <= Vy) ? 1 : 0;
    break;
  case 0xE:
    variable_registers[instr_parts.x] <<= 1;
    variable_registers[0xF] = (Vx >> 7) & 1;
    break;
  default:
    break;
  }
}

void Chip8::execute9(instruction_parts instr_parts) {
  if (variable_registers[instr_parts.x] != variable_registers[instr_parts.y]) {
    pc += 2;
  }
}

void Chip8::executeA(instruction_parts instr_parts) {
  index_register = instr_parts.nnn;
}

void Chip8::executeB(instruction_parts instr_parts) {
  pc = instr_parts.nnn + variable_registers[0];
}

void Chip8::executeC(instruction_parts instr_parts) {
  uint8_t random = rand() % 256;
  random &= instr_parts.nn;
  variable_registers[instr_parts.x] = random;
}

void Chip8::executeD(instruction_parts instr_parts) {
  int x_coord = variable_registers[instr_parts.x];
  int y_coord = variable_registers[instr_parts.y];

  variable_registers[0xF] = 0;
  int n = instr_parts.n;

  for (int i{0}; i < n; ++i) {
    uint8_t sprite_byte = memory[index_register + i];
    for (int j{0}; j < 8; ++j) {
      uint8_t bit = (sprite_byte >> (7 - j)) & 1;
      if (1 == bit) {
        int px = (x_coord + j) % Chip8Interface::DISPLAY_WIDTH;
        int py = (y_coord + i) % Chip8Interface::DISPLAY_HEIGHT;
        bool pixel = chip8_interface.display_arr[py][px];
        if (pixel) {
          chip8_interface.display_arr[py][px] = false;
          variable_registers[0xF] = 1;
        } else {
          chip8_interface.display_arr[py][px] = true;
        }
      }
    }
  }
}

void Chip8::executeE(instruction_parts instr_parts) {
  for (int i = 0; i <= 0xF; i++) {
    std::cout << chip8_interface.keys[i] << " ";
  }
  std::cout << "\n";
  switch (instr_parts.nn) {
  case 0x9E:
    if (chip8_interface.keys[variable_registers[instr_parts.x]]) {
      std::cout << "IT IS PRESSED\n";
      pc += 2;
    }
    break;
  case 0xA1:
    if (!chip8_interface.keys[variable_registers[instr_parts.x]]) {
      pc += 2;
    }
    break;
  }
}

void Chip8::executeF(instruction_parts instr_parts) {
  switch (instr_parts.nn) {
  case 0x07:
    variable_registers[instr_parts.x] = delay_timer;
    break;
  case 0x0A: {
    bool is_pressed = false;
    for (int i{0}; i <= 0xF; ++i) {
      if (true == chip8_interface.keys[i]) {
        variable_registers[instr_parts.x] = i;
        // while (!chip8_interface.process_input() && true == chip8_interface.keys[i]);
        is_pressed = true;
        break;
      }
    }
    if (!is_pressed)
      pc -= 2;
    break;
  }
  case 0x15:
    delay_timer = variable_registers[instr_parts.x];
    break;
  case 0x18:
    sound_timer = variable_registers[instr_parts.x];
    break;
  case 0x29: {
    uint8_t character = variable_registers[instr_parts.x];
    index_register =
        FONT_START_ADDR + character * 5; // 5 for character row length
    break;
  }
  case 0x33: {
    uint8_t Vx = variable_registers[instr_parts.x];
    memory[index_register] = Vx / 100;
    Vx -= memory[index_register] * 100;
    memory[index_register + 1] = Vx / 10;
    memory[index_register + 2] = Vx % 10;
    break;
  }
  case 0x55:
    for (int i{0}; i <= instr_parts.x; ++i) {
      memory[index_register + i] = variable_registers[i];
    }
    break;
  case 0x65:
    for (int i{0}; i <= instr_parts.x; ++i) {
      variable_registers[i] = memory[index_register + i];
    }
    break;
  case 0x1E:
    index_register += variable_registers[instr_parts.x];
    break;
  }
}

void Chip8::print_video_buffer() {
  for (int y = 0; y < Chip8Interface::DISPLAY_HEIGHT; ++y) {
    for (int x = 0; x < Chip8Interface::DISPLAY_WIDTH; ++x) {
      uint32_t pixel = chip8_interface.display_arr[y][x];
      if (pixel == true) {
        std::cout << "#"; // white pixel
      } else {
        std::cout << " "; // black pixel
      }
    }
    std::cout << "\n";
  }
}

void Chip8::print_debug() const {
  std::cout << std::hex << std::uppercase;

  std::cout << "==== CHIP-8 DEBUG STATE ====\n";
  std::cout << "INSTR: 0x" << std::setw(4) << std::setfill('0')
            << curr_instruction << "\n";

  for (int i = 0; i < 16; ++i) {
    std::cout << "V" << std::hex << i << ": " << std::setw(2)
              << std::setfill('0') << static_cast<int>(variable_registers[i])
              << "  ";
    if ((i + 1) % 4 == 0)
      std::cout << "\n";
  }

  std::cout << " I: 0x" << std::setw(4) << std::setfill('0') << index_register
            << "\n";
  std::cout << "PC: 0x" << std::setw(4) << std::setfill('0') << pc << "\n";
  std::cout << "============================\n";
}
// https://github.com/Timendus/chip8-test-suite?tab=readme-ov-file#chip-8-splash-screen
