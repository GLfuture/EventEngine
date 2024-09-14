project(CoScheduler)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE Debug) 

aux_source_directory(. SRC_LIST)
add_executable(CoScheduler ${SRC_LIST})