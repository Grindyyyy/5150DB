#include "main.h"
#include "lemlib/api.hpp"
#define LEFT_DIGITAL_PORT 'A'
#define RIGHT_DIGTIAL_PORT 'B'


bool wingToggle = false;
bool switchToggle = false;
bool cataToggle = false;


pros::Optical opticalSensor(11);
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor leftFront(1, pros::E_MOTOR_GEARSET_06, true);
pros::Motor leftBack(2, pros::E_MOTOR_GEARSET_06, true);
pros::Motor rightFront(7, pros  ::E_MOTOR_GEARSET_06, false);
pros::Motor rightBack(4, pros::E_MOTOR_GEARSET_06, false);
pros::Motor cataMotor(5, pros::E_MOTOR_GEARSET_36, false);
pros::Motor cataMotor2(9,pros::E_MOTOR_GEARSET_36,true);
pros::Motor intakeMotor(6, pros::E_MOTOR_GEARSET_06, true);
pros::ADIDigitalOut leftPiston('B',false);
pros::ADIDigitalOut rightPiston('A',false);
pros::Rotation rot(10);

pros::Motor_Group leftDB({leftFront, leftBack});
pros::Motor_Group rightDB({rightFront, rightBack});

lemlib::Drivetrain_t drivetrain {
    &leftDB, // left drivetrain motors
    &rightDB, // right drivetrain motors
    15, // track width
    4.00, // wheel diameter
    257 // wheel rpm
};
 
// inertial sensor
pros::Imu inertial_sensor(8); // port 2
 
// odometry struct
lemlib::OdomSensors_t sensors {
    // set all to nullptr because we aren't using odometry this year
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    &inertial_sensor // inertial sensor
};

// forward/backward PID
lemlib::ChassisController_t lateralController {
    15,// kP
    100, // kD
    0, // smallErrorRange
    10000, // smallErrorTimeout
    0, // largeErrorRange
    10000, // largeErrorTimeout
    25 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    5, //kPenis
    15.7, // kDick
    1, // small range
    750, // small timeout
    1, // large range
    2000, // large timeout
    25 // slew
};

lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);


// Initialize chassis and calibrate gyro
void initialize() {
    pros::lcd::initialize();
    rot.reset();
    rot.set_reversed(true);
    chassis.calibrate(); // calibrates positioning of the chassis for accurate pid
    chassis.setPose(0,0,0); // x pos, y pos, angle/theta
   
}

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

void killSwitch(){
    if(switchToggle == false){
        switchToggle = true;
    }
    else{
        switchToggle = false;
    }
}

void cataSwitch(){
    if(cataToggle == false){
        cataToggle = true;
    }
    else{
        cataToggle = false;
    }
}

void autonWing(){
    leftPiston.set_value(true);
    rightPiston.set_value(true);
}

void autonWingStop(){
    leftPiston.set_value(false);
    rightPiston.set_value(false);
}



// Disabled (Field Management/Comp Switch Disabled)
// Probably dont put anything in here
void disabled() {}

// Comp initialize
// Use for auton picker if you want
void competition_initialize() {}

void wait(int msec){
    pros::delay(msec);
}

