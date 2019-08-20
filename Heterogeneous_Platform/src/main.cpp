#include"Valve.hpp"
#include"Water_tank.hpp"
#include<systemc.h>
#include<systemc-ams.h>
#include"Testbench.hpp"

int sc_main( int ac, char *av[] )
{
    AMS_testbench tb("testbench");

    sca_trace_file *file = sca_create_vcd_trace_file("water");
    sca_trace(file, tb.water_level_ams, "water_level");
    sca_trace(file,tb.command_ams,"comand");
    sca_trace(file,tb.aperture,"aperture");
    sca_trace(file,tb.threshold_ams,"threshold");
    sc_trace_file *fileSC=sc_create_vcd_trace_file("wave");
    fileSC->set_time_unit(1,SC_NS);
    sc_trace(fileSC,tb.clock,"clock");
    sc_trace(fileSC,tb.reset,"reset");
    sc_trace(fileSC,tb.mode,"mode");
    sc_trace(fileSC,tb.word0_rt,"word0");
    sc_trace(fileSC,tb.xtea.val1,"wor0_processed");
    sc_trace(fileSC,tb.word0_dec_rt,"word0_decr");
    sc_trace(fileSC,tb.word1_rt,"wor1");
    sc_trace(fileSC,tb.xtea.val2,"wor1_processed");
    sc_trace(fileSC,tb.word1_dec_rt,"word1_decr");
    sc_trace(fileSC,tb.din,"d-in");
    sc_trace(fileSC,tb.dout,"d-out");
    sc_trace(fileSC,tb.xtea.STATUS,"Stato");
    sc_trace(fileSC,tb.xtea.counter,"Counter");
    sc_start(1200,SC_SEC);
    sca_close_vcd_trace_file(file);

}