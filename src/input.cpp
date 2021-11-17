#include "ncurses.h"
#include <iostream>
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
        if (in >= '0' && in <= '9') {
            wh.SetThrottle(in-'0');
        }
        if (in == 'b') {
           wh.ToggleBreak();
        }
        while (getch() != ERR) {}
        napms(100);
    }


}