/* 
 * STUDENT NAME: Atharv SATHE
 * ANDREW ID: assathe
 * LAST UPDATE: 5 Nov 2020
 */

#include "assathe_mock.h"
#include <CUnit/Basic.h>

extern Solver solver;
extern Maze maze;

/* Scanning Mode Test Cases */
void s_test_init() {
    solver.scanning_count = 0;
    turtleMove next_move_not_bumped = get_move(false);
    solver.scanning_count = 0;
    turtleMove next_move_bumped = get_move(true);

    CU_ASSERT_EQUAL(next_move_not_bumped, LEFT);
    CU_ASSERT_EQUAL(next_move_bumped, LEFT);
}

void s_test_t1() {
    CU_ASSERT_EQUAL(true, true);
}

void s_test_t2() {
    solver.scanning_count = 1;
    turtleMove next_move_not_bumped = get_move(false);
    solver.scanning_count = 1;
    turtleMove next_move_bumped = get_move(true);

    CU_ASSERT_EQUAL(next_move_not_bumped, LEFT);
    CU_ASSERT_EQUAL(next_move_bumped, LEFT);

    solver.scanning_count = 2;
    next_move_not_bumped = get_move(false);
    solver.scanning_count = 2;
    next_move_bumped = get_move(true);

    CU_ASSERT_EQUAL(next_move_not_bumped, LEFT);
    CU_ASSERT_EQUAL(next_move_bumped, LEFT);

    solver.scanning_count = 3;
    next_move_not_bumped = get_move(false);
    solver.scanning_count = 3;
    next_move_bumped = get_move(true);

    CU_ASSERT_EQUAL(next_move_not_bumped, LEFT);
    CU_ASSERT_EQUAL(next_move_bumped, LEFT);
}

void s_test_t3() {
    solver.scanning_count = 4;
    turtleMove next_move_not_bumped = get_move(false);
    solver.scanning_count = 4;
    turtleMove next_move_bumped = get_move(true);

    CU_ASSERT_NOT_EQUAL(next_move_not_bumped, LEFT);
    CU_ASSERT_NOT_EQUAL(next_move_bumped, LEFT);
}

/* Moving Mode Test Cases */
void m_test_init() {
    solver.scanning_count = 4;
    turtleMove next_move_not_bumped = get_move(false);
    CU_ASSERT_NOT_EQUAL(solver.required_orientation, DEFAULT);

    solver.scanning_count = 4;
    turtleMove next_move_bumped = get_move(true);
    CU_ASSERT_NOT_EQUAL(solver.required_orientation, DEFAULT);
}

void m_test_t1() {
    maze.reset_maze();
    maze.current_orientation = NORTH;

    solver.scan[0] = {NORTH, true, 1};
    solver.scan[1] = {EAST, true, 1};
    solver.scan[2] = {SOUTH, false, 1};
    solver.scan[3] = {WEST, true, 1};

    solver.scanning_count = 4;
    turtleMove next_move_not_bumped = get_move(false);
    CU_ASSERT_EQUAL(solver.required_orientation, SOUTH);
    CU_ASSERT_EQUAL(next_move_not_bumped, RIGHT); 
}

void m_test_t3() {
    maze.reset_maze();
    maze.current_orientation = SOUTH;

    solver.scan[0] = {NORTH, true, 1};
    solver.scan[1] = {EAST, true, 1};
    solver.scan[2] = {SOUTH, false, 1};
    solver.scan[3] = {WEST, true, 1};

    solver.scanning_count = 4;
    turtleMove next_move_not_bumped = get_move(false);
    CU_ASSERT_EQUAL(solver.required_orientation, SOUTH);
    CU_ASSERT_EQUAL(next_move_not_bumped, MOVE); 
    CU_ASSERT_EQUAL(solver.scanning_count, 0);
}

