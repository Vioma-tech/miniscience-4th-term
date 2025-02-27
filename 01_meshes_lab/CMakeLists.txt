cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_FLAGS "-std=c++11 -g")

project(gmshdemo)
add_executable(cube cube.cpp)
add_executable(circle circle.cpp)
add_executable(cylinder cylinder.cpp)
add_executable(donut donut.cpp)
add_executable(plane plane.cpp)


#include_directories(${GMSH_INCLUDE_DIR})

add_library(gmsh SHARED IMPORTED)
set_target_properties(gmsh PROPERTIES
    IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libgmsh.so"
    INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
)
set(GMSH_LIBRARIES gmsh)


target_link_libraries(cube ${GMSH_LIBRARIES})
target_link_libraries(circle ${GMSH_LIBRARIES})
target_link_libraries(cylinder ${GMSH_LIBRARIES})
target_link_libraries(donut ${GMSH_LIBRARIES})
target_link_libraries(plane ${GMSH_LIBRARIES})