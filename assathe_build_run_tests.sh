current_path_1=$(pwd)
cd "$current_path_1"/catkin_ws/src/ece642rtle/student;g++ -std=c++11 -Dtesting -o assathe_tests assathe_test.cpp assathe_student_turtle.cpp -lcunit
"$current_path_1"/catkin_ws/src/ece642rtle/student/assathe_tests
cd ..