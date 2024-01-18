#include "main.h"
#include "lemlib/api.hpp"

// ---------------------------------------------------------- //
//                          Initialize
// ---------------------------------------------------------- //

// Initialize a Controller called 'master' as the main controller.
// It is called master in case of other controllers being used.
// For example, another controller can be used to deploy our hang.
// This controller would be called 'child' or 'slave'.
pros::Controller master(pros::E_CONTROLLER_MASTER);

// Initialize the drivebase of our robot.
// There are 2 motors on each side.
// We run 600RPM motors with a 36/84 gear ratio.
// This makes our RPM 257. (600 * (36/84))
pros::Motor leftFront(1, pros::E_MOTOR_GEARSET_06, true);
pros::Motor leftBack(2, pros::E_MOTOR_GEARSET_06, true);
pros::Motor rightFront(7, pros::E_MOTOR_GEARSET_06, false);
pros::Motor rightBack(4, pros::E_MOTOR_GEARSET_06, false);

// Initialize two motor groups, one for each side of the drivebase.
// This makes it much simpler to do many things, but especially
// drive code and autonomous.
pros::Motor_Group leftDB({leftFront, leftBack});
pros::Motor_Group rightDB({rightFront, rightBack});

// Initialize 2 catapult motors.
// One spins in reverse while one doesn't because they 
// are on opposite sides.
// We run red motor with a 12/36 ratio so that's 33.333 RPM.
pros::Motor cataMotor(5, pros::E_MOTOR_GEARSET_36, false);
pros::Motor cataMotor2(9,pros::E_MOTOR_GEARSET_36,true);

// Initialize an intake motor with 600RPM. 
// The way that the motor is placed requires it to move in reverse.
pros::Motor intakeMotor(6, pros::E_MOTOR_GEARSET_06, true);

// Initialize our pneumatics.
// We use the digital out ports for VEX pneumatics, and they're lettered
// rather than numbered to prevent confusion when looking at code.
// I'm not exactly sure what 'false' does but it is a required bool.
pros::ADIDigitalOut leftPiston('E',false);
pros::ADIDigitalOut rightPiston('F',false);
pros::ADIDigitalOut liftMech('H',false);
pros::ADIDigitalOut blocker('A',false);

// Initialize our sensors.
// Our IMU (Inertial Measurement Unit) is used for our PIDs to turn accurately.
// Our rotation sensor is placed on our cata with a ratchet to create a linear
// switch, which will be covered later in the code.
pros::Imu inertial_sensor(8);
pros::Rotation rot(10);

// We use the LemLib library for simpler PID creation and faster tuning, and this library
// requires a drivebase class to be set. We establish necessary information such as the
// track width and both sides of the drivebase.
lemlib::Drivetrain_t drivetrain {
    &leftDB, // Left MotorGroup
    &rightDB, // Right MotorGroup
    15, // track width
    4.00, // wheel diameter
    257 // wheel rpm
};
 
// LemLib is able to have VEX Odometry (a complex and extremely accurate coordinate system
// for autonomous using PID and sensors) using motor encoders. Typically, this is much
// harder to code and most programmers strive for rotational sensors on the bottom of
// a chassis, commonly called Odom Wheels.
lemlib::OdomSensors_t sensors {
    // We aren't using odometry wheels this year, so the lemlib sensors
    // need to be set to 'nullptr'.
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    // We need to set the IMU to inertial sensor so that it can properly turn properly.
    &inertial_sensor // inertial sensor
};

// LemLib has a massive PID class for move and turn inside of ChassisController_t
// and creating lateralController just takes the parameters that you put inside and 
// adjusts the values to that.

