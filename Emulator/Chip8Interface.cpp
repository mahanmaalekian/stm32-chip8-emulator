#include "Chip8Interface.h"

Chip8Interface::Chip8Interface() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(DISPLAY_WIDTH*10, DISPLAY_HEIGHT*10, 0, &window, &renderer);
    SDL_RenderSetLogicalSize(renderer, 64, 32);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Chip8Interface::draw_display() {
    for (int y{0}; y < DISPLAY_HEIGHT; ++y){
        for (int x{0}; x < DISPLAY_WIDTH; ++x)
        {
            bool pixel = display_arr[y][x];
            if (pixel) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
    SDL_RenderPresent(renderer);
}

bool Chip8Interface::process_input() {
    bool quit{false};
    SDL_Event event{};

    while (SDL_PollEvent(&event))  {
        if (event.type == SDL_KEYDOWN) {
            switch(event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                case SDLK_x:
                    keys[0] = true;
                    break;
                case SDLK_1:
                    keys[1] = true;
                    break;
                case SDLK_2:
                    keys[2] = true;
                    break;
                case SDLK_3:
                    keys[3] = true;
                    break;
                case SDLK_q:
                    keys[4] = true;
                    break;
                case SDLK_w:
                    keys[5] = true;
                    break;
                case SDLK_e:
                    keys[6] = true;
                    break;
                case SDLK_a:
                    keys[7] = true;
                    break;
                case SDLK_s:
                    keys[8] = true;
                    break;
                case SDLK_d:
                    keys[9] = true;
                    break;
                case SDLK_z:
                    keys[0xA] = true;
                    break;
                case SDLK_c:
                    keys[0xB] = true;
                    break;
                case SDLK_4:
                    keys[0xC] = true;
                    break;
                case SDLK_r:
                    keys[0xD] = true;
                    break;
                case SDLK_f:
                    keys[0xE] = true;
                    break;
                case SDLK_v:
                    keys[0xF] = true;
                    break;
            }
        }
        else if (event.type == SDL_KEYUP) {
            switch(event.key.keysym.sym) {
                case SDLK_x:
                    keys[0] = false;
                    break;
                case SDLK_1:
                    keys[1] = false;
                    break;
                case SDLK_2:
                    keys[2] = false;
                    break;
                case SDLK_3:
                    keys[3] = false;
                    break;
                case SDLK_q:
                    keys[4] = false;
                    break;
                case SDLK_w:
                    keys[5] = false;
                    break;
                case SDLK_e:
                    keys[6] = false;
                    break;
                case SDLK_a:
                    keys[7] = false;
                    break;
                case SDLK_s:
                    keys[8] = false;
                    break;
                case SDLK_d:
                    keys[9] = false;
                    break;
                case SDLK_z:
                    keys[0xA] = false;
                    break;
                case SDLK_c:
                    keys[0xB] = false;
                    break;
                case SDLK_4:
                    keys[0xC] = false;
                    break;
                case SDLK_r:
                    keys[0xD] = false;
                    break;
                case SDLK_f:
                    keys[0xE] = false;
                    break;
                case SDLK_v:
                    keys[0xF] = false;
                    break;
            }
        }
    }
    return quit;
}

void Chip8Interface::beep() {}
