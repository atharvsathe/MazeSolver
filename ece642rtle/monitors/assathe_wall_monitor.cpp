/* 
 * STUDENT NAME: Atharv SATHE
 * ANDREW ID: assathe
 * LAST UPDATE: 22 Nov 2020
 */

#include "monitor_interface.h"
#include <map>
#include <string>

/* size of walls checked */
const int SIZE = 4;
/* stores current pose and moved pose */
static Pose current_pose, only_pos;
/* stores current orientation */
static Orientation current_orientation;
/* stores bump data from all 4 directions */
static bool all_data[SIZE];

/* disctionary to get strings */
static std::map<int, std::string> orientation_val {
    {WEST, "West"}, {SOUTH, "South"}, {EAST, "East"}, {NORTH, "North"}
};

// Occurs every time moveTurtle is called
void tickInterrupt(ros::Time t) {

}

// Occurs every time turtle pose and orientation is updated
void poseInterrupt(ros::Time t, int x, int y, Orientation o) {
    current_pose.x = x;
    current_pose.y = y;
    current_orientation = o;
    if (current_pose.x != only_pos.x || current_pose.y != only_pos.y) {
        if (all_data[o] == false) {
            ROS_INFO("[[%ld ns]] 'Wall' not present, moved correctly at (%d,%d)", t.toNSec(), only_pos.x, only_pos.y);
        } else {
            ROS_WARN("Violation: Moved through a wall at (%d,%d)", only_pos.x, only_pos.y);
        }
        only_pos.x = x;
        only_pos.y = y;   
    }
}

// Occurs every time the visit count at the current location is updated
void visitInterrupt(ros::Time t, int visits) {

}

// Occurs every time a call to bumped(x1,y1,x2,y2) returns
// (t is the time of the server request, not answer)
void bumpInterrupt(ros::Time t, int x1, int y1, int x2, int y2, bool bumped) {
    if (current_pose.x == only_pos.x && current_pose.y == only_pos.y) {
        all_data[current_orientation] = bumped;
    } else {
    	/* resets all values */
        for (int i = 0 ; i < SIZE; i++) {
        	all_data[i] = true;
    	}
    }

}

// Occurs every time a call to atend(x,y) returns
// (t is the time of the server request, not answer)
void atEndInterrupt(ros::Time t, int x, int y, bool atEnd) {
}
