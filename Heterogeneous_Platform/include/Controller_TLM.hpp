#ifndef CONTROLLER_TLM_HPP
#define CONTROLLER_TLM_HPP
#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/tlm_quantumkeeper.h>
#include "valve_control.hpp"
#include "water_control.hpp"
#include"Commands.hpp"

class Controller :  public sc_module,public virtual tlm::tlm_bw_transport_if<>,
                    tlm::tlm_fw_transport_if<>
{
    public:
        double thrsh;
        double water_level;

        SC_HAS_PROCESS( Controller );
        virtual void invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range);
        virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t);
                //Funzione invocata dall'Initiator
        virtual void b_transport(tlm::tlm_generic_payload &trans, sc_time &t);

        //Funzioni di interfaccia non usate
        virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data);
        virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_time &t);
        virtual unsigned int transport_dbg(tlm::tlm_generic_payload &trans);


        void run();
        void xtea_cyp(int command);

        tlm_utils::tlm_quantumkeeper m_qk;

        tlm::tlm_initiator_socket<> initiator_socket;
        tlm::tlm_target_socket<> target_socket;
        Controller( sc_module_name name,
                    sc_uint<32> key0,
                    sc_uint<32> key1,
                    sc_uint<32> key2,
                    sc_uint<32> key3,
                    sc_uint<32> delta);

    private:
        sc_time timing;
        sc_uint<32> word0;
        sc_uint<32> word1;
        sc_uint<32> key0;
        sc_uint<32> key1;
        sc_uint<32> key2;
        sc_uint<32> key3;
        sc_uint<32> delta;


};  
#endif