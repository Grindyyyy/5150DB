#pragma once
#include "api.h"
#include "lemlib/api.hpp"

extern pros::Controller master;
extern pros::Motor leftFront;
extern pros::Motor leftBack;
extern pros::Motor rightFront;
extern pros::Motor rightBack;
extern pros::Motor_Group leftDB;
extern pros::Motor_Group rightDB;
extern pros::Motor cataMotor;
extern pros::Motor cataMotor2;
extern pros::Motor intakeMotor;
extern pros::ADIDigitalOut leftPiston;
extern pros::ADIDigitalOut rightPiston;
extern pros::ADIDigitalOut liftMech;
extern pros::ADIDigitalOut blocker;
extern pros::Imu inertial_sensor;
extern pros::Rotation rot;
extern lemlib::Drivetrain_t drivetrain;
extern lemlib::OdomSensors_t sensors;
extern lemlib::ChassisController_t lateralController;
extern lemlib::ChassisController_t angularController;
extern lemlib::Chassis chassis;


