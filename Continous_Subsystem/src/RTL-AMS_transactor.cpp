#include "RTL-AMS_transactor.hpp"

Transactor_RTL_AMS::Transactor_RTL_AMS( sc_core::sc_module_name ) :
  command_ams( "comand_ams"),
  command_rtl( "comand_rtl"),
  threshold_ams("threshold_ams"),
  threshold_rtl("threshold_rtl")
{
}


void Transactor_RTL_AMS::processing()
{
  command_ams.write(command_rtl.read());
  threshold_ams.write(threshold_rtl.read());
}

void Transactor_RTL_AMS::set_attribute()
{}
