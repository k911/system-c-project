//
// Created by k911 on 1/2/18.
//

#include "Hardware.h"

void hardware::runSixth() {
    if(program->read() == 6) {
        cout << (running->read() ? "Program 6" : "Program 6 Off") << endl;
    }
}