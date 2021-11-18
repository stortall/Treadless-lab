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
                transmitter.Set
            }
        }
    }




   return 0; 
}