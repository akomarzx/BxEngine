cmake_minimum_required(VERSION 3.0)


project(BxEngine
		VERSION 2.0
		DESCRIPTION "Simple Cmake project with glfw and glew"
		HOMEPAGE_URL "https://github.com/akomarzx/msep"
		LANGUAGES C CXX
		)
configure_file(config/BxEngineConfig.h.in BxEngineConfig.h)

set (CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} src/Application.cpp)


target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

find_package(OpenGL REQUIRED)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/dep/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/dep/glew/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_subdirectory(dep/glew)

add_subdirectory(dep/glfw)

add_subdirectory(dep/MyLibrary)


target_include_directories	(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dep/MyLibrary/header
										   PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dep/glew/include
										   PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dep/glfw/include
							)
								
target_link_libraries	(${PROJECT_NAME} PRIVATE OpenGL::GL
										 PRIVATE glfw
										 PRIVATE libglew_static
										 PRIVATE MyLibrary
						)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/BxEngineConfig.h" DESTINATION include)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${BxEngine_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${BxEngine_VERSION_MAJOR}")
set(CPACK_PACKAGE_EXECUTABLES "BxEngine" "BxEngine")
include(CPack)