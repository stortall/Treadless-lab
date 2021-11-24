#include "ncurses.h"
#include <iostream>
#include "wh.hpp"
#include "chrono"

int main(){
    WriteHandler wh;
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
        if (in == 'p') {
           wh.SetGearSelectorState('P');
        }
      //   if (in == 'r') {
      //      wh.SetGearSelectorState('R');
      //   }
        if (in == 'n') {
           wh.SetGearSelectorState('N');
        }
        if (in == 'd') {
           wh.SetGearSelectorState('D');
        }
        while (getch() != ERR) {}
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }


}