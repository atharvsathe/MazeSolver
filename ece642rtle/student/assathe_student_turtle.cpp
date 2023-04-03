/* 
 * Originally by Philip Koopman (koopman@cmu.edu)
 * and Milda Zizyte (milda@cmu.edu)
 *
 * STUDENT NAME: Atharv SATHE
 * ANDREW ID: assathe
 * LAST UPDATE: 8 October 2020
 *
 * This file is an algorithm to solve the ece642rtle maze
 * using the left-hand rule. The code is intentionaly left obfuscated.
 *
 */

#ifdef testing
#include "assathe_mock.h"
#endif

#ifndef testing
#include "student.h"
#endif

#include <iostream>
#include <string>

Maze maze;
Solver solver;

/*
  Checks if in scanning mode or not. Compurtes move accordingly.
  Argument: bumped flag
  Returns: move
*/
turtleMove get_move(bool bumped) {
    turtleMove move = STOP;
    if (solver.is_scanning() == true) {
        solver.update(bumped);
        move = LEFT;
        maze.turn(move);
    }
    else {
        if (solver.required_orientation != maze.current_orientation) {
            move = RIGHT;
            maze.turn(move);
        }
        else {
            move = MOVE;
            maze.forward(move);
            solver.scanning_count = 0;
        }
    } 
    return move;
}

/*
  Computes valid move and updates number of visits based on 
  bumped and reached flag. This is an API function for assathe_student_maze
  Argument: bumped and reahed flags
  Returns: Struct containing valid move and number of visits for that position
*/
transfer studentTurtleStep(bool bumped, bool reached) {
	transfer final;	  
    final.move = STOP;

    if (reached == false) {
        final.move = get_move(bumped);
    }
     
    final.visits = maze.get_visits();
    return final;

	 
}

