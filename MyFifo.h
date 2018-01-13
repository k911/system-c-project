#pragma once

#include <systemc.h>

#include "MyIOInterfaces.h"

class MyFifo : public sc_channel, public MyReadInterface, public MyWriteInterface {
private:
    sc_fifo<int> fifo;
    sc_event val_chg_event;

public:
    explicit MyFifo(const sc_module_name &name) : sc_channel(name), fifo("Fifo1", 16) {}

    int read() override;

    void write(int val) override;

    const sc_event &default_event() const override;
};