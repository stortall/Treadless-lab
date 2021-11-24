//#include <chrono>
#include <thread>
#include <iostream>
#include "your_stuff.h"
#include "can_common.h"
#include <sstream>

namespace CANID
{
    const canid_t TO_IC_FROM_EMU = 0x321;
    const canid_t TO_IC_FROM_INPUT = 0x123;
    const canid_t ICONS =0x333;

    //int toEmuFromInput = 0x123;
}// namespace CANID


void yourStuff::YouHaveJustRecievedACANFrame(const canfd_frame * const _frame) {
    switch (_frame->can_id) {
    case CANID::TO_IC_FROM_EMU: {
            //const struct CAN::MSG::_engine *d = reinterpret_cast<const struct CAN::MSG::_engine * >((_frame->data));

        this->InstrumentCluster.setSpeed(_frame->data[0]);
        QString accbrakegear = "Speed: " + QString::number(_frame->data[0],10) + "%\n"
                               "brake: " + QString::number(_frame->data[1],16) + "\n"
                               "Gear:"   + QString::number(_frame->data[2],16)+ "\n";

        this->InstrumentCluster.setTXT(accbrakegear);
        this->InstrumentCluster.setRPM((_frame->data[1])*25);
        this->InstrumentCluster.setGear(_frame->data[2]);
        this->InstrumentCluster.setGearPindle_int(_frame->data[2]);


        break;
    }
    case CANID::ICONS: {
       //struct _icons  p//= reinterpret_cast<struct _icons * >(_frame->data);
       Iconss_t icn;
       icn.Data[0]=_frame->data[0];
       icn.Data[1]=_frame->data[1];
       
    static bool once = false;
    if (!once) {
        icn.Bits.hazard=1;
        //     p.hazard = 1;
             once = true;
         } else{
             //icons.hazard = _frame->data[0] >> 0 & 1;
             icn.Bits.hazard=0;
         }
        
           //p.hazard = 0;
    //icons.hazard = _frame->data[0] >> 0 & 1;
    //  icons.right_blinker = _frame->data[0] >> 1 & 1;
    // icons.left_blinker = _frame->data[0] >> 2 & 1;
    // icons.engine_check = _frame->data[0] >> 3 & 1;
    // icons.oil_check = _frame->data[0] >> 4 & 1;
    // icons.abs = _frame->data[0] >> 5 & 1;
    // icons.battery = _frame->data[0] >> 6 & 1;
    // icons.seat_belt = _frame->data[1] >> 7 & 1;

    // icons.doors_open = _frame->data[1] >> 0 & 1;
    // icons.high_beam = _frame->data[1] >> 1 & 1;
    // icons.hand_break = _frame->data[1] >> 2 & 1;
    //icn.Bits.right_blinker =

    this->InstrumentCluster.setIcon(&icn);
        
        
        
            // this->InstrumentCluster.setIcon(&p);

        
        //SetIcons(_frame->data[0],_frame->data[1]);


    //      if(_frame->data[0]==4)
    // {
    //     //icons.hazard = _frame->data[0] >> 0 & 1;
    // }   
    //this->InstrumentCluster.setIcon(&icons);

        // static bool once = false;

        // if (!once) {
        //     p.hazard = 1;
        //     once = true;
        // } else
        //    p.hazard = 0;
        // QString pp = "icon1: " + QString::number(p) + "%\n"
        //                        "icon2: " + QString::number(p) + "%\n"
        //                        "icon3:" +QString::number(p)+ "%\n";
        // this->InstrumentCluster.setTXT(pp);
        //this->InstrumentCluster.setIcon(&p);
        //this->InstrumentCluster.setIcon(&p);

        break;
    }
//    case CANID::example:{
//       const struct CAN::MSG::_userin *d = reinterpret_cast<const struct CAN::MSG::_userin * >((_frame->data));
//       this->InstrumentCluster.ignite(d->IGNT);
//    }
//       break;

    // case CANID::TO_IC_FROM_EMU {
    //     //const struct CAN::MSG::Gearbx_t::_bits *d = reinterpret_cast<const struct CAN::MSG::Gearbx_t::_bits * >((_frame->data));
    //     this->InstrumentCluster.setGearPindle_int(frame->data[2]);
    //     //this->InstrumentCluster.setGear(_frame->data[2]);
    // }
    //    break;
    //case CAN::MSG::ENGINE_ID: {
    //     const struct CAN::MSG::_engine *d = reinterpret_cast<const struct CAN::MSG::_engine * >((_frame->data));
    //     //this->InstrumentCluster.ignite(d->RUN);
    //     this->InstrumentCluster.setRPM(d->RPM);
    //     this->InstrumentCluster.setSpeed(d->SPD);

    // }
    //     break;
    default:
        break;
    }

}

void yourStuff::SetIcons(uint8_t data1,uint8_t data2)
{
    


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

