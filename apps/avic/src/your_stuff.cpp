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
    const double temp = 30;
    const double oil_temp =50;
    const double fuel_level =80;
    const double fake_rpm=1500;

}// namespace CANID


void yourStuff::YouHaveJustRecievedACANFrame(const canfd_frame * const _frame) {
   
    switch (_frame->can_id) {
    case CANID::TO_IC_FROM_EMU: {
        this->InstrumentCluster.setSpeed(_frame->data[0]);
    QString accbrakegear = "Friction Resistance on the vehicle:" + QString::number(_frame->data[4],10)+ "\n";
        this->InstrumentCluster.setTXT(accbrakegear);

        this->InstrumentCluster.setRPM((_frame->data[1])*25);
        this->InstrumentCluster.setGear(_frame->data[2]);
        int gear_shifter_state = 0;
        if (_frame->data[3] == 'P') {
            gear_shifter_state = 0;
            x=0;
        } else if (_frame->data[3] == 'N') {
            gear_shifter_state = 1;
            x+10;
        } else if (_frame->data[3] == 'D') {
            gear_shifter_state = 3;
            x+50;
        }
        this->InstrumentCluster.setGearPindle_int(gear_shifter_state);

        this->InstrumentCluster.setOilTemperatureGauges(CANID::oil_temp);
        this->InstrumentCluster.setTemperatureGauges(CANID::temp);
        this->InstrumentCluster.setFuelGauges(CANID::fuel_level);
            if (double(((_frame->data[1])*25))>(CANID::fake_rpm))
        {
            this->InstrumentCluster.setFuelGauges((CANID::fuel_level-10));
            this->InstrumentCluster.setOilTemperatureGauges(CANID::oil_temp+10);
             this->InstrumentCluster.setTemperatureGauges(CANID::temp+10);

        }
        if(_frame->data[3] == 'N'||_frame->data[3] == 'D')
        {
          this->InstrumentCluster.ignite(1);
        }
        else
          {this->InstrumentCluster.ignite(0);
            this->InstrumentCluster.setOilTemperatureGauges(0);
        this->InstrumentCluster.setTemperatureGauges(0);
        this->InstrumentCluster.setFuelGauges(0);
          }
        break;
    }
    case CANID::ICONS: {
       Iconss_t icn;
       icn.Data[0] =_frame->data[0];
       icn.Data[1] =_frame->data[1];
    this->InstrumentCluster.setOilTemperatureGauges(CANID::oil_temp);
    QString accbrakegear = "Friction Resistance on the vehicle:" + QString::number(_frame->data[4],10)+ "\n";
        this->InstrumentCluster.setTXT(accbrakegear);
    this->InstrumentCluster.setTemperatureGauges(CANID::temp);
    this->InstrumentCluster.setFuelGauges(CANID::fuel_level);

            if (double(((_frame->data[1])*25))>(CANID::fake_rpm))
        {
            this->InstrumentCluster.setFuelGauges((CANID::fuel_level-10));
            this->InstrumentCluster.setOilTemperatureGauges(CANID::oil_temp+10);
            this->InstrumentCluster.setTemperatureGauges(CANID::temp+10);


        }

        if(_frame->data[3] == 'N'||_frame->data[3] == 'D')
        {
          this->InstrumentCluster.ignite(1);
        }
        else
          {this->InstrumentCluster.setOilTemperatureGauges(CANID::oil_temp);
        this->InstrumentCluster.setTemperatureGauges(CANID::temp);
        this->InstrumentCluster.setFuelGauges(CANID::fuel_level);}
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

