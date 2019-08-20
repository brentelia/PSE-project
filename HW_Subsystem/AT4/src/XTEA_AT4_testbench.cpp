#include"XTEA_AT4_testbench.hpp"

Xtea_AT4_testbench::Xtea_AT4_testbench(sc_module_name name): 
    sc_module(name),
    is_waiting(false)
{
    initiator_socket(*this);
    SC_THREAD(run);
}

void Xtea_AT4_testbench::run(){

    payload_struct data;
    tlm::tlm_generic_payload payload;
    sc_time time=SC_ZERO_TIME;
    tlm::tlm_phase phase=tlm::BEGIN_REQ;

    data.key0 = 0x6a1d78c8; 
    data.key1 = 0x8c86d67f; 
    data.key2 = 0x2a65bfbe; 
    data.key3 = 0xb4bd6e46; 

    data.word0 = 0x12345678; 
    data.word1 = 0x9abcdeff; 

    cout<<"[TESTBECH:] Richiesta di cifratura "<<endl;
    payload.set_data_ptr((unsigned char*)&data);
    payload.set_address(0);
    payload.set_write();

    
    tlm::tlm_sync_enum fw_result=initiator_socket->nb_transport_fw(payload,phase,time);
    //Avanti in parallelo, controllo di eventuali errori ritornati

    if(fw_result==tlm::TLM_COMPLETED||phase!=tlm::END_REQ){
        cout<<"[TESTBENCH:] ERRORE: Transazione non risuscita o fase non corretta"<<endl;
        sc_stop();
    }

    cout<<"[TESTBENCH:] In attesa di risposta"<<endl;
    
    is_waiting=true;

    wait(compute_end);

    is_waiting=false;

    if(payload.get_response_status()==tlm::TLM_OK_RESPONSE){
        if((data.result0 != 0x99bbb92b) || (data.result1 != 0x3ebd1644))
            cout<<"[TESTBENCH:] RISULATO ERRATO: "<<endl;
        else cout<<"[TESTBENCH:] RISULTATO CORRETTO"<<endl;
        cout<<"[TESTBENCH:] "<<data.word0 <<"<->"<<hex<< data.result0<<endl;
        cout<<"[TESTBENCH:] "<<data.word1 <<"<->"<<hex<< data.result1<<endl;
    }


    cout<<"[TESTBENCH:] Richiesta di decifratura "<<endl;
    data.word0 = data.result0; 
    data.word1 = data.result1; 
    payload.set_read();
    phase=tlm::BEGIN_REQ;

    
    fw_result=initiator_socket->nb_transport_fw(payload,phase,time);
    //Avanti in parallelo, controllo di eventuali errori ritornati

    if(fw_result==tlm::TLM_COMPLETED||phase!=tlm::END_REQ){
        cout<<"[TESTBENCH:] ERRORE: Transazione non risuscita o fase non corretta"<<endl;
        sc_stop();
    }

    cout<<"[TESTBENCH:] In attesa di risposta"<<endl;
    
    is_waiting=true;

    wait(compute_end);

    is_waiting=false;

    if(payload.get_response_status()==tlm::TLM_OK_RESPONSE){
        if((data.result0 != 0x12345678) || (data.result1 != 0x9abcdeff))
            cout<<"[TESTBENCH:] RISULATO ERRATO: "<<endl;
        else cout<<"[TESTBENCH:] RISULTATO CORRETTO"<<endl;
        cout<<"[TESTBENCH:] "<<data.word0 <<"<->"<<hex<< data.result0<<endl;
        cout<<"[TESTBENCH:] "<<data.word1 <<"<->"<<hex<< data.result1<<endl;

    }
    cout<<"[TESTBENCH:] SIMULAZIONE TERMINATA"<<endl;
    sc_stop();   
   
}

tlm::tlm_sync_enum Xtea_AT4_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
    if(!is_waiting){//chiamata con waiting a false
        cout<<"[TESTBENCH:] ERRORE: Ricevuta chiamata si sblocco ma senza che vi fosse una risposta da attendere"<<endl;
        trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return tlm::TLM_COMPLETED;
    }
    if(phase!=tlm::BEGIN_RESP){
        cout<<"[TESTBENCH:] ERRORE: fase non corretta"<<endl;        
        trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return tlm::TLM_COMPLETED;    
    }
    compute_end.notify();
    phase=tlm::END_RESP;
    cout<<"[TESTBENCH:] Fase di risposta terminata"<<endl;        
    return tlm::TLM_COMPLETED;
}

//metodo di interfaccia non usato
void Xtea_AT4_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{}
