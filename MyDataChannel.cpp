#include "MyDataChannel.h"


int MyDataChannel::read() {
    return data;
}

int MyDataChannel::running() {
    return runningProgram;
}

void MyDataChannel::write(int val) {


    if(runningProgram == val) {
//        cout << "stop program" << val << endl;
        runningProgram = 0;
        data = val;
    } else if (runningProgram == 0 && val != -1) {
//        cout << "run program" << val << endl;
        runningProgram = val;
        data = val;
    } else {
//        cout << "error program" << val << endl;
        data = -1;
        runningProgram = 0;
    }

    request_update();
}

const sc_event &MyDataChannel::default_event() const {
    return val_chg_event;
}

void MyDataChannel::update() {
    val_chg_event.notify(SC_ZERO_TIME);
}