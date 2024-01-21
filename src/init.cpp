#include "api.h"
#include "lemlib/api.hpp"
#include "init.hpp"

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
pros::Motor leftFront(19, pros::E_MOTOR_GEARSET_06, true);
pros::Motor leftMiddle(2, pros::E_MOTOR_GEARSET_06, false);
pros::Motor leftBack(3, pros::E_MOTOR_GEARSET_06, false);
pros::Motor rightFront(4, pros::E_MOTOR_GEARSET_06, false);
pros::Motor rightMiddle(5, pros::E_MOTOR_GEARSET_06, true);
pros::Motor rightBack(6, pros::E_MOTOR_GEARSET_06, true);

// Initialize two motor groups, one for each side of the drivebase.
// This makes it much simpler to do many things, but especially
// drive code and autonomous.
pros::Motor_Group leftDB({leftFront, leftMiddle, leftBack});
pros::Motor_Group rightDB({rightFront, rightMiddle, rightBack});

// Initialize 2 catapult motors.
// One spins in reverse while one doesn't because they 
// are on opposite sides.
// We run red motor with a 12/36 ratio so that's 33.333 RPM.
pros::Motor cataMotor(5, pros::E_MOTOR_GEARSET_36, false);
pros::Motor cataMotor2(9,pros::E_MOTOR_GEARSET_36,true);

// Initialize an intake motor with 600RPM. 
// The way that the motor is placed requires it to move in reverse.
pros::Motor intakeMotor(20, pros::E_MOTOR_GEARSET_06, false);

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
