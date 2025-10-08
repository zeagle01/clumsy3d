
cmake_minimum_required(VERSION 3.30)

project(cl_matrix_test)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}

PUBLIC
	FILE_SET cxx_modules
	TYPE CXX_MODULES
	FILES 
PRIVATE
	main.cpp
	matrix_test.cpp  
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

target_link_libraries(${PROJECT_NAME} PRIVATE cl_matrix)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gmock)
