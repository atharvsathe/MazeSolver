/* 
 * Originally by Philip Koopman (koopman@cmu.edu)
 * and Milda Zizyte (milda@cmu.edu)
 *
 * STUDENT NAME: Atharv SATHE
 * ANDREW ID: assathe
 * LAST UPDATE: 1 Oct 2020
 *
 * This file keeps track of where the turtle is in the maze
 * and updates the location when the turtle is moved. It shall not
 * contain the maze solving logic/algorithm.
 *
 * This file is used along with student_turtle.cpp. student_turtle.cpp shall
 * contain the maze solving logic/algorithm and shall not make use of the
 * absolute coordinates or orientation of the turtle.
 *
 * This file shall call studentTurtleStep(..) in student_turtle.cpp to determine
 * the next move the turtle will make, and shall use translatePos(..) and
 * translateOrnt(..) to translate this move into absolute coordinates
 * to display the turtle.
 *
 */

#include "student.h"

/*
 Initializes the turtle and stores the position.
 Arguments: ROS QPointF datastructure that holds current position
            coordinate placeholders
 Returns: None
*/
void initialise_coordinates(QPointF& pos_, coordinate *position1, coordinate *position2) {
    position1->x = (uint8_t)pos_.x(); 
    position1->y = (uint8_t)pos_.y();
    position2->x = (uint8_t)pos_.x(); 
    position2->y = (uint8_t)pos_.y();
}

/*
 Update coordinates based on current orientation.
 Stores the updated values to coordinate placeholders.
 Arguments: current orientation and coordinate placeholders.
 Returns: None
*/
void update_coordinates(int orientation, coordinate *position1, coordinate *position2) {
    switch (orientation) {
        case WEST:
            position2->y ++;
            break;
        case SOUTH:
            position2->x ++;
            break;
        case EAST:
            position2->x ++; 
            position2->y ++; 
            position1->x ++;
            break;
        case NORTH:
            position2->x ++; 
            position2->y ++; 
            position1->y ++;
            break;
        default:
            ROS_ERROR("Orientation not found");
            break;
    }
}
/*
 * This procedure takes the current turtle position and orientation and returns true=accept changes, false=do not accept changes
 * Ground rule -- you are only allowed to call the three helper functions defined in student.h, and NO other turtle methods or maze methods (no peeking at the maze!)
 * This file interfaces with functions in student_turtle.cpp
 */
bool moveTurtle(QPointF& pos_, int& nw_or) {
    coordinate position1, position2;
    initialise_coordinates(pos_, &position1, &position2);
    update_coordinates(nw_or, &position1, &position2);

    bool bump = bumped(position1.x, position1.y, position2.x, position2.y);
    bool reach = atend((int)pos_.x(), (int)pos_.y());
    transfer data = studentTurtleStep(bump, reach); 
  
    pos_ = translatePos(pos_, data.move, nw_or);
    nw_or = translateOrnt(nw_or, data.move);
    displayVisits(data.visits);

    return !reach;
}

/*
 * Takes a position and a turtleMove and returns a new position
 * based on the move
 */
QPointF translatePos(QPointF pos_, turtleMove nextMove, int orientation) {
    if (nextMove == MOVE) {
        move_map map = translation[orientation];
        pos_.setX(pos_.x() + map.x);
        pos_.setY(pos_.y() + map.y); 
    }
    return pos_;
}

/*
 * Takes an orientation and a turtleMove and returns a new orienation
 * based on the move
 */
int translateOrnt(int orientation, turtleMove nextMove) {
    if (nextMove == RIGHT) {
        orientation = right[orientation];
    }
    else if (nextMove == LEFT) {
        orientation = left[orientation];
    }
    return orientation;
}
