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
  Input in = GetInputParameters();
  Output out = GetOutputParameters();
  out.GearSelectorState = in.GearSelectorState;
  if (in.GearSelectorState == 'N' || in.GearSelectorState == 'D') {
    if (in.throttle > 0 && out.gear > 0) {
      UpdateEngineSpeed(370 * ratio[out.gear] / ratio[1] - out.resistance, out);
    } else if (in.throttle > 0 && out.gear == 0) {
      UpdateEngineSpeed(370 - out.resistance, out);
    } else if (out.vehicle_speed > 0 && out.engine_speed > idle_speed &&
               !in.brake) {
      UpdateEngineSpeed(-(out.resistance), out);
    } else if (out.vehicle_speed > 0 && out.engine_speed > idle_speed &&
               in.brake) {
      UpdateEngineSpeed(-(out.resistance + 100), out);
    } else if (out.engine_speed <= idle_speed && !in.brake) {
      UpdateEngineSpeed(10 + ((idle_speed - out.engine_speed) / 10), out);
    } else if (out.engine_speed <= idle_speed && in.brake) {
      UpdateEngineSpeed(10 + ((idle_speed - out.engine_speed) / 10), out,
                        false);
    } else if (out.gear == 0 && out.engine_speed > idle_speed) {
      UpdateEngineSpeed(
          -(out.resistance + (out.engine_speed - idle_speed) / 20), out);
    }
  }
  SetOutputParameters(out);
}
void Emulator::UpdateEngineSpeed(float _delta, Output& _out,
                                 bool _clutch_engaged) {
  _out.engine_speed = _out.engine_speed + _delta;
  if (!_clutch_engaged && _out.engine_speed >= idle_speed) {
    _out.engine_speed = _out.engine_speed - (_delta * 3);
  }
  if (_out.engine_speed < 2000) {
    if (!GearDown(_out) && _out.engine_speed < 0) {
      _out.engine_speed = 0;
    }
  } else if (_out.engine_speed > 4500 && _out.gear > 0) {
    if (!GearUp(_out) && _out.engine_speed > max_engine_speed) {
      _out.engine_speed = max_engine_speed;
    }
  } else if (_out.gear == 0) {
    if (_out.engine_speed > max_engine_speed) {
      _out.engine_speed = max_engine_speed - 500;
    }
  }
  if (_clutch_engaged && _out.gear > 0) {
    _out.vehicle_speed = _out.engine_speed / ratio[_out.gear];
  } else if (_out.vehicle_speed > 0) {
    _out.vehicle_speed = _out.vehicle_speed - 1;
  }
}

void Emulator::PrintState() {
  Output out = GetOutputParameters();
  Input in = GetInputParameters();
  system("clear");
  std::cout << "RPM:               " << out.engine_speed << " rpm\r"
            << std::endl;
  std::cout << "Speed:             " << out.vehicle_speed << " km/h\r"
            << std::endl;
  std::cout << "Gear:              " << out.gear << "\r" << std::endl;
  std::cout << "Throttle:          " << in.throttle << "\r" << std::endl;
  std::cout << "Brake:             " << in.brake << "\r" << std::endl;
  std::cout << "GearSelectorState: " << out.GearSelectorState << "\r"
            << std::endl;
  std::cout << "Resistance:        " << out.resistance << "\r" << std::endl;
}
bool Emulator::GearUp(Output& _out) {
  bool ret = false;
  if (_out.gear < (sizeof(ratio) / 4 - 1)) {
    _out.gear++;
    _out.engine_speed = _out.vehicle_speed * ratio[_out.gear];
    ret = true;
  }
  return ret;
}
bool Emulator::GearDown(Output& _out) {
  bool ret = false;
  if (_out.gear > 1) {
    _out.gear--;
    _out.engine_speed = _out.vehicle_speed * ratio[_out.gear];
    ret = true;
  }
  return ret;
}
void Emulator::UpdateResistance() {
  struct Output out = GetOutputParameters();
  int air_drag = static_cast<int>(std::pow((out.vehicle_speed / 65.0), 3));
  int mass_resistance =
      static_cast<int>(std::pow((out.vehicle_speed / 40.0), 2));
  int rolling_resistance = 10;
  int internal_resistance = static_cast<int>(out.engine_speed / 400.0);
  if (out.gear > 0) {
    out.resistance =
        air_drag + mass_resistance + rolling_resistance + internal_resistance;
  } else {
    out.resistance = internal_resistance;
  }
  SetOutputParameters(out);
}
char Emulator::SetGearSelectorState(char _new) {
  struct Output out = GetOutputParameters();
  if (_new == 'P' && out.vehicle_speed == 0) {
    out.GearSelectorState = _new;
    out.gear = 0;
    out.engine_speed = 0;
  } else if (_new == 'N' && out.vehicle_speed == 0 &&
             out.GearSelectorState != 'N') {
    out.GearSelectorState = _new;
    out.gear = 0;
    out.engine_speed = 0;
  } else if (_new == 'D' && out.vehicle_speed == 0 &&
             out.GearSelectorState != 'D') {
    out.GearSelectorState = _new;
    out.gear = 1;
    out.engine_speed = 0;
    UpdateEngineSpeed(idle_speed, out);
  }
  SetOutputParameters(out);
  return out.GearSelectorState;
}
bool Emulator::AppIsRunning() { return run == true; }
void Emulator::ShutOffApp(int b) {
  if (b == 255) {
    run = false;
  }
}
void Emulator::SetInputParameters(scpp::CanFrame _fr) {
  std::unique_lock input_lock(input_mutex);
  input_data.throttle = _fr.data[0];
  input_data.brake = _fr.data[1];
  input_data.GearSelectorState = SetGearSelectorState(_fr.data[3]);
  ShutOffApp(_fr.data[4]);
}
Input Emulator::GetInputParameters() {
  std::unique_lock input_lock(input_mutex);
  return input_data;
}
Output Emulator::GetOutputParameters() {
  std::unique_lock output_lock(output_mutex);
  return output_data;
}
void Emulator::SetOutputParameters(Output _out) {
  std::unique_lock output_lock(output_mutex);
  output_data = _out;
}
