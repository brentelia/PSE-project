#ifndef VALVE_HPP
#define VALVE_HPP

#include<systemc.h>
#include<systemc-ams.h>
#include"Commands.hpp"

SCA_TDF_MODULE(Valve)
{
    private:
        double current_aperture;
    public:
        sca_tdf::sca_in<sc_uint<32>> command;
        sca_tdf::sca_in<double> threshold;
        sca_tdf::sca_out<double> aperture;
        Valve(sc_core::sc_module_name name);
        void set_attributes();
        void processing();
};

#endif 