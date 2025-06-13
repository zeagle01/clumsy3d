

cmake_minimum_required(VERSION 3.30)


project(clumsy3d_entry)


add_executable(
	${PROJECT_NAME}
	main.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
