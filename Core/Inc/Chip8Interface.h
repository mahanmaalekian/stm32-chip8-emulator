#ifndef DISPLAY_H
#define DISPLAY_H
#include <cstdint>
class Chip8Interface {
    public:
        const static uint8_t DISPLAY_WIDTH{64};
        const static uint8_t DISPLAY_HEIGHT{32};
        bool display_arr[DISPLAY_HEIGHT][DISPLAY_WIDTH]{false};
        bool keys[16]{false};

        Chip8Interface();
        void draw_display(); 
        bool process_input();
        void beep();
};


#endif
