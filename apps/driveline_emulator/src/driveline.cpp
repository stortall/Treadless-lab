#include "driveline.hpp"

void Driveline::loop() {
  while (true) {
    Driveline::UpdateState();
    Driveline::PrintState();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
void Driveline::UpdateState() {
  if (throttle > 0) {
    brake = false;
    SetSpeed(50);
  } else if (vehicle_speed > 0 && !brake) {
    SetSpeed(-(engine_speed / 400));
  } else if (vehicle_speed > 0 && brake) {
    SetSpeed(-100);
  }
}
void Driveline::SetThrottle(unsigned int _value) {
  std::unique_lock lock(throttle_mutex);
  throttle = _value;
}
int Driveline::GetThrottle() {
  std::shared_lock lock(throttle_mutex);
  return throttle;
}
int Driveline::GetVehicleSpeed() { return vehicle_speed; }
void Driveline::SetBrake(int _i) {
  const std::unique_lock lock(brake_mutex);
  brake = _i;
}
bool Driveline::GetBrake() {
  const std::shared_lock lock(brake_mutex);
  return brake;
}
void Driveline::SetSpeed(float _delta) {
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

void Driveline::PrintState() {
  system("clear");
  std::cout << "RPM:      " << (int)(engine_speed) << " rpm\r" << std::endl;
  std::cout << "Speed:    " << (int)vehicle_speed << " km/h\r" << std::endl;
  std::cout << "Gear:     " << gear + 1 << "\r" << std::endl;
  std::cout << "Throttle: " << GetThrottle() << "\r" << std::endl;
  std::cout << "Brake:    " << GetBrake() << "\r" << std::endl;
}
bool Driveline::GearUp() {
  bool ret = false;
  if (gear < (sizeof(ratio) / 4 - 1)) {
    gear++;
    engine_speed = vehicle_speed * ratio[gear];
    ret = true;
  }
  return ret;
}
bool Driveline::GearDown() {
  bool ret = false;
  if (gear > 0) {
    gear--;
    engine_speed = vehicle_speed * ratio[gear];
    ret = true;
  }
  return ret;
}