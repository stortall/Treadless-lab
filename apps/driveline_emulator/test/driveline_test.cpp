#include "gtest/gtest.h"
#include "driveline.hpp"


 class DrivelineTest : public ::testing::Test
{
protected:
    Driveline UpdateEngineSpeed(float 50,true);

  void SetUp() override
  {
    //Engine On
    engineOn.setEngineStatus(true);

    //Engine at 50 acc
    engine50.setEngineStatus(true);
    engine50.updateTRPM(50);
    WaitForRPM(engine50, GearMode::D);

    //Engine at 100 acc
    engine100.setEngineStatus(true);
    engine100.updateTRPM(100);
    WaitForRPM(engine100, GearMode::D);
  }
};

public:
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
    
// protected:
//   Engine engineOff;
//   Engine engineOn;
//   Engine engine50;
//   Engine engine100;
//   void WaitForRPM(Engine &, GearMode);
//   void SetUp() override
//   {
//     //Engine On
//     engineOn.setEngineStatus(true);

//     //Engine at 50 acc
//     engine50.setEngineStatus(true);
//     engine50.updateTRPM(50);
//     WaitForRPM(engine50, GearMode::D);

//     //Engine at 100 acc
//     engine100.setEngineStatus(true);
//     engine100.updateTRPM(100);
//     WaitForRPM(engine100, GearMode::D);
//   }
// };

// void EngineTest::WaitForRPM(Engine &engine, GearMode gear_mode)
// {
//   int iters = 0;
//   do
//   {
//     engine.updateARPM(0, gear_mode);
//     iters++;

//   } while (iters < 5000);
// }

void DrivelineTest::

// TEST_F(DrivelineTest, Hazard)
// {
//   engineOn.setHazard(true);
//   EXPECT_EQ(engineOn.getHazard(), true);
//   engineOn.setHazard(false);
//   EXPECT_EQ(engineOn.getHazard(), false);
// }