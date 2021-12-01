#include "write_handler.hpp"

WriteHandler::WriteHandler() {
  if (sockat_can.open("vcan0") != scpp::STATUS_OK) {
    std::cout << "Cannot open vcan0." << std::endl;
    std::cout << "Check whether the vcan0 interface is up!" << std::endl;
    exit(-1);
  }
}

void WriteHandler::WriteToCAN(int _id, uint8_t _value[]) {
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

void WriteHandler::SetThrottle(int _value) {
  value[0] = _value;
  value[1] = 0;

  WriteToCAN(toEmuFromInput, value);
}
void WriteHandler::SetGearSelectorState(char _value) {
  value[3] = _value;
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
void WriteHandler::WriteEngineState(float _vs, float _es, int _gear,
                                    char _gear_shifter_state, int _res) {
  value[0] = _vs;
  value[1] = _es;
  value[2] = _gear;
  value[3] = _gear_shifter_state;
  value[4] = _res;
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
void WriteHandler::SendShutOff() {
  printf("in shutoff");
  value[4] = 255;
  WriteToCAN(toEmuFromInput, value);
}
