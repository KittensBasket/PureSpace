cmake_minimum_required(VERSION 3.10)
project(PureSpace-tests)

set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wconversion -Wunreachable-code -Wold-style-cast -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -Wconversion -Wunreachable-code -Wold-style-cast -fprofile-arcs -ftest-coverage")

find_package(OpenGL REQUIRED)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include(GoogleTest)

set (TESTS
	collision_test.hpp
	shader_test.hpp
	graphics_test.hpp
)

add_executable(${PROJECT_NAME} main.cpp ${TESTS})

add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/../res
		${CMAKE_CURRENT_BINARY_DIR}/res
)

target_include_directories(${PROJECT_NAME} 
	PUBLIC ../src
	PUBLIC ../ext/glfw/include
    PUBLIC ../ext/entt/single_include
    PUBLIC ../ext/stb
)

target_link_directories(${PROJECT_NAME}
    PRIVATE glew
    PRIVATE glfw
)

target_link_libraries(${PROJECT_NAME}
	OpenGL::GL
	GLEW::GLEW
	glfw
)

target_link_libraries(${PROJECT_NAME} 
	gtest
	gtest_main 
	gmock 
	pthread 
	gcov
)

gtest_add_tests(TARGET ${PROJECT_NAME}
	TEST_SUFFIX .noArgs
	TEST_LIST   noArgsTests
)

gtest_add_tests(TARGET ${PROJECT_NAME}
	EXTRA_ARGS  --someArg someValue
	TEST_SUFFIX .withArgs
	TEST_LIST   withArgsTests
)