void m_test_turn() {
    maze.reset_maze();
    maze.current_orientation = SOUTH;
    maze.turn(LEFT);
    CU_ASSERT_EQUAL(maze.current_orientation, WEST);
    maze.turn(RIGHT);
    CU_ASSERT_EQUAL(maze.current_orientation, SOUTH);

    maze.current_orientation = WEST;
    maze.turn(LEFT);
    CU_ASSERT_EQUAL(maze.current_orientation, NORTH);
    maze.turn(RIGHT);
    CU_ASSERT_EQUAL(maze.current_orientation, WEST);

    maze.current_orientation = NORTH;
    maze.turn(LEFT);
    CU_ASSERT_EQUAL(maze.current_orientation, EAST);
    maze.turn(RIGHT);
    CU_ASSERT_EQUAL(maze.current_orientation, NORTH);

    maze.current_orientation = EAST;
    maze.turn(LEFT);
    CU_ASSERT_EQUAL(maze.current_orientation, SOUTH);
    maze.turn(RIGHT);
    CU_ASSERT_EQUAL(maze.current_orientation, EAST);
}

void m_test_forward() {
    maze.reset_maze();
    coordinate current_position = maze.current_position;
    maze.current_orientation = SOUTH;
    maze.forward(MOVE);
    CU_ASSERT_EQUAL(current_position.x, maze.current_position.x);
    CU_ASSERT_EQUAL(current_position.y - 1, maze.current_position.y);

    current_position = maze.current_position;
    maze.current_orientation = EAST;
    maze.forward(MOVE);
    CU_ASSERT_EQUAL(current_position.x + 1, maze.current_position.x);
    CU_ASSERT_EQUAL(current_position.y, maze.current_position.y);

    current_position = maze.current_position;
    maze.current_orientation = NORTH;
    maze.forward(MOVE);
    CU_ASSERT_EQUAL(current_position.x, maze.current_position.x);
    CU_ASSERT_EQUAL(current_position.y + 1, maze.current_position.y);

    current_position = maze.current_position;
    maze.current_orientation = WEST;
    maze.forward(MOVE);
    CU_ASSERT_EQUAL(current_position.x - 1, maze.current_position.x);
    CU_ASSERT_EQUAL(current_position.y, maze.current_position.y);
}

void m_test_visits() {
    maze.reset_maze();
    maze.current_orientation = SOUTH;
    maze.forward(MOVE);
    CU_ASSERT_EQUAL(maze.get_visits(), 1);

    maze.current_orientation = EAST;
    maze.forward(MOVE);
    CU_ASSERT_EQUAL(maze.get_visits(), 1);

    maze.current_orientation = NORTH;
    maze.forward(MOVE);
    CU_ASSERT_EQUAL(maze.get_visits(), 1);

    maze.current_orientation = WEST;
    maze.forward(MOVE);
    CU_ASSERT_EQUAL(maze.get_visits(), 1);
}

void m_test_compute() {
    maze.reset_maze();
    solver.reset_solver();

    solver.scan[WEST].blocked = false;
    solver.scan[EAST].blocked = true;
    solver.scan[SOUTH].blocked = true;
    solver.scan[NORTH].blocked = true;

    solver.compute();
    CU_ASSERT_EQUAL(solver.required_orientation, WEST);

    solver.scan[WEST].blocked = true;
    solver.scan[EAST].blocked = false;
    solver.compute();
    CU_ASSERT_EQUAL(solver.required_orientation, EAST);

    solver.scan[EAST].blocked = true;
    solver.scan[SOUTH].blocked = false;
    solver.compute();
    CU_ASSERT_EQUAL(solver.required_orientation, SOUTH);

    solver.scan[SOUTH].blocked = true;
    solver.scan[NORTH].blocked = false;
    solver.compute();
    CU_ASSERT_EQUAL(solver.required_orientation, NORTH);

    solver.scan[WEST].blocked = false;
    solver.scan[EAST].blocked = false;
    solver.scan[SOUTH].blocked = false;
    solver.scan[NORTH].blocked = false;

    solver.compute();
    CU_ASSERT_EQUAL(solver.required_orientation, WEST);

    solver.scan[WEST].blocked = true;
    solver.compute();
    CU_ASSERT_EQUAL(solver.required_orientation, SOUTH);

    solver.scan[SOUTH].blocked = true;
    solver.compute();
    CU_ASSERT_EQUAL(solver.required_orientation, EAST);

    solver.scan[EAST].blocked = true;
    solver.compute();
    CU_ASSERT_EQUAL(solver.required_orientation, NORTH);

}

