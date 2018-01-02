#include "MyDataChannel.h"


int MyDataChannel::read() {
    return data;
}

void MyDataChannel::write(int val) {
    data = val;
    request_update();
}

const sc_event &MyDataChannel::default_event() const {
    return val_chg_event;
}

void MyDataChannel::update() {
    val_chg_event.notify(SC_ZERO_TIME);
}