

cmake_minimum_required(VERSION 3.30)


project(clumsy3d)


add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} 
PUBLIC
	FILE_SET cxx_modules
	TYPE CXX_MODULES
	FILES 
	clumsy3d.ixx  
PRIVATE
	clumsy3d.cpp  
	component.cpp
	update_table.cpp
	input_table.cpp
	update_functions.cpp
	update_functions_meta.cpp
	ui_binder.cpp
	entity_manager.cpp
	commands.cpp
	command_manager.cpp
	invoke_update_function.cpp
	common_structs.cpp
	cmd_executor.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

target_link_libraries(${PROJECT_NAME} PRIVATE cl_event_driver)
target_link_libraries(${PROJECT_NAME} PRIVATE cl_render)
target_link_libraries(${PROJECT_NAME} PRIVATE cl_core)
target_link_libraries(${PROJECT_NAME} PRIVATE cl_matrix)
target_link_libraries(${PROJECT_NAME} PRIVATE cl_ui)
