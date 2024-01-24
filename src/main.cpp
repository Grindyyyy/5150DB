#include "main.h"
#include "lemlib/api.hpp"
#include "init.hpp"
#include "toggles.hpp"
#include "autonomous.hpp"


// ---------------------------------------------------------- //
//                          Main
// ---------------------------------------------------------- //

// The initialize function calibrates this chassis and sets the pose to 0,0,0 (default.)
// It also resets the rotational sensor and sets the reversed bool to true.
// A fundamental step for testing is initializing the LCD, which allows values to be
// printed to a part of the brain.
void initialize() {
    pros::lcd::initialize();
    rot.reset();
    rot.set_reversed(true);
    chassis.calibrate(); // calibrates positioning of the chassis for accurate pid
    chassis.setPose(0,0,0); // x pos, y pos, angle/theta
}

void autonomous(){
    Autons myAutons;
    myAutons.awp();
}

// ---------------------------------------------------------- //
//                          Driver
// ---------------------------------------------------------- //

// Disabled (Field Management/Comp Switch Disabled)
// Nothing should be inside the disabled function.
void disabled() {}

// Competition Initialization Function
// This is for if you have an autonomous picker.
void competition_initialize() {}

// Driver Control 
void opcontrol() {
    // We put all of the managers and drive code in a while loop so that it can properly update.
    // It updates every 20ms to prevent lag.
    while(1){
        // Arcade Drive Code
        // When the left joystick is moved up and down, the bot moves up and down.
        // When the right joystick is moved left and right, the bot moves left and right.
        // Combinations of these joystick movements creates a midpoint between, where
        // the bot can turn while moving forward.s
        double power = master.get_analog(ANALOG_LEFT_Y);
        double turn = master.get_analog(ANALOG_RIGHT_X);
        leftDB.move(power + turn);
        rightDB.move(power - turn);


        // Intake Code
        // If R2 is held down, motor = max speed
        if(master.get_digital(DIGITAL_R2)){
            intakeMotor.move(127);
        }
        
        // Intake Code
        // If L2 is held down, motor = max reverse speed
        else if(master.get_digital(DIGITAL_R1)){
            intakeMotor.move(-127);
        }

        // Intake Code
        // Otherwise, dont move at all
        else{
            intakeMotor.move(0);
        }

        // Cata Code
        // If L2 is being held down, motor = max speed
        // If not, motor = half speed unless rotational sensor angle is between 66 and 68
        // If rot sensor is between values motor stops so its a linear switch.
        
        // Blocker keybind toggle makes the cata go up when the blocker button is pressed
        if(cataUp == true){
            switchToggle = true;
            puncherMotor = -127;
            wait(350);
            cataUp = false; 
                   }   
        else if(switchToggle == false){
                // If the angle is between 0 and 80, don't move the cata motors.
                if(!master.get_digital(DIGITAL_L2) && cataToggle != true){
                    puncherMotor = 0;
                }
                // Else if L2 is held down, spin cata motors
                else if(master.get_digital(DIGITAL_L2)){
                    puncherMotor = 127;
                }
                else if(master.get_digital(DIGITAL_L1)){
                    if(rot.get_angle() / 100 > 0 && rot.get_angle() / 100 < 80){
                        puncherMotor = 0;
                    }
                    else{
                        puncherMotor = 110;
                    }
                }

                // We add this to our if statement so that it can check if the toggle is pressed and spin
                // without being overrided by other things such as the linear switch being in range.
                else if(cataToggle == true){
                    puncherMotor = 127;
                }

                // Otherwise, spin the cata at 100 (not max so the value doesn't skip)
                else{
                    puncherMotor = 100;
                }

        }
        else if(master.get_digital(DIGITAL_L2)){
            puncherMotor = 127;
        }
        else{
            puncherMotor = 0;
        }
        // Toggle Managers
        // These check for new presses. When there is one it runs the toggle function.
        if(master.get_digital_new_press(DIGITAL_X)){
            wings();
        }
        if(master.get_digital_new_press(DIGITAL_A)){
            killSwitch();
        }
        if(master.get_digital_new_press(DIGITAL_RIGHT)){
            cataSwitch();
        }
        if(master.get_digital(DIGITAL_Y)){
            puncherMotor = -127;
        }
        // This if statement manages the hang mechanism. If the up button is pressed the hang mech immediately releases.
        if(master.get_digital_new_press(DIGITAL_DOWN)){
            sideHang.set_value(true);
            pros::delay(200);
            sideHang.set_value(false);
        }
        if(master.get_digital_new_press(DIGITAL_UP)){

        }

        // ---------------------------------------------------------- //
        //                          Testing
        // ---------------------------------------------------------- //

        // This segment prints the x and y position of the bot as well as it's heading relative
        // to the pose set.
        lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        pros::lcd::print(0, "x: %f", pose.x); // print the x pqosition
        pros::lcd::print(1, "y: %f", pose.y); // print the y position

        // This prints the angle recieved from the rotational sensor to the brain.
        // This value updates every 20 milliseconds.
        pros::lcd::print(2, "cata heading: %i", rot.get_angle() / 100); 

        pros::lcd::print(3,"heading: %f", pose.theta);

        pros::delay(20);
    }
   
}