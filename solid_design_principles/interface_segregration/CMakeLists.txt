
cmake_minimum_required(VERSION 3.16)

project(LearnCPP)



set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.72.0)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(run_me run.cpp )
    target_link_libraries(run_me ${Boost_LIBRARIES})
    set_property(TARGET run_me PROPERTY CXX_STANDARD 11)
endif(Boost_FOUND)
