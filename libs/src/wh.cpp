#include "wh.hpp"



  void WriteHandler::SetThrottle(int _value) {
    value[0] = _value;
    value[1] = 0;
    value[7] = 255;
    WriteToCAN(toEmuFromInput, value);
  }
  void WriteHandler::SetGear(int _value) {
    value[2] = _value;
    WriteToCAN(toEmuFromInput, value);
  }
  void WriteHandler::ToggleBreak() {
    if (value[1] == 0) {
      value[1] = 1;
      value[0] = 0;  // turn off throttle
      WriteToCAN(toEmuFromInput, value);
    } else if (value[1] == 1) {
      value[1] = 0;
      WriteToCAN(toEmuFromInput, value);
    }
  }
  void WriteHandler::WriteRPM(float _value) {}
  void WriteHandler::WriteVehicleSpeed(float _value) {
    // value[0] = _value;
    // WriteToCAN(toICFromEmu, value);
  }
  void WriteHandler::WriteEngineState(float _vs, float _es, int _gear){
    value[0]=_vs;
    value[1]=_es;
    value[2]=_gear;
    WriteToCAN(toICFromEmu, value);
  }