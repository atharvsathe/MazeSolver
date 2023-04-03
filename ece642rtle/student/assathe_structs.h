/* 
 * STUDENT NAME: Atharv SATHE
 * ANDREW ID: assathe
 * LAST UPDATE: 5 Nov 2020
 */

#include <map>

// Scope-preserving changes to these lines permitted (see p5 writeup)
typedef enum turtleMove {MOVE, RIGHT, LEFT, STOP} turtleMove;
typedef enum heading {WEST, SOUTH, EAST, NORTH, DEFAULT} heading;

typedef struct status {heading orientation; bool blocked; int visits;} status;
typedef struct coordinate{uint8_t x; uint8_t y;} coordinate;
typedef struct transfer { turtleMove move; int visits;} transfer;
typedef struct move_map{int x; int y;
    move_map () {}
    move_map(int input_x, int input_y) {
        x = input_x;
        y = input_y;
    }
} move_map;

static std::map<int, int> right {
    {WEST, SOUTH}, {SOUTH, EAST}, {EAST, NORTH}, {NORTH, WEST}
};

static std::map<int, int> left {
    {WEST, NORTH}, {SOUTH, WEST}, {EAST, SOUTH}, {NORTH, EAST}
};

static std::map<int, move_map> translation {
    {WEST, move_map(-1, 0)}, {SOUTH, move_map(0, -1)}, 
    {EAST, move_map(1, 0)}, {NORTH, move_map(0, 1)}
};

// Defines variable to store position and orientation on grid
typedef struct Maze {
    static const uint8_t size = 23;
    int all_data[size][size];
    coordinate current_position;
    int current_orientation;

    /*
      Constructor. Defines grid. Sets starting position at (12, 12)
      Default orienatation set to NORTH.
    */
    Maze() {
        reset_maze();
    } 

    /*
      Changes the orientation of the turtle.
      Argument: Move for turn
      Returns: None
    */
    void turn(turtleMove this_turn) {
        if (this_turn == LEFT) {
            current_orientation = left[current_orientation];
        }
        else if (this_turn == RIGHT) {
            current_orientation = right[current_orientation];
        }
    }

    /*
      Updates position of the turtle in the grid
      Argument: Move for forward
      Returns: None
    */
    void forward(turtleMove this_forward) {
        if (this_forward == MOVE) {
            move_map map = translation[current_orientation];
            if (map.x == 1) {
                current_position.x ++;
            } else if (map.x == -1) {
                current_position.x --;
            }

            if (map.y == 1) {
                current_position.y ++;
            } else if (map.y == -1) {
                current_position.y --;
            }
            all_data[current_position.x][current_position.y] += 1;
        }
    }

    /*
      Getter function to return number of visits at current position
    */
    int get_visits() {
        return all_data[current_position.x][current_position.y];
    }

    /*
      Getter function to get number of visits some point from current position
      Arguments: x and y offset from current position
      Returns: visits at the offset position
    */
    int get_visits_for(int x, int y) {
        return all_data[current_position.x + x][current_position.y + y];
    }

    /*
      Resetting maze to initial conditoins
    */
    void reset_maze() {
        for (uint8_t row = 0; row < size; row++) {
            for (uint8_t column = 0; column < size; column++) {
                all_data[row][column] = 0;
            }
        }
        current_position.x = 11;
        current_position.y = 11;
        current_orientation = SOUTH;
    }
} Maze;
extern Maze maze;

// Defines variable that stores all computation
typedef struct Solver {
    static const uint8_t SIZE = 4;
    static const int MAX = 255;

    heading required_orientation = DEFAULT;
    uint8_t scanning_count;
    status scan[4];
    /*
      Constructor to initialize variables
    */
    Solver() {
        reset_solver();
    }

    /*
      Updates bumpber flag against each orientatoion
    */
    void update(bool bumped) {
        scan[maze.current_orientation].blocked = bumped;
    }

    /*
      Computes the orientation which has minimum number of visits
    */
    void compute() {
        status minimum = {};
        minimum.visits = MAX;

        for (uint8_t index = 0; index < SIZE; index++) {
            if (scan[index].blocked == false) {
                move_map map = translation[scan[index].orientation];
                scan[index].visits = maze.get_visits_for(map.x, map.y);
                if (scan[index].visits < minimum.visits) {
                    minimum = scan[index];
                }
            }
        }
        required_orientation = minimum.orientation;
    }

    /*
      Checks if the algorithm is in scanning mode
    */
    bool is_scanning() {
        bool flag;
        if (scanning_count < 4) {
            flag = true;
            scanning_count++;
            required_orientation = DEFAULT;
        }
        else {
            flag = false;
            compute();
        }
        return flag;
    }

    void reset_solver() {
        scanning_count = 0;
        for (uint8_t count = 0; count < SIZE; count++) {
            scan[count].orientation = heading(count);
        }
    }
} Solver;



