#ifndef DRIVELINE_HPP_
#define DRIVELINE_HPP_

#include <array>
#include <chrono>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>

class Driveline {
 private:
  float engine_speed;
  float vehicle_speed;
  int throttle;
  mutable std::shared_mutex throttle_mutex;
  bool brake;
  mutable std::shared_mutex brake_mutex;
  int gear;
  float max_engine_speed;
  std::array<int, 5> ratio;

 public:
  Driveline() :
    engine_speed(0),
    vehicle_speed(0),
    throttle(0),
    brake(false),
    gear(0),
    max_engine_speed(6000),
    ratio({80, 60, 40, 30, 25}) {}
    void loop();
    void UpdateState();
    void SetThrottle(unsigned int _value);
    int GetThrottle();
    int GetVehicleSpeed();
    void SetBrake(int _i);
    bool GetBrake();
    int GetRPM();
    int GetGear();
    void SetSpeed(float _delta);
    void PrintState();
    bool GearUp();
    bool GearDown();
};

#endif