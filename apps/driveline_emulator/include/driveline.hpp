#ifndef DRIVELINE_HPP_
#define DRIVELINE_HPP_

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <iostream>
#include <map>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>

#include "read_write_handler.hpp"
#include "socketcan.h"

struct Input {
  int throttle = 0;
  bool brake = false;
  char GearSelectorState = 'P';
};

struct Output {
  char GearSelectorState = 'P';
  int engine_speed = 0;
  int vehicle_speed = 0;
  int gear = 0;
  int resistance = 0;
};

class Emulator {
 private:
  float max_engine_speed;
  std::array<int, 6> ratio;
  int idle_speed;
  std::atomic<bool> run;
  mutable std::shared_mutex input_mutex;
  Input input_data;
  mutable std::shared_mutex output_mutex;
  Output output_data;

 public:
  Emulator()
      : run(true),
        max_engine_speed(6300),
        ratio({0, 90, 60, 40, 30, 25}),
        idle_speed(800) {}
  void loop();
  void UpdateState();
  void UpdateEngineSpeed(float _delta, Output& _out,
                         bool _clutch_engaged = true);
  void PrintState();
  bool GearUp(Output& _out);
  bool GearDown(Output& _out);
  void UpdateResistance();
  char SetGearSelectorState(char _new);
  bool AppIsRunning();
  void ShutOffApp(int b);
  void SetInputParameters(scpp::CanFrame _fr);
  Input GetInputParameters();
  Output GetOutputParameters();
  void SetOutputParameters(Output _out);
};

#endif