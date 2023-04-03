/* 
 * STUDENT NAME: Atharv SATHE
 * ANDREW ID: assathe
 * LAST UPDATE: 19 Nov 2020
 */

#include "monitor_interface.h"

/* Checks if turtle has reached the end */
static bool at_end = false;

// Occurs every time moveTurtle is called
void tickInterrupt(ros::Time t) {

}

// Occurs every time turtle pose and orientation is updated
void poseInterrupt(ros::Time t, int x, int y, Orientation o) {
    if (at_end == true) {
        ROS_WARN("Violation: Moved even after reaching the end.");
    }
}

// Occurs every time the visit count at the current location is updated
void visitInterrupt(ros::Time t, int visits) {

}

// Occurs every time a call to bumped(x1,y1,x2,y2) returns
// (t is the time of the server request, not answer)
void bumpInterrupt(ros::Time t, int x1, int y1, int x2, int y2, bool bumped) {

}

// Occurs every time a call to atend(x,y) returns
// (t is the time of the server request, not answer)
void atEndInterrupt(ros::Time t, int x, int y, bool atEnd) {
    if (atEnd == true) {
        at_end = true;
        ROS_INFO("[[%ld ns]] 'End' reached at (%d,%d)", x, y);
    }
        
}