
#ifndef USERINPUT_READER_H
#define USERINPUT_READER_H

#include <ncurses.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <chrono>
#include "socketcan.h"
#include "vCAN_Writer.hpp"
#include "write_handler.hpp"

WriteHandler write_handler;

class InputReader {
 public:
  char in;
  bool on;

 public:
  InputReader() {
    initscr();
    cbreak();
    noecho();
    // keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    on = true;
  }

  void readInput() {
    while ((in = getch()) == ERR) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    if (in >= '0' && in <= '9') {
      write_handler.SetThrottle(in - '0');
    }
    if (in == 'b') {
      write_handler.ToggleBreak();
    }
    if (in == 'p') {
      write_handler.SetGearSelectorState('P');
    }
    if (in == 'n') {
      write_handler.SetGearSelectorState('N');
    }
    if (in == 'd') {
      write_handler.SetGearSelectorState('D');
    }
    if (in == 'h') {
      write_handler.ToggleHazard();
    }
    if (in == 'o') {
      write_handler.ToggleOilCheck();
    }
    if (in == 'a') {
      write_handler.ToggleABS();
    }
    if (in == 'l') {
      write_handler.ToggleHighBeam();
    }
    if (in == 'z') {
      write_handler.ToggleSeatBelt();
    }
    if (in == 'c') {
      write_handler.ToggleEngineCheck();
    }
    if (in == 'y') {
      write_handler.ToggleLeftBlinker();
    }
    if (in == 'u') {
      write_handler.ToggleRightBlinker();
    }
    if (in == 'x') {
      write_handler.ToggleDoorsOpen();
    }
    if (in == 'q') {
      write_handler.ToggleBattery();
    }
    if (in == 27) {
      write_handler.SendShutOff();
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      on = false;
    }
    while (getch() != ERR) {
    }
  }
};

#endif  // USERINPUT_READER_H