// Autonomous
void autonomous() {
// OLD CODE
// --------------------------------------------------------------- \\
   // Close AWP
/*
   chassis.setPose(0,0,45);
   cataMotor.move(127);
   cataMotor2.move(127);
   wait(300);
   cataMotor2.move(0);
   cataMotor.move(0);
   autonWing();
   wait(100);
   chassis.turnTo(0,10000,750,false,100);
   wait(200);
   autonWingStop();
   wait(100);
   chassis.moveTo(6,24,1000,100);
   wait(100);
   chassis.turnTo(6,10000,750);
   wait(300);
   chassis.setPose(0,0,0);
   wait(400);
   chassis.turnTo(0,10000,750);
   wait(100);
   chassis.moveTo(0,14,1000,100);
*/
    // Skills
/*
    chassis.setPose(0,0,145);
    cataMotor.move(127);
    cataMotor2.move(127);
    wait(35000);
    while(1){
        if(rot.get_angle() / 100 > 0 && rot.get_angle() / 100 < 80){
        cataMotor.move(0);
        cataMotor2.move(0);
        chassis.moveTo(5,10,1500,127);
        wait(200);
        chassis.moveTo(3,93,1500,127);
        wait(200);
        autonWing();
        wait(100);
        chassis.moveTo(-18,105,1000,127);
    wait(100);
        autonWingStop(); 
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
        autonWing();
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
        autonWingStop();
        chassis.setPose(0,0,0);
        wait(100);
        wait(100);
        chassis.moveTo(0,10,1000,127);
        wait(100);
        chassis.turnTo(100,-15,1000);
        wait(100);
        chassis.moveTo(50,-20,1500,127);
        wait(100);
        chassis.setPose(0,0,0);
        wait(100);
        autonWing();
        wait(100);
        chassis.moveTo(40,-30,1000,127);
        wait(100);
        chassis.setPose(0,0,0);
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
        autonWingStop();
        wait(100000);
    }
    else{
        cataMotor.move(127);
        cataMotor2.move(127);
    }
    }
*/
// --------------------------------------------------------------- 
// NEW CODE
// ---------------------------------------------------------------
/*
// 6 BALL RIGHT/FAR AUTON
// ----------------------
// Start
chassis.setPose(8.27,-58.015,270);
// Lower Intake with Cata
cataMotor = 127;
wait(300);
cataMotor = 0;
// Intake Bar Triball
intakeMotor = 127;
wait(1000);
intakeMotor = 0;
// Move to Match Load
chassis.moveTo(37.689,-57.784,1000,127);
chassis.moveTo(54.538,-50.794,1000,127);
// Extend Wings to Dislodge Match Load
autonWing();
chassis.moveTo(59.62,-37.956,1000,127);
autonWingStop();
// Ram Triballs into Goal using Wedge x2
chassis.moveTo(59.887,-22.444,800,127);
chassis.moveTo(59.62,-37.956,1000,127);
chassis.moveTo(59.887,-22.444,800,127);
// Set up to grab the next triballs
chassis.moveTo(45.712,-49.724,1000,127);
chassis.moveTo(25.386,-22.444,1000,127);
// Intake the Triball
intakeMotor = 127;
chassis.moveTo(11.211,-23.514,2000,80);
wait(500);
intakeMotor = 0;
// Turn to Goal and Outtake Triball
chassis.turnTo(46.782,-12.816,1000);
intakeMotor = -127;
wait(200);
intakeMotor = 0;
wait(100);
// Intake the Line Triball
intakeMotor = 127;
chassis.moveTo(21.107,-6.13,2000,80);
// Turn to Goal & Outtake Triball
chassis.turnTo(47.05,-6.932,1000);
intakeMotor = -127;
wait(300);
intakeMotor = 0;
// Intake other Line Triball
chassis.turnTo(11.479,-1.048,1000);
intakeMotor = 127;
chassis.moveTo(11.479,-1.048,1000,127);
// Outtake into Goal
chassis.turnTo(47.05,0.824,1000);
intakeMotor = -127;
wait(300);
intakeMotor = 0;
// Turn to face the other goal (To push with wings)
chassis.turnTo(-70,-0.781,1000);
// Open wings and ram the goal twice
autonWing();
chassis.moveTo(47.05,0.824,1000,127);
chassis.moveTo(30,0.824,1000,127);
chassis.moveTo(47.05,0.824,1000,127);
// Congrats it might be a 6 ball
*/
/*
// LEFT/CLOSE SIDE 2 GOALS 2 PUSH
// ----------------------
// Set Position
chassis.setPose(-34.522,-58.817,90);
// Open Wing to Dislodge Triball
autonWing();
chassis.moveTo(-56.988,-43.84,1000,127);
autonWingStop();
// Ram Matchload and Triball into the Goal
chassis.moveTo(-57.255,-22.979,1000,127);
// Back Up to Rush Middle
chassis.moveTo(-56.988,-42.79,1000,127);
// Go to middle and set up for push
chassis.moveTo(-20.882,-26.189,1000,127);
chassis.moveTo(-37.732,-10.677,1000,127);
// Turn to face the goal & open wings
chassis.turnTo(-100,10.677,1000);
autonWing();
// Push the triballs to the other side of the field
chassis.moveTo(-8.312,-10.677,1000,127);
autonWingStop();
// Move to the matchload bar to set up for immediate matchloading after auton
chassis.moveTo(-53.779,-49.724,1500,127);
chassis.turnTo(-147.95, -94.314,1000);
*/
/*
// PROG SKILLS (~150 PT)
// ----------------------
chassis.setPose(-44.997,-54.73,240);
cataMotor.move(127);
cataMotor2.move(127);
wait(35000);
// Linear Switch Statement
while(1){
    if(rot.get_angle() / 100 > 0 && rot.get_angle() / 100 < 80){
        // Move under Bar
        chassis.moveTo(-23.052,-59.639,1000,127);
        chassis.moveTo(32.389,-60.216,1000,127);
        // Open wing to dislodge matchload & any triballs that may have been stuck inside
        autonWing();
        chassis.moveTo(52.313,-49.243,1000,127);
        chassis.moveTo(59.243,-40.003,1000,127);
        autonWingStop();
        // Ram all triballs into goal twice
        chassis.moveTo(58.954,-24.122,800,127);
        chassis.moveTo(59.82,-38.848,1000,127);
        chassis.moveTo(58.954,-24.122,800,127);
        // Move to the middle
        chassis.moveTo(46.782,-48.387,1000,127);
        chassis.moveTo(17.363,-18.433,1000,127);
        chassis.moveTo(17.095,-6.665,1000,127);
        // Line up for ram
        chassis.turnTo(-62.604,-6.665,1000);
        autonWing();
        // Ram once, move up 10 inches and ram again (to get all triballs in)
        chassis.moveTo(46.782,-6.665,1000,127);
        chassis.moveTo(16.026,5.905,1000,127);
        chassis.moveTo(47.317,5.905,1000,127);
        autonWingStop();
        // Move to the last side of the net
        chassis.moveTo(16.828,17.94,1000,127);
        chassis.moveTo(44.972,57.4,1000,127);
        // Line up for ramming
        chassis.turnTo(-5.656,116.927,1000);
        // Dislodge triballs in matchload area
        autonWing();
        chassis.moveTo(55.645,43.917,1000,127);
        autonWingStop();
        // Ram 3 times * Change all if your gonna change 1
        chassis.moveTo(59.577,35.21,1000,127);
        chassis.moveTo(59.577,22.009,1000,127);
        chassis.moveTo(59.577,35.21,1000,127);
        chassis.moveTo(59.577,22.009,1000,127);
        chassis.moveTo(59.577,35.21,1000,127);
        chassis.moveTo(59.577,22.009,1000,127);


}
    else{
        cataMotor.move(127);
        cataMotor2.move(127);
}
}
*/
}
void IntakeFull(){

}

