cmake_minimum_required(VERSION 3.30)

project(cl_ui)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
PUBLIC
	FILE_SET cxx_modules
	TYPE CXX_MODULES
	FILES 
	ui.ixx  
	ui_type_table.ixx  
PRIVATE
	ui.cpp  
	ui_components.cpp  
	ui_wrappers.cpp  
	##imgui impl
	imgui_impl_glfw.h
	imgui_impl_glfw.cpp
	imgui_impl_opengl3.h
	imgui_impl_opengl3.cpp
	imgui_impl_opengl3_loader.h
)


target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)


target_link_libraries(${PROJECT_NAME} PRIVATE cl_core)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)




