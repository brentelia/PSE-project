#include "Xtea_RTL_testbench.hpp"
#include <iostream>


void XTea_RTL_testbench::timeout(){
    wait(5000,SC_NS);
    cout<<"STOP\n";
    sc_stop();
}


void XTea_RTL_testbench::clock_run()
{
    while(true)
    {
        clock.write(SC_LOGIC_1);
        wait(PERIOD/2, SC_NS);  //SC_NS=nanosecondi
        clock.write(SC_LOGIC_0);
        wait(PERIOD/2, SC_NS);
    }
}

void XTea_RTL_testbench::run()
{
    reset.write(1);
    wait();
    reset.write(0);
    wait();
    cout<<"Test di codifica\n";
    mode.write(0);
    key1.write(0x6a1d78c8); 
    key2.write(0x8c86d67f); 
    key3.write(0x2a65bfbe); 
    key4.write(0xb4bd6e46); 
    cout<<"Parola 1:"<<hex<<0x12345678<<"\n";
    word0.write(0x12345678);
    cout<<"Parola 1:"<<hex<<0x9abcdeff<<"\n";
    word1.write(0x9abcdeff);
    din_rdy.write(1);
    wait();
    din_rdy.write(0);
    while(dout_rdy.read()!=1) wait();

    if((word0_pr.read() != 0x99bbb92b) || (word1_pr.read() != 0x3ebd1644)){
        cout<<"Risultato sbagliato:\n";
        cout<<hex<<word0_pr.read()<<" =/="<<0x99bbb92b<<"\n";
        cout<<hex<<word1_pr.read()<<" =/="<<0x3ebd1644<<"\n";
    }
    else {
        cout<<"Test terminato con successo:\n";
        cout<<hex<<0x12345678<<"-->"<<word0_pr.read()<<"\n";
        cout<<hex<<0x9abcdeff<<"-->"<<word1_pr.read()<<"\n";
    }
    cout<<"Test di decodifica\n";
    
    mode.write(1);
    key1.write(0x6a1d78c8); 
    key2.write(0x8c86d67f); 
    key3.write(0x2a65bfbe); 
    key4.write(0xb4bd6e46); 
    reset.write(0);
    cout<<"Parola 1:"<<hex<<word0_pr.read()<<"\n";
    word0.write(word0_pr.read());
    cout<<"Parola 1:"<<hex<<word1_pr.read()<<"\n";
    word1.write(word1_pr.read());
    din_rdy.write(1);
    wait();
    din_rdy.write(0);
    while(dout_rdy.read()!=1) wait();

    if((word0_pr.read() != 0x12345678) || (word1_pr.read() != 0x9abcdeff)){
        cout<<"Risultato sbagliato:\n";
        cout<<hex<<word0_pr.read()<<" =/="<<0x12345678<<"\n";
        cout<<hex<<word1_pr.read()<<" =/="<<0x9abcdeff<<"\n";
    }
    else {
        cout<<"Test terminato con successo\n";
        cout<<hex<<word0.read()<<"-->"<<word0_pr.read()<<"\n";
        cout<<hex<<word1.read()<<"-->"<<word1_pr.read()<<"\n";

    }
    reset.write(1);
    din_rdy.write(0);
    word0.write(0);
    word1.write(0);

    sc_stop();
}


