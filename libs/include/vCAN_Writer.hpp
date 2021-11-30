#ifndef VCAN_WRITER_HPP_
#define VCAN_WRITER_HPP_
#include <iostream>
#include "socketcan_cpp.h"
#include <chrono>
#include <thread>

class VCANWriter {
 private:
    scpp::SocketCan sockat_can;
 public:
    VCANWriter();
    void WriteToCAN(int _id, uint8_t _value[]);
};

#endif