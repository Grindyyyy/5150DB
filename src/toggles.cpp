#include "api.h"
#include "toggles.hpp"
#include "init.hpp"

// ---------------------------------------------------------- //
//                          Toggles
// ---------------------------------------------------------- //

// Wing Toggles

// Declare a variable that is either true or false.
// This can help create toggles.
bool wingToggle = false;
bool backWingToggle = false;
bool cataUp = false;

// This function is binded to a keypress. It checks the wingToggle boolean and sets it to the opposite value.
// It then opens or closes the piston correspondant to the wingToggle boolean.
void wings() {
    if(wingToggle == true){
        wingToggle = false;
    }
    else{
        wingToggle = true;
    }
    if(wingToggle == true){
        frontWings.set_value(true);
    }
    else{
        frontWings.set_value(false);
    }
}

void bWings(){
    if(backWingToggle == true){
        backWingToggle = false;
    }
    else{
        backWingToggle = true;
    }
    if(backWingToggle == true){
        backWings.set_value(true);
    }
    else{
        backWings.set_value(false);
    }
}
// Declare a variable that is either true or false.
// This can help create toggles.
bool switchToggle = false;

// This is a function for our catapult switch that turns a false to a true or vice versa.
// Turning this toggle on turns off our linear switch, shown later in the code.
void killSwitch(){
    if(switchToggle == false){
        switchToggle = true;
    }
    else{
        switchToggle = false;
    }
}


// Declare a variable that is either true or false.
// This can help create toggles.
bool cataToggle = false;

// This is a function for our catapult switch that turns a false to a true or vice versa.
// Turning this toggle on spins the catapult infinitely at 127 volts.
void cataSwitch(){
    if(cataToggle == false){
        cataToggle = true;
    }
    else{
        cataToggle = false;
    }
}