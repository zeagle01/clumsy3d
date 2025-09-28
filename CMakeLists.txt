
cmake_minimum_required(VERSION 3.30)

project(clumsy3d_sln)

include(cmake/utils.cmake)


set(glfw3_DIR ${CMAKE_SOURCE_DIR}/3rd/glfw3/share/glfw3)


add_subdirectory(entry)
add_subdirectory(clumsy3d)
add_subdirectory(components/cl_event_driver)
