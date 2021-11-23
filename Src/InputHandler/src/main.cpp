#include <iostream>
#include "ncurses.h"





int main()
{
    CanTransmitter transmitter;
    initscr(); //initialises the screen sets up memory and clears the screen

    //endwin(); deallocates memory and ends ncurses
    //refresh(); refreshes the screen to match whats is in memory
    //getch(); waits for user input, returns int value of that key
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