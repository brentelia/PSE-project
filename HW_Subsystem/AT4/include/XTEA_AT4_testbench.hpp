#ifndef XTEA_AT4_TESTBENCH_HPP
#define XTEA_AT4_TESTBENCH_HPP

#include<systemc.h>
#include<tlm.h>
#include <tlm_utils/tlm_quantumkeeper.h>
#include"AT4_data.hpp"

class Xtea_AT4_testbench : public sc_module, 
                         public virtual tlm::tlm_bw_transport_if<>
{
    private:
        void run();
        sc_event compute_end;
        bool is_waiting;
    public:
        //funzioni di interfaccia
        virtual void invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range);
        virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t);
        SC_HAS_PROCESS(Xtea_AT4_testbench);
        Xtea_AT4_testbench(sc_module_name name);
        tlm::tlm_initiator_socket<> initiator_socket;
};
#endif