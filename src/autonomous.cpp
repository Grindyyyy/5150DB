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
    intakeMotor.move(127);
}
void Autons::closeSide(){
    // This autonomous scores alliance triball, dislodges,
    // intakes 1 mid triball, and touches elevation bar
    chassis.setPose(-49.605, -54.506, 135);
    law();
    chassis.moveTo(-47.161, -59.539, 750);
    chassis.moveTo(-32.185,-63.933,750);
    //ram
    chassis.moveTo(-58.471,-39.991,1000);
    chassis.turnTo(-58.234, -61.418, 750);
    chassis.moveTo(-62,-24,750);
    laws();
    //ram end
    chassis.moveTo(-48.745, -49.867, 1000);
    chassis.moveTo(-25.703,-25.414,1150);
    intakeMotor = 127;
    chassis.turnTo(-18.875,-5.652,750);
    // intake mid triball
    chassis.moveTo(-27.875,-13,1250);
    intakeMotor = 0;
    chassis.moveTo(-24.82, -19.804, 750);
    // align to touch elevation
    chassis.moveTo(-45.872, -50.017, 1000);
    chassis.turnTo(-40.689,-58.097,750);
    chassis.moveTo(-40.689,-58.097,750);
    // outtake triball
    intakeMotor = -127;
    wait(200);
    intakeMotor = 0;
    // touch bar
    chassis.moveTo(-17.488,-57.948,3000);
}
void Autons::farSide(){
    // Far 6 Ball 2
    // This is a rework of the previous autonomous.
    // Intake elevation triball
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
}
void Autons::skills(){
    // Skills
    // This skills autonomous attempts to shoot the cata over for 40 seconds.
    // Afterwards, it will go under the bar and score on 3 sides of the goal.
    // INCOMPLETE  
    chassis.setPose(0,0,130);
    cataMotor.move(127);
    cataMotor2.move(127);
    wait(2000);
    while(1){
        if(rot.get_angle() / 100 > 0 && rot.get_angle() / 100 < 80){
        cataMotor.move(0);
        cataMotor2.move(0);
        chassis.moveTo(0,8,1000,127);
        chassis.moveTo(-7,80,1750,127);
        chassis.moveTo(-18,105,1000,127);
    wait(100);
        chassis.moveTo(0,105,1000,127);
        // ram 1
        chassis.moveTo(-35,110,1000,127);
        wait(100);
        chassis.setPose(0,0,0);
        // ram 2
        chassis.moveTo(0,10,600,127);
        wait(100);
        chassis.moveTo(0,-10,700,127);
        wait(100);
        chassis.moveTo(0,17,600,127);
        wait(100);
        chassis.setPose(0,0,0);
        wait(100);
        chassis.turnTo(45,0,1000);
        wait(100);
        wait(100);
        chassis.moveTo(25,-15,1000,127);
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
        chassis.setPose(0,0,0);
        wait(100);
        wait(100);
        chassis.moveTo(0,10,1000,127);
        raws();
        wait(100);
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
}
void Autons::awp(){
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
}
