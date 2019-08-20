#ifndef AT4_DATA_HPP
#define AT4_DATA_HPP

#include <systemc.h>

//DATI DA TRASPORTARE -> MEGLIO DEFINIRE STRUCT 

struct payload_struct {
    sc_uint<32> word0;
    sc_uint<32> word1;
    sc_uint<32> result0;
    sc_uint<32> result1;
    sc_uint<32> key0;
    sc_uint<32> key1;
    sc_uint<32> key2;
    sc_uint<32> key3;

};

#endif
