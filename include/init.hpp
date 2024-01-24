#pragma once
#include "api.h"
#include "lemlib/api.hpp"

extern pros::Controller master;
extern pros::Motor leftFront;
extern pros::Motor leftMiddle;
extern pros::Motor leftBack;
extern pros::Motor rightFront;
extern pros::Motor rightMiddle;
extern pros::Motor rightBack;
extern pros::Motor_Group leftDB;
extern pros::Motor_Group rightDB;
extern pros::Motor puncherMotor;
extern pros::Motor intakeMotor;
extern pros::ADIDigitalOut frontWings;
extern pros::ADIDigitalOut backWings;
extern pros::ADIDigitalOut sideHang;
extern pros::ADIDigitalOut vertHang;
extern pros::Imu inertial_sensor;
extern pros::Rotation rot;
extern lemlib::Drivetrain drivetrain;
extern lemlib::OdomSensors sensors;
extern lemlib::ControllerSettings lateralController;
extern lemlib::ControllerSettings angularController;
extern lemlib::Chassis chassis;


