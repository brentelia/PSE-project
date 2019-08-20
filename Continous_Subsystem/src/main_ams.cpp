#include"Valve.hpp"
#include"Water_tank.hpp"
#include<systemc.h>
#include<systemc-ams.h>
#include"AMS-testbench.hpp"

int sc_main( int ac, char *av[] )
{
    AMS_testbench tb("testbench");

    sca_trace_file *file = sca_create_vcd_trace_file("water");
    sca_trace(file, tb.water_level_ams, "water_level");
    sca_trace(file,tb.command_rt,"comand");
    sca_trace(file,tb.aperture,"aperture");
    sca_trace(file,tb.threshold_ams,"threshold");
    
    
    sc_start(6000,SC_SEC);
    sca_close_vcd_trace_file(file);

}