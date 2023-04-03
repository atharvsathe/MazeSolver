/* 
 * STUDENT NAME: Atharv SATHE
 * ANDREW ID: assathe
 * LAST UPDATE: 25 Nov 2020
 */

#include "monitor_interface.h"

/* Manitains number of pose interrupts*/
static int pose = 0;
/* Manitains number of visit interrupts*/
static int visit = 0;
/* Manitains number of bump interrupts*/
static int bump = 0;
/* Checks if tick inteerupr is called for the fisrt time*/
static bool tick = false;

// Occurs every time moveTurtle is called
void tickInterrupt(ros::Time t) {
	if (tick == true) {
		if (pose <= 1 && visit <= 1 && bump <= 1) {
			ROS_INFO("[[%ld ns]] 'Tick' recieved.", t.toNSec());
		} else {
			ROS_WARN("Vioation: 'Tick' recieved but multiple times action called %d %d %d", pose, visit, bump);
		}
	} else {
		tick = true;
	}
	pose = 0;
	visit = 0;
	bump = 0;
}

// Occurs every time turtle pose and orientation is updated
void poseInterrupt(ros::Time t, int x, int y, Orientation o) {
	pose++;
}

// Occurs every time the visit count at the current location is updated
void visitInterrupt(ros::Time t, int visits) {
	visit++;

}

// Occurs every time a call to bumped(x1,y1,x2,y2) returns
// (t is the time of the server request, not answer)
void bumpInterrupt(ros::Time t, int x1, int y1, int x2, int y2, bool bumped) {
	bump++;

}

// Occurs every time a call to atend(x,y) returns
// (t is the time of the server request, not answer)
void atEndInterrupt(ros::Time t, int x, int y, bool atEnd) {

}