/* Changing Mode Test Cases */
void c_test_t2() {
    solver.scanning_count = 4;
    transfer transfer_data = studentTurtleStep(true, false);
    CU_ASSERT_NOT_EQUAL(transfer_data.move, STOP);

    solver.scanning_count = 4;
    transfer_data = studentTurtleStep(false, false);
    CU_ASSERT_NOT_EQUAL(transfer_data.move, STOP);
}

void c_test_t3() {
    solver.scanning_count = 4;
    transfer transfer_data = studentTurtleStep(true, true);
    CU_ASSERT_EQUAL(transfer_data.move, STOP);

    solver.scanning_count = 4;
    transfer_data = studentTurtleStep(false, true);
    CU_ASSERT_EQUAL(transfer_data.move, STOP);
}

void c_test_update() {
    maze.reset_maze();

    maze.current_orientation = NORTH;
    solver.update(true);
    maze.current_orientation = EAST;
    solver.update(true);
    maze.current_orientation = SOUTH;
    solver.update(true);
    maze.current_orientation = WEST;
    solver.update(true);

    CU_ASSERT_EQUAL(solver.scan[0].blocked, true);
    CU_ASSERT_EQUAL(solver.scan[1].blocked, true);
    CU_ASSERT_EQUAL(solver.scan[2].blocked, true);
    CU_ASSERT_EQUAL(solver.scan[3].blocked, true);

    maze.current_orientation = NORTH;
    solver.update(false);
    maze.current_orientation = EAST;
    solver.update(false);
    maze.current_orientation = SOUTH;
    solver.update(false);
    maze.current_orientation = WEST;
    solver.update(false);

    CU_ASSERT_EQUAL(solver.scan[0].blocked, false);
    CU_ASSERT_EQUAL(solver.scan[1].blocked, false);
    CU_ASSERT_EQUAL(solver.scan[2].blocked, false);
    CU_ASSERT_EQUAL(solver.scan[3].blocked, false);
}


int init() {
  // Any test initialization code goes here
  return 0;
}

int cleanup() {
  // Any test cleanup code goes here
  return 0;
}

/* Skeleton code from http://cunit.sourceforge.net/example.html */
int main() {

    CU_pSuite scanningSuite = NULL;
    CU_pSuite moveSuite = NULL;
    CU_pSuite changingMode = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry()) {
    return CU_get_error();
    }

    /* add a suite to the registry */
    scanningSuite = CU_add_suite("Scanning Mode", init, cleanup);
    if (NULL == scanningSuite) {
    CU_cleanup_registry();
    return CU_get_error();
    }

    moveSuite = CU_add_suite("Move Mode", init, cleanup);
    if (NULL == moveSuite) {
    CU_cleanup_registry();
    return CU_get_error();
    }

    changingMode = CU_add_suite("Changing Mode", init, cleanup);
    if (NULL == changingMode) {
    CU_cleanup_registry();
    return CU_get_error();
    }

    /* add the tests to the suite */
    if ((NULL == CU_add_test(scanningSuite, "Test of initialization arc", s_test_init)) ||
        (NULL == CU_add_test(scanningSuite, "Test of T-1", s_test_t1)) ||
        (NULL == CU_add_test(scanningSuite, "Test of T-2", s_test_t2)) ||
        (NULL == CU_add_test(scanningSuite, "Test of T-3", s_test_t3))) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if ((NULL == CU_add_test(moveSuite, "Test of initialization arc", m_test_init)) ||
        (NULL == CU_add_test(moveSuite, "Test of T-1 and T-2", m_test_t1)) ||
        (NULL == CU_add_test(moveSuite, "Test of T-3", m_test_t3)) ||
        (NULL == CU_add_test(moveSuite, "Test of turning function", m_test_turn)) ||
        (NULL == CU_add_test(moveSuite, "Test of forward function", m_test_forward)) ||
        (NULL == CU_add_test(moveSuite, "Test of visit update function", m_test_visits)) ||
        (NULL == CU_add_test(moveSuite, "Test of move compute function", m_test_compute))) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if ((NULL == CU_add_test(changingMode, "Test of T-2", c_test_t2)) ||
        (NULL == CU_add_test(changingMode, "Test of T-3", c_test_t3)) ||
        (NULL == CU_add_test(changingMode, "Test of update function", c_test_update))) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();

    return 0;
}