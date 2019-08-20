#include"XTEA_UT.hpp"

Xtea_UT::Xtea_UT(sc_module_name name):sc_module(name),
    target_socket("target"),
    delta(0x9e3779b9)
{
    target_socket(*this);
}

void Xtea_UT::b_transport(tlm::tlm_generic_payload& trans, sc_time& t)
{
    payload = *((payload_struct*)trans.get_data_ptr());
    if(trans.is_write()){ //Scrittura = cifratura
        cout<<"\t\t[XTEA_UT:] Ricevuta richiesta di cifratura"<<endl;
        xtea_crypt();
        cout<<"\t\t[XTEA_UT:] Criptazione finita con valori:"<<hex<<payload.result0
            <<" "<<hex<<payload.result1<<endl;
        *((payload_struct*)trans.get_data_ptr()) = payload;
        cout<<"\t\t[XTEA_UT:] Ritorno valori all'Initiator"<<endl;
        trans.set_response_status(tlm::TLM_OK_RESPONSE);
    }
    else if (trans.is_read()) //Lettura = decifratura
    {
        cout<<"\t\t[XTEA_UT:] Ricevuta richiesta di decifratura"<<endl;
        xtea_dec();
        cout<<"\t\t[XTEA_UT:] Decriptazione finita con valori:"<<hex<<payload.result0
            <<" "<<hex<<payload.result1<<endl;
        *((payload_struct*)trans.get_data_ptr()) = payload;
        cout<<"\t\t[XTEA_UT:] Ritorno valori all'Initiator"<<endl;
        trans.set_response_status(tlm::TLM_OK_RESPONSE);
    }
}
    
void Xtea_UT::xtea_crypt(){
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

void Xtea_UT::xtea_dec(){
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

bool Xtea_UT::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
    return false;
}

tlm::tlm_sync_enum Xtea_UT::nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t)
{
    return tlm::TLM_COMPLETED;
}

unsigned int Xtea_UT::transport_dbg(tlm::tlm_generic_payload& trans)
{
    return 0;
}