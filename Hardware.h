#pragma once

#include <systemc.h>

SC_MODULE(hardware) {
    sc_in_clk clock;
    sc_in<sc_int<4>> program;
    sc_in<sc_int<4>> running;

    void runSixth();

    SC_CTOR(hardware) {
        SC_METHOD(runSixth)
        sensitive << clock.pos();
    }
};