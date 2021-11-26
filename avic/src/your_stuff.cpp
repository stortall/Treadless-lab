//#include <chrono>
#include <thread>
#include <iostream>
#include "your_stuff.h"
#include "can_common.h"
#include <sstream>
#include <typeinfo>

namespace CANID
{
    const canid_t TO_IC_FROM_EMU = 0x321;
    const canid_t TO_IC_FROM_INPUT = 0x123;
    const canid_t ICONS =0x333;
}// namespace CANID


void yourStuff::YouHaveJustRecievedACANFrame(const canfd_frame * const _frame) {
    switch (_frame->can_id) {
    case CANID::TO_IC_FROM_EMU: {
            //const struct CAN::MSG::_engine *d = reinterpret_cast<const struct CAN::MSG::_engine * >((_frame->data));

        this->InstrumentCluster.setSpeed(_frame->data[0]);
        QString accbrakegear = /* "Speed: " + QString::number(_frame->data[0],10) + "\n"
                               "brake: " + QString::number(_frame->data[1],16) + "\n"
                               "Gear:"   + QString::number(_frame->data[2],16)+ "\n" */
                            "Resistance:" + QString::number(_frame->data[4],10)+ "\n";
        this->InstrumentCluster.setTXT(accbrakegear);
        this->InstrumentCluster.setRPM((_frame->data[1])*25);
        this->InstrumentCluster.setGear(_frame->data[2]);

        // this->InstrumentCluster.setGearPindle_char(_frame->data[3]);
        int gear_shifter_state = 0;
        if (_frame->data[3] == 'P') {
            gear_shifter_state = 0;
        } else if (_frame->data[3] == 'N') {
            gear_shifter_state = 1;
        } else if (_frame->data[3] == 'D') {
            gear_shifter_state = 3;
        }
        this->InstrumentCluster.setGearPindle_int(gear_shifter_state);


        break;
    }
    case CANID::ICONS: {
       //struct _icons  p//= reinterpret_cast<struct _icons * >(_frame->data);
       Iconss_t icn;
       icn.Data[0]=_frame->data[0];
       icn.Data[1]=_frame->data[1];
       
  /*   static bool once = false;
    if (!once) {
        icn.Bits.hazard=1;
        //     p.hazard = 1;
             once = true;
         } else{
             //icons.hazard = _frame->data[0] >> 0 & 1;
             icn.Bits.hazard=0;
         }
 */
    this->InstrumentCluster.setIcon(&icn);


        break;
    }
    default:
        break;
    }

}


/******************************* ANYTHING BELOW THIS LINE IS JUST BORING STUFF *******************************/

yourStuff::yourStuff(const std::string &_ifName, QObject *_vs) {
    if(!(this->CANReader.open(_ifName))) exit(-1);//emit die();

    this->InstrumentCluster.init(_vs);

    this->startTimer(1);
}

bool yourStuff::run() {
    bool ret = true;
    CANOpener::ReadStatus status = CANOpener::ReadStatus::OK;
    canfd_frame frame;
    this->CANReader.read(&frame);
    /*while*/if (status == CANOpener::ReadStatus::OK) {
        this->YouHaveJustRecievedACANFrame(&frame);
    }
    if(frame.can_id==0x123 && frame.data[4]==255){
        ret = false;
    }
    if (status == CANOpener::ReadStatus::ERROR) ret = false;
    else if (status == CANOpener::ReadStatus::NAVAL ||
             status == CANOpener::ReadStatus::ENDOF) this->Counter++;
    else   this->Counter = 0;
    //if (this->Counter > 200) ret = false;
    
    return ret;
}

void yourStuff::timerEvent(QTimerEvent*) {
    if(this->run());
    else {
//    emit this->die();
        exit(-1);
    }

}

