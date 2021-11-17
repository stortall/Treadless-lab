#ifndef USER_INPUT_H
#define USER_INPUT_H
#include <cstdint>
#include <mutex>


typedef struct user_input_struct1
{
    bool ignition   : false;
    uint8_t accelerator_pedal;
    
    
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
}

namespace gear_position
{
    
    const uint8_t P = 0;
    const uint8_t N = 1;
    const uint8_t D = 2;
    const uint8_t R = 3;

}

namespace acceleration
{
    
}


#endif // USER_INPUT_H