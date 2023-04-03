current_path=$(pwd)
cd "$current_path"/catkin_ws/src/ece642rtle/monitors
#gnome-terminal -x ./run_642_monitors.sh ece642rtle_atend_monitor ece642rtle_step_monitor ece642rtle_turn_monitor ece642rtle_tick_monitor ece642rtle_forward_monitor ece642rtle_wall_monitor ece642rtle_face_monitor ece642rtle_solved_monitor 
#gnome-terminal -x ./run_642_monitors.sh ece642rtle_atend_monitor
cd
"$current_path"/catkin_ws/src/ece642rtle/build_run_turtle.sh m"$1".maze

cd
