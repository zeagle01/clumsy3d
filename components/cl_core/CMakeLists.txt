
cmake_minimum_required(VERSION 3.30)

project(cl_core)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
PUBLIC
	FILE_SET cxx_modules
	TYPE CXX_MODULES
	FILES 
	core.ixx  
	entity_system.ixx  
	type_list.ixx
	member_extractor.ixx
PRIVATE
	macro_loop.h
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

