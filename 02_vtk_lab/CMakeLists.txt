cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_FLAGS "-std=c++11")

project(vtkdemo)
add_executable(plane-vtk plane-vtk.cpp)


#include_directories(${GMSH_INCLUDE_DIR})

add_library(gmsh SHARED IMPORTED)
set_target_properties(gmsh PROPERTIES
    IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libgmsh.so"
    INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
)
set(GMSH_LIBRARIES gmsh)


find_package(VTK REQUIRED)
include(${VTK_USE_FILE})


target_link_libraries(plane-vtk ${VTK_LIBRARIES})
target_link_libraries(plane-vtk ${GMSH_LIBRARIES})
