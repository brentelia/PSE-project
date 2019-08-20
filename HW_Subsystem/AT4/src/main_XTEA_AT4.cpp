#include "XTEA_AT4.hpp"
#include"XTEA_AT4_testbench.hpp"

class main_module:public sc_module{
    private:
        Xtea_AT4 target;
        Xtea_AT4_testbench initiator;

    public:
        main_module(sc_module_name name):sc_module(name),
                                        target("target_LT"),
                                        initiator("initiator_LT")
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