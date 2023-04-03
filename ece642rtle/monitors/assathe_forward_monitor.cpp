/* 
 * STUDENT NAME: Atharv SATHE
 * ANDREW ID: assathe
 * LAST UPDATE: 19 Nov 2020
 */

#include "monitor_interface.h"
#include <map>
#include <string>

static Pose last_pos;
static Orientation last_orientation;
static bool first_update = true;
//bool move = false;

static std::map<int, int> x_offset {
    {WEST, -1}, {SOUTH, 0}, {EAST, 1}, {NORTH, 0}
};

static std::map<int, int> y_offset {
    {WEST, 0}, {SOUTH, 1}, {EAST, 0}, {NORTH, -1}
};

static std::map<int, std::string> orientation_val {
    {WEST, "West"}, {SOUTH, "South"}, {EAST, "East"}, {NORTH, "North"}
};

// Occurs every time moveTurtle is called
void tickInterrupt(ros::Time t) {

}

// Occurs every time turtle pose and orientation is updated
void poseInterrupt(ros::Time t, int x, int y, Orientation o) {
    if (first_update == true) {
        first_update = false;
    } else if (first_update == false) {
        if (last_pos.x != x || last_pos.y != y) {
            if (last_orientation == o && last_pos.x + x_offset[o] == x && last_pos.y + y_offset[o] == y) {
                ROS_INFO("[[%ld ns]] 'Forward' move successful. Moved from (%d,%d) to (%d, %d) facing %s", t.toNSec(),
                    last_pos.x, last_pos.y, x, y, orientation_val[o].c_str());
            } else {
                ROS_WARN("Vioation: Moved from (%d,%d) to (%d, %d) facing %s",
                    last_pos.x, last_pos.y, x, y, orientation_val[o].c_str());
            }
        }
    }
    last_pos.x = x;
    last_pos.y = y;
    last_orientation = o;

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