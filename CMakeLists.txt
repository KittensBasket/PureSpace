cmake_minimum_required(VERSION 3.10)
project(PureSpace)

set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    main.cpp)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
pkg_check_modules(externals QUIET entt glfw)

if(NOT externals_FOUND)
    add_subdirectory(ext/entt)
    add_subdirectory(ext/glfw)
endif(NOT entt_FOUND)

option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC ext
)

target_link_directories(${PROJECT_NAME}
    PRIVATE ext/glfw/src
)

target_link_libraries(${PROJECT_NAME}
    glfw
    OpenGL::GL
)