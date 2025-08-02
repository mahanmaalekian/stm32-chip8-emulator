#include "Chip8Interface.h"
#include "ssd1306.h"
Chip8Interface::Chip8Interface() {
}

void Chip8Interface::draw_display() {
    for (int y{0}; y < DISPLAY_HEIGHT; ++y){
        for (int x{0}; x < DISPLAY_WIDTH; ++x)
        {
            bool pixel = display_arr[y][x];
            int x_double = 2 * x;
            int y_double = 2 * y;
            if (pixel) {
                ssd1306_DrawPixel(x_double, y_double, White);
                ssd1306_DrawPixel(x_double + 1, y_double, White);
                ssd1306_DrawPixel(x_double, y_double + 1, White);
                ssd1306_DrawPixel(x_double + 1, y_double + 1, White);
            }
            else {
                ssd1306_DrawPixel(x_double, y_double, Black);
                ssd1306_DrawPixel(x_double + 1, y_double, Black);
                ssd1306_DrawPixel(x_double, y_double + 1, Black);
                ssd1306_DrawPixel(x_double + 1, y_double + 1, Black);
            }
        }
    }
    ssd1306_UpdateScreen();
}

bool Chip8Interface::process_input() {
 return true;
}

void Chip8Interface::beep() {}
