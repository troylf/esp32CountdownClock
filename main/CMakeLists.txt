# Edit following two lines to set component requirements (see docs)
# set(COMPONENT_REQUIRES )
# set(COMPONENT_PRIV_REQUIRES )

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Functions
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
function(appendModuleSrc projectList returnList)

	execute_process(
					COMMAND sh -c "ls -d ${CMAKE_CURRENT_SOURCE_DIR}/modules/*/"
					OUTPUT_VARIABLE dirVariable
					RESULT_VARIABLE dirResult
					)

	message("VARIABLE TEST FILES ${projectList}")

	if(NOT ${dirResult})

		string(REPLACE "\n" ";" dirList ${dirVariable})

		message("VARIABLE TEST List ${dirList}")

		foreach(item ${dirList})
			string(APPEND item "src")
			list(APPEND projectList ${item})
		endforeach()

		message("VARIABLE Final List ${projectList}")

		set(${returnList} ${projectList} PARENT_SCOPE)

	endif()

endfunction()

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Script
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set(project_dirs 
		"application/src" 
		"PHY/src" 
		"drivers/src" 
		)

appendModuleSrc( "${project_dirs}" project_dirs )

idf_component_register(
	SRC_DIRS ${project_dirs}
	INCLUDE_DIRS ${project_dirs}
	)

