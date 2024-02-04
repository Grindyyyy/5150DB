#include "toggles.hpp"
#include "api.h"
#include "init.hpp"
#include "autonomous.hpp"


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

// This wait function is for quality of life during autonomous.
// Usually, you'll have to do pros::delay(msec);
// But with wait, you can just do wait(msec);
void wait(int msec){
    pros::delay(msec);
}



void Autons::test(){
    chassis.setPose(10,-60,270);
    intakeMotor = 127;
    chassis.moveToPoint(43.769,-59.033,1000,false);
    wait(700);
    backWings.set_value(true);
    chassis.moveToPoint(55.155,-46.769,1000,false);
    chassis.turnTo(60.325,-60.379,750);
    backWings.set_value(false);
    chassis.moveToPoint(68.788,-20.238,1000,false);
    chassis.moveToPoint(58.359,-38.607,750);
    chassis.turnTo(58.808,-20.201,750,true,80);
    intakeMotor = -127;
    wait(300);
    intakeMotor = 0;
    chassis.moveToPoint(63.073,-24.017,600);
    chassis.moveToPoint(36,-60,1250,false);
    chassis.turnTo(36,10000,1000);
}
void Autons::closeSide(){
    
}
void Autons::farSide(){
    chassis.setPose(36,-60,0);
    frontWings.set_value(true);
    wait(200);
    frontWings.set_value(false);
    chassis.moveToPoint(33.22,-26.711,800, true, 127, false);
    intakeMotor = 127;
    chassis.turnTo(8,-24,400);
    chassis.moveToPoint(3.978,-24.241,800);
    wait(350);
    chassis.turnTo(46.238,-13,750,true,127,false);
    intakeMotor = -127;
    wait(300);
    intakeMotor = 0;
    chassis.turnTo(-4.611,-1.122,750,true,127,false);
    intakeMotor = 127;
    chassis.moveToPoint(-4,-10,1000);
    chassis.turnTo(46.463,-15,750,true,127,false);
    frontWings.set_value(true);
    intakeMotor = -127;
    chassis.moveToPoint(46.463,-15.836,1000,true,127,false);
    frontWings.set_value(false);
    chassis.moveToPoint(5,-20,1000,false);
    chassis.moveToPoint(20,-60,1500,true,127,false);
    intakeMotor.move(127);
    chassis.moveToPoint(-11,-62,1500,true);
    chassis.moveToPoint(15,-66,1250,false,127,false);
    backWings.set_value(true);
    chassis.moveToPoint(37,-54,1000,false,127,false);
    chassis.turnTo(37,-10000,400);
    chassis.turnTo(37,-20,1000,true,127,false);
    backWings.set_value(false);
    intakeMotor = -127;
    chassis.moveToPoint(65,0,3000,true,127,false);
     
}
// i love you :3 - matt (cooper) thx
void Autons::farSide2(){
    chassis.setPose(10,-60,270);
    intakeMotor = 127;
    chassis.moveToPoint(34.791,-59.033,1000,false);
    chassis.turnTo(57.237,-23.119,750);
    wait(500);
    intakeMotor = -127;
    wait(300);
    intakeMotor = 0;
    chassis.turnTo(10.325,-60.379,750);
    backWings.set_value(true);
    chassis.moveToPoint(56.788,-50.238,1000,false);
    chassis.turnTo(63.073,-24.017,750);
    backWings.set_value(false);
    chassis.moveToPoint(63.073,-24.017,600,false);
    chassis.moveToPoint(36,-60,1250);
    chassis.turnTo(36,10000,1000);
    wait(1000);
    chassis.moveToPoint(33.22,-26.711,800);
    chassis.turnTo(8.978,-24.241,600);
    intakeMotor = 127;
    chassis.moveToPoint(8.978,-24.241,800);
    wait(350);
    chassis.turnTo(46.238,-13.794,900,true,95);
    wait(1200);
    intakeMotor = -127;
    wait(300);
    intakeMotor = 0;
    chassis.turnTo(-8.611,-1.122,750);
    intakeMotor = 127;
    chassis.moveToPoint(-8.611,-13.122,1600);
    chassis.turnTo(46.463,-15.836,750);
    wait(1000);
    frontWings.set_value(true);
    intakeMotor = -127;
    chassis.moveToPoint(46.463,-15.836,1000);
}

void Autons::skills(){
    chassis.setPose(40.627,61.277,270);
    backWings.set_value(true);
    wait(45000);
    backWings.set_value(false);
    chassis.moveToPoint(-36.362,58.808,2000,true,127,false);
    frontWings.set_value(true);
    chassis.moveToPoint(-56.563,43.545,1000);
    chassis.moveToPoint(-56.563,27.608,1000);
    chassis.moveToPoint(-56.563,43.545,1000);
    chassis.moveToPoint(-56.563,27.608,1000);
    
    chassis.moveToPoint(-56.563,43.545,1000);
    
    

}
void Autons::awp(){  
    chassis.setPose(-47.585,-57.461,135);
    wait(500);
    intakeMotor.move(127);
    wait(500);
    intakeMotor.move(0);
    backWings.set_value(true);
    chassis.moveToPoint(-30.526,-60.379,1000);
    wait(1000);
    backWings.set_value(false);
    wait(1500);
    chassis.moveToPoint(-10,-60,1000);
    intakeMotor = -127;
    wait(2000);
    intakeMotor = 0;
}
