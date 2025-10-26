
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
	get_type_name.ixx
	static_var_map.ixx
	type_helper.ixx
PUBLIC
	include/cl_core/config_define_helper.h
PRIVATE
	macro_loop.h
)

target_include_directories(${PROJECT_NAME}
PRIVATE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/cl_core>
PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

