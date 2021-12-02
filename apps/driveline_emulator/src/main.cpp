
#include "driveline.hpp"
#include "read_write_handler.hpp"
#include "socketcan.h"

void WriteCAN(ReaderWriteHandler* _rwh, Emulator* _emu) {
  Output data = _emu->GetOutputParameters();
  _rwh->WriteEngineState(data.vehicle_speed, data.engine_speed / 25,
                         std::max(data.gear, 1), data.GearSelectorState,
                         data.resistance);
}
void ReadCAN(ReaderWriteHandler* _rwh, Emulator* _emu) {
  scpp::CanFrame fr;
  if (_rwh->ReadFromCAN(fr) == scpp::STATUS_OK && fr.id == 0x123) {
    _emu->SetInputParameters(fr);
  }
}
void CanReadWrite(Emulator* _emu) {
  ReaderWriteHandler rw_handler;
  bool run = true;
  while (_emu->AppIsRunning()) {
    WriteCAN(&rw_handler, _emu);
    ReadCAN(&rw_handler, _emu);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
int main() {
  Emulator emu;
  std::thread DrivelineLoop(&Emulator::loop, &emu);
  std::thread CanLoop(CanReadWrite, &emu);
  DrivelineLoop.join();
  CanLoop.join();
  return 0;
}
