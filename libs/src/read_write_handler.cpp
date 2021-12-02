#include "read_write_handler.hpp"

ReaderWriteHandler::ReaderWriteHandler() {
  if (sockat_can.open("vcan0") != scpp::STATUS_OK) {
    std::cout << "Cannot open vcan0." << std::endl;
    std::cout << "Check whether the vcan0 interface is up!" << std::endl;
    exit(-1);
  }
}

void ReaderWriteHandler::WriteToCAN(int _id, uint8_t _value[]) {
  scpp::CanFrame cf_to_write;
  cf_to_write.id = _id;
  cf_to_write.len = 8;
  for (int i = 0; i < 8; ++i) {
    cf_to_write.data[i] = _value[i];
  }
  auto write_sc_status = sockat_can.write(cf_to_write);
  if (write_sc_status != scpp::STATUS_OK)
    printf("something went wrong on socket write, error code : %d \n",
           int32_t(write_sc_status));
}

scpp::SocketCanStatus ReaderWriteHandler::ReadFromCAN(scpp::CanFrame& _fr) {
  return sockat_can.read(_fr);
}

void ReaderWriteHandler::SetThrottle(const int _value) {
  value[0] = _value;
  value[1] = 0;
  WriteToCAN(toEmuFromInput, value);
}
void ReaderWriteHandler::SetGearSelectorState(const char _value) {
  value[3] = _value;
  WriteToCAN(toEmuFromInput, value);
}
void ReaderWriteHandler::ToggleBreak() {
  if (value[1] == 0) {
    value[1] = 1;
    value[0] = 0;  // turn off throttle

  } else if (value[1] == 1) {
    value[1] = 0;
  }
  WriteToCAN(toEmuFromInput, value);
}

void ReaderWriteHandler::WriteEngineState(float _vs, float _es, int _gear,
                                          char _gear_shifter_state, int _res) {
  value[0] = _vs;
  value[1] = _es;
  value[2] = _gear;
  value[3] = _gear_shifter_state;
  value[4] = _res;
  WriteToCAN(toICFromEmu, value);
}
void ReaderWriteHandler::ToggleHazard() {
  icons.Bits.hazard ^= 0b1;
  WriteToCAN(toICFromInput, icons.Data);
}

void ReaderWriteHandler::ToggleABS() {
  icons.Bits.abs ^= 0b1;
  WriteToCAN(toICFromInput, icons.Data);
}

void ReaderWriteHandler::ToggleDoorsOpen() {
  icons.Bits.doors_open ^= 0b1;
  WriteToCAN(toICFromInput, icons.Data);
}

void ReaderWriteHandler::ToggleEngineCheck() {
  icons.Bits.engine_check ^= 0b1;
  WriteToCAN(toICFromInput, icons.Data);
}

void ReaderWriteHandler::ToggleHandBrake() {
  icons.Bits.hand_break ^= 0b1;
  WriteToCAN(toICFromInput, icons.Data);
}

void ReaderWriteHandler::ToggleHighBeam() {
  icons.Bits.high_beam ^= 0b1;
  WriteToCAN(toICFromInput, icons.Data);
}

void ReaderWriteHandler::ToggleLeftBlinker() {
  icons.Bits.left_blinker ^= 0b1;
  WriteToCAN(toICFromInput, icons.Data);
}

void ReaderWriteHandler::ToggleRightBlinker() {
  icons.Bits.right_blinker ^= 0b1;
  WriteToCAN(toICFromInput, icons.Data);
}

void ReaderWriteHandler::ToggleOilCheck() {
  icons.Bits.oil_check ^= 0b1;
  WriteToCAN(toICFromInput, icons.Data);
}

void ReaderWriteHandler::ToggleSeatBelt() {
  icons.Bits.seat_belt ^= 0b1;
  WriteToCAN(toICFromInput, icons.Data);
}

void ReaderWriteHandler::ToggleBattery() {
  icons.Bits.battery ^= 0b1;
  WriteToCAN(toICFromInput, icons.Data);
}
void ReaderWriteHandler::SendShutOff() {
  printf("in shutoff");
  value[4] = 255;
  WriteToCAN(toEmuFromInput, value);
}
