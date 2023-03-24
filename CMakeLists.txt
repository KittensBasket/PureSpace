cmake_minimum_required(VERSION 3.10)
project(PureSpace)

set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PkgConfig REQUIRED)
pkg_check_modules(entt QUIET entt)

if(NOT entt_FOUND)
    add_subdirectory(ext/entt)
endif(NOT entt_FOUND)

include_directories(ext)

set(SOURCES
    main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})