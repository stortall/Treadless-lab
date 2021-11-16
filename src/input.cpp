#include "ncurses.h"
#include <iostream>
#include "socketcan_cpp.h"
#include "vCAN_Writer.hpp"
#include "wh.cpp"


int main(){
    WriterHandler wh = WriterHandler();
    initscr();
    cbreak();
    noecho();
    // keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    while (true) {
        char in;
        while ((in = getch()) == ERR) {}
        if (in == '1') {
            wh.SetThottle(1);
        }
        else if (in == '0') {
            wh.SetThottle(0);
        }
        if (in == 'b') {
            /* engine->SetThrottle(0);
            engine->ToggleBrake(); */
        }
        while (getch() != ERR) {}
        napms(100);
    }


}