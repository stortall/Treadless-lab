
#ifndef USERINPUT_READER_H
#define USERINPUT_READER_H

#include <ncurses.h>
#include <stdlib.h>

#include <chrono>
#include <cstring>
#include <iostream>
#include <thread>

#include "read_write_handler.hpp"
#include "socketcan.h"

class InputReader {
 public:
  ReaderWriteHandler rw_handler;
  char in;
  bool on;

 public:
  InputReader();
  void readInput();
};

#endif  // USERINPUT_READER_H
