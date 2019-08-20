#include "AMS-testbench.hpp"

AMS_testbench::AMS_testbench(sc_core::sc_module_name):
    controller("controller"),
    tlm_to_rtl("tlm_to_rtl"),
    rtl_to_ams("rtl_to_ams"),
    valve("valve"),
    tank("tank",0.6,0.03),
    ams_to_rtl("ams_to_rtl"),
    rtl_to_tlm("rtl_to_tlm")
{
    //controller => tlm-rtl
    controller.initiator_socket(tlm_to_rtl.target_socket);
    tlm_to_rtl.command(command_rt);
    tlm_to_rtl.threshold(threshold_rt);

    //tlm-rtl => rtl-ams
    rtl_to_ams.command_rtl(command_rt);
    rtl_to_ams.threshold_rtl(threshold_rt);
    rtl_to_ams.command_ams(command_ams);
    rtl_to_ams.threshold_ams(threshold_ams);

    //rtl-ams => valvola
    valve.threshold(threshold_ams);
    valve.command(command_ams);
    valve.aperture(aperture);
    //valvola => tank
    tank.aperture(aperture);
    tank.water_level(water_level_ams);

    //tank => ams-rtl
    ams_to_rtl.water_level_ams(water_level_ams);
    ams_to_rtl.water_level_rtl(water_level_rt);

    //ams-rtl => rtl-tlm
    rtl_to_tlm.water_level_rt(water_level_rt);
    rtl_to_tlm.initiator_socket(controller.target_socket);
}
