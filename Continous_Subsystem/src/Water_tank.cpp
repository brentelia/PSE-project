#include"Water_tank.hpp"

Water_tank::Water_tank(sc_core::sc_module_name name,
             double k1, double k2 ): //costanti dei moltiplicatori
             aperture("valve_aperture"), water_level("water_level"),
             x("x"),a("a"),a_gain("a_gain"),water1("water_deriv"),
             water2("water_tdf"),converter("converter"),
             mult1("k1",k1),mult2("k2",k2),sub("sub"),integral("integrale"),
             converterTDF("converter_lsf-tdf")
{   
    //binding
    converter.inp(aperture);
    converter.y(a);
    mult1.x(a);
    mult1.y(a_gain);
    sub.x1(a_gain);
    sub.x2(x);
    sub.y(water1);
    integral.x(water1);
    integral.y(water2);
    mult2.x(water2);
    mult2.y(x);
    converterTDF.x(water2);
    converterTDF.outp(water_level);
}