#include <iostream>
#include "ncurses.h"





int main()
{
    CanTransmitter transmitter;
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    while(true)
    {
        char in;
        while((in = getch()) == ERR){
            if(in >= '0' && in <= '9')
            {
                transmitter.SetThrottle(in-'0');

            }
            if (in == 'b') 
            {
                transmitter.ToggleBreak();
            }
            while (getch() != ERR) {}
            napms(100);
        }
    }




   return 0; 
}