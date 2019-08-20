#include"Valve.hpp"

Valve::Valve(sc_core::sc_module_name name):
            command("command"),
            threshold("threshold"),
            aperture("aperture")
{
    current_aperture=0;
}

void Valve::set_attributes()
{
    command.set_timestep(5,SC_MS);
    command.set_delay(1);
    threshold.set_timestep(5,SC_MS);
    threshold.set_delay(1);

}

void Valve::processing(){
    double delta=0.25*get_timestep().to_seconds();
    if(command.read()==IDLE)
        aperture.write(current_aperture);
    else if( command.read()==OPEN){
        if(current_aperture>=threshold.read()){
            current_aperture=threshold.read();
            aperture.write(threshold.read());
        }
        else{
            current_aperture+=delta;
            aperture.write(current_aperture);
        }
    }
    else if(command.read()==CLOSE){
        if(current_aperture<0){
            current_aperture=threshold.read();
            aperture.write(0);
        }
        else {
            current_aperture-=delta;
            aperture.write(current_aperture);
        }
    }

}