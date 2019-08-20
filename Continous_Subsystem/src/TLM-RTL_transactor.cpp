#include "TLM-RTL_transactor.hpp"

Transactor_TLM_RTL::Transactor_TLM_RTL(sc_module_name name) : 
    sc_module(name),
    target_socket("target_socket")
{
    target_socket(*this);
}

void Transactor_TLM_RTL::b_transport(tlm::tlm_generic_payload &trans, sc_time &t)
{
 //   cout<<"[TRANSATTORE RTL:] inizio traduzione"<<endl;
    valve_commands = *((valve_control *)trans.get_data_ptr());
    transduce();
}

void Transactor_TLM_RTL::transduce()
{
    //cout<<"[TRANSATTORE RTL:] Scrittura segnali"<<endl;
    command.write(valve_commands.command);
    threshold.write(valve_commands.threshold);
}

bool Transactor_TLM_RTL::get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data)
{
    return false;
}

tlm::tlm_sync_enum Transactor_TLM_RTL::nb_transport_fw(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_time &t)
{
    return tlm::TLM_COMPLETED;
}

unsigned int Transactor_TLM_RTL::transport_dbg(tlm::tlm_generic_payload &trans)
{
    return 0;
}

