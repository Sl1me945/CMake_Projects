# CMakeList.txt : CMake project for Task_Tracker_Cli, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Task_Tracker_Cli "Task_Tracker_Cli.cpp" "Task_Tracker_Cli.h" "Task.h" "task_utils.h" "TaskTracker.cpp" "TaskTracker.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Task_Tracker_Cli PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
