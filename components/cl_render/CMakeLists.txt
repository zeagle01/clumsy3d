
cmake_minimum_required(VERSION 3.30)

project(cl_render)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
PUBLIC
	FILE_SET cxx_modules
	TYPE CXX_MODULES
	FILES 
	renderer.ixx  
PRIVATE
	renderer.cpp  
	shader.cpp  
	vertex_array.cpp  
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
