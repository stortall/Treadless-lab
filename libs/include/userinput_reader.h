
#ifndef USERINPUT_READER_H
#define USERINPUT_READER_H

#include "wh.hpp"
#include <ncurses.h>
#include<iostream>
#include <cstring>
#include <stdlib.h>
#include "chrono"
#include "socketcan_cpp.h"
#include "vCAN_Writer.hpp"



WriteHandler wh;

class InputReader{
public:
    char input;
public:
    InputReader(){
        initscr();
        cbreak();
        noecho();
        // keypad(stdscr, TRUE);
        scrollok(stdscr, TRUE);
        nodelay(stdscr, TRUE);

    }

    void readInput(){
        char in;
    while ((in = getch()) == ERR) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));}
    if (in >= '0' && in <= '9') {
      wh.SetThrottle(in - '0');
    }
    if (in == 'b') {
      wh.ToggleBreak();
    }
    if (in == 'p') {
      wh.SetGearSelectorState('P');
    }
    if (in == 'n') {
      wh.SetGearSelectorState('N');
    }
    if (in == 'd') {
      wh.SetGearSelectorState('D');
    }
    if (in == 'h') {
      wh.ToggleHazard();
    }
    if (in == 'o') {
      wh.ToggleOilCheck();
    }
    if (in == 'a') {
      wh.ToggleABS();
    }
    if (in == 'l') {
      wh.ToggleHighBeam();
    }
    if (in == 'z') {
      wh.ToggleSeatBelt();
    }
    if (in == 'c') {
      wh.ToggleEngineCheck();
    }
    if (in == 'y') {
      wh.ToggleLeftBlinker();
    }
    if (in == 'u') {
      wh.ToggleRightBlinker();
    }
    if (in == 'x') {
      wh.ToggleDoorsOpen();
    }
    if (in == 'q') {
      wh.ToggleBattery();
    }
    while (getch() != ERR) {
    }

    }
};



#endif //USERINPUT_READER_H