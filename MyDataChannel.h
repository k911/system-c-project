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

class MyDataChannel :
        public sc_prim_channel, public MyReadInterface, public MyWriteInterface {
public:
    int data{};
    sc_event val_chg_event;

    explicit MyDataChannel() : sc_prim_channel(sc_gen_unique_name("MyDataChannel")) {}

    int read() override;

    void write(int val) override;

    const sc_event &default_event() const override;

    void update() override;
};