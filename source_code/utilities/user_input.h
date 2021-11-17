#ifndef USER_INPUT_H
#define USER_INPUT_H
#include <cstdint>
#include <mutex>
#include <array>


typedef struct user_input_struct1
{
    bool ignition = false;
    uint8_t accelerator_pedal = 0;
    
    
}UserInputToEngine;

typedef struct user_input_struct2
{
    uint8_t gear_position;

}UserInputToGearBox;

typedef struct user_input_struct3
{
    uint8_t brake_pedal;
    bool lock;
    bool seat_belt;
    bool hazard_light;
    bool right_blinker;
    bool left_blinker;
    bool hand_brake;

}UserInputToVehicle;

namespace programmer_input
{
    bool simulation_running;
    uint8_t padding =   4;
}

namespace gear_position
{
    
    const uint8_t P = 0;
    const uint8_t N = 1;
    const uint8_t D = 2;
    const uint8_t R = 3;
    std::array<int, 5> ratio({80, 60, 40, 30, 25});

}

namespace acceleration
{
    const uint8_t up = 10;
    const uint8_t down = 10;
    const uint8_t max = 100;
    const uint8_t min = 0;
    
}

namespace braking
{
    const uint8_t up = 25;
    const uint8_t down = 25;
    const uint8_t max = 100;
    const uint8_t min = 0;


}

/*namespace engine
{
    const float rpm_max = 6000;
    const float rpm_min = 0;
    
}*/

namespace enviornment
{
    const uint8_t positive_inclination;     //
    const uint8_t negative_inclination;

}


#endif // USER_INPUT_H