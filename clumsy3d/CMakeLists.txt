

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
	entity_relation.cpp
	entity_relation_functions.cpp
	ui_binder.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

target_link_libraries(${PROJECT_NAME} PRIVATE cl_event_driver)
target_link_libraries(${PROJECT_NAME} PRIVATE cl_render)
target_link_libraries(${PROJECT_NAME} PRIVATE cl_core)
target_link_libraries(${PROJECT_NAME} PRIVATE cl_matrix)
target_link_libraries(${PROJECT_NAME} PRIVATE cl_ui)
