//
// Created by k911 on 1/2/18.
//

#include "Hardware.h"

void hardware::runSixth() {
    if(readChannel->read() == 6) {
        cout << "Program 6" << endl;
    }
}