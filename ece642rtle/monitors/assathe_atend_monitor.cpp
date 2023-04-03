/* 
 * STUDENT NAME: Atharv SATHE
 * ANDREW ID: assathe
 * LAST UPDATE: 9 Dec 2020
 */

#include "monitor_interface.h"

/* Stores current position */
static Pose current_pose;
/* Checks if first time calling for pose */
static bool first_pose = false;


// Occurs every time moveTurtle is called
void tickInterrupt(ros::Time t) {

}

// Occurs every time turtle pose and orientation is updated
void poseInterrupt(ros::Time t, int x, int y, Orientation o) {
    current_pose.x = x;
    current_pose.y = y; 

}

// Occurs every time the visit count at the current location is updated
void visitInterrupt(ros::Time t, int visits) {

}

// Occurs every time a call to bumped(x1,y1,x2,y2) returns
// (t is the time of the server request, not answer)
void bumpInterrupt(ros::Time t, int x1, int y1, int x2, int y2, bool bumped) {

}

// Occurs every time a call to atend(x,y) returns
// (t is the time, of the server request, not answer)
void atEndInterrupt(ros::Time t, int x, int y, bool atEnd) {
    if (first_pose == true) {
        if (current_pose.x == x && current_pose.y == y) {
           ROS_INFO("[[%ld ns]] 'AtEnd' used at actual location (%d,%d)", t.toNSec(), x, y);
        } else {
           ROS_WARN("Violation: Current position is (%d,%d) AtEnd called at (%d,%d)", current_pose.x, current_pose.y, x, y);
        }   
    }
    first_pose = true;
}