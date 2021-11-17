#include <ncurses.h>
#include <array>
#include <chrono>
#include <iostream>
#include <thread>
#include "socketcan_cpp.h"
#include "vCAN_Writer.hpp"
#include "wh.cpp"
#include <mutex>
#include <shared_mutex>

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
  void loop() {
    while (true) {
      UpdateState();
      PrintState();
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  }
  void UpdateState() {
    if (throttle > 0) {
      brake = false;
      SetSpeed(50);
    } else if (vehicle_speed > 0 && !brake) {
      SetSpeed(-(engine_speed / 400));
    } else if (vehicle_speed > 0 && brake) {
      SetSpeed(-100);
    }
  }
  void SetThrottle(unsigned int _value) {
    std::unique_lock lock(throttle_mutex);
    throttle = _value;
  }
  int GetThrottle() {
    std::shared_lock lock(throttle_mutex);
    return throttle;
  }
  int GetVehicleSpeed() {
    return vehicle_speed;
  }
  void SetBrake(int _i) {
    const std::unique_lock lock(brake_mutex);
    brake = _i;
  }
  bool GetBrake() {
    const std::shared_lock lock(brake_mutex);
    return brake;
  }
  void SetSpeed(float _delta) {
    engine_speed = engine_speed + _delta;
    if (engine_speed < 1500) {
      if (!GearDown() && engine_speed < 0) {
        engine_speed = 0;
      }
    } else if (engine_speed > 4000) {
      if (!GearUp() && engine_speed > max_engine_speed) {
        engine_speed = max_engine_speed;
      }
    }
    vehicle_speed = engine_speed / ratio[gear];
  }
  void PrintState() {
    system("clear");
    std::cout << "RPM:      " << (int)(engine_speed) << " rpm\r" << std::endl;
    std::cout << "Speed:    " << (int)vehicle_speed << " km/h\r" << std::endl;
    std::cout << "Gear:     " << gear + 1 << "\r" << std::endl;
    std::cout << "Throttle: " << GetThrottle() << "\r" << std::endl;
    std::cout << "Brake:    " << GetBrake() << "\r" << std::endl;
  }
  bool GearUp() {
    bool ret = false;
    if (gear < (sizeof(ratio) / 4 - 1)) {
      gear++;
      engine_speed = vehicle_speed * ratio[gear];
      ret = true;
    }
    return ret;
  }
  bool GearDown() {
    bool ret = false;
    if (gear > 0) {
      gear--;
      engine_speed = vehicle_speed * ratio[gear];
      ret = true;
    }
    return ret;
  }
};

void CanReader(Driveline* engine) {
  // init
  scpp::SocketCan sockat_can;
  if (sockat_can.open("vcan0") != scpp::STATUS_OK) {
    std::cout << "Cannot open vcan0." << std::endl;
    std::cout << "Check whether the vcan0 interface is up!" << std::endl;
    exit(-1);
  }
  while (true) {
    scpp::CanFrame fr;
    if (sockat_can.read(fr) == scpp::STATUS_OK && fr.id == 123) {
      engine->SetThrottle(fr.data[0]);
      engine->SetBrake(fr.data[1]);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

void CanSend(Driveline * engine) {
  WriterHandler wh = WriterHandler();
  while (true) {
    wh.WriteVehicleSpeed(engine->GetVehicleSpeed());
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

int main() {
  Driveline DL1;
  std::thread DrivelineLoop(&Driveline::loop, &DL1);
  std::thread InputLoop(CanReader, &DL1);
  std::thread PrintLoop(CanSend, &DL1);
  DrivelineLoop.join();
  InputLoop.join();
  PrintLoop.join();
  return 0;
}
