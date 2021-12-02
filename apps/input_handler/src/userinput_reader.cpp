#include "userinput_reader.h"

InputReader::InputReader() {
  initscr();
  cbreak();
  noecho();
  scrollok(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  on = true;
}
void InputReader::readInput() {
  while ((in = getch()) == ERR) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  if (in >= '0' && in <= '9') {
    rw_handler.SetThrottle(in - '0');
  }
  if (in == 'b') {
    rw_handler.ToggleBreak();
  }
  if (in == 'p') {
    rw_handler.SetGearSelectorState('P');
  }
  if (in == 'n') {
    rw_handler.SetGearSelectorState('N');
  }
  if (in == 'd') {
    rw_handler.SetGearSelectorState('D');
  }
  if (in == 'h') {
    rw_handler.ToggleHazard();
  }
  if (in == 'o') {
    rw_handler.ToggleOilCheck();
  }
  if (in == 'a') {
    rw_handler.ToggleABS();
  }
  if (in == 'l') {
    rw_handler.ToggleHighBeam();
  }
  if (in == 'z') {
    rw_handler.ToggleSeatBelt();
  }
  if (in == 'c') {
    rw_handler.ToggleEngineCheck();
  }
  if (in == 'y') {
    rw_handler.ToggleLeftBlinker();
  }
  if (in == 'u') {
    rw_handler.ToggleRightBlinker();
  }
  if (in == 'x') {
    rw_handler.ToggleDoorsOpen();
  }
  if (in == 'q') {
    rw_handler.ToggleBattery();
  }
  if (in == 27) {
    rw_handler.SendShutOff();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    on = false;
  }
  while (getch() != ERR) {
  }
}
