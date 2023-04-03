/* 
 * STUDENT NAME: Atharv SATHE
 * ANDREW ID: assathe
 * LAST UPDATE: 22 Nov 2020
 */

#include "monitor_interface.h"
#include <map>
#include <string>

/* Stores the current pose */
static Pose current_pose;
/* Stores the orientation pose */
static Orientation current_orientation;
/* Checks is pose interrupt is called for first time*/
bool first_pose = true;

/* Dictionary to get respective strings */
static std::map<int, std::string> orientation_val {
    {WEST, "West"}, {SOUTH, "South"}, {EAST, "East"}, {NORTH, "North"}
};

/* Dictionary to get x offset to check */
static std::map<int, int> x1_offset {
    {WEST, 0}, {SOUTH, 0}, {EAST, 1}, {NORTH, 0}
};

/* Dictionary to get x offset to check */
static std::map<int, int> x2_offset {
    {WEST, 0}, {SOUTH, 1}, {EAST, 1}, {NORTH, 1}
};

/* Dictionary to get y offset to check */
static std::map<int, int> y1_offset {
    {WEST, 0}, {SOUTH, 1}, {EAST, 0}, {NORTH, 0}
};

/* Dictionary to get y offset to check */
static std::map<int, int> y2_offset {
    {WEST, 1}, {SOUTH, 1}, {EAST, 1}, {NORTH, 0}
};

// Occurs every time moveTurtle is called
void tickInterrupt(ros::Time t) {

}

// Occurs every time turtle pose and orientation is updated
void poseInterrupt(ros::Time t, int x, int y, Orientation o) {
    if (first_pose == true) {
        current_pose.x = x;
        current_pose.y = y;
        current_orientation = o;
        first_pose = false;
    }   
}

// Occurs every time the visit count at the current location is updated
void visitInterrupt(ros::Time t, int visits) {

}

// Occurs every time a call to bumped(x1,y1,x2,y2) returns
// (t is the time of the server request, not answer)
void bumpInterrupt(ros::Time t, int x1, int y1, int x2, int y2, bool bumped) {
    if (first_pose == false) {
        bool x1_correct = x1 == current_pose.x + x1_offset[current_orientation];
        bool x2_correct = x2 == current_pose.x + x2_offset[current_orientation];
        bool y1_correct = y1 == current_pose.y + y1_offset[current_orientation];
        bool y2_correct = y2 == current_pose.y + y2_offset[current_orientation];

        if (x1_correct && x2_correct && y1_correct && y2_correct) {
            ROS_INFO("[[%ld ns]] 'Bump' successfull at location (%d,%d) facing %s", t.toNSec(), current_pose.x, current_pose.y, orientation_val[current_orientation].c_str());
        } else {
            ROS_WARN("Violation: Incorrect Bump at location (%d,%d) facing %s", current_pose.x, current_pose.y,orientation_val[current_orientation].c_str());
            ROS_WARN("Values: (%d,%d), (%d,%d)", x1, y1, x2, y2);
        }
        first_pose = true;
    }
}

// Occurs every time a call to atend(x,y) returns
// (t is the time of the server request, not answer)
void atEndInterrupt(ros::Time t, int x, int y, bool atEnd) {
}