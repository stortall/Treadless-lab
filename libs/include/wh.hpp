#ifndef WRITEHANDLER_HPP_
#define WRITEHANDLER_HPP_
#include "socketcan_cpp.h"
#include "vCAN_Writer.hpp"
#include <cstring>

typedef union _icons {
  struct __attribute__((packed)) _bits {
    unsigned char  hazard : 1;
    unsigned char  right_blinker : 1;
    unsigned char  left_blinker : 1;
    unsigned char  engine_check : 1;
    unsigned char  oil_check : 1;
    unsigned char  abs : 1;
    unsigned char  battery : 1;
    unsigned char  seat_belt : 1;
    unsigned char  doors_open : 1;
    unsigned char  high_beam : 1;
    unsigned char  hand_break : 1;
    unsigned char  _reserved_pad : 5;
    unsigned char  res_pad_2 [6];
  } Bits;
  uint8_t Data[8];
} Iconss_t;

class WriteHandler {
 private:
  uint8_t value[8]{0, 0, 0, 0, 0, 0, 0, 0};
  
  Iconss_t icons;
  uint8_t to_ic_array[8];
  
  int toEmuFromInput = 0x123;
  int toICFromInput = 0x333;
  int toICFromEmu = 0x321;

 public:
  WriteHandler() {
    std::memset(&icons,0, sizeof (Iconss_t));
    
  }

  void ToggleBreak();
  void SetThrottle(int _value);
  void SetGearSelectorState(char _value);
  void WriteRPM(float _value);
  void WriteVehicleSpeed(float _value);
  void WriteEngineState(float _vs, float _es, int _gear);
  void ToggleHazard();
  void ToggleHighBeam();
  void ToggleABS();
  void ToggleHandBrake();
  void ToggleBattery();
  void ToggleSeatBelt();
  void ToggleDoorsOpen();
  void ToggleEngineCheck();
  void ToggleOilCheck();
  void ToggleLeftBlinker();
  void ToggleRightBlinker();

};
#endif
