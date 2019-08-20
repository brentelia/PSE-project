#ifndef WATER_TANK_HPP
#define WATER_TANK_HPP

#include <systemc.h>
#include <systemc-ams.h>
//LSF
class Water_tank:public sc_core::sc_module
{
    public:
        sca_tdf::sca_in <double> aperture; //apertura
        sca_tdf::sca_out<double> water_level; //livello
        Water_tank(sc_core::sc_module_name name,
             double k1, double k2 );
    private:
        sca_lsf::sca_signal a, a_gain,x,water1,water2; //segnali uscita moduli
        sca_lsf::sca_tdf::sca_source converter; //convertitore tdf/lsf
        sca_lsf::sca_gain mult1,mult2; //moltplicatori
        sca_lsf::sca_sub sub;   //sottrattore
        sca_lsf::sca_integ integral;
        sca_lsf::sca_tdf::sca_sink converterTDF;
    

};

#endif