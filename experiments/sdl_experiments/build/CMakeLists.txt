cmake_minimum_required (VERSION 2.6)

set (PROJECT sdl_experiment)
project (${PROJECT})

find_package(SDL REQUIRED)
if(NOT SDL_FOUND)
    message(SEND_ERROR "Failed to find SDL")
    return()
else()
    include_directories(${SDL_INCLUDE_DIR})
endif()

include_directories (../../experiments/shared)

if (MSVC)
	add_definitions (-D_SCL_SECURE_NO_WARNINGS)
elseif (CMAKE_COMPILER_IS_GNUCXX)
else ()
	message ("Unknown compiler")
endif ()

# set (HEADERS
#	hello.h)

set (SOURCES
	../placeholder.cpp)


add_executable (${PROJECT} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT} ${SDL_LIBRARY})



