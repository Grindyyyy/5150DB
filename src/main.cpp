#include "main.h"
#include "lemlib/api.hpp"
#define LEFT_DIGITAL_PORT 'A'
#define RIGHT_DIGTIAL_PORT 'B'



pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor leftFront(1, pros::E_MOTOR_GEARSET_06, true);
pros::Motor leftBack(2, pros::E_MOTOR_GEARSET_06, true);
pros::Motor rightFront(7, pros::E_MOTOR_GEARSET_06, false);
pros::Motor rightBack(4, pros::E_MOTOR_GEARSET_06, false);
pros::Motor cataMotor(5, pros::E_MOTOR_GEARSET_36, false);
pros::Motor cataMotor2(9,pros::E_MOTOR_GEARSET_36,true);
pros::Motor intakeMotor(6, pros::E_MOTOR_GEARSET_06, true);
pros::ADIDigitalOut leftPiston(LEFT_DIGITAL_PORT);
pros::ADIDigitalOut rightPiston(RIGHT_DIGTIAL_PORT);
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
    10.8, // kP
    20, // kD
    1, // smallErrorRange
    200, // smallErrorTimeout
    3, // largeErrorRange
    1100, // largeErrorTimeout
    25 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    5.55, // kPenis
    12, // kDick
    1, // small range
    300, // small timeout
    1, // large range
    1000, // large timeout
    25 // slew
};

lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);


// Initialize chassis and calibrate gyro
void initialize() {
    pros::lcd::initialize();
    chassis.calibrate(); // calibrates positioning of the chassis for accurate pid
    chassis.setPose(0,0,0); // x pos, y pos, angle/theta
   
}

// Disabled (Field Management/Comp Switch Disabled)
// Probably dont put anything in here
void disabled() {}

// Comp initialize
// Use for auton picker if you want
void competition_initialize() {}

// Autonomous
void autonomous() {
    // Intake
    intakeMotor.move(127);
    pros::delay(500);
    // Path 1 gets into position to ram the matchload into the goal
    chassis.follow("RightEasy1.txt",750,12);
    // Outtake matchload triball
    intakeMotor.move(-127);
    pros::delay(500);
    intakeMotor.move(0);
    // This path rams the matchload triball into the goal and sets up to intake the next triball
    chassis.follow("RightEasy2.txt",750,12);
    // Intake
    intakeMotor.move(127);
    // This path intakes the triball that is not on the line
    chassis.follow("RightEasy3.txt",500,12);
    pros::delay(1000);
    // Stop intake
    intakeMotor.move(0);
    // This path sets up to ram the triball into the goal
    chassis.follow("RightEasy4.txt",500,12);
    // Outtake
    intakeMotor.move(-127);
    pros::delay(500);
    intakeMotor.move(0);
    // This path rams the triball into the goal and sets up to pick up the far back triball
    chassis.follow("RightEasy5.txt",500,20);
    // Intake
    intakeMotor.move(127);
    // This path intakes the far back triball and sets up to ram both triballs inside the goal
    chassis.follow("RightEasy6.txt",500,5);
    pros::delay(1000);
    intakeMotor.move(0);
    // This path rams the triball closest to the goal into the goal and sets up to outtake the
    // intaked triball
    chassis.follow("RightEasy7.txt",750,20);
    // Outtake
    intakeMotor.move(-127);
    pros::delay(500);
    intakeMotor.move(0);
    // This path rams the final triball into the goal
    chassis.follow("RightEasy8.txt",500,20);

    // RIGHT SIDE EASY, 20 POINT AUTON \\

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
        if(rot.get_angle() > 66 && rot.get_angle() < 68){
            cataMotor.move(0);
            cataMotor2.move(0);
        }
        else if(master.get_digital(DIGITAL_L2)){
            cataMotor.move(127);
            cataMotor2.move(127);
        }
        else{
            cataMotor.move(63);
            cataMotor2.move(63);
        }

        lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        pros::lcd::print(0, "x: %f", pose.x); // print the x position
        pros::lcd::print(1, "y: %f", pose.y); // print the y position
        pros::lcd::print(2, "heading: %f", pose.theta); // print the heading

        pros::delay(20);
    }
   
}

// 


