#ifndef TRANSACTOR_RTL_AMS_HPP
#define TRANSACTOR_RTL_AMS_HPP

#include "systemc-ams.h"

SCA_TDF_MODULE( Transactor_RTL_AMS )
{
  public:
    sca_tdf::sca_out< double > threshold_ams;
    sca_tdf::sca_out< int > command_ams;

    sca_tdf::sca_de::sca_in< double > threshold_rtl;
    sca_tdf::sca_de::sca_in< int > command_rtl;

    Transactor_RTL_AMS( sc_core::sc_module_name );

    void set_attribute();
    void processing();

};

#endif 
