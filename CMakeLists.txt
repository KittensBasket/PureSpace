cmake_minimum_required(VERSION 3.10)
project(PureSpace)

set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(GLEW 2.0 REQUIRED)
add_compile_definitions(GLEW_STATIC)

set(SOURCES
    main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

add_subdirectory(ext/glfw)
add_subdirectory(ext/entt)
add_subdirectory(ext/gtest)

target_include_directories(${PROJECT_NAME}
    PUBLIC ext/glfw/include
    PUBLIC ext/entt/single_include
    PUBLIC ext/stb
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

add_subdirectory(tests)
enable_testing()
add_test(NAME gtest-tests COMMAND tests/PureSpace-tests --gtest_output:./PureSpace-tests.xml)
