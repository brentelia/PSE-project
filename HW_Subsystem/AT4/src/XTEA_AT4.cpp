#include"XTEA_AT4.hpp"

Xtea_AT4::Xtea_AT4(sc_module_name name):sc_module(name),
    target_socket("target"),
    delta(0x9e3779b9),
    actual_transaction(nullptr)
{
    target_socket(*this);
    SC_THREAD(compute_process);
}

tlm::tlm_sync_enum Xtea_AT4::nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t)
{
    if(actual_transaction!= nullptr || phase!= tlm::BEGIN_REQ){
        cout<<"\t\t[XTEA_AT4:] Impossibile eseguire richiesta"<<endl;
        trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return tlm::TLM_COMPLETED;
    }

    cout<<"\t\t[XTEA_AT4:] Richiesta accettata, inizio calcolo..."<<endl;
    actual_transaction= &trans;
    payload = *((payload_struct*)trans.get_data_ptr());
    phase=tlm::END_REQ;
    compute_event.notify();
    cout<<"\t\t[XTEA_AT4:] Primitiva terminata, in attesa del risultato"<<endl;
    return tlm::TLM_UPDATED;
}

void Xtea_AT4::compute_process(){
    sc_time time;
    while(1){
        wait(compute_event);
        cout<<"\t\t[XTEA_AT4:] Attivazione processo di calcolo"<<endl;
        wait(670,SC_NS);
        if(actual_transaction->is_write()){ //Scrittura = cifratura
        cout<<"\t\t[XTEA_AT4:] Ricevuta richiesta di cifratura"<<endl;
        xtea_crypt();
        cout<<"\t\t[XTEA_AT4:] Criptazione finita con valori:"<<hex<<payload.result0
            <<" "<<hex<<payload.result1<<endl;
        *((payload_struct*)actual_transaction->get_data_ptr()) = payload;
        cout<<"\t\t[XTEA_AT4]: Ritorno valori all'Initiator"<<endl;
        actual_transaction->set_response_status(tlm::TLM_OK_RESPONSE);
        }
        else if (actual_transaction->is_read()) //Lettura = decifratura
        {
            cout<<"\t\t[XTEA_AT4:] Ricevuta richiesta di decifratura"<<endl;
            xtea_dec();
            cout<<"\t\t[XTEA_AT4:] Decriptazione finita con valori:"<<hex<<payload.result0
                <<" "<<hex<<payload.result1<<endl;
            *((payload_struct*)actual_transaction->get_data_ptr()) = payload;
            cout<<"\t\t[XTEA_AT4: Ritorno valori all'Initiator"<<endl;
            actual_transaction->set_response_status(tlm::TLM_OK_RESPONSE);
        }
        cout<<"\t\t[XTEA_AT4:] Inizio fase di risposta"<<endl;
        tlm::tlm_phase phase=tlm::BEGIN_RESP;
        target_socket->nb_transport_bw(*actual_transaction,phase,time);
        actual_transaction=nullptr;
    }
}
    
void Xtea_AT4::xtea_crypt(){
    sc_uint<64> sum=0; 
    sc_uint<32>v0, v1, temp;
    sc_uint<6>i;
    v0 = payload.word0;
    v1 = payload.word1; 
    for (i=0; i < 32; i++) {     
        if((sum & 3) == 0) 
            temp = payload.key0;
        else if((sum & 3) == 1) 
            temp = payload.key1;
        else if ((sum & 3) == 2)
            temp = payload.key2; 
        else temp = payload.key3; 
        v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + temp);
        sum += delta;
        if(((sum>>11) & 3) == 0) 
            temp = payload.key0;
        else if(((sum>>11) & 3) == 1) 
            temp = payload.key1;
        else if (((sum>>11) & 3) == 2)
            temp = payload.key2; 
        else temp = payload.key3; 
        v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + temp);
    }
    payload.result0=v0;
    payload.result1=v1; 
}

void Xtea_AT4::xtea_dec(){
    sc_uint<64> sum=0; 
    sc_uint<32>v0, v1, temp;
    sc_uint<6>i;
    v0 = payload.word0;
    v1 = payload.word1; 
    sum = delta*32;     
    for (i=0; i<32; i++) {      
        if(((sum>>11) & 3) == 0) 
            temp = payload.key0;
        else if(((sum>>11) & 3) == 1) 
            temp = payload.key1;
        else if (((sum>>11) & 3) == 2)
             temp = payload.key2; 
        else temp = payload.key3;  
        v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + temp);
        sum -= delta;                         
        if((sum & 3) == 0) 
          temp = payload.key0;
        else if((sum & 3) == 1) 
          temp = payload.key1;
        else if ((sum & 3) == 2)
         temp = payload.key2; 
        else temp = payload.key3; 
        v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + temp);
    }
    payload.result0=v0;
    payload.result1=v1;
}

bool Xtea_AT4::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
    return false;
}

void Xtea_AT4::b_transport(tlm::tlm_generic_payload& trans, sc_time& t)
{
}

unsigned int Xtea_AT4::transport_dbg(tlm::tlm_generic_payload& trans)
{
    return 0;
}