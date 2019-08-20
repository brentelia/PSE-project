#ifndef XTea_RTL_testbench_HPP

#define XTea_RTL_testbench_HPP

#define PERIOD 10

#include <systemc.h>

SC_MODULE (XTea_RTL_testbench)
{
    public:
        sc_in<sc_uint<32>> word0_pr;
        sc_in<sc_uint<32>> word1_pr;
        sc_in<bool> dout_rdy;

        sc_out<sc_uint<32>> word0;
        sc_out<sc_uint<32>> word1;
        sc_out<sc_uint<32>> key1;
        sc_out<sc_uint<32>> key2;
        sc_out<sc_uint<32>> key3;
        sc_out<sc_uint<32>> key4;

        sc_out<sc_uint<1>> mode;
        sc_out<bool> din_rdy;
        sc_out<bool> reset;
        
        sc_out<sc_logic > clock;
        SC_CTOR(XTea_RTL_testbench){

            SC_THREAD(clock_run);

            SC_THREAD(run);
            sensitive<<clock.pos();

            SC_THREAD(timeout);

        };
    
    protected:
        sc_signal<sc_uint<32>> res0;
        sc_signal<sc_uint<32>> res1;
        void run();
        void clock_run();    
        void timeout();
};

#endif