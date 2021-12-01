#include "driveline.hpp"

void Emulator::loop() {
  while (run) {
    UpdateResistance();
    UpdateState();
    PrintState();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
void Emulator::UpdateState() {
  if (GetGearSelectorState() == 'N' ||
    GetGearSelectorState() == 'D') {
    if (throttle > 0 && gear > 0) {
      brake = false;
      UpdateEngineSpeed(370 * ratio[gear] / ratio[1] - resistance);
    } else if (throttle > 0 && gear == 0) {
      brake = false;
      UpdateEngineSpeed(370 - resistance);
    } else if (vehicle_speed > 0 && engine_speed > idle_speed && !brake) {
      UpdateEngineSpeed(-(resistance));
    } else if (vehicle_speed > 0 && engine_speed > idle_speed && brake) {
      UpdateEngineSpeed(-(resistance + 100));
    } else if (engine_speed <= idle_speed && !brake) {
      UpdateEngineSpeed(10 + ((idle_speed - engine_speed) / 10));
    } else if (engine_speed <= idle_speed && brake) {
      UpdateEngineSpeed(10 + ((idle_speed - engine_speed) / 10), false);
    } else if (gear == 0 && engine_speed > idle_speed) {
      UpdateEngineSpeed(-(resistance + (engine_speed - idle_speed) / 20));
    }
  }
}
void Emulator::SetThrottle(unsigned int _value) {
  std::unique_lock lock(throttle_mutex);
  throttle = _value;
}
int Emulator::GetThrottle() {
  std::shared_lock lock(throttle_mutex);
  return throttle;
}
int Emulator::GetVehicleSpeed() {
  return vehicle_speed;
}
int Emulator::GetRPM() {
  return engine_speed;
}
int Emulator::GetGear() {
  return gear;
}
void Emulator::SetBrake(int _i) {
  const std::unique_lock lock(brake_mutex);
  brake = _i;
}
bool Emulator::GetBrake() {
  const std::shared_lock lock(brake_mutex);
  return brake;
}
void Emulator::UpdateEngineSpeed(float _delta, bool _clutch_engaged) {
  engine_speed = engine_speed + _delta;
  if (!_clutch_engaged && engine_speed >= idle_speed) {
    engine_speed = engine_speed - (_delta * 3);
  }
  if (engine_speed < 2000) {
    if (!GearDown() && engine_speed < 0) {
      engine_speed = 0;
    }
  } else if (engine_speed > 4500 && gear > 0) {
    if (!GearUp() && engine_speed > max_engine_speed) {
      engine_speed = max_engine_speed;
    }
  } else if (gear == 0) {
    if (engine_speed > max_engine_speed) {
      engine_speed = max_engine_speed - 500;
    }
  }
  if (_clutch_engaged && gear > 0) {
    vehicle_speed = engine_speed / ratio[gear];
  } else if (vehicle_speed > 0) {
    vehicle_speed = vehicle_speed - 1;
  }
}

void Emulator::PrintState() {
  system("clear");
  std::cout << "RPM:               " << GetRPM() << " rpm\r" << std::endl;
  std::cout << "Speed:             " << GetVehicleSpeed() << " km/h\r" << std::endl;
  std::cout << "Gear:              " << GetGear() << "\r" << std::endl;
  std::cout << "Throttle:          " << GetThrottle() << "\r" << std::endl;
  std::cout << "Brake:             " << GetBrake() << "\r" << std::endl;
  std::cout << "GearSelectorState: " << GetGearSelectorState() << "\r" << std::endl;
  std::cout << "Resistance:        " << GetResistance() << "\r" << std::endl;
}
bool Emulator::GearUp() {
  bool ret = false;
  if (gear < (sizeof(ratio) / 4 - 1)) {
    gear++;
    engine_speed = vehicle_speed * ratio[gear];
    ret = true;
  }
  return ret;
}
bool Emulator::GearDown() {
  bool ret = false;
  if (gear > 1) {
    gear--;
    engine_speed = vehicle_speed * ratio[gear];
    ret = true;
  }
  return ret;
}
void Emulator::UpdateResistance() {
  int air_drag = static_cast<int>(std::pow((GetVehicleSpeed()/65.0), 3));
  int mass_resistance = static_cast<int>(std::pow((GetVehicleSpeed()/40.0), 2));
  int rolling_resistance = 10;
  int internal_resistance = static_cast<int>(GetRPM()/400.0);
  if (gear > 0) {
    resistance = air_drag + mass_resistance + rolling_resistance + internal_resistance;
  } else {
    resistance = internal_resistance;
  }
}
int Emulator::GetResistance() {
  return resistance;
}
void Emulator::SetGearSelectorState(char _value) {
  if (_value == 'P' && GetVehicleSpeed() == 0) {
    GearSelectorState = _value;
    gear = 0;
    engine_speed = 0;
  // } else if (_value == 'R' && GetVehicleSpeed() == 0) {
  //   GearSelectorState = _value;
  //   gear = 0;
  //   engine_speed = 0;
  } else if (_value == 'N' && GetVehicleSpeed() == 0 && GearSelectorState != 'N') {
    GearSelectorState = _value;
    gear = 0;
    engine_speed = 0;
  } else if (_value == 'D' && GetVehicleSpeed() == 0 && GearSelectorState != 'D') {
    GearSelectorState = _value;
    gear = 1;
    engine_speed = 0;
    UpdateEngineSpeed(idle_speed);
  }
}
char Emulator::GetGearSelectorState() {
  return GearSelectorState;
}

bool Emulator::AppIsRunning() {
  return run;
}
void Emulator::ShutOffApp(int b) {
  if (b == 255) {
    run = false;
  }
}
