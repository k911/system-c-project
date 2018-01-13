#include "MyFifo.h"


int MyFifo::read() {
    return fifo.read();
}

void MyFifo::write(int val) {
    fifo.write(val);
}

const sc_event &MyFifo::default_event() const {
    return val_chg_event;
}