#ifndef XTEA_UT_TESTBENCH_HPP
#define XTEA_UT_TESTBENCH_HPP

#include<systemc.h>
#include<tlm.h>
#include"UT_data.hpp"

class Xtea_UT_testbench : public sc_module, 
                         public virtual tlm::tlm_bw_transport_if<>
{
    private:
          void run();
    public:
        //funzioni di interfaccia
        virtual void invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range);
        virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t);
        SC_HAS_PROCESS(Xtea_UT_testbench);
        Xtea_UT_testbench(sc_module_name name);
        tlm::tlm_initiator_socket<> initiator_socket;
};
#endif