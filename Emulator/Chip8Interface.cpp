#include "Chip8Interface.h"
#include "ssd1306.h"
extern "C" {
#include "keypad.h"

}
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
	char key = keypad_read();
     switch(key) {
        case '1':
            keys[1] = true;
            break;
        case '2':
            keys[2] = true;
            break;
        case '3':
            keys[3] = true;
            break;
        case '4':
            keys[4] = true;
            break;
        case '5':
            keys[5] = true;
            break;
        case '6':
            keys[6] = true;
            break;
        case '7':
            keys[7] = true;
            break;
        case '8':
            keys[8] = true;
            break;
        case '9':
            keys[9] = true;
            break;
        case '0':
            keys[0] = true;
            break;
        case '*':
            keys[0xA] = true;
            break;
        case '#':
            keys[0xB] = true;
            break;
        case 'A':
            keys[0xC] = true;
            break;
        case 'B':
            keys[0xD] = true;
            break;
        case 'C':
            keys[0xE] = true;
            break;
        case 'D':
            keys[0xF] = true;
            break;
     }
 return true;
}

void Chip8Interface::beep() {}
