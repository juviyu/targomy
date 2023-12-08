
ActuatorState {
    running
    success
    failiure
}


Actuator
    ActuatorState
    
    setup()
    set_target(int: 0 - 100, timout)
    get_state() -> ActuatorState
    update()

    _timoutReached() //what happens when timout reached



JawLogic{
    current_phase
}





TELEMETRY_HZ = 5//Hz
ACTUATOR_STATES_HZ = 1000//Hz
JAWS_HZ = 1000//Hz


TELEMETRY_DELAY_MS  = 1000 / TELEMETRY_HZ
ACTUATOR_STATES_DELAY_MS  = 1000 / TELEMETRY_HZ
JAWS_DELAY_MS  = 1000 / TELEMETRY_HZ

void loop(){
 
    EVERY_N_MILLISECONDS( 1000 / TELEMETRY_HZ)
        telemetry()
    
    EVERY_N_MILLISECONDS( 1000 / TELEMETRY_HZ)
        recvCmds()

    EVERY_N_MILLISECONDS( 1000 / JAWS_HZ)
        JawLogic.update()
    
    EVERY_N_MILLISECONDS( 1000 / ACTUATOR_STATES_HZ)
        handleActuatorStates()
    
}