// Driver Control 
void opcontrol() {
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
        // If L2 is held down, motor = max reverse speed
        // Otherwise, dont move at all
        if(master.get_digital(DIGITAL_R2)){
            intakeMotor.move(127);
        }
        else if(master.get_digital(DIGITAL_R1)){
            intakeMotor.move(-127);
        }
        else{
            intakeMotor.move(0);
        }

        // Cata Code
        // If L2 is being held down, motor = max speed
        // If not, motor = half speed unless rotational sensor angle is between 66 and 68
        // If rot sensor is between values motor stops so its a linear switch.
        double angle = rot.get_angle();
        std::printf("%f", angle);
        
        if(switchToggle == false){
            if(rot.get_angle() / 100 > 0 && rot.get_angle() / 100 < 80 && !master.get_digital(DIGITAL_L2) && cataToggle != true){
                cataMotor.move(0);
                cataMotor2.move(0);  
            }
            else if(master.get_digital(DIGITAL_L2)){
                cataMotor.move(127);
                cataMotor2.move(127);
            }
            else if(cataToggle == true){
                cataMotor.move(127);
                cataMotor2.move(127);
            }
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
         
        if(master.get_digital_new_press(DIGITAL_X)){
            wings();
        }
        if(master.get_digital_new_press(DIGITAL_A)){
            killSwitch();
        }
        if(master.get_digital_new_press(DIGITAL_UP)){
            cataSwitch();
        }


        lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        pros::lcd::print(0, "x: %f", pose.x); // print the x position
        pros::lcd::print(1, "y: %f", pose.y); // print the y position
        pros::lcd::print(2, "cata heading: %i", rot.get_angle() / 100); // print the heading
        pros::lcd::print(3,"heading: %f", pose.theta);
        pros::lcd::print(4,"left torque: %f", leftFront.get_torque());
        pros::lcd::print(5,"right torque: %f",rightFront.get_torque());

        pros::delay(20);
    }
   
}

// 


