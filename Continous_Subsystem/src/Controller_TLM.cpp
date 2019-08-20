#include "Controller_TLM.hpp"

Controller::Controller(sc_module_name name) : 
sc_module(name), target_socket("target")
{
    initiator_socket(*this);
    target_socket(*this);
    m_qk.set_global_quantum(sc_time(5, SC_MS));
    m_qk.reset();
    thrsh = 0.7;
}

void Controller::b_transport(tlm::tlm_generic_payload &trans, sc_time &t)
{
    water_level = (*((water_control *)trans.get_data_ptr())).water_level;
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
    run();
}

void Controller::run()
{
    valve_control packet;
    tlm::tlm_generic_payload payload;
    sc_time local_time = m_qk.get_local_time();
    payload.set_data_ptr((unsigned char *)&packet);
    payload.set_write();
    local_time = m_qk.get_local_time();

    if (water_level > 8.8)
    {
        thrsh *= 0.7;
        packet.command = CLOSE;
    }
    else if (water_level < 5)
    {
        thrsh *= 1.1;
        packet.command = OPEN;
    }
    else
        packet.command = IDLE;

    packet.threshold = thrsh;
    initiator_socket->b_transport(payload, local_time);
}

void Controller::invalidate_direct_mem_ptr(
    uint64 start_range,
    uint64 end_range)
{
}

tlm::tlm_sync_enum Controller::nb_transport_bw(tlm::tlm_generic_payload &trans,
                                               tlm::tlm_phase &phase,
                                               sc_time &t)
{
    return tlm::TLM_COMPLETED;
}

tlm::tlm_sync_enum Controller::nb_transport_fw(tlm::tlm_generic_payload &trans,
                                               tlm::tlm_phase &phase,
                                               sc_time &t)
{
    return tlm::TLM_COMPLETED;
}

unsigned int Controller::transport_dbg(tlm::tlm_generic_payload &trans)
{
    return 0;
}

bool Controller::get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data)
{
    return 0;
}
