

cmake_minimum_required(VERSION 3.30)


project(entry)


add_executable(
	${PROJECT_NAME}
	main.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

target_link_libraries(${PROJECT_NAME} PRIVATE clumsy3d)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
	$<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}> 
	COMMAND_EXPAND_LISTS
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E echo 
	"-- copy: $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> -> $<TARGET_FILE_DIR:${PROJECT_NAME}> "
)
