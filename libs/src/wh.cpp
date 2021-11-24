#include "wh.hpp"

void WriteHandler::SetThrottle(int _value) {
  value[0] = _value;
  value[1] = 0;

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
void WriteHandler::WriteEngineState(float _vs, float _es, int _gear) {
  value[0] = _vs;
  value[1] = _es;
  value[2] = _gear;
  WriteToCAN(toICFromEmu, value);
}
void WriteHandler::ToggleHazard() {
  if (icons.Bits.hazard == 1) {
    icons.Bits.hazard = 0;
  } else {
    icons.Bits.hazard = 1;
  }

  WriteToCAN(toICFromInput, icons.Data);
}

void WriteHandler::ToggleABS() {
  if (icons.Bits.abs == 1) {
    icons.Bits.abs = 0;
  } else {
    icons.Bits.abs = 1;
  }
  WriteToCAN(toICFromInput, icons.Data);
}

void WriteHandler::ToggleDoorsOpen() {
  if (icons.Bits.doors_open == 1) {
    icons.Bits.doors_open = 0;
  } else {
    icons.Bits.doors_open = 1;
  }
  WriteToCAN(toICFromInput, icons.Data);
}

void WriteHandler::ToggleEngineCheck() {
  if (icons.Bits.engine_check == 1) {
    icons.Bits.engine_check = 0;
  } else {
    icons.Bits.engine_check = 1;
  }
  WriteToCAN(toICFromInput, icons.Data);
}

void WriteHandler::ToggleHandBrake() {
  if (icons.Bits.hand_break == 1) {
    icons.Bits.hand_break = 0;
  } else {
    icons.Bits.hand_break = 1;
  }
  WriteToCAN(toICFromInput, icons.Data);
}

void WriteHandler::ToggleHighBeam() {
  if (icons.Bits.high_beam == 1) {
    icons.Bits.high_beam = 0;
  } else {
    icons.Bits.high_beam = 1;
  }
  WriteToCAN(toICFromInput, icons.Data);
}

void WriteHandler::ToggleLeftBlinker() {
  if (icons.Bits.left_blinker == 1) {
    icons.Bits.left_blinker = 0;
  } else {
    icons.Bits.left_blinker = 1;
  }
  WriteToCAN(toICFromInput, icons.Data);
}

void WriteHandler::ToggleRightBlinker() {
  if (icons.Bits.right_blinker == 1) {
    icons.Bits.right_blinker = 0;
  } else {
    icons.Bits.right_blinker = 1;
  }
  WriteToCAN(toICFromInput, icons.Data);
}

void WriteHandler::ToggleOilCheck() {
  if (icons.Bits.oil_check == 1) {
    icons.Bits.oil_check = 0;
  } else {
    icons.Bits.oil_check = 1;
  }
  WriteToCAN(toICFromInput, icons.Data);
}

void WriteHandler::ToggleSeatBelt() {
  if (icons.Bits.seat_belt == 1) {
    icons.Bits.seat_belt = 0;
  } else {
    icons.Bits.seat_belt = 1;
  }
  WriteToCAN(toICFromInput, icons.Data);
}

void WriteHandler::ToggleBattery() {
  if (icons.Bits.battery == 1) {
    icons.Bits.battery = 0;
  } else {
    icons.Bits.battery = 1;
  }
  WriteToCAN(toICFromInput, icons.Data);
}
