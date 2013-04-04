cmake_minimum_required (VERSION 2.6) 
 
set (PROJECT test_vectors) 
 
project (${PROJECT}) 

find_package( Boost REQUIRED )

include_directories (${Boost_INCLUDE_DIRS} ../shared)

if (MSVC)
	add_definitions (-D_SCL_SECURE_NO_WARNINGS)
elseif (CMAKE_COMPILER_IS_GNUCXX)
else ()
	message ("Unknown compiler")
endif ()


 
# set (HEADERS 
#	hello.h)
 
set (SOURCES 
	../vectors/test_vectors.cpp) 
 
add_executable (${PROJECT} ${HEADERS} ${SOURCES})