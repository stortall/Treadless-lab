#include <userinput_reader.h>
#include <iostream>
#include "chrono"



int main() {
  InputReader reader;
  

  while (true) {
    reader.readInput();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}