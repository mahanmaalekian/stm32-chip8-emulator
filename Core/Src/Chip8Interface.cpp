#include "Chip8Interface.h"
#include "ssd1306.h"
#include <cstdlib>
Chip8Interface::Chip8Interface() {
}

void Chip8Interface::draw_display() {
    for (int y{0}; y < DISPLAY_HEIGHT; ++y){
        for (int x{0}; x < DISPLAY_WIDTH; ++x)
        {
            bool pixel = display_arr[y][x];
            if (pixel) {
            	ssd1306_DrawPixel(x, y, White);
            }
            else {
            	ssd1306_DrawPixel(x, y, White);
            }
        }
    }
    ssd1306_UpdateScreen();
}

bool Chip8Interface::process_input() {
 return true;
}

void Chip8Interface::beep() {}
