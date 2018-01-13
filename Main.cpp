#include <systemc.h>
#include "MyDataChannel.h"
#include "Hardware.h"

using namespace std;

SC_MODULE(Procesor2) {
    sc_in_clk clock;
    sc_port<MyReadInterface> readChannel;

    hardware submodule;

    SC_CTOR(Procesor2): submodule("submodule")  {
        submodule.clock(clock);
        submodule.readChannel(readChannel);

        SC_METHOD(runSecondAndError)
        sensitive << clock.pos();

        SC_METHOD(runThird)
        sensitive << clock.pos();

        SC_METHOD(runFourth)
        sensitive << clock.pos();

        SC_METHOD(runFifth)
        sensitive << clock.pos();
    }

    void runSecondAndError() {
        switch (readChannel->read()) {
            case 0:
            case 1:
            case 3:
            case 4:
            case 5:
            case 6:
                break;
            case 2:
                cout << (readChannel->running() ? "Program 2" : "Program 2 Off" ) << endl;
                break;
            default:
                cout << "Error" << endl;
                break;
        }
    }

    void runFifth() {
        if(readChannel->read() == 5) {
            cout << (readChannel->running() ? "Program 5" : "Program 5 Off" ) << endl;
        }
    }

    void runFourth() {
        if(readChannel->read() == 4) {
            cout << (readChannel->running() ? "Program 4" : "Program 4 Off" ) << endl;
        }
    }

    void runThird() {
        if(readChannel->read() == 3) {
            cout << (readChannel->running() ? "Program 3" : "Program 3 Off" ) << endl;
        }
    }
};

SC_MODULE(Procesor1) {
    sc_in_clk clock;
    sc_port<MyWriteInterface> writeChannel;
    sc_port<MyReadInterface> readChannel;
    sc_out<bool> terminate;

    SC_CTOR(Procesor1) {
        SC_THREAD(runReadWrite)
        sensitive << clock.pos();

        SC_METHOD(runFirst)
        sensitive << clock.pos();
    }

    void runFirst() {
        if(readChannel->read() == 1) {
            cout << (readChannel->running() ? "Program 1" : "Program 1 Off" ) << endl;
        }
    }

    void runReadWrite() {

        int program;
        string input;

        while(true) {
            wait();

            getline(cin, input);

            if (cin.fail() || cin.eof() || input.find_first_not_of("0123456789") != string::npos || input.empty()) {

                if (input == "quit") {
                    cout << "Terminating.." << endl;
                    writeChannel->write(0);
                    terminate->write(true);
                } else {
                    writeChannel->write(-1);
                }

                continue;
            }

            string::size_type st;
            program = stoi(input, &st);

            writeChannel->write(program);
        }
    }

};

int sc_main(int argc, char *argv[]) {
    sc_signal<bool> terminate;
    sc_signal<bool> clock;
    sc_time sc_time1 = sc_time(1.0, sc_time_unit::SC_NS);
    MyDataChannel dataChannel;

    Procesor1 taskModule1("taskModule1");
    Procesor2 taskModule2("taskModule2");

    taskModule1.clock(clock);
    taskModule1.terminate(terminate);
    taskModule1.writeChannel(dataChannel);
    taskModule1.readChannel(dataChannel);

    taskModule2.clock(clock);
    taskModule2.readChannel(dataChannel);

    sc_start(sc_time1);

    sc_trace_file *wf = sc_create_vcd_trace_file("tasks");
    sc_trace(wf, terminate, "terminate");

    while (!terminate) {
        clock = false;
        sc_start(sc_time1);
        clock = true;
        sc_start(sc_time1);
    }

    sc_close_vcd_trace_file(wf);
    return 0;
}