
cmake_minimum_required(VERSION 3.30)

project(cl_event_driver)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
PUBLIC
	FILE_SET cxx_modules
	TYPE CXX_MODULES
	FILES 
	event_driver.ixx  
PRIVATE
	event_driver.cpp  
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

