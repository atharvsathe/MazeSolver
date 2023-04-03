current_path=$(pwd)
mv "$current_path"/ece642rtle "$current_path"/catkin_ws/src/
cd catkin_ws/

catkin_make clean
catkin_make
catkin_make ece642rtle_step_monitor
catkin_make ece642rtle_turn_monitor
catkin_make ece642rtle_tick_monitor
catkin_make ece642rtle_forward_monitor
catkin_make ece642rtle_wall_monitor
catkin_make ece642rtle_face_monitor
catkin_make ece642rtle_solved_monitor
catkin_make ece642rtle_atend_monitor
source devel/setup.bash

cd

"$current_path"/assathe_build_run_tests.sh 