#pragma once

#include <systemc.h>

class MyReadInterface : virtual public sc_interface {
public:
    virtual int read() = 0;
};

class MyWriteInterface : virtual public sc_interface {
public:
    virtual void write(int) = 0;
};