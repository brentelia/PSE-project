#include"XTEA_LT_testbench.hpp"


Xtea_LT_testbench::Xtea_LT_testbench(sc_module_name name): sc_module(name)
{
    initiator_socket(*this);
    SC_THREAD(run);
    decoupling.set_global_quantum(sc_time(680,SC_NS));
    decoupling.reset();
}

void Xtea_LT_testbench::run(){
    cout<<"[TESTBECH:] TEMPO:"<<sc_time_stamp()<<endl;
    sc_time time=decoupling.get_local_time();
    payload_struct data;
    tlm::tlm_generic_payload payload;

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

    time=decoupling.get_local_time();
    
    initiator_socket->b_transport(payload,time);
    if(payload.get_response_status()==tlm::TLM_OK_RESPONSE){
        if((data.result0 != 0x99bbb92b) || (data.result1 != 0x3ebd1644))
            cout<<"[TESTBENCH:] RISULATO ERRATO: "<<endl;
        else cout<<"[TESTBENCH:] RISULTATO CORRETTO"<<endl;
        cout<<"[TESTBENCH:] "<<data.word0 <<"<->"<<hex<< data.result0<<endl;
        cout<<"[TESTBENCH:] "<<data.word1 <<"<->"<<hex<< data.result1<<endl;
    }

    cout << "[TESTBECH:] Tempo attuale: " << sc_time_stamp() << " + " << time << endl;
    decoupling.set(time);
    if(decoupling.need_sync()){
        cout<<"[TESTBENCH:] SINCRONIZZAZIONE"<<endl;
        decoupling.sync();
        cout<<"------------"<<endl;
    }

    cout<<"[TESTBENCH:] Richiesta di decifratura "<<endl;
    data.word0 = data.result0; 
    data.word1 = data.result1; 
    payload.set_read();

    time=decoupling.get_local_time();

    initiator_socket->b_transport(payload,time);
    if(payload.get_response_status()==tlm::TLM_OK_RESPONSE){
        if((data.result0 != 0x12345678) || (data.result1 != 0x9abcdeff))
            cout<<"[TESTBENCH:] RISULATO ERRATO: "<<endl;
        else cout<<"[TESTBENCH:] RISULTATO CORRETTO"<<endl;
        cout<<"[TESTBENCH:] "<<data.word0 <<"<->"<<hex<< data.result0<<endl;
        cout<<"[TESTBENCH:] "<<data.word1 <<"<->"<<hex<< data.result1<<endl;

    }
    cout << "[TESTBECH:] Tempo attuale: " << sc_time_stamp() << " + " << time << endl;
    decoupling.set(time);
    if(decoupling.need_sync()){
        cout<<"[TESTBENCH:] SINCRONIZZAZIONE"<<endl;
        decoupling.sync();
        cout<<"------------"<<endl;
    }

    cout<<"[TESTBENCH:] SIMULAZIONE TERMINATA"<<endl;
    sc_stop();   
   
}

//metodo di interfaccia non usato
void Xtea_LT_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{}

//metodo di interfaccia non usato
tlm::tlm_sync_enum Xtea_LT_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
  return tlm::TLM_COMPLETED;
}