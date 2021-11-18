#include "ncurses.h"
#include <iostream>
#include "wh.hpp"
#include "chrono"

int main(){
    WriteHandler wh = WriteHandler();
    initscr();
    cbreak();
    noecho();
    // keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    while (true) {
        char in;
        while ((in = getch()) == ERR) {}
        if (in >= '0' && in <= '9') {
            wh.SetThrottle(in-'0');
        }
        if (in == 'b') {
           wh.ToggleBreak();
        }
        while (getch() != ERR) {}
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }


}