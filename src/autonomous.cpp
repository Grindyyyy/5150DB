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

}
void Autons::farSide(){
}
void Autons::skills(){

}
void Autons::awp(){  
}
