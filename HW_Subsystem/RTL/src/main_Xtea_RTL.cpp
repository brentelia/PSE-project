#include "Xtea_RTL_testbench.hpp"
#include "Xtea_RTL.hpp"

void logo();

int sc_main(int argc, char* argv[])
{
   // logo();
    sc_signal<sc_uint<32>> word0_pr;
    sc_signal<sc_uint<32>> word1_pr;
    sc_signal<bool> dout_rdy;
    sc_signal<sc_uint<32>> word0;
    sc_signal<sc_uint<32>> word1;
    sc_signal<sc_uint<32>> key1;
    sc_signal<sc_uint<32>> key2;
    sc_signal<sc_uint<32>> key3;
    sc_signal<sc_uint<32>> key4;
    sc_signal<sc_uint<1>> mode;
    sc_signal<bool> din_rdy;
    sc_signal<bool> reset;
    sc_signal<sc_logic> clock;

    Xtea_RTL xtea("Xtea");
    XTea_RTL_testbench testbench("Xtea_testbench");

    xtea.clock(clock);
    xtea.word0(word0);
    xtea.word1(word1);
    xtea.key1(key1);
    xtea.key2(key2);
    xtea.key3(key3);
    xtea.key4(key4);
    xtea.mode(mode);
    xtea.din_rdy(din_rdy);
    xtea.word0_pr(word0_pr);
    xtea.word1_pr(word1_pr);
    xtea.dout_rdy(dout_rdy);
    xtea.reset(reset);

    testbench.clock(clock);
    testbench.word0(word0);
    testbench.word1(word1);
    testbench.key1(key1);
    testbench.key2(key2);
    testbench.key3(key3);
    testbench.key4(key4);
    testbench.mode(mode);
    testbench.din_rdy(din_rdy);
    testbench.word0_pr(word0_pr);
    testbench.word1_pr(word1_pr);
    testbench.dout_rdy(dout_rdy);
    testbench.reset(reset);

    sc_trace_file *file=sc_create_vcd_trace_file("wave");
    file->set_time_unit(1,SC_NS);
    sc_trace(file,clock,"clock");
    sc_trace(file,reset,"reset");
    sc_trace(file,mode,"mode");
    sc_trace(file,word0,"word0");
    sc_trace(file,xtea.val1,"wor0_processed");
    sc_trace(file,word1,"wor1");
    sc_trace(file,xtea.val2,"wor1_processed");
    sc_trace(file,din_rdy,"d-in");
    sc_trace(file,dout_rdy,"d-out");
    sc_trace(file,xtea.STATUS,"Stato");
    sc_trace(file,xtea.counter,"Counter");

    sc_start();
    sc_close_vcd_trace_file(file);
    return 0;
}

void logo(){

    cout<<" .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------. \n";
    cout<<"| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n";
    cout<<"| |  ____  ____  | || |  _________   | || |  _________   | || |      __      | || |              | || |  _______     | || |  _________   | || |   _____      | |\n";
    cout<<"| | |_  _||_  _| | || | |  _   _  |  | || | |_   ___  |  | || |     /  \\     | || |              | || | |_   __ \\    | || | |  _   _  |  | || |  |_   _|     | |\n";
    cout<<"| |   \\ \\  / /   | || | |_/ | | \\_|  | || |   | |_  \\_|  | || |    / /\\ \\    | || |    ______    | || |   | |__) |   | || | |_/ | | \\_|  | || |    | |       | |\n";
    cout<<"| |    > `' <    | || |     | |      | || |   |  _|  _   | || |   / ____ \\   | || |   |______|   | || |   |  __ /    | || |     | |      | || |    | |   _   | |\n";
    cout<<"| |  _/ /'`\\ \\_  | || |    _| |_     | || |  _| |___/ |  | || | _/ /    \\ \\_ | || |              | || |  _| |  \\ \\_  | || |    _| |_     | || |   _| |__/ |  | |\n";
    cout<<"| | |____||____| | || |   |_____|    | || | |_________|  | || ||____|  |____|| || |              | || | |____| |___| | || |   |_____|    | || |  |________|  | |\n";
    cout<<"| |              | || |              | || |              | || |              | || |              | || |              | || |              | || |              | |\n";
    cout<<"| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n";
    cout<<" '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' \n";

}
