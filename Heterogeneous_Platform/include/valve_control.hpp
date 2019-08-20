#ifndef VALVE_CONTROLE_HP
#define VALVE_CONTROLE_HP

#include <systemc.h>


struct valve_control {
    sc_uint<32> word0;
    sc_uint<32> word1;
    sc_uint<32> key0;
    sc_uint<32> key1;
    sc_uint<32> key2;
    sc_uint<32> key3;
    double threshold;
};

#endif
