
cmake_minimum_required(VERSION 3.30)

project(clumsy3d_sln)

include(cmake/utils.cmake)


set(glfw3_DIR ${CMAKE_SOURCE_DIR}/3rd/glfw3/share/glfw3)
set(glad_DIR ${CMAKE_SOURCE_DIR}/3rd/glad/share/glad)
set(GTest_DIR ${CMAKE_SOURCE_DIR}/3rd/GTest/share/GTest)
set(imgui_DIR ${CMAKE_SOURCE_DIR}/3rd/imgui/share/imgui)


add_subdirectory(entry)
add_subdirectory(clumsy3d)
add_subdirectory(components/cl_event_driver)
add_subdirectory(components/cl_render)
add_subdirectory(components/cl_matrix)
add_subdirectory(components/cl_core)
add_subdirectory(components/cl_ui)

add_subdirectory(unit_test/cl_matrix_test)

