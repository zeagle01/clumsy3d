
set(AsLib "as_lib")
set(AsSource "as_source")
set(TurnOff "off")
set(ComponentStatus "${TurnOff};${AsSource};${AsLib}")


##append_source_file begin/end
macro(append_source_file_begin my_target)
	set(source_file_groups "")
	set(source_file_names "")
	set(source_file_target ${my_target})
endmacro()

macro(append_source_file group_name file_name)
	list(APPEND source_file_groups ${group_name})
	list(APPEND source_file_names  ${file_name})
endmacro()

macro(append_source_file_end)

	target_sources(${source_file_target} PRIVATE ${source_file_names})

	foreach(g f IN ZIP_LISTS source_file_groups source_file_names)
		source_group(${g} FILES ${f})
		#message("--- g f : ${g} ${f}")
	endforeach()


endmacro()


##set_way_of_introduction
function(set_way_of_introduction var_name)
	set(${var_name} ${AsSource} CACHE STRING "way_of_introduction")
	set_property(CACHE ${var_name} PROPERTY STRINGS ${ComponentStatus})
endfunction()

##copy_dll_to_exe
function(copy_dll_to_exe my_exe)
	add_custom_command(TARGET ${my_exe} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		$<TARGET_RUNTIME_DLLS:${my_exe}> $<TARGET_FILE_DIR:${my_exe}> 
		COMMAND_EXPAND_LISTS
	)

	add_custom_command(TARGET ${my_exe} POST_BUILD COMMAND ${CMAKE_COMMAND} -E echo 
		"-- copy: $<TARGET_RUNTIME_DLLS:${my_exe}> -> $<TARGET_FILE_DIR:${my_exe}> "
	)
endfunction()

##link_target
function(link_target dst_target access source_target source_target_status)

	if(${source_target_status} STREQUAL ${TurnOff})
	else()
		target_link_libraries(${dst_target} ${access} ${source_target})
	endif()
	if(TARGET ${source_target})
		message( "---linking: ${dst_target} <-- ${source_target} (${source_target_status}) linked")
	else()
		message( "---linking: ${dst_target} <-- ${source_target} (${source_target_status}) not linked due to ${source_target} is not present")
	endif()
endfunction()


##introduce_2nd_target
function(introduce_2nd_target my_target source_dir)

	set(target_way_of_introduction WayOfIntroduction_${my_target} )
	set_way_of_introduction(${target_way_of_introduction})

	if(${${target_way_of_introduction}} STREQUAL ${AsSource})
		#message("source target ${my_target} to ${source_dir}")
		add_subdirectory(${source_dir})
	endif()


endfunction()

##find_package_config
function(find_package_config  my_target)

	set(target_way_of_introduction WayOfIntroduction_${my_target} )

	set(target_as_binary ${my_target}_as_binary)

	set(${target_as_binary} TRUE)

	if(DEFINED  ${target_way_of_introduction})

		if(${${target_way_of_introduction}} STREQUAL ${AsSource})
			set(${target_as_binary} FALSE)
		endif()

	endif()

	if(${target_as_binary})

		set(target_config Config_${my_target})

		if(DEFINED ENV{${target_config}})
			message("--- try to link: ${PROJECT_NAME} <-- ${my_target}, as binary with ${target_config} path: $ENV{${target_config}}")
		else()
			message(FATAL_ERROR "--- try to link: ${PROJECT_NAME} <-- ${my_target}, as binary but not found ${target_config} path ! set enviroment variable ${target_config} to dir of ${my_target} ")
		endif()

		find_package(${my_target} CONFIG REQUIRED PATHS $ENV{${target_config}})

	else()
			message("--- try to link: ${PROJECT_NAME} <-- ${my_target}, as source")
	endif()

endfunction()


##install_config
function(install_config my_target)

	include(GNUInstallDirs)
	INSTALL(
		TARGETS ${my_target} 
		EXPORT ${my_target}_export
		LIBRARY DESTINATION ${CAMKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	)

	install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${my_target}-config.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${my_target})

	install(
		EXPORT ${my_target}_export
		FILE ${my_target}_targets.cmake
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${my_target}
		)

endfunction()
