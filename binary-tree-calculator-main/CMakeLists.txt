# Set minimum CMAKE
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project( BinaryTrees )

# require C++20
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_EXTENSIONS OFF )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

set( APP_EXECUTABLE BinaryTreesTest )

include_directories( inc )

ADD_EXECUTABLE( ${APP_EXECUTABLE} "src/binary-tree-test.cpp"  "src/TreeParser.cpp")
#TARGET_LINK_LIBRARIES( ${APP_EXECUTABLE} ${LIB_NAME} )

set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT ${APP_EXECUTABLE} )

include (CTest)
add_test(${APP_EXECUTABLE}_SimpleExpressions ${APP_EXECUTABLE} 1)
add_test(${APP_EXECUTABLE}_TwoOrMoreOperators ${APP_EXECUTABLE} 2)
add_test(${APP_EXECUTABLE}_MultiDigitNumbers ${APP_EXECUTABLE} 3)
add_test(${APP_EXECUTABLE}_BigExpressions ${APP_EXECUTABLE} 4)

find_program(VALGRIND "valgrind")
if(VALGRIND)
	add_custom_target(valgrind
		COMMAND "${VALGRIND}" --tool=memcheck --leak-check=yes --show-reachable=yes  --error-exitcode=1 $<TARGET_FILE:${APP_EXECUTABLE}>)
endif()
