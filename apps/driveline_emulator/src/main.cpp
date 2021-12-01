
#include "socketcan.h"
#include "write_handler.hpp"
#include "driveline.hpp"


void CanReader(Driveline* engine) {
  // init
  bool run = true;
  scpp::SocketCan sockat_can;
  if (sockat_can.open("vcan0") != scpp::STATUS_OK) {
    std::cout << "Cannot open vcan0." << std::endl;
    std::cout << "Check whether the vcan0 interface is up!" << std::endl;
    exit(-1);
  }
  while (run) {
    scpp::CanFrame fr;
    if (sockat_can.read(fr) == scpp::STATUS_OK && fr.id == 0x123) {
      engine->SetThrottle(fr.data[0]);
      engine->SetBrake(fr.data[1]);
      engine->SetGearSelectorState(fr.data[3]);
      engine->ShutOffApp(fr.data[4]);
      if (fr.data[4] == 255) {
        run = false;
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

void CanSend(Driveline * engine) {
  WriteHandler write_handler;
  while (engine->AppIsRunning()) {
    write_handler.WriteEngineState(engine->GetVehicleSpeed(), (engine->GetRPM()/25),
      std::max(engine->GetGear(), 1), engine->GetGearSelectorState(), engine->GetResistance());
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
