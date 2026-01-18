# Set minimum CMAKE
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project( DynamicStringChallenge )

# require C++20
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_EXTENSIONS OFF )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

set( APP_EXECUTABLE DynamicStringTest )

set( LIB_NAME classLibrary )

# Add the DynamicString class
add_library( ${LIB_NAME} STATIC
             src/DynamicString.cpp inc/DynamicString.h )
target_include_directories( ${LIB_NAME} PUBLIC inc )

ADD_EXECUTABLE( ${APP_EXECUTABLE} src/DynamicStringTest.cpp )
TARGET_LINK_LIBRARIES( ${APP_EXECUTABLE} ${LIB_NAME} )

set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT ${APP_EXECUTABLE} )

include (CTest)
add_test(${APP_EXECUTABLE}_accessor ${APP_EXECUTABLE} 1)
add_test(${APP_EXECUTABLE}_output ${APP_EXECUTABLE} 2)
add_test(${APP_EXECUTABLE}_comparison ${APP_EXECUTABLE} 3)
add_test(${APP_EXECUTABLE}_modification ${APP_EXECUTABLE} 4)
add_test(${APP_EXECUTABLE}_deep_copy ${APP_EXECUTABLE} 5)
add_test(${APP_EXECUTABLE}_bounds_checking ${APP_EXECUTABLE} 6)

find_program(VALGRIND "valgrind")
if(VALGRIND)
	add_custom_target(valgrind
		COMMAND "${VALGRIND}" --tool=memcheck --leak-check=yes --show-reachable=yes --error-exitcode=1 $<TARGET_FILE:${APP_EXECUTABLE}>)
endif()