// LemLib only uses PD due to the fruitlessness of PID for autonomous.
// It accepts kP and kD as adjustable values (which are how PIDs are tuned),
// accepts a range to which it can stop, the timeout of which it can adjust or oscillate,
// and the slew rate, which is the maximum rate that the code can accept a rapid change
// in voltage or value.
lemlib::ChassisController_t lateralController {
    16,// kP
    100, // kD
    0, // smallErrorRange
    1000, // smallErrorTimeout
    0, // largeErrorRange
    1000, // largeErrorTimeout
    25 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    5, //kP
    15.7, // kD
    1, // small range
    750, // small timeout
    1, // large range
    2000, // large timeout
    25 // slew
};


// LemLib requires you to establish a chassis, and this chassis class contains everything LemLib needs to create working PID
// as well as the PID itself.
lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);


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

// This wait function is for quality of life during autonomous.
// Usually, you'll have to do pros::delay(msec);
// But with wait, you can just do wait(msec);
void wait(int msec){
    pros::delay(msec);
}

// ---------------------------------------------------------- //
//                          Autonomous
// ---------------------------------------------------------- //

// Autonomous is a 15 second period at the beginning of every match in which the
// robot moves using hard code, rather than being driven manually.
// You can obtain Autonomous Bonus by scoring more points than the opposing team.
// You can obtain Autonomous Win Point by:
// 1) Scoring your alliance's triball into the alliance's goal
// 2) Dislodging your alliance's matchload from the matchload area
// 3) Touching your alliance's elevation bar at the end of the match
// There is a close and far side that you can go on, and typically AWP is obtained
// through the close side.
// The far side scores the most points and houses the 6 ball autonomous.
void autonomous() {
    /*
   // Close AWP
   // Th/is autonomous dislodges the matchload triball and touches the elevation bar.
   blocker.set_value(true);
   wait(500);
   blocker.set_value(false);
   chassis.setPose(0,0,45);
   cataMotor.move(127);
   cataMotor2.move(127);
   wait(300);
   cataMotor2.move(0);
   cataMotor.move(0);
   raw();
   law();
   wait(100);
   chassis.turnTo(0,10000,750,false,100);
   wait(200);
   raws();
   laws();
   wait(100);
   chassis.moveTo(6,24,1000,100);
   wait(100);
   chassis.turnTo(6,10000,750);
   wait(300);
   chassis.setPose(0,0,0);
   wait(400);
   chassis.turnTo(0,2000,750);
   wait(100);
   chassis.moveTo(0,12,1000,100);
   */

/*
    // Close High AWP
    // This autonomous scores the alliance triball, dislodges the triball, pushes 2 triballs across
    // and touches the elevation bar.
    chassis.setPose(-48.707,-51.625,90);
    // Lower Intake
    blocker.set_value(true);
    wait(100);
    blocker.set_value(false);
    // Dislodge Matchload Triball
    raw();
    law();
    chassis.turnTo(-59.033,-42.423,700);
    raws();
    laws();
    // Ram Alliance Triball into Goal
    chassis.moveTo(-59.033,-42.423,700,127);
    chassis.moveTo(-60.828,-22.895,700,127);
    // Set up a push of middle triballs
    chassis.moveTo(-52.523,-45.341,700,127);
    chassis.moveTo(-23.119,-28.506,1000,127);
    chassis.moveTo(-35.24,-9.652,700,127);
    chassis.turnTo(-66.66,-9.652,700);
    // Push triballs
    raw();
    law();
    chassis.moveTo(-9.203,-9.652,1000,127);
    raws();
    laws();
    // Move to the bar
    chassis.moveTo(-43.32,-43.769,1200,127);
    chassis.moveTo(-35.913,-59.033,700,127);
    chassis.turnTo(-64.42,-57.237,700);
    // Touch bar with blocker
    blocker.set_value(true);
    chassis.moveTo(-6.06,-59.033,1000,127);
*/



    // Skills
 // This skills autonomous attempts to shoot the cata over for 40 seconds.
    // Afterwards, it will go under the bar and score on 3 sides of the goal.
    // INCOMPLETE  
    /*
    chassis.setPose(0,0,145);
    cataMotor.move(127);
    cataMotor2.move(127);
    wait(35000);
    while(1){
        if(rot.get_angle() / 100 > 0 && rot.get_angle() / 100 < 80){
        cataMotor.move(0);
        cataMotor2.move(0);
        chassis.moveTo(5,8,1500,127);
        wait(200);
        chassis.moveTo(3,93,1500,127);
        wait(200);
        raw();
        law();
        wait(100);
        chassis.turnTo(22,-66,1000);
        chassis.moveTo(-18,105,1000,127);
    wait(100);
        chassis.moveTo(0,105,1000,127);
        raws();
        laws();
        chassis.moveTo(-35,110,1000,127);
        wait(100);
        chassis.setPose(0,0,0);
        chassis.moveTo(0,10,600,127);
        wait(100);
        chassis.moveTo(0,-10,700,127);
        wait(100);
        chassis.moveTo(4,17,600,127);
        wait(100);
        chassis.setPose(0,0,0);
        wait(100);
        chassis.turnTo(45,0,1000);
        wait(100);
        wait(100);
        chassis.moveTo(35,-10,1000,127);
        wait(100);
        chassis.turnTo(50,5,1000);
        wait(100);
        raw();
        law();
        wait(100);
        chassis.setPose(0,0,0);
        chassis.moveTo(0,-50,1300,127);
        wait(100);
        chassis.setPose(0,0,0);
        wait(100);
        chassis.moveTo(10,25,1200,127);
        wait(100);
        chassis.moveTo(10,-5,1200,127);
        wait(100);
        chassis.moveTo(10,10,1000,127);
        wait(100);
        raws();
        laws();
        chassis.setPose(0,0,0);
        wait(100);
        wait(100);
        chassis.moveTo(0,10,1000,127);
        wait(100);
        raw();
        law();
        wait(100);
        chassis.moveTo(50,-20,1500,127);
        wait(100);
        chassis.setPose(0,0,0);
        wait(100);
        chassis.moveTo(40,-30,1000,127);
        wait(100);
        chassis.setPose(0,0,0);
        chassis.turnTo(10,0,1000,127);
        wait(100);
        chassis.moveTo(0,10,1000,127);
        wait(100);
        chassis.moveTo(0,-15,1000,127);
        wait(100);
        chassis.setPose(0,0,0);
        wait(100);
        chassis.moveTo(0,10,1000,127);
        wait(100);
        chassis.moveTo(0,-15,1000,127);
        raws();
        laws();
        wait(100000);
    }
    else{
        cataMotor.move(127);
        cataMotor2.move(127);
    }
    }
    
    */



// Far 6 Ball 2
// This is a rework of the previous autonomous.
// Intake elevation triball
/*
chassis.setPose(10.223,-58.135,270);
intakeMotor = 127;
wait(500);
intakeMotor = 0;
// Dislodge matchload triball
chassis.moveTo(36.138,-58.135,1000);
raw();
law();
chassis.moveTo(54.89,-52.238,650);
chassis.turnTo(64.257,-55,750);
raws();
laws();
chassis.turnTo(73.257,-23.344,750);
// Outtake triball
intakeMotor = -127;
wait(100);
intakeMotor = 0;
// Ramming process
chassis.moveTo(45.789,-55.666,500);
chassis.moveTo(76.299, -41.344,400);
chassis.moveTo(70.94,-22.67,750);
chassis.moveTo(48.299,-46.463,750);
chassis.moveTo(35.303,-15.262,750);
chassis.turnTo(9.467,-28.364,750);
//
// Intake mid triball 1
chassis.turnTo(6.467, -8, 750);
intakeMotor = 127;
chassis.moveTo(6.467, -8, 750);
wait(300);
// Outtake mid triball 1
chassis.turnTo(42.361,0,750);
intakeMotor = -127;
wait(200);
intakeMotor = 0;
// Position to intake mid triball 2
chassis.moveTo(35,-18.508,750);
chassis.turnTo(4,-3,500);
intakeMotor = 127;
chassis.moveTo(15,-10,500);
// Intake mid triball 2
chassis.moveTo(7,1,500);
wait(300);
intakeMotor = 0;
// Ram all triballs in(win vex)
raw();
law();
chassis.moveTo(46.912,-1,750);
*/
/*
intakeMotor = 127;
wait(200);
intakeMotor = 0;
blocker.set_value(true);
wait(300);
blocker.set_value(false);
chassis.setPose(-52.984, -51.631, 0);
raw();
chassis.moveTo(-45.041, -58.666, 1000);
chassis.turnTo(-14.5,-11.5,1000);
raws();
chassis.moveTo(-15.54, -15.776, 1000);
chassis.turnTo( -40.276,-10.784,1000);
chassis.moveTo(-40.949, -10.507, 1000);
raw();
law();
chassis.moveTo(-3.286, -11.465, 1000);
laws();
raws();
chassis.moveTo(-39.595, -38.469, 1000);
chassis.moveTo(-37.326, -57.985, 1000);
chassis.moveTo(-16.448, -58.666, 1000);
chassis.moveTo(-6.69, -58.666, 1000);
*/

chassis.setPose(-49.605, -54.506, 135);
law();
chassis.moveTo(-47.161, -59.539, 750);
chassis.moveTo(-37.185,-63.933,750);
laws();
//ram
chassis.moveTo(-53.234, -49.418, 750);
chassis.moveTo(-62.022, -38.345, 500);
chassis.moveTo(-62.771, -18.892, 500);
//ram end
chassis.moveTo(-48.745, -49.867, 1000);
chassis.moveTo(-29.703,-30.414,750);
chassis.moveTo(-25.879, -8.844, 1000);
chassis.turnTo(-61.427,-8.811,750);
chassis.moveTo(3.517, -10.968, 1000);
chassis.moveTo(-9.82, -15.804, 750);
chassis.moveTo(-45.872, -50.017, 1000);

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
            cataMotor = -127;
            wait(350);
            cataUp = false; 
                   }   
        else if(switchToggle == false){
                // If the angle is between 0 and 80, don't move the cata motors.
                if(rot.get_angle() / 100 > 0 && rot.get_angle() / 100 < 80 &&
                !master.get_digital(DIGITAL_L2) && cataToggle != true){
                    cataMotor.move(0);
                    cataMotor2.move(0);  
                }
                // Else if L2 is held down, spin cata motors
                else if(master.get_digital(DIGITAL_L2)){
                    cataMotor.move(127);
                    cataMotor2.move(127);
                }

                // We add this to our if statement so that it can check if the toggle is pressed and spin
                // without being overrided by other things such as the linear switch being in range.
                else if(cataToggle == true){
                    cataMotor.move(127);
                    cataMotor2.move(127);
                }

                // Otherwise, spin the cata at 100 (not max so the value doesn't skip)
                else{
                    cataMotor.move(100);
                    cataMotor2.move(100);
                }

        }
        else if(master.get_digital(DIGITAL_L2)){
            cataMotor.move(127);
            cataMotor2.move(127);
        }
        else{
            cataMotor.move(0);
            cataMotor2.move(0);
        }
        // Toggle Managers
        // These check for new presses. When there is one it runs the toggle function.
        if(master.get_digital_new_press(DIGITAL_X)){
            wings();
        }
        if(master.get_digital_new_press(DIGITAL_A)){
            killSwitch();
        }
        if(master.get_digital_new_press(DIGITAL_B)){
            blockerFunc();
        }
        if(master.get_digital_new_press(DIGITAL_DOWN)){
            cataSwitch();
        }
        if(master.get_digital(DIGITAL_Y)){
            cataMotor.move(-127);
            cataMotor2.move(-127);
        }
        // This if statement manages the hang mechanism. If the up button is pressed the hang mech immediately releases.
        if(master.get_digital(DIGITAL_UP)){
            liftMech.set_value(true);
            pros::delay(200);
            liftMech.set_value(false);
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