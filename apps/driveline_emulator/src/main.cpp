
#include "driveline.hpp"
#include "read_write_handler.hpp"
#include "socketcan.h"

void WriteCAN(ReaderWriteHandler* _rwh, Emulator* _emu) {
  _rwh->WriteEngineState(_emu->GetVehicleSpeed(), _emu->GetRPM() / 25,
                         std::max(_emu->GetGear(), 1),
                         _emu->GetGearSelectorState(), _emu->GetResistance());
}
void ReadCAN(ReaderWriteHandler* _rwh, Emulator* _emu, bool* _run) {
  scpp::CanFrame fr;
  if (_rwh->ReadFromCAN(fr) == scpp::STATUS_OK && fr.id == 0x123) {
    _emu->SetThrottle(fr.data[0]);
    _emu->SetBrake(fr.data[1]);
    _emu->SetGearSelectorState(fr.data[3]);
    _emu->ShutOffApp(fr.data[4]);
    if (fr.data[4] == 255) {
      *_run = false;
    }
  }
}
void CanReadWrite(Emulator* _emu) {
  ReaderWriteHandler rw_handler;
  bool run = true;
  while (run) {
    WriteCAN(&rw_handler, _emu);
    ReadCAN(&rw_handler, _emu, &run);
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
