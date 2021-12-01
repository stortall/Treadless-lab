
#ifndef USERINPUT_READER_H
#define USERINPUT_READER_H

#include <ncurses.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <chrono>
#include <thread>
#include "socketcan.h"
#include "write_handler.hpp"

class InputReader {
 public:
  WriteHandler write_handler;
  char in;
  bool on;

 public:
  InputReader();
  void readInput();
};

#endif // USERINPUT_READER_H
