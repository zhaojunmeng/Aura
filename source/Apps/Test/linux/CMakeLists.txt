# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.6)

project(Test)
SET(${PROJECT_NAME} 1.0)
set(DATA 
#	data/momo_ogre_plus.blend 
	../data/OgreKitStartup.cfg 
#	data/OgreKitResource.cfg 
)

if (APPLE)
	include_directories(${OGRELITE_SOURCE_DIR}/OgreMain/include/OSX)
    SET(EXETYPE MACOSX_BUNDLE)
    SET_SOURCE_FILES_PROPERTIES( MainMenu.nib  PROPERTIES MACOSX_PACKAGE_LOCATION Resources )
 	SET_SOURCE_FILES_PROPERTIES(${DATA} PROPERTIES MACOSX_PACKAGE_LOCATION Resources )
	SET (NibFile MainMenu.nib)
endif()


set(SRC 
	${DATA} 
	../source/Main.cpp 
#	source/Common.h 
#	source/ACalls.h source/ACalls.cpp
#	source/RatLogic.h source/RatLogic.cpp 
#	source/MomoLogic.h source/MomoLogic.cpp 
#	source/SceneLogic.h source/SceneLogic.cpp
)

include_directories(
	${OGREKIT_INCLUDE}
)

link_libraries(
    ${OGREKIT_LIB}
)


#set(HiddenCMakeLists ../CMakeLists.txt)
#source_group(ParentCMakeLists FILES ${HiddenCMakeLists})


if (APPLE)
	add_executable(
	${PROJECT_NAME}
	MACOSX_BUNDLE
	../data/MainMenu.nib
	${SRC} ${HiddenCMakeLists}
)
else ()
	add_executable(${PROJECT_NAME} ${SRC} ${HiddenCMakeLists})
	
	IF (NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)

		if(NOT (${CMAKE_CURRENT_BINARY_DIR} EQUAL ${CMAKE_SOURCE_DIR}))
			ADD_CUSTOM_COMMAND(
				TARGET ${PROJECT_NAME}
				POST_BUILD
				#COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/data/momo_ogre_plus.blend ${CMAKE_CURRENT_BINARY_DIR}
				COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/../data/OgreKitResource.cfg ${CMAKE_CURRENT_BINARY_DIR}
				COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/../data/OgreKitStartup.cfg ${CMAKE_CURRENT_BINARY_DIR})
		endif()
	endif()
		
endif()

