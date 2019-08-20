#ifndef XTEA_LT_HPP
#define XTEA_LT_HPP

#include <systemc.h>
#include <tlm.h>
#include "LT_data.hpp"

//socket-slave
class Xtea_LT: public sc_module, public virtual tlm::tlm_fw_transport_if<>
{
    private:

        payload_struct payload; //copia locale della struttura
        sc_uint<32> delta;

        // Vere funzioni
        void xtea_crypt();
        void xtea_dec();
        sc_time timing;

    public:
        //Porta TLM - interfaccia target
        tlm::tlm_target_socket<> target_socket; 

        //Funzione invocata dall'Initiator
        virtual void b_transport(tlm::tlm_generic_payload &trans, sc_time &t);

        //Funzioni di interfaccia non usate
        virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data);
        virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_time &t);
        virtual unsigned int transport_dbg(tlm::tlm_generic_payload &trans);

        // costruttore
        SC_HAS_PROCESS(Xtea_LT);
        Xtea_LT(sc_module_name name);
};

#endif
