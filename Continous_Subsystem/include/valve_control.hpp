#ifndef VALVE_CONTROLE_HP
#define VALVE_CONTROLE_HP

#include <systemc.h>


struct valve_control {
    int command;
    double threshold;
};

#endif
