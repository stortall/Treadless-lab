#include <iostream>
#include "cluster_updater.h"

void ClusterUpdater::setIcon(const  _icons * icons) {

    ValueSource->setProperty("abs", QVariant( static_cast<unsigned>(icons->Bits.abs)));    
    ValueSource->setProperty("battery", QVariant( static_cast<unsigned>(icons->Bits.battery)));
    ValueSource->setProperty("high_beam", QVariant( static_cast<unsigned>(icons->Bits.high_beam)));
    ValueSource->setProperty("oil_check", QVariant( static_cast<unsigned>(icons->Bits.oil_check)));
    ValueSource->setProperty("seat_belt", QVariant( static_cast<unsigned>(icons->Bits.seat_belt)));
    ValueSource->setProperty("hand_break", QVariant( static_cast<unsigned>(icons->Bits.hand_break)));
    ValueSource->setProperty("doors_open", QVariant( static_cast<unsigned>(icons->Bits.doors_open)));
    ValueSource->setProperty("engine_check", QVariant( static_cast<unsigned>(icons->Bits.engine_check)));
    this->checkHazard(icons);
}

void ClusterUpdater::checkHazard(const _icons * icons) {
    std::cout << "setting hazard to " << (int) icons->Bits.hazard << std::endl;
    if ((int)icons->Bits.hazard) {
        ValueSource->setProperty("left_blinker", QVariant( false ));
        ValueSource->setProperty("right_blinker",  QVariant( false ));
        ValueSource->setProperty("left_blinker", QVariant( true ));
        ValueSource->setProperty("right_blinker",  QVariant( true ));
    } else {
        ValueSource->setProperty("left_blinker", QVariant( static_cast<unsigned>(icons->Bits.left_blinker)));
        ValueSource->setProperty("right_blinker",  QVariant( static_cast<unsigned>(icons->Bits.right_blinker)));
    }

}

