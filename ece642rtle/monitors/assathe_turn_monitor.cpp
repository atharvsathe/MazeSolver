/* 
 * STUDENT NAME: Atharv SATHE
 * ANDREW ID: assathe
 * LAST UPDATE: 10 Nov 2020
 */

#include "monitor_interface.h"
#include <map>
#include <string>

/* Dictionary to check unallowed orientations */
static std::map<int, int> opposite {
    {WEST, EAST}, {SOUTH, NORTH}, {EAST, WEST}, {NORTH, SOUTH}
};

/* Dictionary to get strings */
static std::map<int, std::string> orientation_val {
    {WEST, "West"}, {SOUTH, "South"}, {EAST, "East"}, {NORTH, "North"}
};

/* checks if tick interrupt is called for the first time */
static bool first_tick = true;
/* stores current pose of the turtle */
static Orientation pose_orientation;
/* stores previous pose of the turtle */
static Orientation last_orientation;

// Occurs every time moveTurtle is called
void tickInterrupt(ros::Time t) {
    if (first_tick == true) {
        last_orientation = pose_orientation;
        first_tick = false;
    } else {
        ROS_INFO("[[%ld ns]] 'Turn' was sent. Data: orientation = %s", t.toNSec(), orientation_val[pose_orientation].c_str());

        if (opposite[pose_orientation] == last_orientation) {
            ROS_WARN("Violation: Turned from %s to %s", orientation_val[last_orientation].c_str(), orientation_val[pose_orientation].c_str());
        }
        last_orientation = pose_orientation;
    }
}

// Occurs every time turtle pose and orientation is updated
void poseInterrupt(ros::Time t, int x, int y, Orientation o) {
    pose_orientation = o;
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

}