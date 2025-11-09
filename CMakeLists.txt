cmake_minimum_required(VERSION 3.10)
project(OnlyNews)

set(CMAKE_CXX_STANDARD 17)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/include)

include_directories(${INC_DIR})
file(GLOB SRC_FILES ${SRC_DIR}/*.cpp)

add_executable(onlynews ${SRC_FILES})

option(BUILD_API "Build API server" ON)
if(BUILD_API)
    add_executable(onlynews_api api/OnlyNewsAPI.cpp ${SRC_DIR}/*.cpp)
    target_include_directories(onlynews_api PRIVATE ${INC_DIR} api)
    if (WIN32)
        target_link_libraries(onlynews_api PRIVATE ws2_32)
    endif()
endif()
