#ifndef AMS_TESTBENCH_HPP
#define AMS_TESTBENCH_HPP

#include "Controller_TLM.hpp"
#include "TLM-RTL_transactor.hpp"
#include "RTL-AMS_transactor.hpp"
#include "Valve.hpp"
#include "Water_tank.hpp"
#include "AMS-RTL_transactor.hpp"
#include "RTL-TLM_transactor.hpp"
#include <systemc.h>
#include <systemc-ams.h>

class AMS_testbench: public sc_core::sc_module
{
    public:
        AMS_testbench(sc_core::sc_module_name);
        
        sc_signal<double> threshold_rt;
        sc_signal<int> command_rt;
        sca_tdf::sca_signal<double> threshold_ams;
        sca_tdf::sca_signal<int> command_ams;
        sca_tdf::sca_signal<double> aperture;
        sca_tdf::sca_signal<double> water_level_ams;
        sc_signal<double> water_level_rt;
    
    private:
        Controller controller;
        Transactor_TLM_RTL tlm_to_rtl;
        Transactor_RTL_AMS rtl_to_ams;
        Valve valve;
        Water_tank tank;
        Transactor_AMS_RTL ams_to_rtl;
        Transactor_RTL_TLM rtl_to_tlm;
};

#endif