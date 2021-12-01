
#include "socketcan.h"
#include "read_write_handler.hpp"
#include "driveline.hpp"

int main() {
  Driveline DL1;
  std::thread DrivelineLoop(&Driveline::loop, &DL1);
  DrivelineLoop.join();
  return 0;
}
