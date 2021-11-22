#ifndef WRITEHANDLER_HPP_
#define WRITEHANDLER_HPP_
#include "socketcan_cpp.h"
#include "vCAN_Writer.hpp"

class WriteHandler {
 private:
  int value[8]{0, 0, 0, 0, 0, 0, 0, 0};
  int toEmuFromInput = 0x123;
  int toICFromInput = 0x333;
  int toICFromEmu = 0x321;

 public:
  WriteHandler() {}
  void ToggleBreak();
  void SetThrottle(int _value);
  void SetGear(int _value);
  void WriteRPM(float _value);
  void WriteVehicleSpeed(float _value);
  void WriteEngineState(float _vs, float _es, int _gear);
};
#endif
