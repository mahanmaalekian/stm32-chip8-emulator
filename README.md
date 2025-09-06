# CHIP-8 Emulator on a STM32 Board

This project is an extension of a previous [project](https://github.com/mahanmaalekian/chip8-emulator) where I implemented a CHIP-8 emulator, but now modified it to run on an STM32 microcontroller and integrated a keypad and display to transform it into a portable retro gaming console that you can take anywhere and play any CHIP-8 game on!
It includes all the peripherals needed to play CHIP-8 games on the STM32 board.

### What is a CHIP-8 Emulator?
Although this project is called a CHIP-8 emulator, the CHIP-8 is not actually a piece of hardware, but rather an interpreted programming language, virtual machine, and instruction set architecture created by RCA engineer Joe Weisbecker as a way to make programs and games for his computer. Therefore, it might be more accurate to call this project a *CHIP-8 interpreter*.

For information on the specifications and instructions of the CHIP-8, see the documentation [here](http://devernay.free.fr/hacks/CHIP-8/C8TECH10.HTM#1.0).

### Hardware Used:
- STM32F4 Microcontroller
- 4x4 Membrane Matrix Keypad
- SSD1306 OLED display

Add your games to the `roms.h` header file. You can convert your games from binary format to a C++ array using the xxd command: `xxd -i game.ch8`

### How to run it
- Download the STM32CubeIDE and open this project in the IDE
- In the constructor of the CHIP-8 class (`Emulator/CHIP-8`), replace the rom array with the rom of your choice from the `roms.h` file
- Connect the board to the computer and run it as a STM32 C/C++ application to flash it and you can play the game. Once you have flashed it, you can play the game you want from anywhere by simpling connecting a power source to the microcontroller (battery or powerbank for example)

### Diagram of the setup
![alt text](image.png)

### Real life setup
<img width="400" height="1589" alt="image" src="https://github.com/user-attachments/assets/3ec26448-ef2f-4402-aec5-7b99870d7734" />


### Game example: Tetris
<img width="400" height="869" alt="image" src="https://github.com/user-attachments/assets/2bfc3fc0-002e-4d63-8144-28fd0bcb04e4" />
