#ifndef Xtea_RTL_HPP
#define XTea_RTL_HPP

#include <systemc.h>

SC_MODULE(Xtea_RTL)
{
    public:
        sc_in<sc_uint<32>> word0;
        sc_in<sc_uint<32>> word1;
        
        sc_in<sc_uint<32>> key1;
        sc_in<sc_uint<32>> key2;
        sc_in<sc_uint<32>> key3;
        sc_in<sc_uint<32>> key4;

        sc_in<sc_uint<1>> mode;
        sc_in<bool> din_rdy;
        sc_in<bool> reset;
        
        sc_in<sc_logic > clock;

        sc_out<sc_uint<32>> word0_pr;
        sc_out<sc_uint<32>> word1_pr;
        sc_out<bool> dout_rdy;

        SC_CTOR(Xtea_RTL){
            
            SC_METHOD(fsm);
            sensitive <<STATUS<<din_rdy;
            
            SC_METHOD(datapath);
            sensitive <<clock.pos();
            sensitive<<reset.pos();
//            sensitive<<din_rdy;


        };
      
        sc_signal<sc_uint<5>> counter;
        sc_signal<sc_uint<32>> val1;
        sc_signal<sc_uint<32>> val2;
        sc_signal<sc_uint<32>> delta;
        sc_signal<sc_uint<32>> k1;
        sc_signal<sc_uint<32>> k2;
        sc_signal<sc_uint<32>> k3;
        sc_signal<sc_uint<32>> k4;
        sc_signal<sc_uint<64>> sum;
        typedef enum 
        {
            START,
            IDLE,
            FETCH,
            CFR_WORD_1,
            DECFR,
            DCF_WORD_1,
            CFR_WORD_2,
            DCF_WORD_2,
            END
        } STATES;
        sc_signal<int> STATUS, NEXT_STATUS;
        void fsm();
        void datapath();
};
#endif