#ifndef VCAN_WRITER_HPP_
#define VCAN_WRITER_HPP_
#include <iostream>
#include "socketcan_cpp.h"
#include <chrono>
#include <thread>


void WriteToCAN(int _id, int _value[]);

#endif