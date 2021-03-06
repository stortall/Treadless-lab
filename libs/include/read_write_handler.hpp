#ifndef WRITEHANDLER_HPP_
#define WRITEHANDLER_HPP_
#include <cstring>
#include <iostream>

#include "socketcan.h"

typedef union _icons {
  struct __attribute__((packed)) _bits {
    unsigned char hazard : 1;
    unsigned char right_blinker : 1;
    unsigned char left_blinker : 1;
    unsigned char engine_check : 1;
    unsigned char oil_check : 1;
    unsigned char abs : 1;
    unsigned char battery : 1;
    unsigned char seat_belt : 1;
    unsigned char doors_open : 1;
    unsigned char high_beam : 1;
    unsigned char hand_break : 1;
    unsigned char _reserved_pad : 5;
    unsigned char res_pad_2[6];
  } Bits;
  uint8_t Data[8]{0, 0, 0, 0, 0, 0, 0, 0};
} Iconss_t;

class ReaderWriteHandler {
 private:
  uint8_t value[8]{0, 0, 0, 0, 0, 0, 0, 0};
  Iconss_t icons;
  int toEmuFromInput = 0x123;
  int toICFromInput = 0x333;
  int toICFromEmu = 0x321;
  scpp::SocketCan sockat_can;
  void WriteToCAN(int _id, uint8_t _value[]);

 public:
  ReaderWriteHandler();
  void ToggleBreak();
  void SetThrottle(const int _value);
  void SetGearSelectorState(const char _value);

  void WriteEngineState(float _vs, float _es, int _gear,
                        char gear_shifter_state, int _res);
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
  void SendShutOff();
  scpp::SocketCanStatus ReadFromCAN(scpp::CanFrame& _fr);
};

#endif
