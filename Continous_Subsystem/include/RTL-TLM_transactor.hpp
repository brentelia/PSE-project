#ifndef TRANSACTOR_RTL_TLM_HPP
#define TRANSACTOR_RTL_TLM_HPP

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/tlm_quantumkeeper.h>
#include "water_control.hpp"

class Transactor_RTL_TLM :
  public sc_module,
  public virtual tlm::tlm_bw_transport_if<>
{
    public:
        tlm::tlm_initiator_socket<> initiator_socket;
        virtual void invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range);
        virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t);

        SC_HAS_PROCESS(Transactor_RTL_TLM);
        Transactor_RTL_TLM(sc_module_name name);

        // RTL Interface
        sc_in<double> water_level_rt;
    private:
        tlm_utils::tlm_quantumkeeper m_qk;
        void transduce();
        void run();
};

#endif 