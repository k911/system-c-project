#pragma once

#include <systemc.h>
#include "MyDataChannel.h"

SC_MODULE(hardware) {
    sc_in_clk clock;
    sc_port<MyReadInterface> readChannel;

    void runSixth();

    SC_CTOR(hardware) {
        SC_METHOD(runSixth)
        sensitive << clock.pos();
    }
};