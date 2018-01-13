#include <systemc.h>
#include "MyFifo.h"
#include "Hardware.h"

using namespace std;

SC_MODULE(Procesor2) {
    sc_in_clk clock;
    sc_port<MyReadInterface> readChannel;
    sc_signal<sc_int<4>> program;
    sc_signal<sc_int<4>> running;

    hardware submodule;

    SC_CTOR(Procesor2) : submodule("submodule") {
        program.write(0);
        running.write(0);
        submodule.clock(clock);
        submodule.program(program);
        submodule.running(running);

        SC_THREAD(runSecondAndError)
        sensitive << clock.pos();

        SC_METHOD(runThird)
        sensitive << clock.pos();

        SC_METHOD(runFourth)
        sensitive << clock.pos();

        SC_METHOD(runFifth)
        sensitive << clock.pos();
    }

    void runSecondAndError() {
        int val, programWrite, runningWrite;
        while (true) {

            val = readChannel->read();
            if (running.read() == val) {
                programWrite = val;
                runningWrite = 0;
            } else if (running.read() == 0 && val != -1) {
                programWrite = val;
                runningWrite = val;
            } else {
                programWrite = -1;
                runningWrite = 0;
            }

            // Write state
            program.write(programWrite);
            running.write(runningWrite);

            // Handle program 2 and error
            switch (programWrite) {
                case 0:
                case 1:
                case 3:
                case 4:
                case 5:
                case 6:
                    break;
                case 2:
                    cout << (runningWrite ? "Program 2" : "Program 2 Off") << endl;
                    break;
                default:
                    cout << "Error" << endl;
                    break;
            }
        }
    }

    void runFifth() {
        if (program.read() == 5) {
            cout << (running.read() ? "Program 5" : "Program 5 Off") << endl;
        }
    }

    void runFourth() {
        if (program.read() == 4) {
            cout << (running.read() ? "Program 4" : "Program 4 Off") << endl;
        }
    }

    void runThird() {
        if (program.read() == 3) {
            cout << (running.read() ? "Program 3" : "Program 3 Off") << endl;
        }
    }
};

SC_MODULE(Procesor1) {
    sc_in_clk clock;
    sc_port<MyWriteInterface> writeChannel;
    sc_out<bool> terminate;
    sc_signal<sc_int<4>> program;

    SC_CTOR(Procesor1) {
        program.write(0);

        SC_THREAD(runReadWrite)
        sensitive << clock.pos();

        SC_THREAD(runFirst)
        sensitive << clock.pos();
    }

    void runFirst() {
        long running = 0;
        while (true) {
            wait();
            long val = program.read();

            if (running == val) {
                running = 0;
            } else if (running == 0 && val != -1) {
                running = val;
            } else {
                val = -1;
                running = 0;
            }


            if (val == 1) {
                cout << (running ? "Program 1" : "Program 1 Off") << endl;
            }
        }
    }

    void runReadWrite() {

        int val;
        string input;

        while (true) {
            wait();

            getline(cin, input);

            if (cin.fail() || cin.eof() || input.find_first_not_of("0123456789") != string::npos || input.empty()) {

                if (input == "quit") {
                    cout << "Terminating.." << endl;
                    program.write(0);
                    writeChannel->write(0);
                    terminate->write(true);
                } else {
                    program.write(-1);
                    writeChannel->write(-1);
                }

                continue;
            }

            string::size_type st;
            val = stoi(input, &st);
            if(val > 6) {
                val = -1;
            }
            program.write(val);
            writeChannel->write(val);
        }
    }

};

int sc_main(int argc, char *argv[]) {
    sc_signal<bool> terminate;
    sc_signal<bool> clock;
    sc_time sc_time1 = sc_time(1.0, sc_time_unit::SC_NS);
    MyFifo dataChannel("fifo1");

    Procesor1 taskModule1("taskModule1");
    Procesor2 taskModule2("taskModule2");

    taskModule1.clock(clock);
    taskModule1.terminate(terminate);
    taskModule1.writeChannel(dataChannel);
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