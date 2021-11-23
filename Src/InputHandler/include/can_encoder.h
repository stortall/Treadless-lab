#ifndef CAN_BUFFER_H
#define CAN_BUFFER_H

#include "user_input.h"



typedef struct CanData_struct{
    uint32_t id = 0;
    uint8_t data[8] = {0,0,0,0,0,0,0,0};
    uint8_t length = 0;
} CanData;


#endif // CAN_BUFFER_H