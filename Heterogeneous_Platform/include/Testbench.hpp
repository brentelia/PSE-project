#ifndef AMS_TESTBENCH_HPP
#define AMS_TESTBENCH_HPP

#include "Controller_TLM.hpp"
#include "TLM-RTL_transactor.hpp"
#include "Xtea_RTL.hpp"
#include "RTL-AMS_transactor.hpp"
#include "Valve.hpp"
#include "Water_tank.hpp"
#include "AMS-RTL_transactor.hpp"
#include "RTL-TLM_transactor.hpp"
#include <systemc.h>
#include <systemc-ams.h>

#define PERIOD 10

class AMS_testbench: public sc_core::sc_module
{
    public:
        AMS_testbench(sc_core::sc_module_name);
        SC_HAS_PROCESS(AMS_testbench);
        sc_signal<double> threshold_rt;
        sc_signal<sc_uint<32>> word0_rt;
        sc_signal<sc_uint<32>> word1_rt;
        sc_signal<sc_uint<32>> word0_dec_rt;
        sc_signal<sc_uint<32>> word1_dec_rt;
        sca_tdf::sca_signal<double> threshold_ams;
        sca_tdf::sca_signal<sc_uint<32>> command_ams;
        sca_tdf::sca_signal<double> aperture;
        sca_tdf::sca_signal<double> water_level_ams;
        sc_signal<double> water_level_rt;

        sc_signal<sc_uint<32>> key0;
        sc_signal<sc_uint<32>> key1;
        sc_signal<sc_uint<32>> key2;
        sc_signal<sc_uint<32>> key3;
        sc_signal<sc_uint<1>> mode;
        sc_signal<bool> reset;
        sc_signal<bool> din;
        sc_signal<bool> dout;
        sc_signal<sc_logic> clock; 
        sc_out<sc_logic> clock_out;   
    // private:
        Controller controller;
        Transactor_TLM_RTL tlm_to_rtl;
        Xtea_RTL xtea;
        Transactor_RTL_AMS rtl_to_ams;
        Valve valve;
        Water_tank tank;
        Transactor_AMS_RTL ams_to_rtl;
        Transactor_RTL_TLM rtl_to_tlm;
        void clock_gen();
};

#endif