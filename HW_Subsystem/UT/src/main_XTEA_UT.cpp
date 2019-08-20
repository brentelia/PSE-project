#include "XTEA_UT.hpp"
#include"XTEA_UT_testbench.hpp"

class main_module:public sc_module{
    private:
        Xtea_UT target;
        Xtea_UT_testbench initiator;

    public:
        main_module(sc_module_name name):sc_module(name),
                                        target("target_UT"),
                                        initiator("initiator_UT")
        {
            //binding porte
            initiator.initiator_socket(target.target_socket);
        }
};

int main(int argc, char* argv[])
{
    main_module main("main");
    sc_start();
    return 0;
}