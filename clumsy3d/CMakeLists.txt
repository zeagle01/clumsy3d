

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
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

target_link_libraries(${PROJECT_NAME} PRIVATE cl_event_driver)
target_link_libraries(${PROJECT_NAME} PRIVATE cl_render)
