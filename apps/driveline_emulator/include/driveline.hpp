#ifndef DRIVELINE_HPP_
#define DRIVELINE_HPP_

#include <array>
#include <chrono>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <cmath>
#include <algorithm> 
#include <map>
#include <string>
#include "read_write_handler.hpp"
#include "socketcan.h"

class Emulator {
 private:
  float engine_speed;
  float vehicle_speed;
  int throttle;
  mutable std::shared_mutex throttle_mutex;
  bool brake;
  mutable std::shared_mutex brake_mutex;
  int gear;
  float max_engine_speed;
  std::array<int, 6> ratio;
  int resistance;
  char GearSelectorState;
  int idle_speed;
  bool run;

 public:
  Emulator() :
    engine_speed(0),
    vehicle_speed(0),
    throttle(0),
    brake(false),
    gear(0),
    run(true),
    max_engine_speed(6300),
    ratio({0, 90, 60, 40, 30, 25}),
    GearSelectorState('P') ,
    idle_speed(800) {}
    void loop();
    void UpdateState();
    void SetThrottle(unsigned int _value);
    int GetThrottle();
    int GetVehicleSpeed();
    void SetBrake(int _i);
    bool GetBrake();
    int GetRPM();
    int GetGear();
    void UpdateEngineSpeed(float _delta, bool _clutch_engaged = true);
    void PrintState();
    bool GearUp();
    bool GearDown();
    void UpdateResistance();
    int GetResistance();
    void SetGearSelectorState(char _value);
    char GetGearSelectorState();
    bool AppIsRunning();
    void ShutOffApp(int b);
};

#endif