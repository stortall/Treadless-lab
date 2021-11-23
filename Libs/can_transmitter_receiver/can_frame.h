#ifndef CAN_FRAME_H
#define CAN_FRAME_H

class CanFrame
{ 
  public:
    int value[8] {0, 0, 0, 0, 0, 0, 0, 0};
    int toEmuFromInput = 123;
    int toICFromInput= 333;
    int toICFromEmu = 321;
 


}can_frame_structure;


#endif //CAN_FRAME_H