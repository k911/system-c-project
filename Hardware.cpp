//
// Created by k911 on 1/2/18.
//

#include "Hardware.h"

void hardware::runSixth() {
    if(readChannel->read() == 6) {
        cout << (readChannel->running() ? "Program 6" : "Program 6 Off" ) << endl;
    }
}