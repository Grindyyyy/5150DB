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
        leftPiston.set_value(true);
        rightPiston.set_value(true);
    }
    else{
        leftPiston.set_value(false);
        rightPiston.set_value(false);
    }
}

// These functions make it easier to open and close wings in an auton, where all I have to type is
// raw, law, raws or laws.
void raw(){
    rightPiston.set_value(true);
}
void law(){
    leftPiston.set_value(true);
}
void raws(){
    rightPiston.set_value(false);
}
void laws(){
    leftPiston.set_value(false);
}

// Declare a variable that is either true or false.
// This can help create toggles.
bool blockerToggle = false;
bool switchToggle = false;

// This function is binded to a keypress. It checks the blockerToggle boolean and sets it to the opposite value.
// It then opens or closes the piston correspondant to the blockerToggle boolean.
void blockerFunc() {
    if(blockerToggle == true){
        blockerToggle = false;
    }
    else{
        blockerToggle = true;
    }
    if(blockerToggle == true){
        blocker.set_value(true);
        cataUp = true;
    }
    else{
        blocker.set_value(false);
    }
}

// Declare a variable that is either true or false.
// This can help create toggles.


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