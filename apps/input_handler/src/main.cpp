#include <iostream>
#include "chrono"
#include "ncurses.h"
#include "wh.hpp"

int main() {
  WriteHandler wh;
  initscr();
  cbreak();
  noecho();
  // keypad(stdscr, TRUE);
  scrollok(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  while (true) {
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
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}